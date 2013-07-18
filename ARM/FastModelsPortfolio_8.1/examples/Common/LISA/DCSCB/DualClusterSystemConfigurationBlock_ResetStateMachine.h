//
// Handle resets of the Dual Cluster system
//

#ifndef DUALCLUSTERSYSTEMCONFIGURATIONBLOCK_RESETSTATEMACHINE_H
#define DUALCLUSTERSYSTEMCONFIGURATIONBLOCK_RESETSTATEMACHINE_H

#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <vector>

#ifdef _WIN32
#define HERE  if (1) ; else std::cerr << __FILE__ << ":" << __LINE__ << ":" << __FUNCSIG__ << ": "
#define HEREQ if (1) ; else std::cerr
#else
#define HERE  if (1) ; else std::cerr << __FILE__ << ":" << __LINE__ << ":" << __PRETTY_FUNCTION__ << ": "
#define HEREQ if (1) ; else std::cerr
#endif

namespace DCSCBDetails // Dual Cluster System Configuration Block
{
    struct cfg_t {
        bool                      cfgend;
        bool                      vinithi;
        bool                      teinit;

        void clear()
            {
                cfgend = vinithi = teinit = false;
            }

        bool operator == (cfg_t const& o_)
            {
                return cfgend == o_.cfgend
                    && vinithi == o_.vinithi
                    && teinit == o_.teinit
                    ;
            }
    };

    struct cluster_cfg_t {
        unsigned                  reset_cluster_id;
        unsigned                  cluster_id;
        bool                      reset_iminlen;
        bool                      iminlen; // per cluster

        cluster_cfg_t()
            : reset_cluster_id(0),
              reset_iminlen(false)
        {
        }

        void clear()
            {
                cluster_id = reset_cluster_id;
                iminlen = reset_iminlen;
            }

        bool operator == (cluster_cfg_t const& o_)
            {
                return cluster_id == o_.cluster_id
                    && iminlen == o_.iminlen
                    ;
            }
    };

    class reset_handler_t
    {
    public:
        static unsigned const     MAX_CORES_PER_CLUSTER = 4;
        static unsigned const     MAX_CLUSTERS          = 2;

    private:
        static unsigned const     MAX_CORES             = MAX_CLUSTERS * MAX_CORES_PER_CLUSTER;

        unsigned                  bitmap_of_cores_present;

        // Represents input signals for all cores in all clusters
        bool                      wfi_state[MAX_CORES];

        // Represent operations for all cores in all clusters
        bool                      issue_cpu_reset[MAX_CORES];    // reset the cpu, NEON, VFP
        bool                      issue_cpu_poreset[MAX_CORES];  // reset the cpu, NEON, VFP and debug
        bool                      issue_cluster_reset[MAX_CLUSTERS]; // reset all cpus, NEON units, VFP units
        bool                      issue_system_reset; // reset everything except debug
        bool                      issue_poreset;      // reset everything including debug

        // Represent intermediate helpers for all cores in all clusters
        bool                      safe_to_assert_reset[MAX_CORES];

        bool                      cpu_reset_req[MAX_CORES];             // from SYS_SWRESET
        bool                      cpu_poreset_req[MAX_CORES];           // from SYS_SWRESET
        bool                      cluster_reset_req[MAX_CLUSTERS];      // from SYS_SWRESET
        bool                      system_reset_req;                     // from SYS_SWRESET
        bool                      poreset_req;                          // from SYS_SWRESET

    protected:
        struct reset_signals_t
        {
            bool cpu_reset[MAX_CORES];
            bool debug_reset[MAX_CORES]; // Not used in rst_hold register
            bool cpu_poreset[MAX_CORES];
            bool cluster_reset[MAX_CLUSTERS];

            void clear()
                {
                    std::fill( &cpu_reset[0], &cpu_reset[MAX_CORES], false );
                    std::fill( &debug_reset[0], &debug_reset[MAX_CORES], false );
                    std::fill( &cpu_poreset[0], &cpu_poreset[MAX_CORES], false );
                    std::fill( &cluster_reset[0], &cluster_reset[MAX_CLUSTERS], false );
                }
        };

        reset_signals_t           rst_hold;

    private:
        reset_signals_t           current_reset_pins;
        cfg_t                     current_cfg[MAX_CORES];
        cluster_cfg_t             current_cluster_cfg[MAX_CLUSTERS];
        bool                      current_system_debug_reset_pin;
        bool                      current_system_reset_pin;

        cfg_t                     cfg_at_last_reset[MAX_CORES];
        cluster_cfg_t             cluster_cfg_at_last_reset[MAX_CLUSTERS];

    protected:
        unsigned to_start_cpu_id( unsigned cluster_index_ ) const
            {
                return cluster_index_ * MAX_CORES_PER_CLUSTER;
            }

        unsigned cluster_index_from_cpu_id( unsigned cpu_id_ ) const
            {
                return cpu_id_ / MAX_CORES_PER_CLUSTER;
            }

        unsigned local_cpu_id_from_cpu_id( unsigned cpu_id_ ) const
            {
                return cpu_id_ % MAX_CORES_PER_CLUSTER;
            }

        unsigned to_cpu_id_from_local_id_and_cluster( unsigned local_cpu_id_, unsigned cluster_index_ ) const
            {
                assert( local_cpu_id_ < MAX_CORES_PER_CLUSTER );
                assert( cluster_index_ < MAX_CLUSTERS );
                return local_cpu_id_ + cluster_index_ * MAX_CORES_PER_CLUSTER;
            }

        unsigned get_wfi_state_for_cluster( unsigned cluster_index_ ) const
        {
            unsigned cpu_id = to_start_cpu_id( cluster_index_ );
            return wfi_state[ cpu_id + 0 ] << 0
                |  wfi_state[ cpu_id + 1 ] << 1
                |  wfi_state[ cpu_id + 2 ] << 2
                |  wfi_state[ cpu_id + 3 ] << 3
                ;
        }

    private:
        bool all_safe_to_assert_resetQ( unsigned cluster_index_ ) const
            {
                unsigned i = to_start_cpu_id(cluster_index_);
                unsigned end_index = i + MAX_CORES_PER_CLUSTER;
                while (i != end_index && safe_to_assert_reset[i])
                {
                    ++ i;
                }
                return i == end_index;
            }

        void evaluate_issue( unsigned cpu_id_ )
            {
                unsigned const i             = cpu_id_;
                unsigned const cluster_index = cluster_index_from_cpu_id( cpu_id_ );
                // A core may only be reset once it has no outstanding transactions.
                // So in practical terms this means, it is in STANDBYWFI mode or
                // some sort of reset mode already (or not present).
                assign(
                    safe_to_assert_reset[i],
                    wfi_state[i]
                    || issue_cpu_reset[i]
                    || issue_cpu_poreset[i]
                    || issue_cluster_reset[cluster_index]
                    || issue_system_reset
                    || issue_poreset
                    || ((bitmap_of_cores_present >> i) & 1) == 0
                    );

//                HERE << "safe_to_assert_reset[" << i << "] = " << safe_to_assert_reset[i] << "\n";

                assign(
                    issue_cpu_reset[i],
                    // If in WFI state and asked for a reset hold this processor
                    (safe_to_assert_reset[i] && (cluster_reset_req[cluster_index]
                                                 || cpu_reset_req[i]
                                                 || rst_hold.cpu_reset[i]))
                    // Or already reset and there is a hold on the reset
                    || (issue_cpu_reset[i] && rst_hold.cpu_reset[i])
                    );

//                HERE << "issue_cpu_reset[" << i << "] = " << issue_cpu_reset[i] << "\n";

                assign(
                    issue_cpu_poreset[i],
                    // If in WFI state and asked for a reset hold this processor
                    (safe_to_assert_reset[i] && (cpu_poreset_req[i]
                                                 || rst_hold.cpu_poreset[i]))
                    // Or already reset and there is a hold on the reset
                    || (issue_cpu_poreset[i] && rst_hold.cpu_poreset[i])
                    );

//                HERE << "issue_cpu_poreset[" << i << "] = " << issue_cpu_poreset[i] << "\n";
            }

        void evaluate_issue_cluster_reset(unsigned cluster_index_)
            {
                assign(
                    issue_cluster_reset[cluster_index_],
                    (all_safe_to_assert_resetQ(cluster_index_)
                    && (cluster_reset_req[cluster_index_]
                        || rst_hold.cluster_reset[cluster_index_]))
                    // ... or is already in cluster reset and there is a reset hold request
                    || (issue_cluster_reset[cluster_index_] && rst_hold.cluster_reset[cluster_index_])
                    );
            }

        void evaluate_issue_system_reset()
            {
                // We do not need to wait for any safe point so we can always
                // issue a system reset
                assign( issue_system_reset, system_reset_req );
//                HERE << "issue_system_reset = " << issue_system_reset << "\n";
            }

        void evaluate_issue_poreset()
            {
                // We do not need to wait for any safe point so we can always
                // issue a system reset
                assign( issue_poreset, poreset_req );
//                HERE << "issue_poreset = " << issue_poreset << "\n";
            }

        //! Return true if need to be called again with cpu_id_ == ~0u
        void update_reset_signals_helper( unsigned cpu_id_ = ~0u )
            {
                if (cpu_id_ != ~0u)
                {
                    unsigned const cluster_index = cluster_index_from_cpu_id( cpu_id_ );
                    evaluate_issue( cpu_id_ );
                    evaluate_issue_cluster_reset( cluster_index );
                }
                else
                {
                    for (unsigned i = 0; i != MAX_CORES; ++ i)
                    {
                        unsigned const cluster_index = cluster_index_from_cpu_id( i );
                        evaluate_issue( i );
                        evaluate_issue_cluster_reset( cluster_index );
                    }
                }
                evaluate_issue_system_reset();
                evaluate_issue_poreset();

                // Now evaluate all the reset pins.  There is some scope for optimising this
                // but don't bother for the moment.

                //
                // When each pin is changed to assert reset then it will make all
                // requests for that pin go away.
                //

                for (unsigned i = 0; i != MAX_CORES; ++ i)
                {
                    unsigned const cluster_index = cluster_index_from_cpu_id( i );
                    set_cpu_reset_pin(
                        i,
                        issue_cpu_reset[i]
                        || issue_cpu_poreset[i]
                        || issue_cluster_reset[cluster_index]
                        || issue_system_reset
                        || issue_poreset
                        ); // will remove cpu_reset_req

                    /*
                    HERE << "cpu reset " << i << " : "
                         << issue_cpu_reset[i]
                         << issue_cpu_poreset[i]
                         << issue_cluster_reset[cluster_index]
                         << issue_system_reset
                         << issue_poreset
                         << "\n"
                        ;
                    */

                    set_debug_and_poreset_pin(
                        i,
                        issue_cpu_poreset[i]
                        || issue_poreset
                        ); // will remove cpu_poreset_req
                }

                for (unsigned i = 0; i != MAX_CLUSTERS; ++ i)
                {
                    bool const new_value
                        = issue_cluster_reset[i]
                        || issue_system_reset
                        || issue_poreset
                        ;
                    set_cluster_reset_pin(
                        i, new_value
                        ); // will remove cluster_reset_req
                }

                set_system_reset_pin(
                    issue_system_reset
                    || issue_poreset
                    ); // will remove system_reset_req

                set_system_debug_reset_pin(
                    issue_poreset
                    ); // will remove poreset_req
            }

        void update_reset_signals( unsigned cpu_id_ = ~0u )
            {
                // Some events will need to trigger a pulse or we get deadlocked.
                // For example, a system reset will need to generate a pulse or we
                // won't be able to come out of reset again!  We loop until we don't
                // change.
//                HERE << "----------------------------------------------------------------------\n";
                do {
                    changed = false;
//                    HERE << "----------\n";

                    update_reset_signals_helper( cpu_id_ );

                    // A cluster reset req can have wider implications!
                    cpu_id_ = ~0u;
                } while (changed);
            }

    public:

        uint32_t get_bitmap_of_cores_present() const
        {
            return bitmap_of_cores_present;
        }

        enum reset_pin_id_t {
            cpu_reset_pin,
            debug_reset_pin,
            cpu_poreset_pin,
            cluster_reset_pin,
            system_debug_reset_pin,
            system_reset_pin
        };

        struct reset_pin_delta_t {
            reset_pin_id_t        pin;
            unsigned              local_cpu_id;
            unsigned              cluster_index;

        private:
            unsigned              value;
        public:

            reset_pin_id_t get_pin() const { return pin; }

            bool valueQ() const
                { return (value & 1) != 0;                                                               }
            bool cfgendQ() const
                { assert( pin == cpu_reset_pin || pin == cpu_poreset_pin ); return (value & 8) != 0;     }
            bool vinithiQ() const
                { assert( pin == cpu_reset_pin || pin == cpu_poreset_pin ); return (value & 4) != 0;     }
            bool teinitQ() const
                { assert( pin == cpu_reset_pin || pin == cpu_poreset_pin ); return (value & 2) != 0;     }
            unsigned get_cluster_id() const
                { assert( pin == cluster_reset_pin ); return (value >> 4) & 0xF;   }
            bool iminlenQ() const
                { assert( pin == cluster_reset_pin ); return (value & 0x100) != 0; }


            std::ostream& print( std::ostream& os_, std::string const& indent_ = "" ) const
                {
                    (void)indent_;
                    switch (pin)
                    {
                    case cpu_reset_pin:
                        return os_ << "cpu" << local_cpu_id << "-of-" << cluster_index << "->"
                                   << valueQ()
                                   << '-'
                                   << (cfgendQ()  ? 'B' : 'L')
                                   << (vinithiQ() ? 'V' : 'v')
                                   << (teinitQ()  ? 'T' : 't');
                    case debug_reset_pin:
                        return os_ << "debug" << local_cpu_id << "-of-" << cluster_index << "->" << valueQ();
                    case cpu_poreset_pin:
                        return os_ << "cpupo" << local_cpu_id << "-of-" << cluster_index << "->"
                                   << valueQ()
                                   << '-'
                                   << (cfgendQ()  ? 'B' : 'L')
                                   << (vinithiQ() ? 'V' : 'v')
                                   << (teinitQ()  ? 'T' : 't');
                    case cluster_reset_pin:
                        return os_ << "cluster" << cluster_index << "->"
                                   << valueQ()
                                   << '-'
                                   << get_cluster_id()
                                   << '-'
                                   << (iminlenQ() ? "I" : "i");
                    case system_debug_reset_pin:
                        return os_ << "sysdebug" << "->" << valueQ();
                    case system_reset_pin:
                        return os_ << "system->" << valueQ();
                    }
                    assert(0);
                    return os_ << "<error-unknown-reset>";
                }

            reset_pin_delta_t( reset_pin_id_t pin_,
                               unsigned       local_cpu_id_,
                               unsigned       cluster_index_,
                               bool           value_ )
                : pin           ( pin_           ),
                  local_cpu_id  ( local_cpu_id_  ),
                  cluster_index ( cluster_index_ ),
                  value         ( value_         )
                {
                }

            reset_pin_delta_t( reset_pin_id_t pin_,
                               unsigned       local_cpu_id_,
                               unsigned       cluster_index_,
                               bool           value_,
                               cfg_t const&   cfg_ )
                : pin           ( pin_           ),
                  local_cpu_id  ( local_cpu_id_  ),
                  cluster_index ( cluster_index_ )
                {
                    assert( pin_ == cpu_reset_pin );
                    assert( cluster_index_ < MAX_CLUSTERS );
                    assert( local_cpu_id_ < MAX_CORES );
                    value = (value_     * 1)
                        | (cfg_.teinit  * 2)
                        | (cfg_.vinithi * 4)
                        | (cfg_.cfgend  * 8)
                        ;
                }

            reset_pin_delta_t( reset_pin_id_t       pin_,
                               unsigned             local_cpu_id_,
                               unsigned             cluster_index_,
                               bool                 value_,
                               cluster_cfg_t const& cluster_cfg_ )
                : pin           ( pin_           ),
                  local_cpu_id  ( local_cpu_id_  ),
                  cluster_index ( cluster_index_ )
                {
                    assert( pin_ == cluster_reset_pin );
                    assert( cluster_index_ < MAX_CLUSTERS );
                    assert( local_cpu_id_ == ~0u );
                    value = (value_?1:0)
                        | (cluster_cfg_.cluster_id << 4)
                        | (cluster_cfg_.iminlen * 0x100);
                }
        };

        typedef std::vector< reset_pin_delta_t >                     reset_deltas_t;
    private:
        reset_deltas_t                                               reset_deltas;
    public:

        std::ostream& print_deltas( std::ostream& os_, std::string const& indent_ = "" ) const
            {
                reset_deltas_t::const_iterator i = reset_deltas.begin();
                while (i != reset_deltas.end())
                {
                    i->print(os_ << indent_, indent_) << "\n";
                    ++ i;
                }
                return os_;
            }

        void init( unsigned number_of_cores_present_cluster0_,
                   unsigned number_of_cores_present_cluster1_ )
            {
                bitmap_of_cores_present
                    = ((1u << number_of_cores_present_cluster0_) - 1) << 0
                    | ((1u << number_of_cores_present_cluster1_) - 1) << MAX_CORES_PER_CLUSTER;
                common_init();
            }

        void reset( unsigned cfg_activecluster )
            {
                common_init();

                //
                // The reset values of the rst_hold registers are dependent on which
                // cluster we wish to be active out of power-on.
                //
                for (unsigned i = 0; i != MAX_CLUSTERS; ++i)
                    rst_hold.cluster_reset[ i ] = (cfg_activecluster >> i & 1) != 0 ? 0 : 1;

                //
                // Set up deltas to get the system reset initially, as we have setup all the
                // reset pins as false and have requested a poreset_req then we should get
                // all pins set to true.  NOTE that poreset_req doesn't have to wait for
                // STANDBYWFI and so will occur immediately.
                //
                update_reset_signals();

                changed = false;
            }

        //! The STANDBYWFI signal received an update.  Return true if the caller should
        //  process the reset deltas.
        bool set_wfi_state(
            unsigned           local_cpu_id_,
            unsigned           cluster_index_,
            bool               value_
            )
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                if (wfi_state[cpu_id] == value_)
                {
                    return false; // do nothing
                }

                wfi_state[cpu_id] = value_;
                update_reset_signals( cpu_id );

                return ! reset_deltas.empty();
            }

        //! Setup a hold on a reset for a core, it will take effect next time that
        //  the appropriate STANDBYWFI is high
        bool set_rst_hold_cpu_reset(
            unsigned           local_cpu_id_,
            unsigned           cluster_index_,
            bool               value_
            )
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                if (rst_hold.cpu_reset[cpu_id] == value_)
                {
                    return false; // do nothing
                }

                rst_hold.cpu_reset[cpu_id] = value_;

                update_reset_signals( cpu_id );
                return ! reset_deltas.empty();
            }

        //! Setup a hold on a reset for a core, it will take effect next time that
        //  the appropriate STANDBYWFI is high
        bool set_rst_hold_cpu_poreset(
            unsigned           local_cpu_id_,
            unsigned           cluster_index_,
            bool               value_
            )
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                if (rst_hold.cpu_poreset[cpu_id] == value_)
                {
                    return false; // do nothing
                }

                rst_hold.cpu_poreset[cpu_id] = value_;

                update_reset_signals( cpu_id );
                return ! reset_deltas.empty();
            }

        //! Setup a hold on a reset for a core, it will take effect next time that
        //  the appropriate STANDBYWFI is high
        bool set_rst_hold_cluster_reset(
            unsigned           cluster_index_,
            bool               value_
            )
            {
                if (rst_hold.cluster_reset[cluster_index_] == value_)
                {
                    return false; // do nothing
                }

                rst_hold.cluster_reset[cluster_index_] = value_;

                update_reset_signals();
                return ! reset_deltas.empty();
            }

        //! Setup a pulsed cpu reset
        bool set_cpu_reset_req(
            unsigned           local_cpu_id_,
            unsigned           cluster_index_,
            bool               value_
            )
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                if (cpu_reset_req[cpu_id] == value_)
                {
                    return false; // do nothing
                }

                cpu_reset_req[cpu_id] = value_;

                update_reset_signals();
                return ! reset_deltas.empty();
            }

        //! Setup a pulsed cpu poreset
        bool set_cpu_poreset_req(
            unsigned           local_cpu_id_,
            unsigned           cluster_index_,
            bool               value_
            )
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                if (cpu_poreset_req[cpu_id] == value_)
                {
                    return false; // do nothing
                }

                cpu_poreset_req[cpu_id] = value_;

                update_reset_signals();
                return ! reset_deltas.empty();
            }

        //! Setup a pulsed cluster reset
        bool set_cluster_reset_req(
            unsigned           cluster_index_,
            bool               value_
            )
            {
                if (cluster_reset_req[cluster_index_] == value_)
                {
                    return false; // do nothing
                }

                cluster_reset_req[cluster_index_] = value_;

                update_reset_signals();
                return ! reset_deltas.empty();
            }

        //! Setup a pulsed system reset
        bool set_system_reset_req(
            bool value_
            )
            {
                if (system_reset_req == value_)
                {
                    return false; // do nothing
                }

                system_reset_req = value_;

                update_reset_signals();
                return ! reset_deltas.empty();
            }

        //! Setup a pulsed system poreset
        bool set_poreset_req(
            bool value_
            )
            {
                if (poreset_req == value_)
                {
                    return false; // do nothing
                }

                poreset_req = value_;

                update_reset_signals();
                return ! reset_deltas.empty();
            }

        //! Setup the configuration for a core.
        void set_cfg( unsigned   local_cpu_id_,
                      unsigned   cluster_index_,
                      bool       cfgend_,
                      bool       vinithi_,
                      bool       teinit_ )
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                cfg_t& c     = current_cfg[ cpu_id ];
                c.cfgend     = cfgend_;
                c.vinithi    = vinithi_;
                c.teinit     = teinit_;
            }

        //! Setup the configuration for a cluster.
        void set_cluster_cfg( unsigned   cluster_index_,
                              unsigned   cluster_id_,
                              bool       iminlen_ )
            {
                cluster_cfg_t& c = current_cluster_cfg[ cluster_index_ ];
                c.cluster_id     = cluster_id_;
                c.iminlen        = iminlen_;
            }

        //! Setup the reset configuration for a cluster.
        void set_reset_cluster_cfg( unsigned   cluster_index_,
                              unsigned   cluster_id_,
                              bool       iminlen_ )
            {
                cluster_cfg_t& c   = current_cluster_cfg[ cluster_index_ ];
                c.reset_cluster_id = cluster_id_;
                c.reset_iminlen    = iminlen_;
            }

        //! Retrieve the configuration for a core
        cfg_t get_current_cfg( unsigned   local_cpu_id_,
                               unsigned   cluster_index_ ) const
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                return current_cfg[ cpu_id ];
            }

        //! Retrieve the configuration for a core at the time of last reset
        cfg_t get_cfg_at_last_reset( unsigned   local_cpu_id_,
                                     unsigned   cluster_index_ ) const
            {
                unsigned const cpu_id = to_cpu_id_from_local_id_and_cluster( local_cpu_id_, cluster_index_ );
                return cfg_at_last_reset[ cpu_id ];
            }

        //! Retrieve the configuration for a core
        cluster_cfg_t get_current_cluster_cfg( unsigned   cluster_index_ ) const
            {
                return current_cluster_cfg[ cluster_index_ ];
            }

        //! Retrieve the configuration for a core at the time of last reset
        cluster_cfg_t get_cluster_cfg_at_last_reset( unsigned   cluster_index_ ) const
            {
                return cluster_cfg_at_last_reset[ cluster_index_ ];
            }

        //! Get the current value of the pins in an encoded
        //  form.
        uint32_t get_rst_stat( unsigned cluster_index ) const
        {
            unsigned const cpu_id = to_start_cpu_id( cluster_index );
            return
                current_reset_pins.cpu_reset       [    cpu_id + 0 ] << 0
                | current_reset_pins.cpu_reset     [    cpu_id + 1 ] << 1
                | current_reset_pins.cpu_reset     [    cpu_id + 2 ] << 2
                | current_reset_pins.cpu_reset     [    cpu_id + 3 ] << 3

                | current_reset_pins.cpu_poreset   [    cpu_id + 0 ] << 4
                | current_reset_pins.cpu_poreset   [    cpu_id + 1 ] << 5
                | current_reset_pins.cpu_poreset   [    cpu_id + 2 ] << 6
                | current_reset_pins.cpu_poreset   [    cpu_id + 3 ] << 7

                | current_reset_pins.cluster_reset [ cluster_index ] << 8
                ;
        }

        //! Retrieve a sequences of deltas to apply to the cores.
        //  This may be called at any time and if first == second then
        //  the sequences is empty and there are no deltas.
        std::pair< reset_deltas_t::const_iterator,
                   reset_deltas_t::const_iterator >
        get_reset_deltas() const
            {
                return std::make_pair( reset_deltas.begin(), reset_deltas.end() );
            }

        bool are_there_reset_deltasQ() const
            {
                return ! reset_deltas.empty();
            }

        //! Indicate that all the deltas retrieved by get_reset_deltas() have
        //  been applied.
        void reset_deltas_have_been_processed()
            {
                reset_deltas.clear();
            }


        static void tests();

    private:

        void common_init()
            {
                std::fill( &wfi_state[0], &wfi_state[MAX_CORES], false );

                std::fill( &issue_cpu_reset[0], &issue_cpu_reset[MAX_CORES], false );
                std::fill( &issue_cpu_poreset[0], &issue_cpu_poreset[MAX_CORES], false );
                std::fill( &issue_cluster_reset[0], &issue_cluster_reset[MAX_CLUSTERS], false );
                issue_system_reset = false;
                issue_poreset      = false;

                std::fill( &safe_to_assert_reset[0], &safe_to_assert_reset[MAX_CORES], false );
                std::fill( &cpu_reset_req[0], &cpu_reset_req[MAX_CORES], false );
                std::fill( &cpu_poreset_req[0], &cpu_poreset_req[MAX_CORES], false );
                std::fill( &cluster_reset_req[0], &cluster_reset_req[MAX_CLUSTERS], false );
                system_reset_req = false;
                poreset_req      = true;  // Start with a Power-On Reset

                rst_hold.clear();
                current_reset_pins.clear();

                for (unsigned i = 0; i != MAX_CORES; ++ i)
                {
                    current_cfg[ i ].clear();
                }
                for (unsigned i = 0; i != MAX_CLUSTERS; ++ i)
                {
                    current_cluster_cfg[ i ].clear();
                }

                current_system_debug_reset_pin = false;
                current_system_reset_pin = false;

                for (unsigned i = 0; i != MAX_CORES; ++ i)
                {
                    cfg_at_last_reset[ i ].clear();
                }
                for (unsigned i = 0; i != MAX_CLUSTERS; ++ i)
                {
                    cluster_cfg_at_last_reset[ i ].clear();
                }

                changed = true;
            }

        bool changed;

        void assign( bool& lvalue, bool rvalue )
            {
                if (lvalue != rvalue)
                    changed = true;
                lvalue = rvalue;
            }

        void set_cpu_reset_pin( unsigned cpu_id_, bool value_ )
            {
                if (current_reset_pins.cpu_reset[cpu_id_] != value_)
                {
                    reset_deltas.push_back(
                        reset_pin_delta_t( cpu_reset_pin,
                                           local_cpu_id_from_cpu_id( cpu_id_ ),
                                           cluster_index_from_cpu_id( cpu_id_ ),
                                           value_,
                                           current_cfg[ cpu_id_ ] )
                        );
                    current_reset_pins.cpu_reset[cpu_id_] = value_;
                    if (value_)
                    {
                        cpu_reset_req[ cpu_id_ ] = false;
                    }
                    changed = true;

                    cfg_at_last_reset[ cpu_id_ ] = current_cfg[ cpu_id_ ];
                }
            }

        void set_debug_and_poreset_pin( unsigned cpu_id_, bool value_ )
            {
                // NOTE optimisation in that the debug pin is only raised on cpu_poreset
                // so we treat them as the same
                if (current_reset_pins.debug_reset[cpu_id_] != value_)
                {
                    reset_deltas.push_back(
                        reset_pin_delta_t( debug_reset_pin,
                                           local_cpu_id_from_cpu_id( cpu_id_ ),
                                           cluster_index_from_cpu_id( cpu_id_ ),
                                           value_ )
                        );
                    current_reset_pins.debug_reset[cpu_id_] = value_;
                    current_reset_pins.cpu_poreset[cpu_id_] = value_;
                    if (value_)
                    {
                        cpu_poreset_req[ cpu_id_ ] = false;
                    }
                    changed = true;
                }
            }

        void set_cluster_reset_pin( unsigned cluster_index_, bool value_ )
            {
                if (current_reset_pins.cluster_reset[cluster_index_] != value_)
                {
                    reset_deltas.push_back(
                        reset_pin_delta_t( cluster_reset_pin,
                                           ~0u,
                                           cluster_index_,
                                           value_,
                                           current_cluster_cfg[ cluster_index_ ])
                        );
                    current_reset_pins.cluster_reset[cluster_index_] = value_;
                    if (value_)
                    {
                        cluster_reset_req[ cluster_index_ ] = false;
                    }
                    changed = true;

                    cluster_cfg_at_last_reset[ cluster_index_ ] = current_cluster_cfg[ cluster_index_ ];
                }
            }

        void set_system_reset_pin( bool value_ )
            {
                if (current_system_reset_pin != value_)
                {
                    reset_deltas.push_back(
                        reset_pin_delta_t( system_reset_pin,
                                           ~0u,
                                           ~0u,
                                           value_ )
                        );
                    current_system_reset_pin = value_;
                    if (value_)
                    {
                        system_reset_req = false;
                    }
                    changed = true;
                }
            }

        void set_system_debug_reset_pin( bool value_ )
            {
                if (current_system_debug_reset_pin != value_)
                {
                    reset_deltas.push_back(
                        reset_pin_delta_t( system_debug_reset_pin,
                                           ~0u,
                                           ~0u,
                                           value_ )
                        );
                    current_system_debug_reset_pin = value_;
                    if (value_)
                    {
                        poreset_req = false;
                    }
                    changed = true;
                }
            }

    };

    inline std::ostream& operator << (std::ostream& os_, reset_handler_t::reset_pin_delta_t const& delta_ )
    {
        delta_.print(os_);
        return os_;
    }

    //! This class implements the register illusion on top of reset_handler_t
    class reset_register_handler_t
        : public reset_handler_t
    {
        // Dual Cluster System ID register
        uint32_t dcs_id;

    public:

        void set_dcs_id(uint32_t dcs_id_)
        {
            dcs_id = dcs_id_;
        }

        uint32_t get_dcs_id()
        {
            return dcs_id;
        }

        unsigned get_rst_hold( unsigned cluster_index_ ) const
            {
                unsigned const start_of_cluster = to_start_cpu_id( cluster_index_ );
                return 0
                    | rst_hold.cpu_reset    [ start_of_cluster + 0 ] << 0
                    | rst_hold.cpu_reset    [ start_of_cluster + 1 ] << 1
                    | rst_hold.cpu_reset    [ start_of_cluster + 2 ] << 2
                    | rst_hold.cpu_reset    [ start_of_cluster + 3 ] << 3
                    | rst_hold.cpu_poreset  [ start_of_cluster + 0 ] << 4
                    | rst_hold.cpu_poreset  [ start_of_cluster + 1 ] << 5
                    | rst_hold.cpu_poreset  [ start_of_cluster + 2 ] << 6
                    | rst_hold.cpu_poreset  [ start_of_cluster + 3 ] << 7
                    | rst_hold.cluster_reset[ cluster_index_       ] << 8
                    ;
            }

        void set_rst_hold( unsigned cluster_index_, unsigned value_ )
            {
                set_rst_hold_cpu_reset    ( 0, cluster_index_, ((value_ >> 0) & 1) != 0 );
                set_rst_hold_cpu_reset    ( 1, cluster_index_, ((value_ >> 1) & 1) != 0 );
                set_rst_hold_cpu_reset    ( 2, cluster_index_, ((value_ >> 2) & 1) != 0 );
                set_rst_hold_cpu_reset    ( 3, cluster_index_, ((value_ >> 3) & 1) != 0 );
                set_rst_hold_cpu_poreset  ( 0, cluster_index_, ((value_ >> 4) & 1) != 0 );
                set_rst_hold_cpu_poreset  ( 1, cluster_index_, ((value_ >> 5) & 1) != 0 );
                set_rst_hold_cpu_poreset  ( 2, cluster_index_, ((value_ >> 6) & 1) != 0 );
                set_rst_hold_cpu_poreset  ( 3, cluster_index_, ((value_ >> 7) & 1) != 0 );
                set_rst_hold_cluster_reset( cluster_index_,    ((value_ >> 8) & 1) != 0 );
            }

        void set_sys_swreset( unsigned value_ )
            {
                if (((value_ >> 2) & 1) == 0)
                {
                    // unless bit 2 is set then we do absolutely nothing!
                    return;
                }

                if (((value_ >> 0) & 1) == 0)
                {
                    //
                    // System reset.
                    //
                    // We don't care about the rest of the register bits.
                    //
                    // NOTE that this is truly if it is 0 then system reset.
                    //
                    set_system_reset_req( true );
                }
                else
                {
                    //
                    // Cluster reset (in the sense that some cores will be reset)
                    //
                    if (((value_ >> 4) & 1) != 0)
                    {
                        // Primary (Cortex-A15) cluster
                        set_sys_swreset_cluster(
                            0,
                            (value_ >> 8) & 0x3,
                            (value_ >> 16) & 0xF
                            );
                    }
                    if (((value_ >> 5) & 1) != 0)
                    {
                        // Secondary (Cortex-A7) cluster
                        set_sys_swreset_cluster(
                            1,
                            (value_ >> 10) & 0x3,
                            (value_ >> 20) & 0xF
                            );
                    }
                }
            }

        //
        // CFG_W is the current value that will be applied at the next
        // reset, it is RW
        //
        unsigned get_cfg_w( unsigned cluster_index_ )
            {
                //
                // This is the value that was applied at the last reset.
                //
                unsigned value = 0;
                for (unsigned i = 0; i != 4; ++ i)
                {
                    cfg_t const c = get_current_cfg( i, cluster_index_ );
                    value |=
                        ( (c.cfgend * 0x001)
                          | (c.vinithi * 0x010)
                          | (c.teinit * 0x100)
                            ) << i;
                }
                value |= get_current_cluster_cfg( cluster_index_ ).iminlen << 12;
                value |= get_current_cluster_cfg( cluster_index_ ).cluster_id << 16;
                return value;
            }

        void set_cfg_w( unsigned cluster_index_, unsigned value_ )
            {
                for (unsigned i = 0; i != 4; ++ i)
                {
                    unsigned const v = value_ >> i;
                    set_cfg(
                        i,
                        cluster_index_,
                        (v & 0x001) != 0, // cfgend
                        (v & 0x010) != 0, // vinithi
                        (v & 0x100) != 0  // cfgte/teinit
                        );
                }
                set_cluster_cfg(
                    cluster_index_,
                    (value_ >> 16) & 0xF, // cluster id
                    (value_ >> 12) & 0x1  // iminlen
                    );
            }

        //
        // CFG_R is the value of the configuration that was applied at
        // the last reset.  It is read only.
        //
        unsigned get_cfg_r( unsigned cluster_index_ )
            {
                //
                // This is the value that was applied at the last reset.
                //
                unsigned value = 0;
                for (unsigned i = 0; i != 4; ++ i)
                {
                    cfg_t const c = get_cfg_at_last_reset( i, cluster_index_ );
                    value |=
                        ( (c.cfgend * 0x001)
                          | (c.vinithi * 0x010)
                          | (c.teinit * 0x100)
                            ) << i;
                }
                value |= get_cluster_cfg_at_last_reset( cluster_index_ ).iminlen << 12;
                value |= get_cluster_cfg_at_last_reset( cluster_index_ ).cluster_id << 16;
                return value;
            }


    private:
        void set_sys_swreset_cluster( unsigned cluster_index_,
                                      unsigned cluster_level_,
                                      unsigned bitmap_of_cores_ )
            {
                switch (cluster_level_)
                {

                case 0:
                {
                    // Individual core resets
                    for (unsigned i = 0; i != 4; ++ i)
                    {
                        if (((bitmap_of_cores_ >> i) & 1) != 0)
                        {
                            set_cpu_reset_req( i, cluster_index_, true );
                        }
                    }
                    break;
                }

                case 1:
                {
                    // Individual power on core resets
                    for (unsigned i = 0; i != 4; ++ i)
                    {
                        if (((bitmap_of_cores_ >> i) & 1) != 0)
                        {
                            set_cpu_poreset_req( i, cluster_index_, true );
                        }
                    }
                    break;
                }

                case 2:
                {
                    // Full cluster reset
                    set_cluster_reset_req( cluster_index_, true );
                    break;
                }

                case 3:
                {
                    // Reserved
                    ; // do nothing
                    break;
                }

                }
            }
    };



    //
    // Display the DCS_LEDs field in a vaguely pretty form.
    //
    inline std::ostream& display_dcs_leds( std::ostream& os_, uint32_t leds )
    {
        os_ << "DCS_LEDS [ ";

        unsigned i = 8;
        while (i != 0)
        {
            -- i;
            os_ << (leds >> i & 1 ? "O" : ".");
        }

        return os_ << " ]" << std::endl;
    }

    enum interrupt_sensitivity_t {
        level_sensitive = 0,
        edge_sensitive  = 1
    };


    class interrupt_generator_t
    {
    public:

        //
        // Declare the maximum number if interrupts we are prepared to handle.
        //
        static unsigned const absolute_max_number_of_interrupts = 128;

    private:

        unsigned              max_number_of_interrupts;

        interrupt_generator_t( interrupt_generator_t const& ); //disallow
        void operator =( interrupt_generator_t const& ); //disallow
    public:
        // ----------------------------------------------------------------------
        // Construction and initialisation
        // ----------------------------------------------------------------------
        interrupt_generator_t()
            : max_number_of_interrupts(0)
        {
        }

        void set_max_number_of_interrupts( unsigned max_number_of_interrupts_ )
        {
            assert( max_number_of_interrupts_ <= absolute_max_number_of_interrupts );
            max_number_of_interrupts
                = max_number_of_interrupts_ < absolute_max_number_of_interrupts
                ?  max_number_of_interrupts_
                : absolute_max_number_of_interrupts
                ;

            // DCSCB only allows this to be a multiple of two, no need
//            assert( max_number_of_interrupts_ % 32 == 0 );
        }

        static void tests();

        // ----------------------------------------------------------------------
        // Delta records describing what to change
        // ----------------------------------------------------------------------
        typedef unsigned interrupt_id_t;

        // This special value means that it is the timer control
        static interrupt_id_t const timer_id = ~interrupt_id_t(0);

        struct delta_t
        {
            delta_t( interrupt_id_t id_, uint32_t value_ )
                : id(id_),
                  value(value_)
            {
            }

            interrupt_id_t         id;      // interrupt_id or special value timer_id
            uint32_t               value;   // zero or one for an interrupt, 0 to turn timer off,
                                            // or the period to set the timer to.

            std::ostream& print( std::ostream& os_ ) const
            {
                if (id == timer_id)
                {
                    if (value == 0)
                        os_ << "timer-off";
                    else
                        os_ << "timer@" << value;
                }
                else
                {
                    os_ << "int_id" << id << ":" << value;
                }
                return os_;
            }
        };

        typedef std::vector<delta_t>  deltas_t;

        deltas_t                      deltas;

        std::ostringstream            unpredictable;

        std::pair< deltas_t::const_iterator,
                   deltas_t::const_iterator >
        get_deltas() const
        {
            return std::make_pair( deltas.begin(), deltas.end() );
        }

        bool are_there_deltasQ() const
        {
            return ! deltas.empty();
        }

        //! Indicate that all the deltas retrieved by get_deltas() have
        //  been applied.
        void deltas_have_been_processed()
        {
            deltas.clear();
        }

        // ----------------------------------------------------------------------
        // Useful print functions
        // ----------------------------------------------------------------------
        std::ostream& print( std::ostream& os_, std::string indent_ = "    " ) const
        {
            std::ostream::fmtflags   saved_flags = os_.flags();
            std::streamsize          saved_width = os_.width();
            char                     saved_fill  = os_.fill();

            os_ << indent_ << "INT_CTRL: "
                << std::hex << read_INT_CTRL() << std::dec << '-'
                << (is_interrupt_generation_enabled()
                    ? "enabled"
                    : "disabled")
                << (is_timer_interrupt_generation_enabled()
                    ? "-timer_enabled"
                    : "")
                ;

            os_ << "-int_freq:" << read_INT_FREQ() << "\n";
            os_ << indent_ << "INT_NUMBER: " << read_INT_NUMBER() << "\n";

            if ( ! deltas.empty() )
                os_ << indent_ << "Deltas:-\n";
            for (deltas_t::const_iterator i = deltas.begin();
                 i != deltas.end();
                 ++ i)
            {
                os_ << indent_ << "    ";
                i->print( os_ );
                os_ << "\n";
            }


            os_.fill ( saved_fill  );
            os_.width( saved_width );
            os_.flags( saved_flags );
            return os_;
        }

        std::ostream& print_config( std::ostream& os_, std::string indent_ = "    " ) const
        {
            std::ostream::fmtflags   saved_flags = os_.flags();
            std::streamsize          saved_width = os_.width();
            char                     saved_fill  = os_.fill();

            unsigned const read_int_number = read_INT_NUMBER();
            assert(
                read_int_number == int_number
                || (int_number == max_number_of_interrupts && read_int_number == 0xFF)
                );
            os_ << indent_ << "INT_SEQ:-\n";
            for (unsigned i = 0; i != max_number_of_interrupts; ++ i)
            {
                if (i % 8 == 0)
                    os_ << (i != 0 ? "\n" : "") << indent_ << "    " << std::setw(3) << i << ":";
                if (i < read_int_number)
                    os_ << '(' << std::setw(3) << int_seq[i] << ')';
                else
                    os_ << ' ' << std::setw(3) << int_seq[i] << ' ';
            }
            os_ << "\n";

            os_ << indent_ << "INT_TYPE:-\n" << indent_ << "    ";
            for (unsigned i = 0; i != max_number_of_interrupts; ++ i)
            {
                if (i % 8 == 0)
                {
                    if (i == 0)
                        ;
                    else if (i % 32 == 0)
                        os_ << "\n" << indent_ << "    ";
                    else
                        os_ << " ";
                    os_ << std::setw(3) << i << ": ";
                }
                os_ << (levels.get_level_of_interrupt(i) == edge_sensitive
                        ? 'E' : '.');
            }
            os_ << "\n";

            os_ << indent_ << "INT_TYPE: ";
            for (unsigned i = 0; i != 4; ++ i)
            {
                os_ << std::right << std::setw(8) << std::setfill('0') << std::hex
                    << read_INT_TYPE( i )
                    << std::dec
                    << " ";
            }
            os_ << "\n";

            os_.fill ( saved_fill  );
            os_.width( saved_width );
            os_.flags( saved_flags );
            return os_;
        }

        // ----------------------------------------------------------------------
        //                               reset()
        // ----------------------------------------------------------------------
        //
        // NOTE that those pins that have ids > max_number_of_interrupts - 1 will
        // not be driven.  This allows them to be connected to another source as
        // well if necessary.
        //
        void reset()
        {
            // INT_CTRL reset value is 0
            timer_en    = false;
            enabled     = false;

            timer_value = 0;

            int_freq    = 0;

            // INT_TYPE is 0
            levels.reset();

            int_number = 0;

            for (unsigned i = 0; i != absolute_max_number_of_interrupts; ++ i)
            {
                int_seq[i] = 0;
            }

            //
            // All output IRQ pins are low -- we setup all the deltas to produce appropriate
            // transactions.
            //
            deltas.clear();
            deltas.reserve( max_number_of_interrupts );
            for (interrupt_id_t i = 0; i != absolute_max_number_of_interrupts; ++ i)
            {
                // NOTE that we cannot use set_interrupt_pin() as we are not
                // guaranteed that interrupt_pins[] have valid values.
                if (i < max_number_of_interrupts)
                    deltas.push_back( delta_t( i, false ) );
                interrupt_pins[i] = false;
            }

            // Disable timer.
            deltas.push_back( delta_t( timer_id, 0 ) );
        }

        // ----------------------------------------------------------------------
        //                             Timer Callback
        // ----------------------------------------------------------------------
        //
        // The timer has gone off!
        //
        bool timer_callback()
        {
            // If the timer goes off and we are currently disabled then we
            // ignore the call back and ensure that it is disabled.  It should
            // have already been disabled.
            if ( ! is_timer_interrupt_generation_enabled() )
            {
                assert( timer_value == 0 );
                return ! deltas.empty();
            }

            // The timer going off is equivalent to writing to the INT_GENERATE
            // register.
            write_INT_GENERATE(1);

            set_timer( run_out_of_interrupts() ? 0 : int_freq + 1 );

            return ! deltas.empty();
        }

        // ----------------------------------------------------------------------
        //                               INT_CTRL
        // ----------------------------------------------------------------------

        uint32_t read_INT_CTRL() const
        {
            // at the time of writing, there is an INT_CTRL.FREQUENCY field and
            // also an INT_FREQ register.  We assume that the INT_FREQ.FREQUENCY
            // field is erroneous and ignore it.
            return uint32_t(timer_en) << 1
                |  uint32_t(enabled ) << 0
                ;
        }

        bool write_INT_CTRL( uint32_t value_ )
        {
            bool const was_timer_interrupt_generation_enabled
                = is_timer_interrupt_generation_enabled();
            timer_en = ((value_ >> 1) & 1) != 0;
            enabled  = ((value_ >> 0) & 1) != 0;

            if (is_timer_interrupt_generation_enabled())
            {
                if (was_timer_interrupt_generation_enabled)
                {
                    ; // assume nothing to do
                }
                else
                {
                    set_timer( int_freq + 1 );
                }
            }
            else
            {
                set_timer( 0 ); // disabled
            }

            if (is_interrupt_generation_enabled())
            {
                check_for_unpredictable();
            }

            return ! deltas.empty();
        }

        // ----------------------------------------------------------------------
        //                               INT_FREQ
        // ----------------------------------------------------------------------

        uint32_t read_INT_FREQ() const
        {
            return int_freq;
        }

        bool write_INT_FREQ( uint32_t value_ )
        {
            //
            // You _are_ allowed to write to the INT_FREQ register whilst
            // timer-generated interrupts are enabled and the counter
            // automatically zeros and restarts.
            //
            value_ &= 0x1ff;

            if (is_timer_interrupt_generation_enabled())
            {
                set_timer( value_ + 1 );
            }

            return ! deltas.empty();
        }

        // ----------------------------------------------------------------------
        //                               INT_TYPEn
        // ----------------------------------------------------------------------

        uint32_t read_INT_TYPE( unsigned index_ ) const
        {
            interrupt_id_t const start_id = index_ * 32;
            interrupt_id_t const end_id   = start_id + 31;

            // RAZ if we don't have enough interrupts.
            if (start_id >= max_number_of_interrupts)
                return 0;

            uint32_t ret = levels.get_reg(index_);

            interrupt_id_t const last_valid_interrupt = max_number_of_interrupts - 1;
            if (end_id > last_valid_interrupt)
            {
                // Deal with if we have a max_number_of_interrupts that isn't
                // a multiple of 32
                unsigned const bit_position_of_last_valid_interrupt
                    = last_valid_interrupt % 32;
                // so we want to preserve those bits and any lower
                uint32_t const mask_of_last_valid_interrupt
                    = uint32_t(1) << bit_position_of_last_valid_interrupt;
                ret &= ( mask_of_last_valid_interrupt
                         | (mask_of_last_valid_interrupt - 1)
                    )
                    ;

                assert( ((ret >> bit_position_of_last_valid_interrupt) >> 1) == 0 );
            }
            return ret;
        }

        bool write_INT_TYPE( unsigned index_, uint32_t value_ )
        {
            //
            // Although the DCSCB spec doesn't say it, but writing to this
            // register whilst it could potentially be being used is probably a
            // bad idea!
            //
            if (is_interrupt_generation_enabled())
            {
                unpredictable << "Write to INT_TYPE[" << index_ << "] = " << value_
                              << " whilst interrupt generation is enabled!\n";
            }
            else if (are_there_unacknowledged_interrupts())
            {
                unpredictable << "Write to INT_TYPE[" << index_ << "] = " << value_
                              << " whilst there are unacknowledged interrupts!\n";
            }

            levels.set_reg(index_, value_);

            return ! deltas.empty();
        }

        // ----------------------------------------------------------------------
        //                               INT_GENERATE
        // ----------------------------------------------------------------------


        //
        // A write to INT_GENERATE may produce transactions on the deltas list
        // so you should examine it after this call (if return true).
        //
        bool write_INT_GENERATE( uint32_t value_ )
        {
            if (is_interrupt_generation_enabled()
                && (value_ & 1) != 0
                && ! run_out_of_interrupts())
            {
                // Generate an interrupt if bit 0 is set.
                uint32_t const interrupt_id = int_seq[ int_number ];

                if (interrupt_pins[interrupt_id])
                {
                    unpredictable << "Write to INT_GENERATE triggered INT_SEQ[" << int_number << "] "
                                  << "which specifies interrupt " << interrupt_id
                                  << " which is already high!\n";

                    return ! deltas.empty();
                }

                if (interrupt_id >= max_number_of_interrupts)
                {
                    unpredictable << "Write to INT_GENERATE triggered INT_SEQ[" << int_number << "] "
                                  << "which specifies interrupt " << interrupt_id
                                  << " which doesn't exist (max_number_of_interrupts = "
                                  << max_number_of_interrupts << ")!\n";
                }

                ++ int_number;

                set_interrupt_pin( interrupt_id, true );
                if (levels.get_level_of_interrupt( interrupt_id ) == edge_sensitive)
                    set_interrupt_pin( interrupt_id, false );
            }

            return ! deltas.empty();
        }

        // ----------------------------------------------------------------------
        //                               INT_NUMBER
        // ----------------------------------------------------------------------

        uint32_t read_INT_NUMBER() const
        {
            return run_out_of_interrupts() ? 0xFF : int_number;
        }

        // ----------------------------------------------------------------------
        //                               INT_ACK
        // ----------------------------------------------------------------------

        // Return true if there are deltas to process.
        bool write_INT_ACK( uint32_t value_ )
        {
            if ((value_ & 1) != 0)
            {
                int_number = 0;
                for (interrupt_id_t i = 0; i != max_number_of_interrupts; ++ i)
                    set_interrupt_pin(i, false);

                // Immediately start timer generation again.
                if (is_timer_interrupt_generation_enabled()
                    && ! run_out_of_interrupts())
                {
                    set_timer( int_freq + 1 );
                }
            }

            return ! deltas.empty();
        }

        // ----------------------------------------------------------------------
        //                                 INT_SEQ
        // ----------------------------------------------------------------------

        uint32_t read_INT_SEQ( unsigned index_ ) const
        {
            assert( index_ < absolute_max_number_of_interrupts );
            if (index_ < max_number_of_interrupts)
            {
                return int_seq[ index_ ];
            }
            return 0;
        }

        // Return true if there are deltas to process.  Nominally, no changes to
        // the interrupt pins will occur.
        bool write_INT_SEQ( unsigned index_, uint32_t value_ )
        {
            assert( index_ < absolute_max_number_of_interrupts );
            int_seq[ index_ ] = value_ & (absolute_max_number_of_interrupts - 1);

            if (is_interrupt_generation_enabled())
            {
                unpredictable << "Write to INT_SEQ[" << index_ << "] = " << value_
                              << " whilst interrupt generation is enabled!\n";
            }
            else if (are_there_unacknowledged_interrupts())
            {
                unpredictable << "Write to INT_SEQ[" << index_ << "] = " << value_
                              << " whilst there are unacknowledged interrupts!\n";
            }

            return ! deltas.empty();
        }

    private:

        bool is_interrupt_generation_enabled() const
        {
            return enabled;
        }

        bool is_timer_interrupt_generation_enabled() const
        {
            return enabled && timer_en;
        }

        bool are_there_unacknowledged_interrupts() const
        {
            return int_number != 0;
        }

        bool run_out_of_interrupts() const
        {
            return int_number == max_number_of_interrupts;
        }

        void set_interrupt_pin( interrupt_id_t id_, bool value_ )
        {
            if (id_ < max_number_of_interrupts
                && interrupt_pins[id_] != value_)
            {
                deltas.push_back( delta_t( id_, value_ ) );
                interrupt_pins[id_] = value_;
            }
        }

        void set_timer( uint32_t value_ )
        {
            // Only produce a delta for the timer if it isn't disabled.
            //
            // The expectation is that a write to this will immediately
            // change the sleep-for time of the timer.  Thus writing to
            // it is not idempotent unless it is off (value_ == 0).
            if (value_ != 0
                || (value_ == 0 && timer_value != 0))
            {
                deltas.push_back( delta_t( timer_id, value_ ) );
                timer_value = value_;
            }
        }


        // INT_TYPEn register representation
        class levels_t
        {
            uint32_t int_type_reg[4];
        public:
            levels_t()
            {
                reset();
            }

            // The user can only set 32 bits at a time
            void set_reg( unsigned index_, uint32_t value_ )
            {
                assert( index_ < 4 );
                int_type_reg[index_] = value_;
            }

            uint32_t get_reg( unsigned index_ ) const
            {
                assert( index_ < 4 );
                return int_type_reg[index_];
            }

            interrupt_sensitivity_t get_level_of_interrupt( unsigned id_ ) const
            {
                return ((int_type_reg[ id_ / 32 ] >> (id_ % 32)) & 1) != 0
                    ? edge_sensitive
                    : level_sensitive
                    ;
            }

            void reset()
            {
                for (unsigned i = 0; i != 4; ++ i)
                    int_type_reg[i] = 0; // reset value is 0
            }
        };

        levels_t  levels;

        // INT_SEQ registers
        uint32_t  int_seq[absolute_max_number_of_interrupts];

        // INT_NUMBER register
        unsigned  int_number;

        // From INT_CTRL
        bool      enabled;
        bool      timer_en;

        uint32_t  timer_value;

        // From INT_FREQ
        uint32_t  int_freq;

        void check_for_unpredictable()
        {
            // If int_seq has been programmed with the same interrupt in more
            // than one register then the result is unpredictable!
            typedef std::vector< unsigned >   seen_t;
            seen_t                            seen( absolute_max_number_of_interrupts, ~0u);

            assert( seen.size() == absolute_max_number_of_interrupts );
            assert( seen[seen.size() - 1] == ~0u );

            for (unsigned i = 0; i != max_number_of_interrupts; ++ i)
            {
                interrupt_id_t const id = int_seq[i];
                if (seen[id] != ~0u)
                {
                    assert( int_seq[i] == int_seq[seen[id]] );
                    unpredictable << "INT_SEQ[" << i << "] = " << int_seq[i]
                                  << ", but also INT_SEQ[" << seen[id] << " ] = " << int_seq[seen[id]]
                                  << " and this is UNPREDICTABLE\n";
                }
                seen[id] = i;
            }
        }

        // This represents the level of the particular interrupt pin.
        bool interrupt_pins[absolute_max_number_of_interrupts];


    };

}

#endif

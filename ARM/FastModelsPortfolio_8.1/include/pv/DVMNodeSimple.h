/*
 * Copyright 2010 ARM Limited. All rights reserved.
 */

//
// Implements a simple DVM node that looks after up-stream and down-stream
// discovery.
//

#ifndef DVMNODESIMPLE_H
#define DVMNODESIMPLE_H

#include "pv/DVM.h"

#include <vector>
#include <iostream>
#include <iomanip>

#define DEBUG_DVM if (1) ; else
#undef HERE_DVM
#define HERE_DVM std::cerr << __FILE__ << ":" << __LINE__ << ": " << getInstanceName() << ": "

namespace DVM
{
    //
    // An exception that is used if we potentially detect an infinite loop where
    // a component has incorrectly sent DVM messages to masters that it already
    // has done or to a requestor.
    //
    class potential_infiniteness_exception
    {
        typedef std::vector< DVMNode* > backtrace_t;
        backtrace_t                     backtrace;
    public:

        void push_back( DVMNode* node_ );
        void print(std::ostream& os_) const;

    };

    template<typename IN_PORT,
             typename OUT_PORT>
    inline void forward_non_dvm_pvbus_behaviours_from_master_to_slave(
        IN_PORT&   in_,
        OUT_PORT&  out_,
        bool       siphon_off_rw = false
        )
    {
        //
        // If we wish to siphon off just the DVM messages and forward everything
        // else then there appears to be no simple way to do this.
        //
        // We have to instead forward everything that _isn't_ what we want!
        //
#define S(B) in_.B.connectTo(&out_.B)
        if ( ! siphon_off_rw )
        {
            S ( read                            );
            S ( write                           );
        }
        S ( debugRead                       );
        S ( debugWrite                      );
        S ( doReadAccess                    );
        S ( doWriteAccess                   );

        // Do _not_ propagate
        // S ( discoverDownstreamChildDVMNodes );

        // NOTE that we _don't_ bind them the other way round despite calls
        // going 'the other way'.
        S ( busMapChanging                 );
        S ( busMapChanged                  );

        // Do _not_ propagate
        // S ( discoverUpstreamParentDVMNodes );
#undef S
    }
}

//
// This is a simple extension to DVMNode that is useful for a range of purposes.
//
// Its principle features is that to use it then all you need to is to tell it
// about the upstream and downstream ports and assign each port to a set that
// can be used to enable/disable groups of ports.
//
// It also supports a form of infinite loop detection that is intended to help
// the user where ports have been connected incorrectly or the programmers has
// incorrectly sent messages to the wrong nodes.
//
// This is an abstract class, DVMNodeSimpleImpl implements the interface and you
// should derive from that.
//

class DVMNodeSimple : public DVMNode
{
public:  //
         // During init() name the node!  This makes any error messages a lot
         // easier to understand.
         //

    virtual void setInstanceName( std::string const& instance_name_ );

public:  //
         // If you have local DVM behaviour then implement this function, it is
         // guaranteed to be called before the message is propagated
         // up/downstream.  So if you alter the enabled port sets in it then it
         // will be obeyed.
         //

    virtual DVM::error_response_t handleLocalDVMMessage( DVMNode*, DVM::id_t, DVM::Message* );

public:  //
         // During init() then you must either manually bind the ports to this
         // node or you can use these convenience functions.
         //

    template< typename PORT_TYPE >
    void initDownstreamPort( PORT_TYPE& port_, DVM::id_t id_ = DVM::id_t() )
    {
        // A downstream port of this component must connect the upstream
        // discovery protocol to this node as it is the upstream node to
        // the downstream node!
        bind_method( port_,
                     discoverUpstreamParentDVMNodes,
                     &Thunk::discoverUpstreamParentDVMNodes,
                     makeThunk(id_) );
    }

    template< typename PORT_TYPE >
    void initUpstreamPort( PORT_TYPE& port_, DVM::id_t id_ = DVM::id_t() )
    {
        // An upstream port of this component must connect the downstream
        // discovery protocol to this node as it is the downstream node to
        // the upstream node!
        bind_method( port_,
                     discoverDownstreamChildDVMNodes,
                     &Thunk::discoverDownstreamChildDVMNodes,
                     makeThunk(id_) );
    }

public:  //
         // A component should, during reset(), first call reset() on the
         // DVMNode and then call each of these functions on every PVBus port
         // that it has, using the appropriate one for each direction.
         //
         // NOTE that DVM connections are not assumed to be symmetric -- just because
         // we got called from upstream doesn't necessarily mean we will propagate them
         // upstream.
         //
         // The _intent_ of ACE is that all partners should be symmetric in their abilities
         // but we don't make that assumption.
         //

    // Each port can belong to one or more sets.  If its (id_ & enabled_port_sets) !=
    // 0 then DVM messages will be routed along those ports.
    typedef uint32_t port_set_t;

    // The enabled port sets.  By default, all ports are enabled.
    port_set_t enabled_port_sets;

    template<typename DownstreamPort>
    void resetDownstreamPort( DownstreamPort& port_, port_set_t port_set_ = ~port_set_t() )
    {
        if (port_.discoverDownstreamChildDVMNodes.implemented())
        {
            try
            {
                DEBUG_DVM HERE_DVM << "discovering down-stream ports\n";
                port_.discoverDownstreamChildDVMNodes( getDownstreamVisitor(port_set_) );
            }
            catch (DVM::potential_infiniteness_exception& e_)
            {
                e_.push_back(this);
                if (popDownstreamVisitorId(port_set_))
                {
                    throw;
                }
                e_.print(std::cerr); // must do better!
            }
            catch (...)
            {
                popDownstreamVisitorId(port_set_);
                throw;
            }
            popDownstreamVisitorId(port_set_);
        }
    }

    template<typename UpstreamPort>
    void resetUpstreamPort( UpstreamPort& port_, port_set_t port_set_ = ~port_set_t() )
    {
        if (port_.discoverUpstreamParentDVMNodes.implemented())
        {
            try
            {
                DEBUG_DVM HERE_DVM << "discovering up-stream ports\n";
                port_.discoverUpstreamParentDVMNodes( getUpstreamVisitor(port_set_) );
            }
            catch (DVM::potential_infiniteness_exception& e_)
            {
                e_.push_back(this);
                if (popUpstreamVisitorId(port_set_))
                {
                    throw;
                }
                e_.print(std::cerr); // must do better!
            }
            catch (...)
            {
                popUpstreamVisitorId(port_set_);
                throw;
            }
            popUpstreamVisitorId(port_set_);
        }
    }

    virtual std::string const& getInstanceName() const;

public:  /*!
          * In order to send a DVM Message then you can used this interface.
          *
          * It uses the current value of enabled_port_sets.
          *
          * You may exclude a single node from being sent a message.  This is
          * generally useful only if you have overridden handleUpstreamDVMMessage()
          * or handleDownstreamDVMMessage() and are specifically removing a port.
          *
          * NOTE with care that this does _not_ send it to the current node.
          *
          */

    virtual DVM::error_response_t sendDVMMessageToAllInEnabledSet(
        DVM::Message*    message_,
        DVMNode*         exclude_port_ = 0
        ) = 0;

protected:

    DVMNodeSimple( std::string const& instance_name_ = "Unknown");

    DVMNodeSimple( DVMNodeSimple const& ); // disallow
    void operator =( DVMNodeSimple const& ); // disallow

    virtual DVM::DownstreamVisitor* getDownstreamVisitor(port_set_t port_set_) = 0;
    virtual DVM::UpstreamVisitor*   getUpstreamVisitor  (port_set_t port_set_) = 0;

    virtual bool popDownstreamVisitorId(port_set_t port_set_) = 0;
    virtual bool popUpstreamVisitorId(port_set_t port_set_) = 0;

    virtual ~DVMNodeSimple();

private:

    std::string instance_name;
};

//
// This is an implementation of the DVMNodeSimple interface.
//
class DVMNodeSimpleImpl : public DVMNodeSimple
{
    typedef DVMNodeSimple base;

    //
    // base_stream_t is a base class of a container that holds either the
    // immediately connected DVM-aware upstream or downstream DVMNodes.
    //

    struct record_t
    {
        record_t(
            DVMNode*      node_     = 0,
            port_set_t    port_set_ = 0,
            DVM::id_t     id_       = DVM::id_t()
            );

        DVMNode*      node;
        port_set_t    port_set;
        DVM::id_t     id;

        bool matches( DVMNode* node_, DVM::id_t id_ ) const
        {
            return node == node_ && id == id_;
        }
    };


    class undired_base_stream_t : public std::vector< record_t >
    {

        std::vector< port_set_t > current_id_stack;
        unsigned                  max_count;
        std::string               default_instance_name;
    protected:

        DVMNode*                  parent;
        undired_base_stream_t();

        iterator find( DVMNode* node_, DVM::id_t id_ );

    public:
        std::string const& getInstanceName() const;

        void print(std::ostream& os_, std::string const& indent_) const;
        void set_parent( DVMNode* parent_ );
        void register_dvm_node( DVMNode* node_, DVM::id_t id_ );
        void push_id( port_set_t id_ );
        void pop_id( port_set_t id_ );
        bool is_id_stack_empty() const;
    };

    enum dir_t { up, down };

    template< dir_t dir >
    class base_stream_t : public undired_base_stream_t
    {
        unsigned   depth;
        unsigned   max_depth;
    public:

        base_stream_t()
            : depth(0),
              max_depth(2)
        {
        }

        //
        // Send a DVM message to every port in the specified enabled set except
        // for the port specified.  This allows us to receive a message from
        // upsteam and bounce it up-stream to every port but the one that sent
        // it to us.
        //
        DVM::error_response_t send_dvm_message_to_all_in_set_except_for(
            DVM::Message*    message_,
            port_set_t       enabled_set_,
            DVMNode*         exclude_port_ = 0
            )
        {
            DVM::error_response_t  ret = DVM::ok;
            try
            {
                if (++ depth == max_depth)
                {
                    throw DVM::potential_infiniteness_exception();
                }

                iterator i = begin();
                while (i != end())
                {
                    if (i->node != exclude_port_
                        && (i->port_set & enabled_set_) != 0)
                    {
                        DVM::error_response_t resp
                            = dir == up
                            ? i->node->handleUpstreamDVMMessage( parent, i->id, message_ )
                            : i->node->handleDownstreamDVMMessage( parent, i->id, message_ )
                            ;
                        ret = combine_error_responses(ret, resp);
                    }

                    ++ i;
                }

                -- depth;
            }
            catch (DVM::potential_infiniteness_exception& e_)
            {
                e_.push_back( parent );
                if (-- depth != 0)
                {
                    throw;
                }
                e_.print(std::cerr); // should do better!
            }
            catch (...)
            {
                -- depth;
                throw;
            }
            return ret;
        }
    };

    class upstream_t : public base_stream_t<up>, public DVM::UpstreamVisitor
    {
    private:
        virtual void registerDVMNode( DVMNode* node_, DVM::id_t id_ )
        {
            DEBUG_DVM HERE_DVM << "discovered an upstream node " << node_->getInstanceName() << " received via a DVM::UpstreamVisitor with " << id_ << "\n";
            register_dvm_node(node_, id_);
        }
    };

    class downstream_t : public base_stream_t<down>, public DVM::DownstreamVisitor
    {
    private:
        virtual void registerDVMNode( DVMNode* node_, DVM::id_t id_ )
        {
            DEBUG_DVM HERE_DVM << "discovered a downstream node " << node_->getInstanceName() << " received via a DVM::DownstreamVisitor with " << id_ << "\n";
            register_dvm_node(node_, id_);
        }
    };

    upstream_t        upstream;
    downstream_t      downstream;

    virtual DVM::DownstreamVisitor* getDownstreamVisitor(port_set_t id_);
    virtual DVM::UpstreamVisitor* getUpstreamVisitor(port_set_t id_);
    virtual bool popDownstreamVisitorId(port_set_t id_);
    virtual bool popUpstreamVisitorId(port_set_t id_);

public:
    virtual void reset();

    DVMNodeSimpleImpl( std::string const& instance_name_ = "Unknown" );
    ~DVMNodeSimpleImpl();

    virtual void print(std::ostream& os_, std::string const& indent_ = "    ") const;

public:

    //
    // This is a discovery request from an upstream node to see if we handle
    // DVM.
    //
    virtual void discoverDownstreamChildDVMNodes( DVM::DownstreamVisitor* parent_, DVM::id_t id_ );
    //
    // This is a discovery request from a downstream node to see if we handle
    // DVM.
    //
    virtual void discoverUpstreamParentDVMNodes( DVM::UpstreamVisitor* child_, DVM::id_t id_ );

    virtual DVM::error_response_t handleUpstreamDVMMessage(DVMNode* from_, DVM::id_t id_, DVM::Message* message_);
    virtual DVM::error_response_t handleDownstreamDVMMessage(DVMNode* from_, DVM::id_t id_, DVM::Message* message_);

private:

    typedef std::vector< Thunk* > thunks_t;
    thunks_t                      thunks;

public:

    virtual DVM::error_response_t sendDVMMessageToAllInEnabledSet(
        DVM::Message*    message_,
        DVMNode*         exclude_port_ = 0
        );

    using base::makeThunk;

    virtual Thunk* makeThunk( DVM::id_t id_ );

};

inline std::ostream& operator << (std::ostream& os_, DVMNodeSimpleImpl const& t_)
{
    t_.print(os_);
    return os_;
}

#endif

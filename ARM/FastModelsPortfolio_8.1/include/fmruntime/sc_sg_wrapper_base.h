/*
 * SC: sc_sg_wrapper_base.h - SystemGenerator sub-system SystemC wrapper base
 *                            class.
 *
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 * Copyright 2007 ARM Limited.
 * All rights reserved.
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 */

#ifndef SC_SG_WRAPPER_BASE__H
#define SC_SG_WRAPPER_BASE__H

/* Includes */
#include <string>
#include <map>
#include "sc_sg_callbacks.h"

/* Externs */
/*
 * Messages.
 */
extern const char ARM_ID_SYS_GEN_DEPRECATION[];
extern const char ARM_ID_DEBUG_AFTER_START[];


void sc_sg_break_quantum(double /* intr_time */ = 0);


/* Namespaces */

/*
 * SystemGenerator framework.
 */
namespace sg {

  /* Datatypes */

  /*
   * Component factory base class.
   */
  class ComponentFactory;

  /*
   * Port base class.
   */
  class Port;
};
namespace eslapi
{
    class CAInterface;
}

/*
 * SystemC framework for SystemGenerator.
 */
namespace sc {

  /* Datatypes */

  /*
   * Simulation engine.
   */
  class sc_sg_simengine;
    
  /*
   * SystemGenerator sub-system SystemC wrapper base class.
   */
  class sc_sg_wrapper_base {

    /* Construction */
    public:
      sc_sg_wrapper_base(const std::string &,
                         sg::ComponentFactory *,
                         unsigned long long /* freq */ = 1,
                         bool /* debug */ = false);
      virtual ~sc_sg_wrapper_base();

    /* Accessors */
      void set_frequency(unsigned long long);
      unsigned long long get_frequency() const;
      void set_quantum(unsigned long);
      void set_quantum_seconds(double /* interval */);
      void set_global_quantum(double /* interval */);
      unsigned long get_quantum() const;
      double get_quantum_seconds() const;
      double get_global_quantum() const;
      void break_quantum_seconds(double /* intr_time */ = 0);
      void load_application_file(const std::string & /* instance_name */,
                                 const std::string & /* application_filename */);
      /* Unsupported private function: delay app load until sim is running
       * rather than doing it in start_of_simulation callback.
       */
      void defer_appload_to_sim_start(bool /* do_defer */ = true);
      /* Unsupported private function: allow the model to proxy CADI calls
       * across to the simulation thread
       */
      void set_cadi_scthread_context(bool = false);
      void enable_trace(const std::string & /* instance_name */);
      unsigned long long get_ticks_count();
      unsigned long long get_cycle_count();
      /* Deprecated: use get_ticks_count() instead! */
      eslapi::CAInterface *getGlobalInterface();

      static sc_sg_wrapper_base *get_instance();

    /* Instance parameters handling */
      bool set_parameter(const std::string &, const std::string &);
      bool set_parameter(const std::string &, const char *);
      bool set_parameter(const std::string &, bool);
      bool set_parameter(const std::string &, int);
      bool set_parameter(const std::string &, unsigned int);
      bool set_parameter(const std::string &, long long);
      bool set_parameter(const std::string &, unsigned long long);
      std::string get_parameter(const std::string &) const;
      std::map<std::string, std::string> get_parameter_list() const;

    /* Callbacks */
      void set_callbacks(sc_sg_callbacks *);
        const sc_sg_callbacks * get_callbacks() const;

    /* Simuation control */
      void set_debug_mode(bool /* cadi_server */ = true,
                          bool /* start_simulation */ = false,
                          bool /* cadi_log */ = false,
                          bool /* debug */ = false);
      void set_run_once(bool /* once */ = true);
      bool get_run_once() const;
    /* Ports handling */
      sg::Port & find_sg_port(const std::string &);

      void reset(unsigned int);
      void initControlAndCADI();

    /* Implementation */
  protected:
      /* sc_module like */
  public:
      void before_end_of_elaboration();
      void end_of_elaboration();
      void start_of_simulation();
      void end_of_simulation();
  protected:
      /* Member variables */
      sc_sg_simengine * m_eng;  /* Simulation engine */
      static sc_sg_wrapper_base *m_instance;


      /* Helpers */
      void run();   /* Runner thread */

      bool publish_master_port(const std::string &, sg::Port &);
      bool publish_slave_port(const std::string &, sg::Port &);
        /* DE532465: Ports are not published.
         * When they should be! */
      };

  /* Functions */
  inline
  bool sc_sg_wrapper_base::set_parameter(const std::string & param,
                                         const char * name) {
    const std::string tmp(name);

    return (set_parameter(param, tmp));
  }
};

#endif  /* defined(SC_SG_WRAPPER_BASE__H) */

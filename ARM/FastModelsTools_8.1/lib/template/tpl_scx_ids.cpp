/*
 * @SOURCE_HEADER@
 *
 * @This_is_a_template_file___Feel_free_to_edit@
 *
 * Copyright 2011-2012 ARM Limited.
 *
 * All rights reserved.
 */

/* Includes */
#include "GlobalDefs.h"

#include <systemc>
#include <cstdio>
#include <cstdlib>

#include <scx/scx_ids.h>

/* Namespaces */

/*
 * SystemC eXport support namespace.
 */
namespace scx {

/* Globals & functions */

/*
 * Messages identifiers definition.
 *
 * Message identifiers from Fast Models are in the range 1000-1999.
 */
#define DEFINE_MSG(id, n) { \
            (id), \
            0u, {0u},       /* actions */ \
            0u, {0u}, 0u,   /* limits */ \
            0u, {0u}, NULL, /* call counters */ \
            n \
        },
static sc_core::sc_msg_def defs[] = {
    DEFINE_MSG(SCX_ID_FM_DEPRECATION,           1000)
    DEFINE_MSG(SCX_ID_INCOMPATIBLE_PTHREADS,    1001)
    DEFINE_MSG(SCX_ID_INITIALIZE_NOT_CALLED,    1002)
    DEFINE_MSG(SCX_ID_INTERNAL_ERROR,           1003)
    DEFINE_MSG(SCX_ID_EVS_EXISTS,               1004)
    DEFINE_MSG(SCX_ID_INVALID_FACTORY,          1005)
    DEFINE_MSG(SCX_ID_LICENSE_MISSING,          1006)
    DEFINE_MSG(SCX_ID_INSTANTIATE_FAILED,       1007)
    DEFINE_MSG(SCX_ID_INSTANCE_NOT_FOUND,       1008)
    DEFINE_MSG(SCX_ID_INVALID_SIMCONTROL,       1009)
    DEFINE_MSG(SCX_ID_GET_REPORT_HANDLER,       1010)
    DEFINE_MSG(SCX_ID_GET_SCHEDULER,            1011)
    DEFINE_MSG(SCX_ID_LOAD_PLUGINS,             1012)
    DEFINE_MSG(SCX_ID_REGISTER_PLUGINS,         1013)
    DEFINE_MSG(SCX_ID_ADD_CALLBACK,             1014)
    DEFINE_MSG(SCX_ID_LOAD_APPLICATION,         1015)
    DEFINE_MSG(SCX_ID_LOAD_DATA,                1016)
};
static sc_core::sc_report_handler::msg_def_items msgs = {
    defs, sizeof(defs) / sizeof(* defs), false, 0
};

/*
 * Message identifiers registration.
 */
struct forty_two {
    forty_two() {
        sc_core::sc_report_handler::add_static_msg_types(& msgs);

        /* Process any environmental overrides */
        const char * deprecation_warn = std::getenv("FM_SCX_DEPRECATION_WARNINGS");

        if ((deprecation_warn != NULL) && (std::atoi(deprecation_warn) <= 0)) {
            sc_core::sc_report_handler::set_actions(SCX_ID_FM_DEPRECATION,
                                                    sc_core::SC_DO_NOTHING);
        }
    };
    ~forty_two() {

        /* If deprecation warnings were issued tell user how to turn them off */
        if (sc_core::sc_report_handler::get_count(SCX_ID_FM_DEPRECATION) > 0)
        {
            SC_REPORT_INFO(SCX_ID_FM_DEPRECATION,
                            "You can turn off warnings about\n"
                            "              Fast Models deprecated features by "
                            "placing this method call\n"
                            "              as the first statement in your "
                            "sc_main() function:\n\n  "
                            "sc_core::sc_report_handler::set_actions("
                            "SCX_ID_FM_DEPRECATION, SC_DO_NOTHING);\n\n");
        }
    };
};

static forty_two init_and_term;

}   /* namespace scx */

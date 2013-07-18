/*!
 *  \file   SystemTraceInterface_v1.h
 *  \brief  Version 1 SystemTraceInterface class.
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  ModelTraceInterface.h header should be included instead.
 */

#ifndef MTI_SYSTEMTRACEINTERFACE_V1_H
#define MTI_SYSTEMTRACEINTERFACE_V1_H

#include "eslapi/CAInterface.h"

#include <stddef.h> // size_t
#include <utility>  // std::pair

namespace MTI
{
    namespace v1
    {
        /// Class encapsulating all trace components of a system
        /**
         * This class is used to query which of a system's components
         * provide trace sources. Components can be enumerated using
         * the GetNumOfTraceComponents(),
         * GetComponentTracePath(TraceComponentIndex) and
         * GetComponentTrace(TraceComponentIndex) methods, or a
         * component with known name can be requested using
         * GetComponentTrace(const char *).
         */

        class SystemTraceInterface :
            public eslapi::CAInterface
        {
        public: // types

            /** This type is used to index the components which provide
             * a ComponentTraceInterface. */
            typedef int TraceComponentIndex;

        public:
            /// Static helper method to return the interface name for the 
            /// CAInterface.
            static eslapi::if_name_t IFNAME() { return "SystemTraceInterface1"; }
        
            /// Static helper method to return the current interface revision 
            /// for CAInterface.
            static eslapi::if_rev_t IFREVISION() { return 0; }

        public:
            /**
             * Return the number of components providing trace. The
             * components can be accessed with indices 0 to
             * GetNumOfTraceComponents()-1.
             */
            virtual TraceComponentIndex GetNumOfTraceComponents() const = 0;

            /**
             * Return the path of a component providing trace.
             *
             * \param tci This must be between 0 and
             * GetNumOfTraceComponents()-1.
             *
             * \return Returns a string containing the path of the
             * component. 0 will be returned if an illegal value for
             * tci is given. The string returned lives as long as the
             * simulation.
             */
            virtual const char *GetComponentTracePath(TraceComponentIndex tci) const = 0;

            /**
             * Get pointer to the ComponentTraceInterface class of a component by index.
             * 
             * \param tci This must be between 0 and GetNumOfTraceComponents()-1. 
             *
             * \return Returns a pointer to a ComponentTraceInterface
             * instance. If an illegal tci is given then a 0 pointer is
             * returned. The pointer returned is a CAInterface
             * pointer. The ObtainInterface method must be used to
             * convert it into a pointer of type
             * TraceComponentInterface. The object returned will live
             * as long as the simulation it belongs to.
             */
            virtual eslapi::CAInterface *GetComponentTrace(TraceComponentIndex tci) const = 0;

            /**
             * Get a pointer to the ComponentTraceInterface class of a component by name.
             * 
             * \param component_path The should be the pathname of a
             * component providing trace sources as returned by
             * GetComponentTracePath().
             *
             * \return Returns a pointer to a ComponentTraceInterface
             * instance. Returns 0 if no component with that pathname
             * exists, or if the component does not provide
             * trace sources. The pointer returned is a CAInterface
             * pointer. The ObtainInterface method must be used to
             * convert it into a pointer of type
             * TraceComponentInterface. The object returned will live
             * as long as the simulation it belongs to.
             */
            virtual eslapi::CAInterface *GetComponentTrace(const char *component_path) const = 0;
        };
    } // namespace v1

} // namespace MTI

#endif

// end of file SystemTraceInterface_v1.h

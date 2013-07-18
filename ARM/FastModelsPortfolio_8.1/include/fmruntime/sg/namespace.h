/*!
 * \file    namespace.h
 * \brief   Set up namespace alias
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Unless KEEP_ARM_NAMESPACE is predefined, simplify identifier names
 * by importing namespace sg into namespace sg.
 */

#ifndef ARM_SG_NAMESPACE_H
#define ARM_SG_NAMESPACE_H

#ifndef KEEP_ARM_NAMESPACE

//! Declare existence of namespace sg and ARM::fs
namespace ARM { 
    namespace fs { }
}

namespace fs {
    //! Legacy support for System Generator objects in fs:: namespace.
    using namespace ARM::fs;
}
#endif // KEEP_ARM_NAMESPACE

#endif // ARM_SG_NAMESPACE_H

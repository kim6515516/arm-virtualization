 /*!
 * \file    PVAccessWidth.h
 * \brief   Type definition for pv::AccessWidth
 * \date    Copyright 2005-2009 ARM Limited. All rights reserved.
 *
 */

#ifndef PVBUSACCESSWIDTH_H
#define PVBUSACCESSWIDTH_H

namespace pv {

/*! Define an enumeration of access width specifiers, having values
 *  representing lg2 width in bytes.
 */
enum AccessWidth {
    ACCESS_8_BITS = 0,
    ACCESS_16_BITS = 1,
    ACCESS_32_BITS = 2,
    ACCESS_64_BITS = 3,
    ACCESS_128_BITS = 4,
    ACCESS_INVALID = -1 //! Used to request no data transfer (just prefetch)
};

/*! Helper function to convert a byte-width to an AccessWidth. */
AccessWidth byteWidthToAccessWidth(int byte_width);

/*! Helper function to convert an AccessWidth to a byte-width. */
int accessWidthToByteWidth(AccessWidth);

}

#endif

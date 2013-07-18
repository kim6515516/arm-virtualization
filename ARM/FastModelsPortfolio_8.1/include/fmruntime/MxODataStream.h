/*!
 * \file    MxODataStream.h
 * \date    Copyright ARM Limited 2000-2004 All Rights Reserved.
 *
 */

#ifndef MXODATASTREAM_H
#define MXODATASTREAM_H

#include <eslapi/eslapi_stdint.h>

#include <iostream>

class MxODataStream                // data stream class
{
public:
    MxODataStream( std::ostream * );
    virtual ~MxODataStream();

    enum ByteOrder { BigEndian, LittleEndian };
    int         byteOrder()    const;
    void     setByteOrder( int );

    MxODataStream &operator<<( int8_t i );
    MxODataStream &operator<<( uint8_t i );
    MxODataStream &operator<<( int16_t i );
    MxODataStream &operator<<( uint16_t i );
    MxODataStream &operator<<( int32_t i );
    MxODataStream &operator<<( uint32_t i );
    MxODataStream &operator<<( int64_t i );
    MxODataStream &operator<<( uint64_t i );

    MxODataStream &operator<<( bool b );
    MxODataStream &operator<<( float f );
    MxODataStream &operator<<( double f );
    MxODataStream &operator<<( const char *str );

    MxODataStream &writeBytes( const char *, unsigned int len );
    MxODataStream &writeRawBytes( const char *, unsigned int len );

protected:
    std::ostream    *dev;
    int                 byteorder;
    int             ver;
    bool             noswap;
    bool            printable;

private:    // Disabled copy constructor and operator=
    MxODataStream( const MxODataStream & );
    MxODataStream &operator=( const MxODataStream & );
};


/*****************************************************************************
  MxODataStream inline functions
 *****************************************************************************/

inline int MxODataStream::byteOrder() const
{ return byteorder; }

inline MxODataStream &MxODataStream::operator<<( uint8_t i )
{ return *this << (int8_t)i; }

inline MxODataStream &MxODataStream::operator<<( uint16_t i )
{ return *this << (int16_t)i; }

inline MxODataStream &MxODataStream::operator<<( uint32_t i )
{ return *this << (int32_t)i; }

inline MxODataStream &MxODataStream::operator<<( uint64_t i )
{ return *this << (int64_t)i; }

inline MxODataStream &MxODataStream::operator<<( bool b )
{ return *this << ((int8_t)( b ? 1 : 0 )); }

#endif // MXODATASTREAM_H

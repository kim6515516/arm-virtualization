/*!
 * \file    MxIDataStream.h
 * \date    Copyright ARM Limited 2004-2005 All Rights Reserved.
 *
 */

#ifndef MXIDATASTREAM_H
#define MXIDATASTREAM_H

#include <eslapi/eslapi_stdint.h>

#include <iostream>

class  MxIDataStream
{
public:
    MxIDataStream( std::istream * );
    virtual ~MxIDataStream();

    bool     atEnd() const;
    bool     eof() const;

    enum ByteOrder { BigEndian, LittleEndian };
    int         byteOrder()    const;
    void     setByteOrder( int );

    MxIDataStream &operator>>( int8_t &i );
    MxIDataStream &operator>>( uint8_t &i );
    MxIDataStream &operator>>( int16_t &i );
    MxIDataStream &operator>>( uint16_t &i );
    MxIDataStream &operator>>( int32_t &i );
    MxIDataStream &operator>>( uint32_t &i );
    MxIDataStream &operator>>( int64_t &i );
    MxIDataStream &operator>>( uint64_t &i );

    MxIDataStream &operator>>( bool &b );
    MxIDataStream &operator>>( float &f );
    MxIDataStream &operator>>( double &f );
    MxIDataStream &operator>>( char *&str );

    MxIDataStream &readBytes( char *&, unsigned int &len );
    MxIDataStream &readRawBytes( char *, unsigned int len );
    
protected:
    std::istream    *dev;
    int                 byteorder;
    int                ver;
    bool             noswap;
    bool            printable;

private:    // Disabled copy constructor and operator=
    MxIDataStream( const MxIDataStream & );
    MxIDataStream &operator=( const MxIDataStream & );
};


/*****************************************************************************
  MxIDataStream inline functions
 *****************************************************************************/

inline bool MxIDataStream::atEnd() const
{ return dev->eof() ? true : false; }

inline bool MxIDataStream::eof() const
{ return atEnd(); }

inline int MxIDataStream::byteOrder() const
{ return byteorder; }

inline MxIDataStream &MxIDataStream::operator>>( uint8_t &i )
{ return *this >> (int8_t&)i; }

inline MxIDataStream &MxIDataStream::operator>>( uint16_t &i )
{ return *this >> (int16_t&)i; }

inline MxIDataStream &MxIDataStream::operator>>( uint32_t &i )
{ return *this >> (int32_t&)i; }

inline MxIDataStream &MxIDataStream::operator>>( uint64_t &i )
{ return *this >> (int64_t&)i; }

#endif // #ifndef MXIDATASTREAM_H 

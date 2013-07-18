/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   StreamIO.h
 *  \brief  Abstraction between differences between extensions to stream IO.
 *  \date   Copyright ARM Limited 2013 All Rights Reserved.
 *  
 *  This file is not part of a stable public API and it may
 *  change without notice.
 *
 *  There are two interesting extensions to stream IO available under SUS and
 *  under the MS CRT. These are:
 *  - Unlocked IO: This performs IO without locking the stream first resulting
 *  in a substantial performance increase for streams which are known to only
 *  be accessed by a single thread.
 *  - 64 bit offsets: These provide a set of functions which can be used to
 *  manipulate files larger than 2GB. Under Windows these must be used because
 *  off_t does not exist to be redefined. Windows provides a set of functions
 *  suffixed with "i64" which use an __int64. GLIBC instead provides a set
 *  of functions suffixed with "64" which use an off64_t.
 * 
 *  For 32 bit Linux targets defining _FILE_OFFSET_BITS=64 is undesirable in
 *  this specific instance because:
 *  - A bug in fixincs under GCC 4.4.x on RHEL5 which prevents '64' suffixed
 *    functions from being prototyped correctly.
 *  - The possibility of LFS unaware user code that expects off_t to be 32 bits
 *    existing within the simulation.
 *
 *  This file attempts to provide something which looks like the SUS
 *  transitional LFS API on both platforms along with unlocked versions.
 *  Differences in implementation are noted on a base by case basis.
 *
 *  The following functions are not implemented as no direct equivalents exist
 *  in the MS CRT.
 *  fstatvfs64(), ftw64(),lockf64(),lstat64(),nftw64(),readdir64(),truncate64()
 *  
 *  The following functions do not have an unlocked version under the MS CRT
 *  and the locked version is called instead.
 *  fclearerr(), feof(), ferror(), fileno(), fgets(), fputs()
 *  
 *  The following functions do not have an unlocked version under GLIBC but do
 *  have a MS CRT equivalent. Under GLIBC we call the locked version instead.
 *  fseeko64, ftello64
 */

#ifndef INCLUDED_STREAMIO_H
#define INCLUDED_STREAMIO_H

#include "sg/PreInc.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(__unix__)
    #include <unistd.h>
#endif

#if defined(_MSC_VER)
    #include <io.h>
#endif

#include "sg/PostInc.h"


#if defined(_MSC_VER)
    typedef  __int64 sg_off64_t;
    // Under Windows the normal fpos_t can cope with large files.
    typedef fpos_t sg_fpos64_t;
    typedef struct __stat64 sg_stat64_t;
    typedef struct __stat64 sg_fstat64_t;
    typedef int sg_mode_t;
#elif defined(__unix__) && defined(_LARGEFILE64_SOURCE)
    typedef off64_t sg_off64_t;
    typedef fpos64_t sg_fpos64_t;
    typedef struct stat64 sg_stat64_t;
    typedef struct stat64 sg_fstat64_t;
    typedef mode_t sg_mode_t;
#else
    #error "Large files are not supported on this platform"
#endif

// Convenience stat/access macros that are defined on POSIX, but not Windows
#if defined(_MSC_VER)
    #define SG_S_ISREG(f) (((f) & S_IFMT) == S_IFREG)
    #define SG_F_OK       0
    #define SG_W_OK       2
    #define SG_R_OK       4
#else
    #define SG_S_ISREG S_ISREG
    #define SG_F_OK    F_OK
    #define SG_W_OK    W_OK
    #define SG_R_OK    R_OK
#endif

inline int sg_access(const char *__restrict file,
                sg_mode_t mode)
{
#if _MSC_VER
    return _access(file, mode);
#else
    return access(file, mode);
#endif
}

// Large file functions

inline int sg_fgetpos64(FILE *__restrict stream, sg_fpos64_t *__restrict pos)
{
#if _MSC_VER
    return fgetpos(stream, pos);
#else
    return fgetpos64(stream, pos);
#endif
}


inline FILE *sg_freopen64(const char *__restrict filename,
                    const char *__restrict modes,
                    FILE *__restrict stream)
{
#if _MSC_VER
    return freopen(filename, modes, stream);
#else
    return freopen64(filename, modes, stream);
#endif
}

inline int sg_fsetpos64(FILE *stream, const sg_fpos64_t *pos)
{
#if _MSC_VER
    return fsetpos(stream, pos);
#else
    return fsetpos64(stream, pos);
#endif
}


inline FILE *sg_tmpfile64(void)
{
#if _MSC_VER
    return tmpfile();
#else
    return tmpfile64();
#endif
}


inline FILE *sg_fopen64(const char *__restrict filename,
                 const char *__restrict modes)
{
#if _MSC_VER
    return fopen(filename, modes);
#else
    return fopen64(filename, modes);
#endif
}


inline int sg_fseeko64(FILE *stream, sg_off64_t offset, int whence)
{
#if _MSC_VER
    return _fseeki64(stream, offset, whence);
#else
    return fseeko64(stream, offset, whence);
#endif
}


inline sg_off64_t  sg_ftello64(FILE *stream)
{
#if _MSC_VER
    return _ftelli64(stream);
#else
    return ftello64(stream);
#endif
}


inline int sg_creat64(const char *file, sg_mode_t mode)
{
#if _MSC_VER
    return _open(file,_O_CREAT|_O_WRONLY|_O_TRUNC, mode);
#else
    return creat64(file, mode);
#endif
}


inline int sg_stat64(const char *__restrict file,
                sg_stat64_t *__restrict buf)
{
#if _MSC_VER
    return _stat64(file, buf);
#else
    return stat64(file, buf);
#endif
}


inline int sg_fstat64(int fd, sg_fstat64_t *buf)
{
#if _MSC_VER
    return _fstat64(fd, buf);
#else
    return fstat64(fd, buf);
#endif
}

inline sg_off64_t sg_lseek64(int fd, sg_off64_t offset, int whence)
{
#if _MSC_VER
    return _lseeki64(fd, offset, whence);
#else
    return lseek64(fd, offset, whence);
#endif
}

inline int sg_open64(const char *file, int oflag)
{
#if _MSC_VER
    return _open(file, oflag);
#else
    return open64(file, oflag);
#endif
}

inline int sg_open64(const char *file, int oflag, sg_mode_t mode)
{
#if _MSC_VER
    return _open(file, oflag, mode);
#else
    return open64(file, oflag, mode);
#endif
}


// Unlocked functions
inline int sg_getc_unlocked(FILE *stream)
{
#if _MSC_VER
    return _fgetc_nolock(stream);
#else
    return getc_unlocked(stream);
#endif
}

inline int sg_getchar_unlocked(void)
{
#if _MSC_VER
    return _getchar_nolock();
#else
    return getchar_unlocked();
#endif
}

inline int sg_putc_unlocked(int c, FILE *stream)
{
#if _MSC_VER
    return _putc_nolock(c, stream);
#else
    return putc_unlocked(c, stream);
#endif
}

inline int sg_putchar_unlocked(int c)
{
#if _MSC_VER
    return _putchar_nolock(c);
#else
    return putchar_unlocked(c);
#endif
}

inline void sg_clearerr_unlocked(FILE *stream)
{
#if _MSC_VER
    // No unlocked version exists so we have to call the locked version
    clearerr(stream);
#else
    clearerr_unlocked(stream);
#endif
}

inline int sg_feof_unlocked(FILE *stream)
{
#if _MSC_VER
    // No unlocked version exists so we have to call the locked version
    return feof(stream);
#else
    return feof_unlocked(stream);
#endif
}

inline int sg_ferror_unlocked(FILE *stream)
{
#if _MSC_VER
    // No unlocked version exists so we have to call the locked version
    return ferror(stream);
#else
    return ferror_unlocked(stream);
#endif
}

inline int sg_fileno_unlocked(FILE *stream)
{
#if _MSC_VER
    // No unlocked version exists so we have to call the locked version
    return fileno(stream);
#else
    return fileno_unlocked(stream);
#endif
}

inline int sg_fflush_unlocked(FILE *stream)
{
#if _MSC_VER
    return _fflush_nolock(stream);
#else
    return fflush_unlocked(stream);
#endif
}


inline int sg_fgetc_unlocked(FILE *stream)
{
#if _MSC_VER
    return _fgetc_nolock(stream);
#else
    return fgetc_unlocked(stream);
#endif
}

inline int sg_fputc_unlocked(int c, FILE *stream)
{
#if _MSC_VER
    return _fputc_nolock(c, stream);
#else
    return fputc_unlocked(c, stream);
#endif
}


inline size_t sg_fread_unlocked(void *__restrict ptr, size_t size, size_t n,
                      FILE *__restrict stream)
{
#if _MSC_VER
    return _fread_nolock(ptr, size, n, stream);
#else
    return fread_unlocked(ptr, size, n, stream);
#endif
}

inline size_t sg_fwrite_unlocked(const void *__restrict ptr, size_t size, size_t n,
                      FILE *__restrict stream)
{
#if _MSC_VER
    return _fwrite_nolock(ptr, size, n, stream);
#else
    return fwrite_unlocked(ptr, size, n, stream);
#endif
}


inline char *sg_fgets_unlocked(char *__restrict s, int n, FILE *__restrict stream)
{
#if _MSC_VER
    // No unlocked version exists so we have to call the locked version
    return fgets(s, n, stream);
#else
    return fgets_unlocked(s, n, stream);
#endif
}

inline int sg_fputs_unlocked(const char *__restrict s, FILE *__restrict stream)
{
#if _MSC_VER
    // No unlocked version exists so we have to call the locked version
    return fputs(s, stream);
#else
    return fputs_unlocked(s, stream);
#endif
}


// Large file and unlocked
inline int sg_fseeko64_unlocked(FILE *stream, sg_off64_t offset, int whence)
{
#if _MSC_VER
    return _fseeki64_nolock(stream, offset, whence);
#else
    // No unlocked version exists so we have to call the locked version
    return fseeko64(stream, offset, whence);
#endif
}

inline sg_off64_t  sg_ftello64_unlocked(FILE *stream)
{
#if _MSC_VER
    return _ftelli64_nolock(stream);
#else
    // No unlocked version exists so we have to call the locked version
    return ftello64(stream);
#endif
}

#endif

/* eof StreamIO.h */

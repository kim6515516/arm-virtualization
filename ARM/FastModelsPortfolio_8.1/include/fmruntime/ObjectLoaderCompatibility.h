/*
 * $Id: ObjectLoaderCompatibility.h 20039 2007-06-04 10:14:50Z ugrossma $
 *
 * Project: Object Loader
 * $Author: ugrossma $
 * $Date: 2007-06-04 11:14:50 +0100 (Mon, 04 Jun 2007) $
 * $Revision: 20039 $
 *
 * Copyright (c) 2000-2003 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

/** \file
 * Backward compatibility declarations for the ObjectLoader.
 */

#ifndef _ObjectLoaderCompatibility_h_
#define _ObjectLoaderCompatibility_h_ "$Id: ObjectLoaderCompatibility.h 20039 2007-06-04 10:14:50Z ugrossma $"

#include "ObjectLoader.h"
#include "ObjectLoaderInterface.h"
#include "ObjectLoaderError.h"
#include "ObjectLoaderRawInterface.h"
#include "ObjectLoaderFormatSpecificLoader.h"

// these classes are the main classes visisble to the outside world
#define FormatIndependentLoader ObjectLoader
#define LoaderInterface ObjectLoaderInterface
#define LoaderError ObjectLoaderError

// these classes are of no interest to the outside world unless a custom format specific loader is written
#define FormatIndependentLoaderInterface ObjectLoaderRawInterface
#define FormatLoader ObjectLoaderFormatSpecificLoader
#define FormatNotRecognizedLoaderError ObjectLoaderErrorFormatNotRecognized

#endif

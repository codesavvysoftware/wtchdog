/////////////////////////////////////////////////////////////////////////////
/// @file FloatLib.hpp
///
/// Header file that provides floating point number functions
///
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - jmccaff 1-Apr-2016 Original Implementation
/// @endif
///
/// @ingroup App
///
/// @par Copyright (c) 2016 Rockwell Automation Technologies, Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////
#if !defined(FLOATLIB_HPP)
#define FLOATLIB_HPP

// SYSTEM INCLUDES
#include <stdint.h>

// C PROJECT INCLUDES
// (none)
// C++ PROJECT INCLUDES
// (none)

// FORWARD REFERENCES
// (none)

namespace App
{
	
// Float Types
enum FloatType
{
    FLP_INFINITE,
    FLP_NAN,
    FLP_NORMAL,
    FLP_SUBNORMAL,
    FLP_ZERO
};
static const float FLOAT_INFINITY = 0x7F800000U;
static const float FLOAT_NAN = 0x7FFFFFFFU;

////////////////////////////////////////////////////////////////////////////////
//  FUNCTION NAME: IsNan
//
/// @par Full Description
/// This function returns whether the input float is not a number
///
/// @param  fInput       The float to be checked
/// @return bIsNan       Is the float not a number
///
/// @pre none
/// @post Whether the input is NaN will be returned
///
/// @ingroup APP
////////////////////////////////////////////////////////////////////////////////
bool IsNan(float fInput);

////////////////////////////////////////////////////////////////////////////////
//  FUNCTION NAME: IsInf
//
/// @par Full Description
/// This function returns whether the input float is infinite
///
/// @param  fInput       The float to be checked
/// @return bIsInf       Is the float infinite
///
/// @pre none
/// @post Whether the input is infinite will be returned
///
/// @ingroup APP
////////////////////////////////////////////////////////////////////////////////
bool IsInf(float fInput);

////////////////////////////////////////////////////////////////////////////////
//  FUNCTION NAME: FpClassify
//
/// @par Full Description
/// This function classifies a floating point number based of it's bits
///
/// @param  fInput       The float to be classified
/// @return eFloatType   The type of float from enum FloatType
///
/// @pre none
/// @post The input float's classification will be returned
///
/// @ingroup APP
////////////////////////////////////////////////////////////////////////////////
FloatType FpClassify(float fInput);
    
} //namespace App

#endif // #if !defined(FLOATLIB_HPP)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
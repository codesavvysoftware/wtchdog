/////////////////////////////////////////////////////////////////////////////
/// @file FloatLib.cpp
///
/// This file contains the definitions of functions for working with floating point numbers
///
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// jmccaff 6-Apr-2016 initial implementation
/// @endif
///
/// @ingroup FloatLib
///
/// @par Copyright (c) 2016 Rockwell Automation Technologies, Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
// (none)
// C++ PROJECT INCLUDES
#include "FloatLib.hpp"    // This file contains the Class definition
                                // for this class.
// FORWARD REFERENCES

namespace App
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///@begin_claim_coding_exception
///
/// Rule 3-9-3
/// The underlying bit representations must be used to determine the classification of floating point values
///
//@end_claim_coding_exception
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///@begin_code_exception
  
/////////////////////////////////////////////////////////////////////////////
// METHOD NAME: FloatLib::FpClassify
//
/// Returns the type of the input float 
///
/////////////////////////////////////////////////////////////////////////////
FloatType FpClassify(float fInput) 
{
    // Float exponent bit mask
    static const uint32_t FLOAT_EXPONENT       = 0x7F800000U;
    // Float mantissa bit mask
    static const uint32_t FLOAT_MANTISSA       = 0x007FFFFFU;
    // Zero mantissa
    static const uint32_t FLOAT_ZERO_MANTISSA  =        0x0U;
    // Zero float
    static const uint32_t FLOAT_ZERO           =        0x0U;
    // Negative zero float
    static const uint32_t FLOAT_NEGATIVE_ZERO  = 0x80000000U;
    // Float zero exponent
    static const uint32_t FLOAT_ZERO_EXPONENT  =        0x0U; 

    uint32_t ulFloatAsBits = reinterpret_cast<uint32_t&>(fInput);
    FloatType eFloatType;
    //Check for zero
    if(ulFloatAsBits == FLOAT_ZERO || ulFloatAsBits == FLOAT_NEGATIVE_ZERO)
    {
        eFloatType = FLP_ZERO;
    }
    //INF and NAN have all 1's in exponent
    else if((ulFloatAsBits & FLOAT_EXPONENT) == FLOAT_EXPONENT)
    {
        //INF has all 0's in mantissa
        if((ulFloatAsBits & FLOAT_MANTISSA) == FLOAT_ZERO_MANTISSA)
        {
            eFloatType = FLP_INFINITE;
        }
        else
        {
            eFloatType = FLP_NAN;
        }
    }
    else
    {
        //Subnormal has all 0's in exponent
        if((ulFloatAsBits & FLOAT_EXPONENT) == FLOAT_ZERO_EXPONENT)
        {
            eFloatType = FLP_SUBNORMAL;
        }
        else
        {
            eFloatType = FLP_NORMAL;
        }
    }
    return eFloatType;
} 
//@end_code_exception    

/////////////////////////////////////////////////////////////////////////////
// METHOD NAME: FloatLib::IsNan
//
/// Returns whether the input float is not a number
///
/////////////////////////////////////////////////////////////////////////////
bool IsNan(float fInput) 
{
    return FpClassify(fInput) == FLP_NAN;
}

/////////////////////////////////////////////////////////////////////////////
// METHOD NAME: FloatLib::IsInf
//
/// Returns whether the input float is infinite
///
/////////////////////////////////////////////////////////////////////////////
bool IsInf(float fInput) 
{
    return FpClassify(fInput) == FLP_INFINITE;
}
  
} // namespace App

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
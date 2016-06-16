//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file RateofChange.cpp
///
/// Implementation of the RateOfChange class
/// 
/// @see RateOfChange.hpp for a detailed description of this class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - thaley1 14-Jun-2016 Original implementation
/// @endif
///
/// @ingroup SignalChain
///
/// @par Copyright (c) 2016 Rockwell Automation Technolgies, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "RateOfChange.hpp"
#include "FloatLib.hpp"

namespace SignalChain
{

// FORWARD REFERENCES
// (none)

//**********************************************************************************************************************
// Public methods
//**********************************************************************************************************************

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// RateOfChange::RateOfChange
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RateOfChange::RateOfChange() : m_fPreviousValue(0.0f), m_ulPreviousTimestampUs(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// RateOfChange::CalcRateOfChangeUs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float RateOfChange::CalcRateOfChangeUs(float fCurrentValue, uint32_t ulCurrentTimestampUs)
{
    uint32_t ulDifference = 0;

    // Init to INFINITY in case the current and previous timestamnps are equal which would result in a divide by Zero
    float fRateOfChange = App::FLOAT_INFINITY;

    //
    // If the current timestamp is less than the previous timestamp assume an overflow of the 32 bit fixed point number 
    // occurred during the elapsed time from the previous timestamp to the current time stamp.
    // The elapsed time is:
    //
    // largest unsigned int value - previous time stamp this is the time that elapsed before the overflow.
    // +1 for the overflow from the larget value to 0.
    // + the current timestamp to capture the amount of the overflow
    //
    if (ulCurrentTimestampUs < m_ulPreviousTimestampUs)
    {
        ulDifference = ULONG_MAX - m_ulPreviousTimestampUs + 1 + ulCurrentTimestampUs;
    }
    else
    {
        ulDifference = ulCurrentTimestampUs - m_ulPreviousTimestampUs;
    }


    //
    // Do the division if the denominator is non zero.
    //
    if (ulDifference != 0)
    {
        fRateOfChange = (fCurrentValue - m_fPreviousValue) / static_cast<float>(ulDifference);
    }

    //
    // Update the previous timestamp and unit values for the caller 
    // as now the provious timestamp and unit values are the current values upon input
    // since the calculation is complete.
    //
    m_ulPreviousTimestampUs = ulCurrentTimestampUs;

    m_fPreviousValue = fCurrentValue;

    return fRateOfChange;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// RateOfChange::CalcRateOfChangeMs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float RateOfChange::CalcRateOfChangeMs(float fCurrentValue, uint32_t ulCurrentTimestampUs)
{
    // Conversion factor for converting from microseconds to milliseconds
    static const float CONVERSION_US_TO_MS = 1000.0f;

    float fChangeRateSec = CalcRateOfChangeUs(fCurrentValue, ulCurrentTimestampUs);

    if (fChangeRateSec != App::FLOAT_INFINITY)
    {
        fChangeRateSec *= CONVERSION_US_TO_MS;
    }

    return fChangeRateSec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// RateOfChange::CalcRateOfChangeSec
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float RateOfChange::CalcRateOfChangeSec(float fCurrentValue, uint32_t ulCurrentTimestampUs)
{
    // Conversion factor for converting from microseconds to seconds
    static const float CONVERSION_US_TO_SEC = 1000000.0f;

    float fChangeRateSec = CalcRateOfChangeUs(fCurrentValue, ulCurrentTimestampUs);

    if (fChangeRateSec != App::FLOAT_INFINITY)
    {
        fChangeRateSec *= CONVERSION_US_TO_SEC;
    }

    return fChangeRateSec;
}

//**********************************************************************************************************************
// Private methods
//**********************************************************************************************************************
// (none)


} // SignalChain

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


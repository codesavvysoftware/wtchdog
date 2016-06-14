////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file RateofChang.cpp
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

namespace SignalChain
{

	// Conversion factor for converting from microseconds to seconds
	static const float CONVERSION_US_TO_SEC = 1000000.0f;

	// Conversion factor for converting from microseconds to milliseconds
	static const float CONVERSION_US_TO_MS  = 1000.0f;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// FUNCTION NAME: RateOfChange::CalcRateOfChangeUs
	///
	/// Calculate the rate of change between the previous value and the current value in units per microsecond.
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float RateOfChange::CalcRateOfChangeUs(RateOfChangeParams currentRateOfChangeData, RateOfChangeParams & prevRateOfChangeData)
	{
		uint32_t ulDifference = 0;

		float fRateOfChange = INFINITY;

		if (currentRateOfChangeData.ulTimestampUs < prevRateOfChangeData.ulTimestampUs)
		{
			ulDifference = ULONG_MAX - prevRateOfChangeData.ulTimestampUs + 1 + currentRateOfChangeData.ulTimestampUs;
		}
		else
		{
			ulDifference = currentRateOfChangeData.ulTimestampUs - prevRateOfChangeData.ulTimestampUs;
		}


		if (ulDifference != 0)
		{
			fRateOfChange = (currentRateOfChangeData.fValue - prevRateOfChangeData.fValue) / static_cast<float>(ulDifference);
		}

		prevRateOfChangeData.ulTimestampUs = currentRateOfChangeData.ulTimestampUs;

		prevRateOfChangeData.fValue = currentRateOfChangeData.fValue;

		return fRateOfChange;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// FUNCTION NAME: RateOfChange::CalcRateOfChangeMs
	///
	/// Calculate the rate of change between the previous value and the current value in units per millisecond.
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float RateOfChange::CalcRateOfChangeMs(RateOfChangeParams currentRateOfChangeData, RateOfChangeParams & prevRateOfChangeData)
	{
		float fChangeRateSec = CalcRateOfChangeUs(currentRateOfChangeData, prevRateOfChangeData);

		if (fChangeRateSec != INFINITY)
		{
			fChangeRateSec *= CONVERSION_US_TO_MS;
		}

		return fChangeRateSec;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// FUNCTION NAME: RateOfChange::CalcRateOfChangeSec
	///
	/// Calculate the rate of change between the previous value and the current value in units per second.
	///
	/// @return Computed rate of change in units per second
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float RateOfChange::CalcRateOfChangeSec(RateOfChangeParams currentRateOfChangeData, RateOfChangeParams & prevRateOfChangeData)
	{
		float fChangeRateSec = CalcRateOfChangeUs(currentRateOfChangeData, prevRateOfChangeData);

		if (fChangeRateSec != INFINITY)
		{
			fChangeRateSec *= CONVERSION_US_TO_SEC;
		}

		return fChangeRateSec;
	}
}


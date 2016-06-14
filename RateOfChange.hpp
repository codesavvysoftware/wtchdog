#ifndef __RATE_OF_CHANGE_HPP__
#define __RATE_OF_CHANGE_HPP__
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file RateofChang.hpp
///
/// This class exposes methods for computing the rate of change in microseconds, milleseconds, and seconds.  There also
/// is a method for delta time between two values that are inputs to the method
/// 
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
#include <stdint.h>
#include <limits>

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
// (none)
namespace SignalChain
{
    class RateOfChange
    {
    public:
        //**************************************************************************************************************
        // Public methods
        //**************************************************************************************************************

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::RateOfChange
        ///
        /// Constructor
        ///
        /// @par Full Description
        /// Class contructor for computing the rate of change in seconds, milliseconds, and microseconds.
        /// along with a method for computing delta time.
        ///
        /// @pre    none
        /// @post   class created
        /// 
        /// @param  none
        ///
        /// @return  None
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RateOfChange() {}
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::~RateOfChange
        ///
        /// Destrcutor
        ///
        /// @pre    RateOfChange object created.
        /// @post   RateOfChange object destroyed.
        /// 
        /// @par Full Description
        /// Destructor for objects created from the rate of change class.
        ///
        /// @return  None
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~RateOfChange() {}


        typedef struct
        {
            float     fValue;

            uint32_t  ulTimestampUs;
        }
        RateOfChangeParams;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::CalcRateOfChangeUs
        ///
        /// Calculate the rate of change between the previous value and the current value in units per microsecond.
        ///
        /// @par Full Description
        /// A general purpose method for calculating the rate of change between two values that have the same units in 
        /// units per microsecond.  The units could be feet, inches, volts, amps, etc.
        ///
        /// @pre    none.
        /// @post   Rate of change in microseconds calculated.
        /// 
		/// @param  currentRateOfChangeData  Current timestamp and value needed for calculating the rate of change.
		/// @param  RateOfChangeParams       Preceding timestamp and value needed for calculating the rate of change.          
        ///
        /// @return Calculated rate of change in units per microsecond
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float CalcRateOfChangeUs(RateOfChangeParams currentRateOfChangeData, RateOfChangeParams & prevRateOfChangeData);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::CalcRateOfChangeMs
        ///
        /// Calculate the rate of change between the previous value and the current value in units per millisecond.
        ///
        /// @par Full Description
        /// A general purpose method for calculating the rate of change between two values that have the same units in 
        /// units per millisecond.  The units could be feet, inches, volts, amps, etc.
        ///
        /// @pre    none.
        /// @post   Rate of change in milliseconds calculated.
        /// 
		/// @param  currentRateOfChangeData  Current timestamp and value needed for calculating the rate of change.
		/// @param  prevRateOfChangeData     Preceding timestamp and value needed for calculating the rate of change.         
		///
        /// @return Calculated rate of change in units per millisecond
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float CalcRateOfChangeMs(RateOfChangeParams currentRateOfChangeData, RateOfChangeParams & prevRateOfChangeData);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::CalcRateOfChangeSec
        ///
        /// Calculate the rate of change between the previous value and the current value in units per second.
        ///
        /// @par Full Description
        /// A general purpose method for calculating the rate of change between two values that have the same units in 
        /// units per second.  The units could be feet, inches, volts, amps, etc.
        ///
        /// @pre    none.
        /// @post   Rate of change in seconds calculated.
        /// 
        /// @param  currentRateOfChangeData  Current timestamp and value needed for calculating the rate of change.
        /// @param  prevRateOfChangeData     Preceding timestamp and value needed for calculating the rate of change.          
        ///
        /// @return Calculated rate of change in units per second
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float CalcRateOfChangeSec(RateOfChangeParams currentRateOfChangeData, RateOfChangeParams & prevRateOfChangeData);
    };
}
#endif //__WATCHDOG_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

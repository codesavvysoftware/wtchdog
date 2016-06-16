////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file RateofChange.hpp
///
/// For computing rates of change
///
/// @par Full Description
/// Class header for the RateOfChange class.
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

#if !defined(RATE_OF_CHANGE_HPP)
#define RATE_OF_CHANGE_HPP

// SYSTEM INCLUDES
#include <stdint.h>
#include <limits>

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
// (none)

namespace SignalChain
{

    // FORWARD REFERENCES
    // (none)

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CLASS NAME: RateOfChange
    ///
    /// For calculating rates of change
    /// 
    /// @par Full Description
    /// This class exposes methods for computing the rate of change in microseconds, milleseconds, and seconds.  There also
    /// is a method for delta time between two values that are inputs to the method
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RateOfChange 
{
    public:
        //**************************************************************************************************************
        // Public definitions
        //**************************************************************************************************************
        // (none)
        
        //**************************************************************************************************************
        // Public methods
        //**************************************************************************************************************

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: RateOfChange::RateOfChange
        ///
        /// Constructor 
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RateOfChange();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: ClassName::~ClassName
        ///
        /// Destructor 
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~RateOfChange() {}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: RateOfChange::CalcRateOfChangeUs
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
        /// @param  [in]  fCurrentValue          Current value for calculating rate of change.
        /// @param  [in]  ulCurrentTimeStampUs   Current timestamp in microseconds for calculating rate of change.         
        ///
        /// @return Calculated rate of change in units per microsecond
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float CalcRateOfChangeUs(float fCurrentValue, uint32_t ulCurrentTimestampUs);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: RateOfChange::CalcRateOfChangeMs
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
        /// @param  [in]  fCurrentValue          Current value for calculating rate of change.
        /// @param  [in]  ulCurrentTimeStampUs   Current timestamp in microseconds for calculating rate of change.         
        ///
        /// @return Calculated rate of change in units per millisecond
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float CalcRateOfChangeMs(float fCurrentValue, uint32_t ulCurrentTimestampUs);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: RateOfChange::CalcRateOfChangeSec
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
        /// @param  [in]  fCurrentValue          Current value for calculating rate of change.
        /// @param  [in]  ulCurrentTimeStampUs   Current timestamp in microseconds for calculating rate of change.         
        ///
        /// @return Calculated rate of change in units per second
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float CalcRateOfChangeSec(float fCurrentValue, uint32_t ulCurrentTimestampUs);
    private:
        //**************************************************************************************************************
        // Private definitions
        //**************************************************************************************************************
        
        // (none)

        //**************************************************************************************************************
        // Private methods
        //**************************************************************************************************************

        // (none)
        //**************************************************************************************************************
        // Member variables
        //**************************************************************************************************************

        // Initial call flag
        bool     m_bInitialCall;
        
        // Previous Value
        float    m_fPreviousValue;

        // Previous timestamp
        uint32_t m_ulPreviousTimestampUs;
};
} // SignalChain
#endif // #if !defined(RATE_OF_CHANGE_HPP)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

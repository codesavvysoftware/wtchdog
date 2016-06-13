#pragma once
namespace SignalChain
{
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
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    class RateOfChange
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
        virtual ~RateOfChange() {}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::RateOfChangeUs
        ///
        /// Compute the rate of change between the previous value and the current value in units per microsecond.
        ///
        /// @par Full Description
        /// A general purpose method for computing the rate of change between two values that have the same units in 
        /// units per microsecond.  The units could be feet, inches, volts, amps, etc.
        ///
        /// @pre    none.
        /// @post   Rate of change in microseconds computed.
        /// 
        /// @param  fValue                 Current value 
        /// @param  ulTimestampUs          Current Timestamp in microseconds
        /// @param  RateOfChangeParams     Immediately preceding timestamp and value needed for computing the rate of change.          
        ///
        /// @return Computed rate of change in units per microsecond
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float RateOfChangeUs(float fValue, uint32_t ulTimestampUs, RateOfChangeParams & rateOfChangeData)
        {
            uint32_t ulDifference = 0;

            float fRateOfChange = INFINITY;

            if (ulTimestampUs < rateOfChangeData.ulPreviousTimestampUs)
            {
                ulDifference = ULONG_MAX - rateOfChangeData.ulPreviousTimestampUs + 1 + ulTimestampUs;
            }
            else
            {
                ulDifference = ulTimestampUs - rateOfChangeData.ulPreviousTimestampUs;
            }


            if (ulDifference != 0)
            {
                fRateOfChange = (fValue - rateOfChangeData.fPreviousValue) / static_cast<float>(ulDifference);
            }

            rateOfChangeData.ulPreviousTimestampUs = timestampUs;

            rateOfChangeData.fPreviousValue = fValue;

            return fRateOfChange;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::RateOfChangeMs
        ///
        /// Compute the rate of change between the previous value and the current value in units per millisecond.
        ///
        /// @par Full Description
        /// A general purpose method for computing the rate of change between two values that have the same units in 
        /// units per millisecond.  The units could be feet, inches, volts, amps, etc.
        ///
        /// @pre    none.
        /// @post   Rate of change in seconds computed.
        /// 
        /// @param  fValue                 Current value 
        /// @param  ulTimestampUs          Current Timestamp in microseconds
        /// @param  RateOfChangeParams     Immediately preceding timestamp and value needed for computing the rate of change.          
        ///
        /// @return Computed rate of change in units per millisecond
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float RateOfChangeMs(float value, uint32_t timestampUs, RateOfChangeParams & rateOfChangeData)
        {
            float fChangeRateSec = RateOfChangeUs(value, timestampUs, rateOfChangeData);

            if (fChangeRateSec != INFINITY)
            {
                fChangeRateSec *= CONVERSION_US_TO_MS;
            }

            return fChangeRateSec;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: RateOfChange::RateOfChangeSec
        ///
        /// Compute the rate of change between the previous value and the current value in units per second.
        ///
        /// @par Full Description
        /// A general purpose method for computing the rate of change between two values that have the same units in 
        /// units per second.  The units could be feet, inches, volts, amps, etc.
        ///
        /// @pre    none.
        /// @post   Rate of change in seconds computed.
        /// 
        /// @param  fValue                 Current value 
        /// @param  ulTimestampUs          Current Timestamp in microseconds
        /// @param  RateOfChangeParams     Immediately preceding timestamp and value needed for computing the rate of change.          
        ///
        /// @return Computed rate of change in units per second
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float RateOfChangeSec(float value, uint32_t timestampUs, RateOfChangeParams & rateOfChangeData)
        {
            float fChangeRateSec = RateOfChangeUs(value, timestampUs, rateOfChangeData);

            if (fChangeRateSec != INFINITY)
            {
                fChangeRateSec *= CONVERSION_US_TO_SEC;
            }

            return fChangeRateSec;
        }

        typedef struct
        {
            float     fPreviousValue;

            uint32_t  ulPreviousTimestampUs;
        } 
        RateOfChangeParams;
    private:
        const float CONVERSION_US_TO_SEC;

        const float CONVERSION_US_TO_MS;


    };
}
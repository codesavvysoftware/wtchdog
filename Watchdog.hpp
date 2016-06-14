////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file Watchdog.hpp
///
/// Description Watchdog timer class definition
///
/// @par Full Description
/// Watchdog class provides an interface for controlling the Renesas Synergy watchdog hardware module. 
/// The watchdog serviced (kicked) within the refreshing period. 
/// If the service does not occur, the watchdog issues a system reset. 
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - gsb 30-Dec-2015 Original implementation
/// - gsb 08-Jan-2016 Added constant value to magic numbers
/// - zjrybak 04-Feb-2016 Added CpfBsp namespace
/// - zjrybak 29-Feb-2016 Added additional watchdog timeouts and windowed mode option
/// - zjrybak 14-Mar-2016 Removed DisableWatchdog and moved disable into the Init
/// - thaley1 13-Jun-2016 Modified for switch to Renesas Synergy MCUs
/// @endif
///
/// @ingroup CpfBsp
///
/// @par Copyright (c) 2016 Rockwell Automation Technologies, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __WATCHDOG_HPP__
#define __WATCHDOG_HPP__
// SYSTEM INCLUDES
#include <stdint.h>

// C PROJECT INCLUDES
#include "Registers.h"

// C++ PROJECT INCLUDES
// (none)

namespace CpfBsp
{
// FORWARD REFERENCES
// (none)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Watchdog: Watchdog
///
/// Class providing interface to the watchdog timer
/// 
/// @par Full Description
/// Provides KickWatchdog(), and IsWatchdogReset() public methods that interface to Renesas Synergy watchdog
/// peripheral.  This is an implementation based on using the independent watchdog timer (IWDT).  There are two 
/// watchdog timers for the Renesas Synergy MCUs.  An independent watchdog timer and a watchdog timer whose timing is
/// derived from the system clock.  The independent watchdog timer operation is completely configured by the OFS0 
/// register that is located in flash memory.  The specific address is contained in the appropriate Renesas Synergy
/// reference manual.  The OFS0 register is a read-only register and thus is not configurable at runtime.  Please 
/// refer to the appropriate section on the OFS0 operations (chapter 7 in S3A7 and chapter 6 in S124 manuals) for
/// a detailed description.  There is a selection for both watchdog timers for having the timer reset upon a 
/// watchdog timeout or generate an interrupt.  Generating the reset is the preferred choice for the following 
//  reasons:
/// 1.  At reset time the watchdog configuration register, OFS0, has to be configured.
/// 2.  Configuration of the independent watchdog timer is not possible under program control.
/// 3.  After a reset, during system boot time, the watchdog needs to be running in order to catch failures during
///     the system boot process.  So the watchdog needs to be running.  A more complicated scheme could be developed
///     that would use a non maskable interrupt instead of a reset.  The requirements for such a scheme are not 
///     limited to just the watchdog.  They involve initialization the NMI vector after reset and have an interrupt
///     service routine process the interrupt during system boot time.  Not even sure if interrupts are enabled 
///     during system boots.  Anyway if it is going to be implemented as a requirement it is a TBD.  Could be 
///     persuaded otherwise.  For engineering builds the situation is different.  If engineering builds want to use
///     the watchdog timer that is derived from the system clock there are a lot of things that could be configured
///     at run time.  The Init() method which I removed would be the place to add that configuration.  In short, 
///     I think it is fair to state that additional requirements for engineering builds is a TBD.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Watchdog
{
    public:
        //**************************************************************************************************************
        // Public methods
        //**************************************************************************************************************
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: Watchdog::KickWatchdog
        ///
        /// @par Full Description
        /// Write to the independent watchdog refresh register to start a new watchdog timeout. The windowing 
        /// feature specifies a period during the watchdog timer cycle when the watchdog can be refreshed.
        /// Possible window period:
        /// Beginning 00% End 100%  Watchdog can be refreshed at anytime during the watchdog timer cycle.
        /// Beginning 25% End 100%  Watchdog can be refreshed at anytime after 25% of the watchdog timer cycle.
        /// Beginning 50% End 100%  Watchdog can be refreshed at anytime after 50% of the watchdog timer cycle.
        /// Beginning 75% End 100%  Watchdog can be refreshed at anytime after 75% of the watchdog timer cycle.
        /// Beginning 00% End 75%   Watchdog can be refreshed at anytime before 75% of the wathcdog timer cycle 
        ///                         is complete 
        /// Beginning 25% End 75%   Watchdog can be refreshed at anytime after 25% and before 75% of the wathcdog timer 
        ///                         cycle is complete
        /// Beginning 50% End 75%   Watchdog can be refreshed at anytime after 50% and before 75% of the wathcdog timer 
        ///                         cycle is complete.
        /// Beginning 00% End 50%   Watchdog can be refreshed at anytime before 50% of the wathcdog timer cycle 
        ///                         is complete 
        /// Beginning 25% End 50%   Watchdog can be refreshed at anytime after 25% and before 50% of the wathcdog timer 
        ///                         cycle is complete
        /// Beginning 00% End 25%   Watchdog can be refreshed at anytime before 25% of the wathcdog timer cycle 
        ///                         is complete 
        /// Windowing is configured in the OFS0 register that is a read-only flash based register.
        /// For a complete description of the OFS0 register refer the the appropriate reference manual.
        /// Chapter 7 for the S3A7 and chapter 6 for the S124.
        ///       
        /// @pre    OFS0 configured for independing watchdog operation with the watchdog derived from the system clock
        ///         disabled.
        /// @post   none
        ///
        /// @return none
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void KickWatchdog(void);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: Watchdog::IsWatchdogReset
        ///
        /// @par Full Description
        /// Reads the independent watchdog timer status register to determine if the previous reset was caused by the 
        /// watchdog timer.
        ///
        /// @pre    OFS0 configured for independing watchdog operation with the watchdog derived from the system clock
        ///         disabled.
        /// @post   none
        ///
        /// @return whether or not a system reset was caused by a watchdog timeout.
        //  @retval true:  the system was watchdog reset
        /// @retval false: the system was not watchdog reset
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool IsWatchdogReset(void) const;


    private:

        //**************************************************************************************************************
        // Private definitions
        //**************************************************************************************************************

        // Register pointer 
        static RegMapIWdt * const m_pRegMapIWdt;   ///< Pointer to the IWDT Registers  

        // Refreshing the watchdog involves first writing a 0 to refresh register and then an 0xff to the same register
        static const uint8_t  FIRST_REFRESH_BYTE   = 0u;
        static const uint8_t  SECOND_REFRESH_BYTE  = 0xffu;

        // Status bit mask
        static const uint16_t IWDT_STATUS_ERR_MASK = 0xC000u;
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: Watchdog::Watchdog
        ///
        /// Constructor 
        /// 
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Watchdog() {}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// METHOD NAME: Watchdog::~Watchdog
        ///
        /// Destructor 
        /// 
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Watchdog() {}

        // Inhibit copy constructor and assignment operator
        Watchdog(Watchdog &);

        Watchdog & operator=(Watchdog const&); // assign op. hidden
};
} //CpfBsp;


#endif //__WATCHDOG_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file Watchdog.cpp
///
/// Implementation of the watchdog class
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - gsb 30-Dec-2015 Original implementation
/// - gsb 08-Jan-2016 Removed Magic numbers
/// - zjrybak 04-Feb-2016 Added CpfBsp namespace
/// - zjrybak 29-Feb-2016 Added additional watchdog timeouts and windowed mode option
/// - zjrybak 14-Mar-2016 Changed Init so that it only writes to the COP register once.
/// @endif
///
/// @ingroup CpfBsp
///
/// @par Copyright (c) 2016 Rockwell Automation Technologies, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
#include "PlatformAssert.h"

// C++ PROJECT INCLUDES
#include "Watchdog.hpp"
#include <time.h>

namespace CpfBsp
{
    // FORWARD REFERENCES
    RegMapWdt * const Watchdog::m_pRegMapWdt = reinterpret_cast<RegMapWdt *>(REG_ADDRESS_WDT);
    RegMapIWdt * const Watchdog::m_pRegMapIWdt = reinterpret_cast<RegMapIWdt *>(REG_ADDRESS_IWDT);

    //**********************************************************************************************************************
    // PUBLIC METHODS
    //**********************************************************************************************************************

    // Watchdog Initialization
    void Watchdog::Init(WATCHDOG_CONFG wcConfigureWatchdog)
    {
#ifdef _DEBUG
        uint32_t          ulNumberOfClockCyclesForWDT = CLOCKS_PER_SEC * 1000 * wcConfigureWatchdog.lExpirationPeriodMS;

        uint32_t          ulWDTCycles = 0;

        static const uint32_t WDTTOPS_CYCLES_1024 = 0;          // 0 0 : 1024 cycles(03FFh)
        static const uint32_t WDTTOPS_CYCLES_4096 = 0x40000U;   // 0 1 : 4096 cycles(0FFFh)
        static const uint32_t WDTTOPS_CYCLES_8192 = 0x80000U;   // 1 0 : 8192 cycles(1FFFh)
        static const uint32_t WDTTOPS_CYCLES_16384 = 0xC0000U;   // 1 1 : 16384 cycles(3FFFh
        if (ulNumberOfClockCycles >= 16384)
        {
        }
        else if (ulNumberOfClockCycles >= 8192)
        {
        }
        else if (ulNumberOfClockCycles >= 4096)
        {
        }
        else if (ulNumberOfClockCycles >= 1024)
        {
        }

        
        m_pRegMapWdt->uwControl = NOMINAL_WDT_SETTING;

        // Clear out any lingering reset occurred bits
        m_pRegMapWdt->uwStatus = WDT_CLEAR_STATUS;

        // NMI when timer times out
        m_pRegMapWdt->ubResetControl = WDT_CLEAR_STATUS;

        // Stop Counting in sleep mode
        m_pRegMapWdt->ubCountStopControl = WDT_STOP_COUNT_IN_SLEEP_MODES;

        // Start the watchdog
        KickWatchdog();

        
#endif
    }

    // Kick watchdog timer
    void Watchdog::KickWatchdog(void)
    {
#ifdef _DEBUG
        m_pRegMapWdt->ubRefresh = FIRST_REFRESH_BYTE;

        m_pRegMapWdt->ubRefresh = SECOND_REFRESH_BYTE;
#else
        m_pRegMapIWdt->ubRefresh = FIRST_REFRESH_BYTE;

        m_pRegMapIWdt->ubRefresh = SECOND_REFRESH_BYTE;
#endif
    }

    // Check whether the watchdog timer was reset
    bool Watchdog::IsWatchdogReset(void)
    {

        uint16_t  uwStatusOfWdt = 0;
#ifdef _DEBUG
        uwStatusOfWdt = m_pRegMapWdt->uwStatus;
#else
        uwStatusOfWdt = m_pRegMapIWdt->uwStatus;
#endif
        return (uwStatusOfWdt & WDT_STATUS_ERR_MASK);

    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


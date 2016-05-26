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
//#include "PlatformAssert.h"

//#include "stdafx.h"
// C++ PROJECT INCLUDES
#include "Watchdog.hpp"
#include <time.h>
#include <vector>

namespace CpfBsp
{
    //RegMapWdt  * const Watchdog::m_pRegMapWdt = reinterpret_cast<RegMapWdt *>(REG_ADDRESS_WDT);
    // FORWARD REFERENCES
#ifdef ENGINEERING_BUILD
	void Watchdog::Init(WATCHDOG_CONFIG wcConfigureWatchdog)
    {
        bool bChangeTimeoutPeriod = false;
		
		WATCHDOG_PERIOD_CYCLES wpc = {};

        uint16_t uwCurrentControlWord = m_pRegMapWdt->uwControl;

        if (wcConfigureWatchdog.wepExpirationPeriod.bChangeExpirationPeriod)
        {
            static WATCHDOG_PERIOD_CYCLES         wpcCycleSelections[] = {
                                                                       { (1024u * 4u),     WDTTOPS_CYCLES_1024, WDTCKS_DIV_BY_4},       // 2**10 * 2**2  == 2**12
                                                                       { (4096u * 4u),     WDTTOPS_CYCLES_4096, WDTCKS_DIV_BY_4 },      // 2**12 * 2**2  == 2**14
                                                                       { (8192u * 4u),     WDTTOPS_CYCLES_8192, WDTCKS_DIV_BY_4 },      // 2**13 * 2**2  == 2**15
                                                                       { (1024u * 64u),    WDTTOPS_CYCLES_1024, WDTCKS_DIV_BY_64 },     // 2**10 * 2**6  == 2**16
                                                                       { (16384u * 4u),    WDTTOPS_CYCLES_16384, WDTCKS_DIV_BY_4 },     // 2**14 * 2**2  == 2**16
                                                                       { (1024u * 128u),   WDTTOPS_CYCLES_1024, WDTCKS_DIV_BY_128 },    // 2**10 * 2**7  == 2**17
                                                                       { (4096u * 64u),    WDTTOPS_CYCLES_4096, WDTCKS_DIV_BY_64 },     // 2**12 * 2**6  == 2**18
                                                                       { (1024u * 512u),   WDTTOPS_CYCLES_1024, WDTCKS_DIV_BY_512 },    // 2**10 * 2**9  == 2**19
                                                                       { (4096u * 128u),   WDTTOPS_CYCLES_4096, WDTCKS_DIV_BY_128 },    // 2**12 * 2**7  == 2**19
                                                                       { (8192u * 64u),    WDTTOPS_CYCLES_8192, WDTCKS_DIV_BY_64 },     // 2**13 * 2**6  == 2**19
                                                                       { (8192u * 128u),   WDTTOPS_CYCLES_8192, WDTCKS_DIV_BY_128 },    // 2**13 * 2**7  == 2**20 
                                                                       { (16384u * 64u),   WDTTOPS_CYCLES_16384, WDTCKS_DIV_BY_64 },    // 2**14 * 2**6  == 2**20
                                                                       { (4096u * 512u),   WDTTOPS_CYCLES_4096, WDTCKS_DIV_BY_512 },    // 2**12 * 2**9  == 2**21
                                                                       { (16384u * 128u),  WDTTOPS_CYCLES_16384, WDTCKS_DIV_BY_128 },   // 2**14 * 2**7  == 2**21
                                                                       { (8192u * 512u),   WDTTOPS_CYCLES_8192, WDTCKS_DIV_BY_512 },    // 2**13 * 2**9  == 2**22
                                                                       { (1024u * 2048u),  WDTTOPS_CYCLES_1024, WDTCKS_DIV_BY_2048 },   // 2**10 * 2**12 == 2**22
                                                                       { (1024u * 8192u),  WDTTOPS_CYCLES_1024, WDTCKS_DIV_BY_8192 },   // 2**10 * 2**13 == 2**23
                                                                       { (4096u * 2048u),  WDTTOPS_CYCLES_4096, WDTCKS_DIV_BY_2048 },   // 2**12 * 2**11 == 2**23
                                                                       { (16384u * 512u),  WDTTOPS_CYCLES_16384, WDTCKS_DIV_BY_512 },   // 2**14 * 2**9  == 2**23
                                                                       { (8192u * 2048u),  WDTTOPS_CYCLES_8192, WDTCKS_DIV_BY_2048 },   // 2**13 * 2**11 == 2**24
                                                                       { (4096u * 8192u),  WDTTOPS_CYCLES_4096, WDTCKS_DIV_BY_8192 },   // 2**12 * 2**13 == 2**25
                                                                       { (16384u * 2048u), WDTTOPS_CYCLES_16384, WDTCKS_DIV_BY_2048 },  // 2**14 * 2**11 == 2**25
                                                                       { (8192u * 8192u),  WDTTOPS_CYCLES_8192, WDTCKS_DIV_BY_8192 },   // 2**13 * 2**13 == 2**26
                                                                       { (16384u * 8192u), WDTTOPS_CYCLES_16384, WDTCKS_DIV_BY_8192 },  // 2**14 * 2**13 == 2**27
            };
            static std::vector <WATCHDOG_PERIOD_CYCLES> CycleSelections(wpcCycleSelections, end(wpcCycleSelections));

            uint32_t Clocks = CLOCKS_PER_SEC;

            uint32_t SysClock = 48000000;

            uint32_t          ulNumberOfClockCyclesForWDT = (CLOCKS_PER_SEC / 1000) * wcConfigureWatchdog.wepExpirationPeriod.ulExpirationPeriodMS;

            ulNumberOfClockCyclesForWDT = (48000000 / 1000) * wcConfigureWatchdog.wepExpirationPeriod.ulExpirationPeriodMS;

            wpc = *end(wpcCycleSelections);

            for (std::vector<WATCHDOG_PERIOD_CYCLES>::iterator it = CycleSelections.begin(); it != CycleSelections.end(); ++it)
            {
                wpc = *it;

                uint32_t check_val = wpc.ulCycleCount;

                if (check_val > ulNumberOfClockCyclesForWDT)
                {
                    // Set clock cycles and divisor by what it points to
                    uint32_t ValueFound = check_val;

                    bChangeTimeoutPeriod = true;

                    break;
                }
            }

            uwCurrentControlWord &= WDT_CONTROL_TIME_MASK;

            uwCurrentControlWord |= wpc.uwClockDivisionRatio | wpc.uwPeriodSelection;
        }

        if (wcConfigureWatchdog.wwpWindow.bChangeWindowSettings)
        {
            uint16_t   uwWindowStart = 0;

            uint16_t   uwWindowEnd = 0;

            if (wcConfigureWatchdog.wwpWindow.wrwsStart == WINDOW_START_100)
            {
                uwWindowStart = WDTRPSS_100;
            }
            else if (wcConfigureWatchdog.wwpWindow.wrwsStart == WINDOW_START_75)
            {
                uwWindowStart = WDTRPSS_75;
            }
            else if (wcConfigureWatchdog.wwpWindow.wrwsStart == WINDOW_START_50)
            {
                uwWindowStart = WDTRPSS_50;
            }
            else
            {
                uwWindowStart = WDTRPSS_25;
            }

            if (wcConfigureWatchdog.wwpWindow.wrweEnd == WINDOW_END_75)
            {
                uwWindowEnd = WDTRPES_75;
            }
            else if (wcConfigureWatchdog.wwpWindow.wrweEnd == WINDOW_END_50)
            {
                uwWindowEnd = WDTRPES_50;
            }
            else if (wcConfigureWatchdog.wwpWindow.wrweEnd == WINDOW_END_25)
            {
                uwWindowEnd = WDTRPES_25;
            }
            else
            {
                uwWindowEnd = WDTRPES_00;
            }

            uwCurrentControlWord &= WDT_CONTROL_WINDOW_MASK;

            uwCurrentControlWord |= uwWindowStart | uwWindowEnd;
        }
        
        if (    
                wcConfigureWatchdog.wepExpirationPeriod.bChangeExpirationPeriod 
             || wcConfigureWatchdog.wwpWindow.bChangeWindowSettings
           )
        {
           // Configure the control register
           m_pRegMapWdt->uwControl = uwCurrentControlWord;
		}

        uint8_t ubCurrentResetOptionSelection = m_pRegMapWdt->ubResetControl;

        //if ( )

#endif

    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
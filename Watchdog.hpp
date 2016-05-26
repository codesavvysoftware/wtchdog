////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file Watchdog.hpp
///
/// Watchdog class provides a COP watchdog hardware module. 
/// The watchdog serviced (kicked) within the refreshing period. 
/// If the service does not occur, the watchdog issues a system reset. This class contains functions to 
/// configure the registers for the System Integration Module(SIM).
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - gsb 30-Dec-2015 Original implementation
/// - gsb 08-Jan-2016 Added constant value to magic numbers
/// - zjrybak 04-Feb-2016 Added CpfBsp namespace
/// - zjrybak 29-Feb-2016 Added additional watchdog timeouts and windowed mode option
/// - zjrybak 14-Mar-2016 Removed DisableWatchdog and moved disable into the Init
/// @endif
///
/// @ingroup CpfBsp
///
/// @par Copyright (c) 2016 Rockwell Automation Technologies, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __WATCHDOG_HPP__
#define __WATCHDOG_HPP__
// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
//#include "Registers.h"
#include <stdint.h>

// C++ PROJECT INCLUDES
// (none)

namespace CpfBsp
{
#ifdef ENGINEERING_BUILD
	template<typename T, size_t N>
    T * end(T(&ra)[N]) 
	{
        return ra + N;
    }
#endif

    class Watchdog
    {
    public:
#ifndef SIMULATE_ENVIRONMENT
        Watchdog() : m_pRegMapWdt(reinterpret_cast<RegMapWdt *>(REG_ADDRESS_WDT)),
                     m_pRegMapIWdt(reinterpret_cast<RegMapIWdt *>(REG_ADDRESS_IWDT))
        {}
#else
        Watchdog() : m_pRegMapWdt(&SimulatedWatchdogSysClock),
                     m_pRegMapIWdt(&SimulateWatchdogIndependent)
        {}

#endif
#ifdef ENGINEERING_BUILD
		typedef enum
        {
            START,
            STOP,
            NO_OPERATION
        }
        WATCHDOG_ACTION;

		typedef enum
		{
			WINDOW_START_100,
			WINDOW_START_75,
			WINDOW_START_50,
			WINDOW_START_25
		} WATCHDOG_REFRESH_WINDOW_START;

		typedef enum
		{
			WINDOW_END_75,
			WINDOW_END_50,
			WINDOW_END_25,
			WINDOW_END_00
		} WATCHDOG_REFRESH_WINDOW_END;

		typedef struct
		{
            bool                          bChangeWindowSettings;
			WATCHDOG_REFRESH_WINDOW_START wrwsStart;
			WATCHDOG_REFRESH_WINDOW_END   wrweEnd;
		}
		WATCHDOG_WINDOW_PARAMS;

        typedef struct
        {
            bool      bChangeExpirationPeriod;
            uint32_t  ulExpirationPeriodMS;
        } WATCHDOG_EXPIRATION_PERIOD;

		typedef struct
        {
            WATCHDOG_EXPIRATION_PERIOD          wepExpirationPeriod;
			WATCHDOG_WINDOW_PARAMS              wwpWindow;
            WATCHDOG_ACTION                     waStartAction;
            WATCHDOG_ACTION                     waSleepAction;
        }
        WATCHDOG_CONFIG;

        typedef struct
        {
            uint32_t                  ulCycleCount;
            uint16_t                  uwPeriodSelection;
            uint16_t                  uwClockDivisionRatio;
        }
        WATCHDOG_PERIOD_CYCLES;
#endif

        //**************************************************************************************************************
        // Public methods
        //**************************************************************************************************************              

#ifdef ENGINEERING_BUILD
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: Watchdog::Init
        ///
        /// Initialize watchdog HW module.
        ///
        /// @par Full Description
        /// Static function. Initialize the watchdog. 
        ///
        /// @param  none         the timeout value for the watchdog
        ///         
        /// @return none
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void Init(WATCHDOG_CONFIG wcConfigureWatchdog);
#endif
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: Watchdog::KickWatchdog
        ///
        /// @par Full Description
        /// Kicks watchdog HW module
        ///
        /// @param  none
        ///         
        /// @return none
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void KickWatchdog(void);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// FUNCTION NAME: Watchdog::IsWatchdogReset
        ///
        /// @par Full Description
        /// Checks whether there was a watchdog reset last time.
        ///
        /// @param  none
        ///         
        /// @return bool – TRUE:  the system was watchdog reset
        ///                FALSE: the system was not watchdog reset
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool IsWatchdogReset(void);


    private:

        //**************************************************************************************************************
        // Private definitions
        //**************************************************************************************************************
                                                            // WDT Stop Control bit 14
#ifdef ENGINEERING_BUILD
        static const uint8_t WDTSTPCTL_CONT = 0;            // 0: Counting continues
        static const uint8_t WDTSTPCTL_STOP = 0x80;         // 1 : Counting stops when entering Sleep mode.

                                                            // WDT Reset Interrupt Request bit 12
                                                            // Select WDT Behavior Select :
        static const uint8_t WDTRSTIRQS_NMI   = 0;          // 0 : NMI or Interrupt Request.
        static const uint8_t WDTRSTIRQS_RESET = 0x80;       // 1 : Reset

                                                            // WDT Window Start Position bits 11 and 10
                                                            // Select
                                                            // b11 b10
        static const uint16_t WDTRPSS_25  = 0;              // 0 0: 25 %
        static const uint16_t WDTRPSS_50  = 0x1000;         // 0 1 : 50 %
        static const uint16_t WDTRPSS_75  = 0x2000;         // 1 0 : 75 %
        static const uint16_t WDTRPSS_100 = 0x3000;         // 1 1 : 100 % (Window position is not specified).

                                                            // WDT Window End Position bits 9 and 8
                                                            // Select
                                                            // b09 b08
        static const uint16_t WDTRPES_75  = 0;              // 0 0: 25 %
        static const uint16_t WDTRPES_50  = 0x100;          // 0 1 : 50 %
        static const uint16_t WDTRPES_25  = 0X200;          // 1 0 : 75 %
        static const uint16_t WDTRPES_00  = 0X300;          // 1 1 : 100 % (No window end position setting).

                                                            // IWDT Clock Frequency bits 7 through 4
                                                            // Division Ratio Select b23 b20
        static const uint16_t WDTCKS_DIV_BY_4    = 0x0;     // 0 0 0 0 : PCLKB divided by 1
        static const uint16_t WDTCKS_DIV_BY_64   = 0x40;    // 0 1 0 0 : PCLKB divided by 64
        static const uint16_t WDTCKS_DIV_BY_128  = 0xf0;    // 1 1 1 1 : PCLKB divided by 128
        static const uint16_t WDTCKS_DIV_BY_512  = 0x60;    // 0 1 1 0 : PCLKB divided by 512
        static const uint16_t WDTCKS_DIV_BY_2048 = 0x70;    // 0 1 1 1 : PCLKB divided by 2048
        static const uint16_t WDTCKS_DIV_BY_8192 = 0x80;    // 1 0 0 0 : PCLKB divided by 8192

                                                            // WDT Timeout Period Select b19 b18
        static const uint16_t WDTTOPS_CYCLES_1024  = 0;     // 0 0 : 1024 cycles
        static const uint16_t WDTTOPS_CYCLES_4096  = 1;     // 0 1 : 4096 cycles
        static const uint16_t WDTTOPS_CYCLES_8192  = 2;     // 1 0 : 8192 cycles
        static const uint16_t WDTTOPS_CYCLES_16384 = 3;     // 1 1 : 16384 cycles


        static const uint32_t REG_ADDRESS_WDT = 0x40044200;
        static const uint32_t REG_ADDRESS_IWDT = 0x40044400;

        typedef struct
        {
            volatile uint8_t  ubRefresh;                  // WDT refresh register        0x00
            volatile uint8_t  ubUnusedRefresh;            // WDT unused 8 bits           0x01
            volatile uint16_t uwControl;                  // WDT control register        0x02
            volatile uint16_t uwStatus;                   // WDT status register         0x04
            volatile uint8_t  ubResetControl;             // WDT Reset Control Register  0x06
            volatile uint8_t  ubUnusedResetControl;       // WDT unused 8 bits           0x07
            volatile uint8_t  ubCountStopControl;         // WDT Control Stop Register   0x08
            // For alignment on a 4 byte boundry
            volatile uint8_t  ubCountStopControlUnused_0; // WDT Unused                  0x09
            volatile uint8_t  ubCountStopControlUnused_1; // WDT Unused                  0x0A
            volatile uint8_t  ubcountStopControlUnused_2; // WDT Unused                  0x0B
        }
        RegMapWdt;


        typedef struct
        {
            volatile uint8_t  ubRefresh;                  // IWDT refresh register        0x00
            // For alignment on a 4 byte boundry
            volatile uint8_t  ubUnusedRefresh_0;          // IWDT unused 8 bits           0x01
            volatile uint8_t  ubUnusedRefresh_1;          // IWDT unused 8 bits           0x02
            volatile uint8_t  ubUnusedRefresh_2;          // IWDT unused 8 bits           0x02
            volatile uint16_t uwStatus;                   // IWDT status register         0x04
            // For alignment on a 4 byte boundry
            volatile uint8_t  ubUnusedStatus_0;           // IWDT unused 8 bits           0x06
            volatile uint8_t  ubUnusedStatus_1;           // IWDT unused 8 bits           0x07
        }
        RegMapIWdt;


        // Refreshing the watchdog involves first writing a 0 to refresh register and then an 0xff to the same register
        static const uint8_t  FIRST_REFRESH_BYTE = 0;
        static const uint8_t  SECOND_REFRESH_BYTE = 0Xff;

        // Reset Status bit mask
        static const uint16_t WDT_STATUS_ERR_MASK = 0xC000;
        static const uint16_t WDT_CONTROL_TIME_MASK = 0xff0c;

        static const uint16_t WDT_CONTROL_WINDOW_MASK = 0xccff;
#endif
        
        //**************************************************************************************************************
        // Register pointer
        RegMapWdt *  const m_pRegMapWdt;    // Pointer to the WDT Registers
        RegMapIWdt * const m_pRegMapIWdt;   // Pointer to the IWDT Registers 
#ifdef SIMULATE_ENVIRONMENT
        RegMapWdt           SimulatedWatchdogSysClock;
        RegMapIWdt          SimulateWatchdogIndependent;
#endif
    };
};


#endif //__WATCHDOG_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






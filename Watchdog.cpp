////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file Watchdog.cpp
///
/// @see Watchdog.hpp for a detailed description of this class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - gsb 30-Dec-2015 Original implementation
/// - gsb 08-Jan-2016 Removed Magic numbers
/// - zjrybak 04-Feb-2016 Added CpfBsp namespace
/// - zjrybak 29-Feb-2016 Added additional watchdog timeouts and windowed mode option
/// - zjrybak 14-Mar-2016 Changed Init so that it only writes to the COP register once.
/// - thaley1 13-Jun-2016 Interface for Renesas Synergy MCUs
/// @endif
///
/// @ingroup CpfBsp
///
/// @par Copyright (c) 2016 Rockwell Automation Technologies, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "Watchdog.hpp"

namespace CpfBsp
{
// FORWARD REFERENCES
// (none)

    RegMapIWdt * const Watchdog::m_pRegMapIWdt = reinterpret_cast<RegMapIWdt *>(REG_ADDRESS_IWDT);

    //**********************************************************************************************************************
    // Public methods
    //**********************************************************************************************************************

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Watchdog::KickWatchdog
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Watchdog::KickWatchdog(void)
    {         
         m_pRegMapIWdt->ubRefresh = FIRST_REFRESH_BYTE;

         m_pRegMapIWdt->ubRefresh = SECOND_REFRESH_BYTE;
     }

     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// Watchdog::IsWatchdogReset
     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     bool Watchdog::IsWatchdogReset(void) const
     {
         return (m_pRegMapIWdt->uwStatus & IWDT_STATUS_ERR_MASK);
     }
    
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of file.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
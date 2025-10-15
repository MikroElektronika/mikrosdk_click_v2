/*!
 * @file main.c
 * @brief Charger 30 Click example
 *
 * # Description
 * This example demonstrates the use of the Charger 30 Click board by reading and logging
 * the charging status, input and battery voltage, current consumption, and fault diagnostics.
 * The demo configures the default setup and then periodically polls for system status
 * and fault information.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Charger 30 Click driver and applies the default configuration.
 *
 * ## Application Task
 * Periodically reads and logs charger status and fault registers along with voltage, current.
 *
 * @note
 * Ensure a valid power supply and a battery are connected for proper functionality.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger30.h"

static charger30_t charger30;
static log_t logger;

/**
 * @brief Charger 30 display status function.
 * @details This function logs the interpreted status bits from the STATUS register 
 * of the Charger 30 Click board using the logger interface. The output includes:
 * VIN source type, charging state, NTC status, thermal regulation, and VSYS status.
 * @param status : Value of the STATUS register.
 * @return None.
 * @note None.
 */
static void charger30_display_status ( uint8_t status );

/**
 * @brief Charger 30 display fault function.
 * @details This function logs the interpreted fault bits from the FAULT register 
 * of the Charger 30 Click board using the logger interface. The output includes:
 * watchdog timeout, OTG fault, input fault, thermal shutdown, battery fault, and NTC fault.
 * @param fault : Value of the FAULT register.
 * @return None.
 * @note None.
 */
static void charger30_display_fault ( uint8_t fault );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger30_cfg_t charger30_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    charger30_cfg_setup( &charger30_cfg );
    CHARGER30_MAP_MIKROBUS( charger30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger30_init( &charger30, &charger30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER30_ERROR == charger30_default_cfg ( &charger30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    charger30_status_t status;
    if ( CHARGER30_OK == charger30_read_status ( &charger30, &status ) )
    {
        charger30_display_status ( status.status );
        charger30_display_fault ( status.fault );
        log_printf ( &logger, " VBAT: %u mV\r\n", status.vbat );
        log_printf ( &logger, " VSYS: %u mV\r\n", status.vsys );
        log_printf ( &logger, " NTC: %.1f %%\r\n", status.ntc );
        log_printf ( &logger, " VIN: %u mV\r\n", status.vin );
        log_printf ( &logger, " Ichg: %.1f mA\r\n", status.ichg );
        log_printf ( &logger, " Iin: %.1f mA\r\n", status.iin );
        log_printf ( &logger, " Iin_dpm: %u mA\r\n\n", status.iin_dpm );
    }
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void charger30_display_status( uint8_t status )
{
    log_printf ( &logger, " VIN status: " );
    switch ( status & CHARGER30_STATUS_VIN_STAT_MASK )
    {
        case CHARGER30_STATUS_VIN_STAT_NO_INPUT:
        {
            log_printf ( &logger, "No input\r\n" );
            break;
        }
        case CHARGER30_STATUS_VIN_STAT_NONSTANDARD_ADAPT:
        {
            log_printf ( &logger, "Nonstandard adapter (1A/2.1A/2.4A)\r\n" );
            break;
        }
        case CHARGER30_STATUS_VIN_STAT_SDP:
        {
            log_printf ( &logger, "SDP\r\n" );
            break;
        }
        case CHARGER30_STATUS_VIN_STAT_CDP:
        {
            log_printf ( &logger, "CDP\r\n" );
            break;
        }
        case CHARGER30_STATUS_VIN_STAT_DCP:
        {
            log_printf ( &logger, "DCP\r\n" );
            break;
        }
        case CHARGER30_STATUS_VIN_STAT_FAST_CHARGE:
        {
            log_printf ( &logger, "Fast-charge adapter\r\n" );
            break;
        }
        case CHARGER30_STATUS_VIN_STAT_OTG:
        {
            log_printf ( &logger, "OTG\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n" );
            break;
        }
    }
    log_printf ( &logger, " Charge status: " );
    switch ( status & CHARGER30_STATUS_CHG_STAT_MASK )
    {
        case CHARGER30_STATUS_CHG_STAT_NOT_CHARGING:
        {
            log_printf ( &logger, "Not charging\r\n" );
            break;
        }
        case CHARGER30_STATUS_CHG_STAT_TRICKLE_CHARGE:
        {
            log_printf ( &logger, "Trickle charge\r\n" );
            break;
        }
        case CHARGER30_STATUS_CHG_STAT_CC_CHARGE:
        {
            log_printf ( &logger, "Constant current charge\r\n" );
            break;
        }
        case CHARGER30_STATUS_CHG_STAT_CHARGE_DONE:
        {
            log_printf ( &logger, "Charge done\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n" );
            break;
        }
    }
    if ( CHARGER30_STATUS_NTC_FLOAT_FLOAT == ( status & CHARGER30_STATUS_NTC_FLOAT_MASK ) )
    {
        log_printf ( &logger, " NTC float\r\n" );
    }
    if ( CHARGER30_STATUS_THERM_STAT_THERMAL_REG == ( status & CHARGER30_STATUS_THERM_STAT_MASK ) )
    {
        log_printf ( &logger, " Thermal regulation\r\n" );
    }
    if ( CHARGER30_STATUS_VSYS_STAT_IN_REG == ( status & CHARGER30_STATUS_VSYS_STAT_MASK ) )
    {
        log_printf ( &logger, " In Vsysmin regulation (BAT < Vsysmin)\r\n" );
    }
}

static void charger30_display_fault( uint8_t fault )
{
    if ( fault & CHARGER30_FAULT_WATCHDOG )
    {
        log_printf ( &logger, " Fault: Watchdog timer expiration\r\n" );
    }
    if ( fault & CHARGER30_FAULT_OTG )
    {
        log_printf ( &logger, " Fault: VIN overload, or VIN over-voltage protection (OVP),\r\n" );
        log_printf ( &logger, "        or the battery has an under-voltage condition\r\n" );
    }
    if ( fault & CHARGER30_FAULT_INPUT )
    {
        log_printf ( &logger, " Fault: Input over-voltage protection (OVP) or no input\r\n" );
    }
    if ( fault & CHARGER30_FAULT_THERMAL_SHUTDOWN )
    {
        log_printf ( &logger, " Fault: Thermal shutdown\r\n" );
    }
    if ( fault & CHARGER30_FAULT_BAT )
    {
        log_printf ( &logger, " Fault: Battery over-voltage protection (OVP)\r\n" );
    }
    if ( CHARGER30_FAULT_NTC_NORMAL != ( fault & CHARGER30_FAULT_NTC_MASK ) )
    {
        switch ( fault & CHARGER30_FAULT_NTC_MASK )
        {
            case CHARGER30_FAULT_NTC_WARM:
            {
                log_printf ( &logger, " Fault: NTC warm\r\n" );
                break;
            }
            case CHARGER30_FAULT_NTC_COOL:
            {
                log_printf ( &logger, " Fault: NTC cool\r\n" );
                break;
            }
            case CHARGER30_FAULT_NTC_COLD:
            {
                log_printf ( &logger, " Fault: NTC cold\r\n" );
                break;
            }
            case CHARGER30_FAULT_NTC_HOT:
            {
                log_printf ( &logger, " Fault: NTC hot\r\n" );
                break;
            }
            default:
            {
                log_printf ( &logger, " Fault: NTC Fault unknown\r\n" );
                break;
            }
        }
    }
}

// ------------------------------------------------------------------------ END

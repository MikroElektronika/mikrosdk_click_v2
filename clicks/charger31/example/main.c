/*!
 * @file main.c
 * @brief Charger 31 Click example
 *
 * # Description
 * This example demonstrates the operation of the Charger 31 Click board by monitoring
 * the status registers and displaying information related to power input, charging state, 
 * battery presence, and possible faults.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board, then performs the default configuration.
 *
 * ## Application Task
 * Periodically reads the status registers and logs messages for VIN readiness, battery presence,
 * charging status, and charging faults.
 *
 * @note
 * Either a battery or VIN USB must be connected to the Click board for the communication to work.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger31.h"

static charger31_t charger31;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger31_cfg_t charger31_cfg;  /**< Click config object. */

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
    charger31_cfg_setup( &charger31_cfg );
    CHARGER31_MAP_MIKROBUS( charger31_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger31_init( &charger31, &charger31_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER31_ERROR == charger31_default_cfg ( &charger31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    charger31_status_t status;
    if ( CHARGER31_OK == charger31_read_status ( &charger31, &status ) )
    {
        if ( !( ( status.status_1 & CHARGER31_STATUS1_VIN_GD ) && 
                ( status.status_1 & CHARGER31_STATUS1_VIN_RDY ) ) )
        {
            log_printf ( &logger, " No VIN ready to charge\r\n" );
        }

        if ( status.status_3 & CHARGER31_STATUS3_BATT_MISSING )
        {
            log_printf ( &logger, " No battery detected\r\n" );
        }
        else
        {
            if ( !( status.status_1 & CHARGER31_STATUS1_VSYS_STAT ) )
            {
                log_printf ( &logger, " VBATT is lower than VSYS_MIN\r\n" );
            }

            if ( status.status_5 & CHARGER31_STATUS5_BFET_STAT_DISCHARGING )
            {
                log_printf ( &logger, " The battery is discharging\r\n" );
            }
            else
            {
                log_printf ( &logger, " Charging status: " );
                switch ( status.status_2 & CHARGER31_STATUS2_CHG_STAT_MASK )
                {
                    case CHARGER31_STATUS2_CHG_STAT_NOT_CHARGING:
                    {
                        log_printf ( &logger, "Not charging\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_TRICKLE_CHG:
                    {
                        log_printf ( &logger, "Trickle charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_PRE_CHG:
                    {
                        log_printf ( &logger, "Pre-charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_FAST_CHG:
                    {
                        log_printf ( &logger, "Fast charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_CV_CHG:
                    {
                        log_printf ( &logger, "Constant-voltage charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_CHG_DONE:
                    {
                        log_printf ( &logger, "Charging is done\r\n" );
                        break;
                    }
                    default:
                    {
                        log_printf ( &logger, "Unknown\r\n" );
                        break;
                    }
                }
            }

            if ( status.status_2 & CHARGER31_STATUS2_CHG_FAULT_MASK )
            {
                log_printf ( &logger, " Charging fault: " );
                switch ( status.status_2 & CHARGER31_STATUS2_CHG_FAULT_MASK )
                {
                    case CHARGER31_STATUS2_CHG_FAULT_IN_OVP:
                    {
                        log_printf ( &logger, "Input OVP\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_FAULT_TIMER:
                    {
                        log_printf ( &logger, "The charge timer has expired\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_FAULT_BATT_OVP:
                    {
                        log_printf ( &logger, "Battery OVP\r\n" );
                        break;
                    }
                    default:
                    {
                        log_printf ( &logger, "Unknown\r\n" );
                        break;
                    }
                }
            }
        }
        log_printf ( &logger, "\r\n" );
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

// ------------------------------------------------------------------------ END

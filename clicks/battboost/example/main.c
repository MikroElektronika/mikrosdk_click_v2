/*!
 * @file main.c
 * @brief BATT Boost Click example
 *
 * # Description
 * This library contains API for the BATT Boost Click driver.
 * This driver provides the functions to controle battery energy management 
 * device designed to maximize usable capacity from non-rechargeable.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration, 
 * sets the output voltage to 1.8V, charge current to 16mA, 
 * and early warning voltage to 2.6V.
 *
 * ## Application Task
 * This example demonstrates the use of the BATT Boost Click board. 
 * The demo application uses two operations in two states: 
 * the charging state and the active state. First, when the device is in a Charge state, 
 * the external storage capacitor is charging from VBT using a constant current 
 * and displays storage capacitor voltage levels and charge cycle count.
 * Upon completion of a Charge state, the device transitions to the Active state 
 * at which time VDH becomes a regulated voltage output of 1.8V (default configuration), 
 * displays storage capacitor voltage level, and monitors alarms 
 * for low output voltage (below 1.8V) and early warning (below 2.4V). 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "battboost.h"

static battboost_t battboost;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battboost_cfg_t battboost_cfg;  /**< Click config object. */

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
    battboost_cfg_setup( &battboost_cfg );
    BATTBOOST_MAP_MIKROBUS( battboost_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battboost_init( &battboost, &battboost_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTBOOST_ERROR == battboost_default_cfg ( &battboost ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    float vcap = 0;
    uint8_t status = 0;
    uint32_t chenergy = 0;

    if ( BATTBOOST_STATUS_READY != battboost_get_ready( &battboost ) )
    {
        if ( BATTBOOST_OK == battboost_set_op_mode( &battboost, BATTBOOST_OP_MODE_CHARGE ) )
        {
            log_printf( &logger, "\nOperating state: Charge\r\n" );
        }

        if ( BATTBOOST_OK == battboost_get_vcap( &battboost, &vcap ) )
        {
            log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
        }

        if ( BATTBOOST_OK == battboost_get_chenergy( &battboost, &chenergy ) )
        {
            log_printf( &logger, " Charge cycle count: %lu \r\n", chenergy );
        }
        Delay_ms( 1000 );
    }
    else
    {
        if ( BATTBOOST_OK == battboost_set_op_mode( &battboost, BATTBOOST_OP_MODE_ACTIVE ) )
        {
            log_printf( &logger, "\nOperating state: Active\r\n" );
            if ( BATTBOOST_OK == battboost_get_vcap( &battboost, &vcap ) )
            {
                log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
            }

            if ( BATTBOOST_OK == battboost_get_status( &battboost, &status ) )
            {
                if ( BATTBOOST_STATUS_EW & status )
                {
                    log_printf( &logger, " Status: Early warning.\r\n" );
                }

                if ( BATTBOOST_STATUS_ALRM & status )
                {
                    log_printf( &logger, " Status: Low output voltage in the Active state.\r\n" );
                }
            }
        }
        Delay_ms( 1000 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END

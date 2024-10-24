/*!
 * @file main.c
 * @brief BATT Boost 2 Click example
 *
 * # Description
 * This library contains API for the BATT Boost 2 Click driver.
 * This driver provides the functions to control battery energy management 
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
 * This example demonstrates the use of the BATT Boost 2 Click board. 
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
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "battboost2.h"

static battboost2_t battboost2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battboost2_cfg_t battboost2_cfg;  /**< Click config object. */

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
    battboost2_cfg_setup( &battboost2_cfg );
    BATTBOOST2_MAP_MIKROBUS( battboost2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battboost2_init( &battboost2, &battboost2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTBOOST2_ERROR == battboost2_default_cfg ( &battboost2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    float vcap = 0;
    uint8_t status = 0;
    uint32_t chenergy = 0;

    if ( BATTBOOST2_STATUS_READY != battboost2_get_ready( &battboost2 ) )
    {
        if ( BATTBOOST2_OK == battboost2_set_op_mode( &battboost2, BATTBOOST2_OP_MODE_CHARGE ) )
        {
            log_printf( &logger, "\nOperating state: Charge\r\n" );
        }

        if ( BATTBOOST2_OK == battboost2_get_vcap( &battboost2, &vcap ) )
        {
            log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
        }

        if ( BATTBOOST2_OK == battboost2_get_chenergy( &battboost2, &chenergy ) )
        {
            log_printf( &logger, " Charge cycle count: %lu \r\n", chenergy );
        }
        Delay_ms ( 1000 );
    }
    else
    {
        if ( BATTBOOST2_OK == battboost2_set_op_mode( &battboost2, BATTBOOST2_OP_MODE_ACTIVE ) )
        {
            log_printf( &logger, "\nOperating state: Active\r\n" );
            if ( BATTBOOST2_OK == battboost2_get_vcap( &battboost2, &vcap ) )
            {
                log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
            }

            if ( BATTBOOST2_OK == battboost2_get_status( &battboost2, &status ) )
            {
                if ( BATTBOOST2_STATUS_EW & status )
                {
                    log_printf( &logger, " Status: Early warning.\r\n" );
                }

                if ( BATTBOOST2_STATUS_ALRM & status )
                {
                    log_printf( &logger, " Status: Low output voltage in the Active state.\r\n" );
                }
            }
        }
        Delay_ms ( 1000 );
    }
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

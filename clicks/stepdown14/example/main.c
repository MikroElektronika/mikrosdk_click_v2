/*!
 * @file main.c
 * @brief Step Down 14 Click example
 *
 * # Description
 * This example demonstrates the use of the Step Down 14 Click board for
 * adjustable output voltage control. The application continuously changes
 * the output voltage within the supported range and monitors the power-good
 * pin for fault indication.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Step Down 14 Click driver, and enables the device.
 *
 * ## Application Task
 * Adjusts the output voltage between minimum and maximum values, logs the
 * target and actual configured voltage values, and checks the PG pin status
 * for fault detection.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown14.h"

#ifndef MIKROBUS_POSITION_STEPDOWN14
    #define MIKROBUS_POSITION_STEPDOWN14 MIKROBUS_1
#endif

static stepdown14_t stepdown14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown14_cfg_t stepdown14_cfg;  /**< Click config object. */

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
    stepdown14_cfg_setup( &stepdown14_cfg );
    STEPDOWN14_MAP_MIKROBUS( stepdown14_cfg, MIKROBUS_POSITION_STEPDOWN14 );
    if ( I2C_MASTER_ERROR == stepdown14_init( &stepdown14, &stepdown14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepdown14_enable_device ( &stepdown14 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float target_vout = STEPDOWN14_VOUT_MIN;
    static float step = 0.25;
    float set_vout = 0;

    if ( STEPDOWN14_OK == stepdown14_set_vout ( &stepdown14, target_vout, &set_vout ) )
    {
        log_printf( &logger, "Target VOUT: %.2f V\r\n\n", target_vout );
        log_printf( &logger, "Set VOUT: %.2f V\r\n\n", set_vout );
        target_vout += ( target_vout * step );
        if ( target_vout > STEPDOWN14_VOUT_MAX )
        {
            step = -step;
            target_vout = STEPDOWN14_VOUT_MAX;
        }
        else if ( target_vout < STEPDOWN14_VOUT_MIN )
        {
            step = -step;
            target_vout = STEPDOWN14_VOUT_MIN;
        }
    }

    if ( !stepdown14_get_pg_pin ( &stepdown14 ) )
    {
        log_error( &logger, "Fault detected via PG pin\r\n" );
    }

    Delay_ms ( 1000 );
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

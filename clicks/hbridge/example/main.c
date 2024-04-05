/*!
 * @file main.c
 * @brief H-Bridge Click Example.
 *
 * # Description
 * This example demonstrates the use of the H-Bridge click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 400 half
 * steps with a 2 seconds delay before changing the direction. All data is being logged on
 * the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge.h"

static hbridge_t hbridge;   /**< H-Bridge Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge_cfg_t hbridge_cfg;  /**< Click config object. */

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
    hbridge_cfg_setup( &hbridge_cfg );
    HBRIDGE_MAP_MIKROBUS( hbridge_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridge_init( &hbridge, &hbridge_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    hbridge_set_step_mode ( &hbridge, HBRIDGE_MODE_FULL_STEP );
    hbridge_set_direction ( &hbridge, HBRIDGE_DIR_CW );
    hbridge_drive_motor ( &hbridge, 200, HBRIDGE_SPEED_MEDIUM );
    log_printf ( &logger, " Move 200 full steps clockwise\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge_set_step_mode ( &hbridge, HBRIDGE_MODE_HALF_STEP );
    hbridge_set_direction ( &hbridge, HBRIDGE_DIR_CCW );
    hbridge_drive_motor ( &hbridge, 400, HBRIDGE_SPEED_FAST );
    log_printf ( &logger, " Move 400 half steps counter-clockwise\r\n\n" );
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

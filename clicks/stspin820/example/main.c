/*!
 * @file main.c
 * @brief STSPIN820 Click Example.
 *
 * # Description
 * This example demonstrates the use of the STSPIN820 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 steps and then counter-clockwise with a 2 seconds
 * delay delay on driving mode change. All data is being logged on the USB UART where
 * you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stspin820.h"

static stspin820_t stspin820;   /**< STSPIN820 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stspin820_cfg_t stspin820_cfg;  /**< Click config object. */

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
    stspin820_cfg_setup( &stspin820_cfg );
    STSPIN820_MAP_MIKROBUS( stspin820_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stspin820_init( &stspin820, &stspin820_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stspin820_default_cfg ( &stspin820 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 steps clockwise, speed: slow\r\n\n" );
    stspin820_set_direction ( &stspin820, STSPIN820_DIR_CW );
    stspin820_drive_motor ( &stspin820, 200, STSPIN820_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 200 steps counter-clockwise, speed: fast\r\n\n" );
    stspin820_set_direction ( &stspin820, STSPIN820_DIR_CCW );
    stspin820_drive_motor ( &stspin820, 200, STSPIN820_SPEED_FAST );
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

/*!
 * @file main.c
 * @brief DC Motor 20 Click Example.
 *
 * # Description
 * This example demonstrates the use of DC Motor 20 click board by driving the motors
 * in both direction in the span of 14 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the click board to standby mode.
 *
 * ## Application Task
 * Drives the motors in the forward direction for 5 seconds, and then switches the direction, 
 * with a brake time of 2 seconds between switching the direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor20.h"

static dcmotor20_t dcmotor20;   /**< DC Motor 20 Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor20_cfg_t dcmotor20_cfg;  /**< Click config object. */

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
    dcmotor20_cfg_setup( &dcmotor20_cfg );
    DCMOTOR20_MAP_MIKROBUS( dcmotor20_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor20_init( &dcmotor20, &dcmotor20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    dcmotor20_set_standby_mode ( &dcmotor20 );
    log_info( &logger, " Application Task " );
}
void application_task ( void ) 
{
    log_printf ( &logger, " Driving motors forward...\r\n" );
    dcmotor20_set_channel_mode ( &dcmotor20, DCMOTOR20_CHANNEL_1 | DCMOTOR20_CHANNEL_2, DCMOTOR20_MODE_FORWARD );
    dcmotor20_drive_motor ( &dcmotor20, DCMOTOR20_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n" );
    dcmotor20_set_standby_mode ( &dcmotor20 );
    Delay_ms( 2000 );
    log_printf ( &logger, " Driving motors in reverse...\r\n" );
    dcmotor20_set_channel_mode ( &dcmotor20, DCMOTOR20_CHANNEL_1 | DCMOTOR20_CHANNEL_2, DCMOTOR20_MODE_REVERSE );
    dcmotor20_drive_motor ( &dcmotor20, DCMOTOR20_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n\n" );
    dcmotor20_set_standby_mode ( &dcmotor20 );
    Delay_ms( 2000 );
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

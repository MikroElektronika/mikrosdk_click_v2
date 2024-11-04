/*!
 * @file main.c
 * @brief DC Motor 19 Click Example.
 *
 * # Description
 * This example demonstrates the use of DC Motor 19 Click board by driving the motors
 * in both direction in the span of 14 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the Click by disabling the standby mode.
 *
 * ## Application Task
 * Drives the motors in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
 * and after that drives them in the reverse direction for 5 seconds, and finally, 
 * stops driving for 2 seconds which basically disconnects the motors.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor19.h"

static dcmotor19_t dcmotor19;   /**< DC Motor 19 Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor19_cfg_t dcmotor19_cfg;  /**< Click config object. */

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
    dcmotor19_cfg_setup( &dcmotor19_cfg );
    DCMOTOR19_MAP_MIKROBUS( dcmotor19_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor19_init( &dcmotor19, &dcmotor19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    dcmotor19_disable_standby_mode ( &dcmotor19 );
    log_info( &logger, " Application Task " );
}
void application_task ( void ) 
{
    log_printf ( &logger, " Driving motors forward...\r\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_FORWARD );
    dcmotor19_drive_motor ( &dcmotor19, DCMOTOR19_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_SHORT_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf ( &logger, " Driving motors in reverse...\r\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_REVERSE );
    dcmotor19_drive_motor ( &dcmotor19, DCMOTOR19_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Stop driving!\r\n\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_STOP );
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

/*!
 * @file main.c
 * @brief Silent Step 3 Click example
 *
 * # Description
 * This example demonstrates the use of the Silent Step 3 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
 * steps and 400 quarter steps with 2 seconds delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "silentstep3.h"

static silentstep3_t silentstep3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep3_cfg_t silentstep3_cfg;  /**< Click config object. */

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
    silentstep3_cfg_setup( &silentstep3_cfg );
    SILENTSTEP3_MAP_MIKROBUS( silentstep3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == silentstep3_init( &silentstep3, &silentstep3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP3_ERROR == silentstep3_default_cfg ( &silentstep3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    silentstep3_set_direction ( &silentstep3, SILENTSTEP3_DIR_CW );
    silentstep3_set_step_mode ( &silentstep3, SILENTSTEP3_MODE_FULL_STEP );
    silentstep3_drive_motor ( &silentstep3, 200, SILENTSTEP3_SPEED_SLOW );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    silentstep3_set_direction ( &silentstep3, SILENTSTEP3_DIR_CCW );
    silentstep3_set_step_mode ( &silentstep3, SILENTSTEP3_MODE_HALF_STEP );
    silentstep3_drive_motor ( &silentstep3, 200, SILENTSTEP3_SPEED_MEDIUM );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    silentstep3_set_direction ( &silentstep3, SILENTSTEP3_DIR_CCW );
    silentstep3_set_step_mode ( &silentstep3, SILENTSTEP3_MODE_QUARTER_STEP );
    silentstep3_drive_motor ( &silentstep3, 400, SILENTSTEP3_SPEED_FAST );
    Delay_ms ( 2000 );
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

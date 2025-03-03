/*!
 * @file main.c
 * @brief Silent Step Click example
 *
 * # Description
 * This example demonstrates the use of the Silent Step Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
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
#include "silentstep.h"

static silentstep_t silentstep;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep_cfg_t silentstep_cfg;  /**< Click config object. */

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
    silentstep_cfg_setup( &silentstep_cfg );
    SILENTSTEP_MAP_MIKROBUS( silentstep_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == silentstep_init( &silentstep, &silentstep_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP_ERROR == silentstep_default_cfg ( &silentstep ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    silentstep_set_direction ( &silentstep, SILENTSTEP_DIR_CW );
    silentstep_set_step_res ( &silentstep, SILENTSTEP_MRES_FULLSTEP );
    silentstep_drive_motor ( &silentstep, 200, SILENTSTEP_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    silentstep_set_direction ( &silentstep, SILENTSTEP_DIR_CCW );
    silentstep_set_step_res ( &silentstep, SILENTSTEP_MRES_2 );
    silentstep_drive_motor ( &silentstep, 200, SILENTSTEP_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    silentstep_set_direction ( &silentstep, SILENTSTEP_DIR_CCW );
    silentstep_set_step_res ( &silentstep, SILENTSTEP_MRES_4 );
    silentstep_drive_motor ( &silentstep, 400, SILENTSTEP_SPEED_FAST );
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

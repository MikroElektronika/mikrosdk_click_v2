/*!
 * @file main.c
 * @brief Silent Step 5 Click example
 *
 * # Description
 * This example demonstrates the use of the Silent Step 5 Click board by driving the 
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
#include "silentstep5.h"

#ifndef MIKROBUS_POSITION_SILENTSTEP5
    #define MIKROBUS_POSITION_SILENTSTEP5 MIKROBUS_1
#endif

static silentstep5_t silentstep5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep5_cfg_t silentstep5_cfg;  /**< Click config object. */

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
    silentstep5_cfg_setup( &silentstep5_cfg );
    SILENTSTEP5_MAP_MIKROBUS( silentstep5_cfg, MIKROBUS_POSITION_SILENTSTEP5 );
    err_t init_flag = silentstep5_init( &silentstep5, &silentstep5_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP5_ERROR == silentstep5_default_cfg ( &silentstep5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    silentstep5_set_direction ( &silentstep5, SILENTSTEP5_DIR_CW );
    silentstep5_set_step_res ( &silentstep5, SILENTSTEP5_MRES_FULLSTEP );
    silentstep5_drive_motor ( &silentstep5, 200, SILENTSTEP5_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    silentstep5_set_direction ( &silentstep5, SILENTSTEP5_DIR_CCW );
    silentstep5_set_step_res ( &silentstep5, SILENTSTEP5_MRES_2 );
    silentstep5_drive_motor ( &silentstep5, 200, SILENTSTEP5_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    silentstep5_set_direction ( &silentstep5, SILENTSTEP5_DIR_CCW );
    silentstep5_set_step_res ( &silentstep5, SILENTSTEP5_MRES_4 );
    silentstep5_drive_motor ( &silentstep5, 400, SILENTSTEP5_SPEED_FAST );
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

/*!
 * @file main.c
 * @brief Stepper 6 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 6 click board by driving the 
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
#include "stepper6.h"

static stepper6_t stepper6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper6_cfg_t stepper6_cfg;  /**< Click config object. */

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
    stepper6_cfg_setup( &stepper6_cfg );
    STEPPER6_MAP_MIKROBUS( stepper6_cfg, MIKROBUS_1 );
    err_t init_flag = stepper6_init( &stepper6, &stepper6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER6_ERROR == stepper6_default_cfg ( &stepper6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper6_set_direction ( &stepper6, STEPPER6_DIR_CW );
    stepper6_set_step_mode ( &stepper6, STEPPER6_MODE_FULL_STEP );
    stepper6_drive_motor ( &stepper6, 200, STEPPER6_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper6_set_direction ( &stepper6, STEPPER6_DIR_CCW );
    stepper6_set_step_mode ( &stepper6, STEPPER6_MODE_HALF_STEP );
    stepper6_drive_motor ( &stepper6, 200, STEPPER6_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper6_set_direction ( &stepper6, STEPPER6_DIR_CCW );
    stepper6_set_step_mode ( &stepper6, STEPPER6_MODE_QUARTER_STEP );
    stepper6_drive_motor ( &stepper6, 400, STEPPER6_SPEED_FAST );
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

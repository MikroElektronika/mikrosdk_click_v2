/*!
 * @file main.c
 * @brief Stepper 8 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 8 Click board by driving the 
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
#include "stepper8.h"

static stepper8_t stepper8;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper8_cfg_t stepper8_cfg;  /**< Click config object. */

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
    stepper8_cfg_setup( &stepper8_cfg );
    STEPPER8_MAP_MIKROBUS( stepper8_cfg, MIKROBUS_1 );
    err_t init_flag = stepper8_init( &stepper8, &stepper8_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER8_ERROR == stepper8_default_cfg ( &stepper8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper8_set_direction ( &stepper8, STEPPER8_DIR_CW );
    stepper8_set_step_mode ( &stepper8, STEPPER8_MODE_FULL_STEP );
    stepper8_drive_motor ( &stepper8, 200, STEPPER8_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper8_set_direction ( &stepper8, STEPPER8_DIR_CCW );
    stepper8_set_step_mode ( &stepper8, STEPPER8_MODE_HALF_STEP );
    stepper8_drive_motor ( &stepper8, 200, STEPPER8_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper8_set_direction ( &stepper8, STEPPER8_DIR_CCW );
    stepper8_set_step_mode ( &stepper8, STEPPER8_MODE_QUARTER_STEP );
    stepper8_drive_motor ( &stepper8, 400, STEPPER8_SPEED_FAST );
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

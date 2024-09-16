/*!
 * @file main.c
 * @brief Stepper 22 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 22 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
 * steps and 400 quarter steps with a 1 second delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper22.h"

static stepper22_t stepper22;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper22_cfg_t stepper22_cfg;  /**< Click config object. */

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
    stepper22_cfg_setup( &stepper22_cfg );
    STEPPER22_MAP_MIKROBUS( stepper22_cfg, MIKROBUS_1 );
    err_t init_flag = stepper22_init( &stepper22, &stepper22_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER22_ERROR == stepper22_default_cfg ( &stepper22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper22_set_direction ( &stepper22, STEPPER22_DIR_CW );
    stepper22_set_step_mode ( &stepper22, STEPPER22_MODE_FULL_STEP );
    stepper22_drive_motor ( &stepper22, 200, STEPPER22_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper22_set_direction ( &stepper22, STEPPER22_DIR_CCW );
    stepper22_set_step_mode ( &stepper22, STEPPER22_MODE_HALF_STEP );
    stepper22_drive_motor ( &stepper22, 200, STEPPER22_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper22_set_direction ( &stepper22, STEPPER22_DIR_CCW );
    stepper22_set_step_mode ( &stepper22, STEPPER22_MODE_QUARTER_STEP );
    stepper22_drive_motor ( &stepper22, 400, STEPPER22_SPEED_FAST );
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

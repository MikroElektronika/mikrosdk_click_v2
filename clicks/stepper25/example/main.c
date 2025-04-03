/*!
 * @file main.c
 * @brief Stepper 25 Click example
 *
 * # Description
 * This example demonstrates the operation of the Stepper 25 Click board, 
 * which is used to control a bipolar stepper motor. The application initializes 
 * the board and executes different step modes, directions, and speeds to 
 * showcase precise motor control.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and Stepper 25 Click board. Configures the motor driver 
 * with default settings, preparing it for stepper motor control.
 *
 * ## Application Task
 * Moves the stepper motor in different step modes and directions at varying speeds. 
 * The motor completes a predefined number of steps in each mode, switching between 
 * clockwise (CW) and counterclockwise (CCW) directions with different step resolutions.
 *
 * @note
 * Ensure proper power supply and motor connections before running the example.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper25.h"

static stepper25_t stepper25;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper25_cfg_t stepper25_cfg;  /**< Click config object. */

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
    stepper25_cfg_setup( &stepper25_cfg );
    STEPPER25_MAP_MIKROBUS( stepper25_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == stepper25_init( &stepper25, &stepper25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER25_ERROR == stepper25_default_cfg ( &stepper25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Step mode: 1/16\r\n" );
    log_printf ( &logger, " Direction: CW\r\n" );
    log_printf ( &logger, " Steps: 1600\r\n" );
    log_printf ( &logger, " Speed: Medium\r\n\n" );
    stepper25_set_direction ( &stepper25, STEPPER25_DIR_CW );
    stepper25_set_step_mode ( &stepper25, STEPPER25_STEP_MODE_1_OVER_16 );
    stepper25_drive_motor ( &stepper25, 1600, STEPPER25_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/8\r\n" );
    log_printf ( &logger, " Direction: CCW\r\n" );
    log_printf ( &logger, " Steps: 1600\r\n" );
    log_printf ( &logger, " Speed: Fast\r\n\n" );
    stepper25_set_direction ( &stepper25, STEPPER25_DIR_CCW );
    stepper25_set_step_mode ( &stepper25, STEPPER25_STEP_MODE_1_OVER_8 );
    stepper25_drive_motor ( &stepper25, 1600, STEPPER25_SPEED_FAST );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/4\r\n" );
    log_printf ( &logger, " Direction: CW\r\n" );
    log_printf ( &logger, " Steps: 400\r\n" );
    log_printf ( &logger, " Speed: Slow\r\n\n" );
    stepper25_set_direction ( &stepper25, STEPPER25_DIR_CW );
    stepper25_set_step_mode ( &stepper25, STEPPER25_STEP_MODE_QUARTER );
    stepper25_drive_motor ( &stepper25, 400, STEPPER25_SPEED_SLOW );
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

/*!
 * @file main.c
 * @brief Stepper 31 Click example
 *
 * # Description
 * This example demonstrates the use of Stepper 31 Click by driving a bipolar
 * stepper motor in both directions for a specified number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Click driver, verifies expander communication,
 * and selects the stepping mode while leaving both motor windings off.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockwise for
 * 200 half steps and 400 quarter steps, with a 1 second pause on mode change.
 * Each move is logged before starting. The driver checks fault inputs during
 * motion and de-energizes the windings when the move ends.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper31.h"

#ifndef MIKROBUS_POSITION_STEPPER31
    #define MIKROBUS_POSITION_STEPPER31 MIKROBUS_1
#endif

static stepper31_t stepper31;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper31_cfg_t stepper31_cfg;  /**< Click config object. */

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
    stepper31_cfg_setup( &stepper31_cfg );
    STEPPER31_MAP_MIKROBUS( stepper31_cfg, MIKROBUS_POSITION_STEPPER31 );
    if ( SPI_MASTER_ERROR == stepper31_init( &stepper31, &stepper31_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER31_ERROR == stepper31_default_cfg ( &stepper31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper31_set_direction( &stepper31, STEPPER31_DIR_CW );
    stepper31_set_step_mode( &stepper31, STEPPER31_MODE_FULL_STEP );
    if ( STEPPER31_ERROR == stepper31_drive_motor( &stepper31, 200, STEPPER31_SPEED_SLOW ) )
    {
        log_error( &logger, " Motor movement or driver fault." );
        for ( ; ; );
    }
    Delay_ms( 1000 );

    log_printf( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper31_set_direction( &stepper31, STEPPER31_DIR_CCW );
    stepper31_set_step_mode( &stepper31, STEPPER31_MODE_HALF_STEP );
    if ( STEPPER31_ERROR == stepper31_drive_motor( &stepper31, 200, STEPPER31_SPEED_MEDIUM ) )
    {
        log_error( &logger, " Motor movement or driver fault." );
        for ( ; ; );
    }
    Delay_ms( 1000 );

    log_printf( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper31_set_direction( &stepper31, STEPPER31_DIR_CCW );
    stepper31_set_step_mode( &stepper31, STEPPER31_MODE_QUARTER_STEP );
    if ( STEPPER31_ERROR == stepper31_drive_motor( &stepper31, 400, STEPPER31_SPEED_FAST ) )
    {
        log_error( &logger, " Motor movement or driver fault." );
        for ( ; ; );
    }
    Delay_ms( 1000 );
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

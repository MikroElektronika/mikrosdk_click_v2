/*!
 * @file main.c
 * @brief MultiStepperTB67S209 Click example
 *
 * # Description
 * This example demonstrates the use of the Multi Stepper TB67S209 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 steps and then counter-clockiwse for 100 steps with
 * 2 seconds delay before changing the direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "multisteppertb67s209.h"

static multisteppertb67s209_t multisteppertb67s209;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    multisteppertb67s209_cfg_t multisteppertb67s209_cfg;  /**< Click config object. */

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
    multisteppertb67s209_cfg_setup( &multisteppertb67s209_cfg );
    MULTISTEPPERTB67S209_MAP_MIKROBUS( multisteppertb67s209_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == multisteppertb67s209_init( &multisteppertb67s209, &multisteppertb67s209_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MULTISTEPPERTB67S209_ERROR == multisteppertb67s209_default_cfg ( &multisteppertb67s209 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
    multisteppertb67s209_set_direction ( &multisteppertb67s209, MULTISTEPPERTB67S209_DIR_CW );
    multisteppertb67s209_drive_motor ( &multisteppertb67s209, 200, MULTISTEPPERTB67S209_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
    multisteppertb67s209_set_direction ( &multisteppertb67s209, MULTISTEPPERTB67S209_DIR_CCW );
    multisteppertb67s209_drive_motor ( &multisteppertb67s209, 100, MULTISTEPPERTB67S209_SPEED_FAST );
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

/*!
 * @file main.c
 * @brief MultiStepperTB62261 Click example
 *
 * # Description
 * This example demonstrates the use of the Multi Stepper TB62261 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
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
#include "multisteppertb62261.h"

static multisteppertb62261_t multisteppertb62261;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    multisteppertb62261_cfg_t multisteppertb62261_cfg;  /**< Click config object. */

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
    multisteppertb62261_cfg_setup( &multisteppertb62261_cfg );
    MULTISTEPPERTB62261_MAP_MIKROBUS( multisteppertb62261_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == multisteppertb62261_init( &multisteppertb62261, &multisteppertb62261_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MULTISTEPPERTB62261_ERROR == multisteppertb62261_default_cfg ( &multisteppertb62261 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    multisteppertb62261_set_direction ( &multisteppertb62261, MULTISTEPPERTB62261_DIR_CW );
    if ( MULTISTEPPERTB62261_OK == multisteppertb62261_drive_motor ( &multisteppertb62261, 200, 
                                                                     MULTISTEPPERTB62261_SPEED_FAST ) )
    {
        log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
        Delay_ms ( 2000 );
    }
    
    multisteppertb62261_set_direction ( &multisteppertb62261, MULTISTEPPERTB62261_DIR_CCW );
    if ( MULTISTEPPERTB62261_OK == multisteppertb62261_drive_motor ( &multisteppertb62261, 100,
                                                                     MULTISTEPPERTB62261_SPEED_FAST ) )
    {
        log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
        Delay_ms ( 2000 );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END

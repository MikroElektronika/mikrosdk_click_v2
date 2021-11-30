/*!
 * @file main.c
 * @brief DC Motor 21 Click Example.
 *
 * # Description
 * This example demonstrates the use of DC Motor 21 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * In the span of six seconds, it drives the motor in one direction, then switches the direction, 
 * and after that disconnects the motor. Each step will be logged on the USB UART where
 * you can track the program flow.
 * 
 * @note
 * For this example, a DC motor should be connected to OUT1 and OUT2 lines.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor21.h"

static dcmotor21_t dcmotor21;   /**< DC Motor 21 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor21_cfg_t dcmotor21_cfg;  /**< Click config object. */

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
    dcmotor21_cfg_setup( &dcmotor21_cfg );
    DCMOTOR21_MAP_MIKROBUS( dcmotor21_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor21_init( &dcmotor21, &dcmotor21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    dcmotor21_default_cfg ( &dcmotor21 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_LOW );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_HIGH );
    log_printf( &logger, " \r\n Driving the motor...\r\n" );
    Delay_ms( 2000 );
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_HIGH );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_LOW );
    log_printf( &logger, " Switch direction.\r\n" );
    Delay_ms( 2000 );
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_HIGH_Z );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_HIGH_Z );
    log_printf( &logger, " The motor is disconnected.\r\n" );
    Delay_ms( 2000 );
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

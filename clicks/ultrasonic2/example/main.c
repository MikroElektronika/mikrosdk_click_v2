/*!
 * @file main.c
 * @brief Ultrasonic 2 Click Example.
 *
 * # Description
 * This example measures the distance to the first object detected by Ultrasonic 2 Click
 * and displays the result in millimetres on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the UART, enables the boost converter and loads the 40 kHz ranging profile.
 *
 * ## Application Task
 * Reads one distance measurement, displays the result or an error, and waits 500 ms.
 *
 * @note
 * Connect an external pull-up resistor from mikroBUS RX (PGA460 TXD) to a logic rail
 * compatible with the host UART input. PGA460 TXD is high impedance between replies.
 * Distance conversion uses a speed of sound of 343 m/s and the configured profile timing compensation.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ultrasonic2.h"

#ifndef MIKROBUS_POSITION_ULTRASONIC2
    #define MIKROBUS_POSITION_ULTRASONIC2 MIKROBUS_1
#endif

static ultrasonic2_t ultrasonic2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic2_cfg_t ultrasonic2_cfg;  /**< Click config object. */

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
    ultrasonic2_cfg_setup( &ultrasonic2_cfg );
    ULTRASONIC2_MAP_MIKROBUS( ultrasonic2_cfg, MIKROBUS_POSITION_ULTRASONIC2 );
    if ( UART_ERROR == ultrasonic2_init( &ultrasonic2, &ultrasonic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    // Apply the receiver and threshold profile once after each power-up.
    if ( ULTRASONIC2_OK != ultrasonic2_default_cfg( &ultrasonic2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    ultrasonic2_measurement_t measurement;

    // The library completes one burst and validates its reply before updating the measurement.
    err_t status = ultrasonic2_get_measurement( &ultrasonic2, &measurement );
    if ( ULTRASONIC2_OK == status )
    {
        log_printf( &logger, " Distance: %u mm\r\n", measurement.distance_mm );
    }
    else if ( ULTRASONIC2_NO_OBJECT == status )
    {
        log_info( &logger, " No object detected." );
    }
    else
    {
        log_error( &logger, " Measurement failed." );
    }

    // Leave a quiet interval between bursts and limit the terminal output rate.
    Delay_ms( 500 );
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

/*!
 * @file main.c
 * @brief C Meter Click Example.
 *
 * # Description
 * This example demonstrates the use of the C Meter Click board by measuring the
 * capacitance of an external capacitor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the zero calibration with the measurement
 * input left open.
 *
 * ## Application Task
 * Measures the capacitance of the connected capacitor and logs the result in nF
 * on the USB UART once per second.
 *
 * @note
 * Leave the measurement input ( TB1 terminal, J1 socket and the SMD pads ) open
 * during the zero calibration, and connect the capacitor afterwards.
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "cmeter.h"

#ifndef MIKROBUS_POSITION_CMETER
    #define MIKROBUS_POSITION_CMETER MIKROBUS_1
#endif

// Application wait macros
#define CALIBRATION_WAIT_S      5
#define MEASUREMENT_WAIT_S      30

static cmeter_t cmeter;   /**< C Meter Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cmeter_cfg_t cmeter_cfg;  /**< Click config object. */

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
    cmeter_cfg_setup( &cmeter_cfg );
    CMETER_MAP_MIKROBUS( cmeter_cfg, MIKROBUS_POSITION_CMETER );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == cmeter_init( &cmeter, &cmeter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    uint8_t cnt = 0;

    /* On-board CX measurement as a reference */
    log_printf( &logger, " Leave the measurement input open for zero calibration.\r\n" );
    log_printf( &logger, " Calibration starts in %u seconds.\r\n\n", ( uint16_t ) CALIBRATION_WAIT_S );
    for ( cnt = 0; CALIBRATION_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
    if ( CMETER_ERROR == cmeter_calibrate( &cmeter ) )
    {
        log_error( &logger, " Calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Zero reference : %.2f loop passes per period\r\n\n", cmeter.zero_period );

    /* Measurement start with an external capacitor connected */
    log_printf( &logger, " Connect the capacitor.\r\n" );
    log_printf( &logger, " Measurement starts in %u seconds.\r\n\n", ( uint16_t ) MEASUREMENT_WAIT_S );
    for ( cnt = 0; MEASUREMENT_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float capacitance = 0;

    if ( CMETER_OK == cmeter_get_capacitance( &cmeter, &capacitance ) )
    {
        log_printf( &logger, " Capacitance : %.3f nF\r\n", capacitance );
    }
    else
    {
        log_printf( &logger, " Measurement failed, check the connected capacitor.\r\n" );
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

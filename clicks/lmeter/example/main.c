/*!
 * @file main.c
 * @brief L meter Click Example.
 *
 * # Description
 * This example demonstrates the use of the L meter Click board by measuring the
 * inductance of an external coil. The inductance is calculated from the ratio of
 * the edge count measured with the input shorted and the edge count measured
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and takes the zero reference with the 
 * measurement input shorted and checks that the oscillator
 * responds to the on-board calibration capacitor C2.
 *
 * ## Application Task
 * Measures the inductance of the connected coil and displays the result on the
 * USB UART once per second.
 *
 * @note
 * Short the measurement input ( TB1 terminal, TS2 header or the probe tips )
 * before the zero calibration and remove the short afterwards.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "lmeter.h"

#ifndef MIKROBUS_POSITION_LMETER
    #define MIKROBUS_POSITION_LMETER MIKROBUS_1
#endif

// Aplication wait makros
#define CALIBRATION_WAIT_S      10
#define MEASUREMENT_WAIT_S      30

static lmeter_t lmeter;   /**< L meter Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lmeter_cfg_t lmeter_cfg;  /**< Click config object. */

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
    lmeter_cfg_setup( &lmeter_cfg );
    LMETER_MAP_MIKROBUS( lmeter_cfg, MIKROBUS_POSITION_LMETER );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == lmeter_init( &lmeter, &lmeter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint32_t cap_on_count = 0;
    uint16_t cnt = 0;

    /* L1 on-board coil measurement as a reference */
    log_printf( &logger, " Short the measurement input for zero calibration.\r\n" );
    log_printf( &logger, " Calibration starts in %u seconds.\r\n\n", ( uint16_t ) CALIBRATION_WAIT_S );
    for ( cnt = 0; CALIBRATION_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
    if ( LMETER_ERROR == lmeter_calibrate( &lmeter ) )
    {
        log_error( &logger, " Calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Zero reference : %lu counts\r\n", lmeter.zero_count );

    /* Add the on-board C2 to the LC tank to see if it changes the counts as intended */
    lmeter_set_cal_cap( &lmeter, LMETER_CAL_CAP_ENABLE );
    if ( LMETER_OK == lmeter_measure_counts( &lmeter, &cap_on_count ) )
    {
        log_printf( &logger, " C2 connected : %lu counts\r\n\n", cap_on_count );
    }
    lmeter_set_cal_cap( &lmeter, LMETER_CAL_CAP_DISABLE );

    /* Measurement start with an external coil connected */
    log_printf( &logger, " Remove the short and connect the coil.\r\n" );
    log_printf( &logger, " Measurement starts in %u seconds.\r\n\n", ( uint16_t ) MEASUREMENT_WAIT_S );
    for ( cnt = 0; MEASUREMENT_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
        
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float inductance = 0;

    if ( LMETER_OK == lmeter_get_inductance( &lmeter, &inductance ) )
    {
        log_printf( &logger, " Inductance : %.1f uH\r\n\n", inductance );
    }
    else
    {
        log_error( &logger, " Failed to get inductance" );
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

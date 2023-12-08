/*!
 * \file 
 * \brief Diff pressure Click example
 * 
 * # Description
 * This application is temperature compensated and calibrated pressure sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Diff Pressure click board.
 * The example reads the values of ADC module (MPC3551) 22-bit register value
 * converted to voltage and the pressure difference [ Pa ] and displays
 * those values on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "diffpressure.h"

// ------------------------------------------------------------------ VARIABLES

static diffpressure_t diffpressure;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpressure_cfg_t cfg;

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
    diffpressure_cfg_setup( &cfg );
    DIFFPRESSURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( DIFFPRESSURE_OK != diffpressure_init( &diffpressure, &cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float adc_voltage = 0;
    int32_t difference = 0;

    adc_voltage = diffpressure_read_adc_voltage( &diffpressure );
    difference = diffpressure_get_pa_difference( &diffpressure, adc_voltage );

    log_printf( &logger, " ADC Voltage: %.3f [V]\r\n", adc_voltage );

    log_printf( &logger, " Pressure Diff: %ld [Pa]\r\n\n", difference );

    Delay_ms( 100 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END

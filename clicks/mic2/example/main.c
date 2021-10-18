/*!
 * \file 
 * \brief Mic2 Click example
 * 
 * # Description
 * This range is  suited for audio and/or speech applications. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, ADC init and sets digital pot.
 * 
 * ## Application Task  
 * Reads ADC data calculates dB value and logs data to serial plotter.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic2.h"
#include "math.h"

// ------------------------------------------------------------------ VARIABLES
uint16_t plot_time;
static mic2_t mic2;
static log_t logger;
 
static mic2_data_t adc_value;

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mic2_cfg_setup( &cfg );
    MIC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic2_init( &mic2, &cfg );

    mic2_set_potentiometer( &mic2, 35 );
}

void application_task ( void )
{
    adc_value = mic2_generic_read ( &mic2 );
    
    float db_val = ( adc_value + 83.2073 ) / 11.003;
    log_printf( &logger, "%.2f dB\r\n", db_val );
    
    Delay_ms( 100 );
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

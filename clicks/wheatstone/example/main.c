/*!
 * \file 
 * \brief Wheatstone Click example
 * 
 * # Description
 * This example demonstrates the use of Wheatstone click board by measuring the input
 * resistance.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger and sets the default potentiometer (gain) level.
 * 
 * ## Application Task  
 * Reads the AN pin voltage and calculates the input resistance from it.
 * All data are being displayed on the USB UART where you can track their changes.
 * 
 * @note
 * The following formulas you may find useful:
 * AN_PIN(V) = ( ( 1kOhm + R_INPUT(kOhm) ) / ( 1kOhm + 2*R_INPUT(kOhm) ) - 1/2 ) * VCC(V) * GAIN
 * VOUT(V) = AN_PIN(V) / GAIN
 * R_INPUT(kOhm) = ( VCC(V) * GAIN - 2*AN_PIN(V) ) / ( 4*AN_PIN(V) )
 * R_INPUT(kOhm) = ( VCC(V) - 2*VOUT(V) ) / ( 4*VOUT(V) )
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wheatstone.h"

// ------------------------------------------------------------------ VARIABLES

static wheatstone_t wheatstone;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wheatstone_cfg_t cfg;

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
    wheatstone_cfg_setup( &cfg );
    WHEATSTONE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wheatstone_init( &wheatstone, &cfg );

    wheatstone_set_potentiometer ( &wheatstone, WHEATSTONE_POT_MAX );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float an_pin_v = 0;
    float vout = 0;
    float r_kohm = 0;
    if ( WHEATSTONE_OK == wheatstone_read_an_pin_voltage ( &wheatstone, &an_pin_v ) ) 
    {
        vout = an_pin_v / wheatstone.gain;
        if ( 0 != vout )
        {
            r_kohm = ( WHEATSTONE_VCC_5V - 2 * vout ) / ( 4 * vout );
        }
        log_printf( &logger, " VCC     : %.3f V\r\n", WHEATSTONE_VCC_5V );
        log_printf( &logger, " GAIN    : %.3f\r\n", wheatstone.gain );
        log_printf( &logger, " AN_PIN  : %.3f V\r\n", an_pin_v );
        log_printf( &logger, " VOUT    : %.3f V\r\n", vout );
        log_printf( &logger, " R_INPUT : %.3f kOhm\r\n\n", r_kohm );
        Delay_ms( 1000 );
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

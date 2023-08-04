/*!
 * @file 
 * @brief Ambient7 Click example
 * 
 * # Description
 * Reads the AN pin voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes ADC and LOG for logging data.
 * 
 * ## Application Task  
 * Reads the AN pin voltage and displays the results on the USB UART once per second.
 * 
 * @note 
 * Illuminance range [ EV ] - from 0.01 [ lx ] to 10k [ lx ] 
 * 
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient7.h"

static ambient7_t ambient7;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient7_cfg_t cfg;

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
    ambient7_cfg_setup( &cfg );
    AMBIENT7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient7_init( &ambient7, &cfg );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    if ( AMBIENT7_OK == ambient7_read_an_pin_voltage ( &ambient7, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
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

/*!
 * \file 
 * \brief Mic2 Click example
 * 
 * # Description
 * This range is suited for audio and/or speech applications.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger and sets the digital potentiometer.
 * 
 * ## Application Task  
 * Reads the AN pin voltage and displays the results on the USB UART every 100ms.
 * 
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "mic2.h"

static mic2_t mic2;
static log_t logger;
 
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
    log_info( &logger, " Application Init " );

    // Click initialization.
    mic2_cfg_setup( &cfg );
    MIC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic2_init( &mic2, &cfg );

    mic2_set_potentiometer( &mic2, 35 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    if ( MIC2_OK == mic2_read_an_pin_voltage ( &mic2, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms( 100 );
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

/*!
 * \file 
 * \brief Noise click example
 * 
 * # Description
 * This example performs an ambient noise monitoring using the Noise click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Device initialization.
 * 
 * ## Application Task  
 * Reads the voltage from AN pin which presents the noise level and displays it
 * on the USB UART every 5ms. If the noise is above predefined threshold
 * (25 percents of max noise, i.e. about 0.4V) an alarm message is being shown.
 * 
 * @note 
 * We recommend using the SerialPlot tool for data visualizing.
 * 
 * \author MikroE Team
 *
 */
#include "board.h"
#include "log.h"
#include "noise.h"

static noise_t noise;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    noise_cfg_t cfg;

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
    noise_cfg_setup( &cfg );
    NOISE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    noise_init( &noise, &cfg );

    noise_default_cfg( &noise );
}

void application_task ( void )
{
    float voltage = 0;
    if ( NOISE_OK == noise_read_an_pin_voltage ( &noise, &voltage ) )
    {
        log_printf( &logger, "%.3f\r\n", voltage );
    }
    if ( noise_check_int_pin( &noise ) )
    {
        log_printf( &logger, " Sound overlimit detected!\r\n" );
    }
    Delay_ms ( 5 );
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

/*!
 * \file 
 * \brief Force4 Click example
 * 
 * # Description
 * This example shows the use of Force 4 Click.
 * It reads 12bit ADC value, using I2C communication,
 * at the interval of one second. 
 * The result is represented on the UART terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger, and makes an initial log.
 * 
 * ## Application Task  
 * It reads 12bit ADC value, using I2C communication,
 * at the interval of one second.
 * The result is represented on the UART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force4.h"

// ------------------------------------------------------------------ VARIABLES

static force4_t force4;
static log_t logger;

uint16_t adc_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    force4_cfg_t cfg;

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
    Delay_ms( 100 );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    force4_cfg_setup( &cfg );
    FORCE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force4_init( &force4, &cfg );
    Delay_ms( 100 );
}

void application_task ( void )
{
    adc_val = force4_read_adc( &force4 );
    log_printf( &logger, "ADC value: %d\r\n", adc_val );
    Delay_ms( 1000 );
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

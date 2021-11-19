/*!
 * \file 
 * \brief Mic Click example
 * 
 * # Description
 * This example showcases the initialization and configuration of the click and logger
 * modules and later on reads and displays data recorded by the mic.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes LOG communication, ADC and configures AN pin as input on MIKROBUS1.
 * 
 * ## Application Task  
 * Reads 12 bit ADC data from AN pin and displays it using the logger module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic.h"

// ------------------------------------------------------------------ VARIABLES

static mic_t mic;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic_cfg_t cfg;

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

    mic_cfg_setup( &cfg );
    MIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic_init( &mic, &cfg );
}

void application_task ( void )
{
    mic_data_t tmp;
    
    //  Task implementation.
    
    tmp = mic_generic_read ( &mic );

    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );

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

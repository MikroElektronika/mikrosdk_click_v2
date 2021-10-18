/*!
 * \file 
 * \brief Force3 Click example
 * 
 * # Description
 * This application demonstrates the use of Force 3 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * Reads the sensor raw data and displays it on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force3.h"

// ------------------------------------------------------------------ VARIABLES

static force3_t force3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    force3_cfg_t cfg;

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

    force3_cfg_setup( &cfg );
    FORCE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force3_init( &force3, &cfg );
}

void application_task ( void )
{
    uint16_t raw_data;

    raw_data = force3_read_raw_data( &force3 );
    log_printf( &logger, "Raw data: %d \r\n", raw_data );

    if ( ( raw_data > 5 ) && ( raw_data <= 200 ) )
    {
       log_printf( &logger, ">> Light touch \r\n" );
    }
    else if ( ( raw_data > 200 ) && ( raw_data <= 500 ) )
    {
       log_printf( &logger, ">> Light squeeze \r\n" );
    }
    else if ( ( raw_data > 500 ) && ( raw_data <= 800 ) )
    {
       log_printf( &logger, ">> Medium squeeze \r\n" );
    }
    else if ( raw_data > 800 )
    {
       log_printf( &logger, ">> Big squeeze \r\n" );
    }
    
    log_printf( &logger, "----------------------\r\n" );
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

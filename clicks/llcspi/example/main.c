/*!
 * \file 
 * \brief llcspi Click example
 * 
 * # Description
 * This application is converter for logic signals.
 *
 * The demo application is composed of two sections : 
 * 
 * ## Application Init 
 * Initialization device init
 * 
 * ## Application Task  
 * Counter passes through the loop and logs the value of the counter on the bargraph display
 * 
 * *note:* 
 * Connection between BarGraph and LLC-SPI is made through SPI interface.
 * You can connect a BarGraph click to LLC-SPI click with the wires to make connection between click boards.
 * We use the BarGraph click to demonstrate the functions of the LLC-SPI click.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "llcspi.h"

// ------------------------------------------------------------------ VARIABLES

static llcspi_t llcspi;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    llcspi_cfg_t cfg;

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

    llcspi_cfg_setup( &cfg );
    LLCSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llcspi_init( &llcspi, &cfg );
}

void application_task ( void )
{
    uint16_t convert;
    uint8_t tmp[ 2 ];
    uint8_t cnt;

    // BarGraph display
    for ( cnt = 0; cnt <= 10; cnt++ )
    {
        convert  = ( uint16_t ) ( ( 1 << cnt ) - 1 );
        tmp[ 1 ] = ( convert & 0x00FF );
        tmp[ 0 ] = ( convert & 0xFF00 ) >> 8;
    
        llcspi_generic_write( &llcspi, tmp, 2 );
        
        Delay_ms( 1000 );
    }
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

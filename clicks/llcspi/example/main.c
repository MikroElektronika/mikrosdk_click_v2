/*!
 * \file 
 * \brief LlcSpi Click example
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
 * Connection between BarGraph and SPI-LLC is made through SPI interface.
 * You can connect a BarGraph click and SPI-LLC click with the wires to make connection between click boards.
 * We use the BarGraph click to demonstrate the functions of the SPI-LLC click.
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

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    llcspi_cfg_setup( &cfg );
    LLCSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llcspi_init( &llcspi, &cfg );
}

void application_task ( void )
{
    spi_master_transfer_data_t block;
    uint16_t convert;
    uint8_t tmp[ 2 ];
    uint8_t cnt;

    // Bar_graph display
    for ( cnt = 0; cnt <= 10; cnt++ )
    {
        convert  = ( uint16_t ) ( ( 1 << cnt ) - 1 );
        tmp[ 1 ] = ( convert & 0x00FF );
        tmp[ 0 ] = ( convert & 0xFF00 ) >> 8;

        block.tx_buffer = &tmp[ 0 ];
        block.tx_length = 2;
        block.rx_buffer = NULL;
        block.rx_length = 0;
    
        llcspi_generic_transfer( &llcspi, &block );
        
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

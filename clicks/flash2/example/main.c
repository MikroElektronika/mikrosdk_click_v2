/*!
 * \file 
 * \brief Flash2 Click example
 * 
 * # Description
 * This application demonstrates the process of writing and reading data from Flash 2 click memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Flash Driver Initialization, initialization of click by setting mikorBUS to
 * approprieate logic levels, performing global block unlock and chip erase functions.
 * 
 * ## Application Task  
 * Writing data to click memory and displaying the read data via UART. 
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flash2.h"

// ------------------------------------------------------------------ VARIABLES

static flash2_t flash2;
static log_t logger;

char wr_data[ 10 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10 , 0 };
char rd_data[ 10 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    flash2_cfg_setup( &cfg );
    FLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash2_init( &flash2, &cfg );
    Delay_ms( 300 );
    flash2_global_block_unlock( &flash2 );
    Delay_ms( 400 );
    flash2_chip_erase( &flash2 );
    Delay_ms( 300 );
}

void application_task ( void )
{
    log_printf( &logger, "Writing MikroE to flash memory, from address 0x015015:\r\n" );
    flash2_write_generic( &flash2, 0x015015, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of flash memory, from address 0x015015:\r\n" );
    flash2_read_generic( &flash2, 0x015015, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %s\r\n", rd_data );
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

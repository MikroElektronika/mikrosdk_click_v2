/*!
 * \file 
 * \brief Flash4 Click example
 * 
 * # Description
 * This application for the mass storage option in various embedded applications.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device and reset device.
 * 
 * ## Application Task  
 * Erases memory at 0x00001234.
   Writes a message (MikroElektronika) to address 0x00001234.
   Then reads the data from the address 0x00001234.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flash4.h"

// ------------------------------------------------------------------ VARIABLES

static flash4_t flash4;
static log_t logger;

static uint8_t data_buffer[ 17 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    flash4_cfg_setup( &cfg );
    FLASH4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash4_init( &flash4, &cfg );
    
    flash4_reset( &flash4 );
}

void application_task ( void )
{
    char read_buffer[ 20 ];
    uint8_t cnt;

    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    log_printf( &logger, "--- Erase chip --START-- \r\n" );
    flash4_4sector_erase( &flash4,  0x00001234 );
    while ( flash4_check_wip( &flash4 ) );
    log_printf( &logger, "--- Erase chip --DONE-- \r\n" );
    
    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    flash4_4_page_program( &flash4, data_buffer, 0x00001234, 16 );
    while ( flash4_check_wip( &flash4 ) );
    Delay_100ms( );
    
    flash4_read_flash( &flash4, read_buffer, 0x00001234, 16 );
    while ( flash4_check_wip( &flash4 ) );
    
    log_printf( &logger, "--- Read buffer : " );
    log_printf( &logger, "---- %s", read_buffer );
  
    log_printf( &logger, "\r\n" );

    Delay_ms( 3000 );
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

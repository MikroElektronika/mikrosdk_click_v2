/*!
 * \file 
 * \brief Flash4 Click example
 * 
 * # Description
 * This example demonstrates the use of Flash 4 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the click board, then checks the communication 
 * by reading the device and manufacturer IDs.
 * 
 * ## Application Task  
 * Erases sector memory starting from 0x00001234 address, then writes a desired message
 * to the same address. After that, verifies if the message is written correctly by reading 
 * it back and displaying it to the USB UART every 5 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flash4.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_MESSAGE "MikroE"

static flash4_t flash4;
static log_t logger;

static uint8_t device_id[ 2 ];
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash4_cfg_t cfg;

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

    flash4_cfg_setup( &cfg );
    FLASH4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash4_init( &flash4, &cfg );
    
    flash4_reset( &flash4 );
    
    Delay_ms ( 1000 );
    
    flash4_read_manufacturer_id( &flash4, device_id );
    
    if ( device_id[ 0 ] != FLASH4_MANUFACTURER_ID || device_id[ 1 ] != FLASH4_DEVICE_ID )
    {
        log_error( &logger, "WRONG ID READ" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for( ; ; );
    }
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    char read_buffer[ 10 ] = { 0 };

    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    log_printf( &logger, "--- Erase chip --START-- \r\n" );
    flash4_sector_erase_4( &flash4,  0x00001234 );
    while ( flash4_check_wip( &flash4 ) );
    log_printf( &logger, "--- Erase chip --DONE-- \r\n" );
    
    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    flash4_page_program_4( &flash4, DEMO_MESSAGE, 0x00001234, strlen( DEMO_MESSAGE ) );
    while ( flash4_check_wip( &flash4 ) );
    Delay_100ms( );
    
    flash4_read_flash_4( &flash4, read_buffer, 0x00001234, strlen( DEMO_MESSAGE ) );
    while ( flash4_check_wip( &flash4 ) );
    
    log_printf( &logger, "--- Read buffer : %s\r\n", read_buffer );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END

/*!
 * \file main.c
 * \brief Flash Click example
 *
 * # Description
 * This example demonstrates the use (control) of the FLASH memory.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes all necessary peripherals and pins used by Flash click and also
 * initializes uart logger to show results.
 *
 * ## Application Task
 * Executes memory data writing, reading from the memory to verify data writing
 * operation and sector erasing to clear memory.
 *
 * ## Additional Functions
 * - Enter Data / Allows user to enter a desired data.
 * - Process Wait / Makes a delay to wait while some process be done.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include <string.h>
#include "board.h"
#include "log.h"
#include "flash.h"

// ------------------------------------------------------------------ VARIABLES

static flash_t flash;
static log_t logger;
static uint8_t data_buf[ 30 ];
static uint8_t n_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void enter_data( unsigned char *buffer )
{
    uint8_t data_size;

    data_size = sizeof( data_buf );

    memset( data_buf, 0, data_size );
    n_data = 0;
    data_size--;

    while ( ( *buffer != 0 ) && ( data_size > 0 ) )
    {
        data_buf[ n_data ] = *buffer;
        buffer++;
        n_data++;
        data_size--;
    }
}

void process_wait( void )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 9; cnt++ )
    {
        Delay_ms ( 400 );
        log_printf( &logger, "****" );
    }

    log_printf( &logger, "\r\n" );
    Delay_ms ( 400 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    flash_cfg_t flash_cfg;
    log_cfg_t log_cfg;

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
    flash_cfg_setup( &flash_cfg );
    FLASH_MAP_MIKROBUS( flash_cfg, MIKROBUS_1 );
    flash_init( &flash, &flash_cfg );

    //  Click reset and default configuration.
    flash_reset( &flash );
    flash_default_cfg( &flash );

    log_printf( &logger, "***  Flash Initialization Done.  ***\r\n" );
    log_printf( &logger, "************************************\r\n" );
}

void application_task( void )
{
    enter_data( "Mikroelektronika (MikroE)" );

    log_printf( &logger, "> Data content to be written: %s\r\n", data_buf );
    log_printf( &logger, "> Data writing to memory...\r\n" );
    flash_write_page( &flash, FLASH_MEM_ADDR_FIRST_PAGE_START, data_buf, n_data );
    log_printf( &logger, "> Done.\r\n" );

    memset( data_buf, 0, sizeof( data_buf ) );
    process_wait( );

    log_printf( &logger, "> Data reading from memory...\r\n" );
    flash_read_page( &flash, FLASH_MEM_ADDR_FIRST_PAGE_START, data_buf, n_data );
    log_printf( &logger, "> Done.\r\n> Read data content: %s\r\n", data_buf );

    process_wait( );

    log_printf( &logger, "> Sector erasing...\r\n" );
    flash_erase_sector( &flash, FLASH_MEM_ADDR_FIRST_SECTOR_START );
    log_printf( &logger, "> Done.\r\n" );

    process_wait( );
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

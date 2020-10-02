/*!
 * \file 
 * \brief SemperFlash2 Click example
 * 
 * # Description
 * This example showcases how to initialize and use the Semper Flash 2 click. The click
 * is a 512 Mbit SPI Flash memory module. Data can be stored in and read from the flash
 * memory. There's also the option of erasing it's contents. Here's how to do it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. Additional con-
 * figuring is done in the default_cfg(...) function. The device ID should appear in the 
 * UART console if the setup finishes successfully.
 * 
 * ## Application Task  
 * This function first erases the contents of the flash memory and then writes, reads and
 * prints two strings in the UART console. It does so every 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "semperflash2.h"

// ------------------------------------------------------------------ VARIABLES

static semperflash2_t semperflash2;
static log_t logger;

uint8_t id_data[ 8 ];
uint8_t txt_flag;
uint8_t COMPANY_FLAG = 2;
uint8_t CLICK_FLAG = 3;
uint32_t ADRESS_MEMORY = 0x00001111;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void error_handler ( uint8_t stat )
{
    if ( SEMPERFLASH2_ID_ERROR == stat )
    {
        log_printf( &logger, "ID ERROR!" );
        for ( ; ; );
    }
    else if ( SEMPERFLASH2_SIZE_ERROR == stat )
    {
        log_printf( &logger, "BUF SIZE ERROR!" );
        for ( ; ; );
    }
}

void id_check ( )
{
    uint8_t cnt;

    error_handler( semperflash2_check_manufacturer_id( &semperflash2 ) );
    error_handler( semperflash2_get_device_id( &semperflash2, id_data ) );

    log_printf( &logger, "DEVICE ID: 0x" );
    for ( cnt = 0; cnt < SEMPERFLASH2_DEVICE_ID_BYTE_SIZE; cnt++ )
    {
        log_printf( &logger, "%x", id_data[ cnt ] );
    }
    log_printf( &logger, "\r\n\r\n" );
    txt_flag = COMPANY_FLAG;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    semperflash2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    semperflash2_cfg_setup( &cfg );
    SEMPERFLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    semperflash2_init( &semperflash2, &cfg );
    semperflash2_default_cfg( &semperflash2 );
    id_check( );
    Delay_ms( 500 );
}

void application_task ( )
{
    char write_data_com[ 7 ] = "MikroE";
    char write_data_clk[ 15 ] = "Semper Flash 2";
    char read_buf_data[ 15 ] = { 0 };

    semperflash2_send_cmd( &semperflash2, SEMPERFLASH2_WRITE_ENABLE );
    semperflash2_erase_memory( &semperflash2, ADRESS_MEMORY );
    
    if ( COMPANY_FLAG == txt_flag )
    {
       semperflash2_send_cmd( &semperflash2, SEMPERFLASH2_WRITE_ENABLE );
       error_handler( semperflash2_write_memory( &semperflash2, ADRESS_MEMORY, write_data_com, 6 ) );
       error_handler( semperflash2_read_memory( &semperflash2, ADRESS_MEMORY, read_buf_data, 6 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = CLICK_FLAG;       
    }
    else if ( CLICK_FLAG == txt_flag )
    {
       semperflash2_send_cmd( &semperflash2, SEMPERFLASH2_WRITE_ENABLE );
       error_handler( semperflash2_write_memory( &semperflash2, ADRESS_MEMORY, write_data_clk, 14 ) );
       error_handler( semperflash2_read_memory( &semperflash2, ADRESS_MEMORY, read_buf_data, 14 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = COMPANY_FLAG;
    }

    log_printf( &logger, "....................\r\n" );
    Delay_ms( 2000 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END

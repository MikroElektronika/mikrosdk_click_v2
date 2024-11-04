/*!
 * \file 
 * \brief SemperFlash Click example
 * 
 * # Description
 * This example showcases how to initialize and use the Semper Flash Click. The Click
 * is a 512 Mbit SPI Flash memory module. Data can be stored in and read from the flash
 * memory. There's also the option of erasing it's contents. Here's how to do it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the Click and logger modules. Additional con-
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
#include "semperflash.h"

// ------------------------------------------------------------------ VARIABLES

static semperflash_t semperflash;
static log_t logger;

uint8_t id_data[ 8 ];
uint8_t txt_flag;
uint8_t COMPANY_FLAG = 2;
uint8_t CLICK_FLAG = 3;
uint32_t ADRESS_MEMORY = 0x00001111;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void error_handler ( uint8_t stat )
{
    if ( SEMPERFLASH_ID_ERROR == stat )
    {
        log_printf( &logger, "ID ERROR!" );
        for ( ; ; );
    }
    else if ( SEMPERFLASH_SIZE_ERROR == stat )
    {
        log_printf( &logger, "BUF SIZE ERROR!" );
        for ( ; ; );
    }
}

void id_check ( )
{
    uint8_t cnt;

    error_handler( semperflash_check_manufacturer_id( &semperflash ) );
    error_handler( semperflash_get_device_id( &semperflash, id_data ) );

    log_printf( &logger, "DEVICE ID: 0x" );
    for ( cnt = 0; cnt < SEMPERFLASH_DEVICE_ID_BYTE_SIZE; cnt++ )
    {
        log_printf( &logger, "%x", ( uint16_t )id_data[ cnt ] );
    }
    log_printf( &logger, "\r\n\r\n" );
    txt_flag = COMPANY_FLAG;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    semperflash_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    semperflash_cfg_setup( &cfg );
    SEMPERFLASH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    semperflash_init( &semperflash, &cfg );
    
    semperflash_default_cfg( &semperflash );
    
    id_check( );
    Delay_ms ( 500 );
}

void application_task ( )
{
    char write_data_com[ 7 ] = "MikroE";
    char write_data_clk[ 13 ] = "Semper Flash";
    char read_buf_data[ 13 ] = { 0 };

    semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
    semperflash_erase_memory( &semperflash, ADRESS_MEMORY );
    
    if ( COMPANY_FLAG == txt_flag )
    {
       semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
       error_handler( semperflash_write_memory( &semperflash, ADRESS_MEMORY, write_data_com, 6 ) );
       error_handler( semperflash_read_memory( &semperflash, ADRESS_MEMORY, read_buf_data, 6 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = CLICK_FLAG;       
    }
    else if ( CLICK_FLAG == txt_flag )
    {
       semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
       error_handler( semperflash_write_memory( &semperflash, ADRESS_MEMORY, write_data_clk, 12 ) );
       error_handler( semperflash_read_memory( &semperflash, ADRESS_MEMORY, read_buf_data, 12 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = COMPANY_FLAG;
    }

    log_printf( &logger, "....................\r\n" );
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

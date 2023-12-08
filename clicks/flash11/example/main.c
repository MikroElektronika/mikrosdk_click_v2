/*!
 * @file main.c
 * @brief Flash 11 Click example
 *
 * # Description
 * This example demonstrates the use of Flash 11 click board.
 * The demo app writes specified data to the memory and reads it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Flash 11 Click board™.
 * The demo application writes a desired number of bytes to the memory 
 * and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash11.h"

static flash11_t flash11;
static log_t logger;

#define DEMO_TEXT_MESSAGE_1         "MikroE"
#define STARTING_ADDRESS_1           0x010203ul
#define DEMO_TEXT_MESSAGE_2         "Flash 11 Click"
#define STARTING_ADDRESS_2           0x123456ul

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash11_cfg_t flash11_cfg;  /**< Click config object. */
    
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
    log_info( &logger, " Application Init " );
    
    // Click initialization.
    flash11_cfg_setup( &flash11_cfg );
    FLASH11_MAP_MIKROBUS( flash11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash11_init( &flash11, &flash11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH11_ERROR == flash11_default_cfg ( &flash11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS_1 );
    if ( FLASH11_OK == flash11_block_erase( &flash11, FLASH11_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS_1 ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH11_OK == flash11_memory_write( &flash11, STARTING_ADDRESS_1, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH11_OK == flash11_memory_read( &flash11, STARTING_ADDRESS_1, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms( 3000 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS_2 );
    if ( FLASH11_OK == flash11_block_erase( &flash11, FLASH11_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS_2 ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH11_OK == flash11_memory_write( &flash11, STARTING_ADDRESS_2, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH11_OK == flash11_memory_read( &flash11, STARTING_ADDRESS_2, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms( 3000 );
    }
    log_printf ( &logger, " ----------------------------\r\n" );
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

/*!
 * @file main.c
 * @brief Flash 12 Click example
 *
 * # Description
 * This example demonstrates the use of Flash 12 click board 
 * by writing specified data to the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application writes a desired number of bytes to the memory 
 * and then verifies if it is written correctly by reading 
 * from the same memory location and displaying the memory content.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash12.h"

// Starting memory address
#define STARTING_ADDRESS            0x012345

// Demo text messages
#define DEMO_TEXT_MESSAGE_1         "MikroE"
#define DEMO_TEXT_MESSAGE_2         "Flash 12 Click"

static flash12_t flash12;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash12_cfg_t flash12_cfg;  /**< Click config object. */

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
    flash12_cfg_setup( &flash12_cfg );
    FLASH12_MAP_MIKROBUS( flash12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash12_init( &flash12, &flash12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH12_ERROR == flash12_default_cfg ( &flash12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task\r\n" );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };

    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH12_OK == flash12_erase_memory( &flash12, FLASH12_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH12_OK == flash12_memory_write( &flash12, STARTING_ADDRESS, 
                                                       data_buf, 
                                                       sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }

    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH12_OK == flash12_memory_read( &flash12, STARTING_ADDRESS, 
                                                      data_buf, 
                                                      sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms( 3000 );
    }

    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH12_OK == flash12_erase_memory( &flash12, FLASH12_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH12_OK == flash12_memory_write( &flash12, STARTING_ADDRESS, 
                                             data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH12_OK == flash12_memory_read( &flash12, STARTING_ADDRESS, 
                                            data_buf, sizeof ( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms( 3000 );
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

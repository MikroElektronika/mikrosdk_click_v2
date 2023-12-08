/*!
 * @file main.c
 * @brief Flash 10 Click example
 *
 * # Description
 * This example demonstrates the use of Flash 10 click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and checks the communication by reading and verifying the device ID.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content on the USB UART.
 * The whole 4KB block of memory that contains the STARTING_ADDRESS will be erased before writing data.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash10.h"

#define DEMO_TEXT_MESSAGE_1         "MIKROE"
#define DEMO_TEXT_MESSAGE_2         "Flash 10 click"
#define STARTING_ADDRESS            0x012345

static flash10_t flash10;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash10_cfg_t flash10_cfg;  /**< Click config object. */

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
    flash10_cfg_setup( &flash10_cfg );
    FLASH10_MAP_MIKROBUS( flash10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash10_init( &flash10, &flash10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH10_ERROR == flash10_check_communication ( &flash10 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH10_OK == flash10_erase_memory ( &flash10, FLASH10_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH10_OK == flash10_memory_write ( &flash10, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH10_OK == flash10_memory_read ( &flash10, STARTING_ADDRESS, 
                                             data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH10_OK == flash10_erase_memory ( &flash10, FLASH10_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH10_OK == flash10_memory_write ( &flash10, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH10_OK == flash10_memory_read ( &flash10, STARTING_ADDRESS, 
                                             data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
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

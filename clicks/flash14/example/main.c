/*!
 * @file main.c
 * @brief Flash 14 Click example
 *
 * # Description
 * This example demonstrates the use of Flash 14 Click board by writing specified data to
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
 * The whole 4KB sector of memory that contains the STARTING_ADDRESS will be erased before writing data.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash14.h"

#define DEMO_TEXT_MESSAGE_1         "MIKROE"
#define DEMO_TEXT_MESSAGE_2         "Flash 14 Click"
#define STARTING_ADDRESS            0x01234567ul

static flash14_t flash14;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash14_cfg_t flash14_cfg;  /**< Click config object. */

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
    flash14_cfg_setup( &flash14_cfg );
    FLASH14_MAP_MIKROBUS( flash14_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == flash14_init( &flash14, &flash14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH14_ERROR == flash14_check_communication ( &flash14 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };

    log_printf ( &logger, " Memory address: 0x%.8LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH14_OK == flash14_erase_memory ( &flash14, FLASH14_CMD_4B_SECTOR_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory sector (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH14_OK == flash14_memory_write ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH14_OK == flash14_memory_read ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
    }

    log_printf ( &logger, " Memory address: 0x%.8LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH14_OK == flash14_erase_memory ( &flash14, FLASH14_CMD_4B_SECTOR_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory sector (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH14_OK == flash14_memory_write ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH14_OK == flash14_memory_read ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
    }
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

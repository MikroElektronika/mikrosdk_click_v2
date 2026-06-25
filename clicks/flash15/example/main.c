/*!
 * @file main.c
 * @brief Flash 15 Click example
 *
 * # Description
 * This example demonstrates the use of the Flash 15 Click board for basic
 * flash memory operations. The application disables memory protection,
 * erases a memory page, writes text data to the selected page and column,
 * and then reads the written data back from memory.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Flash 15 Click driver, checks device
 * communication, and disables memory protection.
 *
 * ## Application Task
 * Erases the selected memory page, writes demo text messages to flash
 * memory, and reads the stored data back for verification.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash15.h"

#ifndef MIKROBUS_POSITION_FLASH15
    #define MIKROBUS_POSITION_FLASH15 MIKROBUS_1
#endif

#define DEMO_TEXT_MESSAGE_1 "MIKROE"
#define DEMO_TEXT_MESSAGE_2 "Flash 15 Click"
#define START_PAGE          0x1234
#define START_COLUMN        0x0567

static flash15_t flash15;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash15_cfg_t flash15_cfg;  /**< Click config object. */

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
    flash15_cfg_setup( &flash15_cfg );
    FLASH15_MAP_MIKROBUS( flash15_cfg, MIKROBUS_POSITION_FLASH15 );
    if ( SPI_MASTER_ERROR == flash15_init( &flash15, &flash15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH15_ERROR == flash15_check_communication ( &flash15 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    log_printf ( &logger, " Disable memory protection\r\n" );
    flash15_set_feature ( &flash15, FLASH15_REG_PROTECTION, FLASH15_PROTECTION_NONE );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 64 ] = { 0 };

    log_printf ( &logger, " Memory page: 0x%.4X, column: 0x%.4X\r\n", START_PAGE, START_COLUMN );
    if ( FLASH15_OK == flash15_erase_memory ( &flash15, START_PAGE ) )
    {
        log_printf ( &logger, " Erase memory page\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH15_OK == flash15_memory_write ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH15_OK == flash15_memory_read ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
    }

    log_printf ( &logger, " Memory page: 0x%.4X, column: 0x%.4X\r\n", START_PAGE, START_COLUMN );
    if ( FLASH15_OK == flash15_erase_memory ( &flash15, START_PAGE ) )
    {
        log_printf ( &logger, " Erase memory page\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH15_OK == flash15_memory_write ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH15_OK == flash15_memory_read ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
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

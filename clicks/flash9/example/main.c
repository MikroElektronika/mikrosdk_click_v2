/*!
 * @file main.c
 * @brief Flash9 Click example
 *
 * # Description
 * This example demonstrates the use of Flash 9 click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Erases the memory sector and then writes a desired number of data bytes to the memory 
 * and verifies that it is written correctly by reading from the same memory location and 
 * displaying the memory content on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash9.h"

#define DEMO_TEXT_MESSAGE           "MikroE - Flash 9 click board"
#define STARTING_ADDRESS            0x01234567ul

static flash9_t flash9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash9_cfg_t flash9_cfg;  /**< Click config object. */

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
    flash9_cfg_setup( &flash9_cfg );
    FLASH9_MAP_MIKROBUS( flash9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash9_init( &flash9, &flash9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH9_ERROR == flash9_default_cfg ( &flash9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FLASH9_OK == flash9_erase_memory ( &flash9, FLASH9_CMD_SECTOR_ERASE_WITH_4BYTE_ADDRESS, 
                                            STARTING_ADDRESS ) )
    {
        log_printf ( &logger, "Sector from address 0x%.8LX has been erased!\r\n", STARTING_ADDRESS );
    }
    Delay_ms ( 500 );
    
    if ( FLASH9_OK == flash9_memory_write ( &flash9, STARTING_ADDRESS, DEMO_TEXT_MESSAGE, 
                                            strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.8LX: \"%s\"\r\n", STARTING_ADDRESS, 
                                                                  ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 500 );

    if ( FLASH9_OK == flash9_memory_read_fast ( &flash9, STARTING_ADDRESS, data_buf, 
                                                strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.8LX: \"%s\"\r\n\n", STARTING_ADDRESS, 
                                                                              data_buf );
    }
    Delay_ms ( 2000 );
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

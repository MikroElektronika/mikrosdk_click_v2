/*!
 * @file main.c
 * @brief EEPROM 16 Click example
 *
 * # Description
 * This example demonstrates the use of EEPROM 16 Click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom16.h"

#define DEMO_TEXT_MESSAGE_1     "MIKROE"
#define DEMO_TEXT_MESSAGE_2     "EEPROM 16 Click"
#define STARTING_ADDRESS        0x0100 

static eeprom16_t eeprom16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom16_cfg_t eeprom16_cfg;  /**< Click config object. */

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
    eeprom16_cfg_setup( &eeprom16_cfg );
    EEPROM16_MAP_MIKROBUS( eeprom16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == eeprom16_init( &eeprom16, &eeprom16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM16_ERROR == eeprom16_default_cfg ( &eeprom16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ EEPROM16_PAGE_SIZE + 1 ] = { 0 };
    log_printf ( &logger, "\r\n Memory address: 0x%.4X\r\n", ( uint16_t ) STARTING_ADDRESS );
    
    if ( EEPROM16_OK == eeprom16_memory_write ( &eeprom16, STARTING_ADDRESS, 
                                                DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", ( char * ) DEMO_TEXT_MESSAGE_1 );
    }
    if ( EEPROM16_OK == eeprom16_memory_read ( &eeprom16, STARTING_ADDRESS, 
                                               data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
    }

    if ( EEPROM16_OK == eeprom16_memory_write ( &eeprom16, STARTING_ADDRESS, 
                                                DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", ( char * ) DEMO_TEXT_MESSAGE_2 );
    }
    if ( EEPROM16_OK == eeprom16_memory_read ( &eeprom16, STARTING_ADDRESS, 
                                               data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
    }

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

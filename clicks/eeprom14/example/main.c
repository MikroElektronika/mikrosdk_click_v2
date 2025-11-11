/*!
 * @file main.c
 * @brief EEPROM 14 Click example
 *
 * # Description
 * This example demonstrates basic read and write operations on the EEPROM 14 Click.
 * The application writes predefined text messages into memory, then reads them back
 * and logs the results for verification.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, configures and initializes the EEPROM 14 Click.
 *
 * ## Application Task
 * Writes and reads text messages from EEPROM memory, displaying the stored values
 * via the UART logger.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom14.h"

#define DEMO_TEXT_MESSAGE_1     "MIKROE"
#define DEMO_TEXT_MESSAGE_2     "EEPROM 14 Click"
#define STARTING_ADDRESS        0x0123

static eeprom14_t eeprom14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom14_cfg_t eeprom14_cfg;  /**< Click config object. */

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
    eeprom14_cfg_setup( &eeprom14_cfg );
    EEPROM14_MAP_MIKROBUS( eeprom14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom14_init( &eeprom14, &eeprom14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t data_buf[ EEPROM14_MEM_PAGE_SIZE + 1 ] = { 0 };

    log_printf ( &logger, " Memory address: 0x%.4X\r\n", STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( EEPROM14_OK == eeprom14_write_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM14_OK == eeprom14_read_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Memory address: 0x%.4X\r\n", STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( EEPROM14_OK == eeprom14_write_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM14_OK == eeprom14_read_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
    }
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

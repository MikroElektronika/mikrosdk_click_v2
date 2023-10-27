/*!
 * @file main.c
 * @brief EEPROM 11 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the EEPROM 11 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logging, disables write protection.
 *
 * ## Application Task
 * Writes a desired number of data bytes to the EEPROM 11 memory into a specified address, 
 * and verifies that it is written correctly by reading from the same memory location.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom11.h"

#define TX_DATA         "EEPROM 11 Click"
#define MEMORY_ADDRESS  0x00

static eeprom11_t eeprom11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom11_cfg_t eeprom11_cfg;  /**< Click config object. */

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
    eeprom11_cfg_setup( &eeprom11_cfg );
    EEPROM11_MAP_MIKROBUS( eeprom11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom11_init( &eeprom11, &eeprom11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM11_ERROR == eeprom11_default_cfg ( &eeprom11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = EEPROM11_OK;
    uint8_t rx_data[ 16 ] = { 0 };
    uint8_t tx_data[ 16 ] = TX_DATA;
    
    eeprom11_clear_page( &eeprom11, MEMORY_ADDRESS );
    Delay_ms( 1000 );
    error_flag = eeprom11_page_write( &eeprom11, MEMORY_ADDRESS, tx_data );
    if ( EEPROM11_OK == error_flag )
    {
        log_printf( &logger, " Write data: %s \r\n", tx_data );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    Delay_ms( 1000 );
    
    error_flag = eeprom11_generic_read( &eeprom11, MEMORY_ADDRESS, rx_data, 15 );
    if ( EEPROM11_OK == error_flag )
    {
        log_printf( &logger, "Read data: %s \r\n", rx_data );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    
    Delay_ms( 2000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END

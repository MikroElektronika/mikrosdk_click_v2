/*!
 * @file main.c
 * @brief EEPROM 10 Click example
 *
 * # Description
 * This example demonstrates the use of EEPROM 10 click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logging.
 *
 * ## Application Task
 * In this example, we write and then read data from EEPROM memory.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB UART changes approximately every second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom10.h"

#define EEPROM10_TEST_ADDRESS       0x0010u

static eeprom10_t eeprom10;
static log_t logger;
static uint8_t tx_data[ 15 ] = { 'E', 'E', 'P', 'R', 'O', 'M', '1', '0', ' ', 'C', 'l', 'i', 'c', 'k' };
static uint8_t rx_data[ 15 ] = { 0 };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom10_cfg_t eeprom10_cfg;  /**< Click config object. */

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
    eeprom10_cfg_setup( &eeprom10_cfg );
    EEPROM10_MAP_MIKROBUS( eeprom10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom10_init( &eeprom10, &eeprom10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    eeprom10_write_enable( &eeprom10 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = EEPROM10_OK;
    
    error_flag = eeprom10_write_n_byte( &eeprom10, EEPROM10_TEST_ADDRESS, tx_data, 14 );
    if ( EEPROM10_OK == error_flag )
    {
        log_printf( &logger, " Write %s data to 0x%.4X address \r\n", tx_data, ( uint16_t ) EEPROM10_TEST_ADDRESS );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    Delay_ms ( 100 );
    
    error_flag = eeprom10_read_n_byte( &eeprom10, EEPROM10_TEST_ADDRESS, rx_data, 14 );
    if ( EEPROM10_OK == error_flag )
    {
        log_printf( &logger, " Read %s from 0x%.4X address \r\n", rx_data, ( uint16_t ) EEPROM10_TEST_ADDRESS );
    }
    else
    {
        log_error( &logger, " Read operation failed!!! " );
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

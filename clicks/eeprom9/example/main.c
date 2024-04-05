/*!
 * @file main.c
 * @brief EEPROM 9 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the EEPROM 9 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logging, disables hold and write protection.
 *
 * ## Application Task
 * Writes a desired number of data bytes to the EEPROM 9 memory into a specified address, 
 * and verifies that it is written correctly by reading from the same memory location.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom9.h"

static eeprom9_t eeprom9;
static log_t logger;
static char demo_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };

#define MEMORY_ADDRESS  0x0300

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom9_cfg_t eeprom9_cfg;  /**< Click config object. */
    id_data_t id_data;
    
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
    eeprom9_cfg_setup( &eeprom9_cfg );
    EEPROM9_MAP_MIKROBUS( eeprom9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == eeprom9_init( &eeprom9, &eeprom9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    eeprom9_read_identification( &eeprom9, &id_data );
    if ( EEPROM9_ST_MANUFACTURER_CODE != id_data.manufact_code )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    log_printf( &logger, " Manufacturer code: 0x%.2X \r\n", ( uint16_t ) id_data.manufact_code ); 
    
    log_printf( &logger, " Disabling Hold \r\n" );
    eeprom9_set_hold( &eeprom9, EEPROM9_HOLD_DISABLE );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Disabling Write Protection \r\n" );
    eeprom9_set_write_protection( &eeprom9, EEPROM9_WRITE_PROTECT_DISABLE );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
}

void application_task ( void )
{
    char rx_data[ 9 ] = { 0 };
    
    eeprom9_set_write_enable( &eeprom9, EEPROM9_WRITE_ENABLE );
    Delay_ms ( 10 );
    
    eeprom9_write_memory( &eeprom9, MEMORY_ADDRESS, demo_data, 9 );
    log_printf( &logger, " Write data: %s", demo_data );
    Delay_ms ( 100 );
    
    eeprom9_read_memory( &eeprom9, MEMORY_ADDRESS, rx_data, 9 );
    log_printf( &logger, " Read data: %s", rx_data );  
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    
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

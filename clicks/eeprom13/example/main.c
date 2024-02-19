/*!
 * @file main.c
 * @brief EEPROM 13 Click example
 *
 * # Description
 * This example demonstrates the use of EEPROM 13 click board.
 * The demo app writes specified data to the memory and reads it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module, log UART, and additional pins.
 *
 * ## Application Task
 * The demo application writes a desired number of bytes to the memory 
 * and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom13.h"

#define STARTING_ADDRESS             0x12345
#define DEMO_TEXT_MESSAGE_1         "MikroE"
#define DEMO_TEXT_MESSAGE_2         "EEPROM 13 Click"

static eeprom13_t eeprom13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom13_cfg_t eeprom13_cfg;  /**< Click config object. */

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
    eeprom13_cfg_setup( &eeprom13_cfg );
    EEPROM13_MAP_MIKROBUS( eeprom13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom13_init( &eeprom13, &eeprom13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    uint8_t data_buf[ 128 ] = { 0 };
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( EEPROM13_OK == eeprom13_memory_write( &eeprom13, STARTING_ADDRESS, 
                                                          data_buf, 
                                                          strlen( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    Delay_ms( 100 );
    if ( EEPROM13_OK == eeprom13_memory_read( &eeprom13, STARTING_ADDRESS, 
                                                         data_buf, 
                                                         strlen( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        Delay_ms( 100 );
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms( 3000 );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( EEPROM13_OK == eeprom13_memory_write( &eeprom13, STARTING_ADDRESS, 
                                                          data_buf, 
                                                          strlen( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    Delay_ms( 100 );
    if ( EEPROM13_OK == eeprom13_memory_read( &eeprom13, STARTING_ADDRESS, 
                                                         data_buf, 
                                                         strlen( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        Delay_ms( 100 );
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

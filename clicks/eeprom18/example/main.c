/*!
 * @file main.c
 * @brief EEPROM 18 Click example
 *
 * # Description
 * This example demonstrates the use of EEPROM 18 Click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content on the USB UART.
 *
 * @note
 * The identification page cannot be written once it has been
 * permanently locked with eeprom18_lock_id_page().
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom18.h"

#ifndef MIKROBUS_POSITION_EEPROM18
    #define MIKROBUS_POSITION_EEPROM18 MIKROBUS_1
#endif

#define DEMO_TEXT_MESSAGE_1     "MIKROE"
#define DEMO_TEXT_MESSAGE_2     "EEPROM 18 Click"
#define STARTING_ADDRESS        0x012345

static eeprom18_t eeprom18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom18_cfg_t eeprom18_cfg;  /**< Click config object. */

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
    eeprom18_cfg_setup( &eeprom18_cfg );
    EEPROM18_MAP_MIKROBUS( eeprom18_cfg, MIKROBUS_POSITION_EEPROM18 );
    if ( SPI_MASTER_ERROR == eeprom18_init( &eeprom18, &eeprom18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ EEPROM18_PAGE_SIZE ] = { 0 };

    log_printf( &logger, "\r\n Memory address: 0x%.5lX\r\n", ( uint32_t ) STARTING_ADDRESS );

    /* Write first DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_1 ) > EEPROM18_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, EEPROM18_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    }
    if ( EEPROM18_OK == eeprom18_write_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    
    /* Read first DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM18_OK == eeprom18_read_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 1000 );
    
    /* Write second DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_2 ) > EEPROM18_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, EEPROM18_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    }
    if ( EEPROM18_OK == eeprom18_write_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    
    /* Read second DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM18_OK == eeprom18_read_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
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

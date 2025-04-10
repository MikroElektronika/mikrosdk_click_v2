/*!
 * @file main.c
 * @brief EEPROM 15 Click example
 *
 * # Description
 * This example demonstrates the use of EEPROM 15 Click board by writing specified data to
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
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom15.h"

#define DEMO_TEXT_MESSAGE_1     "MIKROE"
#define DEMO_TEXT_MESSAGE_2     "EEPROM 15 Click"
#define STARTING_ADDRESS        0x10

static eeprom15_t eeprom15;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom15_cfg_t eeprom15_cfg;  /**< Click config object. */

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
    eeprom15_cfg_setup( &eeprom15_cfg );
    EEPROM15_MAP_MIKROBUS( eeprom15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom15_init( &eeprom15, &eeprom15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t bank_sel = EEPROM15_BANK_SEL_0; 
    uint8_t data_buf[ EEPROM15_MEM_PAGE_SIZE + 1 ] = { 0 };

    // Selecting memory bank
    if ( EEPROM15_ERROR == eeprom15_select_bank ( &eeprom15, bank_sel ) )
    {
        log_error( &logger, " No communication with EEPROM." );
        for ( ; ; );
    }
    log_printf ( &logger, "\r\n Memory bank: %u\r\n", ( uint16_t ) bank_sel );
    log_printf ( &logger, " Memory address: 0x%.2X\r\n", ( uint16_t ) STARTING_ADDRESS );
    bank_sel ^= EEPROM15_BANK_SEL_1;

    // Write/Read first iterration
    if ( strlen ( DEMO_TEXT_MESSAGE_1 ) > EEPROM15_MEM_PAGE_SIZE )
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, EEPROM15_MEM_PAGE_SIZE );
    }
    else
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    }
    if ( EEPROM15_OK == eeprom15_write_memory ( &eeprom15, STARTING_ADDRESS, data_buf, EEPROM15_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM15_OK == eeprom15_read_memory ( &eeprom15, STARTING_ADDRESS, data_buf, EEPROM15_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    
    // Write/Read second iterration
    if ( strlen ( DEMO_TEXT_MESSAGE_2 ) > EEPROM15_MEM_PAGE_SIZE )
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, EEPROM15_MEM_PAGE_SIZE );
    }
    else
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    }
    if ( EEPROM15_OK == eeprom15_write_memory ( &eeprom15, STARTING_ADDRESS, data_buf, EEPROM15_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM15_OK == eeprom15_read_memory ( &eeprom15, STARTING_ADDRESS, data_buf, EEPROM15_MEM_PAGE_SIZE ) )
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

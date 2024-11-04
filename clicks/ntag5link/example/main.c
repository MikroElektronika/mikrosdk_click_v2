/*!
 * @file main.c
 * @brief NTAG5Link Click example
 *
 * # Description
 * This example demonstrates the use of NTAG 5 Link Click board by programming the
 * specified NDEF URI record to the memory, and showing the memory read/write feature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the Click default configuration which 
 * enables the device and formats its user memory. After that it programs the specified 
 * NDEF URI record to the memory.
 *
 * ## Application Task
 * Writes a desired number of data bytes to the memory and verifies that it is written 
 * correctly by reading from the same memory location and displaying the memory content 
 * on the USB UART approximately every 5 seconds.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ntag5link.h"

/**
 * URL to store to memory as NDEF URI record
 */
#define URI_DATA                "www.mikroe.com/ntag-5-link-click" 

/**
 * Starting block address to where the text message will be stored
 * Must be > ( NTAG5LINK_NDEF_MESSAGE_START_ADDRESS + sizeof ( URI_DATA ) / NTAG5LINK_MEMORY_BLOCK_SIZE + 3 )
 * to avoid overwriting NDEF URI record.
 */
#define TEXT_MESSAGE_ADDRESS    0x0040

/**
 * Text message content that will be stored to memory
 */
#define TEXT_MESSAGE            "MikroE - NTAG 5 Link Click"

static ntag5link_t ntag5link;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ntag5link_cfg_t ntag5link_cfg;  /**< Click config object. */

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
    ntag5link_cfg_setup( &ntag5link_cfg );
    NTAG5LINK_MAP_MIKROBUS( ntag5link_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ntag5link_init( &ntag5link, &ntag5link_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NTAG5LINK_ERROR == ntag5link_default_cfg ( &ntag5link ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( NTAG5LINK_OK == ntag5link_write_ndef_uri_record ( &ntag5link, NTAG5LINK_URI_PREFIX_4, 
                                                           URI_DATA, strlen ( URI_DATA ) ) )
    {
        log_printf( &logger, " NDEF URI record \"https://%s\" has been written\r\n", ( char * ) URI_DATA );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t message_buf[ 100 ] = { 0 };
    if ( NTAG5LINK_OK == ntag5link_write_message_to_memory ( &ntag5link, 
                                                             TEXT_MESSAGE_ADDRESS, 
                                                             TEXT_MESSAGE, 
                                                             strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been written to memory address 0x%.4X \r\n", 
                    ( char * ) TEXT_MESSAGE, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    if ( NTAG5LINK_OK == ntag5link_read_message_from_memory ( &ntag5link, 
                                                              TEXT_MESSAGE_ADDRESS, 
                                                              message_buf, 
                                                              strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been read from memory address 0x%.4X \r\n\n", 
                    message_buf, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

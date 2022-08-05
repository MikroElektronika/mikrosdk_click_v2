/*!
 * @file main.c
 * @brief NFCTag5 Click example
 *
 * # Description
 * This example demonstrates the use of NFC Tag 5 click board by programming the
 * specified NDEF URI record to the memory, and showing the memory read/write feature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration which 
 * formats its user memory. After that it programs the specified NDEF URI record to the memory.
 *
 * ## Application Task
 * Writes a desired number of data bytes to the memory and verifies that it is written 
 * correctly by reading from the same memory location and displaying the memory content 
 * on the USB UART approximately every 5 seconds.
 *
 * @note
 * Trying to write/read in RF mode (for example, processing NDEF URI record with a smartphone) 
 * while writing to memory over I2C is in progress can interrupt and block the I2C communication. 
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfctag5.h"

/**
 * URL to store to memory as NDEF URI record
 */
#define URI_DATA                "www.mikroe.com/nfc-tag-5-click" 

/**
 * Starting block address to where the text message will be stored
 * Must be > ( NFCTAG5_NDEF_MESSAGE_START_ADDRESS + sizeof ( URI_DATA ) / NFCTAG5_MEMORY_BLOCK_SIZE + 3 )
 * to avoid overwriting NDEF URI record.
 */
#define TEXT_MESSAGE_ADDRESS    0x0100

/**
 * Text message content that will be stored to memory
 */
#define TEXT_MESSAGE            "MikroE - NFC Tag 5 click"

static nfctag5_t nfctag5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfctag5_cfg_t nfctag5_cfg;  /**< Click config object. */

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
    nfctag5_cfg_setup( &nfctag5_cfg );
    NFCTAG5_MAP_MIKROBUS( nfctag5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nfctag5_init( &nfctag5, &nfctag5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFCTAG5_ERROR == nfctag5_default_cfg ( &nfctag5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( NFCTAG5_OK == nfctag5_write_ndef_uri_record ( &nfctag5, NFCTAG5_URI_PREFIX_4, 
                                                       URI_DATA, strlen ( URI_DATA ) ) )
    {
        log_printf( &logger, " NDEF URI record \"https://%s\" has been written\r\n", ( char * ) URI_DATA );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t message_buf[ 100 ] = { 0 };
    if ( NFCTAG5_OK == nfctag5_write_message_to_memory ( &nfctag5, 
                                                         TEXT_MESSAGE_ADDRESS, 
                                                         TEXT_MESSAGE, 
                                                         strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been written to memory address 0x%.4X \r\n", 
                    ( char * ) TEXT_MESSAGE, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    if ( NFCTAG5_OK == nfctag5_read_message_from_memory ( &nfctag5,
                                                          TEXT_MESSAGE_ADDRESS, 
                                                          message_buf, 
                                                          strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been read from memory address 0x%.4X \r\n\n", 
                    message_buf, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    Delay_ms( 5000 );
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

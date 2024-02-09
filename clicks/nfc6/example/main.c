/*!
 * @file main.c
 * @brief NFC 6 Click example
 *
 * # Description
 * This example demonstrates the use of NFC 6 Click board by reading
 * MIFARE ISO/IEC 14443 type A tag UID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, performs the click default configuration and
 * reads the device ID.
 *
 * ## Application Task
 * If there's a tag detected, it reads its UID and displays it on the USB UART every 500ms.
 *
 * @note
 * Only ISO14443-A type tags with 4-byte or 7-byte UIDs are compatible with this example.
 * We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc6.h"

static nfc6_t nfc6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc6_cfg_t nfc6_cfg;  /**< Click config object. */

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
    nfc6_cfg_setup( &nfc6_cfg );
    NFC6_MAP_MIKROBUS( nfc6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == nfc6_init( &nfc6, &nfc6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFC6_ERROR == nfc6_default_cfg ( &nfc6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t device_id[ 13 ] = { 0 };
    nfc6_send_command ( &nfc6, NFC6_CMD_IDN, NULL, NULL );
    if ( NFC6_OK == nfc6_read_data ( &nfc6, device_id, sizeof ( device_id ), NULL ) )
    {
        log_printf ( &logger, " Device ID: %s\r\n", device_id );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t tag_uid[ NFC6_TAG_UID_MAX_LEN ] = { 0 };
    uint8_t tag_uid_len = 0;
    if ( NFC6_OK == nfc6_read_mifare_tag_uid ( &nfc6, tag_uid, &tag_uid_len ) )
    {
        log_printf( &logger, " TAG UID: " );
        for ( uint8_t cnt = 0; cnt < tag_uid_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n----------------------------------\r\n" );
        Delay_ms( 500 );
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

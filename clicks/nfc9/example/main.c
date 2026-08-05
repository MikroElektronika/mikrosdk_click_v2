/*!
 * @file main.c
 * @brief NFC 9 Click example
 *
 * # Description
 * This example demonstrates the use of NFC 9 Click board by reading
 * ISO14443-A type tags UID, ATQA, and SAK values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, performs the Click default configuration.
 *
 * ## Application Task
 * Continuously checks for an NFC tag, reads its UID and related data, and logs the results.
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
#include "nfc9.h"

#ifndef MIKROBUS_POSITION_NFC9
    #define MIKROBUS_POSITION_NFC9 MIKROBUS_1
#endif

static nfc9_t nfc9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc9_cfg_t nfc9_cfg;  /**< Click config object. */

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
    nfc9_cfg_setup( &nfc9_cfg );
    NFC9_MAP_MIKROBUS( nfc9_cfg, MIKROBUS_POSITION_NFC9 );
    if ( SPI_MASTER_ERROR == nfc9_init( &nfc9, &nfc9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( NFC9_ERROR == nfc9_default_cfg( &nfc9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    nfc9_tag_t tag_info;
    if ( NFC9_OK == nfc9_read_tag ( &nfc9, &tag_info ) )
    {
        log_printf( &logger, " --- Tag Info ---\r\n" );
        log_printf( &logger, " UID: " );
        for ( uint8_t cnt = 0; cnt < tag_info.uid_len; cnt++ )
        {
            log_printf( &logger, "%.2X", ( uint16_t ) tag_info.uid[ cnt ] );
            if ( cnt < ( tag_info.uid_len - 1 ) )
            {
                log_printf( &logger, ":" );
            }
        }
        log_printf( &logger, "\r\n ATQA: 0x%.4X\r\n", tag_info.atqa );
        log_printf( &logger, " SAK: 0x%.2X\r\n\n", tag_info.sak );
    }
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

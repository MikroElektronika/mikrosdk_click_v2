/*!
 * @file main.c
 * @brief NFC 5 Click example
 *
 * # Description
 * This example demonstrates the use of NFC 4 Click board by reading
 * MIFARE ISO/IEC 14443 type A tag UID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * If there's a tag detected, it reads its UID and displays it on the USB UART every 500ms.
 *
 * @note
 * Only ISO14443-A type tags are compatible with this example.
 * We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc5.h"

static nfc5_t nfc5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc5_cfg_t nfc5_cfg;  /**< Click config object. */

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
    nfc5_cfg_setup( &nfc5_cfg );
    NFC5_MAP_MIKROBUS( nfc5_cfg, MIKROBUS_1 );
    err_t init_flag = nfc5_init( &nfc5, &nfc5_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFC5_ERROR == nfc5_default_cfg ( &nfc5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t tag_uid[ NFC5_NFCA_CASCADE_3_UID_LEN ] = { 0 };
    uint8_t tag_uid_len = 0;
    
    if ( NFC5_OK == nfc5_get_mifare_tag_uid( &nfc5, tag_uid, &tag_uid_len ) )
    {
        log_printf( &logger, " TAG UID: " );
        for ( uint8_t cnt = 0; cnt < tag_uid_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n----------------------------------\r\n" );
        Delay_ms ( 500 );
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

/*!
 * @file main.c
 * @brief NFC3 Click example
 *
 * # Description
 * This example demonstrates the use of NFC 3 Click board 
 * by reading MIFARE ISO/IEC 14443 type A tag UID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and logger, then enables the Click board and reads 
 * the device product, firmware and eeprom versions.
 *
 * ## Application Task
 * If there's a tag detected, it reads its UID and displays it on USB UART.
 *
 * @note
 * Only tags with 4-byte or 7-byte UIDs are compatible with this example.
 * We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc3.h"

static nfc3_t nfc3;
static log_t logger;
static uint16_t info;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc3_cfg_t nfc3_cfg;  /**< Click config object. */

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

    nfc3_cfg_setup( &nfc3_cfg );
    NFC3_MAP_MIKROBUS( nfc3_cfg, MIKROBUS_1 );
    err_t init_flag = nfc3_init( &nfc3, &nfc3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    nfc3_reset ( &nfc3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "------------------------\r\n" );
    nfc3_read_product_version ( &nfc3, &info );
    log_printf( &logger, "Product version: 0x%.4X\r\n", info );
    nfc3_read_firmware_version ( &nfc3, &info );
    log_printf( &logger, "Firmware version: 0x%.4X\r\n", info );
    nfc3_read_eeprom_version ( &nfc3, &info );
    log_printf( &logger, "EEPROM version: 0x%.4X\r\n", info );
    log_printf( &logger, "------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void ) 
{
    uint8_t uid[ 7 ];
    uint8_t uid_len;
    uid_len = nfc3_read_card_uid( &nfc3, uid );
    if ( uid_len > 0 )
    {
        log_printf( &logger, "Tag UID: " );
        for ( uint8_t cnt = 0; cnt < uid_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) uid[ cnt ] );
        }
        log_printf( &logger, "\r\n------------------------\r\n" );
        Delay_ms ( 1000 );
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

/*!
 * @file main.c
 * @brief NFC4 Click example
 *
 * # Description
 * This example demonstrates the use of NFC 4 Click board 
 * by reading MIFARE ISO/IEC 14443 type A tag UID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * If there's a tag detected, it reads its UID and displays it on the USB UART every 500ms.
 *
 * @note
 * For testing purposes we used MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc4.h"

static nfc4_t nfc4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    nfc4_cfg_t nfc4_cfg;    /**< Click config object. */

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
    nfc4_cfg_setup( &nfc4_cfg );
    NFC4_MAP_MIKROBUS( nfc4_cfg, MIKROBUS_1 );
    err_t init_flag  = nfc4_init( &nfc4, &nfc4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    NFC4_SET_DATA_SAMPLE_EDGE;
    
    if ( NFC4_ERROR == nfc4_default_cfg ( &nfc4 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t tag_uid[ 10 ] = { 0 };
    uint8_t uid_len = 0;
    
    if( NFC4_OK == nfc4_get_mifare_tag_uid( &nfc4, tag_uid, &uid_len ) )
    {
        log_printf( &logger, " Tag UID: " );
        for ( uint8_t cnt = 0; cnt < uid_len; cnt++ )
        {
            log_printf( &logger, "%.2X", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
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

/*!
 * @file main.c
 * @brief NFC Tag 2 Click example
 *
 * # Description
 * This example demonstrates the use of NFC Tag 2 Click by storing and verifying
 * an NDEF URI record in user EEPROM and monitoring the RF field.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, applies the default configuration, displays the tag UID,
 * and writes and verifies a URI record linking to the NFC Tag 2 Click product page.
 *
 * ## Application Task
 * Monitors the field detection pin and reports when an RF field is detected or removed.
 *
 * @note
 * Before first run, format the tag with NFC TagWriter using "Erase to factory default"
 * or "Erase & format as NDEF". Keep the phone away during initialization. Enable NFC
 * and use an NFC-enabled phone to open the stored product link.
 * Initialization replaces existing NDEF content; unchanged data is not rewritten.
 * RF field detection does not confirm that the phone has read the record.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfctag2.h"

#ifndef MIKROBUS_POSITION_NFCTAG2
    #define MIKROBUS_POSITION_NFCTAG2 MIKROBUS_1
#endif

/** Product page stored on the tag as an NDEF URI record. */
#define APP_NDEF_URI    "https://www.mikroe.com/nfc-tag-2-click"

static nfctag2_t nfctag2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfctag2_cfg_t nfctag2_cfg;  /**< Click config object. */

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
    nfctag2_cfg_setup( &nfctag2_cfg );
    NFCTAG2_MAP_MIKROBUS( nfctag2_cfg, MIKROBUS_POSITION_NFCTAG2 );
    if ( I2C_MASTER_ERROR == nfctag2_init( &nfctag2, &nfctag2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFCTAG2_ERROR == nfctag2_default_cfg ( &nfctag2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t uid[ NFCTAG2_UID_SIZE ];  /**< Seven-byte NFC tag identifier. */
    nfctag2_ndef_stage_t ndef_stage;  /**< Operation where NDEF preparation failed. */
    
    // Avoid competing with an RF reader while preparing EEPROM data.
    if ( NFCTAG2_FIELD_PRESENT == nfctag2_get_field_detect( &nfctag2 ) )
    {
        log_printf( &logger, " Remove the NFC reader during initialization.\r\n" );
        while ( NFCTAG2_FIELD_PRESENT == nfctag2_get_field_detect( &nfctag2 ) )
        {
            Delay_ms( 100 );
        }
    }

    if ( NFCTAG2_OK != nfctag2_get_uid( &nfctag2, uid ) )
    {
        log_error( &logger, " UID read." );
        for ( ; ; );
    }
    log_printf( &logger, " UID:" );
    for ( uint8_t cnt = 0; cnt < NFCTAG2_UID_SIZE; cnt++ )
    {
        log_printf( &logger, " %.2X", ( uint16_t ) uid[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    if ( NFCTAG2_OK != nfctag2_write_ndef_uri( &nfctag2, APP_NDEF_URI, &ndef_stage ) )
    {
        log_printf( &logger, " NDEF write failed at stage: %u\r\n", ( uint32_t ) ndef_stage );
        for ( ; ; );
    }
    log_printf( &logger, " NDEF URI stored and verified: %s\r\n", APP_NDEF_URI );

    log_printf( &logger, " Bring an NFC-enabled phone near the antenna to open the product page.\r\n" );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t previous_field = NFCTAG2_FIELD_ABSENT;  /**< Last reported FD pin level. */
    uint8_t field = nfctag2_get_field_detect( &nfctag2 );

    // GPIO polling leaves the shared memory available to the RF reader.
    if ( field != previous_field )
    {
        if ( NFCTAG2_FIELD_PRESENT == field )
        {
            log_printf( &logger, " RF field: Detected\r\n" );
        }
        else
        {
            log_printf( &logger, " RF field: Removed\r\n" );
        }
        previous_field = field;
    }
    Delay_ms( 10 );
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

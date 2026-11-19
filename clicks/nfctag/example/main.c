/*!
 * @file main.c
 * @brief NFC Tag Click example
 *
 * # Description
 * This example demonstrates the use of NFC Tag Click by storing and verifying
 * an NDEF URI record in user EEPROM and monitoring the GPO pin.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, applies the default configuration, displays the tag UID,
 * and writes and verifies a URI record linking to the NFC Tag Click product page.
 *
 * ## Application Task
 * Monitors the GPO pin and reports changes in its active-low output level.
 *
 * @note
 * Initialization replaces the NFC message on the Click board if it differs from the product link.
 * Keep your phone away during initialization, then hold it near the antenna with NFC enabled to open the link.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfctag.h"

#ifndef MIKROBUS_POSITION_NFCTAG
    #define MIKROBUS_POSITION_NFCTAG MIKROBUS_1
#endif

/** Product page stored on the tag as an NDEF URI record. */
#define APP_NDEF_URI    "https://www.mikroe.com/nfc-tag-click"

static nfctag_t nfctag;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfctag_cfg_t nfctag_cfg;  /**< Click config object. */
    err_t error_flag;

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
    nfctag_cfg_setup( &nfctag_cfg );
    NFCTAG_MAP_MIKROBUS( nfctag_cfg, MIKROBUS_POSITION_NFCTAG );
    if ( NFCTAG_ERROR == nfctag_init( &nfctag, &nfctag_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    error_flag = nfctag_default_cfg( &nfctag );
    if ( NFCTAG_OK != error_flag )
    {
        log_error( &logger, " Default configuration failed, error: %d, SW: %.4X",
                   ( int16_t ) error_flag, ( uint16_t ) nfctag.last_status );
        for ( ; ; );
    }
    
    uint8_t uid[ NFCTAG_UID_SIZE ];  /**< Seven-byte NFC tag identifier. */
    nfctag_ndef_stage_t ndef_stage;  /**< Operation where NDEF preparation failed. */
    
    error_flag = nfctag_get_uid( &nfctag, uid );
    if ( NFCTAG_OK != error_flag )
    {
        log_error( &logger, " UID read failed at stage: %u, error: %d, SW: %.4X",
                   ( uint16_t ) nfctag.uid_stage, ( int16_t ) error_flag, ( uint16_t ) nfctag.last_status );
        for ( ; ; );
    }
    log_printf( &logger, " UID:" );
    for ( uint8_t cnt = 0; cnt < NFCTAG_UID_SIZE; cnt++ )
    {
        log_printf( &logger, " %.2X", ( uint16_t ) uid[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    error_flag = nfctag_write_ndef_uri( &nfctag, APP_NDEF_URI, &ndef_stage );
    if ( NFCTAG_OK != error_flag )
    {
        log_printf( &logger, " NDEF write failed at stage: %u, error: %d, SW: %.4X\r\n",
                    ( uint16_t ) ndef_stage, ( int16_t ) error_flag, ( uint16_t ) nfctag.last_status );
        for ( ; ; );
    }
    log_printf( &logger, " NDEF URI stored and verified: %s\r\n", ( char * ) APP_NDEF_URI );

    log_printf( &logger, " Bring an NFC-enabled phone near the antenna to open the product page.\r\n" );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t previous_gpo = NFCTAG_GPO_INACTIVE;  /**< Previous GPO pin level. */
    uint8_t gpo = nfctag_get_gpo( &nfctag );

    // GPIO polling leaves the shared memory available to the RF reader.
    if ( gpo != previous_gpo )
    {
        if ( NFCTAG_GPO_ACTIVE == gpo )
        {
            log_printf( &logger, " GPO: Active\r\n" );
        }
        else
        {
            log_printf( &logger, " GPO: Inactive\r\n" );
        }
        previous_gpo = gpo;
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

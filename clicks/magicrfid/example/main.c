/*!
 * @file main.c
 * @brief Magic RFID Click Example.
 *
 * # Description
 * This example reads and processes data from Magic RFID clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize driver init and starts default configuration module.
 *
 * ## Application Task
 * Reads TAG information and RSSI value of the TAG and logs it on UART.
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "magicrfid.h"

static magicrfid_t magicrfid;
static log_t logger;
static magicrfid_data_t tag;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magicrfid_cfg_t magicrfid_cfg;  /**< Click config object. */

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
    magicrfid_cfg_setup( &magicrfid_cfg );
    MAGICRFID_MAP_MIKROBUS( magicrfid_cfg, MIKROBUS_1 );
    if ( UART_ERROR == magicrfid_init( &magicrfid, &magicrfid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, " >> Please, wait for device setup. \r\n" );
    magicrfid_default_cfg ( &magicrfid );
    Delay_ms( 1000 );
    log_printf( &logger, " >> Initialization done, reading tag is available. \r\n" );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    magicrfid_process( &magicrfid, &tag );
    if ( magicrfid_get_data_status( &tag ) == 1 ) 
    {
        magicrfid_tag_parser( &tag );

        log_printf( &logger, " >> TAG INFO: 0x" );
        for( uint8_t cnt = 0; cnt < 12; cnt++ ) 
        {
            log_printf( &logger, "%.2X", ( uint16_t ) tag.tag_buf[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " >> TAG RSSI: %d\r\n", ( uint16_t ) tag.tag_rssi );
        magicrfid_reset_data( &tag );
    }
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

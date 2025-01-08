/*!
 * @file main.c
 * @brief Magic RFID Click Example.
 *
 * # Description
 * This example reads and processes data from Magic RFID Clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize driver init and starts default configuration module.
 *
 * ## Application Task
 * Scans for RFID TAGs and displays on the USB UART the EPC bytes of the detected tag.
 * It also parses and displays the RSSI as well as the frequency this tag was detected at.
 * 
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "magicrfid.h"

static magicrfid_t magicrfid;
static log_t logger;

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
    magicrfid_default_cfg ( &magicrfid );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    magicrfid_response_t rsp = { 0 };
    if ( ( MAGICRFID_OK == magicrfid_get_response ( &magicrfid, &rsp ) ) && 
         ( MAGICRFID_OPCODE_READ_TAG_ID_MULTIPLE == rsp.opcode ) )
    {
        if ( 0 == rsp.data_len )
        {
            log_printf( &logger, "\r\n --- SCANNING ---\r\n" );
        }
        else
        {
            log_printf( &logger, "\r\n --- TAG DETECTED ---\r\n" );
            int8_t tag_rssi = 0;
            uint32_t tag_freq = 0;
            magicrfid_epc_t epc = { 0 };
            tag_rssi = magicrfid_parse_tag_rssi ( rsp );
            log_printf( &logger, " RSSI: %d\r\n", ( int16_t ) tag_rssi );
            tag_freq = magicrfid_parse_tag_freq ( rsp );
            log_printf( &logger, " FREQ: %lu\r\n", tag_freq );
            magicrfid_parse_tag_epc ( rsp, &epc );
            log_printf( &logger, " EPC PC: 0x%.4X\r\n", epc.epc_pc );
            log_printf( &logger, " EPC ID (len: %u): ", ( uint16_t ) epc.data_len );
            for ( uint8_t cnt = 0; cnt < epc.data_len; cnt++ )
            {
                log_printf( &logger, "%.2X", ( uint16_t ) epc.data_buf[ cnt ] );
            }
            log_printf( &logger, "\r\n EPC CRC: 0x%.4X\r\n", epc.epc_crc );
            Delay_ms ( 100 );
            magicrfid_clear_buffers ( &magicrfid );
        }
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

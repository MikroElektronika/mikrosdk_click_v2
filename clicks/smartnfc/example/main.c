/*!
 * @file main.c
 * @brief Smart NFC Click Example.
 *
 * # Description
 * This example demonstrates the use of the Smart NFC Click board for detecting and 
 * reading NFC tags. The application resets the NFC module, retrieves the firmware 
 * version, and continuously scans for nearby NFC tags, displaying their UID and type.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Smart NFC Click board. It establishes 
 * UART communication, resets the NFC module, and retrieves the firmware version 
 * to verify proper operation.
 *
 * ## Application Task
 * Continuously scans for NFC tags and retrieves their unique identifiers (UID). 
 * If tags are detected, it logs their type, parameters, and UID values. The process 
 * repeats at 1-second intervals.
 *
 * @note
 * A proper 13.56 MHz PCB NFC antenna must be attached to the Click board module
 * for optimal tag detection.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartnfc.h"

static smartnfc_t smartnfc;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartnfc_cfg_t smartnfc_cfg;  /**< Click config object. */

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
    smartnfc_cfg_setup( &smartnfc_cfg );
    SMARTNFC_MAP_MIKROBUS( smartnfc_cfg, MIKROBUS_1 );
    if ( UART_ERROR == smartnfc_init( &smartnfc, &smartnfc_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset Device\r\n" );
    if ( SMARTNFC_OK == smartnfc_reset_device ( &smartnfc ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
    }
    
    log_printf( &logger, ">> Get Version\r\n" );
    smartnfc.cmd_frame.cmd = SMARTNFC_CMD_GET_VERSION;
    smartnfc.cmd_frame.payload_len = 0;
    smartnfc_send_frame ( &smartnfc );
    if ( SMARTNFC_OK == smartnfc_read_ack_frame ( &smartnfc, SMARTNFC_CMD_GET_VERSION ) )
    {
        log_printf ( &logger, "%s\r\n", &smartnfc.rsp_frame.payload[ 1 ] );
        log_printf( &logger, "--------------------------------\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t num_tags_found = 0;
    log_printf( &logger, ">> Get Tag Count\r\n" );
    smartnfc.cmd_frame.cmd = SMARTNFC_CMD_GET_TAG_COUNT;
    smartnfc.cmd_frame.payload_len = 0;
    smartnfc_send_frame ( &smartnfc );
    if ( SMARTNFC_OK == smartnfc_read_ack_frame ( &smartnfc, SMARTNFC_CMD_GET_TAG_COUNT ) )
    {
        log_printf ( &logger, "Number of tags found: %u\r\n", ( uint16_t ) smartnfc.rsp_frame.payload[ 1 ] );
        log_printf( &logger, "--------------------------------\r\n" );
        num_tags_found = smartnfc.rsp_frame.payload[ 1 ];
        for ( uint8_t tag_idx = 0; tag_idx < num_tags_found; tag_idx++ )
        {
            log_printf( &logger, ">> Get Tag UID\r\n" );
            smartnfc.cmd_frame.cmd = SMARTNFC_CMD_GET_TAG_UID;
            smartnfc.cmd_frame.payload[ 0 ] = tag_idx;
            smartnfc.cmd_frame.payload_len = 1;
            smartnfc_send_frame ( &smartnfc );
            if ( SMARTNFC_OK == smartnfc_read_ack_frame ( &smartnfc, SMARTNFC_CMD_GET_TAG_UID ) )
            {
                log_printf ( &logger, "Tag Type: 0x%.2X\r\n", ( uint16_t ) smartnfc.rsp_frame.payload[ 1 ] );
                log_printf ( &logger, "Tag Parameter: 0x%.2X\r\n", ( uint16_t ) smartnfc.rsp_frame.payload[ 2 ] );
                log_printf ( &logger, "UID:" );
                for ( uint8_t cnt_uid = 0; cnt_uid < ( smartnfc.rsp_frame.payload_len - 3 ); cnt_uid++ )
                {
                    log_printf ( &logger, " %.2X", ( uint16_t ) smartnfc.rsp_frame.payload[ 3 + cnt_uid ] );
                }
                log_printf( &logger, "\r\n--------------------------------\r\n" );
            }
        }
    }
    Delay_ms ( 1000 );
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

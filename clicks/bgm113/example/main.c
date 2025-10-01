/**
 * @file main.c
 * @brief BGM113 Click Example.
 *
 * # Description
 * This example demonstrates the usage of the BGM113 Click board. The application initializes
 * the module, resets the device, checks communication, retrieves the BT address, 
 * and manages bondings. It also configures the device to be discoverable and bondable 
 * and handles various BT-related events such as connection state changes, 
 * security mode, and GATT operations.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and sets up the BGM113 Click configuration. Resets the device, 
 * checks communication, retrieves the BT address, and deletes existing bondings. 
 * Configures the device to be bondable and sets LE GAP modes.
 *
 * ## Application Task
 * Continuously reads packets from the BGM113, parses the contents, and logs relevant information 
 * regarding system events, BT connections, and bonding information.
 *
 * ## Additional Function
 * - static void bgm113_display_packet ( bgm113_t *ctx )
 * - static void bgm113_parse_packet ( bgm113_t *ctx )
 *
 * @note
 * We recommend using the Simplicity Connect smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bgm113.h"

static bgm113_t bgm113;
static log_t logger;

/**
 * @brief BGM113 Display Packet function.
 * @details This function logs the details of a received packet, including message type, 
 * class, ID, payload length, and payload content if available.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @note None.
 */
static void bgm113_display_packet ( bgm113_t *ctx );

/**
 * @brief BGM113 Parse Packet function.
 * @details This function parses a received packet and logs or processes it based on 
 * the message class and ID. It handles system, LE GAP, SM, GATT, and connection 
 * events, extracting relevant data such as addresses, version numbers, 
 * connection parameters, and bond information.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @note None.
 */
static void bgm113_parse_packet ( bgm113_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bgm113_cfg_t bgm113_cfg;  /**< Click config object. */

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
    bgm113_cfg_setup( &bgm113_cfg );
    BGM113_MAP_MIKROBUS( bgm113_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bgm113_init( &bgm113, &bgm113_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">> Reset Device\r\n" );
    if ( BGM113_OK == bgm113_reset_device ( &bgm113 ) )
    {   
        bgm113_parse_packet ( &bgm113 );
    }

    log_printf( &logger, ">> Check Communication\r\n" );
    if ( BGM113_OK == bgm113_check_communication ( &bgm113 ) )
    {   
        bgm113_parse_packet ( &bgm113 );
    }

    log_printf( &logger, ">> Get BT Address\r\n" );
    if ( BGM113_OK == bgm113_get_bt_address ( &bgm113 ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }

    log_printf( &logger, ">> Delete Bondings\r\n" );
    if ( BGM113_OK == bgm113_delete_bondings ( &bgm113 ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }
    
    log_printf( &logger, ">> Set Bondable Mode\r\n" );
    if ( BGM113_OK == bgm113_set_bondable_mode ( &bgm113, BGM113_SM_SET_BONDABLE_ALLOWED ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }
    
    log_printf( &logger, ">> Set LE GAP Mode\r\n" );
    if ( BGM113_OK == bgm113_set_gap_mode ( &bgm113, BGM113_LE_GAP_UNDIRECTED_CONNECTABLE, 
                                                     BGM113_LE_GAP_GENERAL_DISCOVERABLE ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( BGM113_OK == bgm113_read_packet ( &bgm113 ) ) 
    {
        bgm113_parse_packet ( &bgm113 );
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

static void bgm113_display_packet ( bgm113_t *ctx )
{
    log_printf( &logger, " < Message Type: " );
    if ( BGM113_MSG_TYPE_RESPONSE == ctx->rsp_pkt.msg_type )
    {
        log_printf( &logger, "Response\r\n" );
    }
    else if ( BGM113_MSG_TYPE_EVENT == ctx->rsp_pkt.msg_type )
    {
        log_printf( &logger, "Event\r\n" );
    }
    else
    {
        log_printf( &logger, "Unknown\r\n\n" );
        return;
    }
    log_printf( &logger, "   Message Class: 0x%.2X\r\n", ( uint16_t ) ctx->rsp_pkt.msg_class );
    log_printf( &logger, "   Message ID: 0x%.2X\r\n", ( uint16_t ) ctx->rsp_pkt.msg_id );
    log_printf( &logger, "   Payload len: 0x%.2X\r\n", ( uint16_t ) ctx->rsp_pkt.payload_len );
    if ( ctx->rsp_pkt.payload_len > 0 )
    {
        log_printf( &logger, "   Payload:" );
        for ( uint8_t cnt = 0; cnt < ctx->rsp_pkt.payload_len; cnt++ )
        {
            log_printf( &logger, " 0x%.2X", ( uint16_t ) ctx->rsp_pkt.payload[ cnt ] );
        }
        log_printf( &logger, "\r\n\n" );
    }
}

static void bgm113_parse_packet ( bgm113_t *ctx )
{
    uint8_t byte_cnt = 0;
    uint16_t result = 0;

    if ( BGM113_MSG_TYPE_RESPONSE == ctx->rsp_pkt.msg_type )
    {
        switch ( ctx->rsp_pkt.msg_class )
        {
            case BGM113_MSG_CLASS_SYSTEM:
            {
                if ( BGM113_MSG_ID_SYSTEM_HELLO == ctx->rsp_pkt.msg_id )
                {
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, " < %s\r\n\n", ( char * ) ( ( 0 == result ) ? "OK" : "FAIL" ) );
                }
                else if ( BGM113_MSG_ID_SYSTEM_GET_BT_ADDRESS == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n\n", 
                                ( uint16_t ) bgm113.rsp_pkt.payload[ 5 ], 
                                ( uint16_t ) bgm113.rsp_pkt.payload[ 4 ], 
                                ( uint16_t ) bgm113.rsp_pkt.payload[ 3 ],
                                ( uint16_t ) bgm113.rsp_pkt.payload[ 2 ], 
                                ( uint16_t ) bgm113.rsp_pkt.payload[ 1 ], 
                                ( uint16_t ) bgm113.rsp_pkt.payload[ 0 ] );
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            case BGM113_MSG_CLASS_LE_GAP:
            {
                if ( BGM113_MSG_ID_LE_GAP_SET_MODE == ctx->rsp_pkt.msg_id )
                {
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, " < %s\r\n\n", ( char * ) ( ( 0 == result ) ? "OK" : "FAIL" ) );
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            case BGM113_MSG_CLASS_SM:
            {
                if ( BGM113_MSG_ID_SM_SET_BONDABLE_MODE == ctx->rsp_pkt.msg_id )
                {
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, " < %s\r\n\n", ( char * ) ( ( 0 == result ) ? "OK" : "FAIL" ) );
                }
                else if ( BGM113_MSG_ID_SM_DELETE_BONDINGS == ctx->rsp_pkt.msg_id )
                {
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, " < %s\r\n\n", ( char * ) ( ( 0 == result ) ? "OK" : "FAIL" ) );
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            default:
            {
                bgm113_display_packet ( ctx );
                break;
            }
        }
    }
    else if ( BGM113_MSG_TYPE_EVENT == ctx->rsp_pkt.msg_type )
    {
        switch ( ctx->rsp_pkt.msg_class )
        {
            case BGM113_MSG_CLASS_SYSTEM:
            {
                if ( BGM113_MSG_ID_EVT_SYSTEM_BOOT == ctx->rsp_pkt.msg_id )
                {
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, " < Release version: %u.", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 3 ] << 8 ) | ctx->rsp_pkt.payload[ 2 ];
                    log_printf( &logger, "%u.", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 5 ] << 8 ) | ctx->rsp_pkt.payload[ 4 ];
                    log_printf( &logger, "%u\r\n", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 7 ] << 8 ) | ctx->rsp_pkt.payload[ 6 ];
                    log_printf( &logger, "   Build number: %u\r\n", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 9 ] << 8 ) | ctx->rsp_pkt.payload[ 8 ];
                    log_printf( &logger, "   Bootloader version: %u\r\n", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 11 ] << 8 ) | ctx->rsp_pkt.payload[ 10 ];
                    log_printf( &logger, "   Hardware type: %u\r\n\n", result );
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            case BGM113_MSG_CLASS_GATT:
            {
                if ( BGM113_MSG_ID_EVT_GATT_MTU_EXCHANGED == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < Connection handle: %u\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 0 ] );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 2 ] << 8 ) | ctx->rsp_pkt.payload[ 1 ];
                    log_printf( &logger, "   Exchanged GATT MTU: %u\r\n\n", result );
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            case BGM113_MSG_CLASS_LE_CONNECTION:
            {
                if ( BGM113_MSG_ID_EVT_LE_CONNECTION_OPENED == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < Connection handle: %u\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 8 ] );
                    log_printf( &logger, "   Connection state: Opened\r\n" );
                    log_printf( &logger, "   Address of remote device: " );
                    log_printf( &logger, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 5 ],
                                                                              ( uint16_t ) ctx->rsp_pkt.payload[ 4 ], 
                                                                              ( uint16_t ) ctx->rsp_pkt.payload[ 3 ],
                                                                              ( uint16_t ) ctx->rsp_pkt.payload[ 2 ],
                                                                              ( uint16_t ) ctx->rsp_pkt.payload[ 1 ],
                                                                              ( uint16_t ) ctx->rsp_pkt.payload[ 0 ] );
                    log_printf( &logger, "   Role of the local device: %s\r\n", ( char * )
                                ( 0 == ctx->rsp_pkt.payload[ 7 ] ? "Slave" : "Master" ) );
                    
                    log_printf( &logger, "   Bonding handle: " );
                    if ( 0xFF == ctx->rsp_pkt.payload[ 9 ] )
                    {
                        log_printf( &logger, "No bonding\r\n\n" );
                    }
                    else
                    {
                        log_printf( &logger, "%u\r\n\n", ( uint16_t ) ctx->rsp_pkt.payload[ 9 ] );
                    }
                }
                else if ( BGM113_MSG_ID_EVT_LE_CONNECTION_CLOSED == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < Connection handle: %u\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 2 ] );
                    log_printf( &logger, "   Connection state: Closed\r\n" );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, "   Reason: 0x%.4X\r\n\n", result );
                    log_printf( &logger, ">> Set LE GAP Mode\r\n" );
                    if ( BGM113_OK == bgm113_set_gap_mode ( &bgm113, BGM113_LE_GAP_UNDIRECTED_CONNECTABLE, 
                                                                     BGM113_LE_GAP_GENERAL_DISCOVERABLE ) )
                    {
                        bgm113_parse_packet ( &bgm113 );
                    }
                }
                else if ( BGM113_MSG_ID_EVT_LE_CONNECTION_PARAMS == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < Connection handle: %u\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 0 ] );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 2 ] << 8 ) | ctx->rsp_pkt.payload[ 1 ];
                    log_printf( &logger, "   Connection interval: %u\r\n", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 4 ] << 8 ) | ctx->rsp_pkt.payload[ 3 ];
                    log_printf( &logger, "   Slave latency: %u\r\n", result );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 6 ] << 8 ) | ctx->rsp_pkt.payload[ 5 ];
                    log_printf( &logger, "   Supervision timeout: %u\r\n", result );
                    log_printf( &logger, "   Connection security mode: %u\r\n\n", ( uint16_t ) ctx->rsp_pkt.payload[ 7 ] );
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            case BGM113_MSG_CLASS_SM:
            {
                if ( BGM113_MSG_ID_EVT_SM_BONDED == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < Connection handle: %u\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 0 ] );
                    log_printf( &logger, "   Bonding handle: " );
                    if ( 0xFF == ctx->rsp_pkt.payload[ 1 ] )
                    {
                        log_printf( &logger, "No bonding\r\n\n" );
                    }
                    else
                    {
                        log_printf( &logger, "%u\r\n\n", ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] );
                    }
                }
                else if ( BGM113_MSG_ID_EVT_SM_BONDING_FAILED == ctx->rsp_pkt.msg_id )
                {
                    log_printf( &logger, " < Connection handle: %u\r\n", ( uint16_t ) ctx->rsp_pkt.payload[ 0 ] );
                    result = ( ( uint16_t ) ctx->rsp_pkt.payload[ 1 ] << 8 ) | ctx->rsp_pkt.payload[ 0 ];
                    log_printf( &logger, "   Reason: 0x%.4X\r\n\n", result );
                    log_printf( &logger, ">> Delete Bondings\r\n" );
                    if ( BGM113_OK == bgm113_delete_bondings ( &bgm113 ) )
                    {
                        bgm113_parse_packet ( &bgm113 );
                    }
                }
                else
                {
                    bgm113_display_packet ( ctx );
                }
                break;
            }
            default:
            {
                bgm113_display_packet ( ctx );
                break;
            }
        }
    }
    else 
    {
        bgm113_display_packet ( ctx );
    }
}

// ------------------------------------------------------------------------ END

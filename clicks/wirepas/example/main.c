/*!
 * @file main.c
 * @brief Wirepas Click Example.
 *
 * # Description
 * This example demonstrates the use of Wirepas Click board by processing
 * the incoming data and displaying them on the USB UART in sink mode, and sending data to 
 * the sinks in router mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration, setting device mode, node,
 * net and channel addresses, and starting stack.
 *
 * ## Application Task
 * Router mode - Sending data to the sinks at the same network.
 * Sink mode - Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - err_t wirepas_wait_response ( wirepas_t *ctx, uint8_t primitive_id )
 * - err_t wirepas_parse_frame ( wirepas_t *ctx, uint8_t primitive_id )
 * - err_t wirepas_poll_indication ( wirepas_t *ctx )
 *
 * @note
 * For the best experience use two clicks in sink mode and one in router.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "wirepas.h"

#define PROCESS_BUFFER_SIZE 300
#define TX_DATA             "Wirepas Click"

#define MULTI_SINK_MODE     // Comment out this macro to place device into single sink mode.

/**
* @brief Wirepas node addresses.
 * @details Specified setting for node addresses of Wirepas Click driver.
 */
#define ROUTER_NODE_ADDRESS         0x01
#define SINK_1_NODE_ADDRESS         0x02
#define SINK_2_NODE_ADDRESS         0x03
#define NET_ADDRESS                 0x01
#define CHANNEL_ADDRESS             0x01

#define NODE_ADDRESS                ROUTER_NODE_ADDRESS    /* Change the value of this macro to change 
                                                              node address, each node should have a unique address */

static wirepas_t wirepas;
static log_t logger;
uint8_t frame_id = 0;
uint8_t stack_auto_start = 1;
uint8_t pdu_capacity = 0x10;
wirepas_sink_data sink_1;
wirepas_sink_data sink_2;

/**
 * @brief Wirepas wait response function.
 * @details This function is used to get response from the device. 
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] primitive_id : Expected Primitive ID.
 * @return @li @c >=0 - Success,
 *         @li @c  <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_wait_response ( wirepas_t *ctx, uint8_t primitive_id );

/**
 * @brief Wirepas parse frame function.
 * @details This function is used to parse frame response from the device. 
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] primitive_id : Expected Primitive ID.
 * @return @li @c >=0 - Success,
 *         @li @c  <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_parse_frame ( wirepas_t *ctx, uint8_t primitive_id );

/**
 * @brief Wirepas send poll indication function function.
 * @details This function is used to send poll indication, 
 * and get response from the device. 
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] primitive_id : Expected Primitive ID.
 * @return @li @c >=0 - Success,
 *         @li @c  <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_poll_indication ( wirepas_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wirepas_cfg_t wirepas_cfg;  /**< Click config object. */

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
    wirepas_cfg_setup( &wirepas_cfg );
    WIREPAS_MAP_MIKROBUS( wirepas_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wirepas_init( &wirepas, &wirepas_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    wirepas_default_cfg ( &wirepas );
   
    wirepas.tx_frame_id = 0;
    do
    {
        log_printf( &logger, " Wirepas stack stop request:" );
        wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_STOP_REQUEST, 0, NULL );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_MSAP_STACK_STOP_CONFIRM ) );
    Delay_ms ( 1000 );
    
    do
    {
        log_printf( &logger, " Wirepas factory reset request:" );
        wirepas_send_command( &wirepas, WIREPAS_CSAP_FACTORY_RESET_REQUEST,
                              strlen( WIREPAS_FACTORY_RESET_CODE ), WIREPAS_FACTORY_RESET_CODE );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_FACTORY_RESET_CONFIRM ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    do
    {
        log_printf( &logger, " Set node address:" );
        wirepas_set_node_address( &wirepas, NODE_ADDRESS );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_ms ( 1000 );
    
    do
    {
        log_printf( &logger, " Set net address:" );
        wirepas_set_net_address( &wirepas, NET_ADDRESS );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_ms ( 1000 );
    
    uint8_t channel_net = CHANNEL_ADDRESS;
    do
    {
        log_printf( &logger, " Set channel address:" );
        wirepas_write_csap_attribute( &wirepas, WIREPAS_CSAP_ATTRIBUTE_NETWORK_CHANNEL, 1, &channel_net );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_ms ( 1000 );


    uint8_t role;
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    role = WIREPAS_ROUTER_NODE_MODE;
#else
    role = WIREPAS_SINK_NODE_MODE;
#endif
    do
    {
        log_printf( &logger, " Set role:" );
        wirepas_write_csap_attribute( &wirepas, WIREPAS_CSAP_ATTRIBUTE_NODE_ROLE, 1, &role );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM ) );
    Delay_1sec( );
    
    do
    {
        log_printf( &logger, " Wirepas Stack start request:" ); 
        wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_START_REQUEST, 1, &stack_auto_start );
    }
    while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_MSAP_STACK_START_CONFIRM ) );
    Delay_1sec( );
        
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )

    sink_1.pduid = 0x00;
    sink_1.source_endpoint = 0x01;
    sink_1.destination_addr = SINK_1_NODE_ADDRESS;
    sink_1.destination_endpoint = 0x01;
    #if defined MULTI_SINK_MODE
        sink_2.pduid = 0x00;
        sink_2.source_endpoint = 0x01;
        sink_2.destination_addr = SINK_2_NODE_ADDRESS;
        sink_2.destination_endpoint = 0x01;
    #endif
#endif
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    wirepas_poll_indication ( &wirepas );
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    if ( wirepas_get_din_state ( &wirepas ) && ( pdu_capacity > 0 ) )
    {
        log_printf( &logger, " Sending data to the first Sink node: \n" );
        wirepas_send_data ( &wirepas,  sink_1, 0x01, strlen( TX_DATA ), TX_DATA );
        wirepas_wait_response ( &wirepas, WIREPAS_DSAP_DATA_TX_CONFIRM );
        Delay_ms ( 1000 );
        
        #if defined MULTI_SINK_MODE
            log_printf( &logger, " Sending data to the second Sink node: \n" );
            wirepas_send_data ( &wirepas,  sink_2, 0x01, strlen( TX_DATA ), TX_DATA );
            wirepas_wait_response ( &wirepas, WIREPAS_DSAP_DATA_TX_CONFIRM );
            Delay_ms ( 1000 );
        #endif
    }
#endif
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

err_t wirepas_wait_response ( wirepas_t *ctx, uint8_t primitive_id )
{
    for ( uint8_t cnt = 0; cnt < 5; cnt++ )
    {
        if ( WIREPAS_OK == wirepas_parse_frame ( ctx, primitive_id ) )
        {
            return WIREPAS_OK;
        }
    }
    return WIREPAS_ERROR;
}

err_t wirepas_parse_frame ( wirepas_t *ctx, uint8_t primitive_id )
{
    err_t error_flag = wirepas_read_frame ( ctx, &ctx->frame );
    if ( WIREPAS_OK == error_flag )
    {
        if ( ( primitive_id != ctx->frame.primitive_id ) && ( 0 != primitive_id ) )
        {
            error_flag |= WIREPAS_ERROR;
        }
        switch ( ctx->frame.primitive_id )
        {
            case WIREPAS_MSAP_STACK_STOP_CONFIRM:
            case WIREPAS_MSAP_STACK_START_CONFIRM:
            case WIREPAS_CSAP_FACTORY_RESET_CONFIRM:
            case WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM:
            {
                if ( 0 == ctx->frame.payload[ 0 ] )
                {
                    log_printf( &logger, " OK\r\n" );
                }
                else 
                {
                    log_printf( &logger, " ERROR[%u]\r\n", ( uint16_t ) ctx->frame.payload[ 0 ] );
                    error_flag |= WIREPAS_ERROR;
                }
                break;
            }
            case WIREPAS_DSAP_DATA_TX_CONFIRM:
            {
                pdu_capacity = ctx->frame.payload[ 3 ];
                if ( 0 == ctx->frame.payload[ 2 ] )
                {
                    log_printf( &logger, " TX request with PDU_ID[%u] is placed\r\n", 
                                ( ( ( uint16_t ) ctx->frame.payload[ 1 ] << 8 ) | ctx->frame.payload[ 0 ] ) );
                    sink_1.pduid += 1;
                    if ( sink_1.pduid >= 16 )
                    {
                        sink_1.pduid = 0;
                    }
                #if defined MULTI_SINK_MODE
                    sink_2.pduid += 1;
                    if ( sink_2.pduid >= 16 )
                    {
                        sink_2.pduid = 0;
                    }
                #endif
                }
                else 
                {
                    log_printf( &logger, " ERROR[%u] on TX request with PDU_ID[%u]\r\n", ( uint16_t ) ctx->frame.payload[ 2 ],
                                ( ( ( uint16_t ) ctx->frame.payload[ 1 ] << 8 ) | ctx->frame.payload[ 0 ] ) );
                    error_flag |= WIREPAS_ERROR;
                }
                break;
            }
            case WIREPAS_MSAP_INDICATION_POLL_CONFIRM:
            {
                if ( 1 == ctx->frame.payload[ 0 ] )
                {
                    log_printf( &logger, " There are pending indications\r\n" );
                }
                else
                {
                    log_printf( &logger, " No pending indications on poll request\r\n" );
                }
                break;
            }
            case WIREPAS_DSAP_DATA_TX_INDICATION:
            {
                wirepas_send_ack ( ctx, WIREPAS_DSAP_DATA_TX_RESPONSE, ctx->frame.frame_id, ctx->frame.payload[ 0 ] );
                log_printf( &logger, " TX data with PDU_ID[%u] is sent to dest address: %lu\r\n", 
                            ( ( ( uint16_t ) ctx->frame.payload[ 2 ] << 8 ) | ctx->frame.payload[ 1 ] ),
                            ( ( ( uint32_t ) ctx->frame.payload[ 7 ] << 24 ) | ( ( uint32_t ) ctx->frame.payload[ 6 ] << 16 ) |
                              ( ( uint16_t ) ctx->frame.payload[ 5 ] << 8 ) | ctx->frame.payload[ 4 ] ) );
                pdu_capacity++;
                break;
            }
            case WIREPAS_DSAP_DATA_RX_INDICATION:
            {
                wirepas_send_ack ( ctx, WIREPAS_DSAP_DATA_RX_RESPONSE, ctx->frame.frame_id, ctx->frame.payload[ 0 ] );
                log_printf( &logger, " RX data is received from src address: %lu\r\n", 
                            ( ( ( uint32_t ) ctx->frame.payload[ 4 ] << 24 ) | ( ( uint32_t ) ctx->frame.payload[ 3 ] << 16 ) |
                              ( ( uint16_t ) ctx->frame.payload[ 2 ] << 8 ) | ctx->frame.payload[ 1 ] ) );
                log_printf( &logger, " RX data: " );
                for ( uint8_t cnt = 0; cnt < ctx->frame.payload[ 16 ]; cnt++ )
                {
                    log_printf( &logger, "%c", ctx->frame.payload[ 17 + cnt ] );
                }
                log_printf( &logger, "\r\n---------------------------\r\n" );
                break;
            }
            case WIREPAS_MSAP_STACK_STATE_INDICATION:
            {
                wirepas_send_ack ( ctx, WIREPAS_MSAP_STACK_STATE_RESPONSE, ctx->frame.frame_id, ctx->frame.payload[ 0 ] );
                log_printf( &logger, " Stack state indication: 0x%.2X\r\n", ctx->frame.payload[ 1 ] );
                break;
            }
            case WIREPAS_MSAP_APP_CONFIG_DATA_RX_IND:
            {
                wirepas_send_ack ( ctx, WIREPAS_MSAP_APP_CONFIG_DATA_RX_RESP, ctx->frame.frame_id, ctx->frame.payload[ 0 ] );
                log_printf( &logger, " MSAP app config data rx indication\r\n" );
                break;
            }
            case WIREPAS_MSAP_SCAN_NBORS_INDICATION:
            {
                wirepas_send_ack ( ctx, WIREPAS_MSAP_SCAN_NBORS_RESPONSE, ctx->frame.frame_id, ctx->frame.payload[ 0 ] );
                if ( ctx->frame.payload[ 1 ] )
                {
                    log_printf( &logger, " Neighbors scan is done and ready\r\n" );
                }
                else
                {
                    log_printf( &logger, " Neighbors scan is NOT done and ready\r\n" );
                }
                break;
            }
            default:
            {
                log_printf( &logger, " Frame with unknown primitive ID [0x%.2X] is received\r\n", 
                            ( uint16_t ) ctx->frame.primitive_id );
                log_printf( &logger, " Frame ID: %u\r\n", ( uint16_t ) ctx->frame.primitive_id );
                log_printf( &logger, " Payload len: %u\r\n", ( uint16_t ) ctx->frame.payload_len );
                log_printf( &logger, " Payload: ", ( uint16_t ) ctx->frame.payload_len );
                for ( uint8_t cnt = 0; cnt < ctx->frame.payload_len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ctx->frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                error_flag |= WIREPAS_ERROR;
                break;
            }
        }
    }
    return error_flag;
}

err_t wirepas_poll_indication ( wirepas_t *ctx )
{
    err_t error_flag = WIREPAS_OK;
    uint32_t timeout_cnt = 0;
    while ( wirepas_get_din_state ( ctx ) )
    {
        if ( timeout_cnt++ > 2000 )
        {
            log_printf( &logger, " No pending indications on DIN pin\r\n" );
            break;
        }
        Delay_1ms ( );
    }
    timeout_cnt = 0;

    wirepas_send_command( ctx, WIREPAS_MSAP_INDICATION_POLL_REQUEST, 0, NULL );
    error_flag |= wirepas_wait_response ( ctx, WIREPAS_MSAP_INDICATION_POLL_CONFIRM );
    if ( WIREPAS_OK != error_flag )
    {
        return WIREPAS_ERROR;
    }
    while ( ( WIREPAS_OK == error_flag ) && ( ctx->frame.payload[ 0 ] == 0x01 ) )
    {
        error_flag |= wirepas_parse_frame ( ctx, 0 );
        if ( WIREPAS_OK == error_flag )
        {
            switch ( ctx->frame.primitive_id )
            {
                case WIREPAS_DSAP_DATA_TX_INDICATION:
                case WIREPAS_DSAP_DATA_RX_INDICATION:
                case WIREPAS_MSAP_STACK_STATE_INDICATION:
                case WIREPAS_MSAP_APP_CONFIG_DATA_RX_IND:
                case WIREPAS_MSAP_SCAN_NBORS_INDICATION:
                {
                    if ( ( ctx->frame.payload[ 0 ] == 0x00 ) )
                    {
                        while ( !wirepas_get_din_state ( ctx ) )
                        {
                            if ( timeout_cnt++ > 200 )
                            {
                                log_printf( &logger, " ERROR no IRQ clear\r\n" );
                                error_flag |= WIREPAS_ERROR;
                                break;
                            }
                            Delay_1ms ( );
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        else
        {
            log_printf( &logger, " ERROR on indication frame parse\r\n" );
        }
        if ( WIREPAS_OK != error_flag )
        {
            do
            {
                log_printf( &logger, " Wirepas stack stop request:" );
                wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_STOP_REQUEST, 0, NULL );
            }
            while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_MSAP_STACK_STOP_CONFIRM ) );
            Delay_1sec( );

            do
            {
                log_printf( &logger, " Wirepas Stack start request:" ); 
                wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_START_REQUEST, 1, &stack_auto_start );
            }
            while ( WIREPAS_OK != wirepas_wait_response ( &wirepas, WIREPAS_MSAP_STACK_START_CONFIRM ) );
            Delay_1sec( );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END

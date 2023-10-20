/*!
 * @file main.c
 * @brief Wirepas Click Example.
 *
 * # Description
 * This example demonstrates the use of Wirepas click board by processing
 * the incoming data and displaying them on the USB UART in sink mode, and sending data to 
 * the sinks in router mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration, setting device mode, node,
 * net and channel addresses, and starting stack.
 *
 * ## Application Task
 * Router mode - Sending data to the sinks at the same network.
 * Sink mode - Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - err_t wirepas_get_resp ( wirepas_t *ctx )
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

#define PROCESS_BUFFER_SIZE 200
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
wirepas_sink_data sink_1;
wirepas_sink_data sink_2;

/**
 * @brief Wirepas get response function.
 * @details This function is used to get response from the device. 
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_get_resp ( wirepas_t *ctx );

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
   
    uint8_t tmp_data[ 1 ] = { 0x00 };
    
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
   
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
    
    Delay_ms( 1000 );
    log_printf( &logger, " Wirepas stack stop request: \n" );
    wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_STOP_REQUEST, frame_id, 0x00, tmp_data );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Wirepas factory reset request: \n" );
    wirepas_send_command( &wirepas, WIREPAS_CSAP_FACTORY_RESET_REQUEST, frame_id, strlen( WIREPAS_FACTORY_RESET_CODE ), WIREPAS_FACTORY_RESET_CODE );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
    
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, NULL, NULL );
    frame_id++;
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set node address: \n" );
    wirepas_set_node_address( &wirepas, frame_id, NODE_ADDRESS );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set net address: \n" );
    wirepas_set_net_address( &wirepas, frame_id, NET_ADDRESS );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set channel address: \n" );
    uint8_t channel_net = CHANNEL_ADDRESS;
    wirepas_write_csap_attribute( &wirepas, frame_id, WIREPAS_CSAP_ATTRIBUTE_NETWORK_CHANNEL, 1, &channel_net );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Set role: \n" );
    uint8_t role;
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    role = WIREPAS_ROUTER_NODE_MODE;
#else
    role = WIREPAS_SINK_NODE_MODE;
#endif
    wirepas_write_csap_attribute( &wirepas, frame_id, WIREPAS_CSAP_ATTRIBUTE_NODE_ROLE, 1, &role );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    Delay_ms( 1000 );
    log_printf( &logger, " Wirepas Stack start request: \n" ); 
    tmp_data[ 0 ] = 0x01;
    wirepas_send_command( &wirepas, WIREPAS_MSAP_STACK_START_REQUEST, frame_id, 0x01, tmp_data );
    frame_id++;
    wirepas_get_resp( &wirepas );
    
    uint8_t data_buf[ WIREPAS_RX_DRV_BUFFER_SIZE ] = { 0 };
    
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    Delay_ms( 1000 );
    wirepas_poll_indication( &wirepas, frame_id, data_buf, NULL );
    frame_id++;
        
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
#else
    uint8_t data_rd = 0;
    while ( 0 == data_rd )
    {
        wirepas_poll_indication( &wirepas, frame_id, data_buf, &data_rd );
        frame_id++;
        Delay_ms( 1000 );
    }
#endif
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( ROUTER_NODE_ADDRESS == NODE_ADDRESS )
    log_printf( &logger, " Sending data to the first Sink node: \n" );
    wirepas_send_data ( &wirepas, frame_id, sink_1, 0x01, strlen( TX_DATA ), TX_DATA );
    frame_id++;
    wirepas_get_resp( &wirepas );
    Delay_ms( 5000 );
    
    #if defined MULTI_SINK_MODE
        log_printf( &logger, " Sending data to the second Sink node: \n" );
        wirepas_send_data ( &wirepas, frame_id, sink_2, 0x01, strlen( TX_DATA ), TX_DATA );
        frame_id++;
        wirepas_get_resp( &wirepas );
        Delay_ms( 5000 );
    #endif
#else
    uint8_t data_buf[ WIREPAS_RX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t data_rdy = 0;
    err_t error = wirepas_poll_indication( &wirepas, frame_id, data_buf, &data_rdy );
    frame_id++;
    if ( 1 == data_rdy )
    {
        log_printf( &logger, "%s \r\n", data_buf );
    }
    Delay_ms( 2000 );
#endif
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

err_t wirepas_get_resp ( wirepas_t *ctx )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    
    Delay_ms( 1000 );
    rx_size = wirepas_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 )
    {       
        if ( 0 == rx_buf[ 4 ] )
        {
            log_printf( &logger, " Response OK \n" );
            return WIREPAS_OK;
        }
        else 
        {
            log_printf( &logger, " Response ERROR %d\n", rx_buf[ 4 ] );
            return WIREPAS_ERROR;
        }
        
    }
    
}

// ------------------------------------------------------------------------ END

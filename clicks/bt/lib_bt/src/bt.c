/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file bt.c
 * @brief BT Click Driver.
 */

#include "bt.h"

void bt_cfg_setup ( bt_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->cts  = HAL_PIN_NC;
    cfg->bt0  = HAL_PIN_NC;
    cfg->rts  = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t bt_init ( bt_t *ctx, bt_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->an, cfg->an );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->bt0, cfg->bt0 );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

err_t bt_default_cfg ( bt_t *ctx ) 
{
    // Click default configuration
    bt_set_bt0_pin ( ctx, 0 );
    bt_set_cts_pin ( ctx, 0 );
    bt_set_rst_pin ( ctx, 0 );
    Delay_1sec( );
    bt_set_rst_pin ( ctx, 1 );
    Delay_1sec( );
    Delay_1sec( );
    
    err_t error_flag = bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                      BT_HARDWARE_BUTTON1_PIN_INDEX, 
                                                      BT_HARDWARE_CONFIG_GPIO_INPUT, 
                                                      BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    error_flag |= bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                 BT_HARDWARE_BUTTON2_PIN_INDEX, 
                                                 BT_HARDWARE_CONFIG_GPIO_INPUT, 
                                                 BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    error_flag |= bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                 BT_HARDWARE_BUTTON3_PIN_INDEX, 
                                                 BT_HARDWARE_CONFIG_GPIO_INPUT, 
                                                 BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    error_flag |= bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                 BT_HARDWARE_BUTTON4_PIN_INDEX, 
                                                 BT_HARDWARE_CONFIG_GPIO_INPUT, 
                                                 BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    error_flag |= bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                 BT_HARDWARE_BUTTON5_PIN_INDEX, 
                                                 BT_HARDWARE_CONFIG_GPIO_INPUT, 
                                                 BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    error_flag |= bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                 BT_HARDWARE_LED1_PIN_INDEX, 
                                                 BT_HARDWARE_CONFIG_GPIO_OUTPUT, 
                                                 BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    error_flag |= bt_hardware_config_gpio ( ctx, BT_HARDWARE_CONFIG_PORT_B, 
                                                 BT_HARDWARE_LED2_PIN_INDEX, 
                                                 BT_HARDWARE_CONFIG_GPIO_OUTPUT, 
                                                 BT_HARDWARE_CONFIG_GPIO_PULLDOWN );
    
    return error_flag;
}

err_t bt_generic_write ( bt_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t bt_generic_read ( bt_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void bt_set_an_pin ( bt_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->an, state );
}

void bt_set_rst_pin ( bt_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void bt_set_cts_pin ( bt_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

void bt_set_bt0_pin ( bt_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->bt0, state );
}

uint8_t bt_get_rts_pin ( bt_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

err_t bt_send_package ( bt_t *ctx, bt_package_t pkg ) 
{
    uint8_t tx_buf[ BT_MAX_PAYLOAD_LEN + 4 ] = { 0 };
    
    // Clear RX buffer
    uart_read( &ctx->uart, tx_buf, BT_MAX_PAYLOAD_LEN );
    
    tx_buf[ 0 ] = pkg.msg_type;
    tx_buf[ 1 ] = pkg.payload_len;
    tx_buf[ 2 ] = pkg.msg_class;
    tx_buf[ 3 ] = pkg.msg_id;
    
    for ( uint8_t cnt = 0; cnt < pkg.payload_len; cnt++ )
    {
        tx_buf[ cnt + 4 ] = pkg.payload[ cnt ];
    }
    
    return uart_write( &ctx->uart, tx_buf, pkg.payload_len + 4 ); 
}

err_t bt_read_package ( bt_t *ctx, bt_package_t *pkg )
{
    pkg->msg_type = 0;
    
    while ( ( pkg->msg_type != BT_MSG_TYPE_COMMAND ) && 
            ( pkg->msg_type != BT_MSG_TYPE_EVENT ) )
    {
        uart_read( &ctx->uart, &pkg->msg_type, 1 );
        Delay_1ms( );
    }
    
    Delay_10ms( );
    
    if ( uart_read( &ctx->uart, &pkg->payload_len, 1 ) != 1 )
    {
        return BT_ERROR;
    }
    
    if ( uart_read( &ctx->uart, &pkg->msg_class, 1 ) != 1 )
    {
        return BT_ERROR;
    }
    
    if ( uart_read( &ctx->uart, &pkg->msg_id, 1 ) != 1 )
    {
        return BT_ERROR;
    }
    
    if ( uart_read( &ctx->uart, pkg->payload, pkg->payload_len ) != pkg->payload_len )
    {
        return BT_ERROR;
    }
    
    return BT_OK;
}

err_t bt_set_local_name ( bt_t *ctx, char *name )
{
    if ( strlen( name ) > 30 || strlen( name ) < 1 )
    {
        return BT_ERROR;
    }
    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = strlen( name ) + 1;
    pkg.msg_class = BT_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT_MSG_ID_SYSTEM_SET_LOCAL_NAME;
    pkg.payload[ 0 ] = strlen( name );
    strcpy( &pkg.payload[ 1 ], name );
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_set_bondable_mode ( bt_t *ctx, uint8_t mode )
{
    if ( mode > BT_SM_SET_BONDABLE_ALLOWED )
    {
        return BT_ERROR;
    }
    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 1;
    pkg.msg_class = BT_MSG_CLASS_SM;
    pkg.msg_id = BT_MSG_ID_SM_SET_BONDABLE_MODE;
    pkg.payload[ 0 ] = mode;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_delete_bondings ( bt_t *ctx )
{    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 0;
    pkg.msg_class = BT_MSG_CLASS_SM;
    pkg.msg_id = BT_MSG_ID_SM_DELETE_BONDINGS;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_set_class_of_device ( bt_t *ctx, uint32_t cod )
{    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 4;
    pkg.msg_class = BT_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT_MSG_ID_SYSTEM_SET_CLASS_OF_DEV;
    pkg.payload[ 3 ] = ( uint8_t ) ( ( cod >> 24 ) & 0xFF );
    pkg.payload[ 2 ] = ( uint8_t ) ( ( cod >> 16 ) & 0xFF );
    pkg.payload[ 1 ] = ( uint8_t ) ( ( cod >> 8 ) & 0xFF );
    pkg.payload[ 0 ] = ( uint8_t ) ( cod & 0xFF );
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_set_gap_mode ( bt_t *ctx, uint8_t connectable, uint8_t discoverable, uint8_t limited )
{    
    bt_package_t pkg;
    
    if ( ( connectable > BT_GAP_MODE_CONNECTABLE ) || 
         ( discoverable > BT_GAP_MODE_DISCOVERABLE ) || 
         ( limited > BT_GAP_MODE_NOT_LIMITED ) )
    {
        return BT_ERROR;
    }
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 3;
    pkg.msg_class = BT_MSG_CLASS_GAP;
    pkg.msg_id = BT_MSG_ID_GAP_SET_MODE;
    pkg.payload[ 0 ] = connectable;
    pkg.payload[ 1 ] = discoverable;
    pkg.payload[ 2 ] = limited;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_rfcomm_start_server ( bt_t *ctx, uint8_t sdp_id, uint8_t stream_dest )
{    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 2;
    pkg.msg_class = BT_MSG_CLASS_RFCOMM;
    pkg.msg_id = BT_MSG_ID_RFCOMM_START_SERVER;
    pkg.payload[ 0 ] = sdp_id;
    pkg.payload[ 1 ] = stream_dest;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_rfcomm_stop_server ( bt_t *ctx, uint8_t sdp_id )
{    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 1;
    pkg.msg_class = BT_MSG_CLASS_RFCOMM;
    pkg.msg_id = BT_MSG_ID_RFCOMM_STOP_SERVER;
    pkg.payload[ 0 ] = sdp_id;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_factory_reset ( bt_t *ctx )
{    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 0;
    pkg.msg_class = BT_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT_MSG_ID_SYSTEM_FACTORY_RESET;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_system_reset ( bt_t *ctx, uint8_t mode )
{    
    if ( mode > BT_SYSTEM_RESET_BOOT_TO_DFU )
    {
        return BT_ERROR;
    }
    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 1;
    pkg.msg_class = BT_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT_MSG_ID_SYSTEM_RESET;
    pkg.payload[ 0 ] = mode;
    
    bt_send_package ( ctx, pkg );
    
    return BT_OK;
}

err_t bt_hardware_config_gpio ( bt_t *ctx, uint8_t port, uint16_t pin_index, uint8_t mode, uint8_t pullup )
{    
    if ( ( port > BT_HARDWARE_CONFIG_PORT_B ) ||
         ( mode > BT_HARDWARE_CONFIG_GPIO_ANALOG ) || 
         ( pullup > BT_HARDWARE_CONFIG_GPIO_PULLDOWN ) )
    {
        return BT_ERROR;
    }
    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 5;
    pkg.msg_class = BT_MSG_CLASS_HARDWARE;
    pkg.msg_id = BT_MSG_ID_HARDWARE_CONFIG_GPIO;
    pkg.payload[ 0 ] = port;
    pkg.payload[ 1 ] = ( uint8_t ) ( pin_index & 0xFF );
    pkg.payload[ 2 ] = ( uint8_t ) ( ( pin_index >> 8 ) & 0xFF );
    pkg.payload[ 3 ] = mode;
    pkg.payload[ 4 ] = pullup;
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_hardware_read_gpio ( bt_t *ctx, uint8_t port, uint16_t mask, uint16_t *port_data )
{    
    if ( port > BT_HARDWARE_CONFIG_PORT_B )
    {
        return BT_ERROR;
    }
    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 3;
    pkg.msg_class = BT_MSG_CLASS_HARDWARE;
    pkg.msg_id = BT_MSG_ID_HARDWARE_READ_GPIO;
    pkg.payload[ 0 ] = port;
    pkg.payload[ 1 ] = ( uint8_t ) ( mask & 0xFF );
    pkg.payload[ 2 ] = ( uint8_t ) ( ( mask >> 8 ) & 0xFF );
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        *port_data = ( ( uint16_t ) pkg.payload[ 3 ] << 8 ) | pkg.payload[ 2 ];
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_hardware_write_gpio ( bt_t *ctx, uint8_t port, uint16_t mask, uint16_t port_data )
{    
    if ( port > BT_HARDWARE_CONFIG_PORT_B )
    {
        return BT_ERROR;
    }
    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = 5;
    pkg.msg_class = BT_MSG_CLASS_HARDWARE;
    pkg.msg_id = BT_MSG_ID_HARDWARE_WRITE_GPIO;
    pkg.payload[ 0 ] = port;
    pkg.payload[ 1 ] = ( uint8_t ) ( mask & 0xFF );
    pkg.payload[ 2 ] = ( uint8_t ) ( ( mask >> 8 ) & 0xFF );
    pkg.payload[ 3 ] = ( uint8_t ) ( port_data & 0xFF );
    pkg.payload[ 4 ] = ( uint8_t ) ( ( port_data >> 8 ) & 0xFF );
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        return BT_OK;
    }
    
    return BT_ERROR;
}

err_t bt_endpoint_send_data ( bt_t *ctx, uint8_t *endpoint, char *msg )
{    
    bt_package_t pkg;
    
    pkg.msg_type = BT_MSG_TYPE_COMMAND;
    pkg.payload_len = strlen( msg ) + 2;
    pkg.msg_class = BT_MSG_CLASS_ENDPOINT;
    pkg.msg_id = BT_MSG_ID_ENDPOINT_SEND_DATA;
    pkg.payload[ 0 ] = *endpoint;
    pkg.payload[ 1 ] = strlen( msg );
    strcpy( &pkg.payload[ 2 ], msg );
    
    bt_send_package ( ctx, pkg );
    
    if ( BT_ERROR == bt_read_package ( ctx, &pkg ) )
    {
        return BT_ERROR;
    }
    
    if ( ( pkg.payload[ 0 ] == 0 ) && ( pkg.payload[ 1 ] == 0 ) )
    {
        *endpoint = pkg.payload[ 2 ];
        return BT_OK;
    }
    
    return BT_ERROR;
}

// ------------------------------------------------------------------------- END

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
 * @file wirepas.c
 * @brief Wirepas Click Driver.
 */

#include "wirepas.h"
#include "string.h"

/**
 * @brief Wirepas CRC lut table code.
 * @details CRC lut table of Wirepas Click driver.
 */
static const uint16_t crc_ccitt_lut[] =
{
    0X0000, 0X1021, 0X2042, 0X3063, 0X4084, 0X50A5, 0X60C6, 0X70E7, 
    0X8108, 0X9129, 0XA14A, 0XB16B, 0XC18C, 0XD1AD, 0XE1CE, 0XF1EF, 
    0X1231, 0X0210, 0X3273, 0X2252, 0X52B5, 0X4294, 0X72F7, 0X62D6, 
    0X9339, 0X8318, 0XB37B, 0XA35A, 0XD3BD, 0XC39C, 0XF3FF, 0XE3DE, 
    0X2462, 0X3443, 0X0420, 0X1401, 0X64E6, 0X74C7, 0X44A4, 0X5485, 
    0XA56A, 0XB54B, 0X8528, 0X9509, 0XE5EE, 0XF5CF, 0XC5AC, 0XD58D, 
    0X3653, 0X2672, 0X1611, 0X0630, 0X76D7, 0X66F6, 0X5695, 0X46B4, 
    0XB75B, 0XA77A, 0X9719, 0X8738, 0XF7DF, 0XE7FE, 0XD79D, 0XC7BC, 
    0X48C4, 0X58E5, 0X6886, 0X78A7, 0X0840, 0X1861, 0X2802, 0X3823, 
    0XC9CC, 0XD9ED, 0XE98E, 0XF9AF, 0X8948, 0X9969, 0XA90A, 0XB92B, 
    0X5AF5, 0X4AD4, 0X7AB7, 0X6A96, 0X1A71, 0X0A50, 0X3A33, 0X2A12, 
    0XDBFD, 0XCBDC, 0XFBBF, 0XEB9E, 0X9B79, 0X8B58, 0XBB3B, 0XAB1A, 
    0X6CA6, 0X7C87, 0X4CE4, 0X5CC5, 0X2C22, 0X3C03, 0X0C60, 0X1C41, 
    0XEDAE, 0XFD8F, 0XCDEC, 0XDDCD, 0XAD2A, 0XBD0B, 0X8D68, 0X9D49, 
    0X7E97, 0X6EB6, 0X5ED5, 0X4EF4, 0X3E13, 0X2E32, 0X1E51, 0X0E70, 
    0XFF9F, 0XEFBE, 0XDFDD, 0XCFFC, 0XBF1B, 0XAF3A, 0X9F59, 0X8F78, 
    0X9188, 0X81A9, 0XB1CA, 0XA1EB, 0XD10C, 0XC12D, 0XF14E, 0XE16F, 
    0X1080, 0X00A1, 0X30C2, 0X20E3, 0X5004, 0X4025, 0X7046, 0X6067, 
    0X83B9, 0X9398, 0XA3FB, 0XB3DA, 0XC33D, 0XD31C, 0XE37F, 0XF35E, 
    0X02B1, 0X1290, 0X22F3, 0X32D2, 0X4235, 0X5214, 0X6277, 0X7256, 
    0XB5EA, 0XA5CB, 0X95A8, 0X8589, 0XF56E, 0XE54F, 0XD52C, 0XC50D, 
    0X34E2, 0X24C3, 0X14A0, 0X0481, 0X7466, 0X6447, 0X5424, 0X4405, 
    0XA7DB, 0XB7FA, 0X8799, 0X97B8, 0XE75F, 0XF77E, 0XC71D, 0XD73C, 
    0X26D3, 0X36F2, 0X0691, 0X16B0, 0X6657, 0X7676, 0X4615, 0X5634, 
    0XD94C, 0XC96D, 0XF90E, 0XE92F, 0X99C8, 0X89E9, 0XB98A, 0XA9AB, 
    0X5844, 0X4865, 0X7806, 0X6827, 0X18C0, 0X08E1, 0X3882, 0X28A3, 
    0XCB7D, 0XDB5C, 0XEB3F, 0XFB1E, 0X8BF9, 0X9BD8, 0XABBB, 0XBB9A, 
    0X4A75, 0X5A54, 0X6A37, 0X7A16, 0X0AF1, 0X1AD0, 0X2AB3, 0X3A92, 
    0XFD2E, 0XED0F, 0XDD6C, 0XCD4D, 0XBDAA, 0XAD8B, 0X9DE8, 0X8DC9, 
    0X7C26, 0X6C07, 0X5C64, 0X4C45, 0X3CA2, 0X2C83, 0X1CE0, 0X0CC1, 
    0XEF1F, 0XFF3E, 0XCF5D, 0XDF7C, 0XAF9B, 0XBFBA, 0X8FD9, 0X9FF8, 
    0X6E17, 0X7E36, 0X4E55, 0X5E74, 0X2E93, 0X3EB2, 0X0ED1, 0X1EF0 
};

/** 
 * @brief Calculation for CRC 16 function.
 * @details This function calculates CRC 16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Initialization 0xFF
 * @param[in] buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
uint16_t crc_from_buffer ( uint8_t *buf, uint32_t len );

void wirepas_cfg_setup ( wirepas_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->din = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wirepas_init ( wirepas_t *ctx, wirepas_cfg_t *cfg ) 
{
    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    
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

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Input pins
    digital_in_init( &ctx->din, cfg->din );
    
    return UART_SUCCESS;
}

void wirepas_default_cfg ( wirepas_t *ctx ) 
{
    wirepas_hw_reset( ctx );
}

err_t wirepas_generic_write ( wirepas_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t wirepas_generic_read ( wirepas_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

uint8_t wirepas_get_din_state ( wirepas_t *ctx )
{
    return digital_in_read( &ctx->din );
}

void wirepas_set_rst ( wirepas_t *ctx, uint8_t pin_state )
{
    if ( WIREPAS_PIN_MODE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void wirepas_hw_reset ( wirepas_t *ctx )
{
    wirepas_set_rst( ctx, WIREPAS_PIN_MODE_LOW );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    wirepas_set_rst( ctx, WIREPAS_PIN_MODE_HIGH );
    Delay_100ms( );
}

err_t wirepas_send_command ( wirepas_t *ctx, uint8_t primitive_id, uint8_t frame_id, 
                             uint8_t payload_length, uint8_t *payload )
{
    err_t error_flag = WIREPAS_OK;
    uint16_t crc_data = 0;
    uint8_t data_buf[ 265 ] = { 0 };
   
    data_buf[ 0 ] = WIREPAS_ENDCODE_OCTET;
    data_buf[ 1 ] = WIREPAS_ENDCODE_OCTET;
    data_buf[ 2 ] = WIREPAS_ENDCODE_OCTET;
    data_buf[ 3 ] = primitive_id;
    data_buf[ 4 ] = frame_id;
    data_buf[ 5 ] = payload_length;
    
    if ( 0 != payload_length )
    {
        for ( uint8_t n_cnt = 0; n_cnt < payload_length; n_cnt++ )
        {
            data_buf[ n_cnt + 6 ] = payload[ n_cnt ];
        }
    }
    
    crc_data = crc_from_buffer( &data_buf[ 3 ], payload_length + 3 );
    
    data_buf[ payload_length + 6 ] = ( uint8_t ) crc_data; 
    data_buf[ payload_length + 7 ] = ( uint8_t ) ( crc_data >> 8 ); 
    data_buf[ payload_length + 8 ] = WIREPAS_ENDCODE_OCTET; 
    
    error_flag = wirepas_generic_write( ctx, data_buf, ( payload_length + 9 ) );
    
    return error_flag;
}

err_t wirepas_write_csap_attribute ( wirepas_t *ctx, uint8_t frame_id, uint16_t attribute_id, 
                                     uint8_t attribute_len, uint8_t *attribute_val )
{
    err_t error_flag = WIREPAS_OK;
    uint8_t data_buf[ 19 ] = { 0 };
    uint8_t len_cnt = 3;
    
    data_buf[ 0 ] = ( uint8_t ) attribute_id;
    data_buf[ 1 ] = ( uint8_t ) ( attribute_id >> 8 );
    data_buf[ 2 ] = attribute_len;
    
    for( uint8_t n_cnt = 0; n_cnt < attribute_len; n_cnt++ )
    {
        data_buf[ n_cnt + 3 ] = attribute_val[ n_cnt ];
        len_cnt++;
    }
    
    error_flag = wirepas_send_command( ctx, WIREPAS_CSAP_ATTRIBUTE_WRITE_REQUEST, frame_id, 
                                       len_cnt, data_buf );
    
    return error_flag;
}

err_t wirepas_read_csap_attribute ( wirepas_t *ctx, uint8_t frame_id, uint16_t attribute_id, 
                                    uint8_t *attribute_len, uint8_t *attribute_val )
{
    err_t error_flag = WIREPAS_OK;
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t data_buf[ WIREPAS_RX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t len_cnt = 0;
    uint8_t pay_len = 0;
    uint16_t att_id = 0;
    uint16_t crc_val = 0;
    uint16_t crc_data = 0;
    
    tx_buf[ 0 ] = ( uint8_t ) attribute_id;
    tx_buf[ 1 ] = ( uint8_t ) ( attribute_id >> 8 );
    
    error_flag |= wirepas_send_command( ctx, WIREPAS_CSAP_ATTRIBUTE_READ_REQUEST, frame_id, 0x02, tx_buf );
    Delay_10ms( );
    len_cnt = wirepas_generic_read( ctx, data_buf, WIREPAS_RX_DRV_BUFFER_SIZE );
    pay_len = data_buf[ 3 ];

    crc_val = crc_from_buffer( &data_buf[ 1 ], len_cnt - 4 );
    crc_data = ( uint16_t ) data_buf[ len_cnt - 2 ] << 8 | data_buf[ len_cnt - 3 ];
    
    if ( crc_val != crc_data )
    {
         return WIREPAS_ERROR;
    }

    att_id = ( uint16_t ) data_buf[ 4 ] << 8 | data_buf[ 5 ];
    
    if ( att_id != attribute_id )
    {
         return WIREPAS_ERROR;
    }
    
    *attribute_len = data_buf[ 7 ];
    
     for ( uint8_t n_cnt = 0; n_cnt < data_buf[ 7 ]; n_cnt++ )
    {
        attribute_val[ n_cnt ] = data_buf[ n_cnt + 8 ];
    }
    
    return error_flag;
}

err_t wirepas_set_node_address ( wirepas_t *ctx, uint8_t frame_id, uint32_t address )
{
    err_t error_flag = WIREPAS_OK;
    uint8_t address_buf[ 4 ] = { 0 };
    
    address_buf[ 0 ] = ( uint8_t ) address;
    address_buf[ 1 ] = ( uint8_t ) ( address >> 8 );
    address_buf[ 2 ] = ( uint8_t ) ( address >> 16 );
    address_buf[ 3 ] = ( uint8_t ) ( address >> 24 );
    
    error_flag = wirepas_write_csap_attribute( ctx, frame_id, WIREPAS_CSAP_ATTRIBUTE_NODE_ADDRESS, 
                                               4, address_buf );
    
    return error_flag;
}

err_t wirepas_set_net_address ( wirepas_t *ctx, uint8_t frame_id, uint32_t net_address )
{
    err_t error_flag = WIREPAS_OK;
    uint8_t net_address_buf[ 4 ] = { 0 };
    
    net_address_buf[ 0 ] = ( uint8_t ) net_address;
    net_address_buf[ 1 ] = ( uint8_t ) ( net_address >> 8 );
    net_address_buf[ 2 ] = ( uint8_t ) ( net_address >> 16 );
    
    error_flag = wirepas_write_csap_attribute( ctx, frame_id, WIREPAS_CSAP_ATTRIBUTE_NETWORK_ADDRESS, 
                                               3, net_address_buf );
    
    return error_flag;
}

err_t wirepas_poll_indication ( wirepas_t *ctx, uint8_t frame_id, uint8_t *rx_data, uint8_t *data_rdy )
{
    err_t error_flag = 0;
    uint8_t len_cnt = 0;
    uint8_t tx_buf[ WIREPAS_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t data_buf[ WIREPAS_RX_DRV_BUFFER_SIZE ] = { 0 };
    
    error_flag = wirepas_send_command( ctx, WIREPAS_MSAP_INDICATION_POLL_REQUEST, frame_id, 0, tx_buf );
    Delay_10ms( );
    len_cnt = wirepas_generic_read( ctx, data_buf, WIREPAS_RX_DRV_BUFFER_SIZE );
    if ( len_cnt > 0 )
    {
        if ( WIREPAS_MSAP_INDICATION_POLL_CONFIRM == data_buf[ 1 ] )
        {
            if ( ( data_buf[ 4 ] == 0x01 ) && ( WIREPAS_MSAP_STACK_STATE_INDICATION == data_buf[ 9 ] ) )
            {
                tx_buf[ 0 ] = 0;

                error_flag = wirepas_send_command ( ctx, WIREPAS_MSAP_STACK_STATE_RESPONSE, 
                                                    data_buf[ 10 ], 1, tx_buf );
            }
           
           else if ( ( data_buf[ 4 ] == 0x01 ) &&  ( WIREPAS_DSAP_DATA_RX_INDICATION == data_buf[ 9 ] ) )
            {
                tx_buf[ 0 ] = 0;
                for ( uint8_t n_cnt = 0; n_cnt < data_buf[ 28 ]; n_cnt++ )
                {
                    rx_data[ n_cnt ] = data_buf[ 29 + n_cnt ];
                }
                *data_rdy = 1;
                error_flag = wirepas_send_command ( ctx, WIREPAS_DSAP_DATA_RX_RESPONSE, 
                                                    data_buf[ 10 ], 1, tx_buf );
                
                return WIREPAS_DATA_RDY;
            }
        }
    }
    else
    {
        return WIREPAS_ERROR;
    }
    
    return len_cnt;
}

err_t wirepas_send_data ( wirepas_t *ctx, uint8_t frame_id, wirepas_sink_data sink_data, uint8_t tx_op, 
                          uint8_t apdu_length, uint8_t *apdu )
{
    err_t error_flag = WIREPAS_OK;
    uint8_t tx_buf[ 113 ] = { 0 };
    tx_buf[ 0 ] = ( uint8_t ) sink_data.pduid;
    tx_buf[ 1 ] = ( uint8_t ) ( sink_data.pduid >> 8 );
    tx_buf[ 2 ] = sink_data.source_endpoint;
    tx_buf[ 3 ] = ( uint8_t ) sink_data.destination_addr;
    tx_buf[ 4 ] = ( uint8_t ) ( sink_data.destination_addr >> 8 );
    tx_buf[ 5 ] = ( uint8_t ) ( sink_data.destination_addr >> 16 );
    tx_buf[ 6 ] = ( uint8_t ) ( sink_data.destination_addr >> 24 );
    tx_buf[ 7 ] = sink_data.destination_endpoint;
    tx_buf[ 8 ] = 0x00;
    tx_buf[ 9 ] = tx_op;
    tx_buf[ 10 ] = apdu_length;
    
    for ( uint8_t n_cnt = 0; n_cnt < apdu_length; n_cnt++ )
    {
        tx_buf[ 11 + n_cnt ] = apdu[ n_cnt ];
    }
    
    error_flag = wirepas_send_command( ctx, WIREPAS_DSAP_DATA_TX_REQUEST, frame_id, 
                                       (apdu_length + 11), tx_buf );
    
    return error_flag;
}

uint16_t crc_from_buffer ( uint8_t *buf, uint32_t len )
{
    uint16_t crc = 0xFFFF;
    uint8_t index;
    
    for ( uint32_t i = 0; i < len; i++ )
    {
        index = buf[ i ] ^ ( crc >> 8 );
        crc = crc_ccitt_lut[ index ] ^ ( crc << 8 );
    }
    return crc;
}

// ------------------------------------------------------------------------- END

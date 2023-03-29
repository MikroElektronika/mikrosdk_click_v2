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
 * @file radar.c
 * @brief Radar Click Driver.
 */

#include "radar.h"
#include "conversions.h"

/** 
 * @brief CCITT-FALSE calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x1021 ( x16 + x12 + x5 + x0 )
 * @li @c  Initialization 0xFFFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @li @c  Example { D9, 0D, 00, 00 }- 0x9DE5
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t radar_calculate_crc16_ccitt ( uint8_t *data_buf, uint16_t len );

void radar_cfg_setup ( radar_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->gp0 = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t radar_init ( radar_t *ctx, radar_cfg_t *cfg ) 
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

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->gp2, cfg->gp2 );
    digital_in_init( &ctx->gp1, cfg->gp1 );
    digital_in_init( &ctx->gp0, cfg->gp0 );

    return UART_SUCCESS;
}

err_t radar_default_cfg ( radar_t *ctx ) 
{
    err_t error_flag = RADAR_OK;
    
    radar_disable_device ( ctx );
    Delay_100ms ( );
    
    radar_enable_device ( ctx );
    Delay_100ms ( );
    
    error_flag |= radar_reset_config ( ctx );
    Delay_1sec ( );
    
    error_flag |= radar_set_detection_range ( ctx, RADAR_DEFAULT_MIN_RANGE, RADAR_DEFAULT_MAX_RANGE );
    
    return error_flag;
}

err_t radar_generic_write ( radar_t *ctx, uint8_t *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t radar_generic_read ( radar_t *ctx, uint8_t *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void radar_enable_device ( radar_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void radar_disable_device ( radar_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

uint8_t radar_get_gpio2_pin ( radar_t *ctx )
{
    return digital_in_read ( &ctx->gp2 );
}

uint8_t radar_get_gpio1_pin ( radar_t *ctx )
{
    return digital_in_read ( &ctx->gp1 );
}

uint8_t radar_get_gpio0_pin ( radar_t *ctx )
{
    return digital_in_read ( &ctx->gp0 );
}

err_t radar_set_command ( radar_t *ctx, uint8_t cmd_id, uint8_t *payload, uint8_t payload_size ) 
{
    uint8_t data_buf[ 261 ] = { 0 };
    data_buf[ 0 ] = RADAR_CMD_HEADER;
    data_buf[ 1 ] = cmd_id;
    data_buf[ 2 ] = payload_size;
    data_buf[ 3 ] = 0; // payload size is limited to one byte
    if ( payload && ( payload_size > 0 ) )
    {
        memcpy ( &data_buf[ 4 ], payload, payload_size );
    }
    uint16_t crc = radar_calculate_crc16_ccitt ( data_buf, payload_size + 4 );
    data_buf[ payload_size + 4 ] = ( uint8_t ) ( crc & 0xFF );
    data_buf[ payload_size + 5 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    uart_clear ( &ctx->uart );
    radar_generic_write( ctx, data_buf, payload_size + 6 );
    uint8_t evt_id, evt_payload[ 16 ];
    uint16_t timeout_cnt = 0;
    if ( ( RADAR_ERROR == radar_get_event ( ctx, &evt_id, evt_payload, 0 ) ) ||
         ( RADAR_CMD_ID_ACK != evt_id ) )
    {
        return RADAR_ERROR;
    }
    if ( ( cmd_id == evt_payload[ 0 ] ) && ( RADAR_SET_CMD_SUCCESS == evt_payload[ 1 ] ) )
    {
        return RADAR_OK;
    }
    return RADAR_ERROR;
}

err_t radar_get_command ( radar_t *ctx, uint8_t cmd_id, uint8_t *payload, uint8_t *payload_size ) 
{
    uint8_t data_buf[ 261 ] = { 0 };
    data_buf[ 0 ] = RADAR_CMD_HEADER;
    data_buf[ 1 ] = cmd_id;
    data_buf[ 2 ] = 0;
    data_buf[ 3 ] = 0;
    uint16_t crc = radar_calculate_crc16_ccitt ( data_buf, 4 );
    data_buf[ 4 ] = ( uint8_t ) ( crc & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    uart_clear ( &ctx->uart );
    radar_generic_write( ctx, data_buf, 6 );
    uint16_t timeout_cnt = 0;
    while ( ( radar_generic_read( ctx, data_buf, 1 ) <= 0 ) || ( RADAR_CMD_HEADER != data_buf[ 0 ] ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt > RADAR_TIMEOUT )
        {
            return RADAR_ERROR;
        }
    }
    Delay_10ms( );
    if ( 3 != radar_generic_read( ctx, &data_buf[ 1 ], 3 ) )
    {
        return RADAR_ERROR;
    }
    if ( cmd_id != data_buf[ 1 ] )
    {
        return RADAR_ERROR;
    }
    if ( ( data_buf[ 2 ] + 2 ) != radar_generic_read( ctx, &data_buf[ 4 ], data_buf[ 2 ] + 2 ) )
    {
        return RADAR_ERROR;
    }
    crc = ( ( uint16_t ) data_buf[ data_buf[ 2 ] + 5 ] << 8 ) | data_buf[ data_buf[ 2 ] + 4 ];
    if ( crc != radar_calculate_crc16_ccitt ( data_buf, data_buf[ 2 ] + 4 ) )
    {
        return RADAR_ERROR;
    }
    if ( payload )
    {
        memcpy ( payload, &data_buf[ 4 ], data_buf[ 2 ] );
    }
    if ( payload_size )
    {
        *payload_size = data_buf[ 2 ];
    }
    return RADAR_OK;
}

err_t radar_get_event ( radar_t *ctx, uint8_t *evt_id, uint8_t *payload, uint8_t *payload_size ) 
{
    uint8_t data_buf[ 22 ] = { 0 };
    uint16_t timeout_cnt = 0;
    for ( ; ; )
    {
        if ( ( radar_generic_read( ctx, data_buf, 1 ) > 0 ) && ( RADAR_CMD_HEADER == data_buf[ 0 ] ) )
        {
            Delay_10ms( );
            if ( ( 3 == radar_generic_read( ctx, &data_buf[ 1 ], 3 ) ) && 
                 ( ( RADAR_CMD_ID_DETECT_IN_EVT == data_buf[ 1 ] ) || 
                   ( RADAR_CMD_ID_DETECT_OUT_EVT == data_buf[ 1 ] ) || 
                   ( RADAR_CMD_ID_ACK == data_buf[ 1 ] ) ) )
            {
                break;
            }
        }
        Delay_1ms( );
        if ( ++timeout_cnt > RADAR_TIMEOUT )
        {
            return RADAR_ERROR;
        }
    }
    if ( data_buf[ 2 ] > 16 )
    {
        return RADAR_ERROR;
    }
    if ( ( data_buf[ 2 ] + 2 ) != radar_generic_read( ctx, &data_buf[ 4 ], data_buf[ 2 ] + 2 ) )
    {
        return RADAR_ERROR;
    }
    uint16_t crc = ( ( uint16_t ) data_buf[ data_buf[ 2 ] + 5 ] << 8 ) | data_buf[ data_buf[ 2 ] + 4 ];
    if ( crc != radar_calculate_crc16_ccitt ( data_buf, data_buf[ 2 ] + 4 ) )
    {
        return RADAR_ERROR;
    }
    if ( evt_id )
    {
        *evt_id = data_buf[ 1 ];
    }
    if ( payload_size )
    {
        *payload_size = data_buf[ 2 ];
    }
    if ( payload )
    {
        memcpy ( payload, &data_buf[ 4 ], data_buf[ 2 ] );
    }
    return RADAR_OK;
}

err_t radar_get_temperature ( radar_t *ctx, float *temperature )
{
    radar_float_bytes_t temp;
    err_t error_flag = radar_get_command ( ctx, RADAR_CMD_ID_CHIP_TEMPERATURE, temp.b_data, 0 );
    radar_float_ieee_to_mchip ( &temp.f_data );
    *temperature = temp.f_data;
    return error_flag;
}

err_t radar_set_detection_range ( radar_t *ctx, float min, float max )
{
    if ( ( min < 0.0 ) || ( min > 10.0 ) || ( max < 0.2 ) || ( max > 10.0 ) || ( min > max ) )
    {
        return RADAR_ERROR;
    }
    radar_float_bytes_t range;
    range.f_data = max;
    radar_float_mchip_to_ieee ( &range.f_data );
    err_t error_flag = radar_set_command ( ctx, RADAR_CMD_ID_MAX_DETECT_RANGE, range.b_data, 4 );
    range.f_data = min;
    radar_float_mchip_to_ieee ( &range.f_data );
    error_flag |= radar_set_command ( ctx, RADAR_CMD_ID_MIN_DETECT_RANGE, range.b_data, 4 );
    return error_flag;
}

err_t radar_reset_config ( radar_t *ctx )
{
    return radar_set_command ( ctx, RADAR_CMD_ID_RESET_CONFIG, 0, 0 );
}

void radar_float_ieee_to_mchip ( float *f_data )
{
#ifdef __MIKROC_AI_FOR_PIC__
    radar_float_bytes_t tmp_data;
    tmp_data.f_data = *f_data;
    uint8_t msb = ( tmp_data.b_data[ 3 ] << 1 ) | ( tmp_data.b_data[ 2 ] >> 7 );
    tmp_data.b_data[ 2 ] = ( tmp_data.b_data[ 2 ] & 0x7F ) | ( tmp_data.b_data[ 3 ] & 0x80 );
    tmp_data.b_data[ 3 ] = msb;
    *f_data = tmp_data.f_data;
#endif
}

void radar_float_mchip_to_ieee ( float *f_data )
{
#ifdef __MIKROC_AI_FOR_PIC__
    radar_float_bytes_t tmp_data;
    tmp_data.f_data = *f_data;
    uint8_t msb = ( tmp_data.b_data[ 3 ] >> 1 ) | ( tmp_data.b_data[ 2 ] & 0x80 );
    tmp_data.b_data[ 2 ] = ( tmp_data.b_data[ 2 ] & 0x7F ) | ( tmp_data.b_data[ 3 ] << 7 );
    tmp_data.b_data[ 3 ] = msb;
    *f_data = tmp_data.f_data;
#endif
}

static uint16_t radar_calculate_crc16_ccitt ( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0xFFFF;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( ( data_buf[ cnt ] ) << 8 );
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x1021;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}

// ------------------------------------------------------------------------- END

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
 * @file xsensmti3.c
 * @brief XSENS MTi-3 Click Driver.
 */

#include "xsensmti3.h"
#include "string.h"
#include "math.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief XSENS MTi-3 convert unassigned int to float.
 * @details This function converts unassigned int to float.
 */
static float u32_to_float ( int32_t raw );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void xsensmti3_cfg_setup ( xsensmti3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->syn   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t xsensmti3_init ( xsensmti3_t *ctx, xsensmti3_cfg_t *cfg ) 
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
    digital_out_init( &ctx->syn, cfg->syn );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs,  cfg->cs );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    return UART_SUCCESS;
}

err_t xsensmti3_generic_write ( xsensmti3_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t xsensmti3_generic_read ( xsensmti3_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void xsensmti3_parser ( uint8_t *rsp_buf, uint8_t start_cnt, xsensmti3_parse_t *obj )
{
    uint8_t cnt;

    // PARSER HEADER
    obj->package_header = rsp_buf[ start_cnt ];
    obj->package_header <<= 8;
    obj->package_header |= rsp_buf[ start_cnt + 1 ];
    obj->package_header <<= 8;
    obj->package_header |= rsp_buf[ start_cnt + 2 ];
    obj->package_header <<= 8;
    obj->package_header |= rsp_buf[ start_cnt + 3 ];

    // QUATERNION DATA ID
    obj->quat_obj.data_id = rsp_buf[ start_cnt + 4 ];
    obj->quat_obj.data_id <<= 8;
    obj->quat_obj.data_id |= rsp_buf[ start_cnt + 5 ];

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        // Q DATA
        obj->quat_obj.raw_data[ cnt ] = rsp_buf[ start_cnt + 7 + ( cnt * 4 ) ];
        obj->quat_obj.raw_data[ cnt ] <<= 8;
        obj->quat_obj.raw_data[ cnt ] |= rsp_buf[ start_cnt + 8 + ( cnt * 4 ) ];
        obj->quat_obj.raw_data[ cnt ] <<= 8;
        obj->quat_obj.raw_data[ cnt ] |= rsp_buf[ start_cnt + 9 + ( cnt * 4 ) ];
        obj->quat_obj.raw_data[ cnt ] <<= 8;
        obj->quat_obj.raw_data[ cnt ] |= rsp_buf[ start_cnt + 10 + ( cnt * 4 ) ];

        obj->quat_obj.quat_data[ cnt ] = u32_to_float( obj->quat_obj.raw_data[ cnt ] );
    }

    // TIME ID
    obj->time_obj.data_id = rsp_buf[ start_cnt + 23 ];
    obj->time_obj.data_id <<= 8;
    obj->time_obj.data_id |= rsp_buf[ start_cnt + 24 ];

    // TIME DATA
    obj->time_obj.out_data = rsp_buf[ start_cnt + 25 ];
    obj->time_obj.out_data <<= 8;
    obj->time_obj.out_data |= rsp_buf[ start_cnt + 26 ];
    obj->time_obj.out_data <<= 8;
    obj->time_obj.out_data |= rsp_buf[ start_cnt + 27 ];
    obj->time_obj.out_data <<= 8;
    obj->time_obj.out_data |= rsp_buf[ start_cnt + 28 ];

    // STATUS ID
    obj->status_obj.data_id = rsp_buf[ start_cnt + 29 ];
    obj->status_obj.data_id <<= 8;
    obj->status_obj.data_id |= rsp_buf[ start_cnt + 30 ];

    // STATUS DATA
    obj->status_obj.out_data = rsp_buf[ start_cnt + 31 ];
    obj->status_obj.out_data <<= 8;
    obj->status_obj.out_data |= rsp_buf[ start_cnt + 32 ];
    obj->status_obj.out_data <<= 8;
    obj->status_obj.out_data |= rsp_buf[ start_cnt + 33 ];
    obj->status_obj.out_data <<= 8;
    obj->status_obj.out_data |= rsp_buf[ start_cnt + 34 ];

    // PACKAGE COUNTER ID
    obj->package_obj.data_id = rsp_buf[ start_cnt + 35 ];
    obj->package_obj.data_id <<= 8;
    obj->package_obj.data_id |= rsp_buf[ start_cnt + 36 ];

    // PACKAGE COUNTER data
    obj->package_obj.out_data = rsp_buf[ start_cnt + 37 ];
    obj->package_obj.out_data <<= 8;
    obj->package_obj.out_data |= rsp_buf[ start_cnt + 38 ];

    obj->crc_data = rsp_buf[ start_cnt + 39 ];
}

void xsensmti3_get_data( xsensmti3_quat_t *quat_obj, xsensmti3_data_t *data_obj )
{
    float w = quat_obj->quat_data[ 0 ];
    float x = quat_obj->quat_data[ 1 ];
    float y = quat_obj->quat_data[ 2 ];
    float z = quat_obj->quat_data[ 3 ];

    float sin_data;
    float cos_data;

    // roll (x-axis rotation)
    sin_data = 2 * ( w * x + y * z );
    cos_data = 1 - 2 * ( x * x + y * y );
    data_obj->roll = atan2( sin_data, cos_data );
    data_obj->roll *= 180.0;
    data_obj->roll /= 3.14;

    // pitch (y-axis rotation)
    sin_data = 2 * ( w * y - z * x );
    data_obj->pitch = asin( sin_data );
    data_obj->pitch *= 180.0;
    data_obj->pitch /= 3.14;

    // yaw (z-axis rotation)
    sin_data = 2 * ( w * z + x * y );
    cos_data = 1 - 2 * ( y * y + z * z );
    data_obj->yaw = atan2( sin_data, cos_data );
    data_obj->yaw *= 180.0;
    data_obj->yaw /= 3.14;
}

err_t xsensmti3_check_package( uint8_t *package_buf, uint8_t *start_package )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 100; cnt++ )
    {
        if ( ( package_buf[ cnt ] == 0xFA ) &&
             ( package_buf[ cnt + 1 ] == 0xFF ) &&
             ( package_buf[ cnt + 2 ] == 0x36 ) )
        {
            *start_package = cnt;
            return XSENSMTI3_OK;
        }
    }
    return XSENSMTI3_ERROR;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float u32_to_float ( int32_t raw )
{
    int8_t sign;
    int32_t mantissa;
    int8_t exp_data;
    float result;

    sign = raw >> 31;
    mantissa = ( raw & 0x7FFFFF ) | 0x800000;
    exp_data = ( ( raw >> 23 ) & 0xFF ) - 127 - 23;

    result = ( mantissa * pow( 2.0, exp_data ) );
    if ( sign != 0 )
    {
        result *= -1;
    }
    return result;
}

// ------------------------------------------------------------------------- END

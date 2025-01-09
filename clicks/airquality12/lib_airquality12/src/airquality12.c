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
 * @file airquality12.c
 * @brief Air Quality 12 Click Driver.
 */

#include "airquality12.h"

/**
 * @brief Air Quality 12 get checksum function.
 * @details This function calculates the checksum byte from a desired number of input bytes.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to calculate the checksum from.
 * @param[in] len : Number of bytes in data buffer.
 * @return Calculated checksum byte.
 * @note None.
 */
static uint8_t airquality12_get_checksum ( uint8_t *data_in, uint8_t len );

void airquality12_cfg_setup ( airquality12_cfg_t *cfg ) 
{
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRQUALITY12_DEVICE_ADDRESS;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->drv_sel = AIRQUALITY12_DRV_SEL_I2C;
}

void airquality12_drv_interface_sel ( airquality12_cfg_t *cfg, airquality12_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t airquality12_init ( airquality12_t *ctx, airquality12_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( AIRQUALITY12_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }
    } 
    else 
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

        // Dummy read to enable RX interrupt
        uint8_t dummy_read = 0;
        uart_read ( &ctx->uart, &dummy_read, 1 );
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->gp1, cfg->gp1 );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->gp1 );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AIRQUALITY12_OK;
}

err_t airquality12_default_cfg ( airquality12_t *ctx ) 
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_reset_device ( ctx );
    if ( AIRQUALITY12_ERROR == airquality12_check_comm ( ctx ) )
    {
        return AIRQUALITY12_ERROR;
    }
    error_flag |= airquality12_set_humidity ( ctx, AIRQUALITY12_HUMIDITY_DEFAULT );
    error_flag |= airquality12_set_op_mode ( ctx, AIRQUALITY12_OP_MODE_IAQ_2ND_GEN );
    return error_flag;
}

err_t airquality12_send_cmd ( airquality12_t *ctx, uint8_t cmd, airquality12_param_t *params )
{
    err_t error_flag = AIRQUALITY12_OK;
    uint8_t wr_buf[ 4 ] = { 0 };
    uint8_t rd_buf[ 11 ] = { 0 };
    if ( ( NULL == params ) || ( params->req_len > 2 ) || ( params->resp_len > 9 ) )
    {
        return AIRQUALITY12_ERROR;
    }
    wr_buf[ 0 ] = cmd;
    for ( uint8_t cnt = 0; cnt < params->req_len; cnt++ ) 
    {
        wr_buf[ cnt + 1 ] = params->req_buf[ cnt ];
    }
    wr_buf[ params->req_len + 1 ] = airquality12_get_checksum ( wr_buf, params->req_len + 1 );
    Delay_10ms ( );
    Delay_10ms ( );
    if ( AIRQUALITY12_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        error_flag = i2c_master_write_then_read( &ctx->i2c, wr_buf, params->req_len + 2, 
                                                 rd_buf, params->resp_len + 2 );
    }
    else
    {
        uart_clear ( &ctx->uart );
        uart_write( &ctx->uart, wr_buf, params->req_len + 2 );
        Delay_10ms ( );
        Delay_10ms ( );
        Delay_10ms ( );
        Delay_10ms ( );
        Delay_10ms ( );
        if ( ( params->resp_len + 2 ) != uart_read( &ctx->uart, rd_buf, params->resp_len + 2 ) )
        {
            error_flag = AIRQUALITY12_ERROR;
        }
    }
    if ( AIRQUALITY12_OK == error_flag )
    {
        if ( rd_buf[ params->resp_len + 1 ] == airquality12_get_checksum ( rd_buf, params->resp_len + 1 ) )
        {
            params->status = rd_buf[ 0 ];
            memcpy ( params->resp_buf, &rd_buf[ 1 ], params->resp_len );
        }
        else
        {
            error_flag = AIRQUALITY12_ERROR;
        }
    }

    if ( ( AIRQUALITY12_DRV_SEL_UART == ctx->drv_sel ) && ( AIRQUALITY12_ERROR == error_flag ) ) 
    {
        wr_buf[ 0 ] = 0xFF;
        uart_write( &ctx->uart, wr_buf, 1 );
    }
    
    return error_flag;
}

void airquality12_set_rst_pin ( airquality12_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void airquality12_set_gp1_pin ( airquality12_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->gp1, state );
}

void airquality12_reset_device ( airquality12_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

uint8_t airquality12_get_int_pin ( airquality12_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t airquality12_check_comm ( airquality12_t *ctx )
{
    airquality12_info_t info;
    if ( AIRQUALITY12_OK == airquality12_get_sensor_info ( ctx, &info ) )
    {
        if ( AIRQUALITY12_PRODUCT_ID == info.product_id )
        {
            return AIRQUALITY12_OK;
        }
    }
    return AIRQUALITY12_ERROR;
}

err_t airquality12_get_sensor_info ( airquality12_t *ctx, airquality12_info_t *info )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_len = 0;
    params.resp_len = 5;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_GET_PRODUCT_ID, &params );
    if ( AIRQUALITY12_OK == error_flag )
    {
        if ( NULL != info )
        {
            info->product_id = ( ( uint16_t ) params.resp_buf[ 1 ] << 8 ) | params.resp_buf[ 0 ];
            info->fw_ver_major = params.resp_buf[ 4 ];
            info->fw_ver_minor = params.resp_buf[ 3 ];
            info->fw_ver_patch = params.resp_buf[ 2 ];
        }
        if ( AIRQUALITY12_STATUS_OK != params.status )
        {
            error_flag = AIRQUALITY12_ERROR;
        }
        else
        {
            params.resp_len = 6;
            error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_GET_TRACKING_NUMBER, &params );
        }
    }
    if ( AIRQUALITY12_OK == error_flag )
    {
        if ( NULL != info )
        {
            memcpy ( info->tracking_num, params.resp_buf, 6 );
        }
        if ( AIRQUALITY12_STATUS_OK != params.status )
        {
            error_flag = AIRQUALITY12_ERROR;
        }
    }
    return error_flag;
}

err_t airquality12_get_op_mode ( airquality12_t *ctx, uint8_t *op_mode )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_len = 0;
    params.resp_len = 1;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_GET_OPERATION_MODE, &params );
    if ( ( AIRQUALITY12_STATUS_OK != params.status ) && 
         ( AIRQUALITY12_STATUS_NO_MORE_CLEANING != params.status ) )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    if ( ( AIRQUALITY12_OK == error_flag ) && ( NULL != op_mode ) )
    {
        *op_mode = params.resp_buf[ 0 ];
    }
    return error_flag;
}

err_t airquality12_set_op_mode ( airquality12_t *ctx, uint8_t op_mode )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_buf[ 0 ] = op_mode;
    params.req_len = 1;
    params.resp_len = 0;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_SET_OPERATION_MODE, &params );
    if ( AIRQUALITY12_STATUS_OK != params.status )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    return error_flag;
}

err_t airquality12_set_humidity ( airquality12_t *ctx, float humidity )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    if ( ( humidity < AIRQUALITY12_HUMIDITY_MIN ) || ( humidity > AIRQUALITY12_HUMIDITY_MAX ) )
    {
        return AIRQUALITY12_ERROR;
    }
    params.req_buf[ 0 ] = ( uint8_t ) ( ( humidity / AIRQUALITY12_HUMIDITY_MAX ) * 255 );
    params.req_len = 1;
    params.resp_len = 0;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_SET_HUMIDITY, &params );
    if ( AIRQUALITY12_STATUS_OK != params.status )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    return error_flag;
}

err_t airquality12_get_measurement ( airquality12_t *ctx, airquality12_results_t *results )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    uint8_t op_mode = 0;
    params.req_len = 0;

    error_flag |= airquality12_get_op_mode ( ctx, &op_mode );
    if ( AIRQUALITY12_OK == error_flag )
    {
        switch ( op_mode )
        {
            case AIRQUALITY12_OP_MODE_IAQ_2ND_GEN:
            case AIRQUALITY12_OP_MODE_IAQ_2ND_GEN_ULP:
            {
                params.resp_len = 9;
                error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_GET_MEASUREMENT, &params );
                if ( AIRQUALITY12_STATUS_OK != params.status )
                {
                    error_flag = AIRQUALITY12_ERROR;
                }
                if ( AIRQUALITY12_OK == error_flag )
                {
                    results->sample_num = params.resp_buf[ 0 ];
                    results->iaq = ( float ) params.resp_buf[ 1 ] / 10;
                    results->tvoc = ( float ) ( ( ( uint16_t ) params.resp_buf[ 3 ] << 8 ) | params.resp_buf[ 2 ] ) / 100;
                    results->etoh = ( float ) ( ( ( uint16_t ) params.resp_buf[ 5 ] << 8 ) | params.resp_buf[ 4 ] ) / 100;
                    results->eco2 = ( ( uint16_t ) params.resp_buf[ 7 ] << 8 ) | params.resp_buf[ 6 ];
                    results->rel_iaq = ( float ) params.resp_buf[ 8 ] * 10;
                }
                break;
            }
            case AIRQUALITY12_OP_MODE_PBAQ:
            {
                params.resp_len = 5;
                error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_GET_MEASUREMENT, &params );
                if ( AIRQUALITY12_STATUS_OK != params.status )
                {
                    error_flag = AIRQUALITY12_ERROR;
                }
                if ( AIRQUALITY12_OK == error_flag )
                {
                    results->sample_num = params.resp_buf[ 0 ];
                    results->tvoc = ( float ) ( ( ( uint16_t ) params.resp_buf[ 2 ] << 8 ) | params.resp_buf[ 1 ] ) / 1000;
                    results->etoh = ( float ) ( ( ( uint16_t ) params.resp_buf[ 4 ] << 8 ) | params.resp_buf[ 3 ] ) / 1000;
                }
                break;
            }
            default:
            {
                error_flag = AIRQUALITY12_ERROR;
                break;
            }
        }
    }
    
    return error_flag;
}

err_t airquality12_config_gpio ( airquality12_t *ctx, uint8_t gpio_mask )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_buf[ 0 ] = gpio_mask;
    params.req_len = 1;
    params.resp_len = 0;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_CONFIG_GPIO, &params );
    if ( AIRQUALITY12_STATUS_OK != params.status )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    return error_flag;
}

err_t airquality12_get_gpio ( airquality12_t *ctx, uint8_t *gpio_mask )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_len = 0;
    params.resp_len = 1;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_GET_GPIO, &params );
    if ( AIRQUALITY12_STATUS_OK != params.status )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    if ( ( AIRQUALITY12_OK == error_flag ) && ( NULL != gpio_mask ) )
    {
        *gpio_mask = params.resp_buf[ 0 ];
    }
    return error_flag;
}

err_t airquality12_set_gpio ( airquality12_t *ctx, uint8_t gpio_mask )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_buf[ 0 ] = gpio_mask;
    params.req_len = 1;
    params.resp_len = 0;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_SET_GPIO, &params );
    if ( AIRQUALITY12_STATUS_OK != params.status )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    return error_flag;
}

err_t airquality12_clear_gpio ( airquality12_t *ctx, uint8_t gpio_mask )
{
    err_t error_flag = AIRQUALITY12_OK;
    airquality12_param_t params;
    params.req_buf[ 0 ] = gpio_mask;
    params.req_len = 1;
    params.resp_len = 0;
    error_flag |= airquality12_send_cmd ( ctx, AIRQUALITY12_CMD_CLEAR_GPIO, &params );
    if ( AIRQUALITY12_STATUS_OK != params.status )
    {
        error_flag = AIRQUALITY12_ERROR;
    }
    return error_flag;
}

err_t airquality12_perform_cleaning ( airquality12_t *ctx )
{
    err_t error_flag = AIRQUALITY12_OK;
    uint8_t op_mode_backup = 0;
    uint8_t op_mode = 0;
    uint8_t num_tries = 0;
    error_flag |= airquality12_get_op_mode ( ctx, &op_mode_backup );
    error_flag |= airquality12_set_op_mode ( ctx, AIRQUALITY12_OP_MODE_SENSOR_CLEANING );
    error_flag |= airquality12_get_op_mode ( ctx, &op_mode );
    while ( ( AIRQUALITY12_OK == error_flag ) && ( AIRQUALITY12_OP_MODE_SENSOR_CLEANING == op_mode ) )
    {
        Delay_1sec ( );
        error_flag |= airquality12_get_op_mode ( ctx, &op_mode );
        if ( num_tries++ >= 65 )
        {
            error_flag = AIRQUALITY12_ERROR;
        }
    }
    error_flag |= airquality12_set_op_mode ( ctx, op_mode_backup );
    return error_flag;
}

static uint8_t airquality12_get_checksum ( uint8_t *data_in, uint8_t len )
{
    uint8_t checksum = 0;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        checksum += data_in[ cnt ];
    }
    return ( ~checksum );
}

// ------------------------------------------------------------------------ END

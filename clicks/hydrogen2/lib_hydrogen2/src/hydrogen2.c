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
 * @file hydrogen2.c
 * @brief Hydrogen 2 Click Driver.
 */

#include "hydrogen2.h"

/** 
 * @brief CCITT-FALSE calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x1021 ( x16 + x12 + x5 + x0 )
 * @li @c  Initialization 0xFFFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @li @c  Example { AB, CD } - 0xD46A
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t hydrogen2_calc_crc16_ccitt ( uint8_t *data_buf, uint16_t len );

void hydrogen2_cfg_setup ( hydrogen2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sby = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HYDROGEN2_DEVICE_ADDRESS;
}

err_t hydrogen2_init ( hydrogen2_t *ctx, hydrogen2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->sby, cfg->sby );

    return I2C_MASTER_SUCCESS;
}

err_t hydrogen2_default_cfg ( hydrogen2_t *ctx ) 
{
    err_t error_flag = HYDROGEN2_OK;

    if ( HYDROGEN2_OK != hydrogen2_read_id ( ctx ) )
    {
        return HYDROGEN2_ERROR;
    }

    error_flag |= hydrogen2_set_config ( ctx, ( HYDROGEN2_CFG_1_SPIKE_FILTER_DIS | 
                                                HYDROGEN2_CFG_1_PP2_WAKE_LOW | 
                                                HYDROGEN2_CFG_1_WAKE_MAP_PP2 ), 
                                              HYDROGEN2_CFG_2_BUSY_MAP_STDBY, 
                                              HYDROGEN2_CFG_3_STANDBY_MAP_STDBY );

    return error_flag;
}

err_t hydrogen2_write_cmd ( hydrogen2_t *ctx, uint8_t cmd, uint8_t *param_in, uint8_t param_len )
{
    uint8_t data_buf[ 7 ] = { 0 };
    uint16_t timeout_cnt = 0; 
    uint16_t crc = 0;
    if ( param_len > 4 )
    {
        return HYDROGEN2_ERROR;
    }
    data_buf[ 0 ] = cmd;
    if ( NULL != param_in )
    {
        memcpy ( &data_buf[ 1 ], param_in, param_len );
    }
    crc = hydrogen2_calc_crc16_ccitt ( data_buf, param_len + 1 );
    data_buf[ param_len + 1 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    data_buf[ param_len + 2 ] = ( uint8_t ) ( crc & 0xFF );
    Delay_1ms ( );
    while ( hydrogen2_get_sby_pin ( ctx ) )
    {
        if ( ++timeout_cnt > HYDROGEN2_TIMEOUT_MS )
        {
            return HYDROGEN2_ERROR;
        }
        Delay_1ms ( );
    }
    return i2c_master_write( &ctx->i2c, data_buf, param_len + 3 );
}

err_t hydrogen2_read_response ( hydrogen2_t *ctx, uint8_t *status, uint8_t *param_out, uint8_t param_len )
{
    err_t error_flag = HYDROGEN2_OK;
    uint8_t data_buf[ 12 ] = { 0 };
    uint16_t timeout_cnt = 0; 
    uint16_t crc = 0;
    uint16_t crc_read = 0;
    if ( param_len > 10 )
    {
        return HYDROGEN2_ERROR;
    }
    Delay_1ms ( );
    while ( hydrogen2_get_sby_pin ( ctx ) )
    {
        if ( ++timeout_cnt > HYDROGEN2_TIMEOUT_MS )
        {
            return HYDROGEN2_ERROR;
        }
        Delay_1ms ( );
    }
    error_flag = i2c_master_read( &ctx->i2c, data_buf, param_len + 3 );
    if ( HYDROGEN2_OK == error_flag )
    {
        crc = hydrogen2_calc_crc16_ccitt ( data_buf, param_len + 1 );
        crc_read = ( ( uint16_t ) data_buf[ param_len + 1 ] << 8 ) | data_buf[ param_len + 2 ];
        if ( crc != crc_read )
        {
            error_flag = HYDROGEN2_ERROR;
        }
    }
    if ( HYDROGEN2_OK == error_flag )
    {
        if ( NULL != status )
        {
            *status = data_buf[ 0 ];
        }
        if ( NULL != param_out )
        {
            memcpy ( param_out, &data_buf[ 1 ], param_len );
        }
    }
    return error_flag;
}

uint8_t hydrogen2_get_sby_pin ( hydrogen2_t *ctx )
{
    return !!digital_in_read ( &ctx->sby );
}

err_t hydrogen2_get_conc ( hydrogen2_t *ctx, int16_t *conc )
{
    err_t error_flag = HYDROGEN2_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t status = 0;
    data_buf[ 0 ] = HYDROGEN2_CONC_CONFIG_RH_RES_1 | 
                    HYDROGEN2_CONC_CONFIG_FIELD_CONT_DIS | 
                    HYDROGEN2_CONC_CONFIG_EOL_CONT_DIS | 
                    HYDROGEN2_CONC_CONFIG_MEMS_VREG_NO_BP | 
                    HYDROGEN2_CONC_CONFIG_CALIB_SEL_H2 | 
                    HYDROGEN2_CONC_CONFIG_COMP_SEL_RAW; // Config
    data_buf[ 1 ] = HYDROGEN2_CONC_RH_DEFAULT; // RH at 50%
    data_buf[ 2 ] = HYDROGEN2_CONC_T_DEFAULT;  // Temp at 25degC
    data_buf[ 3 ] = HYDROGEN2_CONC_P_DEFAULT;  // Pressure at 100kPa
    error_flag = hydrogen2_write_cmd ( ctx, HYDROGEN2_CMD_TRIG_CONC_MEAS, data_buf, 4 );
    if ( HYDROGEN2_OK == error_flag )
    {
        error_flag = hydrogen2_read_response ( ctx, &status, data_buf, 2 );
        if ( HYDROGEN2_STATUS_OK != status )
        {
            error_flag = HYDROGEN2_ERROR;
        }
    }
    if ( HYDROGEN2_OK == error_flag )
    {
        *conc = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t hydrogen2_get_temp ( hydrogen2_t *ctx, int8_t *temp )
{
    err_t error_flag = HYDROGEN2_OK;
    uint8_t data_buf[ 1 ] = { 0 };
    uint8_t status = 0;
    error_flag = hydrogen2_write_cmd ( ctx, HYDROGEN2_CMD_TRIG_TEMP_MEAS, NULL, 0 );
    if ( HYDROGEN2_OK == error_flag )
    {
        error_flag = hydrogen2_read_response ( ctx, &status, data_buf, 1 );
        if ( HYDROGEN2_STATUS_OK != status )
        {
            error_flag = HYDROGEN2_ERROR;
        }
    }
    if ( HYDROGEN2_OK == error_flag )
    {
        *temp = ( int8_t ) data_buf[ 0 ];
    }
    return error_flag;
}

err_t hydrogen2_set_config ( hydrogen2_t *ctx, uint8_t cfg_1, uint8_t cfg_2, uint8_t cfg_3 )
{
    err_t error_flag = HYDROGEN2_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t status = 0;
    data_buf[ 0 ] = cfg_1;
    data_buf[ 1 ] = cfg_2;
    data_buf[ 2 ] = cfg_3;
    error_flag = hydrogen2_write_cmd ( ctx, HYDROGEN2_CMD_SET_CONFIG, data_buf, 3 );
    if ( HYDROGEN2_OK == error_flag )
    {
        error_flag = hydrogen2_read_response ( ctx, &status, NULL, 0 );
        if ( HYDROGEN2_STATUS_OK != status )
        {
            error_flag = HYDROGEN2_ERROR;
        }
    }
    return error_flag;
}

err_t hydrogen2_go_standby ( hydrogen2_t *ctx )
{
    return hydrogen2_write_cmd ( ctx, HYDROGEN2_CMD_STANDBY, NULL, 0 );
}

err_t hydrogen2_read_id ( hydrogen2_t *ctx )
{
    err_t error_flag = HYDROGEN2_OK;
    uint8_t data_buf[ 9 ] = { 0 };
    uint8_t status = 0;
    error_flag = hydrogen2_write_cmd ( ctx, HYDROGEN2_CMD_READ_ID, NULL, 0 );
    if ( HYDROGEN2_OK == error_flag )
    {
        error_flag = hydrogen2_read_response ( ctx, &status, data_buf, 9 );
        if ( HYDROGEN2_STATUS_OK != status )
        {
            error_flag = HYDROGEN2_ERROR;
        }
    }
    if ( HYDROGEN2_OK == error_flag )
    {
        ctx->info.sensor_id = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | 
                              ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                              ( ( uint16_t ) data_buf[ 2 ] << 8 ) | 
                                             data_buf[ 3 ];
        ctx->info.product_code = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        ctx->info.fw_rev_num = ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ];
        ctx->info.man_code = data_buf[ 8 ];
    }
    return error_flag;
}

static uint16_t hydrogen2_calc_crc16_ccitt ( uint8_t *data_buf, uint16_t len )
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

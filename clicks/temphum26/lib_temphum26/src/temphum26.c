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
 * @file temphum26.c
 * @brief TempHum 26 Click Driver.
 */

#include "temphum26.h"

/**
 * @brief TempHum 25 crc constants.
 * @details Specified constants for crc of TempHum 25 Click driver.
 */
#define TEMPHUM26_CRC_WIDTH                 7
#define TEMPHUM26_CRC_POLYNOM               0x89
#define TEMPHUM26_CRC_INIT_VALUE            0x7F
#define TEMPHUM26_CRC_MASK                  0x7F
#define TEMPHUM26_CRC_DATA_WIDTH            17
#define TEMPHUM26_CRC_DATA_MASK             0x0001FFFFul
#define TEMPHUM26_CRC_DATA_MSB              0x00010000ul

/** 
 * @brief TempHum 26 calculation for CRC-7 function.
 * @details This function calculates CRC-7 with parameteres: 
 * @li @c  Width 7 bit
 * @li @c  Polynomial 0x89 (x7 + x3 + x0)
 * @li @c  Initialization 0x7F
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0x149FD) = 0x05
 * @param[in] crc_source : 2 bytes array to calculate crc from.
 * @return Calculated CRC-7 output.
 * @note None.
 */
static uint8_t temphum26_calculate_crc ( uint32_t crc_source );

void temphum26_cfg_setup ( temphum26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM26_DEVICE_ADDRESS;
}

err_t temphum26_init ( temphum26_t *ctx, temphum26_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t temphum26_default_cfg ( temphum26_t *ctx ) 
{
    err_t error_flag = TEMPHUM26_OK;
    temphum26_disable_device ( ctx );
    Delay_100ms ( );
    temphum26_enable_device ( ctx );
    Delay_100ms ( );
    if ( TEMPHUM26_ERROR == temphum26_check_communication ( ctx ) )
    {
        return TEMPHUM26_ERROR;
    }
    error_flag |= temphum26_set_measurement_mode ( ctx, TEMPHUM26_MODE_SINGLE_SHOT );
    return error_flag;
}

err_t temphum26_write_regs ( temphum26_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t temphum26_read_regs ( temphum26_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t temphum26_write_reg ( temphum26_t *ctx, uint8_t reg, uint8_t data_in )
{
    return temphum26_write_regs( ctx, reg, &data_in, 1 );
}

err_t temphum26_read_reg ( temphum26_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return temphum26_read_regs( ctx, reg, data_out, 1 );
}

void temphum26_enable_device ( temphum26_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void temphum26_disable_device ( temphum26_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t temphum26_check_communication ( temphum26_t *ctx )
{
    err_t error_flag = TEMPHUM26_OK;
    uint8_t data_buf[ 12 ] = { 0 };

    error_flag |= temphum26_power_mode_active ( ctx );
    if ( TEMPHUM26_OK == error_flag )
    {
        error_flag |= temphum26_read_regs ( ctx, TEMPHUM26_REG_PART_ID, data_buf, 12 );
    }
    if ( TEMPHUM26_OK == error_flag )
    {
        ctx->info.part_id = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        ctx->info.die_rev = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        memcpy ( ctx->info.uid, &data_buf[ 4 ], 8 );
    }
    if ( TEMPHUM26_OK == error_flag )
    {
        error_flag |= temphum26_power_mode_standby ( ctx );
    }
    if ( TEMPHUM26_PART_ID != ctx->info.part_id )
    {
        error_flag |= TEMPHUM26_ERROR;
    }
    return error_flag;
}

err_t temphum26_power_mode_active ( temphum26_t *ctx )
{
    err_t error_flag = TEMPHUM26_OK;
    uint8_t sys_stat = 0;
    error_flag |= temphum26_write_reg ( ctx, TEMPHUM26_REG_SYS_CTRL, TEMPHUM26_SYS_CTRL_LOW_POWER_DISABLE );
    if ( TEMPHUM26_OK == error_flag )
    {
        Delay_10ms ( );
        error_flag |= temphum26_read_reg ( ctx, TEMPHUM26_REG_SYS_STAT, &sys_stat );
        if ( sys_stat != TEMPHUM26_SYS_STAT_ACTIVE )
        {
            error_flag |= TEMPHUM26_ERROR;
        }
    }
    return error_flag;
}

err_t temphum26_power_mode_standby ( temphum26_t *ctx )
{
    err_t error_flag = TEMPHUM26_OK;
    uint8_t sys_stat = 0;
    error_flag |= temphum26_write_reg ( ctx, TEMPHUM26_REG_SYS_CTRL, TEMPHUM26_SYS_CTRL_LOW_POWER_ENABLE );
    if ( TEMPHUM26_OK == error_flag )
    {
        Delay_10ms ( );
        error_flag |= temphum26_read_reg ( ctx, TEMPHUM26_REG_SYS_STAT, &sys_stat );
        if ( sys_stat != TEMPHUM26_SYS_STAT_STANDBY )
        {
            error_flag |= TEMPHUM26_ERROR;
        }
    }
    return error_flag;
}

err_t temphum26_set_measurement_mode ( temphum26_t *ctx, uint8_t mode )
{
    if ( mode > TEMPHUM26_MODE_CONTINUOUS )
    {
        return TEMPHUM26_ERROR;
    }
    return temphum26_write_reg ( ctx, TEMPHUM26_REG_SENS_RUN, mode | ( mode << 1 ) );
}

err_t temphum26_start_measurement ( temphum26_t *ctx, uint8_t flag )
{
    if ( flag > TEMPHUM26_FLAG_TEMP_HUM )
    {
        return TEMPHUM26_ERROR;
    }
    return temphum26_write_reg ( ctx, TEMPHUM26_REG_SENS_START, flag + 1 );
}

err_t temphum26_stop_measurement ( temphum26_t *ctx, uint8_t flag )
{
    if ( flag > TEMPHUM26_FLAG_TEMP_HUM )
    {
        return TEMPHUM26_ERROR;
    }
    return temphum26_write_reg ( ctx, TEMPHUM26_REG_SENS_STOP, flag + 1 );
}

err_t temphum26_read_data ( temphum26_t *ctx, float *temp, float *hum )
{
    err_t error_flag = TEMPHUM26_ERROR;
    uint8_t data_buf[ 6 ] = { 0 };
    uint16_t raw_data = 0;
    uint32_t crc_source = 0;
    uint8_t crc = 0;
    for ( uint8_t num_tries = 0; ( num_tries < TEMPHUM26_NUM_MEASUREMENT_TRIES ) && ( TEMPHUM26_ERROR == error_flag ); num_tries++ )
    {
        error_flag = temphum26_read_regs ( ctx, TEMPHUM26_REG_T_VAL, data_buf, 6 );
        if ( TEMPHUM26_OK == error_flag )
        {
            if ( NULL != temp )
            {
                crc_source = ( ( ( uint32_t ) data_buf[ 2 ] & TEMPHUM26_DATA_VALID_BIT ) << 16 ) | 
                             ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
                crc = ( data_buf[ 2 ] >> 1 ) & TEMPHUM26_CRC_MASK;
                if ( ( crc == temphum26_calculate_crc ( crc_source ) ) && ( data_buf[ 2 ] & TEMPHUM26_DATA_VALID_BIT ) )
                {
                    raw_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
                    *temp = ( float ) raw_data / TEMPHUM26_TEMPERATURE_RES - TEMPHUM26_TEMPERATURE_K_TO_C;
                }
                else
                {
                    error_flag |= TEMPHUM26_ERROR;
                }
            }
            
            if ( NULL != hum )
            {
                crc_source = ( ( ( uint32_t ) data_buf[ 5 ] & TEMPHUM26_DATA_VALID_BIT ) << 16 ) | 
                             ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ];
                crc = ( data_buf[ 5 ] >> 1 ) & TEMPHUM26_CRC_MASK;
                if ( ( crc == temphum26_calculate_crc ( crc_source ) ) && ( data_buf[ 5 ] & TEMPHUM26_DATA_VALID_BIT ) )
                {
                    raw_data = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ];
                    *hum = ( float ) raw_data / TEMPHUM26_HUMIDITY_RES;
                }
                else
                {
                    error_flag |= TEMPHUM26_ERROR;
                }
            }
        }
        Delay_10ms ( );
    }
    return error_flag;
}

static uint8_t temphum26_calculate_crc ( uint32_t crc_source )
{
    // Setup polynomial
    uint32_t poly = TEMPHUM26_CRC_POLYNOM;
    // Align polynomial with data
    poly = poly << ( TEMPHUM26_CRC_DATA_WIDTH - TEMPHUM26_CRC_WIDTH - 1 );
    // Loop variable (indicates which bit to test, start with highest)
    uint32_t bit_mask = TEMPHUM26_CRC_DATA_MSB;
    // Make room for CRC value
    crc_source = crc_source << TEMPHUM26_CRC_WIDTH;
    bit_mask = bit_mask << TEMPHUM26_CRC_WIDTH;
    poly = poly << TEMPHUM26_CRC_WIDTH;
    // Insert initial vector
    crc_source |= TEMPHUM26_CRC_INIT_VALUE;
    // Apply division until all bits done
    while ( bit_mask & ( TEMPHUM26_CRC_DATA_MASK << TEMPHUM26_CRC_WIDTH ) )
    {
        if ( bit_mask & crc_source ) 
        {
            crc_source ^= poly;
        }
        bit_mask >>= 1;
        poly >>= 1;
    }
    return ( uint8_t ) ( crc_source & TEMPHUM26_CRC_MASK );
}

// ------------------------------------------------------------------------- END

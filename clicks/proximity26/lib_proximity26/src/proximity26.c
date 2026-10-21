/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file proximity26.c
 * @brief Proximity 26 Click Driver.
 */

#include "proximity26.h"

void proximity26_cfg_setup ( proximity26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY26_DEVICE_ADDRESS;
}

err_t proximity26_init ( proximity26_t *ctx, proximity26_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t proximity26_default_cfg ( proximity26_t *ctx ) 
{
    err_t error_flag = PROXIMITY26_OK;
    
    if ( PROXIMITY26_OK != proximity26_check_com ( ctx ) )
    {
        return PROXIMITY26_ERROR;
    }

    /*
     * PS_CONF5 register (0x08):
     *
     *  - bits[7:4]  = 1010 -> must be set to 0xA (page 15, table 15).
     *  - bits[3:0]  = 0000 -> reserved, should be kept at default
     *  - bits[15:8] = 0x00 -> reserved, should be kept at default
     */
    error_flag |= proximity26_write_reg ( ctx, PROXIMITY26_REG_PS_CONF5, PROXIMITY26_PS_CONF5_RESERVED );

    /*
     * PS_CONF2 register (0x01):
     *
     *  - bits[15:12] = 0000 -> reserved, should be kept at default
     *  - bits[11:8]  = 1000 -> PS_IT, integration time of one measurement set
     *                          to 25 us x 8 = 200 us (page 13, table 7).
     *  - bits[7:0]   = 31   -> PS_WAIT, wait time between two measurements in auto mode.
     *                          2.5 ms x ( 31 + 1 ) = 80 ms (page 12, table 6).
     */
    error_flag |= proximity26_write_reg ( ctx, PROXIMITY26_REG_PS_CONF2, 
                                               PROXIMITY26_PS_CONF2_PS_IT_200_US | 
                                               PROXIMITY26_PS_CONF2_PS_WAIT_80_MS | 
                                               PROXIMITY26_PS_CONF2_RESERVED );
    /*
     * PS_CONF3 register (0x02):
     *
     *  - bit[15]     = 0   -> reserved, should be kept at default
     *  - bit[14]     = 1   -> high gain of the ADC set to x2.
     *  - bits[13:12] = 00  -> gain of the ADC set to x4.
     *  - bit[11]     = 0   -> reserved, should be kept at default
     *  - bits[10:8]  = 111 -> PD3, PD2 and PD1 photodiodes enabled.
     *  - bits[7:4]   = 000 -> reserved, should be kept at default
     *  - bit[3]      = 1   -> enable VCSEL driver
     *  - bits[2:0]   = 010 -> VCSEL driving current set to 8 mA.
     *
     * The gain, integration time and photodiode settings match the conditions
     * of the proximity value vs. distance characteristic (page 8, figure 11).
     */
    error_flag |= proximity26_write_reg ( ctx, PROXIMITY26_REG_PS_CONF3, 
                                               PROXIMITY26_PS_CONF3_PS_HG_X2 | 
                                               PROXIMITY26_PS_CONF3_PS_GAIN_X4 | 
                                               PROXIMITY26_PS_CONF3_PD_ALL_EN | 
                                               PROXIMITY26_PS_CONF3_DRIVER_EN | 
                                               PROXIMITY26_PS_CONF3_PS_CURRENT_8_MA | 
                                               PROXIMITY26_PS_CONF3_RESERVED );

    /*
     * PS_CONF1 register (0x00) - first write:
     *
     *  - bits[15:14] = 00  -> interrupt disabled, the example polls the proximity data.
     *  - bit[8]      = 1   -> PS_SD, sensor still kept in shutdown.
     *  - bit[7]      = 1   -> internal calibration enabled.
     *  - bit[6]      = 0   -> reserved, should be kept at default
     *  - bit[5]      = 0   -> force trigger mode off
     *  - bit[4]      = 0   -> auto measurement mode selected.
     *  - bits[3:1]   = 000 -> reserved, should be kept at default
     *  - bit[0]      = 1   -> turn on the sensor
     */
    error_flag |= proximity26_write_reg ( ctx, PROXIMITY26_REG_PS_CONF1, 
                                               PROXIMITY26_PS_CONF1_PS_INT_DIS | 
                                               PROXIMITY26_PS_CONF1_PS_CAL_EN | 
                                               PROXIMITY26_PS_CONF1_PS_MODE_AUTO | 
                                               PROXIMITY26_PS_CONF1_PS_ON_EN | 
                                               PROXIMITY26_PS_CONF1_PS_SD_SHUT_DOWN | 
                                               PROXIMITY26_PS_CONF1_RESERVED );
    /*
     * PS_CONF1 register (0x00) - second write:
     *
     *  - bit[8] = 0 -> PS_SD cleared, the sensor leaves shutdown and starts
     *                  measuring with the configured wait time.
     *
     * The sensor is enabled in two steps, the shutdown bit is cleared last so
     * that the calibration is set up before the first measurement cycle starts.
     */
    error_flag |= proximity26_write_reg ( ctx, PROXIMITY26_REG_PS_CONF1, 
                                               PROXIMITY26_PS_CONF1_PS_INT_DIS | 
                                               PROXIMITY26_PS_CONF1_PS_CAL_EN | 
                                               PROXIMITY26_PS_CONF1_PS_MODE_AUTO | 
                                               PROXIMITY26_PS_CONF1_PS_ON_EN | 
                                               PROXIMITY26_PS_CONF1_PS_SD_POWER_ON | 
                                               PROXIMITY26_PS_CONF1_RESERVED );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );

    return error_flag;
}

err_t proximity26_write_reg ( proximity26_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    /* Write frame : S | sl_addr + W | A | reg | A | data_LSB | A | data_MSB | A | P */
    uint8_t data_buf[ PROXIMITY26_I2C_WRITE_DATA_NUM ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) data_in;
    data_buf[ 2 ] = ( uint8_t ) ( data_in >> 8 );

    return i2c_master_write( &ctx->i2c, data_buf, PROXIMITY26_I2C_WRITE_DATA_NUM );
}

err_t proximity26_read_reg ( proximity26_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    /* Read frame : S | sl_addr + W | A | reg | A | Sr | sl_addr + R | A | data_LSB | A | data_MSB | N | P */
    uint8_t data_buf[ PROXIMITY26_I2C_READ_DATA_NUM ] = { 0 };

    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, PROXIMITY26_I2C_READ_DATA_NUM ) )
    {
        return PROXIMITY26_ERROR;
    }
    if ( NULL != data_out )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }

    return PROXIMITY26_OK;
}

err_t proximity26_check_com ( proximity26_t *ctx ) 
{
    uint16_t device_id = 0;

    /* Only the low byte of the ID register is fixed, the high byte depends on the slave address */
    if ( PROXIMITY26_OK == proximity26_read_reg ( ctx, PROXIMITY26_REG_ID, &device_id ) )
    {
        if ( PROXIMITY26_DEVICE_ID == ( device_id & PROXIMITY26_DEVICE_ID_MASK ) )
        {
            return PROXIMITY26_OK;
        }
    }
    return PROXIMITY26_ERROR;
}

err_t proximity26_read_proximity ( proximity26_t *ctx, uint16_t *ps_data ) 
{
    return proximity26_read_reg ( ctx, PROXIMITY26_REG_PS_DATA, ps_data );
}

uint8_t proximity26_get_int_pin ( proximity26_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

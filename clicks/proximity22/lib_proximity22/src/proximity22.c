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
 * @file proximity22.c
 * @brief Proximity 22 Click Driver.
 */

#include "proximity22.h"

void proximity22_cfg_setup ( proximity22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY22_DEVICE_ADDRESS;
}

err_t proximity22_init ( proximity22_t *ctx, proximity22_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t proximity22_default_cfg ( proximity22_t *ctx ) 
{
    err_t error_flag = PROXIMITY22_OK;
    uint8_t status = 0;

    proximity22_reset_device ( ctx );
    if ( PROXIMITY22_ERROR == proximity22_check_comm ( ctx ) )
    {
        return PROXIMITY22_ERROR;
    }
    error_flag |= proximity22_soft_reset ( ctx );
    Delay_100ms ( );

    // Enable internal oscillator and ADC channels
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_ENABLE, PROXIMITY22_ENABLE_PON );
    Delay_100ms ( );
    
    // IPTAT needs to be changed from default during initialization
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_IPTAT, PROXIMITY22_IPTAT_INIT );

    // Select color mode and enable temperature sensor
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_CFG1, PROXIMITY22_CFG1_PD_MUX_SEL_COLOR_MODE | 
                                                                     PROXIMITY22_CFG1_ENAB_TEMP_SENSOR );

    // Enable interrupt clear on status read and set operating mode
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_CFG3, PROXIMITY22_CFG3_INT_READ_CLEAR | 
                                                                     PROXIMITY22_CFG3_MODE_CFG_SEQUENTIAL | 
                                                                     PROXIMITY22_CFG3_RESERVED );

    // Enable LEDs driver and set drive current to 5 mA
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_LDR0_CFG, PROXIMITY22_LDR0_CFG_EN_LDR_0 | 
                                                                         PROXIMITY22_LDR0_CFG_ISINK_LSB_1_0_MA | 
                                                                         PROXIMITY22_LDR0_CFG_PLDRIVE0_4 );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_LDR1_CFG, PROXIMITY22_LDR1_CFG_EN_LDR_1 | 
                                                                         PROXIMITY22_LDR1_CFG_PLDRIVE1_4 );

    // Set proximity gain, max number of pulses, pulse length, and sample duration
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_PCFG0, PROXIMITY22_PCFG0_PGAIN_1X | 
                                                                      PROXIMITY22_PCFG0_PGAIN2_2_5X );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_PCFG1, PROXIMITY22_PCFG1_PPULSE_32 );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_PCFG2, PROXIMITY22_PCFG2_PPULSE_LENL_34_US );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_PTIME, PROXIMITY22_PTIME_2_816_MS );

    // Set ALS gain, integration time, and wait time (which presents full data sample rate)
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_AGAIN_1_0, ( PROXIMITY22_AGAIN_4X << 4 ) | 
                                                                            PROXIMITY22_AGAIN_4X );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_AGAIN_3_2, ( PROXIMITY22_AGAIN_4X << 4 ) | 
                                                                            PROXIMITY22_AGAIN_4X );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_ATIME, PROXIMITY22_ATIME_88_923_MS );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_AWTIME, PROXIMITY22_AWTIME_200_088_MS );
    
    // Set proximity data target number, number of samples for averaging, and starts calibration
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_CALIBCFG, PROXIMITY22_CALIBCFG_BINSRCH_TARGET_15 | 
                                                                         PROXIMITY22_CALIBCFG_RESERVED | 
                                                                         PROXIMITY22_CALIBCFG_PROX_DATA_AVG_8 );
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_CALIB, PROXIMITY22_CALIB_START_OFFSET_CAL );
    while ( PROXIMITY22_CALIBSTAT_CALIB_FINISHED != ( status & PROXIMITY22_CALIBSTAT_CALIB_FINISHED ) )
    {
        error_flag |= proximity22_read_reg ( ctx, PROXIMITY22_REG_CALIBSTAT, &status );
        Delay_100ms ( );
    }

    // Enable proximity APC
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_CFG6, PROXIMITY22_CFG6_RESERVED );

    // Enable ALS wait time interrupt
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_INTENAB_2, PROXIMITY22_INTENAB_2_AWIEN );
    
    // Enable temperature, proximity, and ALS functions
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_ENABLE, PROXIMITY22_ENABLE_TEN | 
                                                                       PROXIMITY22_ENABLE_AWEN | 
                                                                       PROXIMITY22_ENABLE_PEN | 
                                                                       PROXIMITY22_ENABLE_AEN |
                                                                       PROXIMITY22_ENABLE_PON );
    Delay_100ms ( );
    return error_flag;
}

err_t proximity22_write_regs ( proximity22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t proximity22_read_regs ( proximity22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t proximity22_write_reg ( proximity22_t *ctx, uint8_t reg, uint8_t data_in )
{
    return proximity22_write_regs ( ctx, reg, &data_in, 1 );
}

err_t proximity22_read_reg ( proximity22_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return proximity22_read_regs ( ctx, reg, data_out, 1 );
}

void proximity22_set_rst_pin ( proximity22_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t proximity22_get_int_pin ( proximity22_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void proximity22_reset_device ( proximity22_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

err_t proximity22_check_comm ( proximity22_t *ctx )
{
    uint8_t dev_id = 0;
    if ( PROXIMITY22_OK == proximity22_read_reg ( ctx, PROXIMITY22_REG_ID, &dev_id ) )
    {
        if ( PROXIMITY22_DEVICE_ID == dev_id )
        {
            return PROXIMITY22_OK;
        }
    }
    return PROXIMITY22_ERROR;
}

err_t proximity22_soft_reset ( proximity22_t *ctx )
{
    return proximity22_write_reg ( ctx, PROXIMITY22_REG_RESET, PROXIMITY22_RESET_ENAB_XRES | 
                                                               PROXIMITY22_RESET_SOFT_RESET );
}

err_t proximity22_clear_fifo ( proximity22_t *ctx )
{
    err_t error_flag = PROXIMITY22_OK;
    uint8_t fifo_control = 0;
    error_flag |= proximity22_read_reg ( ctx, PROXIMITY22_REG_FIFO_CONTROL, &fifo_control );
    fifo_control |= PROXIMITY22_FIFO_CONTROL_FIFO_CLR;
    error_flag |= proximity22_write_reg ( ctx, PROXIMITY22_REG_FIFO_CONTROL, fifo_control );
    return error_flag;
}

err_t proximity22_read_prox ( proximity22_t *ctx, uint16_t *prox )
{
    err_t error_flag = PROXIMITY22_OK;
    uint8_t prox_data[ 2 ] = { 0 };
    error_flag |= proximity22_read_regs ( ctx, PROXIMITY22_REG_PDATA_L, prox_data, 2 );
    if ( PROXIMITY22_OK == error_flag )
    {
        *prox = ( ( uint16_t ) ( prox_data[ 1 ] & 0x3F ) << 8 ) | prox_data[ 0 ];
    }
    return error_flag;
}

err_t proximity22_read_temp ( proximity22_t *ctx, float *temp )
{
    err_t error_flag = PROXIMITY22_OK;
    uint8_t temp_data[ 2 ] = { 0 };
    error_flag |= proximity22_read_regs ( ctx, PROXIMITY22_REG_TDATA_L, temp_data, 2 );
    if ( PROXIMITY22_OK == error_flag )
    {
        *temp = ( PROXIMITY22_TEMP_OFFSET - 
                  ( ( ( uint16_t ) ( temp_data[ 1 ] & 0x03 ) << 8 ) | temp_data[ 0 ] ) ) / PROXIMITY22_TEMP_RES;
    }
    return error_flag;
}

err_t proximity22_read_als ( proximity22_t *ctx, proximity22_als_t *als )
{
    err_t error_flag = PROXIMITY22_OK;
    uint8_t fifo_data[ 8 ] = { 0 };
    uint8_t fifo_status = 0;
    error_flag |= proximity22_read_reg ( ctx, PROXIMITY22_REG_FIFO_STATUS_1, &fifo_status );
    if ( ( PROXIMITY22_OK == error_flag ) && ( fifo_status > 0 ) )
    {
        error_flag |= proximity22_read_regs ( ctx, PROXIMITY22_REG_FIFO_ADATA_7, fifo_data, 8 );
        if ( PROXIMITY22_OK == error_flag )
        {
            als->blue = ( ( uint16_t ) fifo_data[ 1 ] << 8 ) | fifo_data[ 0 ];
            als->green = ( ( uint16_t ) fifo_data[ 3 ] << 8 ) | fifo_data[ 2 ];
            als->red = ( ( uint16_t ) fifo_data[ 5 ] << 8 ) | fifo_data[ 4 ];
            als->clear = ( ( uint16_t ) fifo_data[ 7 ] << 8 ) | fifo_data[ 6 ];
            error_flag |= proximity22_clear_fifo ( ctx );
        }
    }
    else
    {
        error_flag |= PROXIMITY22_ERROR;
    }
    return error_flag;
}

err_t proximity22_read_data ( proximity22_t *ctx, proximity22_data_t *data_out )
{
    err_t error_flag = PROXIMITY22_OK;
    uint8_t status = 0;
    error_flag |= proximity22_read_reg ( ctx, PROXIMITY22_REG_STATUS_3, &status );
    if ( ( PROXIMITY22_OK == error_flag ) && ( status & PROXIMITY22_STATUS_3_AWINT ) )
    {
        error_flag |= proximity22_read_prox ( ctx, &data_out->proximity );
        error_flag |= proximity22_read_temp ( ctx, &data_out->temperature );
        error_flag |= proximity22_read_als ( ctx, &data_out->als );
    }
    else
    {
        error_flag |= PROXIMITY22_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END

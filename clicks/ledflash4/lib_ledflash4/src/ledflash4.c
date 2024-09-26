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
 * @file ledflash4.c
 * @brief LED Flash 4 Click Driver.
 */

#include "ledflash4.h"

void ledflash4_cfg_setup ( ledflash4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->stb = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDFLASH4_DEVICE_ADDRESS_0;
}

err_t ledflash4_init ( ledflash4_t *ctx, ledflash4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->stb, cfg->stb );
    digital_out_low( &ctx->stb );

    return I2C_MASTER_SUCCESS;
}

err_t ledflash4_default_cfg ( ledflash4_t *ctx ) 
{
    err_t error_flag = LEDFLASH4_OK;
    if ( LEDFLASH4_ERROR == ledflash4_check_communication ( ctx ) )
    {
        return LEDFLASH4_ERROR;
    }
    error_flag |= ledflash4_set_led1_current ( ctx, LEDFLASH4_LED_CURRENT_DEFAULT );
    error_flag |= ledflash4_set_led2_current ( ctx, LEDFLASH4_LED_CURRENT_DEFAULT );
    error_flag |= ledflash4_write_reg ( ctx, LEDFLASH4_REG_LOW_VOLTAGE, LEDFLASH4_VIN_LOW_V_RUN_3V | 
                                                                        LEDFLASH4_VIN_LOW_V_3_07V );
    error_flag |= ledflash4_write_reg ( ctx, LEDFLASH4_REG_FLASH_TIMER, LEDFLASH4_FLASH_TIMER_36MS );
    error_flag |= ledflash4_write_reg ( ctx, LEDFLASH4_REG_CONTROL, LEDFLASH4_CONTROL_MODE_FLASH | 
                                                                    LEDFLASH4_CONTROL_OUT_ON | 
                                                                    LEDFLASH4_CONTROL_AUTO_STROBE_ON | 
                                                                    LEDFLASH4_CONTROL_STROBE_TYPE_LEVEL | 
                                                                    LEDFLASH4_CONTROL_STROBE_INPUT_ON );
    error_flag |= ledflash4_write_reg ( ctx, LEDFLASH4_REG_PWM_AND_INDICATOR, LEDFLASH4_PWM_INCT_1_OF_16_DC );
    return error_flag;
}

err_t ledflash4_generic_write ( ledflash4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ledflash4_generic_read ( ledflash4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ledflash4_write_reg ( ledflash4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ledflash4_generic_write( ctx, reg, &data_in, 1 );
}

err_t ledflash4_read_reg ( ledflash4_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void ledflash4_set_stb_pin ( ledflash4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->stb, state );
}

err_t ledflash4_check_communication ( ledflash4_t *ctx )
{
    uint8_t device_id = 0;
    if ( LEDFLASH4_OK == ledflash4_read_reg ( ctx, LEDFLASH4_REG_CHIP_ID, &device_id ) )
    {
        if ( LEDFLASH4_DEVICE_ID == ( device_id & LEDFLASH4_DEVICE_ID_MASK ) )
        {
            return LEDFLASH4_OK;
        }
    }
    return LEDFLASH4_ERROR;
}

err_t ledflash4_set_led1_current ( ledflash4_t *ctx, uint16_t led_current )
{
    if ( led_current > LEDFLASH4_LED_CURRENT_MAX )
    {
        LEDFLASH4_ERROR;
    }
    uint8_t reg_data = ( uint8_t ) ( ( float ) led_current / LEDFLASH4_LED_CURRENT_MAX * 
                                               LEDFLASH4_LED_CURRENT_REG_MASK + 
                                               LEDFLASH4_LED_CURRENT_ROUND_INT );
    return ledflash4_write_reg ( ctx, LEDFLASH4_REG_CURRENT_SET_LED1, reg_data );
}

err_t ledflash4_set_led2_current ( ledflash4_t *ctx, uint16_t led_current )
{
    if ( led_current > LEDFLASH4_LED_CURRENT_MAX )
    {
        LEDFLASH4_ERROR;
    }
    uint8_t reg_data = ( uint8_t ) ( ( float ) led_current / LEDFLASH4_LED_CURRENT_MAX * 
                                               LEDFLASH4_LED_CURRENT_REG_MASK + 
                                               LEDFLASH4_LED_CURRENT_ROUND_INT );
    return ledflash4_write_reg ( ctx, LEDFLASH4_REG_CURRENT_SET_LED2, reg_data );
}

// ------------------------------------------------------------------------- END

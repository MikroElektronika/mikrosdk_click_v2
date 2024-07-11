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
 * @file c1x4rgb.c
 * @brief 1x4 RGB Click Driver.
 */

#include "c1x4rgb.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                   0x00
#define REG_BITMASK             0x03
#define DEMO_COLOR_INT_OFF      0x00
#define DEMO_COLOR_INT_MAX      0xFF 

void c1x4rgb_cfg_setup ( c1x4rgb_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->syc = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C1X4RGB_DEVICE_ADDRESS_BCST;
}

err_t c1x4rgb_init ( c1x4rgb_t *ctx, c1x4rgb_cfg_t *cfg ) 
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

    digital_out_init( &ctx->syc, cfg->syc );

    return I2C_MASTER_SUCCESS;
}

err_t c1x4rgb_default_cfg ( c1x4rgb_t *ctx ) 
{
    c1x4rgb_set_sync( ctx, C1X4RGB_SYC_STATE_LOW );
    err_t err_flag = c1x4rgb_chip_enable( ctx );
    Delay_10ms( );

    err_flag |= c1x4rgb_set_tmc_mode( ctx , C1X4RGB_REG_DEV_CFG_1, C1X4RGB_TCM_MODE_SCAN_4 );
    Delay_10ms( );

    err_flag |= c1x4rgb_set_lsd_thold( ctx, C1X4RGB_LSD_DET_DEFAULT );
    Delay_10ms( );

    err_flag |= c1x4rgb_set_command( ctx, C1X4RGB_SET_CMD_UPDATE );
    Delay_10ms( );

    err_flag |= c1x4rgb_enable_leds( ctx, C1X4RGB_ENABLE_ALL_LEDS );
    Delay_10ms( );

    err_flag |= c1x4rgb_set_leds_illuminate( ctx, C1X4RGB_DUTY_CYCLE_10 );
    Delay_10ms( );

    c1x4rgb_led_t led_cfg;
    led_cfg.led_0.red = DEMO_COLOR_INT_MAX;
    led_cfg.led_0.green = DEMO_COLOR_INT_OFF;
    led_cfg.led_0.blue = DEMO_COLOR_INT_OFF;

    led_cfg.led_1.red = DEMO_COLOR_INT_OFF;
    led_cfg.led_1.green = DEMO_COLOR_INT_MAX;
    led_cfg.led_1.blue = DEMO_COLOR_INT_OFF;

    led_cfg.led_2.red = DEMO_COLOR_INT_OFF;
    led_cfg.led_2.green = DEMO_COLOR_INT_OFF;
    led_cfg.led_2.blue = DEMO_COLOR_INT_MAX;

    led_cfg.led_3.red = DEMO_COLOR_INT_MAX;
    led_cfg.led_3.green = DEMO_COLOR_INT_MAX;
    led_cfg.led_3.blue = DEMO_COLOR_INT_MAX;
    err_flag |= c1x4rgb_cfg_rgb_color( ctx, led_cfg );
    Delay_10ms( );

    return err_flag;
}

err_t c1x4rgb_generic_write ( c1x4rgb_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    ctx->slave_address &= ~REG_BITMASK;
    ctx->slave_address |= ( uint8_t ) ( ( reg >> 9 ) & REG_BITMASK );
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    err_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    return err_flag;
}

err_t c1x4rgb_generic_read ( c1x4rgb_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) reg;
    ctx->slave_address &= ~REG_BITMASK;
    ctx->slave_address |= ( uint8_t ) ( ( reg >> 9 ) & REG_BITMASK );
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    err_flag |= i2c_master_write_then_read( &ctx->i2c, data_buf, 1, data_out, len );
    return err_flag;
}

err_t c1x4rgb_reg_write ( c1x4rgb_t *ctx, uint16_t reg, uint8_t data_in ) 
{
    return c1x4rgb_generic_write( ctx, reg, &data_in, 1 );
}

err_t c1x4rgb_reg_read ( c1x4rgb_t *ctx, uint16_t reg, uint8_t *data_out ) 
{
    return c1x4rgb_generic_read( ctx, reg, data_out, 1 );
}

err_t c1x4rgb_chip_enable ( c1x4rgb_t *ctx ) 
{
    return c1x4rgb_reg_write( ctx, C1X4RGB_REG_CHIP_EN, C1X4RGB_CHIP_ENABLE );
}

err_t c1x4rgb_set_tmc_mode ( c1x4rgb_t *ctx, uint8_t dev_cfg, uint8_t mode ) 
{
    err_t err_flag = C1X4RGB_ERROR;
    if ( ( C1X4RGB_REG_DEV_CFG_0 <= dev_cfg ) && ( C1X4RGB_REG_DEV_CFG_12 > dev_cfg ) )
    {
        err_flag = c1x4rgb_reg_write( ctx, dev_cfg, mode );
    }
    return err_flag;
}

err_t c1x4rgb_set_lsd_thold ( c1x4rgb_t *ctx, uint8_t lsd_thold ) 
{
    return c1x4rgb_reg_write( ctx, C1X4RGB_REG_DEV_CFG_12, lsd_thold );
}

err_t c1x4rgb_set_command ( c1x4rgb_t *ctx, uint8_t command ) 
{
    err_t err_flag = C1X4RGB_ERROR;
    if ( C1X4RGB_SET_CMD_PAUSE >= command )
    {
        err_flag = c1x4rgb_reg_write( ctx, C1X4RGB_REG_CMD_UPDATE + command, C1X4RGB_CMD_ENABLE );
    }
    return err_flag;
}

err_t c1x4rgb_get_tsd_cfg_status ( c1x4rgb_t *ctx, uint8_t *status ) 
{
    return c1x4rgb_reg_read( ctx, C1X4RGB_REG_STATUS_TSD, status );
}

err_t c1x4rgb_enable_leds ( c1x4rgb_t *ctx, uint16_t led_bitmask ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( led_bitmask & C1X4RGB_LED_ENABLE_BITMASK ) >> 4 );
    data_buf[ 1 ] = ( uint8_t )   led_bitmask;
    return c1x4rgb_generic_write( ctx, C1X4RGB_REG_LED_EN_1, data_buf, 2 );
}

err_t c1x4rgb_set_leds_illuminate ( c1x4rgb_t *ctx, float duty_cycle ) 
{
    err_t err_flag = C1X4RGB_OK;
    if ( C1X4RGB_DUTY_CYCLE_100 > duty_cycle )
    {
        duty_cycle *= C1X4RGB_DUTY_CYCLE_CALC_FACT;
        for ( uint16_t reg = C1X4RGB_REG_MANUAL_PWM_L0_G; reg <= C1X4RGB_REG_MANUAL_PWM_L3_B; reg++ )
        {
            err_flag |= c1x4rgb_reg_write( ctx, reg, ( uint8_t ) duty_cycle );
        }
    }
    else
    {
        err_flag = C1X4RGB_ERROR;
    }
    return err_flag;
}

err_t c1x4rgb_set_led_illuminate ( c1x4rgb_t *ctx, uint8_t n_led, float duty_cycle ) 
{
    err_t err_flag = C1X4RGB_OK;
    if ( ( C1X4RGB_DUTY_CYCLE_100 > duty_cycle ) && ( C1X4RGB_NUM_LED_11 >= n_led ) )
    {
        duty_cycle *= C1X4RGB_DUTY_CYCLE_CALC_FACT;
        err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_PWM_L0_G + n_led, ( uint8_t ) duty_cycle );
    }
    else
    {
        err_flag = C1X4RGB_ERROR;
    }
    return err_flag;
}

err_t c1x4rgb_set_rgb_color ( c1x4rgb_t *ctx, uint8_t led_pos, uint8_t red, uint8_t green, uint8_t blue ) 
{
    err_t err_flag = C1X4RGB_ERROR;
    if ( C1X4RGB_LED_POS_LD4 >= led_pos )
    {
        led_pos *= C1X4RGB_LED_POS_LD4;
        err_flag = c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L0_G + led_pos, green );
        err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L0_R + led_pos, red );
        err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L0_B + led_pos, blue );
    }
    return err_flag;
}

err_t c1x4rgb_cfg_rgb_color ( c1x4rgb_t *ctx, c1x4rgb_led_t led_cfg ) 
{
    err_t err_flag = c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L0_G, led_cfg.led_0.green );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L0_R, led_cfg.led_0.red   );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L0_B, led_cfg.led_0.blue  );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L1_G, led_cfg.led_1.green );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L1_R, led_cfg.led_1.red   );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L1_B, led_cfg.led_1.blue  );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L2_G, led_cfg.led_2.green );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L2_R, led_cfg.led_2.red   );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L2_B, led_cfg.led_2.blue  );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L3_G, led_cfg.led_3.green );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L3_R, led_cfg.led_3.red   );
    err_flag |= c1x4rgb_reg_write( ctx, C1X4RGB_REG_MANUAL_L3_B, led_cfg.led_3.blue  );
    return err_flag;
}

void c1x4rgb_set_sync ( c1x4rgb_t *ctx, uint8_t sync ) 
{
    digital_out_write( &ctx->syc, sync );
}

// ------------------------------------------------------------------------- END

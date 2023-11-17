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
 * @file c2x2rgb.c
 * @brief 2x2 RGB Click Driver.
 */

#include "c2x2rgb.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                    0x00

void c2x2rgb_cfg_setup ( c2x2rgb_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C2X2RGB_DEVICE_ADDRESS;
}

err_t c2x2rgb_init ( c2x2rgb_t *ctx, c2x2rgb_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t c2x2rgb_default_cfg ( c2x2rgb_t *ctx ) 
{
    uint8_t vendor_id = DUMMY, device_id = DUMMY;
    err_t err_flag = c2x2rgb_get_device_id( ctx, &vendor_id, &device_id );
    if ( ( C2X2RGB_VEN_ID == vendor_id ) && ( C2X2RGB_DEV_ID == device_id ) )
    {
        err_flag |= c2x2rgb_sw_reset( ctx );
        Delay_10ms( );
        
        c2x2rgb_set_rgb_led( ctx, C2X2RGB_SET_LD1, C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF );
        c2x2rgb_set_rgb_led( ctx, C2X2RGB_SET_LD2, C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF );
        c2x2rgb_set_rgb_led( ctx, C2X2RGB_SET_LD3, C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF );
        c2x2rgb_set_rgb_led( ctx, C2X2RGB_SET_LD4, C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                   C2X2RGB_LED_CURRENT_OFF );
        Delay_10ms( );
        
        err_flag |= c2x2rgb_set_control( ctx, C2X2RGB_EN_MODE_SHUTDOWN, 
                                              C2X2RGB_BE_DISABLE, 
                                              C2X2RGB_CE_TEMP_135C, 
                                              C2X2RGB_FADE_RATE0_32_MS );
        Delay_10ms( );
    }
    return err_flag;
}

err_t c2x2rgb_generic_write ( c2x2rgb_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t c2x2rgb_generic_read ( c2x2rgb_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t c2x2rgb_get_device_id ( c2x2rgb_t *ctx, uint8_t *vendor_id, uint8_t *device_id ) 
{
    err_t err_flag = c2x2rgb_generic_read( ctx, C2X2RGB_REG_ID, vendor_id );
    *device_id = *vendor_id & C2X2RGB_DEV_ID_BIT_MASK;
    *vendor_id >>= 5;
    *vendor_id &= C2X2RGB_VEN_ID_BIT_MASK;
    return err_flag;
}

err_t c2x2rgb_get_monitor_status ( c2x2rgb_t *ctx, uint8_t *sc_stat, uint8_t *be_stat, 
                                               uint8_t *cool_stat, uint8_t *uv_ot_stat ) 
{
    err_t err_flag = c2x2rgb_generic_read( ctx, C2X2RGB_REG_MONITOR, sc_stat );
    *uv_ot_stat = *sc_stat & C2X2RGB_MONITOR_UV_OT_STAT;
    *cool_stat = ( *sc_stat & C2X2RGB_MONITOR_COOL_STAT ) >> 1;
    *be_stat = ( *be_stat & C2X2RGB_MONITOR_BE_STAT ) >> 2;
    *sc_stat &= C2X2RGB_MONITOR_SC_STAT;
    *sc_stat >>= 3;
    return err_flag;
}

err_t c2x2rgb_set_control ( c2x2rgb_t *ctx, uint8_t en_mode, uint8_t be_en, 
                                            uint8_t ce_temp, uint8_t fade_rate ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = c2x2rgb_generic_read( ctx, C2X2RGB_REG_CONTROL, &data_buf );
    data_buf &= ~C2X2RGB_EN_MODE_BIT_MASK;
    data_buf |= ( en_mode & C2X2RGB_EN_MODE_SW_RESET ) << 6;
    data_buf &= ~C2X2RGB_BE_BIT_MASK;
    data_buf |= ( be_en & C2X2RGB_BE_ENABLE ) << 5;
    data_buf &= ~C2X2RGB_CE_TEMP_BIT_MASK;
    data_buf |= ( ce_temp & C2X2RGB_CE_TEMP_90C ) << 3;
    data_buf &= ~C2X2RGB_FADE_RATE0_BIT_MASK;
    data_buf |= fade_rate & C2X2RGB_FADE_RATE0_4_S;
    err_flag = c2x2rgb_generic_write( ctx, C2X2RGB_REG_CONTROL, data_buf );
    return err_flag;
}

err_t c2x2rgb_set_normal_mode ( c2x2rgb_t *ctx ) 
{
    return c2x2rgb_set_control( ctx, C2X2RGB_EN_MODE_NORMAL, 
                                     C2X2RGB_BE_DISABLE, 
                                     C2X2RGB_CE_TEMP_135C, 
                                     C2X2RGB_FADE_RATE0_32_MS );
}

err_t c2x2rgb_sw_reset ( c2x2rgb_t *ctx ) 
{
    return c2x2rgb_set_control( ctx, C2X2RGB_EN_MODE_SW_RESET, 
                                     C2X2RGB_BE_DISABLE, 
                                     C2X2RGB_CE_TEMP_135C, 
                                     C2X2RGB_FADE_RATE0_32_MS );
}

err_t c2x2rgb_set_rgb_led ( c2x2rgb_t *ctx, uint8_t led_num, uint16_t ired, uint16_t igrn, uint16_t iblu )
{
    err_t err_flag = C2X2RGB_ERROR;
    if ( ( C2X2RGB_SET_LD4 >= led_num  ) && ( C2X2RGB_SET_LD1 <= led_num ) && 
         ( C2X2RGB_LED_CURRENT_MAX >= ired ) && 
         ( C2X2RGB_LED_CURRENT_MAX >= igrn ) && 
         ( C2X2RGB_LED_CURRENT_MAX >= iblu ) )
    {
        led_num--;
        led_num *= 3;
        ired /= C2X2RGB_LED_CURRENT_STEP;
        igrn /= C2X2RGB_LED_CURRENT_STEP;
        iblu /= C2X2RGB_LED_CURRENT_STEP;
        err_flag = c2x2rgb_generic_write( ctx, C2X2RGB_REG_IRED1 + led_num, ( uint8_t )  ired );
        err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IGRN1 + led_num, ( uint8_t ) igrn );
        err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IBLU1 + led_num, ( uint8_t ) iblu );
    }
    err_flag |= c2x2rgb_set_normal_mode( ctx );
    return err_flag;
}

err_t c2x2rgb_set_all_rgb_led ( c2x2rgb_t *ctx, c2x2rgb_rgb_led_t cfg_rgb_led )
{
    err_t err_flag = c2x2rgb_sw_reset( ctx );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IRED1, 
                                           ( uint8_t ) ( cfg_rgb_led.led1_ired / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IGRN1, 
                                           ( uint8_t ) ( cfg_rgb_led.led1_igrn / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IBLU1, 
                                           ( uint8_t ) ( cfg_rgb_led.led1_iblu / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IRED2, 
                                           ( uint8_t ) ( cfg_rgb_led.led2_ired / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IGRN2, 
                                           ( uint8_t ) ( cfg_rgb_led.led2_igrn / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IBLU2, 
                                           ( uint8_t ) ( cfg_rgb_led.led2_iblu / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IRED3, 
                                           ( uint8_t ) ( cfg_rgb_led.led3_ired / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IGRN3, 
                                           ( uint8_t ) ( cfg_rgb_led.led3_igrn / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IBLU3, 
                                           ( uint8_t ) ( cfg_rgb_led.led3_iblu / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IRED4, 
                                           ( uint8_t ) ( cfg_rgb_led.led4_ired / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IGRN4, 
                                           ( uint8_t ) ( cfg_rgb_led.led4_igrn / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_generic_write( ctx, C2X2RGB_REG_IBLU4, 
                                           ( uint8_t ) ( cfg_rgb_led.led4_iblu / C2X2RGB_LED_CURRENT_STEP ) );
    err_flag |= c2x2rgb_set_control( ctx, cfg_rgb_led.en_mode & C2X2RGB_EN_MODE_SW_RESET, C2X2RGB_BE_DISABLE, 
                                          C2X2RGB_CE_TEMP_135C, C2X2RGB_FADE_RATE0_32_MS );
    return err_flag;
}

err_t c2x2rgb_set_pg_ctrl ( c2x2rgb_t *ctx, uint8_t pg_mode, uint8_t pg_time, uint8_t fade_rate )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = c2x2rgb_generic_read( ctx, C2X2RGB_REG_PG_CNTL, &data_buf );
    data_buf &= ~C2X2RGB_PG_MODE_BIT_MASK;
    data_buf |= ( pg_mode & C2X2RGB_PG_MODE_8P_EN ) << 6;
    data_buf &= ~C2X2RGB_PG_TIME_BIT_MASK;
    data_buf |= ( pg_time & C2X2RGB_PG_TIME_2_S ) << 3;
    data_buf &= ~C2X2RGB_FADE_RATE1_BIT_MASK;
    data_buf |= fade_rate & C2X2RGB_FADE_RATE1_4_S;
    err_flag = c2x2rgb_generic_write( ctx, C2X2RGB_REG_PG_CNTL, data_buf );
    return err_flag;
}

err_t c2x2rgb_set_pg_fade ( c2x2rgb_t *ctx, uint8_t pg_fade )
{
    return c2x2rgb_generic_write( ctx, C2X2RGB_REG_PG_FADE, pg_fade );
}

err_t c2x2rgb_set_pg_rgb ( c2x2rgb_t *ctx, uint8_t led_num, uint8_t pg_rgb )
{
    err_t err_flag = C2X2RGB_ERROR;
    if ( ( C2X2RGB_SET_LD4 >= led_num  ) && ( C2X2RGB_SET_LD1 <= led_num ) )
    {
        led_num--;
        err_flag = c2x2rgb_generic_write( ctx, C2X2RGB_REG_PG_RGB1 + led_num, pg_rgb );
    }
    return err_flag;
}

err_t c2x2rgb_set_pg_wd ( c2x2rgb_t *ctx, uint8_t wd_pcr )
{
    return c2x2rgb_generic_write( ctx, C2X2RGB_REG_PG_WD, wd_pcr );
}

// ------------------------------------------------------------------------- END

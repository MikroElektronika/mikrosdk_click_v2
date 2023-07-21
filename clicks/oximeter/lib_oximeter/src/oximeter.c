/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "oximeter.h"
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oximeter_cfg_setup ( oximeter_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->io0 = HAL_PIN_NC;
    cfg->io1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = OXIMETER_DEVICE_ADDRESS;

    cfg->dev_enabled_chann = OXIMETER_ALL_CHANN_EN;
    cfg->dev_enabled_slot_a = OXIMETER_DIS_SLOT;
    cfg->dev_enabled_slot_b = OXIMETER_DIS_SLOT;
}

err_t oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg )
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

    digital_in_init( &ctx->io0, cfg->io0 );
    digital_in_init( &ctx->io1, cfg->io1 );

    ctx->enabled_chann = cfg->dev_enabled_chann;
    ctx->enabled_slot_a = cfg->dev_enabled_slot_a;
    ctx->enabled_slot_b = cfg->dev_enabled_slot_b;

    return OXIMETER_OK;
}

void oximeter_default_cfg ( oximeter_t *ctx )
{
    oximeter_enable_t tmp;
    oximeter_reset( ctx );
    Delay_100ms ( );
    oximeter_write_reg( ctx, OXIMETER_REG_SAMPLE_CLK, 0x0080 );
    oximeter_set_mode( ctx, OXIMETER_DEV_PROGRAM_OP_MODE );

    tmp.enable_slot = OXIMETER_EN_SLOT;
    tmp.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    tmp.enable_led = OXIMETER_LEDX2_EN;
    oximeter_set_time_slot_a( ctx, &tmp, OXIMETER_SLOT_NORM_OP_MODE );

    tmp.enable_slot = OXIMETER_DIS_SLOT;
    tmp.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    tmp.enable_led = OXIMETER_LEDX1_EN;
    oximeter_set_time_slot_b( ctx, &tmp, OXIMETER_SLOT_NORM_OP_MODE );

    oximeter_enable_channels( ctx, OXIMETER_ALL_CHANN_EN );
    oximeter_write_reg( ctx, OXIMETER_REG_STATUS, 0xFFFF );
    oximeter_write_reg( ctx, OXIMETER_REG_DATA_ACCESS_CTL, 0x0000 );
    oximeter_set_mode( ctx, OXIMETER_DEV_NORMAL_OP_MODE );
}

err_t oximeter_write_reg ( oximeter_t* ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t buff_data[ 3 ] = { 0 };

    if ( reg > 0x7F )
    {
        return OXIMETER_ERROR;
    }
    buff_data[ 0 ] = reg;
    buff_data[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    buff_data[ 2 ] = ( uint8_t ) ( data_in & 0xFF );

    i2c_master_write( &ctx->i2c, buff_data, 3 ); 

    return OXIMETER_OK;
}

err_t oximeter_read_reg ( oximeter_t* ctx, uint8_t reg, uint16_t* data_out, uint8_t len )
{
    uint8_t buff_data[ 256 ] = { 0 };

    if ( ( reg > 0x7F ) || ( len > 128 ) )
    {
        return OXIMETER_ERROR;
    }

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, buff_data, len * 2 );

    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_out[ cnt ] = ( ( uint16_t ) buff_data[ cnt * 2 ] << 8 ) | buff_data[ cnt * 2 + 1 ];
    }

    return OXIMETER_OK;
}

err_t oximeter_set_time_slot_a ( oximeter_t* ctx, oximeter_enable_t* dev_enable, uint8_t set_mode )
{
    uint16_t tmp = 0;
    uint16_t led_set = 0;

    if ( dev_enable->enable_slot )
    {
        oximeter_read_reg( ctx, OXIMETER_REG_SLOT_EN, &tmp, 1 );
        tmp |= 0x0001;
        oximeter_write_reg( ctx, OXIMETER_REG_SLOT_EN, tmp );
        oximeter_read_reg( ctx, OXIMETER_REG_PD_LED_SELECT, &tmp, 1 );
        oximeter_read_reg( ctx, OXIMETER_REG_LED_DISABLE, &led_set, 1 );

        switch ( dev_enable->enable_photodiode )
        {
            case OXIMETER_NO_PHOTODIODE_CONN:
            {
                tmp &= 0xFF0F;
                break;
            }
            case OXIMETER_ALL_PHOTODIODE_CONN:
            {
                tmp &= 0xFF0F;
                tmp |= 0x0010;
                break;
            }
            case OXIMETER_PD5_PD6_PD7_PD8_CONN:
            {
                tmp &= 0xFF0F;
                tmp |= 0x0040;
                break;
            }
            case OXIMETER_PD1_PD2_PD3_PD4_CONN:
            {
                tmp &= 0xFF0F;
                tmp |= 0x0050;
                break;
            }
            default:
            {
                return OXIMETER_ERROR;
            }
        }

        switch ( dev_enable->enable_led )
        {
            case OXIMETER_PDX_TO_AFE:
            {
                tmp &= 0xFFFC;
                led_set &= 0xFEFF;
                break;
            }
            case OXIMETER_LEDX1_EN:
            {
                tmp &= 0xFFFC;
                tmp |= 0x0001;
                led_set &= 0xFEFF;
                break;
            }
            case OXIMETER_LEDX2_EN:
            {
                tmp &= 0xFFFC;
                tmp |= 0x0002;
                led_set &= 0xFEFF;
                break;
            }
            case OXIMETER_LEDX3_EN:
            {
                tmp &= 0xFFFC;
                tmp |= 0x0003;
                led_set &= 0xFEFF;
                break;
            }
            case OXIMETER_DIS_LED:
            {
                led_set |= 0x0100;
                break;
            }
            default:
            {
                return OXIMETER_ERROR;
            }
        }

        oximeter_write_reg( ctx, OXIMETER_REG_PD_LED_SELECT, tmp );
        oximeter_write_reg( ctx, OXIMETER_REG_LED_DISABLE, led_set );
        oximeter_read_reg( ctx, OXIMETER_REG_DIGITAL_INT_EN, &tmp, 1 );
        if ( set_mode )
        {
            tmp |= 0x1000;
        }
        else
        {
            tmp &= 0xEFFF;
        }
        oximeter_write_reg( ctx, OXIMETER_REG_DIGITAL_INT_EN, tmp );
        oximeter_read_reg( ctx, OXIMETER_REG_INT_MASK, &tmp, 1 );
        tmp &= 0xFFDF;
        oximeter_write_reg( ctx, OXIMETER_REG_INT_MASK, tmp );
    }
    else
    {
        oximeter_read_reg( ctx, OXIMETER_REG_SLOT_EN, &tmp, 1 );
        tmp &= 0xFFFE;
        oximeter_write_reg( ctx, OXIMETER_REG_SLOT_EN, tmp );
        oximeter_read_reg( ctx, OXIMETER_REG_INT_MASK, &tmp, 1 );
        tmp |= 0x0020;
        oximeter_write_reg( ctx, OXIMETER_REG_INT_MASK, tmp );
    }
    ctx->enabled_slot_a = dev_enable->enable_slot;

    return OXIMETER_OK;
}

err_t oximeter_set_time_slot_b ( oximeter_t* ctx, oximeter_enable_t* dev_enable, uint8_t set_mode )
{
    uint16_t tmp = 0;
    uint16_t led_set = 0;

    if ( dev_enable->enable_slot )
    {
        oximeter_read_reg( ctx, OXIMETER_REG_SLOT_EN, &tmp, 1 );
        tmp |= 0x0020;
        oximeter_write_reg( ctx, OXIMETER_REG_SLOT_EN, tmp );
        oximeter_read_reg( ctx, OXIMETER_REG_PD_LED_SELECT, &tmp, 1 );
        oximeter_read_reg( ctx, OXIMETER_REG_LED_DISABLE, &led_set, 1 );

        switch ( dev_enable->enable_photodiode )
        {
            case OXIMETER_NO_PHOTODIODE_CONN:
            {
                tmp &= 0xF0FF;
                break;
            }
            case OXIMETER_ALL_PHOTODIODE_CONN:
            {
                tmp &= 0xF0FF;
                tmp |= 0x0100;
                break;
            }
            case OXIMETER_PD5_PD6_PD7_PD8_CONN:
            {
                tmp &= 0xF0FF;
                tmp |= 0x0400;
                break;
            }
            case OXIMETER_PD1_PD2_PD3_PD4_CONN:
            {
                tmp &= 0xF0FF;
                tmp |= 0x0500;
                break;
            }
            default:
            {
                return OXIMETER_ERROR;
            }
        }

        switch ( dev_enable->enable_led )
        {
            case OXIMETER_PDX_TO_AFE:
            {
                tmp &= 0xFFF3;
                led_set &= 0xFDFF;
                break;
            }
            case OXIMETER_LEDX1_EN:
            {
                tmp &= 0xFFF3;
                tmp |= 0x0004;
                led_set &= 0xFDFF;
                break;
            }
            case OXIMETER_LEDX2_EN:
            {
                tmp &= 0xFFF3;
                tmp |= 0x0008;
                led_set &= 0xFDFF;
                break;
            }
            case OXIMETER_LEDX3_EN:
            {
                tmp &= 0xFFF3;
                tmp |= 0x000C;
                led_set &= 0xFDFF;
                break;
            }
            case OXIMETER_DIS_LED:
            {
                led_set |= 0x0200;
                break;
            }
            default:
            {
                return OXIMETER_ERROR;
            }
        }

        oximeter_write_reg( ctx, OXIMETER_REG_PD_LED_SELECT, tmp );
        oximeter_write_reg( ctx, OXIMETER_REG_LED_DISABLE, led_set );
        oximeter_read_reg( ctx, OXIMETER_REG_DIGITAL_INT_EN, &tmp, 1 );
        if ( set_mode )
        {
            tmp |= 0x2000;
        }
        else
        {
            tmp &= 0xDFFF;
        }
        oximeter_write_reg( ctx, OXIMETER_REG_DIGITAL_INT_EN, tmp );
        oximeter_read_reg( ctx, OXIMETER_REG_INT_MASK, &tmp, 1 );
        tmp &= 0xFFBF;
        oximeter_write_reg( ctx, OXIMETER_REG_INT_MASK, tmp );
    }
    else
    {
        oximeter_read_reg( ctx, OXIMETER_REG_SLOT_EN, &tmp, 1 );
        tmp &= 0xFFDF;
        oximeter_write_reg( ctx, OXIMETER_REG_SLOT_EN, tmp );
        oximeter_read_reg( ctx, OXIMETER_REG_INT_MASK, &tmp, 1 );
        tmp |= 0x0040;
        oximeter_write_reg( ctx, OXIMETER_REG_INT_MASK, tmp );
    }
    ctx->enabled_slot_b = dev_enable->enable_slot;

    return OXIMETER_OK;
}

err_t oximeter_enable_channels ( oximeter_t* ctx, uint8_t select_channel )
{
    uint16_t pom1 = 0;
    uint16_t pom2 = 0;

    oximeter_read_reg( ctx, OXIMETER_REG_AFE_PWR_CFG1, &pom1, 1 );
    oximeter_read_reg( ctx, OXIMETER_REG_ALT_PWR_DN, &pom2, 1 );

    switch ( select_channel )
    {
        case OXIMETER_CH1_EN:
        {
            pom1 |= 0x01C0;
            pom1 &= 0xFFC7;
            break;
        }
        case OXIMETER_CH2_EN:
        {
            pom1 &= 0xFE3F;
            pom1 |= 0x0038;
            pom2 |= 0xE000;
            pom2 &= 0xE3FF;
            break;
        }
        case OXIMETER_CH1_CH2_EN:
        {
            pom1 &= 0xFE3F;
            pom1 &= 0xFFC7;
            pom2 |= 0xE000;
            pom2 &= 0xE3FF;
            break;
        }
        case OXIMETER_CH3_CH4_EN:
        {
            pom1 &= 0xFE3F;
            pom1 |= 0x0038;
            pom2 &= 0x1FFF;
            pom2 |= 0x1C00;
            break;
        }
        case OXIMETER_CH2_CH3_CH4_EN:
        {
            pom1 &= 0xFE3F;
            pom1 |= 0x0038;
            pom2 &= 0x1FFF;
            pom2 &= 0xE3FF;
            break;
        }
        case OXIMETER_ALL_CHANN_EN:
        {
            pom1 &= 0xFE3F;
            pom1 &= 0xFFC7;
            pom2 &= 0x1FFF;
            pom2 &= 0xE3FF;
            break;
        }
        default:
        {
            return OXIMETER_ERROR;
        }
    }
    oximeter_write_reg( ctx, OXIMETER_REG_AFE_PWR_CFG1, pom1 );
    oximeter_write_reg( ctx, OXIMETER_REG_ALT_PWR_DN, pom2 );
    ctx->enabled_chann = select_channel;

    return OXIMETER_OK;
}

void oximeter_read_data ( oximeter_t* ctx, uint32_t* chann_results, uint8_t result_mode )
{
    uint16_t chann_data[ 4 ] = { 0 };
    uint16_t chann_data_high[ 4 ] = { 0 };
    uint16_t interr_check = { 0 };
    uint32_t tmp = 0;
    uint8_t reg_addr0 = 0;
    uint8_t reg_addr1 = 0;
    uint8_t reg_addr2 = 0;

    oximeter_read_reg( ctx, OXIMETER_REG_STATUS, &interr_check, 1 );
    while ( !( interr_check & 0x0060 ) )
    oximeter_read_reg( ctx, OXIMETER_REG_STATUS, &interr_check, 1 );
    oximeter_write_reg( ctx, OXIMETER_REG_STATUS, 0xFFFF );
    oximeter_write_reg( ctx, OXIMETER_REG_DATA_ACCESS_CTL, 0x0006 );

    if ( !result_mode )
    {
        if ( ctx->enabled_slot_a != OXIMETER_DIS_SLOT )
        {
            reg_addr0 = OXIMETER_REG_SLOTA_PD1_16BIT;
            reg_addr1 = OXIMETER_REG_SLOTA_PD2_16BIT;
            reg_addr2 = OXIMETER_REG_SLOTA_PD3_16BIT;
        }
        if ( ctx->enabled_slot_b != OXIMETER_DIS_SLOT )
        {
            reg_addr0 = OXIMETER_REG_SLOTB_PD1_16BIT;
            reg_addr1 = OXIMETER_REG_SLOTB_PD2_16BIT;
            reg_addr2 = OXIMETER_REG_SLOTB_PD3_16BIT;
        }
        if ( ( OXIMETER_DIS_SLOT != ctx->enabled_slot_a ) || ( OXIMETER_DIS_SLOT != ctx->enabled_slot_b ) )
        {
            switch ( ctx->enabled_chann )
            {
                case OXIMETER_CH1_EN:
                {
                    oximeter_read_reg( ctx, reg_addr0, chann_data, 1 );
                    chann_results[ 0 ] = chann_data[ 0 ] & 0x0000FFFF;
                    break;
                }
                case OXIMETER_CH2_EN:
                {
                    oximeter_read_reg( ctx, reg_addr1, chann_data, 1 );
                    chann_results[ 1 ] = chann_data[ 0 ] & 0x0000FFFF;
                    break;
                }
                case OXIMETER_CH1_CH2_EN:
                {
                    oximeter_read_reg( ctx, reg_addr0, chann_data, 2 );
                    chann_results[ 0 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 1 ] = chann_data[ 1 ] & 0x0000FFFF;
                    break;
                }
                case OXIMETER_CH3_CH4_EN:
                {
                    oximeter_read_reg( ctx, reg_addr2, chann_data, 2 );
                    chann_results[ 2 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 3 ] = chann_data[ 1 ] & 0x0000FFFF;
                    break;
                }
                case OXIMETER_CH2_CH3_CH4_EN:
                {
                    oximeter_read_reg( ctx, reg_addr1, chann_data, 3 );
                    chann_results[ 1 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 2 ] = chann_data[ 1 ] & 0x0000FFFF;
                    chann_results[ 3 ] = chann_data[ 2 ] & 0x0000FFFF;
                    break;
                }
                case OXIMETER_ALL_CHANN_EN:
                {
                    oximeter_read_reg( ctx, reg_addr0, chann_data, 4 );
                    chann_results[ 0 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 1 ] = chann_data[ 1 ] & 0x0000FFFF;
                    chann_results[ 2 ] = chann_data[ 2 ] & 0x0000FFFF;
                    chann_results[ 3 ] = chann_data[ 3 ] & 0x0000FFFF;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    else
    {
        if ( OXIMETER_DIS_SLOT != ctx->enabled_slot_a )
        {
            reg_addr0 = OXIMETER_REG_A_PD1_LOW;
            reg_addr1 = OXIMETER_REG_A_PD2_LOW;
            reg_addr2 = OXIMETER_REG_A_PD3_LOW;
        }
        if ( OXIMETER_DIS_SLOT != ctx->enabled_slot_b )
        {
            reg_addr0 = OXIMETER_REG_B_PD1_LOW;
            reg_addr1 = OXIMETER_REG_B_PD2_LOW;
            reg_addr2 = OXIMETER_REG_B_PD3_LOW;
        }
        if ( ( OXIMETER_DIS_SLOT != ctx->enabled_slot_a ) || ( OXIMETER_DIS_SLOT != ctx->enabled_slot_b ) )
        {
            switch ( ctx->enabled_chann )
            {
                case OXIMETER_CH1_EN:
                {
                    oximeter_read_reg( ctx, reg_addr0, chann_data, 1 );
                    oximeter_read_reg( ctx, ( reg_addr0 + 4 ), chann_data_high, 1 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 0 ] = tmp;
                    break;
                }
                case OXIMETER_CH2_EN:
                {
                    oximeter_read_reg( ctx, reg_addr1, chann_data, 1 );
                    oximeter_read_reg( ctx, ( reg_addr1 + 4 ), chann_data_high, 1 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 1 ] = tmp;
                    break;
                }
                case OXIMETER_CH1_CH2_EN:
                {
                    oximeter_read_reg( ctx, reg_addr0, chann_data, 2 );
                    oximeter_read_reg( ctx, ( reg_addr0 + 4 ), chann_data_high, 2 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 0 ] = tmp;
                    tmp = chann_data_high[ 1 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 1 ];
                    chann_results[ 1 ] = tmp;
                    break;
                }
                case OXIMETER_CH3_CH4_EN:
                {
                    oximeter_read_reg( ctx, reg_addr2, chann_data, 2 );
                    oximeter_read_reg( ctx, ( reg_addr2 + 4 ), chann_data_high, 2 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 2 ] = tmp;
                    tmp = chann_data_high[ 1 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 1 ];
                    chann_results[ 3 ] = tmp;
                    break;
                }
                case OXIMETER_CH2_CH3_CH4_EN:
                {
                    oximeter_read_reg( ctx, reg_addr1, chann_data, 3 );
                    oximeter_read_reg( ctx, ( reg_addr1 + 4 ), chann_data_high, 3 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 1 ] = tmp;
                    tmp = chann_data_high[ 1 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 1 ];
                    chann_results[ 2 ] = tmp;
                    tmp = chann_data_high[ 2 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 2 ];
                    chann_results[ 3 ] = tmp;
                    break;
                }
                case OXIMETER_ALL_CHANN_EN:
                {
                    oximeter_read_reg( ctx, reg_addr0, chann_data, 4 );
                    oximeter_read_reg( ctx, ( reg_addr0 + 4 ), chann_data_high, 4 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 0 ] = tmp;
                    tmp = chann_data_high[ 1 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 1 ];
                    chann_results[ 1 ] = tmp;
                    tmp = chann_data_high[ 2 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 2 ];
                    chann_results[ 2 ] = tmp;
                    tmp = chann_data_high[ 3 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 3 ];
                    chann_results[ 3 ] = tmp;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    oximeter_write_reg( ctx, OXIMETER_REG_DATA_ACCESS_CTL, 0x0000 );
    ctx->result_mode_check = result_mode;
}

uint8_t oximeter_get_int_gpio0 ( oximeter_t* ctx )
{
    return digital_in_read( &ctx->io0 );
}

uint8_t oximeter_get_int_gpio1 ( oximeter_t* ctx )
{
    return digital_in_read( &ctx->io1 );
}

void oximeter_reset ( oximeter_t* ctx )
{
    uint16_t tmp = 0;

    oximeter_write_reg( ctx, OXIMETER_REG_SW_RESET, 0x0001 );
    oximeter_read_reg( ctx, OXIMETER_REG_SW_RESET, &tmp, 1 );
    
    while ( tmp )
    {
        Delay_1ms ( );
        oximeter_read_reg( ctx, OXIMETER_REG_SW_RESET, &tmp, 1 );
    }
}

err_t oximeter_set_mode ( oximeter_t* ctx, uint16_t select_mode )
{
    if ( select_mode > 0x0002 )
    {
        return OXIMETER_ERROR;
    }
    
    oximeter_write_reg( ctx, OXIMETER_REG_MODE, select_mode );
    
    return OXIMETER_OK;
}

// ------------------------------------------------------------------------- END


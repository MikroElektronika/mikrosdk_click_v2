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
    cfg->i2c_address = 0x64;

    cfg->dev_enabled_chann = 5;
    cfg->dev_enabled_slot_a = 0;
    cfg->dev_enabled_slot_b = 0;
}

OXIMETER_RETVAL oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
     i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return OXIMETER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    digital_in_init( &ctx->io0, cfg->io0 );
   
    digital_in_init( &ctx->io1, cfg->io1 );

    ctx->enabled_chann = cfg->dev_enabled_chann;
    ctx->enabled_slot_a = cfg->dev_enabled_slot_a;
    ctx->enabled_slot_b = cfg->dev_enabled_slot_b;

    return OXIMETER_OK;
}

void oximeter_default_cfg ( oximeter_t *ctx )
{
    enable_t tmp;
    oxim_reset( ctx );
    oxim_write_reg( ctx, OXIM_SAMPLE_CLK_REG, 0x0080 );
    oxim_set_mode( ctx, OXIM_DEV_PROGRAM_OP_MODE );

    tmp.enable_slot = OXIM_EN_SLOT;
    tmp.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    tmp.enable_led = OXIM_LEDX2_EN;
    oxim_set_time_slot_a( ctx, &tmp, OXIM_SLOT_NORM_OP_MODE );

    tmp.enable_slot = OXIM_DIS_SLOT;
    tmp.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    tmp.enable_led = OXIM_LEDX1_EN;
    oxim_set_time_slot_b( ctx, &tmp, OXIM_SLOT_NORM_OP_MODE );

    oxim_enable_channels( ctx, OXIM_ALL_CHANN_EN );
    oxim_write_reg( ctx, OXIM_STATUS_REG, 0xFFFF );
    oxim_write_reg( ctx, OXIM_DATA_ACCESS_CTL_REG, 0x0000 );
    oxim_set_mode( ctx, OXIM_DEV_NORMAL_OP_MODE );
}

uint8_t oxim_write_reg ( oximeter_t* ctx, uint8_t register_address,
                         uint16_t transfer_data )
{
    uint8_t buff_data[ 3 ];

    if ( register_address > 0x7F )
        return 1;

    buff_data[ 0 ] = register_address;
    buff_data[ 1 ] = transfer_data >> 8;
    buff_data[ 2 ] = transfer_data;

    i2c_master_write( &ctx->i2c, buff_data, 3 ); 

    return 0;
}

uint8_t oxim_read_reg ( oximeter_t* ctx, uint8_t register_address, uint16_t* data_out,
                        uint8_t n_registers )
{
    uint8_t buff_data[ 256 ];
    uint16_t temp = 0;
    uint8_t cnt;
    uint8_t count = 0;
    uint8_t check_st = 0;
    uint8_t n_bytes;

    if ( register_address > 0x7F )
    {
        return 1;
    }
    if ( n_registers > 128 )
    {
        return 2;
    }

    n_bytes = n_registers * 2;    

    i2c_master_write_then_read( &ctx->i2c, &register_address, 1, buff_data, n_bytes );

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        if ( !check_st )
        {
            temp = buff_data[ cnt ];
            temp <<= 8;
            check_st++;
        }
        else
        {
            temp |= buff_data[ cnt ];
            data_out[ count ] = temp;
            temp = 0;
            check_st = 0;
            count++;
        }
    }

    return 0;
}

uint8_t oxim_set_time_slot_a ( oximeter_t* ctx, enable_t* dev_enable,
                               uint8_t set_mode )
{
    uint16_t tmp;
    uint16_t led_set;

    if ( dev_enable->enable_slot )
    {
        oxim_read_reg( ctx, OXIM_SLOT_EN_REG, &tmp, 1 );
        tmp |= 0x0001;
        oxim_write_reg( ctx, OXIM_SLOT_EN_REG, tmp );
        oxim_read_reg( ctx, OXIM_PD_LED_SELECT_REG, &tmp, 1 );
        oxim_read_reg( ctx, OXIM_LED_DISABLE_REG, &led_set, 1 );

        switch ( dev_enable->enable_photodiode )
        {
            case OXIM_NO_PHOTODIODE_CONN:
            {
                tmp &= 0xFF0F;
                break;
            }
            case OXIM_ALL_PHOTODIODE_CONN:
            {
                tmp &= 0xFF0F;
                tmp |= 0x0010;
                break;
            }
            case OXIM_PD5_PD6_PD7_PD8_CONN:
            {
                tmp &= 0xFF0F;
                tmp |= 0x0040;
                break;
            }
            case OXIM_PD1_PD2_PD3_PD4_CONN:
            {
                tmp &= 0xFF0F;
                tmp |= 0x0050;
                break;
            }
            default:
            {
                return 1;
            }
        }

        switch ( dev_enable->enable_led )
        {
            case OXIM_PDX_TO_AFE:
            {
                tmp &= 0xFFFC;
                led_set &= 0xFEFF;
                break;
            }
            case OXIM_LEDX1_EN:
            {
                tmp &= 0xFFFC;
                tmp |= 0x0001;
                led_set &= 0xFEFF;
                break;
            }
            case OXIM_LEDX2_EN:
            {
                tmp &= 0xFFFC;
                tmp |= 0x0002;
                led_set &= 0xFEFF;
                break;
            }
            case OXIM_LEDX3_EN:
            {
                tmp &= 0xFFFC;
                tmp |= 0x0003;
                led_set &= 0xFEFF;
                break;
            }
            case OXIM_DIS_LED:
            {
                led_set |= 0x0100;
                break;
            }
            default:
            {
                return 2;
            }
        }

        oxim_write_reg( ctx, OXIM_PD_LED_SELECT_REG, tmp );
        oxim_write_reg( ctx, OXIM_LED_DISABLE_REG, led_set );
        oxim_read_reg( ctx, OXIM_DIGITAL_INT_EN_REG, &tmp, 1 );
        if ( set_mode )
            tmp |= 0x1000;
        else
            tmp &= 0xEFFF;
        oxim_write_reg( ctx, OXIM_DIGITAL_INT_EN_REG, tmp );
        oxim_read_reg( ctx, OXIM_INT_MASK_REG, &tmp, 1 );
        tmp &= 0xFFDF;
        oxim_write_reg( ctx, OXIM_INT_MASK_REG, tmp );
    }
    else
    {
        oxim_read_reg( ctx, OXIM_SLOT_EN_REG, &tmp, 1 );
        tmp &= 0xFFFE;
        oxim_write_reg( ctx, OXIM_SLOT_EN_REG, tmp );
        oxim_read_reg( ctx, OXIM_INT_MASK_REG, &tmp, 1 );
        tmp |= 0x0020;
        oxim_write_reg( ctx, OXIM_INT_MASK_REG, tmp );
    }
    ctx->enabled_slot_a = dev_enable->enable_slot;

    return 0;
}

uint8_t oxim_set_time_slot_b ( oximeter_t* ctx, enable_t* dev_enable, uint8_t set_mode )
{
    uint16_t tmp;
    uint16_t led_set;

    if ( dev_enable->enable_slot )
    {
        oxim_read_reg( ctx, OXIM_SLOT_EN_REG, &tmp, 1 );
        tmp |= 0x0020;
        oxim_write_reg( ctx, OXIM_SLOT_EN_REG, tmp );
        oxim_read_reg( ctx, OXIM_PD_LED_SELECT_REG, &tmp, 1 );
        oxim_read_reg( ctx, OXIM_LED_DISABLE_REG, &led_set, 1 );

        switch ( dev_enable->enable_photodiode )
        {
            case OXIM_NO_PHOTODIODE_CONN:
            {
                tmp &= 0xF0FF;
                break;
            }
            case OXIM_ALL_PHOTODIODE_CONN:
            {
                tmp &= 0xF0FF;
                tmp |= 0x0100;
                break;
            }
            case OXIM_PD5_PD6_PD7_PD8_CONN:
            {
                tmp &= 0xF0FF;
                tmp |= 0x0400;
                break;
            }
            case OXIM_PD1_PD2_PD3_PD4_CONN:
            {
                tmp &= 0xF0FF;
                tmp |= 0x0500;
                break;
            }
            default:
            {
                return 1;
            }
        }

        switch ( dev_enable->enable_led )
        {
            case OXIM_PDX_TO_AFE:
            {
                tmp &= 0xFFF3;
                led_set &= 0xFDFF;
                break;
            }
            case OXIM_LEDX1_EN:
            {
                tmp &= 0xFFF3;
                tmp |= 0x0004;
                led_set &= 0xFDFF;
                break;
            }
            case OXIM_LEDX2_EN:
            {
                tmp &= 0xFFF3;
                tmp |= 0x0008;
                led_set &= 0xFDFF;
                break;
            }
            case OXIM_LEDX3_EN:
            {
                tmp &= 0xFFF3;
                tmp |= 0x000C;
                led_set &= 0xFDFF;
                break;
            }
            case OXIM_DIS_LED:
            {
                led_set |= 0x0200;
                break;
            }
            default:
            {
                return 2;
            }
        }

        oxim_write_reg( ctx, OXIM_PD_LED_SELECT_REG, tmp );
        oxim_write_reg( ctx, OXIM_LED_DISABLE_REG, led_set );
        oxim_read_reg( ctx, OXIM_DIGITAL_INT_EN_REG, &tmp, 1 );
        if ( set_mode )
        {
            tmp |= 0x2000;
        }
        else
        {
            tmp &= 0xDFFF;
        }
        oxim_write_reg( ctx, OXIM_DIGITAL_INT_EN_REG, tmp );
        oxim_read_reg( ctx, OXIM_INT_MASK_REG, &tmp, 1 );
        tmp &= 0xFFBF;
        oxim_write_reg( ctx, OXIM_INT_MASK_REG, tmp );
    }
    else
    {
        oxim_read_reg( ctx, OXIM_SLOT_EN_REG, &tmp, 1 );
        tmp &= 0xFFDF;
        oxim_write_reg( ctx, OXIM_SLOT_EN_REG, tmp );
        oxim_read_reg( ctx, OXIM_INT_MASK_REG, &tmp, 1 );
        tmp |= 0x0040;
        oxim_write_reg( ctx, OXIM_INT_MASK_REG, tmp );
    }
    ctx->enabled_slot_b = dev_enable->enable_slot;

    return 0;
}

uint8_t oxim_enable_channels ( oximeter_t* ctx, uint8_t select_channel )
{
    uint16_t pom1;
    uint16_t pom2;

    oxim_read_reg( ctx, OXIM_AFE_PWR_CFG1_REG, &pom1, 1 );
    oxim_read_reg( ctx, OXIM_ALT_PWR_DN_REG, &pom2, 1 );

    switch ( select_channel )
    {
        case OXIM_CH1_EN:
        {
            pom1 |= 0x01C0;
            pom1 &= 0xFFC7;
            break;
        }
        case OXIM_CH2_EN:
        {
            pom1 &= 0xFE3F;
            pom1 |= 0x0038;
            pom2 |= 0xE000;
            pom2 &= 0xE3FF;
            break;
        }
        case OXIM_CH1_CH2_EN:
        {
            pom1 &= 0xFE3F;
            pom1 &= 0xFFC7;
            pom2 |= 0xE000;
            pom2 &= 0xE3FF;
            break;
        }
        case OXIM_CH3_CH4_EN:
        {
            pom1 &= 0xFE3F;
            pom1 |= 0x0038;
            pom2 &= 0x1FFF;
            pom2 |= 0x1C00;
            break;
        }
        case OXIM_CH2_CH3_CH4_EN:
        {
            pom1 &= 0xFE3F;
            pom1 |= 0x0038;
            pom2 &= 0x1FFF;
            pom2 &= 0xE3FF;
            break;
        }
        case OXIM_ALL_CHANN_EN:
        {
            pom1 &= 0xFE3F;
            pom1 &= 0xFFC7;
            pom2 &= 0x1FFF;
            pom2 &= 0xE3FF;
            break;
        }
        default:
        {
            return 1;
        }
    }
    oxim_write_reg( ctx, OXIM_AFE_PWR_CFG1_REG, pom1 );
    oxim_write_reg( ctx, OXIM_ALT_PWR_DN_REG, pom2 );
    ctx->enabled_chann = select_channel;

    return 0;
}

void oxim_read_data ( oximeter_t* ctx, uint32_t* chann_results, uint8_t result_mode )
{
    uint16_t chann_data[ 4 ];
    uint16_t chann_data_high[ 4 ];
    uint16_t interr_check;
    uint32_t tmp = 0;
    uint8_t reg_addr0;
    uint8_t reg_addr1;
    uint8_t reg_addr2;

    oxim_read_reg( ctx, OXIM_STATUS_REG, &interr_check, 1 );
    while ( !( interr_check & 0x0060 ) )
    oxim_read_reg( ctx, OXIM_STATUS_REG, &interr_check, 1 );
    oxim_write_reg( ctx, OXIM_STATUS_REG, 0xFFFF );
    oxim_write_reg( ctx, OXIM_DATA_ACCESS_CTL_REG, 0x0006 );

    if ( !result_mode )
    {
        if ( ctx->enabled_slot_a != OXIM_DIS_SLOT )
        {
            reg_addr0 = OXIM_SLOTA_PD1_16BIT_REG;
            reg_addr1 = OXIM_SLOTA_PD2_16BIT_REG;
            reg_addr2 = OXIM_SLOTA_PD3_16BIT_REG;
        }
        if ( ctx->enabled_slot_b != OXIM_DIS_SLOT )
        {
            reg_addr0 = OXIM_SLOTB_PD1_16BIT_REG;
            reg_addr1 = OXIM_SLOTB_PD2_16BIT_REG;
            reg_addr2 = OXIM_SLOTB_PD3_16BIT_REG;
        }
        if ( ( ctx->enabled_slot_a != OXIM_DIS_SLOT) || ( ctx->enabled_slot_b != OXIM_DIS_SLOT) )
        {
            switch ( ctx->enabled_chann )
            {
                case OXIM_CH1_EN:
                {
                    oxim_read_reg( ctx, reg_addr0, chann_data, 1 );
                    chann_results[ 0 ] = chann_data[ 0 ] & 0x0000FFFF;
                    break;
                }
                case OXIM_CH2_EN:
                {
                    oxim_read_reg( ctx, reg_addr1, chann_data, 1 );
                    chann_results[ 1 ] = chann_data[ 0 ] & 0x0000FFFF;
                    break;
                }
                case OXIM_CH1_CH2_EN:
                {
                    oxim_read_reg( ctx, reg_addr0, chann_data, 2 );
                    chann_results[ 0 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 1 ] = chann_data[ 1 ] & 0x0000FFFF;
                    break;
                }
                case OXIM_CH3_CH4_EN:
                {
                    oxim_read_reg( ctx, reg_addr2, chann_data, 2 );
                    chann_results[ 2 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 3 ] = chann_data[ 1 ] & 0x0000FFFF;
                    break;
                }
                case OXIM_CH2_CH3_CH4_EN:
                {
                    oxim_read_reg( ctx, reg_addr1, chann_data, 3 );
                    chann_results[ 1 ] = chann_data[ 0 ] & 0x0000FFFF;
                    chann_results[ 2 ] = chann_data[ 1 ] & 0x0000FFFF;
                    chann_results[ 3 ] = chann_data[ 2 ] & 0x0000FFFF;
                    break;
                }
                case OXIM_ALL_CHANN_EN:
                {
                    oxim_read_reg( ctx, reg_addr0, chann_data, 4 );
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
        if ( ctx->enabled_slot_a != OXIM_DIS_SLOT )
        {
            reg_addr0 = OXIM_A_PD1_LOW_REG;
            reg_addr1 = OXIM_A_PD2_LOW_REG;
            reg_addr2 = OXIM_A_PD3_LOW_REG;
        }
        if ( ctx->enabled_slot_b != OXIM_DIS_SLOT )
        {
            reg_addr0 = OXIM_B_PD1_LOW_REG;
            reg_addr1 = OXIM_B_PD2_LOW_REG;
            reg_addr2 = OXIM_B_PD3_LOW_REG;
        }
        if ( ( ctx->enabled_slot_a != OXIM_DIS_SLOT ) || ( ctx->enabled_slot_b != OXIM_DIS_SLOT ) )
        {
            switch ( ctx->enabled_chann )
            {
                case OXIM_CH1_EN:
                {
                    oxim_read_reg( ctx, reg_addr0, chann_data, 1 );
                    oxim_read_reg( ctx, ( reg_addr0 + 4 ), chann_data_high, 1 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 0 ] = tmp;
                    break;
                }
                case OXIM_CH2_EN:
                {
                    oxim_read_reg( ctx, reg_addr1, chann_data, 1 );
                    oxim_read_reg( ctx, ( reg_addr1 + 4 ), chann_data_high, 1 );
                    tmp = chann_data_high[ 0 ];
                    tmp <<= 16;
                    tmp |= chann_data[ 0 ];
                    chann_results[ 1 ] = tmp;
                    break;
                }
                case OXIM_CH1_CH2_EN:
                {
                    oxim_read_reg( ctx, reg_addr0, chann_data, 2 );
                    oxim_read_reg( ctx, ( reg_addr0 + 4 ), chann_data_high, 2 );
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
                case OXIM_CH3_CH4_EN:
                {
                    oxim_read_reg( ctx, reg_addr2, chann_data, 2 );
                    oxim_read_reg( ctx, ( reg_addr2 + 4 ), chann_data_high, 2 );
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
                case OXIM_CH2_CH3_CH4_EN:
                {
                    oxim_read_reg( ctx, reg_addr1, chann_data, 3 );
                    oxim_read_reg( ctx, ( reg_addr1 + 4 ), chann_data_high, 3 );
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
                case OXIM_ALL_CHANN_EN:
                {
                    oxim_read_reg( ctx, reg_addr0, chann_data, 4 );
                    oxim_read_reg( ctx, ( reg_addr0 + 4 ), chann_data_high, 4 );
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
    oxim_write_reg( ctx, OXIM_DATA_ACCESS_CTL_REG, 0x0000 );
    ctx->result_mode_check = result_mode;
}

uint8_t oxim_get_interr_gpio0 ( oximeter_t* ctx )
{
    if ( digital_in_read( &ctx->io0 ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t oxim_get_interr_gpio1 ( oximeter_t* ctx )
{
    if ( digital_in_read( &ctx->io1 ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void oxim_reset ( oximeter_t* ctx )
{
    uint16_t tmp = 1;

    oxim_write_reg( ctx, OXIM_SW_RESET_REG, 0x0001 );
    oxim_read_reg( ctx, OXIM_SW_RESET_REG, &tmp, 1 );
    
    while ( tmp )
    {
        oxim_read_reg( ctx, OXIM_SW_RESET_REG, &tmp, 1 );
    }
        
}

uint8_t oxim_set_mode ( oximeter_t* ctx, uint16_t select_mode )
{
    if ( select_mode > 0x0002 )
    {
        return 1;
    }
    
    oxim_write_reg( ctx, OXIM_MODE_REG, select_mode );
    
    return 0;

}

// ------------------------------------------------------------------------- END


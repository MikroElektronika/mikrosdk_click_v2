/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file oximeter2.c
 * @brief This file contains API source for Oximeter 2 Click driver.
 */

#include "oximeter2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oximeter2_cfg_setup( oximeter2_cfg_t *cfg )
{
    cfg->scl_pin = HAL_PIN_NC;
    cfg->sda_pin = HAL_PIN_NC;
    
    cfg->i2c_address = OXIMETER2_SLAVE_ADDRESS;
    cfg->i2c_speed = I2C_MASTER_SPEED_FULL;
    
    cfg->dev_enabled_channel = OXIMETER2_CH3_CH4_SELECTED;
    cfg->dev_enabled_slot_a = OXIMETER2_EN_SLOT;
    cfg->dev_enabled_slot_b = OXIMETER2_EN_SLOT;
}

OXIMETER2_RETVAL oximeter2_init ( oximeter2_t *ctx, oximeter2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    i2c_master_configure_default( &i2c_cfg );
    
    i2c_cfg.speed = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl_pin;
    i2c_cfg.sda = cfg->sda_pin;
    
    ctx->slave_address = cfg->i2c_address;
    
    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return OXIMETER2_INIT_ERROR;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );
    
    ctx->enabled_channel = cfg->dev_enabled_channel;
    ctx->enabled_slot_a = cfg->dev_enabled_slot_a;
    ctx->enabled_slot_b = cfg->dev_enabled_slot_b;
    
    return OXIMETER2_OK;
}

void oximeter2_default_cfg( oximeter2_t *ctx )
{
    enable_t tmp;
    oximeter2_reset( ctx );
    oximeter2_write_reg( ctx, OXIMETER2_SAMPLE_CLK_REG, OXIMETER2_SAMPLE_CLK_CLK32K_EN );
    oximeter2_set_mode( ctx, OXIMETER2_MODE_PROGRAM );

    // Register 0x11.
    oximeter2_write_reg( ctx, OXIMETER2_SLOT_EN_REG, 0x30A9 );
    
    // Register 0x12.
    oximeter2_write_reg( ctx, OXIMETER2_FSAMPLE_REG, 0x000A );
    
    // Register 0x14.
    oximeter2_write_reg( ctx, OXIMETER2_PD_LED_SELECT_REG, 0x0116 );
    
    
    // RECOMMENDED SETTINGS.

    // Register:    NUM_AVG.
    // Description: Average samples for Time Slot A = 8 and Time Slot B = 8.
    oximeter2_write_reg( ctx, OXIMETER2_NUM_AVG_REG, 0x0330 );
    
    // Register:    SLOTA_CH1_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_CH1_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTA_CH2_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_CH2_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTA_CH3_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_CH3_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTA_CH4_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_CH4_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTB_CH1_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_CH1_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTB_CH2_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_CH2_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTB_CH3_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_CH3_OFFSET_REG, 0x1FF0 );

    // Register:    SLOTB_CH4_OFFSET.
    // Description: 8,176 half scale.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_CH4_OFFSET_REG, 0x1FF0 );

    // Register:    ILED1_COARSE.
    // Description: 100mA current.
    oximeter2_write_reg( ctx, OXIMETER2_ILED1_COARSE_REG, 0x3005 );

    // Register:    ILED2_COARSE.
    // Description: 130mA current.
    oximeter2_write_reg( ctx, OXIMETER2_ILED2_COARSE_REG, 0x3007 );

    // Register:    ILED_FINE.
    oximeter2_write_reg( ctx, OXIMETER2_ILED_FINE_REG, 0x0207 );

    // Register:    SLOTA_LEDMODE.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_LEDMODE_REG, 0x0319 );

    // Register:    SLOTA_NUMPULSES.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_NUMPULSES_REG, 0x0813 );

    // Register:    SLOTB_LEDMODE.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_LEDMODE_REG, 0x0319 );

    // Register:    SLOTB_NUMPULSES.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_NUMPULSES_REG, 0x0813 );
        
    // Register:    SLOTA_AFEMODE.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_AFEMODE_REG, 0x21F3 );
    
    // Register:    SLOTB_AFEMODE.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_AFEMODE_REG, 0x21F3 );
    
    // Register:    SLOTA_GAIN.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTA_GAIN_REG, 0x1C36 );

    // Register:    SLOTB_GAIN.
    oximeter2_write_reg( ctx, OXIMETER2_SLOTB_GAIN_REG, 0x1C36 );
    
    // Register:    ADC_TIMING.
    oximeter2_write_reg( ctx, OXIMETER2_ADC_TIMING_REG, 0x0040 );

    tmp.enable_slot = OXIMETER2_EN_SLOT;
    tmp.enable_photodiode = OXIMETER2_CH3_CH4_SELECTED;
    oximeter2_set_time_slot_a( ctx, &tmp );

    tmp.enable_slot = OXIMETER2_EN_SLOT;
    tmp.enable_photodiode = OXIMETER2_CH3_CH4_SELECTED;
    oximeter2_set_time_slot_b( ctx, &tmp );

    oximeter2_write_reg( ctx, OXIMETER2_STATUS_REG, 0xFFFF );
    oximeter2_write_reg( ctx, OXIMETER2_DATA_ACCESS_CTL_REG, OXIMETER2_ALLOW_UPDATE_OF_DATA_REGS );
   
    oximeter2_set_mode( ctx, OXIMETER2_MODE_SAMPLE );

}

uint8_t oximeter2_write_reg( oximeter2_t *ctx, uint8_t register_address, uint16_t transfer_data )
{
    uint8_t buff_data[ 3 ];
    
    if ( register_address > OXIMETER2_B_PD4_HIGH_REG )
    {
        return OXIMETER2_INIT_ERROR;
    }
    
    buff_data[ 0 ] = register_address;
    buff_data[ 1 ] = transfer_data >> 8;
    buff_data[ 2 ] = transfer_data;
    
    i2c_master_write( &ctx->i2c, buff_data, 3 );
    
    return OXIMETER2_OK;
}

uint8_t oximeter2_read_reg ( oximeter2_t* ctx, uint8_t register_address, uint16_t* data_out,
                        uint8_t num_of_regs )
{
    uint8_t buff_data[ 256 ];
    uint16_t temp = 0;
    uint8_t cnt;
    uint8_t count = 0;
    uint8_t check_st = 0;
    uint8_t n_bytes;

    if ( register_address > OXIMETER2_B_PD4_HIGH_REG )
    {
        return OXIMETER2_INIT_ERROR;
    }
    if ( num_of_regs > 128 )
    {
        return OXIMETER2_INIT_ERROR;
    }

    n_bytes = num_of_regs * 2;    

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

    return OXIMETER2_OK;
}

uint8_t oximeter2_set_time_slot_a( oximeter2_t *ctx, enable_t *dev_enable )
{
    uint16_t tmp;
    uint16_t led_set;
    
    if ( dev_enable->enable_slot )
    {
        oximeter2_read_reg( ctx, OXIMETER2_SLOT_EN_REG, &tmp, 1 );
        tmp |= 0x0001;
        oximeter2_write_reg( ctx, OXIMETER2_SLOT_EN_REG, tmp );
        oximeter2_read_reg( ctx, OXIMETER2_PD_LED_SELECT_REG, &tmp, 1 );

        switch ( dev_enable->enable_photodiode )
        {
            case OXIMETER2_ALL_CHANNELS_SELECTED:
            {
                tmp = 0x0446;
                break;
            }
            case OXIMETER2_CH3_CH4_SELECTED:
            {
                tmp = 0x0116;
                break;
            }
            default:
            {
                return OXIMETER2_INIT_ERROR;
            }
        }

        oximeter2_write_reg( ctx, OXIMETER2_PD_LED_SELECT_REG, tmp );
        
    } else
    {
        oximeter2_read_reg( ctx, OXIMETER2_SLOT_EN_REG, &tmp, 1 );
        tmp &= 0xFFFE;
        oximeter2_write_reg( ctx, OXIMETER2_SLOT_EN_REG, tmp );
        oximeter2_read_reg( ctx, OXIMETER2_INT_MASK_REG, &tmp, 1 );
        tmp |= 0x0020;
        oximeter2_write_reg( ctx, OXIMETER2_INT_MASK_REG, tmp );
    }
    ctx->enabled_slot_a = dev_enable->enable_slot;
    
    
    return OXIMETER2_OK;
}

uint8_t oximeter2_set_time_slot_b( oximeter2_t *ctx, enable_t *dev_enable )
{
    uint16_t tmp;
    
    if ( dev_enable->enable_slot )
    {
        oximeter2_read_reg( ctx, OXIMETER2_SLOT_EN_REG, &tmp, 1 );
        tmp |= 0x0001;
        oximeter2_write_reg( ctx, OXIMETER2_SLOT_EN_REG, tmp );
        oximeter2_read_reg( ctx, OXIMETER2_PD_LED_SELECT_REG, &tmp, 1 );

        switch ( dev_enable->enable_photodiode )
        {
            case OXIMETER2_ALL_CHANNELS_SELECTED:
            {
                tmp = 0x0446;
                break;
            }
            case OXIMETER2_CH3_CH4_SELECTED:
            {
                tmp = 0x0116;
                break;
            }
            default:
            {
                return OXIMETER2_INIT_ERROR;
            }
        }
        
        oximeter2_write_reg( ctx, OXIMETER2_PD_LED_SELECT_REG, tmp );
        
    } else
    {
        oximeter2_read_reg( ctx, OXIMETER2_SLOT_EN_REG, &tmp, 1 );
        tmp &= 0xFFDF;
        oximeter2_write_reg( ctx, OXIMETER2_SLOT_EN_REG, tmp );
        oximeter2_read_reg( ctx, OXIMETER2_INT_MASK_REG, &tmp, 1 );
        tmp |= 0x0040;
        oximeter2_write_reg( ctx, OXIMETER2_INT_MASK_REG, tmp );
    }
    ctx->enabled_slot_b = dev_enable->enable_slot;
    
    return OXIMETER2_OK;
}

void oximeter2_read_data( oximeter2_t *ctx, uint32_t *channel_results )
{
    uint16_t channel_data[ 4 ];
    uint16_t interrupt_check;
    uint8_t reg_addr0;
    uint8_t reg_addr1;
    uint8_t reg_addr2;
    uint8_t reg_addr3;
    
    oximeter2_read_reg( ctx, OXIMETER2_STATUS_REG, &interrupt_check, 1 ); // Read the status register for interrupt flags.
    oximeter2_write_reg( ctx, OXIMETER2_STATUS_REG, OXIMETER2_CLEAR_INTERRUPTS ); // Flush them.
    oximeter2_write_reg( ctx, OXIMETER2_DATA_ACCESS_CTL_REG, OXIMETER2_PREVENT_UPDATE_OF_DATA_REGS ); // Stop updating data registers.
    
        if ( ctx->enabled_slot_a != OXIMETER2_DIS_SLOT )
        {
            reg_addr0 = OXIMETER2_SLOTA_PD1_16BIT_REG;
            reg_addr1 = OXIMETER2_SLOTA_PD2_16BIT_REG;
            reg_addr2 = OXIMETER2_SLOTA_PD3_16BIT_REG;
            reg_addr3 = OXIMETER2_SLOTA_PD4_16BIT_REG;
        }
        if ( ctx->enabled_slot_b != OXIMETER2_DIS_SLOT )
        {
            reg_addr0 = OXIMETER2_SLOTB_PD1_16BIT_REG;
            reg_addr1 = OXIMETER2_SLOTB_PD2_16BIT_REG;
            reg_addr2 = OXIMETER2_SLOTB_PD3_16BIT_REG;
            reg_addr3 = OXIMETER2_SLOTB_PD4_16BIT_REG;
        }
        
        if ( ( ctx->enabled_slot_a != OXIMETER2_DIS_SLOT) || ( ctx->enabled_slot_b != OXIMETER2_DIS_SLOT) )
        {
            switch ( ctx->enabled_channel )
            {
                case OXIMETER2_CH3_CH4_SELECTED:
                {
                    oximeter2_read_reg( ctx, reg_addr2, channel_data, 2 );
                    channel_results[ 2 ] = channel_data[ 0 ] & OXIMETER2_16_BIT_DATA_MASK;
                    channel_results[ 3 ] = channel_data[ 1 ] & OXIMETER2_16_BIT_DATA_MASK;
                    break;
                }
                case OXIMETER2_ALL_CHANNELS_SELECTED:
                {
                    oximeter2_read_reg( ctx, reg_addr0, channel_data, 4 );
                    channel_results[ 0 ] = channel_data[ 0 ] & OXIMETER2_16_BIT_DATA_MASK;
                    channel_results[ 1 ] = channel_data[ 1 ] & OXIMETER2_16_BIT_DATA_MASK;
                    channel_results[ 2 ] = channel_data[ 2 ] & OXIMETER2_16_BIT_DATA_MASK;
                    channel_results[ 3 ] = channel_data[ 3 ] & OXIMETER2_16_BIT_DATA_MASK;
                    break;                
                }
                default:
                {
                    break;
                }
            }
        }

    oximeter2_write_reg( ctx, OXIMETER2_DATA_ACCESS_CTL_REG, OXIMETER2_ALLOW_UPDATE_OF_DATA_REGS );
}


void oximeter2_reset ( oximeter2_t* ctx )
{
    oximeter2_write_reg( ctx, OXIMETER2_MODE_REG, OXIMETER2_MODE_PROGRAM );
}

uint8_t oximeter2_set_mode ( oximeter2_t* ctx, uint8_t desired_mode )
{
    if ( desired_mode > OXIMETER2_MODE_SAMPLE )
    {
        return OXIMETER2_INIT_ERROR;
    }
    
    oximeter2_write_reg( ctx, OXIMETER2_MODE_REG, desired_mode );
    
    return OXIMETER2_OK;
}

// ------------------------------------------------------------------------- END


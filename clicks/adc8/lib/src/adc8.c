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

#include "adc8.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void write_data_u16 ( adc8_t *ctx, uint8_t reg, uint16_t wr_data );

static uint16_t read_data_u16 ( adc8_t *ctx, uint8_t reg );

static void conversion_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc8_cfg_setup ( adc8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ADC8_DEVICE_SLAVE_ADDR_GND;
}

ADC8_RETVAL adc8_init ( adc8_t *ctx, adc8_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR)
    {
        return ADC8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->max_voltage = 2048.0;
    ctx->cfg_reg_value = 0x8583;
    ctx->diff_flag = 0;

    return ADC8_OK;
}

void adc8_default_cfg ( adc8_t *ctx )
{
    // Click default configuration

    ctx->max_voltage = 2048.0;
    ctx->cfg_reg_value = 0x8583;
    ctx->diff_flag = 0;

    adc8_set_cfg_register ( ctx, ADC8_CFG_CONVERSION_ENABLE | ADC8_CFG_GAIN_2048mV |
                                 ADC8_CFG_MODE_SINGLE | ADC8_CFG_SPS_8 |
                                 ADC8_CFG_COMP_MODE_TRADITIONAL | ADC8_CFG_COMP_POL_LOW |
                                 ADC8_CFG_COMP_LAT_ENABLE | ADC8_CFG_COMP_QUE_4_CONV );

}

void adc8_generic_write ( adc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

void adc8_generic_read ( adc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void adc8_set_cfg_register ( adc8_t *ctx, uint16_t cfg )
{
    ctx->cfg_reg_value |= cfg;

    write_data_u16 ( ctx, ADC8_REG_CONFIGURATION, ctx->cfg_reg_value );
    conversion_delay( );

    cfg &= 0x0E00;

    if ( cfg == ADC8_CFG_GAIN_256mV )
    {
        ctx->max_voltage = 256.0;
    }
    else if ( cfg == ADC8_CFG_GAIN_512mV )
    {
        ctx->max_voltage = 512.0;
    }
    else if ( cfg == ADC8_CFG_GAIN_1024mV )
    {
        ctx->max_voltage = 1024.0;
    }
    else if ( cfg == ADC8_CFG_GAIN_2048mV )
    {
        ctx->max_voltage = 2048.0;
    }
    else if ( cfg == ADC8_CFG_GAIN_4096mV )
    {
        ctx->max_voltage = 4096.0;
    }
    else if ( cfg == ADC8_CFG_GAIN_6144mV )
    {
        ctx->max_voltage = 6144.0;
    }
}

uint16_t adc8_get_adc_value ( adc8_t *ctx, uint8_t channel )
{
    uint16_t adc_data;

    switch(channel)
    {
        case 0:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP0_GND;
            ctx->diff_flag = 0;
            break;
        }
        case 1:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP1_GND;
            ctx->diff_flag = 0;
            break;
        }
        case 2:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP2_GND;
            ctx->diff_flag = 0;
            break;
        }
        case 3:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP3_GND;
            ctx->diff_flag = 0;
            break;
        }
        case 4:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP0_AINN1;
            ctx->diff_flag = 1;
            break;
        }
        case 5:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP0_AINN3;
            ctx->diff_flag = 1;
            break;
        }
        case 6:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP1_AINN3;
            ctx->diff_flag = 1;
            break;
        }
        case 7:
        {
            ctx->cfg_reg_value &= 0x8FFF;
            ctx->cfg_reg_value |= ADC8_CFG_MUX_AINP2_AINN3;
            ctx->diff_flag = 1;
            break;
        }
        default:
        {
            break;
        }
    }
    write_data_u16( ctx, ADC8_REG_CONFIGURATION, ctx->cfg_reg_value );
    conversion_delay( );

    adc_data = read_data_u16( ctx, ADC8_REG_CONVERSION );

    return adc_data;
}

float adc8_get_voltage ( adc8_t *ctx, uint8_t channel )
{
    uint16_t adc_value;
    float voltage;

    adc_value = adc8_get_adc_value( ctx, channel );

    if ( ctx->diff_flag == 0 )
    {
        voltage = adc_value * (float)( ctx->max_voltage / 0x8000 );
    }
    else
    {
        if ( ( adc_value > 0 ) && ( adc_value <= 0x8000 ) )
        {
            voltage = adc_value * (float)( ctx->max_voltage / 0x8000 );
        }
        else if ( ( adc_value > 0x8000 ) && ( adc_value < 0xFFF0 ) )
        {
            adc_value = 0xFFFF - adc_value;
            voltage = - ( adc_value * (float)( ctx->max_voltage / 0x8000 ) );
        }
        else
        {
            voltage = 0;
        }
    }
    return voltage;
}

uint8_t adc8_get_interrupt_state ( adc8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void adc8_get_single_channel ( adc8_t *ctx, adc8_single_volt_t *volt )
{
    volt->ch_0 = adc8_get_voltage( ctx, ADC8_SINGLE_CHANNEL_0 );
    volt->ch_1 = adc8_get_voltage( ctx, ADC8_SINGLE_CHANNEL_1 );
    volt->ch_2 = adc8_get_voltage( ctx, ADC8_SINGLE_CHANNEL_2 );
    volt->ch_3 = adc8_get_voltage( ctx, ADC8_SINGLE_CHANNEL_3 );
}

void adc8_get_diff_channel ( adc8_t *ctx, adc8_diff_volt_t *volt )
{
    volt->ch_0_1 = adc8_get_voltage( ctx, ADC8_DIFF_CHANNEL_0_1 );
    volt->ch_0_3 = adc8_get_voltage( ctx, ADC8_DIFF_CHANNEL_0_3 );
    volt->ch_1_3 = adc8_get_voltage( ctx, ADC8_DIFF_CHANNEL_1_3 );
    volt->ch_2_3 = adc8_get_voltage( ctx, ADC8_DIFF_CHANNEL_2_3 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void write_data_u16 ( adc8_t *ctx, uint8_t reg, uint16_t wr_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = (uint8_t)(wr_data >> 8);
    tx_buf[ 1 ] = (uint8_t)(wr_data & 0x00FF);

    adc8_generic_write( ctx, reg, tx_buf, 2 );
}

static uint16_t read_data_u16 ( adc8_t *ctx, uint8_t reg )
{
    uint8_t rx_buf[ 2 ];
    uint16_t rx_data;

    adc8_generic_read( ctx, reg, rx_buf, 2 );

    rx_data = rx_buf[ 0 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 1 ];

    return rx_data;
}

static void conversion_delay ( void )
{
    Delay_10ms();
}

// ------------------------------------------------------------------------- END


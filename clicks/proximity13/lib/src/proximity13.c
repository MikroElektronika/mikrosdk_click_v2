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

#include "proximity13.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CMD_MASK_PARAM_SET                                  0x02 << 6
#define CMD_MASK_PARAM_QUERY                                0x01 << 6

#define SHIFT_VAL                                           8

#define RESOLUTION_16_BIT                                   16
#define RESOLUTION_24_BIT                                   24

#define CHANNEL_0                                           0
#define CHANNEL_1                                           1
#define CHANNEL_2                                           2
#define CHANNEL_3                                           3
#define CHANNEL_4                                           4
#define CHANNEL_5                                           5

#define WRITE_SIZE                                          2
#define READ_SIZE                                           1

// -------------------------------------------------------------- PRIVATE TYPES

typedef struct
{
  uint32_t channel_0_res;
  uint32_t channel_1_res;
  uint32_t channel_2_res;
  uint32_t channel_3_res;
  uint32_t channel_4_res;
  uint32_t channel_5_res;
}proximity13_chn_res_t;

// ------------------------------------------------------------------ VARIABLES

static proximity13_chn_res_t chn_reses;
static uint8_t start_read_reg;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void channel_resolution ( uint8_t chn_num, uint8_t chn_res );

static uint32_t read_channel_val ( proximity13_t *ctx, uint8_t chn_res );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity13_cfg_setup ( proximity13_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY13_SLAVE_ADDRESS;
}

PROXIMITY13_RETVAL proximity13_init ( proximity13_t *ctx, proximity13_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY13_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY13_OK;
}

void proximity13_default_cfg ( proximity13_t *ctx )
{
    proximity13_config_t cfg_data;
    
    //Enabeling channels 1
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_CHAN_LIST, PROXIMITY13_CHANNEL_1 );

    //Configurating measure rate
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_MEASRATE_H, 0 );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_MEASRATE_L, 1 );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_MEASCOUNT_0, 5 );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_MEASCOUNT_1, 10 );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_MEASCOUNT_2, 0 );

    //Configurating channel 1
    cfg_data.adc_cfg = PROXIMITY13_ADC_CFG_MUX_LARGE_IR | PROXIMITY13_ADC_CFG_RATE_48p8_US;
    cfg_data.adc_sens = 0x02 | PROXIMITY13_ADC_SENS_SW_GAIN_1;
    cfg_data.adc_post = PROXIMITY13_ADC_POST_RESOLUTION_24;
    cfg_data.measure_cfg = PROXIMITY13_MEAS_CFG_MEASCOUNT0 | PROXIMITY13_MEAS_CFG_LED_1;
    porximity13_config_channel( ctx, 1, cfg_data );
}

void proximity13_generic_write ( proximity13_t *ctx, uint8_t reg_adr, uint8_t write_data )
{
    uint8_t tx_buf[ WRITE_SIZE ];
    
    tx_buf[ 0 ] = reg_adr;
    tx_buf[ 1 ] = write_data; 

    i2c_master_write( &ctx->i2c, tx_buf, WRITE_SIZE );   
}

uint8_t proximity13_generic_read ( proximity13_t *ctx, uint8_t reg_adr )
{
    uint8_t tx_buf[ 1 ];
    uint8_t temp_data;

    tx_buf [ 0 ] = reg_adr;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, &temp_data, READ_SIZE );
    
    return temp_data;
}

uint8_t proximity13_get_int_pin_status ( proximity13_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t proximity13_send_command ( proximity13_t *ctx, uint8_t cmd_val )
{
    uint8_t cmnd_ctr_s;
    uint8_t cmnd_ctr_v;

    for ( ; ; )
    {
        cmnd_ctr_s = proximity13_generic_read( ctx, PROXIMITY13_REG_RESPONSE_0 );

        proximity13_generic_write( ctx, PROXIMITY13_REG_COMMAND, cmd_val );

        cmnd_ctr_v = proximity13_generic_read( ctx, PROXIMITY13_REG_RESPONSE_0 );

        if ( cmnd_ctr_s < cmnd_ctr_v )
        {
            return PROXIMITY13_OK;
        }
    }
}

uint8_t proximity13_set_parameter ( proximity13_t *ctx, uint8_t cmd_val, uint8_t param )
{
    uint8_t cmnd_ctr_s;
    uint8_t cmnd_ctr_v;

    for ( ; ; )
    {
        cmnd_ctr_s = proximity13_generic_read( ctx, PROXIMITY13_REG_RESPONSE_0 );

        proximity13_generic_write( ctx, PROXIMITY13_REG_HOSTIN_0, param );

        proximity13_send_command( ctx, cmd_val | CMD_MASK_PARAM_SET );

        cmnd_ctr_v = proximity13_generic_read( ctx, PROXIMITY13_REG_RESPONSE_0 );

        if ( cmnd_ctr_s < cmnd_ctr_v )
        {
            return PROXIMITY13_OK;
        }
    }
}

uint8_t porximity13_config_channel ( proximity13_t *ctx, uint8_t chn_num, proximity13_config_t cfg_val )
{
    uint8_t index;
    uint8_t temp_sens = cfg_val.adc_sens & 0x0F;

    if ( chn_num < 0 || chn_num > 5 )
    {
        return PROXIMITY13_ERROR;
    }

    if ( temp_sens < PROXIMITY13_ADC_SENS_HW_GAIN_MIN_24p4_US )
    {
        temp_sens = PROXIMITY13_ADC_SENS_HW_GAIN_MIN_24p4_US;
    } 
    else if ( temp_sens > PROXIMITY13_ADC_SENS_HW_GAIN_MAX_50_MS )
    {
        temp_sens = PROXIMITY13_ADC_SENS_HW_GAIN_MAX_50_MS;
    }

    index = 4 * chn_num;

    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_ADCCONFIG_0 + index,
                                cfg_val.adc_cfg );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_ADCSENS_0 + index, 
                                cfg_val.adc_sens );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_ADCPOST_0 + index, 
                                cfg_val.adc_post );
    proximity13_set_parameter ( ctx, PROXIMITY13_PARAMETER_MEASCONFIG_0 + index, 
                                cfg_val.measure_cfg );

    channel_resolution( chn_num, ( cfg_val.adc_post & PROXIMITY13_ADC_POST_RESOLUTION_24 ) );

    return PROXIMITY13_OK;
}

uint8_t porximity13_check_id ( proximity13_t *ctx )
{
    uint8_t check_id;

    check_id = proximity13_generic_read ( ctx, PROXIMITY13_REG_PART_ID );
    if ( ! ( check_id == PROXIMITY13_DEV_ID_VAL ) )
    {
        return PROXIMITY13_ERROR;
    }

    check_id = proximity13_generic_read ( ctx, PROXIMITY13_REG_HW_ID );
    if ( ! ( check_id == PROXIMITY13_HW_ID_VAL ) )
    {
        return PROXIMITY13_ERROR;
    }

    check_id = proximity13_generic_read ( ctx, PROXIMITY13_REG_REV_ID );
    if ( ! ( check_id == PROXIMITY13_REV_ID_VAL ) )
    {
        return PROXIMITY13_ERROR;
    }

    return PROXIMITY13_OK;
}

void proximity13_read_channels ( proximity13_t *ctx, proximity13_chn_val_t *chn_val )
{
    uint8_t enabled;
    start_read_reg = PROXIMITY13_REG_HOSTOUT_0;

    enabled = proximity13_generic_read( ctx, PROXIMITY13_REG_IRQ_STATUS );
    
    if ( ( enabled & PROXIMITY13_CHANNEL_0 ) == PROXIMITY13_CHANNEL_0 )
    {
        chn_val->channel_0 = read_channel_val( ctx, chn_reses.channel_0_res );
    }
    else
    {
        chn_val->channel_0 = 0;
    }

    if ( ( enabled & PROXIMITY13_CHANNEL_1 ) == PROXIMITY13_CHANNEL_1 )
    {
        chn_val->channel_1 = read_channel_val( ctx, chn_reses.channel_1_res );
    }
    else
    {
        chn_val->channel_1 = 0;
    }

    if ( ( enabled & PROXIMITY13_CHANNEL_2 ) == PROXIMITY13_CHANNEL_2 )
    {
        chn_val->channel_2 = read_channel_val( ctx, chn_reses.channel_2_res );
    }
    else
    {
        chn_val->channel_2 = 0;
    }

    if ( ( enabled & PROXIMITY13_CHANNEL_3 ) == PROXIMITY13_CHANNEL_3 )
    {
        chn_val->channel_3 = read_channel_val( ctx, chn_reses.channel_3_res );
    }
    else
    {
        chn_val->channel_3 = 0;
    }

    if ( ( enabled & PROXIMITY13_CHANNEL_4 ) == PROXIMITY13_CHANNEL_4 )
    {
        chn_val->channel_4 = read_channel_val( ctx, chn_reses.channel_4_res );
    }
    else
    {
        chn_val->channel_4 = 0;
    }

        if ( ( enabled & PROXIMITY13_CHANNEL_5 ) == PROXIMITY13_CHANNEL_5 )
    {
        chn_val->channel_5 = read_channel_val( ctx, chn_reses.channel_5_res );
    }
    else
    {
        chn_val->channel_5 = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void channel_resolution ( uint8_t chn_num, uint8_t chn_res )
{
    switch ( chn_num )
    {
        case CHANNEL_0:
        {
            if ( chn_res == PROXIMITY13_ADC_POST_RESOLUTION_24 )
            {
                chn_reses.channel_0_res = RESOLUTION_24_BIT;
            }
            else
            {
                chn_reses.channel_0_res = RESOLUTION_16_BIT;
            }
            break;
        }
        case CHANNEL_1:
        {
            if ( chn_res == PROXIMITY13_ADC_POST_RESOLUTION_24 )
            {
                chn_reses.channel_1_res = RESOLUTION_24_BIT;
            }
            else
            {
                chn_reses.channel_1_res = RESOLUTION_16_BIT;
            }
            break;
        }
        case CHANNEL_2:
        {
            if ( chn_res == PROXIMITY13_ADC_POST_RESOLUTION_24 )
            {
                chn_reses.channel_2_res = RESOLUTION_24_BIT;
            }
            else
            {
                chn_reses.channel_2_res = RESOLUTION_16_BIT;
            }
            break;
        }
        case CHANNEL_3:
        {
            if ( chn_res == PROXIMITY13_ADC_POST_RESOLUTION_24 )
            {
                chn_reses.channel_3_res = RESOLUTION_24_BIT;
            }
            else
            {
                chn_reses.channel_3_res = RESOLUTION_16_BIT;
            }
            break;
        }
        case CHANNEL_4:
        {
            if ( chn_res == PROXIMITY13_ADC_POST_RESOLUTION_24 )
            {
                chn_reses.channel_4_res = RESOLUTION_24_BIT;
            }
            else
            {
                chn_reses.channel_4_res = RESOLUTION_16_BIT;
            }
            break;
        }
        case CHANNEL_5:
        {
            if ( chn_res == PROXIMITY13_ADC_POST_RESOLUTION_24 )
            {
                chn_reses.channel_5_res = RESOLUTION_24_BIT;
            }
            else
            {
                chn_reses.channel_5_res = RESOLUTION_16_BIT;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

static uint32_t read_channel_val ( proximity13_t *ctx, uint8_t chn_res )
{
    uint32_t temp_val;

    switch ( chn_res )
    {
        case RESOLUTION_24_BIT:
        {
            temp_val = proximity13_generic_read( ctx, start_read_reg );
            start_read_reg++;
            temp_val <<= SHIFT_VAL;

            temp_val |= proximity13_generic_read( ctx, start_read_reg );
            start_read_reg++;
            temp_val <<= SHIFT_VAL;

            temp_val |= proximity13_generic_read( ctx, start_read_reg );
            start_read_reg++;

            return temp_val;
        }
        case RESOLUTION_16_BIT:
        {
            temp_val = proximity13_generic_read( ctx, start_read_reg );
            start_read_reg++;
            temp_val <<= SHIFT_VAL;

            temp_val = proximity13_generic_read( ctx, start_read_reg );
            start_read_reg++;

            return temp_val;
        }
        default:
        {
            return 0;
        }
    }
}

// ------------------------------------------------------------------------- END


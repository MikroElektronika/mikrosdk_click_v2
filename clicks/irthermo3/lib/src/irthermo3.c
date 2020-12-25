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

#include "irthermo3.h"
#include "math.h"

// ------------------------------------------------------------- PRIVATE MACROS 

// Calculation constants

#define EMISSIVITY_FACTOR   1.0
#define TO_DUT              25.0
#define TO_0                25.0
#define TA_0                25.0

// Bit manipuolation constants

#define IRTHERMO3_SAVE_LOWER_BYTE           0x00FF
#define IRTHERMO3_SAVE_UPPER_BYTE           0xFF00
#define IRTHERMO3_CTRL_REG_MODE_BITS        0x0003
#define IRTHERMO3_CTRL_REG_SOC_BIT          0x0008
#define IRTHERMO3_EEPROM_BUSY_BIT           0x0200
#define IRTHERMO3_CYCLE_POS_BITS            0x007C

#define IRTHERMO3_APSOLUTE_ZERO_DIF      273.15
#define IRTHERMO3_MESUREMENT_ODD         1
#define IRTHERMO3_MESUREMENT_EVEN        2

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t irthermo3_get_status ( irthermo3_t *ctx );

static uint8_t irthermo3_get_cycle ( irthermo3_t *ctx );

static uint8_t irthermo3_get_mode ( irthermo3_t *ctx );

static void irthermo3_set_soc_bit ( irthermo3_t *ctx );

static uint8_t irthermo3_eeprom_busy ( irthermo3_t *ctx );

static void irthermo3_wait_for_eeprom( irthermo3_t *ctx , uint16_t t_out_ms );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irthermo3_cfg_setup ( irthermo3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = IRTHERMO3_DEV_ADR_GND;
}

IRTHERMO3_RETVAL irthermo3_init ( irthermo3_t *ctx, irthermo3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return IRTHERMO3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return IRTHERMO3_OK;
}

void irthermo3_generic_write ( irthermo3_t *ctx, uint16_t reg, 
                               uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = ( reg & IRTHERMO3_SAVE_UPPER_BYTE ) >> 8;
    tx_buf[ 1 ] = ( reg & IRTHERMO3_SAVE_LOWER_BYTE );
    
    for ( cnt = 2; cnt <= len+1; cnt++ )
    {
        tx_buf[ cnt ] = *data_buf; 
        data_buf++; 
    } 

    i2c_master_write( &ctx->i2c, tx_buf, len + 2 );  
}

void irthermo3_generic_read ( irthermo3_t *ctx, uint16_t reg, 
                              uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( reg & IRTHERMO3_SAVE_UPPER_BYTE ) >> 8;
    tx_buf[ 1 ] = ( reg & IRTHERMO3_SAVE_LOWER_BYTE );

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_buf, len );
}

void irthermo3_write_u16 ( irthermo3_t *ctx, uint16_t reg, uint16_t wr_data )
{
    uint8_t tx_buf[ 4 ];
    tx_buf[ 3 ] = ( wr_data & IRTHERMO3_SAVE_UPPER_BYTE ) >> 8;
    tx_buf[ 2 ] = ( wr_data & IRTHERMO3_SAVE_LOWER_BYTE );
    tx_buf[ 0 ] = ( reg & IRTHERMO3_SAVE_UPPER_BYTE ) >> 8;
    tx_buf[ 1 ] = ( reg & IRTHERMO3_SAVE_LOWER_BYTE );

    i2c_master_write( &ctx->i2c, tx_buf, 4 );     
}

int16_t irthermo3_read_i16 ( irthermo3_t *ctx, uint16_t reg )
{
    uint8_t reg_buf[ 2 ];
    uint8_t rx_buff[ 2 ];
    int16_t ret_val = 0;
    
    reg_buf[ 0 ] = ( reg & IRTHERMO3_SAVE_UPPER_BYTE ) >> 8;
    reg_buf[ 1 ] = ( reg & IRTHERMO3_SAVE_LOWER_BYTE ); 

    i2c_master_write_then_read( &ctx->i2c, reg_buf, 2, rx_buff, 2 );

    ret_val = rx_buff[ 0 ];
    ret_val <<= 8;
    ret_val |= rx_buff[ 1 ];

    return ret_val;
}

int32_t irthermo3_read_i32 ( irthermo3_t *ctx, uint16_t reg )
{
    uint8_t reg_buf[ 2 ];
    uint8_t rx_buff[ 4 ];
    int32_t ret_val = 0;
    
    reg_buf[ 0 ] = ( reg & IRTHERMO3_SAVE_UPPER_BYTE ) >> 8;
    reg_buf[ 1 ] = ( reg & IRTHERMO3_SAVE_LOWER_BYTE ); 

    i2c_master_write_then_read( &ctx->i2c, reg_buf, 2, rx_buff, 4 );
    
    ret_val = rx_buff[ 2 ];
    ret_val <<= 8;
    ret_val |= rx_buff[ 3 ];
    ret_val <<= 8;
    ret_val |= rx_buff[ 0 ];
    ret_val <<= 8;
    ret_val |= rx_buff[ 1 ];

    return ret_val;
}

void irthermo3_global_write ( irthermo3_t *ctx, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    for ( cnt = 0; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = *data_buf; 
        data_buf++; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len );   
}

void irthermo3_set_mode( irthermo3_t *ctx, uint8_t mode )
{    
    uint16_t reg  = irthermo3_read_i16( ctx, IRTHERMO3_REG_CONTROL );
    reg &= ~(0x0003 << 1); //Clear the mode bits
    reg |= (mode << 1);
    irthermo3_write_u16( ctx, IRTHERMO3_REG_CONTROL, reg );
}

void irthermo3_cal ( irthermo3_t *ctx )
{
    int32_t i32_data;
    int16_t i16_data;
   
    irthermo3_wait_for_eeprom( ctx, 750 );
    irthermo3_set_mode( ctx, 0x02 );
    
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_P_R_LSW );
    ctx->cal_coef.p_r = i32_data * 0.00390625;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_P_G_LSW );
    ctx->cal_coef.p_g = i32_data * 0.000000953;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_P_T_LSW );
    ctx->cal_coef.p_t = i32_data * 5.6843418860808015E-14;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_P_O_LSW );
    ctx->cal_coef.p_o = i32_data * 0.00390625;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_EA_LSW );
    ctx->cal_coef.ea = i32_data * 0.00001525;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_EB_LSW );
    ctx->cal_coef.eb = i32_data * 0.00390625;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_FA_LSW );
    ctx->cal_coef.fa = i32_data * 1.4210854715202004E-14;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_FB_LSW );
    ctx->cal_coef.fb = i32_data * 1.4551915228366852E-11;
    i32_data = irthermo3_read_i32( ctx, IRTHERMO3_EEPROM_CAL_CONST_GA_LSW );
    ctx->cal_coef.ga = i32_data * 1.4551915228366852E-11;
    i16_data = irthermo3_read_i16( ctx, IRTHERMO3_EEPROM_CAL_CONST_GB );
    ctx->cal_coef.gb = i16_data * 0.0009765625;
    i16_data = irthermo3_read_i16( ctx, IRTHERMO3_EEPROM_CAL_CONST_KA );
    ctx->cal_coef.ka = i16_data * 0.0009765625;
    i16_data = irthermo3_read_i16( ctx, IRTHERMO3_EEPROM_CAL_CONST_HA_COSTUMER );
    ctx->cal_coef.ha = i16_data * 0.000061035;
    i16_data = irthermo3_read_i16( ctx, IRTHERMO3_EEPROM_CAL_CONST_HB_COSTUMER );
    ctx->cal_coef.hb = i16_data * 0.000061035;
   
    irthermo3_set_mode( ctx, 0x06 );
}

float irthermo3_get_ambient_temperature ( irthermo3_t *ctx )
{
    uint8_t mode;
    int16_t ram6;
    int16_t ram9;
    float vr_ta;
    float amb;
    float ambient_temp;

    mode = irthermo3_get_mode( ctx );
    
    if ( mode != IRTHERMO3_MODE_CONTINOUS )
    {
        irthermo3_set_soc_bit( ctx );
    }
   
    ram6 = irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_6 );
    ram9 = irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_9 );

    vr_ta = ram9;
    vr_ta += ctx->cal_coef.gb * ( ram6 / 12.0 );
    
    amb = ram6 / 12.0;
    amb /= vr_ta;
    amb *= 524288;
    
    ambient_temp = ctx->cal_coef.p_o;
    ambient_temp += ( amb - ctx->cal_coef.p_r ) / ctx->cal_coef.p_g;
    ambient_temp += ctx->cal_coef.p_t * ( amb - ctx->cal_coef.p_r )
                                      * ( amb - ctx->cal_coef.p_r );
   
    return ambient_temp;
}

float irthermo3_get_object_temperature ( irthermo3_t *ctx )
{
    uint8_t mode;
    uint8_t cyc_pos;
    int16_t sc_1;
    int16_t sc_2;
    int16_t ram6;
    int16_t ram9;
    float vr_ta;
    float amb;
    float to;
    float to_clc1;
    float to_clc;
    float ta;
    float vr_to;
    float s_to;
    float ta_dut;
    float ta_dut_k;

    mode = irthermo3_get_mode( ctx );
    
    if ( mode != IRTHERMO3_MODE_CONTINOUS )
    {
        irthermo3_set_soc_bit( ctx );
    }
   
    sc_1 = irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_4 );
    sc_1 += irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_5 );
    sc_1 /= 2;
   
    sc_2 = irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_7 );
    sc_2 += irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_8 );
    sc_2 /= 2;
   
    ram6 = irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_6 );
    ram9 = irthermo3_read_i16( ctx, IRTHERMO3_RAW_DATA_9 );
   
    vr_ta = ram9 + ctx->cal_coef.gb * ( ram6 / 12.0 );
    
    amb = ram6 / 12.0;
    amb /= vr_ta;
    amb *= 524288;
    
    ta = irthermo3_get_ambient_temperature( ctx );
   
    vr_to = ram9;
    vr_to += ctx->cal_coef.ka * ( ram6 / 12 );
   
    cyc_pos = irthermo3_get_cycle( ctx );
   
    if( cyc_pos == IRTHERMO3_MESUREMENT_EVEN )
    {
       s_to = sc_2 / 12;
       s_to /= vr_to;
       s_to *= 524288;
    }
    else
    {
       s_to = sc_1 / 12;
       s_to /= vr_to;
       s_to *= 524288;
    }
    
    ta_dut = amb - ctx->cal_coef.eb;
    ta_dut /= ctx->cal_coef.ea;
    ta_dut += 25.0;
    ta_dut_k = ta_dut;
    ta_dut_k += IRTHERMO3_APSOLUTE_ZERO_DIF;

    to_clc = EMISSIVITY_FACTOR;
    to_clc *= ctx->cal_coef.fa;
    
    to_clc1 = EMISSIVITY_FACTOR;
    to_clc1 += ctx->cal_coef.ga * ( ta - TO_0 );
    to_clc1 += ctx->cal_coef.fb * ( ta_dut - TA_0 );
    
    to = s_to / ( to_clc * to_clc1 );
    to = to + ( ta_dut_k * ta_dut_k * ta_dut_k * ta_dut_k );
    to = pow( to, 0.25 );
    to = to - IRTHERMO3_APSOLUTE_ZERO_DIF - ctx->cal_coef.hb;
   
    return to;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t irthermo3_get_status ( irthermo3_t *ctx )
{
    uint16_t ret_val;
    ret_val = irthermo3_read_i16( ctx, IRTHERMO3_REG_STATUS );
    return ret_val;
}

static uint8_t irthermo3_get_cycle ( irthermo3_t *ctx )
{
    uint16_t ret_val;
    
    ret_val = irthermo3_get_status( ctx );
    ret_val &= IRTHERMO3_CYCLE_POS_BITS;
    ret_val >>= 2;
    
    return ( uint8_t )ret_val;
}

static uint8_t irthermo3_get_mode ( irthermo3_t *ctx )
{
    uint16_t mode;
    
    mode = irthermo3_read_i16( ctx, IRTHERMO3_REG_CONTROL );
    mode >>= 1;
    mode &= IRTHERMO3_CTRL_REG_MODE_BITS;
    
    return ( uint8_t )mode;
}

static void irthermo3_set_soc_bit ( irthermo3_t *ctx )
{
    uint16_t reg = irthermo3_read_i16( ctx, IRTHERMO3_REG_CONTROL );
    reg |= IRTHERMO3_CTRL_REG_SOC_BIT;
    irthermo3_write_u16( ctx, IRTHERMO3_REG_CONTROL, reg );
}

static uint8_t irthermo3_eeprom_busy ( irthermo3_t *ctx )
{
    return ( ( uint16_t )( irthermo3_get_status( ctx ) >> 
                        IRTHERMO3_EEPROM_BUSY_BIT ) & 1 );
}

static void irthermo3_wait_for_eeprom( irthermo3_t *ctx , uint16_t t_out_ms )
{
    uint16_t n_cnt = 0;
    
    while ( irthermo3_eeprom_busy( ctx ) )
    {
        Delay_1ms();
        n_cnt++;
        if ( n_cnt > t_out_ms )
        {
            return;
        }
    }
}

// ------------------------------------------------------------------------- END


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

#include "proximity5.h"

// ------------------------------------------------------------------ VARIABLES

als_conf1_t ALS_CONF1 = { 0 };
als_conf2_t ALS_CONF2 = { 0 };
als_thdh_l_m_t ALS_THDH_L_M = { 0 };
als_thdl_l_m_t ALS_THDL_L_M = { 0 };
ps_conf1_t PS_CONF1 = { 0 };
ps_conf2_t PS_CONF2 = { 0 };
ps_conf3_t PS_CONF3 = { 0 };
ps_ms_t PS_MS = { 0 };
ps_canc_l_m_t PS_CANC_L_M = { 0 };
ps_thdl_l_m_t PS_THDL_L_M = { 0 };
ps_thdh_l_m_t PS_THDH_L_M = { 0 };
ps1_data_l_m_t PS1_DATA_L_M = { 0 };
ps2_data_l_m_t PS2_DATA_L_M = { 0 };
ps3_data_l_m_t PS3_DATA_L_M = { 0 };
als_data_l_m_t ALS_DATA_L_M = { 0 };
white_data_l_m_t WHITE_DATA_L_M = { 0 };
int_flag_t INT_FLAG = { 0 };
id_l_m_t ID_L_M = { 0 };

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity5_cfg_setup ( proximity5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY5_ADDR;
}

PROXIMITY5_RETVAL proximity5_init ( proximity5_t *ctx, proximity5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );


    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY5_OK;
}

void proximity5_default_cfg ( proximity5_t *ctx )
{
    uint8_t w_temp[ 2 ];

    PS_CONF1.PS_SD = PS_SD_ON;
    PS_CONF1.PS_IT = PS_IT_8T;
    PS_CONF1.PS_PERS = PS_PERS_2;
    PS_CONF1.PS_DUTY = PS_DUTY_1_160;

    PS_CONF2.PS_INT_EN = PS_INT_DIS;
    PS_CONF2.PS_NS = PS_NS_TWO_STEP;
    PS_CONF2.PS_HD = PS_HD_16BIT;
    PS_CONF2.PS_GAIN = PS_GAIN_SINGLX1;
    PS_CONF2.GEST_MODE = GEST_MODE_EN;
    PS_CONF2.GEST_INTEN = GEST_INT_EN;

    w_temp[ 0 ] = PS_CONF1.ALL;
    w_temp[ 1 ] = PS_CONF2.ALL;

    proximity5_generic_write( ctx, CMD_PS_CONF1_2, w_temp, 2 );

    PS_CONF3.PS_SC_EN = PS_SC_EN_OFF;
    PS_CONF3.PS_MS = PS_MS_INT;
    PS_CONF3.PS_TRIG = PS_TRIG_EN;
    PS_CONF3.PS_AF = PS_AF_EN;
    PS_CONF3.PS_SMART_PERS = PS_SMART_PERS_EN;
    PS_CONF3.IRED_SEL = IRED_SEL_IRED1;
    PS_CONF3.LED_I_LOW = LED_I_LOW_DIS;

    PS_MS.LED_I = LED_I_50MA;
    PS_MS.PS_SPO = PS_SPO_00h;
    PS_MS.PS_SP = PS_SP_TYP;
    PS_MS.PS_SC_CUR = PS_SC_CUR_1X;


    w_temp[ 0 ] = PS_CONF1.ALL;
    w_temp[ 1 ] = PS_CONF2.ALL;

    proximity5_generic_write( ctx, CMD_PS_CONF1_2, w_temp, 2 );
}

void proximity5_generic_write ( proximity5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void proximity5_generic_read ( proximity5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t proximity5_read_reg ( proximity5_t *ctx, uint8_t addr )
{
    uint8_t temp[ 2 ];
    uint16_t temp1;

    proximity5_generic_read( ctx, addr, temp, 2 );
    
    temp1 =  temp[ 0 ];
    temp1 |= temp[ 1 ] << 8;

    return temp1;
}

uint16_t proximity5_get_id ( proximity5_t *ctx )
{
    uint16_t temp_b;

    temp_b = proximity5_read_reg( ctx, CMD_ID_L_M );

    return temp_b;
}

void proximity5_get_values ( proximity5_t *ctx, uint16_t *prox_val )
{
    static uint16_t ps_array[ 3 ] = { 0 , 0 ,0 };

    uint16_t *data_ptr;
    uint8_t w_temp[ 2 ];
    uint8_t pin_test;

    data_ptr = prox_val;

    PS_CONF3.PS_SC_EN = PS_SC_EN_OFF;
    PS_CONF3.PS_MS = PS_MS_INT;
    PS_CONF3.PS_TRIG = PS_TRIG_EN;
    PS_CONF3.PS_AF = PS_AF_EN;
    PS_CONF3.PS_SMART_PERS = PS_SMART_PERS_EN;
    PS_CONF3.IRED_SEL = IRED_SEL_IRED1;
    PS_CONF3.LED_I_LOW = LED_I_LOW_DIS;

    PS_MS.LED_I = LED_I_200MA;
    PS_MS.PS_SPO = PS_SPO_00h;
    PS_MS.PS_SP = PS_SP_TYP;
    PS_MS.PS_SC_CUR = PS_SC_CUR_1X;

    w_temp[ 0 ] = PS_CONF3.ALL;
    w_temp[ 1 ] = PS_MS.ALL;

    proximity5_generic_write( ctx, CMD_PS_CONF3_MS, w_temp, 2 );

    if ( PS_CONF2.GEST_INTEN == GEST_INT_EN )  
    {
        do
        {
            pin_test = digital_in_read( &ctx->int_pin );

        } while( pin_test == 1 );                  
    
    }
    
    ps_array[ 0 ] = proximity5_read_reg( ctx, CMD_INT_FLAG );   
    INT_FLAG.ALL = ( uint8_t )( ps_array[ 0 ] >> 8 );           

    if ( INT_FLAG.GEST_DATA_RDY_FLG == 1 )
    {                                    
        data_ptr[ 0 ] = proximity5_read_reg( ctx, CMD_PS1_DATA_L_M );
        data_ptr[ 1 ] = proximity5_read_reg( ctx, CMD_PS2_DATA_L_M );
        data_ptr[ 2 ] = proximity5_read_reg( ctx, CMD_PS3_DATA_L_M );
    }
}

// ------------------------------------------------------------------------- END


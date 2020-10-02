/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright ( c ) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "smartbuck.h"

// ------------------------------------------------------------------ CONSTANTS

const float res_sh[ 4 ] = { 0.11, 0.11, 0.05, 0.11 };

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void smartbuck_cfg_setup ( smartbuck_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en1 = HAL_PIN_NC;
    cfg->en2   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address_eeprom = SMARTBUCK_EEPROM_SLAVE_000;
    cfg->i2c_address_mcp4661 = SMARTBUCK_MCP4661_SLAVE_000;
    cfg->i2c_address_pac1934 = SMARTBUCK_PAC1934_SLAVE_0;
}

SMARTBUCK_RETVAL smartbuck_init ( smartbuck_t *ctx, smartbuck_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_eeprom = cfg->i2c_address_eeprom;
    ctx->slave_mcp4661 = cfg->i2c_address_mcp4661;
    ctx->slave_pac1934 = cfg->i2c_address_pac1934;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SMARTBUCK_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->en1, cfg->en1 );
    digital_out_init( &ctx->en2, cfg->en2 );
    digital_out_init( &ctx->pwm, cfg->pwm );

    // Input pins

    digital_in_init( &ctx->pg, cfg->pg );
    
    return SMARTBUCK_OK;
}

void smartbuck_default_cfg ( smartbuck_t *ctx )
{
    ctx->enabled_chann = SMARTBUCK_ALL_CHANN_ON;
    ctx->data_form = SMARTBUCK_ALL_DATA_UNSIGN_FORM;
    ctx->data_select = SMARTBUCK_SAMPL_DATA_MODE;
}

uint8_t smartbuck_write_eeprom ( smartbuck_t *ctx, uint8_t eeprom_addr, uint8_t data_in )
{
    uint8_t temp_data[ 2 ];

    if ( eeprom_addr & 0xF0 )
    {
        return 1;
    } 

    temp_data[ 0 ] = eeprom_addr;
    temp_data[ 1 ] = data_in;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_write( &ctx->i2c, temp_data, 2 );  
    
    return 0;
}

uint8_t smartbuck_read_eeprom ( smartbuck_t *ctx, uint8_t eeprom_addr, uint8_t *data_out )
{
    uint8_t tx_buf[ 1 ];
   
    if ( eeprom_addr & 0xF0 )
    {
        return 1;
    }
    
    tx_buf[ 0 ] = eeprom_addr;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, 1 );
    
    return 0;
}

uint8_t smartbuck_read_seq_eeprom ( smartbuck_t *ctx, uint8_t eeprom_addr, uint8_t *data_out, uint8_t n_bytes)
{
    uint8_t tx_buf[ 1 ];    
    
    if ( eeprom_addr & 0xF0 )
    {
        return 1;
    }
    
    tx_buf[ 0 ] = eeprom_addr;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, n_bytes );
    
    return 0;
}

uint8_t smartbuck_write_pot ( smartbuck_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( reg_addr & 0xF0 )
    {
        return 1;
    }
    if ( data_in & 0xFE00 )
    {
        return 2;
    }
    
    temp_data[ 0 ] = reg_addr << 4;
    temp_data[ 0 ] |= data_in >> 8;
    temp_data[ 1 ] = data_in;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_mcp4661 );
    i2c_master_write( &ctx->i2c, temp_data, 2 );   
    
    return 0;
}

uint8_t smartbuck_read_pot ( smartbuck_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t temp_data[ 1 ];
    uint8_t read_data[ 2 ];
    
    if ( reg_addr & 0xF0 )
    {
        return 1;
    }
    
    temp_data[ 0 ] = reg_addr << 4;
    temp_data[ 0 ] |= SMARTBUCK_POT_READ_CMND;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_mcp4661 );    
    i2c_master_write_then_read( &ctx->i2c, temp_data, 1, read_data, 2 );

    *data_out = read_data[ 0 ];
    *data_out <<= 8;
    *data_out |= read_data[ 1 ];
    
    return 0;
}

uint8_t smartbuck_incr_pot ( smartbuck_t *ctx, uint8_t wiper_sel, uint16_t steps )
{
    uint8_t comm_data;
    uint8_t temp_data[ 256 ];
    uint16_t count;
    
    if ( ( steps > 256) || ( steps < 1 ) )
    {
        return 1;
    }
    
    if ( wiper_sel == 0 )
    {
        comm_data = SMARTBUCK_POT_INCR_CMND;
    }
    else if ( wiper_sel == 1 )
    {
        comm_data = SMARTBUCK_POT_INCR_CMND | ( SMARTBUCK_WIPER1_SEL << 4 );
    }
    else
    {
        return 2;
    }
    
    for ( count = 0; count < steps; count++ )
    {
        temp_data[ count ] = comm_data;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_mcp4661 );
    i2c_master_write( &ctx->i2c, temp_data, steps );  
    
    return 0;
}

uint8_t smartbuck_decr_pot ( smartbuck_t *ctx, uint8_t wiper_sel, uint16_t steps )
{
    uint8_t comm_data;
    uint8_t temp_data[ 256 ];
    uint16_t count;

    if ( ( steps > 256) || ( steps < 1 ) )
    {
        return 1;
    }

    if ( wiper_sel == 0 )
    {
        comm_data = SMARTBUCK_POT_DECR_CMND;
    }
    else if ( wiper_sel == 1 )
    {
        comm_data = SMARTBUCK_POT_DECR_CMND | ( SMARTBUCK_WIPER1_SEL << 4 );
    }
    else
    {
        return 2;
    }

    for ( count = 0; count < steps; count++ )
    {
        temp_data[ count ] = comm_data;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_mcp4661 );
    i2c_master_write( &ctx->i2c, temp_data, steps ); 

    return 0;
}

void smartbuck_en_regulator1 ( smartbuck_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->en1 );
    }
    else
    {
        digital_out_low( &ctx->en1 );
    }
}

void smartbuck_en_regulator2 ( smartbuck_t *ctx,  uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->en2 );
    }
    else
    {
        digital_out_low( &ctx->en2 );
    }
}

void smartbuck_force_pwm_mode ( smartbuck_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->pwm );
    }
    else
    {
        digital_out_low( &ctx->pwm );
    }
}

uint8_t smartbuck_check_diagnostic ( smartbuck_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

uint8_t smartbuck_send_cmd_pac ( smartbuck_t *ctx, uint8_t command )
{
    uint8_t tx_buf[ 1 ];
    
    if ( ( command != SMARTBUCK_REFRESH_CMND) && ( command != SMARTBUCK_REFRESH_G_CMND ) && ( command != SMARTBUCK_REFRESH_V_CMND ) )
    {
        return 1;
    }
    
    tx_buf[ 0 ] = command;
    
    if ( tx_buf[ 0 ] == SMARTBUCK_REFRESH_G_CMND )
    {
        i2c_master_set_slave_address( &ctx->i2c, SMARTBUCK_PAC_GENERAL_CALL_SLAVE );
        i2c_master_write( &ctx->i2c, tx_buf, 1 );  
    }
    else
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_pac1934 );
        i2c_master_write( &ctx->i2c, tx_buf, 1 ); 
    }
    
    return 0;
}

uint8_t smartbuck_write_pac ( smartbuck_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( ( reg_addr > 0x20 ) || ( ( reg_addr < 0x1C ) && ( reg_addr != 0x01 ) ) || ( reg_addr == 0x1E ) || ( reg_addr == 0x1F ) )
    {
        return 1;
    }
    
    temp_data[ 0 ] = reg_addr;
    temp_data[ 1 ] = data_in;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_pac1934 );
    i2c_master_write( &ctx->i2c, temp_data, 2 ); 
    
    return 0;
}

uint8_t smartbuck_read_pac ( smartbuck_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{
    uint8_t tx_buf[ 1 ];
    
    if ( ( ( reg_addr > 0x26) && ( reg_addr < 0xFD ) ) || ( ( reg_addr < 0x1C ) && ( reg_addr != 0x01 ) ) || ( reg_addr == 0x1E ) || ( reg_addr == 0x1F ) )
    {
        return 1;
    }
    
    tx_buf[ 0 ] = reg_addr;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_pac1934 );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, 1 );
    
    return 0;
}

uint8_t smartbuck_set_addr_ptr_pac ( smartbuck_t *ctx, uint8_t reg_addr )
{
    uint8_t tx_buf[ 1 ];
    
    if ( ( ( reg_addr > 0x26) && ( reg_addr < 0xFD ) ) || ( reg_addr < 0x01 ) || ( reg_addr == 0x1E ) || ( reg_addr == 0x1F ) )
    {
        return 1;
    }
    
    tx_buf [ 0 ] = reg_addr;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_pac1934 );
    i2c_master_write( &ctx->i2c, tx_buf, 1 );  
    
    return 0;
}

void smartbuck_receive_byte_pac ( smartbuck_t *ctx, uint8_t *data_out )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_pac1934 );
    i2c_master_read( &ctx->i2c, data_out, 1 );
}

uint8_t smartbuck_block_read_pac ( smartbuck_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t tx_buf [ 1 ];

    if ( ( reg_addr > 0x1A) || ( reg_addr < 0x02) || ( reg_addr == 0x1E ) || ( reg_addr == 0x1F ) )
    {
        return 1;
    }
    
    tx_buf[ 0 ] = reg_addr;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_pac1934 );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, n_bytes );
    
    return 0;
}

uint8_t smartbuck_set_config_pac ( smartbuck_t *ctx, uint8_t en_chann, uint8_t data_format, uint8_t data_sel )
{
    uint8_t tmp_data;
    
    if ( en_chann & 0x0F )
    {
        return 1;
    }
    if ( data_sel > 1 )
    {
        return 2;
    }
    
    tmp_data = en_chann;
    smartbuck_write_pac( ctx, SMARTBUCK_PAC_CHANN_DIS_REG, tmp_data );
    
    tmp_data = data_format;
    smartbuck_write_pac( ctx, SMARTBUCK_PAC_NEG_PWR_REG, tmp_data );
    
    ctx->enabled_chann = en_chann;
    ctx->data_form = data_format;
    ctx->data_select = data_sel;
    
    return 0;
}

void smartbuck_get_data ( smartbuck_t *ctx,  float *voltage, float *current, float *power )
{
    uint8_t count;
    uint8_t indx;
    uint8_t tmp_data[ 2 ];
    uint16_t u_ret_val;
    int16_t s_ret_val;
    uint8_t tmp1;
    uint8_t tmp2;
    uint8_t chann_addr;
    
    tmp1 = 0x80;
    tmp2 = 0x08;
    indx = 0;
    
    if ( ctx->data_select == SMARTBUCK_SAMPL_DATA_MODE )
    {
        chann_addr = SMARTBUCK_PAC_VBUS1_REG;
    }
    else
    {
        chann_addr = SMARTBUCK_PAC_VBUS1_AVG_REG;
    }
    
    for ( count = 0; count < 4; count++ )
    {
        if ( ( ctx->enabled_chann & tmp1 ) == 0 )
        {
            smartbuck_block_read_pac( ctx, chann_addr + count, tmp_data, 2 );
            
            if ( ctx->data_form & tmp2)
            {
                s_ret_val = tmp_data[ 0 ];
                s_ret_val <<= 8;
                s_ret_val |= tmp_data[ 1 ];
                voltage[ indx ] = s_ret_val;
                voltage[ indx ] /= 32767;
            }
            else
            {
                u_ret_val = tmp_data[ 0 ];
                u_ret_val <<= 8;
                u_ret_val |= tmp_data[ 1 ];
                voltage[ indx ] = u_ret_val;
                voltage[ indx ] /= 65535;
            }
            voltage[ indx ] *= 32;
            
            smartbuck_block_read_pac( ctx, chann_addr + 4 + count, tmp_data, 2 );

            if ( ctx->data_form & tmp1 )
            {
                s_ret_val = tmp_data[ 0 ];
                s_ret_val <<= 8;
                s_ret_val |= tmp_data[ 1 ];
                current[ indx ] = s_ret_val;
                current[ indx ] /= 32767;
            }
            else
            {
                u_ret_val = tmp_data[ 0 ];
                u_ret_val <<= 8;
                u_ret_val |= tmp_data[ 1 ];
                current[ indx ] = u_ret_val;
                current[ indx ] /= 65535;
            }
            current[ indx ] *= 100;
            current[ indx ] /= res_sh[ count ];
            
            power[ indx ] = voltage[ indx ] * current[ indx ];
            indx++;
        }
        tmp1 >>= 1;
        tmp2 >>= 1;
    }
}

// ------------------------------------------------------------------------- END


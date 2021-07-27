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

#include "spectrometer.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void spectrometer_cfg_setup ( spectrometer_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SPECTROMETER_I2C_DEV_ADR;
}

SPECTROMETER_RETVAL spectrometer_init ( spectrometer_t *ctx, spectrometer_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SPECTROMETER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPECTROMETER_OK;
}

void spectrometer_generic_write ( spectrometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void spectrometer_generic_read ( spectrometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

// Set the power on bit
void spectrometer_pon ( spectrometer_t *ctx )
{
    uint8_t reg_val;
    
    spectrometer_generic_read( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );

    reg_val &= 0xFE;
    reg_val |= SPECTROMETER_EN_PON;

    spectrometer_generic_write( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );
    Delay_500us( );
}

// Set the spectral measurement enabled bit
void spectrometer_sp_en ( spectrometer_t *ctx, uint8_t state )
{
    uint8_t reg_val;
    spectrometer_generic_read( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );
    if ( state == 1 )
    {
        reg_val |= SPECTROMETER_EN_SP_EN;
    }
    else
    {
        reg_val &= 0xFD;
    }
    spectrometer_generic_write( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );
}

// Starting the SMUX command
void spectrometer_smux_en ( spectrometer_t *ctx )
{
    uint8_t reg_val;

    spectrometer_generic_read( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );
    reg_val &= 0xEF;
    reg_val |= 0x10;
    spectrometer_generic_write( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );
}

// Reading and Polling the the SMUX Enable bit
uint8_t spectrometer_get_smux_en ( spectrometer_t *ctx )
{
  uint8_t smux_stat = 0;
  uint8_t reg_val;
  spectrometer_generic_read( ctx, SPECTROMETER_ENABLE, &reg_val, 1 );

    if ( ( reg_val & SPECTROMETER_EN_SMUXEN ) == SPECTROMETER_EN_SMUXEN )
    {
        smux_stat = 1;
    }

    return smux_stat;
}

// Reading and Polling the the AVALID bit
uint8_t spectrometer_get_data_ready ( spectrometer_t *ctx )
{
    uint8_t reg_val;
    spectrometer_generic_read( ctx, SPECTROMETER_STAT_2, &reg_val, 1 );

    if ( ( reg_val & SPECTROMETER_STAT_2_AVALID ) == SPECTROMETER_STAT_2_AVALID )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// SMUX Config for F1,F2,F3,F4,NIR,Clear
void spectrometer_f1f4_clr_nir ( spectrometer_t *ctx )
{
    uint8_t write_data;

    write_data = 0x30;
    spectrometer_generic_write( ctx, 0x00, &write_data, 1 );
    write_data = 0x01;
    spectrometer_generic_write( ctx, 0x01, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x02, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x03, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x04, &write_data, 1 );
    write_data = 0x42;
    spectrometer_generic_write( ctx, 0x05, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x06, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x07, &write_data, 1 );
    write_data = 0x50;
    spectrometer_generic_write( ctx, 0x08, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x09, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0A, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0B, &write_data, 1 );
    write_data = 0x20;
    spectrometer_generic_write( ctx, 0x0C, &write_data, 1 );
    write_data = 0x04;
    spectrometer_generic_write( ctx, 0x0D, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x0E, &write_data, 1 );
    write_data = 0x30;
    spectrometer_generic_write( ctx, 0x0f, &write_data, 1 );
    write_data = 0x01;
    spectrometer_generic_write( ctx, 0x10, &write_data, 1 );
    write_data = 0x50;
    spectrometer_generic_write( ctx, 0x11, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x12, &write_data, 1 );
    write_data = 0x06;
    spectrometer_generic_write( ctx, 0x13, &write_data, 1 );
}

// SMUX Config for F5,F6,F7,F8,NIR,Clear
void spectrometer_f5f8_clr_nir ( spectrometer_t *ctx )
{
    uint8_t write_data;

    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x00, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x01, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x02, &write_data, 1 );
    write_data = 0x40;
    spectrometer_generic_write( ctx, 0x03, &write_data, 1 );
    write_data = 0x02;
    spectrometer_generic_write( ctx, 0x04, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x05, &write_data, 1 );
    write_data = 0x10;
    spectrometer_generic_write( ctx, 0x06, &write_data, 1 );
    write_data = 0x03;
    spectrometer_generic_write( ctx, 0x07, &write_data, 1 );
    write_data = 0x50;
    spectrometer_generic_write( ctx, 0x08, &write_data, 1 );
    write_data = 0x10;
    spectrometer_generic_write( ctx, 0x09, &write_data, 1 );
    write_data = 0x03;
    spectrometer_generic_write( ctx, 0x0A, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x0B, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0C, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0D, &write_data, 1 );
    write_data = 0x24;
    spectrometer_generic_write( ctx, 0x0E, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x0f, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x10, &write_data, 1 );
    write_data = 0x50;
    spectrometer_generic_write( ctx, 0x11, &write_data, 1 );
    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x12, &write_data, 1 );
    write_data = 0x06;
    spectrometer_generic_write( ctx, 0x13, &write_data, 1 );
}

void spectrometer_fd_cfg ( spectrometer_t *ctx )
{
    uint8_t write_data;

    write_data = 0x00;
    spectrometer_generic_write( ctx, 0x00, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x01, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x02, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x03, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x04, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x05, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x06, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x07, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x08, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x09, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0A, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0B, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0C, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0D, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0E, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x0F, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x10, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x11, &write_data, 1 );
    spectrometer_generic_write( ctx, 0x12, &write_data, 1 );
    write_data = 0x60;
    spectrometer_generic_write( ctx, 0x13, &write_data, 1 );
}

// Select Register bank
void spectrometer_reg_bank_cfg ( spectrometer_t *ctx, uint8_t reg_bank )
{
    uint8_t reg_val;
    spectrometer_generic_read( ctx,  SPECTROMETER_CFG_0, &reg_val, 1 );

    reg_val &= 0xEF;
    reg_val |= reg_bank;
    spectrometer_generic_write( ctx, SPECTROMETER_CFG_0, &reg_val, 1 );
}

// Default configuration
void spectrometer_def_cfg ( spectrometer_t *ctx )
{
    uint8_t write_data;

    write_data = 0x64;
    spectrometer_generic_write( ctx, SPECTROMETER_ATIME, &write_data, 1 );
    write_data = 0xE7;
    spectrometer_generic_write( ctx, SPECTROMETER_ASTEP_L, &write_data, 1 );
    write_data = 0x03;
    spectrometer_generic_write( ctx, SPECTROMETER_ASTEP_L, &write_data, 1 );
    write_data = SPECTROMETER_CFG_1_AGAIN_256;
    spectrometer_generic_write( ctx, SPECTROMETER_CFG_1, &write_data, 1 );
}

void spectrometer_raw_rd_val_mode_1 ( spectrometer_t *ctx, uint8_t *adc_data )
{
    uint8_t write_data;
    uint8_t smux_stat = 1;
    uint8_t data_ready = 0;

    spectrometer_pon( ctx );
    write_data = SPECTROMETER_CFG_6_SMUX_CMD_2;
    spectrometer_generic_write( ctx, SPECTROMETER_CFG_6, &write_data, 1 );
    spectrometer_f1f4_clr_nir( ctx );
    spectrometer_smux_en( ctx );

    while( smux_stat != 0 )
    {
        smux_stat = spectrometer_get_smux_en( ctx );
    }

    spectrometer_sp_en( ctx, 1 );

    while ( data_ready != 1 )
    {
        data_ready = spectrometer_get_data_ready( ctx );
    }

    spectrometer_generic_read ( ctx, SPECTROMETER_CH0_ADC_DATA_L, adc_data, 12 );
}

void spectrometer_raw_rd_val_mode_2 ( spectrometer_t *ctx, uint8_t *adc_data )
{
    uint8_t write_data;
    uint8_t smux_stat = 1;
    uint8_t data_ready = 0;

    spectrometer_pon( ctx );
    spectrometer_sp_en( ctx, 0 );
    write_data = SPECTROMETER_CFG_6_SMUX_CMD_2;
    spectrometer_generic_write( ctx, SPECTROMETER_CFG_6, &write_data, 1 );
    spectrometer_f5f8_clr_nir( ctx );
    spectrometer_smux_en( ctx );

    while( smux_stat != 0 )
    {
        smux_stat = spectrometer_get_smux_en( ctx );
    }

    spectrometer_sp_en( ctx, 1 );

    while ( data_ready != 1 )
    {
        data_ready = spectrometer_get_data_ready( ctx );
    }

    spectrometer_generic_read ( ctx, SPECTROMETER_CH0_ADC_DATA_L, adc_data, 12 );
}

uint8_t spectrometer_flicker_detection ( spectrometer_t *ctx )
{
    uint8_t write_data;
    uint8_t smux_stat = 1;
    uint8_t f_val = 0;
    
    write_data = 0x00;
    spectrometer_generic_write( ctx, SPECTROMETER_ENABLE, &write_data, 1 );
    spectrometer_pon( ctx );
    write_data = SPECTROMETER_CFG_6_SMUX_CMD_2;
    spectrometer_generic_write( ctx, SPECTROMETER_CFG_6, &write_data, 1 );
    spectrometer_fd_cfg( ctx );
    spectrometer_smux_en( ctx );

    while( smux_stat != 0 )
    {
        smux_stat = spectrometer_get_smux_en( ctx );
    }

    spectrometer_sp_en( ctx, 1 );

    write_data = 0x41;
    spectrometer_generic_write( ctx, SPECTROMETER_ENABLE, &write_data, 1 );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );

    spectrometer_generic_read( ctx, SPECTROMETER_FD_STAT, &f_val, 1 );
    
    if ( f_val == 0x2C )
    {
        return SPECTROMETER_UNKNOWN_FREQ;
    }
    else if ( f_val == 0x2D )
    {
        return SPECTROMETER_DETECTED_100_HZ;
    }
    else if ( f_val == 0x2E )
    {
        return SPECTROMETER_DETECTED_120_HZ;
    }
    else
    {
        return SPECTROMETER_READING_ERROR;
    }

    write_data = 0x01;
    spectrometer_generic_write( ctx, SPECTROMETER_ENABLE, &write_data, 1 );
}

uint8_t spectrometer_get_int ( spectrometer_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END


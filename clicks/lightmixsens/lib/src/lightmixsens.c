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

#include "lightmixsens.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Check Register Address function.
 *
 * @param reg_addr  Address to be checked.
 *
 * @returns     0x0  - Ok;      0xFF - Invalid register address.
 *
 * @description This function checks does the entered register address is proper or not.
 */
static lightmixsens_err_t lightmixsens_check_reg_addr ( uint8_t reg_addr );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lightmixsens_cfg_setup ( lightmixsens_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = LIGHTMIXSENS_DEVICE_ADDR;
}

LIGHTMIXSENS_RETVAL lightmixsens_init ( lightmixsens_t *ctx, lightmixsens_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LIGHTMIXSENS_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LIGHTMIXSENS_OK;
}

void lightmixsens_default_cfg ( lightmixsens_t *ctx )
{
    lightmixsens_switch_ir_to_prox( ctx );

    // By setting function argument to '15', IR current for proximity is selected to about 100mA.
    lightmixsens_write_byte( ctx, LIGHTMIXSENS_REG_PCFG1, LIGHTMIXSENS_PCFG1_GAIN_4x + 15 );

    // By setting function argument to '0x3F', ALS/Color integration time is selected to 180ms 
    // and maximum value is selected to 65535, depending also by this parameter.
    lightmixsens_write_byte( ctx, LIGHTMIXSENS_REG_ATIME, 0x3F );
    lightmixsens_write_byte( ctx, LIGHTMIXSENS_REG_ENABLE, LIGHTMIXSENS_ENABLE_PROX |
                                                           LIGHTMIXSENS_ENABLE_ALS |
                                                           LIGHTMIXSENS_ENABLE_OSC );
}

void lightmixsens_generic_write ( lightmixsens_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void lightmixsens_generic_read ( lightmixsens_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

lightmixsens_err_t lightmixsens_write_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t data_in )
{   
    if ( lightmixsens_check_reg_addr( reg_addr ) )
    {
        return LIGHTMIXSENS_ERR_STAT_INVAL_ADDR;
    }
    
    lightmixsens_generic_write( ctx, reg_addr, &data_in, 1 );
    
    return LIGHTMIXSENS_ERR_STAT_OK;
}

lightmixsens_err_t lightmixsens_write_word ( lightmixsens_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t tmp_buf[ 2 ];
    
    if ( lightmixsens_check_reg_addr( reg_addr ) )
    {
        return LIGHTMIXSENS_ERR_STAT_INVAL_ADDR;
    }

    tmp_buf[ 0 ] = data_in & 0xFF;
    tmp_buf[ 1 ] = data_in >> 8;
    
    lightmixsens_generic_write( ctx, reg_addr, tmp_buf, 2 );
    
    return LIGHTMIXSENS_ERR_STAT_OK;
}

lightmixsens_err_t lightmixsens_read_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{   
    if ( lightmixsens_check_reg_addr( reg_addr ) )
    {
        return LIGHTMIXSENS_ERR_STAT_INVAL_ADDR;
    }
    
    lightmixsens_generic_read( ctx, reg_addr, data_out, 1 );
    
    return LIGHTMIXSENS_ERR_STAT_OK;
}

lightmixsens_err_t lightmixsens_read_word ( lightmixsens_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t tmp_buf[ 2 ] = { LIGHTMIXSENS_DUMMY_DATA };
    
    if ( lightmixsens_check_reg_addr( reg_addr ) )
    {
        return LIGHTMIXSENS_ERR_STAT_INVAL_ADDR;
    }
    
    lightmixsens_generic_read( ctx, reg_addr, tmp_buf, 2 );
    
    *data_out = tmp_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= tmp_buf[ 0 ];
    
    return LIGHTMIXSENS_ERR_STAT_OK;
}

void lightmixsens_get_status ( lightmixsens_t *ctx, uint8_t flag_mask, uint8_t *status )
{
    uint8_t stat_byte = LIGHTMIXSENS_DUMMY_DATA;
    
    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_STATUS, &stat_byte );
    
    *status = stat_byte & flag_mask;
}

void lightmixsens_switch_ir_to_green ( lightmixsens_t *ctx )
{
    uint8_t reg_dat = LIGHTMIXSENS_DUMMY_DATA;
    
    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_CFG1, &reg_dat );
    
    reg_dat |= LIGHTMIXSENS_CFG1_IR_TO_GREEN;
    
    lightmixsens_write_byte( ctx, LIGHTMIXSENS_REG_CFG1, reg_dat );
}

void lightmixsens_switch_ir_to_prox ( lightmixsens_t *ctx )
{
    uint8_t reg_dat = LIGHTMIXSENS_DUMMY_DATA;

    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_CFG1, &reg_dat );

    reg_dat &= ~LIGHTMIXSENS_CFG1_IR_TO_GREEN;

    lightmixsens_write_byte( ctx, LIGHTMIXSENS_REG_CFG1, reg_dat );
}

void lightmixsens_wait_atime ( lightmixsens_t *ctx )
{
    uint8_t reg_dat = LIGHTMIXSENS_DUMMY_DATA;
    uint16_t cnt;
    float dly_time_ms = LIGHTMIXSENS_ATIME_WTIME_CONST;
    
    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_ATIME, &reg_dat );
    
    dly_time_ms *= reg_dat + 1;
    
    for ( cnt = 0; cnt <= ( uint16_t ) dly_time_ms; cnt++ )
    {
        Delay_1ms( );
    }
}

void lightmixsens_wait_ptime ( lightmixsens_t *ctx )
{
    uint8_t reg_dat = LIGHTMIXSENS_DUMMY_DATA;
    uint16_t cnt;
    uint16_t dly_time_us = LIGHTMIXSENS_PTIME_CONST;

    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_PTIME, &reg_dat );

    dly_time_us *= reg_dat + 1;

    for ( cnt = 0; cnt <= dly_time_us; cnt++ )
    {
        Delay_1us( );
    }
}

void lightmixsens_wait_wtime ( lightmixsens_t *ctx )
{
    uint8_t reg_dat1 = LIGHTMIXSENS_DUMMY_DATA;
    uint8_t reg_dat2 = LIGHTMIXSENS_DUMMY_DATA;
    uint16_t cnt;
    float dly_time_ms = LIGHTMIXSENS_ATIME_WTIME_CONST;

    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_WTIME, &reg_dat1 );
    lightmixsens_read_byte( ctx, LIGHTMIXSENS_REG_CFG0, &reg_dat2 );
    
    if ( reg_dat2 & LIGHTMIXSENS_CFG0_WLONG )
    {
        dly_time_ms *= LIGHTMIXSENS_WTIME_INCR_FACTOR;
    }

    dly_time_ms *= reg_dat1 + 1;

    for ( cnt = 0; cnt <= ( uint16_t ) dly_time_ms; cnt++ )
    {
        Delay_1ms( );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static lightmixsens_err_t lightmixsens_check_reg_addr ( uint8_t reg_addr )
{
    if ( ( ( reg_addr >= 0x80 ) && ( reg_addr <= 0x9F ) && 
           ( reg_addr != 0x89 ) && ( reg_addr != 0x8B ) && 
           ( reg_addr != 0x9D ) ) || ( reg_addr == 0xAB ) || 
         ( reg_addr == 0xC0 ) || ( reg_addr == 0xC1 ) || 
         ( reg_addr == 0xD6 ) || ( reg_addr == 0xD7 ) || 
         ( reg_addr == 0xD9 ) || ( reg_addr == 0xDC ) || 
         ( reg_addr == 0xDD ) )
    {
        return LIGHTMIXSENS_ERR_STAT_OK;
    }

    return LIGHTMIXSENS_ERR_STAT_INVAL_ADDR;
}

// ------------------------------------------------------------------------- END


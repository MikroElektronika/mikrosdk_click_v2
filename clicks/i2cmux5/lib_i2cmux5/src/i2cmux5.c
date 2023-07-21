/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file i2cmux5.c
 * @brief I2C MUX 5 Click Driver.
 */

#include "i2cmux5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define I2CMUX5_DUMMY                    0x00


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_reset_delay ( void );

static void dev_chg_sl_addr_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS


void i2cmux5_cfg_setup ( i2cmux5_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->ready   = HAL_PIN_NC;
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CMUX5_SET_DEV_ADDR;
}

err_t i2cmux5_init ( i2cmux5_t *ctx, i2cmux5_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->ready, cfg->ready );
    digital_in_init( &ctx->alert, cfg->alert );

    return I2C_MASTER_SUCCESS;
}

void i2cmux5_default_cfg ( i2cmux5_t *ctx ) {
    // Enables I2C communication.
    
    i2cmux5_dev_enable( ctx );
}

void i2cmux5_hw_reset ( i2cmux5_t *ctx ) {
    digital_out_low( &ctx->en );
    dev_reset_delay( );
    
    digital_out_high( &ctx->en );
    dev_reset_delay( );
}

void i2cmux5_dev_enable ( i2cmux5_t *ctx ) {
    digital_out_high( &ctx->en );
}

uint8_t i2cmux5_check_rdy ( i2cmux5_t *ctx ) {
    return digital_in_read( &ctx->ready );
}

uint8_t i2cmux5_check_alert ( i2cmux5_t *ctx ) {
    return digital_in_read( &ctx->alert );
}

err_t i2cmux5_generic_write ( i2cmux5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t i2cmux5_generic_read ( i2cmux5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t i2cmux5_check_ch_alert ( i2cmux5_t *ctx, uint8_t sel_ch ) {
    uint8_t rx_buf[ 1 ];
    uint8_t alert;
    
    if ( ( sel_ch >= I2CMUX5_CH_1 ) && ( sel_ch <= I2CMUX5_CH_4 ) ) {
    
        i2cmux5_generic_read( ctx, I2CMUX5_REGISTER_0, rx_buf, 1 );
   
        sel_ch = 7 - sel_ch;
        alert = rx_buf[ 0 ];
        alert = ~alert;
        alert >>= sel_ch;
        alert &= 0x01;
    }
    else{
        alert = I2CMUX5_CH_SEL_ERROR;
    }
    
    
    return alert;
}

void i2cmux5_channel_write_byte ( i2cmux5_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 1 ];
    
    if ( ( sel_ch >= I2CMUX5_CH_1 ) && ( sel_ch <= I2CMUX5_CH_4 ) ) {
        --sel_ch;
        
        tx_buf[ 0 ] = I2CMUX5_SET_REG_3_BUS_1_SWITCH_CLOSED;
    
        tx_buf[ 0 ] >>= sel_ch;
    
        i2cmux5_generic_write( ctx, I2CMUX5_REGISTER_3, tx_buf, 1 );
    
        ctx->slave_address = ch_slave_addr;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        dev_chg_sl_addr_delay( );
    
        tx_buf[ 0 ] = tx_data;
        
        i2cmux5_generic_write( ctx, reg, tx_buf, 1 );
    
        ctx->slave_address = I2CMUX5_SET_DEV_ADDR;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        dev_chg_sl_addr_delay( );
    }
}

uint8_t i2cmux5_channel_read_byte ( i2cmux5_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];
    
    rx_buf[ 0 ] = I2CMUX5_DUMMY;
    
    if ( ( sel_ch >= I2CMUX5_CH_1 ) && ( sel_ch <= I2CMUX5_CH_4 ) ) {
        --sel_ch;
    
        tx_buf[ 0 ] = I2CMUX5_SET_REG_3_BUS_1_SWITCH_CLOSED;
    
        tx_buf[ 0 ] >>= sel_ch;
    
        i2cmux5_generic_write( ctx, I2CMUX5_REGISTER_3, tx_buf, 1 );
    
        ctx->slave_address = ch_slave_addr;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        dev_chg_sl_addr_delay( );
    
        i2cmux5_generic_read( ctx, reg, rx_buf, 1 );
    
        ctx->slave_address = I2CMUX5_SET_DEV_ADDR;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        dev_chg_sl_addr_delay( );
    }
    
    return rx_buf[ 0 ]; 
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void )
{
    Delay_100ms( );
}

static void dev_chg_sl_addr_delay ( void )
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END

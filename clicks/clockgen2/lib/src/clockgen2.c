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

#include "clockgen2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void clockgen2_cfg_setup ( clockgen2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pdn = HAL_PIN_NC;
    cfg->oe   = HAL_PIN_NC;
    cfg->dtr = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CLOCKGEN2_ADDR;
}

CLOCKGEN2_RETVAL clockgen2_init ( clockgen2_t *ctx, clockgen2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CLOCKGEN2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->pdn, cfg->pdn );
    digital_out_init( &ctx->oe, cfg->oe );
    digital_out_init( &ctx->dtr, cfg->dtr );

    digital_out_write( &ctx->pdn, 1 );
    digital_out_write( &ctx->oe, 1 );
    digital_out_write( &ctx->dtr, 1 );

    return CLOCKGEN2_OK;

}

void clockgen2_generic_write ( clockgen2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void clockgen2_generic_read ( clockgen2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void clockgen2_set_dtr_pin ( clockgen2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->dtr, state );
}

void clockgen2_set_pdn_pin ( clockgen2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->pdn, state );
}

void clockgen2_set_oe_pin ( clockgen2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->oe, state);
}

void clockgen2_write ( clockgen2_t *ctx, uint8_t w_reg, uint8_t w_data )
{
    if ( w_reg == CLOCKGEN2_WRITE_EE_REG )
    {
        clockgen2_generic_write( ctx, w_reg, NULL, 0 );
    }
    else
    {
        clockgen2_generic_write( ctx, w_reg, &w_data, 1 );
    }
}

void clockgen2_set_prescaler ( clockgen2_t *ctx, uint8_t val )
{
    static uint8_t tmp;
    static uint8_t tmp_wc;

    clockgen2_generic_read( ctx, CLOCKGEN2_PRESCALER_REG, &tmp, 1 );
    clockgen2_generic_read( ctx, CLOCKGEN2_ADDR_CHANGE_REG, &tmp_wc, 1 );

    tmp &= 0xF0;
    tmp |= ( val & 0x0F);

    clockgen2_write( ctx, CLOCKGEN2_PRESCALER_REG, tmp );
}

void clockgen2_change_address ( clockgen2_t *ctx, uint8_t new_addr ) 
{
    
    //  Set the address bits from 0 to 7 
    //  1 0 1 1 A2 A1 A0 RW
    //  Default value of A2, A1 and A0 is 0

    static uint8_t tmp;

    clockgen2_generic_read( ctx, CLOCKGEN2_ADDR_CHANGE_REG, &tmp, 1 );

    //clear the lower 3 bit's

    tmp &= 0xF8;

    // mask the lower 3 bits to stay in the scope of the range.

    tmp = ( new_addr & 0x07 ); 

    // if the address is set at runtime set the address to prevent blocking.

    ctx->slave_address &= 0x07;
    ctx->slave_address |= ( new_addr & 0x07 ); 
    
    clockgen2_write( ctx, CLOCKGEN2_ADDR_CHANGE_REG, tmp );
}

void clockgen2_store_config ( clockgen2_t *ctx )
{
    uint8_t w_temp;
    w_temp = 0;

    clockgen2_write( ctx, CLOCKGEN2_WRITE_EE_REG, w_temp );
}

void clockgen2_auto_setting_preserve ( clockgen2_t *ctx, uint8_t state )
{
    static uint8_t tmp;

    clockgen2_generic_read( ctx, CLOCKGEN2_ADDR_CHANGE_REG, &tmp, 1 );

    if ( state == CLOCKGEN2_AUTO_PRESERVE_DISABLE )
    {

       // Disable auto preserve by writing the WC bit to 1.
       // After setting this bit the WRITE EE command needs 
       // to be issued to preserve data. 
       // This is done usually in closed loop systems when the 
       // eeprom memory needs to be written continiously. To prevent 
       // wearing of the eeprom memory. 
        
       tmp |= 0x08;  
    }
    if ( state == CLOKCGEN2_AUTO_PRESERVE_ENABLE )
    {
        tmp &= 0xF7;
    }

    clockgen2_write( ctx, CLOCKGEN2_ADDR_CHANGE_REG, tmp );
}

void clockgen2_output_enable ( clockgen2_t *ctx, uint8_t state )
{  
    digital_out_write( &ctx->oe, state );
}

// ------------------------------------------------------------------------- END


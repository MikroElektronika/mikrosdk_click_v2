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

#include "buck14.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t buck_mfr_id[ 8 ] = { 'E', 'r', 'i', 'c', 's', 's', 'o', 'n' };

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void cmd_delay ( void );

static void rst_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck14_cfg_setup ( buck14_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pg   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->syn = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BUCK14_SLAVE_ADDR;
}

BUCK14_RETVAL buck14_init ( buck14_t *ctx, buck14_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BUCK14_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->syn, cfg->syn );

    // Input pins

    digital_in_init( &ctx->pg, cfg->pg );
    digital_in_init( &ctx->alr, cfg->alr );

    return BUCK14_OK;
}

void buck14_default_cfg ( buck14_t *ctx )
{
    uint8_t write_buf[ 50 ];
    uint16_t limit_vout_pg_on;
    uint16_t limit_vout_pg_off;
    uint8_t amode;

    amode = BUCK14_AMODE_CALIB_CONT_RAMP_UP;

    buck14_generic_write( ctx, BUCK14_CMD_ADAPTIVE_MODE, &amode, 2 );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    
    limit_vout_pg_on = 0x1000;
    write_buf[ 0 ] = limit_vout_pg_on & 0x00FF;
    write_buf[ 1 ] = ( limit_vout_pg_on >> 8) & 0x00FF;
    buck14_generic_write( ctx, BUCK14_CMD_VOUT_UV_FAULT_LIMIT, write_buf, 2 );
    
    limit_vout_pg_on = 0x1000;
    write_buf[ 0 ] = limit_vout_pg_on & 0x00FF;
    write_buf[ 1 ] = ( limit_vout_pg_on >> 8) & 0x00FF;
    buck14_generic_write( ctx, BUCK14_CMD_FAULT_POWER_GOOD_ON, write_buf, 2 );
    
    limit_vout_pg_off = 0x0F00;
    write_buf[ 0 ] = limit_vout_pg_on & 0x00FF;
    write_buf[ 1 ] = ( limit_vout_pg_on >> 8) & 0x00FF;
    buck14_generic_write( ctx, BUCK14_CMD_FAULT_POWERGOOD_OFF, write_buf, 2 );
}

void buck14_generic_write ( buck14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void buck14_generic_read ( buck14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void buck14_power_ctrl ( buck14_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en , state );
    Delay_100ms( );
}

void buck14_power_sync ( buck14_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->syn , state );
    Delay_100ms( );
}

uint8_t buck14_power_good ( buck14_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

uint8_t buck14_salert ( buck14_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

uint8_t buck14_check_mfr_id ( buck14_t *ctx )
{
    uint8_t read_buf[ 9 ];
    uint8_t cnt;

    buck14_generic_read( ctx, BUCK14_CMD_MFR_ID, read_buf, 9 );

    for ( cnt = 1; cnt < 9; cnt++ )
    {
        if ( buck_mfr_id[ cnt - 1 ] != read_buf[ cnt ] )
        {
            return BUCK14_ID_ERROR;
        }
    }

    return BUCK14_SUCCESSFUL;
}

void buck14_reset ( buck14_t *ctx )
{
    digital_out_high( &ctx->en );
    rst_delay(  );
    digital_out_low( &ctx->en );
    rst_delay(  );
    digital_out_high( &ctx->en );
    rst_delay(  );
}

uint16_t buc14_read_vout ( buck14_t *ctx )
{
    static float vout_data;
    static float vout_tmp;
    static uint16_t temp_vout_data;
    static uint8_t read_buf[ 2 ];

    buck14_generic_read( ctx, BUCK14_CMD_READ_VOUT, read_buf , 2 );
    temp_vout_data = read_buf[ 1 ];
    temp_vout_data <<= 8;
    temp_vout_data |= read_buf[ 0 ];

    vout_tmp = temp_vout_data;
    vout_data = vout_tmp * BUCK14_VOUT_MODE_VALUE;

    vout_data *= 1000;
    temp_vout_data = vout_data;

    return temp_vout_data;
}

uint8_t buc14_write_vout ( buck14_t *ctx, float vout )
{
    uint8_t write_buf[ 2 ];
    uint16_t temp_vout;
    uint8_t status_data;

    buck14_power_ctrl( ctx, BUCK14_PIN_STATE_HIGH );

    temp_vout = vout / BUCK14_VOUT_MODE_VALUE;
    
    write_buf[ 0 ] = temp_vout & 0x00FF;
    write_buf[ 1 ] = ( temp_vout >> 8 ) & 0x00FF;
    buck14_generic_write( ctx, BUCK14_CMD_VOUT_COMMAND, write_buf, 2 );

    cmd_delay( );
    
    return BUCK14_SUCCESSFUL;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void cmd_delay ( void )
{
    Delay_1sec(  );
}

static void rst_delay ( void )
{
    Delay_100ms(  );
    Delay_100ms(  );
    Delay_100ms(  );
    Delay_100ms(  );
    Delay_100ms(  );
}

// ------------------------------------------------------------------------- END


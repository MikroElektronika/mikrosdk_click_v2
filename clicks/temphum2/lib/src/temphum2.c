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

#include "temphum2.h"

// --------------------------------------------------PRIVATE VARIABLES

static uint8_t speed_mode = TEMPHUM2_NORMAL_MODE;
static uint8_t select_mode = TEMPHUM2_NO_HOLD_MODE;
static uint16_t data_register = TEMPHUM2_REG_TEMPHUM_NHM_NORMAL_MODE;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum2_cfg_setup ( temphum2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x70;
}

TEMPHUM2_RETVAL temphum2_init ( temphum2_t *ctx, temphum2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return TEMPHUM2_OK;
}

void temphum2_default_cfg ( temphum2_t *ctx )
{
    uint8_t tmp;
    temphum2_set_mode( TEMPHUM2_NO_HOLD_MODE, TEMPHUM2_NORMAL_MODE );
    tmp = TEMPHUM2_HEATER_ENABLE | TEMPHUM2_HEATER_CURRENT_6_4mA;
    temphum2_generic_write( ctx, TEMPHUM2_REG_WRITE_HEATER_CONTROL, &tmp, 1  );
}

void temphum2_generic_write ( temphum2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void temphum2_generic_read ( temphum2_t *ctx, uint8_t *tx_buf, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_buf, len );
}

uint8_t temphum2_read_firmware_revision ( temphum2_t *ctx )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_reg[ 1 ];
    
    write_reg[ 0 ] = ( TEMPHUM2_REG_FIRMWARE_REVISION >> 8 ) & 0x00FF;
    write_reg[ 1 ] = TEMPHUM2_REG_FIRMWARE_REVISION & 0x00FF;
    
    temphum2_generic_read( ctx, write_reg, read_reg, 1 );
    
    return read_reg[ 0 ];
}

void temhum2_get_eletronic_id ( temphum2_t *ctx, uint8_t *electronic_id )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_sna_reg[ 8 ];
    uint8_t read_snb_reg[ 6 ];
    
    write_reg[ 0 ] = ( TEMPHUM2_REG_ELECTRONIC_ID_1 >> 8 ) & 0x00FF;
    write_reg[ 1 ] = TEMPHUM2_REG_ELECTRONIC_ID_1 & 0x00FF;
    
    temphum2_generic_read( ctx, write_reg, read_sna_reg, 8 );
    
    electronic_id[ 0 ] = read_sna_reg[ 0 ];
    electronic_id[ 1 ] = read_sna_reg[ 2 ];
    electronic_id[ 2 ] = read_sna_reg[ 4 ];
    electronic_id[ 3 ] = read_sna_reg[ 6 ];
    
    write_reg[ 0 ] = ( TEMPHUM2_REG_ELECTRONIC_ID_2 >> 8 ) & 0x00FF;
    write_reg[ 1 ] = TEMPHUM2_REG_ELECTRONIC_ID_2 & 0x00FF;
    
    temphum2_generic_read( ctx, write_reg, read_snb_reg, 6 );
    
    electronic_id[ 4 ] = read_snb_reg[ 0 ];
    electronic_id[ 5 ] = read_snb_reg[ 1 ];
    electronic_id[ 6 ] = read_snb_reg[ 3 ];
    electronic_id[ 7 ] = read_snb_reg[ 4 ];
}

uint8_t temphum2_get_query_device ( temphum2_t *ctx )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_reg[ 3 ];
    volatile uint32_t read_data;
    
    write_reg[ 0 ] = ( TEMPHUM2_REG_QUERY_DEVICE_RESP >> 8 ) & 0x00FF;
    write_reg[ 1 ] =  TEMPHUM2_REG_QUERY_DEVICE_RESP & 0x00FF;
    
    temphum2_generic_read( ctx, write_reg, read_reg, 3 );

    read_data = read_reg[ 0 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 1 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 2 ];
    
    if ( read_data == 0x0000472B )
    {
        return QUERY_DEVICE_OK;
    }
    else
    {
        return QUERY_DEVICE_ERROR;
    }
}

void temphum2_set_mode ( uint8_t select_mode, uint8_t speed_mode )
{
    speed_mode = speed_mode;
    select_mode = select_mode;
    
    if ( ( speed_mode == TEMPHUM2_NORMAL_MODE ) && ( select_mode == TEMPHUM2_HOLD_MODE ) )
    {
        data_register = TEMPHUM2_REG_TEMPHUM_HM_NORMAL_MODE;
    }
    else if ( ( speed_mode == TEMPHUM2_NORMAL_MODE ) && ( select_mode == TEMPHUM2_NO_HOLD_MODE ) )
    {
        data_register = TEMPHUM2_REG_TEMPHUM_NHM_NORMAL_MODE;
    }
    else if ( ( speed_mode == TEMPHUM2_FAST_MODE ) && ( select_mode == TEMPHUM2_HOLD_MODE ) )
    {
        data_register = TEMPHUM2_REG_TEMPHUM_HM_FAST_MODE;
    }
    else if ( ( speed_mode == TEMPHUM2_FAST_MODE ) && ( select_mode == TEMPHUM2_NO_HOLD_MODE ) )
    {
        data_register = TEMPHUM2_REG_TEMPHUM_NHM_FAST_MODE;
    }
    else
    {
        data_register = TEMPHUM2_REG_TEMPHUM_NHM_NORMAL_MODE;
    }
}

void temphum2_get_measurement ( temphum2_t *ctx, float *data_buffer )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_reg[ 6 ];
    uint16_t i_temp_data;
    uint16_t i_hum_data;
    float f_hum_data;
    float f_temp_data;
    
    write_reg[ 0 ] = ( data_register >> 8 ) & 0x00FF;
    write_reg[ 1 ] = ( data_register & 0x00FF );
    
	i2c_master_write( &ctx->i2c, write_reg, 2 );
	Delay_100ms();
	i2c_master_read( &ctx->i2c, read_reg, 6 );

    // Temperature
    i_temp_data = read_reg[ 0 ];
    i_temp_data = i_temp_data << 8;
    i_temp_data = i_temp_data | read_reg[ 1 ];
    
    f_temp_data = -45.0 + 175.0 * (i_temp_data / 65535.0);
    
    // Humidity
    i_hum_data = read_reg[ 3 ];
    i_hum_data = i_hum_data << 8;
    i_hum_data = i_hum_data | read_reg[ 4 ];
    
    f_hum_data = 100.0 * ( i_hum_data / 65535.0);
    
    data_buffer[ 0 ] = f_temp_data;
    data_buffer[ 1 ] = f_hum_data;
}

// ------------------------------------------------------------------------- END


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

#include "ambient5.h" 

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient5_cfg_setup ( ambient5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AMBIENT5_DEVICE_ADDRESS;
}

AMBIENT5_RETVAL ambient5_init ( ambient5_t *ctx, ambient5_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT5_INIT_ERROR;
    }

	i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin , cfg->int_pin );

    return AMBIENT5_OK;
}

void ambient5_default_cfg ( ambient5_t *ctx )
{
	ambient5_power_on( ctx );
	ambient5_set_low_light_level_threshold( ctx, 100 );
	ambient5_set_high_light_level_threshold( ctx, 500 );
}

void ambient5_set_register ( ambient5_t *ctx, uint8_t reg_addr, uint16_t reg_value )
{
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = reg_addr;
	tx_buf[ 1 ] = reg_value;
	tx_buf[ 2 ] = reg_value >> 8;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );     
}

uint16_t ambient5_get_register ( ambient5_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 1 ];
	uint8_t rx_buf[ 2 ];
	uint16_t raw_data;

    tx_buf [ 0 ] = reg;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );

	raw_data = rx_buf[ 1 ];
	raw_data <<= 8;
	raw_data |= rx_buf[ 0 ];

	return raw_data;
}

float ambient5_get_resolution ( ambient5_t* ctx )
{
	uint16_t reg;
	uint16_t gain;
	uint16_t it;
	float res = 0.0036;

	reg = ambient5_get_register( ctx, AMBIENT5_CONFIGURATION );

	gain = reg;
	it = reg;

	gain >>= 11;
	gain &= 0x0003;

	it >>= 6;
	it &= 0x000F;

	if ( gain == 1 )
	{
		res *= 1;
	}
	else if ( gain == 0 )
	{
		res *= 2;
	}
	else if ( gain == 3 )
	{
		res *= 8;
	}
	else if ( gain == 2 )
	{
		res *= 16;
	}

	if ( it == 3 )
	{
		res *= 1;
	}
	else if ( it == 2 )
	{
		res *= 2;
	}
	else if ( it == 1 )
	{
		res *= 4;
	}
	else if ( it == 0 )
	{
		res *= 8;
	}
	else if ( it == 8 )
	{
		res *= 16;
	}
	else if ( it == 12 )
	{
		res *= 32;
	}

	return res;
}

uint16_t ambient5_get_refresh_time ( ambient5_t* ctx )
{
	uint16_t it;
	uint16_t mode;
	uint16_t refresh_time;

	it = ambient5_get_register( ctx, AMBIENT5_CONFIGURATION );
	mode = ambient5_get_register( ctx, AMBIENT5_POWER_SAVING_MODE );

	it >>= 6;
	it &= 0x000F;

	mode >>= 1;
	mode &= 0x0003;

	if ( it == 12 )
	{
		if ( mode == 0 )
		{
			refresh_time = 525;
		}
		else if ( mode == 1 )
		{
			refresh_time = 1025;
		}
		else if ( mode == 2 )
		{
			refresh_time = 2025;
		}
		else if ( mode == 3 )
		{
			refresh_time = 4025;
		}
	}
	else if ( it == 8 )
	{
		if ( mode == 0 )
		{
			refresh_time = 550;
		}
		else if ( mode == 1 )
		{
			refresh_time = 1050;
		}
		else if ( mode == 2 )
		{
			refresh_time = 2050;
		}
		else if ( mode == 3 )
		{
			refresh_time = 4050;
		}
	}
	else if ( it == 0 )
	{
		if ( mode == 0 )
		{
			refresh_time = 600;
		}
		else if ( mode == 1 )
		{
			refresh_time = 1100;
		}
		else if ( mode == 2 )
		{
			refresh_time = 2100;
		}
		else if ( mode == 3 )
		{
			refresh_time = 4100;
		}
	}
	else if ( it == 1 )
	{
		if ( mode == 0 )
		{
			refresh_time = 700;
		}
		else if ( mode == 1 )
		{
			refresh_time = 1200;
		}
		else if ( mode == 2 )
		{
			refresh_time = 2200;
		}
		else if ( mode == 3 )
		{
			refresh_time = 4200;
		}
	}
	else if ( it == 2 )
	{
		if ( mode == 0 )
		{
			refresh_time = 900;
		}
		else if ( mode == 1 )
		{
			refresh_time = 1400;
		}
		else if ( mode == 2 )
		{
			refresh_time = 2400;
		}
		else if ( mode == 3 )
		{
			refresh_time = 4400;
		}
	}
	else if ( it == 3 )
	{
		if ( mode == 0 )
		{
			refresh_time = 1300;
		}
		else if ( mode == 1 )
		{
			refresh_time = 1800;
		}
		else if ( mode == 2 )
		{
			refresh_time = 2800;
		}
		else if ( mode == 3 )
		{
			refresh_time = 4800;
		}
	}

	return refresh_time;
}

float ambient5_get_high_resolution_light_level ( ambient5_t* ctx )
{
	float high_resolution_light_level;
	float res;
	uint16_t aux;

	aux = ambient5_get_register( ctx, AMBIENT5_HIGH_RESOLUTION_OUTPUT_DATA );
	res = ambient5_get_resolution( ctx );

	high_resolution_light_level = ( float )( aux * res );

	return high_resolution_light_level;
}

float ambient5_get_white_channel_light_level ( ambient5_t* ctx )
{
	float white_channel_light_level;
	float res;
	uint16_t aux;

	aux = ambient5_get_register( ctx, AMBIENT5_WHITE_CHANNEL_OUTPUT_DATA );
	res = ambient5_get_resolution( ctx );

	white_channel_light_level = ( float )( aux * res );

	return  white_channel_light_level;
	
}

void ambient5_set_low_light_level_threshold ( ambient5_t* ctx, float low_light_level_threshold )
{
	uint16_t light_level_threshold;
	float res;

	res = ambient5_get_resolution( ctx );

	light_level_threshold = ( uint16_t )( low_light_level_threshold / res );

	ambient5_set_register( ctx, AMBIENT5_LOW_THRESHOLD, light_level_threshold );
}

void ambient5_set_high_light_level_threshold ( ambient5_t* ctx, float high_light_level_threshold )
{
	uint16_t light_level_threshold;
	float res;

	res = ambient5_get_resolution( ctx );

	light_level_threshold = ( uint16_t )( high_light_level_threshold / res );

	ambient5_set_register( ctx, AMBIENT5_HIGH_THRESHOLD, light_level_threshold);
}

void ambient5_power_on ( ambient5_t* ctx )
{
	ambient5_set_register( ctx, AMBIENT5_CONFIGURATION,
								AMBIENT5_GAIN_x2 |
								AMBIENT5_INTEGRATION_TIME_25ms |
								AMBIENT5_PERSISTANCE_PROTECT_NUMBER_1 |
								AMBIENT5_INTERRUPT_ENABLE |
								AMBIENT5_POWER_ON );

	ambient5_set_register( ctx, AMBIENT5_POWER_SAVING_MODE,
								AMBIENT5_MODE_1 |
								AMBIENT5_POWER_SAVING_MODE_ENABLE );
}

uint8_t ambient5_checkIntPin ( ambient5_t* ctx )
{
	return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END


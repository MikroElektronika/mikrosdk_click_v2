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

#include "magneto.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MAGNETO_DUMMY                       0
                                            
#define MAGNETO_PARITY_CALIB_FACTOR         2
#define MAGNETO_START_VALUE                 0
#define MAGNETO_ANGLE_START_VALUE           0.0
#define MAGNETO_ANGLE_MULTIP_FACTOR         0.0219
#define MAGNETO_ANGLE_DIV_FACTOR            10.0
#define MAGNETO_BIT_0                       0x01
#define MAGNETO_STATE_LOW                   0

// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t calc_parity ( magneto_t *ctx, uint16_t parity );

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void magneto_cfg_setup ( magneto_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck        = HAL_PIN_NC;
    cfg->miso       = HAL_PIN_NC;
    cfg->mosi       = HAL_PIN_NC;
    cfg->cs         = HAL_PIN_NC;

    // Additional gpio pins

    cfg->out        = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MAGNETO_RETVAL magneto_init ( magneto_t *ctx, magneto_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MAGNETO_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MAGNETO_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MAGNETO_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->out, cfg->out );

    return MAGNETO_OK;

}

void magneto_generic_transfer 
( 
    magneto_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us();
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

uint16_t magneto_read_data ( magneto_t *ctx, uint16_t address_command )
{    
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t result;
    
    address_command  &= MAGNETO_REG_ANGLE;
    address_command  |= MAGNETO_CMD_READ_COMMAND_BIT;
    address_command  |= ( calc_parity( ctx, address_command ) << MAGNETO_CMD_PARITY_VALUE);
    
    tx_buf[ 0 ] = ( uint8_t ) ( address_command >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ( address_command );
    
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    
    result &= ~0xC000;

    return result;
}

void magneto_write_data ( magneto_t *ctx, uint16_t address_command, uint16_t write_data )
{    
    uint8_t tx_buf[ 2 ];
    
    address_command   &= MAGNETO_REG_ANGLE;
    address_command  |= ( calc_parity( ctx, address_command ) << MAGNETO_CMD_PARITY_VALUE);
    
    tx_buf[ 0 ] = ( uint8_t ) ( address_command >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ( address_command );  
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
   
    write_data  |= ( calc_parity( ctx, write_data ) << MAGNETO_CMD_PARITY_VALUE); 
    tx_buf[ 0 ] = ( uint8_t ) ( write_data >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ( write_data );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint16_t magneto_get_state ( magneto_t *ctx )
{
    return magneto_read_data( ctx, MAGNETO_REG_DIAG_AGC );
}

uint8_t magneto_check_state ( magneto_t *ctx )
{
    if ( magneto_get_state( ctx ) != MAGNETO_STATE_LOW )
    {
        return MAGNETO_FLAG_ERROR;
    }
    else
    {
        return MAGNETO_FLAG_OK;
    }
}

float magneto_get_angle ( magneto_t *ctx )
{
    float angle;
    uint16_t raw_data;
    
    raw_data = magneto_read_data( ctx, MAGNETO_REG_MAGNITUDE );
    
    angle = (float)raw_data * (360.0 / 16383.0);
    return angle;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t calc_parity ( magneto_t *ctx, uint16_t parity )
{
	uint8_t cnt = 0;
	uint8_t i;

	for ( i = 0; i < 16; i++ )
	{
		if ( parity & 0x1 )
		{
			cnt++;
		}
		parity >>= 1;
	}
	return cnt & 0x1;
}

static void dev_comm_delay ( void )
{
    Delay_1us();
}

// ------------------------------------------------------------------------- END


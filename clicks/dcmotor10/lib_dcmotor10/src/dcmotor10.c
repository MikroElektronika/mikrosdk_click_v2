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

#include "dcmotor10.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DCMOTOR10_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

uint16_t dev_mirror_bits ( uint16_t wr_data );

void  dcmotor10_generic_transfer ( dcmotor10_t *ctx, uint8_t *wr_buf, uint16_t wr_len, 
                                    uint8_t *rd_buf, uint16_t rd_len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor10_cfg_setup ( dcmotor10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->inh = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

DCMOTOR10_RETVAL dcmotor10_init ( dcmotor10_t *ctx, dcmotor10_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed       = cfg->spi_speed;
    spi_cfg.sck         = cfg->sck;
    spi_cfg.miso        = cfg->miso;
    spi_cfg.mosi        = cfg->mosi;
    spi_cfg.default_write_data = DCMOTOR10_DUMMY;
        
    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;
        
    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return  DCMOTOR10_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DCMOTOR10_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 

    digital_out_init( &ctx->inh, cfg->inh );

    return DCMOTOR10_OK;
}

void dcmotor10_send_cmd ( dcmotor10_t *ctx, uint16_t wr_data )
{
    uint16_t temp_val;
    uint8_t tx_buf[ 2 ];

    temp_val = dev_mirror_bits( wr_data );

    tx_buf[ 1 ] = ( uint8_t )( temp_val & DCMOTOR10_8_BIT_DATA );
    tx_buf[ 0 ] = ( uint8_t )( ( temp_val >> 8 ) & DCMOTOR10_8_BIT_DATA );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );     
}

uint16_t dcmotor10_read_status ( dcmotor10_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t temp_val;
    uint16_t result;

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );     

    temp_val = rx_buf[ 0 ];
    temp_val <<= 8;
    temp_val |= rx_buf[ 1 ];

    result = dev_mirror_bits( temp_val );

    return result;
}

void dcmotor10_inhibit ( dcmotor10_t *ctx, uint8_t state )
{
	if ( state == DCMOTOR10_INHIBIT )
	{
        digital_out_low( &ctx->inh );
	}
	else
	{
        digital_out_high( &ctx->inh );	
	}
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

uint16_t dev_mirror_bits ( uint16_t wr_data )
{
    uint8_t count = 15;
    uint16_t tmp = wr_data;
    wr_data >>= 1;
    while ( wr_data )
    {
        tmp <<= 1;
        tmp |= wr_data & 1;
        wr_data >>= 1;
        count--;
    }
    tmp <<= count;

    return tmp;
}

void dcmotor10_generic_transfer ( dcmotor10_t *ctx, uint8_t *wr_buf, uint16_t wr_len, 
                                    uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

// ------------------------------------------------------------------------- END

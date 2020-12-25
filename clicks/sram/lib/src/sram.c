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

#include "sram.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define SRAM_DUMMY          0

// Data resolution

#define SRAM_24BIT_DATA     0x00FFFFFF

// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void sram_cfg_setup ( sram_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->hld = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

SRAM_RETVAL sram_init ( sram_t *ctx, sram_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = SRAM_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return SRAM_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, SRAM_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );  

    // Output pins 
    
    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_high( &ctx->hld );

    return SRAM_OK;

}

void sram_generic_transfer 
( 
    sram_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, wr_buf, wr_len );
    spi_master_read( &ctx->spi, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void sram_generic_write 
( 
    sram_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, wr_buf, wr_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void sram_write_byte ( sram_t *ctx, uint32_t reg_address, uint8_t write_data )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf;
    
    reg_address &= SRAM_24BIT_DATA;
    
    tx_buf[ 0 ]  = SRAM_CMD_WRITE;
    tx_buf[ 1 ]  = ( uint8_t ) ( reg_address >> 16 );
    tx_buf[ 2 ]  = ( uint8_t ) ( reg_address >> 8 );
    tx_buf[ 3 ]  = ( uint8_t )   reg_address;
    tx_buf[ 4 ]  = write_data;
    
    sram_generic_write( ctx, tx_buf, 5 );
}

uint8_t sram_read_byte ( sram_t *ctx, uint32_t reg_address )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 5 ];
    uint8_t read_data;
    
    reg_address &= SRAM_24BIT_DATA;

    tx_buf[ 0 ] = SRAM_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( reg_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( reg_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t )   reg_address;
    
    sram_generic_transfer( ctx, tx_buf, 4, rx_buf, 1 );

    read_data = rx_buf[ 0 ];
    
    return read_data;
}

void sram_write_mode_reg_ins ( sram_t *ctx, uint8_t ins_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf;

    tx_buf[ 0 ] = SRAM_CMD_WRMR;
    tx_buf[ 1 ] = ins_data;
    
    sram_generic_write( ctx, tx_buf, 2 );
}

uint8_t sram_read_mode_reg_ins ( sram_t *ctx )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint8_t read_data;

    tx_buf[ 0 ] = SRAM_CMD_RDMR;
    
    sram_generic_transfer( ctx, tx_buf, 1, rx_buf, 1 );

    read_data = rx_buf[ 0 ];
    
    return read_data;
}

void sram_soft_reset ( sram_t *ctx )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf;

    tx_buf[ 0 ] = SRAM_CMD_RSTIO;
    
    sram_generic_write( ctx, tx_buf, 1 );
}

void sram_hold_transmission ( sram_t *ctx )
{
    digital_out_high( &ctx->hld );
    dev_comm_delay( );
    digital_out_low( &ctx->hld );
    dev_comm_delay( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_22us();
}

// ------------------------------------------------------------------------- END


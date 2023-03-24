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

#include "dac2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DAC2_DUMMY 0

#define DAC2_PERCENTAGE_VALUE            100
#define DAC2_16_BIT_DATA_VALUE           65535
#define DAC2_DIV_FACTOR                  100
#define DAC2_DATA_MASK                   0x00FF

// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac2_cfg_setup ( dac2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->clr = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

DAC2_RETVAL dac2_init ( dac2_t *ctx, dac2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = DAC2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DAC2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DAC2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->clr, cfg->clr );

    return DAC2_OK;

}

void dac2_generic_transfer 
( 
    dac2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    dev_comm_delay( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void dac2_default_cfg ( dac2_t *ctx )
{
    // Reset LTC2601
    
    dac2_clr_dac_2_reg( ctx );
    dev_comm_delay( );
}

void dac2_clr_dac_2_reg ( dac2_t *ctx )
{
    digital_out_low( &ctx->clr );
    dev_comm_delay( );
    digital_out_high( &ctx->clr );
}

void dac2_write_output_voltage_procentage ( dac2_t *ctx, uint8_t value_pct )
{    
    uint16_t value_output;
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf;
    
    dac2_clr_dac_2_reg( ctx );

    if ( value_pct > 100 )
    {
        value_pct %= DAC2_PERCENTAGE_VALUE;
    }

    value_output   = ( DAC2_16_BIT_DATA_VALUE / DAC2_DIV_FACTOR );
    value_output  *= value_pct;
    
    tx_buf[ 0 ]    = value_output >> 8;
    tx_buf[ 1 ]    = value_output & DAC2_DATA_MASK;
    
    spi_master_select_device( ctx->chip_select );
    dev_comm_delay( );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );   
}

void dac2_write_output_voltage_data ( dac2_t *ctx, uint16_t value_data )
{
    
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf;
    
    dac2_clr_dac_2_reg( ctx );

    tx_buf[ 0 ] = value_data >> 8;
    tx_buf[ 1 ] = value_data  & DAC2_DATA_MASK;
    
    spi_master_select_device( ctx->chip_select );
    dev_comm_delay( );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );   
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_10us();
}

// ------------------------------------------------------------------------- END


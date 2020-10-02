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

#include "counter.h"
#include <string.h>

// ------------------------------------------------------------- PRIVATE MACROS 

#define COUNTER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void counter_write_command ( counter_t *ctx, uint8_t command );
static uint8_t counter_read_register ( counter_t *ctx, uint8_t command );
static void counter_write_data ( counter_t *ctx, uint8_t command, uint8_t *_data, uint8_t count );
static void counter_read_data ( counter_t *ctx, uint8_t command, uint8_t *_data, uint8_t count );


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void counter_cfg_setup ( counter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

COUNTER_RETVAL counter_init ( counter_t *ctx, counter_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = COUNTER_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return COUNTER_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, COUNTER_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->en, cfg->en );
    digital_out_high( &ctx->en );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return COUNTER_OK;
}

void counter_default_cfg ( counter_t *ctx )
{
    counter_init_advanced( ctx, COUNTER_4X_QUAD | COUNTER_FREE_RUN | COUNTER_INDEX_DISABLED | COUNTER_FILTER_CLOCK_DIV1,
                                COUNTER_MODE_24 | COUNTER_DISABLE | COUNTER_FLAG_DISABLE );
    counter_write_dtr( ctx, 0 );
    counter_load_cntr( ctx );
    counter_enable( ctx );
}

void counter_generic_transfer 
( 
    counter_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void counter_write_mdr0 ( counter_t *ctx, uint8_t settings )
{
    counter_write_data( ctx, COUNTER_CMD_WR | COUNTER_MDR0, &settings, 1 );
}

void counter_write_mdr1 ( counter_t *ctx, uint8_t settings )
{
    counter_write_data( ctx, COUNTER_CMD_WR | COUNTER_MDR1, &settings, 1 );
}

void counter_write_dtr ( counter_t *ctx, uint8_t buffer )
{
    counter_write_data( ctx, COUNTER_CMD_WR | COUNTER_DTR, &buffer, ctx->buffer_size );
}

void counter_load_cntr ( counter_t *ctx )
{
    counter_write_command( ctx, COUNTER_CMD_LOAD | COUNTER_CNTR );
}

void counter_load_otr ( counter_t *ctx )
{
    counter_write_command( ctx, COUNTER_CMD_LOAD | COUNTER_OTR );
}

uint8_t counter_read_mdr0 ( counter_t *ctx )
{
    uint8_t result;

    result = counter_read_register( ctx, COUNTER_CMD_RD | COUNTER_MDR0 );

    return result;
}

uint8_t counter_read_mdr1 ( counter_t *ctx )
{
    uint8_t result;

    result = counter_read_register( ctx, COUNTER_CMD_RD | COUNTER_MDR1 );

    return result;
}

uint8_t counter_read_otr ( counter_t *ctx )
{
    uint8_t result;

    counter_read_data( ctx, COUNTER_CMD_RD | COUNTER_OTR, &result, ctx->buffer_size );

    return result;
}

uint8_t counter_read_cntr ( counter_t *ctx )
{
    uint8_t result;

    counter_read_data( ctx, COUNTER_CMD_RD | COUNTER_CNTR, &result, ctx->buffer_size );

    return result;
}

uint8_t counter_read_str ( counter_t *ctx )
{
    uint8_t result;

    result = counter_read_register( ctx, COUNTER_CMD_RD | COUNTER_STR );

    return result;
}

void counter_clear_mrd0 ( counter_t *ctx )
{
    counter_write_command( ctx, COUNTER_CMD_CLR | COUNTER_MDR0 );
}

void counter_clead_mrd1 ( counter_t *ctx )
{
    counter_write_command( ctx, COUNTER_CMD_CLR | COUNTER_MDR1 );
}

void counter_clear_cntr ( counter_t *ctx )
{
    counter_write_command( ctx, COUNTER_CMD_CLR | COUNTER_CNTR );
}

void counter_clear_str ( counter_t *ctx )
{
    counter_write_command( ctx, COUNTER_CMD_CLR | COUNTER_STR );
}

void counter_initialisation ( counter_t *ctx )
{
    uint8_t mdr0_set = COUNTER_4X_QUAD | COUNTER_FREE_RUN | COUNTER_INDEX_DISABLED
                       | COUNTER_FILTER_CLOCK_DIV1;
    uint8_t mdr1_set = COUNTER_MODE_32 | COUNTER_DISABLE | COUNTER_FLAG_DISABLE;

    ctx->buffer_size = 4;
    digital_out_high( &ctx->en );
    counter_write_mdr0( ctx, mdr0_set );
    counter_write_mdr1( ctx, mdr1_set );
}

void counter_init_advanced ( counter_t *ctx, uint8_t mdr0_set, uint8_t mdr1_set )
{
    digital_out_high( &ctx->en );
    counter_write_mdr0( ctx, mdr0_set );
    counter_write_mdr1( ctx, mdr1_set );

    switch ( mdr1_set & 0x03 )
    {
        case 0 :
        {
            ctx->buffer_size = 4;
            break;
        }
        case 1 :
        {
            ctx->buffer_size = 3;
            break;
        }
        case 2 :
        {
            ctx->buffer_size = 2;
            break;
        }
        case 3 :
        {
            ctx->buffer_size = 1;
            break;
        }
    }
}

void counter_enable ( counter_t *ctx )
{
    uint8_t mdr1_temp = 0;

    mdr1_temp = counter_read_mdr1( ctx ) & 0xFB;
    counter_write_mdr1( ctx, mdr1_temp );
}

void counter_disable ( counter_t *ctx )
{
    uint8_t mdr1_temp = 0;

    mdr1_temp = counter_read_mdr1( ctx ) | 0x04;
    counter_write_mdr1( ctx, mdr1_temp );
}

void counter_chip_enable ( counter_t *ctx )
{
    digital_out_high( &ctx->en );
}

void counter_chip_disable ( counter_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t get_int_state ( counter_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void counter_write_command ( counter_t *ctx, uint8_t command )
{
    uint8_t temp[ 1 ];
    temp[ 0 ] = command;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &command, 1 );
    spi_master_deselect_device( ctx->chip_select );     
}

static uint8_t counter_read_register ( counter_t *ctx, uint8_t command )
{   
    uint8_t tx_buff[ 1 ];
    uint8_t rx_buff[ 1 ];
    
    tx_buff[ 0 ] = command;

    counter_generic_transfer ( ctx, &tx_buff, 1, rx_buff, 1 );  
    
    return rx_buff[ 0 ];
}

static void counter_write_data ( counter_t *ctx, uint8_t command, uint8_t *data_buff, uint8_t count )
{
    uint8_t cmnd[ 1 ];
    uint8_t temp[ 4 ];
    
    cmnd[ 0 ] = command;
    memcpy( temp, data_buff, count );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &command, 1 );
    counter_generic_transfer( ctx, temp, count, 0, 0 );
    spi_master_deselect_device( ctx->chip_select );  
}

static void counter_read_data ( counter_t *ctx, uint8_t command, uint8_t *data_buff, uint8_t count )
{
    uint8_t i;
    uint8_t tx_buff[ 1 ];
    uint8_t rx_buff[ 256 ];
    
    tx_buff[ 0 ] = command;

    counter_generic_transfer ( ctx, &tx_buff, 1, rx_buff, count + 1 );  
    
    for ( i = 0; i <= count; i++ )
    {
        data_buff[ i ] = rx_buff[ i+1 ];
    }

}


// ------------------------------------------------------------------------- END


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
 * \file charger5.c
 *
 */

#include "charger5.h"


// ------------------------------------------------------------- PRIVATE MACROS

#define NULL   0
#define CHARGER5_DUMMY 0

//  Charger 5 command bits of command byte.
#define CHARGER5_CMD_WRITE  0x00
#define CHARGER5_CMD_READ   0x0C
#define CHARGER5_CMD_INC    0x04
#define CHARGER5_CMD_DEC    0x08

#define CHARGER5_CMDERR_FLAG  0x02

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
charger5_cfg_setup( charger5_cfg_t *cfg )
{
    cfg->sck = HAL_PIN_NC;
    cfg->sdi = HAL_PIN_NC;
    cfg->sdo = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

charger5_err_t
charger5_init( charger5_t *ctx, charger5_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->sdo;
    spi_cfg.mosi      = cfg->sdi;
    spi_cfg.default_write_data = CHARGER5_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CHARGER5_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CHARGER5_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return CHARGER5_STATUS_OK;
}

void
charger5_default_cfg( charger5_t *ctx )
{
    charger5_generic_write( ctx, CHARGER5_REG_TCONTROL_VOL, 0x7F );
}

charger5_err_t
charger5_generic_write( charger5_t *ctx, uint8_t reg_addr,
                        uint16_t transfer_data )
{
    uint8_t data_in[ 2 ] = { 0 };
    uint8_t data_out[ 2 ] = { 0 };

    //  Makes a command for data writing.
    data_in[ 0 ] = reg_addr;
    data_in[ 0 ] <<= 4;
    data_in[ 0 ] |= ( transfer_data >> 8 ) & 0x01 | CHARGER5_CMD_WRITE;
    data_in[ 1 ] = transfer_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, data_in, 2, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    if ( data_out[ 0 ] & CHARGER5_CMDERR_FLAG )
    {
        return CHARGER5_STATUS_OK;
    }

    return CHARGER5_STATUS_ERROR;
}

uint16_t
charger5_generic_read( charger5_t *ctx, uint8_t reg_addr )
{
    uint8_t data_in = 0;
    uint8_t data_out[ 2 ] = { 0 };
    uint16_t ret_val = 0;

    //  Makes a command for data reading.
    data_in = reg_addr;
    data_in <<= 4;
    data_in |= CHARGER5_CMD_READ;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &data_in, 1, data_out, 2 );
    spi_master_deselect_device( ctx->chip_select ); 

    ret_val = data_out[ 0 ] & 0x01;
    ret_val <<= 8;
    ret_val |= data_out[ 1 ];

    return ret_val;
}

charger5_err_t
charger5_increment_wiper( charger5_t *ctx, uint8_t reg_addr, uint8_t n_steps )
{
    uint8_t data_in = 0;
    uint8_t data_out = 0;
    uint8_t i;

    if ( n_steps < CHARGER5_STEPS_1_MIN )
    {
        return CHARGER5_NSTEPS_RANGE_ERROR;
    }

    //  Makes a command for the wiper incrementing.
    data_in = reg_addr;
    data_in <<= 4;
    data_in |= CHARGER5_CMD_INC;

    //  Increments value of wiper register by the selected number of steps.
    for ( i = 0; i < n_steps; i++ )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_write_then_read( &ctx->spi, &data_in, 1, &data_out, 1 );
        spi_master_deselect_device( ctx->chip_select ); 

        if ( !( data_out & CHARGER5_CMDERR_FLAG ) )
        {
            return CHARGER5_STATUS_ERROR;
        }
    }

    return CHARGER5_STATUS_OK;
}

charger5_err_t
charger5_decrement_wiper( charger5_t *ctx, uint8_t reg_addr, uint8_t n_steps )
{
    uint8_t data_in = 0;
    uint8_t data_out = 0;
    uint8_t i;

    if ( n_steps < CHARGER5_STEPS_1_MIN )
    {
        return CHARGER5_NSTEPS_RANGE_ERROR;
    }

    //  Makes a command for the wiper decrementing.
    data_in = reg_addr;
    data_in <<= 4;
    data_in |= CHARGER5_CMD_DEC;

    //  Decrements value of wiper register by the selected number of steps.
    for( i = 0; i < n_steps; i++ )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_write_then_read( &ctx->spi, &data_in, 1, &data_out, 1 );
        spi_master_deselect_device( ctx->chip_select ); 

        if ( !( data_out & CHARGER5_CMDERR_FLAG ) )
        {
            return CHARGER5_STATUS_ERROR;
        }
    }

    return CHARGER5_STATUS_OK;
}

// ------------------------------------------------------------------------ END

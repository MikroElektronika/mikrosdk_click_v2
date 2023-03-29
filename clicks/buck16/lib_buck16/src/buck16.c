/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file buck16.c
 * @brief Buck 16 Click Driver.
 */

#include "buck16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY               0x00

/**
 * @brief Send data masks.
 * @details Mask for command, command bits, and data.
 */
#define DATA_MASK           0x3FF
#define CMD_MASK            0xF0
#define CMDBITS_MASK        0xC0

/**
 * @brief Calculation macros.
 * @details Const calculation values.
 */
#define RAB                 10000
#define RW                  75
#define R2                  1800
#define MCP_RES             256.0
#define TPS62912_RES        0.8
#define TPS62912_EQ_CONST   1

/**
 * @brief Limitations of output value.
 * @details Minimum and maximum values for output voltage.
 */
#define MIN_OUTPUT          800
#define MAX_OUTPUT          5500

void buck16_cfg_setup ( buck16_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t buck16_init ( buck16_t *ctx, buck16_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );

    return SPI_MASTER_SUCCESS;
}

err_t buck16_generic_write ( buck16_t *ctx, uint8_t cmd, uint8_t cmd_bits, uint16_t tx_data )
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_data &= DATA_MASK;
    cmd &= CMD_MASK;
    cmd_bits &= CMDBITS_MASK;
    tx_buf[ 0 ] = cmd | cmd_bits | tx_data >> 8;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void buck16_enable_output ( buck16_t *ctx, uint8_t enable )
{
    if ( enable )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

err_t buck16_set_potentiometer ( buck16_t *ctx, uint16_t rwb )
{
    uint16_t n = ( rwb - RW ) * ( MCP_RES / RAB );
    return buck16_generic_write( ctx, BUCK16_CMD_VOLATILE_WIPER_0, BUCK16_WRITE, n );
}

err_t buck16_set_output ( buck16_t *ctx, uint16_t vout )
{
    if ( ( vout < MIN_OUTPUT ) || ( vout > MAX_OUTPUT ) )
    {
        return BUCK16_ERROR;
    }
    
    float voltage = vout / 1000.0;/*< Convert value from mV to V */
    float rwb = R2 * ( ( voltage / TPS62912_RES ) - TPS62912_EQ_CONST );
    return buck16_set_potentiometer( ctx, ( uint16_t )rwb );
}

// ------------------------------------------------------------------------- END

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
 * @file expand18.c
 * @brief Expand 18 Click Driver.
 */

#include "expand18.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void expand18_cfg_setup ( expand18_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->spi_address = EXPAND18_DEVICE_ADDRESS_0;
}

err_t expand18_init ( expand18_t *ctx, expand18_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    ctx->slave_address = cfg->spi_address;

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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t expand18_default_cfg ( expand18_t *ctx ) 
{
    err_t error_flag = EXPAND18_OK;
    expand18_reset_device ( ctx );
    error_flag |= expand18_set_pin_direction ( ctx, EXPAND18_OUTPUT_DIRECTION, EXPAND18_PORT_0, EXPAND18_ALL_PINS_MASK );
    error_flag |= expand18_set_pin_direction ( ctx, EXPAND18_INPUT_DIRECTION, EXPAND18_PORT_1, EXPAND18_ALL_PINS_MASK );
    error_flag |= expand18_set_all_pins_value ( ctx, EXPAND18_NO_PIN_MASK );
    error_flag |= expand18_write_register ( ctx, EXPAND18_REG_PULL_SELECTION_P1, EXPAND18_NO_PIN_MASK );
    error_flag |= expand18_write_register ( ctx, EXPAND18_REG_PULL_ENABLE_P1, EXPAND18_ALL_PINS_MASK );
    return error_flag;
}

err_t expand18_generic_write ( expand18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t slave_addr = ctx->slave_address & ( ~EXPAND18_ADDRESS_READ_BIT );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &slave_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t expand18_generic_read ( expand18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t slave_addr = ctx->slave_address | EXPAND18_ADDRESS_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &slave_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t expand18_write_register ( expand18_t *ctx, uint8_t reg, uint8_t data_in )
{
    return expand18_generic_write ( ctx, reg, &data_in, 1 );
}

err_t expand18_read_register ( expand18_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return expand18_generic_read ( ctx, reg, data_out, 1 );
}

void expand18_set_rst_pin ( expand18_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void expand18_reset_device ( expand18_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t expand18_get_int_pin ( expand18_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t expand18_set_pin_direction ( expand18_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask )
{
    if ( ( port > EXPAND18_PORT_1 ) || ( direction > EXPAND18_INPUT_DIRECTION ) )
    {
        return EXPAND18_ERROR;
    }
    uint8_t port_value = 0;
    err_t error_flag = expand18_read_register ( ctx, EXPAND18_REG_CONFIG_P0 + port, &port_value );
    if ( EXPAND18_OUTPUT_DIRECTION == direction )
    {
        port_value &= ~pin_mask;
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_CONFIG_P0 + port, port_value );
    }
    else
    {
        port_value |= pin_mask;
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_CONFIG_P0 + port, port_value );
    }
    return error_flag;
}

err_t expand18_set_all_pins_direction ( expand18_t *ctx, uint8_t direction )
{
    if ( direction > EXPAND18_INPUT_DIRECTION )
    {
        return EXPAND18_ERROR;
    }
    err_t error_flag = EXPAND18_OK;
    if ( EXPAND18_OUTPUT_DIRECTION == direction )
    {
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_CONFIG_P0, ~EXPAND18_ALL_PINS_MASK );
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_CONFIG_P1, ~EXPAND18_ALL_PINS_MASK );
    }
    else
    {
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_CONFIG_P0, EXPAND18_ALL_PINS_MASK );
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_CONFIG_P1, EXPAND18_ALL_PINS_MASK );
    }
    return error_flag;
}

err_t expand18_set_pin_value ( expand18_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask )
{
    if ( port > EXPAND18_PORT_1 )
    {
        return EXPAND18_ERROR;
    }
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    err_t error_flag = expand18_read_register ( ctx, EXPAND18_REG_OUTPUT_P0 + port, &rx_data );
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    if ( rx_data != tx_data )
    {
        error_flag |= expand18_write_register ( ctx, EXPAND18_REG_OUTPUT_P0 + port, tx_data );
    }
    return error_flag;
}

err_t expand18_set_all_pins_value ( expand18_t *ctx, uint8_t set_mask )
{    
    err_t error_flag = expand18_write_register ( ctx, EXPAND18_REG_OUTPUT_P0, set_mask );
    error_flag |= expand18_write_register ( ctx, EXPAND18_REG_OUTPUT_P1, set_mask );
    return error_flag;
}

err_t expand18_read_port_value ( expand18_t *ctx, uint8_t port, uint8_t *data_out )
{
    if ( port > EXPAND18_PORT_1 )
    {
        return EXPAND18_ERROR;
    }
    return expand18_read_register ( ctx, EXPAND18_REG_INPUT_P0 + port, data_out );
}

// ------------------------------------------------------------------------- END

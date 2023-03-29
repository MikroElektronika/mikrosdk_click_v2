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
 * \file digipot5.c
 *
 */

#include "digipot5.h"


// ------------------------------------------------------------- PRIVATE MACROS

#define DIGIPOT5_DUMMY  0

//  DIGI POT 5 command bits of command byte.
#define DIGIPOT5_CMD_WRITE  0x00
#define DIGIPOT5_CMD_READ   0x0C
#define DIGIPOT5_CMD_INC    0x04
#define DIGIPOT5_CMD_DEC    0x08

//  DIGI POT 5 command error flag bit.
#define DIGIPOT5_CMDERR_FLAG  0x02

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
digipot5_cfg_setup( digipot5_cfg_t *cfg )
{
    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->sdo = HAL_PIN_NC;
    cfg->sdi = HAL_PIN_NC;

    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed   = 100000; 
}

digipot5_err_t
digipot5_init( digipot5_t *ctx, digipot5_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed       = cfg->spi_speed;
    spi_cfg.sck         = cfg->sck;
    spi_cfg.miso        = cfg->sdo;
    spi_cfg.mosi        = cfg->sdi;
    spi_cfg.default_write_data = DIGIPOT5_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DIGIPOT5_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DIGIPOT5_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high( &ctx->rst );

    return DIGIPOT5_STATUS_OK;
}

void
digipot5_reset( digipot5_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void
digipot5_default_cfg( digipot5_t *ctx )
{
    digipot5_generic_write( ctx, DIGIPOT5_REG_TCON0_VOL, 0xFF );
    digipot5_generic_write( ctx, DIGIPOT5_REG_TCON1_VOL, 0xFF );
}

digipot5_err_t
digipot5_generic_write( digipot5_t *ctx, digipot5_reg_t reg_addr,
                        uint16_t data_in )
{
    uint8_t tx_data[ 2 ] = { 0 };
    uint8_t rx_data[ 2 ] = { 0 };

    if ( reg_addr == DIGIPOT5_REG_STATUS_VOL )
    {
        return DIGIPOT5_ERROR_REG_ADDR;
    }

    //  Makes a command for data writing.
    tx_data[ 0 ] = reg_addr << 4;
    tx_data[ 0 ] |= ( data_in >> 8 ) & 0x01 | DIGIPOT5_CMD_WRITE;
    tx_data[ 1 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_data, 2, rx_data, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    if ( rx_data[ 0 ] & DIGIPOT5_CMDERR_FLAG )
    {
        return DIGIPOT5_STATUS_OK;
    }

    return DIGIPOT5_ERROR_CMD;
}

digipot5_err_t
digipot5_generic_read( digipot5_t *ctx, digipot5_reg_t reg_addr,
                       uint16_t *data_out )
{
    uint8_t tx_data = 0;
    uint8_t rx_data[ 2 ] = { 0 };

    //  Makes a command for data reading.
    tx_data = reg_addr << 4;
    tx_data |= DIGIPOT5_CMD_READ;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_data, 1, rx_data, 2 );
    spi_master_deselect_device( ctx->chip_select ); 

    *data_out = rx_data[ 0 ];
    *data_out <<= 8;
    *data_out &= 0x100;
    *data_out |= rx_data[ 1 ];

    if ( rx_data[ 0 ] & DIGIPOT5_CMDERR_FLAG )
    {
        return DIGIPOT5_STATUS_OK;
    }

    return DIGIPOT5_ERROR_CMD;
}

digipot5_reg_t
digipot5_increment_wiper( digipot5_t *ctx, digipot5_reg_t reg_addr )
{
    uint8_t tx_data = 0;
    uint8_t rx_data = 0;

    //  Only volatile wiper locations.
    if ( ( reg_addr != DIGIPOT5_REG_WIPER0_VOL ) &&
         ( reg_addr != DIGIPOT5_REG_WIPER1_VOL ) &&
         ( reg_addr != DIGIPOT5_REG_WIPER2_VOL ) &&
         ( reg_addr != DIGIPOT5_REG_WIPER3_VOL ) )
    {
        return DIGIPOT5_ERROR_REG_ADDR;
    }

    //  Makes a command for wiper incrementing.
    tx_data = reg_addr << 4;
    tx_data |= DIGIPOT5_CMD_INC;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_data, 1, &rx_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    if ( rx_data & DIGIPOT5_CMDERR_FLAG )
    {
        return DIGIPOT5_STATUS_OK;
    }

    return DIGIPOT5_ERROR_CMD;
}

digipot5_reg_t
digipot5_decrement_wiper( digipot5_t *ctx, digipot5_reg_t reg_addr )
{
    uint8_t tx_data = 0;
    uint8_t rx_data = 0;

    //  Only volatile wiper locations.
    if ( ( reg_addr != DIGIPOT5_REG_WIPER0_VOL ) &&
         ( reg_addr != DIGIPOT5_REG_WIPER1_VOL ) &&
         ( reg_addr != DIGIPOT5_REG_WIPER2_VOL ) &&
         ( reg_addr != DIGIPOT5_REG_WIPER3_VOL ) )
    {
        return DIGIPOT5_ERROR_REG_ADDR;
    }

    //  Makes a command for wiper decrementing.
    tx_data = reg_addr << 4;
    tx_data |= DIGIPOT5_CMD_DEC;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_data, 1, &rx_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    if ( rx_data & DIGIPOT5_CMDERR_FLAG )
    {
        return DIGIPOT5_STATUS_OK;
    }

    return DIGIPOT5_ERROR_CMD;
}

// ------------------------------------------------------------------------ END

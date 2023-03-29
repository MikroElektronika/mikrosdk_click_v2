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

#include "expand.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EXPAND_DUMMY 0


void expand_cfg_setup ( expand_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

EXPAND_RETVAL expand_init ( expand_t *ctx, expand_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EXPAND_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EXPAND_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EXPAND_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return EXPAND_OK;

}

uint8_t expand_read_byte ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr )
{
    uint8_t buffer_read[ 1 ];
    uint8_t buffer_write[ 2 ];
  
    mod_cmd <<= 1;
    buffer_write[ 0 ] = EXPAND_SPI_DEVICE_OPCODE | mod_cmd | EXPAND_OPCODE_READ;
    buffer_write[ 1 ] = reg_addr;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, buffer_write, 2 );
    spi_master_read( &ctx->spi, buffer_read, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return buffer_read[ 0 ];
}

void expand_write_byte ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t write_data )
{
    uint8_t buffer_write[ 3 ] = { 0x00 };
    
    mod_cmd <<= 1;
    buffer_write[ 0 ] = (EXPAND_SPI_DEVICE_OPCODE | mod_cmd) & EXPAND_OPCODE_WRITE;
    buffer_write[ 1 ] = reg_addr;
    buffer_write[ 2 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, buffer_write, 3 );
    spi_master_deselect_device( ctx->chip_select );
}

void expand_default_configuration ( expand_t *ctx, uint8_t mod_cmd )
{
    expand_reset( ctx );
    expand_write_byte( ctx, mod_cmd, EXPAND_IOCON_BANK0, ( EXPAND_IOCON_BYTE_MODE | EXPAND_IOCON_HAEN ) );    
}

void expand_set_bits ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask )
{
    uint8_t temp;

    temp = expand_read_byte( ctx, mod_cmd, reg_addr );

    temp |= bit_mask;

    expand_write_byte( ctx, mod_cmd, reg_addr, temp );
}

void expand_clear_bits ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask )
{
    uint8_t temp;

    temp = expand_read_byte( ctx, mod_cmd, reg_addr );

    temp &= ~bit_mask;

    expand_write_byte( ctx, mod_cmd, reg_addr, temp );
}

void expand_toggle_bits ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask )
{
    uint8_t temp;

    temp = expand_read_byte( ctx, mod_cmd, reg_addr );

    temp ^= bit_mask;

    expand_write_byte( ctx, mod_cmd, reg_addr, temp );
}

uint8_t expand_read_port_a ( expand_t *ctx, uint8_t mod_cmd )
{
    return expand_read_byte( ctx, mod_cmd, EXPAND_GPIOA_BANK0 );
}

uint8_t expand_read_port_b ( expand_t *ctx, uint8_t mod_cmd )
{
    return expand_read_byte( ctx, mod_cmd, EXPAND_GPIOB_BANK0 );
}

uint16_t expand_read_both_porta ( expand_t *ctx, uint8_t mod_cmd )
{
    uint16_t result;
    uint8_t buffer[ 2 ];

    buffer[ 0 ] = expand_read_port_a( ctx, mod_cmd );
    buffer[ 1 ] = expand_read_port_b( ctx, mod_cmd );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

void expand_write_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data )
{
    expand_write_byte( ctx, mod_cmd, EXPAND_OLATA_BANK0, write_data );
}

void expand_clear_bit_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_clear_bits( ctx,  mod_cmd, EXPAND_OLATA_BANK0, bit_mask );
}

void expand_set_bit_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_set_bits( ctx, mod_cmd, EXPAND_OLATA_BANK0, bit_mask );
}

void expand_toggle_bit_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_toggle_bits( ctx, mod_cmd, EXPAND_OLATA_BANK0, bit_mask );
}

void expand_write_port_b( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data )
{
    expand_write_byte( ctx, mod_cmd, EXPAND_OLATB_BANK0, write_data );
}

void expand_clear_bit_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_clear_bits( ctx, mod_cmd, EXPAND_OLATB_BANK0, bit_mask );
}

void expand_set_bit_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_set_bits( ctx, mod_cmd, EXPAND_OLATB_BANK0, bit_mask );
}

void expand_toggle_bit_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_toggle_bits( ctx, mod_cmd, EXPAND_OLATB_BANK0, bit_mask );
}

void expand_set_direction_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data )
{
    expand_write_byte( ctx, mod_cmd, EXPAND_IODIRA_BANK0, write_data );
}

void expand_set_input_dir_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_set_bits( ctx, mod_cmd, EXPAND_IODIRA_BANK0, bit_mask );
}

void expand_set_output_dir_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_clear_bits( ctx, mod_cmd, EXPAND_IODIRA_BANK0, bit_mask );
}

void expand_set_direction_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data )
{
    expand_write_byte( ctx, mod_cmd, EXPAND_IODIRB_BANK0, write_data );
}

void expand_set_input_dir_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_set_bits( ctx, mod_cmd, EXPAND_IODIRB_BANK0, bit_mask );
}

void expand_set_output_dir_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask )
{
    expand_clear_bits( ctx, mod_cmd, EXPAND_IODIRB_BANK0, bit_mask );
}

void expand_set_pull_ups_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data )
{
    expand_write_byte( ctx, mod_cmd, EXPAND_GPPUA_BANK0, write_data );
}

void expand_set_pull_ups_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data )
{
    expand_write_byte( ctx, mod_cmd, EXPAND_GPPUB_BANK0, write_data );
}

void expand_set_potr_a ( expand_t *ctx, uint8_t position )
{
    uint8_t write_data;

    position %= 8;

    write_data = 0x01 << position;

    expand_write_port_a( ctx, EXPAND_SPI_MODULE_POSITION_0, write_data );
}

void expand_set_potr_b ( expand_t *ctx, uint8_t position )
{
    uint8_t write_data;

    position %= 8;

    write_data = 0x01 << position;

    expand_write_port_b( ctx, EXPAND_SPI_MODULE_POSITION_0, write_data );
}

void expand_reset ( expand_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t expand_get_interrupt ( expand_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}
// ------------------------------------------------------------------------- END


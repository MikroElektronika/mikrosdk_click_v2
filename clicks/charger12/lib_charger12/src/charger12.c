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

#include "charger12.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CHARGER12_DUMMY 0

void charger12_cfg_setup ( charger12_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->che = HAL_PIN_NC;
    cfg->mod = HAL_PIN_NC;
    cfg->vok = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

CHARGER12_RETVAL charger12_init ( charger12_t *ctx, charger12_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CHARGER12_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CHARGER12_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CHARGER12_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    // Output pins 
    
    digital_out_init( &ctx->che, cfg->che );
    digital_out_init( &ctx->mod, cfg->mod );

    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->che );
    digital_out_low( &ctx->mod );

    // Input pins

    digital_in_init( &ctx->vok, cfg->vok );
    
    return CHARGER12_OK;
}

void charger12_generic_transfer ( charger12_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t tx_len, uint8_t rx_len )
{        
    uint8_t r_buf[ 256 ]; 
    uint8_t i;

    Delay_10ms( );
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write_then_read( &ctx->spi, data_in, tx_len, r_buf, rx_len );
    spi_master_deselect_device( ctx->chip_select );  

    for ( i = 0; i < rx_len; i++ )
    {
      data_out[ i ] = r_buf[ i ];
    }
}

uint8_t charger12_int_get ( charger12_t *ctx )
{
    return digital_in_read( &ctx->vok );
}

void charger12_pwm_set ( charger12_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->mod, pin_state  );
}

void charger12_rst_set ( charger12_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->che, pin_state  );
}

void charger12_cs_set ( charger12_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->cs, pin_state  );
}

uint8_t charger12_mode_select ( charger12_t *ctx, uint8_t mode_select )
{
    if ( mode_select > 3 ) return 1;
    
    switch ( mode_select )
    {
        case CHARGER12_MODE_Li:
        {
            digital_out_low( &ctx->che );
            digital_out_low( &ctx->mod );
            break;
        }
        case CHARGER12_MODE_NiMh_NiCd:
        {
            digital_out_low( &ctx->che );
            digital_out_high( &ctx->mod );
            break;
        }
        case CHARGER12_MODE_DISABLE:
        {
            digital_out_high( &ctx->che );
            digital_out_low( &ctx->mod );
            break;
        }
        case CHARGER12_MODE_NO_BATTERY:
        {
            digital_out_high( &ctx->che );
            digital_out_high( &ctx->mod );
            break;
        }
        default :
        {
            break;
        }
    }
    
    return 0;
}

void charger12_spi_set_register( charger12_t *ctx, uint8_t register_address, uint16_t register_value )
{
    uint8_t aux_i[ 2 ];
    uint8_t aux_o[ 2 ];

    aux_i[ 0 ] = register_address;
    aux_i[ 0 ] <<= 4;
    aux_i[ 0 ] &= 0xF0;
    aux_i[ 0 ] |= 0x02;

    register_value &= 0x03FF;

    aux_i[ 0 ] |= (uint8_t)( register_value >> 8 );
    
    aux_i[ 1 ] = (uint8_t)( register_value );

    charger12_generic_transfer( ctx, aux_i, aux_o, 2, 2 );
}

void charger12_spi_increment_wiper( charger12_t *ctx )
{
    uint8_t aux_i[ 1 ];
    uint8_t aux_o[ 1 ];

    aux_i[ 0 ] = 0x04;

    charger12_generic_transfer( ctx, aux_i, aux_o, 1, 1 );
}

void charger12_spi_decrement_wiper( charger12_t *ctx )
{
    uint8_t aux_i[ 1 ];
    uint8_t aux_o[ 1 ];

    aux_i[ 0 ] = 0x08;

    charger12_generic_transfer( ctx, aux_i, aux_o, 1, 1 );
}
// ------------------------------------------------------------------------- END


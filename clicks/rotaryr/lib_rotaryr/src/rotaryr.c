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
 * @file rotaryr.c
 * @brief ROTARY R Click Driver.
 */

#include "rotaryr.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define ROTARYR_DUMMY      0x00
#define ROTARY_LED_MOD       17

void rotaryr_cfg_setup ( rotaryr_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ecb   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->eca = HAL_PIN_NC;
    cfg->sw = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t rotaryr_init ( rotaryr_t *ctx, rotaryr_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;
    spi_cfg.default_write_data = ROTARYR_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, ROTARYR_DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
   
    // Input pins
    
    digital_in_init( &ctx->ecb, cfg->ecb );
    digital_in_init( &ctx->eca, cfg->eca );
    digital_in_init( &ctx->sw, cfg->sw );
    
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );

    return SPI_MASTER_SUCCESS;
}

void rotaryr_generic_transfer ( rotaryr_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len ) {

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select ); 
}

void rotaryr_turn_on_led_by_data ( rotaryr_t *ctx, uint16_t write_data ) {
    uint8_t temp_buf[ 2 ];

    temp_buf[ 0 ] = write_data >> 8;
    temp_buf[ 1 ] = write_data & 0x00FF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp_buf, 2 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );   
}

void rotaryr_turn_on_led_by_position ( rotaryr_t *ctx, uint8_t led_position ) {
    led_position %= ROTARY_LED_MOD;

    if ( led_position > 0 ) {
        rotaryr_turn_on_led_by_data( ctx, 1 << ( led_position - 1 ) );
    }
    if ( led_position == 0 ) {
        rotaryr_reset_led( ctx );
    }
}

uint8_t rotaryr_button_push ( rotaryr_t *ctx ) {
    return digital_in_read( &ctx->sw );
}

uint16_t rotaryr_get_led_data ( uint8_t current_led_state ) {
      switch ( current_led_state ) {
          case 0 : {
                return ROTARYR_ONE_LED;
                break;
          }
          case 1 : {
                return ROTARYR_TWO_LED;
                break;
          }
          case 2 : {
                return ROTARYR_FOUR_LED;
                break;
          }
          case 3 : {
                return ROTARYR_EIGHT_LED;
                break;
          }
          default : {
                return ROTARYR_ONE_LED;
                break;
          }
      }
}

void rotaryr_reset_led ( rotaryr_t *ctx ) {
    rotaryr_turn_on_led_by_data( ctx, ROTARYR_RESET_LED );
}

uint8_t rotaryr_get_ecb_state ( rotaryr_t *ctx ) {
    return digital_in_read( &ctx->ecb );
}

uint8_t rotaryr_get_eca_state ( rotaryr_t *ctx ) {
    return digital_in_read( &ctx->eca );
}


// ------------------------------------------------------------------------- END

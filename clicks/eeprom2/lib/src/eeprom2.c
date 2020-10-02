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

#include "eeprom2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EEPROM2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eeprom2_cfg_setup ( eeprom2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

EEPROM2_RETVAL eeprom2_init ( eeprom2_t *ctx, eeprom2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EEPROM2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EEPROM2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EEPROM2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return EEPROM2_OK;
}

void eeprom2_write ( eeprom2_t *ctx, uint32_t memory_address, uint8_t value )
{
    uint8_t tx_buf[ 5 ];
    tx_buf[ 0 ] = 0x02;
    tx_buf[ 1 ] = ( uint8_t )( ( memory_address >> 16 ) & 0x000000FF );
    tx_buf[ 2 ] = ( uint8_t )( ( memory_address >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = ( uint8_t )( memory_address & 0x000000FF );
    tx_buf[ 4 ] = value;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );  
}

void eeprom2_write_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count )
{
    uint8_t tx_buf[ 4 ];
    uint8_t i;
    tx_buf[ 0 ] = 0x02;
    tx_buf[ 1 ] = ( uint8_t )( ( memory_address >> 16 ) & 0x000000FF );
    tx_buf[ 2 ] = ( uint8_t )( ( memory_address >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = ( uint8_t )( memory_address & 0x000000FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_write( &ctx->spi, value, count );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t eeprom2_read( eeprom2_t *ctx, uint32_t memory_address )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 5 ];

    tx_buf[ 0 ] = 0x03;
    tx_buf[ 1 ] = ( uint8_t ) ( ( memory_address >> 16 ) & 0x000000FF );                       
    tx_buf[ 2 ] = ( uint8_t ) ( ( memory_address >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = ( uint8_t ) ( memory_address & 0x000000FF ); 

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    return rx_buf[ 0 ];
}

void eeprom2_read_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 256 ];
    uint8_t i; 
    eeprom2_memory_enable( ctx );

    tx_buf[ 0 ] = 0x03;
    tx_buf[ 1 ] = ( uint8_t )( ( memory_address >> 16 ) & 0x000000FF );
    tx_buf[ 2 ] = ( uint8_t )( ( memory_address >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = ( uint8_t )( memory_address & 0x000000FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, value, count );
    spi_master_deselect_device( ctx->chip_select );  
}

void eeprom2_memory_enable ( eeprom2_t *ctx )
{
    uint8_t temp;
    temp = 0x06;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &temp, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void eeprom2_memory_disable ( eeprom2_t *ctx )
{
    uint8_t temp;
    temp = 0x04;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &temp, 1 );
    spi_master_deselect_device( ctx->chip_select );  

}

// ------------------------------------------------------------------------- END


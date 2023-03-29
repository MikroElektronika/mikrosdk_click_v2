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

#include "digipot3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DIGIPOT3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t digipot3_check_command ( uint8_t command_check );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void digipot3_cfg_setup ( digipot3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

DIGIPOT3_RETVAL digipot3_init ( digipot3_t *ctx, digipot3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = DIGIPOT3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DIGIPOT3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DIGIPOT3_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->rdy, cfg->rdy );
    
    return DIGIPOT3_OK;
}

void digipot2_generic_transfer ( digipot3_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t digipot3_send_command ( digipot3_t *ctx, uint8_t command_byte )
{
    uint8_t tmp[ 3 ] = { 0 };
    uint8_t check_command;

    check_command = digipot3_check_command ( command_byte );

    if ( check_command )
    {
        return 1;
    }
    
    tmp[ 0 ] = command_byte << 4;
    while ( !digipot3_check_data_ready( ctx ) );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );  

    Delay_100ms( );
    
    if ( command_byte == 0x01 )
    {
        tmp[ 0 ] = 0x00;
        while ( !digipot3_check_data_ready( ctx ) );
    
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tmp, 3 );
        spi_master_deselect_device( ctx->chip_select );    

          Delay_5ms( );
    }
    
    return 0;
}

uint8_t digipot3_store_eemem ( digipot3_t *ctx, uint8_t location_address, uint16_t transfer_data )
{
    uint8_t tmp[ 3 ] = { 0 };
    
    if ( ( location_address < 0x01 ) || ( location_address > 0x0F ) )
    {
        return 1;
    }
        
    tmp[ 0 ] = 0x30 | location_address;
    tmp[ 1 ] = transfer_data >> 8;
    tmp[ 2 ] = transfer_data;

    while ( !digipot3_check_data_ready( ctx ) );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    
      Delay_5ms( );
    
    return 0;
}

uint8_t digipot3_read_eemem ( digipot3_t *ctx, uint8_t location_address, uint16_t *data_out )
{
    uint8_t tmp[ 3 ] = { 0 };
    uint16_t temp = 0;
    
    if ( location_address > 0x0F )
    {
        return 1;
    }

    tmp[ 0 ] = 0x90 | location_address;

    while ( !digipot3_check_data_ready( ctx ) );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_5ms( );
    
    while ( !digipot3_check_data_ready( ctx ) );

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_5ms( );

    temp = tmp[ 1 ];
    temp <<= 8;
    temp |= tmp[ 2 ];
    *data_out = temp;
    
    return 0;
}

uint8_t digipot3_write_dac ( digipot3_t *ctx, uint16_t value_dac )
{
    uint8_t tmp[ 3 ] = { 0 };
    
    if ( value_dac > 0x03FF )
        return 1;
        
    tmp[ 0 ] = 0xB0;
    tmp[ 1 ] = value_dac >> 8;
    tmp[ 2 ] = value_dac;
    while ( !digipot3_check_data_ready( ctx ) );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_5ms(  );

    return 0;
}

void digipot3_read_dac ( digipot3_t *ctx, uint16_t *data_out )
{
    uint8_t tmp[ 3 ] = { 0 };
    uint16_t temp = 0;
    
    tmp[ 0 ] = 0xA0;
    while ( !digipot3_check_data_ready( ctx ) );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );
      Delay_5ms( );
    
    while ( !digipot3_check_data_ready( ctx ) );

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, tmp, 3 );
    spi_master_deselect_device( ctx->chip_select );
      Delay_5ms( );
    
    temp = tmp[ 1 ];
    temp <<= 8;
    temp |= tmp[ 2 ];
    *data_out = temp;
}

uint8_t digipot3_check_data_ready( digipot3_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->rdy );

    if ( state ) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t digipot3_check_command ( uint8_t command_check )
{
    switch ( command_check )
    {
        case 0x00 :
        {
            return 0;
        }
        case 0x01 :
        {
            return 0;
        }
        case 0x02 :
        {
            return 0;
        }
        case 0x04 :
        {
            return 0;
        }
        case 0x05 :
        {
            return 0;
        }
        case 0x06 :
        {
            return 0;
        }
        case 0x07 :
        {
            return 0;
        }
        case 0x08 :
        {
            return 0;
        }
        case 0x0C :
        {
            return 0;
        }
        case 0x0D :
        {
            return 0;
        }
        case 0x0E :
        {
            return 0;
        }
        case 0x0F :
        {
            return 0;
        }
        default :
        {
            return 1;
        }
    }
}

// ------------------------------------------------------------------------- END


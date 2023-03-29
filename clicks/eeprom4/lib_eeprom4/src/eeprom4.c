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

#include "eeprom4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EEPROM4_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eeprom4_cfg_setup ( eeprom4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wp = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

EEPROM4_RETVAL eeprom4_init ( eeprom4_t *ctx, eeprom4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EEPROM4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EEPROM4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EEPROM4_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );

    return EEPROM4_OK;
}

void eeprom4_default_cfg ( eeprom4_t *ctx )
{
    eeprom4_enable_write_protect( ctx, EEPROM4_LOGIC_HIGH );
    eeprom4_send_command( ctx, EEPROM4_SET_WRITE_ENABLE_LATCH_COMMAND );
    eeprom4_write_status_reg( ctx, EEPROM4_NONE_PROTECTED_MEMORY_LOCATION );
    eeprom4_enable_hold_operation( ctx, EEPROM4_LOGIC_HIGH );
}

void eeprom4_generic_transfer ( eeprom4_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

uint8_t eeprom4_send_command ( eeprom4_t *ctx, uint8_t command_byte )
{
    uint8_t ret_val = 0;

    if ( command_byte == EEPROM4_LOW_POWER_WRITE_POLL_COMMAND )
    {
        spi_master_select_device( ctx->chip_select );

        spi_master_write( &ctx->spi, &command_byte, 1 );
        spi_master_read( &ctx->spi, &ret_val, 1 );

        spi_master_deselect_device( ctx->chip_select );    
        
        return ret_val;
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, &command_byte, 1 );
        spi_master_deselect_device( ctx->chip_select );    
        
        return 0;
    }
}

void eeprom4_write_status_reg ( eeprom4_t *ctx, uint8_t data_value )
{
    uint8_t tx_data = 0x01;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &tx_data, 1 );
    spi_master_write( &ctx->spi, &data_value, 1 );

    spi_master_deselect_device( ctx->chip_select );    
}

uint8_t eeprom4_read_status_reg ( eeprom4_t *ctx )
{
    uint8_t data_value = 0;
    uint8_t tx_data = 0x05;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &tx_data, 1 );
    spi_master_read( &ctx->spi, &data_value, 1 );

    spi_master_deselect_device( ctx->chip_select );    

    return data_value;
}

void eeprom4_write_memory ( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_input, uint8_t n_bytes )
{
    uint8_t cnt = 0;
    uint8_t tx_data[ 4 ];

    tx_data[ 0 ] = 0x02;
    tx_data[ 1 ] = memory_address >> 16;
    tx_data[ 2 ] = memory_address >> 8;
    tx_data[ 3 ] = memory_address;

    spi_master_select_device( ctx->chip_select );
     
    spi_master_write( &ctx->spi, tx_data, 4 );
    spi_master_write( &ctx->spi, data_input, n_bytes );

    spi_master_deselect_device( ctx->chip_select );      
}

void eeprom4_read_memory ( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_output, uint8_t n_bytes )
{
    uint8_t cnt = 0;
    uint8_t tx_data[ 4 ];

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = memory_address >> 16;
    tx_data[ 2 ] = memory_address >> 8;
    tx_data[ 3 ] = memory_address;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_data, 4 );
    spi_master_read( &ctx->spi, data_output, n_bytes );
        
    spi_master_deselect_device( ctx->chip_select );      
}

void eeprom4_enable_write_protect ( eeprom4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wp, state );
}

void eeprom4_enable_hold_operation ( eeprom4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->hld, state );
}

uint8_t eeprom4_check_status_reg ( eeprom4_t *ctx, uint8_t check_bit )
{
    uint8_t status_state = 0;
    uint8_t ret_val = 0;
    
    status_state = eeprom4_read_status_reg( ctx );
    
    ret_val = status_state & check_bit;
    
    if ( ( ret_val == 0x01 ) || ( ret_val == 0x02 ) || ( ret_val == 0x08 ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ------------------------------------------------------------------------- END


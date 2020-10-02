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

#include "touchkey3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define TOUCHKEY3_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void touchkey3_cfg_setup ( touchkey3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck   = HAL_PIN_NC;
    cfg->miso  = HAL_PIN_NC;
    cfg->mosi  = HAL_PIN_NC;
    cfg->cs    = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

TOUCHKEY3_RETVAL touchkey3_init ( touchkey3_t *ctx, touchkey3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = TOUCHKEY3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return TOUCHKEY3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, TOUCHKEY3_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );


    spi_master_deselect_device( ctx->chip_select );
    Delay_100ms();

    return TOUCHKEY3_OK;
}

void touchkey3_reset ( touchkey3_t *ctx )
{
    digital_out_write( &ctx->rst, 0 );
    Delay_100ms();
    digital_out_write( &ctx->rst, 1 );
    Delay_100ms();
}

void touchkey3_generic_transfer 
( 
    touchkey3_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void touchkey3_send_command ( touchkey3_t *ctx, uint8_t command )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us();
    spi_master_write( &ctx->spi, &command, 1 );
    Delay_10us();
    spi_master_deselect_device( ctx->chip_select );
    Delay_10us();  
}

void touchkey3_send_setup ( touchkey3_t *ctx, uint8_t *p_setup_data )
{
    uint8_t i;
    uint8_t command = TOUCHKEY3_CMD_SENDSETUP;

    spi_master_select_device( ctx->chip_select );
    Delay_10us();
    spi_master_write( &ctx->spi, &command, 1 );
    Delay_1ms();

    for ( i = 0; i < 42; i++ )
    {
        spi_master_write( &ctx->spi, &p_setup_data[ i ], 1 );
        Delay_1ms();
    }

    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms();  
}

void touchkey3_send_request ( touchkey3_t *ctx, uint8_t request, uint8_t *p_response )
{
    uint8_t i = 0;

    spi_master_select_device( ctx->chip_select );
    Delay_10us();
    spi_master_write( &ctx->spi, &request, 1 );
    Delay_1ms();

    if ( request == TOUCHKEY3_REQ_SETUP_DATA )
    {    
        for ( i = 0; i < 42; i++ )
        {
            spi_master_read( &ctx->spi, &p_response[ i ], 1 );
            Delay_1ms();
        }
    }
    else if ( request == TOUCHKEY3_REQ_ALL_KEYS || request == TOUCHKEY3_REQ_ERROR_KEYS )
    {
        for ( i = 0; i < 2; i++ )
        {
            spi_master_read( &ctx->spi, &p_response[ i ], 1 );
            Delay_1ms();
        }
    }
    else if ( ( request >> 4 ) == 2 || ( request >> 4 ) == 4 )
    {

        for ( i = 0; i < 2; i++ )
        {
            spi_master_read( &ctx->spi, &p_response[ i ], 1 );
            Delay_1ms();
        }
    }
    else
    {
        spi_master_read( &ctx->spi, &p_response[ 0 ], 1 );
        Delay_1ms();
    }

    spi_master_deselect_device( ctx->chip_select );
    Delay_10us();
    
}

void touchkey3_set_data ( touchkey3_t *ctx, uint8_t data_address, uint8_t write_data )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us();
    spi_master_write( &ctx->spi, &data_address, 1 );
    Delay_1ms();
    spi_master_write( &ctx->spi, &write_data, 1 );
    Delay_1ms();
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms();  
}

void touchkey3_get_data ( touchkey3_t *ctx, uint8_t data_address, uint8_t *read_data )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us();
    spi_master_write( &ctx->spi, &data_address, 1 );
    Delay_1ms();
    spi_master_read( &ctx->spi, &read_data[ 0 ], 1 );
    Delay_1ms();
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms(); 
}

// ------------------------------------------------------------------------- END


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

#include "rs232spi.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RS232SPI_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rs232spi_cfg_setup ( rs232spi_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->sdn = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

RS232SPI_RETVAL rs232spi_init ( rs232spi_t *ctx, rs232spi_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode; 
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = RS232SPI_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return RS232SPI_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, RS232SPI_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->sdn, cfg->sdn );

    // Input pins

    digital_in_init( &ctx->irq, cfg->irq );

    spi_master_deselect_device( ctx->chip_select ); 

    return RS232SPI_OK;
}

void rs232spi_default_cfg ( rs232spi_t *ctx, uint32_t speed )
{
    uint16_t cfg;

    switch ( speed )
    {
        case 230400: 
        {
            cfg = RS232SPI_CONF_BAUD_X2_230400; 
            break;
        }
        case 115200:
        {
            cfg = RS232SPI_CONF_BAUD_X2_115200;
            break;
        }
        case 57600:
        {
            cfg = RS232SPI_CONF_BAUD_X2_57600;
            break;
        }
        case 38400:
        {
            cfg = RS232SPI_CONF_BAUD_X2_38400;
            break;
        }
        case 19200:
        {
            cfg = RS232SPI_CONF_BAUD_X2_19200; 
            break;
        }
        case 4800:
        {
            cfg = RS232SPI_CONF_BAUD_X2_4800; 
            break;
        }
        case 2400:
        {
            cfg = RS232SPI_CONF_BAUD_X2_2400; 
            break;
        }
        case 1200:
        {
            cfg = RS232SPI_CONF_BAUD_X2_1200; 
            break;
        }
        case 600:
        {
            cfg = RS232SPI_CONF_BAUD_X2_600; 
            break;
        }
        default:
        {
            cfg = RS232SPI_CONF_BAUD_X2_9600;
        }
    }

    rs232spi_reg_write( ctx, RS232SPI_CMD_WRITE_CONF | RS232SPI_CONF_RM | cfg );
}

void rs232spi_data_write ( rs232spi_t *ctx, uint8_t write_data )
{
    rs232spi_reg_write( ctx, RS232SPI_CMD_WRITE_DATA | write_data );
}

uint16_t rs232spi_check_busy ( rs232spi_t *ctx )
{
    uint16_t temp;
    
    temp = rs232spi_transfer( ctx, RS232SPI_CMD_READ_CONF );
    
    return (!( temp & RS232SPI_CONF_T ));
}

void rs232spi_flush ( rs232spi_t *ctx )
{
    while ( rs232spi_check_busy( ctx ) );
}

uint16_t rs232spi_data_ready ( rs232spi_t *ctx )
{
    return rs232spi_transfer( ctx, RS232SPI_CMD_READ_CONF ) & RS232SPI_CONF_R;
}

uint16_t rs232spi_read_cfg ( rs232spi_t *ctx )
{
    return rs232spi_transfer( ctx, RS232SPI_CMD_READ_CONF );
}

void rs232spi_reg_write ( rs232spi_t *ctx, uint16_t write_data )
{
    uint8_t tmp;
    
    tmp = write_data >> 8;
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tmp, 1 );
    tmp = write_data & 0xFF;
    spi_master_write( &ctx->spi, &tmp, 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t rs232spi_reg_read ( rs232spi_t *ctx )
{
    int16_t result;
    uint16_t temp;

    result = -1;
    
    temp = rs232spi_transfer( ctx, RS232SPI_CMD_READ_DATA );

    if ( temp & RS232SPI_CONF_R )
    {
        result = ( uint8_t ) temp & 0xFF;
    }

    return result;
}

uint16_t rs232spi_transfer ( rs232spi_t *ctx, uint16_t write_data )
{
    uint16_t result;
    uint8_t write_buf[ 2 ];
    uint8_t read_buf[ 2 ];

    write_buf[ 0 ] = ( uint8_t ) write_data >> 8;
    write_buf[ 1 ] = ( uint8_t ) write_data & 0xFF;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, write_buf[ 0 ] );
    spi_master_read( &ctx->spi, &read_buf[ 0 ],1  );
    spi_master_set_default_write_data( &ctx->spi, write_buf[ 1 ] );
    spi_master_read( &ctx->spi, &read_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    spi_master_set_default_write_data( &ctx->spi, RS232SPI_DUMMY );
    
    result = read_buf[ 0 ];
    result <<= 8;
    result |= read_buf[ 1 ];

    return result;
}

void rs232spi_digital_write_rst ( rs232spi_t *ctx, uint8_t signal )
{
    digital_out_write( &ctx->sdn, signal );
}

uint8_t rs232spi_digital_read_int ( rs232spi_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

// ------------------------------------------------------------------------- END


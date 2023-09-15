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
 * @file utl7segb.c
 * @brief UT-L 7-SEG B Click Driver.
 */

#include "utl7segb.h"

/**
 * @brief Dummy and dot position data.
 * @details Definition of dummy and dot position data.
 */
#define DUMMY                    0x00
#define UTL7SEGB_DOT_POSITION    0x80

/**
 * @brief Hexadecimal numeric matrix data.
 * @details Definition of hexadecimal numeric matrix data array.
 */
static const uint8_t hex_num_matrix[ 16 ] =
{
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F,  // 9
    0x77,  // A
    0x7C,  // B
    0x39,  // C
    0x5E,  // D
    0x79,  // E
    0x71   // F
};

void utl7segb_cfg_setup ( utl7segb_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->oe   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t utl7segb_init ( utl7segb_t *ctx, utl7segb_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

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

    digital_out_init( &ctx->oe, cfg->oe );

    return SPI_MASTER_SUCCESS;
}

err_t utl7segb_default_cfg ( utl7segb_t *ctx ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    utl7segb_disable( ctx );
    err_t err_flag = utl7segb_generic_write( ctx, data_buf, 2 );
    utl7segb_enable( ctx );
    return err_flag;
}

err_t utl7segb_generic_write ( utl7segb_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t utl7segb_generic_read ( utl7segb_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void utl7segb_enable ( utl7segb_t *ctx ) 
{
    digital_out_high( &ctx->oe );
}

void utl7segb_disable ( utl7segb_t *ctx ) 
{
    digital_out_low( &ctx->oe );
}

err_t utl7segb_display_number ( utl7segb_t *ctx, uint8_t base, uint8_t num, uint8_t dot_pos ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    err_t err_flag = UTL7SEGB_OK;

    if ( ( ( base * base - 1 ) < num ) || ( UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL < base ) ) 
    {
        err_flag = UTL7SEGB_ERROR;
    }
    else
    {
        data_buf[ 1 ] = hex_num_matrix[ num / base ];
        data_buf[ 0 ] = hex_num_matrix[ num % base ];
        switch ( dot_pos ) 
        {
            case UTL7SEGB_NO_DOT:
            {
                err_flag = UTL7SEGB_OK;
                break;
            }
            case UTL7SEGB_DOT_RIGHT:
            {
                data_buf[ 0 ] |= UTL7SEGB_DOT_POSITION;
                break;
            }
            case UTL7SEGB_DOT_LEFT:
            {
                data_buf[ 1 ] |= UTL7SEGB_DOT_POSITION;
                break;
            }
            case UTL7SEGB_DOT_LEFT_RIGHT:
            {
                data_buf[ 1 ] |= UTL7SEGB_DOT_POSITION;
                data_buf[ 0 ] |= UTL7SEGB_DOT_POSITION;
                break;
            }
            default:
            {
                err_flag = UTL7SEGB_ERROR;
                break;
            }
        }

        if ( hex_num_matrix[ 0 ] == data_buf[ 1 ] ) 
        {
            data_buf[ 1 ] = DUMMY;
        }
        err_flag |= utl7segb_generic_write( ctx, data_buf, 2 );
    }
    return err_flag;
}

err_t utl7segb_get_number ( utl7segb_t *ctx, uint8_t base, uint8_t *num, uint8_t *dot_pos ) 
{
    uint8_t rx_data[ 2 ] = { DUMMY };
    uint8_t l_num = DUMMY, r_num = DUMMY;
    err_t err_flag = UTL7SEGB_OK; 
    
    if ( UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL < base  ) 
    {
        err_flag = UTL7SEGB_ERROR;
    }
    else
    {
        err_flag |= utl7segb_generic_read( ctx, rx_data, 2 );
        *dot_pos = UTL7SEGB_NO_DOT;
        
        if ( ( UTL7SEGB_DOT_POSITION & rx_data[ 0 ] ) && ( UTL7SEGB_DOT_POSITION & rx_data[ 1 ] ) )
        {
            *dot_pos = UTL7SEGB_DOT_LEFT_RIGHT;
        }
        else if ( UTL7SEGB_DOT_POSITION & rx_data[ 1 ] )
        {
            *dot_pos = UTL7SEGB_DOT_LEFT;
        }
        else if ( UTL7SEGB_DOT_POSITION & rx_data[ 0 ] )
        {
            *dot_pos = UTL7SEGB_DOT_RIGHT;
        }
        
        rx_data[ 0 ] &= ~UTL7SEGB_DOT_POSITION;
        rx_data[ 1 ] &= ~UTL7SEGB_DOT_POSITION;
        
        for ( uint8_t cnt = 0; cnt < UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL; cnt++ )
        {
            if ( hex_num_matrix[ cnt ] == rx_data[ 1 ] )
            {
                l_num = cnt;
            }
            if ( hex_num_matrix[ cnt ] == rx_data[ 0 ] )
            {
                r_num = cnt;
            }
        }
        *num = l_num * base + r_num;
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END

/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file pressure26.c
 * @brief Pressure 26 Click Driver.
 */

#include "pressure26.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Pressure 26 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #pressure26_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t pressure26_get_parity_bit ( uint16_t data_in );

void pressure26_cfg_setup ( pressure26_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wkp  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t pressure26_init ( pressure26_t *ctx, pressure26_cfg_t *cfg ) 
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

    digital_in_init( &ctx->wkp, cfg->wkp );
    
    /* After power-on, first sensor response is always identifier */
    ctx->prev_cmd = PRESSURE26_CMD_ACQUIRE_IDENTIFIER;

    PRESSURE26_SET_DATA_SAMPLE_EDGE;

    Delay_100ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t pressure26_send_cmd ( pressure26_t *ctx, uint8_t cmd, uint16_t *prev_rsp )
{
    err_t error_flag = PRESSURE26_OK;
    uint8_t rsp_buf[ 2 ] = { 0 };
    uint16_t rsp = 0;

    spi_master_select_device( ctx->chip_select );
    
    /* send first BYTE of a command and read MSB of response*/
    spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag |= spi_master_read( &ctx->spi, &rsp_buf[ 0 ], 1 );

    /* send second BYTE of a command and read LSB of response*/
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rsp_buf[ 1 ], 1 );

    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );

    if ( PRESSURE26_OK == error_flag )
    { 
        /* Assemble 16-bit response from two bytes.
         * This response is an answer to a PREVIOUS command (N-1). */
        rsp = ( ( uint16_t ) rsp_buf[ 0 ] << 8 ) | rsp_buf[ 1 ];
        
        /* response to the acquire_identifier command does not have a parity bit */
        if ( PRESSURE26_CMD_ACQUIRE_IDENTIFIER != ctx->prev_cmd )
        {   
            /* Odd parity check */
            if ( ( rsp_buf[ 1 ] & PRESSURE26_ODD_PARITY ) == pressure26_get_parity_bit ( rsp ) )
            {
                error_flag = PRESSURE26_ERROR;
            }
        }
        ctx->prev_cmd = cmd;
    }

    if ( ( PRESSURE26_OK == error_flag ) && ( NULL != prev_rsp ) )
    {
        *prev_rsp = rsp;
    }

    return error_flag;
}

err_t pressure26_get_pressure ( pressure26_t *ctx, float *press )
{
    err_t error_flag = PRESSURE26_OK;
    uint16_t rsp = 0;
    
    /* Frame N: trigger pressure acquisition */
    error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_ACQUIRE_PRESSURE_14BIT, NULL );

    if ( PRESSURE26_OK == error_flag )
    {
        /* Frame N+1: read response to frame N */
        error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_RESET_DIAG, &rsp );
    }
    if ( PRESSURE26_OK == error_flag )
    {
        /* In 14-bit mode only bit 15 is available as diagnosis(Internal Error) */
        if ( rsp & PRESSURE26_DIAG_14BIT_INTERNAL_ERROR )
        {
            error_flag = PRESSURE26_ERROR;
        }
    }
    if ( PRESSURE26_OK == error_flag )
    {
        /* rsp >> 1: shift out parity bit (bit 0).
         * Formula: pamb_mBar = (outp - offsp) / Sp */
        *press = ( ( rsp >> 1 ) - PRESSURE26_OFFSP_14BIT ) / PRESSURE26_SP_14BIT;
    }

    return error_flag;
}

err_t pressure26_get_temperature ( pressure26_t *ctx, float *temp )
{
    err_t error_flag = PRESSURE26_OK;
    uint16_t rsp = 0;
    
    /* Frame N: trigger temperature acquisition */
    error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_ACQUIRE_TEMPERATURE_14BIT, NULL );

    if ( PRESSURE26_OK == error_flag )
    {
        /* Frame N+1: read response to frame N */
        error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_RESET_DIAG, &rsp );
    }
    if ( PRESSURE26_OK == error_flag )
    {   
        /* In 14-bit mode only bit 15 is available as diagnosis(Internal Error) */
        if ( rsp & PRESSURE26_DIAG_14BIT_INTERNAL_ERROR )
        {
            error_flag = PRESSURE26_ERROR;
        }
    }
    if ( PRESSURE26_OK == error_flag )
    {   
        /* rsp >> 1: shift out parity bit (bit 0).
         * Formula: Tamb = (outT - offsT) / ST */
        *temp = ( ( rsp >> 1 ) - PRESSURE26_OFFST_14BIT_3V3 ) / PRESSURE26_ST_14BIT;
    }

    return error_flag;
}

err_t pressure26_get_identifier ( pressure26_t *ctx, uint16_t *identifier )
{
    err_t error_flag = PRESSURE26_OK;
    
    /* Frame N: send identifier command */
    error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_ACQUIRE_IDENTIFIER, NULL );

    if ( PRESSURE26_OK == error_flag )
    {
        /* Frame N+1: prev_cmd is ACQUIRE_IDENTIFIER -> parity check is skipped */ 
        error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_RESET_DIAG, identifier );
    }

    return error_flag;
}

err_t pressure26_power_down ( pressure26_t *ctx )
{   
    /* no meaningful data is returned for mode-change commands */
    return pressure26_send_cmd( ctx, PRESSURE26_CMD_TRIGGER_POWER_DOWN, NULL );
}

err_t pressure26_trigger_lpm ( pressure26_t *ctx )
{   
    /* no meaningful data is returned for mode-change commands */
    return pressure26_send_cmd( ctx, PRESSURE26_CMD_TRIGGER_LPM, NULL );
}

err_t pressure26_get_lpm_status ( pressure26_t *ctx, uint16_t *lpm_status )
{
    err_t error_flag = PRESSURE26_OK;
    
    /* Frame N: request LPM status register */
    error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_ACQUIRE_LPM_STATUS, NULL );

    if ( PRESSURE26_OK == error_flag )
    {
        /* Frame N+1: read 16-bit status register as a response to frame N command */
        error_flag = pressure26_send_cmd( ctx, PRESSURE26_CMD_RESET_DIAG, lpm_status );
    }
    return error_flag;
}

uint8_t pressure26_get_wkp_pin ( pressure26_t *ctx )
{  
    /* WUOUT goes HIGH on: power-on, LPM threshold exceeded, diagnostic error, communication error */
    return digital_in_read( &ctx->wkp );
}

static uint8_t pressure26_get_parity_bit ( uint16_t data_in )
{
    uint8_t parity = 0;
    for ( uint8_t cnt = 1; cnt < 16; cnt++ )
    {
        parity += ( ( data_in >> cnt ) & PRESSURE26_ODD_PARITY );
    }
    return parity & PRESSURE26_ODD_PARITY;
}

// ------------------------------------------------------------------------- END

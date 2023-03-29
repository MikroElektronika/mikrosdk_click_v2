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
 * @file c420mat2.c
 * @brief 4-20mA T 2 Click Driver.
 */

#include "c420mat2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                       0xFF

/**
 * @brief Communication bitmask.
 * @details Definition of communication multiple read bitmask.
 */
#define SPI_READ_MASK               0x80

/**
 * @brief DAC 16-bit data value.
 * @details Definition of DAC 16-bit data value.
 */
#define DACCODE_DATA_16_BIT         0xFFFF

/**
 * @brief Current (mA) data value.
 * @details Definition of current (mA) data value.
 */
#define ERR_CURRENT_LIMIT_12_mA     12.0
#define CURRENT_LIMIT_RANGE_MIN      2.0
#define CURRENT_LIMIT_RANGE_MAX     24.1
#define CURRENT_OUTPUT_RANGE_MIN     3.9
#define CURRENT_OUTPUT_RANGE_MAX    20.0

void c420mat2_cfg_setup ( c420mat2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->err = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c420mat2_init ( c420mat2_t *ctx, c420mat2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->err, cfg->err );

    digital_out_high( &ctx->rst );

    return SPI_MASTER_SUCCESS;
}

err_t c420mat2_default_cfg ( c420mat2_t *ctx ) 
{    
    err_t err_flag = c420mat2_sw_reset( ctx );
    
    err_flag |= c420mat2_write_data( ctx, C420MAT2_REG_NOP, C420MAT2_CMD_NOP );
    err_flag |= c420mat2_write_data( ctx, C420MAT2_REG_WR_MODE, C420MAT2_CMD_WR_MODE_DISABLE );
    err_flag |= c420mat2_write_data( ctx, C420MAT2_REG_ERR_CONFIG, C420MAT2_CMD_RETRY_TIMEL_RETRY_TIME_400ms 
                                                                 | C420MAT2_CMD_DIS_RETRY_LOOP_ENABLE
                                                                 | C420MAT2_CMD_MASK_SPI_ERR_ENABLE
                                                                 | C420MAT2_CMD_SPI_TIMEOUT_400ms );

    err_flag |= c420mat2_set_lower_limit( ctx, CURRENT_LIMIT_RANGE_MIN );
    err_flag |= c420mat2_set_upper_limit( ctx, CURRENT_LIMIT_RANGE_MAX );

    return err_flag;
}

err_t c420mat2_write_data ( c420mat2_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t tx_buf[ 6 ] = { 0 };
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) data_in;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t c420mat2_read_data ( c420mat2_t *ctx, uint8_t cmd, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    cmd |= SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write_then_read( &ctx->spi, &cmd, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    return err_flag;
}

err_t c420mat2_protected_write ( c420mat2_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t tx_buf[ 3 ] = { 0 };
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) data_in;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t c420mat2_sw_reset ( c420mat2_t *ctx ) 
{
    err_t err_flag = c420mat2_write_data( ctx, C420MAT2_REG_RESET, C420MAT2_CMD_RESET );
    err_flag |= c420mat2_write_data( ctx, C420MAT2_CMD_NOP, DUMMY );
    return err_flag;
}

err_t c420mat2_set_dac_data ( c420mat2_t *ctx, uint16_t dac_output_code ) 
{
    return c420mat2_write_data( ctx, C420MAT2_REG_DACCODE, dac_output_code );
}

err_t  c420mat2_set_lower_limit ( c420mat2_t *ctx, float upper_limit_ma ) 
{
    err_t err_flag = C420MAT2_OK;

    if ( upper_limit_ma > ERR_CURRENT_LIMIT_12_mA )
    {
        err_flag |= C420MAT2_ERROR;
    }
    else
    {
        err_flag |= c420mat2_write_data( ctx, C420MAT2_REG_ERR_HIGH, 
                                         ( uint16_t ) ( ( DACCODE_DATA_16_BIT * upper_limit_ma ) 
                                         / CURRENT_LIMIT_RANGE_MAX ) );    
    }

    return err_flag;
}

err_t c420mat2_set_upper_limit ( c420mat2_t *ctx, float lower_limit_ma ) 
{
    err_t err_flag = C420MAT2_OK;

    if ( lower_limit_ma < ERR_CURRENT_LIMIT_12_mA )
    {
        err_flag |= C420MAT2_ERROR;
    }
    else
    {
        err_flag |= c420mat2_write_data( ctx, C420MAT2_REG_ERR_LOW, 
                                         ( uint16_t ) ( ( DACCODE_DATA_16_BIT * lower_limit_ma ) 
                                         / CURRENT_LIMIT_RANGE_MAX ) );    
    }

    return err_flag;
}

err_t c420mat2_set_output_current ( c420mat2_t *ctx, float current_ma ) 
{
    err_t err_flag = C420MAT2_OK;

    if ( ( current_ma < CURRENT_OUTPUT_RANGE_MIN ) || ( current_ma > CURRENT_OUTPUT_RANGE_MAX ) )
    {
        err_flag |= C420MAT2_ERROR;
    }
    else
    {
        err_flag |= c420mat2_set_dac_data( ctx, ( uint16_t ) ( ( DACCODE_DATA_16_BIT * current_ma ) 
                                            / CURRENT_LIMIT_RANGE_MAX ) );    
    }

    return err_flag;
}

err_t c420mat2_get_status ( c420mat2_t *ctx, c420mat2_status_t *status ) 
{
    uint16_t status_data;
    err_t err_flag = c420mat2_read_data( ctx, C420MAT2_REG_STATUS, &status_data );
    status->errlvl_pin      = ( uint8_t ) ( ( status_data & C420MAT2_STATUS_ERRLVL_PIN_BIT_MASK ) >> 4 );
    status->ferr_sts        = ( uint8_t ) ( ( status_data & C420MAT2_STATUS_FERR_STS_BIT_MASK ) >> 3 );
    status->spi_timeout_err = ( uint8_t ) ( ( status_data & C420MAT2_STATUSSPI_TIMEOUT_ERR_BIT_MASK ) >> 2 );
    status->loop_sts        = ( uint8_t ) ( ( status_data & C420MAT2_STATUS_LOOP_STS_BIT_MASK ) >> 3 );
    status->curr_loop_sts   = ( uint8_t ) (   status_data & C420MAT2_STATUS_CURR_LOOP_STS_BIT_MASK );
    return err_flag;
}

uint8_t c420mat2_get_err_pin ( c420mat2_t *ctx )
{
    return digital_in_read( &ctx->err );
}


// ------------------------------------------------------------------------- END

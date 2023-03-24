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
 * @file reram2.c
 * @brief ReRAM 2 Click Driver.
 */

#include "reram2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Resistive Random Access Memory data.
 * @details Definition of Resistive Random Access Memory data.
 */
#define RERAM2_MEM_ADDR_END           0x000FFFFF
#define RERAM2_TRANSFER_BYTES_MIN     1
#define RERAM2_TRANSFER_BYTES_MAX     256

/**
 * @brief Wake up delay.
 * @details Wake up delay for 10 milliseconds.
 */
static void dev_wake_up_delay ( void );

void reram2_cfg_setup ( reram2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ho = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t reram2_init ( reram2_t *ctx, reram2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ho, cfg->ho );
    digital_out_init( &ctx->wp, cfg->wp );

    return SPI_MASTER_SUCCESS;
}

err_t reram2_default_cfg ( reram2_t *ctx ) 
{   
    err_t error_flag = reram2_set_hold ( ctx, RERAM2_HOLD_DISABLE );

    error_flag |= reram2_set_write_protect ( ctx, RERAM2_WP_DISABLE );

    return error_flag;
}

err_t reram2_generic_write ( reram2_t *ctx, uint8_t op_code, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = op_code;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t reram2_generic_read ( reram2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t reram2_set_hold ( reram2_t *ctx, uint8_t en_hold )
{
    digital_out_write( &ctx->ho, en_hold );
    
    return RERAM2_OK;
}

err_t reram2_set_write_protect ( reram2_t *ctx, uint8_t en_wp )
{
    digital_out_write( &ctx->wp, en_wp );
    
    return RERAM2_OK;
}

err_t reram2_wake_up ( reram2_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    dev_wake_up_delay();
    spi_master_deselect_device( ctx->chip_select ); 
    dev_wake_up_delay();
    
    return RERAM2_OK;
}

err_t reram2_send_command ( reram2_t *ctx, uint8_t cmd )
{
    if ( ( cmd != RERAM2_CMD_WREN ) &&
         ( cmd != RERAM2_CMD_WRDI ) &&
         ( cmd != RERAM2_CMD_SLEEP ) )
    {
        return RERAM2_ERROR;
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t reram2_get_status ( reram2_t *ctx, reram2_status_t *status )
{
    uint8_t rx_data;
    
    err_t error_flag = reram2_generic_read( ctx, RERAM2_CMD_RDSR, &rx_data, 1 );
    
    status->write_protect      = ( rx_data >> 7 ) & 0x01;
    status->block_protect      = ( rx_data >> 2 ) & 0x03;
    status->write_enable_latch = ( rx_data >> 1 ) & 0x01;
    status->write_in_progress  =   rx_data        & 0x01;
    
    return error_flag;
}

err_t reram2_read_device_id ( reram2_t *ctx, reram2_dev_id_t *dev_id )
{
    uint8_t rx_buf[ 12 ];

    err_t error_flag = reram2_generic_read ( ctx, RERAM2_CMD_RDUID, rx_buf, 12 );
    
    dev_id->manufacturer_id   = rx_buf[ 0 ];
    dev_id->continuation_code = rx_buf[ 1 ];
    dev_id->product_id        = ( ( ( uint16_t ) rx_buf[ 2 ] ) << 8 ) | rx_buf[ 3 ];
    
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        dev_id->lot_id[ n_cnt ] = rx_buf[ 4 + n_cnt ];
    }
    
    dev_id->wafer_id = rx_buf[ 9 ];
    dev_id->chip_id  = ( ( ( uint16_t ) rx_buf[ 10 ] ) << 8 ) | rx_buf[ 11 ];

    return error_flag;
}

err_t reram2_check_device_id ( reram2_t *ctx )
{
    reram2_dev_id_t dev_id;

    reram2_read_device_id( ctx, &dev_id ); 
    
    if ( ( dev_id.manufacturer_id != RERAM2_MANUFACTURER_ID )     ||
         ( dev_id.continuation_code != RERAM2_CONTINUATION_CODE ) ||
         ( dev_id.product_id != RERAM2_PRODUCT_ID ) )
    {
        return RERAM2_ERROR;
    }

    return RERAM2_OK;
}

err_t reram2_write_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint16_t len )
{
    uint8_t data_input[ 259 ];

    if ( mem_addr > RERAM2_MEM_ADDR_END )
    {
        return RERAM2_ERROR;
    }
    
    if ( ( len < RERAM2_TRANSFER_BYTES_MIN ) || ( len > RERAM2_TRANSFER_BYTES_MAX ) )
    {
        return RERAM2_ERROR;
    }

    data_input[ 0 ] = ( uint8_t ) ( mem_addr >> 16 );
    data_input[ 1 ] = ( uint8_t ) ( mem_addr >> 8 );
    data_input[ 2 ] = ( uint8_t )   mem_addr;

    for ( uint16_t n_cnt = 3; n_cnt < len + 3; n_cnt++ )
    {
        data_input[ n_cnt ] = *data_in;
        data_in++;
    }

    return reram2_generic_write ( ctx, RERAM2_CMD_WRITE, data_input, len + 3 );
}

err_t reram2_read_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_buf[ 4 ];

    if ( mem_addr > RERAM2_MEM_ADDR_END )
    {
        return RERAM2_ERROR;
    }
    if ( ( len < RERAM2_TRANSFER_BYTES_MIN ) || ( len > RERAM2_TRANSFER_BYTES_MAX ) )
    {
        return RERAM2_ERROR;
    }

    tx_buf[ 0 ] = RERAM2_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( mem_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t )   mem_addr;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static void dev_wake_up_delay ( void ) 
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

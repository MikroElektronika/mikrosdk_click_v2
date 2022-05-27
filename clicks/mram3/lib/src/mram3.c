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
 * @file mram3.c
 * @brief MRAM 3 Click Driver.
 */

#include "mram3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void mram3_cfg_setup ( mram3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->io3  = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t mram3_init ( mram3_t *ctx, mram3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->io3, cfg->io3 );
    digital_out_init( &ctx->wp, cfg->wp );
    
    digital_out_low ( &ctx->io3 );
    digital_out_low ( &ctx->wp );

    return SPI_MASTER_SUCCESS;
}

err_t mram3_default_cfg ( mram3_t *ctx ) 
{
    err_t error_flag = MRAM3_OK;
    if ( MRAM3_ERROR == mram3_check_communication ( ctx ) )
    {
        return MRAM3_ERROR;
    }
    error_flag |= mram3_write_enable ( ctx );
    error_flag |= mram3_write_cmd ( ctx, MRAM3_CMD_SOFT_RESET_ENABLE );
    error_flag |= mram3_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= mram3_write_status ( ctx, MRAM3_STATUS_WPEN | 
                                            MRAM3_STATUS_BPSEL_NONE );
    uint8_t config[ 4 ];
    config[ 0 ] = MRAM3_CONFIG1_MAPLK_UNLOCK | MRAM3_CONFIG1_ASPLK_UNLOCK;
    config[ 1 ] = MRAM3_CONFIG2_MLATS_0_CYCLES;
    config[ 2 ] = MRAM3_CONFIG3_ODSEL_45OHM;
    config[ 3 ] = MRAM3_CONFIG4_WRENS_NORMAL;
    error_flag |= mram3_write_enable ( ctx );
    error_flag |= mram3_write_cmd_data ( ctx, MRAM3_CMD_WRITE_CONFIG_ALL, config, 4 );
    error_flag |= mram3_write_protect ( ctx );
    return error_flag;
}

err_t mram3_write_cmd ( mram3_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mram3_write_cmd_data ( mram3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || ( len > 8 ) )
    {
        return MRAM3_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mram3_read_cmd_data ( mram3_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || ( len > 8 ) )
    {
        return MRAM3_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mram3_write_cmd_address_data ( mram3_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len )
{
    if ( ( NULL == data_in ) || ( ( address + len ) > MRAM3_MAX_ADDRESS ) )
    {
        return MRAM3_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mram3_read_cmd_address_data ( mram3_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len )
{
    if ( ( NULL == data_out ) || ( ( address + len ) > MRAM3_MAX_ADDRESS ) )
    {
        return MRAM3_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mram3_memory_write ( mram3_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len )
{
    err_t error_flag = mram3_write_enable ( ctx );
    error_flag |= mram3_write_cmd_address_data ( ctx, MRAM3_CMD_WRITE_MEMORY_SDR, address, data_in, len );
    error_flag |= mram3_write_protect ( ctx );
    return error_flag;
}

err_t mram3_memory_read ( mram3_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    return mram3_read_cmd_address_data ( ctx, MRAM3_CMD_READ_MEMORY_SDR, address, data_out, len );
}

err_t mram3_aug_memory_write ( mram3_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = mram3_write_enable ( ctx );
    error_flag |= mram3_write_cmd_address_data ( ctx, MRAM3_CMD_WRITE_AUG_STORAGE_SDR, address, data_in, len );
    error_flag |= mram3_write_protect ( ctx );
    return error_flag;
}

err_t mram3_aug_memory_read ( mram3_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len )
{
    return mram3_read_cmd_address_data ( ctx, MRAM3_CMD_READ_AUG_STORAGE_SDR, address, data_out, len );
}

err_t mram3_check_communication ( mram3_t *ctx )
{
    uint8_t device_id[ 4 ];
    if ( MRAM3_OK == mram3_read_cmd_data( ctx, MRAM3_CMD_READ_DEVICE_ID, device_id, 4 ) )
    {
        if ( ( ( ( MRAM3_DEVICE_ID >> 24 ) & 0xFF ) == device_id[ 0 ] ) && 
             ( ( ( MRAM3_DEVICE_ID >> 16 ) & 0xFF ) == device_id[ 1 ] ) && 
             ( ( ( MRAM3_DEVICE_ID >> 8 ) & 0xFF ) == device_id[ 2 ] ) && 
             ( ( MRAM3_DEVICE_ID & 0xFF ) == device_id[ 3 ] ) )
        {
            return MRAM3_OK;
        }
    }
    return MRAM3_ERROR;
}

err_t mram3_write_protect ( mram3_t *ctx )
{
    digital_out_low ( &ctx->wp );
    err_t error_flag = mram3_write_cmd ( ctx, MRAM3_CMD_WRITE_DISABLE );
    uint8_t status;
    error_flag |= mram3_read_status ( ctx, &status );
    if ( ( MRAM3_OK == error_flag ) && ( MRAM3_STATUS_WREN != ( status & MRAM3_STATUS_WREN ) ) )
    {
        return MRAM3_OK;
    }
    return MRAM3_ERROR;
}

err_t mram3_write_enable ( mram3_t *ctx )
{
    digital_out_high ( &ctx->wp );
    err_t error_flag = mram3_write_cmd ( ctx, MRAM3_CMD_WRITE_ENABLE );
    uint8_t status;
    error_flag |= mram3_read_status ( ctx, &status );
    if ( ( MRAM3_OK == error_flag ) && ( MRAM3_STATUS_WREN == ( status & MRAM3_STATUS_WREN ) ) )
    {
        return MRAM3_OK;
    }
    return MRAM3_ERROR;
}

err_t mram3_soft_reset ( mram3_t *ctx )
{
    return mram3_write_cmd ( ctx, MRAM3_CMD_SOFT_RESET );
}

err_t mram3_write_status ( mram3_t *ctx, uint8_t status )
{
    err_t error_flag = mram3_write_enable ( ctx );
    error_flag |= mram3_write_cmd_data ( ctx, MRAM3_CMD_WRITE_STATUS, &status, 1 );
    error_flag |= mram3_write_protect ( ctx );
    return error_flag;
}

err_t mram3_read_status ( mram3_t *ctx, uint8_t *status )
{
    return mram3_read_cmd_data ( ctx, MRAM3_CMD_READ_STATUS, status, 1 );
}

// ------------------------------------------------------------------------- END

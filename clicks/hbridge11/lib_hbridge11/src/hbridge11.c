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
 * @file hbridge11.c
 * @brief H-Bridge 11 Click Driver.
 */

#include "hbridge11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void hbridge11_cfg_setup ( hbridge11_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cmd  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hbridge11_init ( hbridge11_t *ctx, hbridge11_cfg_t *cfg ) 
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

    digital_out_init( &ctx->cmd, cfg->cmd );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_low ( &ctx->cmd );
    digital_out_low ( &ctx->en );

    digital_in_init( &ctx->flt, cfg->flt );
    return SPI_MASTER_SUCCESS;
}

err_t hbridge11_default_cfg ( hbridge11_t *ctx ) 
{
    err_t error_flag = HBRIDGE11_OK;
    hbridge11_disable_device ( ctx );
    Delay_100ms ( );
    hbridge11_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_STATUS, HBRIDGE11_STATUS_ONCH_ALL_OFF | 
                                                                              HBRIDGE11_STATUS_M_COMF | 
                                                                              HBRIDGE11_STATUS_FREQM_100KHZ | 
                                                                              HBRIDGE11_STATUS_CM76_HBRIDGE | 
                                                                              HBRIDGE11_STATUS_CM54_HBRIDGE | 
                                                                              HBRIDGE11_STATUS_CM32_HBRIDGE | 
                                                                              HBRIDGE11_STATUS_CM10_HBRIDGE | 
                                                                              HBRIDGE11_STATUS_ACTIVE );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH0, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH1, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH2, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH3, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH4, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH5, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH6, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    error_flag |= hbridge11_write_32bit_register ( ctx, HBRIDGE11_REG_CFG_CH7, HBRIDGE11_CFG_CH_HOLD_DUTY_MAX | 
                                                                               HBRIDGE11_CFG_CH_VDRNCDR_VDR );
    Delay_100ms ( );
    // Read status to clear faults
    uint32_t status = 0;
    error_flag |= hbridge11_read_32bit_register ( ctx, HBRIDGE11_REG_STATUS, &status );
    return error_flag;
}

err_t hbridge11_write_8bit_register ( hbridge11_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t cmd = HBRIDGE11_CMD_WRITE | ( ( reg << 1 ) & HBRIDGE11_CMD_ADDRESS_MASK ) | HBRIDGE11_CMD_8BIT_REG;
    digital_out_high ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hbridge11_read_8bit_register ( hbridge11_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t cmd = ( ( reg << 1 ) & HBRIDGE11_CMD_ADDRESS_MASK ) | HBRIDGE11_CMD_8BIT_REG;
    digital_out_high ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hbridge11_write_32bit_register ( hbridge11_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t cmd = HBRIDGE11_CMD_WRITE | ( ( reg << 1 ) & HBRIDGE11_CMD_ADDRESS_MASK );
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    digital_out_high ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hbridge11_read_32bit_register ( hbridge11_t *ctx, uint8_t reg, uint32_t *data_out )
{
    uint8_t cmd = ( ( reg << 1 ) & HBRIDGE11_CMD_ADDRESS_MASK );
    uint8_t data_buf[ 4 ] = { 0 };
    digital_out_high ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low ( &ctx->cmd );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    return error_flag;
}

void hbridge11_enable_device ( hbridge11_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void hbridge11_disable_device ( hbridge11_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t hbridge11_get_fault_pin ( hbridge11_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

err_t hbridge11_read_flags ( hbridge11_t *ctx, uint8_t *fault_flags )
{
    uint32_t status = 0;
    err_t error_flag = hbridge11_read_32bit_register ( ctx, HBRIDGE11_REG_STATUS, &status );
    *fault_flags = ( uint8_t ) ( status & 0xFF );
    return error_flag;
}

err_t hbridge11_set_motor_state ( hbridge11_t *ctx, uint8_t motor, uint8_t state )
{
    if ( ( motor > HBRIDGE11_MOTOR_SEL_3 ) || ( state > HBRIDGE11_MOTOR_STATE_BRAKE ) )
    {
        return HBRIDGE11_ERROR;
    }
    uint8_t onch = 0;
    err_t error_flag = hbridge11_read_8bit_register ( ctx, HBRIDGE11_REG_STATUS, &onch );
    onch &= ~( 3 << ( 2 * motor ) );
    onch |= ( state << ( 2 * motor ) );
    error_flag |= hbridge11_write_8bit_register ( ctx, HBRIDGE11_REG_STATUS, onch );
    return error_flag;
}

// ------------------------------------------------------------------------- END

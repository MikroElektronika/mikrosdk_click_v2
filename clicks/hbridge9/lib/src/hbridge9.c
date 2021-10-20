/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file hbridge9.c
 * @brief H-Bridge 9 Click Driver.
 */

#include "hbridge9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief H-Bridge 9 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t hbridge9_calculate_parity_bit ( uint16_t data_in );

void hbridge9_cfg_setup ( hbridge9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en_out = HAL_PIN_NC;
    cfg->dout = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hbridge9_init ( hbridge9_t *ctx, hbridge9_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en_out, cfg->en_out );

    digital_in_init( &ctx->dout, cfg->dout );

    return SPI_MASTER_SUCCESS;
}

err_t hbridge9_default_cfg ( hbridge9_t *ctx ) 
{
    hbridge9_send_actuation_pulse ( ctx );

    if ( HBRIDGE9_ERROR == hbridge9_check_communication ( ctx ) )
    {
        return HBRIDGE9_ERROR;
    }

    err_t error_flag = hbridge9_set_default ( ctx );
    Delay_100ms( );
    error_flag |= hbridge9_clear_all_status ( ctx );
    Delay_100ms( );

    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR0, HBRIDGE9_CR0_PWM_FREQ_10p240 | 
                                                                   HBRIDGE9_CR0_OUT2_POL_HIGH | 
                                                                   HBRIDGE9_CR0_OUT1_POL_LOW );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR1, HBRIDGE9_CR1_EMCY_NORMAL_MODE );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR2, HBRIDGE9_CR2_DBN_2 | 
                                                                   HBRIDGE9_CR2_DBN_1 | 
                                                                   HBRIDGE9_CR2_ON_TIME_DUR_1000MS | 
                                                                   HBRIDGE9_CR2_BRAKING_DUR_200MS );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR3, HBRIDGE9_CR3_GFI );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR4, 0 );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR5, 0 );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR6, HBRIDGE9_CR6_EXT1_VDS_1p5V | 
                                                                   HBRIDGE9_CR6_EXT2_VDS_1p5V );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR7, 0 );
    error_flag |= hbridge9_write_register ( ctx, HBRIDGE9_REG_CR8, HBRIDGE9_CR8_KI_GAIN_1_OVER_4 | 
                                                                   HBRIDGE9_CR8_KP_GAIN_64 );

    return error_flag;
}

err_t hbridge9_spi_transfer ( hbridge9_t *ctx, uint8_t *data_in, uint8_t tx_len, uint8_t *data_out, uint8_t rx_len ) 
{
    err_t error_flag = HBRIDGE9_OK;

    spi_master_select_device( ctx->chip_select );

    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        if ( cnt < rx_len )
        {
            error_flag |= spi_master_set_default_write_data( &ctx->spi, data_in[ cnt ] );
            error_flag |= spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
        }
        else
        {
            error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
            error_flag |= spi_master_write( &ctx->spi, &data_in[ cnt ], tx_len - rx_len );
            spi_master_deselect_device( ctx->chip_select );
            return error_flag;
        }
    }

    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );

    if ( tx_len < rx_len )
    {
        error_flag |= spi_master_read( &ctx->spi, &data_out[ tx_len ], rx_len - tx_len );
    }

    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t hbridge9_write_register ( hbridge9_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t tx_buf[ 3 ] = { 0 };
    uint8_t rx_buf[ 3 ] = { 0 };

    tx_buf[ 0 ] = ( reg & ~HBRIDGE9_OPCODE_BITS_MASK ) | HBRIDGE9_OPCODE_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );

    if ( HBRIDGE9_REG_CR0 == reg )
    {
        tx_buf[ 2 ] |= !hbridge9_calculate_parity_bit ( data_in );
    }
    else
    {
        tx_buf[ 2 ] |= hbridge9_calculate_parity_bit ( data_in );
    }

    err_t error_flag = hbridge9_spi_transfer ( ctx, tx_buf, 3, rx_buf, 3 );
    
    if ( !hbridge9_calculate_parity_bit ( ( ( uint16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 2 ] ) )
    {
        return HBRIDGE9_ERROR;
    }

    ctx->global_status = rx_buf[ 0 ];

    return error_flag;
}

err_t hbridge9_read_register ( hbridge9_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t tx_data = 0;
    uint8_t rx_buf[ 3 ] = { 0 };

    tx_data = ( reg & ~HBRIDGE9_OPCODE_BITS_MASK ) | HBRIDGE9_OPCODE_READ;

    err_t error_flag = hbridge9_spi_transfer ( ctx, &tx_data, 1, rx_buf, 3 );

    if ( !hbridge9_calculate_parity_bit ( ( ( uint16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 2 ] ) )
    {
        return HBRIDGE9_ERROR;
    }

    ctx->global_status = rx_buf[ 0 ];

    *data_out = rx_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 2 ];

    return error_flag;
}

err_t hbridge9_modify_register_bits ( hbridge9_t *ctx, uint8_t reg, uint16_t clr_mask, uint16_t set_mask )
{
    uint16_t rx_data = 0;
    uint16_t tx_data = 0;

    err_t error_flag = hbridge9_read_register( ctx, reg, &rx_data );

    tx_data = ( rx_data & ~clr_mask ) | set_mask;

    if ( rx_data != tx_data )
    {
        error_flag |= hbridge9_write_register( ctx, reg, tx_data );
    }

    return error_flag;
}

err_t hbridge9_read_register_and_clear ( hbridge9_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 3 ] = { 0 };
    uint8_t tx_data = 0;

    tx_data = ( reg & ~HBRIDGE9_OPCODE_BITS_MASK ) | HBRIDGE9_OPCODE_READ_CLEAR;

    err_t error_flag = hbridge9_spi_transfer ( ctx, &tx_data, 1, rx_buf, 3 );

    if ( !hbridge9_calculate_parity_bit ( ( ( uint16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 2 ] ) )
    {
        return HBRIDGE9_ERROR;
    }

    ctx->global_status = rx_buf[ 0 ];

    *data_out = rx_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 2 ];

    return error_flag;
}

err_t hbridge9_read_info_register ( hbridge9_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    uint8_t rx_buf[ 3 ] = { 0 };
    uint8_t tx_data = 0;

    tx_data = ( reg & ~HBRIDGE9_OPCODE_BITS_MASK ) | HBRIDGE9_OPCODE_READ_DEV_INFO;
    reg |= HBRIDGE9_OPCODE_READ_CLEAR;
    err_t error_flag = hbridge9_spi_transfer ( ctx, &tx_data, 1, rx_buf, 3 );
    ctx->global_status = rx_buf[ 0 ];
    *data_out = rx_buf[ 1 ];
    return error_flag;
}

err_t hbridge9_set_default ( hbridge9_t *ctx ) 
{
    uint8_t tx_data = HBRIDGE9_ADV_OPCODE_SET_DEFAULT;
    return hbridge9_spi_transfer ( ctx, &tx_data, 1, &ctx->global_status, 1 );
}

err_t hbridge9_clear_all_status ( hbridge9_t *ctx ) 
{
    uint8_t tx_data = HBRIDGE9_ADV_OPCODE_CLEAR_STATUS;
    return hbridge9_spi_transfer ( ctx, &tx_data, 1, &ctx->global_status, 1 );
}

err_t hbridge9_check_communication ( hbridge9_t *ctx ) 
{
    uint8_t reg_data = 0;

    if ( HBRIDGE9_OK == hbridge9_read_info_register ( ctx, HBRIDGE9_REG_INFO_SPI_CPHA_TEST, &reg_data ) )
    {
        if ( HBRIDGE9_SPI_CPHA_TEST == reg_data )
        {
            return HBRIDGE9_OK;
        }
    }
    return HBRIDGE9_ERROR;
}

void hbridge9_set_en_out_pin ( hbridge9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en_out, state );
}

void hbridge9_send_actuation_pulse ( hbridge9_t *ctx )
{
    hbridge9_set_en_out_pin ( ctx, 0 );
    Delay_500us( );
    hbridge9_set_en_out_pin ( ctx, 1 );
    Delay_500us( );
}

uint8_t hbridge9_get_dout_pin ( hbridge9_t *ctx )
{
    return digital_in_read ( &ctx->dout );
}

static uint8_t hbridge9_calculate_parity_bit ( uint16_t data_in )
{
    uint8_t parity = 0;

    while ( data_in )
    {
        parity += ( data_in & HBRIDGE9_ODD_PARITY );
        data_in >>= 1;
    }
    return parity & HBRIDGE9_ODD_PARITY;
}

// ------------------------------------------------------------------------- END

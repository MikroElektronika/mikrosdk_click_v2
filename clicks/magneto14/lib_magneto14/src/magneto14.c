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
 * @file magneto14.c
 * @brief Magneto 14 Click Driver.
 */

#include "magneto14.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                             0x00

/**
 * @brief Magneto 14 angle calculation values.
 * @details Definition of angle calculation values.
 */
#define MAGNETO14_ANGLE_FULL_SCALE       65535.0
#define MAGNETO14_ANGLE_MAX_DEGREES        360.0

/**
 * @brief Magneto 14 communication delay function.
 * @details Idle time between two subsequent angle transmissions,
 *  before and after a register readout and before and after a register write.
 * @return Nothing.
 * @note None.
 */
static void magneto14_communication_delay ( void );

/**
 * @brief Magneto 14 store to the NVM delay function.
 * @details Time required to store a single register to the NVM.
 * @return Nothing.
 * @note None.
 */
static void magneto14_store_nvm_delay ( void );

void magneto14_cfg_setup ( magneto14_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->mgh = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t magneto14_init ( magneto14_t *ctx, magneto14_cfg_t *cfg ) 
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

    digital_out_init( &ctx->pwm, cfg->pwm );

    digital_in_init( &ctx->mgh, cfg->mgh );

    return SPI_MASTER_SUCCESS;
}

err_t magneto14_default_cfg ( magneto14_t *ctx ) 
{
    magneto14_communication_delay( );
    return magneto14_set_mag_field_thd( ctx, MAGNETO14_MG_LT_LVL_0, MAGNETO14_MG_HT_LVL_3 );
}

err_t magneto14_write_reg ( magneto14_t *ctx, uint8_t cmd, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( cmd & MAGNETO14_CMD_BIT_MASK ) << 5;
    data_buf[ 0 ] |= reg & MAGNETO14_REG_BIT_MASK;
    data_buf[ 1 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( cmd == MAGNETO14_CMD_STORE_SINGLE_NVM )
    {
        magneto14_store_nvm_delay( );
    }
    else
    {
        magneto14_communication_delay( );
    }
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( data_in != data_buf[ 0 ] )
    {
        error_flag = MAGNETO14_ERROR;
    }
    return error_flag;
}

err_t magneto14_read_reg ( magneto14_t *ctx, uint8_t cmd, uint8_t reg, uint8_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( cmd & MAGNETO14_CMD_BIT_MASK ) << 5;
    data_buf[ 0 ] |= reg & MAGNETO14_REG_BIT_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( cmd == MAGNETO14_CMD_RESTORE_ALL_NVM )
    {
        magneto14_communication_delay( );
    }
    magneto14_communication_delay( );    
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = data_buf[ 0 ];
    return error_flag;
}

err_t magneto14_get_angle_raw_data ( magneto14_t *ctx, uint16_t *raw_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *raw_data = data_buf[ 0 ];
    *raw_data <<= 8;
    *raw_data |= data_buf[ 1 ];
    return error_flag;
}

err_t magneto14_get_angle ( magneto14_t *ctx, float *angle ) 
{
    uint16_t raw_data = DUMMY;
    err_t error_flag = magneto14_get_angle_raw_data( ctx, &raw_data );
    *angle = ( float ) raw_data;
    *angle /= MAGNETO14_ANGLE_FULL_SCALE;
    *angle *= MAGNETO14_ANGLE_MAX_DEGREES;
    return error_flag;
}

err_t magneto14_set_mag_field_thd ( magneto14_t *ctx, uint8_t mglt, uint8_t mght ) 
{
    uint8_t data_buf = DUMMY;
    err_t error_flag = magneto14_read_reg( ctx, MAGNETO14_CMD_READ_REGISTER, MAGNETO14_REG_MG_LT_HT_MG, &data_buf );
    magneto14_communication_delay( );
    data_buf &= MAGNETO14_MG_BIT_MASK;
    data_buf |= mglt & MAGNETO14_MG_LT_LVL_7;
    data_buf |= mght & MAGNETO14_MG_HT_LVL_7;
    error_flag |= magneto14_write_reg( ctx, MAGNETO14_CMD_WRITE_REGISTER, MAGNETO14_REG_MG_LT_HT_MG, data_buf );
    return error_flag;
}

err_t magneto14_get_field_strength ( magneto14_t *ctx, uint8_t *field_strength ) 
{
    uint8_t data_buf = DUMMY;
    err_t error_flag = magneto14_read_reg( ctx, MAGNETO14_CMD_READ_REGISTER, MAGNETO14_REG_M_GH_GL, &data_buf );
    *field_strength = ( data_buf >> 6 ) & MAGNETO14_FLD_ST_BIT_MASK;
    return error_flag;
}

void magneto14_set_pwm_pin ( magneto14_t *ctx, uint8_t pwm_state ) 
{
    digital_out_write( &ctx->pwm, pwm_state );
}

uint8_t magneto14_get_mgh ( magneto14_t *ctx ) 
{
    return digital_in_read( &ctx->mgh );
}

static void magneto14_communication_delay ( void ) 
{
    Delay_10ms( );
    Delay_10ms( );
}

static void magneto14_store_nvm_delay ( void ) 
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_5ms( );
}

// ------------------------------------------------------------------------- END

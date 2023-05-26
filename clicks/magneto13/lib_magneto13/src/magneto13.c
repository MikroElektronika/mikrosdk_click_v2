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
 * @file magneto13.c
 * @brief Magneto 13 Click Driver.
 */

#include "magneto13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                             0x00

/**
 * @brief Magneto 13 angle calculation values.
 * @details Definition of angle calculation values.
 */
#define MAGNETO13_ANGLE_FULL_SCALE       65535.0
#define MAGNETO13_ANGLE_MAX_DEGREES        360.0

/**
 * @brief Magneto 13 communication delay function.
 * @details Idle time between two subsequent angle transmissions,
 *  before and after a register readout and before and after a register write.
 * @return Nothing.
 * @note None.
 */
static void magneto13_communication_delay ( void );

/**
 * @brief Magneto 13 store to the NVM delay function.
 * @details Time required to store a single register to the NVM.
 * @return Nothing.
 * @note None.
 */
static void magneto13_store_nvm_delay ( void );

/**
 * @brief Magneto 13 store all to the NVM delay function.
 * @details Time required to store all registers to the NVM.
 * @return Nothing.
 * @note None.
 */
static void magneto13_store_all_nvm_delay ( void );

void magneto13_cfg_setup ( magneto13_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->err   = HAL_PIN_NC;
    cfg->nvm = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t magneto13_init ( magneto13_t *ctx, magneto13_cfg_t *cfg ) 
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

    digital_in_init( &ctx->err, cfg->err );
    digital_in_init( &ctx->nvm, cfg->nvm );
    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t magneto13_default_cfg ( magneto13_t *ctx ) 
{
    err_t error_flag = magneto13_enable_fld_thd_det( ctx );
    error_flag |= magneto13_set_mag_field_thd( ctx, MAGNETO13_MG_LT_LVL_0, MAGNETO13_MG_HT_LVL_1 );
    return error_flag;
}

err_t magneto13_write_reg ( magneto13_t *ctx, uint8_t cmd, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( cmd & MAGNETO13_CMD_BIT_MASK ) << 5;
    data_buf[ 0 ] |= reg & MAGNETO13_REG_BIT_MASK;
    data_buf[ 1 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( MAGNETO13_CMD_STORE_ALL_NVM == cmd )
    {
        magneto13_store_all_nvm_delay( );
    } 
    else if ( MAGNETO13_CMD_STORE_SINGLE_NVM == cmd )
    {
        magneto13_store_nvm_delay( );
    }
    else
    {
        magneto13_communication_delay( );
    }
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( data_in != data_buf[ 1 ] )
    {
        error_flag = MAGNETO13_ERROR;
    }
    return error_flag;
}

err_t magneto13_read_reg ( magneto13_t *ctx, uint8_t cmd, uint8_t reg, uint8_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( cmd & MAGNETO13_CMD_BIT_MASK ) << 5;
    data_buf[ 0 ] |= reg & MAGNETO13_REG_BIT_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( MAGNETO13_CMD_RESTORE_ALL_NVM  == cmd )
    {
        magneto13_communication_delay( );
    }
    magneto13_communication_delay( );    
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    *data_out = data_buf[ 1 ];
    return error_flag;
}

err_t magneto13_get_angle_raw_data ( magneto13_t *ctx, uint16_t *raw_data ) 
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

err_t magneto13_get_angle ( magneto13_t *ctx, float *angle ) 
{
    uint16_t raw_data = DUMMY;
    err_t error_flag = magneto13_get_angle_raw_data( ctx, &raw_data );
    *angle = ( float ) raw_data;
    *angle /= MAGNETO13_ANGLE_FULL_SCALE;
    *angle *= MAGNETO13_ANGLE_MAX_DEGREES;
    return error_flag;
}

err_t magneto13_set_mag_field_thd ( magneto13_t *ctx, uint8_t mglt, uint8_t mght ) 
{
    uint8_t data_buf = DUMMY;
    err_t error_flag = magneto13_read_reg( ctx, MAGNETO13_CMD_READ_REGISTER, MAGNETO13_REG_MG_LT_HT_MG, &data_buf );
    magneto13_communication_delay( );
    data_buf &= ~MAGNETO13_MG_BIT_MASK;
    data_buf |= mglt & MAGNETO13_MG_LT_LVL_3;
    data_buf |= mght & MAGNETO13_MG_HT_LVL_3;
    error_flag |= magneto13_write_reg( ctx, MAGNETO13_CMD_WRITE_REGISTER, MAGNETO13_REG_MG_LT_HT_MG, data_buf );
    return error_flag;
}

err_t magneto13_enable_fld_thd_det ( magneto13_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t error_flag = magneto13_read_reg( ctx, MAGNETO13_CMD_READ_REGISTER, MAGNETO13_REG_MG_LT_HT_MG, &data_buf );
    magneto13_communication_delay( );
    data_buf |= MAGNETO13_MG_FLD_THD_EN;
    error_flag |= magneto13_write_reg( ctx, MAGNETO13_CMD_WRITE_REGISTER, MAGNETO13_REG_MG_LT_HT_MG, data_buf );
    return error_flag;
}

err_t magneto13_get_field_strength ( magneto13_t *ctx, uint8_t *field_strength ) 
{
    uint8_t data_buf = DUMMY;
    err_t error_flag = magneto13_read_reg( ctx, MAGNETO13_CMD_READ_REGISTER, MAGNETO13_REG_M_GH_GL, &data_buf );
    *field_strength = ( data_buf >> 6 ) & MAGNETO13_FLD_ST_BIT_MASK;
    return error_flag;
}

uint8_t magneto13_get_error_flag ( magneto13_t *ctx ) 
{
    return digital_in_read( &ctx->err );
}

uint8_t magneto13_get_nvm_access_state ( magneto13_t *ctx ) 
{
    return digital_in_read( &ctx->nvm );
}

uint8_t magneto13_get_interrupt ( magneto13_t *ctx ) 
{
    return digital_in_read( &ctx->irq );
}

static void magneto13_communication_delay ( void ) 
{
    Delay_80us( );
    Delay_80us( );
}

static void magneto13_store_nvm_delay ( void ) 
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_5ms( );
}

static void magneto13_store_all_nvm_delay ( void ) 
{
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_5ms( );
}

// ------------------------------------------------------------------------- END

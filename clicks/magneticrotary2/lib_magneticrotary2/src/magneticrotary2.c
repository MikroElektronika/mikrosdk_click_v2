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
 * @file magneticrotary2.c
 * @brief Magnetic Rotary 2 Click Driver.
 */

#include "magneticrotary2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0xFF

/**
 * @brief Magnetic Rotary 2 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t magneticrotary2_calculate_parity_bit ( uint32_t data_in );

void magneticrotary2_cfg_setup ( magneticrotary2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->msel        = MAGNETICROTARY2_MSEL_1;
    if ( MAGNETICROTARY2_MSEL_0 == cfg->msel )
    {
        cfg->spi_mode = SPI_MASTER_MODE_3;
    }
    else
    {
        cfg->spi_mode = SPI_MASTER_MODE_1;
    }
}

void magneticrotary2_msel_pin_selection ( magneticrotary2_cfg_t *cfg, magneticrotary2_msel_t msel ) 
{
    cfg->msel = msel;
    if ( MAGNETICROTARY2_MSEL_0 == msel )
    {
        cfg->spi_mode = SPI_MASTER_MODE_3;
    }
    else
    {
        cfg->spi_mode = SPI_MASTER_MODE_1;
    }
}

err_t magneticrotary2_init ( magneticrotary2_t *ctx, magneticrotary2_cfg_t *cfg ) 
{
    ctx->msel = cfg->msel;
    
    digital_out_init ( &ctx->ssi_sel, cfg->mosi );
    
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
    
    return SPI_MASTER_SUCCESS;
}

err_t magneticrotary2_default_cfg ( magneticrotary2_t *ctx ) 
{
    if ( MAGNETICROTARY2_MSEL_1 == ctx->msel ) 
    {
        SET_SPI_DATA_SAMPLE_EDGE;
    }
    err_t error_flag = MAGNETICROTARY2_OK;
    error_flag |= magneticrotary2_unlock_eeprom ( ctx );
    Delay_100ms( );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_0, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_1, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_2, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_3, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_4, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_5, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_RES_6, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_CONFIG_0_LSB, 
                                                        MAGNETICROTARY2_CC0_MSB_HW_ST_ZERO_EN | 
                                                        MAGNETICROTARY2_CC0_MSB_HW_ACC_CALIB_EN );
    uint8_t tx_data = MAGNETICROTARY2_CC0_LSB_HYST_0_08 | MAGNETICROTARY2_CC0_LSB_ABS_RES_18BIT;
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_CONFIG_0_MSB, tx_data );
    ctx->abs_res = 18 - ( tx_data & MAGNETICROTARY2_CC0_LSB_ABS_RES_MASK );
    uint16_t incremental_res = 1024; // Valid values up to 10000
    incremental_res |= 0x4000; // Reserved bit
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_CONFIG_1_MSB, 
                                                   ( uint8_t ) ( ( incremental_res >> 8 ) & 0xFF ) );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_CONFIG_1_LSB, 
                                                   ( uint8_t ) ( incremental_res & 0xFF ) );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_CUST_CONFIG_2, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_ZERO_RESET_2, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_ZERO_RESET_1, 0 );
    error_flag |= magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_ZERO_RESET_0, 0 );
    Delay_100ms( );
    error_flag |= magneticrotary2_program_eeprom ( ctx );
    Delay_100ms( );
    error_flag |= magneticrotary2_lock_eeprom ( ctx );
    Delay_100ms( );
    return error_flag;
}

err_t magneticrotary2_write_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    err_t error_flag = MAGNETICROTARY2_OK;
    uint8_t tx_buf[ 2 ] = { 0 };
    uint16_t timeout = 1000;
    do
    {
        if ( MAGNETICROTARY2_MSEL_0 == ctx->msel ) 
        {
            tx_buf[ 0 ] = reg | MAGNETICROTARY2_MSEL0_WRITE_BIT;
            tx_buf[ 1 ] = data_in;
            spi_master_select_device( ctx->chip_select );
            error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
            spi_master_deselect_device( ctx->chip_select );
        }
        else
        {
            tx_buf[ 0 ] = ( magneticrotary2_calculate_parity_bit ( reg ) << 7 );
            tx_buf[ 1 ] = reg;
            spi_master_select_device( ctx->chip_select );
            error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
            spi_master_deselect_device( ctx->chip_select );
            
            tx_buf[ 0 ] = ( magneticrotary2_calculate_parity_bit ( data_in ) << 7 );
            tx_buf[ 1 ] = data_in;
            spi_master_select_device( ctx->chip_select );
            error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
            spi_master_deselect_device( ctx->chip_select );
        }
        error_flag |= magneticrotary2_read_register ( ctx, reg, tx_buf );
        timeout--;
        Delay_1ms( );
    } while ( ( tx_buf[ 0 ] != data_in ) && timeout );
    
    if ( timeout )
    {
        return error_flag;
    }
    else
    {
        return MAGNETICROTARY2_ERROR;
    }
}

err_t magneticrotary2_read_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    err_t error_flag = MAGNETICROTARY2_OK;
    uint8_t buffer[ 3 ] = { 0 };
    if ( MAGNETICROTARY2_MSEL_0 == ctx->msel ) 
    {
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        uint32_t parity_check = 0;
        buffer[ 0 ] = MAGNETICROTARY2_MSEL1_READ_BIT | ( magneticrotary2_calculate_parity_bit ( reg ) << 7 );
        buffer[ 1 ] = reg;
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write ( &ctx->spi, buffer, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        spi_master_select_device( ctx->chip_select );
        if ( MAGNETICROTARY2_REG_POSITION == reg )
        {
            error_flag |= spi_master_read ( &ctx->spi, buffer, 3 );
            parity_check = buffer[ 0 ];
            parity_check <<= 8;
            parity_check |= buffer[ 1 ];
            parity_check <<= 8;
            parity_check |= buffer[ 2 ];
            if ( magneticrotary2_calculate_parity_bit ( parity_check ) )
            {
                error_flag = MAGNETICROTARY2_ERROR;
            }
            else
            {
                parity_check <<= 2;
                data_out[ 0 ] = ( uint8_t ) ( ( parity_check >> 16 ) & 0xFF );
                data_out[ 1 ] = ( uint8_t ) ( ( parity_check >> 8 ) & 0xFF );
                data_out[ 2 ] = ( uint8_t ) ( parity_check & 0xFF );
            }
        }
        else
        {
            error_flag |= spi_master_read ( &ctx->spi, buffer, 2 );
            parity_check = buffer[ 0 ];
            parity_check <<= 8;
            parity_check |= buffer[ 1 ];
            if ( magneticrotary2_calculate_parity_bit ( parity_check ) )
            {
                error_flag = MAGNETICROTARY2_ERROR;
            }
            else
            {
                *data_out = buffer[ 1 ];
            }
        }
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t magneticrotary2_unlock_eeprom ( magneticrotary2_t *ctx ) 
{
    return magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_UNLOCK, MAGNETICROTARY2_UNLOCK_VALUE );
}

err_t magneticrotary2_lock_eeprom ( magneticrotary2_t *ctx ) 
{
    return magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_UNLOCK, MAGNETICROTARY2_LOCK_VALUE );
}

err_t magneticrotary2_program_eeprom ( magneticrotary2_t *ctx ) 
{
    return magneticrotary2_write_register ( ctx, MAGNETICROTARY2_REG_PROGRAM, MAGNETICROTARY2_PROGRAM_VALUE );
}

err_t magneticrotary2_get_raw_data ( magneticrotary2_t *ctx, uint32_t *data_out )
{
    err_t error_flag = MAGNETICROTARY2_OK;
    uint8_t rx_buf[ 3 ] = { 0 };
    if ( MAGNETICROTARY2_MSEL_0 == ctx->msel ) 
    {
        error_flag |= spi_master_set_default_write_data( &ctx->spi, 0x00 );
    #ifndef __KINETIS__
        error_flag |= spi_master_set_mode( &ctx->spi, SPI_MASTER_MODE_2 );
        SET_SPI_DATA_SAMPLE_EDGE;
    #endif
        spi_master_deselect_device( ctx->chip_select );
        digital_out_low ( &ctx->ssi_sel );
        error_flag |= spi_master_read( &ctx->spi, rx_buf, 3 );
        spi_master_select_device( ctx->chip_select );
    #ifndef __KINETIS__
        error_flag |= spi_master_set_mode( &ctx->spi, SPI_MASTER_MODE_3 );
        SET_SPI_DATA_SAMPLE_MIDDLE;
    #endif
        error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
        digital_out_high ( &ctx->ssi_sel );
        *data_out = rx_buf[ 0 ];
        *data_out <<= 8;
        *data_out |= rx_buf[ 1 ];
        *data_out <<= 8;
        *data_out |= rx_buf[ 2 ];
        *data_out >>= ( 24 - ( ctx->abs_res + 4 ) );
        if ( *data_out )
        {
            if ( !magneticrotary2_calculate_parity_bit ( *data_out ) )
            {
                *data_out >>= 4;
                return MAGNETICROTARY2_OK;
            }
        }
    }
    else
    {
        error_flag |= magneticrotary2_read_register( ctx, MAGNETICROTARY2_REG_POSITION, rx_buf );
        if ( MAGNETICROTARY2_OK == error_flag )
        {
            *data_out = rx_buf[ 0 ];
            *data_out <<= 8;
            *data_out |= rx_buf[ 1 ];
            *data_out <<= 8;
            *data_out |= rx_buf[ 2 ];
            *data_out >>= ( 24 - ctx->abs_res );
            if ( *data_out )
            {
                return MAGNETICROTARY2_OK;
            }
        }
    }
    return MAGNETICROTARY2_ERROR;
}

err_t magneticrotary2_get_angle ( magneticrotary2_t *ctx, float *angle )
{
    err_t error_flag = MAGNETICROTARY2_OK;
    uint32_t raw_data = 0;
    error_flag |= magneticrotary2_get_raw_data( ctx, &raw_data );
    if ( MAGNETICROTARY2_OK == error_flag )
    {
        *angle = raw_data * ( float ) 360 / ( 1ul << ctx->abs_res );
        return MAGNETICROTARY2_OK;
    }
    return MAGNETICROTARY2_ERROR;
}

static uint8_t magneticrotary2_calculate_parity_bit ( uint32_t data_in )
{
    uint8_t parity = 0;
    while ( data_in )
    {
        parity += ( data_in & MAGNETICROTARY2_ODD_PARITY );
        data_in >>= 1;
    }
    return parity & MAGNETICROTARY2_ODD_PARITY;
}

// ------------------------------------------------------------------------- END

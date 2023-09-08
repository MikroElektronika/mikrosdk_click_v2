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
 * @file adc22.c
 * @brief ADC 22 Click Driver.
 */

#include "adc22.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc22_cfg_setup ( adc22_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rvs  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc22_init ( adc22_t *ctx, adc22_cfg_t *cfg ) 
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

    digital_in_init( &ctx->rvs, cfg->rvs );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t adc22_default_cfg ( adc22_t *ctx ) 
{
    adc22_hw_reset( ctx );
    Delay_100ms( );
    
    err_t err_flag = adc22_set_device_addr( ctx, 1 );
    Delay_1ms( );
    
    err_flag |= adc22_set_sdo_mode( ctx, ADC22_SDO_MODE_SAME_SDI );
    Delay_1ms( );
    
    err_flag |= adc22_en_out_data_parity( ctx );
    Delay_1ms( );
    
    err_flag |= adc22_set_range( ctx, ADC22_RANGE_12V28 );
    Delay_1ms( );
    
    float voltage = ( float ) DUMMY;
    adc22_get_voltage ( ctx, &voltage );
    return err_flag;
}

void adc22_hw_reset ( adc22_t *ctx ) 
{
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
}

uint8_t adc22_get_interrupt ( adc22_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t adc22_get_rvs ( adc22_t *ctx ) 
{
    return digital_in_read( &ctx->rvs );
}

err_t adc22_write_reg ( adc22_t *ctx, uint8_t w_cmd, uint8_t reg, uint8_t data_in ) 
{
    err_t err_flag = ADC22_OK;
    if ( ( ( ADC22_CMD_WRITE == w_cmd )    || 
           ( ADC22_CMD_WRITE_MS == w_cmd ) || 
           ( ADC22_CMD_WRITE_LS == w_cmd ) ) && ( ADC22_REG_ALARM_L_TH_MSB >= reg ) )
    {
        uint8_t data_buf[ 4 ] = { w_cmd, reg, data_in, data_in };
        spi_master_select_device( ctx->chip_select );
        while ( adc22_get_rvs( ctx ) == ADC22_PIN_STATE_HIGH );
        err_flag = spi_master_write( &ctx->spi, data_buf, 4 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        err_flag = ADC22_ERROR;
    }
    return err_flag;
}

err_t adc22_read_reg ( adc22_t *ctx, uint8_t r_cmd, uint8_t reg, uint8_t *data_out ) 
{
    err_t err_flag = ADC22_OK;
    if ( ( ( ADC22_CMD_READ_HWORD == r_cmd ) || ( ADC22_CMD_READ == r_cmd ) ) && 
         ( ADC22_REG_ALARM_L_TH_MSB >= reg ) )
    {
        uint8_t tx_data[ 2 ] = { r_cmd, reg };
        uint8_t rx_data[ 4 ] = { DUMMY };
        spi_master_select_device( ctx->chip_select );
        err_flag |= spi_master_write( &ctx->spi, tx_data, 2 );
        err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
        err_flag |= spi_master_read( &ctx->spi, rx_data, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        spi_master_select_device( ctx->chip_select );
        err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
        err_flag |= spi_master_read( &ctx->spi, rx_data, 4 );
        spi_master_deselect_device( ctx->chip_select );
        if ( ADC22_CMD_READ == r_cmd )
        {
            *data_out = rx_data[ 0 ];
        }
        else
        {
            *data_out = rx_data[ 1 ];
        }
    }
    else
    {
        err_flag = ADC22_ERROR;
    }
    return err_flag;
}

err_t adc22_get_adc_raw_data ( adc22_t *ctx, uint16_t *raw_adc ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, DUMMY );
    while ( adc22_get_rvs( ctx ) == ADC22_PIN_STATE_HIGH );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *raw_adc = data_buf[ 0 ];
    *raw_adc <<= 8;
    *raw_adc |= data_buf[ 1 ];
    *raw_adc >>= 4;
    return err_flag;
}

err_t adc22_get_voltage ( adc22_t *ctx, float *voltage ) 
{
    uint16_t raw_adc = DUMMY;
    uint8_t range = DUMMY;
    err_t err_flag = adc22_get_adc_raw_data( ctx, &raw_adc );
    err_flag |= adc22_get_range( ctx, &range );
    if ( ADC22_RANGE_BI_2V56 >= range )
    {
        *voltage = ( float ) ( raw_adc - ADC22_ADC_ZERO_SCALE );
        *voltage /= ADC22_ADC_MIDDLE_SCALE;
    }
    else
    {      
        *voltage = ( float ) raw_adc;
        *voltage /= ADC22_ADC_FULL_SCALE;
    }
    
    range &= ~ADC22_RANGE_12V28;
    switch ( range )
    {
        case ADC22_RANGE_BI_12V28: 
        {
            *voltage *= ADC22_ADC_RANGE_12V28;
            break;
        }
        case ADC22_RANGE_BI_10V24: 
        {
            *voltage *= ADC22_ADC_RANGE_10V24;
            break;
        }
        case ADC22_RANGE_BI_6V14: 
        {
            *voltage *= ADC22_ADC_RANGE_6V14;
            break;
        }
        case ADC22_RANGE_BI_5V12: 
        {
            *voltage *= ADC22_ADC_RANGE_5V12;
            break;
        }
        case ADC22_RANGE_BI_2V56: 
        {
            *voltage *= ADC22_ADC_RANGE_2V56;
            break;
        }
        default: 
        {
            *voltage *= ( float ) DUMMY;
            err_flag = ADC22_ERROR;
            break;
        }
    }
    return err_flag;
}

err_t adc22_set_device_addr ( adc22_t *ctx, uint8_t device_addr ) 
{
    err_t err_flag = ADC22_OK;
    if ( ADC22_DEVICE_ADDR_MAX < device_addr )
    {
        err_flag = ADC22_ERROR;
    }
    else
    {
        err_flag |= adc22_write_reg( ctx, ADC22_CMD_WRITE_LS, ADC22_REG_DEVICE_ID, device_addr );
    }
    return err_flag;
}

err_t adc22_get_device_id ( adc22_t *ctx, uint8_t *device_id ) 
{
    return adc22_read_reg( ctx, ADC22_CMD_READ, ADC22_REG_DEVICE_ID, device_id );
}

err_t adc22_set_sdo_mode ( adc22_t *ctx, uint8_t sdo_mode ) 
{
    err_t err_flag = ADC22_OK;
    if ( ADC22_SDO_MODE_ADC_M_CLK < sdo_mode )
    {
        err_flag = ADC22_ERROR;
    }
    else
    {
        err_flag |= adc22_write_reg( ctx, ADC22_CMD_WRITE, ADC22_REG_SDO_CTL_LSB, sdo_mode );
    }
    return err_flag;
}

err_t adc22_en_out_data_parity ( adc22_t *ctx ) 
{
    return adc22_write_reg( ctx, ADC22_CMD_WRITE_MS, ADC22_REG_DATAOUT_CTL_LSB, 
                                 ADC22_DATAOUT_CTL_VAL_1_S | ADC22_DATAOUT_CTL_PAR_EN );
}

err_t adc22_set_range ( adc22_t *ctx, adc22_range_sel_t range ) 
{
    return adc22_write_reg( ctx, ADC22_CMD_WRITE_LS, ADC22_REG_RANGE_SEL, range );
}

err_t adc22_get_range ( adc22_t *ctx, uint8_t *range ) 
{
    uint8_t data_buf= DUMMY;
    err_t err_flag = adc22_read_reg( ctx, ADC22_CMD_READ, ADC22_REG_RANGE_SEL, &data_buf );
    *range = data_buf & ADC22_SET_RANGE_BIT_MASK;
    return err_flag;
}

// ------------------------------------------------------------------------- END

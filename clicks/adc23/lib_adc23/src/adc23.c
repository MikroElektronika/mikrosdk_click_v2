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
 * @file adc23.c
 * @brief ADC 23 Click Driver.
 */

#include "adc23.h"

/**
 * @brief Dummy and time out data.
 * @details Definition of dummy and time out data.
 */
#define DUMMY          0x00
#define WAIT_TIME_OUT  1000

/**
 * @brief ADC 23 wait data ready function.
 * @details This function waits until the data is ready.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Time out is 1000 milliseconds.
 */
static err_t adc23_wait_data_ready ( adc23_t *ctx );

void adc23_cfg_setup ( adc23_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->str = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->vref = ADC23_INT_VREF_2_5V;
}

err_t adc23_init ( adc23_t *ctx, adc23_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;
    
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
    digital_out_init( &ctx->str, cfg->str );

    digital_in_init( &ctx->rdy, cfg->rdy );

    return SPI_MASTER_SUCCESS;
}

err_t adc23_default_cfg ( adc23_t *ctx ) 
{
    adc23_hw_reset( ctx );
    Delay_100ms( );
    adc23_set_start( ctx );
    Delay_100ms( );
    err_t err_flag = adc23_sw_reset( ctx );
    Delay_100ms( );
    err_flag |= adc23_start_conversion( ctx );
    Delay_100ms( );
    err_flag |= adc23_read_conversion_data( ctx, DUMMY );
    return err_flag;
}

err_t adc23_generic_write ( adc23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc23_generic_read ( adc23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc23_generic_transfer ( adc23_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = ADC23_OK;
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        err_flag |= spi_master_set_default_write_data( &ctx->spi, data_in[ cnt ] );
        err_flag |= spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc23_read_reg_cmd ( adc23_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t *reg_data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    reg &= ADC23_MAX_REG_ADDR;
    reg |= ADC_CMD_READ_REG;
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, reg );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *reg_data_out = data_buf[ 0 ];
    return err_flag;
}

err_t adc23_read_reg_data ( adc23_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t *reg_data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    reg &= ADC23_MAX_REG_ADDR;
    reg |= ADC_CMD_READ_REG;
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 1 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    err_flag |= spi_master_set_default_write_data( &ctx->spi, reg );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    *data_out |= data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 1 );
    *reg_data_out = data_buf[ 0 ];
    err_flag |= spi_master_set_default_write_data( &ctx->spi, reg );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc23_write_reg_cmd ( adc23_t *ctx, uint8_t reg, uint8_t data_in, uint16_t *data_out ) 
{
    uint8_t data_buf = DUMMY;
    reg &= ADC23_MAX_REG_ADDR;
    reg |= ADC_CMD_WRITE_REG;
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, reg );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, &data_buf, 1 );
    *data_out = data_buf;
    *data_out <<= 8;
    err_flag |= spi_master_set_default_write_data( &ctx->spi, data_in );
    data_buf = DUMMY;
    err_flag |= spi_master_read( &ctx->spi, &data_buf, 1 );
    *data_out |= data_buf;
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc23_write_reg_data ( adc23_t *ctx, uint8_t reg, uint8_t data_in, uint32_t *data_out ) 
{
    uint8_t data_buf = DUMMY;
    reg &= ADC23_MAX_REG_ADDR;
    reg |= ADC_CMD_WRITE_REG;
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, &data_buf, 1 );
    *data_out = data_buf;
    *data_out <<= 8;
    err_flag |= spi_master_set_default_write_data( &ctx->spi, reg );
    data_buf = DUMMY;
    err_flag |= spi_master_read( &ctx->spi, &data_buf, 1 );
    *data_out |= data_buf;
    *data_out <<= 8;
    err_flag |= spi_master_set_default_write_data( &ctx->spi, data_in );
    data_buf = DUMMY;
    err_flag |= spi_master_read( &ctx->spi, &data_buf, 1 );
    *data_out |= data_buf;
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc23_sw_reset ( adc23_t *ctx ) 
{
    return adc23_write_reg_cmd( ctx, ADC_REG_CONTROL, ADC23_SET_CTRL_SW_RESET, DUMMY );
}

err_t adc23_start_conversion ( adc23_t *ctx ) 
{
    return adc23_write_reg_cmd( ctx, ADC_REG_CONTROL, ADC23_SET_CTRL_START, DUMMY );
}

err_t adc23_stop_conversion ( adc23_t *ctx ) 
{
    return adc23_write_reg_cmd( ctx, ADC_REG_CONTROL, ADC23_SET_CTRL_STOP, DUMMY );
}

err_t adc23_read_conversion_data ( adc23_t *ctx, int32_t *adc_data ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t err_flag = adc23_start_conversion( ctx );
    spi_master_select_device( ctx->chip_select );
    if ( ADC23_OK == adc23_wait_data_ready( ctx ) )
    {
        err_flag |= spi_master_read( &ctx->spi, data_buf, 3 );
        spi_master_deselect_device( ctx->chip_select );
    
        err_flag |= adc23_stop_conversion( ctx );
        *adc_data = data_buf[ 0 ];
        *adc_data <<= 8;
        *adc_data |= data_buf[ 1 ];
        *adc_data <<= 8;
        *adc_data |= data_buf[ 2 ];
        *adc_data <<= 8;
        *adc_data >>= 8;
    }
    else
    {
        err_flag = ADC23_ERROR;
    }
    return err_flag;
}

err_t adc23_get_voltage ( adc23_t *ctx, float *voltage ) 
{
    int32_t adc_data = DUMMY;
    err_t err_flag = adc23_read_conversion_data( ctx, &adc_data );
    *voltage = ( float )  adc_data;
    *voltage /= ( float ) ADC23_FULL_SCALE_OUT_DATA_RANGE;
    *voltage *= ctx->vref;
    *voltage *= ADC23_CONV_V_TO_MV;
    return err_flag;
}

void adc23_set_start ( adc23_t *ctx ) 
{
    digital_out_high( &ctx->str );
}

void adc23_set_stop ( adc23_t *ctx ) 
{
    digital_out_low( &ctx->str );
}

void adc23_hw_reset ( adc23_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t adc23_get_data_ready ( adc23_t *ctx ) 
{
    return digital_in_read( &ctx->rdy );
}

static err_t adc23_wait_data_ready ( adc23_t *ctx ) 
{
    err_t err_flag = ADC23_OK;
    uint16_t n_cnt = DUMMY;
    do
    {
        if ( WAIT_TIME_OUT == n_cnt )
        {
            err_flag = ADC23_ERROR;
            break;
        }
        n_cnt++;
        Delay_1ms( );
    }
    while ( adc23_get_data_ready( ctx ) );
    return err_flag;
}

// ------------------------------------------------------------------------- END

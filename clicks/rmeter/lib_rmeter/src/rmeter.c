/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "rmeter.h"

#define RMETER_R1Y1_OHM  200                    /*!< Resistance from negative input of OP to ground for small scale range. */
#define RMETER_R2Y1_OHM  1000                   /*!< Resistance from negative input of OP to ground for medium scale range. */
#define RMETER_R3Y1_OHM  100000                 /*!< Resistance from negative input of OP to ground for large scale range. */
#define RMETER_RFB_OHM   2000                   /*!< Resistance of feedback. */

#define RMETER_MEAS_DATA_ORDER_MSB   0          /*!< Data reading order of MSB. */
#define RMETER_MEAS_DATA_ORDER_LSB   1          /*!< Data reading order of LSB. */
#define RMETER_MEAS_DATA_OFFSET      1          /*!< Data measurement reading offset. */
#define RMETER_MEAS_DATA_MASK        0x1FFF     /*!< Data measurement mask. */
#define RMETER_MEAS_DATA_RESOLUTION  4095       /*!< Resolution of measurement conversion. */
#define RMETER_MEAS_DATA_VREF        2.048      /*!< Reference voltage of measurement conversion. */

#define RMETER_OP_VIN  0.1                      /*!< Input voltage of OP. */

/**
 * @brief Generic Reading function.
 *
 * @param ctx  Click object.
 * @param rd_buf  Data bytes.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function allows the converted measurement data to be read by using
 * SPI serial communication.
 */
static err_t rmeter_generic_read ( rmeter_t *ctx, uint8_t *rd_buf );

void rmeter_cfg_setup ( rmeter_cfg_t *cfg )
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->s3   = HAL_PIN_NC;
    cfg->s1   = HAL_PIN_NC;
    cfg->s2   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->adc_resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->adc_vref       = 3.3;
}

err_t rmeter_init ( rmeter_t *ctx, rmeter_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, 0x00 ) == SPI_MASTER_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    if ( digital_out_init( &ctx->s3, cfg->s3 ) == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return RMETER_INIT_ERROR;
    }

    if ( digital_out_init( &ctx->s2, cfg->s2 ) == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return RMETER_INIT_ERROR;
    }

    if ( digital_out_init( &ctx->s1, cfg->s1 ) == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return RMETER_INIT_ERROR;
    }

    digital_out_low( &ctx->s3 );
    digital_out_low( &ctx->s2 );
    digital_out_low( &ctx->s1 );

    ctx->ifb = 1;
    ctx->callback = NULL;

    analog_in_config_t an_cfg;

    analog_in_configure_default( &an_cfg );

    an_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->an, &an_cfg ) == ADC_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->an, cfg->adc_resolution ) == ADC_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->an, cfg->adc_vref ) == ADC_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    return RMETER_OK;
}

void rmeter_set_callback_handler ( rmeter_t *ctx, rmeter_callback_t handler )
{
    ctx->callback = handler;
}

void rmeter_set_range_up_to_1k9_ohms ( rmeter_t *ctx )
{
    digital_out_low( &ctx->s3 );
    digital_out_low( &ctx->s2 );
    digital_out_high( &ctx->s1 );

    ctx->ifb = 0.07182 / RMETER_R1Y1_OHM;
}

void rmeter_set_range_up_to_17k_ohms ( rmeter_t *ctx )
{
    digital_out_low( &ctx->s3 );
    digital_out_high( &ctx->s2 );
    digital_out_low( &ctx->s1 );

    ctx->ifb = 0.09288 / RMETER_R2Y1_OHM;
}

void rmeter_set_range_up_to_1M9_ohms ( rmeter_t *ctx )
{
    digital_out_high( &ctx->s3 );
    digital_out_low( &ctx->s2 );
    digital_out_low( &ctx->s1 );

    ctx->ifb = 0.1 / RMETER_R3Y1_OHM;
}

err_t rmeter_read_measurement ( rmeter_t *ctx, uint16_t *data_out )
{
    uint8_t read_data[ 2 ];

    if ( rmeter_generic_read( ctx, read_data ) == SPI_MASTER_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    *data_out = read_data[ RMETER_MEAS_DATA_ORDER_MSB ];
    *data_out <<= 8;
    *data_out |= read_data[ RMETER_MEAS_DATA_ORDER_LSB ];

    *data_out >>= RMETER_MEAS_DATA_OFFSET;
    *data_out &= RMETER_MEAS_DATA_MASK;

    return RMETER_OK;
}

err_t rmeter_calculate_resistance ( rmeter_t *ctx, float *data_out, uint16_t data_in )
{
    if ( data_in > RMETER_MEAS_DATA_RESOLUTION )
    {
        return RMETER_INIT_ERROR;
    }

    float vout = data_in;
    vout /= RMETER_MEAS_DATA_RESOLUTION;
    vout *= RMETER_MEAS_DATA_VREF;

    *data_out = vout - RMETER_OP_VIN;
    *data_out /= ctx->ifb;
    *data_out -= RMETER_RFB_OHM;

    return RMETER_OK;
}

uint16_t rmeter_auto_scale_range_execution ( rmeter_t *ctx )
{
    uint8_t cycle_cnt = 3;
    uint16_t vout_val;

    while ( cycle_cnt )
    {
        if ( cycle_cnt == 3 )
        {
            rmeter_set_range_up_to_1k9_ohms( ctx );
        }
        else if ( cycle_cnt == 2 )
        {
            rmeter_set_range_up_to_17k_ohms( ctx );
        }
        else
        {
            rmeter_set_range_up_to_1M9_ohms( ctx );
        }

        uint32_t sum = 0;
        uint8_t cnt_ok = 0;

        for ( uint8_t cnt = 0; cnt < 20; cnt++ )
        {
            if ( rmeter_read_measurement( ctx, &vout_val ) == RMETER_OK )
            {
                sum += vout_val;
                cnt_ok++;

                Delay_10us( );
            }
        }

        vout_val = sum / cnt_ok;

        if ( vout_val < RMETER_MEAS_DATA_RESOLUTION )
        {
            if ( ctx->callback != NULL )
            {
                if ( cycle_cnt == 3 )
                {
                    ctx->callback( "Scale range up to 1k9 ohms is set." );
                }
                else if ( cycle_cnt == 2 )
                {
                    ctx->callback( "Scale range up to 17k ohms is set." );
                }
                else
                {
                    ctx->callback( "Scale range up to 1M9 ohms is set." );
                }
            }

            return vout_val;
        }

        cycle_cnt--;
    }

    if ( ctx->callback != NULL )
    {
        ctx->callback( "Target resistor value is out of range." );
    }

    return vout_val;
}

err_t rmeter_read_an ( rmeter_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->an, data_out );
}

err_t rmeter_read_an_voltage ( rmeter_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->an, data_out );
}

static err_t rmeter_generic_read ( rmeter_t *ctx, uint8_t *rd_buf )
{
    spi_master_select_device( ctx->chip_select );
    err_t error = spi_master_read( &ctx->spi, rd_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error;
}

// ------------------------------------------------------------------------ END

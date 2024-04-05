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
 * @file ldc2.c
 * @brief LDC 2 Click Driver.
 */

#include "ldc2.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief LDC 2 convert Rp reg value function.
 * @details This function returns the Rp resistance in kOhm based on the input Rp value read from registers.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] rp_reg_value : Rp value read from registers.
 * @return Rp resistance in kOhm.
 * @note None.
 */
static float ldc2_convert_rp_reg_value( uint8_t rp_reg_value );

void ldc2_cfg_setup ( ldc2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ldc2_init ( ldc2_t *ctx, ldc2_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t ldc2_default_cfg ( ldc2_t *ctx ) 
{
    if ( LDC2_OK != ldc2_check_device_id( ctx ) )
    {
        return LDC2_ERROR;
    }
    
    err_t error_flag = ldc2_set_power_mode( ctx, LDC2_PWR_MODE_STANDBY );
    Delay_10ms( );
    error_flag |= ldc2_set_rp_range( ctx, LDC2_RP_1p347, LDC2_RP_145p444 );
    error_flag |= ldc2_set_ldc_config( ctx, LDC2_AMPLITUDE_2V, LDC2_RESPONSE_TIME_6144 );
    error_flag |= ldc2_set_comparator_threshold( ctx, LDC2_COMPARATOR_THLD_MIN, LDC2_COMPARATOR_THLD_MAX );
    error_flag |= ldc2_set_wdt_frequency( ctx );
    error_flag |= ldc2_set_interrupt_mode( ctx, LDC2_INTB_MODE_DISABLED );
    error_flag |= ldc2_set_power_mode( ctx, LDC2_PWR_MODE_ACTIVE );
    Delay_10ms( );
    
    return error_flag;
}

err_t ldc2_generic_write ( ldc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 16 ] = { 0 };

    tx_buf[ 0 ] = reg & LDC2_SPI_WRITE_MASK;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ldc2_generic_read ( ldc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    reg |= LDC2_SPI_READ_MASK;
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ldc2_check_device_id ( ldc2_t *ctx )
{
    uint8_t dev_id = 0;
    
    if ( LDC2_OK == ldc2_generic_read( ctx, LDC2_REG_DEVICE_ID, &dev_id, 1 ) )
    {
        if ( LDC2_DEVICE_ID == dev_id )
        {
            return LDC2_OK;
        }
    }
    
    return LDC2_ERROR;
}

err_t ldc2_set_rp_range ( ldc2_t *ctx, ldc2_rp_range_t rp_min, ldc2_rp_range_t rp_max )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    
    tx_buf[ 0 ] = rp_max;
    tx_buf[ 1 ] = rp_min + 0x20;
    
    return ldc2_generic_write ( ctx, LDC2_REG_RP_MAX, tx_buf, 2 );
}

err_t ldc2_set_ldc_config ( ldc2_t *ctx, ldc2_amplitude_t amplitude, ldc2_resp_time_t res_time )
{
    uint8_t tx_data = 0;
    
    tx_data = ( amplitude << 3 ) | res_time;
    
    return ldc2_generic_write ( ctx, LDC2_REG_RP_MAX, &tx_data, 1 );
}

err_t ldc2_set_comparator_threshold ( ldc2_t *ctx, uint8_t thld_low, uint8_t thld_high )
{
    err_t error_flag = ldc2_generic_write ( ctx, LDC2_REG_COMPARATOR_THLD_HIGH, &thld_high, 1 );
    error_flag |= ldc2_generic_write ( ctx, LDC2_REG_COMPARATOR_THLD_LOW, &thld_low, 1 );
    
    return error_flag;
}

err_t ldc2_set_interrupt_mode ( ldc2_t *ctx, ldc2_int_mode_t mode )
{
    uint8_t tx_data = 0;
    
    tx_data = mode;
    
    return ldc2_generic_write ( ctx, LDC2_REG_INTB_TERMINAL_CONFIG, &tx_data, 1 );
}

err_t ldc2_set_power_mode ( ldc2_t *ctx, ldc2_pwr_mode_t mode )
{
    uint8_t tx_data = 0;
    
    tx_data = mode;
    
    return ldc2_generic_write ( ctx, LDC2_REG_POWER_CONFIG, &tx_data, 1 );
}

err_t ldc2_get_status ( ldc2_t *ctx, uint8_t *status )
{
    return ldc2_generic_read( ctx, LDC2_REG_STATUS, status, 1 );
}

err_t ldc2_read_raw_data ( ldc2_t *ctx, uint8_t *prox_data, uint32_t *freq_cnt )
{
    uint8_t tx_buf[ 4 ] = { 0 };
    err_t error_flag = ldc2_get_status( ctx, tx_buf );    
    if ( tx_buf[ 0 ] & LDC2_STATUS_NO_NEW_DATA )
    {
        return LDC2_STATUS_NO_NEW_DATA;
    }
    error_flag |= ldc2_generic_read( ctx, LDC2_REG_PROXIMITY_DATA, tx_buf, 4 );
    
    *prox_data = tx_buf[ 0 ];
    
    *freq_cnt = tx_buf[ 3 ];
    *freq_cnt <<= 8;
    *freq_cnt |= tx_buf[ 2 ];
    *freq_cnt <<= 8;
    *freq_cnt |= tx_buf[ 1 ];
    
    return error_flag;
}

err_t ldc2_get_response_time ( ldc2_t *ctx, uint16_t *res_time )
{
    uint8_t rx_data = 0;
    err_t error_flag = ldc2_generic_read ( ctx, LDC2_REG_LDC_CONFIG, &rx_data, 1 );
    
    rx_data &= LDC2_RESPONSE_TIME_6144;
    
    if ( rx_data >= LDC2_RESPONSE_TIME_192 )
    {
        *res_time = 192 << ( rx_data - LDC2_RESPONSE_TIME_192 );
    }
    
    return error_flag;
}

err_t ldc2_get_sensor_frequency ( ldc2_t *ctx, float *freq )
{
    uint8_t prox_data = 0;
    uint32_t freq_cnt = 0;
    uint16_t res_time = 0;
    
    err_t error_flag = ldc2_read_raw_data ( ctx, &prox_data, &freq_cnt );
    
    error_flag |= ldc2_get_response_time ( ctx, &res_time );
    
    if ( freq_cnt > 0 )
    {
        *freq = ( 1.0 / 3.0 ) * ( LDC2_EXTERNAL_OSC_MHZ / ( float ) freq_cnt ) * ( float ) res_time;
    }
    
    return error_flag;
}

err_t ldc2_get_rp_range ( ldc2_t *ctx, float *rp_min, float *rp_max )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    
    err_t error_flag = ldc2_generic_read ( ctx, LDC2_REG_RP_MAX, rx_buf, 2 );
    
    *rp_max = ldc2_convert_rp_reg_value( rx_buf[ 0 ] & 0x1F );
    *rp_min = ldc2_convert_rp_reg_value( ( rx_buf[ 1 ] & 0x3F ) - 0x20 );
    
    return error_flag;
}

err_t ldc2_set_wdt_frequency ( ldc2_t *ctx )
{
    float freq = 0;
    uint8_t wdt_value = 0;
    
    err_t error_flag = ldc2_get_sensor_frequency ( ctx, &freq );
    
    wdt_value = ( uint8_t ) ( LDC2_MIN_SENSOR_FREQ_CONST * 
                              log10( ( freq * LDC2_MHZ_TO_HZ ) / LDC2_MIN_SENSOR_FREQ_DIVIDER ) + LDC2_ROUND_TO_NEAREST_INT );
    
    error_flag |= ldc2_generic_write ( ctx, LDC2_REG_WDT_FREQ, &wdt_value, 1 );
    
    return error_flag;
}

uint8_t ldc2_get_int_pin ( ldc2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ldc2_measure_resonance_impedance ( ldc2_t *ctx, uint8_t *prox_data, float *rp_data )
{
    uint32_t freq_cnt = 0;
    float rp_max = 0;
    float rp_min = 0;
    float y_data = 0;
    
    err_t error_flag = ldc2_read_raw_data ( ctx, prox_data, &freq_cnt );
    
    y_data = ( float ) *prox_data / 128.0;
    
    error_flag |= ldc2_get_rp_range ( ctx, &rp_min, &rp_max );
    
    if ( rp_min > 0 )
    {
        *rp_data = ( rp_max * rp_min ) / ( ( rp_min * ( 1.0 - y_data ) ) + ( rp_max * y_data ) );
    }
    
    return error_flag;
}

err_t ldc2_measure_inductance ( ldc2_t *ctx, float *freq, float *inductance )
{
    err_t error_flag = ldc2_get_sensor_frequency ( ctx, freq );
    
    if ( *freq > 0 )
    {
        *inductance = 1.0 / ( LDC2_PARALLEL_CAPACITANCE_uF * pow( LDC2_MATH_TWO_PI * *freq, 2.0 ) );
    }
    
    return error_flag;
}

static float ldc2_convert_rp_reg_value( uint8_t rp_reg_value )
{
    switch ( rp_reg_value )
    {
        case LDC2_RP_3926p991:
        {
            return 3926.991;
        }
        case LDC2_RP_3141p593:
        {
            return 3141.593;
        }
        case LDC2_RP_2243p995:
        {
            return 2243.995;
        }
        case LDC2_RP_1745p329:
        {
            return 1745.329;
        }
        case LDC2_RP_1308p997:
        {
            return 1308.997;
        }
        case LDC2_RP_981p748:
        {
            return 981.748;
        }
        case LDC2_RP_747p998:
        {
            return 747.998;
        }
        case LDC2_RP_581p776:
        {
            return 581.776;
        }
        case LDC2_RP_436p332:
        {
            return 436.332;
        }
        case LDC2_RP_349p066:
        {
            return 349.066;
        }
        case LDC2_RP_249p333:
        {
            return 249.333;
        }
        case LDC2_RP_193p926:
        {
            return 193.936;
        }
        case LDC2_RP_145p444:
        {
            return 145.444;
        }
        case LDC2_RP_109p083:
        {
            return 109.083;
        }
        case LDC2_RP_83p111:
        {
            return 83.111;
        }
        case LDC2_RP_64p642:
        {
            return 64.642;
        }
        case LDC2_RP_48p481:
        {
            return 48.481;
        }
        case LDC2_RP_38p785:
        {
            return 38.785;
        }
        case LDC2_RP_27p704:
        {
            return 27.704;
        }
        case LDC2_RP_21p547:
        {
            return 21.547;
        }
        case LDC2_RP_16p160:
        {
            return 16.160;
        }
        case LDC2_RP_12p120:
        {
            return 12.120;
        }
        case LDC2_RP_9p235:
        {
            return 9.235;
        }
        case LDC2_RP_7p182:
        {
            return 7.182;
        }
        case LDC2_RP_5p387:
        {
            return 5.387;
        }
        case LDC2_RP_4p309:
        {
            return 4.309;
        }
        case LDC2_RP_3p078:
        {
            return 3.078;
        }
        case LDC2_RP_2p394:
        {
            return 2.394;
        }
        case LDC2_RP_1p796:
        {
            return 1.796;
        }
        case LDC2_RP_1p347:
        {
            return 1.347;
        }
        case LDC2_RP_1p026:
        {
            return 1.026;
        }
        case LDC2_RP_0p798:
        {
            return 0.798;
        }
        default:
        {
            return 0.0;
        }
    }
}
// ------------------------------------------------------------------------- END

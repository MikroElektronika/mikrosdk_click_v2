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
 * @file tdc.c
 * @brief TDC Click Driver.
 */

#include "tdc.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                     0x00

/**
 * @brief Max stop number.
 * @details Definition of max stop number.
 */
#define DEV_MAX_NUM_STOPS         5


/**
 * @brief Calibration2.
 * @details Number of measuring clock periods, one of ( 2, 10, 20, 40 ).
 */
uint8_t  m_cal_2_periods;

/**
 * @brief CONFIG1 register value.
 * @details CONFIG1 register value to start measurement.
 */
uint8_t  m_config1;

/**
 * @brief Measurement mode.
 * @details Measurement mode ( 1, 2 ).
 */
uint8_t  m_mode;

/**
 * @brief Cached Norm LSB.
 * @details Cached norm_lsb value for tof calculation.
 */
uint32_t  m_norm_lsb; 

/**
 * @brief Clock period.
 * @details Clock period in ( ps ).
 */
uint32_t m_clk_period_ps;

/**
 * @brief Overflow time.
 * @details Overflow time in ( ps ).
 */
uint32_t m_overflow_ps;

/**
 * @brief TDC 24-bits reading function.
 * @details This function reads a 24-bytes from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return Output read data.
 * 
 * @note None.
 */
static uint32_t dev_get_24 ( tdc_t *ctx, uint8_t reg );

/**
 * @brief Puls delay function.
 *
 * @description The function performs the delay of 1 us.
 */
static void dev_puls_delay ( void );

/**
 * @brief Reset delay function.
 *
 * @description The function performs the delay of 5 ms.
 */
static void dev_reset_delay ( void );

void tdc_cfg_setup ( tdc_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->oen   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->trg = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    cfg->stop   = HAL_PIN_NC;
    cfg->start   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t tdc_init ( tdc_t *ctx, tdc_cfg_t *cfg ) 
{
    digital_out_init( &ctx->stop, cfg->stop );
    digital_out_init( &ctx->start, cfg->start );
    digital_out_init( &ctx->stop, cfg->stop );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->oen, cfg->oen );
    digital_out_low( &ctx->start );
    digital_out_low( &ctx->stop );
    digital_out_low( &ctx->en );
    digital_out_high( &ctx->oen );
    
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

    digital_in_init( &ctx->trg, cfg->trg );
    digital_in_init( &ctx->int_pin, cfg->int_pin ); 

    return SPI_MASTER_SUCCESS;
}

err_t tdc_default_cfg ( tdc_t *ctx ) 
{
    digital_out_low( &ctx->en );
    dev_reset_delay( );
    digital_out_high( &ctx->en );
    dev_reset_delay( );
    
    m_clk_period_ps = PS_PER_K_SEC / ( TDC_RING_OSC_FREQ_KHZ * 2 );
    m_overflow_ps = 0;
    
    tdc_generic_write_byte( ctx, TDC_REG_ADR_INT_MASK, 0x04 | 0x02 | 0x01 );
    
    return TDC_OK;
}

err_t tdc_generic_write ( tdc_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= 0x1F;
    tx_buf[ 0 ] |= 0x80;
    tx_buf[ 0 ] |= 0x40;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t tdc_generic_read ( tdc_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {

    reg &= 0x1F;
    reg |= 0x80;
    reg |= 0x00;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t tdc_generic_write_byte ( tdc_t *ctx, uint8_t reg, uint8_t data_in ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= 0x1F;
    tx_buf[ 0 ] |= 0x40;
    tx_buf[ 1 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t tdc_generic_read_byte ( tdc_t *ctx, uint8_t reg, uint8_t *data_out ) {

    reg &= 0x1F;
    reg |= 0x00;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void tdc_gen_pulse ( tdc_t *ctx, uint32_t u_sec, uint8_t n_stops ) {

    digital_out_low( &ctx->start );
    dev_puls_delay( );
    digital_out_high( &ctx->start );
    dev_puls_delay( );
    digital_out_low( &ctx->start );

    u_sec -= 2;
    for ( uint8_t n_cnt = 0; n_cnt < n_stops; ++n_cnt ) {
        for ( uint32_t m_cnt = 0; m_cnt < u_sec; m_cnt++ ) {
            Delay_1us( );
        }
        
       digital_out_low( &ctx->stop );
       dev_puls_delay( );
       digital_out_high( &ctx->stop );
       dev_puls_delay( );
       digital_out_low( &ctx->stop );
    }
   
}

void tdc_start_measurement ( tdc_t *ctx ) {
    tdc_generic_write_byte( ctx, TDC_REG_ADR_INT_STATUS, 0x1F );

    m_norm_lsb = 0;

    tdc_generic_write_byte( ctx, 0x00, m_config1 );
    
    tdc_generic_write_byte( ctx, 0x00, 0x83 );
    
    tdc_generic_write_byte( ctx, 0x01, 0x44 );
}

void tdc_setup_overflow ( tdc_t *ctx, uint32_t overflow_ps ) {
    uint32_t ovf;
    uint16_t coarse_ovf; 
    uint16_t clock_ovf; 
    
    coarse_ovf = 0xFFFF;   
    clock_ovf  = 0xFFFF;

    if ( overflow_ps ) {
        if ( m_mode == 1 ) {

            ovf = ( overflow_ps * TDC_RING_OSC_FREQ_MHZ ) / US_PER_K_SEC;

            if ( ovf < 0xFFFF ) {
                coarse_ovf = ovf;
            }
        }
        else {
            ovf = overflow_ps / m_clk_period_ps;

            if ( ovf < 0xFFFF ) {
                clock_ovf = ovf;
            }
        }
    }

    tdc_generic_write_byte( ctx, TDC_REG_ADR_COARSE_CNTR_OVF_H, coarse_ovf >> 8) ;
    tdc_generic_write_byte( ctx, TDC_REG_ADR_COARSE_CNTR_OVF_L, coarse_ovf );

    tdc_generic_write_byte( ctx, TDC_REG_ADR_CLOCK_CNTR_OVF_H, clock_ovf >> 8 );
    tdc_generic_write_byte( ctx, TDC_REG_ADR_CLOCK_CNTR_OVF_L, clock_ovf );

    m_overflow_ps = overflow_ps;
}

err_t tdc_setup_measurement ( tdc_t *ctx, uint8_t cal_periods, uint8_t avg_cycles, uint8_t num_stops, uint8_t mode ) {
    uint8_t config2 = 0;
    uint8_t tmp_val;

    if ( cal_periods == 2 )  {
        config2 = TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_2  << TDC_REG_SHIFT_CONFIG2_CALIBRATION2_PERIODS;
    }
    else if ( cal_periods == 10 ) {
        config2 = TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_10 << TDC_REG_SHIFT_CONFIG2_CALIBRATION2_PERIODS;
    }
    else if ( cal_periods == 20 ) {
        config2 = TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_20 << TDC_REG_SHIFT_CONFIG2_CALIBRATION2_PERIODS;
    }
    else if ( cal_periods == 40 ) {
        config2 = TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_40 << TDC_REG_SHIFT_CONFIG2_CALIBRATION2_PERIODS;
    }
    else return TDC_ERROR;
    
    m_cal_2_periods = cal_periods;

    tmp_val = TDC_REG_VAL_CONFIG2_AVG_CYCLES_MIN_VAL;
    
    do {
        if ( ( 1 << tmp_val ) == avg_cycles ) {
            config2 |= tmp_val << TDC_REG_SHIFT_CONFIG2_AVG_CYCLES;
            break;
        }
        ++tmp_val;
    } while ( tmp_val <= TDC_REG_VAL_CONFIG2_AVG_CYCLES_MAX_VAL );
    
    if ( tmp_val > TDC_REG_VAL_CONFIG2_AVG_CYCLES_MAX_VAL ) {
        return TDC_ERROR;   
    }
       
    if ( ( num_stops == 0 ) || ( num_stops > TDC_REG_VAL_CONFIG2_NUM_STOP_MAX ) ) {
        return TDC_ERROR;    
    }
       
    config2 |= TDC_REG_VAL_CONFIG2_NUM_STOP( num_stops ) << TDC_REG_SHIFT_CONFIG2_NUM_STOP;

    if ( ( mode < TDC_REG_VAL_CONFIG1_MEAS_MODE_MIN ) || ( mode > TDC_REG_VAL_CONFIG1_MEAS_MODE_MAX ) ) {
        return TDC_ERROR;    
    }
        
    m_mode = mode;
    m_config1 = TDC_REG_VAL_CONFIG1_MEAS_MODE(mode) << TDC_REG_SHIFT_CONFIG1_MEAS_MODE;

    tdc_setup_overflow( ctx, m_overflow_ps );

    m_config1 |= 0x01;

    tdc_generic_write_byte( ctx, TDC_REG_ADR_CONFIG2, config2 );

    return TDC_OK;     
}

err_t tdc_get_measurement ( tdc_t *ctx, uint8_t clock_mode, uint8_t measure_num_stop, uint32_t *time, uint32_t *clock_countn, uint32_t *tof ) {
    uint32_t t_buf[ 3 ];
    int32_t calibration1;
    int32_t calibration2;
    uint8_t shift;
    uint32_t cal_count;
    
    shift = 20;

    if ( measure_num_stop > DEV_MAX_NUM_STOPS ) {
        return TDC_ERROR;    
    }
        
    calibration1 = dev_get_24( ctx, TDC_REG_ADR_CALIBRATION1 );
    calibration2 = dev_get_24( ctx, TDC_REG_ADR_CALIBRATION2 );

    cal_count = (  ( int32_t ) ( calibration2 - calibration1 ) << shift ) / ( uint32_t ) ( m_cal_2_periods - 1 );

    m_norm_lsb = ( ( uint32_t ) ( m_clk_period_ps ) << ( 2 * shift ) )  / cal_count;

    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        time[ n_cnt ] = dev_get_24( ctx, TDC_REG_ADR_TIME1 + ( 2 * n_cnt ) ); 
        clock_countn[ n_cnt ] = dev_get_24( ctx, TDC_REG_ADR_CLOCK_COUNT1 + ( 2 * n_cnt ) ); 
    }
    
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {       
        if ( clock_mode == TDC_MCU_CLOCK_MODE_168_MHZ ) {
            tof[ n_cnt ] = ( ( time[ n_cnt ] - time[ n_cnt + 1 ] ) * m_clk_period_ps ) >> shift;
            tof[ n_cnt ] += clock_countn[ n_cnt ] * m_clk_period_ps;
            tof[ n_cnt ] *= TDC_CLOCK_FREQ_HZ_PS_PER_ARM_SEC;
            tof[ n_cnt ] /= TDC_CLOCK_FREQ_HZ;
            tof[ n_cnt ] -= ( measure_num_stop + n_cnt - 1 );
        } else if ( clock_mode == TDC_MCU_CLOCK_MODE_80_MHZ ) {
            tof[ n_cnt ] = clock_countn[ n_cnt ] - ( n_cnt * 4 );
            tof[ n_cnt ] *= PS_PER_PIC32_SEC;
            tof[ n_cnt ] /= TDC_CLOCK_FREQ_HZ;
            tof[ n_cnt ] -= ( measure_num_stop + n_cnt ) * 2; 
        } else if  ( clock_mode == TDC_MCU_CLOCK_MODE_64_MHZ ) {
            tof[ n_cnt ] = ( uint32_t ) ( clock_countn[ n_cnt ] - ( 115 + ( n_cnt * 10 ) ) ); 
            tof[ n_cnt ] *= TDC_CLOCK_FREQ_HZ_PS_PER_PIC_SEC; 
            tof[ n_cnt ] -= ( measure_num_stop - 1 ) + ( n_cnt * 5 );
        }  
    }

    return TDC_OK;
}

uint8_t tdc_get_interrupt ( tdc_t *ctx ) {
       
    return digital_in_read( &ctx->int_pin );
}

uint8_t tdc_get_trg ( tdc_t *ctx ) {
       
    return digital_in_read( &ctx->trg );
}

static uint32_t dev_get_24 ( tdc_t *ctx, uint8_t reg ) {
    uint8_t rx_buf[ 3 ];
    uint32_t result;
    
    reg &= 0x1F;
    reg |= 0x00;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    result = rx_buf[ 0 ] & 0x7F;
    result <<= 8;
    result |= rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 2 ];

    return result;
}

static void dev_puls_delay ( void ) {
    Delay_1us( );
}

static void dev_reset_delay ( void ) {
    Delay_5ms( );
}

// ------------------------------------------------------------------------- END

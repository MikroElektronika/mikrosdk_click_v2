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
 * @file waveform3.c
 * @brief Waveform 3 Click Driver.
 */

#include "waveform3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x0000

/**
 * @brief Clock input frequency.
 * @details This is the frequency of MCLK in Hz.
 */
#define DEV_WAVEFORM3_FMCLK                              16000000

/**
 * @brief Frequency resolution.
 * @details This is the resolution of frequency ( 2^28 ).
 */
#define DEV_WAVEFORM3_RESOLUTION                         268435456

/**
 * @brief Correction coefficient constant.
 * @details Used to set more accurate frequency on output.
 */
#define DEV_WAVEFORM3_CORR_COEFF                         1.0488

/**
 * @brief Write register lsb mask.
 * @details Extracts the least significant byte from a word.
 */
#define DEV_WAVEFORM3_WR_REG_MASK_LSB                    0x00FF

/**
 * @brief Write register msb mask.
 * @details Extracts the most significant byte from a word.
 */
#define DEV_WAVEFORM3_WR_REG_MASK_MSB                    0xFF00

/**
 * @brief Maximal output frequency.
 * @details Limiting output frequency in Hz.
 */
#define DEV_WAVEFORM3_FREQ_SET_MAX                       15000000

/**
 * @brief Frequency step size.
 * @details Used for return value of frequency that has been set.
 */
#define DEV_WAVEFORM3_FREQ_STEP_SIZE                     0.0596

/**
 * @brief Frequency lsb mask.
 * @details Used to extract the least significant 14-bit for frequency.
 */
#define DEV_WAVEFORM3_FREQ_MASK_LSB                      0x3FFF

/**
 * @brief Frequency msb mask.
 * @details Used to extract the most significant 14-bit for frequency.
 */
#define DEV_WAVEFORM3_FREQ_MASK_MSB                      0xFFFC000

/**
 * @brief Freq0 channel mask.
 * @details Used to set frequency for freq0.
 */
#define DEV_WAVEFORM3_FREQ0_BITMASK                      0x4000

/**
 * @brief Freq1 channel mask.
 * @details Used to set frequency for freq1.
 */
#define DEV_WAVEFORM3_FREQ1_BITMASK                      0x8000

/**
 * @brief Freq0 channel bitmask retval.
 * @details Bitmask used for return value of freq0.
 */
#define DEV_WAVEFORM3_FREQ0_BITMASK_RETVAL               0xBFFF

/**
 * @brief Freq1 channel bitmask retval.
 * @details Bitmask used for return value of freq1.
 */
#define DEV_WAVEFORM3_FREQ1_BITMASK_RETVAL               0x7FFF

/**
 * @brief Maximal output phase shift.
 * @details Limiting output phase shift in angle degrees.
 */
#define DEV_WAVEFORM3_PHASE_SET_MAX                      360

/**
 * @brief Phase resolution.
 * @details This is the resolution of phase shift ( 2^12 ).
 */
#define DEV_WAVEFORM3_PHASE_RESOLUTION                   4096

/**
 * @brief Phase bitmask.
 * @details This bitmask is used for safe storage of phase shift.
 */
#define DEV_WAVEFORM3_PHASE_BITMASK                      0xF000

/**
 * @brief Phase bitmask retval.
 * @details Bitmask used for return value of phase shift.
 */
#define DEV_WAVEFORM3_PHASE_BITMASK_RETVAL               0x0FFF

/**
 * @brief Phase0 channel mask.
 * @details Used to set frequency for phase0.
 */
#define DEV_WAVEFORM3_PHASE0_MASK                        0xE000

/**
 * @brief Phase1 channel mask.
 * @details Used to set frequency for phase1.
 */
#define DEV_WAVEFORM3_PHASE1_MASK                        0xC000

void waveform3_cfg_setup ( waveform3_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t waveform3_init ( waveform3_t *ctx, waveform3_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    return SPI_MASTER_SUCCESS;
}

void waveform3_default_cfg ( waveform3_t *ctx ) {
    // Click default configuration.
    waveform3_set_freq( ctx, WAVEFORM3_DEFAULT_FREQ0, WAVEFORM3_CFG_FREQ_REG0 );
    waveform3_set_freq( ctx, WAVEFORM3_DEFAULT_FREQ1, WAVEFORM3_CFG_FREQ_REG1 );
    waveform3_set_phase( ctx, WAVEFORM3_DEFAULT_PHASE0, WAVEFORM3_CFG_PHASE_REG0 );
    waveform3_set_phase( ctx, WAVEFORM3_DEFAULT_PHASE1, WAVEFORM3_CFG_PHASE_REG1 );
    waveform3_reset( ctx );
}

void waveform3_write_register ( waveform3_t *ctx, uint16_t data_in ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( uint8_t )( ( data_in & DEV_WAVEFORM3_WR_REG_MASK_MSB ) >> 8 );
    tx_buf[ 1 ] = ( uint8_t )( data_in & DEV_WAVEFORM3_WR_REG_MASK_LSB );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void waveform3_reset ( waveform3_t *ctx ) {
    waveform3_write_register( ctx, WAVEFORM3_REG_RESET_BIT );
    waveform3_write_register( ctx, WAVEFORM3_REG_RESET_CLEAR );
}

uint32_t waveform3_set_freq ( waveform3_t *ctx, uint32_t frequency, uint8_t freq_reg ) {
    uint16_t freq_lsb;
    uint16_t freq_msb;
    float step_size;
    uint32_t freq_bitmask;
    uint32_t retval_freq = 0;

    if ( frequency > DEV_WAVEFORM3_FREQ_SET_MAX ) {
        frequency = DEV_WAVEFORM3_FREQ_SET_MAX;
    }
    
    step_size = DEV_WAVEFORM3_RESOLUTION / DEV_WAVEFORM3_FMCLK;
    frequency = ( uint32_t )( frequency * step_size * DEV_WAVEFORM3_CORR_COEFF );

    freq_lsb = ( uint16_t )( frequency & DEV_WAVEFORM3_FREQ_MASK_LSB );
    freq_msb = ( uint16_t )( ( frequency & DEV_WAVEFORM3_FREQ_MASK_MSB ) >> 14 );

    if ( freq_reg == WAVEFORM3_CFG_FREQ_REG1 ) {
        freq_lsb |= DEV_WAVEFORM3_FREQ1_BITMASK;
        freq_msb |= DEV_WAVEFORM3_FREQ1_BITMASK;
        freq_bitmask = DEV_WAVEFORM3_FREQ1_BITMASK_RETVAL;
    } else {
        freq_lsb |= DEV_WAVEFORM3_FREQ0_BITMASK;
        freq_msb |= DEV_WAVEFORM3_FREQ0_BITMASK;
        freq_bitmask = DEV_WAVEFORM3_FREQ0_BITMASK_RETVAL;
    }

    waveform3_write_register( ctx, freq_lsb );
    waveform3_write_register( ctx, freq_msb );
    
    retval_freq = ( uint32_t )freq_lsb & freq_bitmask;
    retval_freq |= ( ( uint32_t )freq_msb & freq_bitmask ) << 14;
    retval_freq = ( uint32_t )( retval_freq * DEV_WAVEFORM3_FREQ_STEP_SIZE );
    
    return retval_freq;
}

uint16_t waveform3_set_phase ( waveform3_t *ctx, float phase, uint8_t phase_reg ) {
    uint16_t retval_phase = 0;
    uint16_t phase_temp = 0;
    
    if ( phase <= DEV_WAVEFORM3_PHASE_SET_MAX ) {
        phase *= DEV_WAVEFORM3_PHASE_RESOLUTION;
        phase /= DEV_WAVEFORM3_PHASE_SET_MAX;
        phase_temp = ( uint16_t )( phase ) & ~DEV_WAVEFORM3_PHASE_BITMASK;
    
        if ( phase_reg == WAVEFORM3_CFG_PHASE_REG1 ) {
            phase_temp |= DEV_WAVEFORM3_PHASE1_MASK;
        } else {
            phase_temp |= DEV_WAVEFORM3_PHASE0_MASK;
        }
        
        waveform3_write_register( ctx, phase_temp );
        
        retval_phase = phase_temp & DEV_WAVEFORM3_PHASE_BITMASK_RETVAL;
    }
    return retval_phase;
}

void waveform3_set_mode ( waveform3_t *ctx, uint8_t mode, uint8_t freq_reg, uint8_t phase_reg ) {
    uint16_t config_reg = WAVEFORM3_REG_B28_BIT;
    
    switch ( mode ) {
        case WAVEFORM3_CFG_MODE_TRIANGLE:
            config_reg |= WAVEFORM3_REG_MODE_BIT;
            break;
        case WAVEFORM3_CFG_MODE_DAC_2:
            config_reg |= WAVEFORM3_REG_OPBITEN_BIT;
            break;
        case WAVEFORM3_CFG_MODE_DAC:
            config_reg |= WAVEFORM3_REG_OPBITEN_BIT | WAVEFORM3_REG_DIV2_BIT;
            break;
        default:
            config_reg |= DUMMY;
            break;
    }
    if ( freq_reg == WAVEFORM3_CFG_FREQ_REG1 ) {
        config_reg |= WAVEFORM3_REG_FSEL_BIT;
    }
    if ( phase_reg == WAVEFORM3_CFG_PHASE_REG1 ) {
        config_reg |= WAVEFORM3_REG_PSEL_BIT;
    }
    
    waveform3_write_register( ctx, config_reg );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END

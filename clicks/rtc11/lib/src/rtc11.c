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
 * @file rtc11.c
 * @brief RTC 11 Click Driver.
 */

#include "rtc11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Max min. & sec.
 * @details Maximum value of minutes and seconds.
 */
#define MAX_MIN_SEC                  59

/**
 * @brief Max hour value.
 * @details Maximum hour value.
 */
#define MAX_HOUR                     23

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Converts BCD to binary.
 * @details Function that is converting BCD to binary.
 */
static uint8_t dev_bcd_to_bin ( uint8_t value );

/**
 * @brief Converts binary to BCD.
 * @details Function that is converting binary to BCD.
 */
static uint8_t dev_bin_to_bcd ( uint8_t value );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void rtc11_cfg_setup ( rtc11_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wdi   = HAL_PIN_NC;
    cfg->exi = HAL_PIN_NC;
    cfg->it2 = HAL_PIN_NC;
    cfg->it1 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t rtc11_init ( rtc11_t *ctx, rtc11_cfg_t *cfg ) {
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

    digital_out_init( &ctx->wdi, cfg->wdi );
    digital_out_init( &ctx->exi, cfg->exi );

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );

    return SPI_MASTER_SUCCESS;
}

void rtc11_generic_write ( rtc11_t *ctx, uint8_t reg, uint8_t *wr_data, uint16_t n_len ) {
    uint8_t tx_buf[ 512 ];
    uint16_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= RTC11_WR_BIT_MASK;

    for ( cnt = 0; cnt < n_len; cnt++ ) {
        tx_buf[ cnt + 1 ] = wr_data[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, n_len + 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void rtc11_generic_read ( rtc11_t *ctx, uint8_t reg, uint8_t *rd_data, uint16_t n_len ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 512 ];
    uint16_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= RTC11_RD_BIT_MASK;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, n_len );
    spi_master_deselect_device( ctx->chip_select );
    
    for ( cnt = 0; cnt < n_len; cnt++ ) {
        rd_data[ cnt ] = rx_buf [ cnt ];
    }
}

uint8_t rtc11_check_irq_1 ( rtc11_t *ctx ) {
    return digital_in_read( &ctx->it1 );
}

uint8_t rtc11_check_irq_2 ( rtc11_t *ctx ) {
    return digital_in_read( &ctx->it2 );
}

void rtc11_wdi ( rtc11_t *ctx, uint8_t state ) {
    if ( state == RTC11_PROP_EN ) {
        digital_out_high( &ctx->wdi );
    } else {
        digital_out_low( &ctx->wdi );
    }
}

void rtc11_ext_int ( rtc11_t *ctx, uint8_t state ) {
    if ( state == RTC11_PROP_EN ) {
        digital_out_high( &ctx->exi );
    } else {
        digital_out_low( &ctx->exi );
    }
}

void rtc11_set_time_hundredths ( rtc11_t *ctx, uint8_t hundredths ) {
    uint8_t temp = 0;

    temp = dev_bin_to_bcd( hundredths );

    rtc11_generic_write( ctx, RTC11_REG_HDT, &temp, 1 );
}

void rtc11_set_time_seconds ( rtc11_t *ctx, uint8_t seconds ) {
    uint8_t temp = 0;

    seconds &= 0x7F;

    temp = dev_bin_to_bcd( seconds );

    rtc11_generic_write( ctx, RTC11_REG_SEC, &temp, 1 );
}

void rtc11_set_time_minutes ( rtc11_t *ctx, uint8_t minutes ) {
    uint8_t temp = 0;

    minutes &= 0x7F;

    temp = dev_bin_to_bcd( minutes );

    rtc11_generic_write( ctx, RTC11_REG_MIN, &temp, 1 );
}

void rtc11_set_time_hours ( rtc11_t *ctx, uint8_t hours ) {
    uint8_t temp = 0;
    hours &= 0x1F;
    temp = dev_bin_to_bcd( hours );
    rtc11_generic_write( ctx, RTC11_REG_HRS, &temp, 1 );
}

uint8_t rtc11_get_time_hundredths ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_HDT, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_time_seconds ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_SEC, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_time_minutes ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_MIN, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_time_hours ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_HRS, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_date_day ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_DAT, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

void rtc11_set_date_day ( rtc11_t *ctx, uint8_t date_day ) {
    uint8_t temp = 0;

    date_day &= 0x3F;

    temp = dev_bin_to_bcd( date_day );

    rtc11_generic_write( ctx, RTC11_REG_DAT, &temp, 1 );
}

uint8_t rtc11_get_date_month ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_MON, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

void rtc11_set_date_month ( rtc11_t *ctx, uint8_t date_mth ) {
    uint8_t temp = 0;

    date_mth &= 0x1F;

    temp = dev_bin_to_bcd( date_mth );

    rtc11_generic_write( ctx, RTC11_REG_MON, &temp, 1 );
}

uint8_t rtc11_get_date_year ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_YRS, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

void rtc11_set_date_year ( rtc11_t *ctx, uint16_t date_yrs ) {
    uint8_t temp = 0;
    date_yrs &= 0x3F;
    temp = dev_bin_to_bcd( date_yrs );

    rtc11_generic_write( ctx, RTC11_REG_YRS, &temp, 1 );
}

uint8_t rtc11_get_century_flag ( rtc11_t *ctx ) {
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_STAT, &temp, 1 );

    temp >= 7;
    temp &= 0x01;

    return temp;
}

uint8_t rtc11_get_day_of_the_week ( rtc11_t *ctx ) {
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_WKD, &temp, 1 );

    return temp;
}

void rtc11_set_day_of_the_week ( rtc11_t *ctx, uint8_t w_day ) {
    w_day &= 0x07;

    rtc11_generic_write( ctx, RTC11_REG_WKD, &w_day, 1 );
}

void rtc11_set_ala_time_hundredths ( rtc11_t *ctx, uint8_t hundredths ) {
    uint8_t temp = 0;

    temp = dev_bin_to_bcd( hundredths );

    rtc11_generic_write( ctx, RTC11_REG_ALA_HDT, &temp, 1 );
}

void rtc11_set_ala_time_seconds ( rtc11_t *ctx, uint8_t seconds ) {
    uint8_t temp = 0;

    seconds &= 0x7F;

    temp = dev_bin_to_bcd( seconds );

    rtc11_generic_write( ctx, RTC11_REG_ALA_SEC, &temp, 1 );
}

void rtc11_set_ala_time_minutes ( rtc11_t *ctx, uint8_t minutes ) {
    uint8_t temp = 0;

    minutes &= 0x7F;

    temp = dev_bin_to_bcd( minutes );

    rtc11_generic_write( ctx, RTC11_REG_ALA_MIN, &temp, 1 );
}

void rtc11_set_ala_time_hours ( rtc11_t *ctx, uint8_t hours ) {
    uint8_t temp = 0;

    hours &= 0x3F;

    temp = dev_bin_to_bcd( hours );

    rtc11_generic_write( ctx, RTC11_REG_ALA_HRS, &temp, 1 );
}

uint8_t rtc11_get_ala_time_hundredths ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_HDT, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_ala_time_seconds ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_SEC, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_ala_time_minutes ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_MIN, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_ala_time_hours ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_HRS, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

uint8_t rtc11_get_ala_date_day ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_DAT, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

void rtc11_set_ala_date_day ( rtc11_t *ctx, uint8_t date_day ) {
    uint8_t temp = 0;

    date_day &= 0x3F;

    temp = dev_bin_to_bcd( date_day );

    rtc11_generic_write( ctx, RTC11_REG_ALA_DAT, &temp, 1 );
}

uint8_t rtc11_get_ala_date_month ( rtc11_t *ctx ) {
    uint8_t result = 0;
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_MON, &temp, 1 );

    result = dev_bcd_to_bin( temp );

    return result;
}

void rtc11_set_ala_date_month ( rtc11_t *ctx, uint8_t date_mth ) {
    uint8_t temp = 0;

    date_mth &= 0x1F;

    temp = dev_bin_to_bcd( date_mth );

    rtc11_generic_write( ctx, RTC11_REG_ALA_MON, &temp, 1 );
}

uint8_t rtc11_get_ala_day_of_the_week ( rtc11_t *ctx ) {
    uint8_t temp = 0;

    rtc11_generic_read( ctx, RTC11_REG_ALA_WKD, &temp, 1 );

    return temp;
}

void rtc11_set_ala_day_of_the_week ( rtc11_t *ctx, uint8_t w_day ) {
    w_day &= 0x07;

    rtc11_generic_write( ctx, RTC11_REG_ALA_WKD, &w_day, 1 );
}

void rtc11_soft_rst ( rtc11_t *ctx ) {
    uint8_t temp = 0;
    temp = RTC11_SW_RST;
    rtc11_generic_write( ctx, RTC11_REG_CFG_KEY, &temp, 1 );
}

err_t rtc11_set_time ( rtc11_t *ctx, rtc11_time_t rtc_time ) {
    err_t error_flag;
    if ( ( rtc_time.sec > MAX_MIN_SEC ) || ( rtc_time.min > MAX_MIN_SEC ) || ( rtc_time.hours > MAX_HOUR ) ) {
        error_flag = RTC11_ERROR;
    } else {
        rtc11_write_rtc( ctx, 1 );
        rtc11_set_time_hours( ctx, rtc_time.hours );
        rtc11_set_time_minutes( ctx, rtc_time.min );
        rtc11_set_time_seconds( ctx, rtc_time.sec );
        rtc11_write_rtc( ctx, 0 );
    }
    return error_flag;
}

void rtc11_get_time ( rtc11_t *ctx, rtc11_time_t *rtc_time ) {
    rtc_time->hours = rtc11_get_time_hours( ctx );
    rtc_time->min = rtc11_get_time_minutes( ctx );
    rtc_time->sec = rtc11_get_time_seconds( ctx );
}

err_t rtc11_set_date ( rtc11_t *ctx, rtc11_date_t rtc_date ) {
    uint8_t num_day;
    err_t error_flag;
    uint8_t tx_buf[ 1 ];
    
    error_flag = RTC11_ERROR;
    
    switch ( rtc_date.month ) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
            num_day = 31;
            break;
        }
        case 4: case 6: case 9: case 11: {
            num_day = 30;
            break;
        }
        case 2: {
            num_day = 28;
            break;
        }
    }
    
    if ( ( rtc_date.year % 4 == 0 ) && ( num_day == 28 ) ) {
        num_day = 29; 
    }
    
    if ( ( rtc_date.day < 1 )       || 
         ( num_day < rtc_date.day ) || 
         ( rtc_date.month < 1 )     || 
         ( rtc_date.month > 12 ) ) {
        error_flag = RTC11_OK;    
    } else {
        rtc11_write_rtc( ctx, 1 );
        rtc11_set_day_of_the_week( ctx, rtc_date.day_of_week );
        rtc11_set_date_day( ctx, rtc_date.day );
        rtc11_set_date_month( ctx, rtc_date.month );
        rtc11_set_date_year( ctx, rtc_date.year );
        rtc11_write_rtc( ctx, 0 );
    }
    
    return error_flag; 
}

void rtc11_get_date ( rtc11_t *ctx, rtc11_date_t *rtc_date ) {
    rtc_date->day_of_week = rtc11_get_day_of_the_week( ctx );
    rtc_date->day = rtc11_get_date_day( ctx );
    rtc_date->month = rtc11_get_date_month( ctx );
    rtc_date->year = rtc11_get_date_year( ctx );
}

void rtc11_stp_sys_slk ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_CTL1, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_CTL1_STOP;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_CTL1_STOP;
    }

    rtc11_generic_write( ctx, RTC11_REG_CTL1, &aux_reg_val, 1 );
}

void rtc11_auto_rst ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_CTL1, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_CTL1_ARST;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_CTL1_ARST;
    }

    rtc11_generic_write( ctx, RTC11_REG_CTL1, &aux_reg_val, 1 );
}

void rtc11_write_rtc ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_CTL1, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_CTL1_WRTC;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_CTL1_WRTC;
    }

    rtc11_generic_write( ctx, RTC11_REG_CTL1, &aux_reg_val, 1 );
}

void rtc11_cen_en ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_CEB;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_CEB;
    }

    rtc11_generic_write( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );
}

void rtc11_bat_low_int_en ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_BLIE;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_BLIE;
    }

    rtc11_generic_write( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );
}

void rtc11_timer_int_en ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_TIE;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_TIE;
    }

    rtc11_generic_write( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );
}

void rtc11_alarm_int_en ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_AIE;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_AIE;
    }

    rtc11_generic_write( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );
}

void rtc11_xt2_int_en ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_EX2E;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_EX2E;
    }

    rtc11_generic_write( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );
}

void rtc11_xt1_int_en ( rtc11_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val = 0;

    rtc11_generic_read( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= ~RTC11_EX1E;
    } else if ( state == 1 ) {
        aux_reg_val |= RTC11_EX1E;
    }

    rtc11_generic_write( ctx, RTC11_REG_INT_MSK, &aux_reg_val, 1 );
}

void rtc11_bat_mode_en ( rtc11_t *ctx,uint8_t state ) {
    uint8_t aux_reg_val = 0;
    uint8_t cfg_key = RTC11_ACS_AN_CTL_REG;

    rtc11_generic_write( ctx, RTC11_REG_CFG_KEY, &cfg_key, 1 );

    rtc11_generic_read( ctx, RTC11_REG_BAT_MODE, &aux_reg_val, 1 );

    if ( state == 0 ) {
        aux_reg_val &= 0x00;
    } else if ( state == 1 ) {
        aux_reg_val |= 0x80;
    }

    rtc11_generic_write( ctx, RTC11_REG_BAT_MODE, &aux_reg_val, 1 );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static uint8_t dev_bcd_to_bin ( uint8_t value ) {
    return ( value & 0x0F ) + ( ( value >> 4 ) * 10 );
}

static uint8_t dev_bin_to_bcd ( uint8_t value ) {
    return ( ( value / 10 ) << 4 ) + value % 10;
}

// ------------------------------------------------------------------------- END

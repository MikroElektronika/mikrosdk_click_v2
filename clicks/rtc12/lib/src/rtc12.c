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
 * @file rtc12.c
 * @brief RTC 12 Click Driver.
 */

#include "rtc12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

#define BIT_MASK_LSN               0x0F
#define BIT_MASK_BIT_0             0x01
#define BIT_MASK_TIME_REV_BIT      0x7F
#define BIT_MASK_ALARM_0           0xFE
#define BIT_MASK_ALARM_1           0xFD
#define BIT_MASK_ALARMS_ENABLE     0x04

#define SPI_WRITE                  0x80

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

/**
 * @brief Max day value.
 * @details Maximum day value.
 */
#define MAX_DAY                      31

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Decimal to RTC.
 * @details Decimal to RTC converter function.
 */
static uint8_t dev_dec_to_rtc ( uint8_t dec );

/**
 * @brief RTC to decimal.
 * @details RTC to decimal converter function.
 */
static uint8_t dev_rtc_to_dec ( uint8_t bcd );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc12_cfg_setup ( rtc12_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pf   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
}

err_t rtc12_init ( rtc12_t *ctx, rtc12_cfg_t *cfg ) {
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
    
    digital_in_init( &ctx->pf, cfg->pf );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t rtc12_default_cfg ( rtc12_t *ctx ) {
    rtc12_control_t rtc_ctrl;
    
    rtc_ctrl.eosc = RTC12_SET_EOSC_DISABLE;
    rtc_ctrl.dosf = RTC12_SET_DOSF_ENABLE;
    rtc_ctrl.egfil = RTC12_SET_EGFIL_DISABLE;
    rtc_ctrl.sqw = RTC12_SET_SQW_DISABLE;
    rtc_ctrl.intcn = RTC12_SET_INTCN_A0IE;
    rtc_ctrl.a1ie = RTC12_SET_ALARM_1_DISABLE;
    rtc_ctrl.a0ie = RTC12_SET_ALARM_0_DISABLE;
    rtc12_set_ctrl_reg( ctx, rtc_ctrl );
    
    return RTC12_OK;
}

err_t rtc12_generic_write ( rtc12_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= SPI_WRITE;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t rtc12_generic_read ( rtc12_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t rtc12_set_ctrl_reg ( rtc12_t *ctx, rtc12_control_t rtc_ctrl ) {
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ]  = ( rtc_ctrl.eosc  & BIT_MASK_BIT_0 ) << 7; 
    tx_buf[ 0 ] |= ( rtc_ctrl.dosf  & BIT_MASK_BIT_0 ) << 5;
    tx_buf[ 0 ] |= ( rtc_ctrl.egfil & BIT_MASK_BIT_0 ) << 4;
    tx_buf[ 0 ] |= ( rtc_ctrl.sqw   & BIT_MASK_BIT_0 ) << 3;
    tx_buf[ 0 ] |= ( rtc_ctrl.intcn & BIT_MASK_BIT_0 ) << 2;
    tx_buf[ 0 ] |= ( rtc_ctrl.a1ie  & BIT_MASK_BIT_0 ) << 1;
    tx_buf[ 0 ] |=   rtc_ctrl.a0ie  & BIT_MASK_BIT_0;
    err_t error_flag = rtc12_generic_write( ctx, RTC12_REG_CONTROL, tx_buf, 1 );
    
    return error_flag;
}

err_t rtc12_get_ctrl_reg ( rtc12_t *ctx, rtc12_control_t *rtc_ctrl ) {
    uint8_t rx_buf[ 1 ];
    
    err_t error_flag = rtc12_generic_read( ctx, RTC12_REG_CONTROL, rx_buf, 1 );
    
    rtc_ctrl->eosc  = ( rx_buf[ 0 ] >> 7 ) & BIT_MASK_BIT_0; 
    rtc_ctrl->dosf  = ( rx_buf[ 0 ] >> 5 ) & BIT_MASK_BIT_0;
    rtc_ctrl->egfil = ( rx_buf[ 0 ] >> 4 ) & BIT_MASK_BIT_0;
    rtc_ctrl->sqw   = ( rx_buf[ 0 ] >> 3 ) & BIT_MASK_BIT_0;
    rtc_ctrl->intcn = ( rx_buf[ 0 ] >> 2 ) & BIT_MASK_BIT_0;
    rtc_ctrl->a1ie  = ( rx_buf[ 0 ] >> 1 ) & BIT_MASK_BIT_0;
    rtc_ctrl->a0ie  =   rx_buf[ 0 ]& BIT_MASK_BIT_0;
    
    return error_flag;
}

err_t rtc12_get_time ( rtc12_t *ctx, rtc12_time_t *rtc_time ) {
    uint8_t rx_data;

    err_t error_flag = rtc12_generic_read( ctx, RTC12_REG_SECONDS, &rx_data, 1 );
    rtc_time->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_MINUTES, &rx_data, 1 );
    rtc_time->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_HOUR, &rx_data, 1 );
    rtc_time->hours = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc12_set_time ( rtc12_t *ctx, rtc12_time_t rtc_time ) {
    uint8_t tx_buf[ 1 ];
    err_t error_flag;
    
    if ( ( rtc_time.sec > MAX_MIN_SEC ) || 
         ( rtc_time.min > MAX_MIN_SEC ) || 
         ( rtc_time.hours > MAX_HOUR ) ) {
        error_flag = RTC12_ERROR;
    } else {
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.sec ); 
        error_flag = rtc12_generic_write( ctx, RTC12_REG_SECONDS, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.min ); 
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_MINUTES, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.hours ); 
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_HOUR, tx_buf, 1 );
    }
    
    return error_flag;
}

err_t rtc12_get_date ( rtc12_t *ctx, rtc12_date_t *rtc_date ) {
    uint8_t rx_data;

    err_t error_flag = rtc12_generic_read( ctx, RTC12_REG_DAY, &rx_data, 1 );
    rtc_date->day_of_week = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_DATE, &rx_data, 1 );
    rtc_date->day = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_MONTH, &rx_data, 1 );
    rtc_date->month = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_YEAR, &rx_data, 1 );
    rtc_date->year = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc12_set_date ( rtc12_t *ctx, rtc12_date_t rtc_date ) {
    uint8_t num_day;
    err_t error_flag;
    uint8_t tx_buf[ 1 ];
    
    error_flag = RTC12_ERROR;
    
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
        error_flag = RTC12_OK;    
    } else {
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.day_of_week ); 
        rtc12_generic_write( ctx, RTC12_REG_DAY, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.day ); 
        rtc12_generic_write( ctx, RTC12_REG_DATE, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.month );
        rtc12_generic_write( ctx, RTC12_REG_MONTH, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.year );
        rtc12_generic_write( ctx, RTC12_REG_YEAR, tx_buf, 1 );
    }
    
    return error_flag; 
}

err_t rtc12_get_alarm_0 ( rtc12_t *ctx, rtc12_alarm_t *rtc_alarm ) {
    uint8_t rx_data;

    err_t error_flag = rtc12_generic_read( ctx, RTC12_REG_ALARM_0_SECONDS, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_ALARM_0_MINUTES, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_ALARM_0_HOUR, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->hours = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_ALARM_0_DAY, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->day = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc12_set_alarm_0 ( rtc12_t *ctx, rtc12_alarm_t rtc_alarm ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_data;
    err_t error_flag;
    
    error_flag = RTC12_OK;
    
    if ( ( rtc_alarm.sec > MAX_MIN_SEC ) || 
         ( rtc_alarm.min > MAX_MIN_SEC ) || 
         ( rtc_alarm.hours > MAX_HOUR )  ||
         ( rtc_alarm.day > MAX_DAY ) ) {
        error_flag = RTC12_ERROR;
    } else {
        error_flag = rtc12_generic_read( ctx, RTC12_REG_CONTROL, &rx_data, 1 );
        rx_data &= BIT_MASK_ALARM_0;
        rx_data |= BIT_MASK_ALARMS_ENABLE;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_CONTROL, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.sec );
        tx_buf[ 0 ] |= rtc_alarm.alarm_rate & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_0_SECONDS, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.min );
        tx_buf[ 0 ] |= ( rtc_alarm.alarm_rate >> 1 ) & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_0_MINUTES, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.hours );
        tx_buf[ 0 ] |= ( rtc_alarm.alarm_rate >> 2 ) & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_0_HOUR, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.day );
        tx_buf[ 0 ] |= ( rtc_alarm.alarm_rate >> 2 ) & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_0_DAY, tx_buf, 1 );
    }
    
    return error_flag;
}

err_t rtc12_get_alarm_1 ( rtc12_t *ctx, rtc12_alarm_t *rtc_alarm ) {
    uint8_t rx_data;

    err_t error_flag = rtc12_generic_read( ctx, RTC12_REG_ALARM_1_SECONDS, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_ALARM_1_MINUTES, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_ALARM_1_HOUR, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->hours = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc12_generic_read( ctx, RTC12_REG_ALARM_1_DAY, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->day = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc12_set_alarm_1 ( rtc12_t *ctx, rtc12_alarm_t rtc_alarm ) {
    uint8_t rx_data;
    uint8_t tx_buf[ 1 ];
    err_t error_flag;
    
    if ( ( rtc_alarm.sec > MAX_MIN_SEC ) || 
         ( rtc_alarm.min > MAX_MIN_SEC ) || 
         ( rtc_alarm.hours > MAX_HOUR )  ||
         ( rtc_alarm.day > MAX_DAY ) ) {
        error_flag = RTC12_ERROR;
    } else {
        error_flag = rtc12_generic_read( ctx, RTC12_REG_CONTROL, &rx_data, 1 );
        rx_data &= BIT_MASK_ALARM_1;
        rx_data |= BIT_MASK_ALARMS_ENABLE;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_CONTROL, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.sec );
        tx_buf[ 0 ] |= rtc_alarm.alarm_rate & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_1_SECONDS, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.min );
        tx_buf[ 0 ] |= ( rtc_alarm.alarm_rate >> 1 ) & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_1_MINUTES, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.hours );
        tx_buf[ 0 ] |= ( rtc_alarm.alarm_rate >> 2 ) & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_1_HOUR, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.day );
        tx_buf[ 0 ] |= ( rtc_alarm.alarm_rate >> 2 ) & BIT_MASK_BIT_0;
        error_flag |= rtc12_generic_write( ctx, RTC12_REG_ALARM_1_DAY, tx_buf, 1 );
    }
    
    return error_flag;
}

uint8_t rtc12_check_int ( rtc12_t *ctx ) {   
    return digital_in_read( &ctx->int_pin );
}

uint8_t rtc12_check_power_fail ( rtc12_t *ctx ) {   
    return digital_in_read( &ctx->pf );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_dec_to_rtc ( uint8_t dec ) {
    return ( ( dec / 10 ) << 4 ) + ( dec % 10 );
}

static uint8_t dev_rtc_to_dec ( uint8_t bcd ) {
    return ( bcd & BIT_MASK_LSN ) + ( ( bcd >> 4 ) * 10 );
}

// ------------------------------------------------------------------------- END

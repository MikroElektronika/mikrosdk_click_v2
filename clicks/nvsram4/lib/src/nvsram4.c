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
 * @file nvsram4.c
 * @brief nvSRAM 4 Click Driver.
 */

#include "nvsram4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                    0x00

/**
 * @brief LSN data.
 * @details Least significant nibble data.
 */
#define BIT_MASK_LSN             0x0F

/**
 * @brief Write enable data.
 * @details RTC write enable data.
 */
#define RTC_WRITE_ENABLE         0x1A

/**
 * @brief Write disable data.
 * @details RTC write disable data.
 */
#define RTC_WRITE_DISABLE        0x18

/**
 * @brief Write enable data.
 * @details Status write enable data.
 */
#define STATUS_WRITE_ENABLE      0x02

/**
 * @brief Last memory address.
 * @details Last memory address value.
 */
#define LAST_MEMORY_ADDRESS      0x0001FFFF

/**
 * @brief Max min. & sec.
 * @details Maximum value of minutes and seconds.
 */
#define MAX_MIN_SEC              59

/**
 * @brief Max hour value.
 * @details Maximum hour value.
 */
#define MAX_HOUR                 23

/**
 * @brief Max day value.
 * @details Maximum day value.
 */
#define MAX_DAY                  31

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

/**
 * @brief Configuration delay.
 * @details Configuration delay for 1 milliseconds.
 */
static void dev_config_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nvsram4_cfg_setup ( nvsram4_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hld   = HAL_PIN_NC;
    cfg->hsb = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t nvsram4_init ( nvsram4_t *ctx, nvsram4_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_init( &ctx->hsb, cfg->hsb );
    digital_out_init( &ctx->wp, cfg->wp );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

void nvsram4_default_cfg ( nvsram4_t *ctx ) {
    
    // Disable Hold
    
    nvsram4_hold( ctx, NVSRAM4_HOLD_DISABLE );
    
    // Disable Hardware Store
    
    nvsram4_hardware_store( ctx, NVSRAM4_HSB_DISABLE );
    
    // Disable Hardware Write Protection
    
    nvsram4_hw_write_protection( ctx, NVSRAM4_WP_DISABLE );
}

err_t nvsram4_generic_write ( nvsram4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nvsram4_generic_read ( nvsram4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nvsram4_set_cmd ( nvsram4_t *ctx, uint8_t cmd ) {

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

uint8_t nvsram4_read_status ( nvsram4_t *ctx ) {
    uint8_t rx_buf[ 1 ];

    nvsram4_generic_read( ctx, NVSRAM4_STATUS_RDSR, rx_buf, 1 );
    
    return rx_buf[ 0 ];
}

void nvsram4_write_status ( nvsram4_t *ctx, uint8_t st_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = NVSRAM4_STATUS_WRSR;
    tx_buf[ 1 ] = st_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

err_t nvsram4_burst_read_memory ( nvsram4_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t n_bytes ) {
    uint8_t tx_buf[ 4 ];
    err_t status;
    
    status = NVSRAM4_SUCCESS;
    
    if ( n_bytes != 0 ) {
        mem_addr &= LAST_MEMORY_ADDRESS;

        tx_buf[ 0 ] = NVSRAM4_SRAM_READ;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;
        
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, 4 );
        spi_master_read( &ctx->spi, data_out, n_bytes );
        spi_master_deselect_device( ctx->chip_select );
    } else {
        status = NVSRAM4_ERROR;    
    }
    
    return status;
}

err_t nvsram4_burst_write_memory ( nvsram4_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t n_bytes ) {
    uint8_t tx_buf[ 260 ];
    uint16_t cnt;
    uint16_t len;
    err_t status;
    
    status = NVSRAM4_SUCCESS;
    
    len = n_bytes + 4;

    if ( n_bytes != 0 ) {
        tx_buf[ 0 ] = NVSRAM4_SRAM_WRITE;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;

        for ( cnt = 0; cnt < n_bytes; cnt++ )
        {
            tx_buf[ cnt + 4 ] = data_in[ cnt ];
        }

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, len );
        spi_master_deselect_device( ctx->chip_select );
    } else {
        status = NVSRAM4_ERROR;    
    }
    
    return status;
}

uint32_t nvsram4_read_id ( nvsram4_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 4 ];
    uint32_t result;

    tx_buf[ 0 ] = NVSRAM4_SPEC_RDID;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_read( &ctx->spi, rx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 2 ];
    result <<= 8;
    result |= rx_buf[ 3 ];

    return result;
}

uint8_t nvsram4_rtc_read_reg ( nvsram4_t *ctx, uint8_t rtc_reg ) {
   uint8_t tx_buf[ 2 ];
   uint8_t rx_buf[ 1 ];
    
   tx_buf[ 0 ] = NVSRAM4_SRAM_RDRTC;
   tx_buf[ 1 ] = rtc_reg;
   tx_buf[ 1 ] &= BIT_MASK_LSN;
   
   spi_master_select_device( ctx->chip_select );
   spi_master_write( &ctx->spi, tx_buf, 2 );
   spi_master_read( &ctx->spi, rx_buf, 1 );
   spi_master_deselect_device( ctx->chip_select );
   
   return rx_buf[ 0 ];
}

void nvsram4_rtc_write_reg ( nvsram4_t *ctx, uint8_t rtc_reg, uint8_t data_in ) {
   uint8_t tx_buf[ 3 ];
    
   tx_buf[ 0 ] = NVSRAM4_SRAM_WRTC;
   tx_buf[ 1 ] = rtc_reg;
   tx_buf[ 1 ] &= BIT_MASK_LSN;
   tx_buf[ 2 ] = data_in;
   
   spi_master_select_device( ctx->chip_select );
   spi_master_write( &ctx->spi, tx_buf, 3 );
   spi_master_deselect_device( ctx->chip_select );
}

void nvsram4_enable_rtc_write ( nvsram4_t *ctx ) {
    nvsram4_set_cmd( ctx, NVSRAM4_STATUS_WREN );
    dev_config_delay( );
    nvsram4_write_status( ctx, STATUS_WRITE_ENABLE );
    dev_config_delay( );
    nvsram4_set_cmd( ctx, NVSRAM4_STATUS_WREN );
    dev_config_delay( );
    nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_FLAGS, RTC_WRITE_ENABLE );
    dev_config_delay( );
    nvsram4_set_cmd( ctx, NVSRAM4_STATUS_WREN );
    dev_config_delay( );
}

void nvsram4_disable_rtc_write ( nvsram4_t *ctx ) {
    nvsram4_set_cmd( ctx, NVSRAM4_STATUS_WREN );
    dev_config_delay( );
    nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_FLAGS, RTC_WRITE_DISABLE );
    dev_config_delay( );
}

void nvsram4_get_rtc_time ( nvsram4_t *ctx, nvsram4_rtc_time_t *rtc_time ) {
    uint8_t rx_data;

    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_SECONDS );
    rtc_time->sec = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_MINUTES );
    rtc_time->min = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_HOURS );
    rtc_time->hours = dev_rtc_to_dec( rx_data );
}

err_t nvsram4_set_rtc_time ( nvsram4_t *ctx, nvsram4_rtc_time_t rtc_time ) {
    err_t status;
    
    status = NVSRAM4_SUCCESS;
    
    if ( ( rtc_time.sec > MAX_MIN_SEC ) || 
         ( rtc_time.min > MAX_MIN_SEC ) || 
         ( rtc_time.hours > MAX_HOUR ) ) {
        status = NVSRAM4_ERROR;
    } else {
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_SECONDS, dev_dec_to_rtc( rtc_time.sec ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_MINUTES, dev_dec_to_rtc( rtc_time.min ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_HOURS, dev_dec_to_rtc( rtc_time.hours ) );
        nvsram4_disable_rtc_write ( ctx );    
    }
    
    return status;
}

void nvsram4_get_rtc_date ( nvsram4_t *ctx, nvsram4_rtc_date_t *rtc_date ) {
    uint8_t rx_data;

    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_DAY );
    rtc_date->day_of_week = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_DATE );
    rtc_date->day = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_MONTHS );
    rtc_date->month = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_TK_YEARS );
    rtc_date->year = dev_rtc_to_dec( rx_data );
}

err_t nvsram4_set_rtc_date ( nvsram4_t *ctx, nvsram4_rtc_date_t rtc_date ) {
    uint8_t num_day;
    err_t status;
    
    status = NVSRAM4_SUCCESS;
    
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
        status = NVSRAM4_ERROR;    
    } else {
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_DAY, dev_dec_to_rtc( rtc_date.day_of_week ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_DATE, dev_dec_to_rtc( rtc_date.day ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_MONTHS, dev_dec_to_rtc( rtc_date.month ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_TK_YEARS, dev_dec_to_rtc( rtc_date.year ) );
        nvsram4_disable_rtc_write ( ctx );
    }
    
    return status; 
}

void nvsram4_get_rtc_alarm ( nvsram4_t *ctx, nvsram4_rtc_alarm_t *rtc_alarm ) {
    uint8_t rx_data;

    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_ALARM_SECONDS );
    rtc_alarm->sec = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_ALARM_MINUTES );
    rtc_alarm->min = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_ALARM_HOURS );
    rtc_alarm->hours = dev_rtc_to_dec( rx_data );
    
    rx_data = nvsram4_rtc_read_reg( ctx, NVSRAM4_RTC_ALARM_DAY );
    rtc_alarm->day = dev_rtc_to_dec( rx_data );
}

err_t nvsram4_set_rtc_alarm ( nvsram4_t *ctx, nvsram4_rtc_alarm_t rtc_alarm ) {
    err_t status;
    
    status = NVSRAM4_SUCCESS;
    
    if ( ( rtc_alarm.sec > MAX_MIN_SEC ) || 
         ( rtc_alarm.min > MAX_MIN_SEC ) || 
         ( rtc_alarm.hours > MAX_HOUR )  ||
         ( rtc_alarm.day > MAX_DAY ) ) {
        status = NVSRAM4_ERROR;
    } else {
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_ALARM_SECONDS, dev_dec_to_rtc( rtc_alarm.sec ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_ALARM_MINUTES, dev_dec_to_rtc( rtc_alarm.min ) );
        nvsram4_disable_rtc_write ( ctx );
    
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_ALARM_HOURS, dev_dec_to_rtc( rtc_alarm.hours ) );
        nvsram4_disable_rtc_write ( ctx );
        
        nvsram4_enable_rtc_write ( ctx );
        nvsram4_rtc_write_reg( ctx, NVSRAM4_RTC_ALARM_DAY, dev_dec_to_rtc( rtc_alarm.day ) );
        nvsram4_disable_rtc_write ( ctx );
    }
    
    return status;
}

err_t nvsram4_hold ( nvsram4_t *ctx, uint8_t en_hold ) {
    err_t status;

    status = NVSRAM4_SUCCESS;
    
    if ( en_hold == NVSRAM4_HOLD_ENABLE ) {
        digital_out_low( &ctx->hld );
        
    } else if ( en_hold == NVSRAM4_HOLD_DISABLE) {
        digital_out_high( &ctx->hld );
    } else {
        status = NVSRAM4_ERROR;    
    }
    
    return status;
}

err_t nvsram4_hardware_store ( nvsram4_t *ctx, uint8_t en_hw_store ) {
    err_t status;

    status = NVSRAM4_SUCCESS;
    
    if ( en_hw_store == NVSRAM4_HSB_ENABLE ) {
        digital_out_low( &ctx->hsb );
        
    } else if ( en_hw_store == NVSRAM4_HSB_DISABLE) {
        digital_out_high( &ctx->hsb );
    } else {
        status = NVSRAM4_ERROR;    
    }
    
    return status;
}

err_t nvsram4_hw_write_protection ( nvsram4_t *ctx, uint8_t en_wp ) {
    err_t status;

    status = NVSRAM4_SUCCESS;
    
    if ( en_wp == NVSRAM4_WP_ENABLE ) {
        digital_out_low( &ctx->wp );
        
    } else if ( en_wp == NVSRAM4_WP_DISABLE) {
        digital_out_high( &ctx->wp );
    } else {
        status = NVSRAM4_ERROR;    
    }
    
    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_dec_to_rtc ( uint8_t dec ) {
    return ( ( dec / 10 ) << 4 ) + ( dec % 10 );
}

static uint8_t dev_rtc_to_dec ( uint8_t bcd ) {
    return ( bcd & BIT_MASK_LSN ) + ( ( bcd >> 4 ) * 10 );
}

static void dev_config_delay ( void ) {
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END

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

#include "rtc5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RTC5_DUMMY              0
#define RTC5_CLEAR              0x00
#define RTC5_CLEAR_VALUE        0x00
#define RTC5_END_OF_SRAM_REG    0x20

// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void dev_write_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc5_cfg_setup ( rtc5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mfp = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

RTC5_RETVAL rtc5_init ( rtc5_t *ctx, rtc5_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = RTC5_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return RTC5_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, RTC5_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );   

    // Input pins

    digital_in_init( &ctx->mfp, cfg->mfp );

    return RTC5_OK;
}

void rtc5_default_cfg ( rtc5_t *ctx )
{
    // Click default configuration
    rtc5_timedate_t timedate_data;
    
    
    // Set time and date
   
    // Time  00:00:00
    
    timedate_data.hun_of_sec = 0;
    timedate_data.sec = 0;
    timedate_data.min = 0;
    timedate_data.hours = 0;
    
    // Date  01.01.2000.
    
    timedate_data.day = 1;
    timedate_data.month = 1;
    timedate_data.year = 0;
    
    // W Day Saturday
    
    timedate_data.w_day = RTC5_DAY_OF_THE_WEEK_SATURDAY;
    
}

void rtc5_generic_transfer 
( 
    rtc5_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void rtc5_generic_write ( rtc5_t *ctx, uint8_t reg, uint8_t tx_data )
{    
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf;
    
    tx_buf[ 0 ] = RTC5_SPI_WRITE;
    tx_buf[ 1 ] = reg;
    tx_buf[ 2 ] = tx_data;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t rtc5_generic_read ( rtc5_t *ctx, uint8_t reg )
{    
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 1 ];
    
    tx_buf[ 0 ] = RTC5_SPI_READ;
    tx_buf[ 1 ] = reg;

    rtc5_generic_transfer ( ctx, tx_buf, 2, rx_buf, 1 );
    
    return rx_buf[ 0 ];
}

void rtc5_set_counting ( rtc5_t *ctx, uint8_t en_osc )
{
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_SEC );

    if ( en_osc == RTC5_OSC_ENABLE )
    {
        temp |= RTC5_COUNTING_ENABLE;
    }
    
    if ( en_osc == RTC5_OSC_DISABLE )
    {
        temp &= RTC5_COUNTING_DISABLE;
    }

    rtc5_generic_write( ctx, RTC5_REG_TIME_SEC, temp );
}

void rtc5_clear ( rtc5_t *ctx )
{
    uint8_t reg_add;
    uint8_t clr_data[ 1 ];
    uint8_t rx_buf;
    
    clr_data[ 0 ] = RTC5_CLR_CMD;
    
    for( reg_add = 0; reg_add < RTC5_END_OF_SRAM_REG; reg_add++ )
    {
        rtc5_generic_write( ctx, reg_add, RTC5_CLEAR );
        dev_write_delay( );
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, clr_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void rtc5_set_time_hun_of_sec ( rtc5_t *ctx, uint8_t hun_sec )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    hun_sec %= 100;

    ones = hun_sec % 10;

    tens = ( hun_sec / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_HUN_OF_SEC, temp );
}

uint8_t rtc5_get_time_hun_of_sec ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_HUN_OF_SEC );

    ones = temp & 0x0F;

    tens = temp >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc5_set_time_sec ( rtc5_t *ctx, uint8_t seconds )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    seconds %= 60;

    ones = seconds % 10;

    tens = ( seconds / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_SEC, temp );
}

uint8_t rtc5_get_time_sec ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_SEC );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc5_set_time_min ( rtc5_t *ctx, uint8_t minutes )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    minutes %= 60;

    ones = minutes % 10;

    tens = ( minutes / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_MIN, temp );
}

uint8_t rtc5_get_time_min ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_MIN );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc5_set_time_hours ( rtc5_t *ctx, uint8_t hours )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    hours %= 24;

    ones = hours % 10;

    tens = ( hours / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_HOUR, temp );
}

uint8_t rtc5_get_time_hours ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_HOUR );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc5_set_day_of_the_week ( rtc5_t *ctx, uint8_t w_day )
{
    w_day %= 8;

    if ( w_day == 0 )
    {
        w_day = 1;
    }
    
    rtc5_generic_write( ctx, RTC5_REG_TIME_DAY_OF_THE_WEEK, w_day );
}

uint8_t rtc5_get_day_of_the_week ( rtc5_t *ctx )
{
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_DAY_OF_THE_WEEK );
    
    temp &= 0x07;

    return temp;
}

void rtc5_set_date_day ( rtc5_t *ctx, uint8_t date_day )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    date_day %= 32;

    if ( date_day == 0 )
    {
        date_day = 1;
    }

    ones = date_day % 10;

    tens = ( date_day / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_DATE_DAY, temp );
}

uint8_t rtc5_get_date_day ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_DATE_DAY );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc5_set_date_month ( rtc5_t *ctx, uint8_t date_month )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    date_month %= 13;

    if ( date_month == 0 )
    {
        date_month = 1;
    }

    ones = date_month % 10;

    tens = ( date_month / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_DATE_MONTH, temp );
}

uint8_t rtc5_get_date_month ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_DATE_MONTH );

    ones = temp & 0x0F;

    tens = ( temp & 0x10 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

uint8_t rtc5_get_leap_year ( rtc5_t *ctx )
{
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_DATE_MONTH );

    temp &= 0x20;
    temp >>= 5;

    return temp;
}

void rtc5_set_date_year ( rtc5_t *ctx, uint16_t date_year )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = RTC5_CLEAR_VALUE;
    tens = RTC5_CLEAR_VALUE;

    date_year %= 100;

    ones = date_year % 10;

    tens = ( date_year / 10 ) << 4;

    temp = tens | ones;

    rtc5_generic_write( ctx, RTC5_REG_TIME_DATE_YEAR, temp );
}

uint8_t rtc5_get_date_year ( rtc5_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc5_generic_read( ctx, RTC5_REG_TIME_DATE_YEAR );

    ones = temp & 0x0F;

    tens = ( temp & 0xF0 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc5_set_time ( rtc5_t *ctx, uint8_t time_hours, uint8_t time_min, uint8_t time_sec )
{
    rtc5_set_time_hours( ctx, time_hours );
    rtc5_set_time_min( ctx, time_min );
    rtc5_set_time_sec( ctx, time_sec );
}

void rtc5_set_date ( rtc5_t *ctx, uint8_t date_day, uint8_t date_month, uint16_t date_year )
{
    rtc5_set_date_day( ctx, date_day );
    rtc5_set_date_month( ctx, date_month );
    rtc5_set_date_year( ctx, date_year );
}

void rtc5_get_time_and_date ( rtc5_t *ctx, rtc5_timedate_t *timedate_data )
{
    timedate_data->hours = rtc5_get_time_hours( ctx );
    timedate_data->min = rtc5_get_time_min( ctx );
    timedate_data->sec = rtc5_get_time_sec( ctx );
    timedate_data->day = rtc5_get_date_day( ctx );
    timedate_data->month = rtc5_get_date_month( ctx );
    timedate_data->year = rtc5_get_date_year( ctx );
    timedate_data->w_day = rtc5_get_day_of_the_week( ctx );
}

uint8_t rtc5_get_interrupt ( rtc5_t *ctx )
{
    return digital_in_read( &ctx->mfp );
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_write_delay ( void )
{
    Delay_1us();   
}

// ------------------------------------------------------------------------- END


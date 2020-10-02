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

#include "shake2wake.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define SHAKE2WAKE_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void shake2wake_cfg_setup ( shake2wake_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

SHAKE2WAKE_RETVAL shake2wake_init ( shake2wake_t *ctx, shake2wake_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = SHAKE2WAKE_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return SHAKE2WAKE_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, SHAKE2WAKE_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SHAKE2WAKE_OK;
}

void shake2wake_default_cfg ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, 0x2D, 0x00 );

    shake2wake_write_byte( ctx, 0x2C, 0x13 );

    shake2wake_write_byte( ctx, 0x20, 0xFA );
    shake2wake_write_byte( ctx, 0x21, 0x00 );

    shake2wake_write_byte( ctx, 0x23, 0x96 );
    shake2wake_write_byte( ctx, 0x24, 0x00 );

    shake2wake_write_byte( ctx, 0x25, 0x1E );

    shake2wake_write_byte( ctx, 0x27, 0x3F );

    shake2wake_write_byte( ctx, 0x2B, 0x40 );

    shake2wake_write_byte( ctx, 0x2D, 0x0A );
}

void shake2wake_generic_transfer 
( 
    shake2wake_t *ctx, 
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

uint8_t shake2wake_read_byte ( shake2wake_t *ctx, uint8_t rd_addr )
{
    uint8_t rd_data;
    uint8_t wr_buff[ 2 ];
    
    wr_buff[ 0 ] = SHAKE2WAKE_READ_REG;
    wr_buff[ 1 ] = rd_addr;

    shake2wake_generic_transfer( ctx, wr_buff, 2, &rd_data, 1 );

    return rd_data;
}

void shake2wake_write_byte ( shake2wake_t *ctx, uint8_t wr_addr, uint8_t wr_val )
{
    uint8_t i;
    uint8_t wr_buff[ 3 ];
    
    wr_buff[ 0 ] = SHAKE2WAKE_WRITE_REG;
    wr_buff[ 1 ] = wr_addr;
    wr_buff[ 2 ] = wr_val;
    
    spi_master_select_device( ctx->chip_select );

    for ( i = 0; i < 3; i++ )
    {
        spi_master_write( &ctx->spi, &wr_buff[ i ], 1 );
    }

    spi_master_deselect_device( ctx->chip_select ); 
}

void shake2wake_write_two_byte ( shake2wake_t *ctx, uint8_t reg_addr, uint16_t reg_val, uint8_t cnt )
{
    uint8_t wr_buff[ 4 ] = { 0, 0, 0, 0 };
    
    wr_buff[ 0 ] = SHAKE2WAKE_WRITE_REG;
    wr_buff[ 1 ] = reg_addr;
    wr_buff[ 2 ] = ( reg_val & 0x00FF );
    wr_buff[ 3 ] = ( reg_val >> 8 );

    shake2wake_generic_transfer( ctx, wr_buff, cnt + 2, 0, 0 );
}

void shake2wake_read_multiple_byte ( shake2wake_t *ctx, uint8_t reg_addr, uint8_t *prd_data, uint8_t cnt )
{
    uint8_t rd_buff[ 32 ];
    uint8_t wr_buff[ 2 ];
    uint8_t i;

    wr_buff[ 0 ] = SHAKE2WAKE_READ_REG;
    wr_buff[ 1 ] = reg_addr;
    i = 0;

    shake2wake_generic_transfer( ctx, wr_buff, 2, prd_data, cnt );
}

void shake2wake_fifo_read ( shake2wake_t *ctx, uint8_t *p_buff, uint16_t cnt )
{
    uint8_t rd_buff[ 512 ];
    uint8_t addr;
    uint16_t i = 0;

    addr = SHAKE2WAKE_READ_FIFO;
    
    shake2wake_generic_transfer( ctx, &addr, 1, rd_buff, cnt );

    for ( i = 0; i < cnt; i++ )
    {
        p_buff[ i ] = rd_buff[ i ];
    }
}

uint8_t shake2wake_read_dev_id_ad ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_DEVID_AD );
    return result;
}

uint8_t shake2wake_read_dev_id_mst ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_DEVID_MST );
    return result;
}

uint8_t shake2wake_read_part_id ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_DEVID_AD );
    return result;
}

uint8_t shake2wake_read_revision ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_REVID );
    return result;
}

void shake2wake_soft_reset ( shake2wake_t *ctx )
{
    shake2wake_write_byte(  ctx, SHAKE2WAKE_REG_SOFT_RESET, SHAKE2WAKE_RESET_KEY );
}

uint8_t shake2wake_read_status ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_STATUS );
    return result;
}

uint16_t shake2wake_read_fifo_ent ( shake2wake_t *ctx )
{
    uint8_t rd_buff[ 2 ];
    uint16_t result;
    
    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_FIFO_L, &rd_buff, 2 );
    
    result = rd_buff[ 1 ];
    result <<=8;
    result |= rd_buff[ 1 ];
    
    return result;
}

void shake2wake_get_lo_res_raw_data ( shake2wake_t *ctx, int8_t *x_val, int8_t *y_val, int8_t *z_val )
{
    *x_val = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_XDATA );
    *y_val = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_YDATA );
    *z_val = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_ZDATA );
}

void shake2wake_get_raw_data ( shake2wake_t *ctx, int16_t *x_val, int16_t *y_val, int16_t *z_val )
{
    uint8_t temp_val[ 6 ] = { 0, 0, 0, 0, 0, 0 };

    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_XDATA_L, temp_val, 6 );

    *x_val = ( ( uint16_t )temp_val[ 1 ] << 8 ) + temp_val[ 0 ];
    *y_val = ( ( uint16_t )temp_val[ 3 ] << 8 ) + temp_val[ 2 ];
    *z_val = ( ( uint16_t )temp_val[ 5 ] << 8 ) + temp_val[ 4 ];
}

float shake2wake_read_temperature ( shake2wake_t *ctx )
{
    uint8_t raw_data[ 2 ] = { 0, 0 };
    int16_t sig_temp = 0;
    float temp_cel = 0.0;

    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_TEMP_L, &raw_data, 2 );

    sig_temp = ( uint16_t )( raw_data[ 1 ] << 8 ) + raw_data[ 0 ];
    temp_cel = ( float )sig_temp * 0.065;

    return temp_cel;
}

void shake2wake_stand_by_mode ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_POWER_CTL, SHAKE2WAKE_POWER_CTL_MEASURE_STD_BY );
}

void shake2wake_measure_mode ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_POWER_CTL_MEASURE_MODE, SHAKE2WAKE_POWER_CTL_MEASURE_MODE );
}

void shake2wake_auto_sleep_mode ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_POWER_CTL, SHAKE2WAKE_POWER_CTL_AUTOSLEEP );
}

void shake2wake_wake_up ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_POWER_CTL, SHAKE2WAKE_POWER_CTL_WAKEUP );
}

void shake2wake_set_low_noise_mode ( shake2wake_t *ctx, uint8_t low_noise )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_POWER_CTL, low_noise );
}

void shake2wake_extern_clk ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_POWER_CTL, SHAKE2WAKE_POWER_CTL_EXT_CLK );
}

void shake2wake_set_range ( shake2wake_t *ctx, uint8_t range )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FILTER_CTL, range );
}

void shake2wake_sel_hal_bandw ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FILTER_CTL, SHAKE2WAKE_FILTER_CTL_HALF_BW );
}

void shake2wake_set_extern_samp_trigg ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FILTER_CTL, SHAKE2WAKE_FILTER_CTL_EXT_SAMPLE );
}

void shake2wake_set_output_data_rate ( shake2wake_t *ctx, uint8_t odr )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FILTER_CTL, odr );
}

void shake2wake_get_data_g ( shake2wake_t *ctx, float *x_val, float *y_val, float *z_val )
{
    uint8_t temp_val[ 6 ];
    uint8_t sel_range;


    sel_range = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_FILTER_CTL );
    sel_range &= 0XC0;
    sel_range >>= 6;

    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_XDATA_L, &temp_val, 6 );

    *x_val = ( ( uint16_t )temp_val[ 1 ] << 8 ) + temp_val[ 0 ];
    *y_val = ( ( uint16_t )temp_val[ 3 ] << 8 ) + temp_val[ 2 ];
    *z_val = ( ( uint16_t )temp_val[ 5 ] << 8 ) + temp_val[ 4 ];

    if ( sel_range == 0 )
    {
        *x_val /= 1000;
        *y_val /= 1000;
        *z_val /= 1000;
    }
    else if ( sel_range == 1 )
    {
        *x_val /= 500;
        *y_val /= 500;
        *z_val /= 500;
    }
    else
    {
        *x_val /= 250;
        *y_val /= 250;
        *z_val /= 250;
    }
}

void shake2wake_set_fifo_above_half ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FIFO_CTL, SHAKE2WAKE_FIFO_CTL_AH );
}

void shake2wake_store_temp ( shake2wake_t *ctx )
{
   shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FIFO_CTL, SHAKE2WAKE_FIFO_CTL_FIFO_TEMP );
}

void shake2wake_set_fifo_mode ( shake2wake_t *ctx, uint8_t mode )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FIFO_CTL, mode );
}

uint8_t shake2wake_read_filter_ctl ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_FILTER_CTL );
    return result;
}

uint8_t shake2wake_read_power_ctl ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_POWER_CTL );
    return result;
}

uint8_t shake2wake_read_fifo_ctl ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_FIFO_CTL );
    return result;
}

uint8_t shake2wake_read_act_inact_ctl ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_ACT_INACT_CTL );
    return result;
}

void shake2wake_set_activity_enable ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_ACT_INACT_CTL, SHAKE2WAKE_ACT_INACT_CTL_ACT_EN );
}

void shake2wake_set_referenced_activity ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_ACT_INACT_CTL, SHAKE2WAKE_ACT_INACT_CTL_ACT_REF );
}

void shake2wake_set_inactivity_enable ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_ACT_INACT_CTL, SHAKE2WAKE_ACT_INACT_CTL_INACT_EN );
}

void shake2wake_set_referenced_inactivity ( shake2wake_t *ctx )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_ACT_INACT_CTL, SHAKE2WAKE_ACT_INACT_CTL_INACT_REF );
}

void shake2wake_sel_link_loop_mode ( shake2wake_t *ctx, uint8_t mode )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_ACT_INACT_CTL, mode );
}

void shake2wake_set_act_trsh ( shake2wake_t *ctx, uint16_t act_trsh )
{
    shake2wake_write_two_byte( ctx, SHAKE2WAKE_REG_THRESH_ACT_L, act_trsh, 2 );
}

int16_t shake2wake_read_act_trsh ( shake2wake_t *ctx )
{
    uint8_t raw_data[ 2 ] = { 0, 0 };
    int16_t result = 0;

    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_THRESH_ACT_L, &raw_data, 2 );

        result = ( uint16_t )( raw_data[ 1 ] << 8 ) | raw_data[ 0 ];

    return result;
}

void shake2wake_set_act_time ( shake2wake_t *ctx, uint8_t ac_time )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_TIME_ACT, ac_time );
}

uint8_t shake2wake_read_act_time ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_TIME_ACT );
    return result;
}

void shake2wake_set_inact_trsh ( shake2wake_t *ctx, uint16_t inact_trsh )
{
    shake2wake_write_two_byte( ctx, SHAKE2WAKE_REG_THRESH_INACT_L, inact_trsh, 2 );
}

int16_t shake2wake_read_inact_trsh ( shake2wake_t *ctx )
{
    uint8_t raw_data[ 2 ] = { 0, 0 };
    int16_t result = 0;

    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_THRESH_INACT_L, &raw_data, 2 );

        result = ( uint16_t )( raw_data[ 1 ] << 8 ) | raw_data[ 0 ];

    return result;
}

void shake2wake_set_inact_time ( shake2wake_t *ctx, uint16_t inac_time )
{
    shake2wake_write_two_byte( ctx, SHAKE2WAKE_REG_TIME_INACT_L, inac_time, 2 );
}

uint16_t shake2wake_read_inact_time ( shake2wake_t *ctx )
{
    uint8_t raw_data[ 2 ] = { 0, 0 };
    int16_t result = 0;

    shake2wake_read_multiple_byte( ctx, SHAKE2WAKE_REG_TIME_INACT_L, &raw_data, 2 );

    result = ( uint16_t )( raw_data[ 1 ] << 8 ) | raw_data[ 0 ];

    return result;
}

void shake2wake_write_int_1_map ( shake2wake_t *ctx, uint8_t wr_data )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_INTMAP1, wr_data );
}

uint8_t shake2wake_read_int_1_map ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_INTMAP1 );
    return result;
}

void shake2wake_write_int_2_map ( shake2wake_t *ctx, uint8_t wr_data )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_INTMAP2, wr_data );
}

uint8_t shake2wake_read_int_2_map ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_INTMAP2 );
    return result;
}

void shake2wake_write_fifo_samp ( shake2wake_t *ctx, uint8_t samp )
{
    shake2wake_write_byte( ctx, SHAKE2WAKE_REG_FIFO_SAMPLES, samp );
}

uint8_t shake2wake_read_fifo_samp ( shake2wake_t *ctx )
{
    uint8_t result;
    result = shake2wake_read_byte( ctx, SHAKE2WAKE_REG_FIFO_SAMPLES );
    return result;
}

uint8_t shake2wake_check_int ( shake2wake_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END


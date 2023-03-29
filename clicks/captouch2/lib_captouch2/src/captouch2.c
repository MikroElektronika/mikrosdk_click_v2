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

#include "captouch2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CAPTOUCH2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void set_def_val_state ( captouch2_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void captouch2_cfg_setup ( captouch2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->alt = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

CAPTOUCH2_RETVAL captouch2_init ( captouch2_t *ctx, captouch2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CAPTOUCH2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CAPTOUCH2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CAPTOUCH2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );

    // Input pins

    digital_in_init( &ctx->alt, cfg->alt );
    set_def_val_state( ctx );

    return CAPTOUCH2_OK;
}

void captouch2_default_cfg ( captouch2_t *ctx )
{
    // Click default configuration

    captouch2_write_reg( ctx, CAPTOUCH2_LED_BEHAVIOR1_REG, CAPTOUCH2_LED1_PULSE2_BEHAVIOR |
                                                           CAPTOUCH2_LED2_PULSE2_BEHAVIOR |
                                                           CAPTOUCH2_LED3_PULSE2_BEHAVIOR |
                                                           CAPTOUCH2_LED4_DIRECT_BEHAVIOR );

    captouch2_write_reg( ctx, CAPTOUCH2_LED_BEHAVIOR2_REG, CAPTOUCH2_LED5_DIRECT_BEHAVIOR |
                                                           CAPTOUCH2_LED6_DIRECT_BEHAVIOR );

    captouch2_write_reg( ctx, CAPTOUCH2_LED_PULSE2_PERIOD_REG, 0x08 );
    captouch2_write_reg( ctx, CAPTOUCH2_LED_CONFIG_REG, CAPTOUCH2_PULSE2_1_PULSE );
    captouch2_write_reg( ctx, CAPTOUCH2_LED_PULSE2_DUTY_REG, CAPTOUCH2_MIN_DUTY_0_PERCENT |
                                                             CAPTOUCH2_MAX_DUTY_100_PERCENTS );

    captouch2_write_reg( ctx, CAPTOUCH2_LED_DIRECT_DUTY_REG, CAPTOUCH2_MIN_DUTY_0_PERCENT |
                                                             CAPTOUCH2_MAX_DUTY_40_PERCENTS );

    captouch2_write_reg( ctx, CAPTOUCH2_REPEAT_RATE_EN_REG, CAPTOUCH2_INPUT4_REPEAT_RATE_EN |
                                                            CAPTOUCH2_INPUT5_REPEAT_RATE_EN |
                                                            CAPTOUCH2_INPUT6_REPEAT_RATE_EN );

    captouch2_write_reg( ctx, CAPTOUCH2_CONFIG2_REG, CAPTOUCH2_ALERT_ACTIVE_LOW |
                                                     CAPTOUCH2_SHOW_LOW_FREQ_NOISE |
                                                     CAPTOUCH2_RF_NOISE_FILTER_EN |
                                                     CAPTOUCH2_DETECT_RELEASE_EN );

    captouch2_write_reg( ctx, CAPTOUCH2_CONFIG_REG, CAPTOUCH2_DIG_NOISE_THRESHOLD_DIS |
                                                    CAPTOUCH2_AN_NOISE_FILTER_EN |
                                                    CAPTOUCH2_WAKE_PIN_NOT_ASSERTED );

    captouch2_write_reg( ctx, CAPTOUCH2_SENSITIVITY_CON_REG, CAPTOUCH2_SENSITIVITY_MULTIPLIER_32X |
                                                             CAPTOUCH2_DATA_SCALING_FACTOR_256X );

    captouch2_write_reg( ctx, CAPTOUCH2_AVRG_AND_SAMPL_CONFIG_REG, CAPTOUCH2_8_SAMPLES |
                                                                   CAPTOUCH2_SAMPLE_TIME_1280MICROSEC |
                                                                   CAPTOUCH2_CYCLE_TIME_70MILISEC );

    captouch2_write_reg( ctx, CAPTOUCH2_SENS_IN_CONFIG2_REG, CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_280MILISEC );

    captouch2_write_reg( ctx, CAPTOUCH2_SENS_IN_CONFIG_REG, CAPTOUCH2_5600MILISEC_BEFORE_RECALIB |
                                                            CAPTOUCH2_INTERR_REPEAT_RATE_175MILISEC );

    captouch2_set_active_mode( ctx, 1, CAPTOUCH2_ALL_INPUTS_ENABLE );

    set_def_val_state( ctx );
}

void captouch2_generic_transfer ( captouch2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void captouch2_write_reg ( captouch2_t *ctx, uint8_t reg_addr, uint8_t tx_data )
{
    uint8_t data_buf[ 6 ];

    data_buf[ 0 ] = 0x7A;
    data_buf[ 1 ] = 0x7A;
    data_buf[ 2 ] = 0x7D;
    data_buf[ 3 ] = reg_addr;
    data_buf[ 4 ] = 0x7E;
    data_buf[ 5 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms();
    spi_master_write( &ctx->spi, data_buf, 6 );
    spi_master_deselect_device( ctx->chip_select );  

    Delay_1ms();
    switch ( reg_addr )
    {
        case 0x00:
        {
            ctx->cfg_byte_data = tx_data;
            break;
        }
        case 0x44:
        {
            ctx->release_check = tx_data;
            break;
        }
    }
}

void captouch2_read_reg( captouch2_t *ctx, uint8_t reg_addr, uint8_t *rx_data, uint8_t n_bytes )
{
    uint8_t data_buf[ 5 ];
    uint8_t rsp_data[ 256 ];
    uint8_t cnt;

    data_buf[ 0 ] = 0x7A;
    data_buf[ 1 ] = 0x7A;
    data_buf[ 2 ] = 0x7D;
    data_buf[ 3 ] = reg_addr;
    data_buf[ 4 ] = 0x7F;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms();
    spi_master_write_then_read( &ctx->spi, data_buf, 5, rsp_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );  

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        rx_data[ cnt ] = rsp_data[ cnt ];
    }

    Delay_1ms();
}

void captouch2_detect_touch( captouch2_t *ctx, uint8_t *in_sens )
{
    uint8_t int_check;
    uint8_t touch_check;
    uint8_t noise_check;
    uint8_t i;
    uint8_t temp = 1;

    captouch2_read_reg( ctx, 0x00, &int_check, 1 );

    while ( !( int_check & 0x01 ) )
    {
        captouch2_read_reg( ctx, 0x00, &int_check, 1 );
    }
    ctx->cfg_byte_data &= 0xFE;

    captouch2_write_reg( ctx, 0x00, ctx->cfg_byte_data );
    captouch2_read_reg( ctx, 0x03, &touch_check, 1 );
    captouch2_read_reg( ctx, 0x0A, &noise_check, 1 );

    for ( i = 0; i < 6; i++ )
    {
        if ( ( touch_check & temp ) && ( !( noise_check & temp ) ) )
        {
            in_sens[ i ] = 1;
            if ( !( ctx->release_check & 0x01 ) )
            {
                ctx->input_check[ i ] = 1;
            }
        }
        else if ( ctx->input_check[ i ] )
        {
            in_sens[ i ] = 2;
            ctx->input_check[ i ] = 0;
        }
        else
        {
            in_sens[ i ] = 0;
        }
        temp <<= 1;
    }
}

void captouch2_set_active_mode( captouch2_t *ctx, uint8_t analog_gain, uint8_t en_input )
{
    uint8_t temp = 0;

    if ( en_input & 0xC0 )
    {
        return;
    }
    
    switch ( analog_gain )
    {
        case 1:
        {
            temp = 0x00;
            break;
        }
        case 2:
        {
            temp = 0x40;
            break;
        }
        case 4:
        {
            temp = 0x80;
            break;
        }
        case 8:
        {
            temp = 0xC0;
            break;
        }
    }
    captouch2_write_reg( ctx, 0x00, temp );
    captouch2_write_reg( ctx, 0x21, en_input );
    captouch2_write_reg( ctx, 0x27, en_input );
    captouch2_write_reg( ctx, 0x72, en_input );
}

void captouch2_set_standby_mode( captouch2_t *ctx, uint8_t analog_gain, uint8_t en_input )
{
    uint8_t temp = 0;

    if ( en_input & 0xC0 )
    {
        return;
    }

    switch ( analog_gain )
    {
        case 1:
        {
            temp = 0x20;
            break;
        }
        case 2:
        {
            temp = 0x60;
            break;
        }
        case 4:
        {
            temp = 0xA0;
            break;
        }
        case 8:
        {
            temp = 0xE0;
            break;
        }
    }
    captouch2_write_reg( ctx, 0x00, temp );
    captouch2_write_reg( ctx, 0x40, en_input );
    captouch2_write_reg( ctx, 0x27, en_input );
    captouch2_write_reg( ctx, 0x72, en_input );
}

void captouch2_set_deep_sleep_mode( captouch2_t *ctx )
{
    uint8_t temp = 0x10;

    captouch2_write_reg( ctx, 0x00, temp );
}

uint8_t captouch2_check_interrupt( captouch2_t *ctx )
{
    if ( digital_in_read( &ctx->alt ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void captouch2_reset( captouch2_t *ctx )
{
    uint8_t reset_state = 0;

    digital_out_high( &ctx->rst );
    Delay_100ms();
    digital_out_low( &ctx->rst );

    captouch2_read_reg( ctx, 0x02, &reset_state, 1 );

    while ( !( reset_state & 0x08 ) )
    {
        captouch2_read_reg( ctx, 0x02, &reset_state, 1 );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void set_def_val_state ( captouch2_t *ctx )
{
    ctx->release_check = 0;
    ctx->cfg_byte_data = 0;
    ctx->input_check[ 0 ] = 0;
    ctx->input_check[ 1 ] = 0;
    ctx->input_check[ 2 ] = 0;
    ctx->input_check[ 3 ] = 0;
    ctx->input_check[ 4 ] = 0;
    ctx->input_check[ 5 ] = 0;
}

// ------------------------------------------------------------------------- END


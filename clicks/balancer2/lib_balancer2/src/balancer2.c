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

#include "balancer2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BALANCER2_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static uint16_t dev_vref;


void balancer2_cfg_setup ( balancer2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg-> cell2 = HAL_PIN_NC;
    cfg-> int_pin = HAL_PIN_NC;
    cfg-> cell1 = HAL_PIN_NC;
    cfg-> stat = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

BALANCER2_RETVAL balancer2_init ( balancer2_t *ctx, balancer2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BALANCER2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BALANCER2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BALANCER2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx-> cell2, cfg-> cell2 );
    digital_out_init( &ctx-> int_pin, cfg-> int_pin );
    digital_out_init( &ctx-> cell1, cfg-> cell1 );
    digital_out_init( &ctx-> stat, cfg-> stat );

    return BALANCER2_OK;
}

void balancer2_default_cfg ( balancer2_t *ctx )
{
    balancer2_cell_1_state( ctx, BALANCER2_PIN_STATE_HIGH );
    balancer2_cell_2_state( ctx, BALANCER2_PIN_STATE_HIGH );
    balancer2_supply_state( ctx, BALANCER2_PIN_STATE_HIGH );
    balancer2_set_vref( ctx, BALANCER2_VREF_3V3 );
}

void balancer2_set_vref ( balancer2_t *ctx, uint16_t vref )
{
    dev_vref = vref;
}

float balancer2_get_batttery_lvl ( balancer2_t *ctx, uint8_t bat_num )
{
    uint16_t adc_val;
    float chn0;
    float chn1;

    if ( bat_num == BALANCER2_BATT1 )
    {
        adc_val = balancer2_read_adc( ctx, BALANCER2_CMD_SINGLE_MODE_CH0 );
        chn0 = balancer2_adc_to_mv( ctx, adc_val );
        chn0 *= CHN_0_MV_MULT;

        adc_val = balancer2_read_adc( ctx, BALANCER2_CMD_SINGLE_MODE_CH1 );
        chn1 = balancer2_adc_to_mv( ctx, adc_val );
        chn1 *= CHN_1_MV_MULT;

        return ( chn0 - chn1 );
    }
    else if ( bat_num == BALANCER2_BATT2 )
    {
        adc_val = balancer2_read_adc( ctx, BALANCER2_CMD_SINGLE_MODE_CH1 );
        chn1 = balancer2_adc_to_mv( ctx, adc_val );
        chn1 *= CHN_1_MV_MULT;

        return chn1;
    }
    else if ( bat_num == BALANCER2_BATT_BOTH )
    {
        adc_val = balancer2_read_adc( ctx, BALANCER2_CMD_SINGLE_MODE_CH0 );
        chn0 = balancer2_adc_to_mv( ctx, adc_val );
        chn0 *= CHN_0_MV_MULT;
        
        return chn0;
    }
    else
    {
        return 0.0;
    }
}
 
void balancer2_cell_1_state ( balancer2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx-> cell1, state );
}

void balancer2_cell_2_state ( balancer2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx-> cell2, state );
}

void balancer2_supply_state ( balancer2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx-> int_pin, state );
}

void balancer2_status_led_state ( balancer2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx-> stat, state );
}

uint16_t balancer2_read_adc ( balancer2_t *ctx, uint8_t cmd_byte )
{
    uint8_t wr_buff[ 3 ];
    uint8_t rd_buff[ 3 ] = { 0 };
    uint16_t result;

    wr_buff[ 0 ] = BALANCER2_CMD_START;
    wr_buff[ 1 ] = cmd_byte;
    wr_buff[ 2 ] = BALANCER2_CMD_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, wr_buff, 1 );
    spi_master_set_default_write_data( &ctx->spi, cmd_byte );
    spi_master_read( &ctx->spi, &rd_buff[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, BALANCER2_DUMMY );
    spi_master_read( &ctx->spi, &rd_buff[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    result = rd_buff[ 0 ] & BALANCER2_MASK;
    result <<= 8;
    result |= rd_buff[ 1 ];

    return result;
} 

float balancer2_adc_to_mv ( balancer2_t *ctx, uint16_t adc_val )
{
    float mv_data;

    mv_data = ( float )adc_val * dev_vref / ADC_RESOLUTION;

    return mv_data;
}
// ------------------------------------------------------------------------- END


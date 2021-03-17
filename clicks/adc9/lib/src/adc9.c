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

#include "adc9.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC9_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc9_cfg_setup ( adc9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mck = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ADC9_RETVAL adc9_init ( adc9_t *ctx, adc9_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC9_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADC9_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->mck, cfg->mck );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    spi_master_deselect_device( ctx->chip_select );  

    return ADC9_OK;
}

void adc9_default_cfg ( adc9_t *ctx, adc9_rw_t *rw )
{
    rw->dev_adr = ADC9_DEVICE_ADR;
    rw->cmd = ADC9_FAST_CMD_DEV_FULL_RESET;
    adc9_write_fast_cmd ( ctx, rw );

    rw->cmd = ADC9_FAST_CMD_ADC_CONV_START;
    adc9_write_fast_cmd ( ctx, rw );
}

void adc9_generic_transfer 
( 
    adc9_t *ctx, 
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

uint8_t adc9_write_fast_cmd ( adc9_t *ctx, adc9_rw_t *rw )
{
    uint8_t tx_buf;
    uint8_t stat_byte = 0;

    tx_buf = ( rw->dev_adr << 6 ) | rw->cmd;

    spi_master_set_default_write_data( &ctx->spi, tx_buf );
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, &stat_byte, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    return stat_byte;
}

// Write byte function
uint8_t adc9_write_u8 ( adc9_t *ctx, adc9_rw_t *rw, uint8_t wr_data )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 4 ];
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( ADC9_CMD_INC_WRITE & 0x03 );
    tx_buf[ 1 ] = wr_data;

    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, &stat_byte, 1 );
    spi_master_write( &ctx->spi, &tx_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    return stat_byte;
}

// Read byte function
uint8_t adc9_read_u8 ( adc9_t *ctx, adc9_rw_t *rw, uint8_t *rd_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( rw->cmd & 0x03 );
    tx_buf[ 1 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 1 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    stat_byte = rx_buf[ 0 ];
    *rd_data = rx_buf[ 1 ];

    return stat_byte;
}

// Write word function
uint8_t adc9_write_u16 ( adc9_t *ctx, adc9_rw_t *rw, uint16_t wr_data )
{
    uint8_t tx_buf [ 3 ];
    uint8_t rx_buf [ 3 ];
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( ADC9_CMD_INC_WRITE & 0x03 );
    tx_buf[ 1 ] = ( wr_data >> 8 ) & 0xFF;
    tx_buf[ 2 ] = wr_data & 0xFF;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    spi_master_write( &ctx->spi, &tx_buf[ 1 ], 2 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Read word function
uint8_t adc9_read_u16 ( adc9_t *ctx, adc9_rw_t *rw, uint16_t *rd_data )
{
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];
    uint8_t stat_byte = 0;
    uint16_t tmp_data;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( rw->cmd & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 2 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    tmp_data = rx_buf[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 2 ];

    *rd_data = tmp_data;

    stat_byte = rx_buf [ 0 ];

    return rx_buf [ 0 ];
}

// Write 24-bit function
uint8_t adc9_write_u24 ( adc9_t *ctx, adc9_rw_t *rw, uint32_t wr_data )
{
    uint8_t tx_buf [ 4 ];
    uint8_t rx_buf [ 4 ];
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( ADC9_CMD_INC_WRITE & 0x03 );
    tx_buf[ 1 ] = ( wr_data >> 16 ) & 0xFF;
    tx_buf[ 2 ] = ( wr_data >> 8 ) & 0xFF;
    tx_buf[ 3 ] = wr_data & 0xFF;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    spi_master_write( &ctx->spi, &tx_buf[ 1 ], 3 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Read 24-bit function
uint8_t adc9_read_u24 ( adc9_t *ctx, adc9_rw_t *rw, uint32_t *rd_data )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 4 ];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( rw->cmd & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 3 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    tmp_data = rx_buf[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 3 ];

    tmp_data &= 0x00FFFFFF;
    *rd_data = tmp_data;

    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Read 32-bit function
uint8_t adc9_read_u32 ( adc9_t *ctx, adc9_rw_t *rw, uint32_t *rd_data )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 5 ];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( rw->reg & 0x0F ) << 2 ) | ( rw->cmd & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x00;
    tx_buf[ 4 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 4 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    tmp_data = rx_buf[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 3 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 4 ];

    *rd_data = tmp_data;

    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Check IRQ pin state function
uint8_t adc9_irq_pin_state ( adc9_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// Read default adc value
uint8_t adc9_read_def_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *rd_data )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 5 ];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( ADC9_REG_ADC_DATA & 0x0F ) << 2 ) | ( ADC9_CMD_INC_READ & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x00;
    tx_buf[ 4 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 3 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    tmp_data = rx_buf[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 3 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 4 ];

    *rd_data = ( ( int32_t ) tmp_data ) / 256;
    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Read 24-bits left justified adc value
uint8_t adc9_read_24_left_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *rd_data )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 4 ];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;
    
    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( ADC9_REG_ADC_DATA & 0x0F ) << 2 ) | ( ADC9_CMD_INC_READ & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 3 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    tmp_data = rx_buf[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 3 ];
    tmp_data <<= 8;
    
    *rd_data = ( ( int32_t ) tmp_data ) / 256;
    stat_byte = rx_buf [ 0 ];
    
    return stat_byte;
}

// Read Sign and ADC value function
uint8_t adc9_read_sign_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *adc_val )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 5 ];
    uint8_t sign;
    int32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( ADC9_REG_ADC_DATA & 0x0F ) << 2 ) | ( ADC9_CMD_INC_READ & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x00;
    tx_buf[ 4 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 3 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    
    tmp_data = rx_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 3 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 4 ];
    
    sign =  rx_buf[ 1 ] & 0x01;

    if( sign != 0 )
    {
        tmp_data -= 16777215;
    }

    *adc_val = tmp_data;

    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Read Channel and ADC value function
uint8_t adc9_read_chan_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *adc_val, uint8_t *chan )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 5 ];
    uint8_t sign;
    uint8_t temp;
    int32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[ 0 ] = ( rw->dev_adr << 6 ) | ( ( ADC9_REG_ADC_DATA & 0x0F ) << 2 ) | ( ADC9_CMD_INC_READ & 0x03 );
    tx_buf[ 1 ] = 0x00;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x00;
    tx_buf[ 4 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );
    spi_master_read( &ctx->spi, &rx_buf[ 1 ], 4 );
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    spi_master_set_default_write_data( &ctx->spi, ADC9_DUMMY );

    tmp_data = rx_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 3 ];
    tmp_data <<= 8;
    tmp_data |= rx_buf[ 4 ];

    temp = rx_buf[ 1 ];

    *chan = ( temp >> 4 ) & 0x0F;
    sign =  temp & 0x01;

    if( sign != 0 )
    {
        tmp_data -= 16777215;
    }

    *adc_val = tmp_data;

    stat_byte = rx_buf [ 0 ];

    return stat_byte;
}

// Calculate Voltage function
float adc9_volt_calc ( adc9_t *ctx, int32_t adc_val, uint16_t v_ref, uint8_t gain )
{
    float volt;
    uint32_t coef = ADC9_CALC_COEF;
    
    volt = ( float )( adc_val / ( float )( coef * gain ) ) * ( float ) v_ref;

    return volt;
}

// ------------------------------------------------------------------------- END


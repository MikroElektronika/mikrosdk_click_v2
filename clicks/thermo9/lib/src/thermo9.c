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

#include "thermo9.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THERMO9_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void thermo9_i2c_write ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                                uint8_t len );

static void thermo9_i2c_read ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                               uint8_t len );

static void thermo9_spi_write ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                                uint8_t len );

static void thermo9_spi_read ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                               uint8_t len );

static void dev_conv_delay ( );

static void thermo9_i2c_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte );

static void thermo9_spi_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo9_cfg_setup ( thermo9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO9_ADDR_GND;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = THERMO9_MASTER_I2C;
}

THERMO9_RETVAL thermo9_init ( thermo9_t *ctx, thermo9_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == THERMO9_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return THERMO9_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = thermo9_i2c_read;
        ctx->write_f = thermo9_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        spi_cfg.default_write_data = THERMO9_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  THERMO9_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, THERMO9_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = thermo9_spi_read;
        ctx->write_f = thermo9_spi_write;
    }

    return THERMO9_OK;
}

void thermo9_generic_write ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                             uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void thermo9_generic_read ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                            uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void thermo9_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte )
{
    if ( ctx->master_sel == THERMO9_MASTER_I2C )
    { 
        thermo9_i2c_send_cmd( ctx, cmd_byte );
    }
    else
    {
        thermo9_spi_send_cmd( ctx, cmd_byte );
    }
}

// Calibration function
void thermo9_calibation ( thermo9_t *ctx )
{
    uint8_t data_buf[ 2 ];
    thermo9_send_cmd( ctx, THERMO9_RESET_CMD );
    dev_conv_delay( );
    
    thermo9_generic_read( ctx, THERMO9_PROM_READ_ADR_1_COEF_K4, data_buf, 2 );
    ctx->temp_coef.coef4 = data_buf[ 0 ];
    ctx->temp_coef.coef4 <<= 8;
    ctx->temp_coef.coef4 |= data_buf[ 1 ];

    thermo9_generic_read( ctx, THERMO9_PROM_READ_ADR_2_COEF_K3, data_buf, 2 );
    ctx->temp_coef.coef3 = data_buf[ 0 ];
    ctx->temp_coef.coef3 <<= 8;
    ctx->temp_coef.coef3 |= data_buf[ 1 ];
    
    thermo9_generic_read( ctx, THERMO9_PROM_READ_ADR_3_COEF_K2, data_buf, 2 );
    ctx->temp_coef.coef2 = data_buf[ 0 ];
    ctx->temp_coef.coef2 <<= 8;
    ctx->temp_coef.coef2 |= data_buf[ 1 ];
    
    thermo9_generic_read( ctx, THERMO9_PROM_READ_ADR_4_COEF_K1, data_buf, 2 );
    ctx->temp_coef.coef1 = data_buf[ 0 ];
    ctx->temp_coef.coef1 <<= 8;
    ctx->temp_coef.coef1 |= data_buf[ 1 ];
    
    thermo9_generic_read( ctx, THERMO9_PROM_READ_ADR_5_COEF_K0, data_buf, 2 );
    ctx->temp_coef.coef0 = data_buf[ 0 ];
    ctx->temp_coef.coef0 <<= 8;
    ctx->temp_coef.coef0 |= data_buf[ 1 ];
}

// Read temperature
float thermo9_read_temp ( thermo9_t *ctx )
{
    uint32_t temp_adc;
	uint8_t rx_buf[ 3 ];
    float adc_value;
    float result;
    
    thermo9_send_cmd( ctx, THERMO9_START_ADC_TEMP_CONV );
    dev_conv_delay( );
    thermo9_generic_read( ctx, THERMO9_READ_ADC_TEMP_RES, rx_buf, 3 );
	
	temp_adc = rx_buf[ 0 ];
    temp_adc <<= 8;
    temp_adc |= rx_buf[ 1 ];
    temp_adc <<= 8;
    temp_adc |= rx_buf[ 2 ];
    temp_adc &= 0x00FFFFFF;
	
    adc_value = (float)temp_adc / THERMO9_RES_MOD;

    result = (-2) * ( float )ctx->temp_coef.coef4 / 
    1000000000000000000000.0 * ( adc_value * adc_value * adc_value * adc_value );
    
    result += 4 * ( float )ctx->temp_coef.coef3 / 
    10000000000000000.0 * ( adc_value * adc_value * adc_value );
    result += (-2) * ( float )ctx->temp_coef.coef2 / 
    100000000000.0 * ( adc_value * adc_value );
    
    result += ( float )ctx->temp_coef.coef1 / 1000000.0 * adc_value;
    result += (-1.5) * ( float )ctx->temp_coef.coef0 /
    100.0;

    return result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void thermo9_i2c_write ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                                uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );        
}

static void thermo9_i2c_read ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                               uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void thermo9_spi_write ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                                uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );      
}

static void thermo9_spi_read ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                               uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

static void dev_conv_delay ( )
{
    Delay_10ms( );
}

static void thermo9_i2c_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte )
{
    i2c_master_write( &ctx->i2c, &cmd_byte, 1 );
}

static void thermo9_spi_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &cmd_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------- END

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

#include "altitude2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ALTITUDE2_DUMMY             0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void altitude2_make_conv_comm ( altitude2_t *ctx, uint8_t *comm_temp, uint8_t *comm_press );
static void altitude2_i2c_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes );
static void altitude2_i2c_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes );
static void altitude2_spi_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes );
static void altitude2_spi_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes );


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void altitude2_cfg_setup ( altitude2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ALTITUDE2_DEVICE_ADDR_1;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->sel = ALTITUDE2_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ALTITUDE2_RETVAL altitude2_init ( altitude2_t *ctx, altitude2_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ALTITUDE2_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;
        ctx->slave_address = cfg->i2c_address;
        
        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ALTITUDE2_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->send_comm_f = altitude2_i2c_send_comm;
        ctx->send_comm_resp_f = altitude2_i2c_send_comm_resp;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode    = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ALTITUDE2_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ALTITUDE2_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->send_comm_f = altitude2_spi_send_comm;
        ctx->send_comm_resp_f = altitude2_spi_send_comm_resp;
    }
    return ALTITUDE2_OK;
}

uint8_t altitude2_read_prom( altitude2_t *ctx, uint8_t select_data, uint32_t *data_out )
{
    uint8_t tmp_data;

    if( select_data > 7 )
    {
        return 1;
    }

    tmp_data = 0xA0 | ( select_data << 1 );
    ctx->send_comm_resp_f( ctx, tmp_data, data_out, 2 );

    return 0;
}

void altitude2_reset( altitude2_t *ctx )
{
    uint8_t comm_data = 0x1E;
    uint8_t cnt;

    ctx->send_comm_f( ctx, comm_data, 0, 0);
    
    for( cnt = 1; cnt < 7; cnt++ )
    {
        altitude2_read_prom( ctx, cnt, &ctx->data_prom[ cnt - 1 ] );
    } 
}

uint8_t altitude2_set_ratio( altitude2_t *ctx, uint8_t temp_ratio, uint8_t press_ratio )
{
    if ( temp_ratio > 4 )
    {
        return 1;
    }
    if ( press_ratio > 4 )
    {
        return 2;
    }

    ctx->ratio_temp = temp_ratio;
    ctx->ratio_press = press_ratio;

    return 0;
}

void altitude2_read_data( altitude2_t *ctx, float *temp_data, float *press_data, float *altitude_data )
{
    uint32_t buff_data[ 2 ];
    uint8_t temp_comm;
    uint8_t press_comm;
    float res_data[ 4 ];
    float  volatile tmp_var;
        
    altitude2_make_conv_comm( ctx, &temp_comm, &press_comm );
    ctx->send_comm_f( ctx, temp_comm, 0, 0 );
    ctx->send_comm_resp_f( ctx, 0x00, &buff_data[ 0 ], 3 );
    ctx->send_comm_f( ctx, press_comm, 0, 0 );
    ctx->send_comm_resp_f( ctx, 0x00, &buff_data[ 1 ], 3 );
    
    res_data[ 0 ] = ( float )ctx->data_prom[ 4 ] * 256.0;
    res_data[ 0 ] = ( float )buff_data[ 0 ] - res_data[ 0 ];
    res_data[ 1 ] = res_data[ 0 ] / 8.0;
    res_data[ 1 ] = res_data[ 1 ] * ( ( float )ctx->data_prom[ 5 ] / 1048576.0 );
    res_data[ 1 ] = res_data[ 1 ] + 2000.0;
    res_data[ 1 ] = res_data[ 1 ] / 100.0;
    *temp_data = res_data[ 1 ];
    
    res_data[ 2 ] = res_data[ 0 ] / 128.0;
    res_data[ 2 ] = res_data[ 2 ] * ( ctx->data_prom[ 2 ] / 2097152.0 );
    res_data[ 2 ] = res_data[ 2 ] + ( ctx->data_prom[ 0 ] / 32.0 );
    res_data[ 3 ] = res_data[ 0 ] / 32.0;
    res_data[ 3 ] = res_data[ 3 ] * ( ctx->data_prom[ 3 ] / 65536.0 ); 
    res_data[ 3 ] = res_data[ 3 ] + ( ctx->data_prom[ 1 ] * 4.0 );
    res_data[ 1 ] = buff_data[ 1 ] / 32768.0; 
    res_data[ 1 ] = res_data[ 1 ] * res_data[ 2 ];
    res_data[ 1 ] = res_data[ 1 ] - res_data[ 3 ];
    res_data[ 1 ] = res_data[ 1 ] / 100.0;
    *press_data = res_data[ 1 ];
    
    tmp_var = 1013.25 / *press_data;
    *altitude_data = pow( tmp_var, 0.19022256 );
    *altitude_data = *altitude_data - 1;
    tmp_var = *temp_data + 273.15;
    *altitude_data = *altitude_data *  tmp_var;
    *altitude_data = *altitude_data / 0.0065;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void altitude2_i2c_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes )
{
    i2c_master_write( &ctx->i2c, &comm_byte, 1 );  
    Delay_10ms( );
}

static void altitude2_spi_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    spi_master_write( &ctx->spi, &comm_byte, 1 );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );  
}

static void altitude2_i2c_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes )
{
    uint8_t tmp[ 3 ];
    uint8_t cnt;
    uint32_t pom = 0;

    i2c_master_write_then_read( &ctx->i2c, &comm_byte, 1, tmp, num_bytes );
    
    for( cnt = 0; cnt < num_bytes; cnt++ )
    {
        pom = pom << 8;
        pom = pom | tmp[ cnt ];
        
    }
    *output_data = pom;
}


static void altitude2_spi_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes )
{   
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 3 ];
    uint8_t cnt;
    uint32_t pom = 0;
    
    tx_buf[ 0 ] = comm_byte;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, num_bytes );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select ); 

    for( cnt = 0; cnt < num_bytes ; cnt++ )
    { 
        pom = pom << 8;
        pom = pom | rx_buf[ cnt ];  
        
    }
    *output_data = pom;
}

static void altitude2_make_conv_comm( altitude2_t *ctx, uint8_t *comm_temp, uint8_t *comm_press )
{
    uint8_t comm_byte = 0x50;
    uint8_t ratio_cnt = 0;

    while ( ctx->ratio_temp != ratio_cnt )
    {
        comm_byte += 2;
        ratio_cnt++;
    }

    *comm_temp = comm_byte;
    comm_byte = 0x40;
    ratio_cnt = 0;
    while ( ctx->ratio_press != ratio_cnt )
    {
        comm_byte += 2;
        ratio_cnt++;
    }

    *comm_press = comm_byte;
}

// ------------------------------------------------------------------------- END


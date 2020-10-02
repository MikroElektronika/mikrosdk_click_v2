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

#include "pressure5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE5_DUMMY 0

// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES

static uint8_t coefficients[ 22 ] = {0};
static pressure5_nvm_par_t   nvm_par;
static pressure5_par_coeff_t par;


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void pressure5_i2c_write ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure5_i2c_read ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure5_spi_write ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure5_spi_read ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void storage_coefficient ( void );

static uint8_t wait_drdy ( pressure5_t *ctx, uint8_t tp );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure5_cfg_setup ( pressure5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x76;
    
    cfg->sel = PRESSURE5_MASTER_SPI;
    //cfg->sel = PRESSURE5_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

PRESSURE5_RETVAL pressure5_init ( pressure5_t *ctx, pressure5_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == PRESSURE5_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return PRESSURE5_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = pressure5_i2c_read;
        ctx->write_f = pressure5_i2c_write;
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
        
        spi_cfg.default_write_data = PRESSURE5_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  PRESSURE5_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE5_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_select_device( ctx->chip_select ); 
        Delay_100ms();
        spi_master_deselect_device( ctx->chip_select ); 
        Delay_100ms();

        ctx->read_f = pressure5_spi_read;
        ctx->write_f = pressure5_spi_write;
    }
    

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return PRESSURE5_OK;
}

void pressure5_default_cfg ( pressure5_t *ctx )
{
    pressure5_generic_write( ctx, PRESSURE5_REG_OSR, PRESSURE5_OSR_PRESSURE_x1 | PRESSURE5_OSR_TEMP_x1 );
    pressure5_generic_write( ctx, PRESSURE5_REG_ODR, PRESSURE5_ODR_200 );
    
    pressure5_generic_write( ctx, PRESSURE5_REG_INT_CTRL, PRESSURE5_INTCFG_INT_OUTPUT_PUSH_PULL |
                                                 PRESSURE5_INTCFG_INT_LEVEL_ACTIVE_HIGH |
                                                 PRESSURE5_INTCFG_INT_LATCH_DISABLE |
                                                 PRESSURE5_INTCFG_FIFO_WTM_DISABLE |
                                                 PRESSURE5_INTCFG_FIFO_FULL_DISABLE |
                                                 PRESSURE5_INTCFG_DATA_READY_ENABLE );

    pressure5_generic_write( ctx, PRESSURE5_REG_IF_CONFIG, PRESSURE5_IFCFG_SPI_4_WIRE |
                                                  PRESSURE5_IFCFG_I2C_WATCHDOG_ENABLE |
                                                  PRESSURE5_IFCFG_I2C_WATCHDOG_LONG_40ms );
                                                  
    pressure5_generic_write( ctx, PRESSURE5_REG_POWER_CTRL,PRESSURE5_PCTRL_PRESSURE_SENSOR_ENABLE |
                                                  PRESSURE5_PCTRL_TEMP_SENSOR_ENABLE |
                                                  PRESSURE5_PCTRL_MODE_NORMAL );
        
    pressure5_update_coefficient( ctx );
}

void pressure5_generic_write ( pressure5_t *ctx, uint8_t reg, uint8_t reg_data)
{
    uint8_t write_data = reg_data;
    
    ctx->write_f( ctx, reg, &write_data, 1 ); 
}

uint8_t pressure5_generic_read ( pressure5_t *ctx, uint8_t reg )
{
    uint8_t read_data = 0;
    
    ctx->read_f( ctx, reg, &read_data, 1 );
    
    return read_data;
    
}

void pressure5_read ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t pressure5_get_interrupt_state ( pressure5_t *ctx )
{
    return digital_in_read(&ctx->int_pin);
}

void pressure5_software_reset ( pressure5_t *ctx )
{
    pressure5_generic_write(ctx, PRESSURE5_REG_COMMAND, PRESSURE5_CMD_SOFTWARE_RESET);
}

uint32_t pressure5_get_raw_data ( pressure5_t *ctx, uint8_t data_addr )
{
    uint32_t data_raw;
    
    if(data_addr == PRESSURE5_REG_TEMPERATURE_DATA_0)
    {
        wait_drdy(ctx, 0x40);
    }
    else
    {
        wait_drdy(ctx, 0x20);
    }
    
    data_raw = 0;

    data_raw = pressure5_generic_read(ctx, data_addr + 2 );
    data_raw <<= 8;
    data_raw |=  pressure5_generic_read(ctx, data_addr + 1 );
    data_raw <<= 8;
    data_raw |=  pressure5_generic_read(ctx, data_addr);
    
    return data_raw;
}

void pressure5_update_coefficient ( pressure5_t *ctx )
{ 
    pressure5_read ( ctx, 0x31, coefficients, 21 );  
    storage_coefficient( );
}

float pressure5_get_temperature_data ( pressure5_t *ctx )
{
    uint32_t temp_raw;
    float partial_data1;
    float partial_data2;
    float calib_temp;
    
    temp_raw = pressure5_get_raw_data(ctx, PRESSURE5_REG_TEMPERATURE_DATA_0);
    
    partial_data1 = ( float )( temp_raw - par.t1 );
    partial_data2 = ( float )( partial_data1 * par.t2 );
    
    calib_temp = partial_data2 + ( partial_data1 * partial_data1 ) * par.t3;
    
    return calib_temp;
}

float pressure5_get_pressure_data ( pressure5_t *ctx )
{
    uint32_t pressure_raw;
    float temp_data;
    float comp_press;
    float data1;
    float data2;
    float data3;
    float data4;
    float out1;
    float out2;
    
    temp_data = pressure5_get_temperature_data( ctx );
    pressure_raw = pressure5_get_raw_data(ctx, PRESSURE5_REG_PRESSURE_DATA_0);
    
    data1 = par.p6 * temp_data;
    data2 = par.p7 * ( temp_data * temp_data );
    data3 = par.p8 * ( temp_data * temp_data * temp_data );
    out1 = par.p5 + data1 + data2 + data3;
    
    data1 = par.p2 * temp_data;
    data2 = par.p3 * ( temp_data * temp_data );
    data3 = par.p4 * ( temp_data * temp_data * temp_data );
    out2 = ( float )pressure_raw;
    out2 *= par.p1 + data1 + data2 + data3;
    
    data1 = ( float )pressure_raw * ( float )pressure_raw;
    data2 = par.p9 + par.p10 * temp_data;
    data3 = data1 * data2;
    data4 = data3 + ( ( float )pressure_raw * ( float )pressure_raw * ( float )pressure_raw ) * par.p11;
    
    comp_press = out1 + out2 + data4;
    
    return comp_press / 100.0;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pressure5_i2c_write ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void pressure5_i2c_read ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void pressure5_spi_write ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void pressure5_spi_read ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ] = { 0 };
    uint8_t read_buf[ 256 ] = { 0 };
    uint16_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, read_buf, len + 1  );
    spi_master_deselect_device( ctx->chip_select );  

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        *data_buf = read_buf[ cnt ];
        data_buf++;
    }
}

static void storage_coefficient( void )
{
    // Temperature 
    nvm_par.t1 = coefficients[ 1 ];
    nvm_par.t1 <<= 8;
    nvm_par.t1 |= coefficients[ 0 ];
    par.t1 = nvm_par.t1 / 0.00390625;
    
    nvm_par.t2 = coefficients[ 3 ];
    nvm_par.t2 <<= 8;
    nvm_par.t2 |= coefficients[ 2 ];
    par.t2 = nvm_par.t2 / 1073741824.0;
    
    nvm_par.t3 = coefficients[ 4 ];
    par.t3 = nvm_par.t3 / 281474976710656.0;
    
    // Pressure
    nvm_par.p1 = coefficients[ 6 ];
    nvm_par.p1 <<= 8;
    nvm_par.p1 |= coefficients[ 5 ];
    par.p1 = (nvm_par.p1 - 16384) / 1048576.0;
    
    nvm_par.p2 = coefficients[ 8 ];
    nvm_par.p2 <<= 8;
    nvm_par.p2 |= coefficients[ 7 ];
    par.p2 = (nvm_par.p2 - 16384) / 536870912.0;
    
    nvm_par.p3 = coefficients[ 9 ];
    par.p3 = nvm_par.p3 / 4294967296.0;
    
    nvm_par.p4 = coefficients[ 10 ];
    par.p4 = nvm_par.p4 / 137438953472.0;
    
    nvm_par.p5 = coefficients[ 12 ];
    nvm_par.p5 <<= 8;
    nvm_par.p5 |= coefficients[ 11 ];
    par.p5 = nvm_par.p5 / 0.125;
    
    nvm_par.p6 = coefficients[ 14 ];
    nvm_par.p6 <<= 8;
    nvm_par.p6 |= coefficients[ 13 ];
    par.p6 = nvm_par.p6 / 64.0;
     
    nvm_par.p7 = coefficients[ 15 ];
    par.p7 = nvm_par.p7 / 256.0;
    nvm_par.p8 = coefficients[ 16 ];
    par.p8 = nvm_par.p8 / 32768.0;
    
    nvm_par.p9 = coefficients[ 18 ];
    nvm_par.p9 <<= 8;
    nvm_par.p9 |= coefficients[ 17 ];
    par.p9 = nvm_par.p9 / 281474976710656.0;
    
    nvm_par.p10 = coefficients[ 19 ];
    par.p10 = nvm_par.p10 / 281474976710656.0;
    nvm_par.p11 = coefficients[ 20 ];
    par.p11 = nvm_par.p11 / 36893488147419103232.0;
}

static uint8_t wait_drdy ( pressure5_t *ctx, uint8_t tp )
{
    uint8_t status;
    uint8_t cnt = 0;
    
    do
    {
        status = pressure5_generic_read(ctx, PRESSURE5_REG_INT_STATUS);
        cnt++;
        Delay_10ms();
        if ( cnt > 20 )
        {
            return 1;
        }
        
    }
    while ( (status & tp) == 0 );
    
    return 0;
}

// ------------------------------------------------------------------------- END


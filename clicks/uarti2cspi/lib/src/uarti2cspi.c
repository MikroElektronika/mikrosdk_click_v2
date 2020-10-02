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

#include "uarti2cspi.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define UARTI2CSPI_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void uarti2cspi_i2c_write ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void uarti2cspi_i2c_read ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void uarti2cspi_spi_write ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void uarti2cspi_spi_read ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static uint16_t drv_calculate_baud_rate ( uint16_t baud_rate );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uarti2cspi_cfg_setup ( uarti2cspi_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FAST; 
    cfg->i2c_address = UARTI2CSPI_ADDR;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = UARTI2CSPI_MASTER_SPI;
}

UARTI2CSPI_RETVAL uarti2cspi_init ( uarti2cspi_t *ctx, uarti2cspi_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == UARTI2CSPI_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return UARTI2CSPI_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = uarti2cspi_i2c_read;
        ctx->write_f = uarti2cspi_i2c_write;
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
        
        spi_cfg.default_write_data = UARTI2CSPI_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        
        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  UARTI2CSPI_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, UARTI2CSPI_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = uarti2cspi_spi_read;
        ctx->write_f = uarti2cspi_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    // Pin configuration

    digital_out_high( &ctx->rst );
    spi_master_deselect_device( ctx->chip_select ); 

    return UARTI2CSPI_OK;
}

void uarti2cspi_generic_write ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void uarti2cspi_generic_read ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void uarti2cspi_advanced_init ( uarti2cspi_t *ctx, uarti2cspi_package_t package )
{
    uint8_t dll_val;
    uint8_t dlh_val;
    uint16_t brr_reg_speed;

    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );

    brr_reg_speed = drv_calculate_baud_rate( package.baud_rate );

    dlh_val = 0x80;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_LCR, &dlh_val, 1 );                            

    dlh_val = ( uint8_t )( ( brr_reg_speed >> 8 ) & 0x00FF );
    dll_val = ( uint8_t )( brr_reg_speed & 0x00FF );

    uarti2cspi_generic_write( ctx, UARTI2CSPI_DLL, &dll_val, 1 );                             
    uarti2cspi_generic_write( ctx, UARTI2CSPI_DLH, &dlh_val, 1 );   

    dlh_val = 0xBF;
    dll_val = 0x00;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_LCR, &dlh_val, 1 );
    uarti2cspi_generic_write( ctx, UARTI2CSPI_EFR, &dll_val, 1 );                              

    dlh_val = package.data_bits | package.parity_mode | package.stop_bits;
    dll_val = 0x03;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_LCR, &dlh_val, 1 );
    uarti2cspi_generic_write( ctx, UARTI2CSPI_IER, &dll_val, 1 );                                
}

void uarti2cspi_interrupt_enable ( uarti2cspi_t *ctx, uint8_t vector )
{
    uint8_t reg_tmp;
    uint8_t flow_tmp;
    
    uarti2cspi_generic_read( ctx, UARTI2CSPI_LCR, &reg_tmp, 1 );
    
    if ( ( vector & 0x80 ) || ( vector & 0x40 ) || ( vector & 0x20 ) || ( vector & 0x10 ) )
    {
        flow_tmp = 0xBF;

        uarti2cspi_generic_write( ctx, UARTI2CSPI_LCR, &flow_tmp, 1 );
        uarti2cspi_generic_read( ctx, UARTI2CSPI_EFR, &flow_tmp, 1 );

        flow_tmp |= 0x10;

        uarti2cspi_generic_write( ctx, UARTI2CSPI_EFR, &flow_tmp, 1 );
    }
    else
    {
        flow_tmp = 0xBF;

        uarti2cspi_generic_write( ctx, UARTI2CSPI_LCR, &flow_tmp, 1 );
        uarti2cspi_generic_read( ctx, UARTI2CSPI_EFR, &flow_tmp, 1 );

        flow_tmp &= ~0x10;

        uarti2cspi_generic_write( ctx, UARTI2CSPI_EFR, &flow_tmp, 1 );
    }
    
    uarti2cspi_generic_write( ctx, UARTI2CSPI_LCR, &reg_tmp, 1 );
    uarti2cspi_generic_write( ctx, UARTI2CSPI_IER, &vector, 1 );
}

void uarti2cspi_serial_write ( uarti2cspi_t *ctx, uint8_t *str_data, uint8_t print_mode )
{
    if ( print_mode & TEXT_PRINT )
    {
        uarti2cspi_uart_text( ctx, str_data );

        if ( print_mode & LINE_PRINT )
        { 
            uarti2cspi_uart_text( ctx, "\r\n" );
        }
    }
    if ( print_mode == CHAR_PRINT )
    {
         uarti2cspi_advanced_uart_write( ctx, *str_data );
    }
}

void uarti2cspi_advanced_uart_write ( uarti2cspi_t *ctx, uint8_t w_byte )
{
    uint8_t tmp;

    tmp = 0x02;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_IER, &tmp, 1 );
    uarti2cspi_generic_write( ctx, UARTI2CSPI_THR, &w_byte, 1 );

    while ( digital_in_read( &ctx->int_pin ) );

    tmp = 0x01;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_IER, &tmp, 1 );
}

void uarti2cspi_uart_text ( uarti2cspi_t *ctx, uint8_t *w_text )
{
    while ( *w_text )
    {
        uarti2cspi_advanced_uart_write( ctx, *w_text++ );
    }
}

void uarti2cspi_uart_write ( uarti2cspi_t *ctx, uint8_t w_byte )
{
    uint8_t tmp;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_THR, &w_byte, 1 );

    while ( digital_in_read( &ctx->int_pin ) ); 

    tmp = 0x01;

    uarti2cspi_generic_write( ctx, UARTI2CSPI_IER, &tmp, 1 );
}

uint8_t uarti2cspi_uart_read ( uarti2cspi_t *ctx )
{
    uint8_t rhr_v;

    uarti2cspi_generic_read( ctx, UARTI2CSPI_RHR, &rhr_v, 1 );

    return  rhr_v;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void uarti2cspi_i2c_write ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void uarti2cspi_i2c_read ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void uarti2cspi_spi_write ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void uarti2cspi_spi_read ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );
}

static uint16_t drv_calculate_baud_rate ( uint16_t baud_rate )
{
    uint16_t calc;
    float tmp;

    tmp =  UARTI2CSPI_OSCILATOR_FREQ / UARTI2CSPI_PRESCALER_DEF;
    calc = ( uint16_t )( tmp / ( ( float ) baud_rate * 16.0 ) );

    return calc;
}

// ------------------------------------------------------------------------- END


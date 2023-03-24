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

#include "i2ctospi.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void i2ctospi_cfg_setup ( i2ctospi_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2CTOSPI_I2C_SLAVE_ADDRESS_0;
}

I2CTOSPI_RETVAL i2ctospi_init ( i2ctospi_t *ctx, i2ctospi_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2CTOSPI_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->cs );

    return I2CTOSPI_OK;
}

void i2ctospi_default_cfg ( i2ctospi_t *ctx )
{
    i2ctospi_hw_reset( ctx );
    Delay_100ms( );
    
    i2ctospi_enable_gpio( ctx, I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS0 );
    
    i2ctospi_config_spi( ctx, I2CTOSPI_CONFIGURE_SPI_ORDER_MSB_FIRST
                        | I2CTOSPI_CONFIGURE_SPI_MODE_SPICLK_LOW_LEADING_EDGE
                        | I2CTOSPI_CONFIGURE_SPI_CLOCK_RATE_115kHz );

    i2ctospi_write_enable( ctx, I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS0 );
    
    i2ctospi_clear_interrupt( ctx );
}

void i2ctospi_generic_write ( i2ctospi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void i2ctospi_generic_read ( i2ctospi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void i2ctospi_hw_reset ( i2ctospi_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t i2ctospi_get_interrupt ( i2ctospi_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// Generic SPI write the byte of data to data buffer function 
void i2ctospi_spi_write_byte ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t write_data )
{
    uint8_t w_buffer[ 3 ];

    w_buffer[ 0 ] = spi->function_id;
    w_buffer[ 1 ] = spi->reg_addr;
    w_buffer[ 2 ] = write_data;

    i2ctospi_generic_write( ctx, spi->slave_device, w_buffer, 3 );

    i2ctospi_clear_interrupt( ctx );
}

// Generic SPI read the byte of data from data buffer function 
uint8_t i2ctospi_spi_read_byte ( i2ctospi_t *ctx, i2ctospi_spi_t *spi )
{
    uint8_t w_buffer[ 4 ];
    uint8_t r_buffer[ 3 ];

    w_buffer[ 0 ] = spi->slave_device;
    w_buffer[ 1 ] = spi->function_id;
    w_buffer[ 2 ] = spi->reg_addr;
    w_buffer[ 3 ] = 0xFF;

    i2c_master_write( &ctx->i2c, w_buffer, 4 );  

    i2ctospi_clear_interrupt( ctx );

    i2c_master_read( &ctx->i2c, r_buffer, 3 ); 

    return r_buffer[ 2 ];
}

// Generic SPI write - single address burst write function 
void i2ctospi_spi_burst_write ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t *write_data )
{
    uint8_t cnt;
    uint8_t w_buffer[ 204 ];

    w_buffer[ 0 ] = spi->function_id;
    w_buffer[ 1 ] = spi->reg_addr;
    
    for ( cnt = 0; cnt < spi->n_bytes; cnt++ )
    {
        w_buffer[ cnt + 3 ] = write_data[ cnt ];
    }

    i2ctospi_generic_write( ctx, spi->slave_device, w_buffer, spi->n_bytes + 3 );

    i2ctospi_clear_interrupt( ctx );
}

// Generic SPI read - single address burst read function 
void i2ctospi_spi_burst_read ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t *read_data )
{
    uint8_t cnt;
    uint8_t w_buffer[ 203 ];

    w_buffer[ 0 ] = spi->slave_device;
    w_buffer[ 1 ] = spi->function_id;
    w_buffer[ 2 ] = spi->reg_addr;
    
    for ( cnt = 0; cnt < spi->n_bytes; cnt++ )
    {
        w_buffer[ cnt + 3 ] = 0xFF;
    }

    i2c_master_write( &ctx->i2c, w_buffer, spi->n_bytes + 3 );

    i2ctospi_clear_interrupt( ctx );

    i2c_master_read( &ctx->i2c, read_data, spi->n_bytes );
}

// Generic burst read from the data buffer function
void i2ctospi_read_buffer_bytes ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t *read_data )
{
    i2c_master_read( &ctx->i2c, read_data, spi->n_bytes );
}

// Generic write command byte of data function
void i2ctospi_write_command ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t command_data )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = command_data;

    i2ctospi_generic_write( ctx, spi->function_id, w_buffer, 1 );
}

// SPI EEPROM wite enable function
void i2ctospi_write_enable ( i2ctospi_t *ctx, uint8_t ss_pin_data )
{
    uint8_t tmp;
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = 0x06;

    i2ctospi_generic_write( ctx, ss_pin_data, w_buffer, 1 );
}

// Configure SPI Interface function
void i2ctospi_config_spi ( i2ctospi_t *ctx, uint8_t config_data )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = config_data;

    i2ctospi_generic_write( ctx, I2CTOSPI_CONFIGURE_SPI, w_buffer, 1 );
}

// Clear interrupt function 
void i2ctospi_clear_interrupt ( i2ctospi_t *ctx )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = I2CTOSPI_CLEAR_INTERRUPT;
    
    while ( i2ctospi_get_interrupt( ctx ) != 0 );
    
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );

    i2ctospi_generic_write( ctx, I2CTOSPI_CLEAR_INTERRUPT, w_buffer, 0 );
}

// Set Idle mode function 
void i2ctospi_set_idle_mode ( i2ctospi_t *ctx )
{
    uint8_t w_buffer[ 1 ];
    i2ctospi_generic_write( ctx, I2CTOSPI_IDLE_MODE, w_buffer, 0 );
}

// Set state of the pins defined as GPIO write function 
void i2ctospi_set_write_state_of_gpio ( i2ctospi_t *ctx, uint8_t gpio_state )
{
    uint8_t w_buffer[ 1 ];

    gpio_state &= 15;

    w_buffer[ 0 ] = gpio_state;

    i2ctospi_generic_write( ctx, I2CTOSPI_GPIO_WRITE, w_buffer, 1 );
}

// Get state of the pins defined as GPIO read function
void i2ctospi_set_read_state_of_gpio ( i2ctospi_t *ctx, uint8_t gpio_state )
{
    uint8_t w_buffer[ 1 ];
    
    gpio_state &= 15;

    w_buffer[ 0 ] = gpio_state;

    i2ctospi_generic_write( ctx, I2CTOSPI_GPIO_READ, w_buffer, 0 );
}

// Enable the pins defined as GPIO function 
void i2ctospi_enable_gpio ( i2ctospi_t *ctx, uint8_t ss_pin_number )
{
    uint8_t w_buffer[ 1 ];

    ss_pin_number &= 3;

    w_buffer[ 0 ] = ( uint8_t ) ( 0x01 << ss_pin_number );

    i2ctospi_generic_write( ctx, I2CTOSPI_GPIO_ENABLE, w_buffer, 1 );
}

// Enable the pins defined as GPIO function
void i2ctospi_types_gpio ( i2ctospi_t *ctx, i2ctospi_gpio_t *gpio )
{
    uint8_t tmp;

    gpio->ss3_val &= 3;
    gpio->ss2_val &= 3;
    gpio->ss1_val &= 3;
    gpio->ss0_val &= 3;

    tmp = 0;

    tmp = gpio->ss3_val;
    tmp <<= 2;
    tmp = gpio->ss2_val;
    tmp <<= 2;
    tmp = gpio->ss1_val;
    tmp <<= 2;
    tmp = gpio->ss0_val;

    i2ctospi_generic_write( ctx, I2CTOSPI_GPIO_CONFIGURATION, &tmp, 1 );
}

// ------------------------------------------------------------------------- END


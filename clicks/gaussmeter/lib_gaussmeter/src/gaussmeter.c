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

#include "gaussmeter.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GAUSSMETER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t drv_make_command ( gaussmeter_t *ctx, uint8_t *command_byte, uint8_t *num_bytes );

static void drv_spi_data_transfer ( gaussmeter_t *ctx, uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len );

static void drv_i2c_data_transfer ( gaussmeter_t *ctx, uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len );

static uint8_t drv_get_data_bytes ( gaussmeter_t *ctx );

static void drv_get_sens( gaussmeter_t *ctx, float *xysens, float *zsens );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gaussmeter_cfg_setup ( gaussmeter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->trg = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x0C;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = GAUSSMETER_MASTER_SPI;

    cfg->aux.command_byte_low = 0;
    cfg->aux.select_gain = 0;
    cfg->aux.select_res = 0;
}

GAUSSMETER_RETVAL gaussmeter_init ( gaussmeter_t *ctx, gaussmeter_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == GAUSSMETER_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return GAUSSMETER_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        i2c_master_set_timeout( &ctx->i2c, 0 );

        ctx->data_transfer_f = drv_i2c_data_transfer;
        
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );
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
        
        spi_cfg.default_write_data = GAUSSMETER_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  GAUSSMETER_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, GAUSSMETER_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->data_transfer_f = drv_spi_data_transfer;
    }

    ctx->aux.command_byte_low = cfg->aux.command_byte_low;
    ctx->aux.select_gain = cfg->aux.select_gain;
    ctx->aux.select_res = cfg->aux.select_res;

    // Input pins

    digital_in_init( &ctx->trg, cfg->trg );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GAUSSMETER_OK;
}

void gaussmeter_default_cfg ( gaussmeter_t *ctx )
{
    ctx->axis.z = GAUSSMETER_EN_Z_AXIS;
    ctx->axis.y = GAUSSMETER_EN_Y_AXIS;
    ctx->axis.x = GAUSSMETER_EN_X_AXIS;

    gaussmeter_send_command( ctx, GAUSSMETER_EXIT_MODE_COMM );
    Delay_100ms( );
    gaussmeter_send_command( ctx, GAUSSMETER_RESET_COMM );
    Delay_100ms( );
    gaussmeter_write_reg( ctx, GAUSSMETER_CONFIG1_REG, GAUSSMETER_GAIN_7 |
                                                       GAUSSMETER_EN_Z_MEASURE_PLATES );
    gaussmeter_write_reg( ctx, GAUSSMETER_CONFIG2_REG, GAUSSMETER_WOC_DIFF_EN |
                                 GAUSSMETER_TCMP_DIS | GAUSSMETER_BOTH_DRIVER );
    gaussmeter_write_reg( ctx, GAUSSMETER_CONFIG3_REG, GAUSSMETER_RES_0 | 0x0801 );   
    
    gaussmeter_enable_measure( ctx, GAUSSMETER_EN_TEMP_MEAS );
    gaussmeter_send_command( ctx, GAUSSMETER_START_WOC_MODE_COMM );
}

uint8_t gaussmeter_write_reg ( gaussmeter_t *ctx, uint8_t reg_addr, uint16_t transfer_data )
{
    uint8_t write_buf[ 4 ];
    uint8_t read_buf[ 1 ];

    if ( reg_addr > 0x1F )
    {
        return 0xFF;
    }
        
    write_buf[ 0 ] = GAUSSMETER_WRITE_REG_COMM;
    write_buf[ 1 ] = transfer_data >> 8;
    write_buf[ 2 ] = transfer_data;
    write_buf[ 3 ] = reg_addr << 2;
    
    gaussmeter_generic_data_transfer( ctx, write_buf, 4, read_buf, 1 );
    
    if ( reg_addr == 0x00 )
    {
        ctx->aux.select_gain = transfer_data & 0x0070;
        ctx->aux.select_gain >>= 4;
    }
    else if ( reg_addr == 0x02 )
    {
        ctx->aux.select_res = transfer_data & 0x07E0;
        ctx->aux.select_res >>= 5;
    }
    
    return read_buf[ 0 ];
}

uint8_t gaussmeter_send_command ( gaussmeter_t *ctx, uint8_t command )
{
    uint8_t n_bytes;
    uint8_t error_check;

    error_check = drv_make_command( ctx, &command, &n_bytes );

    if ( error_check )
    {
        return 0xFF;
    }

    gaussmeter_generic_data_transfer( ctx, &command, 1, &error_check, 1 );

    return error_check;
}

void gaussmeter_enable_measure ( gaussmeter_t *ctx, uint8_t temp )
{
    if ( ctx->axis.z )
    {
        ctx->aux.command_byte_low |= 0x08;
    }
    if ( ctx->axis.y )
    {
        ctx->aux.command_byte_low |= 0x04;
    }
    if ( ctx->axis.x )
    {
        ctx->aux.command_byte_low |= 0x02;
    }
    if ( temp )
    {
        ctx->aux.command_byte_low |= 0x01;
    }
}

uint8_t gaussmeter_get_data( gaussmeter_t *ctx, float *output_data )
{
    uint8_t write_buf[ 9 ];
    uint8_t read_buf[ 50 ];
    int16_t temp_data[ 10 ];
    int16_t temp = 0;
    uint16_t temperature = 0;
    uint8_t n_bytes;
    uint8_t cnt;
    uint8_t index = 0;
    uint8_t pom = 1;
    uint8_t bit_check = 1;
    float sens_x_y;
    float sens_z;
    
    write_buf[ 0 ] = 0x40 | ctx->aux.command_byte_low;
    n_bytes = drv_get_data_bytes( ctx );
    while ( !gaussmeter_digital_read_int( ctx ) );

    gaussmeter_generic_data_transfer( ctx, write_buf, 1, read_buf, n_bytes );
    
    for ( cnt = 1; cnt < n_bytes; cnt++ )
    {
        if ( pom )
        {
            temp = read_buf[ cnt ];
            pom = 0;
        }
        else
        {
            temp <<= 8;
            temp |= read_buf[ cnt ];
            temp_data[ index++ ] = temp;
            pom = 1;
        }
    }
    
    drv_get_sens( ctx, &sens_x_y, &sens_z );
    index = 0;

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( ctx->aux.command_byte_low & bit_check )
        {
            case 1:
                    {
                        temperature = ( uint16_t ) temp_data[ index ] ;
                        
                        if ( temperature > 46244 ) 
                        {
                            temperature -= 46244;
                            output_data[ index ] = 25 + ( float ) temperature / 45.2;
                        }
                        else if ( temperature < 46244 )
                        {
                            temperature = 46244 - temperature;
                            output_data[ index ] = 25 - ( float ) temperature / 45.2;
                        }
                        else
                        {
                            output_data[ index ] = 25;
                        }
                        index++;
                        break;
                    }
            case 2: output_data[ index ] = ( float ) temp_data[ index++ ] * sens_x_y;
                    break;
            case 4: output_data[ index ] = ( float ) temp_data[ index++ ] * sens_x_y;
                    break;
            case 8: output_data[ index ] = ( float ) temp_data[ index++ ] * sens_z;
        }
        bit_check <<= 1;
    }
    read_buf[ 0 ] &= 0x10;
    read_buf[ 0 ] >>= 4;

    return read_buf[ 0 ];
}

uint8_t gaussmeter_digital_read_int ( gaussmeter_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t gaussmeter_digital_read_pwm ( gaussmeter_t *ctx )
{
    return digital_in_read( &ctx->trg );
}

void gaussmeter_generic_data_transfer ( gaussmeter_t *ctx, uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len )
{
    ctx->data_transfer_f( ctx, write_buf, write_len, read_buf, read_len );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void drv_get_sens( gaussmeter_t *ctx, float *xysens, float *zsens )
{
    float sens_1;
    float sens_2;
    uint8_t cnt;

    switch ( ctx->aux.select_gain )
    {
        case 0:
        {
            sens_1 = 0.805;
            sens_2 = 1.468;
            break;
        }
        case 1: 
        {
            sens_1 = 0.644;
            sens_2 = 1.174;
            break;    
        }
        case 2: 
        {
            sens_1 = 0.483;
            sens_2 = 0.881;
            break;
        }
        case 3:
        {
            sens_1 = 0.403;
            sens_2 = 0.734;
            break;
        }
        case 4:
        {
            sens_1 = 0.322;
            sens_2 = 0.587;
            break;
        } 
        case 5: 
        {
            sens_1 = 0.268;
            sens_2 = 0.489;
            break;
        }
        case 6:
        {
            sens_1 = 0.215;
            sens_2 = 0.391;
            break;
        } 
        case 7: 
        {
            sens_1 = 0.161;
            sens_2 = 0.294;
        }
    }
    if ( ctx->aux.select_res > 3 )
    {
        ctx->aux.select_res = 3;
    }
    for ( cnt = 0; cnt < ctx->aux.select_res; cnt++ )
    {
        sens_1 *= 2;
        sens_2 *= 2;
    }
    *xysens = sens_1;
    *zsens = sens_2;
}

static uint8_t drv_get_data_bytes ( gaussmeter_t *ctx )
{
    uint8_t temp = 1;
    uint8_t cnt;
    uint8_t byte_cnt= 0;

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( ctx->aux.command_byte_low & temp )
        {
            byte_cnt++;
        }
        temp <<= 1;
    }
    byte_cnt *= 2;
    byte_cnt++;

    return byte_cnt;
}

static uint8_t drv_make_command ( gaussmeter_t *ctx, uint8_t *command_byte, uint8_t *num_bytes ) 
{
    switch ( *command_byte )
    {
        case 0x10:
        {
            *command_byte |= ctx->aux.command_byte_low;
            *num_bytes = 1;
            break;
        } 
        case 0x20:
        {
            *command_byte |= ctx->aux.command_byte_low;
            *num_bytes = 1;
            break;
        }
        case 0x30:
        {
            *command_byte |= ctx->aux.command_byte_low;
            *num_bytes = 1;
            break;
        }
        case 0x80:
        {
            *num_bytes = 1;
            break;
        }
        case 0xD0:
        {
            *num_bytes = 1;
            break;
        }
        case 0xE0:
        {
            *num_bytes = 1;
            break;
        }
        case 0xF0:
        {
            *num_bytes = 1;
            break;
        }
        default:
        {
            return 1;
        }
    }
    return 0;
}

static void drv_spi_data_transfer ( gaussmeter_t *ctx, uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len )
{
    spi_master_select_device( ctx->chip_select );
    
    spi_master_write_then_read( &ctx->spi, write_buf, write_len, read_buf, read_len );

    spi_master_deselect_device( ctx->chip_select );  
}

static void drv_i2c_data_transfer ( gaussmeter_t *ctx, uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len )
{
    i2c_master_write_then_read( &ctx->i2c, write_buf, write_len, read_buf, read_len );
}

// ------------------------------------------------------------------------- END


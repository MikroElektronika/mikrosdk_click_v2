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

#include "gyro4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GYRO4_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gyro4_cfg_setup ( gyro4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

GYRO4_RETVAL gyro4_init ( gyro4_t *ctx, gyro4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = GYRO4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return GYRO4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, GYRO4_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GYRO4_OK;
}

void gyro4_generic_transfer ( gyro4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );     
}

uint8_t gyro4_int_get( gyro4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void gyro4_cs_set( gyro4_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->int_pin, pin_state );
}

uint8_t gyro4_spi_get ( gyro4_t *ctx, uint8_t register_address, uint8_t *register_buffer, uint16_t n_registers )
{
    uint8_t i;
    uint8_t cmd;

    if ( n_registers > 4 ) 
    {
        return 1;
    }
    cmd = register_address;
    cmd |= 0xC0;

    Delay_1ms( );

    gyro4_generic_transfer( ctx, &cmd, 1, register_buffer, n_registers );

    return 0;
}

uint8_t gyro4_spi_set ( gyro4_t *ctx, uint8_t register_address, uint8_t data_in )
{
    uint8_t temp[ 2 ];

    temp[ 0 ] = register_address;
    temp[ 0 ] &= 0x3F;
    temp[ 0 ] |= 0x40;

    temp[ 1 ] = data_in;

    Delay_1ms( );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 2 );
    spi_master_deselect_device( ctx->chip_select );  

    return 0;
}

uint8_t gyro4_initialize ( gyro4_t *ctx )
{
    uint8_t tmp;
    
    tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL2_OIS, 0x02 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    Delay_1sec( );

    tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL1_OIS, 0x4B );
    if ( 0 != tmp ) 
    {
        return 1;
    }
 
    tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL2_OIS, 0x00 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL3_OIS, 0x02 );
    if ( 0 != tmp ) 
    {
        return 1;
    } 
    tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL4_OIS, 0x10 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    tmp = gyro4_spi_set( ctx, GYRO4_REG_OIS_CFG, 0x08 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    return 0;
}

uint8_t gyro4_get_temperature ( gyro4_t *ctx, float * temperature )
{
    int16_t aux_temperature;
    uint8_t tmp;

    tmp = gyro4_spi_get( ctx, GYRO4_REG_CTRL1_OIS, &ctx->aux_buffer[ 0 ], 1 );
    if ( 0 != tmp ) 
    {
        return 1;
    }

    ctx->aux_buffer[ 0 ] &= 0x20;

    switch ( ctx->aux_buffer[ 0 ] )
    {
        case 0x00:
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_TEMP_OUT_L, &ctx->aux_buffer[ 0 ], 2 );
            if ( 0 != tmp ) 
            {
                return 1;
            }

            aux_temperature = 0;
            aux_temperature |= ctx->aux_buffer[ 1 ];
            aux_temperature <<= 8;
            aux_temperature |= ctx->aux_buffer[ 0 ];
            break;
        }
        case 0x20:
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_TEMP_OUT_L, &ctx->aux_buffer[ 0 ], 2 );
            if ( 0 != tmp ) 
            {
                return 1;
            }

            aux_temperature = 0;
            aux_temperature |= ctx->aux_buffer[ 0 ];
            aux_temperature <<= 8;
            aux_temperature |= ctx->aux_buffer[ 1 ];
            break;
        }
        default :
        {
            break;
        }
    }

    *temperature = ( float ) ( aux_temperature ) * 0.0625;
    *temperature = *temperature / 16.0;
    *temperature = *temperature + 25.0;

    return 0;
}

uint8_t gyro4_get_axes ( gyro4_t *ctx, float * x_axis, float * y_axis )
{
    int16_t aux_x_axis;
    int16_t aux_y_axis;
    uint8_t tmp;
    float aux_resolution;

    tmp = gyro4_spi_get( ctx, GYRO4_REG_OIS_CFG, &ctx->aux_buffer[ 0 ], 1 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    ctx->aux_buffer[ 0 ] &= 0x08;
    switch ( ctx->aux_buffer[ 0 ] )
    {
        case 0x00 :
        {
            aux_resolution = 0.0030517578125; // 100.0 / 32768.0
            break;
        }
        case 0x08 :
        {
            aux_resolution = 0.006103515625; // 200.0 / 32768.0
            break;
        }
        default :
        {
            break;
        }
    }
    tmp = gyro4_spi_get( ctx, GYRO4_REG_CTRL1_OIS, &ctx->aux_buffer[ 0 ], 1 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    ctx->aux_buffer[ 0 ] &= 0x20;
    
    switch ( ctx->aux_buffer[ 0 ] )
    { 
        case 0x00:
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_OUT_X_L, &ctx->aux_buffer[ 0 ], 4 );
            if ( 0 != tmp ) 
            {
                return 1;
            }

            aux_x_axis = 0;
            aux_x_axis |= ctx->aux_buffer[ 1 ];
            aux_x_axis <<= 8; 
            aux_x_axis |= ctx->aux_buffer[ 0 ];
 
            aux_y_axis = 0; 
            aux_y_axis |= ctx->aux_buffer[ 3 ];
            aux_y_axis <<= 8; 
            aux_y_axis |= ctx->aux_buffer[ 2 ];

            *x_axis = ( float ) ( aux_x_axis ) * aux_resolution;
            *y_axis = ( float ) ( aux_y_axis ) * aux_resolution;
            
            break;
        }
        case 0x20:
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_OUT_X_L, &ctx->aux_buffer[ 0 ], 4 );
            if ( 0 != tmp ) 
            {
                return 1;
            }

            aux_x_axis = 0;
            aux_x_axis |= ctx->aux_buffer[ 0 ];
            aux_x_axis <<= 8; 
            aux_x_axis |= ctx->aux_buffer[ 1 ];
 
            aux_y_axis = 0; 
            aux_y_axis |= ctx->aux_buffer[ 2 ];
            aux_y_axis <<= 8; 
            aux_y_axis |= ctx->aux_buffer[ 3 ];

            *x_axis = ( float ) ( aux_x_axis ) * aux_resolution;
            *y_axis = ( float ) ( aux_y_axis ) * aux_resolution;

            break;
        }
        default :
        {
            break;
        }
    }
    return 0;
}

uint8_t gyro4_software_reset ( gyro4_t *ctx )
{
    uint8_t tmp;

    tmp = gyro4_spi_get( ctx, GYRO4_REG_CTRL2_OIS, &ctx->aux_buffer[ 0 ], 1 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL2_OIS, 0x02 );
    if ( 0 != tmp ) 
    {
        return 1;
    }

    Delay_1sec( );
    
    return 0;
}

uint8_t gyro4_set_power_mode ( gyro4_t *ctx, uint8_t power_mode )
{
    uint8_t temp;
    uint8_t tmp;

    if ( power_mode > 3 ) 
    {    
        return 1;
    }
    if ( power_mode < 1 ) 
    {    
        return 1;
    }
    
    switch ( power_mode )
    { 
        case 1 :
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_CTRL1_OIS, &ctx->aux_buffer[ 0 ], 1 );
            if ( 0 != tmp ) 
            {    
                return 1;
            }
            temp &= 0xFC;
            temp |= 0x01;
            tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL1_OIS, temp );
            if ( 0 != tmp ) 
            {    
                return 1;
            }
            break;
        }
        case 2 :
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_CTRL1_OIS, &ctx->aux_buffer[ 0 ], 1 );
            if ( 0 != tmp ) 
            {    
                return 1;
            }
           temp &= 0xFC;
           temp |= 0x02;
           tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL1_OIS, temp );
            if ( 0 != tmp ) 
            {    
                return 1;
            }
            break;
        }
        case 3 :
        {
            tmp = gyro4_spi_get( ctx, GYRO4_REG_CTRL1_OIS, &ctx->aux_buffer[ 0 ], 1 );
            if ( 0 != tmp ) 
            {    
                return 1;
            }
            temp &= 0xFC;
            temp |= 0x03;
            tmp = gyro4_spi_set( ctx, GYRO4_REG_CTRL1_OIS, temp );
            if (0 != tmp ) 
            {    
                return 1;
            }
            break;
        }
        default :
        {
            break;
        }
    }
    
    return 0;
}

uint8_t gyro4_set_full_scale_range ( gyro4_t *ctx, uint8_t full_scale_range )
{
    uint8_t temp;
    uint8_t tmp;

    if ( full_scale_range > 2 ) 
    {
        return 1;
    }
    if ( full_scale_range < 1 ) 
    {
        return 1;
    }
    tmp = gyro4_spi_get( ctx, GYRO4_REG_OIS_CFG, &ctx->aux_buffer[ 0 ], 1 );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    temp &= 0xF7;
    if ( full_scale_range == 2 )
    {
        temp |= 0x08;
    }
    tmp = gyro4_spi_set( ctx, GYRO4_REG_OIS_CFG, temp );
    if ( 0 != tmp ) 
    {
        return 1;
    }
    
    return 0;
}

// ------------------------------------------------------------------------- END


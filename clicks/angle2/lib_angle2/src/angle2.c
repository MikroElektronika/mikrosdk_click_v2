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

#include "angle2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ANGLE2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static double calc_angle( uint16_t angle_deg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void angle2_cfg_setup ( angle2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

ANGLE2_RETVAL angle2_init ( angle2_t *ctx, angle2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ANGLE2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ANGLE2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ANGLE2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return ANGLE2_OK;
}

void angle2_default_cfg ( angle2_t *ctx )
{
    angle2_write_reg( ctx, ANGLE2_BIAS_CURR_TRIMM_REG_3, 0x00 );
    angle2_enable_trimming( ctx, ANGLE2_X_AXIS_TRIMM_EN | ANGLE2_Y_AXIS_TRIMM_EN );
    angle2_set_zero_scale( ctx, 44 );
}

void angle2_generic_transfer ( angle2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

double angle2_write_reg ( angle2_t *ctx, uint8_t addr, uint8_t input )
{
    uint8_t buff_in[ 2 ];
    uint8_t buff_out[ 2 ];
    uint16_t angle_data;
    
    buff_in[ 0 ] = addr & ANGLE2_REG_ADDR_MASK;
    buff_in[ 0 ] |= ANGLE2_WRITE_CMD;
    buff_in[ 1 ] = input;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 0 ] );
    spi_master_read( &ctx->spi,&buff_out[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 1 ] );
    spi_master_read( &ctx->spi,&buff_out[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );  
  
    angle_data = buff_out[ 0 ];
    angle_data <<= 4;
    angle_data |= buff_out[ 1 ] >> 4;
    
    return calc_angle( angle_data );
}

double angle2_read_reg ( angle2_t *ctx, uint8_t addr, uint8_t *output )
{
    uint8_t buff_in[ 2 ];
    uint8_t buff_out[ 2 ];
    uint16_t angle_data;
    
    buff_in[ 0 ] = addr & ANGLE2_REG_ADDR_MASK;
    buff_in[ 0 ] |= ANGLE2_READ_CMD;
    buff_in[ 1 ] = ANGLE2_DUMMY_BYTE;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 0 ] );
    spi_master_read( &ctx->spi,&buff_out[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 1 ] );
    spi_master_read( &ctx->spi,&buff_out[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    *output = buff_out[ 1 ];
    angle_data = buff_out[ 0 ];
    angle_data <<= 4;
    
    return calc_angle( angle_data );
}

double angle2_get_angle ( angle2_t *ctx )
{
    uint8_t buff_in[ 2 ];
    uint8_t buff_out[ 2 ];
    uint16_t angle_data;
    
    buff_in[ 0 ] = ANGLE2_DUMMY_BYTE;
    buff_in[ 1 ] = ANGLE2_DUMMY_BYTE;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 0 ] );
    spi_master_read( &ctx->spi,&buff_out[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 1 ] );
    spi_master_read( &ctx->spi,&buff_out[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    angle_data = buff_out[ 0 ];
    angle_data <<= 4;
    angle_data |= buff_out[ 1 ] >> 4;
    
    return calc_angle( angle_data );
}

double angle2_get_angle_with_time_index ( angle2_t *ctx, uint8_t *time_index )
{
    uint8_t buff_in[ 3 ];
    uint8_t buff_out[ 3 ];
    uint16_t angle_data;
    
    buff_in[ 0 ] = ANGLE2_DUMMY_BYTE;
    buff_in[ 1 ] = ANGLE2_DUMMY_BYTE;
    buff_in[ 2 ] = ANGLE2_DUMMY_BYTE;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 0 ] );
    spi_master_read( &ctx->spi,&buff_out[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, buff_in[ 1 ] );
    spi_master_read( &ctx->spi,&buff_out[ 1 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, buff_in[2 ] );
    spi_master_read( &ctx->spi,&buff_out[ 2 ], 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    *time_index = buff_out[ 2 ];
    angle_data = buff_out[ 0 ];
    angle_data <<= 4;
    angle_data |= buff_out[ 1 ] >> 4;
    
    return calc_angle( angle_data );
}

void angle2_set_zero_scale ( angle2_t *ctx, double zero_deg )
{
    double res;
    uint16_t zero_data;
    uint8_t data_send[ 2 ];
    
    if ( zero_deg > ANGLE2_MAX_SCALE_359_91_DEG )
    {
        res = ANGLE2_MAX_SCALE_359_91_DEG;
    }
    else
    {
        res = zero_deg;
    }
    
    res /= ANGLE2_DEG_LSB;
    zero_data = res;
    
    angle2_read_reg( ctx, ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, &data_send[ 0 ] );
    data_send[ 0 ] &= 0x30;
    data_send[ 0 ] |= ( zero_data & 0x000F );
    data_send[ 1 ] = ( zero_data >> 4 );
    
    angle2_write_reg( ctx, ANGLE2_ZERO_POS_MSB_REG_4, data_send[ 1 ] );
    angle2_write_reg( ctx, ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, data_send[ 0 ] );
}

void angle2_enable_trimming ( angle2_t *ctx, uint8_t state )
{
    uint8_t data_send;
    
    angle2_read_reg( ctx, ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, &data_send );
    
    data_send &= 0xCF;
    data_send |= state & 0x30;
    
    angle2_write_reg( ctx, ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, data_send );
}

void angle2_flash_reg ( angle2_t *ctx, uint8_t reg_sel )
{
    uint8_t data_send;
    
    data_send = reg_sel & 0x38;
    
    angle2_write_reg( ctx, ANGLE2_FLASH_N_REG_9, data_send );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static double calc_angle( uint16_t angle_deg )
{
    double resolution;

    resolution = angle_deg;
    resolution *= ANGLE2_DEG_LSB;

    return resolution;
}

// ------------------------------------------------------------------------- END


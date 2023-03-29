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

#include "angle4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ANGLE4_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void angle4_cfg_setup ( angle4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;

    cfg->cfg_resolution = 0x00;
    cfg->cfg_new_angle = 0;
}

ANGLE4_RETVAL angle4_init ( angle4_t *ctx, angle4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode; 
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ANGLE4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR)
    {
        return ANGLE4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ANGLE4_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return ANGLE4_OK;
}

void angle4_default_cfg ( angle4_t *ctx, uint8_t dir, uint8_t data_resolution )
{
    angle4_write_byte ( ctx, ANGLE4_REG_CUSTOMER_CFG_0, ANGLE4_CCFG0_SELECT_UVW_MODE |
                                                        ANGLE4_CCFG0_PWM_PERIOD_1025us |
                                                        ANGLE4_CCFG0_ABI_270edeg |
                                                        ANGLE4_CCFG0_UVW_POLE_PAIRS_8  );

    angle4_write_byte( ctx, ANGLE4_REG_CUSTOMER_CFG_1, ANGLE4_CCFG1_ABI_CPR_4096 |
                                                       ANGLE4_CCFG1_HYSTERESIS_1_4mdeg );

    angle4_write_byte( ctx, ANGLE4_REG_OPERATING_VOLTAGE, ANGLE4_OPERATING_VOLTAGE_5000mV );
    
    ctx->resolution = data_resolution;
    
    angle4_write_byte( ctx, ANGLE4_REG_CUSTOMER_CFG_2,  dir | ctx->resolution | ANGLE4_CCFG2_SETTINGS_CPR_4096 );
                                                
    angle4_write_byte( ctx, ANGLE4_REG_UNLOCK_REGISTER, 0xAB );
    angle4_write_byte( ctx, ANGLE4_REG_CUSTOMER_RESERVED_OTP, 0xA1 );
    angle4_write_byte( ctx, ANGLE4_REG_ST_ZERO_RESET_OTP, 0xA2 );
    angle4_write_byte( ctx, ANGLE4_REG_CUSTOMER_CONFIG_OTP, 0xA3 );
    angle4_write_byte( ctx, ANGLE4_REG_PROGRAM_OPERATING_VOLTAGE, 0xA4 );
    angle4_write_byte( ctx, ANGLE4_REG_CONFIG_OF_FULL_CALIBRATION_OTP, 0xA5 );
    angle4_write_byte( ctx, 0x00, 0xAA );
}

void angle4_generic_transfer ( angle4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void angle4_write_byte ( angle4_t *ctx, uint8_t addr, uint8_t w_data )
{
    uint8_t write_data[ 2 ];

    write_data[ 0 ] = addr | 0x40;
    write_data[ 1 ] = w_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_data, 2 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t angle4_read_byte ( angle4_t *ctx, uint8_t addr )
{   
    uint8_t write_data[ 1 ];
    uint8_t read_data[ 2 ];
    
    write_data[ 0 ] = addr | 0x80;

    angle4_generic_transfer ( ctx, write_data, 1, read_data, 2 );

    return read_data[ 1 ];
}

void angle4_start_mesuremenet ( angle4_t *ctx )
{
    uint8_t write_data[ 1 ];

    write_data[ 0 ] = 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t angle4_get_new_angle ( angle4_t *ctx, uint16_t *data_out )
{
    uint8_t read_reg[ 3 ];
    uint16_t angle_data;
    uint8_t status;

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, read_reg, 3 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    angle_data = read_reg[ 0 ];
    angle_data = angle_data << 8;
    angle_data = angle_data | read_reg[ 1 ];
    
    // Status 0x0F - Ready, MHI, MLO, Parity

    status = read_reg[ 2 ] >> 4;
    
    if ( ctx->resolution == ANGLE4_DATA_RESOLUTION_14bit )
    {
        angle_data = angle_data >> 2;
        ctx->new_angle = angle_data * 0.02197;

        status = ( read_reg[ 1 ] & 0x03 ) << 2;
        status |= ( read_reg[ 2 ] & 0xC0 ) >> 6;
    }
    else if ( ctx->resolution == ANGLE4_DATA_RESOLUTION_12bit )
    {
        angle_data = angle_data >> 4;
        ctx->new_angle = angle_data * 0.087890;

        status = read_reg[ 1 ] & 0x0F;
    }
    else if ( ctx->resolution == ANGLE4_DATA_RESOLUTION_10bit )
    {
        angle_data = angle_data >> 6;
        ctx->new_angle = angle_data * 0.35156;

        status = ( read_reg[ 1 ] >> 2 ) & 0x0F;
    }
    else
    {
        ctx->new_angle = angle_data * 0.005493247;

        status = ( read_reg[ 2 ] >> 4 ) & 0x0F;
    }

    *data_out = ctx->new_angle;

    return status;
}

// ------------------------------------------------------------------------- END


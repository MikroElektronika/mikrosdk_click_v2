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

#include "thunder.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THUNDER_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thunder_cfg_setup ( thunder_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->irq = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

THUNDER_RETVAL thunder_init ( thunder_t *ctx, thunder_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

   spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = THUNDER_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return THUNDER_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, THUNDER_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->irq, cfg->irq );
    

    return THUNDER_OK;
}

void thunder_default_cfg ( thunder_t *ctx )
{
    thunder_send_command( ctx, THUNDER_RESET_COMM );
    thunder_send_command( ctx, THUNDER_CALIB_RCO_COMM );
    
    thunder_write_reg( ctx, THUNDER_CONFIG_0_REG, THUNDER_OUTDOOR | THUNDER_NORMAL_MODE );
    thunder_write_reg( ctx, THUNDER_CONFIG_1_REG, 0x21 );
    thunder_write_reg( ctx, THUNDER_CONFIG_2_REG, THUNDER_CLEAR_STAT | THUNDER_1_LIGHTNING | 0x02 );
    thunder_write_reg( ctx, THUNDER_CONFIG_3_INTERR_REG, THUNDER_DIV_RATIO_32 | THUNDER_UNMASK_DISTURBER );
    thunder_write_reg( ctx, THUNDER_INTERR_PIN_CONFIG_REG, THUNDER_NO_DISPLAY_ON_IRQ_PIN );
}

void thunder_generic_transfer 
( 
    thunder_t *ctx, 
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

uint8_t thunder_write_reg ( thunder_t *ctx, uint8_t reg_addr, uint8_t transfer_data )
{
    uint8_t buff_data[ 2 ];
    
    if ( ( ( reg_addr > 0x32 ) || ( reg_addr > 0x03 && reg_addr < 0x08 ) ) && ( reg_addr != 0x3C && reg_addr != 0x3D ) )
    {
        return 1;
    }
    
    buff_data[ 0 ] = reg_addr;
    buff_data[ 1 ] = transfer_data;
    
    if ( reg_addr == 0x3C || reg_addr == 0x3D )
    {
        buff_data[ 1 ] = 0x96;
    }

    thunder_generic_transfer( ctx, buff_data, 2, 0, 0 );

    return 0;
}

uint8_t thunder_read_reg ( thunder_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t buff_data_in[ 52 ] = { 0 };
    uint8_t buff_data_out[ 52 ] = { 0 };
    uint8_t cnt;
    
    if ( reg_addr > 0x32 )
    {
        return 1;
    }
    if ( n_bytes > 51 )
    {
        return 2;
    }
    
    buff_data_in[ 0 ] = reg_addr | 0x40;

    thunder_generic_transfer( ctx, buff_data_in, 1, buff_data_out, n_bytes + 1 );

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        data_out[ cnt ] = buff_data_out[ cnt + 1 ];
    }
    
    return 0;
}

void thunder_send_command ( thunder_t *ctx, uint8_t command )
{
    if ( command == 0 )
    {
        thunder_write_reg( ctx, THUNDER_RESET_REG, 0x96 );
    }
    else
    {
        thunder_write_reg( ctx, THUNDER_CALIB_REG, 0x96 );
    }
    
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t thunder_check_interr ( thunder_t *ctx )
{
    uint8_t interr_check;
    
    if ( digital_in_read( &ctx->irq ) )
    {
        Delay_1ms( );
        Delay_1ms( );
        Delay_1ms( );
        Delay_1ms( );
    
        thunder_read_reg( ctx, THUNDER_CONFIG_3_INTERR_REG, &interr_check, 1 );
        interr_check &= 0x0F;
    }
    else
    {
        interr_check = 0;
    }
    
    return interr_check;
}

void thunder_get_storm_info ( thunder_t *ctx, uint32_t *energy_out, uint8_t *distance_out )
{
    uint32_t temp;
    uint8_t tmp[ 4 ];

    thunder_read_reg ( ctx, THUNDER_ENERGY_LIGHTNING_LSBYTE_REG, tmp, 4 );
    
    temp = tmp[ 2 ] & 0x1F;
    temp <<= 8;
    temp |= tmp[ 1 ];
    temp <<= 8;
    temp |= tmp[ 0 ];
    *energy_out = temp;
    
    *distance_out = tmp[ 3 ] & 0x3F;
}

uint8_t thunder_check_irq_pin ( thunder_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

// ------------------------------------------------------------------------- END


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

#include "pwrmeter2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWRMETER2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pwrmeter2_cfg_setup ( pwrmeter2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->md1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->md0 = HAL_PIN_NC;
    cfg->dr = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

PWRMETER2_RETVAL pwrmeter2_init ( pwrmeter2_t *ctx, pwrmeter2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = PWRMETER2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return PWRMETER2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, PWRMETER2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->md1, cfg->md1 );
    digital_in_init( &ctx->md0, cfg->md0 );
    digital_in_init( &ctx->dr, cfg->dr );
    
    return PWRMETER2_OK;
}

void pwrmeter2_default_cfg ( pwrmeter2_t *ctx )
{
    pwrmeter2_reset( ctx );
    pwrmeter2_write_reg( ctx, PWRMETER2_CONFIG1_REG, PWRMETER2_CH0_NORMAL_MODE | PWRMETER2_CH1_NORMAL_MODE | PWRMETER2_INTERNAL_VOL_REF_EN | PWRMETER2_INTERNAL_CLOCK_EN );
    pwrmeter2_write_reg( ctx, PWRMETER2_STATUS_COMM_REG, PWRMETER2_READ_REG_TYPES | PWRMETER2_ADDR_COUNT_INCR_WRITE | PWRMETER2_DATA_WIDTH_24_BIT | 0x000003 );
    pwrmeter2_write_reg( ctx, PWRMETER2_CONFIG0_REG, PWRMETER2_OFFCAL_EN | PWRMETER2_GAINCAL_EN | PWRMETER2_DITHERING_STRENGTH_MAX | PWRMETER2_CURRENT_X_2 | PWRMETER2_AMCLK_MCLK_PER_8 | PWRMETER2_OSR_256 );
    pwrmeter2_write_reg( ctx, PWRMETER2_GAIN_CONFIG_REG, PWRMETER2_CH0_GAIN1 | PWRMETER2_CH1_GAIN1 );
    pwrmeter2_write_reg( ctx, PWRMETER2_GAINCAL_CH0_REG, 0xD30000 );
    pwrmeter2_write_reg( ctx, PWRMETER2_GAINCAL_CH1_REG, 0xD30000 );
    pwrmeter2_write_reg( ctx, PWRMETER2_OFFCAL_CH1_REG, 0xFFE800 );
}

void pwrmeter2_generic_transfer 
( 
    pwrmeter2_t *ctx, 
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

uint8_t pwrmeter2_write_reg ( pwrmeter2_t *ctx, uint8_t register_address, uint32_t transfer_data )
{
    uint8_t buff_data_in[ 4 ];
    
    if ( register_address > 0x1F)
    {
        return 1;
    }
        
    buff_data_in[ 0 ] = ( register_address << 1 ) | 0x40;
    buff_data_in[ 1 ] = transfer_data >> 16;
    buff_data_in[ 2 ] = transfer_data >> 8;
    buff_data_in[ 3 ] = transfer_data;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &buff_data_in[ 0 ], 1 );
    spi_master_write( &ctx->spi, &buff_data_in[ 1 ], 1 );
    spi_master_write( &ctx->spi, &buff_data_in[ 2 ], 1 );
    spi_master_write( &ctx->spi, &buff_data_in[ 3 ], 1 );
    spi_master_deselect_device( ctx->chip_select );  
    
    return 0;
}

uint8_t pwrmeter2_read_reg ( pwrmeter2_t *ctx, uint8_t register_address, uint32_t *data_out, uint8_t n_data )
{
    uint8_t buff_data_in[ 40 ] = { 0 };
    uint8_t buff_data_out[ 40 ] = { 0 };
    uint8_t n_bytes;
    uint8_t cnt;
    uint32_t temp;
    
    if ( register_address > 0x1F )
    {
        return 1;
    }
    if ( n_data > 13 )
    {
        return 2;
    }
        
    buff_data_in[ 0 ] = ( register_address << 1 ) | 0x41;
    n_bytes = ( n_data * 3 ) + 1;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, buff_data_in[ 0 ] );
    spi_master_read( &ctx->spi, buff_data_out, n_bytes );
    spi_master_set_default_write_data( &ctx->spi, PWRMETER2_DUMMY );
    spi_master_deselect_device( ctx->chip_select );  

    n_bytes = 1;
    for ( cnt = 0; cnt < n_data; cnt++ )
    {
        temp = buff_data_out[ n_bytes ];
        temp <<= 8;
        temp |= buff_data_out[ n_bytes + 1 ];
        temp <<= 8;
        temp |= buff_data_out[ n_bytes + 2 ];
        data_out[ cnt ] = temp;
        n_bytes += 3;
    }

    return 0;
}

uint8_t pwrmeter2_check_data_ready ( pwrmeter2_t *ctx, uint8_t sel_chann )
{
    uint32_t tmp;
    uint32_t ready_bits;
    uint8_t ret_val;
    
    if ( ( sel_chann == 0 ) || ( sel_chann > 3 ) )
    {
        return 0xFF;
    }
    if ( sel_chann == ( PWRMETER2_CH0_CHECK_EN | PWRMETER2_CH1_CHECK_EN ) )
    {
        if ( ctx->dr_link != 1 )
        {
            pwrmeter2_read_reg( ctx, PWRMETER2_STATUS_COMM_REG, &ready_bits, 1 );
            ready_bits |= 0x00080000;
            pwrmeter2_write_reg( ctx, PWRMETER2_STATUS_COMM_REG, ready_bits );
            ctx->dr_link = 1;
        }
    }
    else
    {
        if ( ctx->dr_link != 0 )
        {
            pwrmeter2_read_reg( ctx, PWRMETER2_STATUS_COMM_REG, &ready_bits, 1 );
            ready_bits &= 0xFFF7FFFF;
            pwrmeter2_write_reg( ctx, PWRMETER2_STATUS_COMM_REG, ready_bits );
            ctx->dr_link = 0;
        }
    }
        
    tmp = sel_chann;
    pwrmeter2_read_reg( ctx, PWRMETER2_STATUS_COMM_REG, &ready_bits, 1 );
    
    while (ready_bits & tmp)
        pwrmeter2_read_reg( ctx, PWRMETER2_STATUS_COMM_REG, &ready_bits, 1 );
        
    ready_bits &= 0x00030000;
    ready_bits >>= 16;
    ret_val = ready_bits;
        
    return ret_val;
}

uint8_t pwrmeter2_read_conv_data ( pwrmeter2_t *ctx, uint32_t *data_ch_0, uint32_t *data_ch_1 )
{
    uint8_t data_width;
    uint8_t buff_data_in[ 9 ];
    uint8_t buff_data_out[ 9 ];
    uint8_t n_bytes;
    uint8_t byte_indx;
    uint32_t temp_1;
    uint32_t temp_2;
    
    data_width = pwrmeter2_check_data_ready( ctx, PWRMETER2_CH0_CHECK_EN | PWRMETER2_CH1_CHECK_EN );
    
    if ( data_width > 1 )
    {
        n_bytes = 9;
        byte_indx = 5;
    }
    else if ( data_width == 1 )
    {
        n_bytes = 7;
        byte_indx = 4;
    }
    else
    {
        n_bytes = 5;
        byte_indx = 3;
    }
    buff_data_in[ 0 ] = PWRMETER2_CH0_ADC_DATA_REG | 0x41;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, buff_data_in[ 0 ] );
    spi_master_read( &ctx->spi, buff_data_out, n_bytes );
    spi_master_set_default_write_data( &ctx->spi, PWRMETER2_DUMMY );
    spi_master_deselect_device( ctx->chip_select );  
    
    temp_1 = buff_data_out[ 1 ];
    temp_1 <<= 8;
    temp_1 |= buff_data_out[ 2 ];
    temp_2 = buff_data_out[ byte_indx ];
    temp_2 <<= 8;
    temp_2 |= buff_data_out[ byte_indx + 1 ];
    
    if ( data_width != 0 )
    {
        temp_1 <<= 8;
        temp_1 |= buff_data_out[ 3 ];
        temp_2 <<= 8;
        temp_2 |= buff_data_out[ byte_indx + 2 ];

        if ( data_width > 1 )
        {
            temp_1 <<= 8;
            temp_1 |= buff_data_out[ 4 ];
            temp_2 <<= 8;
            temp_2 |= buff_data_out[ byte_indx + 3 ];
        }
    }
    *data_ch_0 = temp_1;
    *data_ch_1 = temp_2;
    
    return data_width;
}

void pwrmeter2_get_data ( pwrmeter2_t *ctx, int32_t *voltage_data, int32_t *current_data, uint32_t *power_data )
{
    int32_t volt_val;
    int32_t curr_val;
    float temp;
    uint32_t ch_0_data;
    uint32_t ch_1_data;
    uint8_t data_size;
    uint32_t chann_mask;
    uint32_t chann_resol;
    uint32_t sign_check;
    uint32_t add_bit;
    int32_t curr_val_abs;
    int32_t volt_val_abs;
    
    data_size = pwrmeter2_read_conv_data( ctx, &ch_0_data, &ch_1_data );
    
    switch ( data_size )
    {
        case 0 :
        {
            chann_mask = 0x0000FFFF;
            chann_resol = 32768;
            sign_check = 0x00008000;
            add_bit = 1;
        break;
        }
        case 1 :
        {
            chann_mask = 0x00FFFFFF;
            chann_resol = 8388608;
            sign_check = 0x00800000;
            add_bit = 1;
        break;
        }
        case 2 :
        {
            chann_mask = 0xFFFFFF00;
            chann_resol = 2147483648;
            sign_check = 0x80000000;
            add_bit = 0x00000100;
        break;
        }
        case 3 :
        {
            chann_mask = 0xFFFFFFFF;
            chann_resol = 8388608;
            sign_check = 0xFF000000;
            add_bit = 1;
        break;
        }
        default :
        {
        break;
        }
    }
    
    if ( ch_0_data & sign_check )
    {
        ch_0_data = ~ch_0_data;
        ch_0_data &= chann_mask;
        ch_0_data += add_bit;
        temp = ch_0_data;
        temp *= ( -1.0 );
        temp /= chann_resol;
        temp *= 48000.0;
        volt_val = temp;
        volt_val_abs = volt_val * ( -1 );
    }
    else
    {
        temp = ch_0_data;
        temp /= chann_resol;
        temp *= 48000.0;
        volt_val = temp;
        volt_val_abs = volt_val;
    }
    
    if ( ch_1_data & sign_check )
    {
        ch_1_data = ~ch_1_data;
        ch_1_data &= chann_mask;
        ch_1_data += add_bit;
        temp = ch_1_data;
        temp /= chann_resol;
        temp *= 40000.0;
        curr_val = temp;
        curr_val_abs = curr_val;
    }
    else
    {
        temp = ch_1_data;
        temp /= chann_resol;
        temp *= 40000.0;
        temp *= ( -1.0 );
        curr_val = temp;
        curr_val_abs = curr_val * ( -1 );
    }
    
    *voltage_data = volt_val;
    *current_data = curr_val;
    *power_data = ( volt_val_abs * curr_val_abs ) / 1000;
}

void pwrmeter2_reset( pwrmeter2_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1sec( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t pwrmeter2_get_modulator_1 ( pwrmeter2_t *ctx )
{
    uint8_t mod_1;

    mod_1 = digital_in_read( &ctx->md1 );

    if ( mod_1 == 1 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t pwrmeter2_get_modulator_0 ( pwrmeter2_t *ctx )
{   
    uint8_t mod_0;

    mod_0 = digital_in_read( &ctx->md0 );

    if ( mod_0 == 1 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t pwrmeter2_check_ready_pin ( pwrmeter2_t *ctx )
{
    uint8_t crp;

    crp = digital_in_read( &ctx->dr );
    
    if ( crp == 1 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ------------------------------------------------------------------------- END


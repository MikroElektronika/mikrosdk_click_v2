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

#include "adc6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC6_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t adc6_get_bytes_number ( adc6_t* ctx, const uint8_t reg_address );

static uint8_t adc6_check_data_ready ( adc6_t* ctx );

static void transfer_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc6_cfg_setup ( adc6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->syn = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ADC6_RETVAL adc6_init ( adc6_t *ctx, adc6_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC6_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
    {
        return ADC6_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC6_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->syn, cfg->syn );

    return ADC6_OK;

}

void adc6_default_cfg ( adc6_t* ctx )
{
    adc6_reset_device( ctx );
    adc6_write_reg( ctx , ADC6_CONFIG_0_REG, ADC6_CONFIG_ENABLE_BIPOLAR_OP |  
                          ADC6_CONFIG_ENABLE_BUFFER_ON_AINP |  
                          ADC6_CONFIG_ENABLE_BUFFER_ON_AINM );
    adc6_write_reg( ctx, ADC6_CHANNEL_0_REG, ADC6_ENABLE_CHANNEL | 
                         ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN1 );
    adc6_write_reg( ctx, ADC6_CONTROL_REG, ADC6_CONTROL_DATA_STATUS_ENABLE | 
                         ADC6_CONTROL_DOUT_PIN_ENABLE |
                         ADC6_CONTROL_INTERNAL_REFERENCE_VOLTAGE_ENABLE |
                         ADC6_CONTROL_FULL_POWER_MODE );
}

void adc6_write_reg ( adc6_t* ctx, const uint8_t register_address, const uint32_t transfer_data )
{
    uint8_t buffer_data[ 4 ] = { 0 };
    uint8_t n_bytes = 0;

    if ( register_address & 0xC0 )
    {
        return;
    }
    buffer_data[ 0 ] = register_address;

    n_bytes = adc6_get_bytes_number( ctx, register_address );

    if ( n_bytes == 2 )
    {
        if ( transfer_data > 0x0000FFFF )
        {
            return;
        }
        buffer_data[ 1 ] |= transfer_data >> 8;
        buffer_data[ 2 ] |= transfer_data;
    }
    else if ( n_bytes == 3 )
    {
        if ( transfer_data > 0x00FFFFFF )
        {
            return;
        }
        buffer_data[ 1 ] |= ( transfer_data >> 16 );
        buffer_data[ 2 ] |= ( ( transfer_data >> 8 ) & 0x000000FF );
        buffer_data[ 3 ] |= transfer_data;
    }
    n_bytes++;

    spi_master_select_device( ctx->chip_select );
    transfer_delay( );

    spi_master_write( &ctx->spi, buffer_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
    transfer_delay( );
}

uint32_t adc6_read_reg ( adc6_t *ctx, const uint8_t register_address )
{
    uint8_t buffer_data[ 3 ] = { 0 };
    uint8_t tx_buf[ 1 ];
    uint8_t n_bytes = 0;
    uint32_t return_value = 0;

    if ( register_address & 0xC0 )
    {
        return 1;
    }
    tx_buf[ 0 ] = ( 0x40 | register_address );

    n_bytes = adc6_get_bytes_number( ctx, register_address );

    spi_master_select_device( ctx->chip_select );
    transfer_delay( );

    spi_master_write_then_read( &ctx->spi, tx_buf, 1, buffer_data, n_bytes );

    spi_master_deselect_device( ctx->chip_select );
    transfer_delay( );

    if ( n_bytes == 1 )
    {
        return_value = buffer_data[ 0 ];
    }
    else if ( n_bytes == 2 )
    {
        return_value = buffer_data[ 0 ];
        return_value <<= 8;
        return_value |= buffer_data[ 1 ];
    }
    else
    {
        return_value = buffer_data[ 0 ];
        return_value <<= 8;
        return_value |= buffer_data[ 1 ];
        return_value <<= 8;
        return_value |= buffer_data[ 2 ];
    }

    return return_value;
}

uint32_t adc6_continuous_read_data ( adc6_t *ctx )
{
    uint8_t buffer_data[ 3 ] = { 0 };
    uint32_t return_value = 0;
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = ADC6_DUMMY;

    spi_master_select_device( ctx->chip_select );
    transfer_delay( );

    spi_master_write_then_read( &ctx->spi, tx_buf, 1, buffer_data, 3 );

    spi_master_deselect_device( ctx->chip_select );

    transfer_delay( );

    return_value = buffer_data[ 0 ];
    return_value <<= 8;
    return_value |= buffer_data[ 1 ];
    return_value <<= 8;
    return_value |= buffer_data[ 2 ];

    return return_value;
}

uint32_t adc6_get_adc_data ( adc6_t* ctx, const uint8_t mode )
{
    uint32_t data_value = 0;
    uint8_t ready_bit = 0;

    if ( mode == ADC6_SINGLE_GET_DATA_MODE )
    {
        ready_bit = adc6_check_data_ready( ctx );
        while ( ready_bit )
        {
            ready_bit = adc6_check_data_ready( ctx );
        }

        data_value = adc6_read_reg( ctx, ADC6_DATA_REG );
    }
    else
    {
        data_value = adc6_continuous_read_data( ctx );
    }

    return data_value;
}

void adc6_reset_device ( adc6_t* ctx )
{
    digital_out_low( &ctx->syn );
    transfer_delay( );
    digital_out_high( &ctx->syn );
    transfer_delay( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void transfer_delay ( void )
{
    Delay_10us( );
}

static uint8_t adc6_check_data_ready ( adc6_t* ctx )
{
    uint8_t ready_check = 0;

    ready_check = adc6_read_reg( ctx, ADC6_COMMUNICATION_AND_STATUS_REG );
    if ( ready_check & 0x80 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static uint8_t adc6_get_bytes_number ( adc6_t* ctx, const uint8_t reg_address )
{
    if ( reg_address > 0x38 )
    { 
        return 0;
    }

    switch ( reg_address )
    {
        case 0x00:
        {
            return 1;
            break;
        }
        case 0x01:
        {
            return 2;
            break;
        }
        case 0x02:
        {
            return 3;
            break;
        }
        case 0x03:
        {
            return 3;
            break;
        }
        case 0x04:
        {
            return 3;
            break;
        }
        case 0x05:
        {
            return 1;
            break;
        }
        case 0x06:
        {
            return 3;
            break;
        }
        case 0x07:
        {
            return 3;
            break;
        }
        case 0x08:
        {
            return 1;
            break;
        }
        case 0x09:
        {
            return 2;
            break;
        }
        case 0x0A:
        {
            return 2;
            break;
        }
        case 0x0B:
        {
            return 2;
            break;
        }
        case 0x0C:
        {
            return 2;
            break;
        }
        case 0x0D:
        {
            return 2;
            break;
        }
        case 0x0E:
        {
            return 2;
            break;
        }
        case 0x0F:
        {
            return 2;
            break;
        }
        case 0x10:
        {
            return 2;
            break;
        }
        case 0x11:
        {
            return 2;
            break;
        }
        case 0x12:
        {
            return 2;
            break;
        }
        case 0x13:
        {
            return 2;
            break;
        }
        case 0x14:
        {
            return 2;
            break;
        }
        case 0x15:
        {
            return 2;
            break;
        }
        case 0x16:
        {
            return 2;
            break;
        }
        case 0x17:
        {
            return 2;
            break;
        }
        case 0x18:
        {
            return 2;
            break;
        }
        case 0x19:
        {
            return 2;
            break;
        }
        case 0x1A:
        {
            return 2;
            break;
        }
        case 0x1B:
        {
            return 2;
            break;
        }
        case 0x1C:
        {
            return 2;
            break;
        }
        case 0x1D:
        {
            return 2;
            break;
        }
        case 0x1E:
        {
            return 2;
            break;
        }
        case 0x1F:
        {
            return 2;
            break;
        }
        case 0x20:
        {
            return 2;
            break;
        }
        default:
        {
            return 3;
            break;
        }
    }
}

// ------------------------------------------------------------------------- END


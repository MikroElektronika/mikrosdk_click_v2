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

#include "adc4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC4_DUMMY 0
#define READ_OPERATION  0
#define WRITE_OPERATION 1

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t calc_size ( const uint8_t reg_addr, uint8_t rw_operation );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc4_cfg_setup ( adc4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->err = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000;
}

ADC4_RETVAL adc4_init ( adc4_t *ctx, adc4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADC4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC4_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Input pins

    digital_in_init( &ctx->err, cfg->err );

    return ADC4_OK;
}

void adc4_default_cfg ( adc4_t *ctx )
{
    adc4_set_config( ctx, ADC4_CH_REG_BASE, ADC4_CH_EN);
    adc4_set_config( ctx, ADC4_MODE_REG, ADC4_MODE_INT_REF_AND_SING_CYC_EN );
    adc4_set_config( ctx, ADC4_IFACE_MODE_REG, ADC4_IFACE_MODE_CRC_DIS );
    adc4_set_config( ctx, ADC4_GPIO_CONFIG_REG, ADC4_CFG_SYNC_EN );
    adc4_set_config( ctx, ADC4_SETUP_CONFIGURATION_REG, 0x1320);
}

void adc4_generic_transfer ( adc4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t adc4_write_reg ( adc4_t *ctx, const uint8_t reg_address, uint8_t *value )
{
    uint8_t tmp    = reg_address & 0xBF;
    uint8_t n_bytes = calc_size( reg_address, WRITE_OPERATION );

    if ( 0 != n_bytes )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, &tmp, 1 );
        spi_master_write( &ctx->spi, value, n_bytes );
        spi_master_deselect_device( ctx->chip_select );

        Delay_10us( );
    }

    return n_bytes;
}

uint8_t adc4_read_reg ( adc4_t *ctx, const uint8_t reg_address, uint8_t *value )
{
    uint8_t tmp = reg_address | 0x40;
    uint8_t n_bytes = calc_size( reg_address, READ_OPERATION );

    if ( 0 != n_bytes )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_write_then_read( &ctx->spi, &tmp, 1, value, n_bytes );
        spi_master_deselect_device( ctx->chip_select );   

        Delay_10us( );
    }

    return n_bytes;
}

void adc4_reset ( adc4_t *ctx )
{
    uint8_t tmp[ 8 ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t i;
    
    spi_master_select_device( ctx->chip_select );
    for( i = 0; i > 7; i++ )
    {
        spi_master_write( &ctx->spi, &tmp[ i ], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t adc4_get_err_pin ( adc4_t *ctx )
{
    return digital_in_read( &ctx->err );
}

void adc4_get_config ( adc4_t *ctx, uint8_t reg_address, uint16_t *value )
{
    uint8_t tmp [ 2] = { 0 };

    if ( 2 == calc_size( reg_address, READ_OPERATION ) )
    {
        adc4_read_reg( ctx, reg_address, tmp );
    }
}

void adc4_set_config ( adc4_t *ctx, const uint8_t reg_address, uint16_t value )
{
    uint8_t tmp[ 2 ] = { 0 };

    tmp[ 0 ] = value >> 8;
    tmp[ 1 ] = value & 0x00FF;

    if ( 2 == calc_size( reg_address, WRITE_OPERATION ) )
    {
        adc4_write_reg( ctx, reg_address, tmp );
    }
}

uint32_t adc4_get_data ( adc4_t *ctx )
{
    uint16_t cnt = 0;
    uint8_t  rdy = 0;
    uint32_t value = 0;
    uint8_t  tmp[ 3 ] = { 0 };

    // Wait RDY - Polling - !!! Blocking !!!

    while  ( adc4_read_reg ( ctx, ADC4_STATUS_REG, &rdy ) )
    {
        if ( 0 == ( rdy & ADC4_STATUS_RDY ) )
        {
            break;
        }

        if ( cnt++ >= ctx->w_dog )
        {
            return 0;
        }
    }

    adc4_read_reg( ctx, ADC4_DATA_REG, tmp );

    value = tmp[ 0 ];
    value <<= 8;
    value |= tmp[ 1 ];
    value <<= 8;
    value |= tmp[ 2 ];
    
    ctx->sing_bit = ( value & 0x00800000 ) >> 23;
    
    if ( ctx->sing_bit == 1 )
    {
        return ( value & 0x007FFFFF );
    }
    else
    {
        value = ~value;
        value &= 0x007FFFFF;
        return value;
    }
}

uint16_t adc4_get_voltage ( adc4_t *ctx, const float ref_voltage )
{
    uint32_t raw = 0;
    float res = 0;
    uint16_t ret_val = 0;
      
    raw = adc4_get_data( ctx );

    res = raw * ref_voltage;
    res /= ADC4_RESOLUTION;
    res *= 1000;
    
    ret_val = res;

    return ret_val;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t calc_size ( const uint8_t reg_addr, uint8_t rw_operation )
{
    switch( reg_addr )
    {
        // Status
        case 0 :
        {
            // RO register
            if ( READ_OPERATION == rw_operation )
            { 
                return 1; 
            }
            else
            {
                return 0;
            }
        }
        // Mode
        case 1 :
        {
            return 2; 
        }
        // Interface mode
        case 2 :
        {
            return 2; 
        }
        // Register Check
        case 3 :
        {
            // RO register
            if ( READ_OPERATION == rw_operation )
            {
                return 3; 
            }
            else
            {
                return 0;
            }
        }
        // Data
        case 4 :
        {
            // RO register
            if ( READ_OPERATION == rw_operation )
            {
                return 3; 
            }
            else
            {
                return 0;
            }
        }
        // Configuration
        case 6 :
        {
            return 2; 
        }
        // ID
        case 7 :
        {
            // RO register
            if ( READ_OPERATION == rw_operation )
            {
                return 2; 
            }
            else
            {
                return 0;
            }
        }
        default :
        {
            // Channel
            if ( ( 0x10 <= reg_addr ) && ( 0x1F >= reg_addr ) )
            {
                return 2;
            }
            // Setup Config
            else if ( ( 0x20 <= reg_addr ) && (0x27 >= reg_addr ) )
            {  
                return 2;  
            }  
            // Filter Config  
            else if ( ( 0x28 <= reg_addr ) && (0x2F >= reg_addr ) )
            {  
                return 2;  
            }  
            // Offset  
            else if ( ( 0x30 <= reg_addr ) && (0x37 >= reg_addr ) )
            {  
                return 3;  
            }  
            // Gain  
            else if ( ( 0x38 <= reg_addr ) && (0x3F >= reg_addr ) )
            {
                return 3;
            }
            else 
            {
                return 0;
            }
        }
    }
}

// ------------------------------------------------------------------------- END


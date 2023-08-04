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

#include "dac7.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DAC7_DUMMY 0

#define DAC7_MASK_BIT_12_BITS          0x0FFF

#define DAC7_MASK_DATA                 0xFF

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// Check command definition function
uint8_t dac7_check_def_cmd ( dac7_t *ctx, uint8_t def_cmd );

// Check address command function
uint8_t dac7_check_addr_cmd ( dac7_t *ctx, uint8_t addr_cmd );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac7_cfg_setup ( dac7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

DAC7_RETVAL dac7_init ( dac7_t *ctx, dac7_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DAC7_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    return DAC7_OK;
}

void dac7_write_data ( dac7_t *ctx, uint8_t def_cmd, uint8_t addr_cmd, uint16_t write_data )
{
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ]  = ( uint8_t ) ( def_cmd & DAC7_MASK_BIT_COMMAND );
    tx_buf[ 0 ] |= ( uint8_t ) ( addr_cmd & DAC7_MASK_BIT_ADDRESS );
    
    tx_buf[ 1 ] = ( uint8_t ) ( ( ( write_data & DAC7_MASK_BIT_12_BITS ) >> 4 ) & DAC7_MASK_BIT_LBS );
    tx_buf[ 2 ] = ( uint8_t ) ( ( write_data & DAC7_MASK_BIT_12_BITS ) << 4 );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );  
}


DAC7_RETVAL_T dac7_set_channel ( dac7_t *ctx, uint8_t set_cmd, uint8_t addr_ch, uint16_t write_data )
{
    if ( dac7_check_def_cmd ( ctx, set_cmd ) )
    {
        if ( dac7_check_addr_cmd ( ctx, addr_ch ) )
        {
            dac7_write_data( ctx, set_cmd, addr_ch, write_data );
            
            return DAC7_SUCCESS;
        }
        else
        {
            return DAC7_ERROR;
        }
    }
    else
    {
        return DAC7_ERROR;
    }
}

DAC7_RETVAL_T dac7_set_ch_voltage ( dac7_t *ctx, uint8_t addr_ch, uint16_t vol_val, uint16_t v_ref_mv )
{
    uint16_t tmp = 0;
    
    if ( ( v_ref_mv == DAC7_VREF_4096mV ) || ( v_ref_mv == DAC7_VREF_5000mV ) )
    {
        if ( ( vol_val >= 0 ) || ( vol_val < v_ref_mv ) )
        {
            tmp = ( uint16_t ) ( ( ( uint32_t ) vol_val * 4095 ) / v_ref_mv  );
        
            if ( dac7_check_addr_cmd ( ctx, addr_ch ) )
            {
                dac7_set_channel( ctx, DAC7_COMMAND_WRITE_UPDATE_CHANNEL, addr_ch, tmp );

                return DAC7_SUCCESS;
            }
            else
            {
                return DAC7_ERROR;
            }
        }
        else
        {
            return DAC7_ERROR;
        }
    }
    else
    {
        return DAC7_ERROR;
    }
}

DAC7_RETVAL_T dac7_update_channel ( dac7_t *ctx, uint8_t addr_ch, uint16_t ch_data )
{
    if ( dac7_check_addr_cmd ( ctx, addr_ch ) )
    {
        dac7_write_data( ctx, DAC7_COMMAND_WRITE_UPDATE_CHANNEL, addr_ch, ch_data );
        
        return DAC7_SUCCESS;
    }
    else
    {
        return DAC7_ERROR;
    }
}

DAC7_RETVAL_T dac7_set_power ( dac7_t *ctx, uint8_t pwr_en, uint8_t sel_ch )
{
    uint8_t tx_buf[ 3 ];
    
    if ( sel_ch > DAC7_MASK_BIT_SEL_CHANNEL )
    {
        return DAC7_ERROR;
    }
    else
    {
        tx_buf[ 0 ]  = DAC7_COMMAND_POWER_UPDOWN;
        tx_buf[ 1 ]  = DAC7_DONT_CARE_COMMAND;
        tx_buf[ 2 ]  = ( pwr_en & DAC7_MASK_BIT_POWERMODE );
        tx_buf[ 2 ] |= ( sel_ch & DAC7_MASK_BIT_SEL_CHANNEL );
        
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, 3 );
        spi_master_deselect_device( ctx->chip_select );  
        
        return DAC7_SUCCESS;
    }
}

DAC7_RETVAL_T dac7_sw_reset ( dac7_t *ctx )
{
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ] = DAC7_COMMAND_RESET;
    tx_buf[ 1 ] = DAC7_DONT_CARE_COMMAND;
    tx_buf[ 2 ] = DAC7_SW_RST_COMMAND;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    
    return DAC7_SUCCESS;
}

DAC7_RETVAL_T dac7_set_ldac ( dac7_t *ctx, uint8_t sel_ch )
{
    uint8_t tx_buf[ 3 ];

    if ( sel_ch > DAC7_MASK_BIT_SEL_CHANNEL )
    {
        return DAC7_ERROR;
    }
    else
    {
        tx_buf[ 0 ] = DAC7_COMMAND_SET_LDAC;
        tx_buf[ 1 ] = DAC7_DONT_CARE_COMMAND;
        tx_buf[ 2 ] = sel_ch & DAC7_MASK_BIT_SEL_CHANNEL;
    
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, 3 );
        spi_master_deselect_device( ctx->chip_select );  

        return DAC7_SUCCESS;
    }
}

DAC7_RETVAL_T dac7_set_internal_reference ( dac7_t *ctx, uint8_t int_ref_en )
{
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ] = DAC7_COMMAND_REFERENCE_ONOFF;
    tx_buf[ 1 ] = DAC7_DONT_CARE_COMMAND;
    tx_buf[ 2 ] = int_ref_en & DAC7_MASK_BIT_0;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    
    return DAC7_SUCCESS;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

uint8_t dac7_check_def_cmd ( dac7_t *ctx, uint8_t def_cmd )
{
    if ( def_cmd == DAC7_SET_MODE_INPUT     ||
         def_cmd == DAC7_SET_MODE_INPUT_DAC ||
         def_cmd == DAC7_SET_MODE_INPUT_DAC_ALL )
    {
        return DAC7_SUCCESS;
    }
    else
    {
        return DAC7_ERROR;
    }
}

uint8_t dac7_check_addr_cmd ( dac7_t *ctx, uint8_t addr_cmd )
{
    if ( addr_cmd == DAC7_ADDRESS_CHANNEL_A ||
         addr_cmd == DAC7_ADDRESS_CHANNEL_B ||
         addr_cmd == DAC7_ADDRESS_CHANNEL_C ||
         addr_cmd == DAC7_ADDRESS_CHANNEL_D ||
         addr_cmd == DAC7_ADDRESS_CHANNEL_ALL )
    {
        return DAC7_SUCCESS;
    }
    else
    {
        return DAC7_ERROR;
    }
}

// ------------------------------------------------------------------------- END


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

#include "ecg3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ECG3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t check_addr ( uint8_t reg_addr );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ecg3_cfg_setup ( ecg3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->clk     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

ECG3_RETVAL ecg3_init ( ecg3_t *ctx, ecg3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ECG3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ECG3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ECG3_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins   
    digital_out_init( &ctx->clk, cfg->clk );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ECG3_OK;
}

void ecg3_default_cfg ( ecg3_t *ctx )
{
    ecg3_write_reg( ctx, ECG3_CNFG_GEN_REG, ECG3_FMSTR_32768HZ_ECG_512HZ | ECG3_ECG_CHANN_EN | ECG3_DCLOFF_EN | ECG3_RBIAS_100M_OHM | ECG3_RBIASP_EN | ECG3_RBIASN_EN );
    ecg3_write_reg( ctx, ECG3_CNFG_CAL_REG, ECG3_VCAL_EN | ECG3_VMODE_BIPOL | ECG3_VMAG_500MICROV );
    ecg3_write_reg( ctx, ECG3_CNFG_EMUX_REG, ECG3_ECGP_EN | ECG3_ECGN_EN | ECG3_ECGP_CAL_VCALP | ECG3_ECGN_CAL_VCALN );
    ecg3_write_reg( ctx, ECG3_CNFG_ECG_REG, 0x800000 | ECG3_DHPF_500MILIHZ | ECG3_DLPF_40HZ );
    ecg3_write_reg( ctx, ECG3_CNFG_RTOR1_REG, ECG3_WNDW_12 | ECG3_RRGAIN_AUTO_SCALE | ECG3_RTOR_EN | ECG3_PAVG_8 | 0x000600 );
}

void ecg3_generic_transfer ( ecg3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );    
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_1us( );    
}

uint8_t ecg3_write_reg ( ecg3_t *ctx, uint8_t reg_addr, uint32_t data_in )
{
    uint8_t temp_data[ 4 ];
    uint8_t addr_check;

    addr_check = check_addr( reg_addr );
    if ( addr_check )
    {
        return addr_check;
    }
    
    temp_data[ 0 ] = reg_addr << 1;
    temp_data[ 1 ] = data_in >> 16;
    temp_data[ 2 ] = data_in >> 8;
    temp_data[ 3 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp_data, 4 );
    spi_master_deselect_device( ctx->chip_select );  
    
    return addr_check;
}

uint8_t ecg3_read_reg ( ecg3_t *ctx, uint8_t reg_addr, uint32_t *data_out )
{
    uint8_t temp_in[ 1 ];
    uint8_t temp_out[ 4 ];
    uint8_t addr_check;
    
    addr_check = check_addr( reg_addr );
    if ( addr_check )
    {
        return addr_check;
    }
    
    temp_in[ 0 ] = reg_addr << 1;
    temp_in[ 0 ] |= 1;
    
    ecg3_generic_transfer( ctx, temp_in, 1, temp_out, 4 );

    *data_out = temp_out[ 1 ];
    *data_out <<= 8;
    *data_out |= temp_out[ 2 ];
    *data_out <<= 8;
    *data_out |= temp_out[ 3 ];
    
    return addr_check;
}

uint8_t ecg3_check_status ( ecg3_t *ctx, uint32_t bit_mask )
{
    uint32_t stat_data;
    
    ecg3_read_reg( ctx, ECG3_STAT_REG, &stat_data );
    
    if ( stat_data & bit_mask)
    {
        return ECG3_INT_OCCURRED;
    }
    
    return ECG3_INT_NOT_OCCURRED;
}

void ecg3_sw_reset ( ecg3_t *ctx )
{
    ecg3_write_reg( ctx, ECG3_SW_RST_REG, ECG3_SW_RST_CMD );
}

void ecg3_fifo_reset ( ecg3_t *ctx )
{
    ecg3_write_reg( ctx, ECG3_FIFO_RST_REG, ECG3_FIFO_RST_CMD );
}
 
void ecg3_sync ( ecg3_t *ctx )
{
    ecg3_write_reg( ctx, ECG3_SYNC_REG, ECG3_SYNCH_CMD );
}

void ecg3_get_ecg ( ecg3_t *ctx, uint32_t *out_ecg )
{
    ecg3_read_reg( ctx, ECG3_ECG_FIFO_REG, out_ecg );
    *out_ecg >>= 6;
}

void ecg3_get_rtor ( ecg3_t *ctx, uint16_t *out_hr, uint16_t *out_rr )
{
    uint32_t rtor_temp;
    float res;
    uint16_t res_int;

    ecg3_read_reg( ctx, ECG3_RTOR_REG, &rtor_temp );
    rtor_temp >>= 10;
    res = 60 / ( ( float )rtor_temp * 0.008 );
    res_int = res;
    *out_hr = res_int;

    res_int = ( uint16_t )rtor_temp * 8;
    *out_rr = res_int; 
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t check_addr ( uint8_t reg_addr )
{
    switch ( reg_addr )
    {
        case ECG3_NO_OP_REG :
        {
            return ECG3_OK;
        }
        case ECG3_STAT_REG :
        {
            return ECG3_OK;
        }
        case ECG3_EN_INT_REG :
        {
            return ECG3_OK;
        }
        case ECG3_EN_INT2_REG :
        {
            return ECG3_OK;
        }
        case ECG3_MNGR_INT_REG :
        {
            return ECG3_OK;
        }
        case ECG3_MNGR_DYN_REG :
        {
            return ECG3_OK;
        }
        case ECG3_SW_RST_REG :
        {
            return ECG3_OK;
        }
        case ECG3_SYNC_REG :
        {
            return ECG3_OK;
        }
        case ECG3_FIFO_RST_REG :
        {
            return ECG3_OK;
        }
        case ECG3_INFO_REG :
        {
            return ECG3_OK;
        }
        case ECG3_CNFG_GEN_REG :
        {
            return ECG3_OK;
        }
        case ECG3_CNFG_CAL_REG :
        {
            return ECG3_OK;
        }
        case ECG3_CNFG_EMUX_REG :
        {
            return ECG3_OK;
        }
        case ECG3_CNFG_ECG_REG :
        {
            return ECG3_OK;
        }
        case ECG3_CNFG_RTOR1_REG :
        {
            return ECG3_OK;
        }
        case ECG3_CNFG_RTOR2_REG :
        {
            return ECG3_OK;
        }
        case ECG3_ECG_FIFO_BURST_REG :
        {
            return ECG3_OK;
        }
        case ECG3_ECG_FIFO_REG :
        {
            return ECG3_OK;
        }
        case ECG3_RTOR_REG :
        {
            return ECG3_OK;
        }
        case ECG3_NO_OP2_REG :
        {
            return ECG3_OK;
        }
        default :
        {
            return ECG3_WRONG_ADDR;
        }
    }
}

// ------------------------------------------------------------------------- END


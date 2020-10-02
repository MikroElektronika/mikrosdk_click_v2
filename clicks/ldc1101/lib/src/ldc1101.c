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

#include "ldc1101.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LDC1101_DUMMY 0

#define LDC1101_DEVICE_ERROR     0x01
#define LDC1101_DEVICE_OK        0x00
#define LDC1101_SPI_READ         0x80

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ldc1101_cfg_setup ( ldc1101_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

LDC1101_RETVAL ldc1101_init ( ldc1101_t *ctx, ldc1101_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = LDC1101_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return LDC1101_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, LDC1101_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->pwm, cfg->pwm );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LDC1101_OK;
}

void ldc1101_default_cfg ( ldc1101_t *ctx )
{
    // Click default configuration
    
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_RP_MEASUREMENT_DYNAMIC_RANGE, 
                                 LDC1101_RP_SET_RP_MIN_0_75KOh );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_1, 
                                 LDC1101_TC1_C1_3pF | 
                                 LDC1101_TC1_R1_212_7kOhm );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_2, 
                                 LDC1101_TC2_C2_12pF | 
                                 LDC1101_TC2_R2_426_4kOhm );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_RP_L_CONVERSION_INTERVAL, 
                                 LDC1101_DIG_CFG_RESP_TIME_384s );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_ADDITIONAL_DEVICE, 
                                 LDC1101_ALT_CFG_SHUTDOWN_DISABLE | 
                                 LDC1101_ALT_CFG_L_OPTIMAL_DISABLED );                 
    ldc1101_generic_write ( ctx, LDC1101_REG_RP_THRESH_H_MSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_RP_THRESH_L_LSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_RP_THRESH_L_MSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_INTB_MODE, 
                                 LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_POWER_STATE, 
                                 LDC1101_FUNC_MODE_SLEEP_MODE );
    ldc1101_generic_write ( ctx, LDC1101_REG_AMPLITUDE_CONTROL_REQUIREMENT, 
                                 LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE );
    ldc1101_generic_write ( ctx, LDC1101_REG_L_THRESH_HI_LSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_L_THRESH_HI_MSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_L_THRESH_LO_LSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_L_THRESH_LO_MSB, 
                                 LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_LHR_RCOUNT_LSB, 
                                 LDC1101_RES_L_MEAS_REF_CNT_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_LHR_RCOUNT_MSB, 
                                 LDC1101_RES_L_MEAS_REF_CNT_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_LHR_OFFSET_LSB, 
                                 LDC1101_RES_OFF_L_MEAS_REF_CNT_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_LHR_OFFSET_MSB, 
                                 LDC1101_RES_OFF_L_MEAS_REF_CNT_DEF_CFG );
    ldc1101_generic_write ( ctx, LDC1101_REG_CFG_LHR, 
                                 LDC1101_SENSOR_FREQ_DIV_NO );
    
    // Work configuration
    
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_RP_MEASUREMENT_DYNAMIC_RANGE, 
                                LDC1101_RP_SET_RP_MAX_24KOhm | 
                                LDC1101_RP_SET_RP_MIN_1_5KOhm );
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_1, 
                                LDC1101_TC1_C1_0_75pF | 
                                LDC1101_TC1_R1_21_1kOhm );
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_2, 
                                LDC1101_TC2_C2_3pF | 
                                LDC1101_TC2_R2_30_5kOhm );
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_RP_L_CONVERSION_INTERVAL, 
                                LDC1101_DIG_CFG_MIN_FREQ_118kHz | 
                                LDC1101_DIG_CFG_RESP_TIME_768s );
    
    ldc1101_set_power_mode( ctx, LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE );
}

void ldc1101_generic_transfer 
( 
    ldc1101_t *ctx, 
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

void ldc1101_generic_write ( ldc1101_t *ctx, uint8_t reg_addr, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg_addr;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );    
}

uint8_t ldc1101_generic_read ( ldc1101_t *ctx, uint8_t reg_addr )
{
    uint8_t tx_buf;
    uint8_t rx_buf[ 2 ];

    tx_buf = reg_addr;
    tx_buf |= LDC1101_SPI_READ;

    ldc1101_generic_transfer( ctx, &tx_buf, 1, rx_buf, 1 );
    
    return rx_buf[ 0 ];
}

void ldc1101_set_power_mode ( ldc1101_t *ctx, uint8_t pwr_mode )
{
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_POWER_STATE, pwr_mode );
}

void ldc1101_go_to_l_mode ( ldc1101_t *ctx )
{
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_ADDITIONAL_DEVICE, 
                                LDC1101_ALT_CFG_L_OPTIMAL_ENABLE );
    ldc1101_generic_write( ctx, LDC1101_REG_AMPLITUDE_CONTROL_REQUIREMENT, 
                                LDC1101_CONTINUES_CONVERT );
}

void ldc1101_go_to_r_mode ( ldc1101_t *ctx )
{
    ldc1101_generic_write( ctx, LDC1101_REG_CFG_ADDITIONAL_DEVICE, 
                                LDC1101_ALT_CFG_R_OPTIMAL_ENABLE );
    ldc1101_generic_write( ctx, LDC1101_REG_AMPLITUDE_CONTROL_REQUIREMENT, 
                                LDC1101_REQ_AMPLINTUDE_REGUL_CONVERT );
}

uint8_t ldc1101_get_status ( ldc1101_t *ctx )
{
    uint8_t stat_val;
    
    stat_val = ldc1101_generic_read( ctx, LDC1101_REG_RP_L_MEASUREMENT_STATUS );
    
    return stat_val;
}

uint16_t ldc1101_get_rp_data ( ldc1101_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t res_val;
    
    rx_buf[ 0 ] = ldc1101_generic_read( ctx, LDC1101_REG_RP_DATA_MSB );
    rx_buf[ 1 ] = ldc1101_generic_read( ctx, LDC1101_REG_RP_DATA_LSB );

    res_val = rx_buf[ 0 ];
    res_val <<= 8;
    res_val |= rx_buf[ 1 ];
    
    return res_val;
}

uint16_t ldc1101_get_l_data ( ldc1101_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t res_val;
    
    rx_buf[ 0 ] = ldc1101_generic_read( ctx, LDC1101_REG_L_DATA_MSB );
    rx_buf[ 1 ] = ldc1101_generic_read( ctx, LDC1101_REG_L_DATA_LSB );

    res_val = rx_buf[ 0 ];
    res_val <<= 8;
    res_val |= rx_buf[ 1 ];
    
    return res_val;
}

uint8_t ldc1101_get_interrupt( ldc1101_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END


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

#include "pressure3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void pressure3_i2c_write ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure3_i2c_read ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure3_spi_write ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure3_spi_read ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure3_cfg_setup ( pressure3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PRESSURE3_I2C_ADDRESS;

    cfg->spi_speed = 100000; 
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_mode = SPI_MASTER_MODE_0;

    cfg->sel = PRESSURE3_MASTER_I2C;
}

PRESSURE3_RETVAL pressure3_init ( pressure3_t *ctx, pressure3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == PRESSURE3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed   = cfg->i2c_speed;
        i2c_cfg.scl     = cfg->scl;
        i2c_cfg.sda     = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return PRESSURE3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = pressure3_i2c_read;
        ctx->write_f = pressure3_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        spi_cfg.default_write_data = PRESSURE3_DUMMY;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  PRESSURE3_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE3_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = pressure3_spi_read;
        ctx->write_f = pressure3_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESSURE3_OK;
}

void pressure3_default_cfg ( pressure3_t *ctx )
{
    uint8_t write_data;

    write_data = PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_NO_AVB |
                 PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_NO_CMP | 
                 PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_IDLE |
                 PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_PRS_TMP;

    Delay_100ms( );
    
    pressure3_generic_write( ctx, PRESSURE3_REG_MEAS_CFG, &write_data, 1 );

    Delay_100ms( );
}

void pressure3_generic_write ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void pressure3_generic_read ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void pressure3_get_t_p_data ( pressure3_t *ctx, float *temperature, float *presure, pressure3_coeff_t *coeff_struct )
{
    float temp_buff;
    float press_buff;
    float temp_temp;
    uint8_t write_data;

    pressure3_get_coefficients ( ctx, coeff_struct );
    
    write_data = PRESSURE3_BIT_MASK_PM_RATE_1_PER_SEC | PRESSURE3_BIT_MASK_PM_PRC_2_PER_SEC;
    pressure3_generic_write( ctx, PRESSURE3_REG_PRS_CFG, &write_data, 1 );

    write_data = PRESSURE3_BIT_MASK_TMP_EXT_EXTERNAL_SENSOR |
                 PRESSURE3_BIT_MASK_TMP_RATE_1_PER_SEC | 
                 PRESSURE3_BIT_MASK_TMP_PRC_1_PER_SEC;
    pressure3_generic_write( ctx, PRESSURE3_REG_TMP_CFG, &write_data, 1 );

    write_data = PRESSURE3_BIT_MASK_CFG_REG_INT_HL_LOW | 
                 PRESSURE3_BIT_MASK_CFG_REG_INT_FIFO_DISABLE | 
                 PRESSURE3_BIT_MASK_CFG_REG_INT_TMP_DISABLE | 
                 PRESSURE3_BIT_MASK_CFG_REG_INT_PRS_DISABLE | 
                 PRESSURE3_BIT_MASK_CFG_REG_T_SHIFT_NO_SHIFT |
                 PRESSURE3_BIT_MASK_CFG_REG_P_SHIFT_NO_SHIFT | 
                 PRESSURE3_BIT_MASK_CFG_REG_FIFO_EN_DISABLE | 
                 PRESSURE3_BIT_MASK_CFG_REG_SPI_MODE_DISABLE;
    pressure3_generic_write( ctx, PRESSURE3_REG_CFG_REG, &write_data, 1 );

    write_data = PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_NO_AVB | 
                 PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_NO_CMP | 
                 PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_TMP;
    pressure3_generic_write( ctx, PRESSURE3_REG_MEAS_CFG, &write_data, 1 );

    temp_buff = ( float ) pressure3_get_measurement_data( ctx, PRESSURE3_REG_TMP_B2 );

    temp_buff /= 524288.0;
    temp_temp = temp_buff;
    temp_buff = ( ( ( ( float ) coeff_struct->coeff_c0 ) * 0.5 ) + ( temp_buff *
                   ( ( float ) coeff_struct->coeff_c1 ) ) ) * 0.45;
    *temperature = temp_buff;

    write_data = PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_NO_AVB | 
                 PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_NO_CMP | 
                 PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_PRS;
    pressure3_generic_write( ctx, PRESSURE3_REG_MEAS_CFG, &write_data, 1 );

    temp_buff = ( float ) pressure3_get_measurement_data( ctx, PRESSURE3_REG_PSR_B2 );
    temp_buff /= 1572864.0;
    temp_buff = ( float ) coeff_struct->coeff_c00 + temp_buff *
              ( ( float ) coeff_struct->coeff_c10 + temp_buff *
              ( ( float ) coeff_struct->coeff_c20 + ( temp_buff *
                ( float ) coeff_struct->coeff_c30 ) ) ) + temp_temp *
                ( float ) coeff_struct->coeff_c01 + temp_temp * temp_buff *
              ( ( float ) coeff_struct->coeff_c11 + ( temp_buff *
                ( float ) coeff_struct->coeff_c21 ) );
    *presure = temp_buff / 100.0;
}

void pressure3_get_coefficients ( pressure3_t *ctx, pressure3_coeff_t *coeff_struct )
{
    uint8_t temp_mbs;
    uint8_t temp_lbs;
    uint8_t temp_xlbs;
    uint32_t temp_data;

    temp_data = 0;

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C0_MBS, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C0_LBS_C1_MBS, &temp_lbs, 1 );
    temp_lbs &= 0xF0;
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;
    temp_data >>= 4;

    if ( temp_data > 2047 )
    {
       coeff_struct->coeff_c0 = temp_data - 4096;
    }
    else
    {
        coeff_struct->coeff_c0 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C0_LBS_C1_MBS, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C1_LBS, &temp_lbs, 1 );
    temp_mbs &= 0x0F;
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;

    if ( temp_data > 2047 )
    {
        coeff_struct->coeff_c1 = temp_data - 4096;
    }
    else
    {
        coeff_struct->coeff_c1 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C00_MBS, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C00_LSB, &temp_lbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C00_XLSB_C10_MSB, &temp_xlbs, 1 );
    temp_xlbs &= 0xF0;
    temp_xlbs >>= 4;
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;
    temp_data <<= 4;
    temp_data |= temp_xlbs;

    if ( temp_data > 524287 )
    {
        coeff_struct->coeff_c00 = temp_data - 1048576;
    }
    else
    {
        coeff_struct->coeff_c00 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C00_XLSB_C10_MSB, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C10_LSB, &temp_lbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C10_XLSB, &temp_xlbs, 1 );
    temp_mbs &= 0x0F;
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;
    temp_data <<= 8;
    temp_data |= temp_xlbs;

    if ( temp_data > 524287 )
    {
        coeff_struct->coeff_c10 = temp_data - 1048576;
    }
    else
    {
        coeff_struct->coeff_c10 = temp_data;
    }
    
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C01_MSB, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C01_LSB, &temp_lbs, 1 );
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;

    if ( temp_data > 32767 )
    {
        coeff_struct->coeff_c01 = temp_data - 65536;
    }
    else
    {
        coeff_struct->coeff_c01 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C11_MSB, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C11_LSB, &temp_lbs, 1 );
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;

    if ( temp_data > 32767 )
    {
        coeff_struct->coeff_c11 = temp_data - 65536;
    }
    else
    {
        coeff_struct->coeff_c11 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C20_MSB, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C20_LSB, &temp_lbs, 1 );
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;

    if ( temp_data > 32767 )
    {
        coeff_struct->coeff_c20 = temp_data - 65536;
    }
    else
    {
        coeff_struct->coeff_c20 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C21_MSB, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C21_LSB, &temp_lbs, 1 );
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;

    if ( temp_data > 32767 )
    {
        coeff_struct->coeff_c21 = temp_data - 65536;
    }
    else
    {
        coeff_struct->coeff_c21 = temp_data;
    }

    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C30_MSB, &temp_mbs, 1 );
    pressure3_generic_read( ctx, PRESSURE3_REG_COEF_C30_LSB, &temp_lbs, 1 );
    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;

    if ( temp_data > 32767 )
    {
        coeff_struct->coeff_c30 = temp_data - 65536;
    }
    else
    {
        coeff_struct->coeff_c30 = temp_data;
    }
}

int32_t pressure3_get_measurement_data ( pressure3_t *ctx, uint8_t mbs_reg_addr )
{
    uint8_t temp_mbs;
    uint8_t temp_lbs;
    uint8_t temp_xlbs;
    uint32_t temp_data;
    int32_t result;

    pressure3_generic_read( ctx, mbs_reg_addr, &temp_mbs, 1 );
    pressure3_generic_read( ctx, mbs_reg_addr + 1, &temp_lbs, 1 );
    pressure3_generic_read( ctx, mbs_reg_addr + 2, &temp_xlbs, 1 );

    temp_data = temp_mbs;
    temp_data <<= 8;
    temp_data |= temp_lbs;
    temp_data <<= 8;
    temp_data |= temp_xlbs;

    if ( temp_data > 8388607 )
    {
        result = temp_data - 16777216;
    }
    else
    {
        result = temp_data;
    }

    return result;
}

void pressure3_set_pressure_configuration ( pressure3_t *ctx, uint8_t press_config )
{
    pressure3_generic_write( ctx, PRESSURE3_REG_PRS_CFG, &press_config, 1 );
}

uint8_t pressure3_get_pressure_configuration ( pressure3_t *ctx )
{
    uint8_t temp_data;

    pressure3_generic_read( ctx, PRESSURE3_REG_PRS_CFG, &temp_data, 1 );
    
    return temp_data;
}

void pressure3_set_temperature_configuration ( pressure3_t *ctx, uint8_t temp_config )
{
    pressure3_generic_write( ctx, PRESSURE3_REG_TMP_CFG, &temp_config, 1 );
}

uint8_t pressure3_get_temperature_configuration ( pressure3_t *ctx )
{
    uint8_t temp_data;

    pressure3_generic_read( ctx, PRESSURE3_REG_TMP_CFG, &temp_data, 1 );

    return temp_data;
}

void pressure3_set_operating_mode( pressure3_t *ctx, uint8_t operation_mode )
{
    pressure3_generic_write( ctx, PRESSURE3_REG_MEAS_CFG, &operation_mode, 1 );
}

uint8_t pressure3_get_operating_mode ( pressure3_t *ctx )
{
    uint8_t temp_data;

    pressure3_generic_read( ctx, PRESSURE3_REG_MEAS_CFG, &temp_data, 1 );

    return temp_data;
}

void pressure3_set_configuration ( pressure3_t *ctx,uint8_t confg_data )
{
    pressure3_generic_write( ctx, PRESSURE3_REG_CFG_REG, &confg_data, 1 );
}

uint8_t pressure3_get_configuration ( pressure3_t *ctx )
{
    uint8_t temp_data;

    pressure3_generic_read( ctx, PRESSURE3_REG_CFG_REG, &temp_data, 1 );

    return temp_data;
}

uint8_t pressure3_get_interrupt_status ( pressure3_t *ctx )
{
    uint8_t temp_data;
    
    pressure3_generic_read( ctx, PRESSURE3_REG_INT_STS, &temp_data, 1 );
    
    return temp_data;
}

uint8_t pressure3_get_fifo_status ( pressure3_t *ctx )
{
    uint8_t temp_data;

    pressure3_generic_read( ctx, PRESSURE3_REG_FIFO_STS, &temp_data, 1 );
    

    return temp_data;
}

void pressure3_soft_reset (  pressure3_t *ctx )
{
    uint8_t temp;
    temp = PRESSURE3_BIT_MASK_RESET_SOFT_RST;
    pressure3_generic_write( ctx, PRESSURE3_REG_RESET, &temp, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pressure3_i2c_write ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );        
}

static void pressure3_i2c_read ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void pressure3_spi_write ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );       
}

static void pressure3_spi_read ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt ];
    }
}

// ------------------------------------------------------------------------- END


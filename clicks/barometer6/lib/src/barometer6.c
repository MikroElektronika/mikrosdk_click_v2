/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file barometer6.c
 * @brief Barometer 6 Click Driver.
 */

#include "barometer6.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                     0x00

/**
 * @brief Barometer 6 conversion factors.
 * @details Definition of conversion factor data.
 */
#define BAROMETER6_A_A1                   -0.0063
#define BAROMETER6_S_A1                    0.00043
#define BAROMETER6_A_A2                   -0.000000000019
#define BAROMETER6_S_A2                    0.00000000012
#define BAROMETER6_A_BT1	               0.100000000000000000
#define BAROMETER6_S_BT1	               0.091000000000000000
#define BAROMETER6_A_BT2	               0.000000012000000000
#define BAROMETER6_S_BT2	               0.000001200000000000
#define BAROMETER6_A_BP1	               0.033000000000000000
#define BAROMETER6_S_BP1	               0.019000000000000000
#define BAROMETER6_A_B11	               0.000000210000000000
#define BAROMETER6_S_B11	               0.000000140000000000
#define BAROMETER6_A_BP2	              -0.000000000630000000
#define BAROMETER6_S_BP2	               0.000000000350000000
#define BAROMETER6_A_B12	               0.000000000000290000
#define BAROMETER6_S_B12	               0.000000000000760000
#define BAROMETER6_A_B21	               0.000000000000002100
#define BAROMETER6_S_B21	               0.000000000000012000
#define BAROMETER6_A_BP3	               0.000000000000000130
#define BAROMETER6_S_BP3	               0.000000000000000079

#define BAROMETER6_COEFICIENT_DEVIDER      32767.0
#define BAROMETER6_MAX_23BIT_VALUE         0x0007FFFF
#define BAROMETER6_MAX_24BIT_VALUE         0x000FFFFF

/**
 * @brief Barometer 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer6_i2c_write ( barometer6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer6_i2c_read ( barometer6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 6 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer6_spi_write ( barometer6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 6 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer6_spi_read ( barometer6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 6 Click reset delay function.
 * @details This function is used for performing hardware reset delay of Barometer 6 Click driver.
 */
void dev_reset_delay ( void );

void barometer6_cfg_setup ( barometer6_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER6_SET_DEV_ADDR_LOW;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = BAROMETER6_DRV_SEL_SPI;
}

void barometer6_drv_interface_selection ( barometer6_cfg_t *cfg, barometer6_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t barometer6_init ( barometer6_t *ctx, barometer6_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( BAROMETER6_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = barometer6_i2c_read;
        ctx->write_f = barometer6_i2c_write;
    } 
    else 
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

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

        ctx->read_f  = barometer6_spi_read;
        ctx->write_f = barometer6_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_out_low( &ctx->rst );

    return BAROMETER6_OK;
}

void barometer6_default_cfg ( barometer6_t *ctx ) 
{
    barometer6_hardware_reset( ctx );
    barometer6_write_register( ctx, BAROMETER6_IO_SETUP, DUMMY );
    barometer6_get_conpesation_coe( ctx );    
    barometer6_set_mode( ctx, BAROMETER6_NORMAL_MODE );
    barometer6_set_avrege( ctx, BAROMETER6_AVG_64, BAROMETER6_AVG_64 );
    barometer6_set_standby_time( ctx, BAROMETER6_STANDBY_1ms );
}

err_t barometer6_generic_write ( barometer6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t barometer6_generic_read ( barometer6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

void barometer6_write_register ( barometer6_t *ctx, uint8_t reg, uint8_t data_in )
{
    barometer6_generic_write( ctx, reg, &data_in, 1 );    
}

void barometer6_read_register ( barometer6_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t rx_buf[ 2 ];
    uint16_t rx_data;
    
    barometer6_generic_read( ctx, reg, rx_buf, 2 );
    
    rx_data = rx_buf[ 0 ];
    rx_data <<= 8 ;
    rx_data |= rx_buf[ 1 ];
    
    *data_out = rx_data;
}

void barometer6_read_id ( barometer6_t *ctx, uint8_t *data_out )
{
    uint8_t rx_data;
    barometer6_generic_read( ctx, BAROMETER6_CHIP_ID, &rx_data, 1 );
    *data_out = rx_data;
}

void barometer6_software_reset ( barometer6_t *ctx )
{
    barometer6_write_register( ctx, BAROMETER6_RESET, BAROMETER6_CMD_RESET );
}

void barometer6_hardware_reset ( barometer6_t *ctx )
{
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
    digital_out_low( &ctx->rst );          
    dev_reset_delay( );
}

void barometer6_set_avrege ( barometer6_t *ctx, uint8_t temp_avg, uint8_t pressure_avg )
{
    uint8_t tmp_data;
    barometer6_generic_read( ctx, BAROMETER6_CTRL_MESS, &tmp_data, 1 );
    tmp_data |= ( temp_avg << 5 );
    tmp_data |= ( pressure_avg << 2 );
    barometer6_write_register( ctx, BAROMETER6_CTRL_MESS, tmp_data );
}

void barometer6_set_mode ( barometer6_t *ctx, uint8_t mode )
{
    uint8_t tmp_data;
    barometer6_generic_read( ctx, BAROMETER6_CTRL_MESS, &tmp_data, 1 );
    tmp_data |= mode;
    barometer6_write_register( ctx, BAROMETER6_CTRL_MESS, tmp_data );
}

void barometer6_set_standby_time ( barometer6_t *ctx, uint8_t t_standby )
{
    uint8_t tmp_data;
    tmp_data = t_standby << 5;
    barometer6_write_register( ctx, BAROMETER6_IO_SETUP, tmp_data );
}

uint8_t barometer6_check_ready ( barometer6_t *ctx )
{
    uint8_t rx_data;
    
    barometer6_generic_read( ctx, BAROMETER6_DEVICE_STAT, &rx_data, 1 );
    
    if (  ( rx_data & 0x08 ) == 0 )
    {
        return BAROMETER6_DATA_NOT_READY;
    }
    else
    {
        return BAROMETER6_DATA_READY;
    }
}

void barometer6_read_raw_temp ( barometer6_t *ctx, int32_t *data_out )
{
    uint8_t rx_buf[ 3 ];
    uint32_t temp_data;
    uint32_t tmp;
    
    barometer6_generic_read( ctx, BAROMETER6_TEMP_TXD2, rx_buf, 3 );
    
    temp_data = ( ( uint32_t ) rx_buf[ 0 ] << 16 ) | ( ( uint32_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 2 ];

    *data_out = ( int32_t )temp_data - pow( 2, 23 );
}

void barometer6_read_raw_pressure ( barometer6_t *ctx, float *data_out )
{
    uint8_t rx_buf[ 3 ];
    uint32_t press_data;
    uint32_t tmp;
    
    barometer6_generic_read( ctx, BAROMETER6_PRESS_TXD2, rx_buf, 3 );
    
    press_data = ( ( uint32_t ) rx_buf[ 0 ] << 16 ) | ( ( uint32_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 2 ];
    
    *data_out = ( float )press_data - pow( 2, 23 );
}

void barometer6_read_conp_coef ( barometer6_t *ctx, uint8_t reg, int16_t *data_out )
{
    uint16_t tmp_data;
    barometer6_read_register( ctx, reg, &tmp_data );
    
    *data_out = ( int16_t ) tmp_data;
}

void barometer6_get_conp_coef ( barometer6_t *ctx, uint8_t reg, float a_coef, float s_coef, 
                                float *data_out )
{
    int16_t tmp_data; 
    float coef_val;
    
    barometer6_read_conp_coef( ctx, reg, &tmp_data );
    
    coef_val = a_coef + ( s_coef *( ( float ) tmp_data / BAROMETER6_COEFICIENT_DEVIDER ) );
    
    *data_out = coef_val;
}

void barometer6_get_a0_b00_coef ( barometer6_t *ctx, float *coef_a0, float *coef_b00 )
{
    uint8_t rx_buf[ 3 ];
    uint32_t tmp_val;
    int32_t tmp;
    float coef_val;
    
    barometer6_generic_read( ctx, BAROMETER6_COE_A0_1, rx_buf, 2 );
    barometer6_generic_read( ctx, BAROMETER6_COE_B00_A0_EX, &rx_buf[ 2 ], 1 );
    tmp_val = ( ( uint32_t ) rx_buf[ 0 ] << 12 ) | ( ( uint32_t ) rx_buf[ 1 ] << 4 ) | 
              ( rx_buf[ 2 ] & 0x0F );
    
    tmp = ( int32_t ) tmp_val;
    if ( tmp_val > BAROMETER6_MAX_23BIT_VALUE )
    {
        tmp = ( int32_t ) tmp_val - BAROMETER6_MAX_24BIT_VALUE;
    }
    coef_val = ( float ) tmp / 16;
    
    *coef_a0 = coef_val;
    
    barometer6_generic_read( ctx, BAROMETER6_COE_B00_1, rx_buf, 2 );
    barometer6_generic_read( ctx, BAROMETER6_COE_B00_A0_EX, &rx_buf[ 2 ], 1 );
    tmp_val = ( ( uint32_t ) rx_buf[ 0 ] << 12 ) | ( ( uint32_t ) rx_buf[ 1 ] << 4 ) | 
              ( rx_buf[ 2 ] >> 4 );
    
    tmp = ( int32_t ) tmp_val;
    if ( tmp_val > BAROMETER6_MAX_23BIT_VALUE )
    {
        tmp = ( int32_t ) tmp_val - BAROMETER6_MAX_24BIT_VALUE;
    }
    coef_val = ( float ) tmp / 16;
    
    *coef_b00 = coef_val;
}

void barometer6_get_conpesation_coe ( barometer6_t *ctx )
{
     barometer6_get_a0_b00_coef( ctx, &ctx->coef_a0, &ctx->coef_b00 );
    
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_A1_1, BAROMETER6_A_A1, BAROMETER6_S_A1,
                              &ctx->coef_a1 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_A2_1, BAROMETER6_A_A2, BAROMETER6_S_A2,
                              &ctx->coef_a2 );
    
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_BP3_1, BAROMETER6_A_BP3, BAROMETER6_S_BP3,
                              &ctx->coef_bp3 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_B21_1, BAROMETER6_A_B21, BAROMETER6_S_B21,
                              &ctx->coef_b21 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_BP2_1, BAROMETER6_A_BP2, BAROMETER6_S_BP2,
                              &ctx->coef_bp2 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_B11_1, BAROMETER6_A_B11, BAROMETER6_S_B11,
                              &ctx->coef_b11 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_BP1_1, BAROMETER6_A_BP1, BAROMETER6_S_BP1,
                              &ctx->coef_bp1 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_BT2_1, BAROMETER6_A_BT2, BAROMETER6_S_BT2,
                              &ctx->coef_bt2 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_BT1_1, BAROMETER6_A_BT1, BAROMETER6_S_BT1,
                              &ctx->coef_bt1 );
    barometer6_get_conp_coef( ctx, BAROMETER6_COE_B12_1, BAROMETER6_A_B12, BAROMETER6_S_B12,
                              &ctx->coef_b12 );
    
}

void barometer6_get_temperature_data ( barometer6_t *ctx, float *temp_out )
{
    int32_t tmp_data;
    float temp_data;
    
    barometer6_read_raw_temp( ctx, &tmp_data );
    
    temp_data = (float) ( ctx->coef_a0 + ctx->coef_a1 * tmp_data + ctx->coef_a2 * ( tmp_data * tmp_data ) );
    
    *temp_out = temp_data;
}

void barometer6_read_temperature_value ( barometer6_t *ctx, float *temp_out )
{
    float temp_data;
    
    barometer6_get_temperature_data( ctx, &temp_data );
    
    *temp_out = temp_data / 256;
}

void barometer6_read_preassure_data ( barometer6_t *ctx, float *press_out )
{
    float temp_data;
    float tmp_data;
    float press_data;
        
    barometer6_get_temperature_data( ctx, &tmp_data );
    barometer6_read_raw_pressure( ctx, &press_data );
    temp_data = (float) ( ctx->coef_b00 + ctx->coef_bt1 * tmp_data + ctx->coef_bp1 * press_data + 
                          ctx->coef_b11 * press_data * tmp_data + 
                          ctx->coef_bt2 * pow( tmp_data, 2 ) + 
                          ctx->coef_bp2 * pow( press_data, 2 ) + 
                          ctx->coef_b12 * press_data * pow( tmp_data, 2 ) + 
                          ctx->coef_b21 * pow( press_data, 2 ) * tmp_data + 
                          ctx->coef_bp3 * pow( press_data, 3 ) );
    
    *press_out = temp_data;
}

void barometer6_read_preassure_value ( barometer6_t *ctx, float *press_out )
{
    float press_data;
    barometer6_read_preassure_data( ctx, &press_data );
    *press_out = press_data / 100;
}

static err_t barometer6_i2c_write ( barometer6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t barometer6_i2c_read ( barometer6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t barometer6_spi_write ( barometer6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = ( reg & 0x7F );
    
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t barometer6_spi_read ( barometer6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void dev_reset_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------ END

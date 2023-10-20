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
 * @file pressure23.c
 * @brief Pressure 23 Click Driver.
 */

#include "pressure23.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Pressure 23 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure23_i2c_write ( pressure23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 23 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure23_i2c_read ( pressure23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 23 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure23_spi_write ( pressure23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 23 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure23_spi_read ( pressure23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 23 calculate CRC8 function.
 * @details This function calculate 8-bit cyclic redundancy check (CRC8).
 * @param[in] data_in : Data in.
 * @param[out] crc_init : CRC init.
 * @return 8-bit CRC.
 * @note None.
 */
static uint8_t pressure23_calc_crc8 ( uint8_t data_in, uint8_t crc_init );

/**
 * @brief Pressure 23 Conversion time delay for OSR 0.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 0 (OSR).
 * @return Nothing.
 * @note The delay is 0.33 milliseconds.
 */
static void pressure23_delay_osr_0 ( void );

/**
 * @brief Pressure 23 Conversion time delay for OSR 1.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 1 (OSR).
 * @return Nothing.
 * @note The delay is 0.59 milliseconds.
 */
static void pressure23_delay_osr_1 ( void );

/**
 * @brief Pressure 23 Conversion time delay for OSR 2.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 2 (OSR).
 * @return Nothing.
 * @note The delay is 1.1 milliseconds.
 */
static void pressure23_delay_osr_2 ( void );

/**
 * @brief Pressure 23 Conversion time delay for OSR 3.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 3 (OSR).
 * @return Nothing.
 * @note The delay is 2.124 milliseconds.
 */
static void pressure23_delay_osr_3 ( void );

/**
 * @brief Pressure 23 Conversion time delay for OSR 4.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 4 (OSR).
 * @return Nothing.
 * @note The delay is 4.16 milliseconds.
 */
static void pressure23_delay_osr_4 ( void );

/**
 * @brief Pressure 23 Conversion time delay for OSR 5.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 5 (OSR).
 * @return Nothing.
 * @note The delay is 8.24 milliseconds.
 */
static void pressure23_delay_osr_5 ( void );

/**
 * @brief Pressure 23 Conversion time delay for OSR 6.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 6 (OSR).
 * @return Nothing.
 * @note The delay is 16.5 milliseconds.
 */
static void pressure23_delay_osr_6 ( void );

/**
 * @brief Pressure 23 array of function pointers.
 * @details his function is an array 
 * of conversion time delay function pointers.
 * @return Nothing.
 * @note None.
 */
static void ( *delay_ptr[ 7 ] ) ( void ) = 
{
    pressure23_delay_osr_0,
    pressure23_delay_osr_1,
    pressure23_delay_osr_2,
    pressure23_delay_osr_3,
    pressure23_delay_osr_4,
    pressure23_delay_osr_5,
    pressure23_delay_osr_6
};

void pressure23_cfg_setup ( pressure23_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE23_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE23_DRV_SEL_SPI;
}

void pressure23_drv_interface_selection ( pressure23_cfg_t *cfg, pressure23_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure23_init ( pressure23_t *ctx, pressure23_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( PRESSURE23_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = pressure23_i2c_read;
        ctx->write_f = pressure23_i2c_write;

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

        ctx->read_f  = pressure23_spi_read;
        ctx->write_f = pressure23_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESSURE23_OK;
}

err_t pressure23_default_cfg ( pressure23_t *ctx ) 
{
    // Reset sequence
    err_t err_flag = pressure23_sw_reset( ctx );
    Delay_100ms( );
    
    // Read coefficients defined during factory calibration
    err_flag |= pressure23_get_calibration_data( ctx );
    Delay_100ms( );
    
    // Pressure data configuration
    pressure23_sensor_cfg_t config;
    config.sel = PRESSURE23_SNSR_CFG_SEL_PRESS;
    config.ratio = PRESSURE23_SNSR_CFG_RATIO_OFF;
    config.filter = PRESSURE23_SNSR_CFG_FILTER_OFF;
    config.resolution = PRESSURE23_SNSR_CFG_RES_24_BIT;
    config.osr = PRESSURE23_SNSR_CFG_OSR_4;
    err_flag |= pressure23_write_config( ctx, config );
    Delay_100ms( );
    
    // Temperature data configuration
    config.sel = PRESSURE23_SNSR_CFG_SEL_TEMP;
    config.ratio = PRESSURE23_SNSR_CFG_RATIO_OFF;
    config.filter = PRESSURE23_SNSR_CFG_FILTER_OFF;
    config.resolution = PRESSURE23_SNSR_CFG_RES_24_BIT;
    config.osr = PRESSURE23_SNSR_CFG_OSR_4;
    err_flag |= pressure23_write_config( ctx, config );
    Delay_100ms( );
    
    return err_flag;
}

err_t pressure23_generic_write ( pressure23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t pressure23_generic_read ( pressure23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t pressure23_set_command ( pressure23_t *ctx, uint8_t cmd ) 
{
    err_t err_flag = PRESSURE23_OK;
    if ( PRESSURE23_DRV_SEL_I2C == ctx->drv_sel )
    {
        err_flag = i2c_master_write( &ctx->i2c, &cmd, 1 );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write( &ctx->spi, &cmd, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t pressure23_sw_reset ( pressure23_t *ctx ) 
{
    return pressure23_set_command( ctx, PRESSURE23_CMD_RESET );
}

err_t pressure23_read_memory ( pressure23_t *ctx, uint8_t reg, uint16_t *prom ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    err_t err_flag = PRESSURE23_OK;
    if ( PRESSURE23_REG_PROM_ID_CRC < reg )
    {
        err_flag = PRESSURE23_ERROR;
    }
    else
    {
        reg <<= 1;
        err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_MEMORY | reg, data_buf, 2 );
        *prom = data_buf[ 0 ];
        *prom <<= 8;
        *prom |= data_buf[ 1 ];
    }
    return err_flag;
}

err_t pressure23_start_conversion ( pressure23_t *ctx, uint8_t sel_cnv ) 
{
    sel_cnv &= PRESSURE23_CNV_ADC_BIT_MASK;
    return pressure23_set_command( ctx, PRESSURE23_CMD_START_CONVERSION | 
                                       ( PRESSURE23_CNV_ADC_REG_BIT_MASK << sel_cnv ) );
}

err_t pressure23_write_config ( pressure23_t *ctx, pressure23_sensor_cfg_t config ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t cfg_sel = ( config.sel & PRESSURE23_SNSR_CFG_SEL_BIT_MASK ) << 1;
    if ( PRESSURE23_SNSR_CFG_SEL_PRESS == cfg_sel )
    {
        ctx->osr_press = config.osr;
    }
    else
    {
        ctx->osr_temp = config.osr;
    }
    data_buf[ 0 ]  =   config.ratio      & PRESSURE23_SNSR_CFG_RATIO_BIT_MASK;
    data_buf[ 1 ]  = ( config.filter     & PRESSURE23_SNSR_CFG_FILTER_BIT_MASK ) << 5;
    data_buf[ 1 ] |= ( config.resolution & PRESSURE23_SNSR_CFG_RES_BIT_MASK ) << 3;
    data_buf[ 1 ] |=   config.osr        & PRESSURE23_SNSR_CFG_OSR_BIT_MASK;
    return pressure23_generic_write( ctx, PRESSURE23_CMD_WRITE_CONFIG_PRESS | cfg_sel, data_buf, 2 );
}

err_t pressure23_read_config ( pressure23_t *ctx, uint8_t sel_cfg, pressure23_sensor_cfg_t *config ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    sel_cfg &= PRESSURE23_SNSR_CFG_SEL_BIT_MASK;
    sel_cfg <<= 1;
    err_t err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_CONFIG_PRESS | sel_cfg, data_buf, 2 );
    config->ratio      =   data_buf[ 0 ]        & PRESSURE23_SNSR_CFG_RATIO_BIT_MASK;
    config->filter     = ( data_buf[ 1 ] >> 5 ) & PRESSURE23_SNSR_CFG_FILTER_BIT_MASK;
    config->resolution = ( data_buf[ 1 ] >> 3 ) & PRESSURE23_SNSR_CFG_RES_BIT_MASK;
    config->osr        =   data_buf[ 1 ]        & PRESSURE23_SNSR_CFG_OSR_BIT_MASK;
    return err_flag;
}

err_t pressure23_read_adc ( pressure23_t *ctx, uint8_t sel_data, uint32_t *adc_data ) 
{
    uint8_t data_buf[ 3 ] = { DUMMY };
    sel_data &= PRESSURE23_CNV_ADC_BIT_MASK;
    err_t err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_ADC_REG | 
                                              ( PRESSURE23_CNV_ADC_REG_BIT_MASK << sel_data ), data_buf, 3 );
    *adc_data = data_buf[ 0 ];
    *adc_data <<= 8;
    *adc_data |= data_buf[ 1 ];
    *adc_data <<= 8;
    *adc_data |= data_buf[ 2 ];
    return err_flag;
}

err_t pressure23_write_op_reg ( pressure23_t *ctx, uint8_t fifo_int_th, uint8_t fifo_mode, uint8_t delay ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ]  =   fifo_int_th & PRESSURE23_OP_REG_FIFO_INT_TH_BIT_MASK;
    data_buf[ 1 ]  = ( fifo_mode   & PRESSURE23_OP_REG_FIFO_MODE_BIT_MASK ) << 6;
    data_buf[ 1 ] |=   delay       & PRESSURE23_OP_REG_DELAY_BIT_MASK;
    return pressure23_generic_write( ctx, PRESSURE23_CMD_WRITE_OPERATION_REG, data_buf, 2 );
}

err_t pressure23_read_op_reg ( pressure23_t *ctx, uint8_t *fifo_int_th, uint8_t *fifo_mode, uint8_t *delay )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_OPERATION_REG, data_buf, 2 );
    *fifo_int_th =    data_buf[ 0 ] & PRESSURE23_OP_REG_FIFO_INT_TH_BIT_MASK;
    *fifo_mode   =  ( data_buf[ 1 ] >> 6 ) & PRESSURE23_OP_REG_FIFO_MODE_BIT_MASK;
    *delay       =    data_buf[ 1 ] & PRESSURE23_OP_REG_DELAY_BIT_MASK;
    return err_flag;
}

err_t pressure23_write_int_mask ( pressure23_t *ctx, uint16_t int_mask_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ]  = ( uint8_t ) ( int_mask_data >> 8 );
    data_buf[ 1 ]  = ( uint8_t )   int_mask_data;
    return pressure23_generic_write( ctx, PRESSURE23_CMD_WRITE_INTERRUPT_MASK, data_buf, 2 );
}

err_t pressure23_read_int_mask ( pressure23_t *ctx, uint16_t *int_mask_data )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_INTERRUPT_MASK, data_buf, 2 );
    *int_mask_data = data_buf[ 0 ];
    *int_mask_data <<= 8;
    *int_mask_data |= data_buf[ 1 ];
    return err_flag;
}

err_t pressure23_write_int_reg ( pressure23_t *ctx, uint16_t int_reg_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ]  = ( uint8_t ) ( int_reg_data >> 8 );
    data_buf[ 1 ]  = ( uint8_t )   int_reg_data;
    return pressure23_generic_write( ctx, PRESSURE23_CMD_WRITE_INTERRUPT_REG, data_buf, 2 );
}

err_t pressure23_read_int_reg ( pressure23_t *ctx, uint16_t *int_reg_data )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_INTERRUPT_REG, data_buf, 2 );
    *int_reg_data = data_buf[ 0 ];
    *int_reg_data <<= 8;
    *int_reg_data |= data_buf[ 1 ];
    return err_flag;
}

err_t pressure23_write_lim_reg ( pressure23_t *ctx, uint8_t sel_adr, uint8_t sel_lim, uint16_t lim_reg_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    sel_adr &= PRESSURE23_LIM_REG_SEL_BIT_MASK;
    sel_adr <<= 2;
    sel_lim &= PRESSURE23_LIM_REG_LIM_BIT_MASK;
    sel_lim <<= 1;
    data_buf[ 0 ]  = ( uint8_t ) ( lim_reg_data >> 8 );
    data_buf[ 1 ]  = ( uint8_t )   lim_reg_data;
    return pressure23_generic_write( ctx, PRESSURE23_CMD_WRITE_LIMIT_REG_TEMP_L | 
                                     sel_adr | sel_lim, data_buf, 2 );
}

err_t pressure23_read_lim_reg ( pressure23_t *ctx, uint8_t sel_adr, uint8_t sel_lim, uint16_t *lim_reg_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    sel_adr &= PRESSURE23_LIM_REG_SEL_BIT_MASK;
    sel_adr <<= 2;
    sel_lim &= PRESSURE23_LIM_REG_LIM_BIT_MASK;
    sel_lim <<= 1;
    err_t err_flag = pressure23_generic_read( ctx, PRESSURE23_CMD_READ_LIMIT_REG_TEMP_L | 
                                              sel_adr | sel_lim, data_buf, 2 );
    *lim_reg_data = data_buf[ 0 ];
    *lim_reg_data <<= 8;
    *lim_reg_data |= data_buf[ 1 ];
    return err_flag;
}

err_t pressure23_get_adc_data_press ( pressure23_t *ctx, uint32_t *pressure ) 
{
    // Start pressure conversion
    err_t err_flag = pressure23_start_conversion( ctx, PRESSURE23_CNV_ADC_SEL_PRESS );
    
    // Conversion time delay
    ( *delay_ptr[ ctx->osr_press ] )( );
    
    // Read pressure raw data
    err_flag |= pressure23_read_adc( ctx, PRESSURE23_CNV_ADC_SEL_PRESS, pressure );
    return err_flag;
}

err_t pressure23_get_adc_data_temp ( pressure23_t *ctx, uint32_t *temperature ) 
{
    // Start temperature conversion
    err_t err_flag = pressure23_start_conversion( ctx, PRESSURE23_CNV_ADC_SEL_TEMP );
    
    // Conversion time delay
    ( *delay_ptr[ ctx->osr_temp ] )( );
    
    // Read temperature raw data
    err_flag |= pressure23_read_adc( ctx, PRESSURE23_CNV_ADC_SEL_TEMP, temperature );
    return err_flag;
}

err_t pressure23_get_calibration_data ( pressure23_t *ctx ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = pressure23_read_memory( ctx, PRESSURE23_REG_SERIAL_NUMBER_MSB, &data_buf );
    ctx->prom_serial_num = data_buf;
    ctx->prom_serial_num <<= 16;
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_SERIAL_NUMBER_LSB, &data_buf );
    ctx->prom_serial_num |= data_buf;
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C1, &ctx->prom_c1 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C2, &ctx->prom_c2 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C3, &ctx->prom_c3 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C4, &ctx->prom_c4 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C5, &ctx->prom_c5 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C6, &ctx->prom_c6 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C7, &ctx->prom_c7 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C8, &ctx->prom_c8 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C9, &ctx->prom_c9 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_COEF_C10, &ctx->prom_c10 );
    err_flag |= pressure23_read_memory( ctx, PRESSURE23_REG_PROM_ID_CRC, &data_buf );
    ctx->prom_product_id = ( uint8_t ) ( data_buf >> 8 );
    ctx->prom_crc = ( uint8_t )  data_buf;
    return err_flag;
}

err_t pressure23_get_measurement_data ( pressure23_t *ctx, float *pressure, float *temperature ) 
{
    uint32_t d1 = DUMMY, d2 = DUMMY;
    float off = DUMMY, sens = DUMMY, temp = DUMMY;
    
    err_t err_flag = pressure23_get_adc_data_press( ctx, &d1 );
    Delay_10ms( );
    err_flag |= pressure23_get_adc_data_temp( ctx, &d2 );
    
    // Compensated temperature in degree Celsius
    temp = ( ( ( float ) ( ctx->prom_c1 ) ) * ( ( float ) d2 ) ) / PRESSURE23_COEF_TEMP_D2_DIV;
    temp -= ( ( ( float ) ( ctx->prom_c3 ) ) * ( ( float ) d1 ) ) / PRESSURE23_COEF_TEMP_D1_DIV;
    temp -= ( ( float ) ( ctx->prom_c2 ) ) / PRESSURE23_COEF_TEMP_C2_DIV;
    *temperature = temp; 

    // Offset at actual temperature
    off = ( ( float ) ( ctx->prom_c6 ) );
    off += ( ( ( float ) ( ctx->prom_c7 ) ) * temp ) / PRESSURE23_COEF_OFF_SENS_DIV;
    
     // Sensitivity at actual temperature
    sens = ( ( float ) ( ctx->prom_c8 ) );
    sens += ( ( ( float ) ( ctx->prom_c9 ) ) * temp ) / PRESSURE23_COEF_OFF_SENS_DIV;

    // Temperature compensated pressure
    *pressure = ( float ) d1;
    *pressure *= ( float ) sens;
    *pressure /= PRESSURE23_COEF_PRESS_DIV;
    *pressure -= off;
    
    return err_flag;
}

uint8_t pressure23_get_interrupt ( pressure23_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

static err_t pressure23_i2c_write ( pressure23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t pressure23_i2c_read ( pressure23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t pressure23_spi_write ( pressure23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

static err_t pressure23_spi_read ( pressure23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

static uint8_t pressure23_calc_crc8 ( uint8_t data_in, uint8_t crc_init )
{
    // Polynom 0x31 = 49 decimal
    // Most significant bit
    uint16_t msb_dat = DUMMY, msb_rem = DUMMY; 
    // CRC data
    uint8_t u_dat = data_in;
    // crc remainder
    uint8_t u_rem = crc_init;
    
    for ( uint8_t cnt = 0; cnt <= 7; cnt++ )
    {
        msb_dat = u_dat >> 7;
        msb_rem = u_rem >> 7;
        u_dat = u_dat << 1;
        u_rem = u_rem << 1;
        if ( msb_dat != msb_rem )
        {
            u_rem = u_rem ^ 0x31;
        }
    }
    return ( u_rem & 0xFF );
}

static void pressure23_delay_osr_0 ( void ) 
{
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_10us( );
}

static void pressure23_delay_osr_1 ( void ) 
{
    Delay_500us( );
    Delay_80us( );
    Delay_10us( );
}

static void pressure23_delay_osr_2 ( void ) 
{
    Delay_1ms( );
    Delay_50us( );
    Delay_50us( );
}

static void pressure23_delay_osr_3 ( void ) 
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_80us( );
    Delay_22us( );
    Delay_22us( );
}

static void pressure23_delay_osr_4 ( void ) 
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_80us( );
    Delay_80us( );
}

static void pressure23_delay_osr_5 ( void ) 
{
    Delay_8ms( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
}

static void pressure23_delay_osr_6 ( void ) 
{
    Delay_8ms( );
    Delay_8ms( );
    Delay_500us( );
}

// ------------------------------------------------------------------------ END

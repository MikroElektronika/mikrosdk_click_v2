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
 * @file c6dofimu17.c
 * @brief 6DOF IMU 17 Click Driver.
 */

#include "c6dofimu17.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80
#define BIT_MASK_BIT_0    0x01
#define BIT_MASK_BIT_1    0x02
#define BIT_MASK_BIT_2    0x04
#define BIT_MASK_BIT_3    0x08
#define BIT_MASK_BIT_4    0x10
#define BIT_MASK_BIT_5    0x20
#define BIT_MASK_BIT_6    0x40
#define BIT_MASK_BIT_7    0x80

/**
 * @brief 6DOF IMU 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu17_i2c_write ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu17_i2c_read ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 17 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu17_spi_write ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 17 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu17_spi_read ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 17 configuration delay function.
 * @details Configuration delay for 10 milliseconds.
 *
 * @note None.
 */
static void c6dofimu17_config_delay ( void );

void c6dofimu17_cfg_setup ( c6dofimu17_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C6DOFIMU17_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = C6DOFIMU17_DRV_SEL_SPI;
}

void c6dofimu17_drv_interface_selection ( c6dofimu17_cfg_t *cfg, c6dofimu17_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t c6dofimu17_init ( c6dofimu17_t *ctx, c6dofimu17_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( C6DOFIMU17_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = c6dofimu17_i2c_read;
        ctx->write_f = c6dofimu17_i2c_write;
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

        ctx->read_f  = c6dofimu17_spi_read;
        ctx->write_f = c6dofimu17_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return 0;
}

err_t c6dofimu17_default_cfg ( c6dofimu17_t *ctx ) 
{
    c6dofimu17_gyro_cfg_t gyro_cfg;
    c6dofimu17_accel_cfg_t accel_cfg;
     
    c6dofimu17_soft_reset( ctx );
    c6dofimu17_config_delay( );
     
    c6dofimu17_temperature_enable( ctx );
    c6dofimu17_config_delay( );
     
    c6dofimu17_gyro_enable( ctx );
    c6dofimu17_config_delay( );
     
    c6dofimu17_accel_enable( ctx );
    c6dofimu17_config_delay( );
     
    gyro_cfg.gyro_fs_sel      = C6DOFIMU17_SET_GYRO_FS_SEL_2000_dps;
    gyro_cfg.gyro_odr         = C6DOFIMU17_SET_GYRO_ODR_1kHz;
    gyro_cfg.gyro_ui_filt_ord = C6DOFIMU17_SET_GYRO_UI_FILT_ORD_2st;
    gyro_cfg.gyro_dec2_m2_ord = C6DOFIMU17_SET_GYRO_DEC2_M2_ORD_3st;
    gyro_cfg.gyro_ui_filt_bw  = C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_4;
    c6dofimu17_set_config_gyro( ctx, gyro_cfg );
    c6dofimu17_config_delay( );
    
    accel_cfg.accel_fs_sel      = C6DOFIMU17_SET_ACCEL_FS_SEL_16g;
    accel_cfg.accel_odr         = C6DOFIMU17_SET_ACCEL_ODR_1kHz;
    accel_cfg.accel_ui_filt_bw  = C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_4;
    accel_cfg.accel_ui_filt_ord = C6DOFIMU17_SET_ACCEL_UI_FILT_ORD_2st;
    accel_cfg.accel_dec2_m2_ord = C6DOFIMU17_SET_ACCEL_DEC2_M2_ORD_3st;
    c6dofimu17_set_config_accel( ctx, accel_cfg );
    c6dofimu17_config_delay( );
    
    return C6DOFIMU17_OK;
}

err_t c6dofimu17_generic_write ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t c6dofimu17_generic_read ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t c6dofimu17_bank_selection ( c6dofimu17_t *ctx, uint8_t bank_sel ) 
{  
    if ( bank_sel >= C6DOFIMU17_SET_BANK_4 )
    {
        return C6DOFIMU17_ERROR;        
    }
    return c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_BANK_SEL, &bank_sel, 1 );
}

uint8_t c6dofimu17_get_interrupt ( c6dofimu17_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

err_t c6dofimu17_get_device_id ( c6dofimu17_t *ctx, uint8_t *device_id ) 
{    
    return c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_WHO_AM_I, device_id, 1 );
}

err_t c6dofimu17_temperature_enable ( c6dofimu17_t *ctx ) 
{
    uint8_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_PWR_MGMT0, &tmp, 1 );
    
    tmp &= ~C6DOFIMU17_SET_TEMPERATURE_DISABLED;
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_PWR_MGMT0, &tmp, 1 );
    
    return err_flag;
}

err_t c6dofimu17_gyro_enable ( c6dofimu17_t *ctx ) 
{
    uint8_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_PWR_MGMT0, &tmp, 1 );
    
    tmp |= C6DOFIMU17_SET_GYRO_TLOW_NOISE_MODE;
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_PWR_MGMT0, &tmp, 1 );
    
    return err_flag;
}

err_t c6dofimu17_accel_enable ( c6dofimu17_t *ctx ) 
{
    uint8_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_PWR_MGMT0, &tmp, 1 );
    
    tmp |= C6DOFIMU17_SET_ACCEL_LOW_NOISE_MODE;
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_PWR_MGMT0, &tmp, 1 );
    
    return err_flag;
}

err_t c6dofimu17_set_config_gyro ( c6dofimu17_t *ctx, c6dofimu17_gyro_cfg_t gyro_cfg ) 
{
    uint8_t tmp;
    
    tmp  = ( gyro_cfg.gyro_fs_sel & ( BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 ) ) << 5;
    tmp |=   gyro_cfg.gyro_odr    & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_t err_flag = c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_GYRO_CONFIG0, &tmp, 1 );
    
    tmp  =  ( gyro_cfg.gyro_ui_filt_ord  & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 ) ) << 2;
    tmp |=    gyro_cfg.gyro_dec2_m2_ord  & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_ACCEL_CONFIG1, &tmp, 1 );
    
    err_flag |= c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0, &tmp, 1 );
    
    tmp |= gyro_cfg.gyro_ui_filt_bw & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0, &tmp, 1 );
    
    return err_flag;
}

err_t c6dofimu17_get_config_gyro ( c6dofimu17_t *ctx, c6dofimu17_gyro_cfg_t *gyro_cfg ) 
{
    uint8_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_GYRO_CONFIG0, &tmp, 1 );
    
    gyro_cfg->gyro_fs_sel = ( tmp >> 5 ) & ( BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    gyro_cfg->gyro_odr    =   tmp & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_flag |= c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_ACCEL_CONFIG1, &tmp, 1 );
    
    gyro_cfg->gyro_ui_filt_ord = ( tmp >> 2 ) & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    gyro_cfg->gyro_dec2_m2_ord =   tmp  & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_flag |= c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0, &tmp, 1 );
    
    gyro_cfg->gyro_dec2_m2_ord = tmp & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    return err_flag;
}

err_t c6dofimu17_set_config_accel ( c6dofimu17_t *ctx, c6dofimu17_accel_cfg_t accel_cfg ) 
{
    uint8_t tmp;
    
    tmp  = ( accel_cfg.accel_fs_sel & ( BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 ) ) << 5;
    tmp |=   accel_cfg.accel_odr    & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_t err_flag = c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_ACCEL_CONFIG0, &tmp, 1 );
    
    err_flag |= c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0, &tmp, 1 );
    
    tmp |= ( accel_cfg.accel_ui_filt_bw & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 ) ) << 4;
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0, &tmp, 1 );
    
    tmp  =  ( accel_cfg.accel_ui_filt_ord  & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 ) ) << 3;
    tmp |=  ( accel_cfg.accel_dec2_m2_ord  & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 ) ) << 1;
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_ACCEL_CONFIG1, &tmp, 1 );
    
    return err_flag;
}

err_t c6dofimu17_get_config_accel ( c6dofimu17_t *ctx, c6dofimu17_accel_cfg_t *accel_cfg ) 
{
    uint8_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_ACCEL_CONFIG0, &tmp, 1 );
    
    accel_cfg->accel_fs_sel = ( tmp >> 5 ) & ( BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    accel_cfg->accel_odr     =  tmp & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
       
    err_flag |= c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0, &tmp, 1 );
    
    accel_cfg->accel_ui_filt_bw = ( tmp >> 4 ) & ( BIT_MASK_BIT_3 | BIT_MASK_BIT_2 | BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    err_flag |= c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_ACCEL_CONFIG1, &tmp, 1 );
    
    accel_cfg->accel_ui_filt_ord = ( tmp << 3 ) & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    accel_cfg->accel_dec2_m2_ord = ( tmp << 1 ) & ( BIT_MASK_BIT_1 | BIT_MASK_BIT_0 );
    
    return err_flag;
}

err_t c6dofimu17_soft_reset ( c6dofimu17_t *ctx ) 
{
    uint8_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_DEVICE_CONFIG, &tmp, 1 );
    
    tmp |= 0x01;
    
    err_flag |= c6dofimu17_generic_write( ctx, C6DOFIMU17_REG_DEVICE_CONFIG, &tmp, 1 );
    c6dofimu17_config_delay( ) ;
    
    return err_flag;
}

err_t c6dofimu17_get_accel_data ( c6dofimu17_t *ctx, c6dofimu17_axis_t *accel_data ) 
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp; 
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_ACCEL_DATA_X1_UI, rx_buf, 6 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    accel_data->x = ( int16_t ) tmp;
    
    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    
    accel_data->y = ( int16_t ) tmp;
    
    tmp = rx_buf[ 4 ];
    tmp <<= 8;
    tmp |= rx_buf[ 5 ];
    
    accel_data->z = ( int16_t ) tmp;
    
    return err_flag;
}

err_t c6dofimu17_get_gyro_data ( c6dofimu17_t *ctx, c6dofimu17_axis_t *gyro_data ) 
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp; 
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_GYRO_DATA_X1_UI, rx_buf, 6 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    gyro_data->x = ( int16_t ) tmp;
    
    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    
    gyro_data->y = ( int16_t ) tmp;
    
    tmp = rx_buf[ 4 ];
    tmp <<= 8;
    tmp |= rx_buf[ 5 ];
    
    gyro_data->z = ( int16_t ) tmp;
    
    return err_flag;
}

err_t c6dofimu17_get_temperature ( c6dofimu17_t *ctx, float *temperature ) 
{
    uint8_t rx_buf[ 2 ];
    int16_t tmp;
    
    err_t err_flag = c6dofimu17_generic_read( ctx, C6DOFIMU17_REG_TEMP_DATA1_UI, rx_buf, 2 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    *temperature = ( float ) tmp;
    *temperature /= 132.48;
    *temperature += 25;
    
    return err_flag;
}

static err_t c6dofimu17_i2c_write ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t c6dofimu17_i2c_read ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t c6dofimu17_spi_write ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t c6dofimu17_spi_read ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static void c6dofimu17_config_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------ END

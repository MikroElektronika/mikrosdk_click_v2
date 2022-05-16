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
 * @file pressure20.c
 * @brief Pressure 20 Click Driver.
 */

#include "pressure20.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Pressure 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure20_i2c_write ( pressure20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure20_i2c_read ( pressure20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 20 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure20_spi_write ( pressure20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 20 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure20_spi_read ( pressure20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void pressure20_cfg_setup ( pressure20_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE20_DEVICE_ADDRESS_1;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE20_DRV_SEL_I2C;
}

void pressure20_drv_interface_selection ( pressure20_cfg_t *cfg, pressure20_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure20_init ( pressure20_t *ctx, pressure20_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    if ( PRESSURE20_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        digital_out_t scl;
        digital_out_init ( &scl, cfg->scl );
        digital_out_toggle ( &scl );
        digital_out_toggle ( &scl );
        digital_out_toggle ( &scl );
        digital_out_toggle ( &scl );
        digital_out_toggle ( &scl );
        digital_out_toggle ( &scl );
        Delay_100ms ( );
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
        ctx->read_f  = pressure20_i2c_read;
        ctx->write_f = pressure20_i2c_write;
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
        ctx->read_f  = pressure20_spi_read;
        ctx->write_f = pressure20_spi_write;
    }
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    return PRESSURE20_OK;
}

err_t pressure20_default_cfg ( pressure20_t *ctx ) 
{
    err_t error_flag = PRESSURE20_OK;
    if ( PRESSURE20_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        // dummy write
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_DUMMY, DUMMY );
    }
    if ( PRESSURE20_ERROR == pressure20_check_communication ( ctx ) )
    {
        return PRESSURE20_ERROR;
    }
    // Move to stand by mode
    error_flag |= pressure20_write_mode_select ( ctx, PRESSURE20_POWER_MODE_NORMAL );
    Delay_5ms ( );
    // Flush the FIFO to empty it
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_FIFO_FILL, PRESSURE20_FIFO_FLUSH );
    // Reset FIFO config
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_FIFO_CONFIG, PRESSURE20_FIFO_LEVEL_EMPTY );
    // Mask all interrupts
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_INTERRUPT_MASK, PRESSURE20_INT_MASK_ALL );
    // Clear interrupts
    error_flag |= pressure20_clear_interrupts ( ctx );
    uint8_t reg_data;
    // Read boot up status and avoid re-running boot up sequence if it is already done
    error_flag |= pressure20_read_register ( ctx, PRESSURE20_REG_OTP_STATUS2, &reg_data );
    if ( PRESSURE20_BOOT_UP_STATUS != ( reg_data & PRESSURE20_BOOT_UP_STATUS ) )
    {
        // Continue with boot up sequence for A1
        // Set to power mode to activate the OTP power domain and get access to the main registers */
        error_flag |= pressure20_write_mode_select ( ctx, PRESSURE20_POWER_MODE_ACTIVE );
        Delay_5ms ( ); 
        // Unlock the main registers
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_MASTER_LOCK, PRESSURE20_MASTER_UNLOCK );
        // Enable the OTP and the write switch
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_CONFIG1, PRESSURE20_OTP_WRITE_SWITCH | 
                                                                                   PRESSURE20_OTP_ENABLE );
        Delay_10us ( ); 
        // Toggle the OTP reset pin
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_DBG2, PRESSURE20_OTP_RESET_SET );
        Delay_10us ( ); 
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_DBG2, PRESSURE20_OTP_RESET_CLEAR );
        Delay_10us ( ); 
        // Program redundant read
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_MRA_LSB, PRESSURE20_OTP_MRA_LSB );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_MRA_MSB, PRESSURE20_OTP_MRA_MSB );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_MRB_LSB, PRESSURE20_OTP_MRB_LSB );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_MRB_MSB, PRESSURE20_OTP_MRB_MSB );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_MR_LSB, PRESSURE20_OTP_MR_LSB );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_MR_MSB, PRESSURE20_OTP_MR_MSB );
        // Read offset, gain and hfosc
        uint8_t offset, gain, hfosc;
        error_flag |= pressure20_read_otp_data ( ctx, PRESSURE20_OTP_ADDRESS_OFFSET, &offset );
        error_flag |= pressure20_read_otp_data ( ctx, PRESSURE20_OTP_ADDRESS_GAIN, &gain );
        error_flag |= pressure20_read_otp_data ( ctx, PRESSURE20_OTP_ADDRESS_HFOSC, &hfosc );
        // Disable OTP and write switch
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_CONFIG1, PRESSURE20_OTP_DISABLE );
        // Write OTP values to main registers
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_TRIM1_MSB, ( offset & PRESSURE20_TRIM1_MSB_PEFE_OFFSET_MASK ) );
        error_flag |= pressure20_read_register ( ctx, PRESSURE20_REG_TRIM2_MSB, &reg_data );
        reg_data = ( reg_data & ( ~PRESSURE20_TRIM2_MSB_PEFE_GAIN_MASK ) ) | ( ( gain << 4 ) & PRESSURE20_TRIM2_MSB_PEFE_GAIN_MASK );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_TRIM2_MSB, reg_data );
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_TRIM2_LSB, ( hfosc & PRESSURE20_TRIM2_LSB_HFOSC_MASK ) );
        // Lock the main register
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_MASTER_LOCK, PRESSURE20_MASTER_LOCK );
        // Move to stand by mode
        error_flag |= pressure20_write_mode_select ( ctx, PRESSURE20_POWER_MODE_NORMAL );
        Delay_5ms ( ); 
        // Update boot up status to 1
        error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_STATUS2, PRESSURE20_BOOT_UP_STATUS );
    }
    // Enable continuous measurement and set ODR to 25 Hz
    error_flag |= pressure20_write_mode_select ( ctx, PRESSURE20_MEAS_MODE_CONTINUOUS | PRESSURE20_MEAS_CONFIG_MODE0_ODR_25HZ );
    Delay_5ms ( ); 
    // Flush the FIFO to empty it
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_FIFO_FILL, PRESSURE20_FIFO_FLUSH );
    // Wait for the FIFO full indication
    do 
    {
        Delay_100ms ( );
        error_flag |= pressure20_read_register ( ctx, PRESSURE20_REG_FIFO_FILL, &reg_data );
    } while ( PRESSURE20_FIFO_FULL != ( reg_data & PRESSURE20_FIFO_FULL ) );
    // Flush the FIFO to empty it, because of the FIR filter settling effect (warm up) on the first FIFO output
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_FIFO_FILL, PRESSURE20_FIFO_FLUSH );
    // Set FIFO watermark HIGH level to 1
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_FIFO_CONFIG, PRESSURE20_FIFO_LEVEL_1 << 4 );
    // Unmask FIFO watermark HIGH interrupt
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_INTERRUPT_MASK, ( ~PRESSURE20_INT_MASK_FIFO_WMK_HIGH ) );
    // Clear interrupts
    error_flag |= pressure20_clear_interrupts ( ctx );
    return error_flag;
}

err_t pressure20_generic_write ( pressure20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t pressure20_generic_read ( pressure20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t pressure20_write_register ( pressure20_t *ctx, uint8_t reg, uint8_t data_in )
{
    return pressure20_generic_write( ctx, reg, &data_in, 1 );
}

err_t pressure20_read_register ( pressure20_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pressure20_generic_read( ctx, reg, data_out, 1 );
}

err_t pressure20_check_communication ( pressure20_t *ctx )
{
    uint8_t device_id;
    if ( PRESSURE20_OK == pressure20_read_register ( ctx, PRESSURE20_REG_DEVICE_ID, &device_id ) )
    {
        if ( PRESSURE20_DEVICE_ID == device_id )
        {
            return PRESSURE20_OK;
        }
    }
    return PRESSURE20_ERROR;
}

err_t pressure20_write_mode_select ( pressure20_t *ctx, uint8_t mode_select )
{
    err_t error_flag = PRESSURE20_OK;
    uint8_t dev_status;
    do 
    {
        Delay_1ms ( );
        error_flag |= pressure20_read_register ( ctx, PRESSURE20_REG_DEVICE_STATUS, &dev_status );
    } while ( PRESSURE20_MODE_SYNC_STATUS != ( dev_status & PRESSURE20_MODE_SYNC_STATUS ) );
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_MODE_SELECT, mode_select );
    return error_flag;
}

err_t pressure20_read_otp_data ( pressure20_t *ctx, uint8_t otp_address, uint8_t *data_out )
{
    err_t error_flag = pressure20_write_register ( ctx, PRESSURE20_REG_OTP_ADDRESS_REG, otp_address );
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_OTP_COMMAND_REG, PRESSURE20_OTP_COMMAND_READ_ACTION );
    // Wait for the OTP read to finish
    uint8_t otp_status;
    do 
    {
        Delay_1ms ( ); 
        error_flag |= pressure20_read_register ( ctx, PRESSURE20_REG_OTP_STATUS, &otp_status );
    } while ( PRESSURE20_BUSY == otp_status );
    // Read the data from register
    error_flag |= pressure20_read_register ( ctx, PRESSURE20_REG_OTP_RDATA, data_out );
    return error_flag;
}

err_t pressure20_read_data ( pressure20_t *ctx, float *pressure, float *temperature )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = pressure20_generic_read( ctx, PRESSURE20_REG_PRESS_DATA_0, data_buf, 6 );
    int32_t raw_data = ( ( int32_t ) ( ( ( int32_t ) ( data_buf[ 2 ] & 0x0F ) << 16 ) | 
                                       ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] ) << 12 ) >> 12;
    // P = ( POUT / 2^17 ) * 400mBar + 700mBar
    *pressure = ( ( float ) raw_data / PRESSURE20_PRESSURE_RES_RAW ) * PRESSURE20_PRESSURE_RES_MBAR + 
                PRESSURE20_PRESSURE_OFFSET_MBAR;
    raw_data = ( ( int32_t ) ( ( ( int32_t ) ( data_buf[ 5 ] & 0x0F ) << 16 ) | 
                               ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ] ) << 12 ) >> 12;
    // T = ( TOUT / 2^18 ) * 65C + 25C
    *temperature = ( ( float ) raw_data / PRESSURE20_TEMPERATURE_RES_RAW ) * PRESSURE20_TEMPERATURE_RES_C + 
                   PRESSURE20_TEMPERATURE_OFFSET_C;
    return error_flag;
}

uint8_t pressure20_get_int_pin ( pressure20_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t pressure20_clear_interrupts ( pressure20_t *ctx )
{
    uint8_t int_status;
    err_t error_flag = pressure20_read_register ( ctx, PRESSURE20_REG_INTERRUPT_STATUS, &int_status );
    error_flag |= pressure20_write_register ( ctx, PRESSURE20_REG_INTERRUPT_STATUS, int_status );
    return error_flag;
}

static err_t pressure20_i2c_write ( pressure20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        tx_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t pressure20_i2c_read ( pressure20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t pressure20_spi_write ( pressure20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 2 ] = { PRESSURE20_SPI_WRITE_REG, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t pressure20_spi_read ( pressure20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tx_buf[ 2 ] = { PRESSURE20_SPI_READ_REG, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file accel36.c
 * @brief Accel 36 Click Driver.
 */

#include "accel36.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                   0x00

/**
 * @brief SPI command bytes.
 * @details Definition of SPI command bytes
 */
#define ACCEL36_SPI_WRITE_MASK  0x40         /**< 0 | 1 | addr[5:0] – write command. */
#define ACCEL36_SPI_READ_MASK   0xC0         /**< 1 | 1 | addr[5:0] – read command.  */
#define ACCEL36_SPI_ADDR_MASK   0x3F         /**< 6-bit address mask. */

/**
 * @brief Accel 36 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel36_i2c_write ( accel36_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 36 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel36_i2c_read ( accel36_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 36 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel36_spi_write ( accel36_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 36 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel36_spi_read ( accel36_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel36_cfg_setup ( accel36_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL36_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL36_DRV_SEL_I2C;
}

void accel36_drv_interface_sel ( accel36_cfg_t *cfg, accel36_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel36_init ( accel36_t *ctx, accel36_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL36_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel36_i2c_read;
        ctx->write_f = accel36_i2c_write;
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

        ctx->read_f  = accel36_spi_read;
        ctx->write_f = accel36_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    /* Default sensitivity for +-2g at 14-bit. */
    ctx->accel_sens = ACCEL36_SENS_2G;

    return ACCEL36_OK;
}

err_t accel36_default_cfg ( accel36_t *ctx )
{
    err_t error_flag = ACCEL36_OK;
    uint8_t reg_data = 0;
    uint8_t timeout = 0;

    if ( ACCEL36_DRV_SEL_I2C == ctx->drv_sel )
    {
        /* ----------------------------------------------------------------
         * Per section 5.3 table 10, the following sequence represents the  
         * recommended initialization sequence for I2C Interface.
         * ---------------------------------------------------------------- */
        
        /* 1. Go to STANDBY (now safe to write other registers) */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_MODE_C, ACCEL36_MODE_STANDBY );

        /* 2. Software reset. */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RESET, ACCEL36_RESET_CMD );

        /* 3. Wait at least 1ms for reset to complete */
        Delay_5ms( );

        /* 4. Enable I2C mode */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_FREG_1, ACCEL36_FREG1_I2C_EN );

        /* 5-9. Mandatory init values */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_INIT_1, ACCEL36_INIT_1_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_DMX, ACCEL36_DMX_INIT_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_DMY, ACCEL36_DMY_INIT_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_INIT_2, ACCEL36_INIT_2_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_INIT_3, ACCEL36_INIT_3_VALUE );
    }
    else
    {
        /* ----------------------------------------------------------------
         * Per section 5.3 table 11, the following sequence represents the  
         * recommended initialization sequence for SPI Interface.
         * ---------------------------------------------------------------- */

        /* 1. Go to STANDBY */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_MODE_C, ACCEL36_MODE_STANDBY );

        /* 2. Software reset. */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RESET, ACCEL36_RESET_CMD );

        /* 3. Wait at least 1ms for reset to complete */
        Delay_5ms( );

        /* 4. Read CHIP_ID until non-zero (confirms bus is up after reset). */
        do
        {
            error_flag |= accel36_read_reg( ctx, ACCEL36_REG_CHIP_ID, &reg_data );
            Delay_1ms( );
            timeout++;
            if ( timeout > ACCEL36_ID_TIMEOUT_MS )
            {
                return ACCEL36_ERROR;
            }
        }
        while ( ACCEL36_ID_POLL_DATA == reg_data );

        /* 5-6. Enable SPI and poll Feature Register 1 to confirm when SPI is enabled */
        reg_data = 0;
        timeout = 0;
        do
        {
            error_flag |= accel36_write_reg( ctx, ACCEL36_REG_FREG_1, ACCEL36_FREG1_SPI_EN );
            error_flag |= accel36_read_reg( ctx, ACCEL36_REG_FREG_1, &reg_data );
            Delay_1ms( );
            timeout++;
            if ( timeout > ACCEL36_SPI_ENABLE_MS )
            {
                return ACCEL36_ERROR;
            }
        }
        while ( ACCEL36_SPI_ENABLE_POLL_DATA != reg_data );

        /* 7. Write mandatory value. */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_INIT_1, ACCEL36_INIT_1_VALUE );

        /* 8. Go to STANDBY (from SLEEP state entered after reset). */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_MODE_C, ACCEL36_MODE_STANDBY );

        /* 9. Wait at least 10ms for state machine */
        Delay_10ms( );
        Delay_5ms( );

        /* 10-13. Mandatory init values */
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_DMX, ACCEL36_DMX_INIT_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_DMY, ACCEL36_DMY_INIT_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_INIT_2, ACCEL36_INIT_2_VALUE );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_INIT_3, ACCEL36_INIT_3_VALUE );
    }

    if ( ACCEL36_OK != error_flag )
    {
        return ACCEL36_ERROR;
    }

    /* Verify communication by checking CHIP_ID. */
    if ( ACCEL36_OK != accel36_check_communication( ctx ) )
    {
        return ACCEL36_ERROR;
    }

    /* Range and Resolution Control Register:
     *    bit[2:0] = 101 => 14bit width of accelerometer data
     *    bit[6:4] = 000 => +-2g range resolution */
    error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RANGE_C,
                                          ACCEL36_RANGE_2G | 
                                          ACCEL36_RES_14BIT );
    /* cache current sensitivity */
    ctx->accel_sens = ACCEL36_SENS_2G;

    /* Power Mode Control Register:
     *    bit[2:0] = 000 => low power mode for CWAKE,SWAKE modes
     *    bit[6:4] = 000 => low power mode for SNIFF mode */
    error_flag |= accel36_write_reg( ctx, ACCEL36_REG_PMCR,
                                          ACCEL36_CSPM_LOW_POWER | 
                                          ACCEL36_SPM_LOW_POWER );

    /* Output Data Rate for wake modes: 105 Hz in Low Power mode */
    error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RATE_1, ACCEL36_ODR_105HZ );

    /* Enter CWAKE (continuous measurement) mode. 
     * Active XYZ sampling, SNIFF circuitry not active */
    error_flag |= accel36_write_reg( ctx, ACCEL36_REG_MODE_C, ACCEL36_MODE_CWAKE );

    /* Wait at least 10ms for mode transition */
    Delay_10ms( );
    Delay_5ms( );

    return error_flag;
}

err_t accel36_write_reg ( accel36_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t accel36_write_regs ( accel36_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel36_read_reg ( accel36_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t accel36_read_regs ( accel36_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel36_check_communication ( accel36_t *ctx )
{
    uint8_t chip_id = 0;

    if ( ACCEL36_OK != accel36_read_reg( ctx, ACCEL36_REG_CHIP_ID, &chip_id ) )
    {
        return ACCEL36_ERROR;
    }
    
    if ( ACCEL36_CHIP_ID == chip_id )
    {
        return ACCEL36_OK;
    }
    else
    {
        return ACCEL36_ERROR;
    }
}

err_t accel36_reset_device ( accel36_t *ctx )
{
    err_t error_flag = ACCEL36_OK;

    /* Device must be in STANDBY before issuing reset. */
    error_flag |= accel36_write_reg( ctx, ACCEL36_REG_MODE_C, ACCEL36_MODE_STANDBY );

    /* Wait at least 10ms for mode transition */
    Delay_10ms( );
    Delay_5ms( );

    /* Set RESET bit. The bit is self-clearing. */
    error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RESET, ACCEL36_RESET_CMD );

    /* Wait at least 1ms after reset */
    Delay_5ms( );

    return error_flag;
}

err_t accel36_set_fsr ( accel36_t *ctx, uint8_t fsr )
{
    uint8_t reg_data = 0;
    err_t error_flag = ACCEL36_OK;

    if ( fsr > ACCEL36_FSR_12G )
    {
        return ACCEL36_ERROR;
    }

    /* Perform read-modify-write to update bits[6:4] and preserve bits[2:0]. */
    error_flag |= accel36_read_reg( ctx, ACCEL36_REG_RANGE_C, &reg_data );
    if ( ACCEL36_OK == error_flag )
    {
        reg_data &= ~ACCEL36_RANGE_MASK;
        reg_data |= ( ( fsr << ACCEL36_RANGE_BIT ) & ACCEL36_RANGE_MASK );

        /* Update cached sensitivity. */
        switch ( fsr )
        {
            case ACCEL36_FSR_2G:  
                ctx->accel_sens = ACCEL36_SENS_2G;  
                break;
            case ACCEL36_FSR_4G:  
                ctx->accel_sens = ACCEL36_SENS_4G;
                break;
            case ACCEL36_FSR_8G:
                ctx->accel_sens = ACCEL36_SENS_8G;
                break;
            case ACCEL36_FSR_16G:
                ctx->accel_sens = ACCEL36_SENS_16G;
                break;
            case ACCEL36_FSR_12G:
                ctx->accel_sens = ACCEL36_SENS_12G;
                break;
            default:
                return ACCEL36_ERROR;
        }

        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RANGE_C, reg_data );
    }

    return error_flag;
}

err_t accel36_set_odr ( accel36_t *ctx, uint8_t odr )
{
    uint8_t reg_data = 0;

    /* Perform read-modify-write to update bits[3:0] and preserve bits[6:4]. */
    err_t error_flag = accel36_read_reg( ctx, ACCEL36_REG_RATE_1, &reg_data );
    if ( ACCEL36_OK == error_flag )
    {
        reg_data &= ACCEL36_MSB_BYTE_MASK;
        reg_data |= ( odr & ACCEL36_LSB_BYTE_MASK );
        error_flag |= accel36_write_reg( ctx, ACCEL36_REG_RATE_1, reg_data );
    }

    return error_flag;
}

err_t accel36_data_ready ( accel36_t *ctx )
{
    uint8_t status = 0;
    
    /* Read status register 1 */
    if ( ACCEL36_OK != accel36_read_reg( ctx, ACCEL36_REG_STATUS_1, &status ) )
    {
        return ACCEL36_ERROR;
    }
    
    if ( status & ACCEL36_STATUS1_NEW_DATA )
    {
        return ACCEL36_OK;
    }
    else
    {
        return ACCEL36_DATA_NOT_READY;
    }
}

err_t accel36_get_accel ( accel36_t *ctx, accel36_axes_t *accel )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = ACCEL36_OK;

    if ( NULL == accel )
    {
        return ACCEL36_ERROR;
    }

    error_flag |= accel36_data_ready( ctx );
    if ( ACCEL36_OK != error_flag )
    {
        return error_flag;
    }

    /* Burst-read all 6 output registers atomically (0x02 to 0x07).
     * Data format: LSB at lower address, MSB at higher address.
     * For 14-bit data: XOUT[13:0] are valid, sign-extended to XOUT[15:14]. */
    error_flag |= accel36_read_regs( ctx, ACCEL36_REG_XOUT_LSB, data_buf, 6 );

    if ( ACCEL36_OK == error_flag )
    {
        int16_t raw_x = ( int16_t ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] );
        int16_t raw_y = ( int16_t ) ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ] );
        int16_t raw_z = ( int16_t ) ( ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ] );

        accel->x = ( float ) raw_x / ctx->accel_sens;
        accel->y = ( float ) raw_y / ctx->accel_sens;
        accel->z = ( float ) raw_z / ctx->accel_sens;
    }

    return error_flag;
}

uint8_t accel36_get_int_pin ( accel36_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t accel36_i2c_write ( accel36_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel36_i2c_read ( accel36_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel36_spi_write ( accel36_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t cmd = ACCEL36_SPI_WRITE_MASK | ( reg & ACCEL36_SPI_ADDR_MASK );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel36_spi_read ( accel36_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t cmd = ACCEL36_SPI_READ_MASK | ( reg & ACCEL36_SPI_ADDR_MASK );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

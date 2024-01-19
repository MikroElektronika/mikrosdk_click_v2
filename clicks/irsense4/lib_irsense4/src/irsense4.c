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
 * @file irsense4.c
 * @brief IR Sense 4 Click Driver.
 */

#include "irsense4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                0x00
#define SPI_READ_MASK        0x80
#define IRSENSE4_TIME_OUT    1000u

/**
 * @brief IR Sense 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irsense4_i2c_write ( irsense4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief IR Sense 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irsense4_i2c_read ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief IR Sense 4 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irsense4_spi_write ( irsense4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief IR Sense 4 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irsense4_spi_read ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void irsense4_cfg_setup ( irsense4_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRSENSE4_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = IRSENSE4_DRV_SEL_I2C;
}

void irsense4_drv_interface_selection ( irsense4_cfg_t *cfg, irsense4_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t irsense4_init ( irsense4_t *ctx, irsense4_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( IRSENSE4_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = irsense4_i2c_read;
        ctx->write_f = irsense4_i2c_write;
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

        ctx->read_f  = irsense4_spi_read;
        ctx->write_f = irsense4_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return IRSENSE4_OK;
}

err_t irsense4_default_cfg ( irsense4_t *ctx ) 
{
    uint8_t device_id = DUMMY;
    err_t err_flag = irsense4_get_device_id( ctx, &device_id );
    if ( IRSENSE4_DEVICE_ID == device_id )
    {
        // Low-pass filter configuration for motion detection
        err_flag |= irsense4_set_lp_filter_motion( ctx, IRSENSE4_LPF1_M_ODR_200 );
        Delay_10ms( );
        
        // Low-pass filter configuration for presence detection and ambient temperature
        err_flag |= irsense4_set_lp_filter_presence( ctx, IRSENSE4_LPF2_P_ODR_200 );
        Delay_10ms( );
        
        // Low-pass filter configuration for ambient temperature
        err_flag |= irsense4_set_lp_filter_amb_temp( ctx, IRSENSE4_LPF2_A_T_ODR_50 );
        Delay_10ms( );
        
        // Averaging selection for object temperature and noise
        err_flag |= irsense4_set_avr_temp( ctx, IRSENSE4_AVG_TRIM_T_8, IRSENSE4_AVG_TRIM_TMOS_32 );
        Delay_10ms( );
        
        // Temperature gain mode
        err_flag |= irsense4_set_gain_mode( ctx, IRSENSE4_CTRL0_GAIN_8 );
        Delay_10ms( );
        
        // Sensitivity data of the component that can be used for the compensation algorithm
        err_flag |= irsense4_set_sens_data( ctx, IRSENSE4_SENS_DATA_MIN );
        Delay_10ms( );
        
        // ODR configuration
        err_flag |= irsense4_config_odr( ctx, IRSENSE4_CTRL1_ODR_15 | 
                                              IRSENSE4_CTRL1_BDU_DIS );
        Delay_10ms( );
        
        // Interrupt mask configuration
        err_flag |= irsense4_set_int_mask( ctx, IRSENSE4_CTRL3_INT_MSK_PRES | 
                                                IRSENSE4_CTRL3_INT_MSK_MOT  | 
                                                IRSENSE4_CTRL3_INT_MSK_T_SHOCK );
        Delay_10ms( );
        
        // Interrupt signal configuration
        err_flag |= irsense4_config_int_signal( ctx, IRSENSE4_CTRL3_IEN_DRDY );
        Delay_10ms( );
        
        // Presence threshold for presence detection algorithms
        err_flag |= irsense4_set_threshold( ctx, IRSENSE4_THS_PRESENCE, 
                                                 IRSENSE4_SET_THS_PRESENCE_DEFAULT );
        Delay_10ms( );
        
        // Motion threshold for motion detection algorithm
        err_flag |= irsense4_set_threshold( ctx, IRSENSE4_THS_MOTION, 
                                                 IRSENSE4_SET_THS_MOTION_DEFAULT );
        Delay_10ms( );
        
        // Ambient temperature shock threshold for tambient shock detection algorithm
        err_flag |= irsense4_set_threshold( ctx, IRSENSE4_THS_TAMB_SHOCK, 
                                                 IRSENSE4_SET_THS_T_SHOCK_DEFAULT );
        Delay_10ms( );
    }
    else
    {
        err_flag = IRSENSE4_ERROR;
    }
    return err_flag;
}

err_t irsense4_generic_write ( irsense4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t irsense4_generic_read ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t irsense4_write_reg ( irsense4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return irsense4_generic_write( ctx, reg, &data_in, 1 );
}

err_t irsense4_read_reg ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return irsense4_generic_read( ctx, reg, data_out, 1 );
}

err_t irsense4_read_word ( irsense4_t *ctx, uint8_t reg, int16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = irsense4_generic_read( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 0 ];
    return err_flag;
}

err_t irsense4_set_lp_filter_motion ( irsense4_t *ctx, uint8_t lpf_m ) 
{
    uint8_t data_buf = DUMMY;
    lpf_m &= IRSENSE4_LPF1_M_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_LPF1, &data_buf );
    data_buf &= ~IRSENSE4_LPF1_M_BIT_MASK;
    data_buf |= lpf_m;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_LPF1, data_buf );
    return err_flag;
}

err_t irsense4_set_lp_filter_presence ( irsense4_t *ctx, uint8_t lpf_p ) 
{
    uint8_t data_buf = DUMMY;
    lpf_p &= IRSENSE4_LPF2_P_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_LPF2, &data_buf );
    data_buf &= ~IRSENSE4_LPF2_P_BIT_MASK;
    data_buf |= lpf_p;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_LPF2, data_buf );
    return err_flag;
}

err_t irsense4_set_lp_filter_amb_temp ( irsense4_t *ctx, uint8_t lpf_at ) 
{
    uint8_t data_buf = DUMMY;
    lpf_at &= IRSENSE4_LPF2_A_T_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_LPF2, &data_buf );
    data_buf &= ~IRSENSE4_LPF2_A_T_BIT_MASK;
    data_buf |= lpf_at;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_LPF2, data_buf );
    return err_flag;
}

err_t irsense4_get_device_id ( irsense4_t *ctx, uint8_t *device_id ) 
{
    return irsense4_generic_read( ctx, IRSENSE4_REG_WHO_AM_I, device_id, 1 );
}

err_t irsense4_set_avr_temp ( irsense4_t *ctx, uint8_t avr_amp_temp, uint8_t avr_obj_temp ) 
{
    uint8_t data_buf = DUMMY;
    avr_amp_temp &= IRSENSE4_AVG_TRIM_T_BIT_MASK;
    avr_obj_temp &= IRSENSE4_AVG_TRIM_TMOS_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_AVG_TRIM, &data_buf );
    data_buf &= ~( IRSENSE4_AVG_TRIM_T_BIT_MASK | IRSENSE4_AVG_TRIM_TMOS_BIT_MASK );
    data_buf |= avr_amp_temp;
    data_buf |= avr_obj_temp;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_AVG_TRIM, data_buf );
    return err_flag;
}

err_t irsense4_set_gain_mode ( irsense4_t *ctx, uint8_t gain_mode ) 
{
    uint8_t data_buf = DUMMY;
    gain_mode &= IRSENSE4_CTRL0_GAIN_8;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_CTRL0, &data_buf );
    data_buf &= ~IRSENSE4_CTRL0_GAIN_8;
    data_buf |= IRSENSE4_CTRL0_DEFAULT;
    data_buf |= gain_mode;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_CTRL0, data_buf );
    return err_flag;
}

err_t irsense4_set_sens_data ( irsense4_t *ctx, uint16_t sens )
{
    err_t err_flag = IRSENSE4_OK;
    if ( ( IRSENSE4_SENS_DATA_MAX < sens ) || ( IRSENSE4_SENS_DATA_MIN > sens ) )
    {
        err_flag = IRSENSE4_ERROR;
    }
    else
    {
        sens -= IRSENSE4_SENS_DATA_MIN;
        sens /= IRSENSE4_SENS_DATA_CALC_DEV;
        err_flag = irsense4_write_reg( ctx, IRSENSE4_REG_SENS_DATA, ( uint8_t ) sens );
    }
    return err_flag;
}

err_t irsense4_config_odr ( irsense4_t *ctx, uint8_t odr ) 
{
    uint8_t data_buf = DUMMY;
    odr &= IRSENSE4_CTRL1_ODR_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_CTRL1, &data_buf );
    data_buf &= ~IRSENSE4_CTRL1_ODR_BIT_MASK;
    data_buf |= odr;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_CTRL1, data_buf );
    return err_flag;
}

err_t irsense4_enable_one_shot ( irsense4_t *ctx ) 
{
    return irsense4_write_reg( ctx, IRSENSE4_REG_CTRL2, IRSENSE4_CTRL2_ONE_SHOT_EN );
}

err_t irsense4_set_int_mask ( irsense4_t *ctx, uint8_t int_mask ) 
{
    uint8_t data_buf = DUMMY;
    int_mask &= IRSENSE4_CTRL3_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_CTRL3, &data_buf );
    data_buf &= ~IRSENSE4_CTRL3_BIT_MASK;
    data_buf |= int_mask;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_CTRL3, data_buf );
    return err_flag;
}

err_t irsense4_config_int_signal ( irsense4_t *ctx, uint8_t int_sr ) 
{
    uint8_t data_buf = DUMMY;
    int_sr &= IRSENSE4_CTRL3_IEN_BIT_MASK;
    err_t err_flag = irsense4_read_reg( ctx, IRSENSE4_REG_CTRL3, &data_buf );
    data_buf &= ~IRSENSE4_CTRL3_IEN_BIT_MASK;
    data_buf |= int_sr;
    err_flag |= irsense4_write_reg( ctx, IRSENSE4_REG_CTRL3, data_buf );
    return err_flag;
}

err_t irsense4_wait_new_data_ready ( irsense4_t *ctx ) 
{
    uint16_t time_out = DUMMY;
    uint8_t status = DUMMY;
    err_t err_flag = irsense4_enable_one_shot( ctx );
    do
    {
        err_flag |= irsense4_generic_read( ctx, IRSENSE4_REG_STATUS, &status, 1 );
        time_out++;
        Delay_10ms( );
    }
    while ( ( IRSENSE4_STATUS_NOT_DRDY == status ) && ( IRSENSE4_TIME_OUT > time_out ) );
    
    if ( IRSENSE4_TIME_OUT < time_out )
    {
        err_flag = IRSENSE4_ERROR;
    }
    
    return err_flag;
}

err_t irsense4_get_status ( irsense4_t *ctx, uint8_t *status ) 
{
    return irsense4_generic_read( ctx, IRSENSE4_REG_FUNC_STATUS, status, 1 );
}

err_t irsense4_get_obj_temperature ( irsense4_t *ctx, float *temperature ) 
{
    int16_t tmp = DUMMY;
    err_t err_flag = irsense4_read_word( ctx, IRSENSE4_REG_TOBJECT_L, &tmp );
    *temperature = ( float ) tmp;
    *temperature /= IRSENSE4_SENS_TOBJECT; 
    return err_flag;
}

err_t irsense4_get_amb_temperature ( irsense4_t *ctx, float *temperature ) 
{
    int16_t tmp = DUMMY;
    err_t err_flag = irsense4_read_word( ctx, IRSENSE4_REG_TAMBIENT_L, &tmp );
    *temperature = ( float ) tmp;
    *temperature /= IRSENSE4_SENS_TAMBIENT; 
    return err_flag;
}

err_t irsense4_get_comp_temperature ( irsense4_t *ctx, float *temperature ) 
{
    int16_t tmp = DUMMY;
    err_t err_flag = irsense4_read_word( ctx, IRSENSE4_REG_TOBJ_COMP_L, &tmp );
    *temperature = ( float ) tmp;
    *temperature /= IRSENSE4_SENS_TOBJ_COMP;
    return err_flag;
}

err_t irsense4_get_presence_data ( irsense4_t *ctx, int16_t *presence ) 
{
    return irsense4_read_word( ctx, IRSENSE4_REG_TPRESENCE_L, presence );
}

err_t irsense4_get_motion_data ( irsense4_t *ctx, int16_t *motion ) 
{
    return irsense4_read_word( ctx, IRSENSE4_REG_TMOTION_L, motion );
}

err_t irsense4_get_amb_shock_data ( irsense4_t *ctx, int16_t *shock ) 
{
    return irsense4_read_word( ctx, IRSENSE4_REG_TAMB_SHOCK_L, shock );
}

err_t irsense4_write_emb_reg ( irsense4_t *ctx, uint8_t reg_emb, uint8_t data_in )
{
    uint8_t data_buf = DUMMY, odr = DUMMY;
    // Save the ODR value to restore it at the end of the procedure
    err_t err_flag = irsense4_generic_read( ctx, IRSENSE4_REG_CTRL1, &odr, 1 );
    
    // Stop acquiring data and enter power-down mode (ODR = 0 Hz)
    data_buf = IRSENSE4_CTRL1_ODR_POWER_DOWN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL1, &data_buf, 1 );
    Delay_1ms( );
    
    // Enable access to the embedded functions registers
    err_flag |= irsense4_generic_read( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    data_buf |= IRSENSE4_CTRL2_F_CFG_ACCESS_EN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    Delay_1ms( );
    
    // Select write operation mode
    data_buf = IRSENSE4_EMB_PAGE_RW_WRITE_EN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_PAGE_RW, &data_buf, 1 );
    Delay_1ms( );
    
    // Set address XXh of the embedded functions register to be written
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_FUNC_CFG_ADDR, &reg_emb, 1 );
    Delay_1ms( );
    
    // Set value YYh to be written
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_FUNC_CFG_DATA, &data_in, 1 );
    Delay_1ms( );
    
    // Disable write operation mode
    data_buf = IRSENSE4_EMB_PAGE_RW_WRITE_DIS;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_PAGE_RW, &data_buf, 1 );
    Delay_1ms( );
    
    // Disable access to the embedded functions registers
    err_flag |= irsense4_generic_read( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    data_buf &= ~IRSENSE4_CTRL2_F_CFG_ACCESS_EN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    Delay_1ms( );
    
    // Restore the ODR value
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL1, &odr, 1 );
    return err_flag;
}

err_t irsense4_read_emb_reg ( irsense4_t *ctx, uint8_t reg_emb, uint8_t *data_out )
{
    uint8_t data_buf = DUMMY, odr = DUMMY;
    // Save the ODR value to restore it at the end of the procedure
    err_t err_flag = irsense4_generic_read( ctx, IRSENSE4_REG_CTRL1, &odr, 1 );
    
    // Stop acquiring data and enter power-down mode (ODR = 0 Hz)
    data_buf = IRSENSE4_CTRL1_ODR_POWER_DOWN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL1, &data_buf, 1 );
    Delay_1ms( );
    
    // Enable access to the embedded functions registers
    err_flag |= irsense4_generic_read( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    data_buf |= IRSENSE4_CTRL2_F_CFG_ACCESS_EN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    Delay_1ms( );
    
    //  Select read operation mode
    data_buf = IRSENSE4_EMB_PAGE_RW_READ_EN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_PAGE_RW, &data_buf, 1 );
    Delay_1ms( );
    
    // Set address XXh of the embedded functions register to be written
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_FUNC_CFG_ADDR, &reg_emb, 1 );
    Delay_1ms( );
    
    // Get register value
    err_flag |= irsense4_generic_read( ctx, IRSENSE4_REG_EMB_FUNC_CFG_DATA, data_out, 1 );
    Delay_1ms( );
    
    // Disable read operation mode
    data_buf = IRSENSE4_EMB_PAGE_RW_READ_DIS;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_EMB_PAGE_RW, &data_buf, 1 );
    Delay_1ms( );
    
    // Disable access to the embedded functions registers
    err_flag |= irsense4_generic_read( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    data_buf &= ~IRSENSE4_CTRL2_F_CFG_ACCESS_EN;
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL2, &data_buf, 1 );
    Delay_1ms( );
    
    // Restore the ODR value
    err_flag |= irsense4_generic_write( ctx, IRSENSE4_REG_CTRL1, &odr, 1 );

    return err_flag;
}

err_t irsense4_set_threshold ( irsense4_t *ctx, irsense4_ths_sel_t ths_sel, uint16_t threshold ) 
{
    threshold &= IRSENSE4_SET_THS_MAX;
    err_t err_flag = irsense4_write_emb_reg( ctx, IRSENSE4_REG_EMB_PRESENCE_THS_L + ths_sel, 
                                                  ( uint8_t ) ( threshold ) );
    err_flag |= irsense4_write_emb_reg( ctx, IRSENSE4_REG_EMB_PRESENCE_THS_H + ths_sel, 
                                             ( uint8_t ) ( threshold >> 8 ) );
    return err_flag;
}

err_t irsense4_get_threshold ( irsense4_t *ctx, irsense4_ths_sel_t ths_sel, uint16_t *threshold ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = irsense4_read_emb_reg( ctx, IRSENSE4_REG_EMB_PRESENCE_THS_H + ths_sel, 
                                                 &data_buf );
    *threshold = data_buf;
    *threshold <<= 8;
    err_flag |= irsense4_read_emb_reg( ctx, IRSENSE4_REG_EMB_PRESENCE_THS_L + ths_sel, 
                                            &data_buf );
    *threshold |= data_buf;
    return err_flag;
}

uint8_t irsense4_get_interrupt ( irsense4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t irsense4_i2c_write ( irsense4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t irsense4_i2c_read ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t irsense4_spi_write ( irsense4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t irsense4_spi_read ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

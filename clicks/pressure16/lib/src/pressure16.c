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
 * @file pressure16.c
 * @brief Pressure 16 Click Driver.
 */

#include "pressure16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Pressure 16 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure16_i2c_write ( pressure16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 16 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure16_i2c_read ( pressure16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 16 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure16_spi_write ( pressure16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 16 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure16_spi_read ( pressure16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Configuration delay.
 * @details Configuration delay for 100 milliseconds.
 * @return Nothing.
 * @note None.
 */
static void pressure16_cfg_delay ( void );

void pressure16_cfg_setup ( pressure16_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE16_SET_DEV_ADDR_VCC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE16_DRV_SEL_I2C;
}

void pressure16_drv_interface_selection ( pressure16_cfg_t *cfg, pressure16_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure16_init ( pressure16_t *ctx, pressure16_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ctx->drv_sel == PRESSURE16_DRV_SEL_I2C ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = pressure16_i2c_read;
        ctx->write_f = pressure16_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = pressure16_spi_read;
        ctx->write_f = pressure16_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return 0;
}

err_t pressure16_default_cfg ( pressure16_t *ctx ) 
{
    pressure16_ctrl_cfg_t ctrl_cfg_data;
    pressure16_int_cfg_t int_cfg_data;
    
    pressure16_sw_reset( ctx );
    pressure16_cfg_delay( );
    
    int_cfg_data.auto_refp = PRESSURE16_SET_INT_CFG_AUTOREFP_DISABLED; 
    int_cfg_data.reset_arp = PRESSURE16_SET_INT_CFG_RESET_ARP_NORMAL_MODE;
    int_cfg_data.auto_zero = PRESSURE16_SET_INT_CFG_AUTOZERO_DISABLED;
    int_cfg_data.reset_az  = PRESSURE16_SET_INT_CFG_AUTOZERO_NORMAL_MODE;
    int_cfg_data.diff_en   = PRESSURE16_SET_INT_CFG_DIFF_EN_ENABLED;
    int_cfg_data.lir       = PRESSURE16_SET_INT_CFG_LIR_INT_IS_NOT_LATCHED;
    int_cfg_data.ple       = PRESSURE16_SET_INT_CFG_PLE_INT_IS_ACTIVE;
    int_cfg_data.phe       = PRESSURE16_SET_INT_CFG_PHE_INT_IS_ACTIVE;
    pressure16_set_interrupt_config( ctx, int_cfg_data );
    pressure16_cfg_delay( );
    
    ctrl_cfg_data.odr          = PRESSURE16_SET_CTRL_ODR_1;
    ctrl_cfg_data.en_lpfp      = PRESSURE16_SET_CTRL_LPFP_DISABLE;
    ctrl_cfg_data.lpfp_cfg     = PRESSURE16_SET_CTRL_LPFP_DISABLE;
    ctrl_cfg_data.bdu          = PRESSURE16_SET_BDU_DATA_UPDATES_CONTINUOUS;
    ctrl_cfg_data.sim          = PRESSURE16_SET_SIM_SPI_4_WIRE_INTERFACE;
    ctrl_cfg_data.boot         = PRESSURE16_SET_BOOT_NORMAL_OPERATION;
    ctrl_cfg_data.int_h_l      = PRESSURE16_SET_INT_H_L_INTERRUPT_ACTIVE_HIGH;
    ctrl_cfg_data.pp_od        = PRESSURE16_SET_PP_OD_PUSH_PULL;
    ctrl_cfg_data.if_add_inc   = PRESSURE16_SET_IF_ADD_INC_ENABLED;
    ctrl_cfg_data.low_noise_en = PRESSURE16_SET_LOW_NOISE_ENABLE_LOW_POWER_MODE;
    ctrl_cfg_data.one_shot     = PRESSURE16_SET_ONE_SHOT_NORMAL_OPERATION;
    ctrl_cfg_data.int_f_full   = PRESSURE16_SET_INT_F_FULL_DISABLED;
    ctrl_cfg_data.int_f_wtm    = PRESSURE16_SET_INT_F_WTM_DISABLED;
    ctrl_cfg_data.int_f_ovr    = PRESSURE16_SET_INT_F_OVR_DISABLED;
    ctrl_cfg_data.drdy         = PRESSURE16_SET_DRDY_DISABLED;
    ctrl_cfg_data.int_s        = PRESSURE16_SET_INT_S_DATA_SIGNAL;
    pressure16_set_ctrl_config( ctx, ctrl_cfg_data );
    pressure16_cfg_delay( );
    
    return PRESSURE16_OK;
}

err_t pressure16_generic_write ( pressure16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t pressure16_generic_read ( pressure16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t pressure16_get_device_id ( pressure16_t *ctx, uint8_t *dev_id ) 
{   
    return pressure16_generic_read( ctx, PRESSURE16_REG_DEVICE_ID, dev_id, 1 );;
}

err_t pressure16_sw_reset ( pressure16_t *ctx ) 
{
    uint8_t tmp;

    err_t err_flag = pressure16_generic_read( ctx, PRESSURE16_REG_CTRL_2, &tmp, 1 );
    
    tmp |= PRESSURE16_SET_SW_RESET_BIT_MASK;
    
    err_flag |= pressure16_generic_write( ctx, PRESSURE16_REG_CTRL_2, &tmp, 1 );
    
    return err_flag;
}

err_t pressure16_set_interrupt_config( pressure16_t *ctx, pressure16_int_cfg_t int_cfg_data ) 
{
    uint8_t tx_data;
    
    tx_data =  ( int_cfg_data.auto_refp & 0x01 ) << 7;
    tx_data |= ( int_cfg_data.reset_arp & 0x01 ) << 6;
    tx_data |= ( int_cfg_data.auto_zero & 0x01 ) << 5;
    tx_data |= ( int_cfg_data.reset_az  & 0x01 ) << 4;
    tx_data |= ( int_cfg_data.diff_en   & 0x01 ) << 3;
    tx_data |= ( int_cfg_data.lir       & 0x01 ) << 2;
    tx_data |= ( int_cfg_data.ple       & 0x01 ) << 1;
    tx_data |=   int_cfg_data.phe       & 0x01;
    
//     err_t err_flag = 
    
    return pressure16_generic_write( ctx, PRESSURE16_REG_INT_CFG, &tx_data, 1 );
}

err_t pressure16_get_interrupt_config( pressure16_t *ctx, pressure16_int_cfg_t *int_cfg_data ) 
{
    uint8_t rx_data;
    
    err_t err_flag = pressure16_generic_read( ctx, PRESSURE16_REG_INT_CFG, &rx_data, 1 );
    
    int_cfg_data->auto_refp = ( rx_data >> 7 ) & 0x01;
    int_cfg_data->reset_arp = ( rx_data >> 6 ) & 0x01;
    int_cfg_data->auto_zero = ( rx_data >> 5 ) & 0x01;
    int_cfg_data->reset_az  = ( rx_data >> 4 ) & 0x01;
    int_cfg_data->diff_en   = ( rx_data >> 3 ) & 0x01;
    int_cfg_data->lir       = ( rx_data >> 2 ) & 0x01;
    int_cfg_data->ple       = ( rx_data >> 1 ) & 0x01;
    int_cfg_data->phe       =   rx_data        & 0x01;
    
    return err_flag;
}

err_t pressure16_set_ctrl_config( pressure16_t *ctx, pressure16_ctrl_cfg_t ctrl_cfg_data ) 
{
    uint8_t tx_data;
    
    tx_data =  ( ctrl_cfg_data.odr      & 0x07 ) << 4;
    tx_data |= ( ctrl_cfg_data.en_lpfp  & 0x01 ) << 3;
    tx_data |= ( ctrl_cfg_data.lpfp_cfg & 0x01 ) << 2;
    tx_data |= ( ctrl_cfg_data.bdu      & 0x01 ) << 1;
    tx_data |=   ctrl_cfg_data.sim      & 0x01;
    
    err_t err_flag = pressure16_generic_write( ctx, PRESSURE16_REG_CTRL_1, &tx_data, 1 );
    
    tx_data =  ( ctrl_cfg_data.boot         & 0x01 ) << 7;
    tx_data |= ( ctrl_cfg_data.int_h_l      & 0x01 ) << 6;
    tx_data |= ( ctrl_cfg_data.pp_od        & 0x01 ) << 5;
    tx_data |= ( ctrl_cfg_data.if_add_inc   & 0x01 ) << 4;
    tx_data |= ( ctrl_cfg_data.low_noise_en & 0x01 ) << 1;
    tx_data |=   ctrl_cfg_data.one_shot     & 0x01;
    
    err_flag |= pressure16_generic_write( ctx, PRESSURE16_REG_CTRL_2, &tx_data, 1 );
    
    tx_data =  ( ctrl_cfg_data.int_f_full & 0x01 ) << 5;
    tx_data |= ( ctrl_cfg_data.int_f_wtm  & 0x01 ) << 4;
    tx_data |= ( ctrl_cfg_data.int_f_ovr  & 0x01 ) << 3;
    tx_data |= ( ctrl_cfg_data.drdy       & 0x01 ) << 2;
    tx_data |=   ctrl_cfg_data.int_s      & 0x03;
    
    err_flag |= pressure16_generic_write( ctx, PRESSURE16_REG_CTRL_3, &tx_data, 1 );
    
    return err_flag;
}

err_t pressure16_get_ctrl_config( pressure16_t *ctx, pressure16_ctrl_cfg_t *ctrl_cfg_data ) 
{
    uint8_t rx_data;
    
    err_t err_flag = pressure16_generic_read( ctx, PRESSURE16_REG_CTRL_1, &rx_data, 1 );
    
    ctrl_cfg_data->odr      = ( rx_data >> 4 ) & 0x07;
    ctrl_cfg_data->en_lpfp  = ( rx_data >> 3 ) & 0x01;
    ctrl_cfg_data->lpfp_cfg = ( rx_data >> 2 ) & 0x01;
    ctrl_cfg_data->bdu      = ( rx_data >> 1 ) & 0x01;
    ctrl_cfg_data->sim      =   rx_data        & 0x01;
    
    err_flag |= pressure16_generic_read( ctx, PRESSURE16_REG_CTRL_2, &rx_data, 1 );
    
    ctrl_cfg_data->boot         = ( rx_data >> 7 ) & 0x01;
    ctrl_cfg_data->int_h_l      = ( rx_data >> 6 ) & 0x01;
    ctrl_cfg_data->pp_od        = ( rx_data >> 5 ) & 0x01;
    ctrl_cfg_data->if_add_inc   = ( rx_data >> 4 ) & 0x01;
    ctrl_cfg_data->low_noise_en = ( rx_data >> 1 ) & 0x01;
    ctrl_cfg_data->one_shot     =   rx_data        & 0x01;
    
    err_flag |= pressure16_generic_read( ctx, PRESSURE16_REG_CTRL_3, &rx_data, 1 );
    
    ctrl_cfg_data->int_f_full = ( rx_data >> 5 ) & 0x01;
    ctrl_cfg_data->int_f_wtm  = ( rx_data >> 4 ) & 0x01;
    ctrl_cfg_data->int_f_ovr  = ( rx_data >> 3 ) & 0x01;
    ctrl_cfg_data->drdy       = ( rx_data >> 2 ) & 0x01;
    ctrl_cfg_data->int_s      =   rx_data        & 0x02;
    
    return err_flag;
}

err_t pressure16_get_pressure ( pressure16_t *ctx, float *pressure ) 
{
    uint8_t rx_buf[ 3 ];
    uint32_t tmp;

    err_t err_flag = pressure16_generic_read( ctx, PRESSURE16_REG_DATA_P_XL, rx_buf, 3 );
    
    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    
    *pressure = ( float ) tmp;
    *pressure /= 4096.0;
    
    return err_flag;
}

err_t pressure16_get_temperature ( pressure16_t *ctx, float *temperature ) 
{
    uint8_t rx_buf[ 2 ];
    uint16_t tmp;

    err_t err_flag = pressure16_generic_read( ctx, PRESSURE16_REG_DATA_T_L, rx_buf, 2 );
    
    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    
    *temperature = ( float ) tmp;
    *temperature /= 100.0;
    
    return err_flag;
}

err_t pressure16_get_press_temp ( pressure16_t *ctx, float *pressure, float *temperature ) 
{
    err_t err_flag = pressure16_get_pressure( ctx, pressure );
    
    err_flag |= pressure16_get_temperature( ctx, temperature );
    
    return err_flag;
}

uint8_t pressure16_get_interrupt ( pressure16_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

static err_t pressure16_i2c_write ( pressure16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t pressure16_i2c_read ( pressure16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t pressure16_spi_write ( pressure16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t pressure16_spi_read ( pressure16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static void pressure16_cfg_delay ( void ) 
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------ END

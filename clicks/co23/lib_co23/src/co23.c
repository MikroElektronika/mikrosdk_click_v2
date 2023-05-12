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
 * @file co23.c
 * @brief CO2 3 Click Driver.
 */

#include "co23.h"

/**
 * @brief CO2 3 UART interface data.
 * @details Specified UART interface frame sequence payload for description 
 * of CO2 3 Click driver.
 */
#define CO23_UART_WRITE             0x57
#define CO23_UART_READ              0x72
#define CO23_UART_DELIMITER         0x2C
#define CO23_UART_END_OF_MESSAGE    0x0A
#define CO23_UART_ACK               0x06
#define CO23_UART_NAK               0x15

/**
 * @brief CO2 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t co23_i2c_write ( co23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief CO2 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t co23_i2c_read ( co23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief CO2 3 UART writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t co23_uart_write ( co23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief CO2 3 UART reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t co23_uart_read ( co23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief CO2 3 UART write register function.
 * @details This function writes a desired data byte 
 * to the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t co23_uart_write_reg ( co23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief CO2 3 UART readregister  function.
 * @details This function reads a data bytes 
 * from the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t co23_uart_read_reg ( co23_t *ctx, uint8_t reg, uint8_t *data_out );

void co23_cfg_setup ( co23_cfg_t *cfg ) 
{
    // I2C communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // UART communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pwo = HAL_PIN_NC;
    cfg->pws = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CO23_DEVICE_ADDRESS;
    
    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
    
    cfg->drv_sel = CO23_DRV_SEL_I2C;
}

void co23_drv_interface_selection ( co23_cfg_t *cfg, co23_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t co23_init ( co23_t *ctx, co23_cfg_t *cfg ) 
{
    digital_out_init( &ctx->pws, cfg->pws );

    digital_out_low( &ctx->pws );
    Delay_10ms( );

    ctx->drv_sel = cfg->drv_sel;
    
    if ( CO23_DRV_SEL_I2C == ctx->drv_sel )
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

        ctx->read_f  = co23_i2c_read;
        ctx->write_f = co23_i2c_write;
    } 
    else
    {
        uart_config_t uart_cfg;

        // Default config
        uart_configure_default( &uart_cfg );

        // Ring buffer mapping
        ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
        ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

        // UART module config
        uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
        uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
        uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
        uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

        if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
        {
            return UART_ERROR;
        }
        uart_set_baud( &ctx->uart, cfg->baud_rate );
        uart_set_parity( &ctx->uart, cfg->parity_bit );
        uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        uart_set_data_bits( &ctx->uart, cfg->data_bit );

        uart_set_blocking( &ctx->uart, cfg->uart_blocking );
        
        ctx->read_f  = co23_uart_read;
        ctx->write_f = co23_uart_write;
    }
    
    digital_in_init( &ctx->pwo, cfg->pwo );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t co23_default_cfg ( co23_t *ctx ) 
{      
    co23_meas_cfg_t meas_cfg;
    meas_cfg.op_mode = CO23_OP_MODE_IDLE;
    err_t err_flag = co23_set_meas_cfg ( ctx, meas_cfg );
    Delay_10ms( );

    err_flag |= co23_set_pressure_ref( ctx, 1015 );
    Delay_10ms( );

    uint16_t result = 0;
    err_flag |= co23_get_co2_ppm( ctx, &result );
    Delay_10ms( );
    
    return err_flag;
}

err_t co23_generic_write ( co23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t co23_generic_read ( co23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t co23_get_device_id ( co23_t *ctx, uint8_t *prod, uint8_t *rev ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    err_t err_flag = co23_generic_read( ctx, CO23_REG_PROD_ID, data_buf, 1 );
    *prod = ( data_buf[ 0 ] >> 5 ) & 0x07;
    *rev  =   data_buf[ 0 ]        & 0x1F;
    return err_flag;
}

err_t co23_get_sens_status ( co23_t *ctx, co23_sens_status_t *sens_status ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = co23_generic_read( ctx, CO23_REG_SENS_STS, &data_buf, 1 );
    sens_status->sen_rdy    = ( data_buf >> 7 ) & 0x01;
    sens_status->pwm_dis_st = ( data_buf >> 6 ) & 0x01;
    sens_status->ortmp      = ( data_buf >> 5 ) & 0x01;
    sens_status->orvs       = ( data_buf >> 4 ) & 0x01;
    sens_status->iccer      = ( data_buf >> 3 ) & 0x01;
    sens_status->ortmp_clr  = ( data_buf >> 2 ) & 0x01;
    sens_status->orvs_clr   = ( data_buf >> 1 ) & 0x01;
    sens_status->iccer_clr  =   data_buf        & 0x01;
    return err_flag;
}

err_t co23_set_meas_rate ( co23_t *ctx, uint16_t meas_rate_sec ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = CO23_OK;
    if ( ( meas_rate_sec < 5 ) || ( meas_rate_sec > 4096 ) )
    {
        err_flag = CO23_ERROR;  
    }
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( meas_rate_sec >> 8 );
        data_buf[ 1 ] = ( uint8_t )   meas_rate_sec;
        err_flag = co23_generic_write( ctx, CO23_REG_MEAS_RATE_H, data_buf, 2 );
    }
    return err_flag;
}

err_t co23_get_meas_cfg ( co23_t *ctx, co23_meas_cfg_t *meas_cfg ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = co23_generic_read( ctx, CO23_REG_MEAS_CFG, &data_buf, 1 );
    meas_cfg->pwm_outen = ( data_buf >> 5 ) & 0x01;
    meas_cfg->pwm_mode  = ( data_buf >> 4 ) & 0x01;
    meas_cfg->boc_cfg   = ( data_buf >> 2 ) & 0x03;
    meas_cfg->op_mode   =   data_buf        & 0x03;
    return err_flag;
}

err_t co23_set_meas_cfg ( co23_t *ctx, co23_meas_cfg_t meas_cfg ) 
{
    uint8_t data_buf = ( meas_cfg.pwm_outen & 0x01 ) << 5;
    data_buf |= ( meas_cfg.pwm_mode  & 0x01 ) << 4;
    data_buf |= ( meas_cfg.boc_cfg   & 0x03 ) << 2;
    data_buf |=   meas_cfg.op_mode   & 0x03;
    return co23_generic_write( ctx, CO23_REG_MEAS_CFG, &data_buf, 1 );
}

err_t co23_get_co2_ppm ( co23_t *ctx, uint16_t *co2_ppm ) 
{
    uint8_t data_buf = 0; 
    err_t err_flag = co23_generic_read( ctx, CO23_REG_CO2PPM_H, &data_buf, 1 );
    Delay_500us();
    *co2_ppm = data_buf;
    *co2_ppm <<= 8;
    err_flag |= co23_generic_read( ctx, CO23_REG_CO2PPM_L, &data_buf, 1 );
    Delay_500us();
    *co2_ppm |= data_buf;
    return err_flag;
}

err_t co23_get_meas_status ( co23_t *ctx, co23_meas_status_t *meas_status ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = co23_generic_read( ctx, CO23_REG_MEAS_STS, &data_buf, 1 );
    meas_status->drdy        = ( data_buf >> 4 ) & 0x01;
    meas_status->int_sts     = ( data_buf >> 3 ) & 0x01;
    meas_status->alarm       = ( data_buf >> 2 ) & 0x01;
    meas_status->int_sts_clr = ( data_buf >> 1 ) & 0x01;
    meas_status->alarm_clr   =   data_buf        & 0x01;
    return err_flag;
}

err_t co23_get_int_cfg ( co23_t *ctx, co23_int_cfg_t *int_cfg ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = co23_generic_read( ctx, CO23_REG_INT_CFG, &data_buf, 1 );
    int_cfg->int_typ   = ( data_buf >> 4 ) & 0x01;
    int_cfg->int_func  = ( data_buf >> 1 ) & 0x07;
    int_cfg->alarm_typ =   data_buf        & 0x01;
    return err_flag;
}

err_t co23_set_int_cfg ( co23_t *ctx, co23_int_cfg_t int_cfg ) 
{
    uint8_t data_buf = ( int_cfg.int_typ & 0x01 ) << 4;
    data_buf |= ( int_cfg.int_func  & 0x07 ) << 1;
    data_buf |=   int_cfg.alarm_typ & 0x01;
    return co23_generic_write( ctx, CO23_REG_INT_CFG, &data_buf, 1 );
}

err_t co23_set_alarm_threshold ( co23_t *ctx, uint16_t alarm_th_ppm ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = CO23_OK;
    if ( alarm_th_ppm > 1000 )
    {
        err_flag = CO23_ERROR;
    }
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( alarm_th_ppm >> 8 );
        data_buf[ 1 ] = ( uint8_t )   alarm_th_ppm;
        err_flag = co23_generic_write( ctx, CO23_REG_ALARM_TH_H, data_buf, 2 );
    }
    return err_flag;
}

err_t co23_set_pressure_ref ( co23_t *ctx, uint16_t pressure_mbar ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = CO23_OK;
    if ( ( pressure_mbar < 750 ) || ( pressure_mbar > 1150 ) )
    {
        err_flag = CO23_ERROR;
    }
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( pressure_mbar >> 8 );
        data_buf[ 1 ] = ( uint8_t )   pressure_mbar;
        err_flag = co23_generic_write( ctx, CO23_REG_PRESS_REF_H, data_buf, 2 );
    }
    return err_flag;
}

err_t co23_set_calib_ref ( co23_t *ctx, uint16_t calib_ppm ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = CO23_OK;
    if ( ( calib_ppm < 350 ) || ( calib_ppm > 900 ) )
    {
        err_flag = CO23_ERROR;
    }
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( calib_ppm >> 8 );
        data_buf[ 1 ] = ( uint8_t )   calib_ppm;
        err_flag = co23_generic_write( ctx, CO23_REG_CALIB_REF_H, data_buf, 2 );
    }
    return err_flag;
}

err_t co23_soft_reset_trigger ( co23_t *ctx, co23_soft_reset_value_t reset_cmd ) 
{
    return co23_generic_write( ctx, CO23_REG_SENS_RST, &reset_cmd, 1 );
}

uint8_t co23_get_pwo_pin ( co23_t *ctx ) 
{
    return digital_in_read( &ctx->pwo );
}

uint8_t co23_get_int_pin ( co23_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

static err_t co23_i2c_write ( co23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t co23_i2c_read ( co23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t co23_uart_write ( co23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t err_flag = CO23_OK;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        err_flag = co23_uart_write_reg( ctx, reg + cnt, data_in[ cnt ] );
        Delay_1ms( );
    }
    return err_flag;
}

static err_t co23_uart_read ( co23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = CO23_OK;
    uint8_t data_buf = { 0 };
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        err_flag = co23_uart_read_reg( ctx, reg + cnt, &data_buf );
        Delay_1ms( );
        data_out[ cnt ] = data_buf;
    }
    return err_flag;
}

static err_t co23_uart_write_reg ( co23_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    err_t err_flag = CO23_OK;
    uint8_t tx_buf[ 8 ] = { 0 };
    uint8_t rx_buf[ 2 ] = { 0 };

    // Initiate request Write “W”
    tx_buf[ 0 ] = CO23_UART_WRITE; 
    // Delimiter “,”
    tx_buf[ 1 ] = CO23_UART_DELIMITER;
    // Register Addr
    if ( ( reg >> 4 ) > 0x09 )
    {
        tx_buf[ 2 ] = 0x37 + ( reg >> 4 );
    }
    else
    {
        tx_buf[ 2 ] = 0x30 + ( reg >> 4 );
    }
    
    if ( ( reg & 0x0F ) > 0x09 )
    {
        tx_buf[ 3 ] = 0x37 + ( reg & 0x0F );
    }
    else
    {
        tx_buf[ 3 ] = 0x30 + ( reg & 0x0F );
    }
    // Delimiter “,”
    tx_buf[ 4 ] = 0x2C; 
    // Data to be written
    if ( ( data_in >> 4 ) > 0x09 )
    {
        tx_buf[ 5 ] = 0x37 + ( data_in >> 4 );
    }
    else
    {
        tx_buf[ 5 ] = 0x30 + ( data_in >> 4 );
    }
    
    if ( ( data_in & 0x0F ) > 0x09 )
    {
        tx_buf[ 6 ] = 0x37 + ( data_in & 0x0F );
    }
    else
    {
        tx_buf[ 6 ] = 0x30 + ( data_in & 0x0F );
    }
    // End of message “\n”
    tx_buf[ 7 ] = CO23_UART_END_OF_MESSAGE;
    
    uart_write( &ctx->uart, tx_buf, 8 );
    uart_read( &ctx->uart, rx_buf, 2 );
    
    if ( rx_buf[ 0 ] == CO23_UART_NAK )
    {
        err_flag = CO23_ERROR;    
    }
    return err_flag;
}

static err_t co23_uart_read_reg ( co23_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    err_t err_flag = CO23_OK;
    uint8_t tx_buf[ 5 ] = { 0 };
    uint8_t rx_buf[ 3 ] = { 0 };
    uint8_t res_buf[ 2 ] = { 0 };
    
    // Initiate request Read “R”
    tx_buf[ 0 ] = CO23_UART_READ;
    // Delimiter “,”
    tx_buf[ 1 ] = CO23_UART_DELIMITER; 
    // Register Addr
    if ( ( reg >> 4 ) > 0x09 )
    {
        tx_buf[ 2 ] = 0x37 + ( reg >> 4 );
    }
    else
    {
        tx_buf[ 2 ] = 0x30 + ( reg >> 4 );
    }
    
    if ( ( reg & 0x0F ) > 0x09 )
    {
        tx_buf[ 3 ] = 0x37 + ( reg & 0x0F );
    }
    else
    {
        tx_buf[ 3 ] = 0x30 + ( reg & 0x0F );
    }
    // End of message “\n”
    tx_buf[ 4 ] = CO23_UART_END_OF_MESSAGE; 

    uart_write( &ctx->uart, tx_buf, 5 );
    uart_read( &ctx->uart, rx_buf, 3 );

    uart_write( &ctx->uart, tx_buf, 5 );
    uart_read( &ctx->uart, rx_buf, 3 );
    
    // Response
    if ( rx_buf[ 0 ] > 0x41 )
    {
        res_buf[ 0 ] = rx_buf[ 0 ] - 0x37; 
    }
    else
    {
        res_buf[ 0 ] = rx_buf[ 0 ] - 0x30; 
    }
    
    if ( rx_buf[ 1 ] > 0x41 )
    {
        res_buf[ 1 ] = rx_buf[ 1 ] - 0x37;
    }
    else
    {
        res_buf[ 1 ] = rx_buf[ 1 ] - 0x30;
    }
    *data_out = res_buf[ 0 ];
    *data_out <<= 4;
    *data_out |= res_buf[ 1 ];
    
    if ( rx_buf[ 2 ] == CO23_UART_NAK )
    {
        err_flag = CO23_ERROR;
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END

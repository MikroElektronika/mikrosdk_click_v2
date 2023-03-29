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
 * @file airflow.c
 * @brief Air Flow Click Driver.
 */

#include "airflow.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                           0x00

/**
 * @brief Pressure correction.
 */
#define AIRFLOW_RESOLUTION_GREATER_125  0.7
#define AIRFLOW_RESOLUTION_LESS_125     0.05

/**
 * @brief Scale factors.
 */
#define AIRFLOW_PRESSURE_SCALE_FACTOR   256.0
#define AIRFLOW_BAR_TEMPERATURE_SCALE   100.0
#define AIRFLOW_BAR_PAS_SCALE           0.01

/**
 * @brief Status data masks.
 */
#define AIRFLOW_MASK_DIFF_DATA_READY    0x10 
#define AIRFLOW_MASK_BAR_DATA_READY     0x20


/**
 * @brief Air Flow I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airflow_i2c_write ( airflow_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Flow I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t airflow_i2c_read ( airflow_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Air Flow SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t airflow_spi_write ( airflow_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Flow SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airflow_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t airflow_spi_read ( airflow_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void airflow_cfg_setup ( airflow_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRFLOW_SET_DEV_ADDR;

    cfg->spi_speed   = 500000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = AIRFLOW_DRV_SEL_I2C;
}

void airflow_drv_interface_selection ( airflow_cfg_t *cfg, airflow_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t airflow_init ( airflow_t *ctx, airflow_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ctx->drv_sel == AIRFLOW_DRV_SEL_I2C ) 
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

        if ( i2c_master_set_timeout( &ctx->i2c, 0 ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = airflow_i2c_read;
        ctx->write_f = airflow_i2c_write;
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

        ctx->read_f  = airflow_spi_read;
        ctx->write_f = airflow_spi_write;
    }
    
    digital_in_init( &ctx->rdy, cfg->rdy );

    return 0;
}

err_t airflow_default_cfg ( airflow_t *ctx ) 
{
    err_t error_flag = AIRFLOW_ERROR;
    uint8_t sig_data[ 64 ] = { 0 };
    memset( ctx->part_number, 0, 12 );
    memset( ctx->lot_number, 0, 8 );
    memset( ctx->calibration_id, 0, 3 );
    
    if ( ctx->drv_sel == AIRFLOW_DRV_SEL_I2C )
    {
        error_flag = airflow_generic_read( ctx, AIRFLOW_I2C_CMD_GET_SIG, sig_data, 64 );
    }
    else if ( ctx->drv_sel == AIRFLOW_DRV_SEL_SPI )
    {
        error_flag = airflow_generic_read( ctx, AIRFLOW_SPI_CMD_GET_SIG, sig_data, 64 );
    }
    
    if ( error_flag >= 0 )
    {
        //firmware version
        ctx->minor_fw_ver = sig_data[ 0 ];
        ctx->major_fw_ver = sig_data[ 1 ];
        //part number
        for ( uint8_t pn = 0; pn < 11; pn++ )
        {
            ctx->part_number[ pn ] = sig_data[ 2 + pn ];
        }
        //lot number
        for ( uint8_t ln = 0; ln < 7; ln++ )
        {
            ctx->lot_number[ ln ] = sig_data[ 13 + ln ];
        }
        //pressure range
        ctx->pressure_range = ( ( uint16_t )sig_data[ 20 ] << 8 ) | sig_data[ 21 ];
        //output type
        ctx->output_type = sig_data[ 22 ];
        //scale factor
        ctx->scale_factor = ( ( uint16_t )sig_data[ 23 ] << 8 ) | sig_data[ 24 ];
        //calibration id
        ctx->calibration_id[ 0 ] = sig_data[ 25 ];
        ctx->calibration_id[ 1 ] = sig_data[ 26 ];
        //week
        ctx->week = sig_data[ 27 ];
        //year
        ctx->year = sig_data[ 28 ];
        //sequence number
        ctx->sequence_number = ( ( uint16_t )sig_data[ 29 ] << 8 ) | sig_data[ 30 ];
    }
    return error_flag;
}

err_t airflow_generic_write ( airflow_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t airflow_generic_read ( airflow_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t airflow_check_ready ( airflow_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

err_t airflow_get_differential_pressure ( airflow_t *ctx, float *pressure )
{
    err_t error_flag = AIRFLOW_ERROR;
    uint8_t sensor_data[ 8 ] = { 0 };
    int32_t press = 0;
    
    *pressure = 0.0;

    if ( AIRFLOW_DRV_SEL_I2C == ctx->drv_sel )
    {
        uint8_t sensor_cmd[ 2 ] = { AIRFLOW_I2C_CMD_CONV, AIRFLOW_BAROMETRIC_CORRECTION };
        i2c_master_write( &ctx->i2c, sensor_cmd, 2 );
        while ( !digital_in_read( &ctx->rdy ) );
        i2c_master_read( &ctx->i2c, sensor_data, 3 );
        
        press = ( ( int32_t )sensor_data[ 0 ] << 8 ) | 
                ( ( int32_t )sensor_data[ 1 ] << 16 ) | 
                ( ( int32_t )sensor_data[ 2 ] << 24 );
        press >>= 8;        
        
        error_flag = AIRFLOW_OK;
    }
    else if ( AIRFLOW_DRV_SEL_SPI == ctx->drv_sel )
    {
        uint8_t status = 0;
        uint8_t conversion_param = AIRFLOW_BAROMETRIC_CORRECTION;
        airflow_spi_write( ctx, AIRFLOW_SPI_CMD_CONV, &conversion_param, 1 );
        while ( !digital_in_read( &ctx->rdy ) );
        airflow_get_status( ctx, &status );
        
        if ( status & AIRFLOW_MASK_DIFF_DATA_READY )
        {
            airflow_spi_read( ctx, AIRFLOW_SPI_CMD_GET_DATA, sensor_data, 4 );
            
            press = ( ( int32_t )sensor_data[ 1 ] << 8 ) | 
                    ( ( int32_t )sensor_data[ 2 ] << 16 ) | 
                    ( ( int32_t )sensor_data[ 3 ] << 24 );
            press >>= 8;

            error_flag = AIRFLOW_OK;
        }
    }

    if ( AIRFLOW_OK == error_flag )
    {
        *pressure = press / AIRFLOW_PRESSURE_SCALE_FACTOR; 
    
        if ( *pressure >= 125.0 )
        {
            *pressure *= AIRFLOW_RESOLUTION_GREATER_125;
        }
        else
        {
            *pressure *= AIRFLOW_RESOLUTION_LESS_125;
        }
    }
    
    return error_flag;
}

err_t airflow_get_atmospheric_pressure ( airflow_t *ctx, float *pressure, float *temperature )
{
    err_t error_flag = AIRFLOW_ERROR;
    uint8_t sensor_data[ 8 ] = { 0 };
    uint8_t status = 0;
    uint32_t press;
    int16_t temp;
    
    *pressure = 0.0;
    *temperature = 0.0;
    if ( AIRFLOW_DRV_SEL_I2C == ctx->drv_sel )
    {
        uint8_t sensor_cmd[ 2 ] = { AIRFLOW_I2C_CMD_GET_NON_BAR, AIRFLOW_BAROMETRIC_CORRECTION };
        i2c_master_write( &ctx->i2c, sensor_cmd, 1 );
        while ( !digital_in_read( &ctx->rdy ) );
        i2c_master_read( &ctx->i2c, sensor_data, 7 );
        error_flag = AIRFLOW_OK;
    }
    else if ( AIRFLOW_DRV_SEL_SPI == ctx->drv_sel )
    {
        uint8_t conversion_param = AIRFLOW_BAROMETRIC_CORRECTION;
        airflow_spi_write( ctx, AIRFLOW_SPI_CMD_CONV, &conversion_param, 1 );
        while ( !digital_in_read( &ctx->rdy ) );
        airflow_get_status( ctx, &status );
        if ( status & AIRFLOW_MASK_BAR_DATA_READY )
        {
            airflow_spi_read( ctx, AIRFLOW_SPI_CMD_GET_BAR, sensor_data, 6 );
            error_flag = AIRFLOW_OK;
        }
    }
    
    if ( AIRFLOW_OK == error_flag )
    {
        press = ( ( uint32_t )sensor_data[ 0 ] << 0 ) | 
                ( ( uint32_t )sensor_data[ 1 ] << 8 ) |
                ( ( uint32_t )sensor_data[ 2 ] << 16 )| 
                ( ( uint32_t )sensor_data[ 3 ] << 24 );

        *pressure = press * AIRFLOW_BAR_PAS_SCALE;

        temp = sensor_data[ 4 ] | ( ( int16_t )sensor_data[ 5 ] << 8 );
            
        *temperature = temp / AIRFLOW_BAR_TEMPERATURE_SCALE;
    }
            
    return error_flag;
}

void airflow_reset_device ( airflow_t *ctx )
{
    if ( ctx->drv_sel == AIRFLOW_DRV_SEL_I2C )
    {
        airflow_generic_write( ctx, AIRFLOW_I2C_CMD_RESET, NULL, 0 );
    }
    else if ( ctx->drv_sel == AIRFLOW_DRV_SEL_SPI )
    {
        airflow_generic_write( ctx, AIRFLOW_SPI_CMD_RESET, NULL, 0 );
    }
    Delay_100ms( );
}

err_t airflow_get_status ( airflow_t *ctx, uint8_t *status )
{
    err_t error_flag = AIRFLOW_ERROR;
    if ( ctx->drv_sel == AIRFLOW_DRV_SEL_SPI )
    {
        spi_master_select_device( ctx->chip_select );
        Delay_10us();
        Delay_50us();
        error_flag = spi_master_read( &ctx->spi, status, 1 );
        Delay_10us();
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

static err_t airflow_i2c_write ( airflow_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t airflow_i2c_read ( airflow_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t airflow_spi_write ( airflow_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = AIRFLOW_OK;
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    Delay_50us( );
    error_flag |= spi_master_write( &ctx->spi, &reg, 1 );
    Delay_10us( );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        error_flag |= spi_master_write( &ctx->spi, &data_in[ cnt ], 1 );
        Delay_10us( );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t airflow_spi_read ( airflow_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tx_buf[ 2 ] = { reg , 0x00 };
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    Delay_50us( );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 1 );
    Delay_10us( );
    error_flag |= spi_master_write( &ctx->spi, tx_buf + 1, 1 );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        Delay_10us( );
        error_flag |= spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
    }
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

// ------------------------------------------------------------------------ END

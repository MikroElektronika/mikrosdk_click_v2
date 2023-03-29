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
 * @file vcpmonitor3.c
 * @brief VCP Monitor 3 Click Driver.
 */

#include "vcpmonitor3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief VCP Monitor 3 Dev bit compare.
 * @details This function compares if a bit is set in a specified place.
 */
static void dev_get_twos_comp ( int32_t *raw, uint8_t length );

/**
 * @brief VCP Monitor 3 Dev timer function.
 * @details This function deploys a 100 ms delay.
 */
static void dev_time_to_apply ( void );

/**
 * @brief VCP Monitor 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t vcpmonitor3_i2c_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief VCP Monitor 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t vcpmonitor3_i2c_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief VCP Monitor 3 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t vcpmonitor3_spi_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief VCP Monitor 3 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t vcpmonitor3_spi_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void vcpmonitor3_cfg_setup ( vcpmonitor3_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->io = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VCPMONITOR3_I2C_ADR_L_R;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = VCPMONITOR3_DRV_SEL_I2C;
}

void vcpmonitor3_drv_interface_selection ( vcpmonitor3_cfg_t *cfg, vcpmonitor3_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t vcpmonitor3_init ( vcpmonitor3_t *ctx, vcpmonitor3_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( VCPMONITOR3_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = vcpmonitor3_i2c_read;
        ctx->write_f = vcpmonitor3_i2c_write;
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

        ctx->read_f  = vcpmonitor3_spi_read;
        ctx->write_f = vcpmonitor3_spi_write;
    }

    digital_out_init( &ctx->io, cfg->io );

    digital_in_init( &ctx->alr, cfg->alr );

    if ( VCPMONITOR3_DRV_SEL_I2C == ctx->drv_sel )
    {
        spi_master_select_device( ctx->chip_select );
        digital_out_low( &ctx->io );
    }
    else
    {
        spi_master_deselect_device( ctx->chip_select );  
        digital_out_high( &ctx->io );
    }

    return 0;
}

err_t vcpmonitor3_default_cfg ( vcpmonitor3_t *ctx ) 
{
    err_t error_flag = VCPMONITOR3_OK;
    
    uint8_t tmp_data;
    
    vcpmonitor3_set_op_mode( ctx, VCPMONITOR3_CLR );
    vcpmonitor3_set_op_mode( ctx, VCPMONITOR3_NORM_OP );
    vcpmonitor3_set_op_mode( ctx, VCPMONITOR3_CONT );
    tmp_data = 0x11;
    error_flag = vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_GPIOSTATCL, &tmp_data, 1 );
    tmp_data = 0x00;
    error_flag |= vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_ALERTBCTL, &tmp_data, 1 );

    return error_flag;
}

err_t vcpmonitor3_generic_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t vcpmonitor3_generic_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

static err_t vcpmonitor3_i2c_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t vcpmonitor3_i2c_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t vcpmonitor3_spi_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = VCPMONITOR3_SPI_WR_CMD;
    tx_buf[ 1 ] = reg;
    for ( uint8_t cnt = 0; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt + 2 ] = data_in[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t vcpmonitor3_spi_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t rx_buf[ 2 ];

    rx_buf[ 0 ] = VCPMONITOR3_SPI_RD_CMD;
    rx_buf[ 1 ] = reg;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, rx_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void vcpmonitor3_wr_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *wr_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_write( ctx, reg, wr_data, n_bytes );
}

void vcpmonitor3_rd_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_read ( ctx, reg, rd_data, n_bytes );
}

void vcpmonitor3_wr_page_1 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *wr_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_1;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_write( ctx, reg, wr_data, n_bytes );
}

void vcpmonitor3_rd_page_1 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_1;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_read ( ctx, reg, rd_data, n_bytes );
}

void vcpmonitor3_set_op_mode ( vcpmonitor3_t *ctx, uint8_t op_mode )
{
    uint8_t data_buf;
    uint8_t tmp_data;

    tmp_data = VCPMONITOR3_PAGE_0;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    switch ( op_mode )
    {
        case ( VCPMONITOR3_NORM_OP ):
        {
            tmp_data = VCPMONITOR3_NORM_OP;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_SHDN ):
        {
            tmp_data = VCPMONITOR3_SHDN;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_CLR ):
        {
            tmp_data = VCPMONITOR3_CLR;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_SSHOT ):
        {
            vcpmonitor3_generic_read( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            data_buf &= ~VCPMONITOR3_CONT;
            data_buf |= VCPMONITOR3_SSHOT;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_CONT ):
        {
            vcpmonitor3_generic_read( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            data_buf &= ~VCPMONITOR3_SSHOT;
            data_buf |= VCPMONITOR3_CONT;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_RST ):
        {
            tmp_data = VCPMONITOR3_RST;
            vcpmonitor3_generic_write( ctx,  VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        default :
        {
            break;
        }
    }
}

float vcpmonitor3_read_i ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 3 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_I, data_buf, 3 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 24 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_I;
    result /= 1000.0;

    return result;
}

float vcpmonitor3_read_p ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 3 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_P, data_buf, 3 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 24 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_P;
    result /= 1000.0;

    return result;
}

float vcpmonitor3_read_v ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 2 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_V, data_buf, 2 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 16 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_V;
    result /= 1000.0;

    return result;
}

float vcpmonitor3_read_temp ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 2 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_TEMP, data_buf, 2 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 16 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_TEMP;
    result += VCPMONITOR3_OFFS_TEMP;

    return result;
}

float vcpmonitor3_read_vcc ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 2 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_VDVCC, data_buf, 2 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 16 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_VDVCC;
    result /= 1000.0;

    return result;
}

float vcpmonitor3_read_c ( vcpmonitor3_t *ctx, uint8_t accu_set1 )
{
    uint8_t data_buf[ 4 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    if ( accu_set1 )
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_C1, data_buf, 4 );
    }
    else
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_C2, data_buf, 4 );
    }

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 3 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 32 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_C1;

    return result;
}

float vcpmonitor3_read_e ( vcpmonitor3_t *ctx, uint8_t accu_set1 )
{
    uint8_t data_buf[ 4 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data =  VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    if ( accu_set1 )
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_E1, data_buf, 4 );
    }
    else
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_E2, data_buf, 4 );
    }

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 3 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 32 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_E1;

    return result;
}

float vcpmonitor3_read_tb ( vcpmonitor3_t *ctx, uint8_t accu_set1 )
{
    uint8_t data_buf[ 4 ];
    uint32_t tmp_val;
    float result;
    uint8_t tmp_data =  VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    if ( accu_set1 )
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_TB1, data_buf, 4 );
    }
    else
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_TB2, data_buf, 4 );
    }

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 3 ];

    result = ( float ) tmp_val * VCPMONITOR3_LSB_TB1;

    return result;
}

uint8_t vcpmonitor3_get_int ( vcpmonitor3_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_get_twos_comp ( int32_t *raw, uint8_t length )
{
    if ( *raw & ( ( uint32_t ) 1 << ( length - 1 ) ) )
    {
        *raw -= ( uint32_t ) 1 << length;
    }
}

static void dev_time_to_apply ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------ END

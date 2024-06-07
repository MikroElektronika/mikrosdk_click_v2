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
 * @file inclinometer3.c
 * @brief Inclinometer 3 Click Driver.
 */

#include "inclinometer3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY              0x00
#define SPI_WRITE_MASK     0x80

/**
 * @brief Calculate checksum for 4 byte data.
 * @details This function returns crc byte for input data with parameteres:
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D ( x8 + x4 + x3 + x2 + 1 )
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  XOR out 0xFF
 * @param[in] data_val : Data to calculate CRC for.
 * @return CRC data
 * @note Calculate CRC for 24 MSB's of the 32 bit dword (8 LSB's 
 * are the CRC field and are not included in CRC calculation).
 */
static uint8_t inclinometer3_calc_crc ( uint32_t data_val );

/** 
 * @brief Calculation for CRC 85 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D ( x8 + x4 + x3 + x2 + 1 )
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  XOR out 0xFF
 * @param[in] bit_value : Bit value for CRC calculation.
 * @param[in] crc : Current for CRC calculation.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t inclinometer3_crc8 ( uint8_t bit_value, uint8_t crc );

void inclinometer3_cfg_setup ( inclinometer3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t inclinometer3_init ( inclinometer3_t *ctx, inclinometer3_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t inclinometer3_default_cfg ( inclinometer3_t *ctx ) 
{
    uint8_t device_id = DUMMY;
    err_t err_flag = inclinometer3_get_sensor_id( ctx, &device_id );
    if ( INCLINOMETER3_WHOAMI == device_id )
    {
        err_flag |= inclinometer3_sw_reset( ctx );
        Delay_100ms( );
        
        err_flag |= inclinometer3_set_bank( ctx, INCLINOMETER3_SEL_BANK_0 );
        Delay_100ms( );
        
        err_flag |= inclinometer3_set_mode( ctx, INCLINOMETER3_SEL_MODE_A );
        Delay_100ms( );
    }
    else
    {
        err_flag = INCLINOMETER3_ERROR;
    }
    return err_flag;
}

err_t inclinometer3_reg_write ( inclinometer3_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf_tx[ 4 ] = { 0 };
    data_buf_tx[ 0 ] = ( ( reg & 0x1F ) << 2 ) | SPI_WRITE_MASK;
    data_buf_tx[ 1 ] = data_in >> 8;
    data_buf_tx[ 2 ] = data_in;
    data_buf_tx[ 3 ] = inclinometer3_calc_crc( ( ( ( uint32_t ) data_buf_tx[ 0 ] ) << 24 ) | 
                                          ( ( uint32_t ) data_in ) << 8 );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_buf_tx[ 0 ] );
    err_t err_flag = spi_master_read( &ctx->spi, &ctx->rtn_sts, 1 );
    err_flag |= spi_master_write( &ctx->spi, &data_buf_tx[ 1 ], 3 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    Delay_10us( );
    ctx->rtn_sts &= INCLINOMETER3_RTN_STS_BITMASK;
    return err_flag;
}

err_t inclinometer3_reg_read ( inclinometer3_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    err_t err_flag = INCLINOMETER3_OK;
    uint8_t data_frame = ( reg & 0x1F ) << 2;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t dummy = 0, crc = 0;
    crc = inclinometer3_calc_crc( ( ( uint32_t ) data_frame ) << 24 );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_frame );
    err_flag |= spi_master_read( &ctx->spi, &ctx->rtn_sts, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_set_default_write_data( &ctx->spi, crc );
    err_flag = spi_master_read( &ctx->spi, &dummy, 1 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_frame );
    err_flag |= spi_master_read( &ctx->spi, &ctx->rtn_sts, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_set_default_write_data( &ctx->spi, crc );
    err_flag = spi_master_read( &ctx->spi, &dummy, 1 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    
    *data_out = ( ( ( uint16_t ) data_buf[ 0 ] ) << 8 ) | data_buf[ 1 ];
    Delay_10us( );
    ctx->rtn_sts &= INCLINOMETER3_RTN_STS_BITMASK;
    return err_flag;
}

err_t inclinometer3_cmd_write ( inclinometer3_t *ctx, uint32_t op_cmd )
{
    uint8_t data_buf_tx[ 4 ] = { 0 };
    data_buf_tx[ 0 ] = op_cmd >> 24;
    data_buf_tx[ 1 ] = op_cmd >> 16;
    data_buf_tx[ 2 ] = op_cmd >> 8;
    data_buf_tx[ 3 ] = op_cmd;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_buf_tx[ 0 ] );
    err_t err_flag = spi_master_read( &ctx->spi, &ctx->rtn_sts, 1 );
    err_flag |= spi_master_write( &ctx->spi, &data_buf_tx[ 1 ], 3 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    Delay_10us( );
    
    ctx->rtn_sts &= INCLINOMETER3_RTN_STS_BITMASK;
    return err_flag;
}

err_t inclinometer3_cmd_read ( inclinometer3_t *ctx, uint32_t op_cmd, uint32_t *data_out )
{
    err_t err_flag = INCLINOMETER3_OK;
    uint8_t data_buf_tx[ 4 ] = { 0 };
    uint8_t data_buf_rx[ 4 ] = { 0 };
    data_buf_tx[ 0 ] = op_cmd >> 24;
    data_buf_tx[ 1 ] = op_cmd >> 16;
    data_buf_tx[ 2 ] = op_cmd >> 8;
    data_buf_tx[ 3 ] = op_cmd;
    
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t n_cnt = 0; n_cnt < 4; n_cnt++ )
    {
        spi_master_set_default_write_data( &ctx->spi, data_buf_tx[ n_cnt ] );
        err_flag |= spi_master_read( &ctx->spi, &data_buf_rx[ n_cnt ], 1 );
    }
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );

    spi_master_select_device( ctx->chip_select );
    for ( uint8_t n_cnt = 0; n_cnt < 4; n_cnt++ )
    {
        spi_master_set_default_write_data( &ctx->spi, data_buf_tx[ n_cnt ] );
        err_flag |= spi_master_read( &ctx->spi, &data_buf_rx[ n_cnt ], 1 );
    }
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    
    *data_out = ( ( uint32_t ) data_buf_rx[ 0 ] << 24 ) | 
                ( ( uint32_t ) data_buf_rx[ 1 ] << 16 ) | 
                ( ( uint32_t ) data_buf_rx[ 2 ] << 8 )  | 
                  data_buf_rx[ 3 ];
               
    Delay_10us( );
    return err_flag;
}

err_t inclinometer3_set_bank ( inclinometer3_t *ctx, uint8_t bank )
{
    err_t err_flag = INCLINOMETER3_OK;
    if ( INCLINOMETER3_SEL_BANK_0 == bank )
    {
        err_flag |= inclinometer3_cmd_write( ctx, INCLINOMETER3_CMD_SWITCH_TO_BANK_0 );
    }
    else if ( INCLINOMETER3_SEL_BANK_1 == bank )
    {
        err_flag |= inclinometer3_cmd_write( ctx, INCLINOMETER3_CMD_SWITCH_TO_BANK_1 );
    }
    return err_flag;
}

err_t inclinometer3_sw_reset ( inclinometer3_t *ctx )
{
    return inclinometer3_cmd_write( ctx, INCLINOMETER3_CMD_SW_RESET );
}

err_t inclinometer3_get_sensor_id ( inclinometer3_t *ctx, uint8_t *device_id )
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = inclinometer3_reg_read( ctx, INCLINOMETER3_REG_WHOAMI, &data_buf );
    *device_id = ( uint8_t ) data_buf;
    return err_flag;
}

err_t inclinometer3_get_status ( inclinometer3_t *ctx, uint32_t *status )
{
    return inclinometer3_cmd_read( ctx, INCLINOMETER3_CMD_READ_STATUS, status );
}

err_t inclinometer3_set_mode ( inclinometer3_t *ctx, uint8_t mode )
{
    err_t err_flag = INCLINOMETER3_OK;
    if ( INCLINOMETER3_SEL_MODE_A == mode )
    {
        err_flag |= inclinometer3_cmd_write( ctx, INCLINOMETER3_CMD_CHANGE_TO_MODE_A );
        ctx->sensitivity = INCLINOMETER3_ACC_SENS_MODE_A;
    }
    else if ( INCLINOMETER3_SEL_MODE_B == mode )
    {
        err_flag |= inclinometer3_cmd_write( ctx, INCLINOMETER3_CMD_CHANGE_TO_MODE_B );
        ctx->sensitivity = INCLINOMETER3_ACC_SENS_MODE_B;
    }
    return err_flag;
}

err_t inclinometer3_get_axes_data ( inclinometer3_t *ctx, int16_t *x_data, int16_t *y_data )
{
    uint32_t data_buf = DUMMY;
    int32_t axes = DUMMY;
    err_t err_flag = inclinometer3_cmd_read( ctx, INCLINOMETER3_CMD_READ_ACC_X, &data_buf );
    data_buf <<= 8;
    axes = ( int32_t ) data_buf;
    axes >>= 16; 
    *x_data = ( int16_t ) axes;

    err_flag |= inclinometer3_cmd_read( ctx, INCLINOMETER3_CMD_READ_ACC_Y, &data_buf );
    data_buf <<= 8;
    axes = ( int32_t ) data_buf;
    axes >>= 16; 
    *y_data = ( int16_t ) axes;
    return err_flag;
}

err_t inclinometer3_get_axes ( inclinometer3_t *ctx, float *x_axes, float *y_axes )
{
    int16_t x_data = DUMMY, y_data = DUMMY;
    err_t err_flag = inclinometer3_get_axes_data( ctx, &x_data, &y_data );
    *x_axes = ( ( float ) x_data ) / ctx->sensitivity;
    *y_axes = ( ( float ) y_data ) / ctx->sensitivity;
    return err_flag;
}

err_t inclinometer3_get_temp_data ( inclinometer3_t *ctx, int16_t *temp_data )
{
    uint32_t data_buf = DUMMY;
    int32_t tmp_data = DUMMY;
    err_t err_flag = inclinometer3_cmd_read( ctx, INCLINOMETER3_CMD_READ_TEMP, &data_buf );
    data_buf <<= 8;
    tmp_data = ( int32_t ) data_buf;
    tmp_data >>= 16; 
    *temp_data = ( int16_t ) tmp_data;
    return err_flag;
}

err_t inclinometer3_get_temperature ( inclinometer3_t *ctx, float *temperature )
{
    int16_t tmp_data = DUMMY;
    err_t err_flag = inclinometer3_get_temp_data( ctx, &tmp_data );
    err_flag |= inclinometer3_get_temp_data( ctx, &tmp_data );
    *temperature = ( float ) tmp_data;
    *temperature /= INCLINOMETER3_TEMP_SENS;
    *temperature -= INCLINOMETER3_TEMP_CONVERT;
    return err_flag;
}

static uint8_t inclinometer3_calc_crc ( uint32_t data_val )
{
    uint8_t bit_value;
    uint8_t crc = 0xFF;
    for ( uint8_t bit_index = 31; bit_index > 7; bit_index-- )
    {
        bit_value = (uint8_t) ( ( data_val >> bit_index ) & 0x01 );
        crc = inclinometer3_crc8( bit_value, crc );
    }
    return ~crc;
}

static uint8_t inclinometer3_crc8 ( uint8_t bit_value, uint8_t crc )
{
    uint8_t temp = ( uint8_t ) ( crc & 0x80 );
    if ( 0x01 == bit_value )
    {
        temp ^= 0x80;
    }
    crc <<= 1;
    if ( 0 < temp )
    {
        crc ^= 0x1D;
    }
    return crc;
}

// ------------------------------------------------------------------------- END

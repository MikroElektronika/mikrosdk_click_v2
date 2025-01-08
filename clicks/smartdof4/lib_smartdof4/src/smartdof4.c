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
 * @file smartdof4.c
 * @brief Smart DOF 4 Click Driver.
 */

#include "smartdof4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY       0x00
#define DUMMY_WAKE  0xAA

void smartdof4_cfg_setup ( smartdof4_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->wup  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTDOF4_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMARTDOF4_DRV_SEL_I2C;
}

void smartdof4_drv_interface_sel ( smartdof4_cfg_t *cfg, smartdof4_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smartdof4_init ( smartdof4_t *ctx, smartdof4_cfg_t *cfg ) 
{
    digital_out_init( &ctx->wup, cfg->wup );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->drv_sel = cfg->drv_sel;

    if ( SMARTDOF4_DRV_SEL_I2C == ctx->drv_sel ) 
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

        digital_out_low( &ctx->wup );
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
        
        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY_WAKE ) ) 
        {
            return SPI_MASTER_ERROR;
        }
        uint8_t dummy_read = 0;
        if ( SPI_MASTER_ERROR == spi_master_read( &ctx->spi, &dummy_read, 1 ) )
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
        {
            return SPI_MASTER_ERROR;
        }
        digital_out_high( &ctx->wup );
    }

    return SMARTDOF4_OK;
}

err_t smartdof4_default_cfg ( smartdof4_t *ctx ) 
{
    err_t error_flag = SMARTDOF4_OK;
    ctx->cmd_seq_num = 0;
    memset ( ctx->ch_seq_num, 0, sizeof ( ctx->ch_seq_num ) );
    smartdof4_reset_device ( ctx );

    // Device sends 3 packets after HW reset
    error_flag |= smartdof4_read_packet ( ctx );
    error_flag |= smartdof4_read_packet ( ctx );
    error_flag |= smartdof4_read_packet ( ctx );

    // Reinitialize device
    uint8_t cmd = 0;
    uint8_t cmd_params[ 11 ] = { 0 };
    cmd_params[ 0 ] = SMARTDOF4_CMD_INIT_SUB_REINIT;
    error_flag |= smartdof4_cmd_req ( ctx, SMARTDOF4_CMD_INIT, cmd_params );
    Delay_100ms ( );
    Delay_100ms ( );
    error_flag |= smartdof4_cmd_resp ( ctx, &cmd, cmd_params );
    if ( ( SMARTDOF4_CMD_INIT != cmd ) || 
         ( SMARTDOF4_CMD_INIT_STATUS_OK != cmd_params[ 0 ] ) || 
         ( SMARTDOF4_CMD_INIT_SUB_REINIT != cmd_params[ 1 ] ) )
    {
        error_flag |= SMARTDOF4_ERROR;
    }

    // Configures and enables accel, gyro, and magnetometer sensors
    smartdof4_feature_t feat;
    feat.flags = SMARTDOF4_FEATURE_FLAGS;
    feat.change_sens = SMARTDOF4_FEATURE_CHANCE_SENS;
    feat.rep_interval_us = SMARTDOF4_FEATURE_REP_INTERVAL_US;
    feat.batch_interval_us = SMARTDOF4_FEATURE_BATCH_INTERVAL_US;
    feat.sensor_spec = SMARTDOF4_FEATURE_SENSOR_SPEC;
    
    feat.rep_id = SMARTDOF4_REP_ID_ACCEL;
    error_flag |= smartdof4_feature_set ( ctx, &feat );
    feat.rep_id = SMARTDOF4_REP_ID_GYRO;
    error_flag |= smartdof4_feature_set ( ctx, &feat );
    feat.rep_id = SMARTDOF4_REP_ID_MAGNET;
    error_flag |= smartdof4_feature_set ( ctx, &feat );

    Delay_100ms ( );
    return error_flag;
}

err_t smartdof4_send_packet ( smartdof4_t *ctx, uint8_t ch_num, uint8_t *payload, uint16_t len )
{
    err_t error_flag = SMARTDOF4_OK;
    uint8_t shtp_wbuf[ 132 ];
    uint16_t byte_cnt = 0;
    if ( ( len > 128 ) || ( ch_num > SMARTDOF4_CH_GYRO_VECTOR ) )
    {
        return SMARTDOF4_ERROR;
    }
    ctx->shtp.channel = 0;
    ctx->shtp.ch_seq_num = 0;
    ctx->shtp.payload_len = 0;
    memset ( ctx->shtp.payload, 0, sizeof ( ctx->shtp.payload ) );

    shtp_wbuf[ 0 ] = ( uint8_t ) ( ( len + 4 ) & 0xFF );
    shtp_wbuf[ 1 ] = ( uint8_t ) ( ( ( len + 4 ) >> 8 ) & 0xFF );
    shtp_wbuf[ 2 ] = ch_num;
    shtp_wbuf[ 3 ] = ctx->ch_seq_num[ ch_num ]++;
    if ( ( NULL != payload ) && ( len > 0 ) )
    {
        memcpy ( &shtp_wbuf[ 4 ], payload, len );
    }
    if ( SMARTDOF4_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        error_flag |= i2c_master_write( &ctx->i2c, shtp_wbuf, len + 4 );
    }
    else
    {
        smartdof4_set_wup_pin ( ctx, 0 );
        if ( SMARTDOF4_ERROR == smartdof4_wait_ready ( ctx, SMARTDOF4_TIMEOUT_MS ) )
        {
            smartdof4_set_wup_pin ( ctx, 1 );
            return SMARTDOF4_ERROR;
        }
        spi_master_select_device( ctx->chip_select );

        for ( byte_cnt = 0; byte_cnt < ( len + 4 ); byte_cnt++ )
        {
            spi_master_set_default_write_data( &ctx->spi, shtp_wbuf[ byte_cnt ] );
            error_flag |= spi_master_read( &ctx->spi, &shtp_wbuf[ byte_cnt ], 1 );
        }
        spi_master_set_default_write_data( &ctx->spi, DUMMY );
        ctx->shtp.payload_len = ( ( uint16_t ) ( shtp_wbuf[ 1 ] & 0x7F ) << 8 ) | shtp_wbuf[ 0 ];
        ctx->shtp.channel = shtp_wbuf[ 2 ];
        ctx->shtp.ch_seq_num = shtp_wbuf[ 3 ];
        if ( ctx->shtp.payload_len > 4 )
        {
            ctx->shtp.payload_len -= 4;
        }
        else
        {
            ctx->shtp.payload_len = 0;
        }

        if ( ctx->shtp.payload_len > len )
        {
            memcpy ( ctx->shtp.payload, &shtp_wbuf[ 4 ], len );
            error_flag |= spi_master_read( &ctx->spi, &ctx->shtp.payload[ len ], ctx->shtp.payload_len - len );
        }
        else
        {
            memcpy ( ctx->shtp.payload, &shtp_wbuf[ 4 ], ctx->shtp.payload_len );
        }
        
        spi_master_deselect_device( ctx->chip_select );
        smartdof4_set_wup_pin ( ctx, 1 );
    }
    Delay_10ms ( );
    return error_flag;
}

err_t smartdof4_read_packet ( smartdof4_t *ctx )
{
    err_t error_flag = SMARTDOF4_OK;
    uint8_t header_buf[ 4 ] = { 0 };
    ctx->shtp.channel = 0;
    ctx->shtp.ch_seq_num = 0;
    ctx->shtp.payload_len = 0;
    memset ( ctx->shtp.payload, 0, sizeof ( ctx->shtp.payload ) );

    if ( SMARTDOF4_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        if ( SMARTDOF4_ERROR == smartdof4_wait_ready ( ctx, SMARTDOF4_TIMEOUT_MS ) )
        {
            return SMARTDOF4_ERROR;
        }
        error_flag |= i2c_master_read( &ctx->i2c, header_buf, 4 );
        ctx->shtp.payload_len = ( ( uint16_t ) ( header_buf[ 1 ] & 0x7F ) << 8 ) | header_buf[ 0 ];
        ctx->shtp.channel = header_buf[ 2 ];
        ctx->shtp.ch_seq_num = header_buf[ 3 ];
        if ( ctx->shtp.payload_len > 4 )
        {
            ctx->shtp.payload_len -= 4;
        }
        else
        {
            ctx->shtp.payload_len = 0;
        }

        if ( ctx->shtp.payload_len > 0 )
        {
            error_flag |= i2c_master_read( &ctx->i2c, ctx->shtp.payload, ctx->shtp.payload_len + 4 );
            memmove ( ctx->shtp.payload, &ctx->shtp.payload[ 4 ], ctx->shtp.payload_len );
        }
    }
    else
    {
        smartdof4_set_wup_pin ( ctx, 0 );
        if ( SMARTDOF4_ERROR == smartdof4_wait_ready ( ctx, SMARTDOF4_TIMEOUT_MS ) )
        {
            smartdof4_set_wup_pin ( ctx, 1 );
            return SMARTDOF4_ERROR;
        }
        spi_master_select_device( ctx->chip_select );

        error_flag |= spi_master_read( &ctx->spi, header_buf, 4 );
        ctx->shtp.payload_len = ( ( uint16_t ) ( header_buf[ 1 ] & 0x7F ) << 8 ) | header_buf[ 0 ];
        ctx->shtp.channel = header_buf[ 2 ];
        ctx->shtp.ch_seq_num = header_buf[ 3 ];
        if ( ctx->shtp.payload_len > 4 )
        {
            ctx->shtp.payload_len -= 4;
        }
        else
        {
            ctx->shtp.payload_len = 0;
        }

        if ( ctx->shtp.payload_len > 0 )
        {
            error_flag |= spi_master_read( &ctx->spi, ctx->shtp.payload, ctx->shtp.payload_len );
        }
        
        spi_master_deselect_device( ctx->chip_select );
        smartdof4_set_wup_pin ( ctx, 1 );
    }
    Delay_10ms ( );
    return error_flag;
}

void smartdof4_set_rst_pin ( smartdof4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void smartdof4_set_wup_pin ( smartdof4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

uint8_t smartdof4_get_int_pin ( smartdof4_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void smartdof4_reset_device ( smartdof4_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_10ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    Delay_100ms ( );
}

err_t smartdof4_wait_ready ( smartdof4_t *ctx, uint16_t timeout_ms )
{
    uint32_t timeout_cnt = 0;
    while ( smartdof4_get_int_pin ( ctx ) )
    {
        if ( ( ( ++timeout_cnt ) / 20 ) >= timeout_ms )
        {
            return SMARTDOF4_ERROR;
        }
        Delay_50us ( );
    }
    return SMARTDOF4_OK;
}

err_t smartdof4_read_pid ( smartdof4_t *ctx, smartdof4_pid_t *pid )
{
    uint8_t payload[ 2 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_PROD_ID_REQ;
    error_flag |= smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 2 );
    if ( SMARTDOF4_REP_ID_PROD_ID_RESP != ctx->shtp.payload[ 0 ] )
    {
        error_flag |= smartdof4_read_packet ( ctx );
    }

    if ( ( SMARTDOF4_REP_ID_PROD_ID_RESP != ctx->shtp.payload[ 0 ] ) ||
         ( ctx->shtp.payload_len < 16 ) )
    {
        error_flag |= SMARTDOF4_ERROR;
    }

    if ( SMARTDOF4_OK == error_flag )
    {
        pid->reset_cause = ctx->shtp.payload[ 1 ];
        pid->sw_ver_major = ctx->shtp.payload[ 2 ];
        pid->sw_ver_minor = ctx->shtp.payload[ 3 ];
        pid->sw_part_num = ( ( uint32_t ) ctx->shtp.payload[ 7 ] << 24 ) | 
                           ( ( uint32_t ) ctx->shtp.payload[ 6 ] << 16 ) | 
                           ( ( uint16_t ) ctx->shtp.payload[ 5 ] << 8 ) | 
                           ctx->shtp.payload[ 4 ];
        pid->sw_build_num = ( ( uint32_t ) ctx->shtp.payload[ 11 ] << 24 ) | 
                            ( ( uint32_t ) ctx->shtp.payload[ 10 ] << 16 ) | 
                            ( ( uint16_t ) ctx->shtp.payload[ 9 ] << 8 ) | 
                            ctx->shtp.payload[ 8 ];
        pid->sw_ver_patch = ( ( uint16_t ) ctx->shtp.payload[ 13 ] << 8 ) | 
                            ctx->shtp.payload[ 12 ];
    }
    return error_flag;
}

err_t smartdof4_frs_wr_req ( smartdof4_t *ctx, uint16_t rec_id, uint16_t len )
{
    uint8_t payload[ 6 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_FRS_WR_REQ;
    payload[ 2 ] = ( uint8_t ) ( len & 0xFF );
    payload[ 3 ] = ( uint8_t ) ( ( len >> 8 ) & 0xFF );
    payload[ 4 ] = ( uint8_t ) ( rec_id & 0xFF );
    payload[ 5 ] = ( uint8_t ) ( ( rec_id >> 8 ) & 0xFF );
    return smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 6 );
}

err_t smartdof4_frs_wr_data_req ( smartdof4_t *ctx, uint16_t offset, uint32_t data0_in, uint32_t data1_in )
{
    uint8_t payload[ 12 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_FRS_WR_DATA;
    payload[ 2 ] = ( uint8_t ) ( offset & 0xFF );
    payload[ 3 ] = ( uint8_t ) ( ( offset >> 8 ) & 0xFF );
    payload[ 4 ] = ( uint8_t ) ( data0_in & 0xFF );
    payload[ 5 ] = ( uint8_t ) ( ( data0_in >> 8 ) & 0xFF );
    payload[ 6 ] = ( uint8_t ) ( ( data0_in >> 16 ) & 0xFF );
    payload[ 7 ] = ( uint8_t ) ( ( data0_in >> 24 ) & 0xFF );
    payload[ 8 ] = ( uint8_t ) ( data1_in & 0xFF );
    payload[ 9 ] = ( uint8_t ) ( ( data1_in >> 8 ) & 0xFF );
    payload[ 10 ] = ( uint8_t ) ( ( data1_in >> 16 ) & 0xFF );
    payload[ 11 ] = ( uint8_t ) ( ( data1_in >> 24 ) & 0xFF );
    return smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 12 );
}

err_t smartdof4_frs_wr_resp ( smartdof4_t *ctx, uint16_t *offset, uint8_t *status )
{
    if ( ( NULL == offset ) || ( NULL == status ) )
    {
        return SMARTDOF4_ERROR;
    }
    err_t error_flag = SMARTDOF4_OK;
    if ( SMARTDOF4_REP_ID_FRS_WR_RESP != ctx->shtp.payload[ 0 ] )
    {
        error_flag |= smartdof4_read_packet ( ctx );
    }
    if ( SMARTDOF4_OK == error_flag )
    {
        *status = ctx->shtp.payload[ 1 ];
        *offset = ( ( uint16_t ) ctx->shtp.payload[ 3 ] << 8 ) | ctx->shtp.payload[ 2 ];
    }
    return error_flag;
}

err_t smartdof4_frs_rd_req ( smartdof4_t *ctx, uint16_t rec_id )
{
    uint8_t payload[ 8 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_FRS_RD_REQ;
    payload[ 4 ] = ( uint8_t ) ( rec_id & 0xFF );
    payload[ 5 ] = ( uint8_t ) ( ( rec_id >> 8 ) & 0xFF );
    return smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 8 );
}

err_t smartdof4_frs_rd_resp ( smartdof4_t *ctx, uint16_t *offset, uint8_t *status, 
                              uint32_t *data0_out, uint32_t *data1_out, uint16_t *rec_id )
{
    if ( ( NULL == offset ) || ( NULL == status ) || 
         ( NULL == data0_out ) || ( NULL == data1_out ) || ( NULL == rec_id ) )
    {
        return SMARTDOF4_ERROR;
    }
    err_t error_flag = SMARTDOF4_OK;
    if ( SMARTDOF4_REP_ID_FRS_RD_RESP != ctx->shtp.payload[ 0 ] )
    {
        error_flag |= smartdof4_read_packet ( ctx );
    }
    if ( SMARTDOF4_OK == error_flag )
    {
        *status = ctx->shtp.payload[ 1 ];
        *offset = ( ( uint16_t ) ctx->shtp.payload[ 3 ] << 8 ) | ctx->shtp.payload[ 2 ];
        *data0_out = ( ( uint32_t ) ctx->shtp.payload[ 7 ] << 24 ) | 
                     ( ( uint32_t ) ctx->shtp.payload[ 6 ] << 16 ) | 
                     ( ( uint16_t ) ctx->shtp.payload[ 5 ] << 8 ) | 
                     ctx->shtp.payload[ 4 ];
        *data1_out = ( ( uint32_t ) ctx->shtp.payload[ 11 ] << 24 ) | 
                     ( ( uint32_t ) ctx->shtp.payload[ 10 ] << 16 ) | 
                     ( ( uint16_t ) ctx->shtp.payload[ 9 ] << 8 ) | 
                     ctx->shtp.payload[ 8 ];
        *rec_id = ( ( uint16_t ) ctx->shtp.payload[ 13 ] << 8 ) | ctx->shtp.payload[ 12 ];
    }
    return error_flag;
}

err_t smartdof4_cmd_req ( smartdof4_t *ctx, uint8_t cmd, uint8_t *params )
{
    uint8_t payload[ 12 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_CMD_REQ;
    payload[ 1 ] = ctx->cmd_seq_num++;
    payload[ 2 ] = cmd;
    memcpy ( &payload[ 3 ], params, 9 );
    return smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 12 );
}

err_t smartdof4_cmd_resp ( smartdof4_t *ctx, uint8_t *cmd, uint8_t *params )
{
    if ( ( NULL == cmd ) || ( NULL == params ) )
    {
        return SMARTDOF4_ERROR;
    }
    err_t error_flag = SMARTDOF4_OK;
    if ( SMARTDOF4_REP_ID_CMD_RESP != ctx->shtp.payload[ 0 ] )
    {
        error_flag |= smartdof4_read_packet ( ctx );
    }
    if ( SMARTDOF4_OK == error_flag )
    {
        *cmd = ctx->shtp.payload[ 2 ];
        memcpy ( params, &ctx->shtp.payload[ 5 ], 11 );
    }
    return error_flag;
}

err_t smartdof4_feature_req ( smartdof4_t *ctx, uint8_t rep_id )
{
    uint8_t payload[ 2 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_GET_FEAT_REQ;
    payload[ 1 ] = rep_id;
    return smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 2 );
}

err_t smartdof4_feature_set ( smartdof4_t *ctx, smartdof4_feature_t *feat )
{
    uint8_t payload[ 17 ] = { 0 };
    err_t error_flag = SMARTDOF4_OK;
    payload[ 0 ] = SMARTDOF4_REP_ID_SET_FEAT_CMD;
    payload[ 1 ] = feat->rep_id;
    payload[ 2 ] = feat->flags;
    payload[ 3 ] = ( uint8_t ) ( feat->change_sens & 0xFF );
    payload[ 4 ] = ( uint8_t ) ( ( feat->change_sens >> 8 ) & 0xFF );
    payload[ 5 ] = ( uint8_t ) ( feat->rep_interval_us & 0xFF );
    payload[ 6 ] = ( uint8_t ) ( ( feat->rep_interval_us >> 8 ) & 0xFF );
    payload[ 7 ] = ( uint8_t ) ( ( feat->rep_interval_us >> 16 ) & 0xFF );
    payload[ 8 ] = ( uint8_t ) ( ( feat->rep_interval_us >> 24 ) & 0xFF );
    payload[ 9 ] = ( uint8_t ) ( feat->batch_interval_us & 0xFF );
    payload[ 10 ] = ( uint8_t ) ( ( feat->batch_interval_us >> 8 ) & 0xFF );
    payload[ 11 ] = ( uint8_t ) ( ( feat->batch_interval_us >> 16 ) & 0xFF );
    payload[ 12 ] = ( uint8_t ) ( ( feat->batch_interval_us >> 24 ) & 0xFF );
    payload[ 13 ] = ( uint8_t ) ( feat->sensor_spec & 0xFF );
    payload[ 14 ] = ( uint8_t ) ( ( feat->sensor_spec >> 8 ) & 0xFF );
    payload[ 15 ] = ( uint8_t ) ( ( feat->sensor_spec >> 16 ) & 0xFF );
    payload[ 16 ] = ( uint8_t ) ( ( feat->sensor_spec >> 24 ) & 0xFF );
    return smartdof4_send_packet ( ctx, SMARTDOF4_CH_CTRL, payload, 17 );
}

err_t smartdof4_feature_resp ( smartdof4_t *ctx, smartdof4_feature_t *feat )
{
    if ( NULL == feat )
    {
        return SMARTDOF4_ERROR;
    }
    err_t error_flag = SMARTDOF4_OK;
    if ( SMARTDOF4_REP_ID_GET_FEAT_RESP != ctx->shtp.payload[ 0 ] )
    {
        error_flag |= smartdof4_read_packet ( ctx );
    }
    if ( SMARTDOF4_OK == error_flag )
    {
        feat->rep_id = ctx->shtp.payload[ 1 ];
        feat->flags = ctx->shtp.payload[ 2 ];
        feat->change_sens = ( ( uint16_t ) ctx->shtp.payload[ 4 ] << 8 ) | ctx->shtp.payload[ 3 ];
        feat->rep_interval_us = ( ( uint32_t ) ctx->shtp.payload[ 8 ] << 24 ) | 
                                ( ( uint32_t ) ctx->shtp.payload[ 7 ] << 16 ) | 
                                ( ( uint16_t ) ctx->shtp.payload[ 6 ] << 8 ) | 
                                ctx->shtp.payload[ 5 ];
        feat->batch_interval_us = ( ( uint32_t ) ctx->shtp.payload[ 12 ] << 24 ) | 
                                  ( ( uint32_t ) ctx->shtp.payload[ 11 ] << 16 ) | 
                                  ( ( uint16_t ) ctx->shtp.payload[ 10 ] << 8 ) | 
                                  ctx->shtp.payload[ 9 ];
        feat->sensor_spec = ( ( uint32_t ) ctx->shtp.payload[ 16 ] << 24 ) | 
                            ( ( uint32_t ) ctx->shtp.payload[ 15 ] << 16 ) | 
                            ( ( uint16_t ) ctx->shtp.payload[ 14 ] << 8 ) | 
                            ctx->shtp.payload[ 13 ];
    }
    return error_flag;
}

err_t smartdof4_read_data ( smartdof4_t *ctx, smartdof4_axis_t *accel, 
                            smartdof4_axis_t *gyro, smartdof4_axis_t *mag )
{
    if ( ( NULL == accel ) || ( NULL == gyro ) || ( NULL == mag ) )
    {
        return SMARTDOF4_ERROR;
    }
    int16_t raw_x = 0;
    int16_t raw_y = 0;
    int16_t raw_z = 0;
    uint8_t cnt = 0;

    if ( SMARTDOF4_OK == smartdof4_read_packet ( ctx ) )
    {
        if ( SMARTDOF4_REP_ID_BASE_TIMESTAMP == ctx->shtp.payload[ 0 ] )
        {
            for ( cnt = 15; ( cnt <= 35 ) && ( cnt <= ctx->shtp.payload_len ); cnt += 10 )
            {
                raw_x = ( ( int16_t ) ctx->shtp.payload[ cnt - 5 ] << 8 ) | ctx->shtp.payload[ cnt - 6 ];
                raw_y = ( ( int16_t ) ctx->shtp.payload[ cnt - 3 ] << 8 ) | ctx->shtp.payload[ cnt - 4 ];
                raw_z = ( ( int16_t ) ctx->shtp.payload[ cnt - 1 ] << 8 ) | ctx->shtp.payload[ cnt - 2 ];
                if ( SMARTDOF4_REP_ID_ACCEL == ctx->shtp.payload[ cnt - 10 ] )
                {
                    accel->x = raw_x * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_ACCEL ) / SMARTDOF4_GRAVITY;
                    accel->y = raw_y * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_ACCEL ) / SMARTDOF4_GRAVITY;
                    accel->z = raw_z * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_ACCEL ) / SMARTDOF4_GRAVITY;
                }
                else if ( SMARTDOF4_REP_ID_GYRO == ctx->shtp.payload[ cnt - 10 ] )
                {
                    gyro->x = raw_x * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_GYRO_CALIB ) * SMARTDOF4_RAD_TO_DEG;
                    gyro->y = raw_y * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_GYRO_CALIB ) * SMARTDOF4_RAD_TO_DEG;
                    gyro->z = raw_z * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_GYRO_CALIB ) * SMARTDOF4_RAD_TO_DEG;
                }
                else if ( SMARTDOF4_REP_ID_MAGNET == ctx->shtp.payload[ cnt - 10 ] )
                {
                    mag->x = raw_x * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_MAGNET_CALIB );
                    mag->y = raw_y * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_MAGNET_CALIB );
                    mag->z = raw_z * SMARTDOF4_SCALEQ ( SMARTDOF4_QPOINT_MAGNET_CALIB );
                }
            }
            return SMARTDOF4_OK;
        }
    }
    return SMARTDOF4_ERROR;
}

// ------------------------------------------------------------------------ END

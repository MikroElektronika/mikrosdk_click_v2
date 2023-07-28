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
 * @file amfm2.c
 * @brief AM/FM 2 Click Driver.
 */

#include "amfm2.h"

/**
 * @brief Dummy and timeout data.
 * @details Definition of dummy and timeout data.
 */
#define DUMMY             0x00
#define AMFM2_TIMEOUT     10000u

void amfm2_cfg_setup ( amfm2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ema   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMFM2_DEVICE_ADDRESS_GND;
}

err_t amfm2_init ( amfm2_t *ctx, amfm2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ema, cfg->ema );
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->gp1, cfg->gp1 );
    digital_in_init( &ctx->gp2, cfg->gp2 );

    return I2C_MASTER_SUCCESS;
}

err_t amfm2_default_cfg ( amfm2_t *ctx ) 
{
    amfm2_hw_reset( ctx );

    uint8_t rsp_status = DUMMY;
    uint8_t arg[ 3 ] = { AMFM2_PWRUP_ARG_CTSIEN  | 
                         AMFM2_PWRUP_ARG_GPO2OEN | 
                         AMFM2_PWRUP_ARG_XOSCEN  | 
                         AMFM2_PWRUP_ARG_FUNC_FMRECEIVE, 
                         AMFM2_PWRUP_ARG_OPMODE_ANALOGOUT };
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_POWER_UP, arg, 3, &rsp_status, 1 );
    
    amfm2_headphone_amp_enable( ctx );
    
    err_flag |= amfm2_sound_on( ctx, &rsp_status );
    err_flag |= amfm2_check_clear_to_send( ctx );
    
    return err_flag;
}

err_t amfm2_generic_write ( amfm2_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = cmd;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t amfm2_generic_read ( amfm2_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, len );
}

void amfm2_hw_reset ( amfm2_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

void amfm2_headphone_amp_enable ( amfm2_t *ctx )
{
    digital_out_high( &ctx->ema );
}

void amfm2_headphone_amp_disable ( amfm2_t *ctx )
{
    digital_out_low( &ctx->ema );
}

uint8_t amfm2_get_gp1 ( amfm2_t *ctx )
{
    return digital_in_read( &ctx->gp1 );
}

uint8_t amfm2_get_gp2 ( amfm2_t *ctx )
{
    return digital_in_read( &ctx->gp2 );
}

void amfm2_rst_set ( amfm2_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->rst, pin_state );
}

err_t amfm2_wait_rsp ( amfm2_t *ctx )
{
    err_t err_flag = AMFM2_OK;
    uint8_t data_buf = DUMMY;
    do
    {
        Delay_500us( );
        err_flag |= i2c_master_read( &ctx->i2c, &data_buf, 1 );
    } 
    while ( !( data_buf & AMFM2_RSP_STATUS_CTS ) );
    return err_flag;
}

err_t amfm2_set_command ( amfm2_t *ctx, uint8_t cmd, uint8_t *arg, 
                          uint8_t arg_len, uint8_t *rsp, uint8_t rsp_len )
{
    err_t err_flag = amfm2_generic_write( ctx, cmd, arg, arg_len );
    err_flag |= amfm2_wait_rsp( ctx );
    err_flag |= amfm2_generic_read( ctx, DUMMY, rsp, rsp_len );
    return err_flag;
}

err_t amfm2_get_response ( amfm2_t *ctx, uint8_t *rsp, uint8_t rsp_len )
{   
    err_t err_flag = AMFM2_ERROR;
    if ( ( AMFM2_OK == amfm2_check_clear_to_send( ctx ) ) && (  0 != rsp_len ) )
    {
        err_flag = amfm2_generic_read( ctx, DUMMY, rsp, rsp_len );
    }
    return err_flag;
}

err_t amfm2_get_rev ( amfm2_t *ctx, amfm2_device_info_t *rev )
{
    uint8_t arg = DUMMY;
    uint8_t rsp[ 9 ] = { 0 };
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_GET_REV, &arg, 1, rsp, 9 );
    rev->pn = rsp[ 1 ];
    rev->fwmajor = rsp[ 2 ];
    rev->fwminor = rsp[ 3 ];
    rev->patch = ( ( ( uint16_t) rsp[ 4 ] ) << 8 ) | rsp[ 5 ];
    rev->cmpmajor = rsp[ 6 ];
    rev->cmpminor = rsp[ 7 ];
    rev->chiprev = rsp[ 8 ];
    return err_flag;
}

err_t amfm2_seek_station ( amfm2_t *ctx, uint8_t *rsp )
{
    uint8_t arg = AMFM2_FMSEEKSTART_ARG_SEEKUP | AMFM2_FMSEEKSTART_ARG_WRAP;
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_FM_SEEK_START, &arg, 1, rsp, 1 );
    err_flag |= amfm2_check_seek_tune_complete( ctx );
    return err_flag;
}

err_t amfm2_set_volume ( amfm2_t *ctx, uint8_t volume, uint8_t *rsp )
{
    err_t err_flag = AMFM2_ERROR;
    if ( ( volume >= AMFM2_SET_VOLUME_MUTE ) && ( volume <= AMFM2_SET_VOLUME_MAX ) )
    {
        uint8_t arg[ 5 ] = { DUMMY, AMFM2_PROP_RXVOLUME_H, AMFM2_PROP_RXVOLUME_L, DUMMY, volume };
        err_flag = amfm2_set_command( ctx, AMFM2_CMD_SET_PROPERTY, arg, 5, rsp, 1 );
        err_flag |= amfm2_check_clear_to_send( ctx );
    }
    return err_flag;
}

err_t amfm2_sound_off ( amfm2_t *ctx, uint8_t *rsp )
{ 
    uint8_t arg[ 5 ] = { DUMMY, 
                         AMFM2_PROP_RXHMUTE_H, 
                         AMFM2_PROP_RXHMUTE_L, 
                         DUMMY,
                         AMFM2_PROPVALL_LMUTE | AMFM2_PROPVALL_RMUTE };
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_SET_PROPERTY, arg, 5, rsp, 1 );
    err_flag |= amfm2_check_clear_to_send( ctx );
    return err_flag;
}

err_t amfm2_sound_on ( amfm2_t *ctx, uint8_t *rsp )
{
    uint8_t arg[ 5 ] = { DUMMY, AMFM2_PROP_RXHMUTE_H, AMFM2_PROP_RXHMUTE_L, DUMMY, DUMMY };
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_SET_PROPERTY, arg, 5, rsp, 1 );
    err_flag |= amfm2_check_clear_to_send( ctx );
    return err_flag; 
}

err_t amfm2_tuning_freq_up ( amfm2_t *ctx, uint8_t *rsp )
{
    uint8_t arg[ 4 ] = { 0 };
    uint8_t rsp_status = DUMMY;
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_FM_TUNE_STATUS, arg, 1, rsp, 7 );
    uint16_t aux_buf = ( ( uint16_t ) rsp[ 2 ] ) << 8;
    aux_buf |= rsp[ 3 ];
    aux_buf += 10;

    arg[ 0 ] = DUMMY;
    arg[ 1 ] = ( uint8_t )( aux_buf >> 8 );
    arg[ 2 ] = ( uint8_t ) aux_buf;
    arg[ 3 ] = DUMMY;
    err_flag |= amfm2_set_command( ctx, AMFM2_CMD_FM_TUNE_FREQ, arg, 4, &rsp_status, 1 );
    err_flag |= amfm2_check_seek_tune_complete( ctx );
    return err_flag;
}

err_t amfm2_tuning_freq_down ( amfm2_t *ctx, uint8_t *rsp )
{
    uint8_t arg[ 4 ] = { 0 };
    uint8_t rsp_status = DUMMY;
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_FM_TUNE_STATUS, arg, 1, rsp, 7 );
    uint16_t aux_buf = ( ( uint16_t ) rsp[ 2 ] ) << 8;
    aux_buf |= rsp[ 3 ];
    aux_buf -= 10;
    
    arg[ 0 ] = DUMMY;
    arg[ 1 ] = ( uint8_t )( aux_buf >> 8 );
    arg[ 2 ] = ( uint8_t ) aux_buf;
    arg[ 3 ] = DUMMY;
    err_flag |= amfm2_set_command( ctx, AMFM2_CMD_FM_TUNE_FREQ, arg, 4, &rsp_status, 1 );
    err_flag |= amfm2_check_seek_tune_complete( ctx );
    return err_flag;
}

err_t amfm2_tuning_freq ( amfm2_t *ctx, float frequency, uint8_t *rsp )
{
    uint16_t freq_tmp = frequency * 100;
    uint8_t arg[ 4 ] = { DUMMY, ( uint8_t ) ( freq_tmp >> 8 ), ( uint8_t ) ( freq_tmp ), DUMMY };
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_FM_TUNE_FREQ, arg, 4, rsp, 1 );
    err_flag |= amfm2_check_seek_tune_complete( ctx );
    return err_flag;
}

err_t amfm2_get_tuning_freq ( amfm2_t *ctx, float *frequency )
{
    uint8_t arg = DUMMY;
    uint8_t rsp[ 7 ] = { 0 };
    uint16_t freq_tmp = DUMMY;
    err_t err_flag = amfm2_set_command( ctx, AMFM2_CMD_FM_TUNE_STATUS, &arg, 1, rsp, 7 );
    freq_tmp = ( ( uint16_t ) rsp[ 2 ] ) << 8;
    freq_tmp |= rsp[ 3 ];
    *frequency = ( float ) freq_tmp / 100.0;
    return err_flag;
}

err_t amfm2_check_clear_to_send ( amfm2_t *ctx )
{
    uint16_t check_cnt = DUMMY;
    uint8_t status_rsp = DUMMY;
    err_t err_flag = AMFM2_OK;
    do
    {
        err_flag |= amfm2_generic_read( ctx, DUMMY, &status_rsp, 1 );
        check_cnt++;
        if ( AMFM2_TIMEOUT < check_cnt )
        {
            err_flag = AMFM2_ERROR;
            break;
        }
    } 
    while ( !( status_rsp & AMFM2_RSP_STATUS_CTS ) );
    return err_flag;
}

err_t amfm2_check_seek_tune_complete ( amfm2_t *ctx )
{
    uint16_t check_cnt = DUMMY;
    uint8_t status_rsp = DUMMY;
    err_t err_flag = amfm2_check_clear_to_send( ctx );
    do
    {
        err_flag |= amfm2_set_command( ctx, AMFM2_CMD_GET_INT_STATUS, DUMMY, DUMMY, &status_rsp, 1 );
        check_cnt++;
        if ( AMFM2_TIMEOUT < check_cnt )
        {
            err_flag = AMFM2_ERROR;
            break;
        }
    } 
    while ( !( status_rsp & AMFM2_RSP_STATUS_STCINT ) );
    return err_flag;
}

err_t amfm2_check_status_error ( amfm2_t *ctx )
{
    uint8_t status_rsp = DUMMY;
    err_t err_flag = amfm2_check_clear_to_send( ctx );
    err_flag |= amfm2_get_response( ctx, &status_rsp, 1 );
    if ( !( status_rsp & AMFM2_RSP_STATUS_ERROR ) )
    {
        err_flag = AMFM2_ERROR;
    }
    return err_flag;
}

err_t amfm2_check_rds_interrupt ( amfm2_t *ctx )
{
    uint16_t check_cnt = DUMMY;
    uint8_t status_rsp = DUMMY;
    err_t err_flag = amfm2_check_clear_to_send( ctx );
    do
    {
        err_flag |= amfm2_set_command( ctx, AMFM2_CMD_GET_INT_STATUS, DUMMY, DUMMY, &status_rsp, 1 );
        check_cnt++;
        if ( AMFM2_TIMEOUT < check_cnt )
        {
            err_flag = AMFM2_ERROR;
            break;
        }
    } 
    while ( !( status_rsp & AMFM2_RSP_STATUS_RDSINT ) );
    return err_flag;
}

// ------------------------------------------------------------------------- END

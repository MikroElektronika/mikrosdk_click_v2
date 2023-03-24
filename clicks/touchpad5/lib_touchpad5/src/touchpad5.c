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
 * @file touchpad5.c
 * @brief Touchpad 5 Click Driver.
 */

#include "touchpad5.h"

void touchpad5_cfg_setup( touchpad5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->nrst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TOUCHPAD5_SET_DEV_ADDR;
}

void touchpad5_reset( touchpad5_t *ctx )
{
    digital_out_low( &ctx->nrst );
    Delay_1sec( );
    digital_out_high( &ctx->nrst );
}

err_t touchpad5_init( touchpad5_t *ctx, touchpad5_cfg_t *cfg ) 
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

    if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->nrst, cfg->nrst ) )
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    }

    if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) )
    {
        return DIGITAL_IN_UNSUPPORTED_PIN;
    }

    touchpad5_reset( ctx );

    return I2C_MASTER_SUCCESS;
}

err_t touchpad5_default_cfg( touchpad5_t *ctx ) 
{
    err_t status = TOUCHPAD5_OK;
    touchpad5_channel_setup_t ch_setup;
    touchpad5_threshold_settings_t thresh_settings;
    touchpad5_control_settings_t ctrl_settings;
    uint8_t ack_reset_byte;
    
    ch_setup.total_rx = 10;
    ch_setup.total_tx = 13;
    ch_setup.track_pad_rx = 10;
    ch_setup.track_pad_tx = 13;
    ch_setup.pm_setup = TOUCHPAD5_CHARGE_MUTUAL_SELF_CHARG |
                        TOUCHPAD5_RX_GROUP_RXB |
                        TOUCHPAD5_SUM_OF_TP_TX;
                        
    ch_setup.tx_config = TOUCHPAD5_TX_HIGH_DFLT << 8 |
                         TOUCHPAD5_TX_LOW_DFLT;
    
    status |= touchpad5_channel_setup( ctx, ch_setup );
    
    Delay_1sec( );
    
    ack_reset_byte = TOUCHPAD5_ACK_RESET;
    status |= touchpad5_generic_write( ctx, TOUCHPAD5_CMD_CONTROL_SETTINGS, &ack_reset_byte, 1 );

    Delay_1sec( );

    thresh_settings.prox_thresh = 10;
    thresh_settings.touch_thresh_mult = 25;
    thresh_settings.touch_thresh_shift = 5;
    thresh_settings.pm_prox_thresh = 10;
    thresh_settings.snap_thresh_high = 0;
    thresh_settings.snap_thresh_low = 0;

    status |= touchpad5_threshold_setup( ctx, thresh_settings );
    
    Delay_1sec( );

    ctrl_settings.ctrl_settings0 = TOUCHPAD5_SINGLE_XY;
    ctrl_settings.ctrl_settings1 = TOUCHPAD5_SNAP_EN;
    
    status |= touchpad5_control_setup( ctx, ctrl_settings );
    
    Delay_1sec( );
        
    return status;
}

err_t touchpad5_generic_write( touchpad5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[0] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    touchpad5_wait_ready( ctx );
    return i2c_master_write( &ctx->i2c, &data_buf, tx_len + 1 );
}

err_t touchpad5_generic_read( touchpad5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    touchpad5_wait_ready( ctx );
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t touchpad5_check_interrupt( touchpad5_t *ctx ) 
{    
    return digital_in_read( &ctx->int_pin ); 
}

void touchpad5_wait_ready( touchpad5_t *ctx ) 
{
    // wait for communication window (RDY bit enable)
    while ( digital_in_read( &ctx->int_pin ) );
    while ( !digital_in_read( &ctx->int_pin ) );
}

err_t touchpad5_channel_setup( touchpad5_t *ctx, touchpad5_channel_setup_t ch_setup ) 
{
    err_t status = TOUCHPAD5_OK;
    uint8_t tx_buf[ 7 ];
    
    tx_buf[ 0 ] = ch_setup.total_rx;
    tx_buf[ 1 ] = ch_setup.total_tx;
    tx_buf[ 2 ] = ch_setup.track_pad_rx;
    tx_buf[ 3 ] = ch_setup.track_pad_tx;
    tx_buf[ 4 ] = ch_setup.pm_setup;
    tx_buf[ 5 ] = ( uint8_t ) ( ch_setup.tx_config >> 8 );
    tx_buf[ 6 ] = ( uint8_t ) ch_setup.tx_config;
    
    status |= touchpad5_generic_write( ctx, TOUCHPAD5_CMD_CHANNEL_SETUP, tx_buf, 7 );
    
    return status;
}

err_t touchpad5_threshold_setup( touchpad5_t *ctx, touchpad5_threshold_settings_t thresh_setup ) 
{
    err_t status = TOUCHPAD5_OK;
    uint8_t tx_buf[ 8 ];
        
    tx_buf[ 0 ] = thresh_setup.prox_thresh;
    tx_buf[ 1 ] = thresh_setup.touch_thresh_mult;
    tx_buf[ 2 ] = thresh_setup.touch_thresh_shift;
    tx_buf[ 3 ] = thresh_setup.pm_prox_thresh;
    tx_buf[ 4 ] = thresh_setup.snap_thresh_high;
    tx_buf[ 5 ] = thresh_setup.snap_thresh_low;
    
    status |= touchpad5_generic_write( ctx, TOUCHPAD5_CMD_THRESHOLD_SETTINGS, tx_buf, 6 );
    
    return status;
}


err_t touchpad5_control_setup( touchpad5_t *ctx, touchpad5_control_settings_t ctrl_setup ) 
{
    err_t status = TOUCHPAD5_OK;
    uint8_t tx_buf[ 2 ];
        
    tx_buf[ 0 ] = ctrl_setup.ctrl_settings0;
    tx_buf[ 1 ] = ctrl_setup.ctrl_settings1;

    status |= touchpad5_generic_write( ctx, TOUCHPAD5_CMD_CONTROL_SETTINGS, tx_buf, 2 );
    
    return status;
}


err_t touchpad5_check_version( touchpad5_t *ctx, touchpad5_ver_info_t *ver_info ) 
{
    err_t status = TOUCHPAD5_OK;
    uint8_t rx_buf[ 10 ];
    float ver;
    
    status |= touchpad5_generic_read( ctx, TOUCHPAD5_CMD_VERSION_INFO, rx_buf, 10 );
    
    ver_info->product_num = ( ( ( uint16_t )  rx_buf[ 0 ] ) << 8 ) | rx_buf[ 1 ];
    
    ver_info->project_num = ( ( ( uint16_t )  rx_buf[ 2 ] ) << 8 ) | rx_buf[ 3 ];
    
    ver = ( float ) rx_buf[ 4 ];
    
    if ( rx_buf[ 5 ] > 99 ) 
    {
        ver += ( float ) ( ( float ) rx_buf[ 5 ] / 1000 );    
    } 
    else if ( rx_buf[ 5 ] > 9 ) 
    {
        ver += ( float ) ( ( float  )rx_buf[ 5 ] / 100 );       
    } 
    else 
    {
        ver += ( float ) (( float ) rx_buf[ 5 ] / 10 );   
    }
    
    ver_info->version = ver;
    
    ver_info->hw_id = ( ( ( uint16_t )  rx_buf[ 6 ] ) << 8 ) | rx_buf[ 7 ];
    
    ver_info->hw_revision = ( ( ( uint16_t )  rx_buf[ 8 ] ) << 8 ) | rx_buf[ 9 ];
    
    return status;
}

err_t touchpad5_check_bl_status( touchpad5_t *ctx, uint8_t* rx_buf )
{
    return touchpad5_generic_read( ctx, TOUCHPAD5_CMD_BOOTLOADER, rx_buf, 1 );
}

err_t touchpad5_get_touch( touchpad5_t *ctx, touchpad5_touch_t *touch_data ) 
{
    err_t status = TOUCHPAD5_OK;
    uint8_t rx_buf[ 8 ];
    
    status |= touchpad5_generic_read( ctx, TOUCHPAD5_CMD_XY_DATA, rx_buf, 8 );

    touch_data->xy_info = rx_buf[ 0 ];
    touch_data->no_of_fingers = rx_buf[ 0 ] & TOUCHPAD5_NO_OF_FINGERS; 
    touch_data->id_tag = rx_buf[ 1 ];
    touch_data->x_pos = ( ( ( uint16_t )  rx_buf[ 2 ] ) << 8 ) | rx_buf[ 3 ];
    touch_data->y_pos = ( ( ( uint16_t )  rx_buf[ 4 ] ) << 8 ) | rx_buf[ 5 ];
    touch_data->touch_strength = ( ( ( uint16_t )  rx_buf[ 6 ] ) << 8 ) | rx_buf[ 7 ];
    
    return status;
}


err_t touchpad5_get_all_data( touchpad5_t *ctx, uint8_t *rx_data ) 
{
    return touchpad5_generic_read( ctx, TOUCHPAD5_CMD_XY_DATA, rx_data, 36 );
}

err_t touchpad5_get_status( touchpad5_t *ctx, uint8_t sel_status, uint16_t *rx_data, uint8_t num_of_samples ) 
{
    err_t status = TOUCHPAD5_OK;
    uint8_t rx_buf[ 30 ] = { 0 };
    
    if ( TOUCHPAD5_PROXIMITY_STATUS == sel_status ) 
    {
        status |= touchpad5_generic_read( ctx, TOUCHPAD5_CMD_PROXIMITY_STATUS, rx_buf, num_of_samples );
    } 
    else if ( TOUCHPAD5_TOUCH_STATUS == sel_status ) 
    {
        status |= touchpad5_generic_read( ctx, TOUCHPAD5_CMD_TOUCH_STATUS, rx_buf, num_of_samples );   
    } 
    else 
    {
        status |= touchpad5_generic_read( ctx, TOUCHPAD5_CMD_SNAP_STATUS, rx_buf, num_of_samples );       
    }
    
    for( int i = 0; i < 15; i++)
    {
        rx_data[ i ] = ( ( ( uint16_t )  rx_buf[ ( 2 * i ) + 1 ] ) << 8 ) | rx_buf[ 2 * i ];
    }

    return status;
}


// ------------------------------------------------------------------------- END

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
 * @file touchpad4.c
 * @brief Touchpad 4 Click Driver.
 */

#include "touchpad4.h"

void touchpad4_cfg_setup ( touchpad4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TOUCHPAD4_SET_DEV_ADDR;
}

err_t touchpad4_init ( touchpad4_t *ctx, touchpad4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->mclr, cfg->mclr );
    digital_in_init( &ctx->rdy, cfg->rdy );

    return I2C_MASTER_SUCCESS;
}

err_t touchpad4_default_cfg ( touchpad4_t *ctx ) 
{
    err_t error_flag = TOUCHPAD4_OK;
    uint16_t temp_data = 0;
    //Enable/disable Rx pins
    temp_data = 0x030F;
    error_flag = touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_SETUP, temp_data );
    //Enable/disable Tx pins
    temp_data = 0x07C0;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_TX_ENABLE, temp_data );
    //Total number of Rx pins
    error_flag |= touchpad4_generic_read( ctx, TOUCHPAD4_REG_TOTAL_RXS_TRACKPAD_SETTINGS, &temp_data );
    temp_data &= 0x00FF;
    temp_data |= 0x0400;//0x043B
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TOTAL_RXS_TRACKPAD_SETTINGS, temp_data );
    //Total number of Tx pins
    touchpad4_generic_read( ctx, TOUCHPAD4_REG_MAX_MULTITOUCHES_TOTAL_TXS, &temp_data );
    temp_data &= 0xFF00;
    temp_data |= 0x0005;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_MAX_MULTITOUCHES_TOTAL_TXS, temp_data );
    //Pin mapping
    temp_data = 0x0203;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_1_0, temp_data );
    temp_data = 0x0001;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_3_2, temp_data );
    temp_data = 0x090A;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_5_4, temp_data );
    temp_data = 0x0708;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_7_6, temp_data );
    temp_data = 0x0506;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_9_8, temp_data );
    //Channel configuration
    temp_data = 0x0005;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE0, temp_data );
    temp_data = 0x0501;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE0, temp_data );
    temp_data = 0x0302;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE1, temp_data );
    temp_data = 0x0405;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE2, temp_data );
    temp_data = 0x0505;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE2, temp_data );
    temp_data = 0x0706;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE3, temp_data );
    temp_data = 0x0805;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE4, temp_data );
    temp_data = 0x0509;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE4, temp_data );
    temp_data = 0x0B0A;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE5, temp_data );
    temp_data = 0x0C05;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE6, temp_data );
    temp_data = 0x050D;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE6, temp_data );
    temp_data = 0x0F0E;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE7, temp_data );
    temp_data = 0x1005;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE8, temp_data );
    temp_data = 0x0511;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE8, temp_data );
    temp_data = 0x1312;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE9, temp_data );  
    //Enable gestures
    temp_data = 0x003F;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_GESTURE_ENABLE, temp_data );
    //Disable timeoutes
    temp_data = 0;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ACTIVE_MODE_TIMEOUT, temp_data );
    temp_data = 0;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_IDLE_TOUCH_MODE_TIMEOUT, temp_data );
    temp_data = 0;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_IDLE_MODE_TIMEOUT, temp_data );
    temp_data = 0;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_LP1_MODE_TIMEOUT, temp_data );
    temp_data = 0;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_I2C_TIMEOUT, temp_data );
    //Set active state
    error_flag |= touchpad4_generic_read( ctx, TOUCHPAD4_REG_SYSTEM_CONTROL, &temp_data );
    temp_data &= 0xFFF8;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SYSTEM_CONTROL, temp_data );
    //Set to trigger rdy pin on touch detected
    temp_data = 0x4702;
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_CONFIG_SETTINGS, temp_data );
    
    return error_flag;
}

err_t touchpad4_generic_write ( touchpad4_t *ctx, uint8_t reg, uint16_t tx_data ) 
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;
    data_buf[ 2 ] = tx_data >> 8;
    
    if ( ctx->event_enabled )
    {
        while ( digital_in_read( &ctx->rdy ) );
        Delay_1ms( );
    }
    
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 3 );
    
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    
    return error_flag;
}

err_t touchpad4_generic_read ( touchpad4_t *ctx, uint8_t reg, uint16_t *rx_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    
    if ( ctx->event_enabled )
    {
        while ( digital_in_read( &ctx->rdy ) );
        Delay_1ms( );
    }

    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );

    *rx_data = ( ( uint16_t )data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    
    return error_flag;
}

uint8_t touchpad4_get_ready ( touchpad4_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

void touchpad4_reset ( touchpad4_t *ctx )
{
    uint16_t temp_data = 0;
    ctx->event_enabled = 0;
    touchpad4_generic_write( ctx, TOUCHPAD4_REG_GESTURES, temp_data );
    
    temp_data = 0x0200;
    touchpad4_generic_write( ctx, TOUCHPAD4_REG_SYSTEM_CONTROL, temp_data );
    do {
        touchpad4_generic_read( ctx, TOUCHPAD4_REG_INFO_FLAGS, &temp_data );
        temp_data &= 0x0080;
    } while( !temp_data );
    
    ctx->event_enabled = 1;
}

err_t touchpad4_get_touch ( touchpad4_t *ctx, touchpad4_info_t *touch_info )
{
    uint16_t temp_data = 0;
    
    touchpad4_generic_read( ctx, TOUCHPAD4_REG_INFO_FLAGS, &temp_data );
    touch_info->number_of_touches = ( temp_data >> 8 ) & 3;
    
    if ( touch_info->number_of_touches > 0 )
    {
        for ( uint8_t touch_index = 0; touch_index < touch_info->number_of_touches; touch_index++ )
        {
            uint16_t coords;
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_X + ( touch_index * 4 ), 
                                    &touch_info->touches[ touch_index ].x );
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_Y + ( touch_index * 4 ),
                                    &touch_info->touches[ touch_index ].y );
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_TOUCH_STR + ( touch_index * 4 ),
                                    &touch_info->touches[ touch_index ].strength );
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_AREA + ( touch_index * 4 ),
                                    &touch_info->touches[ touch_index ].area );
        }
    }    
    
    return TOUCHPAD4_OK;
}

err_t touchpad_get_channels ( touchpad4_t *ctx, uint32_t *channels )
{
    uint32_t ch_status = 0;
    uint16_t temp_data = 0;
    
    err_t error_flag = touchpad4_generic_read( ctx, TOUCHPAD4_REG_TOUCH_STATUS1, &temp_data );
    ch_status = temp_data;
    ch_status <<= 16;
    error_flag |= touchpad4_generic_read( ctx, TOUCHPAD4_REG_TOUCH_STATUS0, &temp_data );
    ch_status |= temp_data;
    
    *channels = ch_status;
    
    return error_flag;
}

// ------------------------------------------------------------------------- END

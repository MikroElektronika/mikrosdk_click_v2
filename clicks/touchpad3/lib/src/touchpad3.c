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
 * @file touchpad3.c
 * @brief Touchpad 3 Click Driver.
 */

#include "touchpad3.h"

/**
 * @brief HW reset delay of 100 milliseconds.
 */
static void dev_reset_delay ( void );

/**
 * @brief Write delay of 10 milliseconds.
 */
static void dev_write_delay ( void );

/**
 * @brief Write delay of 100 milliseconds.
 */
static void dev_config_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void touchpad3_cfg_setup ( touchpad3_cfg_t *cfg ) {
    
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TOUCHPAD3_SET_DEV_ADDR;
}

err_t touchpad3_init ( touchpad3_t *ctx, touchpad3_cfg_t *cfg ) {    
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    return I2C_MASTER_SUCCESS;
}

err_t touchpad3_default_cfg ( touchpad3_t *ctx ) {    
    touchpad3_hw_reset( ctx );
    dev_config_delay( );
    
    touchpad3_general_configuration( ctx );
    dev_config_delay( );
    
    touchpad3_decoding_configuration( ctx );
    dev_config_delay( );
    
    touchpad3_sensor_mapping_configuration( ctx );
    dev_config_delay( );
    return TOUCHPAD3_OK;
}

uint8_t touchpad3_get_int ( touchpad3_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void touchpad3_hw_reset ( touchpad3_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    
    while ( touchpad3_get_int( ctx ) != 0 ) {
        dev_reset_delay( );
    }
}

void touchpad3_generic_write ( touchpad3_t *ctx,  uint8_t *tx_buf, uint8_t tx_len ) {    
    i2c_master_write( &ctx->i2c, tx_buf, tx_len );
}

err_t touchpad3_generic_read ( touchpad3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {    
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void touchpad3_general_configuration ( touchpad3_t *ctx ) {    
    uint8_t rx_ch[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_GENERAL_INDEX_LOCATION, 
                           TOUCHPAD3_GENERAL_RX_CH_ADD, TOUCHPAD3_GENERAL_RX_CH };
 
    uint8_t tx_ch[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_GENERAL_INDEX_LOCATION, 
                           TOUCHPAD3_GENERAL_TX_CH_ADD, TOUCHPAD3_GENERAL_TX_CH };

    uint8_t rx_scaling_factor_L[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_GENERAL_INDEX_LOCATION, 
                                         TOUCHPAD3_GENERAL_RX_SC_L_ADD, TOUCHPAD3_GENERAL_RX_SC_L };
    uint8_t rx_scaling_factor_H[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_GENERAL_INDEX_LOCATION, 
                                         TOUCHPAD3_GENERAL_RX_SC_H_ADD, TOUCHPAD3_GENERAL_RX_SC_H };

    uint8_t tx_scaling_factor_L[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_GENERAL_INDEX_LOCATION,
                                         TOUCHPAD3_GENERAL_TX_SC_L_ADD, TOUCHPAD3_GENERAL_TX_SC_L };
    uint8_t tx_scaling_factor_H[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_GENERAL_INDEX_LOCATION,
                                         TOUCHPAD3_GENERAL_TX_SC_H_ADD, TOUCHPAD3_GENERAL_TX_SC_H };

    touchpad3_generic_write( ctx, rx_ch, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_ch, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, rx_scaling_factor_L, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, rx_scaling_factor_H, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_scaling_factor_L, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_scaling_factor_H, 6 );
}

void touchpad3_decoding_configuration ( touchpad3_t *ctx ) {    
    uint8_t flip_state[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_DECODING_INDEX_LOCATION, 
                                TOUCHPAD3_DEC_FLIP_STATE_ADD, TOUCHPAD3_DEC_FLIP_STATE };

    uint8_t num_avg[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_DECODING_INDEX_LOCATION, 
                             TOUCHPAD3_DEC_NUM_AVG_ADD, TOUCHPAD3_DEC_NUM_AVG };

    uint8_t min_distance[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_DECODING_INDEX_LOCATION, 
                                  TOUCHPAD3_DEC_MIN_TOUCH_DISTANCE_ADD, 
                                  TOUCHPAD3_DEC_MIN_TOUCH_DISTANCE };

    touchpad3_generic_write( ctx, flip_state, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, num_avg, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, min_distance, 6 );
}


void touchpad3_sensor_mapping_configuration ( touchpad3_t *ctx ) {
    uint8_t rx_ch_1[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_RX_MAP_INDEX_ADD, TOUCHPAD3_RX_CH1_ADD,
                             TOUCHPAD3_RX_CH1 };
    uint8_t rx_ch_2[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_RX_MAP_INDEX_ADD, TOUCHPAD3_RX_CH2_ADD, 
                             TOUCHPAD3_RX_CH2 };
    uint8_t rx_ch_3[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_RX_MAP_INDEX_ADD, TOUCHPAD3_RX_CH3_ADD,
                             TOUCHPAD3_RX_CH3 };
    uint8_t rx_ch_4[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_RX_MAP_INDEX_ADD, TOUCHPAD3_RX_CH4_ADD, 
                             TOUCHPAD3_RX_CH4 };
    uint8_t rx_ch_5[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_RX_MAP_INDEX_ADD, TOUCHPAD3_RX_CH5_ADD, 
                             TOUCHPAD3_RX_CH5 };

    uint8_t tx_ch_1[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_TX_MAP_INDEX_ADD, TOUCHPAD3_TX_CH1_ADD, 
                             TOUCHPAD3_TX_CH1 };
    uint8_t tx_ch_2[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_TX_MAP_INDEX_ADD, TOUCHPAD3_TX_CH2_ADD, 
                             TOUCHPAD3_TX_CH2 };
    uint8_t tx_ch_3[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_TX_MAP_INDEX_ADD, TOUCHPAD3_TX_CH3_ADD, 
                             TOUCHPAD3_TX_CH3 };
    uint8_t tx_ch_4[ 6 ] = { TOUCHPAD3_REG_WRITE, TOUCHPAD3_TX_MAP_INDEX_ADD, TOUCHPAD3_TX_CH4_ADD, 
                             TOUCHPAD3_TX_CH4 };

    touchpad3_generic_write( ctx, rx_ch_1, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, rx_ch_2, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, rx_ch_3, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, rx_ch_4, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, rx_ch_5, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_ch_1, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_ch_2, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_ch_3, 6 );
    dev_write_delay( );
    touchpad3_generic_write( ctx, tx_ch_4, 6 );
}

uint8_t touchpad3_get_touch ( touchpad3_t *ctx, touch_data_t *tch_data,uint16_t *x_axis, 
                              uint16_t *y_axis ) {    
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    uint16_t t_state;
    
    t_state = TOUCHPAD3_STATUS_ERROR;
    
    i2c_master_read( &ctx->i2c, rx_buf, 6 );

    if ( rx_buf[ 0 ] == TOUCHPAD3_LEN_TCH ) {
        t_state = TOUCHPAD3_STATUS_SUCCESS;
        
        tch_data->touch_id = ( rx_buf[ 1 ] >> 3 ) & TOUCHPAD3_T_AND_G_ID_BIT_MASK;
        tch_data->tch_state = ( rx_buf[ 1 ] >> 2 ) & TOUCHPAD3_TCH_STATE_BIT_MASK;
        tch_data->pen_state = rx_buf[ 1 ] & TOUCHPAD3_PEN_STATE_BIT_MASK;

        tmp = rx_buf[ 3 ] & TOUCHPAD3_5_BIT_MASK;
        tmp <<= 5;
        tmp |= rx_buf[ 2 ];

        *x_axis = tmp;

        tmp = rx_buf[ 5 ] & TOUCHPAD3_5_BIT_MASK;
        tmp <<= 5;
        tmp |= rx_buf[ 4 ];

        *y_axis = tmp;
    } else {
        tch_data->tch_state = TOUCHPAD3_STATE_GST;
    }
    return rx_buf[ 0 ];
}

uint8_t touchpad3_get_gesture ( touchpad3_t *ctx, touch_data_t *gst_data, uint8_t *gesture ) {    
    uint8_t rx_buf[ 3 ];
    uint16_t g_state;

    g_state = TOUCHPAD3_STATUS_ERROR;

    i2c_master_read( &ctx->i2c, rx_buf, 3 );
    
    if ( rx_buf[ 0 ] == TOUCHPAD3_LEN_GST ) {        
        g_state = TOUCHPAD3_STATUS_SUCCESS;
        
        gst_data->touch_id = ( rx_buf[ 1 ] >> 3 ) & TOUCHPAD3_T_AND_G_ID_BIT_MASK;
        gst_data->tch_state = ( rx_buf[ 1 ] >> 2 ) & TOUCHPAD3_TCH_STATE_BIT_MASK;
        gst_data->pen_state = rx_buf[ 1 ] & TOUCHPAD3_PEN_STATE_BIT_MASK;

        *gesture = rx_buf[ 2 ];
    } else {
        gst_data->tch_state = TOUCHPAD3_STATE_TCH;
    }
    return g_state;
}

uint8_t touchpad3_cmd_protocol ( touchpad3_t *ctx, cmd_protocol_t cmd_data, uint8_t *p_tx_data, 
                                 uint8_t *p_rx_data ) {    
    uint8_t n_cnt;
    uint8_t tx_buf[ 255 ];
    uint8_t tx_len;
    uint8_t rx_len;
    uint8_t respond;
    
    tx_len = cmd_data.n_tx_bytes;
    rx_len = cmd_data.n_rx_bytes;

    tx_buf[ 0 ] = TOUCHPAD3_SET_COMMAND;
    tx_buf[ 1 ] = cmd_data.n_tx_bytes;
    tx_buf[ 2 ] = cmd_data.cmd;

    for ( n_cnt = 0; n_cnt < tx_len - 1; n_cnt++ ) {
        tx_buf[ n_cnt + 3 ] = p_tx_data[ n_cnt ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, tx_len + 2 );

    while ( touchpad3_get_int( ctx ) != 1 );

    i2c_master_read( &ctx->i2c, p_rx_data, rx_len + 2 );
    
    respond = p_rx_data[ 3 ]; 
    return respond;
}

uint8_t touchpad3_write_reg ( touchpad3_t *ctx, uint8_t index_loc, uint8_t offset_loc, 
                              uint8_t tx_data, uint8_t *p_response ) {
    uint8_t cmd_status;
    uint8_t tx_buf[ 6 ];

    tx_buf[ 0 ] = TOUCHPAD3_SET_COMMAND;
    tx_buf[ 1 ] = 4;
    tx_buf[ 2 ] = TOUCHPAD3_CMD_WRITE_REGISTER;
    tx_buf[ 3 ] = index_loc;
    tx_buf[ 4 ] = offset_loc;
    tx_buf[ 5 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 6 );
    
    while ( touchpad3_get_int( ctx ) != 1 );

    i2c_master_write( &ctx->i2c, p_response, 5 );
    cmd_status = p_response[ 3 ];
    return cmd_status;
}

uint8_t touchpad3_read_reg ( touchpad3_t *ctx, uint8_t index_loc, uint8_t offset_loc, 
                             uint8_t *read_data, uint8_t *p_response ) {
    uint8_t cmd_status;
    uint8_t tx_buf[ 255 ];

    tx_buf[ 0 ] = TOUCHPAD3_SET_COMMAND;
    tx_buf[ 1 ] = 3;
    tx_buf[ 2 ] = TOUCHPAD3_CMD_READ_REGISTER;
    tx_buf[ 3 ] = index_loc;
    tx_buf[ 4 ] = offset_loc;

    i2c_master_write( &ctx->i2c, tx_buf, 5 );
    while ( touchpad3_get_int( ctx ) != 1 );

    i2c_master_read( &ctx->i2c, p_response, 6 );
    *read_data = p_response[ 5 ];
    
    cmd_status = p_response[ 3 ];
    return cmd_status;
}

uint8_t touchpad3_manufacturing_test ( touchpad3_t *ctx ) {
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 6 ];
    uint8_t manufacturing_test;

    tx_buf[ 0 ] = TOUCHPAD3_SET_COMMAND;
    tx_buf[ 1 ] = 1;
    tx_buf[ 2 ] = TOUCHPAD3_CMD_MANUFACTURING_TEST;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );
    while ( touchpad3_get_int( ctx ) != 1 );

    i2c_master_write( &ctx->i2c, rx_buf, 6 );
    manufacturing_test = rx_buf[ 5 ];
    return manufacturing_test;
}

uint32_t touchpad3_get_device_id ( touchpad3_t *ctx ) { 
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 9 ];
    uint32_t device_id;
    
    tx_buf[ 0 ] = TOUCHPAD3_SET_COMMAND;
    tx_buf[ 1 ] = 1;
    tx_buf[ 2 ] = TOUCHPAD3_CMD_DEVICE_ID;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );    
    while ( touchpad3_get_int( ctx ) != 1 );

    i2c_master_read( &ctx->i2c, rx_buf, 9 );
    device_id = rx_buf[ 5 ];
    device_id <<= 8;
    device_id |= rx_buf[ 6 ];
    device_id <<= 8;
    device_id |= rx_buf[ 7 ];
    device_id <<= 8;
    device_id |= rx_buf[ 8 ];
    return device_id;
}

uint8_t touchpad3_config_touch ( touchpad3_t *ctx, uint8_t en_touch ) {  
    uint8_t c_state;
    uint8_t touch_cgf_val;
    uint8_t response[ 5 ];
    
    if ( en_touch == TOUCHPAD3_TOUCH_GESTURE_ENABLE ) {   
        touch_cgf_val = TOUCHPAD3_CONFIG_TOUCH_GESTURE_PCK_ENABLE;
    } else {   
        touch_cgf_val = TOUCHPAD3_CONFIG_TOUCH_GESTURE_PCK_DISABLE;
    }
    
    c_state = touchpad3_write_reg( ctx, TOUCHPAD3_CONFIGURATION_INDEX_BYTE, 
                                        TOUCHPAD3_CONFIG_OFFSET_BYTE_TOUCH_PCK_CFG, 
                                        touch_cgf_val, &response[ 0 ] );
    return c_state;
}

uint8_t touchpad3_config_gesture ( touchpad3_t *ctx, uint8_t en_gesture ) {
    uint8_t c_state;
    uint8_t gesture_cgf_val;
    uint8_t response[ 5 ];

    if ( en_gesture == TOUCHPAD3_TOUCH_GESTURE_ENABLE ) {     
        gesture_cgf_val = TOUCHPAD3_CONFIG_TOUCH_GESTURE_PCK_ENABLE;
    } else { 
        gesture_cgf_val = TOUCHPAD3_CONFIG_TOUCH_GESTURE_PCK_DISABLE;
    }

    c_state = touchpad3_write_reg( ctx, TOUCHPAD3_CONFIGURATION_INDEX_BYTE, 
                                        TOUCHPAD3_CONFIG_OFFSET_BYTE_GESTURE_PCK_CFG,   
                                        gesture_cgf_val, &response[ 0 ] );
    return c_state;
}


// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_config_delay ( void ) {
    Delay_100ms( );
}

static void dev_reset_delay ( void ) {
    Delay_10ms( );
}

static void dev_write_delay ( void ) {    
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

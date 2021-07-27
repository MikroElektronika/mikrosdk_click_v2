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
 * @file bletx.c
 * @brief BLE TX Click Driver.
 */

#include "bletx.h"

#define BLETX_SLAVE_ADDR_SET_S0                              0x01
#define BLETX_SLAVE_ADDR_SET_S1                              0x02
#define BLETX_SLAVE_ADDR_BIT_MASK                            0x03
#define BLETX_STOP_ADVERTISING_BIT                           0x00
#define BLETX_START_ADVERTISING_BIT                          0x01
#define BLETX_TXDATA_BIT_MASK                                0x07
#define BLETX_EVENTNUM_BIT_MASK                              0x18

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void bletx_cfg_setup ( bletx_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->ui  = HAL_PIN_NC;
    cfg->s0  = HAL_PIN_NC;
    cfg->s1  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BLETX_SET_DEV_ADDR;
}

err_t bletx_init ( bletx_t *ctx, bletx_cfg_t *cfg ) {
    
    digital_out_init( &ctx->s0, cfg->s0 );
    digital_out_init( &ctx->s1, cfg->s1 );
    digital_out_init( &ctx->ui, cfg->ui );
    digital_out_init( &ctx->rst, cfg->rst );
    
    digital_out_low( &ctx->s0 );
    digital_out_low( &ctx->s1 );
    digital_out_low( &ctx->ui );
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    
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

    // It should contain the error status checking for every pin init.

    return I2C_MASTER_SUCCESS;
}

err_t bletx_default_cfg ( bletx_t *ctx ) {
    // Click default configuration.
    
    bletx_power_down( ctx );
    dev_reset_delay( );
    
    digital_out_low( &ctx->s0 );
    digital_out_low( &ctx->s1 );
    digital_out_low( &ctx->ui );
   
    bletx_hw_reset( ctx );
    
    return BLETX_OK;
}

err_t bletx_power_down ( bletx_t *ctx ) {   
    digital_out_low( &ctx->rst );
    
    return BLETX_OK;
}

err_t bletx_power_up ( bletx_t *ctx ) {   
    digital_out_high( &ctx->rst );
    
    return BLETX_OK;
}

err_t bletx_hw_reset ( bletx_t *ctx ) {   
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
    
    return BLETX_OK;
}

err_t bletx_soft_reset ( bletx_t *ctx ) {   
    uint8_t data_buf = BLETX_SOFT_RESET_CMD;
    
    return bletx_generic_write( ctx, BLETX_REG_SOFT_RESET, &data_buf, 1 );
}

err_t bletx_interface_selection ( bletx_t *ctx, uint8_t sel_interface ) {   
    if ( sel_interface == BLETX_SEL_INTERFACE_I2C ) { 
        digital_out_low( &ctx->ui );    
    } else if ( sel_interface == BLETX_SEL_INTERFACE_UART ) { 
        digital_out_high( &ctx->ui );      
    } else {
        return BLETX_ERROR;
    }
    
    return BLETX_OK;
}

err_t bletx_slave_address_selection ( bletx_t *ctx, uint8_t sel_slave_address ) {   
    sel_slave_address &= BLETX_SLAVE_ADDR_BIT_MASK;
    
    digital_out_write( &ctx->s1, ( sel_slave_address & BLETX_SLAVE_ADDR_SET_S1 ) >> 1 );
    digital_out_write( &ctx->s0, sel_slave_address & BLETX_SLAVE_ADDR_SET_S0 );
    
    ctx->slave_address = BLETX_SET_DEV_ADDR | sel_slave_address;
    return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
}

err_t bletx_baud_rate_selection ( bletx_t *ctx, uint32_t sel_baud_rate ) {   
    if ( sel_baud_rate == BLETX_SEL_BAUD_RATE_9600 ) { 
        digital_out_low( &ctx->s0 );
    } else if ( sel_baud_rate == BLETX_SEL_BAUD_RATE_115200 ) { 
        digital_out_high( &ctx->s0 );      
    } else {
        return BLETX_ERROR;
    }
    
    return BLETX_OK;
}

err_t bletx_generic_write ( bletx_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t bletx_generic_read ( bletx_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t bletx_start_advertising ( bletx_t *ctx ) {   
    uint8_t data_buf;
    data_buf = BLETX_START_ADVERTISING_BIT;

    return bletx_generic_write( ctx, BLETX_REG_MODE, &data_buf, 1 );
}

err_t bletx_stop_advertising ( bletx_t *ctx ) {   
    uint8_t data_buf;
    data_buf = BLETX_STOP_ADVERTISING_BIT;

    return bletx_generic_write( ctx, BLETX_REG_MODE, &data_buf, 1 );
}

err_t bletx_set_cfg_adv_channel ( bletx_t *ctx, bletx_advch_value_t advch_data ) {   
    uint8_t data_buf;
    data_buf = advch_data;

    return bletx_generic_write( ctx, BLETX_REG_SETTING_1, &data_buf, 1 );
}

err_t bletx_set_output_power ( bletx_t *ctx, bletx_tx_output_power_value_t power_data ) {   
    uint8_t data_buf;
    data_buf = power_data;

    return bletx_generic_write( ctx, BLETX_REG_SETTING_2, &data_buf, 1 );
}

err_t bletx_set_tx_data ( bletx_t *ctx, bletx_txdata_value_t txdata_data ) {   
    uint8_t data_buf;
    
    bletx_generic_read ( ctx, BLETX_REG_SETTING_3, &data_buf, 1 );
    
    data_buf &= BLETX_TXDATA_BIT_MASK;
    data_buf |= txdata_data;

    return bletx_generic_write( ctx, BLETX_REG_SETTING_3, &data_buf, 1 );
}

err_t bletx_set_eventnum ( bletx_t *ctx, bletx_eventnum_value_t eventnum_data ) {   
    uint8_t data_buf;
    
    bletx_generic_read ( ctx, BLETX_REG_SETTING_3, &data_buf, 1 );
    
    data_buf &= BLETX_EVENTNUM_BIT_MASK;
    data_buf |= eventnum_data;

    return bletx_generic_write( ctx, BLETX_REG_SETTING_3, &data_buf, 1 );
}

err_t bletx_set_adv_delay ( bletx_t *ctx, float adv_delay_ms ) {   
    uint8_t tx_buf[ 2 ];
    uint16_t tmp;
    
    if ( ( adv_delay_ms < 20 ) || ( adv_delay_ms > 10240 ) ) {
        return BLETX_ERROR;    
    }
    
    adv_delay_ms -= 20.000;
    adv_delay_ms /= 0.625;
    tmp = ( uint16_t ) adv_delay_ms;
    tmp += 0x0020;
    tmp &= 0x7FFF;
    
    tx_buf[ 0 ] = BLETX_ADV_DELAY_ENABLE;
    tx_buf[ 0 ] |= ( uint8_t ) ( tmp >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) tmp;

    return bletx_generic_write( ctx, BLETX_REG_SETTING_4, tx_buf, 2 );
}

err_t bletx_set_configuration ( bletx_t *ctx, bletx_adv_cfg_t adv_cfg ) {
    uint8_t data_buf[ 20 ];
    
    data_buf[ 0 ] = adv_cfg.adv_ch_1_frequency;
    data_buf[ 0 ] |= adv_cfg.adv_ch_2_frequency;
    data_buf[ 0 ] |= adv_cfg.adv_ch_3_frequency;
    
    data_buf[ 1 ] = adv_cfg.tx_output_power;
    
    data_buf[ 2 ] = adv_cfg.txdata_loop;
    data_buf[ 2 ] |= adv_cfg.txdata_cw;
    data_buf[ 2 ] |= adv_cfg.eventnum;
    
    data_buf[ 3 ] = adv_cfg.advdelay_enb;
    data_buf[ 3 ] |= ( uint8_t ) ( ( adv_cfg.avdintvl_interval_ms >> 8 ) & 0x7F );
    data_buf[ 4 ] = ( uint8_t ) adv_cfg.avdintvl_interval_ms;
    
    data_buf[ 5 ] = adv_cfg.crc_enb;
    data_buf[ 5 ] |= adv_cfg.white_enb;
    data_buf[ 5 ] |= adv_cfg.pdu_len;
    
    err_t error_flag = bletx_generic_write( ctx, BLETX_REG_SETTING_1, data_buf, 6 );
    
    data_buf[ 0 ] = BLETX_PREAMBLE;
    
    data_buf[ 1 ] = ( uint8_t ) ( BLETX_ACCESS_ADDRESS >> 24 );
    data_buf[ 2 ] = ( uint8_t ) ( BLETX_ACCESS_ADDRESS >> 16 );
    data_buf[ 3 ] = ( uint8_t ) ( BLETX_ACCESS_ADDRESS >> 8 );
    data_buf[ 4 ] = ( uint8_t ) BLETX_ACCESS_ADDRESS;   
    
    data_buf[ 5 ] = 2;
    data_buf[ 6 ] = BLETX_AD_TYPE_FLAGS_INDOOR_POSITIONING;
    
    data_buf[ 7 ]  = adv_cfg.uuid[ 5 ];
    data_buf[ 8 ]  = adv_cfg.uuid[ 4 ];
    data_buf[ 9 ]  = adv_cfg.uuid[ 3 ];
    data_buf[ 10 ] = adv_cfg.uuid[ 2 ];
    data_buf[ 11 ] = adv_cfg.uuid[ 1 ];
    data_buf[ 12 ] = adv_cfg.uuid[ 0 ];
    
    data_buf[ 13 ] = 2;
    data_buf[ 14 ] = BLETX_AD_TYPE_FLAGS;
    data_buf[ 15 ] = BLETX_HEADER_PDU_TYPE_ADV_SCAN_IND;
    error_flag |= bletx_generic_write( ctx, BLETX_REG_PREAMBLE, data_buf, 16 );
    
    return error_flag;
}

err_t bletx_create_adv_data_packet ( bletx_t *ctx, bletx_bletx_create_adv_data_packet_t adv_data_packet ) {
    uint8_t data_buf[ 32 ];
    
    err_t error_flag = bletx_generic_write( ctx, 0x07, &adv_data_packet.preamble, 1 );
    
    data_buf[ 0 ] = ( uint8_t ) ( adv_data_packet.access_address >> 24 ); 
    data_buf[ 1 ] = ( uint8_t ) ( adv_data_packet.access_address >> 16 );
    data_buf[ 2 ] = ( uint8_t ) ( adv_data_packet.access_address >> 8 );
    data_buf[ 3 ] = ( uint8_t ) adv_data_packet.access_address;
    error_flag = bletx_generic_write( ctx, BLETX_REG_PREAMBLE, data_buf, 4 );
    
    data_buf[ 0 ] = ( uint8_t ) ( adv_data_packet.pdu_header >> 8 );
    data_buf[ 1 ] = ( uint8_t ) adv_data_packet.pdu_header;
    error_flag |= bletx_generic_write( ctx, BLETX_REG_PDU_HEADER_0, data_buf, 2 );
    
    for ( uint8_t n_cnt = 0; n_cnt < 6; n_cnt++ ) {
        data_buf[ n_cnt ] = adv_data_packet.adv_addr[ n_cnt ];     
    }
    error_flag |= bletx_generic_write( ctx, BLETX_REG_PDU_ADV_ADDR_0, data_buf, 6 );
    
    for ( uint8_t n_cnt = 0; n_cnt < 32; n_cnt++ ) {
        data_buf[ n_cnt ] = adv_data_packet.adv_data[ n_cnt ];     
    }
    error_flag |= bletx_generic_write( ctx, BLETX_REG_PDU_ADV_DATA_START, data_buf, 32 );
    
    data_buf[ 0 ] = ( uint8_t ) ( adv_data_packet.crc >> 16 );
    data_buf[ 1 ] = ( uint8_t ) ( adv_data_packet.crc >> 8 );
    data_buf[ 2 ] = ( uint8_t ) adv_data_packet.crc;
    error_flag |= bletx_generic_write( ctx, BLETX_REG_CRC_0, data_buf, 3 );
    
    return error_flag;
}

err_t bletx_create_eddystone_uri ( bletx_t *ctx, bletx_eddystone_data_t adv_data ) {
    uint8_t data_url[ 9 ] = { 0x65, 0x75, 0x10, 0x00, 0x01 , 0x64, 0x43, 0x48, 0x24 };
    uint8_t data_buf[ 20 ];
    uint8_t len;
    uint8_t reg_tmp;
    
    len = adv_data.length_of_service_data; 
    
    if ( len > 0x0F ) {
        return BLETX_ERROR;    
    }
    
    data_buf[ 0 ] = adv_data.length_of_service_list;
    data_buf[ 1 ] = adv_data.param_service_list;
    data_buf[ 2 ] = ( uint8_t ) ( adv_data.eddystone_id >> 8 );
    data_buf[ 3 ] = ( uint8_t ) adv_data.eddystone_id;
    data_buf[ 4 ] = adv_data.length_of_service_data;
    data_buf[ 5 ] = adv_data.service_data;
    data_buf[ 6 ] = ( uint8_t ) ( adv_data.eddystone_id >> 8 );
    data_buf[ 7 ] = ( uint8_t ) adv_data.eddystone_id;
    data_buf[ 8 ] = adv_data.frame_type_url;
    data_buf[ 9 ] = adv_data.power;
    data_buf[ 10 ] = adv_data.spec_data;
    
    for ( uint8_t n_cnt = 0; n_cnt < len - 7; n_cnt++ ) {
        data_buf[ 11 + n_cnt ] = adv_data.advdata_url[ n_cnt ];   
    }
    
    data_buf[ len + 4 ] = adv_data.domain;
    err_t error_flag = bletx_generic_write( ctx, BLETX_REG_PDU_ADV_EDDYSTONE_DATA, data_buf, len + 5 );
    
    reg_tmp = BLETX_REG_PDU_ADV_EDDYSTONE_DATA;
    reg_tmp += len;
    reg_tmp += 5;
    error_flag |= bletx_generic_write( ctx, reg_tmp, data_url, 9 );
    
    return error_flag;
}

err_t bletx_create_eddystone_uid ( bletx_t *ctx, bletx_eddystone_data_t adv_data ) {
    uint8_t data_buf[ 27 ];
    
    data_buf[ 0 ] = adv_data.length_of_service_list;
    data_buf[ 1 ] = adv_data.param_service_list;
    data_buf[ 2 ] = ( uint8_t ) ( adv_data.eddystone_id >> 8 );
    data_buf[ 3 ] = ( uint8_t ) adv_data.eddystone_id;
    data_buf[ 4 ] = adv_data.length_of_service_data;
    data_buf[ 5 ] = adv_data.service_data;
    data_buf[ 6 ] = ( uint8_t ) ( adv_data.eddystone_id >> 8 );
    data_buf[ 7 ] = ( uint8_t ) adv_data.eddystone_id;
    data_buf[ 8 ] = adv_data.frame_type_url;
    data_buf[ 9 ] = adv_data.power;
    
    for ( uint8_t n_cnt = 0; n_cnt < 10; n_cnt++ ) {
        data_buf[ n_cnt + 10 ] = adv_data.name_space_id[ n_cnt ]; 
    }
    
    for ( uint8_t n_cnt = 0; n_cnt < 6; n_cnt++ ) {
        data_buf[ n_cnt + 20 ] = adv_data.instance_id[ n_cnt ]; 
    }
    
    err_t error_flag = bletx_generic_write( ctx, BLETX_REG_PDU_ADV_EDDYSTONE_DATA, data_buf, 27 );
    
    return error_flag;
}

err_t bletx_create_eddystone_tlm ( bletx_t *ctx, bletx_eddystone_data_t adv_data ) {
    uint8_t data_buf[ 27 ];
    uint16_t tmp;
         
    data_buf[ 0 ] = adv_data.length_of_service_list;
    data_buf[ 1 ] = adv_data.param_service_list;
    data_buf[ 2 ] = ( uint8_t ) ( adv_data.eddystone_id >> 8 );
    data_buf[ 3 ] = ( uint8_t ) adv_data.eddystone_id;
    data_buf[ 4 ] = adv_data.length_of_service_data;
    data_buf[ 5 ] = adv_data.service_data;
    data_buf[ 6 ] = ( uint8_t ) ( adv_data.eddystone_id >> 8 );
    data_buf[ 7 ] = ( uint8_t ) adv_data.eddystone_id;
    data_buf[ 8 ] = adv_data.frame_type_url;
    data_buf[ 9 ] = adv_data.tlm_version;
    
    data_buf[ 10 ] = ( uint8_t ) ( adv_data.battery_voltage >> 8 );
    data_buf[ 11 ] = ( uint8_t ) adv_data.battery_voltage;
    
    tmp = ( uint16_t ) ( adv_data.beacon_temperature * 256 );
    
    data_buf[ 12 ] = ( uint8_t ) adv_data.beacon_temperature; 
    data_buf[ 13 ] =  ( uint8_t ) ( tmp % 256 );
    
    data_buf[ 14 ] = ( uint8_t ) ( adv_data.pdu_count >> 24 ); 
    data_buf[ 15 ] = ( uint8_t ) ( adv_data.pdu_count >> 16 );
    data_buf[ 16 ] = ( uint8_t ) ( adv_data.pdu_count >> 8 );
    data_buf[ 17 ] = ( uint8_t ) adv_data.pdu_count;

    data_buf[ 18 ] = ( uint8_t ) ( adv_data.time_since_reboot >> 24 );
    data_buf[ 19 ] = ( uint8_t ) ( adv_data.time_since_reboot >> 16 );
    data_buf[ 20 ] = ( uint8_t ) ( adv_data.time_since_reboot >> 8 );
    data_buf[ 21 ] = ( uint8_t ) adv_data.time_since_reboot;
    
    err_t error_flag = bletx_generic_write( ctx, BLETX_REG_PDU_ADV_EDDYSTONE_DATA, data_buf, 22 );
    
    
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

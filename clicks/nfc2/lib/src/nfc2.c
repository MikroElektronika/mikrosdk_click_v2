/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file nfc2.c
 * @brief NFC 2 Click Driver.
 */

#include "nfc2.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief NFC 2 communication delay.
 * @details Communication delay of 1 ms.
 */
static void communication_delay ( void );

/**
 * @brief NFC 2 config delay.
 * @details Config delay of 100 ms.
 */
static void config_delay ( void );

/**
 * @brief NFC 2 reset delay.
 * @details Reset delay of 10 ms.
 */
static void reset_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void nfc2_cfg_setup ( nfc2_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NFC2_I2C_ADDR_0;
}

err_t nfc2_init ( nfc2_t *ctx, nfc2_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

void nfc2_default_cfg ( nfc2_t *ctx, control_packet_t *ctrl_pck ) {
    nfc2_cmd_core_reset( ctx );
    config_delay( );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    config_delay( );
    nfc2_cmd_core_init( ctx );
    config_delay( );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    config_delay( );
    nfc2_core_reset( ctx );
    config_delay( );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    config_delay( );
    nfc2_init_core( ctx );
    config_delay( );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    config_delay( );

    config_delay( );
    nfc2_core_set_default_config( ctx );
    config_delay( );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    config_delay( );
    nfc2_core_set_protocol_config( ctx );
    config_delay( );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    config_delay( );
}

err_t nfc2_generic_write ( nfc2_t *ctx, uint8_t *p_tx_data, uint8_t n_bytes ) {
    uint8_t tx_buf[ 255 ];

    for ( uint8_t cnt = 0; cnt <= n_bytes; cnt++ ) {
        tx_buf[ cnt ] = p_tx_data[ cnt ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, n_bytes );
}

err_t nfc2_generic_read ( nfc2_t *ctx, uint8_t *p_rx_h_data, uint8_t *p_rx_p_data ) {
    i2c_master_read( &ctx->i2c, p_rx_h_data, 3 );

    communication_delay( );

    i2c_master_read( &ctx->i2c, p_rx_p_data, p_rx_h_data[ 2 ] );
    return NFC2_OK;
}

void nfc2_hw_reset( nfc2_t *ctx ) {
    digital_out_high( &ctx->rst );
    reset_delay( );

    digital_out_low( &ctx->rst );
    reset_delay( );

    digital_out_high( &ctx->rst );
    reset_delay( );
}

uint8_t nfc2_get_data ( nfc2_t *ctx, uint8_t *p_rx_data ) {
    uint8_t rx_buf[ 3 ];
    uint8_t n_bytes;

    i2c_master_read( &ctx->i2c, rx_buf, 3 );

    n_bytes = rx_buf[ 2 ];
    communication_delay( );

    i2c_master_read( &ctx->i2c, p_rx_data, n_bytes );

    return n_bytes;
}

void nfc2_read_ctrl_packet_data ( nfc2_t *ctx, control_packet_t *ctrl_pck ) {
    uint8_t rx_buf[ 3 ];

    nfc2_generic_read( ctx, rx_buf, ctrl_pck->payload );

    ctrl_pck->message_type   = ( rx_buf[ 0 ] & 0xE0 ) >> 5;
    ctrl_pck->pck_bound_flag = ( rx_buf[ 0 ] & 0x10 ) >> 4;
    ctrl_pck->group_ident = rx_buf[ 0 ] & 0x0F;
    ctrl_pck->opcode_ident   = rx_buf[ 1 ] & 0x3F;
    ctrl_pck->payload_length   = rx_buf[ 2 ];
}

void nfc2_write_ctrl_packet_data ( nfc2_t *ctx, control_packet_t ctrl_pck ) {
    uint8_t tx_buf[ 3 ];
    uint8_t n_cnt;
    uint8_t n_bytes;

    tx_buf[ 0 ] = ctrl_pck.message_type << 5;
    tx_buf[ 0 ] |= ctrl_pck.pck_bound_flag << 4;
    tx_buf[ 0 ] |= ctrl_pck.group_ident;
    tx_buf[ 1 ] = ctrl_pck.opcode_ident;
    tx_buf[ 2 ] = ctrl_pck.payload_length;

    n_bytes = tx_buf[ 2 ];

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
        tx_buf[ n_cnt + 3 ] = ctrl_pck.payload[ n_cnt ];
    }

    nfc2_generic_write( ctx, tx_buf, n_bytes + 3 );
}

uint8_t nfc2_check_irq ( nfc2_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void nfc2_cmd_core_reset ( nfc2_t *ctx ) {
    uint8_t core_reset_cmd[ 4 ] = { 0x20, 0x00, 0x01, 0x01 };

    nfc2_generic_write( ctx, core_reset_cmd, 4 );
}

void nfc2_cmd_core_init ( nfc2_t *ctx ) {
    uint8_t core_init_cmd[ 3 ] = { 0x20, 0x01, 0x00 };

    nfc2_generic_write( ctx, core_init_cmd, 3 );
}

void nfc2_cmd_disable_standby_mode ( nfc2_t *ctx ) {
    uint8_t disable_standby_mode_cmd[ 4 ] = { 0x2F, 0x00, 0x01, 0x00 };

    nfc2_generic_write( ctx, disable_standby_mode_cmd, 4 );
}

void nfc2_cmd_antenna_test ( nfc2_t *ctx, uint8_t sel_ant ) {
    uint8_t test_antenna_cmd[ 8 ] = { 0x2F, 0x3D, 0x05, 0x20, 0x00, 0x00, 0x00, 0x00 };
    uint8_t n_cnt;

    test_antenna_cmd[ 4 ] = sel_ant & 0x01;
    test_antenna_cmd[ 5 ] = ( sel_ant & 0x02 ) >> 1;
    test_antenna_cmd[ 6 ] = ( sel_ant & 0x04 ) >> 2;
    test_antenna_cmd[ 7 ] = ( sel_ant & 0x08 ) >> 3;

    nfc2_generic_write( ctx, test_antenna_cmd, 8 );
}

void nfc2_cmd_test_procedure ( nfc2_t *ctx ) {
    uint8_t test_procedure_cmd[ 7 ] = { 0x2F, 0x30, 0x04, 0x00, 0x00, 0x00, 0x1F };

    nfc2_generic_write( ctx, test_procedure_cmd, 7 );
}

void nfc2_core_reset ( nfc2_t *ctx ) {
    uint8_t init_core_cmd[ 25 ] = { 0x21, 0x00, 0x16, 0x07, 0x04, 0x02, 0x02, 0x05, 0x03, 0x03,
                                    0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x03, 0x01, 0x01, 0x04,
                                    0x01, 0x02, 0x80, 0x01, 0x80 };

    nfc2_generic_write( ctx, init_core_cmd, 25 );
}

void nfc2_init_core ( nfc2_t *ctx ) {
    uint8_t init_core_cmd[ 15 ] = { 0x21, 0x01, 0x0C, 0x00, 0x02, 0x01, 0x03, 0x00, 0x01, 0x04,
                                    0x01, 0x03, 0x00, 0x01, 0x05 };

    nfc2_generic_write( ctx, init_core_cmd, 15 );
}

void nfc2_core_set_default_config ( nfc2_t *ctx ) {
    uint8_t init_core_cmd[ 7 ] = { 0x20, 0x02, 0x04, 0x01, 0x32, 0x01, 0x60 };

    nfc2_generic_write( ctx, init_core_cmd, 7 );
}

void nfc2_core_set_protocol_config ( nfc2_t *ctx ) {
    uint8_t init_core_cmd[ 34 ] = { 0x20, 0x02, 0x1F, 0x02, 0x29, 0x0D, 0x46, 0x66, 0x6D, 0x01,
                                    0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA, 0x61,
                                    0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00,
                                    0x01, 0x04, 0x01, 0xFA };

    nfc2_generic_write( ctx, init_core_cmd, 34 );
}

void nfc2_cmd_start_discovery ( nfc2_t *ctx ) {
    uint8_t start_discovery_cmd[ 20 ] = { 0x21, 0x03, 0x11, 0x08, 0x00, 0x01, 0x01, 0x01, 0x02,
                                          0x01, 0x05, 0x01, 0x80, 0x01, 0x82,  0x01, 0x83, 0x01,
                                          0x85, 0x01 };

    nfc2_generic_write( ctx, start_discovery_cmd, 20 );
}

void nfc2_activate_rmt_mifare_card ( nfc2_t *ctx ) {
    uint8_t activate_rmt_mifare_card_cmd[ 12 ] = { 0x00, 0x00, 0x09, 0x40, 0x01, 0x10, 0xFF, 0xFF,
                                                   0xFF, 0xFF, 0xFF, 0xFF };

    nfc2_generic_write( ctx, activate_rmt_mifare_card_cmd, 12 );
}

void nfc2_cmd_authenticate_sector ( nfc2_t *ctx, uint8_t sel_sect_addr ) {
    uint8_t authenticate_sector_cmd[ 6 ] = { 0x00, 0x00, 0x03, 0x10, 0x30, 0x04 };

    authenticate_sector_cmd[ 4 ] = sel_sect_addr;

    nfc2_generic_write( ctx, authenticate_sector_cmd, 6 );
}

void nfc2_cmd_card_disconnected ( nfc2_t *ctx ) {
    uint8_t start_discovery_cmd[ 4 ] = { 0x21, 0x06, 0x01, 0x03 };

    nfc2_generic_write( ctx, start_discovery_cmd, 4 );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void communication_delay ( void ) {
    Delay_1ms( );
}

static void config_delay ( void ) {
    Delay_100ms( );
}

static void reset_delay ( void ) {
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

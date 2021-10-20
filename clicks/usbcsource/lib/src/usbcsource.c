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
 * @file usbcsource.c
 * @brief USB-C Source Click Driver.
 */

#include "usbcsource.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Device reset delay function.
**/
static void dev_device_reset_delay ( void );

/**
 * @brief Device config delay function.
**/
static void dev_device_config_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void usbcsource_cfg_setup ( usbcsource_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCSOURCE_I2C_SLAVE_ADR_GND;
}

err_t usbcsource_init ( usbcsource_t *ctx, usbcsource_cfg_t *cfg ) {
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

err_t usbcsource_generic_write ( usbcsource_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t usbcsource_generic_read ( usbcsource_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void usbcsource_write_byte ( usbcsource_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t usbcsource_read_byte ( usbcsource_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void usbcsource_hw_reset ( usbcsource_t *ctx ) {
    digital_out_high( &ctx->rst );
    dev_device_reset_delay( );
    digital_out_low( &ctx->rst );
    dev_device_reset_delay( );
}

uint8_t usbcsource_int_pin_state ( usbcsource_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void usbcsource_get_alert_status ( usbcsource_t *ctx, alert_status_t *alert_status_data ) {
    uint8_t rx_data;

    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_ALERT_STATUS_REG );

    alert_status_data->hard_reset_al               = ( rx_data >> 7 ) & 0x01;
    alert_status_data->port_status_al              = ( rx_data >> 6 ) & 0x01;
    alert_status_data->typec_monitoring_status_al  = ( rx_data >> 5 ) & 0x01;
    alert_status_data->cc_hw_fault_status_al       = ( rx_data >> 4 ) & 0x01;
    alert_status_data->prt_status_al               = ( rx_data >> 1 ) & 0x01;
    alert_status_data->phy_status_al               = rx_data & 0x01;
}

void usbcsource_set_alert_status ( usbcsource_t *ctx, alert_status_t alert_status_data ) {
    uint8_t tx_data;

    tx_data  = alert_status_data.hard_reset_al              << 7;
    tx_data |= alert_status_data.port_status_al             << 6;
    tx_data |= alert_status_data.typec_monitoring_status_al << 5;
    tx_data |= alert_status_data.cc_hw_fault_status_al      << 4;
    tx_data |= alert_status_data.prt_status_al              << 1;
    tx_data |= alert_status_data.phy_status_al;

    usbcsource_write_byte( ctx, USBCSOURCE_REG_ALERT_STATUS_MASK_CTRL, tx_data );
}

uint8_t usbcsource_check_attach_trans ( usbcsource_t *ctx ) {
    uint8_t rx_data;

    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_CC_CONNECTION_STATUS_TRANS );

    rx_data &= 0x01;
    
    return rx_data;
}

void usbcsource_get_port_status ( usbcsource_t *ctx, port_status_t *port_status_data ) {
    uint8_t rx_data;

    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_CC_CONNECTION_STATUS_1 );

    port_status_data->attached_device   = ( rx_data >> 5 ) & 0x07;
    port_status_data->low_power_standby = ( rx_data >> 4 ) & 0x01;
    port_status_data->power_mode        = ( rx_data >> 3 ) & 0x01;
    port_status_data->data_mode         = ( rx_data >> 2 ) & 0x01;
    port_status_data->vconn_mode        = ( rx_data >> 1 ) & 0x01;
    port_status_data->attach            = rx_data & 0x01;
}

void usbcsource_get_monitoring_status ( usbcsource_t *ctx, monitor_status_t *monitor_status_data ) {
    uint8_t rx_data;

    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_MONITORING_STATUS_TRANS );

    monitor_status_data->pd_typec_hand_check = ( rx_data >> 4 ) & 0x0F;
    
    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_MONITORING_STATUS );
    
    monitor_status_data->vbus_ready          = ( rx_data >> 3 ) & 0x01;
    monitor_status_data->vbus_vsafe0v        = ( rx_data >> 2 ) & 0x01;
    monitor_status_data->vbus_valid          = ( rx_data >> 1 ) & 0x01;
    monitor_status_data->vconn_valid         = rx_data & 0x01;
}

void usbcsource_get_connection_status ( usbcsource_t *ctx, connection_status_t *conn_data ) {
    uint8_t rx_data;

    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_CC_CONNECTION_STATUS_2 );

    conn_data->cc_reverse = ( rx_data >> 7 ) & 0x01;
    conn_data->snk_power_level = ( rx_data >> 5 ) & 0x03;
    conn_data->typec_fsm_state = rx_data & 0x0F;
}

void usbcsource_get_fault_status ( usbcsource_t *ctx, fault_status_t *fault_data ) {
    uint8_t rx_data;

    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_HW_FAULT_STATUS_TRANS );

    fault_data->th_145_status            = ( rx_data >> 7 ) & 0x01;
    fault_data->vpu_ovp_fault_trans      = ( rx_data >> 5 ) & 0x01;
    fault_data->vpu_valid_trans          = ( rx_data >> 4 ) & 0x01;
    fault_data->vconn_sw_rvp_fault_trans = ( rx_data >> 2 ) & 0x01;
    fault_data->vconn_sw_ocp_fault_trans = ( rx_data >> 1 ) & 0x01;
    fault_data->vconn_sw_ovp_fault_trans = rx_data & 0x01;
    
    rx_data = usbcsource_read_byte( ctx, USBCSOURCE_REG_HW_FAULT_STATUS );
    
    fault_data->vpu_ovp_fault            = ( rx_data >> 7 ) & 0x01;
    fault_data->vpu_valid                = ( rx_data >> 6 ) & 0x01;
    fault_data->vconn_sw_rvp_fault_cc1   = ( rx_data >> 5 ) & 0x01;
    fault_data->vconn_sw_rvp_fault_cc2   = ( rx_data >> 4 ) & 0x01;
    fault_data->vconn_sw_ocp_fault_cc1   = ( rx_data >> 3 ) & 0x01;
    fault_data->vconn_sw_ocp_fault_cc2   = ( rx_data >> 2 ) & 0x01;
    fault_data->vconn_sw_ovp_fault_cc1   = ( rx_data >> 1 ) & 0x01;
    fault_data->vconn_sw_ovp_fault_cc2   = rx_data & 0x01;
}

void usbcsource_sw_reset ( usbcsource_t *ctx ) {
    usbcsource_write_byte( ctx, USBCSOURCE_REG_RESET_CTRL , USBCSOURCE_RESET_EN );
    dev_device_reset_delay( );
    usbcsource_write_byte ( ctx, USBCSOURCE_REG_RESET_CTRL, USBCSOURCE_RESET_DIS );
    dev_device_reset_delay( );
}

uint8_t usbcsource_set_pdo_config ( usbcsource_t *ctx, pdo_config_t pdo_cfg_data ) {
    uint8_t tx_data[ 4 ];
    uint8_t reg;
    uint8_t tmp;
    uint8_t status;
    uint16_t v_data;
    uint16_t c_data;
    
    status = USBCSOURCE_STATUS_SUCCESS;
    
    reg = USBCSOURCE_REG_SRC_PDO1;
    
    tmp = pdo_cfg_data.pdo_number;
    
    if ( ( tmp < 1 ) || ( tmp > 5 ) ) {
        status = USBCSOURCE_STATUS_ERROR;
    } else {
        tmp -= 1;
        tmp *= 4;
    
        reg += tmp;

        tx_data[ 3 ]  = ( ( pdo_cfg_data.fixed_supply & 0x03 ) << 6 );
        tx_data[ 3 ] |= ( ( pdo_cfg_data.dual_role_power & 0x01 ) << 5 );
        tx_data[ 3 ] |= ( ( pdo_cfg_data.usb_suspend_support & 0x01 ) << 4 );
        tx_data[ 3 ] |= ( ( pdo_cfg_data.unconstr_power & 0x01 ) << 3 );
        tx_data[ 3 ] |= ( ( pdo_cfg_data.usb_commun_capable & 0x01 ) << 2 );
        tx_data[ 3 ] |= ( ( pdo_cfg_data.dual_role_data & 0x01 ) << 1 );
        tx_data[ 3 ] |= pdo_cfg_data.unch_exd_mesg_support & 0x01;
        tx_data[ 2 ] = ( ( pdo_cfg_data.peak_current & 0x03 ) << 4 );
        
        v_data = ( uint16_t ) ( pdo_cfg_data.vtg_data * 20.0 );
        c_data = ( uint16_t ) ( pdo_cfg_data.curr_data * 100.0 );
        
        tx_data[ 2 ] |= ( uint8_t )( ( v_data & 0x03C0 ) >> 6 );
        tx_data[ 1 ] = ( uint8_t ) ( ( v_data & 0x003F ) << 2 );
        tx_data[ 1 ] |= ( uint8_t )( ( c_data & 0x0300 ) >> 8 );
        tx_data[ 0 ] = ( uint8_t ) ( c_data & 0x00FF );

        usbcsource_generic_write( ctx, reg, tx_data, 4 );
    }
    
    return status;
}

uint8_t usbcsource_get_pdo_config ( usbcsource_t *ctx, uint8_t pdo_numb, pdo_config_t *pdo_cfg_data ) {
    uint8_t rx_data[ 4 ];
    uint8_t reg;
    uint16_t tmp;
    uint8_t status;
    
    status = USBCSOURCE_STATUS_SUCCESS;
    
    if ( ( pdo_numb < 1 ) || ( pdo_numb > 5 ) ) {
        status = USBCSOURCE_STATUS_ERROR;
    } else {
        pdo_cfg_data->pdo_number = pdo_numb;
        pdo_numb -= 1;
        pdo_numb *= 4;
        
        reg = USBCSOURCE_REG_SRC_PDO1;
        reg += pdo_numb;

        usbcsource_generic_read( ctx, reg, rx_data, 4 );
        
        pdo_cfg_data->fixed_supply = ( rx_data[ 3 ] >> 6 ) & 0x03;
        pdo_cfg_data->dual_role_power = ( rx_data[ 3 ] >> 5 ) & 0x01;
        pdo_cfg_data->usb_suspend_support = ( rx_data[ 3 ] >> 4 ) & 0x01;
        pdo_cfg_data->unconstr_power = ( rx_data[ 3 ] >> 3 ) & 0x01;
        pdo_cfg_data->usb_commun_capable = ( rx_data[ 3 ] >> 2 ) & 0x01;
        pdo_cfg_data->dual_role_data = ( rx_data[ 3 ] >> 1 ) & 0x01;
        pdo_cfg_data->unch_exd_mesg_support = rx_data[ 3 ] & 0x01;
        pdo_cfg_data->peak_current = ( rx_data[ 2 ] >> 4 ) & 0x03;


        tmp = rx_data[ 2 ] & 0x0F;
        tmp <<= 6;
        tmp |= ( rx_data[ 1 ] & 0xFC ) >> 2;
        
        pdo_cfg_data->vtg_data = ( ( float ) tmp ) / 20.0;
        
        tmp = rx_data[ 1 ] & 0x03;
        tmp <<= 8;
        tmp |= rx_data[ 0 ];
        
        pdo_cfg_data->curr_data = ( ( float ) tmp ) / 100.0;
    }

    return status;
}

void usbcsource_default_config ( usbcsource_t *ctx ) {
    pdo_config_t pdo_cfg;
    
    // PDO 1
    pdo_cfg.pdo_number = USBCSOURCE_SEL_PDO1;
    pdo_cfg.fixed_supply = 0;
    pdo_cfg.dual_role_power = 0;
    pdo_cfg.usb_suspend_support = 0;
    pdo_cfg.unconstr_power = 1;
    pdo_cfg.usb_commun_capable = 0;
    pdo_cfg.dual_role_data = 0;
    pdo_cfg.unch_exd_mesg_support = 0;
    pdo_cfg.peak_current = 0;
    pdo_cfg.vtg_data = 5.0;
    pdo_cfg.curr_data = 3.0;
    usbcsource_set_pdo_config ( ctx, pdo_cfg );
    dev_device_config_delay( );

    // PDO 2
    pdo_cfg.pdo_number = USBCSOURCE_SEL_PDO2;
    pdo_cfg.fixed_supply = 0;
    pdo_cfg.dual_role_power = 0;
    pdo_cfg.usb_suspend_support = 0;
    pdo_cfg.unconstr_power = 0;
    pdo_cfg.usb_commun_capable = 0;
    pdo_cfg.dual_role_data = 0;
    pdo_cfg.unch_exd_mesg_support = 0;
    pdo_cfg.peak_current = 0;
    pdo_cfg.vtg_data = 9.0;
    pdo_cfg.curr_data = 3.0;
    usbcsource_set_pdo_config ( ctx, pdo_cfg );
    dev_device_config_delay( );

    // PDO 3
    pdo_cfg.pdo_number = USBCSOURCE_SEL_PDO3;
    pdo_cfg.fixed_supply = 0;
    pdo_cfg.dual_role_power = 0;
    pdo_cfg.usb_suspend_support = 0;
    pdo_cfg.unconstr_power = 0;
    pdo_cfg.usb_commun_capable = 0;
    pdo_cfg.dual_role_data = 0;
    pdo_cfg.unch_exd_mesg_support = 0;
    pdo_cfg.peak_current = 0;
    pdo_cfg.vtg_data = 12.0;
    pdo_cfg.curr_data = 3.0;
    usbcsource_set_pdo_config ( ctx, pdo_cfg );
    dev_device_config_delay( );

    // PDO 4
    pdo_cfg.pdo_number = USBCSOURCE_SEL_PDO4;
    pdo_cfg.fixed_supply = 0;
    pdo_cfg.dual_role_power = 0;
    pdo_cfg.usb_suspend_support = 0;
    pdo_cfg.unconstr_power = 0;
    pdo_cfg.usb_commun_capable = 0;
    pdo_cfg.dual_role_data = 0;
    pdo_cfg.unch_exd_mesg_support = 0;
    pdo_cfg.peak_current = 0;
    pdo_cfg.vtg_data = 15.0;
    pdo_cfg.curr_data = 3.0;
    usbcsource_set_pdo_config ( ctx, pdo_cfg );
    dev_device_config_delay( );

    // PDO 5
    pdo_cfg.pdo_number = USBCSOURCE_SEL_PDO5;
    pdo_cfg.fixed_supply = 0;
    pdo_cfg.dual_role_power = 0;
    pdo_cfg.usb_suspend_support = 0;
    pdo_cfg.unconstr_power = 0;
    pdo_cfg.usb_commun_capable = 0;
    pdo_cfg.dual_role_data = 0;
    pdo_cfg.unch_exd_mesg_support = 0;
    pdo_cfg.peak_current = 0;
    pdo_cfg.vtg_data = 20.0;
    pdo_cfg.curr_data = 2.25;
    usbcsource_set_pdo_config ( ctx, pdo_cfg );
    dev_device_config_delay( );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_device_reset_delay ( void ) {
    Delay_100ms( );
}

static void dev_device_config_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

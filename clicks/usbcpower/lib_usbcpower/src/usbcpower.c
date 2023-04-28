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
 * @file usbcpower.c
 * @brief USB-C Power Click Driver.
 */

#include "usbcpower.h"
#include "usbcpower_config.h"

/**
 * @brief USB-C Power converts the response function.
 * @details This function converts the response to 32-bit value.
 * @param[in] data_in : The array of data to convert.
 * @return 32-bit response values.
 */
static uint32_t usbcpower_convert_response ( uint8_t *data_in );

void usbcpower_cfg_setup ( usbcpower_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCPOWER_DEVICE_ADDRESS;
}

err_t usbcpower_init ( usbcpower_t *ctx, usbcpower_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t usbcpower_default_cfg ( usbcpower_t *ctx ) 
{   
    uint32_t response;
    uint8_t device_info[ USBCPOWER_DEVICE_INFO_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_device_info( ctx, device_info );
    
    if ( USBCPOWER_RSP_OK != strncmp( device_info, USBCPOWER_RSP_DEVICE_INFO_NAME, 8 ) )
    {
        err_flag = USBCPOWER_ERROR;
    }
    else
    {
        uint8_t sel_mode;
        err_flag |= usbcpower_get_selected_mode ( ctx, &sel_mode );
        Delay_100ms();
    
        if ( sel_mode == USBCPOWER_MODE_PTCH )
        {
            usbcpower_pbms_cfg_t pbms_cfg;
            pbms_cfg.bundle_size = 0x3900;
            pbms_cfg.eeprom_slave_address = 0x50;
            pbms_cfg.timeout_value = 0x32;
            err_flag |= usbcpower_start_patch_burst_mode( ctx, pbms_cfg, &response );
            Delay_100ms();
        
            if ( USBCPOWER_RSP_OK != response )
            {
                err_flag = USBCPOWER_ERROR;
            }
            else
            {
                err_flag |= usbcpower_update_patch_bundle( ctx, pbms_cfg );
                Delay_100ms();
            }
        
            err_flag |= usbcpower_complete_patch_burst_mode( ctx, &response );
            Delay_100ms();
        
            if ( USBCPOWER_RSP_OK != response )
            {
                err_flag |= usbcpower_exit_patch_burst_mode ( ctx, &response );
                err_flag = USBCPOWER_ERROR;
            }
        }
    }
    return err_flag;
}

err_t usbcpower_generic_write ( usbcpower_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t usbcpower_generic_read ( usbcpower_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t usbcpower_get_device_mode ( usbcpower_t *ctx, uint8_t *device_mode ) 
{
    return usbcpower_generic_read( ctx, USBCPOWER_REG_MODE, device_mode, USBCPOWER_MODE_REG_SIZE );
}

err_t usbcpower_get_device_capabilities ( usbcpower_t *ctx, uint8_t *device_cap ) 
{
    return usbcpower_generic_read( ctx, USBCPOWER_REG_DEVICE_CAP, device_cap, USBCPOWER_DEVICE_CAP_REG_SIZE );
}

err_t usbcpower_device_info ( usbcpower_t *ctx, uint8_t *device_info ) 
{
    uint8_t data_buf[ USBCPOWER_DEVICE_INFO_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_DEVICE_INFO, data_buf, USBCPOWER_DEVICE_INFO_REG_SIZE );
    for ( uint8_t cnt = 0; cnt < USBCPOWER_DEVICE_INFO_REG_SIZE; cnt++ )
    {
        device_info[ cnt ] = data_buf[ cnt + 1 ];
    }
    return err_flag;
}

err_t usbcpower_set_patch_mode ( usbcpower_t *ctx, uint32_t *response ) 
{
    uint8_t data_buf[ USBCPOWER_CMD1_REG_SIZE ] = { 0 };
    strcpy( data_buf, USBCPOWER_CMD_GO2P );
    err_t err_flag = usbcpower_generic_write( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    *response = usbcpower_convert_response( data_buf );
    return err_flag;
}

err_t usbcpower_start_patch_burst_mode ( usbcpower_t *ctx, usbcpower_pbms_cfg_t pbms_cfg, uint32_t *response ) 
{
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 0 ] = 6;
    data_buf[ 1 ] = ( uint8_t ) pbms_cfg.bundle_size;
    data_buf[ 2 ] = ( uint8_t ) ( pbms_cfg.bundle_size >> 8 );
    data_buf[ 3 ] = ( uint8_t ) ( pbms_cfg.bundle_size >> 16 );
    data_buf[ 4 ] = ( uint8_t ) ( pbms_cfg.bundle_size >> 24 );
    data_buf[ 5 ] = pbms_cfg.eeprom_slave_address;
    data_buf[ 6 ] = pbms_cfg.timeout_value;
    err_t err_flag = usbcpower_generic_write( ctx, USBCPOWER_REG_DATA, data_buf, 7 );
    Delay_10ms( );
    strcpy( data_buf, USBCPOWER_CMD_PBMs );
    err_flag |= usbcpower_generic_write( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    *response = usbcpower_convert_response( data_buf );
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_DATA, data_buf, 2 );
    Delay_1ms( );
    if ( USBCPOWER_RSP_OK != data_buf[ 1 ] )
    {
        err_flag = USBCPOWER_ERROR;    
    }
    return err_flag;
}

err_t usbcpower_complete_patch_burst_mode ( usbcpower_t *ctx, uint32_t *response ) 
{
    uint8_t data_buf[ USBCPOWER_CMD1_REG_SIZE ] = { 0 };
    data_buf[ 0 ] = 0;
    data_buf[ 1 ] = 0;
    err_t err_flag = usbcpower_generic_write( ctx, USBCPOWER_REG_DATA, data_buf, 2 );
    Delay_1ms( );
    strcpy( data_buf, USBCPOWER_CMD_PBMc );
    err_flag |= usbcpower_generic_write( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_DATA, data_buf, 5 );
    Delay_1ms( );
    *response = usbcpower_convert_response( data_buf );
    if ( USBCPOWER_RSP_OK != data_buf[ 1 ] )
    {
        err_flag = USBCPOWER_ERROR;    
    }
    return err_flag;
}

err_t usbcpower_exit_patch_burst_mode ( usbcpower_t *ctx, uint32_t *response ) 
{
    uint8_t data_buf[ USBCPOWER_CMD1_REG_SIZE ] = { 0 };
    data_buf[ 0 ] = 0;
    data_buf[ 1 ] = 0;
    err_t err_flag = usbcpower_generic_write( ctx, USBCPOWER_REG_DATA, data_buf, 2 );
    Delay_10ms( );
    strcpy( data_buf, USBCPOWER_CMD_PBMe );
    err_flag |= usbcpower_generic_write( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_CMD1, data_buf, USBCPOWER_CMD1_REG_SIZE );
    Delay_1ms( );
    if ( USBCPOWER_RSP_OK != data_buf[ 1 ] )
    {
        err_flag = USBCPOWER_ERROR;
    }
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_DATA, data_buf, 5 );
    Delay_1ms( );
    *response = usbcpower_convert_response( data_buf );
    return err_flag;
}

err_t usbcpower_get_selected_mode ( usbcpower_t *ctx, uint8_t *sel_mode ) 
{
    uint8_t data_buf[ 5 ] = { 0 };
    uint8_t cmp_buf[ 5 ] = { 0 };
    err_t err_flag = usbcpower_get_device_mode( ctx, data_buf );
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        cmp_buf[ cnt ] = data_buf[ cnt + 1 ];
    }
    if ( USBCPOWER_RSP_OK == strcmp( cmp_buf, USBCPOWER_RSP_PTCH ) )
    {
        *sel_mode = USBCPOWER_MODE_PTCH;
    }
    else if ( USBCPOWER_RSP_OK == strcmp( cmp_buf, USBCPOWER_RSP_APP ) )
    {
        *sel_mode = USBCPOWER_MODE_APP;
    }
    else if ( USBCPOWER_RSP_OK == strcmp( cmp_buf, USBCPOWER_RSP_BOOT ) )
    {
        *sel_mode = USBCPOWER_MODE_BOOT;
    }
    else
    {
        *sel_mode = USBCPOWER_MODE_UNKNOWN;
    }
    return err_flag;
}

err_t usbcpower_update_patch_bundle ( usbcpower_t *ctx, usbcpower_pbms_cfg_t pbms_cfg ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    uint32_t cnt = 0;
    uint32_t len = 0;
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, pbms_cfg.eeprom_slave_address );
    Delay_10ms( );
#if ( USBCPOWER_PD_MODE_SELECTOR == USBCPOWER_PD_CON_MODE_SOURCE )
    len = sizeof ( usbcpower_source_i2c_array );
    while ( cnt < len )
    {
        if ( ( len - cnt ) >= 256 ) 
        {
            memcpy ( data_buf, &usbcpower_source_i2c_array[ cnt ], 256 );
            err_flag |= i2c_master_write( &ctx->i2c, data_buf, 256 );
        }
        else
        {
            memcpy ( data_buf, &usbcpower_source_i2c_array[ cnt ], len - cnt );
            err_flag |= i2c_master_write( &ctx->i2c, data_buf, len - cnt );
        }
        cnt += 256;
    }
#else
    len = sizeof ( usbcpower_sink_i2c_array );
    while ( cnt < len )
    {
        if ( ( len - cnt ) >= 256 ) 
        {
            memcpy ( data_buf, &usbcpower_sink_i2c_array[ cnt ], 256 );
            err_flag |= i2c_master_write( &ctx->i2c, data_buf, 256 );
        }
        else
        {
            memcpy ( data_buf, &usbcpower_sink_i2c_array[ cnt ], len - cnt );
            err_flag |= i2c_master_write( &ctx->i2c, data_buf, len - cnt );
        }
        cnt += 256;
    }    
#endif
    Delay_10ms( );
    err_flag |= i2c_master_set_slave_address( &ctx->i2c, USBCPOWER_DEVICE_ADDRESS );
    return err_flag;
}

err_t usbcpower_get_status ( usbcpower_t *ctx, usbcpower_status_t *status ) 
{
    uint8_t data_buf[ USBCPOWER_STATUS_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_STATUS, data_buf, USBCPOWER_STATUS_REG_SIZE );
    status->plug_present     =   data_buf[ 1 ]        & 0x01;
    status->conn_state       = ( data_buf[ 1 ] >> 1 ) & 0x07;
    status->plug_orientation = ( data_buf[ 1 ] >> 4 ) & 0x01;
    status->port_role        = ( data_buf[ 1 ] >> 5 ) & 0x01;
    status->data_role        = ( data_buf[ 1 ] >> 6 ) & 0x01;
    status->vbus_status      = ( data_buf[ 4 ] >> 4 ) & 0x03;
    status->usb_hos_tpresent = ( data_buf[ 4 ] >> 6 ) & 0x03;
    status->acting_as_legacy =   data_buf[ 5 ]        & 0x01;
    status->bist             = ( data_buf[ 5 ] >> 3 ) & 0x01;
    return err_flag;
}

err_t usbcpower_get_pwr_path_status ( usbcpower_t *ctx, usbcpower_pwr_path_status_t *pp_status ) 
{
    uint8_t data_buf[ USBCPOWER_POWER_PATH_STATUS_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_POWER_PATH_STATUS, data_buf, USBCPOWER_POWER_PATH_STATUS_REG_SIZE );
    pp_status->pp_cable1_switch =   data_buf[ 1 ]        & 0x03;
    pp_status->pp1_switch       = ( data_buf[ 1 ] >> 6 ) & 0x03;
    pp_status->pp1_switch      |= ( data_buf[ 2 ] << 2 ) & 0x04;
    pp_status->pp3_switch       = ( data_buf[ 2 ] >> 4 ) & 0x07;
    pp_status->pp1_overcurrent  = ( data_buf[ 4 ] >> 1 ) & 0x01;
    pp_status->pp_cable1_ovc    = ( data_buf[ 5 ] >> 2 ) & 0x01;
    pp_status->power_source     = ( data_buf[ 5 ] >> 6 ) & 0x03;
    return err_flag;
}

err_t usbcpower_get_boot_status ( usbcpower_t *ctx, usbcpower_boot_status_t *boot_status ) 
{
    uint8_t data_buf[ USBCPOWER_BOOT_STATUS_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_BOOT_STATUS, data_buf, USBCPOWER_BOOT_STATUS_REG_SIZE );
    boot_status->patch_header_err   =   data_buf[ 1 ]        & 0x01;
    boot_status->dead_battery_flag  = ( data_buf[ 1 ] >> 2 ) & 0x01;
    boot_status->i2c_eeprom_present = ( data_buf[ 1 ] >> 3 ) & 0x01;
    boot_status->patch_downloader   = ( data_buf[ 2 ] >> 2 ) & 0x01;
    boot_status->master_tsd         = ( data_buf[ 3 ] >> 3 ) & 0x01;
    boot_status->patch_cfg_source   = ( data_buf[ 4 ] >> 5 ) & 0x07;
    boot_status->rev_id             =   data_buf[ 5 ];
    return err_flag;
}

err_t usbcpower_get_rx_caps ( usbcpower_t *ctx, usbcpower_rx_caps_t *rx_caps ) 
{
    uint8_t data_buf[ USBCPOWER_RX_SOURCE_CAPS_REG_SIZE ] = { 0 };
    uint32_t tmp = 0;
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_RX_SOURCE_CAPS, data_buf, USBCPOWER_RX_SOURCE_CAPS_REG_SIZE );
    rx_caps->num_src_pdos = data_buf[ 1 ] & 0x03;
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        tmp = 0;
        tmp = data_buf[ cnt + 2 ];
        tmp <<= 8;
        tmp |= data_buf[ cnt + 3 ];
        tmp <<= 8;
        tmp |= data_buf[ cnt + 4 ];
        tmp <<= 8;
        tmp |= data_buf[ cnt + 5 ];
        rx_caps->source_pdo[ cnt ] = tmp;
    }
    err_flag |= usbcpower_generic_read( ctx, USBCPOWER_REG_RX_SINK_CAPS, data_buf, USBCPOWER_RX_SINK_CAPS_REG_SIZE );
    rx_caps->num_sink_pdos = data_buf[ 1 ] & 0x03;
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        tmp = 0;
        tmp = data_buf[ cnt + 2 ];
        tmp <<= 8;
        tmp |= data_buf[ cnt + 3 ];
        tmp <<= 8;
        tmp |= data_buf[ cnt + 4 ];
        tmp <<= 8;
        tmp |= data_buf[ cnt + 5 ];
        rx_caps->sink_pdo[ cnt ] = tmp;
    }   
    return err_flag;
}

err_t usbcpower_get_pwr_status ( usbcpower_t *ctx, usbcpower_pwr_status_t *pwr_status ) 
{
    uint8_t data_buf[ USBCPOWER_POWER_STATUS_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_POWER_STATUS, data_buf, USBCPOWER_POWER_STATUS_REG_SIZE );
    pwr_status->pwr_conn          =   data_buf[ 1 ]        & 0x01;
    pwr_status->src_sink          = ( data_buf[ 1 ] >> 1 ) & 0x01;
    pwr_status->type_c_current    = ( data_buf[ 1 ] >> 2 ) & 0x03;
    pwr_status->charger_detect    = ( data_buf[ 1 ] >> 4 ) & 0x0F;
    pwr_status->charger_advertise =   data_buf[ 2 ]        & 0x03;
    return err_flag;
}

err_t usbcpower_get_pd_status ( usbcpower_t *ctx, usbcpower_pd_status_t *pd_status ) 
{
    uint8_t data_buf[ USBCPOWER_PD_STATUS_REG_SIZE ] = { 0 };
    err_t err_flag = usbcpower_generic_read( ctx, USBCPOWER_REG_PD_STATUS, data_buf, USBCPOWER_PD_STATUS_REG_SIZE );
    pd_status->cc_pull_up    = ( data_buf[ 1 ] >> 1 ) & 0x03;
    pd_status->port_type     = ( data_buf[ 1 ] >> 4 ) & 0x03;
    pd_status->pd_role       = ( data_buf[ 1 ] >> 6 ) & 0x01;
    pd_status->soft_rst_dets = ( data_buf[ 2 ]      ) & 0x1F;
    pd_status->hard_rst_dets =   data_buf[ 3 ]        & 0x3F;
    pd_status->err_rec_dets  = ( data_buf[ 3 ] >> 6 ) & 0x03;
    pd_status->err_rec_dets |= ( data_buf[ 4 ] & 0x0F ) << 2;
    pd_status->data_rst_dets = ( data_buf[ 4 ] >> 6 ) & 0x07;
    return err_flag;
}

uint8_t usbcpower_get_int_pin ( usbcpower_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

static uint32_t usbcpower_convert_response ( uint8_t *data_in )
{
    uint32_t response = data_in[ 1 ];
    response <<= 8;
    response |= data_in[ 2 ];
    response <<= 8;
    response |= data_in[ 3 ];
    response <<= 8;
    response |= data_in[ 4 ];
    return response;
}

// ------------------------------------------------------------------------- END

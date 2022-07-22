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
 * @file lightranger9.c
 * @brief LightRanger 9 Click Driver.
 */

#include "lightranger9.h"
#include "tof_bin_image.h"

/**
 * @brief LightRanger 9 calculate checksum function.
 * @details This function calculates the checksum byte from the input bytes.
 * @param[in] data_in : Input data bytes.
 * @param[in] len : Number of data bytes.
 * @return Calculated checksum byte.
 * @note None.
 */
static uint8_t lightranger9_calculate_checksum ( uint8_t *data_in, uint8_t len );

void lightranger9_cfg_setup ( lightranger9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->gpio0 = HAL_PIN_NC;
    cfg->gpio1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHTRANGER9_DEVICE_ADDRESS;
}

err_t lightranger9_init ( lightranger9_t *ctx, lightranger9_cfg_t *cfg ) 
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

    digital_out_init( &ctx->gpio0, cfg->gpio0 );
    digital_out_init( &ctx->gpio1, cfg->gpio1 );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_low ( &ctx->gpio0 );
    digital_out_low ( &ctx->gpio1 );
    digital_out_low ( &ctx->en );
    
    return I2C_MASTER_SUCCESS;
}

err_t lightranger9_default_cfg ( lightranger9_t *ctx ) 
{
    err_t error_flag = LIGHTRANGER9_OK;
    lightranger9_enable_device ( ctx );
    Delay_100ms ( );
    if ( LIGHTRANGER9_ERROR == lightranger9_check_communication ( ctx ) )
    {
        return LIGHTRANGER9_ERROR;
    }
    // Activate oscillator
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_ENABLE, LIGHTRANGER9_ENABLE_PON );
    Delay_100ms ( );

    // Download FW bin if the bootloader is running
    error_flag |= lightranger9_download_fw_bin ( ctx );
    
    // Set measurement period
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_CONFIG_RESULT, LIGHTRANGER9_CONFIG_RESULT_COMMON_CID );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_CMD_STAT, LIGHTRANGER9_CMD_STAT_LOAD_CFG_PAGE_COMMON );
    Delay_100ms ( );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_PERIOD_MS_LSB, 
                                                ( uint8_t ) ( LIGHTRANGER9_DEFAULT_MEASUREMENT_PERIOD_MS & 0xFF ) );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_PERIOD_MS_MSB, 
                                                ( uint8_t ) ( ( LIGHTRANGER9_DEFAULT_MEASUREMENT_PERIOD_MS >> 8 ) & 0xFF ) );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_CMD_STAT, LIGHTRANGER9_CMD_STAT_WRITE_CFG_PAGE );
    Delay_100ms ( );
    
    // Enable measurement ready interrupt, start measurement and clear interrupts
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_INT_ENAB, LIGHTRANGER9_INT_ENAB_MEAS_READY );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_CONFIG_RESULT, LIGHTRANGER9_CONFIG_RESULT_MEAS );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_CMD_STAT, LIGHTRANGER9_CMD_STAT_MEASURE );
    error_flag |= lightranger9_clear_interrupts ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t lightranger9_generic_write ( lightranger9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t lightranger9_generic_read ( lightranger9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t lightranger9_write_register ( lightranger9_t *ctx, uint8_t reg, uint8_t data_in )
{
    return lightranger9_generic_write ( ctx, reg, &data_in, 1 );
}

err_t lightranger9_read_register ( lightranger9_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return lightranger9_generic_read ( ctx, reg, data_out, 1 );
}

err_t lightranger9_write_bl_cmd ( lightranger9_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = len;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    data_buf[ len + 2 ] = lightranger9_calculate_checksum ( data_buf, len + 2 );
    return lightranger9_generic_write ( ctx, LIGHTRANGER9_REG_CMD_STAT, data_buf, len + 3 );
}

err_t lightranger9_read_bl_cmd_status ( lightranger9_t *ctx, uint8_t *status )
{
    err_t error_flag = LIGHTRANGER9_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    error_flag |= lightranger9_generic_read ( ctx, LIGHTRANGER9_REG_CMD_STAT, data_buf, 3 );
    if ( ( data_buf[ 1 ] ) ||
         ( data_buf[ 2 ] != lightranger9_calculate_checksum ( data_buf, 2 ) ) || 
         ( LIGHTRANGER9_ERROR == error_flag ) )
    {
        return LIGHTRANGER9_ERROR;
    }
    *status = data_buf[ 0 ];
    return LIGHTRANGER9_OK;
}

err_t lightranger9_check_communication ( lightranger9_t *ctx )
{
    uint8_t device_id;
    if ( LIGHTRANGER9_OK == lightranger9_read_register ( ctx, LIGHTRANGER9_REG_ID, &device_id ) )
    {
        if ( LIGHTRANGER9_DEVICE_ID == device_id )
        {
            return LIGHTRANGER9_OK;
        }
    }
    return LIGHTRANGER9_ERROR;
}

void lightranger9_set_gpio0_pin ( lightranger9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->gpio0, state );
}

void lightranger9_set_gpio1_pin ( lightranger9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->gpio1, state );
}

void lightranger9_enable_device ( lightranger9_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void lightranger9_disable_device ( lightranger9_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t lightranger9_get_int_pin ( lightranger9_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t lightranger9_download_fw_bin ( lightranger9_t *ctx )
{
    #define BL_MAX_CHUNK_BYTES      128
    #define BL_DOWNLOAD_INIT_SEED   0x29
    #define BL_START_ADDRESS        0x0000
    uint8_t data_buf[ BL_MAX_CHUNK_BYTES ] = { 0 };
    err_t error_flag = LIGHTRANGER9_OK;
    uint16_t timeout_cnt = 0;
    uint32_t fw_index = 0;
    uint8_t chunk_bytes = 0;
    error_flag |= lightranger9_read_register ( ctx, LIGHTRANGER9_REG_APPID, data_buf );
    if ( LIGHTRANGER9_APP_ID_BOOTLOADER == data_buf[ 0 ] )
    {
        data_buf[ 0 ] = BL_DOWNLOAD_INIT_SEED;
        error_flag |= lightranger9_write_bl_cmd ( ctx, LIGHTRANGER9_BL_CMD_DOWNLOAD_INIT, data_buf, 1 );
        timeout_cnt = 0;
        do
        {
            Delay_1ms ( );
            error_flag |= lightranger9_read_bl_cmd_status ( ctx, data_buf );
            if ( ++timeout_cnt > LIGHTRANGER9_TIMEOUT )
            {
                return LIGHTRANGER9_ERROR;
            }
        } while ( LIGHTRANGER9_BL_CMD_STAT_READY != data_buf[ 0 ] );
        
        data_buf[ 0 ] = BL_START_ADDRESS & 0xFF;
        data_buf[ 1 ] = ( BL_START_ADDRESS >> 8 ) & 0xFF;
        error_flag |= lightranger9_write_bl_cmd ( ctx, LIGHTRANGER9_BL_CMD_ADDR_RAM, data_buf, 2 );
        timeout_cnt = 0;
        do
        {
            Delay_1ms ( );
            error_flag |= lightranger9_read_bl_cmd_status ( ctx, data_buf );
            if ( ++timeout_cnt > LIGHTRANGER9_TIMEOUT )
            {
                return LIGHTRANGER9_ERROR;
            }
        } while ( LIGHTRANGER9_BL_CMD_STAT_READY != data_buf[ 0 ] );
        
        while ( fw_index < sizeof ( tof_bin_image ) )
        {
            if ( ( fw_index + BL_MAX_CHUNK_BYTES ) <= sizeof ( tof_bin_image ) )
            {
                chunk_bytes = BL_MAX_CHUNK_BYTES;
            }
            else
            {
                chunk_bytes = sizeof ( tof_bin_image ) - fw_index;
            }
            memcpy ( data_buf, &tof_bin_image[ fw_index ], chunk_bytes );
            error_flag |= lightranger9_write_bl_cmd ( ctx, LIGHTRANGER9_BL_CMD_W_RAM, data_buf, chunk_bytes );
            fw_index += chunk_bytes;
            timeout_cnt = 0;
            do
            {
                Delay_1ms ( );
                error_flag |= lightranger9_read_bl_cmd_status ( ctx, data_buf );
                if ( ++timeout_cnt > LIGHTRANGER9_TIMEOUT )
                {
                    return LIGHTRANGER9_ERROR;
                }
            } while ( LIGHTRANGER9_BL_CMD_STAT_READY != data_buf[ 0 ] );
        }
        
        error_flag |= lightranger9_write_bl_cmd ( ctx, LIGHTRANGER9_BL_CMD_RAMREMAP_RESET, NULL, 0 );
        timeout_cnt = 0;
        do
        {
            Delay_1ms ( );
            error_flag |= lightranger9_read_register ( ctx, LIGHTRANGER9_REG_APPID, data_buf );
            if ( ++timeout_cnt > LIGHTRANGER9_TIMEOUT )
            {
                return LIGHTRANGER9_ERROR;
            }
        } while ( LIGHTRANGER9_APP_ID_MEASUREMENT != data_buf[ 0 ] );
    }
    return error_flag;
}

err_t lightranger9_clear_interrupts ( lightranger9_t *ctx )
{
    uint8_t int_status;
    err_t error_flag = lightranger9_read_register ( ctx, LIGHTRANGER9_REG_INT_STATUS, &int_status );
    error_flag |= lightranger9_write_register ( ctx, LIGHTRANGER9_REG_INT_STATUS, int_status );
    return error_flag;
}

err_t lightranger9_get_capture ( lightranger9_t *ctx, lightranger9_capture_t *capture )
{
    uint8_t data_buf[ LIGHTRANGER9_BLOCKREAD_SIZE ] = { 0 };
    if ( LIGHTRANGER9_OK == lightranger9_generic_read ( ctx, LIGHTRANGER9_REG_BLOCKREAD, 
                                                        data_buf, LIGHTRANGER9_BLOCKREAD_SIZE ) )
    {
        capture->sub_capture = 
            data_buf[ LIGHTRANGER9_REG_RESULT_NUMBER - LIGHTRANGER9_REG_BLOCKREAD ] & LIGHTRANGER9_SUBCAPTURE_MASK;
        capture->result_number = 
            ( data_buf[ LIGHTRANGER9_REG_RESULT_NUMBER - LIGHTRANGER9_REG_BLOCKREAD ] >> 2 ) & LIGHTRANGER9_RESULT_NUMBER_MASK;
        capture->temperature = ( int8_t ) data_buf[ LIGHTRANGER9_REG_TEMPERATURE - LIGHTRANGER9_REG_BLOCKREAD ];
        capture->valid_results = data_buf[ LIGHTRANGER9_REG_NUMBER_VALID_RESULTS - LIGHTRANGER9_REG_BLOCKREAD ];
        capture->ambient_light = 
            ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_AMBIENT_LIGHT_3 - LIGHTRANGER9_REG_BLOCKREAD ] << 24 ) | 
            ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_AMBIENT_LIGHT_2 - LIGHTRANGER9_REG_BLOCKREAD ] << 16 ) | 
            ( ( uint16_t ) data_buf[ LIGHTRANGER9_REG_AMBIENT_LIGHT_1 - LIGHTRANGER9_REG_BLOCKREAD ] << 8 ) | 
            data_buf[ LIGHTRANGER9_REG_AMBIENT_LIGHT_0 - LIGHTRANGER9_REG_BLOCKREAD ];
        capture->photon_count = 
            ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_PHOTON_COUNT_3 - LIGHTRANGER9_REG_BLOCKREAD ] << 24 ) | 
            ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_PHOTON_COUNT_2 - LIGHTRANGER9_REG_BLOCKREAD ] << 16 ) | 
            ( ( uint16_t ) data_buf[ LIGHTRANGER9_REG_PHOTON_COUNT_1 - LIGHTRANGER9_REG_BLOCKREAD ] << 8 ) | 
            data_buf[ LIGHTRANGER9_REG_PHOTON_COUNT_0 - LIGHTRANGER9_REG_BLOCKREAD ];
        capture->reference_count = 
            ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_REFERENCE_COUNT_3 - LIGHTRANGER9_REG_BLOCKREAD ] << 24 ) | 
            ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_REFERENCE_COUNT_2 - LIGHTRANGER9_REG_BLOCKREAD ] << 16 ) | 
            ( ( uint16_t ) data_buf[ LIGHTRANGER9_REG_REFERENCE_COUNT_1 - LIGHTRANGER9_REG_BLOCKREAD ] << 8 ) | 
            data_buf[ LIGHTRANGER9_REG_REFERENCE_COUNT_0 - LIGHTRANGER9_REG_BLOCKREAD ];
        capture->sys_tick_sec = 
            ( ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_SYS_TICK_3 - LIGHTRANGER9_REG_BLOCKREAD ] << 24 ) | 
              ( ( uint32_t ) data_buf[ LIGHTRANGER9_REG_SYS_TICK_2 - LIGHTRANGER9_REG_BLOCKREAD ] << 16 ) | 
              ( ( uint16_t ) data_buf[ LIGHTRANGER9_REG_SYS_TICK_1 - LIGHTRANGER9_REG_BLOCKREAD ] << 8 ) | 
              data_buf[ LIGHTRANGER9_REG_SYS_TICK_0 - LIGHTRANGER9_REG_BLOCKREAD ] ) * LIGHTRANGER9_SYS_TICK_TO_SEC;
        for ( uint8_t cnt = 0; cnt < LIGHTRANGER9_MAX_MEAS_RESULTS; cnt++ )
        {
            capture->result[ cnt ].confidence = 
                data_buf[ LIGHTRANGER9_REG_RES_CONFIDENCE_0 - LIGHTRANGER9_REG_BLOCKREAD + cnt * 3 ];
            if ( capture->result[ cnt ].confidence >= LIGHTRANGER9_CONFIDENCE_THRESHOLD )
            {
                capture->result[ cnt ].distance_mm = 
                    ( ( uint16_t ) data_buf[ LIGHTRANGER9_REG_RES_DISTANCE_0_MSB - LIGHTRANGER9_REG_BLOCKREAD + cnt * 3 ] << 8 ) | 
                    data_buf[ LIGHTRANGER9_REG_RES_DISTANCE_0_LSB - LIGHTRANGER9_REG_BLOCKREAD + cnt * 3 ];
            }
            else
            {
                capture->result[ cnt ].distance_mm = 0;
            }
        }
        return LIGHTRANGER9_OK;
    }
    return LIGHTRANGER9_ERROR;
}

static uint8_t lightranger9_calculate_checksum ( uint8_t *data_in, uint8_t len )
{
    uint16_t data_sum = 0;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_sum += data_in[ cnt ];
    }
    return ( uint8_t ) ( ( ~data_sum ) & 0xFF );
}

// ------------------------------------------------------------------------- END

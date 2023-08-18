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
 * @file proximity16.c
 * @brief Proximity 16 Click Driver.
 */

#include "proximity16.h"
#include "firmware_buffers.h"

/**
 * @brief Proximity 16 swap buffer function.
 * @details This function swaps a buffer. The buffer size is always a multiple of 4 (4, 8, 12, 16, ...).
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in,out] buffer : Buffer to swap, generally uint32_t.
 * @param[in] size : Buffer size to swap.
 * @return None.
 * @note None.
 */
static void proximity16_swap_buffer ( uint8_t *buffer, uint16_t size );

/**
 * @brief Proximity 16 poll for answer function.
 * @details This function waits for an answer from the sensor.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] size : Data read size.
 * @param[in] pos : Position in data buffer.
 * @param[in] address : Address of data.
 * @param[in] mask : Data bit mask to compare.
 * @param[in] expected_value : Expected value of masked bits.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proximity16_poll_for_answer ( proximity16_t *ctx, uint8_t size, uint8_t pos,
                                           uint16_t address, uint8_t mask, uint8_t expected_value );

/**
 * @brief Proximity 16 poll for mcu boot function.
 * @details This function waits for the sensor MCU to boot.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proximity16_poll_for_mcu_boot ( proximity16_t *ctx );

/**
 * @brief Proximity 16 send offset data function.
 * @details This function sets the offset data gathered from NVM for the selected resolution
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] resolution : Use macro PROXIMITY16_RESOLUTION_4X4 or PROXIMITY16_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proximity16_send_offset_data ( proximity16_t *ctx, uint8_t resolution );

/**
 * @brief Proximity 16 send xtalk data function.
 * @details This function sets the Xtalk data from generic configuration, or user's calibration for the selected resolution.
 * @param[in] ctx : Click context object.
 * See #proximity16_t object definition for detailed explanation.
 * @param[in] resolution : Use macro PROXIMITY16_RESOLUTION_4X4 or PROXIMITY16_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proximity16_send_xtalk_data ( proximity16_t *ctx, uint8_t resolution );

void proximity16_cfg_setup ( proximity16_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->i2c_rst = HAL_PIN_NC;
    cfg->lpn = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = PROXIMITY16_DEVICE_ADDRESS;
}

err_t proximity16_init ( proximity16_t *ctx, proximity16_cfg_t *cfg ) 
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

    digital_out_init( &ctx->i2c_rst, cfg->i2c_rst );
    digital_out_init( &ctx->lpn, cfg->lpn );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_low ( &ctx->i2c_rst );
    digital_out_high ( &ctx->lpn );

    return I2C_MASTER_SUCCESS;
}

err_t proximity16_default_cfg ( proximity16_t *ctx ) 
{
    err_t error_flag = PROXIMITY16_OK;
    proximity16_reset_i2c ( ctx );
    if ( PROXIMITY16_ERROR == proximity16_check_communication ( ctx ) )
    {
        return PROXIMITY16_ERROR;
    }
    error_flag |= proximity16_sensor_init ( ctx );
    error_flag |= proximity16_set_resolution ( ctx, PROXIMITY16_DEF_RESOLUTION );
    error_flag |= proximity16_set_ranging_frequency_hz ( ctx, PROXIMITY16_DEF_RANGING_FREQ_HZ );
    error_flag |= proximity16_set_ranging_mode ( ctx, PROXIMITY16_DEF_RANGING_MODE );
    error_flag |= proximity16_set_integration_time_ms ( ctx, PROXIMITY16_DEF_INTEGRATION_TIME_MS );
    error_flag |= proximity16_start_ranging ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t proximity16_write_multi ( proximity16_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len )
{
    if ( len > 16 )
    {
        return PROXIMITY16_ERROR;
    }
    uint8_t data_buf[ 18 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2c_master_write ( &ctx->i2c, data_buf, len + 2 );
}

err_t proximity16_read_multi ( proximity16_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    err_t error_flag = i2c_master_write ( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_read ( &ctx->i2c, data_out, len );
    return error_flag;
}

err_t proximity16_write_byte ( proximity16_t *ctx, uint16_t reg, uint8_t data_in )
{
    return proximity16_write_multi ( ctx, reg, &data_in, 1 );
}

err_t proximity16_read_byte ( proximity16_t *ctx, uint16_t reg, uint8_t *data_out )
{
    return proximity16_read_multi ( ctx, reg, data_out, 1 );
}

err_t proximity16_write_data ( proximity16_t *ctx, uint8_t *data_in, uint16_t len )
{
    return i2c_master_write ( &ctx->i2c, data_in, len );
}

err_t proximity16_check_communication ( proximity16_t *ctx )
{
    err_t error_flag = PROXIMITY16_OK;
    uint8_t device_id;
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_read_byte ( ctx, 0x0000, &device_id );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x02 );
    if ( ( PROXIMITY16_OK == error_flag ) && ( 0xF0 == device_id ) )
    {
        return PROXIMITY16_OK;
    }
    return PROXIMITY16_ERROR;
}

uint8_t proximity16_get_int_pin ( proximity16_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void proximity16_set_i2c_rst_pin ( proximity16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->i2c_rst, state );
}

void proximity16_set_lpn_pin ( proximity16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->lpn, state );
}

void proximity16_reset_i2c ( proximity16_t *ctx )
{
    digital_out_low ( &ctx->i2c_rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->i2c_rst );
    Delay_100ms ( );
    digital_out_low ( &ctx->i2c_rst );
    Delay_100ms ( );
}

err_t proximity16_sensor_init ( proximity16_t *ctx )
{
    err_t error_flag = PROXIMITY16_OK;
    /* SW reboot sequence */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0009, 0x04 );
    error_flag |= proximity16_write_byte ( ctx, 0x000F, 0x40 );
    error_flag |= proximity16_write_byte ( ctx, 0x000A, 0x03 );
    uint8_t tmp;
    error_flag |= proximity16_read_byte ( ctx, 0x7FFF, &tmp  );
    error_flag |= proximity16_write_byte ( ctx, 0x000C, 0x01 );

    error_flag |= proximity16_write_byte ( ctx, 0x0101, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0102, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x010A, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x4002, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x4002, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x010A, 0x03 );
    error_flag |= proximity16_write_byte ( ctx, 0x0103, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x000C, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x000F, 0x43 );
    Delay_1ms ( );

    error_flag |= proximity16_write_byte ( ctx, 0x000F, 0x40 );
    error_flag |= proximity16_write_byte ( ctx, 0x000A, 0x01 );
    Delay_100ms ( );
    
    /* Wait for sensor booted (several ms required to get sensor ready ) */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_poll_for_answer ( ctx, 1, 0, 0x06, 0xFF, 0x01 );
    if ( PROXIMITY16_OK != error_flag )
    {
        return error_flag;
    }
    
    error_flag |= proximity16_write_byte ( ctx, 0x000E, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x02 );

    /* Enable FW access */
    error_flag |= proximity16_write_byte ( ctx, 0x03, 0x0D );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x01 );
    error_flag |= proximity16_poll_for_answer ( ctx, 1, 0, 0x21, 0x10, 0x10 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );

    /* Enable host access to GO1 */
    error_flag |= proximity16_read_byte ( ctx, 0x7FFF, &tmp );
    error_flag |= proximity16_write_byte ( ctx, 0x0C, 0x01 );

    /* Power ON error_flag */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0101, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0102, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x010A, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x4002, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x4002, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x010A, 0x03 );
    error_flag |= proximity16_write_byte ( ctx, 0x0103, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x400F, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x021A, 0x43 );
    error_flag |= proximity16_write_byte ( ctx, 0x021A, 0x03 );
    error_flag |= proximity16_write_byte ( ctx, 0x021A, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x021A, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0219, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x021B, 0x00 );

    /* Wake up MCU */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_read_byte ( ctx, 0x7FFF, &tmp );
    error_flag |= proximity16_write_byte ( ctx, 0x0C, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x01 );
    error_flag |= proximity16_write_byte ( ctx, 0x20, 0x07 );
    error_flag |= proximity16_write_byte ( ctx, 0x20, 0x06 );

    /* Download FW into VL53L5 */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x09 );
    error_flag |= proximity16_write_data ( ctx, ( uint8_t * ) &proximity16_firmware_buf[ 0 ], 0x8002 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x0A );
    error_flag |= proximity16_write_data ( ctx, ( uint8_t * ) &proximity16_firmware_buf[ 0x8002 ], 0x8002 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x0B );
    error_flag |= proximity16_write_data ( ctx, ( uint8_t * ) &proximity16_firmware_buf[ 0x10004 ], 0x5002 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x01 );

    /* Check if FW correctly downloaded */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x02 );
    error_flag |= proximity16_write_byte ( ctx, 0x03, 0x0D );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x01 );
    error_flag |= proximity16_poll_for_answer ( ctx, 1, 0, 0x21, 0x10, 0x10 );
    if ( PROXIMITY16_OK != error_flag )
    {
        return error_flag;
    }

    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_read_byte ( ctx, 0x7FFF, &tmp );
    error_flag |= proximity16_write_byte ( ctx, 0x0C, 0x01 );
    
    /* Reset MCU and wait boot */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0114, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0115, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0116, 0x42 );
    error_flag |= proximity16_write_byte ( ctx, 0x0117, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0B, 0x00 );
    error_flag |= proximity16_read_byte ( ctx, 0x7FFF, &tmp );
    error_flag |= proximity16_write_byte ( ctx, 0x0C, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x0B, 0x01 );
    error_flag |= proximity16_poll_for_mcu_boot ( ctx );
    if ( PROXIMITY16_OK != error_flag )
    {
        return error_flag;
    }
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x02 );
    
    /* Get offset NVM data and store them into the offset buffer */
    error_flag |= proximity16_write_data ( ctx, ( uint8_t * ) proximity16_get_nvm_cmd_buf, 
                                           sizeof ( proximity16_get_nvm_cmd_buf ) );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 0, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x02 );
    error_flag |= proximity16_read_multi ( ctx, PROXIMITY16_UI_CMD_START, ctx->temp_buf, PROXIMITY16_NVM_DATA_SIZE );
    memcpy ( ctx->offset_data, ctx->temp_buf, PROXIMITY16_OFFSET_BUFFER_SIZE );
    
    /* Send default configuration to VL53L5CX firmware */
    error_flag |= proximity16_write_data ( ctx, ( uint8_t * ) proximity16_default_cfg_buf,
                                           sizeof ( proximity16_default_cfg_buf ) );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 1, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x03 );

    uint8_t pipe_ctrl[ ] = { 0x01, 0x00, 0x01, 0x00 };
    uint8_t single_range[ ] = { 0x01, 0x00, 0x00, 0x00 };
    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_PIPE_CONTROL, pipe_ctrl, sizeof ( pipe_ctrl ) );
    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_SINGLE_RANGE, single_range, sizeof ( single_range ) );
    return error_flag;
}

err_t proximity16_dci_write_data ( proximity16_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size )
{
    err_t error_flag = PROXIMITY16_OK;
    uint8_t headers[ ] = { 0x00, 0x00, 0x00, 0x00 };
    uint8_t footer[ ] = { 0x00, 0x00, 0x00, 0x0F, 0x05, 0x01,
                         ( uint8_t ) ( ( ( data_size + 8 ) >> 8 ) & 0xFF ), 
                         ( uint8_t ) ( ( data_size + 8 ) & 0xFF ) };
    uint16_t address = PROXIMITY16_UI_CMD_END - ( data_size + 12 ) + 1;

    /* Check if cmd buffer is large enough */
    if ( ( data_size + 12 ) > PROXIMITY16_TEMP_BUFFER_SIZE )
    {
        return PROXIMITY16_ERROR;
    }
    headers[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    headers[ 1 ] = ( uint8_t ) ( index & 0xFF );
    headers[ 2 ] = ( uint8_t ) ( ( data_size >> 4 ) & 0xFF );
    headers[ 3 ] = ( uint8_t ) ( ( data_size & 0x0F ) << 4 );

    /* Copy data from structure to FW format (+4 bytes to add header) */
    proximity16_swap_buffer ( data_in, data_size );
    for ( uint16_t cnt = data_size; cnt > 0; cnt-- )
    {
        ctx->temp_buf[ cnt + 3 ] = data_in [ cnt - 1 ];
    }

    /* Add headers and footer */
    memcpy ( &ctx->temp_buf[ 0 ], headers, sizeof ( headers ) );
    memcpy ( &ctx->temp_buf[ data_size + 4 ], footer, sizeof ( footer ) );

    /* Send data to FW */
    memmove ( &ctx->temp_buf[ 2 ], &ctx->temp_buf[ 0 ], ( data_size + 12 ) );
    ctx->temp_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF ); // address msb
    ctx->temp_buf[ 1 ] = ( uint8_t ) ( address & 0xFF ); // address lsb
    error_flag |= proximity16_write_data ( ctx, ctx->temp_buf, ( data_size + 14 ) );
    memmove ( &ctx->temp_buf[ 0 ], &ctx->temp_buf[ 2 ], ( data_size + 12 ) );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 1, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x03 );
    
    proximity16_swap_buffer ( data_in, data_size );
    return error_flag;
}

err_t proximity16_dci_read_data ( proximity16_t *ctx, uint16_t index, uint8_t *data_out, uint16_t data_size )
{
    err_t error_flag = PROXIMITY16_OK;
    uint8_t cmd[ ] = { 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x0F,
                       0x00, 0x02, 0x00, 0x08 };

    /* Check if tmp buffer is large enough */
    if ( ( data_size + 12 ) > PROXIMITY16_TEMP_BUFFER_SIZE )
    {
        return PROXIMITY16_ERROR;
    }
    
    cmd[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    cmd[ 1 ] = ( uint8_t ) ( index & 0xFF );
    cmd[ 2 ] = ( uint8_t ) ( ( data_size >> 4 ) & 0xFF );
    cmd[ 3 ] = ( uint8_t ) ( ( data_size & 0x0F ) << 4 );

    /* Request data reading from FW */
    error_flag |= proximity16_write_multi ( ctx, ( PROXIMITY16_UI_CMD_END - 11 ), cmd, sizeof ( cmd ) );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 1, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x03 );

    /* Read new data sent (4 bytes header + data_size + 8 bytes footer) */
    error_flag |= proximity16_read_multi ( ctx, PROXIMITY16_UI_CMD_START, ctx->temp_buf, ( data_size + 12 ) );
    proximity16_swap_buffer ( ctx->temp_buf, ( data_size + 12 ) );

    /* Copy data from FW into input structure (-4 bytes to remove header) */
    for ( uint16_t cnt = 0; cnt < data_size; cnt++ )
    {
        data_out[ cnt ] = ctx->temp_buf[ cnt + 4 ];
    }
    return error_flag;
}

err_t proximity16_dci_replace_data ( proximity16_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size, 
                                     uint8_t *new_data, uint16_t new_data_size, uint16_t new_data_pos )
{
    err_t error_flag = PROXIMITY16_OK;
    error_flag |= proximity16_dci_read_data ( ctx, index, data_in, data_size );
    memcpy ( &data_in[ new_data_pos ], new_data, new_data_size );
    error_flag |= proximity16_dci_write_data ( ctx, index, data_in, data_size );
    return error_flag;
}

err_t proximity16_set_resolution ( proximity16_t *ctx, uint8_t resolution )
{
    err_t error_flag = PROXIMITY16_OK;
    switch ( resolution )
    {
        case PROXIMITY16_RESOLUTION_4X4:
        {
            error_flag |= proximity16_dci_read_data( ctx, PROXIMITY16_DCI_DSS_CONFIG, 
                                                     ctx->temp_buf, 16 );
            ctx->temp_buf[ 0x04 ] = 64;
            ctx->temp_buf[ 0x06 ] = 64;
            ctx->temp_buf[ 0x09 ] = 4;
            error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_DSS_CONFIG, 
                                                       ctx->temp_buf, 16 );
            error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_ZONE_CONFIG, 
                                                      ctx->temp_buf, 8 );
            ctx->temp_buf[ 0x00 ] = 4;
            ctx->temp_buf[ 0x01 ] = 4;
            ctx->temp_buf[ 0x04 ] = 8;
            ctx->temp_buf[ 0x05 ] = 8;
            error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_ZONE_CONFIG, 
                                                       ctx->temp_buf, 8 );
            break;
        }
        case PROXIMITY16_RESOLUTION_8X8:
        {
            error_flag |= proximity16_dci_read_data( ctx, PROXIMITY16_DCI_DSS_CONFIG, 
                                                     ctx->temp_buf, 16 );
            ctx->temp_buf[ 0x04 ] = 16;
            ctx->temp_buf[ 0x06 ] = 16;
            ctx->temp_buf[ 0x09 ] = 1;
            error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_DSS_CONFIG, 
                                                       ctx->temp_buf, 16 );

            error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_ZONE_CONFIG, 
                                                      ctx->temp_buf, 8 );
            ctx->temp_buf[ 0x00 ] = 8;
            ctx->temp_buf[ 0x01 ] = 8;
            ctx->temp_buf[ 0x04 ] = 4;
            ctx->temp_buf[ 0x05 ] = 4;
            error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_ZONE_CONFIG, 
                                                       ctx->temp_buf, 8 );
            break;
        }
        default:
        {
            return PROXIMITY16_ERROR;
        }
    }
    error_flag |= proximity16_send_offset_data ( ctx, resolution );
    error_flag |= proximity16_send_xtalk_data ( ctx, resolution );
    return error_flag;
}

err_t proximity16_get_resolution ( proximity16_t *ctx, uint8_t *resolution )
{
    err_t error_flag = PROXIMITY16_OK;
    error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_ZONE_CONFIG, ctx->temp_buf, 8 );
    *resolution = ctx->temp_buf[ 0x00 ] * ctx->temp_buf[ 0x01 ];
    return error_flag;
}

err_t proximity16_set_ranging_frequency_hz ( proximity16_t *ctx, uint8_t frequency_hz )
{
    return proximity16_dci_replace_data ( ctx, PROXIMITY16_DCI_FREQ_HZ, ctx->temp_buf, 4, &frequency_hz, 1, 1 );
}

err_t proximity16_get_ranging_frequency_hz ( proximity16_t *ctx, uint8_t *frequency_hz )
{
    err_t error_flag = PROXIMITY16_OK;
    error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_FREQ_HZ, ctx->temp_buf, 4 );
    *frequency_hz = ctx->temp_buf[ 0x01 ];
    return error_flag;
}

err_t proximity16_set_integration_time_ms ( proximity16_t *ctx, uint32_t integration_time_ms )
{
    uint32_t integration = integration_time_ms;
    /* Integration time must be between 2ms and 1000ms */
    if ( ( integration < 2 ) || ( integration > 1000 ) )
    {
        return PROXIMITY16_ERROR;
    }
    integration *= 1000;
    return proximity16_dci_replace_data ( ctx, PROXIMITY16_DCI_INT_TIME, ctx->temp_buf, 20, 
                                          ( uint8_t * ) &integration, 4, 0x00 );
}

err_t proximity16_get_integration_time_ms ( proximity16_t *ctx, uint32_t *integration_time_ms )
{
    err_t error_flag = PROXIMITY16_OK;
    error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_INT_TIME, ctx->temp_buf, 20 );
    memcpy ( integration_time_ms, ctx->temp_buf, 4 );
    *integration_time_ms /= 1000;
    return error_flag;
}

err_t proximity16_set_ranging_mode ( proximity16_t *ctx, uint8_t ranging_mode )
{
    err_t error_flag = PROXIMITY16_OK;
    uint8_t single_range[ ] = { 0x01, 0x00, 0x00, 0x00 };
    error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_RANGING_MODE, ctx->temp_buf, 8 );
    switch ( ranging_mode )
    {
        case PROXIMITY16_RANGING_MODE_CONTINUOUS:
        {
            ctx->temp_buf[ 0x01 ] = 0x1;
            ctx->temp_buf[ 0x03 ] = 0x3;
            single_range[ 0x00 ] = 0x00;
            break;
        }
        case PROXIMITY16_RANGING_MODE_AUTONOMOUS:
        {
            ctx->temp_buf[ 0x01 ] = 0x3;
            ctx->temp_buf[ 0x03 ] = 0x2;
            single_range[ 0x00 ] = 0x01;
            break;
        }
        default:
        {
            return PROXIMITY16_ERROR;
        }
    }
    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_RANGING_MODE, ctx->temp_buf, 8 );
    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_SINGLE_RANGE, single_range, sizeof ( single_range ) );
    return error_flag;
}

err_t proximity16_get_ranging_mode ( proximity16_t *ctx, uint8_t *ranging_mode )
{
    err_t error_flag = PROXIMITY16_OK;
    error_flag |= proximity16_dci_read_data ( ctx, PROXIMITY16_DCI_RANGING_MODE, ctx->temp_buf, 8 );
    if ( PROXIMITY16_RANGING_MODE_CONTINUOUS == ctx->temp_buf[ 0x01 ] )
    {
        *ranging_mode = PROXIMITY16_RANGING_MODE_CONTINUOUS;
    }
    else
    {
        *ranging_mode = PROXIMITY16_RANGING_MODE_AUTONOMOUS;
    }
    return error_flag;
}

err_t proximity16_start_ranging ( proximity16_t *ctx )
{
    err_t error_flag = PROXIMITY16_OK;
    uint32_t header_config[ 2 ] = { 0, 0 };
    uint32_t cnt;
    uint16_t tmp;
    uint8_t resolution;
    volatile proximity16_block_header_t *bh_ptr;
    uint8_t cmd[ ] = { 0x00, 0x03, 0x00, 0x00 };

    error_flag |= proximity16_get_resolution ( ctx, &resolution );
    ctx->data_read_size = 0;
    ctx->stream_count = 255;

    /* Enable mandatory output (meta and common data) */
    uint32_t output_bh_enable[ ] = { 0x00000007ul, 0x00000000ul, 0x00000000ul, 0xC0000000ul };

    /* Send addresses of possible output */
    uint32_t output[ ] = 
    { 
        PROXIMITY16_START_BH, 
        PROXIMITY16_METADATA_BH,
        PROXIMITY16_COMMONDATA_BH,
        PROXIMITY16_AMBIENT_RATE_BH,
        PROXIMITY16_SPAD_COUNT_BH,
        PROXIMITY16_NB_TARGET_DETECTED_BH,
        PROXIMITY16_SIGNAL_RATE_BH,
        PROXIMITY16_RANGE_SIGMA_MM_BH,
        PROXIMITY16_DISTANCE_BH,
        PROXIMITY16_REFLECTANCE_BH,
        PROXIMITY16_TARGET_STATUS_BH,
        PROXIMITY16_MOTION_DETECT_BH
    };

    output_bh_enable[ 0 ] += 32; // nb target detected
    output_bh_enable[ 0 ] += 256; // distance mm
    output_bh_enable[ 0 ] += 1024; // target status

    /* Update data size */
    for ( cnt = 0; cnt < ( sizeof ( output ) / 4 ); cnt++ )
    {
        if ( ( 0 == output[ cnt ] ) || ( 0 == ( output_bh_enable[ cnt / 32 ] & ( 1ul << ( cnt % 32 ) ) ) ) )
        {
            continue;
        }
        bh_ptr = ( proximity16_block_header_t * ) &output[ cnt ];
        if ( ( ( uint8_t ) bh_ptr->type >= 0x01 ) && ( ( uint8_t ) bh_ptr->type < 0x0D ) )
        {
            bh_ptr->size = resolution;
            ctx->data_read_size += ( bh_ptr->type * bh_ptr->size );
        }
        else
        {
            ctx->data_read_size += bh_ptr->size;
        }
        ctx->data_read_size += 4;
    }
    ctx->data_read_size += 24;

    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_OUTPUT_LIST, 
                                               ( uint8_t * ) &output[ 0 ], sizeof ( output ) );

    header_config[ 0 ] = ctx->data_read_size;
    header_config[ 1 ] = cnt + 1;

    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_OUTPUT_CONFIG,
                                               ( uint8_t * ) &header_config[ 0 ], sizeof ( header_config ) );

    error_flag |= proximity16_dci_write_data ( ctx, PROXIMITY16_DCI_OUTPUT_ENABLES,
                                               ( uint8_t * ) &output_bh_enable[ 0 ], sizeof ( output_bh_enable ) );

    /* Start xshut bypass (interrupt mode) */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x09, 0x05 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x02 );

    /* Start ranging session */
    error_flag |= proximity16_write_multi ( ctx, ( PROXIMITY16_UI_CMD_END - 3 ), cmd, 4 );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 1, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x03 );

    /* Read ui range data content and compare if data size is the correct one */
    error_flag |= proximity16_dci_read_data ( ctx, 0x5440, ctx->temp_buf, 12 );
    memcpy ( &tmp, &ctx->temp_buf[ 0x08 ], sizeof ( tmp ) );
    if ( tmp != ctx->data_read_size )
    {
        return PROXIMITY16_ERROR;
    }
    return error_flag;
}

err_t proximity16_stop_ranging ( proximity16_t *ctx )
{
    err_t error_flag = PROXIMITY16_OK;
    uint32_t auto_stop_flag = 0;
    uint16_t timeout = 0;
    uint8_t tmp = 0;

    error_flag |= proximity16_read_multi ( ctx, 0x2FFC, ( uint8_t * ) &auto_stop_flag, 4 );
    if ( 0x04FF != auto_stop_flag )
    {
        error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );

        /* Provoke MCU stop */
        error_flag |= proximity16_write_byte ( ctx, 0x15, 0x16 );
        error_flag |= proximity16_write_byte ( ctx, 0x14, 0x01 );

        /* Poll for G02 status 0 MCU stop */
        while ( 0x00 == ( ( tmp & 0x80 ) >> 7 ) )
        {
            error_flag |= proximity16_read_byte ( ctx, 0x06, &tmp );
            Delay_10ms ( );
            /* Timeout reached after 5 seconds */
            if ( timeout++ > 500 )
            {
                error_flag |= tmp;
                break;
            }
        }
    }

    /* Check GO2 status 1 if status is still OK */
    error_flag |= proximity16_read_byte ( ctx, 0x06, &tmp );
    if ( tmp & 0x80 )
    {
        error_flag |= proximity16_read_byte ( ctx, 0x07, &tmp );
        if ( ( tmp != 0x84 ) && ( tmp != 0x85 ) )
        {
            error_flag |= tmp;
        }
    }

    /* Undo MCU stop */
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x14, 0x00 );
    error_flag |= proximity16_write_byte ( ctx, 0x15, 0x00 );

    /* Stop xshut bypass */
    error_flag |= proximity16_write_byte ( ctx, 0x09, 0x04 );
    error_flag |= proximity16_write_byte ( ctx, 0x7FFF, 0x02 );
    return error_flag;
}

err_t proximity16_get_ranging_data ( proximity16_t *ctx, proximity16_results_data_t *results )
{
    err_t error_flag = PROXIMITY16_OK;
    volatile proximity16_block_header_t *bh_ptr;
    uint16_t header_id, footer_id;
    uint32_t cnt, msize;

    error_flag |= proximity16_read_multi ( ctx, 0x00, ctx->temp_buf, ctx->data_read_size );
    ctx->stream_count = ctx->temp_buf[ 0 ];
    proximity16_swap_buffer ( ctx->temp_buf, ctx->data_read_size );

    /* Start conversion at position 16 to avoid headers */
    for ( cnt = 16; cnt < ctx->data_read_size; cnt += 4 )
    {
        bh_ptr = ( proximity16_block_header_t * ) &ctx->temp_buf[ cnt ];
        if ( ( bh_ptr->type > 0x01 ) && ( bh_ptr->type < 0x0D ) )
        {
            msize = bh_ptr->type * bh_ptr->size;
        }
        else
        {
            msize = bh_ptr->size;
        }

        switch ( bh_ptr->idx )
        {
            case PROXIMITY16_METADATA_IDX:
            {
                results->silicon_temp_degc = ( int8_t ) ctx->temp_buf[ cnt + 12 ];
                break;
            }
            case PROXIMITY16_NB_TARGET_DETECTED_IDX:
            {
                memcpy ( results->nb_target_detected, &ctx->temp_buf[ cnt + 4 ], msize );
                break;
            }
            case PROXIMITY16_DISTANCE_IDX:
            {
                memcpy ( results->distance_mm, &ctx->temp_buf[ cnt + 4 ], msize );
                break;
            }
            case PROXIMITY16_TARGET_STATUS_IDX:
            {
                memcpy ( results->target_status, &ctx->temp_buf[ cnt + 4 ], msize );
                break;
            }
            default:
            {
                break;
            }
        }
        cnt += msize;
    }

    for ( cnt = 0; cnt < PROXIMITY16_RESOLUTION_8X8; cnt++ )
    {
        results->distance_mm[ cnt ] /= 4;
        if ( results->distance_mm[ cnt ] < 0 )
        {
            results->distance_mm[ cnt ] = 0;
        }
    }

    /* Set target status to 255 if no target is detected for this zone */
    for ( cnt = 0; cnt < PROXIMITY16_RESOLUTION_8X8; cnt++ )
    {
        if ( 0 == results->nb_target_detected[ cnt ] )
        {
            results->target_status[ cnt ] = 255;
        }
    }

    /* Check if footer id and header id are matching. This allows to detect corrupted frames */
    header_id = ( uint16_t ) ( ( uint16_t ) ctx->temp_buf[ 0x08 ] << 8 ) | ctx->temp_buf[ 0x09 ];
    footer_id = ( uint16_t ) ( ( uint16_t ) ctx->temp_buf[ ctx->data_read_size - 4 ] << 8 ) | 
                             ctx->temp_buf[ ctx->data_read_size - 3 ];
    if ( header_id != footer_id )
    {
        return PROXIMITY16_ERROR;
    }
    return error_flag;
}

static void proximity16_swap_buffer ( uint8_t *buffer, uint16_t size )
{
    for ( uint16_t cnt = 0; cnt < size; cnt = cnt + 4 )
    {
        uint32_t tmp = ( ( uint32_t ) buffer[ cnt ] << 24 ) | ( ( uint32_t ) buffer[ cnt + 1 ] << 16 ) | 
                       ( ( uint16_t ) buffer[ cnt + 2 ] << 8 ) | buffer[ cnt + 3 ];
        memcpy ( &buffer[ cnt ], &tmp, 4 );
    }
}

static err_t proximity16_poll_for_answer ( proximity16_t *ctx, uint8_t size, uint8_t pos,
                                           uint16_t address, uint8_t mask, uint8_t expected_value )
{
    err_t error_flag = PROXIMITY16_OK;
    uint8_t timeout = 0;
    do 
    {
        error_flag |= proximity16_read_multi ( ctx, address, ctx->temp_buf, size );
        Delay_10ms ( );
        if ( ( timeout++ >= 200 ) || /* 2s timeout */ 
             ( ( size >= 4 ) && ( ctx->temp_buf[ 2 ] >= 0x7F ) ) )   
        {
            return PROXIMITY16_ERROR;
        }
    } 
    while ( ( ctx->temp_buf[ pos ] & mask ) != expected_value );

    return error_flag;
}

static err_t proximity16_poll_for_mcu_boot ( proximity16_t *ctx )
{
   err_t error_flag = PROXIMITY16_OK;
   uint16_t timeout = 0;
   uint8_t go2_status0, go2_status1; 
   do 
   {
        error_flag |= proximity16_read_byte ( ctx, 0x06, &go2_status0 );
        if ( go2_status0 & 0x80 )
        {
            error_flag |= proximity16_read_byte ( ctx, 0x07, &go2_status1 );
            error_flag |= go2_status1;
            return error_flag;
        }
        Delay_1ms ( );
        if ( go2_status0 & 0x01 )
        {
            return error_flag;
        }
    }
    while ( timeout++ < 500 );

    return PROXIMITY16_ERROR;
}

static err_t proximity16_send_offset_data ( proximity16_t *ctx, uint8_t resolution )
{
    err_t error_flag = PROXIMITY16_OK;
    uint32_t signal_grid[ 64 ];
    int16_t range_grid[ 64 ];
    uint8_t dss_4x4[ ] = { 0x0F, 0x04, 0x04, 0x00, 0x08, 0x10, 0x10, 0x07 };
    uint8_t footer[ ] = { 0x00, 0x00, 0x00, 0x0F, 0x03, 0x01, 0x01, 0xE4 };

    memcpy ( ctx->temp_buf, ctx->offset_data, PROXIMITY16_OFFSET_BUFFER_SIZE );

    /* Data extrapolation is required for 4X4 offset */
    if ( PROXIMITY16_RESOLUTION_4X4 == resolution )
    {
        memcpy ( &ctx->temp_buf[ 0x10 ], dss_4x4, sizeof ( dss_4x4 ) );
        proximity16_swap_buffer ( ctx->temp_buf, PROXIMITY16_OFFSET_BUFFER_SIZE );
        memcpy ( signal_grid, &ctx->temp_buf[ 0x3C ], sizeof ( signal_grid ) );
        memcpy ( range_grid, &ctx->temp_buf[ 0x0140 ], sizeof ( range_grid ) );

        for ( uint8_t cnt_0 = 0; cnt_0 < 4; cnt_0++ )
        {
            for ( uint8_t cnt_1 = 0; cnt_1 < 4; cnt_1++ )
            {
                signal_grid [ cnt_1 + ( 4 * cnt_0 ) ] = ( signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 1 ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 8 ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 9 ] ) / 4;
                range_grid [ cnt_1 + ( 4 * cnt_0 ) ] = ( range_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) ] + 
                                                         range_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 1 ] + 
                                                         range_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 8 ] + 
                                                         range_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 9 ] ) / 4;
            }
        }
        memset ( &range_grid[ 0x10 ], 0, 96 );
        memset ( &signal_grid[ 0x10 ], 0, 192 );
        memcpy ( &ctx->temp_buf[ 0x3C ], signal_grid, sizeof ( signal_grid ) );
        memcpy ( &ctx->temp_buf[ 0x0140 ], range_grid, sizeof ( range_grid ) );
        proximity16_swap_buffer ( ctx->temp_buf, PROXIMITY16_OFFSET_BUFFER_SIZE );
    }
    for ( uint16_t cnt = 0; cnt < ( PROXIMITY16_OFFSET_BUFFER_SIZE - 4 ); cnt++ )
    {
        ctx->temp_buf[ cnt ] = ctx->temp_buf[ cnt + 8 ];
    }
    memcpy ( &ctx->temp_buf[ 0x01E0 ], footer, 8 );
    memmove ( &ctx->temp_buf[ 2 ], &ctx->temp_buf[ 0 ], PROXIMITY16_OFFSET_BUFFER_SIZE );
    ctx->temp_buf[ 0 ] = 0x2E; // address msb
    ctx->temp_buf[ 1 ] = 0x18; // address lsb
    error_flag |= proximity16_write_data ( ctx, ctx->temp_buf, PROXIMITY16_OFFSET_BUFFER_SIZE + 2 );
    memmove ( &ctx->temp_buf[ 0 ], &ctx->temp_buf[ 2 ], PROXIMITY16_OFFSET_BUFFER_SIZE );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 1, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x03 );
    return error_flag;
}

static err_t proximity16_send_xtalk_data ( proximity16_t *ctx, uint8_t resolution )
{
    err_t error_flag = PROXIMITY16_OK;
    uint8_t res4x4[ ] = { 0x0F, 0x04, 0x04, 0x17, 0x08, 0x10, 0x10, 0x07 };
    uint8_t dss_4x4[ ] = { 0x00, 0x78, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08 };
    uint8_t profile_4x4[ ] = { 0xA0, 0xFC, 0x01, 0x00 };
    uint32_t signal_grid[ 64 ];

    memcpy ( ctx->temp_buf, ( uint8_t * ) proximity16_default_xtalk_buf, 
             sizeof ( proximity16_default_xtalk_buf ) );

    /* Data extrapolation is required for 4X4 Xtalk */
    if ( PROXIMITY16_RESOLUTION_4X4 == resolution )
    {
        memcpy ( &ctx->temp_buf[ 0x08 ], res4x4, sizeof ( res4x4 ) );
        memcpy ( &ctx->temp_buf[ 0x20 ], dss_4x4, sizeof ( dss_4x4 ) );

        proximity16_swap_buffer ( ctx->temp_buf, PROXIMITY16_XTALK_BUFFER_SIZE );
        memcpy ( signal_grid, &ctx->temp_buf[ 0x34 ], sizeof ( signal_grid ) );

        for ( uint8_t cnt_0 = 0; cnt_0 < 4; cnt_0++ )
        {
            for ( uint8_t cnt_1 = 0; cnt_1 < 4; cnt_1++ )
            {
                signal_grid [ cnt_1 + ( 4 * cnt_0 ) ] = ( signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 1 ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 8 ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 9 ] ) / 4;
            }
        }
        memset( &signal_grid[ 0x10 ], 0, 192 );
        memcpy ( &ctx->temp_buf[ 0x34 ], signal_grid, sizeof ( signal_grid ) );
        proximity16_swap_buffer ( ctx->temp_buf, PROXIMITY16_XTALK_BUFFER_SIZE );
        memcpy ( &ctx->temp_buf[ 0x0134 ], profile_4x4, sizeof ( profile_4x4 ) );
        memset ( &ctx->temp_buf[ 0x78 ], 0, 4 );
    }

    memmove ( &ctx->temp_buf[ 2 ], &ctx->temp_buf[ 0 ], PROXIMITY16_XTALK_BUFFER_SIZE );
    ctx->temp_buf[ 0 ] = 0x2C; // address msb
    ctx->temp_buf[ 1 ] = 0xF8; // address lsb
    error_flag |= proximity16_write_data ( ctx, ctx->temp_buf, PROXIMITY16_XTALK_BUFFER_SIZE + 2 );
    memmove ( &ctx->temp_buf[ 0 ], &ctx->temp_buf[ 2 ], PROXIMITY16_XTALK_BUFFER_SIZE );
    error_flag |= proximity16_poll_for_answer ( ctx, 4, 1, PROXIMITY16_UI_CMD_STATUS, 0xFF, 0x03 );
    return error_flag;
}

// ------------------------------------------------------------------------- END

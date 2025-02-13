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
 * @file lightranger12.c
 * @brief LightRanger 12 Click Driver.
 */

#include "lightranger12.h"
#include "firmware_buffers.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_WRITE_MASK    0x80

/**
 * @brief LightRanger 12 swap buffer function.
 * @details This function swaps a buffer. The buffer size is always a multiple of 4 (4, 8, 12, 16, ...).
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in,out] buffer : Buffer to swap, generally uint32_t.
 * @param[in] size : Buffer size to swap.
 * @return None.
 * @note None.
 */
static void lightranger12_swap_buffer ( uint8_t *buffer, uint16_t size );

/**
 * @brief LightRanger 12 poll for answer function.
 * @details This function waits for an answer from the sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
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
static err_t lightranger12_poll_for_answer ( lightranger12_t *ctx, uint8_t size, uint8_t pos,
                                             uint16_t address, uint8_t mask, uint8_t expected_value );

/**
 * @brief LightRanger 12 poll for mcu boot function.
 * @details This function waits for the sensor MCU to boot.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_poll_for_mcu_boot ( lightranger12_t *ctx );

/**
 * @brief LightRanger 12 send offset data function.
 * @details This function sets the offset data gathered from NVM for the selected resolution
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] resolution : Use macro LIGHTRANGER12_RESOLUTION_4X4 or LIGHTRANGER12_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_send_offset_data ( lightranger12_t *ctx, uint8_t resolution );

/**
 * @brief LightRanger 12 send xtalk data function.
 * @details This function sets the Xtalk data from generic configuration, or user's calibration for the selected resolution.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] resolution : Use macro LIGHTRANGER12_RESOLUTION_4X4 or LIGHTRANGER12_RESOLUTION_8X8 to set the resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_send_xtalk_data ( lightranger12_t *ctx, uint8_t resolution );

/**
 * @brief LightRanger 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_i2c_write ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief LightRanger 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_i2c_read ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief LightRanger 12 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_spi_write ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief LightRanger 12 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger12_spi_read ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

void lightranger12_cfg_setup ( lightranger12_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->sync = HAL_PIN_NC;
    cfg->lpn  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = LIGHTRANGER12_DEVICE_ADDRESS;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = LIGHTRANGER12_DRV_SEL_I2C;
}

void lightranger12_drv_interface_sel ( lightranger12_cfg_t *cfg, lightranger12_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t lightranger12_init ( lightranger12_t *ctx, lightranger12_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    digital_out_init( &ctx->sync, cfg->sync );
    digital_out_init( &ctx->lpn, cfg->lpn );
    digital_out_low ( &ctx->sync );
    digital_out_low ( &ctx->lpn );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_100ms ( );

    lightranger12_enable_i2c ( ctx );
    Delay_100ms ( );

    if ( LIGHTRANGER12_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = lightranger12_i2c_read;
        ctx->write_f = lightranger12_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = lightranger12_spi_read;
        ctx->write_f = lightranger12_spi_write;
    }

    return LIGHTRANGER12_OK;
}

err_t lightranger12_default_cfg ( lightranger12_t *ctx ) 
{
    err_t error_flag = LIGHTRANGER12_OK;
    if ( LIGHTRANGER12_ERROR == lightranger12_check_comm ( ctx ) )
    {
        return LIGHTRANGER12_ERROR;
    }
    error_flag |= lightranger12_sensor_init ( ctx );
    error_flag |= lightranger12_set_resolution ( ctx, LIGHTRANGER12_DEF_RESOLUTION );
    error_flag |= lightranger12_set_ranging_freq ( ctx, LIGHTRANGER12_DEF_RANGING_FREQ_HZ );
    error_flag |= lightranger12_set_ranging_mode ( ctx, LIGHTRANGER12_DEF_RANGING_MODE );
    error_flag |= lightranger12_set_int_time ( ctx, LIGHTRANGER12_DEF_INTEGRATION_TIME_MS );
    error_flag |= lightranger12_start_ranging ( ctx );
    Delay_1sec ( );
    return error_flag;
}

err_t lightranger12_write_multi ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t lightranger12_read_multi ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t lightranger12_write_byte ( lightranger12_t *ctx, uint16_t reg, uint8_t data_in )
{
    return lightranger12_write_multi ( ctx, reg, &data_in, 1 );
}

err_t lightranger12_read_byte ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out )
{
    return lightranger12_read_multi ( ctx, reg, data_out, 1 );
}

err_t lightranger12_write_data ( lightranger12_t *ctx, uint8_t *data_in, uint16_t len )
{
    return lightranger12_write_multi ( ctx, 0xFFFF, data_in, len );
}

void lightranger12_disable_i2c ( lightranger12_t *ctx )
{
    digital_out_low ( &ctx->lpn );
}

void lightranger12_enable_i2c ( lightranger12_t *ctx )
{
    digital_out_high ( &ctx->lpn );
}

void lightranger12_set_sync_pin ( lightranger12_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sync, state );
}

uint8_t lightranger12_get_int_pin ( lightranger12_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t lightranger12_check_comm ( lightranger12_t *ctx )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_read_multi ( ctx, 0x0000, data_buf, 2 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x02 );
    if ( ( LIGHTRANGER12_OK == error_flag ) && 
         ( LIGHTRANGER12_DEVICE_ID == data_buf[ 0 ] ) && 
         ( LIGHTRANGER12_REVISION_ID_L8 == data_buf[ 1 ] ) )
    {
        return LIGHTRANGER12_OK;
    }
    return LIGHTRANGER12_ERROR;
}

err_t lightranger12_set_i2c_address ( lightranger12_t *ctx, uint8_t i2c_address )
{
    err_t error_flag = LIGHTRANGER12_OK;
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0004, i2c_address );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x02 );
    if ( ( LIGHTRANGER12_DRV_SEL_I2C == ctx->drv_sel ) && ( LIGHTRANGER12_OK == error_flag ) ) 
    {
        ctx->slave_address = i2c_address;
        error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return error_flag;
}

err_t lightranger12_sensor_init ( lightranger12_t *ctx )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t pipe_ctrl[ ] = { 0x01, 0x00, 0x01, 0x00 };
    uint8_t single_range[ ] = { 0x01, 0x00, 0x00, 0x00 };
    uint8_t reg_data = 0;
    
    // SW reboot sequence
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0009, 0x04 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000F, 0x40 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000A, 0x03 );
    error_flag |= lightranger12_read_byte ( ctx, 0x7FFF, &reg_data  );
    error_flag |= lightranger12_write_byte ( ctx, 0x000C, 0x01 );

    error_flag |= lightranger12_write_byte ( ctx, 0x0101, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0102, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x010A, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x4002, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x4002, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x010A, 0x03 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0103, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000C, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000F, 0x43 );
    Delay_1ms ( );

    error_flag |= lightranger12_write_byte ( ctx, 0x000F, 0x40 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000A, 0x01 );
    Delay_100ms ( );
    
    // Wait for sensor booted (several ms required to get sensor ready)
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_poll_for_answer ( ctx, 1, 0, 0x0006, 0xFF, 0x01 );
    if ( LIGHTRANGER12_OK != error_flag )
    {
        return error_flag;
    }
    error_flag |= lightranger12_write_byte ( ctx, 0x000E, 0x01 );

    // Enable FW access
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0006, 0x01 );
    error_flag |= lightranger12_poll_for_answer ( ctx, 1, 0, 0x0021, 0xFF, 0x04 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );

    // Enable host access to GO1
    error_flag |= lightranger12_read_byte ( ctx, 0x7FFF, &reg_data );
    error_flag |= lightranger12_write_byte ( ctx, 0x000C, 0x01 );

    // Power ON status
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0101, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0102, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x010A, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x4002, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x4002, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x010A, 0x03 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0103, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x400F, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x021A, 0x43 );
    error_flag |= lightranger12_write_byte ( ctx, 0x021A, 0x03 );
    error_flag |= lightranger12_write_byte ( ctx, 0x021A, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x021A, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0219, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x021B, 0x00 );

    // Wake up MCU
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_read_byte ( ctx, 0x7FFF, &reg_data );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0020, 0x07 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0020, 0x06 );

    // Download FW into VL53LMZ, address word is added at the beginning of each buffer block
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x09 );
    error_flag |= lightranger12_write_data ( ctx, ( uint8_t * ) &lightranger12_firmware_buf[ 0 ], 0x8002 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x0A );
    error_flag |= lightranger12_write_data ( ctx, ( uint8_t * ) &lightranger12_firmware_buf[ 0x8002 ], 0x8002 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x0B );
    error_flag |= lightranger12_write_data ( ctx, ( uint8_t * ) &lightranger12_firmware_buf[ 0x10004 ], 0x5002 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x01 );

    // Check if FW is correctly downloaded
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x01 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0006, 0x03 );
    if ( LIGHTRANGER12_OK != error_flag )
    {
        return error_flag;
    }
    Delay_10ms ( );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_read_byte ( ctx, 0x7FFF, &reg_data );
    error_flag |= lightranger12_write_byte ( ctx, 0x000C, 0x01 );
    
    // Reset MCU and wait boot
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0114, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0115, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0116, 0x42 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0117, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000B, 0x00 );
    error_flag |= lightranger12_read_byte ( ctx, 0x7FFF, &reg_data );
    error_flag |= lightranger12_write_byte ( ctx, 0x000C, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x000B, 0x01 );
    error_flag |= lightranger12_poll_for_mcu_boot ( ctx );
    if ( LIGHTRANGER12_OK != error_flag )
    {
        return error_flag;
    }
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x02 );
    
    // Get offset NVM data and store them into the offset buffer
    error_flag |= lightranger12_write_data ( ctx, ( uint8_t * ) &lightranger12_get_nvm_cmd_buf[ 0 ], 
                                             sizeof ( lightranger12_get_nvm_cmd_buf ) );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 0, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x02 );
    error_flag |= lightranger12_read_multi ( ctx, LIGHTRANGER12_UI_CMD_START, ctx->temp_buf, LIGHTRANGER12_NVM_DATA_SIZE );
    memcpy ( ctx->offset_data, ctx->temp_buf, LIGHTRANGER12_OFFSET_BUFFER_SIZE );
    error_flag |= lightranger12_send_offset_data ( ctx, LIGHTRANGER12_DEF_RESOLUTION );

    // Set default XTALK shape
    error_flag |= lightranger12_send_xtalk_data ( ctx, LIGHTRANGER12_DEF_RESOLUTION );
    
    // Send default configuration to sensor firmware
    error_flag |= lightranger12_write_data ( ctx, ( uint8_t * ) &lightranger12_default_cfg_buf[ 0 ],
                                             sizeof ( lightranger12_default_cfg_buf ) );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 1, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x03 );

    error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_PIPE_CONTROL, pipe_ctrl, sizeof ( pipe_ctrl ) );
    error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_SINGLE_RANGE, single_range, sizeof ( single_range ) );
    return error_flag;
}

err_t lightranger12_dci_write_data ( lightranger12_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t headers[ 4 ] = { 0 };
    uint8_t footer[ ] = { 0x00, 0x00, 0x00, 0x0F, 0x05, 0x01,
                         ( uint8_t ) ( ( ( data_size + 8 ) >> 8 ) & 0xFF ), 
                         ( uint8_t ) ( ( data_size + 8 ) & 0xFF ) };
    uint16_t address = LIGHTRANGER12_UI_CMD_END - ( data_size + 12 ) + 1;
    uint16_t cnt = 0;

    // Check if cmd buffer is oversized
    if ( ( data_size + 12 ) > LIGHTRANGER12_TEMP_BUFFER_SIZE )
    {
        return LIGHTRANGER12_ERROR;
    }
    headers[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    headers[ 1 ] = ( uint8_t ) ( index & 0xFF );
    headers[ 2 ] = ( uint8_t ) ( ( data_size >> 4 ) & 0xFF );
    headers[ 3 ] = ( uint8_t ) ( ( data_size & 0x0F ) << 4 );

    // Copy data from structure to FW format (+4 bytes to add header)
    lightranger12_swap_buffer ( data_in, data_size );
    for ( cnt = data_size; cnt > 0; cnt-- )
    {
        ctx->temp_buf[ cnt + 3 ] = data_in [ cnt - 1 ];
    }

    // Add headers and footer
    memcpy ( &ctx->temp_buf[ 0 ], headers, sizeof ( headers ) );
    memcpy ( &ctx->temp_buf[ data_size + 4 ], footer, sizeof ( footer ) );

    // Send data to FW
    memmove ( &ctx->temp_buf[ 2 ], &ctx->temp_buf[ 0 ], ( data_size + 12 ) );
    ctx->temp_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF ); // address msb
    ctx->temp_buf[ 1 ] = ( uint8_t ) ( address & 0xFF ); // address lsb
    error_flag |= lightranger12_write_data ( ctx, ctx->temp_buf, ( data_size + 14 ) );
    memmove ( &ctx->temp_buf[ 0 ], &ctx->temp_buf[ 2 ], ( data_size + 12 ) );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 1, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x03 );
    
    lightranger12_swap_buffer ( data_in, data_size );
    return error_flag;
}

err_t lightranger12_dci_read_data ( lightranger12_t *ctx, uint16_t index, uint8_t *data_out, uint16_t data_size )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t cmd[ ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x02, 0x00, 0x08 };

    // Check if tmp buffer is large enough
    if ( ( data_size + 12 ) > LIGHTRANGER12_TEMP_BUFFER_SIZE )
    {
        return LIGHTRANGER12_ERROR;
    }
    
    cmd[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    cmd[ 1 ] = ( uint8_t ) ( index & 0xFF );
    cmd[ 2 ] = ( uint8_t ) ( ( data_size >> 4 ) & 0xFF );
    cmd[ 3 ] = ( uint8_t ) ( ( data_size & 0x0F ) << 4 );

    // Request data reading from FW
    error_flag |= lightranger12_write_multi ( ctx, ( LIGHTRANGER12_UI_CMD_END - 11 ), cmd, sizeof ( cmd ) );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 1, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x03 );

    // Read new data sent (4 bytes header + data_size + 8 bytes footer)
    error_flag |= lightranger12_read_multi ( ctx, LIGHTRANGER12_UI_CMD_START, ctx->temp_buf, ( data_size + 12 ) );
    lightranger12_swap_buffer ( ctx->temp_buf, ( data_size + 12 ) );

    // Copy data from FW into input structure (-4 bytes to remove header)
    for ( uint16_t cnt = 0; cnt < data_size; cnt++ )
    {
        data_out[ cnt ] = ctx->temp_buf[ cnt + 4 ];
    }
    return error_flag;
}

err_t lightranger12_dci_replace_data ( lightranger12_t *ctx, uint16_t index, uint8_t *data_in, uint16_t data_size, 
                                       uint8_t *new_data, uint16_t new_data_size, uint16_t new_data_pos )
{
    err_t error_flag = LIGHTRANGER12_OK;
    error_flag |= lightranger12_dci_read_data ( ctx, index, data_in, data_size );
    memcpy ( &data_in[ new_data_pos ], new_data, new_data_size );
    error_flag |= lightranger12_dci_write_data ( ctx, index, data_in, data_size );
    return error_flag;
}

err_t lightranger12_set_resolution ( lightranger12_t *ctx, uint8_t resolution )
{
    err_t error_flag = LIGHTRANGER12_OK;
    switch ( resolution )
    {
        case LIGHTRANGER12_RESOLUTION_4X4:
        {
            error_flag |= lightranger12_dci_read_data( ctx, LIGHTRANGER12_DCI_DSS_CONFIG, ctx->temp_buf, 16 );
            ctx->temp_buf[ 4 ] = 64;
            ctx->temp_buf[ 6 ] = 64;
            ctx->temp_buf[ 9 ] = 4;
            error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_DSS_CONFIG, ctx->temp_buf, 16 );
            error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_ZONE_CONFIG, ctx->temp_buf, 8 );
            ctx->temp_buf[ 0 ] = 4;
            ctx->temp_buf[ 1 ] = 4;
            ctx->temp_buf[ 4 ] = 8;
            ctx->temp_buf[ 5 ] = 8;
            error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_ZONE_CONFIG, ctx->temp_buf, 8 );
            break;
        }
        case LIGHTRANGER12_RESOLUTION_8X8:
        {
            error_flag |= lightranger12_dci_read_data( ctx, LIGHTRANGER12_DCI_DSS_CONFIG, ctx->temp_buf, 16 );
            ctx->temp_buf[ 4 ] = 16;
            ctx->temp_buf[ 6 ] = 16;
            ctx->temp_buf[ 9 ] = 1;
            error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_DSS_CONFIG, ctx->temp_buf, 16 );

            error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_ZONE_CONFIG, ctx->temp_buf, 8 );
            ctx->temp_buf[ 0 ] = 8;
            ctx->temp_buf[ 1 ] = 8;
            ctx->temp_buf[ 4 ] = 4;
            ctx->temp_buf[ 5 ] = 4;
            error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_ZONE_CONFIG, ctx->temp_buf, 8 );
            break;
        }
        default:
        {
            error_flag |= LIGHTRANGER12_ERROR;
            break;
        }
    }
    if ( LIGHTRANGER12_OK == error_flag )
    {
        error_flag |= lightranger12_send_offset_data ( ctx, resolution );
        error_flag |= lightranger12_send_xtalk_data ( ctx, resolution );
    }
    return error_flag;
}

err_t lightranger12_get_resolution ( lightranger12_t *ctx, uint8_t *resolution )
{
    err_t error_flag = LIGHTRANGER12_OK;
    error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_ZONE_CONFIG, ctx->temp_buf, 8 );
    *resolution = ctx->temp_buf[ 0 ] * ctx->temp_buf[ 1 ];
    return error_flag;
}

err_t lightranger12_set_ranging_freq ( lightranger12_t *ctx, uint8_t frequency_hz )
{
    return lightranger12_dci_replace_data ( ctx, LIGHTRANGER12_DCI_FREQ_HZ, ctx->temp_buf, 4, &frequency_hz, 1, 1 );
}

err_t lightranger12_get_ranging_freq ( lightranger12_t *ctx, uint8_t *frequency_hz )
{
    err_t error_flag = LIGHTRANGER12_OK;
    error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_FREQ_HZ, ctx->temp_buf, 4 );
    *frequency_hz = ctx->temp_buf[ 1 ];
    return error_flag;
}

err_t lightranger12_set_int_time ( lightranger12_t *ctx, uint32_t int_time_ms )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint32_t integration = int_time_ms;
    uint8_t data_buf[ 4 ] = { 0 };
    // Integration time must be between 2ms and 1000ms
    if ( ( integration < 2 ) || ( integration > 1000 ) )
    {
        error_flag |= LIGHTRANGER12_ERROR;
    }
    else
    {
        integration *= 1000;
        data_buf[ 0 ] = ( uint8_t ) ( integration & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( integration >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( integration >> 16 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( integration >> 24 ) & 0xFF );
        error_flag |= lightranger12_dci_replace_data ( ctx, LIGHTRANGER12_DCI_INT_TIME, ctx->temp_buf, 20, data_buf, 4, 0 );
    }
    return error_flag;
}

err_t lightranger12_get_int_time ( lightranger12_t *ctx, uint32_t *int_time_ms )
{
    err_t error_flag = LIGHTRANGER12_OK;
    error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_INT_TIME, ctx->temp_buf, 20 );
    *int_time_ms = ( ( uint32_t ) ctx->temp_buf[ 3 ] << 24 ) | ( ( uint32_t ) ctx->temp_buf[ 2 ] << 16 ) | 
                   ( ( uint16_t ) ctx->temp_buf[ 1 ] << 8 ) | ctx->temp_buf[ 0 ]; 
    *int_time_ms /= 1000;
    return error_flag;
}

err_t lightranger12_set_ranging_mode ( lightranger12_t *ctx, uint8_t ranging_mode )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t single_range[ 4 ] = { 0 };
    error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_RANGING_MODE, ctx->temp_buf, 8 );
    switch ( ranging_mode )
    {
        case LIGHTRANGER12_RANGING_MODE_CONTINUOUS:
        {
            ctx->temp_buf[ 1 ] = LIGHTRANGER12_RANGING_MODE_CONTINUOUS;
            ctx->temp_buf[ 3 ] = 0x03;
            single_range[ 0 ] = 0x00;
            break;
        }
        case LIGHTRANGER12_RANGING_MODE_AUTONOMOUS:
        {
            ctx->temp_buf[ 1 ] = LIGHTRANGER12_RANGING_MODE_AUTONOMOUS;
            ctx->temp_buf[ 3 ] = 0x02;
            single_range[ 0 ] = 0x01;
            break;
        }
        default:
        {
            error_flag |= LIGHTRANGER12_ERROR;
            break;
        }
    }
    if ( LIGHTRANGER12_OK == error_flag )
    {
        error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_RANGING_MODE, ctx->temp_buf, 8 );
        error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_SINGLE_RANGE, single_range, 4 );
    }
    return error_flag;
}

err_t lightranger12_get_ranging_mode ( lightranger12_t *ctx, uint8_t *ranging_mode )
{
    err_t error_flag = LIGHTRANGER12_OK;
    error_flag |= lightranger12_dci_read_data ( ctx, LIGHTRANGER12_DCI_RANGING_MODE, ctx->temp_buf, 8 );
    if ( LIGHTRANGER12_RANGING_MODE_CONTINUOUS == ctx->temp_buf[ 1 ] )
    {
        *ranging_mode = LIGHTRANGER12_RANGING_MODE_CONTINUOUS;
    }
    else
    {
        *ranging_mode = LIGHTRANGER12_RANGING_MODE_AUTONOMOUS;
    }
    return error_flag;
}

err_t lightranger12_start_ranging ( lightranger12_t *ctx )
{
    err_t error_flag = LIGHTRANGER12_OK;
    volatile lightranger12_block_header_t *bh_ptr;
    uint8_t cmd[ 4 ] = { 0x00, 0x03, 0x00, 0x00 };
    uint32_t header_config[ 2 ] = { 0 };
    uint32_t output[ 32 ] = { 0 };
    uint32_t output_bh_enable[ 4 ] = { 0 };
    uint32_t cnt = 0;
    uint8_t resolution = 0;

    // Enable mandatory output (meta and common data)
	output_bh_enable[ 0 ] = 0x00000007ul;
	output_bh_enable[ 1 ] = 0x00000000ul;
	output_bh_enable[ 2 ] = 0x00000000ul;
	output_bh_enable[ 3 ] = 0x00000000ul;

	// Enable selected outputs
    output_bh_enable[ 0 ] |= 0x00000020ul; // nb target detected
    output_bh_enable[ 0 ] |= 0x00000100ul; // distance mm
    output_bh_enable[ 0 ] |= 0x00000400ul; // target status

    // Send addresses of possible output
    output[ 0 ] = LIGHTRANGER12_START_BH;
    output[ 1 ] = LIGHTRANGER12_METADATA_BH;
    output[ 2 ] = LIGHTRANGER12_COMMONDATA_BH;
    output[ 3 ] = LIGHTRANGER12_AMBIENT_RATE_BH;
    output[ 4 ] = LIGHTRANGER12_SPAD_COUNT_BH;
    output[ 5 ] = LIGHTRANGER12_NB_TARGET_DETECTED_BH;
    output[ 6 ] = LIGHTRANGER12_SIGNAL_RATE_BH;
    output[ 7 ] = LIGHTRANGER12_RANGE_SIGMA_MM_BH;
    output[ 8 ] = LIGHTRANGER12_DISTANCE_BH;
    output[ 9 ] = LIGHTRANGER12_REFLECTANCE_BH;
    output[ 10 ] = LIGHTRANGER12_TARGET_STATUS_BH;
    output[ 11 ] = LIGHTRANGER12_MOTION_DETECT_BH;

    error_flag |= lightranger12_get_resolution ( ctx, &resolution );
    ctx->data_read_size = 0;
    ctx->stream_count = 255;

    // Update data size
    for ( cnt = 0; cnt < 32; cnt++ )
    {
        if ( ( 0 == output[ cnt ] ) || ( 0 == ( output_bh_enable[ 0 ] & ( 1ul << ( cnt % 32 ) ) ) ) )
        {
            continue;
        }
        bh_ptr = ( lightranger12_block_header_t * ) &output[ cnt ];
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

    if ( ctx->data_read_size > LIGHTRANGER12_TEMP_BUFFER_SIZE )
    {
        return LIGHTRANGER12_ERROR;
    }

    for ( cnt = 0; cnt < 128; cnt += 4 )
    {
        ctx->temp_buf[ cnt ] = ( uint8_t ) ( output[ cnt / 4 ] & 0xFF );
        ctx->temp_buf[ cnt + 1 ] = ( uint8_t ) ( ( output[ cnt / 4 ] >> 8 ) & 0xFF );
        ctx->temp_buf[ cnt + 2 ] = ( uint8_t ) ( ( output[ cnt / 4 ] >> 16 ) & 0xFF );
        ctx->temp_buf[ cnt + 3 ] = ( uint8_t ) ( ( output[ cnt / 4 ] >> 24 ) & 0xFF );
    }
    error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_OUTPUT_LIST, ctx->temp_buf, 128 );

    header_config[ 0 ] = ctx->data_read_size;
    header_config[ 1 ] = cnt + 1;

    for ( cnt = 0; cnt < 8; cnt += 4 )
    {
        ctx->temp_buf[ cnt ] = ( uint8_t ) ( header_config[ cnt / 4 ] & 0xFF );
        ctx->temp_buf[ cnt + 1 ] = ( uint8_t ) ( ( header_config[ cnt / 4 ] >> 8 ) & 0xFF );
        ctx->temp_buf[ cnt + 2 ] = ( uint8_t ) ( ( header_config[ cnt / 4 ] >> 16 ) & 0xFF );
        ctx->temp_buf[ cnt + 3 ] = ( uint8_t ) ( ( header_config[ cnt / 4 ] >> 24 ) & 0xFF );
    }
    error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_OUTPUT_CONFIG, ctx->temp_buf, 8 );

    for ( cnt = 0; cnt < 16; cnt += 4 )
    {
        ctx->temp_buf[ cnt ] = ( uint8_t ) ( output_bh_enable[ cnt / 4 ] & 0xFF );
        ctx->temp_buf[ cnt + 1 ] = ( uint8_t ) ( ( output_bh_enable[ cnt / 4 ] >> 8 ) & 0xFF );
        ctx->temp_buf[ cnt + 2 ] = ( uint8_t ) ( ( output_bh_enable[ cnt / 4 ] >> 16 ) & 0xFF );
        ctx->temp_buf[ cnt + 3 ] = ( uint8_t ) ( ( output_bh_enable[ cnt / 4 ] >> 24 ) & 0xFF );
    }
    error_flag |= lightranger12_dci_write_data ( ctx, LIGHTRANGER12_DCI_OUTPUT_ENABLES, ctx->temp_buf, 16 );

    // Start xshut bypass (interrupt mode)
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0009, 0x05 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x02 );

    // Start ranging session
    error_flag |= lightranger12_write_multi ( ctx, ( LIGHTRANGER12_UI_CMD_END - 3 ), cmd, 4 );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 1, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x03 );

    // Read UI range data content and compare if data size is the correct one
    error_flag |= lightranger12_dci_read_data ( ctx, 0x5440, ctx->temp_buf, 12 );
    if ( ( ( ( uint16_t ) ctx->temp_buf[ 9 ] << 8 ) | ctx->temp_buf[ 8 ] ) != ctx->data_read_size )
    {
        return LIGHTRANGER12_ERROR;
    }
    return error_flag;
}

err_t lightranger12_stop_ranging ( lightranger12_t *ctx )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint16_t timeout = 0;
    uint8_t status = 0;

    error_flag |= lightranger12_read_multi ( ctx, 0x2FFC, ctx->temp_buf, 4 );
    if ( ( 0x04 != ctx->temp_buf[ 1 ] ) || ( 0xFF != ctx->temp_buf[ 0 ] ) )
    {
        error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );

        // Provoke MCU stop
        error_flag |= lightranger12_write_byte ( ctx, 0x0015, 0x16 );
        error_flag |= lightranger12_write_byte ( ctx, 0x0014, 0x01 );

        // Poll for G02 status 0 MCU stop
        while ( 0x80 != ( status & 0x80 ) )
        {
            error_flag |= lightranger12_read_byte ( ctx, 0x0006, &status );
            Delay_10ms ( );
            // Timeout reached after 5 seconds
            if ( timeout++ > 500 )
            {
                error_flag |= LIGHTRANGER12_ERROR;
                break;
            }
        }
    }

    // Check GO2 status 1 if status is still OK
    error_flag |= lightranger12_read_byte ( ctx, 0x0006, &status );
    if ( status & 0x80 )
    {
        error_flag |= lightranger12_read_byte ( ctx, 0x0007, &status );
        if ( ( 0x84 != status ) && ( 0x85 != status ) )
        {
            error_flag |= LIGHTRANGER12_ERROR;
        }
    }

    // Undo MCU stop
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0014, 0x00 );
    error_flag |= lightranger12_write_byte ( ctx, 0x0015, 0x00 );

    // Stop xshut bypass
    error_flag |= lightranger12_write_byte ( ctx, 0x0009, 0x04 );
    error_flag |= lightranger12_write_byte ( ctx, 0x7FFF, 0x02 );
    return error_flag;
}

err_t lightranger12_get_ranging_data ( lightranger12_t *ctx, lightranger12_results_data_t *results )
{
    err_t error_flag = LIGHTRANGER12_OK;
    volatile lightranger12_block_header_t *bh_ptr;
    volatile uint16_t header_id = 0;
    volatile uint16_t footer_id = 0;
    uint32_t cnt = 0;
    uint32_t msize = 0;

    error_flag |= lightranger12_read_multi ( ctx, 0x0000, ctx->temp_buf, ctx->data_read_size );
    ctx->stream_count = ctx->temp_buf[ 0 ];
    lightranger12_swap_buffer ( ctx->temp_buf, ctx->data_read_size );

    // Start conversion at position 16 to avoid headers
    for ( cnt = 16; cnt < ctx->data_read_size; cnt += 4 )
    {
        bh_ptr = ( lightranger12_block_header_t * ) &ctx->temp_buf[ cnt ];
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
            case LIGHTRANGER12_METADATA_IDX:
            {
                results->silicon_temp_degc = ( int8_t ) ctx->temp_buf[ cnt + 12 ];
                break;
            }
            case LIGHTRANGER12_NB_TARGET_DETECTED_IDX:
            {
                memcpy ( results->nb_target_detected, &ctx->temp_buf[ cnt + 4 ], msize );
                break;
            }
            case LIGHTRANGER12_DISTANCE_IDX:
            {
                memcpy ( results->distance_mm, &ctx->temp_buf[ cnt + 4 ], msize );
                break;
            }
            case LIGHTRANGER12_TARGET_STATUS_IDX:
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

	// Convert data into their real format
    for ( cnt = 0; cnt < LIGHTRANGER12_RESOLUTION_8X8; cnt++ )
    {
        results->distance_mm[ cnt ] /= 4;
        if ( results->distance_mm[ cnt ] < 0 )
        {
            results->distance_mm[ cnt ] = 0;
        }
    }

    // Set target status to 255 if no target is detected for this zone
    for ( cnt = 0; cnt < LIGHTRANGER12_RESOLUTION_8X8; cnt++ )
    {
        if ( 0 == results->nb_target_detected[ cnt ] )
        {
            results->target_status[ cnt ] = 255;
        }
    }

    // Check if footer id and header id are matching. This allows to detect corrupted frames
    header_id = ( ( uint16_t ) ctx->temp_buf[ 8 ] << 8 ) | ctx->temp_buf[ 9 ];
    footer_id = ( ( uint16_t ) ctx->temp_buf[ ctx->data_read_size - 4 ] << 8 ) | 
                ctx->temp_buf[ ctx->data_read_size - 3 ];
    if ( header_id != footer_id )
    {
        return LIGHTRANGER12_ERROR;
    }
    return error_flag;
}

static void lightranger12_swap_buffer ( uint8_t *buffer, uint16_t size )
{
    uint8_t data_buf[ 4 ] = { 0 };
    uint16_t cnt = 0;
    for ( cnt = 0; cnt < size; cnt += 4 )
    {
        memcpy ( data_buf, &buffer[ cnt ], 4 );
        buffer[ cnt ] = data_buf[ 3 ];
        buffer[ cnt + 1 ] = data_buf[ 2 ];
        buffer[ cnt + 2 ] = data_buf[ 1 ];
        buffer[ cnt + 3 ] = data_buf[ 0 ];
    }
}

static err_t lightranger12_poll_for_answer ( lightranger12_t *ctx, uint8_t size, uint8_t pos,
                                             uint16_t address, uint8_t mask, uint8_t expected_value )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t timeout = 0;
    do 
    {
        error_flag |= lightranger12_read_multi ( ctx, address, ctx->temp_buf, size );
        Delay_10ms ( );
        // 2s timeout
        if ( ( timeout++ >= 200 ) ||
             ( ( size >= 4 ) && ( ctx->temp_buf[ 2 ] >= 0x7F ) ) )   
        {
            return LIGHTRANGER12_ERROR;
        }
    } 
    while ( ( ctx->temp_buf[ pos ] & mask ) != expected_value );

    return error_flag;
}

static err_t lightranger12_poll_for_mcu_boot ( lightranger12_t *ctx )
{
   err_t error_flag = LIGHTRANGER12_OK;
   uint16_t timeout = 0;
   uint8_t go2_status0 = 0;
   uint8_t go2_status1 = 0; 
   do 
   {
        error_flag |= lightranger12_read_byte ( ctx, 0x0006, &go2_status0 );
        if ( go2_status0 & 0x80 )
        {
            error_flag |= lightranger12_read_byte ( ctx, 0x0007, &go2_status1 );
            if ( go2_status1 & 0x01 )
            {
                break;
            }
        }
        Delay_1ms ( );
        if ( go2_status0 & 0x01 )
        {
            break;
        }
    }
    while ( timeout++ < 500 );

    return error_flag;
}

static err_t lightranger12_send_offset_data ( lightranger12_t *ctx, uint8_t resolution )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint32_t signal_grid[ 64 ] = { 0 };
    int16_t range_grid[ 64 ] = { 0 };
    uint8_t dss_4x4[ 8 ] = { 0x0F, 0x04, 0x04, 0x00, 0x08, 0x10, 0x10, 0x07 };
    uint8_t footer[ 8 ] = { 0x00, 0x00, 0x00, 0x0F, 0x03, 0x01, 0x01, 0xE4 };
    uint8_t cnt_0 = 0;
    uint8_t cnt_1 = 0;
    uint16_t cnt = 0;

    memcpy ( ctx->temp_buf, ctx->offset_data, LIGHTRANGER12_OFFSET_BUFFER_SIZE );

    // Data extrapolation is required for 4X4 offset
    if ( LIGHTRANGER12_RESOLUTION_4X4 == resolution )
    {
        memcpy ( &ctx->temp_buf[ 16 ], dss_4x4, sizeof ( dss_4x4 ) );
        lightranger12_swap_buffer ( ctx->temp_buf, LIGHTRANGER12_OFFSET_BUFFER_SIZE );
        for ( cnt = 0; cnt < 256; cnt += 4 )
        {
            signal_grid[ cnt / 4 ] = ( ( uint32_t ) ctx->temp_buf[ cnt + 60 ] << 24 ) | 
                                     ( ( uint32_t ) ctx->temp_buf[ cnt + 61 ] << 16 ) | 
                                     ( ( uint16_t ) ctx->temp_buf[ cnt + 62 ] << 8 ) | 
                                     ctx->temp_buf[ cnt + 63 ];
        }
        for ( cnt = 0; cnt < 128; cnt += 2 )
        {
            range_grid[ cnt / 2 ] = ( ( int16_t ) ctx->temp_buf[ cnt + 320 ] << 8 ) | ctx->temp_buf[ cnt + 321 ];
        }

        for ( cnt_0 = 0; cnt_0 < 4; cnt_0++ )
        {
            for ( cnt_1 = 0; cnt_1 < 4; cnt_1++ )
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
        memset ( &range_grid[ 16 ], 0, 96 );
        memset ( &signal_grid[ 16 ], 0, 192 );
        
        for ( cnt = 0; cnt < 256; cnt += 4 )
        {
            ctx->temp_buf[ cnt + 63 ] = ( uint8_t ) ( signal_grid[ cnt / 4 ] & 0xFF );
            ctx->temp_buf[ cnt + 62 ] = ( uint8_t ) ( ( signal_grid[ cnt / 4 ] >> 8 ) & 0xFF );
            ctx->temp_buf[ cnt + 61 ] = ( uint8_t ) ( ( signal_grid[ cnt / 4 ] >> 16 ) & 0xFF );
            ctx->temp_buf[ cnt + 60 ] = ( uint8_t ) ( ( signal_grid[ cnt / 4 ] >> 24 ) & 0xFF );
        }
        for ( cnt = 0; cnt < 128; cnt += 2 )
        {
            ctx->temp_buf[ cnt + 321 ] = ( uint8_t ) ( range_grid[ cnt / 2 ] & 0xFF );
            ctx->temp_buf[ cnt + 320 ] = ( uint8_t ) ( ( range_grid[ cnt / 2 ] >> 8 ) & 0xFF );
        }
        lightranger12_swap_buffer ( ctx->temp_buf, LIGHTRANGER12_OFFSET_BUFFER_SIZE );
    }
    for ( cnt = 0; cnt < ( LIGHTRANGER12_OFFSET_BUFFER_SIZE - 4 ); cnt++ )
    {
        ctx->temp_buf[ cnt ] = ctx->temp_buf[ cnt + 8 ];
    }
    memcpy ( &ctx->temp_buf[ 480 ], footer, 8 );
    memmove ( &ctx->temp_buf[ 2 ], &ctx->temp_buf[ 0 ], LIGHTRANGER12_OFFSET_BUFFER_SIZE );
    ctx->temp_buf[ 0 ] = 0x2E; // address msb
    ctx->temp_buf[ 1 ] = 0x18; // address lsb
    error_flag |= lightranger12_write_data ( ctx, ctx->temp_buf, LIGHTRANGER12_OFFSET_BUFFER_SIZE + 2 );
    memmove ( &ctx->temp_buf[ 0 ], &ctx->temp_buf[ 2 ], LIGHTRANGER12_OFFSET_BUFFER_SIZE );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 1, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x03 );
    return error_flag;
}

static err_t lightranger12_send_xtalk_data ( lightranger12_t *ctx, uint8_t resolution )
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t res4x4[ 8 ] = { 0x0F, 0x04, 0x04, 0x17, 0x08, 0x10, 0x10, 0x07 };
    uint8_t dss_4x4[ 8 ] = { 0x00, 0x78, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08 };
    uint8_t profile_4x4[ 4 ] = { 0xA0, 0xFC, 0x01, 0x00 };
    uint32_t signal_grid[ 64 ] = { 0 };
    uint8_t cnt_0 = 0;
    uint8_t cnt_1 = 0;
    uint16_t cnt = 0;

    memcpy ( ctx->temp_buf, ( uint8_t * ) lightranger12_default_xtalk_buf, 
             sizeof ( lightranger12_default_xtalk_buf ) );

    // Data extrapolation is required for 4X4 Xtalk
    if ( LIGHTRANGER12_RESOLUTION_4X4 == resolution )
    {
        memcpy ( &ctx->temp_buf[ 10 ], res4x4, sizeof ( res4x4 ) );
        memcpy ( &ctx->temp_buf[ 34 ], dss_4x4, sizeof ( dss_4x4 ) );

        lightranger12_swap_buffer ( &ctx->temp_buf[ 2 ], LIGHTRANGER12_XTALK_BUFFER_SIZE );
        for ( cnt = 0; cnt < 256; cnt += 4 )
        {
            signal_grid[ cnt / 4 ] = ( ( uint32_t ) ctx->temp_buf[ cnt + 54 ] << 24 ) | 
                                     ( ( uint32_t ) ctx->temp_buf[ cnt + 55 ] << 16 ) | 
                                     ( ( uint16_t ) ctx->temp_buf[ cnt + 56 ] << 8 ) | 
                                     ctx->temp_buf[ cnt + 57 ];
        }

        for ( cnt_0 = 0; cnt_0 < 4; cnt_0++ )
        {
            for ( cnt_1 = 0; cnt_1 < 4; cnt_1++ )
            {
                signal_grid [ cnt_1 + ( 4 * cnt_0 ) ] = ( signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 1 ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 8 ] + 
                                                          signal_grid [ ( 2 * cnt_1 ) + ( 16 * cnt_0 ) + 9 ] ) / 4;
            }
        }
        memset( &signal_grid[ 16 ], 0, 192 );
        for ( cnt = 0; cnt < 256; cnt += 4 )
        {
            ctx->temp_buf[ cnt + 57 ] = ( uint8_t ) ( signal_grid[ cnt / 4 ] & 0xFF );
            ctx->temp_buf[ cnt + 56 ] = ( uint8_t ) ( ( signal_grid[ cnt / 4 ] >> 8 ) & 0xFF );
            ctx->temp_buf[ cnt + 55 ] = ( uint8_t ) ( ( signal_grid[ cnt / 4 ] >> 16 ) & 0xFF );
            ctx->temp_buf[ cnt + 54 ] = ( uint8_t ) ( ( signal_grid[ cnt / 4 ] >> 24 ) & 0xFF );
        }
        lightranger12_swap_buffer ( &ctx->temp_buf[ 2 ], LIGHTRANGER12_XTALK_BUFFER_SIZE );
        memcpy ( &ctx->temp_buf[ 310 ], profile_4x4, sizeof ( profile_4x4 ) );
        memset ( &ctx->temp_buf[ 122 ], 0, 4 );
    }

    error_flag |= lightranger12_write_data ( ctx, ctx->temp_buf, LIGHTRANGER12_XTALK_BUFFER_SIZE + 2 );
    error_flag |= lightranger12_poll_for_answer ( ctx, 4, 1, LIGHTRANGER12_UI_CMD_STATUS, 0xFF, 0x03 );
    return error_flag;
}

static err_t lightranger12_i2c_write ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len ) 
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t data_buf[ 18 ] = { 0 };
    uint8_t cnt = 0;
    if ( 0xFFFF == reg )
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_in, len );
    }
    else if ( len <= 16 )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
        for ( cnt = 0; cnt < len; cnt++ )
        {
            data_buf[ cnt + 2 ] = data_in[ cnt ];
        }
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 2 );
    }
    else
    {
        error_flag |= LIGHTRANGER12_ERROR;
    }
    return error_flag;
}

static err_t lightranger12_i2c_read ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, data_out, len );
    return error_flag;
}

static err_t lightranger12_spi_write ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len ) 
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( 0xFFFF == reg )
    {
        data_buf[ 0 ] = data_in[ 0 ] | SPI_WRITE_MASK;
        data_buf[ 1 ] = data_in[ 1 ];
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
        error_flag |= spi_master_write( &ctx->spi, &data_in[ 2 ], len - 2 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else if ( len <= 16 )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF ) | SPI_WRITE_MASK;
        data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
        error_flag |= spi_master_write( &ctx->spi, data_in, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        error_flag |= LIGHTRANGER12_ERROR;
    }
    return error_flag;
}

static err_t lightranger12_spi_read ( lightranger12_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = LIGHTRANGER12_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF ) & ( ~SPI_WRITE_MASK );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, data_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

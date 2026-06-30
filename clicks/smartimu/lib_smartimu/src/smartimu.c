/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file smartimu.c
 * @brief Smart IMU Click Driver.
 */

#include "smartimu.h"
#include "smartimu_firmware.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief SPI read mask.
 * @details Definition of SPI read mask.
 */
#define SPI_READ_MASK     0x80

/**
 * @brief Boot-sequence poll timeout.
 * @details Definition of Boot-sequence poll timeout.
 */
#define BOOT_POLL_LIMIT   200u

/* Pointer and size of the BHI385 pre-compiled firmware image */
const uint8_t *smartimu_bhi385_firmware = bhi385_firmware_image;
const uint32_t smartimu_bhi385_firmware_size = sizeof( bhi385_firmware_image );

/**
 * @brief Smart IMU I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartimu_i2c_write ( smartimu_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart IMU I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartimu_i2c_read ( smartimu_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart IMU SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartimu_spi_write ( smartimu_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart IMU SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartimu_spi_read ( smartimu_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void smartimu_cfg_setup ( smartimu_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTIMU_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMARTIMU_DRV_SEL_I2C;
}

void smartimu_drv_interface_sel ( smartimu_cfg_t *cfg, smartimu_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smartimu_init ( smartimu_t *ctx, smartimu_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->accel_scale = SMARTIMU_ACCEL_SCALE_8G;
    ctx->gyro_scale = SMARTIMU_GYRO_SCALE_2000DPS;

    if ( SMARTIMU_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f = smartimu_i2c_read;
        ctx->write_f = smartimu_i2c_write;
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

        ctx->read_f  = smartimu_spi_read;
        ctx->write_f = smartimu_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SMARTIMU_OK;
}

err_t smartimu_default_cfg ( smartimu_t *ctx ) 
{
    err_t error_flag = SMARTIMU_OK;
    uint8_t reg_data = 0;
    uint16_t timeout = 0;
    
    /* Software reset */
    error_flag |= smartimu_reset_device( ctx );
    Delay_10ms( );
    Delay_10ms( ); 

    /* Verify communication */
    if ( SMARTIMU_OK != smartimu_check_communication( ctx ) )
    {
        return SMARTIMU_ERROR;
    }
    
    /* Configure HIRQ:
     *    bit[5] = 0 -> active high
     *    bit[6] = 0 -> level output
     *    bit[7] = 0 -> push-pull    */
    reg_data = SMARTIMU_HOST_INT_HIGH_LEVEL_PP;
    error_flag |= ctx->write_f( ctx, SMARTIMU_REG_HOST_INT_CTRL, &reg_data, 1u );

    /* Wait for bootloader "Host Interface Ready" */
    for ( timeout = 0; timeout < BOOT_POLL_LIMIT; timeout++ )
    {
        error_flag |= ctx->read_f( ctx, SMARTIMU_REG_BOOT_STATUS, &reg_data, 1u );

        if ( reg_data & SMARTIMU_BOOT_STAT_HOST_IF_RDY )
        {
            break;
        }

        Delay_10ms( );
    }
    
    /* Check if bootloader did not become ready */
    if ( !( reg_data & SMARTIMU_BOOT_STAT_HOST_IF_RDY ) )
    {
        return SMARTIMU_ERROR; 
    }

    /* Upload firmware */
    if ( SMARTIMU_OK != smartimu_upload_firmware( ctx, smartimu_bhi385_firmware, smartimu_bhi385_firmware_size ) )
    {
        return SMARTIMU_ERROR;
    }
    
    /* Wait for ECDSA firmware verification */
    for ( timeout = 0; timeout < BOOT_POLL_LIMIT; timeout++ )
    {
        error_flag |= ctx->read_f( ctx, SMARTIMU_REG_BOOT_STATUS, &reg_data, 1u );

        if ( reg_data & SMARTIMU_BOOT_STAT_FW_VFY_DONE )
        {
            break;
        }

        Delay_10ms( );
    }
    
    /* Check if ECDSA signature or CRC failed */
    if ( reg_data & SMARTIMU_BOOT_STAT_FW_VFY_ERR )
    { 
        return SMARTIMU_ERROR;   
    }

    /* Check if verification did not complete in time */
    if ( !( reg_data & SMARTIMU_BOOT_STAT_FW_VFY_DONE ) )
    {
        return SMARTIMU_ERROR;
    }

    /* Boot firmware (CMD 0x0003, no payload) */
    if ( SMARTIMU_OK != smartimu_send_command( ctx, SMARTIMU_CMD_BOOT_RAM, NULL, 0 ) )
    {
        return SMARTIMU_ERROR;
    }

    /* Wait for firmware "Host Interface Ready" */
    for ( timeout = 0; timeout < BOOT_POLL_LIMIT; timeout++ )
    {
        error_flag |= ctx->read_f( ctx, SMARTIMU_REG_BOOT_STATUS, &reg_data, 1u );

        if ( reg_data & SMARTIMU_BOOT_STAT_HOST_IF_RDY )
        {
            break;
        }

        Delay_10ms( );
    }
    
    /* Check if firmware boot has not completed */
    if ( !( reg_data & SMARTIMU_BOOT_STAT_HOST_IF_RDY ) )
    {
        return SMARTIMU_ERROR;
    }

    /* Drain initialisation FIFOs.
     * The "Initialized" Meta Events are the first events in both the Wake-Up
     * and Non-Wake-Up FIFOs. Read (and discard) the FIFO descriptors to
     * consume them and de-assert HIRQ before enabling virtual sensors.     */
    error_flag |= smartimu_drain_fifo_channel( ctx, SMARTIMU_REG_CHAN_FIFO_W );
    error_flag |= smartimu_drain_fifo_channel( ctx, SMARTIMU_REG_CHAN_FIFO_NW );
    error_flag |= smartimu_drain_fifo_channel( ctx, SMARTIMU_REG_CHAN_STATUS );
    Delay_10ms( );

    /* Enable virtual sensors.
     * Accel Corrected Non-Wake-Up (ID=4), 10 Hz, latency = 0 ms
     * Gyro  Corrected Non-Wake-Up (ID=13), 10 Hz, latency = 0 ms */
    error_flag |= smartimu_configure_vir_sensor( ctx, SMARTIMU_VSENSOR_ACCEL_CORR_NWU, SMARTIMU_DEFAULT_ODR_HZ, 0 );
    Delay_10ms( );
    error_flag |= smartimu_configure_vir_sensor( ctx, SMARTIMU_VSENSOR_GYRO_CORR_NWU, SMARTIMU_DEFAULT_ODR_HZ, 0 );
    Delay_10ms( );

    return error_flag;
}

err_t smartimu_generic_write ( smartimu_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t smartimu_generic_read ( smartimu_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t smartimu_check_communication ( smartimu_t *ctx )
{
    uint8_t chip_id = 0;

    err_t error_flag = ctx->read_f( ctx, SMARTIMU_REG_CHIP_ID, &chip_id, 1 );
    if ( SMARTIMU_OK != error_flag )
    {
        return SMARTIMU_ERROR;
    }
    
    if ( SMARTIMU_CHIP_ID_VALUE != chip_id )
    {
        return SMARTIMU_ERROR;
    }

    return SMARTIMU_OK;
}

err_t smartimu_reset_device ( smartimu_t *ctx )
{
    uint8_t reset_val = SMARTIMU_RESET_REQUEST;
    return ctx->write_f( ctx, SMARTIMU_REG_RESET_REQ, &reset_val, 1 );
}

err_t smartimu_send_command ( smartimu_t *ctx, uint16_t cmd_id, uint8_t *payload, uint16_t payload_len )
{
    /* Command packet layout (all multi-byte fields are little-endian):
     *
     *   Offset 0x00-0x01 : Command ID  
     *   Offset 0x02-0x03 : Length = number of CONTENT bytes that follow,    
     *                               rounded UP to the next multiple of 4.
     *   Offset 0x04+     : Payload (Length bytes, zero-padded to 4B boundary)
     *
     *   Total packet size must be a multiple of 4 bytes. */
    uint16_t padded_len = ( payload_len + 3u ) & ~3u;
    uint8_t  packet[ 256 ] = { 0 };

    packet[ 0 ] = ( uint8_t ) ( cmd_id & 0xFF );
    packet[ 1 ] = ( uint8_t ) ( ( cmd_id >> 8 ) & 0xFF );
    packet[ 2 ] = ( uint8_t ) ( padded_len & 0xFF );
    packet[ 3 ] = ( uint8_t ) ( ( padded_len >> 8 ) & 0xFF );

    if ( NULL != payload && payload_len > 0 )
    {
        for ( uint16_t cnt = 0; cnt < payload_len; cnt++ )
        {
            packet[ SMARTIMU_CMD_HEADER_SIZE + cnt ] = payload[ cnt ];
        }   
    }

    uint8_t total = ( uint8_t ) ( SMARTIMU_CMD_HEADER_SIZE + padded_len );
    return ctx->write_f( ctx, SMARTIMU_REG_CHAN_CMD, packet, total );
}

err_t smartimu_upload_firmware ( smartimu_t *ctx, const uint8_t *fw_data, uint32_t fw_size )                        
{
    /* Firmware upload protocol:
     *
     *   Transaction 1 (write to DMA channel 0 -> reg 0x00):
     *      [0x02][0x00] -> Command ID = 0x0002 (Upload to Program RAM)
     *      [fw_words_LSB][fw_words_MSB] -> Length field = total FW size in 32-bit words
     *      [fw_data[0] ... fw_data[FW_FIRST_CHUNK-1]] -> first firmware chunk
     *
     *   Transactions 2..N (subsequent writes to reg 0x00, NO command header):
     *      [fw_data[offset] ... fw_data[offset + FW_CHUNK_SIZE - 1]]
     *
     *   Every write must contain a multiple of 4 bytes. */
    uint8_t  packet[ 256 ] = { 0 };
    uint32_t fw_words = fw_size / SMARTIMU_FW_WORD_SIZE;
    uint32_t bytes_sent = 0;
    uint32_t first_chunk = 0;
    err_t error_flag = SMARTIMU_OK;

    if ( ( NULL == fw_data ) || ( 0 == fw_size ) || ( 0 != fw_size % SMARTIMU_FW_WORD_SIZE ) )
    {
        return SMARTIMU_ERROR;
    }

    /* Write upload FW to RAM command(command ID = 0x002) to DMA channel 0.
     * Command header:
     *    packet[0] = CMD_ID LSB
     *    packet[1] = CMD_ID MSB
     *    packet[2] = length LSB
     *    packet[3] = length MSB */
    packet[ 0 ] = ( uint8_t ) ( SMARTIMU_CMD_UPLOAD_FW & 0xFF );                              
    packet[ 1 ] = ( uint8_t ) ( ( SMARTIMU_CMD_UPLOAD_FW >> 8 ) & 0xFF );                               
    packet[ 2 ] = ( uint8_t ) ( fw_words & 0xFF );       
    packet[ 3 ] = ( uint8_t ) ( ( fw_words >> 8 ) & 0xFF );
    
    /* fill first data chunk */
    if ( fw_size < SMARTIMU_FW_FIRST_CHUNK )
    {
        first_chunk = fw_size;
    }
    else
    {
        first_chunk = SMARTIMU_FW_FIRST_CHUNK;
    }

    for ( uint32_t cnt = 0; cnt < first_chunk; cnt++ )
    {
        packet[ SMARTIMU_CMD_HEADER_SIZE + cnt ] = fw_data[ cnt ];
    }

    /* send first data chunk */
    error_flag = ctx->write_f( ctx, SMARTIMU_REG_CHAN_CMD, packet, ( uint8_t ) ( SMARTIMU_CMD_HEADER_SIZE + first_chunk ) );
    if ( SMARTIMU_OK != error_flag )
    {
        return SMARTIMU_ERROR;
    }
    
    /* keep track of how many firmware bytes have been sent */
    bytes_sent += first_chunk;
    
    /* Subsequent transactions: firmware data only (no header) */
    while ( bytes_sent < fw_size )
    {
        uint32_t chunk = 0;
        uint32_t remaining = fw_size - bytes_sent;

        /* fill next data chunk */
        if ( remaining < SMARTIMU_FW_CHUNK_SIZE )
        {
            chunk = remaining;
        }
        else
        {
            chunk = SMARTIMU_FW_CHUNK_SIZE;
        }
        
        /* send next data chunk */ 
        uint8_t fw_chunk_buf[ SMARTIMU_FW_CHUNK_SIZE ] = { 0 };        
        for ( uint32_t cnt = 0; cnt < chunk; cnt++ )
        {
            fw_chunk_buf[ cnt ] = fw_data[ bytes_sent + cnt ];
        }

        error_flag = ctx->write_f( ctx, SMARTIMU_REG_CHAN_CMD, fw_chunk_buf, ( uint8_t ) chunk );      
        if ( SMARTIMU_OK != error_flag )
        {
            return SMARTIMU_ERROR;
        }
        
        bytes_sent += chunk;
    }

    return SMARTIMU_OK;
}

err_t smartimu_configure_vir_sensor ( smartimu_t *ctx, uint8_t sensor_id, float odr_hz, uint32_t latency_ms )
{
    /* Configure Sensor payload:
     *
     *   Offset 0x00      : Sensor ID 
     *   Offset 0x01-0x04 : Sample Rate in Hz (LSB first)
     *   Offset 0x05-0x07 : Latency in ms (24-bit unsigned, LSB first)
     *
     *   Setting odr_hz = 0.0f disables the virtual sensor. */
    uint8_t payload[ SMARTIMU_CFG_SENSOR_PAYLOAD_SIZE ] = { 0 };

    payload[ 0 ] = sensor_id;

    /* Copy the float ODR value as raw little-endian bytes into the payload. */
    uint32_t odr_raw = 0;
    memcpy( &odr_raw, &odr_hz, sizeof( float ) );

    payload[ 1 ] = ( uint8_t ) ( odr_raw & 0xFF );
    payload[ 2 ] = ( uint8_t ) ( ( odr_raw >> 8  ) & 0xFF );
    payload[ 3 ] = ( uint8_t ) ( ( odr_raw >> 16 ) & 0xFF );
    payload[ 4 ] = ( uint8_t ) ( ( odr_raw >> 24 ) & 0xFF );

    payload[ 5 ] = ( uint8_t ) ( latency_ms & 0xFF );
    payload[ 6 ] = ( uint8_t ) ( ( latency_ms >> 8 )  & 0xFF );
    payload[ 7 ] = ( uint8_t ) ( ( latency_ms >> 16 ) & 0xFF );
    
    /* Send configure sensor command to DMA channel 0 */
    return smartimu_send_command( ctx, SMARTIMU_CMD_CONFIGURE_SENSOR, payload, SMARTIMU_CFG_SENSOR_PAYLOAD_SIZE );
}

uint8_t smartimu_get_int_pin ( smartimu_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t smartimu_drain_fifo_channel ( smartimu_t *ctx, uint8_t fifo_reg )
{
    uint8_t buff[ SMARTIMU_FIFO_READ_MAX ] = { 0 };

    err_t error_flag = ctx->read_f( ctx, fifo_reg, buff, SMARTIMU_FIFO_READ_MAX );
    if ( SMARTIMU_OK != error_flag )
    {
        return SMARTIMU_ERROR;
    }

    return SMARTIMU_OK;
}

err_t smartimu_read_fifo_channel ( smartimu_t *ctx, uint8_t fifo_reg, smartimu_data_t *data_out, uint8_t *sample_found )
{
    uint8_t buff[ SMARTIMU_FIFO_READ_MAX ] = { 0 };
    uint16_t end = 0;

    if ( ( NULL == data_out ) || ( NULL == sample_found ) )
    {
        return SMARTIMU_ERROR;
    }

    *sample_found = 0;
    
    /* Read bytes from the requested FIFO */
    if ( SMARTIMU_OK != ctx->read_f( ctx, fifo_reg, buff, SMARTIMU_FIFO_READ_MAX ) )
    {
        return SMARTIMU_ERROR;
    }

    /* Parse the 4-byte channel descriptor:
     *   BYTE 0-1 -> payload length
     *   BYTE 2-3 -> padding / reserved */
    uint16_t transfer_len = ( uint16_t ) buff[ 0 ] | ( ( uint16_t ) buff[ 1 ] << 8 );
    if ( 0 == transfer_len )
    {
        return SMARTIMU_OK;
    }
    
    /* Clamp the parse boundary to the buffer size to avoid overrun.
     * +4 accounts for the channel descriptor consumed above. */
    if ( ( transfer_len + SMARTIMU_CMD_HEADER_SIZE ) < SMARTIMU_FIFO_READ_MAX )
    {
        end = transfer_len + SMARTIMU_CMD_HEADER_SIZE;
    }
    else
    {
        end = SMARTIMU_FIFO_READ_MAX;
    }

    uint16_t cnt = SMARTIMU_CMD_HEADER_SIZE;
    while ( cnt < end )
    {   
        /* Every event begins with a 1-byte event ID. */
        uint8_t event_id = buff[ cnt++ ];
        
        /* Padding: marks end of useful data in this transfer. */
        if ( SMARTIMU_FIFO_PADDING == event_id )
        {
            break;
        }
        
        /* Filler: alignment byte inserted by BHI385, skip and read next ID. */
        if ( SMARTIMU_FIFO_FILLER == event_id )
        {
            continue;
        }
        
        /* Timestamp events: BHI385 inserts these between sensor events to indicate
         * when the following sample was captured.
         *   Small : 1-byte payload.
         *   Large : 2-byte payload.
         *   Full  : 5-byte payload. */
        if ( ( SMARTIMU_FIFO_TS_SMALL_NWU == event_id ) ||
             ( SMARTIMU_FIFO_TS_SMALL_WU  == event_id ) )
        {
            if ( cnt < end )
            {
                cnt += SMARTIMU_FIFO_TS_SMALL_PAYLOAD_SIZE;
            }
            continue;
        }

        if ( ( SMARTIMU_FIFO_TS_LARGE_NWU == event_id ) ||
             ( SMARTIMU_FIFO_TS_LARGE_WU  == event_id ) )
        {
            if ( ( cnt + SMARTIMU_FIFO_TS_LARGE_PAYLOAD_SIZE - 1u ) < end )
            {
                cnt += SMARTIMU_FIFO_TS_LARGE_PAYLOAD_SIZE;
            }
            continue;
        }
        
        if ( ( SMARTIMU_FIFO_TS_FULL_NWU == event_id ) ||
             ( SMARTIMU_FIFO_TS_FULL_WU  == event_id ) )
        {
            if ( ( cnt + SMARTIMU_FIFO_TS_FULL_PAYLOAD_SIZE - 1u ) < end )
            {
                cnt += SMARTIMU_FIFO_TS_FULL_PAYLOAD_SIZE;
            }
            continue;
        }
        
        /* Meta events: system notifications from BHI385 firmware.
         * Each carries a fixed 3-byte payload. */
        if ( ( SMARTIMU_FIFO_META_NWU == event_id ) ||
             ( SMARTIMU_FIFO_META_WU  == event_id ) )
        {
            if ( ( cnt + SMARTIMU_FIFO_META_PAYLOAD_SIZE - 1u ) < end )
            {
                cnt += SMARTIMU_FIFO_META_PAYLOAD_SIZE;
            }
            continue;
        }
        
        /* Accelerometer corrected event (Wake-Up or Non-Wake-Up).
         * Payload: 6 bytes — two bytes per axis, signed 16-bit, little-endian.
         * Physical value [g] = raw / accel_scale (4096 LSB/g for +/-8 g range). */
        if ( ( SMARTIMU_VSENSOR_ACCEL_CORR_NWU == event_id ) ||
             ( SMARTIMU_VSENSOR_ACCEL_CORR_WU  == event_id ) )
        {
            if ( ( cnt + SMARTIMU_FIFO_SENSOR_PAYLOAD_SIZE - 1u ) < end )
            {
                int16_t x = ( int16_t ) ( ( uint16_t ) buff[ cnt ] | ( ( uint16_t ) buff[ cnt + 1u ] << 8 ) );
                int16_t y = ( int16_t ) ( ( uint16_t ) buff[ cnt + 2u ] | ( ( uint16_t ) buff[ cnt + 3u ] << 8 ) );
                int16_t z = ( int16_t ) ( ( uint16_t ) buff[ cnt + 4u ] | ( ( uint16_t ) buff[ cnt + 5u ] << 8 ) );

                data_out->accel.x = ( float ) x / ctx->accel_scale;
                data_out->accel.y = ( float ) y / ctx->accel_scale;
                data_out->accel.z = ( float ) z / ctx->accel_scale;
                *sample_found = 1u;
                cnt += SMARTIMU_FIFO_SENSOR_PAYLOAD_SIZE;
            }
            continue;
        }
        
        /* Gyroscope corrected event (Wake-Up or Non-Wake-Up).
         * Payload: 6 bytes — two bytes per axis, signed 16-bit, little-endian.
         * Physical value [dps] = raw / gyro_scale (16.384 LSB/dps for +/-2000 dps range). */
        if ( ( SMARTIMU_VSENSOR_GYRO_CORR_NWU == event_id ) ||
             ( SMARTIMU_VSENSOR_GYRO_CORR_WU  == event_id ) )
        {
            if ( ( cnt + SMARTIMU_FIFO_SENSOR_PAYLOAD_SIZE - 1u ) < end )
            {
                int16_t x = ( int16_t ) ( ( uint16_t ) buff[ cnt ] | ( ( uint16_t ) buff[ cnt + 1u ] << 8 ) );
                int16_t y = ( int16_t ) ( ( uint16_t ) buff[ cnt + 2u ] | ( ( uint16_t ) buff[ cnt + 3u ] << 8 ) );
                int16_t z = ( int16_t ) ( ( uint16_t ) buff[ cnt + 4u ] | ( ( uint16_t ) buff[ cnt + 5u ] << 8 ) );

                data_out->gyro.x = ( float ) x / ctx->gyro_scale;
                data_out->gyro.y = ( float ) y / ctx->gyro_scale;
                data_out->gyro.z = ( float ) z / ctx->gyro_scale;
                *sample_found = 1u;
                cnt += SMARTIMU_FIFO_SENSOR_PAYLOAD_SIZE;
            }
            continue;
        }

        break;
    }

    return SMARTIMU_OK;
}

static err_t smartimu_i2c_write ( smartimu_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t smartimu_i2c_read ( smartimu_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t smartimu_spi_write ( smartimu_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t smartimu_spi_read ( smartimu_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

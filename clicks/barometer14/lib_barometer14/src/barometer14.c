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
 * @file barometer14.c
 * @brief Barometer 14 Click Driver.
 */

#include "barometer14.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                   0x00

/**
 * @brief SPI read trigger.
 * @details Definition of the first byte sent by the master to trigger an SPI read transaction.
 */
#define SPI_READ_TRIGGER        0x6C

/**
 * @brief CRC16-CCITT polynomial and preload.
 * @details Definition of CRC16-CCITT polynomial and preload value used to protect all data exchanged with the device.
 */
#define CRC16_POLYNOMIAL        0x1021
#define CRC16_PRELOAD           0xFFFF

/**
 * @brief Barometer 14 calculate CRC function.
 * @details This function calculates CRC16-CCITT over a byte array.
 * @param[in] data_in : Pointer to the input byte array.
 * @param[in] len : Number of bytes to process.
 * @return 16-bit CRC value.
 * @note Polynomial: 0x1021, preload: 0xFFFF, high byte first.
 */
static uint16_t barometer14_calculate_crc ( uint8_t *data_in, uint16_t len );

/**
 * @brief Barometer 14 error code function.
 * @details This function checks whether the first byte received from the device
 * is a known error response code.
 * @param[in] first_byte : First byte of the device response.
 * @return @li @c 1 - Known error code,
 *         @li @c 0 - Not an error code.
 * @note None.
 */
static uint8_t barometer14_is_error_code ( uint8_t first_byte );

/**
 * @brief Barometer 14 serialize measurement configuration function.
 * @details This function serializes a measurement configuration structure into
 * an 18-byte wire buffer for the Save AS Config command.
 * @param[in] meas_cfg : Pointer to the source configuration structure.
 * See #barometer14_meas_cfg_t object definition for detailed explanation.
 * @param[out] buf : Pointer to the output buffer(18 bytes).
 * @return Nothing.
 * @note None.
 */
static void barometer14_ser_meas_cfg ( barometer14_meas_cfg_t *meas_cfg, uint8_t *buf );

/**
 * @brief Barometer 14 deserialize measurement configuration function.
 * @details This function deserializes an 18-byte wire buffer into a measurement
 * configuration structure received from the Read AS Config command.
 * @param[in] buf : Pointer to the source buffer (18 bytes).
 * @param[out] meas_cfg : Pointer to the output configuration structure.
 * See #barometer14_meas_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void barometer14_deser_meas_cfg ( uint8_t *buf, barometer14_meas_cfg_t *meas_cfg );

/**
 * @brief Barometer 14 SPI writing function.
 * @details This function builds a proper command frame and writes it to
 * the device by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer14_spi_write ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 14 SPI reading function.
 * @details This function sends the 0x6C read trigger byte and then reads
 * a proper command frame from the device by using SPI serial interface,
 * verifying both the command echo and the CRC.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer14_spi_read ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 14 I2C writing function.
 * @details This function builds a proper command frame and writes it to the device
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of command parameters to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer14_i2c_write ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 14 I2C reading function.
 * @details This function reads a proper command frame from the device by using I2C serial
 * interface and verifies both the command echo and the CRC.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of command result bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer14_i2c_read ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 14 send command then read function.
 * @details This function sends a command with optional parameters,
 * waits for BUSY to clear and optionally reads the response.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Pointer to the command parameter bytes to send (NULL if params_len is 0).
 * @param[in] params_len : Number of command parameter bytes to send.
 * @param[out] data_out : Pointer to the response buffer (NULL if no response is expected).
 * @param[in] response_len : Number of result bytes expected (excluding CMD echo and CRC).
 * @param[in] spi_delay_ms : Delay in milliseconds used in SPI mode instead of WKP polling between write and read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer14_send_cmd_then_read ( barometer14_t *ctx,
                                              uint8_t cmd,
                                              uint8_t *data_in,
                                              uint8_t params_len,
                                              uint8_t *data_out,
                                              uint8_t response_len,
                                              uint16_t spi_delay_ms );

void barometer14_cfg_setup ( barometer14_cfg_t *cfg )
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wkp  = HAL_PIN_NC;
    cfg->alt  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER14_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    /* SPI mode requires an MCU where the minimum achievable SPI clock does not exceed 100 kHz due to half-duplex implementation */
    cfg->drv_sel = BAROMETER14_DRV_SEL_I2C;
}

void barometer14_drv_interface_sel ( barometer14_cfg_t *cfg, barometer14_drv_t drv_sel )
{
    cfg->drv_sel = drv_sel;
}

err_t barometer14_init ( barometer14_t *ctx, barometer14_cfg_t *cfg )
{
    ctx->drv_sel = cfg->drv_sel;

    if ( BAROMETER14_DRV_SEL_I2C == ctx->drv_sel )
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

        ctx->read_f  = barometer14_i2c_read;
        ctx->write_f = barometer14_i2c_write;

        /* KP497 I2C serial interface selection procedure (User Manual, Chapter 1, page 4):
         *    1. Wait >10ms after power-on reset.
         *    2. Apply high level to both SCL and SDA (pull-ups R4/R5 on the Click board ensure this).
         *    3. Pull WKP pin low for >10us.
         *    4. Release WKP pin.
         *    5. Wait >200us - I2C interface is now ready. */
        digital_out_t wkp_out;

        digital_out_init( &wkp_out, cfg->wkp );

        Delay_10ms( );
        
        digital_out_low( &wkp_out );
        Delay_10us( );
        Delay_10us( );

        digital_out_high( &wkp_out );
        Delay_1ms( );
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        /* KP497 SPI serial interface selection procedure (User Manual, Chapter 1, page 4):
         *    1. Wait >10ms after power-on reset.
         *    2. Pull CLK or DATA or both to low level (recommended to pull both).
         *    3. Wait >2us.
         *    4. Pull WKP pin low(which in this case is CS pin when jumpers are set for SPI communication).
         *    5. Wait >10us.
         *    6. Release CLK, DATA and WKP (all should go high via internal pull-up resistors).
         *    7. Wait >200us - SPI interface is now ready.
         * All three pins are controlled as GPIO before handing them over to the driver. */
        digital_out_t cs_out;
        digital_out_t sck_out;
        digital_out_t mosi_out;

        digital_out_init( &sck_out, cfg->sck );
        digital_out_init( &mosi_out, cfg->mosi );
        digital_out_init( &cs_out, cfg->cs );

        Delay_10ms( );

        digital_out_low( &sck_out );
        digital_out_low( &mosi_out );
        Delay_10us( );

        digital_out_low( &cs_out );
        Delay_10us( );
        Delay_10us( );

        digital_out_high( &sck_out );
        digital_out_high( &mosi_out );
        digital_out_high( &cs_out );
        Delay_1ms( );

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

        ctx->read_f  = barometer14_spi_read;
        ctx->write_f = barometer14_spi_write;
    }

    digital_in_init( &ctx->wkp, cfg->wkp );
    digital_in_init( &ctx->alt, cfg->alt );

    return BAROMETER14_OK;
}

err_t barometer14_default_cfg ( barometer14_t *ctx )
{
    err_t error_flag = BAROMETER14_OK;
    uint32_t sensor_id    = 0;
    uint16_t product_code = 0;
    uint32_t dev_status   = 0;
    uint16_t auto_status  = 0;
    uint8_t  meas_status  = 0;
    uint8_t  last_id      = 0;

    /* Wait for the device to complete power-on initialization before sending the first command. */
    Delay_10ms( );
    
    /* Check communication by reading sensor ID and product code */
    error_flag |= barometer14_read_id( ctx, &sensor_id, &product_code );
    if ( BAROMETER14_OK != error_flag )
    {
        return BAROMETER14_ERROR;
    }

    /* Setting the parameter to 0xAC clears the Device Status Register and the Alert pin */
    error_flag |= barometer14_read_status( ctx,
                                           BAROMETER14_STATUS_CLEAR,
                                           &dev_status,
                                           &auto_status,
                                           &meas_status,
                                           &last_id );

    // /* Serial interface selection */
    // uint8_t set_status = 0;
    // uint8_t iface_type = 0;

    // if ( BAROMETER14_DRV_SEL_I2C == ctx->drv_sel )
    // {
    //     iface_type = BAROMETER14_SERIAL_I2C;
    // }
    // else
    // {
    //     iface_type = BAROMETER14_SERIAL_SPI;
    // }

    // error_flag |= barometer14_lock_ser_interface( ctx, iface_type, &set_status );
    // if ( set_status & 0x80 )
    // {
    //     return BAROMETER14_ERROR;
    // }

    return error_flag;
}

err_t barometer14_measure_pressure ( barometer14_t *ctx, uint8_t *meas_status, float *pressure )
{
    uint8_t data_buf[ 3 ] = { 0 };

    /* Send 'Measure Pressure command' (0xA8):
     *    Parameters: None.
     *    Response[3 bytes]: 1 byte  (data_buf[0])    -> Status
     *                       2 bytes (data_buf[1..2]) -> Pressure data (16-bit two's complement,
     *                                                   MSB first, resolution 16 LSB = 1 kPa). */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_MEASURE_PRESSURE,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       3,
                                                       BAROMETER14_PROC_TIME_PRESS_MS );
    *meas_status = data_buf[ 0 ];

    /* Pin[kPa] = Pserial / 16 -> datasheet page 9 */
    *pressure = ( float ) ( int16_t ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] ) / BAROMETER14_PRESS_RES;

    return error_flag;
}

err_t barometer14_measure_accel ( barometer14_t *ctx, uint8_t *meas_status, float *acceleration )
{
    uint8_t data_buf[ 3 ] = { 0 };

    /* Send 'Measure Acceleration command' (0xA9):
     *    Parameters: None.
     *    Response[3 bytes]: 1 byte  (data_buf[0])    -> Status
     *                       2 bytes (data_buf[1..2]) -> Acceleration data (16-bit two's complement,
     *                                                   MSB first, resolution 16 LSB = 1 g). */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_MEASURE_ACCELERATION,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       3,
                                                       BAROMETER14_PROC_TIME_ACC_MS );
    *meas_status  = data_buf[ 0 ];

    /* ain[kPa] = aserial / 16 -> datasheet page 11 */
    *acceleration = ( float ) ( int16_t ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] ) / BAROMETER14_ACC_RES;

    return error_flag;
}

err_t barometer14_measure_temp ( barometer14_t *ctx, uint8_t *meas_status, float *temperature )
{
    uint8_t data_buf[ 3 ] = { 0 };

    /* Send 'Measure Temperature command' (0xAA):
     *    Parameters: None.
     *    Response[3 bytes]: 1 byte  (data_buf[0])    -> Status
     *                       2 bytes (data_buf[1..2]) -> Temperature data (16-bit two's complement,
     *                                                   MSB first, resolution 128 LSB = 1 degC). */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_MEASURE_TEMPERATURE,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       3,
                                                       BAROMETER14_PROC_TIME_TEMP_MS );
    *meas_status = data_buf[ 0 ];

    /* Tin[kPa] = Tserial / 16 -> datasheet page 13 */
    *temperature = ( float ) ( int16_t ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] ) / BAROMETER14_TEMP_RES;

    return error_flag;
}

err_t barometer14_read_id ( barometer14_t *ctx, uint32_t *sensor_id, uint16_t *product_code )
{
    uint8_t data_buf[ 6 ] = { 0 };

    /* Send 'Read ID command' (0xC3):
     *    Parameters: None.
     *    Response[6 bytes]: 4 bytes (data_buf[0..3]) -> Sensor ID (MSB first)
     *                       2 bytes (data_buf[4..5]) -> Product Code (MSB first) */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_READ_ID,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       6,
                                                       BAROMETER14_PROC_TIME_READ_ID_MS );

    *sensor_id    = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                    ( ( uint32_t ) data_buf[ 2 ] <<  8 ) | ( ( uint32_t ) data_buf[ 3 ] );
    *product_code = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];

    return error_flag;
}

err_t barometer14_self_test ( barometer14_t *ctx, uint8_t config, uint8_t *test_status )
{
    uint8_t data_buf[ 1 ] = { 0 };
    uint16_t delay_ms = 0;

    /* Check if self-test with memory check is requested */
    if ( BAROMETER14_SELF_TEST_WITH_MEM == config )
    {
        delay_ms = BAROMETER14_PROC_TIME_SELF_TEST_MEM_MS;
    }
    else
    {
        delay_ms = BAROMETER14_PROC_TIME_SELF_TEST_MS;
    }

    /* Send 'Self-Test command' (0xC5):
     *    Parameter[1 byte]:  =0x00 -> Self-test without memory check (approximately 2.4 ms)
     *                       !=0x00 -> Self-test with memory check (approximately 280 ms)
     *    Response[1 byte]: bit[0] = 1 -> Internal memory CRC check failed
     *                      bit[1] = 1 -> Signal path check failed
     *                      bit[2] = 1 -> Check of internal RC oscillators failed */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_SELF_TEST,
                                                       &config,
                                                       1,
                                                       data_buf,
                                                       1,
                                                       delay_ms );
    *test_status = data_buf[ 0 ];

    return error_flag;
}

err_t barometer14_soft_reset ( barometer14_t *ctx )
{
    /* Send 'Soft Reset command' (0xC7):
     *    Parameters: None.
     *    Response: None.
     * After soft reset, communication interface selection procedure is required. */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_TRIGGER_SOFTRESET,
                                                       NULL,
                                                       0,
                                                       NULL,
                                                       0,
                                                       BAROMETER14_PROC_TIME_STATUS_MS );
    Delay_10ms( );

    return error_flag;
}

err_t barometer14_read_status ( barometer14_t *ctx,
                                uint8_t clear,
                                uint32_t *dev_status,
                                uint16_t *auto_status,
                                uint8_t *meas_status,
                                uint8_t *last_cfg_id )
{
    uint8_t data_buf[ 7 ] = { 0 };

    /* Send 'Read Device Status Register command' (0xD8):
     *    Parameter[1 byte]: 0xAC -> Read and clear status register and ALERT pin.
     *                       0x53 -> Read without clearing.
     *    Response[7 bytes]:
     *       3 bytes (data_buf[0..2]) -> Device Status Register content (MSB first)
     *       2 bytes (data_buf[3..4]) -> Autonomous Status Register content (MSB first)
     *       1 byte  (data_buf[5])    -> Measurement Status Register content
     *       1 byte  (data_buf[6])    -> Last Configuration ID */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_READ_STATUS_REG,
                                                       &clear,
                                                       1,
                                                       data_buf,
                                                       7,
                                                       BAROMETER14_PROC_TIME_STATUS_MS );

    *dev_status  = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint32_t ) data_buf[ 1 ] << 8 ) |
                   ( ( uint32_t ) data_buf[ 2 ] );
    *auto_status = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    *meas_status = data_buf[ 5 ];
    *last_cfg_id = data_buf[ 6 ];

    return error_flag;
}

err_t barometer14_lock_ser_interface ( barometer14_t *ctx, uint8_t type, uint8_t *set_status )
{
    uint8_t data_buf[ 1 ] = { 0 };

    /* Send 'Set Serial Interface command' (0xD0):
     *    Parameter[1 byte]: 0 -> I2C selected (with spike filter disabled)
     *                       1 -> SPI selected
     *                       2 -> I2C selected (with spike filter enabled)
     *    Result[1 byte]: bit[1] = 1 -> invalid parameter sent
     *                    bit[3] = 1 -> already locked (not an error)
     *                    bit[7] = 1 -> flash write failed */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_SET_SERIAL_INTERFACE,
                                                       &type,
                                                       1,
                                                       data_buf,
                                                       1,
                                                       BAROMETER14_PROC_TIME_SET_SERIAL_MS );
    *set_status = data_buf[ 0 ];

    return error_flag;
}

err_t barometer14_enter_auto_state ( barometer14_t *ctx, uint8_t config_id )
{
    /* Note: the caller must clear the Device Status Register with
     * barometer14_read_status( BAROMETER14_STATUS_CLEAR ) before calling this function. */
    uint8_t param = config_id & BAROMETER14_CONFIG_ID_MASK;

    /* Send 'Enter Autonomous State command' (0xC1):
     *    Parameter[1 byte]: Configuration ID (bits 4:0)
     *    Response[0 bytes]: None */
    return barometer14_send_cmd_then_read( ctx, 
                                           BAROMETER14_CMD_ENTER_AUTONOMOUS_STATE,
                                           &param,
                                           1,
                                           NULL,
                                           0,
                                           BAROMETER14_PROC_TIME_STATUS_MS );
}

err_t barometer14_enter_sleep ( barometer14_t *ctx )
{
    /* Send 'Enter Sleep command' (0xC2):
     *    Parameters: None.
     *    Response: None. */
    return barometer14_send_cmd_then_read( ctx,
                                           BAROMETER14_CMD_ENTER_SLEEP,
                                           NULL,
                                           0,
                                           NULL,
                                           0,
                                           BAROMETER14_PROC_TIME_STATUS_MS );
}

err_t barometer14_read_as_history ( barometer14_t *ctx, uint8_t *length, uint8_t *ids )
{
    uint8_t data_buf[ 17 ] = { 0 };

    /* Send 'Read Autonomous State History command' (0xA0):
     *    Parameters: None.
     *    Response[17 bytes]: 1 byte  (data_buf[0])     -> Number of valid entries N (max 16).
     *                        N bytes (data_buf[1..N])  -> IDs of stored AS configs, oldest first. */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_READ_AS_HISTORY,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       17,
                                                       BAROMETER14_PROC_TIME_AS_HISTORY_MS );
    *length = data_buf[ 0 ];

    /* Load IDs */
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        ids[ cnt ] = data_buf[ cnt + 1 ];
    }

    return error_flag;
}

err_t barometer14_read_as_press_buf ( barometer14_t *ctx, uint8_t *length, float *pressure )
{
    uint8_t data_buf[ 33 ] = { 0 };

    /* Send 'Read Autonomous State Pressure Buffer command' (0xA1):
     *    Parameters: None.
     *    Response[33 bytes]: 1 byte   (data_buf[0])      -> Number of valid entries N (max 16).
     *                        2N bytes (data_buf[1..2N])  -> Pressure data, oldest first
     *                                                       (16-bit two's complement, MSB first,
     *                                                        resolution 16 LSB = 1 kPa). */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_READ_AS_PRESS_BUF,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       33,
                                                       BAROMETER14_PROC_TIME_AS_BUFFER_MS );
    *length = data_buf[ 0 ];

    /* Load pressure data */
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        pressure[ cnt ] = ( float ) ( int16_t ) ( ( ( uint16_t ) data_buf[ 1 + ( cnt * 2 ) ] << 8 ) |
                                                    data_buf[ 2 + ( cnt * 2 ) ] ) / BAROMETER14_PRESS_RES;
    }

    return error_flag;
}

err_t barometer14_read_as_accel_buf ( barometer14_t *ctx, uint8_t *length, float *acceleration )
{
    uint8_t data_buf[ 33 ] = { 0 };

    /* Send 'Read Autonomous State Acceleration Buffer command' (0xA2):
     *    Parameters: None.
     *    Response[33 bytes]: 1 byte   (data_buf[0])      -> Number of valid entries N (max 16).
     *                        2N bytes (data_buf[1..2N])  -> Acceleration data, oldest first
     *                                                       (16-bit two's complement, MSB first,
     *                                                        resolution 16 LSB = 1 g). */
    err_t error_flag = barometer14_send_cmd_then_read( ctx,
                                                       BAROMETER14_CMD_READ_AS_ACC_BUF,
                                                       NULL,
                                                       0,
                                                       data_buf,
                                                       33,
                                                       BAROMETER14_PROC_TIME_AS_BUFFER_MS );
    *length = data_buf[ 0 ];

    /* Load acceleration data */
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        acceleration[ cnt ] = ( float ) ( int16_t ) ( ( ( uint16_t ) data_buf[ 1 + ( cnt * 2 ) ] << 8 ) |
                                                        data_buf[ 2 + ( cnt * 2 ) ] ) / BAROMETER14_ACC_RES;
    }

    return error_flag;
}

err_t barometer14_save_as_config ( barometer14_t *ctx, barometer14_as_cfg_t *as_cfg, uint8_t *save_status )
{
    /* All Autonomous State configuration values:
     *    data_buf[0]      : Configuration ID of the Autonomous State Configuration (bits 4:0).
     *    data_buf[1]      : Precounter value in milliseconds.
     *    data_buf[2..3]   : Postcounter of the Autonomous State Timer (MSB first).
     *    data_buf[4]      : Timeout value (0 = disabled, timeout after 2^timeout AS timer periods).
     *    data_buf[5..22]  : High-priority measurement configuration.
     *    data_buf[23..40] : Low-priority measurement configuration. */
    uint8_t data_buf[ 41 ] = { 0 };

    data_buf[ 0 ] = as_cfg->confg_id & BAROMETER14_CONFIG_ID_MASK;
    data_buf[ 1 ] = as_cfg->precounter;
    data_buf[ 2 ] = ( uint8_t ) ( as_cfg->postcounter >> 8 );
    data_buf[ 3 ] = ( uint8_t ) ( as_cfg->postcounter & 0xFF );
    data_buf[ 4 ] = as_cfg->timeout;

    /* Serialize high-priority and low-priority measurement configurations into the buffer. */
    barometer14_ser_meas_cfg( &as_cfg->meas_1, &data_buf[ 5 ] );
    barometer14_ser_meas_cfg( &as_cfg->meas_2, &data_buf[ 23 ] );

    uint8_t response[ 1 ] = { 0 };

    /* Send Save AS Config command (0xD4):
     *    Parameters[41 bytes]: Autonomous State configuration data as described above.
     *    Result[1 byte]: bit[0] = 1 -> Parameter out of range, adjusted. Configuration still saved.
     *                    bit[1] = 1 -> Invalid configuration. Configuration NOT saved.
     *                    bit[2] = 1 -> Existing config was corrupt. New one saved but may not be reliable.
     *                    bit[6] = 1 -> Flash write limit exceeded (100 writes per block 32byte block). May not be reliable.
     *                    bit[7] = 1 -> Flash write failed. Configuration NOT saved. */
    err_t error_flag = barometer14_send_cmd_then_read( ctx, 
                                                       BAROMETER14_CMD_SAVE_AS_CONFIG,
                                                       data_buf, 
                                                       41, 
                                                       response, 
                                                       1,
                                                       BAROMETER14_PROC_TIME_SAVE_AS_CFG_MS );
    *save_status = response[ 0 ];

    return error_flag;
}

err_t barometer14_read_as_config ( barometer14_t *ctx, uint8_t confg_id, barometer14_as_cfg_t *as_cfg )
{
    uint8_t param = confg_id & BAROMETER14_CONFIG_ID_MASK;
    uint8_t data_buf[ 42 ] = { 0 };

    /* Send Read AS Config command (0xD5):
     *    Parameter[1 byte]: Configuration ID of the Autonomous State Configuration (bits 4:0).
     *    Result[42 bytes]:  Status(1) + ID(1) + Precounter(1) + Postcounter(2) + Timeout(1)
     *                       + Meas_1(18) + Meas_2(18) */
    err_t error_flag = barometer14_send_cmd_then_read( ctx, 
                                                       BAROMETER14_CMD_READ_AS_CONFIG,
                                                       &param, 
                                                       1, 
                                                       data_buf, 
                                                       42,
                                                       BAROMETER14_PROC_TIME_READ_AS_CFG_MS );
    if ( BAROMETER14_OK == error_flag )
    {
        /* data_buf[0] = CRC status of the stored config (0 = valid) */
        as_cfg->confg_id    = data_buf[ 1 ] & BAROMETER14_CONFIG_ID_MASK;
        as_cfg->precounter  = data_buf[ 2 ];
        as_cfg->postcounter = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
        as_cfg->timeout     = data_buf[ 5 ];
        barometer14_deser_meas_cfg( &data_buf[ 6 ],  &as_cfg->meas_1 );
        barometer14_deser_meas_cfg( &data_buf[ 24 ], &as_cfg->meas_2 );
    }

    return error_flag;
}

err_t barometer14_write_flash ( barometer14_t *ctx, uint16_t address, uint8_t *data_in, uint8_t *write_status )
{
    /* KP497 has a 3kB internal flash memory available for users data.
     * Data is stored in 32byte blocks.
     * Write frame : Keyword(0x9D) | 32Byte block address(2bytes) | Data(32bytes)
     * Return : Status (1 byte) */
    uint8_t data_buf[ 35 ] = { 0 };

    data_buf[ 0 ] = BAROMETER14_DATA_WRITE_KEYWORD;
    data_buf[ 1 ] = ( uint8_t ) ( address >> 8 );
    data_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );

    /* Load data bytes */
    for ( uint8_t cnt = 0; cnt < BAROMETER14_DATA_LINE_BYTES; cnt++ )
    {
        data_buf[ cnt + 3 ] = data_in[ cnt ];
    }

    uint8_t response[ 1 ] = { 0 };

    /* Send 'Write data line' command(0xB1):
     *    Parameters[35 bytes]: Keyword(0x9D) | 32Byte block address(2bytes) | Data(32bytes).
     *    Response[1 byte]: Status -> bit[0] = 0 -> write successful. */
    err_t error_flag = barometer14_send_cmd_then_read( ctx, 
                                                       BAROMETER14_CMD_WRITE_DATA_LINE,
                                                       data_buf, 
                                                       35, 
                                                       response, 
                                                       1,
                                                       BAROMETER14_PROC_TIME_WRITE_DATA_MS );
    *write_status = response[ 0 ];

    return error_flag;
}

err_t barometer14_read_flash ( barometer14_t *ctx, uint16_t address, uint8_t *data_out, uint8_t *read_status )
{
    /* Reads 32byte data users data from sensors internal flash */
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( address >> 8 ), ( uint8_t ) ( address & 0xFF ) };
    uint8_t response[ 33 ] = { 0 };

    /* Send 'Read data line' command(0xB0):
     *    Parameters[2 bytes]: 32Byte block address(2bytes).
     *    Response[33 bytes]: Status(1byte) + Data(32bytes) */
    err_t error_flag = barometer14_send_cmd_then_read( ctx, 
                                                       BAROMETER14_CMD_READ_DATA_LINE,
                                                       data_buf, 
                                                       2, 
                                                       response, 
                                                       33,
                                                       BAROMETER14_PROC_TIME_READ_DATA_MS );
    *read_status = response[ 0 ];

    /* Load response data */
    for ( uint8_t cnt = 0; cnt < BAROMETER14_DATA_LINE_BYTES; cnt++ )
    {
        data_out[ cnt ] = response[ cnt + 1 ];
    }

    return error_flag;
}

uint8_t barometer14_get_alt ( barometer14_t *ctx )
{
    /* The ALERT pin is HIGH when the device has entered On State or when an Autonomous State
     * threshold is violated. */
    return digital_in_read( &ctx->alt );
}

uint8_t barometer14_get_wkp ( barometer14_t *ctx )
{
    /* The WKP pin is LOW while the device is processing a command and HIGH when ready. */
    return digital_in_read( &ctx->wkp );
}

static uint16_t barometer14_calculate_crc ( uint8_t *data_in, uint16_t len )
{
    /* Start with the CCITT preload value (0xFFFF) instead of zero.
     * This makes the algorithm sensitive to leading zero bytes. */
    uint16_t crc = CRC16_PRELOAD;

    for ( uint16_t byte_idx = 0; byte_idx < len; byte_idx++ )
    {
        /* Feed the next byte into the top 8 bits of the CRC register.
         * XOR merges the new byte with the current running checksum. */
        crc ^= ( ( uint16_t ) data_in[ byte_idx ] << 8 );

        /* Process all 8 bits of the byte one at a time. */
        for ( uint8_t bit_idx = 0; bit_idx < 8; bit_idx++ )
        {
            if ( crc & 0x8000 )
            {
                /* MSB is 1: shift left and XOR with the CCITT polynomial (0x1021).
                 * This is equivalent to polynomial division in GF(2) arithmetic. */
                crc = ( crc << 1 ) ^ CRC16_POLYNOMIAL;
            }
            else
            {
                /* MSB is 0: just shift left, no XOR needed. */
                crc <<= 1;
            }
        }
    }
    return crc;
}

static uint8_t barometer14_is_error_code ( uint8_t first_byte )
{
    if ( ( BAROMETER14_RESP_EMPTY_BUFFER == first_byte ) ||
         ( BAROMETER14_RESP_INVALID_CMD  == first_byte ) ||
         ( BAROMETER14_RESP_CRC_FAIL     == first_byte ) ||
         ( BAROMETER14_RESP_COLLISION    == first_byte ) ||
         ( BAROMETER14_RESP_OVERFLOW     == first_byte ) )
    {
        return 1;
    }
    return 0;
}

static void barometer14_ser_meas_cfg ( barometer14_meas_cfg_t *meas_cfg, uint8_t *buf )
{
    /* Load all Measurement configuration values into the buffer for transmission:
     *    Sensor       : 0 -> Pressure, 1 -> Acceleration, 0xFF -> Disabled.
     *    Postcounter  : Number of times that the Autonomous State Timer needs to elapse
     *                   between each acquisition and threshold evaluation of the measurement.
     *    Rec_samples  : Number of samples to be acquired during Acceleration Recording (MSB first).
     *    Threshold configuration for each of the 2 thresholds:
     *       - Config      : Enable/disable lower and upper threshold, set the threshold type
     *                       (absolute, rate of change, relative to On State, relative to config start).
     *       - Trans_Lower : Action taken when lower threshold is violated (bits [7:6]) and
     *                       target configuration ID for config change action (bits [4:0]).
     *       - Thrld_Lower : Lower threshold value (MSB first, resolution 16 LSB = 1 kPa or 1 g).
     *                       Cast to uint16_t before shift to avoid undefined behavior on signed types.
     *       - Trans_Upper : Action taken when upper threshold is violated (bits [7:6]) and
     *                       target configuration ID for config change action (bits [4:0]).
     *       - Thrld_Upper : Upper threshold value (MSB first, resolution 16 LSB = 1 kPa or 1 g).
     *                       Cast to uint16_t before shift to avoid undefined behavior on signed types. */
    buf[ 0 ]  = meas_cfg->sensor;
    buf[ 1 ]  = meas_cfg->postcounter;
    buf[ 2 ]  = ( uint8_t ) ( meas_cfg->rec_samples >> 8 );
    buf[ 3 ]  = ( uint8_t ) ( meas_cfg->rec_samples & 0xFF );
    buf[ 4 ]  = meas_cfg->thr_1.config;
    buf[ 5 ]  = meas_cfg->thr_1.trans_lower;
    buf[ 6 ]  = ( uint8_t ) ( ( uint16_t ) meas_cfg->thr_1.thrld_lower >> 8 );
    buf[ 7 ]  = ( uint8_t ) ( meas_cfg->thr_1.thrld_lower & 0xFF );
    buf[ 8 ]  = meas_cfg->thr_1.trans_upper;
    buf[ 9 ]  = ( uint8_t ) ( ( uint16_t ) meas_cfg->thr_1.thrld_upper >> 8 );
    buf[ 10 ] = ( uint8_t ) ( meas_cfg->thr_1.thrld_upper & 0xFF );
    buf[ 11 ] = meas_cfg->thr_2.config;
    buf[ 12 ] = meas_cfg->thr_2.trans_lower;
    buf[ 13 ] = ( uint8_t ) ( ( uint16_t ) meas_cfg->thr_2.thrld_lower >> 8 );
    buf[ 14 ] = ( uint8_t ) ( meas_cfg->thr_2.thrld_lower & 0xFF );
    buf[ 15 ] = meas_cfg->thr_2.trans_upper;
    buf[ 16 ] = ( uint8_t ) ( ( uint16_t ) meas_cfg->thr_2.thrld_upper >> 8 );
    buf[ 17 ] = ( uint8_t ) ( meas_cfg->thr_2.thrld_upper & 0xFF );
}

static void barometer14_deser_meas_cfg ( uint8_t *buf, barometer14_meas_cfg_t *meas_cfg )
{
    /* Load all Measurement configuration values from received buffer to configuration structure */
    meas_cfg->sensor            = buf[ 0 ];
    meas_cfg->postcounter       = buf[ 1 ];
    meas_cfg->rec_samples       = ( ( uint16_t ) buf[ 2 ] << 8 ) | buf[ 3 ];
    meas_cfg->thr_1.config      = buf[ 4 ];
    meas_cfg->thr_1.trans_lower = buf[ 5 ];
    meas_cfg->thr_1.thrld_lower = ( int16_t ) ( ( ( uint16_t ) buf[ 6 ] << 8 ) | buf[ 7 ] );
    meas_cfg->thr_1.trans_upper = buf[ 8 ];
    meas_cfg->thr_1.thrld_upper = ( int16_t ) ( ( ( uint16_t ) buf[ 9 ] << 8 ) | buf[ 10 ] );
    meas_cfg->thr_2.config      = buf[ 11 ];
    meas_cfg->thr_2.trans_lower = buf[ 12 ];
    meas_cfg->thr_2.thrld_lower = ( int16_t ) ( ( ( uint16_t ) buf[ 13 ] << 8 ) | buf[ 14 ] );
    meas_cfg->thr_2.trans_upper = buf[ 15 ];
    meas_cfg->thr_2.thrld_upper = ( int16_t ) ( ( ( uint16_t ) buf[ 16 ] << 8 ) | buf[ 17 ] );
}

static err_t barometer14_spi_write ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    /* Wire frame: CMD byte | Parameters (>= 0 bytes) | CRC_MSB | CRC_LSB */
    uint8_t data_buf[ 256 ] = { 0 };

    /* Load the command byte */
    data_buf[ 0 ] = cmd;

    /* Load the parameter bytes, if len = 0 -> this iteration is skipped */
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    
    /* CRC covers CMD byte and all parameter bytes */
    uint16_t crc = barometer14_calculate_crc( data_buf, len + 1 );

    /* First send CRC MSB and then CRC LSB */
    data_buf[ len + 1 ] = ( uint8_t ) ( crc >> 8 );
    data_buf[ len + 2 ] = ( uint8_t ) ( crc & 0xFF );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, len + 3 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t barometer14_spi_read ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    /* Wire frame : 0x6C trigger | CMD_echo byte | Results (>= 0 bytes) | CRC_MSB | CRC_LSB */
    uint8_t read_trigger = SPI_READ_TRIGGER;
    uint8_t data_buf[ 256 ] = { 0 };

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &read_trigger, 1, data_buf, len + 3 );
    spi_master_deselect_device( ctx->chip_select );

    if ( BAROMETER14_OK != error_flag )
    {
        return BAROMETER14_ERROR;
    }

    /* Check if error was received.
     * First byte to receive is always either CMD echo byte or ERROR code.
     * Error frame : [ Error_code (1 byte) | CRC_MSB | CRC_LSB ] */
    if ( barometer14_is_error_code( data_buf[ 0 ] ) )
    {
        return BAROMETER14_ERROR;
    }

    /* In case error was caused by something not covered by the error checking codes. */
    if ( data_buf[ 0 ] != cmd )
    {
        return BAROMETER14_ERROR;
    }

    /* CRC_MSB = data_buf[ len + 1 ]
     * CRC_LSB = data_buf[ len + 2 ] */
    uint16_t recv_crc = ( ( uint16_t ) data_buf[ len + 1 ] << 8 ) | data_buf[ len + 2 ];
    uint16_t calc_crc = barometer14_calculate_crc( data_buf, len + 1 );

    /* Compare received and calculated CRC */
    if ( recv_crc != calc_crc )
    {
        return BAROMETER14_ERROR;
    }

    /* Skip command echo byte at index 0 */
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_out[ cnt ] = data_buf[ cnt + 1 ];
    }

    return BAROMETER14_OK;
}

static err_t barometer14_i2c_write ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    /* Wire frame: S | slave_addr + W | A | Command byte (1 byte) | A | Parameters (>= 0 bytes) | A | CRC_MSB | A | CRC_LSB | A | P */
    uint8_t data_buf[ 256 ] = { 0 };

    /* Load the command byte */
    data_buf[ 0 ] = cmd;

    /* Load the parameter bytes, if len = 0 -> this iteration is skipped */
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }

    /* CRC covers CMD byte and all parameter bytes */
    uint16_t crc = barometer14_calculate_crc( data_buf, len + 1 );
    data_buf[ len + 1 ] = ( uint8_t ) ( crc >> 8 );
    data_buf[ len + 2 ] = ( uint8_t ) ( crc & 0xFF );

    return i2c_master_write( &ctx->i2c, data_buf, len + 3 );
}

static err_t barometer14_i2c_read ( barometer14_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    /* Wire frame: S | slave_addr + R | A | CMD_echo (1 byte) | A | Results (>= 0 bytes) | A | CRC_MSB | A | CRC_LSB | NA | P
     * Does not use repeated start -> waiting until WKP is high between WRITE and READ is necessary. */
    uint8_t data_buf[ 256 ] = { 0 };

    err_t error_flag = i2c_master_read( &ctx->i2c, data_buf, len + 3 );
    if ( BAROMETER14_OK != error_flag )
    {
        return BAROMETER14_ERROR;
    }

    /* Check if error was received.
     * First byte to receive is always either CMD echo byte or ERROR code.
     * Error frame : [ Error_code (1 byte) | CRC_MSB | CRC_LSB ] */
    if ( barometer14_is_error_code( data_buf[ 0 ] ) )
    {
        return BAROMETER14_ERROR;
    }

    /* In case error was caused by something not covered by the error checking codes. */
    if ( data_buf[ 0 ] != cmd )
    {
        return BAROMETER14_ERROR;
    }

    /* CRC_MSB = data_buf[ len + 1 ]
     * CRC_LSB = data_buf[ len + 2 ] */
    uint16_t recv_crc = ( ( uint16_t ) data_buf[ len + 1 ] << 8 ) | data_buf[ len + 2 ];
    uint16_t calc_crc = barometer14_calculate_crc( data_buf, len + 1 );

    /* Compare received and calculated CRC */
    if ( recv_crc != calc_crc )
    {
        return BAROMETER14_ERROR;
    }

    /* Skip command echo byte at index 0 */
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_out[ cnt ] = data_buf[ cnt + 1 ];
    }

    return BAROMETER14_OK;
}

static err_t barometer14_send_cmd_then_read ( barometer14_t *ctx,
                                              uint8_t cmd,
                                              uint8_t *data_in,
                                              uint8_t params_len,
                                              uint8_t *data_out,
                                              uint8_t response_len,
                                              uint16_t spi_delay_ms )
{
    /* Command frame:
     *    Write : [ CMD (1 byte) | Parameters (>= 0 bytes) | CRC_MSB | CRC_LSB ]
     *    Read : [ 0x6C trigger | CMD_echo (1 byte) | Results (>= 0 bytes) | CRC_MSB | CRC_LSB ]
     *    Received Error : [ Error_code (1 byte) | CRC_MSB | CRC_LSB ] */

    /* Send the command with optional parameters (params_len = 0 if no parameters) */
    err_t error_flag = ctx->write_f( ctx, cmd, data_in, params_len );
    if ( BAROMETER14_OK != error_flag )
    {
        return BAROMETER14_ERROR;
    }

    /* Wait for BUSY to clear.
     * After the write, KP497 pulls NCS/WAKEUP/BUSY LOW while processing received data.
     * We wait until the pin returns HIGH before reading the response.
     *
     * I2C mode: WKP is on a separate pin (MikroBUS PWM) - poll it directly.
     * SPI mode: Since NCS/WAKEUP/BUSY is mapped to MikroBUS CS, a specific
     *           amount of wait time defined by the user manual is necessary
     *           (page 39, table 28). */
    if ( BAROMETER14_DRV_SEL_I2C == ctx->drv_sel )
    {
        /* Allow the device time to assert the WKP/BUSY pin LOW after the I2C STOP condition. */
        Delay_1ms( );
        
        /* Poll the WKP pin */
        uint32_t timeout = BAROMETER14_BUSY_TIMEOUT_MS;
        while ( !digital_in_read( &ctx->wkp ) )
        {
            Delay_1ms( );
            if ( 0 == --timeout )
            {
                return BAROMETER14_ERROR;
            }
        }
    }
    else
    {
        for ( uint16_t cnt = 0; cnt < spi_delay_ms; cnt++ )
        {
            Delay_1ms( );
        }
     }

    /* Read response if a buffer was provided */
    if ( NULL != data_out )
    {
        error_flag = ctx->read_f( ctx, cmd, data_out, response_len );
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END

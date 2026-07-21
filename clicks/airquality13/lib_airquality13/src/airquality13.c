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
 * @file airquality13.c
 * @brief Air Quality 13 Click Driver.
 */

#include "airquality13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                            0x00

/**
 * @brief Maximum size of the I2C TX buffer used for BMV080 write transactions.
 * @details Definition of the maximum size of the I2C TX buffer used for BMV080 write transactions.
 */
#define AIRQUALITY13_I2C_TX_BUF_SIZE     256

/**
 * @brief Air Quality 13 SPI read function.
 * @details This function is a callback function called by the Bosch BMV080 SDK
 * to perform a SPI read transaction.
 * @param[in] handle : Pointer to the airquality13_t context.
 * @param[in] header : 16-bit transfer header.
 * @param[out] payload : Buffer for received 16-bit words.
 * @param[in] payload_length : Number of 16-bit words to receive.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t airquality13_spi_read ( bmv080_sercom_handle_t handle,
                                      uint16_t header,
                                      uint16_t *payload,
                                      uint16_t payload_length );

/**
 * @brief Air Quality 13 SPI write function.
 * @details This function is a callback function called by the Bosch BMV080 SDK
 * to perform a SPI write transaction.
 * @param[in] handle : Pointer to the airquality13_t context.
 * @param[in] header : 16-bit transfer header.
 * @param[in] payload : Buffer of 16-bit words to transmit.
 * @param[in] payload_length : Number of 16-bit words to transmit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t airquality13_spi_write ( bmv080_sercom_handle_t handle,
                                       uint16_t header,
                                       const uint16_t *payload,
                                       uint16_t payload_length );

/**
 * @brief Air Quality 13 I2C read function.
 * @details This function is a callback function called by the Bosch BMV080 SDK
 * to perform an I2C read transaction.
 * @param[in] handle : Pointer to the airquality13_t context.
 * @param[in] header : 16-bit transfer header.
 * @param[out] payload : Buffer for received 16-bit words.
 * @param[in] payload_length : Number of 16-bit words to receive.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t airquality13_i2c_read ( bmv080_sercom_handle_t handle,
                                      uint16_t header,
                                      uint16_t *payload,
                                      uint16_t payload_length );

/**
 * @brief Air Quality 13 I2C write function.
 * @details This function is a callback function called by the Bosch BMV080 SDK
 * to perform an I2C write transaction.
 * @param[in] handle : Pointer to the airquality13_t context.
 * @param[in] header : 16-bit transfer header.
 * @param[in] payload : Buffer of 16-bit words to transmit.
 * @param[in] payload_length : Number of 16-bit words to transmit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t airquality13_i2c_write ( bmv080_sercom_handle_t handle,
                                       uint16_t header,
                                       const uint16_t *payload,
                                       uint16_t payload_length );

/**
 * @brief Air Quality 13 delay function.
 * @details This function is a callback function called by the Bosch BMV080 SDK
 * to insert a delay in milliseconds.
 * @param[in] duration_ms : Delay duration in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t airquality13_delay ( uint32_t duration_ms );

/**
 * @brief Air Quality 13 data ready function.
 * @details This function is a callback function called by the Bosch BMV080 SDK 
 * whenever a new PM measurement is available. Copies all output fields into the 
 * airquality13_data_t structure passed via callback_parameters and sets the data_ready flag.
 * @param[in] output : BMV080 output structure with PM concentration values.
 * @param[in,out] params : Pointer to airquality13_data_t.
 * @return None.
 * @note None.
 */
static void airquality13_data_ready_cb ( bmv080_output_t output, void *params );

void airquality13_cfg_setup ( airquality13_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRQUALITY13_DEVICE_ADDRESS;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = AIRQUALITY13_DRV_SEL_I2C;
}

void airquality13_drv_interface_sel ( airquality13_cfg_t *cfg, airquality13_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t airquality13_init ( airquality13_t *ctx, airquality13_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->bmv080_handle = NULL;
   
    bmv080_callback_read_t  bmv080_read;  
    bmv080_callback_write_t bmv080_write;

    if ( AIRQUALITY13_DRV_SEL_I2C == ctx->drv_sel ) 
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

        bmv080_read  = airquality13_i2c_read;
        bmv080_write = airquality13_i2c_write;
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

        bmv080_read  = airquality13_spi_read;
        bmv080_write = airquality13_spi_write;
    }

    digital_in_init( &ctx->irq, cfg->irq );

    /* Open the Bosch BMV080 SDK handle.
     * ctx itself is passed as the sercom_handle so that the static callbacks
     * can recover the SPI/I2C peripheral handles. */
    if ( E_BMV080_OK != bmv080_open( &ctx->bmv080_handle,
                                     ( bmv080_sercom_handle_t ) ctx,
                                     bmv080_read,
                                     bmv080_write,
                                     airquality13_delay ) )
    {
        return AIRQUALITY13_ERROR;
    }

    return AIRQUALITY13_OK;
}

err_t airquality13_default_cfg ( airquality13_t *ctx ) 
{
    float integration_time = AIRQUALITY13_DEFAULT_INTEGRATION_TIME;

    /* bmv080_reset resets a sensor unit by performing a reset of the hardware and software. */
    if ( E_BMV080_OK != bmv080_reset( ctx->bmv080_handle ) )
    {
        return AIRQUALITY13_ERROR;
    }

    /* Give sensor enough time to initialize */
    Delay_1sec( );

    /* Measurement window for computing PM value set to 10s. */
    if ( E_BMV080_OK != bmv080_set_parameter( ctx->bmv080_handle, "integration_time", &integration_time ) )
    {
        return AIRQUALITY13_ERROR;
    }

    /* High precision algorithm for maximum measurement accuracy. */
    if ( AIRQUALITY13_OK != airquality13_set_meas_alg( ctx, AIRQUALITY13_MEAS_ALG_HIGH_PRECISION ) )
    {
        return AIRQUALITY13_ERROR;
    }

    return airquality13_start_measurement( ctx );
}

err_t airquality13_get_sensor_id ( airquality13_t *ctx, char *sensor_id )
{
    if ( NULL == sensor_id )
    {
        return AIRQUALITY13_ERROR;
    }
    
    /* Sensor ID is a 13-character string. */
    if ( E_BMV080_OK != bmv080_get_sensor_id( ctx->bmv080_handle, sensor_id ) )
    {
        return AIRQUALITY13_ERROR;
    }

    return AIRQUALITY13_OK;
}

err_t airquality13_start_measurement ( airquality13_t *ctx )
{   
    /* Start particle measurement in continuous mode -> new sensor data available every 1.03 seconds.
     * Sensor stays in measurement mode until bmv080_stop_measurement is called. */
    if ( E_BMV080_OK != bmv080_start_continuous_measurement( ctx->bmv080_handle ) )
    {
        return AIRQUALITY13_ERROR;
    }
    return AIRQUALITY13_OK;
}

err_t airquality13_stop_measurement ( airquality13_t *ctx )
{
    if ( E_BMV080_OK != bmv080_stop_measurement( ctx->bmv080_handle ) )
    {
        return AIRQUALITY13_ERROR;
    }
    return AIRQUALITY13_OK;
}

err_t airquality13_serve_interrupt ( airquality13_t *ctx, airquality13_data_t *meas_data )
{
    if ( NULL == meas_data )
    {
        return AIRQUALITY13_ERROR;
    }

    /* Clear the flag before processing so the caller can detect new data. */
    meas_data->data_ready = 0;
    
    /* If a new measurement is available, process it. 
     * SDK will populate the data structure(bmv080_output_t) with the latest measurements
     * and airquality13_data_t->data_ready will be set to 1. */
    if ( E_BMV080_OK != bmv080_serve_interrupt( ctx->bmv080_handle, airquality13_data_ready_cb, ( void* ) meas_data ) )
    {
        return AIRQUALITY13_ERROR;
    }

    return AIRQUALITY13_OK;
}

uint8_t airquality13_get_irq_pin ( airquality13_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

err_t airquality13_set_meas_alg ( airquality13_t *ctx, airquality13_meas_alg_t algorithm )
{
    bmv080_measurement_algorithm_t meas_alg = ( bmv080_measurement_algorithm_t ) algorithm;

    if ( E_BMV080_OK != bmv080_set_parameter( ctx->bmv080_handle, "measurement_algorithm", &meas_alg ) )
    {
        return AIRQUALITY13_ERROR;
    }

    return AIRQUALITY13_OK;
}

static int8_t airquality13_spi_read ( bmv080_sercom_handle_t handle,
                                      uint16_t header,
                                      uint16_t *payload,
                                      uint16_t payload_length )
{
    /* S | header(16 bits) | data0(16bits) | .... dataN(16bits) | P */
    uint8_t header_buf[ 2 ] = { 0 };

    if ( ( NULL == handle ) || ( NULL == payload ) || ( 0 == payload_length ) )
    {
        return -1;
    }
    
    airquality13_t *ctx = ( airquality13_t* ) handle;

    /* Header: 16-bit, MSB first. */
    header_buf[ 0 ] = ( uint8_t ) ( header >> 8 );
    header_buf[ 1 ] = ( uint8_t ) ( header & 0xFF );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, header_buf, 2 );

    /* Read payload_length words (2 bytes each) directly into the payload buffer.
     * The sensor sends data big-endian (MSB first), so bytes land in reverse
     * order relative to the MCU little-endian uint16_t layout. */
    error_flag |= spi_master_read( &ctx->spi, ( uint8_t* ) payload, payload_length * 2 );
    spi_master_deselect_device( ctx->chip_select );

    if ( AIRQUALITY13_OK != error_flag )
    {
        return -1;
    }

    /* Byte-swap each 16bit word: big-endian (wire) → little-endian (host). */
    for ( uint16_t cnt = 0; cnt < payload_length; cnt++ )
    {
        /* Take the address of the cnt-th uint16_t word and view it as a byte array.
         * byte_value[0] = MSB (sensor always sends MSB first)
         * byte_value[1] = LSB */
        uint8_t *byte_value = ( uint8_t* ) &payload[ cnt ];

        /* Swap stored MSB and LSB bytes in payload buffer */
        uint8_t tmp = byte_value[ 0 ];
        byte_value[ 0 ] = byte_value[ 1 ];
        byte_value[ 1 ] = tmp;
    }

    return 0;
}

static int8_t airquality13_spi_write ( bmv080_sercom_handle_t handle,
                                      uint16_t header,
                                      const uint16_t *payload,
                                      uint16_t payload_length )
{
    /* S | header(16 bits) | data0(16bits) | .... dataN(16bits) | P */
    uint8_t header_buf[ 2 ] = { 0 };

    if ( ( NULL == handle ) || ( NULL == payload ) || ( 0 == payload_length ) )
    {
        return -1;
    }

    airquality13_t *ctx = ( airquality13_t* ) handle;
   
    /* Header: 16-bit, MSB first. */
    header_buf[ 0 ] = ( uint8_t ) ( header >> 8 );
    header_buf[ 1 ] = ( uint8_t ) ( header & 0xFF );

    spi_master_select_device( ctx->chip_select );

    err_t error_flag = spi_master_write( &ctx->spi, header_buf, 2 );

    /* Send each payload word MSB first (big-endian on wire). */
    for ( uint16_t cnt = 0; cnt < payload_length; cnt++ )
    {
        uint8_t word_buf[ 2 ] = { ( uint8_t ) ( payload[ cnt ] >> 8 ),
                                  ( uint8_t ) ( payload[ cnt ] & 0xFF ) };
                                  
        error_flag |= spi_master_write( &ctx->spi, word_buf, 2 );
    }

    spi_master_deselect_device( ctx->chip_select );

    if ( AIRQUALITY13_OK != error_flag )
    {
        return -1;
    }

    return 0;
}

static int8_t airquality13_i2c_read ( bmv080_sercom_handle_t handle,
                                     uint16_t header,
                                     uint16_t *payload,
                                     uint16_t payload_length )
{
    /* Does not use repeated start:
     * S | slave_address + w | A | Header MSB | A | Header LSB | A | P 
     * S | slave_address + R | A | Data0 MSB | A | Data0 LSB | A | ... | DataN LSB | NA | P */
    if ( ( NULL == handle ) || ( NULL == payload ) || ( 0 == payload_length ) )
    {
        return -1;
    }

    airquality13_t *ctx = ( airquality13_t* ) handle;
    
    /* R/W flag is coded in the bit15 of the header.
     * 16 bit header left shifted, since the R/W bit has already been passed.
     * Not mentioned in the documentation but in Bosch SDK folder -> Combridge.c example */
    uint16_t header_adjusted = header << 1;
    uint8_t  header_buf[ 2 ] = { ( uint8_t ) ( header_adjusted >> 8 ),
                                 ( uint8_t ) ( header_adjusted & 0xFF ) };

    err_t error_flag = i2c_master_write( &ctx->i2c, header_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, ( uint8_t* ) payload, payload_length * 2 );

    if ( AIRQUALITY13_OK != error_flag )
    {
        return -1;
    }

    /* Byte-swap each 16bit word: big-endian (wire) → little-endian (host). */
    for ( uint16_t cnt = 0; cnt < payload_length; cnt++ )
    {
        /* Take the address of the cnt-th uint16_t word and view it as a byte array.
         * byte_value[0] = MSB (sensor always sends MSB first)
         * byte_value[1] = LSB */
        uint8_t *byte_value = ( uint8_t* ) &payload[ cnt ];

        /* Swap stored MSB and LSB bytes in payload buffer */
        uint8_t tmp = byte_value[ 0 ];
        byte_value[ 0 ] = byte_value[ 1 ];
        byte_value[ 1 ] = tmp;
    }

    return 0;
}

static int8_t airquality13_i2c_write ( bmv080_sercom_handle_t handle,
                                       uint16_t header,
                                       const uint16_t *payload,
                                       uint16_t payload_length )
{
    if ( ( NULL == handle ) || ( NULL == payload ) || ( 0 == payload_length ) )
    {
        return -1;
    }

    airquality13_t *ctx = ( airquality13_t* ) handle;
    
    /* R/W flag is coded in the bit15 of the header.
     * 16 bit header left shifted, since the R/W bit has already been passed.
     * Not mentioned in the documentation but in Bosch SDK folder -> Combridge.c example */
    uint16_t header_adjusted = header << 1;
    uint8_t  tx_buf[ AIRQUALITY13_I2C_TX_BUF_SIZE ];
    uint16_t total_len = 2 + payload_length * 2;

    if ( total_len > AIRQUALITY13_I2C_TX_BUF_SIZE )
    {
        return -1;
    }

    /* Header (2 bytes, MSB first). */
    tx_buf[ 0 ] = ( uint8_t ) ( header_adjusted >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ( header_adjusted & 0xFF );

    /* Payload words in big-endian order (MSB first on wire). */
    for ( uint16_t cnt = 0; cnt < payload_length; cnt++ )
    {
        tx_buf[ 2 + cnt * 2 ] = ( uint8_t ) ( payload[ cnt ] >> 8 );
        tx_buf[ 2 + cnt * 2 + 1 ]  = ( uint8_t ) ( payload[ cnt ] & 0xFF );
    }

    err_t error_flag = i2c_master_write( &ctx->i2c, tx_buf, total_len );
    if ( AIRQUALITY13_OK != error_flag )
    {
        return -1;
    }

    return 0;
}

static int8_t airquality13_delay ( uint32_t duration_ms )
{
    for ( uint32_t cnt = 0; cnt < duration_ms; cnt++ )
    {
        Delay_1ms( );
    }
    return 0;
}

static void airquality13_data_ready_cb ( bmv080_output_t output, void *params )
{
    if ( NULL == params )
    {
        return;
    }

    airquality13_data_t *meas_data = ( airquality13_data_t* ) params;
    
    /* Update the data structure with the latest measurements. */
    meas_data->pm2_5_mass_concentration   = output.pm2_5_mass_concentration;
    meas_data->pm1_mass_concentration     = output.pm1_mass_concentration;
    meas_data->pm10_mass_concentration    = output.pm10_mass_concentration;
    meas_data->pm2_5_number_concentration = output.pm2_5_number_concentration;
    meas_data->pm1_number_concentration   = output.pm1_number_concentration;
    meas_data->pm10_number_concentration  = output.pm10_number_concentration;
    meas_data->runtime_in_sec             = output.runtime_in_sec;
    meas_data->is_obstructed              = ( uint8_t ) output.is_obstructed;
    meas_data->is_outside_range           = ( uint8_t ) output.is_outside_measurement_range;
    meas_data->data_ready                 = 1;
}

// ------------------------------------------------------------------------ END

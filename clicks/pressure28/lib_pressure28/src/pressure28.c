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
 * @file pressure28.c
 * @brief Pressure 28 Click Driver.
 */

#include "pressure28.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Pressure 28 I2C writing function.
 * @details This function sends a desired operation command using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note All operation commands of this device are sent without data bytes.
 */
static err_t pressure28_i2c_write ( pressure28_t *ctx, uint8_t cmd );

/**
 * @brief Pressure 28 I2C reading function.
 * @details This function sends a command byte and reads the response by using
 * I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @param[in] addr : Non-volatile memory address, used by the read NVM command only.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure28_i2c_read ( pressure28_t *ctx, uint8_t cmd, uint8_t addr, uint8_t *data_out );

/**
 * @brief Pressure 28 SPI writing function.
 * @details This function sends a desired operation command using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note All operation commands of this device are sent without data bytes.
 */
static err_t pressure28_spi_write ( pressure28_t *ctx, uint8_t cmd );

/**
 * @brief Pressure 28 SPI reading function.
 * @details This function sends a command byte and reads the response by using
 * SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @param[in] addr : Non-volatile memory address, used by the read NVM command only.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure28_spi_read ( pressure28_t *ctx, uint8_t cmd, uint8_t addr, uint8_t *data_out );

/**
 * @brief Pressure 28 delay function.
 * @details This function performs a delay of a desired duration.
 * @param[in] delay_len : Delay duration in milliseconds.
 * @return Nothing.
 * @note None.
 */
static void pressure28_delay_ms ( uint16_t delay_len );

/**
 * @brief Pressure 28 conversion time function.
 * @details This function returns the maximum duration of a pressure conversion
 * cycle for the selected measurement mode.
 * @param[in] mode : Active command that selects the measurement mode.
 * @return Conversion time in milliseconds.
 * @note None.
 */
static uint16_t pressure28_conv_time ( uint8_t mode );

/**
 * @brief Pressure 28 first conversion time function.
 * @details This function returns the maximum duration of the first conversion
 * cycle for the selected measurement mode.
 * @param[in] mode : Active command that selects the measurement mode.
 * @return First conversion time in milliseconds.
 * @note None.
 */
static uint16_t pressure28_first_conv_time ( uint8_t mode );

/**
 * @brief Pressure 28 read raw function.
 * @details This function reads a 24-bit measurement result and extends its sign
 * to a 32-bit signed value.
 * @param[in] ctx : Click context object.
 * See #pressure28_t object definition for detailed explanation.
 * @param[in] cmd : Result command byte to be sent.
 * @param[out] raw_out : Pointer to the sign extended raw result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure28_read_raw ( pressure28_t *ctx, uint8_t cmd, int32_t *raw_out );

void pressure28_cfg_setup ( pressure28_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dry  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE28_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE28_DRV_SEL_I2C;
}

void pressure28_drv_interface_sel ( pressure28_cfg_t *cfg, pressure28_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure28_init ( pressure28_t *ctx, pressure28_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->mode = PRESSURE28_DEFAULT_MODE;

    if ( PRESSURE28_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = pressure28_i2c_read;
        ctx->write_f = pressure28_i2c_write;
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

        ctx->read_f  = pressure28_spi_read;
        ctx->write_f = pressure28_spi_write;
    }

    digital_in_init( &ctx->dry, cfg->dry );

    /* POR and initial boot take up to 1.8ms ( datasheet page 27 ) */
    Delay_5ms( );

    return PRESSURE28_OK;
}

err_t pressure28_default_cfg ( pressure28_t *ctx ) 
{
    err_t error_flag = PRESSURE28_OK;
    uint8_t dev_state = 0;

    error_flag |= pressure28_reset_device( ctx );

    /* The read NVM command is accepted in the idle state only */
    error_flag |= pressure28_set_idle( ctx );

    /* Make sure the device entered idle state before checking communication */
    error_flag |= pressure28_read_status( ctx, &dev_state );
    if ( PRESSURE28_STATE_IDLE != dev_state )
    {
        error_flag = PRESSURE28_ERROR;
    }
    error_flag |= pressure28_check_communication( ctx );

    /* 
     * Start the session from the shutdown state so that the conversion timings
     * documented in the flow chart apply ( datasheet page 13 ).
     */
    error_flag |= pressure28_reset_device( ctx );
    error_flag |= pressure28_start_measurement( ctx, PRESSURE28_DEFAULT_MODE );

    return error_flag;
}

err_t pressure28_generic_write ( pressure28_t *ctx, uint8_t cmd ) 
{
    return ctx->write_f( ctx, cmd );
}

err_t pressure28_generic_read ( pressure28_t *ctx, uint8_t cmd, uint8_t *data_out ) 
{
    /* Result commands carry no memory address */
    return ctx->read_f( ctx, cmd, DUMMY, data_out );
}

err_t pressure28_read_nvm ( pressure28_t *ctx, uint8_t addr, uint8_t *data_out ) 
{
    return ctx->read_f( ctx, PRESSURE28_CMD_READ_NVM, addr, data_out );
}

err_t pressure28_reset_device ( pressure28_t *ctx ) 
{
    err_t error_flag = PRESSURE28_OK;

    /* The reset command returns the device to the shutdown state from any state */
    error_flag |= pressure28_generic_write( ctx, PRESSURE28_CMD_RESET );
    Delay_5ms( );

    return error_flag;
}

err_t pressure28_set_idle ( pressure28_t *ctx ) 
{
    err_t error_flag = PRESSURE28_OK;

    error_flag |= pressure28_generic_write( ctx, PRESSURE28_CMD_IDLE );
    Delay_5ms( );

    return error_flag;
}

err_t pressure28_check_communication ( pressure28_t *ctx ) 
{
    err_t error_flag = PRESSURE28_OK;
    uint8_t nvm_data = 0;

    /* The product code is factory programmed in NVM and identical on every device ( datasheet page 14 ) */
    error_flag |= pressure28_read_nvm( ctx, PRESSURE28_NVM_ADDR_MODEL_RANK, &nvm_data );
    if ( PRESSURE28_NVM_MODEL_RANK_MMR902_A != nvm_data )
    {
        error_flag = PRESSURE28_ERROR;
    }
    error_flag |= pressure28_read_nvm( ctx, PRESSURE28_NVM_ADDR_CORR_VOLTAGE, &nvm_data );
    if ( PRESSURE28_NVM_CORR_VOLTAGE_3V4 != nvm_data )
    {
        error_flag = PRESSURE28_ERROR;
    }

    return error_flag;
}

err_t pressure28_read_status ( pressure28_t *ctx, uint8_t *status ) 
{
    return pressure28_generic_read( ctx, PRESSURE28_CMD_READ_STATUS, status );
}

err_t pressure28_start_measurement ( pressure28_t *ctx, uint8_t mode ) 
{
    err_t error_flag = PRESSURE28_OK;

    /* Operation command both starts the measuring session and selects the measurement mode */
    error_flag |= pressure28_generic_write( ctx, mode );
    if ( PRESSURE28_OK == error_flag )
    {
        ctx->mode = mode;

        /* The first cycle covers boot, the single temperature conversion and the first pressure conversion */
        pressure28_delay_ms( pressure28_first_conv_time( mode ) );
    }

    return error_flag;
}

err_t pressure28_read_temperature ( pressure28_t *ctx, float *temp ) 
{
    err_t error_flag = PRESSURE28_OK;
    int32_t raw_temp = 0;

    error_flag |= pressure28_read_raw( ctx, PRESSURE28_CMD_READ_TEMPERATURE, &raw_temp );

    /* Temperature = raw_value / 2^16 ( datasheet page 24, table 7 ) */
    *temp = ( float ) raw_temp / PRESSURE28_TEMPERATURE_RES_C;

    return error_flag;
}

err_t pressure28_read_pressure ( pressure28_t *ctx, float *press ) 
{
    err_t error_flag = PRESSURE28_OK;
    int32_t raw_press = 0;

    /* Wait for the running conversion to store a fresh result */
    pressure28_delay_ms( pressure28_conv_time( ctx->mode ) );
    error_flag |= pressure28_read_raw( ctx, PRESSURE28_CMD_READ_PRESSURE, &raw_press );

    /* Pressure = raw_value / 1000 ( datasheet page 24, table 7 ) */
    *press = ( float ) raw_press / PRESSURE28_PRESSURE_RES_MMHG;

    return error_flag;
}

uint8_t pressure28_get_dry_pin ( pressure28_t *ctx ) 
{
    return digital_in_read( &ctx->dry );
}

static err_t pressure28_i2c_write ( pressure28_t *ctx, uint8_t cmd ) 
{
    /* 
     * Operation command frame: S | addr + W | A | command_byte | A | P
     * 
     *  commands:
     *     - reset ( 0x72 )
     *     - idle  ( 0x94 )
     *     - MODE1 ( 0xA0 )
     *     - MODE2 ( 0xA2 )
     *     - MODE3 ( 0xA4 )
     *     - MODE4 ( 0xA6 )
     * 
     *  No data bytes are sent with the operation commands.
     */
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

static err_t pressure28_i2c_read ( pressure28_t *ctx, uint8_t cmd, uint8_t addr, uint8_t *data_out ) 
{   
    /* Result command frame : S | sl_addr + W | A | cmd | A | P
     *                        S | sl_addr + R | A | data0 | A | ... | dataN | N | P
     *      - commands:
     *          - read compensated pressure result    ( 0xC0 ) -> data[23:0], 2nd complement
     *          - read compensated temperature result ( 0xC2 ) -> data[23:0], 2nd complement
     *          - read status                         ( 0x80 ) -> data[7:0]  
     * 
     * Read NVM frame : S | sl_addr + W | A | cmd | A | addr | A | P
     *                  S | sl_addr + R | A | data0 | N | P
     *      - commands: read NVM ( 0xD6 ) -> data[7:0]
     */
    err_t error_flag = PRESSURE28_OK;
    uint8_t cmd_buf[ PRESSURE28_CMD_BUF_LEN ] = { 0 };
    uint8_t cmd_len = 1;
    uint8_t rsp_len = 1;

    cmd_buf[ 0 ] = cmd;

    if ( PRESSURE28_CMD_READ_NVM == cmd )
    {
        cmd_buf[ 1 ] = addr;
        cmd_len = PRESSURE28_CMD_BUF_LEN;
    }

    if ( ( PRESSURE28_CMD_READ_PRESSURE == cmd ) || ( PRESSURE28_CMD_READ_TEMPERATURE == cmd ) )
    {
        rsp_len = PRESSURE28_RESULT_LEN;
    }

    /* No repeated start condition */
    error_flag |= i2c_master_write( &ctx->i2c, cmd_buf, cmd_len );
    error_flag |= i2c_master_read( &ctx->i2c, data_out, rsp_len );

    return error_flag;
}

static err_t pressure28_spi_write ( pressure28_t *ctx, uint8_t cmd ) 
{
    /* 
     * Operation command frame: cs_low | command_byte | cs_high
     * 
     *  commands:
     *     - reset ( 0x72 )
     *     - idle  ( 0x94 )
     *     - MODE1 ( 0xA0 )
     *     - MODE2 ( 0xA2 )
     *     - MODE3 ( 0xA4 )
     *     - MODE4 ( 0xA6 )
     * 
     *  No data bytes are sent with the operation commands.
     */
    err_t error_flag = PRESSURE28_OK;

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t pressure28_spi_read ( pressure28_t *ctx, uint8_t cmd, uint8_t addr, uint8_t *data_out ) 
{
    /* 
     * Result command frame : cs_low | cmd | data0 | ... dataN | cs_high 
     *  - commands:
     *      - read compensated pressure result    ( 0xC0 ) -> data[23:0], 2nd complement
     *      - read compensated temperature result ( 0xC2 ) -> data[23:0], 2nd complement
     *      - read status                         ( 0x80 ) -> data[7:0]                   
     *
     * Read NVM frame : cs_low | cmd | addr | 0x00 until ready (0x01) | data0 | cs_high
     *      - commands: read NVM ( 0xD6 ) -> data[7:0]
     */
    err_t error_flag = PRESSURE28_OK;
    uint8_t cmd_buf[ PRESSURE28_CMD_BUF_LEN ] = { 0 };
    uint8_t rsp_data = 0;
    uint8_t rsp_len = 1;
    uint8_t timeout_cnt = PRESSURE28_NVM_SPI_TIMEOUT;

    cmd_buf[ 0 ] = cmd;
    if ( ( PRESSURE28_CMD_READ_PRESSURE == cmd ) || ( PRESSURE28_CMD_READ_TEMPERATURE == cmd ) )
    {
        rsp_len = PRESSURE28_RESULT_LEN;
    }

    spi_master_select_device( ctx->chip_select );
    if ( PRESSURE28_CMD_READ_NVM == cmd )
    {
        /* The device outputs 0x00 while busy, then 0x01 to signal readiness */
        cmd_buf[ 1 ] = addr;
        error_flag |= spi_master_write( &ctx->spi, cmd_buf, PRESSURE28_CMD_BUF_LEN );

        do
        {
            error_flag |= spi_master_read( &ctx->spi, &rsp_data, 1 );
            timeout_cnt--;
        }
        while ( ( PRESSURE28_NVM_SPI_READY_MARKER != rsp_data ) && ( timeout_cnt ) );

        /* Check which condition was met */
        if ( PRESSURE28_NVM_SPI_READY_MARKER == rsp_data )
        {
            /* The memory byte follows the ready indicator */
            error_flag |= spi_master_read( &ctx->spi, data_out, 1 );
        }
        else
        {
            error_flag = PRESSURE28_ERROR;
        }
    }
    else
    {
        error_flag |= spi_master_write_then_read( &ctx->spi, cmd_buf, 1, data_out, rsp_len );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static void pressure28_delay_ms ( uint16_t delay_len ) 
{
    while ( delay_len )
    {
        Delay_1ms( );
        delay_len--;
    }
}

static uint16_t pressure28_conv_time ( uint8_t mode ) 
{
    uint16_t conv_time = 0;

    /* 
     * Maximum duration of a pressure conversion cycle ( datasheet page 13, figure 6 ):
     *  - MODE1: 16ms
     *  - MODE2: 8ms
     *  - MODE3: 4ms
     *  - MODE4: 256ms
     */
    switch ( mode )
    {
        case PRESSURE28_CMD_ACTIVE_MODE_1:
        {
            conv_time = PRESSURE28_CONV_MODE_1_MS;
            break;
        }
        case PRESSURE28_CMD_ACTIVE_MODE_2:
        {
            conv_time = PRESSURE28_CONV_MODE_2_MS;
            break;
        }
        case PRESSURE28_CMD_ACTIVE_MODE_3:
        {
            conv_time = PRESSURE28_CONV_MODE_3_MS;
            break;
        }
        case PRESSURE28_CMD_ACTIVE_MODE_4:
        {
            conv_time = PRESSURE28_CONV_MODE_4_MS;
            break;
        }
        default:
        {
            /* Fall back to the longest cycle */
            conv_time = PRESSURE28_CONV_MODE_4_MS;
            break;
        }
    }

    return conv_time;
}

static uint16_t pressure28_first_conv_time ( uint8_t mode ) 
{
    uint16_t conv_time = 0;

    /* 
     * Maximum duration of the first conversion cycle ( datasheet page 13, figure 6 ):
     *  - MODE1: 34ms
     *  - MODE2: 21ms
     *  - MODE3: 14ms
     *  - MODE4: 439ms
     */
    switch ( mode )
    {
        case PRESSURE28_CMD_ACTIVE_MODE_1:
        {
            conv_time = PRESSURE28_FIRST_CONV_MODE_1_MS;
            break;
        }
        case PRESSURE28_CMD_ACTIVE_MODE_2:
        {
            conv_time = PRESSURE28_FIRST_CONV_MODE_2_MS;
            break;
        }
        case PRESSURE28_CMD_ACTIVE_MODE_3:
        {
            conv_time = PRESSURE28_FIRST_CONV_MODE_3_MS;
            break;
        }
        case PRESSURE28_CMD_ACTIVE_MODE_4:
        {
            conv_time = PRESSURE28_FIRST_CONV_MODE_4_MS;
            break;
        }
        default:
        {
            /* Fall back to the longest cycle */
            conv_time = PRESSURE28_FIRST_CONV_MODE_4_MS;
            break;
        }
    }

    return conv_time;
}

static err_t pressure28_read_raw ( pressure28_t *ctx, uint8_t cmd, int32_t *raw_out ) 
{
    err_t error_flag = PRESSURE28_OK;
    uint8_t data_buf[ PRESSURE28_RESULT_LEN ] = { 0 };
    uint32_t raw_data = 0;

    error_flag |= pressure28_generic_read( ctx, cmd, data_buf );
    if ( PRESSURE28_OK == error_flag )
    {
        /* Results are output as 24 bits, MSB first */
        raw_data = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | 
                   ( ( uint32_t ) data_buf[ 1 ] << 8 ) | 
                   ( uint32_t ) data_buf[ 2 ];

        /* Negative results are expressed in two's complement => sign extend ( datasheet page 24 ) */
        if ( raw_data & PRESSURE28_SIGN_BIT_MASK )
        {
            raw_data |= PRESSURE28_SIGN_EXTENSION_MASK;
        }

        *raw_out = ( int32_t ) raw_data;
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END

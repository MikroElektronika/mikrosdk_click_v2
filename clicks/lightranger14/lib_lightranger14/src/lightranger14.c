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
 * @file lightranger14.c
 * @brief LightRanger 14 Click Driver.
 */

#include "lightranger14.h"
#include "lightranger14_firmware.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY           0x00
#define SPI_WRITE_CMD   0x02
#define SPI_READ_CMD    0x03

/**
 * @brief LightRanger 14 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger14_i2c_write ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 14 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger14_i2c_read ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LightRanger 14 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger14_spi_write ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 14 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger14_spi_read ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void lightranger14_cfg_setup ( lightranger14_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = LIGHTRANGER14_DEVICE_ADDRESS;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = LIGHTRANGER14_DRV_SEL_I2C;
}

void lightranger14_drv_interface_sel ( lightranger14_cfg_t *cfg, lightranger14_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t lightranger14_init ( lightranger14_t *ctx, lightranger14_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( LIGHTRANGER14_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = lightranger14_i2c_read;
        ctx->write_f = lightranger14_i2c_write;
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

        ctx->read_f  = lightranger14_spi_read;
        ctx->write_f = lightranger14_spi_write;
    }

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LIGHTRANGER14_OK;
}

err_t lightranger14_default_cfg ( lightranger14_t *ctx ) 
{
    err_t error_flag = LIGHTRANGER14_OK;
    
    lightranger14_disable_device ( ctx );
    Delay_100ms ( );
    lightranger14_enable_device ( ctx );
    Delay_100ms ( );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_download_fw ( ctx );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_check_com ( ctx );
    }

    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_load_cfg_page ( ctx );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
    #if ( LIGHTRANGER14_MAP_WIDTH <= 16 )
        error_flag = lightranger14_set_meas_period ( ctx, LIGHTRANGER14_MEASUREMENT_PERIOD_MS );
    #elif ( LIGHTRANGER14_MAP_WIDTH <= 32 )
        error_flag = lightranger14_set_meas_period ( ctx, LIGHTRANGER14_MEASUREMENT_PERIOD_MS * 2 );
    #elif ( LIGHTRANGER14_MAP_WIDTH <= 48 )
        error_flag = lightranger14_set_meas_period ( ctx, LIGHTRANGER14_MEASUREMENT_PERIOD_MS * 3 );
    #endif
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_write_cfg_page ( ctx );
    }
    
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_REG_INT_ENAB, LIGHTRANGER14_INT_ENAB_RESULTS );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_write_cmd ( ctx, LIGHTRANGER14_DEFAULT_LOAD_CONFIG, LIGHTRANGER14_CMD_STAT_APP_OK );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_start_measurement ( ctx );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_clear_interrupts ( ctx );
    }
    return error_flag;
}

err_t lightranger14_write_reg ( lightranger14_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t lightranger14_read_reg ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t lightranger14_write_regs ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t lightranger14_read_regs ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t lightranger14_check_reg ( lightranger14_t *ctx, uint8_t reg, uint8_t exp_data )
{
    err_t error_flag = LIGHTRANGER14_OK;
    uint16_t timeout_cnt = 0;
    uint8_t reg_data = 0;
    while ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_read_reg ( ctx, reg, &reg_data );
        if ( reg_data == exp_data )
        {
            break;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > LIGHTRANGER14_TIMEOUT_MS )
        {
            error_flag = LIGHTRANGER14_ERROR_TIMEOUT;
        }
    }
    return error_flag;
}

err_t lightranger14_write_cmd ( lightranger14_t *ctx, uint8_t cmd, uint8_t exp_resp )
{
    err_t error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_REG_CMD_STAT, cmd );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_check_reg ( ctx, LIGHTRANGER14_REG_CMD_STAT, exp_resp );
    }
    return error_flag;
}

void lightranger14_enable_device ( lightranger14_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void lightranger14_disable_device ( lightranger14_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t lightranger14_get_int_pin ( lightranger14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t lightranger14_check_com ( lightranger14_t *ctx )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = lightranger14_read_regs ( ctx, LIGHTRANGER14_REG_APP_ID, data_buf, 4 );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        memcpy ( ctx->info.app_ver, data_buf, 4 );
        error_flag = lightranger14_read_regs ( ctx, LIGHTRANGER14_REG_SERIAL_NUM_0, data_buf, 4 );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        ctx->info.serial_num = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | 
                               ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                               ( ( uint16_t ) data_buf[ 1 ] << 8 ) |
                                              data_buf[ 0 ];
        error_flag = lightranger14_read_regs ( ctx, LIGHTRANGER14_REG_ID, data_buf, 2 );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        memcpy ( ctx->info.chip_ver, data_buf, 2 );
        if ( LIGHTRANGER14_CHIP_ID != ctx->info.chip_ver[ 0 ] )
        {
            error_flag = LIGHTRANGER14_ERROR;
        }
    }
    return error_flag;
}

err_t lightranger14_power_up ( lightranger14_t *ctx )
{
    uint16_t timeout_cnt = 0;
    uint8_t reg_data = 0;
    err_t error_flag = lightranger14_read_reg ( ctx, LIGHTRANGER14_REG_ENABLE, &reg_data );
    if ( ( LIGHTRANGER14_OK == error_flag ) && 
         ( LIGHTRANGER14_ENABLE_PON != ( LIGHTRANGER14_ENABLE_PON & reg_data ) ) )
    {
        error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_REG_ENABLE, LIGHTRANGER14_ENABLE_PON );
        Delay_10ms ( );
    }
    while ( ( LIGHTRANGER14_OK == error_flag ) && 
            ( LIGHTRANGER14_ENABLE_CPU_READY != ( LIGHTRANGER14_ENABLE_CPU_READY & reg_data ) ) )
    {
        error_flag = lightranger14_read_reg ( ctx, LIGHTRANGER14_REG_ENABLE, &reg_data );
        Delay_1ms ( );
        if ( ++timeout_cnt > LIGHTRANGER14_TIMEOUT_MS )
        {
            error_flag = LIGHTRANGER14_ERROR_TIMEOUT;
        }
    }
    return error_flag;
}

err_t lightranger14_power_down ( lightranger14_t *ctx )
{
    uint8_t reg_data = 0;
    err_t error_flag = lightranger14_read_reg ( ctx, LIGHTRANGER14_REG_ENABLE, &reg_data );
    if ( ( LIGHTRANGER14_OK == error_flag ) && 
         ( LIGHTRANGER14_ENABLE_CPU_READY & reg_data ) )
    {
        reg_data |= LIGHTRANGER14_ENABLE_POFF;
        error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_REG_ENABLE, reg_data );
        Delay_10ms ( );
    }
    return error_flag;
}

err_t lightranger14_download_fw ( lightranger14_t *ctx )
{
    err_t error_flag = LIGHTRANGER14_OK;
    uint32_t fw_size = LIGHTRANGER14_IMAGE_FINISH - LIGHTRANGER14_IMAGE_START;
    uint32_t fw_index = 0;
    uint8_t chunk_bytes = 0;
    uint8_t data_buf[ LIGHTRANGER14_MAX_RW_BUF_SIZE ] = { 0 };

    // Check if sensor is in the bootloader mode
    error_flag = lightranger14_check_reg ( ctx, LIGHTRANGER14_REG_APP_ID, LIGHTRANGER14_APP_ID_BOOTLOADER );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Disable unused communication
        if ( LIGHTRANGER14_DRV_SEL_I2C == ctx->drv_sel ) 
        {
            error_flag = lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_BL_SPI_OFF, LIGHTRANGER14_CMD_STAT_BL_READY );
        }
        else
        {
            error_flag = lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_BL_I2C_OFF, LIGHTRANGER14_CMD_STAT_BL_READY );
        }
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Set FIFO start address and size
        data_buf[ 0 ] = LIGHTRANGER14_CMD_BL_W_FIFO_BOTH;
        data_buf[ 1 ] = 6; // payload
        data_buf[ 2 ] = ( LIGHTRANGER14_IMAGE_START & 0xFF );
        data_buf[ 3 ] = ( ( LIGHTRANGER14_IMAGE_START >> 8 ) & 0xFF );
        data_buf[ 4 ] = ( ( LIGHTRANGER14_IMAGE_START >> 16 ) & 0xFF );
        data_buf[ 5 ] = ( ( LIGHTRANGER14_IMAGE_START >> 24 ) & 0xFF );
        data_buf[ 6 ] = ( ( ( fw_size + 3 ) / 4 ) & 0xFF ); // round size to a word size
        data_buf[ 7 ] = ( ( ( ( fw_size + 3 ) / 4 ) >> 8 ) & 0xFF );
        error_flag = lightranger14_write_regs ( ctx, LIGHTRANGER14_REG_BL_CMD_STAT, data_buf, 8 );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Check ready
        error_flag = lightranger14_check_reg ( ctx, LIGHTRANGER14_REG_BL_CMD_STAT, LIGHTRANGER14_CMD_STAT_BL_READY );
    }
    while ( ( LIGHTRANGER14_OK == error_flag ) && 
            ( fw_index < fw_size ) )
    {
        chunk_bytes = LIGHTRANGER14_MAX_RW_BUF_SIZE;
        if ( ( fw_index + chunk_bytes ) > fw_size )
        {
            chunk_bytes = fw_size - fw_index;
        }
        memcpy ( data_buf, &lightranger14_image[ fw_index ], chunk_bytes );
        // Write image to FIFO in chunks of up to LIGHTRANGER14_MAX_RW_BUF_SIZE
        error_flag = lightranger14_write_regs ( ctx, LIGHTRANGER14_REG_FIFO, data_buf, chunk_bytes );
        fw_index += chunk_bytes;
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Start the downloaded application
        error_flag = lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_BL_START_RAM_APP, LIGHTRANGER14_CMD_STAT_BL_READY );
    }
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Check if it's started
        error_flag = lightranger14_check_reg ( ctx, LIGHTRANGER14_REG_APP_ID, LIGHTRANGER14_APP_ID_RAM );
    }
    return error_flag;
}

err_t lightranger14_clear_interrupts ( lightranger14_t *ctx )
{
    uint8_t int_status = 0;
    err_t error_flag = lightranger14_read_reg ( ctx, LIGHTRANGER14_REG_INT_STATUS, &int_status );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_REG_INT_STATUS, int_status );
    }
    return error_flag;
}

err_t lightranger14_load_cfg_page ( lightranger14_t *ctx )
{
    err_t error_flag = lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_APP_LOAD_CONFIG_PAGE, LIGHTRANGER14_CMD_STAT_APP_OK );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_check_reg ( ctx, LIGHTRANGER14_REG_CID_RID, LIGHTRANGER14_CID_RID_CID_CONFIG );
    }
    return error_flag;
}

err_t lightranger14_write_cfg_page ( lightranger14_t *ctx )
{
    return lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_APP_WRITE_PAGE, LIGHTRANGER14_CMD_STAT_APP_OK );
}

err_t lightranger14_set_meas_period ( lightranger14_t *ctx, uint16_t period_ms )
{
    err_t error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_CFG_PERIOD_MS_LSB, ( uint8_t ) ( period_ms & 0xFF ) );
    if ( LIGHTRANGER14_OK == error_flag )
    {
        error_flag = lightranger14_write_reg ( ctx, LIGHTRANGER14_CFG_PERIOD_MS_MSB, ( uint8_t ) ( ( period_ms >> 8 ) & 0xFF ) );
    }
    return error_flag;
}

err_t lightranger14_start_measurement ( lightranger14_t *ctx )
{
    return lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_APP_MEASURE, LIGHTRANGER14_CMD_STAT_APP_ACCEPTED );
}

err_t lightranger14_stop_measurement ( lightranger14_t *ctx )
{
    return lightranger14_write_cmd ( ctx, LIGHTRANGER14_CMD_APP_STOP, LIGHTRANGER14_CMD_STAT_APP_OK );
}

err_t lightranger14_read_results ( lightranger14_t *ctx, uint8_t *frame_data, uint16_t len )
{
    uint8_t data_buf[ LIGHRANGER14_FRAME_PREHEADER_SIZE + LIGHRANGER14_FRAME_HEADER_SIZE ] = { 0 };
    uint16_t pl_idx = 0;
    uint8_t chunk_bytes = 0;
    
    ctx->results.payload = frame_data; // Set payload data pointer

    // Read preheader and frame header
    err_t error_flag = lightranger14_read_regs ( ctx, LIGHTRANGER14_REG_FIFOSTATUS, data_buf, 
                                                 LIGHRANGER14_FRAME_PREHEADER_SIZE + LIGHRANGER14_FRAME_HEADER_SIZE );

    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Preheader
        ctx->results.fifostatus = data_buf[ 0 ];
        ctx->results.systick = ( ( uint32_t ) data_buf[ 4 ] << 24 ) | 
                               ( ( uint32_t ) data_buf[ 3 ] << 16 ) | 
                               ( ( uint32_t ) data_buf[ 2 ] << 8 ) | 
                               ( ( uint32_t ) data_buf[ 1 ] << 0 );
        
        // Frame header
        ctx->results.frame_id = data_buf[ 5 ];
        ctx->results.res_format = data_buf[ 6 ];
        ctx->results.payload_len = ( ( ( uint16_t ) data_buf[ 8 ] << 8 ) | ( ( uint16_t ) data_buf[ 7 ] << 0 ) ) - 
                                     LIGHRANGER14_FRAME_FOOTER_SIZE - ( LIGHRANGER14_FRAME_HEADER_SIZE - 4 );
        ctx->results.frame_num = ( ( uint32_t ) data_buf[ 12 ] << 24 ) | 
                                 ( ( uint32_t ) data_buf[ 11 ] << 16 ) | 
                                 ( ( uint32_t ) data_buf[ 10 ] << 8 ) | 
                                 ( ( uint32_t ) data_buf[ 9 ] << 0 );
        ctx->results.temperature[ 0 ] = data_buf[ 13 ];
        ctx->results.temperature[ 1 ] = data_buf[ 14 ];
        ctx->results.temperature[ 2 ] = data_buf[ 15 ];
        ctx->results.bdv = data_buf[ 16 ];
        ctx->results.ref_peak_first = ( ( uint16_t ) data_buf[ 18 ] << 8 ) | 
                                      ( ( uint16_t ) data_buf[ 17 ] << 0 );
        ctx->results.ref_peak_last = ( ( uint16_t ) data_buf[ 20 ] << 8 ) | 
                                     ( ( uint16_t ) data_buf[ 19 ] << 0 );

        if ( ( ctx->results.payload_len > 0 ) || ( ctx->results.payload_len <= len ) )
        {
            // Read payload data if it can be fitted in frame_data buffer
            while ( ( LIGHTRANGER14_OK == error_flag ) && 
                    ( pl_idx < ctx->results.payload_len ) )
            {
                chunk_bytes = LIGHTRANGER14_MAX_RW_BUF_SIZE;
                if ( ( pl_idx + chunk_bytes ) > ctx->results.payload_len )
                {
                    chunk_bytes = ctx->results.payload_len - pl_idx;
                }
                error_flag = lightranger14_read_regs ( ctx, LIGHTRANGER14_REG_FIFO, &ctx->results.payload[ pl_idx ], chunk_bytes );
                pl_idx += chunk_bytes;
            }
        }
        else
        {
            error_flag = LIGHTRANGER14_ERROR;
        }
    }
    
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Read frame footer
        error_flag = lightranger14_read_regs ( ctx, LIGHTRANGER14_REG_FIFO, data_buf, LIGHRANGER14_FRAME_FOOTER_SIZE );
    }
    
    if ( LIGHTRANGER14_OK == error_flag )
    {
        // Frame footer
        ctx->results.t_first = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | 
                               ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                               ( ( uint32_t ) data_buf[ 1 ] << 8 ) | 
                               ( ( uint32_t ) data_buf[ 0 ] << 0 );
        ctx->results.t_last = ( ( uint32_t ) data_buf[ 7 ] << 24 ) | 
                              ( ( uint32_t ) data_buf[ 6 ] << 16 ) | 
                              ( ( uint32_t ) data_buf[ 5 ] << 8 ) | 
                              ( ( uint32_t ) data_buf[ 4 ] << 0 );
        ctx->results.frame_status = data_buf[ 8 ];
        ctx->results.eof_marker = ( ( uint16_t ) data_buf[ 11 ] << 8 ) | 
                                  ( ( uint16_t ) data_buf[ 10 ] << 0 );

        if ( LIGHRANGER14_FRAME_EOF_MARKER != ctx->results.eof_marker )
        {
            error_flag = LIGHTRANGER14_ERROR;
        }
    }
    return error_flag;
}

static err_t lightranger14_i2c_write ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ LIGHTRANGER14_MAX_RW_BUF_SIZE + 1 ] = { 0 };
    data_buf[ 0 ] = reg;
    if ( len > LIGHTRANGER14_MAX_RW_BUF_SIZE )
    {
        return LIGHTRANGER14_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t lightranger14_i2c_read ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t lightranger14_spi_write ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = SPI_WRITE_CMD;
    data_buf[ 1 ] = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t lightranger14_spi_read ( lightranger14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = SPI_READ_CMD;
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 3, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

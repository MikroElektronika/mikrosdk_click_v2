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
 * @file ism5.c
 * @brief ISM 5 Click Driver.
 */

#include "ism5.h"
#include "ism5_radio_config.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0xFF

/**
 * @brief Radio configuration data.
 * @details Radio configuration constant data array.
 */
static const uint8_t radio_config_data[ ] = RADIO_CONFIGURATION_DATA_ARRAY;

void ism5_cfg_setup ( ism5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ism5_init ( ism5_t *ctx, ism5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->shd, cfg->shd );
    digital_out_low( &ctx->shd );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t ism5_default_cfg ( ism5_t *ctx ) 
{
    err_t error_flag = ISM5_OK;
    
    ism5_disable_device ( ctx );
    Delay_100ms ( );
    ism5_enable_device ( ctx );
    Delay_100ms ( );
    if ( ISM5_ERROR == ism5_check_communication ( ctx ) )
    {
        return ISM5_ERROR;
    }
    // Apply default configuration
    error_flag |= ism5_config_init ( ctx );

    // Clear interrupts
    error_flag |= ism5_get_int_status ( ctx, NULL );

    // Set to sleep mode
    error_flag |= ism5_change_state ( ctx, ISM5_STATE_SLEEP );

    // Set TX power to MAX
    error_flag |= ism5_set_property_byte ( ctx, ISM5_PROPERTY_PA_PWR_LVL, ISM5_PA_PWR_LVL_MAX );
    
    return error_flag;
}

err_t ism5_send_cmd ( ism5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    if ( ISM5_OK != ism5_wait_ready ( ctx ) )
    {
        return ISM5_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    if ( ( len > 0 ) && ( NULL != data_in ) )
    {
        error_flag |= spi_master_write( &ctx->spi, data_in, len );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t ism5_read_rsp ( ism5_t *ctx, uint8_t *data_out, uint8_t len )
{
    if ( ( 0 == len ) || ( NULL == data_out ) )
    {
        return ISM5_ERROR;
    }
    err_t error_flag = ISM5_OK;
    uint32_t timeout_cnt = 0;
    uint8_t cmd_byte = ISM5_CMD_READ_CMD_BUFF;
    uint8_t cts_byte = 0;
    while ( ( ISM5_OK == error_flag ) && 
            ( ISM5_CTS_READY_BYTE != cts_byte ) )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write_then_read( &ctx->spi, &cmd_byte, 1, &cts_byte, 1 );
        if ( ++timeout_cnt > ISM5_CTS_READY_TIMEOUT )
        {
            spi_master_deselect_device( ctx->chip_select );
            error_flag = ISM5_TIMEOUT;
        }
        else if ( ISM5_CTS_READY_BYTE != cts_byte )
        {
            spi_master_deselect_device( ctx->chip_select );
            Delay_1ms ( );
        }
        else
        {
            error_flag |= spi_master_read( &ctx->spi, data_out, len );
            spi_master_deselect_device( ctx->chip_select );
        }
    }
    return error_flag;
}

err_t ism5_send_fast_cmd ( ism5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    if ( ( 0 == len ) || ( NULL == data_in ) )
    {
        return ISM5_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t ism5_read_fast_cmd ( ism5_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    if ( ( 0 == len ) || ( NULL == data_out ) )
    {
        return ISM5_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t ism5_wait_ready ( ism5_t *ctx )
{
    uint32_t timeout_cnt = 0;
    while ( ISM5_OK != ism5_check_ready ( ctx ) )
    {
        if ( ++timeout_cnt > ISM5_CTS_READY_TIMEOUT )
        {
            return ISM5_TIMEOUT;
        }
        Delay_1ms ( );
    }
    return ISM5_OK;
}

err_t ism5_check_ready ( ism5_t *ctx )
{
    err_t error_flag = ISM5_OK;
    uint8_t cmd_byte = ISM5_CMD_READ_CMD_BUFF;
    uint8_t cts_byte = 0;
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &cmd_byte, 1, &cts_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ISM5_CTS_READY_BYTE != cts_byte )
    {
        error_flag = ISM5_ERROR;
    }
    return error_flag;
}

void ism5_enable_device ( ism5_t *ctx )
{
    digital_out_high ( &ctx->shd );
}

void ism5_disable_device ( ism5_t *ctx )
{
    digital_out_low ( &ctx->shd );
}

uint8_t ism5_get_int_pin ( ism5_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ism5_check_communication ( ism5_t *ctx )
{
    ism5_part_info_t part_info;
    if ( ISM5_OK == ism5_get_part_info ( ctx, &part_info ) )
    {
        if ( ISM5_PART_NUMBER == part_info.part )
        {
            return ISM5_OK;
        }
    }
    return ISM5_ERROR;
}

err_t ism5_config_init ( ism5_t *ctx )
{
    err_t error_flag = ISM5_OK;
    uint8_t config_cmd[ 16 ] = { 0 };
    ism5_int_status_t status;
    uint16_t config_data_idx = 0;
    uint8_t config_cmd_idx = 0;
    uint8_t response = 0;
    uint8_t cmd_num_bytes = 0;

    // Cycle as far as the config data index points to a command
    while ( ( ISM5_OK == error_flag ) && ( 0 != radio_config_data[ config_data_idx ] ) )
    {
        // Commands structure in the array: LEN | <LEN lenghth of data>
        cmd_num_bytes = radio_config_data[ config_data_idx++ ];
        if ( cmd_num_bytes > 16 )
        {
            // Number of command bytes exceeds maximal allowable length
            error_flag = ISM5_ERROR;
        }

        if ( ISM5_OK == error_flag )
        {
            for ( config_cmd_idx = 0; config_cmd_idx < cmd_num_bytes; config_cmd_idx++ )
            {
                config_cmd[ config_cmd_idx ] = radio_config_data[ config_data_idx++ ];
            }
            error_flag = ism5_send_cmd ( ctx, config_cmd[ 0 ], &config_cmd[ 1 ], cmd_num_bytes - 1 );
        }

        if ( ISM5_OK == error_flag )
        {
            error_flag = ism5_read_rsp ( ctx, &response, 1 );
        }

        if ( ( ISM5_OK == error_flag ) && ( 0 == ism5_get_int_pin ( ctx ) ) )
        {
            // Get and clear all interrupts. An error has occured...
            error_flag = ism5_get_int_status ( ctx, &status );
            if ( ( ISM5_OK == error_flag ) && ( status.chip_pend & ISM5_CHIP_PEND_CMD_ERROR ) )
            {
                error_flag = ISM5_ERROR;
            }
        }
    }
    return error_flag;
}

err_t ism5_power_up ( ism5_t *ctx )
{
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = ISM5_POWER_UP_BOOT_FUNCTIONAL;
    data_buf[ 1 ] = ISM5_POWER_UP_SELECT_TCXO;
    data_buf[ 2 ] = ( uint8_t ) ( ( ISM5_POWER_UP_TCXO_26MHZ >> 24 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( ISM5_POWER_UP_TCXO_26MHZ >> 16 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( ISM5_POWER_UP_TCXO_26MHZ >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ISM5_POWER_UP_TCXO_26MHZ & 0xFF );
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_POWER_UP, data_buf, 6 );
    Delay_10ms ( );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_wait_ready ( ctx );
    }
    return error_flag;
}

err_t ism5_get_part_info ( ism5_t *ctx, ism5_part_info_t *part_info )
{
    if ( NULL == part_info )
    {
        return ISM5_ERROR;
    }
    uint8_t data_buf[ 8 ] = { 0 };
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_PART_INFO, NULL, 0 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_read_rsp ( ctx, data_buf, 8 );
    }
    if ( ISM5_OK == error_flag )
    {
        part_info->chip_rev = data_buf[ 0 ];
        part_info->part = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        part_info->part_build = data_buf[ 3 ];
        part_info->id = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        part_info->customer = data_buf[ 6 ];
        part_info->rom_id = data_buf[ 7 ];
    }
    return error_flag;
}

err_t ism5_set_property ( ism5_t *ctx, uint16_t prop_idx, uint8_t *data_in, uint8_t num_props )
{
    if ( ( NULL == data_in ) || ( num_props < 1 ) || ( num_props > 12 ) )
    {
        return ISM5_ERROR;
    }
    uint8_t data_buf[ 15 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( prop_idx >> 8 ) & 0xFF );
    data_buf[ 1 ] = num_props;
    data_buf[ 2 ] = ( uint8_t ) ( prop_idx & 0xFF );
    for ( uint8_t cnt = 0; cnt < num_props; cnt++ )
    {
        data_buf[ 3 + cnt ] = data_in[ cnt ];
    }
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_SET_PROPERTY, data_buf, num_props + 3 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_wait_ready ( ctx );
    }
    return error_flag;
}

err_t ism5_get_property ( ism5_t *ctx, uint16_t prop_idx, uint8_t *data_out, uint8_t num_props )
{
    if ( ( NULL == data_out ) || ( num_props < 1 ) || ( num_props > 16 ) )
    {
        return ISM5_ERROR;
    }
    uint8_t data_buf[ 16 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( prop_idx >> 8 ) & 0xFF );
    data_buf[ 1 ] = num_props;
    data_buf[ 2 ] = ( uint8_t ) ( prop_idx & 0xFF );
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_GET_PROPERTY, data_buf, 3 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_read_rsp ( ctx, data_out, num_props );
    }
    return error_flag;
}

err_t ism5_set_property_byte ( ism5_t *ctx, uint16_t prop_idx, uint8_t data_in )
{
    return ism5_set_property ( ctx, prop_idx, &data_in, 1 );
}

err_t ism5_get_property_byte ( ism5_t *ctx, uint16_t prop_idx, uint8_t *data_out )
{
    return ism5_get_property ( ctx, prop_idx, data_out, 1 );
}

err_t ism5_gpio_config ( ism5_t *ctx, ism5_gpio_config_t *gpio_cfg )
{
    if ( NULL == gpio_cfg )
    {
        return ISM5_ERROR;
    }
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 0 ] = gpio_cfg->gpio_0;
    data_buf[ 1 ] = gpio_cfg->gpio_1;
    data_buf[ 2 ] = gpio_cfg->gpio_2;
    data_buf[ 3 ] = gpio_cfg->gpio_3;
    data_buf[ 4 ] = gpio_cfg->nirq;
    data_buf[ 5 ] = gpio_cfg->sdo;
    data_buf[ 6 ] = gpio_cfg->gen_config;
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_GPIO_PIN_CFG, data_buf, 7 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_read_rsp ( ctx, data_buf, 7 );
    }
    if ( ISM5_OK == error_flag )
    {
        gpio_cfg->gpio_0 = data_buf[ 0 ];
        gpio_cfg->gpio_1 = data_buf[ 1 ];
        gpio_cfg->gpio_2 = data_buf[ 2 ];
        gpio_cfg->gpio_3 = data_buf[ 3 ];
        gpio_cfg->nirq = data_buf[ 4 ];
        gpio_cfg->sdo = data_buf[ 5 ];
        gpio_cfg->gen_config = data_buf[ 6 ];
    }
    return error_flag;
}

err_t ism5_fifo_info ( ism5_t *ctx, uint8_t fifo_reset, uint8_t *rx_fifo_count, uint8_t *tx_fifo_space )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = fifo_reset & ISM5_FIFO_RESET_MASK;
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_FIFO_INFO, data_buf, 1 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_read_rsp ( ctx, data_buf, 2 );
    }
    if ( ISM5_OK == error_flag )
    {
        if ( NULL != rx_fifo_count )
        {
            *rx_fifo_count = data_buf[ 0 ];
        }
        if ( NULL != tx_fifo_space )
        {
            *tx_fifo_space = data_buf[ 1 ];
        }
    }
    return error_flag;
}

err_t ism5_get_int_status ( ism5_t *ctx, ism5_int_status_t *status )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = ISM5_INT_CLEAR;
    data_buf[ 1 ] = ISM5_INT_CLEAR;
    data_buf[ 2 ] = ISM5_INT_CLEAR;
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_GET_INT_STATUS, data_buf, 3 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_read_rsp ( ctx, data_buf, 8 );
    }
    if ( ( ISM5_OK == error_flag ) && ( NULL != status ) )
    {
        status->int_pend = data_buf[ 0 ];
        status->int_status = data_buf[ 1 ];
        status->ph_pend = data_buf[ 2 ];
        status->ph_status = data_buf[ 3 ];
        status->modem_pend = data_buf[ 4 ];
        status->modem_status = data_buf[ 5 ];
        status->chip_pend = data_buf[ 6 ];
        status->chip_status = data_buf[ 7 ];
    }
    return error_flag;
}

err_t ism5_get_device_state ( ism5_t *ctx, uint8_t *state, uint8_t *channel )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_REQUEST_DEVICE_STATE, NULL, 0 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_read_rsp ( ctx, data_buf, 2 );
    }
    if ( ISM5_OK == error_flag )
    {
        if ( NULL != state )
        {
            *state = data_buf[ 0 ] & ISM5_STATE_MASK;
        }
        if ( NULL != channel )
        {
            *channel = data_buf[ 1 ];
        }
    }
    return error_flag;
}

err_t ism5_change_state ( ism5_t *ctx, uint8_t state )
{
    if ( state > ISM5_STATE_RX )
    {
        return ISM5_ERROR;
    }
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_CHANGE_STATE, &state, 1 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_wait_ready ( ctx );
    }
    return error_flag;
}

err_t ism5_start_tx ( ism5_t *ctx, uint8_t channel, uint8_t condition, uint16_t len )
{
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = channel;
    data_buf[ 1 ] = condition;
    data_buf[ 2 ] = ( uint8_t ) ( ( len >> 8 ) & 0x1F );
    data_buf[ 3 ] = ( uint8_t ) ( len & 0xFF );
    data_buf[ 4 ] = 0; // Disable TX delay
    data_buf[ 5 ] = 0; // Disable TX repeat
    err_t error_flag = ism5_send_cmd ( ctx, ISM5_CMD_START_TX, data_buf, 6 );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_wait_ready ( ctx );
    }
    return error_flag;
}

err_t ism5_write_tx_fifo ( ism5_t *ctx, uint8_t *data_in, uint8_t len )
{
    return ism5_send_fast_cmd ( ctx, ISM5_CMD_WRITE_TX_FIFO, data_in, len );
}

err_t ism5_start_rx ( ism5_t *ctx, uint8_t channel, uint8_t condition, uint16_t len )
{
    uint8_t data_buf[ 7 ] = { 0 };
    // Set to idle state
    err_t error_flag = ism5_change_state ( ctx, ISM5_STATE_READY );
    if ( ISM5_OK == error_flag )
    {
        // Clear FIFO
        error_flag = ism5_fifo_info ( ctx, ISM5_FIFO_RESET_TX_RX, NULL, NULL );
    }
    if ( ISM5_OK == error_flag )
    {
        // Clear interrupts
        error_flag = ism5_get_int_status ( ctx, NULL );
    }
    if ( ISM5_OK == error_flag )
    {
        data_buf[ 0 ] = channel;
        data_buf[ 1 ] = condition;
        data_buf[ 2 ] = ( uint8_t ) ( ( len >> 8 ) & 0x1F );
        data_buf[ 3 ] = ( uint8_t ) ( len & 0xFF );
        data_buf[ 4 ] = ISM5_STATE_NO_CHANGE;
        data_buf[ 5 ] = ISM5_STATE_READY;
        data_buf[ 6 ] = ISM5_STATE_SLEEP;
        error_flag = ism5_send_cmd ( ctx, ISM5_CMD_START_RX, data_buf, 7 );
    }
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_wait_ready ( ctx );
    }
    return error_flag;
}

err_t ism5_read_rx_fifo ( ism5_t *ctx, uint8_t *data_out, uint8_t len )
{
    return ism5_read_fast_cmd ( ctx, ISM5_CMD_READ_RX_FIFO, data_out, len );
}

err_t ism5_wait_tx_finish ( ism5_t *ctx, uint32_t timeout )
{
    uint32_t timeout_cnt = 0;
    uint8_t state = 0;
    err_t error_flag = ISM5_OK;
    error_flag = ism5_get_device_state ( ctx, &state, NULL );
    while ( ( ISM5_STATE_TX == state ) && ( ISM5_OK == error_flag ) ) 
    {
        if ( ( ISM5_PACKET_TIMEOUT_DISABLE != timeout ) && ( timeout_cnt > timeout ) )
        {
            error_flag = ISM5_TIMEOUT;
        }
        else
        {
            timeout_cnt += 100;
            Delay_100ms ( );
            error_flag = ism5_get_device_state ( ctx, &state, NULL );
        }
    }
    return error_flag;
}

err_t ism5_transmit_packet ( ism5_t *ctx, uint8_t channel, uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || ( len > ISM5_PACKET_MAX_SIZE ) )
    {
        return ISM5_ERROR;
    }
    uint8_t state = 0;
    err_t error_flag = ism5_wait_tx_finish ( ctx, ISM5_PACKET_TIMEOUT_1_SEC );
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_change_state ( ctx, ISM5_STATE_READY );
    }
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_fifo_info ( ctx, ISM5_FIFO_RESET_TX_RX, NULL, NULL );
    }
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_get_int_status ( ctx, NULL );
    }
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_write_tx_fifo ( ctx, data_in, len );
    }
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_start_tx ( ctx, channel, ISM5_STATE_READY << 4, ISM5_PACKET_FIXED_SIZE );
    }
    if ( ISM5_OK == error_flag )
    {
        Delay_100ms ( );
        error_flag = ism5_wait_tx_finish ( ctx, ISM5_PACKET_TIMEOUT_1_SEC );
    }
    return error_flag;
}

err_t ism5_receive_packet ( ism5_t *ctx, uint8_t channel, uint8_t *data_out, uint8_t *len, uint32_t timeout )
{
    if ( NULL == data_out )
    {
        return ISM5_ERROR;
    }
    ism5_int_status_t status;
    uint8_t rx_data_len = 0;
    uint32_t timeout_cnt = 0;
    err_t error_flag = ism5_start_rx ( ctx, channel, ISM5_STATE_READY << 4, ISM5_PACKET_FIXED_SIZE );
    if ( ISM5_OK == error_flag )
    {
        // Wait for data
        while ( ( ism5_get_int_pin ( ctx ) ) && ( ISM5_OK == error_flag ) )
        {
            if ( ( ISM5_PACKET_TIMEOUT_DISABLE != timeout ) && ( timeout_cnt++ > timeout ) )
            {
                error_flag = ISM5_TIMEOUT;
            }
            Delay_1ms ( );
        }
    }
    if ( ISM5_OK == error_flag )
    {
        error_flag = ism5_get_int_status ( ctx, &status );
        if ( ISM5_PH_STATUS_PACKET_RX != ( status.ph_status & ISM5_PH_STATUS_PACKET_RX ) )
        {
            error_flag = ISM5_ERROR;
        }
    }
    if ( ISM5_OK == error_flag )
    {
        // Get rx length from FIFO
        error_flag = ism5_fifo_info ( ctx, ISM5_FIFO_RESET_NONE, &rx_data_len, NULL );
        if ( ( rx_data_len > ISM5_PACKET_MAX_SIZE ) || ( 0 == rx_data_len ) )
        {
            error_flag = ISM5_ERROR;
        }
    }
    if ( ISM5_OK == error_flag )
    {
        if ( NULL != len )
        {
            *len = rx_data_len;
        }
        error_flag = ism5_read_rx_fifo ( ctx, data_out, rx_data_len );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END

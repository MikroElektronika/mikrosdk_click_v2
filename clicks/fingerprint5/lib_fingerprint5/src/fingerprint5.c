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
 * @file fingerprint5.c
 * @brief Fingerprint 5 Click Driver.
 */

#include "fingerprint5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void fingerprint5_cfg_setup ( fingerprint5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->cs = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->baud_rate     = 921600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = FINGERPRINT5_DRV_SEL_SPI;
}

void fingerprint5_drv_interface_sel ( fingerprint5_cfg_t *cfg, fingerprint5_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t fingerprint5_init ( fingerprint5_t *ctx, fingerprint5_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low ( &ctx->rst );

    // Input pins
    digital_in_init( &ctx->irq, cfg->irq );

    if ( FINGERPRINT5_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_config_t uart_cfg;

        // Default config
        uart_configure_default( &uart_cfg );

        // Ring buffer mapping
        ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
        ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

        // UART module config
        uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
        uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
        uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
        uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

        if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
        {
            return UART_ERROR;
        }
        uart_set_baud( &ctx->uart, cfg->baud_rate );
        uart_set_parity( &ctx->uart, cfg->parity_bit );
        uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        uart_set_data_bits( &ctx->uart, cfg->data_bit );

        uart_set_blocking( &ctx->uart, cfg->uart_blocking );

        // Dummy read to enable RX interrupt
        uint8_t dummy_read = 0;
        uart_read ( &ctx->uart, &dummy_read, 1 );
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
    }
    Delay_100ms ( );

    return FINGERPRINT5_OK;
}

err_t fingerprint5_generic_write ( fingerprint5_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    err_t error_flag = FINGERPRINT5_OK;
    if ( FINGERPRINT5_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_write( &ctx->uart, data_in, len );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        Delay_1ms ( );
        error_flag = spi_master_write( &ctx->spi, data_in, len );
        Delay_1ms ( );
        spi_master_deselect_device( ctx->chip_select );
        Delay_1ms ( );
    }
    return error_flag;
}

err_t fingerprint5_generic_read ( fingerprint5_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = FINGERPRINT5_OK;
    uint32_t timeout_cnt = 0;
    uint16_t data_cnt = 0;
    if ( FINGERPRINT5_DRV_SEL_UART == ctx->drv_sel ) 
    {
        while ( data_cnt < len )
        {
            if ( timeout_cnt++ > FINGERPRINT5_RX_TIMEOUT_MS )
            {
                error_flag = FINGERPRINT5_ERROR_TIMEOUT;
                break;
            }
            if ( 1 == uart_read( &ctx->uart, &data_out[ data_cnt ], 1 ) )
            {
                data_cnt++;
                timeout_cnt = 0;
            }
            Delay_1ms ( );
        }
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        Delay_1ms ( );
        error_flag = spi_master_read( &ctx->spi, data_out, len );
        Delay_1ms ( );
        spi_master_deselect_device( ctx->chip_select );
        Delay_1ms ( );
    }
    return error_flag;
}

void fingerprint5_set_rst_pin ( fingerprint5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void fingerprint5_reset_device ( fingerprint5_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t fingerprint5_get_irq_pin ( fingerprint5_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

err_t fingerprint5_send_cmd ( fingerprint5_t *ctx )
{
    uint16_t frame_len = ctx->cmd.payload_len + 12;
    ctx->frame[ 0 ] = ( uint8_t ) ( FINGERPRINT5_FRAME_PROTOCOL_VERSION & 0xFF );
    ctx->frame[ 1 ] = ( uint8_t ) ( ( FINGERPRINT5_FRAME_PROTOCOL_VERSION >> 8 ) & 0xFF );
    ctx->frame[ 2 ] = ( uint8_t ) ( FINGERPRINT5_FRAME_TYPE_REQUEST & 0xFF );
    ctx->frame[ 3 ] = ( uint8_t ) ( ( FINGERPRINT5_FRAME_TYPE_REQUEST >> 8 ) & 0xFF );
    ctx->frame[ 4 ] = ( uint8_t ) ( FINGERPRINT5_FRAME_FLAG_HOST & 0xFF );
    ctx->frame[ 5 ] = ( uint8_t ) ( ( FINGERPRINT5_FRAME_FLAG_HOST >> 8 ) & 0xFF );
    ctx->frame[ 6 ] = ( uint8_t ) ( ( ctx->cmd.payload_len + 4 ) & 0xFF );
    ctx->frame[ 7 ] = ( uint8_t ) ( ( ( ctx->cmd.payload_len + 4 ) >> 8 ) & 0xFF );
    ctx->frame[ 8 ] = ( uint8_t ) ( ctx->cmd.cmd_id & 0xFF );
    ctx->frame[ 9 ] = ( uint8_t ) ( ( ctx->cmd.cmd_id >> 8 ) & 0xFF );
    ctx->frame[ 10 ] = ( uint8_t ) ( FINGERPRINT5_FRAME_TYPE_REQUEST & 0xFF );
    ctx->frame[ 11 ] = ( uint8_t ) ( ( FINGERPRINT5_FRAME_TYPE_REQUEST >> 8 ) & 0xFF );
    if ( ctx->cmd.payload_len )
    {
        memcpy ( &ctx->frame[ 12 ], ctx->cmd.payload, ctx->cmd.payload_len );
    }

    return fingerprint5_generic_write ( ctx, ctx->frame, frame_len );
}

err_t fingerprint5_read_cmd ( fingerprint5_t *ctx )
{
    err_t error_flag = FINGERPRINT5_OK;
    uint16_t version = 0;
    uint16_t type = 0;
    uint16_t flags = 0;
    uint32_t timeout_cnt = 0;
    memset ( ctx->frame, 0, FINGERPRINT5_FRAME_MAX_SIZE );
    memset ( &ctx->cmd, 0, sizeof ( ctx->cmd ) );
    
    while ( !fingerprint5_get_irq_pin ( ctx ) )
    {
        if ( timeout_cnt++ > FINGERPRINT5_RX_TIMEOUT_MS )
        {
            error_flag = FINGERPRINT5_ERROR_TIMEOUT;
            break;
        }
        Delay_1ms ( );
    }
    if ( FINGERPRINT5_OK == error_flag )
    {
        error_flag = fingerprint5_generic_read ( ctx, ctx->frame, 12 );
    }
    if ( FINGERPRINT5_OK == error_flag )
    {
        version = ( ( ( uint16_t ) ctx->frame[ 1 ] << 8 ) | ctx->frame[ 0 ] );
        type = ( ( ( uint16_t ) ctx->frame[ 3 ] << 8 ) | ctx->frame[ 2 ] );
        flags = ( ( ( uint16_t ) ctx->frame[ 5 ] << 8 ) | ctx->frame[ 4 ] );
        if ( ( FINGERPRINT5_FRAME_PROTOCOL_VERSION != version ) || 
             ( ( FINGERPRINT5_FRAME_TYPE_RESPONSE != type ) && 
               ( FINGERPRINT5_FRAME_TYPE_EVENT != type ) ) || 
             ( 0 == ( flags & FINGERPRINT5_FRAME_FLAG_FW_APP ) ) )
        {
            error_flag = FINGERPRINT5_ERROR;
        }
    }
    if ( FINGERPRINT5_OK == error_flag )
    {
        ctx->cmd.payload_len = ( ( ( uint16_t ) ctx->frame[ 7 ] << 8 ) | ctx->frame[ 6 ] );
        ctx->cmd.cmd_id = ( ( ( uint16_t ) ctx->frame[ 9 ] << 8 ) | ctx->frame[ 8 ] );
        type = ( ( ( uint16_t ) ctx->frame[ 11 ] << 8 ) | ctx->frame[ 10 ] );
        if ( ( ctx->cmd.payload_len < 4 ) || 
             ( ( FINGERPRINT5_FRAME_TYPE_RESPONSE != type ) && 
               ( FINGERPRINT5_FRAME_TYPE_EVENT != type ) ) )
        {
            error_flag = FINGERPRINT5_ERROR;
        }
    }
    if ( FINGERPRINT5_OK == error_flag )
    {
        ctx->cmd.payload_len -= 4;
        if ( ctx->cmd.payload_len > FINGERPRINT5_FRAME_CMD_MAX_DATA_SIZE )
        {
            ctx->cmd.payload_len = FINGERPRINT5_FRAME_CMD_MAX_DATA_SIZE;
        }
        error_flag = fingerprint5_generic_read ( ctx, &ctx->frame[ 12 ], ctx->cmd.payload_len );
    }
    if ( FINGERPRINT5_OK == error_flag )
    {
        memcpy ( ctx->cmd.payload, &ctx->frame[ 12 ], ctx->cmd.payload_len );
    }
    return error_flag;
}

err_t fingerprint5_get_status ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_STATUS;
    ctx->cmd.payload_len = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_get_version ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_VERSION;
    ctx->cmd.payload_len = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_enroll_finger ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_ENROLL;
    ctx->cmd.payload_len = 4;
    ctx->cmd.payload[ 0 ] = ( uint8_t ) ( FINGERPRINT5_TEMPLATE_ID_TYPE_NEW & 0xFF );
    ctx->cmd.payload[ 1 ] = ( uint8_t ) ( ( FINGERPRINT5_TEMPLATE_ID_TYPE_NEW >> 8 ) & 0xFF );
    ctx->cmd.payload[ 2 ] = 0;
    ctx->cmd.payload[ 3 ] = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_identify_finger ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_IDENTIFY;
    ctx->cmd.payload_len = 6;
    ctx->cmd.payload[ 0 ] = ( uint8_t ) ( FINGERPRINT5_TEMPLATE_ID_TYPE_ALL & 0xFF );
    ctx->cmd.payload[ 1 ] = ( uint8_t ) ( ( FINGERPRINT5_TEMPLATE_ID_TYPE_ALL >> 8 ) & 0xFF );
    ctx->cmd.payload[ 2 ] = 0;
    ctx->cmd.payload[ 3 ] = 0;
    ctx->cmd.payload[ 4 ] = 0;
    ctx->cmd.payload[ 5 ] = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_request_abort ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_ABORT;
    ctx->cmd.payload_len = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_list_templates ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_LIST_TEMPLATES;
    ctx->cmd.payload_len = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_delete_templates ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_DELETE_TEMPLATE;
    ctx->cmd.payload_len = 4;
    ctx->cmd.payload[ 0 ] = ( uint8_t ) ( FINGERPRINT5_TEMPLATE_ID_TYPE_ALL & 0xFF );
    ctx->cmd.payload[ 1 ] = ( uint8_t ) ( ( FINGERPRINT5_TEMPLATE_ID_TYPE_ALL >> 8 ) & 0xFF );
    ctx->cmd.payload[ 2 ] = 0;
    ctx->cmd.payload[ 3 ] = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_request_reset ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_RESET;
    ctx->cmd.payload_len = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_start_navigation ( fingerprint5_t *ctx, uint8_t orientation )
{
    if ( orientation > FINGERPRINT5_NAV_ORIENTATION_270 )
    {
        return FINGERPRINT5_ERROR;
    }
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_NAVIGATION;
    ctx->cmd.payload_len = 4;
    ctx->cmd.payload[ 0 ] = orientation;
    ctx->cmd.payload[ 1 ] = 0;
    ctx->cmd.payload[ 2 ] = 0;
    ctx->cmd.payload[ 3 ] = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_run_bist ( fingerprint5_t *ctx )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_BIST;
    ctx->cmd.payload_len = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_set_gpio ( fingerprint5_t *ctx, uint8_t pin, uint8_t mode, uint8_t state )
{
    if ( ( mode > FINGERPRINT5_GPIO_MODE_INPUT_PULL_DOWN ) || ( state > FINGERPRINT5_GPIO_STATE_SET ) )
    {
        return FINGERPRINT5_ERROR;
    }
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_GPIO_CONTROL;
    ctx->cmd.payload_len = 4;
    ctx->cmd.payload[ 0 ] = FINGERPRINT5_GPIO_SUB_CMD_SET;
    ctx->cmd.payload[ 1 ] = pin;
    ctx->cmd.payload[ 2 ] = mode;
    ctx->cmd.payload[ 3 ] = state;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_get_gpio ( fingerprint5_t *ctx, uint8_t pin )
{
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_GPIO_CONTROL;
    ctx->cmd.payload_len = 4;
    ctx->cmd.payload[ 0 ] = FINGERPRINT5_GPIO_SUB_CMD_GET;
    ctx->cmd.payload[ 1 ] = pin;
    ctx->cmd.payload[ 2 ] = 0;
    ctx->cmd.payload[ 3 ] = 0;
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_set_config ( fingerprint5_t *ctx, fingerprint5_sys_config_t *config )
{
    if ( NULL == config )
    {
        return FINGERPRINT5_ERROR;
    }
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_SET_SYSTEM_CONFIG;
    ctx->cmd.payload_len = 14;
    ctx->cmd.payload[ 0 ] = ( uint8_t ) ( config->version & 0xFF );
    ctx->cmd.payload[ 1 ] = ( uint8_t ) ( ( config->version >> 8 ) & 0xFF );
    ctx->cmd.payload[ 2 ] = ( uint8_t ) ( config->finger_scan_int_ms & 0xFF );
    ctx->cmd.payload[ 3 ] = ( uint8_t ) ( ( config->finger_scan_int_ms >> 8 ) & 0xFF );
    ctx->cmd.payload[ 4 ] = ( uint8_t ) ( config->sys_flags & 0xFF );
    ctx->cmd.payload[ 5 ] = ( uint8_t ) ( ( config->sys_flags >> 8 ) & 0xFF );
    ctx->cmd.payload[ 6 ] = ( uint8_t ) ( ( config->sys_flags >> 16 ) & 0xFF );
    ctx->cmd.payload[ 7 ] = ( uint8_t ) ( ( config->sys_flags >> 24 ) & 0xFF );
    ctx->cmd.payload[ 8 ] = config->uart_irq_delay_ms;
    ctx->cmd.payload[ 9 ] = config->uart_baudrate;
    ctx->cmd.payload[ 10 ] = config->idfy_max_cons_fails;
    ctx->cmd.payload[ 11 ] = config->idfy_lockout_time_s;
    ctx->cmd.payload[ 12 ] = ( uint8_t ) ( config->idle_time_ms & 0xFF );
    ctx->cmd.payload[ 13 ] = ( uint8_t ) ( ( config->idle_time_ms >> 8 ) & 0xFF );
    return fingerprint5_send_cmd ( ctx );
}

err_t fingerprint5_get_config ( fingerprint5_t *ctx, uint8_t type )
{
    if ( type > FINGERPRINT5_SYS_CFG_TYPE_CUSTOM )
    {
        return FINGERPRINT5_ERROR;
    }
    ctx->cmd.cmd_id = FINGERPRINT5_CMD_GET_SYSTEM_CONFIG;
    ctx->cmd.payload_len = 2;
    ctx->cmd.payload[ 0 ] = type;
    ctx->cmd.payload[ 1 ] = 0;
    return fingerprint5_send_cmd ( ctx );
}

// ------------------------------------------------------------------------- END

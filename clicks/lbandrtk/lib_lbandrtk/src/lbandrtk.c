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
 * @file lbandrtk.c
 * @brief LBAND RTK Click Driver.
 */

#include "lbandrtk.h"

/**
 * @brief LBAND RTK I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lbandrtk_i2c_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LBAND RTK I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lbandrtk_i2c_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LBAND RTK SPI writing function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lbandrtk_spi_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LBAND RTK SPI reading function.
 * @details This function reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lbandrtk_spi_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LBAND RTK UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lbandrtk_uart_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LBAND RTK UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lbandrtk_uart_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LBAND RTK calculate checksum function.
 * @details This function calculates the checksum word from the UBX frame buffer.
 * @param[in] data_in : UBX frame buffer starting from class ID byte to calculate the checksum from.
 * @param[in] data_len : Number of bytes to for checksum calculation.
 * @return Calculated checksum word.
 * @note None.
 */
static uint16_t lbandrtk_calculate_checksum ( uint8_t *data_in, uint16_t data_len );

void lbandrtk_cfg_setup ( lbandrtk_cfg_t *cfg ) 
{
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rx_pin  = HAL_PIN_NC;
    cfg->tx_pin  = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->ein     = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LBANDRTK_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;

    cfg->drv_sel = LBANDRTK_DRV_SEL_UART;
}

void lbandrtk_drv_interface_selection ( lbandrtk_cfg_t *cfg, lbandrtk_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t lbandrtk_init ( lbandrtk_t *ctx, lbandrtk_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( LBANDRTK_DRV_SEL_UART == ctx->drv_sel ) 
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
        
        ctx->read_f  = lbandrtk_uart_read;
        ctx->write_f = lbandrtk_uart_write;
    } 
    else if ( LBANDRTK_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = lbandrtk_i2c_read;
        ctx->write_f = lbandrtk_i2c_write;
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

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, LBANDRTK_DUMMY ) ) 
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

        ctx->read_f  = lbandrtk_spi_read;
        ctx->write_f = lbandrtk_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->ein, cfg->ein );

    digital_out_low ( &ctx->ein );
    digital_out_high ( &ctx->rst );

    return LBANDRTK_OK;
}

err_t lbandrtk_generic_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len )
{
    return ctx->write_f( ctx, data_in, len );
}

err_t lbandrtk_generic_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len )
{
    return ctx->read_f( ctx, data_out, len );
}

err_t lbandrtk_write_ubx_frame ( lbandrtk_t *ctx, lbandrtk_ubx_frame_t *frame )
{
    if ( LBANDRTK_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_clear ( &ctx->uart );
    }
    frame->data_buf[ 0 ] = LBANDRTK_PREAMBLE_SYNC_CHAR_1;
    frame->data_buf[ 1 ] = LBANDRTK_PREAMBLE_SYNC_CHAR_2;
    uint16_t checksum = lbandrtk_calculate_checksum ( &frame->data_buf[ 2 ], frame->payload_len + 4 );
    frame->data_buf[ frame->payload_len + 6 ] = ( uint8_t ) ( ( checksum >> 8 ) & 0xFF );
    frame->data_buf[ frame->payload_len + 7 ] = ( uint8_t ) ( checksum & 0xFF );
    return lbandrtk_generic_write( ctx, frame->data_buf, frame->payload_len + 8 );
}

err_t lbandrtk_read_ubx_frame ( lbandrtk_t *ctx, lbandrtk_ubx_frame_t *frame )
{
    uint16_t timeout_cnt = 0;
    while ( ( lbandrtk_generic_read( ctx, frame->data_buf, 1 ) <= 0 ) || 
            ( LBANDRTK_PREAMBLE_SYNC_CHAR_1 != frame->data_buf[ 0 ] ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt > LBANDRTK_TIMEOUT )
        {
            return LBANDRTK_ERROR;
        }
    }
    Delay_10ms( );
    if ( 5 != lbandrtk_generic_read( ctx, &frame->data_buf[ 1 ], 5 ) )
    {
        return LBANDRTK_ERROR;
    }
    if ( LBANDRTK_PREAMBLE_SYNC_CHAR_2 != frame->data_buf[ 1 ] )
    {
        return LBANDRTK_ERROR;
    }
    for ( uint16_t cnt = 0; cnt < frame->payload_len; cnt++ )
    {
        Delay_1ms( );
        Delay_1ms( );
    }
    if ( frame->payload_len != lbandrtk_generic_read( ctx, frame->payload, frame->payload_len ) )
    {
        return LBANDRTK_ERROR;
    }
    if ( 2 != lbandrtk_generic_read( ctx, &frame->data_buf[ frame->payload_len + 6 ], 2 ) )
    {
        return LBANDRTK_ERROR;
    }
    if ( ( ( ( uint16_t ) frame->data_buf[ frame->payload_len + 6 ] << 8 ) | frame->data_buf[ frame->payload_len + 7 ] ) != 
         lbandrtk_calculate_checksum ( &frame->data_buf[ 2 ], frame->payload_len + 4 ) )
    {
        return LBANDRTK_ERROR;
    }
    return LBANDRTK_OK;
}

void lbandrtk_set_rst_pin ( lbandrtk_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void lbandrtk_set_ein_pin ( lbandrtk_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ein, state );
}

void lbandrtk_reset_device ( lbandrtk_t *ctx )
{
    lbandrtk_set_rst_pin ( ctx, 0 );
    Delay_1sec ( );
    lbandrtk_set_rst_pin ( ctx, 1 );
    Delay_1sec ( );
}

err_t lbandrtk_check_ack ( lbandrtk_t *ctx, uint8_t class_id, uint8_t msg_id )
{
    for ( uint8_t retry_cnt = 0; retry_cnt < LBANDRTK_NUM_OF_RETRIES; retry_cnt++ )
    {
        if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( ctx, &ctx->frame ) )
        {
            if ( LBANDRTK_CLASS_ID_UBX_ACK == ctx->frame.class_id )
            {
                if ( ( class_id == ctx->frame.payload[ 0 ] ) && ( msg_id == ctx->frame.payload[ 1 ] ) )
                {
                    return ctx->frame.msg_id;
                }
            }
        }
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_set_val_8 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint8_t value )
{
    if ( ( ( LBANDRTK_KEY_ID_SIZE_1_BIT != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) && 
           ( LBANDRTK_KEY_ID_SIZE_1_BYTE != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) ) || 
         ( layer > LBANDRTK_LAYER_ALL ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALSET;
    ctx->frame.payload_len = 9; // 4 byte header, 4 byte key ID, 1 byte value
    ctx->frame.payload[ 0 ] = 0; // Message version - simplified
    ctx->frame.payload[ 1 ] = layer;
    ctx->frame.payload[ 2 ] = 0; // Reserved
    ctx->frame.payload[ 3 ] = 0; // Reserved
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    ctx->frame.payload[ 8 ] = value;
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
         lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALSET ) )
    {
        return LBANDRTK_OK;
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_set_val_16 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint16_t value )
{
    if ( ( LBANDRTK_KEY_ID_SIZE_2_BYTES != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) || 
         ( layer > LBANDRTK_LAYER_ALL ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALSET;
    ctx->frame.payload_len = 10; // 4 byte header, 4 byte key ID, 2 bytes value
    ctx->frame.payload[ 0 ] = 0; // Message version - simplified
    ctx->frame.payload[ 1 ] = layer;
    ctx->frame.payload[ 2 ] = 0; // Reserved
    ctx->frame.payload[ 3 ] = 0; // Reserved
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    ctx->frame.payload[ 8 ] = ( uint8_t ) ( value & 0xFF );
    ctx->frame.payload[ 9 ] = ( uint8_t ) ( ( value >> 8 ) & 0xFF );
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
         lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALSET ) )
    {
        return LBANDRTK_OK;
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_set_val_32 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t value )
{
    if ( ( LBANDRTK_KEY_ID_SIZE_4_BYTES != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) || 
         ( layer > LBANDRTK_LAYER_ALL ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALSET;
    ctx->frame.payload_len = 12; // 4 byte header, 4 byte key ID, 4 bytes value
    ctx->frame.payload[ 0 ] = 0; // Message version - simplified
    ctx->frame.payload[ 1 ] = layer;
    ctx->frame.payload[ 2 ] = 0; // Reserved
    ctx->frame.payload[ 3 ] = 0; // Reserved
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    ctx->frame.payload[ 8 ] = ( uint8_t ) ( value & 0xFF );
    ctx->frame.payload[ 9 ] = ( uint8_t ) ( ( value >> 8 ) & 0xFF );
    ctx->frame.payload[ 10 ] = ( uint8_t ) ( ( value >> 16 ) & 0xFF );
    ctx->frame.payload[ 11 ] = ( uint8_t ) ( ( value >> 24 ) & 0xFF );
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
         lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALSET ) )
    {
        return LBANDRTK_OK;
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_set_val_64 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t value_high, uint32_t value_low )
{
    if ( ( LBANDRTK_KEY_ID_SIZE_8_BYTES != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) || 
         ( layer > LBANDRTK_LAYER_ALL ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALSET;
    ctx->frame.payload_len = 16; // 4 byte header, 4 byte key ID, 8 bytes value
    ctx->frame.payload[ 0 ] = 0; // Message version - simplified
    ctx->frame.payload[ 1 ] = layer;
    ctx->frame.payload[ 2 ] = 0; // Reserved
    ctx->frame.payload[ 3 ] = 0; // Reserved
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    ctx->frame.payload[ 8 ] = ( uint8_t ) ( value_low & 0xFF );
    ctx->frame.payload[ 9 ] = ( uint8_t ) ( ( value_low >> 8 ) & 0xFF );
    ctx->frame.payload[ 10 ] = ( uint8_t ) ( ( value_low >> 16 ) & 0xFF );
    ctx->frame.payload[ 11 ] = ( uint8_t ) ( ( value_low >> 24 ) & 0xFF );
    ctx->frame.payload[ 12 ] = ( uint8_t ) ( value_high & 0xFF );
    ctx->frame.payload[ 13 ] = ( uint8_t ) ( ( value_high >> 8 ) & 0xFF );
    ctx->frame.payload[ 14 ] = ( uint8_t ) ( ( value_high >> 16 ) & 0xFF );
    ctx->frame.payload[ 15 ] = ( uint8_t ) ( ( value_high >> 24 ) & 0xFF );
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
         lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALSET ) )
    {
        return LBANDRTK_OK;
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_get_val_8 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint8_t *value )
{
    if ( ( ( LBANDRTK_KEY_ID_SIZE_1_BIT != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) && 
           ( LBANDRTK_KEY_ID_SIZE_1_BYTE != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) ) || 
         ( ( LBANDRTK_LAYER_RAM != layer ) && 
           ( LBANDRTK_LAYER_BBR != layer ) && 
           ( LBANDRTK_LAYER_FLASH != layer ) ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALGET;
    ctx->frame.payload_len = 8; // 4 byte header, 4 byte key ID
    ctx->frame.payload[ 0 ] = LBANDRTK_VER_CFG_POLL_REQUEST;
    ctx->frame.payload[ 1 ] = layer >> 1;
    ctx->frame.payload[ 2 ] = 0; // Position zero
    ctx->frame.payload[ 3 ] = 0; // Position zero
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    // Send poll request
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    // Read polled message
    if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( ctx, &ctx->frame ) )
    {
        if ( ( LBANDRTK_CLASS_ID_UBX_CFG == ctx->frame.class_id ) && 
             ( LBANDRTK_MSG_ID_UBX_CFG_VALGET == ctx->frame.msg_id ) && 
             ( LBANDRTK_VER_CFG_POLLED == ctx->frame.payload[ 0 ] ) )
        {
            *value = ctx->frame.payload[ 8 ];
            if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
                 lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALGET ) )
            {
                return LBANDRTK_OK;
            }
        }
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_get_val_16 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint16_t *value )
{
    if ( ( LBANDRTK_KEY_ID_SIZE_2_BYTES != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) || 
         ( ( LBANDRTK_LAYER_RAM != layer ) && 
           ( LBANDRTK_LAYER_BBR != layer ) && 
           ( LBANDRTK_LAYER_FLASH != layer ) ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALGET;
    ctx->frame.payload_len = 8; // 4 byte header, 4 byte key ID
    ctx->frame.payload[ 0 ] = LBANDRTK_VER_CFG_POLL_REQUEST;
    ctx->frame.payload[ 1 ] = layer >> 1;
    ctx->frame.payload[ 2 ] = 0; // Position zero
    ctx->frame.payload[ 3 ] = 0; // Position zero
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    // Send poll request
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    // Read polled message
    if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( ctx, &ctx->frame ) )
    {
        if ( ( LBANDRTK_CLASS_ID_UBX_CFG == ctx->frame.class_id ) && 
             ( LBANDRTK_MSG_ID_UBX_CFG_VALGET == ctx->frame.msg_id ) && 
             ( LBANDRTK_VER_CFG_POLLED == ctx->frame.payload[ 0 ] ) )
        {
            *value = ( ( uint16_t ) ctx->frame.payload[ 9 ] << 8 ) | ctx->frame.payload[ 8 ];
            if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
                 lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALGET ) )
            {
                return LBANDRTK_OK;
            }
        }
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_get_val_32 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t *value )
{
    if ( ( LBANDRTK_KEY_ID_SIZE_4_BYTES != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) || 
         ( ( LBANDRTK_LAYER_RAM != layer ) && 
           ( LBANDRTK_LAYER_BBR != layer ) && 
           ( LBANDRTK_LAYER_FLASH != layer ) ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALGET;
    ctx->frame.payload_len = 8; // 4 byte header, 4 byte key ID
    ctx->frame.payload[ 0 ] = LBANDRTK_VER_CFG_POLL_REQUEST;
    ctx->frame.payload[ 1 ] = layer >> 1;
    ctx->frame.payload[ 2 ] = 0; // Position zero
    ctx->frame.payload[ 3 ] = 0; // Position zero
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    // Send poll request
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    // Read polled message
    if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( ctx, &ctx->frame ) )
    {
        if ( ( LBANDRTK_CLASS_ID_UBX_CFG == ctx->frame.class_id ) && 
             ( LBANDRTK_MSG_ID_UBX_CFG_VALGET == ctx->frame.msg_id ) && 
             ( LBANDRTK_VER_CFG_POLLED == ctx->frame.payload[ 0 ] ) )
        {
            *value = ( ( uint32_t ) ctx->frame.payload[ 11 ] << 24 ) | ( ( uint32_t ) ctx->frame.payload[ 10 ] << 16 ) | 
                     ( ( uint16_t ) ctx->frame.payload[ 9 ] << 8 ) | ctx->frame.payload[ 8 ];
            if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
                 lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALGET ) )
            {
                return LBANDRTK_OK;
            }
        }
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_get_val_64 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t *value_high, uint32_t *value_low )
{
    if ( ( LBANDRTK_KEY_ID_SIZE_8_BYTES != ( key_id & LBANDRTK_KEY_ID_SIZE_MASK ) ) || 
         ( ( LBANDRTK_LAYER_RAM != layer ) && 
           ( LBANDRTK_LAYER_BBR != layer ) && 
           ( LBANDRTK_LAYER_FLASH != layer ) ) )
    {
        return LBANDRTK_ERROR;
    }
    ctx->frame.class_id = LBANDRTK_CLASS_ID_UBX_CFG;
    ctx->frame.msg_id = LBANDRTK_MSG_ID_UBX_CFG_VALGET;
    ctx->frame.payload_len = 8; // 4 byte header, 4 byte key ID
    ctx->frame.payload[ 0 ] = LBANDRTK_VER_CFG_POLL_REQUEST;
    ctx->frame.payload[ 1 ] = layer >> 1;
    ctx->frame.payload[ 2 ] = 0; // Position zero
    ctx->frame.payload[ 3 ] = 0; // Position zero
    ctx->frame.payload[ 4 ] = ( uint8_t ) ( key_id & 0xFF );
    ctx->frame.payload[ 5 ] = ( uint8_t ) ( ( key_id >> 8 ) & 0xFF );
    ctx->frame.payload[ 6 ] = ( uint8_t ) ( ( key_id >> 16 ) & 0xFF );
    ctx->frame.payload[ 7 ] = ( uint8_t ) ( ( key_id >> 24 ) & 0xFF );
    // Send poll request
    lbandrtk_write_ubx_frame ( ctx, &ctx->frame );
    Delay_10ms ( );
    // Read polled message
    if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( ctx, &ctx->frame ) )
    {
        if ( ( LBANDRTK_CLASS_ID_UBX_CFG == ctx->frame.class_id ) && 
             ( LBANDRTK_MSG_ID_UBX_CFG_VALGET == ctx->frame.msg_id ) && 
             ( LBANDRTK_VER_CFG_POLLED == ctx->frame.payload[ 0 ] ) )
        {
            *value_low = ( ( uint32_t ) ctx->frame.payload[ 11 ] << 24 ) | ( ( uint32_t ) ctx->frame.payload[ 10 ] << 16 ) | 
                         ( ( uint16_t ) ctx->frame.payload[ 9 ] << 8 ) | ctx->frame.payload[ 8 ];
            *value_high = ( ( uint32_t ) ctx->frame.payload[ 15 ] << 24 ) | ( ( uint32_t ) ctx->frame.payload[ 14 ] << 16 ) | 
                          ( ( uint16_t ) ctx->frame.payload[ 13 ] << 8 ) | ctx->frame.payload[ 12 ];
            if ( LBANDRTK_MSG_ID_UBX_ACK_ACK == 
                 lbandrtk_check_ack ( ctx, LBANDRTK_CLASS_ID_UBX_CFG, LBANDRTK_MSG_ID_UBX_CFG_VALGET ) )
            {
                return LBANDRTK_OK;
            }
        }
    }
    return LBANDRTK_ERROR;
}

err_t lbandrtk_set_default_pmp_cfg ( lbandrtk_t *ctx )
{
    lbandrtk_pmp_cfg_t pmp_cfg;
    pmp_cfg.center_freq = LBANDRTK_PMP_CENTER_FREQ;
    pmp_cfg.search_window = LBANDRTK_PMP_SEARCH_WINDOW;
    pmp_cfg.use_service_id = LBANDRTK_PMP_USE_SERVICE_ID;
    pmp_cfg.service_id = LBANDRTK_PMP_SERVICE_ID;
    pmp_cfg.data_rate = LBANDRTK_PMP_DATA_RATE;
    pmp_cfg.use_descrambler = LBANDRTK_PMP_USE_DESCRAMBLER;
    pmp_cfg.descrambler_init = LBANDRTK_PMP_DESCRAMBLER_INIT;
    pmp_cfg.use_prescrambling = LBANDRTK_PMP_USE_PRESCRAMBLING;
    pmp_cfg.unique_word_high = LBANDRTK_PMP_UNIQUE_WORD_HIGH;
    pmp_cfg.unique_word_low = LBANDRTK_PMP_UNIQUE_WORD_LOW;
    return lbandrtk_set_pmp_cfg ( ctx, pmp_cfg );
}

err_t lbandrtk_set_pmp_cfg ( lbandrtk_t *ctx, lbandrtk_pmp_cfg_t pmp_cfg )
{
    err_t error_flag = LBANDRTK_OK;
    error_flag |= lbandrtk_set_val_32 ( ctx, LBANDRTK_CFG_PMP_CENTER_FREQUENCY, LBANDRTK_LAYER_RAM, pmp_cfg.center_freq );
    error_flag |= lbandrtk_set_val_16 ( ctx, LBANDRTK_CFG_PMP_SEARCH_WINDOW, LBANDRTK_LAYER_RAM, pmp_cfg.search_window );
    error_flag |= lbandrtk_set_val_8 ( ctx, LBANDRTK_CFG_PMP_USE_SERVICE_ID, LBANDRTK_LAYER_RAM, pmp_cfg.use_service_id );
    error_flag |= lbandrtk_set_val_16 ( ctx, LBANDRTK_CFG_PMP_SERVICE_ID, LBANDRTK_LAYER_RAM, pmp_cfg.service_id );
    error_flag |= lbandrtk_set_val_16 ( ctx, LBANDRTK_CFG_PMP_DATA_RATE, LBANDRTK_LAYER_RAM, pmp_cfg.data_rate );
    error_flag |= lbandrtk_set_val_8 ( ctx, LBANDRTK_CFG_PMP_USE_DESCRAMBLER, LBANDRTK_LAYER_RAM, pmp_cfg.use_descrambler );
    error_flag |= lbandrtk_set_val_16 ( ctx, LBANDRTK_CFG_PMP_DESCRAMBLER_INIT, LBANDRTK_LAYER_RAM, pmp_cfg.descrambler_init );
    error_flag |= lbandrtk_set_val_8 ( ctx, LBANDRTK_CFG_PMP_USE_PRESCRAMBLING, LBANDRTK_LAYER_RAM, pmp_cfg.use_prescrambling );
    error_flag |= lbandrtk_set_val_64 ( ctx, LBANDRTK_CFG_PMP_UNIQUE_WORD, LBANDRTK_LAYER_RAM, 
                                        pmp_cfg.unique_word_high, pmp_cfg.unique_word_low );
    return error_flag;
}

err_t lbandrtk_get_pmp_cfg ( lbandrtk_t *ctx, lbandrtk_pmp_cfg_t *pmp_cfg )
{
    err_t error_flag = LBANDRTK_OK;
    error_flag |= lbandrtk_get_val_32 ( ctx, LBANDRTK_CFG_PMP_CENTER_FREQUENCY, LBANDRTK_LAYER_RAM, &pmp_cfg->center_freq );
    error_flag |= lbandrtk_get_val_16 ( ctx, LBANDRTK_CFG_PMP_SEARCH_WINDOW, LBANDRTK_LAYER_RAM, &pmp_cfg->search_window );
    error_flag |= lbandrtk_get_val_8 ( ctx, LBANDRTK_CFG_PMP_USE_SERVICE_ID, LBANDRTK_LAYER_RAM, &pmp_cfg->use_service_id );
    error_flag |= lbandrtk_get_val_16 ( ctx, LBANDRTK_CFG_PMP_SERVICE_ID, LBANDRTK_LAYER_RAM, &pmp_cfg->service_id );
    error_flag |= lbandrtk_get_val_16 ( ctx, LBANDRTK_CFG_PMP_DATA_RATE, LBANDRTK_LAYER_RAM, &pmp_cfg->data_rate );
    error_flag |= lbandrtk_get_val_8 ( ctx, LBANDRTK_CFG_PMP_USE_DESCRAMBLER, LBANDRTK_LAYER_RAM, &pmp_cfg->use_descrambler );
    error_flag |= lbandrtk_get_val_16 ( ctx, LBANDRTK_CFG_PMP_DESCRAMBLER_INIT, LBANDRTK_LAYER_RAM, &pmp_cfg->descrambler_init );
    error_flag |= lbandrtk_get_val_8 ( ctx, LBANDRTK_CFG_PMP_USE_PRESCRAMBLING, LBANDRTK_LAYER_RAM, &pmp_cfg->use_prescrambling );
    error_flag |= lbandrtk_get_val_64 ( ctx, LBANDRTK_CFG_PMP_UNIQUE_WORD, LBANDRTK_LAYER_RAM, 
                                        &pmp_cfg->unique_word_high, &pmp_cfg->unique_word_low );
    return error_flag;
}

static err_t lbandrtk_i2c_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t lbandrtk_i2c_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    if ( I2C_MASTER_ERROR == i2c_master_read( &ctx->i2c, data_out, len ) )
    {
        return LBANDRTK_ERROR;
    }
    return len;
}

static err_t lbandrtk_spi_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t lbandrtk_spi_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    if ( SPI_MASTER_ERROR == error_flag )
    {
        return LBANDRTK_ERROR;
    }
    return len;
}

static err_t lbandrtk_uart_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t lbandrtk_uart_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

static uint16_t lbandrtk_calculate_checksum ( uint8_t *data_in, uint16_t data_len )
{
    uint32_t ck_a = 0, ck_b = 0;
    for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
    {
        ck_a = ck_a + data_in[ cnt ];
        ck_b = ck_b + ck_a;
    }
    return ( uint16_t ) ( ( ( ck_a & 0xFF ) << 8 ) | ( ck_b & 0xFF ) );
}

// ------------------------------------------------------------------------ END

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
 * @file tfmini.c
 * @brief TFmini Click Driver.
 */

#include "tfmini.h"

void tfmini_cfg_setup ( tfmini_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->i2c_speed      = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address    = TFMINI_SET_DEV_ADDR;
    
    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
    cfg->drv_sel = TFMINI_DRV_SEL_UART;
}

void tfmini_drv_interface_selection ( tfmini_cfg_t *cfg, tfmini_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t tfmini_init ( tfmini_t *ctx, tfmini_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( TFMINI_DRV_SEL_UART == ctx->drv_sel ) 
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
    } 
    else 
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
    }
    return TFMINI_OK;
}

err_t tfmini_default_cfg ( tfmini_t *ctx ) 
{
    err_t error_flag = TFMINI_OK;
    Delay_100ms ( );
    if ( TFMINI_DRV_SEL_UART == ctx->drv_sel ) 
    {
        error_flag |= tfmini_set_frame_rate ( ctx, 10 );
        Delay_100ms ( );
        error_flag |= tfmini_save_settings( ctx );
        Delay_100ms ( );
    }
    return error_flag;
}

err_t tfmini_send_frame ( tfmini_t *ctx, tfmini_frame_t frame ) 
{
    uint8_t frame_buf[ TFMINI_FRAME_SIZE + 4 ] = { 0 };
    frame_buf[ 0 ] = TFMINI_CMD_HEADER;
    frame_buf[ 1 ] = frame.payload_len + 4;
    frame_buf[ 2 ] = frame.cmd_id;
    uint8_t checksum = frame_buf[ 0 ] + frame_buf[ 1 ] + frame_buf[ 2 ];
    for ( uint8_t cnt = 0; cnt < frame.payload_len; cnt++ )
    {
        frame_buf[ cnt + 3 ] = frame.payload[ cnt ];
        checksum += frame.payload[ cnt ];
    }
    frame_buf[ frame.payload_len + 3 ] = checksum;
    
    if ( TFMINI_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_clear ( &ctx->uart );
        if ( ( frame.payload_len + 4 ) == uart_write( &ctx->uart, frame_buf, frame.payload_len + 4 ) )
        {
            return TFMINI_OK;
        }
    }
    else
    {
        return i2c_master_write( &ctx->i2c, frame_buf, frame.payload_len + 4 );
    }
    return TFMINI_ERROR;
}

err_t tfmini_get_response ( tfmini_t *ctx, tfmini_frame_t *frame ) 
{
    if ( TFMINI_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uint8_t header = 0;
        uint8_t num_chars_read = 0;
        for ( ; ; ) 
        {
            if ( uart_read( &ctx->uart, &header, 1 ) > 0 )
            {
                if ( TFMINI_CMD_HEADER == header ) 
                {
                    break; // Break to begin frame
                }
                else
                {
                    num_chars_read++;
                }
            }
            if ( num_chars_read > TFMINI_MAX_BYTES_BEFORE_HEADER )
            {
                return TFMINI_NO_HEADER_FOUND;
            }
        }
        uint8_t checksum = TFMINI_CMD_HEADER;
        while ( uart_read( &ctx->uart, &frame->payload_len, 1 ) <= 0 );
        checksum += frame->payload_len;
        frame->payload_len -= 4;
        
        while ( uart_read( &ctx->uart, &frame->cmd_id, 1 ) <= 0 );
        checksum += frame->cmd_id;
        
        for ( uint8_t cnt = 0; cnt < frame->payload_len; cnt++ )
        {
            while ( uart_read( &ctx->uart, &frame->payload[ cnt ], 1 ) <= 0 );
            checksum += frame->payload[ cnt ];
        }
        uint8_t checksum_read = 0;
        while ( uart_read( &ctx->uart, &checksum_read, 1 ) <= 0 );
        if ( checksum != checksum_read )
        {
            return TFMINI_WRONG_CHECKSUM;
        }
        return TFMINI_OK;
    }
    else
    {
        uint8_t rx_buf[ TFMINI_MAX_BYTES_BEFORE_HEADER ] = { 0 };
        err_t error_flag = i2c_master_read( &ctx->i2c, rx_buf, frame->payload_len + 4 );
        if ( TFMINI_OK == error_flag )
        {
            if ( TFMINI_CMD_HEADER != rx_buf[ 0 ] ) 
            {
                return TFMINI_NO_HEADER_FOUND;
            }
            frame->payload_len = rx_buf[ 1 ] - 4;
            frame->cmd_id = rx_buf[ 2 ];
            memcpy ( &frame->payload, &rx_buf[ 3 ], frame->payload_len );
            uint8_t checksum = rx_buf[ 0 ] + rx_buf[ 1 ] + rx_buf[ 2 ];
            for ( uint8_t cnt = 0; cnt < frame->payload_len; cnt++ )
            {
                checksum += frame->payload[ cnt ];
            }
            if ( checksum == rx_buf[ frame->payload_len + 3 ] )
            {
                return TFMINI_OK;
            }
            else
            {
                return TFMINI_WRONG_CHECKSUM;
            }
        }
        return TFMINI_ERROR;
    }
}

err_t tfmini_get_firmware_version ( tfmini_t *ctx, uint32_t *fw_version )
{
    tfmini_frame_t frame;
    frame.cmd_id = TFMINI_CMD_ID_FW_VERSION;
    frame.payload_len = 0;
    if ( TFMINI_OK == tfmini_send_frame ( ctx, frame ) )
    {
        if ( TFMINI_DRV_SEL_I2C == ctx->drv_sel )
        {
            frame.payload_len = 3;
            Delay_100ms( );
        }
        while ( TFMINI_OK == tfmini_get_response ( ctx, &frame ) )
        {
            if ( TFMINI_CMD_ID_FW_VERSION == frame.cmd_id )
            {
                *fw_version = frame.payload[ 2 ];
                *fw_version <<= 8;
                *fw_version |= frame.payload[ 1 ];
                *fw_version <<= 8;
                *fw_version |= frame.payload[ 0 ];
                return TFMINI_OK;
            }
        }
    }
    return TFMINI_ERROR;
}

err_t tfmini_system_reset ( tfmini_t *ctx )
{
    tfmini_frame_t frame;
    frame.cmd_id = TFMINI_CMD_ID_SYSTEM_RESET;
    frame.payload_len = 0;
    if ( TFMINI_OK == tfmini_send_frame ( ctx, frame ) )
    {
        if ( TFMINI_DRV_SEL_I2C == ctx->drv_sel )
        {
            frame.payload_len = 1;
            Delay_100ms( );
        }
        while ( TFMINI_OK == tfmini_get_response ( ctx, &frame ) )
        {
            if ( TFMINI_CMD_ID_SYSTEM_RESET == frame.cmd_id )
            {
                return ( TFMINI_OK == frame.payload[ 0 ] ) ? TFMINI_OK : TFMINI_ERROR;
            }
        }
    }
    return TFMINI_ERROR;
}

err_t tfmini_set_frame_rate ( tfmini_t *ctx, uint16_t frame_rate )
{
    if ( ( frame_rate < 1 ) || ( frame_rate > 1000 ) )
    {
        return TFMINI_ERROR;
    }
    tfmini_frame_t frame;
    frame.cmd_id = TFMINI_CMD_ID_FRAME_RATE;
    frame.payload[ 0 ] = ( uint8_t ) ( frame_rate & 0xFF );
    frame.payload[ 1 ] = ( uint8_t ) ( ( frame_rate >> 8 ) & 0xFF );
    frame.payload_len = 2;
    if ( TFMINI_OK == tfmini_send_frame ( ctx, frame ) )
    {
        while ( TFMINI_OK == tfmini_get_response ( ctx, &frame ) )
        {
            if ( TFMINI_CMD_ID_FRAME_RATE == frame.cmd_id )
            {
                return TFMINI_OK;
            }
        }
    }
    return TFMINI_ERROR;
}

err_t tfmini_change_interface ( tfmini_t *ctx, tfmini_drv_t drv_sel )
{
    tfmini_frame_t frame;
    frame.cmd_id = TFMINI_CMD_ID_COM_SELECTION;
    frame.payload[ 0 ] = drv_sel;
    frame.payload_len = 1;
    return tfmini_send_frame ( ctx, frame );
}

err_t tfmini_factory_default ( tfmini_t *ctx )
{
    tfmini_frame_t frame;
    frame.cmd_id = TFMINI_CMD_ID_RESTORE_FACTORY;
    frame.payload_len = 0;
    if ( TFMINI_OK == tfmini_send_frame ( ctx, frame ) )
    {
        if ( TFMINI_DRV_SEL_I2C == ctx->drv_sel )
        {
            frame.payload_len = 1;
            Delay_1sec ( );
            Delay_1sec ( );
        }
        while ( TFMINI_OK == tfmini_get_response ( ctx, &frame ) )
        {
            if ( TFMINI_CMD_ID_RESTORE_FACTORY == frame.cmd_id )
            {
                return ( TFMINI_OK == frame.payload[ 0 ] ) ? TFMINI_OK : TFMINI_ERROR;
            }
        }
    }
    return TFMINI_ERROR;
}

err_t tfmini_save_settings ( tfmini_t *ctx )
{
    tfmini_frame_t frame;
    frame.cmd_id = TFMINI_CMD_ID_SAVE_SETTINGS;
    frame.payload_len = 0;
    if ( TFMINI_OK == tfmini_send_frame ( ctx, frame ) )
    {
        if ( TFMINI_DRV_SEL_I2C == ctx->drv_sel )
        {
            frame.payload_len = 1;
            Delay_1sec ( );
            Delay_1sec ( );
        }
        while ( TFMINI_OK == tfmini_get_response ( ctx, &frame ) )
        {
            if ( TFMINI_CMD_ID_SAVE_SETTINGS == frame.cmd_id )
            {
                return ( TFMINI_OK == frame.payload[ 0 ] ) ? TFMINI_OK : TFMINI_ERROR;
            }
        }
    }
    return TFMINI_ERROR;
}

err_t tfmini_get_measurement ( tfmini_t *ctx, int16_t *distance, int16_t *strength, float *temperature ) 
{
    uint8_t rx_buf[ TFMINI_FRAME_SIZE + 2 ] = { 0 };
    if ( TFMINI_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uint8_t num_chars_read = 0;
        for ( ; ; ) 
        {
            if ( uart_read( &ctx->uart, &rx_buf[ 1 ], 1 ) > 0 )
            {
                if ( ( TFMINI_HEADER == rx_buf[ 0 ] ) && ( TFMINI_HEADER == rx_buf[ 1 ] ) ) 
                {
                    break; // Break to begin frame
                }
                else
                {
                    rx_buf[ 0 ] = rx_buf[ 1 ];
                    num_chars_read++;
                }
            }
            if ( num_chars_read > TFMINI_MAX_BYTES_BEFORE_HEADER )
            {
                return TFMINI_NO_HEADER_FOUND;
            }
        }
        for ( uint8_t cnt = 0; cnt < TFMINI_FRAME_SIZE; cnt++ )
        {
            while ( uart_read( &ctx->uart, &rx_buf[ cnt + 2 ], 1 ) <= 0 );
        }
    }
    else
    {
        tfmini_frame_t frame;
        frame.cmd_id = TFMINI_CMD_ID_DATA_FRAME;
        frame.payload[ 0 ] = 1;
        frame.payload_len = 1;
        err_t error_flag = tfmini_send_frame ( ctx, frame );
        Delay_100ms ( );
        error_flag |= i2c_master_read( &ctx->i2c, rx_buf, TFMINI_FRAME_SIZE + 2 );
        if ( TFMINI_ERROR == error_flag )
        {
            return TFMINI_ERROR;
        }
    }
    uint8_t checksum = 0;
    for ( uint8_t cnt = 0; cnt < ( TFMINI_FRAME_SIZE + 1 ); cnt++ )
    {
        checksum += rx_buf[ cnt ];
    }
    if ( checksum != rx_buf[ TFMINI_FRAME_SIZE + 1 ] )
    {
        return TFMINI_WRONG_CHECKSUM;
    }
    *distance = ( ( int16_t ) rx_buf[ 3 ] << 8 ) | rx_buf[ 2 ];
    *strength = ( ( int16_t ) rx_buf[ 5 ] << 8 ) | rx_buf[ 4 ];
    int16_t raw_temp = ( ( int16_t ) rx_buf[ 7 ] << 8 ) | rx_buf[ 6 ];
    *temperature = ( ( float ) raw_temp / 8 ) - 256;
    
    if ( TFMINI_LOW_SIGNAL_STRENGTH == *distance )
    {
        return TFMINI_LOW_SIGNAL_STRENGTH;
    }
    else if ( TFMINI_SIGNAL_STRENGTH_SATURATION == *distance )
    {
        return TFMINI_SIGNAL_STRENGTH_SATURATION;
    }
    else if ( TFMINI_AMBIENT_LIGHT_SATURATION == *distance )
    {
        return TFMINI_AMBIENT_LIGHT_SATURATION;
    }
    return TFMINI_OK;
}

// ------------------------------------------------------------------------- END

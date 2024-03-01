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
 * @file stepper5.c
 * @brief Stepper 5 Click Driver.
 */

#include "stepper5.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper5_speed_delay ( uint8_t speed_macro );

/** 
 * @brief CRC8-ATM calculation function.
 * @details This function calculates CRC8-ATM with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x +1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input True
 * @li @c  Reflect output False
 * @li @c  Final NO XOR
 * @param[in] data_buf : Array of bytes to calculate CRC8-ATM from.
 * @param[in] len : Number of bytes to calculate CRC8-ATM from.
 * @return Calculated CRC8-ATM byte.
 * @note None.
 */
static uint8_t stepper5_calculate_crc ( uint8_t *data_buf, uint8_t len );

void stepper5_cfg_setup ( stepper5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->diag = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->ind = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t stepper5_init ( stepper5_t *ctx, stepper5_cfg_t *cfg ) 
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

    // Output pins
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->step, cfg->step );

    // Input pins
    digital_in_init( &ctx->diag, cfg->diag );
    digital_in_init( &ctx->ind, cfg->ind );

    uint8_t dummy = 0;
    uart_read( &ctx->uart, &dummy, 1 );

    return UART_SUCCESS;
}

err_t stepper5_default_cfg ( stepper5_t *ctx ) 
{
    err_t error_flag = STEPPER5_OK;
    stepper5_disable_device ( ctx );
    stepper5_set_direction ( ctx, STEPPER5_DIR_CW );
    Delay_100ms ( );
    if ( STEPPER5_OK != stepper5_check_com ( ctx ) )
    {
        return STEPPER5_ERROR;
    }
    uint32_t reg_data = 0;
    stepper5_read_reg ( ctx, STEPPER5_REG_GCONF, &reg_data );
    reg_data &= ~( STEPPER5_GCONF_MSTEP_REG_SELECT_MSTEP | STEPPER5_GCONF_PDN_DISABLE_UART_EN );
    reg_data |= ( STEPPER5_GCONF_MSTEP_REG_SELECT_MSTEP | STEPPER5_GCONF_PDN_DISABLE_UART_EN );
    stepper5_write_reg ( ctx, STEPPER5_REG_GCONF, reg_data );
    Delay_10ms ( );
    error_flag |= stepper5_set_toff ( ctx, STEPPER5_TOFF_DRIVER_DISABLE );
    Delay_10ms ( );
    error_flag |= stepper5_set_run_current ( ctx, STEPPER5_IRUN_DEFAULT );
    Delay_10ms ( );
    error_flag |= stepper5_set_step_res ( ctx, STEPPER5_MRES_FULLSTEP );
    return error_flag;
}

void stepper5_write_reg ( stepper5_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = STEPPER5_UART_SYNC_BYTE;
    data_buf[ 1 ] = STEPPER5_UART_SLAVE_ADDRESS;
    data_buf[ 2 ] = reg | STEPPER5_UART_WRITE_BIT;
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 7 ] = stepper5_calculate_crc ( data_buf, 7 );
    uart_write( &ctx->uart, data_buf, 8 );
    Delay_10ms ( );
}

err_t stepper5_read_reg ( stepper5_t *ctx, uint8_t reg, uint32_t *data_out )
{
    uint8_t data_buf[ 12 ] = { 0 };
    data_buf[ 0 ] = STEPPER5_UART_SYNC_BYTE;
    data_buf[ 1 ] = STEPPER5_UART_SLAVE_ADDRESS;
    data_buf[ 2 ] = reg & ( ~STEPPER5_UART_WRITE_BIT );
    data_buf[ 3 ] = stepper5_calculate_crc ( data_buf, 3 );
    uart_clear ( &ctx->uart );
    uart_write( &ctx->uart, data_buf, 4 );
    Delay_10ms ( );
    if ( 12 != uart_read( &ctx->uart, data_buf, 12 ) )
    {
        return STEPPER5_ERROR;
    }
    if ( data_buf[ 11 ] != stepper5_calculate_crc ( &data_buf[ 4 ], 7 ) )
    {
        return STEPPER5_ERROR;
    }
    *data_out = ( ( uint32_t ) data_buf[ 7 ] << 24 ) | ( ( uint32_t ) data_buf[ 8 ] << 16 ) | 
                ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 10 ];
    return STEPPER5_OK;
}

err_t stepper5_check_com ( stepper5_t *ctx )
{
    uint32_t reg_data = 0;
    if ( STEPPER5_OK == stepper5_read_reg ( ctx, STEPPER5_REG_IOIN, &reg_data ) )
    {
        if ( STEPPER5_IOIN_VERSION_DEFAULT == ( reg_data & STEPPER5_IOIN_VERSION_MASK ) )
        {
            return STEPPER5_OK;
        }
    }
    return STEPPER5_ERROR;
}

void stepper5_enable_device ( stepper5_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper5_disable_device ( stepper5_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper5_set_direction ( stepper5_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper5_switch_direction ( stepper5_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper5_set_step_pin ( stepper5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

uint8_t stepper5_get_diag_pin ( stepper5_t *ctx )
{
    return digital_in_read ( &ctx->diag );
}

uint8_t stepper5_get_index_pin ( stepper5_t *ctx )
{
    return digital_in_read ( &ctx->ind );
}

err_t stepper5_set_toff ( stepper5_t *ctx, uint8_t toff )
{
    uint32_t reg_data = 0;
    if ( toff > STEPPER5_TOFF_MAX )
    {
        return STEPPER5_ERROR;
    }
    if ( STEPPER5_ERROR == stepper5_read_reg ( ctx, STEPPER5_REG_CHOPCONF, &reg_data ) )
    {
        return STEPPER5_ERROR;
    }
    if ( ( ( uint32_t ) toff << STEPPER5_TOFF_SHIFT ) == ( reg_data & STEPPER5_TOFF_MASK ) )
    {
        return STEPPER5_OK;
    }
    reg_data &= ~STEPPER5_TOFF_MASK;
    reg_data |= ( ( uint32_t ) toff << STEPPER5_TOFF_SHIFT );
    stepper5_write_reg ( ctx, STEPPER5_REG_CHOPCONF, reg_data );
    return STEPPER5_OK;
}

err_t stepper5_set_step_res ( stepper5_t *ctx, uint8_t mres )
{
    uint32_t reg_data = 0;
    if ( mres > STEPPER5_MRES_FULLSTEP )
    {
        return STEPPER5_ERROR;
    }
    if ( STEPPER5_ERROR == stepper5_read_reg ( ctx, STEPPER5_REG_CHOPCONF, &reg_data ) )
    {
        return STEPPER5_ERROR;
    }
    if ( ( ( uint32_t ) mres << STEPPER5_MRES_SHIFT ) == ( reg_data & STEPPER5_MRES_MASK ) )
    {
        return STEPPER5_OK;
    }
    reg_data &= ~STEPPER5_MRES_MASK;
    reg_data |= ( ( uint32_t ) mres << STEPPER5_MRES_SHIFT );
    stepper5_write_reg ( ctx, STEPPER5_REG_CHOPCONF, reg_data );
    return STEPPER5_OK;
}

err_t stepper5_set_run_current ( stepper5_t *ctx, uint8_t irun )
{
    uint32_t reg_data = 0;
    if ( irun > STEPPER5_IRUN_MAX )
    {
        return STEPPER5_ERROR;
    }
    if ( STEPPER5_ERROR == stepper5_read_reg ( ctx, STEPPER5_REG_IHOLD_IRUN, &reg_data ) )
    {
        return STEPPER5_ERROR;
    }
    if ( ( ( uint32_t ) irun << STEPPER5_IRUN_SHIFT ) == ( reg_data & STEPPER5_IRUN_MASK ) )
    {
        return STEPPER5_OK;
    }
    reg_data &= ~STEPPER5_IRUN_MASK;
    reg_data |= ( ( uint32_t ) irun << STEPPER5_IRUN_SHIFT );
    stepper5_write_reg ( ctx, STEPPER5_REG_IHOLD_IRUN, reg_data );
    return STEPPER5_OK;
}

void stepper5_drive_motor ( stepper5_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper5_set_toff ( ctx, STEPPER5_TOFF_DEFAULT );
    stepper5_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper5_set_step_pin ( ctx, STEPPER5_PIN_STATE_HIGH );
        stepper5_speed_delay ( speed );
        stepper5_set_step_pin ( ctx, STEPPER5_PIN_STATE_LOW );
        stepper5_speed_delay ( speed );
    }
    stepper5_disable_device ( ctx );
    stepper5_set_toff ( ctx, STEPPER5_TOFF_DRIVER_DISABLE );
}

static void stepper5_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER5_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER5_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER5_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER5_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER5_SPEED_VERY_FAST:
        {
            Delay_1ms( );
            break;
        }
        default:
        {
            Delay_5ms( );
            break;
        }
    }
}

static uint8_t stepper5_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    for ( uint8_t cnt_byte = 0; cnt_byte < len; cnt_byte++ ) 
    {
        uint8_t curr_byte = data_buf[ cnt_byte ];
        for ( uint8_t cnt_bit = 0; cnt_bit < 8; cnt_bit++ ) 
        {
            if ( ( crc >> 7 ) ^ ( curr_byte & 0x01 ) )
            {    
                crc = ( uint8_t )( ( crc << 1 ) ^ 0x07 );
            }
            else
            {
                crc <<= 1;
            }
            curr_byte >>= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END

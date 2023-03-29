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
 * @file rs232toi2c.c
 * @brief RS232 to I2C Click Driver.
 */

#include "rs232toi2c.h"

void rs232toi2c_cfg_setup ( rs232toi2c_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RS232TOI2C_SET_DEV_ADDR_A2_GND;
}

err_t rs232toi2c_init ( rs232toi2c_t *ctx, rs232toi2c_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wp, cfg->wp );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rs232toi2c_default_cfg ( rs232toi2c_t *ctx ) 
{
    err_t error_flag = RS232TOI2C_OK;
    
    rs232toi2c_reset_device ( ctx );
    rs232toi2c_set_wp_pin ( ctx, 0 );
    
    // set all GPIO to output direction
    error_flag |= rs232toi2c_write_gpio_config ( ctx, RS232TOI2C_GPIO_SUB_CMD_DIR, 
                                                 RS232TOI2C_GPIO_MASK_ALL, RS232TOI2C_GPIO_MASK_ALL );
    
    // set all GPIO to LOW logic state
    error_flag |= rs232toi2c_set_gpio_out ( ctx, RS232TOI2C_GPIO_MASK_ALL, RS232TOI2C_GPIO_MASK_NONE );
    
    // set UART baud rate
    error_flag |= rs232toi2c_set_baud_rate ( ctx, 9600 );
    
    // set UART config
    error_flag |= rs232toi2c_write_uart_config ( ctx, RS232TOI2C_UART_SUB_CMD_DATABITS, RS232TOI2C_UART_DATABITS_8 );
    error_flag |= rs232toi2c_write_uart_config ( ctx, RS232TOI2C_UART_SUB_CMD_PARITY, RS232TOI2C_UART_PARITY_NONE );
    error_flag |= rs232toi2c_write_uart_config ( ctx, RS232TOI2C_UART_SUB_CMD_STOP_BITS, RS232TOI2C_UART_STOP_BIT_1 );
    error_flag |= rs232toi2c_write_uart_config ( ctx, RS232TOI2C_UART_SUB_CMD_FLOW_CONTROL, RS232TOI2C_UART_FLOW_CONTROL_NONE );
    
    // enable UART RX and TX
    error_flag |= rs232toi2c_enable_uart ( ctx, RS232TOI2C_UART_ENABLE_RX_TX );
    
    // enable RX interrupt
    error_flag |= rs232toi2c_enable_interrupts ( ctx, RS232TOI2C_INTERRUPT_RX_DATA );
    
    return error_flag;
}

err_t rs232toi2c_write_command ( rs232toi2c_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t data_len )
{
    ctx->slave_address = RS232TOI2C_SET_DEV_ADDR_A2_GND | RS232TOI2C_CMD_ACCESS_BIT;
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = cmd;
    for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    Delay_1ms ( );
    return i2c_master_write( &ctx->i2c, data_buf, data_len + 1 );
}

err_t rs232toi2c_read_command ( rs232toi2c_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t data_len )
{
    ctx->slave_address = RS232TOI2C_SET_DEV_ADDR_A2_GND | RS232TOI2C_CMD_ACCESS_BIT;
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    Delay_1ms ( );
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, data_len );
}

err_t rs232toi2c_write_eeprom ( rs232toi2c_t *ctx, uint16_t address, uint8_t *data_in, uint8_t data_len )
{
    if ( ( ( address + data_len ) > RS232TOI2C_EEPROM_SIZE ) || ( data_len > RS232TOI2C_EEPROM_PAGE_SIZE ) )
    {
        return I2C_MASTER_ERROR;
    }
    ctx->slave_address = RS232TOI2C_SET_DEV_ADDR_A2_GND;
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ RS232TOI2C_EEPROM_PAGE_SIZE + 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    Delay_1ms ( );
    return i2c_master_write( &ctx->i2c, data_buf, data_len + 2 );
}

err_t rs232toi2c_read_eeprom ( rs232toi2c_t *ctx, uint16_t address, uint8_t *data_out, uint8_t data_len )
{
    if ( ( address + data_len ) > RS232TOI2C_EEPROM_SIZE )
    {
        return I2C_MASTER_ERROR;
    }
    ctx->slave_address = RS232TOI2C_SET_DEV_ADDR_A2_GND;
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    Delay_1ms ( );
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, data_len );
}

err_t rs232toi2c_erase_eeprom_page ( rs232toi2c_t *ctx, uint8_t page_num )
{
    if ( page_num >= RS232TOI2C_EEPROM_PAGE_NUM )
    {
        return I2C_MASTER_ERROR;
    }
    return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_ERASE_EEPROM_PAGE, &page_num, 1 );
}

err_t rs232toi2c_set_gpio_out ( rs232toi2c_t *ctx, uint8_t mask, uint8_t state )
{
    if ( ( mask > RS232TOI2C_GPIO_MASK_ALL ) || ( state > RS232TOI2C_GPIO_MASK_ALL ) )
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ 2 ] = { mask, state };
    return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_SET_GPIO_OUT, data_buf, 2 );
}

err_t rs232toi2c_get_gpio_in ( rs232toi2c_t *ctx, uint8_t *state )
{
    return rs232toi2c_read_command( ctx, RS232TOI2C_CMD_GET_GPIO_IN, state, 1 );
}

err_t rs232toi2c_write_gpio_config ( rs232toi2c_t *ctx, uint8_t sub_cmd, uint8_t mask, uint8_t config )
{
    if ( ( ( sub_cmd > RS232TOI2C_GPIO_SUB_CMD_INTERRUPT ) && 
           ( RS232TOI2C_GPIO_SUB_CMD_RESET_DEFAULT != sub_cmd ) ) || 
         ( sub_cmd < RS232TOI2C_GPIO_SUB_CMD_DIR ) )
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ 3 ] = { sub_cmd, mask, config };
    if ( RS232TOI2C_GPIO_SUB_CMD_RESET_DEFAULT != sub_cmd )
    {
        return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_WRITE_GPIO_CFG, data_buf, 3 );
    }
    else
    {
        return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_WRITE_GPIO_CFG, data_buf, 1 );
    }
}

err_t rs232toi2c_read_gpio_config ( rs232toi2c_t *ctx, uint8_t sub_cmd, uint8_t *config )
{
    if ( ( sub_cmd > RS232TOI2C_GPIO_SUB_CMD_INTERRUPT ) || 
         ( sub_cmd < RS232TOI2C_GPIO_SUB_CMD_DIR ) )
    {
        return I2C_MASTER_ERROR;
    }
    ctx->slave_address = RS232TOI2C_SET_DEV_ADDR_A2_GND | RS232TOI2C_CMD_ACCESS_BIT;
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = RS232TOI2C_CMD_READ_GPIO_CFG;
    data_buf[ 1 ] = sub_cmd;
    Delay_1ms ( );
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, config, 1 );
}

err_t rs232toi2c_write_uart_config ( rs232toi2c_t *ctx, uint8_t sub_cmd, uint8_t config )
{
    uint8_t data_buf[ 2 ] = { sub_cmd, config };
    if ( RS232TOI2C_GPIO_SUB_CMD_RESET_DEFAULT != sub_cmd )
    {
        return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_WRITE_UART_CFG, data_buf, 2 );
    }
    else
    {
        return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_WRITE_UART_CFG, data_buf, 1 );
    }
}

err_t rs232toi2c_read_uart_config ( rs232toi2c_t *ctx, uint8_t *config )
{
    return rs232toi2c_read_command( ctx, RS232TOI2C_CMD_READ_UART_CFG, config, 2 );
}

err_t rs232toi2c_enable_uart ( rs232toi2c_t *ctx, uint8_t state )
{
    return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_ENABLE_UART, &state, 1 );
}

err_t rs232toi2c_set_baud_rate ( rs232toi2c_t *ctx, uint32_t baud_rate )
{
    baud_rate /= 100;
    if ( baud_rate > 0xFFFF )
    {
        return I2C_MASTER_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( baud_rate >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( baud_rate & 0xFF );
    return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_WRITE_BAUD_RATE, data_buf, 2 );
}

err_t rs232toi2c_get_baud_rate ( rs232toi2c_t *ctx, uint32_t *baud_rate )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( RS232TOI2C_OK == rs232toi2c_read_command( ctx, RS232TOI2C_CMD_READ_BAUD_RATE, data_buf, 2 ) )
    {
        *baud_rate = data_buf[ 0 ];
        *baud_rate <<= 8;
        *baud_rate |= data_buf[ 1 ];
        *baud_rate *= 100;
        return RS232TOI2C_OK;
    }
    return I2C_MASTER_ERROR;
}

err_t rs232toi2c_enable_interrupts ( rs232toi2c_t *ctx, uint8_t int_mask )
{
    return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_ENABLE_INT, &int_mask, 1 );
}

err_t rs232toi2c_get_interrupt_status ( rs232toi2c_t *ctx, uint8_t *int_status )
{
    uint8_t clear_status = 0;
    err_t error_flag = rs232toi2c_read_command( ctx, RS232TOI2C_CMD_INT_STATUS, int_status, 1 );
    error_flag |= rs232toi2c_write_command( ctx, RS232TOI2C_CMD_INT_STATUS, &clear_status, 1 );
    return error_flag;
}

err_t rs232toi2c_get_uart_status ( rs232toi2c_t *ctx, uint8_t *uart_status )
{
    uint8_t clear_status = 0;
    err_t error_flag = rs232toi2c_read_command( ctx, RS232TOI2C_CMD_READ_UART_STATUS, uart_status, 1 );
    error_flag |= rs232toi2c_write_command( ctx, RS232TOI2C_CMD_READ_UART_STATUS, &clear_status, 1 );
    return error_flag;
}

err_t rs232toi2c_get_gpio_status ( rs232toi2c_t *ctx, uint8_t *gpio_status )
{
    uint8_t clear_status = 0;
    err_t error_flag = rs232toi2c_read_command( ctx, RS232TOI2C_CMD_READ_GPIO_INT_STATUS, gpio_status, 1 );
    error_flag |= rs232toi2c_write_command( ctx, RS232TOI2C_CMD_READ_GPIO_INT_STATUS, &clear_status, 1 );
    return error_flag;
}

err_t rs232toi2c_write_tx_fifo ( rs232toi2c_t *ctx, uint8_t *data_in, uint8_t data_len )
{
    return rs232toi2c_write_command( ctx, RS232TOI2C_CMD_WRITE_TX_FIFO, data_in, data_len );
}

err_t rs232toi2c_read_rx_fifo ( rs232toi2c_t *ctx, uint8_t *data_out, uint8_t *data_len )
{
    uint8_t int_status = 0;
    *data_len = 0;
    err_t error_flag = rs232toi2c_get_interrupt_status ( ctx, &int_status );
    while ( RS232TOI2C_INTERRUPT_RX_DATA & int_status ) 
    {
        error_flag |= rs232toi2c_read_command( ctx, RS232TOI2C_CMD_READ_RX_FIFO, &data_out[ *data_len ], 1 );
        error_flag |= rs232toi2c_get_interrupt_status ( ctx, &int_status );
        *data_len += 1;
        if ( 255 == *data_len )
        {
            return error_flag;
        }
    }
    if ( 0 == *data_len )
    {
        return RS232TOI2C_ERROR;
    }
    return error_flag;
}

err_t rs232toi2c_read_system_version ( rs232toi2c_t *ctx, uint32_t *system_version )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( RS232TOI2C_OK == rs232toi2c_read_command ( ctx, RS232TOI2C_CMD_READ_SYSTEM_VERSION, data_buf, 3 ) )
    {
        *system_version = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        return RS232TOI2C_OK;
    }
    return RS232TOI2C_ERROR;
}

void rs232toi2c_set_rst_pin ( rs232toi2c_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void rs232toi2c_set_wp_pin ( rs232toi2c_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void rs232toi2c_reset_device ( rs232toi2c_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t rs232toi2c_get_int_pin ( rs232toi2c_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

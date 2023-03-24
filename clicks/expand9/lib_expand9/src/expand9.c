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
 * @file expand9.c
 * @brief Expand 9 Click Driver.
 */

#include "expand9.h"

static uint8_t expand9_reg_i_on[ 16 ] = 
{
    EXPAND9_REG_I_ON_0,
    EXPAND9_REG_I_ON_1,
    EXPAND9_REG_I_ON_2,
    EXPAND9_REG_I_ON_3,
    EXPAND9_REG_I_ON_4,
    EXPAND9_REG_I_ON_5,
    EXPAND9_REG_I_ON_6,
    EXPAND9_REG_I_ON_7,
    EXPAND9_REG_I_ON_8,
    EXPAND9_REG_I_ON_9,
    EXPAND9_REG_I_ON_10,
    EXPAND9_REG_I_ON_11,
    EXPAND9_REG_I_ON_12,
    EXPAND9_REG_I_ON_13,
    EXPAND9_REG_I_ON_14,
    EXPAND9_REG_I_ON_15
};

/**
 * @brief Expand 9 Reset delay function.
 * @details This function performs a delay of 1 millisecond.
 * @return Nothing.
 * @note None.
 */
static void dev_reset_delay ( void );

void expand9_cfg_setup ( expand9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->add   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND9_SET_DEV_ADDR_GND;
}

err_t expand9_init ( expand9_t *ctx, expand9_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    
    digital_out_init( &ctx->add, cfg->add );
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
    digital_out_low( &ctx->add );
    dev_reset_delay( );

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

    return I2C_MASTER_SUCCESS;
}

err_t expand9_default_cfg ( expand9_t *ctx ) 
{
    err_t err_flag = expand9_soft_reset( ctx );
    dev_reset_delay( );
    
    err_flag |= expand9_set_slave_address ( ctx, EXPAND9_SET_DEV_ADDR_GND );
    dev_reset_delay( );
    
    return err_flag;
}

err_t expand9_set_slave_address ( expand9_t *ctx, uint8_t slave_addr ) 
{
    err_t err_flag;
    
    if ( slave_addr == EXPAND9_SET_DEV_ADDR_GND )
    {
        digital_out_low( &ctx->add );
        dev_reset_delay( );
        
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EXPAND9_SET_DEV_ADDR_GND );    
    }
    else if ( slave_addr == EXPAND9_SET_DEV_ADDR_VCC )
    {
        digital_out_high( &ctx->add );
        dev_reset_delay( );
        
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EXPAND9_SET_DEV_ADDR_VCC ); 
    }
    else
    {
        return EXPAND9_ERROR;    
    }
    
    return err_flag;
}

err_t expand9_generic_write ( expand9_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t expand9_generic_read ( expand9_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t expand9_soft_reset ( expand9_t *ctx ) 
{
    uint8_t tx_buf;
    
    tx_buf = 0x12;
    err_t err_flag = expand9_generic_write( ctx, EXPAND9_REG_RESET, &tx_buf, 1 );
    
    tx_buf = 0x34;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_RESET, &tx_buf, 1 );
    
    return err_flag;
}

err_t expand9_set_ch_direction ( expand9_t *ctx, uint8_t ch_pos, expand9_direction_value_t direction ) 
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t sel_data;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_DIR_B, rx_buf, 2 );
    
    sel_data = rx_buf[ 0 ];
    sel_data <<= 8;
    sel_data |= rx_buf[ 1 ];
    
    if ( direction == DIRECTION_INPUT )
    {
        sel_data |= ( 0x0001 << ch_pos );
    }
    else
    {
        sel_data &= ~( 0x0001 << ch_pos );    
    }
    
    tx_buf[ 0 ] = ( uint8_t ) ( sel_data >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   sel_data;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_DIR_B, tx_buf, 2 );
    
    return err_flag;
}

err_t expand9_set_all_ch_output ( expand9_t *ctx ) 
{
    uint8_t tx_buf[ 2 ] = { 0x00, 0x00 };
    
    return expand9_generic_write( ctx, EXPAND9_REG_DIR_B, tx_buf, 2 );
}

err_t expand9_set_all_ch_input ( expand9_t *ctx ) 
{
    uint8_t tx_buf[ 2 ] = { 0xFF, 0xFF };
    
    return expand9_generic_write( ctx, EXPAND9_REG_DIR_B, tx_buf, 2 );
}

err_t expand9_set_ch_output_state ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t ch_state ) 
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t sel_data;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_set_ch_direction( ctx, ch_pos, DIRECTION_OUTPUT );
    
    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_DATA_B, rx_buf, 2 );
    
    sel_data = rx_buf[ 0 ];
    sel_data <<= 8;
    sel_data |= rx_buf[ 1 ];
    
    if ( ch_state == CH_OUTPUT_ON ) 
    {
        sel_data |= ( 0x0001 << ch_pos );
    }
    else
    {
        sel_data &= ~( 0x0001 << ch_pos );    
    }
    
    tx_buf[ 0 ] = ( uint8_t ) ( sel_data >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   sel_data;
    err_flag |= expand9_generic_write( ctx, 0x10, tx_buf, 2 );
    
    return err_flag;
}

err_t expand9_get_ch_output_state ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t *ch_state ) 
{
    uint8_t rx_buf[ 2 ];
    uint16_t sel_data;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_set_ch_direction( ctx, ch_pos, DIRECTION_INPUT );
    
    err_flag |= expand9_generic_read( ctx, 0x10, rx_buf, 2 );
    
    sel_data = rx_buf[ 0 ];
    sel_data <<= 8;
    sel_data |= rx_buf[ 1 ];
    
    if ( sel_data & ( 0x0001 << ch_pos ) ) 
    {
        *ch_state = CH_OUTPUT_ON;    
    }
    else
    {
        *ch_state = CH_OUTPUT_OFF;
    }
    
    return err_flag;
}

err_t expand9_write_ch (  expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t ch_state )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t temp_dir;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_DIR_B, rx_buf, 2 );
    
    temp_dir = rx_buf[ 0 ];
    temp_dir <<= 8;
    temp_dir |= rx_buf[ 1 ];

    if ( ( 0xFFFF ^ temp_dir ) & ( 0x0001 << ch_pos ) )	
    {
        uint16_t temp_data;
        
        err_flag |= expand9_generic_read( ctx, EXPAND9_REG_DATA_B, rx_buf, 2 );
        
        temp_data = rx_buf[ 0 ];
        temp_data <<= 8;
        temp_data |= rx_buf[ 1 ];
        
        if ( ch_state )
        {
            temp_data |=  ( 0x0001 << ch_pos );
        }
        else
        {
            temp_data &= ~( 0x0001 << ch_pos );
        }
        
        tx_buf[ 0 ] = ( uint8_t ) ( temp_data >> 8 );
        tx_buf[ 1 ] = ( uint8_t )   temp_data;
        err_flag |= expand9_generic_write( ctx, EXPAND9_REG_DATA_B, tx_buf, 2 );
    }
    else
    {
        uint16_t temp_pull_up;
        uint16_t temp_pull_down;
        
        err_flag |= expand9_generic_read( ctx, EXPAND9_REG_PULL_UP_B, rx_buf, 2 );
        
        temp_pull_up = rx_buf[ 0 ];
        temp_pull_up <<= 8;
        temp_pull_up |= rx_buf[ 1 ];
        
        err_flag |= expand9_generic_read( ctx, EXPAND9_REG_PULL_DOWN_B, rx_buf, 2 );
        
        temp_pull_down = rx_buf[ 0 ];
        temp_pull_down <<= 8;
        temp_pull_down |= rx_buf[ 1 ];

        if ( ch_state == CH_OUTPUT_ON )
        {
            temp_pull_up |= ( 0x0001 << ch_pos );
            tx_buf[ 0 ] = ( uint8_t ) ( temp_pull_up >> 8 );
            tx_buf[ 1 ] = ( uint8_t )   temp_pull_up;
            err_flag |= expand9_generic_write( ctx, EXPAND9_REG_PULL_UP_B, tx_buf, 2 );
            
            temp_pull_down &= ~( 0x0001 << ch_pos );
            tx_buf[ 0 ] = ( uint8_t ) ( temp_pull_down >> 8 );
            tx_buf[ 1 ] = ( uint8_t )   temp_pull_down;
            err_flag |= expand9_generic_write( ctx, EXPAND9_REG_PULL_DOWN_B, tx_buf, 2 );
            
        }
        else
        {
            temp_pull_up &= ~( 0x0001 << ch_pos );
            tx_buf[ 0 ] = ( uint8_t ) ( temp_pull_up >> 8 );
            tx_buf[ 1 ] = ( uint8_t )   temp_pull_up;
            err_flag |= expand9_generic_write( ctx, EXPAND9_REG_PULL_UP_B, tx_buf, 2 );
            
            temp_pull_down |= ( 0x0001 << ch_pos );
            tx_buf[ 0 ] = ( uint8_t ) ( temp_pull_down >> 8 );
            tx_buf[ 1 ] = ( uint8_t )   temp_pull_down;
            err_flag |= expand9_generic_write( ctx, EXPAND9_REG_PULL_DOWN_B, tx_buf, 2 );
        }
    }
    
    return err_flag;
}

err_t expand9_read_ch ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t *ch_state )
{
    uint8_t rx_buf[ 2 ];
    uint16_t temp;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_DIR_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    if ( temp & ( 0x0001 << ch_pos ) )
    {
        err_flag |= expand9_generic_read( ctx, EXPAND9_REG_DATA_B, rx_buf, 2 );
        temp = rx_buf[ 0 ];
        temp <<= 8;
        temp |= rx_buf[ 1 ];
        if ( temp & ( 1 << ch_pos ) )
        {
            *ch_state = CH_OUTPUT_ON;
        }
        else
        {
            *ch_state = CH_OUTPUT_OFF;    
        }
    }
    
    return err_flag;
}

err_t expand9_led_driver_config ( expand9_t *ctx, uint8_t ch_pos, uint8_t freq_div, uint8_t lin_log )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t temp;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }

    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_INPUT_DISABLE_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    temp |= ( 0x0001 << ch_pos );
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_INPUT_DISABLE_B, tx_buf, 2 );

    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_PULL_UP_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    temp &= ~( 0x0001 << ch_pos );
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_PULL_UP_B, tx_buf, 2 );

    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_DIR_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    temp &= ~( 0x0001 << ch_pos );
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_DIR_B, tx_buf, 2 );    
    
    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_CLOCK, rx_buf, 1 );
    
    tx_buf[ 0 ] = rx_buf [ 0 ];
    tx_buf[ 0 ] |= ( 1 << 6 );
    tx_buf[ 0 ] &= ~( 1 <<5 );
    rx_buf[ 0 ] |= freq_div;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_CLOCK, tx_buf, 1 );  
    

    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_MISC, rx_buf, 1 );
    if ( lin_log )
    {
        rx_buf[ 0 ] |= 0x80;
        rx_buf[ 0 ] |= 0x08;
    }
    else
    {
        rx_buf[ 0 ] &= ~0x80;
        rx_buf[ 0 ] &= ~0x08;
    }

    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_MISC, tx_buf, 1 ); 

    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_LED_DRIVER_ENABLE_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    temp |= ( 0x0001 << ch_pos );
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_LED_DRIVER_ENABLE_B, tx_buf, 2 );

    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_LED_DRIVER_ENABLE_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    temp &= ~( 0x0001 << ch_pos );
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_DATA_B, tx_buf, 2 );

    return err_flag;
}

err_t expand9_set_intensity ( expand9_t *ctx, uint8_t ch_pos, uint8_t intensity )
{    
    if ( ch_pos > 7 )
    {
        return EXPAND9_ERROR;
    }
    
    return expand9_generic_write( ctx, expand9_reg_i_on[ ch_pos ], &intensity, 1 );
}

err_t expand9_sync ( expand9_t *ctx )
{
    uint8_t rx_tx_buf[ 1 ];
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_MISC, rx_tx_buf, 1 );
    
    if ( !( rx_tx_buf[ 0 ] & 0x04 ) )
    {
        rx_tx_buf[ 0 ] |= 0x04;
        err_flag |= expand9_generic_write( ctx, EXPAND9_REG_MISC, rx_tx_buf, 1 );
    }
    
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
    
    rx_tx_buf[ 0 ] &= ~0x04;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_MISC, rx_tx_buf, 1 );

    return err_flag;
}

err_t expand9_debounce_config ( expand9_t *ctx, uint8_t config_val )
{
    uint8_t rx_tx_buf[ 1 ];
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_MISC, rx_tx_buf, 1 );
    
    if ( ( rx_tx_buf[ 0 ] & 0x70 ) == 0 )
    {
        rx_tx_buf[ 0 ] |= 0x10;
        err_flag |= expand9_generic_write( ctx, EXPAND9_REG_MISC, rx_tx_buf, 1 );
    }
    
    err_flag |= expand9_generic_read( ctx, EXPAND9_REG_CLOCK, rx_tx_buf, 1 );
    
    if ( ( rx_tx_buf[ 0 ] & 0x60 ) == 0 )
    {
        rx_tx_buf[ 0 ] |= 0x40;
        err_flag |= expand9_generic_write( ctx, EXPAND9_REG_CLOCK, rx_tx_buf, 1 );
    }
    
    config_val &= 0x07;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_DEBOUNCE_CONFIG, &config_val, 1 );
    
    return err_flag;
}

err_t expand9_enable_ch_interrupt ( expand9_t *ctx, uint8_t ch_pos, uint8_t rise_fall )
{
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint8_t sensitivity;
    uint8_t pin_mask;
    uint8_t s_reg;
    uint16_t temp;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_INTERRUPT_MASK_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    temp &= ~( 0x0001 << ch_pos );
    
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, EXPAND9_REG_INTERRUPT_MASK_B, tx_buf, 1 );

    switch ( rise_fall )
    {
        case EXPAND9_CHANGE:
        {
            sensitivity = 0x03;
            break;   
        }
        case EXPAND9_FALLING:
        {
            sensitivity = 0x02;
            break;   
        }
        case EXPAND9_RISING:
        {
            sensitivity = 0x01;
            break;   
        }
        default: {
            return EXPAND9_ERROR;
        }
    }
        
    if ( ch_pos >=  8 )
    {
        s_reg = EXPAND9_REG_SENSE_HIGH_B;
    }
    else
    {
        s_reg = EXPAND9_REG_SENSE_HIGH_A;
    }
    
    err_flag |= expand9_generic_read( ctx, s_reg, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    temp &= ~( 0x03 << pin_mask );
    temp |= ( sensitivity << pin_mask );
    tx_buf[ 0 ] = ( uint8_t ) ( temp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   temp;
    err_flag |= expand9_generic_write( ctx, s_reg, tx_buf, 1 );

    return err_flag;
}

err_t expand9_clear_interrupt ( expand9_t *ctx )
{
    uint8_t tx_buf[ 2 ] = { 0xFF, 0xFF };

    return expand9_generic_read( ctx, EXPAND9_REG_INTERRUPT_SOURCE_B, tx_buf, 2 );
}

err_t expand9_check_ch_interrupt ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t *int_state )
{
    uint8_t rx_buf[ 2 ];
    uint16_t temp;
    
    if ( ch_pos > 16 )
    {
        return EXPAND9_ERROR;
    }
    
    err_t err_flag = expand9_generic_read( ctx, EXPAND9_REG_INTERRUPT_SOURCE_B, rx_buf, 2 );
    
    temp = rx_buf[ 0 ];
    temp <<= 8;
    temp |= rx_buf[ 1 ];
    
    if ( temp & ( 0x0001 << ch_pos ) )
    {
        *int_state = CH_OUTPUT_ON;    
    }
    else
    {
        *int_state = CH_OUTPUT_OFF;
    }
    
    err_flag |= expand9_clear_interrupt( ctx );
    dev_reset_delay( );

    return err_flag;
}

uint8_t expand9_check_interrupt_pin ( expand9_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static void dev_reset_delay ( void )
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END

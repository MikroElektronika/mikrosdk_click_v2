/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "capwheel.h"

void capwheel_cfg_setup ( capwheel_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg-> clr = HAL_PIN_NC;
    cfg-> rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CAPWHEEL_DEVICE_ADDR;
}

CAPWHEEL_RETVAL capwheel_init ( capwheel_t *ctx, capwheel_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CAPWHEEL_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
//     i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx-> clr, cfg-> clr );

    // Input pins

    digital_in_init( &ctx-> rdy, cfg-> rdy );
    
    // Example: Sets pin [high, low] 

     digital_out_high( &ctx-> clr );


    return CAPWHEEL_OK;

}

void capwheel_generic_write ( capwheel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void capwheel_generic_read ( capwheel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t capwheel_write_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes )
{
    uint8_t buff_data[ 19 ];
    uint8_t cnt;

    if ((register_address > 0x0F) || ((register_address < 0x06) && (register_address != 0x01)))
    {
        return CAPWHEEL_ADDR_ERROR;
    }
    if (n_bytes > 18)
    {
        return CAPWHEEL_NBYTES_ERROR;
    }

    buff_data[ 0 ] = register_address;
    for (cnt = 1; cnt < n_bytes; cnt++)
    {
        buff_data[ cnt ] = data_in[ cnt - 1 ];
    }

//     capwheel_generic_write( ctx, register_address, buff_data, n_bytes );
    i2c_master_write( &ctx->i2c, buff_data, n_bytes + 1 );  

    Delay_10ms(  );
    Delay_10ms(  );
    Delay_5ms( );
    return CAPWHEEL_OK;
}

uint8_t capwheel_read_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t reg_addr;

    if ( register_address > 0x0F )
    {
        return CAPWHEEL_ADDR_ERROR;
    }
    if ( n_bytes > 18 )
    {
        return CAPWHEEL_NBYTES_ERROR;
    }

    reg_addr = register_address;
    
//     capwheel_generic_read( ctx, reg_addr, data_out, n_bytes );
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_out, n_bytes );
    
    Delay_10ms();
    Delay_10ms();
    Delay_5ms();

    return CAPWHEEL_OK;
}

uint8_t capwheel_check_data_ready ( capwheel_t *ctx )
{
    if ( digital_in_read(&ctx-> rdy) )
    {
        return CAPWHEEL_DATA_NOT_READY;
    }
    else
    {
        return CAPWHEEL_DATA_READY;
    }
}

uint8_t capwheel_enable_chann ( capwheel_t *ctx, uint16_t sel_chann )
{
    uint16_t temp = 1;
    uint8_t chann_data[ 2 ] = { 0 };
    uint8_t cnt;

    if ( sel_chann & 0xFC00 )
    {
        return CAPWHEEL_CH_SEL_ERROR;
    }

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        if ( cnt < 8 )
        {
            if ( sel_chann & temp )
            {
                chann_data[ 0 ] |= temp;
            }
        }
        else
        {
            if ( sel_chann & temp )
            {
                chann_data[ 1 ] |= ( temp >> 8 );
            }
        }
        temp <<= 1;
    }

    capwheel_write_reg( ctx, CAPWHEEL_ACTIVE_CHANN_REG, chann_data, CAPWHEEL_ACT_CHANN_NBYTES );

    return CAPWHEEL_OK;
}

void capwheel_get_data ( capwheel_t *ctx, uint16_t *wheel_data )
{
    uint8_t touch_buff[ 4 ];
    uint16_t ret_val;

    capwheel_read_reg( ctx, CAPWHEEL_WHEEL_COORDNT_REG, touch_buff, CAPWHEEL_WHEEL_NBYTES );

    ret_val = touch_buff[ 1 ];
    ret_val <<= 8;
    ret_val |= touch_buff[ 0 ];

    *wheel_data = ret_val;
}

void capwheel_set_output ( capwheel_t *ctx, uint16_t input_data, uint8_t output_mode )
{
    uint8_t output_data[ 8 ];
    uint16_t temp_var;
    uint8_t count;

    if ( output_mode == CAPWHEEL_LED_BRIGHTNESS_INTENSITY )
    {
        temp_var = input_data / 65;

        for ( count = 0; count < 8; count++ )
        {
            output_data[ count ] = temp_var;
            output_data[ count ] |= CAPWHEEL_PWM_CONST;
        }
    }
    else
    {
        temp_var = input_data / 230;
        
        for ( count = 0; count < 8; count++ )
        {
            if ( count < temp_var )
            {
                output_data[ count ] = CAPWHEEL_PWM_CONST | CAPWHEEL_PWM_DUTY_100_PERCENTS;
            }
            else
            {
                output_data[ count ] = CAPWHEEL_PWM_CONST | CAPWHEEL_PWM_DUTY_0_PERCENTS;
            }
        }
    }

    capwheel_write_reg( ctx, CAPWHEEL_PWM_DUTY_REG, output_data, CAPWHEEL_PWM_DUTY_NBYTES );
}

void capwheel_set_threshold ( capwheel_t *ctx, uint8_t thresh_value )
{
    uint8_t thresh_data[ 10 ];
    uint8_t cnt;
    
    for (cnt = 0; cnt < 10; cnt++)
    {
        thresh_data[ cnt ] = thresh_value;
    }
    
    capwheel_write_reg( ctx, CAPWHEEL_THRESH_REG, thresh_data, CAPWHEEL_THRESH_NBYTES );
}

void capwheel_reset ( capwheel_t *ctx )
{
    digital_out_low( &ctx-> clr);
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx-> clr);
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

// ------------------------------------------------------------------------- END


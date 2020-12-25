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

#include "capslider2.h"


void capslider2_cfg_setup ( capslider2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
;
    cfg-> clr = HAL_PIN_NC;
    cfg-> rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CAPSLDR2_DEVICE_ADDR;
}

CAPSLIDER2_RETVAL capslider2_init ( capslider2_t *ctx, capslider2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CAPSLIDER2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx-> clr, cfg-> clr );

    // Input pins

    digital_in_init( &ctx-> rdy, cfg-> rdy );
    
    // Example: Sets pin [high, low] 

     digital_out_high( &ctx-> clr );
    
    // Example: Get pin state 


    return CAPSLIDER2_OK;

}

void capslider2_generic_write ( capslider2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void capslider2_generic_read ( capslider2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t capsldr2_write_reg ( capslider2_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes )
{
    uint8_t buff_data[ 19 ];
    uint8_t cnt;

    if ((register_address > 0x0F) || ((register_address < 0x06) && (register_address != 0x01)))
    {
        return CAPSLDR2_INVALID_ADDR;
    }
    if (n_bytes > 18)
    {
        return CAPSLDR2_INVALID_NBYTES;
    }
    
    for (cnt = 0; cnt < n_bytes; cnt++)
    {
        buff_data[ cnt ] = data_in[ cnt ];
    }

    capslider2_generic_write( ctx, register_address, buff_data, n_bytes );
    Delay_10ms(  );
    Delay_10ms(  );
    Delay_10ms(  );

    return CAPSLDR2_OK;
}

uint8_t capsldr2_read_reg ( capslider2_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t reg_addr;

    if (register_address > 0x0F)
    {
        return CAPSLDR2_INVALID_ADDR;
    }
    if (n_bytes > 18)
    {
        return CAPSLDR2_INVALID_NBYTES;
    }

    reg_addr = register_address;
    
    capslider2_generic_read( ctx, reg_addr, data_out, n_bytes );
    Delay_10ms(  );
    Delay_10ms(  );
    Delay_10ms(  );

    return CAPSLDR2_OK;
}

uint8_t capsldr2_check_data_ready ( capslider2_t *ctx )
{
    if ( digital_in_read( &ctx-> rdy) )
    {
        return CAPSLDR2_DATA_NOT_READY;
    }
    else
    {
        return CAPSLDR2_DATA_READY;
    }
}

uint8_t capsldr2_enable_chann ( capslider2_t *ctx, uint16_t sel_chann )
{
    uint16_t temp = 1;
    uint8_t chann_data[ 2 ] = { 0 };
    uint8_t cnt;

    if (sel_chann & 0xFC00)
    {
        return CAPSLDR2_INVALID_CHANNEL;
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
            if (sel_chann & temp)
            {
                chann_data[ 1 ] |= (temp >> 8);
            }
        }
        temp <<= 1;
    }

    capsldr2_write_reg( ctx, CAPSLDR2_ACTIVE_CHANN_REG, chann_data, CAPSLDR2_ACT_CHANN_NBYTES );

    return CAPSLDR2_OK;
}

void capsldr2_get_data( capslider2_t *ctx, uint16_t *wheel_data1, uint16_t *wheel_data2 )
{
    uint8_t touch_buff[ 4 ];
    uint16_t ret_val;

    capsldr2_read_reg( ctx, CAPSLDR2_WHEEL_COORDNT_REG, touch_buff, CAPSLDR2_WHEEL_NBYTES );

    ret_val = touch_buff[ 1 ];
    ret_val <<= 8;
    ret_val |= touch_buff[ 0 ];

    *wheel_data1 = ret_val;
    
    ret_val = touch_buff[ 3 ];
    ret_val <<= 8;
    ret_val |= touch_buff[ 2 ];

    *wheel_data2 = ret_val;
}

void capsldr2_set_output ( capslider2_t *ctx, uint8_t input_data, uint8_t output_mode )
{
    uint8_t output_data[ 8 ];
    uint8_t count;
    static uint8_t intensity = CAPSLDR2_PWM_DUTY_100_PERCENTS;
    static uint8_t n_leds = 0;

    if (output_mode == CAPSLDR2_LED_INTENSITY)
    {
        intensity = input_data * 3.875;
        
        if (intensity > CAPSLDR2_PWM_DUTY_100_PERCENTS)
        {
            intensity = CAPSLDR2_PWM_DUTY_100_PERCENTS;
        }
    }
    else
    {
        n_leds = input_data;
    }
    
    for (count = 0; count < 8; count++)
    {
        if (count < n_leds)
        {
            output_data[ count ] = intensity;
        }
        else
        {
            output_data[ count ] = CAPSLDR2_PWM_DUTY_0_PERCENTS;
        }
        output_data[ count ] |= CAPSLDR2_PWM_CONST;
    }

    capsldr2_write_reg( ctx, CAPSLDR2_PWM_DUTY_REG, output_data, CAPSLDR2_PWM_DUTY_NBYTES );
}

void capsldr2_set_threshold ( capslider2_t *ctx, uint8_t thresh_value )
{
    uint8_t thresh_data[ 10 ];
    uint8_t cnt;

    for (cnt = 0; cnt < 10; cnt++)
    {
        thresh_data[ cnt ] = thresh_value;
    }

    capsldr2_write_reg( ctx, CAPSLDR2_THRESH_REG, thresh_data, CAPSLDR2_THRESH_NBYTES );
}

void capsldr2_reset ( capslider2_t *ctx )
{
    digital_out_low( &ctx-> clr );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx-> clr );
    Delay_1sec( );
}

void capsldr2_config ( capslider2_t *ctx )
{
    uint8_t cnfg[ 10 ] = { 69, 106, 96, 102, 102, 113, 101, 40, 44, 41 };
    uint8_t mult[ 10 ] = { 0xF3, 0x95, 0x93, 0x97, 0x95, 0x92, 0x95, 0x01, 0x01, 0x01 };
    
    capsldr2_write_reg( ctx, CAPSLDR2_COMPENS_REG, cnfg, CAPSLDR2_COMPENS_NBYTES );
    capsldr2_write_reg( ctx, CAPSLDR2_MULTIPLIERS_REG, mult, CAPSLDR2_MULTIPL_NBYTES );
}

// ------------------------------------------------------------------------- END


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

#include "irsense2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irsense2_cfg_setup ( irsense2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x64;
    cfg->data_flag_cfg = 0;
    cfg->prev_ir_data_cfg = 0;
    cfg->prev_ir_data_cfg2 = 0;
}

IRSENSE2_RETVAL irsense2_init ( irsense2_t *ctx, irsense2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return IRSENSE2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return IRSENSE2_OK;

}

void irsense2_default_cfg ( irsense2_t *ctx )
{
    uint8_t w_temp;

    w_temp = CNTL3_RESET_MODE;
    irsense2_generic_write( ctx, CNTL3_SOFT_RESET, &w_temp, 1 );

    w_temp = INTEN_RST | INTEN_MODE_MASK_DATARDY_INT_VALID;
    irsense2_generic_write( ctx, INTEN_INTERRUPT_FACTOR_SETTING, &w_temp, 1 );

    w_temp = CNTL1_RST | CNTL1_IR_MODE_MASK_FC_0_45HZ | CNTL1_TMP_MODE_MASK_FC_0_45HZ;
    irsense2_generic_write( ctx, CNTL1_CUT_OFF_FREQ_SETTING, &w_temp, 1 );

    w_temp = CNTL2_RST | CNTL2_CONTINUOUS_MODE;
    irsense2_generic_write( ctx, CNTL2_OPERATING_MODE_SETTING, &w_temp, 1 );
}

void irsense2_generic_write ( irsense2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void irsense2_generic_read ( irsense2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void irsense2_data_read ( irsense2_t *ctx, float *ir_data, float *temp_data )
{
    uint8_t read_data;
    uint8_t read_wrd[ 2 ];
    int16_t helper;

    irsense2_generic_read( ctx, STATUS_1_ST1, &read_data, 1 );
    
    while ( read_data.B0 == ST1_RST );

    irsense2_get_int( ctx );

    helper = irsense2_get_ir_data ( ctx );

    *ir_data = ( float )helper * 0.4578;

    helper = irsense2_get_temperature_data ( ctx );

    *temp_data = 0.0019837 * ( float )helper + 25;

    irsense2_generic_read( ctx, STATUS_2_ST2, &read_data, 1 );
}

int16_t irsense2_get_ir_data ( irsense2_t *ctx )
{
    uint8_t read_wrd[ 2 ];
    uint16_t helper;
    

    irsense2_generic_read( ctx, IR_SENSOR_LSB, read_wrd, 2 );
    
    helper = read_wrd[ 1 ];
    helper <<= 8;
    helper |= read_wrd[ 0 ];

    return helper;
}

int16_t irsense2_get_temperature_data ( irsense2_t *ctx )
{
    uint8_t read_wrd[ 2 ];
    uint16_t helper;

    irsense2_generic_read( ctx, TMP_SENSOR_LSB, read_wrd, 2 );

    helper = read_wrd[ 1 ];
    helper <<= 8;
    helper |= read_wrd[ 0 ];

    return helper;
}

void irsense2_get_int ( irsense2_t *ctx )
{
    uint8_t r_temp;
    irsense2_generic_read( ctx, INTCAUSE, &r_temp, 1 );
}

uint8_t irsense_human_detected ( irsense2_t *ctx, float ir_data )
{
    uint8_t pom_1;
    uint8_t pom_2;
    uint8_t pom_3; 
    uint8_t ret_flag;

    ret_flag = 0;

    if ( ( ctx->prev_ir_data != 0 ) && ( ctx->prev_ir_data2 != 0 ) )
    {
        if ( ( ( uint16_t )ctx->prev_ir_data2 - ( uint16_t )ctx->prev_ir_data ) > 0 )
        {
            pom_1 = ( uint16_t )ctx->prev_ir_data2 - ( uint16_t )ctx->prev_ir_data;
        }
        else
        {
            pom_1 = ( uint16_t )ctx->prev_ir_data - ( uint16_t )ctx->prev_ir_data2;
        }
        
        if ( ( pom_1 < 50 ) && ( ir_data > 0 ) )
        {
            pom_2 = ir_data - ( uint16_t )ctx->prev_ir_data2;
            pom_3 = ir_data - ( uint16_t )ctx->prev_ir_data;

            if ( ( pom_2 > 100 ) || ( pom_3 > 100 ) )
            {
                ret_flag = 1;
            }
        }
    }

    if ( ctx->data_flag == 0 )
    {
        ctx->prev_ir_data = ir_data;

        ctx->data_flag = 1;
    }
    else
    {
        ctx->prev_ir_data2 = ir_data;

        ctx->data_flag = 0;
    }

    return ret_flag;
}

void irsense2_get_int_pin( irsense2_t *ctx )
{
    digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END


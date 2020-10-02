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

#include "proximity.h"


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity_cfg_setup ( proximity_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY_SLAVE_ADDR;
}

PROXIMITY_RETVAL proximity_init ( proximity_t *ctx, proximity_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY_OK;

}

void proximity_write_byte ( proximity_t *ctx, uint8_t w_addr, uint8_t w_data )
{
    uint8_t buffer[ 2 ];
    buffer[ 0 ] = w_addr;
    buffer[ 1 ] = w_data;

    i2c_master_write( &ctx->i2c, buffer, 2 );  
}

uint8_t proximity_read_byte ( proximity_t *ctx, uint8_t r_addr )
{
    uint8_t read_data;

    i2c_master_write_then_read( &ctx->i2c, &r_addr, 1, &read_data, 1 );
    
    return read_data;
}

void proximity_read_data ( proximity_t *ctx, uint8_t r_addr, uint8_t* rcv_data, uint8_t n_len )
{
    i2c_master_write_then_read( &ctx->i2c, &r_addr, 1, rcv_data, n_len );
}

void proximity_write_data ( proximity_t *ctx, uint8_t w_addr, uint8_t* wr_data, uint8_t n_len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = w_addr;
    
    for ( cnt = 1; cnt <= n_len; cnt++ )
    {
        tx_buf[ cnt ] = wr_data[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, n_len + 1 );   
}

void proximity_set_default_mode ( proximity_t *ctx )
{
    proximity_write_byte( ctx, PROXIMITY_REGISTER_PROX_CURRENT, 20 );
    proximity_write_byte( ctx, PROXIMITY_REGISTER_PROX_RATE, PROXIMITY_MEASUREMENT_RATE_31 );
    proximity_write_byte( ctx, PROXIMITY_REGISTER_COMMAND, PROXIMITY_COMMAND_PROX_ENABLE | 
                               PROXIMITY_COMMAND_AMBI_ENABLE | 
                               PROXIMITY_COMMAND_SELFTIMED_MODE_ENABLE );
    proximity_write_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_CONTROL, 
                               PROXIMITY_INTERRUPT_THRES_SEL_PROX | 
                               PROXIMITY_INTERRUPT_THRES_ENABLE | 
                               PROXIMITY_INTERRUPT_COUNT_EXCEED_1 );
    proximity_write_byte( ctx, PROXIMITY_REGISTER_AMBI_PARAMETER, 
                               PROXIMITY_AMBI_PARA_AVERAGE_32 | 
                               PROXIMITY_AMBI_PARA_AUTO_OFFSET_ENABLE | 
                               PROXIMITY_AMBI_PARA_MEAS_RATE_2 );
}

void proximity_set_upper_threshold ( proximity_t *ctx )
{
    uint8_t i_loop;
    uint16_t proxi_value;
    uint8_t command;
    uint8_t lo_byte, hi_byte;
    uint32_t summ_proxi_value = 0;
    uint16_t proximity_average_proxi_value;
    uint8_t proximity_data[ 2 ];

    for (i_loop = 0; i_loop < 16; i_loop++)
    {
        do
        {
            command = proximity_read_byte( ctx, PROXIMITY_REGISTER_COMMAND );
        } 
        while (0 == ( command & PROXIMITY_COMMAND_MASK_PROX_DATA_READY ) );
        
        proximity_read_data( ctx, PROXIMITY_REGISTER_PROX_VALUE, &proximity_data[ 0 ], 2 );
        proxi_value = proximity_data[ 0 ];
        proxi_value <<= 8;
        proxi_value |= proximity_data[ 1 ];
        summ_proxi_value += proxi_value;
    }
    proximity_average_proxi_value = summ_proxi_value / 16;

    lo_byte = ( uint8_t )( ( proximity_average_proxi_value + 20 ) & 0x00FF );
    hi_byte = ( uint8_t )( ( ( proximity_average_proxi_value + 20 ) & 0xFF00 ) >> 8 );
    proximity_write_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_HIGH_THRES, hi_byte );
    proximity_write_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_HIGH_THRES + 1, lo_byte );
}

uint16_t proximity_read_prox_data ( proximity_t *ctx )
{
    uint8_t proximity_command;
    uint16_t proximity_proxi_value;
    uint8_t proximity_interrupt_status;
    uint8_t proximity_data[ 2 ];
    
    do
    {
        proximity_command = proximity_read_byte( ctx, PROXIMITY_REGISTER_COMMAND );
    }
    while (0 == ( proximity_command & PROXIMITY_COMMAND_MASK_PROX_DATA_READY ) );

    proximity_interrupt_status = proximity_read_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_STATUS );
    if (proximity_interrupt_status & PROXIMITY_INTERRUPT_MASK_STATUS_THRES_HI )
    {
        proximity_write_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_STATUS, proximity_interrupt_status );
    }

    if ( ( proximity_command & PROXIMITY_COMMAND_MASK_PROX_DATA_READY ) != 0 )
    { 
        proximity_read_data( ctx, PROXIMITY_REGISTER_PROX_VALUE, &proximity_data[ 0 ], 2 );
        proximity_proxi_value = proximity_data[0];
        proximity_proxi_value <<= 8;
        proximity_proxi_value |= proximity_data[1];
        return  proximity_proxi_value;
    }
    return 0;
}

uint16_t proximity_read_ambient_light ( proximity_t *ctx )
{
    uint8_t proximity_command;
    uint16_t proximity_ambi_value;
    uint8_t proximity_interrupt_status;
    uint8_t proximity_data[ 2 ];

    do
    {
        proximity_command = proximity_read_byte( ctx, PROXIMITY_REGISTER_COMMAND );
    }
    while ( 0 == ( proximity_command & PROXIMITY_COMMAND_MASK_AMBI_DATA_READY ) );

    proximity_interrupt_status = proximity_read_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_STATUS );
    
    if ( proximity_interrupt_status & PROXIMITY_INTERRUPT_MASK_STATUS_THRES_HI )
    {
        proximity_write_byte( ctx, PROXIMITY_REGISTER_INTERRUPT_STATUS, proximity_interrupt_status );
    }

    if ( ( proximity_command & PROXIMITY_COMMAND_MASK_AMBI_DATA_READY ) != 0 )
    {
         proximity_read_data( ctx, PROXIMITY_REGISTER_AMBI_VALUE, &proximity_data[ 0 ], 2 );
         proximity_ambi_value = proximity_data[ 0 ];
         proximity_ambi_value <<= 8;
         proximity_ambi_value |= proximity_data[ 1 ];
         return proximity_ambi_value;
    }
    return 0;
}

// ------------------------------------------------------------------------- END


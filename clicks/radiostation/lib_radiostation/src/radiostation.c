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

#include "radiostation.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void send_command (  radiostation_t *ctx, radiostation_cmd_t *cmd  );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void radiostation_cfg_setup ( radiostation_cfg_t *cfg, bool slave_select )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->sen  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->slave_select = slave_select;
}

RADIOSTATION_RETVAL radiostation_init ( radiostation_t *ctx, radiostation_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    if ( cfg->slave_select == true )
    {
        ctx->slave_address = RADIOSTATION_SLAVE_ADDR0;
        digital_out_write( &ctx->sen, 0 );
    }
    else if ( cfg->slave_select == false )
    {
        ctx->slave_address = RADIOSTATION_SLAVE_ADDR1;
        digital_out_write( &ctx->sen, 0 );
    }

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RADIOSTATION_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->sen, cfg->sen );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_write( &ctx->rst, 0 );
    Delay_80us(  );    // 100us is the minimum duration of RST as per datasheet.
    Delay_10us(  );    // 100us is the minimum duration of RST as per datasheet.
    Delay_10us(  );    // 100us is the minimum duration of RST as per datasheet.
    digital_out_write( &ctx->rst, 1 );

    return RADIOSTATION_OK;
}

void radiostation_default_cfg ( radiostation_t *ctx, radiostation_cmd_t *cmd )
{
    uint8_t buff[ 16 ];

    ctx->status = radiostation_power_up( ctx, cmd );
    radiostation_get_revision( ctx, cmd, &buff[ 0 ] );
    ctx->status = radiostation_set_tune_frequency ( ctx, cmd, ctx->transmit_frequency );
    radiostation_busy_wait_for_stcint( ctx, cmd );
    radiostation_get_tune_status( ctx, cmd, 1, &buff[ 0 ] );
    ctx->status = radiostation_set_tune_power( ctx, cmd, 115, 0 );
    radiostation_busy_wait_for_stcint( ctx, cmd );
    radiostation_get_tune_status( ctx, cmd, 1, &buff[ 0 ] );
}

void radiostation_write ( radiostation_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, data_buf, len );
}

void radiostation_read ( radiostation_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );
}

uint8_t radiostation_power_up_advanced ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t config ) 
{
    uint8_t params[ 3 ];
    uint8_t ret_vals[ 1 ];

    params[ 0 ] = 0x01;             // POWER_UP

                // XOSCEN = 1   // FUNC = 2 (Transmit)
    params[ 1 ] =   0x10    |   ( 0x02 & 0x0F );
    if ( ( config & RADIOSTATION_CTS_INTERRUPT_ENABLE ) != 0 )
        params[ 1 ] |= 0x80;
    if ( ( config & RADIOSTATION_GPO2_OUTPUT_ENABLE ) != 0 )
        params[ 1 ] |= 0x40;
    if ( ( config & RADIOSTATION_PATCH_ENABLE ) != 0 )
        params[ 1 ] |= 0x20;
    params[ 2 ] = 0x50;             // OPMODE = Analog audio inputs

    cmd->params = params;
    cmd->params_count = 3;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );
    Delay_100ms( );        // Powerup Settling Time! (110) 500 kada je XOSCEN setovan.
    Delay_100ms( );      
    Delay_100ms( );      
    Delay_100ms( );      
    Delay_100ms( );      

    return ret_vals[ 0 ];
}

uint8_t radiostation_power_up ( radiostation_t *ctx, radiostation_cmd_t *cmd ) 
{
    return radiostation_power_up_advanced( ctx, cmd, 0 );
}

uint8_t radiostation_power_down ( radiostation_t *ctx, radiostation_cmd_t *cmd )
 {
    uint8_t params[ 1 ];
    uint8_t ret_vals[ 1 ];

    params[ 0 ] = 0x11;     // POWER_DOWN

    cmd->params = params;
    cmd->params_count = 1;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint8_t radiostation_get_revision ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t *ret_vals ) 
{
    uint8_t params[ 1 ];
    params[ 0 ] = 0x10;     // GET_REV

    cmd->params = params;
    cmd->params_count = 1;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1 + 8;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint8_t radiostation_get_revision1 ( radiostation_t *ctx, uint8_t *ret_vals ) 
{
    uint8_t params[ 1 ];
    uint8_t status12 = 0x00;
    params[ 0 ] = 0x10;     // GET_REV
   
    radiostation_write( ctx, params, 1 );
    do 
    {
        radiostation_read( ctx, &status12, 1 );
    }
    while ( ( status12 & 0x80 ) == 0 );
    
    radiostation_read( ctx, ret_vals, 8 );
    
    return status12;
}

uint8_t radiostation_set_tune_frequency ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t freq ) 
{
    uint8_t params[ 4 ];
    uint8_t ret_vals[ 1 ];

    if ( freq < 7600 || freq > 10800 )
       freq = 7600;
    params[ 0 ] = 0x30;     // TX_TUNE_FREQ
    params[ 1 ] = 0x00;     // Always write 0.
    params[ 2 ] = ( uint8_t ) ( freq >> 8 );
    params[ 3 ] = ( uint8_t ) ( freq );

    cmd->params = params;
    cmd->params_count = 4;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint8_t radiostation_set_tune_power ( radiostation_t *ctx,  radiostation_cmd_t *cmd, uint8_t voltage, uint8_t capacitance )
 {
    uint8_t params[ 5 ];
    uint8_t ret_vals[ 1 ];

    params[ 0 ] = 0x31;     // TX_TUNE_POWER
    params[ 1 ] = 0x00;     // Always write 0.
    params[ 2 ] = 0x00;     // Always write 0.
    params[ 3 ] = voltage >= 88 && voltage <= 120 ? voltage : 115;
    params[ 4 ] = capacitance >= 0 && capacitance <= 191 ? capacitance : 0;

    cmd->params = params;
    cmd->params_count = 5;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint8_t radiostation_get_tune_measure ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t freq, uint8_t capacitance ) 
{
    uint8_t params[ 5 ], ret_vals[ 1 ];
    params[ 0 ] = 0x32;     // TX_TUNE_MEASURE
    params[ 1 ] = 0x00;     // Always write 0.
    params[ 2 ] = ( uint8_t ) ( freq >> 8 );
    params[ 3 ] = ( uint8_t ) ( freq );
    params[ 4 ] = capacitance >= 0 && capacitance <= 191 ? capacitance : 0; // 0 za automatsku kapacitivnost.
    
    cmd->params = params;
    cmd->params_count = 5;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );
    
    return ret_vals[ 0 ];
}

uint8_t radiostation_get_int_status ( radiostation_t *ctx, radiostation_cmd_t *cmd ) 
{
    uint8_t param;
    uint8_t status;
    param = 0x14;   // GET_INT_STATUS

    cmd->params = &param;
    cmd->params_count = 1;
    cmd->ret_vals = &status;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );

    return status;
}

void radiostation_busy_wait_for_stcint ( radiostation_t *ctx, radiostation_cmd_t *cmd ) 
{
    uint8_t status;
    do 
    {
        status = radiostation_get_int_status( ctx, cmd );
    }
    while ( ( status & RADIOSTATION_STCINT ) == 0 );
}

void radiostation_busy_wait_for_asqint ( radiostation_t *ctx, radiostation_cmd_t *cmd )
 {
    uint8_t status;
    do 
    {
        status = radiostation_get_int_status ( ctx, cmd );
    }
    while ( ( status & RADIOSTATION_ASQINT ) == 0 );
}

void radiostation_busy_wait_for_rdsint ( radiostation_t *ctx, radiostation_cmd_t *cmd )
 {
    uint8_t status;
    do 
    {
        status = radiostation_get_int_status ( ctx, cmd );
    }
    while ( ( status & RADIOSTATION_RDSINT ) == 0 );
}

uint8_t radiostation_get_tune_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t clear_stc_status_bit, uint8_t *ret_vals ) 
{
    uint8_t params[ 2 ];
    params[ 0 ] = 0x33;     // TX_TUNE_STATUS
    params[ 1 ] = clear_stc_status_bit != 0 ? 0x01 : 0x00;

    cmd->params = params;
    cmd->params_count = 1;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1 + 7;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint8_t radiostation_get_asq_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t *ret_vals ) 
{
    uint8_t params[ 2 ];
    params[ 0 ] = 0x34;     // TX_ASQ_STATUS
    params[ 1 ] = 0x01;     // INTACK bit

    cmd->params = params;
    cmd->params_count = 1;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1 + 4;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint8_t radiostation_set_property ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t property_id, uint16_t property_value ) 
{
    uint8_t params[ 6 ];
    uint8_t ret_vals[ 1 ];

    params[ 0 ] = 0x12;     // SET_PROPERTY
    params[ 1 ] = 0x00;     // Always 0.
    params[ 2 ] = ( uint8_t ) ( property_id >> 8 );
    params[ 3 ] = ( uint8_t ) ( property_id );
    if ( property_id == RADIOSTATION_PROP_TX_ASQ_LEVEL_LOW  || 
         property_id == RADIOSTATION_PROP_TX_ASQ_LEVEL_HIGH )
    {
        // If the number -70 is sent to the function, property_value will be 0xFFBA, 
        // but Click is expecting 0x00BA! 
        // That's why the 5th byte is corect manualy.
            params[ 4 ] = 0x00;
    }
    else
    {
        params[ 4 ] = ( uint8_t ) ( property_value >> 8 );
    }
    params[ 5 ] = ( uint8_t ) ( property_value );

    cmd->params = params;
    cmd->params_count = 6;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1;
    send_command( ctx, cmd );

    return ret_vals[ 0 ];
}

uint16_t radiostation_get_property ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t property_id )
 {
    uint8_t params[ 4 ], ret_vals[ 1 + 3 ];
    params[ 0 ] = 0x13;     // GET_PROPERTY
    params[ 1 ] = 0x00;     // Always 0.
    params[ 2 ] = ( uint8_t ) ( property_id >> 8 );
    params[ 3 ] = ( uint8_t ) ( property_id );

    cmd->params = params;
    cmd->params_count = 4;
    cmd->ret_vals = ret_vals;
    cmd->ret_vals_count = 1 + 3;
    send_command( ctx, cmd );

    return ( ( uint16_t ) ret_vals[ 2 ] << 8 ) | ret_vals[ 3 ];
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void send_command ( radiostation_t *ctx, radiostation_cmd_t *cmd ) 
{
    radiostation_write( ctx, cmd->params, cmd->params_count );
    do 
    { 
        radiostation_read( ctx, cmd->ret_vals, cmd->ret_vals_count );
    }
    while ( ( cmd->ret_vals[ 0 ] & RADIOSTATION_CTS ) == 0 );

}

// ------------------------------------------------------------------------- END


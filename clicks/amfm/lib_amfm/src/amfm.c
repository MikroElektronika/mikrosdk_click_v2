/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "amfm.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void amfm_cfg_setup ( amfm_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->gp1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->sen = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AMFM_DEVICE_ADDRESS;
}

err_t amfm_init ( amfm_t *ctx, amfm_cfg_t *cfg )
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

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->sen, cfg->sen );
    digital_out_init( &ctx->shd, cfg->shd );

    // Input pins
    digital_in_init( &ctx->gp1, cfg->gp1 );
    digital_in_init( &ctx->gp2, cfg->gp2 );
    ctx->gp1_pin = cfg->gp1;
    ctx->gp2_pin = cfg->gp2;
   
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->shd );

    return AMFM_OK;
}

void amfm_generic_write ( amfm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );       
}

void amfm_generic_read ( amfm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t amfm_an_get ( amfm_t *ctx )
{
    return digital_in_read( &ctx->gp1 );
}

uint8_t amfm_int_get ( amfm_t *ctx )
{
    return digital_in_read( &ctx->gp2 );
}

void amfm_rst_set ( amfm_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->rst, pin_state );
}

void amfm_cs_set ( amfm_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->sen, pin_state );
}

uint8_t amfm_send_command ( amfm_t *ctx, uint8_t *cmd_and_args_buf )
{
    uint8_t n_bytes;
    uint8_t n_response_bytes;
    
    switch ( cmd_and_args_buf[ 0 ] )
    {
        case AMFM_CMD_PWRUP :
        {
            if ( AMFM_PWRUP_ARG1_FUNC_FMRECEIVE == ( cmd_and_args_buf[ 1 ] & 0x0F ) )
            {
                n_response_bytes = 1;
            }
            else if ( AMFM_PWRUP_ARG1_FUNC_QUERYLIBID == ( cmd_and_args_buf[ 1 ] & 0x0F ) )
            {
                n_response_bytes =  8;
            }
            n_bytes = 3;
            break;
        }
        case AMFM_CMD_GETREV :
        {
            n_bytes = 1;
            n_response_bytes = 9;
            break;
        }
        case AMFM_CMD_PWRDOWN :
        {
            n_bytes = 1;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_SETPROP :
        {
            n_bytes = 6;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_GETPROP :
        {
            n_bytes = 4;
            n_response_bytes = 4;
            break;
        }
        case AMFM_CMD_GETINTSTATUS :
        {
            n_bytes = 1;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_FMTUNEFREQ :
        {
            n_bytes = 5;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_FMSEEKSTART :
        {
            n_bytes = 2;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_FMTUNESTATUS :
        {
            n_bytes = 2;
            n_response_bytes = 8;
            break;
        }
        case AMFM_CMD_FMRSQSTATUS :
        {
            n_bytes = 2;
            n_response_bytes = 8;
            break;
        }
        case AMFM_CMD_FMRDSSTATUS :
        {
            n_bytes = 2;
            n_response_bytes = 13;
            break;
        }
        case AMFM_CMD_FMAGCSTATUS :
        {
            n_bytes = 1;
            n_response_bytes = 3;
            break;
        }
        case AMFM_CMD_FMAGCOVERRIDE :
        {
            n_bytes = 3;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_GPIOCTL :
        {
            n_bytes = 2;
            n_response_bytes = 1;
            break;
        }
        case AMFM_CMD_GPIOSET :
        {
            n_bytes = 2;
            n_response_bytes = 1;
            break;
        }
        default :
        {
            n_bytes = 0;
            n_response_bytes = 0;
            break;
        }
    }

    amfm_generic_write( ctx, cmd_and_args_buf[ 0 ], &cmd_and_args_buf[ 1 ], n_bytes );
    return n_response_bytes;
}

uint8_t amfm_get_cts ( amfm_t *ctx )
{
    uint16_t status_counter = 0;
    uint8_t status_check = 0;
    uint8_t error_flag = 0;
    
    while ( ( 0 == ( status_check & 0x80 ) ) && ( 0 == error_flag ) )
    {
        amfm_generic_read( ctx, 0x00, &status_check, 1 );

        status_counter++;

        if ( status_counter > 500 )
        {
            error_flag = 1;
        }
    }
    return error_flag;
}

uint8_t amfm_get_stc ( amfm_t *ctx )
{
    uint16_t status_counter = 0;
    uint8_t status_check = 0;
    uint8_t error_flag = 0;

    error_flag = amfm_get_cts( ctx );

    while ( ( 0 == ( status_check & 0x01 ) ) && ( 0 == error_flag ) )
    {
        ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_GETINTSTATUS;
        amfm_send_command( ctx, ctx->command_and_arguments_buffer );

        amfm_generic_read( ctx, 0x00, &status_check, 1 );

        status_counter++;

        if ( status_counter >= 65535 )
        {
            error_flag = 1;
        }
    }

    return error_flag;
}

uint8_t amfm_get_rsq ( amfm_t *ctx )
{
    uint16_t status_counter = 0;
    uint8_t status_check = 0;
    uint8_t error_flag = 0;

    error_flag = amfm_get_cts( ctx );

    while ( ( 0 == ( status_check & 0x08 ) ) && ( 0 == error_flag ) )
    {
        ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_GETINTSTATUS;
        amfm_send_command( ctx, ctx->command_and_arguments_buffer );

        amfm_generic_read( ctx, 0x00, &status_check, 1 );

        status_counter++;

        if ( status_counter >= 65535 )
        {
            error_flag = 1;
        }
    }

    return error_flag;
}

uint8_t amfm_get_rds ( amfm_t *ctx )
{
    uint16_t status_counter = 0;
    uint8_t status_check = 0;
    uint8_t error_flag = 0;

    error_flag = amfm_get_cts( ctx );

    while ( ( 0 == ( status_check & 0x04 ) ) && ( 0 == error_flag ) )
    {
        ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_GETINTSTATUS;
        amfm_send_command( ctx, ctx->command_and_arguments_buffer );

        amfm_generic_read( ctx, 0x00, &status_check, 1 );

        status_counter++;

        if ( status_counter >= 65535 )
        {
            error_flag = 1;
        }
    }

    return error_flag;
}

uint8_t amfm_get_response ( amfm_t *ctx, uint8_t *resp_buf, uint8_t n_bytes )
{
    uint8_t status_byte;
    
    status_byte = amfm_get_cts( ctx );
    
    if ( 1 == status_byte )
    {
        return 1;
    }
    else if ( 0 == status_byte )
    {
        if ( 0 == n_bytes )
        {
            return 0;
        }
        else
        {
            amfm_generic_read( ctx, 0x00, resp_buf, n_bytes );
            return 0;
        }
    }
}

uint8_t amfm_init_device ( amfm_t *ctx )
{
    digital_out_t gp1;
    digital_out_t gp2;
    digital_out_init ( &gp1, ctx->gp1_pin );
    digital_out_init ( &gp2, ctx->gp2_pin );
    digital_out_high( &gp1 );
    digital_out_low( &gp2 );
    Delay_100ms( );
    digital_out_low( &ctx->sen );
    digital_out_low( &ctx->rst );

    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    
    digital_in_init( &ctx->gp1, ctx->gp1_pin );
    digital_in_init( &ctx->gp2, ctx->gp2_pin );
    Delay_100ms( );

    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_PWRUP;
    ctx->command_and_arguments_buffer[ 1 ] = AMFM_PWRUP_ARG1_CTSIEN | AMFM_PWRUP_ARG1_GPO2OEN | 
                                             AMFM_PWRUP_ARG1_XOSCEN | AMFM_PWRUP_ARG1_FUNC_FMRECEIVE;
    ctx->command_and_arguments_buffer[ 2 ] = AMFM_PWRUP_ARG2_OPMODE_ANALOGOUT;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );
    
    return amfm_get_cts( ctx );
}

uint8_t amfm_seek ( amfm_t *ctx )
{
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMSEEKSTART;
    ctx->command_and_arguments_buffer[ 1 ] = AMFM_FMSEEKSTART_ARG1_SEEKUP | AMFM_FMSEEKSTART_ARG1_WRAP;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );
    
    return amfm_get_stc( ctx );
}

uint8_t amfm_set_volume ( amfm_t *ctx, uint8_t volume )
{
    if ( ( volume >= 0 ) && ( volume <= 63 ) )
    {
        ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_SETPROP;
        ctx->command_and_arguments_buffer[ 1 ] = 0x00;
        ctx->command_and_arguments_buffer[ 2 ] = AMFM_PROP_RXVOLUME_H;
        ctx->command_and_arguments_buffer[ 3 ] = AMFM_PROP_RXVOLUME_L;
        ctx->command_and_arguments_buffer[ 4 ] = 0x00;
        ctx->command_and_arguments_buffer[ 5 ] = volume;

        amfm_send_command( ctx, ctx->command_and_arguments_buffer );

        return amfm_get_cts( ctx );
    }
    else
    {
        return 1;
    }
}

uint8_t amfm_mute ( amfm_t *ctx )
{
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_SETPROP;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->command_and_arguments_buffer[ 2 ] = AMFM_PROP_RXHMUTE_H;
    ctx->command_and_arguments_buffer[ 3 ] = AMFM_PROP_RXHMUTE_L;
    ctx->command_and_arguments_buffer[ 4 ] = 0x00;
    ctx->command_and_arguments_buffer[ 5 ] = AMFM_PROPVALL_LMUTE | AMFM_PROPVALL_RMUTE;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );
    
    return amfm_get_cts( ctx );
}

uint8_t amfm_unmute ( amfm_t *ctx )
{
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_SETPROP;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->command_and_arguments_buffer[ 2 ] = AMFM_PROP_RXHMUTE_H;
    ctx->command_and_arguments_buffer[ 3 ] = AMFM_PROP_RXHMUTE_L;
    ctx->command_and_arguments_buffer[ 4 ] = 0x00;
    ctx->command_and_arguments_buffer[ 5 ] = 0x00;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );

    return amfm_get_cts( ctx );
}

uint8_t amfm_tune_up ( amfm_t *ctx )
{
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMTUNESTATUS;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->n_bytes = amfm_send_command( ctx, ctx->command_and_arguments_buffer );
    amfm_get_response( ctx, ctx->response_buffer, ctx->n_bytes );

    ctx->aux_variable = ( ctx->response_buffer[ 2 ] * 256 );
    ctx->aux_variable += ctx->response_buffer[ 3 ];
    ctx->aux_variable += 10;

    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMTUNEFREQ;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->command_and_arguments_buffer[ 2 ] = ( uint8_t )( ctx->aux_variable >> 8 );
    ctx->command_and_arguments_buffer[ 3 ] = ( uint8_t )( ctx->aux_variable );
    ctx->command_and_arguments_buffer[ 4 ] = 0x00;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );

    return amfm_get_stc( ctx );
}

uint8_t amfm_tune_down ( amfm_t *ctx )
{
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMTUNESTATUS;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->n_bytes = amfm_send_command( ctx, ctx->command_and_arguments_buffer );
    amfm_get_response( ctx, ctx->response_buffer, ctx->n_bytes );

    ctx->aux_variable = ( ctx->response_buffer[ 2 ] * 256 );
    ctx->aux_variable += ctx->response_buffer[ 3 ];
    ctx->aux_variable -= 10;

    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMTUNEFREQ;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->command_and_arguments_buffer[ 2 ] = ( uint8_t )( ctx->aux_variable >> 8 );
    ctx->command_and_arguments_buffer[ 3 ] = ( uint8_t )( ctx->aux_variable );
    ctx->command_and_arguments_buffer[ 4 ] = 0x00;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );

    return amfm_get_stc( ctx );
}

uint8_t amfm_tune_frequency ( amfm_t *ctx, uint16_t frequency )
{
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMTUNEFREQ;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->command_and_arguments_buffer[ 2 ] = ( uint8_t )( frequency >> 8 );
    ctx->command_and_arguments_buffer[ 3 ] = ( uint8_t )( frequency );
    ctx->command_and_arguments_buffer[ 4 ] = 0x00;

    amfm_send_command( ctx, ctx->command_and_arguments_buffer );

    return amfm_get_stc( ctx );
}

uint16_t amfm_get_channel ( amfm_t *ctx )
{
    uint16_t channel_value;
        
    ctx->command_and_arguments_buffer[ 0 ] = AMFM_CMD_FMTUNESTATUS;
    ctx->command_and_arguments_buffer[ 1 ] = 0x00;
    ctx->n_bytes = amfm_send_command( ctx, ctx->command_and_arguments_buffer );

    amfm_get_response( ctx, ctx->response_buffer, ctx->n_bytes );
    
    channel_value = ( ctx->response_buffer[ 2 ] * 256 );
    channel_value += ctx->response_buffer[ 3 ];

    return channel_value;
}

// ------------------------------------------------------------------------- END


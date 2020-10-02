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

#include "smartdof.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Sets specified number of array elements to 0x00
 */
static void smartdof_erase_buffer ( uint8_t *erase_buffer, uint16_t buffer_size );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void smartdof_cfg_setup ( smartdof_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst     = HAL_PIN_NC;
    cfg->bt      = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SLAVE_ADDRESS;
}

SMARTDOF_RETVAL smartdof_init ( smartdof_t *ctx, smartdof_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SMARTDOF_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->bt, cfg->bt );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    // Example: Sets pin [high, low] 

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->bt );

    return SMARTDOF_OK;
}

uint8_t smartdof_default_cfg ( smartdof_t *ctx )
{
    smartdof_device_reset( ctx, SMARTDOF_BMODE_NORMAL );

    //  device sends 3 data packets after reset

    if ( smartdof_receive_packet( ctx, 10000000 ) == 1 ) 
    {
        return 1; // response 1
    }
    else 
    {
        Delay_1ms();
    }

    if ( smartdof_receive_packet( ctx, 10000000 ) == 1 ) 
    {
        return 1; // response 2
    }
    else 
    {
        Delay_1ms();
    }

    if ( smartdof_receive_packet( ctx, 10000000 ) == 1 ) 
    {
        return 1; // response 3
    }
    else 
    {
        Delay_1ms();
    }

    //  erases first 9 send data buffer elements as we need to send 9 command parameters
    
    smartdof_erase_buffer( ctx->send_data_buf, 9 ); 

    //  sub command (parameter 0) - reinitialize entire sensor hub

    ctx->send_data_buf[ 0 ] = SMARTDOF_CMD_INIT_SCMD_ENT_SENS_HUB;

    //  initialize command

    smartdof_command_request( ctx, SMARTDOF_CMD_INIT, ctx->send_data_buf );
    Delay_1ms();
    
    if ( smartdof_receive_packet( ctx, 10000000 ) == 1 ) 
    {
        return 1; // initialize command response
    }
    else 
    {
        Delay_1ms();
    }

    if ( ctx->rec_data_buf[ 0 + 4 ]  != 0xF1 ) 
    {
        return 1; // checking for correct report id
    }
    if ( ctx->rec_data_buf[ 2 + 4 ]  != 0x04 ) 
    {
        return 1; // checking for correct command
    }
    if ( ctx->rec_data_buf[ 5 + 4 ]  != 0x00 ) 
    {
        return 1; // checking for correct status (status = successful)
    }
    if ( ctx->rec_data_buf[ 6 + 4 ]  != 0x01 ) 
    {
        return 1; // checking for correct sub command
    }

    //  returns no error (0) for successful operation
    return 0;
}

void smartdof_i2c_write ( smartdof_t *ctx, uint8_t *write_data, uint16_t n_bytes )
{
    i2c_master_write( &ctx->i2c, write_data, n_bytes );     
}

void smartdof_i2c_read ( smartdof_t *ctx,  uint8_t *read_data, uint16_t n_bytes )
{
    i2c_master_read( &ctx->i2c, read_data, n_bytes );  
}

uint8_t smartdof_int_get ( smartdof_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void smartdof_rst_set ( smartdof_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->rst, pin_state );
}

void smartdof_bt_set ( smartdof_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->bt, pin_state );
}

void smartdof_device_reset ( smartdof_t *ctx, uint8_t boot_mode )
{
    //  selecting boot mode

    smartdof_bt_set( ctx, boot_mode); // boot pin

    //  deveice reset

    smartdof_rst_set( ctx, 1 );
    Delay_10ms();
    smartdof_rst_set( ctx, 0 );
    Delay_10ms();
    smartdof_rst_set( ctx, 1 );
    Delay_1ms();
}

float smartdof_q_point_to_float ( int16_t sensor_data, uint8_t sensor_q_point )
{
    float return_value;

    return_value = ( float )( sensor_data );
    return_value *= ( float )( 1.0 / ( float )( 1 << sensor_q_point ) );

    return return_value;
}

void smartdof_send_packet ( smartdof_t *ctx, uint8_t channel_number, uint16_t data_length, uint8_t *packet_data )
{
    uint16_t i;
    uint8_t sequence_number[ 6 ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    for ( i = data_length; i > 0; i -- )
    {
        packet_data[ i + 3 ] = packet_data[ i - 1 ];
    }

    packet_data[ 0 ] = ( uint8_t )( data_length + 4 );           // Data length LSB
    packet_data[ 1 ] = ( uint8_t )( ( data_length + 4 ) >> 8 );  // Data length MSB
    packet_data[ 2 ] = channel_number;                           // Channel number
    packet_data[ 3 ] = sequence_number[ channel_number ];        // Sequence number

    //  Incrementing specified channel number

    if ( sequence_number[ channel_number ] < 255) 
    {
        sequence_number[ channel_number ]++;
    }
    else 
    {
        // Incrementing sequence number each time function is called
        sequence_number[ channel_number ] = 0; 
    }

    //  sending packet data including 4 header bytes

    smartdof_i2c_write( ctx, packet_data, ( uint16_t )( data_length + 4 ) );
}

uint8_t smartdof_receive_packet ( smartdof_t *ctx, uint32_t n_cycles_timeout )
{
    uint32_t timeout_counter;

    //  Erases receiving data buffer every time function is called

    smartdof_erase_buffer( ctx->rec_data_buf, 1024 );

    // Reset counter

    timeout_counter = 0; 

    //  Waits for int pin to go low and checks if counter exceeded specified value

    while ( ( smartdof_int_get( ctx ) == 1 ) && ( timeout_counter < n_cycles_timeout ) )
    {
        timeout_counter ++;
    }
    if ( timeout_counter == n_cycles_timeout )
    {
        // return error (1) if counter exceeded specified threshold value

        return 1; 
    }

    // Receives message header bytes

    smartdof_i2c_read( ctx, ctx->rec_data_buf, 4 ); 

    //  Moving received header to shtp_header[] buffer

    ctx->shtp_header[ 0 ] = ctx->rec_data_buf[ 0 ]; // data length LSB
    ctx->shtp_header[ 1 ] = ctx->rec_data_buf[ 1 ]; // data length MSB
    ctx->shtp_header[ 2 ] = ctx->rec_data_buf[ 2 ]; // channel
    ctx->shtp_header[ 3 ] = ctx->rec_data_buf[ 3 ]; // sequence number

    //  Data length calculation

    ctx->data_len = ctx->rec_data_buf[ 1 ];
    ctx->data_len <<= 8;
    ctx->data_len |= ctx->rec_data_buf[ 0 ];

    //  Removing most significant bit 
    //  (most significant bit tells us if received message is a continuation of previous message)
    ctx->data_len &= 0x7FFF; 

    //  Reset counter
    timeout_counter = 0; 

    //  Waits for int pin to go low and checks if counter exceeded specified value
    
    while ( ( smartdof_int_get( ctx ) == 1 ) && ( timeout_counter < n_cycles_timeout ) )
    {
        timeout_counter ++;
    }
    if ( timeout_counter == n_cycles_timeout )
    {
        return 1; // return error (1) if counter exceeded specified threshold value
    }
    smartdof_i2c_read( ctx, ctx->rec_data_buf, ctx->data_len ); // reads rest of the data (including header)
    ctx->data_len -= 4; // received data length minus four header bytes (i.e. data length only)
    
    return 0; // returns no error (0) if data reception was successful
}

void smartdof_get_data ( smartdof_t *ctx, uint8_t *data_header, uint16_t *data_length, uint8_t *data_buffer )
{
    uint16_t i;
    
    //  moves received header bytes to user header buffer
    
    for ( i = 0; i < 4; i ++ )
    {
        data_header[ i ] = ctx->shtp_header[ i ];
    }

    //  moves data length value to data length variable

    *data_length = ctx->data_len;
    
    //  moves all received data bytes to data buffer

    for ( i = 0; i < ctx->data_len; i ++ )
    {
        data_buffer[ i ] = ctx->rec_data_buf[ i + 4 ];
    }
}

void smartdof_product_id_request ( smartdof_t *ctx )
{
    ctx->send_data_buf[ 0 ] = 0xF9; // product id request report id
    ctx->send_data_buf[ 1 ] = 0x00; // reserved

    // sending these 2 bytes over control channel

    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 2, ctx->send_data_buf ); 
}

uint8_t smartdof_product_id_response ( smartdof_t *ctx, smartdof_pir_t *pir )
{
    if ( smartdof_receive_packet( ctx, 1000000 ) == 1 )
    {
        return 1; // receives packet and returns error (1) if no packet is received
    }
    if ( ctx->data_len != 16 ) 
    {
        return 1; // checks if received data length is correct
    }
    if ( ctx->rec_data_buf[ 0 + 4 ] != 0xF8 ) 
    {
        return 1; // check if correct report id is received
    }

    //  parsing data

    *pir->reset_cause = ctx->rec_data_buf[ 1 + 4 ];
    *pir->sw_version  = ctx->rec_data_buf[ 2 + 4 ];
    *pir->sw_version <<= 8;
    *pir->sw_version |= ctx->rec_data_buf[ 3 + 4 ];

    *pir->sw_part_number  = ctx->rec_data_buf[ 7 + 4 ];
    *pir->sw_part_number <<= 8;
    *pir->sw_part_number |= ctx->rec_data_buf[ 6 + 4 ];
    *pir->sw_part_number <<= 8;
    *pir->sw_part_number |= ctx->rec_data_buf[ 5 + 4 ];
    *pir->sw_part_number <<= 8;
    *pir->sw_part_number |= ctx->rec_data_buf[ 4 + 4 ];

    *pir->sw_build_number  = ctx->rec_data_buf[ 11 + 4 ];
    *pir->sw_build_number <<= 8;
    *pir->sw_build_number |= ctx->rec_data_buf[ 10 + 4 ];
    *pir->sw_build_number <<= 8;
    *pir->sw_build_number |= ctx->rec_data_buf[ 9 + 4 ];
    *pir->sw_build_number <<= 8;
    *pir->sw_build_number |= ctx->rec_data_buf[ 8 + 4 ];

    *pir->sw_version_patch  = ctx->rec_data_buf[ 13 + 4 ];
    *pir->sw_version_patch <<= 8;
    *pir->sw_version_patch |= ctx->rec_data_buf[ 12 + 4 ];

    //  returns no error (0) for successful operation
    return 0;
}

void smartdof_frs_write_request ( smartdof_t *ctx, uint16_t data_length, uint16_t frs_type )
{
    ctx->send_data_buf[ 0 ] = 0xF7; // frs write request report id
    ctx->send_data_buf[ 1 ] = 0x00; // reserved
    ctx->send_data_buf[ 2 ] = ( uint8_t )( data_length );      // data length LSB
    ctx->send_data_buf[ 3 ] = ( uint8_t )( data_length >> 8 ); // data length MSB
    ctx->send_data_buf[ 4 ] = ( uint8_t )( frs_type );         // FRS type LSB
    ctx->send_data_buf[ 5 ] = ( uint8_t )( frs_type >> 8 );    // FRS type MSB

    // sending these 6 bytes over control channel

    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 6, ctx->send_data_buf );
}

void smartdof_frs_write_data_request ( smartdof_t *ctx, uint16_t data_offset, uint32_t *data_buffer )
{
    ctx->send_data_buf[ 0 ]  = 0xF6; // frs write data request report id
    ctx->send_data_buf[ 1 ]  = 0x00; // reserved
    ctx->send_data_buf[ 2 ]  = ( uint8_t )( data_offset );
    ctx->send_data_buf[ 3 ]  = ( uint8_t )( data_offset >> 8 );
    ctx->send_data_buf[ 4 ]  = ( uint8_t )( data_buffer[ 0 ] );       // data word 0 LSB
    ctx->send_data_buf[ 5 ]  = ( uint8_t )( data_buffer[ 0 ] >> 8 );  // ...
    ctx->send_data_buf[ 6 ]  = ( uint8_t )( data_buffer[ 0 ] >> 16 ); // ...
    ctx->send_data_buf[ 7 ]  = ( uint8_t )( data_buffer[ 0 ] >> 24 ); // data word 0 MSB
    ctx->send_data_buf[ 8 ]  = ( uint8_t )( data_buffer[ 1 ]);       // data word 1 LSB
    ctx->send_data_buf[ 9 ]  = ( uint8_t )( data_buffer[ 1 ] >> 8 );  // ...
    ctx->send_data_buf[ 10 ] = ( uint8_t )( data_buffer[ 1 ] >> 16 ); // ...
    ctx->send_data_buf[ 11 ] = ( uint8_t )( data_buffer[ 1 ] >> 24 ); // data word 1 MSB

    // sending these 12 bytes over control channel

    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 12, ctx->send_data_buf );
}

uint8_t smartdof_frs_write_response ( smartdof_t *ctx, uint8_t *frs_status, uint16_t *data_offset )
{
    if ( smartdof_receive_packet( ctx, 1000000 ) == 1 ) 
    {
        return 1; // receives packet and returns error (1) if no packet is received
    }
    if ( ctx->data_len != 4 ) 
    {
        return 1; // checks if received data length is correct
    }
    if ( ctx->rec_data_buf[ 0 + 4 ] != 0xF5 ) 
    {
        return 1; // check if correct report id is received
    }

    *frs_status = ctx->rec_data_buf[ 1 + 4 ];   // frs status byte

    *data_offset = ctx->rec_data_buf[ 3 + 4 ];  // data offset MSB
    *data_offset <<= 8;
    *data_offset |= ctx->rec_data_buf[ 2 + 4 ]; // data offset LSB
    
    //  returns no error (0) for successful operation
    return 0;
}

void smartdof_frs_read_request ( smartdof_t *ctx, uint16_t data_offset, uint16_t frs_type, uint16_t data_size )
{
    ctx->send_data_buf[ 0 ] = 0xF4; // frs read requesf reprt id
    ctx->send_data_buf[ 1 ] = 0x00; // reserved
    ctx->send_data_buf[ 2 ] = ( uint8_t )( data_offset );      // data offset LSB
    ctx->send_data_buf[ 3 ] = ( uint8_t )( data_offset >> 8 ); // data offset MSB
    ctx->send_data_buf[ 4 ] = ( uint8_t )( frs_type );         // frs type LSB
    ctx->send_data_buf[ 5 ] = ( uint8_t )( frs_type >> 8 );    // frs type MSB
    ctx->send_data_buf[ 6 ] = ( uint8_t )( data_size );        // data size LSB
    ctx->send_data_buf[ 7 ] = ( uint8_t )( data_size >> 8 );   // data size MSB

    // sending these 8 bytes over control channel

    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 8, ctx->send_data_buf );
}

uint8_t smartdof_frs_read_response ( smartdof_t *ctx,  smartdof_rr_t *rr )
{
    if ( smartdof_receive_packet( ctx, 1000000 ) == 1 ) 
    {
        return 1; // receives packet and returns error (1) if no packet is received
    }
    if ( ctx->data_len != 16) 
    {
        return 1; // checks if received data length is correct
    }
    if ( ctx->rec_data_buf[ 0 + 4 ] != 0xF3) 
    {
        return 1; // check if correct report id is received
    }

    //  parsing data

    *rr->data_length = ctx->rec_data_buf[ 1 + 4 ];      // data length is in byte 1 of received data [7:4 ]
    *rr->data_length >>= 4;
    *rr->data_length &= 0x0F;                           // masking all other bits
    *rr->read_status = ctx->rec_data_buf[ 1 + 4 ];      // read status in in byte 1 of received data [3:0]
    *rr->read_status &= 0x0F;                           // masking all other bits
    *rr->data_offset = ctx->rec_data_buf[ 3 + 4 ];      // data offset MSB
    *rr->data_offset <<= 8;
    *rr->data_offset |= ctx->rec_data_buf[ 2 + 4 ];     // data offset LSB
    rr->data_buffer[ 0 ] = ctx->rec_data_buf[ 7 + 4 ];  // data word 0 MSB
    rr->data_buffer[ 0 ] <<= 8;
    rr->data_buffer[ 0 ] |= ctx->rec_data_buf[ 6 + 4 ];  // ...
    rr->data_buffer[ 0 ] <<= 8;
    rr->data_buffer[ 0 ] |= ctx->rec_data_buf[ 5 + 4 ];  // ...
    rr->data_buffer[ 0 ] <<= 8;
    rr->data_buffer[ 0 ] |= ctx->rec_data_buf[ 4 + 4 ];  // data word 0 LSB
    rr->data_buffer[ 1 ] = ctx->rec_data_buf[ 11 + 4 ];  // data word 1 MSB
    rr->data_buffer[ 1 ] <<= 8;
    rr->data_buffer[ 1 ] |= ctx->rec_data_buf[ 10 + 4 ]; // ...
    rr->data_buffer[ 1 ] <<= 8;
    rr->data_buffer[ 1 ] |= ctx->rec_data_buf[ 9 + 4 ];  // ...
    rr->data_buffer[ 1 ] <<= 8;
    rr->data_buffer[ 1 ] |= ctx->rec_data_buf[ 8 + 4 ];  // data word 1 LSB
    *rr->frs_type = ctx->rec_data_buf[ 13 + 4 ];         // frs report id MSB
    *rr->frs_type <<= 8;
    *rr->frs_type |= ctx->rec_data_buf[ 12 + 4 ];        // frs report id LSB
    
    //  returns no error (0) for successful operation
    return 0;
}

void smartdof_command_request ( smartdof_t *ctx, uint8_t command_type, uint8_t *command_parameters )
{
    uint8_t send_cmd_buf[ 16 ];
    uint8_t command_sequence_number = 0;

    send_cmd_buf[ 0 ]  = 0xF2; // command request report id
    send_cmd_buf[ 1 ]  = command_sequence_number; // command sequence number
    send_cmd_buf[ 2 ]  = command_type; // command to be sent
    
    if ( command_sequence_number < 255 ) 
    {
        command_sequence_number ++; // incrementing sequence number if less than 255
    }
    else 
    {
        command_sequence_number = 0; // if not less return to 0
    }

    send_cmd_buf[ 3 ]  = command_parameters[ 0 ]; // command parameter 0
    send_cmd_buf[ 4 ]  = command_parameters[ 1 ]; // command parameter 1
    send_cmd_buf[ 5 ]  = command_parameters[ 2 ]; // command parameter 2
    send_cmd_buf[ 6 ]  = command_parameters[ 3 ]; // command parameter 3
    send_cmd_buf[ 7 ]  = command_parameters[ 4 ]; // command parameter 4
    send_cmd_buf[ 8 ]  = command_parameters[ 5 ]; // command parameter 5
    send_cmd_buf[ 9 ]  = command_parameters[ 6 ]; // command parameter 6
    send_cmd_buf[ 10 ] = command_parameters[ 7 ]; // command parameter 7
    send_cmd_buf[ 11 ] = command_parameters[ 8 ]; // command parameter 8
    
    // sending these 12 bytes over control channel

    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 12, send_cmd_buf ); 
}

uint8_t smartdof_command_response ( smartdof_t *ctx, uint8_t *response_parameters )
{
    if ( smartdof_receive_packet( ctx, 1000000 ) == 1 ) 
    {
        return 1; // receives packet and returns error (1) if no packet is received
    }
    if ( ctx->data_len != 16 ) 
    {
        return 1; // checks if received data length is correct
    }
    if ( ctx->rec_data_buf[ 0 + 4 ] != 0xF1 ) 
    {
        return 1; // check if correct report id is received
    }

    response_parameters[ 0 ]  = ctx->rec_data_buf[ 5 + 4 ];  // command parameter 0
    response_parameters[ 1 ]  = ctx->rec_data_buf[ 6 + 4 ];  // command parameter 1
    response_parameters[ 2 ]  = ctx->rec_data_buf[ 7 + 4 ];  // command parameter 2
    response_parameters[ 3 ]  = ctx->rec_data_buf[ 8 + 4 ];  // command parameter 3
    response_parameters[ 4 ]  = ctx->rec_data_buf[ 9 + 4 ];  // command parameter 4
    response_parameters[ 5 ]  = ctx->rec_data_buf[ 10 + 4 ]; // command parameter 5
    response_parameters[ 6 ]  = ctx->rec_data_buf[ 11 + 4 ]; // command parameter 6
    response_parameters[ 7 ]  = ctx->rec_data_buf[ 12 + 4 ]; // command parameter 7
    response_parameters[ 8 ]  = ctx->rec_data_buf[ 13 + 4 ]; // command parameter 8
    response_parameters[ 9 ]  = ctx->rec_data_buf[ 14 + 4 ]; // command parameter 9
    response_parameters[ 10 ] = ctx->rec_data_buf[ 15 + 4 ]; // command parameter 10
    
    //  returns no error (0) for successful operation
    return 0;
}

void smartdof_get_feature_request ( smartdof_t *ctx, uint8_t feature_report_id )
{
    ctx->send_data_buf[ 0 ] = 0xFE; // get feature report id
    ctx->send_data_buf[ 1 ] = feature_report_id; // feature report id
    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 2, ctx->send_data_buf ); // sending these 2 bytes over control channel
}

void smartdof_set_feature_command ( smartdof_t *ctx, smartdof_sfc_t *sfc )
{
    ctx->send_data_buf[ 0 ]  = 0xFD;                                         // set feature command report id
    ctx->send_data_buf[ 1 ]  = sfc->feature_report_id;                       // feature report id
    ctx->send_data_buf[ 2 ]  = sfc->feature_flags;                           // feature flags
    ctx->send_data_buf[ 3 ]  = ( uint8_t )( sfc->change_sensitivity );       // change sensitivity (LSB)
    ctx->send_data_buf[ 4 ]  = ( uint8_t )( sfc->change_sensitivity >> 8 );  // change sensitivity (MSB)
    ctx->send_data_buf[ 5 ]  = ( sfc->report_interval >> 0 )  & 0xFF;        // report interval (LSB)
    ctx->send_data_buf[ 6 ]  = ( sfc->report_interval >> 8 )  & 0xFF;        // ...
    ctx->send_data_buf[ 7 ]  = ( sfc->report_interval >> 16 ) & 0xFF;        // ...
    ctx->send_data_buf[ 8 ]  = ( sfc->report_interval >> 24 ) & 0xFF;        // report interval (MSB)
    ctx->send_data_buf[ 9 ]  = ( sfc->batch_interval >> 0 )  & 0xFF;         // batch Interval (LSB)
    ctx->send_data_buf[ 10 ] = ( sfc->batch_interval >> 8 )  & 0xFF;         // ...
    ctx->send_data_buf[ 11 ] = ( sfc->batch_interval >> 16 ) & 0xFF;         // ...
    ctx->send_data_buf[ 12 ] = ( sfc->batch_interval >> 24 ) & 0xFF;         // batch Interval (MSB)
    ctx->send_data_buf[ 13 ] = ( sfc->sensor_specific_config >> 0 )  & 0xFF; // sensor-specific config (LSB)
    ctx->send_data_buf[ 14 ] = ( sfc->sensor_specific_config >> 8 )  & 0xFF; // ...
    ctx->send_data_buf[ 15 ] = ( sfc->sensor_specific_config >> 16 ) & 0xFF; // ...
    ctx->send_data_buf[ 16 ] = ( sfc->sensor_specific_config >> 24 ) & 0xFF; // sensor-specific config (MSB)

    // sending these 17 bytes over control channel
    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 17, ctx->send_data_buf );
}

uint8_t smartdof_get_feature_response ( smartdof_t *ctx, smartdof_sfc_t *sfc )
{
    if ( smartdof_receive_packet( ctx, 1000000 ) == 1 ) 
    {
        return 1; // receives packet and returns error (1) if no packet is received
    }
    if ( ctx->data_len != 17 ) 
    {
        return 1; // checks if received data length is correct
    }
    if ( ctx->rec_data_buf[ 0 + 4 ] != 0xFC ) 
    {
        return 1; // check if correct report id is received
    }

    //  parsing data

    sfc->feature_report_id = ctx->rec_data_buf[ 1 + 4 ];        // feature report id
    sfc->feature_flags = ctx->rec_data_buf[ 2 + 4 ];
    sfc->change_sensitivity = ctx->rec_data_buf[ 4 + 4 ];       // change sensitivity MSB
    sfc->change_sensitivity <<= 8;
    sfc->change_sensitivity |= ctx->rec_data_buf[ 3 + 4 ];      // change sensitivity LSB
    sfc->report_interval = ctx->rec_data_buf[ 8 + 4 ];          // report interval MSB
    sfc->report_interval <<= 8;
    sfc->report_interval |= ctx->rec_data_buf[ 7 + 4 ];         // ...
    sfc->report_interval <<= 8;
    sfc->report_interval |= ctx->rec_data_buf[ 6 + 4 ];         // ...
    sfc->report_interval <<= 8;
    sfc->report_interval |= ctx->rec_data_buf[ 5 + 4 ];         // report interval LSB
    sfc->batch_interval = ctx->rec_data_buf[ 12 + 4 ];          // batch interval MSB
    sfc->batch_interval <<= 8;
    sfc->batch_interval |= ctx->rec_data_buf[ 11 + 4 ];         // ...
    sfc->batch_interval <<= 8;
    sfc->batch_interval |= ctx->rec_data_buf[ 10 + 4 ];         // ...
    sfc->batch_interval <<= 8;
    sfc->batch_interval |= ctx->rec_data_buf[ 9 + 4 ];          // batch interval LSB
    sfc->sensor_specific_config = ctx->rec_data_buf[ 16 + 4 ];  // sensor specific configuration MSB
    sfc->sensor_specific_config <<= 8;
    sfc->sensor_specific_config |= ctx->rec_data_buf[ 15 + 4 ]; // ...
    sfc->sensor_specific_config <<= 8;
    sfc->sensor_specific_config |= ctx->rec_data_buf[ 14 + 4 ]; // ...
    sfc->sensor_specific_config <<= 8;
    sfc->sensor_specific_config |= ctx->rec_data_buf[ 13 + 4 ]; // sensor specific configuration MSB

    //  returns no error (0) for successful operation
    return 0;
}

void smartdof_force_sensor_flush ( smartdof_t *ctx, uint8_t sensor_id )
{
    ctx->send_data_buf[ 0 ] = 0xF0; // force sensor flush report id
    ctx->send_data_buf[ 1 ] = sensor_id; // sensor id - feature id of a sensor to be flushed
    smartdof_send_packet( ctx, SMARTDOF_CHAN_CTRL, 2, ctx->send_data_buf ); // sending these 2 bytes over control channel
}

uint8_t smartdof_flush_completed ( smartdof_t *ctx, uint8_t * sensor_id )
{
    if ( smartdof_receive_packet( ctx, 1000000 ) == 1 ) 
    {
        return 1; // receives packet and returns error (1) if no packet is received
    }
    if ( ctx->data_len != 2 ) 
    {
        return 1; // checks if received data length is correct
    }
    if ( ctx->rec_data_buf[ 0 + 4 ] != 0xEF ) 
    {
        return 1; // check if correct report id is received
    }

    // sensor id - feature id of a flushed sensor
    *sensor_id = ctx->rec_data_buf[ 1 + 4 ];

    //  returns no error (0) for successful operation
    return 0;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void smartdof_erase_buffer ( uint8_t *erase_buffer, uint16_t buffer_size )
{
    uint16_t i;
    
    for ( i = 0; i < buffer_size; i ++ )
    {
        erase_buffer[ i ] = 0x00;
    }
}

// ------------------------------------------------------------------------- END


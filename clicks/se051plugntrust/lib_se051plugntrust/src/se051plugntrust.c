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
 * @file se051plugntrust.c
 * @brief SE051 Plug n Trust Click Driver.
 */

#include "se051plugntrust.h"

/**
 * @brief Communication data objects
 * @details Data objects that driver uses through most 
 *          of the functions to communicate with device.
 */
static se051plugntrust_apdu_t apdu_data;
static se051plugntrust_frame_data_t frame_data;

/**
 * @brief Calculates CRC.
 * @details Goes through @b crc_buff and returns calculated CRC.
 * @param[in] apdu_data : APDU object.
 * See se051plugntrust_apdu_t object definition for detailed explanation.
 * @param[in] crc_buff : Data to calculate crc from.
 * @param[in] length : Length of crc_buff.
 * @return CRC data.
 * @note None.
 */
static uint16_t se051plugntrust_create_crc ( uint8_t *crc_buff, uint16_t length );

void se051plugntrust_cfg_setup ( se051plugntrust_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = SE051PLUGNTRUST_DEVICE_ADDRESS;
}

err_t se051plugntrust_init ( se051plugntrust_t *ctx, se051plugntrust_cfg_t *cfg ) 
{
    frame_data.apdu = &apdu_data;
    
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

err_t se051plugntrust_apdu_write ( se051plugntrust_t *ctx, se051plugntrust_frame_data_t *frame_data ) 
{
    uint8_t data_buf[ 0xFF ] = { 0 };
    volatile uint8_t cnt = 3;
    data_buf[ 0 ] = SE051PLUGNTRUST_NAD_WRITE; // set NAD
    data_buf[ 1 ] = frame_data->pcb; // set PCB
    data_buf[ 2 ] = frame_data->len; // set APDU len
    // if APDU exists
    if ( frame_data->len > 0 )
    {
        data_buf[ cnt++ ] = frame_data->apdu->cla; // set CLA
        data_buf[ cnt++ ] = frame_data->apdu->ins; // set INS
        data_buf[ cnt++ ] = frame_data->apdu->p1; // set P1
        data_buf[ cnt++ ] = frame_data->apdu->p2; // set P2
        if ( frame_data->apdu->payload_len > 0 )
        {
            if ( frame_data->apdu->payload_len < frame_data->len )
            {
                data_buf[ cnt++ ] = frame_data->apdu->payload_len; // set payload len
            }
            for ( uint8_t i = 0; i < frame_data->apdu->payload_len; i++ )
            {
                data_buf[ cnt++ ] = frame_data->apdu->payload[ i ]; // set payload data
            }
        }
        // set rsp data request if APDU len is missing one byte
        if ( ( frame_data->apdu->rsp_len <= 0 ) && ( frame_data->len > ( cnt - 3 ) ) )
        {
            data_buf[ cnt++ ] = 0;
        }
        else if ( ( frame_data->apdu->rsp_len > 0 ) && ( frame_data->len > ( cnt - 3 ) ) )
        {
            data_buf[ cnt++ ] = frame_data->apdu->rsp_len;
        }
    }
    // calculate and set CRC data
    frame_data->crc16 = se051plugntrust_create_crc( data_buf, ( data_buf[ 2 ] + 3 ) );
    data_buf[ cnt++ ] = ( uint8_t ) ( frame_data->crc16 >> 8 );
    data_buf[ cnt++ ] = ( uint8_t ) frame_data->crc16;
    // check if data buf is overflown
    if ( cnt > 0xFF )
    {
        return SE051PLUGNTRUST_ERROR_DATA_OVF;
    }
    // send data to device
    uint16_t timeout_cnt = 0;
    while ( timeout_cnt++ < 100 )
    {
        if ( I2C_MASTER_SUCCESS == i2c_master_write( &ctx->i2c, data_buf, cnt ) )
        {
            Delay_100ms();
            return SE051PLUGNTRUST_OK;
        }
        Delay_100ms( );
    }
    return SE051PLUGNTRUST_ERROR_TIMEOUT;
}

err_t se051plugntrust_apdu_read ( se051plugntrust_t *ctx, se051plugntrust_frame_data_t *frame_data )
{
    uint8_t temp_buf[ 0xFF ] = { 0 };
    // read 3 bytes NAD,PCB, APDU length
    while ( I2C_MASTER_SUCCESS != i2c_master_read( &ctx->i2c, temp_buf, 3 ) )
    {
        Delay_1ms( );
    }
    frame_data->nad = temp_buf[ 0 ];
    frame_data->pcb = temp_buf[ 1 ];
    frame_data->len = temp_buf[ 2 ];
    frame_data->apdu->payload_len = frame_data->len;
    
    err_t error_flag;
    // read APDU
    if ( frame_data->len > 0 )
    {
        memset( frame_data->apdu->payload, 0, 0xFF ); // clear APDU payload
        // read APDU and CRC data
        error_flag = i2c_master_read( &ctx->i2c, temp_buf, frame_data->len + 2 );
        // copy read data to payload
        memcpy( frame_data->apdu->payload, temp_buf, frame_data->len );
        // set CRC
        frame_data->crc16 = ( ( uint16_t ) temp_buf[ frame_data->len ] << 8 ) | 
                            ( uint16_t ) temp_buf[ frame_data->len + 1 ];
        // set APDU status if information block is read
        if ( ( frame_data->pcb & SE051PLUGNTRUST_PCB_BLOCK_S ) != SE051PLUGNTRUST_PCB_BLOCK_S )
        {
            frame_data->apdu->status = ( temp_buf[ frame_data->apdu->payload_len - 2 ] << 8 ) | 
                                         temp_buf[ frame_data->apdu->payload_len - 1 ];
        }
    }
    else
    {
        error_flag = i2c_master_read( &ctx->i2c, temp_buf, 2 ); // read CRC
        frame_data->crc16 = ( ( uint16_t ) temp_buf[ 0 ] << 8 ) | ( uint16_t ) temp_buf[ 1 ];
    }
    Delay_100ms( );
    return error_flag;
}

err_t se051plugntrust_apdu_transfer ( se051plugntrust_t *ctx, se051plugntrust_frame_data_t *frame_data )
{
    if ( SE051PLUGNTRUST_OK != se051plugntrust_apdu_write( ctx, frame_data ) )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    Delay_10ms ( );
    Delay_10ms ( );
    return se051plugntrust_apdu_read( ctx, frame_data );
}

void se051plugntrust_set_en_pin ( se051plugntrust_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

void se051plugntrust_set_rst_pin ( se051plugntrust_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void se051plugntrust_reset ( se051plugntrust_t *ctx )
{
    if ( SE051PLUGNTRUST_INTERFACE_I2C == ctx->interface )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

//----------------------------------------------------------------------------------TLV

void se051plugntrust_set_tlv_u8 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t value )
{
    const size_t size_of_tlv = 1 + 1 + 1;
    uint8_t *p_buf = buf + *buf_len;
    *( p_buf++ ) = tag; // added tlv tag
    *( p_buf++ ) = 1; // added tlv len
    *( p_buf++ ) = value; // added tlv value
    *( buf_len ) += size_of_tlv; // added payload buf
}

void se051plugntrust_set_tlv_u16 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint16_t value )
{
    const size_t size_of_tlv = 1 + 1 + 2;
    uint8_t *p_buf = buf + *buf_len;
    *( p_buf++ ) = tag; // added tlv tag
    *( p_buf++ ) = 2; // added tlv len
    *( p_buf++ ) = ( uint8_t ) ( value >> 8 ); // added tlv value
    *( p_buf++ ) = ( uint8_t ) value; // added tlv value
    *( buf_len ) += size_of_tlv; // added payload buf
}

void se051plugntrust_set_tlv_u16_optional ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint16_t value )
{
    if ( value )
    {
        se051plugntrust_set_tlv_u16( buf, buf_len, tag, value );
    }
}

void se051plugntrust_set_tlv_u32 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint32_t value )
{
    const size_t size_of_tlv = 1 + 1 + 4;
    uint8_t *p_buf = buf + *buf_len;
    *( p_buf++ ) = tag; // added tlv tag
    *( p_buf++ ) = 4; // added tlv len
    *( p_buf++ ) = ( uint8_t )( value >> 24 ); // added tlv value
    *( p_buf++ ) = ( uint8_t )( value >> 16 ); // added tlv value
    *( p_buf++ ) = ( uint8_t )( value >> 8 ); // added tlv value
    *( p_buf++ ) = ( uint8_t )value; // added tlv value
    *( buf_len ) += size_of_tlv; // added payload buf
}

err_t se051plugntrust_set_tlv_u8buf ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t *cmd, uint32_t cmd_len )
{
    const size_t size_of_length = ( ( cmd_len <= 0x7F ) ? 1 : ( ( cmd_len <= 0xFF ) ? 2 : 3 ) ); // check cmd
    const size_t size_of_tlv = 1 + size_of_length + cmd_len;
    
    uint8_t *p_buf = buf + *buf_len;
    // set TLV tag
    *( p_buf++ ) = tag; // added tlv tag
    // set TLV length
    if ( cmd_len <= 0x7F ) 
    {
        *( p_buf++ ) = ( uint8_t ) cmd_len;
    }
    else if ( cmd_len <= 0xFF ) 
    {
        *( p_buf++ ) = ( uint8_t ) ( 0x80 /* Extended */ | 0x01 /* Additional Length */ );
        *( p_buf++ ) = ( uint8_t ) ( cmd_len & 0xFF );
    }
    else if ( cmd_len <= 0xFFFFu ) 
    {
        *( p_buf++ ) = ( uint8_t ) ( 0x80 /* Extended */ | 0x02 /* Additional Length */ );
        *( p_buf++ ) = ( uint8_t ) ( ( cmd_len >> 8 ) & 0xFF );
        *( p_buf++ ) = ( uint8_t ) ( cmd_len & 0xFF );
    }
    else
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // set TLV data
    if ( cmd_len ) 
    {
        while ( cmd_len-- > 0 ) 
        {
            *( p_buf++ ) = *( cmd++ );
        }
    }
    // increment payload size
    *( buf_len ) += size_of_tlv;
    
    return SE051PLUGNTRUST_OK;
}

err_t se051plugntrust_set_tlv_u8buf_optional ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t *cmd, uint32_t cmd_len )
{
    if ( cmd_len )
    {
        return se051plugntrust_set_tlv_u8buf( buf, buf_len, tag, cmd, cmd_len );
    }
    else
    {
        return SE051PLUGNTRUST_OK;
    }
}

err_t se051plugntrust_get_tlv_u8 ( uint8_t *buf, uint32_t *buf_index, uint8_t tag, uint8_t *rsp )
{
    uint8_t *pbuf = buf + ( *buf_index );
    uint32_t rsp_len;
    // check if tag is ok
    if ( *pbuf++ != tag )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // check if rsp i greater then 1 byte of data
    rsp_len = *pbuf++;
    if ( rsp_len > 1 )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // set rsp and index
    *rsp = *pbuf;
    *buf_index += ( 1 + 1 + ( rsp_len ) );
    buf += ( 1 + 1 + ( rsp_len ) );
    return SE051PLUGNTRUST_OK;
}

err_t se051plugntrust_get_tlv_u16 ( uint8_t *buf, uint32_t *buf_index, uint8_t tag, uint16_t *rsp )
{
    uint8_t *pbuf = buf + ( *buf_index );
    uint32_t rsp_len;
    // check tag
    if ( *pbuf++ != tag )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // check if response is greater then 2 bytes
    rsp_len = *pbuf++;
    if ( rsp_len > 2 )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // set rsp;
    *rsp = ( *pbuf++ ) << 8;
    *rsp |= *pbuf++;
    *buf_index += ( 1 + 1 + ( rsp_len ) );
    buf += ( 1 + 1 + ( rsp_len ) );
    return SE051PLUGNTRUST_OK;
}

err_t se051plugntrust_get_tlv_u8buf ( uint8_t *buf, uint32_t *buf_index, uint8_t buf_len, 
                                      uint8_t tag, uint8_t *rsp, uint32_t *rsp_len )
{
    uint8_t *pbuf = buf + (*buf_index);
    uint32_t extended_len;
    uint32_t rsplen;
    // check tag
    if ( *pbuf++ != tag )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // check size
    rsplen = *pbuf++;
    if ( rsplen <= 0x7FU ) 
    {
        extended_len = rsplen;
        *buf_index += ( 1 + 1 );
    }
    else if ( 0x81 == rsplen ) 
    {
        extended_len = *pbuf++;
        *buf_index += ( 1 + 1 + 1 );
    }
    else if ( 0x82 == rsplen ) 
    {
        extended_len = *pbuf++;
        extended_len = ( extended_len << 8 ) | *pbuf++;
        *buf_index += ( 1 + 1 + 2 );
    }
    else 
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // check ovf
    if ( extended_len > ( *rsp_len ) )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    if ( extended_len > buf_len )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // set rsp len, index, and rs data
    *rsp_len = extended_len;
    *buf_index += extended_len;
    while ( extended_len-- > 0 ) 
    {
        *rsp++ = *pbuf++;
    }
    return SE051PLUGNTRUST_OK;
}

uint8_t se051plugntrust_calculate_apdu_size ( se051plugntrust_apdu_t *apdu_data )
{
    uint8_t size = 4;
    if ( apdu_data->payload_len > 0 )
    {
        size++;
        size += apdu_data->payload_len;
    }
    if ( apdu_data->rsp_len > 0 )
    {
        size ++;
    }
    return size;
}

err_t se051plugntrust_end_apdu_session ( se051plugntrust_t *ctx )
{ 
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_S | SE051PLUGNTRUST_PCB_BLOCK_S_END_APDU_SESSION_REQ;
    frame_data.len = 0;
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // check if apdu session is ended
    if ( ( SE051PLUGNTRUST_PCB_BLOCK_S | SE051PLUGNTRUST_PCB_BLOCK_S_END_APDU_SESSION_RSP ) == frame_data.pcb )
    {
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_object_id_list ( se051plugntrust_t *ctx, uint32_t *id_list, uint8_t *list_len )
{
    *list_len = 0;
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_READ;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_LIST;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    frame_data.len = 0;
    // offset->no offset
    se051plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, 0 );
    // filter type->no filter, list all objects
    se051plugntrust_set_tlv_u8( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                SE051PLUGNTRUST_TLV_TAG_2, 0xFF );
    // calculate apdu size
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    // request resposne data[LE]
    frame_data.len++;
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // check APDU status
    if ( SE051PLUGNTRUST_SW_NOERROR != frame_data.apdu->status )
    {
        return SE051PLUGNTRUST_ERROR;
    }
    // parse data
    uint8_t parse_data[ 0xFF ] = { 0 };
    uint32_t parse_len;
    uint8_t more;
    uint32_t parse_index;
    uint8_t id_len = 0;
    parse_len = 0xFF;
    more = 0;
    parse_index = 0;
    // check more indicator data
    if ( SE051PLUGNTRUST_OK != se051plugntrust_get_tlv_u8( frame_data.apdu->payload, &parse_index, 
                                                           SE051PLUGNTRUST_TLV_TAG_1, &more ) )
    {
        se051plugntrust_end_apdu_session( ctx );
        return SE051PLUGNTRUST_ERROR;
    }
    // format and set object ID's in array
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, 
                                                              SE051PLUGNTRUST_TLV_TAG_2, parse_data, &parse_len ) )
    {
        parse_index = 0;
        for ( uint8_t i = 0; i < parse_len; i++ )
        {
            if ( ( !( i % 4 ) ) && ( i > 0 ) )
            {
                id_list[ id_len++ ] = parse_index;
                parse_index = 0;
            }
            parse_index |=  ( uint32_t )( parse_data[ i ] ) << ( 8 * ( 3 - ( i % 4 ) ) );
        }
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx );
        return SE051PLUGNTRUST_ERROR;
    }
    *list_len = id_len;
    se051plugntrust_end_apdu_session( ctx );
    return SE051PLUGNTRUST_OK;
}

err_t se051plugntrust_sw_reset ( se051plugntrust_t *ctx, se051plugntrust_atr_t *atr_data )
{    
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_S | SE051PLUGNTRUST_PCB_BLOCK_S_SOFT_RESET_REQ;
    frame_data.len = 0;
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // check if atr data is valid and copy it if atr_data object is provided
    if ( sizeof( se051plugntrust_atr_t ) == frame_data.len )
    {
        if ( 0 != atr_data )
        {
            memcpy( ( uint8_t * ) atr_data, frame_data.apdu->payload, frame_data.len );
        }
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_select_applet ( se051plugntrust_t *ctx, uint8_t ns_encode, se051plugntrust_version_info_t *ver_info )
{   
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I | ns_encode;
    frame_data.len = 0x15;
    frame_data.apdu->cla = 0;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT | SE051PLUGNTRUST_INS_TRANSIENT | SE051PLUGNTRUST_INS_ATTEST;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DES;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 16;
    uint8_t aid[ 16 ] = { 0xA0, 0x00, 0x00, 0x03, 0x96, 0x54, 0x53, 0x00, 
                          0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 };
    memcpy( frame_data.apdu->payload, aid, 16 );
    frame_data.apdu->rsp_len = 0;
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // Check if APDU status and inputs ver_info data if provided.
    if ( SE051PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        if ( ver_info )
        {
            ver_info->major_version = frame_data.apdu->payload[ 0 ];
            ver_info->minor_version = frame_data.apdu->payload[ 1 ];
            ver_info->patch_version = frame_data.apdu->payload[ 2 ];
            ver_info->applet_config = ( frame_data.apdu->payload[ 3 ] << 8 ) | frame_data.apdu->payload[ 4 ];
            ver_info->secure_box = (  frame_data.apdu->payload[ 5 ] << 8 ) | frame_data.apdu->payload[ 6 ];
        }
        else 
        {
            return SE051PLUGNTRUST_ERROR;
        }
        
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_get_free_memory ( se051plugntrust_t *ctx, uint8_t memory_type, uint16_t *free_memory )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_MEMORY;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0 , sizeof(frame_data.apdu->payload) );
    // set type memory to request
    se051plugntrust_set_tlv_u8( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                SE051PLUGNTRUST_TLV_TAG_1, memory_type );
    // calculate APDU data size
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // prase
    uint32_t parse_index = 0;
    *free_memory = 0;
    // set free_memory value
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u16( frame_data.apdu->payload, &parse_index, 
                                                            SE051PLUGNTRUST_TLV_TAG_1, free_memory ) )
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_get_random_numbers ( se051plugntrust_t *ctx, uint8_t *random_buf, uint8_t buf_len )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_RANDOM;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0 , sizeof(frame_data.apdu->payload) );
    // set number of random bytes to request
    se051plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, buf_len );
    // calculate APDU size
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    // set rsp_len request data
    frame_data.len++;
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // parse
    uint32_t parse_len = buf_len;
    uint32_t parse_index = 0;
    // input random data in object
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, 
                                                              SE051PLUGNTRUST_TLV_TAG_1, random_buf, &parse_len ) )
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_check_object_exist ( se051plugntrust_t *ctx, uint32_t object_id )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_EXIST;
    frame_data.apdu->payload_len = 0;
    // set object ID
    se051plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, object_id );
    // calculate APDU size
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // parse
    uint32_t parse_index = 0;
    uint8_t obj_exists = 0;
    // check rsp if object exists
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u8( frame_data.apdu->payload, &parse_index, 
                                                           SE051PLUGNTRUST_TLV_TAG_1, &obj_exists ) )
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return obj_exists;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_delete_object ( se051plugntrust_t *ctx, uint32_t object_id )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_DELETE_OBJECT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0, sizeof ( frame_data.apdu->payload ) );
    // object to delete
    se051plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, object_id );
    // calculate APDU
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    se051plugntrust_apdu_transfer( ctx, &frame_data ); 
    // check status
    if ( SE051PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_select_card_manager ( se051plugntrust_t *ctx, uint8_t rsp, 
                                            uint8_t *cardmanager_rsp, uint8_t *cardmanager_rsp_len )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.len = 4 + rsp;
    frame_data.apdu->cla = 0;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT | SE051PLUGNTRUST_INS_TRANSIENT | SE051PLUGNTRUST_INS_ATTEST;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DES;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // if rsp copy data to output buffer
    if ( rsp )
    {
        memcpy( cardmanager_rsp, frame_data.apdu->payload, frame_data.apdu->payload_len );
        *cardmanager_rsp_len = frame_data.apdu->payload_len;
    }
    // check status
    if ( SE051PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_read_object ( se051plugntrust_t *ctx, uint32_t object_id, uint16_t offset, 
                                    uint16_t read_len, uint8_t *data_buf, uint32_t *data_len )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_READ;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0, sizeof ( frame_data.apdu->payload ) );
    // set object ID
    se051plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, object_id );
    // set read offset
    se051plugntrust_set_tlv_u16_optional( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                          SE051PLUGNTRUST_TLV_TAG_2, offset );
    // limit read length(0 if you want to read everything)
    se051plugntrust_set_tlv_u16_optional( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                          SE051PLUGNTRUST_TLV_TAG_3, read_len );
    // calculate APDU
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    // request rsp data
    frame_data.len++;
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // parse
    uint32_t parse_index = 0;
    // set read data to output buffer
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, 
                                                              SE051PLUGNTRUST_TLV_TAG_1, data_buf, data_len ) )
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_write_binary_object ( se051plugntrust_t *ctx, uint32_t object_id, uint16_t offset, 
                                            uint16_t data_len, uint8_t *data_buf )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_WRITE;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_BINARY;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    frame_data.len = 0;
    // object ID
    se051plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, object_id );
    // write offeset
    se051plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_2, offset );
    // bytes to write
    se051plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_3, data_len );
    // data bytes
    se051plugntrust_set_tlv_u8buf( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                   SE051PLUGNTRUST_TLV_TAG_4, data_buf, ( uint32_t ) data_len );
    // calculate APDU size
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    // check status
    if ( SE051PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

err_t se051plugntrust_get_applet_info ( se051plugntrust_t *ctx, se051plugntrust_version_info_t *ver_info )
{
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_VERSION;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0x09;
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu );
    se051plugntrust_apdu_transfer( ctx, &frame_data );
    uint32_t parse_index = 0;
    uint32_t parse_len = 0xA;
    uint8_t prase_buf[ 0xA ] = { 0 };
    // check APDU size
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, 
                                                              SE051PLUGNTRUST_TLV_TAG_1, prase_buf, &parse_len ) )
    {
        ver_info->major_version = prase_buf[ 0 ];
        ver_info->minor_version = prase_buf[ 1 ];
        ver_info->patch_version = prase_buf[ 2 ];
        ver_info->applet_config = ( prase_buf[ 3 ] << 8 ) | prase_buf[ 4 ];
        ver_info->secure_box = (  prase_buf[ 5 ] << 8 ) | prase_buf[ 6 ];
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_OK;
    }
    else
    {
        se051plugntrust_end_apdu_session( ctx ); 
        return SE051PLUGNTRUST_ERROR;
    }
}

static uint16_t se051plugntrust_create_crc ( uint8_t *crc_buff, uint16_t length )
{
    uint16_t crc16 = 0xFFFF;
    int8_t bit_idx;
    uint8_t new_byte[ 2 ] = { 0 };
    if ( NULL == crc_buff )
    {
        return crc16;
    }
    for ( uint16_t i = 0; i < length; i++ )
    {
        crc16 ^= crc_buff[ i ];
        for ( bit_idx = 8; bit_idx > 0; --bit_idx )
        {
            if ( 0x0001 == ( crc16 & 0x0001 ) )
            {
                crc16 = ( crc16 >> 1 ) ^ 0x8408;
            }
            else
            {
                crc16 >>= 1;
            }
        }
    }
    crc16 ^= 0xFFFF;
    new_byte[ 0 ] = crc16 & 0xFF;
    new_byte[ 1 ] = ( crc16 >> 8 ) & 0xFF;
    crc16 = ( new_byte[ 0 ] << 8 ) | new_byte[ 1 ];
    return crc16;
}

// ------------------------------------------------------------------------- END

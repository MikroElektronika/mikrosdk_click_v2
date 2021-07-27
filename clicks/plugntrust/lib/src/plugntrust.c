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
 * @file plugntrust.c
 * @brief Plug n Trust Click Driver.
 */

#include "plugntrust.h"

/**
 * @brief Communication data objects
 * @details Data objects that driver uses through most 
 *          of the functions to communicate with device.
 */
static plugntrust_apdu_t apdu_data;
static plugntrust_frame_data_t frame_data;

/**
 * @brief Calculates CRC.
 * @details Goes through @b crc_buff and returns calculated CRC.
 * @param[in] apdu_data : APDU object.
 * See plugntrust_apdu_t object definition for detailed explanation.
 * @param[in] crc_buff : Data to calculate crc from.
 * @param[in] length : Length of crc_buff.
 * @return CRC data.
 * @note None.
 */
static uint16_t plugntrust_create_crc ( uint8_t *crc_buff, uint16_t length );

void plugntrust_cfg_setup ( plugntrust_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = PLUGNTRUST_SET_DEV_ADDR;
}

err_t plugntrust_init ( plugntrust_t *ctx, plugntrust_cfg_t *cfg ) 
{
    frame_data.apdu = &apdu_data;
    
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->rst, cfg->rst );
    
    ctx->i2c_timeout = 1000;
    
    return I2C_MASTER_SUCCESS;
}

err_t plugntrust_default_cfg ( plugntrust_t *ctx ) 
{
    ctx->interface = PLUGNTRUST_INTERFACE_I2C;
    
    plugntrust_reset( ctx );
    
    return PLUGNTRUST_OK;
}

err_t plugntrust_apdu_write ( plugntrust_t *ctx, plugntrust_frame_data_t *frame_data ) 
{
    uint8_t data_buf[ 0xFF ] = { 0 };
    volatile uint8_t cnt = 3;
    data_buf[ 0 ] = PLUGNTRUST_NAD_WRITE;//set NAD
    data_buf[ 1 ] = frame_data->pcb;//set PCB
    data_buf[ 2 ] = frame_data->len;//set APDU len
    //if APDU exists
    if ( frame_data->len > 0 )
    {
        data_buf[ cnt++ ] = frame_data->apdu->cla;//set CLA
        data_buf[ cnt++ ] = frame_data->apdu->ins;//set INS
        data_buf[ cnt++ ] = frame_data->apdu->p1;//set P1
        data_buf[ cnt++ ] = frame_data->apdu->p2;//set P2
        if ( frame_data->apdu->payload_len > 0 )
        {
            if ( frame_data->apdu->payload_len < frame_data->len )
            {
                data_buf[ cnt++ ] = frame_data->apdu->payload_len;//set payload len
            }
            for ( uint8_t i = 0; i < frame_data->apdu->payload_len; i++ )
            {
                data_buf[ cnt++ ] = frame_data->apdu->payload[ i ];//set payload data
            }
        }
        //set rsp data request if APDU len is missing one byte
        if ( ( frame_data->apdu->rsp_len <= 0 ) && ( frame_data->len > ( cnt - 3 ) ) )
        {
            data_buf[ cnt++ ] = 0;
        }
        else if ( ( frame_data->apdu->rsp_len > 0 ) && ( frame_data->len > ( cnt - 3 ) ) )
        {
            data_buf[ cnt++ ] = frame_data->apdu->rsp_len;
        }
    }
    //calculate and set CRC data
    frame_data->crc16 = plugntrust_create_crc( data_buf, ( data_buf[ 2 ] + 3 ) );
    data_buf[ cnt++ ] = ( uint8_t )( frame_data->crc16 >> 8 );
    data_buf[ cnt++ ] = ( uint8_t )frame_data->crc16;
    //check if data buf is overflown
    if ( cnt > 0xFF )
    {
        return PLUGNTRUST_ERROR_DATA_OVF;
    }
    //send data to device
    uint16_t timeout_cnt = ctx->i2c_timeout;
    while ( timeout_cnt-- )
    {
        if ( i2c_master_write( &ctx->i2c, data_buf, cnt ) >= I2C_MASTER_SUCCESS )
        {
            Delay_100ms();
            return PLUGNTRUST_OK;
        }
        Delay_100ms();
    }
    return PLUGNTRUST_ERROR_TIMEOUT;
}

err_t plugntrust_apdu_read ( plugntrust_t *ctx, plugntrust_frame_data_t *frame_data )
{
    uint8_t temp_buf[ 0xFF ] = { 0 };
    uint16_t ret_status = 0;
    //read 3 bytes NAD,PCB, APDU length
    while ( i2c_master_read( &ctx->i2c, temp_buf, 3 ) < I2C_MASTER_SUCCESS )
    {
        Delay_1ms( );
    }
    frame_data->nad = temp_buf[ 0 ];
    frame_data->pcb = temp_buf[ 1 ];
    frame_data->len = temp_buf[ 2 ];
    frame_data->apdu->payload_len = frame_data->len;
    
    err_t error_flag;
    //read APDU
    if ( frame_data->len > 0 )
    {
        memset( frame_data->apdu->payload, 0, 0xFF );//clear APDU payload
        //read APDU and CRC data
        error_flag = i2c_master_read( &ctx->i2c, temp_buf, frame_data->len + 2 );
        //copy read data to payload
        memcpy( frame_data->apdu->payload, temp_buf, frame_data->len );
        //set CRC
        frame_data->crc16 = ( ( uint16_t )( temp_buf[ frame_data->len ] << 8 ) | 
                              ( uint16_t )temp_buf[ frame_data->len + 1 ] );
        //set APDU status if information block is read
        if ( ( frame_data->pcb & PLUGNTRUST_PCB_BLOCK_S ) != PLUGNTRUST_PCB_BLOCK_S )
        {
            frame_data->apdu->status = ( temp_buf[ frame_data->apdu->payload_len - 2 ] << 8 ) | 
                                         temp_buf[ frame_data->apdu->payload_len - 1 ];
        }
    }
    else
    {
        error_flag = i2c_master_read( &ctx->i2c, temp_buf, 2 );//read CRC
        frame_data->crc16 = ( ( uint16_t )( temp_buf[ 0 ] << 8 ) | ( uint16_t )temp_buf[ 1 ] );
    }
    
    Delay_100ms( );
    
    return error_flag;
}

err_t plugntrust_apdu_transfer ( plugntrust_t *ctx, plugntrust_frame_data_t *frame_data )
{
    if (plugntrust_apdu_write( ctx, frame_data ) != PLUGNTRUST_OK )
    {
        return PLUGNTRUST_ERROR;
    }
    return plugntrust_apdu_read( ctx, frame_data );
}

void plugntrust_set_en ( plugntrust_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

void plugntrust_set_rst ( plugntrust_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void plugntrust_reset ( plugntrust_t *ctx )
{
    if ( PLUGNTRUST_INTERFACE_I2C == ctx->interface )
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


void plugntrust_set_tlv_u8 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t value )
{
    const size_t size_of_tlv = 1 + 1 + 1;
    uint8_t *p_buf = buf + *buf_len;
    *( p_buf++ ) = tag;//added tlv tag
    *( p_buf++ ) = 1;//added tlv len
    *( p_buf++ ) = value;//added tlv value
    *( buf_len ) += size_of_tlv;//added payload buf
}

void plugntrust_set_tlv_u16 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint16_t value )
{
    const size_t size_of_tlv = 1 + 1 + 2;
    uint8_t *p_buf = buf + *buf_len;
    *( p_buf++ ) = tag;//added tlv tag
    *( p_buf++ ) = 2;//added tlv len
    *( p_buf++ ) = ( uint8_t )( value >> 8 );//added tlv value
    *( p_buf++ ) = ( uint8_t )value;//added tlv value
    *( buf_len ) += size_of_tlv;//added payload buf
}

void plugntrust_set_tlv_u16_optional ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint16_t value )
{
    if ( value )
    {
        plugntrust_set_tlv_u16( buf, buf_len, tag, value );
    }
}

void plugntrust_set_tlv_u32 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint32_t value )
{
    const size_t size_of_tlv = 1 + 1 + 4;
    uint8_t *p_buf = buf + *buf_len;
    *( p_buf++ ) = tag;//added tlv tag
    *( p_buf++ ) = 4;//added tlv len
    *( p_buf++ ) = ( uint8_t )( value >> 24 );//added tlv value
    *( p_buf++ ) = ( uint8_t )( value >> 16 );//added tlv value
    *( p_buf++ ) = ( uint8_t )( value >> 8 );//added tlv value
    *( p_buf++ ) = ( uint8_t )value;//added tlv value
    *( buf_len ) += size_of_tlv;//added payload buf
}

err_t plugntrust_set_tlv_u8buf ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t *cmd, uint32_t cmd_len )
{
    const size_t size_of_length = ( cmd_len <= 0x7f ? 1 : ( cmd_len <= 0xFf ? 2 : 3 ) );//check cmd
    const size_t size_of_tlv = 1 + size_of_length + cmd_len;
    
    uint8_t *p_buf = buf + *buf_len;
    //set TLV tag
    *( p_buf++ ) = tag;//added tlv tag
    //set TLV length
    if ( cmd_len <= 0x7F ) 
    {
        *( p_buf++ ) = ( uint8_t )cmd_len;
    }
    else if ( cmd_len <= 0xFF ) 
    {
        *( p_buf++ ) = ( uint8_t )( 0x80 /* Extended */ | 0x01 /* Additional Length */ );
        *( p_buf++ ) = ( uint8_t )( ( cmd_len >> 0 * 8 ) & 0xFF );
    }
    else if (cmd_len <= 0xFFFFu) 
    {
        *( p_buf++ ) = ( uint8_t )( 0x80 /* Extended */ | 0x02 /* Additional Length */ );
        *( p_buf++ ) = ( uint8_t )( ( cmd_len >> 1 * 8 ) & 0xFF );
        *( p_buf++ ) = ( uint8_t )( ( cmd_len >> 0 * 8 ) & 0xFF );
    }
    else
    {
        return PLUGNTRUST_ERROR;
    }
    //set TLV data
    if ( cmd_len ) 
    {
        while ( cmd_len-- > 0 ) 
        {
            *( p_buf++ ) = *( cmd++ );
        }
    }
    //increment payload size
    *( buf_len ) += size_of_tlv;
    
    return PLUGNTRUST_OK;
}

err_t plugntrust_set_tlv_u8buf_optional ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t *cmd, uint32_t cmd_len )
{
    if ( cmd_len )
    {
        return plugntrust_set_tlv_u8buf( buf, buf_len, tag, cmd, cmd_len );
    }
    else
    {
        return PLUGNTRUST_OK;
    }
}

err_t plugntrust_get_tlv_u8 ( uint8_t *buf, uint32_t *buf_index, uint8_t tag, uint8_t *rsp )
{
    uint8_t *pbuf = buf + ( *buf_index );
    uint8_t got_tag = *pbuf++;
    uint32_t rsp_len;
    //check if tag is ok
    if ( got_tag != tag )
    {
        return PLUGNTRUST_ERROR;
    }
    //check if rsp i greater then 1 byte of data
    rsp_len = *pbuf++;
    if ( rsp_len > 1 )
    {
        return PLUGNTRUST_ERROR;
    }
    //set rsp and index
    *rsp = *pbuf;
    *buf_index += ( 1 + 1 + ( rsp_len ) );
    buf += ( 1 + 1 + ( rsp_len ) );
    return PLUGNTRUST_OK;
}

err_t plugntrust_get_tlv_u16 ( uint8_t *buf, uint32_t *buf_index, uint8_t tag, uint16_t *rsp )
{
    uint8_t *pbuf = buf + ( *buf_index );
    uint8_t got_tag = *pbuf++;
    uint32_t rsp_len;
    //check tag
    if ( got_tag != tag )
    {
        return PLUGNTRUST_ERROR;
    }
    //check if response is greater then 2 bytes
    rsp_len = *pbuf++;
    if ( rsp_len > 2 )
    {
        return PLUGNTRUST_ERROR;
    }
    //set rsp;
    *rsp = ( *pbuf++ ) << 8;
    *rsp |= *pbuf++;
    *buf_index += ( 1 + 1 + ( rsp_len ) );
    buf += ( 1 + 1 + ( rsp_len ) );
    return PLUGNTRUST_OK;
}

err_t plugntrust_get_tlv_u8buf ( uint8_t *buf, uint32_t *buf_index, uint8_t buf_len, uint8_t tag, uint8_t *rsp, uint32_t *rsp_len )
{
    int retVal = 1;
    uint8_t *pbuf = buf + (*buf_index);
    uint8_t got_tag = *pbuf++;
    uint32_t extended_len;
    uint32_t rsplen;
    //check tag
    if ( got_tag != tag )
    {
        return PLUGNTRUST_ERROR;
    }
    //check size
    rsplen = *pbuf++;
    if ( rsplen <= 0x7FU ) 
    {
        extended_len = rsplen;
        *buf_index += ( 1 + 1 );
    }
    else if ( rsplen == 0x81 ) 
    {
        extended_len = *pbuf++;
        *buf_index += ( 1 + 1 + 1 );
    }
    else if ( rsplen == 0x82 ) 
    {
        extended_len = *pbuf++;
        extended_len = ( extended_len << 8 ) | *pbuf++;
        *buf_index += ( 1 + 1 + 2 );
    }
    else 
    {
        return PLUGNTRUST_ERROR;
    }
    //check ovf
    if ( extended_len > (*rsp_len) )
    {
        return PLUGNTRUST_ERROR;
    }
    if ( extended_len > buf_len )
    {
        return PLUGNTRUST_ERROR;
    }
    //set rsp len, index, and rs data
    *rsp_len = extended_len;
    *buf_index += extended_len;
    while ( extended_len-- > 0 ) 
    {
        *rsp++ = *pbuf++;
    }
    return PLUGNTRUST_OK;
}

uint8_t plugntrust_calculate_apdu_size ( plugntrust_apdu_t *apdu_data )
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

err_t plugntrust_end_apdu_session ( plugntrust_t *ctx )
{ 
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_S | PLUGNTRUST_PCB_BLOCK_S_END_APDU_SESSION_REQ;
    frame_data.len = 0;
    plugntrust_apdu_transfer( ctx, &frame_data );
    //check if apdu session is ended
    if ( ( PLUGNTRUST_PCB_BLOCK_S | PLUGNTRUST_PCB_BLOCK_S_END_APDU_SESSION_RSP ) == frame_data.pcb )
    {
        return PLUGNTRUST_OK;
    }
    else
    {
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_object_id_list ( plugntrust_t *ctx, uint32_t *id_list, uint8_t *list_len )
{
    *list_len = 0;
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_READ;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_LIST;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    frame_data.len = 0;
    //offset->no offset
    plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_1, 0 );
    //filter type->no filter, list all objects
    plugntrust_set_tlv_u8( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_2, 0xFF );
    //calculate apdu size
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    //request resposne data[LE]
    frame_data.len++;
    plugntrust_apdu_transfer( ctx, &frame_data );
    //check APDU status
    if ( PLUGNTRUST_SW_NOERROR != frame_data.apdu->status )
    {
        return PLUGNTRUST_ERROR;
    }
    //parse data
    uint8_t parse_data[ 0xFF ] = { 0 };
    uint32_t parse_len;
    uint8_t more;
    volatile uint32_t parse_index;
    uint8_t id_len = 0;
    parse_len = 0xFF;
    more = 0;
    parse_index = 0;
    //check more indicator data
    if ( PLUGNTRUST_OK != plugntrust_get_tlv_u8( frame_data.apdu->payload, &parse_index, PLUGNTRUST_TLV_TAG_1, &more ) )
    {
        plugntrust_end_apdu_session( ctx );
        return PLUGNTRUST_ERROR;
    }
    //format and set object ID's in array
    if ( PLUGNTRUST_OK == plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, PLUGNTRUST_TLV_TAG_2, parse_data, &parse_len ) )
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
        plugntrust_end_apdu_session( ctx );
        return PLUGNTRUST_ERROR;
    }
    *list_len = id_len;
    plugntrust_end_apdu_session( ctx );
    return PLUGNTRUST_OK;
}

err_t plugntrust_sw_reset ( plugntrust_t *ctx, plugntrust_atr_t *atr_data )
{    
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_S | PLUGNTRUST_PCB_BLOCK_S_SOFT_RESET_REQ;
    frame_data.len = 0;
    plugntrust_apdu_transfer( ctx, &frame_data );
    //check if atr data is valid and copy it if atr_data object is provided
    if ( sizeof( plugntrust_atr_t ) == frame_data.len )
    {
        if ( 0 != atr_data )
        {
            memcpy( (uint8_t *)atr_data, frame_data.apdu->payload, frame_data.len );
        }
        return PLUGNTRUST_OK;
    }
    else
    {
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_select_applet ( plugntrust_t *ctx, uint8_t ns_encode, plugntrust_version_info_t *ver_info )
{   
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I | ns_encode;
    frame_data.len = 0x15;
    frame_data.apdu->cla = 0;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT | PLUGNTRUST_INS_TRANSIENT | PLUGNTRUST_INS_ATTEST;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DES;
    frame_data.apdu->p2 = PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 16;
    uint8_t aid[ 16 ] = { 0xA0, 0x00, 0x00, 0x03, 0x96, 0x54, 0x53, 0x00, 
                          0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 };
    memcpy( frame_data.apdu->payload, aid, 16 );
    frame_data.apdu->rsp_len = 0;
    plugntrust_apdu_transfer( ctx, &frame_data );
    //Check if APDU status and inputs ver_info data if provided.
    if ( PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        if ( 0 != ver_info )
        {
            ver_info->major_version = frame_data.apdu->payload[ 0 ];
            ver_info->minor_version = frame_data.apdu->payload[ 1 ];
            ver_info->patch_version = frame_data.apdu->payload[ 2 ];
            ver_info->applet_config = ( frame_data.apdu->payload[ 3 ] << 8 ) | frame_data.apdu->payload[ 4 ];
            ver_info->secure_box = (  frame_data.apdu->payload[ 5 ] << 8 ) | frame_data.apdu->payload[ 6 ];
        }
        else 
        {
            return PLUGNTRUST_ERROR;
        }
        
        return PLUGNTRUST_OK;
    }
    else
    {
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_get_free_memory ( plugntrust_t *ctx, uint8_t memory_type, uint16_t *free_memory )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_MEMORY;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0 , sizeof(frame_data.apdu->payload) );
    //set type memory to request
    plugntrust_set_tlv_u8( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                           PLUGNTRUST_TLV_TAG_1, memory_type );
    //calculate APDU data size
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    plugntrust_apdu_transfer( ctx, &frame_data );
    //prase
    uint32_t parse_index = 0;
    *free_memory = 0;
    //set free_memory value
    if ( PLUGNTRUST_OK == plugntrust_get_tlv_u16( frame_data.apdu->payload, &parse_index, PLUGNTRUST_TLV_TAG_1, free_memory ) )
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_OK;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_get_random_numbers ( plugntrust_t *ctx, uint8_t *random_buf, uint8_t buf_len )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_RANDOM;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0 , sizeof(frame_data.apdu->payload) );
    //set number of random bytes to request
    plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                           PLUGNTRUST_TLV_TAG_1, buf_len );
    //calculate APDU size
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    //set rsp_len request data
    frame_data.len++;
    plugntrust_apdu_transfer( ctx, &frame_data );
    //parse
    uint32_t parse_len = buf_len;
    uint32_t parse_index = 0;
    //input random data in object
    if ( PLUGNTRUST_OK == plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, PLUGNTRUST_TLV_TAG_1, random_buf, &parse_len ) )
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_OK;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_check_object_exist ( plugntrust_t *ctx, uint32_t object_id )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_EXIST;
    frame_data.apdu->payload_len = 0;
    //set object ID
    plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                           PLUGNTRUST_TLV_TAG_1, object_id );
    //calculate APDU size
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    plugntrust_apdu_transfer( ctx, &frame_data );
    //parse
    uint32_t parse_index = 0;
    uint8_t obj_exists = 0;
    //check rsp if object exists
    if ( PLUGNTRUST_OK == plugntrust_get_tlv_u8( frame_data.apdu->payload, &parse_index, PLUGNTRUST_TLV_TAG_1, &obj_exists ) )
    {
        plugntrust_end_apdu_session( ctx ); 
        return obj_exists;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_delete_object ( plugntrust_t *ctx, uint32_t object_id )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_DELETE_OBJECT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0 , sizeof(frame_data.apdu->payload) );
    //object to delete
    plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_1, object_id );
    //calculate APDU
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    plugntrust_apdu_transfer( ctx, &frame_data ); 
    //check status
    if ( PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_OK;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_select_card_manager ( plugntrust_t *ctx, uint8_t rsp, uint8_t *cardmanager_rsp, uint8_t *cardmanager_rsp_len )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.len = 4 + rsp;
    frame_data.apdu->cla = 0;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT | PLUGNTRUST_INS_TRANSIENT | PLUGNTRUST_INS_ATTEST;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DES;
    frame_data.apdu->p2 = PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    
    plugntrust_apdu_transfer( ctx, &frame_data );
    //if rsp copy data to output buffer
    if ( rsp )
    {
        memcpy( cardmanager_rsp, frame_data.apdu->payload, frame_data.apdu->payload_len );
        *cardmanager_rsp_len = frame_data.apdu->payload_len;
    }
    //check status
    if ( PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        return PLUGNTRUST_OK;
    }
    else
    {
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_read_object 
( plugntrust_t *ctx, uint32_t object_id, uint16_t offset, uint16_t read_len, uint8_t *data_buf, uint32_t *data_len )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_READ;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    memset( frame_data.apdu->payload, 0 , sizeof(frame_data.apdu->payload) );
    //set object ID
    plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_1, object_id );
    //set read offset
    plugntrust_set_tlv_u16_optional( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_2, offset );
    //limit read length(0 if you want to read everything)
    plugntrust_set_tlv_u16_optional( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_3, read_len );
    //calculate APDU
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    //request rsp data
    frame_data.len++;
    plugntrust_apdu_transfer( ctx, &frame_data );
    //parse
    uint32_t parse_index = 0;
    //set read data to output buffer
    if ( PLUGNTRUST_OK == plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, PLUGNTRUST_TLV_TAG_1, data_buf, data_len ) )
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_OK;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_write_binary_object 
( plugntrust_t *ctx, uint32_t object_id, uint16_t offset, uint16_t data_len, uint8_t *data_buf )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_WRITE;
    frame_data.apdu->p1 = PLUGNTRUST_P1_BINARY;
    frame_data.apdu->p2 = PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0;
    frame_data.len = 0;
    //object ID
    plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_1, object_id );
    //write offeset
    plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_2, offset );
    //bytes to write
    plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_3, data_len );
    //data bytes
    plugntrust_set_tlv_u8buf( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                            PLUGNTRUST_TLV_TAG_4, data_buf, ( uint32_t )data_len );
    //calculate APDU size
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    plugntrust_apdu_transfer( ctx, &frame_data );
    //check status
    if ( PLUGNTRUST_SW_NOERROR == frame_data.apdu->status )
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_OK;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

err_t plugntrust_get_applet_info ( plugntrust_t *ctx, plugntrust_version_info_t *ver_info )
{
    frame_data.pcb = PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = PLUGNTRUST_INS_MGMT;
    frame_data.apdu->p1 = PLUGNTRUST_P1_DEFAULT;
    frame_data.apdu->p2 = PLUGNTRUST_P2_VERSION;
    frame_data.apdu->payload_len = 0;
    frame_data.apdu->rsp_len = 0x09;
    frame_data.len = plugntrust_calculate_apdu_size( frame_data.apdu );
    plugntrust_apdu_transfer( ctx, &frame_data );
    uint32_t parse_index = 0;
    uint32_t parse_len = 0xA;
    uint8_t prase_buf[ 0xA ] = { 0 };
    //check APDU size
    if ( PLUGNTRUST_OK == plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, PLUGNTRUST_TLV_TAG_1, prase_buf, &parse_len ) )
    {
        ver_info->major_version = prase_buf[ 0 ];
        ver_info->minor_version = prase_buf[ 1 ];
        ver_info->patch_version = prase_buf[ 2 ];
        ver_info->applet_config = ( prase_buf[ 3 ] << 8 ) | prase_buf[ 4 ];
        ver_info->secure_box = (  prase_buf[ 5 ] << 8 ) | prase_buf[ 6 ];
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_OK;
    }
    else
    {
        plugntrust_end_apdu_session( ctx ); 
        return PLUGNTRUST_ERROR;
    }
}

static uint16_t plugntrust_create_crc ( uint8_t *crc_buff, uint16_t length )
{
    uint16_t crc16 = 0xFFFF;
    int8_t bit_idx;
    uint8_t new_byte[ 2 ] = { 0 };

    if ( crc_buff == NULL )
    {
        return crc16;
    }
    
    for ( uint16_t i = 0; i < length; i++ )
    {
        crc16 ^= crc_buff[ i ];
        
        for ( bit_idx = 8; bit_idx > 0; --bit_idx )
        {
            if ( ( crc16 & 0x0001 ) == 0x0001 )
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

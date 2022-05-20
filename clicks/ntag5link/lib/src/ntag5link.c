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
 * @file ntag5link.c
 * @brief NTAG 5 Link Click Driver.
 */

#include "ntag5link.h"

void ntag5link_cfg_setup ( ntag5link_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->hpd = HAL_PIN_NC;
    cfg->ed = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NTAG5LINK_DEVICE_ADDRESS;
}

err_t ntag5link_init ( ntag5link_t *ctx, ntag5link_cfg_t *cfg ) 
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

    digital_out_init( &ctx->hpd, cfg->hpd );

    digital_in_init( &ctx->ed, cfg->ed );

    return I2C_MASTER_SUCCESS;
}

err_t ntag5link_default_cfg ( ntag5link_t *ctx ) 
{
    err_t error_flag = NTAG5LINK_OK;
    ntag5link_enable_device ( ctx );
    Delay_100ms ( );
    ntag5link_block_t config;
    config.value_bytes[ 0 ] = NTAG5LINK_CONFIG_0_EH_LOW_FIELD_STR;
    config.value_bytes[ 1 ] = NTAG5LINK_CONFIG_1_ARBITER_SRAM_MIRROR | NTAG5LINK_CONFIG_1_SRAM_ENABLE;
    config.value_bytes[ 2 ] = NTAG5LINK_CONFIG_2_GPIO1_IN_PULL_DOWN | NTAG5LINK_CONFIG_2_GPIO0_IN_PULL_DOWN |
                              NTAG5LINK_CONFIG_2_EXT_CMD_SUPPORT | NTAG5LINK_CONFIG_2_LOCK_BLK_CMD_SUPPORT |
                              NTAG5LINK_CONFIG_2_GPIO1_HIGH_SLEW_RATE | NTAG5LINK_CONFIG_2_GPIO0_HIGH_SLEW_RATE;
    config.value_bytes[ 3 ] = 0; // RFU
    error_flag |= ntag5link_write_memory_block ( ctx, NTAG5LINK_CONFIG_CONFIG, &config );
    ntag5link_disable_device ( ctx );
    Delay_100ms ( );
    ntag5link_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= ntag5link_format_memory ( ctx );
    return error_flag;
}

err_t ntag5link_write_memory_block ( ntag5link_t *ctx, uint16_t block_addr, ntag5link_block_t *block )
{
    if ( ( ( block_addr > NTAG5LINK_USER_MEMORY_ADDRESS_MAX ) && 
           ( block_addr < NTAG5LINK_CONFIG_MEMORY_ADDRESS_MIN ) ) || 
         ( block_addr > NTAG5LINK_CONFIG_MEMORY_ADDRESS_MAX ) )
    {
        return NTAG5LINK_ERROR;
    }
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( block_addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( block_addr & 0xFF );
    data_buf[ 2 ] = block->value_bytes[ 0 ];
    data_buf[ 3 ] = block->value_bytes[ 1 ];
    data_buf[ 4 ] = block->value_bytes[ 2 ];
    data_buf[ 5 ] = block->value_bytes[ 3 ];
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 6 );
    Delay_5ms ( );
    return error_flag;
}

err_t ntag5link_read_memory_block ( ntag5link_t *ctx, uint16_t block_addr, ntag5link_block_t *block )
{
    if ( ( ( block_addr > NTAG5LINK_USER_MEMORY_ADDRESS_MAX ) && 
           ( block_addr < NTAG5LINK_CONFIG_MEMORY_ADDRESS_MIN ) ) || 
         ( block_addr > NTAG5LINK_CONFIG_MEMORY_ADDRESS_MAX ) )
    {
        return NTAG5LINK_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( block_addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( block_addr & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, block->value_bytes, 4 );
    return error_flag;
}

err_t ntag5link_write_multiple_memory_block ( ntag5link_t *ctx, uint16_t block_addr, 
                                              ntag5link_block_t *block, uint8_t num_blocks )
{
    if ( ( ( ( block_addr + num_blocks ) > NTAG5LINK_USER_MEMORY_ADDRESS_MAX ) && 
           ( block_addr < NTAG5LINK_CONFIG_MEMORY_ADDRESS_MIN ) ) || 
         ( ( block_addr + num_blocks ) > NTAG5LINK_CONFIG_MEMORY_ADDRESS_MAX ) )
    {
        return NTAG5LINK_ERROR;
    }
    err_t error_flag = NTAG5LINK_OK;
    for ( uint8_t cnt = 0; cnt < num_blocks; cnt++ )
    {
        error_flag |= ntag5link_write_memory_block ( ctx, block_addr + cnt, &block[ cnt ] );
    }
    return error_flag;
}

err_t ntag5link_read_multiple_memory_block ( ntag5link_t *ctx, uint16_t block_addr, 
                                             ntag5link_block_t *block, uint8_t num_blocks )
{
    if ( ( ( ( block_addr + num_blocks ) > NTAG5LINK_USER_MEMORY_ADDRESS_MAX ) && 
           ( block_addr < NTAG5LINK_CONFIG_MEMORY_ADDRESS_MIN ) ) || 
         ( ( block_addr + num_blocks ) > NTAG5LINK_CONFIG_MEMORY_ADDRESS_MAX ) )
    {
        return NTAG5LINK_ERROR;
    }
    err_t error_flag = NTAG5LINK_OK;
    for ( uint8_t cnt = 0; cnt < num_blocks; cnt++ )
    {
        error_flag |= ntag5link_read_memory_block ( ctx, block_addr + cnt, &block[ cnt ] );
    }
    return error_flag;
}

err_t ntag5link_write_session_register ( ntag5link_t *ctx, uint16_t block_addr, uint8_t byte_num, 
                                         uint8_t mask, uint8_t data_in )
{
    if ( ( block_addr < NTAG5LINK_SESSION_REG_ADDRESS_MIN ) || 
         ( block_addr > NTAG5LINK_SESSION_REG_ADDRESS_MAX ) || 
         ( byte_num > NTAG5LINK_SESSION_REG_BYTE_3 ) )
    {
        return NTAG5LINK_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( block_addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( block_addr & 0xFF );
    data_buf[ 2 ] = byte_num;
    data_buf[ 3 ] = mask;
    data_buf[ 4 ] = data_in;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 5 );
    Delay_5ms ( );
    return error_flag;
}

err_t ntag5link_read_session_register ( ntag5link_t *ctx, uint16_t block_addr, uint8_t byte_num, uint8_t *data_out )
{
    if ( ( block_addr < NTAG5LINK_SESSION_REG_ADDRESS_MIN ) || 
         ( block_addr > NTAG5LINK_SESSION_REG_ADDRESS_MAX ) || 
         ( byte_num > NTAG5LINK_SESSION_REG_BYTE_3 ) )
    {
        return NTAG5LINK_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( block_addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( block_addr & 0xFF );
    data_buf[ 2 ] = byte_num;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 3 );
    error_flag |= i2c_master_read( &ctx->i2c, data_out, 1 );
    return error_flag;
}

err_t ntag5link_write_ndef_uri_record ( ntag5link_t *ctx, uint8_t uri_prefix, uint8_t *uri_data, uint8_t data_len )
{
    err_t error_flag = NTAG5LINK_OK;
    ntag5link_block_t ndef_block = { NTAG5LINK_CAPABILITY_CONTAINER };
    error_flag |= ntag5link_write_memory_block ( ctx, NTAG5LINK_CAPABILITY_CONTAINER_ADDRESS, &ndef_block );
    
    uint8_t block_address = NTAG5LINK_NDEF_MESSAGE_START_ADDRESS;
    ndef_block.value_bytes[ 0 ] = NTAG5LINK_TYPE_NDEF_MESSAGE;  // NDEF Message
    ndef_block.value_bytes[ 1 ] = data_len + 5;                 // Message size
    ndef_block.value_bytes[ 2 ] = NTAG5LINK_NDEF_RECORD_HEADER; // Record header
    ndef_block.value_bytes[ 3 ] = NTAG5LINK_NDEF_TYPE_LENGTH;   // Type Length - 1 byte
    error_flag |= ntag5link_write_memory_block ( ctx, block_address++, &ndef_block );
    
    ndef_block.value_bytes[ 0 ] = data_len + 1;                 // Payload Length
    ndef_block.value_bytes[ 1 ] = NTAG5LINK_NDEF_URI_TYPE;      // Type / URI
    ndef_block.value_bytes[ 2 ] = uri_prefix;                   // URI prefix
    ndef_block.value_bytes[ 3 ] = uri_data[ 0 ];                // URI data
    error_flag |= ntag5link_write_memory_block ( ctx, block_address++, &ndef_block );
    data_len--;
    while ( data_len >= NTAG5LINK_MEMORY_BLOCK_SIZE )
    {
        memcpy ( ndef_block.value_bytes, 
                 &uri_data[ ( block_address - NTAG5LINK_NDEF_MESSAGE_START_ADDRESS - 2 ) * NTAG5LINK_MEMORY_BLOCK_SIZE + 1 ], 
                 NTAG5LINK_MEMORY_BLOCK_SIZE );
        error_flag |= ntag5link_write_memory_block ( ctx, block_address++, &ndef_block );
        data_len -= NTAG5LINK_MEMORY_BLOCK_SIZE;
    }
    ndef_block.value = 0;
    memcpy ( ndef_block.value_bytes, 
             &uri_data[ ( block_address - NTAG5LINK_NDEF_MESSAGE_START_ADDRESS - 2 ) * NTAG5LINK_MEMORY_BLOCK_SIZE + 1 ], 
             data_len % NTAG5LINK_MEMORY_BLOCK_SIZE );
    ndef_block.value_bytes[ data_len % NTAG5LINK_MEMORY_BLOCK_SIZE ] = NTAG5LINK_NDEF_MESSAGE_END_MARK;
    error_flag |= ntag5link_write_memory_block ( ctx, block_address, &ndef_block );
    return error_flag;
}

err_t ntag5link_format_memory ( ntag5link_t *ctx )
{
    err_t error_flag = NTAG5LINK_OK;
    ntag5link_block_t ndef_block;
    ndef_block.value = 0;
    for ( uint16_t cnt = NTAG5LINK_USER_MEMORY_ADDRESS_MIN; cnt < NTAG5LINK_USER_MEMORY_ADDRESS_MAX; cnt++ )
    {
        error_flag |= ntag5link_write_memory_block ( ctx, cnt, &ndef_block );
    }
    return error_flag;
}

err_t ntag5link_write_message_to_memory ( ntag5link_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len )
{
    if ( ( block_addr < NTAG5LINK_USER_MEMORY_ADDRESS_MIN ) || 
         ( block_addr > NTAG5LINK_USER_MEMORY_ADDRESS_MAX ) || 
         ( NULL == message_len ) || 
         ( NULL == message ) )
    {
        return NTAG5LINK_ERROR;
    }
    ntag5link_block_t *ndef_block = ( ntag5link_block_t * ) message;
    uint8_t num_blocks = message_len / NTAG5LINK_MEMORY_BLOCK_SIZE;
    if ( message_len % NTAG5LINK_MEMORY_BLOCK_SIZE )
    {
        num_blocks++;
    }
    return ntag5link_write_multiple_memory_block ( ctx, block_addr, ndef_block, num_blocks );
}

err_t ntag5link_read_message_from_memory ( ntag5link_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len )
{
    if ( ( block_addr < NTAG5LINK_USER_MEMORY_ADDRESS_MIN ) || 
         ( block_addr > NTAG5LINK_USER_MEMORY_ADDRESS_MAX ) || 
         ( NULL == message_len ) || 
         ( NULL == message ) )
    {
        return NTAG5LINK_ERROR;
    }
    ntag5link_block_t *ndef_block = ( ntag5link_block_t * ) message;
    uint8_t num_blocks = message_len / NTAG5LINK_MEMORY_BLOCK_SIZE;
    if ( message_len % NTAG5LINK_MEMORY_BLOCK_SIZE )
    {
        num_blocks++;
    }
    return ntag5link_read_multiple_memory_block ( ctx, block_addr, ndef_block, num_blocks );
}

uint8_t ntag5link_get_event_detection_pin ( ntag5link_t *ctx )
{
    return digital_in_read ( &ctx->ed );
}

void ntag5link_enable_device ( ntag5link_t *ctx )
{
    digital_out_low ( &ctx->hpd );
}

void ntag5link_disable_device ( ntag5link_t *ctx )
{
    digital_out_high ( &ctx->hpd );
}

// ------------------------------------------------------------------------- END

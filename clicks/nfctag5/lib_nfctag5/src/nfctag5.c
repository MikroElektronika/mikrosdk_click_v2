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
 * @file nfctag5.c
 * @brief NFC Tag 5 Click Driver.
 */

#include "nfctag5.h"

void nfctag5_cfg_setup ( nfctag5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->vh   = HAL_PIN_NC;
    cfg->busy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NFCTAG5_ADDRESS_MODE_USER_MEMORY;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = NFCTAG5_VH_VREF;
}

err_t nfctag5_init ( nfctag5_t *ctx, nfctag5_cfg_t *cfg ) 
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
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->vh;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_in_init( &ctx->busy, cfg->busy );

    return I2C_MASTER_SUCCESS;
}

err_t nfctag5_default_cfg ( nfctag5_t *ctx ) 
{
    err_t error_flag = NFCTAG5_OK;
    error_flag |= nfctag5_set_address_mode ( ctx, NFCTAG5_ADDRESS_MODE_USER_MEMORY );
    error_flag |= nfctag5_format_memory ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t nfctag5_set_address_mode ( nfctag5_t *ctx, uint8_t mode )
{
    if ( NFCTAG5_ADDRESS_MODE_CONFIG == mode )
    {
        ctx->slave_address = NFCTAG5_DEVICE_ADDRESS_CONFIG;
        return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    else
    {
        ctx->slave_address = NFCTAG5_DEVICE_ADDRESS_USER_MEMORY;
        return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
}

err_t nfctag5_write_memory_block ( nfctag5_t *ctx, uint16_t block_addr, nfctag5_block_t *block )
{
    block_addr &= NFCTAG5_MEMORY_BLOCK_MASK;
    if ( ( block_addr + NFCTAG5_MEMORY_BLOCK_SIZE ) > NFCTAG5_USER_MEMORY_ADDRESS_MAX )
    {
        return NFCTAG5_ERROR;
    }
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( block_addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( block_addr & 0xFF );
    data_buf[ 2 ] = block->value_bytes[ 0 ];
    data_buf[ 3 ] = block->value_bytes[ 1 ];
    data_buf[ 4 ] = block->value_bytes[ 2 ];
    data_buf[ 5 ] = block->value_bytes[ 3 ];
    while ( !nfctag5_get_busy_pin ( ctx ) );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 6 );
    Delay_5ms ( );
    return error_flag;
}

err_t nfctag5_read_memory_block ( nfctag5_t *ctx, uint16_t block_addr, nfctag5_block_t *block )
{
    block_addr &= NFCTAG5_MEMORY_BLOCK_MASK;
    if ( ( block_addr + NFCTAG5_MEMORY_BLOCK_SIZE ) > NFCTAG5_USER_MEMORY_ADDRESS_MAX )
    {
        return NFCTAG5_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( block_addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( block_addr & 0xFF );
    while ( !nfctag5_get_busy_pin ( ctx ) );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, block->value_bytes, 4 );
    return error_flag;
}

err_t nfctag5_write_multiple_memory_block ( nfctag5_t *ctx, uint16_t block_addr, 
                                            nfctag5_block_t *block, uint8_t num_blocks )
{
    block_addr &= NFCTAG5_MEMORY_BLOCK_MASK;
    if ( ( block_addr + ( num_blocks * NFCTAG5_MEMORY_BLOCK_SIZE ) ) > NFCTAG5_USER_MEMORY_ADDRESS_MAX )
    {
        return NFCTAG5_ERROR;
    }
    err_t error_flag = NFCTAG5_OK;
    for ( uint8_t cnt = 0; cnt < num_blocks; cnt++ )
    {
        error_flag |= nfctag5_write_memory_block ( ctx, block_addr + ( cnt * NFCTAG5_MEMORY_BLOCK_SIZE ), &block[ cnt ] );
    }
    return error_flag;
}

err_t nfctag5_read_multiple_memory_block ( nfctag5_t *ctx, uint16_t block_addr, 
                                           nfctag5_block_t *block, uint8_t num_blocks )
{
    block_addr &= NFCTAG5_MEMORY_BLOCK_MASK;
    if ( ( block_addr + ( num_blocks * NFCTAG5_MEMORY_BLOCK_SIZE ) ) > NFCTAG5_USER_MEMORY_ADDRESS_MAX )
    {
        return NFCTAG5_ERROR;
    }
    err_t error_flag = NFCTAG5_OK;
    for ( uint8_t cnt = 0; cnt < num_blocks; cnt++ )
    {
        error_flag |= nfctag5_read_memory_block ( ctx, block_addr + ( cnt * NFCTAG5_MEMORY_BLOCK_SIZE ), &block[ cnt ] );
    }
    return error_flag;
}

err_t nfctag5_write_ndef_uri_record ( nfctag5_t *ctx, uint8_t uri_prefix, uint8_t *uri_data, uint8_t data_len )
{
    err_t error_flag = NFCTAG5_OK;
    nfctag5_block_t ndef_block = { NFCTAG5_CAPABILITY_CONTAINER };
    error_flag |= nfctag5_write_memory_block ( ctx, NFCTAG5_CAPABILITY_CONTAINER_ADDRESS, &ndef_block );
    
    uint8_t block_address = NFCTAG5_NDEF_MESSAGE_START_ADDRESS;
    ndef_block.value_bytes[ 0 ] = NFCTAG5_TYPE_NDEF_MESSAGE;    // NDEF Message
    ndef_block.value_bytes[ 1 ] = data_len + 5;                 // Message size
    ndef_block.value_bytes[ 2 ] = NFCTAG5_NDEF_RECORD_HEADER;   // Record header
    ndef_block.value_bytes[ 3 ] = NFCTAG5_NDEF_TYPE_LENGTH;     // Type Length - 1 byte
    error_flag |= nfctag5_write_memory_block ( ctx, block_address, &ndef_block );
    block_address += NFCTAG5_MEMORY_BLOCK_SIZE;
    
    ndef_block.value_bytes[ 0 ] = data_len + 1;                 // Payload Length
    ndef_block.value_bytes[ 1 ] = NFCTAG5_NDEF_URI_TYPE;        // Type / URI
    ndef_block.value_bytes[ 2 ] = uri_prefix;                   // URI prefix
    ndef_block.value_bytes[ 3 ] = uri_data[ 0 ];                // URI data
    error_flag |= nfctag5_write_memory_block ( ctx, block_address, &ndef_block );
    block_address += NFCTAG5_MEMORY_BLOCK_SIZE;
    data_len--;
    while ( data_len >= NFCTAG5_MEMORY_BLOCK_SIZE )
    {
        memcpy ( ndef_block.value_bytes, 
                 &uri_data[ block_address - NFCTAG5_NDEF_MESSAGE_START_ADDRESS - 7 ], 
                 NFCTAG5_MEMORY_BLOCK_SIZE );
        error_flag |= nfctag5_write_memory_block ( ctx, block_address, &ndef_block );
        block_address += NFCTAG5_MEMORY_BLOCK_SIZE;
        data_len -= NFCTAG5_MEMORY_BLOCK_SIZE;
    }
    ndef_block.value = 0;
    memcpy ( ndef_block.value_bytes, 
             &uri_data[ block_address - NFCTAG5_NDEF_MESSAGE_START_ADDRESS - 7 ], 
             data_len % NFCTAG5_MEMORY_BLOCK_SIZE );
    ndef_block.value_bytes[ data_len % NFCTAG5_MEMORY_BLOCK_SIZE ] = NFCTAG5_NDEF_MESSAGE_END_MARK;
    error_flag |= nfctag5_write_memory_block ( ctx, block_address, &ndef_block );
    return error_flag;
}

err_t nfctag5_format_memory ( nfctag5_t *ctx )
{
    err_t error_flag = NFCTAG5_OK;
    nfctag5_block_t ndef_block;
    ndef_block.value = 0;
    for ( uint16_t cnt = NFCTAG5_USER_MEMORY_ADDRESS_MIN; 
          cnt < ( NFCTAG5_USER_MEMORY_ADDRESS_MAX - NFCTAG5_MEMORY_BLOCK_SIZE ); 
          cnt += NFCTAG5_MEMORY_BLOCK_SIZE )
    {
        error_flag |= nfctag5_write_memory_block ( ctx, cnt, &ndef_block );
    }
    return error_flag;
}

err_t nfctag5_write_message_to_memory ( nfctag5_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len )
{
    if ( ( NULL == message_len ) || ( NULL == message ) )
    {
        return NFCTAG5_ERROR;
    }
    uint8_t num_blocks = message_len / NFCTAG5_MEMORY_BLOCK_SIZE;
    if ( message_len % NFCTAG5_MEMORY_BLOCK_SIZE )
    {
        num_blocks++;
    }
    if ( ( block_addr + num_blocks * NFCTAG5_MEMORY_BLOCK_SIZE ) > NFCTAG5_USER_MEMORY_ADDRESS_MAX ) 
    {
        return NFCTAG5_ERROR;
    }
    nfctag5_block_t *ndef_block = ( nfctag5_block_t * ) message;
    return nfctag5_write_multiple_memory_block ( ctx, block_addr, ndef_block, num_blocks );
}

err_t nfctag5_read_message_from_memory ( nfctag5_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len )
{
    if ( ( NULL == message_len ) || ( NULL == message ) )
    {
        return NFCTAG5_ERROR;
    }
    uint8_t num_blocks = message_len / NFCTAG5_MEMORY_BLOCK_SIZE;
    if ( message_len % NFCTAG5_MEMORY_BLOCK_SIZE )
    {
        num_blocks++;
    }
    if ( ( block_addr + num_blocks * NFCTAG5_MEMORY_BLOCK_SIZE ) > NFCTAG5_USER_MEMORY_ADDRESS_MAX ) 
    {
        return NFCTAG5_ERROR;
    }
    nfctag5_block_t *ndef_block = ( nfctag5_block_t * ) message;
    return nfctag5_read_multiple_memory_block ( ctx, block_addr, ndef_block, num_blocks );
}

err_t nfctag5_read_vh_pin_value ( nfctag5_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t nfctag5_read_vh_pin_voltage ( nfctag5_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

uint8_t nfctag5_get_busy_pin ( nfctag5_t *ctx )
{
    return digital_in_read ( &ctx->busy );
}

// ------------------------------------------------------------------------- END

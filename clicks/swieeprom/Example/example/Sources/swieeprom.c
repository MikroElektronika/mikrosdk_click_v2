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
 * @file swieeprom.c
 * @brief This file contains API for SWI EEPROM Click Driver.
 */

#include "swieeprom.h"
#include "swi.h"

/**
 * @brief Delay after memory write
 * @details Delay for device to proces written data to memory.
 */
#define MEMORY_WRITE_DELAY      1

/**
 * @brief Addres read/write bit
 * @details Bit to send device to notify it of read/write communication.
 */
#define W_BIT                   0
#define R_BIT                   1

/**
 * @brief Slave address
 * @details Driver slave address.
 */
static uint8_t slave_address    = 0;

/**
 * @brief Discover devices slave address.
 * @details Sends slave adress with opcode wor memory 
 * and checks ACK data to store @b slave_address in driver.
 * @return @li @c  0 - Slave address found,
 *         @li @c -1 - No slave address found.
 */
static swieeprom_return_value_t scan_slave_address( swieeprom_t *ctx );

swieeprom_return_value_t swieeprom_init( swieeprom_t *ctx )
{
    if ( swi_init( ) )
        return SWIEEPROM_RET_VAL_ERROR_NO_DEVICE_FOUND;
    
    ctx->slave_address = 0;
    
    if ( SWIEEPROM_RET_VAL_ERROR == scan_slave_address( ctx ) )
        return SWIEEPROM_RET_VAL_ERROR_SLAVE_ADDRESS;
    
    return SWIEEPROM_RET_VAL_OK;
}

swieeprom_return_value_t swieeprom_read_id( swieeprom_t *ctx )
{
    uint8_t id_data[ 3 ] = { 0 };
    uint32_t id_value = 0;
    
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_ID | ctx->slave_address | R_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    swi_receive_byte( &id_data[ 0 ], SWI_ACK );
    swi_receive_byte( &id_data[ 1 ], SWI_ACK );
    swi_receive_byte( &id_data[ 2 ], SWI_NACK );
    swi_stop( );
    
    id_value = id_data[ 0 ];
    id_value <<= 8;
    id_value |= id_data[ 1 ];
    id_value <<= 8;
    id_value |= id_data[ 2 ];
    
    if ( SWIEEPROM_ID == id_value )
        return SWIEEPROM_RET_VAL_OK;
    else
        return SWIEEPROM_RET_VAL_ERROR_ID;
}

swieeprom_return_value_t swieeprom_write_to_memory ( swieeprom_t *ctx, uint8_t mem_adr, uint8_t mem_data )
{
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | W_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    if ( swi_send_byte( mem_adr ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_ADR;
    }
    if ( swi_send_byte( mem_data ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_DATA;
    }
    swi_stop( );
    
    Delay_ms( MEMORY_WRITE_DELAY );
    
    return SWIEEPROM_RET_VAL_OK;
}

swieeprom_return_value_t swieeprom_read_from_memory ( swieeprom_t *ctx, uint8_t mem_adr, uint8_t *mem_data )
{
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | W_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    if ( swi_send_byte( mem_adr ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_ADR;
    }
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | R_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    swi_receive_byte( mem_data, SWI_NACK );
    swi_stop( );
    return SWIEEPROM_RET_VAL_OK;
}

swieeprom_return_value_t swieeprom_write_data_to_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint8_t *tx_buf, uint16_t buf_len )
{
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | W_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    if ( swi_send_byte( start_mem_adr ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_ADR;
    }
    
    for ( uint16_t buf_cnt = 0; buf_cnt < buf_len; buf_cnt++ )
    {
        if ( swi_send_byte( tx_buf[ buf_cnt ] ) )
        {
            swi_stop( );
            return SWIEEPROM_RET_VAL_ERROR_DATA;
        }
    }
    
    swi_stop( );
    
    Delay_ms( MEMORY_WRITE_DELAY );
    
    return SWIEEPROM_RET_VAL_OK;
}

swieeprom_return_value_t swieeprom_read_data_from_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint8_t *rx_buf, uint16_t buf_len )
{
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | W_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    if ( swi_send_byte( start_mem_adr ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_ADR;
    }
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | R_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    for ( uint16_t buf_cnt = 0; buf_cnt < buf_len; buf_cnt++ )
    {
        if ( ( buf_cnt + 1 ) == buf_len )
            swi_receive_byte( rx_buf + buf_cnt, SWI_NACK );
        else
            swi_receive_byte( rx_buf + buf_cnt, SWI_ACK );
    }
    
    swi_stop( );
    return SWIEEPROM_RET_VAL_OK;
}

swieeprom_return_value_t swieeprom_clear_data_from_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint16_t buf_len )
{
    swi_start( );
    if ( swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | W_BIT ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_OP_CODE;
    }
    if ( swi_send_byte( start_mem_adr ) )
    {
        swi_stop( );
        return SWIEEPROM_RET_VAL_ERROR_ADR;
    }
    
    for ( uint16_t buf_cnt = 0; buf_cnt < buf_len; buf_cnt++ )
    {
        if ( swi_send_byte( 0xFF ) )
        {
            swi_stop( );
            return SWIEEPROM_RET_VAL_ERROR_DATA;
        }
    }
    
    swi_stop( );
    
    Delay_ms( MEMORY_WRITE_DELAY );
    
    return SWIEEPROM_RET_VAL_OK;
}

static swieeprom_return_value_t scan_slave_address ( swieeprom_t *ctx )
{
    for ( uint8_t slave_cnt = 0; slave_cnt < 7; slave_cnt++ )
    {
        uint8_t slave_adr = slave_cnt << 1;
        swi_start( );
        if ( SWI_ACK == swi_send_byte( SWIEEPROM_OP_CODE_EEPROM | slave_adr ) )
        {
            ctx->slave_address = slave_adr;
            swi_stop( );
            return SWIEEPROM_RET_VAL_OK;
        }
        swi_stop( );
    }
    
    return SWIEEPROM_RET_VAL_ERROR;
}


// ------------------------------------------------------------------------ END

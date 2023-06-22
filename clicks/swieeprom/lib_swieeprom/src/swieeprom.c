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
 * @brief SWI EEPROM Click Driver.
 */

#include "swieeprom.h"

/**
 * @brief SWI EEPROM send byte function.
 * @details This function writes one byte using the Single Wire interface.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @param[in] byte_to_send : Byte data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static uint8_t swieeprom_send_byte ( swieeprom_t *ctx, uint8_t byte_to_send );

/**
 * @brief SWI EEPROM receive byte function.
 * @details This function reads one byte using the Single Wire interface.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @param[out] byte_to_receive : Read data byte.
 * @param[in] ack_nack : 0 - ACK, 1 - NACK to be written after read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static void swieeprom_receive_byte ( swieeprom_t *ctx, uint8_t *byte_to_receive, uint8_t ack_nack );

/**
 * @brief SWI EEPROM scan devices function.
 * @details This function scans for devices on the bus and saves the device address in the context object.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t swieeprom_scan_devices ( swieeprom_t *ctx );

err_t swieeprom_init ( swieeprom_t *ctx ) 
{
    err_t error_flag = SWIEEPROM_OK;
    
    if ( SWIEEPROM_ERROR == ctx->swi_reset ( ) )
    {
        return SWIEEPROM_ERROR;
    }
    
    ctx->slave_address = 0;
    
    error_flag |= swieeprom_scan_devices( ctx );
    
    Delay_100ms ( );

    return error_flag;
}

err_t swieeprom_check_communication ( swieeprom_t *ctx )
{
    uint8_t id_data[ 3 ] = { 0 };
    uint32_t id_value = 0;
    
    ctx->swi_start_stop ( );
    if ( SWIEEPROM_ERROR == swieeprom_send_byte ( ctx, SWIEEPROM_OP_CODE_ID | ctx->slave_address | 1 ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    swieeprom_receive_byte ( ctx, &id_data[ 0 ], 0 );
    swieeprom_receive_byte ( ctx, &id_data[ 1 ], 0 );
    swieeprom_receive_byte ( ctx, &id_data[ 2 ], 1 );
    ctx->swi_start_stop ( );
    
    id_value = id_data[ 0 ];
    id_value <<= 8;
    id_value |= id_data[ 1 ];
    id_value <<= 8;
    id_value |= id_data[ 2 ];
    
    if ( SWIEEPROM_DEVICE_ID != id_value )
    {
        return SWIEEPROM_ERROR;
    }
    return SWIEEPROM_OK;
}

err_t swieeprom_mem_write ( swieeprom_t *ctx, uint8_t start_addr, uint8_t data_in )
{
    if ( start_addr >= 128 )
    {
        return SWIEEPROM_ERROR;
    }
    ctx->swi_start_stop ( );
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, start_addr ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, data_in ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    ctx->swi_start_stop ( );
    Delay_10ms( );
    return SWIEEPROM_OK;
}

err_t swieeprom_mem_write_page ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || ( len > 8 ) || ( ( start_addr + len ) > 128 ) )
    {
        return SWIEEPROM_ERROR;
    }
    ctx->swi_start_stop ( );
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, start_addr ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, data_in[ cnt ] ) )
        {
            ctx->swi_start_stop ( );
            return SWIEEPROM_ERROR;
        }
    }
    ctx->swi_start_stop ( );
    Delay_10ms( );
    return SWIEEPROM_OK;
}

err_t swieeprom_mem_read ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || ( ( start_addr + len ) > 128 ) )
    {
        return SWIEEPROM_ERROR;
    }
    ctx->swi_start_stop ( );
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, start_addr ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    ctx->swi_start_stop ( );
    if ( SWIEEPROM_ERROR == swieeprom_send_byte( ctx, SWIEEPROM_OP_CODE_EEPROM | ctx->slave_address | 1 ) )
    {
        ctx->swi_start_stop ( );
        return SWIEEPROM_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        if ( ( cnt + 1 ) == len )
        {
            swieeprom_receive_byte( ctx, &data_out[ cnt ], 1 );
        }
        else
        {
            swieeprom_receive_byte( ctx, &data_out[ cnt ], 0 );
        }
    }
    ctx->swi_start_stop ( );
    return SWIEEPROM_OK;
}

err_t swieeprom_mem_clear ( swieeprom_t *ctx )
{
    uint8_t data_buf[ 8 ] = { 0 };
    for ( uint8_t cnt = 0; cnt < 128; cnt += 8 )
    {
        if ( SWIEEPROM_ERROR == swieeprom_mem_write_page ( ctx, cnt, data_buf, 8 ) )
        {
            return SWIEEPROM_ERROR;
        }
    }
    return SWIEEPROM_OK;
}

static uint8_t swieeprom_send_byte ( swieeprom_t *ctx, uint8_t byte_to_send )
{
    for ( uint8_t bit_mask = 0x80; bit_mask >= 1; bit_mask >>= 1 )
    {
        if ( bit_mask & byte_to_send )
        {
            ctx->swi_logic_1 ( );
        }
        else
        {
            ctx->swi_logic_0 ( );
        }
    }
    return ctx->swi_logic_read ( );
}

static void swieeprom_receive_byte ( swieeprom_t *ctx, uint8_t *byte_to_receive, uint8_t ack_nack )
{
    for ( uint8_t bit_mask = 0x80; bit_mask >= 1; bit_mask >>= 1 )
    {
        if ( ctx->swi_logic_read ( ) )
        {
            *byte_to_receive |= bit_mask;
        }
    }
    if ( ack_nack )
    {
        ctx->swi_logic_1 ( );
    }
    else
    {
        ctx->swi_logic_0 ( );
    }
}

static err_t swieeprom_scan_devices ( swieeprom_t *ctx )
{
    uint8_t slave_cnt = 0;
    uint8_t slave_adr = 0;
    for ( slave_cnt = 0; slave_cnt < 7; slave_cnt++ )
    {
        slave_adr = slave_cnt << 1;
        ctx->swi_start_stop ( );
        if ( SWIEEPROM_OK == swieeprom_send_byte( ctx, SWIEEPROM_OP_CODE_EEPROM | slave_adr ) )
        {
            ctx->slave_address = slave_adr;
            ctx->swi_start_stop ( );
            return SWIEEPROM_OK;
        }
        ctx->swi_start_stop ( );
    }
    return SWIEEPROM_ERROR;
}

// ------------------------------------------------------------------------- END

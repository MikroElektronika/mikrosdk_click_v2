/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file uniqueid2.c
 * @brief UNIQUE ID 2 Click Driver.
 */

#include "uniqueid2.h"

void uniqueid2_cfg_setup ( uniqueid2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wc = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = UNIQUEID2_DEVICE_ADDRESS_MEM;
}

err_t uniqueid2_init ( uniqueid2_t *ctx, uniqueid2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wc, cfg->wc );

    /* Keep the memory write protected by default */
    digital_out_high( &ctx->wc );

    return I2C_MASTER_SUCCESS;
}

err_t uniqueid2_default_cfg ( uniqueid2_t *ctx ) 
{
    err_t error_flag = UNIQUEID2_OK;
    uint8_t dti = 0;
    uint8_t uid[ UNIQUEID2_UID_LEN ] = { 0 };

    /* Keep the memory write protected, do not touch any lock bit */
    uniqueid2_set_wc_pin( ctx, UNIQUEID2_WC_WRITE_DISABLE );

    /* Verify device identity through the read only DTI register */
    error_flag |= uniqueid2_read_register( ctx, UNIQUEID2_REG_DTI, &dti );
    if ( UNIQUEID2_DTI_DEFAULT != dti )
    {
        return UNIQUEID2_ERROR;
    }

    /* Verify communication through the fixed UID header bytes */
    error_flag |= uniqueid2_read_uid( ctx, uid );

    if ( ( UNIQUEID2_UID_HEADER_ST_CODE != uid[ 0 ] )      || 
         ( UNIQUEID2_UID_HEADER_BUS_PROTOCOL != uid[ 1 ] ) ||
         ( UNIQUEID2_UID_HEADER_DENSITY != uid[ 2 ] ) )
    {
        return UNIQUEID2_ERROR;
    }

    return error_flag;
}

err_t uniqueid2_write_memory ( uniqueid2_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len )
{
    /* Byte write frame: S | sl_addr + W | A | addr_MSB | A | addr_LSB | A | data_byte | NA | P 
     * Page write frame: S | sl_addr + W | A | addr_MSB | A | addr_LSB | A | data_1 | A | ... data_N | NA | P */
    err_t error_flag = UNIQUEID2_OK;
    uint8_t data_buf[ UNIQUEID2_PAGE_SIZE + 2 ] = { 0 };
    uint8_t slave_address = 0;
    uint16_t cnt = 0;

    if ( NULL == data_in )
    {
        return UNIQUEID2_ERROR;
    }

    /* Verify that the start address is within bounds and that the write does not cross a page boundary
     * address[17:16] -> block selector bits (to select one of four 64kB memory blocks)
     * address[15:8]  -> page number inside the selected memory block
     * address[7:0]   -> page offset */
    if ( ( address >= UNIQUEID2_MEMORY_SIZE ) || ( ( ( address & UNIQUEID2_PAGE_OFFSET_MASK ) + len ) > UNIQUEID2_PAGE_SIZE ) )
    {
        return UNIQUEID2_ERROR;
    }

    /* I2C device address structure: 
     *    bit[7]   = 0
     *    bit[6:3] = memory/register selector (1010-memory access, 1011-register access)
     *    bit[2]   = 0
     *    bit[1:0] = memory_address[17:16], select one of four 64kB memory blocks(00b for register access) */
    slave_address = UNIQUEID2_DEVICE_ADDRESS_MEM | ( uint8_t ) ( ( address >> UNIQUEID2_BLOCK_OFFSET ) & UNIQUEID2_BLOCK_MASK );
                    
    /* Two address bytes (A15:A0) followed by the data payload, MSB first */
    data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    
    /* Write enable */
    uniqueid2_set_wc_pin( ctx, UNIQUEID2_WC_WRITE_ENABLE );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, slave_address );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 2 );

    /* Wait for internal write cycle to finish before disabling writing, tW max is 4ms  */
    Delay_10ms( );
    uniqueid2_set_wc_pin( ctx, UNIQUEID2_WC_WRITE_DISABLE );

    return error_flag;
}

err_t uniqueid2_read_memory ( uniqueid2_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    err_t error_flag = UNIQUEID2_OK;
    uint8_t addr_buf[ 2 ] = { 0 };
    uint8_t slave_address = 0;
    uint32_t block_size = UNIQUEID2_BLOCK_SIZE;
    uint32_t curr_address = 0;
    uint32_t block_offset = 0;
    uint32_t block_data_left = 0;
    uint32_t bytes_done = 0;

    if ( NULL == data_out )
    {
        return UNIQUEID2_ERROR;
    }

    /* Verify that the read range does not exceed the memory bounds */
    if ( ( address + len ) > UNIQUEID2_MEMORY_SIZE )
    {
        return UNIQUEID2_ERROR;
    }

    /* Memory address structure:
     *     address[17:16] -> block selector bits (to select one of four 64kB memory blocks)
     *     address[15:8]  -> page number inside the selected memory block
     *     address[7:0]   -> page offset
     * 
     * A single memory access must stay within one block => split the read if needed */
    while ( bytes_done < len )
    {
        /* Current address to be read */
        curr_address = address + bytes_done;

        /* Offset within the current block */
        block_offset = curr_address & UNIQUEID2_BLOCK_ADDR_MASK;

        /* Remaining bytes in the current block */
        block_data_left = block_size - block_offset;
        
        /* Check if there is data left in the current block that need to be read */
        if ( block_data_left > ( len - bytes_done ) )
        {
            block_data_left = len - bytes_done;
        }

        /* I2C device address structure: 
         *    bit[7]   = 0
         *    bit[6:3] = memory/register selector (1010-memory access, 1011-register access)
         *    bit[2]   = 0
         *    bit[1:0] = memory_address[17:16], select one of four 64kB memory blocks(00b for register access) */
        slave_address = UNIQUEID2_DEVICE_ADDRESS_MEM | ( uint8_t ) ( ( curr_address >> UNIQUEID2_BLOCK_OFFSET ) & UNIQUEID2_BLOCK_MASK );
                        
        error_flag |= i2c_master_set_slave_address( &ctx->i2c, slave_address );

        addr_buf[ 0 ] = ( uint8_t ) ( ( curr_address >> 8 ) & 0xFF );
        addr_buf[ 1 ] = ( uint8_t ) ( curr_address & 0xFF );

        error_flag |= i2c_master_write_then_read( &ctx->i2c, addr_buf, 2, &data_out[ bytes_done ], block_data_left );

        bytes_done += block_data_left;
    }

    return error_flag;
}

err_t uniqueid2_write_register ( uniqueid2_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = UNIQUEID2_OK;
    uint8_t data_buf[ 3 ] = { 0 };

    /* Register write frame : S | sl_addr + W | A | addr_MSB | A | addr_LSB | A | data_byte | A | P 
     * addr_MSB[7:5] -> these 3 bits code which register is being written to
     * addr_MSB[4:0] -> dont care bits
     * addr_LSB[7:0] -> dont care bits */
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = 0x00;
    data_buf[ 2 ] = data_in;

    uniqueid2_set_wc_pin( ctx, UNIQUEID2_WC_WRITE_ENABLE );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, UNIQUEID2_DEVICE_ADDRESS_REG );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 3 );
    
    /* Wait for internal write cycle to finish before disabling writing, tW max is 4ms  */
    Delay_10ms( );
    uniqueid2_set_wc_pin( ctx, UNIQUEID2_WC_WRITE_DISABLE );

    return error_flag;
}

err_t uniqueid2_read_register ( uniqueid2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = UNIQUEID2_OK;
    uint8_t addr_buf[ 2 ] = { 0 };

    if ( NULL == data_out )
    {
        return UNIQUEID2_ERROR;
    }

    error_flag |= i2c_master_set_slave_address( &ctx->i2c, UNIQUEID2_DEVICE_ADDRESS_REG );

    /* Register read frame : S | sl_addr + W | A | addr_MSB | A | addr_LSB | A | RS | sl_addr + R | data_out | A | P 
     * addr_MSB[7:5] -> register selector bits
     * addr_MSB[4:0] -> dont care bits
     * addr_LSB[7:0] -> dont care bits */
    addr_buf[ 0 ] = reg;
    addr_buf[ 1 ] = 0x00;

    error_flag |= i2c_master_write_then_read( &ctx->i2c, addr_buf, 2, data_out, 1 );

    return error_flag;
}

err_t uniqueid2_read_id_page ( uniqueid2_t *ctx, uint8_t offset, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = UNIQUEID2_OK;
    uint8_t addr_buf[ 2 ] = { 0 };

    if ( NULL == data_out )
    {
        return UNIQUEID2_ERROR;
    }

    /* Verify that the read range does not exceed the identification page bounds */
    if ( ( ( uint16_t ) offset + len ) > UNIQUEID2_ID_PAGE_SIZE )
    {
        return UNIQUEID2_ERROR;
    }

    /* Reading identification page uses the same instruction protocol as reading registers:
     *     addr_MSB[7:5] -> register selector bits(000b)
     *     addr_MSB[4:0] -> dont care bits
     *     addr_LSB[7:0] -> offset inside the identification page */
    addr_buf[ 0 ] = UNIQUEID2_SEL_ID_PAGE;
    addr_buf[ 1 ] = offset;

    error_flag |= i2c_master_set_slave_address( &ctx->i2c, UNIQUEID2_DEVICE_ADDRESS_REG );
    error_flag |= i2c_master_write_then_read( &ctx->i2c, addr_buf, 2, data_out, len );

    return error_flag;
}

err_t uniqueid2_read_uid ( uniqueid2_t *ctx, uint8_t *uid )
{
    if ( NULL == uid )
    {
        return UNIQUEID2_ERROR;
    }

    /* The UID occupies the first 16 bytes of the identification page.
     * The first 4 bytes are a fixed header, the remaining 12 bytes are the
     * per-device serial number. */
    return uniqueid2_read_id_page( ctx, 0, uid, UNIQUEID2_UID_LEN );
}

void uniqueid2_set_wc_pin ( uniqueid2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wc, state );
}

// ------------------------------------------------------------------------- END

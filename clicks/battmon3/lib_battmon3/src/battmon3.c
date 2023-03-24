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
 * @file battmon3.c
 * @brief BATT-MON 3 Click Driver.
 */

#include "battmon3.h"
#include "math.h"

/**
 * @brief BATT-MON 3 calculate checksum function.
 * @details This function computes the checksum over an address plus the block of data.
 * @param[in] data_buf : Data buffer.
 * @param[in] data_len : Data length.
 * @return Calculated checksum byte.
 * @note None.
 */
static uint8_t battmon3_calculate_checksum ( uint8_t *data_buf, uint8_t data_len );

/**
 * @brief BATT-MON 3 float to DF function.
 * @details This function converts the floating point CC Gain and CC Delta values to 
 * the format recognized by the gauge.
 * @param[in] val : Floating point value.
 * @param[out] result : Result buffer [ 4 bytes ].
 * @return None.
 * @note None.
 */
static void battmon3_float_to_df ( float val, uint8_t *result );

void battmon3_cfg_setup ( battmon3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTMON3_DEVICE_ADDRESS;
}

err_t battmon3_init ( battmon3_t *ctx, battmon3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->alr, cfg->alr );
    
    digital_out_low ( &ctx->en );

    return I2C_MASTER_SUCCESS;
}

err_t battmon3_default_cfg ( battmon3_t *ctx ) 
{
    err_t error_flag = BATTMON3_OK;

    Delay_100ms ( );
    battmon3_set_en_pin_high ( ctx );
    // Wait for Alert to go low indicating the chip power up
    while ( battmon3_get_alert_pin ( ctx ) );
    
    if ( BATTMON3_ERROR == battmon3_check_communication( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    
    if ( BATTMON3_ERROR == battmon3_reset ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    
    // Get security mode & status
    if ( BATTMON3_ERROR == battmon3_read_security_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    
    uint16_t status;
    if ( BATTMON3_ERROR == battmon3_read_status ( ctx, &status ) )
    {
        return BATTMON3_ERROR;
    }
    
    // Wait for initialization
    if ( !( status & BATTMON3_STATUS_INIT_COMP_BIT_MASK ) )
    {
        if ( BATTMON3_ERROR == battmon3_wait_for_status ( ctx, BATTMON3_STATUS_INIT_COMP_BIT_MASK, 
                                                               BATTMON3_STATUS_INIT_COMP_BIT_MASK ) )
        {
            return BATTMON3_ERROR;
        }
    }
    
    ctx->enabled = status & BATTMON3_STATUS_GA_BIT_MASK;
    
    error_flag |= battmon3_set_security_mode ( ctx, BATTMON3_SECURITY_MODE_UNSEALED );
    
    error_flag |= battmon3_set_gauge_mode ( ctx, BATTMON3_GAUGE_MODE_ACCUMULATOR );
    
    error_flag |= battmon3_start_gauge ( ctx );
    Delay_1sec ( );
    
    error_flag |= battmon3_use_internal_temperature ( ctx );
    
    error_flag |= battmon3_set_security_mode ( ctx, BATTMON3_SECURITY_MODE_SEALED );
    
    return error_flag;
}

err_t battmon3_generic_write ( battmon3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }

    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
    Delay_1ms ( );
    Delay_1ms ( );
    return error_flag;
}

err_t battmon3_generic_read ( battmon3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
    Delay_1ms ( );
    Delay_1ms ( );
    return error_flag;
}

err_t battmon3_write_two_bytes ( battmon3_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF ); 
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF ); 
    return battmon3_generic_write ( ctx, reg, data_buf, 2 );
}

err_t battmon3_read_two_bytes ( battmon3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, reg, data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_write_control ( battmon3_t *ctx, uint16_t control )
{
    return battmon3_write_two_bytes ( ctx, BATTMON3_REG_CONTROL, control );
}

err_t battmon3_read_control ( battmon3_t *ctx, uint16_t control, uint16_t *data_out )
{
    uint16_t answer;
    if ( BATTMON3_OK == battmon3_write_control ( ctx, control ) )
    {
        if ( BATTMON3_OK == battmon3_read_two_bytes ( ctx, BATTMON3_REG_MAC_DATA, &answer ) )
        {
            *data_out = answer;
            return BATTMON3_OK;
        }
    }
    return BATTMON3_ERROR;
}

err_t battmon3_write_data_flash ( battmon3_t *ctx, uint16_t address, uint8_t *tx_buf, uint8_t tx_len )
{
    if ( ( tx_len > 32 ) || ( address < 0x4000 ) || ( address > 0x43FF ) || ( NULL == tx_buf ) )
    {
        return BATTMON3_ERROR;
    }
    uint8_t current_mode = ctx->security_mode;
    err_t error_flag = BATTMON3_ERROR;
    uint8_t data_buf[ 2 + 32 ] = { 0 };
    // Handle security mode
    if ( BATTMON3_SECURITY_MODE_UNSEALED != ctx->security_mode )
    {
        if ( BATTMON3_ERROR == battmon3_set_security_mode ( ctx, BATTMON3_SECURITY_MODE_UNSEALED ) )
        {
            return BATTMON3_ERROR;
        }
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( address & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    memcpy ( &data_buf[ 2 ], tx_buf, tx_len );
    Delay_1sec ( );
    if ( BATTMON3_OK == battmon3_generic_write( ctx, BATTMON3_REG_MAC, data_buf, tx_len + 2 ) )
    {
        // Compute the checksum and write it to MACDataSum (0x60)
        data_buf[ 0 ] = battmon3_calculate_checksum( data_buf, tx_len + 2 );
        if ( BATTMON3_OK == battmon3_generic_write ( ctx, BATTMON3_REG_MAC_DATA_SUM, data_buf, 1 ) )
        {
            // Write 4 + length to MACDataLen (0x61)
            data_buf[ 0 ] = tx_len + 4;
            if ( BATTMON3_OK == battmon3_generic_write ( ctx, BATTMON3_REG_MAC_DATA_LEN, data_buf, 1 ) )
            {
                Delay_100ms ( );
                // Read the control status register to see if a bad
                // flash write has been detected (bit 15)
                uint16_t status;
                if ( BATTMON3_OK == battmon3_read_status( ctx, &status ) )
                {
                    if ( BATTMON3_STATUS_FLASHF_BIT_MASK != ( status & BATTMON3_STATUS_FLASHF_BIT_MASK ) )
                    {
                        error_flag = BATTMON3_OK;
                    }
                }
            }
        }
    }
    
    if ( current_mode != ctx->security_mode )
    {
        if ( BATTMON3_ERROR == battmon3_set_security_mode ( ctx, current_mode ) )
        {
            return BATTMON3_ERROR;
        }
    }
    
    return error_flag;
}

err_t battmon3_read_data_flash ( battmon3_t *ctx, uint16_t address, uint8_t *rx_buf, uint8_t rx_len )
{
    if ( ( rx_len > 32 ) || ( address < 0x4000 ) || ( address > 0x43FF ) || ( NULL == rx_buf ) )
    {
        return BATTMON3_ERROR;
    }
    uint8_t current_mode = ctx->security_mode;
    err_t error_flag = BATTMON3_ERROR;
    uint8_t data_buf[ 32 + 2 + 2 ] = { 0 }; // 32 bytes of data, 2 bytes of address,
                                            // 1 byte of MACDataSum and 1 byte of MACDataLen
    // Handle security mode
    if ( BATTMON3_SECURITY_MODE_UNSEALED != ctx->security_mode )
    {
        if ( BATTMON3_ERROR == battmon3_set_security_mode ( ctx, BATTMON3_SECURITY_MODE_UNSEALED ) )
        {
            return BATTMON3_ERROR;
        }
    }
    Delay_1sec ( );
    if ( BATTMON3_OK == battmon3_write_two_bytes( ctx, BATTMON3_REG_MAC, address ) )
    {
        // Read the address from ManufacturerAccessControl (0x3e then 0x3f),
        // data from MACData (0x40 to 0x5f), checksum from MACDataSum (0x60) 
        // and length from MACDataLen (0x61)
        if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_MAC, data_buf, 36 ) )
        {
            // Check that the address matches
            if ( ( data_buf[ 0 ] == ( uint8_t ) ( address & 0xFF ) ) && 
                 ( data_buf[ 1 ] == ( uint8_t ) ( ( address >> 8 ) & 0xFF ) ) )
            {
                // Check that the checksum matches (-2 on MACDataLen as it includes MACDataSum and itself)
                if ( data_buf[ 34 ] == battmon3_calculate_checksum ( data_buf, data_buf[ 35 ] - 2 ) )
                {
                    // -4 rather than -2 to remove the two bytes of address as well
                    uint8_t length_read = data_buf[ 35 ] - 4;
                    if ( length_read > rx_len )
                    {
                        length_read = rx_len;
                    }
                    memcpy ( rx_buf, &data_buf[ 2 ], length_read );
                    error_flag = BATTMON3_OK;
                }
            }
        }
    }
    
    if ( current_mode != ctx->security_mode )
    {
        if ( BATTMON3_ERROR == battmon3_set_security_mode ( ctx, current_mode ) )
        {
            return BATTMON3_ERROR;
        }
    }
    return error_flag;
}

err_t battmon3_check_communication ( battmon3_t *ctx )
{
    uint16_t chem_id;
    if ( BATTMON3_OK == battmon3_read_control( ctx, BATTMON3_CONTROL_CHEM_ID, &chem_id ) )
    {
        if ( BATTMON3_CHEM_ID == chem_id )
        {
            return BATTMON3_OK;
        }
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_status ( battmon3_t *ctx, uint16_t *status )
{
    uint16_t answer;
    if ( BATTMON3_OK == battmon3_read_two_bytes ( ctx, BATTMON3_REG_CONTROL, &answer ) )
    {
        *status = answer;
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_wait_for_status ( battmon3_t *ctx, uint16_t mask, uint16_t status )
{
    uint16_t answer;
    for ( uint16_t timeout_cnt = 0; timeout_cnt < 100; timeout_cnt++ )
    {
        if ( BATTMON3_ERROR == battmon3_read_status ( ctx, &answer ) )
        {
            return BATTMON3_ERROR;
        }
        if ( ( answer & mask ) == status )
        {
            return BATTMON3_OK;
        }
        Delay_100ms ( );
    }
    return BATTMON3_ERROR;
}

void battmon3_set_en_pin_high ( battmon3_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void battmon3_set_en_pin_low ( battmon3_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t battmon3_get_alert_pin ( battmon3_t *ctx )
{
    return digital_in_read ( &ctx->alr );
}

err_t battmon3_start_gauge ( battmon3_t *ctx )
{
    if ( true == ctx->enabled )
    {
        return BATTMON3_OK;
    }
    
    if ( BATTMON3_OK == battmon3_write_control( ctx, BATTMON3_CONTROL_GAUGE_START ) )
    {
        if ( BATTMON3_OK == battmon3_wait_for_status( ctx, BATTMON3_STATUS_GA_BIT_MASK, 
                                                           BATTMON3_STATUS_GA_BIT_MASK ) )
        {
            ctx->enabled = true;
            return BATTMON3_OK;
        }
    }
    ctx->enabled = false;
    return BATTMON3_ERROR;
}

err_t battmon3_stop_gauge ( battmon3_t *ctx )
{
    if ( false == ctx->enabled )
    {
        return BATTMON3_OK;
    }
    
    if ( BATTMON3_OK == battmon3_write_control( ctx, BATTMON3_CONTROL_GAUGE_STOP ) )
    {
        if ( BATTMON3_OK == battmon3_wait_for_status( ctx, BATTMON3_STATUS_GA_BIT_MASK, 0 ) )
        {
            ctx->enabled = false;
            return BATTMON3_OK;
        }
    }
    ctx->enabled = true;
    return BATTMON3_ERROR;
}

err_t battmon3_disable_gauge ( battmon3_t *ctx )
{
    if ( BATTMON3_ERROR == battmon3_stop_gauge ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_wait_for_status( ctx, BATTMON3_STATUS_G_DONE_BIT_MASK, 
                                                          BATTMON3_STATUS_G_DONE_BIT_MASK ) )
    {
        return BATTMON3_ERROR;
    }
    battmon3_set_en_pin_low ( ctx );
    return BATTMON3_OK;
}

err_t battmon3_set_gauge_mode ( battmon3_t *ctx, uint8_t gauge_mode )
{
    err_t error_flag = BATTMON3_OK;
    if ( gauge_mode > BATTMON3_GAUGE_MODE_UNKNOWN )
    {
        return BATTMON3_ERROR;
    }
    uint8_t op_config;
    // Get the Operation Config A
    if ( BATTMON3_ERROR == battmon3_read_data_flash ( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &op_config, 1 ) )
    {
        return BATTMON3_ERROR;
    }
    
    // Set the mode (GMSEL 1:0)
    if ( gauge_mode != ( op_config & BATTMON3_OP_CONFIG_A_GMSEL_BIT_MASK ) )
    {
        op_config &= ~BATTMON3_OP_CONFIG_A_GMSEL_BIT_MASK;
        op_config |= gauge_mode;
        Delay_100ms( );
        if ( BATTMON3_ERROR == battmon3_write_data_flash ( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &op_config, 1 ) )
        {
            return BATTMON3_ERROR;
        }
    }
    return BATTMON3_OK;
}

err_t battmon3_reset ( battmon3_t *ctx )
{
    uint8_t security_mode = ctx->security_mode;
    if ( BATTMON3_SECURITY_MODE_UNSEALED != ctx->security_mode )
    {
        if ( BATTMON3_ERROR == battmon3_set_security_mode ( ctx, BATTMON3_SECURITY_MODE_UNSEALED ) )
        {
            return BATTMON3_ERROR;
        }
    }
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_RESET ) )
    {
        return BATTMON3_ERROR;
    }
    Delay_1sec ( );
    if ( ( security_mode >= BATTMON3_SECURITY_MODE_FULL_ACCESS ) && 
         ( security_mode <= BATTMON3_SECURITY_MODE_SEALED ) && 
         ( security_mode == ctx->security_mode ) )
    {
        if ( BATTMON3_ERROR == battmon3_set_security_mode ( ctx, security_mode ) )
        {
            return BATTMON3_ERROR;
        }
    }
    
    return BATTMON3_OK;
}

err_t battmon3_read_security_mode ( battmon3_t *ctx )
{
    uint16_t status;
    if ( BATTMON3_OK == battmon3_read_status ( ctx, &status ) )
    {
        // Bits 13 and 14 of the high byte represent the security status,
        // 01 = full access
        // 10 = unsealed access
        // 11 = sealed access
        ctx->security_mode = ( uint8_t ) ( ( status >> 13 ) & 0x03 );
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_set_security_mode ( battmon3_t *ctx, uint8_t security_mode )
{
    err_t error_flag = BATTMON3_OK;
    if ( ( BATTMON3_SECURITY_MODE_UNKNOWN == security_mode ) || 
         ( security_mode > BATTMON3_SECURITY_MODE_SEALED ) )
    {
        return BATTMON3_ERROR;
    }
    if ( ctx->security_mode == security_mode )
    {
        return BATTMON3_OK;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    // Try to change the mode up to 30 times in the next 3 seconds
    for ( uint8_t timeout_cnt = 0; timeout_cnt < 30; timeout_cnt++ )
    {
        data_buf[ 0 ] = BATTMON3_REG_MAC;
        switch ( security_mode )
        {
            case BATTMON3_SECURITY_MODE_FULL_ACCESS:
            {
                // Unseal first if in Sealed mode
                if ( ctx->security_mode == BATTMON3_SECURITY_MODE_SEALED ) 
                {
                    security_mode = BATTMON3_SECURITY_MODE_UNSEALED;
                    continue;
                }
                
                // Code snippet from battmon3_read_data_flash to avoid cross-calling
                err_t tmp_error_flag = BATTMON3_ERROR;
                uint8_t tmp_data_buf[ 32 + 2 + 2 ] = { 0 }; // 32 bytes of data, 2 bytes of address,
                                                            // 1 byte of MACDataSum and 1 byte of MACDataLen
                Delay_1sec ( );
                if ( BATTMON3_OK == battmon3_write_two_bytes( ctx, BATTMON3_REG_MAC, BATTMON3_DF_FULL_UNSEAL_STEP_1 ) )
                {
                    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_MAC, tmp_data_buf, 36 ) )
                    {
                        // Check that the address matches
                        if ( ( tmp_data_buf[ 0 ] == ( uint8_t ) ( BATTMON3_DF_FULL_UNSEAL_STEP_1 & 0xFF ) ) && 
                             ( tmp_data_buf[ 1 ] == ( uint8_t ) ( ( BATTMON3_DF_FULL_UNSEAL_STEP_1 >> 8 ) & 0xFF ) ) )
                        {
                            // Check that the checksum matches (-2 on MACDataLen as it includes MACDataSum and itself)
                            if ( tmp_data_buf[ 34 ] == battmon3_calculate_checksum ( tmp_data_buf, tmp_data_buf[ 35 ] - 2 ) )
                            {
                                // -4 rather than -2 to remove the two bytes of address as well
                                uint8_t length_read = tmp_data_buf[ 35 ] - 4;
                                if ( length_read > 4 )
                                {
                                    length_read = 4;
                                }
                                memcpy ( data_buf, &tmp_data_buf[ 2 ], length_read );
                                tmp_error_flag = BATTMON3_OK;
                            }
                        }
                    }
                }
                if ( BATTMON3_ERROR == tmp_error_flag )
                {
                    return BATTMON3_ERROR;
                }
                uint32_t full_access_codes = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                                             ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
                error_flag |= battmon3_write_two_bytes( ctx, BATTMON3_REG_MAC, 
                                                        ( uint16_t ) ( ( full_access_codes >> 16 ) & 0xFFFF ) );
                if ( BATTMON3_OK == error_flag )
                {
                    error_flag |= battmon3_write_two_bytes( ctx, BATTMON3_REG_MAC, 
                                                            ( uint16_t ) ( full_access_codes & 0xFFFF ) );
                }
                break;
            }
            case BATTMON3_SECURITY_MODE_UNSEALED:
            {
                // Seal first if in Full Access mode
                if ( ctx->security_mode == BATTMON3_SECURITY_MODE_FULL_ACCESS ) 
                {
                    security_mode = BATTMON3_SECURITY_MODE_SEALED;
                    continue;
                }
                error_flag |= battmon3_write_two_bytes( ctx, BATTMON3_REG_MAC, 
                                                        ( uint16_t ) ( ( BATTMON3_SEAL_CODES_DEFAULT >> 16 ) & 0xFFFF ) );
                if ( BATTMON3_OK == error_flag )
                {
                    error_flag |= battmon3_write_two_bytes( ctx, BATTMON3_REG_MAC, 
                                                            ( uint16_t ) ( BATTMON3_SEAL_CODES_DEFAULT & 0xFFFF ) );
                }
                break;
            }
            case BATTMON3_SECURITY_MODE_SEALED:
            {
                error_flag |= battmon3_write_control( ctx, BATTMON3_CONTROL_SEALED );
                break;
            }
        }
        error_flag |= battmon3_read_security_mode ( ctx );
        
        if ( ( BATTMON3_OK == error_flag ) && ( ctx->security_mode == security_mode ) )
        {
            return BATTMON3_OK;
        }
        Delay_100ms ( );
    }
    return BATTMON3_ERROR;
}

err_t battmon3_new_battery ( battmon3_t *ctx, uint16_t des_capacity )
{
    if ( ( 0 != des_capacity ) && ( BATTMON3_ERROR == battmon3_set_design_capacity ( ctx, des_capacity ) ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_NEW_BATTERY ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_set_design_capacity ( battmon3_t *ctx, uint16_t des_capacity )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( des_capacity >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( des_capacity & 0xFF );
    // Write to the "Cell Design Capacity mAh" address in data flash
    return battmon3_write_data_flash ( ctx, BATTMON3_DF_CELL_DESIGN_CAPACITY, data_buf, 2 );
}

err_t battmon3_read_design_capacity ( battmon3_t *ctx, uint16_t *des_capacity )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_DESIGN_CAPACITY, data_buf, 2 ) )
    {
        *des_capacity = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_used_capacity ( battmon3_t *ctx, float *used_capacity )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_ACCUMULATED_CAPACITY, data_buf, 4 ) )
    {
        int32_t raw_data = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) |
                           ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        // Convert from uAh to mAh and invert the sign
        // It's counted from zero minus used capacity hence the result is "inverted".
        *used_capacity = ( raw_data * -0.001 ); // uAh to mAh 
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_remaining_capacity ( battmon3_t *ctx, float *rem_capacity )
{
    uint16_t des_capacity;
    float used_capacity;
    if ( BATTMON3_ERROR == battmon3_read_design_capacity ( ctx, &des_capacity ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_read_used_capacity ( ctx, &used_capacity ) )
    {
        return BATTMON3_ERROR;
    }
    if ( used_capacity < 0 )
    {
        used_capacity = 0;
    }
    if ( used_capacity > des_capacity )
    {
        used_capacity = des_capacity;
    }
    *rem_capacity = ( float ) des_capacity - used_capacity;
    return BATTMON3_OK;
}

err_t battmon3_read_remaining_percentage ( battmon3_t *ctx, float *rem_percentage )
{
    uint16_t des_capacity;
    float used_capacity;
    if ( BATTMON3_ERROR == battmon3_read_design_capacity ( ctx, &des_capacity ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_read_used_capacity ( ctx, &used_capacity ) )
    {
        return BATTMON3_ERROR;
    }
    if ( used_capacity < 0 )
    {
        used_capacity = 0;
    }
    if ( used_capacity > des_capacity )
    {
        used_capacity = des_capacity;
    }
    *rem_percentage = ( ( float ) des_capacity - used_capacity ) / des_capacity;
    *rem_percentage *= 100.0; // Scale to 100 percent
    return BATTMON3_OK;
}

err_t battmon3_use_internal_temperature ( battmon3_t *ctx )
{
    // Get the Operation Config A
    uint8_t raw_data;
    if ( BATTMON3_ERROR == battmon3_read_data_flash( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &raw_data, 1 ) )
    {
        return BATTMON3_ERROR;
    }
    
    if ( BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK == ( raw_data & BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK ) )
    {
        raw_data &= ~BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK;
        Delay_100ms ( );
        if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &raw_data, 1 ) )
        {
            return BATTMON3_ERROR;
        }
    }
    return BATTMON3_OK;
}

err_t battmon3_use_external_temperature ( battmon3_t *ctx )
{
    // Get the Operation Config A
    uint8_t raw_data;
    if ( BATTMON3_ERROR == battmon3_read_data_flash( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &raw_data, 1 ) )
    {
        return BATTMON3_ERROR;
    }
    
    if ( BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK != ( raw_data & BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK ) )
    {
        raw_data |= BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK;
        Delay_100ms ( );
        if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &raw_data, 1 ) )
        {
            return BATTMON3_ERROR;
        }
    }
    return BATTMON3_OK;
}

err_t battmon3_read_temperature ( battmon3_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_TEMPERATURE, data_buf, 2 ) )
    {
        int16_t raw_data = ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        *temperature = ( raw_data * 0.1 ) - 273.15; // 0.1 resolution in Kelvin, 273.15 Kelvin to Celsius
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_internal_temperature ( battmon3_t *ctx, float *int_temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_INTERNAL_TEMPERATURE, data_buf, 2 ) )
    {
        int16_t raw_data = ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        *int_temperature = ( raw_data * 0.1 ) - 273.15; // 0.1 resolution in Kelvin, 273.15 Kelvin to Celsius
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_voltage ( battmon3_t *ctx, uint16_t *voltage )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_VOLTAGE, data_buf, 2 ) )
    {
        *voltage = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_current ( battmon3_t *ctx, int16_t *current )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_CURRENT, data_buf, 2 ) )
    {
        *current = ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_scaled_r ( battmon3_t *ctx, uint16_t *scaled_r )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_SCALED_R, data_buf, 2 ) )
    {
        *scaled_r = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_measured_z ( battmon3_t *ctx, uint16_t *measured_z )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_MEASURED_Z, data_buf, 2 ) )
    {
        *measured_z = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_state_of_health ( battmon3_t *ctx, uint8_t *state_of_health )
{
    uint8_t reg_data;
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_STATE_OF_HEALTH, &reg_data, 1 ) )
    {
        *state_of_health = reg_data;
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_battery_status ( battmon3_t *ctx, uint8_t *batt_status )
{
    uint8_t reg_data;
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_BATTERY_STATUS, &reg_data, 1 ) )
    {
        *batt_status = reg_data;
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_read_battery_alert ( battmon3_t *ctx, uint8_t *batt_alert )
{
    uint8_t reg_data;
    if ( BATTMON3_OK == battmon3_generic_read ( ctx, BATTMON3_REG_BATTERY_ALERT, &reg_data, 1 ) )
    {
        *batt_alert = reg_data;
        return BATTMON3_OK;
    }
    return BATTMON3_ERROR;
}

err_t battmon3_enter_calibration_mode ( battmon3_t *ctx )
{
    Delay_1sec ( );
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_ENTER_CAL ) )
    {
        return BATTMON3_ERROR;
    }

    if ( BATTMON3_ERROR == battmon3_wait_for_status ( ctx, BATTMON3_STATUS_CAL_MODE_BIT_MASK, 
                                                           BATTMON3_STATUS_CAL_MODE_BIT_MASK ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_exit_calibration_mode ( battmon3_t *ctx )
{
    Delay_1sec ( );
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_EXIT_CAL ) )
    {
        return BATTMON3_ERROR;
    }
        
    if ( BATTMON3_ERROR == battmon3_wait_for_status ( ctx, BATTMON3_STATUS_CAL_MODE_BIT_MASK, 0 ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_read_raw_calibration_data ( battmon3_t *ctx, uint8_t reg, uint16_t *cal_data )
{
    if ( ( reg < BATTMON3_REG_CAL_CURRENT ) || ( reg > BATTMON3_REG_CAL_TEMPERATURE ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_enter_calibration_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    uint32_t avg_data = 0;
    uint16_t raw_data = 0;
    uint8_t adc_count = 0;
    uint8_t adc_count_prev = 0;
    uint8_t cnt = 0;
    while ( cnt < 4 )
    {
        Delay_100ms ( );
        Delay_100ms ( );
        if ( BATTMON3_ERROR == battmon3_generic_read ( ctx, BATTMON3_REG_CAL_COUNT, &adc_count, 1 ) )
        {
            return BATTMON3_ERROR;
        }
        if ( adc_count_prev == adc_count )
        {
            continue;
        }
        adc_count_prev = adc_count;
        
        if ( BATTMON3_ERROR == battmon3_read_two_bytes ( ctx, reg, &raw_data ) )
        {
            return BATTMON3_ERROR;
        }
        avg_data += raw_data;
        cnt++;
    }
    *cal_data = ( uint16_t ) ( avg_data / cnt );
    if ( BATTMON3_ERROR == battmon3_exit_calibration_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_perform_cc_offset ( battmon3_t *ctx )
{
    if ( BATTMON3_ERROR == battmon3_enter_calibration_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    Delay_1sec ( );
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_CC_OFFSET ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_wait_for_status( ctx, BATTMON3_STATUS_CCA_BIT_MASK, 
                                                          BATTMON3_STATUS_CCA_BIT_MASK ) )
    {
        return BATTMON3_ERROR;
    }
    Delay_1sec ( );
    if ( BATTMON3_ERROR == battmon3_wait_for_status( ctx, BATTMON3_STATUS_CCA_BIT_MASK, 0 ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_CC_OFFSET_SAVE ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_exit_calibration_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_perform_board_offset ( battmon3_t *ctx )
{
    if ( BATTMON3_ERROR == battmon3_enter_calibration_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    Delay_1sec ( );
    if ( BATTMON3_ERROR == battmon3_write_control ( ctx, BATTMON3_CONTROL_BOARD_OFFSET ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_wait_for_status( ctx, BATTMON3_STATUS_BCA_BIT_MASK, 
                                                          BATTMON3_STATUS_BCA_BIT_MASK ) )
    {
        return BATTMON3_ERROR;
    }
    Delay_1sec ( );
    if ( BATTMON3_ERROR == battmon3_wait_for_status( ctx, BATTMON3_STATUS_BCA_BIT_MASK, 0 ) )
    {
        return BATTMON3_ERROR;
    }
    if ( BATTMON3_ERROR == battmon3_exit_calibration_mode ( ctx ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_calibrate_voltage ( battmon3_t *ctx, uint16_t voltage )
{
    uint16_t avg_voltage;
    
    if ( BATTMON3_ERROR == battmon3_read_raw_calibration_data ( ctx, BATTMON3_REG_CAL_VOLTAGE, &avg_voltage ) )
    {
        return BATTMON3_ERROR;
    }
    int16_t offset = voltage - avg_voltage;
    
    if ( ( offset < -128 ) || ( offset > 127 ) )
    {
        return BATTMON3_ERROR;
    }
    Delay_1sec ( );
    uint8_t off_data = ( uint8_t ) offset;
    if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_PACK_V_OFFSET, &off_data, 1 ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_calibrate_current ( battmon3_t *ctx, int16_t current )
{
    uint8_t data_buf[ 4 ] = { 0 };
    uint16_t avg_current;
    int16_t cc_offset;
    int8_t board_offset;
    // Get CC offset
    if ( BATTMON3_ERROR == battmon3_read_data_flash( ctx, BATTMON3_DF_CC_OFFSET, data_buf, 2 ) )
    {
        return BATTMON3_ERROR;
    }
    cc_offset = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    
    // Get Board offset
    if ( BATTMON3_ERROR == battmon3_read_data_flash( ctx, BATTMON3_DF_BOARD_OFFSET, data_buf, 1 ) )
    {
        return BATTMON3_ERROR;
    }
    board_offset = ( int8_t ) data_buf[ 0 ];
    Delay_1sec ( );
    
    // Get avg raw current
    if ( BATTMON3_ERROR == battmon3_read_raw_calibration_data ( ctx, BATTMON3_REG_CAL_CURRENT, &avg_current ) )
    {
        return BATTMON3_ERROR;
    }
    float cc_gain = ( float ) ( avg_current - ( cc_offset + board_offset ) / 16 );
    
    if ( 0.0 == cc_gain )
    {
        return BATTMON3_ERROR;
    }
    cc_gain = ( float ) current / cc_gain;
    float cc_delta = cc_gain * 1193046.0;

    // Save CC gain
    battmon3_float_to_df ( cc_gain, data_buf );
    Delay_100ms ( );
    if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_CC_GAIN, data_buf, 4 ) )
    {
        return BATTMON3_ERROR;
    }
    // Save CC delta
    battmon3_float_to_df ( cc_delta, data_buf );
    Delay_100ms ( );
    if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_CC_DELTA, data_buf, 4 ) )
    {
        return BATTMON3_ERROR;
    }
    return BATTMON3_OK;
}

err_t battmon3_calibrate_temperature ( battmon3_t *ctx, float temperature )
{
    // Get the Operation Config A
    uint8_t raw_data;
    if ( BATTMON3_ERROR == battmon3_read_data_flash( ctx, BATTMON3_DF_OPERATION_CONFIG_A, &raw_data, 1 ) )
    {
        return BATTMON3_ERROR;
    }

    // Determine which temperature source is selected
    uint8_t external = raw_data & BATTMON3_OP_CONFIG_A_TEMPS_BIT_MASK;
    Delay_1sec ( );
    
    // Get avg raw temperature
    uint16_t avg_temp;
    if ( BATTMON3_ERROR == battmon3_read_raw_calibration_data ( ctx, BATTMON3_REG_CAL_TEMPERATURE, &avg_temp ) )
    {
        return BATTMON3_ERROR;
    }
    // 273.15 Celsius to Kelvin, 0.1 resolution in Kelvin
    temperature = ( temperature + 273.15 ) / 0.1;
    int16_t offset = ( int16_t ) temperature - avg_temp;
    
    if ( ( offset < -128 ) || ( offset > 127 ) )
    {
        return BATTMON3_ERROR;
    }
    raw_data = ( int8_t ) offset;
    
    // Save offset
    Delay_1sec ( );
    if ( external )
    {
        if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_EXT_TEMP_OFFSET, &raw_data, 1 ) )
        {
            return BATTMON3_ERROR;
        }
    }
    else
    {
        if ( BATTMON3_ERROR == battmon3_write_data_flash( ctx, BATTMON3_DF_INT_TEMP_OFFSET, &raw_data, 1 ) )
        {
            return BATTMON3_ERROR;
        }
    }
    
    return BATTMON3_OK;
}

static uint8_t battmon3_calculate_checksum ( uint8_t *data_buf, uint8_t data_len )
{
    uint8_t checksum = 0;
    for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
    {
        checksum += data_buf[ cnt ];
    }
    return ( 0xFF - checksum );
}

static void battmon3_float_to_df ( float val, uint8_t *result )
{
    int32_t exp = 0;
    float mod_val = val;
    float tmp_val = 0;
    uint8_t data_buf[ 4 ];

    if ( val < 0.0 ) 
    {
        mod_val *= -1.0;
    }

    tmp_val = mod_val;

    tmp_val *= ( 1 + pow ( 2, -25 ) );

    if ( tmp_val < 0.5 ) 
    {
        while ( tmp_val < 0.5 ) 
        {
            tmp_val *= 2;
            exp--;
        }

    } 
    else if ( tmp_val >= 1.0 ) 
    {
        while ( tmp_val >= 1.0 ) 
        {
            tmp_val /= 2;
            exp--;
        }
    }

    if ( exp > 127 ) 
    {
        exp = 127;
    } 
    else if ( exp < -128 ) 
    {
        exp = -128;
    }

    tmp_val = pow ( 2, 8 - exp ) * val - 128;

    result[ 2 ] = ( uint8_t ) tmp_val;
    tmp_val = pow ( 2, 8 ) * ( tmp_val - result[ 2 ] );
    result[ 1 ] = ( uint8_t ) tmp_val;
    tmp_val = pow ( 2, 8 ) * ( tmp_val - result[ 1 ] );
    result[ 0 ] = ( uint8_t ) tmp_val;

    if ( val < 0.0 ) 
    {
        result[ 2 ] |= 0x80;
    }
    result[ 3 ] = exp + 128;
}

// ------------------------------------------------------------------------- END

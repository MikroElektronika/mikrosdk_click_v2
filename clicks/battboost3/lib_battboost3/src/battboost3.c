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
 * @file battboost3.c
 * @brief BATT Boost 3 Click Driver.
 */

#include "battboost3.h"

/**
 * @brief BATT Boost 3 update bits function.
 * @details This function updates selected bits of a selected register by 
 * performing the read-modify-write operation.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Bit mask that selects which bits should be modified.
 * @param[in] value : New value for the selected bits.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t battboost3_update_bits ( battboost3_t *ctx, uint8_t reg, uint8_t mask, uint8_t value );

void battboost3_cfg_setup ( battboost3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTBOOST3_DEVICE_ADDRESS;
}

err_t battboost3_init ( battboost3_t *ctx, battboost3_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t battboost3_default_cfg ( battboost3_t *ctx ) 
{
    err_t error_flag = BATTBOOST3_OK;

    /* Enable the device by setting en pin high */
    battboost3_set_en_pin( ctx, BATTBOOST3_ENABLE );
    Delay_1ms( );

    /* Read DeviceID register to check communication */
    error_flag |= battboost3_check_communication( ctx );

    /* CONFIG register(0x01):
     *     bits[6:5] = 01 -> Device automatically selects boost or bypass operation.
     *
     * VIN > VOUT thr -> device in bypass mode.
     * VIN < VOUT thr -> device in boost mode. */
    error_flag |= battboost3_set_enable_mode( ctx, BATTBOOST3_ENABLE_MODE_AUTO );

    /* CONFIG register(0x01):
     *     bits[1:0] = 00 -> Device operates in Auto PFM mode. */
    error_flag |= battboost3_set_operation_mode( ctx, BATTBOOST3_MODE_AUTO_PFM );

    /* Set VOUT threshold */
    error_flag |= battboost3_set_output_voltage( ctx, 3.4f );

    /* Set average current limit in boost mode to 8A */
    error_flag |= battboost3_set_boost_ilim( ctx, BATTBOOST3_BOOST_ILIM_8A );

    /* Set current limits in forced bypass mode and automatic bypass mode */
    error_flag |= battboost3_set_bypass_ilim( ctx, BATTBOOST3_BYPASS_ILIM_10A, BATTBOOST3_BYPASS_ILIM_10A );

    Delay_10ms( );

    return error_flag;
}

err_t battboost3_write_reg ( battboost3_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return battboost3_write_regs( ctx, reg, &data_in, 1 );
}

err_t battboost3_write_regs ( battboost3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* S | slave_addr + W | A | reg_addr | A | data0 | A | .... dataN | A | P */
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t battboost3_read_reg ( battboost3_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return battboost3_read_regs( ctx, reg, data_out, 1 );
}

err_t battboost3_read_regs ( battboost3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* S | slave_addr + W | A | reg_addr | A | RS | slave_addr + R | A | data0 | A | .... dataN | A | P */
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t battboost3_check_communication ( battboost3_t *ctx )
{
    uint8_t device_id = 0;

    /* Read DeviceID register(0x00):
     *     bits[7:4] -> manufacture ID 
     *     bits[3:0] -> Device ID */ 
    err_t error_flag = battboost3_get_device_id( ctx, &device_id );

    if ( BATTBOOST3_OK != error_flag )
    {
        return error_flag;
    }

    /* Check manufacturer ID bits, expected value is 0111b */
    if ( BATTBOOST3_DEVICE_ID_MFR_VAL != ( device_id & BATTBOOST3_DEVICE_ID_MFR_MASK ) )
    {
        return BATTBOOST3_ERROR;
    }

    return BATTBOOST3_OK;
}

err_t battboost3_get_device_id ( battboost3_t *ctx, uint8_t *device_id )
{
    err_t error_flag = BATTBOOST3_OK;
    
    /* Read DeviceID register(0x00) */
    error_flag |=  battboost3_read_reg( ctx, BATTBOOST3_REG_DEVICE_ID, device_id );

    return  error_flag;
}

err_t battboost3_get_status ( battboost3_t *ctx, uint8_t *status )
{
    err_t error_flag = BATTBOOST3_OK;
    
    /* Read STATUS register(0x05):
     *     bit[7] -> Thermal shutdown status bit.
     *     bit[6] -> OTP test status bit.
     *     bit[5] -> Vout status bit.
     *     bit[4] -> Device mode of operation status bit.
     *     bit[3] -> Current limit status bit(bypass mode).    
     *     bit[2] -> Current limit status bit(boost mode).
     *     bit[1] -> Current limit status bit(boost mode).
     *     bit[0] -> Power Good status bit. */
    error_flag |= battboost3_read_reg( ctx, BATTBOOST3_REG_STATUS, status );

    return error_flag;
}

err_t battboost3_set_enable_mode ( battboost3_t *ctx, uint8_t enable_mode )
{
    err_t error_flag = BATTBOOST3_OK;

    /* Set ENABLE bits[6:5] of CONFIG register(0x01) to desired value */
    error_flag |= battboost3_update_bits( ctx, BATTBOOST3_REG_CONFIG, BATTBOOST3_CONFIG_ENABLE_MASK, enable_mode );

    return error_flag;
}

err_t battboost3_set_operation_mode ( battboost3_t *ctx, uint8_t mode )
{
    err_t error_flag = BATTBOOST3_OK;

    /* Set MODE_CTRL bits[1:0] of CONFIG register(0x01) to desired value */
    error_flag |= battboost3_update_bits( ctx, BATTBOOST3_REG_CONFIG, BATTBOOST3_CONFIG_MODE_CTRL_MASK, mode );

    return error_flag;
}

err_t battboost3_set_output_voltage ( battboost3_t *ctx, float vout )
{
    uint8_t vout_code = 0;
    err_t error_flag = BATTBOOST3_OK;

    if ( ( vout < BATTBOOST3_VOUT_MIN ) || ( vout > BATTBOOST3_VOUT_MAX ) )
    {
        return BATTBOOST3_ERROR;
    }
    

    /* Encode voltage based on the voltage region it is in:
     *     Low voltage region(2.35V to 2.80V) -> encoded in reverse order
     *     Normal voltage region(2.85V to 5.00V) -> encoded in increasing order */
    if ( vout <= BATTBOOST3_VOUT_LOW_MAX )
    {
        vout_code = BATTBOOST3_VOUT_CODE_MAX  - 
                    ( uint8_t ) ( ( ( vout - BATTBOOST3_VOUT_MIN ) / BATTBOOST3_VOUT_STEP ) + BATTBOOST3_VOUT_ROUND_OFFSET );
    }
    else if ( vout >= BATTBOOST3_VOUT_NORMAL_BASE )
    {
        vout_code = ( uint8_t ) ( ( ( vout - BATTBOOST3_VOUT_NORMAL_BASE ) / BATTBOOST3_VOUT_STEP ) + BATTBOOST3_VOUT_ROUND_OFFSET );
    }
    else
    {
        return BATTBOOST3_ERROR;
    }

    /* Write calculated code into THRESHOLD bits[5:0] of the VOUTFLOORSET register(0x02). */
    error_flag |= battboost3_write_reg( ctx, BATTBOOST3_REG_VOUT_FLOOR_SET, vout_code );

    return error_flag;
}

err_t battboost3_set_boost_ilim ( battboost3_t *ctx, uint8_t ilim )
{
    err_t error_flag = BATTBOOST3_OK;

    /* Set ILIM_BOOST bits[3:0] of the ILIMBSTSET register(0x03) to desired value. */
    error_flag |= battboost3_update_bits( ctx, BATTBOOST3_REG_ILIM_BST_SET, BATTBOOST3_BOOST_ILIM_MASK, ilim );

    return error_flag;
}

err_t battboost3_set_bypass_ilim ( battboost3_t *ctx, uint8_t apt_ilim, uint8_t fpt_ilim )
{
    uint8_t data_buf = 0;
    err_t error_flag = BATTBOOST3_OK;

    /* ILIMPTSET register(0x06):
     *     bits[5:3] -> Current limit in forced true bypass mode.
     *     bits[2:0] -> Current limit in automatic true bypass mode. */
    data_buf = ( ( fpt_ilim << 3 ) & BATTBOOST3_ILIM_FPT_MASK ) | ( apt_ilim & BATTBOOST3_ILIM_APT_MASK );
    
    error_flag |= battboost3_write_reg( ctx, BATTBOOST3_REG_ILIM_PT_SET, data_buf );

    return error_flag;
}

err_t battboost3_soft_reset ( battboost3_t *ctx )
{
    /* perform SW reset by setting RESET bit[7] of the CONFIG register(0x01). */
    return battboost3_update_bits( ctx, BATTBOOST3_REG_CONFIG, BATTBOOST3_CONFIG_RESET, BATTBOOST3_CONFIG_RESET );
}

void battboost3_set_en_pin ( battboost3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

static err_t battboost3_update_bits ( battboost3_t *ctx, uint8_t reg, uint8_t mask, uint8_t value )
{
    uint8_t data_buf = 0;
    err_t error_flag = BATTBOOST3_OK;

    /* Perform a read-modify-write on the selected register */
    error_flag = battboost3_read_reg( ctx, reg, &data_buf );
    if ( BATTBOOST3_OK != error_flag )
    {
        return error_flag;
    }

    data_buf &= ~mask;
    data_buf |= value & mask;

    error_flag |= battboost3_write_reg( ctx, reg, data_buf );

    return error_flag;
}

// ------------------------------------------------------------------------- END

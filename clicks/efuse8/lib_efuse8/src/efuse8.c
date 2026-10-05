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
 * @file efuse8.c
 * @brief eFuse 8 Click Driver.
 */

#include "efuse8.h"

void efuse8_cfg_setup ( efuse8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pgd = HAL_PIN_NC;
    cfg->ren = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EFUSE8_DEVICE_ADDRESS_0;
}

err_t efuse8_init ( efuse8_t *ctx, efuse8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ren, cfg->ren );
    digital_in_init( &ctx->pgd, cfg->pgd );

    /* Enable reverse current blocking */
    digital_out_high( &ctx->ren );

    return I2C_MASTER_SUCCESS;
}

err_t efuse8_default_cfg ( efuse8_t *ctx ) 
{
    err_t error_flag = EFUSE8_OK;
    
    /*
     * The volatile wiper keeps its position across an MCU reset
     * so it is placed back to mid scale as a default position.
     */
    error_flag |= efuse8_set_wiper( ctx, EFUSE8_WIPER_MID_SCALE );

    return error_flag;
}

err_t efuse8_write_data ( efuse8_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    /* Write frame : S | addr + W | A | command_byte | A | data_byte | A | P
     * 
     *  - Command byte : [7:4] -> register address
     *                   [3:2] -> command : 00 -> write data
     *                                      01 -> increment
     *                                      10 -> decrement
     *                                      11 -> read data
     *                   [1] -> unused
     *                   [0] -> wiper position MSB bit
     * 
     *  - Wiper position(9bits) : Command_byte[0] + data_byte[7:0]
     */
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( ( ( reg & EFUSE8_CMD_REG_MASK ) << EFUSE8_CMD_REG_SHIFT ) | 
                                  ( ( EFUSE8_CMD_WRITE_DATA & EFUSE8_CMD_OP_MASK ) << EFUSE8_CMD_OP_SHIFT ) | 
                                  ( ( data_in >> EFUSE8_DATA_MSB_SHIFT ) & EFUSE8_DATA_MSB_MASK ) );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & EFUSE8_DATA_LSB_MASK );

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t efuse8_read_data ( efuse8_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    /* Read frame : S | addr + W | A | command_byte | A | RS | addr + R | A | 0000 000D8 | A | D7...D0 | NA | P
     * 
     *  - Command byte : [7:4] -> register address
     *                   [3:2] -> command : 00 -> write data
     *                                      01 -> increment
     *                                      10 -> decrement
     *                                      11 -> read data
     *                   [1] -> unused
     *                   [0] -> unused
     */
    uint8_t cmd_byte = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = EFUSE8_OK;

    if ( NULL == data_out )
    {
        return EFUSE8_ERROR;
    }

    cmd_byte = ( uint8_t ) ( ( ( reg & EFUSE8_CMD_REG_MASK ) << EFUSE8_CMD_REG_SHIFT ) | 
                             ( ( EFUSE8_CMD_READ_DATA & EFUSE8_CMD_OP_MASK ) << EFUSE8_CMD_OP_SHIFT ) );

    error_flag |= i2c_master_write_then_read( &ctx->i2c, &cmd_byte, 1, data_buf, 2 );

    *data_out = ( uint16_t ) ( ( ( data_buf[ 0 ] & EFUSE8_DATA_MSB_MASK ) << EFUSE8_DATA_MSB_SHIFT ) | data_buf[ 1 ] );

    return error_flag;
}

err_t efuse8_set_wiper ( efuse8_t *ctx, uint16_t wiper ) 
{
    uint16_t wiper_pos = wiper;
    err_t error_flag = EFUSE8_OK;

    /* 
     * Clamped so that the R_ILM pin resistance stays inside the recommended
     * range 536-4834Ohm (TPS259483 datasheet, page 8, 6.3) 
     */
    if ( EFUSE8_WIPER_MAX < wiper_pos )
    {
        wiper_pos = EFUSE8_WIPER_MAX;
    }

    error_flag |= efuse8_write_data( ctx, EFUSE8_REG_WIPER_VOLATILE, wiper_pos );

    return error_flag;
}

err_t efuse8_get_wiper ( efuse8_t *ctx, uint16_t *wiper ) 
{
    return efuse8_read_data( ctx, EFUSE8_REG_WIPER_VOLATILE, wiper );
}

err_t efuse8_set_current_limit ( efuse8_t *ctx, uint16_t ilim_ma ) 
{
    uint32_t res_ohm = 0;
    uint16_t wiper_pos = 0;
    err_t error_flag = EFUSE8_OK;

    if ( EFUSE8_ILIM_MIN_MA > ilim_ma )
    {
        ilim_ma = EFUSE8_ILIM_MIN_MA;
    }

    if ( EFUSE8_ILIM_MAX_MA < ilim_ma )
    {
        ilim_ma = EFUSE8_ILIM_MAX_MA;
    }

    /* RILM[Ohm] = 4834 / ILIM[A] (page 26, 7.3.3.2) */
    res_ohm = ( uint32_t ) EFUSE8_ILIM_CONST_OHM_MA / ilim_ma;

    /*
     * 256 positions => Rs = RAB / 256
     * Schematic : P0W -> GND, P0B -> GND, ILIM -> P0A
     *  - RILM = RAW = ( RAB / 256 ) * ( 256 - N ) + RW
     *               = RAB * ( 256 - N ) / 256 + RW, (datasheet page 44)
     * 
     * => N = 256 - ( ( RAW - RW ) * 256 ) / RAB
     */
    wiper_pos = ( uint16_t ) ( EFUSE8_WIPER_RESOLUTION - 
                               ( ( ( res_ohm - EFUSE8_RW_OHM ) * EFUSE8_WIPER_RESOLUTION ) / EFUSE8_RAB_OHM ) );

    error_flag |= efuse8_set_wiper( ctx, wiper_pos );

    return error_flag;
}

err_t efuse8_get_current_limit ( efuse8_t *ctx, uint16_t *ilim_ma ) 
{
    uint32_t res_ohm = 0;
    uint16_t wiper_pos = 0;
    err_t error_flag = EFUSE8_OK;

    if ( NULL == ilim_ma )
    {
        return EFUSE8_ERROR;
    }

    error_flag |= efuse8_get_wiper( ctx, &wiper_pos );

    if ( EFUSE8_OK == error_flag )
    {
        /*
         * RILM = RAW = ( RAB / 256 ) * ( 256 - N ) + RW
         *            = RAB * ( 256 - N ) / 256 + RW
         */
        res_ohm = ( ( uint32_t ) EFUSE8_RAB_OHM * ( EFUSE8_WIPER_RESOLUTION - wiper_pos ) ) / 
                  EFUSE8_WIPER_RESOLUTION + EFUSE8_RW_OHM;

        /* ILIM[A] = 4834 / RILM[Ohm] (page 26, 7.3.3.2) */
        *ilim_ma = ( uint16_t ) ( ( uint32_t ) EFUSE8_ILIM_CONST_OHM_MA / res_ohm );
    }

    return error_flag;
}

void efuse8_set_ren ( efuse8_t *ctx, uint8_t state ) 
{
    if ( EFUSE8_RCB_ENABLE == state )
    {
        digital_out_high( &ctx->ren );
    }
    else
    {
        digital_out_low( &ctx->ren );
    }
}

uint8_t efuse8_get_pgd_pin ( efuse8_t *ctx ) 
{
    return digital_in_read( &ctx->pgd );
}

// ------------------------------------------------------------------------- END

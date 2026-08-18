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
 * @file c3dhall17.c
 * @brief 3D Hall 17 Click Driver.
 */

#include "c3dhall17.h"

void c3dhall17_cfg_setup ( c3dhall17_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL17_DEVICE_ADDRESS;
}

err_t c3dhall17_init ( c3dhall17_t *ctx, c3dhall17_cfg_t *cfg )
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
    
    /* Enable device */
    digital_out_high( &ctx->en );
    Delay_1ms( );

    return I2C_MASTER_SUCCESS;
}

err_t c3dhall17_default_cfg ( c3dhall17_t *ctx )
{
    err_t error_flag = C3DHALL17_OK;
    
    /* HW reset */
    c3dhall17_hw_reset( ctx );

    /* MOD1 register:
     *    bits[7:0] = 0x03 -> Device is in Master Controlled Mode and waits for master
     *                        to read out data before new measurement cycle(Datasheet page 15). */
    error_flag = c3dhall17_set_op_mode( ctx, C3DHALL17_OP_MODE1_MASTER_CTRL, C3DHALL17_OP_MODE2_DEFAULT );

    return error_flag;
}

err_t c3dhall17_write_regs ( c3dhall17_t *ctx, uint8_t *data_in )
{
    /* AH4931Q requires all 4 write registers to be written in one transaction(Datasheet page 10):
     *    0H[7:0] = reserved, write 0x00
     *    1H[7:0] = MOD1
     *    2H[7:0] = reserved, write 0x00
     *    3H[7:0] = MOD2 */
    return i2c_master_write( &ctx->i2c, data_in, C3DHALL17_WRITE_LEN );
}

err_t c3dhall17_read_regs ( c3dhall17_t *ctx, uint8_t *data_out )
{
    /* AH4931Q requires all 7 read registers to be read in one transaction(Datasheet page 10):
     *    0H[7:0] = Bx[11:4], zero after reset
     *    1H[7:0] = By[11:4], zero after reset
     *    2H[7:0] = Bz[11:4], zero after reset
     *    3H[7:0] = Temp[11:8], frame_number[1:0],CH_number[1:0]
     *    4H[7:0] = Bx[3:0], By[3:0]
     *    5H[7:0] = reserved, PD[4], Bz[3:0]
     *    6H[7:0] = Temp[7:0] */
    return i2c_master_read( &ctx->i2c, data_out, C3DHALL17_READ_LEN );
}

void c3dhall17_enable_device ( c3dhall17_t *ctx )
{
    digital_out_high( &ctx->en );
}

void c3dhall17_disable_device ( c3dhall17_t *ctx )
{
    digital_out_low( &ctx->en );
}

err_t c3dhall17_set_op_mode ( c3dhall17_t *ctx, uint8_t mod1, uint8_t mod2 )
{
    /* Data sequence to be written in all 4 write registers.
     * 0x00 needs to be written in reserved write registers. */
    uint8_t cfg_buf[ C3DHALL17_WRITE_LEN  ] = { C3DHALL17_RSVD_REG_DATA, mod1, C3DHALL17_RSVD_REG_DATA, mod2 };

    return c3dhall17_write_regs( ctx, cfg_buf );
}

err_t c3dhall17_get_data ( c3dhall17_t *ctx, c3dhall17_data_t *data_out )
{
    uint8_t raw[ C3DHALL17_READ_LEN ] = { 0 };
    uint32_t timeout_cnt = C3DHALL17_TIMEOUT_MS;
    int16_t bx_raw = 0;
    int16_t by_raw = 0;
    int16_t bz_raw = 0;
    int16_t temp_raw = 0;

    /* PD(Power-down flag) must be 1 at read-out => Poll it(Datasheet page 18). */
    do
    {
        Delay_1ms( );
        if ( 0 == --timeout_cnt )
        {
            return C3DHALL17_ERROR;
        }
        c3dhall17_read_regs( ctx, raw );
    } while ( !( raw[ 5 ] & C3DHALL17_BZ2_PD_FLAG ) );

    /* Assemble 12-bit signed values (2's complement) from split register layout:
     *    Bx[11:4] = raw[0], Bx[3:0] = raw[4] bits [7:4]
     *    By[11:4] = raw[1], By[3:0] = raw[4] bits [3:0]
     *    Bz[11:4] = raw[2], Bz[3:0] = raw[5] bits [3:0]
     *    Temp[11:8] = raw[3] bits [7:4], Temp[7:0] = raw[6] */
    bx_raw = ( ( int16_t ) raw[ 0 ] << 4 ) | ( ( raw[ 4 ] >> 4 ) & 0x0F );
    by_raw = ( ( int16_t ) raw[ 1 ] << 4 ) | ( raw[ 4 ] & 0x0F );
    bz_raw = ( ( int16_t ) raw[ 2 ] << 4 ) | ( raw[ 5 ] & 0x0F );
    temp_raw = ( ( int16_t ) ( raw[ 3 ] >> 4 ) << 8 ) | raw[ 6 ];

    /* Sign-extend from 12-bit to 16-bit */
    if ( bx_raw & C3DHALL17_BIT_11_MASK )
    {
        bx_raw |= C3DHALL17_4TH_BYTE_MASK;
    }
    if ( by_raw & C3DHALL17_BIT_11_MASK )
    {
        by_raw |= C3DHALL17_4TH_BYTE_MASK;
    }
    if ( bz_raw & C3DHALL17_BIT_11_MASK )
    {
        bz_raw |= C3DHALL17_4TH_BYTE_MASK;
    }
    if ( temp_raw & C3DHALL17_BIT_11_MASK )
    {
        temp_raw |= C3DHALL17_4TH_BYTE_MASK;
    }

    /* Convert to physical units: 1 LSB = 1 Gauss, 1 LSB = 1 degC(Datasheet pages 8 and 9 ) */
    data_out->x_val    = ( float ) bx_raw   * C3DHALL17_SENS_LSB_PER_GAUSS;
    data_out->y_val    = ( float ) by_raw   * C3DHALL17_SENS_LSB_PER_GAUSS;
    data_out->z_val    = ( float ) bz_raw   * C3DHALL17_SENS_LSB_PER_GAUSS;
    data_out->temp_val = ( float ) temp_raw * C3DHALL17_TEMP_RES_DEG_PER_LSB;

    return C3DHALL17_OK;
}

void c3dhall17_hw_reset ( c3dhall17_t *ctx )
{
    digital_out_low( &ctx->en );
    Delay_100ms( );             
    digital_out_high( &ctx->en );
    Delay_1ms( );    
}

// ------------------------------------------------------------------------- END

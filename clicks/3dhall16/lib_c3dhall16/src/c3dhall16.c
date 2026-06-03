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
 * @file c3dhall16.c
 * @brief 3D Hall 16 Click Driver.
 */

#include "c3dhall16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief 3D Hall 16 assemble 14bit function.
 * @details This function assembles a 14-bit signed value from two raw register bytes.
 * @param[in] msb : Value of the MSB register.
 * @param[in] lsb : Value of the LSB register.
 * @return 16-bit signed integer with the 14-bit value sign-extended.
 * @note None.
 */
static int16_t c3dhall16_assemble_14bit ( uint8_t msb, uint8_t lsb );

void c3dhall16_cfg_setup ( c3dhall16_cfg_t *cfg ) 
{   
    // Communication gpio pins
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c3dhall16_init ( c3dhall16_t *ctx, c3dhall16_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    /* full range:
     *    magnetic range: +-160mT
     *    sensitivity: 29.5 LSB/mT */
    ctx->sensitivity = C3DHALL16_SENS_FULL_RANGE;

    Delay_5ms( );

    return SPI_MASTER_SUCCESS;
}

err_t c3dhall16_default_cfg ( c3dhall16_t *ctx ) 
{
    err_t error_flag = C3DHALL16_OK;
    uint16_t timeout = C3DHALL16_CHECK_COM_TIMEOUT_MS;
    
    /* check if data is corrupted */
    while ( C3DHALL16_ERROR == c3dhall16_check_communication( ctx ) )
    {
        timeout--;

        if ( 0 == timeout )
        {
            return C3DHALL16_ERROR;
        }

        Delay_1ms( );
    }

    /* Software reset. */
    error_flag |= c3dhall16_reset( ctx );

    /* Sensor mode register 2:
     *    bit[7:4] = 0000 => all channels enabled (Bx, By, Bz, Temp) for measurement  
     *    bit[3:2] = 01   => output data updated at 125 Hz
     *    bit[1:0] = 00   => full range(magnetic range: +-160mT, sensitivity: 29.5 LSB/mT ) */
    error_flag |= c3dhall16_write_reg( ctx, C3DHALL16_REG_MOD2,
                                            C3DHALL16_MOD2_CH_ALL |
                                            C3DHALL16_MOD2_FUPDATE_125HZ |
                                            C3DHALL16_MOD2_FULL_RANGE );
    
    /* Cache sensitivity based on the current range */
    ctx->sensitivity = C3DHALL16_SENS_FULL_RANGE;

    /* Sensor mode register 1:
     *    bit[7]   = 0  => low power mode (self-triggered measurement at f_update rate, no external trigger needed)
     *    bit[6]   = 0  => INTN pin enabled to indicate measurement completion (active LOW)
     *    bit[4]   = 0  => wake-up function disabled 
     *    bit[3:2] = 00 => no trigger set
     *    bit[0]   = 0  => CRC for writing disabled */
    error_flag |= c3dhall16_write_reg( ctx, C3DHALL16_REG_MOD1, 
                                            C3DHALL16_MOD1_LOW_POWER |
                                            C3DHALL16_MOD1_INT_EN    |
                                            C3DHALL16_MOD1_WU_DIS    |
                                            C3DHALL16_MOD1_CRC_WR_DIS );

    /* fUpdate is valid with the second conversion after power up and/or register reset */
    Delay_10ms( );

    return error_flag;
}

err_t c3dhall16_write_reg ( c3dhall16_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return c3dhall16_write_regs( ctx, reg, &data_in, 1 );
}

err_t c3dhall16_write_regs ( c3dhall16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* SPI write frame: | 0 | b | reg address (6 bits) | data byte 0 | ... | data byte N | */
    uint8_t cmd = C3DHALL16_SPI_WRITE_CMD | ( reg & C3DHALL16_SPI_ADDR_MASK );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t c3dhall16_read_reg ( c3dhall16_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return c3dhall16_read_regs( ctx, reg, data_out, 1 );
}

err_t c3dhall16_read_regs ( c3dhall16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* SPI read frame: | 1 | 0 | reg address (6 bits) | dummy byte 0 | ... | dummy byte N | */
    uint8_t cmd = C3DHALL16_SPI_READ_CMD | ( reg & C3DHALL16_SPI_ADDR_MASK );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write(&ctx->spi, &cmd, 1 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

uint8_t c3dhall16_get_int_pin ( c3dhall16_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t c3dhall16_reset ( c3dhall16_t *ctx )
{
    err_t error_flag = C3DHALL16_OK;
    uint8_t diag = 0;
    uint16_t timeout = C3DHALL16_RESET_TIMEOUT_MS;

    /* Trigger software reset by setting soft_rst bit. */
    error_flag |= c3dhall16_write_reg( ctx, C3DHALL16_REG_RST, C3DHALL16_SOFT_RST );

    /* Wait for the rst_flg bit in DIAG register to be set, indicating reset completed. */
    do
    {
        Delay_1ms( );
        error_flag |= c3dhall16_read_reg( ctx, C3DHALL16_REG_DIAG, &diag );
        timeout--;
    }
    while ( !( diag & C3DHALL16_DIAG_RST_FLG ) && timeout );

    if ( 0 == timeout )
    {
        return C3DHALL16_ERROR;
    }

    /* Clear the rst_flg by writing 1 to rst_flg_clr. */
    error_flag |= c3dhall16_write_reg( ctx, C3DHALL16_REG_RST, C3DHALL16_RST_FLG_CLR );

    return error_flag;
}

err_t c3dhall16_check_communication ( c3dhall16_t *ctx )
{
    uint8_t diag = 0;

    if ( C3DHALL16_OK == c3dhall16_read_reg( ctx, C3DHALL16_REG_DIAG, &diag ) )
    {
        /* fuse_par_flg (bit 0) must be 1.
         * If 0, output of the sensor must be considered corrupted. */
        if ( diag & C3DHALL16_DIAG_FUSE_PAR_FLG )
        {
            return C3DHALL16_OK;
        }
    }

    return C3DHALL16_ERROR;
}

err_t c3dhall16_check_data_ready ( c3dhall16_t *ctx )
{
    uint8_t diag = 0;

    if ( C3DHALL16_OK != c3dhall16_read_reg( ctx, C3DHALL16_REG_DIAG, &diag ) )
    {
        return C3DHALL16_ERROR;
    }

    /* Three conditions must all be true for valid, ready data:
     *    bit[7](meas_flg)     = 1 => all register values belong to the same ADC conversion cycle.
     *    bit[6](test_flg)     = 0 => registers contain measurement data, not test data.
     *    bit[0](fuse_par_flg) = 1 => sensor output data is not corrupted. */
    if ( ( diag & C3DHALL16_DIAG_MEAS_FLG ) && !( diag & C3DHALL16_DIAG_TEST_FLG  ) && ( diag & C3DHALL16_DIAG_FUSE_PAR_FLG ) )
    {
        return C3DHALL16_OK;
    }
    else
    {
        return C3DHALL16_ERROR;
    }
}

err_t c3dhall16_set_operating_mode ( c3dhall16_t *ctx, uint8_t mode )
{
    uint8_t mod1 = 0;
    err_t error_flag = C3DHALL16_OK;

    error_flag |= c3dhall16_read_reg( ctx, C3DHALL16_REG_MOD1, &mod1 );

    /* Clear only mode_sel bit (bit 7), preserve all other bits. */
    mod1 &= ~C3DHALL16_MOD1_MODE_MASK;
    mod1 |= ( mode & C3DHALL16_MOD1_MODE_MASK );

    error_flag |= c3dhall16_write_reg( ctx, C3DHALL16_REG_MOD1, mod1 );

    return error_flag;
}

err_t c3dhall16_set_range ( c3dhall16_t *ctx, uint8_t range )
{
    uint8_t mod2 = 0;
    err_t error_flag = C3DHALL16_OK;

    /* Read current MOD2 register value to preserve channel_sel[7:4] and f_update_sel[3:2] bits. */
    error_flag |= c3dhall16_read_reg( ctx, C3DHALL16_REG_MOD2, &mod2 );

    /* Clear the range bits. */
    mod2 &= ~C3DHALL16_MOD2_RANGE_MASK;

    /* Apply the requested range bits. */
    mod2 |= ( range & C3DHALL16_MOD2_RANGE_MASK );

    error_flag |= c3dhall16_write_reg( ctx, C3DHALL16_REG_MOD2, mod2 );

    /* Cache sensitivity based on the current range. */
    if ( C3DHALL16_MOD2_XSHORT_RANGE == ( range & C3DHALL16_MOD2_XSHORT_RANGE ) )
    {
        ctx->sensitivity = C3DHALL16_SENS_XSHORT_RANGE;
    }
    else if ( C3DHALL16_MOD2_SHORT_RANGE == ( range & C3DHALL16_MOD2_SHORT_RANGE ) )
    {
        ctx->sensitivity = C3DHALL16_SENS_SHORT_RANGE;
    }
    else
    {
        ctx->sensitivity = C3DHALL16_SENS_FULL_RANGE;
    }

    return error_flag;
}

err_t c3dhall16_get_magnetic_flux ( c3dhall16_t *ctx, float *x_axis, float *y_axis, float *z_axis )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw = 0;

    /* Poll until a new valid measurement is available. */
    while ( C3DHALL16_ERROR == c3dhall16_check_data_ready( ctx ) );

    /* Burst-read 6 bytes starting from BX_MSB (0x00):
     *    buf[0] = BX_MSB,   buf[1] = BX_LSB
     *    buf[2] = BY_MSB,   buf[3] = BY_LSB
     *    buf[4] = BZ_MSB,   buf[5] = BZ_LSB
     * This ensures all values are from the same measurement cycle. */
    if ( C3DHALL16_OK != c3dhall16_read_regs( ctx, C3DHALL16_REG_BX_MSB, data_buf, 6 ) )
    {
        return C3DHALL16_ERROR;
    }

    /* Assemble and convert each 14-bit signed value.
     * B[uT] = ( raw / sensitivity ) * 1000 */
    raw = c3dhall16_assemble_14bit( data_buf[ 0 ], data_buf[ 1 ] );
    *x_axis = ( ( float ) raw / ctx->sensitivity ) * C3DHALL16_MT_TO_UT;

    raw = c3dhall16_assemble_14bit( data_buf[ 2 ], data_buf[ 3 ] );
    *y_axis = ( ( float ) raw / ctx->sensitivity ) * C3DHALL16_MT_TO_UT;

    raw = c3dhall16_assemble_14bit( data_buf[ 4 ], data_buf[ 5 ] );
    *z_axis = ( ( float ) raw / ctx->sensitivity ) * C3DHALL16_MT_TO_UT;

    return C3DHALL16_OK;
}

err_t c3dhall16_get_temperature ( c3dhall16_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw = 0;

    /* Poll until a new valid measurement is available. */
    while ( C3DHALL16_ERROR == c3dhall16_check_data_ready( ctx ) );
    
    /* buf[0] = TEMP_MSB, buf[1] = TEMP_LSB */
    if ( C3DHALL16_OK != c3dhall16_read_regs( ctx, C3DHALL16_REG_TEMP_MSB, data_buf, 2 ) )
    {
        return C3DHALL16_ERROR;
    }

    /* Assemble 14-bit signed temperature value.
     * Formula: T[degC] = 25.0 + (raw - 4200) / 15.2
     *    25 degC    : Typical physical temperature reference
     *    4200 LSB   : Typical ADC output at 25 degC
     *    15.2 LSB/K : Typical temperature sensitivity */
    raw = c3dhall16_assemble_14bit( data_buf[ 0 ], data_buf[ 1 ] );
    *temperature = C3DHALL16_TEMP_REF_DEG + ( ( float ) raw - C3DHALL16_TEMP_REF_VALUE ) / C3DHALL16_TEMP_SENSITIVITY;

    return C3DHALL16_OK;
}

err_t c3dhall16_get_data ( c3dhall16_t *ctx, float *x_axis, float *y_axis, float *z_axis, float *temperature )                            
{
    uint8_t data_buf[ 8 ] = { 0 };
    int16_t raw = 0;

    /* Poll until a new valid measurement is available. */
    while ( C3DHALL16_ERROR == c3dhall16_check_data_ready( ctx ) );

    /* Burst-read all 8 bytes in a single SPI transaction:
     *    buf[0] = BX_MSB,   buf[1] = BX_LSB
     *    buf[2] = BY_MSB,   buf[3] = BY_LSB
     *    buf[4] = BZ_MSB,   buf[5] = BZ_LSB
     *    buf[6] = TEMP_MSB, buf[7] = TEMP_LSB */
    if ( C3DHALL16_OK != c3dhall16_read_regs( ctx, C3DHALL16_REG_BX_MSB, data_buf, 8 ) )
    {
        return C3DHALL16_ERROR;
    }

    /* Assemble and convert each 14-bit signed value.
     * B[uT] = ( raw / sensitivity ) * 1000 */
    raw = c3dhall16_assemble_14bit( data_buf[ 0 ], data_buf[ 1 ] );
    *x_axis = ( ( float ) raw / ctx->sensitivity ) * C3DHALL16_MT_TO_UT;

    raw = c3dhall16_assemble_14bit( data_buf[ 2 ], data_buf[ 3 ] );
    *y_axis = ( ( float ) raw / ctx->sensitivity ) * C3DHALL16_MT_TO_UT;

    raw = c3dhall16_assemble_14bit( data_buf[ 4 ], data_buf[ 5 ] );
    *z_axis = ( ( float ) raw / ctx->sensitivity ) * C3DHALL16_MT_TO_UT;

    /* Assemble 14-bit signed temperature value.
     * Formula: T[degC] = 25.0 + (raw - 4200) / 15.2
     *    25 degC    : Typical physical temperature reference
     *    4200 LSB   : Typical ADC output at 25 degC
     *    15.2 LSB/K : Typical temperature sensitivity */
    raw = c3dhall16_assemble_14bit( data_buf[ 6 ], data_buf[ 7 ] );
    *temperature = C3DHALL16_TEMP_REF_DEG + ( ( float ) raw - C3DHALL16_TEMP_REF_VALUE ) / C3DHALL16_TEMP_SENSITIVITY;

    return C3DHALL16_OK;
}

static int16_t c3dhall16_assemble_14bit ( uint8_t msb, uint8_t lsb )
{
    /* The sensor stores each magnetic/temperature value as a 14-bit
     * two's complement number split across two registers:
     *     MSB register: bits [13:6] (all 8 bits used)
     *     LSB register: bits [5:0]  (only bits 5:0 used, bits 7:6 are reserved) */
    int16_t raw = ( ( int16_t ) msb << C3DHALL16_14BIT_MSB_SHIFT ) | ( lsb & C3DHALL16_14BIT_LSB_MASK );

    /* Sign-extend from 14 bits to 16 bits. */
    if ( raw & C3DHALL16_14BIT_SIGN_BIT )
    {
        raw |= C3DHALL16_14BIT_SIGN_EXT;
    }
    return raw;
}

// ------------------------------------------------------------------------- END

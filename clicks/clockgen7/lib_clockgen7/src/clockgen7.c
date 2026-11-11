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
 * @file clockgen7.c
 * @brief Clock Gen 7 Click Driver.
 */

#include "clockgen7.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Clock Gen 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen7_i2c_write ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Clock Gen 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen7_i2c_read ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Clock Gen 7 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen7_spi_write ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Clock Gen 7 SPI reading function.
 * @details This function is a placeholder for the read interface. The CS2501
 * SPI control port is write-only, so this function always returns an error.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen7_spi_read ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void clockgen7_cfg_setup ( clockgen7_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cin  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CLOCKGEN7_DEVICE_ADDRESS_VDD;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->cin_freq = CLOCKGEN7_DEF_CLK_IN_FREQ;

    cfg->drv_sel = CLOCKGEN7_DRV_SEL_I2C;
}

void clockgen7_drv_interface_sel ( clockgen7_cfg_t *cfg, clockgen7_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t clockgen7_init ( clockgen7_t *ctx, clockgen7_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( CLOCKGEN7_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = clockgen7_i2c_read;
        ctx->write_f = clockgen7_i2c_write;
    } 
    else 
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

        ctx->read_f  = clockgen7_spi_read;
        ctx->write_f = clockgen7_spi_write;
    }

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin = cfg->cin;
    pwm_cfg.freq_hz = cfg->cin_freq;

    if ( PWM_ERROR == pwm_open( &ctx->cin, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }

    if ( PWM_ERROR == pwm_set_freq( &ctx->cin, pwm_cfg.freq_hz ) )
    {
        return PWM_ERROR;
    }

    /* Set default values to the register shadow copies */
    ctx->shadow_pll_cfg1 = CLOCKGEN7_UNLOCK_MASK;
    ctx->shadow_pll_cfg2 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->shadow_pll_cfg4 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->shadow_pll_cfg5 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->shadow_pll_cfg6 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->ratio_format = CLOCKGEN7_RATIO_CFG_20_12;

    return CLOCKGEN7_OK;
}

err_t clockgen7_default_cfg ( clockgen7_t *ctx ) 
{
    err_t error_flag = CLOCKGEN7_OK;

    /* Check communication only for I2C since CS2501 does not support SPI read */
    if ( CLOCKGEN7_DRV_SEL_I2C == ctx->drv_sel )
    {
        if ( CLOCKGEN7_OK != clockgen7_check_communication( ctx ) )
        {
            return CLOCKGEN7_ERROR;
        }
    }

    error_flag |= clockgen7_sw_reset( ctx );
    Delay_1ms( );

    /*
     * PLL_CFG5 register(0x16):
     *
     *  - bits[4:3] = 01 -> REF_CLK_IN input divider set to 2.
     *    (Click board uses 25 MHz crystal => divider must be 2, page 8 table 3-4 )
     *  - bits[2:1] = 01 -> REF_CLK_IN selected as source for PLL.
     */
    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG5,
                                            CLOCKGEN7_REF_CLK_IN_DIV_2 | 
                                            CLOCKGEN7_SYSCLK_SRC_REF_CLK );
    /*
     * PLL_CFG6 register(0x17):
     *
     *  - bit[4] = 0 -> Clock outputs are stopped automatically if they are not valid.
     *  - bit[3] = 1 -> High resolution ratio format, recommended for resolution < 4096 (page 13, 4.3.2).
     */
    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG6,
                                            CLOCKGEN7_OUT_GATE_EN | 
                                            CLOCKGEN7_RATIO_CFG_12_20 );

    /* Update cached ratio format */
    ctx->ratio_format = CLOCKGEN7_RATIO_CFG_12_20;

    /*
     * PLL_CFG7 register(0x1E):
     *
     *  - bits[7]   = 0   -> FLL_BW is multiplied by 1.
     *  - bits[6:4] = 100 -> FLL_BW set to 16 Hz.
     * 
     * Effective FLL bandwidth = 16 Hz x 1 = 16 Hz.
     */
    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG7,
                                            CLOCKGEN7_FLL_BW_MOD_MUL_1 | 
                                            CLOCKGEN7_FLL_BW_16_HZ );

    /* Default PLL ratio set to 512 => f_CLK_OUT = f_CLK_IN * 512 (page 13, 4.3.2)  */
    error_flag |= clockgen7_set_ratio( ctx, CLOCKGEN7_DEF_RATIO );

    /* Set CLK_IN as AUX_OUT -> use CN2 on click board to see the reference */
    error_flag |= clockgen7_set_aux_out( ctx, CLOCKGEN7_AUX_OUT_SEL_CLK_IN );

    /* Start the CLK_IN reference before enabling the PLL */
    error_flag |= clockgen7_set_clk_in_freq( ctx, CLOCKGEN7_DEF_CLK_IN_FREQ );

    /*
     * Enable PLL and apply delay for PLL to lock.
     * The device should be fully configured by writing to the applicable
     * control registers before enabling the PLL (page 13, 4.3.1).
     */
    error_flag |= clockgen7_pll_enable( ctx );
    Delay_10ms( );
                        
    return error_flag;
}

err_t clockgen7_write_reg ( clockgen7_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t clockgen7_write_regs ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* Auto-increment is configured via MSB of the register address byte */
    uint8_t reg_addr = reg;
    if ( 1 < len )
    {
        reg_addr |= CLOCKGEN7_AUTO_INCREMENT;
    }
    return ctx->write_f( ctx, reg_addr, data_in, len );
}

err_t clockgen7_read_reg ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t clockgen7_read_regs ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* Auto-increment is configured via MSB of the register address byte */
    uint8_t reg_addr = reg;
    if ( 1 < len )
    {
        reg_addr |= CLOCKGEN7_AUTO_INCREMENT;
    }
    return ctx->read_f( ctx, reg_addr, data_out, len );
}

err_t clockgen7_sw_reset ( clockgen7_t *ctx )
{
    /* Perform a software reset by writing 0x5A to the SW_RESET register(0x58) */
    err_t error_flag = clockgen7_write_reg( ctx, CLOCKGEN7_REG_SW_RESET, CLOCKGEN7_SW_RST );

    /* Set default values to the register shadow copies */
    ctx->shadow_pll_cfg1 = CLOCKGEN7_UNLOCK_MASK;
    ctx->shadow_pll_cfg2 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->shadow_pll_cfg4 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->shadow_pll_cfg5 = CLOCKGEN7_SHADOW_COPY_DEF;
    ctx->shadow_pll_cfg6 = CLOCKGEN7_SHADOW_COPY_DEF;

    /* Update cached ratio format to default value */
    ctx->ratio_format = CLOCKGEN7_RATIO_CFG_20_12;

    return error_flag;
}

err_t clockgen7_check_communication ( clockgen7_t *ctx )
{
    /*
     * Device ID:
     *
     *  - DEV_ID_0 register(0x54) -> Device ID MSB, expected 0x25
     *  - DEV_ID_1 register(0x55) -> Device ID LSB, expected 0x01
     */
    uint8_t dev_id[ 2 ] = { 0 };
    err_t error_flag = clockgen7_read_regs( ctx, CLOCKGEN7_REG_DEV_ID_0, dev_id, 2 );
    if ( CLOCKGEN7_OK != error_flag )
    {
        return CLOCKGEN7_ERROR;
    }

    uint16_t device_id = ( ( uint16_t ) dev_id[ 0 ] << 8 ) | dev_id[ 1 ];
    if ( CLOCKGEN7_DEVICE_ID != device_id )
    {
        return CLOCKGEN7_ERROR;
    }
    return CLOCKGEN7_OK;
}

err_t clockgen7_set_clk_in_freq ( clockgen7_t *ctx, uint32_t freq )
{
    if ( PWM_ERROR == pwm_set_freq( &ctx->cin, freq ) )
    {
        return PWM_ERROR;
    }

    if ( PWM_ERROR == pwm_set_duty( &ctx->cin, CLOCKGEN7_DEF_DUTY_CYCLE ) )
    {
        return PWM_ERROR;
    }

    if ( PWM_ERROR == pwm_start( &ctx->cin ) )
    {
        return PWM_ERROR;
    }

    return CLOCKGEN7_OK;
}

err_t clockgen7_set_ratio ( clockgen7_t *ctx, float ratio )
{
    uint8_t ratio_buf[ CLOCKGEN7_RATIO_NUM_BYTES ] = { 0 };
    uint32_t raw_ratio = 0;
    float scale = CLOCKGEN7_RATIO_SCALE_20_12;
    err_t error_flag = CLOCKGEN7_OK;

    if ( CLOCKGEN7_RATIO_MIN >= ratio )
    {
        return CLOCKGEN7_ERROR;
    }

    /*
     * Ratio format: (page 13, 4.3.2)
     *
     *  - High resolution(12.20) -> 12 MSBs are integer portion
     *                              20 LSBs are fractional portion
     *                              => maximum ratio = ~4096
     *                              scale = 2^20 = 1048576
     *  - High multiplication(20.12) -> 20 MSBs are integer portion
     *                                  12 LSBs are fractional portion
     *                                  => maximum ratio = ~1,048,576
     *                                  scale = 2^12 = 4096
     * 
     * If the desired ratio is less than 4096, the 12.20 format is recommended.
     */
    if ( CLOCKGEN7_RATIO_CFG_12_20 == ctx->ratio_format )
    {
        if ( CLOCKGEN7_RATIO_MAX_12_20 <= ratio )
        {
            return CLOCKGEN7_ERROR;
        }
        scale = CLOCKGEN7_RATIO_SCALE_12_20;
    }
    else
    {
        if ( CLOCKGEN7_RATIO_MAX_20_12 <= ratio )
        {
            return CLOCKGEN7_ERROR;
        }
        scale = CLOCKGEN7_RATIO_SCALE_20_12;
    }

    /* 32 bit raw ratio(register value) = integer_portion.fractional_portion * scale */
    raw_ratio = ( uint32_t ) ( ratio * scale );

    /* MSB first */
    ratio_buf[ 0 ] = ( uint8_t ) ( ( raw_ratio >> 24 ) & 0xFF );
    ratio_buf[ 1 ] = ( uint8_t ) ( ( raw_ratio >> 16 ) & 0xFF );
    ratio_buf[ 2 ] = ( uint8_t ) ( ( raw_ratio >> 8 ) & 0xFF );
    ratio_buf[ 3 ] = ( uint8_t ) ( raw_ratio & 0xFF );

    /*
     * PLL ratio registers:
     *
     *  - RATIO_REG_1(0x06) -> PLL ratio bits[31:24]
     *  - RATIO_REG_2(0x07) -> PLL ratio bits[23:16]
     *  - RATIO_REG_3(0x08) -> PLL ratio bits[15:8]
     *  - RATIO_REG_4(0x09) -> PLL ratio bits[7:0]
     */
    error_flag |= clockgen7_write_regs( ctx, CLOCKGEN7_REG_RATIO_1, ratio_buf, CLOCKGEN7_RATIO_NUM_BYTES );

    return error_flag;
}

err_t clockgen7_pll_enable ( clockgen7_t *ctx )
{
    err_t error_flag = CLOCKGEN7_OK;

    /*
     * PLL enable/disable bits:
     *
     *  - PLL_CFG2[0] = 1 -> PLL_EN1 enable
     *  - PLL_CFG4[0] = 1 -> PLL_EN2 enable
     * 
     * Both bits need to be set in order to enable PLL(page 13, 4.3.1).
     */
    ctx->shadow_pll_cfg2 |= CLOCKGEN7_PLL_EN1;
    ctx->shadow_pll_cfg4 |= CLOCKGEN7_PLL_EN2;

    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG2, ctx->shadow_pll_cfg2 );
    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG4, ctx->shadow_pll_cfg4 );

    return error_flag;
}

err_t clockgen7_pll_disable ( clockgen7_t *ctx )
{
    /*
     * PLL enable/disable bits:
     *
     *  - PLL_CFG2[0] = 0 -> PLL_EN1 disabled
     *  - PLL_CFG4[0] = 0 -> PLL_EN2 disabled
     */
    err_t error_flag = CLOCKGEN7_OK;

    ctx->shadow_pll_cfg2 &= ~CLOCKGEN7_PLL_EN1;
    ctx->shadow_pll_cfg4 &= ~CLOCKGEN7_PLL_EN2;

    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG2, ctx->shadow_pll_cfg2 );
    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG4, ctx->shadow_pll_cfg4 );

    return error_flag;
}

err_t clockgen7_get_lock_status ( clockgen7_t *ctx, uint8_t *status )
{
    uint8_t reg_data = 0;
    err_t error_flag = CLOCKGEN7_OK;

    /*
     * PLL_CFG1 register(0x02):
     *
     * bit[7]:
     *  - 0 -> PLL is locked and has remained locked since the last read.
     *  - 1 -> Either the PLL is unlocked, or the PLL is locked but
     *         had previously unlocked since the last read.
     *         => a second read of the UNLOCK bit is required in order to
     *         confirm the current lock status(page 13, 4.3.1).
     */
    error_flag |= clockgen7_read_reg( ctx, CLOCKGEN7_REG_PLL_CFG1, &reg_data );
    if ( CLOCKGEN7_OK != error_flag )
    {
        return CLOCKGEN7_ERROR;
    }
    if ( !( reg_data & CLOCKGEN7_UNLOCK_MASK ) )
    {
        *status = CLOCKGEN7_STATUS_LOCKED;
        return CLOCKGEN7_OK;
    }

    /* Second read in order to confirm the current lock status */
    error_flag = clockgen7_read_reg( ctx, CLOCKGEN7_REG_PLL_CFG1, &reg_data );
    if ( CLOCKGEN7_OK != error_flag )
    {
        return CLOCKGEN7_ERROR;
    }
    if ( !( reg_data & CLOCKGEN7_UNLOCK_MASK ) )
    {
        *status = CLOCKGEN7_STATUS_LOCKED;
    }
    else
    {
        *status = CLOCKGEN7_STATUS_UNLOCKED;
    }

    return CLOCKGEN7_OK;
}

err_t clockgen7_set_aux_out ( clockgen7_t *ctx, uint8_t aux_sel )
{
    err_t error_flag = CLOCKGEN7_OK;

    /*
     * PLL_CFG2 register(0x03):
     *
     * AUX_OUT function select bits[2:1]:
     *  - 00 -> REF_CLK_IN
     *  - 01 -> CLK_IN
     *  - 10 -> CLK_OUT
     *  - 11 -> PLL unlock
     */
    ctx->shadow_pll_cfg2 &= ~CLOCKGEN7_AUX_OUT_SEL_MASK;
    ctx->shadow_pll_cfg2 |= ( aux_sel & CLOCKGEN7_AUX_OUT_SEL_MASK );
    error_flag |= clockgen7_write_reg( ctx, CLOCKGEN7_REG_PLL_CFG2, ctx->shadow_pll_cfg2 );

    return error_flag;
}

static err_t clockgen7_i2c_write ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* 
     * Write frame : S | sl_addr + W | A | reg_addr | A | data0 | A | ... dataN | A | P 
     * - reg_addr[7] = auto-increment bit
     * - reg_addr[6:0] = register address
     */
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t clockgen7_i2c_read ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* 
     * Read frame : S | sl_addr + W | A | reg_addr | A | RS | sl_addr + R | data0 | A | ... dataN | NA | P 
     * - reg_addr[7] = auto-increment bit
     * - reg_addr[6:0] = register address
     */
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t clockgen7_spi_write ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* 
     * Write frame : CS low | chip_address(0x9E) | register_address | data0 | ... dataN | CS high 
     *  - reg_addr[7] = auto-increment bit
     *  - reg_addr[6:0] = register address
     */
    uint8_t chip_addr = CLOCKGEN7_SPI_CHIP_ADDRESS;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &chip_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t clockgen7_spi_read ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* The CS2501 does not support SPI read. */
    return CLOCKGEN7_ERROR;
}

// ------------------------------------------------------------------------ END

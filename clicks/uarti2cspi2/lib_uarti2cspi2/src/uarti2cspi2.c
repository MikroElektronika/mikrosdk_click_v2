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
 * @file uarti2cspi2.c
 * @brief UART I2C SPI 2 Click Driver.
 */

#include "uarti2cspi2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY   0x00

/**
 * @brief UART I2C SPI 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t uarti2cspi2_i2c_write ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief UART I2C SPI 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t uarti2cspi2_i2c_read ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief UART I2C SPI 2 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t uarti2cspi2_spi_write ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief UART I2C SPI 2 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t uarti2cspi2_spi_read ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void uarti2cspi2_cfg_setup ( uarti2cspi2_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = UARTI2CSPI2_DEVICE_ADDRESS_A1A0_11;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = UARTI2CSPI2_DRV_SEL_SPI;
}

void uarti2cspi2_drv_interface_sel ( uarti2cspi2_cfg_t *cfg, uarti2cspi2_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t uarti2cspi2_init ( uarti2cspi2_t *ctx, uarti2cspi2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( UARTI2CSPI2_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = uarti2cspi2_i2c_read;
        ctx->write_f = uarti2cspi2_i2c_write;
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

        ctx->read_f  = uarti2cspi2_spi_read;
        ctx->write_f = uarti2cspi2_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return UARTI2CSPI2_OK;
}

err_t uarti2cspi2_default_cfg ( uarti2cspi2_t *ctx )
{
    err_t error_flag = UARTI2CSPI2_OK;
    uarti2cspi2_enable_device ( ctx );
    if ( UARTI2CSPI2_ERROR == uarti2cspi2_check_com ( ctx ) )
    {
        return UARTI2CSPI2_ERROR;
    }
    uarti2cspi2_select_uart_0 ( ctx );
    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_CLKSRC, UARTI2CSPI2_CLKSRC_PLL_BYPASS | 
                                                                       UARTI2CSPI2_CLKSRC_CRYSTAL_EN );
    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_LCR, UARTI2CSPI2_LCR_STOP_BITS_1 | 
                                                                    UARTI2CSPI2_LCR_WORD_LENGTH_8 );
    error_flag |= uarti2cspi2_set_baud_rate ( ctx, UARTI2CSPI2_BAUDRATE_115200, NULL );
    
    uarti2cspi2_select_uart_1 ( ctx );
    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_CLKSRC, UARTI2CSPI2_CLKSRC_PLL_BYPASS | 
                                                                       UARTI2CSPI2_CLKSRC_CRYSTAL_EN );
    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_LCR, UARTI2CSPI2_LCR_STOP_BITS_1 | 
                                                                    UARTI2CSPI2_LCR_WORD_LENGTH_8 );
    error_flag |= uarti2cspi2_set_baud_rate ( ctx, UARTI2CSPI2_BAUDRATE_9600, NULL );
    return error_flag;
}

err_t uarti2cspi2_write_regs ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t cmd = 0;
    if ( reg > UARTI2CSPI2_REG_REVID )
    {
        return UARTI2CSPI2_ERROR;
    }
    if ( UARTI2CSPI2_DRV_SEL_SPI == ctx->drv_sel )
    {
        if ( reg >= UARTI2CSPI2_REG_TXSYNCH )
        {
            cmd = UARTI2CSPI2_GLOBAL_CMD_EN_EXT_REGMAP;
            ctx->write_f( ctx, UARTI2CSPI2_REG_GLOBAL_CMD, &cmd, 1 );
        }
        else
        {
            cmd = UARTI2CSPI2_GLOBAL_CMD_DIS_EXT_REGMAP;
            ctx->write_f( ctx, UARTI2CSPI2_REG_GLOBAL_CMD, &cmd, 1 );
        }
    }
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t uarti2cspi2_read_regs ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t cmd = 0;
    if ( reg > UARTI2CSPI2_REG_REVID )
    {
        return UARTI2CSPI2_ERROR;
    }
    if ( UARTI2CSPI2_DRV_SEL_SPI == ctx->drv_sel )
    {
        if ( reg >= UARTI2CSPI2_REG_TXSYNCH )
        {
            cmd = UARTI2CSPI2_GLOBAL_CMD_EN_EXT_REGMAP;
            ctx->write_f( ctx, UARTI2CSPI2_REG_GLOBAL_CMD, &cmd, 1 );
        }
        else
        {
            cmd = UARTI2CSPI2_GLOBAL_CMD_DIS_EXT_REGMAP;
            ctx->write_f( ctx, UARTI2CSPI2_REG_GLOBAL_CMD, &cmd, 1 );
        }
    }
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t uarti2cspi2_write_reg ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return uarti2cspi2_write_regs( ctx, reg, &data_in, 1 );
}

err_t uarti2cspi2_read_reg ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return uarti2cspi2_read_regs( ctx, reg, data_out, 1 );
}

err_t uarti2cspi2_check_com ( uarti2cspi2_t *ctx )
{
    uint8_t revid = 0;
    if ( UARTI2CSPI2_OK == uarti2cspi2_read_reg ( ctx, UARTI2CSPI2_REG_REVID, &revid ) )
    {
        if ( UARTI2CSPI2_REVID_MAJOR == ( revid & UARTI2CSPI2_REVID_MAJOR_MASK ) )
        {
            return UARTI2CSPI2_OK;
        }
    }
    return UARTI2CSPI2_ERROR;
}

void uarti2cspi2_enable_device ( uarti2cspi2_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void uarti2cspi2_disable_device ( uarti2cspi2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t uarti2cspi2_get_int_pin ( uarti2cspi2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void uarti2cspi2_select_uart_0 ( uarti2cspi2_t *ctx )
{
    ctx->act_uart = UARTI2CSPI2_UART_SEL_0;
}

void uarti2cspi2_select_uart_1 ( uarti2cspi2_t *ctx )
{
    ctx->act_uart = UARTI2CSPI2_UART_SEL_1;
}

err_t uarti2cspi2_set_baud_rate ( uarti2cspi2_t *ctx, uint32_t baud_rate, uint32_t *act_baud_rate )
{
    err_t error_flag = UARTI2CSPI2_OK;
    uint8_t mode = 0;
    uint16_t div = 0;
    uint32_t frac = 0;
    uint8_t clock_rate = 0;
    uint8_t freq = 0;

    /*
     * Calculate the integer divisor first. Select a proper mode
     * in case if the requested baud is too high for the pre-defined
     * clocks frequency.
     */
    div = UARTI2CSPI2_CRYSTAL_FREQ / baud_rate;
    if ( div < 8 ) 
    {
        /* Mode x4 */
        clock_rate = 4;
        mode = UARTI2CSPI2_BRGCFG_4XMODE;
    } 
    else if ( div < 16 ) 
    {
        /* Mode x2 */
        clock_rate = 8;
        mode = UARTI2CSPI2_BRGCFG_2XMODE;
    } 
    else 
    {
        clock_rate = 16;
    }

    /* Calculate the divisor in accordance with the fraction coefficient */
    div /= clock_rate;
    freq = clock_rate * baud_rate;

    /* Calculate the baud rate fraction */
    if ( div > 0 )
    {
        frac = ( 16 * ( UARTI2CSPI2_CRYSTAL_FREQ % freq ) ) / freq;
    }
    else
    {
        div = 1;
    }

    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_BRGDIVMSB, div >> 8 );
    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_BRGDIVLSB, div );
    error_flag |= uarti2cspi2_write_reg ( ctx, UARTI2CSPI2_REG_BRGCFG, frac | mode );

    /* Calculate the actual baud rate we just programmed */
    if ( NULL != act_baud_rate )
    {
        *act_baud_rate = ( 16 * UARTI2CSPI2_CRYSTAL_FREQ ) / ( clock_rate * ( 16 * div + frac ) );
    }
    return error_flag;
}

err_t uarti2cspi2_write_data ( uarti2cspi2_t *ctx, uint8_t *data_in, uint8_t len )
{
    if ( len > UARTI2CSPI2_FIFO_LEN )
    {
        return UARTI2CSPI2_ERROR;
    }
    return uarti2cspi2_write_regs ( ctx, UARTI2CSPI2_REG_THR, data_in, len );
}

err_t uarti2cspi2_read_data ( uarti2cspi2_t *ctx, uint8_t *data_out, uint8_t len )
{
    if ( len > UARTI2CSPI2_FIFO_LEN )
    {
        return UARTI2CSPI2_ERROR;
    }
    return uarti2cspi2_read_regs ( ctx, UARTI2CSPI2_REG_RHR, data_out, len );
}

static err_t uarti2cspi2_i2c_write ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ UARTI2CSPI2_FIFO_LEN + 1 ] = { 0 };
    if ( len > UARTI2CSPI2_FIFO_LEN )
    {
        return UARTI2CSPI2_ERROR;
    }
    if ( ( UARTI2CSPI2_UART_SEL_1 == ctx->act_uart ) && ( UARTI2CSPI2_I2C_UART_SEL_1 != ( ctx->slave_address & UARTI2CSPI2_I2C_UART_SEL_MASK ) ) )
    {
        ctx->slave_address &= ( ~UARTI2CSPI2_I2C_UART_SEL_MASK );
        ctx->slave_address |= UARTI2CSPI2_I2C_UART_SEL_1;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    else if ( ( UARTI2CSPI2_UART_SEL_0 == ctx->act_uart ) && ( UARTI2CSPI2_I2C_UART_SEL_0 != ( ctx->slave_address & UARTI2CSPI2_I2C_UART_SEL_MASK ) ) )
    {
        ctx->slave_address &= ( ~UARTI2CSPI2_I2C_UART_SEL_MASK );
        ctx->slave_address |= UARTI2CSPI2_I2C_UART_SEL_0;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t uarti2cspi2_i2c_read ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    if ( len > UARTI2CSPI2_FIFO_LEN )
    {
        return UARTI2CSPI2_ERROR;
    }
    if ( ( UARTI2CSPI2_UART_SEL_1 == ctx->act_uart ) && 
         ( UARTI2CSPI2_I2C_UART_SEL_1 != ( ctx->slave_address & UARTI2CSPI2_I2C_UART_SEL_MASK ) ) )
    {
        ctx->slave_address &= ( ~UARTI2CSPI2_I2C_UART_SEL_MASK );
        ctx->slave_address |= UARTI2CSPI2_I2C_UART_SEL_1;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    else if ( ( UARTI2CSPI2_UART_SEL_0 == ctx->act_uart ) && 
              ( UARTI2CSPI2_I2C_UART_SEL_0 != ( ctx->slave_address & UARTI2CSPI2_I2C_UART_SEL_MASK ) ) )
    {
        ctx->slave_address &= ( ~UARTI2CSPI2_I2C_UART_SEL_MASK );
        ctx->slave_address |= UARTI2CSPI2_I2C_UART_SEL_0;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t uarti2cspi2_spi_write ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t cmd = ( reg & UARTI2CSPI2_SPI_REG_MASK ) | UARTI2CSPI2_SPI_WRITE_BIT;
    if ( len > UARTI2CSPI2_FIFO_LEN )
    {
        return UARTI2CSPI2_ERROR;
    }
    if ( UARTI2CSPI2_UART_SEL_1 == ctx->act_uart )
    {
        cmd |= UARTI2CSPI2_SPI_UART_SEL_1;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t uarti2cspi2_spi_read ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t cmd = ( reg & UARTI2CSPI2_SPI_REG_MASK );
    if ( len > UARTI2CSPI2_FIFO_LEN )
    {
        return UARTI2CSPI2_ERROR;
    }
    if ( UARTI2CSPI2_UART_SEL_1 == ctx->act_uart )
    {
        cmd |= UARTI2CSPI2_SPI_UART_SEL_1;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END

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
 * @file solidswitch9.c
 * @brief SolidSwitch 9 Click Driver.
 */

#include "solidswitch9.h"

/**
 * @brief SPI Dummy and operation codes data.
 * @details Definition of SPI Dummy and operation codes data.
 */
#define SOLIDSWITCH9_SPI_DUMMY          0x00
#define SOLIDSWITCH9_SPI_OC_WRITE       0x00
#define SOLIDSWITCH9_SPI_OC_READ        0x40
#define SOLIDSWITCH9_SPI_OC_READ_CLEAR  0x80
#define SOLIDSWITCH9_SPI_OC_READ_ROM    0xC0
#define SOLIDSWITCH9_SPI_OC_MASK        0xC0
#define SOLIDSWITCH9_SPI_PARITY_BIT     0x01

/**
 * @brief Three bytes to dword macro.
 * @details Definition of three bytes to dword conversion.
 */
#define THREE_BYTES_TO_DWORD( x )  ( ( ( uint32_t ) x[ 0 ] << 16 ) | ( ( uint16_t ) x[ 1 ] << 8 ) | x[ 2 ] )

/**
 * @brief SolidSwitch 9 SPI transfer function.
 * @details This function performs an SPI data transfer where the same buffer is used for both sending 
 * and receiving data for the SolidSwitch 9 Click board.
 * @param[in,out] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in,out] data_io : Pointer to the data buffer for both transmitting and receiving data.
 * @param[in] len : Number of bytes to transfer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t solidswitch9_spi_transfer ( solidswitch9_t *ctx, uint8_t *data_io, uint8_t len );

/**
 * @brief SolidSwitch 9 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] data_in : 24-bit SPI frame data from which it will calculate the parity bit.
 * @return @li @c 1 - Even parity (inverted),
 *         @li @c 0 - ODD parity (inverted).
 * @note None.
 */
static uint8_t solidswitch9_get_parity ( uint32_t data_in );

void solidswitch9_cfg_setup ( solidswitch9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->di0  = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->di1  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->dev_pwm_freq = SOLIDSWITCH9_DEF_FREQ;
}

err_t solidswitch9_init ( solidswitch9_t *ctx, solidswitch9_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, SOLIDSWITCH9_SPI_DUMMY ) ) 
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

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->di0, cfg->di0 );
    digital_out_init( &ctx->di1, cfg->di1 );

    return SPI_MASTER_SUCCESS;
}

err_t solidswitch9_default_cfg ( solidswitch9_t *ctx ) 
{
    err_t error_flag = SOLIDSWITCH9_OK;
    
    error_flag |= solidswitch9_set_duty_cycle ( ctx, SOLIDSWITCH9_DEF_DUTY_CYCLE );
    error_flag |= solidswitch9_pwm_start ( ctx );

    digital_out_low ( &ctx->di0 );
    digital_out_low ( &ctx->di1 );

    error_flag |= solidswitch9_sw_reset ( ctx );
    Delay_100ms ( );
    error_flag |= solidswitch9_check_info ( ctx );
    return error_flag;
}

err_t solidswitch9_write_reg ( solidswitch9_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg & ( ~SOLIDSWITCH9_SPI_OC_MASK ) ) | SOLIDSWITCH9_SPI_OC_WRITE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFE );
    data_buf[ 2 ] = solidswitch9_get_parity ( THREE_BYTES_TO_DWORD ( data_buf ) );
    error_flag |= solidswitch9_spi_transfer ( ctx, data_buf, 3 );
    if ( ( data_buf[ 2 ] & SOLIDSWITCH9_SPI_PARITY_BIT ) != 
           solidswitch9_get_parity ( THREE_BYTES_TO_DWORD ( data_buf ) ) )
    {
        error_flag |= SOLIDSWITCH9_ERROR;
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        ctx->status = data_buf[ 0 ];
    }
    return error_flag;
}

err_t solidswitch9_read_reg ( solidswitch9_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg & ( ~SOLIDSWITCH9_SPI_OC_MASK ) ) | SOLIDSWITCH9_SPI_OC_READ;
    data_buf[ 1 ] = SOLIDSWITCH9_SPI_DUMMY;
    data_buf[ 2 ] = SOLIDSWITCH9_SPI_DUMMY;
    data_buf[ 2 ] = solidswitch9_get_parity ( THREE_BYTES_TO_DWORD ( data_buf ) );
    error_flag |= solidswitch9_spi_transfer ( ctx, data_buf, 3 );
    if ( ( data_buf[ 2 ] & SOLIDSWITCH9_SPI_PARITY_BIT ) != 
           solidswitch9_get_parity ( THREE_BYTES_TO_DWORD ( data_buf ) ) )
    {
        error_flag |= SOLIDSWITCH9_ERROR;
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        ctx->status = data_buf[ 0 ];
        if ( NULL != data_out )
        {
            *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        }
    }
    return error_flag;
}

err_t solidswitch9_read_reg_clear ( solidswitch9_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg & ( ~SOLIDSWITCH9_SPI_OC_MASK ) ) | SOLIDSWITCH9_SPI_OC_READ_CLEAR;
    data_buf[ 1 ] = SOLIDSWITCH9_SPI_DUMMY;
    data_buf[ 2 ] = SOLIDSWITCH9_SPI_DUMMY;
    data_buf[ 2 ] = solidswitch9_get_parity ( THREE_BYTES_TO_DWORD ( data_buf ) );
    error_flag |= solidswitch9_spi_transfer ( ctx, data_buf, 3 );
    if ( ( data_buf[ 2 ] & SOLIDSWITCH9_SPI_PARITY_BIT ) != 
           solidswitch9_get_parity ( THREE_BYTES_TO_DWORD ( data_buf ) ) )
    {
        error_flag |= SOLIDSWITCH9_ERROR;
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        ctx->status = data_buf[ 0 ];
        if ( NULL != data_out )
        {
            *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        }
    }
    return error_flag;
}

err_t solidswitch9_read_rom ( solidswitch9_t *ctx, uint8_t addr, uint8_t *data_out )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( addr & ( ~SOLIDSWITCH9_SPI_OC_MASK ) ) | SOLIDSWITCH9_SPI_OC_READ_ROM;
    data_buf[ 1 ] = SOLIDSWITCH9_SPI_DUMMY;
    data_buf[ 2 ] = SOLIDSWITCH9_SPI_DUMMY;
    error_flag |= solidswitch9_spi_transfer ( ctx, data_buf, 3 );
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        ctx->status = data_buf[ 0 ];
        if ( NULL != data_out )
        {
            *data_out = data_buf[ 1 ];
        }
    }
    return error_flag;
}

err_t solidswitch9_set_duty_cycle ( solidswitch9_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t solidswitch9_pwm_stop ( solidswitch9_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t solidswitch9_pwm_start ( solidswitch9_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void solidswitch9_set_in0_pin ( solidswitch9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->di0, state );
}

void solidswitch9_set_in1_pin ( solidswitch9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->di1, state );
}

err_t solidswitch9_sw_reset ( solidswitch9_t *ctx )
{
    return solidswitch9_read_rom ( ctx, SOLIDSWITCH9_ROM_SW_RESET, NULL );
}

err_t solidswitch9_clear_all_status ( solidswitch9_t *ctx )
{
    return solidswitch9_read_reg_clear ( ctx, SOLIDSWITCH9_REG_CLEAR_ALL_STATUS, NULL );
}

err_t solidswitch9_check_info ( solidswitch9_t *ctx )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint8_t rom_data = 0;
    error_flag |= solidswitch9_read_rom ( ctx, SOLIDSWITCH9_ROM_COMPANY_CODE, &rom_data );
    if ( SOLIDSWITCH9_INFO_COMPANY_CODE != rom_data )
    {
        error_flag |= SOLIDSWITCH9_ERROR;
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        error_flag |= solidswitch9_read_rom ( ctx, SOLIDSWITCH9_ROM_DEVICE_FAMILY, &rom_data );
        if ( SOLIDSWITCH9_INFO_DEVICE_FAMILY != rom_data )
        {
            error_flag |= SOLIDSWITCH9_ERROR;
        }
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        error_flag |= solidswitch9_read_rom ( ctx, SOLIDSWITCH9_ROM_PRODUCT_CODE_1, &rom_data );
        if ( SOLIDSWITCH9_INFO_PRODUCT_CODE_1 != rom_data )
        {
            error_flag |= SOLIDSWITCH9_ERROR;
        }
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        error_flag |= solidswitch9_read_rom ( ctx, SOLIDSWITCH9_ROM_PRODUCT_CODE_2, &rom_data );
        if ( SOLIDSWITCH9_INFO_PRODUCT_CODE_2 != rom_data )
        {
            error_flag |= SOLIDSWITCH9_ERROR;
        }
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        error_flag |= solidswitch9_read_rom ( ctx, SOLIDSWITCH9_ROM_PRODUCT_CODE_3, &rom_data );
        if ( SOLIDSWITCH9_INFO_PRODUCT_CODE_3 != rom_data )
        {
            error_flag |= SOLIDSWITCH9_ERROR;
        }
    }
    return error_flag;
}

err_t solidswitch9_unlock_write ( solidswitch9_t *ctx )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint16_t ctrl = 0;
    error_flag |= solidswitch9_read_reg ( ctx, SOLIDSWITCH9_REG_CTRL, &ctrl );
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        ctrl |= SOLIDSWITCH9_CTRL_UNLOCK;
        error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_CTRL, ctrl );
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        ctrl &= ( ~( SOLIDSWITCH9_CTRL_GOSTBY | SOLIDSWITCH9_CTRL_UNLOCK ) );
        ctrl |= SOLIDSWITCH9_CTRL_EN;
        error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_CTRL, ctrl );
    }
    return error_flag;
}

err_t solidswitch9_set_out_duty ( solidswitch9_t *ctx, uint8_t out_mask, uint16_t duty )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint16_t outctrcr = 0;
    if ( ( out_mask > SOLIDSWITCH9_OUT_MASK ) || ( duty > SOLIDSWITCH9_OUT_DUTY_100_PCT ) )
    {
        return SOLIDSWITCH9_ERROR;
    }
    
    if ( out_mask & SOLIDSWITCH9_OUT0 )
    {
        error_flag |= solidswitch9_read_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR0, &outctrcr );
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            error_flag |= solidswitch9_unlock_write ( ctx );
        }
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            outctrcr &= ( ~SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            outctrcr |= ( ( ( uint16_t ) duty << 4 ) & SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            ctx->wdtb ^= SOLIDSWITCH9_OUTCTRCRX_WDTB;
            outctrcr |= ctx->wdtb; // WDT must be toggled up to every 30ms to avoid entering fail-safe mode
            error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR0, outctrcr );
        }
    }
    
    if ( out_mask & SOLIDSWITCH9_OUT1 )
    {
        error_flag |= solidswitch9_read_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR1, &outctrcr );
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            error_flag |= solidswitch9_unlock_write ( ctx );
        }
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            outctrcr &= ( ~SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            outctrcr |= ( ( ( uint16_t ) duty << 4 ) & SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            ctx->wdtb ^= SOLIDSWITCH9_OUTCTRCRX_WDTB;
            outctrcr |= ctx->wdtb; // WDT must be toggled at least every 30ms to avoid entering fail-safe mode
            error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR1, outctrcr );
        }
    }
    
    if ( out_mask & SOLIDSWITCH9_OUT2 )
    {
        error_flag |= solidswitch9_read_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR2, &outctrcr );
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            error_flag |= solidswitch9_unlock_write ( ctx );
        }
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            outctrcr &= ( ~SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            outctrcr |= ( ( ( uint16_t ) duty << 4 ) & SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            ctx->wdtb ^= SOLIDSWITCH9_OUTCTRCRX_WDTB;
            outctrcr |= ctx->wdtb; // WDT must be toggled at least every 30ms to avoid entering fail-safe mode
            error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR2, outctrcr );
        }
    }
    
    if ( out_mask & SOLIDSWITCH9_OUT3 )
    {
        error_flag |= solidswitch9_read_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR3, &outctrcr );
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            error_flag |= solidswitch9_unlock_write ( ctx );
        }
        if ( SOLIDSWITCH9_OK == error_flag )
        {
            outctrcr &= ( ~SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            outctrcr |= ( ( ( uint16_t ) duty << 4 ) & SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK );
            ctx->wdtb ^= SOLIDSWITCH9_OUTCTRCRX_WDTB;
            outctrcr |= ctx->wdtb; // WDT must be toggled up to every 30ms to avoid entering fail-safe mode
            error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_OUTCTRCR3, outctrcr );
        }
    }
    return error_flag;
}

err_t solidswitch9_enable_out ( solidswitch9_t *ctx, uint8_t out_mask )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    uint16_t socr = 0;
    uint16_t ctrl = 0;
    if ( out_mask > SOLIDSWITCH9_OUT_MASK )
    {
        return SOLIDSWITCH9_ERROR;
    }
    error_flag |= solidswitch9_read_reg ( ctx, SOLIDSWITCH9_REG_SOCR, &socr );
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        error_flag |= solidswitch9_unlock_write ( ctx );
    }
    if ( SOLIDSWITCH9_OK == error_flag )
    {
        socr &= ( ~SOLIDSWITCH9_SOCR_CHX_MASK );
        socr |= ( ( ( uint16_t ) out_mask << 8 ) & SOLIDSWITCH9_SOCR_CHX_MASK );
        ctx->wdtb ^= SOLIDSWITCH9_SOCR_WDTB;
        socr |= ctx->wdtb; // WDT must be toggled up to every 30ms to avoid entering fail-safe mode
        error_flag |= solidswitch9_write_reg ( ctx, SOLIDSWITCH9_REG_SOCR, socr );
    }
    return error_flag;
}

static err_t solidswitch9_spi_transfer ( solidswitch9_t *ctx, uint8_t *data_io, uint8_t len )
{
    err_t error_flag = SOLIDSWITCH9_OK;
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        spi_master_set_default_write_data( &ctx->spi, data_io[ cnt ] );
        error_flag |= spi_master_read( &ctx->spi, &data_io[ cnt ], 1 );
    }
    spi_master_set_default_write_data( &ctx->spi, SOLIDSWITCH9_SPI_DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static uint8_t solidswitch9_get_parity ( uint32_t data_in )
{
    uint32_t temp_data = data_in & 0xFFFFFE;
    uint8_t parity = 0;
    while ( temp_data )
    {
        parity += ( temp_data & 1 );
        temp_data >>= 1;
    }
    parity += 1;
    return ( parity & 1 );
}

// ------------------------------------------------------------------------- END

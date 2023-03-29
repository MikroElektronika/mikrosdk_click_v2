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
 * @file solidswitch2.c
 * @brief SolidSwitch 2 Click Driver.
 */

#include "solidswitch2.h"

/**
 * @brief Two bytes to word macro.
 * @details Definition of two bytes to word conversion.
 */
#define TWO_BYTES_TO_WORD( x )  ( ( ( uint16_t ) x[ 0 ] << 8 ) | x[ 1 ] ) 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                   0x00

/**
 * @brief SolidSwitch 2 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #solidswitch2_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t solidswitch2_calculate_parity_bit ( uint16_t data_in );

void solidswitch2_cfg_setup ( solidswitch2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->idle = HAL_PIN_NC;
    cfg->in0  = HAL_PIN_NC;
    cfg->in1  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t solidswitch2_init ( solidswitch2_t *ctx, solidswitch2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->idle, cfg->idle );
    digital_out_init( &ctx->in0, cfg->in0 );
    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_low ( &ctx->idle );
    digital_out_low ( &ctx->in0 );
    digital_out_low ( &ctx->in1 );
    Delay_100ms ( );
    
    digital_out_high ( &ctx->idle );
    digital_out_high ( &ctx->in0 );
    digital_out_high ( &ctx->in1 );
    Delay_100ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t solidswitch2_default_cfg ( solidswitch2_t *ctx ) 
{
    err_t error_flag = SOLIDSWITCH2_OK;
    if ( SOLIDSWITCH2_ERROR == solidswitch2_check_communication ( ctx ) )
    {
        return SOLIDSWITCH2_ERROR;
    }
    // Perform software reset
    error_flag |= solidswitch2_soft_reset ( ctx );
    Delay_100ms ( );
    
    // Set PWM frequency for LED and GEN PWM to 122.5Hz
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_CFG_1, SOLIDSWITCH2_CFG_1_PWM_DIV_LED_122p5Hz );
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_CFG_2, SOLIDSWITCH2_CFG_2_PWM_DIV_GEN_122p5Hz );
    
    // MAP IN0 pin to OUT2
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_MAP_IN0, SOLIDSWITCH2_OUT2 );
    
    // MAP IN1 pin to OUT3
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_MAP_IN1, SOLIDSWITCH2_OUT3 );
    
    // MAP PWM to OUT4-7
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_MAP_PWM, SOLIDSWITCH2_OUT7 | SOLIDSWITCH2_OUT6 | 
                                                                               SOLIDSWITCH2_OUT5 | SOLIDSWITCH2_OUT4 );
    // Select PWM_LED for OUT7 and OUT6, and PWM_GEN for other outputs
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_PWM_SEL, SOLIDSWITCH2_OUT7 | SOLIDSWITCH2_OUT6 );
    
    // Set PWM duty cycle for LED and GEN PWM to minimum
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_PWM_GEN_DC, SOLIDSWITCH2_MIN_DUTY_CYCLE );
    error_flag |= solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_PWM_LED_DC, SOLIDSWITCH2_MIN_DUTY_CYCLE );
    return error_flag;
}

err_t solidswitch2_write_register ( solidswitch2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = SOLIDSWITCH2_SPI_RW_BIT | ( ( reg & SOLIDSWITCH2_ADDRESS_BIT_MASK ) << 2 ) | ( data_in >> 6 );
    data_buf[ 1 ] = ( data_in << 2 );
    data_buf[ 1 ] |= ( solidswitch2_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) << 1 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t solidswitch2_read_register ( solidswitch2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( ( reg & SOLIDSWITCH2_ADDRESS_BIT_MASK ) << 2 );
    data_buf[ 1 ] = DUMMY;    
    data_buf[ 1 ] |= ( solidswitch2_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) << 1 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_50us ( );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( data_buf[ 0 ] & SOLIDSWITCH2_SPI_ERROR_BIT ) || 
         ( ( ( data_buf[ 0 ] >> 2 ) & SOLIDSWITCH2_ADDRESS_BIT_MASK ) != reg ) || 
         ( ( ( data_buf[ 1 ] >> 1 ) & SOLIDSWITCH2_ODD_PARITY ) != 
           solidswitch2_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) ) )
    {
        return SOLIDSWITCH2_ERROR;
    }
    *data_out = ( data_buf[ 0 ] << 6 ) | ( data_buf[ 1 ] >> 2 );
    return error_flag;
}

err_t solidswitch2_check_communication ( solidswitch2_t *ctx )
{
    uint8_t chip_id;
    if ( SOLIDSWITCH2_OK == solidswitch2_read_register ( ctx, SOLIDSWITCH2_REG_CHIP_ID, &chip_id ) )
    {
        if ( SOLIDSWITCH2_CHIP_ID == chip_id )
        {
            return SOLIDSWITCH2_OK;
        }
    }
    return SOLIDSWITCH2_ERROR;
}

void solidswitch2_set_idle_pin ( solidswitch2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->idle, state );
}

void solidswitch2_set_in0_pin ( solidswitch2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in0, state );
}

void solidswitch2_set_in1_pin ( solidswitch2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in1, state );
}

void solidswitch2_toggle_in0_pin ( solidswitch2_t *ctx )
{
    digital_out_toggle ( &ctx->in0 );
}

void solidswitch2_toggle_in1_pin ( solidswitch2_t *ctx )
{
    digital_out_toggle ( &ctx->in1 );
}

err_t solidswitch2_soft_reset ( solidswitch2_t *ctx )
{
    return solidswitch2_write_register ( ctx, SOLIDSWITCH2_REG_CFG_1, SOLIDSWITCH2_CFG_1_RST );
}

static uint8_t solidswitch2_calculate_parity_bit ( uint16_t data_in )
{
    uint8_t parity = SOLIDSWITCH2_ODD_PARITY;
    data_in >>= 2;
    while ( data_in & 0x3FFF )
    {
        parity += ( data_in & SOLIDSWITCH2_ODD_PARITY );
        data_in >>= 1;
    }
    return parity & SOLIDSWITCH2_ODD_PARITY;
}

// ------------------------------------------------------------------------- END

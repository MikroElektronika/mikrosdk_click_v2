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
 * @file stepper7.c
 * @brief Stepper 7 Click Driver.
 */

#include "stepper7.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY   0x00

/**
 * @brief Stepper 7 I/O signal table for full step resolution.
 * @details Specified I/O signal table for full step resolution, set in the following order:
 * I01, I11, PHASE1, I02, I12, and PHASE2.
 */
static uint8_t stepper7_full_step[ 4 ][ 6 ] = 
{
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
};

/**
 * @brief Stepper 7 I/O signal table for half step resolution.
 * @details Specified I/O signal table for half step resolution, set in the following order:
 * I01, I11, PHASE1, I02, I12, and PHASE2.
 */
static uint8_t stepper7_half_step[ 8 ][ 6 ] = 
{
    { 0, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 1, 1 },
    { 1, 1, 0, 0, 1, 1 },
    { 0, 1, 0, 0, 1, 1 },
    { 0, 1, 0, 1, 1, 0 },
    { 0, 1, 0, 0, 1, 0 },
    { 1, 1, 1, 0, 1, 0 },
    { 0, 1, 1, 0, 1, 0 }
};

/**
 * @brief Stepper 7 I/O signal table for 1/8th step resolution.
 * @details Specified I/O signal table for 1/8th step resolution, set in the following order:
 * I01, I11, PHASE1, I02, I12, and PHASE2.
 */
static uint8_t stepper7_micro_step[ 32 ][ 6 ] = 
{
    { 0, 0, 1, 1, 1, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 } 
};

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper7_speed_delay ( uint8_t speed_macro );

/**
 * @brief Set pins for one micro step.
 * @details This function sets I01, I11, PHASE1, I02, I12, and PHASE2 pins for a desired step.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] pins_array : Array of six bytes that contains I01, I11, PHASE1, I02, I12, and PHASE2 pins
 * logic state value.
 * @return Nothing.
 */
static err_t stepper7_set_pins ( stepper7_t *ctx, uint8_t pins_array[ 6 ] );

void stepper7_cfg_setup ( stepper7_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t stepper7_init ( stepper7_t *ctx, stepper7_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    return SPI_MASTER_SUCCESS;
}

err_t stepper7_default_cfg ( stepper7_t *ctx ) 
{
    err_t error_flag = STEPPER7_OK;
    stepper7_reset_device ( ctx );
    error_flag |= stepper7_write_reg ( ctx, STEPPER7_REG_IODIR, STEPPER7_IODIR_DEFAULT );
    error_flag |= stepper7_write_reg ( ctx, STEPPER7_REG_IOCON, STEPPER7_IOCON_DEFAULT );
    error_flag |= stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, STEPPER7_GPIO_CLEAR );
    stepper7_set_direction ( ctx, STEPPER7_DIR_CW );
    stepper7_set_step_mode ( ctx, STEPPER7_MODE_FULL_STEP );
    return error_flag;
}

err_t stepper7_write_reg ( stepper7_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 3 ] = { STEPPER7_SPI_WRITE_OPCODE, reg, data_in };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t stepper7_read_reg ( stepper7_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t data_buf[ 2 ] = { STEPPER7_SPI_READ_OPCODE, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 2, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void stepper7_set_rst_pin ( stepper7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper7_reset_device ( stepper7_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t stepper7_set_phase2_pin ( stepper7_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER7_PIN_HIGH_LEVEL )
    {
        return STEPPER7_ERROR;
    }
    if ( STEPPER7_ERROR == stepper7_read_reg ( ctx, STEPPER7_REG_GPIO, &reg_data ) )
    {
        return STEPPER7_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER7_PIN_PHASE2 ) >> 7 ) )
    {
        return STEPPER7_OK;
    }
    reg_data &= ~STEPPER7_PIN_PHASE2;
    reg_data |= ( state << 7 );
    return stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, reg_data );
}

err_t stepper7_set_phase1_pin ( stepper7_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER7_PIN_HIGH_LEVEL )
    {
        return STEPPER7_ERROR;
    }
    if ( STEPPER7_ERROR == stepper7_read_reg ( ctx, STEPPER7_REG_GPIO, &reg_data ) )
    {
        return STEPPER7_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER7_PIN_PHASE1 ) >> 6 ) )
    {
        return STEPPER7_OK;
    }
    reg_data &= ~STEPPER7_PIN_PHASE1;
    reg_data |= ( state << 6 );
    return stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, reg_data );
}

err_t stepper7_set_i12_pin ( stepper7_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER7_PIN_HIGH_LEVEL )
    {
        return STEPPER7_ERROR;
    }
    if ( STEPPER7_ERROR == stepper7_read_reg ( ctx, STEPPER7_REG_GPIO, &reg_data ) )
    {
        return STEPPER7_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER7_PIN_I12 ) >> 5 ) )
    {
        return STEPPER7_OK;
    }
    reg_data &= ~STEPPER7_PIN_I12;
    reg_data |= ( state << 5 );
    return stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, reg_data );
}

err_t stepper7_set_i02_pin ( stepper7_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER7_PIN_HIGH_LEVEL )
    {
        return STEPPER7_ERROR;
    }
    if ( STEPPER7_ERROR == stepper7_read_reg ( ctx, STEPPER7_REG_GPIO, &reg_data ) )
    {
        return STEPPER7_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER7_PIN_I02 ) >> 4 ) )
    {
        return STEPPER7_OK;
    }
    reg_data &= ~STEPPER7_PIN_I02;
    reg_data |= ( state << 4 );
    return stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, reg_data );
}

err_t stepper7_set_i11_pin ( stepper7_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER7_PIN_HIGH_LEVEL )
    {
        return STEPPER7_ERROR;
    }
    if ( STEPPER7_ERROR == stepper7_read_reg ( ctx, STEPPER7_REG_GPIO, &reg_data ) )
    {
        return STEPPER7_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER7_PIN_I11 ) >> 3 ) )
    {
        return STEPPER7_OK;
    }
    reg_data &= ~STEPPER7_PIN_I11;
    reg_data |= ( state << 3 );
    return stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, reg_data );
}

err_t stepper7_set_i01_pin ( stepper7_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER7_PIN_HIGH_LEVEL )
    {
        return STEPPER7_ERROR;
    }
    if ( STEPPER7_ERROR == stepper7_read_reg ( ctx, STEPPER7_REG_GPIO, &reg_data ) )
    {
        return STEPPER7_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER7_PIN_I01 ) >> 2 ) )
    {
        return STEPPER7_OK;
    }
    reg_data &= ~STEPPER7_PIN_I01;
    reg_data |= ( state << 2 );
    return stepper7_write_reg ( ctx, STEPPER7_REG_GPIO, reg_data );
}

err_t stepper7_enable_device ( stepper7_t *ctx )
{
    err_t error_flag = STEPPER7_OK;
    error_flag |= stepper7_set_i01_pin ( ctx, STEPPER7_PIN_LOW_LEVEL );
    error_flag |= stepper7_set_i11_pin ( ctx, STEPPER7_PIN_LOW_LEVEL );
    error_flag |= stepper7_set_phase1_pin ( ctx, STEPPER7_PIN_LOW_LEVEL );
    error_flag |= stepper7_set_i02_pin ( ctx, STEPPER7_PIN_LOW_LEVEL );
    error_flag |= stepper7_set_i12_pin ( ctx, STEPPER7_PIN_LOW_LEVEL );
    error_flag |= stepper7_set_phase2_pin ( ctx, STEPPER7_PIN_LOW_LEVEL );
    return error_flag;
}

err_t stepper7_disable_device ( stepper7_t *ctx )
{
    err_t error_flag = STEPPER7_OK;
    error_flag |= stepper7_set_i01_pin ( ctx, STEPPER7_PIN_HIGH_LEVEL );
    error_flag |= stepper7_set_i11_pin ( ctx, STEPPER7_PIN_HIGH_LEVEL );
    error_flag |= stepper7_set_phase1_pin ( ctx, STEPPER7_PIN_HIGH_LEVEL );
    error_flag |= stepper7_set_i02_pin ( ctx, STEPPER7_PIN_HIGH_LEVEL );
    error_flag |= stepper7_set_i12_pin ( ctx, STEPPER7_PIN_HIGH_LEVEL );
    error_flag |= stepper7_set_phase2_pin ( ctx, STEPPER7_PIN_HIGH_LEVEL );
    return error_flag;
}

void stepper7_set_step_mode ( stepper7_t *ctx, uint8_t mode )
{
    if ( STEPPER7_MODE_1_OVER_8_STEP == mode )
    {
        ctx->step_mode = STEPPER7_MODE_1_OVER_8_STEP;
    }
    else if ( STEPPER7_MODE_HALF_STEP == mode )
    {
        ctx->step_mode = STEPPER7_MODE_HALF_STEP;
    }
    else
    {
        ctx->step_mode = STEPPER7_MODE_FULL_STEP;
    }
}

void stepper7_set_direction ( stepper7_t *ctx, uint8_t dir )
{
    if ( STEPPER7_DIR_CCW == dir )
    {
        ctx->direction = STEPPER7_DIR_CCW;
    }
    else
    {
        ctx->direction = STEPPER7_DIR_CW;
    }
}

void stepper7_switch_direction ( stepper7_t *ctx )
{
    if ( STEPPER7_DIR_CCW == ctx->direction )
    {
        ctx->direction = STEPPER7_DIR_CW;
    }
    else
    {
        ctx->direction = STEPPER7_DIR_CCW;
    }
}

err_t stepper7_drive_motor ( stepper7_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER7_OK;
    error_flag |= stepper7_enable_device ( ctx );
    for ( uint32_t num_steps = 0; num_steps < steps; num_steps++ )
    {
        if ( STEPPER7_MODE_1_OVER_8_STEP == ctx->step_mode )
        {
            if ( STEPPER7_DIR_CW == ctx->direction )
            {
                error_flag |= stepper7_set_pins ( ctx, stepper7_micro_step[ num_steps % 32 ] );
            }
            else
            {
                error_flag |= stepper7_set_pins ( ctx, stepper7_micro_step[ 31 - ( num_steps % 32 ) ] );
            }
        }
        else if ( STEPPER7_MODE_HALF_STEP == ctx->step_mode )
        {
            if ( STEPPER7_DIR_CW == ctx->direction )
            {
                error_flag |= stepper7_set_pins ( ctx, stepper7_half_step[ num_steps % 8 ] );
            }
            else
            {
                error_flag |= stepper7_set_pins ( ctx, stepper7_half_step[ 7 - ( num_steps % 8 ) ] );
            }
        }
        else
        {
            if ( STEPPER7_DIR_CW == ctx->direction )
            {
                error_flag |= stepper7_set_pins ( ctx, stepper7_full_step[ num_steps % 4 ] );
            }
            else
            {
                error_flag |= stepper7_set_pins ( ctx, stepper7_full_step[ 3 - ( num_steps % 4 ) ] );
            }
        }
        stepper7_speed_delay ( speed );
    }
    error_flag |= stepper7_disable_device ( ctx );
    return error_flag;
}

static void stepper7_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER7_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER7_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER7_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER7_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER7_SPEED_VERY_FAST:
        {
            Delay_500us( );
            break;
        }
        default:
        {
            Delay_1ms( );
            break;
        }
    }
}

static err_t stepper7_set_pins ( stepper7_t *ctx, uint8_t pins_array[ 6 ] )
{
    err_t error_flag = STEPPER7_OK;
    error_flag |= stepper7_set_i01_pin ( ctx, pins_array[ 0 ] );
    error_flag |= stepper7_set_i11_pin ( ctx, pins_array[ 1 ] );
    error_flag |= stepper7_set_phase1_pin ( ctx, pins_array[ 2 ] );
    error_flag |= stepper7_set_i02_pin ( ctx, pins_array[ 3 ] );
    error_flag |= stepper7_set_i12_pin ( ctx, pins_array[ 4 ] );
    error_flag |= stepper7_set_phase2_pin ( ctx, pins_array[ 5 ] );
    return error_flag;
}

// ------------------------------------------------------------------------- END

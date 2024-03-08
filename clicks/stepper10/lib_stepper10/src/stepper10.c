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
 * @file stepper10.c
 * @brief Stepper 10 Click Driver.
 */

#include "stepper10.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper10_speed_delay ( uint8_t speed_macro );

void stepper10_cfg_setup ( stepper10_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER10_DEVICE0_ADDRESS_A2A1_00;

    cfg->spi_speed   = 5000000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
}

err_t stepper10_init ( stepper10_t *ctx, stepper10_cfg_t *cfg ) 
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

    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return STEPPER10_OK;
}

err_t stepper10_default_cfg ( stepper10_t *ctx ) 
{
    err_t error_flag = STEPPER10_OK;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    error_flag |= stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_CONFIG, 
                                                 STEPPER10_TCA9534A_0_DEFAULT_CONFIG );
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    error_flag |= stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_CONFIG, 
                                                 STEPPER10_TCA9534A_1_DEFAULT_CONFIG );
    stepper10_set_direction ( ctx, STEPPER10_DIR_CW );
    stepper10_disable_device ( ctx );
    stepper10_reset_device ( ctx );
    error_flag |= stepper10_select_gpio ( ctx );
    error_flag |= stepper10_set_step_mode ( ctx, STEPPER10_MODE_FULL_STEP );
    error_flag |= stepper10_set_sleep_pin ( ctx, STEPPER10_PIN_STATE_HIGH );
    error_flag |= stepper10_set_mixed_decay ( ctx, STEPPER10_MIXED_DECAY_FAST_37_5 );
    error_flag |= stepper10_set_agc_pin ( ctx, STEPPER10_PIN_STATE_LOW );
    error_flag |= stepper10_set_torque ( ctx, STEPPER10_TORQUE_50 );
    error_flag |= stepper10_set_clim0_pin ( ctx, STEPPER10_PIN_STATE_LOW );
    error_flag |= stepper10_set_edg_sel_pin ( ctx, STEPPER10_PIN_STATE_LOW );
    stepper10_enable_device ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t stepper10_write_spi_bank0 ( stepper10_t *ctx, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->en );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    digital_out_high ( &ctx->en );
    return error_flag;
}

err_t stepper10_write_spi_bank1 ( stepper10_t *ctx, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    digital_out_high ( &ctx->rst );
    digital_out_low ( &ctx->en );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    digital_out_high ( &ctx->en );
    return error_flag;
}

err_t stepper10_tca_write_reg ( stepper10_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper10_tca_read_reg ( stepper10_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper10_get_step_mode ( stepper10_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *mode = reg_data & STEPPER10_PIN0_MS_MASK;
    return STEPPER10_OK;
}

err_t stepper10_set_step_mode ( stepper10_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER10_MODE_1_OVER_128 )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( mode == ( reg_data & STEPPER10_PIN0_MS_MASK ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN0_MS_MASK;
    reg_data |= mode;
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_sleep_pin ( stepper10_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *state = ( reg_data & STEPPER10_PIN0_SLEEP ) >> 3;
    return STEPPER10_OK;
}

err_t stepper10_set_sleep_pin ( stepper10_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER10_PIN_STATE_HIGH )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER10_PIN0_SLEEP ) >> 3 ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN0_SLEEP;
    reg_data |= ( state << 3 );
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_mixed_decay ( stepper10_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *mode = ( ( reg_data & STEPPER10_PIN0_MDT_MASK ) >> 4 );
    return STEPPER10_OK;
}

err_t stepper10_set_mixed_decay ( stepper10_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER10_MIXED_DECAY_ADMD )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( mode == ( ( reg_data & STEPPER10_PIN0_MDT_MASK ) >> 4 ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN0_MDT_MASK;
    reg_data |= ( mode << 4 );
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_agc_pin ( stepper10_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *state = ( reg_data & STEPPER10_PIN0_AGC ) >> 6;
    return STEPPER10_OK;
}

err_t stepper10_set_agc_pin ( stepper10_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER10_PIN_STATE_HIGH )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER10_PIN0_AGC ) >> 6 ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN0_AGC;
    reg_data |= ( state << 6 );
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_select_gpio ( stepper10_t *ctx )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( STEPPER10_PIN0_IF_SEL != ( reg_data & STEPPER10_PIN0_IF_SEL ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN0_IF_SEL;
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_select_spi ( stepper10_t *ctx )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( STEPPER10_PIN0_IF_SEL == ( reg_data & STEPPER10_PIN0_IF_SEL ) )
    {
        return STEPPER10_OK;
    }
    reg_data |= STEPPER10_PIN0_IF_SEL;
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_torque ( stepper10_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *mode = ( reg_data & STEPPER10_PIN1_TORQUE_MASK );
    return STEPPER10_OK;
}

err_t stepper10_set_torque ( stepper10_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER10_TORQUE_10 )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( mode == ( reg_data & STEPPER10_PIN1_TORQUE_MASK ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN1_TORQUE_MASK;
    reg_data |= mode;
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_clim0_pin ( stepper10_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *state = ( reg_data & STEPPER10_PIN1_CLIM0 ) >> 3;
    return STEPPER10_OK;
}

err_t stepper10_set_clim0_pin ( stepper10_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER10_PIN_STATE_HIGH )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER10_PIN1_CLIM0 ) >> 3 ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN1_CLIM0;
    reg_data |= ( state << 3 );
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_edg_sel_pin ( stepper10_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *state = ( reg_data & STEPPER10_PIN1_EDG_SEL ) >> 4;
    return STEPPER10_OK;
}

err_t stepper10_set_edg_sel_pin ( stepper10_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER10_PIN_STATE_HIGH )
    {
        return STEPPER10_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER10_PIN1_EDG_SEL ) >> 4 ) )
    {
        return STEPPER10_OK;
    }
    reg_data &= ~STEPPER10_PIN1_EDG_SEL;
    reg_data |= ( state << 4 );
    return stepper10_tca_write_reg ( ctx, STEPPER10_TCA9534A_REG_OUTPUT, reg_data );
}

err_t stepper10_get_mo_pin ( stepper10_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_INPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *state = ( reg_data & STEPPER10_PIN1_MO ) >> 5;
    return STEPPER10_OK;
}

err_t stepper10_get_lo_state ( stepper10_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address + 1 );
    if ( STEPPER10_ERROR == stepper10_tca_read_reg ( ctx, STEPPER10_TCA9534A_REG_INPUT, &reg_data ) )
    {
        return STEPPER10_ERROR;
    }
    *state = ( reg_data & STEPPER10_PIN1_LO_MASK ) >> 6;
    return STEPPER10_OK;
}

void stepper10_enable_device ( stepper10_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper10_disable_device ( stepper10_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t stepper10_get_int_pin ( stepper10_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void stepper10_set_direction ( stepper10_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper10_switch_direction ( stepper10_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper10_set_rst_pin ( stepper10_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper10_reset_device ( stepper10_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

void stepper10_set_step_pin ( stepper10_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t stepper10_drive_motor ( stepper10_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER10_OK;
    error_flag |= stepper10_set_sleep_pin ( ctx, STEPPER10_PIN_STATE_HIGH );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper10_set_step_pin ( ctx, STEPPER10_PIN_STATE_HIGH );
        stepper10_speed_delay ( speed );
        stepper10_set_step_pin ( ctx, STEPPER10_PIN_STATE_LOW );
        stepper10_speed_delay ( speed );
    }
    error_flag |= stepper10_set_sleep_pin ( ctx, STEPPER10_PIN_STATE_LOW );
    return error_flag;
}

static void stepper10_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER10_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER10_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER10_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER10_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER10_SPEED_VERY_FAST:
        {
            Delay_1ms( );
            break;
        }
        default:
        {
            Delay_5ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END

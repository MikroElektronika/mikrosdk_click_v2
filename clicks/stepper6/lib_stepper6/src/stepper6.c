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
 * @file stepper6.c
 * @brief Stepper 6 Click Driver.
 */

#include "stepper6.h"

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
static void stepper6_speed_delay ( uint8_t speed_macro );

void stepper6_cfg_setup ( stepper6_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER6_DEVICE_ADDRESS_A1A0_11;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t stepper6_init ( stepper6_t *ctx, stepper6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->step, cfg->step );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->rst, cfg->rst );

    return STEPPER6_OK;
}

err_t stepper6_default_cfg ( stepper6_t *ctx ) 
{
    err_t error_flag = STEPPER6_OK;
    stepper6_reset_pca ( ctx );
    // Configure FAULT pin as INPUT, others as OUTPUT
    error_flag |= stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, 
                                                STEPPER6_PCA9538A_DEFAULT_CONFIG );
    stepper6_disable_device ( ctx );
    stepper6_set_direction ( ctx, STEPPER6_DIR_CW );
    error_flag |= stepper6_set_sleep_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
    error_flag |= stepper6_set_trq_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
    error_flag |= stepper6_set_step_mode ( ctx, STEPPER6_MODE_FULL_STEP );
    error_flag |= stepper6_set_dac ( ctx, STEPPER6_DAC_DEFAULT_CONFIG );
    Delay_100ms ( );
    return error_flag;
}

err_t stepper6_set_dac ( stepper6_t *ctx, uint16_t dac_cmd )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( dac_cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( dac_cmd & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t stepper6_pca_write_reg ( stepper6_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper6_pca_read_reg ( stepper6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper6_get_trq_pin ( stepper6_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    if ( reg_data & STEPPER6_PIN_TRQ )
    {
        *state = STEPPER6_PIN_STATE_OPEN;
    }
    else
    {
        if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
        {
            return STEPPER6_ERROR;
        }
        *state = ( reg_data & STEPPER6_PIN_TRQ );
    }
    return STEPPER6_OK;
}

err_t stepper6_set_trq_pin ( stepper6_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER6_PIN_STATE_OPEN )
    {
        return STEPPER6_ERROR;
    }
    
    // Check if decay pin is configured as input (state open) or output (state low/high)
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    
    // Check and configure the pin as input for open state
    if ( STEPPER6_PIN_STATE_OPEN == state)
    {
        if ( STEPPER6_PIN_TRQ == ( reg_data & STEPPER6_PIN_TRQ ) )
        {
            return STEPPER6_OK;
        }
        else
        {
            reg_data |= STEPPER6_PIN_TRQ;
            return stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, reg_data );
        }
    }
    
    // Check and configure the pin as output for low or high states
    if ( STEPPER6_PIN_TRQ == ( reg_data & STEPPER6_PIN_TRQ ) )
    {
        reg_data &= ~STEPPER6_PIN_TRQ;
        if ( STEPPER6_ERROR == stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, reg_data ) )
        {
            return STEPPER6_ERROR;
        }
    }
    
    // Check and configure the pin output state
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    if ( state == ( reg_data & STEPPER6_PIN_TRQ ) )
    {
        return STEPPER6_OK;
    }
    reg_data &= ~STEPPER6_PIN_TRQ;
    reg_data |= state;
    return stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper6_get_m1_pin ( stepper6_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    *state = ( reg_data & STEPPER6_PIN_M1 ) >> 1;
    return STEPPER6_OK;
}

err_t stepper6_set_m1_pin ( stepper6_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER6_PIN_STATE_HIGH )
    {
        return STEPPER6_ERROR;
    }
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    if ( ( state << 1 ) == ( reg_data & STEPPER6_PIN_M1 ) )
    {
        return STEPPER6_OK;
    }
    reg_data &= ~STEPPER6_PIN_M1;
    reg_data |= ( state << 1 );
    return stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper6_get_m0_pin ( stepper6_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    if ( reg_data & STEPPER6_PIN_M0 )
    {
        *state = STEPPER6_PIN_STATE_OPEN;
    }
    else
    {
        if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
        {
            return STEPPER6_ERROR;
        }
        *state = ( reg_data & STEPPER6_PIN_M0 ) >> 2;
    }
    return STEPPER6_OK;
}

err_t stepper6_set_m0_pin ( stepper6_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER6_PIN_STATE_OPEN )
    {
        return STEPPER6_ERROR;
    }
    
    // Check if decay pin is configured as input (state open) or output (state low/high)
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    
    // Check and configure the pin as input for open state
    if ( STEPPER6_PIN_STATE_OPEN == state)
    {
        if ( STEPPER6_PIN_M0 == ( reg_data & STEPPER6_PIN_M0 ) )
        {
            return STEPPER6_OK;
        }
        else
        {
            reg_data |= STEPPER6_PIN_M0;
            return stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, reg_data );
        }
    }
    
    // Check and configure the pin as output for low or high states
    if ( STEPPER6_PIN_M0 == ( reg_data & STEPPER6_PIN_M0 ) )
    {
        reg_data &= ~STEPPER6_PIN_M0;
        if ( STEPPER6_ERROR == stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_CONFIG, reg_data ) )
        {
            return STEPPER6_ERROR;
        }
    }
    
    // Check and configure the pin output state
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER6_PIN_M0 ) >> 2 ) )
    {
        return STEPPER6_OK;
    }
    reg_data &= ~STEPPER6_PIN_M0;
    reg_data |= ( state << 2 );
    return stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper6_get_sleep_pin ( stepper6_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    *state = ( reg_data & STEPPER6_PIN_SLEEP ) >> 3;
    return STEPPER6_OK;
}

err_t stepper6_set_sleep_pin ( stepper6_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER6_PIN_STATE_HIGH )
    {
        return STEPPER6_ERROR;
    }
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    if ( ( state << 3 ) == ( reg_data & STEPPER6_PIN_SLEEP ) )
    {
        return STEPPER6_OK;
    }
    reg_data &= ~STEPPER6_PIN_SLEEP;
    reg_data |= ( state << 3 );
    return stepper6_pca_write_reg ( ctx, STEPPER6_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper6_get_fault_pin ( stepper6_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER6_ERROR == stepper6_pca_read_reg ( ctx, STEPPER6_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return STEPPER6_ERROR;
    }
    *state = ( reg_data & STEPPER6_PIN_FAULT ) >> 4;
    return STEPPER6_OK;
}

void stepper6_enable_device ( stepper6_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper6_disable_device ( stepper6_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper6_set_direction ( stepper6_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper6_switch_direction ( stepper6_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper6_reset_pca ( stepper6_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void stepper6_set_rst_pin ( stepper6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper6_set_step_pin ( stepper6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t stepper6_get_step_mode ( stepper6_t *ctx, uint8_t *mode )
{
    uint8_t m1_state = 0;
    uint8_t m0_state = 0;
    if ( ( STEPPER6_ERROR == stepper6_get_m1_pin ( ctx, &m1_state ) ) || 
         ( STEPPER6_ERROR == stepper6_get_m0_pin ( ctx, &m0_state ) ) || 
         ( NULL == mode ) )
    {
        return STEPPER6_ERROR;
    }
    if ( ( STEPPER6_PIN_STATE_LOW == m1_state ) && ( STEPPER6_PIN_STATE_LOW == m0_state ) )
    {
        *mode = STEPPER6_MODE_FULL_STEP;
    }
    else if ( ( STEPPER6_PIN_STATE_LOW == m1_state ) && ( STEPPER6_PIN_STATE_HIGH == m0_state ) )
    {
        *mode = STEPPER6_MODE_1_OVER_16;
    }
    else if ( ( STEPPER6_PIN_STATE_HIGH == m1_state ) && ( STEPPER6_PIN_STATE_LOW == m0_state ) )
    {
        *mode = STEPPER6_MODE_HALF_STEP;
    }
    else if ( ( STEPPER6_PIN_STATE_HIGH == m1_state ) && ( STEPPER6_PIN_STATE_HIGH == m0_state ) )
    {
        *mode = STEPPER6_MODE_QUARTER_STEP;
    }
    else if ( ( STEPPER6_PIN_STATE_LOW == m1_state ) && ( STEPPER6_PIN_STATE_OPEN == m0_state ) )
    {
        *mode = STEPPER6_MODE_1_OVER_8;
    }
    else if ( ( STEPPER6_PIN_STATE_HIGH == m1_state ) && ( STEPPER6_PIN_STATE_OPEN == m0_state ) )
    {
        *mode = STEPPER6_MODE_HALF_NON_CIRC_STEP;
    }
    return STEPPER6_OK;
}

err_t stepper6_set_step_mode ( stepper6_t *ctx, uint8_t mode )
{
    err_t error_flag = STEPPER6_OK;
    switch ( mode )
    {
        case STEPPER6_MODE_FULL_STEP:
        {
            error_flag |= stepper6_set_m1_pin ( ctx, STEPPER6_PIN_STATE_LOW );
            error_flag |= stepper6_set_m0_pin ( ctx, STEPPER6_PIN_STATE_LOW );
            break;
        }
        case STEPPER6_MODE_1_OVER_16:
        {
            error_flag |= stepper6_set_m1_pin ( ctx, STEPPER6_PIN_STATE_LOW );
            error_flag |= stepper6_set_m0_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
            break;
        }
        case STEPPER6_MODE_HALF_STEP:
        {
            error_flag |= stepper6_set_m1_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
            error_flag |= stepper6_set_m0_pin ( ctx, STEPPER6_PIN_STATE_LOW );
            break;
        }
        case STEPPER6_MODE_QUARTER_STEP:
        {
            error_flag |= stepper6_set_m1_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
            error_flag |= stepper6_set_m0_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
            break;
        }
        case STEPPER6_MODE_1_OVER_8:
        {
            error_flag |= stepper6_set_m1_pin ( ctx, STEPPER6_PIN_STATE_LOW );
            error_flag |= stepper6_set_m0_pin ( ctx, STEPPER6_PIN_STATE_OPEN );
            break;
        }
        case STEPPER6_MODE_HALF_NON_CIRC_STEP:
        {
            error_flag |= stepper6_set_m1_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
            error_flag |= stepper6_set_m0_pin ( ctx, STEPPER6_PIN_STATE_OPEN );
            break;
        }
        default:
        {
            error_flag = STEPPER6_ERROR;
        }
    }
    return error_flag;
}

void stepper6_drive_motor ( stepper6_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper6_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper6_set_step_pin ( ctx, STEPPER6_PIN_STATE_HIGH );
        stepper6_speed_delay ( speed );
        stepper6_set_step_pin ( ctx, STEPPER6_PIN_STATE_LOW );
        stepper6_speed_delay ( speed );
    }
    stepper6_disable_device ( ctx );
}

static void stepper6_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER6_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER6_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER6_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER6_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER6_SPEED_VERY_FAST:
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

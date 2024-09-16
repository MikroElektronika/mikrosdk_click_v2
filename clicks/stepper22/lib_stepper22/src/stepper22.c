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
 * @file stepper22.c
 * @brief Stepper 22 Click Driver.
 */

#include "stepper22.h"

/**
 * @brief SPI read bit and dummy data.
 * @details Definition of SPI read bit and dummy data.
 */
#define DUMMY                   0x00
#define STEPPER22_SPI_READ_BIT  0x80

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper22_speed_delay ( uint8_t speed_macro );

void stepper22_cfg_setup ( stepper22_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->bemf = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER22_DEVICE_ADDRESS_A1A0_00;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t stepper22_init ( stepper22_t *ctx, stepper22_cfg_t *cfg ) 
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->bemf;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return STEPPER22_OK;
}

err_t stepper22_default_cfg ( stepper22_t *ctx ) 
{
    err_t error_flag = STEPPER22_OK;
    stepper22_reset_pca ( ctx );
    // Configure FAULT and STALL pins as INPUT, others as OUTPUT
    error_flag |= stepper22_pca_write_reg ( ctx, STEPPER22_PCA9538A_REG_CONFIG, 
                                                 STEPPER22_PCA9538A_DEFAULT_CONFIG );
    error_flag |= stepper22_disable_device ( ctx );
    error_flag |= stepper22_set_direction ( ctx, STEPPER22_DIR_CW );
    error_flag |= stepper22_set_bin1_pin ( ctx, STEPPER22_PIN_STATE_LOW );
    error_flag |= stepper22_set_bin2_pin ( ctx, STEPPER22_PIN_STATE_LOW );
    error_flag |= stepper22_set_reset_pin ( ctx, STEPPER22_PIN_STATE_HIGH );
    Delay_100ms ( );
    error_flag |= stepper22_set_reset_pin ( ctx, STEPPER22_PIN_STATE_LOW );
    Delay_100ms ( );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_CTRL, STEPPER22_CTRL_DTIME_850_NS | 
                                                                 STEPPER22_CTRL_ISGAIN_5 | 
                                                                 STEPPER22_CTRL_EXSTALL_INT_STALL | 
                                                                 STEPPER22_CTRL_MODE_FULL_STEP | 
                                                                 STEPPER22_CTRL_RSTEP_NO_ACTION | 
                                                                 STEPPER22_CTRL_RDIR_DIR_PIN | 
                                                                 STEPPER22_CTRL_ENBL_MOTOR_ENABLE );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_TORQUE, STEPPER22_TORQUE_SMPLTH_100_US | 
                                                                   STEPPER22_TORQUE_TORQUE_DEFAULT );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_OFF, STEPPER22_OFF_PWMMODE_USE_INDEXER | 
                                                                STEPPER22_OFF_TOFF_24_5_US );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_BLANK, STEPPER22_BLANK_ABT_DISABLE | 
                                                                  STEPPER22_BLANK_TBLANK_2_58_US );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_DECAY, STEPPER22_DECAY_DECMOD_SLOW_MIXED | 
                                                                  STEPPER22_DECAY_TDECAY_8_5_US );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_STALL, STEPPER22_STALL_VDIV_DIV_32 | 
                                                                  STEPPER22_STALL_SDCNT_1_STEP | 
                                                                  STEPPER22_STALL_SDTHR_DEFAULT );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_DRIVE, STEPPER22_DRIVE_IDRIVEP_150_MA | 
                                                                  STEPPER22_DRIVE_IDRIVEN_300_MA | 
                                                                  STEPPER22_DRIVE_TDRIVEP_500_NS | 
                                                                  STEPPER22_DRIVE_TDRIVEN_500_NS | 
                                                                  STEPPER22_DRIVE_OCPDEG_4_US | 
                                                                  STEPPER22_DRIVE_OCPTH_500_MV );
    error_flag |= stepper22_write_reg ( ctx, STEPPER22_REG_STATUS, STEPPER22_STATUS_CLEAR_ALL );
    Delay_100ms ( );
    return error_flag;
}

err_t stepper22_write_reg ( stepper22_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( reg > STEPPER22_REG_STATUS )
    {
        return STEPPER22_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( reg << 4 ) | ( ( uint8_t ) ( ( data_in >> 8 ) & 0x0F ) );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t stepper22_read_reg ( stepper22_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( ( reg > STEPPER22_REG_STATUS ) || ( NULL == data_out ) )
    {
        return STEPPER22_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( reg << 4 ) | STEPPER22_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    err_t error_flag = spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( STEPPER22_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) ( data_buf[ 0 ] & 0x0F ) << 8 ) | ( data_buf[ 1 ] );
    }
    return error_flag;
}

err_t stepper22_pca_write_reg ( stepper22_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper22_pca_read_reg ( stepper22_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper22_read_bemf_voltage ( stepper22_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t stepper22_get_stall_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_STALL ) >> 1;
    return STEPPER22_OK;
}

err_t stepper22_get_fault_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_FAULT ) >> 2;
    return STEPPER22_OK;
}

err_t stepper22_get_bin2_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_BIN2 ) >> 3;
    return STEPPER22_OK;
}

err_t stepper22_set_bin2_pin ( stepper22_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER22_PIN_STATE_HIGH )
    {
        return STEPPER22_ERROR;
    }
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    if ( ( state << 3 ) == ( reg_data & STEPPER22_PIN_BIN2 ) )
    {
        return STEPPER22_OK;
    }
    reg_data &= ~STEPPER22_PIN_BIN2;
    reg_data |= ( state << 3 );
    return stepper22_pca_write_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper22_get_bin1_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_BIN1 ) >> 4;
    return STEPPER22_OK;
}

err_t stepper22_set_bin1_pin ( stepper22_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER22_PIN_STATE_HIGH )
    {
        return STEPPER22_ERROR;
    }
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    if ( ( state << 4 ) == ( reg_data & STEPPER22_PIN_BIN1 ) )
    {
        return STEPPER22_OK;
    }
    reg_data &= ~STEPPER22_PIN_BIN1;
    reg_data |= ( state << 4 );
    return stepper22_pca_write_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper22_get_dir_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_DIR ) >> 5;
    return STEPPER22_OK;
}

err_t stepper22_set_dir_pin ( stepper22_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER22_PIN_STATE_HIGH )
    {
        return STEPPER22_ERROR;
    }
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    if ( ( state << 5 ) == ( reg_data & STEPPER22_PIN_DIR ) )
    {
        return STEPPER22_OK;
    }
    reg_data &= ~STEPPER22_PIN_DIR;
    reg_data |= ( state << 5 );
    return stepper22_pca_write_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper22_get_reset_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_RESET ) >> 6;
    return STEPPER22_OK;
}

err_t stepper22_set_reset_pin ( stepper22_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER22_PIN_STATE_HIGH )
    {
        return STEPPER22_ERROR;
    }
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    if ( ( state << 6 ) == ( reg_data & STEPPER22_PIN_RESET ) )
    {
        return STEPPER22_OK;
    }
    reg_data &= ~STEPPER22_PIN_RESET;
    reg_data |= ( state << 6 );
    return stepper22_pca_write_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper22_get_sleep_pin ( stepper22_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    *state = ( reg_data & STEPPER22_PIN_SLEEP ) >> 7;
    return STEPPER22_OK;
}

err_t stepper22_set_sleep_pin ( stepper22_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER22_PIN_STATE_HIGH )
    {
        return STEPPER22_ERROR;
    }
    if ( STEPPER22_ERROR == stepper22_pca_read_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER22_ERROR;
    }
    if ( ( state << 7 ) == ( reg_data & STEPPER22_PIN_SLEEP ) )
    {
        return STEPPER22_OK;
    }
    reg_data &= ~STEPPER22_PIN_SLEEP;
    reg_data |= ( state << 7 );
    return stepper22_pca_write_reg ( ctx, STEPPER22_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper22_enable_device ( stepper22_t *ctx )
{
    return stepper22_set_sleep_pin ( ctx, STEPPER22_PIN_STATE_HIGH );
}

err_t stepper22_disable_device ( stepper22_t *ctx )
{
    return stepper22_set_sleep_pin ( ctx, STEPPER22_PIN_STATE_LOW );
}

err_t stepper22_set_direction ( stepper22_t *ctx, uint8_t dir )
{
    return stepper22_set_dir_pin ( ctx, dir );
}

err_t stepper22_switch_direction ( stepper22_t *ctx )
{
    uint8_t dir = 0;
    err_t error_flag = stepper22_get_dir_pin ( ctx, &dir );
    if ( STEPPER22_OK == error_flag )
    {
        error_flag = stepper22_set_dir_pin ( ctx, dir ^ STEPPER22_PIN_STATE_HIGH );
    }
    return error_flag;
}

void stepper22_reset_pca ( stepper22_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void stepper22_set_rst_pin ( stepper22_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper22_set_step_pin ( stepper22_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

uint8_t stepper22_get_int_pin ( stepper22_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t stepper22_get_step_mode ( stepper22_t *ctx, uint8_t *mode )
{
    uint16_t reg_data = 0;
    err_t error_flag = stepper22_read_reg ( ctx, STEPPER22_REG_CTRL, &reg_data );
    if ( ( STEPPER22_OK == error_flag ) && ( NULL != mode ) )
    {
        *mode = ( uint8_t ) ( ( reg_data & STEPPER22_CTRL_MODE_MASK ) >> 3 );
    }
    return error_flag;
}

err_t stepper22_set_step_mode ( stepper22_t *ctx, uint8_t mode )
{
    if ( mode > STEPPER22_MODE_1_OVER_256 )
    {
        return STEPPER22_ERROR;
    }
    uint16_t reg_data = 0;
    err_t error_flag = stepper22_read_reg ( ctx, STEPPER22_REG_CTRL, &reg_data );
    if ( STEPPER22_OK == error_flag )
    {
        reg_data &= ~STEPPER22_CTRL_MODE_MASK;
        reg_data |= ( mode << 3 );
        error_flag = stepper22_write_reg ( ctx, STEPPER22_REG_CTRL, reg_data );
    }
    return error_flag;
}

err_t stepper22_drive_motor ( stepper22_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = stepper22_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper22_set_step_pin ( ctx, STEPPER22_PIN_STATE_HIGH );
        stepper22_speed_delay ( speed );
        stepper22_set_step_pin ( ctx, STEPPER22_PIN_STATE_LOW );
        stepper22_speed_delay ( speed );
    }
    error_flag |= stepper22_disable_device ( ctx );
    return error_flag;
}

static void stepper22_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER22_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER22_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER22_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER22_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER22_SPEED_VERY_FAST:
        {
            Delay_500us( );
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

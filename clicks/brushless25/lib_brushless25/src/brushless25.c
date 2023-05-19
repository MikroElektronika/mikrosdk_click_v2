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
 * @file brushless25.c
 * @brief Brushless 25 Click Driver.
 */

#include "brushless25.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x + 1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t brushless25_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void brushless25_cfg_setup ( brushless25_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->fg   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BRUSHLESS25_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->dev_pwm_freq = BRUSHLESS25_DEF_FREQ;
}

err_t brushless25_init ( brushless25_t *ctx, brushless25_cfg_t *cfg ) 
{
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->flt, cfg->flt );
    digital_in_init( &ctx->fg, cfg->fg );

    digital_out_high( &ctx->rst );

    return BRUSHLESS25_OK;
}

err_t brushless25_default_cfg ( brushless25_t *ctx ) 
{
    err_t error_flag = BRUSHLESS25_OK;
    brushless25_set_duty_cycle ( ctx, 0 );
    brushless25_disable_drvoff( ctx );
    
    ctx->crc_en = BRUSHLESS25_CRC_ENABLED;
    
    error_flag |= brushless25_fast_start_config( ctx );
    
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, BRUSHLESS25_CLR_FLT );
    error_flag |= brushless25_set_speed_ctrl_mode( ctx, BRUSHLESS25_ANALOG_SPD_CTRL );
    
    return error_flag;
}

err_t brushless25_set_duty_cycle ( brushless25_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless25_pwm_stop ( brushless25_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless25_pwm_start ( brushless25_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t brushless25_i2c_write ( brushless25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    uint8_t cnt = 0;
    data_buf[ 0 ] = reg;
    for ( cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t brushless25_spi_write ( brushless25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void brushless25_enable_drvoff ( brushless25_t *ctx )
{
    digital_out_low( &ctx->rst );
}

void brushless25_disable_drvoff ( brushless25_t *ctx )
{
    digital_out_high( &ctx->rst );
}

err_t brushless25_cfg_write ( brushless25_t *ctx, uint16_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 0 ] = BRUSHLESS25_OP_W_CW | BRUSHLESS25_32_BIT_DATA_CW | BRUSHLESS25_MEM_SEC;
    data_buf[ 1 ] = BRUSHLESS25_MEM_PAGE | ( ( uint8_t ) ( reg >> 8 ) & 0X0F );
    data_buf[ 2 ] = ( uint8_t ) reg;
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 7 );
}

err_t brushless25_cfg_write_with_crc ( brushless25_t *ctx, uint16_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 8 ] = { 0 };
    uint8_t crc_buf[ 8 ];
    data_buf[ 0 ] = BRUSHLESS25_OP_W_CW | BRUSHLESS25_CRC_EN_CW | BRUSHLESS25_32_BIT_DATA_CW | BRUSHLESS25_MEM_SEC;
    data_buf[ 1 ] = BRUSHLESS25_MEM_PAGE | ( ( uint8_t ) ( reg >> 8 ) & 0X0F );
    data_buf[ 2 ] = ( uint8_t ) reg;
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    crc_buf[ 0 ] = 0x00;
    for ( uint8_t n_cnt = 0; n_cnt < 7; n_cnt++ )
    {
        crc_buf[ n_cnt + 1 ] = data_buf[ n_cnt ];
    }
    data_buf[ 7 ] = brushless25_calculate_crc8( crc_buf, 8 );
    
    return i2c_master_write( &ctx->i2c, data_buf, 8 );;
}

err_t brushless25_register_write ( brushless25_t *ctx, uint16_t reg, uint32_t data_in )
{
    if ( BRUSHLESS25_CRC_ENABLED == ctx->crc_en )
    {
        return brushless25_cfg_write_with_crc( ctx, reg, data_in );
    }
    else
    {
        return brushless25_cfg_write( ctx, reg, data_in );
    }
}

err_t brushless25_cfg_read ( brushless25_t *ctx, uint16_t reg, uint32_t *data_out )
{
    err_t error_flag = BRUSHLESS25_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t data_rx[ 4 ] = { 0 };
    data_buf[ 0 ] = BRUSHLESS25_OP_R_CW | BRUSHLESS25_32_BIT_DATA_CW | BRUSHLESS25_MEM_SEC;
    data_buf[ 1 ] = BRUSHLESS25_MEM_PAGE | ( ( uint8_t ) ( reg >> 8 ) & 0X0F );
    data_buf[ 2 ] = ( uint8_t ) reg;
    error_flag |= i2c_master_write_then_read( &ctx->i2c, data_buf, 3, data_rx, 4 );
    
    if ( BRUSHLESS25_ERROR == error_flag )
    {
        for ( uint8_t n_cnt = 0; n_cnt < 10; n_cnt++ )
        {
            error_flag = i2c_master_read( &ctx->i2c, data_rx, 4 );
            if ( BRUSHLESS25_OK == error_flag )
            {
                break;
            }
            Delay_1ms( );
        }
        if ( BRUSHLESS25_ERROR == error_flag )
        {
            return BRUSHLESS25_ERROR;
        }
    }
    
    *data_out = ( ( uint32_t ) data_rx[ 3 ] << 24 ) | ( ( uint32_t ) data_rx[ 2 ] << 16 ) | 
                ( ( uint16_t ) data_rx[ 1 ] << 8 ) | data_rx[ 0 ];
    return error_flag;
}

err_t brushless25_cfg_read_with_crc ( brushless25_t *ctx, uint16_t reg, uint32_t *data_out )
{
    err_t error_flag = BRUSHLESS25_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t data_rx[ 5 ] = { 0 };
    uint8_t crc_buf[ 9 ];
    data_buf[ 0 ] = BRUSHLESS25_OP_R_CW | BRUSHLESS25_CRC_EN_CW | BRUSHLESS25_32_BIT_DATA_CW | BRUSHLESS25_MEM_SEC;
    data_buf[ 1 ] = BRUSHLESS25_MEM_PAGE | ( ( uint8_t ) ( reg >> 8 ) & 0X0F );
    data_buf[ 2 ] = ( uint8_t ) reg;
    error_flag |= i2c_master_write_then_read( &ctx->i2c, data_buf, 3, data_rx, 5 );
    
    if ( BRUSHLESS25_ERROR == error_flag )
    {
        for ( uint8_t n_cnt = 0; n_cnt < 10; n_cnt++ )
        {
            error_flag = i2c_master_read( &ctx->i2c, data_rx, 4 );
            if ( BRUSHLESS25_OK == error_flag )
            {
                break;
            }
            Delay_1ms( );
        }
        if ( BRUSHLESS25_ERROR == error_flag )
        {
            return BRUSHLESS25_ERROR;
        }
    }
    crc_buf[ 0 ] = 0x00;
    for ( uint8_t n_cnt = 0; n_cnt < 3; n_cnt++ )
    {
        crc_buf[ n_cnt + 1 ] = data_buf[ n_cnt ];
    }
    crc_buf[ 4 ] = 0x01;
    for ( uint8_t n_cnt = 0; n_cnt < 4; n_cnt++ )
    {
        crc_buf[ n_cnt + 5 ] = data_rx[ n_cnt ];
    }
    uint8_t crc_data =  brushless25_calculate_crc8( crc_buf, 9 );
    if ( crc_data == data_rx[ 4 ] )
    {
        *data_out = ( ( uint32_t ) data_rx[ 3 ] << 24 ) | ( ( uint32_t ) data_rx[ 2 ] << 16 ) | 
                ( ( uint16_t ) data_rx[ 1 ] << 8 ) | data_rx[ 0 ];
    }
    else
    {
        return BRUSHLESS25_ERROR;
    }
    
    return error_flag;
}

err_t brushless25_register_read ( brushless25_t *ctx, uint16_t reg, uint32_t *data_out )
{
    if ( BRUSHLESS25_CRC_ENABLED == ctx->crc_en )
    {
        return brushless25_cfg_read_with_crc( ctx, reg, data_out );
    }
    else
    {
        return brushless25_cfg_read( ctx, reg, data_out );
    }
}

err_t brushless25_pot_write ( brushless25_t *ctx, uint8_t cmd, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = BRUSHLESS25_OK;
    uint8_t tx_buf [ 2 ] = { 0 };
    data_in &= 0x01FF;
    tx_buf[ 0 ] = reg << 4;
    tx_buf[ 0 ] |= ( cmd & 0x03 ) << 2;
    tx_buf[ 0 ] |= ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) data_in;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t brushless25_set_wiper_position ( brushless25_t *ctx, uint16_t data_in )
{
    err_t error_flag = BRUSHLESS25_OK;
    
    error_flag |= brushless25_pot_write( ctx, BRUSHLESS25_POT_WRITE_REG_CMD, 
                                         BRUSHLESS25_POT_VOLATILE_WIPER0_REG, data_in );
    
    return error_flag;
}

err_t brushless25_set_speed_ctrl_mode ( brushless25_t *ctx, uint8_t mode )
{
    err_t error_flag = BRUSHLESS25_OK;
    uint32_t tmp_data = 0;
    
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, BRUSHLESS25_EEPROM_READ );
    
    error_flag |= brushless25_register_read( ctx, BRUSHLESS25_REG_PIN_CONFIG1, &tmp_data );
    tmp_data &= ~BRUSHLESS25_SPD_CTRL_MODE_MASK;
    switch ( mode )
    {
        case BRUSHLESS25_PWM_SPD_CTRL:
        {
            ctx->spd_ctrl_mode = BRUSHLESS25_PWM_SPD_CTRL;
            tmp_data |= BRUSHLESS25_SPD_CTRL_MODE_PWM_MODE;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            
            error_flag |= brushless25_pwm_start( ctx );  
            break;
        }
        case BRUSHLESS25_ANALOG_SPD_CTRL:
        {
            ctx->spd_ctrl_mode = BRUSHLESS25_ANALOG_SPD_CTRL;
            tmp_data |= BRUSHLESS25_SPD_CTRL_MODE_ANALOG_MODE;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            break;
        }
        case BRUSHLESS25_I2C_SPD_CTRL:
        {
            ctx->spd_ctrl_mode = BRUSHLESS25_I2C_SPD_CTRL;
            tmp_data |= BRUSHLESS25_SPD_CTRL_MODE_I2C_MODE;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            break;
        }
        default:
        {
            ctx->spd_ctrl_mode = BRUSHLESS25_ANALOG_SPD_CTRL;
            error_flag |= BRUSHLESS25_ERROR;
        }
    }
    
    return error_flag;
}

err_t brushless25_set_speed_value ( brushless25_t *ctx, float spd_val )
{
    err_t error_flag = BRUSHLESS25_OK;
    uint32_t tmp_data = 0;
    
    switch ( ctx->spd_ctrl_mode )
    {
        case BRUSHLESS25_PWM_SPD_CTRL:
        {
            error_flag |= brushless25_set_duty_cycle( ctx, ( spd_val / 100 ) );
            break;
        }
        case BRUSHLESS25_ANALOG_SPD_CTRL:
        {
            if ( 0 == spd_val )
            {
                error_flag |= brushless25_set_wiper_position( ctx, BRUSHLESS25_POT_MAX_VAL );
            }
            else
            {
                error_flag |= brushless25_set_wiper_position( ctx, BRUSHLESS25_POT_MAX_VAL - ( uint16_t ) 
                                                              ( ( spd_val / 100 ) * BRUSHLESS25_POT_MAX_VAL ) );
            }
            break;
        }
        case BRUSHLESS25_I2C_SPD_CTRL:
        {
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_READ );
            error_flag |= brushless25_register_read( ctx, BRUSHLESS25_REG_DEVICE_CTRL, &tmp_data );
            
            tmp_data &= ~BRUSHLESS25_SPEED_CTRL_MASK;
            tmp_data |= ( ( uint32_t ) ( ( spd_val / 100 ) * BRUSHLESS25_SPEED_CMD_MULTIPLAYER ) << 16 );
            tmp_data |= BRUSHLESS25_SPEED_CMD_USING_SPEED_CTRL;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_DEVICE_CTRL, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            
            break;
        }
        default:
        {
            error_flag |= BRUSHLESS25_ERROR;
        }
    }
    
    return error_flag;
}

err_t brushless25_set_brake_state ( brushless25_t *ctx, uint8_t brake_state )
{
    err_t error_flag = BRUSHLESS25_OK;
    uint32_t tmp_data = 0;
    
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, BRUSHLESS25_EEPROM_READ );
    
    error_flag |= brushless25_register_read( ctx, BRUSHLESS25_REG_PIN_CONFIG1, &tmp_data );
    tmp_data &= ~BRUSHLESS25_BRAKE_INPUT_BRAKE_MASK;
    switch ( brake_state )
    {
        case BRUSHLESS25_HW_CTRL_BRAKE:
        {
            tmp_data |= BRUSHLESS25_BRAKE_INPUT_HARDWARE_BRAKE;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            break;
        }
        case BRUSHLESS25_BRAKE_ON:
        {
            tmp_data |= BRUSHLESS25_BRAKE_INPUT_BRAKE_ENABLED;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            break;
        }
        case BRUSHLESS25_BRAKE_OFF:
        {
            tmp_data |= BRUSHLESS25_BRAKE_INPUT_BRAKE_DISABLED;
            
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, tmp_data );
            error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                                 BRUSHLESS25_EEPROM_WRITE );
            break;
        }
        default:
        {
            error_flag |= BRUSHLESS25_ERROR;
        }
    }
    
    return error_flag;
}

err_t brushless25_slow_start_config ( brushless25_t *ctx )
{
    err_t error_flag = BRUSHLESS25_OK;
    
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ISD_CONFIG, 
                                         BRUSHLESS25_SLOW_START_ISD_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_MOTOR_STARTUP1, 
                                         BRUSHLESS25_SLOW_START_MOTOR_STARTUP1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_MOTOR_STARTUP2, 
                                         BRUSHLESS25_SLOW_START_MOTOR_STARTUP2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP1, 
                                         BRUSHLESS25_SLOW_START_CLOSED_LOOP1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP2, 
                                         BRUSHLESS25_SLOW_START_CLOSED_LOOP2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP3, 
                                         BRUSHLESS25_SLOW_START_CLOSED_LOOP3 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP4, 
                                         BRUSHLESS25_SLOW_START_CLOSED_LOOP4 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CONST_SPEED, 
                                         BRUSHLESS25_SLOW_START_CONST_SPEED );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CONST_PWR, 
                                         BRUSHLESS25_SLOW_START_CONST_PWR );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_150_DEG_TWO_PH_PROFILE, 
                                         BRUSHLESS25_SLOW_START_150_DEG_TWO_PH );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_150_DEG_THREE_PH_PROFILE, 
                                         BRUSHLESS25_SLOW_START_150_DEG_THREE_PH );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_TRAP_CONFIG1, 
                                         BRUSHLESS25_SLOW_START_TRAP_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_TRAP_CONFIG2, 
                                         BRUSHLESS25_SLOW_START_TRAP_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_FAULT_CONFIG1, 
                                         BRUSHLESS25_SLOW_START_FAULT_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_FAULT_CONFIG2, 
                                         BRUSHLESS25_SLOW_START_FAULT_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_GD_CONFIG1, 
                                         BRUSHLESS25_SLOW_START_GD_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_GD_CONFIG2, 
                                         BRUSHLESS25_SLOW_START_GD_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, 
                                         BRUSHLESS25_SLOW_START_PIN_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG2, 
                                         BRUSHLESS25_SLOW_START_PIN_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_DEVICE_CONFIG, 
                                         BRUSHLESS25_SLOW_START_DEVICE_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PERIPH_CONFIG, 
                                         BRUSHLESS25_SLOW_START_PERIPH_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1, 
                                         BRUSHLESS25_EEPROM_WRITE );
    return error_flag;
}

err_t brushless25_fast_start_config ( brushless25_t *ctx )
{
    err_t error_flag = BRUSHLESS25_OK;
    
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ISD_CONFIG, 
                                         BRUSHLESS25_FAST_START_ISD_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_MOTOR_STARTUP1, 
                                         BRUSHLESS25_FAST_START_MOTOR_STARTUP1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_MOTOR_STARTUP2, 
                                         BRUSHLESS25_FAST_START_MOTOR_STARTUP2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP1, 
                                         BRUSHLESS25_FAST_START_CLOSED_LOOP1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP2,
                                         BRUSHLESS25_FAST_START_CLOSED_LOOP2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP3, 
                                         BRUSHLESS25_FAST_START_CLOSED_LOOP3 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP4, 
                                         BRUSHLESS25_FAST_START_CLOSED_LOOP4 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CONST_SPEED, 
                                         BRUSHLESS25_FAST_START_CONST_SPEED );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CONST_PWR, 
                                         BRUSHLESS25_FAST_START_CONST_PWR );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_150_DEG_TWO_PH_PROFILE, 
                                         BRUSHLESS25_FAST_START_150_DEG_TWO_PH );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_150_DEG_THREE_PH_PROFILE, 
                                         BRUSHLESS25_FAST_START_150_DEG_THREE_PH );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_TRAP_CONFIG1, 
                                         BRUSHLESS25_FAST_START_TRAP_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_TRAP_CONFIG2, 
                                         BRUSHLESS25_FAST_START_TRAP_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_FAULT_CONFIG1, 
                                         BRUSHLESS25_FAST_START_FAULT_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_FAULT_CONFIG2, 
                                         BRUSHLESS25_FAST_START_FAULT_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_GD_CONFIG1, 
                                         BRUSHLESS25_FAST_START_GD_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_GD_CONFIG2, 
                                         BRUSHLESS25_FAST_START_GD_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1, 
                                         BRUSHLESS25_FAST_START_PIN_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG2, 
                                         BRUSHLESS25_FAST_START_PIN_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_DEVICE_CONFIG, 
                                         BRUSHLESS25_FAST_START_DEVICE_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PERIPH_CONFIG,
                                         BRUSHLESS25_FAST_START_PERIPH_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1,
                                         BRUSHLESS25_EEPROM_WRITE );
    
    return error_flag;
}

err_t brushless25_ultra_fast_start_config ( brushless25_t *ctx )
{
    err_t error_flag = BRUSHLESS25_OK;
    
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_ISD_CONFIG,
                                         BRUSHLESS25_ULTRA_START_ISD_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_MOTOR_STARTUP1,
                                         BRUSHLESS25_ULTRA_START_MOTOR_STARTUP1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_MOTOR_STARTUP2,
                                         BRUSHLESS25_ULTRA_START_MOTOR_STARTUP2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP1,
                                         BRUSHLESS25_ULTRA_START_CLOSED_LOOP1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP2,
                                         BRUSHLESS25_ULTRA_START_CLOSED_LOOP2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP3,
                                         BRUSHLESS25_ULTRA_START_CLOSED_LOOP3 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CLOSED_LOOP4,
                                         BRUSHLESS25_ULTRA_START_CLOSED_LOOP4 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CONST_SPEED,
                                         BRUSHLESS25_ULTRA_START_CONST_SPEED );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_CONST_PWR,
                                         BRUSHLESS25_ULTRA_START_CONST_PWR );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_150_DEG_TWO_PH_PROFILE,
                                         BRUSHLESS25_ULTRA_START_150_DEG_TWO_PH );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_150_DEG_THREE_PH_PROFILE,
                                         BRUSHLESS25_ULTRA_START_150_DEG_THREE_PH );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_TRAP_CONFIG1,
                                         BRUSHLESS25_ULTRA_START_TRAP_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_TRAP_CONFIG2,
                                         BRUSHLESS25_ULTRA_START_TRAP_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_FAULT_CONFIG1,
                                         BRUSHLESS25_ULTRA_START_FAULT_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_FAULT_CONFIG2,
                                         BRUSHLESS25_ULTRA_START_FAULT_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_GD_CONFIG1,
                                         BRUSHLESS25_ULTRA_START_GD_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_GD_CONFIG2,
                                         BRUSHLESS25_ULTRA_START_GD_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG1,
                                         BRUSHLESS25_ULTRA_START_PIN_CONFIG1 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PIN_CONFIG2,
                                         BRUSHLESS25_ULTRA_START_PIN_CONFIG2 );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_DEVICE_CONFIG,
                                         BRUSHLESS25_ULTRA_START_DEVICE_CONFIG );
    error_flag |= brushless25_register_write( ctx, BRUSHLESS25_REG_PERIPH_CONFIG,
                                         BRUSHLESS25_ULTRA_START_PERIPH_CONFIG );
    error_flag |= brushless25_cfg_write( ctx, BRUSHLESS25_REG_ALGO_CTRL1,
                                         BRUSHLESS25_EEPROM_WRITE );
    
    return error_flag;
}

static uint8_t brushless25_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xFF;
    uint8_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data_buf[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x07);
            else
                crc <<= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------ END

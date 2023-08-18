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
 * @file usbcsink3.c
 * @brief USB-C Sink 3 Click Driver.
 */

#include "usbcsink3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void usbcsink3_cfg_setup ( usbcsink3_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCSINK3_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default 
                                                         for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->vref        = USBCSINK3_VREF_3V3;
}

err_t usbcsink3_init ( usbcsink3_t *ctx, usbcsink3_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;
    
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

    adc_cfg.input_pin = cfg->an;

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
    
    return USBCSINK3_OK;
}

err_t usbcsink3_default_cfg ( usbcsink3_t *ctx ) 
{   
    // Sets the output direction of all pins
    err_t err_flag = usbcsink3_i2c_write( ctx, USBCSINK3_REG_CONFIG, USBCSINK3_DIRECTION_OUTPUT );
    Delay_10ms( );
    
    // All the internal pull-up resistors are disabled
    err_flag |= usbcsink3_i2c_write( ctx, USBCSINK3_REG_SPECIAL_FUNC, 
                                          USBCSINK3_SPEC_FUNC_PU_DISABLED );
    Delay_10ms( );
    
    // Voltage: 5.0 [V]
    err_flag |= usbcsink3_set_voltage( ctx, USBCSINK3_VTG_SEL_5V );
    Delay_10ms( );
    
    // Power: 15.0 [W]
    err_flag |= usbcsink3_set_power( ctx, USBCSINK3_PWR_SEL_15W );
    Delay_10ms( );
    
    return err_flag;
}

err_t usbcsink3_i2c_write ( usbcsink3_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t usbcsink3_i2c_read ( usbcsink3_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t usbcsink3_spi_write ( usbcsink3_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t usbcsink3_read_raw_adc ( usbcsink3_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t usbcsink3_read_voltage ( usbcsink3_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t usbcsink3_set_vref ( usbcsink3_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t usbcsink3_get_vbus ( usbcsink3_t *ctx, float *vbus ) 
{
    float voltage = 0.0, vbas_vtg = 0.0;
    err_t err_flag = usbcsink3_read_voltage( ctx, &voltage );
    vbas_vtg = voltage * ( ( USBCSINK3_VBUS_R11_RES_73_2_KOHM + USBCSINK3_VBUS_R13_RES_10_KOHM ) / 
                             USBCSINK3_VBUS_R13_RES_10_KOHM );
    if ( USBCSINK3_VBUS_VTG_17_2V < vbas_vtg )
    {
        *vbus = USBCSINK3_VBUS_VTG_0V;
        err_flag = USBCSINK3_ERROR;
    }
    else
    {
        *vbus = vbas_vtg;
    }
    return err_flag;
}

err_t usbcsink3_set_wiper ( usbcsink3_t *ctx, uint8_t wiper_pos ) 
{
    return usbcsink3_spi_write( ctx, USBCSINK3_CMD_SEL_DATA_WRITE | 
                                     USBCSINK3_POT_SEL_DIGI_POT_1, wiper_pos );
}

err_t usbcsink3_set_resistence ( usbcsink3_t *ctx, float resistence )
{
    uint8_t wiper_pos = DUMMY;
    if ( ( USBCSINK3_RES_6_8_KOHM <= resistence ) && ( USBCSINK3_RES_91_KOHM >= resistence ) )
    {
        wiper_pos = ( uint8_t ) ( ( resistence / USBCSINK3_RES_100_KOHM ) * 
                                      ( float ) USBCSINK3_WIPER_POS_MAX );
    }
    else
    {
        return USBCSINK3_ERROR;
    }
    return usbcsink3_set_wiper( ctx, wiper_pos );
}

err_t usbcsink3_set_voltage ( usbcsink3_t *ctx, usbcsink3_vtg_sel_t voltage )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = usbcsink3_i2c_read( ctx, USBCSINK3_REG_OUTPUT_PORT, &data_buf );
    data_buf &= USBCSINK3_ALL_PINS_BIT_MASK;
    switch ( voltage )
    {
        case USBCSINK3_VTG_SEL_5V: 
        {
            data_buf |= USBCSINK3_VSEL2_DISABLE | USBCSINK3_VSEL1_DISABLE | USBCSINK3_VSEL0_DISABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_9V: 
        {
            data_buf |= USBCSINK3_VSEL2_DISABLE | USBCSINK3_VSEL1_DISABLE | USBCSINK3_VSEL0_ENABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_15V: 
        {
            data_buf |= USBCSINK3_VSEL2_DISABLE | USBCSINK3_VSEL1_ENABLE | USBCSINK3_VSEL0_DISABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_20V: 
        {
            data_buf |= USBCSINK3_VSEL2_DISABLE | USBCSINK3_VSEL1_ENABLE | USBCSINK3_VSEL0_ENABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_4_3V: 
        {
            data_buf |= USBCSINK3_VSEL2_ENABLE | USBCSINK3_VSEL1_DISABLE | USBCSINK3_VSEL0_DISABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_8_6V: 
        {
            data_buf |= USBCSINK3_VSEL2_ENABLE | USBCSINK3_VSEL1_DISABLE | USBCSINK3_VSEL0_ENABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_12_9V: 
        {
            data_buf |= USBCSINK3_VSEL2_ENABLE | USBCSINK3_VSEL1_ENABLE | USBCSINK3_VSEL0_DISABLE;
            break;
        }
        case USBCSINK3_VTG_SEL_17_2V: 
        {
            data_buf |= USBCSINK3_VSEL2_ENABLE | USBCSINK3_VSEL1_ENABLE | USBCSINK3_VSEL0_ENABLE;
            break;
        }
        default: 
        {
            data_buf |= USBCSINK3_VSEL2_DISABLE | USBCSINK3_VSEL1_DISABLE | USBCSINK3_VSEL0_DISABLE;
            err_flag = USBCSINK3_ERROR;
            break;
        }
    }
    err_flag |= usbcsink3_i2c_write( ctx, USBCSINK3_REG_OUTPUT_PORT, data_buf );
    return err_flag;
}

err_t usbcsink3_set_power ( usbcsink3_t *ctx, usbcsink3_pwr_sel_t power )
{
    err_t err_flag = USBCSINK3_OK;
    switch ( power )
    {
        case USBCSINK3_PWR_SEL_12W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_6_8_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_15W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_16_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_18W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_27_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_20W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_36_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_27W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_45_3_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_36W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_56_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_45W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_64_9_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_60W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_75_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_90W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_82_KOHM );
            break;
        }
        case USBCSINK3_PWR_SEL_100W: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_91_KOHM );
            break;
        }
        default: 
        {
            err_flag |= usbcsink3_set_resistence( ctx, USBCSINK3_RES_6_8_KOHM );
            err_flag = USBCSINK3_ERROR;
            break;
        }
    }
    return err_flag;
}

// ------------------------------------------------------------------------ END

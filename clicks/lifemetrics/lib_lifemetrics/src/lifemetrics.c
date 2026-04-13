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
 * @file lifemetrics.c
 * @brief Life Metrics Click Driver.
 */

#include "lifemetrics.h"

/**
 * @brief Dummy and accel I2C subcommand setting data.
 * @details Definition of dummy and accel I2C subcommand setting data.
 */
#define DUMMY                               0x00
#define ACCEL_I2C_AUTO_INCREMENT_REG_BIT    0x80

void lifemetrics_cfg_setup ( lifemetrics_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->it2 = HAL_PIN_NC;
    cfg->gpo = HAL_PIN_NC;
    cfg->it1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIFEMETRICS_DEVICE_ADDRESS_AFE;
}

err_t lifemetrics_init ( lifemetrics_t *ctx, lifemetrics_cfg_t *cfg ) 
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

    digital_out_init( &ctx->gpo, cfg->gpo );

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t lifemetrics_default_cfg ( lifemetrics_t *ctx ) 
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t data_buf[ 29 ] = { 0 };

    /**< AFE config. */
    if ( LIFEMETRICS_ERROR == lifemetrics_afe_check_com ( ctx ) )
    {
        return LIFEMETRICS_ERROR;
    }
    error_flag |= lifemetrics_afe_reset ( ctx );

    data_buf[ 0 ] = LIFEMETRICS_AFE_POWER_PWR_ON;
    data_buf[ 1 ] = LIFEMETRICS_AFE_POWER_PWR_ISO;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_PWR_ON, data_buf, 2 );
    data_buf[ 0 ] = LIFEMETRICS_AFE_POWER_CLK_CFG;
    data_buf[ 1 ] = LIFEMETRICS_AFE_POWER_REF_CFG1;
    data_buf[ 2 ] = LIFEMETRICS_AFE_POWER_REF_CFG2;
    data_buf[ 3 ] = LIFEMETRICS_AFE_POWER_REF_CFG3;
    data_buf[ 4 ] = LIFEMETRICS_AFE_POWER_STANDBY_ON1;
    data_buf[ 5 ] = LIFEMETRICS_AFE_POWER_STANDBY_ON2;
    data_buf[ 6 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN1;
    data_buf[ 7 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN2;
    data_buf[ 8 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN3;
    data_buf[ 9 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN4;
    data_buf[ 10 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN5;
    data_buf[ 11 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN6;
    data_buf[ 12 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN7;
    data_buf[ 13 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN8;
    data_buf[ 14 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN9;
    data_buf[ 15 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN10;
    data_buf[ 16 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN11;
    data_buf[ 17 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN12;
    data_buf[ 18 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN13;
    data_buf[ 19 ] = LIFEMETRICS_AFE_POWER_STANDBY_EN14;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_CLK_CFG, data_buf, 20 );

    error_flag |= lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_I2C_MODE, LIFEMETRICS_AFE_CONTROL_I2C_MODE );
    data_buf[ 0 ] = LIFEMETRICS_AFE_CONTROL_INT_CFG;
    data_buf[ 1 ] = LIFEMETRICS_AFE_CONTROL_IF_CFG;
    data_buf[ 2 ] = LIFEMETRICS_AFE_CONTROL_GPIO_CFG1;
    data_buf[ 3 ] = LIFEMETRICS_AFE_CONTROL_GPIO_CFG2;
    data_buf[ 4 ] = LIFEMETRICS_AFE_CONTROL_IO_CFG;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_INT_CFG, data_buf, 5 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_LED_VCSEL_PASSWORD;
    data_buf[ 1 ] = LIFEMETRICS_AFE_LED_VCSEL_CFG;
    data_buf[ 2 ] = LIFEMETRICS_AFE_LED_VCSEL_MODE;
    data_buf[ 3 ] = LIFEMETRICS_AFE_LED_LED_CFG;
    data_buf[ 4 ] = LIFEMETRICS_AFE_LED_LED_DRV1;
    data_buf[ 5 ] = LIFEMETRICS_AFE_LED_LED_DRV2;
    data_buf[ 6 ] = LIFEMETRICS_AFE_LED_LED1_ICTRL;
    data_buf[ 7 ] = LIFEMETRICS_AFE_LED_LED2_ICTRL;
    data_buf[ 8 ] = LIFEMETRICS_AFE_LED_LED3_ICTRL;
    data_buf[ 9 ] = LIFEMETRICS_AFE_LED_LED4_ICTRL;
    data_buf[ 10 ] = LIFEMETRICS_AFE_LED_LED5_ICTRL;
    data_buf[ 11 ] = LIFEMETRICS_AFE_LED_LED6_ICTRL;
    data_buf[ 12 ] = LIFEMETRICS_AFE_LED_LED7_ICTRL;
    data_buf[ 13 ] = LIFEMETRICS_AFE_LED_LED8_ICTRL;
    data_buf[ 14 ] = LIFEMETRICS_AFE_LED_LED_IRNG1;
    data_buf[ 15 ] = LIFEMETRICS_AFE_LED_LED_IRNG2;
    data_buf[ 16 ] = LIFEMETRICS_AFE_LED_LED_SUB1;
    data_buf[ 17 ] = LIFEMETRICS_AFE_LED_LED_SUB2;
    data_buf[ 18 ] = LIFEMETRICS_AFE_LED_LED_SUB3;
    data_buf[ 19 ] = LIFEMETRICS_AFE_LED_LED_SUB4;
    data_buf[ 20 ] = LIFEMETRICS_AFE_LED_LED_SUB5;
    data_buf[ 21 ] = LIFEMETRICS_AFE_LED_LED_SUB6;
    data_buf[ 22 ] = LIFEMETRICS_AFE_LED_LED_SUB7;
    data_buf[ 23 ] = LIFEMETRICS_AFE_LED_LED_SUB8;
    data_buf[ 24 ] = LIFEMETRICS_AFE_LED_LOWVDS_WAIT;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_VCSEL_PASSWORD, data_buf, 25 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_PD_PDSEL_CFG;
    data_buf[ 1 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL1;
    data_buf[ 2 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL2;
    data_buf[ 3 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL3;
    data_buf[ 4 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL4;
    data_buf[ 5 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL5;
    data_buf[ 6 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL6;
    data_buf[ 7 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL7;
    data_buf[ 8 ] = LIFEMETRICS_AFE_PD_PPG1_PDSEL8;
    data_buf[ 9 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL1;
    data_buf[ 10 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL2;
    data_buf[ 11 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL3;
    data_buf[ 12 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL4;
    data_buf[ 13 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL5;
    data_buf[ 14 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL6;
    data_buf[ 15 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL7;
    data_buf[ 16 ] = LIFEMETRICS_AFE_PD_PPG2_PDSEL8;
    data_buf[ 17 ] = LIFEMETRICS_AFE_PD_PPG2_AFESEL1;
    data_buf[ 18 ] = LIFEMETRICS_AFE_PD_PPG2_AFESEL2;
    data_buf[ 19 ] = LIFEMETRICS_AFE_PD_PPG2_AFESEL3;
    data_buf[ 20 ] = LIFEMETRICS_AFE_PD_PPG2_AFESEL4;
    data_buf[ 21 ] = LIFEMETRICS_AFE_PD_PPG2_AFEEN;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_PDSEL_CFG, data_buf, 22 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB1;
    data_buf[ 1 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB2;
    data_buf[ 2 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB3;
    data_buf[ 3 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB4;
    data_buf[ 4 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB5;
    data_buf[ 5 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB6;
    data_buf[ 6 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB7;
    data_buf[ 7 ] = LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB8;
    data_buf[ 8 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB1;
    data_buf[ 9 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB2;
    data_buf[ 10 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB3;
    data_buf[ 11 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB4;
    data_buf[ 12 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB5;
    data_buf[ 13 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB6;
    data_buf[ 14 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB7;
    data_buf[ 15 ] = LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB8;
    data_buf[ 16 ] = LIFEMETRICS_AFE_IOS_IOS_LEDOFF;
    data_buf[ 17 ] = LIFEMETRICS_AFE_IOS_IOS_CFG;
    data_buf[ 18 ] = LIFEMETRICS_AFE_IOS_AOC_SAR_THRES;
    data_buf[ 19 ] = LIFEMETRICS_AFE_IOS_AOC_SAR_RANGE;
    data_buf[ 20 ] = LIFEMETRICS_AFE_IOS_AOC_SAR_PPG1;
    data_buf[ 21 ] = LIFEMETRICS_AFE_IOS_AOC_SAR_PPG2;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_IOS_PPG1_SUB1, data_buf, 22 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_PPG_PPGMOD_CFG1;
    data_buf[ 1 ] = LIFEMETRICS_AFE_PPG_PPGMOD_CFG2;
    data_buf[ 2 ] = LIFEMETRICS_AFE_PPG_PPGMOD_CFG3;
    data_buf[ 3 ] = LIFEMETRICS_AFE_PPG_PPGMOD1_CFG1;
    data_buf[ 4 ] = LIFEMETRICS_AFE_PPG_PPGMOD1_CFG2;
    data_buf[ 5 ] = LIFEMETRICS_AFE_PPG_PPGMOD1_CFG3;
    data_buf[ 6 ] = LIFEMETRICS_AFE_PPG_PPGMOD2_CFG1;
    data_buf[ 7 ] = LIFEMETRICS_AFE_PPG_PPGMOD2_CFG2;
    data_buf[ 8 ] = LIFEMETRICS_AFE_PPG_PPGMOD2_CFG3;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_PPGMOD_CFG1, data_buf, 9 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_ECG_BIOZ_CFG;
    data_buf[ 1 ] = LIFEMETRICS_AFE_ECG_BIOZ_EXCIT;
    data_buf[ 2 ] = LIFEMETRICS_AFE_ECG_BIOZ_MIXER;
    data_buf[ 3 ] = LIFEMETRICS_AFE_ECG_BIOZ_SELECT;
    data_buf[ 4 ] = LIFEMETRICS_AFE_ECG_BIOZ_GAIN;
    data_buf[ 5 ] = LIFEMETRICS_AFE_ECG_ECGMOD_CFG1;
    data_buf[ 6 ] = LIFEMETRICS_AFE_ECG_ECGMOD_CFG2;
    data_buf[ 7 ] = LIFEMETRICS_AFE_ECG_ECGIMUX_CFG1;
    data_buf[ 8 ] = LIFEMETRICS_AFE_ECG_ECGIMUX_CFG2;
    data_buf[ 9 ] = LIFEMETRICS_AFE_ECG_ECGIMUX_CFG3;
    data_buf[ 10 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG1;
    data_buf[ 11 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG2;
    data_buf[ 12 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG3;
    data_buf[ 13 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG4;
    data_buf[ 14 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG5;
    data_buf[ 15 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG6;
    data_buf[ 16 ] = LIFEMETRICS_AFE_ECG_ECGAMP_CFG7;
    data_buf[ 17 ] = LIFEMETRICS_AFE_ECG_ECG_BIOZ;
    data_buf[ 18 ] = LIFEMETRICS_AFE_ECG_LEADOFF_CFG;
    data_buf[ 19 ] = LIFEMETRICS_AFE_ECG_LEADOFF_THRESL;
    data_buf[ 20 ] = LIFEMETRICS_AFE_ECG_LEADOFF_THRESH;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_BIOZ_CFG, data_buf, 21 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_SINC_PPG_SINC_CFGA;
    data_buf[ 1 ] = LIFEMETRICS_AFE_SINC_PPG_SINC_CFGB;
    data_buf[ 2 ] = LIFEMETRICS_AFE_SINC_PPG_SINC_CFGC;
    data_buf[ 3 ] = LIFEMETRICS_AFE_SINC_PPG_SINC_CFGD;
    data_buf[ 4 ] = LIFEMETRICS_AFE_SINC_ECG1_SINC_CFGA;
    data_buf[ 5 ] = LIFEMETRICS_AFE_SINC_ECG1_SINC_CFGB;
    data_buf[ 6 ] = LIFEMETRICS_AFE_SINC_ECG1_SINC_CFGC;
    data_buf[ 7 ] = LIFEMETRICS_AFE_SINC_ECG2_SINC_CFGA;
    data_buf[ 8 ] = LIFEMETRICS_AFE_SINC_ECG2_SINC_CFGB;
    data_buf[ 9 ] = LIFEMETRICS_AFE_SINC_ECG2_SINC_CFGC;
    data_buf[ 10 ] = LIFEMETRICS_AFE_SINC_ECG_SINC_CFG;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_PPG_SINC_CFGA, data_buf, 11 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_SEQ_IRQ_ENABLE;
    data_buf[ 1 ] = LIFEMETRICS_AFE_SEQ_PPG_SUB_WAIT;
    data_buf[ 2 ] = LIFEMETRICS_AFE_SEQ_PPG_SAR_WAIT;
    data_buf[ 3 ] = LIFEMETRICS_AFE_SEQ_PPG_LED_INIT;
    data_buf[ 4 ] = LIFEMETRICS_AFE_SEQ_PPG_FREQL;
    data_buf[ 5 ] = LIFEMETRICS_AFE_SEQ_PPG_FREQH;
    data_buf[ 6 ] = LIFEMETRICS_AFE_SEQ_PPG1_SUB_EN;
    data_buf[ 7 ] = LIFEMETRICS_AFE_SEQ_PPG2_SUB_EN;
    data_buf[ 8 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_1;
    data_buf[ 9 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_2;
    data_buf[ 10 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_3;
    data_buf[ 11 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_4;
    data_buf[ 12 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_5;
    data_buf[ 13 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_6;
    data_buf[ 14 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_7;
    data_buf[ 15 ] = LIFEMETRICS_AFE_SEQ_PPG_MODE_8;
    data_buf[ 16 ] = LIFEMETRICS_AFE_SEQ_PPG_CFG;
    data_buf[ 17 ] = LIFEMETRICS_AFE_SEQ_ECG_FREQL;
    data_buf[ 18 ] = LIFEMETRICS_AFE_SEQ_ECG_FREQH;
    data_buf[ 19 ] = LIFEMETRICS_AFE_SEQ_ECG1_FREQDIVL;
    data_buf[ 20 ] = LIFEMETRICS_AFE_SEQ_ECG1_FREQDIVH;
    data_buf[ 21 ] = LIFEMETRICS_AFE_SEQ_ECG2_FREQDIVL;
    data_buf[ 22 ] = LIFEMETRICS_AFE_SEQ_ECG2_FREQDIVH;
    data_buf[ 23 ] = LIFEMETRICS_AFE_SEQ_ECG_SUBS;
    data_buf[ 24 ] = LIFEMETRICS_AFE_SEQ_LEADOFF_INITL;
    data_buf[ 25 ] = LIFEMETRICS_AFE_SEQ_LEADOFF_INITH;
    data_buf[ 26 ] = LIFEMETRICS_AFE_SEQ_ECG_INITL;
    data_buf[ 27 ] = LIFEMETRICS_AFE_SEQ_ECG_INITH;
    data_buf[ 28 ] = LIFEMETRICS_AFE_SEQ_SAMPLE_NUM;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_IRQ_ENABLE, data_buf, 29 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_POST_PP_CFG;
    data_buf[ 1 ] = LIFEMETRICS_AFE_POST_PPG1_PP1;
    data_buf[ 2 ] = LIFEMETRICS_AFE_POST_PPG1_PP2;
    data_buf[ 3 ] = LIFEMETRICS_AFE_POST_PPG2_PP1;
    data_buf[ 4 ] = LIFEMETRICS_AFE_POST_PPG2_PP2;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_PP_CFG, data_buf, 5 );

    data_buf[ 0 ] = LIFEMETRICS_AFE_FIFO_FIFO_THRESHOLD;
    data_buf[ 1 ] = LIFEMETRICS_AFE_FIFO_FIFO_CTRL;
    error_flag |= lifemetrics_afe_write_regs ( ctx, LIFEMETRICS_AFE_REG_FIFO_THRESHOLD, data_buf, 2 );

    error_flag |= lifemetrics_afe_read_reg( ctx, LIFEMETRICS_AFE_REG_FIFO_THRESHOLD, &ctx->fifo_thld );

    /**< Accel config. */
    if ( LIFEMETRICS_ERROR == lifemetrics_accel_check_com ( ctx ) )
    {
        return LIFEMETRICS_ERROR;
    }
    error_flag |= lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL1, 
                                                LIFEMETRICS_ACCEL_CTRL1_ODR_POWER_DOWN | 
                                                LIFEMETRICS_ACCEL_CTRL1_ZEN | 
                                                LIFEMETRICS_ACCEL_CTRL1_YEN | 
                                                LIFEMETRICS_ACCEL_CTRL1_XEN );

    error_flag |= lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL3, 
                                                LIFEMETRICS_ACCEL_CTRL3_I1_ZYXDA );

    error_flag |= lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL4, 
                                                LIFEMETRICS_ACCEL_CTRL4_BDU | 
                                                LIFEMETRICS_ACCEL_CTRL4_HIGH_RES | 
                                                LIFEMETRICS_ACCEL_CTRL4_FS_2G | 
                                                LIFEMETRICS_ACCEL_CTRL4_ST_NORMAL | 
                                                LIFEMETRICS_ACCEL_CTRL4_SIM_4_WIRE );
    error_flag |= lifemetrics_accel_en_temp_sen ( ctx );

    error_flag |= lifemetrics_accel_set_odr( ctx, LIFEMETRICS_ACCEL_ODR_10_HZ );

    error_flag |= lifemetrics_accel_set_fsr( ctx, LIFEMETRICS_ACCEL_FS_2G );

    /**< Temperature config. */
    error_flag |= lifemetrics_temp_write_config ( ctx, LIFEMETRICS_TEMP_CONFIG_OSR_32MS | 
                                                       LIFEMETRICS_TEMP_CONFIG_CONV_RATE_1S );
    
    return error_flag;
}

void lifemetrics_set_device_addr ( lifemetrics_t *ctx, uint8_t address )
{
    if ( ctx->slave_address != address )
    {
        ctx->slave_address = address;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
}

uint8_t lifemetrics_get_it1_pin ( lifemetrics_t *ctx )
{
    return !!digital_in_read ( &ctx->it1 );
}

uint8_t lifemetrics_get_it2_pin ( lifemetrics_t *ctx )
{
    return !!digital_in_read ( &ctx->it2 );
}

err_t lifemetrics_afe_write_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t data_in )
{
    return lifemetrics_afe_write_regs( ctx, reg, &data_in, 1 );
}

err_t lifemetrics_afe_write_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    lifemetrics_set_device_addr ( ctx, LIFEMETRICS_DEVICE_ADDRESS_AFE );
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t lifemetrics_afe_read_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return lifemetrics_afe_read_regs( ctx, reg, data_out, 1 );
}

err_t lifemetrics_afe_read_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    lifemetrics_set_device_addr ( ctx, LIFEMETRICS_DEVICE_ADDRESS_AFE );
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t lifemetrics_afe_check_com ( lifemetrics_t *ctx )
{
    uint8_t num_tries = 10;
    uint8_t silicon_id = 0;
    while ( num_tries-- )
    {
        if ( LIFEMETRICS_OK == lifemetrics_afe_read_reg ( ctx, LIFEMETRICS_AFE_REG_SILICON_ID, &silicon_id ) )
        {
            if ( LIFEMETRICS_AFE_MISC_SILICON_ID == silicon_id )
            {
                return LIFEMETRICS_OK;
            }
        }
        Delay_10ms ( );
    }
    return LIFEMETRICS_ERROR;
}

err_t lifemetrics_afe_reset ( lifemetrics_t *ctx )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t chip_ctrl = LIFEMETRICS_AFE_MISC_CHIP_CTRL_CHIP_RESET;

    error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_CHIP_CTRL, chip_ctrl );
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_afe_read_reg ( ctx, LIFEMETRICS_AFE_REG_CHIP_CTRL, &chip_ctrl );
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_PWR_ISO, LIFEMETRICS_AFE_POWER_PWR_ISO );
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_PWR_ON, LIFEMETRICS_AFE_POWER_PWR_ON );
    }
    return error_flag;
}

err_t lifemetrics_afe_clear_fifo ( lifemetrics_t *ctx )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t fifo_ctrl = 0;

    error_flag = lifemetrics_afe_read_reg ( ctx, LIFEMETRICS_AFE_REG_FIFO_CTRL, &fifo_ctrl );
    if ( LIFEMETRICS_OK == error_flag )
    {
        fifo_ctrl |= LIFEMETRICS_AFE_FIFO_FIFO_CTRL_RESET;
        error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_FIFO_CTRL, fifo_ctrl );
    }
    return error_flag;
}

err_t lifemetrics_afe_start_meas ( lifemetrics_t *ctx )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t irq_status[ 10 ] = { 0 };

    /* Clear FIFO level register and possible active interrupt pin */
    error_flag = lifemetrics_afe_clear_fifo ( ctx );
    if ( LIFEMETRICS_OK == error_flag )
    {
        /* Read old interrupt status register to reset interrupt pin */
        error_flag = lifemetrics_afe_read_regs ( ctx, LIFEMETRICS_AFE_REG_STATUS_SEQ, irq_status, 10 );
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        /* Read the main status register in a separate call again to give chip enough time to reset internal status registers */
        error_flag = lifemetrics_afe_read_regs ( ctx, LIFEMETRICS_AFE_REG_STATUS, irq_status, 1 );
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( 0 == irq_status[ 0 ] )
        {
            error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_SEQ_START, LIFEMETRICS_AFE_MISC_SEQ_START_START );
        }
        else
        {
            error_flag = LIFEMETRICS_ERROR;
        }
    }
    return error_flag;
}

err_t lifemetrics_afe_stop_meas ( lifemetrics_t *ctx )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t retry = 255;
    uint8_t reg_data = 0;

    error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_SEQ_START, LIFEMETRICS_AFE_MISC_SEQ_START_STOP );
    
    while ( ( LIFEMETRICS_OK == error_flag ) && ( retry-- ) )
    {
        error_flag = lifemetrics_afe_read_reg ( ctx, LIFEMETRICS_AFE_REG_SEQ_START, &reg_data );
        if ( ( LIFEMETRICS_OK == error_flag ) && 
             ( LIFEMETRICS_AFE_MISC_SEQ_START_STOP == ( reg_data & LIFEMETRICS_AFE_MISC_SEQ_START_START ) ) )
        {
            break;
        }
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        /* It seems that there is a bug in the chip where the measurement is not stopped correctly.
           Stopping the measurement again helps to fix it. */
        error_flag = lifemetrics_afe_write_reg ( ctx, LIFEMETRICS_AFE_REG_SEQ_START, LIFEMETRICS_AFE_MISC_SEQ_START_STOP );
    }
    return error_flag;
}

err_t lifemetrics_afe_read_fifo_lvl ( lifemetrics_t *ctx, uint16_t *fifo_lvl )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t reg_data[ 2 ] = { 0 };

    error_flag = lifemetrics_afe_read_regs ( ctx, LIFEMETRICS_AFE_REG_FIFO_LEVEL0, reg_data, 2 );
    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( ( LIFEMETRICS_AFE_MISC_FIFO_LEVEL1_OVERFLOW != 
               ( LIFEMETRICS_AFE_MISC_FIFO_LEVEL1_OVERFLOW & reg_data[ 1 ] ) ) && 
             ( NULL != fifo_lvl ) )
        {
            *fifo_lvl = ( ( uint16_t ) reg_data[ 1 ] << 8 ) | reg_data[ 0 ];
        }
        else
        {
            error_flag = LIFEMETRICS_ERROR;
        }
    }
    return error_flag;
}

err_t lifemetrics_afe_read_fifo ( lifemetrics_t *ctx, uint8_t *fifo_data, uint16_t *fifo_data_size )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint16_t fifo_lvl = 0;
    uint8_t irq_status = 0;

    if ( ( NULL == fifo_data ) || ( NULL == fifo_data_size ) )
    {
        error_flag = LIFEMETRICS_ERROR;
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( !lifemetrics_get_it1_pin ( ctx ) )
        {
            error_flag = LIFEMETRICS_ERROR;
        }
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_afe_read_reg ( ctx, LIFEMETRICS_AFE_REG_STATUS, &irq_status );
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( irq_status & LIFEMETRICS_AFE_MISC_STATUS_IRQ_FIFO_OVERFLOW )
        {
            error_flag = LIFEMETRICS_ERROR;
        }
        else if ( irq_status & LIFEMETRICS_AFE_MISC_STATUS_IRQ_FIFO_THRESHOLD )
        {
            error_flag = lifemetrics_afe_read_fifo_lvl ( ctx, &fifo_lvl );
        }
        else
        {
            error_flag = LIFEMETRICS_ERROR;
        }
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        /* Calculate read length as multiple of FIFO threshold */
        if ( 0 == ctx->fifo_thld )
        {
            error_flag = LIFEMETRICS_ERROR;
        }
        else
        {
            fifo_lvl = ( fifo_lvl / ctx->fifo_thld ) * ctx->fifo_thld;

            /* Calculate the real data size */
            *fifo_data_size = fifo_lvl * LIFEMETRICS_AFE_FIFO_SAMPLE_SIZE;
            if ( ( *fifo_data_size > LIFEMETRICS_AFE_FIFO_BUFFER_SIZE ) || ( 0 == *fifo_data_size ) )
            {
                *fifo_data_size = 0;
                error_flag = LIFEMETRICS_ERROR;
            }
            else
            {
                error_flag = lifemetrics_afe_read_regs ( ctx, LIFEMETRICS_AFE_REG_FIFOL, fifo_data, *fifo_data_size );
            }
        }
    }
    return error_flag;
}

err_t lifemetrics_accel_write_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t data_in )
{
    return lifemetrics_accel_write_regs( ctx, reg, &data_in, 1 );
}

err_t lifemetrics_accel_write_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    if ( len > 1 )
    {
        data_buf[ 0 ] = reg | ACCEL_I2C_AUTO_INCREMENT_REG_BIT;
    }
    else
    {
        data_buf[ 0 ] = reg;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    lifemetrics_set_device_addr ( ctx, LIFEMETRICS_DEVICE_ADDRESS_ACCEL );
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t lifemetrics_accel_read_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return lifemetrics_accel_read_regs( ctx, reg, data_out, 1 );
}

err_t lifemetrics_accel_read_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t subcmd = 0;
    if ( len > 1 )
    {
        subcmd = reg | ACCEL_I2C_AUTO_INCREMENT_REG_BIT;
    }
    else
    {
        subcmd = reg;
    }
    lifemetrics_set_device_addr ( ctx, LIFEMETRICS_DEVICE_ADDRESS_ACCEL );
    return i2c_master_write_then_read( &ctx->i2c, &subcmd, 1, data_out, len );
}

err_t lifemetrics_accel_check_com ( lifemetrics_t *ctx )
{
    uint8_t num_tries = 10;
    uint8_t who_am_i = 0;
    while ( num_tries-- )
    {
        if ( LIFEMETRICS_OK == lifemetrics_accel_read_reg ( ctx, LIFEMETRICS_ACCEL_REG_WHO_AM_I, &who_am_i ) )
        {
            if ( LIFEMETRICS_ACCEL_WHO_AM_I == who_am_i )
            {
                return LIFEMETRICS_OK;
            }
        }
        Delay_10ms ( );
    }
    return LIFEMETRICS_ERROR;
}

err_t lifemetrics_accel_set_odr ( lifemetrics_t *ctx, uint8_t odr ) 
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t ctrl1 = DUMMY;
    if ( odr > LIFEMETRICS_ACCEL_ODR_5376_HZ )
    {
        error_flag = LIFEMETRICS_ERROR;
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_read_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL1, &ctrl1 );
        ctrl1 &= ~LIFEMETRICS_ACCEL_CTRL1_ODR_MASK;
        ctrl1 |= ( ( odr << 4 ) & LIFEMETRICS_ACCEL_CTRL1_ODR_MASK );
        error_flag |= lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL1, ctrl1 );
    }
    return error_flag;
}

err_t lifemetrics_accel_set_fsr ( lifemetrics_t *ctx, uint8_t fsr ) 
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t ctrl4 = DUMMY;
    if ( fsr > LIFEMETRICS_ACCEL_FS_16G )
    {
        error_flag = LIFEMETRICS_ERROR;
    }
    
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_read_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL4, &ctrl4 );
        ctrl4 &= ~LIFEMETRICS_ACCEL_CTRL4_FS_MASK;
        ctrl4 |= ( fsr & LIFEMETRICS_ACCEL_CTRL4_FS_MASK );
        error_flag |= lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_CTRL4, ctrl4 );
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        ctx->accel_sens = LIFEMETRICS_ACCEL_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
    }
    return error_flag;
}

err_t lifemetrics_accel_en_temp_sen ( lifemetrics_t *ctx ) 
{
    return lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_TEMP_CFG, LIFEMETRICS_ACCEL_TEMP_CFG_TEMP_ENABLE );
}

err_t lifemetrics_accel_dis_temp_sen ( lifemetrics_t *ctx ) 
{
    return lifemetrics_accel_write_reg ( ctx, LIFEMETRICS_ACCEL_REG_TEMP_CFG, LIFEMETRICS_ACCEL_TEMP_CFG_TEMP_DISABLE );
}

err_t lifemetrics_accel_drdy ( lifemetrics_t *ctx )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t status = 0;
    error_flag = lifemetrics_accel_read_reg ( ctx, LIFEMETRICS_ACCEL_REG_STATUS, &status );
    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( LIFEMETRICS_ACCEL_STATUS_ZYXDA != ( status & LIFEMETRICS_ACCEL_STATUS_ZYXDA ) )
        {
            error_flag = LIFEMETRICS_ACCEL_NO_DRDY;
        }
    }
    return error_flag;
}

err_t lifemetrics_accel_get_accel ( lifemetrics_t *ctx, lifemetrics_accel_axes_t *accel )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = DUMMY;
    
    if ( NULL == accel )
    {
        error_flag = LIFEMETRICS_ERROR;
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( !lifemetrics_get_it2_pin ( ctx ) )
        {
            error_flag = LIFEMETRICS_ERROR;
        }
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_drdy ( ctx );
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_read_regs ( ctx, LIFEMETRICS_ACCEL_REG_OUT_X_L, data_buf, 6 );
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        raw_data >>= 4;
        accel->x = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 3 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 2 ];
        raw_data >>= 4;
        accel->y = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 5 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 4 ];
        raw_data >>= 4;
        accel->z = ( float ) raw_data * ctx->accel_sens;
    }
    return error_flag;
}

err_t lifemetrics_accel_temp_drdy ( lifemetrics_t *ctx )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t status = 0;
    error_flag = lifemetrics_accel_read_reg ( ctx, LIFEMETRICS_ACCEL_REG_STATUS_AUX, &status );
    if ( LIFEMETRICS_OK == error_flag )
    {
        if ( LIFEMETRICS_ACCEL_STATUS_AUX_TDA != ( status & LIFEMETRICS_ACCEL_STATUS_AUX_TDA ) )
        {
            error_flag = LIFEMETRICS_ACCEL_NO_DRDY;
        }
    }
    return error_flag;
}

err_t lifemetrics_accel_get_temp ( lifemetrics_t *ctx, float *temp )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = LIFEMETRICS_ERROR;
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_temp_drdy ( ctx );
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_read_regs ( ctx, LIFEMETRICS_ACCEL_REG_OUT_TEMP_L, data_buf, 2 );
    }

    if ( LIFEMETRICS_OK == error_flag )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        raw_data >>= 6;
        *temp = ( float ) raw_data * LIFEMETRICS_ACCEL_TEMP_SENS_C_PER_LSB + LIFEMETRICS_ACCEL_TEMP_OFFSET;
    }
    return error_flag;
}

err_t lifemetrics_accel_get_data ( lifemetrics_t *ctx, lifemetrics_accel_data_t *data_out )
{
    err_t error_flag = LIFEMETRICS_OK;
    if ( NULL == data_out )
    {
        error_flag = LIFEMETRICS_ERROR;
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_get_accel ( ctx, &data_out->accel );
    }
    if ( LIFEMETRICS_OK == error_flag )
    {
        error_flag = lifemetrics_accel_get_temp ( ctx, &data_out->temperature );
    }
    return error_flag;
}

err_t lifemetrics_temp_write_reg ( lifemetrics_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    lifemetrics_set_device_addr ( ctx, LIFEMETRICS_DEVICE_ADDRESS_TEMP );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t lifemetrics_temp_read_reg ( lifemetrics_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = LIFEMETRICS_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    lifemetrics_set_device_addr ( ctx, LIFEMETRICS_DEVICE_ADDRESS_TEMP );
    error_flag = i2c_master_write_then_read ( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( ( LIFEMETRICS_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t lifemetrics_temp_write_config ( lifemetrics_t *ctx, uint16_t config )
{
    return lifemetrics_temp_write_reg ( ctx, LIFEMETRICS_TEMP_REG_CONFIG, config );
}

err_t lifemetrics_temp_read_config ( lifemetrics_t *ctx, uint16_t *config )
{
    return lifemetrics_temp_read_reg ( ctx, LIFEMETRICS_TEMP_REG_CONFIG, config );
}

err_t lifemetrics_temp_read_temp ( lifemetrics_t *ctx, float *temp )
{
    uint16_t raw_temp = 0;
    err_t error_flag = lifemetrics_temp_read_reg ( ctx, LIFEMETRICS_TEMP_REG_TVAL_L, &raw_temp );
    if ( ( LIFEMETRICS_OK == error_flag ) && ( NULL != temp ) )
    {
        *temp = ( ( int16_t ) raw_temp ) * LIFEMETRICS_TEMP_RESOLUTION;
    }
    return error_flag;
}

err_t lifemetrics_temp_read_id ( lifemetrics_t *ctx, uint16_t *chip_id )
{
    err_t error_flag = LIFEMETRICS_OK;
    for ( uint8_t cnt = 0; cnt < 3; cnt++ )
    {
        if ( LIFEMETRICS_OK == error_flag )
        {
            error_flag = lifemetrics_temp_read_reg ( ctx, LIFEMETRICS_TEMP_REG_CHIP_ID_1 + cnt, &chip_id[ cnt ] );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END

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
 * @file hbridgedriver2.c
 * @brief H-Bridge Driver 2 Click Driver.
 */

#include "hbridgedriver2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                            0x00
#define CMD_REG_BIT_MASK                 0x3F

/**
 * @brief Operation codes data.
 * @details Definition of operation codes data.
 */
#define ACCESS_MODE_WRITE                0x00
#define ACCESS_MODE_READ                 0x40
#define ACCESS_MODEP_READ_ADN_CLEAR      0x80
#define ACCESS_MODE_READ_DEVICE_ID       0xC0

/**
 * @brief Tsact delay.
 * @details Time delay from Standby ( CS rising edge MODE = 1 and EN = 1 ) 
 * into Active mode ( NRDY = 0 ).
 */
static void dev_tsact_delay ( void );

/**
 * @brief Tscsn hi EN hi delay.
 * @details Minimum time between CS high and EN high edge.
 */
static void dev_tcsn_hi_en_hi_delay ( void );

/**
 * @brief Repeat set-up delay.
 * @details Minimum time to repeat set-up delay.
 */
static void dev_repeat_delay ( void );

void hbridgedriver2_cfg_setup ( hbridgedriver2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->dev_pwm_freq = HBRIDGEDRIVER2_DEF_FREQ;
}

err_t hbridgedriver2_init ( hbridgedriver2_t *ctx, hbridgedriver2_cfg_t *cfg ) 
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
    
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) 
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->en, cfg->en );
  
    return SPI_MASTER_SUCCESS;
}

err_t hbridgedriver2_default_cfg ( hbridgedriver2_t *ctx ) 
{   
    err_t error_flag = hbridgedriver2_disable( ctx );
    
    error_flag |= hbridgedriver2_set_active_mode( ctx );
    
    return error_flag;
}

err_t hbridgedriver2_enable ( hbridgedriver2_t *ctx ) 
{
    err_t error_flag = HBRIDGEDRIVER2_OK;
    
    digital_out_high( &ctx->en );

    return error_flag;
}

err_t hbridgedriver2_disable ( hbridgedriver2_t *ctx ) 
{
    err_t error_flag = HBRIDGEDRIVER2_OK;
    
    digital_out_low( &ctx->en );

    return error_flag;
}

err_t hbridgedriver2_write_reg ( hbridgedriver2_t *ctx, uint8_t reg, uint8_t *global_fault, uint16_t data_in ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t rx_buf_msb = 0;
    uint8_t rx_buf_lsb = 0;
    err_t error_flag = HBRIDGEDRIVER2_OK;

    reg &= CMD_REG_BIT_MASK;
    reg |= ACCESS_MODE_WRITE;
    tx_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) data_in;

    while ( ( rx_buf_msb != tx_buf[ 0 ] ) || ( rx_buf_lsb != tx_buf[ 1 ] ) )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, reg );
        error_flag |= spi_master_read( &ctx->spi, global_fault, 1 );
        spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
        error_flag |= spi_master_read( &ctx->spi, &rx_buf_msb, 1 );
        spi_master_set_default_write_data( &ctx->spi, tx_buf[ 1 ] );
        error_flag |= spi_master_read( &ctx->spi, &rx_buf_lsb, 1 );
        spi_master_deselect_device( ctx->chip_select );  
    }

    return error_flag;
}

err_t hbridgedriver2_read_reg ( hbridgedriver2_t *ctx, uint8_t reg, uint8_t *global_fault, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ];
    
    reg &= CMD_REG_BIT_MASK;
    reg |= ACCESS_MODE_READ;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg );
    err_t error_flag = spi_master_read( &ctx->spi, global_fault, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];

    return error_flag;
}

err_t hbridgedriver2_read_clear_reg ( hbridgedriver2_t *ctx, uint8_t reg, uint8_t *global_fault, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ];
    
    reg &= CMD_REG_BIT_MASK;
    reg |= ACCESS_MODEP_READ_ADN_CLEAR;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg );
    err_t error_flag = spi_master_read( &ctx->spi, global_fault, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];

    return error_flag;
}

err_t hbridgedriver2_read_id ( hbridgedriver2_t *ctx, uint8_t reg, uint8_t *global_fault, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ];
    
    reg &= CMD_REG_BIT_MASK;
    reg |= ACCESS_MODE_READ_DEVICE_ID;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg );
    err_t error_flag = spi_master_read( &ctx->spi, global_fault, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];

    return error_flag;
}

err_t hbridgedriver2_set_active_mode ( hbridgedriver2_t *ctx ) 
{
    err_t error_flag = HBRIDGEDRIVER2_OK;
    uint8_t device_status_bits;    
   
    digital_out_high( &ctx->en );
    dev_tcsn_hi_en_hi_delay( );
    
    spi_master_select_device( ctx->chip_select );
    
    hbridgedriver2_set_control( ctx, &device_status_bits, HBRIDGEDRIVER2_CTL_0_MODE );
    
    spi_master_deselect_device( ctx->chip_select );
    dev_tsact_delay( );
    
    while ( device_status_bits != HBRIDGEDRIVER2_GLB_RESB_NORMAL )
    {  
        hbridgedriver2_set_control( ctx, &device_status_bits, HBRIDGEDRIVER2_CTL_0_MODE );
        dev_repeat_delay( );
    }
    


    hbridgedriver2_set_config( ctx, &device_status_bits, HBRIDGEDRIVER2_CFG_NOCRLH_250_NS |
                                                         HBRIDGEDRIVER2_CFG_NOCRHL_250_NS |
                                                         HBRIDGEDRIVER2_CFG_OCTH_0_25_V   |
                                                         HBRIDGEDRIVER2_CFG_FULL_H_BRIDGE |
                                                         HBRIDGEDRIVER2_CFG_SLOW_SLEW_RATE );

    return error_flag;
}

err_t hbridgedriver2_get_status ( hbridgedriver2_t *ctx, uint16_t *status ) 
{
    uint8_t rx_buf_0;
    uint8_t rx_buf_1;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, HBRIDGEDRIVER2_CMD_REG_STAT_0 |
                                                  ACCESS_MODEP_READ_ADN_CLEAR );
    err_t error_flag = spi_master_read( &ctx->spi, &rx_buf_0, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf_0, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf_1, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *status = rx_buf_0;
    *status <<= 8;
    *status |= rx_buf_1;
    
    return error_flag;
}

err_t hbridgedriver2_get_control ( hbridgedriver2_t *ctx, uint16_t *control ) 
{
    uint8_t device_status_bits;
    uint8_t rx_buf_0;
    uint8_t rx_buf_1;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, HBRIDGEDRIVER2_CMD_REG_CTL_0 | 
                                                  ACCESS_MODE_READ );
    err_t error_flag = spi_master_read( &ctx->spi, &device_status_bits, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf_0, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf_1, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *control = rx_buf_0;
    *control <<= 8;
    *control |= rx_buf_1;
    
    return error_flag;
}

err_t hbridgedriver2_set_control ( hbridgedriver2_t *ctx, uint8_t *write_status, uint16_t control ) 
{   
    return hbridgedriver2_write_reg( ctx, HBRIDGEDRIVER2_CMD_REG_CTL_0, write_status, control );
}

err_t hbridgedriver2_get_config ( hbridgedriver2_t *ctx, uint16_t *config ) 
{
    uint8_t device_status_bits;
    uint8_t rx_buf_0;
    uint8_t rx_buf_1;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, HBRIDGEDRIVER2_CMD_REG_CFG | 
                                                  ACCESS_MODE_READ );
    err_t error_flag = spi_master_read( &ctx->spi, &device_status_bits, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf_0, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf_1, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *config = rx_buf_0;
    *config <<= 8;
    *config |= rx_buf_1;
    
    return error_flag;
}

err_t hbridgedriver2_set_config ( hbridgedriver2_t *ctx, uint8_t *write_status, uint16_t config ) 
{   
    return hbridgedriver2_write_reg( ctx, HBRIDGEDRIVER2_CMD_REG_CFG, write_status, config );
}

err_t hbridgedriver2_get_device_id ( hbridgedriver2_t *ctx, uint8_t *read_status, hbridgedriver2_dev_id_t *dev_id ) 
{      
    err_t error_flag = hbridgedriver2_read_id( ctx, HBRIDGEDRIVER2_ID_REG_ID_HDR, read_status, &dev_id->id_header );
    
    error_flag |= hbridgedriver2_read_id( ctx, HBRIDGEDRIVER2_ID_REG_VERSION, read_status, &dev_id->version );
    
    error_flag |= hbridgedriver2_read_id( ctx, HBRIDGEDRIVER2_ID_REG_P_CODE_1, read_status, &dev_id->product_code_1 );
    
    error_flag |= hbridgedriver2_read_id( ctx, HBRIDGEDRIVER2_ID_REG_P_CODE_2, read_status, &dev_id->product_code_2 );
    
    error_flag |= hbridgedriver2_read_id( ctx, HBRIDGEDRIVER2_ID_REG_SPI_F_ID, read_status, &dev_id->spi_frame_id );

    return error_flag;
}

err_t hbridgedriver2_control ( hbridgedriver2_t *ctx, uint8_t *write_status, hbridgedriver2_ctrl_t dev_ctrl ) 
{
    uint16_t rx_buf;
   
    rx_buf = dev_ctrl.hs_1;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.ls_1;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.hs_2;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.ls_2;
    rx_buf <<= 2;
    rx_buf |= dev_ctrl.fw_h;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.fw_a;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.ovr;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.uvr;
    rx_buf <<= 1;
    rx_buf |= dev_ctrl.mode;

    return hbridgedriver2_write_reg( ctx, HBRIDGEDRIVER2_CMD_REG_CTL_0, write_status, rx_buf );
}

err_t hbridgedriver2_run_backward ( hbridgedriver2_t *ctx, uint8_t *global_fault ) 
{
    hbridgedriver2_ctrl_t dev_ctrl;
    
    dev_ctrl.hs_1 = HBRIDGEDRIVER2_SET;
    dev_ctrl.ls_1 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.hs_2 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ls_2 = HBRIDGEDRIVER2_SET;
    dev_ctrl.fw_h = HBRIDGEDRIVER2_SET;
    dev_ctrl.fw_a = HBRIDGEDRIVER2_SET;
    dev_ctrl.ovr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.uvr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.mode = HBRIDGEDRIVER2_SET; 

    return hbridgedriver2_control( ctx, global_fault, dev_ctrl );
}

err_t hbridgedriver2_run_forward ( hbridgedriver2_t *ctx, uint8_t *global_fault ) 
{
    hbridgedriver2_ctrl_t dev_ctrl;
    
    dev_ctrl.hs_1 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ls_1 = HBRIDGEDRIVER2_SET;
    dev_ctrl.hs_2 = HBRIDGEDRIVER2_SET;
    dev_ctrl.ls_2 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.fw_h = HBRIDGEDRIVER2_SET;
    dev_ctrl.fw_a = HBRIDGEDRIVER2_SET;
    dev_ctrl.ovr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.uvr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.mode = HBRIDGEDRIVER2_SET; 

    return hbridgedriver2_control( ctx, global_fault, dev_ctrl );
}

err_t hbridgedriver2_stop ( hbridgedriver2_t *ctx, uint8_t *global_fault ) 
{
    hbridgedriver2_ctrl_t dev_ctrl;
    
    dev_ctrl.hs_1 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ls_1 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.hs_2 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ls_2 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.fw_h = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.fw_a = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ovr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.uvr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.mode = HBRIDGEDRIVER2_SET; 

    return hbridgedriver2_control( ctx, global_fault, dev_ctrl );
}

err_t hbridgedriver2_stop_with_brake ( hbridgedriver2_t *ctx, uint8_t *global_fault ) 
{
    hbridgedriver2_ctrl_t dev_ctrl;
    
    dev_ctrl.hs_1 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ls_1 = HBRIDGEDRIVER2_SET;
    dev_ctrl.hs_2 = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ls_2 = HBRIDGEDRIVER2_SET;
    dev_ctrl.fw_h = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.fw_a = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.ovr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.uvr  = HBRIDGEDRIVER2_CLEAR;
    dev_ctrl.mode = HBRIDGEDRIVER2_SET; 

    return hbridgedriver2_control( ctx, global_fault, dev_ctrl );
}

err_t hbridgedriver2_set_duty_cycle ( hbridgedriver2_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t hbridgedriver2_pwm_stop ( hbridgedriver2_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t hbridgedriver2_pwm_start ( hbridgedriver2_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

static void dev_tsact_delay ( void )
{
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_22us( );
}

static void dev_tcsn_hi_en_hi_delay ( void )
{
    Delay_80us( );
    Delay_22us( );
}

static void dev_repeat_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

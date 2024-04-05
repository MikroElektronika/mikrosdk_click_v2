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
 * @file adswio3.c
 * @brief AD-SWIO 3 Click Driver.
 */

#include "adswio3.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief AD-SWIO 3 senssel calculation function.
 * @details This function calculate voltage level on SENSEL Pin. 
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] vtg : Start register address.
 * @return Voltage level on SENSEL Pin.
 * @note None.
 */
static float adswio3_calc_senssel ( adswio3_t *ctx, float vtg );

/** 
 * @brief AD-SWIO 3 calculation for CRC 8 function.
 * @details This function calculates 8-bit CRC with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8+x2+x+1)
 * @li @c  Initialization 0x00000107
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_in : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t adswio3_cal_crc8 ( uint8_t *data_in, uint8_t len );

void adswio3_cfg_setup ( adswio3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;
    cfg->alr  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adswio3_init ( adswio3_t *ctx, adswio3_cfg_t *cfg ) 
{
    ctx->dig_out_mode = ADSWIO3_DIGI_OUT_MODE_SRC;
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

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->alr, cfg->alr );

    return SPI_MASTER_SUCCESS;
}

err_t adswio3_default_cfg ( adswio3_t *ctx ) 
{
    ADSWIO3_SET_DATA_SAMPLE_EDGE;
    adswio3_hw_reset( ctx );
    Delay_ms ( 100 );

    err_t err_flag = adswio3_function_setup( ctx, ADSWIO3_CH_FUNC_SETUP_VTG_IN );
    Delay_ms ( 100 );

    err_flag |= adswio3_set_diag_assign( ctx, ADSWIO3_DIAG_ASSIGN_AVDD, 
                                              ADSWIO3_DIAG_ASSIGN_AVSS, 
                                              ADSWIO3_DIAG_ASSIGN_AVCC, 
                                              ADSWIO3_DIAG_ASSIGN_LVIN );
    Delay_ms ( 100 );

    adswio3_adc_cnv_ctrl_t adc_cnv_ctrl;
    adc_cnv_ctrl.conv_rate_diag = ADSWIO3_ADC_CONV_RATE_DIAG_20_SPS;
    adc_cnv_ctrl.conv_seq = ADSWIO3_ADC_CONV_SEQ_START_CONT_CNV;
    adc_cnv_ctrl.diag_3_en = ADSWIO3_ADC_CONV_DIAG_EN;
    adc_cnv_ctrl.diag_2_en = ADSWIO3_ADC_CONV_DIAG_EN;
    adc_cnv_ctrl.diag_1_en = ADSWIO3_ADC_CONV_DIAG_EN;
    adc_cnv_ctrl.diag_0_en = ADSWIO3_ADC_CONV_DIAG_EN;
    adc_cnv_ctrl.conv2_en = ADSWIO3_ADC_CONV_CTRL_CONV_DIS;
    adc_cnv_ctrl.conv1_en = ADSWIO3_ADC_CONV_CTRL_CONV_EN;
    err_flag |= adswio3_set_adc_cnv( ctx, adc_cnv_ctrl );
    Delay_ms ( 100 );

    adswio3_adc_cfg_t adc_config;
    adc_config.conv1_mux = ADSWIO3_ADC_CONFIG_CNV1_SENSELF_AGND_SEN;
    adc_config.conv2_mux = ADSWIO3_ADC_CONFIG_CNV2_EXT1_AGND_SEN;
    adc_config.conv1_range = ADSWIO3_ADC_CONFIG_CNV_RANGE_P_12V;
    adc_config.conv2_range = ADSWIO3_ADC_CONFIG_CNV_RANGE_P_12V;
    adc_config.conv1_rate = ADSWIO3_ADC_CONFIG_CNV_RATE_4_8K_SPS;
    adc_config.conv2_rate = ADSWIO3_ADC_CONFIG_CNV_RATE_4_8K_SPS;
    err_flag |= adswio3_adc_config( ctx, adc_config );
    Delay_ms ( 100 );

    return err_flag;
}

void adswio3_hw_reset ( adswio3_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

err_t adswio3_register_write ( adswio3_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tx_data[ 4 ] = { 0 };

    tx_data[ 0 ] = reg;
    tx_data[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    tx_data[ 2 ] = ( uint8_t ) data_in;
    tx_data[ 3 ] = adswio3_cal_crc8( tx_data, 3 );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    err_t err_flag = spi_master_write( &ctx->spi, tx_data, 4 );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    return err_flag;
}

err_t adswio3_register_read ( adswio3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t crc8 = DUMMY;

    data_buf[ 0 ] = ADSWIO3_REG_READ_SELECT;
    data_buf[ 1 ] = ADSWIO3_READ_SELECT_AUTO_RD_EN;
    data_buf[ 2 ] = reg;
    data_buf[ 3 ] = adswio3_cal_crc8( data_buf, 3 );

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    err_t err_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );
    
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1us( );

    crc8 = adswio3_cal_crc8( data_buf, 3 );

    if ( ( crc8 != data_buf[ 3 ] ) || 
         ( ( data_buf[ 0 ] & ADSWIO3_READ_REG_STATUS_BIT ) != reg ) )
    {
        err_flag = ADSWIO3_ERROR;
    }
    else
    {
        *data_out = data_buf[ 1 ];
        *data_out <<= 8;
        *data_out |= data_buf[ 2 ];
    }

    return err_flag;
}

err_t adswio3_function_setup ( adswio3_t *ctx, uint8_t ch_fun )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ADSWIO3_CH_FUNC_SETUP_CURR_IN_HART_LOOP >= ch_fun )
    {
        err_flag = adswio3_register_write( ctx, ADSWIO3_REG_CH_FUNC_SETUP, ( uint16_t ) ch_fun );
    }
    return err_flag;
}

err_t adswio3_adc_config ( adswio3_t *ctx, adswio3_adc_cfg_t adc_config )
{
    uint16_t data_buf = DUMMY;
    data_buf  = ( ( uint16_t ) ( adc_config.conv2_rate  & 0x07 ) ) << 13;
    data_buf |= ( ( uint16_t ) ( adc_config.conv1_rate  & 0x07 ) ) << 10;
    data_buf |= ( ( uint16_t ) ( adc_config.conv2_range & 0x07 ) ) << 7;
    data_buf |= ( ( uint16_t ) ( adc_config.conv1_range & 0x07 ) ) << 4;
    data_buf |= ( ( uint16_t ) ( adc_config.conv2_mux   & 0x03 ) ) << 2;
    data_buf |=   ( uint16_t ) ( adc_config.conv1_mux   & 0x03 );
    return adswio3_register_write( ctx, ADSWIO3_REG_ADC_CONFIG, data_buf );
}

err_t adswio3_pwr_optim_config ( adswio3_t *ctx, uint8_t buff_sel, uint8_t buff_mode )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ( ADSWIO3_PWR_OPTIM_CONFIG_SEL_SEN_AGND >= buff_sel ) && 
         ( ADSWIO3_PWR_OPTIM_CONFIG_FULL_PWR >= buff_mode ) )
    {
        uint16_t data_buf = DUMMY;
        err_flag = adswio3_register_read( ctx, ADSWIO3_REG_PWR_OPTIM_CONFIG, &data_buf );
        data_buf &= ~( ( uint16_t ) ( 1 << buff_sel ) );
        data_buf |= ( uint16_t ) ( buff_mode << buff_sel );
        err_flag |= adswio3_register_write( ctx, ADSWIO3_REG_PWR_OPTIM_CONFIG, data_buf );
    }
    return err_flag;
}

err_t adswio3_output_config ( adswio3_t *ctx, adswio3_output_cfg_t out_cfg )
{
    uint16_t data_buf = DUMMY;
    data_buf  = ( ( uint16_t ) ( out_cfg.vout_range    & 0x01 ) ) << 7;
    data_buf |= ( ( uint16_t ) ( out_cfg.slew_en       & 0x03 ) ) << 5;
    data_buf |= ( ( uint16_t ) ( out_cfg.slew_lin_step & 0x03 ) ) << 3;
    data_buf |= ( ( uint16_t ) ( out_cfg.slew_lin_rate & 0x03 ) ) << 1;
    data_buf |=   ( uint16_t ) ( out_cfg.i_limit       & 0x01 );
    return adswio3_register_write( ctx, ADSWIO3_REG_OUTPUT_CONFIG, data_buf );
}

err_t adswio3_rtd_config ( adswio3_t *ctx, uint8_t rtd_mode_sel, uint8_t rtd_exc_swap, uint8_t rtd_current )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ( ADSWIO3_RTD3W4W_CONFIG_RTD_4_WIRE >= rtd_mode_sel )   && 
         ( ADSWIO3_RTD3W4W_CONFIG_RTD_EXC_SWAP >= rtd_exc_swap ) && 
         ( ADSWIO3_RTD3W4W_CONFIG_RTD_CURR_1MA >= rtd_current ) )
    {
        uint16_t data_buf = DUMMY;
        err_flag = adswio3_register_read( ctx, ADSWIO3_REG_RTD3W4W_CONFIG, &data_buf );
        data_buf &= ADSWIO3_RTD3W4W_CONFIG_BIT_MASK;
        data_buf |= ( uint16_t ) ( rtd_mode_sel << 3 );
        data_buf |= ( uint16_t ) ( rtd_exc_swap << 2 );
        data_buf |= ( uint16_t ) rtd_current;
        err_flag |= adswio3_register_write( ctx, ADSWIO3_REG_RTD3W4W_CONFIG, data_buf );
    }
    return err_flag;
}

err_t adswio3_set_dac_code ( adswio3_t *ctx, uint16_t dac_code )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ADSWIO3_DAC_CODE_RESOLUTION >= dac_code )
    {
        err_flag = adswio3_register_write( ctx, ADSWIO3_REG_DAC_CODE, dac_code );
    }
    return err_flag;
}

err_t adswio3_set_gpio_config ( adswio3_t *ctx, uint8_t gpio_sel, uint8_t gpo_data, 
                                                uint8_t gp_wk_pd_en, uint8_t out_mode )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ( ADSWIO3_GPIO_CONFIG_SEL_D >= gpio_sel ) && 
         ( ADSWIO3_GPIO_CONFIG_GPO_DATA_HIGH >= ( gp_wk_pd_en | gpo_data ) ) && 
         ( ADSWIO3_GPIO_CONFIG_MODE_TX_COM >= out_mode ) )
    {
        uint16_t data_buf = DUMMY;
        data_buf = ( uint16_t ) ( gpo_data << 4 );
        data_buf |= ( uint16_t ) ( gp_wk_pd_en << 3 );
        data_buf |= ( uint16_t ) out_mode;
        err_flag = adswio3_register_write( ctx, ADSWIO3_REG_GPIO_CONFIG0 + gpio_sel, data_buf );
    }
    return err_flag;
}

err_t adswio3_set_adc_cnv ( adswio3_t *ctx, adswio3_adc_cnv_ctrl_t adc_cnv_ctrl )
{
    uint16_t data_buf = DUMMY;
    data_buf  = ( ( uint16_t ) ( adc_cnv_ctrl.conv_rate_diag & 0x03 ) ) << 14;
    data_buf |= ( ( uint16_t ) ( adc_cnv_ctrl.conv_seq       & 0x03 ) ) << 12;
    data_buf |= ( ( uint16_t ) ( adc_cnv_ctrl.diag_3_en      & 0x01 ) ) << 11;
    data_buf |= ( ( uint16_t ) ( adc_cnv_ctrl.diag_2_en      & 0x01 ) ) << 10;
    data_buf |= ( ( uint16_t ) ( adc_cnv_ctrl.diag_1_en      & 0x01 ) ) << 9;
    data_buf |= ( ( uint16_t ) ( adc_cnv_ctrl.diag_0_en      & 0x01 ) ) << 8;
    data_buf |= ( ( uint16_t ) ( adc_cnv_ctrl.conv2_en       & 0x01 ) ) << 1;
    data_buf |=   ( uint16_t ) ( adc_cnv_ctrl.conv1_en       & 0x01 );
    return adswio3_register_write( ctx, ADSWIO3_REG_ADC_CONV_CTRL, data_buf );
}

err_t adswio3_set_diag_assign ( adswio3_t *ctx, uint8_t diag_0, uint8_t diag_1, 
                                                uint8_t diag_2, uint8_t diag_3 )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ADSWIO3_DIAG_ASSIGN_CURRENT_EXT >= ( diag_3 | diag_2 | diag_1 | diag_0 ) )
    {
        uint16_t data_buf = DUMMY;
        data_buf = ( uint16_t ) diag_3;
        data_buf <<= 4;
        data_buf |= ( uint16_t ) diag_2;
        data_buf <<= 4;
        data_buf |= ( uint16_t ) diag_1;
        data_buf <<= 4;
        data_buf |= ( uint16_t ) diag_0;
        err_flag = adswio3_register_write( ctx, ADSWIO3_REG_DIAG_ASSIGN, data_buf );
    }
    return err_flag;
}

err_t adswio3_get_status ( adswio3_t *ctx, adswio3_alert_status_t *alert_status, 
                                           adswio3_live_status_t *live_status )
{
    uint16_t data_buf = 0;
    err_t err_flag = adswio3_register_read( ctx, ADSWIO3_REG_ALERT_STATUS, &data_buf );
    alert_status->hart_alert     = ( ( uint8_t ) ( data_buf >> 15 ) ) & 0x01;
    alert_status->analog_io_oc   = ( ( uint8_t ) ( data_buf >> 14 ) ) & 0x01;
    alert_status->analog_io_sc   = ( ( uint8_t ) ( data_buf >> 13 ) ) & 0x01;
    alert_status->do_int_timeout = ( ( uint8_t ) ( data_buf >> 12 ) ) & 0x01;
    alert_status->do_ext_timeout = ( ( uint8_t ) ( data_buf >> 11 ) ) & 0x01;
    alert_status->do_int_sc      = ( ( uint8_t ) ( data_buf >> 10 ) ) & 0x01;
    alert_status->do_ext_sc      = ( ( uint8_t ) ( data_buf >> 9 ) )  & 0x01;
    alert_status->do_therm_reset = ( ( uint8_t ) ( data_buf >> 8 ) )  & 0x01;
    alert_status->di_oc_err      = ( ( uint8_t ) ( data_buf >> 7 ) )  & 0x01;
    alert_status->di_sc_err      = ( ( uint8_t ) ( data_buf >> 6 ) )  & 0x01;
    alert_status->adc_err        = ( ( uint8_t ) ( data_buf >> 5 ) )  & 0x01;
    alert_status->temp_alert     = ( ( uint8_t ) ( data_buf >> 4 ) )  & 0x01;
    alert_status->ppc_err        = ( ( uint8_t ) ( data_buf >> 3 ) )  & 0x01;
    alert_status->spi_err        = ( ( uint8_t ) ( data_buf >> 2 ) )  & 0x01;
    alert_status->supply_err     = ( ( uint8_t ) ( data_buf >> 1 ) )  & 0x01;
    alert_status->reset_occurred = ( ( uint8_t )   data_buf )         & 0x01;
    data_buf = 0;
    err_flag |= adswio3_register_read( ctx, ADSWIO3_REG_LIVE_STATUS, &data_buf );
    live_status->analog_io_oc_status   = ( ( uint8_t ) ( data_buf >> 14 ) ) & 0x01;
    live_status->analog_io_sc_status   = ( ( uint8_t ) ( data_buf >> 13 ) ) & 0x01;
    live_status->do_int_sc_status      = ( ( uint8_t ) ( data_buf >> 10 ) ) & 0x01;
    live_status->do_ext_sc_status      = ( ( uint8_t ) ( data_buf >> 9 ) )  & 0x01;
    live_status->do_therm_reset_status = ( ( uint8_t ) ( data_buf >> 8 ) )  & 0x01;
    live_status->di_oc_status          = ( ( uint8_t ) ( data_buf >> 7 ) )  & 0x01;
    live_status->di_sc_status          = ( ( uint8_t ) ( data_buf >> 6 ) )  & 0x01;
    live_status->temp_alert_status     = ( ( uint8_t ) ( data_buf >> 4 ) )  & 0x01;
    live_status->adc_data_rdy          = ( ( uint8_t ) ( data_buf >> 3 ) )  & 0x01;
    live_status->adc_busy              = ( ( uint8_t ) ( data_buf >> 2 ) )  & 0x01;
    live_status->supply_status         = ( ( uint8_t ) ( data_buf >> 1 ) )  & 0x01;
    return err_flag;
}

err_t adswio3_get_adc_res ( adswio3_t *ctx, uint8_t adc_sel, uint16_t *adc_data )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ADSWIO3_ADC_RESULT_SEL_2 >= adc_sel )
    {
        err_flag = adswio3_register_read( ctx, ADSWIO3_REG_ADC_RESULT1 + adc_sel, adc_data );
    }
    return err_flag;
}

err_t adswio3_get_voltage_input ( adswio3_t *ctx, uint8_t adc_sel, float *voltage )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ADSWIO3_ADC_RESULT_SEL_2 >= adc_sel )
    {
        uint16_t adc_data = DUMMY;
        err_flag = adswio3_get_adc_res( ctx, adc_sel, &adc_data );
        *voltage = ( float ) adc_data;
        *voltage /= ADSWIO3_ADC_RESULT_RESOLUTION;
        *voltage *= ADSWIO3_ADC_RESULT_RANGE;
    }
    return err_flag;
}

err_t adswio3_get_diag_res ( adswio3_t *ctx, uint8_t diag_sel, uint16_t *adc_diag_data )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ADSWIO3_DIAG_RESULT_SEL_3 >= diag_sel )
    {
        err_flag = adswio3_register_read( ctx, ADSWIO3_REG_ADC_DIAG_RESULT0 + diag_sel, adc_diag_data );
    }
    return err_flag;
}

err_t adswio3_get_ntc_temp ( adswio3_t *ctx, uint8_t diag_sel, float *ntc_temp )
{
    err_t err_flag = ADSWIO3_ERROR;
    float ntc_coeff_table[ 15 ] = { -19.6078, -17.1232, -14.807502, -12.706,
                                    -10.813, -9.1157, -9.1157, -7.61, -7.61,
                                    25.12, 28.25, 31.45, 30.72, 5.136, 42.13 };
    if ( ADSWIO3_DIAG_RESULT_SEL_3 >= diag_sel )
    {
        float temp = DUMMY, diag_vtg = DUMMY, coeff = DUMMY;
        uint8_t table_pos = 0;
        err_flag = adswio3_get_diag_vtg( ctx, diag_sel, &diag_vtg );
        if ( ADSWIO3_NTC_VTG_AT_25_C < diag_vtg )
        {
            temp = diag_vtg - ADSWIO3_NTC_VTG_AT_25_C;
            table_pos = ( uint8_t ) ( temp / ADSWIO3_NTC_TABLE_POS_CALC_P );
            if ( table_pos < ADSWIO3_NTC_TABLE_POS_MAX )
            {

                coeff = ntc_coeff_table[ table_pos ];
            }
            else
            {
                coeff = ntc_coeff_table[ 13 ];
            }
        }
        else
        {
            temp = ADSWIO3_NTC_VTG_AT_25_C - diag_vtg;
            table_pos = ( uint8_t ) ( temp / ADSWIO3_NTC_TABLE_POS_CALC_N );
            table_pos += ADSWIO3_NTC_TABLE_POS_MAX;
            if ( table_pos < ADSWIO3_NTC_TABLE_NEG_MAX )
            {
                coeff = ntc_coeff_table[ table_pos ];
            }
            else
            {
                coeff = ntc_coeff_table[ 14 ];
            }
        }
        *ntc_temp = temp * coeff;
        *ntc_temp += ADSWIO3_NTC_TEMP_AT_1_V;
    }
    return err_flag;
}

err_t adswio3_get_diag_vtg ( adswio3_t *ctx, uint8_t diag_sel, float *diag_vtg )
{
    uint16_t adc_diag_data = DUMMY, diag_assign = DUMMY;
    err_t err_flag = adswio3_register_read( ctx, ADSWIO3_REG_DIAG_ASSIGN, &diag_assign );
    Delay_1ms( );
    err_flag |= adswio3_get_diag_res( ctx, diag_sel, &adc_diag_data );
    Delay_1ms( );

    diag_sel *= 4;
    diag_assign >>= diag_sel;
    diag_assign &= ADSWIO3_DIAG_ASSIGN_CURRENT_EXT;

    switch ( diag_assign )
    {
        case ADSWIO3_DIAG_ASSIGN_AGND:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_AGND( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_TEMP_SENS:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_SENS_TEMP( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_DVCC:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_DVCC( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_AVCC:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_VTG_AVCC( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_ALDO1V8:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_ALDO1V8( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_DLDO1V8:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_DLDO1V8( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_REFOUT:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_REFOUT( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_AVDD:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_VTG_AVDD( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_AVSS:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_VTG_AVSS( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_LVIN:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_LVIN( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_SENSEL:
        {
            *diag_vtg = adswio3_calc_senssel( ctx, ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_SENSE_EXT1:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_SENSE_EXT( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_SENSE_EXT2:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_SENSE_EXT( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_DO_VDD:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_DO_VDD( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_AGND0:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_AGND( ( float ) adc_diag_data );
            break;
        }
        case ADSWIO3_DIAG_ASSIGN_CURRENT_EXT:
        {
            *diag_vtg = ADSWIO3_CALC_DIAG_CURRENT( ( float ) adc_diag_data * 
                                                    ctx->dig_out_mode );
            break;
        }
        default: 
        {
            err_flag = ADSWIO3_ERROR;
            break;
        }
    }
    return err_flag;
}

err_t adswio3_set_alert_mask ( adswio3_t *ctx, uint16_t alert_mask )
{
    err_t err_flag = ADSWIO3_ERROR;
    if ( ( ADSWIO3_ALERT_ANALOG_IO_OC_MASK >= alert_mask ) && 
         ( ADSWIO3_ALERT_SPI_ERR_MASK <= alert_mask ) )
    {
        err_flag = adswio3_register_write( ctx, ADSWIO3_REG_ALERT_MASK, alert_mask );
    }
    return err_flag;
}

err_t adswio3_set_ppc_vtg ( adswio3_t *ctx, float ppc_vtg )
{
    err_t err_flag = ADSWIO3_OK;
    uint16_t data_buf = 0;
    if ( ( ADSWIO3_PPC_TX_AVDD_VTG_MAX < ppc_vtg ) || 
         ( ADSWIO3_PPC_TX_AVDD_VTG_MIN > ppc_vtg ) )
    {
        err_flag = ADSWIO3_ERROR;
    }
    else
    {
        err_flag = adswio3_register_read( ctx, ADSWIO3_REG_PPC_ACTIVE, &data_buf );
        if ( ADSWIO3_OK == ( data_buf & ( ADSWIO3_PPC_ACTIVE_TX_BUSY | 
                                          ADSWIO3_PPC_ACTIVE_PPC_TX_BUSY_ERR ) ) )
        {
            ppc_vtg /= ADSWIO3_PPC_TX_AVDD_VTG_MAX;
            ppc_vtg *= ADSWIO3_PPC_TX_AVDD_DATA_MAX;
            ppc_vtg -= ADSWIO3_PPC_TX_AVDD_DATA_CALC;
            err_flag |= adswio3_register_write( ctx, ADSWIO3_REG_PPC_TX, ( uint16_t ) ppc_vtg );
        }
    }
    return err_flag;
}

uint8_t adswio3_get_ready ( adswio3_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t adswio3_get_alarm ( adswio3_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

static float adswio3_calc_senssel ( adswio3_t *ctx, float vtg )
{
    uint16_t data_buf = DUMMY;
    float senssel_vtg = DUMMY, avdd_vtg = DUMMY;
    err_t err_flag = adswio3_register_read( ctx, ADSWIO3_REG_DIN_CONFIG2, &data_buf );
    if ( ADSWIO3_DIN_CONFIG2_DIN_THRESH_MODE & data_buf )
    {
        senssel_vtg = vtg * ADSWIO3_SENS_SEL_TRSH_MULTI;
        senssel_vtg -= ADSWIO3_SENS_SEL_TRSH_CORR_VAL;
    }
    else
    {
        data_buf = DUMMY;
        err_flag |= adswio3_register_read( ctx, ADSWIO3_REG_PPC_TX, &data_buf );
        avdd_vtg = ( float ) data_buf;
        avdd_vtg *= ADSWIO3_PPC_TX_AVDD_VTG_DEFAULT;
        avdd_vtg /= ADSWIO3_PPC_TX_AVDD_DATA_MAX;
        senssel_vtg = vtg * ADSWIO3_SENS_SEL_SCALE_MULTI;
        senssel_vtg -= avdd_vtg;
    }

    return senssel_vtg;
}

static uint8_t adswio3_cal_crc8 ( uint8_t *data_in, uint8_t len )
{
    uint32_t crc_code = 0x00000107;
    uint8_t i = 31;
    uint32_t data_out = 0;
    uint8_t crc_check = 0;

    for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
    {
        data_out |= data_in[ n_cnt ];
        data_out <<= 8;
    }

    while ( i >= 8 )
    {
        if ( ( data_out & ( ( uint32_t ) 1 << i ) ) != 0 )
        {
            data_out ^= ( crc_code << ( i - 8 ) );
        }
        i--;
    }

    crc_check = ( uint8_t ) data_out;
    
    return crc_check;
}

// ------------------------------------------------------------------------- END

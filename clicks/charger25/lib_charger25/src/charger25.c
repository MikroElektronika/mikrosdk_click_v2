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
 * @file charger25.c
 * @brief Charger 25 Click Driver.
 */

#include "charger25.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void charger25_cfg_setup ( charger25_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->qon = HAL_PIN_NC;
    cfg->ce = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER25_DEVICE_ADDRESS;
}

err_t charger25_init ( charger25_t *ctx, charger25_cfg_t *cfg ) 
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

    digital_out_init( &ctx->qon, cfg->qon );
    digital_out_init( &ctx->ce, cfg->ce );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t charger25_default_cfg ( charger25_t *ctx ) 
{
    charger25_set_qon_pin( ctx, CHARGER25_STATE_PIN_QON_LOW );
    Delay_100ms( );
    
    charger25_enable( ctx );
    Delay_100ms( );
    
    charger25_sw_reset( ctx );
    Delay_100ms( );

    charger25_adc_func_t adc_func;
    adc_func.ibus_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.ibat_adc_dis = CHARGER25_SET_ADC_FUNC_ENABLE;
    adc_func.vbus_adc_dis = CHARGER25_SET_ADC_FUNC_ENABLE;
    adc_func.vbat_adc_dis = CHARGER25_SET_ADC_FUNC_ENABLE;
    adc_func.vsys_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.ts_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.tdie_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.dp_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.dm_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.vac2_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    adc_func.vac1_adc_dis = CHARGER25_SET_ADC_FUNC_DISABLE;
    err_t err_flag = charger25_set_adc_function ( ctx, adc_func );
    Delay_100ms( );
    
    charger25_adc_ctrl_t adc_control;
    adc_control.adc_en = CHARGER25_SET_ADC_CTRL_ENABLE;
    adc_control.adc_rate = CHARGER25_SET_ADC_RATE_CONT_CNV;
    adc_control.adc_sample = CHARGER25_SET_ADC_SAMPLE_15_BIT;
    adc_control.adc_avg = CHARGER25_SET_ADC_AVG_RUN_AVG;
    adc_control.adc_avg_init = CHARGER25_SET_ADC_AVG_INIT_ADC_CNV;
    err_flag |= charger25_set_adc_control ( ctx, adc_control );
    Delay_100ms( );
    
    return err_flag;
}

err_t charger25_generic_write ( charger25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t charger25_generic_read ( charger25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void charger25_set_qon_pin ( charger25_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->qon, state );
}

void charger25_enable ( charger25_t *ctx )
{
    digital_out_low( &ctx->ce );
}

void charger25_disable ( charger25_t *ctx )
{
    digital_out_high( &ctx->ce );
}

uint8_t charger25_get_interrupt ( charger25_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t charger25_sw_reset ( charger25_t *ctx )
{
    uint8_t tx_buf = CHARGER25_SOFT_RESET;
    return charger25_generic_write( ctx, CHARGER25_REG_TERMINATION_CONTROL, &tx_buf, 1 );
}

err_t charger25_get_vbat ( charger25_t *ctx, uint16_t *vbat )
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t vbat_data = DUMMY;
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_VBAT_ADC, data_buf, 2 );
    *vbat = data_buf[ 0 ];
    *vbat <<= 8;
    *vbat |= data_buf[ 1 ];
    return err_flag;
}

err_t charger25_get_vsys_min ( charger25_t *ctx, uint16_t *vsys_min )
{
    uint8_t data_buf = 0;
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_MINIMAL_SYSTEM_VOLTAGE, &data_buf, 1 );
    data_buf &= CHARGER25_VSYS_MIN_BIT_MASK;
    *vsys_min = data_buf;
    *vsys_min *= CHARGER25_VSYS_MIN_STEP_SIZE;
    *vsys_min += CHARGER25_VSYS_MIN_FIXED_OFFSET;  
    return err_flag;
}

err_t charger25_set_adc_control ( charger25_t *ctx, charger25_adc_ctrl_t adc_ctrl )
{
    uint8_t data_buf = DUMMY;
    data_buf |= ( adc_ctrl.adc_en       & 0x01 ) << 7;
    data_buf |= ( adc_ctrl.adc_rate     & 0x01 ) << 6;
    data_buf |= ( adc_ctrl.adc_sample   & 0x03 ) << 4;
    data_buf |= ( adc_ctrl.adc_avg      & 0x01 ) << 3;
    data_buf |= ( adc_ctrl.adc_avg_init & 0x01 ) << 2;
    return charger25_generic_write( ctx, CHARGER25_REG_ADC_CONTROL, &data_buf, 1 );
}

err_t charger25_set_adc_function ( charger25_t *ctx, charger25_adc_func_t adc_func )
{
    uint8_t data_buf = DUMMY;
    data_buf |= ( adc_func.ibus_adc_dis & 0x01 ) << 7;
    data_buf |= ( adc_func.ibat_adc_dis & 0x01 ) << 6;
    data_buf |= ( adc_func.vbus_adc_dis & 0x01 ) << 5;
    data_buf |= ( adc_func.vbat_adc_dis & 0x01 ) << 4;
    data_buf |= ( adc_func.vsys_adc_dis & 0x01 ) << 3;
    data_buf |= ( adc_func.ts_adc_dis   & 0x01 ) << 2;
    data_buf |= ( adc_func.tdie_adc_dis & 0x01 ) << 1;
    err_t err_flag = charger25_generic_write( ctx, CHARGER25_REG_ADC_FUNCTION_DISABLE_0, &data_buf, 1 );
    Delay_10ms( );
    data_buf = DUMMY;
    data_buf |= ( adc_func.dp_adc_dis   & 0x01 ) << 7;
    data_buf |= ( adc_func.dm_adc_dis   & 0x01 ) << 6;
    data_buf |= ( adc_func.vac2_adc_dis & 0x01 ) << 5;
    data_buf |= ( adc_func.vac1_adc_dis & 0x01 ) << 4;
    err_flag |= charger25_generic_write( ctx, CHARGER25_REG_ADC_FUNCTION_DISABLE_1, &data_buf, 1 );
    return err_flag;
}

err_t charger25_get_vbat_lim ( charger25_t *ctx, uint16_t *vtg_lim )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_CHARGE_VOLTAGE_LIMIT, data_buf, 2 );
    *vtg_lim = data_buf[ 0 ] & CHARGER25_VTG_LIM_MSB_BIT_MASK;
    *vtg_lim <<= 8;
    *vtg_lim |= data_buf[ 1 ];
    *vtg_lim *= CHARGER25_VTG_CONV_V_MV;
    return err_flag;
}

err_t charger25_set_vbat_lim ( charger25_t *ctx, uint16_t vtg_lim )
{
    vtg_lim /= CHARGER25_VTG_CONV_V_MV; 
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( vtg_lim >> 8 );
    data_buf[ 1 ] = ( uint8_t )   vtg_lim;
    return charger25_generic_write( ctx, CHARGER25_REG_CHARGE_VOLTAGE_LIMIT, data_buf, 2 );
}

err_t charger25_get_cell_count ( charger25_t *ctx, uint8_t *cell_count )
{
    uint16_t vsys_min = DUMMY;
    err_t err_flag = charger25_get_vsys_min( ctx, &vsys_min );
    *cell_count = ( uint8_t ) ( vsys_min / CHARGER25_VTG_CELL_COUNT_DIV );
    return err_flag;
}

err_t charger25_set_cell_count ( charger25_t *ctx, uint8_t cell_count )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = CHARGER25_OK;
    if ( ( CHARGER25_VTG_CELL_COUNT_MIN > cell_count ) || 
         ( CHARGER25_VTG_CELL_COUNT_MAX < cell_count ) )
    {
        err_flag = CHARGER25_ERROR;
    }
    else
    {
        data_buf = cell_count * CHARGER25_VTG_CELL_COUNT_MAX;
        data_buf += ( cell_count - 1 ) * CHARGER25_VTG_CELL_COUNT_MUL;
        if ( ( CHARGER25_VTG_CELL_SEL_2 == cell_count ) || 
             ( CHARGER25_VTG_CELL_SEL_4 == cell_count ) )
        {
            data_buf++;
        }
        err_flag |= charger25_generic_write( ctx, CHARGER25_REG_MINIMAL_SYSTEM_VOLTAGE, &data_buf, 1 );
    }
    return err_flag;
}

err_t charger25_get_current_limit ( charger25_t *ctx, uint16_t *current_lim )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_CHARGE_CURRENT_LIMIT, data_buf, 2 );
    *current_lim = data_buf[ 0 ] & CHARGER25_CURR_LIM_MSB_BIT_MASK;
    *current_lim <<= 8;
    *current_lim |= data_buf[ 1 ];
    *current_lim *= CHARGER25_CURR_CONV_A_MA;
    return err_flag;
}

err_t charger25_set_current_limit ( charger25_t *ctx, uint16_t current_lim )
{
    current_lim /= CHARGER25_CURR_CONV_A_MA; 
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( current_lim >> 8 );
    data_buf[ 1 ] = ( uint8_t )   current_lim;
    return charger25_generic_write( ctx, CHARGER25_REG_CHARGE_CURRENT_LIMIT, data_buf, 2 );
}

err_t charger25_get_input_vtg_limit ( charger25_t *ctx, uint16_t *input_vtg_limit )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_INPUT_VOLTAGE_LIMIT, &data_buf, 1 );
    *input_vtg_limit = data_buf;
    *input_vtg_limit *= CHARGER25_INPUT_VTG_CONV_V_MV;
    return err_flag;
}

err_t charger25_set_input_vtg_limit ( charger25_t *ctx, uint16_t input_vtg_limit )
{
    uint8_t data_buf = DUMMY;
    data_buf = ( uint8_t ) ( input_vtg_limit / CHARGER25_INPUT_VTG_CONV_V_MV ); 
    return charger25_generic_write( ctx, CHARGER25_REG_INPUT_VOLTAGE_LIMIT, &data_buf, 1 );
}

err_t charger25_get_input_curr_limit ( charger25_t *ctx, uint16_t *input_curr_limit )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_INPUT_CURRENT_LIMIT, data_buf, 2 );
    *input_curr_limit = data_buf[ 0 ] & CHARGER25_CURR_LIM_MSB_BIT_MASK;
    *input_curr_limit <<= 8;
    *input_curr_limit |= data_buf[ 1 ];
    *input_curr_limit *= CHARGER25_CURR_CONV_A_MA;
    return err_flag;
}

err_t charger25_set_input_curr_limit ( charger25_t *ctx, uint16_t input_curr_limit )
{
    input_curr_limit /= CHARGER25_CURR_CONV_A_MA; 
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( input_curr_limit >> 8 );
    data_buf[ 1 ] = ( uint8_t )   input_curr_limit;
    return charger25_generic_write( ctx, CHARGER25_REG_INPUT_CURRENT_LIMIT, data_buf, 2 );
}

err_t charger25_get_status ( charger25_t *ctx, charger25_status_t *status )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = charger25_generic_read( ctx, CHARGER25_REG_CHARGER_STATUS_0, &data_buf, 1 );
    Delay_1ms( );
    status->iindpm_stat       = ( data_buf >> 7 ) & 0x01;
    status->vindpm_stat       = ( data_buf >> 6 ) & 0x01;
    status->wd_stat           = ( data_buf >> 5 ) & 0x01;
    status->poorsrc_stat      = ( data_buf >> 4 ) & 0x01;
    status->pg_stat           = ( data_buf >> 3 ) & 0x01;
    status->ac2_present_stat  = ( data_buf >> 2 ) & 0x01;
    status->ac1_present_stat  = ( data_buf >> 1 ) & 0x01;
    status->vbus_present_stat =   data_buf        & 0x01;
    err_flag |= charger25_generic_read( ctx, CHARGER25_REG_CHARGER_STATUS_1, &data_buf, 1 );
    Delay_1ms( );
    status->chg_stat   = ( data_buf >> 5 ) & 0x07;
    status->vbus_stat  = ( data_buf >> 1 ) & 0x0F;
    status->bc1_2_done =   data_buf        & 0x01;
    err_flag |= charger25_generic_read( ctx, CHARGER25_REG_CHARGER_STATUS_2, &data_buf, 1 );
    Delay_1ms( );
    status->ico_stat          = ( data_buf >> 6 ) & 0x03;
    status->treg_stat         = ( data_buf >> 2 ) & 0x01;
    status->dpdm_stat         = ( data_buf >> 1 ) & 0x01;
    status->vbat_present_stat =   data_buf        & 0x01;
    err_flag |= charger25_generic_read( ctx, CHARGER25_REG_CHARGER_STATUS_3, &data_buf, 1 );
    Delay_1ms( );
    status->acrb2_stat      = ( data_buf >> 7 ) & 0x01;
    status->acrb1_stat      = ( data_buf >> 6 ) & 0x01;
    status->adc_done_stat   = ( data_buf >> 5 ) & 0x01;
    status->vsys_stat       = ( data_buf >> 4 ) & 0x01;
    status->chg_tmr_stat    = ( data_buf >> 3 ) & 0x01;
    status->trichg_tmr_stat = ( data_buf >> 2 ) & 0x01;
    status->prechg_tmr_stat = ( data_buf >> 1 ) & 0x01;
    err_flag |= charger25_generic_read( ctx, CHARGER25_REG_CHARGER_STATUS_4, &data_buf, 1 );
    Delay_1ms( );
    status->vbatotg_low_stat = ( data_buf >> 4 ) & 0x01;
    status->ts_cold_stat     = ( data_buf >> 3 ) & 0x01;
    status->ts_cool_stat     = ( data_buf >> 2 ) & 0x01;
    status->ts_warm_stat     = ( data_buf >> 1 ) & 0x01;
    status->ts_hot_stat      =   data_buf        & 0x01;
    return err_flag;
}

// ------------------------------------------------------------------------- END

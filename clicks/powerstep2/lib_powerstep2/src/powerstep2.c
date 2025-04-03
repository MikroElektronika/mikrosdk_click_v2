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
 * @file powerstep2.c
 * @brief Power Step 2 Click Driver.
 */

#include "powerstep2.h"

/**
 * @brief Power Step 2 get parameter length function.
 * @details This function determines the length of the specified parameter in bytes for the Power Step 2 device.
 * @param[in] param : Parameter register.
 * @return Parameter length in bytes (1, 2, or 3), depending on the parameter.
 * If the parameter is not recognized, the function defaults to 1 byte.
 */
static uint8_t powerstep2_get_param_len ( uint8_t param );

/**
 * @brief Set delay for controlling motor speed in step clock mode.
 * @details This function sets a delay between toggling step pin.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return None.
 */
static void powerstep2_speed_delay ( powerstep2_t *ctx, uint8_t speed_macro );

void powerstep2_cfg_setup ( powerstep2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->busy = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->flag = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t powerstep2_init ( powerstep2_t *ctx, powerstep2_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, POWERSTEP2_CMD_NOP ) ) 
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
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->busy, cfg->busy );
    digital_in_init( &ctx->flag, cfg->flag );

    return SPI_MASTER_SUCCESS;
}

err_t powerstep2_default_cfg ( powerstep2_t *ctx ) 
{
    err_t error_flag = POWERSTEP2_OK;
    powerstep2_hw_reset_device ( ctx );
    error_flag |= powerstep2_reset_device ( ctx );
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_ACC, POWERSTEP2_GEN_ACC_DEF );
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_DEC, POWERSTEP2_GEN_DEC_DEF );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_MAX_SPEED, POWERSTEP2_GEN_MAX_SPEED_DEF );
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_MIN_SPEED, POWERSTEP2_GEN_MIN_SPEED_DEF );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_OCD_TH, POWERSTEP2_GEN_OCD_TH_DEF );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_FS_SPD, POWERSTEP2_GEN_FS_SPD_DEF );
    error_flag |= powerstep2_soft_hiz ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_STEP_MODE, POWERSTEP2_GEN_STEP_MODE_DEF );
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_ALARM_EN, POWERSTEP2_GEN_ALARM_EN_DEF );
    error_flag |= powerstep2_soft_hiz ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_GATECFG1, POWERSTEP2_GEN_GATECFG1_DEF );
    error_flag |= powerstep2_soft_hiz ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_GATECFG2, POWERSTEP2_GEN_GATECFG2_DEF );

    if ( POWERSTEP2_GEN_STEP_MODE_CM_VM_CURRENT == ( POWERSTEP2_GEN_STEP_MODE_CM_VM_MASK & POWERSTEP2_GEN_STEP_MODE_DEF ) )
    {
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_CONFIG, POWERSTEP2_C_CONFIG_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_HOLD, POWERSTEP2_C_TVAL_HOLD_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_RUN, POWERSTEP2_C_TVAL_RUN_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_ACC, POWERSTEP2_C_TVAL_ACC_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_DEC, POWERSTEP2_C_TVAL_DEC_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_T_FAST, POWERSTEP2_C_T_FAST_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TON_MIN, POWERSTEP2_C_TON_MIN_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TOFF_MIN, POWERSTEP2_C_TOFF_MIN_DEF );
    }
    else
    {
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_CONFIG, POWERSTEP2_V_CONFIG_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_HOLD, POWERSTEP2_V_KVAL_HOLD_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_RUN, POWERSTEP2_V_KVAL_RUN_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_ACC, POWERSTEP2_V_KVAL_ACC_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_DEC, POWERSTEP2_V_KVAL_DEC_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_INT_SPEED, POWERSTEP2_V_INT_SPEED_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_ST_SLP, POWERSTEP2_V_ST_SLP_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_FN_SLP_ACC, POWERSTEP2_V_FN_SLP_ACC_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_FN_SLP_DEC, POWERSTEP2_V_FN_SLP_DEC_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_K_THERM, POWERSTEP2_V_K_THERM_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_STALL_TH, POWERSTEP2_V_STALL_TH_DEF );
    }
    error_flag |= powerstep2_clear_status ( ctx );

    return error_flag;
}

err_t powerstep2_spi_transfer ( powerstep2_t *ctx, uint8_t *data_io, uint8_t len )
{
    err_t error_flag = POWERSTEP2_OK;
    uint8_t cnt = 0;
    if ( ( 0 == len ) || ( NULL == data_io ) )
    {
        return POWERSTEP2_ERROR;
    }
    for ( cnt = 0; cnt < len; cnt++ )
    {
        while ( !powerstep2_get_busy_pin ( ctx ) );
        spi_master_select_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, data_io[ cnt ] );
        error_flag |= spi_master_read( &ctx->spi, &data_io[ cnt ], 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    spi_master_set_default_write_data( &ctx->spi, POWERSTEP2_CMD_NOP );
    return error_flag;
}

void powerstep2_set_rst_pin ( powerstep2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void powerstep2_set_step_pin ( powerstep2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

uint8_t powerstep2_get_busy_pin ( powerstep2_t *ctx )
{
    return digital_in_read ( &ctx->busy );
}

uint8_t powerstep2_get_flag_pin ( powerstep2_t *ctx )
{
    return digital_in_read ( &ctx->flag );
}

void powerstep2_hw_reset_device ( powerstep2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t powerstep2_set_param ( powerstep2_t *ctx, uint8_t param, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    uint8_t param_len = 0;
    uint8_t cnt = 0;
    if ( ( param < POWERSTEP2_PARAM_GEN_ABS_POS ) || 
         ( param > POWERSTEP2_PARAM_GEN_STATUS ) || 
         ( POWERSTEP2_PARAM_GEN_SPEED == param ) || 
         ( POWERSTEP2_PARAM_GEN_ADC_OUT == param ) || 
         ( POWERSTEP2_PARAM_GEN_STATUS == param ) )
    {
        return POWERSTEP2_ERROR;
    }
    param_len = powerstep2_get_param_len ( param );
    data_buf[ 0 ] = POWERSTEP2_CMD_SET_PARAM | param;
    for ( cnt = 0; cnt < param_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = ( uint8_t ) ( ( data_in >> ( ( param_len - cnt - 1 ) * 8 ) ) & 0xFF );
    }
    return powerstep2_spi_transfer ( ctx, data_buf, param_len + 1 );
}

err_t powerstep2_get_param ( powerstep2_t *ctx, uint8_t param, uint32_t *data_out )
{
    err_t error_flag = POWERSTEP2_OK;
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    uint8_t param_len = 0;
    uint8_t cnt = 0;
    if ( ( NULL == data_out ) || 
         ( param < POWERSTEP2_PARAM_GEN_ABS_POS ) || 
         ( param > POWERSTEP2_PARAM_GEN_STATUS ) )
    {
        return POWERSTEP2_ERROR;
    }
    param_len = powerstep2_get_param_len ( param );
    data_buf[ 0 ] = POWERSTEP2_CMD_GET_PARAM | param;
    error_flag |= powerstep2_spi_transfer ( ctx, data_buf, param_len + 1 );
    *data_out = 0;
    for ( cnt = 0; ( cnt < param_len ) && ( POWERSTEP2_OK == error_flag ); cnt++ )
    {
        *data_out <<= 8;
        *data_out |= data_buf[ cnt + 1 ];
    }
    return error_flag;
}

err_t powerstep2_run ( powerstep2_t *ctx, uint8_t dir, uint32_t speed )
{
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    if ( ( dir > POWERSTEP2_DIR_CW ) || 
         ( speed > 0x0FFFFF ) )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_RUN | dir;
    data_buf[ 1 ] = ( uint8_t ) ( ( speed >> 16 ) & 0x0F );
    data_buf[ 2 ] = ( uint8_t ) ( ( speed >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( speed & 0xFF );
    return powerstep2_spi_transfer ( ctx, data_buf, 4 );
}

err_t powerstep2_step_clock ( powerstep2_t *ctx, uint8_t dir )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_NOP };
    if ( dir > POWERSTEP2_DIR_CW )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_STEP_CLOCK | dir;
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_move ( powerstep2_t *ctx, uint8_t dir, uint32_t n_step )
{
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    if ( ( dir > POWERSTEP2_DIR_CW ) || 
         ( n_step > 0x3FFFFF ) )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_MOVE | dir;
    data_buf[ 1 ] = ( uint8_t ) ( ( n_step >> 16 ) & 0x3F );
    data_buf[ 2 ] = ( uint8_t ) ( ( n_step >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( n_step & 0xFF );
    return powerstep2_spi_transfer ( ctx, data_buf, 4 );
}

err_t powerstep2_go_to ( powerstep2_t *ctx, uint32_t abs_pos )
{
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    if ( abs_pos > 0x3FFFFF )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_GO_TO;
    data_buf[ 1 ] = ( uint8_t ) ( ( abs_pos >> 16 ) & 0x3F );
    data_buf[ 2 ] = ( uint8_t ) ( ( abs_pos >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( abs_pos & 0xFF );
    return powerstep2_spi_transfer ( ctx, data_buf, 4 );
}

err_t powerstep2_go_to_dir ( powerstep2_t *ctx, uint8_t dir, uint32_t abs_pos )
{
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    if ( ( dir > POWERSTEP2_DIR_CW ) || 
         ( abs_pos > 0x3FFFFF ) )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_GO_TO_DIR | dir;
    data_buf[ 1 ] = ( uint8_t ) ( ( abs_pos >> 16 ) & 0x3F );
    data_buf[ 2 ] = ( uint8_t ) ( ( abs_pos >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( abs_pos & 0xFF );
    return powerstep2_spi_transfer ( ctx, data_buf, 4 );
}

err_t powerstep2_go_until ( powerstep2_t *ctx, uint8_t act, uint8_t dir, uint32_t speed )
{
    uint8_t data_buf[ 4 ] = { POWERSTEP2_CMD_NOP };
    if ( ( act > 1 ) || 
         ( dir > POWERSTEP2_DIR_CW ) || 
         ( speed > 0x0FFFFF ) )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_GO_UNTIL | ( act << 3 ) | dir;
    data_buf[ 1 ] = ( uint8_t ) ( ( speed >> 16 ) & 0x0F );
    data_buf[ 2 ] = ( uint8_t ) ( ( speed >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( speed & 0xFF );
    return powerstep2_spi_transfer ( ctx, data_buf, 4 );
}

err_t powerstep2_release_sw ( powerstep2_t *ctx, uint8_t act, uint8_t dir )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_NOP };
    if ( ( act > 1 ) || 
         ( dir > POWERSTEP2_DIR_CW ) )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_RELEASE_SW | ( act << 3 ) | dir;
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_go_home ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_GO_HOME };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_go_mark ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_GO_MARK };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_reset_pos ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_RESET_POS };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_reset_device ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_RESET_DEVICE };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_soft_stop ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_SOFT_STOP };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_hard_stop ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_HARD_STOP };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_soft_hiz ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_SOFT_HIZ };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_hard_hiz ( powerstep2_t *ctx )
{
    uint8_t data_buf[ 1 ] = { POWERSTEP2_CMD_HARD_HIZ };
    return powerstep2_spi_transfer ( ctx, data_buf, 1 );
}

err_t powerstep2_get_status ( powerstep2_t *ctx, uint16_t *status )
{
    err_t error_flag = POWERSTEP2_OK;
    uint8_t data_buf[ 3 ] = { POWERSTEP2_CMD_NOP };
    if ( NULL == status )
    {
        return POWERSTEP2_ERROR;
    }
    data_buf[ 0 ] = POWERSTEP2_CMD_GET_STATUS;
    error_flag |= powerstep2_spi_transfer ( ctx, data_buf, 3 );
    if ( POWERSTEP2_OK == error_flag )
    {
        *status = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

err_t powerstep2_clear_status ( powerstep2_t *ctx )
{
    uint16_t status = 0;
    return powerstep2_get_status ( ctx, &status );
}

err_t powerstep2_set_control_mode ( powerstep2_t *ctx, uint8_t ctrl_mode )
{
    err_t error_flag = POWERSTEP2_OK;
    uint32_t param_data = 0;
    if ( ctrl_mode > POWERSTEP2_CONTROL_MODE_CURRENT )
    {
        return POWERSTEP2_ERROR;
    }
    error_flag |= powerstep2_soft_hiz ( ctx );
    error_flag |= powerstep2_get_param ( ctx, POWERSTEP2_PARAM_GEN_STEP_MODE, &param_data );
    param_data &= ( ~POWERSTEP2_GEN_STEP_MODE_CM_VM_MASK );
    param_data |= ( ( ctrl_mode << 3 ) & POWERSTEP2_GEN_STEP_MODE_CM_VM_MASK );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_STEP_MODE, param_data );
    if ( POWERSTEP2_CONTROL_MODE_CURRENT == ctrl_mode )
    {
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_CONFIG, POWERSTEP2_C_CONFIG_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_HOLD, POWERSTEP2_C_TVAL_HOLD_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_RUN, POWERSTEP2_C_TVAL_RUN_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_ACC, POWERSTEP2_C_TVAL_ACC_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TVAL_DEC, POWERSTEP2_C_TVAL_DEC_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_T_FAST, POWERSTEP2_C_T_FAST_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TON_MIN, POWERSTEP2_C_TON_MIN_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_C_TOFF_MIN, POWERSTEP2_C_TOFF_MIN_DEF );
    }
    else
    {
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_CONFIG, POWERSTEP2_V_CONFIG_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_HOLD, POWERSTEP2_V_KVAL_HOLD_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_RUN, POWERSTEP2_V_KVAL_RUN_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_ACC, POWERSTEP2_V_KVAL_ACC_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_KVAL_DEC, POWERSTEP2_V_KVAL_DEC_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_INT_SPEED, POWERSTEP2_V_INT_SPEED_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_ST_SLP, POWERSTEP2_V_ST_SLP_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_FN_SLP_ACC, POWERSTEP2_V_FN_SLP_ACC_DEF );
        error_flag |= powerstep2_soft_hiz ( ctx );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_FN_SLP_DEC, POWERSTEP2_V_FN_SLP_DEC_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_K_THERM, POWERSTEP2_V_K_THERM_DEF );
        error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_V_STALL_TH, POWERSTEP2_V_STALL_TH_DEF );
    }
    if ( POWERSTEP2_OK == error_flag )
    {
        ctx->control_mode = ctrl_mode;
    }
    return error_flag;
}

err_t powerstep2_set_step_mode ( powerstep2_t *ctx, uint8_t step_mode )
{
    err_t error_flag = POWERSTEP2_OK;
    uint32_t param_data = 0;
    if ( step_mode > POWERSTEP2_STEP_MODE_1_OVER_128 )
    {
        return POWERSTEP2_ERROR;
    }
    error_flag |= powerstep2_soft_hiz ( ctx );
    error_flag |= powerstep2_get_param ( ctx, POWERSTEP2_PARAM_GEN_STEP_MODE, &param_data );
    param_data &= ( ~POWERSTEP2_GEN_STEP_MODE_STEP_SEL_MASK );
    param_data |= step_mode;
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_STEP_MODE, param_data );
    if ( POWERSTEP2_OK == error_flag )
    {
        ctx->step_mode = step_mode;
    }
    return error_flag;
}

err_t powerstep2_set_acc_dec ( powerstep2_t *ctx, float acc_step_s2, float dec_step_s2 )
{
    err_t error_flag = POWERSTEP2_OK;
    uint32_t param_data = 0;
    if ( ( acc_step_s2 > POWERSTEP2_ACCELERATION_MAX ) || ( acc_step_s2 < POWERSTEP2_ACCELERATION_MIN ) || 
         ( dec_step_s2 > POWERSTEP2_DECELERATION_MAX ) || ( dec_step_s2 < POWERSTEP2_DECELERATION_MIN ) )
    {
        return POWERSTEP2_ERROR;
    }
    param_data = ( uint32_t ) ( acc_step_s2 / POWERSTEP2_ACCELERATION_STEP + POWERSTEP2_ROUND_TO_INT );
    param_data &= POWERSTEP2_GEN_ACC_MASK;
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_ACC, param_data );
    param_data = ( uint32_t ) ( dec_step_s2 / POWERSTEP2_DECELERATION_STEP + POWERSTEP2_ROUND_TO_INT );
    param_data &= POWERSTEP2_GEN_DEC_MASK;
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_DEC, param_data );
    return error_flag;
}

err_t powerstep2_set_speed ( powerstep2_t *ctx, float min_speed, float max_speed )
{
    err_t error_flag = POWERSTEP2_OK;
    uint32_t param_data = 0;
    if ( ( min_speed > POWERSTEP2_MIN_SPEED_MAX ) || ( min_speed < POWERSTEP2_MIN_SPEED_MIN ) || 
         ( max_speed > POWERSTEP2_MAX_SPEED_MAX ) || ( max_speed < POWERSTEP2_MAX_SPEED_MIN ) )
    {
        return POWERSTEP2_ERROR;
    }
    error_flag |= powerstep2_soft_stop ( ctx );
    error_flag |= powerstep2_get_param ( ctx, POWERSTEP2_PARAM_GEN_MIN_SPEED, &param_data );
    param_data &= ( ~POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_MASK );
    if ( min_speed > POWERSTEP2_MIN_SPEED_MIN )
    {
        param_data |= ( ( ( uint32_t ) ( min_speed / POWERSTEP2_MIN_SPEED_STEP + POWERSTEP2_ROUND_TO_INT ) ) & 
                      POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_MASK );
    }
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_MIN_SPEED, param_data );
    param_data = ( uint32_t ) ( max_speed / POWERSTEP2_MAX_SPEED_STEP + POWERSTEP2_ROUND_TO_INT );
    param_data &= POWERSTEP2_GEN_MAX_SPEED_MASK;
    error_flag |= powerstep2_set_param ( ctx, POWERSTEP2_PARAM_GEN_MAX_SPEED, param_data );
    return error_flag;
}

void powerstep2_drive_motor ( powerstep2_t *ctx, uint32_t steps, uint8_t speed )
{
    while ( !powerstep2_get_busy_pin ( ctx ) );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        powerstep2_set_step_pin ( ctx, POWERSTEP2_PIN_HIGH_LEVEL );
        powerstep2_speed_delay ( ctx, speed );
        powerstep2_set_step_pin ( ctx, POWERSTEP2_PIN_LOW_LEVEL );
        powerstep2_speed_delay ( ctx, speed );
    }
}

static uint8_t powerstep2_get_param_len ( uint8_t param )
{
    uint8_t param_len = 1;
    switch ( param )
    {
        case POWERSTEP2_PARAM_GEN_ABS_POS:
        case POWERSTEP2_PARAM_GEN_MARK:
        case POWERSTEP2_PARAM_GEN_SPEED:
        {
            param_len = 3;
            break;
        }
        case POWERSTEP2_PARAM_GEN_EL_POS:
        case POWERSTEP2_PARAM_GEN_ACC:
        case POWERSTEP2_PARAM_GEN_DEC:
        case POWERSTEP2_PARAM_GEN_MAX_SPEED:
        case POWERSTEP2_PARAM_GEN_MIN_SPEED:
        case POWERSTEP2_PARAM_GEN_FS_SPD:
        case POWERSTEP2_PARAM_V_INT_SPEED:
        case POWERSTEP2_PARAM_GEN_GATECFG1:
        case POWERSTEP2_PARAM_V_CONFIG:
        case POWERSTEP2_PARAM_GEN_STATUS:
        {
            param_len = 2;
            break;
        }
        default:
        {
            break;
        }
    }
    return param_len;
}

static void powerstep2_speed_delay ( powerstep2_t *ctx, uint8_t speed_macro )
{
    uint32_t num_delay_10us = 0;
    if ( POWERSTEP2_CONTROL_MODE_CURRENT == ctx->control_mode )
    {
        num_delay_10us = 180;
        num_delay_10us /= ( 1 << ctx->step_mode );
        num_delay_10us = ( num_delay_10us / 3 ) + ( ( num_delay_10us - num_delay_10us / 3 ) / ( speed_macro + 1 ) );  
    }
    else
    {
        num_delay_10us = 10000;
        num_delay_10us /= ( 1 << ctx->step_mode );
        num_delay_10us /= ( 1 << speed_macro );
    }
    while ( num_delay_10us-- )
    {
        Delay_10us ( );
    }
}

// ------------------------------------------------------------------------- END

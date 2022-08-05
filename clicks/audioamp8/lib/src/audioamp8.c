/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file audioamp8.c
 * @brief AudioAmp 8 Click Driver.
 */

#include "audioamp8.h"

/**
 * @brief AudioAmp 8 clear delay function.
 * @details This function performs a delay of 1 millisecond.
 * @return Nothing.
 * @note None.
 */
static void dev_clear_delay ( void );

/**
 * @brief AudioAmp 8 configuration delay function.
 * @details This function performs a delay of 100 millisecond.
 * @return Nothing.
 * @note None.
 */
static void dev_cfg_delay ( void );

void audioamp8_cfg_setup ( audioamp8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->mut = HAL_PIN_NC;
    cfg->ms0 = HAL_PIN_NC;
    cfg->ms1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AUDIOAMP8_SET_DEV_ADDR_0;
}

err_t audioamp8_init ( audioamp8_t *ctx, audioamp8_cfg_t *cfg ) 
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
  
    digital_out_init( &ctx->mut, cfg->mut );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->ms0, cfg->ms0 );
    digital_out_init( &ctx->ms1, cfg->ms1 );

    return I2C_MASTER_SUCCESS;
}

err_t audioamp8_default_cfg ( audioamp8_t *ctx ) 
{
    // Click default configuration.
    audioamp8_pwr_mon_cfg_t pwr_mode;
    audioamp8_pwr_mod_profile_cfg_t pm_profile;
    
    pwr_mode.manual_pm = AUDIOAMP8_SET_AUTO_PWR_MODE;
    pwr_mode.pm_man    = AUDIOAMP8_PM_MAN_1;
    pwr_mode.mthr_1to2 = AUDIOAMP8_SET_MTHR_1TO2_DEFAULT;
    pwr_mode.mthr_2to1 = AUDIOAMP8_SET_MTHR_2TO1_DEFAULT;
    pwr_mode.mthr_2to3 = AUDIOAMP8_SET_MTHR_2TO3_DEFAULT;
    pwr_mode.mthr_3to2 = AUDIOAMP8_SET_MTHR_3TO2_DEFAULT;
    audioamp8_set_config_power_mode( ctx, pwr_mode );
    dev_cfg_delay( );
    
    pm_profile.pm_profile = AUDIOAMP8_PM_PROFILE_3; 
    pm_profile.pm3_man_sh = AUDIOAMP8_SCHEME_C;
    pm_profile.pm2_man_sh = AUDIOAMP8_SCHEME_C;
    pm_profile.pm1_man_sh = AUDIOAMP8_SCHEME_C;
    audioamp8_set_config_power_mode_profile( ctx, pm_profile );
    dev_cfg_delay( );
    
    audioamp8_set_audio_in_mode( ctx, AUDIOAMP8_AUDIO_IN_MODE_0_20dB );
    dev_cfg_delay( );
    
    audioamp8_set_audio_in_mode_overwrite( ctx, AUDIOAMP8_AUDIO_IN_MODE_EXT_DISABLE );
    dev_cfg_delay( );
    
    audioamp8_set_soft_clp_ovc_prot_lat( ctx, AUDIOAMP8_SET_ENABLE, AUDIOAMP8_SET_DISABLE );
    dev_cfg_delay( );

    audioamp8_start_up( ctx );
    dev_cfg_delay( );
    
    return AUDIOAMP8_OK;
}

err_t audioamp8_generic_write ( audioamp8_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t audioamp8_generic_read ( audioamp8_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t audioamp8_start_up ( audioamp8_t *ctx ) 
{
    err_t err_flag = audioamp8_set_enable( ctx, AUDIOAMP8_SET_DISABLE );
    err_flag |= audioamp8_set_mute( ctx, AUDIOAMP8_SET_ENABLE );
    dev_cfg_delay( );

    err_flag |= audioamp8_set_enable( ctx, AUDIOAMP8_SET_ENABLE );
    dev_cfg_delay( );
    
    return err_flag;
}

err_t audioamp8_shut_down ( audioamp8_t *ctx ) 
{
    err_t err_flag = audioamp8_set_enable( ctx, AUDIOAMP8_SET_DISABLE );
    err_flag |= audioamp8_set_mute( ctx, AUDIOAMP8_SET_ENABLE );
    dev_cfg_delay( );
    
    return err_flag;
}

err_t audioamp8_set_mute ( audioamp8_t *ctx, uint8_t en_mute ) 
{
    if ( en_mute == AUDIOAMP8_SET_ENABLE )
    {
        digital_out_low( &ctx->mut );    
    }
    else
    {
        digital_out_high( &ctx->mut );
    }
    
    return AUDIOAMP8_OK;
}

err_t audioamp8_set_enable ( audioamp8_t *ctx, uint8_t dev_en ) 
{
    if ( dev_en == AUDIOAMP8_SET_ENABLE )
    {
        digital_out_low( &ctx->en );    
    }
    else
    {
        digital_out_high( &ctx->en );
    }
    
    return AUDIOAMP8_OK;
}

err_t audioamp8_btl_config ( audioamp8_t *ctx ) 
{
    digital_out_high( &ctx->ms0 );
    digital_out_low( &ctx->ms1 );
    
    return AUDIOAMP8_OK;
}

err_t audioamp8_set_config_power_mode ( audioamp8_t *ctx, audioamp8_pwr_mon_cfg_t pwr_mode ) 
{
    uint8_t tx_buf;
    
    tx_buf  = ( pwr_mode.manual_pm & 0x01 ) << 6;
    tx_buf |= ( pwr_mode.pm_man    & 0x03 ) << 4;
    tx_buf |= 0x0F;
    err_t err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_PWR_MODE_CTRL, &tx_buf, 1 );
    
    tx_buf  = pwr_mode.mthr_1to2;
    err_flag |= audioamp8_generic_write( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM12, &tx_buf, 1 );
    
    tx_buf  = pwr_mode.mthr_2to1;
    err_flag |= audioamp8_generic_write( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM21, &tx_buf, 1 );
    
    tx_buf  = pwr_mode.mthr_2to3;
    err_flag |= audioamp8_generic_write( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM23, &tx_buf, 1 );
    
    tx_buf  = pwr_mode.mthr_3to2;
    err_flag |= audioamp8_generic_write( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM32, &tx_buf, 1 );
    
    return err_flag;
}

err_t audioamp8_get_config_power_mode ( audioamp8_t *ctx, audioamp8_pwr_mon_cfg_t *pwr_mode ) 
{
    uint8_t rx_buf;
    
    err_t err_flag = audioamp8_generic_read( ctx, AUDIOAMP8_REG_PWR_MODE_CTRL, &rx_buf, 1 );
    pwr_mode->manual_pm = ( rx_buf >> 6 ) & 0x01;
    pwr_mode->pm_man    = ( rx_buf >> 4 ) & 0x03;
    
    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM12, &rx_buf, 1 );
    pwr_mode->mthr_1to2 = rx_buf;
    
    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM21, &rx_buf, 1 );
    pwr_mode->mthr_2to1 = rx_buf;
    
    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM23, &rx_buf, 1 );
    pwr_mode->mthr_2to3 = rx_buf;
    
    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_THSH_PWR_MODE_PM32, &rx_buf, 1 );
    pwr_mode->mthr_3to2 = rx_buf;
    
    return err_flag;
}

err_t audioamp8_set_soft_clp_ovc_prot_lat ( audioamp8_t *ctx, uint8_t lf_clamp_en, uint8_t ocp_latch_en ) 
{
    uint8_t tx_buf;    
    
    tx_buf  = ( lf_clamp_en  & 0x01 ) << 7;
    tx_buf |=   ocp_latch_en & 0x01;
    
    return audioamp8_generic_write( ctx, AUDIOAMP8_REG_SOFT_CLP_OVC_PROT_LAT, &tx_buf, 1 );
}

err_t audioamp8_set_config_power_mode_profile ( audioamp8_t *ctx, audioamp8_pwr_mod_profile_cfg_t pm_profile ) 
{
    uint8_t tx_buf;
    
    tx_buf  = pm_profile.pm_profile & 0x07;
    err_t err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_SEL_PWR_MODE_PROFILE, &tx_buf, 1 );
    
    tx_buf  = ( pm_profile.pm3_man_sh & 0x03 ) << 4;
    tx_buf |= ( pm_profile.pm2_man_sh & 0x03 ) << 2;
    tx_buf |=   pm_profile.pm1_man_sh & 0x03;
    err_flag |= audioamp8_generic_write( ctx, AUDIOAMP8_REG_PWR_MODE_PROFILE_CFG, &tx_buf, 1 );
    
    return err_flag;
}

err_t audioamp8_get_config_power_mode_profile ( audioamp8_t *ctx, audioamp8_pwr_mod_profile_cfg_t *pm_profile ) 
{
    uint8_t rx_buf;
    
    err_t err_flag = audioamp8_generic_read( ctx, AUDIOAMP8_REG_SEL_PWR_MODE_PROFILE, &rx_buf, 1 );
    pm_profile->pm_profile = rx_buf & 0x07;
    
    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_PWR_MODE_PROFILE_CFG, &rx_buf, 1 );
    pm_profile->pm3_man_sh = ( rx_buf >> 4 ) & 0x03;
    pm_profile->pm2_man_sh = ( rx_buf >> 2 ) & 0x03;
    pm_profile->pm1_man_sh =   rx_buf        & 0x03;
    
    return err_flag;
}

err_t audioamp8_clear_ovc_prot_latch ( audioamp8_t *ctx ) 
{
    uint8_t tx_buf;
    
    tx_buf = 0x1F;
    err_t err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_OVC_PROT_LAT_CLR, &tx_buf, 1 );    
    dev_clear_delay( );
    
    tx_buf |= 0x80;
    err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_OVC_PROT_LAT_CLR, &tx_buf, 1 );
    dev_clear_delay( );
    
    return err_flag; 
}

err_t audioamp8_set_audio_in_mode ( audioamp8_t *ctx, uint8_t audio_in_mode ) 
{
    uint8_t tx_buf;
    
    tx_buf = ( audio_in_mode & 0x01 ) << 5;

    return audioamp8_generic_write( ctx, AUDIOAMP8_REG_AUDIO_IN_MODE, &tx_buf, 1 ); 
}

err_t audioamp8_set_dc_protection ( audioamp8_t *ctx, uint8_t eh_dcshdn ) 
{
    uint8_t tx_buf;
    
    tx_buf = ( eh_dcshdn & 0x01 ) << 2;

    return audioamp8_generic_write( ctx, AUDIOAMP8_REG_DC_PROTECTION, &tx_buf, 1 ); 
}

err_t audioamp8_set_audio_in_mode_overwrite ( audioamp8_t *ctx, uint8_t audio_in_mode_ext ) 
{
    uint8_t tx_buf;
    
    tx_buf = ( audio_in_mode_ext & 0x01 ) << 5;

    return audioamp8_generic_write( ctx, AUDIOAMP8_REG_AUDIO_IN_MODE_OVERWRITE, &tx_buf, 1 ); 
}

err_t audioamp8_clear_error_handler ( audioamp8_t *ctx ) 
{
    uint8_t tx_buf= 0x30;
    
    tx_buf &= 0xFD;
    err_t err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_OVC_PROT_LAT_CLR, &tx_buf, 1 );    
    dev_clear_delay( );
    
    tx_buf |= 0x02;
    err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_OVC_PROT_LAT_CLR, &tx_buf, 1 );
    dev_clear_delay( );
    
    tx_buf &= 0xFD;
    err_flag = audioamp8_generic_write( ctx, AUDIOAMP8_REG_OVC_PROT_LAT_CLR, &tx_buf, 1 );    
    dev_clear_delay( );
    
    return err_flag; 
}

err_t audioamp8_channel_monitoring ( audioamp8_t *ctx, uint8_t mon_ch, audioamp8_monitor_channel_t *ch_mon ) 
{
    uint8_t rx_buf;
    uint8_t ch_tmp;
    
    ch_tmp = mon_ch & 0x01;
    
    if ( mon_ch == AUDIOAMP8_SET_MON_CH_1 )
    {
        ch_tmp = 0x04;    
    }
    
    err_t err_flag = audioamp8_generic_read( ctx, AUDIOAMP8_REG_MON_CH_0_FREQ_PWR_MODE + ch_tmp, &rx_buf, 1 );
    ch_mon->freq_mode = ( rx_buf >> 4 ) & 0x07;
    ch_mon->pwr_mode  =   rx_buf        & 0x03;
    
    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_MON_CH_0 + ch_tmp, &rx_buf, 1 );
    ch_mon->mute_mon  = ( rx_buf >> 5 ) & 0x01;
    ch_mon->vdd_mon   = ( rx_buf >> 4 ) & 0x01;
    ch_mon->pvdd_mon  = ( rx_buf >> 3 ) & 0x01;
    ch_mon->cfly2_mon = ( rx_buf >> 2 ) & 0x01;
    ch_mon->cfly1_mon = ( rx_buf >> 1 ) & 0x01;
    ch_mon->ovc_prot  =   rx_buf        & 0x01;

    err_flag |= audioamp8_generic_read( ctx, AUDIOAMP8_REG_MON_CH_0_MODUL_INDEX + ch_tmp, &rx_buf, 1 );
    ch_mon->modul_index_mon = rx_buf;
    
    return err_flag;
}

err_t audioamp8_monitor_msel ( audioamp8_t *ctx, uint8_t *msel ) 
{
    err_t err_flag = audioamp8_generic_read( ctx, AUDIOAMP8_REG_MONITOR_MSEL, msel, 1 );
    
    *msel &= 0x07;

    return err_flag;  
}

err_t audioamp8_err_status ( audioamp8_t *ctx, audioamp8_error_status_t *error_status ) 
{
    uint8_t rx_buf;
       
    err_t err_flag = audioamp8_generic_read( ctx, AUDIOAMP8_REG_ERROR, &rx_buf, 1 );
    error_status->fly_cap_ov_vtg   = ( rx_buf >> 7 ) & 0x01;
    error_status->ov_curr_prot     = ( rx_buf >> 6 ) & 0x01;
    error_status->pll_err          = ( rx_buf >> 5 ) & 0x01;
    error_status->pvdd_un_vtg_prot = ( rx_buf >> 4 ) & 0x01;
    error_status->ov_temp_wrg      = ( rx_buf >> 3 ) & 0x01;
    error_status->ov_temp_err      = ( rx_buf >> 2 ) & 0x01;
    error_status->imped_prot       = ( rx_buf >> 1 ) & 0x01;
    error_status->dc_prot          =   rx_buf        & 0x01;
    
    return err_flag;
}

static void dev_clear_delay ( void )
{
    Delay_1ms( );
}

static void dev_cfg_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

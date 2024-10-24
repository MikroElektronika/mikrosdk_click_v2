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
 * @file solidswitch6.c
 * @brief SolidSwitch 6 Click Driver.
 */

#include "solidswitch6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                        0x00
#define SPI_FRAME_READ_ROM_MASK      0xC0
#define SPI_FRAME_WRITE_MASK         0x00
#define SPI_FRAME_READ_MASK          0x40
#define SPI_FRAME_READ_CLEAR_MASK    0x80
#define SET_PARITY_BIT               0x01

void solidswitch6_cfg_setup ( solidswitch6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hwl  = HAL_PIN_NC;
    cfg->dgn  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t solidswitch6_init ( solidswitch6_t *ctx, solidswitch6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->hwl, cfg->hwl );
    digital_in_init( &ctx->dgn, cfg->dgn );
    ctx->vcc_sel = SOLIDSWITCH6_VCC_SEL_3V3;

    return SPI_MASTER_SUCCESS;
}

err_t solidswitch6_default_cfg ( solidswitch6_t *ctx ) 
{
    solidswitch6_unlock_write( ctx );
    Delay_100ms( );

    err_t err_flag = solidswitch6_frame_write( ctx, SOLIDSWITCH6_REG_CTRL_3, 
                                                    SOLIDSWITCH6_CTRL_3_GOTO_UNLOCK |
                                                    SOLIDSWITCH6_CTRL_3_WD_TRIG |
                                                    SOLIDSWITCH6_CTRL_3_PARITY_BITMASK );
    Delay_10ms( );

    solidswitch6_device_info_t device_info;
    err_flag = solidswitch6_get_device_info( ctx, &device_info );
    if ( ( SOLIDSWITCH6_ROM_PRODUCT_CODE_1 == device_info.pc1 ) && 
         ( SOLIDSWITCH6_ROM_PRODUCT_CODE_2 == device_info.pc2 ) &&
         ( SOLIDSWITCH6_ROM_PRODUCT_CODE_3 == device_info.pc3 ) && 
         ( SOLIDSWITCH6_ROM_PRODUCT_CODE_4 == device_info.pc4 ) )
    {
        solidswitch6_ctrl_t ctrl;
        ctrl.gostby = SOLIDSWITCH6_CTRL_1_GOSTBY_DIS;
        ctrl.en = SOLIDSWITCH6_CTRL_1_EN;
        ctrl.s_t_start = SOLIDSWITCH6_CTRL_1_S_T_START_DIS;
        ctrl.s_t_stop = SOLIDSWITCH6_CTRL_1_S_T_STOP_DIS;
        ctrl.s_t_cfg = SOLIDSWITCH6_CTRL_1_S_T_CFG_NO;
        ctrl.outctl = SOLIDSWITCH6_CTRL_1_OUTCTL_OFF;
        ctrl.bypassctl = SOLIDSWITCH6_CTRL_1_BYPASSCTL_OFF;
        ctrl.t_nom = SOLIDSWITCH6_CTRL_2_T_NOM_1SEC;
        ctrl.ovc_thr = SOLIDSWITCH6_CTRL_2_OVC_THR_90_MV;
        ctrl.hsht_thr = SOLIDSWITCH6_CTRL_2_HSHT_THR_160_MV;
        ctrl.vds_thr = SOLIDSWITCH6_CTRL_2_VDS_THR_0_3_V;
        ctrl.unlock = SOLIDSWITCH6_CTRL_3_UNLOCK_EN;
        ctrl.ntc_thr = SOLIDSWITCH6_CTRL_3_NTC_THR_37_5;
        ctrl.wd_time = SOLIDSWITCH6_CTRL_3_WD_TIME_50_MS;
        ctrl.dis_out_mode = SOLIDSWITCH6_CTRL_3_DIS_OUT_MODE_DIS;
        ctrl.wd_trig = SOLIDSWITCH6_CTRL_3_WD_TRI_EN;
        err_flag |= solidswitch6_set_control( ctx, ctrl );
    }
    else
    {
        err_flag = SOLIDSWITCH6_ERROR;
    }
    return err_flag;
}

err_t solidswitch6_generic_write ( solidswitch6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t solidswitch6_generic_read ( solidswitch6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t solidswitch6_frame_write ( solidswitch6_t *ctx, uint8_t reg, uint32_t data_in ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 16 );
    data_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 2 ] = ( uint8_t ) ( data_in | SET_PARITY_BIT );
    reg |= SPI_FRAME_WRITE_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, reg );
    err_flag |= spi_master_read( &ctx->spi, &ctx->global_status, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t solidswitch6_frame_read ( solidswitch6_t *ctx, uint8_t reg, uint32_t *data_out ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    reg |= SPI_FRAME_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, reg );
    err_flag |= spi_master_read( &ctx->spi, &ctx->global_status, 1 );
    err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 2 ];
    return err_flag;
}

err_t solidswitch6_frame_read_clear ( solidswitch6_t *ctx, uint8_t reg, uint32_t data_in, uint32_t *data_out ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    reg |= SPI_FRAME_READ_CLEAR_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, reg );
    err_flag |= spi_master_read( &ctx->spi, &ctx->global_status, 1 );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 2 ];
    return err_flag;
}

err_t solidswitch6_read_rom ( solidswitch6_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    reg |= SPI_FRAME_READ_ROM_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, reg );
    err_flag |= spi_master_read( &ctx->spi, &ctx->global_status, 1 );
    err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_flag |= spi_master_read( &ctx->spi, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t solidswitch6_get_global_status ( solidswitch6_t *ctx ) 
{   
    err_t err_flag = SOLIDSWITCH6_OK;
    if ( SOLIDSWITCH6_GS_GSBN_BIT & ctx->global_status )
    {
        err_flag = SOLIDSWITCH6_ERROR;
    }
    return err_flag;
}

err_t solidswitch6_get_device_info ( solidswitch6_t *ctx, solidswitch6_device_info_t *device_info ) 
{
    err_t err_flag = solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_CCODE, 
                                                 &device_info->co_code );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_DEVF, 
                                            &device_info->d_family );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_PR_CODE_1, 
                                            &device_info->pc1 );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_PR_CODE_2, 
                                            &device_info->pc2 );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_PR_CODE_3, 
                                            &device_info->pc3 );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_PR_CODE_4, 
                                            &device_info->pc4 );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_SIL_VER, 
                                            &device_info->sil_ver );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_SPI_MODE, 
                                            &device_info->spi_mode );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_WD_TYPE, 
                                            &device_info->wd_type );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_WD_P1, 
                                            &device_info->wd_bp1 );
    Delay_1ms( );

    err_flag |= solidswitch6_read_rom( ctx, SOLIDSWITCH6_REG_ROM_WD_P2, 
                                            &device_info->wd_bp2 );
    Delay_1ms( );

    return err_flag;
}

void solidswitch6_lock_write ( solidswitch6_t *ctx ) 
{
    digital_out_high( &ctx->hwl );
}

void solidswitch6_unlock_write ( solidswitch6_t *ctx ) 
{
    digital_out_low( &ctx->hwl );
}

err_t solidswitch6_set_control ( solidswitch6_t *ctx, solidswitch6_ctrl_t ctrl ) 
{
    uint32_t data_buf = SET_PARITY_BIT;
    data_buf |= ( ( uint32_t ) ( ctrl.gostby    & 0x01 ) ) << 11;
    data_buf |= ( ( uint32_t ) ( ctrl.en        & 0x01 ) ) << 10;
    data_buf |= ( ( uint32_t ) ( ctrl.s_t_start & 0x01 ) ) << 9;
    data_buf |= ( ( uint32_t ) ( ctrl.s_t_stop  & 0x01 ) ) << 8;
    data_buf |= ( ( uint32_t ) ( ctrl.s_t_cfg   & 0x07 ) ) << 5;
    data_buf |= ( ( uint32_t ) ( ctrl.outctl    & 0x01 ) ) << 4;
    data_buf |= ( ( uint32_t ) ( ctrl.bypassctl & 0x01 ) ) << 3;
    data_buf |= ( ( uint32_t ) ( ctrl.wd_trig   & 0x01 ) ) << 1;
    err_t err_flag = solidswitch6_frame_write( ctx, SOLIDSWITCH6_REG_CTRL_1, data_buf );

    data_buf |= ( ( uint32_t ) ( ctrl.t_nom        & 0xFF ) ) << 16;
    data_buf |= ( ( uint32_t ) ( ctrl.ntc_thr      & 0x0F ) ) << 5;
    data_buf |= ( ( uint32_t ) ( ctrl.wd_time      & 0x03 ) ) << 3;
    data_buf |= ( ( uint32_t ) ( ctrl.dis_out_mode & 0x01 ) ) << 2;
    data_buf |= ( ( uint32_t ) ( ctrl.wd_trig      & 0x01 ) ) << 1;
    err_flag |= solidswitch6_frame_write( ctx, SOLIDSWITCH6_REG_CTRL_2, data_buf );
    Delay_1ms( );

    data_buf = SET_PARITY_BIT;
    data_buf |= ( ( uint32_t ) ( ctrl.unlock       & 0x01 ) ) << 9;
    data_buf |= ( ( uint32_t ) ( ctrl.ntc_thr      & 0x0F ) ) << 5;
    data_buf |= ( ( uint32_t ) ( ctrl.wd_time      & 0x03 ) ) << 3;
    data_buf |= ( ( uint32_t ) ( ctrl.dis_out_mode & 0x01 ) ) << 2;
    data_buf |= ( ( uint32_t ) ( ctrl.wd_trig      & 0x01 ) ) << 1;
    err_flag |= solidswitch6_frame_write( ctx, SOLIDSWITCH6_REG_CTRL_3, data_buf );
    Delay_1ms( );
    
    return err_flag;
}

err_t solidswitch6_get_vsense ( solidswitch6_t *ctx, float *vsense ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_2, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 2;
    adc_buf &= SOLIDSWITCH6_CURR_SENSE_RES;
    *vsense = ( float ) adc_buf;
    *vsense *= SOLIDSWITCH6_CURR_SENSE_RANGE_MV;
    *vsense /= ( float ) SOLIDSWITCH6_CURR_SENSE_RES;
    return err_flag;
}

err_t solidswitch6_get_device_temp ( solidswitch6_t *ctx, float *tj ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_3, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 13;
    adc_buf &= SOLIDSWITCH6_TJ_RES;
    *tj = ( float ) adc_buf;
    *tj *= SOLIDSWITCH6_TJ_RANGE;
    *tj /= ( float ) SOLIDSWITCH6_TJ_RES;
    *tj += SOLIDSWITCH6_TJ_TEMP_MIN;
    return err_flag;
}

err_t solidswitch6_get_vntc ( solidswitch6_t *ctx, float *vntc ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_3, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 2;
    adc_buf &= SOLIDSWITCH6_TJ_RES;

    *vntc = ( float ) adc_buf;
    if ( SOLIDSWITCH6_VCC_SEL_3V3 == ctx->vcc_sel )
    {
        *vntc *= SOLIDSWITCH6_VNTC_RANGE_3V3;
        *vntc /= ( float ) SOLIDSWITCH6_VNTC_RES;
        *vntc += SOLIDSWITCH6_VNTC_MIN_3V3;
    }
    else
    {
        *vntc *= SOLIDSWITCH6_VNTC_RANGE_5V;
        *vntc /= ( float ) SOLIDSWITCH6_VNTC_RES;
        *vntc += SOLIDSWITCH6_VNTC_MIN_5V;
    }
    return err_flag;
}

err_t solidswitch6_get_vds ( solidswitch6_t *ctx, float *vds ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_4, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 13;
    adc_buf &= SOLIDSWITCH6_VDS_RES;
    *vds = ( float ) adc_buf;
    *vds *= SOLIDSWITCH6_VDS_RANGE_MV;
    *vds /= ( float ) SOLIDSWITCH6_VDS_RES;
    *vds += SOLIDSWITCH6_VDS_MIN_MV;
    *vds /= SOLIDSWITCH6_VDS_CONVERT_TO_V;
    return err_flag;
}

err_t solidswitch6_get_vout ( solidswitch6_t *ctx, float *vout ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_4, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 2;
    adc_buf &= SOLIDSWITCH6_VOUT_RES;
    *vout = ( float ) adc_buf;
    *vout *= SOLIDSWITCH6_VOUT_RANGE;
    *vout /= ( float ) SOLIDSWITCH6_VOUT_RES;
    return err_flag;
}

err_t solidswitch6_get_st_vds ( solidswitch6_t *ctx, float *st_vds ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_5, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 3;
    adc_buf &= SOLIDSWITCH6_S_T_VDS_RES;
    *st_vds = ( float ) adc_buf;
    *st_vds *= SOLIDSWITCH6_S_T_VDS_RANGE_MV;
    *st_vds /= ( float ) SOLIDSWITCH6_S_T_VDS_RES;
    *st_vds += SOLIDSWITCH6_S_T_VDS_MIN_START;
    return err_flag;
}

err_t solidswitch6_get_st_stuck ( solidswitch6_t *ctx, float *st_stuck ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_6, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 3;
    adc_buf &= SOLIDSWITCH6_S_T_STUCK_RES;
    *st_stuck = ( float ) adc_buf;
    *st_stuck *= SOLIDSWITCH6_S_T_STUCK_RANGE_MV;
    *st_stuck /= ( float ) SOLIDSWITCH6_S_T_STUCK_RES;
    *st_stuck += SOLIDSWITCH6_S_T_STUCK_MIN_MIN;
    return err_flag;
}

err_t solidswitch6_get_st_curr ( solidswitch6_t *ctx, float *st_curr ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_7, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 3;
    adc_buf &= SOLIDSWITCH6_S_T_CURR_RES;
    *st_curr = ( float ) adc_buf;
    *st_curr *= SOLIDSWITCH6_S_T_CURR_RANGE_MV;
    *st_curr /= ( float ) SOLIDSWITCH6_S_T_CURR_RES;
    return err_flag;
}

err_t solidswitch6_get_vsense_hshd ( solidswitch6_t *ctx, float *vsense_hshd ) 
{
    uint32_t adc_buf = DUMMY;
    err_t err_flag = solidswitch6_frame_read( ctx, SOLIDSWITCH6_REG_STATUS_8, &adc_buf );
    err_flag |= solidswitch6_get_global_status( ctx );
    adc_buf >>= 2;
    adc_buf &= SOLIDSWITCH6_HSHT_SAR_RES;
    *vsense_hshd = ( float ) adc_buf;
    *vsense_hshd *= SOLIDSWITCH6_HSHT_SAR_RANGE_MV;
    *vsense_hshd /= ( float ) SOLIDSWITCH6_HSHT_SAR_RES;
    return err_flag;
}

uint8_t solidswitch6_get_diag ( solidswitch6_t *ctx ) 
{   
    return digital_in_read( &ctx->dgn );
}

// ------------------------------------------------------------------------- END

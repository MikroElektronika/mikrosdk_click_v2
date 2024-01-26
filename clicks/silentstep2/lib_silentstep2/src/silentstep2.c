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
 * @file silentstep2.c
 * @brief Silent Step 2 Click Driver.
 */

#include "silentstep2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief SPI write/read bit masks.
 * @details Definition of SPI write/read bit masks.
 */
#define SPI_WRITE_MASK    0x80
#define SPI_READ_MASK     0x7F

/**
 * @brief Silent Step 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t silentstep2_i2c_write ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Silent Step 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t silentstep2_i2c_read ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Silent Step 2 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t silentstep2_spi_write ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Silent Step 2 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t silentstep2_spi_read ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Silent Step 2 step delay function.
 * @details This function sets the defined delay value.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void silentstep2_step_delay ( silentstep2_t *ctx );

void silentstep2_cfg_setup ( silentstep2_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->stp  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SILENTSTEP2_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->step_delay = SILENTSTEP2_STEP_DELAY_DEFAULT_100US;
}

err_t silentstep2_init ( silentstep2_t *ctx, silentstep2_cfg_t *cfg ) 
{
    ctx->step_delay = cfg->step_delay;
    
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

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->stp, cfg->stp );

    digital_in_init( &ctx->int_pin, cfg->int_pin );  

    return SILENTSTEP2_OK;
}

err_t silentstep2_default_cfg ( silentstep2_t *ctx ) 
{
    err_t err_flag = silentstep2_port_exp_write( ctx, SILENTSTEP2_REG_EXP_CONFIG, 
                                                      SILENTSTEP2_PIN_FT1 | 
                                                      SILENTSTEP2_PIN_FT2 );
    Delay_10ms( );
    
    err_flag |= silentstep2_switch_off( ctx );
    Delay_100ms( );
    
    uint32_t gstat = DUMMY;
    err_flag |= silentstep2_get_gstat( ctx, &gstat );
    Delay_10ms( );
    
    if ( ( SILENTSTEP2_GSTAT_RESET != gstat )   && 
         ( SILENTSTEP2_GSTAT_DRV_ERR != gstat ) && 
         ( SILENTSTEP2_GSTAT_UV_CP != gstat ) )
    {
        silentstep2_gconf_t gconf;
        gconf.i_scale_analog = SILENTSTEP2_GCONF_I_SC_AN_AIN;
        gconf.internal_rsense = SILENTSTEP2_GCONF_INT_RSE_OP_NORMAL;
        gconf.en_pwm_mode = SILENTSTEP2_GCONF_DISABLE;
        gconf.enc_commutation = SILENTSTEP2_GCONF_DISABLE;
        gconf.shaft = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag0_error = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag0_otpw = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag0_stall = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag1_stall = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag1_index = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag1_onstate = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag1_steps_skipped = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag0_int_pushpull = SILENTSTEP2_GCONF_DISABLE;
        gconf.diag1_pushpull = SILENTSTEP2_GCONF_DISABLE;
        gconf.small_hysteresis = SILENTSTEP2_GCONF_DISABLE;
        gconf.stop_enable = SILENTSTEP2_GCONF_DISABLE;
        gconf.direct_mode = SILENTSTEP2_GCONF_DISABLE;
        err_flag |= silentstep2_set_gconf( ctx, gconf );
        Delay_10ms( );
        
        silentstep2_set_tcoolthrs( ctx, SILENTSTEP2_TCOOLTHRS_DEFAULT );
        Delay_10ms( );
        
        err_flag |= silentstep2_set_thigh( ctx, SILENTSTEP2_THIGH_DEFAULT );
        Delay_10ms( );
        
        silentstep2_coolconf_t coolconf;
        coolconf.semin = SILENTSTEP2_CHOPCONF_SEMIN_0;
        coolconf.seup = SILENTSTEP2_CHOPCONF_SEUP_1;
        coolconf.semax = SILENTSTEP2_CHOPCONF_SEMAX_0;
        coolconf.sedn = SILENTSTEP2_CHOPCONF_SEDN_32;
        coolconf.seimin = SILENTSTEP2_CHOPCONF_SEIMIN_1_2;
        coolconf.sgt = SILENTSTEP2_CHOPCONF_SGT_M64;
        coolconf.sfilt = SILENTSTEP2_CHOPCONF_SFILT_MODE_FLTR;
        err_flag |= silentstep2_set_coolconf( ctx, coolconf );
        Delay_10ms( );
        
        err_flag |= silentstep2_set_ihold_irun( ctx, SILENTSTEP2_IHOLD_10_32, 
                                                     SILENTSTEP2_IRUN_10_32, 
                                                     SILENTSTEP2_IHOLDDELAY_32 );
        Delay_10ms( );
        
        silentstep2_set_toff( ctx, SILENTSTEP2_TOFF_NCLK_140 );
        Delay_10ms( );
        
        err_flag |= silentstep2_set_h_end_strt( ctx, SILENTSTEP2_CHOPCONF_CHM_MODE_STND, 
                                                     SILENTSTEP2_CHOPCONF_HE_OS_M3, 
                                                     SILENTSTEP2_CHOPCONF_HSTRT_TFD_4 );
        Delay_10ms( );
        
        err_flag |= silentstep2_set_mstep_res( ctx, SILENTSTEP2_MRES_NATIVE );
        Delay_100ms( );
        Delay_100ms( );
        
        err_flag |= silentstep2_input_enable( ctx );
        Delay_100ms( );
    }
    else
    {
        err_flag = SILENTSTEP2_ERROR;
    }

    return err_flag;
}

err_t silentstep2_reg_write ( silentstep2_t *ctx, uint8_t reg, uint32_t data_in ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    reg |= SPI_WRITE_MASK;
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 24 );
    data_buf[ 1 ] = ( uint8_t ) ( data_in >> 16 );
    data_buf[ 2 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 3 ] = ( uint8_t )   data_in;
    return silentstep2_spi_write( ctx, reg, data_buf, 4 );
}

err_t silentstep2_reg_read ( silentstep2_t *ctx, uint8_t reg, uint32_t *data_in ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    reg &= SPI_READ_MASK;
    err_t err_flag = silentstep2_spi_read( ctx, reg, data_buf, 4 );
    Delay_1ms( );
    err_flag |= silentstep2_spi_read( ctx, reg, data_buf, 4 );
    *data_in = data_buf[ 0 ];
    *data_in <<= 8;
    *data_in |= data_buf[ 1 ];
    *data_in <<= 8;
    *data_in |= data_buf[ 2 ];
    *data_in <<= 8;
    *data_in |= data_buf[ 3 ];
    return err_flag;
}

err_t silentstep2_set_gconf ( silentstep2_t *ctx, silentstep2_gconf_t gconf ) 
{
    uint32_t data_buf = DUMMY;
    data_buf =    ( uint32_t ) ( gconf.i_scale_analog      & 0x01 );
    data_buf |= ( ( uint32_t ) ( gconf.internal_rsense     & 0x01 ) ) << 1;
    data_buf |= ( ( uint32_t ) ( gconf.en_pwm_mode         & 0x01 ) ) << 2;
    data_buf |= ( ( uint32_t ) ( gconf.enc_commutation     & 0x01 ) ) << 3;
    data_buf |= ( ( uint32_t ) ( gconf.shaft               & 0x01 ) ) << 4;
    data_buf |= ( ( uint32_t ) ( gconf.diag0_error         & 0x01 ) ) << 5;
    data_buf |= ( ( uint32_t ) ( gconf.diag0_otpw          & 0x01 ) ) << 6;
    data_buf |= ( ( uint32_t ) ( gconf.diag0_stall         & 0x01 ) ) << 7;
    data_buf |= ( ( uint32_t ) ( gconf.diag1_stall         & 0x01 ) ) << 8;
    data_buf |= ( ( uint32_t ) ( gconf.diag1_index         & 0x01 ) ) << 9;
    data_buf |= ( ( uint32_t ) ( gconf.diag1_onstate       & 0x01 ) ) << 10;
    data_buf |= ( ( uint32_t ) ( gconf.diag1_steps_skipped & 0x01 ) ) << 11;
    data_buf |= ( ( uint32_t ) ( gconf.diag0_int_pushpull  & 0x01 ) ) << 12;
    data_buf |= ( ( uint32_t ) ( gconf.diag1_pushpull      & 0x01 ) ) << 13;
    data_buf |= ( ( uint32_t ) ( gconf.small_hysteresis    & 0x01 ) ) << 14;
    data_buf |= ( ( uint32_t ) ( gconf.stop_enable         & 0x01 ) ) << 15;
    data_buf |= ( ( uint32_t ) ( gconf.direct_mode         & 0x01 ) ) << 16;
    return silentstep2_reg_write( ctx, SILENTSTEP2_REG_GCONF, data_buf );
}

err_t silentstep2_get_gstat ( silentstep2_t *ctx, uint32_t *gstat ) 
{
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_GSTAT, gstat );
    *gstat &= SILENTSTEP2_GSTAT_RESET | SILENTSTEP2_GSTAT_DRV_ERR | SILENTSTEP2_GSTAT_UV_CP;
    return err_flag;
}

err_t silentstep2_set_ihold_irun ( silentstep2_t *ctx, uint8_t ihold, uint8_t irun, uint8_t ihold_delay ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( ( SILENTSTEP2_IHOLD_BIT_MASK >= ihold ) || 
         ( SILENTSTEP2_IRUN_BIT_MASK >= irun )   || 
         ( SILENTSTEP2_IHOLDDELAY_BIT_MASK >= ihold_delay ) )
    {
        uint32_t data_buf = DUMMY;
        data_buf = ( ( uint32_t ) ihold & SILENTSTEP2_IHOLD_BIT_MASK ) << 0;
        data_buf |= ( ( uint32_t ) irun & SILENTSTEP2_IRUN_BIT_MASK ) << 8;
        data_buf |= ( ( uint32_t ) ihold_delay & SILENTSTEP2_IHOLDDELAY_BIT_MASK ) << 16;
        err_flag = silentstep2_reg_write( ctx, SILENTSTEP2_REG_IHOLD_IRUN, data_buf );
    }
    return err_flag;
}

err_t silentstep2_set_tcoolthrs ( silentstep2_t *ctx, uint32_t tcoolthrs ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( SILENTSTEP2_TCOOLTHRS_MAX >= tcoolthrs )
    {
        err_flag = silentstep2_reg_write( ctx, SILENTSTEP2_REG_TCOOLTHRS, tcoolthrs );
    }  
    return err_flag;
}

err_t silentstep2_set_thigh ( silentstep2_t *ctx, uint32_t thigh ) 
{
    uint32_t tstep = DUMMY;
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_TSTEP, &tstep );
    if ( ( SILENTSTEP2_THIGH_MAX < thigh ) || ( tstep <= thigh ) )
    {
        err_flag = SILENTSTEP2_ERROR;
    }
    else
    {
        err_flag = silentstep2_reg_write( ctx, SILENTSTEP2_REG_THIGH, thigh );
    }
    return err_flag;
}

err_t silentstep2_set_mslut ( silentstep2_t *ctx, uint8_t mslut_num, uint32_t mslut ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( SILENTSTEP2_MSLUT_SEL_7 >= mslut_num )
    {
        err_flag = silentstep2_reg_write( ctx, SILENTSTEP2_REG_MSLUT0 | mslut_num, mslut );
    }
    return err_flag;
}

err_t silentstep2_set_mslutsel ( silentstep2_t *ctx, uint32_t lut_seg_str, uint32_t lut_width_sel ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( ( SILENTSTEP2_MSLUTSEL_SEG_BIT_MASK >= lut_seg_str ) && 
         ( SILENTSTEP2_MSLUTSEL_WIDTH_BIT_MASK >= lut_width_sel ) )
    {
        uint32_t data_buf = DUMMY;
        data_buf = lut_seg_str << 8;
        data_buf |= lut_width_sel;
        err_flag = silentstep2_reg_write( ctx, SILENTSTEP2_REG_MSLUTSEL, data_buf );
    }
    return err_flag;
}

err_t silentstep2_set_mslutstart ( silentstep2_t *ctx, uint32_t start_sin, uint32_t start_sin90 ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( ( SILENTSTEP2_MSLUTSTART_SIN_BIT_MASK >= start_sin ) && 
         ( SILENTSTEP2_MSLUTSTART_SIN90_BIT_MASK >= start_sin90 ) )
    {
        uint32_t data_buf = DUMMY;
        data_buf = start_sin90 << 16;
        data_buf |= start_sin;
        err_flag = silentstep2_reg_write( ctx, SILENTSTEP2_REG_MSLUTSTART, data_buf );
    }
    return err_flag;
}

err_t silentstep2_set_mstep_res ( silentstep2_t *ctx, silentstep2_mres_t step_width ) 
{
    uint32_t data_buf = DUMMY;
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_CHOPCONF, &data_buf );
    data_buf &= SILENTSTEP2_CHOPCONF_MRES_BIT_MASK;
    data_buf |= ( ( uint32_t ) step_width ) << 24;
    err_flag |= silentstep2_reg_write( ctx, SILENTSTEP2_REG_CHOPCONF, data_buf );
    return err_flag;
}

err_t silentstep2_set_dedge ( silentstep2_t *ctx, uint8_t dedge_en ) 
{
    uint32_t data_buf = DUMMY;
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_CHOPCONF, &data_buf );
    data_buf &= SILENTSTEP2_CHOPCONF_DEDGE_BIT_MASK;
    data_buf |= ( ( uint32_t ) ( dedge_en & 0x01 ) ) << 29;
    err_flag |= silentstep2_reg_write( ctx, SILENTSTEP2_REG_CHOPCONF, data_buf );
    return err_flag;
}

err_t silentstep2_set_intpol ( silentstep2_t *ctx, uint8_t intpol_en ) 
{
    uint32_t data_buf = DUMMY;
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_CHOPCONF, &data_buf );
    data_buf &= SILENTSTEP2_CHOPCONF_INTPOL_BIT_MASK;
    data_buf |= ( ( uint32_t ) ( intpol_en & 0x01 ) ) << 28;
    err_flag |= silentstep2_reg_write( ctx, SILENTSTEP2_REG_CHOPCONF, data_buf );
    return err_flag;
}

err_t silentstep2_set_tbl_blank_time ( silentstep2_t *ctx, silentstep2_tbl_t tbl ) 
{
    uint32_t data_buf = DUMMY;
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_CHOPCONF, &data_buf );
    data_buf &= SILENTSTEP2_CHOPCONF_TBL_BIT_MASK;
    data_buf |= ( ( uint32_t ) tbl ) << 15;
    err_flag |= silentstep2_reg_write( ctx, SILENTSTEP2_REG_CHOPCONF, data_buf );
    return err_flag;
}

err_t silentstep2_set_h_end_strt ( silentstep2_t *ctx, uint8_t chm, uint8_t h_end_offset, uint8_t hstrt_tfd ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( ( SILENTSTEP2_CHOPCONF_CHM_CONST_OFF_TIME >= chm ) && 
        ( SILENTSTEP2_CHOPCONF_HE_OS_12 >= h_end_offset )   && 
        ( SILENTSTEP2_CHOPCONF_HSTRT_TFD_7 >= hstrt_tfd ) )
    {
        uint32_t data_buf = DUMMY;
        err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_CHOPCONF, &data_buf );
        data_buf &= ~SILENTSTEP2_CHOPCONF_CHM_BIT_MASK;
        data_buf &= ~SILENTSTEP2_CHOPCONF_HE_OS_BIT_MASK;
        data_buf &= ~SILENTSTEP2_CHOPCONF_HSTRT_TFD_BIT_MASK;
        data_buf |= ( ( uint32_t ) chm ) << 14;
        data_buf |= ( ( uint32_t ) h_end_offset ) << 7;
        data_buf |= ( ( uint32_t ) hstrt_tfd ) << 4;
        err_flag |= silentstep2_reg_write( ctx, SILENTSTEP2_REG_CHOPCONF, data_buf );
    }
    return err_flag;
}

err_t silentstep2_set_toff ( silentstep2_t *ctx, uint8_t off_time ) 
{
    err_t err_flag = SILENTSTEP2_ERROR;
    if ( SILENTSTEP2_TOFF_BIT_MASK >= off_time )
    {
        uint32_t data_buf = DUMMY;
        err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_CHOPCONF, &data_buf );
        data_buf &= SILENTSTEP2_CHOPCONF_TOFF_BIT_MASK;
        data_buf |= ( uint32_t ) off_time;
        err_flag |= silentstep2_reg_write( ctx, SILENTSTEP2_REG_CHOPCONF, data_buf );
    }
    return err_flag;
}

err_t silentstep2_set_coolconf ( silentstep2_t *ctx, silentstep2_coolconf_t coolconf ) 
{
    uint32_t data_buf = DUMMY;
    data_buf =      ( uint32_t ) ( coolconf.semin  & 0x0F );
    data_buf |= ( ( ( uint32_t ) ( coolconf.seup   & 0x03 ) ) << 5 );
    data_buf |= ( ( ( uint32_t ) ( coolconf.semax  & 0x0F ) ) << 8 );
    data_buf |= ( ( ( uint32_t ) ( coolconf.sedn   & 0x03 ) ) << 13 );
    data_buf |= ( ( ( uint32_t ) ( coolconf.seimin & 0x01 ) ) << 15 );
    data_buf |= ( ( ( uint32_t ) ( coolconf.sgt    & 0x7F ) ) << 16 );
    data_buf |= ( ( ( uint32_t ) ( coolconf.sfilt  & 0x01 ) ) << 24 );
    return silentstep2_reg_write( ctx, SILENTSTEP2_REG_COOLCONF, data_buf );
}

err_t silentstep2_set_pwmconf ( silentstep2_t *ctx, silentstep2_pwmconf_t pwmconf ) 
{
    uint32_t data_buf = DUMMY;
    data_buf =    ( uint32_t ) pwmconf.pwm_ampl;
    data_buf |= ( ( uint32_t ) pwmconf.pwm_grad )                 << 8;
    data_buf |= ( ( uint32_t ) ( pwmconf.pwm_freq      & 0x03 ) ) << 16;
    data_buf |= ( ( uint32_t ) ( pwmconf.pwm_autoscale & 0x01 ) ) << 18;
    data_buf |= ( ( uint32_t ) ( pwmconf.pwm_symmetric & 0x01 ) ) << 19;
    data_buf |= ( ( uint32_t ) ( pwmconf.freewheel     & 0x03 ) ) << 20;
    return silentstep2_reg_write( ctx, SILENTSTEP2_REG_PWMCONF, data_buf );
}

err_t silentstep2_get_drv_status ( silentstep2_t *ctx, silentstep2_drv_status_t *drv_status ) 
{
    uint32_t data_buf = DUMMY;
    err_t err_flag = silentstep2_reg_read( ctx, SILENTSTEP2_REG_DRV_STATUS, &data_buf );
    drv_status->sg_result   = ( uint16_t ) ( data_buf & 0x03FF );
    drv_status->fsactive    = ( ( uint8_t ) ( data_buf >> 15 ) ) & 0x01;
    drv_status->cs_actual   = ( ( uint8_t ) ( data_buf >> 16 ) ) & 0x1F;
    drv_status->stall_guard = ( ( uint8_t ) ( data_buf >> 24 ) ) & 0x01;
    drv_status->ot          = ( ( uint8_t ) ( data_buf >> 25 ) ) & 0x01;
    drv_status->otpw        = ( ( uint8_t ) ( data_buf >> 26 ) ) & 0x01;
    drv_status->s2ga        = ( ( uint8_t ) ( data_buf >> 27 ) ) & 0x01;
    drv_status->s2gb        = ( ( uint8_t ) ( data_buf >> 28 ) ) & 0x01;
    drv_status->ola         = ( ( uint8_t ) ( data_buf >> 29 ) ) & 0x01;
    drv_status->olb         = ( ( uint8_t ) ( data_buf >> 30 ) ) & 0x01;
    drv_status->stst        = ( ( uint8_t ) ( data_buf >> 31 ) ) & 0x01;
    return err_flag;
}

err_t silentstep2_port_exp_write ( silentstep2_t *ctx, uint8_t reg, uint8_t data_in )
{
    return silentstep2_i2c_write( ctx, reg, &data_in, 1 );
}

err_t silentstep2_port_exp_read ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return silentstep2_i2c_read( ctx, reg, data_out, 1 );
}

err_t silentstep2_set_pins ( silentstep2_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in = DUMMY;
    uint8_t data_out = DUMMY;
    err_t err_flag = silentstep2_port_exp_read( ctx, SILENTSTEP2_REG_EXP_OUT_PORT, &data_out );
   
    data_in = ( data_out & ~clr_mask ) | set_mask;
    
    if ( data_out != data_in )
    {
        err_flag |= silentstep2_port_exp_write( ctx, SILENTSTEP2_REG_EXP_OUT_PORT, data_in );
    }
    return err_flag;
}

err_t silentstep2_get_diag0 ( silentstep2_t *ctx, uint8_t *diag0 )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = silentstep2_port_exp_read( ctx, SILENTSTEP2_REG_EXP_IN_PORT, diag0 );
    *diag0 &= SILENTSTEP2_PIN_FT1;
    return err_flag;
}

err_t silentstep2_get_diag1 ( silentstep2_t *ctx, uint8_t *diag1 )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = silentstep2_port_exp_read( ctx, SILENTSTEP2_REG_EXP_IN_PORT, diag1 );
    *diag1 &= SILENTSTEP2_PIN_FT2;
    return err_flag;
}

err_t silentstep2_switch_off ( silentstep2_t *ctx )
{
    return silentstep2_set_pins( ctx, SILENTSTEP2_PIN_EN, SILENTSTEP2_PIN_NONE );
}

err_t silentstep2_input_enable ( silentstep2_t *ctx )
{    
    return silentstep2_set_pins( ctx, SILENTSTEP2_PIN_NONE, SILENTSTEP2_PIN_EN );
}

void silentstep2_set_direction ( silentstep2_t *ctx, uint8_t dir )
{    
    digital_out_write( &ctx->dir, dir );
}

void silentstep2_set_step ( silentstep2_t *ctx, uint8_t step )
{    
    digital_out_write( &ctx->stp, step );
}

err_t silentstep2_make_one_step ( silentstep2_t *ctx, uint8_t step_speed ) 
{
    err_t err_flag = SILENTSTEP2_OK;
    
    if ( ( SILENTSTEP2_STEP_SPEED_MAX < step_speed ) || 
         ( SILENTSTEP2_STEP_SPEED_MIN > step_speed ) ) 
    {
        err_flag = SILENTSTEP2_ERROR;    
    } 
    else 
    {
        err_flag = SILENTSTEP2_OK;
        silentstep2_set_step( ctx, 1 );
        silentstep2_step_delay( ctx );
        
        for ( uint8_t n_cnt = SILENTSTEP2_STEP_SPEED_MAX; n_cnt > step_speed; n_cnt-- ) 
        {
            silentstep2_step_delay( ctx );
        }
    
        silentstep2_set_step( ctx, 0 );
        silentstep2_step_delay( ctx );
        
        for ( uint8_t n_cnt = SILENTSTEP2_STEP_SPEED_MAX; n_cnt > step_speed; n_cnt-- ) 
        {
            Delay_50us( );
        }
    }
    return err_flag;
}

err_t silentstep2_rotate_by_angle ( silentstep2_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 ) 
{
    err_t err_flag = SILENTSTEP2_OK;
    float step_angle = DUMMY;
    uint16_t make_step = DUMMY;

    step_angle = SILENTSTEP2_ANGLE_360_DEGREES;
    step_angle /= ( float ) res_360;
    
    make_step = ( uint16_t ) ( angle / step_angle );
    
    for ( uint16_t n_cnt = 0; n_cnt < make_step; n_cnt++ ) 
    {
        err_flag |= silentstep2_make_one_step ( ctx, step_speed );
        Delay_1ms( );
    }
    return err_flag;
}

uint8_t silentstep2_get_interrupt ( silentstep2_t *ctx )
{
    return  digital_in_read( &ctx->int_pin );
}

static err_t silentstep2_i2c_write ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t silentstep2_i2c_read ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t silentstep2_spi_write ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

static err_t silentstep2_spi_read ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

static void silentstep2_step_delay ( silentstep2_t *ctx ) 
{
    for ( uint32_t n_cnt = 0; n_cnt < ctx->step_delay; n_cnt++ )
    {
        Delay_1us( );
    }
}

// ------------------------------------------------------------------------ END

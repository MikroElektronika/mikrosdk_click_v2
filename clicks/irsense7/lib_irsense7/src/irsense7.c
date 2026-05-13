/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file irsense7.c
 * @brief IR Sense 7 Click Driver.
 */

#include "irsense7.h"
#include "math.h"

/** 
 * @brief IR Sense 7 CCITT calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x1021 ( x16 + x12 + x5 + x0 )
 * @li @c  Initialization 0x620D
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @li @c  Example { 0x3F2B, 0x0BA2, 0x4193 } - 0x882D
 * @param[in] data_buf : Array of words to calculate crc from.
 * @param[in] len : Number of words to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t irsense7_calculate_crc16 ( uint16_t *data_buf, uint8_t len );

void irsense7_cfg_setup ( irsense7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = IRSENSE7_DEVICE_ADDRESS_0;
}

err_t irsense7_init ( irsense7_t *ctx, irsense7_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t irsense7_default_cfg ( irsense7_t *ctx ) 
{
    err_t error_flag = IRSENSE7_OK;
    if ( IRSENSE7_ERROR == irsense7_check_com ( ctx ) )
    {
        return IRSENSE7_ERROR;
    }
    error_flag = irsense7_reset_device ( ctx );
    Delay_100ms ( );

    error_flag |= irsense7_read_eeprom ( ctx );
    // Read RAM three times to get ready for the measurement calculations
    error_flag |= irsense7_read_ram ( ctx );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    error_flag |= irsense7_read_ram ( ctx );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    error_flag |= irsense7_read_ram ( ctx );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    return error_flag;
}

err_t irsense7_write_data ( irsense7_t *ctx, uint16_t addr, uint16_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( addr & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 4 );
}

err_t irsense7_read_data ( irsense7_t *ctx, uint16_t addr, uint16_t *data_out, uint16_t len )
{
    err_t error_flag = IRSENSE7_OK;
    uint8_t data_buf[ ( IRSENSE7_IDX_END - IRSENSE7_IDX_START + 1 ) * 2 ] = { 0 };
    if ( ( 0 == len ) || ( len > ( IRSENSE7_IDX_END - IRSENSE7_IDX_START + 1 ) ) || ( NULL == data_out ) )
    {
        return IRSENSE7_ERROR;
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( addr & 0xFF );
    error_flag |= i2c_master_write_then_read ( &ctx->i2c, data_buf, 2, data_buf, len * 2 );
    for ( uint16_t cnt = 0; ( cnt < len ) && ( IRSENSE7_OK == error_flag ); cnt++ )
    {
        data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 ] << 8 ) | data_buf[ cnt * 2 + 1 ];
    }
    return error_flag;
}

err_t irsense7_reset_device ( irsense7_t *ctx )
{
    return irsense7_write_data ( ctx, IRSENSE7_REG_EE_CONTROL, IRSENSE7_EE_CONTROL_DEVICE_RESET );
}

err_t irsense7_eeprom_write_unlock ( irsense7_t *ctx )
{
    return irsense7_write_data ( ctx, IRSENSE7_REG_EE_CONTROL, IRSENSE7_EE_CONTROL_EEPROM_UNLOCK );
}

err_t irsense7_check_com ( irsense7_t *ctx )
{
    err_t error_flag = IRSENSE7_OK;
    uint16_t id_buf[ ( IRSENSE7_IDX_ID_CRC16 - IRSENSE7_IDX_ID0 + 1 ) ] = { 0 };
    if ( IRSENSE7_OK == irsense7_read_data ( ctx, ( IRSENSE7_EEPROM_PROTECTED_START + IRSENSE7_IDX_ID0 ), 
                                             id_buf, ( IRSENSE7_IDX_ID_CRC16 - IRSENSE7_IDX_ID0 + 1 ) ) )
    {
        if ( id_buf[ ( IRSENSE7_IDX_ID_CRC16 - IRSENSE7_IDX_ID0 ) ] == 
             irsense7_calculate_crc16 ( id_buf, ( IRSENSE7_IDX_ID_CRC16 - IRSENSE7_IDX_ID0 ) ) )
        {
            return IRSENSE7_OK;
        }
    }
    return IRSENSE7_ERROR;
}

err_t irsense7_read_eeprom ( irsense7_t *ctx )
{
    uint32_t raw_32_u = 0;
    int32_t raw_32_s = 0;
    int16_t raw_16_s = 0;
    err_t error_flag = irsense7_read_data ( ctx, IRSENSE7_EEPROM_PROTECTED_START, ctx->ee_data, 
                                            ( IRSENSE7_IDX_END - IRSENSE7_IDX_START + 1 ) );
    if ( IRSENSE7_OK == error_flag )
    {
        // Check ID CRC
        if ( ctx->ee_data[ IRSENSE7_IDX_ID_CRC16 ] != 
             irsense7_calculate_crc16 ( &ctx->ee_data[ IRSENSE7_IDX_ID0 ], 
                                        ( IRSENSE7_IDX_ID_CRC16 - IRSENSE7_IDX_ID0 ) ) )
        {
            error_flag = IRSENSE7_ERROR;
        }
    }
    if ( IRSENSE7_OK == error_flag )
    {
        // Check MLX CRC
        if ( ctx->ee_data[ IRSENSE7_IDX_MLX_CRC ] != 
             irsense7_calculate_crc16 ( &ctx->ee_data[ IRSENSE7_IDX_START ], 
                                        ( IRSENSE7_IDX_MLX_CRC - IRSENSE7_IDX_START ) ) )
        {
            error_flag = IRSENSE7_ERROR;
        }
    }
    if ( IRSENSE7_OK == error_flag )
    {
        // Check CUST CRC
        if ( ctx->ee_data[ IRSENSE7_IDX_CUST_CRC ] != 
             irsense7_calculate_crc16 ( &ctx->ee_data[ IRSENSE7_IDX_EE_HA ], 
                                        ( IRSENSE7_IDX_END - IRSENSE7_IDX_CUST_CRC ) ) )
        {
            error_flag = IRSENSE7_ERROR;
        }
    }
    if ( IRSENSE7_OK == error_flag )
    {
        // Calculate and store calibration constants as per scaling from datasheet
        ctx->ee_cal.cp_val = ctx->ee_data[ IRSENSE7_IDX_EE_TCC1 ] & 0x03;
        ctx->ee_cal.cv_val = ( ctx->ee_data[ IRSENSE7_IDX_EE_TCC1 ] >> 2 ) & 0x03;
        ctx->ee_cal.ch_val = ( ctx->ee_data[ IRSENSE7_IDX_EE_TCC1 ] >> 4 ) & 0x03;
        ctx->ee_cal.cl_val = ( ctx->ee_data[ IRSENSE7_IDX_EE_TCC1 ] >> 6 ) & 0x03;
        ctx->ee_cal.ci_val = ( ctx->ee_data[ IRSENSE7_IDX_EE_TCC2 ] >> 10 ) & 0x03;
        raw_32_u = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_P_R_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_P_R_L ];
        ctx->ee_cal.p_r_val = raw_32_u * pow( 2, -8 );
        raw_32_u = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_P_G_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_P_G_L ];
        ctx->ee_cal.p_g_val = raw_32_u * pow( 2, -20 );
        raw_32_s = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_P_T_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_P_T_L ];
        ctx->ee_cal.p_t_val = raw_32_s * pow( 2, -44 );
        raw_32_s = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_P_O_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_P_O_L ];
        ctx->ee_cal.p_o_val = raw_32_s * pow( 2, -8 );
        raw_32_u = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_EA_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_EA_L ];
        ctx->ee_cal.ea_val = raw_32_u * pow( 2, -16 );
        raw_32_u = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_EB_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_EB_L ];
        ctx->ee_cal.eb_val = raw_32_u * pow( 2, -8 );
        raw_32_u = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_FA_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_FA_L ];
        ctx->ee_cal.fa_val = raw_32_u * pow( 2, -46 );
        raw_32_s = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_FB_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_FB_L ];
        ctx->ee_cal.fb_val = raw_32_s * pow( 2, -36 );
        raw_32_s = ( ( uint32_t ) ctx->ee_data[ IRSENSE7_IDX_EE_GA_H ] << 16 ) | 
                                  ctx->ee_data[ IRSENSE7_IDX_EE_GA_L ];
        ctx->ee_cal.ga_val = raw_32_s * pow( 2, -36 );
        ctx->ee_cal.gb_val = ctx->ee_data[ IRSENSE7_IDX_EE_GB ] * pow( 2, -10 );
        ctx->ee_cal.ka_val = ctx->ee_data[ IRSENSE7_IDX_EE_KA ] * pow( 2, -10 );
        ctx->ee_cal.ha_val = ctx->ee_data[ IRSENSE7_IDX_EE_HA ] * pow( 2, -14 );
        raw_16_s = ctx->ee_data[ IRSENSE7_IDX_EE_HB ];
        ctx->ee_cal.hb_val = raw_16_s * pow( 2, -10 );
    }
    return error_flag;
}

err_t irsense7_read_ram ( irsense7_t *ctx )
{
    return irsense7_read_data ( ctx, IRSENSE7_RAM_START, ( uint16_t * ) ctx->ram_data, 
                                ( IRSENSE7_RAM_END - IRSENSE7_RAM_START + 1 ) );
}

float irsense7_calculate_amb_temp ( irsense7_t *ctx )
{
    float t_amb = 0;
    float gr_val = 0;

    /*---------------------------------------------------------------*/
    /* GR = (RAM_6 / 2^CL) / (RAM_3 / 2^CH)                          */
    /*---------------------------------------------------------------*/
    gr_val = ctx->ram_data[ 5 ] / pow ( 2, ctx->ee_cal.cl_val );
    gr_val /= ( ctx->ram_data[ 2 ] / pow ( 2, ctx->ee_cal.ch_val ) );

    /*----------------------------------------------------------------*/
    /* Ta = ((RAM_9 * 2^19) /                                         */
    /*       (RAM_12 * GR * 2^(CP-CV) + Gb * RAM_9) - P_R) / P_G + 30 */
    /*----------------------------------------------------------------*/
    t_amb = ctx->ram_data[ 8 ] * pow ( 2, 19 );
    t_amb /= ( ( ctx->ram_data[ 11 ] * gr_val * 
                 pow ( 2, ( ctx->ee_cal.cp_val - ctx->ee_cal.cv_val ) ) ) + 
               ( ctx->ee_cal.gb_val * ctx->ram_data[ 8 ] ) );
    t_amb -= ctx->ee_cal.p_r_val;
    t_amb /= ctx->ee_cal.p_g_val;
    t_amb += 30;
    return t_amb;
}

float irsense7_calculate_obj_temp ( irsense7_t *ctx )
{
    static float to_val_old = 25.0; // In the first iteration 'To' is assumed to be 25degC
    float t_obj = 0;
    float s_val = 0;
    float vro_val = 0;
    float s_to_val = 0;
    float amb_val = 0;
    float ta_dut = 0;
    float ta_k = 0;

    /*---------------------------------------------------------------*/
    /* S = (RAM_7 + RAM_8 + RAM_10 + RAM_11) / 4                     */
    /*---------------------------------------------------------------*/
    s_val = ctx->ram_data[ 6 ];
    s_val += ctx->ram_data[ 7 ];
    s_val += ctx->ram_data[ 9 ];
    s_val += ctx->ram_data[ 10 ];
    s_val /= 4.0;

    /*---------------------------------------------------------------*/
    /* VRO = (RAM_12 / 2^CB) + (Ka * RAM_9) / (3 * 2^CP)             */
    /*---------------------------------------------------------------*/
    vro_val = ( ctx->ee_cal.ka_val * ctx->ram_data[ 8 ] );
    vro_val /= ( 3 * pow ( 2, ctx->ee_cal.cp_val ) );
    vro_val += ctx->ram_data[ 11 ];

    /*---------------------------------------------------------------*/
    /* STO = (S / (VRO * 3 * 2^CI)) * 2^19                           */
    /*---------------------------------------------------------------*/
    s_to_val = s_val;
    s_to_val /= ( vro_val * 3 * pow ( 2, ctx->ee_cal.ci_val ) );
    s_to_val *= pow ( 2, 19 );

    /*---------------------------------------------------------------*/
    /* AMB = (RAM_9 * 2^19) / (VRO * 3 * 2^CP)                       */
    /*---------------------------------------------------------------*/
    amb_val = ( ctx->ram_data[ 8 ] * pow ( 2, 19 ) );
    amb_val /= ( vro_val * 3 * pow ( 2, ctx->ee_cal.cp_val ) );

    /*---------------------------------------------------------------*/
    /* TA_DUT = (AMB - Eb) / Ea + 30                                 */
    /*---------------------------------------------------------------*/
    ta_dut = ( ( amb_val - ctx->ee_cal.eb_val ) / ctx->ee_cal.ea_val ) + 30;
    /* Convert to Kelvin */
    ta_k = ta_dut + 273.15;

    /*-----------------------------------------------------------*/
    /* To = 4th_root( STO / (ε * Fa * Ha * (1 + Ga*(To_old-To0)+ */
    /*               Fb*(TA_DUT-Ta0))) + Ta[K]^4 ) - 273.15 - Hb */
    /*-----------------------------------------------------------*/
    t_obj = s_to_val;
    t_obj /= ( ctx->ee_cal.fa_val * ctx->ee_cal.ha_val * 
               ( 1 + ctx->ee_cal.ga_val * ( to_val_old - 60 ) + ctx->ee_cal.fb_val * ( ta_dut - 30 ) ) );
    t_obj += pow ( ta_k, 4 );
    t_obj = pow ( t_obj, 0.25 );
    t_obj -= 273.15;
    t_obj -= ctx->ee_cal.hb_val;
    to_val_old = t_obj;
    return t_obj;
}

static uint16_t irsense7_calculate_crc16 ( uint16_t *data_buf, uint8_t len )
{
    uint16_t crc16 = 0x620D; // 90637 & 0xFFFF
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( ( ( data_buf[ cnt ] & 0xFF ) << 8 ) | ( ( data_buf[ cnt ] >> 8 ) & 0xFF ) );
        for ( uint8_t bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x1021;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}

// ------------------------------------------------------------------------- END

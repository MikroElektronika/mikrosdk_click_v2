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
 * @file irgrid4.c
 * @brief IR Grid 4 Click Driver.
 */

#include "irgrid4.h"
#include "math.h"

/**
 * @brief IR Grid 4 get VDD param function.
 * @details This function extracts VDD calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_vdd_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get PTAT param function.
 * @details This function extracts PTAT calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_ptat_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get GAIN param function.
 * @details This function extracts GAIN calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_gain_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get TGC param function.
 * @details This function extracts TGC calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_tgc_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get emissivity param function.
 * @details This function extracts emissivity calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_emissivity_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get resolution param function.
 * @details This function extracts resolution calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_resolution_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get KS_TA param function.
 * @details This function extracts KS_TA calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_ks_ta_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get KS_TO param function.
 * @details This function extracts KS_TO calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_ks_to_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get alpha param function.
 * @details This function extracts alpha calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_alpha_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get offset param function.
 * @details This function extracts offset calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_offset_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get KTA pixel param function.
 * @details This function extracts KTA pixel calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_kta_pixel_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get KV pixel param function.
 * @details This function extracts KV pixel calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_kv_pixel_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get CP param function.
 * @details This function extracts CP calibration parameters from EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void irgrid4_get_cp_param ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get deviating pixels function.
 * @details This function checks the broken pixels in EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irgrid4_get_deviating_pixels ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 hamming decode function.
 * @details This function performs hamming decode of EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irgrid4_hamming_decode ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 check EEPROM valid function.
 * @details This function validates EEPROM data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irgrid4_check_eeprom_valid ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 validate frame data function.
 * @details This function validates frame data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irgrid4_validate_frame_data ( uint16_t *frame_data );

/**
 * @brief IR Grid 4 validate aux data function.
 * @details This function validates aux data.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irgrid4_validate_aux_data ( uint16_t *aux_data );

void irgrid4_cfg_setup ( irgrid4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->led2 = HAL_PIN_NC;
    cfg->led1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRGRID4_DEVICE_ADDRESS;
}

err_t irgrid4_init ( irgrid4_t *ctx, irgrid4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->led2, cfg->led2 );
    digital_out_init( &ctx->led1, cfg->led1 );

    return I2C_MASTER_SUCCESS;
}

err_t irgrid4_default_cfg ( irgrid4_t *ctx ) 
{
    err_t error_flag = IRGRID4_OK;
    irgrid4_enable_led1 ( ctx );
    irgrid4_enable_led2 ( ctx );
    irgrid4_general_reset ( ctx );
    Delay_1sec ( );
    error_flag |= irgrid4_dump_eeprom ( ctx );
    error_flag |= irgrid4_get_parameters ( ctx );
    error_flag |= irgrid4_set_resolution ( ctx, IRGRID4_RESOLUTION_18_BIT );
    error_flag |= irgrid4_set_refresh_rate ( ctx, IRGRID4_REFRESH_RATE_4_HZ );
    Delay_100ms ( );
    irgrid4_disable_led1 ( ctx );
    irgrid4_disable_led2 ( ctx );
    return error_flag;
}

err_t irgrid4_write_data ( irgrid4_t *ctx, uint16_t addr, uint16_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( addr & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 4 );
}

err_t irgrid4_read_data ( irgrid4_t *ctx, uint16_t addr, uint16_t *data_out, uint8_t len )
{
    err_t error_flag = IRGRID4_OK;
    uint8_t data_buf[ 96 ] = { 0 };
    if ( ( 0 == len ) || ( len > 48 ) || ( NULL == data_out ) )
    {
        return IRGRID4_ERROR;
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( addr >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( addr & 0xFF );
    error_flag |= i2c_master_write_then_read ( &ctx->i2c, data_buf, 2, data_buf, len * 2 );
    for ( uint16_t cnt = 0; ( cnt < len ) && ( IRGRID4_OK == error_flag ); cnt++ )
    {
        data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 ] << 8 ) | data_buf[ cnt * 2 + 1 ];
    }
    return error_flag;
}

err_t irgrid4_general_reset ( irgrid4_t *ctx )
{
    uint8_t reset = 0x06;
    i2c_master_set_slave_address( &ctx->i2c, 0 );
    err_t error_flag = i2c_master_write( &ctx->i2c, &reset, 1 );
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    return error_flag;
}

void irgrid4_enable_led1 ( irgrid4_t *ctx )
{
    digital_out_high ( &ctx->led1 );
}

void irgrid4_disable_led1 ( irgrid4_t *ctx )
{
    digital_out_low ( &ctx->led1 );
}

void irgrid4_enable_led2 ( irgrid4_t *ctx )
{
    digital_out_high ( &ctx->led2 );
}

void irgrid4_disable_led2 ( irgrid4_t *ctx )
{
    digital_out_low ( &ctx->led2 );
}

err_t irgrid4_dump_eeprom ( irgrid4_t *ctx )
{
    err_t error_flag = IRGRID4_OK;
    for ( uint16_t addr = IRGRID4_ADDR_EEPROM_START; ( addr < IRGRID4_ADDR_EEPROM_END ) && 
                                                     ( IRGRID4_OK == error_flag ); addr += 32 )
    {
        error_flag |= irgrid4_read_data ( ctx, addr, &ctx->eeprom[ addr - IRGRID4_ADDR_EEPROM_START ], 32 );
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag = irgrid4_hamming_decode ( ctx );
    }
    return error_flag;
}

err_t irgrid4_sync_frame ( irgrid4_t *ctx )
{
    uint16_t status = 0;
    err_t error_flag = IRGRID4_OK;
    error_flag |= irgrid4_write_data ( ctx, IRGRID4_ADDR_REG_STATUS, IRGRID4_STATUS_OVERWRITE_EN );

    while ( ( IRGRID4_STATUS_DATA_READY != ( status & IRGRID4_STATUS_DATA_READY ) ) && ( IRGRID4_OK == error_flag ) )
    {
        error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_STATUS, &status, 1 );
    }
    return error_flag;
}

err_t irgrid4_trigger_measurement ( irgrid4_t *ctx )
{
    uint16_t control = 0;
    err_t error_flag = IRGRID4_OK;
    error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
    if ( IRGRID4_OK == error_flag )
    {
        control |= IRGRID4_ADDR_REG_STATUS;
        error_flag |= irgrid4_write_data ( ctx, IRGRID4_ADDR_REG_CONTROL, control );
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_general_reset ( ctx ); 
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
    }
    if ( ( IRGRID4_OK == error_flag ) && ( control & IRGRID4_ADDR_REG_STATUS ) )
    {
        error_flag |= IRGRID4_ERROR;
    }
    return error_flag;
}

err_t irgrid4_get_frame_data ( irgrid4_t *ctx, uint16_t *frame_data )
{
    uint16_t control = 0;
    uint16_t status = 0;
    err_t error_flag = irgrid4_sync_frame ( ctx );
    if ( IRGRID4_OK == error_flag )
    {
        if ( IRGRID4_STATUS_SUBPAGE != ( status & IRGRID4_STATUS_SUBPAGE ) )
        {
            error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START, &frame_data[ 0 ], 32 );
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 64, &frame_data[ 32 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 128, &frame_data[ 64 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 192, &frame_data[ 96 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 256, &frame_data[ 128 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 320, &frame_data[ 160 ], 32 );
            }
        }
        else
        {   
            error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 32, &frame_data[ 0 ], 32 );
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 96, &frame_data[ 32 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 160, &frame_data[ 64 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 224, &frame_data[ 96 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 288, &frame_data[ 128 ], 32 );
            }
            if ( IRGRID4_OK == error_flag )
            {
                error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_START + 352, &frame_data[ 160 ], 32 );
            }
        }
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_RAM_END - 63, &frame_data[ 192 ], 48 );
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
        frame_data[ 240 ] = control;
        frame_data[ 241 ] = status & IRGRID4_STATUS_SUBPAGE;
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_validate_aux_data ( &frame_data[ 192 ] );
    }
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_validate_frame_data ( frame_data );
    }
    return error_flag;
}

err_t irgrid4_get_parameters ( irgrid4_t *ctx )
{
    err_t error_flag = irgrid4_check_eeprom_valid ( ctx );
    if ( IRGRID4_OK == error_flag )
    {
        irgrid4_get_vdd_param ( ctx );
        irgrid4_get_ptat_param ( ctx );
        irgrid4_get_gain_param ( ctx );
        irgrid4_get_tgc_param ( ctx );
        irgrid4_get_emissivity_param ( ctx );
        irgrid4_get_resolution_param ( ctx );
        irgrid4_get_ks_ta_param ( ctx );
        irgrid4_get_ks_to_param ( ctx );
        irgrid4_get_cp_param ( ctx );
        irgrid4_get_alpha_param ( ctx );
        irgrid4_get_offset_param ( ctx );
        irgrid4_get_kta_pixel_param ( ctx );
        irgrid4_get_kv_pixel_param ( ctx );
        error_flag = irgrid4_get_deviating_pixels ( ctx );
    }
    return error_flag;
}

float irgrid4_get_vdd ( irgrid4_t *ctx, uint16_t *frame_data )
{
    float vdd_val = 0;
    float res_corr = 0;
    
    vdd_val = frame_data[ 234 ];
    if ( vdd_val > 32767 )
    {
        vdd_val = vdd_val - 65536;
    }

    res_corr = pow ( 2, ctx->calib.resolution_ee ) / 
               pow ( 2, ( ( frame_data[ 240 ] & IRGRID4_CONTROL_RESOLUTION_MASK ) >> 10 ) );
    vdd_val = ( res_corr * vdd_val - ctx->calib.vdd_25 ) / ctx->calib.k_vdd + 3.3;
    
    return vdd_val;
}

float irgrid4_get_ta ( irgrid4_t *ctx, uint16_t *frame_data )
{
    float ptat = 0;
    float ptat_art = 0;
    float vdd_val = 0;
    float ta_val = 0;
    
    vdd_val = irgrid4_get_vdd ( ctx, frame_data );
    ptat = frame_data[ 224 ];
    if ( ptat > 32767 )
    {
        ptat = ptat - 65536;
    }

    ptat_art = frame_data[ 192 ];
    if ( ptat_art > 32767 )
    {
        ptat_art = ptat_art - 65536;
    }
    ptat_art = ( ptat / ( ptat * ctx->calib.alpha_ptat + ptat_art ) ) * pow ( 2, 18 );
    
    ta_val = ( ptat_art / ( 1 + ctx->calib.kv_ptat * ( vdd_val - 3.3 ) ) - ctx->calib.v_ptat_25 );
    ta_val = ta_val / ctx->calib.kt_ptat + 25;
    
    return ta_val;
}

void irgrid4_get_to ( irgrid4_t *ctx, uint16_t *frame_data, float tr_val, float *result )
{
    float vdd_val = 0;
    float ta_val = 0;
    float ta_tr = 0;
    float gain = 0;
    float ir_data_cp = 0;
    float ir_data = 0;
    float alpha_compensated = 0;
    float sx_val = 0;
    float to_val = 0;
    float alpha_corr_r[ 8 ] = { 0 };
    uint8_t range = 0;
    float raw_kta = 0;
    float raw_kv = 0;
    
    vdd_val = irgrid4_get_vdd ( ctx, frame_data );
    ta_val = irgrid4_get_ta ( ctx, frame_data );
    
    ta_tr = pow ( ( tr_val + IRGRID4_ABS_ZERO_K ), 4 ) - 
            ( pow ( ( tr_val + IRGRID4_ABS_ZERO_K ), 4 ) - pow ( ( ta_val + IRGRID4_ABS_ZERO_K ), 4 ) ) / IRGRID4_EMISSIVITY;
    
    alpha_corr_r[ 1 ] = 1 / ( 1 + ctx->calib.ks_to[ 1 ] * 20 );
    alpha_corr_r[ 0 ] = alpha_corr_r[ 1 ] / ( 1 + ctx->calib.ks_to[ 0 ] * 20 );
    alpha_corr_r[ 2 ] = 1;
    alpha_corr_r[ 3 ] = ( 1 + ctx->calib.ks_to[ 2 ] * ctx->calib.ct[ 3 ] );
    alpha_corr_r[ 4 ] = alpha_corr_r[ 3 ] * ( 1 + ctx->calib.ks_to[ 3 ] * ( ctx->calib.ct[ 4 ] - ctx->calib.ct[ 3 ] ) );
    alpha_corr_r[ 5 ] = alpha_corr_r[ 4 ] * ( 1 + ctx->calib.ks_to[ 4 ] * ( ctx->calib.ct[ 5 ] - ctx->calib.ct[ 4 ] ) );
    alpha_corr_r[ 6 ] = alpha_corr_r[ 5 ] * ( 1 + ctx->calib.ks_to[ 5 ] * ( ctx->calib.ct[ 6 ] - ctx->calib.ct[ 5 ] ) );
    alpha_corr_r[ 7 ] = alpha_corr_r[ 6 ] * ( 1 + ctx->calib.ks_to[ 6 ] * ( ctx->calib.ct[ 7 ] - ctx->calib.ct[ 6 ] ) );
    
    gain = frame_data[ 202 ];
    if ( gain > 32767 )
    {
        gain = gain - 65536;
    }
    gain = ctx->calib.gain_ee / gain; 

    ir_data_cp = frame_data[ 200 ];  
    if ( ir_data_cp > 32767 )
    {
        ir_data_cp = ir_data_cp - 65536;
    }
    ir_data_cp = ir_data_cp * gain;

    ir_data_cp = 
        ir_data_cp - ctx->calib.cp_offset * ( 1 + ctx->calib.cp_kta * ( ta_val - 25 ) ) * 
        ( 1 + ctx->calib.cp_kv * ( vdd_val - 3.3 ) );
    
    for ( uint8_t pixel_number = 0; pixel_number < 192; pixel_number++ )
    {      
        ir_data = frame_data[ pixel_number ];
        if ( ir_data > 32767 )
        {
            ir_data = ir_data - 65536;
        }
        ir_data = ir_data * gain;
        
        raw_kta = ( float ) ctx->calib.kta[ pixel_number ] / pow ( 2, ctx->calib.kta_scale );
        raw_kv = ( float ) ctx->calib.kv[ pixel_number ] / pow ( 2, ctx->calib.kv_scale );
            
        ir_data = 
            ir_data - ctx->calib.offset[ frame_data[ 241 ] ][ pixel_number ] * 
            ( 1 + raw_kta * ( ta_val - 25 ) ) * ( 1 + raw_kv * ( vdd_val - 3.3 ) );                
    
        ir_data = ir_data - ctx->calib.tgc * ir_data_cp;
        
        ir_data = ir_data / IRGRID4_EMISSIVITY;
        
        alpha_compensated = IRGRID4_SCALE_ALPHA * pow ( 2, ctx->calib.alpha_scale ) / ctx->calib.alpha[ pixel_number ];
        alpha_compensated = alpha_compensated * ( 1 + ctx->calib.ks_ta * ( ta_val - 25 ) );
        
        sx_val = pow ( alpha_compensated, 3 ) * ( ir_data + alpha_compensated * ta_tr );
        sx_val = pow ( sx_val, 0.25 ) * ctx->calib.ks_to[ 2 ];
        
        to_val = 
            pow ( ( ir_data / ( alpha_compensated * ( 1 - ctx->calib.ks_to[ 2 ] * IRGRID4_ABS_ZERO_K ) + sx_val ) + 
                    ta_tr ), 0.25 ) - IRGRID4_ABS_ZERO_K;
                
        if ( to_val < ctx->calib.ct[ 1 ] )
        {
            range = 0;
        }
        else if ( to_val < ctx->calib.ct[ 2 ] )   
        {
            range = 1;            
        }   
        else if ( to_val < ctx->calib.ct[ 3 ] )
        {
            range = 2;            
        }
        else if ( to_val < ctx->calib.ct[ 4 ] )
        {
            range = 3;            
        }
        else if ( to_val < ctx->calib.ct[ 5 ] )
        {
            range = 4;            
        }
        else if ( to_val < ctx->calib.ct[ 6 ] )
        {
            range = 5;            
        }
        else if ( to_val < ctx->calib.ct[ 7 ] )
        {
            range = 6;            
        }
        else
        {
            range = 7;            
        }      
        
        to_val = 
            pow ( ( ir_data / ( alpha_compensated * alpha_corr_r[ range ] * 
                                ( 1 + ctx->calib.ks_to[ range ] * ( to_val - ctx->calib.ct[ range ] ) ) ) + 
                    ta_tr ), 0.25 ) - IRGRID4_ABS_ZERO_K;
        
        result[ pixel_number ] = to_val;
    }
}

err_t irgrid4_set_resolution ( irgrid4_t *ctx, uint8_t resolution )
{
    uint16_t control = 0;
    err_t error_flag = IRGRID4_OK;

    error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
    if ( IRGRID4_OK == error_flag )
    {
        control = ( control & ( ~IRGRID4_CONTROL_RESOLUTION_MASK ) ) | 
                  ( ( ( uint16_t ) resolution << 10 ) & IRGRID4_CONTROL_RESOLUTION_MASK );
        error_flag |= irgrid4_write_data ( ctx, IRGRID4_ADDR_REG_CONTROL, control );
    }
    return error_flag;
}

err_t irgrid4_get_resolution ( irgrid4_t *ctx, uint8_t *resolution )
{
    uint16_t control = 0;
    err_t error_flag = IRGRID4_OK;

    error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
    if ( ( IRGRID4_OK == error_flag ) && ( NULL != resolution ) )
    {
        *resolution = ( uint8_t ) ( ( control & IRGRID4_CONTROL_RESOLUTION_MASK ) >> 10 );
    }
    return error_flag;
}

err_t irgrid4_set_refresh_rate ( irgrid4_t *ctx, uint8_t refresh_rate )
{
    uint16_t control = 0;
    err_t error_flag = IRGRID4_OK;

    error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
    if ( IRGRID4_OK == error_flag )
    {
        control = ( control & ( ~IRGRID4_CONTROL_REFRESH_RATE_MASK ) ) | 
                  ( ( ( uint16_t ) refresh_rate << 7 ) & IRGRID4_CONTROL_REFRESH_RATE_MASK );
        error_flag |= irgrid4_write_data ( ctx, IRGRID4_ADDR_REG_CONTROL, control );
    }
    return error_flag;
}

err_t irgrid4_get_refresh_rate ( irgrid4_t *ctx, uint8_t *refresh_rate )
{
    uint16_t control = 0;
    err_t error_flag = IRGRID4_OK;

    error_flag |= irgrid4_read_data ( ctx, IRGRID4_ADDR_REG_CONTROL, &control, 1 );
    if ( ( IRGRID4_OK == error_flag ) && ( NULL != refresh_rate ) )
    {
        *refresh_rate = ( uint8_t ) ( ( control & IRGRID4_CONTROL_REFRESH_RATE_MASK ) >> 7 );
    }
    return error_flag;
}

err_t irgrid4_get_measurement ( irgrid4_t *ctx, float *t_amb, float *t_obj )
{
    uint16_t frame_data[ 242 ] = { 0 };
    err_t error_flag = IRGRID4_OK;
    error_flag |= irgrid4_get_frame_data ( ctx, frame_data );
    if ( IRGRID4_OK == error_flag )
    {
        error_flag |= irgrid4_get_frame_data ( ctx, frame_data );
    }
    if ( ( IRGRID4_OK == error_flag ) && ( NULL != t_amb ) && ( NULL != t_obj ) )
    {
        *t_amb = irgrid4_get_ta ( ctx, frame_data ) - IRGRID4_TA_SHIFT;
        irgrid4_get_to ( ctx, frame_data, *t_amb, t_obj );
    }
    return error_flag;
}

static void irgrid4_get_vdd_param ( irgrid4_t *ctx )
{
    int16_t k_vdd = 0;
    int16_t vdd_25 = 0;

    k_vdd = ctx->eeprom[ 39 ];
    if ( k_vdd > 1023 )
    {
        k_vdd = k_vdd - 2048;
    }
    k_vdd = 32 * k_vdd;

    vdd_25 = ctx->eeprom[ 38 ];
    if ( vdd_25 > 1023 )
    {
        vdd_25 = vdd_25 - 2048;
    }
    vdd_25 = 32 * vdd_25;
    ctx->calib.k_vdd = k_vdd;
    ctx->calib.vdd_25 = vdd_25;
}

static void irgrid4_get_ptat_param ( irgrid4_t *ctx )
{
    float kv_ptat = 0;
    float kt_ptat = 0;
    int16_t v_ptat_25 = 0;
    float alpha_ptat = 0;

    kv_ptat = ctx->eeprom[ 43 ];
    if ( kv_ptat > 1023 )
    {
        kv_ptat = kv_ptat - 2048;
    }
    kv_ptat = kv_ptat / 4096;

    kt_ptat = ctx->eeprom[ 42 ];
    if ( kt_ptat > 1023 )
    {
        kt_ptat = kt_ptat - 2048;
    }
    kt_ptat = kt_ptat / 8;

    v_ptat_25 = 32 * ctx->eeprom[ 40 ] + ctx->eeprom[ 41 ];

    alpha_ptat = ctx->eeprom[ 44 ] / 128.0f;
    ctx->calib.kv_ptat = kv_ptat;
    ctx->calib.kt_ptat = kt_ptat;
    ctx->calib.v_ptat_25 = v_ptat_25;
    ctx->calib.alpha_ptat = alpha_ptat;
}

static void irgrid4_get_gain_param ( irgrid4_t *ctx )
{
    int16_t gain_ee = 0;

    gain_ee = 32 * ctx->eeprom[ 36 ] + ctx->eeprom[ 37 ];

    ctx->calib.gain_ee = gain_ee;
}

static void irgrid4_get_tgc_param ( irgrid4_t *ctx )
{
    float tgc = 0;

    tgc = ctx->eeprom[ 51 ] & 0x01FF;
    if ( tgc > 255 )
    {
        tgc = tgc - 512;
    }
    tgc = tgc / 64.0f;
    
    ctx->calib.tgc = tgc;     
}

static void irgrid4_get_emissivity_param ( irgrid4_t *ctx )
{
    float emissivity = 0;

    emissivity = ctx->eeprom[ 35 ];
       
    if ( emissivity > 1023 )
    {
        emissivity = emissivity - 2048;
    }
    emissivity = emissivity / 512;
    
    ctx->calib.emissivity_ee = emissivity;
}

static void irgrid4_get_resolution_param ( irgrid4_t *ctx )
{
    uint8_t resolution_ee = 0;

    resolution_ee = ( ctx->eeprom[ 51 ] & 0x0600 ) >> 9;    
    
    ctx->calib.resolution_ee = resolution_ee;
}

static void irgrid4_get_ks_ta_param ( irgrid4_t *ctx )
{
    float ks_ta = 0;

    ks_ta = ctx->eeprom[ 34 ];
    if ( ks_ta > 1023 )
    {
        ks_ta = ks_ta - 2048;
    }
    ks_ta = ks_ta / 32768.0f;
    
    ctx->calib.ks_ta = ks_ta;
}

static void irgrid4_get_ks_to_param ( irgrid4_t *ctx )
{
    int32_t ks_to_scale = 0;
    
    ctx->calib.ct[ 0 ] = -40;
    ctx->calib.ct[ 1 ] = -20;
    ctx->calib.ct[ 2 ] = 0;
    ctx->calib.ct[ 3 ] = 80;
    ctx->calib.ct[ 4 ] = 120;
    ctx->calib.ct[ 5 ] = ctx->eeprom[ 58 ];
    ctx->calib.ct[ 6 ] = ctx->eeprom[ 60 ];
    ctx->calib.ct[ 7 ] = ctx->eeprom[ 62 ];

    ks_to_scale = ctx->eeprom[ 52 ];
    ks_to_scale = 1ul << ks_to_scale;
    
    ctx->calib.ks_to[ 0 ] = ctx->eeprom[ 53 ];
    ctx->calib.ks_to[ 1 ] = ctx->eeprom[ 54 ];
    ctx->calib.ks_to[ 2 ] = ctx->eeprom[ 55 ];
    ctx->calib.ks_to[ 3 ] = ctx->eeprom[ 56 ];
    ctx->calib.ks_to[ 4 ] = ctx->eeprom[ 57 ];
    ctx->calib.ks_to[ 5 ] = ctx->eeprom[ 59 ];
    ctx->calib.ks_to[ 6 ] = ctx->eeprom[ 61 ];
    ctx->calib.ks_to[ 7 ] = ctx->eeprom[ 63 ];
    
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        if ( ctx->calib.ks_to[ cnt ] > 1023 )
        {
            ctx->calib.ks_to[ cnt ] = ctx->calib.ks_to[ cnt ] - 2048;
        }
        ctx->calib.ks_to[ cnt ] = ctx->calib.ks_to[ cnt ] / ks_to_scale;
    } 
}

static void irgrid4_get_alpha_param ( irgrid4_t *ctx )
{
    float row_max_alpha_norm[ 6 ] = { 0 };
    uint16_t scale_row_alpha[ 6 ] = { 0 };
    uint8_t alpha_scale = 0;
    float alpha_temp[ 192 ] = { 0 };
    float temp = 0;
    uint8_t p_cnt = 0;
    uint8_t cnt_0 = 0;
    uint8_t cnt_1 = 0;

    scale_row_alpha[ 0 ] = ( ctx->eeprom[ 25 ] >> 5 ) + 20;
    scale_row_alpha[ 1 ] = ( ctx->eeprom[ 25 ] & 0x001F ) + 20;
    scale_row_alpha[ 2 ] = ( ctx->eeprom[ 26 ] >> 5 ) + 20;
    scale_row_alpha[ 3 ] = ( ctx->eeprom[ 26 ] & 0x001F ) + 20;
    scale_row_alpha[ 4 ] = ( ctx->eeprom[ 27 ] >> 5 ) + 20;
    scale_row_alpha[ 5 ] = ( ctx->eeprom[ 27 ] & 0x001F ) + 20;
    
    for ( cnt_0 = 0; cnt_0 < 6; cnt_0++ )
    {
        row_max_alpha_norm[ cnt_0 ] = ctx->eeprom[ 28 + cnt_0 ] / pow ( 2, scale_row_alpha[ cnt_0 ] );
        row_max_alpha_norm[ cnt_0 ] = row_max_alpha_norm[ cnt_0 ] / 2047.0f;
    }

    for ( cnt_0 = 0; cnt_0 < 6; cnt_0++ )
    {
        for ( cnt_1 = 0; cnt_1 < 32; cnt_1++ )
        {
            p_cnt = 32 * cnt_0 + cnt_1;
            alpha_temp[ p_cnt ] = ctx->eeprom[ 256 + p_cnt ] * row_max_alpha_norm[ cnt_0 ]; 
            alpha_temp[ p_cnt ] = alpha_temp[ p_cnt ] - ctx->calib.tgc * ctx->calib.cp_alpha;
            alpha_temp[ p_cnt ] = IRGRID4_SCALE_ALPHA / alpha_temp[ p_cnt ];
        }
    }
    
    temp = alpha_temp[ 0 ];
    for ( cnt_0 = 1; cnt_0 < 192; cnt_0++ )
    {
        if ( alpha_temp[ cnt_0 ] > temp )
        {
            temp = alpha_temp[ cnt_0 ];
        }
    }
    
    alpha_scale = 0;
    while ( temp < 32768 )
    {
        temp = temp * 2;
        alpha_scale = alpha_scale + 1;
    } 
    
    for ( cnt_0 = 0; cnt_0 < 192; cnt_0++ )
    {
        temp = alpha_temp[ cnt_0 ] * pow ( 2, alpha_scale );        
        ctx->calib.alpha[ cnt_0 ] = ( temp + 0.5 );
    } 
    
    ctx->calib.alpha_scale = alpha_scale;
}

static void irgrid4_get_offset_param ( irgrid4_t *ctx )
{
    int32_t scale_offset = 0;
    int16_t offset_ref = 0;
    int16_t temp_offset = 0;
    uint8_t cnt = 0;
    
    scale_offset = ctx->eeprom[ 16 ] >> 5;
    scale_offset = 1ul << scale_offset;

    offset_ref = 32 * ctx->eeprom[ 17 ] + ctx->eeprom[ 18 ];
    if ( offset_ref > 32767 )
    {
        offset_ref = offset_ref - 65536;
    }

    for ( cnt = 0; cnt < 192; cnt++ )
    {
        temp_offset = ctx->eeprom[ 64 + cnt ];
        if ( temp_offset > 1023 )
        {
            temp_offset = ctx->eeprom[ 64 + cnt ] - 2048; 
        }
        ctx->calib.offset[ 0 ][ cnt ] = temp_offset * scale_offset + offset_ref;
        
        temp_offset = ctx->eeprom[ 640 + cnt ];
        if ( temp_offset > 1023 )
        {
            temp_offset = ctx->eeprom[ 640 + cnt ] - 2048; 
        }
        ctx->calib.offset[ 1 ][ cnt ] = temp_offset * scale_offset + offset_ref;
    }
}

static void irgrid4_get_kta_pixel_param ( irgrid4_t *ctx )
{
    uint8_t kta_scale_1 = 0;
    uint8_t kta_scale_2 = 0;
    int16_t kta_avg = 0;
    int16_t temp_kta = 0;
    float kta_temp[ 192 ] = { 0 };
    float temp = 0;
    uint8_t cnt = 0;

    kta_avg = ctx->eeprom[ 21 ];
    if ( kta_avg > 1023 )
    {
        kta_avg = kta_avg - 2048;
    }
  
    kta_scale_1 = ctx->eeprom[ 22 ] >> 5;
    kta_scale_2 = ctx->eeprom[ 22 ] & 0x001F;

    for ( cnt = 0; cnt < 192; cnt++ )
    {
        temp_kta = ( ctx->eeprom[ 448 + cnt ] >> 5 );
        if ( temp_kta > 31 )
        {
            temp_kta = temp_kta - 64;
        }
        kta_temp[ cnt ] = ( temp_kta * pow ( 2, kta_scale_2 ) + kta_avg ) / pow ( 2, kta_scale_1 );
    }
    
    temp = fabs ( kta_temp[ 0 ] );
    for ( cnt = 1; cnt < 192; cnt++ )
    {
        if ( fabs ( kta_temp[ cnt ] ) > temp )
        {
            temp = fabs ( kta_temp[ cnt ] );
        }
    }
    
    kta_scale_1 = 0;
    while ( temp < 64 )
    {
        temp = temp * 2;
        kta_scale_1 = kta_scale_1 + 1;
    }    
     
    for ( cnt = 0; cnt < 192; cnt++ )
    {
        temp = kta_temp[ cnt ] * pow ( 2, kta_scale_1 );
        if ( temp < 0 )
        {
            ctx->calib.kta[ cnt ] = ( int8_t ) ( temp - 0.5 );
        }
        else
        {
            ctx->calib.kta[ cnt ] = ( int8_t ) ( temp + 0.5 );
        }
    } 
    
    ctx->calib.kta_scale = kta_scale_1;
}

static void irgrid4_get_kv_pixel_param ( irgrid4_t *ctx )
{
    uint8_t kv_scale_1 = 0;
    uint8_t kv_scale_2 = 0;
    int16_t kv_avg = 0;
    int16_t temp_kv = 0;
    float kv_temp[ 192 ] = { 0 };
    float temp = 0;
    uint8_t cnt = 0;

    kv_avg = ctx->eeprom[ 23 ];
    if ( kv_avg > 1023 )
    {
        kv_avg = kv_avg - 2048;
    }
    
    kv_scale_1 = ctx->eeprom[ 24 ] >> 5;
    kv_scale_2 = ctx->eeprom[ 24 ] & 0x001F;

    for ( cnt = 0; cnt < 192; cnt++ )
    {
        temp_kv = ( ctx->eeprom[ 448 + cnt ] & 0x001F );
        if ( temp_kv > 15 )
        {
            temp_kv = temp_kv - 32;
        }
        kv_temp[ cnt ] = ( temp_kv * pow ( 2, kv_scale_2 ) + kv_avg ) / pow ( 2, kv_scale_1 );
    }
    
    temp = fabs ( kv_temp[ 0 ] );
    for ( cnt = 1; cnt < 192; cnt++ )
    {
        if ( fabs ( kv_temp[ cnt ] ) > temp )
        {
            temp = fabs ( kv_temp[ cnt ] );
        }
    }
    
    kv_scale_1 = 0;
    while ( temp < 64 )
    {
        temp = temp * 2;
        kv_scale_1 = kv_scale_1 + 1;
    }    
     
    for ( cnt = 0; cnt < 192; cnt++ )
    {
        temp = kv_temp[ cnt ] * pow ( 2, kv_scale_1 );
        if ( temp < 0 )
        {
            ctx->calib.kv[ cnt ] = ( int8_t ) ( temp - 0.5 );
        }
        else
        {
            ctx->calib.kv[ cnt ] = ( int8_t ) ( temp + 0.5 );
        }
    } 
    
    ctx->calib.kv_scale = kv_scale_1;
}

static void irgrid4_get_cp_param ( irgrid4_t *ctx )
{
    float alpha_cp = 0;
    int16_t offset_cp = 0;
    float cp_kv = 0;
    float cp_kta = 0;

    offset_cp = 32 * ctx->eeprom[ 47 ] + ctx->eeprom[ 48 ];
    if ( offset_cp > 32767 )
    {
        offset_cp = offset_cp - 65536;
    }
    
    alpha_cp = ctx->eeprom[ 45 ];
    if ( alpha_cp > 1023 )
    {
        alpha_cp = alpha_cp - 2048;
    }
    alpha_cp = alpha_cp / pow ( 2, ctx->eeprom[ 46 ] );
    
    cp_kta = ctx->eeprom[ 49 ] & 0x003F;
    if ( cp_kta > 31 )
    {
        cp_kta = cp_kta - 64;
    }
    ctx->calib.cp_kta = cp_kta / pow ( 2, ( ctx->eeprom[ 49 ] >> 6 ) );
    
    cp_kv = ctx->eeprom[ 50 ] & 0x003F;
    if ( cp_kv > 31 )
    {
        cp_kv = cp_kv - 64;
    }
    ctx->calib.cp_kv = cp_kv / pow ( 2, ( ctx->eeprom[ 50 ] >> 6 ) );

    ctx->calib.cp_alpha = alpha_cp;
    ctx->calib.cp_offset = offset_cp;
}

static err_t irgrid4_get_deviating_pixels ( irgrid4_t *ctx )
{
    uint16_t pix_cnt = 0;
    uint16_t broken_pix_cnt = 0;
    err_t error_flag = IRGRID4_OK;
    
    ctx->calib.broken_pixel = 0xFFFF;
    
    pix_cnt = 0;   
    while ( ( pix_cnt < 192 ) && ( broken_pix_cnt < 2 ) )
    {
        if ( ( 0 == ctx->eeprom[ pix_cnt + 64 ] ) && ( 0 == ctx->eeprom[ pix_cnt + 256 ] ) && 
             ( 0 == ctx->eeprom[ pix_cnt + 448 ] ) && ( 0 == ctx->eeprom[ pix_cnt + 640 ] ) )
        {
            ctx->calib.broken_pixel = pix_cnt;
            broken_pix_cnt = broken_pix_cnt + 1;
        }
        pix_cnt = pix_cnt + 1;
    } 
    
    if ( broken_pix_cnt > 1 )  
    {
        error_flag = IRGRID4_ERROR;
    }         
    
    return error_flag;
}

static err_t irgrid4_hamming_decode ( irgrid4_t *ctx )
{
    int16_t parity[ 5 ] = { 0 };
    int8_t d_bit[ 16 ] = { 0 };
    int16_t check = 0;
    uint16_t ee_data = 0;
    uint16_t mask = 0;
    uint8_t bit_cnt = 0;
    err_t error_flag = IRGRID4_OK;
    
    for ( uint16_t addr = 16; addr < 832; addr++ )
    {   
        parity[ 0 ] = -1;
        parity[ 1 ] = -1;
        parity[ 2 ] = -1;
        parity[ 3 ] = -1;
        parity[ 4 ] = -1;
        
        ee_data = ctx->eeprom[ addr ];
        
        mask = 1;
        for ( bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
        {          
            d_bit[ bit_cnt ] = ( ee_data & mask ) >> bit_cnt;
            mask = mask << 1;
        }
        
        parity[ 0 ] = 
            d_bit[ 0 ] ^ d_bit[ 1 ] ^ d_bit[ 3 ] ^ d_bit[ 4 ] ^ d_bit[ 6 ] ^ d_bit[ 8 ] ^ d_bit[ 10 ] ^ d_bit[ 11 ];
        parity[ 1 ] = 
            d_bit[ 0 ] ^ d_bit[ 2 ] ^ d_bit[ 3 ] ^ d_bit[ 5 ] ^ d_bit[ 6 ] ^ d_bit[ 9 ] ^ d_bit[ 10 ] ^ d_bit[ 12 ];
        parity[ 2 ] = 
            d_bit[ 1 ] ^ d_bit[ 2 ] ^ d_bit[ 3 ] ^ d_bit[ 7 ] ^ d_bit[ 8 ] ^ d_bit[ 9 ] ^ d_bit[ 10 ] ^ d_bit[ 13 ];
        parity[ 3 ] = 
            d_bit[ 4 ] ^ d_bit[ 5 ] ^ d_bit[ 6 ] ^ d_bit[ 7 ] ^ d_bit[ 8 ] ^ d_bit[ 9 ] ^ d_bit[ 10 ] ^ d_bit[ 14 ];
        parity[ 4 ] = 
            d_bit[ 0 ] ^ d_bit[ 1 ] ^ d_bit[ 2 ] ^ d_bit[ 3 ] ^ d_bit[ 4 ] ^ d_bit[ 5 ] ^ d_bit[ 6 ] ^ d_bit[ 7 ] ^ 
            d_bit[ 8 ] ^ d_bit[ 9 ] ^ d_bit[ 10 ] ^ d_bit[ 11 ] ^ d_bit[ 12 ] ^ d_bit[ 13 ] ^ d_bit[ 14 ] ^ d_bit[ 15 ];
        
        if ( ( parity[ 0 ] ) || ( parity[ 1 ] ) || ( parity[ 2 ] ) || ( parity[ 3 ] ) || ( parity[ 4 ] ) )
        {        
            check = 
                parity[ 0 ] + ( parity[ 1 ] << 1 ) + ( parity[ 2 ] << 2 ) + ( parity[ 3 ] << 3 ) + ( parity[ 4 ] << 4 );

            if ( ( check > 15 ) && ( check < 32 ) )
            {
                switch ( check )
                {    
                    case 16:
                    {
                        d_bit[ 15 ] = 1 - d_bit[ 15 ];
                        break;
                    }
                    case 24:
                    {
                        d_bit[ 14 ] = 1 - d_bit[ 14 ];
                        break;
                    }   
                    case 20:
                    {
                        d_bit[ 13 ] = 1 - d_bit[ 13 ];
                        break;
                    }   
                    case 18:
                    { 
                        d_bit[ 12 ] = 1 - d_bit[ 12 ];
                        break;                                
                    }   
                    case 17:
                    {
                        d_bit[ 11 ] = 1 - d_bit[ 11 ];
                        break;
                    }   
                    case 31:
                    { 
                        d_bit[ 10 ] = 1 - d_bit[ 10 ];
                        break;
                    }   
                    case 30:
                    {
                        d_bit[ 9 ] = 1 - d_bit[ 9 ];
                        break;
                    }
                    case 29:
                    {
                        d_bit[ 8 ] = 1 - d_bit[ 8 ];
                        break;                
                    }
                    case 28:
                    {
                        d_bit[ 7 ] = 1 - d_bit[ 7 ];
                        break;
                    }   
                    case 27:
                    {
                        d_bit[ 6 ] = 1 - d_bit[ 6 ];
                        break;
                    }       
                    case 26:
                    {
                        d_bit[ 5 ] = 1 - d_bit[ 5 ];
                        break;    
                    }   
                    case 25:
                    {
                        d_bit[ 4 ] = 1 - d_bit[ 4 ];
                        break;     
                    }   
                    case 23:
                    {
                        d_bit[ 3 ] = 1 - d_bit[ 3 ];
                        break; 
                    }   
                    case 22:
                    {
                        d_bit[ 2 ] = 1 - d_bit[ 2 ];
                        break; 
                    }       
                    case 21:
                    {
                        d_bit[ 1 ] = 1 - d_bit[ 1 ];
                        break; 
                    }
                    case 19:
                    {   
                        d_bit[ 0 ] = 1 - d_bit[ 0 ];
                        break;     
                    }
                    default:
                    {
                        break;
                    }             
                }
                
                ee_data = 0;
                mask = 1;
                for ( bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
                {                    
                    ee_data = ee_data + d_bit[ bit_cnt ] * mask;
                    mask = mask << 1;
                }
            }
            error_flag = IRGRID4_ERROR;
        }
        ctx->eeprom[ addr ] = ee_data & 0x07FF;
    }
    return error_flag;
}

static err_t irgrid4_check_eeprom_valid ( irgrid4_t *ctx )
{
    if ( ctx->eeprom[ 10 ] & 0x0040 )
    {
        return IRGRID4_OK;
    }
    return IRGRID4_ERROR;
}

static err_t irgrid4_validate_frame_data ( uint16_t *frame_data )
{
    uint8_t cnt = 0;
    for ( cnt = 0; cnt < 192; cnt += 16 )
    {
        if ( 0x7FFF == frame_data[ cnt ] )
        {
            return IRGRID4_ERROR;
        }
    }
    return IRGRID4_OK;
}

static err_t irgrid4_validate_aux_data ( uint16_t *aux_data )
{
    uint8_t cnt = 0;
    if ( 0x7FFF == aux_data[ 0 ] )
    {
        return IRGRID4_ERROR;
    }
    for ( cnt = 8; cnt < 19; cnt++ )
    {
        if ( 0x7FFF == aux_data[ cnt ] )
        {
            return IRGRID4_ERROR;
        }
    }
    for ( cnt = 20; cnt < 23; cnt++ )
    {
        if ( 0x7FFF == aux_data[ cnt ] )
        {
            return IRGRID4_ERROR;
        }
    }
    for ( cnt = 24; cnt < 33; cnt++ )
    {
        if ( 0x7FFF == aux_data[ cnt ] )
        {
            return IRGRID4_ERROR;
        }
    }
    for ( cnt = 40; cnt < 48; cnt++ )
    {
        if ( 0x7FFF == aux_data[ cnt ] )
        {
            return IRGRID4_ERROR;
        }
    }
    return IRGRID4_OK;
}

// ------------------------------------------------------------------------- END

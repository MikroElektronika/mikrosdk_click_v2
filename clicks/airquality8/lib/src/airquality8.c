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
 * @file airquality8.c
 * @brief Air Quality 8 Click Driver.
 */

#include "airquality8.h"
#include "math.h"

#define DUMMY                            0x00

#define AIRQUALITY8_FIRST_SEQ_STEP       0
#define AIRQUALITY8_LAST_SEQ_STEP        1

#define D_RISING_M1                      4.9601944386079566e-05
#define D_FALLING_M1                     0.3934693402873666
#define D_CLASS_M1                       0.024690087971667385

static float scaler_and_pca_o[ 8 ] = 
{
    1.74133742, -1.05259192, -0.6739225, 6.25734425, 6.44056368,
    -2.85911536, 1.26398969, -0.07627178
    
};

static float scaler_and_pca_g[ 88 ] = 
{
    0.098822169, 0.076355919, -0.24257118, -0.3427524, -0.36181408,
    -0.56742352, -0.59832847, -0.52399075, -0.81655341, -0.66967648,
    -0.55128223, 0.0052506132, -0.089478098, 1.5322995, 1.2153398,
    0.69527262, 0.80276036, -0.38943779, -0.84154904, -1.0249839,
    -1.9840645, -2.0471313, 1.0043662, -0.68624401, -0.17178419,
    -0.021966385, 0.080418855, -0.29417408, 0.053931851, 0.17823912,
    -0.10622692, 0.21712069, 0.28085747, -0.72911143, -0.67155647,
    1.605744, -1.6921251, -2.6079316, 0.18752402, -1.1799121,
    -1.1853565, 1.0869612, 0.42717779, 0.48912618, -1.0410491,
    -0.76051044, -2.2981009, 0.83406442, 1.7949145, -2.4980917,
    -0.17692336, 0.53374362, -3.6838586, -1.4608299, -0.90180105,
    0.11278431, 0.25221416, 3.2374511, 2.74702, -0.62844849,
    -8.571579, -1.8568134, 1.7693721, -5.4411964, 3.0048814,
    5.5464873, -0.031913839, -0.078795917, -3.0445056, 7.693006,
    -5.6150074, 1.6021262, -1.4109792, -2.7250714, 3.8859453,
    1.1784325, 0.053968702, 0.10485264, 0.061339337, 0.22992066,
    0.19881652, -8.227809, 8.450017, -1.3848327, 23.178757,
    -16.182943, -7.2538972, -5.0571938
    
};
    
static float svc_poly_coeffs[ 168 ] = 
{
    -3.1019304, -2.3316905, 4.7303534, -0.80521905, 1.9767121,
    -2.0625834, 2.9635882, 1.1311389, -0.0052948906, -0.95747906,
    1.6330426, 2.2969685, -2.7378335, 1.1746475, -0.079822987,
    0.086946793, 3.4260488, -2.1125345, -0.959176, 0.066470027,
    3.703608, -3.8293538, 0.6122278, 3.7048388, -1.1051865,
    -1.0215594, 4.7507892, -3.3319578, -1.4624187, -0.2667965,
    0.40958887, -0.58006084, -0.7323609, 0.49243289, 0.26756704,
    4.6461277, -3.2305396, 0.94641966, 0.98231965, -0.29620481,
    -1.3983079, 2.0152678, -2.8249195, 3.7985516, -0.48653999,
    2.0379181, -3.2296391, -0.7920357, -1.0288268, -0.055438876,
    2.8394473, -0.80105704, 3.4359744, -1.5734187, -0.93969798,
    -0.98496193, 3.165663, 0.67869413, -2.4870875, 1.8048391,
    2.0739756, -1.7421837, -8.9348974, 0.56574947, -2.32111,
    1.2667328, -6.863461, 2.2387428, -1.7676632, 2.0244179,
    0.11134893, -7.9828277, 0.40084094, 0.44028839, -4.6814523,
    -0.712448, -3.60025, 1.2042403, -2.565119, 0.54992688,
    3.9262941, -0.77998477, 0.05671934, 0.033889253, -2.9563978,
    0.88960683, -0.44980583, -0.52007324, 0.048948638, 0.32514209,
    -6.4129553, 3.8077362, 0.56695652, 0.071017198, 5.5018158,
    -1.9626614, -0.34950507, 2.4830499, 0.33693412, 0.4366965,
    -0.4496052, 4.5655513, -1.100323, -2.6142988, -0.9866693,
    6.0067482, 0.394243, -0.26413938, 3.6902361, -4.9410615,
    -5.2179823, -1.3120681, 1.9078605, 1.7019941, -0.22031876,
    4.0383296, 2.2260122, 1.9149201, 1.0517087, 1.5966017,
    0.71503288, 2.8193233, 0.67933881, 3.7416115, 3.3591559,
    -1.8144586, -0.090612598, -2.4134445, -0.219465, 0.52822685,
    -3.670917, 0.32494608, -4.2846279, -0.64396828, 0.85289752,
    -4.4223251, 1.5727997, -3.3692346, 0.027973272, 0.061191835,
    1.6783003, -2.2148285, -4.3223734, -2.6331933, -3.7221727,
    -1.2402098, 2.2283425, -0.074013151, -0.67211276, -2.4923341,
    0.12842907, -1.9091744, -2.24827, 3.5922465, -0.89560825,
    -0.45383194, 0.38090637, 0.64149636, -0.41870576, -0.55770171,
    -1.8514881, -0.69146079, -0.3754369, -0.050475389, 0.13151406,
    0.0, 0.0, 0.0
    
};
    
static uint32_t epa_no2_conc[ 6 ] = 
{
    0x00000036, 0x00000065,
    0x00000169, 0x0000028A,
    0x000004E2, 0x00000672
    
};

static uint32_t epa_no2_aqi[ 6 ] = 
{
    0x00000033, 0x00000065,
    0x00000097, 0x000000C9,
    0x0000012D, 0x00000191
    
};

static uint32_t epa_o3_conc[ 6 ] = 
{
    0x0000007D, 0x000000A5,
    0x000000CD, 0x00000195,
    0x000001F9, 0x0000025C
    
};

static uint32_t epa_o3_aqi[ 6 ] = 
{
    0x00000065, 0x00000097,
    0x000000C9, 0x0000012D,
    0x00000191, 0x000001F4
    
};

/**
 * @brief Air Quality 8 ZZMOD4510 d addr configuration.
 */
static uint8_t data_set_4510_continuous_d[ 6 ] = 
{ 
    0x20, 0x05, 0xA0, 0x18, 0xC0, 0x1C 
    
};

/**
 * @brief Air Quality 8 ZZMOD4510 m addr configuration.
 */
static uint8_t data_set_4510_continuous_m[ 1 ] = 
{ 
    0x03 
    
};

/**
 * @brief Air Quality 8 ZZMOD4510 s addr configuration.
 */
static uint8_t data_set_4510_continuous_s[ 30 ] = 
{ 
    0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x01, 0x00, 0x09, 
    0x00, 0x11, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x12, 0x00, 0x03, 
    0x00, 0x0B, 0x00, 0x13, 0x00, 0x04, 0x00, 0x0C, 0x80, 0x14 
    
};

/**
 * @brief Air Quality 8 ZMOD45XX d addr sensor initialization configuration.
 */
static uint8_t data_set_4510i_d[ 2 ] = 
{ 
    0x00, 0xA4 
    
};

/**
 * @brief Air Quality 8 ZMOD45XX m addr sensor initialization configuration.
 */
static uint8_t data_set_4510i_m[ 2 ] = 
{ 
    0xC3, 0xE3 
    
};

/**
 * @brief Air Quality 8 ZMOD45XX s addr sensor initialization configuration.
 */
static uint8_t data_set_4510i_s[ 4 ] = 
{ 
    0x00, 0x00, 0x80, 0x40 
    
};

static uint8_t general_purpose[ 9 ] = 
{
    215, 18, 119, 194, 57, 251, 78, 105, 1
    
};

static float dev_oaq_base_interp ( float conc, uint32_t *epa_conc, uint32_t *epa_aqi, uint8_t imax );

static float dev_oaq_base_classify ( float *rmox, float rmox_mean );

static void dev_reset_delay ( void );

static void dev_cont_run_delay ( void );

static void dev_read_delay ( void );

void airquality8_cfg_setup ( airquality8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRQUALITY8_SET_DEV_ADDR;
}

err_t airquality8_init ( airquality8_t *ctx, airquality8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t airquality8_default_cfg ( airquality8_t *ctx ) 
{
    err_t error_flag = AIRQUALITY8_OK;
    
    airquality8_hw_reset( ctx );

    return error_flag;
}

err_t airquality8_generic_write ( airquality8_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t airquality8_generic_read ( airquality8_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void airquality8_hw_reset ( airquality8_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

uint8_t airquality8_check_interrupt ( airquality8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t airquality8_get_status ( airquality8_t *ctx, uint8_t *status )
{
    return airquality8_generic_read( ctx, AIRQUALITY8_REG_STATUS, status, 1 );
}

err_t airquality8_get_sensor_info ( airquality8_t *ctx, uint8_t *cfg_data, uint8_t *prod_data, uint16_t *pid )
{
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 1 ];
    uint8_t status = 0;
    uint16_t n_cnt = 0;
    err_t err_flag = AIRQUALITY8_OK;
    
    do 
    {
        tx_buf[ 0 ] = DUMMY;
        err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CMD, tx_buf, 1 );
        
        dev_read_delay( );
        
        airquality8_get_status( ctx, &status );
        n_cnt++;
    } 
    while ( ( ( status & 0x80 ) != AIRQUALITY8_OK ) && ( n_cnt < 1000 ) );
    
    err_flag = airquality8_generic_read( ctx, AIRQUALITY8_REG_PID, rx_buf, 2 );
    
    *pid = rx_buf[ 0 ];
    *pid <<= 8;
    *pid |= rx_buf[ 1 ];
    
    err_flag = airquality8_generic_read( ctx, AIRQUALITY8_REG_CONF, cfg_data, 6 );
    
    err_flag = airquality8_generic_read( ctx, AIRQUALITY8_REG_PROD_DATA, prod_data, 5 );
    
    if ( err_flag != AIRQUALITY8_OK )
    {
        err_flag = AIRQUALITY8_ERROR_I2C;
    }
    else if ( n_cnt >= 1000 )
    {
        err_flag = AIRQUALITY8_ERROR_GAS_TIMEOUT;
    }
    
    return err_flag;
}

err_t airquality8_init_sensor ( airquality8_t *ctx, uint16_t *mox_lr, uint16_t *mox_er )
{
    uint8_t buf[ 4 ];
    uint8_t rx_cfg[ 6 ];
    float hspf;
    uint8_t stat;
    uint8_t status;
    uint8_t tx_buf[ 1 ];
    err_t err_flag = AIRQUALITY8_OK;
    
    err_flag = airquality8_generic_read( ctx, 0xB7, &stat, 1 );

    err_flag = airquality8_generic_read( ctx, AIRQUALITY8_REG_CONF, rx_cfg, 6 );

    hspf = ( -( ( float ) rx_cfg[ 2 ] * 256.0 + rx_cfg[ 3 ] ) *
               ( ( rx_cfg[ 4 ] + 640.0 ) * ( rx_cfg[ 5 ] + 80.0 ) - 512000.0 ) )
               / 12288000.0;

    buf[ 0 ] = ( uint8_t ) ( ( uint16_t ) hspf >> 8 );
    buf[ 1 ] = ( uint8_t ) ( ( uint16_t ) hspf & 0x00FF );
    
    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_H, buf, 2 );
    
    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_D, data_set_4510i_d, 2 );

    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_M, data_set_4510i_m, 2 );

    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_S, data_set_4510i_s, 4 );
    
    tx_buf[ 0 ] = 0xC0;
    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CMD, tx_buf, 1 );

    dev_read_delay( );

    err_flag = airquality8_get_status( ctx, &status );
    
    if ( err_flag != AIRQUALITY8_OK )
    {
        err_flag = AIRQUALITY8_ERROR_I2C;
    }
    else if ( ( status & 0x80 ) == 0x80 )
    {
        err_flag = AIRQUALITY8_ERROR_GAS_TIMEOUT;
    }
    else if ( ( hspf < 0.0 ) || (  hspf > 4096.0 ) )
    {
        return AIRQUALITY8_ERROR_INIT_OUT_OF_RANGE;
    }

    err_flag = airquality8_generic_read( ctx, 0x97, buf, 4 );

    *mox_lr = buf[ 0 ];
    *mox_lr <<= 8;
    *mox_lr |= buf[ 1 ];
    
    *mox_er = buf[ 2 ];
    *mox_er <<= 8;
    *mox_er |= buf[ 3 ];

    return err_flag;
}

err_t airquality8_init_measurement ( airquality8_t *ctx )
{
    uint8_t buf[ 4 ];
    uint8_t rx_cfg[ 6 ];
    uint8_t stat;
    float hspf;
    err_t err_flag = AIRQUALITY8_OK;
    
    err_flag = airquality8_generic_read( ctx, 0xB7, &stat, 1 );

    err_flag|= airquality8_generic_read( ctx, AIRQUALITY8_REG_CONF, rx_cfg, 6 );
    
    hspf = ( -( ( float ) rx_cfg[ 2 ] * 256.0 + rx_cfg[ 3 ] ) *
              ( ( rx_cfg[ 4 ] + 640.0 ) * ( rx_cfg[ 5 ] + 80.0 ) - 512000.0 ) )
                 / 12288000.0;

    buf[ 0 ] = ( uint8_t ) ( ( uint16_t ) hspf >> 8 );
    buf[ 1 ] = ( uint8_t ) ( ( uint16_t ) hspf & 0x00FF );

    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_H, buf, 2 );
    
    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_D, data_set_4510_continuous_d, 6 );
    
    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_M, data_set_4510_continuous_m, 1 );
    
    err_flag = airquality8_generic_write( ctx, AIRQUALITY8_REG_CFG_S, data_set_4510_continuous_s, 30 );

    if ( err_flag != AIRQUALITY8_OK )
    {
        err_flag = AIRQUALITY8_ERROR_I2C;
    }
    else if ( ( hspf < 0.0 ) || (  hspf > 4096.0 ) )
    {
        err_flag = AIRQUALITY8_ERROR_INIT_OUT_OF_RANGE;
    }

    return err_flag;
}

err_t airquality8_start_measurement ( airquality8_t *ctx )
{
    uint8_t tx_buf[ 1 ];
    err_t err_flag = AIRQUALITY8_OK;

    tx_buf[ 0 ] = 0xC0;
    err_flag |= airquality8_generic_write( ctx, AIRQUALITY8_REG_CMD, tx_buf, 1 );
    
    if ( err_flag != AIRQUALITY8_OK )
    {
        err_flag = AIRQUALITY8_ERROR_I2C;
    }

    return err_flag;
}

err_t airquality8_read_rmox ( airquality8_t *ctx, float *rmox, uint16_t mox_lr, uint16_t mox_er )
{
    uint8_t buf[ 2 ];
    uint16_t adc_result;
    uint8_t rx_cfg[ 6 ];
    float temp;
    err_t err_flag = AIRQUALITY8_OK;
    
    err_flag = airquality8_generic_read( ctx, AIRQUALITY8_REG_CONF, rx_cfg, 6 );
    
    err_flag = airquality8_generic_read( ctx, 0x99, buf, 2 );

    adc_result = buf[ 0 ];
    adc_result <<= 8;
    adc_result |= buf[ 1 ];
    
    err_flag = airquality8_generic_read( ctx, 0xB7, buf, 1 );

    if ( ( adc_result - mox_lr ) < 0 )
    {
        temp = 1e-3;
    }
    else if ( ( mox_er - adc_result ) <= 0 )
    {
        temp = 1e12;
    }
    else
    {
        temp = ( float ) rx_cfg[ 0 ];
        temp *= 1000.0;
        temp *= ( float )( adc_result - mox_lr );
        temp /= ( float )( mox_er - adc_result );
    }

    *rmox = temp;
    
    if ( err_flag != AIRQUALITY8_OK )
    {
        err_flag = AIRQUALITY8_ERROR_I2C;
    }
    else if ( buf[ 0 ] != 0 )
    {
        if ( buf[ 0 ] & AIRQUALITY8_STATUS_ACCESS_CONFLICT_MASK )
        {
            err_flag = AIRQUALITY8_ERROR_ACCESS_CONFLICT;
        }
        else if ( buf[ 0 ] & AIRQUALITY8_STATUS_POR_EVENT_MASK )
        {
            err_flag = AIRQUALITY8_ERROR_POR_EVENT;
        }
    }

    return err_flag;
}

float airquality8_calc_oaq ( float *rmox, uint8_t rcda_strategy, uint8_t gas_detection_strategy )
{
    float rcda_22;
    float rcda_42;
    float trim_b;
    float trim_beta2;
    float rmox_valid[ 12 ];
    float rmox_mean = 0.0;
    float prob_no2 = 0;
    float conc_no2 = 0;
    float conc_o3 = 0; 
    float aqi_no2 = 0; 
    float aqi_o3 = 0;
    
    trim_b  = pow( 10.0, ( ( ( general_purpose[ 2 ] << 8 ) | general_purpose[ 3 ] ) / 65536.0 ) * 4.0 - 1.5 );
    trim_b *= pow( 10.0, ( ( ( general_purpose[ 0 ] << 8 ) | general_purpose[ 1 ] ) / 65536.0 ) * 5.0 + 4.0 );
    
    trim_beta2 = ( ( ( general_purpose[ 4 ] << 8 ) | general_purpose[ 5 ] ) / 65536.0 ) * 3.0;

    for ( uint8_t n_cnt = 0; n_cnt < 12; n_cnt++ )
    {
        if ( rmox[ n_cnt + 3 ] > 1e12 )
        {
            rmox_valid[ n_cnt ] = 1e12;
        }
        else if ( rmox[ n_cnt + 3 ] < 100.0 )
        {
            rmox_valid[ n_cnt ] = 100.0;
        }
        else
        {
            rmox_valid[ n_cnt ] = rmox[ n_cnt + 3 ];    
        }
            
        rmox_mean += rmox_valid[ n_cnt ];
    }

    rmox_mean /= 12.0;

    if ( rcda_strategy == AIRQUALITY8_RCDA_STRATEGY_SET )
    {
        rcda_22 = rmox_valid[ 5 ];
        rcda_42 = rmox_valid[ 11 ];
    }
    else if ( rcda_strategy == AIRQUALITY8_RCDA_STRATEGY_ADJ )
    {
        float m1;

        if ( rmox_valid[ 5 ] <= rcda_22 )
        {
            m1 = D_FALLING_M1;    
        }
        else
        {
            m1 = D_RISING_M1;
        }
            
        rcda_22 *= pow( rmox_valid[ 5 ] / rcda_22, m1 );

        if ( rmox_valid[ 11 ] <= rcda_42 )
        {
            m1 = D_FALLING_M1;    
        }
        else
        {
            m1 = D_RISING_M1;
        }
            
        rcda_42 *= pow( rmox_valid[ 11 ] / rcda_42, m1 );
    }

    float new_conc_no2 = ( rmox_valid[ 5 ] - rcda_22 ) / trim_b;

    if ( new_conc_no2 < 0.0 )
    {
        new_conc_no2 = 0.0;    
    }

    new_conc_no2 = pow( new_conc_no2, 1.0 / trim_beta2 );

    if ( general_purpose[ 8 ] > 0 )
    {
        new_conc_no2 *= 100.0;    
    }
    else
    {
        new_conc_no2 *= 250.f;    
    }

    conc_no2 = ( new_conc_no2 - conc_no2 ) * 0.18126924 + conc_no2;
    aqi_no2 = dev_oaq_base_interp( conc_no2, epa_no2_conc, epa_no2_aqi, 7 );

    float new_conc_o3 = ( rmox_valid[ 11 ] - rcda_42 ) / 56234132.0;

    if ( new_conc_o3 < 0.0 )
    {
        new_conc_o3 = 0.0;    
    }

    new_conc_o3 *= 50.0;

    conc_o3 = ( new_conc_o3 - conc_o3 ) * 0.18126924 + conc_o3;
    aqi_o3 = dev_oaq_base_interp( conc_o3, epa_o3_conc, epa_o3_aqi, 6 );

    float mult;

    if ( ( gas_detection_strategy == AIRQUALITY8_GAS_DETECTION_STRATEGY_FORCE_O3 ) || ( conc_no2 >= 10000.0 ) )
    {
        mult = 0.0;
    }
    else if ( gas_detection_strategy == AIRQUALITY8_GAS_DETECTION_STRATEGY_FORCE_NO2 )
    {
        mult = 1.0;
    }
    else
    {
        if ( ( ( uint8_t )dev_oaq_base_classify( rmox_valid, rmox_mean ) ) == 0 )
        {
            mult = 1.0;    
        }
        else
        {
            mult = 0.0;    
        }
    }

    prob_no2 += ( mult - prob_no2 ) * D_CLASS_M1;

    return ( float )( ( aqi_no2 - aqi_o3 ) * prob_no2 + aqi_o3 );
}

uint8_t raq_check_interrupt ( airquality8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static float dev_oaq_base_interp ( float conc, uint32_t *epa_conc, uint32_t *epa_aqi, uint8_t imax )
{
    for ( uint8_t n_cnt = 0; n_cnt < imax; n_cnt++ )
    {
        if ( epa_conc[ n_cnt ] >= conc )
        {
            if  ( n_cnt )
            {
                return ( float )epa_aqi[ n_cnt - 1 ] + ( float )( epa_aqi[ n_cnt ] - epa_aqi[ n_cnt - 1 ] ) / ( float )( epa_conc[ n_cnt ] - epa_conc[ n_cnt - 1 ] ) * ( conc - ( float )epa_conc[ n_cnt - 1 ] );    
            }
            else
            {
                return ( float )epa_aqi[ 0 ] / ( float )epa_conc[ 0 ] * conc;    
            }
        }
    }

    return epa_aqi[ imax - 1 ];
}

static float dev_oaq_base_classify ( float *rmox, float rmox_mean )
{
    float rmox_scaled[ 8 ];
    float rmox_div_by_mean[ 11 ];
    float res = 0.0;
    uint8_t svc_poly_index = 0;
    
    for ( uint8_t n_cnt = 0; n_cnt < 11; n_cnt++ )
    {
        rmox_div_by_mean[ n_cnt ] = rmox[ n_cnt + 1 ] / rmox_mean;
    }
        
    for ( uint8_t cnt_i = 0; cnt_i < 8; cnt_i++ )
    {
        rmox_scaled[ cnt_i ] = scaler_and_pca_o[ cnt_i ];

        for ( uint8_t cnt_j = 0; cnt_j < 11; cnt_j++ )
        {
            rmox_scaled[ cnt_j ] += rmox_div_by_mean[ cnt_j ] * scaler_and_pca_g[ cnt_j + ( 11 * cnt_i ) ];
        }
    }

    for ( uint8_t cnt_i = 0; cnt_i < 9; cnt_i++ )
    {
        float a;

        if ( cnt_i )
        {
            a = rmox_scaled[ cnt_i - 1 ];
        }
        else
        {
            a = 1.0;    
        }
            
        for ( uint8_t cnt_j = 0; cnt_j < cnt_i + 1; cnt_j++ )
        {
            float b;

            if ( cnt_j )
                b = rmox_scaled[ cnt_j - 1 ] * a;
            else
                b = a;

            for( uint8_t cnt_k = 0; cnt_k < cnt_j + 1; cnt_k++ )
            {
                float c;

                if ( cnt_k )
                    c = rmox_scaled[ cnt_k - 1 ] * b;
                else
                    c = b;

                res += c * svc_poly_coeffs[ svc_poly_index++ ];
            }
        }
    }

    return res;
}

static void dev_reset_delay ( void )
{
    Delay_100ms( );
}

static void dev_cont_run_delay ( void )
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_read_delay ( void )
{
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

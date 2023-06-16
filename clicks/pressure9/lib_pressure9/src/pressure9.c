/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "pressure9.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE9_DUMMY                             0
#define TEMPERATURE_DATA_READY                      0x20
#define PRESSURE_DATA_READY                         0x10
#define PRESSURE9_3_BIT_DATA                        0x07
#define PRESSURE9_7TH_BIT_HIGH                      0x80
#define PRESSURE9_1ST_BIT_HIGH                      0x01
#define PRESSURE9_UPPER_NIBLE                       0xF0
#define PRESSURE9_LOWER_NIBLE                       0x0F
#define PRESSURE9_LOWER_7_BITS_HIGH                 0x7F
#define PRESSURE9_LOWER_6_BITS_HIGH                 0x3F
#define PRESSURE9_UPPER_TWO_BITS_HIGH               0xC0
#define CAL_A0                                      5030
#define CAL_TREF                                    27
#define CAL_VBE_TARGET                              0.687027
#define CAL_ALFA                                    9.45
#define CAL_TC_VBE                                 -1.735E-3
#define CAL_KPTAT_CORNER                           -0.8
#define CAL_KPTAT_CURVATURE                         0.039
#define PRESSURE9_APSOLUTE_ZERO                     273.15 
#define PRESSURE9_PRESS_RES_0                       524288ul
#define PRESSURE9_PRESS_RES_1                       1572864ul
#define PRESSURE9_PRESS_RES_2                       3670016ul
#define PRESSURE9_PRESS_RES_3                       7864320ul
#define PRESSURE9_PRESS_RES_4                       253952ul
#define PRESSURE9_PRESS_RES_5                       516096ul
#define PRESSURE9_PRESS_RES_6                       1040384ul
#define PRESSURE9_PRESS_RES_7                       2088960ul
#define PRESSURE9_PRESS_SEL_0                       0
#define PRESSURE9_PRESS_SEL_1                       1
#define PRESSURE9_PRESS_SEL_2                       2
#define PRESSURE9_PRESS_SEL_3                       3
#define PRESSURE9_PRESS_SEL_4                       4
#define PRESSURE9_PRESS_SEL_5                       5
#define PRESSURE9_PRESS_SEL_6                       6
#define PRESSURE9_PRESS_SEL_7                       7
#define PRESSURE9_TEMP_CAL_COEFF_VAL_T_VBE_1        1.05031E-4
#define PRESSURE9_TEMP_CAL_COEFF_VAL_T_VBE_2        0.463232422
#define PRESSURE9_TEMP_CAL_COEFF_VAL_T_DVBE_1       1.25885E-5 
#define PRESSURE9_TEMP_CAL_COEFF_VAL_T_DVBE_2       0.04027621 
#define PRESSURE9_TEMP_CAL_COEFF_VAL_T_GAIN_1       8.4375E-5 
#define PRESSURE9_TEMP_CAL_COEFF_VAL_T_GAIN_2       0.675
#define PRESSURE9_TEMP_CALC_COEF                    1048576ul
#define PRESSURE9_TEMP_CAL_COEFF_MTP                8.5
#define PRESSURE9_TEMP_CALC_COEF_CORR               8.8

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void pressure9_i2c_write ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void pressure9_i2c_read ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void pressure9_spi_write ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void pressure9_spi_read ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void press_coefficient_buf ( pressure9_t *ctx, uint8_t *data_out );
static void temp_coefficient_buf ( pressure9_t *ctx, uint8_t *data_out );
static void get_twos_complement ( int32_t *raw, uint8_t length );
static void calc_ab_coefficient ( pressure9_t *ctx );
static float calc_pressure_calibration ( pressure9_t *ctx, float press_calc, float temp_calc );
static void update_presure_rate ( pressure9_t *ctx, uint8_t res );
static err_t wait_data_rdy ( pressure9_t *ctx, uint8_t tp );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure9_cfg_setup ( pressure9_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PRESSURE9_DEV_SLAVE_ADR_GND;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = PRESSURE9_MASTER_I2C;
}

err_t pressure9_init ( pressure9_t *ctx, pressure9_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( PRESSURE9_MASTER_I2C == ctx->master_sel )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed   = cfg->i2c_speed;
        i2c_cfg.scl     = cfg->scl;
        i2c_cfg.sda     = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
        {
            return PRESSURE9_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        
        // Enter I2C mode
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );
        ctx->read_f = pressure9_i2c_read;
        ctx->write_f = pressure9_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        spi_cfg.default_write_data = PRESSURE9_DUMMY;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
        {
            return  PRESSURE9_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE9_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );   
        
        // Enter SPI mode
        ctx->read_f = pressure9_spi_read;
        ctx->write_f = pressure9_spi_write;
    }

    return PRESSURE9_OK;
}

void pressure9_default_cfg ( pressure9_t *ctx )
{
    ctx->pressure_res = 7864320ul;
    pressure9_configuration ( ctx, PRESSURE9_REG_PRESSURE_CONFIG, 
                              PRESSURE9_PTCFG_RATE_2_SAMPLES_SEC | PRESSURE9_PTCFG_RES_X2_512_SAMPLES );
    pressure9_configuration ( ctx, PRESSURE9_REG_TEMPERATURE_CONFIG, 
                              PRESSURE9_PTCFG_RATE_2_SAMPLES_SEC | PRESSURE9_PTCFG_RES_X8_2048_SAMPLES);
    pressure9_configuration ( ctx, PRESSURE9_REG_MEASUREMENT_CONFIG, PRESSURE9_MCFG_TEMP_AND_PRESS_CONT );
    
    pressure9_configuration ( ctx, PRESSURE9_REG_CONFIGURATION, 
                              PRESSURE9_CFG_SINT_PRESS_AND_TEMP_INT_EN | PRESSURE9_CFG_PINT_INT_ACTIVE_HIGH );
    
    pressure9_update_calc_coef ( ctx ); 
}

void pressure9_generic_write ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void pressure9_generic_read ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void pressure9_configuration ( pressure9_t *ctx, uint8_t reg_adr, uint8_t data_in )
{
    uint8_t tmp = 0;
    
    if ( PRESSURE9_REG_PRESSURE_CONFIG == reg_adr )
    {
         tmp = data_in & PRESSURE9_3_BIT_DATA;
         update_presure_rate( ctx, tmp );
         pressure9_generic_write( ctx, reg_adr, &data_in, 1 );
    }
    else if ( PRESSURE9_REG_TEMPERATURE_CONFIG == reg_adr )
    {
        tmp = data_in | PRESSURE9_7TH_BIT_HIGH;
        pressure9_generic_write( ctx, reg_adr, &tmp, 1 );
    }
    else
    {
        pressure9_generic_write( ctx, reg_adr, &data_in, 1 );
    }
}

int32_t pressure9_get_coefficients ( pressure9_t *ctx, uint8_t coeff )
{
    int32_t tmp = 0;

    switch ( coeff )
    {
        case PRESSURE9_COEFF_CAL_00:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_00 = ctx->press_buf[ 0 ];
            ctx->press_coef.cal_00 <<= 8;
            ctx->press_coef.cal_00 |= ctx->press_buf[ 1 ];
            ctx->press_coef.cal_00 <<= 4;
            ctx->press_buf[ 2 ] &= PRESSURE9_UPPER_NIBLE;
            ctx->press_buf[ 2 ] >>= 4;
            ctx->press_coef.cal_00 |= ctx->press_buf[ 2 ];
            
            get_twos_complement( &ctx->press_coef.cal_00, 20 );
            tmp = ctx->press_coef.cal_00;
            break;
        }
        case PRESSURE9_COEFF_CAL_10:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_10 = ctx->press_buf[ 2 ] & PRESSURE9_LOWER_NIBLE;
            ctx->press_coef.cal_10 <<= 8;
            ctx->press_coef.cal_10 |= ctx->press_buf[ 3 ];
            ctx->press_coef.cal_10 <<= 8;
            ctx->press_coef.cal_10 |= ctx->press_buf[ 4 ];

            get_twos_complement( &ctx->press_coef.cal_10, 20 );
            tmp = ctx->press_coef.cal_10;
            break;
        }
        case PRESSURE9_COEFF_CAL_01:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_01 = ctx->press_buf[ 5 ];
            ctx->press_coef.cal_01 <<= 8;
            ctx->press_coef.cal_01 |= ctx->press_buf[ 6 ];
            ctx->press_coef.cal_01 <<= 4;
            ctx->press_coef.cal_01 |= ( ctx->press_buf[ 7 ] & PRESSURE9_UPPER_NIBLE ) >> 4;

            get_twos_complement( &ctx->press_coef.cal_01, 20 );
            tmp = ctx->press_coef.cal_01;
            break;
        }
        case PRESSURE9_COEFF_CAL_02:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_02 = ctx->press_buf[ 7 ] & PRESSURE9_LOWER_NIBLE; 
            ctx->press_coef.cal_02 <<= 8;
            ctx->press_coef.cal_02 |= ctx->press_buf[ 8 ];
            ctx->press_coef.cal_02 <<= 8;
            ctx->press_coef.cal_02 |= ctx->press_buf[ 9 ];

            get_twos_complement( &ctx->press_coef.cal_02, 20 );
            
            tmp = ctx->press_coef.cal_02;
            break;
        }
        case PRESSURE9_COEFF_CAL_20:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_20 = ctx->press_buf[ 10 ] & PRESSURE9_LOWER_7_BITS_HIGH;
            ctx->press_coef.cal_20 <<= 8;
            ctx->press_coef.cal_20 |= ctx->press_buf[ 11 ];

            get_twos_complement( &ctx->press_coef.cal_20, 15 );
            
            tmp = ctx->press_coef.cal_20;
            break;
        }
        case PRESSURE9_COEFF_CAL_30:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_30 = ctx->press_buf[ 12 ] & PRESSURE9_LOWER_NIBLE;
            ctx->press_coef.cal_30 <<= 8;
            ctx->press_coef.cal_30 |= ctx->press_buf[ 13 ];

            get_twos_complement( &ctx->press_coef.cal_30, 12 );
            
            tmp = ctx->press_coef.cal_30;
            break;
        }
        case PRESSURE9_COEFF_CAL_11:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_11 = ctx->press_buf[ 14 ];
            ctx->press_coef.cal_11 <<= 8;
            ctx->press_coef.cal_11 |= ctx->press_buf[ 15 ];
            ctx->press_coef.cal_11 <<= 1;
            ctx->press_coef.cal_11 |= ( ctx->press_buf[ 16 ] & PRESSURE9_7TH_BIT_HIGH ) >> 7;

            get_twos_complement( &ctx->press_coef.cal_11, 17 );
            
            tmp = ctx->press_coef.cal_11;
            break;
        }
        case PRESSURE9_COEFF_CAL_12:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_12 = ctx->press_buf[ 16 ] & PRESSURE9_LOWER_7_BITS_HIGH;
            ctx->press_coef.cal_12 <<= 8;
            ctx->press_coef.cal_12 |= ctx->press_buf[ 17 ];
            ctx->press_coef.cal_12 <<= 2;
            ctx->press_coef.cal_12 |= ( ctx->press_buf[ 18 ] & PRESSURE9_UPPER_TWO_BITS_HIGH ) >> 6;

            get_twos_complement( &ctx->press_coef.cal_12, 17 );
            
            tmp = ctx->press_coef.cal_12;
            break;
        }
        case PRESSURE9_COEFF_CAL_21:
        {
            press_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->press_coef.cal_21 = ctx->press_buf[ 18 ] & PRESSURE9_LOWER_6_BITS_HIGH;
            ctx->press_coef.cal_21 <<= 8;
            ctx->press_coef.cal_21 |= ctx->press_buf[ 19 ];

            get_twos_complement( &ctx->press_coef.cal_21, 14 );
            
            tmp = ctx->press_coef.cal_21;
            break;
        }
        case PRESSURE9_COEFF_T_GAIN:
        {
            temp_coefficient_buf( ctx, ctx->press_buf );
            
            ctx->temp_coef.t_gain = ctx->temp_buf[ 0 ];
            
            get_twos_complement( &ctx->temp_coef.t_gain, 8 );

            tmp = ctx->temp_coef.t_gain;
            break;
        }
        case PRESSURE9_COEFF_T_DVBE:
        {
            temp_coefficient_buf( ctx, ctx->temp_buf );
            
            ctx->temp_coef.t_dvbe = ( uint32_t )( ctx->temp_buf[ 1 ] >> 1 );
            
            get_twos_complement( &ctx->temp_coef.t_dvbe, 7 );

            tmp = ctx->temp_coef.t_dvbe;
            break;
        }
        case PRESSURE9_COEFF_T_VBE:
        {
            temp_coefficient_buf( ctx, ctx->temp_buf );
            
            ctx->temp_coef.t_vbe  = ( int32_t )( ctx->temp_buf[ 2 ] );
            ctx->temp_coef.t_vbe <<= 1;
            ctx->temp_coef.t_vbe |= ( int32_t )( ctx->temp_buf[ 1 ] & PRESSURE9_1ST_BIT_HIGH );

            get_twos_complement( &ctx->temp_coef.t_vbe, 9 );
            
            tmp = ctx->temp_coef.t_vbe;
            break;
        }
    }
    return tmp;
}

void pressure9_update_calc_coef ( pressure9_t *ctx )
{
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C00 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C01 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C02 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C10 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C20 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C30 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C11 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C12 );
    pressure9_get_coefficients( ctx, PRESSURE9_PRESSURE_COEFFICIENT_C21 );
 
    pressure9_get_coefficients( ctx, PRESSURE9_TEMP_COEFFICIENT_T_GAIN );
    pressure9_get_coefficients( ctx, PRESSURE9_TEMP_COEFFICIENT_T_DVBE );
    pressure9_get_coefficients( ctx, PRESSURE9_TEMP_COEFFICIENT_T_VBE );

    calc_ab_coefficient( ctx );
}

int32_t pressure9_get_temperature_raw ( pressure9_t *ctx )
{
    int32_t temp_raw = 0;
    uint8_t rd_buf[ 3 ] = { 0 };
    
    wait_data_rdy( ctx, TEMPERATURE_DATA_READY );
    pressure9_generic_read( ctx, PRESSURE9_REG_TEMPERATRE_DATA_B2, &rd_buf[ 0 ], 1 );
    pressure9_generic_read(  ctx, PRESSURE9_REG_TEMPERATRE_DATA_B1, &rd_buf[ 1 ], 1 );
    pressure9_generic_read(  ctx, PRESSURE9_REG_TEMPERATRE_DATA_B0, &rd_buf[ 2 ], 1 );
    
    temp_raw = rd_buf[ 0 ];
    temp_raw <<= 8;
    temp_raw |= rd_buf[ 1 ];
    temp_raw <<= 8;
    temp_raw |= rd_buf[ 2 ];
    
    get_twos_complement( &temp_raw, 24 );
    
    return temp_raw;
}

int32_t pressure9_get_pressure_raw ( pressure9_t *ctx )
{
    int32_t press_raw = 0;
    uint8_t rd_buf[ 3 ] = { 0 };

    wait_data_rdy( ctx, PRESSURE_DATA_READY );
    
    pressure9_generic_read( ctx, PRESSURE9_REG_PRESSURE_DATA_B2, &rd_buf[ 0 ], 1 );
    pressure9_generic_read( ctx, PRESSURE9_REG_PRESSURE_DATA_B1, &rd_buf[ 1 ], 1 );
    pressure9_generic_read( ctx, PRESSURE9_REG_PRESSURE_DATA_B0, &rd_buf[ 2 ], 1 );

    press_raw = rd_buf[ 0 ];
    press_raw <<= 8;
    press_raw |= rd_buf[ 1 ];
    press_raw <<= 8;
    press_raw |= rd_buf[ 2 ];
    get_twos_complement( &press_raw, 24 );

    return press_raw;
}

float pressure9_get_pressure_data ( pressure9_t *ctx )
{
    float press_calc = 0;
    float temp_calc = 0;
    
    press_calc = pressure9_get_pressure_raw( ctx );
    press_calc /= ctx->pressure_res;
    
    temp_calc = pressure9_get_temperature_raw( ctx );
    temp_calc /= PRESSURE9_TEMP_CALC_COEF;

    return ( float )( calc_pressure_calibration( ctx, press_calc, temp_calc ) / 100 );
}

float pressure9_get_temperature_data ( pressure9_t *ctx )
{
    float temp_calc = 0;
    float temp_out = 0;
    
    temp_calc = pressure9_get_temperature_raw( ctx );
    temp_calc /= PRESSURE9_TEMP_CALC_COEF;

    temp_out = ctx->temp_coef.ap;
    temp_out *= ( temp_calc / ( 1 + CAL_ALFA * temp_calc ) );
    temp_out += ctx->temp_coef.bp;
    
    return temp_out;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pressure9_i2c_write ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );      
}

static void pressure9_i2c_read ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void pressure9_spi_write ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &reg, 1 );
    spi_master_write( &ctx->spi, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );      
}

static void pressure9_spi_read ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t reg_read = reg | 0x80;
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &reg_read, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void press_coefficient_buf ( pressure9_t *ctx, uint8_t *data_out )
{
    pressure9_generic_read ( ctx, PRESSURE9_COEFF_REG_1, data_out, 20 );
}

static void temp_coefficient_buf ( pressure9_t *ctx, uint8_t *data_out )
{
    pressure9_generic_read( ctx, PRESSURE9_T_GAIN_COEFF, data_out, 3 );
}

static void get_twos_complement ( int32_t *raw, uint8_t length )
{
    if ( *raw & ( 1ul << ( length - 1 ) ) )
    {
        *raw -= ( 1ul << length );
    }
}

static void calc_ab_coefficient ( pressure9_t *ctx )
{
    ctx->temp_coef.vbe = ctx->temp_coef.t_vbe * PRESSURE9_TEMP_CAL_COEFF_VAL_T_VBE_1 + 
                         PRESSURE9_TEMP_CAL_COEFF_VAL_T_VBE_2;
    ctx->temp_coef.dvbe = ctx->temp_coef.t_dvbe * PRESSURE9_TEMP_CAL_COEFF_VAL_T_DVBE_1 + 
                          PRESSURE9_TEMP_CAL_COEFF_VAL_T_DVBE_2;
    ctx->temp_coef.adc_val = ctx->temp_coef.t_gain * PRESSURE9_TEMP_CAL_COEFF_VAL_T_GAIN_1 + 
                             PRESSURE9_TEMP_CAL_COEFF_VAL_T_GAIN_2;
    
    ctx->temp_coef.vbe_cal = ctx->temp_coef.vbe / ctx->temp_coef.adc_val;
    ctx->temp_coef.dvbe_cal = ctx->temp_coef.dvbe / ctx->temp_coef.adc_val;

    ctx->temp_coef.t_cal = CAL_A0 * ctx->temp_coef.dvbe_cal - PRESSURE9_APSOLUTE_ZERO;
    
    ctx->temp_coef.vbe_cal_t_ref = ctx->temp_coef.vbe_cal - ( ctx->temp_coef.t_cal - CAL_TREF ) * CAL_TC_VBE;
    
    ctx->temp_coef.kptat = ( CAL_VBE_TARGET - ctx->temp_coef.vbe_cal_t_ref ) * CAL_KPTAT_CORNER + CAL_KPTAT_CURVATURE;
    
    ctx->temp_coef.ap = CAL_A0 * ( ctx->temp_coef.vbe_cal + CAL_ALFA * ctx->temp_coef.dvbe_cal ) * 
                        ( 1 + ctx->temp_coef.kptat );

    ctx->temp_coef.bp = ( -PRESSURE9_APSOLUTE_ZERO ) * ( 1 + ctx->temp_coef.kptat ) - 
                        ctx->temp_coef.kptat * ctx->temp_coef.t_cal;
}

static float calc_pressure_calibration ( pressure9_t *ctx, float press_calc, float temp_calc )
{
    float temp_scaled = 0;
    float press_scaled = 0;
    
    temp_scaled = temp_calc;
    temp_scaled *= PRESSURE9_TEMP_CAL_COEFF_MTP;
    temp_scaled /= ( temp_calc * PRESSURE9_TEMP_CALC_COEF_CORR + 1 );

    press_scaled = ctx->press_coef.cal_00;
    press_scaled += ( float )( ctx->press_coef.cal_10 * press_calc );
    press_scaled += ( float )( ctx->press_coef.cal_01 * temp_scaled );
    press_scaled += ( float )( ctx->press_coef.cal_20 * press_calc * press_calc );
    press_scaled += ( float )( ctx->press_coef.cal_02 * temp_scaled * temp_scaled );
    press_scaled += ( float )( ctx->press_coef.cal_30 * press_calc * press_calc * press_calc );
    press_scaled += ( float )( ctx->press_coef.cal_11 * press_calc * temp_scaled );
    press_scaled += ( float )( ctx->press_coef.cal_12 * press_calc * temp_scaled * temp_scaled );
    press_scaled += ( float )( ctx->press_coef.cal_12 * press_calc * press_calc * temp_scaled );

    return press_scaled;
}

static void update_presure_rate ( pressure9_t *ctx, uint8_t res )
{
    switch ( res )
    {
        case PRESSURE9_PRESS_SEL_0:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_0;
            break;
        }
        case PRESSURE9_PRESS_SEL_1:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_1;
            break;
        }
        case PRESSURE9_PRESS_SEL_2:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_2;
            break;
        }
        case PRESSURE9_PRESS_SEL_3:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_3;
            break;
        }
        case PRESSURE9_PRESS_SEL_4:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_4;
            break;
        }
        case PRESSURE9_PRESS_SEL_5:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_5;
            break;
        }
        case PRESSURE9_PRESS_SEL_6:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_6;
            break;
        }
        case PRESSURE9_PRESS_SEL_7:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_7;
            break;
        }
        default:
        {
            ctx->pressure_res = PRESSURE9_PRESS_RES_3;
            break;
        }
    }
}

static err_t wait_data_rdy ( pressure9_t *ctx, uint8_t tp )
{
    uint8_t reg_data = 0;
    uint8_t timeout_cnt = 0;
    do
    {
        timeout_cnt++;
        Delay_10ms( );
        
        if ( timeout_cnt > 20 )
        {
            return PRESSURE9_ERROR;
        }
        
        pressure9_generic_read ( ctx, PRESSURE9_REG_MEASUREMENT_CONFIG, &reg_data, 1 );
        
    } while ( 0 == ( reg_data & tp ) );
    
    return PRESSURE9_OK;
}

// ------------------------------------------------------------------------- END


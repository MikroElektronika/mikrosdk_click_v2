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
 * @file pressure22.c
 * @brief Pressure 22 Click Driver.
 */

#include "pressure22.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                    0x00

/**
 * @brief Calculate crc4 function.
 * @details This function calculate 4-bit crc (crc4).
 * @param[in] prom : PROM data.
 * @return 4-bit crc.
 * @note None.
 */
static uint8_t pressure22_calc_crc4 ( uint16_t *prom );

/**
 * @brief Conversion time delay for ODR 256.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 256 (OSR).
 * @return Nothing.
 * @note The delay is 0.56 milliseconds.
 */
static void pressure22_delay_odr_256 ( void );

/**
 * @brief Conversion time delay for ODR 512.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 512 (OSR).
 * @return Nothing.
 * @note The delay is 1.10 milliseconds.
 */
static void pressure22_delay_odr_512 ( void );

/**
 * @brief Conversion time delay for ODR 1024.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 1024 (OSR).
 * @return Nothing.
 * @note The delay is 2.17 milliseconds.
 */
static void pressure22_delay_odr_1024 ( void );

/**
 * @brief Conversion time delay for ODR 2048.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 2048 (OSR).
 * @return Nothing.
 * @note The delay is 4.32 milliseconds.
 */
static void pressure22_delay_odr_2048 ( void );

/**
 * @brief Conversion time delay for ODR 4096.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 4096 (OSR).
 * @return Nothing.
 * @note The delay is 8.61 milliseconds.
 */
static void pressure22_delay_odr_4096 ( void );

/**
 * @brief Conversion time delay for ODR 8192.
 * @details This function is used for delay 
 * when the ADC time conversion condition is 8192 (OSR).
 * @return Nothing.
 * @note The delay is 17.2 milliseconds.
 */
static void pressure22_delay_odr_8192 ( void );

/**
 * @brief Array of function pointers.
 * @details This function is an array 
 * of conversion time delay function pointers.
 * @return Nothing.
 * @note None.
 */
static void ( *delay_ptr[ 6 ] ) ( void ) = 
{
    pressure22_delay_odr_256,
    pressure22_delay_odr_512,
    pressure22_delay_odr_1024,
    pressure22_delay_odr_2048,
    pressure22_delay_odr_4096,
    pressure22_delay_odr_8192
};

void pressure22_cfg_setup ( pressure22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE22_DEVICE_ADDRESS;
}

err_t pressure22_init ( pressure22_t *ctx, pressure22_cfg_t *cfg ) 
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

err_t pressure22_default_cfg ( pressure22_t *ctx ) 
{
    err_t err_flag = pressure22_sw_reset( ctx );
    Delay_10ms( );
    err_flag |= pressure22_get_calibration_data( ctx );
    Delay_10ms( );
    err_flag |= pressure22_check_data_validity( ctx );
    Delay_10ms( );
    pressure22_set_conversion( ctx, PRESSURE22_CMD_PRESS_OSR_4096, PRESSURE22_CMD_TEMP_OSR_8192 );
    Delay_10ms( );
    return err_flag;
}

err_t pressure22_generic_write ( pressure22_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { DUMMY };
    data_buf[ 0 ] = cmd;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t pressure22_generic_read ( pressure22_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, len );
}

err_t pressure22_set_command ( pressure22_t *ctx, uint8_t cmd ) 
{
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t pressure22_sw_reset ( pressure22_t *ctx ) 
{
    return pressure22_set_command( ctx, PRESSURE22_CMD_RESET );
}

err_t pressure22_get_adc_data ( pressure22_t *ctx, uint32_t *adc ) 
{
    uint8_t data_buf[ 3 ] = { DUMMY };  
    err_t err_flag = pressure22_generic_read( ctx, PRESSURE22_CMD_ADC_READ, data_buf, 3 );
    *adc = data_buf[ 0 ];
    *adc <<= 8;
    *adc |= data_buf[ 1 ];
    *adc <<= 8;
    *adc |= data_buf[ 2 ];
    return err_flag;
}

err_t pressure22_get_prom_data ( pressure22_t *ctx, uint8_t cmd_prom, uint16_t *prom ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };  
    err_t err_flag = pressure22_generic_read( ctx, cmd_prom, data_buf, 2 );
    *prom = data_buf[ 0 ];
    *prom <<= 8;
    *prom |= data_buf[ 1 ];
    return err_flag;
}

err_t pressure22_get_calibration_data ( pressure22_t *ctx ) 
{
    err_t err_flag = pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_VERSION, &ctx->prom_pt );
    ctx->prom_crc = ( uint8_t ) ( ( ctx->prom_pt >> 12 ) & PRESSURE22_CRC4_BIT_MASK );
    ctx->prom_ver = ( uint8_t ) ( ( ctx->prom_pt >>  5 ) & PRESSURE22_VER_DEF_BIT_MASK );
    ctx->prom_fct = ( uint8_t ) ( ctx->prom_pt & PRESSURE22_FCT_DEF_BIT_MASK );
    err_flag |= pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_READ_C1, &ctx->prom_c1 );
    err_flag |= pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_READ_C2, &ctx->prom_c2 );
    err_flag |= pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_READ_C3, &ctx->prom_c3 );
    err_flag |= pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_READ_C4, &ctx->prom_c4 );
    err_flag |= pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_READ_C5, &ctx->prom_c5 );
    err_flag |= pressure22_get_prom_data( ctx, PRESSURE22_CMD_PROM_READ_C6, &ctx->prom_c6 );
    return err_flag;
}

err_t pressure22_check_data_validity ( pressure22_t *ctx ) 
{
    err_t err_flag = PRESSURE22_OK;
    uint16_t prom_data[ 8 ] = { ctx->prom_pt, ctx->prom_c1, ctx->prom_c2, ctx->prom_c3, 
                                ctx->prom_c4, ctx->prom_c5, ctx->prom_c6 };
    if ( ctx->prom_crc != pressure22_calc_crc4( &prom_data[ 0 ] ) )
    {
        err_flag = PRESSURE22_ERROR;
    }
    return err_flag;
}

void pressure22_set_conversion ( pressure22_t *ctx, pressure22_press_conv_t press_conv, 
                                                    pressure22_temp_conv_t temp_conv ) 
{
    ctx->press_conv = press_conv;
    ctx->temp_conv = temp_conv;
}

err_t pressure22_get_measurement_data ( pressure22_t *ctx, float *temperature, float *pressure ) 
{
    uint32_t d1 = DUMMY, d2 = DUMMY;
    int32_t dt = DUMMY, temp = DUMMY;
    float off = DUMMY, sens = DUMMY;
    
    // Pressure conversion sequence
    err_t err_flag = pressure22_set_command( ctx, ctx->press_conv );
    ( *delay_ptr[ ( ctx->press_conv - PRESSURE22_CMD_PRESS_OSR_256 ) >> 1 ] )( );
    err_flag |= pressure22_get_adc_data( ctx, &d1 );

    // Temperature conversion sequence
    err_flag |= pressure22_set_command( ctx, ctx->temp_conv );
    ( *delay_ptr[ ( ctx->temp_conv - PRESSURE22_CMD_TEMP_OSR_256 ) >> 1 ] )( );
    err_flag |= pressure22_get_adc_data( ctx, &d2 );

    // Difference between actual and reference temperature
    dt = ( int32_t ) d2;
    dt -= ( ( int32_t ) ( ctx->prom_c5 ) ) << 8;
    
    // Actual temperature
    *temperature = PRESSURE22_TEMP_TYPICAL;
    *temperature += ( float ) ( ( dt * ( ( uint32_t ) ( ctx->prom_c5 ) ) ) >> 23 );
    temp = ( int32_t ) *temperature;
    temp -= ( int32_t ) PRESSURE22_TEMP_TYPICAL;
    *temperature /= PRESSURE22_TEMP_DIV;
    
    // Second order compensation flowchart
    float ti = DUMMY, offi = DUMMY, sensi = DUMMY;
    if ( PRESSURE22_TEMPERATURE_20_C > *temperature )
    {
        ti = ( PRESSURE22_SEC_COMP_TI_1_MULTP * ( float ) ( dt * dt ) ) / PRESSURE22_SEC_COMP_TI_DIV;
        offi = PRESSURE22_SEC_COMP_OFFI_1_MULTP * ( float ) ( temp * temp ) / PRESSURE22_SEC_COMP_OFFI_1_DIV;
        sensi  = PRESSURE22_SEC_COMP_SENS_MULTP * ( float ) ( temp * temp ) / PRESSURE22_SEC_COMP_SENSI_DIV;
    }
    else if ( PRESSURE22_TEMPERATURE_10_C > *temperature )
    {
        ti = ( PRESSURE22_SEC_COMP_TI_2_MULTP * ( float ) ( dt * dt ) ) / PRESSURE22_SEC_COMP_TI_DIV;
        offi = PRESSURE22_SEC_COMP_OFFI_2_MULTP * ( float ) ( temp * temp ) / PRESSURE22_SEC_COMP_OFFI_2_DIV;
    }
    *temperature -= ( ( float ) ti ) / PRESSURE22_TEMP_DIV; 
    
    // Offset at actual temperature
    off = ( ( float ) ( ctx->prom_c2 ) ) * PRESSURE22_OFF_ACT_TEMP_MULTP;
    off += ( ( ( float ) ( ctx->prom_c4 ) ) *  dt ) / PRESSURE22_OFF_ACT_TEMP_DIV;
    off -= offi;
    
    // Sensitivity at actual temperature
    sens = ( ( float ) ( ctx->prom_c1 ) ) * PRESSURE22_SENS_ACT_TEMP_MULTP;
    sens += ( ( ( float ) ( ctx->prom_c3 ) ) * dt ) / PRESSURE22_SENS_ACT_TEMP_DIV;
    sens -= sensi;
    
    // Temperature compensated pressure
    *pressure = ( float ) d1;
    *pressure *= ( float ) sens;
    *pressure /= PRESSURE22_TEMP_COMP_PRESS_DIV;
    *pressure -= ( float ) off;
    *pressure /= PRESSURE22_COMP_PRESS_DIV;
    *pressure /= PRESSURE22_PRESS_CONVERT_PA_MBAR;
    
    return err_flag;
}

static void pressure22_delay_odr_256 ( void ) 
{
    Delay_500us( );
    Delay_50us( );
    Delay_10us( );
}

static void pressure22_delay_odr_512 ( void ) 
{
    Delay_1ms( );
    Delay_50us( );
    Delay_50us( );
}

static void pressure22_delay_odr_1024 ( void ) 
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_80us( );
    Delay_80us( );
    Delay_10us( );
}

static void pressure22_delay_odr_2048 ( void ) 
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
}

static void pressure22_delay_odr_4096 ( void ) 
{
    Delay_8ms( );
    Delay_500us( );
    Delay_50us( );
    Delay_50us( );
    Delay_10us( );
}

static void pressure22_delay_odr_8192 ( void ) 
{
    Delay_8ms( );
    Delay_8ms( );
    Delay_1ms( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
}

static uint8_t pressure22_calc_crc4 ( uint16_t *prom )
{
    uint8_t cnt;
    uint16_t n_rem = 0;
    uint8_t n_bit;
    prom[ 0 ] = ( ( prom[ 0 ] ) & 0x0FFF );
    prom[ 7 ] = 0;
    for ( cnt = 0; cnt < 16; cnt++ )
    {
        if ( 1 == cnt % 2 ) 
        {
            n_rem ^= ( uint8_t ) ( ( prom[ cnt >> 1 ] ) & 0x00FF );
        }
        else
        {
            n_rem ^= ( uint8_t ) ( prom[ cnt >> 1 ] >> 8 );
        }
        
        for ( n_bit = 8; n_bit > 0; n_bit-- )
        {
            if ( n_rem & 0x8000 )
            {
                n_rem = ( n_rem << 1 ) ^ 0x3000;
            } 
            else
            {
                n_rem = ( n_rem << 1 );
            }
        }
    }
    n_rem = ( ( n_rem >> 12 ) & 0x000F );
    return ( uint8_t ) ( n_rem ^ 0x00 );
}

// ------------------------------------------------------------------------- END

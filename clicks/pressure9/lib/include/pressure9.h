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
 * \brief This file contains API for Pressure 9 Click driver.
 *
 * \addtogroup pressure9 Pressure 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE9_H
#define PRESSURE9_H

#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define PRESSURE9_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define PRESSURE9_MASTER_I2C 0
#define PRESSURE9_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE9_RETVAL  uint8_t

#define PRESSURE9_OK           0x00
#define PRESSURE9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Registers
 * \{
 */
#define PRESSURE9_REG_PRESSURE_DATA_B2               0x00 
#define PRESSURE9_REG_PRESSURE_DATA_B1               0x01 
#define PRESSURE9_REG_PRESSURE_DATA_B0               0x02 
#define PRESSURE9_REG_TEMPERATRE_DATA_B2             0x03 
#define PRESSURE9_REG_TEMPERATRE_DATA_B1             0x04 
#define PRESSURE9_REG_TEMPERATRE_DATA_B0             0x05 
#define PRESSURE9_REG_PRESSURE_CONFIG                0x06 
#define PRESSURE9_REG_TEMPERATURE_CONFIG             0x07 
#define PRESSURE9_REG_MEASUREMENT_CONFIG             0x08 
#define PRESSURE9_REG_CONFIGURATION                  0x09 
#define PRESSURE9_REG_INT_STATUS                     0x0A 
#define PRESSURE9_REG_WATERMARK_CONFIG               0x0B 
#define PRESSURE9_REG_FIFO_STATUS                    0x0C 
#define PRESSURE9_REG_RESET                          0x0D 
#define PRESSURE9_REG_PRODUCT_ID                     0x1D 
#define PRESSURE9_T_GAIN_COEFF                       0x20
#define PRESSURE9_T_DVBE_COEFF                       0x21
#define PRESSURE9_T_VBE_COEFF                        0x22
#define PRESSURE9_COEFF_REG_1                        0x26
#define PRESSURE9_COEFF_REG_2                        0x27
#define PRESSURE9_COEFF_REG_3                        0x28
#define PRESSURE9_COEFF_REG_4                        0x29
#define PRESSURE9_COEFF_REG_5                        0x2A
#define PRESSURE9_COEFF_REG_6                        0x2B
#define PRESSURE9_COEFF_REG_7                        0x2C
#define PRESSURE9_COEFF_REG_8                        0x2D
#define PRESSURE9_COEFF_REG_9                        0x2E
#define PRESSURE9_COEFF_REG_10                       0x2F
#define PRESSURE9_COEFF_REG_11                       0x30
#define PRESSURE9_COEFF_REG_12                       0x31
#define PRESSURE9_COEFF_REG_13                       0x32
#define PRESSURE9_COEFF_REG_14                       0x33
#define PRESSURE9_COEFF_REG_15                       0x34
#define PRESSURE9_COEFF_REG_16                       0x35
#define PRESSURE9_COEFF_REG_17                       0x36
#define PRESSURE9_COEFF_REG_18                       0x37
/** \} */

/**
 * \defgroup press_temp_cfg Pressure config / Tempeature config
 * \{
 */
#define PRESSURE9_PTCFG_RATE_1_SAMPLE_SEC            0x00 
#define PRESSURE9_PTCFG_RATE_2_SAMPLES_SEC           0x10 
#define PRESSURE9_PTCFG_RATE_4_SAMPLES_SEC           0x20 
#define PRESSURE9_PTCFG_RATE_8_SAMPLES_SEC           0x30 
#define PRESSURE9_PTCFG_RATE_16_SAMPLES_SEC          0x40 
#define PRESSURE9_PTCFG_RATE_32_SAMPLES_SEC          0x50 
#define PRESSURE9_PTCFG_RATE_64_SAMPLES_SEC          0x60 
#define PRESSURE9_PTCFG_RATE_128_SAMPLES_SEC         0x70 
#define PRESSURE9_PTCFG_RES_X1_256_SAMPLES           0x00 
#define PRESSURE9_PTCFG_RES_X2_512_SAMPLES           0x01 
#define PRESSURE9_PTCFG_RES_X4_1024_SAMPLES          0x02 
#define PRESSURE9_PTCFG_RES_X8_2048_SAMPLES          0x03 
#define PRESSURE9_PTCFG_RES_X16_4096_SAMPLES         0x04 
#define PRESSURE9_PTCFG_RES_X32_8192_SAMPLES         0x05 
#define PRESSURE9_PTCFG_RES_X64_16384_SAMPLES        0x06 
#define PRESSURE9_PTCFG_RES_X128_32768_SAMPLES       0x07 
/** \} */

/**
 * \defgroup mess_cfg  Measurement config
 */
#define PRESSURE9_MCFG_IDLE_STOP_BACKGROUND          0x00 
#define PRESSURE9_MCFG_PRESSURE_MEASUREMENT          0x01 
#define PRESSURE9_MCFG_TEMPERATURE_MEASUREMENT       0x02 
#define PRESSURE9_MCFG_TEMP_AND_PRESS_ONE_SHOT       0x03 
#define PRESSURE9_MCFG_PRESSURE_MEASUREMENT_CONT     0x05 
#define PRESSURE9_MCFG_TEMPERATURE_MEASUREMENT_CONT  0x06 
#define PRESSURE9_MCFG_TEMP_AND_PRESS_CONT           0x07 
/** \} */

/**
 * \defgroup config Configuration
 */ 
#define PRESSURE9_CFG_SINT_NO_INT_ENABLED            0x00 
#define PRESSURE9_CFG_SINT_PRESS_INT_ENABLED         0x10 
#define PRESSURE9_CFG_SINT_TEMP_INT_ENABLED          0x20 
#define PRESSURE9_CFG_SINT_PRESS_AND_TEMP_INT_EN     0x30 
#define PRESSURE9_CFG_SINT_FIFO_WM_INT_ENABLED       0x40 
#define PRESSURE9_CFG_SINT_FIFO_FULL_INT_ENABLED     0x80 
#define PRESSURE9_CFG_PINT_INT_ACTIVE_LOW            0x00 
#define PRESSURE9_CFG_PINT_INT_ACTIVE_HIGH           0x08 
#define PRESSURE9_CFG_FIFO_SF_STREAMING_MODE         0x00 
#define PRESSURE9_CFG_FIFO_SF_FULL_MODE              0x04 
#define PRESSURE9_CFG_FIFO_EN_ENABLED                0x02 
#define PRESSURE9_CFG_FIFO_EN_DISABLED               0x00 
#define PRESSURE9_CFG_SPI_MODE_4_WIRE                0x00 
#define PRESSURE9_CFG_SPI_MODE_3_WIRE                0x01 
/** \} */

/**
 * \defgroup reset Reset
 */ 
#define PRESSURE9_RESET_CONFIGURATION_REG            0x08 
#define PRESSURE9_FULL_SOFTWARE_RESET                0x09 
#define PRESSURE9_FIFO_FLUSH                         0x80 
/** \} */

/**
 * \defgroup slave_address_pid Slave addresses and product ID 
 */ 
#define PRESSURE9_DEV_SLAVE_ADR_GND                  0x76 
#define PRESSURE9_DEV_SLAVE_ADR_VCC                  0x77 
#define PRESSURE9_PRODUCT_ID                         0x1A 
/** \} */

/**
 * \defgroup calib_coef Calculation coefficients 
 */ 
#define PRESSURE9_PRESSURE_COEFFICIENT_C00           0x00 
#define PRESSURE9_PRESSURE_COEFFICIENT_C01           0x01 
#define PRESSURE9_PRESSURE_COEFFICIENT_C02           0x02 
#define PRESSURE9_PRESSURE_COEFFICIENT_C10           0x10 
#define PRESSURE9_PRESSURE_COEFFICIENT_C20           0x20 
#define PRESSURE9_PRESSURE_COEFFICIENT_C30           0x30 
#define PRESSURE9_PRESSURE_COEFFICIENT_C11           0x11 
#define PRESSURE9_PRESSURE_COEFFICIENT_C12           0x12 
#define PRESSURE9_PRESSURE_COEFFICIENT_C21           0x21 
#define PRESSURE9_TEMP_COEFFICIENT_T_GAIN            0x03 
#define PRESSURE9_TEMP_COEFFICIENT_T_DVBE            0x04 
#define PRESSURE9_TEMP_COEFFICIENT_T_VBE             0x05 
#define PRESSURE9_COEFF_CAL_00                       0x00
#define PRESSURE9_COEFF_CAL_10                       0x10
#define PRESSURE9_COEFF_CAL_01                       0x01
#define PRESSURE9_COEFF_CAL_02                       0x02
#define PRESSURE9_COEFF_CAL_20                       0x20
#define PRESSURE9_COEFF_CAL_30                       0x30
#define PRESSURE9_COEFF_CAL_11                       0x11
#define PRESSURE9_COEFF_CAL_12                       0x12
#define PRESSURE9_COEFF_CAL_21                       0x21
#define PRESSURE9_COEFF_T_GAIN                       0x03
#define PRESSURE9_COEFF_T_DVBE                       0x04
#define PRESSURE9_COEFF_T_VBE                        0x05
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  pressure9_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *pressure9_master_io_t )( struct pressure9_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Pressure calibration coefficient.
 */
typedef struct
{
    int32_t cal_00;
    int32_t cal_10;
    int32_t cal_01;
    int32_t cal_02;
    int32_t cal_20;
    int32_t cal_30;
    int32_t cal_11;
    int32_t cal_12;
    int32_t cal_21;

} pressure9_press_cal_coef_t;

/**
 * @brief Temperature calibration coefficient.
 */
typedef struct
{
    int32_t t_gain;
    int32_t t_dvbe;
    int32_t t_vbe;
    float vbe;
    float dvbe;
    float adc_val;
    float vbe_cal;
    float dvbe_cal;
    float t_cal;
    float vbe_cal_t_ref;
    float kptat;
    float ap;
    float bp;

} pressure9_temp_cal_coef_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct pressure9_s
{
    // Output pins 
   
    digital_out_t cs;

    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 
    uint8_t slave_address;
    pin_name_t chip_select;
    pressure9_master_io_t  write_f;
    pressure9_master_io_t  read_f;
    pressure9_select_t master_sel;
    
    // Pressure calibration coefficient 
    
    pressure9_press_cal_coef_t press_coef;
    
    // Temperature calibration coefficient 
    
    pressure9_temp_cal_coef_t temp_coef;

} pressure9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    pressure9_select_t sel;

} pressure9_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void pressure9_cfg_setup ( pressure9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PRESSURE9_RETVAL pressure9_init ( pressure9_t *ctx, pressure9_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure9 click.
 */
void pressure9_default_cfg ( pressure9_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void pressure9_generic_write ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void pressure9_generic_read ( pressure9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Writing data to the configuration registers
 *
 * @param ctx      Click object.
 * @param regAddr        Configuration register address
 * @param dataIn         Data that will be written in the register
 * @note - Use this function when you want to write data to one of the configuration registers
         - Configuration registers: PRESSURE_CONFIG, TEMPERATURE_CONFIG, MEASUREMENT_CONFIG and CONFIGURATION
 */
void pressure9_configuration ( pressure9_t *ctx, uint8_t reg_adr, uint8_t data_in );

/**
 * @brief Get calibration coefficients
 *
 * @param ctx      Click object.
 * @param coeff        Coefficient, which will be read
 * @return Calibration coefficients
 *
 * @note - This function allows you to read the calibration coefficient 
         - Pressure coefficient or Temperature coefficient
 */
int32_t pressure9_get_coefficients ( pressure9_t *ctx, uint8_t coeff );

/**
 * @brief Update all calibration coefficients
 *
 * @param ctx      Click object.
 * @note - This function must be called before the measurement starts
 */
void pressure9_update_calculation_coefficient ( pressure9_t *ctx );

/**
 * @brief Get Temperature Raw data
 *
 * @param ctx      Click object.
 * @return 24bit temperature raw data
 */
int32_t pressure9_get_temperature_raw ( pressure9_t *ctx );

/**
 * @brief Get Pressure Raw data
 *
 * @param ctx      Click object.
 * @return 24bit pressure raw data
 */
int32_t pressure9_get_pressure_raw ( pressure9_t *ctx );

/**
 * @brief Get Pressure data in mBar
 *
 * @param ctx      Click object.
 * @return Pressure data
 */
float pressure9_get_pressure_data ( pressure9_t *ctx );

/**
 * @brief Get Temperature data in C
 *
 * @param ctx      Click object.
 * @return Temperature data
 */
float pressure9_get_temperature_data ( pressure9_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

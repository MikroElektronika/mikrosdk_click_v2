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
 * \brief This file contains API for PAC1921 Click driver.
 *
 * \addtogroup pac1921 PAC1921 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PAC1921_H
#define PAC1921_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define PAC1921_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an      = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PAC1921_RETVAL  uint8_t

#define PAC1921_OK           0x00
#define PAC1921_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define PAC1921_SLAVE_ADDRESS   0x4C
/** \} */

/**
 * \defgroup register_addresses Register Adddresses
 * \{
 */
#define PAC1921_GAIN_CFG_REG              0x00
#define PAC1921_INTEGRATION_CFG_REG       0x01
#define PAC1921_CONTROL_REG               0x02
#define PAC1921_VBUS_RESULT_HIGH          0x10
#define PAC1921_VBUS_RESULT_LOW           0x11
#define PAC1921_VSENSE_RESULT_HIGH        0x12
#define PAC1921_VSENSE_RESULT_LOW         0x13
#define PAC1921_VSUM_ACCUMULATOR_HIGH     0x14
#define PAC1921_VSUM_ACCUMULATOR_MID_H    0x15
#define PAC1921_VSUM_ACCUMULATOR_MID_L    0x16
#define PAC1921_VSUM_ACCUMULATOR_LOW      0x17
#define PAC1921_ISUM_ACCUMULATOR_HIGH     0x18
#define PAC1921_ISUM_ACCUMULATOR_MID_H    0x19
#define PAC1921_ISUM_ACCUMULATOR_MID_L    0x1A
#define PAC1921_ISUM_ACCUMULATOR_LOW      0x1B
#define PAC1921_OVERFLOW_STATUS           0x1C
#define PAC1921_VPOWER_RESULT_HIGH        0x1D
#define PAC1921_VPOWER_RESULT_LOW         0x1E
#define PAC1921_SAMPLES_HIGH              0x21
#define PAC1921_SAMPLES_LOW               0x22
#define PAC1921_PSUM_ACCUMULATOR_HIGH     0x23
#define PAC1921_PSUM_ACCUMULATOR_MID_H    0x24
#define PAC1921_PSUM_ACCUMULATOR_MID_M    0x25
#define PAC1921_PSUM_ACCUMULATOR_MID_L    0x26
#define PAC1921_PSUM_ACCUMULATOR_LOW      0x27
#define PAC1921_PRODUCT_ID                0xFD
#define PAC1921_MANUFACTURER_ID           0xFE
#define PAC1921_REVISION                  0xFF
/** \} */

/**
 * \defgroup gain_configuration_bits Gain Configuration Bits
 * \{
 */
#define PAC1921_I_RESOLUTION_11_BIT   0x80
#define PAC1921_I_RESOLUTION_14_BIT   0x00
#define PAC1921_V_RESOLUTION_11_BIT   0x40
#define PAC1921_V_RESOLUTION_14_BIT   0x00
#define PAC1921_DIGITAL_I_GAIN_1X     0x00
#define PAC1921_DIGITAL_I_GAIN_2X     0x08
#define PAC1921_DIGITAL_I_GAIN_4X     0x10
#define PAC1921_DIGITAL_I_GAIN_8X     0x18
#define PAC1921_DIGITAL_I_GAIN_16X    0x20
#define PAC1921_DIGITAL_I_GAIN_32X    0x28
#define PAC1921_DIGITAL_I_GAIN_64X    0x30
#define PAC1921_DIGITAL_I_GAIN_128X   0x38
#define PAC1921_DIGITAL_V_GAIN_1X     0x00
#define PAC1921_DIGITAL_V_GAIN_2X     0x01
#define PAC1921_DIGITAL_V_GAIN_4X     0x02
#define PAC1921_DIGITAL_V_GAIN_8X     0x03
#define PAC1921_DIGITAL_V_GAIN_16X    0x04
#define PAC1921_DIGITAL_V_GAIN_32X    0x05
#define PAC1921_DIGITAL_V_GAIN_64X    0x06
#define PAC1921_DIGITAL_V_GAIN_128X   0x07
/** \} */

/**
 * \defgroup integration_configuration_bits Integration Configuration Bits
 * \{
 */
#define PAC1921_SAMPLE_RATE_1               0x00
#define PAC1921_SAMPLE_RATE_2               0x10
#define PAC1921_SAMPLE_RATE_4               0x20
#define PAC1921_SAMPLE_RATE_8               0x30
#define PAC1921_SAMPLE_RATE_16              0x40
#define PAC1921_SAMPLE_RATE_32              0x50
#define PAC1921_SAMPLE_RATE_64              0x60
#define PAC1921_SAMPLE_RATE_128             0x70
#define PAC1921_SAMPLE_RATE_256             0x80
#define PAC1921_SAMPLE_RATE_512             0x90
#define PAC1921_SAMPLE_RATE_1024            0xA0
#define PAC1921_SAMPLE_RATE_2048            0xB0
#define PAC1921_V_SENSE_FILTER_ON           0x08   
#define PAC1921_V_SENSE_FILTER_OFF          0x00
#define PAC1921_V_BUS_FILTER_ON             0x04
#define PAC1921_V_BUS_FILTER_OFF            0x00
#define PAC1921_READ_INT_OVERRIDE_ON        0x02   
#define PAC1921_READ_INT_OVERRIDE_OFF       0x00
#define PAC1921_FORCED_INTEGRATE_MODE_ON    0x01 
#define PAC1921_FORCED_INTEGRATE_MODE_OFF   0x00 
/** \} */

/**
 * \defgroup control_bits Control Bits
 * \{
 */
#define PAC1921_MEASUREMENT_MODE_V_POWER_PIN_CTRL    0x00
#define PAC1921_MEASUREMENT_MODE_V_SENSE_FREE_RUN    0x40
#define PAC1921_MEASUREMENT_MODE_V_BUS_FREE_RUN      0x80
#define PAC1921_MEASUREMENT_MODE_V_POWER_FREE_RUN    0xC0
#define PAC1921_MEASUREMENT_MODE_MASK                0xC0  
#define PAC1921_OUT_PIN_FULL_SCALE_RANGE_3V          0x00
#define PAC1921_OUT_PIN_FULL_SCALE_RANGE_2V          0x10
#define PAC1921_OUT_PIN_FULL_SCALE_RANGE_1_5_V       0x20
#define PAC1921_OUT_PIN_FULL_SCALE_RANGE_1V          0x30
#define PAC1921_TIMEOUT_ON                           0x08
#define PAC1921_TIMEOUT_OFF                          0x00
#define PAC1921_SLEEP_ON                             0x04
#define PAC1921_SLEEP_OFF                            0x00
#define PAC1921_FORCED_READ_MODE_ON                  0x02
#define PAC1921_FORCED_READ_MODE_OFF                 0x00
#define PAC1921_FORCED_RECALCULATE_MODE_ON           0x01
#define PAC1921_FORCED_RECALCULATE_MODE_OFF          0x00
/** \} */

/**
 * \defgroup measurement_maximums Measurement Maximums
 * \{
 */
#define PAC1921_VOLTAGE_MAX   10   
#define PAC1921_CURRENT_MAX   32
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Auxiliary variables structure.
 */
typedef struct
{
    uint8_t ctrl_byte;
    uint8_t cfg_byte;
    uint8_t measurement_mode_old;
    uint8_t sample_num_old;
    uint8_t iarp;
    uint16_t output_fsr;

} aux_vars_t;

/**
 * @brief Auxiliary variables default cfg.
 */
typedef struct
{
    uint8_t ctrl_byte;
    uint8_t cfg_byte;
    uint8_t measurement_mode_old;
    uint8_t sample_num_old;
    uint8_t iarp;
    uint16_t output_fsr;

} aux_cfg_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t int_pin;

    // Input pins 

    digital_in_t an;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    aux_vars_t aux; 

} pac1921_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    aux_cfg_t aux_cfg;

} pac1921_cfg_t;

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
void pac1921_cfg_setup ( pac1921_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PAC1921_RETVAL pac1921_init ( pac1921_t *ctx, pac1921_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for PAC1921 click.
 */
void pac1921_default_cfg ( pac1921_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void pac1921_generic_write ( pac1921_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void pac1921_generic_read ( pac1921_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Register write function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * @param write_data   Data which will be written.
 * @param len          Size of write_data in bytes.
 *
 * @description This function writes data to the specified register address/es and saves the 
 *              state of the register/s so it doesn't write the same value/s twice.
 */
void pac1921_write_to_reg ( pac1921_t *ctx, uint8_t reg_addr, uint8_t *write_data, uint8_t len );

/**
 * @brief Measured data read function.
 *
 * @param ctx                  Click object.
 * @param measurement_mode     Measurement mode of the PAC1921 chip.
 * @param sample_num           Number of samples that will be acquired.
 *
 * @description This function gathers voltage/power data from the PAC1921 chip and, depending
 *              on the measurement mode, converts those raw values into a more suitable form.
 */
float pac1921_get_measured_data ( pac1921_t *ctx, uint8_t measurement_mode, uint8_t sample_num );

/**
 * @brief INT pin set output function.
 *
 * @param ctx        Click object.
 * @param output     Pin digital output.
 *
 * @description This function sets the digital output on the interrupt pin.
 */
void pac1921_set_int_pin ( pac1921_t *ctx, uint8_t output );

/**
 * @brief AN pin get input function.
 *
 * @param ctx        Click object.
 *
 * @description This function gets the digital input from the analog pin.
 */
uint8_t pac1921_get_an_pin ( pac1921_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PAC1921_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

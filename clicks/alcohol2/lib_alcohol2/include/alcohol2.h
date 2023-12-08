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
 * \brief This file contains API for Alcohol 2 Click driver.
 *
 * \addtogroup alcohol2 Alcohol 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ALCOHOL2_H
#define ALCOHOL2_H

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
#define ALCOHOL2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ALCOHOL2_RETVAL  uint8_t

#define ALCOHOL2_OK           0x00
#define ALCOHOL2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define ALCOHOL2_STATUS_REG                       0x00
#define ALCOHOL2_LOCK_REG                         0x01
#define ALCOHOL2_TIACN_REG                        0x10
#define ALCOHOL2_REFCN_REG                        0x11
#define ALCOHOL2_MODECN_REG                       0x12
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define ALCOHOL2_WRITE_MODE                       0x00
#define ALCOHOL2_READ_ONLY_MODE                   0x01
/** \} */

/**
 * \defgroup ohm Ohm
 * \{
 */
#define ALCOHOL2_EXT_TIA_RES                      0x00
#define ALCOHOL2_2750_OHM_TIA_RES                 0x04
#define ALCOHOL2_3500_OHM_TIA_RES                 0x08
#define ALCOHOL2_7K_OHM_TIA_RES                   0x0C
#define ALCOHOL2_14K_OHM_TIA_RES                  0x10
#define ALCOHOL2_35K_OHM_TIA_RES                  0x14
#define ALCOHOL2_120K_OHM_TIA_RES                 0x18
#define ALCOHOL2_350K_OHM_TIA_RES                 0x1C
#define ALCOHOL2_10_OHM_LOAD_RES                  0x00
#define ALCOHOL2_33_OHM_LOAD_RES                  0x01
#define ALCOHOL2_50_OHM_LOAD_RES                  0x02
#define ALCOHOL2_100_OHM_LOAD_RES                 0x03
/** \} */

/**
 * \defgroup percents_mode Percents Mode
 * \{
 */
#define ALCOHOL2_VREF_INT                         0x00
#define ALCOHOL2_VREF_EXT                         0x80
#define ALCOHOL2_20_PERCENTS_INT_ZERO             0x00
#define ALCOHOL2_50_PERCENTS_INT_ZERO             0x20
#define ALCOHOL2_67_PERCENTS_INT_ZERO             0x40
#define ALCOHOL2_INT_ZERO_BYPASSED                0x60
#define ALCOHOL2_BIAS_POL_NEGATIVE                0x00
#define ALCOHOL2_BIAS_POL_POSITIVE                0x10
#define ALCOHOL2_0_PERCENTS_BIAS                  0x00
#define ALCOHOL2_1_PERCENT_BIAS                   0x01
#define ALCOHOL2_2_PERCENTS_BIAS                  0x02
#define ALCOHOL2_4_PERCENTS_BIAS                  0x03
#define ALCOHOL2_6_PERCENTS_BIAS                  0x04
#define ALCOHOL2_8_PERCENTS_BIAS                  0x05
#define ALCOHOL2_10_PERCENTS_BIAS                 0x06
#define ALCOHOL2_12_PERCENTS_BIAS                 0x07
#define ALCOHOL2_14_PERCENTS_BIAS                 0x08
#define ALCOHOL2_16_PERCENTS_BIAS                 0x09
#define ALCOHOL2_18_PERCENTS_BIAS                 0x0A
#define ALCOHOL2_20_PERCENTS_BIAS                 0x0B
#define ALCOHOL2_22_PERCENTS_BIAS                 0x0C
#define ALCOHOL2_24_PERCENTS_BIAS                 0x0D
/** \} */

/**
 * \defgroup mode1 Mode1
 * \{
 */
#define ALCOHOL2_FET_DIS                          0x00
#define ALCOHOL2_FET_EN                           0x80
#define ALCOHOL2_DEEP_SLEEP_MODE                  0x00
#define ALCOHOL2_2_LEAD_MODE                      0x01
#define ALCOHOL2_STANDBY_MODE                     0x02
#define ALCOHOL2_3_LEAD_MODE                      0x03
#define ALCOHOL2_TEMP_MODE_TIA_OFF                0x06
#define ALCOHOL2_TEMP_MODE_TIA_ON                 0x07
/** \} */

/**
 * \defgroup device_state Device State
 * \{
 */
#define ALCOHOL2_DEVICE_EN                        0x00
#define ALCOHOL2_DEVICE_DIS                       0x01
/** \} */

/**
 * \defgroup adc_address ADC Address
 * \{
 */
#define ADC_DEVICE_ADDR                           0x4D
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;


    // Input pins 

    digital_in_t an;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} alcohol2_t;

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
    pin_name_t rst;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} alcohol2_cfg_t;

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
void alcohol2_cfg_setup ( alcohol2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ALCOHOL2_RETVAL alcohol2_init ( alcohol2_t *ctx, alcohol2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Alcohol2 click.
 */
void alcohol2_default_cfg ( alcohol2_t *ctx );

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
void alcohol2_generic_write ( alcohol2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void alcohol2_generic_read ( alcohol2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function writes one byte to the register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param W_data       Data to be written.
 *
 * @description This function writes one byte to the register.
 */
void alcohol2_write_byte ( alcohol2_t *ctx, uint8_t reg, uint8_t w_data );

/**
 * @brief Function reads one byte from the register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads one byte from the register.
 */
uint8_t alcohol2_read_byte ( alcohol2_t *ctx, uint8_t reg );

/**
 * @brief Device Enable function.
 *
 * @param ctx          Click object.
 * @param state        State.
 *
 * @description This function enable device.
 */
void alcohol2_enable ( alcohol2_t *ctx, uint8_t state );

/**
 * @brief Function for read Alcohol data.
 *
 * @param ctx          Click object.
 *
 * @description This function reads Alcohol data.
 */
uint16_t alcohol2_read_alcohol ( alcohol2_t *ctx );

/**
 * @brief Function waits until I2C is ready for the next command.
 *
 * @param ctx          Click object.
 *
 * @description This function waits until I2C is ready for the next command.
 */
void alcohol2_wait_ready( alcohol2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ALCOHOL2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

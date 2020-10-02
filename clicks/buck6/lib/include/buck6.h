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
 * \brief This file contains API for BUCK 6 Click driver.
 *
 * \addtogroup buck6 BUCK 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK6_H
#define BUCK6_H

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
#define BUCK6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.syn = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK6_RETVAL  uint8_t

#define BUCK6_OK           0x00
#define BUCK6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup max_range Max range
 * \{
 */
#define BUCK6_MAX_RANGE_1000mV   0xFA
#define BUCK6_MAX_RANGE_1500mV   0xF4
#define BUCK6_MAX_RANGE_2000mV   0xF1
#define BUCK6_MAX_RANGE_2500mV   0xEE
#define BUCK6_MAX_RANGE_3000mV   0xEA
#define BUCK6_MAX_RANGE_3500mV   0xE7
#define BUCK6_MAX_RANGE_4000mV   0xE4
#define BUCK6_MAX_RANGE_4500mV   0xE1
#define BUCK6_MAX_RANGE_5000mV   0xDE
#define BUCK6_MAX_RANGE_5500mV   0xDB

#define BUCK6_MAX_RANGE_6000mV   0xD8
#define BUCK6_MAX_RANGE_6500mV   0xD4
#define BUCK6_MAX_RANGE_7000mV   0xD1
#define BUCK6_MAX_RANGE_7500mV   0xCF
#define BUCK6_MAX_RANGE_8000mV   0xCB
#define BUCK6_MAX_RANGE_8500mV   0xC8
#define BUCK6_MAX_RANGE_9000mV   0xC5
#define BUCK6_MAX_RANGE_9500mV   0xC2
#define BUCK6_MAX_RANGE_10000mV  0xBF
#define BUCK6_MAX_RANGE_10500mV  0xBC
#define BUCK6_MAX_RANGE_11000mV  0xB9
#define BUCK6_MAX_RANGE_11500mV  0xB6
#define BUCK6_MAX_RANGE_12000mV  0xB2
#define BUCK6_MAX_RANGE_12500mV  0xAF

#define BUCK6_MAX_RANGE_13000mV  0xAB
#define BUCK6_MAX_RANGE_13500mV  0xA9
#define BUCK6_MAX_RANGE_14000mV  0xA6
#define BUCK6_MAX_RANGE_14500mV  0xA3
#define BUCK6_MAX_RANGE_15000mV  0xA0
#define BUCK6_MAX_RANGE_15500mV  0x9C
#define BUCK6_MAX_RANGE_16000mV  0x99
#define BUCK6_MAX_RANGE_16500mV  0x96
#define BUCK6_MAX_RANGE_17000mV  0x93
#define BUCK6_MAX_RANGE_17500mV  0x90
#define BUCK6_MAX_RANGE_18000mV  0x8D
#define BUCK6_MAX_RANGE_18500mV  0x8A
#define BUCK6_MAX_RANGE_19000mV  0x87
#define BUCK6_MAX_RANGE_19500mV  0x84
#define BUCK6_MAX_RANGE_20000mV  0x80
/** \} */

/**
 * \defgroup sleep_mode Sleep mode
 * \{
 */
#define BUCK6_SLEEP_MODE  0x00
/** \} */

/**
 * \defgroup active_mode Active mode
 * \{
 */
#define BUCK6_ACTIVE_MODE  0x01
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

    digital_out_t en;
    digital_out_t syn;

    // Input pins 

    digital_in_t rst;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} buck6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t rst;
    pin_name_t syn;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} buck6_cfg_t;

/** \} */ // End types group


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
void buck6_cfg_setup ( buck6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK6_RETVAL buck6_init ( buck6_t *ctx, buck6_cfg_t *cfg );

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
void buck6_generic_write ( buck6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void buck6_generic_read ( buck6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief 
 *
 * 
 * @param ctx          Click object.
 *
 *
 * @description This function gets reset.
 */
uint8_t buck6_get_rst( buck6_t *ctx );

/**
 * @brief Set mode.
 *
 * 
 * @param ctx          Click object.
 * @param mode         Mode select
 *
 * @description This function sets mode.
 */
void buck6_set_mode( buck6_t *ctx, uint8_t mode);

/**
 * @brief Set maximum voltage.
 *
 * 
 * @param ctx          Click object.
 * @param voltage      Voltage value
 *
 * @description This function sets maximum voltage.
 */
void buck6_set_max_voltage( buck6_t *ctx, uint8_t voltage );

#ifdef __cplusplus
}
#endif
#endif  // _BUCK6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

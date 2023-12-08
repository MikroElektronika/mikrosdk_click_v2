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
 * \file ambient2.h
 *
 * \brief This file contains API for Ambient 2 Click driver.
 *
 * \addtogroup ambient2 Ambient 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _AMBIENT2_H_
#define _AMBIENT2_H_

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup cfg_range Measurement Range Configuration
 * \{
 */
#define AMBIENT2_CFG_RANGE_40_95_LX_MIN    0x0
#define AMBIENT2_CFG_RANGE_81_9_LX         0x1000
#define AMBIENT2_CFG_RANGE_163_8_LX        0x2000
#define AMBIENT2_CFG_RANGE_327_6_LX        0x3000
#define AMBIENT2_CFG_RANGE_655_2_LX        0x4000
#define AMBIENT2_CFG_RANGE_1310_4_LX       0x5000
#define AMBIENT2_CFG_RANGE_2620_8_LX       0x6000
#define AMBIENT2_CFG_RANGE_5241_6_LX       0x7000
#define AMBIENT2_CFG_RANGE_10483_2_LX      0x8000
#define AMBIENT2_CFG_RANGE_20966_4_LX      0x9000
#define AMBIENT2_CFG_RANGE_41932_8_LX      0xA000
#define AMBIENT2_CFG_RANGE_83865_6_LX_MAX  0xB000
#define AMBIENT2_CFG_RANGE_AUTO_SCALE      0xC000
/** \} */

/**
 * \defgroup cfg_conv_time Conversion Time Configuration
 * \{
 */
#define AMBIENT2_CFG_CONV_TIME_100MS  0x0
#define AMBIENT2_CFG_CONV_TIME_800MS  0x800
/** \} */

/**
 * \defgroup cfg_conv_mode Conversion Mode Configuration
 * \{
 */
#define AMBIENT2_CFG_CONV_MODE_SHUTDOWN     0x0
#define AMBIENT2_CFG_CONV_MODE_SINGLE_SHOT  0x200
#define AMBIENT2_CFG_CONV_MODE_CONT_CONV    0x400
/** \} */

/**
 * \defgroup cfg_latch_cmp Interrupt Reporting Mechanisms Configuration
 * \{
 */
#define AMBIENT2_CFG_LATCH_COMP_HYSTERESIS_STYLE  0x0
#define AMBIENT2_CFG_LATCH_COMP_WINDOW_STYLE      0x10
/** \} */

/**
 * \defgroup cfg_int_pol Interrupt Polarity Configuration
 * \{
 */
#define AMBIENT2_CFG_POL_INT_ACTIVE_LOW   0x0
#define AMBIENT2_CFG_POL_INT_ACTIVE_HIGH  0x8
/** \} */

/**
 * \defgroup cfg_mask Mask Configuration
 * \{
 */
#define AMBIENT2_CFG_MASK_EXPONENT  0x4
/** \} */

/**
 * \defgroup cfg_fault_cnt Interrupt Fault Events Counter Configuration
 * \{
 */
#define AMBIENT2_CFG_FAULT_1_COUNT   0x0
#define AMBIENT2_CFG_FAULT_2_COUNTS  0x1
#define AMBIENT2_CFG_FAULT_4_COUNTS  0x2
#define AMBIENT2_CFG_FAULT_8_COUNTS  0x3
/** \} */

/**
 * \defgroup flag_mask Flag Mask
 * \{
 */
#define AMBIENT2_FLAG_MASK_OVERFLOW    0x100
#define AMBIENT2_FLAG_MASK_CONV_READY  0x80
#define AMBIENT2_FLAG_MASK_HIGH        0x40
#define AMBIENT2_FLAG_MASK_LOW         0x20
/** \} */

/**
 * \defgroup id ID
 * \{
 */
#define AMBIENT2_ID_MANUFACTURER  0x5449
#define AMBIENT2_ID_DEVICE        0x3001
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define AMBIENT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/** \} */ // End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click registers data type.
 */
typedef uint16_t ambient2_data_t;

/**
 * @brief Click error code definition.
 */
typedef enum
{
    AMBIENT2_OK = 0x0,
    AMBIENT2_ERR_INIT_DRV = 0xFE,
    AMBIENT2_ERR_UNSUPPORTED_PIN

} ambient2_err_t;

/**
 * @brief Click I2C address selection.
 */
typedef enum
{
    AMBIENT2_I2C_ADDRESS_GND = 0x44,
    AMBIENT2_I2C_ADDRESS_VDD,
    AMBIENT2_I2C_ADDRESS_SDA,
    AMBIENT2_I2C_ADDRESS_SCL

} ambient_addr_t;

/**
 * @brief Click register address selection.
 */
typedef enum
{
    AMBIENT2_REG_RESULT = 0x0,
    AMBIENT2_REG_CONFIGURATION,
    AMBIENT2_REG_LOW_LIMIT,
    AMBIENT2_REG_HIGH_LIMIT,
    AMBIENT2_REG_MANUFACTURER_ID = 0x7E,
    AMBIENT2_REG_DEVICE_ID

} ambient2_reg_addr_t;

/**
 * @brief Click sensor data definition.
 */
typedef struct
{
    float    amb_light_lx;
    float    amb_light_range;
    uint8_t  amb_light_per;

} ambient2_sens_data_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    //  Event pin.
    digital_in_t  int_pin;

    //  Module.
    i2c_master_t  i2c;

    //  Device slave address.
    uint8_t  slave_addr;

    //  Ambient light sensor data.
    ambient2_sens_data_t  sens_data;

} ambient2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  scl;
    pin_name_t  sda;

    //  Additional gpio pin.
    pin_name_t  int_pin;

    //  Module configuration variables.
    uint32_t  i2c_speed;
    uint8_t  i2c_addr;

} ambient2_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Functions
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to initial state.
 * @note All used pins will be set to unconnected state.
 */
void ambient2_cfg_setup( ambient2_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok, 0xFE - Driver init error, 0xFF - Unsupported pin.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ambient2_err_t ambient2_init( ambient2_t *ctx, ambient2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a default configuration for Ambient 2 click.
 */
void ambient2_default_cfg( ambient2_t *ctx );

/**
 * @brief Generic Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @description This function allows user to perform a 16-bit data writing operation
 * to the desired register.
 */
void ambient2_generic_write( ambient2_t *ctx, ambient2_reg_addr_t reg_addr, ambient2_data_t data_in );

/**
 * @brief Generic Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 *
 * @returns A 16-bit read data.
 *
 * @description This function allows user to perform a 16-bit data reading operation
 * from the desired register.
 */
ambient2_data_t ambient2_generic_read( ambient2_t *ctx, ambient2_reg_addr_t reg_addr );

/**
 * @brief Sensor Results Read function.
 *
 * @param ctx  Click object.
 *
 * @description This function allows user to get sensor results data which consists of the
 * ambient light measured data [lux], ambient light range data [lux] and ambient light data
 * in percents.
 */
void ambient2_get_sens_results( ambient2_t *ctx );

/**
 * @brief INT Pin Check function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns the state of the INT pin.
 */
uint8_t ambient2_get_int( ambient2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _AMBIENT2_H_

/** \} */ //  End public_function group
/// \}    //  End ambient2 group
/*! @} */
// ------------------------------------------------------------------------ END

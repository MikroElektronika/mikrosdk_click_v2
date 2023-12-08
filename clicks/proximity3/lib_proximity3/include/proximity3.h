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
 * \brief This file contains API for Proximity 3 Click driver.
 *
 * \addtogroup proximity3 Proximity 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY3_H
#define PROXIMITY3_H

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
#define PROXIMITY3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY3_OK                           0
#define PROXIMITY3_ERROR                       -1
/** \} */


/**
 * \defgroup register_address Register address declaratons
 * \{
 */
#define PROXIMITY3_I2CADDR                      0x51     // I2C ADDRESS
#define PROXIMITY3_ALS_CONF_REG                 0x00     // Ambient Light Sensor Interrupt Threshold
#define PROXIMITY3_ALS_THDH_REG                 0x01     // Ambient Light Sensor Threshold Data High
#define PROXIMITY3_ALS_THDL_REG                 0x02     // Ambient Light Sensor Threshold Data Low
#define PROXIMITY3_PS_CONF1_CONF2_REG           0x03     // Proximity Conf1 and Conf2
#define PROXIMITY3_PS_CONF3_MS_REG              0x04     // Proximity Conf3 and Mode Select
#define PROXIMITY3_PS_CANC_REG                  0x05     // Proximity Cancellation Level Setting
#define PROXIMITY3_PS_THDL_REG                  0x06     // Proximity Sensor Threshold Data Low
#define PROXIMITY3_PS_THDH_REG                  0x07     // Proximity Sensor Threshold Data High
#define PROXIMITY3_PROXIMITY_REG                0x08     // Proximity output data
#define PROXIMITY3_AMBIENT_REG                  0x09     // Ambient Light Sensor output data
#define PROXIMITY3_WHITE_REG                    0x0A     // White output data
#define PROXIMITY3_INT_FLAG_REG                 0x0D     // Ambient Light Sensor and Proximity interrupt flags
#define PROXIMITY3_DEVICE_ID_REG                0x0E     // Device ID
/** \} */

/**
 * \defgroup device_id Device ID value.
 * \{
 */
#define PROXIMITY3_DEVICE_ID_VALUE              0x1058
/** \} */

/**
 * \defgroup config_bits Configuration bits.
 * \{
 */
#define PROXIMITY3_ALS_CONF_CONFIG              0x0040   // Default Startup Options Ambient Light Sensor
#define PROXIMITY3_PS_CONF1_CONF2_CONFIG        0x0A2A   // Default Startup Options Proximity Conf1 & Conf2
#define PROXIMITY3_PS_CONF3_MS_CONFIG           0x0770   // Default Startup Options Proximity Conf3 & MS
#define PROXIMITY3_PS_THDL_CONFIG               0x1388   // Proximity Interrupt Levels Threshold Data Low
#define PROXIMITY3_PS_THDH_CONFIG               0x2EE0   // Proximity Interrupt Levels Threshold Data High  
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
    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} proximity3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} proximity3_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void proximity3_cfg_setup ( proximity3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t proximity3_init ( proximity3_t *ctx, proximity3_cfg_t *cfg );

/**
 * @brief Proximity 3 default configuration function.
 * @details This function executes a default configuration of Proximity 3 click board.
 * @param[in] ctx : Click context object.
 * See #proximity3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity3_default_cfg ( proximity3_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx                  Click object.
 * @param reg_address          Register address.
 * @param data_in              16-BIT data ata to be written.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t proximity3_write_16 ( proximity3_t *ctx, uint8_t reg_address, uint16_t data_in );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @returns            16-BIT data read from the register.
 * 
 * @details This function reads data from the desired register.
 */
uint16_t proximity3_read_16 ( proximity3_t *ctx, uint8_t reg_address );

/**
 * @brief Read ambient light sensor data.
 * 
 * @param ctx          Click object.
 *
 * @returns            Ambient light sensor data.
 * 
 * @details This function gets the data returned by the ambient light sensor.
 */
uint16_t proximity3_read_als ( proximity3_t *ctx );

/**
 * @brief Read proximity.
 * 
 * @param ctx          Click object.
 *
 * @returns            Proximity data.
 * 
 * @details This function returns the proximity.
 */
uint16_t proximity3_read_proximity ( proximity3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

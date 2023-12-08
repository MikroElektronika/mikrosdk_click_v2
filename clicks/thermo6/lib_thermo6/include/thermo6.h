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
 * \brief This file contains API for Thermo 6 Click driver.
 *
 * \addtogroup thermo6 Thermo 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO6_H
#define THERMO6_H

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
#define THERMO6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO6_RETVAL  uint8_t

#define THERMO6_OK           0x00
#define THERMO6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_slave_address Device slave address
 * \{
 */
#define THERMO6_SLAVE_ADDRESS  0x48
/** \} */

/**
 * \defgroup register_address Register address
 * \{
 */
#define THERMO6_REG_TEMPERATURE    0x00
#define THERMO6_REG_CONFIG         0x01
#define THERMO6_REG_TEMP_HYST      0x02
#define THERMO6_REG_TEMP_OS        0x03
/** \} */

/**
 * \defgroup config Configuration
 * \{
 */
#define THERMO6_CFG_ONE_SHOT              0x0001

#define THERMO6_CFG_CONVERSION_RATE_0_25  0x0000
#define THERMO6_CFG_CONVERSION_RATE_1     0x0002
#define THERMO6_CFG_CONVERSION_RATE_4     0x0004
#define THERMO6_CFG_CONVERSION_RATE_8     0x0006

#define THERMO6_CFG_PEC_ENABLE            0x0008
#define THERMO6_CFG_PEC_DISABLE           0x0000

#define THERMO6_CFG_TIMEOUT_ENABLE        0x0010
#define THERMO6_CFG_TIMEOUT_DISABLE       0x0000

#define THERMO6_CFG_RESOLUTION_8          0x0000
#define THERMO6_CFG_RESOLUTION_9          0x0020
#define THERMO6_CFG_RESOLUTION_10         0x0040
#define THERMO6_CFG_RESOLUTION_12         0x0060

#define THERMO6_CFG_NORMAL_FORMAT         0x0000
#define THERMO6_CFG_EXTENDED_FORMAT       0x0080

#define THERMO6_CFG_SHUT_DOWN             0x0100
#define THERMO6_CFG_POWER_UP              0x0000

#define THERMO6_CFG_COMPARATOR_MODE       0x0000
#define THERMO6_CFG_INTERRUPT_MODE        0x0200

#define THERMO6_CFG_FAULT_QUEUE_1         0x0000
#define THERMO6_CFG_FAULT_QUEUE_2         0x0800
#define THERMO6_CFG_FAULT_QUEUE_4         0x1000
#define THERMO6_CFG_FAULT_QUEUE_6         0x1800
/** \} */

/**
 * \defgroup temp_format Temperature format
 * \{
 */
#define THERMO6_TEMP_FORMAT_CELSIUS 0
#define THERMO6_TEMP_FORMAT_FAHRENHEIT 2
#define THERMO6_TEMP_FORMAT_KELVIN 1
/** \} */

/**
 * \defgroup temp_resolution Temperature resolution
 * \{
 */
#define THERMO6_TEMP_RESOLUTION_12bit  3
#define THERMO6_TEMP_RESOLUTION_10bit  2
#define THERMO6_TEMP_RESOLUTION_9bit   1
#define THERMO6_TEMP_RESOLUTION_8bit   0
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
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint8_t temp_resolution;

} thermo6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo6_cfg_t;

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
void thermo6_cfg_setup ( thermo6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO6_RETVAL thermo6_init ( thermo6_t *ctx, thermo6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Thermo6 click.
 *
 * @note Default configuration of the chip contains the settings :
 * <pre>
 *     ** Config register
 *            - THERMO6_CFG_CONVERSION_RATE_8
 *            - THERMO6_CFG_PEC_ENABLE
 *            - THERMO6_CFG_TIMEOUT_ENABLE
 *            - THERMO6_CFG_RESOLUTION_12
 *            - THERMO6_CFG_NORMAL_FORMAT
 *            - THERMO6_CFG_POWER_UP
 *            - THERMO6_CFG_COMPARATOR_MODE
 *            - THERMO6_CFG_FAULT_QUEUE_1
 * </pre>
 */
void thermo6_default_cfg ( thermo6_t *ctx );

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
void thermo6_generic_write ( thermo6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void thermo6_generic_read ( thermo6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Temperature function
 *
 * @param ctx            Click object.
 * @param temp_format    Temperature format (FORMAT_CELSIUS, FORMAT_FAHRENHEIT or FORMAT_KELVIN).
 * @returns Temperature data
 *
 * @description Reads sensor and performs calculations in order to return result value representing current temperature.
**/
float thermo6_get_temperature_data ( thermo6_t *ctx, uint8_t temp_format );

/**
 * @brief Set other register
 *
 * @param ctx            Click object.
 * @param reg      Select register (REG_TEMP_HYST or REG_TEMP_OS)
 * @param tx_data  Data for write in the register
 *
 * @description Sets new (shutdown threshold or hysteresis) value.
 */
void thermo6_set_other_register ( thermo6_t *ctx, uint8_t reg, float tx_data );

/**
 * @brief Set other register
 *
 * @param ctx            Click object.
 * @param reg      Select register (REG_TEMP_HYST or REG_TEMP_OS)
 * @returns float result value representing current overtemperature shutdown threshold or hysteresis
 *
 * @description  Reads current overtemperature shutdown threshold or hysteresis.
 */
float thermo6_get_other_register( thermo6_t *ctx, uint8_t reg );

/**
 * @brief Read over-temperature status function
 *
 * @param ctx            Click object.
 * @returns result 8-bit value that represent configuration register's B15 state :
 *          - '0' :  value in the TOS register has not been exceeded
 *          - '1' :  value in the TOS register has been exceeded
 *
 * @description  Reads configuration register's B15, that indicates that the over-temperature value in the TOS register has been exceeded.
 * @note Configuration register's B15 behavior is controlled by the Comparator/Interrupt bit.
 */
uint8_t thermo6_get_over_temp_status( thermo6_t *ctx );

/**
 * @brief Write configuration function
 *
 * @param ctx            Click object.
 * @param cfg_data  16-bit data that defines wanted configuration
 *
 * @description writes 16-bit data into configuration register.
 * @note Consult datasheet in order to discern what to write into register or use predefined values.
 */
void thermo6_set_register_cfg ( thermo6_t *ctx, uint16_t cfg_data );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

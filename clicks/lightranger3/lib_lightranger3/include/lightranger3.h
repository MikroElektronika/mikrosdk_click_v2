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
 * \brief This file contains API for Light Ranger 3 Click driver.
 *
 * \addtogroup lightranger3 Light Ranger 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LIGHTRANGER3_H
#define LIGHTRANGER3_H

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
#define LIGHTRANGER3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LIGHTRANGER3_RETVAL  uint8_t

#define LIGHTRANGER3_OK           0x00
#define LIGHTRANGER3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define LIGHTRANGER3_REG_ICSR               0x00
#define LIGHTRANGER3_REG_IER                0x02
#define LIGHTRANGER3_REG_CMD                0x04
#define LIGHTRANGER3_REG_DEV_STATUS         0x06
#define LIGHTRANGER3_REG_RESULT             0x08
#define LIGHTRANGER3_REG_RESULT_CONFIG      0x0A
#define LIGHTRANGER3_REG_CMD_CONFIG_A       0x0C
#define LIGHTRANGER3_REG_CMD_CONFIG_B       0x0E
#define LIGHTRANGER3_REG_HOST_TO_MCPU_MBX   0x10
#define LIGHTRANGER3_REG_MCPU_TO_HOST_MBX   0x12
#define LIGHTRANGER3_REG_PMU_CONFIG         0x14
#define LIGHTRANGER3_REG_I2C_ADDR_PTR       0x18
#define LIGHTRANGER3_REG_I2C_DATA_PTR       0x1A
#define LIGHTRANGER3_REG_I2C_INIT_CFG       0x1C
#define LIGHTRANGER3_REG_MCPU_PM_CTRL       0x1E
#define LIGHTRANGER3_REG_HW_FW_CONFIG_0     0x20
#define LIGHTRANGER3_REG_HW_FW_CONFIG_1     0x22
#define LIGHTRANGER3_REG_HW_FW_CONFIG_2     0x24
#define LIGHTRANGER3_REG_HW_FW_CONFIG_3     0x26
#define LIGHTRANGER3_REG_DEVICE_ID          0x28
#define LIGHTRANGER3_REG_PTCH_MEMORY_CFG    0x2A
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define LIGHTRANGER3_STANDBY_MODE         0x90
#define LIGHTRANGER3_OFF_MODE             0x91
#define LIGHTRANGER3_ON_MODE              0x92
#define LIGHTRANGER3_MEASUREMENT_MODE     0x81
/** \} */

/**
 * \defgroup good Good
 * \{
 */
#define LIGHTRANGER3_ERROR    0x01
#define DISTANCE_IS_GOOD      0x7FFF
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

    uint16_t confidence_value;
    uint16_t distance;

} lightranger3_t;

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

    uint16_t dev_confidence_value;
    uint16_t dev_distance;

} lightranger3_cfg_t;

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
void lightranger3_cfg_setup ( lightranger3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param lightranger3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LIGHTRANGER3_RETVAL lightranger3_init ( lightranger3_t *ctx, lightranger3_cfg_t *cfg );

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
void lightranger3_generic_write ( lightranger3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void lightranger3_generic_read ( lightranger3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for write one byte in register.
 *
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written.
 * @param w_data       Data which be written in the register.
 *
 * @description This function use when you need to written one byte into the register.
 */
void lightranger3_write_byte ( lightranger3_t *ctx, uint8_t reg, uint8_t w_data );

/**
 * @brief Functions for write data in register.
 *
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written.
 * @param w_data       Data which be written in the register.
 *
 * @description This function use when you need to written data into the register.
 */
void lightranger3_write_data ( lightranger3_t *ctx, uint8_t reg, uint16_t w_data );

/**
 * @brief Functions for read one byte from register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function use when you need to reads one byte from the register.
 */
uint8_t lightranger3_read_byte ( lightranger3_t *ctx, uint8_t reg );

/**
 * @brief Functions for read data from register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function use when you need to reads data from the register.
 */
uint16_t lightranger3_read_data ( lightranger3_t *ctx, uint8_t reg );

/**
 * @brief Functions for go to standby mode.
 *
 * @param ctx          Click object.
 *
 * @description This function sets standby mode.
 */
uint8_t lightranger3_set_standby_mode ( lightranger3_t *ctx );

/**
 * @brief Functions for go to OFF mode.
 *
 * @param ctx          Click object.
 *
 * @description This function sets OFF mode.
 */
uint8_t lightranger3_set_off_mode ( lightranger3_t *ctx );

/**
 * @brief Functions for go to ON mode.
 *
 * @param ctx          Click object.
 *
 * @description This function sets ON mode.
 */
uint8_t lightranger3_set_on_mode ( lightranger3_t *ctx );

/**
 * @brief Functions for go to measurement mode.
 *
 * @param ctx          Click object.
 *
 * @description This function go to measurement mode.
 */
uint8_t lightranger3_set_measurement_mode ( lightranger3_t *ctx );

/**
 * @brief Functions for measurement.
 *
 * @param ctx          Click object.
 *
 * @description This function must be called in to start measuring.
 */
uint8_t lightranger3_take_single_measurement ( lightranger3_t *ctx );

/**
 * @brief Functions for reads distance.
 *
 * @param ctx          Click object.
 *
 * @description This function reads distance.
 */
uint16_t lightranger3_get_distance ( lightranger3_t *ctx );

/**
 * @brief Functions for reads confidence value.
 *
 * @param ctx          Click object.
 *
 * @description This function reads confidence value.
 */
uint16_t lightranger3_get_confidence_value ( lightranger3_t *ctx );

/**
 * @brief Functions for reads device ID.
 *
 * @param ctx          Click object.
 *
 * @description This function reads device ID.
 */
uint16_t lightranger3_get_device_id ( lightranger3_t *ctx );

/**
 * @brief Functions for soft reset.
 *
 * @param ctx          Click object.
 *
 * @description This function for soft reset.
 */
void lightranger3_soft_reset ( lightranger3_t *ctx );

/**
 * @brief Functions for reads interrupt pin.
 *
 * @param ctx          Click object.
 *
 * @description This function reads interrupt pin.
 */
uint8_t lightranger3_get_interrupt ( lightranger3_t *ctx );

/**
 * @brief Functions for initializes chip.
 *
 * @param ctx          Click object.
 *
 * @description This function initializes chip.
 * @note Procedure has been written following instructions from the datasheet.
 */
uint8_t lightranger3_device_init ( lightranger3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LIGHTRANGER3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

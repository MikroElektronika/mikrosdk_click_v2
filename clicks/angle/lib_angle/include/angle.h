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
 * \brief This file contains API for Angle Click driver.
 *
 * \addtogroup angle Angle Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANGLE_H
#define ANGLE_H

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
#define ANGLE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); 

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANGLE_RETVAL  uint8_t

#define ANGLE_OK           0x00
#define ANGLE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_register_status Error register status
 * \{
 */
#define ANGLE_ERROR_REG_MASK              0x34 
#define ANGLE_EXTENDED_ERROR_REG_MASK     0x36 
#define ANGLE_EXTENDED_ERROR_REG          0x26 
#define ANGLE_ERROR_REG                   0x24 
#define ANGLE_STATUS_REG                  0x22 
#define ANGLE_SETTINGS_REG                0x1E 
/** \} */

/**
 * \defgroup processor_state Change Processor State
 * \{
 */
#define ANGLE_CDS_NO_CHANGLE              0x0000 << 13
#define ANGLE_CDS_IDLE_MODE               0x0002 << 13
#define ANGLE_CDS_RUN_MODE                0x0003 << 13
/** \} */

/**
 * \defgroup hard_reset Hard reset
 * \{
 */
#define ANGLE_HDR_RESET_0                 0x0000 << 12
#define ANGLE_HDR_RESET_1                 0x0001 << 12
/** \} */

/**
 * \defgroup soft_reset Soft Reset
 * \{
 */
#define ANGLE_SFR_RESET_0                 0x0000 << 11
#define ANGLE_SFR_RESET_1                 0x0001 << 11
/** \} */

/**
 * \defgroup clear_status_registar Clear Status registar
 * \{
 */
#define ANGLE_CSR_STA_0                   0x0000 << 9
#define ANGLE_CSR_STA_1                   0x0001 << 9
/** \} */

/**
 * \defgroup clear_extended_error_register Clear Extended Error register
 * \{
 */
#define ANGLE_CXE_0                       0x0000 << 8
#define ANGLE_CXE_1                       0x0001 << 8
/** \} */

/**
 * \defgroup clear_error_register Clear Error register
 * \{
 */
 #define ANGLE_CER_0                      0x0000 << 7
 #define ANGLE_CER_1                      0x0001 << 7
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

} angle_t;

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

} angle_cfg_t;

/** \} */ // End types group
 
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
void angle_cfg_setup ( angle_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANGLE_RETVAL angle_init ( angle_t *ctx, angle_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Angle click.
 */
void angle_default_cfg ( angle_t *ctx );

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
void angle_generic_write ( angle_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void angle_generic_read ( angle_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read angle.
 *
 * @param ctx          Click object.
 * @returns            Angle value.
 *
 * @description This function reads angle value.
 */
uint16_t angle_get_angle ( angle_t *ctx );

/**
 * @brief Read temperature.
 *
 * @param ctx          Click object.
 * @returns            Temperature value.
 * @description This function reads temperature value.
 */
uint16_t angle_get_temperature ( angle_t *ctx );

/**
 * @brief Read magnetics.
 *
 * @param ctx          Click object.
 * @returns            Magnetics value.
 *
 * @description This function reads magnetics value.
 */
uint16_t angle_get_magnetics ( angle_t *ctx );

/**
 * @brief Read angle status.
 *
 * @param ctx          Click object.
 * @returns
 *
 * @description This function reads the angle status.
 */
uint16_t angle_get_status( angle_t *ctx, uint8_t reg );

/**
 * @brief Setting angle configuration.
 *
 * @param ctx           Click object.
 * @param set_value     Configuration value.
 *
 * @description This function sets desired configuration.
 */
void angle_set_config ( angle_t *ctx, uint16_t set_value );

#ifdef __cplusplus
}
#endif
#endif  // _ANGLE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

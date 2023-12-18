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
 * \brief This file contains API for Temp&Hum 2 Click driver.
 *
 * \addtogroup temphum2 Temp&Hum 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM2_H
#define TEMPHUM2_H

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
#define TEMPHUM2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM2_RETVAL  uint8_t

#define TEMPHUM2_OK           0x00
#define TEMPHUM2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register  Register
 * \{
 */
#define TEMPHUM2_REG_FIRMWARE_REVISION        0x84F1
#define TEMPHUM2_REG_ELECTRONIC_ID_1          0xFA0F
#define TEMPHUM2_REG_ELECTRONIC_ID_2          0xFCC9
#define TEMPHUM2_REG_SOFT_RESET                 0xFE
#define TEMPHUM2_REG_TEMPHUM_HM_NORMAL_MODE   0x7CA2
#define TEMPHUM2_REG_TEMPHUM_NHM_NORMAL_MODE  0x7866
#define TEMPHUM2_REG_TEMPHUM_HM_FAST_MODE     0x6458
#define TEMPHUM2_REG_TEMPHUM_NHM_FAST_MODE    0x609C
#define TEMPHUM2_REG_QUERY_DEVICE_RESP        0xEFC8
#define TEMPHUM2_REG_QUERY_DEVICE_RESP1       0x805D
#define TEMPHUM2_REG_WRITE_HEATER_CONTROL       0xE6
#define TEMPHUM2_REG_READ_HEATER_CONTROL        0xE7
/** \} */
 
/**
 * \defgroup device_flag  Device flag
 * \{
 */
#define QUERY_DEVICE_ERROR  1
#define QUERY_DEVICE_OK     0
/** \} */
 
/**
 * \defgroup heater_control_register  Heater Control Register
 * \{
 */
#define TEMPHUM2_HEATER_ENABLE           0x10
#define TEMPHUM2_HEATER_DISABLE          0x00
#define TEMPHUM2_HEATER_CURRENT_6_4mA    0x00
#define TEMPHUM2_HEATER_CURRENT_9_7mA    0x01
#define TEMPHUM2_HEATER_CURRENT_13_1mA   0x02
#define TEMPHUM2_HEATER_CURRENT_19_6mA   0x04
#define TEMPHUM2_HEATER_CURRENT_32_4mA   0x08
#define TEMPHUM2_HEATER_CURRENT_53_5mA   0x0F
/** \} */
 
/**
 * \defgroup mode  Mode
 * \{
 */
#define TEMPHUM2_NO_HOLD_MODE  0x01
#define TEMPHUM2_HOLD_MODE     0x02
#define TEMPHUM2_NORMAL_MODE   0x01
#define TEMPHUM2_FAST_MODE     0x01
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

} temphum2_t;

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

} temphum2_cfg_t;

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
void temphum2_cfg_setup ( temphum2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM2_RETVAL temphum2_init ( temphum2_t *ctx, temphum2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note
 * <pre>
 *    Set: TEMPHUM2_NO_HOLD_MODE
 *          - TEMPHUM2_NORMAL_MODE
 *    Set: TEMPHUM2_REG_WRITE_HEATER_CONTROL
 *          - TEMPHUM2_HEATER_ENABLE | TEMPHUM2_HEATER_CURRENT_6_4mA
 * </pre>
 * @description This function executes default configuration for TempHum2 click.
 */
void temphum2_default_cfg ( temphum2_t *ctx );

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
void temphum2_generic_write ( temphum2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param tx_buf       Register buffer.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void temphum2_generic_read ( temphum2_t *ctx, uint8_t *tx_buf, uint8_t *data_buf, uint8_t len );

/**
 * @brief This function for reads Firmware Revision
 *
 * @param ctx          Click object.
 *
 * @return Firmware Revision ( 0x10 = Firmware version 1.0 )
 */
uint8_t temphum2_read_firmware_revision ( temphum2_t *ctx );

/**
 * @brief This function for reads Eletronic ID
 *
 * @param ctx             Click object.
 * @param electronicI_id  buffer that will be written 8 elements Eletronic ID
 */
void temhum2_get_eletronic_id ( temphum2_t *ctx, uint8_t *electronic_id );

/**
 * @brief This function for reads Query Device
 *
 * @param ctx          Click object.
 *
 * @return QUERY_DEVICE_OK - if the read the response is 0x00 0x47 0x2B
           QUERY_DEVICE_ERROR - if the read data is not good
 */
uint8_t temphum2_get_query_device ( temphum2_t *ctx );

/**
 * @brief Functions for set measurement mode
 *
 * @param select_mode  TEMPHUM2_NO_HOLD_MODE(default) or TEMPHUM2_HOLD_MODE
 * @param speend_mode  TEMPHUM2_NORMAL_MODE(default) or TEMPHUM2_FAST_MODE
 */
void temphum2_set_mode ( uint8_t select_mode, uint8_t speed_mode );

/**
 * @brief Functions for mesurement
 *
 * @param ctx          Click object.
 * @param data_buffer  buffer that will be written Temperature and Humidity data
 *
 * Data:
     data_buffer[ 0 ] - Temperature
     data_buffer[ 1 ] - Humidity
 */
void temphum2_get_measurement ( temphum2_t *ctx, float *data_buffer );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

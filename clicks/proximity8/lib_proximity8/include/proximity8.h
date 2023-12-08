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
 * \brief This file contains API for Proximity 8 Click driver.
 *
 * \addtogroup proximity8 Proximity 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY8_H
#define PROXIMITY8_H

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
#define PROXIMITY8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY8_RETVAL  uint8_t

#define PROXIMITY8_OK           0x00
#define PROXIMITY8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define PROXIMITY8_REG_PS_CONFIG_12          0x03
#define PROXIMITY8_REG_PS_CONFIG_34          0x04
#define PROXIMITY8_REG_THRESHOLD_LOW         0x05
#define PROXIMITY8_REG_THRESHOLD_HIGH        0x06
#define PROXIMITY8_REG_CANCELLATION_LEVEL    0x07
#define PROXIMITY8_REG_PS_CONFIG_5           0x08
#define PROXIMITY8_REG_PROX_DATA             0xF2
#define PROXIMITY8_REG_INTERRUPT_FLAG        0xF3
#define PROXIMITY8_REG_DEVICE_ID             0xF4
/** \} */

/**
 * \defgroup config_1_2_reg Configuration 1/2 reg[0x03]
 * \{
 */
#define PROXIMITY8_CFG12_PS_IT_1T              0x0000
#define PROXIMITY8_CFG12_PS_IT_2T              0x4000
#define PROXIMITY8_CFG12_PS_IT_4T              0x8000
#define PROXIMITY8_CFG12_PS_IT_8T              0xC000
#define PROXIMITY8_CFG12_MPS_1                 0x0000
#define PROXIMITY8_CFG12_MPS_2                 0x1000
#define PROXIMITY8_CFG12_MPS_4                 0x2000
#define PROXIMITY8_CFG12_MPS_8                 0x3000
#define PROXIMITY8_CFG12_ITB_25us              0x0000
#define PROXIMITY8_CFG12_ITB_50us              0x0800
#define PROXIMITY8_CFG12_PERIOD_8ms            0x0000
#define PROXIMITY8_CFG12_PERIOD_16ms           0x0040
#define PROXIMITY8_CFG12_PERIOD_32ms           0x0080
#define PROXIMITY8_CFG12_PERIOD_64ms           0x00C0
#define PROXIMITY8_CFG12_PERS_1                0x0000
#define PROXIMITY8_CFG12_PERS_2                0x0010
#define PROXIMITY8_CFG12_PERS_3                0x0020
#define PROXIMITY8_CFG12_PERS_4                0x0030
#define PROXIMITY8_CFG12_INT_ENABLE            0x0008
#define PROXIMITY8_CFG12_INT_DISABLE           0x0004
#define PROXIMITY8_CFG12_SMART_PERS_DISABLE    0x0000
#define PROXIMITY8_CFG12_SMART_PERS_ENABLE     0x0002
#define PROXIMITY8_CFG12_SD_POWER_ON           0x0000
#define PROXIMITY8_CFG12_SD_SHUT_DOWN          0x0001
/** \} */

/**
 * \defgroup config_3_4_reg Configuration 3/4 reg[0x04]
 * \{
 */
#define PROXIMITY8_CFG34_OFF_SUNLIGHT_CANCEL    0x0000
#define PROXIMITY8_CFG34_ON_SUNLIGHT_CANCEL     0x8000
#define PROXIMITY8_CFG34_SC_CUR_X1              0x0000
#define PROXIMITY8_CFG34_SC_CUR_X2              0x2000
#define PROXIMITY8_CFG34_SC_CUR_X4              0x4000
#define PROXIMITY8_CFG34_SC_CUR_X8              0x6000
#define PROXIMITY8_CFG34_PS_OUTPUT_12bit        0x0000
#define PROXIMITY8_CFG34_PS_OUTPUT_16bit        0x1000
#define PROXIMITY8_CFG34_VCSEL_I_7mA            0x0000
#define PROXIMITY8_CFG34_VCSEL_I_11mA           0x0100
#define PROXIMITY8_CFG34_VCSEL_I_14mA           0x0200
#define PROXIMITY8_CFG34_VCSEL_I_17mA           0x0300
#define PROXIMITY8_CFG34_VCSEL_I_20mA           0x0400
#define PROXIMITY8_CFG34_AF_MODE_AUTO           0x0000
#define PROXIMITY8_CFG34_AF_MODE_FORCE          0x0040
#define PROXIMITY8_CFG34_FOR_TRIG_ACTIVE        0x0000
#define PROXIMITY8_CFG34_FOR_TRIG_ONE_TIME      0x0020
/** \} */

/**
 * \defgroup dev_val Device Values
 * \{
 */
#define PROXIMITY8_DEVICE_ID    0x0588
#define PROXIMITY8_DEVICE_SLAVE_ADDRESS    0x60
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

} proximity8_t;

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

} proximity8_cfg_t;

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
void proximity8_cfg_setup ( proximity8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY8_RETVAL proximity8_init ( proximity8_t *ctx, proximity8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity8 click.
 */
void proximity8_default_cfg ( proximity8_t *ctx );

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
void proximity8_generic_write ( proximity8_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 *
 * @description This function reads data from the desired register.
 */
void proximity8_generic_read ( proximity8_t *ctx, uint8_t reg, uint16_t *data_buf );

/**
 * @brief Get interrupt state on the INT pin
 *
 * @param ctx          Click object.
 * 
 * @return Interrupt state
 * 
 * @description This function returns Interrupt state.
 */
uint8_t proximity8_get_interrupt_state( proximity8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

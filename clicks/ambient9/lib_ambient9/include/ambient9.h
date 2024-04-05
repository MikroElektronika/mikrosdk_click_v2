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
 * \brief This file contains API for Ambient 9 Click driver.
 *
 * \addtogroup ambient9 Ambient 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT9_H
#define AMBIENT9_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define AMBIENT9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT9_RETVAL  uint8_t

#define AMBIENT9_OK           0x00
#define AMBIENT9_INIT_ERROR   0xFF
/** \} */

#define  AMBIENT9_SLAVE_ADDR                 0x53 

#define  AMBIENT9_REG_MAIN_CTRL              0x00 
#define  AMBIENT9_REG_PS_LED                 0x01 
#define  AMBIENT9_REG_PS_PULSES              0x02 
#define  AMBIENT9_REG_PS_MEAS_RATE           0x03 
#define  AMBIENT9_REG_ALS_MEAS_RATE          0x04 
#define  AMBIENT9_REG_ALS_GAIN               0x05 
#define  AMBIENT9_REG_PART_ID                0x06 
#define  AMBIENT9_REG_MAIN_STATUS            0x07 
#define  AMBIENT9_REG_PS_DATA_0              0x08 
#define  AMBIENT9_REG_PS_DATA_1              0x09 
#define  AMBIENT9_REG_LS_CLEAR_DATA_0        0x0A 
#define  AMBIENT9_REG_LS_CLEAR_DATA_1        0x0B 
#define  AMBIENT9_REG_LS_CLEAR_DATA_2        0x0C 
#define  AMBIENT9_REG_ALS_DATA_0             0x0D 
#define  AMBIENT9_REG_ALS_DATA_1             0x0E 
#define  AMBIENT9_REG_ALS_DATA_2             0x0F 
#define  AMBIENT9_REG_INT_CFG                0x19 
#define  AMBIENT9_REG_INT_PST                0x1A 
#define  AMBIENT9_REG_PS_THRES_UP_0          0x1B 
#define  AMBIENT9_REG_PS_THRES_UP_1          0x1C 
#define  AMBIENT9_REG_PS_THRES_LOW_0         0x1D 
#define  AMBIENT9_REG_PS_THRES_LOW_1         0x1E 
#define  AMBIENT9_REG_PS_CAN_DIG_0           0x1F 
#define  AMBIENT9_REG_PS_CAN_DIG_1           0x20 
#define  AMBIENT9_REG_PS_CAN_ANA_DURATION    0x21 
#define  AMBIENT9_REG_PS_CAN_ANA_CURRENT     0x22 
#define  AMBIENT9_REG_PS_AV_HYST             0x23 
#define  AMBIENT9_REG_ALS_THRES_UP_0         0x24 
#define  AMBIENT9_REG_ALS_THRES_UP_1         0x25 
#define  AMBIENT9_REG_ALS_THRES_UP_2         0x26 
#define  AMBIENT9_REG_ALS_THRES_LOW_0        0x27 
#define  AMBIENT9_REG_ALS_THRES_LOW_1        0x28 
#define  AMBIENT9_REG_ALS_THRES_LOW_2        0x29 
#define  AMBIENT9_REG_ALS_THRES_VAR          0x2A 

#define  AMBIENT9_PART_ID_VAL                0x03 
#define  AMBIENT9_POWER_ON                   0x20 

#define  AMBIENT9_ALS                        0xAA 
#define  AMBIENT9_PROXY                      0xBB 

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

} ambient9_t;

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

} ambient9_cfg_t;

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
void ambient9_cfg_setup ( ambient9_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ambient9 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMBIENT9_RETVAL ambient9_init ( ambient9_t *ctx, ambient9_cfg_t *cfg );

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
void ambient9_generic_write ( ambient9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void ambient9_generic_read ( ambient9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic function for getting int pin status
 * 
 * @param ctx          Click object.
 * 
 * @return Interrupt pin status
 */
uint8_t ambient9_get_int_status ( ambient9_t *ctx );

/**
 * @brief Generic function for reading ALS data from sensor
 * 
 * @param ctx          Click object.
 * 
 * @return Sensor data
 */
uint32_t ambient9_als_data ( ambient9_t *ctx );

/**
 * @brief Generic function for reading proximity data from sensor
 * 
 * @param ctx          Click object.
 * 
 * @return Sensor data
 */
uint16_t ambient9_proxy_data ( ambient9_t *ctx );

/**
 * @brief Function for enabeling sensor for ALS or proximity
 * 
 * @param ctx          Click object.
 * @param als_ps       Als or proximiy macro
 * 
 */
void ambient9_enable_data ( ambient9_t *ctx, uint8_t als_ps );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

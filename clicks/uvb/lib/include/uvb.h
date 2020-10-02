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
 * \brief This file contains API for UVB Click driver.
 *
 * \addtogroup uvb UVB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UVB_H
#define UVB_H

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
#define UVB_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UVB_RETVAL  uint8_t

#define UVB_OK           0x00
#define UVB_INIT_ERROR   0xFF

#define DEVICE_OK        0
#define DEVICE_ERROR     1
/** \} */

/**
 * \defgroup slave_address DEVICE SLAVE ADDRESS
 * \{
 */
#define UVB_DEVICE_SLAVE_ADDRESS      0x39
/** \} */

/**
 * \defgroup registers REGISTERS
 * \{
 */
#define UVB_REG_CHIP_ID               0x00
#define UVB_REG_MODE                  0x01
#define UVB_REG_RES_UV                0x04
#define UVB_REG_RANGE_UVB             0x07
#define UVB_REG_MODE_CTRL             0x0A
#define UVB_REG_SOFT_RESET            0x0B
#define UVB_REG_UVB_LSB               0x17
#define UVB_REG_UVB_MSB               0x18
#define UVB_REG_NVM_READ_CTRL         0x30
#define UVB_REG_NVM_MSB               0x31
#define UVB_REG_NVM_LSB               0x32
/** \} */

/**
 * \defgroup default_value DEFAULT VALUE
 * \{
 */
#define UVB_DEF_CHIP_ID               0x62
/** \} */

/**
 * \defgroup mode MODE
 * \{
 */
#define UVB_MODE_NO_OPERATION         0x00
#define UVB_MODE_UVB_OPERATION        0x20
#define UVB_MODE_NORMAL               0x00
#define UVB_MODE_LOW_POWER            0x01
#define UVB_MODE_AUTO_SHUTDOWN        0x02
#define UVB_MODE_SHUTDOWN             0x03
/** \} */

/**
 * \defgroup resolution_uv RES_UV
 * \{
 */
#define UVB_RESOLUTION_800ms          0x00
#define UVB_RESOLUTION_400ms          0x01
#define UVB_RESOLUTION_200ms          0x02
#define UVB_RESOLUTION_100ms          0x03
/** \} */

/**
 * \defgroup range_uvb RANGE UVB
 * \{
 */
#define UVB_RANGE_x1                  0x00
#define UVB_RANGE_x2                  0x01
#define UVB_RANGE_x4                  0x02
#define UVB_RANGE_x8                  0x03
#define UVB_RANGE_x16                 0x04
#define UVB_RANGE_x32                 0x05
#define UVB_RANGE_x64                 0x06
#define UVB_RANGE_x128                0x07
/** \} */

/**
 * \defgroup mode_ctrl MODE CTRL
 * \{
 */
#define UVB_MCTRL_SLEEP_2_TIMES       0x00
#define UVB_MCTRL_SLEEP_4_TIMES       0x01
#define UVB_MCTRL_SLEEP_8_TIMES       0x02
#define UVB_MCTRL_SLEEP_16_TIMES      0x03
#define UVB_MCTRL_SLEEP_32_TIMES      0x04
#define UVB_MCTRL_SLEEP_64_TIMES      0x05
#define UVB_MCTRL_SLEEP_128_TIMES     0x06
#define UVB_MCTRL_SLEEP_256_TIMES     0x07
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

} uvb_t;

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

} uvb_cfg_t;

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
void uvb_cfg_setup ( uvb_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UVB_RETVAL uvb_init ( uvb_t *ctx, uvb_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Uvb click.
 */
void uvb_default_cfg ( uvb_t *ctx );

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
void uvb_generic_write ( uvb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 *
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void uvb_generic_read ( uvb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Configuration register
 *
 * @param ctx       Click object. 
 *
 * @param reg       Register Address
 * @param cfg       Config data
 *
 * @description This function configure register.
 */
void uvb_configuration ( uvb_t *ctx, uint8_t reg, uint8_t cfg );

/**
 * @brief Read one byte data from register
 *
 * @param ctx        Click object. 
 * @param reg        Register Address
 *
 * @returns One byte data
 *
 * @description This function reads one byte of data.
 */
uint8_t uvb_read_byte ( uvb_t *ctx, uint8_t reg );

/**
 * @brief Check communication
 *
 * @param ctx          Click object.
 * 
 * @returns  if device communication ok return [0], else return [1]
 *
 * @description This function checks communication.
 */
uint8_t uvb_check_communication ( uvb_t *ctx );

/**
 * @brief Get UVB data 
 *
 * @param ctx          Click object.
 * 
 * @returns (16 bit) UVB data
 *
 * @description This function gets UVB data.
 */
uint16_t uvb_get_uv_data ( uvb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _UVB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

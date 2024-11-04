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
 * \brief This file contains API for FRAM 3 Click driver.
 *
 * \addtogroup fram3 FRAM 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FRAM3_H
#define FRAM3_H

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
#define FRAM3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FRAM3_RETVAL  uint8_t

#define FRAM3_OK           0x00
#define FRAM3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define  FRAM3_SLAVE_ADDR                        0x50
/** \} */
 
/**
 * \defgroup max_size Max size
 * \{
 */ 
#define  FRAM3_MAX_ADDR                          0x6F
#define  FRAM3_MAX_BUF_SIZE                      16
/** \} */
 
/**
 * \defgroup commands Commands
 * \{
 */
#define  FRAM3_CMD_AES_RNG_GEN                   0x1D
#define  FRAM3_CMD_AES_CHALLENGE_RESPONSE_A      0x1B
#define  FRAM3_CMD_AES_CHALLENGE_RESPONSE_B      0x1E
#define  FRAM3_CMD_ID_READ                       0x63
#define  FRAM3_CMD_AES_ID_READ_MAC_A             0x8B
#define  FRAM3_CMD_AES_ID_READ_MAC_B             0x8E
#define  FRAM3_CMD_COUNTER_READ                  0x66
#define  FRAM3_CMD_COUNTER_INC                   0x65
#define  FRAM3_CMD_AES_COUNTER_READ_MAC_A        0x2B
#define  FRAM3_CMD_AES_COUNTER_READ_MAC_B        0x2E
#define  FRAM3_CMD_AES_COUNTER_INC_MAC_A         0x4B
#define  FRAM3_CMD_AES_COUNTER_INC_MAC_B         0x4E
#define  FRAM3_CMD_OTW_FRAM_READ                 0x2D
#define  FRAM3_CMD_OTW_FRAM_WRITE                0x27
#define  FRAM3_CMD_PROTECT_AREA_CONF             0xCA
#define  FRAM3_CMD_PROTECT_AREA_READ             0x8D
#define  FRAM3_CMD_PROTECT_AREA_WRITE            0x87
#define  FRAM3_CMD_MEMORY_RESET                  0xA5
#define  FRAM3_CMD_FRAM_READ                     0x4D
#define  FRAM3_CMD_FRAM_WRITE                    0x47
#define  FRAM3_CMD_ID_WRITE                      0xC3
#define  FRAM3_CMD_FUNC_CONF_WRITE               0xA6
#define  FRAM3_CMD_SEC_KEY_WRITE                 0xA9
#define  FRAM3_CMD_PASSWORD_CHG                  0xC9
#define  FRAM3_CMD_MIXING_CONST_WRITE            0xCC
#define  FRAM3_CMD_LIFE_CYCLE_CHG                0x6C
#define  FRAM3_CMD_STATUS_READ                   0x6A
/** \} */
 
/**
 * \defgroup status Status
 * \{
 */ 
#define  FRAM3_SUCCESS                           0xAA
#define  FRAM3_ERROR                             0xBB
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

} fram3_t;

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

} fram3_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void fram3_cfg_setup ( fram3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FRAM3_RETVAL fram3_init ( fram3_t *ctx, fram3_cfg_t *cfg );

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
void fram3_generic_write ( fram3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void fram3_generic_read ( fram3_t *ctx, uint8_t *tx_buf, uint8_t *data_buf, uint8_t len );

/**
 * @brief Memory read function
 * 
 * @param ctx          Click object.
 * @param start_addr   Address from where data will be read
 * @param data_buf     OUTPUT buffer data
 * @param n_buf_size   Number of bytes data
 *
 * @return either FRAM3_SUCCESSFUL or FRAM3_ERROR.
 */
uint8_t fram3_read_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size );

/**
 * @brief Memory write function
 * 
 * @param ctx          Click object.
 * @param start_addr   Address from where data will be written
 * @param data_buf     OUTPUT buffer data
 * @param n_buf_size   Number of bytes data
 *
 * @return either FRAM3_SUCCESSFUL or FRAM3_ERROR.
 */
uint8_t fram3_write_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size );

#ifdef __cplusplus
}
#endif
#endif  // _FRAM3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

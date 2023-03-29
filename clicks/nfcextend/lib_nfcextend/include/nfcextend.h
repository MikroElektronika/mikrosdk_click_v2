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
 * \brief This file contains API for NFC Extend Click driver.
 *
 * \addtogroup nfcextend NFC Extend Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NFCEXTEND_H
#define NFCEXTEND_H

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
#define NFCEXTEND_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NFCEXTEND_RETVAL  uint8_t

#define NFCEXTEND_OK           0x00
#define NFCEXTEND_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define NFCEXTEND_I2C_SLAVE_ADDRESS   0x53
/** \} */

/**
 * \defgroup memory_map Memory Map
 * \{
 */
// MEMORY AREAS
#define NFCEXTEND_MEMORY_USER              0x01
#define NFCEXTEND_MEMORY_DYNAMIC           0x02
#define NFCEXTEND_MEMORY_MAILBOX           0x03
#define NFCEXTEND_MEMORY_SYSTEM            0x04

// SYSTEM REGISTER ADDRESSES
#define NFCEXTEND_SYSTEM_REG_GPO           0x0000
#define NFCEXTEND_SYSTEM_REG_IT_TIME       0x0001
#define NFCEXTEND_SYSTEM_REG_EH_MODE       0x0002
#define NFCEXTEND_SYSTEM_REG_RF_MNGT       0x0003
#define NFCEXTEND_SYSTEM_REG_RFA1SS        0x0004
#define NFCEXTEND_SYSTEM_REG_ENDA1         0x0005
#define NFCEXTEND_SYSTEM_REG_RFA2SS        0x0006
#define NFCEXTEND_SYSTEM_REG_ENDA2         0x0007
#define NFCEXTEND_SYSTEM_REG_RFA3SS        0x0008
#define NFCEXTEND_SYSTEM_REG_ENDA3         0x0009
#define NFCEXTEND_SYSTEM_REG_RFA4SS        0x000A
#define NFCEXTEND_SYSTEM_REG_I2CSS         0x000B
#define NFCEXTEND_SYSTEM_REG_LOCK_CCFILE   0x000C
#define NFCEXTEND_SYSTEM_REG_MB_MODE       0x000D
#define NFCEXTEND_SYSTEM_REG_MB_WDG        0x000E
#define NFCEXTEND_SYSTEM_REG_LOCK_CFG      0x000F
#define NFCEXTEND_SYSTEM_REG_LOCK_DSFID    0x0010
#define NFCEXTEND_SYSTEM_REG_LOCK_AFI      0x0011
#define NFCEXTEND_SYSTEM_REG_DSFID         0x0012
#define NFCEXTEND_SYSTEM_REG_AFI           0x0013
#define NFCEXTEND_SYSTEM_REG_MEM_SIZE_1    0x0014
#define NFCEXTEND_SYSTEM_REG_MEM_SIZE_2    0x0015
#define NFCEXTEND_SYSTEM_REG_BLK_SIZE      0x0016
#define NFCEXTEND_SYSTEM_REG_IC_REF        0x0017
#define NFCEXTEND_SYSTEM_REG_UID_1         0x0018
#define NFCEXTEND_SYSTEM_REG_UID_2         0x0019
#define NFCEXTEND_SYSTEM_REG_UID_3         0x001A
#define NFCEXTEND_SYSTEM_REG_UID_4         0x001B
#define NFCEXTEND_SYSTEM_REG_UID_5         0x001C
#define NFCEXTEND_SYSTEM_REG_UID_6         0x001D
#define NFCEXTEND_SYSTEM_REG_UID_7         0x001E
#define NFCEXTEND_SYSTEM_REG_UID_8         0x001F
#define NFCEXTEND_SYSTEM_REG_IC_REV        0x0020
#define NFCEXTEND_SYSTEM_REG_ST_RES_1      0x0021
#define NFCEXTEND_SYSTEM_REG_ST_RES_2      0x0022
#define NFCEXTEND_SYSTEM_REG_ST_RES_3      0x0023
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_1     0x0900
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_2     0x0901
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_3     0x0902
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_4     0x0903
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_5     0x0904
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_6     0x0905
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_7     0x0906
#define NFCEXTEND_SYSTEM_REG_I2C_PWD_8     0x0907

// DYNAMIC REGISTER ADDRESSES
#define NFCEXTEND_DYNAMIC_REG_GPO_CTRL     0x2000
#define NFCEXTEND_DYNAMIC_REG_RESERVED_1   0x2001
#define NFCEXTEND_DYNAMIC_REG_EH_CTRL      0x2002
#define NFCEXTEND_DYNAMIC_REG_RF_MNGT      0x2003
#define NFCEXTEND_DYNAMIC_REG_I2C_SSO      0x2004
#define NFCEXTEND_DYNAMIC_REG_IT_STS       0x2005
#define NFCEXTEND_DYNAMIC_REG_MB_CTRL      0x2006
#define NFCEXTEND_DYNAMIC_REG_MB_LEN       0x2007
/** \} */

/**
 * \defgroup mailbox Mailbox
 * \{
 */
// MAILBOX REGISTER ADDRESSES
#define NFCEXTEND_MAILBOX_REG_BYTE_0             0x2008
          
// MAILBOX ENABLE/DISABLE          
#define NFCEXTEND_MAILBOX_DISABLE                0x00
#define NFCEXTEND_MAILBOX_ENABLE                 0x01
          
// RF ENABLE/DISABLE          
#define NFCEXTEND_RF_DISABLE                     0x00
#define NFCEXTEND_RF_ENABLE                      0x01
          
// PASSWORD PRESENT          
#define NFCEXTEND_PASSWORD_LEN                   8
#define NFCEXTEND_PASSWORD_BUFFER_SIZE           NFCEXTEND_PASSWORD_LEN * 2 + 1
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief I2C communication block object definition.
 */
typedef struct
{
    uint8_t memory_area;
    uint16_t reg_addr;
    uint8_t *data_buf;
    uint16_t len;

} nfcextend_block_t;

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

} nfcextend_t;

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

} nfcextend_cfg_t;

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
void nfcextend_cfg_setup ( nfcextend_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param nfcextend Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NFCEXTEND_RETVAL nfcextend_init ( nfcextend_t *ctx, nfcextend_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for NfcExtend click.
 */
uint8_t nfcextend_default_cfg ( nfcextend_t *ctx );

/**
 * @brief Password present function.
 *
 * @param ctx        Click object.
 * @param pass_buf   Password buffer pointer.
 *
 * @description This function presents the specified password to the chip.
 */
uint8_t nfcextend_password_present ( nfcextend_t *ctx, uint8_t *pass_buf );

/**
 * @brief I2C set function.
 *
 * @param ctx        Click object.
 * @param block      I2C block structure.
 *
 * @description This function writes data to the chip.
 */
uint8_t nfcextend_i2c_set ( nfcextend_t *ctx, nfcextend_block_t *block );

/**
 * @brief I2C get function.
 *
 * @param ctx        Click object.
 * @param block      I2C block structure.
 *
 * @description This function reads data from the chip.
 */
uint8_t nfcextend_i2c_get ( nfcextend_t *ctx, nfcextend_block_t *block );

/**
 * @brief Digital read interrupt.
 *
 * @param ctx        Click object.
 * @param block      I2C block structure.
 *
 * @description This function reads the digital signal from the INT pin.
 */
uint8_t nfcextend_digital_read_int ( nfcextend_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _NFCEXTEND_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for NFC Tag 4  Click driver.
 *
 * \addtogroup nfctag4 NFC Tag 4  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NFCTAG4_H
#define NFCTAG4_H

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
#define NFCTAG4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NFCTAG4_RETVAL  uint8_t

#define NFCTAG4_OK           0x00
#define NFCTAG4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device Address
 * \{
 */
#define NFCTAG4_DEVICE_ADDRESS      0x53
/** \} */

/**
 * \defgroup memory_areas Memory Areas
 * \{
 */
#define NFCTAG4_MEMORY_USER      0x01
#define NFCTAG4_MEMORY_DYNAMIC   0x02
#define NFCTAG4_MEMORY_MAILBOX   0x03
#define NFCTAG4_MEMORY_SYSTEM    0x04
/** \} */

/**
 * \defgroup system_register_addresses System Register Addresses
 * \{
 */
#define NFCTAG4_SYSTEM_REG_GPO           0x0000
#define NFCTAG4_SYSTEM_REG_IT_TIME       0x0001
#define NFCTAG4_SYSTEM_REG_EH_MODE       0x0002
#define NFCTAG4_SYSTEM_REG_RF_MNGT       0x0003
#define NFCTAG4_SYSTEM_REG_RFA1SS        0x0004
#define NFCTAG4_SYSTEM_REG_ENDA1         0x0005
#define NFCTAG4_SYSTEM_REG_RFA2SS        0x0006
#define NFCTAG4_SYSTEM_REG_ENDA2         0x0007
#define NFCTAG4_SYSTEM_REG_RFA3SS        0x0008
#define NFCTAG4_SYSTEM_REG_ENDA3         0x0009
#define NFCTAG4_SYSTEM_REG_RFA4SS        0x000A
#define NFCTAG4_SYSTEM_REG_I2CSS         0x000B
#define NFCTAG4_SYSTEM_REG_LOCK_CCFILE   0x000C
#define NFCTAG4_SYSTEM_REG_MB_MODE       0x000D
#define NFCTAG4_SYSTEM_REG_MB_WDG        0x000E
#define NFCTAG4_SYSTEM_REG_LOCK_CFG      0x000F
#define NFCTAG4_SYSTEM_REG_LOCK_DSFID    0x0010
#define NFCTAG4_SYSTEM_REG_LOCK_AFI      0x0011
#define NFCTAG4_SYSTEM_REG_DSFID         0x0012
#define NFCTAG4_SYSTEM_REG_AFI           0x0013
#define NFCTAG4_SYSTEM_REG_MEM_SIZE_1    0x0014
#define NFCTAG4_SYSTEM_REG_MEM_SIZE_2    0x0015
#define NFCTAG4_SYSTEM_REG_BLK_SIZE      0x0016
#define NFCTAG4_SYSTEM_REG_IC_REF        0x0017
#define NFCTAG4_SYSTEM_REG_UID_1         0x0018
#define NFCTAG4_SYSTEM_REG_UID_2         0x0019
#define NFCTAG4_SYSTEM_REG_UID_3         0x001A
#define NFCTAG4_SYSTEM_REG_UID_4         0x001B
#define NFCTAG4_SYSTEM_REG_UID_5         0x001C
#define NFCTAG4_SYSTEM_REG_UID_6         0x001D
#define NFCTAG4_SYSTEM_REG_UID_7         0x001E
#define NFCTAG4_SYSTEM_REG_UID_8         0x001F
#define NFCTAG4_SYSTEM_REG_IC_REV        0x0020
#define NFCTAG4_SYSTEM_REG_ST_RES_1      0x0021
#define NFCTAG4_SYSTEM_REG_ST_RES_2      0x0022
#define NFCTAG4_SYSTEM_REG_ST_RES_3      0x0023
#define NFCTAG4_SYSTEM_REG_I2C_PWD_1     0x0900
#define NFCTAG4_SYSTEM_REG_I2C_PWD_2     0x0901
#define NFCTAG4_SYSTEM_REG_I2C_PWD_3     0x0902
#define NFCTAG4_SYSTEM_REG_I2C_PWD_4     0x0903
#define NFCTAG4_SYSTEM_REG_I2C_PWD_5     0x0904
#define NFCTAG4_SYSTEM_REG_I2C_PWD_6     0x0905
#define NFCTAG4_SYSTEM_REG_I2C_PWD_7     0x0906
#define NFCTAG4_SYSTEM_REG_I2C_PWD_8     0x0907
/** \} */

/**
 * \defgroup dynamic_register_addresses Dynamic Register Addresses
 * \{
 */
#define NFCTAG4_DYNAMIC_REG_GPO_CTRL     0x2000
#define NFCTAG4_DYNAMIC_REG_RESERVED_1   0x2001
#define NFCTAG4_DYNAMIC_REG_EH_CTRL      0x2002
#define NFCTAG4_DYNAMIC_REG_RF_MNGT      0x2003
#define NFCTAG4_DYNAMIC_REG_I2C_SSO      0x2004
#define NFCTAG4_DYNAMIC_REG_IT_STS       0x2005
#define NFCTAG4_DYNAMIC_REG_MB_CTRL      0x2006
#define NFCTAG4_DYNAMIC_REG_MB_LEN       0x2007
/** \} */

/**
 * \defgroup mailbox_register_addresses Mailbox Register Addresses
 * \{
 */
#define NFCTAG4_MAILBOX_REG_BYTE_0       0x2008
/** \} */

/**
 * \defgroup mailbox_enable_disable Mailbox Enable/Disable
 * \{
 */
#define NFCTAG4_MAILBOX_DISABLE     0x00
#define NFCTAG4_MAILBOX_ENABLE      0x01
/** \} */

/**
 * \defgroup rf_enable_disable RF Enable/Disable
 * \{
 */
#define NFCTAG4_RF_DISABLE        0x00
#define NFCTAG4_RF_ENABLE         0x01
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} nfctag4_t;

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

} nfctag4_cfg_t;

typedef struct
{
    uint8_t memory_area;
    uint16_t register_address;
    uint16_t n_registers;

}transfer_info;
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
void nfctag4_cfg_setup ( nfctag4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NFCTAG4_RETVAL nfctag4_init ( nfctag4_t *ctx, nfctag4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for NfcTag4 click.
 */
void nfctag4_default_cfg ( nfctag4_t *ctx );

/**
 * @brief Getting INT pin state
 *
 * @param ctx  Click object.
 *
 * @returns 0 for LOW pin state
 * @returns 1 for HIGH pin state
 *
 * @description This function returns INT pin state
 */
uint8_t nfctag4_int_get ( nfctag4_t* ctx );

/**
 * @brief Getting registers via I2C
 *
 * @param ctx                Click object.
 * @param dev                Structure with info needed for transfer.
 * @param register_buffer    register buffer
 *
 * @returns 0 for correct memory area and number of registers
 * @returns 1 for incorrect memory area and number of registers
 *
 * @description This function gets specified number of registers, from specified memory area, starting from specified register address
 */
uint8_t nfctag4_i2c_get ( nfctag4_t* ctx, transfer_info* dev, uint8_t* register_buffer );

/**
 * @brief Setting registers via I2C
 *
 * @param ctx                Click object.
 * @param dev                Structure with info needed for transfer.
 * @param register_buffer    register buffer
 *
 * @returns 0 for correct memory area and number of registers
 * @returns 1 for incorrect memory area and number of registers
 *
 * @description This function sets specified number of registers, from specified memory area, starting from specified register address
 */
uint8_t nfctag4_i2c_set ( nfctag4_t* ctx, transfer_info* dev, uint8_t* register_buffer );

/**
 * @brief Presenting password to device
 *
 * @param ctx             Click object.
 * @param password_bytes  password buffer
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function presents password to device in order to open I2C security session
 */
uint8_t nfctag4_password_present ( nfctag4_t* ctx, uint8_t* password_bytes );

/**
 * @brief Writing password to device
 *
 * @param ctx             Click object.
 * @param password_bytes  password buffer
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function writes password to device in order to set new I2C security session password
 */
uint8_t nfctag4_password_write ( nfctag4_t* ctx, uint8_t* password_bytes );

/**
 * @brief Enabling or disabling mailbox
 *
 * @param ctx              Click object.
 * @param enable_mailbox   enable mailbox (use macros)
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function enables or disables mailbox functionality
 */
uint8_t nfctag4_enable_mailbox ( nfctag4_t* ctx, uint8_t enable_mailbox );

/**
 * @brief Enabling or disabling RF
 *
 * @param ctx              Click object.
 * @param enable_rf        enable RF (use macros)
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function enables or disables RF functionality
 */
uint8_t nfctag4_enable_rf ( nfctag4_t* ctx, uint8_t enable_rf );


#ifdef __cplusplus
}
#endif
#endif  // _NFCTAG4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

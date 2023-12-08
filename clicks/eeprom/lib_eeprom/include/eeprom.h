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
 * \file eeprom.h
 *
 * \brief This file contains API for EEPROM Click driver.
 *
 * \addtogroup eeprom EEPROM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup mem_block Memory Block
 * \{
 */
#define EEPROM_BLOCK_ADDR_START   0x00
#define EEPROM_BLOCK_ADDR_MIDDLE  0x80
#define EEPROM_BLOCK_ADDR_END     0xFF
/** \} */

/**
 * \defgroup ndata_lim Data Transfer Limit
 * \{
 */
#define EEPROM_NBYTES_MIN   1
#define EEPROM_NBYTES_PAGE  16
#define EEPROM_NBYTES_MAX   256
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define EEPROM_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.wp  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES

/**
 * @brief Click address (memory block) selection.
 */
typedef enum
{
    EEPROM_I2C_ADDR_SEL_0 = 0,
    EEPROM_I2C_ADDR_SEL_1,
    EEPROM_I2C_ADDR_SEL_2,
    EEPROM_I2C_ADDR_SEL_3,
    EEPROM_I2C_ADDR_SEL_4,
    EEPROM_I2C_ADDR_SEL_5,
    EEPROM_I2C_ADDR_SEL_6,
    EEPROM_I2C_ADDR_SEL_7

} eeprom_i2c_address_selector_t;

/**
 * @brief Click error code.
 */
typedef enum
{
    EEPROM_RETVAL_OK           = 0x00,
    EEPROM_RETVAL_ERR_DRV_INIT = 0xFE,
    EEPROM_RETVAL_ERR_NBYTES

} eeprom_retval_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    //  Click mikrobus DRV objects.
    digital_out_t  wp;
    i2c_master_t   i2c;
    //  Device slave address.
    uint8_t  slave_addr;

} eeprom_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Used mikrobus pins.
    pin_name_t  wp;
    pin_name_t  scl;
    pin_name_t  sda;
    //  Device address selector.
    eeprom_i2c_address_selector_t  addr_sel;
    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} eeprom_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Structure Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 */
void eeprom_cfg_setup( eeprom_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param context  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x00 - Ok, 0xFE - Driver init error.
 *
 * @description This function initializes peripherals and pins used by EEPROM click.
 */
eeprom_retval_t eeprom_init( eeprom_t *context, eeprom_cfg_t *cfg );

/**
 * @brief Byte Write function.
 *
 * @param context  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @description This function writes one byte data to the desired register.
 */
void eeprom_write_byte( eeprom_t *context, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Page Write function.
 *
 * @param context  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @description This function writes 16 bytes data starting from the selected register.
 */
void eeprom_write_page( eeprom_t *context, uint8_t reg_addr, uint8_t *data_in );

/**
 * @brief Byte Read function.
 *
 * @param context  Click object.
 * @param reg_addr  Register address.
 *
 * @returns Data value from the selected register.
 *
 * @description This function reads one byte data from the desired register.
 */
uint8_t eeprom_read_byte( eeprom_t *context, uint8_t reg_addr );

/**
 * @brief Sequential Read function.
 *
 * @param context  Click object.
 * @param reg_addr  Register address.
 * @param n_bytes  Number of bytes to be read.
 * @param data_out  Memory where data be stored.
 *
 * @returns 0x00 - Ok, 0xFE - Invalid number of bytes.
 *
 * @description This function reads the desired number of bytes starting from the selected register.
 */
eeprom_retval_t eeprom_read_sequential( eeprom_t *context, uint8_t reg_addr, uint16_t n_bytes, uint8_t *data_out );

/**
 * @brief Write Enable function.
 *
 * @param context  Click object.
 *
 * @description This function allows data writing to the EEPROM.
 */
void eeprom_write_enable( eeprom_t *context );

/**
 * @brief Write Protect function.
 *
 * @param context  Click object.
 *
 * @description This function blocks data writing operation to the EEPROM.
 */
void eeprom_write_protect( eeprom_t *context );

#ifdef __cplusplus
}
#endif
#endif  //  _EEPROM_H_

/** \} */ //  End public_function group
/// \}    //  End eeprom group
/*! @} */
// ------------------------------------------------------------------------ END

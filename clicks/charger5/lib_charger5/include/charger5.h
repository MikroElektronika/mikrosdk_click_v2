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
 * \file charger5.h
 *
 * \brief This file contains API for Charger 5 Click driver.
 *
 * \addtogroup charger5 Charger 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _CHARGER5_H_
#define _CHARGER5_H_

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

 /**
 * \defgroup error_code Error Code
 * \{
 */
#define CHARGER5_RETVAL  uint8_t

#define CHARGER5_OK           0x00
#define CHARGER5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define CHARGER5_REG_WIPER0_VOL     0x00
#define CHARGER5_REG_WIPER1_VOL     0x01
#define CHARGER5_REG_WIPER0_NONVOL  0x02
#define CHARGER5_REG_WIPER1_NONVOL  0x03
#define CHARGER5_REG_TCONTROL_VOL   0x04
#define CHARGER5_REG_STATUS_VOL     0x05
#define CHARGER5_REG_DATA_EEPROM0   0x06
#define CHARGER5_REG_DATA_EEPROM1   0x07
#define CHARGER5_REG_DATA_EEPROM2   0x08
#define CHARGER5_REG_DATA_EEPROM3   0x09
#define CHARGER5_REG_DATA_EEPROM4   0x0A
#define CHARGER5_REG_DATA_EEPROM5   0x0B
#define CHARGER5_REG_DATA_EEPROM6   0x0C
#define CHARGER5_REG_DATA_EEPROM7   0x0D
#define CHARGER5_REG_DATA_EEPROM8   0x0E
#define CHARGER5_REG_DATA_EEPROM9   0x0F
/** \} */

/**
 * \defgroup curr_value Current Values
 * \{
 */
#define CHARGER5_CURRENT_100MA_MIN  0x00
#define CHARGER5_CURRENT_200MA      0x88
#define CHARGER5_CURRENT_300MA      0xBD
#define CHARGER5_CURRENT_400MA      0xD6
#define CHARGER5_CURRENT_500MA      0xE4
#define CHARGER5_CURRENT_600MA      0xEE
#define CHARGER5_CURRENT_700MA      0xF5
#define CHARGER5_CURRENT_800MA      0xFB
#define CHARGER5_CURRENT_900MA      0xFE
#define CHARGER5_CURRENT_950MA_MAX  0x0100
/** \} */

/**
 * \defgroup n_steps Wiper Increment/Decrement Steps
 * \{
 */
#define CHARGER5_STEPS_1_MIN    0x01
#define CHARGER5_STEPS_2        0x02
#define CHARGER5_STEPS_5        0x05
#define CHARGER5_STEPS_10       0x0A
#define CHARGER5_STEPS_50       0x32
#define CHARGER5_STEPS_100      0x64
#define CHARGER5_STEPS_150      0x96
#define CHARGER5_STEPS_200      0xC8
#define CHARGER5_STEPS_255_MAX  0xFF
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CHARGER5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sdi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS   )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click error code definition.
 */
typedef enum
{
    CHARGER5_STATUS_OK,
    CHARGER5_STATUS_ERROR,
    CHARGER5_MODULE_INIT_ERROR,
    CHARGER5_NSTEPS_RANGE_ERROR

} charger5_err_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    digital_out_t cs;

    //  Module.
    spi_master_t spi;
    pin_name_t chip_select;

} charger5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  sdo;
    pin_name_t  sdi;
    pin_name_t  sck;
    pin_name_t  cs;

    //  SPI module config variables.
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} charger5_cfg_t;

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
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note The all used pins will be set to unconnected state.
 */
void
charger5_cfg_setup( charger5_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns Initialization status: 0 - Ok,
 *                                 2 - Module init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for Charger 5 click.
 */
charger5_err_t
charger5_init( charger5_t *ctx, charger5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a default configuration for Charger 5
 * click.
 * @note Executes a TCONTROL register configuration, wiper resistor network 0
 *       is enabled, and wiper resistor network 1 is disabled, don't exist.
 */
void
charger5_default_cfg( charger5_t *ctx );

/**
 * @brief Generic Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address where data be written.
 * @param transfer_data  Data to be written.
 *
 * @returns Operation status: 0 - Ok,
 *                            1 - Error.
 *
 * @description This function writes 9-bit data to the selected register.
 */
charger5_err_t
charger5_generic_write( charger5_t *ctx, uint8_t reg_addr,
                        uint16_t transfer_data );

/**
 * @brief Generic Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address which from data be read.
 *
 * @returns 9-bit data.
 *
 * @description This function reads 9-bit data from the selected register.
 */
uint16_t
charger5_generic_read( charger5_t *ctx, uint8_t reg_addr );

/**
 * @brief Increment Wiper function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Wiper register address.
 * @param n_steps  Number of steps which for the selected wiper will be
 *                 incremented.
 *
 * @returns Operation status: 0 - Ok,
 *                            1 - Error.
 *
 * @description This function increments the selected wiper for the desired
 * number of steps.
 */
charger5_err_t
charger5_increment_wiper( charger5_t *ctx, uint8_t reg_addr, uint8_t n_steps );

/**
 * @brief Decrement Wiper function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Wiper register address.
 * @param n_steps  Number of steps which for the selected wiper will be
 *                 decremented.
 *
 * @returns Operation status: 0 - Ok,
 *                            1 - Error.
 *
 * @description This function decrements the selected wiper for the desired
 * number of steps.
 */
charger5_err_t
charger5_decrement_wiper( charger5_t *ctx, uint8_t reg_addr, uint8_t n_steps );

#ifdef __cplusplus
}
#endif
#endif  //  _CHARGER5_H_

/** \} */ //  End public_function group
/// \}    //  End charger5 group
/*! @} */
// ------------------------------------------------------------------------ END

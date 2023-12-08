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
 * \file templog2.h
 *
 * \brief This file contains API for Temp-Log 2 Click driver.
 *
 * \addtogroup templog2 Temp-Log 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _TEMPLOG2_H_
#define _TEMPLOG2_H_

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup registers Registers
 * \{
 */

/**
 * \defgroup address Address
 * \{
 */
#define TEMPLOG2_TEMP_REG                  0x00
#define TEMPLOG2_CONFIG_REG                0x01
#define TEMPLOG2_HIGH_LIMIT_REG            0x02
#define TEMPLOG2_LOW_LIMIT_REG             0x03
#define TEMPLOG2_EEPROM_UNLOCK_REG         0x04
#define TEMPLOG2_EEPROM1_REG               0x05
#define TEMPLOG2_EEPROM2_REG               0x06
#define TEMPLOG2_EEPROM3_REG               0x07
#define TEMPLOG2_EEPROM4_REG               0x08
#define TEMPLOG2_ID_REG                    0x0F
/** \} */

/**
 * \defgroup settings Settings
 * \{
 */
#define TEMPLOG2_15_MILISEC_0_AVG          0x00
#define TEMPLOG2_125_MILISEC_0_AVG         0x0080
#define TEMPLOG2_250_MILISEC_0_AVG         0x0100
#define TEMPLOG2_500_MILISEC_0_AVG         0x0180
#define TEMPLOG2_1_SEC_0_AVG               0x0200
#define TEMPLOG2_4_SEC_0_AVG               0x0280
#define TEMPLOG2_8_SEC_0_AVG               0x0300
#define TEMPLOG2_16_SEC_0_AVG              0x0380
#define TEMPLOG2_125_MILISEC_8_AVG         0x0020
#define TEMPLOG2_250_MILISEC_8_AVG         0x0120
#define TEMPLOG2_500_MILISEC_8_AVG         0x01A0
#define TEMPLOG2_1_SEC_8_AVG               0x0220
#define TEMPLOG2_4_SEC_8_AVG               0x02A0
#define TEMPLOG2_8_SEC_8_AVG               0x0320
#define TEMPLOG2_16_SEC_8_AVG              0x03A0
#define TEMPLOG2_500_MILISEC_32_AVG        0x0040
#define TEMPLOG2_1_SEC_32_AVG              0x0240
#define TEMPLOG2_4_SEC_32_AVG              0x02C0
#define TEMPLOG2_8_SEC_32_AVG              0x0340
#define TEMPLOG2_16_SEC_32_AVG             0x03C0
#define TEMPLOG2_1_SEC_64_AVG              0x0060
#define TEMPLOG2_4_SEC_64_AVG              0x02E0
#define TEMPLOG2_8_SEC_64_AVG              0x0360
#define TEMPLOG2_16_SEC_64_AVG             0x03E0
#define TEMPLOG2_POL_ACTIVE_LOW            0x00
#define TEMPLOG2_POL_ACTIVE_HIGH           0x0008
#define TEMPLOG2_PIN_ALERT_FLAGS           0x00
#define TEMPLOG2_PIN_DATAREADY_FLAG        0x0004

/**
 * \defgroup eeprom_protect EEPROM Protect
 * \{
 */
#define TEMPLOG2_LOCK_EEPROM               0x00
#define TEMPLOG2_UNLOCK_EEPROM             0x8000
/** \} */

/**
 * \defgroup data_values Data Values
 * \{
 */
#define TEMPLOG2_0_CELSIUS                 0x00
#define TEMPLOG2_1_CELSIUS_POS             0x0080
#define TEMPLOG2_25_CELSIUS_POS            0x0C80
#define TEMPLOG2_25_CELSIUS_NEG            0xF380
#define TEMPLOG2_100_CELSIUS_POS           0x3200
#define TEMPLOG2_256_CELSIUS_POS           0x7FFF
#define TEMPLOG2_256_CELSIUS_NEG           0x8000
/** \} */

/**
 * \defgroup data_mode Data Mode
 * \{
 */
#define TEMPLOG2_CONT_CONV_OP_MODE         0x00
#define TEMPLOG2_SHUTDOWN_OP_MODE          0x01
#define TEMPLOG2_ONE_SHOT_OP_MODE          0x02
#define TEMPLOG2_ALERT_MODE                0x00
#define TEMPLOG2_THERM_MODE                0x01
/** \} */

/** \} */ //  End settings group

/**
 * \defgroup status Status
 * \{
 */
#define TEMPLOG2_DATA_READY_MASK           0x01
#define TEMPLOG2_LOW_LIMIT_MASK            0x02
#define TEMPLOG2_HIGH_LIMIT_MASK           0x04
#define TEMPLOG2_BUSY_MASK                 0x4000
/** \} */

/** \} */ //  End registers group

/**
 * \defgroup error Error
 * \{
 */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPLOG2_OK                        0x00
#define TEMPLOG2_INVALID_ADDR              0xFF
#define TEMPLOG2_INVALID_PARAM             0xFE
#define TEMPLOG2_INIT_DRV_ERROR            0xFD
/** \} */

/**
 * \defgroup error_type Error Type
 * \{
 */
#define TEMPLOG2_RETVAL  uint8_t
/** \} */

/** \} */ //  End error group

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TEMPLOG2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click context object definition.
 */
typedef struct
{
    //  Click mikrobus DRV objects.
    digital_in_t  alt;
    i2c_master_t  i2c;

    //  Used I2C slave address.
    uint8_t  slave_addr;

} templog2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Used mikrobus pins.
    pin_name_t  alt;
    pin_name_t  scl;
    pin_name_t  sda;

    /**
     * I2C address selector.
     * Default - false. (ADDR SEL - 0)
     */
    bool  addr_sel;
    uint32_t i2c_speed;

} templog2_cfg_t;

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
 * @description This function initializes click configuration structure to init
 * state.
 *
 * @note All used pins will be set to unconnected state.
 *       ADDR SEL will be set to 0 (false) by default.
 */
void
templog2_cfg_setup( templog2_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x00 - Ok, 0xFD - Driver init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
TEMPLOG2_RETVAL
templog2_init( templog2_t *ctx, templog2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Temp-Log 2
 * click.
 */
void
templog2_default_config( templog2_t *ctx );

/**
 * @brief Write Register function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param transfer_data  Data to be written.
 *
 * @returns 0x00 - Ok, 0xFF - Invalid register address.
 *
 * @description This function writes 16-bit data to the desired register.
 */
TEMPLOG2_RETVAL
templog2_write_reg( templog2_t *ctx, uint8_t reg_addr, uint16_t transfer_data );

/**
 * @brief Read Register function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Data output.
 *
 * @returns 0x00 - Ok, 0xFF - Invalid register address.
 *
 * @description This function reads 16-bit data from the desired register.
 */
TEMPLOG2_RETVAL
templog2_read_reg( templog2_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Data Ready function.
 *
 * @param ctx  Click object.
 *
 * @returns Data ready and limit detection flags (0b0000 0xxx).
 *
 * @description This function checks data ready and limit status flags.
 */
uint8_t
templog2_data_ready( templog2_t *ctx );

/**
 * @brief Alert Checking function.
 *
 * @param ctx  Click object.
 *
 * @returns 0 or 1.
 *
 * @description This function returns the state of the Alert pin on the
 * Temp-Log 2 click.
 */
uint8_t
templog2_check_alert( templog2_t *ctx );

/**
 * @brief Read Temperature function.
 *
 * @param ctx  Click object.
 *
 * @returns Temperature [Celsius degrees].
 *
 * @description This function returns temperature calculated to Celsius degrees.
 */
float
templog2_read_temp( templog2_t *ctx );

/**
 * @brief Mode Setting function.
 *
 * @param ctx  Click object.
 * @param op_mode  Operating mode setting.
 * @param alert_mode  Alert mode setting.
 *
 * @returns 0x00 - Ok, 0xFE - Invalid parameter value.
 *
 * @description This function allows user to set operating and alert mode.
 */
TEMPLOG2_RETVAL
templog2_set_mode( templog2_t *ctx, uint8_t op_mode, uint8_t alert_mode );

/**
 * @brief EEPROM Writing function.
 *
 * @param ctx  Click object.
 * @param eeprom_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @returns 0x00 - Ok, 0xFF - Invalid register address.
 *
 * @description This function writes data to EEPROM.
 */
TEMPLOG2_RETVAL
templog2_write_eeprom( templog2_t *ctx, uint8_t eeprom_addr, uint16_t data_in );

/**
 * @brief Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a device reset and makes 1 second delay
 * until device was stabilized.
 */
void
templog2_reset( templog2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _TEMPLOG2_H_

/** \} */ //  End public_function group
/// \}    //  End templog2 group
/*! @} */
// ------------------------------------------------------------------------ END

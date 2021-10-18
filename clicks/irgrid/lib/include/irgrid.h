/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file irgrid.h
 * @brief This file contains API for IR Grid Click Driver.
 */

#ifndef IRGRID_H
#define IRGRID_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup irgrid IR Grid Click Driver
 * @brief API for configuring and manipulating IR Grid Click driver.
 * @{
 */

/**
 * @defgroup irgrid_reg IR Grid Registers List
 * @brief List of registers of IR Grid Click driver.
 */

/**
 * @addtogroup irgrid_reg
 * @{
 */

/**
 * @brief IR Grid description register.
 * @details Specified register for description of IR Grid Click driver.
 */
#define IRGRID_CAL_ACOMMON_L        0xD0
#define IRGRID_CAL_ACOMMON_H        0xD1
#define IRGRID_CAL_ACP_L            0xD3
#define IRGRID_CAL_ACP_H            0xD4
#define IRGRID_CAL_BCP              0xD5
#define IRGRID_CAL_ALPHA_CP_L       0xD6
#define IRGRID_CAL_ALPHA_CP_H       0xD7
#define IRGRID_CAL_TGC              0xD8
#define IRGRID_CAL_AI_SCALE         0xD9
#define IRGRID_CAL_BI_SCALE         0xD9
#define IRGRID_VTH_L                0xDA
#define IRGRID_VTH_H                0xDB
#define IRGRID_KT1_L                0xDC
#define IRGRID_KT1_H                0xDD
#define IRGRID_KT2_L                0xDE
#define IRGRID_KT2_H                0xDF
#define IRGRID_KT_SCALE             0xD2
#define IRGRID_CAL_A0_L             0xE0
#define IRGRID_CAL_A0_H             0xE1
#define IRGRID_CAL_A0_SCALE         0xE2
#define IRGRID_CAL_DELTA_A_SCALE    0xE3
#define IRGRID_CAL_EMIS_L           0xE4
#define IRGRID_CAL_EMIS_H           0xE5
#define IRGRID_OSC_TRIM_VALUE       0xF7

/*! @} */ // irgrid_reg

/**
 * @defgroup irgrid_set IR Grid Registers Settings
 * @brief Settings for registers of IR Grid Click driver.
 */

/**
 * @defgroup irgrid_map IR Grid MikroBUS Map
 * @brief MikroBUS pin mapping of IR Grid Click driver.
 */

/**
 * @addtogroup irgrid_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Grid Click to the selected MikroBUS.
 */
#define IRGRID_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // irgrid_map
/*! @} */ // irgrid

/**
 * @brief IR Grid Click context object.
 * @details Context object definition of IR Grid Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_ram_address;
    uint8_t slave_eeprom_address;

    // static variable 
    uint8_t refresh_rate;
    float   temperature_amb;
    int16_t resolution;
    int16_t cpix;
    int16_t ptat;

} irgrid_t;

/**
 * @brief IR Grid Click configuration object.
 * @details Configuration object definition of IR Grid Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t i2c_ram_address;    /**< I2C ram address. */
    uint8_t i2c_eeprom_address; /**< I2C eeprom address. */

} irgrid_cfg_t;

/**
 * @brief Click data object definition.
 */
typedef struct
{
    // Static variable 

    uint8_t  eeprom_data[ 256 ];
    int16_t  ir_data[ 64 ];
    float    temperature_data[ 64 ];
    float    a_data[ 64 ];
    float    b_data[ 64 ];
    float    alpha_a_data[ 64 ];

} irgrid_data_t;

/**
 * @brief IR Grid Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRGRID_OK = 0,
    IRGRID_ERROR = -1

} irgrid_return_value_t;

/*!
 * @addtogroup irgrid IR Grid Click Driver
 * @brief API for configuring and manipulating IR Grid Click driver.
 * @{
 */

/**
 * @brief IR Grid configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irgrid_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irgrid_cfg_setup ( irgrid_cfg_t *cfg );

/**
 * @brief IR Grid initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irgrid_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irgrid_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid_init ( irgrid_t *ctx, irgrid_cfg_t *cfg );

/**
 * @brief Device Initialization
 *
 * @param ctx          Click object.
 * @param data_str     Data click object.
 * @param refrate      Refresh Rate
 *
 * @returns 0 - OK
 *
 *  @description Initializes device, reads eeprom memory and places it inside internal buffers.
 */
uint8_t irgrid_device_init ( irgrid_t *ctx, irgrid_data_t *data_str, uint8_t refrate );

/**
 * @brief Write function using RAM slave adress.
 *
 * @param ctx          Data click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void irgrid_write_ram( irgrid_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read function using RAM slave adress.
 *
 * @param ctx          Click object.
 * @param reg          Register address pointer.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void irgrid_read_ram ( irgrid_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write function using EEPROM slave adress.
 *
 * @param ctx          Data click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void irgrid_write_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read function using EEPROM slave adress.
 *
 * @param ctx          Click object.
 * @param reg          Register address pointer.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void irgrid_read_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Measurement
 *
 * @param ctx          Click object.
 * @param data_str     Data click object.
 * @returns 0 - OK
 *
 * @description Measures temperature and places it inside internal buffers. This function is 
 * needed to be called prior to `irgrid_get_ir_raw` or `irgrid_get_temperature`.
 */
uint8_t irgrid_measure ( irgrid_t *ctx, irgrid_data_t *data_str );

/**
 * @brief Read Raw Temperature buffer
 *
 * @param data_str     Data click object.
 * @param buffer       Output data buf.
 *
 * @description Populates provided buffer with raw measurements. Buffer must have at least 64 members.
 */
void irgrid_get_ir_raw ( irgrid_data_t *data_str, int16_t *buffer );

/**
 * @brief Read Calculated Temperature buffer
 *
 * @param data_str     Data click object.
 * @param buffer       Output data buf.
 *
 * @description Populates provided buffer with calculated temperatures. Buffer must have at least 64 members.
 */
void irgrid_get_temperature ( irgrid_data_t *data_str, float *buffer );

/**
 * @brief Read Ambient Temperature
 *
 * @param ctx          Click object.
 *
 * @returns            Ambient temperature.
 *
 * @description Read Ambient temperautre.
 */
float irgrid_get_amb_temperature ( irgrid_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IRGRID_H

/*! @} */ // irgrid

// ------------------------------------------------------------------------ END

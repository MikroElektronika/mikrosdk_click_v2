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
 * @file efuse5.h
 * @brief This file contains API for eFuse 5 Click Driver.
 */

#ifndef EFUSE5_H
#define EFUSE5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup efuse5 eFuse 5 Click Driver
 * @brief API for configuring and manipulating eFuse 5 Click driver.
 * @{
 */

/**
 * @defgroup efuse5_inst eFuse 5 Instruction Byte List
 * @brief List of Instruction Byte of eFuse 5 Click driver.
 */

/**
 * @addtogroup efuse5_inst
 * @{
 */

/**
 * @brief eFuse 5 description Instruction Byte.
 * @details Specified Instruction Byte for description of eFuse 5 Click driver.
 */
#define EFUSE5_WRITE_TO_RDAC          0x00
#define EFUSE5_ONE_TIME_PROG          0x80


/*! @} */ // efuse5_inst

/**
 * @defgroup efuse5_set eFuse 5 Registers Settings
 * @brief Settings for registers of eFuse 5 Click driver.
 */

/**
 * @addtogroup efuse5_set
 * @{
 */

/**
 * @brief eFuse 5 description OTP Validation Bits.
 * @details Specified OTP Validation Bits for description of eFuse 5 Click driver.
 */
#define EFUSE5_OTP_V_READY            0x00
#define EFUSE5_OTP_V_TEST_FUSE_OK     0x40
#define EFUSE5_OTP_V_ERROR            0x80
#define EFUSE5_OTP_V_PROG_SUCCESS     0xC0

/**
 * @brief eFuse 5 device address setting.
 * @details Specified setting for device slave address selection of
 * eFuse 5 Click driver.
 */
#define EFUSE5_DEVICE_ADDRESS         0x2C

/*! @} */ // efuse5_set

/**
 * @defgroup efuse5_map eFuse 5 MikroBUS Map
 * @brief MikroBUS pin mapping of eFuse 5 Click driver.
 */

/**
 * @addtogroup efuse5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of eFuse 5 Click to the selected MikroBUS.
 */
#define EFUSE5_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.mon = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.pgd = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // efuse5_map
/*! @} */ // efuse5

/**
 * @brief eFuse 5 Click context object.
 * @details Context object definition of eFuse 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;    /**< Enable pin. */

    // Input pins
    digital_in_t mon;    /**< Analog current monitor outpu. */
    digital_in_t pgd;    /**< Power good indicator pin. */
    digital_in_t flt;    /**< Fault event indicator pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} efuse5_t;

/**
 * @brief eFuse 5 Click configuration object.
 * @details Configuration object definition of eFuse 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t mon;    /**< Analog current monitor outpu. */
    pin_name_t en;     /**< Enable pin. */
    pin_name_t pgd;    /**< Power good indicator pin. */
    pin_name_t flt;    /**< Fault event indicator pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} efuse5_cfg_t;

/**
 * @brief eFuse 5 Click current limit value data.
 * @details Predefined enum values for driver current limit values.
 */
typedef enum
{
    EFUSE5_CURRENT_LIMIT_600_mA = 600,
    EFUSE5_CURRENT_LIMIT_720_mA = 720,
    EFUSE5_CURRENT_LIMIT_865_mA = 865,
    EFUSE5_CURRENT_LIMIT_900_mA = 900,
    EFUSE5_CURRENT_LIMIT_1030_mA = 1030,
    EFUSE5_CURRENT_LIMIT_1200_mA = 1200,
    EFUSE5_CURRENT_LIMIT_1445_mA = 1445,
    EFUSE5_CURRENT_LIMIT_1550_mA = 1550,
    EFUSE5_CURRENT_LIMIT_2000_mA = 2000,
    EFUSE5_CURRENT_LIMIT_4500_mA = 4500

} efuse5_current_limit_t;

/**
 * @brief eFuse 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EFUSE5_OK = 0,
    EFUSE5_ERROR = -1

} efuse5_return_value_t;

/*!
 * @addtogroup efuse5 eFuse 5 Click Driver
 * @brief API for configuring and manipulating eFuse 5 Click driver.
 * @{
 */

/**
 * @brief eFuse 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse5_cfg_setup ( efuse5_cfg_t *cfg );

/**
 * @brief eFuse 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_init ( efuse5_t *ctx, efuse5_cfg_t *cfg );

/**
 * @brief eFuse 5 default configuration function.
 * @details This function executes a default configuration of eFuse 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t efuse5_default_cfg ( efuse5_t *ctx );

/**
 * @brief eFuse 5 I2C writing function.
 * @details This function writes data bytes with desired instructions 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[in] inst : Instruction Byte.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_write_byte ( efuse5_t *ctx, uint8_t inst, uint8_t data_in );

/**
 * @brief eFuse 5 I2C reading function.
 * @details This function reads data bytes 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_generic_read ( efuse5_t *ctx, uint8_t *data_out );

/**
 * @brief eFuse 5 write RDAC function.
 * @details This function writes 6-bit RDAC values
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[in] rdac_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_write_rdac ( efuse5_t *ctx, uint8_t rdac_data );

/**
 * @brief eFuse 5 read RDAC function.
 * @details This function reads 6-bit RDAC values
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[out] rdac_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_read_rdac ( efuse5_t *ctx, uint8_t *rdac_data );

/**
 * @brief eFuse 5 set the digital potentiometer function.
 * @details This function set the digital potentiometer wiper position 
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position (from 0 to 63).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_set_digi_pot ( efuse5_t *ctx, uint8_t wiper_pos );

/**
 * @brief eFuse 5 set the resistance function.
 * @details This function set the resistance value 
 * of the digital potentiometer wiper position
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance (from 4000 to 30000 Ohm).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_set_resistance ( efuse5_t *ctx, uint16_t res_ohm );

/**
 * @brief eFuse 5 set the current limit function.
 * @details This function set current limit value
 * of the AD5171, 64-Position OTP Digital Potentiometer 
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @param[in] current_limit : Current limit values [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse5_set_current_limit ( efuse5_t *ctx, efuse5_current_limit_t current_limit );

/**
 * @brief eFuse 5 enable the device function.
 * @details This function performs the device 
 * to enter into low-power shutdown mode
 * of the TPS16530 58-V, 4.5-A eFuse With Pulse Current Support for Load Transients
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse5_enable_device ( efuse5_t *ctx );

/**
 * @brief eFuse 5 disable the device function.
 * @details This function resets the device 
 * that has latched off due to a fault condition
 * of theTPS16530 58-V, 4.5-A eFuse With Pulse Current Support for Load Transients
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse5_shutdown ( efuse5_t *ctx );

/**
 * @brief eFuse 5 get imon function.
 * @details This function get the states of the MON pin  
 * of theTPS16530 58-V, 4.5-A eFuse With Pulse Current Support for Load Transients
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @return States of the MON pin.
 * @note None.
 */
uint8_t efuse5_get_imon ( efuse5_t *ctx );

/**
 * @brief eFuse 5 gets power good state function.
 * @details This function get the states of the PGD pin  
 * of theTPS16530 58-V, 4.5-A eFuse With Pulse Current Support for Load Transients
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @return @li @c 0 - Fault condition, internal FET is turned OFF during a fault.
 *         @li @c 1 - Power is good, internal FET is enhanced.
 * @note None.
 */
uint8_t efuse5_get_pgood ( efuse5_t *ctx );

/**
 * @brief eFuse 5 gets fault condition state function.
 * @details This function get the states of the FLT pin  
 * of theTPS16530 58-V, 4.5-A eFuse With Pulse Current Support for Load Transients
 * on the eFuse 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse5_t object definition for detailed explanation.
 * @return @li @c 0 - Fault condition.
 *         @li @c 1 - No fault.
 * @note None.
 */
uint8_t efuse5_get_fault ( efuse5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EFUSE5_H

/*! @} */ // efuse5

// ------------------------------------------------------------------------ END

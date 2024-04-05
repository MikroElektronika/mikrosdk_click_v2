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
 * @file efuse4.h
 * @brief This file contains API for eFuse 4 Click Driver.
 */

#ifndef EFUSE4_H
#define EFUSE4_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup efuse4 eFuse 4 Click Driver
 * @brief API for configuring and manipulating eFuse 4 Click driver.
 * @{
 */

/**
 * @defgroup efuse4_com eFuse 4 Commands List
 * @brief List of registers of eFuse 4 Click driver.
 */

/**
 * @addtogroup efuse4_com
 * @{
 */

/**
 * @brief eFuse 4 description command.
 * @details Specified command for description of eFuse 4 Click driver.
 */
#define EFUSE4_CMD_NOP                        0x00
#define EFUSE4_CMD_WRITE_RDAC                 0x04
#define EFUSE4_CMD_READ_RDAC                  0x08
#define EFUSE4_CMD_STORE_WIPER                0x0C
#define EFUSE4_CMD_SW_RESET                   0x10
#define EFUSE4_CMD_READ_CONTENTS              0x14
#define EFUSE4_CMD_READ_MEMORY                0x18
#define EFUSE4_CMD_WRITE_MEMORY               0x1C
#define EFUSE4_CMD_READ_CTRL                  0x20
#define EFUSE4_CMD_SW_SHUTDOWN                0x24

/*! @} */ // efuse4_com

/**
 * @defgroup efuse4_set eFuse 4 Registers Settings
 * @brief Settings for registers of eFuse 4 Click driver.
 */

/**
 * @addtogroup efuse4_set
 * @{
 */

/**
 * @brief eFuse 4 description setting.
 * @details Specified setting for description of eFuse 4 Click driver.
 */
#define EFUSE4_SET_SHUTDOWN_BIT_MASK          0x01
#define EFUSE4_SET_NORMAL_MODE                0x00
#define EFUSE4_SET_SHUTDOWN_MODE              0x01
#define EFUSE4_SET_ENABLE_WRITE_MEMORY        0x0002

/**
 * @brief eFuse 4 device address setting.
 * @details Specified setting for device slave address selection of
 * eFuse 4 Click driver.
 */
#define EFUSE4_DEVICE_ADDRESS                  0x2F

/*! @} */ // efuse4_set

/**
 * @defgroup efuse4_map eFuse 4 MikroBUS Map
 * @brief MikroBUS pin mapping of eFuse 4 Click driver.
 */

/**
 * @addtogroup efuse4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of eFuse 4 Click to the selected MikroBUS.
 */
#define EFUSE4_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pgd = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dsv = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // efuse4_map
/*! @} */ // efuse4

/**
 * @brief eFuse 4 Click context object.
 * @details Context object definition of eFuse 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;        /**< Enable pin. */
    digital_out_t dsv;        /**< DevSleep Mode control pin. */

    // Input pins
    digital_in_t pgd;         /**< Power good indicator pin. */
    digital_in_t flt;         /**< Fault event indicator pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} efuse4_t;

/**
 * @brief eFuse 4 Click configuration object.
 * @details Configuration object definition of eFuse 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pgd;             /**< Power good indicator pin. */
    pin_name_t rst;             /**< Enable pin. */
    pin_name_t dsv;             /**< DevSleep Mode control pin. */
    pin_name_t flt;             /**< Fault event indicator pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} efuse4_cfg_t;

/**
 * @brief eFuse 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EFUSE4_OK = 0,
    EFUSE4_ERROR = -1

} efuse4_return_value_t;

/**
 * @brief eFuse 4 Click current limit value data.
 * @details Predefined enum values for driver current limit values.
 */
typedef enum
{
    EFUSE4_CURRENT_LIMIT_670_mA = 670,
    EFUSE4_CURRENT_LIMIT_750_mA = 750,
    EFUSE4_CURRENT_LIMIT_990_mA = 990,
    EFUSE4_CURRENT_LIMIT_2080_mA = 2080,
    EFUSE4_CURRENT_LIMIT_3530_mA = 3530,
    EFUSE4_CURRENT_LIMIT_4450_mA = 4450,
    EFUSE4_CURRENT_LIMIT_5200_mA = 5200

} efuse4_current_limit_t;

/*!
 * @addtogroup efuse4 eFuse 4 Click Driver
 * @brief API for configuring and manipulating eFuse 4 Click driver.
 * @{
 */

/**
 * @brief eFuse 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse4_cfg_setup ( efuse4_cfg_t *cfg );

/**
 * @brief eFuse 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_init ( efuse4_t *ctx, efuse4_cfg_t *cfg );

/**
 * @brief eFuse 4 default configuration function.
 * @details This function executes a default configuration:
 * enables a programmable under-voltage lockout threshold,
 * set normal mode, performs the software reset,
 * sets normal operation mode of the digital potentiometer,
 * performs command to enable the write and set the current limit to 750 mA
 * of eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t efuse4_default_cfg ( efuse4_t *ctx );

/**
 * @brief eFuse 4 I2C writing function.
 * @details This function writes a 10-bit data value 
 * for the desired command operation by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_generic_write ( efuse4_t *ctx, uint8_t cmd, uint16_t data_in );

/**
 * @brief eFuse 4 I2C reading function.
 * @details This function reads a 10-bit data value 
 * for the desired command operation by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_generic_read ( efuse4_t *ctx, uint8_t cmd, uint16_t data_in, uint16_t *data_out );

/**
 * @brief eFuse 4 enable function.
 * @details This function enables a programmable under-voltage lockout threshold
 * of the TPS25940x 2.7 – 18V eFuse with True Reverse Blocking and DevSleep Support for SSDs
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse4_set_enable ( efuse4_t *ctx );

/**
 * @brief eFuse 4 disable function.
 * @details This function disables a programmable under-voltage lockout threshold
 * of the TPS25940x 2.7 – 18V eFuse with True Reverse Blocking and DevSleep Support for SSDs
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse4_set_disable ( efuse4_t *ctx );

/**
 * @brief eFuse 4 set low power mode function.
 * @details This function activates the DevSleep mode (Low Power Mode)
 * of the TPS25940x 2.7 – 18V eFuse with True Reverse Blocking and DevSleep Support for SSDs
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse4_set_low_power_mode ( efuse4_t *ctx );

/**
 * @brief eFuse 4 set normal mode function.
 * @details This function deactivates the DevSleep mode (Normal Power Mode)
 * of the TPS25940x 2.7 – 18V eFuse with True Reverse Blocking and DevSleep Support for SSDs
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse4_set_normal_mode ( efuse4_t *ctx );

/**
 * @brief eFuse 4 software reset function.
 * @details This function performs the software reset 
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_sw_reset ( efuse4_t *ctx );

/**
 * @brief eFuse 4 enable write function.
 * @details This function performs command to enable the write 
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_enable_write ( efuse4_t *ctx );

/**
 * @brief eFuse 4 write RDAC function.
 * @details This function writes 10-bit RDAC values
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_write_rdac ( efuse4_t *ctx, uint16_t data_in );

/**
 * @brief eFuse 4 read RDAC function.
 * @details This function reads 10-bit RDAC values
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_read_rdac ( efuse4_t *ctx, uint16_t *data_out );

/**
 * @brief eFuse 4 set digital potentiometer operation mode function.
 * @details This function sets the digital potentiometer operation mode
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] mode : Operating mode: Shutdown or Normal mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_digi_pot_op_mode ( efuse4_t *ctx, uint8_t mode );

/**
 * @brief eFuse 4 store wiper function.
 * @details This function store wiper setting, store RDAC setting
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_store_wiper_pos ( efuse4_t *ctx );

/**
 * @brief eFuse 4 next frame read function.
 * @details This function read contents of 50-TP output in the next frame
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] wiper_location : Wiper location (from 0x00 to the 0x38).
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_next_frame_read ( efuse4_t *ctx, uint8_t wiper_location, uint16_t *data_out );

/**
 * @brief eFuse 4 read memory function.
 * @details This function read address of the last 50-TP programmed memory location
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_read_memory ( efuse4_t *ctx, uint16_t *data_out );

/**
 * @brief eFuse 4 set digital potentiometer function.
 * @details This function set the digital potentiometer wiper position 
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] wiper_pos : Wiper position (from 0 to 1023).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_set_digi_pot ( efuse4_t *ctx, uint16_t wiper_pos );

/**
 * @brief eFuse 4 set resistance function.
 * @details This function set the resistance of the digital potentiometer wiper position 
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] res_ohm : Resistance [ Ohm ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_set_resistance ( efuse4_t *ctx, uint32_t res_ohm );

/**
 * @brief eFuse 4 set current limit function.
 * @details This function set current limit 
 * of the AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] current_limit : Current limit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse4_set_current_limit ( efuse4_t *ctx, efuse4_current_limit_t current_limit );

/**
 * @brief eFuse 4 get fault state function.
 * @details This function get fault event indicator state
 * of the TPS25940x 2.7 – 18V eFuse with True Reverse Blocking and DevSleep Support for SSDs
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return @li @c 0 - Fault condition due to Undervoltage, Overvoltage, Reverse voltage and Thermal shutdown event,
 *         @li @c 1 - Normal condition.
 * @note None.
 */
uint8_t efuse4_fault_state ( efuse4_t *ctx );

/**
 * @brief eFuse 4 get power good state function.
 * @details This function get power good state
 * of the TPS25940x 2.7 – 18V eFuse with True Reverse Blocking and DevSleep Support for SSDs
 * on the eFuse 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #efuse4_t object definition for detailed explanation.
 * @return @li @c 0 - Normal condition,
 *         @li @c 1 - Positive input of power good comparator has crossed the threshold value.
 * @note None.
 */
uint8_t efuse4_pwr_good_state ( efuse4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EFUSE4_H

/*! @} */ // efuse4

// ------------------------------------------------------------------------ END

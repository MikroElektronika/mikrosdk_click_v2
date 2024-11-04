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
 * @file captouch4.h
 * @brief This file contains API for Cap Touch 4 Click Driver.
 */

#ifndef CAPTOUCH4_H
#define CAPTOUCH4_H

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
 * @addtogroup captouch4 Cap Touch 4 Click Driver
 * @brief API for configuring and manipulating Cap Touch 4 Click driver.
 * @{
 */

/**
 * @defgroup captouch4_reg Cap Touch 4 Registers List
 * @brief List of registers of Cap Touch 4 Click driver.
 */

/**
 * @addtogroup captouch4_reg
 * @{
 */

/**
 * @brief Cap Touch 4 register list.
 * @details Specified register list of Cap Touch 4 Click driver.
 */
#define CAPTOUCH4_REG_PRODUCT_NUM               0x00
#define CAPTOUCH4_REG_VERSION_NUM               0x01
#define CAPTOUCH4_REG_SYSFLAGS0                 0x10
#define CAPTOUCH4_REG_MOVEMENT_VALUE            0x41
#define CAPTOUCH4_REG_CS_H                      0x42
#define CAPTOUCH4_REG_CS_L                      0x43
#define CAPTOUCH4_REG_LTA_H                     0x83
#define CAPTOUCH4_REG_LTA_L                     0x84
#define CAPTOUCH4_REG_TOUCH_THRESHOLD_H         0x90
#define CAPTOUCH4_REG_TOUCH_THRESHOLD_L         0x91
#define CAPTOUCH4_REG_MULTIPLIERS               0xC4
#define CAPTOUCH4_REG_COMPENSATION              0xC5
#define CAPTOUCH4_REG_PROX_SETTINGS0            0xC6
#define CAPTOUCH4_REG_PROX_SETTINGS1            0xC7
#define CAPTOUCH4_REG_PROX_SETTINGS2            0xC8
#define CAPTOUCH4_REG_ATI_TARGET                0xC9
#define CAPTOUCH4_REG_LP_PERIOD                 0xCA
#define CAPTOUCH4_REG_PROX_THRESHOLD            0xCB
#define CAPTOUCH4_REG_TOUCH_THRESHOLD           0xCC
#define CAPTOUCH4_REG_MOVEMENT_THRESHOLD        0xCD
#define CAPTOUCH4_REG_AUTO_RESEED_LIMIT         0xCE
#define CAPTOUCH4_REG_TEST_MODE                 0x0F
#define CAPTOUCH4_REG_OTP_BANK_0                0x10
#define CAPTOUCH4_REG_OTP_BANK_1                0x11
#define CAPTOUCH4_REG_OTP_BANK_2                0x12
#define CAPTOUCH4_REG_OTP_BANK_3                0x13
#define CAPTOUCH4_REG_OTP_BANK_4                0x14

/*! @} */ // captouch4_reg

/**
 * @defgroup captouch4_set Cap Touch 4 Registers Settings
 * @brief Settings for registers of Cap Touch 4 Click driver.
 */

/**
 * @addtogroup captouch4_set
 * @{
 */

/**
 * @brief Cap Touch 4 OTP test mode setting.
 * @details Specified setting for OTP test mode of Cap Touch 4 Click driver.
 */
#define CAPTOUCH4_TEST_MODE_OK                  0xA5
#define CAPTOUCH4_OTP_BANK_2_OUT_I2C_NO_WKP     0x05

/**
 * @brief Cap Touch 4 SYSFLAGS0 register setting.
 * @details Specified setting for SYSFLAGS0 register of Cap Touch 4 Click driver.
 */
#define CAPTOUCH4_SYSFLAGS0_MOVEMENT            0x80
#define CAPTOUCH4_SYSFLAGS0_MOVEMENT_LATCH      0x40
#define CAPTOUCH4_SYSFLAGS0_PROX                0x20
#define CAPTOUCH4_SYSFLAGS0_TOUCH               0x10
#define CAPTOUCH4_SYSFLAGS0_SHOW_RESET          0x08
#define CAPTOUCH4_SYSFLAGS0_ATI_BUSY            0x04
#define CAPTOUCH4_SYSFLAGS0_FILTER_HALT         0x02
#define CAPTOUCH4_SYSFLAGS0_LP_ACTIVE           0x01
#define CAPTOUCH4_SYSFLAGS0_CLEAR               0x01

/**
 * @brief Cap Touch 4 device ID setting.
 * @details Specified setting for device ID of Cap Touch 4 Click driver.
 */
#define CAPTOUCH4_PRODUCT_NUMBER                0x3D
#define CAPTOUCH4_VERSION_NUMBER                0x02

/**
 * @brief Cap Touch 4 I2C timeout setting.
 * @details Specified setting for I2C timeout of Cap Touch 4 Click driver.
 */
#define CAPTOUCH4_I2C_TIMEOUT                   100000ul

/**
 * @brief Cap Touch 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Cap Touch 4 Click driver.
 */
#define CAPTOUCH4_DEVICE_ADDRESS                0x47

/*! @} */ // captouch4_set

/**
 * @defgroup captouch4_map Cap Touch 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Cap Touch 4 Click driver.
 */

/**
 * @addtogroup captouch4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Cap Touch 4 Click to the selected MikroBUS.
 */
#define CAPTOUCH4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // captouch4_map
/*! @} */ // captouch4

/**
 * @brief Cap Touch 4 Click context object.
 * @details Context object definition of Cap Touch 4 Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Enable pin (active high). */
    
    // Modules
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint8_t i2c_started;        /**< I2C started flag. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} captouch4_t;

/**
 * @brief Cap Touch 4 Click configuration object.
 * @details Configuration object definition of Cap Touch 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t en;              /**< Enable pin (active high). */

    uint8_t    i2c_address;     /**< I2C slave address. */

} captouch4_cfg_t;

/**
 * @brief Cap Touch 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CAPTOUCH4_OK = 0,
    CAPTOUCH4_ERROR = -1

} captouch4_return_value_t;

/*!
 * @addtogroup captouch4 Cap Touch 4 Click Driver
 * @brief API for configuring and manipulating Cap Touch 4 Click driver.
 * @{
 */

/**
 * @brief Cap Touch 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #captouch4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void captouch4_cfg_setup ( captouch4_cfg_t *cfg );

/**
 * @brief Cap Touch 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #captouch4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_init ( captouch4_t *ctx, captouch4_cfg_t *cfg );

/**
 * @brief Cap Touch 4 default configuration function.
 * @details This function executes a default configuration of Cap Touch 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t captouch4_default_cfg ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_write_reg ( captouch4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Cap Touch 4 read reg function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_read_reg ( captouch4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Cap Touch 4 check communication function.
 * @details This function checks the communication by reading and verifying the device
 * product and version numbers.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_check_communication ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void captouch4_enable_device ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void captouch4_disable_device ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 read system flags function.
 * @details This function reads the system flags register.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[out] sysflags : System flags.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_read_system_flags ( captouch4_t *ctx, uint8_t *sysflags );

/**
 * @brief Cap Touch 4 read movement function.
 * @details This function reads an average of movement pulses over a time period.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[out] movement : 8-bit movement value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_read_movement ( captouch4_t *ctx, uint8_t *movement );

/**
 * @brief Cap Touch 4 read cap counts function.
 * @details This function reads the counts number directly proportional to capacitance.
 * The system is calibrated to make the counts as sensitive as possible to changes in
 * capacitance for relative measurements.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[out] cap_counts : 16-bit capacitance counts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_read_cap_counts ( captouch4_t *ctx, uint16_t *cap_counts );

/**
 * @brief Cap Touch 4 read lta function.
 * @details This function reads the long-term averate (LTA) value.
 * The LTA is used as reference to compare with capacitance counts.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[out] lta : 16-bit long term average value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch4_read_lta ( captouch4_t *ctx, uint16_t *lta );

#ifdef __cplusplus
}
#endif
#endif // CAPTOUCH4_H

/*! @} */ // captouch4

// ------------------------------------------------------------------------ END

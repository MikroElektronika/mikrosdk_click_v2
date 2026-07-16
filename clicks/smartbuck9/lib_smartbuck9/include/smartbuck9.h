/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file smartbuck9.h
 * @brief This file contains API for Smart Buck 9 Click Driver.
 */

#ifndef SMARTBUCK9_H
#define SMARTBUCK9_H

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
 * @addtogroup smartbuck9 Smart Buck 9 Click Driver
 * @brief API for configuring and manipulating Smart Buck 9 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck9_reg Smart Buck 9 Registers List
 * @brief List of registers of Smart Buck 9 Click driver.
 */

/**
 * @addtogroup smartbuck9_reg
 * @{
 */

/**
 * @brief Smart Buck 9 register map.
 * @details Specified register map of Smart Buck 9 Click driver.
 */
#define SMARTBUCK9_REG_DEVICE_ID            0x00
#define SMARTBUCK9_REG_STATUS               0x01
#define SMARTBUCK9_REG_CONFIG               0x02
#define SMARTBUCK9_REG_VOUT                 0x03

/*! @} */ // smartbuck9_reg

/**
 * @defgroup smartbuck9_set Smart Buck 9 Registers Settings
 * @brief Settings for registers of Smart Buck 9 Click driver.
 */

/**
 * @addtogroup smartbuck9_set
 * @{
 */

/**
 * @brief Smart Buck 9 DEVICE_ID register setting.
 * @details Specified setting for DEVICE_ID register of Smart Buck 9 Click driver.
 */
#define SMARTBUCK9_DEVICE_ID_VERSION_A      0x00
#define SMARTBUCK9_DEVICE_ID_VERSION_MASK   0x78
#define SMARTBUCK9_DEVICE_ID_CHIP_REV_MASK  0x07

/**
 * @brief Smart Buck 9 STATUS register setting.
 * @details Specified setting for STATUS register of Smart Buck 9 Click driver.
 */
#define SMARTBUCK9_STATUS_TSHDN             0x08
#define SMARTBUCK9_STATUS_VI_OVP            0x04
#define SMARTBUCK9_STATUS_VO_OVP            0x02
#define SMARTBUCK9_STATUS_OCP               0x01

/**
 * @brief Smart Buck 9 CONFIG register setting.
 * @details Specified setting for CONFIG register of Smart Buck 9 Click driver.
 */
#define SMARTBUCK9_CONFIG_EN_BUCK_DIS       0x00
#define SMARTBUCK9_CONFIG_EN_BUCK_EN        0x80
#define SMARTBUCK9_CONFIG_EN_MASK           0x80
#define SMARTBUCK9_CONFIG_AD_DIS            0x00
#define SMARTBUCK9_CONFIG_AD_EN             0x40
#define SMARTBUCK9_CONFIG_AD_MASK           0x40
#define SMARTBUCK9_CONFIG_FREQ_1MHZ         0x00
#define SMARTBUCK9_CONFIG_FREQ_1M5HZ        0x10
#define SMARTBUCK9_CONFIG_FREQ_2MHZ         0x20
#define SMARTBUCK9_CONFIG_FREQ_2M5HZ        0x30
#define SMARTBUCK9_CONFIG_FREQ_MASK         0x30
#define SMARTBUCK9_CONFIG_OCP_1A            0x00
#define SMARTBUCK9_CONFIG_OCP_2A            0x04
#define SMARTBUCK9_CONFIG_OCP_3A            0x08
#define SMARTBUCK9_CONFIG_OCP_4A            0x0C
#define SMARTBUCK9_CONFIG_OCP_MASK          0x0C
#define SMARTBUCK9_CONFIG_PWM_PFM           0x00
#define SMARTBUCK9_CONFIG_PWM_FORCED        0x01
#define SMARTBUCK9_CONFIG_PWM_MASK          0x01

/**
 * @brief Smart Buck 9 VOUT register setting.
 * @details Specified setting for VOUT register of Smart Buck 9 Click driver.
 */
#define SMARTBUCK9_VOUT_MIN_MV              300
#define SMARTBUCK9_VOUT_MAX_MV              3600
#define SMARTBUCK9_VOUT_DEFAULT_MV          2500
#define SMARTBUCK9_VOUT_STEP_MV             20
#define SMARTBUCK9_VOUT_CODE_MIN            0x00
#define SMARTBUCK9_VOUT_CODE_MAX            0xA5

/**
 * @brief Smart Buck 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 9 Click driver.
 */
#define SMARTBUCK9_DEVICE_ADDRESS           0x50

/*! @} */ // smartbuck9_set

/**
 * @defgroup smartbuck9_map Smart Buck 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 9 Click driver.
 */

/**
 * @addtogroup smartbuck9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 9 Click to the selected MikroBUS.
 */
#define SMARTBUCK9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartbuck9_map
/*! @} */ // smartbuck9

/**
 * @brief Smart Buck 9 Click context object.
 * @details Context object definition of Smart Buck 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable device pin (active high). */

    // Input pins
    digital_in_t pg;            /**< Power good pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} smartbuck9_t;

/**
 * @brief Smart Buck 9 Click configuration object.
 * @details Configuration object definition of Smart Buck 9 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Description. */
    pin_name_t pg;              /**< Description. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck9_cfg_t;

/**
 * @brief Smart Buck 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK9_OK = 0,
    SMARTBUCK9_ERROR = -1

} smartbuck9_return_value_t;

/*!
 * @addtogroup smartbuck9 Smart Buck 9 Click Driver
 * @brief API for configuring and manipulating Smart Buck 9 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck9_cfg_setup ( smartbuck9_cfg_t *cfg );

/**
 * @brief Smart Buck 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck9_init ( smartbuck9_t *ctx, smartbuck9_cfg_t *cfg );

/**
 * @brief Smart Buck 9 default configuration function.
 * @details This function executes a default configuration of Smart Buck 9
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck9_default_cfg ( smartbuck9_t *ctx );

/**
 * @brief Smart Buck 9 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck9_write_reg ( smartbuck9_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Smart Buck 9 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck9_read_reg ( smartbuck9_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Smart Buck 9 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck9_enable_device ( smartbuck9_t *ctx );

/**
 * @brief Smart Buck 9 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck9_disable_device ( smartbuck9_t *ctx );

/**
 * @brief Smart Buck 9 get PG pin function.
 * @details This function returns the PG pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartbuck9_get_pg_pin ( smartbuck9_t *ctx );

/**
 * @brief Smart Buck 9 check com function.
 * @details This function check communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck9_check_com ( smartbuck9_t *ctx );

/**
 * @brief Smart Buck 9 set VOUT function.
 * @details This function sets the VOUT output voltage.
 * @param[in] ctx : Click context object.
 * See #smartbuck9_t object definition for detailed explanation.
 * @param[in] voltage_mv : Output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck9_set_vout ( smartbuck9_t *ctx, uint16_t voltage_mv );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK9_H

/*! @} */ // smartbuck9

// ------------------------------------------------------------------------ END

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
 * @file battboost3.h
 * @brief This file contains API for BATT Boost 3 Click Driver.
 */

#ifndef BATTBOOST3_H
#define BATTBOOST3_H

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
 * @addtogroup battboost3 BATT Boost 3 Click Driver
 * @brief API for configuring and manipulating BATT Boost 3 Click driver.
 * @{
 */

/**
 * @defgroup battboost3_reg BATT Boost 3 Registers List
 * @brief List of registers of BATT Boost 3 Click driver.
 */

/**
 * @addtogroup battboost3_reg
 * @{
 */

/**
 * @brief BATT Boost 3 register list.
 * @details Specified register list of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_REG_DEVICE_ID                 0x00
#define BATTBOOST3_REG_CONFIG                    0x01
#define BATTBOOST3_REG_VOUT_FLOOR_SET            0x02
#define BATTBOOST3_REG_ILIM_BST_SET              0x03
#define BATTBOOST3_REG_VOUT_ROOF_SET             0x04
#define BATTBOOST3_REG_STATUS                    0x05
#define BATTBOOST3_REG_ILIM_PT_SET               0x06
#define BATTBOOST3_REG_BST_LOOP                  0x07

/*! @} */ // battboost3_reg

/**
 * @defgroup battboost3_set BATT Boost 3 Registers Settings
 * @brief Settings for registers of BATT Boost 3 Click driver.
 */

/**
 * @addtogroup battboost3_set
 * @{
 */

/**
 * @brief BATT Boost 3 DeviceID register setting.
 * @details Specified setting for DeviceID register of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_DEVICE_ID_MFR_MASK            0xF0
#define BATTBOOST3_DEVICE_ID_MFR_VAL             0x70

/**
 * @brief BATT Boost 3 CONFIG register setting.
 * @details Specified setting for CONFIG register of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_CONFIG_RESET                  0x80
#define BATTBOOST3_CONFIG_ENABLE_MASK            0x60
#define BATTBOOST3_CONFIG_HICCUP_MODE            0x10
#define BATTBOOST3_CONFIG_DISCHG                 0x08
#define BATTBOOST3_CONFIG_SSFM                   0x04
#define BATTBOOST3_CONFIG_MODE_CTRL_MASK         0x03
#define BATTBOOST3_ENABLE_MODE_AUTO              0x20
#define BATTBOOST3_ENABLE_MODE_FORCED_BYPASS     0x40
#define BATTBOOST3_ENABLE_MODE_I2C_SHUTDOWN      0x60
#define BATTBOOST3_MODE_AUTO_PFM                 0x00
#define BATTBOOST3_MODE_ULTRASONIC               0x01
#define BATTBOOST3_MODE_FORCED_PWM               0x02
#define BATTBOOST3_MODE_FORCED_PWM_ALT           0x03

/**
 * @brief BATT Boost 3 STATUS register setting.
 * @details Specified setting for STATUS register of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_STATUS_TSD                    0x80
#define BATTBOOST3_STATUS_CRC_PASS               0x40
#define BATTBOOST3_STATUS_VOUT_START             0x20
#define BATTBOOST3_STATUS_OPMODE                 0x10
#define BATTBOOST3_STATUS_ILIMPT                 0x08
#define BATTBOOST3_STATUS_ILIMBST                0x04
#define BATTBOOST3_STATUS_FL_LD                  0x02
#define BATTBOOST3_STATUS_PGOOD                  0x01

/**
 * @brief BATT Boost 3 boost current limit setting.
 * @details Specified setting for boost current limit of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_BOOST_ILIM_5A                 0x00
#define BATTBOOST3_BOOST_ILIM_5A5                0x01
#define BATTBOOST3_BOOST_ILIM_6A                 0x02
#define BATTBOOST3_BOOST_ILIM_6A5                0x03
#define BATTBOOST3_BOOST_ILIM_7A                 0x04
#define BATTBOOST3_BOOST_ILIM_7A5                0x05
#define BATTBOOST3_BOOST_ILIM_8A                 0x06
#define BATTBOOST3_BOOST_ILIM_3A5                0x0D
#define BATTBOOST3_BOOST_ILIM_4A                 0x0E
#define BATTBOOST3_BOOST_ILIM_4A5                0x0F
#define BATTBOOST3_BOOST_ILIM_MASK               0x0F

/**
 * @brief BATT Boost 3 bypass current limit setting.
 * @details Specified setting for bypass current limit of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_BYPASS_ILIM_16A               0x00
#define BATTBOOST3_BYPASS_ILIM_6A                0x01
#define BATTBOOST3_BYPASS_ILIM_8A                0x02
#define BATTBOOST3_BYPASS_ILIM_10A               0x03
#define BATTBOOST3_BYPASS_ILIM_12A               0x04
#define BATTBOOST3_BYPASS_ILIM_14A               0x05
#define BATTBOOST3_BYPASS_ILIM_4A                0x06
#define BATTBOOST3_BYPASS_ILIM_18A               0x07

#define BATTBOOST3_ILIM_FPT_MASK                 0x38
#define BATTBOOST3_ILIM_APT_MASK                 0x07

/**
 * @brief BATT Boost 3 output voltage limits setting.
 * @details Specified setting for output voltage limits of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_VOUT_MIN                      2.35f
#define BATTBOOST3_VOUT_MAX                      5.00f

/**
 * @brief BATT Boost 3 output voltage calculation values.
 * @details Specified setting for output voltage calculation of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_VOUT_STEP                     0.05f
#define BATTBOOST3_VOUT_LOW_MAX                  2.80f
#define BATTBOOST3_VOUT_NORMAL_BASE              2.85f
#define BATTBOOST3_VOUT_ROUND_OFFSET             0.5f
#define BATTBOOST3_VOUT_CODE_MAX                 0x3F

/**
 * @brief BATT Boost 3 EN pin states setting.
 * @details Specified setting for 3 EN pin states of BATT Boost 3 Click driver.
 */
#define BATTBOOST3_DISABLE                       0
#define BATTBOOST3_ENABLE                        1

/**
 * @brief BATT Boost 3 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT Boost 3 Click driver.
 */
#define BATTBOOST3_DEVICE_ADDRESS_0              0x75
#define BATTBOOST3_DEVICE_ADDRESS_1              0x76
#define BATTBOOST3_DEVICE_ADDRESS_2              0x77
#define BATTBOOST3_DEVICE_ADDRESS                BATTBOOST3_DEVICE_ADDRESS_0

/*! @} */ // battboost3_set

/**
 * @defgroup battboost3_map BATT Boost 3 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT Boost 3 Click driver.
 */

/**
 * @addtogroup battboost3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT Boost 3 Click to the selected MikroBUS.
 */
#define BATTBOOST3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // battboost3_map
/*! @} */ // battboost3

/**
 * @brief BATT Boost 3 Click context object.
 * @details Context object definition of BATT Boost 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;                           /**< Enable pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} battboost3_t;

/**
 * @brief BATT Boost 3 Click configuration object.
 * @details Configuration object definition of BATT Boost 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;                              /**< Enable pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} battboost3_cfg_t;

/**
 * @brief BATT Boost 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTBOOST3_OK = 0,
    BATTBOOST3_ERROR = -1

} battboost3_return_value_t;

/*!
 * @addtogroup battboost3 BATT Boost 3 Click Driver
 * @brief API for configuring and manipulating BATT Boost 3 Click driver.
 * @{
 */

/**
 * @brief BATT Boost 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battboost3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battboost3_cfg_setup ( battboost3_cfg_t *cfg );

/**
 * @brief BATT Boost 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battboost3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_init ( battboost3_t *ctx, battboost3_cfg_t *cfg );

/**
 * @brief BATT Boost 3 default configuration function.
 * @details This function executes a default configuration of BATT Boost 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t battboost3_default_cfg ( battboost3_t *ctx );

/**
 * @brief BATT Boost 3 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_write_reg ( battboost3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief BATT Boost 3 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_write_regs ( battboost3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief BATT Boost 3 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_read_reg ( battboost3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief BATT Boost 3 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_read_regs ( battboost3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief BATT Boost 3 check communication function.
 * @details This function checks the device manufacturer ID.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_check_communication ( battboost3_t *ctx );

/**
 * @brief BATT Boost 3 get device ID function.
 * @details This function reads the DeviceID register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[out] device_id : Device ID register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_get_device_id ( battboost3_t *ctx, uint8_t *device_id );

/**
 * @brief BATT Boost 3 get status function.
 * @details This function reads the STATUS register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[out] status : Status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_get_status ( battboost3_t *ctx, uint8_t *status );

/**
 * @brief BATT Boost 3 set enable mode function.
 * @details This function sets the device enable mode via CONFIG register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] enable_mode : Enable mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_set_enable_mode ( battboost3_t *ctx, uint8_t enable_mode );

/**
 * @brief BATT Boost 3 set operation mode function.
 * @details This function sets Auto PFM, Ultrasonic, or Forced PWM mode via CONFIG register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] mode : Operation mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_set_operation_mode ( battboost3_t *ctx, uint8_t mode );

/**
 * @brief BATT Boost 3 set output voltage function.
 * @details This function sets the VOUT floor threshold from 2.35V to 5.00V.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] vout : Output voltage threshold.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_set_output_voltage ( battboost3_t *ctx, float vout );

/**
 * @brief BATT Boost 3 set boost current limit function.
 * @details This function sets the boost mode average input current limit.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] ilim : Boost current limit setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_set_boost_ilim ( battboost3_t *ctx, uint8_t ilim );

/**
 * @brief BATT Boost 3 set bypass current limit function.
 * @details This function sets automatic and forced bypass current limits.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] apt_ilim : Automatic true bypass current limit setting.
 * @param[in] fpt_ilim : Forced true bypass current limit setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_set_bypass_ilim ( battboost3_t *ctx, uint8_t apt_ilim, uint8_t fpt_ilim );

/**
 * @brief BATT Boost 3 soft reset function.
 * @details This function performs a soft reset via CONFIG register.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost3_soft_reset ( battboost3_t *ctx );

/**
 * @brief BATT Boost 3 sets EN pin state function.
 * @details This function sets the logic state of the EN pin.
 * @param[in] ctx : Click context object.
 * See #battboost3_t object definition for detailed explanation.
 * @param[in] state : EN pin logic state.
 * @return Nothing.
 * @note None.
 */
void battboost3_set_en_pin ( battboost3_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // BATTBOOST3_H

/*! @} */ // battboost3

// ------------------------------------------------------------------------ END

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
 * @file pmic2.h
 * @brief This file contains API for PMIC 2 Click Driver.
 */

#ifndef PMIC2_H
#define PMIC2_H

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
 * @addtogroup pmic2 PMIC 2 Click Driver
 * @brief API for configuring and manipulating PMIC 2 Click driver.
 * @{
 */

/**
 * @defgroup pmic2_reg PMIC 2 Registers List
 * @brief List of registers of PMIC 2 Click driver.
 */

/**
 * @addtogroup pmic2_reg
 * @{
 */

/**
 * @brief PMIC 2 register map.
 * @details Specified register map of PMIC 2 Click driver.
 */
#define PMIC2_REG_LVD_OVP                       0x00
#define PMIC2_REG_LDO_IUSB                      0x01
#define PMIC2_REG_FREQUENCY_RANGE               0x03
#define PMIC2_REG_BOOSTING_FACTOR_RANGE         0x04
#define PMIC2_REG_MPPT_INTERVAL                 0x05
#define PMIC2_REG_CHIP_ID                       0x07
#define PMIC2_REG_FLAGS                         0x08
#define PMIC2_REG_I_RANGE                       0x09
#define PMIC2_REG_I_MEASURED                    0x0A

/*! @} */ // pmic2_reg

/**
 * @defgroup pmic2_set PMIC 2 Registers Settings
 * @brief Settings for registers of PMIC 2 Click driver.
 */

/**
 * @addtogroup pmic2_set
 * @{
 */

/**
 * @brief PMIC 2 LVD_OVP register setting.
 * @details Specified setting for LVD_OVP register of PMIC 2 Click driver.
 */
#define PMIC2_LVD_OVP_LVD_2_2V                  0x00
#define PMIC2_LVD_OVP_LVD_2_3V                  0x10
#define PMIC2_LVD_OVP_LVD_2_4V                  0x20
#define PMIC2_LVD_OVP_LVD_2_5V                  0x30
#define PMIC2_LVD_OVP_LVD_2_6V                  0x40
#define PMIC2_LVD_OVP_LVD_2_7V                  0x50
#define PMIC2_LVD_OVP_LVD_2_8V                  0x60
#define PMIC2_LVD_OVP_LVD_2_9V                  0x70
#define PMIC2_LVD_OVP_LVD_3_0V                  0x80
#define PMIC2_LVD_OVP_LVD_3_1V                  0x90
#define PMIC2_LVD_OVP_LVD_3_2V                  0xA0
#define PMIC2_LVD_OVP_LVD_3_3V                  0xB0
#define PMIC2_LVD_OVP_LVD_3_4V                  0xC0
#define PMIC2_LVD_OVP_LVD_3_5V                  0xD0
#define PMIC2_LVD_OVP_LVD_3_6V                  0xE0
#define PMIC2_LVD_OVP_LVD_3_7V                  0xF0
#define PMIC2_LVD_OVP_LVD_MASK                  0xF0
#define PMIC2_LVD_OVP_OVP_2_7V                  0x00
#define PMIC2_LVD_OVP_OVP_2_9V                  0x01
#define PMIC2_LVD_OVP_OVP_3_1V                  0x02
#define PMIC2_LVD_OVP_OVP_3_3V                  0x03
#define PMIC2_LVD_OVP_OVP_3_4V                  0x04
#define PMIC2_LVD_OVP_OVP_3_5V                  0x05
#define PMIC2_LVD_OVP_OVP_3_6V                  0x06
#define PMIC2_LVD_OVP_OVP_3_7V                  0x07
#define PMIC2_LVD_OVP_OVP_3_8V                  0x08
#define PMIC2_LVD_OVP_OVP_3_9V                  0x09
#define PMIC2_LVD_OVP_OVP_4_0V                  0x0A
#define PMIC2_LVD_OVP_OVP_4_1V                  0x0B
#define PMIC2_LVD_OVP_OVP_4_2V                  0x0C
#define PMIC2_LVD_OVP_OVP_4_3V                  0x0D
#define PMIC2_LVD_OVP_OVP_4_4V                  0x0E
#define PMIC2_LVD_OVP_OVP_4_5V                  0x0F
#define PMIC2_LVD_OVP_OVP_MASK                  0x0F

/**
 * @brief PMIC 2 LDO_IUSB register setting.
 * @details Specified setting for LDO_IUSB register of PMIC 2 Click driver.
 */
#define PMIC2_LDO_IUSB_LDO_BP_NORMAL            0x00
#define PMIC2_LDO_IUSB_LDO_BP_BYPASS            0x80
#define PMIC2_LDO_IUSB_LDO_BP_MASK              0x80
#define PMIC2_LDO_IUSB_LDO_CTRL_AUTO            0x00
#define PMIC2_LDO_IUSB_LDO_CTRL_LDOEN           0x40
#define PMIC2_LDO_IUSB_LDO_CTRL_MASK            0x40
#define PMIC2_LDO_IUSB_VLDO_1_2V                0x00
#define PMIC2_LDO_IUSB_VLDO_1_5V                0x08
#define PMIC2_LDO_IUSB_VLDO_1_8V                0x10
#define PMIC2_LDO_IUSB_VLDO_2_0V                0x18
#define PMIC2_LDO_IUSB_VLDO_2_4V                0x20
#define PMIC2_LDO_IUSB_VLDO_3_0V                0x28
#define PMIC2_LDO_IUSB_VLDO_3_3V                0x30
#define PMIC2_LDO_IUSB_VLDO_3_6V                0x38
#define PMIC2_LDO_IUSB_VLDO_MASK                0x38
#define PMIC2_LDO_IUSB_IUSB_MAX_0_5MA           0x00
#define PMIC2_LDO_IUSB_IUSB_MAX_1MA             0x01
#define PMIC2_LDO_IUSB_IUSB_MAX_2MA             0x02
#define PMIC2_LDO_IUSB_IUSB_MAX_10MA            0x03
#define PMIC2_LDO_IUSB_IUSB_MAX_50MA            0x04
#define PMIC2_LDO_IUSB_IUSB_MAX_100MA           0x05
#define PMIC2_LDO_IUSB_IUSB_MAX_150MA           0x06
#define PMIC2_LDO_IUSB_IUSB_MAX_200MA           0x07
#define PMIC2_LDO_IUSB_IUSB_MAX_MASK            0x07

/**
 * @brief PMIC 2 FREQUENCY_RANGE register setting.
 * @details Specified setting for FREQUENCY_RANGE register of PMIC 2 Click driver.
 */
#define PMIC2_FREQUENCY_RANGE_MAX_32_KHZ        0x00
#define PMIC2_FREQUENCY_RANGE_MAX_64_KHZ        0x10
#define PMIC2_FREQUENCY_RANGE_MAX_128_KHZ       0x20
#define PMIC2_FREQUENCY_RANGE_MAX_256_KHZ       0x30
#define PMIC2_FREQUENCY_RANGE_MAX_512_KHZ       0x40
#define PMIC2_FREQUENCY_RANGE_MAX_1024_KHZ      0x50
#define PMIC2_FREQUENCY_RANGE_MAX_MASK          0x70
#define PMIC2_FREQUENCY_RANGE_MIN_32_KHZ        0x00
#define PMIC2_FREQUENCY_RANGE_MIN_64_KHZ        0x01
#define PMIC2_FREQUENCY_RANGE_MIN_128_KHZ       0x02
#define PMIC2_FREQUENCY_RANGE_MIN_256_KHZ       0x03
#define PMIC2_FREQUENCY_RANGE_MIN_512_KHZ       0x04
#define PMIC2_FREQUENCY_RANGE_MIN_1024_KHZ      0x05
#define PMIC2_FREQUENCY_RANGE_MIN_MASK          0x07

/**
 * @brief PMIC 2 BOOSTING_FACTOR_RANGE register setting.
 * @details Specified setting for BOOSTING_FACTOR_RANGE register of PMIC 2 Click driver.
 */
#define PMIC2_BOOSTING_FACTOR_RANGE_MAX_2X      0x00
#define PMIC2_BOOSTING_FACTOR_RANGE_MAX_4X      0x10
#define PMIC2_BOOSTING_FACTOR_RANGE_MAX_8X      0x20
#define PMIC2_BOOSTING_FACTOR_RANGE_MAX_16X     0x30
#define PMIC2_BOOSTING_FACTOR_RANGE_MAX_MASK    0x30
#define PMIC2_BOOSTING_FACTOR_RANGE_MIN_2X      0x00
#define PMIC2_BOOSTING_FACTOR_RANGE_MIN_4X      0x01
#define PMIC2_BOOSTING_FACTOR_RANGE_MIN_8X      0x02
#define PMIC2_BOOSTING_FACTOR_RANGE_MIN_16X     0x03
#define PMIC2_BOOSTING_FACTOR_RANGE_MIN_MASK    0x03

/**
 * @brief PMIC 2 MPPT_INTERVAL register setting.
 * @details Specified setting for MPPT_INTERVAL register of PMIC 2 Click driver.
 */
#define PMIC2_MPPT_INTERVAL_0_5S                0x00
#define PMIC2_MPPT_INTERVAL_1S                  0x01
#define PMIC2_MPPT_INTERVAL_2S                  0x02
#define PMIC2_MPPT_INTERVAL_4S                  0x03
#define PMIC2_MPPT_INTERVAL_8S                  0x04
#define PMIC2_MPPT_INTERVAL_16S                 0x05
#define PMIC2_MPPT_INTERVAL_32S                 0x06
#define PMIC2_MPPT_INTERVAL_64S                 0x07
#define PMIC2_MPPT_INTERVAL_MASK                0x07

/**
 * @brief PMIC 2 CHIP_ID register setting.
 * @details Specified setting for CHIP_ID register of PMIC 2 Click driver.
 */
#define PMIC2_CHIP_ID                           0x15

/**
 * @brief PMIC 2 FLAGS register setting.
 * @details Specified setting for FLAGS register of PMIC 2 Click driver.
 */
#define PMIC2_FLAGS_OVP_OUT_MASK                0x10
#define PMIC2_FLAGS_LVD_OUT_MASK                0x08
#define PMIC2_FLAGS_SDF_MASK                    0x04
#define PMIC2_FLAGS_OCF_MASK                    0x02
#define PMIC2_FLAGS_CHIP_OK_MASK                0x01

/**
 * @brief PMIC 2 I_RANGE register setting.
 * @details Specified setting for I_RANGE register of PMIC 2 Click driver.
 */
#define PMIC2_I_RANGE_0                         0x00
#define PMIC2_I_RANGE_1                         0x01
#define PMIC2_I_RANGE_2                         0x02
#define PMIC2_I_RANGE_3                         0x03
#define PMIC2_I_RANGE_MASK                      0x03

/**
 * @brief PMIC 2 I_MEASURED register setting.
 * @details Specified setting for I_MEASURED register of PMIC 2 Click driver.
 */
#define PMIC2_I_MEASURED_RANGE_0                0.0706
#define PMIC2_I_MEASURED_RANGE_1                0.478
#define PMIC2_I_MEASURED_RANGE_2                4.71
#define PMIC2_I_MEASURED_RANGE_3                67.5

/**
 * @brief PMIC 2 device address setting.
 * @details Specified setting for device slave address selection of
 * PMIC 2 Click driver.
 */
#define PMIC2_DEVICE_ADDRESS                    0x3C

/*! @} */ // pmic2_set

/**
 * @defgroup pmic2_map PMIC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of PMIC 2 Click driver.
 */

/**
 * @addtogroup pmic2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PMIC 2 Click to the selected MikroBUS.
 */
#define PMIC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dis = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.bok = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pmic2_map
/*! @} */ // pmic2

/**
 * @brief PMIC 2 Click context object.
 * @details Context object definition of PMIC 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dis;          /**< Disable pin (active high). */

    // Input pins
    digital_in_t bok;           /**< Battery OK pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} pmic2_t;

/**
 * @brief PMIC 2 Click configuration object.
 * @details Configuration object definition of PMIC 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t dis;             /**< Disable pin (active high). */
    pin_name_t bok;             /**< Battery OK pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pmic2_cfg_t;

/**
 * @brief PMIC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PMIC2_OK = 0,
    PMIC2_ERROR = -1

} pmic2_return_value_t;

/*!
 * @addtogroup pmic2 PMIC 2 Click Driver
 * @brief API for configuring and manipulating PMIC 2 Click driver.
 * @{
 */

/**
 * @brief PMIC 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pmic2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pmic2_cfg_setup ( pmic2_cfg_t *cfg );

/**
 * @brief PMIC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pmic2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic2_init ( pmic2_t *ctx, pmic2_cfg_t *cfg );

/**
 * @brief PMIC 2 default configuration function.
 * @details This function executes a default configuration of PMIC 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pmic2_default_cfg ( pmic2_t *ctx );

/**
 * @brief PMIC 2 write register function.
 * @details This function writes a single byte of data to the selected register
 * of the PMIC 2 Click board.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t pmic2_write_reg ( pmic2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PMIC 2 read register function.
 * @details This function reads a single byte of data from the selected register
 * of the PMIC 2 Click board.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t pmic2_read_reg ( pmic2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PMIC 2 disable device function.
 * @details This function disables the device by setting the DIS pin to HIGH
 * on the PMIC 2 Click board.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pmic2_disable_device ( pmic2_t *ctx );

/**
 * @brief PMIC 2 enable device function.
 * @details This function enables the device by setting the DIS pin to LOW
 * on the PMIC 2 Click board.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pmic2_enable_device ( pmic2_t *ctx );

/**
 * @brief PMIC 2 get BOK pin function.
 * @details This function reads the logic state of the BOK pin.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pmic2_get_bok_pin ( pmic2_t *ctx );

/**
 * @brief PMIC 2 check communication function.
 * @details This function checks device communication by reading the chip ID
 * register and comparing it with the expected value.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t pmic2_check_communication ( pmic2_t *ctx );

/**
 * @brief PMIC 2 get charge current function.
 * @details This function reads the charge current measurement and calculates the current value in milliamps.
 * @param[in] ctx : Click context object.
 * See #pmic2_t object definition for detailed explanation.
 * @param[out] current : Pointer to the float variable to store the current value [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t pmic2_get_charge_current ( pmic2_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // PMIC2_H

/*! @} */ // pmic2

// ------------------------------------------------------------------------ END

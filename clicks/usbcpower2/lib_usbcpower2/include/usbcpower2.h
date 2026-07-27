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
 * @file usbcpower2.h
 * @brief This file contains API for USB-C Power 2 Click Driver.
 */

#ifndef USBCPOWER2_H
#define USBCPOWER2_H

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
 * @addtogroup usbcpower2 USB-C Power 2 Click Driver
 * @brief API for configuring and manipulating USB-C Power 2 Click driver.
 * @{
 */

/**
 * @defgroup usbcpower2_reg USB-C Power 2 Registers List
 * @brief List of registers of USB-C Power 2 Click driver.
 */

/**
 * @addtogroup usbcpower2_reg
 * @{
 */

/**
 * @brief USB-C Power 2 register list.
 * @details Specified register list of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_REG_VENDOR_ID                            0x01
#define USBCPOWER2_REG_CONTROL                              0x02
#define USBCPOWER2_REG_INTERRUPT_STATUS                     0x03
#define USBCPOWER2_REG_CC_STATUS                            0x04
#define USBCPOWER2_REG_CON_DET_CONFIG                       0x09
#define USBCPOWER2_REG_VCONN_STATUS                         0x0A
#define USBCPOWER2_REG_RESET                                0x10
#define USBCPOWER2_REG_INTERRUPT_MASK                       0x18
#define USBCPOWER2_REG_INTERRUPT_REG_STATUS                 0x19

/*! @} */ // usbcpower2_reg

/**
 * @defgroup usbcpower2_set USB-C Power 2 Registers Settings
 * @brief Settings for registers of USB-C Power 2 Click driver.
 */

/**
 * @addtogroup usbcpower2_set
 * @{
 */

/**
 * @brief USB-C Power 2 VENDOR_ID register setting.
 * @details Specified setting for VENDOR_ID register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_VENDOR_ID_DEVICE_VERSION                 0x08
#define USBCPOWER2_VENDOR_ID_DEVICE_VERSION_MASK            0xF8
#define USBCPOWER2_VENDOR_ID_VENDOR_ID                      0x03
#define USBCPOWER2_VENDOR_ID_VENDOR_ID_MASK                 0x07

/**
 * @brief USB-C Power 2 CONTROL register setting.
 * @details Specified setting for CONTROL register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_CONTROL_RP_SEL_80UA                      0x00
#define USBCPOWER2_CONTROL_RP_SEL_180UA                     0x08
#define USBCPOWER2_CONTROL_RP_SEL_330UA                     0x10
#define USBCPOWER2_CONTROL_RP_SEL_MASK                      0x18
#define USBCPOWER2_CONTROL_MODE_SEL_DEVICE_UFP              0x00
#define USBCPOWER2_CONTROL_MODE_SEL_HOST_DFP                0x02
#define USBCPOWER2_CONTROL_MODE_SEL_DUAL_ROLE_DRP           0x04
#define USBCPOWER2_CONTROL_MODE_SEL_MASK                    0x06
#define USBCPOWER2_CONTROL_INT_MASK_DIS                     0x00
#define USBCPOWER2_CONTROL_INT_MASK_EN                      0x01
#define USBCPOWER2_CONTROL_INT_MASK_MASK                    0x01

/**
 * @brief USB-C Power 2 INTERRUPT_STATUS register setting.
 * @details Specified setting for INTERRUPT_STATUS register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_INTERRUPT_STATUS_CABLE_DETACHED          0x02
#define USBCPOWER2_INTERRUPT_STATUS_CABLE_ATTACHED          0x01

/**
 * @brief USB-C Power 2 CC_STATUS register setting.
 * @details Specified setting for CC_STATUS register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_CC_STATUS_VBUS_DETECTED                  0x80
#define USBCPOWER2_CC_STATUS_RP_DET_STANDBY                 0x00
#define USBCPOWER2_CC_STATUS_RP_DET_STD_USB                 0x20
#define USBCPOWER2_CC_STATUS_RP_DET_1_5_A                   0x40
#define USBCPOWER2_CC_STATUS_RP_DET_3_0_A                   0x60
#define USBCPOWER2_CC_STATUS_RP_DET_MASK                    0x60
#define USBCPOWER2_CC_STATUS_PORT_STATUS_NOT_CONNECTED      0x00
#define USBCPOWER2_CC_STATUS_PORT_STATUS_DFP_ATTACHED       0x04
#define USBCPOWER2_CC_STATUS_PORT_STATUS_UFP_ATTACHED       0x08
#define USBCPOWER2_CC_STATUS_PORT_STATUS_ANALOG_AUDIO       0x0C
#define USBCPOWER2_CC_STATUS_PORT_STATUS_DEBUG              0x10
#define USBCPOWER2_CC_STATUS_PORT_STATUS_MASK               0x1C
#define USBCPOWER2_CC_STATUS_CC_POLARITY_CABLE_NOT_ATTACHED 0x00
#define USBCPOWER2_CC_STATUS_CC_POLARITY_CC1_NORMAL         0x01
#define USBCPOWER2_CC_STATUS_CC_POLARITY_CC2_REVERSED       0x02
#define USBCPOWER2_CC_STATUS_CC_POLARITY_MASK               0x03

/**
 * @brief USB-C Power 2 CON_DET_CONFIG register setting.
 * @details Specified setting for CON_DET_CONFIG register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_CON_DET_CONFIG_EN                        0x00
#define USBCPOWER2_CON_DET_CONFIG_DIS                       0x01
#define USBCPOWER2_CON_DET_CONFIG_MASK                      0x01

/**
 * @brief USB-C Power 2 VCONN_STATUS register setting.
 * @details Specified setting for VCONN_STATUS register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_VCONN_STATUS_STANDBY                     0x00
#define USBCPOWER2_VCONN_STATUS_CC1                         0x01
#define USBCPOWER2_VCONN_STATUS_CC2                         0x02
#define USBCPOWER2_VCONN_STATUS_MASK                        0x03

/**
 * @brief USB-C Power 2 RESET register setting.
 * @details Specified setting for RESET register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_RESET_SYSTEM                             0x01

/**
 * @brief USB-C Power 2 INTERRUPT_MASK register setting.
 * @details Specified setting for INTERRUPT_MASK register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_INTERRUPT_MASK_CC1_CC2_CHANGE_DIS        0x00
#define USBCPOWER2_INTERRUPT_MASK_CC1_CC2_CHANGE_EN         0x10
#define USBCPOWER2_INTERRUPT_MASK_CC1_CC2_CHANGE_MASK       0x10
#define USBCPOWER2_INTERRUPT_MASK_ROLE_CHANGE_DIS           0x00
#define USBCPOWER2_INTERRUPT_MASK_ROLE_CHANGE_EN            0x08
#define USBCPOWER2_INTERRUPT_MASK_ROLE_CHANGE_MASK          0x08
#define USBCPOWER2_INTERRUPT_MASK_ORIENTATION_DIS           0x00
#define USBCPOWER2_INTERRUPT_MASK_ORIENTATION_EN            0x04
#define USBCPOWER2_INTERRUPT_MASK_ORIENTATION_MASK          0x04
#define USBCPOWER2_INTERRUPT_MASK_DEBUG_DIS                 0x00
#define USBCPOWER2_INTERRUPT_MASK_DEBUG_EN                  0x02
#define USBCPOWER2_INTERRUPT_MASK_DEBUG_MASK                0x02
#define USBCPOWER2_INTERRUPT_MASK_AUDIO_DIS                 0x00
#define USBCPOWER2_INTERRUPT_MASK_AUDIO_EN                  0x01
#define USBCPOWER2_INTERRUPT_MASK_AUDIO_MASK                0x01

/**
 * @brief USB-C Power 2 INTERRUPT_REG_STATUS register setting.
 * @details Specified setting for INTERRUPT_REG_STATUS register of USB-C Power 2 Click driver.
 */
#define USBCPOWER2_INTERRUPT_REG_STATUS_CC1_CC2_CHANGE      0x10
#define USBCPOWER2_INTERRUPT_REG_STATUS_ROLE_CHANGE         0x08
#define USBCPOWER2_INTERRUPT_REG_STATUS_ORIENTATION         0x04
#define USBCPOWER2_INTERRUPT_REG_STATUS_DEBUG               0x02
#define USBCPOWER2_INTERRUPT_REG_STATUS_AUDIO               0x01

/**
 * @brief USB-C Power 2 device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Power 2 Click driver.
 */
#define USBCPOWER2_DEVICE_ADDRESS                           0x1D

/*! @} */ // usbcpower2_set

/**
 * @defgroup usbcpower2_map USB-C Power 2 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Power 2 Click driver.
 */

/**
 * @addtogroup usbcpower2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Power 2 Click to the selected MikroBUS.
 */
#define USBCPOWER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.id_pin = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcpower2_map
/*! @} */ // usbcpower2

/**
 * @brief USB-C Power 2 Click context object.
 * @details Context object definition of USB-C Power 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t id_pin;        /**< USB ID pin (Low-Host, High-Device). */
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} usbcpower2_t;

/**
 * @brief USB-C Power 2 Click configuration object.
 * @details Configuration object definition of USB-C Power 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t id_pin;          /**< USB ID pin (Low-Host, High-Device). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} usbcpower2_cfg_t;

/**
 * @brief USB-C Power 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCPOWER2_OK = 0,
    USBCPOWER2_ERROR = -1

} usbcpower2_return_value_t;

/*!
 * @addtogroup usbcpower2 USB-C Power 2 Click Driver
 * @brief API for configuring and manipulating USB-C Power 2 Click driver.
 * @{
 */

/**
 * @brief USB-C Power 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcpower2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcpower2_cfg_setup ( usbcpower2_cfg_t *cfg );

/**
 * @brief USB-C Power 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcpower2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower2_init ( usbcpower2_t *ctx, usbcpower2_cfg_t *cfg );

/**
 * @brief USB-C Power 2 default configuration function.
 * @details This function executes a default configuration of USB-C Power 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t usbcpower2_default_cfg ( usbcpower2_t *ctx );

/**
 * @brief USB-C Power 2 write register function.
 * @details This function writes a single byte of data to the selected writable
 * register address.
 * @param[in] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @param[in] reg : Writable register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower2_write_reg ( usbcpower2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Power 2 read register function.
 * @details This function reads a single byte of data from the selected
 * readable register address.
 * @param[in] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @param[in] reg : Readable register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower2_read_reg ( usbcpower2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief USB-C Power 2 get ID pin function.
 * @details This function reads and returns the logic state of the ID pin.
 * @param[in] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @return ID pin logic state.
 * @note None.
 */
uint8_t usbcpower2_get_id_pin ( usbcpower2_t *ctx );

/**
 * @brief USB-C Power 2 get INT pin function.
 * @details This function reads and returns the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @return INT pin logic state.
 * @note None.
 */
uint8_t usbcpower2_get_int_pin ( usbcpower2_t *ctx );

/**
 * @brief USB-C Power 2 communication check function.
 * @details This function checks communication with the device by reading the
 * vendor ID register and validating the returned value.
 * @param[in] ctx : Click context object.
 * See #usbcpower2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower2_check_com ( usbcpower2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCPOWER2_H

/*! @} */ // usbcpower2

// ------------------------------------------------------------------------ END

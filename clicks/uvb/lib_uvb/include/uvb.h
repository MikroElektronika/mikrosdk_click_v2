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
 * @file uvb.h
 * @brief This file contains API for UVB Click Driver.
 */

#ifndef UVB_H
#define UVB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup uvb UVB Click Driver
 * @brief API for configuring and manipulating UVB Click driver.
 * @{
 */

/**
 * @defgroup uvb_reg UVB Registers List
 * @brief List of registers of UVB Click driver.
 */

/**
 * @addtogroup uvb_reg
 * @{
 */

/**
 * @brief UVB description register.
 * @details Specified register for description of UVB Click driver.
 */
#define UVB_REG_CHIP_ID               0x00
#define UVB_REG_MODE                  0x01
#define UVB_REG_RES_UV                0x04
#define UVB_REG_RANGE_UVB             0x07
#define UVB_REG_MODE_CTRL             0x0A
#define UVB_REG_SOFT_RESET            0x0B
#define UVB_REG_UVB_LSB               0x17
#define UVB_REG_UVB_MSB               0x18
#define UVB_REG_NVM_READ_CTRL         0x30
#define UVB_REG_NVM_MSB               0x31
#define UVB_REG_NVM_LSB               0x32

/*! @} */ // uvb_reg

/**
 * @defgroup uvb_set UVB Registers Settings
 * @brief Settings for registers of UVB Click driver.
 */

/**
 * @addtogroup uvb_set
 * @{
 */

/**
 * @brief UVB description setting.
 * @details Specified setting for description of UVB Click driver.
 */
#define UVB_MODE_NO_OPERATION         0x00
#define UVB_MODE_UVB_OPERATION        0x20
#define UVB_MODE_NORMAL               0x00
#define UVB_MODE_LOW_POWER            0x01
#define UVB_MODE_AUTO_SHUTDOWN        0x02
#define UVB_MODE_SHUTDOWN             0x03

/**
 * @brief UVB resolution setting.
 * @details Specified resolution setting for description of UVB Click driver.
 */
#define UVB_RESOLUTION_800ms          0x00
#define UVB_RESOLUTION_400ms          0x01
#define UVB_RESOLUTION_200ms          0x02
#define UVB_RESOLUTION_100ms          0x03

/**
 * @brief UVB range setting.
 * @details Specified range setting of UVB Click driver.
 */
#define UVB_RANGE_x1                  0x00
#define UVB_RANGE_x2                  0x01
#define UVB_RANGE_x4                  0x02
#define UVB_RANGE_x8                  0x03
#define UVB_RANGE_x16                 0x04
#define UVB_RANGE_x32                 0x05
#define UVB_RANGE_x64                 0x06
#define UVB_RANGE_x128                0x07

/**
 * @brief UVB sleep setting.
 * @details Specified sleep setting of UVB Click driver.
 */
#define UVB_MCTRL_SLEEP_2_TIMES       0x00
#define UVB_MCTRL_SLEEP_4_TIMES       0x01
#define UVB_MCTRL_SLEEP_8_TIMES       0x02
#define UVB_MCTRL_SLEEP_16_TIMES      0x03
#define UVB_MCTRL_SLEEP_32_TIMES      0x04
#define UVB_MCTRL_SLEEP_64_TIMES      0x05
#define UVB_MCTRL_SLEEP_128_TIMES     0x06
#define UVB_MCTRL_SLEEP_256_TIMES     0x07

#define UVB_DEF_CHIP_ID               0x62


/**
 * @brief UVB device address setting.
 * @details Specified setting for device slave address selection of
 * UVB Click driver.
 */
#define UVB_SET_DEV_ADDR  0x39

/*! @} */ // uvb_set

/**
 * @defgroup uvb_map UVB MikroBUS Map
 * @brief MikroBUS pin mapping of UVB Click driver.
 */

/**
 * @addtogroup uvb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UVB Click to the selected MikroBUS.
 */
#define UVB_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // uvb_map
/*! @} */ // uvb

/**
 * @brief UVB Click context object.
 * @details Context object definition of UVB Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} uvb_t;

/**
 * @brief UVB Click configuration object.
 * @details Configuration object definition of UVB Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} uvb_cfg_t;

/**
 * @brief UVB Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   UVB_OK = 0,
   UVB_ERROR = -1

} uvb_return_value_t;

/*!
 * @addtogroup uvb UVB Click Driver
 * @brief API for configuring and manipulating UVB Click driver.
 * @{
 */

/**
 * @brief UVB configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uvb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uvb_cfg_setup ( uvb_cfg_t *cfg );

/**
 * @brief UVB initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uvb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t uvb_init ( uvb_t *ctx, uvb_cfg_t *cfg );

/**
 * @brief UVB default configuration function.
 * @details This function executes a default configuration of UVB
 * click board.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uvb_default_cfg ( uvb_t *ctx );

/**
 * @brief UVB I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t uvb_generic_write ( uvb_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief UVB I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t uvb_generic_read ( uvb_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Configuration register.
 * @details This function configure register.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @param[in] reg : Register Address.
 * @param[in] cfg : Config data.
 * @return Nothing.
 */
void uvb_configuration ( uvb_t *ctx, uint8_t reg, uint8_t cfg );

/**
 * @brief Read one byte data from register.
 * @details This function reads one byte of data.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @param[in] reg : Register Address.
 * @returns One byte data.
 */
uint8_t uvb_read_byte ( uvb_t *ctx, uint8_t reg );

/**
 * @brief Check communication.
 * @details This function checks communication.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t uvb_check_communication ( uvb_t *ctx );

/**
 * @brief Get UVB data.
 * @details This function gets UVB data.
 * @param[in] ctx : Click context object.
 * See #uvb_t object definition for detailed explanation.
 * @returns (16 bit) UVB data.
 */
uint16_t uvb_get_uv_data ( uvb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // UVB_H

/*! @} */ // uvb

// ------------------------------------------------------------------------ END

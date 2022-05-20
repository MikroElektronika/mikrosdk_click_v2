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
 * @file proximity17.h
 * @brief This file contains API for Proximity 17 Click Driver.
 */

#ifndef PROXIMITY17_H
#define PROXIMITY17_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup proximity17 Proximity 17 Click Driver
 * @brief API for configuring and manipulating Proximity 17 Click driver.
 * @{
 */

/**
 * @defgroup proximity17_reg Proximity 17 Registers List
 * @brief List of registers of Proximity 17 Click driver.
 */

/**
 * @addtogroup proximity17_reg
 * @{
 */

/**
 * @brief Proximity 17 register list.
 * @details Specified register list of Proximity 17 Click driver.
 */
#define PROXIMITY17_REG_ENABLE              0x80
#define PROXIMITY17_REG_PRATE               0x82
#define PROXIMITY17_REG_PILTL               0x88
#define PROXIMITY17_REG_PILTH               0x89
#define PROXIMITY17_REG_PIHTL               0x8A
#define PROXIMITY17_REG_PIHTH               0x8B
#define PROXIMITY17_REG_PERS                0x8C
#define PROXIMITY17_REG_CFG0                0x8D
#define PROXIMITY17_REG_PCFG0               0x8E
#define PROXIMITY17_REG_PCFG1               0x8F
#define PROXIMITY17_REG_REVID               0x91
#define PROXIMITY17_REG_ID                  0x92
#define PROXIMITY17_REG_STATUS              0x9B
#define PROXIMITY17_REG_PDATAL              0x9C
#define PROXIMITY17_REG_PDATAH              0x9D
#define PROXIMITY17_REG_REVID2              0xA6
#define PROXIMITY17_REG_SOFTRST             0xA8
#define PROXIMITY17_REG_PWTIME              0xA9
#define PROXIMITY17_REG_CFG8                0xAA
#define PROXIMITY17_REG_CFG3                0xAB
#define PROXIMITY17_REG_CFG6                0xAE
#define PROXIMITY17_REG_PFILTER             0xB3
#define PROXIMITY17_REG_POFFSETL            0xC0
#define PROXIMITY17_REG_POFFSETH            0xC1
#define PROXIMITY17_REG_CALIB               0xD7
#define PROXIMITY17_REG_CALIBCFG            0xD9
#define PROXIMITY17_REG_CALIBSTAT           0xDC
#define PROXIMITY17_REG_INTENAB             0xDD
#define PROXIMITY17_REG_FAC_L               0xE5
#define PROXIMITY17_REG_FAC_H               0xE6
#define PROXIMITY17_REG_TEST9               0xF9

/*! @} */ // proximity17_reg

/**
 * @defgroup proximity17_set Proximity 17 Registers Settings
 * @brief Settings for registers of Proximity 17 Click driver.
 */

/**
 * @addtogroup proximity17_set
 * @{
 */

/**
 * @brief Proximity 17 ENABLE register setting.
 * @details Specified setting for ENABLE register of Proximity 17 Click driver.
 */
#define PROXIMITY17_ENABLE_PWEN             0x10
#define PROXIMITY17_ENABLE_PEN              0x04
#define PROXIMITY17_ENABLE_PON              0x01

/**
 * @brief Proximity 17 SOFTRST register setting.
 * @details Specified setting for SOFTRST register of Proximity 17 Click driver.
 */
#define PROXIMITY17_SOFT_RESET              0x01

/**
 * @brief Proximity 17 PCFG0 register setting.
 * @details Specified setting for PCFG0 register of Proximity 17 Click driver.
 */
#define PROXIMITY17_PGAIN_1X                0x00
#define PROXIMITY17_PGAIN_2X                0x40
#define PROXIMITY17_PGAIN_4X                0x80
#define PROXIMITY17_PGAIN_8X                0xC0
#define PROXIMITY17_PPULSE_MIN              0x00
#define PROXIMITY17_PPULSE_DEFAULT          0x0F
#define PROXIMITY17_PPULSE_MAX              0x3F

/**
 * @brief Proximity 17 PCFG1 register setting.
 * @details Specified setting for PCFG1 register of Proximity 17 Click driver.
 */
#define PROXIMITY17_PPULSE_LEN_1US          0x00
#define PROXIMITY17_PPULSE_LEN_2US          0x20
#define PROXIMITY17_PPULSE_LEN_4US          0x40
#define PROXIMITY17_PPULSE_LEN_8US          0x60
#define PROXIMITY17_PPULSE_LEN_12US         0x80
#define PROXIMITY17_PPULSE_LEN_16US         0xA0
#define PROXIMITY17_PPULSE_LEN_24US         0xC0
#define PROXIMITY17_PPULSE_LEN_32US         0xE0
#define PROXIMITY17_PLDRIVE_2mA             0x00
#define PROXIMITY17_PLDRIVE_3mA             0x01
#define PROXIMITY17_PLDRIVE_4mA             0x02
#define PROXIMITY17_PLDRIVE_5mA             0x03
#define PROXIMITY17_PLDRIVE_6mA             0x04
#define PROXIMITY17_PLDRIVE_7mA             0x05
#define PROXIMITY17_PLDRIVE_8mA             0x06
#define PROXIMITY17_PLDRIVE_9mA             0x07
#define PROXIMITY17_PLDRIVE_10mA            0x08

/**
 * @brief Proximity 17 CFG8 register setting.
 * @details Specified setting for CFG8 register of Proximity 17 Click driver.
 */
#define PROXIMITY17_PDSELECT_NO_PDIODE      0x00
#define PROXIMITY17_PDSELECT_FAR_PDIODE     0x01
#define PROXIMITY17_PDSELECT_NEAR_PDIODE    0x02
#define PROXIMITY17_PDSELECT_BOTH_PDIODE    0x03

/**
 * @brief Proximity 17 STATUS register setting.
 * @details Specified setting for STATUS register of Proximity 17 Click driver.
 */
#define PROXIMITY17_STATUS_PHIGH            0x80
#define PROXIMITY17_STATUS_PLOW             0x40
#define PROXIMITY17_STATUS_PSAT             0x20
#define PROXIMITY17_STATUS_PINT             0x10
#define PROXIMITY17_STATUS_CINT             0x08
#define PROXIMITY17_STATUS_ZINT             0x04
#define PROXIMITY17_STATUS_PSAT_REFLECTIVE  0x02
#define PROXIMITY17_STATUS_PSAT_AMBIENT     0x01
#define PROXIMITY17_STATUS_CLEAR_ALL        0xFF

/**
 * @brief Proximity 17 INTENAB register setting.
 * @details Specified setting for INTENAB register of Proximity 17 Click driver.
 */
#define PROXIMITY17_INTENAB_PIM             0x20
#define PROXIMITY17_INTENAB_PIEN            0x10
#define PROXIMITY17_INTENAB_PSIEN           0x08
#define PROXIMITY17_INTENAB_CIEN            0x04
#define PROXIMITY17_INTENAB_ZIEN            0x02
#define PROXIMITY17_INTENAB_DISABLE         0x00

/**
 * @brief Proximity 17 CALIB register setting.
 * @details Specified setting for CALIB register of Proximity 17 Click driver.
 */
#define PROXIMITY17_CALAVG                  0x80
#define PROXIMITY17_ELECTRICAL_CALIB        0x20
#define PROXIMITY17_CALPRATE                0x10
#define PROXIMITY17_START_OFFSET_CAL        0x01

/**
 * @brief Proximity 17 CALIBCFG register setting.
 * @details Specified setting for CALIBCFG register of Proximity 17 Click driver.
 */
#define PROXIMITY17_BINSRCH_TARGET_3        0x00
#define PROXIMITY17_BINSRCH_TARGET_7        0x20
#define PROXIMITY17_BINSRCH_TARGET_15       0x40
#define PROXIMITY17_BINSRCH_TARGET_31       0x60
#define PROXIMITY17_BINSRCH_TARGET_63       0x80
#define PROXIMITY17_BINSRCH_TARGET_127      0xA0
#define PROXIMITY17_BINSRCH_TARGET_255      0xC0
#define PROXIMITY17_BINSRCH_TARGET_511      0xE0
#define PROXIMITY17_CALIBCFG_RESERVED       0x10
#define PROXIMITY17_AUTO_OFFSET_ADJ         0x08
#define PROXIMITY17_PROX_AVG_DISABLE        0x00
#define PROXIMITY17_PROX_AVG_2              0x01
#define PROXIMITY17_PROX_AVG_4              0x02
#define PROXIMITY17_PROX_AVG_8              0x03
#define PROXIMITY17_PROX_AVG_16             0x04
#define PROXIMITY17_PROX_AVG_32             0x05
#define PROXIMITY17_PROX_AVG_64             0x06
#define PROXIMITY17_PROX_AVG_128            0x07                

/**
 * @brief Proximity 17 CALIBSTAT register setting.
 * @details Specified setting for CALIBSTAT register of Proximity 17 Click driver.
 */
#define PROXIMITY17_OFFSET_ADJUSTED         0x04
#define PROXIMITY17_CALIB_FINISHED          0x01

/**
 * @brief Proximity 17 CFG6 register setting.
 * @details Specified setting for CFG6 register of Proximity 17 Click driver.
 */
#define PROXIMITY17_APC_ENABLE              0x3F
#define PROXIMITY17_APC_DISABLE             0x7F

/**
 * @brief Proximity 17 device ID value.
 * @details Specified value of device ID of Proximity 17 Click driver.
 */
#define PROXIMITY17_DEVICE_ID               0x44

/**
 * @brief Proximity 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 17 Click driver.
 */
#define PROXIMITY17_DEVICE_ADDRESS          0x39

/*! @} */ // proximity17_set

/**
 * @defgroup proximity17_map Proximity 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 17 Click driver.
 */

/**
 * @addtogroup proximity17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 17 Click to the selected MikroBUS.
 */
#define PROXIMITY17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity17_map
/*! @} */ // proximity17

/**
 * @brief Proximity 17 Click context object.
 * @details Context object definition of Proximity 17 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} proximity17_t;

/**
 * @brief Proximity 17 Click configuration object.
 * @details Configuration object definition of Proximity 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} proximity17_cfg_t;

/**
 * @brief Proximity 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY17_OK = 0,
    PROXIMITY17_ERROR = -1

} proximity17_return_value_t;

/*!
 * @addtogroup proximity17 Proximity 17 Click Driver
 * @brief API for configuring and manipulating Proximity 17 Click driver.
 * @{
 */

/**
 * @brief Proximity 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity17_cfg_setup ( proximity17_cfg_t *cfg );

/**
 * @brief Proximity 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_init ( proximity17_t *ctx, proximity17_cfg_t *cfg );

/**
 * @brief Proximity 17 default configuration function.
 * @details This function executes a default configuration of Proximity 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity17_default_cfg ( proximity17_t *ctx );

/**
 * @brief Proximity 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_generic_write ( proximity17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Proximity 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_generic_read ( proximity17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Proximity 17 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_write_register ( proximity17_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Proximity 17 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_read_register ( proximity17_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Proximity 17 check communication function.
 * @details This function checks the communication by reading and verifying the device ID 
 * on up to 10 tries.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_check_communication ( proximity17_t *ctx );

/**
 * @brief Proximity 17 soft reset function.
 * @details This function executes the defice software reset command.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_soft_reset ( proximity17_t *ctx );

/**
 * @brief Proximity 17 read proximity function.
 * @details This function reads the raw proximity data. The higher the value, the closer the detected object is.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @param[out] prox_data : Proximity data 14-bit (10-bit in case APC is disabled).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity17_read_proximity ( proximity17_t *ctx, uint16_t *prox_data );

/**
 * @brief Proximity 17 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity17_get_int_pin ( proximity17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY17_H

/*! @} */ // proximity17

// ------------------------------------------------------------------------ END

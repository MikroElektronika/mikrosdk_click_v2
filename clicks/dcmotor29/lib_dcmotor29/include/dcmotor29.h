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
 * @file dcmotor29.h
 * @brief This file contains API for DC Motor 29 Click Driver.
 */

#ifndef DCMOTOR29_H
#define DCMOTOR29_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup dcmotor29 DC Motor 29 Click Driver
 * @brief API for configuring and manipulating DC Motor 29 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor29_reg DC Motor 29 Registers List
 * @brief List of registers of DC Motor 29 Click driver.
 */

/**
 * @addtogroup dcmotor29_reg
 * @{
 */

/**
 * @brief DC Motor 29 description register.
 * @details Specified register for description of DC Motor 29 Click driver.
 */
#define DCMOTOR29_REG_DEVICE_ID                   0x00
#define DCMOTOR29_REG_FAULT_SUMMARY               0x01
#define DCMOTOR29_REG_STATUS1                     0x02
#define DCMOTOR29_REG_STATUS2                     0x03
#define DCMOTOR29_REG_COMMAND                     0x08
#define DCMOTOR29_REG_SPI_IN                      0x09
#define DCMOTOR29_REG_CONFIG1                     0x0A
#define DCMOTOR29_REG_CONFIG2                     0x0B
#define DCMOTOR29_REG_CONFIG3                     0x0C
#define DCMOTOR29_REG_CONFIG4                     0x0D
#define DCMOTOR29_REG_INPUT_PORT                  0x00
#define DCMOTOR29_REG_OUTPUT_PORT                 0x01
#define DCMOTOR29_REG_POLARITY_INV                0x02
#define DCMOTOR29_REG_CONFIG                      0x03

/*! @} */ // dcmotor29_reg

/**
 * @defgroup dcmotor29_set DC Motor 29 Registers Settings
 * @brief Settings for registers of DC Motor 29 Click driver.
 */

/**
 * @addtogroup dcmotor29_set
 * @{
 */

/**
 * @brief DC Motor 29 description setting.
 * @details Specified setting for description of DC Motor 29 Click driver.
 */
#define DCMOTOR29_CLR_FLT_CMD                     0x80
#define DCMOTOR29_SPI_IN_UNLOCK_CMD               0x10
#define DCMOTOR29_SPI_IN_LOCK_CMD                 0x08
#define DCMOTOR29_REG_UNLOCK_CMD                  0x01
#define DCMOTOR29_REG_LOCK_CMD                    0x02

/**
 * @brief DC Motor 29 pin setting.
 * @details Specified setting for pin selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_NONE_PIN                        0x00
#define DCMOTOR29_IN2_PIN                         0x01
#define DCMOTOR29_DOF_PIN                         0x02
#define DCMOTOR29_FLT_PIN                         0x04
#define DCMOTOR29_ALL_PIN                         0x07

/**
 * @brief DC Motor 29 read register.
 * @details Specified setting for reading registers of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_READ_REG_MASK                   0x40

/**
 * @brief DC Motor 29 DRVOFF pin setting.
 * @details Specified setting for DRVOFF pin selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_DRVOFF_ON                       0x01
#define DCMOTOR29_DRVOFF_OFF                      0x00

/**
 * @brief DC Motor 29 pin setting.
 * @details Specified setting for pin selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_PIN_STATE_HIGH                  0x01
#define DCMOTOR29_PIN_STATE_LOW                   0x00

/**
 * @brief DC Motor 29 SPI_IN Register setting.
 * @details Specified setting for SPI_IN Register selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_S_EN_DEVOFF_MASK                0x08
#define DCMOTOR29_S_EN_DEVOFF2_MASK               0x04
#define DCMOTOR29_S_EN_IN1_MASK                   0x02
#define DCMOTOR29_S_EN_IN2_MASK                   0x01
#define DCMOTOR29_S_EN_NONE                       0x00

/**
 * @brief DC Motor 29 CONFIG1 Register setting.
 * @details Specified setting for CONFIG1 Register selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_EN_OLA                          0x80
#define DCMOTOR29_VMOV_SEL_DISABLED               0x60
#define DCMOTOR29_VMOV_SEL_18V                    0x40
#define DCMOTOR29_VMOV_SEL_28V                    0x20
#define DCMOTOR29_VMOV_SEL_35V                    0x00
#define DCMOTOR29_SSC_DISABLE                     0x10
#define DCMOTOR29_OCP_RETRY                       0x08
#define DCMOTOR29_TSD_RETRY                       0x04
#define DCMOTOR29_VMOV_RETRY                      0x02
#define DCMOTOR29_OLA_RETRY                       0x01

/**
 * @brief DC Motor 29 CONFIG3 Register setting.
 * @details Specified setting for CONFIG3 Register selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_TOF_50_US                       0xC0
#define DCMOTOR29_TOF_40_US                       0x80
#define DCMOTOR29_TOF_30_US                       0x40
#define DCMOTOR29_TOF_20_US                       0x00
#define DCMOTOR29_S_SR_50_V_US                    0x1C
#define DCMOTOR29_S_SR_38_V_US                    0x18
#define DCMOTOR29_S_SR_26_V_US                    0x14
#define DCMOTOR29_S_SR_20_V_US                    0x10
#define DCMOTOR29_S_SR_14_V_US                    0x0C
#define DCMOTOR29_S_SR_9_8V_US                    0x08
#define DCMOTOR29_S_SR_5_V_US                     0x04
#define DCMOTOR29_S_SR_1_5V_US                    0x00
#define DCMOTOR29_S_MODE_PWM                      0x03
#define DCMOTOR29_S_MODE_INDEPENDENT              0x01
#define DCMOTOR29_S_MODE_PH_EN                    0x00

/**
 * @brief DC Motor 29 motor states setting.
 * @details Specified setting for motor state selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_DRIVE_MOTOR_CW                  0x00
#define DCMOTOR29_DRIVE_MOTOR_CCW                 0x01
#define DCMOTOR29_DRIVE_MOTOR_BRAKE               0x02
#define DCMOTOR29_DRIVE_MOTOR_COASTING            0x03

/**
 * @brief DC Motor 29 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 29 Click driver.
 */
#define DCMOTOR29_DEVICE_ADDRESS_A1A0_00          0x70
#define DCMOTOR29_DEVICE_ADDRESS_A1A0_01          0x71
#define DCMOTOR29_DEVICE_ADDRESS_A1A0_10          0x72
#define DCMOTOR29_DEVICE_ADDRESS_A1A0_11          0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dcmotor29_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DCMOTOR29_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DCMOTOR29_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dcmotor29_set

/**
 * @defgroup dcmotor29_map DC Motor 29 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 29 Click driver.
 */

/**
 * @addtogroup dcmotor29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 29 Click to the selected MikroBUS.
 */
#define DCMOTOR29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ip = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor29_map
/*! @} */ // dcmotor29

/**
 * @brief DC Motor 29 Click context object.
 * @details Context object definition of DC Motor 29 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t in1;          /**< Enable O1 pin. */

    // Input pins
    digital_in_t ip;            /**< Driver load current analog feedbac. */
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} dcmotor29_t;

/**
 * @brief DC Motor 29 Click configuration object.
 * @details Configuration object definition of DC Motor 29 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t ip;              /**< Driver load current analog feedbac. */
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t in1;             /**< Enable O1 pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} dcmotor29_cfg_t;

/**
 * @brief DC Motor 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR29_OK = 0,
    DCMOTOR29_ERROR = -1

} dcmotor29_return_value_t;

/*!
 * @addtogroup dcmotor29 DC Motor 29 Click Driver
 * @brief API for configuring and manipulating DC Motor 29 Click driver.
 * @{
 */

/**
 * @brief DC Motor 29 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor29_cfg_setup ( dcmotor29_cfg_t *cfg );

/**
 * @brief DC Motor 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_init ( dcmotor29_t *ctx, dcmotor29_cfg_t *cfg );

/**
 * @brief DC Motor 29 default configuration function.
 * @details This function executes a default configuration of DC Motor 29
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor29_default_cfg ( dcmotor29_t *ctx );

/**
 * @brief DC Motor 29 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_generic_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DC Motor 29 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_generic_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DC Motor 29 set IN1 pin function.
 * @details This function is used to set state of the IN1 pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void dcmotor29_set_in1_pin ( dcmotor29_t *ctx, uint8_t pin_state );

/**
 * @brief DC Motor 29 set RST pin function.
 * @details This function is used to set state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void dcmotor29_set_rst_pin ( dcmotor29_t *ctx, uint8_t pin_state );

/**
 * @brief DC Motor 29 get IP pin function.
 * @details This function is used to get state of the IP pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @return State of the IP pin.
 * @note None.
 */
uint8_t dcmotor29_get_ip_pin ( dcmotor29_t *ctx );

/**
 * @brief DC Motor 29 get INT pin function.
 * @details This function is used to get state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t dcmotor29_get_int_pin ( dcmotor29_t *ctx );

/**
 * @brief DC Motor 29 data register writing function.
 * @details This function writes a data byte into
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_register_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 29 data register reading function.
 * @details This function reads a data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_register_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 29 port ecpander write register function.
 * @details This function writes a data byte into
 * the selected register of the port expander.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_port_expander_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 29 port ecpander read register function.
 * @details This function reads a data byte from
 * the selected register of the port expander.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_port_expander_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 29 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_set_pins ( dcmotor29_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief DC Motor 29 control drvoff function.
 * @details This function sets the state of the DRVOFF pin, enabling or disabling outputs.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] drvoff_state : State of the DRVOFF pin.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_drvoff_state ( dcmotor29_t *ctx, uint8_t drvoff_state );

/**
 * @brief DC Motor 29 drive motor function.
 * @details This function sets motor driver into the selected state.
 * @param[in] ctx : Click context object.
 * See #dcmotor29_t object definition for detailed explanation.
 * @param[in] state : State of the driver.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor29_drive_motor ( dcmotor29_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR29_H

/*! @} */ // dcmotor29

// ------------------------------------------------------------------------ END

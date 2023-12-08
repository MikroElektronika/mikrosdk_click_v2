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
 * @file hbridge14.h
 * @brief This file contains API for H-Bridge 14 Click Driver.
 */

#ifndef HBRIDGE14_H
#define HBRIDGE14_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup hbridge14 H-Bridge 14 Click Driver
 * @brief API for configuring and manipulating H-Bridge 14 Click driver.
 * @{
 */

/**
 * @defgroup hbridge14_reg H-Bridge 14 Registers List
 * @brief List of registers of H-Bridge 14 Click driver.
 */

/**
 * @addtogroup hbridge14_reg
 * @{
 */

/**
 * @brief H-Bridge 14 description register.
 * @details Specified register for description of H-Bridge 14 Click driver.
 */
#define HBRIDGE14_REG_FAULT_STATUS                0x00
#define HBRIDGE14_REG_DIAG_STATUS                 0x02
#define HBRIDGE14_REG_IC1_CTRL                    0x04
#define HBRIDGE14_REG_IC2_CTRL                    0x06
#define HBRIDGE14_REG_IC3_CTRL                    0x08
#define HBRIDGE14_REG_IC4_CTRL                    0x0A
#define HBRIDGE14_REG_INPUT_PORT                  0x00
#define HBRIDGE14_REG_OUTPUT_PORT                 0x01
#define HBRIDGE14_REG_POLARITY_INV                0x02
#define HBRIDGE14_REG_CONFIG                      0x03

/*! @} */ // hbridge14_reg

/**
 * @defgroup hbridge14_set H-Bridge 14 Registers Settings
 * @brief Settings for registers of H-Bridge 14 Click driver.
 */

/**
 * @addtogroup hbridge14_set
 * @{
 */

/**
 * @brief H-Bridge 14 DRVOFF pin setting.
 * @details Specified setting for DRVOFF pin selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_DIS_ON                            0x01
#define HBRIDGE14_DIS_OFF                           0x00

/**
 * @brief H-Bridge 14 SLEEP pin setting.
 * @details Specified setting for SLEEP pin selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_SLEEP_ON                          0x01
#define HBRIDGE14_SLEEP_OFF                         0x00

/**
 * @brief H-Bridge 14 pin setting.
 * @details Specified setting for pin selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_PIN_STATE_HIGH                    0x01
#define HBRIDGE14_PIN_STATE_LOW                     0x00

/**
 * @brief H-Bridge 14 motor states setting.
 * @details Specified setting for motor state selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_DRIVE_MOTOR_CW                    0x00
#define HBRIDGE14_DRIVE_MOTOR_CCW                   0x01
#define HBRIDGE14_DRIVE_MOTOR_BRAKE                 0x02
#define HBRIDGE14_DRIVE_MOTOR_COASTING              0x03

/**
 * @brief H-Bridge 14 pin mask setting.
 * @details Specified setting for pin mask selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_NONE_PIN                          0x00
#define HBRIDGE14_SLP_PIN                           0x01
#define HBRIDGE14_FLT_PIN                           0x02
#define HBRIDGE14_DIS_PIN                           0x04
#define HBRIDGE14_ALL_PIN                           0x07

/**
 * @brief H-Bridge 14 IC1 Control Register setting.
 * @details Specified setting for IC1 Control Register selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_TOF_80_US                         0xC0
#define HBRIDGE14_TOF_60_US                         0x80
#define HBRIDGE14_TOF_40_US                         0x40
#define HBRIDGE14_TOF_20_US                         0x00
#define HBRIDGE14_SPI_IN_EN                         0x20
#define HBRIDGE14_SPI_IN_DIS                        0x00
#define HBRIDGE14_S_SR_2_6V_US                      0x1C
#define HBRIDGE14_S_SR_5_3V_US                      0x18
#define HBRIDGE14_S_SR_7_9V_US                      0x14
#define HBRIDGE14_S_SR_10_8V_US                     0x10
#define HBRIDGE14_S_SR_13_V_US                      0x0C
#define HBRIDGE14_S_SR_18_3V_US                     0x08
#define HBRIDGE14_S_SR_34_V_US                      0x04
#define HBRIDGE14_S_SR_53_2V_US                     0x00
#define HBRIDGE14_MODE_DISABLED                     0x03
#define HBRIDGE14_MODE_INDEPENDENT                  0x02
#define HBRIDGE14_MODE_PWM                          0x01
#define HBRIDGE14_MODE_PH_EN                        0x00

/**
 * @brief H-Bridge 14 IC2 Control Register setting.
 * @details Specified setting for IC2 Control Register selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_ITRIP_REP                         0x80
#define HBRIDGE14_TSD_MODE_AUTO                     0x40
#define HBRIDGE14_OTW_REP                           0x20
#define HBRIDGE14_DIS_CPUV                          0x10
#define HBRIDGE14_OCP_TRETRY_4_MS                   0x0C
#define HBRIDGE14_OCP_TRETRY_2_MS                   0x08
#define HBRIDGE14_OCP_TRETRY_1_MS                   0x04
#define HBRIDGE14_OCP_TRETRY_500_NS                 0x00
#define HBRIDGE14_OCP_MODE_NOT_REPORT               0x03
#define HBRIDGE14_OCP_MODE_REPORT                   0x02
#define HBRIDGE14_OCP_MODE_RETRING                  0x01
#define HBRIDGE14_OCP_MODE_LATCHED                  0x00

/**
 * @brief H-Bridge 14 IC3 Control Register setting.
 * @details Specified setting for IC3 Control Register selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_CLR_FLT                           0x80
#define HBRIDGE14_LOCK_REG                          0x30
#define HBRIDGE14_UNLOCK_REG                        0x40
#define HBRIDGE14_OUT1_DIS                          0x08
#define HBRIDGE14_OUT2_DIS                          0x04
#define HBRIDGE14_EN_IN1                            0x02
#define HBRIDGE14_PH_IN2                            0x01

/**
 * @brief H-Bridge 14 IC4 Control Register setting.
 * @details Specified setting for IC4 Control Register selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_EN_OLP                            0x40
#define HBRIDGE14_OLP_DLY_300_US                    0x00
#define HBRIDGE14_OLP_DLY_1_2_MS                    0x20
#define HBRIDGE14_EN_OLA                            0x10
#define HBRIDGE14_ITRIP_LVL_7_A                     0x0C
#define HBRIDGE14_ITRIP_LVL_6_5_A                   0x08
#define HBRIDGE14_ITRIP_LVL_5_4_A                   0x04
#define HBRIDGE14_ITRIP_LVL_4_A                     0x00
#define HBRIDGE14_DIS_ITRIP_OUT1_OUT2               0x03
#define HBRIDGE14_DIS_ITRIP_OUT2                    0x02
#define HBRIDGE14_DIS_ITRIP_OUT1                    0x01
#define HBRIDGE14_DIS_ITRIP                         0x00

/**
 * @brief H-Bridge 14 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 14 Click driver.
 */
#define HBRIDGE14_DEVICE_ADDRESS_A1A0_00            0x70
#define HBRIDGE14_DEVICE_ADDRESS_A1A0_01            0x71
#define HBRIDGE14_DEVICE_ADDRESS_A1A0_10            0x72
#define HBRIDGE14_DEVICE_ADDRESS_A1A0_11            0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge14_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE14_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE14_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge14_set

/**
 * @defgroup hbridge14_map H-Bridge 14 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 14 Click driver.
 */

/**
 * @addtogroup hbridge14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 14 Click to the selected MikroBUS.
 */
#define HBRIDGE14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in2  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge14_map
/*! @} */ // hbridge14

/**
 * @brief H-Bridge 14 Click context object.
 * @details Context object definition of H-Bridge 14 Click driver.
 */
typedef struct hbridge14_s
{
    digital_out_t in2;          /**< Enable output 2 pin. */
    digital_out_t rst;          /**< Reset port expander pin. */
    digital_out_t in1;          /**< Enable output 1 pin. */

    digital_in_t int_pin;       /**< Interrupt pin. */

    i2c_master_t i2c;           /**< I2C driver object. */
    spi_master_t spi;           /**< SPI driver object. */

    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} hbridge14_t;

/**
 * @brief H-Bridge 14 Click configuration object.
 * @details Configuration object definition of H-Bridge 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t in2;             /**< Enable output 2 pin. */
    pin_name_t rst;             /**< Reset port expander pin. */
    pin_name_t in1;             /**< Enable output 1 pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hbridge14_cfg_t;

/**
 * @brief H-Bridge 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE14_OK = 0,
    HBRIDGE14_ERROR = -1

} hbridge14_return_value_t;

/*!
 * @addtogroup hbridge14 H-Bridge 14 Click Driver
 * @brief API for configuring and manipulating H-Bridge 14 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge14_cfg_setup ( hbridge14_cfg_t *cfg );

/**
 * @brief H-Bridge 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_init ( hbridge14_t *ctx, hbridge14_cfg_t *cfg );

/**
 * @brief H-Bridge 14 default configuration function.
 * @details This function executes a default configuration of H-Bridge 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge14_default_cfg ( hbridge14_t *ctx );

/**
 * @brief H-Bridge 14 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_generic_write ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief H-Bridge 14 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_generic_read ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief H-Bridge 14 set IN1 pin function.
 * @details This function is used to set state of the IN1 pin.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void hbridge14_set_in1_pin ( hbridge14_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 14 set RST pin function.
 * @details This function is used to set state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void hbridge14_set_rst_pin ( hbridge14_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 14 get IP pin function.
 * @details This function is used to get state of the IP pin.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @return State of the IP pin.
 * @note None.
 */
uint8_t hbridge14_get_ip_pin ( hbridge14_t *ctx );

/**
 * @brief H-Bridge 14 get INT pin function.
 * @details This function is used to get state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t hbridge14_get_int_pin ( hbridge14_t *ctx );

/**
 * @brief H-Bridge 14 data register writing function.
 * @details This function writes a data byte into
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_register_write ( hbridge14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief H-Bridge 14 data register reading function.
 * @details This function reads a data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_register_read ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 14 port ecpander write register function.
 * @details This function writes a data byte into
 * the selected register of the port expander.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_port_expander_write ( hbridge14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief H-Bridge 14 port ecpander read register function.
 * @details This function reads a data byte from
 * the selected register of the port expander.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_port_expander_read ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 14 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_set_pins ( hbridge14_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief H-Bridge 14 control disable function.
 * @details This function sets the state of the DIS pin, enabling or disabling outputs.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] dis_state : State of the DIS pin.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_disable_state ( hbridge14_t *ctx, uint8_t dis_state );

/**
 * @brief H-Bridge 14 control sleep function.
 * @details This function sets the state of the SLP pin, enabling or disabling sleep mode.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] sleep_state : State of the SLP pin.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_sleep_state ( hbridge14_t *ctx, uint8_t sleep_state );

/**
 * @brief H-Bridge 14 drive motor function.
 * @details This function sets motor driver into the selected state.
 * @param[in] ctx : Click context object.
 * See #hbridge14_t object definition for detailed explanation.
 * @param[in] state : State of the driver.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge14_drive_motor ( hbridge14_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE14_H

/*! @} */ // hbridge14

// ------------------------------------------------------------------------ END

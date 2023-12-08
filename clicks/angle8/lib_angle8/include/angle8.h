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
 * @file angle8.h
 * @brief This file contains API for Angle 8 Click Driver.
 */

#ifndef ANGLE8_H
#define ANGLE8_H

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

/*!
 * @addtogroup angle8 Angle 8 Click Driver
 * @brief API for configuring and manipulating Angle 8 Click driver.
 * @{
 */

/**
 * @defgroup angle8_reg Angle 8 Registers List
 * @brief List of registers of Angle 8 Click driver.
 */

/**
 * @addtogroup angle8_reg
 * @{
 */

/**
 * @brief Angle 8 Register List.
 * @details Specified Register List of Angle 8 Click driver.
 */
#define ANGLE8_REG_ZERO_SETTING_LSB             0x00
#define ANGLE8_REG_ZERO_SETTING_MSB             0x01
#define ANGLE8_REG_BIAS_CURRENT_TIMING          0x02
#define ANGLE8_REG_ENABLE_TRIMMING              0x03
#define ANGLE8_REG_CYCLE_TIME_LSB               0x04
#define ANGLE8_REG_CYCLE_TIME_MSB               0x05
#define ANGLE8_REG_MAGNETIC_FIELD_CONFIG        0x06
#define ANGLE8_REG_ND_CONFIG                    0x07
#define ANGLE8_REG_ASC_MODE_THRESHOLD           0x08
#define ANGLE8_REG_ROTATION_DIRECTION           0x09
#define ANGLE8_REG_ASC_MODE_REFERENCE           0x0A
#define ANGLE8_REG_ASC_MODE_CONFIG              0x0B
#define ANGLE8_REG_FILTER_WINDOW                0x0E
#define ANGLE8_REG_ERROR_FLAGS                  0x1A
#define ANGLE8_REG_ALARM_FLAGS                  0x1B

/**
 * @brief Angle 8 Command List.
 * @details Specified Command List of Angle 8 Click driver.
 */
#define ANGLE8_CMD_READ_ANGLE                   0x00
#define ANGLE8_CMD_READ_REGISTER                0x40
#define ANGLE8_CMD_WRITE_REGISTER               0x80
#define ANGLE8_CMD_STORE_SINGLE_REGISTER        0xE0
#define ANGLE8_CMD_STORE_ALL_REGISTERS          0xC0
#define ANGLE8_CMD_RESTORE_ALL_REGISTERS        0xA0
#define ANGLE8_CMD_CLEAR_ERROR_FLAGS            0x20

/*! @} */ // angle8_reg

/**
 * @defgroup angle8_set Angle 8 Registers Settings
 * @brief Settings for registers of Angle 8 Click driver.
 */

/**
 * @addtogroup angle8_set
 * @{
 */

/**
 * @brief Angle 8 Rotation Direction register setting.
 * @details Specified setting for Rotation Direction register of Angle 8 Click driver.
 */
#define ANGLE8_ROTATION_DIRECTION_CW            0x00
#define ANGLE8_ROTATION_DIRECTION_CCW           0x80

/**
 * @brief Angle 8 Angle calculation values.
 * @details Specified Angle calculation values of Angle 8 Click driver.
 */
#define ANGLE8_RESOLUTION                       0xFFFF
#define ANGLE8_FULL_CIRCLE                      360.0

/**
 * @brief Angle 8 Cycle time range values.
 * @details Specified Cycle time range values of Angle 8 Click driver.
 */
#define ANGLE8_CYCLE_TIME_MAX                   6553.5
#define ANGLE8_CYCLE_TIME_100MS                 100.0
#define ANGLE8_CYCLE_TIME_MIN                   0.2

/**
 * @brief Angle 8 Rotation Direction register setting.
 * @details Specified setting for Rotation Direction register of Angle 8 Click driver.
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b angle8_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ANGLE8_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ANGLE8_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // angle8_set

/**
 * @defgroup angle8_map Angle 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Angle 8 Click driver.
 */

/**
 * @addtogroup angle8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Angle 8 Click to the selected MikroBUS.
 */
#define ANGLE8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.nd   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dv   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.mgl  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // angle8_map
/*! @} */ // angle8

/**
 * @brief Angle 8 Click context object.
 * @details Context object definition of Angle 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */

    // Input pins
    digital_in_t  nd;           /**< New data ready pin. */
    digital_in_t  dv;           /**< Data valid pin. */
    digital_in_t  mgl;          /**< MGL alarm flag pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} angle8_t;

/**
 * @brief Angle 8 Click configuration object.
 * @details Configuration object definition of Angle 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  nd;             /**< New data ready pin. */
    pin_name_t  dv;             /**< Data valid pin. */
    pin_name_t  en;             /**< Enable pin. */
    pin_name_t  mgl;            /**< MGL alarm flag pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} angle8_cfg_t;

/**
 * @brief Angle 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANGLE8_OK = 0,
    ANGLE8_ERROR = -1

} angle8_return_value_t;

/*!
 * @addtogroup angle8 Angle 8 Click Driver
 * @brief API for configuring and manipulating Angle 8 Click driver.
 * @{
 */

/**
 * @brief Angle 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #angle8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void angle8_cfg_setup ( angle8_cfg_t *cfg );

/**
 * @brief Angle 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #angle8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_init ( angle8_t *ctx, angle8_cfg_t *cfg );

/**
 * @brief Angle 8 default configuration function.
 * @details This function executes a default configuration of Angle 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t angle8_default_cfg ( angle8_t *ctx );

/**
 * @brief Angle 8 write register function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_write_register ( angle8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Angle 8 read register function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_read_register ( angle8_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Angle 8 read angle function.
 * @details This function reads raw angle data and converts it to degrees.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_read_angle ( angle8_t *ctx, float *angle );

/**
 * @brief Angle 8 store all registers function.
 * @details This function executes the store all registers to NVM command.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_store_all_registers ( angle8_t *ctx );

/**
 * @brief Angle 8 store single register function.
 * @details This function executes the store single register to NVM command.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_store_single_register ( angle8_t *ctx, uint8_t reg );

/**
 * @brief Angle 8 clear error flags function.
 * @details This function executes the clear error flags command.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_clear_error_flags ( angle8_t *ctx );

/**
 * @brief Angle 8 enable device function.
 * @details This function enables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void angle8_enable_device ( angle8_t *ctx );

/**
 * @brief Angle 8 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void angle8_disable_device ( angle8_t *ctx );

/**
 * @brief Angle 8 get nd pin function.
 * @details This function returns the new data ready (ND) pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle8_get_nd_pin ( angle8_t *ctx );

/**
 * @brief Angle 8 get dv pin function.
 * @details This function returns the data valid (DV) pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle8_get_dv_pin ( angle8_t *ctx );

/**
 * @brief Angle 8 get mgl pin function.
 * @details This function returns the MGL alarm flag (MGL) pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle8_get_mgl_pin ( angle8_t *ctx );

/**
 * @brief Angle 8 set cycle time function.
 * @details This function sets the sensor cycle time (measurement rate) in milliseconds.
 * @param[in] ctx : Click context object.
 * See #angle8_t object definition for detailed explanation.
 * @param[in] time_ms : Cycle time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle8_set_cycle_time ( angle8_t *ctx, float time_ms );

#ifdef __cplusplus
}
#endif
#endif // ANGLE8_H

/*! @} */ // angle8

// ------------------------------------------------------------------------ END

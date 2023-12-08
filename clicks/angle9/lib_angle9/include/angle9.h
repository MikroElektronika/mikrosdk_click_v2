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
 * @file angle9.h
 * @brief This file contains API for Angle 9 Click Driver.
 */

#ifndef ANGLE9_H
#define ANGLE9_H

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
 * @addtogroup angle9 Angle 9 Click Driver
 * @brief API for configuring and manipulating Angle 9 Click driver.
 * @{
 */

/**
 * @defgroup angle9_reg Angle 9 Registers List
 * @brief List of registers of Angle 9 Click driver.
 */

/**
 * @addtogroup angle9_reg
 * @{
 */

/**
 * @brief Angle 9 registers list.
 * @details Specified registers list of Angle 9 Click driver.
 */
#define ANGLE9_REG_EWA                      0x02
#define ANGLE9_REG_EWDH                     0x04
#define ANGLE9_REG_EWDL                     0x06
#define ANGLE9_REG_EWCS                     0x08
#define ANGLE9_REG_ERA                      0x0A
#define ANGLE9_REG_ERCS                     0x0C
#define ANGLE9_REG_ERDH                     0x0E
#define ANGLE9_REG_ERDL                     0x10
#define ANGLE9_REG_CTRL                     0x1E
#define ANGLE9_REG_ANG                      0x20
#define ANGLE9_REG_STA                      0x22
#define ANGLE9_REG_ERR                      0x24
#define ANGLE9_REG_WARN                     0x26
#define ANGLE9_REG_TSEN                     0x28
#define ANGLE9_REG_FIELD                    0x2A
#define ANGLE9_REG_HANG                     0x30
#define ANGLE9_REG_ANG15                    0x32
#define ANGLE9_REG_ZANG                     0x34
#define ANGLE9_REG_KEY                      0x3C

/*! @} */ // angle9_reg

/**
 * @defgroup angle9_set Angle 9 Registers Settings
 * @brief Settings for registers of Angle 9 Click driver.
 */

/**
 * @addtogroup angle9_set
 * @{
 */

/**
 * @brief Angle 9 SPI frame setting.
 * @details Specified SPI frame setting of Angle 9 Click driver.
 */
#define ANGLE9_WRITE_BIT                    0x40            

/**
 * @brief Angle 9 calculation values.
 * @details Specified calculation values of Angle 9 Click driver.
 */
#define ANGLE9_DATA_RESOLUTION              0x0FFFu
#define ANGLE9_FULL_CIRCLE                  360.0f
#define ANGLE9_TEMP_RESOLUTION              8.0f
#define ANGLE9_TEMP_OFFSET                  25.0f

/**
 * @brief Angle 9 ODD parity flag.
 * @details Specified flag for ODD parity of Angle 9 Click driver.
 */
#define ANGLE9_ODD_PARITY                   0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b angle9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ANGLE9_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define ANGLE9_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // angle9_set

/**
 * @defgroup angle9_map Angle 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Angle 9 Click driver.
 */

/**
 * @addtogroup angle9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Angle 9 Click to the selected MikroBUS.
 */
#define ANGLE9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // angle9_map
/*! @} */ // angle9

/**
 * @brief Angle 9 Click context object.
 * @details Context object definition of Angle 9 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t pwm;           /**< PWM input pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} angle9_t;

/**
 * @brief Angle 9 Click configuration object.
 * @details Configuration object definition of Angle 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t pwm;             /**< PWM input pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} angle9_cfg_t;

/**
 * @brief Angle 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANGLE9_OK = 0,
    ANGLE9_ERROR = -1

} angle9_return_value_t;

/*!
 * @addtogroup angle9 Angle 9 Click Driver
 * @brief API for configuring and manipulating Angle 9 Click driver.
 * @{
 */

/**
 * @brief Angle 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #angle9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void angle9_cfg_setup ( angle9_cfg_t *cfg );

/**
 * @brief Angle 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #angle9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle9_init ( angle9_t *ctx, angle9_cfg_t *cfg );

/**
 * @brief Angle 9 write register function.
 * @details This function writes two bytes of data to the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle9_write_register ( angle9_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Angle 9 read register function.
 * @details This function reads two bytes of data from the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle9_read_register ( angle9_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Angle 9 get pwm pin function.
 * @details This function returns the PWM pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle9_get_pwm_pin ( angle9_t *ctx );

/**
 * @brief Angle 9 read angle function.
 * @details This function reads the magnetic angular position in degrees.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[out] angle : Magnetic angular position in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle9_read_angle ( angle9_t *ctx, float *angle );

/**
 * @brief Angle 9 read temperature function.
 * @details This function reads the sensor internal temperature in degrees celsius.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[out] temperature : Sensor internal temperature in degrees celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle9_read_temperature ( angle9_t *ctx, float *temperature );

/**
 * @brief Angle 9 read field strength function.
 * @details This function reads the magnetic field strength in gauss.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[out] field_str : Magnetic field strength in gauss.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle9_read_field_strength ( angle9_t *ctx, uint16_t *field_str );

#ifdef __cplusplus
}
#endif
#endif // ANGLE9_H

/*! @} */ // angle9

// ------------------------------------------------------------------------ END

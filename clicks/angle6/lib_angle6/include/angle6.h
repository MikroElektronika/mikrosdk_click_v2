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
 * @file angle6.h
 * @brief This file contains API for Angle 6 Click Driver.
 */

#ifndef ANGLE6_H
#define ANGLE6_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup angle6 Angle 6 Click Driver
 * @brief API for configuring and manipulating Angle 6 Click driver.
 * @{
 */

/**
 * @defgroup angle6_reg Angle 6 Registers List
 * @brief List of registers of Angle 6 Click driver.
 */

/**
 * @addtogroup angle6_reg
 * @{
 */

/**
 * @brief Angle 6 Register List.
 * @details Specified Register List of Angle 6 Click driver.
 */
#define ANGLE6_REG_ZERO_SETTING_LSB             0x00
#define ANGLE6_REG_ZERO_SETTING_MSB             0x01
#define ANGLE6_REG_BIAS_CURRENT_TIMING          0x02
#define ANGLE6_REG_ENABLE_TRIMMING              0x03
#define ANGLE6_REG_ABZ_SETTING_LSB              0x04
#define ANGLE6_REG_ABZ_SETTING_MSB              0x05
#define ANGLE6_REG_MAGNETIC_FIELD_CONFIG        0x06
#define ANGLE6_REG_ROTATION_DIRECTION           0x09
#define ANGLE6_REG_ALARM_FLAGS                  0x1B

/**
 * @brief Angle 6 Command List.
 * @details Specified Command List of Angle 6 Click driver.
 */
#define ANGLE6_CMD_READ_ANGLE                   0x00
#define ANGLE6_CMD_READ_REGISTER                0x40
#define ANGLE6_CMD_WRITE_REGISTER               0x80

/*! @} */ // angle6_reg

/**
 * @defgroup angle6_set Angle 6 Registers Settings
 * @brief Settings for registers of Angle 6 Click driver.
 */

/**
 * @addtogroup angle6_set
 * @{
 */

/**
 * @brief Angle 6 Rotation Direction register setting.
 * @details Specified setting for Rotation Direction register of Angle 6 Click driver.
 */
#define ANGLE6_ROTATION_DIRECTION_CW            0x00
#define ANGLE6_ROTATION_DIRECTION_CCW           0x80

/**
 * @brief Angle 6 Angle calculation values.
 * @details Specified Angle calculation values of Angle 6 Click driver.
 */
#define ANGLE6_RESOLUTION                       0xFFFF
#define ANGLE6_FULL_CIRCLE                      360.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b angle6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ANGLE6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ANGLE6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // angle6_set

/**
 * @defgroup angle6_map Angle 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Angle 6 Click driver.
 */

/**
 * @addtogroup angle6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Angle 6 Click to the selected MikroBUS.
 */
#define ANGLE6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.mgh = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.mgl = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // angle6_map
/*! @} */ // angle6

/**
 * @brief Angle 6 Click context object.
 * @details Context object definition of Angle 6 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  mgh;          /**< Inticating field strength above MGHT level. */
    digital_in_t  pwm;          /**< PWM absolute output. */
    digital_in_t  mgl;          /**< Indicating field strength below MGHT level. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} angle6_t;

/**
 * @brief Angle 6 Click configuration object.
 * @details Configuration object definition of Angle 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  mgh;                                    /**< Inticating field strength above MGHT level. */
    pin_name_t  pwm;                                    /**< PWM absolute output. */
    pin_name_t  mgl;                                    /**< Indicating field strength below MGHT level. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} angle6_cfg_t;

/**
 * @brief Angle 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANGLE6_OK = 0,
    ANGLE6_ERROR = -1

} angle6_return_value_t;

/*!
 * @addtogroup angle6 Angle 6 Click Driver
 * @brief API for configuring and manipulating Angle 6 Click driver.
 * @{
 */

/**
 * @brief Angle 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #angle6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void angle6_cfg_setup ( angle6_cfg_t *cfg );

/**
 * @brief Angle 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #angle6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle6_init ( angle6_t *ctx, angle6_cfg_t *cfg );

/**
 * @brief Angle 6 default configuration function.
 * @details This function executes a default configuration of Angle 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t angle6_default_cfg ( angle6_t *ctx );

/**
 * @brief Angle 6 write register function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle6_write_register ( angle6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Angle 6 read register function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle6_read_register ( angle6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Angle 6 read angle function.
 * @details This function reads raw angle data and converts it to degrees.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle6_read_angle ( angle6_t *ctx, float *angle );

/**
 * @brief Angle 6 get pwm pin function.
 * @details This function returns the PWM absolute output pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle6_get_pwm_pin ( angle6_t *ctx );

/**
 * @brief Angle 6 get mgh pin function.
 * @details This function returns the MGH alarm flag (MGH) pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle6_get_mgh_pin ( angle6_t *ctx );

/**
 * @brief Angle 6 get mgl pin function.
 * @details This function returns the MGL alarm flag (MGL) pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle6_get_mgl_pin ( angle6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ANGLE6_H

/*! @} */ // angle6

// ------------------------------------------------------------------------ END

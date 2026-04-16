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
 * @file angle11.h
 * @brief This file contains API for Angle 11 Click Driver.
 */

#ifndef ANGLE11_H
#define ANGLE11_H

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
 * @addtogroup angle11 Angle 11 Click Driver
 * @brief API for configuring and manipulating Angle 11 Click driver.
 * @{
 */

/**
 * @defgroup angle11_reg Angle 11 Registers List
 * @brief List of registers of Angle 11 Click driver.
 */

/**
 * @addtogroup angle11_reg
 * @{
 */

/**
 * @brief Angle 11 registers list.
 * @details Specified registers list of Angle 11 Click driver.
 */
#define ANGLE11_REG_EWA                         0x02
#define ANGLE11_REG_EWDH                        0x04
#define ANGLE11_REG_EWDL                        0x06
#define ANGLE11_REG_EWCS                        0x08
#define ANGLE11_REG_ERA                         0x0A
#define ANGLE11_REG_ERCS                        0x0C
#define ANGLE11_REG_ERDH                        0x0E
#define ANGLE11_REG_ERDL                        0x10
#define ANGLE11_REG_CTRL                        0x1E
#define ANGLE11_REG_ANG                         0x20
#define ANGLE11_REG_STA                         0x22
#define ANGLE11_REG_ERR                         0x24
#define ANGLE11_REG_WARN                        0x26
#define ANGLE11_REG_TSEN                        0x28
#define ANGLE11_REG_FIELD                       0x2A
#define ANGLE11_REG_TURNS                       0x2C
#define ANGLE11_REG_HANG                        0x30
#define ANGLE11_REG_ANG15                       0x32
#define ANGLE11_REG_ZANG                        0x34
#define ANGLE11_REG_IKEY                        0x3C

/*! @} */ // angle11_reg

/**
 * @defgroup angle11_set Angle 11 Registers Settings
 * @brief Settings for registers of Angle 11 Click driver.
 */

/**
 * @addtogroup angle11_set
 * @{
 */

/**
 * @brief Angle 11 SPI frame setting.
 * @details Specified SPI frame setting of Angle 11 Click driver.
 */
#define ANGLE11_WRITE_BIT                       0x40            

/**
 * @brief Angle 11 calculation values.
 * @details Specified calculation values of Angle 11 Click driver.
 */
#define ANGLE11_DATA_RESOLUTION                 0x0FFFu
#define ANGLE11_FULL_CIRCLE                     360.0f
#define ANGLE11_TEMP_RESOLUTION                 8.0f
#define ANGLE11_TEMP_OFFSET                     25.0f

/**
 * @brief Angle 11 ODD parity flag.
 * @details Specified flag for ODD parity of Angle 11 Click driver.
 */
#define ANGLE11_ODD_PARITY                      0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b angle11_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ANGLE11_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define ANGLE11_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // angle11_set

/**
 * @defgroup angle11_map Angle 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Angle 11 Click driver.
 */

/**
 * @addtogroup angle11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Angle 11 Click to the selected MikroBUS.
 */
#define ANGLE11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // angle11_map
/*! @} */ // angle11

/**
 * @brief Angle 11 Click context object.
 * @details Context object definition of Angle 11 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t pwm;           /**< PWM input pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} angle11_t;

/**
 * @brief Angle 11 Click configuration object.
 * @details Configuration object definition of Angle 11 Click driver.
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

} angle11_cfg_t;

/**
 * @brief Angle 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANGLE11_OK = 0,
    ANGLE11_ERROR = -1

} angle11_return_value_t;

/*!
 * @addtogroup angle11 Angle 11 Click Driver
 * @brief API for configuring and manipulating Angle 11 Click driver.
 * @{
 */

/**
 * @brief Angle 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #angle11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void angle11_cfg_setup ( angle11_cfg_t *cfg );

/**
 * @brief Angle 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #angle11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle11_init ( angle11_t *ctx, angle11_cfg_t *cfg );

/**
 * @brief Angle 11 write register function.
 * @details This function writes two bytes of data to the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle11_write_reg ( angle11_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Angle 11 read register function.
 * @details This function reads two bytes of data from the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle11_read_reg ( angle11_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Angle 11 get pwm pin function.
 * @details This function returns the PWM pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle11_get_pwm_pin ( angle11_t *ctx );

/**
 * @brief Angle 11 read angle function.
 * @details This function reads the magnetic angular position in degrees.
 * @param[in] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @param[out] angle : Magnetic angular position in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle11_read_angle ( angle11_t *ctx, float *angle );

/**
 * @brief Angle 11 read temperature function.
 * @details This function reads the sensor internal temperature in degrees celsius.
 * @param[in] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @param[out] temperature : Sensor internal temperature in degrees celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle11_read_temperature ( angle11_t *ctx, float *temperature );

/**
 * @brief Angle 11 read field strength function.
 * @details This function reads the magnetic field strength in gauss.
 * @param[in] ctx : Click context object.
 * See #angle11_t object definition for detailed explanation.
 * @param[out] field_str : Magnetic field strength in gauss.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle11_read_field_strength ( angle11_t *ctx, uint16_t *field_str );

#ifdef __cplusplus
}
#endif
#endif // ANGLE11_H

/*! @} */ // angle11

// ------------------------------------------------------------------------ END

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
 * @file magneto14.h
 * @brief This file contains API for Magneto 14 Click Driver.
 */

#ifndef MAGNETO14_H
#define MAGNETO14_H

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
 * @addtogroup magneto14 Magneto 14 Click Driver
 * @brief API for configuring and manipulating Magneto 14 Click driver.
 * @{
 */

/**
 * @defgroup magneto14_reg Magneto 14 Registers List
 * @brief List of registers of Magneto 14 Click driver.
 */

/**
 * @addtogroup magneto14_reg
 * @{
 */

/**
 * @brief Magneto 14 description register.
 * @details Specified register for description of Magneto 14 Click driver.
 */
#define MAGNETO14_REG_ZERO_0                0x00
#define MAGNETO14_REG_ZERO_1                0x01
#define MAGNETO14_REG_BCT                   0x02
#define MAGNETO14_REG_ET_YX                 0x03
#define MAGNETO14_REG_PPT_ILIP              0x04
#define MAGNETO14_REG_PPT                   0x05
#define MAGNETO14_REG_MG_LT_HT_MG           0x06
#define MAGNETO14_REG_RD                    0x09
#define MAGNETO14_REG_FW                    0x0E
#define MAGNETO14_REG_HYS                   0x10
#define MAGNETO14_REG_M_GH_GL               0x1B

/*! @} */ // magneto14_reg

/**
 * @addtogroup magneto14_cmd
 * @{
 */

/**
 * @brief Magneto 14 description commands.
 * @details Specified commands of Magneto 14 Click driver.
 */
#define MAGNETO14_CMD_READ_ANGLE            0x00
#define MAGNETO14_CMD_READ_REGISTER         0x02
#define MAGNETO14_CMD_WRITE_REGISTER        0x04
#define MAGNETO14_CMD_RESTORE_ALL_NVM       0x05
#define MAGNETO14_CMD_STORE_ALL_NVM         0x06
#define MAGNETO14_CMD_STORE_SINGLE_NVM      0x07

/*! @} */ // magneto14_cmd

/**
 * @defgroup magneto14_set Magneto 14 Registers Settings
 * @brief Settings for registers of Magneto 14 Click driver.
 */

/**
 * @addtogroup magneto14_set
 * @{
 */

/**
 * @brief Magneto 14 description of the command and register bit masks.
 * @details Specified command and register bit masks of Magneto 14 Click driver.
 */
#define MAGNETO14_CMD_BIT_MASK              0x07
#define MAGNETO14_REG_BIT_MASK              0x1F

/**
 * @brief Magneto 14 description of trimming settings.
 * @details Specified trimming settings of Magneto 14 Click driver.
 */
#define MAGNETO14_TRIMMING_X_DIS            0x00
#define MAGNETO14_TRIMMING_X_EN             0x01
#define MAGNETO14_TRIMMING_Y_DIS            0x00
#define MAGNETO14_TRIMMING_Y_EN             0x02

/**
 * @brief Magneto 14 description of magnetic field threshold settings.
 * @details Specified magnetic field threshold settings of Magneto 14 Click driver.
 */
#define MAGNETO14_MG_LT_LVL_0               0x00
#define MAGNETO14_MG_LT_LVL_1               0x20
#define MAGNETO14_MG_LT_LVL_2               0x40
#define MAGNETO14_MG_LT_LVL_3               0x60
#define MAGNETO14_MG_LT_LVL_4               0x80
#define MAGNETO14_MG_LT_LVL_5               0xA0
#define MAGNETO14_MG_LT_LVL_6               0xC0
#define MAGNETO14_MG_LT_LVL_7               0xE0
#define MAGNETO14_MG_HT_LVL_0               0x00
#define MAGNETO14_MG_HT_LVL_1               0x04
#define MAGNETO14_MG_HT_LVL_2               0x08
#define MAGNETO14_MG_HT_LVL_3               0x0C
#define MAGNETO14_MG_HT_LVL_4               0x10
#define MAGNETO14_MG_HT_LVL_5               0x14
#define MAGNETO14_MG_HT_LVL_6               0x18
#define MAGNETO14_MG_HT_LVL_7               0x1C
#define MAGNETO14_MG_BIT_MASK               0xFC

/**
 * @brief Magneto 14 description of field strength level.
 * @details Specified field strength level of Magneto 14 Click driver.
 */
#define MAGNETO14_MGH_ST_OK                 0x00
#define MAGNETO14_FLD_ST_OK                 0x00
#define MAGNETO14_FLD_ST_MGL                0x01
#define MAGNETO14_FLD_ST_MGH                0x02
#define MAGNETO14_FLD_ST_BIT_MASK           0x03

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b magneto14_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MAGNETO14_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define MAGNETO14_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // magneto14_set

/**
 * @defgroup magneto14_map Magneto 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 14 Click driver.
 */

/**
 * @addtogroup magneto14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 14 Click to the selected MikroBUS.
 */
#define MAGNETO14_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.mgh = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // magneto14_map
/*! @} */ // magneto14

/**
 * @brief Magneto 14 Click context object.
 * @details Context object definition of Magneto 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwm;    /**< Pulse-width modulation pin. */

    // Input pins
    digital_in_t mgh;     /**< Field strength above the MGHT level. */

    // Modules
    spi_master_t spi;     /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} magneto14_t;

/**
 * @brief Magneto 14 Click configuration object.
 * @details Configuration object definition of Magneto 14 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t pwm;    /**< Pulse-width modulation pin. */
    pin_name_t mgh;    /**< Field strength above the MGHT level. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} magneto14_cfg_t;

/**
 * @brief Magneto 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO14_OK = 0,
    MAGNETO14_ERROR = -1

} magneto14_return_value_t;

/*!
 * @addtogroup magneto14 Magneto 14 Click Driver
 * @brief API for configuring and manipulating Magneto 14 Click driver.
 * @{
 */

/**
 * @brief Magneto 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto14_cfg_setup ( magneto14_cfg_t *cfg );

/**
 * @brief Magneto 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_init ( magneto14_t *ctx, magneto14_cfg_t *cfg );

/**
 * @brief Magneto 14 default configuration function.
 * @details This function executes a default configuration of Magneto 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneto14_default_cfg ( magneto14_t *ctx );

/**
 * @brief Magneto 14 data writing function.
 * @details This function writes a data byte to the selected register  
 * of the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_write_reg ( magneto14_t *ctx, uint8_t cmd, uint8_t reg, uint8_t data_in );

/**
 * @brief Magneto 14 data reading function.
 * @details This function reads a data byte from the selected register 
 * of the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_read_reg ( magneto14_t *ctx, uint8_t cmd, uint8_t reg, uint8_t *data_out );

/**
 * @brief Magneto 14 gets the angle raw data function.
 * @details This function reads a 16-bit angle raw data
 * of the MagAlpha MA735, Contactless Digital Angle Sensor
 * on the Magneto 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[out] raw_data : Angle raw data [0-65535].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_get_angle_raw_data ( magneto14_t *ctx, uint16_t *raw_data );

/**
 * @brief Magneto 14 gets the angular position function.
 * @details This function reads an angular position in degrees
 * of the MagAlpha MA735, Contactless Digital Angle Sensor
 * on the Magneto 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[out] angle : Angle data, degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_get_angle ( magneto14_t *ctx, float *angle );

/**
 * @brief Magneto 14 sets the magnetic field threshold function.
 * @details This function sets the magnetic field's high and low thresholds
 * of the MagAlpha MA735, Contactless Digital Angle Sensor
 * on the Magneto 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[in] mglt : Sets the field strength low threshold.
 * @param[in] mght : Sets the field strength high threshold.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_set_mag_field_thd ( magneto14_t *ctx, uint8_t mglt, uint8_t mght );

/**
 * @brief Magneto 14 gets the magnetic field strength function.
 * @details This function reads a magnetic field strength detection
 * of the MagAlpha MA735, Contactless Digital Angle Sensor
 * on the Magneto 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[out] field_strength : 
 *         @li @c  0 - Magnetic field strength OK,
 *         @li @c  1 - Magnetic field strength below the MGLT level,
 *         @li @c  2 - Magnetic field strength above the MGHT level.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto14_get_field_strength ( magneto14_t *ctx, uint8_t *field_strength );

/**
 * @brief Magneto 14 set PWM pin function.
 * @details This function sets the PWM pin logic state
 * of the MagAlpha MA735, Contactless Digital Angle Sensor
 * on the Magneto 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @param[in] pwm_state : Logic state of the PWM pin.
 * @return Nothing.
 * @note None.
 */
void magneto14_set_pwm_pin ( magneto14_t *ctx, uint8_t pwm_state );

/**
 * @brief Magneto 14 gets the MGH function.
 * @details This function gets states of the MGH ( INT ) pin 
 * to indicate the magnetic field strength
 * of the MagAlpha MA735, Contactless Digital Angle Sensor
 * on the Magneto 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto14_t object definition for detailed explanation.
 * @return @li @c 0 - MGHT level OK,
 *         @li @c 1 - Magnetic field strength above the MGHT level.
 * @note None.
 */
uint8_t magneto14_get_mgh ( magneto14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MAGNETO14_H

/*! @} */ // magneto14

// ------------------------------------------------------------------------ END

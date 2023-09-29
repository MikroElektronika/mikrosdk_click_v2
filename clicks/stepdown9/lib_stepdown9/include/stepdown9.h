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
 * @file stepdown9.h
 * @brief This file contains API for Step Down 9 Click Driver.
 */

#ifndef STEPDOWN9_H
#define STEPDOWN9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup stepdown9 Step Down 9 Click Driver
 * @brief API for configuring and manipulating Step Down 9 Click driver.
 * @{
 */

/**
 * @defgroup stepdown9_set Step Down 9 Registers Settings
 * @brief Settings for registers of Step Down 9 Click driver.
 */

/**
 * @addtogroup stepdown9_set
 * @{
 */

/**
 * @brief Step Down 9 description setting.
 * @details Specified setting for description of Step Down 9 Click driver.
 */
#define STEPDOWN9_VOUT_10V_RESISTANCE           8700 
#define STEPDOWN9_VOUT_9V5_RESISTANCE           11500
#define STEPDOWN9_VOUT_9V_RESISTANCE            11700
#define STEPDOWN9_VOUT_8V5_RESISTANCE           12500
#define STEPDOWN9_VOUT_8V_RESISTANCE            13000
#define STEPDOWN9_VOUT_7V5_RESISTANCE           13700
#define STEPDOWN9_VOUT_7V_RESISTANCE            14700
#define STEPDOWN9_VOUT_6V5_RESISTANCE           15800
#define STEPDOWN9_VOUT_6V_RESISTANCE            17000
#define STEPDOWN9_VOUT_5V5_RESISTANCE           19000
#define STEPDOWN9_VOUT_5V_RESISTANCE            21000 
#define STEPDOWN9_VOUT_4V5_RESISTANCE           23500
#define STEPDOWN9_VOUT_4V_RESISTANCE            27000
#define STEPDOWN9_VOUT_3V5_RESISTANCE           32000
#define STEPDOWN9_VOUT_3V3_RESISTANCE           34000
#define STEPDOWN9_VOUT_3V_RESISTANCE            38000
#define STEPDOWN9_VOUT_2V5_RESISTANCE           50000
#define STEPDOWN9_VOUT_2V_RESISTANCE            70000
#define STEPDOWN9_VOUT_1V6_RESISTANCE           100000 

/**
 * @brief Step Down 9 Vout setting.
 * @details Specified setting for Vout of Step Down 9 Click driver.
 */
#define STEPDOWN9_VOUT_10V                      0x12
#define STEPDOWN9_VOUT_9V5                      0x11
#define STEPDOWN9_VOUT_9V                       0x10
#define STEPDOWN9_VOUT_8V5                      0x0F
#define STEPDOWN9_VOUT_8V                       0x0E
#define STEPDOWN9_VOUT_7V5                      0x0D
#define STEPDOWN9_VOUT_7V                       0x0C
#define STEPDOWN9_VOUT_6V5                      0x0B
#define STEPDOWN9_VOUT_6V                       0x0A
#define STEPDOWN9_VOUT_5V5                      0x09
#define STEPDOWN9_VOUT_5V                       0x08
#define STEPDOWN9_VOUT_4V5                      0x07
#define STEPDOWN9_VOUT_4V                       0x06
#define STEPDOWN9_VOUT_3V5                      0x05
#define STEPDOWN9_VOUT_3V3                      0x04
#define STEPDOWN9_VOUT_3V                       0x03
#define STEPDOWN9_VOUT_2V5                      0x02
#define STEPDOWN9_VOUT_2V                       0x01
#define STEPDOWN9_VOUT_1V6                      0x00

/**
 * @brief Step Down 9 pin state setting.
 * @details Specified setting for pin state of Step Down 9 Click driver.
 */
#define STEPDOWN9_PIN_STATE_HIGH                0x01
#define STEPDOWN9_PIN_STATE_LOW                 0x00

/**
 * @brief Step Down 9 description digital potentiometer wiper data.
 * @details Specified digital potentiometer wiper data 
 * for description of Step Down 9 Click driver.
 */
#define STEPDOWN9_RESISTANCE_MIN                8700
#define STEPDOWN9_FULL_SCALE_RES_100_KOHM       100000
#define STEPDOWN9_WIPER_POS_MAX                 0xFF
#define STEPDOWN9_ROUND_TO_NEAREST_INT          0.5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepdown9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPDOWN9_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define STEPDOWN9_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepdown9_set

/**
 * @defgroup stepdown9_map Step Down 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 9 Click driver.
 */

/**
 * @addtogroup stepdown9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 9 Click to the selected MikroBUS.
 */
#define STEPDOWN9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown9_map
/*! @} */ // stepdown9

/**
 * @brief Step Down 9 Click context object.
 * @details Context object definition of Step Down 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */

    // Input pins
    digital_in_t pg;            /**< Power good pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} stepdown9_t;

/**
 * @brief Step Down 9 Click configuration object.
 * @details Configuration object definition of Step Down 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t en;              /**< Enable pin. */
    pin_name_t pg;              /**< Power good pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} stepdown9_cfg_t;

/**
 * @brief Step Down 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN9_OK = 0,
    STEPDOWN9_ERROR = -1

} stepdown9_return_value_t;

/*!
 * @addtogroup stepdown9 Step Down 9 Click Driver
 * @brief API for configuring and manipulating Step Down 9 Click driver.
 * @{
 */

/**
 * @brief Step Down 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown9_cfg_setup ( stepdown9_cfg_t *cfg );

/**
 * @brief Step Down 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown9_init ( stepdown9_t *ctx, stepdown9_cfg_t *cfg );

/**
 * @brief Step Down 9 default configuration function.
 * @details This function executes a default configuration of Step Down 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepdown9_default_cfg ( stepdown9_t *ctx );

/**
 * @brief Step Down 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown9_generic_write ( stepdown9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Step Down 9 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown9_generic_read ( stepdown9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Step Down 9 set EN pin state function.
 * @details This function sets a EN pin state.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] pin_state : State of the EN pin.
 * @return Nothing.
 * @note None.
 */
void stepdown9_set_en_pin ( stepdown9_t *ctx, uint8_t pin_state );

/**
 * @brief Step Down 9 get PG pin state function.
 * @details This function is used to get state of the PG pin.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown9_t object definition for detailed explanation.
 * @return State of the PG pin.
 * @note None.
 */
uint8_t stepdown9_get_pg_pin ( stepdown9_t *ctx );

/**
 * @brief Step Down 9 set wiper position.
 * @details This function sets a wiper of the potentiometer to the desired position.
 * @param[in] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] wiper_pos : Position of the wiper.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown9_set_wiper_pos ( stepdown9_t *ctx, uint8_t wiper_pos );

/**
 * @brief Step Down 9 set potentiometer resistance.
 * @details This function sets a resistance of the potentiometer to the desired value.
 * @param[in] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] resistance : Desired resistance.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown9_set_resistance ( stepdown9_t *ctx, uint32_t res_ohm );

/**
 * @brief Step Down 9 set output voltage.
 * @details This function sets a predefined output level.
 * @param[in] ctx : Click context object.
 * See #stepdown9_t object definition for detailed explanation.
 * @param[in] voltage : Desired output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown9_set_output ( stepdown9_t *ctx, uint8_t voltage );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN9_H

/*! @} */ // stepdown9

// ------------------------------------------------------------------------ END

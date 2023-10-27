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
 * @file timerrelay.h
 * @brief This file contains API for Timer Relay Click Driver.
 */

#ifndef TIMERRELAY_H
#define TIMERRELAY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup timerrelay Timer Relay Click Driver
 * @brief API for configuring and manipulating Timer Relay Click driver.
 * @{
 */

/**
 * @defgroup timerrelay_set Timer Relay Registers Settings
 * @brief Settings for registers of Timer Relay Click driver.
 */

/**
 * @addtogroup timerrelay_set
 * @{
 */

/**
 * @brief Timer Relay description setting.
 * @details Specified setting for description of Timer Relay Click driver.
 */
#define TIMERRELAY_PIN_STATE_HIGH               0x01
#define TIMERRELAY_PIN_STATE_LOW                0x00

/**
 * @brief Timer Relay calculation setting.
 * @details Specified calculation setting of Timer Relay Click driver.
 */
#define TIMERRELAY_5V_MAX_DELAY                 60
#define TIMERRELAY_3V3_MAX_DELAY                160
#define TIMERRELAY_5V_CALCULATION_MULTIPLIER    0.2353f
#define TIMERRELAY_3V3_CALCULATION_MULTIPLIER   0.6275f

/**
 * @brief Timer Relay Vcc select setting.
 * @details Specified Vcc selection of Timer Relay Click driver.
 */
#define TIMERRELAY_VCC_5V                       0x01
#define TIMERRELAY_VCC_3V3                      0x00

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b timerrelay_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define TIMERRELAY_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define TIMERRELAY_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // timerrelay_set

/**
 * @defgroup timerrelay_map Timer Relay MikroBUS Map
 * @brief MikroBUS pin mapping of Timer Relay Click driver.
 */

/**
 * @addtogroup timerrelay_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Timer Relay Click to the selected MikroBUS.
 */
#define TIMERRELAY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.trg  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // timerrelay_map
/*! @} */ // timerrelay

/**
 * @brief Timer Relay Click context object.
 * @details Context object definition of Timer Relay Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t trg;          /**< Trigger pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t vcc_sel;            /**< Vcc select. */
    
} timerrelay_t;

/**
 * @brief Timer Relay Click configuration object.
 * @details Configuration object definition of Timer Relay Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t trg;             /**< Trigger pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} timerrelay_cfg_t;

/**
 * @brief Timer Relay Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TIMERRELAY_OK = 0,
    TIMERRELAY_ERROR = -1

} timerrelay_return_value_t;

/*!
 * @addtogroup timerrelay Timer Relay Click Driver
 * @brief API for configuring and manipulating Timer Relay Click driver.
 * @{
 */

/**
 * @brief Timer Relay configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #timerrelay_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void timerrelay_cfg_setup ( timerrelay_cfg_t *cfg );

/**
 * @brief Timer Relay initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #timerrelay_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t timerrelay_init ( timerrelay_t *ctx, timerrelay_cfg_t *cfg );

/**
 * @brief Timer Relay default configuration function.
 * @details This function executes a default configuration of Timer Relay
 * click board.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t timerrelay_default_cfg ( timerrelay_t *ctx );

/**
 * @brief Timer Relay data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t timerrelay_generic_write ( timerrelay_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Timer Relay set Vcc select settings function.
 * @details This function is used to set appropriate Vcc selection settings 
 * in order to determine the delay time.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] vcc_sel : Vcc select state.
 * @return Nothing.
 * @note If a wrong setting is set delays will not work properly.
 */
void timerrelay_set_vcc_sel ( timerrelay_t *ctx, uint8_t vcc_sel );

/**
 * @brief Timer Relay set wiper position function.
 * @details This function is used to set wiper position of Timer Relay
 * click board.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position to be set.
 * @return Nothing.
 * @note None.
 */
err_t timerrelay_set_wiper_pos ( timerrelay_t *ctx, uint8_t wiper_pos );

/**
 * @brief Timer Relay set delay function.
 * @details This function is used to set delay in seconds up to 60 Seconds.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] delay : Delay to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t timerrelay_set_delay ( timerrelay_t *ctx, uint8_t delay );

/**
 * @brief Timer Relay set RST pin state function.
 * @details This function is used to set state of the RST pin of Timer Relay
 * click board.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void timerrelay_set_rst_pin ( timerrelay_t *ctx, uint8_t pin_state );

/**
 * @brief Timer Relay set TRG pin state function.
 * @details This function is used to set state of the TRG pin of Timer Relay
 * click board.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @param[in] pin_state : State of the TRG pin.
 * @return Nothing.
 * @note None.
 */
void timerrelay_set_trg_pin ( timerrelay_t *ctx, uint8_t pin_state );

/**
 * @brief Timer Relay reset timer function.
 * @details This function is used to reset timer of Timer Relay
 * click board.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void timerrelay_activate_reset ( timerrelay_t *ctx );

/**
 * @brief Timer Relay activate trigger function.
 * @details This function is used to activate trigger of Timer Relay
 * click board.
 * @param[in] ctx : Click context object.
 * See #timerrelay_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void timerrelay_activate_trigger ( timerrelay_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TIMERRELAY_H

/*! @} */ // timerrelay

// ------------------------------------------------------------------------ END

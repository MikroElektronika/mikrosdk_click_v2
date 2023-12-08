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
 * @file ismrx.h
 * @brief This file contains API for ISM RX Click Driver.
 */

#ifndef ISMRX_H
#define ISMRX_H

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

/*!
 * @addtogroup ismrx ISM RX Click Driver
 * @brief API for configuring and manipulating ISM RX Click driver.
 * @{
 */

/**
 * @defgroup ismrx_reg ISM RX Registers List
 * @brief List of registers of ISM RX Click driver.
 */

/**
 * @addtogroup ismrx_reg
 * @{
 */

/**
 * @brief ISM RX description register.
 * @details Specified register for description of ISM RX Click driver.
 */
#define ISMRX_REG_POWER_CFG                 0x00
#define ISMRX_REG_CFG                       0x01
#define ISMRX_REG_CTRL                      0x02
#define ISMRX_REG_OSC_FREQ                  0x03
#define ISMRX_REG_OFF_TIMER_MSB             0x04
#define ISMRX_REG_OFF_TIMER_LSB             0x05
#define ISMRX_REG_CPU_RECOVERY_TIME         0x06
#define ISMRX_REG_RF_SETTLE_TIMER_MSB       0x07
#define ISMRX_REG_RF_SETTLE_TIMER_LSB       0x08
#define ISMRX_REG_STATUS                    0x09
#define ISMRX_REG_AGC_DWELL_TIMER           0x0A

/*! @} */ // ismrx_reg

/**
 * @defgroup ismrx_set ISM RX Registers Settings
 * @brief Settings for registers of ISM RX Click driver.
 */

/**
 * @addtogroup ismrx_set
 * @{
 */

/**
 * @brief ISM RX description setting.
 * @details Specified setting for description of ISM RX Click driver.
 */
#define ISMRX_MODULATION_NULL               0
#define ISMRX_MODULATION_ASK                1
#define ISMRX_MODULATION_FSK                2

#define ISMRX_RECEIVE_MODE_NULL             0
#define ISMRX_RECEIVE_MODE_RX               3
#define ISMRX_RECEIVE_MODE_DRX              4

/*! @} */ // ismrx_set

/**
 * @defgroup ismrx_map ISM RX MikroBUS Map
 * @brief MikroBUS pin mapping of ISM RX Click driver.
 */

/**
 * @addtogroup ismrx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM RX Click to the selected MikroBUS.
 */
#define ISMRX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); 

/*! @} */ // ismrx_map
/*! @} */ // ismrx

/**
 * @brief ISM RX Click context object.
 * @details Context object definition of ISM RX Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mosi;         /**< SPI MOSI pin. */

    // Input pins
    digital_in_t  miso;         /**< SPI MISO pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t modulation;
    uint8_t receive_mode;

} ismrx_t;

/**
 * @brief ISM RX Click configuration object.
 * @details Configuration object definition of ISM RX Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} ismrx_cfg_t;

/**
 * @brief ISM RX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISMRX_OK = 0,
    ISMRX_ERROR = -1,
    ISMRX_CONTEXT_MODULATION_ERROR = -2,
    ISMRX_CONTEXT_RECEIVE_MODE_ERROR = -3

} ismtx_return_value_t;

/*!
 * @addtogroup ismrx ISM RX Click Driver
 * @brief API for configuring and manipulating ISM RX Click driver.
 * @{
 */

/**
 * @brief ISM RX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ismrx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ismrx_cfg_setup ( ismrx_cfg_t *cfg );

/**
 * @brief ISM RX initialization function.
 * @details This function initializes spi module for device configuration.
 * @param[out] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ismrx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx_init ( ismrx_t *ctx, ismrx_cfg_t *cfg );

/**
 * @brief ISM RX initialization function.
 * @details This function closes spi module and initializes data pin as GPIO.
 * @param[out] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ismrx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx_task_init ( ismrx_t *ctx, ismrx_cfg_t *cfg );

/**
 * @brief ISM RX default configuration function.
 * @details This function executes a default configuration of ISM RX.
 * click board.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ismrx_default_cfg ( ismrx_t *ctx );

/**
 * @brief ISM RX data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx_generic_write ( ismrx_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ISM RX data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx_generic_read ( ismrx_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ISM RX software reset.
 * @details This sends command for resetting device.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note There is a 1 second delay after the reset command is sent.
 */
err_t ismrx_master_reset ( ismrx_t *ctx );

/**
 * @brief ISM RX start receiving signal.
 * @details This function adjust device to start receiving signal in discontinuous mode.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @return Nothing.
 */
void ismrx_start_drx ( ismrx_t *ctx );

/**
 * @brief ISM RX stop receiving signal.
 * @details This function adjust device to stop receiving signal in discontinuous mode.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @return Nothing.
 */
void ismrx_stop_drx ( ismrx_t *ctx );

/**
 * @brief ISM RX get miso pin state.
 * @details This function get's @b miso pin state.
 * @param[in] ctx : Click context object.
 * See #ismrx_t object definition for detailed explanation.
 * @return @b miso pin state.
 */
uint8_t ismrx_get_data ( ismrx_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ISMRX_H

/*! @} */ // ismrx

// ------------------------------------------------------------------------ END

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
 * @file dac11.h
 * @brief This file contains API for DAC 11 Click Driver.
 */

#ifndef DAC11_H
#define DAC11_H

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
 * @addtogroup dac11 DAC 11 Click Driver
 * @brief API for configuring and manipulating DAC 11 Click driver.
 * @{
 */

/**
 * @defgroup dac11_reg DAC 11 Commands List
 * @brief List of commands of DAC 11 Click driver.
 */

/**
 * @addtogroup dac11_reg
 * @{
 */

/**
 * @brief DAC 11 commands list.
 * @details Specified list of commands of control registers of DAC 11 Click driver.
 */
#define DAC11_CMD_CHANNEL_A             0x00
#define DAC11_CMD_CHANNEL_B             0x01
#define DAC11_CMD_CHANNEL_C             0x02
#define DAC11_CMD_CHANNEL_D             0x03
#define DAC11_CMD_CHANNEL_E             0x04
#define DAC11_CMD_CHANNEL_F             0x05
#define DAC11_CMD_CHANNEL_G             0x06
#define DAC11_CMD_CHANNEL_H             0x07
#define DAC11_CMD_WRM                   0x08
#define DAC11_CMD_WTM                   0x09
#define DAC11_CMD_UPDATE_SELECT         0x0A
#define DAC11_CMD_CHANNEL_A_WRITE       0x0B       
#define DAC11_CMD_BROADCAST             0x0C
#define DAC11_CMD_PD_HIGH_Z             0x0D
#define DAC11_CMD_PD_100KOHM            0x0E
#define DAC11_CMD_PD_2p5KOHM            0x0F

/*! @} */ // dac11_reg

/**
 * @defgroup dac11_set DAC 11 Control register Settings
 * @brief Settings for control registers of DAC 11 Click driver.
 */

/**
 * @addtogroup dac11_set
 * @{
 */

/**
 * @brief DAC 11 select channel flags.
 * @details Specified channel selection flags of DAC 11 Click driver.
 */
#define DAC11_SELECT_CHANNEL_A          0x01
#define DAC11_SELECT_CHANNEL_B          0x02
#define DAC11_SELECT_CHANNEL_C          0x04
#define DAC11_SELECT_CHANNEL_D          0x08
#define DAC11_SELECT_CHANNEL_E          0x10
#define DAC11_SELECT_CHANNEL_F          0x20
#define DAC11_SELECT_CHANNEL_G          0x40
#define DAC11_SELECT_CHANNEL_H          0x80
#define DAC11_SELECT_ALL_CHANNELS       0xFF

/**
 * @brief DAC 11 range values.
 * @details DAC range values of DAC 11 Click driver.
 */
#define DAC11_MIN_DAC_VALUE             0x0000
#define DAC11_MAX_DAC_VALUE             0x0FFF

/**
 * @brief DAC 11 vref values.
 * @details DAC vref values of DAC 11 Click driver.
 */
#define DAC11_VREF_3V3                  3.3
#define DAC11_VREF_5V                   5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac11_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC11_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DAC11_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac11_set

/**
 * @defgroup dac11_map DAC 11 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 11 Click driver.
 */

/**
 * @addtogroup dac11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 11 Click to the selected MikroBUS.
 */
#define DAC11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // dac11_map
/*! @} */ // dac11

/**
 * @brief DAC 11 Click context object.
 * @details Context object definition of DAC 11 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;                                  /**< SPI driver object. */

    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */

} dac11_t;

/**
 * @brief DAC 11 Click configuration object.
 * @details Configuration object definition of DAC 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} dac11_cfg_t;

/**
 * @brief DAC 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC11_OK = 0,
    DAC11_ERROR = -1

} dac11_return_value_t;

/*!
 * @addtogroup dac11 DAC 11 Click Driver
 * @brief API for configuring and manipulating DAC 11 Click driver.
 * @{
 */

/**
 * @brief DAC 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac11_cfg_setup ( dac11_cfg_t *cfg );

/**
 * @brief DAC 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac11_init ( dac11_t *ctx, dac11_cfg_t *cfg );

/**
 * @brief DAC 11 default configuration function.
 * @details This function executes a default configuration of DAC 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac11_default_cfg ( dac11_t *ctx );

/**
 * @brief DAC 11 generic write function.
 * @details This function writes a desired number of control bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of registers to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Writing to more than one control register is used for daisy-chain operations.
 */
err_t dac11_generic_write ( dac11_t *ctx, uint16_t *data_in, uint8_t len );

/**
 * @brief DAC 11 write control register function.
 * @details This function writes data to a single control register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] cmd : 4-bit command of control registers.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac11_write_control_reg( dac11_t *ctx, uint8_t cmd, uint16_t data_in );

/**
 * @brief DAC 11 set all channels value function.
 * @details This function sets the raw DAC value to all channels output.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] dac_value : 12-bit raw DAC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac11_set_all_ch_value( dac11_t *ctx, uint16_t dac_value );

/**
 * @brief DAC 11 set all channels voltage function.
 * @details This function sets the output voltage of all channels depending on the vref value defined by 
 * the VCC SEL on-board jumper. The VREF and Voltage values can be either in Volts or Milivolts.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] vref : VREF value defined by VCC SEL on-board jumper.
 * @param[in] voltage : Float value to be set as output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac11_set_all_ch_voltage( dac11_t *ctx, float vref, float voltage );

/**
 * @brief DAC 11 set specific channels value function.
 * @details This function sets the raw DAC value to the specific channels output.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] channel : Output channel mask.
 * @param[in] dac_value : 12-bit raw DAC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac11_set_specific_ch_value( dac11_t *ctx, uint8_t channel, uint16_t dac_value );

/**
 * @brief DAC 11 set specific channels voltage function.
 * @details This function sets the output voltage of the specific channels depending on the vref value defined by 
 * the VCC SEL on-board jumper. The VREF and Voltage values can be either in Volts or Milivolts.
 * @param[in] ctx : Click context object.
 * See #dac11_t object definition for detailed explanation.
 * @param[in] channel : Output channel mask.
 * @param[in] vref : VREF value defined by VCC SEL on-board jumper.
 * @param[in] voltage : Float value to be set as output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac11_set_specific_ch_voltage( dac11_t *ctx, uint8_t channel, float vref, float voltage );

#ifdef __cplusplus
}
#endif
#endif // DAC11_H

/*! @} */ // dac11

// ------------------------------------------------------------------------ END

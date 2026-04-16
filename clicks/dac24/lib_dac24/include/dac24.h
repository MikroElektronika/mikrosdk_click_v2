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
 * @file dac24.h
 * @brief This file contains API for DAC 24 Click Driver.
 */

#ifndef DAC24_H
#define DAC24_H

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
 * @addtogroup dac24 DAC 24 Click Driver
 * @brief API for configuring and manipulating DAC 24 Click driver.
 * @{
 */

/**
 * @defgroup dac24_reg DAC 24 Registers List
 * @brief List of registers of DAC 24 Click driver.
 */

/**
 * @addtogroup dac24_reg
 * @{
 */

/**
 * @brief DAC 24 channel register.
 * @details Specified register for channel of DAC 24 Click driver.
 */
#define DAC24_REG_POWER_DOWN_100K               0x00
#define DAC24_REG_AO1_DATA_OUT                  0x01
#define DAC24_REG_AO2_DATA_OUT                  0x02
#define DAC24_REG_AO3_DATA_OUT                  0x03
#define DAC24_REG_ALL_CH_DATA_OUT               0x07
#define DAC24_REG_POWER_DOWN_2_5K               0x08
#define DAC24_REG_AO1_DATA                      0x09
#define DAC24_REG_AO2_DATA                      0x0A
#define DAC24_REG_AO3_DATA                      0x0B
#define DAC24_REG_POWER_DOWN_HIZ                0x0F

/*! @} */ // dac24_reg

/**
 * @defgroup dac24_set DAC 24 Registers Settings
 * @brief Settings for registers of DAC 24 Click driver.
 */

/**
 * @addtogroup dac24_set
 * @{
 */

/**
 * @brief DAC 24 output channel selection.
 * @details DAC output channel selection of DAC 24 Click driver.
 */
#define DAC24_CHANNEL_ALL                       0
#define DAC24_CHANNEL_1                         1
#define DAC24_CHANNEL_2                         2
#define DAC24_CHANNEL_3                         3

/**
 * @brief DAC 24 power settings.
 * @details Power settings of DAC 24 Click driver.
 */
#define DAC24_POWER_DOWN_HIZ                    0
#define DAC24_POWER_DOWN_2_5K                   1
#define DAC24_POWER_DOWN_100K                   2

/**
 * @brief DAC 24 range values.
 * @details DAC range values of DAC 24 Click driver.
 */
#define DAC24_DAC_VALUE_MIN                     0x00
#define DAC24_DAC_VALUE_MID                     0x80
#define DAC24_DAC_VALUE_MAX                     0xFF

/**
 * @brief DAC 24 VREF and VCC values.
 * @details DAC VREF and VCC values of DAC 24 Click driver.
 */
#define DAC24_VCC_3V3                           3300
#define DAC24_VCC_5V                            5000
#define DAC24_VCC_LEVEL                         DAC24_VCC_3V3

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac24_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC24_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define DAC24_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac24_set

/**
 * @defgroup dac24_map DAC 24 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 24 Click driver.
 */

/**
 * @addtogroup dac24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 24 Click to the selected MikroBUS.
 */
#define DAC24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // dac24_map
/*! @} */ // dac24

/**
 * @brief DAC 24 Click context object.
 * @details Context object definition of DAC 24 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} dac24_t;

/**
 * @brief DAC 24 Click configuration object.
 * @details Configuration object definition of DAC 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} dac24_cfg_t;

/**
 * @brief DAC 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC24_OK = 0,
    DAC24_ERROR = -1

} dac24_return_value_t;

/*!
 * @addtogroup dac24 DAC 24 Click Driver
 * @brief API for configuring and manipulating DAC 24 Click driver.
 * @{
 */

/**
 * @brief DAC 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac24_cfg_setup ( dac24_cfg_t *cfg );

/**
 * @brief DAC 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac24_init ( dac24_t *ctx, dac24_cfg_t *cfg );

/**
 * @brief DAC 24 write register function.
 * @details This function writes a data byte to the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac24_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 8-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac24_write_reg ( dac24_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DAC 24 set power down function.
 * @details This function sets the device in the selected power down mode.
 * @param[in] ctx : Click context object.
 * See #dac24_t object definition for detailed explanation.
 * @param[in] pwr : Power down setting, see DAC24_POWER_DOWN_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p pwr argument).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac24_set_power_down ( dac24_t *ctx, uint8_t pwr );

/**
 * @brief DAC 24 set DAC value function.
 * @details This function writes the 8-bit DAC code value to one or more channels.
 * @param[in] ctx : Click context object.
 * See #dac24_t object definition for detailed explanation.
 * @param[in] channel : DAC channels to be updated, see DAC24_CHANNEL_x macros.
 * @param[in] value : DAC code value (0 to @ref DAC24_DAC_VALUE_MAX).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p channel argument).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac24_set_dac_value ( dac24_t *ctx, uint8_t channel, uint8_t value );

/**
 * @brief DAC 24 set DAC voltage function.
 * @details This function sets the output voltage (in millivolts) for one or more channels
 * by converting it to a corresponding DAC code and updating the device.
 * @param[in] ctx : Click context object.
 * See #dac24_t object definition for detailed explanation.
 * @param[in] channel : DAC channels to be updated, see DAC24_CHANNEL_x macros.
 * @param[in] voltage_mv : Desired output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (voltage out of range).
 * See #err_t definition for detailed explanation.
 * @note The calculation is based on the DAC24_VCC_LEVEL setting.
 */
err_t dac24_set_dac_voltage ( dac24_t *ctx, uint8_t channel, uint16_t voltage_mv );

#ifdef __cplusplus
}
#endif
#endif // DAC24_H

/*! @} */ // dac24

// ------------------------------------------------------------------------ END

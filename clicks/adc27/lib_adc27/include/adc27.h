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
 * @file adc27.h
 * @brief This file contains API for ADC 27 Click Driver.
 */

#ifndef ADC27_H
#define ADC27_H

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
 * @addtogroup adc27 ADC 27 Click Driver
 * @brief API for configuring and manipulating ADC 27 Click driver.
 * @{
 */

/**
 * @defgroup adc27_set ADC 27 Registers Settings
 * @brief Settings for registers of ADC 27 Click driver.
 */

/**
 * @addtogroup adc27_set
 * @{
 */

/**
 * @brief ADC 27 start bit setting.
 * @details Specified setting for start bit of ADC 27 Click driver.
 */
#define ADC27_START_BIT                                 0x80

/**
 * @brief ADC 27 Analog-Input configuration byte setting.
 * @details Specified setting for Analog-Input configuration byte of ADC 27 Click driver.
 */
#define ADC27_CONFIG_CH_SGL_0                           0x00
#define ADC27_CONFIG_CH_SGL_1                           0x10
#define ADC27_CONFIG_CH_SGL_2                           0x20
#define ADC27_CONFIG_CH_SGL_3                           0x30
#define ADC27_CONFIG_CH_SGL_4                           0x40
#define ADC27_CONFIG_CH_SGL_5                           0x50
#define ADC27_CONFIG_CH_SGL_6                           0x60
#define ADC27_CONFIG_CH_SGL_7                           0x70
#define ADC27_CONFIG_CH_DIF_01                          0x00
#define ADC27_CONFIG_CH_DIF_23                          0x20
#define ADC27_CONFIG_CH_DIF_45                          0x40
#define ADC27_CONFIG_CH_DIF_67                          0x60
#define ADC27_CONFIG_CH_MASK                            0x70
#define ADC27_CONFIG_RANGE_SGL_NO_CHANGE                0x00
#define ADC27_CONFIG_RANGE_SGL_VREF_4_NEG_TO_VREF_4_POS 0x01
#define ADC27_CONFIG_RANGE_SGL_VREF_2_NEG_TO_GND        0x02
#define ADC27_CONFIG_RANGE_SGL_GND_TO_VREF_2_POS        0x03
#define ADC27_CONFIG_RANGE_SGL_VREF_2_NEG_TO_VREF_2_POS 0x04
#define ADC27_CONFIG_RANGE_SGL_VREF_NEG_TO_GND          0x05
#define ADC27_CONFIG_RANGE_SGL_GND_TO_VREF_POS          0x06
#define ADC27_CONFIG_RANGE_SGL_VREF_NEG_TO_VREF_POS     0x07
#define ADC27_CONFIG_RANGE_DIF_NO_CHANGE                0x08
#define ADC27_CONFIG_RANGE_DIF_VREF_2_NEG_TO_VREF_2_POS 0x09
#define ADC27_CONFIG_RANGE_DIF_VREF_NEG_TO_VREF_POS     0x0C
#define ADC27_CONFIG_RANGE_DIF_2_VREF_NEG_TO_2_VREF_POS 0x0F
#define ADC27_CONFIG_RANGE_MASK                         0x0F

/**
 * @brief ADC 27 Mode-Control byte setting.
 * @details Specified setting for Mode-Control byte of ADC 27 Click driver.
 */
#define ADC27_MODE_EXT_CLOCK                            0x08
#define ADC27_MODE_EXT_ACQUISITION                      0x18
#define ADC27_MODE_INT_CLOCK                            0x28
#define ADC27_MODE_RESET                                0x48
#define ADC27_MODE_PARTIAL_POWER_DOWN                   0x68
#define ADC27_MODE_FULL_POWER_DOWN                      0x78
#define ADC27_MODE_MASK                                 0x78

/**
 * @brief ADC 27 timeout setting.
 * @details Specified setting for timeout of ADC 27 Click driver.
 */
#define ADC27_TIMEOUT                                   1000

/**
 * @brief ADC 27 VREF setting.
 * @details Specified setting for VREF of ADC 27 Click driver.
 */
#define ADC27_VREF                                      4.096

/**
 * @brief ADC 27 data resolution setting.
 * @details Specified setting for data resolution of ADC 27 Click driver.
 */
#define ADC27_DATA_RES_FULL                             65535.0
#define ADC27_DATA_RES_HALF                             32767.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc27_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC27_SET_DATA_SAMPLE_EDGE                      SET_SPI_DATA_SAMPLE_EDGE
#define ADC27_SET_DATA_SAMPLE_MIDDLE                    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc27_set

/**
 * @defgroup adc27_map ADC 27 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 27 Click driver.
 */

/**
 * @addtogroup adc27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 27 Click to the selected MikroBUS.
 */
#define ADC27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc27_map
/*! @} */ // adc27

/**
 * @brief ADC 27 Click context object.
 * @details Context object definition of ADC 27 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Data ready input pin (rising edge). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t mode;               /**< Mode byte. */
    uint8_t config[ 8 ];        /**< Config bytes for 8 channels. */

} adc27_t;

/**
 * @brief ADC 27 Click configuration object.
 * @details Configuration object definition of ADC 27 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t int_pin;         /**< Data ready input pin (rising edge). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc27_cfg_t;

/**
 * @brief ADC 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC27_OK = 0,
    ADC27_ERROR = -1

} adc27_return_value_t;

/*!
 * @addtogroup adc27 ADC 27 Click Driver
 * @brief API for configuring and manipulating ADC 27 Click driver.
 * @{
 */

/**
 * @brief ADC 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc27_cfg_setup ( adc27_cfg_t *cfg );

/**
 * @brief ADC 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc27_init ( adc27_t *ctx, adc27_cfg_t *cfg );

/**
 * @brief ADC 27 default configuration function.
 * @details This function executes a default configuration of ADC 27
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc27_default_cfg ( adc27_t *ctx );

/**
 * @brief ADC 27 set config function.
 * @details This function sets the configuration for the selected channel
 * of the ADC 27 Click board.
 * @param[in] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @param[in] config : Configuration byte (includes channel, range, and mode).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The function also stores the config for voltage calculations.
 */
err_t adc27_set_config ( adc27_t *ctx, uint8_t config );

/**
 * @brief ADC 27 set mode function.
 * @details This function sets the operating mode of the ADC 27 Click board.
 * @param[in] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @param[in] mode : Operating mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc27_set_mode ( adc27_t *ctx, uint8_t mode );

/**
 * @brief ADC 27 read raw data function.
 * @details This function reads raw ADC data from the selected channel.
 * @param[in] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @param[in] channel : ADC channel to read from.
 * @param[out] data_out : Pointer to the memory where raw data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Data resolution and channel behavior depend on current mode.
 */
err_t adc27_read_raw_data ( adc27_t *ctx, uint8_t channel, uint16_t *data_out );

/**
 * @brief ADC 27 read voltage function.
 * @details This function reads the ADC value from the selected channel and
 * converts it to a voltage level using the configured range.
 * @param[in] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @param[in] channel : ADC channel to read from.
 * @param[out] voltage : Pointer to the memory where voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Voltage calculation uses VREF and resolution defined by config.
 */
err_t adc27_read_voltage ( adc27_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief ADC 27 get INT pin function.
 * @details This function returns the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #adc27_t object definition for detailed explanation.
 * @return Pin state.
 * @note None.
 */
uint8_t adc27_get_int_pin ( adc27_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ADC27_H

/*! @} */ // adc27

// ------------------------------------------------------------------------ END

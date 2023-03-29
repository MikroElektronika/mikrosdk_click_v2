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
 * @file piezoaccel.h
 * @brief This file contains API for Piezo Accel Click Driver.
 */

#ifndef PIEZOACCEL_H
#define PIEZOACCEL_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup piezoaccel Piezo Accel Click Driver
 * @brief API for configuring and manipulating Piezo Accel Click driver.
 * @{
 */

/**
 * @addtogroup measurement_mode
 * @{
 */

/**
 * @brief Piezo Accel measurement mode.
 * @details Configuration depending on the AN SEL onboard jumper.
 */

#define PIEZOACCEL_MEAS_MODE_AN_PIN      0x00
#define PIEZOACCEL_MEAS_MODE_ADC         0x01

/*! @} */ // measurement_mode

/**
 * @addtogroup sensor_voltage
 * @{
 */

/**
 * @brief Piezo Accel sensor voltage mode.
 * @details Configuration depending on the VCC SEL onboard jumper.
 */

#define PIEZOACCEL_SENSOR_VOLTAGE_5V     0x00
#define PIEZOACCEL_SENSOR_VOLTAGE_3V3    0x01

/*! @} */ // sensor_voltage

/**
 * @defgroup piezoaccel_map Piezo Accel MikroBUS Map
 * @brief MikroBUS pin mapping of Piezo Accel Click driver.
 */

/**
 * @addtogroup piezoaccel_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Piezo Accel Click to the selected MikroBUS.
 */
#define PIEZOACCEL_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // piezoaccel_map
/*! @} */ // piezoaccel

/**
 * @brief Piezo Accel Click context object.
 * @details Context object definition of Piezo Accel Click driver.
 */
typedef struct
{
    // Modules

    analog_in_t   adc;                               /**< ADC driver object. */
    
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t    chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} piezoaccel_t;

/**
 * @brief Piezo Accel Click configuration object.
 * @details Configuration object definition of Piezo Accel Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                      /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                      /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                       /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                        /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  an;                        /**< Analog pin descriptor. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    
    analog_in_resolution_t             resolution;       /**< ADC resolution. */
    float                              vref;             /**< ADC reference voltage. */

} piezoaccel_cfg_t;

/**
 * @brief Piezo Accel Click Configuration setup structure.
 * @details Configuration setup of Piezo Accel Click driver.
 */
typedef struct
{
    uint8_t measurement_mode;                        /**< Measurement mode config. */
    uint8_t sensor_voltage;                          /**< Sensor voltage config. */
    float offset_data;                               /**< Offset data from calibration. */
    
} piezoaccel_setup_t;

/*!
 * @addtogroup piezoaccel Piezo Accel Click Driver
 * @brief API for configuring and manipulating Piezo Accel Click driver.
 * @{
 */

/**
 * @brief Piezo Accel configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #piezoaccel_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void piezoaccel_cfg_setup ( piezoaccel_cfg_t *cfg );

/**
 * @brief Piezo Accel initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #piezoaccel_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #piezoaccel_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel_init ( piezoaccel_t *ctx, piezoaccel_cfg_t *cfg );

/**
 * @brief Piezo Accel default configuration function.
 * @details This function executes a default configuration of Piezo Accel
 * click board.
 * @param[in] ctx : Click context object.
 * See #piezoaccel_t object definition for detailed explanation.
 * @param setup_cfg_data : Setup config structure.
 *
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void piezoaccel_default_cfg ( piezoaccel_t *ctx, piezoaccel_setup_t *setup_cfg_data );

/**
 * @brief Piezo Accel read raw adc function.
 * @details This function returns raw value of LTC1864 adc.
 * @param[in] ctx : Click context object.
 * See #piezoaccel_t object definition for detailed explanation.
 * @return Raw adc value.
 *
 * @note None.
 */
uint16_t piezoaccel_adc_raw_read ( piezoaccel_t *ctx );

/**
 * @brief Piezo Accel read adc converted to voltage function.
 * @details This function returns input voltage value of LTC1864 adc.
 * @param[in] ctx : Click context object.
 * See #piezoaccel_t object definition for detailed explanation.
 * @return Voltage adc value [V].
 *
 * @note None.
 */
float piezoaccel_adc_voltage_read ( piezoaccel_t *ctx );

/**
 * @brief Piezo Accel read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel_read_an_pin_value ( piezoaccel_t *ctx, uint16_t *data_out );

/**
 * @brief Piezo Accel read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t piezoaccel_read_an_pin_voltage ( piezoaccel_t *ctx, float *data_out );

/**
 * @brief Piezo Accel read force of acceleration function.
 * @details This function returns the converted G-force of acceleration
 * depending on the config settings. In addition, the configuration has
 * to be set on the click board by soldering jumpers.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param cfg_data : Config data structure.
 * @return G-force acceleration value.
 *
 * @note None.
 */
float piezoaccel_g_unit_read ( piezoaccel_t *ctx, piezoaccel_setup_t *cfg_data );

/**
 * @brief Piezo Accel calibration function.
 * @details This function performs calibration which updates the offset
 * data in config structure. Used to correct the offset output voltage
 * caused by the inaccurate power supply of the sensor.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param cfg_data : Config data structure.
 *
 * @note None.
 */
void piezoaccel_calibration ( piezoaccel_t *ctx, piezoaccel_setup_t *cfg_data );

#ifdef __cplusplus
}
#endif
#endif // PIEZOACCEL_H

/*! @} */ // piezoaccel

// ------------------------------------------------------------------------ END

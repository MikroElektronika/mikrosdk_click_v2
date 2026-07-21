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
 * @file airquality13.h
 * @brief This file contains API for Air Quality 13 Click Driver.
 */

#ifndef AIRQUALITY13_H
#define AIRQUALITY13_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "bmv080.h"
#include "bmv080_defs.h"

/*!
 * @addtogroup airquality13 Air Quality 13 Click Driver
 * @brief API for configuring and manipulating Air Quality 13 Click driver.
 * @{
 */

/**
 * @defgroup airquality13_set Air Quality 13 Registers Settings
 * @brief Settings for registers of Air Quality 13 Click driver.
 */

/**
 * @addtogroup airquality13_set
 * @{
 */

/**
 * @brief Air Quality 13 sensor ID setting.
 * @details Specified setting for sensor ID of Air Quality 13 Click driver.
 */
#define AIRQUALITY13_SENSOR_ID_LEN                  13

/**
 * @brief Air Quality 13 default measurement settings.
 * @details Specified setting for default measurement of Air Quality 13 Click driver.
 */
#define AIRQUALITY13_DEFAULT_INTEGRATION_TIME       10.0f

/**
 * @brief Air Quality 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Air Quality 13 Click driver.
 */
#define AIRQUALITY13_DEVICE_ADDRESS                 0x54

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b airquality13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define AIRQUALITY13_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define AIRQUALITY13_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // airquality13_set

/**
 * @defgroup airquality13_map Air Quality 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Air Quality 13 Click driver.
 */

/**
 * @addtogroup airquality13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Quality 13 Click to the selected MikroBUS.
 */
#define AIRQUALITY13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // airquality13_map
/*! @} */ // airquality13

/**
 * @brief Air Quality 13 Click driver selector.
 * @details Selects target driver interface of Air Quality 13 Click driver.
 */
typedef enum
{
    AIRQUALITY13_DRV_SEL_SPI,                       /**< SPI driver descriptor. */
    AIRQUALITY13_DRV_SEL_I2C                        /**< I2C driver descriptor. */

} airquality13_drv_t;

/**
 * @brief Air Quality 13 Click context object.
 * @details Context object definition of Air Quality 13 Click driver.
 */
typedef struct airquality13_s
{
    digital_in_t irq;                               /**< Interrupt pin(active low). */

    i2c_master_t i2c;                               /**< I2C driver object. */
    spi_master_t spi;                               /**< SPI driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */
    airquality13_drv_t drv_sel;                     /**< Master driver interface selector. */

    bmv080_handle_t bmv080_handle;                  /**< Bosch BMV080 SDK unique handle for a sensor unit. */

} airquality13_t;

/**
 * @brief Air Quality 13 Click configuration object.
 * @details Configuration object definition of Air Quality 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t irq;                                 /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;                           /**< I2C serial speed. */
    uint8_t    i2c_address;                         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    airquality13_drv_t drv_sel;                     /**< Master driver interface selector. */

} airquality13_cfg_t;

/**
 * @brief Air Quality 13 Click measurement data structure.
 * @details Data object definition of Air Quality 13 Click driver.
 */
typedef struct
{
    float   pm2_5_mass_concentration;               /**< PM2.5 mass concentration in µg/m³. */
    float   pm1_mass_concentration;                 /**< PM1.0 mass concentration in µg/m³. */
    float   pm10_mass_concentration;                /**< PM10  mass concentration in µg/m³. */
    float   pm2_5_number_concentration;             /**< PM2.5 number concentration in particles/cm³. */
    float   pm1_number_concentration;               /**< PM1.0 number concentration in particles/cm³. */
    float   pm10_number_concentration;              /**< PM10  number concentration in particles/cm³. */
    float   runtime_in_sec;                         /**< Time elapsed since measurement start in seconds. */
    uint8_t is_obstructed;                          /**< Flag whether the sensor is obstructed and cannot perform a valid measurement. */
    uint8_t is_outside_range;                       /**< Flag whether the PM2.5 concentration is outside the measurement range (0-1000 µg/m³). */
    uint8_t data_ready;                             /**< Set to 1 by the SDK callback when new data arrives. */

} airquality13_data_t;

/**
 * @brief Air Quality 13 measurement algorithm selector.
 * @details Predefined enum values for measurement algorithm selection in Air Quality 13 Click driver.
 */
typedef enum
{
    /**< Measurement algorithm with fastest response. */
    AIRQUALITY13_MEAS_ALG_FAST_RESPONSE = E_BMV080_MEASUREMENT_ALGORITHM_FAST_RESPONSE,  
    /**< Measurement algorithm with balance between precision and response time. */
    AIRQUALITY13_MEAS_ALG_BALANCED = E_BMV080_MEASUREMENT_ALGORITHM_BALANCED,
    /**< Measurement algorithm with maximum precision. */
    AIRQUALITY13_MEAS_ALG_HIGH_PRECISION = E_BMV080_MEASUREMENT_ALGORITHM_HIGH_PRECISION

} airquality13_meas_alg_t;

/**
 * @brief Air Quality 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIRQUALITY13_OK = 0,
    AIRQUALITY13_ERROR = -1

} airquality13_return_value_t;

/*!
 * @addtogroup airquality13 Air Quality 13 Click Driver
 * @brief API for configuring and manipulating Air Quality 13 Click driver.
 * @{
 */

/**
 * @brief Air Quality 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airquality13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airquality13_cfg_setup ( airquality13_cfg_t *cfg );

/**
 * @brief Air Quality 13 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #airquality13_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #airquality13_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void airquality13_drv_interface_sel ( airquality13_cfg_t *cfg, airquality13_drv_t drv_sel );

/**
 * @brief Air Quality 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airquality13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality13_init ( airquality13_t *ctx, airquality13_cfg_t *cfg );

/**
 * @brief Air Quality 13 default configuration function.
 * @details This function executes a default configuration of Air Quality 13
 * Click board.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t airquality13_default_cfg ( airquality13_t *ctx );

/**
 * @brief Air Quality 13 get sensor ID function.
 * @details This function reads the unique 12-character sensor ID string from the BMV080 sensor.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @param[out] sensor_id : Pointer to a character array where sensor ID will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality13_get_sensor_id ( airquality13_t *ctx, char *sensor_id );

/**
 * @brief Air Quality 13 start measurement function.
 * @details This function starts continuous particulate matter measurement via
 * bmv080_start_continuous_measurement function from the Bosch BMV080 SDK.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality13_start_measurement ( airquality13_t *ctx );

/**
 * @brief Air Quality 13 stop measurement function.
 * @details This function stops the active measurement and puts the sensor into sleep mode.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality13_stop_measurement ( airquality13_t *ctx );

/**
 * @brief Air Quality 13 serve interrupt function.
 * @details This function processes pending data from the BMV080 FIFO by calling
 * bmv080_serve_interrupt function from the Bosch BMV080 SDK.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @param[out] meas_data : Pointer to the measurement data structure.
 * See #airquality13_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success (data_ready may be 0 if no new measurement yet),
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality13_serve_interrupt ( airquality13_t *ctx, airquality13_data_t *meas_data );

/**
 * @brief Air Quality 13 get IRQ pin function.
 * @details This function reads the state of the IRQ interrupt pin.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @return IRQ pin state level.
 * @note None.
 */
uint8_t airquality13_get_irq_pin ( airquality13_t *ctx );

/**
 * @brief Air Quality 13 set measurement algorithm function.
 * @details This function sets the PM concentration calculation algorithm via bmv080_set_parameter.
 * @param[in] ctx : Click context object.
 * See #airquality13_t object definition for detailed explanation.
 * @param[in] algorithm : Algorithm selection.
 * See #airquality13_meas_alg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality13_set_meas_alg ( airquality13_t *ctx, airquality13_meas_alg_t algorithm );

#ifdef __cplusplus
}
#endif
#endif // AIRQUALITY13_H

/*! @} */ // airquality13

// ------------------------------------------------------------------------ END

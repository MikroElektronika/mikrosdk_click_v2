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
 * @file tds.h
 * @brief This file contains API for TDS Click Driver.
 */

#ifndef TDS_H
#define TDS_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup tds TDS Click Driver
 * @brief API for configuring and manipulating TDS Click driver.
 * @{
 */

/**
 * @defgroup tds_set TDS Settings
 * @brief Settings of TDS Click driver.
 */

/**
 * @addtogroup tds_set
 * @{
 */

/**
 * @brief TDS ppm calculation values.
 * @details Specified ppm calculation values of TDS Click driver.
 */
#define TDS_COEF_POW3               133.42
#define TDS_COEF_POW2               255.86
#define TDS_COEF_POW1               875.39
#define TDS_COEF_FINAL              0.5

/**
 * @brief TDS default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of TDS Click driver.
 */
#define TDS_NUM_CONVERSIONS         200

/**
 * @brief TDS ADC setting.
 * @details Specified settings for ADC of TDS Click driver.
 */
#define TDS_ADC_RESOLUTION          0x0FFF
#define TDS_VREF_3V3                3.3
#define TDS_VREF_5V                 5.0

/**
 * @brief TDS timeout setting.
 * @details Specified setting for timeout of TDS Click driver.
 */
#define TDS_TIMEOUT_MS              2000

/**
 * @brief TDS device address setting.
 * @details Specified setting for device slave address selection of
 * TDS Click driver.
 */
#define TDS_SET_DEV_ADDR            0x4D

/*! @} */ // tds_set

/**
 * @defgroup tds_map TDS MikroBUS Map
 * @brief MikroBUS pin mapping of TDS Click driver.
 */

/**
 * @addtogroup tds_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TDS Click to the selected MikroBUS.
 */
#define TDS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // tds_map
/*! @} */ // tds

/**
 * @brief TDS Click driver selector.
 * @details Selects target driver interface of TDS Click driver.
 */
typedef enum
{
    TDS_DRV_SEL_ADC,            /**< ADC driver descriptor. */
    TDS_DRV_SEL_I2C             /**< I2C driver descriptor. */

} tds_drv_t;

/**
 * @brief TDS Click context object.
 * @details Context object definition of TDS Click driver.
 */
typedef struct
{
    analog_in_t  adc;           /**< ADC module object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    float        vref;          /**< ADC reference voltage. */
    tds_drv_t    drv_sel;       /**< Master driver interface selector. */

} tds_t;

/**
 * @brief TDS Click configuration object.
 * @details Configuration object definition of TDS Click driver.
 */
typedef struct
{
    pin_name_t an;              /**< Analog pin descriptor. */
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;      /**< ADC resolution. */
    float                  vref;            /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;       /**< I2C serial speed. */
    uint8_t                i2c_address;     /**< I2C slave address. */
    
    tds_drv_t drv_sel;          /**< Master driver interface selector. */

} tds_cfg_t;

/**
 * @brief TDS Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TDS_OK = 0,
    TDS_ERROR = -1

} tds_return_value_t;

/*!
 * @addtogroup tds TDS Click Driver
 * @brief API for configuring and manipulating TDS Click driver.
 * @{
 */

/**
 * @brief TDS configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tds_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tds_cfg_setup ( tds_cfg_t *cfg );

/**
 * @brief TDS driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #tds_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #tds_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void tds_drv_interface_sel ( tds_cfg_t *cfg, tds_drv_t drv_sel );

/**
 * @brief TDS initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tds_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tds_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tds_init ( tds_t *ctx, tds_cfg_t *cfg );

/**
 * @brief TDS read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #tds_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tds_read_raw_adc ( tds_t *ctx, uint16_t *raw_adc );

/**
 * @brief TDS read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #tds_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t tds_read_voltage ( tds_t *ctx, float *voltage );

/**
 * @brief TDS read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #tds_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t tds_read_voltage_avg ( tds_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief TDS set vref function.
 * @details This function sets the voltage reference for TDS Click driver.
 * @param[in] ctx : Click context object.
 * See #tds_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b tds_init is 3.3V.
 */
err_t tds_set_vref ( tds_t *ctx, float vref );

/**
 * @brief TDS read ppm function.
 * @details This function reads the TDS measurement value in ppm.
 * @param[in] ctx : Click context object.
 * See #tds_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store the measured TDS value in ppm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t tds_read_ppm ( tds_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // TDS_H

/*! @} */ // tds

// ------------------------------------------------------------------------ END

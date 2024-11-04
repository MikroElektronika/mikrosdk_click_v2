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
 * @file diffpress3.h
 * @brief This file contains API for Diff Press 3 Click Driver.
 */

#ifndef DIFFPRESS3_H
#define DIFFPRESS3_H

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
 * @addtogroup diffpress3 Diff Press 3 Click Driver
 * @brief API for configuring and manipulating Diff Press 3 Click driver.
 * @{
 */

/**
 * @defgroup diffpress3_set Diff Press 3 Registers Settings
 * @brief Settings for registers of Diff Press 3 Click driver.
 */

/**
 * @addtogroup diffpress3_set
 * @{
 */

/**
 * @brief Diff Press 3 pressure sensor parameter specifications.
 * @details Specified pressure sensor parameter values of Diff Press 3 Click driver.
 */
#define DIFFPRESS3_PMIN             -100.0f   // Measurement range minimum
#define DIFFPRESS3_PMAX              1000.0f  // Measurement range maximum
#define DIFFPRESS3_ACCP_ABS_MIN     -0.3f     // Absolute accuracy minimum
#define DIFFPRESS3_ACCP_ABS_TYP      0.1f     // Absolute accuracy typical
#define DIFFPRESS3_ACCP_ABS_MAX      0.3f     // Absolute accuracy minimum
#define DIFFPRESS3_ACCP_TOT_MIN     -0.5f     // Total accuracy minimum
#define DIFFPRESS3_ACCP_TOT_TYP      0.25f    // Total accuracy typical
#define DIFFPRESS3_ACCP_TOT_MAX      0.5f     // Total accuracy minimum
#define DIFFPRESS3_SENP              0.04196f // Sensitivity (digital)
#define DIFFPRESS3_AN_SENP           275.0f   // Sensitivity (analog)
#define DIFFPRESS3_ACCP_REP          0.01f    // Repeatability
#define DIFFPRESS3_ACCP_DRIFT        0.05f    // Long term drift
#define DIFFPRESS3_DIG_OUTOFF        5660.0f  // Digital Zero pressure offset
#define DIFFPRESS3_DIG_FSS           26214.0f // DigitalFull scale span 
#define DIFFPRESS3_DIG_OUTP_MIN      3207.0f  // Digital Output at minimum pressure
#define DIFFPRESS3_DIG_OUTP_MAX      29491.0f // Digital Output at maximum pressure
#define DIFFPRESS3_AN_OUTOFF         0.87f    // Analog Zero pressure offset
#define DIFFPRESS3_AN_FSS            4.0f     // Analog Full scale span 
#define DIFFPRESS3_AN_OUTP_MIN       0.5f     // Analog Output at minimum pressure
#define DIFFPRESS3_AN_OUTP_MAX       4.5f     // Analog Output at maximum pressure
#define DIFFPRESS3_PRES              0x7FFF   // Resolution

/**
 * @brief Diff Press 3 temperature sensor parameter specifications.
 * @details Specified temperature sensor parameter values of Diff Press 3 Click driver.
 */
#define DIFFPRESS3_TRANGE_MIN        0.0f     // Measurement range minimum
#define DIFFPRESS3_TRANGE_MAX        70.0f    // Measurement range maximum
#define DIFFPRESS3_TRES              0x7FFF   // Resolution
#define DIFFPRESS3_SENT              0.004272 // Sensitivity
#define DIFFPRESS3_OUTT_MIN          8192.0   // Output at minimum temperature
#define DIFFPRESS3_OUTT_MAX          24576.0  // Output at maximum temperature

/**
 * @brief Diff Press 3 ADC setting.
 * @details Specified settings for ADC of Diff Press 3 Click driver.
 */
#define DIFFPRESS3_ADC_RESOLUTION    0x7FFF
#define DIFFPRESS3_VREF_3V3          3.3
#define DIFFPRESS3_VREF_5V           5.0

/**
 * @brief Diff Press 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Diff Press 3 Click driver.
 */
#define DIFFPRESS3_SET_DEV_ADDR      0x78

/*! @} */ // diffpress3_set

/**
 * @defgroup diffpress3_map Diff Press 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Diff Press 3 Click driver.
 */

/**
 * @addtogroup diffpress3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Diff Press 3 Click to the selected MikroBUS.
 */
#define DIFFPRESS3_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // diffpress3_map
/*! @} */ // diffpress3

/**
 * @brief Diff Press 3 Click driver selector.
 * @details Selects target driver interface of Diff Press 3 Click driver.
 */
typedef enum
{
    DIFFPRESS3_DRV_SEL_ADC,    /**< ADC driver descriptor. */
    DIFFPRESS3_DRV_SEL_I2C     /**< I2C driver descriptor. */

} diffpress3_drv_t;

/**
 * @brief Diff Press 3 Click AN SEL selector value.
 * @details AN SEL value of Diff Press 3 Click driver.
 */
typedef enum
{
    DIFFPRESS3_AN_SEL_5V  = 1,    /**< AN SEL: 5V */
    DIFFPRESS3_AN_SEL_2V5 = 2     /**< AN SEL: 2.5V */

} diffpress3_an_sel_t;

/**
 * @brief Diff Press 3 Click digital output data selector.
 * @details Digital output data value of Diff Press 3 Click driver.
 */
typedef enum
{
    DIFFPRESS3_RAW_DATA_PRESSURE    = 0,    /**< Digital pressure. */
    DIFFPRESS3_RAW_DATA_TEMPERATURE = 2     /**< Temperature pressure. */

} diffpress3_d_sel_t;

/**
 * @brief Diff Press 3 Click context object.
 * @details Context object definition of Diff Press 3 Click driver.
 */
typedef struct
{
    analog_in_t  adc;    /**< ADC module object. */
    i2c_master_t i2c;    /**< I2C driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    float        vref;             /**< ADC reference voltage. */
    diffpress3_drv_t drv_sel;      /**< Master driver interface selector. */
    
    diffpress3_an_sel_t an_sel;     /**< AN SEL selector. */
    diffpress3_d_sel_t data_sel;    /**< Digital output data selector. */

} diffpress3_t;

/**
 * @brief Diff Press 3 Click configuration object.
 * @details Configuration object definition of Diff Press 3 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;    /**< ADC resolution. */
    float                  vref;          /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;     /**< I2C serial speed. */
    uint8_t                i2c_address;   /**< I2C slave address. */
    
    diffpress3_drv_t drv_sel;       /**< Master driver interface selector. */
    diffpress3_an_sel_t an_sel;     /**< AN SEL selector. */
    diffpress3_d_sel_t data_sel;    /**< Digital output data selector. */

} diffpress3_cfg_t;

/**
 * @brief Diff Press 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIFFPRESS3_OK = 0,
    DIFFPRESS3_ERROR = -1

} diffpress3_return_value_t;

/*!
 * @addtogroup diffpress3 Diff Press 3 Click Driver
 * @brief API for configuring and manipulating Diff Press 3 Click driver.
 * @{
 */

/**
 * @brief Diff Press 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #diffpress3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void diffpress3_cfg_setup ( diffpress3_cfg_t *cfg );

/**
 * @brief Diff Press 3 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #diffpress3_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #diffpress3_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void diffpress3_drv_interface_selection ( diffpress3_cfg_t *cfg, diffpress3_drv_t drv_sel );

/**
 * @brief Diff Press 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #diffpress3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress3_init ( diffpress3_t *ctx, diffpress3_cfg_t *cfg );

/**
 * @brief Diff Press 3 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @param[out] data_sel : Digital output data selector.
 * See diffpress3_d_sel_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress3_read_raw_adc ( diffpress3_t *ctx, uint16_t *raw_adc, diffpress3_d_sel_t data_sel );

/**
 * @brief Diff Press 3 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t diffpress3_read_voltage ( diffpress3_t *ctx, float *voltage );

/**
 * @brief Diff Press 3 set vref function.
 * @details This function sets the voltage reference for Diff Press 3 Click driver.
 * @param[in] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b diffpress3_init is 3.3V.
 */
err_t diffpress3_set_vref ( diffpress3_t *ctx, float vref );

/**
 * @brief Diff Press 3 get pressure function.
 * @details This function reads a differential pressure data in kPa
 * of the WSEN-PDUS, differential pressure sensor
 * on the Diff Press 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[out] pressure : Differential pressure (kPa).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress3_get_pressure ( diffpress3_t *ctx, float *pressure );

/**
 * @brief Diff Press 3 get temperature function.
 * @details This function reads a temperature data in degree Celsius
 * of the WSEN-PDUS, differential pressure sensor
 * on the Diff Press 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[out] temperature : Temperature (degree Celsius).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note WSEN-PDUS sensor support only analog pressure data.
 */
err_t diffpress3_get_temperature ( diffpress3_t *ctx, float *temperature );

/**
 * @brief Diff Press 3 get digital output data function.
 * @details This function reads pressure and temperature digital output raw data
 * of the WSEN-PDUS, differential pressure sensor
 * on the Diff Press 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #diffpress3_t object definition for detailed explanation.
 * @param[out] press_data : Raw pressure values.
 * @param[out] press_data : Raw temperature values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress3_get_digit_out_data ( diffpress3_t *ctx, uint16_t *press_data, uint16_t *temp_data );

#ifdef __cplusplus
}
#endif
#endif // DIFFPRESS3_H

/*! @} */ // diffpress3

// ------------------------------------------------------------------------ END

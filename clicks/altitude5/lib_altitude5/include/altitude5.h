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
 * @file altitude5.h
 * @brief This file contains API for Altitude 5 Click Driver.
 */

#ifndef ALTITUDE5_H
#define ALTITUDE5_H

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

#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup altitude5 Altitude 5 Click Driver
 * @brief API for configuring and manipulating Altitude 5 Click driver.
 * @{
 */

/**
 * @defgroup altitude5_reg Altitude 5 Registers List
 * @brief List of registers of Altitude 5 Click driver.
 */

/**
 * @defgroup altitude5_set Altitude 5 Registers Settings
 * @brief Settings for registers of Altitude 5 Click driver.
 */

/**
 * @addtogroup altitude5_set
 * @{
 */

/**
 * @brief Altitude 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Altitude 5 Click driver.
 */
#define ALTITUDE5_SET_DEV_ADDR                0x4D

/*! @} */ // altitude5_set

/**
 * @defgroup altitude5_map Altitude 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Altitude 5 Click driver.
 */

/**
 * @addtogroup altitude5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Altitude 5 Click to the selected MikroBUS.
 */
#define ALTITUDE5_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // altitude5_map
/*! @} */ // altitude5

typedef enum
{
   ALTITUDE5_DRV_SEL_AN,       /**< AN driver descriptor. */
   ALTITUDE5_DRV_SEL_I2C       /**< I2C driver descriptor. */

} altitude5_drv_t;

typedef err_t ( *altitude5_master_io_t )( struct altitude5_s*, uint16_t* ); 

/**
 * @brief Altitude 5 Click context object.
 * @details Context object definition of Altitude 5 Click driver.
 */
typedef struct altitude5_s
{   
    analog_in_t  adc;                   /**< ADC module object. */

    // Modules
    i2c_master_t i2c;                   /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;              /**< Device slave address (used for I2C driver). */
    
    altitude5_drv_t  drv_sel;           /**< Master driver interface selector. */
    
    altitude5_master_io_t  read_adc_f;  /**< Master write function. */
    
    int16_t offset;                     /**< ADC offset. */
    float sea_lvl_pressure;             /**< Sea-level pressure. */
    float temperature;                  /**< Temperature degree Celsius. */

} altitude5_t;

/**
 * @brief Altitude 5 Click configuration object.
 * @details Configuration object definition of Altitude 5 Click driver.
 */
typedef struct
{
    pin_name_t  an;                         /**< Analog pin descriptor. */
    
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
    pin_name_t  scl;                        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                    /**< I2C serial speed. */
    uint8_t   i2c_address;                  /**< I2C slave address. */
    
    altitude5_drv_t  drv_sel;
    
    int16_t adc_offset;                     /**< ADC offset. */
    float sea_level_pressure;               /**< Sea-level pressure. */
    float temperature_degree_celsius;       /**< Temperature degree Celsius. */

} altitude5_cfg_t;


/**
 * @brief Altitude 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ALTITUDE5_OK = 0,
   ALTITUDE5_ERROR = -1

} altitude5_return_value_t;

/*!
 * @addtogroup altitude5 Altitude 5 Click Driver
 * @brief API for configuring and manipulating Altitude 5 Click driver.
 * @{
 */

/**
 * @brief Altitude 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #altitude5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void altitude5_cfg_setup ( altitude5_cfg_t *cfg );

/**
 * @brief Altitude 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #altitude5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude5_init ( altitude5_t *ctx, altitude5_cfg_t *cfg );

/**
 * @brief Altitude 5 default configuration function.
 * @details This function executes a default configuration of Altitude 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t altitude5_default_cfg ( altitude5_t *ctx );

/**
 * @brief Altitude 5 get ADC function.
 * @details This function reads 12-bit ADC data
 * of the TKP236 Analog Absolute Pressure Sensor
 * on the Altitude 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude5_get_adc ( altitude5_t *ctx, uint16_t *data_out );

/**
 * @brief Altitude 5 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin ( V ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude5_read_an_pin_voltage ( altitude5_t *ctx, float *data_out );

/**
 * @brief Altitude 5 get ADC voltage function.
 * @details This function reads 12-bit ADC data and calculate ADC voltage ( V )
 * of the TKP236 Analog Absolute Pressure Sensor
 * on the Altitude 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output ADC voltage ( V ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude5_get_adc_voltage ( altitude5_t *ctx, float *adc_vtg );

/**
 * @brief Altitude 5 get pressure function.
 * @details This function reads 12-bit ADC data and calculate pressure ( hPa - mBar )
 * of the TKP236 Analog Absolute Pressure Sensor
 * on the Altitude 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] pressure : Output pressure ( hPa - mBar ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude5_get_pressure ( altitude5_t *ctx, float *pressure );

/**
 * @brief Altitude 5 get altitude function.
 * @details This function reads 12-bit ADC data and calculate altitude ( meters )
 * of the TKP236 Analog Absolute Pressure Sensor
 * on the Altitude 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] altitude : Output altitude ( m ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude5_get_altitude ( altitude5_t *ctx, float *altitude );

#ifdef __cplusplus
}
#endif
#endif // ALTITUDE5_H

/*! @} */ // altitude5

// ------------------------------------------------------------------------ END

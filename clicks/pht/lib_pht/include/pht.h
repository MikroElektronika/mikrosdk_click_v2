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
 * @file pht.h
 * @brief This file contains API for PHT Click Driver.
 */

#ifndef PHT_H
#define PHT_H

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

/*!
 * @addtogroup pht PHT Click Driver
 * @brief API for configuring and manipulating PHT Click driver.
 * @{
 */

/**
 * @defgroup pht_set PHT Registers Settings
 * @brief Settings for registers of PHT Click driver.
 */

/**
 * @addtogroup pht_set
 * @{
 */

/**
 * @brief PHT Command for relative humidity.
 * @details Specified commands for relative humidity of PHT Click driver.
 */
#define PHT_RH_CMD_RESET                                           0xFE
#define PHT_RH_CMD_WRITE_USER_REG                                  0xE6
#define PHT_RH_CMD_READ_USER_REG                                   0xE7
#define PHT_RH_MEASURE_RH_HOLD                                     0xE5
#define PHT_RH_MEASURE_RH_NO_HOLD                                  0xF5

/**
 * @brief PHT Command for pressure and temperature.
 * @details Specified commands for pressure and temperature of PHT Click driver.
 */
#define PHT_PT_CMD_RESET                                           0x1E
#define PHT_PT_CMD_ADC_READ                                        0x00
#define PHT_PT_CMD_PROM_READ_P_T_START                             0xA0
#define PHT_PT_CMD_PROM_READ_P_T_END                               0xAE

#define PHT_PT_CMD_RATIO_256                                       0x00
#define PHT_PT_CMD_RATIO_512                                       0x01
#define PHT_PT_CMD_RATIO_1024                                      0x02
#define PHT_PT_CMD_RATIO_2048                                      0x03
#define PHT_PT_CMD_RATIO_4096                                      0x04
#define PHT_PT_CMD_RATIO_8192                                      0x05

/**
 * @brief PHT coefficient for pressure and temperature.
 * @details Specified coefficient for calculation pressure and temperature of PHT Click driver.
 */
#define PHT_PT_MANUFACTURER_RESERVED                               0x00
#define PHT_PT_C1_SENS                                             0x01
#define PHT_PT_C2_OFF                                              0x02
#define PHT_PT_C3_TCS                                              0x03
#define PHT_PT_C4_TCO                                              0x04
#define PHT_PT_C5_TREF                                             0x05
#define PHT_PT_C6_TEMPSENS                                         0x06
#define PHT_PT_CRC                                                 0x07

/**
 * @brief PHT Select output data.
 * @details Select output data of PHT Click driver.
 */
#define PHT_SENSOR_TYPE_RH                                         0x00
#define PHT_SENSOR_TYPE_PT                                         0x01

/**
 * @brief PHT device address setting.
 * @details Specified setting for device slave address selection of
 * PHT Click driver.
 */
#define PHT_I2C_SLAVE_ADDR_RH                                      0x40
#define PHT_I2C_SLAVE_ADDR_P_AND_T                                 0x76


/*! @} */ // pht_set

/**
 * @defgroup pht_map PHT MikroBUS Map
 * @brief MikroBUS pin mapping of PHT Click driver.
 */

/**
 * @addtogroup pht_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PHT Click to the selected MikroBUS.
 */
#define PHT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // pht_map
/*! @} */ // pht

/**
 * @brief PHT Click context object.
 * @details Context object definition of PHT Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} pht_t;

/**
 * @brief PHT Click configuration object.
 * @details Configuration object definition of PHT Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} pht_cfg_t;

/**
 * @brief PHT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PHT_OK = 0,
   PHT_ERROR = -1

} pht_return_value_t;

/*!
 * @addtogroup pht PHT Click Driver
 * @brief API for configuring and manipulating PHT Click driver.
 * @{
 */

/**
 * @brief PHT configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pht_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pht_cfg_setup ( pht_cfg_t *cfg );

/**
 * @brief PHT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pht_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pht_init ( pht_t *ctx, pht_cfg_t *cfg );

/**
 * @brief PHT I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pht_generic_write ( pht_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief PHT I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pht_generic_read ( pht_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );


/**
 * @brief Set Command function.
 * @details The function set desired command to the desired sensor type
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] sensor_type : Selection between temperature and pressure or humidity.
 * @param[in] cmd : Command byte to be written.
 * @return Nothing.
 */
void pht_set_command ( pht_t *ctx, uint8_t sensor_type, uint8_t cmd );

/**
 * @brief Soft Reset function.
 * @details The function is performed by a software reset
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] sensor_type : Selection between temperature and pressure or humidity.
 * @return Nothing.
 */
void pht_soft_reset ( pht_t *ctx, uint8_t sensor_type );

/**
 * @brief Calibration Data Read function.
 * @details The function reads calibration data from PROM
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] sel_data : Select coefficient from 0 to 7 which be read;
 * @param[in] tx_data : Buffer where coefficient be stored;
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
uint8_t pht_get_prom ( pht_t *ctx, uint8_t sel_data, uint32_t *tx_data );

/**
 * @brief Set Ratio function.
 * @details The function determines the oversampling ratio value 
 * for temperature and pressure measurements 
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] temp_ratio : Determines the oversampling ratio for temperature measurement:
 * @param[in] press_ratio : Determines the oversampling ratio for pressure measurement:
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
uint8_t pht_set_ratio ( pht_t *ctx, uint8_t temp_ratio, uint8_t press_ratio );

/**
 * @brief Reset function.
 * @details The function performs the device reset and 
 * reads calibration coefficients after reset,
 * which are necessary for temperature and pressure calculation
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @return Nothing.
 */
void pht_reset ( pht_t *ctx );

/**
 * @brief Write User Register function.
 * @details The function write the byte of the data to the user register
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[in] tx_data : 8-bit data to be written to the user register;
 * @return Nothing.
 */
void pht_write_user_register ( pht_t *ctx, uint8_t tx_data );

/**
 * @brief Raed User Register function.
 * @details The function read the byte of the data from the user register
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @return 8-bit status register.
 */
uint8_t pht_read_user_register ( pht_t *ctx );

/**
 * @brief Measure RH function.
 * @details The function performs humidity measurements
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[out] rh_data : Pointer to the memory location where humidity data be stored.
 * @return 8-bit status.
 */
uint8_t pht_measure_rh ( pht_t *ctx, uint16_t *rh_data );

/**
 * @brief Get temperature and pressure function.
 * @details The function performs temperature and pressure measurements 
 * with desired oversampling ratio and performs
 * the calculations that converts temperature data in celsius value 
 * and pressure data in mbar value 
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the memory location where temperature (degree Celsius) be stored.
 * @param[out] pressure : Pointer to the memory location where pressure (mBar) be stored.
 * @return Nothing.
 */
void pht_get_temperature_pressure ( pht_t *ctx, float *temperature, float *pressure );

/**
 * @brief Get humidity function.
 * @details The function performs humidity measurements
 * with desired oversampling ratio and performs
 * the calculations that converts humidity data in mBar
 * of MS8607 PHT ( Pressure, Humidity and Temperature ) Combination Sensor
 * on the PHT Click board.
 * @param[in] ctx : Click context object.
 * See #pht_t object definition for detailed explanation.
 * @param[out] humidity : Pointer to the memory location where humidity (percentage) be stored.
 * @return Nothing.
 */
void pht_get_relative_humidity ( pht_t *ctx, float *humidity );

#ifdef __cplusplus
}
#endif
#endif // PHT_H

/*! @} */ // pht

// ------------------------------------------------------------------------ END

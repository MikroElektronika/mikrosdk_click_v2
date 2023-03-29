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
 * @file hvac.h
 * @brief This file contains API for HVAC Click Driver.
 */

#ifndef HVAC_H
#define HVAC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup hvac HVAC Click Driver
 * @brief API for configuring and manipulating HVAC Click driver.
 * @{
 */

/**
 * @defgroup hvac_set HVAC Registers Settings
 * @brief Settings for registers of HVAC Click driver.
 */

/**
 * @addtogroup hvac_set
 * @{
 */

/**
 * @brief HVAC description setting.
 * @details Specified setting for description of HVAC Click driver.
 */

/**
 * @brief HVAC List of SCD40 sensor commands.
 * @details Specified list of SCD40 sensor commands of HVAC Click driver.
 */
#define HVAC_START_PERIODIC_MEASUREMENT                             0x21B1
#define HVAC_START_LOW_POWER_PERIODIC_MEASUREMENT                   0x21AC
#define HVAC_START_ULTRA_LOW_POWER_PERIODIC_MEASUREMENT             0x21A7
#define HVAC_MEASURE_SINGLE_SHOT                                    0x219D
#define HVAC_MEASURE_SINGLE_SHOT_RHT_ONLY                           0x2196
#define HVAC_READ_MEASUREMENT                                       0xEC05
#define HVAC_STOP_PERIODIC_MEASUREMENT                              0x3F86
#define HVAC_GET_SERIAL_NUMBER                                      0x3682
#define HVAC_GET_FEATURE_SET_VERSION                                0x202F
#define HVAC_GET_TEMPERATURE_OFFSET                                 0x2318
#define HVAC_SET_TEMPERATURE_OFFSET                                 0x241D
#define HVAC_PERFORM_FORCED_RECALIBRATION                           0x362F
#define HVAC_GET_AUTOMATIC_SELF_CALIBRATION_ENABLED                 0x2313
#define HVAC_SET_AUTOMATIC_SELF_CALIBRATION_ENABLED                 0x2416
#define HVAC_GET_AUTOMATIC_SELF_CALIBRATION_INITIAL_PERIOD          0x2340
#define HVAC_SET_AUTOMATIC_SELF_CALIBRATION_INITIAL_PERIOD          0x2445
#define HVAC_GET_AUTOMATIC_SELF_CALIBRATION_STANDARD_PERIOD         0x234B
#define HVAC_SET_AUTOMATIC_SELF_CALIBRATION_STANDARD_PERIOD         0x244E
#define HVAC_PERSIST_SETTINGS                                       0x3615
#define HVAC_PERFORM_FACTORY_RESET                                  0x3632
#define HVAC_REINIT                                                 0x3646

/**
 * @brief HVAC I2C communication information.
 * @details Specified I2C communication information of HVAC Click driver.
 */
#define HVAC_SPS30_I2C_START_MEASUREMENT                            0x0010
#define HVAC_SPS30_I2C_STOP_MEASUREMENT                             0x0104
#define HVAC_SPS30_I2C_READ_DATA_RDY_FLAG                           0x0202
#define HVAC_SPS30_I2C_READ_MEASURED_VALUE                          0x0300
#define HVAC_SPS30_I2C_SLEEP                                        0x1001
#define HVAC_SPS30_I2C_WAKEUP                                       0x1103
#define HVAC_SPS30_I2C_START_FAN_CLEANING                           0x5607
#define HVAC_SPS30_I2C_AUTO_CLEANING_INTERVAL                       0x8004
#define HVAC_SPS30_I2C_SET_AUTO_CLEANING_INTERVAL                   0x8005
#define HVAC_SPS30_I2C_STOP_MEASUREMENT_DUMMY                       0x0000

#define HVAC_SPS30_I2C_READ_PRODUCT_TYPE                            0xD002
#define HVAC_SPS30_I2C_READ_SERIAL_NUMBER                           0xD033
#define HVAC_SPS30_I2C_READ_VERSION                                 0xD100
#define HVAC_SPS30_I2C_READ_STATUS_REGISTER                         0xD206
#define HVAC_SPS30_I2C_CLEAR_STATUS_REGISTER                        0xD210
#define HVAC_SPS30_I2C_RESET                                        0xD304

/**
 * @brief HVAC new data ready Flag.
 * @details New data ready flag of HVAC Click driver.
 */
#define HVAC_SPS30_NEW_DATA_NOT_READY                               0x00
#define HVAC_SPS30_NEW_DATA_IS_READY                                0x01

/**
 * @brief HVAC device address setting.
 * @details Specified setting for device slave address selection of
 * HVAC Click driver.
 */
#define HVAC_SPS30_SLAVE_ADDR                                       0x69
#define HVAC_SCD40_SLAVE_ADDR                                       0x62


/*! @} */ // hvac_set

/**
 * @defgroup hvac_map HVAC MikroBUS Map
 * @brief MikroBUS pin mapping of HVAC Click driver.
 */

/**
 * @addtogroup hvac_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HVAC Click to the selected MikroBUS.
 */
#define HVAC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // hvac_map
/*! @} */ // hvac

/**
 * @brief HVAC Click measurements object.
 * @details Measurements object definition of HVAC Click driver.
 */
typedef struct
{
    uint16_t co2_concent;
    float temperature;
    float r_humidity;
    uint16_t asc_update_count;
    uint16_t asc_last_correction;
} measuremen_data_t;

/**
 * @brief HVAC Click feature data object.
 * @details Feature data object definition of HVAC Click driver.
 */
typedef struct
{
    uint8_t product_type;
    uint8_t platform_type;
    uint8_t product_major_version;
    uint8_t product_minor_version;
} feature_data_t;

/**
 * @brief HVAC Click mass and number of particles object.
 * @details Mass and number of particles object definition of HVAC Click driver.
 */
typedef struct
{
    float mass_pm_1_0;
    float mass_pm_2_5;
    float mass_pm_4_0;
    float mass_pm_10;
    float num_pm_0_5;
    float num_pm_1_0;
    float num_pm_2_5;
    float num_pm_4_0;
    float num_pm_10;
    float typ_ptcl_size;
} mass_and_num_cnt_data_t;

/**
 * @brief HVAC Click context object.
 * @details Context object definition of HVAC Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;      /**< I2C driver object. */
    uart_t uart;           /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address; /**< Device slave address (used for I2C driver). */
    
} hvac_t;

/**
 * @brief HVAC Click configuration object.
 * @details Configuration object definition of HVAC Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */
    
} hvac_cfg_t;

/**
 * @brief HVAC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HVAC_OK = 0,
    HVAC_ERROR = -1

} hvac_return_value_t;

/*!
 * @addtogroup hvac HVAC Click Driver
 * @brief API for configuring and manipulating HVAC Click driver.
 * @{
 */

/**
 * @brief HVAC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hvac_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hvac_cfg_setup ( hvac_cfg_t *cfg );

/**
 * @brief HVAC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hvac_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac_init ( hvac_t *ctx, hvac_cfg_t *cfg );

/**
 * @brief HVAC I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac_generic_write ( hvac_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief HVAC I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac_generic_read ( hvac_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );


/**
 * @brief SCD40 generic write data function.
 * @details The function writes a 16-bit data to the targeted 16-bit
 * register address of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] reg : 16-bit register address.
 * @param[in] tx_data : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hvac_scd40_write_data ( hvac_t *ctx, uint16_t reg, uint16_t tx_data );

/**
 * @brief SCD40 generic read data function.
 * @details The function read a 16-bit data from the targeted 16-bit
 * register address of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] reg : 16-bit register address.
 * @param[out] rx_data : Pointer to the memory location where 16-bit read data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hvac_scd40_read_data ( hvac_t *ctx, uint16_t reg, uint16_t *rx_data );
/**
 * @brief SCD40 send command function.
 * @details The function send command to the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] cmd : 16-bit command.
 * @return Nothing.
 */
void hvac_scd40_send_cmd ( hvac_t *ctx, uint16_t cmd );

/**
 * @brief SCD40 read measurement function.
 * @details The function read sensor measurement data
 * of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] m_data : Pointer to the memory location where structure data be stored.
 * @return Nothing.
 */
void hvac_scd40_read_measurement ( hvac_t *ctx, measuremen_data_t *m_data );

/**
 * @brief SCD40 get serial number function.
 * @details The function get serial number value 
 * of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] serial_number : Pointer to the memory location where serial numbe value be stored.
 * @return Nothing.
 */
void hvac_scd40_get_serial_number ( hvac_t *ctx, uint16_t *serial_number );

/**
 * @brief SCD40 get feature set version function.
 * @details The function get feature set version value
 * of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] f_data : Pointer to the memory location where structure data be stored.
 * @return Nothing.
 */
void hvac_scd40_get_feature_set_version ( hvac_t *ctx, feature_data_t *f_data );

/**
 * @brief SCD40 set temperature offset function
 * @details The function set temperature offset value
 * of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] temp_offset : Float temperature offset value ( degree Celsius ).
 * @return Nothing.
 */
void hvac_scd40_set_temperature_offset ( hvac_t *ctx, float temp_offset );

/**
 * @brief SCD40 get temperature offset function.
 * @details The function get temperature offset value
 * of the SCD40 CO2, RH and T Sensor
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @return Float temperature offset value ( degree Celsius ).
 */
float hvac_scd40_get_temperature_offset ( hvac_t *ctx );

/**
 * @brief SPS30 generic write data function.
 * @details The function writes a 16-bit data to the targeted 16-bit
 * register address 
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] reg : 16-bit register address.
 * @param[in] tx_data : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hvac_sps30_i2c_write_data ( hvac_t *ctx, uint16_t reg, uint16_t tx_data );

/**
 * @brief SPS30 generic read data function.
 * @details The function read a 16-bit data from the targeted 16-bit
 * register address
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[in] reg : 16-bit register address.
 * @param[out] rx_data : Pointer to the memory location where 16-bit read data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hvac_sps30_i2c_read_data ( hvac_t *ctx, uint16_t reg, uint16_t *rx_data );

/**
 * @brief SPS30 start measurement command function.
 * @details The function set starts the measurement mode
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @return Nothing.
 */
void hvac_sps30_start_measurement ( hvac_t *ctx );

/**
 * @brief SPS30 stop measurement command function.
 * @details The function set stop the measurement mode
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @return Nothing.
 */
void hvac_sps30_stop_measurement ( hvac_t *ctx );

/**
 * @brief SPS30 set device reset function.
 * @details The function set set device reset
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @return Nothing.
 */
void hvac_sps30_device_reset ( hvac_t *ctx );

/**
 * @brief SPS30 get ready flag function.
 * @details The function get new data ready flag
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @return @li @c 0 - No new data,
 *         @li @c 1 - Data ready.
 *
 * See #err_t definition for detailed explanation.
 */
uint8_t hvac_sps30_get_ready_flag ( hvac_t *ctx );

/**
 * @brief SPS30 read measured data function.
 * @details The functionread measured data
 * of the SPS30 Particulate Matter Sensor for Air Quality Monitoring and Control
 * on the HVAC click board.
 * @param[in] ctx : Click context object.
 * See #hvac_t object definition for detailed explanation.
 * @param[out] m_n_c_data : Pointer to the memory location where structure data be stored.
 * @return Nothing.
 */
void hvac_sps30_read_measured_data ( hvac_t *ctx, mass_and_num_cnt_data_t *m_n_c_data );

#ifdef __cplusplus
}
#endif
#endif // HVAC_H

/*! @} */ // hvac

// ------------------------------------------------------------------------ END

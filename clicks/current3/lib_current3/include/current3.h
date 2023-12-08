/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Current 3 Click driver.
 *
 * \addtogroup current3 Current 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CURRENT3_H
#define CURRENT3_H

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
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CURRENT3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.trm = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CURRENT3_OK                                                0
#define CURRENT3_ERROR                                            -1
/** \} */

/**
 * \defgroup slave_and_resp_addr Slave and Response address
 * \{
 */
#define CURRENT3_I2C_SLAVE_ADDR                                    0x4C
#define CURRENT3_ALERT_RESPONSE_ADDRESS                            0x0C
/** \} */

/**
 * \defgroup diode_settings Diode Settings
 * \{
 */
#define CURRENT3_REG_INT_DIODE_DATA_HIGH_BYTE                      0x00
#define CURRENT3_REG_EXT_DIODE_1_DATA_HIGH_BYTE                    0x01
#define CURRENT3_REG_STATUS                                        0x02
#define CURRENT3_REG_CFG                                           0x03
#define CURRENT3_REG_CONVERSION_RATE                               0x04
#define CURRENT3_REG_INT_DIODE_HIGH_LIMIT                          0x05
#define CURRENT3_REG_INT_DIODE_LOW_LIMIT                           0x06
#define CURRENT3_REG_EXT_DIODE_1_HIGH_LIMIT_HIGH_BYTE              0x07
#define CURRENT3_REG_EXT_DIODE_1_LOW_LIMIT_HIGH_BYTE               0x08
#define CURRENT3_REG_ONE_SHOT                                      0x0F
#define CURRENT3_REG_EXT_DIODE_1_DATA_LOW_BYTE                     0x10
#define CURRENT3_REG_EXT_DIODE_1_HIGH_LIMIT_LOW_BYTE               0x13
#define CURRENT3_REG_EXT_DIODE_1_LOW_LIMIT_LOW_BYTE                0x14
#define CURRENT3_REG_EXT_DIODE_1_TCRIT_LIMIT                       0x19
#define CURRENT3_REG_EXT_DIODE_FAULT                               0x1B
#define CURRENT3_REG_CHANNEL_MASK_REGISTER                         0x1F
#define CURRENT3_REG_INT_DIODE_TCRIT_LIMIT                         0x20
#define CURRENT3_REG_TCRIT_HYSTERESIS                              0x21
#define CURRENT3_REG_CONSECUTIVE_ALERT                             0x22
#define CURRENT3_REG_EXT_DIODE_1_BETA_CFG                          0x25
#define CURRENT3_REG_EXT_DIODE_1_IDEALITY_FACTOR                   0x27
#define CURRENT3_REG_INT_DIODE_DATA_LOW_BYTE                       0x29
#define CURRENT3_REG_HIGH_LIMIT_STATUS                             0x35
#define CURRENT3_REG_LOW_LIMIT_STATUS                              0x36
#define CURRENT3_REG_CRIT_LIMIT_STATUS                             0x37
#define CURRENT3_REG_INT_DIODE_HIGH_BYTE                           0x38
#define CURRENT3_REG_INT_DIODE_LOW_BYTE                            0x39
#define CURRENT3_REG_EXT_DIODE_1_HIGH_BYTE                         0x3A
#define CURRENT3_REG_EXT_DIODE_1_LOW_BYTE                          0x3B
#define CURRENT3_REG_AVERAGING_CONTROL                             0x40
/** \} */

/**
 * \defgroup current_sense_ctrl_and_measurement  Current Sense Control and Measurement
 * \{
 */
#define CURRENT3_REG_VOLTAGE_SAMPLING_CFG                          0x50
#define CURRENT3_REG_CURRENT_SENSE_SAMPLING_CFG                    0x51
#define CURRENT3_REG_PEAK_DETECTION_CONFIG                         0x52
#define CURRENT3_REG_SENSE_VOLTAGE_HIGH_BYTE                       0x54
#define CURRENT3_REG_SENSE_VOLTAGE_LOW_BYTE                        0x55
#define CURRENT3_REG_SOURCE_VOLTAGE_HIGH_BYTE                      0x58
#define CURRENT3_REG_SOURCE_VOLTAGE_LOW_BYTE                       0x59
#define CURRENT3_REG_POWER_RATIO_HIGH_BYTE                         0x5B
#define CURRENT3_REG_POWER_RATIO_LOW_BYTE                          0x5C
/** \} */

/**
 * \defgroup current_sense_and_source_voltage_limits Current Sense and Source Voltage Limits
 * \{
 */
#define CURRENT3_REG_SENSE_VOLTAGE_HIGH_LIMIT                      0x60
#define CURRENT3_REG_SENSE_VOLTAGE_LOW_LIMIT                       0x61
#define CURRENT3_REG_SOURCE_VOLTAGE_HIGH_LIMIT                     0x64
#define CURRENT3_REG_SOURCE_VOLTAGE_LOW_LIMIT                      0x65
#define CURRENT3_REG_SENSE_VOLTAGE_VCRIT_LIMIT                     0x66
#define CURRENT3_REG_SOURCE_VOLTAGE_VCRIT_LIMIT                    0x68
#define CURRENT3_REG_SENSE_VCRIT_HYSTERESIS                        0x69
#define CURRENT3_REG_SOURCE_VOLTAGE_VCRIT_HYSTERESIS               0x6A
#define CURRENT3_REG_PRODUCT_FEATURES                              0xFC
#define CURRENT3_REG_PRODUCT_ID                                    0xFD
#define CURRENT3_REG_SMSC_ID                                       0xFE
#define CURRENT3_REG_REVISION                                      0xFF
/** \} */

/**
 * \defgroup device_id Device ID
 * \{
 */
#define CURRENT3_DEV_ID                                            0x39
/** \} */

/**
 * \defgroup temperature_diode_select Temperature Diode Select
 * \{
 */
#define CURRENT3_TEMP_INTERNAL_DIODE                               0x00
#define CURRENT3_TEMP_EXTERNAL_DIODE                               0x01
/** \} */

/**
 * \defgroup voltage_sampling_configuration Voltage Sampling Configuration
 * \{
 */

 /**
 * \defgroup peak_detector_circuitry Peak Detector circuitry
 * \{
 */
#define CURRENT3_PK_ALERT                                          0x00
#define CURRENT3_PK_THERM                                          0x01
/** \} */

/**
 * \defgroup voltage_queue_settings Voltage Queue Settings
 * \{
 */
#define CURRENT3_V_QUEUE_1                                         0x00
#define CURRENT3_V_QUEUE_2                                         0x01
#define CURRENT3_V_QUEUE_3                                         0x02
#define CURRENT3_V_QUEUE_4                                         0x03

#define CURRENT3_V_AVG_DISABLE                                     0x00
#define CURRENT3_V_AVG_2x                                          0x01
#define CURRENT3_V_AVG_4x                                          0x02
#define CURRENT3_V_AVG_8x                                          0x03
/** \} */
/** \} */

/**
 * \defgroup current_sense_sampling_configuration Current Sense Sampling Configuration
 * \{
 */

 /**
 * \defgroup sense_queue_settings Sense Queue Settings
 * \{
 */
#define CURRENT3_NUM_OF_CONS_OUT_LIMIT_MEASUR_1                    0x00
#define CURRENT3_NUM_OF_CONS_OUT_LIMIT_MEASUR_2                    0x01
#define CURRENT3_NUM_OF_CONS_OUT_LIMIT_MEASUR_3                    0x02
#define CURRENT3_NUM_OF_CONS_OUT_LIMIT_MEASUR_4                    0x03
/** \} */

 /**
 * \defgroup current_sense_averaging_settings Current Sense Averaging Settings
 * \{
 */
#define CURRENT3_CURRENT_SENSE_AVG_1X                              0x00
#define CURRENT3_CURRENT_SENSE_AVG_2X                              0x01
#define CURRENT3_CURRENT_SENSE_AVG_4X                              0x02
#define CURRENT3_CURRENT_SENSE_AVG_8X                              0x03
/** \} */

 /**
 * \defgroup current_sensing_sampl_time_settings Current Sensing Sampling Time Settings
 * \{
 */
#define CURRENT3_CS_SAMP_TIME_82ms                                 0x00
#define CURRENT3_CS_SAMP_TIME_164ms                                0x02
#define CURRENT3_CS_SAMP_TIME_328ms                                0x03
/** \} */

 /**
 * \defgroup current_sensing_range_settings  Current Sensing Range (Full Scale Range) Settings
 * \{
 */
#define CURRENT3_SENSOR_RANGE_BIT_MASK                             0x03
#define CURRENT3_SENSOR_RANGE_10_mV                                0x00
#define CURRENT3_SENSOR_RANGE_20_mV                                0x01
#define CURRENT3_SENSOR_RANGE_40_mV                                0x02
#define CURRENT3_SENSOR_RANGE_80_mV                                0x03
/** \} */
/** \} */

 /**
 * \defgroup configuration_register Configuration Register
 * \{
 */

 /**
 * \defgroup masks_the_alert_pin_from_asserting Masks the ALERT pin from asserting
 * \{
 */
#define CURRENT3_MASK_ALL_ALERT_NOT_MASKED                         0x00
#define CURRENT3_MASK_ALL_ALERT_INTERRUPT_MODE                     0x01
/** \} */

 /**
 * \defgroup controls_temperature_measurement_modes Controls Temperature measurement modes
 * \{
 */
#define CURRENT3_TMEAS_STOP_MEASURING_ALL                          0x00
#define CURRENT3_TMEAS_STOP_NOT_MEASURING                          0x01
/** \} */

 /**
 * \defgroup controls_the_operation_of_the_alert_pin Controls the operation of the ALERT pin
 * \{
 */
#define CURRENT3_ALERT_COMP_MODE_INTERRUPT                         0x00
#define CURRENT3_ALERT_COMP_MODE_COMPARATOR                        0x01
/** \} */

 /**
 * \defgroup disables_resistance_error_correction Disables the Resistance Error Correction (REC) for External Diode 1
 * \{
 */
#define CURRENT3_DIS_REC1_ENABLED                                  0x00
#define CURRENT3_DIS_REC1_DISABLED                                 0x01
/** \} */

 /**
 * \defgroup controls_vsense_and_vsource_measurement_modes Controls VSENSE and VSOURCE measurement modes
 * \{
 */
#define CURRENT3_IMEAS_SOURCE_SENSE_VOLTAGE_STOP_MEASUR            0x00
#define CURRENT3_IMEAS_SOURCE_SENSE_VOLTAGE_START_MEASUR           0x01
/** \} */

 /**
 * \defgroup disables_dynamic_averaging Disables the dynamic averaging feature on all temperature channels
 * \{
 */
#define CURRENT3_DAVG_DIS_ENABLED                                  0x00
#define CURRENT3_DAVG_DIS_DISABLED                                 0x01
/** \} */

 /**
 * \defgroup calculation Calculation
 * \{
 */
#define CURRENT3_SENSOR_RANGE_VALUE_10_mV                          10.0
#define CURRENT3_SENSOR_RANGE_VALUE_20_mV                          20.0
#define CURRENT3_SENSOR_RANGE_VALUE_40_mV                          40.0
#define CURRENT3_SENSOR_RANGE_VALUE_80_mV                          80.0
#define CURRENT3_DEFAULT_RSENSE                                    10.0
#define CURRENT3_FULL_SCALE_SENSE_VOLTAGE                          2047
#define CURRENT3_CON_FCT_mV_TO_V                                   1000
#define CURRENT3_SOURCE_VOLTAGE_CALC_FACT                          0.0117
#define CURRENT3_TEMPERATURE_CALC_FACT                             0.125
/** \} */
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t trm;
    digital_in_t alr;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} current3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t trm;
    pin_name_t alr;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} current3_cfg_t;

/**
 * @brief Click configuration data definition.
 */
typedef struct
{
    uint8_t mask_all;
    uint8_t tmeas_stop;
    uint8_t alert_comp;
    uint8_t dis_rec1;
    uint8_t imeas_stop;
    uint8_t davg_dis;
}
current3_cfg_data_t;

/**
 * @brief Click status data structure definition.
 */
typedef struct
{
    uint8_t busy_data;
    uint8_t peak_data;
    uint8_t high_data;
    uint8_t low_data;
    uint8_t fault_data;
    uint8_t crit_data;
}
current3_status_data_t;

/**
 * @brief Click voltage configuration structure definition.
 */
typedef struct
{
    uint8_t pk_alert_therm;
    uint8_t v_queue;
    uint8_t v_avg;
}
current3_voltage_cfg_data_t;

/**
 * @brief Click sense configuration structure definition.
 */
typedef struct
{
    uint8_t cs_queue;
    uint8_t cs_samp_avg;
    uint8_t cs_samp_time;
    uint8_t cs_rng;
}
current3_sense_cfg_data_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void current3_cfg_setup ( current3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t current3_init ( current3_t *ctx, current3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for Current3 click.
 */
void current3_default_cfg ( current3_t *ctx, current3_sense_cfg_data_t sense_cfg_data );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t current3_generic_write ( current3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function reads data from the desired register.
 */
err_t current3_generic_read ( current3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Get temperature function.
 *
 * @param ctx          Click object. 
 * @param temp_sel
 * <pre>
 * - 0x00 ( CURRENT3_TEMP_INTERNAL_DIODE ) : Internal Diode.
 * - 0x01 ( CURRENT3_TEMP_EXTERNAL_DIODE ) : External Diode.
 * </pre> 
 *
 * @returns float temperature data [ degree Celsius ].
 *
 * @details The function get the temperature by read multiple data bytes from a group of 
 * contiguous registers of the High-Side Current-Sense and Dual 1�C Temperature Monitor
 * on Current 3 Click board.
**/
float current3_get_temperature ( current3_t *ctx, uint8_t temp_sel );

/**
 * @brief Get status function.
 *
 * @param ctx           Click object. 
 * @param status_cfg    Structure where data be stored.
 *
 * @details The function get status by read data byte from a register of the High-Side 
 * Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_get_status ( current3_t *ctx, current3_status_data_t *status_cfg );

/**
 * @brief Set configuration function.
 *
 * @param ctx          Click object. 
 * @param cfg_data     Structure where data be stored.
 *
 * @details The function set the configuration by write data byte to the register of the 
 * High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_set_configuration ( current3_t *ctx,  current3_cfg_data_t cfg_data );

/**
 * @brief Get configuration function.
 *
 * @param ctx          Click object. 
 * @param cfg_data     Pointer to the memory location where data be stored.
 *
 * @details The function get the configuration by read data byte from a register of the 
 * High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_get_configuration ( current3_t *ctx,  current3_cfg_data_t *cfg_data );

/**
 * @brief Set voltage sampling configuration function.
 *
 * @param ctx             Click object. 
 * @param vtg_cfg_data    Structure where data be stored.
 *
 * @details The function set voltage sampling configuration by write data byte from a 
 * register of the High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_set_voltage_sampling_config ( current3_t *ctx, current3_voltage_cfg_data_t vtg_cfg_data );

/**
 * @brief Get voltage sampling configuration function.
 *
 * @param ctx             Click object. 
 * @param vtg_cfg_data    Pointer to the memory location where data be stored.
 *
 * @details The function get voltage sampling configuration by read data byte from a register
 * of the High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_get_voltage_sampling_config ( current3_t *ctx, current3_voltage_cfg_data_t *vtg_cfg_data );

/**
 * @brief Set sense sampling configuration function.
 *
 * @param ctx               Click object. 
 * @param sense_cfg_data    Structure where data be stored.
 *
 * @details The function set sense sampling configuration by write data byte from a register
 * of the High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_set_sense_sampling_config ( current3_t *ctx, current3_sense_cfg_data_t sense_cfg_data );

/**
 * @brief Get sense sampling configuration function.
 *
 * @param ctx               Click object.  
 * @param sense_cfg_data    Pointer to the memory location where data be stored.
 *
 * @details The function get sense sampling configurationby read data byte from a register of
 * the High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
void current3_get_sense_sampling_config ( current3_t *ctx, current3_sense_cfg_data_t *sense_cfg_data );

/**
 * @brief Get sense voltage function.
 *
 * @param ctx               Click object. 
 * 
 * @returns Vsense          12-bit ( signed ) measured VSENSE voltage.
 *
 * @details The function measured Vsense voltage across the sense resistor ( Rsense ) placed 
 * between the SENSE+ and SENSE- pins of the High-Side Current-Sense and Dual 1�C
 * Temperature Monitor on Current 3 Click board.
 *
 * @note
 * <pre>
 * The bit weighting values are for representation of the voltage relative to full scale. There 
 * is no internal scaling of data and all normal binary bit weightings still apply.
 * </pre>
**/
int16_t current3_get_sense_voltage ( current3_t *ctx );

/**
 * @brief Get source voltage function.
 *
 * @param ctx               Click object. 
 * 
 * @returns Vsource         Float measured source voltage.
 *
 * @details The function source voltage registers store the voltage measured at the SENSE+ pin
 * of the High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
**/
float current3_get_source_voltage ( current3_t *ctx );

/**
 * @brief Get current measurement function.
 *
 * @param ctx               Click object. 
 *
 * @returns Isource         Float measured current.
 *
 * @details The function current measurement measure the direction of current flow 
 * ( from SENSE+ to SENSE- or from SENSE- to SENSE+ ) of the High-Side Current-Sense and 
 * Dual 1�C Temperature Monitor on Current 3 Click board.
**/
float current3_get_current ( current3_t *ctx );

/**
 * @brief Check therm ststus function.
 *
 * @param ctx               Click object. 
 * 
 * @returns THERM state:    0 - No active;     1 - Active.
 *
 * @details Function check therm stauts by detecting temperatures drops below the Tcrit Limit
 * of the High-Side Current-Sense and Dual 1�C Temperature Monitor on Current 3 Click board.
 */
uint8_t current3_check_therm ( current3_t *ctx );

/**
 * @brief Check alert ststus function.
 *
 * @param ctx               Click object.  
 *
 * @returns ALERT state:    0 - No active;    1 - Active.
 *
 * @details Function check alert stauts of the High-Side Current-Sense and Dual 1�C
 * Temperature Monitor on Current 3 Click board.
 * 
 * @note When the ALERT pin is configured to operate in Comparator mode, it will be asserted if 
 *       any of the measured temperatures meets or exceeds the respective high limit.
 */
uint8_t current3_check_alert ( current3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CURRENT3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

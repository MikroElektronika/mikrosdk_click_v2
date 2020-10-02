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
 * \brief This file contains API for Thermo K Click driver.
 *
 * \addtogroup thermok Thermo K Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMOK_H
#define THERMOK_H

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
#define THERMOK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.al4 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.al3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.al2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.al1 = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMOK_RETVAL  uint8_t

#define THERMOK_OK           0x00
#define THERMOK_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Device slave address
 * \{
 */
#define THERMOK_DEVICE_SLAVE_ADDR_0  0x60
#define THERMOK_DEVICE_SLAVE_ADDR_1  0x61
#define THERMOK_DEVICE_SLAVE_ADDR_2  0x62
#define THERMOK_DEVICE_SLAVE_ADDR_3  0x63
#define THERMOK_DEVICE_SLAVE_ADDR_4  0x64
#define THERMOK_DEVICE_SLAVE_ADDR_5  0x65
#define THERMOK_DEVICE_SLAVE_ADDR_6  0x66
#define THERMOK_DEVICE_SLAVE_ADDR_7  0x67
/** \} */

/**
 * \defgroup register_address Register address
 * \{
 */
#define THERMOK_REG_HOT_JUNCTION_TEMP_THR     0x00
#define THERMOK_REG_JUNCTIONS_TEMP_DELTA_THR  0x01
#define THERMOK_REG_COLD_JUNCTION_TEMP_THR    0x02
#define THERMOK_REG_RAW_ADC_DATA              0x03
#define THERMOK_REG_STATUS                    0x04
#define THERMOK_REG_SENSOR_CONFIG             0x05
#define THERMOK_REG_DEVICE_CONFIG             0x06
#define THERMOK_REG_ALERT1_CONFIG             0x08
#define THERMOK_REG_ALERT2_CONFIG             0x09
#define THERMOK_REG_ALERT3_CONFIG             0x0A
#define THERMOK_REG_ALERT4_CONFIG             0x0B
#define THERMOK_REG_ALERT1_HYSTERESIS         0x0C
#define THERMOK_REG_ALERT2_HYSTERESIS         0x0D
#define THERMOK_REG_ALERT3_HYSTERESIS         0x0E
#define THERMOK_REG_ALERT4_HYSTERESIS         0x0F
#define THERMOK_REG_ALERT1_LIMIT              0x10
#define THERMOK_REG_ALERT2_LIMIT              0x11
#define THERMOK_REG_ALERT3_LIMIT              0x12
#define THERMOK_REG_ALERT4_LIMIT              0x13
#define THERMOK_REG_DEVICE_ID                 0x20
/** \} */

/**
 * \defgroup sensor_cfg Sensor configuration
 * \{
 */
#define THERMOK_SCFG_TYPE_K                0x00
#define THERMOK_SCFG_TYPE_J                0x10
#define THERMOK_SCFG_TYPE_T                0x20
#define THERMOK_SCFG_TYPE_N                0x30
#define THERMOK_SCFG_TYPE_S                0x40
#define THERMOK_SCFG_TYPE_E                0x50
#define THERMOK_SCFG_TYPE_B                0x60
#define THERMOK_SCFG_TYPE_R                0x70
#define THERMOK_SCFG_FILTER_COEFFICIENT_0  0x00
#define THERMOK_SCFG_FILTER_COEFFICIENT_1  0x01
#define THERMOK_SCFG_FILTER_COEFFICIENT_2  0x02
#define THERMOK_SCFG_FILTER_COEFFICIENT_3  0x03
#define THERMOK_SCFG_FILTER_COEFFICIENT_4  0x04
#define THERMOK_SCFG_FILTER_COEFFICIENT_5  0x05
#define THERMOK_SCFG_FILTER_COEFFICIENT_6  0x06
#define THERMOK_SCFG_FILTER_COEFFICIENT_7  0x07
/** \} */

/**
 * \defgroup device_cfg Device configuration
 * \{
 */
#define THERMOK_DCFG_COLD_JUNCTION_RES_0p0625  0x00
#define THERMOK_DCFG_COLD_JUNCTION_RES_0p25    0x80
#define THERMOK_DCFG_ADC_RES_18bit             0x00
#define THERMOK_DCFG_ADC_RES_16bit             0x20
#define THERMOK_DCFG_ADC_RES_14bit             0x40
#define THERMOK_DCFG_ADC_RES_12bit             0x60
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_1        0x00
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_2        0x04
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_4        0x08
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_8        0x0C
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_16       0x10
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_32       0x14
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_64       0x18
#define THERMOK_DCFG_NUM_TEMP_SAMPLES_128      0x1C
#define THERMOK_DCFG_MODE_NORMAL_OPERATION     0x00
#define THERMOK_DCFG_MODE_SHUTDOWN             0x01
#define THERMOK_DCFG_MODE_BURST                0x02
/** \} */

/**
 * \defgroup alert_cfg Alert configuration
 * \{
 */
#define THERMOK_ACFG_INTERRUPT_CLEAR_1      0x80
#define THERMOK_ACFG_INTERRUPT_CLEAR_0      0x00
#define THERMOK_ACFG_ALERT_MONITOR_TC       0x10
#define THERMOK_ACFG_ALERT_MONITOR_TH       0x00
#define THERMOK_ACFG_ALERT_LIMIT_RISING     0x08
#define THERMOK_ACFG_ALERT_LIMIT_FALLING    0x00
#define THERMOK_ACFG_ALERT_ACTIVE_HIGH      0x04
#define THERMOK_ACFG_ALERT_ACTIVE_LOW       0x00
#define THERMOK_ACFG_ALERT_MODE_INTERRUPT   0x02
#define THERMOK_ACFG_ALERT_MODE_COMPARATOR  0x00
#define THERMOK_ACFG_ALERT_OUT_ENABLED      0x01
#define THERMOK_ACFG_ALERT_OUT_DISABLED     0x00
/** \} */

/**
 * \defgroup alert_hysteresis ALERT Hysteresis
 * \{
 */
#define THERMOK_AHYS_HYSTERESIS_128C  0x80
#define THERMOK_AHYS_HYSTERESIS_64C   0x40
#define THERMOK_AHYS_HYSTERESIS_32C   0x20
#define THERMOK_AHYS_HYSTERESIS_16C   0x10
#define THERMOK_AHYS_HYSTERESIS_8C    0x08
#define THERMOK_AHYS_HYSTERESIS_4C    0x04
#define THERMOK_AHYS_HYSTERESIS_2C    0x02
#define THERMOK_AHYS_HYSTERESIS_1C    0x01
/** \} */

/**
 * \defgroup alert_limit ALERT limit
 * \{
 */
#define THERMOK_ALIMIT_1024C    0x4000
#define THERMOK_ALIMIT_512C     0x2000
#define THERMOK_ALIMIT_255C     0x1000
#define THERMOK_ALIMIT_128C     0x0800
#define THERMOK_ALIMIT_64C      0x0400
#define THERMOK_ALIMIT_32C      0x0200
#define THERMOK_ALIMIT_16C      0x0100
#define THERMOK_ALIMIT_8C       0x0080
#define THERMOK_ALIMIT_4C       0x0040
#define THERMOK_ALIMIT_2C       0x0020
#define THERMOK_ALIMIT_1C       0x0010
#define THERMOK_ALIMIT_0p5C     0x0008
#define THERMOK_ALIMIT_0p25C    0x0004
#define THERMOK_ALIMIT_SIGN_1   0x8000
#define THERMOK_ALIMIT_SIGN_0   0x0000
/** \} */

/**
 * \defgroup device_info Device Info
 * \{
 */
#define THERMOK_DEVICE_ID    0x40
#define THERMOK_DEVICE_REV   0x10
#define THERMOK_DEVICE_INFO  0x4010
/** \} */

/**
 * \defgroup temperatre_format Temperature format
 * \{
 */
#define THERMOK_TEMP_IN_FAHRENHEIT 0x02
#define THERMOK_TEMP_IN_KELVIN     0x01
#define THERMOK_TEMP_IN_CELSIUS    0x00
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

    digital_in_t al4;
    digital_in_t al3;
    digital_in_t al2;
    digital_in_t al1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermok_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t al4;
    pin_name_t al3;
    pin_name_t al2;
    pin_name_t al1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermok_cfg_t;

/**
 * @brief Alert structure definition.
 */
typedef struct
{
    uint8_t burst_cmp;
    uint8_t temp_h_update;
    uint8_t over_volt;
    uint8_t alert_4;
    uint8_t alert_3;
    uint8_t alert_2;
    uint8_t alert_1;

}thermok_alert_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void thermok_cfg_setup ( thermok_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMOK_RETVAL thermok_init ( thermok_t *ctx, thermok_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void thermok_generic_write ( thermok_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void thermok_generic_read ( thermok_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for read device info
 *
 * @param ctx          Click object.
 * @return device info (MSB - device ID, LSB - device rev )
 */
uint16_t thermok_get_device_info ( thermok_t *ctx );

/**
 * @brief Get status
 *
 * @param ctx          Click object.
 * @param status   Status structure
 */
void thermok_get_status ( thermok_t *ctx, thermok_alert_t *status );

/**
 * @brief Temperature data
 *
 * @param ctx            Click object.
 * @param reg            Temperature Register
 * @param temp_format    Temperature in ... (FAHRENHEIT, KELVIN or CELSIUS)
 *
 * @return Temperature data
 */
float thermok_get_temperature ( thermok_t *ctx, uint8_t reg, uint8_t temp_format );

/**
 * @brief Set register config
 *
 * @param ctx            Click object.
 * @param reg_cfg    Register type: Sensor config / Device config / Alert config
 * @param cfg_data   Data which will be set in one of three configuration registers
 */
void thermok_set_register_cfg ( thermok_t *ctx, uint8_t reg_cfg, uint8_t cfg_data );

/**
 * @brief Alert 1 pin state
 *
 * @param ctx            Click object.
 * @return Alert pin state on the INT pin
 */
uint8_t thermok_get_alert_state_1 ( thermok_t *ctx );

/**
 * @brief Alert 2 pin state
 *
 * @param ctx            Click object.
 * @return Alert pin state on the PWM pin
 */
uint8_t thermok_get_alert_state_2 ( thermok_t *ctx );

/**
 * @brief Alert 3 pin state
 *
 * @param ctx            Click object.
 * @return Alert pin state on the RST pin
 */
uint8_t thermok_get_alert_state_3 ( thermok_t *ctx );

/**
 * @brief Alert 4 pin state
 *
 * @param ctx            Click object.
 * @return Alert pin state on the AN pin
 */
uint8_t thermok_get_alert_state_4 ( thermok_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMOK_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

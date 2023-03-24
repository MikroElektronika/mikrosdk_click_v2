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
 * \brief This file contains API for Thermo J Click driver.
 *
 * \addtogroup thermoj Thermo J Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMOJ_H
#define THERMOJ_H

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
#define THERMOJ_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.alert4 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.alert3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.alert2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.alert1 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMOJ_RETVAL  uint8_t

#define THERMOJ_OK           0x00
#define THERMOJ_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Addr
 * \{
 */
#define THERMOJ_I2C_ADDR_0                                         0x60
#define THERMOJ_I2C_ADDR_1                                         0x67
/** \} */

/**
 * \defgroup config Config
 * \{
 */
#define THERMOJ_TH                                                 0x00
#define THERMOJ_TD                                                 0x01
#define THERMOJ_TC                                                 0x02
#define THERMOJ_RAW_ADC_DATA                                       0x03
#define THERMOJ_STATUS                                             0x04
#define THERMOJ_SENSOR_CONFIG                                      0x05
#define THERMOJ_DEVICE_CONFIG                                      0x06
#define THERMOJ_ALERT1_CONFIG                                      0x08
#define THERMOJ_ALERT2_CONFIG                                      0x09
#define THERMOJ_ALERT3_CONFIG                                      0x0A
#define THERMOJ_Alert4_CONFIG                                      0x0B
#define THERMOJ_THYST1                                             0x0C
#define THERMOJ_THYST2                                             0x0D
#define THERMOJ_THYST3                                             0x0E
#define THERMOJ_THYST4                                             0x0F
#define THERMOJ_TALERT1                                            0x10
#define THERMOJ_TALERT2                                            0x11
#define THERMOJ_TALERT3                                            0x12
#define THERMOJ_TALERT4                                            0x13
#define THERMOJ_DEVICE_ID                                          0x20
/** \} */

/**
 * \defgroup thermocouple_type Thermocouple Type
 * \{
 */
#define THERMOJ_THERMOCOUPLE_TYPE_K                                0x00
#define THERMOJ_THERMOCOUPLE_TYPE_J                                0x01
#define THERMOJ_THERMOCOUPLE_TYPE_T                                0x02
#define THERMOJ_THERMOCOUPLE_TYPE_N                                0x03
#define THERMOJ_THERMOCOUPLE_TYPE_S                                0x04
#define THERMOJ_THERMOCOUPLE_TYPE_E                                0x05
#define THERMOJ_THERMOCOUPLE_TYPE_B                                0x06
#define THERMOJ_THERMOCOUPLE_TYPE_R                                0x07
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

    digital_in_t alert4;
    digital_in_t alert3;
    digital_in_t alert2;
    digital_in_t alert1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermoj_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t alert4;
    pin_name_t alert3;
    pin_name_t alert2;
    pin_name_t alert1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermoj_cfg_t;

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
void thermoj_cfg_setup ( thermoj_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMOJ_RETVAL thermoj_init ( thermoj_t *ctx, thermoj_cfg_t *cfg );

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
void thermoj_generic_write ( thermoj_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void thermoj_generic_read ( thermoj_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write the byte of data function.
 *
 * @param ctx            Click object.
 * @param reg_address    Register address.
 * @param write_data     Byte of data to write.
 *
 * @description This function write the 8-bit of data to the
 * target 8-bit register address of MCP9600 sensor on Thermo J click board.
 */
void thermoj_write_byte ( thermoj_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Read the byte of data function.
 *
 * @param ctx            Click object.
 * @param reg_address    Register address.
 *
 * @description This function read the 8-bit of data from the
 * target 8-bit register address of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_read_byte ( thermoj_t *ctx, uint8_t reg_address );

/**
 * @brief Get the status function.
 *
 * @param ctx            Click object.
 *
 * @description This function read the 8-bit status data from the
 * target status register of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_status ( thermoj_t *ctx );

/**
 * @brief Check the status of burst complete function.
 *
 * @param ctx            Click object.
 *
 * @description This function check the status of burst complete data from the
 * target status register of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_check_burst_complete ( thermoj_t *ctx );

/**
 * @brief Check the status of data ready function.
 *
 * @param ctx            Click object.
 *
 * @description This function check the status of data ready data from the
 * target status register of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_check_data_ready ( thermoj_t *ctx );

/**
 * @brief Check the status of over voltage function.
 *
 * @param ctx            Click object.
 *
 * @description This function check the status of data ready data from the
 * target status register of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_check_over_voltage ( thermoj_t *ctx );

/**
 * @brief Write the byte of data function.
 *
 * @param ctx         Click object.
 * @param alert_1     Pointer of alert 1 status.
 * @param alert_2     Pointer of alert 2 status.
 * @param alert_3     Pointer of alert 3 status.
 * @param alert_4     Pointer of alert 4 status.
 *
 * @description This function check status of alerts from the
 * target status register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_check_alert_status ( thermoj_t *ctx, uint8_t *alert_1, uint8_t *alert_2, uint8_t *alert_3, uint8_t *alert_4 );

/**
 * @brief Set sensor configuration function.
 *
 * @param ctx           Click object.
 * @param config_val    8-bit configuration value.
 *
 * @description This function write sensor configuration data to the
 * target sensor configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_sensor_config ( thermoj_t *ctx, uint8_t config_val );

/**
 * @brief Set thermocouple type sensor configuration function.
 *
 * @param ctx                  Click object.
 * @param thermocouple_type    Thermocouple type value.
 *
 * @description This function write thermocouple type sensor configuration data to the
 * target sensor configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_thermocouple_type ( thermoj_t *ctx, uint8_t thermocouple_type );

/**
 * @brief Set filter coefficient sensor configuration function.
 *
 * @param ctx             Click object.
 * @param filter_coeff    Filter coefficient value.
 *
 * @description This function write filter coefficient sensor configuration data to the
 * target sensor configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_filter_coefficient ( thermoj_t *ctx, uint8_t filter_coeff );

/**
 * @brief Get sensor configuration function.
 *
 * @param ctx            Click object.
 *
 * @description This function read sensor configuration data from the
 * target sensor configuration register of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_sensor_config ( thermoj_t *ctx );

/**
 * @brief Set configuration function.
 *
 * @param ctx             Click object.
 * @param config_val      Config value.
 *
 * @description This function write configuration data to the
 * target device configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_config ( thermoj_t *ctx, uint8_t config_val );

/**
 * @brief Set cold-junction resolution function.
 *
 * @param ctx         Click object.
 * @param cj_res      Cold-junction resolution.
 *
 * @description This function write cold-junction resolution data to the
 * target device configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_cold_junction_resolution ( thermoj_t *ctx, uint8_t cj_res );

/**
 * @brief Set ADC measurement resolution function.
 *
 * @param ctx         Click object.
 * @param adc_res     ADC measurement resolution.
 *
 * @description This function write ADC measurement resolution data to the
 * target device configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_adc_resolution ( thermoj_t *ctx, uint8_t adc_res );

/**
 * @brief Set number of temperature samples function.
 *
 * @param ctx               Click object.
 * @param num_temp_samp     Number of Temperature Samples.
 *
 * @description This function write number of temperature samples data to the
 * target device configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_number_of_temperature_samples ( thermoj_t *ctx, uint8_t num_temp_samp );

/**
 * @brief Set shutdown modes function.
 *
 * @param ctx        Click object.
 * @param sd_mod     ADC measurement resolution.
 *
 * @description This function write shutdown modes data to the
 * target device configuration register of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_shutdown_modes ( thermoj_t *ctx, uint8_t sd_mod );

/**
 * @brief Write data function.
 *
 * @param ctx             Click object.
 * @param reg_address     Register address.
 * @param write_data      16-bit data to write.
 *
 * @description This function write the 16-bit of data to the
 * target 8-bit register address of MCP9600 sensor on Thermo J click board.
 */
void thermoj_write_data ( thermoj_t *ctx, uint8_t reg_address, uint16_t write_data );

/**
 * @brief Read data function.
 *
 * @param ctx             Click object.
 * @param reg_address     Register address.
 *
 * @description This function read the 16-bit of data from the
 * target 8-bit register address of MCP9600 sensor on Thermo J click board.
 */
uint16_t thermoj_read_data ( thermoj_t *ctx, uint8_t reg_address );

/**
 * @brief Get the device ID function.
 *
 * @param ctx             Click object.
 *
 * @description This function read the device ID data from the
 * target 8-bit register address of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_device_id ( thermoj_t *ctx );

/**
 * @brief Get temperature function.
 *
 * @param ctx             Click object.
 *
 * @description This function get value of temperature [ �C ] from the
 * target temperature register address of MCP9600 sensor on Thermo J click board.
 */
float thermoj_get_temperature ( thermoj_t *ctx );

/**
 * @brief Get temperature ( Fahrenheit ) function.
 *
 * @param ctx             Click object.
 *
 * @description This function get value of temperature [ �F ] from the
 * target temperature register address of MCP9600 sensor on Thermo J click board.
 */
float thermoj_get_temperature_fahrenheit ( thermoj_t *ctx );

/**
 * @brief Get temperature alert 1 function.
 *
 * @param ctx             Click object.
 *
 * @description This function get temperature alert 1 status
 * of INT pin of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_alert_1 ( thermoj_t *ctx );

/**
 * @brief Get temperature alert 2 function.
 *
 * @param ctx             Click object.
 *
 * @description This function get temperature alert 2 status
 * of INT pin of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_alert_2 ( thermoj_t *ctx );

/**
 * @brief Get temperature alert 3 function.
 *
 * @param ctx             Click object.
 *
 * @description This function get temperature alert 3 status
 * of INT pin of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_alert_3 ( thermoj_t *ctx );

/**
 * @brief Get temperature alert 4 function.
 *
 * @param ctx             Click object.
 *
 * @description This function get temperature alert 4 status
 * of INT pin of MCP9600 sensor on Thermo J click board.
 */
uint8_t thermoj_get_alert_4 ( thermoj_t *ctx );

/**
 * @brief Set temperature alert limits function.
 *
 * @param ctx                 Click object.
 * @param pos_alert           Click object.
 * @param temp_alert_limit    Click object.
 *
 * @description This function set temperature alert limits data to the
 * target temperature alert 1, 2, 3 or 4 limits register address
 * of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_alerts_limits ( thermoj_t *ctx, uint8_t pos_alert, float temp_alert_limit );

/**
 * @brief Set alert configuration function.
 *
 * @param ctx                 Click object.
 * @param pos_alert           Pos alert.
 * @param alert_config        Alert configuration value.
 *
 * @description This function set temperature alert limits data to the
 * target alert 1, 2, 3 or 4 configuration registers address
 * of MCP9600 sensor on Thermo J click board.
 */
void thermoj_set_alert_config ( thermoj_t *ctx, uint8_t pos_alert, uint8_t alert_config );

/**
 * @brief Enable alerts function.
 *
 * @param ctx                 Click object.
 * @param pos_alert           Pos alert.
 *
 * @description This function enable alert by set alert bits in the
 * target alert 1, 2, 3 or 4 configuration registers address
 * of MCP9600 sensor on Thermo J click board.
 */
void thermoj_enable_alert ( thermoj_t *ctx, uint8_t pos_alert );

/**
 * @brief Disable alerts function.
 *
 * @param ctx                 Click object.
 * @param pos_alert           Pos alert.
 *
 * @description This function disable alert by clear alert bits in the
 * target alert 1, 2, 3 or 4 configuration registers address
 * of MCP9600 sensor on Thermo J click board.
 */
void thermoj_disable_alert ( thermoj_t *ctx, uint8_t pos_alert );

#ifdef __cplusplus
}
#endif
#endif  // _THERMOJ_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

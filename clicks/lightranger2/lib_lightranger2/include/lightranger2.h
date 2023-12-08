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
 * \brief This file contains API for LightRanger 2 Click driver.
 *
 * \addtogroup lightranger2 LightRanger 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LIGHTRANGER2_H
#define LIGHTRANGER2_H

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
#define LIGHTRANGER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LIGHTRANGER2_RETVAL  uint8_t

#define LIGHTRANGER2_OK           0x00
#define LIGHTRANGER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define LIGHTRANGER2_I2C_ADDR                                      0x29
/** \} */

/**
 * \defgroup sys_range_start System Range Start
 * \{
 */
#define LIGHTRANGER2_SYSRANGE_START                                0x00
 /** \} */

/**
* \defgroup system_threshold System Threshold
* \{
*/
#define LIGHTRANGER2_SYSTEM_THRESH_HIGH                            0x0C
#define LIGHTRANGER2_SYSTEM_THRESH_LOW                             0x0E
/** \} */

/**
* \defgroup system_configuration System Configuration
* \{
*/
#define LIGHTRANGER2_SYSTEM_SEQUENCE_CONFIG                        0x01
#define LIGHTRANGER2_SYSTEM_RANGE_CONFIG                           0x09
#define LIGHTRANGER2_SYSTEM_INTERMEASUREMENT_PERIOD                0x04
/** \} */

/**
* \defgroup system_interrupt System Interrupt
* \{
*/
#define LIGHTRANGER2_SYSTEM_INTERRUPT_CONFIG_GPIO                  0x0A
/** \} */

/**
* \defgroup gpio GPIO
* \{
*/
#define LIGHTRANGER2_GPIO_HV_MUX_ACTIVE_HIGH                       0x84
/** \} */

/**
* \defgroup system_interrupt System Interrupt
* \{
*/
#define LIGHTRANGER2_SYSTEM_INTERRUPT_CLEAR                        0x0B
/** \} */

/**
* \defgroup results Results
* \{
*/
#define LIGHTRANGER2_RESULT_INTERRUPT_STATUS                       0x13
#define LIGHTRANGER2_RESULT_RANGE_STATUS                           0x14
/** \} */

/**
* \defgroup result_core Result Core
* \{
*/
#define LIGHTRANGER2_RESULT_CORE_AMBIENT_WINDOW_EVENTS_RTN         0xBC
#define LIGHTRANGER2_RESULT_CORE_RANGING_TOTAL_EVENTS_RTN          0xC0
#define LIGHTRANGER2_RESULT_CORE_AMBIENT_WINDOW_EVENTS_REF         0xD0
#define LIGHTRANGER2_RESULT_CORE_RANGING_TOTAL_EVENTS_REF          0xD4
#define LIGHTRANGER2_RESULT_PEAK_SIGNAL_RATE_REF                   0xB6
/** \} */

/**
* \defgroup range_offset Range Offset
* \{
*/
#define LIGHTRANGER2_ALGO_PART_TO_PART_RANGE_OFFSET_MM             0x28
/** \} */

/**
* \defgroup  config_control Configuration Control
* \{
*/
#define LIGHTRANGER2_MSRC_CONFIG_CONTROL                           0x60
/** \} */

/**
* \defgroup  pre_range Pre Range
* \{
*/
#define LIGHTRANGER2_PRE_RANGE_CONFIG_MIN_SNR                      0x27
#define LIGHTRANGER2_PRE_RANGE_CONFIG_VALID_PHASE_LOW              0x56
#define LIGHTRANGER2_PRE_RANGE_CONFIG_VALID_PHASE_HIGH             0x57
#define LIGHTRANGER2_PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT            0x64
/** \} */

/**
* \defgroup  final_range Final Range
* \{
*/
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_MIN_SNR                    0x67
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_VALID_PHASE_LOW            0x47
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_VALID_PHASE_HIGH           0x48
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT   0x44
/** \} */

/**
* \defgroup pre_range_threshold Pre Range Threshold
* \{
*/
#define LIGHTRANGER2_PRE_RANGE_CONFIG_SIGMA_THRESH_HI              0x61
#define LIGHTRANGER2_PRE_RANGE_CONFIG_SIGMA_THRESH_LO              0x62
/** \} */

/**
* \defgroup pre_range_timeout Pre Range Timeout
* \{
*/
#define LIGHTRANGER2_PRE_RANGE_CONFIG_VCSEL_PERIOD                 0x50
#define LIGHTRANGER2_PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI            0x51
#define LIGHTRANGER2_PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO            0x52
/** \} */

/**
* \defgroup histogram Histogram
* \{
*/
#define LIGHTRANGER2_SYSTEM_HISTOGRAM_BIN                          0x81
#define LIGHTRANGER2_HISTOGRAM_CONFIG_INITIAL_PHASE_SELECT         0x33
#define LIGHTRANGER2_HISTOGRAM_CONFIG_READOUT_CTRL                 0x55
/** \} */

/**
* \defgroup final_range Final Range
* \{
*/
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_VCSEL_PERIOD               0x70
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI          0x71
#define LIGHTRANGER2_FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO          0x72
#define LIGHTRANGER2_CROSSTALK_COMPENSATION_PEAK_RATE_MCPS         0x20
/** \} */

/**
* \defgroup msrc_configuration Msrc Configuration
* \{
*/
#define LIGHTRANGER2_MSRC_CONFIG_TIMEOUT_MACROP                    0x46
/** \} */

/**
* \defgroup identification Identification
* \{
*/
#define LIGHTRANGER2_SOFT_RESET_GO2_SOFT_RESET_N                   0xBF
#define LIGHTRANGER2_IDENTIFICATION_MODEL_ID                       0xC0
#define LIGHTRANGER2_IDENTIFICATION_REVISION_ID                    0xC2
/** \} */

/**
* \defgroup calibrate Calibrate
* \{
*/
#define LIGHTRANGER2_OSC_CALIBRATE_VAL                             0xF8
/** \} */

/**
* \defgroup global_configuration Global Configuration
* \{
*/
#define LIGHTRANGER2_GLOBAL_CONFIG_VCSEL_WIDTH                     0x32
#define LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_0              0xB0
#define LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_1              0xB1
#define LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_2              0xB2
#define LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_3              0xB3
#define LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_4              0xB4
#define LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_5              0xB5
/** \} */

/**
* \defgroup dynamic_spad Dynamic Spad
* \{
*/
#define LIGHTRANGER2_GLOBAL_CONFIG_REF_EN_START_SELECT             0xB6
#define LIGHTRANGER2_DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD           0x4E
#define LIGHTRANGER2_DYNAMIC_SPAD_REF_EN_START_OFFSET              0x4F
#define LIGHTRANGER2_POWER_MANAGEMENT_GO1_POWER_FORCE              0x80
/** \} */

/**
* \defgroup vhv_config VHV Config
* \{
*/
#define LIGHTRANGER2_VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV             0x89
/** \} */

/**
* \defgroup algo_phasecal Algo Phasecal
* \{
*/
#define LIGHTRANGER2_ALGO_PHASECAL_LIM                             0x30
#define LIGHTRANGER2_ALGO_PHASECAL_CONFIG_TIMEOUT                  0x30
/** \} */

/**
* \defgroup status Status
* \{
*/
#define LIGHTRANGER2_STATUS_ERR                                             0x00
#define LIGHTRANGER2_STATUS_OK                                              0x01
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
   
    digital_out_t en;

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint32_t milliseconds_counter;
    uint16_t io_timeout;
    uint8_t did_timeout;
    uint16_t timeout_start_ms;

} lightranger2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 


    pin_name_t en;

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;


} lightranger2_cfg_t;

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
void lightranger2_cfg_setup ( lightranger2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param lightranger2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LIGHTRANGER2_RETVAL lightranger2_init ( lightranger2_t *ctx, lightranger2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for LightRanger2 click.
 */
LIGHTRANGER2_RETVAL lightranger2_default_cfg ( lightranger2_t *ctx );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx            Click object.
 * @param reg_address    8-bit register address.
 * @param write_data     8-bit data to write.
 *
 * @description This function writes a byte of data to the targeted 8-bit register
 * address of the VL53L0X ranging and gesture detection sensor on the LightRanger
 * 2 click board.
 */
void lightranger2_write_byte ( lightranger2_t* ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx            Click object.
 * @param reg_address    8-bit register address.
 *
 * @returns 8-bit read data.
 *
 * @description Function reads a byte of data from the targeted 8-bit register 
 * address of the VL53L0X ranging and gesture detection sensor on the LightRanger
 * 2 click board.
 */
uint8_t lightranger2_read_byte ( lightranger2_t* ctx, uint8_t reg_address );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx            Click object.
 * @param reg_address    8-bit register address.
 * @param write_data     16-bit data to write.
 *
 * @description This function writes the 16-bit data to the targeted 8-bit register
 * address of the VL53L0X ranging and gesture detection sensor on the LightRanger
 * 2 click board.
 */
void lightranger2_write_data ( lightranger2_t* ctx, uint8_t reg_address, uint16_t write_data );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx            Click object.
 * @param reg_address    8-bit register address.
 *
 * @returns 16-bit read data.
 *
 * @description Function reads the 16-bit data from the targeted 8-bit register
 * address of the VL53L0X ranging and gesture detection sensor on the LightRanger
 * 2 click board.
 */
uint16_t lightranger2_read_data ( lightranger2_t* ctx, uint8_t reg_address );

/**
 * @brief Generic sequential data write function
 *
 * @param ctx            Click object.
 * @param reg_address                8-bit register address
 * @param write_data                 pointer to the data to be written
 * @param n_bytes                    number of bytes to be written
 *
 * @description Function writes a sequential data starting to the
 * targeted 8-bit register address of the
 * VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
void lightranger2_write_bytes ( lightranger2_t* ctx, uint8_t reg_address, uint8_t* write_data, uint8_t n_bytes );

/**
 * @brief Generic sequential data read function
 *
 * @param ctx            Click object.
 * @param reg_address                8-bit register address
 * @param read_data                 pointer to the memory location where data be stored
 * @param n_bytes                    number of bytes to be written
 *
 * @description Function read a sequential data starting from the
 * targeted 8-bit register address of the
 * VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
void lightranger2_read_bytes ( lightranger2_t* ctx, uint8_t reg_address, uint8_t* read_data, uint8_t n_bytes );

/**
 * @brief Hardware reset function
 *
 * @param ctx            Click object.
 *
 * @description Function hardware reset the VL53L0X ranging and gesture detection sensor
 * by cleared to '0' states of RST pin, wait 100 ms,
 * sets to '1' states of RST pin and wait for another 100 ms.
 *
 * @note
 * Delay is 200 ms.
 */
void lightranger2_hw_reset ( lightranger2_t* ctx );

/**
 * @brief Enable function
 *
 * @param ctx            Click object.
 *
 * @description Function enable VL53L0X ranging and gesture detection sensor
 * by sets to '1' states of RST pin
 * of the LightRanger 2 click board.
 */
void lightranger2_enable ( lightranger2_t* ctx );

/**
 * @brief Disable function
 *
 * @param ctx            Click object.
 *
 * @description Function disable VL53L0X ranging and gesture detection sensor
 * by cleared to '0' states of RST pin
 * of the LightRanger 2 click board.
 */
void lightranger2_disable ( lightranger2_t* ctx );

/**
 * @brief Get interrupt state function
 *
 * @param ctx            Click object.
 *
 * @return interrupt state
 * - 0 : not active
 * - 1 : active
 *
 * @description The function gets interrupt state
 * by return status of INT pin of the
 * LightRanger 2 click board.
 */
uint8_t lightranger2_get_interrupt ( lightranger2_t* ctx );

/**
 * @brief Start continuous ranging measurements function
 *
 * @param ctx            Click object.
 * @param period_ms                32-bit period in ms
 *
 * @description Function start continuous ranging measurements of the
 * VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
void lightranger2_start_continuous ( lightranger2_t* ctx, uint32_t period_ms );

/**
 * @brief Stop continuous measurements function
 *
 * @param ctx            Click object.
 *
 * @description Function stop continuous ranging measurements of the
 * VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
void lightranger2_stop_continuous ( lightranger2_t* ctx );

/**
 * @brief Set the signal rate limit check value function
 *
 * @param ctx            Click object.
 * @param period_ms      float signal rate limit check value
 *
 * @return status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description Function sets the limit presumably determines
 * the minimum measurement necessary for the sensor to report a valid reading
 * of the VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
LIGHTRANGER2_RETVAL lightranger2_set_signal_rate_limit ( lightranger2_t* ctx,
                                                         float limit_mcps );

/**
 * @brief Get the signal rate limit check value function
 *
 * @param ctx         Click object.
 *
 * @return
 * float signal rate limit check value
 *
 * @description Function gets the signal rate limit check value of the
 * VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
float lightranger2_get_signal_rate_limit ( lightranger2_t* ctx );

/**
 * @brief Get reference SPAD ( single photon avalanche diode ) function
 *
 * @param ctx                      Click object.
 * @param count_data               pointer to the memory location where count data data be stored
 * @param aperture_Type            pointer to the memory location where aperture type data be stored
 *
 * @return status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description Function get reference SPAD ( single photon avalanche diode )
 * count and type of the
 * VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
LIGHTRANGER2_RETVAL lightranger2_get_spad_info ( lightranger2_t* ctx, 
                                                 uint8_t* count_data, 
                                                 uint8_t* aperture_type );

/**
 * @brief Perform single reference calibration function
 *
 * @param ctx                        Click object.
 * @param vhv_init_byte              8-bit vhv init byte
 *
 * @return status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description Function perform single reference calibration
 * of the VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
LIGHTRANGER2_RETVAL lightranger2_single_calibration ( lightranger2_t* ctx,
                                                      uint8_t vhv_init_byte );

/**
 * @brief Get a range measurement ( continuous mode ) function
 *
 * @param ctx         Click object.
 *
 * @return
 * 16-bit range measurement in millimeters value
 *
 * @description Function gets a range measurement in millimeters when continuous mode is active
 * of the VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
uint16_t lightranger2_get_range_continuous ( lightranger2_t* ctx );

/**
 * @brief Get a range measurement ( single mode ) function
 *
 * @param ctx       Click object.
 *
 * @return
 * 16-bit range measurement in millimeters value
 *
 * @description Function gets a range measurement in millimeters when single mode is active
 * of the VL53L0X ranging and gesture detection sensor
 * on the LightRanger 2 click board.
 */
uint16_t lightranger2_get_range_single ( lightranger2_t* ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LIGHTRANGER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

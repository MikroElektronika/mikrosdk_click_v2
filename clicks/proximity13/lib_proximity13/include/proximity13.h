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
 * \brief This file contains API for Proximity 13 Click driver.
 *
 * \addtogroup proximity13 Proximity 13 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY13_H
#define PROXIMITY13_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define PROXIMITY13_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY13_RETVAL  uint8_t

#define PROXIMITY13_OK                                  0x00
#define PROXIMITY13_INIT_ERROR                          0xFF
#define PROXIMITY13_ERROR                               0xEE
/** \} */

/**
 * \defgroup slave_address Slave address of device
 * \{
 */
#define PROXIMITY13_SLAVE_ADDRESS                       0x53 
/** \} */

/**
 * \defgroup device_registers Device registers
 * \{
 */         
#define PROXIMITY13_REG_PART_ID                         0x00 
#define PROXIMITY13_REG_HW_ID                           0x01 
#define PROXIMITY13_REG_REV_ID                          0x02 
#define PROXIMITY13_REG_INFO_0                          0x03
#define PROXIMITY13_REG_INFO_1                          0x04 
#define PROXIMITY13_REG_HOSTIN_0                        0x0A
#define PROXIMITY13_REG_COMMAND                         0x0B
#define PROXIMITY13_REG_IRQ_ENABLE                      0x0F
#define PROXIMITY13_REG_RESPONSE_1                      0x10 
#define PROXIMITY13_REG_RESPONSE_0                      0x11 
#define PROXIMITY13_REG_IRQ_STATUS                      0x12
#define PROXIMITY13_REG_HOSTOUT_0                       0x13 
#define PROXIMITY13_REG_HOSTOUT_1                       0x14 
#define PROXIMITY13_REG_HOSTOUT_2                       0x15 
#define PROXIMITY13_REG_HOSTOUT_3                       0x16 
#define PROXIMITY13_REG_HOSTOUT_4                       0x17 
#define PROXIMITY13_REG_HOSTOUT_5                       0x18 
#define PROXIMITY13_REG_HOSTOUT_6                       0x19 
#define PROXIMITY13_REG_HOSTOUT_7                       0x1A 
#define PROXIMITY13_REG_HOSTOUT_8                       0x1B 
#define PROXIMITY13_REG_HOSTOUT_9                       0x1C 
#define PROXIMITY13_REG_HOSTOUT_10                      0x1D 
#define PROXIMITY13_REG_HOSTOUT_11                      0x1E 
#define PROXIMITY13_REG_HOSTOUT_12                      0x1F 
#define PROXIMITY13_REG_HOSTOUT_13                      0x20 
#define PROXIMITY13_REG_HOSTOUT_14                      0x21 
#define PROXIMITY13_REG_HOSTOUT_15                      0x22 
#define PROXIMITY13_REG_HOSTOUT_16                      0x23 
#define PROXIMITY13_REG_HOSTOUT_17                      0x24 
#define PROXIMITY13_REG_HOSTOUT_18                      0x25 
#define PROXIMITY13_REG_HOSTOUT_19                      0x26 
#define PROXIMITY13_REG_HOSTOUT_20                      0x27 
#define PROXIMITY13_REG_HOSTOUT_21                      0x28 
#define PROXIMITY13_REG_HOSTOUT_22                      0x29 
#define PROXIMITY13_REG_HOSTOUT_23                      0x2A 
#define PROXIMITY13_REG_HOSTOUT_24                      0x2B 
#define PROXIMITY13_REG_HOSTOUT_25                      0x2C 
/** \} */

/**
 * \defgroup parameter_addresses    Parameter addresses
 * \{
 */
#define PROXIMITY13_PARAMETER_I2C_ADDR                  0x00
#define PROXIMITY13_PARAMETER_CHAN_LIST                 0x01
#define PROXIMITY13_PARAMETER_ADCCONFIG_0               0x02
#define PROXIMITY13_PARAMETER_ADCSENS_0                 0x03
#define PROXIMITY13_PARAMETER_ADCPOST_0                 0x04
#define PROXIMITY13_PARAMETER_MEASCONFIG_0              0x05
#define PROXIMITY13_PARAMETER_ADCCONFIG_1               0x06
#define PROXIMITY13_PARAMETER_ADCSENS_1                 0x07
#define PROXIMITY13_PARAMETER_ADCPOST_1                 0x08
#define PROXIMITY13_PARAMETER_MEASCONFIG_1              0x09
#define PROXIMITY13_PARAMETER_ADCCONFIG_2               0x0A
#define PROXIMITY13_PARAMETER_ADCSENS_2                 0x0B
#define PROXIMITY13_PARAMETER_ADCPOST_2                 0x0C
#define PROXIMITY13_PARAMETER_MEASCONFIG_2              0x0D
#define PROXIMITY13_PARAMETER_ADCCONFIG_3               0x0E
#define PROXIMITY13_PARAMETER_ADCSENS_3                 0x0F
#define PROXIMITY13_PARAMETER_ADCPOST_3                 0x10
#define PROXIMITY13_PARAMETER_MEASCONFIG_3              0x11
#define PROXIMITY13_PARAMETER_ADCCONFIG_4               0x12
#define PROXIMITY13_PARAMETER_ADCSENS_4                 0x13
#define PROXIMITY13_PARAMETER_ADCPOST_4                 0x14
#define PROXIMITY13_PARAMETER_MEASCONFIG_4              0x15
#define PROXIMITY13_PARAMETER_ADCCONFIG_5               0x16
#define PROXIMITY13_PARAMETER_ADCSENS_5                 0x17
#define PROXIMITY13_PARAMETER_ADCPOST_5                 0x18
#define PROXIMITY13_PARAMETER_MEASCONFIG_5              0x19
#define PROXIMITY13_PARAMETER_MEASRATE_H                0x1A
#define PROXIMITY13_PARAMETER_MEASRATE_L                0x1B
#define PROXIMITY13_PARAMETER_MEASCOUNT_0               0x1C
#define PROXIMITY13_PARAMETER_MEASCOUNT_1               0x1D
#define PROXIMITY13_PARAMETER_MEASCOUNT_2               0x1E
#define PROXIMITY13_PARAMETER_LED1_A                    0x1F
#define PROXIMITY13_PARAMETER_LED1_B                    0x20
#define PROXIMITY13_PARAMETER_LED2_A                    0x21
#define PROXIMITY13_PARAMETER_LED2_B                    0x22
#define PROXIMITY13_PARAMETER_LED3_A                    0x23
#define PROXIMITY13_PARAMETER_LED3_B                    0x24
#define PROXIMITY13_PARAMETER_THRESHOLD0_H              0x25
#define PROXIMITY13_PARAMETER_THRESHOLD0_L              0x26
#define PROXIMITY13_PARAMETER_THRESHOLD1_H              0x27
#define PROXIMITY13_PARAMETER_THRESHOLD1_L              0x28
#define PROXIMITY13_PARAMETER_THRESHOLD2_H              0x29
#define PROXIMITY13_PARAMETER_THRESHOLD2_L              0x2A
#define PROXIMITY13_PARAMETER_BURST                     0x2B
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define PROXIMITY13_CMD_RESET_CTR                       0x00
#define PROXIMITY13_CMD_RESET_SW                        0x01
#define PROXIMITY13_CMD_FORCE                           0x11
#define PROXIMITY13_CMD_PAUSE                           0x12
#define PROXIMITY13_CMD_START                           0x13
/** \} */

/**
 * \defgroup dev_ids    Device IDs
 * \{
 */
#define PROXIMITY13_DEV_ID_VAL                          0x53
#define PROXIMITY13_HW_ID_VAL                           0x01
#define PROXIMITY13_REV_ID_VAL                          0x11
/** \} */

/**
 * \defgroup adc_cfg ADC configuration values
 * \{
 */  
#define PROXIMITY13_ADC_CFG_RATE_48p8_US                0x00
#define PROXIMITY13_ADC_CFG_RATE_97p6_US                0x20
#define PROXIMITY13_ADC_CFG_RATE_195_US                 0x40
#define PROXIMITY13_ADC_CFG_RATE_24p4_US                0x60
#define PROXIMITY13_ADC_CFG_MUX_SMALL_IR                0x00
#define PROXIMITY13_ADC_CFG_MUX_MEDIUM_IR               0x01
#define PROXIMITY13_ADC_CFG_MUX_LARGE_IR                0x02
#define PROXIMITY13_ADC_CFG_MUX_WHITE                   0x0B
#define PROXIMITY13_ADC_CFG_MUX_LARGE_WHITE             0x0D
/** \} */

/**
 * \defgroup adc_sens ADC seonsor values
 * \{
 */ 
#define PROXIMITY13_ADC_SENS_SW_GAIN_1                  0x00
#define PROXIMITY13_ADC_SENS_SW_GAIN_2                  0x10
#define PROXIMITY13_ADC_SENS_SW_GAIN_4                  0x20
#define PROXIMITY13_ADC_SENS_SW_GAIN_8                  0x30
#define PROXIMITY13_ADC_SENS_SW_GAIN_16                 0x40
#define PROXIMITY13_ADC_SENS_SW_GAIN_32                 0x50
#define PROXIMITY13_ADC_SENS_SW_GAIN_64                 0x60
#define PROXIMITY13_ADC_SENS_SW_GAIN_128                0x70
#define PROXIMITY13_ADC_SENS_HW_GAIN_MIN_24p4_US        0x00
#define PROXIMITY13_ADC_SENS_HW_GAIN_MAX_50_MS          0x0B
/** \} */

/**
 * \defgroup adc_post   ADC post values
 * \{
 */
#define PROXIMITY13_ADC_POST_RESOLUTION_16              0x00
#define PROXIMITY13_ADC_POST_RESOLUTION_24              0x40
#define PROXIMITY13_ADC_POST_INT_MORE_THEN_THRESH       0x00
#define PROXIMITY13_ADC_POST_INT_LESS_THEN_THRESH       0x04
#define PROXIMITY13_ADC_POST_INT_NO_TRESH               0x00
#define PROXIMITY13_ADC_POST_INT_THRESHOLD_0_EN         0x01
#define PROXIMITY13_ADC_POST_INT_THRESHOLD_1_EN         0x02
#define PROXIMITY13_ADC_POST_INT_BETWEEN_TRESHOLD       0x03
/** \} */

/**
 * \defgroup measure_cfg Measurement configuration
 * \{
 */ 
#define PROXIMITY13_MEAS_CFG_BURST_ONLY                 0x00
#define PROXIMITY13_MEAS_CFG_MEASCOUNT0                 0x40
#define PROXIMITY13_MEAS_CFG_MEASCOUNT1                 0x80
#define PROXIMITY13_MEAS_CFG_MEASCOUNT2                 0xC0
#define PROXIMITY13_MEAS_CFG_NOMINAL_LED                0x00
#define PROXIMITY13_MEAS_CFG_LED_UNDEFINED              0x10
#define PROXIMITY13_MEAS_CFG_LED_INC_9_PCT              0x20
#define PROXIMITY13_MEAS_CFG_LED_INC_10_PCT             0x30
#define PROXIMITY13_MEAS_CFG_LED_A                      0x00
#define PROXIMITY13_MEAS_CFG_LED_B                      0x08
#define PROXIMITY13_MEAS_CFG_LED_2                      0x04
#define PROXIMITY13_MEAS_CFG_LED_3                      0x02
#define PROXIMITY13_MEAS_CFG_LED_1                      0x01
/** \} */

/**
 * \defgroup pin_state Pin state
 * \{
 */
#define PROXIMITY13_PIN_HIGH                            1
#define PROXIMITY13_PIN_LOW                             0
/** \} */

/**
 * \defgroup channels_macro  Channels marcro
 * \{
 */
#define PROXIMITY13_CHANNEL_0                           0x01
#define PROXIMITY13_CHANNEL_1                           0x02
#define PROXIMITY13_CHANNEL_2                           0x04
#define PROXIMITY13_CHANNEL_3                           0x08
#define PROXIMITY13_CHANNEL_4                           0x10
#define PROXIMITY13_CHANNEL_5                           0x20
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} proximity13_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} proximity13_cfg_t;

/**
 * @brief Structure for configurating device
 */
typedef struct
{
  uint8_t adc_cfg;
  uint8_t adc_sens;
  uint8_t adc_post;
  uint8_t measure_cfg;
}proximity13_config_t;

/**
 * @brief Structure for reading values of channels
 */
typedef struct
{
  uint32_t channel_0;
  uint32_t channel_1;
  uint32_t channel_2;
  uint32_t channel_3;
  uint32_t channel_4;
  uint32_t channel_5;
}proximity13_chn_val_t;

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
void proximity13_cfg_setup ( proximity13_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY13_RETVAL proximity13_init ( proximity13_t *ctx, proximity13_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity13 click.
 */
void proximity13_default_cfg ( proximity13_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg_adr      Register address.
 * @param write_data   Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void proximity13_generic_write ( proximity13_t *ctx, uint8_t reg_adr, uint8_t write_data );

/**
 * @brief Generic read function.
 *
 * @param   ctx             Click object.
 * @param   reg_adr         Register address.
 * 
 * @returns Returns read data
 *
 * @description This function reads data from the desired register.
 */
uint8_t proximity13_generic_read ( proximity13_t *ctx, uint8_t reg_adr );

/**
 * @brief Checks status of int pin.
 *
 * @param    ctx             Click object.
 *
 * @returns 0 or 1.
 *
 * @description This function returns the state of the int pin.
 */
uint8_t proximity13_get_int_pin_status ( proximity13_t *ctx );

/**
 * @brief Sends command to command register
 * 
 * @param    ctx               Click object.
 * @param    cmd_val           sending value
 * 
 * @return Parameter query
 * 
 * @description This function sends command to command register
 */
uint8_t proximity13_send_command ( proximity13_t *ctx, uint8_t cmd_val );

/**
 * @brief Sets parameter
 * 
 * @param    ctx             Click object.
 * @param    param           parameter
 * @param    cmd_val         sending value
 * 
 * @return Returns OK if function is done
 * 
 * @description This function sets paramter
 */
uint8_t proximity13_set_parameter ( proximity13_t *ctx, uint8_t param, uint8_t cmd_val );

/**
 * @brief Configuration of channel
 * 
 * @param    ctx              Click object.
 * @param    chn_num          channel number
 * @param    cfg_val          configuration struct value
 * 
 * @return Returns OK if function is done
 * 
 * @description This function configurates specific channel
 */
uint8_t porximity13_config_channel ( proximity13_t *ctx, uint8_t chn_num, proximity13_config_t cfg_val );

/**
 * @brief Checks id of the device
 * 
 * @param    ctx             Click object.
 * 
 * @return Returns OK or ERROR status macro
 * 
 * @description This function checks ID
 */
uint8_t porximity13_check_id ( proximity13_t *ctx );

/**
 * @brief Reads all enabled channels
 * 
 * @param    ctx              Click object.
 * @param    chn_val          channel value structure
 * 
 * @description This function reads all enabled channels
 */
void proximity13_read_channels ( proximity13_t *ctx, proximity13_chn_val_t *chn_val );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY13_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

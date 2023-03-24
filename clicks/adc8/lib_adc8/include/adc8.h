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
 * \brief This file contains API for ADC 8 Click driver.
 *
 * \addtogroup adc8 ADC 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC8_H
#define ADC8_H

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
#define ADC8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC8_RETVAL  uint8_t

#define ADC8_OK           0x00
#define ADC8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers (commands)
 * \{
 */
#define ADC8_REG_CONFIGURATION   0x01
#define ADC8_REG_CONVERSION      0x00
#define ADC8_REG_THRESHOLD_LOW   0x02
#define ADC8_REG_THRESHOLD_HIGH  0x03
/** \} */

/**
 * \defgroup config Configuration
 * \{
 */
#define ADC8_CFG_CONVERSION_ENABLE   0x0000
#define ADC8_CFG_CONVERSION_DISABLE  0x8000
/** \} */

/**
 * \defgroup mux Mux
 * \{
 */
#define ADC8_CFG_MUX_AINP0_AINN1   0x0000
#define ADC8_CFG_MUX_AINP0_AINN3   0x1000
#define ADC8_CFG_MUX_AINP1_AINN3   0x2000
#define ADC8_CFG_MUX_AINP2_AINN3   0x3000
#define ADC8_CFG_MUX_AINP0_GND     0x4000
#define ADC8_CFG_MUX_AINP1_GND     0x5000
#define ADC8_CFG_MUX_AINP2_GND     0x6000
#define ADC8_CFG_MUX_AINP3_GND     0x7000
/** \} */

/**
 * \defgroup gain Gain
 * \{
 */
#define ADC8_CFG_GAIN_6144mV   0x0000
#define ADC8_CFG_GAIN_4096mV   0x0200
#define ADC8_CFG_GAIN_2048mV   0x0400
#define ADC8_CFG_GAIN_1024mV   0x0600
#define ADC8_CFG_GAIN_512mV    0x0800
#define ADC8_CFG_GAIN_256mV    0x0A00
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define ADC8_CFG_MODE_CONTINUOUS  0x0000
#define ADC8_CFG_MODE_SINGLE      0x0100
/** \} */

/**
 * \defgroup data_rate Data Rate
 * \{
 */
#define ADC8_CFG_SPS_8    0x0000
#define ADC8_CFG_SPS_16   0x0020
#define ADC8_CFG_SPS_32   0x0040
#define ADC8_CFG_SPS_64   0x0060
#define ADC8_CFG_SPS_128  0x0080
#define ADC8_CFG_SPS_250  0x00A0
#define ADC8_CFG_SPS_475  0x00C0
#define ADC8_CFG_SPS_860  0x00E0
/** \} */

/**
 * \defgroup comparator_mode Comparator mode
 * \{
 */
#define ADC8_CFG_COMP_MODE_TRADITIONAL  0x0000
#define ADC8_CFG_COMP_MODE_WINDOW       0x0010
/** \} */

/**
 * \defgroup comparator_polarity Comparator polarity
 * \{
 */
#define ADC8_CFG_COMP_POL_LOW    0x0000
#define ADC8_CFG_COMP_POL_HIGH   0x0008
/** \} */

/**
 * \defgroup comparator_latching Comparator Latching
 * \{
 */
#define ADC8_CFG_COMP_LAT_ENABLE    0x0000
#define ADC8_CFG_COMP_LAT_DISABLE   0x0004

#define ADC8_CFG_COMP_QUE_1_CONV       0x0000
#define ADC8_CFG_COMP_QUE_2_CONV       0x0001
#define ADC8_CFG_COMP_QUE_4_CONV       0x0002
#define ADC8_CFG_COMP_QUE_ALERT_CONV   0x0003
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define ADC8_DEVICE_SLAVE_ADDR_GND 0x48
#define ADC8_DEVICE_SLAVE_ADDR_VDD 0x49
#define ADC8_DEVICE_SLAVE_ADDR_SDA 0x4A
#define ADC8_DEVICE_SLAVE_ADDR_SCL 0x4B
/** \} */

/**
 * \defgroup channel Channel
 * \{
 */
#define ADC8_SINGLE_CHANNEL_0  0x00
#define ADC8_SINGLE_CHANNEL_1  0x01
#define ADC8_SINGLE_CHANNEL_2  0x02
#define ADC8_SINGLE_CHANNEL_3  0x03
#define ADC8_DIFF_CHANNEL_0_1  0x04
#define ADC8_DIFF_CHANNEL_0_3  0x05
#define ADC8_DIFF_CHANNEL_1_3  0x06
#define ADC8_DIFF_CHANNEL_2_3  0x07
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

    float max_voltage;
    uint16_t cfg_reg_value;
    uint8_t diff_flag;

} adc8_t;

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

} adc8_cfg_t;

/**
 * @brief Single channel (volt) type
 */
typedef struct
{
    float ch_0;
    float ch_1;
    float ch_2;
    float ch_3;

} adc8_single_volt_t;

/**
 * @brief Diff channel (volt) type
 */
typedef struct
{
    float ch_0_1;
    float ch_0_3;
    float ch_1_3;
    float ch_2_3;

} adc8_diff_volt_t;

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
void adc8_cfg_setup ( adc8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ADC8_RETVAL adc8_init ( adc8_t *ctx, adc8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Adc8 click.
 *
 * @note The default configuration is set:
 * <pre>
 *    -  Set config register:
 *         - ADC8_CFG_GAIN_2048mV
 *         - ADC8_CFG_MODE_SINGLE
 *         - ADC8_CFG_SPS_8
 *         - ADC8_CFG_COMP_MODE_TRADITIONAL
 *         - ADC8_CFG_COMP_POL_LOW
 *         - ADC8_CFG_COMP_LAT_ENABLE
 *         - ADC8_CFG_COMP_QUE_4_CONV
 * </pre>
 */
void adc8_default_cfg ( adc8_t *ctx );

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
void adc8_generic_write ( adc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void adc8_generic_read ( adc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Device configuration for measurement
 *
 * @param ctx          Click object.
 * @param cfg   Config data
 *
 * @note Options:
 * <pre>
 *    - Conversions (Enable or Disable)
 *    - Gain (256mV, 512mV, 1024mV and 2048mV - "4096mV and 6144mV" - can make a reading problem)
 *    - Mode (Single and continuous)
 *    - Data Rate ( 8 SPS ... 860 SPS)
 *    - Comparator mode (traditional or window)
 *    - Comparator polarity (LOW or HIGH)
 *    - Comparator Latching (Enable or Disable)
 *    - Comparator queue (1,2,4 or after ALERT)
 * </pre>
 */
void adc8_set_cfg_register ( adc8_t *ctx, uint16_t cfg );

/**
 * @brief Get ADC value on the channel
 *
 * @param ctx          Click object.
 * @param channel   Channel (Single - 0,1,2 or 3 and diff 0-1, 0-3, 1-3, or 2-3)
 *
 * @return 16bit ADC value for (diff channels) and 15bit ADC value for (single channel)
 */
uint16_t adc8_get_adc_value ( adc8_t *ctx, uint8_t channel );

/**
 * @brief Read Voltage in mV
 *
 * @param ctx          Click object.
 * @param channel   Channel (Single - 0,1,2 or 3 and diff 0-1, 0-3, 1-3, or 2-3)
 *
 * @return Voltage in minivolts
 */
float adc8_get_voltage ( adc8_t *ctx, uint8_t channel );

/**
 * @brief Get interrupt pin state
 *
 * @param ctx          Click object.
 *
 * @return Interrupt state on the INT pin
 */
uint8_t adc8_get_interrupt_state( adc8_t *ctx );

/**
 * @brief Get [Package} Single channel voltage
 *
 * @param ctx      Click object.
 * @param *volt    Voltage - on the channel ( 0, 1, 2 and 3 )
 *
 * @note Voltage is in the minivolts
 */
void adc8_get_single_channel( adc8_t *ctx, adc8_single_volt_t *volt );

/**
 * @brief Get [Package] Diff channel voltage
 *
 * @param ctx      Click object.
 * @param *volt    Voltage - on the channel ( 0-1, 0-3, 1-3 and 2-3 )
 *
 * @note Voltage is in the minivolts
 */
void adc8_get_diff_channel( adc8_t *ctx, adc8_diff_volt_t *volt );

#ifdef __cplusplus
}
#endif
#endif  // _ADC8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

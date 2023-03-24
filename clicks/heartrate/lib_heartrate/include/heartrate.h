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
 * \brief This file contains API for Heart Rate Click driver.
 *
 * \addtogroup heartrate Heart Rate Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEARTRATE_H
#define HEARTRATE_H

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
#define HEARTRATE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEARTRATE_RETVAL  uint8_t

#define HEARTRATE_OK           0x00
#define HEARTRATE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Default slave address
 * \{
 */
#define SLAVE_ADDRESS          0x57
/** \} */

/**
 * \defgroup reg_addr Registers addresses
 * \{
 */
#define HEARTRATE_INT_STATUS              0x00
#define HEARTRATE_INT_ENABLE              0x01
#define HEARTRATE_FIFO_WRITE_PTR          0x02
#define HEARTRATE_OVER_FLOW_CNT           0x03
#define HEARTRATE_FIFO_READ_PTR           0x04
#define HEARTRATE_FIFO_DATA_REG           0x05
#define HEARTRATE_MODE_CONFIG             0x06
#define HEARTRATE_SPO2_CONFIG             0x07
#define HEARTRATE_LED_CONFIG              0x09
#define HEARTRATE_TEMP_INTEGER            0x16
#define HEARTRATE_TEMP_FRACTION           0x17
#define HEARTRATE_REVISION_ID             0xFE
#define HEARTRATE_PART_ID                 0xFF
/** \} */

/**
 * \defgroup mode_cfg_bits Mode configuration bits
 * \{
 */
#define HEARTRATE_TEMP_EN                 0x08
#define HEARTRATE_HR_ONLY                 0x02
#define HEARTRATE_SPO2_EN                 0x03
/** \} */

/**
 * \defgroup spO2_cfg_bits SpO2 configuration bits
 * \{
 */
#define HEARTRATE_SPO2_HI_RES_EN          0x40
/** \} */

/**
 * \defgroup interrupt_enable_bits Interrupt enable bits
 * \{
 */
 #define HEARTRATE_ENA_A_FULL             0x80
 #define HEARTRATE_ENA_TEP_RDY            0x40
 #define HEARTRATE_ENA_HR_RDY             0x20
 #define HEARTRATE_ENA_SO2_RDY            0x10
/** \} */

/**
 * \defgroup interrupt_status_bits Interrupt status bits
 * \{
 */
#define HEARTRATE_PWR_RDY                 0x01
/** \} */

/**
 * \defgroup sample_rate_control_bits Sample rate control bits [samples per second]
 * \{
 */
#define HEARTRATE_SAMPLES_50              0x00
#define HEARTRATE_SAMPLES_100             0x04
#define HEARTRATE_SAMPLES_167             0x08
#define HEARTRATE_SAMPLES_200             0x0C
#define HEARTRATE_SAMPLES_400             0x10
#define HEARTRATE_SAMPLES_600             0x14
#define HEARTRATE_SAMPLES_800             0x18
#define HEARTRATE_SAMPLES_1000            0x1C
/** \} */

/**
 * \defgroup led_pulse_width_control_bits LED pulse width control bits - pulse width [us]
 * \{
 */
#define HEARTRATE_PULSE_WIDTH_200         0x00  // 13-bit ADC resolution
#define HEARTRATE_PULSE_WIDTH_400         0x01  // 14-bit ADC resolution
#define HEARTRATE_PULSE_WIDTH_800         0x02  // 15-bit ADC resolution
#define HEARTRATE_PULSE_WIDTH_1600        0x03  // 16-bit ADC resolution
/** \} */

/**
 * \defgroup led_current_control_bits LED current control bits [ma]
 * \{
 */
#define HEARTRATE_IR_CURRENT_0            0x00  // 0.0 mA
#define HEARTRATE_IR_CURRENT_44           0x01  // 4.4 mA
#define HEARTRATE_IR_CURRENT_76           0x02  // 7.6 mA
#define HEARTRATE_IR_CURRENT_110          0x03  // 11.0 mA
#define HEARTRATE_IR_CURRENT_142          0x04  // 14.2 mA
#define HEARTRATE_IR_CURRENT_174          0x05  // 17.4 mA
#define HEARTRATE_IR_CURRENT_208          0x06  // 20.8 mA
#define HEARTRATE_IR_CURRENT_240          0x07  // 24.0 mA
#define HEARTRATE_IR_CURRENT_271          0x08  // 27.1 mA
#define HEARTRATE_IR_CURRENT_306          0x09  // 30.6 mA
#define HEARTRATE_IR_CURRENT_338          0x0A  // 33.8 mA
#define HEARTRATE_IR_CURRENT_370          0x0B  // 37.0 mA
#define HEARTRATE_IR_CURRENT_402          0x0C  // 40.2 mA
#define HEARTRATE_IR_CURRENT_436          0x0D  // 43.6 mA
#define HEARTRATE_IR_CURRENT_468          0x0E  // 46.8 mA
#define HEARTRATE_IR_CURRENT_500          0x0F  // 50.0 mA

#define HEARTRATE_RED_CURRENT_0           0x00  // 0.0 mA
#define HEARTRATE_RED_CURRENT_44          0x10  // 4.4 mA
#define HEARTRATE_RED_CURRENT_76          0x20  // 7.6 mA
#define HEARTRATE_RED_CURRENT_110         0x30  // 11.0 mA
#define HEARTRATE_RED_CURRENT_142         0x40  // 14.2 mA
#define HEARTRATE_RED_CURRENT_174         0x50  // 17.4 mA
#define HEARTRATE_RED_CURRENT_208         0x60  // 20.8 mA
#define HEARTRATE_RED_CURRENT_240         0x70  // 24.0 mA
#define HEARTRATE_RED_CURRENT_271         0x80  // 27.1 mA
#define HEARTRATE_RED_CURRENT_306         0x90  // 30.6 mA
#define HEARTRATE_RED_CURRENT_338         0xA0  // 33.8 mA
#define HEARTRATE_RED_CURRENT_370         0xB0  // 37.0 mA
#define HEARTRATE_RED_CURRENT_402         0xC0  // 40.2 mA
#define HEARTRATE_RED_CURRENT_436         0xD0  // 43.6 mA
#define HEARTRATE_RED_CURRENT_468         0xE0  // 46.8 mA
#define HEARTRATE_RED_CURRENT_500         0xF0  // 50.0 mA
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

} heartrate_t;

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

} heartrate_cfg_t;

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
void heartrate_cfg_setup ( heartrate_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HEARTRATE_RETVAL heartrate_init ( heartrate_t *ctx, heartrate_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HeartRate click.
 */
void heartrate_default_cfg ( heartrate_t *ctx );

/**
 * @brief Function for getting revision ID.
 * 
 * @param ctx  Click object.
 *
 * @description Using this function we can get revision ID.
 */
uint8_t heartrate_get_revision_id ( heartrate_t *ctx );

/**
 * @brief Function for getting part ID.
 *
 * @param ctx  Click object.
 *
 * @description Using this function we can get part ID.
 */
uint8_t heartrate_get_part_id ( heartrate_t *ctx );

/**
 * @brief Function for getting configuration of the chip.
 *
 * @param ctx  Click object.
 *
 * @description Using this function we can get configuration of the chip.
 */ 
uint8_t heartrate_get_config ( heartrate_t *ctx );

/**
 * @brief Function for getting status of heartrate click.
 * 
 * @param ctx  Click object.
 *
 * @description Using this function we can get status of heartrate click.
 */
uint8_t heartrate_get_status ( heartrate_t *ctx );

/**
 * @brief Function for configuration heartrate chip.
 * 
 * @param ctx  Click object.
 * @param cfg  Confing byte.
 * 
 * @description Using this function we can configure heartrate chip.
 */
void heartrate_set_config ( heartrate_t *ctx, uint8_t cfg );

/**
 * @brief Function for setting interrupt for heartrate click.
 * 
 * @param ctx     Click object.
 * @param intrpts Interrup.
 * 
 * @description Using this function we can set interrupt for heartrate click.
 */
void heartrate_set_interrupt ( heartrate_t *ctx, uint8_t intrpts );

/**
 * @brief Function for reading IR and RED values.
 * 
 * @param ctx       Click object.
 * @param ir_buff   IR values.
 * @param red_buff  RED values.
 * 
 * @returns 0 - if success
 * 
 * @description Using this function we can read IR and RED values.
 */
uint8_t heartrate_read_ir_red ( heartrate_t *ctx, uint16_t *ir_buff, uint16_t *red_buff );

/**
 * @brief Function for reading temperature.
 * 
 * @param ctx         Click object.
 * @param temp_value  Temperature value to be read.
 * 
 * @description Using this function we can read temperature.
 */
void heartrate_read_temp ( heartrate_t *ctx, uint16_t *temp_value );

/**
 * @brief Function checking if the data is ready for reading
 * 
 * @param ctx         Click object.
 * 
 * @returns 1 - data ready; 0 - data not ready
 * 
 * @description Using this function we can check if the data is ready for reading
 */
uint8_t heartrate_data_ready ( heartrate_t *ctx );

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
void heartrate_generic_write ( heartrate_t *ctx, uint8_t reg, uint16_t len, uint8_t *data_buf );

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
void heartrate_generic_read ( heartrate_t *ctx, uint8_t reg, uint16_t len, uint8_t *data_buf );

/**
 * @brief Shut down function
 * 
 * @param ctx          Click object.
 * @param enable True - enables shut down, false - disables
 * 
 * @description Enables/disables power saving mode.  While in power-save mode, 
 * all registers retain their values, and write/read operations function as normal. 
 * @note All interrupts are cleared to zero in this mode. 
 */
void hr_shut_down ( heartrate_t *ctx, bool enable );

/**
 * @brief Reset function
 * 
 * @param ctx     Click object.
 * 
 * @description   All configuration, threshold, and data registers are reset to their power-on-state.
 */
void hr_reset ( heartrate_t *ctx );

/**
 * @brief Single temperature reading function
 * 
 * @param ctx     Click object.
 * @param enable  True - enables the reading, false - disables
 * 
 * @description Initiates a single temperature reading from the temperature sensor. This bit is
 * cleared automatically back to zero at the conclusion of the temperature reading when the bit is set to one in heart rate or SpO2 mode.
 */
void hr_temp_enable ( heartrate_t *ctx, bool enable );

/**
 * @brief Set mode function
 * 
 * @param ctx     Click object.
 * @param mode    Desired mode as stated in the datasheet 
 * 
 * @returns -1 if failed, 0 if successful
 * 
 * @description Sets the operating state of the MAX30100
 */
uint8_t hr_set_mode ( heartrate_t *ctx, uint8_t mode );

/**
 * @brief Function for setting the SpO2 ADC resolution
 * 
 * @param ctx     Click object.
 * @param enable  True - enables SpO2 high resolution, False - disables
 * 
 * @description Sets the SpO2 ADC resolution to 16-bit with 1.6ms LED pulse width.
 */
void hr_spo2_high_res_enable ( heartrate_t *ctx, bool enable );

/**
 * @brief  Function for setting
 * 
 * @param ctx           Click object.
 * @param sample_rate   Desired sample rate as stated in the datasheet 
 * @returns -1 if failed, 0 if successful
 * 
 * @description Sets the operating state of the MAX30100
 */
uint8_t hr_spo2_set_sample_rate ( heartrate_t *ctx, uint8_t sample_rate );

/**
 * @brief  Function for setting LED pulse width
 * 
 * @param ctx     Click object.
 * @param _value  Desired pulse width as stated in the datasheet
 * 
 * @returns -1 if failed, 0 if successful
 *
 * @description Sets the  (the IR and RED have the same pulse width)
 */
uint8_t hr_set_led_pulse_width ( heartrate_t *ctx, uint8_t _value );

/**
 * @brief  Function for setting Red LED
 * 
 * @param ctx     Click object.
 * @param level   Desired current level as stated in the datasheet
 * 
 * @returns -1 if failed, 0 if successful
 * 
 * @description Sets the current level of the Red LED.
 */
uint8_t hr_set_red_current_level ( heartrate_t *ctx, uint8_t level );

/**
 * @brief  Function for setting
 * 
 * @param ctx     Click object.
 * @param level   Desired current level as stated in the datasheet
 * 
 * @returns -1 if failed, 0 if successful
 * 
 * @description Sets the current level of the IR LED.
 */
uint8_t hr_set_ir_current_level ( heartrate_t *ctx, uint8_t level );

/**
 * @brief Function to enable/disable the FIFO almost full interrupt
 * 
 * @param ctx     Click object.
 * @param enable  True - interrupt enabled, false - interrupt disabled
 * 
 * @description Enables/disables the FIFO almost full interrupt
 */
void hr_fifo_almost_full_int_enable ( heartrate_t *ctx, bool enable );

/**
 * @brief Function to enable/disable the temperature data ready interrupt
 *
 * @param ctx     Click object.
 * @param enable  True - interrupt enabled, false - interrupt disabled
 * 
 * @description  Enables/disables the temperature data ready interrupt
 */
void hr_temp_ready_int_enable ( heartrate_t *ctx, bool enable );

/**
 * @brief Function to enable/disable heart rate data ready interrupt
 * 
 * @param ctx     Click object.
 * @param enable  True - interrupt enabled, false - interrupt disabled
 * 
 * @description Enables/disables heart rate data ready interrupt
 */
void hr_heartrate_data_ready_int_enable ( heartrate_t *ctx, bool enable );

/**
 * @brief Function to enable/disable the SpO2 data ready
 * 
 * @param ctx     Click object.
 * @param enable  True - interrupt enabled, false - interrupt disabled
 * 
 * @description Enables/disables the SpO2 data ready
 */
void hr_heartrate_spo2_data_ready_int_enable ( heartrate_t *ctx, bool enable );

/**
 * @brief Function for reading the ADC values of the IR and RED LEDs from the FIFO buffer
 *
 * @param ctx     Click object.
 * @param ir_buffer Buffer to which to store the IR LED values
 * @param red_buffer Buffer to which to store the RED LED values
 * 
 * @returns the number of samples
 * 
 * @description  Reads the ADC values of the IR and RED LEDs from the FIFO buffer, 
 * and stores them into the given buffers.
 */
uint8_t hr_read_diodes ( heartrate_t *ctx, uint16_t* ir_buff, uint16_t* red_buff );

/**
 * @brief Function for getting the value read from the interrupt status register
 * 
 * @param ctx     Click object.
 * 
 * @returns the status value
 * 
 * @description Returns the value read from the interrupt status register. 
 * The value shows which interrupts have been trigerred
 */
uint8_t hr_get_status ( heartrate_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HEARTRATE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

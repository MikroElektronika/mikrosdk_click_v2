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
 * \brief This file contains API for UV 4 Click driver.
 *
 * \addtogroup uv4 UV 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UV4_H
#define UV4_H

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
#define UV4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UV4_RETVAL  uint8_t

#define UV4_OK           0x00
#define UV4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup generic_register Generic Register
 * \{
 */
#define UV4_PART_ID_REG       0x00
#define UV4_HW_ID_REG         0x01
#define UV4_REV_ID_REG        0x02
#define UV4_INFO_0_REG        0x03
#define UV4_INFO_1_REG        0x04
#define UV4_INPUT_3_REG       0x07
#define UV4_INPUT_2_REG       0x08
#define UV4_INPUT_1_REG       0x09
#define UV4_INPUT_0_REG       0x0A
#define UV4_COMMAND_REG       0x0B
#define UV4_IRQ_ENABLE_REG    0x0F
#define UV4_RESPONSE_1_REG    0x10
#define UV4_RESPONSE_0_REG    0x11
#define UV4_IRQ_STATUS_REG    0x12
#define UV4_OUTPUT_0_REG      0x13
#define UV4_OUTPUT_1_REG      0x14
#define UV4_OUTPUT_2_REG      0x15
#define UV4_OUTPUT_3_REG      0x16
#define UV4_OUTPUT_4_REG      0x17
#define UV4_OUTPUT_5_REG      0x18
#define UV4_OUTPUT_6_REG      0x19
#define UV4_OUTPUT_7_REG      0x1A
#define UV4_OUTPUT_8_REG      0x1B
#define UV4_OUTPUT_9_REG      0x1C
#define UV4_OUTPUT_10_REG     0x1D
#define UV4_OUTPUT_11_REG     0x1E
#define UV4_OUTPUT_12_REG     0x1F
#define UV4_OUTPUT_13_REG     0x20
#define UV4_OUTPUT_14_REG     0x21
#define UV4_OUTPUT_15_REG     0x22
#define UV4_OUTPUT_16_REG     0x23
#define UV4_OUTPUT_17_REG     0x24
#define UV4_OUTPUT_18_REG     0x25
#define UV4_OUTPUT_19_REG     0x26
#define UV4_OUTPUT_20_REG     0x27
#define UV4_OUTPUT_21_REG     0x28
#define UV4_OUTPUT_22_REG     0x29
#define UV4_OUTPUT_23_REG     0x2A
#define UV4_OUTPUT_24_REG     0x2B
#define UV4_OUTPUT_25_REG     0x2C
/** \} */

/**
* \defgroup parameters Parameters
* \{
*/
#define UV4_I2C_ADDR_PARAM        0x00
#define UV4_CHAN_LIST_PARAM       0x01
#define UV4_ADCCONFIG_0_PARAM     0x02
#define UV4_ADCSENS_0_PARAM       0x03
#define UV4_ADCPOST_0_PARAM       0x04
#define UV4_MEASCONFIG_0_PARAM    0x05
#define UV4_ADCCONFIG_1_PARAM     0x06
#define UV4_ADCSENS_1_PARAM       0x07
#define UV4_ADCPOST_1_PARAM       0x08
#define UV4_MEASCONFIG_1_PARAM    0x09
#define UV4_ADCCONFIG_2_PARAM     0x0A
#define UV4_ADCSENS_2_PARAM       0x0B
#define UV4_ADCPOST_2_PARAM       0x0C
#define UV4_MEASCONFIG_2_PARAM    0x0D
#define UV4_ADCCONFIG_3_PARAM     0x0E
#define UV4_ADCSENS_3_PARAM       0x0F
#define UV4_ADCPOST_3_PARAM       0x10
#define UV4_MEASCONFIG_3_PARAM    0x11
#define UV4_ADCCONFIG_4_PARAM     0x12
#define UV4_ADCSENS_4_PARAM       0x13
#define UV4_ADCPOST_4_PARAM       0x14
#define UV4_MEASCONFIG_4_PARAM    0x15
#define UV4_ADCCONFIG_5_PARAM     0x16
#define UV4_ADCSENS_5_PARAM       0x17
#define UV4_ADCPOST_5_PARAM       0x18
#define UV4_MEASCONFIG_5_PARAM    0x19
#define UV4_MEASRATE_H_PARAM      0x1A
#define UV4_MEASRATE_L_PARAM      0x1B
#define UV4_MEASCOUNT_0_PARAM     0x1C
#define UV4_MEASCOUNT_1_PARAM     0x1D
#define UV4_MEASCOUNT_2_PARAM     0x1E
#define UV4_THRESHOLD0_H_PARAM    0x25
#define UV4_THRESHOLD0_L_PARAM    0x26
#define UV4_THRESHOLD1_H_PARAM    0x27
#define UV4_THRESHOLD1_L_PARAM    0x28
#define UV4_THRESHOLD2_H_PARAM    0x29
#define UV4_THRESHOLD2_L_PARAM    0x2A
#define UV4_BURST_PARAM           0x2B
/** \} */

/**
* \defgroup commands Commands
* \{
*/
#define UV4_RESET_CTR_CMD  0x00
#define UV4_RESET_SW_CMD   0x01
#define UV4_FORCE_CMD      0x11
#define UV4_PAUSE_CMD      0x12
#define UV4_START_CMD      0x13
/** \} */

/**
* \defgroup interrupt_enable_commands Interrupt Enable Commands
* \{
*/
#define UV4_ALL_INTERR_DISABLE     0x00
#define UV4_CHAN0_INTERR_ENABLE    0x01
#define UV4_CHAN1_INTERR_ENABLE    0x02
#define UV4_CHAN2_INTERR_ENABLE    0x04
#define UV4_CHAN3_INTERR_ENABLE    0x08
#define UV4_CHAN4_INTERR_ENABLE    0x10
#define UV4_CHAN5_INTERR_ENABLE    0x20
/** \} */

/**
* \defgroup channels_enable Channels Enable
* \{
*/
#define UV4_ALL_CHANNELS_DISABLE   0x00
#define UV4_CHAN0_ENABLE           0x01
#define UV4_CHAN1_ENABLE           0x02
#define UV4_CHAN2_ENABLE           0x04
#define UV4_CHAN3_ENABLE           0x08
#define UV4_CHAN4_ENABLE           0x10
#define UV4_CHAN5_ENABLE           0x20
/** \} */

/**
* \defgroup data_rate  Data Rate
* \{
*/
#define UV4_DATARATE_1024          0x00
#define UV4_DATARATE_2048          0x20
#define UV4_DATARATE_4096          0x40
#define UV4_DATARATE_512           0x60
/** \} */

/**
* \defgroup uv4_options  UV4 Options
* \{
*/
#define UV4_OPT_FUNC_SMALL_IR      0x00
#define UV4_OPT_FUNC_MEDIUM_IR     0x01
#define UV4_OPT_FUNC_LARGE_IR      0x02
#define UV4_OPT_FUNC_WHITE         0x0B
#define UV4_OPT_FUNC_LARGE_WHITE   0x0D
#define UV4_OPT_FUNC_UV            0x18
#define UV4_OPT_FUNC_UV_DEEP       0x19
/** \} */

/**
* \defgroup uv4_measurements  UV4 Measurements
* \{
*/
#define UV4_NORMAL_GAIN           0x00
#define UV4_HIGH_RANGE            0x80
#define UV4_1_MEASUREMENT         0x00
#define UV4_2_MEASUREMENTS        0x10
#define UV4_4_MEASUREMENTS        0x20
#define UV4_8_MEASUREMENTS        0x30
#define UV4_16_MEASUREMENTS       0x40
#define UV4_32_MEASUREMENTS       0x50
#define UV4_64_MEASUREMENTS       0x60
#define UV4_128_MEASUREMENTS      0x70
#define UV4_MEASTIME_24MICROSEC   0x00
#define UV4_MEASTIME_48MICROSEC   0x01
#define UV4_MEASTIME_96MICROSEC   0x02
#define UV4_MEASTIME_25MILISEC    0x0A
#define UV4_MEASTIME_50MILISEC    0x0B
/** \} */

/**
* \defgroup shift_registers  Shift_registers
* \{
*/
#define UV4_16BIT_OUT                  0x00
#define UV4_24BIT_OUT                  0x40
#define UV4_NO_SHIFT_RIGHT             0x00
#define UV4_1BIT_SHIFT_RIGHT           0x08
#define UV4_2BITS_SHIFT_RIGHT          0x10
#define UV4_3BITS_SHIFT_RIGHT          0x18
#define UV4_4BITS_SHIFT_RIGHT          0x20
/** \} */

/**
* \defgroup thresholds_registers  Thresholds_registers
* \{
*/
#define UV4_THRESHOLDS_DISABLE         0x00
#define UV4_THRESHOLD0_INTERR_ENABLE   0x01
#define UV4_THRESHOLD1_INTERR_ENABLE   0x02
#define UV4_THRESHOLD2_INTERR_ENABLE   0x03
/** \} */

/**
* \defgroup meas_count  Measurment count
* \{
*/
#define UV4_NO_COUNTER_SELECTED   0x00
#define UV4_MEASCOUNT1_SELECT     0x40
#define UV4_MEASCOUNT2_SELECT     0x80
#define UV4_MEASCOUNT3_SELECT     0xC0
/** \} */

/**
* \defgroup burst_enable  Burst Enable
* \{
*/
#define UV4_BURST_DISABLE        0x00
#define UV4_BURST_ENABLE         0x80
/** \} */

/**
* \defgroup autoinc_enable Autoinc Enable
* \{
*/
#define UV4_AUTOINC_ENABLE    0x00
#define UV4_AUTOINC_DISABLE   0x40
/** \} */

/**
* \defgroup  errors Errors
* \{
*/
#define UV4_OK                  0x00
#define UV4_ADDR_ERR            0x01
#define UV4_PARAM_ERR           0x02
#define UV4_CMMND_ERR           0x03
#define UV4_LOC_ERR             0x04
#define UV4_ACCM_OVERFLOW       0x05
#define UV4_BUFF_OVERFLOW       0x06
#define UV4_RST_OCCURED         0x07
#define UV4_INTERR_OCCURED      0xFF
#define UV4_NO_INTERR           0x00
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint8_t config_byte;

    uint8_t optical_data[ 6 ];

    uint8_t tmp;
    uint8_t bit_size[ 6 ];
    uint8_t inc_en;

} uv4_t;

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

    uint8_t config_byte;
    uint8_t optical_data[ 6 ];

    uint8_t dev_tmp;

} uv4_cfg_t;

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
void uv4_cfg_setup ( uv4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UV4_RETVAL uv4_init ( uv4_t *ctx, uv4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for UV4 Click.
 */
void uv4_default_cfg ( uv4_t* ctx );

/**
 * @brief Generic write function.
 *
 * @param uv4           Click object.
 * @param reg_address   Address to write byte to.
 *
 * @returns 0 - OK, 1 - Wrong address parameter.
 *
 * @description This function write one byte of data to given address.
 */
UV4_RETVAL uv4_write_reg ( uv4_t* ctx, const uint8_t reg_address, const uint8_t transfer_data );

/**
 * @brief Generic read function.
 *
 * @param uv4           Click object.
 * @param reg_address   Address to read byte from.
 * @param data_out      Pointer to buffer where data is to be stored.
 * @param inc_en        0x00 - Enable autoincrement pointer,
 *                      0x40 - Disable autoincrement pointer.
 *
 * @returns 0 - OK, 1 - Wrong address parameter, 2 - Wrong inc_en parameter.
 *
 * @description This function reads determined number of bytes from given address.
 */
UV4_RETVAL uv4_read_reg ( uv4_t* ctx,  uint8_t reg_address, uint8_t* data_out,
                          uint8_t n_bytes );

/**
 * @brief Parameter Data Write Function.
 *
 * @param uv4             Click object.
 * @param param_address   Address of parameter data.
 * @param transfer_data   Data to be written.
 *
 * @returns 0 - OK, 1 - Wrong address parameter, 3 - Invalid command, 
 *          4 - Invalid location, 5 - Saturation or overflow of accumulation,
 *          6 - Output buffer overflow, 7 - Reset occurred.
 *
 * @description This function writes one byte of data in parameter table.
 */
UV4_RETVAL uv4_write_param_data ( uv4_t* ctx, uint8_t param_address, uint8_t transfer_data );

/**
 * @brief Parameter Data Read Function.
 *
 * @param uv4             Click object.
 * @param param_address   Address of parameter data.
 * @param param_out       Pointer to buffer where parameter is stored.
 *
 * @returns 0 - OK, 1 - Wrong address parameter, 3 - Invalid command,
 *          4 - Invalid location, 5 - Saturation or overflow of accumulation,
 *          6 - Output buffer overflow, 7 - Reset occurred.
 *
 * @description This function reads one byte of data from parameter table.
 */
UV4_RETVAL uv4_read_param_data(uv4_t* ctx, uint8_t param_address, uint8_t* param_out);

/**
 * @brief Measurements Read Function.
 *
 * @param uv4             Click object.
 * @param measure_out     Pointer to buffer where measured data is stored.
 *
 * @description This function reads measured determined data from selected
 * channel/channels, when measurement is completed on selected channel. 
 * Measured data can be 16-bit unsigned data, or 24-bit signed data.
 */
void uv4_read_measurements(uv4_t* ctx, uint32_t* measure_out);

/**
 * @brief Error And Counter Check function.
 *
 * @param uv4             Click object.
 * @param cnt_data        Pointer where counter data is stored.
 *
 * @returns 0 - OK, 1 - Wrong address parameter, 3 - Invalid command,
 *          4 - Invalid location, 5 - Saturation or overflow of accumulation,
 *          6 - Output buffer overflow, 7 - Reset occurred.
 *
 * @description This function checks if error occurred and if it didn't, reads
 * counter data. Counter increments on every successful command.
 */
UV4_RETVAL uv4_check_err_and_ctr(uv4_t* ctx, uint8_t* cnt_data);

/**
 * @brief Error And Counter Check function.
 *
 * @param uv4             Click object.
 *
 * @returns 0x00 - No interrupt, 0xFF - Interrupt occurred.
 *
 * @description This function checks state on INT pin, if interrupt occurred.
 */
UV4_RETVAL uv4_check_interr(uv4_t* ctx);

#ifdef __cplusplus
}
#endif
#endif  // _UV4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

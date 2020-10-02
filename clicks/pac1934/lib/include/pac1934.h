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
 * \brief This file contains API for Pac1934 Click driver.
 *
 * \addtogroup pac1934 Pac1934 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PAC1934_H
#define PAC1934_H

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
#define PAC1934_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.ale = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PAC1934_RETVAL  uint8_t

#define PAC1934_OK           0x00
#define PAC1934_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_slave_address  I2c Slave Address
 * \{
 */
#define PAC1934_I2C_ADDR                                      0x10
/** \} */

/**
 * \defgroup refresh_command  Refresh Command
 * \{
 */
#define PAC1934_REFRESH_CMD                                   0x00
/** \} */

/**
 * \defgroup control_register   Control Register
 * \{
 */
#define PAC1934_CTRL_REG                                      0x01
/** \} */

/**
 * \defgroup accumulator_count  Accumulator Count
 * \{
 */
#define PAC1934_ACC_COUNT                                     0x02
/** \} */

/**
 * \defgroup accumulated_power_registers  Accumulated Power Registers
 * \{
 */
#define PAC1934_VPOWER1_ACC                                   0x03
#define PAC1934_VPOWER2_ACC                                   0x04
#define PAC1934_VPOWER3_ACC                                   0x05
#define PAC1934_VPOWER4_ACC                                   0x06
/** \} */

/**
 * \defgroup most_recent_vbus_sample  Most Recent Vbus Sample
 * \{
 */
#define PAC1934_VBUS1                                         0x07
#define PAC1934_VBUS2                                         0x08
#define PAC1934_VBUS3                                         0x09
#define PAC1934_VBUS4                                         0x0A
/** \} */

/**
 * \defgroup most_recent_vsense_sample  Most Recent Vsanse Sample
 * \{
 */
#define PAC1934_VSENSE1                                       0x0B
#define PAC1934_VSENSE2                                       0x0C
#define PAC1934_VSENSE3                                       0x0D
#define PAC1934_VSENSE4                                       0x0E
/** \} */

/**
 * \defgroup average_vbus_sample  Average Vbus Sample
 * \{
 */
#define PAC1934_VBUS1_AVG                                     0x0F
#define PAC1934_VBUS2_AVG                                     0x10
#define PAC1934_VBUS3_AVG                                     0x11
#define PAC1934_VBUS4_AVG                                     0x12
/** \} */

/**
 * \defgroup average_vsense_sample  Average Vsense Sample
 * \{
 */
#define PAC1934_VSENSE1_AVG                                   0x13
#define PAC1934_VSENSE2_AVG                                   0x14
#define PAC1934_VSENSE3_AVG                                   0x15
#define PAC1934_VSENSE4_AVG                                   0x16
/** \} */

/**
 * \defgroup vbus_and_vsense_product_1   Vbus and Vsense Product 1
 * \{
 */
#define PAC1934_VPOWER1                                       0x17
#define PAC1934_VPOWER2                                       0x18
#define PAC1934_VPOWER3                                       0x19
#define PAC1934_VPOWER4                                       0x1A
/** \} */

/**
 * \defgroup channel_disable_and_other_settings   Channel Disable And Other Settings
 * \{
 */
#define PAC1934_CHANNEL_DIS                                   0x1C
/** \} */

/**
 * \defgroup bidirectional_measurements_settings   Bidirectional Measutements Settings
 * \{
 */
#define PAC1934_NEG_PWR                                       0x1D
/** \} */

/**
 * \defgroup refresh_g_command   Refresh G Command
 * \{
 */
#define PAC1934_REFRESH_G_CMD                                 0x1E
/** \} */

/**
 * \defgroup refresh_v_command   Refresh V Command
 * \{
 */
#define PAC1934_REFRESH_V_CMD                                 0x1F
/** \} */


/**
 * \defgroup slow_pin_state_and_settings  Slow Pin State And Settings
 * \{
 */
#define PAC1934_SLOW                                          0x20
/** \} */

/**
 * \defgroup actual_state_of_ctrl_register  Actual State Of Ctrl Register
 * \{
 */
#define PAC1934_CTRL_ACT                                      0x21
/** \} */

/**
 * \defgroup actual_state_of_channel_dis_register   Actual State Of Channel Dis Register
 * \{
 */
#define PAC1934_DIS_ACT                                       0x22
/** \} */

/**
 * \defgroup actual_state_of_neg_pwr_register   Actual State Of Neg Pwr Register
 * \{
 */
#define PAC1934_NEG_PWR_ACT                                   0x23
/** \} */

/**
 * \defgroup latched_state_of_ctrl_register   Latched State Of_Ctrl_Register
 * \{
 */
#define PAC1934_CTRL_LAT                                      0x24
/** \} */

/**
 * \defgroup latched_state_of_channel_dis_register   Latched State Of_Channel_Dis_Register
 * \{
 */
#define PAC1934_DIS_LAT                                       0x25
/** \} */

/**
 * \defgroup latched_state_of_neg_pwr_register   Latched State Of_Neg_Pwr_Register
 * \{
 */
#define PAC1934_NEG_PWR_LAT                                   0x26
/** \} */

/**
 * \defgroup product_id_register  Product Id Register
 * \{
 */
#define PAC1934_PRODUCT_ID                                    0xFD
/** \} */

/**
 * \defgroup manufacturer_id_register   Manufacturer Id Register
 * \{
 */
#define PAC1934_MANUFACT_ID                                   0xFE
/** \} */

/**
 * \defgroup revision_id_register   Revision Id Register
 * \{
 */
#define PAC1934_REVISION_ID                                   0xFF
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
    // Output pins 

    digital_out_t rst;

    // Input pins 

    digital_in_t ale;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;


} pac1934_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;

    pin_name_t ale;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} pac1934_cfg_t;

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
void pac1934_cfg_setup ( pac1934_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PAC1934_RETVAL pac1934_init ( pac1934_t *ctx, pac1934_cfg_t *cfg );

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
void pac1934_generic_write ( pac1934_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void pac1934_generic_read ( pac1934_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write function.
 * 
 * @param ctx          Click object.
 * @param wr_addr      8-bit register address.
 * @param wr_data      8-bit data to be written into register.
 
 *
 * @description Tunction writes single byte of data into specified register..
 */
void pac1934_write_byte ( pac1934_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
 * @brief Read one byte function.
 * 
 * @param ctx          Click object.
 * @param rd_addr      8-bit register address.
 *
 * @returns 8-bit data from address specified register
 *
 * @description Tunction reads single byte of data from specified register.
 */
uint8_t pac1934_read_byte ( pac1934_t *ctx, uint8_t rd_addr );

/**
 * @brief Read two bytes function.
 * 
 * @param ctx          Click object.
 * @param rd_addr      8-bit register address.
 *
 * @returns 16-bit data from address specified registers
 *
 * @description This function reads 2 bytes of data from specified, registers.
 */
uint16_t pac1934_read_two_byte ( pac1934_t *ctx, uint8_t rd_addr );

/**
 * @brief Read four bytes function.
 * 
 * @param ctx          Click object.
 * @param rd_addr      8-bit register address.
 *
 * @returns 32-bit data from address specified registers
 *
 * @description This function reads 4 bytes of data from specified, registers.
 */
uint32_t pac1934_read_four_byte ( pac1934_t *ctx, uint8_t rd_addr );

/**
 * @brief Read chosen number of bytes function.
 * 
 * @param ctx          Click object.
 * @param reg_addr     8-bit register address.
 * @param output_data  outputData data from address specified registers.
 * @param cnt          8-bit register address.
 *
 * @description This function reads user defined number bytes of data from specified, registers.
 */
void pac1934_read_reg( pac1934_t *ctx, uint8_t reg_addr, uint8_t *output_data, uint8_t cnt );

/**
 * @brief Send Command.
 * 
 * @param ctx          Click object.
 * @param wr_cmd       8-bit command to execute.
 *
 * @note Calling this function with '_PAC1934_REFRESH_G_CMD' parameter will issue a
 * global command to all the devices on the bus.
 *
 * @description This function Executes refresh commands.
 */
void pac1934_send_command ( pac1934_t *ctx, uint8_t wr_cmd );

/**
 * @brief Measure Voltage function.
 * 
 * @param ctx          Click object.
 * @param channel      Channel from which to read.
 *
 * @returns result float value that represents voltage
 *
 Reads the voltage data from one of the _PAC1934_VBUS registers, depending
 * on the selected channel and converts it into float value expressed in Volts.
 *
 * @note This command reads voltage from the time of the most recent refresh command.
 *
 * @description This function measure Voltage function.
 */
float pac1934_measure_voltage ( pac1934_t *ctx, uint8_t channel );

/**
 * @brief Measure Current function.
 * 
 * @param ctx          Click object.
 * @param channel      Channel from which to read.
 *
 * @returns result float value that represents current
 *
 * Reads the current data from one of the _PAC1934_VSENSE registers, depending
 * on the selected channel and converts it into float value expressed in mA.
 *
 * @note This command reads current from the time of the most recent refresh command.
 *
 * @description This function measure Current function
 */
float pac1934_measure_current ( pac1934_t *ctx, uint8_t channel );

/**
 * @brief Measure Power function.
 * 
 * @param ctx          Click object.
 * @param channel      Channel from which to read.
 *
 * @returns result float value that represents power.
 *
 * Reads the power data from one of the _PAC1934_VPOWER registers, depending
 * on the selected channel and converts it into float value expressed in Watts.
 *
 * @note This command reads power from the time of the most recent refresh command.
 *
 * @description This function measure Power function.
 */
float pac1934_measure_power ( pac1934_t *ctx, uint8_t channel );

/**
 * @brief Calculate Power function.
 * 
 * @param ctx          Click object.
 * @param voltage      Float value representing the voltage.
 * @param amperage     Float value representing the amperage.
 *
 * @note Make sure that voltage and amperage are taken from the same channel.
 *
 * @description This function is used to calculate power by multiplying voltage and amperage.
 */
float pac1934_calc_power ( pac1934_t *ctx, float voltage, float amperage );

/**
 * @brief Measure Energy function.
 * 
 * @param ctx          Click object.
 * @param chann        channel  Channel from which to read.
 * @param samp_rate    16-but data representing sample rate.
 *
 * Reads the energy data from one of the _PAC1934_VPOWER registers, depending
 * on the selected channel and converts it into float value expressed in Joules.
 * @note This command reads power from the time of the most recent refresh command.
 * @note This function is not available for: PIC, dsPic and AVR based boards.
 *
 * @description This function measure Energy function.
 */
float pac1934_measure_energy ( pac1934_t *ctx, uint8_t chann, uint16_t samp_rate );

/**
 * @brief Enable device function.
 * 
 * @param ctx          Click object.
 *
 * @description This function is used to disable the device.
 */
void pac1934_dev_enable ( pac1934_t *ctx );

/**
 * @brief Disable device function.
 * 
 * @param ctx          Click object.
 *
 * @description This function is used to disable the device.
 */
void pac1934_dev_disable ( pac1934_t *ctx );

/**
 * @brief Reset device function.
 * 
 * @param ctx          Click object.
 *
 * @note Function has a small 200 milisecond delay.
 *
 * @description This function is used to reset the device.
 */
void pac1934_dev_reset ( pac1934_t *ctx );

/**
 * @brief Check Interrupt function.
 *
 * @param ctx          Click object.
 *
 * @returns Result  State of the INT pin
 *
 * @description This function is used to check the state of INT pin.
 */
uint8_t pac1934_check_inrterrupt ( pac1934_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PAC1934_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

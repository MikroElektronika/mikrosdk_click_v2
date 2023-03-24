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
 * \brief This file contains API for Heart rate 4 Click driver.
 *
 * \addtogroup heartrate4 Heart rate 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEARTRATE4_H
#define HEARTRATE4_H

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
#define HEARTRATE4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl1 = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda1 = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEARTRATE4_RETVAL  uint8_t

#define HEARTRATE4_OK           0x00
#define HEARTRATE4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Heart Rate 4 click slave address 
 * \{
 */
#define HEARTRATE4_I2C_ADDRESS    0x57
/** \} */

/**
 * \defgroup reg_addr Registers addresses
 * \{
 */

/**
 * \defgroup status_reg Status Registers
 * \{
 */
#define HEARTRATE4_INT_STAT1                  0x00
#define HEARTRATE4_INT_STAT2                  0x01
#define HEARTRATE4_INT_ENABLE1                0x02
#define HEARTRATE4_INT_ENABLE2                0x03
/** \} */

/**
 * \defgroup fifo_reg FIFO Registers
 * \{
 */
#define HEARTRATE4_FIFO_WRITE_PTR             0x04
#define HEARTRATE4_FIFO_OVERFLOW              0x05
#define HEARTRATE4_FIFO_READ_PTR              0x06
#define HEARTRATE4_FIFO_DATA                  0x07
#define HEARTRATE4_BUFFER_LENGTH              32
/** \} */

/**
 * \defgroup cfg_reg Configuration Registers
 * \{
 */
#define HEARTRATE4_FIFO_CONFIG                0x08
#define HEARTRATE4_MODE_CONFIG                0x09
#define HEARTRATE4_SPO2_CONFIG                0x0A //SpO2 Configuration
#define HEARTRATE4_LED1_PULSE_AMP             0x0C
#define HEARTRATE4_LED2_PULSE_AMP             0x0D
#define HEARTRATE4_LED3_PULSE_AMP             0x0E
#define HEARTRATE4_LED_PROX_AMP               0x10
#define HEARTRATE4_MULTI_LED_CONFIG1          0x11
#define HEARTRATE4_MULTI_LED_CONFIG2          0x12
#define HEARTRATE4_MIN_POWER_LEVEL            0x01
#define HEARTRATE4_AVG_POWER_LEVEL            0x1F
#define HEARTRATE4_MAX_POWER_LEVEL            0xFF
/** \} */

/**
 * \defgroup die_temp_reg  Die Temperature Registers 
 * \{
 */
#define HEARTRATE4_DIE_TEMP_INT               0x1F
#define HEARTRATE4_DIE_TEMP_FRAC              0x20
#define HEARTRATE4_DIE_TEMP_CONFIG            0x21
/** \} */

/**
 * \defgroup proximity_func_reg Proximity Function Registers
 * \{
 */
#define HEARTRATE4_PROX_INT_THRESH            0x30
/** \} */

/**
 * \defgroup part_id_reg Part ID Registers
 * \{
 */
#define HEARTRATE4_REVISION_ID                0xFE
#define HEARTRATE4_PART_ID                    0xFF
/** \} */
/** \} */ //End registers addresses group of macro

/**
 * \defgroup commands HEARTRATE4 Commands
 * \{
 */

/**
 * \defgroup interrupt_cfg Interrupt configuration
 * \{
 */
#define HEARTRATE4_INT_A_FULL_MASK            (uint8_t)~0b10000000
#define HEARTRATE4_INT_A_FULL_ENABLE          0x80
#define HEARTRATE4_INT_A_FULL_DISABLE         0x00
#define HEARTRATE4_INT_DATA_RDY_MASK          (uint8_t)~0b01000000
#define HEARTRATE4_INT_DATA_RDY_ENABLE        0x40
#define HEARTRATE4_INT_DATA_RDY_DISABLE       0x00
#define HEARTRATE4_INT_ALC_OVF_MASK           (uint8_t)~0b00100000
#define HEARTRATE4_INT_ALC_OVF_ENABLE         0x20
#define HEARTRATE4_INT_ALC_OVF_DISABLE        0x00
#define HEARTRATE4_INT_PROX_INT_MASK          (uint8_t)~0b00010000
#define HEARTRATE4_INT_PROX_INT_ENABLE        0x10
#define HEARTRATE4_INT_PROX_INT_DISABLE       0x00
#define HEARTRATE4_INT_DIE_TEMP_RDY_MASK      (uint8_t)~0b00000010
#define HEARTRATE4_INT_DIE_TEMP_RDY_ENABLE    0x02
#define HEARTRATE4_INT_DIE_TEMP_RDY_DISABLE   0x00
/** \} */

/**
 * \defgroup fifo_cfg_commands FIFO configuration commands
 * \{
 */
#define HEARTRATE4_SAMPLEAVG_MASK             (uint8_t)~0b11100000
#define HEARTRATE4_SAMPLEAVG_1                0x00
#define HEARTRATE4_SAMPLEAVG_2                0x20
#define HEARTRATE4_SAMPLEAVG_4                0x40
#define HEARTRATE4_SAMPLEAVG_8                0x60
#define HEARTRATE4_SAMPLEAVG_16               0x80
#define HEARTRATE4_SAMPLEAVG_32               0xA0
#define HEARTRATE4_ROLLOVER_MASK              0xEF
#define HEARTRATE4_ROLLOVER_ENABLE            0x10
#define HEARTRATE4_ROLLOVER_DISABLE           0x00
#define HEARTRATE4_A_FULL_MASK                0xF0
/** \} */

/**
 * \defgroup mode_cfg_commands  Mode configuration commands 
 * \{
 */
#define HEARTRATE4_SHUTDOWN_MASK              0x7F
#define HEARTRATE4_SHUTDOWN                   0x80
#define HEARTRATE4_WAKEUP                     0x00
#define HEARTRATE4_RESET_MASK                 0xBF
#define HEARTRATE4_RESET                      0x40
#define HEARTRATE4_MODE_MASK                  0xF8
#define HEARTRATE4_MODE_REDONLY               0x02     // Heart Rate mode
#define HEARTRATE4_MODE_REDIRONLY             0x03     // SpO2 mode
#define HEARTRATE4_MODE_MULTILED              0x07     // Multi-LED mode
/** \} */

/**
 * \defgroup particle_sensing_cfg_commands Particle sensing configuration commands
 * \{
 */
#define HEARTRATE4_ADCRANGE_MASK              0x9F
#define HEARTRATE4_ADCRANGE_2048              0x00
#define HEARTRATE4_ADCRANGE_4096              0x20
#define HEARTRATE4_ADCRANGE_8192              0x40
#define HEARTRATE4_ADCRANGE_16384             0x60
#define HEARTRATE4_SAMPLERATE_MASK            0xE3
#define HEARTRATE4_SAMPLERATE_50              0x00
#define HEARTRATE4_SAMPLERATE_100             0x04
#define HEARTRATE4_SAMPLERATE_200             0x08
#define HEARTRATE4_SAMPLERATE_400             0x0C
#define HEARTRATE4_SAMPLERATE_800             0x10
#define HEARTRATE4_SAMPLERATE_1000            0x14
#define HEARTRATE4_SAMPLERATE_1600            0x18
#define HEARTRATE4_SAMPLERATE_3200            0x1C
#define HEARTRATE4_PULSEWIDTH_MASK            0xFC
#define HEARTRATE4_PULSEWIDTH_69              0x00
#define HEARTRATE4_PULSEWIDTH_118             0x01
#define HEARTRATE4_PULSEWIDTH_215             0x02
#define HEARTRATE4_PULSEWIDTH_411             0x03
/** \} */

/**
 * \defgroup  multi_led_mode_cfg Multi-LED Mode configuration
 * \{
 */
#define HEARTRATE4_SLOT1_MASK                 0xF8
#define HEARTRATE4_SLOT2_MASK                 0x8F
#define HEARTRATE4_SLOT3_MASK                 0xF8
#define HEARTRATE4_SLOT4_MASK                 0x8F
#define HEARTRATE4_SLOT_NONE                  0x00
#define HEARTRATE4_SLOT_RED_LED               0x01
#define HEARTRATE4_SLOT_IR_LED                0x02
#define HEARTRATE4_SLOT_GREEN_LED             0x03
#define HEARTRATE4_SLOT_NONE_PILOT            0x04
#define HEARTRATE4_SLOT_RED_PILOT             0x05
#define HEARTRATE4_SLOT_IR_PILOT              0x06
#define HEARTRATE4_SLOT_GREEN_PILOT           0x07
/** \} */
/** \} */ // End command group macro
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

    digital_in_t int1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} heartrate4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl1;
    pin_name_t sda1;
    
    // Additional gpio pins 

    pin_name_t int1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} heartrate4_cfg_t;

/**
 * @brief Click registers object definition.
 */
typedef struct
{
  // Structure fields  

  uint8_t avg_samp; 
  uint8_t mode; 
  uint8_t adc_range; 
  uint8_t samp_rate; 
  uint8_t pulse_width; 
  uint8_t led_pow_lvl;

} heartrate4_set_registers_t;

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
void heartrate4_cfg_setup ( heartrate4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HEARTRATE4_RETVAL heartrate4_init ( heartrate4_t *ctx, heartrate4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HeartRate4 click.
 */
void heartrate4_default_cfg ( heartrate4_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param wr_addr      Register address.
 * @param wr_data      8-bit data to be written into register.
 *
 * @description This function writes single byte of data into specified register.
 */
void heartrate4_write_data ( heartrate4_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param rd_addr      Register address.
 * 
 * @returns 8-bit data from address specified register
 *
 * @description This function reads single byte of data from specified register.
 */
uint8_t heartrate4_read_data ( heartrate4_t *ctx, uint8_t rd_addr );

/**
 * @brief Multi read function.
 *
 * @param ctx          Click object.
 * @param rd_addr      Register address.
 * @param buffer       Data buf to read.
 * @param cnt          Number of bytes to read.
 *
 * @description This function reads user defined number byte of data .
 */
void heartrate4_multi_read ( heartrate4_t *ctx, uint8_t rd_addr, uint8_t *buffer, uint8_t cnt );

/**
 * @brief Set new value function
 *
 * @param ctx         Click object.
 * @param reg         8-bit register address
 * @param mask        8-bit value used as a mask
 * @param value       8-bit data to be written into register
 *
 * @description Function is used to apply new values.
**/
void heartrate4_set_new_value ( heartrate4_t *ctx, uint8_t reg, uint8_t mask, uint8_t value );

/**
 * @brief Get desired interrupt function
 *
 * @param ctx         Click object.
 * @param flag        1 - Get the main interrupt group; 2 - Get the temporary ready interrupt
 * @returns result 8-bit data representing the desired interrupt.
 *
 * @description Function is used to read desired interrupt specified by flag.
 * @note Use datasheet to discerm what value from register represents.
**/
uint8_t heartrate4_get_intrrupt ( heartrate4_t *ctx, uint8_t flag );

/**
 * @brief Enable or disable interrupt function
 *
 * @param ctx             Click object.
 * @param interrupt_flag  Flag that specifie interrupt    
 * @param enable_flag     1 - enable; 0 - disable
 * 
 * @description Function is used to enable or disable specified interupt.
 * 
 * @note
 * <pre> 
 *  interrupt_flag state: 
 *        0 - A full 
 *        1 - FIFO data ready interrupt
 *        2 - Ambient Light Cancellation Overflow
 *        3 - Proximity Threshold
 *        4 - Temperature conversion interrupt
 *  enable_flag state:
 *         1 - enable;
 *         0 - disable;
 *  One may consult datasheet in order to discern what to write into register or use predefined values.
 *  </pre> 
 * Consult datasheet in order to discern what to write into register or use predefined values.
**/
void heartrate4_enable_disable_interrupts ( heartrate4_t *ctx, uint8_t interrupt_flag, uint8_t enable_flag );

/**
 * @brief Set corresponding configuration register function
 *
 * @param ctx      Click object.
 * @param flag     Flag that specifie interrupt    
 * @param mode     8-bit data representing desired mode
 * 
 * @description Function is used to write specified mode into corresponding configuration register.
 * 
 * @note
 * <pre> 
 * flag state: 
 *       0 - Soft shut down 
 *       1 - Soft wake up 
 *       2 - Set LED Mode For Sampling
 *       3 - Set ADC Range
 *       4 - Set sample rate
 *       5 - Set pulse width
 * One may consult datasheet in order to discern what to write into register or use predefined values. 
 * </pre> 
**/
void heartrate4_setting_function ( heartrate4_t *ctx, uint8_t flag, uint8_t mode );

/**
 * @brief Set corresponding amplitude or proximity threshold function
 *
 * @param ctx           Click object.
 * @param flag          Flag that specifie amplitude or proximity threshold    
 * @param write_data    8-bit data representing amplitude or the proximity mode interrupt threshold
 * 
 * @description Function is used to set specified amplitude or proximity threshold.
 * 
 * @note
 * <pre> 
 * flag state: 
 *     0 - Set RED LED Pulse Amplitude   
 *     1 - Set IR LED Pulse Amplitude   
 *     2 - Set GREEN LED Pulse Amplitude  
 *     3 - Set Proximity Pulse Amplitude   
 *     4 - Set Proximity Threshold  
 * One may consult datasheet in order to discern what to write into register or use predefined values.
 * </pre> 
**/
void heartrate4_setting_prox_and_amp ( heartrate4_t *ctx, uint8_t flag, uint8_t write_data );

/**
 * @brief Define slots in MultiLED mode function
 *
 * @param ctx           Click object.
 * @param slot_num      8-bit data representing the slot number
 * @param dev           8-bit data representing the device(LED)
 *
 * @description Function is used to determine which LED is active in each time slot.
**/
void heartrate4_enable_slot ( heartrate4_t *ctx, uint8_t slot_num, uint8_t dev );

/**
 * @brief Disable slots in MultiLED mode function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to disable all LED-s in each time slot.
**/
void heartrate4_disable_slots ( heartrate4_t *ctx );

/**
 * @brief Clearing FIFO pointers function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to clear FIFO pointers.
**/
void heartrate4_clear_fifo ( heartrate4_t *ctx );

/**
 * @brief Set FIFO configuration register function
 *
 * @param ctx           Click object.
 * @param flag          Flag that specifie amplitude or proximity threshold    
 * @param samp_num      8-bit data representing the number of samples
 * 
 * @description Function is used to set number of samples by writning into FIFO configuration register.
 *              Or to enable or disable FIFO Rolls on Full
 * @note
 * <pre> 
 * flag state: 
 *     0 - Disable roll over     
 *     1 - Enable roll over    
 *     2 - Set sample average   
 *     3 - Set number of trigger samples    
 * One may consult datasheet in order to discern what to write into register or use predefined values.
 * </pre> 
**/
void heartrate4_fifo_setting ( heartrate4_t *ctx, uint8_t flag, uint8_t samp_num );

/**
 * @brief Read the FIFO Write Pointer function
 *
 * @param ctx           Click object.
 * @returns result 8-bit data that points to the location where the MAX30105 writes the next sample
 *
 * @description Function is used to check write pointer.
 * @note The write pointer increments every time a new sample is added to the FIFO.
**/
uint8_t heartrate4_get_write_ptr ( heartrate4_t *ctx );

/**
 * @brief Read the FIFO Read Pointer function
 *
 * @param ctx           Click object.
 * @returns result 8-bit data that points to the location from where the processor gets the next sample from the FIFO
 *
 * @description Function is used to check read pointer.
 * @note The read pointer is incremented every time a sample is read from the FIFO.
**/
uint8_t heartrate4_get_read_ptr ( heartrate4_t *ctx );

/**
 * @brief Read temperature in Centigrade function
 *
 * @param ctx           Click object.
 * @returns result float value of temperature in Celsius
 *
 * @description Function is used to read current IC�s internal temperature.
**/
float heartrate4_read_temp_c ( heartrate4_t *ctx );

/**
 * @brief Read temperature in Fahrenheit function
 *
 * @param ctx           Click object.
 * @returns result float value of temperature in Fahrenheit
 *
 * @description Function is used to read current IC�s internal temperature.
**/
float heartrate4_read_temp_f ( heartrate4_t *ctx );

/**
 * @brief Reset device function
 *
 * @param ctx           Click object.
 * @description Function is used to apply software reset.
**/
void heartrate4_reset ( heartrate4_t *ctx );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to check the state of INT pin.
**/
uint8_t heartrate4_check_int ( heartrate4_t *ctx );

/**
 * @brief Read oldest FIFO sample function
 * 
 * @param ctx           Click object.
 *
 * @returns 32-bit value representing the oldest RED value
 *
 * @description Function is used to read the oldest RED value from FIFO.
**/
uint32_t heartrate4_read_fifo_oldest_sample ( heartrate4_t *ctx );

/**
 * @brief Check interrupt, power ready or internal temperature ready flag function
 *
 * @param ctx           Click object.
 * @param flag          Flag that specifie interrupt, power ready or internal temperature   
 * 
 * @returns 1 - Interrupt has not occured; 0 - Interrupt has occured
 * 
 * @description Function is used to check if desired interrupt, power ready or internal temperature ready flag has occured 
 * @note
 * <pre> 
 * flag state: 
 *      0 - Check FIFO full interrupt 
 *      1 - Check FIFO data readdy interrupt
 *      2 - Check ambient light cancellation overflow interrupt 
 *      3 - Check proximity threshold triggered interrupt
 *      4 - Check power ready flag
 *      5 - Check internal temperature ready flag   
 * </pre> 
**/
uint8_t heartrate4_check_int_pow_and_temp ( heartrate4_t *ctx, uint8_t flag );

/**
 * @brief Read all FIFO samples function
 *
 * @param ctx           Click object.
 * @param buff  output buffer
 *
 * @returns 16-bit data representing the number of samples to read
 *
 * @description Function is used to read all FIFO data samples and returns average value.
**/
uint16_t heartrate4_read_fifo_all_samples ( heartrate4_t *ctx, uint8_t *buff );

/**
 * @brief Get Red value function
 *
 * @param ctx           Click object.
 * @returns result 32-bit value representing the oldest RED value
 *
 * @description Function is used to read the oldest RED value.
**/
uint32_t heartrate4_get_red_val ( heartrate4_t *ctx );

/**
 * @brief Set registers values function
 *
 * @param ctx           Click object.
 * @param registers     Click registers object.
 * <pre> 
 * Registers structure fields
 *      avg_samp      -   8-bit data representing the number of samples
 *      mode          -   8-bit data representing led mode
 *      adc_range     -   8-bit data representing ADC range
 *      samp_rate     -   8-bit data representing sample rate
 *      pulse_width   -   8-bit data representing the puls width
 *      led_pow_lvl   -   8-bit data representing the power level
 *</pre>
 * @description Function is used to apply device settings.
 * @note Consult datasheet in order to discern what to write into register or use predefined values.
**/
void heartrate4_set_registers( heartrate4_t *ctx, heartrate4_set_registers_t *registers );

#ifdef __cplusplus
}
#endif
#endif  // _HEARTRATE4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

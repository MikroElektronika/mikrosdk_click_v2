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
 * \brief This file contains API for Smoke Click driver.
 *
 * \addtogroup smoke Smoke Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SMOKE_H
#define SMOKE_H

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
#define SMOKE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SMOKE_RETVAL  uint8_t

#define SMOKE_OK           0x00
#define SMOKE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address SMOKE click slave address
 * \{
 */
#define SMOKE_I2C_ADDRESS                 0x57
/** \} */

/**
 * \defgroup registers_addresses Registers addresses
 * \{
 */

/**
 * \defgroup status_registers Status Registers
 * \{
 */
#define SMOKE_INT_STAT1                   0x00
#define SMOKE_INT_STAT2                   0x01
#define SMOKE_INT_ENABLE1                 0x02
#define SMOKE_INT_ENABLE2                 0x03
/** \} */

/**
 * \defgroup fifo_registers FIFO Registers
 * \{
 */
#define SMOKE_FIFO_WRITE_PTR              0x04
#define SMOKE_FIFO_OVERFLOW               0x05
#define SMOKE_FIFO_READ_PTR               0x06
#define SMOKE_FIFO_DATA                   0x07
#define SMOKE_BUFFER_LENGTH               32
/** \} */

/**
 * \defgroup configuration_registers Configuration Registers
 * \{
 */
#define SMOKE_FIFO_CONFIG                 0x08
#define SMOKE_MODE_CONFIG                 0x09
#define SMOKE_PARTICLE_CONFIG             0x0A
#define SMOKE_LED1_PULSE_AMP              0x0C
#define SMOKE_LED2_PULSE_AMP              0x0D
#define SMOKE_LED3_PULSE_AMP              0x0E
#define SMOKE_LED_PROX_AMP                0x10
#define SMOKE_MULTI_LED_CONFIG1           0x11
#define SMOKE_MULTI_LED_CONFIG2           0x12
#define SMOKE_MIN_POWER_LEVEL             0x01
#define SMOKE_AVG_POWER_LEVEL             0x1F
#define SMOKE_MAX_POWER_LEVEL             0xFF
/** \} */

/**
 * \defgroup die_temperature_registers Die Temperature Registers
 * \{
 */
#define SMOKE_DIE_TEMP_INT                0x1F
#define SMOKE_DIE_TEMP_FRAC               0x20
#define SMOKE_DIE_TEMP_CONFIG             0x21
/** \} */

/**
 * \defgroup proximity_function_registers Proximity Function Registers
 * \{
 */
#define SMOKE_PROX_INT_THRESH             0x30
/** \} */

/**
 * \defgroup  part_id_registers  Part ID Registers
 * \{
 */
#define SMOKE_REVISION_ID                 0xFE
#define SMOKE_PART_ID                     0xFF
/** \} */
/** \} */


/**
 * \defgroup smoke_commands Smoke Commands
 * \{
 */

/**
 * \defgroup interrupt_configuration Interrupt configuration
 * \{
 */
#define SMOKE_INT_A_FULL_MASK             (uint8_t)~0b10000000
#define SMOKE_INT_A_FULL_ENABLE           0x80
#define SMOKE_INT_A_FULL_DISABLE          0x00
#define SMOKE_INT_DATA_RDY_MASK           (uint8_t)~0b01000000
#define SMOKE_INT_DATA_RDY_ENABLE         0x40
#define SMOKE_INT_DATA_RDY_DISABLE        0x00
#define SMOKE_INT_ALC_OVF_MASK            (uint8_t)~0b00100000
#define SMOKE_INT_ALC_OVF_ENABLE          0x20
#define SMOKE_INT_ALC_OVF_DISABLE         0x00
#define SMOKE_INT_PROX_INT_MASK           (uint8_t)~0b00010000
#define SMOKE_INT_PROX_INT_ENABLE         0x10
#define SMOKE_INT_PROX_INT_DISABLE        0x00
#define SMOKE_INT_DIE_TEMP_RDY_MASK       (uint8_t)~0b00000010
#define SMOKE_INT_DIE_TEMP_RDY_ENABLE     0x02
#define SMOKE_INT_DIE_TEMP_RDY_DISABLE    0x00
/** \} */

/**
 * \defgroup fifo_configuration_commands FIFO configuration commands
 * \{
 */
#define SMOKE_SAMPLEAVG_MASK              (uint8_t)~0b11100000
#define SMOKE_SAMPLEAVG_1                 0x00
#define SMOKE_SAMPLEAVG_2                 0x20
#define SMOKE_SAMPLEAVG_4                 0x40
#define SMOKE_SAMPLEAVG_8                 0x60
#define SMOKE_SAMPLEAVG_16                0x80
#define SMOKE_SAMPLEAVG_32                0xA0
#define SMOKE_ROLLOVER_MASK               0xEF
#define SMOKE_ROLLOVER_ENABLE             0x10
#define SMOKE_ROLLOVER_DISABLE            0x00
#define SMOKE_A_FULL_MASK                 0xF0
/** \} */

/**
 * \defgroup  mode_configuration_commands  Mode configuration commands
 * \{
 */
#define SMOKE_SHUTDOWN_MASK               0x7F
#define SMOKE_SHUTDOWN                    0x80
#define SMOKE_WAKEUP                      0x00
#define SMOKE_RESET_MASK                  0xBF
#define SMOKE_RESET                       0x40
#define SMOKE_MODE_MASK                   0xF8
#define SMOKE_MODE_REDONLY                0x02
#define SMOKE_MODE_REDIRONLY              0x03
#define SMOKE_MODE_MULTILED               0x07
/** \} */

/**
 * \defgroup particle_sensing_cconfiguration_commands Particle sensing configuration commands
 * \{
 */
#define SMOKE_ADCRANGE_MASK               0x9F
#define SMOKE_ADCRANGE_2048               0x00
#define SMOKE_ADCRANGE_4096               0x20
#define SMOKE_ADCRANGE_8192               0x40
#define SMOKE_ADCRANGE_16384              0x60
#define SMOKE_SAMPLERATE_MASK             0xE3
#define SMOKE_SAMPLERATE_50               0x00
#define SMOKE_SAMPLERATE_100              0x04
#define SMOKE_SAMPLERATE_200              0x08
#define SMOKE_SAMPLERATE_400              0x0C
#define SMOKE_SAMPLERATE_800              0x10
#define SMOKE_SAMPLERATE_1000             0x14
#define SMOKE_SAMPLERATE_1600             0x18
#define SMOKE_SAMPLERATE_3200             0x1C
#define SMOKE_PULSEWIDTH_MASK             0xFC
#define SMOKE_PULSEWIDTH_69               0x00
#define SMOKE_PULSEWIDTH_118              0x01
#define SMOKE_PULSEWIDTH_215              0x02
#define SMOKE_PULSEWIDTH_411              0x03
/** \} */

/**
 * \defgroup multi_led_mode_configuration Multi-LED Mode configuration
 * \{
 */
#define SMOKE_SLOT1_MASK                  0xF8
#define SMOKE_SLOT2_MASK                  0x8F
#define SMOKE_SLOT3_MASK                  0xF8
#define SMOKE_SLOT4_MASK                  0x8F
#define SMOKE_SLOT_NONE                   0x00
#define SMOKE_SLOT_RED_LED                0x01
#define SMOKE_SLOT_IR_LED                 0x02
#define SMOKE_SLOT_GREEN_LED              0x03
#define SMOKE_SLOT_NONE_PILOT             0x04
#define SMOKE_SLOT_RED_PILOT              0x05
#define SMOKE_SLOT_IR_PILOT               0x06
#define SMOKE_SLOT_GREEN_PILOT            0x07
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} smoke_t;

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

} smoke_cfg_t;

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

} smoke_set_registers_t;

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
void smoke_cfg_setup ( smoke_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SMOKE_RETVAL smoke_init ( smoke_t *ctx, smoke_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Smoke click.
 */
void smoke_default_cfg ( smoke_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param wr_addr      Register address.
 * @param wr_data      Data buf to be written.
 *
 * @description This function writes data to the desired register.
 */
void smoke_write_data ( smoke_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param rd_addr      Register address.
 * 
 * @returns    8-bit data from address specified register
 *
 * @description This function reads 8-bit data from the desired register.
 */
uint8_t smoke_read_data ( smoke_t *ctx, uint8_t rd_addr );

/**
 * @brief Multi read function.
 *
 * @param ctx          Click object.
 * @param rd_addr      Register address.
 * @param buffer       Data buf to beread.
 * @param cnt          Number of bytes to be read.
 *
 * @description This function reads n-bytes data from the desired register.
 */
void smoke_multi_read ( smoke_t *ctx, uint8_t rd_addr, uint8_t *buffer, uint8_t cnt );

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
void smoke_set_new_value ( smoke_t *ctx, uint8_t reg, uint8_t mask, uint8_t value );

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
uint8_t smoke_get_intrrupt ( smoke_t *ctx, uint8_t flag );

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
void smoke_enable_disable_interrupts ( smoke_t *ctx, uint8_t interrupt_flag, uint8_t enable_flag );

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
void smoke_setting_function ( smoke_t *ctx, uint8_t flag, uint8_t mode );

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
void smoke_setting_prox_and_amp ( smoke_t *ctx, uint8_t flag, uint8_t write_data );

/**
 * @brief Define slots in MultiLED mode function
 *
 * @param ctx           Click object.
 * @param slot_num      8-bit data representing the slot number
 * @param dev           8-bit data representing the device(LED)
 *
 * @description Function is used to determine which LED is active in each time slot.
**/
void smoke_enable_slot ( smoke_t *ctx, uint8_t slot_num, uint8_t dev );

/**
 * @brief Disable slots in MultiLED mode function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to disable all LED-s in each time slot.
**/
void smoke_disable_slots ( smoke_t *ctx );

/**
 * @brief Clearing FIFO pointers function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to clear FIFO pointers.
**/
void smoke_clear_fifo ( smoke_t *ctx );

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
void smoke_fifo_setting ( smoke_t *ctx, uint8_t flag, uint8_t samp_num );

/**
 * @brief Read the FIFO Write Pointer function
 *
 * @param ctx           Click object.
 * @returns result 8-bit data that points to the location where the MAX30105 writes the next sample
 *
 * @description Function is used to check write pointer.
 * @note The write pointer increments every time a new sample is added to the FIFO.
**/
uint8_t smoke_get_write_ptr ( smoke_t *ctx );

/**
 * @brief Read the FIFO Read Pointer function
 *
 * @param ctx           Click object.
 * @returns result 8-bit data that points to the location from where the processor gets the next sample from the FIFO
 *
 * @description Function is used to check read pointer.
 * @note The read pointer is incremented every time a sample is read from the FIFO.
**/
uint8_t smoke_get_read_ptr ( smoke_t *ctx );

/**
 * @brief Read temperature in Centigrade function
 *
 * @param ctx           Click object.
 * @returns result float value of temperature in Celsius
 *
 * @description Function is used to read current IC�s internal temperature.
**/
float smoke_read_temp_c ( smoke_t *ctx );

/**
 * @brief Read temperature in Fahrenheit function
 *
 * @param ctx           Click object.
 * @returns result float value of temperature in Fahrenheit
 *
 * @description Function is used to read current IC�s internal temperature.
**/
float smoke_read_temp_f ( smoke_t *ctx );

/**
 * @brief Reset device function
 *
 * @param ctx           Click object.
 * @description Function is used to apply software reset.
**/
void smoke_reset ( smoke_t *ctx );

/**
 * @brief Read device ID function
 *
 * @param ctx           Click object.
 * @returns result 8-bit value representing the device's ID number
 *
 * @description Function is used to read the device's ID number.
**/
uint8_t smoke_read_device_id ( smoke_t *ctx );

/**
 * @brief Get Red value function
 *
 * @param ctx           Click object.
 * @returns result 32-bit value representing the oldest RED value
 *
 * @description Function is used to read the oldest RED value.
**/
uint32_t smoke_get_red_val ( smoke_t *ctx );

/**
 * @brief Get IR value function
 *
 * @param ctx           Click object.
 * @returns result 32-bit value representing the oldest IR value
 *
 * @description Function is used to read the oldest IR value.
**/
uint32_t smoke_get_ir_val ( smoke_t *ctx );

/**
 * @brief Get Green value function
 *
 * @param ctx           Click object.
 * @returns result 32-bit value representing the oldest Green value
 *
 * @description Function is used to read the oldest Green value.
**/
uint32_t smoke_get_green_val ( smoke_t *ctx );

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
void smoke_set_registers ( smoke_t *ctx, smoke_set_registers_t *registers );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to check the state of INT pin.
**/
uint8_t smoke_check_int ( smoke_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SMOKE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

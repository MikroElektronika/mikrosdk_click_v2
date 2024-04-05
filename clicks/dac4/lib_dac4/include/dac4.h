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
 * \brief This file contains API for DAC 4 Click driver.
 *
 * \addtogroup dac4 DAC 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC4_H
#define DAC4_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define DAC4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.lda = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC4_OK                 0
#define DAC4_ERROR             -1
/** \} */

#define DAC4_DEVICE_ADDRESS     0x60

/**
 * \defgroup channels  Channels
 * \{
 */
#define DAC4_CHANNEL_A          0
#define DAC4_CHANNEL_B          1
#define DAC4_CHANNEL_C          2
#define DAC4_CHANNEL_D          3
/** \} */
 
/**
 * \defgroup dac_latch  Dac Latch
 * \{
 */
#define DAC4_UPDATE             0
#define DAC4_DONT_UPDATE        1
/** \} */
 
/**
 * \defgroup voltafe_reference  Voltage reference
 * \{
 */
#define DAC4_VREF_EXTERNAL      0
#define DAC4_VREF_INTERNAL      1
/** \} */
 
/**
 * \defgroup power_mode  Power mode
 * \{
 */
#define DAC4_MODE_NORMAL        0
#define DAC4_MODE_1kOhm         1
#define DAC4_MODE_100kOhm       2
#define DAC4_MODE_500kOhm       3
/** \} */
 
/**
 * \defgroup gain  Gain
 * \{
 */
#define DAC4_GAIN_x1            0
#define DAC4_GAIN_x2            1
/** \} */
 
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint8_t rdy_bit;
    uint8_t por_bit;
    uint8_t channel_select;
    uint8_t udac_bit;
    uint8_t voltage_reference;
    uint8_t power_mode;
    uint8_t gain_value;
    uint16_t dac_input_data;

} dac4_channel_setting_t;

typedef struct 
{
    dac4_channel_setting_t channel_a;
    dac4_channel_setting_t channel_b;
    dac4_channel_setting_t channel_c;
    dac4_channel_setting_t channel_d;

} dac4_channel_t;

typedef struct 
{
    uint8_t channel_a; 
    uint8_t channel_b; 
    uint8_t channel_c; 
    uint8_t channel_d;

} dac4_v_ref_channels_t;

typedef struct 
{
    uint8_t channel_a; 
    uint8_t channel_b; 
    uint8_t channel_c; 
    uint8_t channel_d;

} dac4_pm_channels_t;

typedef struct 
{
    uint8_t channel_a; 
    uint8_t channel_b; 
    uint8_t channel_c;
    uint8_t channel_d;

} dac4_gain_channels_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t lda;

    // Input pins 

    digital_in_t rdy;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} dac4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t lda;
    pin_name_t rdy;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} dac4_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void dac4_cfg_setup ( dac4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t dac4_init ( dac4_t *ctx, dac4_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function writes desired number of data bytes.
 */
void dac4_generic_write ( dac4_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads desired number of data bytes.
 */
void dac4_generic_read ( dac4_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Getting INT pin state
 *
 * @param ctx      Click object.
 *
 * @returns 0 if INT pin is LOW
 * @returns 1 if INT pin is HIGH
 *
 * @note This function returns INT pin state
 */
uint8_t dac4_int_get ( dac4_t *ctx );

/**
 * @brief Setting PWM pin state
 *
 * @param ctx      Click object.
 * @param uint8_t  pin_state - pin state
 *
 * @note This function sets PWM pin state
 */
void dac4_pwm_set ( dac4_t *ctx, uint8_t pin_state );

/**
 * @brief Getting data via I2C
 *
 * @param ctx      Click object.
 * @param uint8_t  get_buffer - data buffer
 * @param uint16_t n_bytes - number of bytes
 *
 * @note This function performs I2C read operation
 */
void dac4_i2c_get ( dac4_t *ctx, uint8_t *get_buffer, uint16_t n_bytes );

/**
 * @brief Setting data via I2C
 *
 * @param ctx      Click object.
 * @param uint8_t  get_buffer - data buffer
 * @param uint16_t n_bytes - number of bytes
 *
 * @note This function performs I2C write operation
 */
void dac4_i2c_set ( dac4_t *ctx, uint8_t *set_buffer, uint16_t n_bytes );

/**
 * @brief Executing reset command
 *
 * @param ctx      Click object.
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes general call reset command
 */
uint8_t dac4_general_call_reset ( dac4_t *ctx );

/**
 * @brief Executing wake up command
 *
 * @param ctx      Click object.
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes general call wake up command
 */
uint8_t dac4_general_call_wake_up ( dac4_t *ctx );

/**
 * @brief Executing software update command
 *
 * @param ctx      Click object.
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes general call software update command
 */
uint8_t dac4_general_call_software_update ( dac4_t *ctx );

/**
 * @brief Executing fast write command
 *
 * @param ctx                         Click object.
 * @param channels                    Settings for channels
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes fast write command
 *
 *     dac_channel_setting_t.rdy_bit           - set to 0
 *     dac_channel_setting_t.por_bit           - set to 0
 *     dac_channel_setting_t.channel_select    - set to 0
 *     dac_channel_setting_t.udac_bit          - set to 0
 *     dac_channel_setting_t.voltage_reference - set to 0
 *     dac_channel_setting_t.power_mode        - set to desired value
 *     dac_channel_setting_t.gain_value        - set to 0
 *     dac_channel_setting_t.dac_input_data    - set to desired value
 */
uint8_t dac4_fast_write ( dac4_t *ctx, dac4_channel_t *channels );
/**
 * @brief Executing multi-write command
 *
 * @param ctx                   Click object.
 * @param dac_channel_setting_t channel_buffer - channel setting buffer
 * @param uint8_t               n_channels - number of channels
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes multi write command
 *
 *     dac_channel_setting_t.rdy_bit           - set to 0
 *     dac_channel_setting_t.por_bit           - set to 0
 *     dac_channel_setting_t.channel_select    - set to desired value
 *     dac_channel_setting_t.udac_bit          - set to desired value
 *     dac_channel_setting_t.voltage_reference - set to desired value
 *     dac_channel_setting_t.power_mode        - set to desired value
 *     dac_channel_setting_t.gain_value        - set to desired value
 *     dac_channel_setting_t.dac_input_data    - set to desired value
 */
uint8_t dac4_multi_write ( dac4_t *ctx, dac4_channel_setting_t *channel_buffer, uint8_t n_channels );

/**
 * @brief Executing sequential write command
 *
 * @param ctx                   Click object.
 * @param uint8_t               starting_channel - starting channel
 * @param dac_channel_setting_t channel_buffer - channel setting buffer
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes sequenctial write command
 *
 *     dac_channel_setting_t.rdy_bit           - set to 0
 *     dac_channel_setting_t.por_bit           - set to 0
 *     dac_channel_setting_t.channel_select    - set to desired value
 *     dac_channel_setting_t.udac_bit          - set to desired value
 *     dac_channel_setting_t.voltage_reference - set to desired value
 *     dac_channel_setting_t.power_mode        - set to desired value
 *     dac_channel_setting_t.gain_value        - set to desired value
 *     dac_channel_setting_t.dac_input_data    - set to desired value
 */
uint8_t dac4_sequential_write ( dac4_t *ctx, uint8_t starting_channel, dac4_channel_setting_t *channel_buffer );

/**
 * @brief Executing single write command
 *
 * @param ctx                   Click object.
 * @param dac_channel_setting_t channel_x[ 0 ] - channel settings
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function executes single write command
 *
 *     dac_channel_setting_t.rdy_bit           - set to 0
 *     dac_channel_setting_t.por_bit           - set to 0
 *     dac_channel_setting_t.channel_select    - set to desired value
 *     dac_channel_setting_t.udac_bit          - set to desired value
 *     dac_channel_setting_t.voltage_reference - set to desired value
 *     dac_channel_setting_t.power_mode        - set to desired value
 *     dac_channel_setting_t.gain_value        - set to desired value
 *     dac_channel_setting_t.dac_input_data    - set to desired value
 */
uint8_t dac4_single_write ( dac4_t *ctx, dac4_channel_setting_t *channel_x );

/**
 * @brief Setting channel voltage reference values
 *
 * @param ctx     Click object.
 * @param uint8_t v_ref_channel_a - voltage reference for channel A
 * @param uint8_t v_ref_channel_b - voltage reference for channel B
 * @param uint8_t v_ref_channel_c - voltage reference for channel C
 * @param uint8_t v_ref_channel_d - voltage reference for channel D
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function sets voltage reference value for each channel
 */
uint8_t dac4_voltage_reference_set ( dac4_t *ctx, dac4_v_ref_channels_t *vref );

/**
 * @brief Setting channel power modes
 *
 * @param ctx     Click object.
 * @param uint8_t pm_channel_a - power mode for channel A
 * @param uint8_t pm_channel_b - power mode for channel B
 * @param uint8_t pm_channel_c - power mode for channel C
 * @param uint8_t pm_channel_d - power mode for channel D
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function sets power mode for each channel
 */
uint8_t dac4_power_mode_set ( dac4_t *ctx, dac4_pm_channels_t *pm );

/**
 * @brief Writing channel gain values
 *
 * @param ctx     Click object.
 * @param uint8_t gain_channel_a - gain value for channel A
 * @param uint8_t gain_channel_b - gain value for channel B
 * @param uint8_t gain_channel_c - gain value for channel C
 * @param uint8_t gain_channel_d - gain value for channel D
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function sets gain values for each channel
 */
uint8_t dac4_gain_set ( dac4_t *ctx, dac4_gain_channels_t *gain );

/**
 * @brief Reading channel data and forming reports
 *
 * @param ctx                   Click object.
 * @param dac_channel_setting_t channel_buffer - report buffer
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note This function reads data for all 4 channels, forms a report and stores it into the buffer
 * @note This function forms 8 reports, 2 for each channel
 * @note Reports on even buffer positions(i.e. positions 0, 2, 4, 6) are DAC input register reports
 * @note Reports on odd buffer positions(i.e. positions 1, 3, 5, 7) are DAC EEPROM memory reports
 *
 * @example channel_buffer[ 0 ] - stores DAC input register report for channel A
 * @example channel_buffer[ 1 ] - stores DAC EEPROM register report for channel A
 * @example channel_buffer[ 2 ] - stores DAC input register report for channel B
 */
uint8_t dac4_data_report ( dac4_t *ctx, dac4_channel_setting_t *channel_buffer );


#ifdef __cplusplus
}
#endif
#endif  // _DAC4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

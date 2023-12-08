
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
 * \brief This file contains API for Proximity 10 Click driver.
 *
 * \addtogroup proximity10 Proximity 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY10_H
#define PROXIMITY10_H

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
#define PROXIMITY10_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY10_RETVAL  uint8_t

#define PROXIMITY10_OK           0x00
#define PROXIMITY10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup dev_addr Default Dev Address
 * \{
 */
#define PROXIMITY10_DEFAULT_DEV_ADDR                0x5A
/** \} */

/**
 * \defgroup register_addr Register Addresses
 * \{
 */
#define PROXIMITY10_PART_ID_REG                     0x00
#define PROXIMITY10_REV_ID_REG                      0x01
#define PROXIMITY10_SEQ_ID_REG                      0x02
#define PROXIMITY10_INT_CFG_REG                     0x03
#define PROXIMITY10_IRQ_EN_REG                      0x04
#define PROXIMITY10_IRQ_MODE1_REG                   0x05
#define PROXIMITY10_IRQ_MODE2_REG                   0x06
#define PROXIMITY10_HW_KEY_REG                      0x07
#define PROXIMITY10_MEAS_RATE_REG                   0x08
#define PROXIMITY10_ALS_RATE_REG                    0x09
#define PROXIMITY10_PS_RATE_REG                     0x0A
#define PROXIMITY10_ALS_LOW_TH_REG                  0x0B
#define PROXIMITY10_ALS_HIGH_TH_REG                 0x0D
#define PROXIMITY10_PS_LED21_REG                    0x0F
#define PROXIMITY10_PS_LED3_REG                     0x10
#define PROXIMITY10_PS1_TH_REG                      0x11
#define PROXIMITY10_PS2_TH_REG                      0x13
#define PROXIMITY10_PS3_TH_REG                      0x15
#define PROXIMITY10_PARAM_WR_REG                    0x17
#define PROXIMITY10_COMMAND_REG                     0x18
#define PROXIMITY10_RESPONSE_REG                    0x20
#define PROXIMITY10_IRQ_STATUS_REG                  0x21
#define PROXIMITY10_ALS_VIS_DATA_REG                0x22
#define PROXIMITY10_ALS_IR_DATA_REG                 0x24
#define PROXIMITY10_PS1_DATA_REG                    0x26
#define PROXIMITY10_PS2_DATA_REG                    0x28
#define PROXIMITY10_PS3_DATA_REG                    0x2A
#define PROXIMITY10_AUX_DATA_REG                    0x2C
#define PROXIMITY10_PARAM_RD_REG                    0x2E
#define PROXIMITY10_CHIP_STATUS_REG                 0x30
#define PROXIMITY10_ANA_IN_KEY_REG                  0x3B
/** \} */

/**
 * \defgroup reg_config Settings for Register Configurations
 * \{
 */
#define PROXIMITY10_INT_HOST_CLEAR                  0x00
#define PROXIMITY10_INT_AUTO_CLEAR                  0x02
#define PROXIMITY10_INT_PIN_EN                      0x01

#define PROXIMITY10_CMD_INT_EN                      0x20
#define PROXIMITY10_PS3_INT_EN                      0x10
#define PROXIMITY10_PS2_INT_EN                      0x08
#define PROXIMITY10_PS1_INT_EN                      0x04
#define PROXIMITY10_ALS_INT1_EN                     0x02
#define PROXIMITY10_ALS_INT0_EN                     0x01
#define PROXIMITY10_ALL_INT_DIS                     0x00
 
#define PROXIMITY10_PS2_INT_MEAS_COMPLETE           0x00
#define PROXIMITY10_PS2_INT_MEAS_CROSS_TH           0x40
#define PROXIMITY10_PS2_INT_MEAS_GREATER_TH         0xC0
#define PROXIMITY10_PS1_INT_MEAS_COMPLETE           0x00
#define PROXIMITY10_PS1_INT_MEAS_CROSS_TH           0x10
#define PROXIMITY10_PS1_INT_MEAS_GREATER_TH         0x30
#define PROXIMITY10_CMD_INT_RESP_WRITTEN            0x00
#define PROXIMITY10_CMD_INT_RESP_ERROR              0x04
#define PROXIMITY10_PS3_INT_MEAS_COMPLETE           0x00
#define PROXIMITY10_PS3_INT_MEAS_CROSS_TH           0x01
#define PROXIMITY10_PS3_INT_MEAS_GREATER_TH         0x03
 
#define PROXIMITY10_HW_KEY                          0x17
 
#define PROXIMITY10_DEV_WAKEUP_EVERY_10MS           0x84
#define PROXIMITY10_DEV_WAKEUP_EVERY_20MS           0x94
#define PROXIMITY10_DEV_WAKEUP_EVERY_100MS          0xB9
#define PROXIMITY10_DEV_WAKEUP_EVERY_496MS          0xDF
#define PROXIMITY10_DEV_WAKEUP_EVERY_1984MS         0xFF
 
#define PROXIMITY10_AUTONOM_MEAS_DIS                0x00
#define PROXIMITY10_MEAS_AFTER_EVERY_WAKEUP         0x08
#define PROXIMITY10_MEAS_AFTER_10_TIMES_WAKEUP      0x32
#define PROXIMITY10_MEAS_AFTER_100_TIMES_WAKEUP     0x69
 
#define PROXIMITY10_LED_NO_CURRENT                  0x00
#define PROXIMITY10_LED_MIN_CURRENT                 0x01
#define PROXIMITY10_LED_MAX_CURRENT                 0x0F
/** \} */

/**
 * \defgroup response_error Response error Codes
 * \{
 */
#define PROXIMITY10_INVALID_CMD_ENCOUNT             0x80
#define PROXIMITY10_ADC_OVRFLOW_ENCOUNT_PS1         0x88
#define PROXIMITY10_ADC_OVRFLOW_ENCOUNT_PS2         0x89
#define PROXIMITY10_ADC_OVRFLOW_ENCOUNT_PS3         0x8A
#define PROXIMITY10_ADC_OVRFLOW_ENCOUNT_ALS_VIS     0x8C
#define PROXIMITY10_ADC_OVRFLOW_ENCOUNT_ALS_IR      0x8D
#define PROXIMITY10_ADC_OVRFLOW_ENCOUNT_AUX         0x8E
/** \} */

/**
 * \defgroup interrupt_flags Interupt Flags
 * \{
 */
#define PROXIMITY10_CMD_INT_FLAG                    0x20
#define PROXIMITY10_PS3_INT_FLAG                    0x10
#define PROXIMITY10_PS2_INT_FLAG                    0x08
#define PROXIMITY10_PS1_INT_FLAG                    0x04
#define PROXIMITY10_ALS_INT_FLAG                    0x03
#define PROXIMITY10_INT_CLEARED                     0x00
 
#define PROXIMITY10_RUNNING_FLAG                    0x04
#define PROXIMITY10_SUSPEND_FLAG                    0x02
#define PROXIMITY10_SLEEP_FLAG                      0x01
/** \} */

/**
 * \defgroup parameters_addr Parameters Address
 * \{
 */
#define PROXIMITY10_I2C_ADDR_PARAM                  0x00
#define PROXIMITY10_CHLIST_PARAM                    0x01
#define PROXIMITY10_PSLED12_SEL_PARAM               0x02
#define PROXIMITY10_PSLED3_SEL_PARAM                0x03
#define PROXIMITY10_PS_ENCODING_PARAM               0x05
#define PROXIMITY10_ALS_ENCODING_PARAM              0x06
#define PROXIMITY10_PS1_ADCMUX_PARAM                0x07
#define PROXIMITY10_PS2_ADCMUX_PARAM                0x08
#define PROXIMITY10_PS3_ADCMUX_PARAM                0x09
#define PROXIMITY10_PS_ADC_COUNT_PARAM              0x0A
#define PROXIMITY10_PS_ADC_GAIN_PARAM               0x0B
#define PROXIMITY10_PS_ADC_MISC_PARAM               0x0C
#define PROXIMITY10_ALS_IR_ADCMUX_PARAM             0x0E
#define PROXIMITY10_AUX_ADCMUX_PARAM                0x0F
#define PROXIMITY10_ALS_VIS_ADC_COUNT_PARAM         0x10
#define PROXIMITY10_ALS_VIS_ADC_GAIN_PARAM          0x11
#define PROXIMITY10_ALS_VIS_ADC_MISC_PARAM          0x12
#define PROXIMITY10_ALS_HYST_PARAM                  0x16
#define PROXIMITY10_PS_HYST_PARAM                   0x17
#define PROXIMITY10_PS_HISTORY_PARAM                0x18
#define PROXIMITY10_ALS_HISTORY_PARAM               0x19
#define PROXIMITY10_ADC_OFFSET_PARAM                0x1A
#define PROXIMITY10_LED_REC_PARAM                   0x1C
#define PROXIMITY10_ALS_IR_ADC_COUNT_PARAM          0x1D
#define PROXIMITY10_ALS_IR_ADC_GAIN_PARAM           0x1E
#define PROXIMITY10_ALS_IR_ADC_MISC_PARAM           0x1F
/** \} */

/**
 * \defgroup parameters_config Settings for Parameters Configurations
 * \{
 */
#define PROXIMITY10_EN_AUX                          0x40
#define PROXIMITY10_EN_ALS_IR                       0x20
#define PROXIMITY10_EN_ALS_VIS                      0x10
#define PROXIMITY10_EN_PS3                          0x04
#define PROXIMITY10_EN_PS2                          0x02
#define PROXIMITY10_EN_PS1                          0x01
 
#define PROXIMITY10_NO_LED_DRIVE                    0x00
#define PROXIMITY10_LED1_DRIVE_EN                   0x01
#define PROXIMITY10_LED2_DRIVE_EN                   0x02
#define PROXIMITY10_LED3_DRIVE_EN                   0x04
 
#define PROXIMITY10_ADC_REC_1_CLOCK                 0x00
#define PROXIMITY10_ADC_REC_7_CLOCK                 0x10
#define PROXIMITY10_ADC_REC_15_CLOCK                0x20
#define PROXIMITY10_ADC_REC_31_CLOCK                0x30
#define PROXIMITY10_ADC_REC_63_CLOCK                0x40
#define PROXIMITY10_ADC_REC_127_CLOCK               0x50
#define PROXIMITY10_ADC_REC_255_CLOCK               0x60
#define PROXIMITY10_ADC_REC_511_CLOCK               0x70
 
#define PROXIMITY10_ADC_CLOCK_DIV_1                 0x00
#define PROXIMITY10_ADC_CLOCK_DIV_2                 0x01
#define PROXIMITY10_ADC_CLOCK_DIV_4                 0x02
#define PROXIMITY10_ADC_CLOCK_DIV_8                 0x03
#define PROXIMITY10_ADC_CLOCK_DIV_16                0x04
#define PROXIMITY10_ADC_CLOCK_DIV_32                0x05
#define PROXIMITY10_ADC_CLOCK_DIV_64                0x06
#define PROXIMITY10_ADC_CLOCK_DIV_128               0x07
 
#define PROXIMITY10_NORMAL_SIGNAL_RANGE             0x00
#define PROXIMITY10_HIGH_SIGNAL_RANGE               0x20
#define PROXIMITY10_RAW_ADC_MEAS_MODE               0x00
#define PROXIMITY10_NORMAL_PROX_MEAS_MODE           0x04
 
#define PROXIMITY10_ADC_INPUT_SMALL_IR              0x00
#define PROXIMITY10_ADC_INPUT_LARGE_IR              0x03
#define PROXIMITY10_ADC_INPUT_VIS_PHOTODIODE        0x02
#define PROXIMITY10_ADC_INPUT_NO_PHOTODIODE         0x06
#define PROXIMITY10_ADC_INPUT_GND                   0x25
#define PROXIMITY10_ADC_INPUT_TEMP                  0x65
#define PROXIMITY10_ADC_INPUT_VDD                   0x75
 
#define PROXIMITY10_2_CONS_SAMPLES                  0x03
#define PROXIMITY10_3_CONS_SAMPLES                  0x07
#define PROXIMITY10_8_CONS_SAMPLES                  0xFF
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define PROXIMITY10_PARAM_QUERY_CMD                 0x80
#define PROXIMITY10_PARAM_SET_CMD                   0xA0
#define PROXIMITY10_PARAM_AND_CMD                   0xC0
#define PROXIMITY10_PARAM_OR_CMD                    0xE0
#define PROXIMITY10_NOP_CMD                         0x00
#define PROXIMITY10_RESET_CMD                       0x01
#define PROXIMITY10_BUSADDR_CMD                     0x02
#define PROXIMITY10_PS_FORCE_CMD                    0x05
#define PROXIMITY10_ALS_FORCE_CMD                   0x06
#define PROXIMITY10_PSALS_FORCE_CMD                 0x07
#define PROXIMITY10_PS_PAUSE_CMD                    0x09
#define PROXIMITY10_ALS_PAUSE_CMD                   0x0A
#define PROXIMITY10_PSALS_PAUSE_CMD                 0x0B
#define PROXIMITY10_PS_AUTO_CMD                     0x0D
#define PROXIMITY10_ALS_AUTO_CMD                    0x0E
#define PROXIMITY10_PSALS_AUTO_CMD                  0x0F
/** \} */

/**
 * \defgroup en_di_int_clear Settings to enable or disable an interrupt clearing by the host
 * \{
 */
#define PROXIMITY10_INT_CLEAR_DIS                   0x00
#define PROXIMITY10_INT_CLEAR_EN                    0x01
#define PROXIMITY10_CLEAR_INT_CMD                   0xFF
/** \} */

/**
 * \defgroup ret_vals Function Return Values
 * \{
 */
#define PROXIMITY10_OK                              0x00
#define PROXIMITY10_INVALID_REG_ADDR                0x01
#define PROXIMITY10_INVALID_PARAM_ADDR              0x02
#define PROXIMITY10_INVALID_CMD                     0x03
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

} proximity10_t;

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

} proximity10_cfg_t;

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
void proximity10_cfg_setup ( proximity10_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY10_RETVAL proximity10_init ( proximity10_t *ctx, proximity10_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity10 click.
 */
void proximity10_default_cfg ( proximity10_t *ctx );

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
uint8_t proximity10_generic_write ( proximity10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
uint8_t proximity10_generic_read ( proximity10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Check INT Flags function
 *
 * @param ctx          Click object.
 * @param bitMask      Selects a flags to be checked
 * @param clearEn      0 - Disable, 1 - Enable a interrupt clearing by the host
 *
 * @returns Interrupt flags status
 *
 * @description This function checks the desired interrupt flags status.
 */
uint8_t proximity10_check_int_status ( proximity10_t *ctx, uint8_t bit_mask, uint8_t clear_en );

/**
 * @brief Check Chip Status function
 *
 * @param ctx          Click object.
 * @param bitMask      Selects a flags to be checked
 *
 * @returns Chip status flags
 *
 * @description This function checks the desired chip status flags.
 */
uint8_t proximity10_check_chip_status ( proximity10_t *ctx, uint8_t bit_mask );

/**
 * @brief Check INT Pin function
 * 
 * @param ctx          Click object.
 * 
 * @returns 0 or 1
 *
 * @description This function checks the INT pin status.
 */
uint8_t proximity10_check_int_pin ( proximity10_t *ctx );

/**
 * @brief Command Send function
 *
 * @param ctx             Click object.
 * @param prox_command    Selects a desired command to be sent
 *
 * @returns 0 - OK, 3 - Invalid command, or returns a response error code
 *
 * @description This function allows user to execute a desired command and checks the response.
 * 
 * @note If error is detected in the response, the Reset command will be executed.
 */
uint8_t proximity10_send_command ( proximity10_t *ctx, uint8_t prox_command );

/**
 * @brief Parameter Query function
 *
 * @param ctx             Click object.
 * @param paramAddr       Address of the desired parameter to be read
 *
 * @returns 0 - OK, 2 - Invalid parameter address, or returns a response error code
 *
 * @descritpion This function reads the selected parameter and writes value to PARAM_RD register, and checks the response.
 * 
 * @note If error is detected in the response, the Reset command will be executed.
 */
uint8_t proximity10_param_query ( proximity10_t *ctx, uint8_t param_addr );

/**
 * @brief Parameter Set function
 *
 * @param ctx             Click object.
 * @param paramAddr       Address of the desired parameter to be set
 *
 * @returns 0 - OK, 2 - Invalid parameter address, or returns a response error code
 *
 * @description This function sets the selected parameter to the desired value, and checks the response.
 * 
 * @note If error is detected in the response, the Reset command will be executed.
 */
uint8_t proximity10_param_set ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value );

/**
 * @brief Parameter AND function
 *
 * @param ctx             Click object.
 * @param paramAddr       Address of the desired parameter to be modified
 *
 * @returns 0 - OK, 2 - Invalid parameter address, or returns a response error code
 *
 * @descritpion This function performs a bit-wise AND operation between selected parameter and entered value, and checks the response.
 * 
 * @note If error is detected in the response, the Reset command will be executed.
 */
uint8_t proximity10_param_and ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value );

/**
 * @brief Parameter OR function
 *
 * @param ctx             Click object.
 * @param paramAddr       Address of the desired parameter to be modified
 *
 * @returns 0 - OK, 2 - Invalid parameter address, or returns a response error code
 *
 * @description This function performs a bit-wise OR operation between selected parameter and entered value, and checks the response.
 * 
 * @note If error is detected in the response, the Reset command will be executed.
 */
uint8_t proximity10_param_or ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY10_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

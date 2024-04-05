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
 * \brief This file contains API for Buck 14 Click driver.
 *
 * \addtogroup buck14 Buck 14 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK14_H
#define BUCK14_H

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
#define BUCK14_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pg   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.syn  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.alr  = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK14_RETVAL  uint8_t

#define BUCK14_OK           0x00
#define BUCK14_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Addr
 * \{
 */
#define BUCK14_SLAVE_ADDR  0x0A
/** \} */

/**
 * \defgroup control_commands Control Commands
 * \{
 */
#define BUCK14_CMD_OPERATION        0x01
#define BUCK14_CMD_ON_OFF_CONFIG    0x02
#define BUCK14_CMD_WRITE_PROTECT    0x10
/** \} */

/**
 * \defgroup output_commands Output Commands
 * \{
 */
#define BUCK14_CMD_CAPABILITY               0x19
#define BUCK14_CMD_VOUT_MODE                0x20
#define BUCK14_CMD_VOUT_COMMAND             0x21
#define BUCK14_CMD_VOUT_TRIM                0x22
#define BUCK14_CMD_VOUT_CAL_OFFSET          0x23
#define BUCK14_CMD_VOUT_MAX                 0x24
#define BUCK14_CMD_VOUT_MARGIN_HIGH         0x25
#define BUCK14_CMD_VOUT_MARGIN_LOW          0x26
#define BUCK14_CMD_VOUT_TRANSITION_RATE     0x27
#define BUCK14_CMD_VOUT_DROOP               0x28
#define BUCK14_CMD_FREQUENCY_SWITCH         0x33
#define BUCK14_CMD_VIN_ON                   0x35
#define BUCK14_CMD_VIN_OFF                  0x36
#define BUCK14_CMD_IOUT_CAL_GAIN            0x38
#define BUCK14_CMD_IOUT_CAL_OFFSET          0x39
/** \} */

/**
 * \defgroup fault_limit_commands Fault Limit Commands
 * \{
 */
#define BUCK14_CMD_FAULT_POWER_GOOD_ON      0x5E
#define BUCK14_CMD_FAULT_POWERGOOD_OFF      0x5F
#define BUCK14_CMD_VOUT_OC_FAULT_LIMIT      0x40
#define BUCK14_CMD_VOUT_UV_FAULT_LIMIT      0x44
#define BUCK14_CMD_IOUT_OC_FAULT_LIMIT      0x46
#define BUCK14_CMD_OT_FAULT_LIMIT           0x4F
#define BUCK14_CMD_OT_WARN_LIMIT            0x51
#define BUCK14_CMD_VIN_OV_FAULT_LIMIT       0x55
#define BUCK14_CMD_VIN_UV_FAULT_LIMIT       0x59
/** \} */

/**
 * \defgroup fault_response_commands Fault Response Commands
 * \{
 */
#define BUCK14_CMD_VOUT_OV_FAULT_RESPONSE   0x41
#define BUCK14_CMD_VOUT_UV_FAULT_RESPONSE   0x45
#define BUCK14_CMD_OT_FAULT_RESPONSE        0x50
#define BUCK14_CMD_VIN_OV_FAULT_RESPONSE    0x56
#define BUCK14_CMD_VIN_UV_FAULT_RESPONSE    0x5A
#define BUCK14_CMD_IOUT_OC_FAULT_RESPONSE   0x47
#define BUCK14_CMD_TON_MAX_FAULT_RESPONSE   0x63
/** \} */

/**
 * \defgroup time_setting_commands Time Setting Commands
 * \{
 */
#define BUCK14_CMD_TON_DELAY                0x60
#define BUCK14_CMD_TON_RISE                 0x61
#define BUCK14_CMD_TOFF_DELAY               0x64
#define BUCK14_CMD_TOFF_FALL                0x65
#define BUCK14_CMD_TON_MAX_FAULT_LIMIT      0x62
/** \} */

/**
 * \defgroup status_commands Status Commands
 * \{
 */
#define BUCK14_CMD_CLEAR_FAULTS           0x03
#define BUCK14_CMD_STATUS_BYTE            0x78
#define BUCK14_CMD_STATUS_WORD            0x79
#define BUCK14_CMD_STATUS_VOUT            0x7A
#define BUCK14_CMD_STATUS_IOUT            0x7B
#define BUCK14_CMD_STATUS_INPUT           0x7C
#define BUCK14_CMD_STATUS_TEMPERATURE     0x7D
#define BUCK14_CMD_STATUS_CML             0x7E
#define BUCK14_CMD_STATUS_MFR_SPECIFIC    0x80
/** \} */

/**
 * \defgroup monitor_commands Monitor Commands
 * \{
 */
#define BUCK14_CMD_READ_VIN               0x88
#define BUCK14_CMD_READ_VOUT              0x8B
#define BUCK14_CMD_READ_IOUT              0x8C
#define BUCK14_CMD_READ_TEMPERATURE_1     0x8D
#define BUCK14_CMD_READ_TEMPERATURE_2     0x8E
#define BUCK14_CMD_READ_DUTY_CYCLE        0x94
#define BUCK14_CMD_READ_FREQUENCY         0x95
/** \} */

/**
 * \defgroup group_commands Group Commands
 * \{
 */
#define BUCK14_CMD_INTERLEAVE             0x37
/** \} */

/**
 * \defgroup identification_commands Identification Commands
 * \{
 */
#define BUCK14_CMD_PMBUS_REVISION         0x98
#define BUCK14_CMD_MFR_ID                 0x99
#define BUCK14_CMD_MFR_MODEL              0x9A
#define BUCK14_CMD_MFR_REVISION           0x9B
#define BUCK14_CMD_MFR_LOCATION           0x9C
#define BUCK14_CMD_MFR_DATE               0x9D
#define BUCK14_CMD_MFR_SERIAL             0x9E
#define BUCK14_CMD_IC_DEVICE_ID           0xAD
#define BUCK14_CMD_IC_DEVICE_REV          0xAE
/** \} */

/**
 * \defgroup supervisory_commands Supervisory Commands
 * \{
 */
#define BUCK14_CMD_STORE_DEFAULT_ALL      0x11
#define BUCK14_CMD_RESTORE_DEFAUL_ALL     0x12
#define BUCK14_CMD_STORE_USER_ALL         0x15
#define BUCK14_CMD_RESTORE_USER_ALL       0x16
/** \} */

/**
 * \defgroup product_specific_commands Product Specific Commands
 * \{
 */
#define BUCK14_CMD_ADAPTIVE_MODE          0xD0
#define BUCK14_CMD_FEEDBACK_EFFORT        0xD3
#define BUCK14_CMD_LOOP_CONFIG            0xD5
#define BUCK14_CMD_TEST_MODE              0xD9
#define BUCK14_CMD_COMP_MODEL             0xDB
#define BUCK14_CMD_STRAP_DISABLE          0xDC
#define BUCK14_CMD_MANUF_CONF             0xE0
#define BUCK14_CMD_MANUF_LOCK             0xE1
#define BUCK14_CMD_MANUF_PASSWD           0xE2
#define BUCK14_CMD_USER_CONF              0xE3
#define BUCK14_CMD_USER_LOCK              0xE4
#define BUCK14_CMD_USER_PASSWD            0xE5
#define BUCK14_CMD_SECURITY_LEVVEL        0xE6
#define BUCK14_CMD_DEADTIME_GCTRL         0xE7
#define BUCK14_CMD_ZETAP                  0xE8
/** \} */

/**
 * \defgroup ctrl_commands Ctrl Commands
 * \{
 */
#define BUCK14_CTRL_DISABLE              0x00
#define BUCK14_CTRL_SOFT_DISABLE         0x60
#define BUCK14_CTRL_ENABLE_NO_MARGIN     0x80
#define BUCK14_CTRL_ENABLE_LOW_MARGIN1   0x96
#define BUCK14_CTRL_ENABLE_LOW_MARGIN2   0x98
#define BUCK14_CTRL_ENABLE_HIGH_MARGIN1  0xA6
#define BUCK14_CTRL_ENABLE_HIGH_MARGIN2  0xA8
/** \} */

/**
 * \defgroup vout_mode Vout Mode
 * \{
 */
#define BUCK14_VOUT_MODE_EXPONENT_12  0x14
#define BUCK14_VOUT_MODE_EXPONENT_13  0x13
#define BUCK14_VOUT_MODE_VALUE        0.000244
/** \} */

/**
 * \defgroup pin_state Pin State
 * \{
 */
#define BUCK14_PIN_STATE_HIGH         1
#define BUCK14_PIN_STATE_LOW          0
/** \} */

/**
 * \defgroup error_commands Error Commands
 * \{
 */
#define BUCK14_SUCCESSFUL             0xAA
#define BUCK14_ID_ERROR               0xBB
#define BUCK14_CMD_ERROR              0xCC
#define BUCK14_ERROR                  0xDD
/** \} */

/**
 * \defgroup amode_calib Amode Calib
 * \{
 */
#define BUCK14_AMODE_CALIB_CONT_RAMP_UP 0x4B
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

    digital_out_t en;
    digital_out_t syn;

    // Input pins 

    digital_in_t pg;
    digital_in_t alr;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} buck14_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pg;
    pin_name_t en;
    pin_name_t syn;
    pin_name_t alr;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} buck14_cfg_t;

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
void buck14_cfg_setup ( buck14_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck14 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK14_RETVAL buck14_init ( buck14_t *ctx, buck14_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck14 click.
 */
void buck14_default_cfg ( buck14_t *ctx );

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
void buck14_generic_write ( buck14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void buck14_generic_read ( buck14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set power ctrl function.
 *
 * @param ctx          Click object.
 * @param state        Value of pin to be set.
 *
 * @description This function sets state of the power control pin on cs.
 */
void buck14_power_ctrl ( buck14_t *ctx, uint8_t state );

/**
 * @brief Set power sync function.
 *
 * @param ctx          Click object.
 * @param state        Value of pin to be set.
 *
 * @description This function sets state of the sync pin on pwm.
 */
void buck14_power_sync ( buck14_t *ctx, uint8_t state );

/**
 * @brief Get power good function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets state of the power good pin on an.
 */
uint8_t buck14_power_good ( buck14_t *ctx );

/**
 * @brief Get alert function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets state of the alert pin on int.
 */
uint8_t buck14_salert ( buck14_t *ctx );

/**
 * @brief Fucntion for checking manufacturer id.
 *
 * @param ctx          Click object.
 *
 * @description This function gets manufacturer id.
 */
uint8_t buck14_check_mfr_id ( buck14_t *ctx );

/**
 * @brief Reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function for reseting device power.
 */
void buck14_reset ( buck14_t *ctx );

/**
 * @brief Read Vout function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads output V.
 */
uint16_t buc14_read_vout ( buck14_t *ctx );

/**
 * @brief Set Vout function.
 *
 * @param ctx          Click object.
 * @param vout         Value to set on output V.
 *
 * @description This function sets output V.
 */
uint8_t buc14_write_vout ( buck14_t *ctx, float vout );

#ifdef __cplusplus
}
#endif
#endif  // _BUCK14_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

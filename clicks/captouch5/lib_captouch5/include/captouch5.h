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
 * \brief This file contains API for Cap Touch 5 Click driver.
 *
 * \addtogroup captouch5 Cap Touch 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPTOUCH5_H
#define CAPTOUCH5_H

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
#define CAPTOUCH5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );
 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPTOUCH5_RETVAL  uint8_t

#define CAPTOUCH5_OK           0x00
#define CAPTOUCH5_INIT_ERROR   0xFF
/** \} */

#define  CAPTOUCH5_I2C_SLAVE_ADDRESS                                0x37

/**
 * \defgroup register Register
 * \{
 */
#define  CAPTOUCH5_REG_SENSOR_EN                                    0x00
#define  CAPTOUCH5_REG_FSS_EN                                       0x02
#define  CAPTOUCH5_REG_SENSITIVITY0                                 0x08
#define  CAPTOUCH5_REG_SENSITIVITY1                                 0x09
#define  CAPTOUCH5_REG_SENSITIVITY2                                 0x0A
#define  CAPTOUCH5_REG_SENSITIVITY3                                 0x0B
#define  CAPTOUCH5_REG_BASE_THRESHOLD0                              0x0C
#define  CAPTOUCH5_REG_BASE_THRESHOLD1                              0x0D
#define  CAPTOUCH5_REG_FINGER_THRESHOLD2                            0x0E
#define  CAPTOUCH5_REG_FINGER_THRESHOLD3                            0x0F
#define  CAPTOUCH5_REG_FINGER_THRESHOLD4                            0x10
#define  CAPTOUCH5_REG_FINGER_THRESHOLD5                            0x11
#define  CAPTOUCH5_REG_FINGER_THRESHOLD6                            0x12
#define  CAPTOUCH5_REG_FINGER_THRESHOLD7                            0x13
#define  CAPTOUCH5_REG_FINGER_THRESHOLD8                            0x14
#define  CAPTOUCH5_REG_FINGER_THRESHOLD9                            0x15
#define  CAPTOUCH5_REG_FINGER_THRESHOLD10                           0x16
#define  CAPTOUCH5_REG_FINGER_THRESHOLD11                           0x17
#define  CAPTOUCH5_REG_FINGER_THRESHOLD12                           0x18
#define  CAPTOUCH5_REG_FINGER_THRESHOLD13                           0x19
#define  CAPTOUCH5_REG_FINGER_THRESHOLD14                           0x1A
#define  CAPTOUCH5_REG_FINGER_THRESHOLD15                           0x1B
#define  CAPTOUCH5_REG_SENSOR_DEBOUNCE                              0x1C
#define  CAPTOUCH5_REG_BUTTON_HYS                                   0x1D
#define  CAPTOUCH5_REG_BUTTON_LBR                                   0x1F
#define  CAPTOUCH5_REG_BUTTON_NNT                                   0x20
#define  CAPTOUCH5_REG_BUTTON_NT                                    0x21
#define  CAPTOUCH5_REG_PROX_EN                                      0x26
#define  CAPTOUCH5_REG_PROX_CFG                                     0x27
#define  CAPTOUCH5_REG_PROX_TOUCH_TH0                               0x28
#define  CAPTOUCH5_REG_PROX_TOUCH_TH1                               0x2A
#define  CAPTOUCH5_REG_PROX_RESOLUTION0                             0x2E
#define  CAPTOUCH5_REG_PROX_RESOLUTION1                             0x2F
#define  CAPTOUCH5_REG_PROX_HYS                                     0x30
#define  CAPTOUCH5_REG_PROX_LBR                                     0x32
#define  CAPTOUCH5_REG_PROX_NNT                                     0x33
#define  CAPTOUCH5_REG_PROX_NT                                      0x34
#define  CAPTOUCH5_REG_BUZZER_CFG                                   0x3E
#define  CAPTOUCH5_REG_BUZZER_ON_TIME                               0x3F
#define  CAPTOUCH5_REG_SPO_CFG                                      0x4C
#define  CAPTOUCH5_REG_DEVICE_CFG0                                  0x4D
#define  CAPTOUCH5_REG_DEVICE_CFG1                                  0x4E
#define  CAPTOUCH5_REG_DEVICE_CFG2                                  0x4F
#define  CAPTOUCH5_REG_DEVICE_CFG3                                  0x50
#define  CAPTOUCH5_REG_I2C_ADDR                                     0x51
#define  CAPTOUCH5_REG_REFRESH_CTRL                                 0x52
#define  CAPTOUCH5_REG_STATE_TIMEOUT                                0x55
#define  CAPTOUCH5_REG_SLIDER_CFG                                   0x5D
#define  CAPTOUCH5_REG_SLIDER1_CFG                                  0x61
#define  CAPTOUCH5_REG_SLIDER1_RESOLUTION                           0x62
#define  CAPTOUCH5_REG_SLIDER1_THRESHOLD                            0x63
#define  CAPTOUCH5_REG_SLIDER2_CFG                                  0x67
#define  CAPTOUCH5_REG_SLIDER2_RESOLUTION                           0x68
#define  CAPTOUCH5_REG_SLIDER2_THRESHOLD                            0x69
#define  CAPTOUCH5_REG_SLIDER_LBR                                   0x71
#define  CAPTOUCH5_REG_SLIDER_NNT                                   0x72
#define  CAPTOUCH5_REG_SLIDER_NT                                    0x73
#define  CAPTOUCH5_REG_SCRATCHPAD0                                  0x7A
#define  CAPTOUCH5_REG_SCRATCHPAD1                                  0x7B
#define  CAPTOUCH5_REG_CONFIG_CRC                                   0x7E
#define  CAPTOUCH5_REG_SENSOR_ID                                    0x82
#define  CAPTOUCH5_REG_CTRL_CMD                                     0x86
#define  CAPTOUCH5_REG_CTRL_CMD_STATUS                              0x88
#define  CAPTOUCH5_REG_CTRL_CMD_ERR                                 0x89
#define  CAPTOUCH5_REG_SYSTEM_STATUS                                0x8A
#define  CAPTOUCH5_REG_PREV_CTRL_CMD_CODE                           0x8C
#define  CAPTOUCH5_REG_FAMILY_ID                                    0x8F
#define  CAPTOUCH5_REG_DEVICE_ID                                    0x90
#define  CAPTOUCH5_REG_DEVICE_REV                                   0x92
#define  CAPTOUCH5_REG_CALC_CRC                                     0x94
#define  CAPTOUCH5_REG_TOTAL_WORKING_SNS                            0x97
#define  CAPTOUCH5_REG_SNS_CP_HIGH                                  0x98
#define  CAPTOUCH5_REG_SNS_VDD_SHORT                                0x9A
#define  CAPTOUCH5_REG_SNS_GND_SHORT                                0x9C
#define  CAPTOUCH5_REG_CMOD_SHIELD_TEST                             0xA0
#define  CAPTOUCH5_REG_BUTTON_STAT                                  0xAA
#define  CAPTOUCH5_REG_LATCHED_BUTTON_STAT                          0xAC
#define  CAPTOUCH5_REG_PROX_STAT                                    0xAE
#define  CAPTOUCH5_REG_LATCHED_PROx_STAT                            0xAF
#define  CAPTOUCH5_REG_SLIDER1_POSITION                             0xB0
#define  CAPTOUCH5_REG_LIFTOFF_SLIDER1_POSITION                     0xB1
#define  CAPTOUCH5_REG_SLIDER2_POSITION                             0xB2
#define  CAPTOUCH5_REG_LIFTOFF_SLIDER2_POSITION                     0xB3
#define  CAPTOUCH5_REG_SYNC_COUNTER0                                0xB9
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR0                     0xBA
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR1                     0xBC
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR2                     0xBE
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR3                     0xC0
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR4                     0xC2
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR5                     0xC4
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR6                     0xC6
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR7                     0xC8
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR8                     0xCA
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR9                     0xCC
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR10                    0xCE
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR11                    0xD0
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR12                    0xD2
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR13                    0xD4
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR14                    0xD6
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT_SENSOR15                    0xD8
#define  CAPTOUCH5_REG_SYNC_COUNTER1                                0xDB
#define  CAPTOUCH5_REG_DEBUG_SENSOR_ID                              0xDC
#define  CAPTOUCH5_REG_DEBUG_CP                                     0xDD
#define  CAPTOUCH5_REG_DIFFERENCE_COUNT0                            0xDE
#define  CAPTOUCH5_REG_DEBUG_BASELINE0                              0xE0
#define  CAPTOUCH5_REG_DEBUG_RAW_COUNT0                             0xE2
#define  CAPTOUCH5_REG_DEBUG_AVG_RAW_COUNT0                         0xE4
#define  CAPTOUCH5_REG_SYNC_COUNTER2                                0xE7
/** \} */

/**
 * \defgroup button_state Button State
 * \{
 */
#define  CAPTOUCH5_BUTTON_PRESSED                                   1
#define  CAPTOUCH5_BUTTON_NOT_PRESSED                               0
/** \} */

/**
 * \defgroup device_cfg0_data Device CFG0 Data
 * \{
 */
#define  CAPTOUCH5_CFG0_IIR_FILTER_ENABLED                          1
#define  CAPTOUCH5_CFG0_IIR_FILTER_DISABLED                         1
#define  CAPTOUCH5_CFG0_MED_FILTER_ENABLED                          1
#define  CAPTOUCH5_CFG0_MED_FILTER_DISABLED                         1
/** \} */

/**
 * \defgroup device_cfg1_data Device CFG1 Data
 * \{
 */
#define  CAPTOUCH5_CFG1_SYS_DIAGNOSTIC_ENABLED                      1
#define  CAPTOUCH5_CFG1_SYS_DIAGNOSTIC_DISABLED                     1
/** \} */

/**
 * \defgroup device_cfg2_data Device CFG2 Data
 * \{
 */
#define  CAPTOUCH5_CFG2_SHIELD_ENABLED                              1
#define  CAPTOUCH5_CFG2_SHIELD_DISABLED                             0
#define  CAPTOUCH5_CFG2_GUARD_SENS_ENABLED                          1
#define  CAPTOUCH5_CFG2_GUARD_SENS_DISABLED                         0
#define  CAPTOUCH5_CFG2_EMC_ENABLED                                 1
#define  CAPTOUCH5_CFG2_EMC_DISABLED                                0
#define  CAPTOUCH5_CFG2_AUTOMATIC_THRESHOLD_ENABLED                 1
#define  CAPTOUCH5_CFG2_AUTOMATIC_THRESHOLD_DISABLED                0
#define  CAPTOUCH5_CFG2_BUTTON_SLIDER_AUTO_RESET_DISABLED           0
#define  CAPTOUCH5_CFG2_BUTTON_SLIDER_AUTO_RESET_ENABLED_5_SEC      1
#define  CAPTOUCH5_CFG2_BUTTON_SLIDER_AUTO_RESET_ENABLED_20_SEC     2
#define  CAPTOUCH5_CFG2_PROXIMIYU_AUTO_RESET_DISABLED               0
#define  CAPTOUCH5_CFG2_PROXIMIYU_AUTO_RESET_ENABLED_5_SEC          1
#define  CAPTOUCH5_CFG2_PROXIMIYU_AUTO_RESET_ENABLED_20_SEC         2
/** \} */

/**
 * \defgroup device_cfg3_data Device CFG3 Data
 * \{
 */
#define  CAPTOUCH5_CFG3_POWER_SUPPLY_INTERNALLY                     0
#define  CAPTOUCH5_CFG3_POWER_SUPPLY_EXTERNALLY                     1
/** \} */

/**
 * \defgroup slider_configuration_data Slider Configuration Data
 * \{
 */
#define  CAPTOUCH5_SLIDER_SENS_0p1                                  0
#define  CAPTOUCH5_SLIDER_SENS_0p2                                  1
#define  CAPTOUCH5_SLIDER_SENS_0p3                                  2
#define  CAPTOUCH5_SLIDER_SENS_0p4                                  3
/** \} */

/**
 * \defgroup sens_configuration_data Sens Configuration Data
 * \{
 */
#define  CAPTOUCH5_BUTTON_SENS_ENABLED                              0xFFFF
#define  CAPTOUCH5_BUTTON_SENS_DISABLED                             0x0000
/** \} */

/**
 * \defgroup id_values Id Values
 * \{
 */
#define  CAPTOUCH5_DEVICE_ID                                       2566
#define  CAPTOUCH5_FAMILY_ID                                       154
/** \} */


/**
 * \defgroup device_process_state Device Process State
 * \{
 */
#define  CAPTOUCH5_ERROR                                            1
#define  CAPTOUCH5_NO_ERROR                                         0
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

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} captouch5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} captouch5_cfg_t;


typedef struct
{
  uint8_t button1;
  uint8_t button2;
  uint8_t button3;
  uint8_t button4;
}T_CAPTOUCH5_BUTTONS;

typedef struct
{
  uint8_t iirFilter;
  uint8_t medFilter;
}T_CAPTOUCH5_CONFIG0;

typedef struct
{
  uint8_t sysDiagnostic;
}T_CAPTOUCH5_CONFIG1;

typedef struct
{
  uint8_t proximityAutoReset;
  uint8_t buttonAutoReset;
  uint8_t autoThreshold;
  uint8_t emcSolution;
  uint8_t guardSens;
  uint8_t shieldSens;
}T_CAPTOUCH5_CONFIG2;

typedef struct
{
  uint8_t powerSupply;
}T_CAPTOUCH5_CONFIG3;


typedef struct
{
  T_CAPTOUCH5_CONFIG0 cfg0;
  T_CAPTOUCH5_CONFIG1 cfg1;
  T_CAPTOUCH5_CONFIG2 cfg2;
  T_CAPTOUCH5_CONFIG3 cfg3;
}T_CAPTOUCH5_DEVICE_CONFIG;

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
void captouch5_cfg_setup ( captouch5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param captouch5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPTOUCH5_RETVAL captouch5_init ( captouch5_t *ctx, captouch5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @param device_cfg Click configuration structure
 *
 * @description This function executes default configuration for CapTouch5 click.
 */
void captouch5_default_cfg ( captouch5_t *ctx, T_CAPTOUCH5_DEVICE_CONFIG *device_cfg );

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
void captouch5_generic_write ( captouch5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void captouch5_generic_read ( captouch5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for configuring device
 *
 * @param   ctx          Click object.
 * @param   device_cfg   Pointer to structure data which will be written.
 *
 * @description This function performs basic device configuration.
 */
void captouch5_device_config( captouch5_t *ctx, T_CAPTOUCH5_DEVICE_CONFIG *device_cfg );

/**
 * @brief Generic read 16bit data function
 *
 * @param   ctx         Click object.
 * @param   reg_addr    Register from which data should be read.
 *
 * @returns 16bit data from reg_addr.
 *
 * @description This function reads 16bit data from reg_addr address.
 */
uint16_t captouch5_read_two_bytes ( captouch5_t *ctx, uint8_t reg_addr );

/**
 * @brief Generic write 16bit data function
 *
 * @param  ctx           Click object.
 * @param  reg_addr      Register where data should be written.
 * @param  data_buf      OUTPUT data.
 *
 * @description This function writes 16bit data data_buf to address reg_addr.
 */
void captouch5_write_two_bytes ( captouch5_t *ctx, uint8_t reg_addr, uint16_t data_buf );

/**
 * @brief Generic read 8bit data function
 *
 * @param   ctx         Click object.
 * @param   reg_addr    Register address from which data should be read.
 *
 * @returns 8bit data from reg_addr.
 *
 * @description This function reads 8bit data from address reg_addr.
 */
uint8_t captouch5_read_byte ( captouch5_t *ctx, uint8_t reg_addr );

/**
 * @brief Generic write 8bit data function
 *
 * @param   ctx           Click object.
 * @param   reg_addr      Register where data should be written.
 * @param   data_buf      OUTPUT data.
 *
 * @description This function writes 8bit data from data_buf to address reg_addr.
 */
void captouch5_write_byte ( captouch5_t *ctx, uint8_t reg_addr, uint8_t data_buf );

/**
 * @brief Function for checking error
 *
 * @param   ctx         Click object.
 *
 * @returns             CAPTOUCH5_ERROR or CAPTOUCH5_NO_ERROR
 *
 * @description This function checks error occurence.
 */
uint8_t captouch5_process ( captouch5_t *ctx );

/**
 * @brief Function for geting device id
 *
 * @param   ctx         Click object.
 *
 * @returns             CAPTOUCH5_DEVICE_ID
 *
 * @description This function gets device id.
 */
uint16_t captouch5_get_device_id ( captouch5_t *ctx );

/**
 * @brief Function for geting family id
 *
 * @param   ctx         Click object.
 *
 * @returns             CAPTOUCH5_FAMILY_ID
 *
 * @description This function gets family id of click object ctx.
 */
uint8_t captouch5_get_family_id ( captouch5_t *ctx );

/**
 * @brief Function read button status
 *
 * @param   ctx           Click object.
 * @param   buttons       Pointer to struct wich will accept data read from device.
 * 
 * @description This function reads button status.
 */
void captouch5_read_button_status ( captouch5_t *ctx, T_CAPTOUCH5_BUTTONS *buttons );

/**
 * @brief Function for reading slider position
 *
 * @param   ctx           Click object.
 *
 * @returns               Data from slider.
 *
 * @description This function reads slider position.
 */
uint16_t captouch5_read_slider_position ( captouch5_t *ctx );

/**
 * @brief Function to reset device
 *
 * @param   ctx           Click object.
 *
 * @description This function resets device.
 */
void captouch5_software_reset ( captouch5_t *ctx );

/**
 * @brief Function for configuring sensor
 *
 * @param   ctx         Click object.
 * @param   sens_data   Data for configuring.
 *
 * @description This function performs sensor configuration.
 */
void captouch5_config_sensors ( captouch5_t *ctx, uint16_t sens_data );

/**
 * @brief Function for configuring slider
 *
 * @param   ctx           Click object.
 * @param   slider_data   Data for configuring.
 *
 * @description This function performs slider configuration.
 */
void captouch5_config_slider ( captouch5_t *ctx, uint8_t slider_data );


#ifdef __cplusplus
}
#endif
#endif  // _CAPTOUCH5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

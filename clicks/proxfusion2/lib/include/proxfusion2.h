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
 * \brief This file contains API for ProxFusion 2 Click driver.
 *
 * \addtogroup proxfusion2 ProxFusion 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXFUSION2_H
#define PROXFUSION2_H

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
#define PROXFUSION2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXFUSION2_RETVAL  uint8_t

#define PROXFUSION2_OK                                              0x00
#define PROXFUSION2_INIT_ERROR                                      0xFF
/** \} */

/**
 * \defgroup device_info Device Information Data
 * \{
 */
#define PROXFUSION2_REG_PRODUCT_NUMBER                              0x00
#define PROXFUSION2_REG_SOFTWARE_NUMBER                             0x01
#define PROXFUSION2_REG_HARDWARE_NUMBER                             0x02
/** \} */

/**
 * \defgroup ui_data Flags and user interface data
 * \{
 */
#define PROXFUSION2_REG_SYSTEM_FLAGS                                0x10
#define PROXFUSION2_REG_GLOBAL_EVENTS                               0x11
#define PROXFUSION2_REG_PROXFUSION_UI_FLAGS                         0x12
#define PROXFUSION2_REG_HYSTERESIS_UI_FLAGS                         0x13
#define PROXFUSION2_REG_HYSTERESIS_UI_OUTPUT_LSB                    0x14
#define PROXFUSION2_REG_HYSTERESIS_UI_OUTPUT_MSB                    0x15
#define PROXFUSION2_REG_ALS_UI_FLAGS                                0x16
#define PROXFUSION2_REG_ALS_UI_OUTPUT_LSB                           0x17
#define PROXFUSION2_REG_ALS_UI_OUTPUT_MSB                           0x18
#define PROXFUSION2_REG_HALL_EFFECT_UI_FLAGS                        0x19
#define PROXFUSION2_REG_HALL_EFFECT_UI_OUTPUT_LSB                   0x1A
#define PROXFUSION2_REG_HALL_EFFECT_UI_OUTPUT_MSB                   0x1B
#define PROXFUSION2_REG_TEMPERATURE_UI_FLAGS                        0x1C
#define PROXFUSION2_REG_TEMPERATURE_UI_OUTPUT_LSB                   0x1D
#define PROXFUSION2_REG_TEMPERATURE_UI_OUTPUT_MSB                   0x1E
/** \} */

/**
 * \defgroup channel_counts Channel counts (raw data)
 * \{
 */
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH0_LSB                      0x20
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH0_MSB                      0x21
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH1_LSB                      0x22
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH1_MSB                      0x23
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH2_LSB                      0x24
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH2_MSB                      0x25
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH3_LSB                      0x26
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH3_MSB                      0x27
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH4_LSB                      0x28
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH4_MSB                      0x29
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH5_LSB                      0x2A
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH5_MSB                      0x2B
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH6_LSB                      0x2C
#define PROXFUSION2_REG_CHANNEL_COUNTS_CH6_MSB                      0x2D
/** \} */

/**
 * \defgroup lta_values LTA values (filtered data)
 * \{
 */
#define PROXFUSION2_REG_LTA_VALUES_CH0_LSB                          0x30
#define PROXFUSION2_REG_LTA_VALUES_CH0_MSB                          0x31
#define PROXFUSION2_REG_LTA_VALUES_CH1_LSB                          0x32
#define PROXFUSION2_REG_LTA_VALUES_CH1_MSB                          0x33
/** \} */

/**
 * \defgroup proxfusion_sensor ProxFusion sensor settings
 * \{
 */
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_00                      0x40
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_01                      0x41
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_10                      0x42
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_11                      0x43

#define PROXFUSION2_REG_PROXFUSION_SETTINGS_20                      0x44
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_21                      0x45
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_30                      0x46
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_31                      0x47
#define PROXFUSION2_REG_PROXFUSION_SETTINGS_4                       0x48
/** \} */

/**
 * \defgroup proxfusion_ui ProxFusion UI settings
 * \{
 */
#define PROXFUSION2_REG_PROX_THRESHOLD_CH0                          0x50
#define PROXFUSION2_REG_PROX_THRESHOLD_CH1                          0x52
#define PROXFUSION2_REG_TOUCH_THRESHOLD_CH0                         0x51
#define PROXFUSION2_REG_TOUCH_THRESHOLD_CH1                         0x53
#define PROXFUSION2_REG_DISCRETE_UI_HALT_TIME                       0x54
/** \} */

/**
 * \defgroup hysteris_ui Hysteresis UI settings
 * \{
 */
#define PROXFUSION2_REG_HYSTERESIS_UI_SETTINGS                      0x60
#define PROXFUSION2_REG_HYSTERESIS_UI_FILTER_HALT_THRESHOLD         0x61
#define PROXFUSION2_REG_HYSTERESIS_UI_PROXIMITY_THRESHOLD           0x62
#define PROXFUSION2_REG_HYSTERESIS_UI_TOUCH_THRESHOLD               0x63
/** \} */

/**
 * \defgroup als_sensor ALS sensor settings
 * \{
 */
#define PROXFUSION2_REG_ALS_settings_0                              0x70
#define PROXFUSION2_REG_ALS_settings_1                              0x71
#define PROXFUSION2_REG_ALS_SETTINGS_FILTER_SPEED                   0x72
#define PROXFUSION2_REG_MULTIPLIERS_CH34                            0x73
/** \} */

/**
 * \defgroup als_ui ALS UI settings
 * \{
 */
#define PROXFUSION2_REG_ALS_DARK_THRESHOLD                           0x80
#define PROXFUSION2_REG_ALS_LIGHT_THRESHOLD                          0x81
#define PROXFUSION2_REG_ALS_RAW_TO_LUX_DIVIDER                       0x82
#define PROXFUSION2_REG_ALS_IR_COMPENSATION                          0x83
/** \} */

/**
 * \defgroup hall_sensor Hall-effect sensor settings
 * \{
 */
#define PROXFUSION2_REG_HALL_EFFECT_SETTINGS_0                       0x90
#define PROXFUSION2_REG_HALL_EFFECT_SETTINGS_1                       0x91
#define PROXFUSION2_REG_COMPENSATION_CH56                            0x92
#define PROXFUSION2_REG_MULTIPLIERS_CH56                             0x93
/** \} */

/**
 * \defgroup hall_ui Hall-effect switch UI settings
 * \{
 */
#define PROXFUSION2_REG_HALL_EFFECT_UI_SETTINGS                      0xA0
#define PROXFUSION2_REG_HALL_PROXIMITY_THRESHOLD                     0xA1
#define PROXFUSION2_REG_HALL_TOUCH_THRESHOLD                         0xA2
/** \} */

/**
 * \defgroup temp_settings Temperature monitoring UI settings
 * \{
 */
#define PROXFUSION2_REG_TEMPERATURE_UI_SETTINGS                      0xC0
#define PROXFUSION2_REG_MULTIPLIER_CH2                               0xC1
#define PROXFUSION2_REG_TEMPERATURE_CALIBRATION_0                    0xC2
#define PROXFUSION2_REG_TEMPERATURE_CALIBRATION_1                    0xC3
/** \} */

/**
 * \defgroup device_and_pw_settings Device and power mode settings
 * \{
 */
#define PROXFUSION2_REG_SYSTEM_SETTINGS                              0xD0
#define PROXFUSION2_REG_ACTIVE_CHANNELS                              0xD1
#define PROXFUSION2_REG_POWER_MODE_SETTINGS                          0xD2
#define PROXFUSION2_REG_NORMAL_POWER_MODE_REPORT_RATE                0xD3
#define PROXFUSION2_REG_LOW_POWER_MODE_REPORT_RATE                   0xD4
#define PROXFUSION2_REG_UALTRA_LOW_POWER_MODE_REPORT_RATE            0xD5
#define PROXFUSION2_REG_AUTO_MODE_TIMER                              0xD6
#define PROXFUSION2_REG_GLOBAL_EVENT_MASK                            0xD7
#define PROXFUSION2_REG_RDY_TIMEOUT_PERIOD                           0xD8
#define PROXFUSION2_REG_I2C_SETTINGS                                 0xD9
/** \} */

/**
 * \defgroup sys_flags System flags (R)
 * \{
 */
#define PROXFUSION2_SF_SHOW_RESET                                    0x80
#define PROXFUSION2_SF_NO_RESET                                      0x00
#define PROXFUSION2_SF_NORMAL_MODE                                   0x00
#define PROXFUSION2_SF_ULTRA_LOW_POWER_MODE                          0x10
#define PROXFUSION2_SF_LOW_POWER_MODE                                0x08
#define PROXFUSION2_SF_HALT_MODE                                     0x00
#define PROXFUSION2_SF_ACTIVE_ATI                                    0x04
#define PROXFUSION2_SF_NO_ATI                                        0x00
#define PROXFUSION2_SF_NO_NEW_EVENT                                  0x00
#define PROXFUSION2_SF_NEW_EVENT                                     0x02
#define PROXFUSION2_SF_NOT_PERFORMING_NM_UPDATE                      0x00
#define PROXFUSION2_SF_BUSY_PERFORMING_NM_UPDATE                     0x02
/** \} */

/**
 * \defgroup global Global events (R)
 * \{
 */
#define PROXFUSION2_GE_POWER_MODE_EVENT_ACTIVE                       0x40
#define PROXFUSION2_GE_SYS_EVENT_ACTIVE                              0x20
#define PROXFUSION2_GE_TEMP_EVENT_ACTIVE                             0x10
#define PROXFUSION2_GE_HYSTERESIS_UI_EVENT_ACTIVE                    0x08
#define PROXFUSION2_GE_ALS_EVENT_ACTIVE                              0x04
#define PROXFUSION2_GE_HALL_EVENT_ACTIVE                             0x02
#define PROXFUSION2_GE_PROXSENSE_EVENT_ACTIVE                        0x01
/** \} */

/**
 * \defgroup proxfusion_flags ProxFusion UI flags (R)
 * \{
 */
#define PROXFUSION2_PFUIF_CH1_TOUCH_DELTA_BELOW                      0x00
#define PROXFUSION2_PFUIF_CH0_TOUCH_DELTA_BELOW                      0x00
#define PROXFUSION2_PFUIF_CH1_TOUCH_DELTA_ABOVE                      0x20
#define PROXFUSION2_PFUIF_CH0_TOUCH_DELTA_ABOVE                      0x10
#define PROXFUSION2_PFUIF_CH1_PROXIMITY_DELTA_BELOW                  0x00
#define PROXFUSION2_PFUIF_CH0_PROXIMITY_DELTA_BELOW                  0x00
#define PROXFUSION2_PFUIF_CH1_PROXIMITY_DELTA_ABOVE                  0x02
#define PROXFUSION2_PFUIF_CH0_PROXIMITY_DELTA_ABOVE                  0x01
/** \} */

/**
 * \defgroup hysteris_flags Hysteresis UI flags (R)
 * \{
 */
#define PROXFUSION2_HIUIF_COUNTS_RISE_ABOVE_THE_LTA                  0x00
#define PROXFUSION2_HIUIF_COUNTS_FALL_BELOW_THE_LTA                  0x04
#define PROXFUSION2_HIUIF_DELTA_BELOW_TOUCH_THRESHOLD                0x00
#define PROXFUSION2_HIUIF_DELTA_ABOVE_TOUCH_THRESHOLD                0x02
#define PROXFUSION2_HIUIF_DELTA_BELOW_PROX_THRESHOLD                 0x00
#define PROXFUSION2_HIUIF_DELTA_ABOVE_PROX_THRESHOLD                 0x01
/** \} */

/**
 * \defgroup als_flags ALS UI flags (R)
 * \{
 */
#define PROXFUSION2_ALSUIF_LIGHT_INDICATION                          0x00
#define PROXFUSION2_ALSUIF_DARK_INDICATION                           0x80
/** \} */

/**
 * \defgroup hall_flags Hall-effect UI flags (R)
 * \{
 */
#define PROXFUSION2_HEUIF_FIELD_STRENGTH_BELOW_TOUCH_LEVEL           0x00
#define PROXFUSION2_HEUIF_FIELD_STRENGTH_ABOVE_TOUCH_LEVEL           0x04
#define PROXFUSION2_HEUIF_FIELD_STRENGTH_BELOW_PROX_LEVEL            0x00
#define PROXFUSION2_HEUIF_FIELD_STRENGTH_ABOVE_PROX_LEVEL            0x02
#define PROXFUSION2_HEUIF_NORTH_FIELD_PRESENT                        0x00
#define PROXFUSION2_HEUIF_SOUTH_FIELD_PRESENT                        0x01
/** \} */

/**
 * \defgroup temep_flags Temperature UI flags (R)
 * \{
 */
#define PROXFUSION2_TUIF_TEMPERATURE_BELOW_TRIP_LEVEL                0x00
#define PROXFUSION2_TUIF_TEMPERATURE_ABOVE_TRIP_LEVEL                0x80
/** \} */

/**
 * \defgroup proxfusion_settings ProxFusion settings 0_0 (RW)
 * \{
 */
#define PROXFUSION2_PFS00_CAPACITIVE_SENSING_MODE                    0x00
#define PROXFUSION2_PFS00_TX0_AND_TX1_DISABLED                       0x00
#define PROXFUSION2_PFS00_RX0_AND_RX1_DISABLED                       0x00
#define PROXFUSION2_PFS00_RX0_ENABLE                                 0x01
#define PROXFUSION2_PFS00_RX1_ENABLE                                 0x02
#define PROXFUSION2_PFS00_RX0_AND_RX1_ENABLE                         0x03
/** \} */

/**
 * \defgroup proxfusion_settings ProxFusion settings 0_1 (RW)
 * \{
 */
#define PROXFUSION2_PFS01_INDUCTIVE_SENSOR_MODE                      0x80
#define PROXFUSION2_PFS01_MULTIPLIER_RANGE_LARGE                     0x00
#define PROXFUSION2_PFS01_MULTIPLIER_RANGE_SMALL                     0x01
#define PROXFUSION2_PFS01_TX0_AND_TX1_DISABLED                       0x00
#define PROXFUSION2_PFS01_TX0_AND_TX1_ENABLE                         0x03
/** \} */

/**
 * \defgroup proxfusion_settings ProxFusion settings 1_0 (RW)
 * \{
 */
#define PROXFUSION2_PFS10_CAPACITOR_15pF                             0x00
#define PROXFUSION2_PFS10_CAPACITOR_60pF                             0x40
#define PROXFUSION2_PFS10_FREQUENCY_DIVIDER_1_2                      0x00
#define PROXFUSION2_PFS10_FREQUENCY_DIVIDER_1_4                      0x10
#define PROXFUSION2_PFS10_FREQUENCY_DIVIDER_1_8                      0x20
#define PROXFUSION2_PFS10_FREQUENCY_DIVIDER_1_16                     0x30
#define PROXFUSION2_PFS10_ATI_MODE_DISABLE                           0x00
#define PROXFUSION2_PFS10_PARTIAL_ATI                                0x01
#define PROXFUSION2_PFS10_SEMI_PARTIAL_ATI                           0x02
#define PROXFUSION2_PFS10_FULL_ATI                                   0x03
/** \} */

/**
 * \defgroup proxfusion_settings ProxFusion settings 1_1 (RW)
 * \{
 */
#define PROXFUSION2_PFS11_CAPACITOR_15pF                             0x00
#define PROXFUSION2_PFS11_CAPACITOR_60pF                             0x40
#define PROXFUSION2_PFS11_FREQUENCY_DIVIDER_1_2                      0x00
#define PROXFUSION2_PFS11_FREQUENCY_DIVIDER_1_4                      0x10
#define PROXFUSION2_PFS11_FREQUENCY_DIVIDER_1_8                      0x20
#define PROXFUSION2_PFS11_FREQUENCY_DIVIDER_1_16                     0x30
#define PROXFUSION2_PFS11_INTERNAL_RESISTOR_2_5uA_88kOhm             0x00
#define PROXFUSION2_PFS11_INTERNAL_RESISTOR_5uA_66kOhm               0x04
#define PROXFUSION2_PFS11_INTERNAL_RESISTOR_10uA_44kOhm              0x08
#define PROXFUSION2_PFS11_INTERNAL_RESISTOR_20uA_22kOhm              0x0C
#define PROXFUSION2_PFS11_ATI_MODE_DISABLE                           0x00
#define PROXFUSION2_PFS11_PARTIAL_ATI                                0x01
#define PROXFUSION2_PFS11_SEMI_PARTIAL_ATI                           0x02
#define PROXFUSION2_PFS11_FULL_ATI                                   0x03
/** \} */

/**
 * \defgroup proxfusion_settings ProxFusion settings 2_0 and 2_1 (RW)
 * \{
 */
#define PROXFUSION2_PFS201_ATI_BASE_VALUE_75                         0x00
#define PROXFUSION2_PFS201_ATI_BASE_VALUE_100                        0x40
#define PROXFUSION2_PFS201_ATI_BASE_VALUE_150                        0x80
#define PROXFUSION2_PFS201_ATI_BASE_VALUE_200                        0xC0
/** \} */

/**
 * \defgroup proxfusion_settings ProxFusion settings 4 (RW)
 * \{
 */
#define PROXFUSION2_PFS4_HYSTERESIS_UI_DISABLED                      0x00
#define PROXFUSION2_PFS4_HYSTERESIS_UI_ENABLE                        0x40
#define PROXFUSION2_PFS4_BIDIRECTIONAL_DETECTION_DISABLED            0x00
#define PROXFUSION2_PFS4_BIDIRECTIONAL_DETECTION_ENABLE              0x20
#define PROXFUSION2_PFS4_AC_FILTER_ENABLED                           0x00
#define PROXFUSION2_PFS4_AC_FILTER_DISABLED                          0x10
#define PROXFUSION2_PFS4_LONG_TERM_AVERAGE_BETA_VALUE_7              0x00
#define PROXFUSION2_PFS4_LONG_TERM_AVERAGE_BETA_VALUE_8              0x04
#define PROXFUSION2_PFS4_LONG_TERM_AVERAGE_BETA_VALUE_9              0x08
#define PROXFUSION2_PFS4_LONG_TERM_AVERAGE_BETA_VALUE_10             0x0C
#define PROXFUSION2_PFS4_AC_FILTER_BETA_VALUE_1                      0x00
#define PROXFUSION2_PFS4_AC_FILTER_BETA_VALUE_2                      0x01
#define PROXFUSION2_PFS4_AC_FILTER_BETA_VALUE_3                      0x02
#define PROXFUSION2_PFS4_AC_FILTER_BETA_VALUE_4                      0x03
/** \} */

/**
 * \defgroup hysterisis_settings Hysteresis UI settings (RW)
 * \{
 */
#define PROXFUSION2_HIUIS_TOUCH_HYSTERESIS_DISABLED                  0x00
#define PROXFUSION2_HIUIS_TOUCH_HYSTERESIS_1_8_OF_THRESHOLD          0x20
#define PROXFUSION2_HIUIS_TOUCH_HYSTERESIS_1_4_OF_THRESHOLD          0x10
#define PROXFUSION2_HIUIS_TOUCH_HYSTERESIS_1_16_OF_THRESHOLD         0x30
#define PROXFUSION2_HIUIS_PROXIMITY_HYSTERESIS_DISABLED              0x00
#define PROXFUSION2_HIUIS_PROXIMITY_HYSTERESIS_1_8_OF_THRESHOLD      0x02
#define PROXFUSION2_HIUIS_PROXIMITY_HYSTERESIS_1_4_OF_THRESHOLD      0x01
#define PROXFUSION2_HIUIS_PROXIMITY_HYSTERESIS_1_16_OF_THRESHOLD     0x03
/** \} */

/**
 * \defgroup various_macros
 * \{
 */
#define PROXFUSION2_TOUCH_IS_DETECTED                                0x01
#define PROXFUSION2_DARK_AMBIENT                                     0x01
#define PROXFUSION2_LIGHT_AMBIENT                                    0x00
#define PROXFUSION2_HALL_NORTH                                       0x00
#define PROXFUSION2_HALL_SOUTH                                       0x01

#define PROXFUSION2_HYSTERESIS_UI_OUTPUT                             0x14
#define PROXFUSION2_ALS_UI_OUTPUT                                    0x17
#define PROXFUSION2_HALL_EFFECT_UI_OUTPUT                            0x1A
#define PROXFUSION2_TEMPERATURE_UI_OUTPUT                            0x1D
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

    digital_in_t rdy;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} proxfusion2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rdy;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} proxfusion2_cfg_t;

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
 * @brief                               Config Object Initialization function.
 *
 * @param cfg                           Click configuration structure.
 *
 * @description                         This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void proxfusion2_cfg_setup ( proxfusion2_cfg_t *cfg );

/**
 * @brief                                      Initialization function.
 * @param ctx                                  Click object.
 * @param cfg                                  Click configuration structure.
 * 
 * @description                                This function initializes all necessary pins and peripherals used for this click.
 */
PROXFUSION2_RETVAL proxfusion2_init ( proxfusion2_t *ctx, proxfusion2_cfg_t *cfg );

/**
 * @brief                                     Click Default Configuration function.
 *
 * @param ctx                                 Click object.
 *
 * @description                               This function executes default configuration for ProxFusion2 click.
 */
uint8_t proxfusion2_default_cfg ( proxfusion2_t *ctx );

/**
 * @brief Function for writing one byte into the register
 *
 * @param proxfusion2                  Click object.
 * @param reg                          Register in which the data will be written
 * @param d_data                       Data which be written in register
 */
void proxfusion2_write_byte ( proxfusion2_t *ctx, uint8_t reg, uint8_t d_data );

/**
 * @brief Function for reads one byte from register
 *
 * @param proxfusion2                      Click object.
 * @param reg                              Register from which the data is read
 * @return                                 data that is read
 */
uint8_t proxfusion2_read_byte ( proxfusion2_t *ctx, uint8_t reg );

/**
 * @brief Function for reads two byte from register
 *
 * @param proxfusion2                      Click object.
 * @param reg                              Register from which the data is read
 * @return                                 data that is read
 */
uint16_t proxfusion2_read_data ( proxfusion2_t *ctx, uint8_t reg );

/**
 * @brief Function for configuration chip
 *
 * @param proxfusion2                      Click object.
 * @return                                 The function contains all necessary sensors for operation and measurement.
 */
void proxfusion2_default_config ( proxfusion2_t *ctx );

  /**
  * @brief                Function for init chip
  * @param proxfusion2            Click object.
  * @return                               Error code if init failed
  */
uint8_t proxfusion2_init_func ( proxfusion2_t *ctx );

/**
 * @brief                                Function for detect Touch
 * 
 *@param proxfusion2                     Click object.
 * 
 * @retval                               1 - TOUCH_DETECTED or 0 - NO_TOUCH
 */
uint8_t proxfusion2_detect_touch ( proxfusion2_t *ctx );

/**
 * @brief                               Function for read ambient light
 *
 * @param als_range                     ALS range (0-10)
 * @param proxfusion2                   Click object.
 * 
 * @retval                             1 - DARK or 0 - LIGHT
 */
uint8_t proxfusion2_detect_dark_light ( proxfusion2_t *ctx, uint8_t *als_range );

/**
 * @brief                               Function for read Hall-effect
 *
 * @param proxfusion2                   Click object.
 * 
 * @retval                              1 - NORTH, 2 - SOUTH or 0 - NO_HALL
 */
uint8_t proxfusion2_detect_hall ( proxfusion2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXFUSION2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

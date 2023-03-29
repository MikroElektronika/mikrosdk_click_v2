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
 * \brief This file contains API for SwipeSwitch Click driver.
 *
 * \addtogroup swipeswitch SwipeSwitch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SWIPESWITCH_H
#define SWIPESWITCH_H

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
#define SWIPESWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SWIPESWITCH_RETVAL  uint8_t

#define SWIPESWITCH_OK           0x00
#define SWIPESWITCH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_macros Register Macros
 * \{
 */
#define SWIPESWITCH_REG_DEVICE_INFO                            0x00  
#define SWIPESWITCH_REG_SYS_FLAGS                              0x01    
#define SWIPESWITCH_REG_TP_FLAGS                               0x02    
#define SWIPESWITCH_REG_COORDINATES                            0x03   
#define SWIPESWITCH_REG_CHANNEL_BYTES                          0x04   
#define SWIPESWITCH_REG_ACF_CH0                                0x05    
#define SWIPESWITCH_REG_ACF_CH1                                0x06    
#define SWIPESWITCH_REG_ACF_CH2                                0x07    
#define SWIPESWITCH_REG_ACF_CH3                                0x08   
#define SWIPESWITCH_REG_ACF_CH4                                0x09    
#define SWIPESWITCH_REG_ACF_CH5                                0x0A    
#define SWIPESWITCH_REG_ACF_CH6                                0x0B    
#define SWIPESWITCH_REG_LTA_CH0                                0x0C    
#define SWIPESWITCH_REG_LTA_CH1                                0x0D    
#define SWIPESWITCH_REG_LTA_CH2                                0x0E    
#define SWIPESWITCH_REG_LTA_CH3                                0x0F    
#define SWIPESWITCH_REG_LTA_CH4                                0x10    
#define SWIPESWITCH_REG_LTA_CH5                                0x11    
#define SWIPESWITCH_REG_LTA_CH6                                0x12    
#define SWIPESWITCH_REG_DELTA_CH0                              0x13    
#define SWIPESWITCH_REG_DELTA_CH1                              0x14    
#define SWIPESWITCH_REG_DELTA_CH2                              0x15    
#define SWIPESWITCH_REG_DELTA_CH3                              0x16    
#define SWIPESWITCH_REG_DELTA_CH4                              0x17    
#define SWIPESWITCH_REG_DELTA_CH5                              0x18    
#define SWIPESWITCH_REG_DELTA_CH6                              0x19    
#define SWIPESWITCH_REG_PROXSETTINGS_01                        0x80    
#define SWIPESWITCH_REG_PROXSETTINGS_23                        0x81    
#define SWIPESWITCH_REG_EVENT_MASK                             0x82    
#define SWIPESWITCH_REG_TIMEOUT_PERIODS                        0x83    
#define SWIPESWITCH_REG_REPORT_RATES                           0x84    
#define SWIPESWITCH_REG_THRESHOLDS_CH0                         0x85    
#define SWIPESWITCH_REG_TOUCH_THR_CH1_CH2                      0x86    
#define SWIPESWITCH_REG_TOUCH_THR_CH3_CH4                      0x87    
#define SWIPESWITCH_REG_TOUCH_THR_CH5_CH6                      0x88    
#define SWIPESWITCH_REG_ATI_TARGETS                            0x89    
#define SWIPESWITCH_REG_CHANNEL_SETTINGS                       0x8A   
#define SWIPESWITCH_REG_TAP_SETTINGS                           0x8B    
#define SWIPESWITCH_REG_SWIPE_SETTINGS                         0x8C  
/** \} */

/**
 * \defgroup event_macros Event Macros
 * \{
 */
#define SWIPESWITCH_EVENT_PROX                                 0x01
#define SWIPESWITCH_EVENT_TOUCH                                0x02
#define SWIPESWITCH_EVENT_TP                                   0x04
#define SWIPESWITCH_EVENT_ATI                                  0x08
#define SWIPESWITCH_EVENT_TAP                                  0x10
#define SWIPESWITCH_EVENT_SWIPE                                0x20
#define SWIPESWITCH_EVENT_LP                                   0x80
#define SWIPESWITCH_EVENTS_ALL                                 0xFF
/** \} */

/**
 * \defgroup gesture_macros Gesture Macros
 * \{
 */
#define SWIPESWITCH_GESTURE_TP                                 0x01
#define SWIPESWITCH_GESTURE_TAP                                0x02
#define SWIPESWITCH_GESTURE_SWIPE_UP                           0x04
#define SWIPESWITCH_GESTURE_SWIPE_DOWN                         0x08
#define SWIPESWITCH_GESTURE_SWIPE_LEFT                         0x10
#define SWIPESWITCH_GESTURE_SWIPE_RIGHT                        0x20
/** \} */

/**
 * \defgroup various_mode_macros Various Mode Macros
 * \{
 */
#define SWIPESWITCH_CH0_PROX                                   0x01
#define SWIPESWITCH_SHOW_RESET                                 0x80
#define SWIPESWITCH_ACK_RESET                                  0x80
#define SWIPESWITCH_REDO_ATI                                   0x10
#define SWIPESWITCH_EVENT_MODE                                 0x40


/**
 * \defgroup touch_macros Touch Macros
 * \{
 */
#define SWIPESWITCH_CH0_TOUCH                                  0x01
#define SWIPESWITCH_CH1_TOUCH                                  0x02
#define SWIPESWITCH_CH2_TOUCH                                  0x04
#define SWIPESWITCH_CH3_TOUCH                                  0x08
#define SWIPESWITCH_CH4_TOUCH                                  0x10
#define SWIPESWITCH_CH5_TOUCH                                  0x20
#define SWIPESWITCH_CH6_TOUCH                                  0x40
/** \} */

/**
 * \defgroup trackpad_flags Trackpad flags Macros
 * \{
 */
#define SWIPESWITCH_TPF_SEGMENT_0                              0x00
#define SWIPESWITCH_TPF_SEGMENT_1                              0x40
#define SWIPESWITCH_TPF_SEGMENT_2                              0x80
#define SWIPESWITCH_TPF_SEGMENT_3                              0xC0
#define SWIPESWITCH_TPF_SWIPE_RIGHT                            0x20
#define SWIPESWITCH_TPF_SWIPE_LEFT                             0x10
#define SWIPESWITCH_TPF_SWIPE_DOWN                             0x08
#define SWIPESWITCH_TPF_SWIPE_UP                               0x04
#define SWIPESWITCH_TPF_TAP                                    0x02
#define SWIPESWITCH_TPF_TP_ACTIVE                              0x01
/** \} */

/**
 * \defgroup prox_settings_0 Prox settings 0 Macros
 * \{
 */
#define SWIPESWITCH_PS0_AUTO_ATI_ON                            0x00
#define SWIPESWITCH_PS0_AUTO_ATI_OFF                           0x80
#define SWIPESWITCH_PS0_NORMAL_ATI_ACTIVE                      0x00
#define SWIPESWITCH_PS0_PARTIAL_ATI_ACTIVE                     0x40
#define SWIPESWITCH_PS0_NORMAL_ATI_BAND                        0x00
#define SWIPESWITCH_PS0_LARGE_ATI_BAND                         0x20
#define SWIPESWITCH_PS0_REDO_AN_ATI                            0x10
#define SWIPESWITCH_PS0_DEBUG_ATI_DISABLE                      0x00
#define SWIPESWITCH_PS0_DEBUG_ATI_ENABLE                       0x04
#define SWIPESWITCH_PS0_NORMAL_ANALOGUE_TIME                   0x00
#define SWIPESWITCH_PS0_INCREASED_ANALOGUE_TIME                0x02
#define SWIPESWITCH_PS0_NORMAL_HALTING                         0x00
#define SWIPESWITCH_PS0_Force_halt                             0x01
/** \} */

/**
 * \defgroup prox_settings_1 Prox settings 1 Macros
 * \{
 */
#define SWIPESWITCH_PS1_COMMUNICATION_WATCH_DOG_ENABLED        0x00
#define SWIPESWITCH_PS1_COMMUNICATION_WATCH_DOG_DISABLED       0x80
#define SWIPESWITCH_PS1_STREAMING_MODE                         0x00
#define SWIPESWITCH_PS1_EVENT_MODE                             0x40
#define SWIPESWITCH_PS1_LTA_BETA_1_512                         0x00
#define SWIPESWITCH_PS1_LTA_BETA_1_256                         0x10
#define SWIPESWITCH_PS1_LTA_BETA_1_128                         0x20
#define SWIPESWITCH_PS1_LTA_BETA_1_64                          0x30
#define SWIPESWITCH_PS1_ACF_BETA_1                             0x01
#define SWIPESWITCH_PS1_ACF_BETA_2                             0x02
#define SWIPESWITCH_PS1_ACF_BETA_3                             0x03
#define SWIPESWITCH_PS1_ACF_FILTER_OFF                         0x00
/** \} */

/**
 * \defgroup prox_settings_2 Prox settings 2 Macros
 * \{
 */
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_1                      0x00
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_2                      0x01
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_4                      0x02
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_8                      0x03
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_16                     0x04
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_32                     0x05
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_64                     0x06
#define SWIPESWITCH_PS2_NP_SEGMENT_RATE_128                    0x07
/** \} */

/**
 * \defgroup prox_settings_3 Prox settings 3 Macros
 * \{
 */
#define SWIPESWITCH_PS3_ACKNOWLEDGE_RESET                      0x80
#define SWIPESWITCH_PS3_IC_IN_ON_MODE                          0x00
#define SWIPESWITCH_PS3_IC_IN_OFF_MODE                         0x40
#define SWIPESWITCH_PS3_BIAS_CURRENT_5uA                       0x00
#define SWIPESWITCH_PS3_BIAS_CURRENT_10uA                      0x20
#define SWIPESWITCH_PS3_GROUND_Cx_PINS                         0x00
#define SWIPESWITCH_PS3_FLOAT_Cx_PINS                          0x10
#define SWIPESWITCH_PS3_NORMAL_CHARGING                        0x00
#define SWIPESWITCH_PS3_HALT_CHARGING                          0x08
#define SWIPESWITCH_PS3_CHARGING_FREQ_CH123456_2MHz            0x00
#define SWIPESWITCH_PS3_CHARGING_FREQ_CH123456_1MHz            0x02
#define SWIPESWITCH_PS3_CHARGING_FREQ_CH0_1MHz                 0x00
#define SWIPESWITCH_PS3_CHARGING_FREQ_CH0_500kHz               0x10
/** \} */

/**
 * \defgroup channels Channels Macros
 * \{
 */
#define SWIPESWITCH_CHANNEL_0                                  0x01
#define SWIPESWITCH_CHANNEL_1                                  0x02
#define SWIPESWITCH_CHANNEL_2                                  0x04
#define SWIPESWITCH_CHANNEL_3                                  0x08
#define SWIPESWITCH_CHANNEL_4                                  0x10
#define SWIPESWITCH_CHANNEL_5                                  0x20
#define SWIPESWITCH_CHANNEL_6                                  0x40
/** \} */


#define SWIPESWITCH_DEVICE_SLAVE_ADDRESS                       0x44

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

    digital_in_t rdy_in;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} swipeswitch_t;

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

} swipeswitch_cfg_t;

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
void swipeswitch_cfg_setup ( swipeswitch_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SWIPESWITCH_RETVAL swipeswitch_init ( swipeswitch_t *ctx, swipeswitch_cfg_t *cfg );

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
void swipeswitch_generic_write ( swipeswitch_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void swipeswitch_generic_read ( swipeswitch_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
  * @brief  Function that waits for the module to be ready for operation.
  * 
  * @param ctx          Click object.
  * 
  * @returns            0 or 1
  * 
  * @description This function waits for the module to be ready for operation
  */
uint8_t swipeswitch_wait_for_ready ( swipeswitch_t *ctx );

/**
  * @brief  Function for disable halt time
  * 
  * @param ctx          Click object.
  * 
  * @description This function disable halt time
  */
void swipeswitch_disable_halt_timeout ( swipeswitch_t *ctx );

/**
  * @brief  Function for disabled Event
  * 
  * @param ctx          Click object.
  * 
  * @description This function disable desired event.
  */
void swipeswitch_disable_events ( swipeswitch_t *ctx, uint8_t event );

 /**
  * @brief  Function for enabled Event
  * 
  * @param ctx          Click object.
  * 
  * @description This function anable desired event.
  */
void swipeswitch_enable_events ( swipeswitch_t *ctx, uint8_t event );

/**
  * @brief  Function for Event mode
  * 
  * @param ctx          Click object.
  * 
  * @description This function is for going to Event mode.
  */
void swipeswitch_go_to_event_mode ( swipeswitch_t *ctx );

/**
  * @brief  Function for Stream mode
  * 
  * @param ctx          Click object.
  * 
  * @description This function is for going to Stream mode.
  */
void swipeswitch_go_to_stream_mode ( swipeswitch_t *ctx );

/**
  * @brief  Function for reads system falgs
  * 
  * @param ctx          Click object.
  * @returns            Get System flag value.
  * 
  * @description This function reads system falgs.
  */
uint8_t swipeswitch_read_system_flags ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading event
  * 
  * @param ctx          Click object.
  * @returns            Get Event value.
  * 
  * @description This function reads event.
  */
uint8_t swipeswitch_read_events ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading Gestures
  * 
  * @param ctx          Click object.
  * returns             Gesture value.
  * 
  * @description This function reads Gestures.
  */
uint8_t swipeswitch_read_gestures ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading Trackpad falgs
  * 
  * @param ctx          Click object.
  * @returns            Gets Trackpad Flag.
  * 
  * @description This function reads Trackpad flag.
  */
uint8_t swipeswitch_read_trackpad_flags ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading Prox byte
  * 
  * @param ctx          Click object.
  * @returns            Reads Prox byte value.
  * 
  * @description This function reads Prox byte.
  */
uint8_t swipeswitch_read_prox_byte ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading Touch byte
  * 
  * @param ctx          Click object.
  * 
  * @description This function reads Touch byte.
  */
uint8_t swipeswitch_read_touch_byte ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading X coordinate
  * 
  * @param ctx          Click object.
  * @returns            Reads value of X coordinate. 
  * @description This function reads X coordinate.
  */
uint8_t swipeswitch_read_x_coordinate ( swipeswitch_t *ctx );

/**
  * @brief  Function for reading Y coordinate
  * 
  * @param ctx          Click object.
  * @returns            Reads value of Y coordinate.
  * @description This function reads Y coordinate.
  */
uint8_t swipeswitch_read_y_coordinate ( swipeswitch_t *ctx );

/**
  * @brief  Function for setting Touch Sensitivity
  * 
  * @param ctx          Click object.
  * 
  * @description This function set Touch Sensitivity.
  */
void swipeswitch_set_touch_sensitivity ( swipeswitch_t *ctx, uint8_t sensitivity );

/**
  * @brief  Function for setting Prox Sensitivity
  * 
  * @param ctx          Click object.
  * 
  * @description This function set Prox Sensitivity.
  */
void swipeswitch_set_prox_sensitivity ( swipeswitch_t *ctx, uint8_t sensitivity );

/**
  * @brief  Function for setting Event mask
  * 
  * @param ctx          Click object.
  * 
  * @description This function set Event mask.
  */
void swipeswitch_set_event_mask ( swipeswitch_t *ctx, uint8_t event_mask );

/**
  * @brief  Function for enabling channels
  * 
  * @param ctx          Click object.
  * 
  * @description This function enable channels.
  */
void swipeswitch_enable_channel ( swipeswitch_t *ctx, uint8_t channel );

/**
  * @brief  Function for disabling channels
  * 
  * @param ctx          Click object.
  * 
  * @description This function disable channels.
  */
void swipeswitch_disable_channel ( swipeswitch_t *ctx, uint8_t channel );

/**
  * @brief  Function for reading channel
  * 
  * @param ctx          Click object.
  * @returns            Returns value from selected channel.
  * @description This function reads channel.
  */
uint16_t swipeswitch_read_channel ( swipeswitch_t *ctx, uint8_t read_data, uint8_t channel );

/**
  * @brief  Function for setting tap timer limit
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets tap timer limit.
  */
void swipeswitch_set_tap_timer_limit ( swipeswitch_t *ctx, uint8_t time_limit );

/**
  * @brief  Function for setting tap threshold
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets tap threshold.
  */
void swipeswitch_set_tap_threshold ( swipeswitch_t *ctx, uint8_t threshold );

/**
  * @brief  Function for setting swipe timer limit
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets swipe timer limit.
  */
void swipeswitch_set_swipe_timer_limit ( swipeswitch_t *ctx, uint8_t time_limit );

/**
  * @brief  Function for setting swipe threshold
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets swipe threshold.
  */
void swipeswitch_set_swipe_threshold ( swipeswitch_t *ctx, uint8_t threshold );

/**
  * @brief  Function for setting report rate NM
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets NM report rate.
  */
void swipeswitch_set_report_rate_nm ( swipeswitch_t *ctx, uint8_t report_rate );

/**
  * @brief  Function for setting report rate LP
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets LP report rate.
  */
void swipeswitch_set_report_rate_lp ( swipeswitch_t *ctx, uint8_t report_rate );

/**
  * @brief  Function for setting segment rate 
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets segment rate.
  */
void swipeswitch_set_np_segment_rate ( swipeswitch_t *ctx, uint8_t segment_rate );

/**
  * @brief  Function for setting zoom timeout
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets zoom timeout.
  */
void swipeswitch_set_zoom_timeout ( swipeswitch_t *ctx, uint8_t timeout_period );

/**
  * @brief  Function for setting halt timeout
  * 
  * @param ctx          Click object.
  * 
  * @description This function sets halt timeout.
  */
void swipeswitch_set_halt_timeout ( swipeswitch_t *ctx, uint8_t halt_time );


#ifdef __cplusplus
}
#endif
#endif  // _SWIPESWITCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

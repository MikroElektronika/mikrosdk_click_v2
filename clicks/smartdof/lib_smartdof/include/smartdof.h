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
 * \brief This file contains API for Smart DOF Click driver.
 *
 * \addtogroup smartdof Smart DOF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SMARTDOF_H
#define SMARTDOF_H

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
#define SMARTDOF_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.bt      = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SMARTDOF_RETVAL  uint8_t

#define SMARTDOF_OK           0x00
#define SMARTDOF_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Slave address
 * \{
 */
#define SLAVE_ADDRESS                                      0x4A
/** \} */

/**
 * \defgroup boot_modes Boot Modes
 * \{
 */
#define SMARTDOF_BMODE_FW_UPDATE                           0x00
#define SMARTDOF_BMODE_NORMAL                              0x01
/** \} */

/**
 * \defgroup sensor_data_q_points Sensor Data Q Points
 * \{
 */
#define SMARTDOF_QPOINT_RAW_ACCEL                          0
#define SMARTDOF_QPOINT_ACCEL                              8
#define SMARTDOF_QPOINT_LINEAR_ACCEL                       8
#define SMARTDOF_QPOINT_GRAVITY                            8
#define SMARTDOF_QPOINT_RAW_GYRO                           0
#define SMARTDOF_QPOINT_GYRO_CALIB                         9
#define SMARTDOF_QPOINT_GYRO_UNCALIB                       9
#define SMARTDOF_QPOINT_RAW_MAGNETO                        0
#define SMARTDOF_QPOINT_MAGNET_CALIB                       4
#define SMARTDOF_QPOINT_MAGNET_UNCALIB                     4
#define SMARTDOF_QPOINT_ROT_VECT                           14
#define SMARTDOF_QPOINT_GAME_ROT_VECT                      14
#define SMARTDOF_QPOINT_GEOMAG_ROT_VECT                    14
#define SMARTDOF_QPOINT_TAP_DETECT                         0
#define SMARTDOF_QPOINT_STEP_DETECT                        0
#define SMARTDOF_QPOINT_STEP_COUNT                         0
#define SMARTDOF_QPOINT_SIG_MOTION                         0
#define SMARTDOF_QPOINT_STABIL_CLASS                       0
#define SMARTDOF_QPOINT_SHAKE_DETECT                       0
#define SMARTDOF_QPOINT_STABIL_DETECT                      0
#define SMARTDOF_QPOINT_PERS_ACT_CLASS                     0
#define SMARTDOF_QPOINT_ARVR_STABIL_ROT_VECT               14
#define SMARTDOF_QPOINT_ARVR_STABIL_GAME_ROT_VECT          14
#define SMARTDOF_QPOINT_GYRO_INT_ROT_VECT                  14
/** \} */

/**
 * \defgroup channels Channels
 * \{
 */
#define SMARTDOF_CHAN_CMD                                  0
#define SMARTDOF_CHAN_EXE                                  1
#define SMARTDOF_CHAN_CTRL                                 2
#define SMARTDOF_CHAN_INPUT_REP                            3
#define SMARTDOF_CHAN_WAKE_REP                             4
#define SMARTDOF_CHAN_GYRO_ROT_VECT                        5
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define SMARTDOF_CMD_ERR                                   0x01
#define SMARTDOF_CMD_COUNT                                 0x02
#define SMARTDOF_CMD_TARE                                  0x03
#define SMARTDOF_CMD_INIT                                  0x04
#define SMARTDOF_CMD_UNS_INIT                              0x84
#define SMARTDOF_CMD_SAVE_DCD                              0x06
#define SMARTDOF_CMD_ME_CALIB                              0x07
#define SMARTDOF_CMD_DCD_PERIOD_SAVE                       0x09
#define SMARTDOF_CMD_OSCIL                                 0x0A
#define SMARTDOF_CMD_CLEAR_DCD                             0x0B
/** \} */

/**
 * \defgroup sub_commands Sub Commands
 * \{
 */
#define SMARTDOF_CMD_CTR_SCMD_GET_CNT                      0x00
#define SMARTDOF_CMD_CTR_SCMD_CLEAR_CNT                    0x01
#define SMARTDOF_CMD_TARE_SCMD_TARE_NOW                    0x00
#define SMARTDOF_CMD_TARE_SCMD_PERS_TARE                   0x01
#define SMARTDOF_CMD_TARE_SCMD_SET_REORIENT                0x02
#define SMARTDOF_CMD_INIT_SCMD_NO_OP                       0x00
#define SMARTDOF_CMD_INIT_SCMD_ENT_SENS_HUB                0x01
/** \} */

/**
 * \defgroup report_ids Report IDs
 * \{
 */
#define SMARTDOF_REP_ID_GET_FEAT_REQ                       0xFE
#define SMARTDOF_REP_ID_SET_FEAT_CMD                       0xFD
#define SMARTDOF_REP_ID_GET_FEAT_RESP                      0xFC
#define SMARTDOF_REP_ID_PROD_ID_REQ                        0xF9
#define SMARTDOF_REP_ID_PROD_ID_RESP                       0xF8
#define SMARTDOF_REP_ID_FRS_WR_REQ                         0xF7
#define SMARTDOF_REP_ID_FRS_WR_DATA                        0xF6
#define SMARTDOF_REP_ID_FRS_WR_RESP                        0xF5
#define SMARTDOF_REP_ID_FRS_RD_REQ                         0xF4
#define SMARTDOF_REP_ID_FRS_RD_RESP                        0xF3
#define SMARTDOF_REP_ID_CMD_REQ                            0xF2
#define SMARTDOF_REP_ID_CMD_RESP                           0xF1
#define SMARTDOF_FEAT_REP_ID_BASE_TIMESTAMP                0xFB
#define SMARTDOF_FEAT_REP_ID_TIMESTAMP_REBASE              0xFA
#define SMARTDOF_FEAT_REP_ID_ACCEL                         0x01
#define SMARTDOF_FEAT_REP_ID_GYRO                          0x02
#define SMARTDOF_FEAT_REP_ID_MAGNET                        0x03
#define SMARTDOF_FEAT_REP_ID_LINEAR_ACCEL                  0x04
#define SMARTDOF_FEAT_REP_ID_ROT_VECTOR                    0x05
#define SMARTDOF_FEAT_REP_ID_GRAVITY                       0x06
#define SMARTDOF_FEAT_REP_ID_UNCALIB_GYRO                  0x07
#define SMARTDOF_FEAT_REP_ID_GAME_ROT_VECTOR               0x08
#define SMARTDOF_FEAT_REP_ID_GEOMAG_ROT_VECTOR             0x09
#define SMARTDOF_FEAT_REP_ID_PRESSURE                      0x0A
#define SMARTDOF_FEAT_REP_ID_AMBI_LIGHT                    0x0B
#define SMARTDOF_FEAT_REP_ID_HIMIDITY                      0x0C
#define SMARTDOF_FEAT_REP_ID_PROXY                         0x0D
#define SMARTDOF_FEAT_REP_ID_TEMPERATURE                   0x0E
#define SMARTDOF_FEAT_REP_ID_UNCALIB_MAG_FIELD             0x0F
#define SMARTDOF_FEAT_REP_ID_TAP_DETECT                    0x10
#define SMARTDOF_FEAT_REP_ID_STEP_COUNT                    0x11
#define SMARTDOF_FEAT_REP_ID_SIG_MOTION                    0x12
#define SMARTDOF_FEAT_REP_ID_STABIL_CLASS                  0x13
#define SMARTDOF_FEAT_REP_ID_RAW_ACCEL                     0x14
#define SMARTDOF_FEAT_REP_ID_RAW_GYRO                      0x15
#define SMARTDOF_FEAT_REP_ID_RAW_MAGNETO                   0x16
#define SMARTDOF_FEAT_REP_ID_SAR                           0x17
#define SMARTDOF_FEAT_REP_ID_STEP_DETECT                   0x18
#define SMARTDOF_FEAT_REP_ID_SHAKE_DETECT                  0x19
#define SMARTDOF_FEAT_REP_ID_FLIP_DETECT                   0x1A
#define SMARTDOF_FEAT_REP_ID_PICKUP_DETECT                 0x1B
#define SMARTDOF_FEAT_REP_ID_STABIL_DETECT                 0x1C
#define SMARTDOF_FEAT_REP_ID_PERS_ACT_CLASS                0x1E
#define SMARTDOF_FEAT_REP_ID_SLEEP_DETECT                  0x1F
#define SMARTDOF_FEAT_REP_ID_TILT_DETECT                   0x20
#define SMARTDOF_FEAT_REP_ID_POCKET_DETECT                 0x21
#define SMARTDOF_FEAT_REP_ID_CIRCLE_DETECT                 0x22
#define SMARTDOF_FEAT_REP_ID_HART_RATE_MONITOR             0x23
#define SMARTDOF_FEAT_REP_ID_ARVR_STABIL_ROT_VECT          0x28
#define SMARTDOF_FEAT_REP_ID_ARVR_GAME_STABIL_ROT_VECT     0x29
/** \} */

/**
 * \defgroup frs_report_ids Configuration reports
 * \{
 */
#define SMARTDOF_FRS_REP_ID_STATIC_CALIB_AGM               0x7979
#define SMARTDOF_FRS_REP_ID_NOMINAL_CALIB_AGM              0x4D4D
#define SMARTDOF_FRS_REP_ID_STATIC_CALIB_SRA               0x8A8A
#define SMARTDOF_FRS_REP_ID_NOMINAL_CALIB_SRA              0x4E4E
#define SMARTDOF_FRS_REP_ID_DYNAMIC_CALIB                  0x1F1F
#define SMARTDOF_FRS_REP_ID_MOTION_ENG_POW_MGMT            0xD3E2
#define SMARTDOF_FRS_REP_ID_SYS_ORIENT                     0x2D3E
#define SMARTDOF_FRS_REP_ID_PRIM_ACCEL_ORIENT              0x2D41
#define SMARTDOF_FRS_REP_ID_SCREEN_ROT_ACCEL_ORIENT        0x2D43
#define SMARTDOF_FRS_REP_ID_GYRO_ORIENT                    0x2D46
#define SMARTDOF_FRS_REP_ID_MAGNETO_ORIENT                 0x2D4C
#define SMARTDOF_FRS_REP_ID_ARVR_STABIL_ROT_VEC            0x3E2D
#define SMARTDOF_FRS_REP_ID_ARVR_STABIL_GAME_ROT_VEC       0x3E2E
#define SMARTDOF_FRS_REP_ID_SIG_MOTION_DETECT_CFG          0xC274
#define SMARTDOF_FRS_REP_ID_SHAKE_DETECT_CFG               0x7D7D
#define SMARTDOF_FRS_REP_ID_MAX_FUSION_PERIOD              0xD7D7
#define SMARTDOF_FRS_REP_ID_SERIAL_NUM                     0x4B4B
#define SMARTDOF_FRS_REP_ID_ENVIRO_SENS_PRESS              0x39AF
#define SMARTDOF_FRS_REP_ID_ENVIRO_SENS_TEMP               0x4D20
#define SMARTDOF_FRS_REP_ID_ENVIRO_SENS_HUMI               0x1AC9
#define SMARTDOF_FRS_REP_ID_ENVIRO_SENS_AMBI               0x39B1
#define SMARTDOF_FRS_REP_ID_ENVIRO_SENS_PROXI              0x4DA2
#define SMARTDOF_FRS_REP_ID_ALS_CALIB                      0xD401
#define SMARTDOF_FRS_REP_ID_PROXI_SENS_CALIB               0xD402
#define SMARTDOF_FRS_REP_ID_PICKUP_DETECT_CFG              0x1B2A
#define SMARTDOF_FRS_REP_ID_FLIP_DETECT_CFG                0xFC94
#define SMARTDOF_FRS_REP_ID_STAB_DETECT_CFG                0xED85
#define SMARTDOF_FRS_REP_ID_ACT_TRACK_CFG                  0xED88
#define SMARTDOF_FRS_REP_ID_SLEEP_DETECT_CFG               0xED87
#define SMARTDOF_FRS_REP_ID_TILT_DETECT_CFG                0xED89
#define SMARTDOF_FRS_REP_ID_POCK_DETECT_CFG                0xEF27
#define SMARTDOF_FRS_REP_ID_CIRC_DETECT_CFG                0xEE51
#define SMARTDOF_FRS_REP_ID_USER_REC                       0x74B4
#define SMARTDOF_FRS_REP_ID_MOTION_ENG_TIME_SRC_SEL        0xD403
#define SMARTDOF_FRS_REP_ID_UART_OUT_FORMAT_SEL            0xA1A1
#define SMARTDOF_FRS_REP_ID_GYROINT_ROT_VEC_CFG            0xA1A2
#define SMARTDOF_FRS_REP_ID_FUSION_CTRL_FLAGS              0xA1A3
/** \} */

/**
 * \defgroup frs_report_ids Sensor metadata reports
 * \{
 */
#define SMARTDOF_FRS_REP_ID_RAW_ACCEL                      0xE301
#define SMARTDOF_FRS_REP_ID_ACCEL                          0xE302
#define SMARTDOF_FRS_REP_ID_LINEAR_ACCEL                   0xE303
#define SMARTDOF_FRS_REP_ID_GRAVITY                        0xE304
#define SMARTDOF_FRS_REP_ID_RAW_GYRO                       0xE305
#define SMARTDOF_FRS_REP_ID_GYRO_CALIB                     0xE306
#define SMARTDOF_FRS_REP_ID_GYRO_UNCALIB                   0xE307
#define SMARTDOF_FRS_REP_ID_RAW_MAGNETO                    0xE308
#define SMARTDOF_FRS_REP_ID_MAGNETO_CALIB                  0xE309
#define SMARTDOF_FRS_REP_ID_MAGNETO_UNCALIB                0xE30A
#define SMARTDOF_FRS_REP_ID_ROT_VECTOR                     0xE30B
#define SMARTDOF_FRS_REP_ID_GAME_ROT_VECTOR                0xE30C
#define SMARTDOF_FRS_REP_ID_GEO_ROT_VECTOR                 0xE30D
#define SMARTDOF_FRS_REP_ID_PRESSURE                       0xE30E
#define SMARTDOF_FRS_REP_ID_AMBIENT_LIGHT                  0xE30F
#define SMARTDOF_FRS_REP_ID_HUMIDITY                       0xE310
#define SMARTDOF_FRS_REP_ID_PROXY                          0xE311
#define SMARTDOF_FRS_REP_ID_TEMPERATURE                    0xE312
#define SMARTDOF_FRS_REP_ID_TAP_DETECT                     0xE313
#define SMARTDOF_FRS_REP_ID_STEP_DETECT                    0xE314
#define SMARTDOF_FRS_REP_ID_STEP_COUNT                     0xE315
#define SMARTDOF_FRS_REP_ID_SIG_MOTION                     0xE316
#define SMARTDOF_FRS_REP_ID_STABIL_CLASS                   0xE317
#define SMARTDOF_FRS_REP_ID_SHAKE_DETECT                   0xE318
#define SMARTDOF_FRS_REP_ID_FLIP_DETECT                    0xE319
#define SMARTDOF_FRS_REP_ID_PICK_DETECT                    0xE31A
#define SMARTDOF_FRS_REP_ID_STABIL_DETECT                  0xE31B
#define SMARTDOF_FRS_REP_ID_PERS_ACT_CLASS                 0xE31C
#define SMARTDOF_FRS_REP_ID_SLEEP_DETECT                   0xE31D
#define SMARTDOF_FRS_REP_ID_TILT_DETECT                    0xE31E
#define SMARTDOF_FRS_REP_ID_POCKET_DETECT                  0xE31F
#define SMARTDOF_FRS_REP_ID_CIRCLE_DETECT                  0xE320
#define SMARTDOF_FRS_REP_ID_HEART_RATE_MON                 0xE321
#define SMARTDOF_FRS_REP_ID_ARVR_STABIL_ROT_VECTOR         0xE322
#define SMARTDOF_FRS_REP_ID_ARVR_STABIL_GAME_ROT_VECTOR    0xE323
#define SMARTDOF_FRS_REP_ID_GYRO_INTEG_ROT_VEC             0xE324
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
    digital_out_t bt;

    // Input pins 
    
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint8_t shtp_header[ 4 ];
    uint8_t send_data_buf[ 21 ];
    uint8_t rec_data_buf[ 1024 ];
    uint16_t data_len;

} smartdof_t;

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
    pin_name_t bt;
    pin_name_t int_pin;

    // Static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} smartdof_cfg_t;

/**
 * @brief Click product id response definition.
 */
typedef struct
{
    // Variables 
    uint8_t  *reset_cause; 
    uint16_t *sw_version; 
    uint32_t *sw_part_number; 
    uint32_t *sw_build_number; 
    uint16_t *sw_version_patch;

} smartdof_pir_t;

/**
 * @brief Click FRS read response definition.
 */
typedef struct
{
    // Variables 
    uint8_t  *data_length; 
    uint8_t  *read_status; 
    uint16_t *data_offset; 
    uint32_t *data_buffer; 
    uint16_t *frs_type;
    
} smartdof_rr_t;

/**
 * @brief Click set feature command definition.
 */
typedef struct
{
    // Variables 
    uint8_t  feature_report_id; 
    uint8_t  feature_flags; 
    uint16_t change_sensitivity; 
    uint32_t report_interval; 
    uint32_t batch_interval; 
    uint32_t sensor_specific_config;

} smartdof_sfc_t;

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
void smartdof_cfg_setup ( smartdof_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SMARTDOF_RETVAL smartdof_init ( smartdof_t *ctx, smartdof_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for SmartDof click.
 */
uint8_t smartdof_default_cfg ( smartdof_t *ctx );

/**
 * @brief  Sending data bytes via I2C.
 *
 * @param ctx          Click object.
 * @param write_data   Buffer that holds data to be sent.
 * @param n_bytes      Number of bytes to send.
 *
 * @description This function sends specified number of bytes (n_bytes) from data buffer (write_data[]) via I2C
 */
void smartdof_i2c_write ( smartdof_t *ctx, uint8_t *write_data, uint16_t n_bytes );

/**
 * @brief Receiving data bytes via I2C.
 *
 * @param ctx          Click object.
 * @param read_data    Buffer that holds data to be sent.
 * @param n_bytes      Number of bytes to send.
 *
 * @description This function receives number of bytes (n_bytes) via I2C and stores those bytes into data buffer (read_data[])
 */
void smartdof_i2c_read ( smartdof_t *ctx,  uint8_t *read_data, uint16_t n_bytes );

/**
 * @brief Getting state of INT pin
 *
 * @param ctx          Click object.
 *
 * @returns 0 if INT pin is in LOW state; 1 if INT pin is in HIGH state
 *
 * @description This function returns INT pin state
 */
uint8_t smartdof_int_get ( smartdof_t *ctx );

/**
 * @brief Setting RST pin state
 *
 * @param ctx          Click object.
 * @param pin_state    State of RST pin
 *
 * @description This function sets RST pin to HIGH state if pin_state is set to 1;
 * sets RST pin to LOW state if pin_state is set to 0
 *
 * @note RST pin resets the device if set to LOW (0) and than to HIGH (1)
 */
void smartdof_rst_set ( smartdof_t *ctx, uint8_t pin_state );

/**
 * @brief Setting BT pin state
 *
 * @param ctx          Click object.
 * @param pin_state    State of BT pin
 *
 * @description This function sets BT pin to HIGH state if pin_state is set to 1;
 * sets BT pin to LOW state if pin_state is set to 0
 * 
 * @note BT pin sets device into BOOT mode if held to LOW (0) during device reset
 */
void smartdof_bt_set ( smartdof_t *ctx, uint8_t pin_state );

/**
 * @brief Device reset
 *
 * @param ctx          Click object.
 * @param  boot_mode   Device boot mode (normal or dfu - fw update)
 *
 * @description This function resets device and sets it into normal or boot (dfu) mode
 */
void smartdof_device_reset ( smartdof_t *ctx, uint8_t boot_mode );

/**
 * @brief Q point (fixed point) value to float conversion
 *
 * @param sensor_data
 * @param sensor_q_point
 *
 * @returns converted floating point value
 *
 * @description This function converts fixed point value (sensor_data) 
 * with specified Q point (sensor_Qpoint) to floating point value (return value)
 * @note Each sensor has a specific Q point for its data
 *
 * @recomended Obtain Q point values via 'frs_read_request()' function
 */
float smartdof_q_point_to_float ( int16_t sensor_data, uint8_t sensor_q_point );

/**
 * @brief Sending data packet
 *
 * @param ctx              Click object.
 * @param channel_number   Channel for sending data
 * @param data_length      Length of data to be sent (in bytes, not including header bytes)
 * @param packet_data      Buffer that holds data to be sent (not including header bytes)
 *
 * @description  This function forms a packet of data by attaching proper header to data
 * by setting data length (data_length + 4), channel and channel sequence number bytes
 * 
 * @note This function auto increments channel sequence number every time data is sent over that channel
 * and the maximum number of bytes to be sent (not including header bytes) is 1020
 */
void smartdof_send_packet ( smartdof_t *ctx, uint8_t channel_number, uint16_t data_length, uint8_t *packet_data );

/**
 * @brief Receiving data packet
 *
 * @param ctx                   Click object.
 * @param n_cycles_timeout      Number of cycles to wait for INT pin to go LOW
 *
 * @returns 0 if no error occured during data reception; 1 if error occured during reception 
 *          ( 1 if INT pin did not go LOW during specifiod number of cycles ( n_cycles_timeout ) )
 *
 * @description This function receives data packet from device
 *
 * @note 
 * <pre>
 * This function waits for INT pin to go LOW
 * This function than receives 4 header bytes
 * This function than parses header bytes to get data length of entire packet and stores header bytes to header buffer
 * This function than waits for INT pin to go LOW again, receives entire packet and stores packet data to data buffer
 * </pre>
 * 
 * @recomended Retrieve header bytes, data length and data bytes with 'smartdof_getData()' function
 */
uint8_t smartdof_receive_packet ( smartdof_t *ctx, uint32_t n_cycles_timeout );

/**
 * @brief Getting received data
 *
 * @param ctx                   Click object.
 * @param data_header           Received header bytes
 * @param data_length           Length of received data (not including header bytes)
 * @param data_buffer           Received data bytes
 *
 * @description This function returns data received by 'smartdof_receive_packet()' function to user
 * @note This function returns received header bytes, data length in bytes (not including header bytes) and data bytes to user
 *
 * @recomanded Provide 'data_buffer[]' with size of 1020 bytes as that is maximum number of data bytes that can be received (not including header bytes)
 */
void smartdof_get_data ( smartdof_t *ctx, uint8_t *data_header, uint16_t *data_length, uint8_t *data_buffer );

/**
 * @brief Requesting product id
 *
 * @param ctx                   Click object.
 * 
 * @description This function sends product id request report to device
 */
void smartdof_product_id_request ( smartdof_t *ctx );


/**
 * @brief Receiving product id response
 *
 * @param ctx          Click object.
 * @param pir          Click product id response object.
 * <pre>
 * Structure Members:
 * - uint8_t reset_cause - last cause of the processor reset
 * - uint16_t sw_version - device software version
 * - uint32_t sw_part_number - device software part number
 * - uint32_t sw_build_number - device software build number
 * - uint16_t sw_version_patch - device software version patch
 * </pre>
 * 
 * @returns 0 if no error occured during data reception
 * @returns 1 if error occured during reception (INT pin did not go LOW during specifiod number of cycles (n_cycles_timeout))
 * @returns 1 if received data length does not equal 16 bytes (not including header bytes)
 * @returns 1 if report id does not equal product id response report (0xF8)
 *
 * @description
 * <pre>
 * - This function receives product id response report bytes
 * - This function than checks if it received correct report (correct data length and correct report id)
 * - This function than parses received data and returns parsed data to user
 * - Reset causes can be : 0 - Not Applicable, 1 - Power On Reset, 2 - Internal System Reset, 3 - Watchdog Timeout, 4 - External Reset, 5 - Other
 * </pre>
 */
uint8_t smartdof_product_id_response ( smartdof_t *ctx, smartdof_pir_t *pir );

/**
 * @brief Requesting FRS write
 *
 * @param ctx               Click object.
 * @param data_length       Length in 32-bit words of the record to be written
 * @param frs_type          Type of FRS record to be sent
 *
 * @description This function is used to initiate writing FRS record, by sending product FRS write request report to device
 * @note If the length of record (data_length) is set to 0 then the entire record is erased
 */
void smartdof_frs_write_request ( smartdof_t *ctx, uint16_t data_length, uint16_t frs_type );

/**
 * @brief Requesting FRS write data
 *
 * @param ctx               Click object.
 * @param data_offset       Offset (expressed in number of 32-bit data words) from the beginning of the FRS record
 * @param data_buffer       Two 32-bit words of data to be written to the FRS record
 *
 * @description This function sends FRS write data request report to device
 * @note This function is to be called after specifying FRS record to write to by 'smartdof_frsWriteRequest()' function
 */
void smartdof_frs_write_data_request ( smartdof_t *ctx, uint16_t data_offset, uint32_t *data_buffer );

/**
 * @brief Receiving FRS write response
 *
 * @param ctx               Click object.
 * @param frs_status        Status of previous write operation
 * @param data_offset       Offset ( expressed in number of 32-bit data words) from the beginning of the FRS record
 *
 * @returns 0 if no error occured during data reception
 * @returns 1 if error occured during reception (INT pin did not go LOW during specifiod number of cycles (n_cycles_timeout))
 * @returns 1 if received data length does not equal 4 bytes (not including header bytes)
 * @returns 1 if report id does not equal product id response report (0xF5)
 *
 * @description
 * <pre>
 *  This function receives FRS write response report bytes
 *  This function than checks if it received correct report (correct data length and correct report id)
 *  This function than parses received data and returns parsed data to user
 *  This function is to be called after 'smartdof_frsWriteRequest()' and 'smartdof_frsWriteDataRequest()' functions
 * </pre>
 */
uint8_t smartdof_frs_write_response ( smartdof_t *ctx, uint8_t *frs_status, uint16_t *data_offset );

/**
 * @brief Requesting FRS read
 *
 * @param ctx               Click object.
 * @param data_offset       Offset ( expressed in number of 32-bit data words) from the beginning of the FRS record
 * @param frs_type          Type of FRS record to read
 * @param data_size         Number of 32-bit data words to read
 *
 * @description This function sends FRS read request report to device; If the data size is set to zero, 
 * then the entire record beginning at the offset value (data_offset) is returned
 */
void smartdof_frs_read_request ( smartdof_t *ctx, uint16_t data_offset, uint16_t frs_type, uint16_t data_size );

/**
 * @brief Receiving FRS read response
 *
 * @param ctx               Click object.
 * @param rr                Click FRS read response object.
 * <pre>
 * Structure Members:
 * - uint8_t data_length - number of received 32-bit data words
 * - uint8_t read_status - status of FRS read operation
 * - uint16_t data_offset - offset ( expressed in number of 32-bit data words) from the beginning of the FRS record
 * - uint32_t data_buffer[] - buffer in which data words are to be stored
 * - uint16_t frs_type - FRS record type to be read
 *  </pre>
 *
 * @returns 0 if no error occured during data reception
 * @returns 1 if error occured during reception (INT pin did not go LOW during specifiod number of cycles (n_cycles_timeout))
 * @returns 1 if received data length does not equal 16 bytes (not including header bytes)
 * @returns 1 if report id does not equal product id response report (0xF3)
 *
 * @description
 * <pre>
 * This function receives FRS read response report bytes
 * This function than checks if it received correct report (correct data length and correct report id)
 * This function than parses received data and returns parsed data to user
 * Once a read request has been received, the FSP3xx generates read responses until the request record or portion of a record is returned
 * Read status can be : 0 - no error 1, - unrecognized FRS type, 2 - busy, 3 - read record completed, 4 - offset out of range, 5 - record empty, 
 *                      6 - read block completed (if block size requested), 7 - read block completed and read record completed,
 *                      8 - device error (DFU flash memory device unavailable), 9-15 - reserved
 * </pre>                           
 */
uint8_t smartdof_frs_read_response ( smartdof_t *ctx,  smartdof_rr_t *rr );

/**
 * @brief Requesting command
 *
 * @param ctx                  Click object.
 * @param command_type         Command type to be requested [range : 1 - 127]
 * @param command_parameters   Buffer that holds command parameters [parameter interpretation is defined for each command]
 *
 * @description This function sends command request report to device
 * @note This function is used to ask the device to perform some special operation or report some special data that is not part of normal sensor operation
 */
void smartdof_command_request ( smartdof_t *ctx, uint8_t command_type, uint8_t *command_parameters );

/**
 * @brief Receiving command response
 *
 * @param ctx                   Click object.
 * @param response_parameters   Buffer that holds command response parameters
 *
 * @returns 0 if no error occured during data reception
 * @returns 1 if error occured during reception (INT pin did not go LOW during specifiod number of cycles (n_cycles_timeout))
 * @returns 1 if received data length does not equal 16 bytes (not including header bytes)
 * @returns 1 if report id does not equal product id response report (0xF1)
 *
 * @description
 * <pre>
 * This function receives command response report bytes
 * This function than checks if it received correct report (correct data length and correct report id)
 * This function than parses received data and returns parsed data to user
 * This function is used to report the results of some special operation or some special data that is not part of normal sensor operation
 * </pre>
 */
uint8_t smartdof_command_response ( smartdof_t *ctx, uint8_t *response_parameters );

/**
 * @brief Requesting get feature request
 *
 * @param ctx                   Click object.
 * @param feature_report_id     Report id of the feature to be requested
 *
 * @description This function sends get feature request report to device
 */
void smartdof_get_feature_request ( smartdof_t *ctx, uint8_t feature_report_id );

/**
 * @brief Requesting set feature command
 *
 * @param ctx           Click object.
 * @param sfc           Click set feature command object.
 * <pre>
 * Structure Members:
 * - [in] uint8_t feature_report_id   - report id of the feature to be set
 * - [in] uint8_t feature_flags       - bit field that enables various device features
 * - [in] uint16_t change_sensitivity - 16-bit signed fixed point integer representing the value a sensor output must exceed in order to trigger
                                            another input report
 * - [in] uint32_t report_interval    - 32-bit unsigned integer representing the interval in microseconds between asynchronous input reports and the time
 * - [in] uint32_t batch_interval     - 32-bit unsigned integer controlling the maximum delay (in microseconds) between the time that a sensor is sampled
 *                                      that its data can be reported. The value 0 is reserved for do not delay and the value 0xFFFFFFFF is reserved
 *                                      for never trigger delivery on the basis of elapsed time
 * - [in] uint32_t sensor_specific_config - 32-bit field available for use by sensors requiring additional configuration options
 * </pre>
 *
 * @description This function sends set feature request report to device
 */
void smartdof_set_feature_command ( smartdof_t *ctx, smartdof_sfc_t *sfc );

/**
 * @brief Receiving get feature response
 *
 * @param ctx           Click object.
 * @param sfc           Click set feature command object.
 * <pre>
 * Structure Members:
 * - [out] uint8_t feature_report_id   - report id of the feature to be set
 * - [out] uint8_t feature_flags       - bit field that enables various device features
 * - [out] uint16_t change_sensitivity - 16-bit signed fixed point integer representing the value a sensor output must exceed in order to trigger
                                            another input report
 * - [out] uint32_t report_interval    - 32-bit unsigned integer representing the interval in microseconds between asynchronous input reports and the time
 * - [out] uint32_t batch_interval     - 32-bit unsigned integer controlling the maximum delay (in microseconds) between the time that a sensor is sampled
 *                                      that its data can be reported. The value 0 is reserved for do not delay and the value 0xFFFFFFFF is reserved
 *                                      for never trigger delivery on the basis of elapsed time
 * - [out] uint32_t sensor_specific_config - 32-bit field available for use by sensors requiring additional configuration options
 * </pre>
 * 
 * @returns 0 if no error occured during data reception
 * @returns 1 if error occured during reception (INT pin did not go LOW during specifiod number of cycles (n_cycles_timeout))
 * @returns 1 if received data length does not equal 17 bytes (not including header bytes)
 * @returns 1 if report id does not equal product id response report (0xFC)
 *
 * @description
 * <pre>
 * This function receives get feature response report bytes
 * This function than checks if it received correct report (correct data length and correct report id)
 * This function than parses received data and returns parsed data to user
 * </pre>
 */
uint8_t smartdof_get_feature_response ( smartdof_t *ctx, smartdof_sfc_t *sfc );

/**
 * @brief Requesting force sensor flush
 *
 * @param ctx           Click object.
 * @param sensor_id     Report id of the sensor whose data is to be flushed
 * 
 * @description This function sends force sensor flush request report to device
 * @note This function is executed in order to trigger a flush of outstanding data from a given sensor (e.g. before its batch settings would require it)
 */
void smartdof_force_sensor_flush ( smartdof_t *ctx, uint8_t sensor_id );

/**
 * @brief Receiving flush completed response
 *
 * @param ctx           Click object.
 * @param sensor_id     Report id of the sensor whose data was flushed
 *
 * @returns 0 if no error occured during data reception
 * @returns 1 if error occured during reception (INT pin did not go LOW during specifiod number of cycles (n_cycles_timeout))
 * @returns 1 if received data length does not equal 2 bytes (not including header bytes)
 * @returns 1 if report id does not equal product id response report (0xEF)
 *
 * @description
 * <pre>
 * This function receives flush completed response report bytes
 * This function than checks if it received correct report (correct data length and correct report id)
 * This function than parses received data and returns parsed data to user
 * </pre>
 */
uint8_t smartdof_flush_completed ( smartdof_t *ctx, uint8_t * sensor_id );

#ifdef __cplusplus
}
#endif
#endif  // _SMARTDOF_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

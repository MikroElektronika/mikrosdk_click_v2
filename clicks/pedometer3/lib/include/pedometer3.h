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
 * \brief This file contains API for Pedometer 3 Click driver.
 *
 * \addtogroup pedometer3 Pedometer 3 Click Driver
 * @{
 */

#ifndef PEDOMETER3_H
#define PEDOMETER3_H

#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define PEDOMETER3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.trg     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.it2     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup select_com Communication
 * \{
 */
#define PEDOMETER3_MASTER_I2C 0 
#define PEDOMETER3_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PEDOMETER3_RETVAL  uint8_t

#define PEDOMETER3_OK           0x00
#define PEDOMETER3_ERROR        0xFF
#define PEDOMETER3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Map registers
 * \{
 */
#define PEDOMETER3_REG_MANUFACTURING_ID        0x00
#define PEDOMETER3_REG_PART_ID                 0x01
#define PEDOMETER3_REG_X_AXIS_HIGH_PASS_LOW    0x02
#define PEDOMETER3_REG_X_AXIS_HIGH_PASS_HIGH   0x03
#define PEDOMETER3_REG_Y_AXIS_HIGH_PASS_LOW    0x04
#define PEDOMETER3_REG_Y_AXIS_HIGH_PASS_HIGH   0x05
#define PEDOMETER3_REG_Z_AXIS_HIGH_PASS_LOW    0x06
#define PEDOMETER3_REG_Z_AXIS_HIGH_PASS_HIGH   0x07
#define PEDOMETER3_REG_X_AXIS_OUTPUT_LOW       0x08
#define PEDOMETER3_REG_X_AXIS_OUTPUT_HIGH      0x09
#define PEDOMETER3_REG_Y_AXIS_OUTPUT_LOW       0x0A
#define PEDOMETER3_REG_Y_AXIS_OUTPUT_HIGH      0x0B
#define PEDOMETER3_REG_Z_AXIS_OUTPUT_LOW       0x0C
#define PEDOMETER3_REG_Z_AXIS_OUTPUT_HIGH      0x0D
#define PEDOMETER3_REG_PAD_STEP_LOW            0x0E
#define PEDOMETER3_REG_PAD_STEP_HIGH           0x0F
#define PEDOMETER3_REG_COMMAND_TEST_RESPONSE   0x10
#define PEDOMETER3_REG_WHO_AM_I                0x11
#define PEDOMETER3_REG_CURRENT_TILT_POSITION   0x12
#define PEDOMETER3_REG_PREVIOUS_TILT_POSITION  0x13
#define PEDOMETER3_REG_INS1                    0x14
#define PEDOMETER3_REG_INS2                    0x15
#define PEDOMETER3_REG_INS3                    0x16
#define PEDOMETER3_REG_STATUS                  0x17
#define PEDOMETER3_REG_INT_REL                 0x19
#define PEDOMETER3_REG_CONTROL_1               0x1A
#define PEDOMETER3_REG_CONTROL_2               0x1B
#define PEDOMETER3_REG_CONTROL_3               0x1C
#define PEDOMETER3_REG_CONTROL_4               0x1D
#define PEDOMETER3_REG_CONTROL_5               0x1E
#define PEDOMETER3_REG_OUTPUT_DATA_CONTROL     0x1F
#define PEDOMETER3_REG_INTERRUPT_CONTROL_1     0x20
#define PEDOMETER3_REG_INTERRUPT_CONTROL_2     0x21
#define PEDOMETER3_REG_INTERRUPT_CONTROL_3     0x22
#define PEDOMETER3_REG_INTERRUPT_CONTROL_4     0x23
#define PEDOMETER3_REG_INTERRUPT_CONTROL_5     0x24
#define PEDOMETER3_REG_INTERRUPT_CONTROL_6     0x25
#define PEDOMETER3_REG_INTERRUPT_CONTROL_7     0x26
#define PEDOMETER3_REG_TILT_TIMER              0x27
#define PEDOMETER3_REG_TAP_REPORT_CONTROL      0x28
#define PEDOMETER3_REG_DOUBLE_TAP_EVENT        0x29
#define PEDOMETER3_REG_TAP_THRESHOLD_HIGH      0x2A
#define PEDOMETER3_REG_TAP_THRESHOLD_LOW       0x2B
#define PEDOMETER3_REG_FTD                     0x2C
#define PEDOMETER3_REG_STD                     0x2D
#define PEDOMETER3_REG_TLT                     0x2E
#define PEDOMETER3_REG_TWS                     0x2F
#define PEDOMETER3_REG_FREE_FALL_THRESHOLD     0x30
#define PEDOMETER3_REG_FREE_FALL_COUNTER       0x31
#define PEDOMETER3_REG_FREE_FALL_CONTROL       0x32
#define PEDOMETER3_REG_TILT_ANGLE_LL           0x34
#define PEDOMETER3_REG_TILT_ANGLE_HL           0x35
#define PEDOMETER3_REG_HYSTERESIS_SET          0x36
#define PEDOMETER3_REG_LOW_POWER_CONTROL       0x37
#define PEDOMETER3_REG_WUFTH                   0x3C
#define PEDOMETER3_REG_BTSWUFTH                0x3D
#define PEDOMETER3_REG_BTSTH                   0x3E
#define PEDOMETER3_REG_BTS_MOTION_DETECTION    0x3F
#define PEDOMETER3_REG_WUF_MOTION_DETECTION    0x40
#define PEDOMETER3_REG_PED_STPWM_LOW           0x41
#define PEDOMETER3_REG_PED_STPWM_HIGH          0x42
#define PEDOMETER3_REG_PEDOMETER_CONTROL_1     0x43
#define PEDOMETER3_REG_PEDOMETER_CONTROL_2     0x44
#define PEDOMETER3_REG_PEDOMETER_CONTROL_3     0x45
#define PEDOMETER3_REG_PEDOMETER_CONTROL_4     0x46
#define PEDOMETER3_REG_PEDOMETER_CONTROL_5     0x47
#define PEDOMETER3_REG_PEDOMETER_CONTROL_6     0x48
#define PEDOMETER3_REG_PEDOMETER_CONTROL_7     0x49
#define PEDOMETER3_REG_PEDOMETER_CONTROL_8     0x4A
#define PEDOMETER3_REG_PEDOMETER_CONTROL_9     0x4B
#define PEDOMETER3_REG_PEDOMETER_CONTROL_10    0x4C
#define PEDOMETER3_REG_SELF_TEST               0x4D
#define PEDOMETER3_REG_BUFFER_CONTROL_1        0x5A
#define PEDOMETER3_REG_BUFFER_CONTROL_2        0x5B
#define PEDOMETER3_REG_BUFFER_STATUS_1         0x5C
#define PEDOMETER3_REG_BUFFER_STATUS_2         0x5D
#define PEDOMETER3_REG_BUFFER_CLEAR            0x5E
#define PEDOMETER3_REG_BUFFER_READ             0x5F
/** \} */

/**
 * \defgroup tilt_position Tilt Position
 * \{
 */
#define PEDOMETER3_POSITON_BIT_LEFT_X_NEGATIVE       0x20
#define PEDOMETER3_POSITON_BIT_RIGHT_X_POSITIVE      0x10
#define PEDOMETER3_POSITON_BIT_DOWN_Y_NEGATIVE       0x08
#define PEDOMETER3_POSITON_BIT_UP_Y_POSITIVE         0x04
#define PEDOMETER3_POSITON_BIT_FACE_DOWN_Y_NEGATIVE  0x02
#define PEDOMETER3_POSITON_BIT_FACE_UP_Y_POSITIVE    0x01
/** \} */

/**
 * \defgroup int1_source Interrupt Source 1
 * \{
 */
#define PEDOMETER3_INS1_STPOVI 0x80
#define PEDOMETER3_INS1_STPWMI 0x40
#define PEDOMETER3_INS1_TLE    0x20
#define PEDOMETER3_INS1_TRI    0x10
#define PEDOMETER3_INS1_TDO    0x08
#define PEDOMETER3_INS1_TUO    0x04
#define PEDOMETER3_INS1_TFD    0x02
#define PEDOMETER3_INS1_TFU    0x01
/** \} */

/**
 * \defgroup int2_source Interrupt Source 2
 * \{
 */
#define PEDOMETER3_INS2_FFS              0x80
#define PEDOMETER3_INS2_BFI              0x40
#define PEDOMETER3_INS2_WMI              0x20
#define PEDOMETER3_INS2_DRDY             0x10
#define PEDOMETER3_INS2_TDTS_NO_TAP      0x00
#define PEDOMETER3_INS2_TDTS_SINGLE_TAP  0x04
#define PEDOMETER3_INS2_TDTS_DOUBLE_TAP  0x08
#define PEDOMETER3_INS2_STPINCI          0x02
#define PEDOMETER3_INS2_TPS              0x01
/** \} */

/**
 * \defgroup int3_source Interrupt Source 3
 * \{
 */
#define PEDOMETER3_INS3_WUFS 0x80
#define PEDOMETER3_INS3_BTS  0x40
#define PEDOMETER3_INS3_XNWU 0x20
#define PEDOMETER3_INS3_XPWU 0x10
#define PEDOMETER3_INS3_YNWU 0x08
#define PEDOMETER3_INS3_YPWU 0x04
#define PEDOMETER3_INS3_ZNWU 0x02
#define PEDOMETER3_INS3_ZPWU 0x01
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define PEDOMETER3_STATUS_NO_INT        0x00
#define PEDOMETER3_STATUS_INT_ACTIVE    0x10
#define PEDOMETER3_STATUS_BACK_TO_SLEEP 0x00
#define PEDOMETER3_STATUS_WAKE_UP       0x01
/** \} */

/**
 * \defgroup ctrl1 Control register 1
 * \{
 */
#define PEDOMETER3_CNTL1_MODE_STAND_BY         0x00
#define PEDOMETER3_CNTL1_MODE_LOW_POWER        0x80
#define PEDOMETER3_CNTL1_RES_MODE_HIGHER_NOISE 0x00
#define PEDOMETER3_CNTL1_RES_MODE_LOWER_NOISE  0x40
#define PEDOMETER3_CNTL1_DATA_READY_DISABLE    0x00
#define PEDOMETER3_CNTL1_DATA_READY_ENABLE     0x20
#define PEDOMETER3_CNTL1_G_RANGE_2g            0x00
#define PEDOMETER3_CNTL1_G_RANGE_4g            0x08
#define PEDOMETER3_CNTL1_G_RANGE_8g            0x10
#define PEDOMETER3_CNTL1_TAP_DISABLE           0x00
#define PEDOMETER3_CNTL1_TAP_ENABLE            0x04
#define PEDOMETER3_CNTL1_PEDOMETER_DISABLE     0x00
#define PEDOMETER3_CNTL1_PEDOMETER_ENABLE      0x02
#define PEDOMETER3_CNTL1_TILT_DISABLE          0x00
#define PEDOMETER3_CNTL1_TILT_ENABLE           0x01
/** \} */

/**
 * \defgroup ctrl2 Control register 2
 * \{
 */
#define PEDOMETER3_CNTL2_SOFTWARE_RESET_ACTIVE     0x80
#define PEDOMETER3_CNTL2_SOFTWARE_RESET_NO_ACTIVE  0x00
#define PEDOMETER3_CNTL2_COMMAND_TEST_ACTIVE       0x40
#define PEDOMETER3_CNTL2_COMMAND_TEST_NO_ACTIVE    0x00
#define PEDOMETER3_CNTL2_LEFT_STATE_ENABLE         0x20
#define PEDOMETER3_CNTL2_RIGHT_STATE_ENABLE        0x10
#define PEDOMETER3_CNTL2_DOWN_STATE_ENABLE         0x08
#define PEDOMETER3_CNTL2_UP_STATE_ENABLE           0x04
#define PEDOMETER3_CNTL2_FACE_DOWN_STATE_ENABLE    0x02
#define PEDOMETER3_CNTL2_FACE_UP_STATE_ENABLE      0x01
/** \} */

/**
 * \defgroup ctrl3 Control register 3
 * \{
 */
#define PEDOMETER3_CNTL3_OTP_OUTPUT_DATA_RATE_1_563Hz   0x00
#define PEDOMETER3_CNTL3_OTP_OUTPUT_DATA_RATE_6_25Hz    0x40
#define PEDOMETER3_CNTL3_OTP_OUTPUT_DATA_RATE_12_5Hz    0x80
#define PEDOMETER3_CNTL3_OTP_OUTPUT_DATA_RATE_50Hz      0xC0
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_50Hz      0x00
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_100Hz     0x08
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_200Hz     0x10
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_400Hz     0x18
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_12_5Hz    0x20
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_25Hz      0x28
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_800Hz     0x30
#define PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_1600Hz    0x38
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_0_781Hz  0x00
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_1_563Hz  0x01
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_3_125Hz  0x02
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_6_250Hz  0x03
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_12_5Hz   0x04
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_25Hz     0x05
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_50Hz     0x06
#define PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_100Hz    0x07
/** \} */

/**
 * \defgroup ctrl4 Control register 4
 * \{
 */
#define PEDOMETER3_CNTL4_COUNTER_CLEAR_MODE            0x00
#define PEDOMETER3_CNTL4_COUNTER_DECREMENT_MODE        0x80
#define PEDOMETER3_CNTL4_THRESHOLD_MODE_ABSOLUTE       0x00
#define PEDOMETER3_CNTL4_THRESHOLD_MODE_RELATIVE       0x40
#define PEDOMETER3_CNTL4_WAKE_UP_DISABLE               0x00
#define PEDOMETER3_CNTL4_WAKE_UP_ENABLE                0x20
#define PEDOMETER3_CNTL4_BACK_TO_SLEEP_DISABLE         0x00
#define PEDOMETER3_CNTL4_BACK_TO_SLEEP_ENABLE          0x10
#define PEDOMETER3_CNTL4_HIGH_PASS_DISABLE             0x00
#define PEDOMETER3_CNTL4_HIGH_PASS_ENABLE              0x08
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_0_781Hz 0x00
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_1_563Hz 0x01
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_3_125Hz 0x02
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_6_250Hz 0x03
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_12_5Hz  0x04
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_25Hz    0x05
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_50Hz    0x06
#define PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_100Hz   0x07
/** \} */

/**
 * \defgroup ctrl5 Control register 5
 * \{
 */
#define PEDOMETER3_CNTL5_MANUAL_WAKE_UP_0  0x00
#define PEDOMETER3_CNTL5_MANUAL_WAKE_UP_1  0x02
#define PEDOMETER3_CNTL5_MANUAL_SLEEP_UP_0 0x00
#define PEDOMETER3_CNTL5_MANUAL_SLEEP_UP_1 0x01
/** \} */

/**
 * \defgroup out_ctrl Output data control
 * \{
 */
#define PEDOMETER3_ODCNTL_IR_BYPASS_FILTERING_APPLIED   0x00
#define PEDOMETER3_ODCNTL_IR_BYPASS_FILTER_BYPASSED     0x80
#define PEDOMETER3_ODCNTL_LPRO_ODR_9                    0x00
#define PEDOMETER3_ODCNTL_LPRO_ODR_2                    0x40
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_12_5Hz   0x00
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_25Hz     0x01
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_50Hz     0x02
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_100Hz    0x03
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_200Hz    0x04
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_400Hz    0x05
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_800Hz    0x06
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_1600Hz   0x07
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_0_781Hz  0x08
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_1_563Hz  0x09
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_3_125Hz  0x0A
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_6_25Hz   0x0B
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_3200Hz   0x0C
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_6400Hz   0x0D
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_12800Hz  0x0E
#define PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_25600Hz  0x0F
/** \} */

/**
 * \defgroup in_crtl_1 Interrupt Control 1
 * \{
 */
#define PEDOMETER3_INC1_PULSE_INTERRUPT_1_50uSec      0x00
#define PEDOMETER3_INC1_PULSE_INTERRUPT_1_OSA_PERIOD  0x40
#define PEDOMETER3_INC1_PULSE_INTERRUPT_1_OSA2_PERIOD 0x80
#define PEDOMETER3_INC1_PULSE_INTERRUPT_1_OSA4_PERIOD 0xC0
#define PEDOMETER3_INC1_PHYSICAL_INTERRUPT_DISABLE    0x00
#define PEDOMETER3_INC1_PHYSICAL_INTERRUPT_ENABLE     0x20
#define PEDOMETER3_INC1_INTERRUPT_ACTIVE_LEVEL_LOW    0x00
#define PEDOMETER3_INC1_INTERRUPT_ACTIVE_LEVEL_HIGH   0x10
#define PEDOMETER3_INC1_INTERRUPT_LATCHED             0x00
#define PEDOMETER3_INC1_INTERRUPT_PULSED              0x08
#define PEDOMETER3_INC1_SELF_TEST_POLARITY_NEGATIVE   0x00
#define PEDOMETER3_INC1_SELF_TEST_POLARITY_POSITIVE   0x02
#define PEDOMETER3_INC1_3_WIRE_SPI_INTERFACE_DISABLE  0x00
#define PEDOMETER3_INC1_3_WIRE_SPI_INTERFACE_ENABLED  0x01
/** \} */

/**
 * \defgroup in_crtl_2 Interrupt Control 2
 * \{
 */
#define PEDOMETER3_INC2_AOI_ACTIVE_STATE_IN_OR   0x00
#define PEDOMETER3_INC2_AOI_ACTIVE_STATE_IN_AND  0x40
#define PEDOMETER3_INC2_X_NEGATIVE_DISABLE       0x00
#define PEDOMETER3_INC2_X_NEGATIVE_ENABEL        0x20
#define PEDOMETER3_INC2_Y_NEGATIVE_DISABLE       0x00
#define PEDOMETER3_INC2_Y_NEGATIVE_ENABEL        0x08
#define PEDOMETER3_INC2_Z_NEGATIVE_DISABLE       0x00
#define PEDOMETER3_INC2_Z_NEGATIVE_ENABEL        0x02
#define PEDOMETER3_INC2_X_POSITIVE_DISABLE       0x00
#define PEDOMETER3_INC2_X_POSITIVE_ENABEL        0x10
#define PEDOMETER3_INC2_Y_POSITIVE_DISABLE       0x00
#define PEDOMETER3_INC2_Y_POSITIVE_ENABEL        0x04
#define PEDOMETER3_INC2_Z_POSITIVE_DISABLE       0x00
#define PEDOMETER3_INC2_Z_POSITIVE_ENABEL        0x01
/** \} */

/**
 * \defgroup in_crtl_3 Interrupt Control 3
 * \{
 */
#define PEDOMETER3_INC3_ALTERNATE_TAP_DISABLE    0x00
#define PEDOMETER3_INC3_ALTERNATE_TAP_ENABLE     0x40
#define PEDOMETER3_INC3_LEFT_STATE_DISABLE       0x00
#define PEDOMETER3_INC3_LEFT_STATE_ENABLE        0x20
#define PEDOMETER3_INC3_RIGHT_STATE_DISABLE      0x00
#define PEDOMETER3_INC3_RIGHT_STATE_ENABLE       0x10
#define PEDOMETER3_INC3_DOWN_STATE_DISABLE       0x00
#define PEDOMETER3_INC3_DOWN_STATE_ENABLE        0x08
#define PEDOMETER3_INC3_UP_STATE_DISABLE         0x00
#define PEDOMETER3_INC3_UP_STATE_ENABLE          0x04
#define PEDOMETER3_INC3_FACE_DOWN_STATE_DISABLE  0x00
#define PEDOMETER3_INC3_FACE_DOWN_STATE_ENABLE   0x02
#define PEDOMETER3_INC3_FACE_UP_STATE_DISABLE    0x00
#define PEDOMETER3_INC3_FACE_UP_STATE_ENABLE     0x01
/** \} */

/**
 * \defgroup in_crtl_4 Interrupt Control 4
 * \{
 */
#define PEDOMETER3_INC4_FREE_FALL_INTERRUPT_1_DISABLE      0x00
#define PEDOMETER3_INC4_FREE_FALL_INTERRUPT_1_ENABLE       0x80
#define PEDOMETER3_INC4_BUFFER_FULL_INTERRUPT_1_DISABLE    0x00
#define PEDOMETER3_INC4_BUFFER_FULL_INTERRUPT_1_ENABLE     0x40
#define PEDOMETER3_INC4_WATERMARK_INTERRUPT_1_DISABLE      0x00
#define PEDOMETER3_INC4_WATERMARK_INTERRUPT_1_ENABLE       0x20
#define PEDOMETER3_INC4_DATA_READY_INTERRUPT_1_DISABLE     0x00
#define PEDOMETER3_INC4_DATA_READY_INTERRUPT_1_ENABLE      0x10
#define PEDOMETER3_INC4_BACK_TO_SLEEP_INTERRUPT_1_DISABLE  0x00
#define PEDOMETER3_INC4_BACK_TO_SLEEP_INTERRUPT_1_ENABLE   0x08
#define PEDOMETER3_INC4_TAP_INTERRUPT_1_DISABLE            0x00
#define PEDOMETER3_INC4_TAP_INTERRUPT_1_ENABLE             0x04
#define PEDOMETER3_INC4_WAKE_UP_INTERRUPT_1_DISABLE        0x00
#define PEDOMETER3_INC4_WAKE_UP_INTERRUPT_1_ENABLE         0x02
#define PEDOMETER3_INC4_TILT_POSITION_INTERRUPT_1_DISABLE  0x00
#define PEDOMETER3_INC4_TILT_POSITION_INTERRUPT_1_ENABLE   0x01
/** \} */

/**
 * \defgroup in_crtl_5 Interrupt Control 5
 * \{
 */
#define PEDOMETER3_INC5_PULSE_INTERRUPT_2_50uSec       0x00
#define PEDOMETER3_INC5_PULSE_INTERRUPT_2_OSA_PERIOD   0x40
#define PEDOMETER3_INC5_PULSE_INTERRUPT_2_OSA2_PERIOD  0x80
#define PEDOMETER3_INC5_PULSE_INTERRUPT_2_OSA4_PERIOD  0xC0
#define PEDOMETER3_INC5_PHYSICAL_INTERRUPT_DISABLE     0x00
#define PEDOMETER3_INC5_PHYSICAL_INTERRUPT_ENABLE      0x20
#define PEDOMETER3_INC5_INTERRUPT_ACTIVE_LEVEL_LOW     0x00
#define PEDOMETER3_INC5_INTERRUPT_ACTIVE_LEVEL_HIGH    0x10
#define PEDOMETER3_INC5_INTERRUPT_LATCHED              0x00
#define PEDOMETER3_INC5_INTERRUPT_PULSED               0x08
#define PEDOMETER3_INC5_LATCHED_INTERRUPT_2_DISABLE    0x00
#define PEDOMETER3_INC5_LATCHED_INTERRUPT_2_ENABLE     0x02
#define PEDOMETER3_INC5_LATCHED_INTERRUPT_1_DISABLE    0x00
#define PEDOMETER3_INC5_LATCHED_INTERRUPT_1_ENABLE     0x01
/** \} */

/**
 * \defgroup in_crtl_6 Interrupt Control 6
 * \{
 */
#define PEDOMETER3_INC6_FREE_FALL_INTERRUPT_2_DISABLE     0x00
#define PEDOMETER3_INC6_FREE_FALL_INTERRUPT_2_ENABLE      0x80
#define PEDOMETER3_INC6_BUFFER_FULL_INTERRUPT_2_DISABLE   0x00
#define PEDOMETER3_INC6_BUFFER_FULL_INTERRUPT_2_ENABLE    0x40
#define PEDOMETER3_INC6_WATERMARK_INTERRUPT_2_DISABLE     0x00
#define PEDOMETER3_INC6_WATERMARK_INTERRUPT_2_ENABLE      0x20
#define PEDOMETER3_INC6_DATA_READY_INTERRUPT_2_DISABLE    0x00
#define PEDOMETER3_INC6_DATA_READY_INTERRUPT_2_ENABLE     0x10
#define PEDOMETER3_INC6_BACK_TO_SLEEP_INTERRUPT_2_DISABLE 0x00
#define PEDOMETER3_INC6_BACK_TO_SLEEP_INTERRUPT_2_ENABLE  0x08
#define PEDOMETER3_INC6_TAP_INTERRUPT_2_DISABLE           0x00
#define PEDOMETER3_INC6_TAP_INTERRUPT_2_ENABLE            0x04
#define PEDOMETER3_INC6_WAKE_UP_INTERRUPT_2_DISABLE       0x00
#define PEDOMETER3_INC6_WAKE_UP_INTERRUPT_2_ENABLE        0x02
#define PEDOMETER3_INC6_TILT_POSITION_INTERRUPT_2_DISABLE 0x00
#define PEDOMETER3_INC6_TILT_POSITION_INTERRUPT_2_ENABLE  0x01
/** \} */

/**
 * \defgroup in_crtl_7 Interrupt Control 7
 * \{
 */
#define PEDOMETER3_INC7_STEP_OVERFLOW_INTERRUPT_2_DISABLE   0x00
#define PEDOMETER3_INC7_STEP_OVERFLOW_INTERRUPT_2_ENABLE    0x40
#define PEDOMETER3_INC7_STEP_WATERMARK_INTERRUPT_2_DISABLE  0x00
#define PEDOMETER3_INC7_STEP_WATERMARK_INTERRUPT_2_ENABLE   0x20
#define PEDOMETER3_INC7_STEP_INCREMENT_INTERRUPT_2_DISABLE  0x00
#define PEDOMETER3_INC7_STEP_INCREMENT_INTERRUPT_2_ENABLE   0x10
#define PEDOMETER3_INC7_STEP_OVERFLOW_INTERRUPT_1_DISABLE   0x00
#define PEDOMETER3_INC7_STEP_OVERFLOW_INTERRUPT_1_ENABLE    0x04
#define PEDOMETER3_INC7_STEP_WATERMARK_INTERRUPT_1_DISABLE  0x00
#define PEDOMETER3_INC7_STEP_WATERMARK_INTERRUPT_1_ENABLE   0x02
#define PEDOMETER3_INC7_STEP_INCREMENT_INTERRUPT_1_DISABLE  0x00
#define PEDOMETER3_INC7_STEP_INCREMENT_INTERRUPT_1_ENABLE   0x01
/** \} */

/**
 * \defgroup tap_ctrl Tap Report Control
 * \{
 */
#define PEDOMETER3_TDTRC_DOUBLE_TAP_INTERRUPT_DISABLE  0x00
#define PEDOMETER3_TDTRC_DOUBLE_TAP_INTERRUPT_ENABLE   0x02
#define PEDOMETER3_TDTRC_SINGLE_TAP_INTERRUPT_DISABLE  0x00
#define PEDOMETER3_TDTRC_SINGLE_TAP_INTERRUPT_ENABLE   0x01
/** \} */

/**
 * \defgroup free_fall_ctrl Free Fall Control
 * \{
 */
#define PEDOMETER3_FFCNTL_FREE_FALL_DISABLE                   0x00
#define PEDOMETER3_FFCNTL_FREE_FALL_ENABLE                    0x80
#define PEDOMETER3_FFCNTL_FREE_FALL_INTERRUPT_LATCH_DISABLE   0x00
#define PEDOMETER3_FFCNTL_FREE_FALL_INTERRUPT_UNLATCH_ENABLE  0x40
#define PEDOMETER3_FFCNTL_DEBOUNCE_METHODOLOGY_DISABLE        0x00
#define PEDOMETER3_FFCNTL_DEBOUNCE_METHODOLOGY_ENABLE         0x08
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_12_5Hz        0x00
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_25Hz          0x01
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_50Hz          0x02
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_100Hz         0x03
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_200Hz         0x04
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_400Hz         0x05
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_800Hz         0x06
#define PEDOMETER3_FFCNTL_OFFI_OUTPUT_DATA_RATE_1600Hz        0x07
/** \} */

/**
 * \defgroup low_power_ctrl Low Power Control
 * \{
 */
#define PEDOMETER3_LP_CNTL_NO_AVERAGING         0x00
#define PEDOMETER3_LP_CNTL_2_SAMPLES_AVERAGED   0x10
#define PEDOMETER3_LP_CNTL_4_SAMPLES_AVERAGED   0x20
#define PEDOMETER3_LP_CNTL_8_SAMPLES_AVERAGED   0x30
#define PEDOMETER3_LP_CNTL_16_SAMPLES_AVERAGED  0x40
#define PEDOMETER3_LP_CNTL_32_SAMPLES_AVERAGED  0x50
#define PEDOMETER3_LP_CNTL_64_SAMPLES_AVERAGED  0x60
#define PEDOMETER3_LP_CNTL_128_SAMPLES_AVERAGED 0x70
/** \} */

/**
 * \defgroup ped_ctrl_1 Pedometer Control register 1
 * \{
 */
#define PEDOMETER3_PED_CNTL1_STEP_TH_NO_STEPS  0x00
#define PEDOMETER3_PED_CNTL1_STEP_TH_2_STEPS   0x01
#define PEDOMETER3_PED_CNTL1_STEP_TH_4_STEPS   0x02
#define PEDOMETER3_PED_CNTL1_STEP_TH_6_STEPS   0x03
#define PEDOMETER3_PED_CNTL1_STEP_TH_8_STEPS   0x04
#define PEDOMETER3_PED_CNTL1_STEP_TH_10_STEPS  0x05
#define PEDOMETER3_PED_CNTL1_STEP_TH_12_STEPS  0x06
#define PEDOMETER3_PED_CNTL1_STEP_TH_14_STEPS  0x07
/** \} */

/**
 * \defgroup ped_ctrl_2 Pedometer Control register 2
 * \{
 */
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_1   0x00
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_2   0x10
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_4   0x20
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_8   0x30
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_16  0x40
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_32  0x50
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_64  0x60
#define PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_128 0x70
#define PEDOMETER3_PED_CNTL2_ODR_SELECT_100Hz     0x0C
#define PEDOMETER3_PED_CNTL2_ODR_SELECT_50Hz      0x06
/** \} */

/**
 * \defgroup device_slave_addr Device slave address
 * \{
 */
#define PEDOMETER3_SLAVE_ADDRESS_0 0x1E
#define PEDOMETER3_SLAVE_ADDRESS_1 0x1F
/** \} */

/**
 * \defgroup tilt_pos Current/Previous Tilt Position
 * \{
 */
#define PEDOMETER3_TILT_POSITION_LEFT       1
#define PEDOMETER3_TILT_POSITION_RIGHT      2
#define PEDOMETER3_TILT_POSITION_DOWN       3
#define PEDOMETER3_TILT_POSITION_UP         4
#define PEDOMETER3_TILT_POSITION_FACE_DOWN  5
#define PEDOMETER3_TILT_POSITION_FACE_UP    6
/** \} */

/**
 * \defgroup tap_detection Tap detection
 * \{
 */
#define PEDOMETER3_TAP_X_NEGATIVE  0x10
#define PEDOMETER3_TAP_X_POSITIVE  0x11
#define PEDOMETER3_TAP_Y_NEGATIVE  0x20
#define PEDOMETER3_TAP_Y_POSITIVE  0x21
#define PEDOMETER3_TAP_Z_NEGATIVE  0x30
#define PEDOMETER3_TAP_Z_POSITIVE  0x31
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Comunication select type 
 */
typedef uint8_t  pedometer3_select_t;

/**
 * @brief Function pointer for master input/output type 
 */
typedef void ( *pedometer3_master_io_t )( struct pedometer3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition
 */
typedef struct pedometer3_s
{
   // Output pins 
   
    digital_out_t cs;

    // Input pins

    digital_in_t trg;
    digital_in_t it2;
    digital_in_t int_pin;

    // Modules

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable

    uint8_t slave_address;
    pin_name_t chip_select;
    pedometer3_master_io_t  write_f;
    pedometer3_master_io_t  read_f;
    pedometer3_select_t master_sel;

} pedometer3_t;

/**
 * @brief Click configuration structure definition
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins

     pin_name_t trg;
     pin_name_t it2;
     pin_name_t int_pin;

    // static variable

    uint32_t i2c_speed;
    uint8_t i2c_address;
    
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    pedometer3_select_t sel;

} pedometer3_cfg_t;

/**
 * @brief Axis structure
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

}pedometer3_axis_t;

/**
 * @brief Tilt position structure
 */
typedef struct
{
    uint8_t current_pos;
    uint8_t previous_pos;

}pedometer3_tilt_position_t;

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
void pedometer3_cfg_setup ( pedometer3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PEDOMETER3_RETVAL pedometer3_init ( pedometer3_t *ctx, pedometer3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pedometer3 click.
 * @note Functions and setups that are included in the device's start configuration
 * <pre>
 *   PEDOMETER3_REG_CONTROL_1
 * -------------------------------------------
 *   PEDOMETER3_CNTL1_MODE_STAND_BY
 *   PEDOMETER3_CNTL1_RES_MODE_HIGHER_NOISE
 *   PEDOMETER3_CNTL1_DATA_READY_DISABLE
 *   PEDOMETER3_CNTL1_G_RANGE_8g
 *   PEDOMETER3_CNTL1_PEDOMETER_DISABLE
 *   PEDOMETER3_CNTL1_TILT_DISABLE
 *   PEDOMETER3_CNTL1_TAP_DISABLE
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_CONTROL_2
 * -------------------------------------------
 *   PEDOMETER3_CNTL2_SOFTWARE_RESET_NO_ACTIVE
 *   PEDOMETER3_CNTL2_COMMAND_TEST_NO_ACTIVE
 *   PEDOMETER3_CNTL2_DOWN_STATE_ENABLE
 *   PEDOMETER3_CNTL2_FACE_DOWN_STATE_ENABLE
 *   PEDOMETER3_CNTL2_FACE_UP_STATE_ENABLE
 *   PEDOMETER3_CNTL2_LEFT_STATE_ENABLE
 *   PEDOMETER3_CNTL2_RIGHT_STATE_ENABLE
 *   PEDOMETER3_CNTL2_UP_STATE_ENABLE
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_CONTROL_3
 * -------------------------------------------
 *   PEDOMETER3_CNTL3_OTP_OUTPUT_DATA_RATE_12_5Hz
 *   PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_400Hz
 *   PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_0_781Hz
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_CONTROL_4
 * -------------------------------------------
 *   PEDOMETER3_CNTL4_COUNTER_DECREMENT_MODE
 *   PEDOMETER3_CNTL4_THRESHOLD_MODE_ABSOLUTE
 *   PEDOMETER3_CNTL4_WAKE_UP_DISABLE
 *   PEDOMETER3_CNTL4_BACK_TO_SLEEP_DISABLE
 *   PEDOMETER3_CNTL2_FACE_UP_STATE_ENABLE
 *   PEDOMETER3_CNTL4_HIGH_PASS_ENABLE
 *   PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_0_781Hz
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_CONTROL_5
 * -------------------------------------------
 *   PEDOMETER3_CNTL5_MANUAL_WAKE_UP_0
 *   PEDOMETER3_CNTL5_MANUAL_SLEEP_UP_0
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_OUTPUT_DATA_CONTROL
 * -------------------------------------------
 *   PEDOMETER3_ODCNTL_IR_BYPASS_FILTERING_APPLIED
 *   PEDOMETER3_ODCNTL_LPRO_ODR_9
 *   PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_50Hz
 *   PEDOMETER3_CNTL4_BACK_TO_SLEEP_DISABLE
 *   PEDOMETER3_CNTL2_FACE_UP_STATE_ENABLE
 *   PEDOMETER3_CNTL4_HIGH_PASS_ENABLE
 *   PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_0_781Hz
 * </pre>
 *
 * Set Pedometer Step Watermark on the 10 000 steps
 *
 * <pre>
 *   PEDOMETER3_REG_PEDOMETER_CONTROL_2
 * -------------------------------------------
 *   PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_4
 *   PEDOMETER3_PED_CNTL2_ODR_SELECT_100Hz
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_INTERRUPT_CONTROL_7
 * -------------------------------------------
 *   PEDOMETER3_INC7_STEP_OVERFLOW_INTERRUPT_2_ENABLE
 *   PEDOMETER3_INC7_STEP_WATERMARK_INTERRUPT_2_ENABLE
 *   PEDOMETER3_INC7_STEP_INCREMENT_INTERRUPT_1_ENABLE
 * </pre>
 *
 * <pre>
 *   PEDOMETER3_REG_INTERRUPT_CONTROL_1
 * -------------------------------------------
 *   PEDOMETER3_INC1_PHYSICAL_INTERRUPT_ENABLE
 *
 *   PEDOMETER3_REG_INTERRUPT_CONTROL_5
 * -------------------------------------------
 *   PEDOMETER3_INC5_PHYSICAL_INTERRUPT_ENABLE
 * </pre>
 * Start pedometer config on the ODR = 100Hz
 */
void pedometer3_default_cfg ( pedometer3_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Data buf to be written.
 * @param len        Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void pedometer3_generic_write ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void pedometer3_generic_read ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for read Accel axis data
 *
 * @param ctx        Click object.
 * @param axis       Accel axis structure.
 */
void pedometer3_get_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis );

/**
 * @brief Functions for read High Pass Accel axis data
 *
 * @param ctx        Click object.
 * @param axis       Accel axis structure.
 */
void pedometer3_get_highpass_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis );

/**
 * @brief Functions for sets pedometer step counter Watermark
 *
 * @param ctx        Click object.
 * @param value      Value for sets
 *
 * @note This function is used to set the 16-bit watermark threshold for step counting.
 */
void pedometer3_set_step_watermark ( pedometer3_t *ctx, uint16_t value );

/**
 * @brief Functions for pedometer configuration
 *
 * @param ctx        Click object.
 * @param odr        ODR frequency ( 100 Hz or 50 Hz)
 *
 * @note This function uses default pedometer control of registers for set ODR.
 *       Settings that are used for Set frequency see datasheet.
 */
void pedometer3_pedometer_cfg ( pedometer3_t *ctx, uint8_t odr );

/**
 * @brief Functions for get pedometer step counter
 *
 * @param ctx        Click object.
 * @return Number of detected steps in one period
 */
uint16_t pedometer3_get_step_counter ( pedometer3_t *ctx );

/**
 * @brief Functions for get Tilt current and previous position
 *
 * @param ctx        Click object.
 * @param tilt     Tilt structure
 *
 * @note
 * <pre>
 * return value | name position
 * -------------+------------------------------------
 * 1            | PEDOMETER3_TILT_POSITION_LEFT
 * 2            | PEDOMETER3_TILT_POSITION_RIGHT
 * 3            | PEDOMETER3_TILT_POSITION_DOWN
 * 4            | PEDOMETER3_TILT_POSITION_UP
 * 5            | PEDOMETER3_TILT_POSITION_FACE_DOWN
 * 6            | PEDOMETER3_TILT_POSITION_FACE_UP
 * </pre>
 */
void pedometer3_get_tilt_position ( pedometer3_t *ctx, pedometer3_tilt_position_t *tilt );

/**
 * @brief Functions for get Tap detection
 *
 * @param ctx        Click object.
 * @param tap        A tap that's detected
 *
 * @note
 * <pre>
 * return value  | name TAP
 * --------------+---------------------------
 * 10            | PEDOMETER3_TAP_X_NEGATIVE
 * 11            | PEDOMETER3_TAP_X_POSITIVE
 * 20            | PEDOMETER3_TAP_Y_NEGATIVE
 * 21            | PEDOMETER3_TAP_Y_POSITIVE
 * 30            | PEDOMETER3_TAP_Z_NEGATIVE
 * 31            | PEDOMETER3_TAP_Z_POSITIVE
 * </pre>
 */
uint8_t pedometer3_get_tap_detection ( pedometer3_t *ctx );

/**
 * @brief Functions for test first comunication width chip
 *
 * @param ctx        Click object.
 *
 * @return Did the device have communication with the MCU.
 * @retval 0 [PEDOMETER3_ERROR] - Device error, not read main iD
 * @retval 1 [PEDOMETER_OK] - Successfully read the main ID and the device is ready to work
 */
PEDOMETER3_RETVAL pedometer3_test_communication ( pedometer3_t *ctx );

/**
 * @brief Functions for read INT pin state
 *
 * @param ctx        Click object.
 * @retval Interrupt 1 state
 */
uint8_t pedometer3_get_interrupt_1 ( pedometer3_t *ctx );

/**
 * @brief Functions for read RST pin state
 *
 * @param ctx        Click object.
 * @retval Interrupt 2 state
 */
uint8_t pedometer3_get_interrupt_2 ( pedometer3_t *ctx );

/**
 * @brief Functions for read AN pin state
 *
 * @param ctx        Click object.
 * @retval Trigger interrupt state
 */
uint8_t pedometer3_get_trigger_interrupt ( pedometer3_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _PEDOMETER3_H_

/** \} */ // End varialbles group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

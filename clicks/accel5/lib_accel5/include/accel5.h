/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 * \brief This file contains API for Accel 5 Click driver.
 * \addtogroup accel5 Accel 5 Click Driver
 * \{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL5_H
#define ACCEL5_H

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
#define ACCEL5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_INT );

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL5_OK            0
#define ACCEL5_INIT_ERROR  (-1)
/** \} */

/**
 * \defgroup chip Chip
 * \{
 */
#define ACCEL5_CHIP_ID  0x90
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define ACCEL5_REG_CHIP_ID             0x00
#define ACCEL5_REG_ERR_REG             0x02
#define ACCEL5_REG_STATUS              0x03
#define ACCEL5_REG_ACC_X_LSB           0x04
#define ACCEL5_REG_ACC_X_MSB           0x05
#define ACCEL5_REG_ACC_Y_LSB           0x06
#define ACCEL5_REG_ACC_Y_MSB           0x07
#define ACCEL5_REG_ACC_Z_LSB           0x08
#define ACCEL5_REG_ACC_Z_MSB           0x09
#define ACCEL5_REG_SENSOR_TIME_0       0x0A
#define ACCEL5_REG_SENSOR_TIME_1       0x0B
#define ACCEL5_REG_SENSOR_TIME_2       0x0C
#define ACCEL5_REG_EVENT               0x0D
#define ACCEL5_REG_INT_STATUS_0        0x0E
#define ACCEL5_REG_INT_STATUS_1        0x0F
#define ACCEL5_REG_INT_STATUS_2        0x10
#define ACCEL5_REG_TEMPERATURE         0x11
#define ACCEL5_REG_FIFO_LENGTH_0       0x12
#define ACCEL5_REG_FIFO_LENGTH_1       0x13
#define ACCEL5_REG_FIFO_DATA           0x14
#define ACCEL5_REG_STEP_CNT_0          0x15
#define ACCEL5_REG_STEP_CNT_1          0x16
#define ACCEL5_REG_STEP_CNT_2          0x17
#define ACCEL5_REG_STEP_STATUS         0x18
#define ACCEL5_REG_ACC_CONGIG_0        0x19
#define ACCEL5_REG_ACC_CONGIG_1        0x1A
#define ACCEL5_REG_ACC_CONGIG_2        0x1B
#define ACCEL5_REG_INT_CONFIG_0        0x1F
#define ACCEL5_REG_INT_CONFIG_1        0x20
#define ACCEL5_REG_INT1_MAP            0x21
#define ACCEL5_REG_INT2_MAP            0x22
#define ACCEL5_REG_INT12_MAP           0x23
#define ACCEL5_REG_INT12_IO_CTRL       0x24
#define ACCEL5_REG_FIFO_CONFIG_0       0x26
#define ACCEL5_REG_FIFO_CONFIG_1       0x27
#define ACCEL5_REG_FIFO_CONFIG_2       0x28
#define ACCEL5_REG_FIFO_PWR_CONFIG     0x29
#define ACCEL5_REG_AUTO_LOW_POW_0      0x2A
#define ACCEL5_REG_AUTO_LOW_POW_1      0x2B
#define ACCEL5_REG_AUTO_WAKEUP_0       0x2C
#define ACCEL5_REG_AUTO_WAKEUP_1       0x2D
#define ACCEL5_REG_WAKEUP_CONFIG_0     0x2F
#define ACCEL5_REG_WAKEUP_CONFIG_1     0x30
#define ACCEL5_REG_WAKEUP_CONFIG_2     0x31
#define ACCEL5_REG_WAKEUP_CONFIG_3     0x32
#define ACCEL5_REG_WAKEUP_CONFIG_4     0x33
#define ACCEL5_REG_ORIENTCH_CONFIG_0   0x35
#define ACCEL5_REG_ORIENTCH_CONFIG_1   0x36
#define ACCEL5_REG_ORIENTCH_CONFIG_2   0x37
#define ACCEL5_REG_ORIENTCH_CONFIG_3   0x38
#define ACCEL5_REG_ORIENTCH_CONFIG_4   0x39
#define ACCEL5_REG_ORIENTCH_CONFIG_5   0x3A
#define ACCEL5_REG_ORIENTCH_CONFIG_6   0x3B
#define ACCEL5_REG_ORIENTCH_CONFIG_7   0x3C
#define ACCEL5_REG_ORIENTCH_CONFIG_8   0x3D
#define ACCEL5_REG_ORIENTCH_CONFIG_9   0x3E
#define ACCEL5_REG_GEN1_INT_CONFIG_0   0x3F
#define ACCEL5_REG_GEN1_INT_CONFIG_1   0x40
#define ACCEL5_REG_GEN1_INT_CONFIG_2   0x41
#define ACCEL5_REG_GEN1_INT_CONFIG_3   0x42
#define ACCEL5_REG_GEN1_INT_CONFIG_31  0x43
#define ACCEL5_REG_GEN1_INT_CONFIG_4   0x44
#define ACCEL5_REG_GEN1_INT_CONFIG_5   0x45
#define ACCEL5_REG_GEN1_INT_CONFIG_6   0x46
#define ACCEL5_REG_GEN1_INT_CONFIG_7   0x47
#define ACCEL5_REG_GEN1_INT_CONFIG_8   0x48
#define ACCEL5_REG_GEN1_INT_CONFIG_9   0x49
#define ACCEL5_REG_GEN2_INT_CONFIG_0   0x4A
#define ACCEL5_REG_GEN2_INT_CONFIG_1   0x4B
#define ACCEL5_REG_GEN2_INT_CONFIG_2   0x4C
#define ACCEL5_REG_GEN2_INT_CONFIG_3   0x4D
#define ACCEL5_REG_GEN2_INT_CONFIG_31  0x4E
#define ACCEL5_REG_GEN2_INT_CONFIG_4   0x4F
#define ACCEL5_REG_GEN2_INT_CONFIG_5   0x50
#define ACCEL5_REG_GEN2_INT_CONFIG_6   0x51
#define ACCEL5_REG_GEN2_INT_CONFIG_7   0x52
#define ACCEL5_REG_GEN2_INT_CONFIG_8   0x53
#define ACCEL5_REG_GEN2_INT_CONFIG_9   0x54
#define ACCEL5_REG_ACTCH_CONFIG_0      0x55
#define ACCEL5_REG_ACTCH_CONFIG_1      0x56
#define ACCEL5_REG_TAP_CONFIG_0        0x57
#define ACCEL5_REG_TAP_CONFIG_1        0x58
#define ACCEL5_REG_STEP_CNT_CONFIG_0   0x59
#define ACCEL5_REG_STEP_CNT_CONFIG_1   0x5A
#define ACCEL5_REG_STEP_CNT_CONFIG_2   0x5B
#define ACCEL5_REG_STEP_CNT_CONFIG_3   0x5C
#define ACCEL5_REG_STEP_CNT_CONFIG_4   0x5D
#define ACCEL5_REG_STEP_CNT_CONFIG_5   0x5E
#define ACCEL5_REG_STEP_CNT_CONFIG_6   0x5F
#define ACCEL5_REG_STEP_CNT_CONFIG_7   0x60
#define ACCEL5_REG_STEP_CNT_CONFIG_8   0x61
#define ACCEL5_REG_STEP_CNT_CONFIG_9   0x62
#define ACCEL5_REG_STEP_CNT_CONFIG_10  0x63
#define ACCEL5_REG_STEP_CNT_CONFIG_11  0x64
#define ACCEL5_REG_STEP_CNT_CONFIG_12  0x65
#define ACCEL5_REG_STEP_CNT_CONFIG_13  0x66
#define ACCEL5_REG_STEP_CNT_CONFIG_14  0x67
#define ACCEL5_REG_STEP_CNT_CONFIG_15  0x68
#define ACCEL5_REG_STEP_CNT_CONFIG_16  0x69
#define ACCEL5_REG_STEP_CNT_CONFIG_17  0x6A
#define ACCEL5_REG_STEP_CNT_CONFIG_18  0x6B
#define ACCEL5_REG_STEP_CNT_CONFIG_19  0x6C
#define ACCEL5_REG_STEP_CNT_CONFIG_20  0x6D
#define ACCEL5_REG_STEP_CNT_CONFIG_21  0x6E
#define ACCEL5_REG_STEP_CNT_CONFIG_22  0x6F
#define ACCEL5_REG_STEP_CNT_CONFIG_23  0x70
#define ACCEL5_REG_STEP_CNT_CONFIG_24  0x71
#define ACCEL5_REG_IF_CONFIG           0x7C
#define ACCEL5_REG_SELF_TEST           0x7D
#define ACCEL5_REG_CMD                 0x7E
/** \} */

/**
 * \defgroup error_status_register Error Status Register
 * \{
 */
#define ACCEL5_ERROR_CMD               0x02
/** \} */

/**
 * \defgroup status_register Status Register
 * \{
 */
#define  ACCEL5_STATUS_DATA_RDY_START            0x80
#define  ACCEL5_STATUS_RDY_CMD                   0x10
#define  ACCEL5_STATUS_NORMAL_MODE               0x04
#define  ACCEL5_STATUS_LOW_POWER_MODE            0x02
#define  ACCEL5_STATUS_SLEEP_MODE                0x04
#define  ACCEL5_STATUS_INT_ACTIVE_TRIGGERED      0x01
#define  ACCEL5_STATUS_INT_ACTIVE_NOT_TRIGGERED  0x00
/** \} */

/**
 * \defgroup sensor_status_flags_event  Sensor Status Flags Event
 * \{
 */
#define ACCEL5_EVENT_POR_DETECTED       0x01
/** \} */

/**
 * \defgroup interrupt_status_0   Interrupt Status 0
 * \{
 */
#define ACCEL5_INT_STATUS_0_DATA_RDY_STATUS       0x80
#define ACCEL5_INT_STATUS_0_FIFO_WATERMARK        0x40
#define ACCEL5_INT_STATUS_0_FIFO_FULL             0x20
#define ACCEL5_INT_STATUS_0_IENG_OVERRUN_STATUS   0x10
#define ACCEL5_INT_STATUS_0_GEN2_INT_STATUS       0x08
#define ACCEL5_INT_STATUS_0_GEN1_INT_STATUS       0x04
#define ACCEL5_INT_STATUS_0_ORIENTCH_INT_STATUS   0x02
#define ACCEL5_INT_STATUS_0_WAKEUP_INT_STATUS     0x01
/** \} */

/**
 * \defgroup interrupt_status_1   Interrupt Status 1
 * \{
 */
#define ACCEL5_INT_STATUS_1_IENG_OVERRUN_STATUS   0x10
#define ACCEL5_INT_STATUS_1_DOUBLE_TAP            0x08
#define ACCEL5_INT_STATUS_1_SINGLE_TAP            0x04
#define ACCEL5_INT_STATUS_1_STEP_NO_SET           0x00
#define ACCEL5_INT_STATUS_1_STEP_SET              0x01
#define ACCEL5_INT_STATUS_1_STEP_DETECT           0x02
#define ACCEL5_INT_STATUS_1_STEP_NO_USED          0x03
/** \} */

/**
 * \defgroup interrupt_status_2   Interrupt Status 2
 * \{
 */
#define ACCEL5_INT_STATUS_2_IENG_OVERRUN_STATUS   0x10
#define ACCEL5_INT_STATUS_2_ACTCH_Z_INIT_STATUS   0x04
#define ACCEL5_INT_STATUS_2_ACTCH_Y_INIT_STATUS   0x02
#define ACCEL5_INT_STATUS_2_ACTCH_X_INIT_STATUS   0x01
/** \} */

/**
 * \defgroup step_status  Step Status
 * \{
 */
#define ACCEL5_STEP_STATUS_WALKING                0x01
#define ACCEL5_STEP_STATUS_RUNNING                0x02
#define ACCEL5_STEP_STATUS_NO_WALK_RUN            0x00
/** \} */

/**
 * \defgroup accel_config_0   Accel Config 0
 * \{
 */
#define ACCEL5_CFG_0_FILT1_BW_LOW_0_2X_ODR        0x80
#define ACCEL5_CFG_0_FILT1_BW_HIGH_0_4X_ODR       0x00
#define ACCEL5_CFG_0_SLEEP_MODE                   0x00
#define ACCEL5_CFG_0_LOW_POWER_MODE               0x01
#define ACCEL5_CFG_0_NORMAL_MODE                  0x02
/** \} */

/**
 * \defgroup accel_config_1   Accel Config 1
 * \{
 */
#define ACCEL5_CFG_1_ACC_RANGE_2g                 0x00
#define ACCEL5_CFG_1_ACC_RANGE_4g                 0x40
#define ACCEL5_CFG_1_ACC_RANGE_8g                 0x80
#define ACCEL5_CFG_1_ACC_RANGE_16g                0xC0
#define ACCEL5_CFG_1_OSR_LOW_POWER                0x00
#define ACCEL5_CFG_1_OSR_HIGH_POWER               0x30
#define ACCEL5_CFG_1_ODR_12p5_5                   0x00
#define ACCEL5_CFG_1_ODR_12p5_4                   0x01
#define ACCEL5_CFG_1_ODR_12p5_3                   0x02
#define ACCEL5_CFG_1_ODR_12p5_2                   0x03
#define ACCEL5_CFG_1_ODR_12p5_1                   0x04
#define ACCEL5_CFG_1_ODR_12p5                     0x05
#define ACCEL5_CFG_1_ODR_25                       0x06
#define ACCEL5_CFG_1_ODR_50                       0x07
#define ACCEL5_CFG_1_ODR_100                      0x08
#define ACCEL5_CFG_1_ODR_200                      0x09
#define ACCEL5_CFG_1_ODR_400                      0x0A
#define ACCEL5_CFG_1_ODR_800                      0x0B
#define ACCEL5_CFG_1_ODR_800_1                    0x0C
#define ACCEL5_CFG_1_ODR_800_2                    0x0D
#define ACCEL5_CFG_1_ODR_800_3                    0x0E
#define ACCEL5_CFG_1_ODR_800_4                    0x0F
/** \} */

/**
 * \defgroup accel_config_2   Accel Config 2
 * \{
 */
#define ACCEL5_CFG_2_DATA_SCR_ACC_FILT_1          0x00
#define ACCEL5_CFG_2_DATA_SCR_ACC_FILT_2          0x04
#define ACCEL5_CFG_2_DATA_SCR_ACC_FILT_LP         0x08
/** \} */

/**
 * \defgroup interrupt_config_0   Interrupt Config 0
 * \{
 */
#define ACCEL5_INT_CFG_0_DATA_RDY                 0x80
#define ACCEL5_INT_CFG_0_FIFO_WATERMARK           0x40
#define ACCEL5_INT_CFG_0_FIFO_FULL                0x20
#define ACCEL5_INT_CFG_0_GEN2_INT_STATUS          0x08
#define ACCEL5_INT_CFG_0_GEN1_INT_STATUS          0x04
#define ACCEL5_INT_CFG_0_ORIENTCH_INT             0x02
/** \} */

/**
 * \defgroup interrupt_config_1   Interrupt Config 1
 * \{
 */
#define ACCEL5_INT_CFG_1_LATCH_MODE_NOLATCH    0x00
#define ACCEL5_INT_CFG_1_LATCH_MODE_LATCHING   0x80
#define ACCEL5_INT_CFG_1_ACTCH_INT_ENABLE      0x10
#define ACCEL5_INT_CFG_1_DOUBLE_TAP_ENABLE     0x08
#define ACCEL5_INT_CFG_1_SINGLE_TAP_ENABLE     0x04
#define ACCEL5_INT_CFG_1_STEP_INT_ENABLE       0x01
/** \} */

/**
 * \defgroup interrupt_map_1  Interrupt Map 1
 * \{
 */
#define ACCEL5_INT1_MAP_DATA_RDY_STATUS        0x80
#define ACCEL5_INT1_MAP_FIFO_WATERMARK         0x40
#define ACCEL5_INT1_MAP_FIFO_FULL              0x20
#define ACCEL5_INT1_MAP_IENG_OVERRUN_STATUS    0x10
#define ACCEL5_INT1_MAP_GEN2_INT_STATUS        0x08
#define ACCEL5_INT1_MAP_GEN1_INT_STATUS        0x04
#define ACCEL5_INT1_MAP_ORIENTCH_INT_STATUS    0x02
#define ACCEL5_INT1_MAP_WAKEUP_INT_STATUS      0x01
/** \} */

/**
 * \defgroup interrupt_map_2  Interrupt Map 2
 * \{
 */
#define ACCEL5_INT2_MAP_DATA_RDY_STATUS        0x80
#define ACCEL5_INT2_MAP_FIFO_WATERMARK         0x40
#define ACCEL5_INT2_MAP_FIFO_FULL              0x20
#define ACCEL5_INT2_MAP_IENG_OVERRUN_STATUS    0x10
#define ACCEL5_INT2_MAP_GEN2_INT_STATUS        0x08
#define ACCEL5_INT2_MAP_GEN1_INT_STATUS        0x04
#define ACCEL5_INT2_MAP_ORIENTCH_INT_STATUS    0x02
#define ACCEL5_INT2_MAP_WAKEUP_INT_STATUS      0x01
/** \} */

/**
 * \defgroup interrupt_map_1_2  Interrupt Map_1_2
 * \{
 */
#define ACCEL5_INT12_MAP_ACTCH_INT2   0x80
#define ACCEL5_INT12_MAP_TAP_INT2     0x40
#define ACCEL5_INT12_MAP_STEP_INT2    0x10
#define ACCEL5_INT12_MAP_ACTCH_INT1   0x08
#define ACCEL5_INT12_MAP_TAP_INT1     0x04
#define ACCEL5_INT12_MAP_STEP_INT1    0x01
/** \} */

/**
 * \defgroup interrupt_io_ctrl_1_2 Interrupt Io Ctrl 1 2
 * \{
 */
#define ACCEL5_INT12_CTRL_INT2_OPEN_DRAIN     0x40
#define ACCEL5_INT12_CTRL_INT1_OPEN_DRAIN     0x04
#define ACCEL5_INT12_CTRL_INT2_HIGH_ACTIVE    0x20
#define ACCEL5_INT12_CTRL_INT1_HIGH_ACTIVE    0x02
/** \} */

/**
 * \defgroup fifo_config_0    Fifo Config 0
 * \{
 */
#define ACCEL5_FIFO_CFG0_Z_AXIS_ENABLE        0x80
#define ACCEL5_FIFO_CFG0_Y_AXIS_ENABLE        0x40
#define ACCEL5_FIFO_CFG0_X_AXIS_ENABLE        0x20
#define ACCEL5_FIFO_CFG0_8bit_ENABLE          0x10
#define ACCEL5_FIFO_CFG0_DATA_SRC_ENABLE      0x08
#define ACCEL5_FIFO_CFG0_TIME_ENABLE          0x04
#define ACCEL5_FIFO_CFG0_STOP_NO_FULL_ENABLE  0x02
#define ACCEL5_FIFO_CFG0_AUTO_FLUSH_ENABLE    0x01
/** \} */

/**
 * \defgroup auto_low_pow_1_register  Auto Low Pow 1 Register
 * \{
 */
#define ACCEL5_FIFO_AUTO_IP_TIMEOUT_0         0x00
#define ACCEL5_FIFO_AUTO_IP_TIMEOUT_1         0x04
#define ACCEL5_FIFO_AUTO_IP_TIMEOUT_2         0x08
#define ACCEL5_FIFO_AUTO_IP_TIMEOUT_3         0x0C
#define ACCEL5_FIFO_AUTO_TRIG_GEN1_INT        0x02
#define ACCEL5_FIFO_AUTO_TRIG_DATA_RDY        0x01
/** \} */

/**
 * \defgroup auto_wakeup   Auto Wakeup
 * \{
 */
#define ACCEL5_WAKEUP_TIMEOUT_ENABLE          0x04
#define ACCEL5_WAKEUP_ENABLE                  0x02
/** \} */

/**
 * \defgroup wakeup_config_o    Wakeup Config 0
 * \{
 */
#define ACCEL5_WAKEUP_Z_AXIS_ENABLE           0x80
#define ACCEL5_WAKEUP_Y_AXIS_ENABLE           0x40
#define ACCEL5_WAKEUP_X_AXIS_ENABLE           0x20
#define ACCEL5_WAKEUP_NUMBER_OF_SIMPLE        0x10
#define ACCEL5_WAKEUP_REFU_MANUAL             0x00
#define ACCEL5_WAKEUP_REFU_ONETIME            0x01
#define ACCEL5_WAKEUP_REFU_EVERYTIME          0x02
/** \} */

/**
 * \defgroup orient_config_0    Orient config 0
 * \{
 */
#define ACCEL5_ORIENT_Z_AXIS_ENABLE           0x80
#define ACCEL5_ORIENT_Y_AXIS_ENABLE           0x40
#define ACCEL5_ORIENT_X_AXIS_ENABLE           0x20
#define ACCEL5_ORIENT_DATA_SRC_ENABLE         0x10
#define ACCEL5_ORIENT_REFU_MANUAL             0x00
#define ACCEL5_ORIENT_REFU_ONETIME_2          0x04
#define ACCEL5_ORIENT_REFU_ONETIME_IP         0x08
#define ACCEL5_ORIENT_STABILITY_INACTIVE      0x00
#define ACCEL5_ORIENT_STABILITY_ENABLED_1     0x01
#define ACCEL5_ORIENT_STABILITY_ENABLED_2     0x02
/** \} */

/**
 * \defgroup generic_interrupt_1_config_0   Generic Interrupt 1 Config 0
 * \{
 */
#define ACCEL5_GEN1_CFG0_ACT_Z_ENABLE         0x80
#define ACCEL5_GEN1_CFG0_ACT_Y_ENABLE         0x40
#define ACCEL5_GEN1_CFG0_ACT_X_ENABLE         0x20
#define ACCEL5_GEN1_CFG0_DATA_ENABLE          0x10
#define ACCEL5_GEN1_CFG0_REFU_MANUAL          0x00
#define ACCEL5_GEN1_CFG0_REFU_ONETIME         0x04
#define ACCEL5_GEN1_CFG0_REFU_EVERYTIME       0x08
#define ACCEL5_GEN1_CFG0_HYST_24mg            0x01
#define ACCEL5_GEN1_CFG0_HYST_48mg            0x02
#define ACCEL5_GEN1_CFG0_HYST_96mg            0x03
#define ACCEL5_GEN1_CFG0_HYST_NO_ACTIVE       0x00
/** \} */

/**
 * \defgroup generic_interrupt_1_config_1   Generic Interrupt 1 Config 1
 * \{
 */
#define ACCEL5_GEN1_CFG1_CRITERION_SEL_ACTIVE      0x20
#define ACCEL5_GEN1_CFG1_CRITERION_SEL_INACTIVE    0x00
#define ACCEL5_GEN1_CFG1_COMB_SEL_AND              0x10
#define ACCEL5_GEN1_CFG1_COMB_SEL_OR               0x00 
/** \} */

/**
 * \defgroup generic_interrupt_2_consfig_1   Generic Interrupt 2 Consfig 1
 * \{
 */
#define ACCEL5_GEN2_CFG0_ACT_Z_ENABLE              0x80
#define ACCEL5_GEN2_CFG0_ACT_Y_ENABLE              0x40
#define ACCEL5_GEN2_CFG0_ACT_X_ENABLE              0x20
#define ACCEL5_GEN2_CFG0_DATA_ENABLE               0x10
#define ACCEL5_GEN2_CFG0_REFU_MANUAL               0x00
#define ACCEL5_GEN2_CFG0_REFU_ONETIME              0x04
#define ACCEL5_GEN2_CFG0_REFU_EVERYTIME            0x08
#define ACCEL5_GEN2_CFG0_HYST_24mg                 0x01
#define ACCEL5_GEN2_CFG0_HYST_48mg                 0x02
#define ACCEL5_GEN2_CFG0_HYST_96mg                 0x03
#define ACCEL5_GEN2_CFG0_HYST_NO_ACTIVE            0x00
/** \} */

/**
 * \defgroup generic_interrupt_2_config_1   Generic Interrupt 2 Config 1
 * \{
 */
#define ACCEL5_GEN2_CFG1_CRITERION_SEL_ACTIVE      0x20
#define ACCEL5_GEN2_CFG1_CRITERION_SEL_INACTIVE    0x00
#define ACCEL5_GEN2_CFG1_COMB_SEL_AND              0x10
#define ACCEL5_GEN2_CFG1_COMB_SEL_OR               0x00
/** \} */

/**
 * \defgroup activity_interrupt_config    Activity Interrupt config
 * \{
 */
#define ACCEL5_ACTCH_CFG0_Z_AXIS_ENABLE            0x80
#define ACCEL5_ACTCH_CFG0_Y_AXIS_ENABLE            0x40
#define ACCEL5_ACTCH_CFG0_X_AXIS_ENABLE            0x20
#define ACCEL5_ACTCH_CFG0_DATA_ENABLE              0x10
#define ACCEL5_ACTCH_CFG0_NPTS_POINT_32            0x00
#define ACCEL5_ACTCH_CFG0_NPTS_POINT_64            0x01
#define ACCEL5_ACTCH_CFG0_NPTS_POINT_128           0x02
#define ACCEL5_ACTCH_CFG0_NPTS_POINT_256           0x03
#define ACCEL5_ACTCH_CFG0_NPTS_POINT_512           0x04
/** \} */

/**
 * \defgroup tap_config_0    Tap Config 0
 * \{
 */
#define ACCEL5_TAP_CFG0_USE_Z_AXIS                 0x00
#define ACCEL5_TAP_CFG0_USE_Y_AXIS                 0x01
#define ACCEL5_TAP_CFG0_USE_X_AXIS                 0x02
#define ACCEL5_TAP_CFG0_TAP_SEL_HIGH               0x00
#define ACCEL5_TAP_CFG0_TAP_SEL_LOW                0x10
/** \} */

/**
 * \defgroup tap_config_1    Tap Config 1
 * \{
 */
#define ACCEL5_TAP_CFG1_QUIET_DT_SAMPLE_4          0x00
#define ACCEL5_TAP_CFG1_QUIET_DT_SAMPLE_8          0x10
#define ACCEL5_TAP_CFG1_QUIET_DT_SAMPLE_12         0x20
#define ACCEL5_TAP_CFG1_QUIET_DT_SAMPLE_16         0x30
#define ACCEL5_TAP_CFG1_QUIET_SAMPLE_60            0x00
#define ACCEL5_TAP_CFG1_QUIET_SAMPLE_80            0x04
#define ACCEL5_TAP_CFG1_QUIET_SAMPLE_100           0x08
#define ACCEL5_TAP_CFG1_QUIET_SAMPLE_120           0x0C
#define ACCEL5_TAP_CFG1_TICS_TH_SAMPLE_6           0x00
#define ACCEL5_TAP_CFG1_TICS_TH_SAMPLE_9           0x01
#define ACCEL5_TAP_CFG1_TICS_TH_SAMPLE_12          0x02
#define ACCEL5_TAP_CFG1_TICS_TH_SAMPLE_18          0x03
/** \} */

/**
 * \defgroup if_config    If Config
 * \{
 */
#define ACCEL5_IF_CONFIG_SPI_4_WIRE                0x00
#define ACCEL5_IF_CONFIG_SPI_3_WIRE                0x01
/** \} */

/**
 * \defgroup self_test    Self Test
 * \{
 */
#define ACCEL5_TEST_SIGN_ENABLE                    0x08
#define ACCEL5_TEST_Z_AXIS_ENABLE                  0x04
#define ACCEL5_TEST_Y_AXIS_ENABLE                  0x02
#define ACCEL5_TEST_X_AXIS_ENABLE                  0x01
/** \} */

/**
 * \defgroup command_register    Comand Register 
 * \{
 */
#define ACCEL5_CMD_FIFO_FLUSH                      0xB0
#define ACCEL5_CMD_STEP_CNT_CLEAR                  0xB1
#define ACCEL5_CMD_SOFTWARE_RESET                  0xB6
/** \} */

/**
 * \defgroup axis    Axis
 * \{
 */
#define ACCEL5_X_AXIS                              0x04
#define ACCEL5_Y_AXIS                              0x06
#define ACCEL5_Z_AXIS                              0x08
/** \} */ 

/**
 * \defgroup flags    Flags
 * \{
 */
#define DEVICE_ERROR                               0x01
#define DEVICE_OK                                  0x00
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

    digital_in_t it2;
    digital_in_t it1;

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} accel5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // Additional gpio pins 

    pin_name_t it2;
    pin_name_t it1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} accel5_cfg_t;

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
 * @param cfg  Click configuration structure.
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void accel5_cfg_setup ( accel5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t accel5_init ( accel5_t *ctx, accel5_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 * @description This function writes data to the desired register.
 */
err_t accel5_generic_write ( accel5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 * @description This function reads data from the desired register.
 */
err_t accel5_generic_read ( accel5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Click Default Configuration function..
 * 
 * @param ctx          Click object.
 * @param mode         Mode.
 * @param range        Range.
 * @description This Functions initializes accelerometer g-range and mode.
 *  Initialization contains and enable data, single tap, double tap, step,
 *  actch and x / y / z axis.
 */
void accel5_default_cfg ( accel5_t *ctx, uint8_t mode, uint8_t range );

/**
 * @brief Functions for write one byte in register.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data         Data
 * @description This function write byte.
 */
void accel5_write_byte ( accel5_t *ctx, uint8_t reg, uint8_t reg_data );

/**
 * @brief Functions for read byte from register.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @description This function read one byte data which is read from the register.
 */
uint8_t accel5_read_byte ( accel5_t *ctx, uint8_t reg );

/**
 * @brief Functions for read data from register.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @description This function read data.
 */
uint16_t accel5_read_data ( accel5_t *ctx, uint8_t reg );

/**
 * @brief Functions for read axis data.
 * 
 * @param ctx          Click object.
 * @param axis         Axis.
 * @description This function gets axis.
 */
int16_t accel5_get_axis ( accel5_t *ctx, uint8_t axis );

/**
 * @brief Functions for initialize the chip.
 * 
 * @param ctx          Click object.
 * @description The internal sensor time is calculated using the formula:
 *     Sensor time =  Time * 312.5us
 *     - Time   The value read from the three time sensor register.
 */
uint32_t accel5_sensor_time ( accel5_t *ctx );

/**
 * @brief Functions for read temperature.
 *
 * @param ctx          Click object.
 * @description This function read temperature.
 */
float accel5_get_temperature ( accel5_t *ctx );

/**
 * @brief Functions for software reset.
 * 
 * @param ctx          Click object.
 * @description This function software reset .
 */
void accel5_soft_reset ( accel5_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // ACCEL5_H

/** \} */ // End public_function group
/** \} */ // End click Driver group

// ------------------------------------------------------------------------ END

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
 * \brief This file contains API for c6DOF IMU 10 Click driver.
 *
 * \addtogroup c6dofimu10 c6DOF IMU 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef c6DOFIMU10_H
#define c6DOFIMU10_H

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
#define c6DOFIMU10_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.gp2  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.gp1  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define c6DOFIMU10_RETVAL  uint8_t

#define c6DOFIMU10_OK           0x00
#define c6DOFIMU10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_slave_address Device Slave Address
 * \{
 */
#define C6DOFIMU10_SLAVE_ADDRESS_GND    0x0E
#define C6DOFIMU10_SLAVE_ADDRESS_VCC    0x0F
/** \} */

/**
 * \defgroup Registers registers
 * \{
 */
#define C6DOFIMU10_REG_WHO_AM_I          0x00
#define C6DOFIMU10_REG_INS_1             0x01
#define C6DOFIMU10_REG_INS_2             0x02
#define C6DOFIMU10_REG_INS_3             0x03
#define C6DOFIMU10_REG_INL               0x05
#define C6DOFIMU10_REG_ACCEL_XOUT_L      0x0A
#define C6DOFIMU10_REG_ACCEL_XOUT        0x0A
#define C6DOFIMU10_REG_ACCEL_XOUT_H      0x0B
#define C6DOFIMU10_REG_ACCEL_YOUT_L      0x0C
#define C6DOFIMU10_REG_ACCEL_YOUT        0x0C
#define C6DOFIMU10_REG_ACCEL_YOUT_H      0x0D
#define C6DOFIMU10_REG_ACCEL_ZOUT_L      0x0E
#define C6DOFIMU10_REG_ACCEL_ZOUT        0x0E
#define C6DOFIMU10_REG_ACCEL_ZOUT_H      0x0F
#define C6DOFIMU10_REG_MAG_XOUT_L        0x10
#define C6DOFIMU10_REG_MAG_XOUT          0x10
#define C6DOFIMU10_REG_MAG_XOUT_H        0x11
#define C6DOFIMU10_REG_MAG_YOUT_L        0x12
#define C6DOFIMU10_REG_MAG_YOUT          0x12
#define C6DOFIMU10_REG_MAG_YOUT_H        0x13
#define C6DOFIMU10_REG_MAG_ZOUT_L        0x14
#define C6DOFIMU10_REG_MAG_ZOUT          0x14
#define C6DOFIMU10_REG_MAG_ZOUT_H        0x15
#define C6DOFIMU10_REG_TEMP_OUT_L        0x16
#define C6DOFIMU10_REG_TEMP_OUT          0x16
#define C6DOFIMU10_REG_TEMP_OUT_H        0x17
#define C6DOFIMU10_REG_INC_1             0x2A
#define C6DOFIMU10_REG_INC_2             0x2B
#define C6DOFIMU10_REG_INC_3             0x2C
#define C6DOFIMU10_REG_INC_4             0x2D
#define C6DOFIMU10_REG_INC_5             0x2E
#define C6DOFIMU10_REG_AMI_CNTL_1        0x2F
#define C6DOFIMU10_REG_AMI_CNTL_2        0x30
#define C6DOFIMU10_REG_AMI_CNTL_3        0x31
#define C6DOFIMU10_REG_MMI_CNTL_1        0x32
#define C6DOFIMU10_REG_MMI_CNTL_2        0x33
#define C6DOFIMU10_REG_MMI_CNTL_3        0x34
#define C6DOFIMU10_REG_FFI_CNTL_1        0x35
#define C6DOFIMU10_REG_FFI_CNTL_2        0x36
#define C6DOFIMU10_REG_FFI_CNTL_3        0x37
#define C6DOFIMU10_REG_ODCNTL            0x38
#define C6DOFIMU10_REG_CNTL_1            0x39
#define C6DOFIMU10_REG_CNTL_2            0x3A
#define C6DOFIMU10_REG_COTR              0x3C
#define C6DOFIMU10_REG_BUF_CTRL_1        0x77
#define C6DOFIMU10_REG_BUF_CTRL_2        0x78
#define C6DOFIMU10_REG_BUF_CTRL_3        0x79
#define C6DOFIMU10_REG_BUF_CLEAR         0x7A
#define C6DOFIMU10_REG_BUF_STATUS_1      0x7B
#define C6DOFIMU10_REG_BUF_STATUS_2      0x7C
#define C6DOFIMU10_REG_BUF_STATUS_3      0x7D
#define C6DOFIMU10_REG_BUF_READ          0x7E
/** \} */

/**
 * \defgroup default_register_value Default Register Value
 * \{
 */
#define C6DOFIMU10_DEF_WHO_AM_I           0x18
/** \} */

/**
 * \defgroup interrupt_source_register_1 Interrupt Source Register 1
 * \{
 */
#define C6DOFIMU10_INS1_NO_INTERRUPT_EVENT            0x00
#define C6DOFIMU10_INS1_INTERRUPT_EVENT               0x80
#define C6DOFIMU10_INS1_BUFFER_IS_NOT_FULL            0x00
#define C6DOFIMU10_INS1_BUFFER_IS_FULL                0x40
#define C6DOFIMU10_INS1_BUFFER_WM_NOT_REACHED         0x00
#define C6DOFIMU10_INS1_BUFFER_WM_REACHED             0x20
#define C6DOFIMU10_INS1_ACCEL_DATA_NOT_AVAILABLE      0x00
#define C6DOFIMU10_INS1_ACCEL_DATA_AVAILABLE          0x10
#define C6DOFIMU10_INS1_MAG_DATA_NOT_AVAILABLE        0x00
#define C6DOFIMU10_INS1_MAG_DATA_AVAILABLE            0x08
#define C6DOFIMU10_INS1_FREE_FALL_HAS_ACTIVATED       0x00
#define C6DOFIMU10_INS1_NO_FREE_FALL                  0x04
#define C6DOFIMU10_INS1_ACCEL_MOTION_HAS_ACTIVATED    0x00
#define C6DOFIMU10_INS1_NO_ACCEL_MOTION               0x02
#define C6DOFIMU10_INS1_MAG_MOTION_HAS_ACTIVATED      0x00
#define C6DOFIMU10_INS1_NO_MAG_MOTION                 0x01
/** \} */

/**
 * \defgroup interrupt_source_register_2 Interrupt Source Register 2
 * \{
 */
#define C6DOFIMU10_INS2_ACCEL_NEGATIVE_X              0x20
#define C6DOFIMU10_INS2_ACCEL_POSITIVE_X              0x10
#define C6DOFIMU10_INS2_ACCEL_NEGATIVE_Y              0x08
#define C6DOFIMU10_INS2_ACCEL_POSITIVE_Y              0x04
#define C6DOFIMU10_INS2_ACCEL_NEGATIVE_Z              0x02
#define C6DOFIMU10_INS2_ACCEL_POSITIVE_Z              0x01
/** \} */

/**
 * \defgroup interrupt_source_register_3 Interrupt Source Register 3
 * \{
 */
#define C6DOFIMU10_INS3_MAG_NEGATIVE_X                0x20
#define C6DOFIMU10_INS3_MAG_POSITIVE_X                0x10
#define C6DOFIMU10_INS3_MAG_NEGATIVE_Y                0x08
#define C6DOFIMU10_INS3_MAG_POSITIVE_Y                0x04
#define C6DOFIMU10_INS3_MAG_NEGATIVE_Z                0x02
#define C6DOFIMU10_INS3_MAG_POSITIVE_Z                0x01
/** \} */

/**
 * \defgroup interrupt_control_1 Interrupt Control 1
 * \{
 */
#define C6DOFIMU10_INC1_GP1_BUFF_FULL_INT_DISABLE     0x00
#define C6DOFIMU10_INC1_GP1_BUFF_FULL_INT_ENABLE      0x40
#define C6DOFIMU10_INC1_GP1_WM_INT_DISABLE            0x00
#define C6DOFIMU10_INC1_GP1_WM_INT_ENABLE             0x20
#define C6DOFIMU10_INC1_GP1_ACCEL_DRDY_DISABLE        0x00
#define C6DOFIMU10_INC1_GP1_ACCEL_DRDY_ENABLE         0x10
#define C6DOFIMU10_INC1_GP1_MAG_DRDY_DISABLE          0x00
#define C6DOFIMU10_INC1_GP1_MAG_DRDY_ENABLE           0x08
#define C6DOFIMU10_INC1_GP1_FREE_FALL_INT_DISABLE     0x00
#define C6DOFIMU10_INC1_GP1_FREE_FALL_INT_ENABLE      0x04
#define C6DOFIMU10_INC1_GP1_ACCEL_MOTION_DISABLE      0x00
#define C6DOFIMU10_INC1_GP1_ACCEL_MOTION_ENABLE       0x02
#define C6DOFIMU10_INC1_GP1_MAG_MOTION_DISABLE        0x00
#define C6DOFIMU10_INC1_GP1_MAG_MOTION_ENABLE         0x01
/** \} */

/**
 * \defgroup interrupt_control_2 Interrupt Control 2
 * \{
 */
#define C6DOFIMU10_INC2_GP2_BUFF_FULL_INT_DISABLE     0x00
#define C6DOFIMU10_INC2_GP2_BUFF_FULL_INT_ENABLE      0x40
#define C6DOFIMU10_INC2_GP2_WM_INT_DISABLE            0x00
#define C6DOFIMU10_INC2_GP2_WM_INT_ENABLE             0x20
#define C6DOFIMU10_INC2_GP2_ACCEL_DRDY_DISABLE        0x00
#define C6DOFIMU10_INC2_GP2_ACCEL_DRDY_ENABLE         0x10
#define C6DOFIMU10_INC2_GP2_MAG_DRDY_DISABLE          0x00
#define C6DOFIMU10_INC2_GP2_MAG_DRDY_ENABLE           0x08
#define C6DOFIMU10_INC2_GP2_FREE_FALL_INT_DISABLE     0x00
#define C6DOFIMU10_INC2_GP2_FREE_FALL_INT_ENABLE      0x04
#define C6DOFIMU10_INC2_GP2_ACCEL_MOTION_DISABLE      0x00
#define C6DOFIMU10_INC2_GP2_ACCEL_MOTION_ENABLE       0x02
#define C6DOFIMU10_INC2_GP2_MAG_MOTION_DISABLE        0x00
#define C6DOFIMU10_INC2_GP2_MAG_MOTION_ENABLE         0x01
/** \} */

/**
 * \defgroup interrupt_control_3 Interrupt Control 3
 * \{
 */
#define C6DOFIMU10_INC3_IED2_PUSH_PULL                0x00
#define C6DOFIMU10_INC3_IED2_OPEN_DRAIN               0x80
#define C6DOFIMU10_INC3_IEA2_ACTIVE_LOW               0x00
#define C6DOFIMU10_INC3_IEA2_ACTIVE_HIGH              0x40
#define C6DOFIMU10_INC3_IEL2_LATCHED                  0x00
#define C6DOFIMU10_INC3_IEL2_PULSED                   0x10
#define C6DOFIMU10_INC3_IEL2_TRIGGER                  0x20
#define C6DOFIMU10_INC3_IED1_PUSH_PULL                0x00
#define C6DOFIMU10_INC3_IED1_OPEN_DRAIN               0x08
#define C6DOFIMU10_INC3_IEA1_ACTIVE_LOW               0x00
#define C6DOFIMU10_INC3_IEA1_ACTIVE_HIGH              0x04
#define C6DOFIMU10_INC3_IEL1_LATCHED                  0x00
#define C6DOFIMU10_INC3_IEL1_PULSED                   0x01
#define C6DOFIMU10_INC3_IEL1_TRIGGER                  0x02
/** \} */

/**
 * \defgroup interrupt_control_4 Interrupt Control 4
 * \{
 */
#define C6DOFIMU10_INC4_ACCEL_NEGATIVE_X_ENABLE       0x20
#define C6DOFIMU10_INC4_ACCEL_POSITIVE_X_ENABLE       0x10
#define C6DOFIMU10_INC4_ACCEL_NEGATIVE_Y_ENABLE       0x08
#define C6DOFIMU10_INC4_ACCEL_POSITIVE_Y_ENABLE       0x04
#define C6DOFIMU10_INC4_ACCEL_NEGATIVE_Z_ENABLE       0x02
#define C6DOFIMU10_INC4_ACCEL_POSITIVE_Z_ENABLE       0x01
#define C6DOFIMU10_INC4_ACCEL_NEGATIVE_X_DISABLE      0x00
#define C6DOFIMU10_INC4_ACCEL_POSITIVE_X_DISABLE      0x00
#define C6DOFIMU10_INC4_ACCEL_NEGATIVE_Y_DISABLE      0x00
#define C6DOFIMU10_INC4_ACCEL_POSITIVE_Y_DISABLE      0x00
#define C6DOFIMU10_INC4_ACCEL_NEGATIVE_Z_DISABLE      0x00
#define C6DOFIMU10_INC4_ACCEL_POSITIVE_Z_DISABLE      0x00
/** \} */

/**
 * \defgroup interrupt_control_5 Interrupt Control 5
 * \{
 */
#define C6DOFIMU10_INC4_MAG_NEGATIVE_X_ENABLE         0x20
#define C6DOFIMU10_INC4_MAG_POSITIVE_X_ENABLE         0x10
#define C6DOFIMU10_INC4_MAG_NEGATIVE_Y_ENABLE         0x08
#define C6DOFIMU10_INC4_MAG_POSITIVE_Y_ENABLE         0x04
#define C6DOFIMU10_INC4_MAG_NEGATIVE_Z_ENABLE         0x02
#define C6DOFIMU10_INC4_MAG_POSITIVE_Z_ENABLE         0x01
#define C6DOFIMU10_INC4_MAG_NEGATIVE_X_DISABLE        0x00
#define C6DOFIMU10_INC4_MAG_POSITIVE_X_DISABLE        0x00
#define C6DOFIMU10_INC4_MAG_NEGATIVE_Y_DISABLE        0x00
#define C6DOFIMU10_INC4_MAG_POSITIVE_Y_DISABLE        0x00
#define C6DOFIMU10_INC4_MAG_NEGATIVE_Z_DISABLE        0x00
#define C6DOFIMU10_INC4_MAG_POSITIVE_Z_DISABLE        0x00
/** \} */

/**
 * \defgroup accelerometer_motion_control_3 Accelerometer Motion Control 3
 * \{
 */
#define C6DOFIMU10_AMICNTL3_ACCEL_MOTION_DISABLE      0x00 
#define C6DOFIMU10_AMICNTL3_ACCEL_MOTION_ENABLE       0x80
#define C6DOFIMU10_AMICNTL3_ACCEL_MOTION_LATCHED      0x00 
#define C6DOFIMU10_AMICNTL3_ACCEL_MOTION_UNLATCHED    0x40
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_0p781           0x00
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_1p563           0x01
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_3p125           0x02
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_6p25            0x03
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_12p5            0x04
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_25              0x05
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_50              0x06
#define C6DOFIMU10_AMICNTL3_ACCEL_ODR_100             0x07
/** \} */

/**
 * \defgroup magnetometer_motion_control_3 Magnetometer Motion Control 3
 * \{
 */
#define C6DOFIMU10_MMICNTL3_MAG_MOTION_DISABLE        0x00 
#define C6DOFIMU10_MMICNTL3_MAG_MOTION_ENABLE         0x80
#define C6DOFIMU10_MMICNTL3_MAG_MOTION_LATCHED        0x00 
#define C6DOFIMU10_MMICNTL3_MAG_MOTION_UNLATCHED      0x40
#define C6DOFIMU10_MMICNTL3_MAG_ODR_0p781             0x00
#define C6DOFIMU10_MMICNTL3_MAG_ODR_1p563             0x01
#define C6DOFIMU10_MMICNTL3_MAG_ODR_3p125             0x02
#define C6DOFIMU10_MMICNTL3_MAG_ODR_6p25              0x03
#define C6DOFIMU10_MMICNTL3_MAG_ODR_12p5              0x04
#define C6DOFIMU10_MMICNTL3_MAG_ODR_25                0x05
#define C6DOFIMU10_MMICNTL3_MAG_ODR_50                0x06
#define C6DOFIMU10_MMICNTL3_MAG_ODR_100               0x07
/** \} */

/**
 * \defgroup free_fall_control_3 Free Fall Control 3
 * \{
 */
#define C6DOFIMU10_FFICNTL3_FREE_FALL_DISABLE         0x00 
#define C6DOFIMU10_FFICNTL3_FREE_FALL_ENABLE          0x80
#define C6DOFIMU10_FFICNTL3_FREE_FALL_LATCHED         0x00 
#define C6DOFIMU10_FFICNTL3_FREE_FALL_UNLATCHED       0x40
#define C6DOFIMU10_FFICNTL3_FFI_DEBOUNCE_CNT_UP_DOWN  0x00 
#define C6DOFIMU10_FFICNTL3_FFI_DEBOUNCE_CNT_UP_RESET 0x08
#define C6DOFIMU10_FFICNTL3_ODR_12p5                  0x00
#define C6DOFIMU10_FFICNTL3_ODR_25                    0x01
#define C6DOFIMU10_FFICNTL3_ODR_50                    0x02
#define C6DOFIMU10_FFICNTL3_ODR_100                   0x03
#define C6DOFIMU10_FFICNTL3_ODR_200                   0x04
#define C6DOFIMU10_FFICNTL3_ODR_400                   0x05
#define C6DOFIMU10_FFICNTL3_ODR_800                   0x06
#define C6DOFIMU10_FFICNTL3_ODR_1600                  0x07
/** \} */

/**
 * \defgroup output_data_control_register Output Data Control Register
 * \{
 */
#define C6DOFIMU10_ODCNTL_MAG_ODR_12p5                0x00
#define C6DOFIMU10_ODCNTL_MAG_ODR_15                  0x10
#define C6DOFIMU10_ODCNTL_MAG_ODR_50                  0x20
#define C6DOFIMU10_ODCNTL_MAG_ODR_100                 0x30
#define C6DOFIMU10_ODCNTL_MAG_ODR_200                 0x40
#define C6DOFIMU10_ODCNTL_MAG_ODR_400                 0x50
#define C6DOFIMU10_ODCNTL_MAG_ODR_800                 0x60
#define C6DOFIMU10_ODCNTL_MAG_ODR_1600                0x70
#define C6DOFIMU10_ODCNTL_MAG_ODR_0p781               0x80
#define C6DOFIMU10_ODCNTL_MAG_ODR_1p563               0x90
#define C6DOFIMU10_ODCNTL_MAG_ODR_3p125               0xA0
#define C6DOFIMU10_ODCNTL_MAG_ODR_6p25                0xB0
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_12p5              0x00
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_15                0x01
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_50                0x02
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_100               0x03
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_200               0x04
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_400               0x05
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_800               0x06
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_1600              0x07
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_0p781             0x08
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_1p563             0x09
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_3p125             0x0A
#define C6DOFIMU10_ODCNTL_ACCEL_ODR_6p25              0x0B
/** \} */

/**
 * \defgroup control_register_1 Control Register 1
 * \{
 */
#define C6DOFIMU10_CNTL1_SW_RESET_NO_ACTION           0x00
#define C6DOFIMU10_CNTL1_SW_RESET_START_REBOOT        0x80
#define C6DOFIMU10_CNTL1_ST_MODE_DISABLE              0x00
#define C6DOFIMU10_CNTL1_ST_MODE_ENABLE               0x40
#define C6DOFIMU10_CNTL1_ST_POLARITY_POSITIVE         0x00
#define C6DOFIMU10_CNTL1_ST_POLARITY_NEGATIVE         0x20
#define C6DOFIMU10_CNTL1_COTC_NO_ACTION               0x00
#define C6DOFIMU10_CNTL1_COTC_SETS_COTR               0x08
/** \} */

/**
 * \defgroup control_register_2 Control Register 2
 * \{
 */
#define C6DOFIMU10_CNTL2_TEMP_STANDBY_MODE            0x00
#define C6DOFIMU10_CNTL2_TEMP_OPERATING_MODE          0x40
#define C6DOFIMU10_CNTL2_ACCEL_RANGE_2g               0x00
#define C6DOFIMU10_CNTL2_ACCEL_RANGE_4g               0x10
#define C6DOFIMU10_CNTL2_ACCEL_RANGE_8g               0x20
#define C6DOFIMU10_CNTL2_ACCEL_RANGE_16g              0x30
#define C6DOFIMU10_CNTL2_RES_SAMBLE_A4_M2             0x00
#define C6DOFIMU10_CNTL2_RES_SAMBLE_A32_M16           0x04
#define C6DOFIMU10_CNTL2_RES_SAMBLE_MAX_MAX           0x08
#define C6DOFIMU10_CNTL2_MAG_STANDBY_MODE             0x00
#define C6DOFIMU10_CNTL2_MAG_OPERATING_MODE           0x02
#define C6DOFIMU10_CNTL2_ACCEL_STANDBY_MODE           0x00
#define C6DOFIMU10_CNTL2_ACCEL_OPERATING_MODE         0x01
/** \} */

/**
 * \defgroup device_error Device Error
 * \{
 */
#define C6DOFIMU10_DEVICE_OK                          0
#define C6DOFIMU10_DEVICE_ERROR                       1
/** \} */

/**
 * \defgroup temperature_data_format Temperature Data Format
 * \{
 */
#define C6DOFIMU10_TEMP_FORMAT_FARENHAJT              2
#define C6DOFIMU10_TEMP_FORMAT_KELVIN                 1
#define C6DOFIMU10_TEMP_FORMAT_CELSIUS                0
/** \} */

/**
 * \defgroup Interrupt_pins Interrupt Pins
 * \{
 */
#define C6DOFIMU10_GP1_INT_PIN                        0
#define C6DOFIMU10_GP2_INT_PIN                        1
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Axis structure
 *
 * @param x  X axis data 
 * @param y  Y axis data 
 * @param z  Z axis data 
 */
typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;
  
} c6dofimu10_axis_t;

/**
 * @brief Motion interrupt structure
 *
 * @param neg_x  Negative X axis motion status 
 * @param pos_x  Positive X axis motion status 
 * @param neg_y  Negative Y axis motion status 
 * @param pos_y  Positive Y axis motion status 
 * @param neg_z  Negative Z axis motion status 
 * @param pos_z  Positive Z axis motion status 
 */
typedef struct
{
    uint8_t neg_x;
    uint8_t pos_x;
    uint8_t neg_y;
    uint8_t pos_y;
    uint8_t neg_z;
    uint8_t pos_z;

} c6dofimu10_motion_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t gp2;

    // Input pins 

    digital_in_t gp1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    c6dofimu10_axis_t axis;
    c6dofimu10_motion_t motion;

} c6dofimu10_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t gp2;
    pin_name_t gp1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

    uint8_t op_temp;
    uint8_t op_accel;
    uint8_t op_mag;
    uint8_t accel_range;
    uint8_t res_sample;    

} c6dofimu10_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void c6dofimu10_cfg_setup ( c6dofimu10_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c6dofimu10 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
c6DOFIMU10_RETVAL c6dofimu10_init ( c6dofimu10_t *ctx, c6dofimu10_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for c6DofImu10 Click.
 */
void c6dofimu10_default_cfg ( c6dofimu10_t *ctx );

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
void c6dofimu10_generic_write ( c6dofimu10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void c6dofimu10_generic_read ( c6dofimu10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Measurement config.
 *
 * @param ctx          Click object.
 * @param cfg          Measurement config structure.
 *
 * @description This function sets measurement config.
 */
void c6dofimu10_measurement_cfg( c6dofimu10_t *ctx, c6dofimu10_cfg_t *cfg );

/**
 * @brief Accelerometer axis data.
 *
 * @param ctx          Click object.
 * @param axis         Measurement config structure.
 *
 * @description This function gets accelerometer axis data.
 * 
 * @note axis data contains
 * <pre>
 *     - X axis data
 *     - Y axis data
 *     - Z axis data
 * </pre>
 */
void c6dofimu10_get_accel_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis );

/**
 * @brief Magnetometer axis data.
 *
 * @param ctx          Click object.
 * @param axis         Measurement config structure.
 *
 * @description This function gets magnetometer axis data.
 * 
 * @note axis data contains
 * <pre>
 *     - X axis data
 *     - Y axis data
 *     - Z axis data
 * </pre>
 */
void c6dofimu10_get_mag_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis );

/**
 * @brief Temperature data.
 *
 * @param ctx          Click object.
 * @param temp_format  Temperature data format.
 *
 * @description This function gets temperature data.
 * 
 * @note Temperature format options: 
 * <pre>
 *    - C6DOFIMU10_TEMP_FORMAT_FARENHAJT 
 *    - C6DOFIMU10_TEMP_FORMAT_KELVIN    
 *    - C6DOFIMU10_TEMP_FORMAT_CELSIUS 
 * </pre>
 */
float c6dofimu10_get_temperature ( c6dofimu10_t *ctx, uint8_t temp_format );

/**
 * @brief Communication test.
 *
 * @param ctx          Click object.
 *
 * @description This function test communication.
 * 
 * @note Test comunication info: 
 * <pre>
 *    - C6DOFIMU10_DEVICE_OK   
 *    - C6DOFIMU10_DEVICE_ERROR
 * </pre>
 */
uint8_t c6dofimu10_communication_test ( c6dofimu10_t *ctx );

/**
 * @brief Get motion interrupt status.
 *
 * @param ctx          Click object.
 * @param sensor_reg   Sensor register.
 * @param motion_obj   Motion status object.
 *
 * @description This function gets motion.
 * 
 * @note Sensor register options: 
 * <pre>
 *    - INS3 - Interrupt Source Register 3   
 *    - INS2 - Interrupt Source Register 2
 * </pre>
 */
void c6dofimu10_get_motion ( c6dofimu10_t *ctx, uint8_t sensor_reg, c6dofimu10_motion_t *motion_obj );

/**
 * @brief Get interrupt pin status.
 *
 * @param ctx         Click object.
 * @param int_pin     Sensor register.
 *
 * @description This function gets interrupt.
 * 
 * @note Interrupt pin options: 
 * <pre>
 *   - C6DOFIMU10_GP1_INT_PIN - PWM pin 
 *   - C6DOFIMU10_GP2_INT_PIN - RST pin 
 * </pre>
 */
uint8_t c6dofimu10_get_interrupt ( c6dofimu10_t *ctx, uint8_t int_pin );

#ifdef __cplusplus
}
#endif
#endif  // _c6DOFIMU10_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

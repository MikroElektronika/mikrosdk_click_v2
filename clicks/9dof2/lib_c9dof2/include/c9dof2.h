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
 * \brief This file contains API for 9 DOF 2 Click driver.
 *
 * \addtogroup c9dof2 9 DOF 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C9DOF2_H
#define C9DOF2_H

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

#define C9DOF2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.snc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C9DOF2_RETVAL  uint8_t

#define C9DOF2_OK           0x00
#define C9DOF2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mag_regs Magnetometer Registers
 * \{
 */
#define C9DOF2_AK09916_ADR         0x0C
#define C9DOF2_WHO_AM_I_AK09916    0x01
#define C9DOF2_AK09916_ST1         0x10
#define C9DOF2_AK09916_XOUT_L      0x11
#define C9DOF2_AK09916_XOUT_H      0x12
#define C9DOF2_AK09916_YOUT_L      0x13
#define C9DOF2_AK09916_YOUT_H      0x14
#define C9DOF2_AK09916_ZOUT_L      0x15
#define C9DOF2_AK09916_ZOUT_H      0x16
#define C9DOF2_AK09916_ST2         0x18
#define C9DOF2_AK09916_CNTL        0x30
#define C9DOF2_AK09916_CNTL2       0x31
/** \} */

/**
 * \defgroup usr_bnk_0 User Bank 0 Register Map
 * \{
 */
#define C9DOF2_WHO_AM_I_ICM20948    0x00
#define C9DOF2_USER_CTRL            0x03
#define C9DOF2_LP_CCFG              0x05
#define C9DOF2_PWR_MGMT_1           0x06
#define C9DOF2_PWR_MGMT_2           0x07
#define C9DOF2_INT_PIN_CFG          0x0F
#define C9DOF2_INT_EN               0x10
#define C9DOF2_INT_EN_1             0x11
#define C9DOF2_INT_EN_2             0x12
#define C9DOF2_INT_EN_3             0x13
#define C9DOF2_I2C_MST_STAT         0x17
#define C9DOF2_INT_STAT             0x19
#define C9DOF2_INT_STAT_1           0x1A
#define C9DOF2_INT_STAT_2           0x1B
#define C9DOF2_INT_STAT_3           0x1C
#define C9DOF2_DELAY_TIMEH          0x28
#define C9DOF2_DELAY_TIMEL          0x29
#define C9DOF2_ACCEL_XOUT_H         0x2D
#define C9DOF2_ACCEL_XOUT_L         0x2E
#define C9DOF2_ACCEL_YOUT_H         0x2F
#define C9DOF2_ACCEL_YOUT_L         0x30
#define C9DOF2_ACCEL_ZOUT_H         0x31
#define C9DOF2_ACCEL_ZOUT_L         0x32
#define C9DOF2_GYRO_XOUT_H          0x33
#define C9DOF2_GYRO_XOUT_L          0x34
#define C9DOF2_GYRO_YOUT_H          0x35
#define C9DOF2_GYRO_YOUT_L          0x36
#define C9DOF2_GYRO_ZOUT_H          0x37
#define C9DOF2_GYRO_ZOUT_L          0x38
#define C9DOF2_TEMP_OUT_H           0x39
#define C9DOF2_TEMP_OUT_L           0x3A
#define C9DOF2_EXT_SENS_DATA_00     0x3B
#define C9DOF2_EXT_SENS_DATA_01     0x3C
#define C9DOF2_EXT_SENS_DATA_02     0x3D
#define C9DOF2_EXT_SENS_DATA_03     0x3E
#define C9DOF2_EXT_SENS_DATA_04     0x3F
#define C9DOF2_EXT_SENS_DATA_05     0x40
#define C9DOF2_EXT_SENS_DATA_06     0x41
#define C9DOF2_EXT_SENS_DATA_07     0x42
#define C9DOF2_EXT_SENS_DATA_08     0x43
#define C9DOF2_EXT_SENS_DATA_09     0x44
#define C9DOF2_EXT_SENS_DATA_10     0x45
#define C9DOF2_EXT_SENS_DATA_11     0x46
#define C9DOF2_EXT_SENS_DATA_12     0x47
#define C9DOF2_EXT_SENS_DATA_13     0x48
#define C9DOF2_EXT_SENS_DATA_14     0x49
#define C9DOF2_EXT_SENS_DATA_15     0x4A
#define C9DOF2_EXT_SENS_DATA_16     0x4B
#define C9DOF2_EXT_SENS_DATA_17     0x4C
#define C9DOF2_EXT_SENS_DATA_18     0x4D
#define C9DOF2_EXT_SENS_DATA_19     0x4E
#define C9DOF2_EXT_SENS_DATA_20     0x4F
#define C9DOF2_EXT_SENS_DATA_21     0x50
#define C9DOF2_EXT_SENS_DATA_22     0x51
#define C9DOF2_EXT_SENS_DATA_23     0x52
#define C9DOF2_FIFO_EN_1            0x66
#define C9DOF2_FIFO_EN_2            0x67
#define C9DOF2_FIFO_RST             0x68
#define C9DOF2_FIFO_MODE            0x69
#define C9DOF2_FIFO_CNT_H           0x70
#define C9DOF2_FIFO_CNT_L           0x71
#define C9DOF2_FIFO_R_W             0x72
#define C9DOF2_DATA_RDY_STAT        0x74
#define C9DOF2_FIFO_CFG             0x76
#define C9DOF2_REG_BANK_SEL         0x7F
/** \} */

/**
 * \defgroup usr_bnk_1 User Bank 1 Register Map
 * \{
 */
#define C9DOF2_SELF_TEST_X_GYRO       0x02
#define C9DOF2_SELF_TEST_Y_GYRO       0x03
#define C9DOF2_SELF_TEST_Z_GYRO       0x04
#define C9DOF2_SELF_TEST_X_ACCEL      0x0E
#define C9DOF2_SELF_TEST_Y_ACCEL      0x0F
#define C9DOF2_SELF_TEST_Z_ACCEL      0x10
#define C9DOF2_XA_OFFSET_H            0x14
#define C9DOF2_XA_OFFSET_L            0x15
#define C9DOF2_YA_OFFSET_H            0x17
#define C9DOF2_YA_OFFSET_L            0x18
#define C9DOF2_ZA_OFFSET_H            0x1A
#define C9DOF2_ZA_OFFSET_L            0x1B
#define C9DOF2_TIMEBASE_CORREC_PLL    0x28
/** \} */

/**
 * \defgroup usr_bnk_2 User Bank 2 Register Map
 * \{
 */
#define C9DOF2_GYRO_SMPLRT_DIV       0x00
#define C9DOF2_GYRO_CFG_1            0x01
#define C9DOF2_GYRO_CFG_2            0x02
#define C9DOF2_XG_OFFSET_H           0x03
#define C9DOF2_XG_OFFSET_L           0x04
#define C9DOF2_YG_OFFSET_H           0x05
#define C9DOF2_YG_OFFSET_L           0x06
#define C9DOF2_ZG_OFFSET_H           0x07
#define C9DOF2_ZG_OFFSET_L           0x08
#define C9DOF2_ODR_ALIGN_EN          0x09
#define C9DOF2_ACCEL_SMPLRT_DIV_1    0x10
#define C9DOF2_ACCEL_SMPLRT_DIV_2    0x11
#define C9DOF2_ACCEL_INTEL_CTRL      0x12
#define C9DOF2_ACCEL_WOM_THR         0x13
#define C9DOF2_ACCEL_CFG             0x14
#define C9DOF2_ACCEL_CFG_2           0x15
#define C9DOF2_FSYNC_CFG             0x52
#define C9DOF2_TEMP_CFG              0x53
#define C9DOF2_MOD_CTRL_USR          0x54
/** \} */

/**
 * \defgroup usr_bnk_3 User Bank 3 Register Map
 * \{
 */
#define C9DOF2_I2C_MST_ODR_CFG       0x00
#define C9DOF2_I2C_MST_CTRL          0x01
#define C9DOF2_I2C_MST_DELAY_CTRL    0x02
#define C9DOF2_I2C_SLV0_ADR          0x03
#define C9DOF2_I2C_SLV0_REG          0x04
#define C9DOF2_I2C_SLV0_CTRL         0x05
#define C9DOF2_I2C_SLV0_DO           0x06
#define C9DOF2_I2C_SLV1_ADR          0x07
#define C9DOF2_I2C_SLV1_REG          0x08
#define C9DOF2_I2C_SLV1_CTRL         0x09
#define C9DOF2_I2C_SLV1_DO           0x0A
#define C9DOF2_I2C_SLV2_ADR          0x0B
#define C9DOF2_I2C_SLV2_REG          0x0C
#define C9DOF2_I2C_SLV2_CTRL         0x0D
#define C9DOF2_I2C_SLV2_DO           0x0E
#define C9DOF2_I2C_SLV3_ADR          0x0F
#define C9DOF2_I2C_SLV3_REG          0x10
#define C9DOF2_I2C_SLV3_CTRL         0x11
#define C9DOF2_I2C_SLV3_DO           0x12
#define C9DOF2_I2C_SLV4_ADR          0x13
#define C9DOF2_I2C_SLV4_REG          0x14
#define C9DOF2_I2C_SLV4_CTRL         0x15
#define C9DOF2_I2C_SLV4_DO           0x16
#define C9DOF2_I2C_SLV4_DI           0x17
/** \} */

/**
 * \defgroup reg_banks Register Banks
 * \{
 */
#define C9DOF2_REG_BANK_0           0x00
#define C9DOF2_REG_BANK_1           0x10
#define C9DOF2_REG_BANK_2           0x20
#define C9DOF2_REG_BANK_3           0x30
/** \} */

/**
 * \defgroup usr_ctrl_cmd User Control Register Commands
 * \{
 */
#define C9DOF2_USER_CTL_DMP_EN         0x80
#define C9DOF2_USER_CTL_FIFO_EN        0x40
#define C9DOF2_USER_CTL_I2C_MST_EN     0x20
#define C9DOF2_USER_CTL_I2C_IF_DIS     0x10
#define C9DOF2_USER_CTL_DMP_RST        0x08
#define C9DOF2_USER_CTL_SRAM_RST       0x04
#define C9DOF2_USER_CTL_I2C_MST_RST    0x02
/** \} */

/**
 * \defgroup low_pow_cmd Low Power Register Commands
 * \{
 */
#define C9DOF2_LP_CFG_I2C_MST_CYC      0x80
#define C9DOF2_LP_CFG_ACCEL_CYC        0x40
#define C9DOF2_LP_CFG_GYRO_CYC         0x20
/** \} */

/**
 * \defgroup pwr_mgm_1 Power Management 1 Register Commands
 * \{
 */
#define C9DOF2_PWR_MGMT_1_DEV_RST      0x80
#define C9DOF2_PWR_MGMT_1_SLP          0x40
#define C9DOF2_PWR_MGMT_1_LP_EN        0x20
#define C9DOF2_PWR_MGMT_1_TEMP_DIS     0x08
#define C9DOF2_PWR_MGMT_1_CLKSEL_7     0x07
#define C9DOF2_PWR_MGMT_1_CLKSEL_6     0x06
#define C9DOF2_PWR_MGMT_1_CLKSEL_5     0x05
#define C9DOF2_PWR_MGMT_1_CLKSEL_4     0x04
#define C9DOF2_PWR_MGMT_1_CLKSEL_3     0x03
#define C9DOF2_PWR_MGMT_1_CLKSEL_2     0x02
#define C9DOF2_PWR_MGMT_1_CLKSEL_1     0x01
#define C9DOF2_PWR_MGMT_1_CLKSEL_0     0x00
/** \} */

/**
 * \defgroup pwr_mgm_2 Power Management 2 Register Commands
 * \{
 */
#define C9DOF2_PWR_MGMT_2_DIS_XA    0x20
#define C9DOF2_PWR_MGMT_2_DIS_YA    0x10
#define C9DOF2_PWR_MGMT_2_DIS_ZA    0x08
#define C9DOF2_PWR_MGMT_2_DIS_XG    0x04
#define C9DOF2_PWR_MGMT_2_DIS_YG    0x02
#define C9DOF2_PWR_MGMT_2_DIS_ZG    0x01
/** \} */

/**
 * \defgroup int_pin_cmd Interrupt/Bypass Pin Configuration Register Commands
 * \{
 */
#define C9DOF2_INT_PIN_CFG_ACTL                 0x80
#define C9DOF2_INT_PIN_CFG_OPEN                 0x40
#define C9DOF2_INT_PIN_CFG_LATCH_INT_EN         0x20
#define C9DOF2_INT_PIN_CFG_INT_ANYRD_2CLR       0x10
#define C9DOF2_INT_PIN_CFG_ACTL_FSYNC           0x08
#define C9DOF2_INT_PIN_CFG_FSYNC_INT_MODE_EN    0x04
#define C9DOF2_INT_PIN_CFG_BYPASS_EN            0x02
/** \} */

/**
 * \defgroup int_en_cmd Interrupt Enable Register Commands
 * \{
 */
#define C9DOF2_INT_ENABLE_REG_WOF_EN         0x80
#define C9DOF2_INT_ENABLE_WOM_INT_EN         0x08
#define C9DOF2_INT_ENABLE_PLL_RDY_EN         0x04
#define C9DOF2_INT_ENABLE_FIFO_OVF_EN        0x10
#define C9DOF2_INT_ENABLE_DMP_INT1_EN        0x04
#define C9DOF2_INT_ENABLE_I2C_MST_INT_EN     0x01
/** \} */

/**
 * \defgroup int_en_1_cmd Interrupt Enable 1 Register Commands
 * \{
 */
#define C9DOF2_INT_EN_1_RAW_DATA_0_RDY_EN    0x01
/** \} */

/**
 * \defgroup int_en_2_cmd Interrupt Enable 2 Register Commands
 * \{
 */
#define C9DOF2_INT_EN_2_FIFO_OVERFLOW_EN    0x1F
/** \} */

/**
 * \defgroup int_en_3_cmd Interrupt Enable 3 Register Commands
 * \{
 */
#define C9DOF2_INT_ENABLE_3_FIFO_WM_EN     0x1F
/** \} */

/**
 * \defgroup i2c_mstr I2C Master Status
 * \{
 */
#define C9DOF2_I2C_MST_STAT_PASS_THROUGH     0x80
#define C9DOF2_I2C_MST_STAT_I2C_SLV4_DONE    0x40
#define C9DOF2_I2C_MST_STAT_I2C_LOST_ARB     0x20
#define C9DOF2_I2C_MST_STAT_I2C_SLV4_NACK    0x10
#define C9DOF2_I2C_MST_STAT_I2C_SLV3_NACK    0x08
#define C9DOF2_I2C_MST_STAT_I2C_SLV2_NACK    0x04
#define C9DOF2_I2C_MST_STAT_I2C_SLV1_NACK    0x02
#define C9DOF2_I2C_MST_STAT_I2C_SLV0_NACK    0x01
/** \} */

/**
 * \defgroup int_status Interrupt Status
 * \{
 */
#define C9DOF2_INT_STAT_WOM_INT           0x80
#define C9DOF2_INT_STAT_PLL_RDY_INT       0x40
#define C9DOF2_INT_STAT_DMP_INT1          0x20
#define C9DOF2_INT_STAT_I2C_MST_INT       0x10
/** \} */

/**
 * \defgroup int_status_1 Interrupt Status 1 Register
 * \{
 */
#define C9DOF2_INT_STAT_1_RAW_DATA_0_RDY_EN    0x01
/** \} */

/**
 * \defgroup int_status_2 Interrupt Status 2 Register
 * \{
 */
#define C9DOF2_INT_STAT_2_FIFO_OWF_EN        0x1F
/** \} */

/**
 * \defgroup int_status_3 Interrupt Status 3 Register
 * \{
 */
#define C9DOF2_INT_STAT_3_FIFO_WM_EN         0x1F
/** \} */

/**
 * \defgroup fifo_1_reg_cmd FIFO Enable 1 Register Commands
 * \{
 */
#define C9DOF2_FIFO_EN_1_SLV_3_FIFO_EN     0x08
#define C9DOF2_FIFO_EN_1_SLV_2_FIFO_EN     0x04
#define C9DOF2_FIFO_EN_1_SLV_1_FIFO_EN     0x02
#define C9DOF2_FIFO_EN_1_SLV_0_FIFO_EN     0x01
/** \} */

/**
 * \defgroup fifo_2_reg_cmd FIFO Enable 2 Register Commands
 * \{
 */
#define C9DOF2_FIFO_EN_2_ACCEL_FIFO_EN     0x10
#define C9DOF2_FIFO_EN_2_GYRO_Z_FIFO_EN    0x08
#define C9DOF2_FIFO_EN_2_GYRO_Y_FIFO_EN    0x04
#define C9DOF2_FIFO_EN_2_GYRO_X_FIFO_EN    0x02
#define C9DOF2_FIFO_EN_2_TEMP_FIFO_EN      0x01
/** \} */

/**
 * \defgroup int_stat_1_reg Interrupt Status 1 Register
 * \{
 */
#define C9DOF2_FIFO_CFG_CMD               0x01
/** \} */

/**
 * \defgroup gyro_cfg_reg_cmd Gyroscope Configuration Register Commands
 * \{
 */
#define C9DOF2_GYRO_CFG_1_DLPFCFG_7      0x38
#define C9DOF2_GYRO_CFG_1_DLPFCFG_6      0x30
#define C9DOF2_GYRO_CFG_1_DLPFCFG_5      0x28
#define C9DOF2_GYRO_CFG_1_DLPFCFG_4      0x20
#define C9DOF2_GYRO_CFG_1_DLPFCFG_3      0x18
#define C9DOF2_GYRO_CFG_1_DLPFCFG_2      0x10
#define C9DOF2_GYRO_CFG_1_DLPFCFG_1      0x08
#define C9DOF2_GYRO_CFG_1_DLPFCFG_0      0x00
#define C9DOF2_GYRO_CFG_1_FS_SEL_2000    0x06
#define C9DOF2_GYRO_CFG_1_FS_SEL_1000    0x04
#define C9DOF2_GYRO_CFG_1_FS_SEL_500     0x02
#define C9DOF2_GYRO_CFG_1_FS_SEL_250     0x00
#define C9DOF2_GYRO_CFG_1_FCHOICE_EN     0x01
#define C9DOF2_GYRO_CFG_1_FCHOICE_BP     0x00
/** \} */

/**
 * \defgroup gyro_cfg_reg_cmd Gyroscope Configuration Register Commands
 * \{
 */
#define C9DOF2_GYRO_CFG_2_XGYRO_CTEN    0x20
#define C9DOF2_GYRO_CFG_2_YGYRO_CTEN    0x10
#define C9DOF2_GYRO_CFG_2_ZGYRO_CTEN    0x08
#define C9DOF2_GYRO_CFG_2_AVGCFG_7      0x07
#define C9DOF2_GYRO_CFG_2_AVGCFG_6      0x06
#define C9DOF2_GYRO_CFG_2_AVGCFG_5      0x05
#define C9DOF2_GYRO_CFG_2_AVGCFG_4      0x04
#define C9DOF2_GYRO_CFG_2_AVGCFG_3      0x03
#define C9DOF2_GYRO_CFG_2_AVGCFG_2      0x02
#define C9DOF2_GYRO_CFG_2_AVGCFG_1      0x01
#define C9DOF2_GYRO_CFG_2_AVGCFG_0      0x00
/** \} */

/**
 * \defgroup odr_alg_cmd ODR Start-time Alignment Commands
 * \{
 */
#define C9DOF2_ODR_ALIGN_CMD_EN       0x01
#define C9DOF2_ODR_ALIGN_CMD_DIS      0x00
/** \} */

/**
 * \defgroup odr_alg_cmd ODR Start-time Alignment Commands
 * \{
 */
#define C9DOF2_ACCEL_INTEL_CTL_INTEL_EN               0x02
#define C9DOF2_ACCEL_INTEL_CTL_INTEL_MODE_INT_CURR    0x01
#define C9DOF2_ACCEL_INTEL_CTL_INTEL_MODE_INT_INIT    0x00
/** \} */

/**
 * \defgroup acc_cfg_reg_cmd Accelerometer Configuration Register commands
 * \{
 */
#define C9DOF2_ACCEL_CFG_DLPFCFG_7     0x38
#define C9DOF2_ACCEL_CFG_DLPFCFG_6     0x30
#define C9DOF2_ACCEL_CFG_DLPFCFG_5     0x28
#define C9DOF2_ACCEL_CFG_DLPFCFG_4     0x20
#define C9DOF2_ACCEL_CFG_DLPFCFG_3     0x18
#define C9DOF2_ACCEL_CFG_DLPFCFG_2     0x10
#define C9DOF2_ACCEL_CFG_DLPFCFG_1     0x08
#define C9DOF2_ACCEL_CFG_DLPFCFG_0     0x00
#define C9DOF2_ACCEL_CFG_FS_SEL_16G    0x06
#define C9DOF2_ACCEL_CFG_FS_SEL_8G     0x04
#define C9DOF2_ACCEL_CFG_FS_SEL_4G     0x02
#define C9DOF2_ACCEL_CFG_FS_SEL_2G     0x00
#define C9DOF2_ACCEL_CFG_FCHOICE_EN    0x01
#define C9DOF2_ACCEL_CFG_FCHOICE_BP    0x00
/** \} */

/**
 * \defgroup acc_cfg_reg_cmd Accelerometer Configuration 2 Register commands
 * \{
 */
#define C9DOF2_ACCEL_2_CFG_AX_ST_EN_REG     0x10
#define C9DOF2_ACCEL_2_CFG_AY_ST_EN_REG     0x08
#define C9DOF2_ACCEL_2_CFG_AZ_ST_EN_REG     0x04
#define C9DOF2_ACCEL_2_CFG_DEC3_CFG_32      0x03
#define C9DOF2_ACCEL_2_CFG_DEC3_CFG_16      0x02
#define C9DOF2_ACCEL_2_CFG_DEC3_CFG_8       0x01
#define C9DOF2_ACCEL_2_CFG_DEC3_CFG_4       0x00
#define C9DOF2_ACCEL_2_CFG_DEC3_CFG_1       0x00
/** \} */

/**
 * \defgroup fsync_cfg_reg_cmd FSYNC Configuration Register Commands
 * \{
 */
#define C9DOF2_FSYNC_CFG_DELAY_TIME_EN                0x80
#define C9DOF2_FSYNC_CFG_WOF_DEGLITCH_EN              0x40
#define C9DOF2_FSYNC_CFG_WOF_EDGE_INT                 0x20
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_ACCEL_ZOUT_L    0x07
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_ACCEL_YOUT_L    0x06
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_ACCEL_XOUT_L    0x05
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_GYRO_ZOUT_L     0x04
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_GYRO_YOUT_L     0x03
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_GYRO_XOUT_L     0x02
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_TEMP_OUT_L      0x01
#define C9DOF2_FSYNC_CFG_EXT_SYNC_SET_DIS             0x00
/** \} */

/**
 * \defgroup temp_cfg_reg_cmd Temperature Configuration Register Commands
 * \{
 */
#define C9DOF2_TEMP_CFG_DLPFCFG_7    0x07
#define C9DOF2_TEMP_CFG_DLPFCFG_6    0x06
#define C9DOF2_TEMP_CFG_DLPFCFG_5    0x05
#define C9DOF2_TEMP_CFG_DLPFCFG_4    0x04
#define C9DOF2_TEMP_CFG_DLPFCFG_3    0x03
#define C9DOF2_TEMP_CFG_DLPFCFG_2    0x02
#define C9DOF2_TEMP_CFG_DLPFCFG_1    0x01
#define C9DOF2_TEMP_CFG_DLPFCFG_0    0x00
/** \} */

/**
 * \defgroup odr_alg_cmd ODR Start-time Alignment Commands
 * \{
 */
#define C9DOF2_MOD_CTRL_USR_REG_LP_DMP_EN     0x01
#define C9DOF2_MOD_CTRL_USR_REG_LP_DMP_DIS    0x00
/** \} */

/**
 * \defgroup magm_meas_mode_cmd Magnetometer Measurement Mode Commands
 * \{
 */
#define C9DOF2_CNTL2_MODE_SELF_TEST      0x10
#define C9DOF2_CNTL2_MODE_CONT_MEAS_4    0x08
#define C9DOF2_CNTL2_MODE_CONT_MEAS_3    0x06
#define C9DOF2_CNTL2_MODE_CONT_MEAS_2    0x04
#define C9DOF2_CNTL2_MODE_CONT_MEAS_1    0x02
#define C9DOF2_CNTL2_MODE_ONE_SHOT       0x01
#define C9DOF2_CNTL2_MODE_POW_DOWN       0x00
/** \} */
 
/**
 * \defgroup magm_soft_rst Magnetometer Soft Reset Commands
 * \{
 */
#define C9DOF2_CNTL3_SOFT_RST           0x01
/** \} */

/**
 * \defgroup who_am_i "Who Am I" Value For ICM-20948
 * \{
 */
#define C9DOF2_WHO_AM_I_ICM20948_VAL   0xEA
/** \} */

/**
 * \defgroup sens_val Sensor Sensitivity Values
 * \{
 */
#define C9DOF2_GYRO_SENS_FS_SEL_2000     16.4
#define C9DOF2_GYRO_SENS_FS_SEL_1000     32.8
#define C9DOF2_GYRO_SENS_FS_SEL_500      65.5
#define C9DOF2_GYRO_SENS_FS_SEL_250      131.0
#define C9DOF2_ACCEL_SENS_FS_SEL_16G     2048.0
#define C9DOF2_ACCEL_SENS_FS_SEL_8G      4096.0
#define C9DOF2_ACCEL_SENS_FS_SEL_4G      8192.0
#define C9DOF2_ACCEL_SENS_FS_SEL_2G      16384.0
/** \} */

/**
 * \defgroup pow_states Power States
 * \{
 */
#define C9DOF2_POWER_ON                0x01
#define C9DOF2_POWER_OFF               0x00
/** \} */

/**
 * \defgroup pow_states Power States
 * \{
 */
#define C9DOF2_SNC_LOW                0x00
#define C9DOF2_SNC_HIGH               0x01
/** \} */

/**
 * \defgroup spi_masks SPI Masks
 * \{
 */
#define C9DOF2_READ_BIT_MASK           0x80
#define C9DOF2_WRITE_BIT_MASK          0x7F
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

    digital_out_t snc;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} c9dof2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t snc;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} c9dof2_cfg_t;

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
void c9dof2_cfg_setup ( c9dof2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c9dof2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C9DOF2_RETVAL c9dof2_init ( c9dof2_t *ctx, c9dof2_cfg_t *cfg );

/**
 * @brief Write Byte function
 *
 * @param ctx          Click object.
 * @param reg               8-bit register address
 * @param wr_data           8-bit write data
 *
 * @description Writes one byte into register defined by 8-bit register
 * address
**/
void c9dof2_write_byte ( c9dof2_t *ctx, uint8_t reg, uint8_t wr_data );

/**
 * @brief Write Data function
 *
 * @param ctx          Click object.
 * @param reg              8-bit register address
 * @param wr_data          16-bit write data
 *
 * @description Writes two bytes into registers defined by 8-bit register
 * address
**/
void c9dof2_write_data ( c9dof2_t *ctx, uint8_t reg, int16_t wr_data );

/**
 * @brief Read Byte function
 *
 * @param ctx          Click object.
 * @param reg  8-bit register address
 *
 * @returns result 8-bit read data
 *
 * @descritpion Reads one byte from register defined by 8-bit register
 * address
**/
uint8_t c9dof2_read_byte ( c9dof2_t *ctx, uint8_t reg );

/**
 * @brief Read Data function
 *
 * @param ctx          Click object.
 * @param reg  8-bit register address
 *
 * @returns result 16-bit read data
 *
 * @description Reads two byte from registers defined by 8-bit register
 * address
**/
int16_t c9dof2_read_data ( c9dof2_t *ctx, uint8_t reg );

/**
 * @brief Device Reset function
 *
 * @param ctx          Click object.
 * 
 * @description Function is used to perform soft reset.
**/
void c9dof2_dev_rst ( c9dof2_t *ctx );

/**
 * @brief Power up function
 *
 * @param ctx           Click object.
 * @param on_off        Value defines power state of the device
 *
 * @description Turns the device on or off.
 * @note It is advisable to use predefined values.
**/
void c9dof2_power ( c9dof2_t *ctx, uint8_t on_off );

/**
 * @brief Default settings function
 *
 * @param ctx           Click object.
 * 
 * @description Function is used to apply the default settings to the device.
 * @note It is advisable to use this device once.
**/
void c9dof2_def_settings ( c9dof2_t *ctx );

/**
 * @brief Read gyroscope data function
 *
 * @param ctx           Click object.
 * @param gyro_x        16-bit gyroscope X-axis data
 * @param gyro_y        16-bit gyroscope Y-axis data
 * @param gyro_z        16-bit gyroscope Z-axis data
 *
 * @description Function is used to read gyroscope data.
**/
void c9dof2_read_gyroscope ( c9dof2_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

/**
 * @brief Read Angular Rate function
 *
 * @param ctx           Click object.
 * @param x_ang_rte     float X-axis angular rate
 * @param y_ang_rte     float Y-axis angular rate
 * @param z_ang_rte     float Z-axis angular rate
 *
 * @description Function is used to calculate angular rate.
**/
void c9dof2_angular_rate ( c9dof2_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte );

/**
 * @brief Read accelerometer data function
 *
 * @param ctx           Click object.
 * @param accel_x       16-bit accelerometer X-axis data
 * @param accel_y       16-bit accelerometer Y-axis data
 * @param accel_z       16-bit accelerometer Z-axis data
 *
 * @description Function is used to read accelerometer data.
**/
void c9dof2_read_accelerometer ( c9dof2_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

/**
 * @brief Read acceleration Rate function
 *
 * @param ctx               Click object.
 * @param x_accel_rte       float X-axis acceleration rate
 * @param y_accel_rte       float Y-axis acceleration rate
 * @param z_accel_rte       float Z-axis acceleration rate
 *
 * @description Function is used to calculate acceleration rate.
**/
void c9dof2_acceleration_rate ( c9dof2_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte );

/**
 * @brief Read temperture function
 *
 * @param ctx               Click object.
 * @param temp_offs         temperature offset.
 * 
 * @returns result float temperture data
 *
 * @description Function is used to read temperture in degree Centigrade.
**/
float c9dof2_read_temperature ( c9dof2_t *ctx, float temp_offs );

/**
 * @brief Check Interrupt state function
 *
 * @param ctx               Click object.
 * 
 * @return
 *      <pre>
 *          - 0 : Interrupt has not occured
 *          - 1 : Interrupt has occured
 *      </pre>
 * 
 * @description Function is used to check if an interrupt has occured.
**/
uint8_t c9dof2_check_int ( c9dof2_t *ctx );

/**
 * @brief FSYNC Pin State function
 *
 * @param ctx               Click object.
 * @param state             value that defines the state of the FSYNC pin.
 *
 * @description Function is used to define the device to change the state of the pin.
**/
void c9dof2_snc_pin ( c9dof2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _C9DOF2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

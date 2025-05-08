/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file c6dofimu27.h
 * @brief This file contains API for 6DOF IMU 27 Click Driver.
 */

#ifndef C6DOFIMU27_H
#define C6DOFIMU27_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup c6dofimu27 6DOF IMU 27 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 27 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu27_reg 6DOF IMU 27 Registers List
 * @brief List of registers of 6DOF IMU 27 Click driver.
 */

/**
 * @addtogroup c6dofimu27_reg
 * @{
 */

/**
 * @brief 6DOF IMU 27 USER BANK 0 register map summary.
 * @details The list of USER BANK 0 registers.
 */
#define C6DOFIMU27_REG_ACCEL_DATA_X1_UI                     0x00
#define C6DOFIMU27_REG_ACCEL_DATA_X0_UI                     0x01
#define C6DOFIMU27_REG_ACCEL_DATA_Y1_UI                     0x02
#define C6DOFIMU27_REG_ACCEL_DATA_Y0_UI                     0x03
#define C6DOFIMU27_REG_ACCEL_DATA_Z1_UI                     0x04
#define C6DOFIMU27_REG_ACCEL_DATA_Z0_UI                     0x05
#define C6DOFIMU27_REG_GYRO_DATA_X1_UI                      0x06
#define C6DOFIMU27_REG_GYRO_DATA_X0_UI                      0x07
#define C6DOFIMU27_REG_GYRO_DATA_Y1_UI                      0x08
#define C6DOFIMU27_REG_GYRO_DATA_Y0_UI                      0x09
#define C6DOFIMU27_REG_GYRO_DATA_Z1_UI                      0x0A
#define C6DOFIMU27_REG_GYRO_DATA_Z0_UI                      0x0B
#define C6DOFIMU27_REG_TEMP_DATA1_UI                        0x0C
#define C6DOFIMU27_REG_TEMP_DATA0_UI                        0x0D
#define C6DOFIMU27_REG_TMST_FSYNCH                          0x0E
#define C6DOFIMU27_REG_TMST_FSYNCL                          0x0F
#define C6DOFIMU27_REG_PWR_MGMT0                            0x10
#define C6DOFIMU27_REG_FIFO_COUNT_0                         0x12
#define C6DOFIMU27_REG_FIFO_COUNT_1                         0x13
#define C6DOFIMU27_REG_FIFO_DATA                            0x14
#define C6DOFIMU27_REG_INT1_CONFIG0                         0x16
#define C6DOFIMU27_REG_INT1_CONFIG1                         0x17
#define C6DOFIMU27_REG_INT1_CONFIG2                         0x18
#define C6DOFIMU27_REG_INT1_STATUS0                         0x19
#define C6DOFIMU27_REG_INT1_STATUS1                         0x1A
#define C6DOFIMU27_REG_ACCEL_CONFIG0                        0x1B
#define C6DOFIMU27_REG_GYRO_CONFIG0                         0x1C
#define C6DOFIMU27_REG_FIFO_CONFIG0                         0x1D
#define C6DOFIMU27_REG_FIFO_CONFIG1_0                       0x1E
#define C6DOFIMU27_REG_FIFO_CONFIG1_1                       0x1F
#define C6DOFIMU27_REG_FIFO_CONFIG2                         0x20
#define C6DOFIMU27_REG_FIFO_CONFIG3                         0x21
#define C6DOFIMU27_REG_FIFO_CONFIG4                         0x22
#define C6DOFIMU27_REG_TMST_WOM_CONFIG                      0x23
#define C6DOFIMU27_REG_FSYNC_CONFIG0                        0x24
#define C6DOFIMU27_REG_FSYNC_CONFIG1                        0x25
#define C6DOFIMU27_REG_RTC_CONFIG                           0x26
#define C6DOFIMU27_REG_DMP_EXT_SEN_ODR_CFG                  0x27
#define C6DOFIMU27_REG_ODR_DECIMATE_CONFIG                  0x28
#define C6DOFIMU27_REG_EDMP_APEX_EN0                        0x29
#define C6DOFIMU27_REG_EDMP_APEX_EN1                        0x2A
#define C6DOFIMU27_REG_APEX_BUFFER_MGMT                     0x2B
#define C6DOFIMU27_REG_INTF_CONFIG0                         0x2C
#define C6DOFIMU27_REG_INTF_CONFIG1_OVRD                    0x2D
#define C6DOFIMU27_REG_INTF_AUX_CONFIG                      0x2E
#define C6DOFIMU27_REG_IOC_PAD_SCENARIO                     0x2F
#define C6DOFIMU27_REG_IOC_PAD_SCENARIO_AUX_OVRD            0x30
#define C6DOFIMU27_REG_DRIVE_CONFIG0                        0x32
#define C6DOFIMU27_REG_DRIVE_CONFIG1                        0x33
#define C6DOFIMU27_REG_DRIVE_CONFIG2                        0x34
#define C6DOFIMU27_REG_INT_APEX_CONFIG0                     0x39
#define C6DOFIMU27_REG_INT_APEX_CONFIG1                     0x3A
#define C6DOFIMU27_REG_INT_APEX_STATUS0                     0x3B
#define C6DOFIMU27_REG_INT_APEX_STATUS1                     0x3C
#define C6DOFIMU27_REG_ACCEL_DATA_X1_UI_AUX1                0x44
#define C6DOFIMU27_REG_ACCEL_DATA_X0_UI_AUX1                0x45
#define C6DOFIMU27_REG_ACCEL_DATA_Y1_UI_AUX1                0x46
#define C6DOFIMU27_REG_ACCEL_DATA_Y0_UI_AUX1                0x47
#define C6DOFIMU27_REG_ACCEL_DATA_Z1_UI_AUX1                0x48
#define C6DOFIMU27_REG_ACCEL_DATA_Z0_UI_AUX1                0x49
#define C6DOFIMU27_REG_GYRO_DATA_X1_UI_AUX1                 0x4A
#define C6DOFIMU27_REG_GYRO_DATA_X0_UI_AUX1                 0x4B
#define C6DOFIMU27_REG_GYRO_DATA_Y1_UI_AUX1                 0x4C
#define C6DOFIMU27_REG_GYRO_DATA_Y0_UI_AUX1                 0x4D
#define C6DOFIMU27_REG_GYRO_DATA_Z1_UI_AUX1                 0x4E
#define C6DOFIMU27_REG_GYRO_DATA_Z0_UI_AUX1                 0x4F
#define C6DOFIMU27_REG_TEMP_DATA1_UI_AUX1                   0x50
#define C6DOFIMU27_REG_TEMP_DATA0_UI_AUX1                   0x51
#define C6DOFIMU27_REG_TMST_FSYNCH_AUX1                     0x52
#define C6DOFIMU27_REG_TMST_FSYNCL_AUX1                     0x53
#define C6DOFIMU27_REG_PWR_MGMNT0_AUX1                      0x54
#define C6DOFIMU27_REG_FS_SEL_AUX1                          0x55
#define C6DOFIMU27_REG_INT2_CONFIG0                         0x56
#define C6DOFIMU27_REG_INT2_CONFIG1                         0x57
#define C6DOFIMU27_REG_INT2_CONFIG2                         0x58
#define C6DOFIMU27_REG_INT2_STATUS0                         0x59
#define C6DOFIMU27_REG_INT2_STATUS1                         0x5A
#define C6DOFIMU27_REG_WHO_AM_I                             0x72
#define C6DOFIMU27_REG_REG_HOST_MSG                         0x73
#define C6DOFIMU27_REG_IREG_ADDR_15_8                       0x7C
#define C6DOFIMU27_REG_IREG_ADDR_7_0                        0x7D
#define C6DOFIMU27_REG_IREG_DATA                            0x7E
#define C6DOFIMU27_REG_MISC2                                0x7F

/*! @} */ // c6dofimu27_reg

/**
 * @defgroup c6dofimu27_set 6DOF IMU 27 Registers Settings
 * @brief Settings for registers of 6DOF IMU 27 Click driver.
 */

/**
 * @addtogroup c6dofimu27_set
 * @{
 */

/**
 * @brief 6DOF IMU 27 MISC2 register setting.
 * @details Specified setting for MISC2 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_MISC2_SOFT_RST                           0x02
#define C6DOFIMU27_MISC2_IREG_DONE                          0x01

/**
 * @brief 6DOF IMU 27 INTx_CONFIG0/INTx_STATUS0 register setting.
 * @details Specified setting for INTx_CONFIG0/INTx_STATUS0 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_INTX_STATUS0_RESET_DONE                  0x80
#define C6DOFIMU27_INTX_STATUS0_AUX1_AGC_RDY                0x40
#define C6DOFIMU27_INTX_STATUS0_AP_AGC_RDY                  0x20
#define C6DOFIMU27_INTX_STATUS0_AP_FSYNC                    0x10
#define C6DOFIMU27_INTX_STATUS0_AUX1_DRDY                   0x08
#define C6DOFIMU27_INTX_STATUS0_DRDY                        0x04
#define C6DOFIMU27_INTX_STATUS0_FIFO_THS                    0x02
#define C6DOFIMU27_INTX_STATUS0_FIFO_FULL                   0x01

/**
 * @brief 6DOF IMU 27 INTx_CONFIG1/INTx_STATUS1 register setting.
 * @details Specified setting for INTx_CONFIG1/INTx_STATUS1 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_INTX_STATUS1_APEX_EVENT                  0x40
#define C6DOFIMU27_INTX_STATUS1_I2CM_DONE                   0x20
#define C6DOFIMU27_INTX_STATUS1_I3C_PROTOCOL_ERR            0x10
#define C6DOFIMU27_INTX_STATUS1_WOM_Z                       0x08
#define C6DOFIMU27_INTX_STATUS1_WOM_Y                       0x04
#define C6DOFIMU27_INTX_STATUS1_WOM_X                       0x02
#define C6DOFIMU27_INTX_STATUS1_PLL_RDY                     0x01

/**
 * @brief 6DOF IMU 27 INTx_CONFIG2 register setting.
 * @details Specified setting for INTx_CONFIG2 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_INTX_CONFIG2_DRIVE_PP                    0x00
#define C6DOFIMU27_INTX_CONFIG2_DRIVE_OD                    0x04
#define C6DOFIMU27_INTX_CONFIG2_DRIVE_MASK                  0x04
#define C6DOFIMU27_INTX_CONFIG2_MODE_PULSE                  0x00
#define C6DOFIMU27_INTX_CONFIG2_MODE_LATCH                  0x02
#define C6DOFIMU27_INTX_CONFIG2_MODE_MASK                   0x02
#define C6DOFIMU27_INTX_CONFIG2_POLARITY_ACT_LOW            0x00
#define C6DOFIMU27_INTX_CONFIG2_POLARITY_ACT_HIGH           0x01
#define C6DOFIMU27_INTX_CONFIG2_POLARITY_MASK               0x01

/**
 * @brief 6DOF IMU 27 PWR_MGMT0 register setting.
 * @details Specified setting for PWR_MGMT0 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_PWR_MGMT0_GYRO_MODE_OFF                  0x00
#define C6DOFIMU27_PWR_MGMT0_GYRO_MODE_STBY                 0x04
#define C6DOFIMU27_PWR_MGMT0_GYRO_MODE_LP                   0x08
#define C6DOFIMU27_PWR_MGMT0_GYRO_MODE_LN                   0x0C
#define C6DOFIMU27_PWR_MGMT0_GYRO_MODE_MASK                 0x0C
#define C6DOFIMU27_PWR_MGMT0_ACCEL_MODE_OFF                 0x00
#define C6DOFIMU27_PWR_MGMT0_ACCEL_MODE_LP                  0x02
#define C6DOFIMU27_PWR_MGMT0_ACCEL_MODE_LN                  0x03
#define C6DOFIMU27_PWR_MGMT0_ACCEL_MODE_MASK                0x03

/**
 * @brief 6DOF IMU 27 GYRO_CONFIG0 register setting.
 * @details Specified setting for GYRO_CONFIG0 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_4000DPS           0x00
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_2000DPS           0x10
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_1000DPS           0x20
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_500DPS            0x30
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_250DPS            0x40
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_125DPS            0x50
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_62_5DPS           0x60
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_31_25DPS          0x70
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_15_625DPS         0x80
#define C6DOFIMU27_GYRO_CONFIG0_UI_FS_SEL_MASK              0xF0
#define C6DOFIMU27_GYRO_CONFIG0_ODR_6400HZ                  0x03
#define C6DOFIMU27_GYRO_CONFIG0_ODR_3200HZ                  0x04
#define C6DOFIMU27_GYRO_CONFIG0_ODR_1600HZ                  0x05
#define C6DOFIMU27_GYRO_CONFIG0_ODR_800HZ                   0x06
#define C6DOFIMU27_GYRO_CONFIG0_ODR_400HZ                   0x07
#define C6DOFIMU27_GYRO_CONFIG0_ODR_200HZ                   0x08
#define C6DOFIMU27_GYRO_CONFIG0_ODR_100HZ                   0x09
#define C6DOFIMU27_GYRO_CONFIG0_ODR_50HZ                    0x0A
#define C6DOFIMU27_GYRO_CONFIG0_ODR_25HZ                    0x0B
#define C6DOFIMU27_GYRO_CONFIG0_ODR_12_5HZ                  0x0C
#define C6DOFIMU27_GYRO_CONFIG0_ODR_6_25HZ                  0x0D
#define C6DOFIMU27_GYRO_CONFIG0_ODR_3_125HZ                 0x0E
#define C6DOFIMU27_GYRO_CONFIG0_ODR_1_5625HZ                0x0F
#define C6DOFIMU27_GYRO_CONFIG0_ODR_MASK                    0x0F

/**
 * @brief 6DOF IMU 27 ACCEL_CONFIG0 register setting.
 * @details Specified setting for ACCEL_CONFIG0 register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_ACCEL_CONFIG0_UI_FS_SEL_32G              0x00
#define C6DOFIMU27_ACCEL_CONFIG0_UI_FS_SEL_16G              0x10
#define C6DOFIMU27_ACCEL_CONFIG0_UI_FS_SEL_8G               0x20
#define C6DOFIMU27_ACCEL_CONFIG0_UI_FS_SEL_4G               0x30
#define C6DOFIMU27_ACCEL_CONFIG0_UI_FS_SEL_2G               0x40
#define C6DOFIMU27_ACCEL_CONFIG0_UI_FS_SEL_MASK             0x70
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_6400HZ                 0x03
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_3200HZ                 0x04
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_1600HZ                 0x05
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_800HZ                  0x06
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_400HZ                  0x07
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_200HZ                  0x08
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_100HZ                  0x09
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_50HZ                   0x0A
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_25HZ                   0x0B
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_12_5HZ                 0x0C
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_6_25HZ                 0x0D
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_3_125HZ                0x0E
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_1_5625HZ               0x0F
#define C6DOFIMU27_ACCEL_CONFIG0_ODR_MASK                   0x0F

/**
 * @brief 6DOF IMU 27 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_WHO_AM_I                                 0xE9

/**
 * @brief 6DOF IMU 27 gyro fs sel and odr setting.
 * @details Specified setting for gyro full scale resolution and output data rate of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_GYRO_FS_SEL_15_625DPS                    0x00
#define C6DOFIMU27_GYRO_FS_SEL_31_25DPS                     0x01
#define C6DOFIMU27_GYRO_FS_SEL_62_5DPS                      0x02
#define C6DOFIMU27_GYRO_FS_SEL_125DPS                       0x03
#define C6DOFIMU27_GYRO_FS_SEL_250DPS                       0x04
#define C6DOFIMU27_GYRO_FS_SEL_500DPS                       0x05
#define C6DOFIMU27_GYRO_FS_SEL_1000DPS                      0x06
#define C6DOFIMU27_GYRO_FS_SEL_2000DPS                      0x07
#define C6DOFIMU27_GYRO_FS_SEL_4000DPS                      0x08
#define C6DOFIMU27_GYRO_ODR_1_5625HZ                        0x00
#define C6DOFIMU27_GYRO_ODR_3_125HZ                         0x01
#define C6DOFIMU27_GYRO_ODR_6_25HZ                          0x02
#define C6DOFIMU27_GYRO_ODR_12_5HZ                          0x03
#define C6DOFIMU27_GYRO_ODR_25HZ                            0x04
#define C6DOFIMU27_GYRO_ODR_50HZ                            0x05
#define C6DOFIMU27_GYRO_ODR_100HZ                           0x06
#define C6DOFIMU27_GYRO_ODR_200HZ                           0x07
#define C6DOFIMU27_GYRO_ODR_400HZ                           0x08
#define C6DOFIMU27_GYRO_ODR_800HZ                           0x09
#define C6DOFIMU27_GYRO_ODR_1600HZ                          0x0A
#define C6DOFIMU27_GYRO_ODR_3200HZ                          0x0B
#define C6DOFIMU27_GYRO_ODR_6400HZ                          0x0C
#define C6DOFIMU27_GYRO_DATA_RES                            32767.0
#define C6DOFIMU27_GYRO_MIN_DPS                             15.625

/**
 * @brief 6DOF IMU 27 accel fs sel and odr setting.
 * @details Specified setting for accel full scale resolution and output data rate of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_ACCEL_FS_SEL_2G                          0x00
#define C6DOFIMU27_ACCEL_FS_SEL_4G                          0x01
#define C6DOFIMU27_ACCEL_FS_SEL_8G                          0x02
#define C6DOFIMU27_ACCEL_FS_SEL_16G                         0x03
#define C6DOFIMU27_ACCEL_FS_SEL_32G                         0x04
#define C6DOFIMU27_ACCEL_ODR_1_5625HZ                       0x00
#define C6DOFIMU27_ACCEL_ODR_3_125HZ                        0x01
#define C6DOFIMU27_ACCEL_ODR_6_25HZ                         0x02
#define C6DOFIMU27_ACCEL_ODR_12_5HZ                         0x03
#define C6DOFIMU27_ACCEL_ODR_25HZ                           0x04
#define C6DOFIMU27_ACCEL_ODR_50HZ                           0x05
#define C6DOFIMU27_ACCEL_ODR_100HZ                          0x06
#define C6DOFIMU27_ACCEL_ODR_200HZ                          0x07
#define C6DOFIMU27_ACCEL_ODR_400HZ                          0x08
#define C6DOFIMU27_ACCEL_ODR_800HZ                          0x09
#define C6DOFIMU27_ACCEL_ODR_1600HZ                         0x0A
#define C6DOFIMU27_ACCEL_ODR_3200HZ                         0x0B
#define C6DOFIMU27_ACCEL_ODR_6400HZ                         0x0C
#define C6DOFIMU27_ACCEL_DATA_RES                           32767.0
#define C6DOFIMU27_ACCEL_MIN_G                              2.0

/**
 * @brief 6DOF IMU 27 temperature calculation setting.
 * @details Specified setting for temperature calculation of 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_TEMP_RES                                 128.0
#define C6DOFIMU27_TEMP_OFFSET                              25.0

/**
 * @brief 6DOF IMU 27 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 27 Click driver.
 */
#define C6DOFIMU27_DEVICE_ADDRESS_0                         0x68
#define C6DOFIMU27_DEVICE_ADDRESS_1                         0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu27_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU27_SET_DATA_SAMPLE_EDGE                     SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU27_SET_DATA_SAMPLE_MIDDLE                   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu27_set

/**
 * @defgroup c6dofimu27_map 6DOF IMU 27 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 27 Click driver.
 */

/**
 * @addtogroup c6dofimu27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 27 Click to the selected MikroBUS.
 */
#define C6DOFIMU27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu27_map
/*! @} */ // c6dofimu27

/**
 * @brief 6DOF IMU 27 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 27 Click driver.
 */
typedef enum
{
    C6DOFIMU27_DRV_SEL_SPI,         /**< SPI driver descriptor. */
    C6DOFIMU27_DRV_SEL_I2C          /**< I2C driver descriptor. */

} c6dofimu27_drv_t;

/**
 * @brief 6DOF IMU 27 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 27 Click driver.
 */
struct c6dofimu27_s;
typedef err_t ( *c6dofimu27_master_io_t )( struct c6dofimu27_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 27 Click context object.
 * @details Context object definition of 6DOF IMU 27 Click driver.
 */
typedef struct c6dofimu27_s
{
    digital_in_t int2;              /**< Interrupt 2 pin. */
    digital_in_t int1;              /**< Interrupt 1 pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu27_drv_t drv_sel;       /**< Master driver interface selector. */

    c6dofimu27_master_io_t write_f; /**< Master write function. */
    c6dofimu27_master_io_t read_f;  /**< Master read function. */

    float gyro_sens;                /**< Gyro sensitivity setting. */
    float accel_sens;               /**< Accel sensitivity setting. */

} c6dofimu27_t;

/**
 * @brief 6DOF IMU 27 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 27 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int2;                /**< Interrupt 2 pin. */
    pin_name_t int1;                /**< Interrupt 1 pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    c6dofimu27_drv_t drv_sel;       /**< Master driver interface selector. */

} c6dofimu27_cfg_t;

/**
 * @brief 6DOF IMU 27 Click axes data structure.
 * @details Axes data object definition of 6DOF IMU 27 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} c6dofimu27_axes_t;

/**
 * @brief 6DOF IMU 27 Click data structure.
 * @details Data object definition of 6DOF IMU 27 Click driver.
 */
typedef struct
{
    c6dofimu27_axes_t gyro;         /**< Gyro data. */
    c6dofimu27_axes_t accel;        /**< Accel data. */
    float temperature;              /**< Temperature data. */

} c6dofimu27_data_t;

/**
 * @brief 6DOF IMU 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU27_OK = 0,
    C6DOFIMU27_ERROR = -1

} c6dofimu27_return_value_t;

/*!
 * @addtogroup c6dofimu27 6DOF IMU 27 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 27 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu27_cfg_setup ( c6dofimu27_cfg_t *cfg );

/**
 * @brief 6DOF IMU 27 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu27_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu27_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu27_drv_interface_sel ( c6dofimu27_cfg_t *cfg, c6dofimu27_drv_t drv_sel );

/**
 * @brief 6DOF IMU 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_init ( c6dofimu27_t *ctx, c6dofimu27_cfg_t *cfg );

/**
 * @brief 6DOF IMU 27 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 27
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu27_default_cfg ( c6dofimu27_t *ctx );

/**
 * @brief 6DOF IMU 27 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_write_regs ( c6dofimu27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 27 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_read_regs ( c6dofimu27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 27 write register function.
 * @details This function writes a data byte to the selected bank 0 register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_write_reg ( c6dofimu27_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 6DOF IMU 27 read register function.
 * @details This function reads data from the selected bank 0 register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_read_reg ( c6dofimu27_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 6DOF IMU 27 get int1 pin function.
 * @details This function returns the INT1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu27_get_int1_pin ( c6dofimu27_t *ctx );

/**
 * @brief 6DOF IMU 27 get int2 pin function.
 * @details This function returns the INT2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu27_get_int2_pin ( c6dofimu27_t *ctx );

/**
 * @brief 6DOF IMU 27 reset device function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_reset_device ( c6dofimu27_t *ctx );

/**
 * @brief 6DOF IMU 27 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_check_communication ( c6dofimu27_t *ctx );

/**
 * @brief 6DOF IMU 27 set gyro fs odr function.
 * @details This function sets the gyro full scale resolution and output data rate.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] fs_sel : Full scale selection: 0-3 which leads to 250x2^fs_sel DPS.
 * @param[in] odr : Output data rate: 0-7 which leads to 12.5x2^odr Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_set_gyro_fs_odr ( c6dofimu27_t *ctx, uint8_t fs_sel, uint8_t odr );

/**
 * @brief 6DOF IMU 27 set accel fs odr function.
 * @details This function sets the accel full scale resolution and output data rate.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[in] fs_sel : Full scale selection: 0-3 which leads to 2x2^fs_sel G.
 * @param[in] odr : Output data rate: 0-10 which leads to 1.5625x2^odr Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_set_accel_fs_odr ( c6dofimu27_t *ctx, uint8_t fs_sel, uint8_t odr );

/**
 * @brief 6DOF IMU 27 read gyro function.
 * @details This function reads the angular rate of X, Y, and Z axis in degrees per second (dps).
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[out] gyro : Output gyro data.
 * See #c6dofimu27_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_read_gyro ( c6dofimu27_t *ctx, c6dofimu27_axes_t *gyro );

/**
 * @brief 6DOF IMU 27 read accel function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (g).
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[out] accel : Output accelerometer data.
 * See #c6dofimu27_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_read_accel ( c6dofimu27_t *ctx, c6dofimu27_axes_t *accel );

/**
 * @brief 6DOF IMU 27 read temperature function.
 * @details This function reads the temperature measurement in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_read_temperature ( c6dofimu27_t *ctx, float *temperature );

/**
 * @brief 6DOF IMU 27 read data function.
 * @details This function reads the accelerometer, gyroscope, and temperature measurement data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu27_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure read.
 * See #c6dofimu27_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu27_read_data ( c6dofimu27_t *ctx, c6dofimu27_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU27_H

/*! @} */ // c6dofimu27

// ------------------------------------------------------------------------ END

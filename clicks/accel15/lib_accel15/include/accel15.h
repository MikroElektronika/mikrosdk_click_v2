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
 * @file accel15.h
 * @brief This file contains API for Accel 15 Click Driver.
 */

#ifndef ACCEL15_H
#define ACCEL15_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
    
/*!
 * @addtogroup accel15 Accel 15 Click Driver
 * @brief API for configuring and manipulating Accel 15 Click driver.
 * @{
 */

/**
 * @defgroup accel15_reg Accel 15 Registers List
 * @brief List of registers of Accel 15 Click driver.
 */

/**
 * @addtogroup accel15_reg
 * @{
 */

/**
 * @brief Accel 15 description register.
 * @details Specified register for description of Accel 15 Click driver.
 */
#define ACCEL15_REG_CHIP_ID                           0x00 
#define ACCEL15_REG_ERROR                             0x02 
#define ACCEL15_REG_STATUS                            0x03 
#define ACCEL15_REG_DATA_0                            0x0A 
#define ACCEL15_REG_DATA_8                            0x12
#define ACCEL15_REG_SENSORTIME_0                      0x18 
#define ACCEL15_REG_EVENT                             0x1B
#define ACCEL15_REG_INT_STAT_0                        0x1C
#define ACCEL15_REG_INT_STAT_1                        0x1D 
#define ACCEL15_REG_TEMPERATURE                       0x22
#define ACCEL15_REG_FIFO_LENGTH_0                     0x24 
#define ACCEL15_REG_FIFO_DATA                         0x26
#define ACCEL15_REG_INTERNAL_STAT                     0x2A
#define ACCEL15_REG_ACCEL_CONFIG                      0x40 
#define ACCEL15_REG_ACCEL_RANGE                       0x41
#define ACCEL15_REG_AUX_CONF                          0x44
#define ACCEL15_REG_FIFO_DOWN                         0x45 
#define ACCEL15_REG_FIFO_WTM_0                        0x46 
#define ACCEL15_REG_FIFO_CONFIG_0                     0x48 
#define ACCEL15_REG_FIFO_CONFIG_1                     0x49
#define ACCEL15_REG_AUX_DEV_ID                        0x4B
#define ACCEL15_REG_AUX_IF_CONF                       0x4C
#define ACCEL15_REG_AUX_RD                            0x4D 
#define ACCEL15_REG_INT1_IO_CTRL                      0x53 
#define ACCEL15_REG_INT2_IO_CTRL                      0x54 
#define ACCEL15_REG_INT_LATCH                         0x55 
#define ACCEL15_REG_INT_MAP_1                         0x56 
#define ACCEL15_REG_INT_MAP_2                         0x57 
#define ACCEL15_REG_INT_MAP_DATA                      0x58 
#define ACCEL15_REG_INIT_CTRL                         0x59
#define ACCEL15_REG_RESERVED_REG_5B                   0x5B 
#define ACCEL15_REG_RESERVED_REG_5C                   0x5C 
#define ACCEL15_REG_FEATURE_CONFIG                    0x5E 
#define ACCEL15_REG_INTERNAL_ERROR                    0x5F 
#define ACCEL15_REG_ACC_SELF_TEST                     0x6D 
#define ACCEL15_REG_ACC_SELF_TEST                     0x6D
#define ACCEL15_REG_NV_CONFIG                         0x70
#define ACCEL15_REG_OFFSET_0                          0x71 
#define ACCEL15_REG_OFFSET_1                          0x72 
#define ACCEL15_REG_OFFSET_2                          0x73  
#define ACCEL15_REG_POWER_CONF                        0x7C 
#define ACCEL15_REG_POWER_CTRL                        0x7D 
#define ACCEL15_REG_CMD                               0x7E  

/*! @} */ // accel15_reg

/**
 * @defgroup accel15_set Accel 15 Registers Settings
 * @brief Settings for registers of Accel 15 Click driver.
 */

/**
 * @addtogroup accel15_set
 * @{
 */

/**
 * @brief Accel 15 description setting.
 * @details Specified setting for description of Accel 15 Click driver.
 */

/**
 * @brief Accel 15 data.
 * @details Specified setting for data of Accel 15 Click driver.
 */
#define ACCEL15_CHIP_ID                               0x1A 
#define ACCEL15_FEATURE_SIZE                          0x0C 
#define ACCEL15_RD_WR_MIN_LEN                         0x02 
#define ACCEL15_RD_WR_MAX_LEN                         1300 

/**
 * @brief Accel 15 feature start address.
 * @details Specified setting for feature start address of Accel 15 Click driver.
 */
#define ACCEL15_ANY_MOT_START_ADDR                    0x00 
#define ACCEL15_NO_MOT_START_ADDR                     0x04 
#define ACCEL15_CONFIG_ID_START_ADDR                  0x08 
#define ACCEL15_AXES_REMAP_START_ADDR                 0x0A 

/**
 * @brief Accel 15 Mask definitions for axes re-mapping.
 * @details Specified setting for mask definitions for axes re-mapping
 * of Accel 15 Click driver.
 */
#define ACCEL15_X_AXIS_MSK                            0x03 
#define ACCEL15_X_AXIS_SIGN_MSK                       0x04 
#define ACCEL15_Y_AXIS_MSK                            0x18 
#define ACCEL15_Y_AXIS_SIGN_MSK                       0x20 
#define ACCEL15_Z_AXIS_MSK                            0xC0 
#define ACCEL15_Z_AXIS_SIGN_MSK                       0x01 

/**
 * @brief Accel 15 Bit position for axes re-mapping.
 * @details Specified setting for bit position for axes re-mapping
 * of Accel 15 Click driver.
 */
#define ACCEL15_X_AXIS_SIGN_POS                       0x02 
#define ACCEL15_Y_AXIS_POS                            0x03 
#define ACCEL15_Y_AXIS_SIGN_POS                       0x05 
#define ACCEL15_Z_AXIS_POS                            0x06 

/**
 * @brief Accel 15 Any/No-motion axis enable macros.
 * @details Specified setting for any/no-motion axis enable macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_X_AXIS_EN                             0x01 
#define ACCEL15_Y_AXIS_EN                             0x02 
#define ACCEL15_Z_AXIS_EN                             0x04 
#define ACCEL15_EN_ALL_AXIS                           0x07 
#define ACCEL15_DIS_ALL_AXIS                          0x00 

/**
 * @brief Accel 15 Interrupt status macros.
 * @details Specified setting for Interrupt status macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_ANY_MOT_INT                           0x20 
#define ACCEL15_NO_MOT_INT                            0x40 
#define ACCEL15_ERROR_INT                             0x80

/**
 * @brief Accel 15 Int1 IO ctrl macros.
 * @details Specified setting for INT1 IO ctrl macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_INT1_IO_CTRL_INPUT_EN                 0x10
#define ACCEL15_INT1_IO_CTRL_OUTPUT_EN                0x08
#define ACCEL15_INT1_IO_CTRL_OD_EN                    0x04
#define ACCEL15_INT1_IO_CTRL_LVL_HIGH                 0x02
#define ACCEL15_INT1_IO_CTRL_EDGE_EN                  0x01

/**
 * @brief Accel 15 INT map data macros.
 * @details Specified setting for INT map data macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_INT_MAP_DATA_INT2_DRDY                0x40
#define ACCEL15_INT_MAP_DATA_INT2_FWM                 0x20
#define ACCEL15_INT_MAP_DATA_INT2_FFULL               0x10
#define ACCEL15_INT_MAP_DATA_INT1_DRDY                0x04
#define ACCEL15_INT_MAP_DATA_INT1_FWM                 0x02
#define ACCEL15_INT_MAP_DATA_INT1_FFULL               0x01

/**
 * @brief Accel 15 Accel config macros.
 * @details Specified setting for Accel config macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_

/**
 * @brief Accel 15 power ctrl macros.
 * @details Specified setting for power ctrl macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_OFF                             0x00
#define ACCEL15_ACCEL_ON                              0x04 
#define ACCEL15_AUX_OFF                               0x00
#define ACCEL15_AUX_ON                                0x01

/**
 * @brief Accel 15 power mode macros.
 * @details Specified setting for power mode macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_APS_OFF                               0x00
#define ACCEL15_APS_ON                                0x01 
#define ACCEL15_FSW_OFF                               0x00
#define ACCEL15_FSW_ON                                0x02

/**
 * @brief Accel 15 Bit position for major configuration.
 * @details Specified setting for bit position for major configuration
 * of Accel 15 Click driver.
 */
#define ACCEL15_CONFIG_MAJOR_POS                      0x06 

/**
 * @brief Accel 15 Accel enable and data ready macros.
 * @details Specified setting for accel enable and data ready macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_DRDY                                  0x01 
#define ACCEL15_ACCEL_EN                              0x40 
#define ACCEL15_ACCEL_DRDY                            0x80 

/**
 * @brief Accel 15 Interface selection macro.
 * @details Specified setting for interface selection macro
 * of Accel 15 Click driver.
 */
#define ACCEL15_SPI_WR_MASK                           0x7F 
#define ACCEL15_SPI_RD_MASK                           0x80 

/**
 * @brief Accel 15 enable/disable bit values.
 * @details Specified setting for enable/disable bit values
 * of Accel 15 Click driver.
 */
#define ACCEL15_ENABLE                                0x01 
#define ACCEL15_DISABLE                               0x00 

/**
 * @brief Accel 15 accel performance mode parameter.
 * @details Specified setting for enable/disable bit values
 * of Accel 15 Click driver.
 */
#define ACCEL15_CIC_AVG_MODE                          0 
#define ACCEL15_CONTINUOUS_MODE                       1 

/**
 * @brief Accel 15 advance power save position and mask.
 * @details Specified setting for advance power save position and mask
 * of Accel 15 Click driver.
 */
#define ACCEL15_ADVANCE_POWER_SAVE_MSK                0x01 

/**
 * @brief Accel 15 sensor resolution.
 * @details Specified setting for sensor resolution
 * of Accel 15 Click driver.
 */
#define ACCEL15_12_BIT_RESOLUTION                     12 
#define ACCEL15_16_BIT_RESOLUTION                     16 

/**
 * @brief Accel 15 accelerometer enable position and mask.
 * @details Specified setting for accelerometer enable position and mask
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_ENABLE_POS                      2 
#define ACCEL15_ACCEL_ENABLE_MSK                      0x04

/**
 * @brief Accel 15 soft reset.
 * @details Specified setting for soft reset
 * of Accel 15 Click driver.
 */
#define ACCEL15_SOFT_RESET                            0x6B 

/**
 * @brief Accel 15 accel configuration position and mask.
 * @details Specified setting for accel configuration position and mask
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_ODR_MSK                         0x0F 
#define ACCEL15_ACCEL_BW_POS                          4 
#define ACCEL15_ACCEL_BW_MSK                          0x70 
#define ACCEL15_ACCEL_RANGE_MSK                       0x03 
#define ACCEL15_ACCEL_PERFMODE_POS                    7 
#define ACCEL15_ACCEL_PERFMODE_MSK                    0x80 

/**
 * @brief Accel 15 constants.
 * @details Specified setting for constants
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_CONFIG_LENGTH                   2 
#define ACCEL15_FIFO_CONFIG_LENGTH                    2 
#define ACCEL15_FIFO_WM_LENGTH                        2 
#define ACCEL15_ACCEL_DATA_LENGTH                     6 
#define ACCEL15_FIFO_DATA_LENGTH                      2 
#define ACCEL15_MA_FIFO_A_X_LSB                       8 
#define ACCEL15_SENSOR_TIME_MSB_BYTE                  2 
#define ACCEL15_SENSOR_TIME_XLSB_BYTE                 1 
#define ACCEL15_SENSOR_TIME_LSB_BYTE                  0 
#define ACCEL15_FIFO_LENGTH_MSB_BYTE                  1 

/**
 * @brief Accel 15 accel ODR.
 * @details Specified setting for accel ODR
 * of Accel 15 Click driver.
 */
#define ACCEL15_OUTPUT_DATA_RATE_12_5HZ               0x05 
#define ACCEL15_OUTPUT_DATA_RATE_25HZ                 0x06 
#define ACCEL15_OUTPUT_DATA_RATE_50HZ                 0x07 
#define ACCEL15_OUTPUT_DATA_RATE_100HZ                0x08 
#define ACCEL15_OUTPUT_DATA_RATE_200HZ                0x09 
#define ACCEL15_OUTPUT_DATA_RATE_400HZ                0x0A 
#define ACCEL15_OUTPUT_DATA_RATE_800HZ                0x0B 
#define ACCEL15_OUTPUT_DATA_RATE_1600HZ               0x0C 

/**
 * @brief Accel 15 accel bandwidth parameter.
 * @details Specified setting for accel bandwidth parameter
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_OSR4_AVG1                       0 
#define ACCEL15_ACCEL_OSR2_AVG2                       1 
#define ACCEL15_ACCEL_NORMAL_AVG4                     2 
#define ACCEL15_ACCEL_CIC_AVG8                        3 
#define ACCEL15_ACCEL_RES_AVG16                       4 
#define ACCEL15_ACCEL_RES_AVG32                       5 
#define ACCEL15_ACCEL_RES_AVG64                       6 
#define ACCEL15_ACCEL_RES_AVG128                      7 

/**
 * @brief Accel 15 accel range check.
 * @details Specified setting for accel range check
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_RANGE_16G                       0 
#define ACCEL15_ACCEL_RANGE_8G                        1 
#define ACCEL15_ACCEL_RANGE_4G                        2 
#define ACCEL15_ACCEL_RANGE_2G                        3 

/**
 * @brief Accel 15 error status position and mask.
 * @details Specified setting for error status position and mask
 * of Accel 15 Click driver.
 */
#define ACCEL15_FATAL_ERR_MSK                         0x01 
#define ACCEL15_CMD_ERR_POS                           1 
#define ACCEL15_CMD_ERR_MSK                           0x02 
#define ACCEL15_ERR_CODE_POS                          2 
#define ACCEL15_ERR_CODE_MSK                          0x1C 
#define ACCEL15_FIFO_ERR_POS                          6 
#define ACCEL15_FIFO_ERR_MSK                          0x40 

/**
 * @brief Accel 15 fifo self wake up position and mask.
 * @details Specified setting for fifo
 * of Accel 15 Click driver.
 */
#define ACCEL15_FIFO_SELF_WAKE_UP_POS                 1 
#define ACCEL15_FIFO_SELF_WAKE_UP_MSK                 0x02 
#define ACCEL15_FIFO_BYTE_COUNTER_MSB_MSK             0x3F 
#define ACCEL15_FIFO_DATA_POS                         0 
#define ACCEL15_FIFO_DATA_MSK                         0xFF 
#define ACCEL15_FIFO_DOWN_ACCEL_POS                   4 
#define ACCEL15_FIFO_DOWN_ACCEL_MSK                   0x70 
#define ACCEL15_FIFO_FILTER_ACCEL_POS                 7 
#define ACCEL15_FIFO_FILTER_ACCEL_MSK                 0x80 

/**
 * @brief Accel 15 fifo header data definitions.
 * @details Specified setting for fifo header data definitions
 * of Accel 15 Click driver.
 */
#define ACCEL15_FIFO_HEADER_ACC                       0x84 
#define ACCEL15_FIFO_HEADER_MAG                       0x90 
#define ACCEL15_FIFO_HEADER_MAG_ACC                   0x94 
#define ACCEL15_FIFO_HEADER_SENSOR_TIME               0x44 
#define ACCEL15_FIFO_HEADER_INPUT_CONFIG              0x48 
#define ACCEL15_FIFO_HEADER_SKIP_FRAME                0x40 
#define ACCEL15_FIFO_HEADER_OVER_READ_MSB             0x80 
#define ACCEL15_FIFO_HEADER_SAMPLE_DROP               0x50 
#define ACCEL15_FIFO_MAG_ACC_ENABLE                   0x60 
#define ACCEL15_FIFO_ACC_ENABLE                       0x40 
#define ACCEL15_FIFO_MAG_ENABLE                       0x20 
#define ACCEL15_FIFO_STOP_ON_FULL                     0x01 
#define ACCEL15_FIFO_TIME                             0x02 
#define ACCEL15_FIFO_TAG_INTR2                        0x04 
#define ACCEL15_FIFO_TAG_INTR1                        0x08 
#define ACCEL15_FIFO_HEADER                           0x10 
#define ACCEL15_FIFO_MAG                              0x20 
#define ACCEL15_FIFO_ACCEL                            0x40 
#define ACCEL15_FIFO_ALL                              0x7F 
#define ACCEL15_FIFO_CONFIG_0_MASK                    0x03 
#define ACCEL15_FIFO_CONFIG_1_MASK                    0xFC 

/**
 * @brief Accel 15 fifo frame count definition.
 * @details Specified setting for fifo frame count definition
 * of Accel 15 Click driver.
 */
#define ACCEL15_FIFO_LSB_CONFIG_CHECK                 0x00 
#define ACCEL15_FIFO_MSB_CONFIG_CHECK                 0x80 
#define ACCEL15_FIFO_TAG_INTR_MASK                    0xFC 

/**
 * @brief Accel 15 fifo dropped frame definition.
 * @details Specified setting for fifo dropped frame definition
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_AUX_FIFO_DROP                   0x05 
#define ACCEL15_ACCEL_FIFO_DROP                       0x01

/**
 * @brief Accel 15 initialization.
 * @details Specified setting for initialization
 * of Accel 15 Click driver.
 */
#define ACCEL15_INIT_START                            0x00 
#define ACCEL15_INIT_STOP                             0x01 

/**
 * @brief Accel 15 fifo sensor time length definitions.
 * @details Specified setting for fifo sensor time length definitions
 * of Accel 15 Click driver.
 */
#define ACCEL15_SENSOR_TIME_LENGTH                    3 

/**
 * @brief Accel 15 fifo length definition.
 * @details Specified setting for fifo length definition
 * of Accel 15 Click driver.
 */
#define ACCEL15_FIFO_ACC_LENGTH                       6 
#define ACCEL15_FIFO_MAG_LENGTH                       8 
#define ACCEL15_FIFO_MAG_ACC_LENGTH                   14 
#define ACCEL15_CONFIG_STREAM_MESSAGE_MSK             0x0F 
#define ACCEL15_ASIC_INITIALIZED                      0x01 

/**
 * @brief Accel 15 foc related macros.
 * @details Specified setting for foc related macros
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_CONFIG_FOC                      0xB7 

/**
 * @brief Accel 15 enable/disable selections.
 * @details Specified setting for enable/disable selections
 * of Accel 15 Click driver.
 */
#define ACCEL15_X_AXIS                                0 
#define ACCEL15_Y_AXIS                                1 
#define ACCEL15_Z_AXIS                                2 

/**
 * @brief Accel 15 NV_CONFIG position and mask.
 * @details Specified setting for NV_CONFIG position and mask
 * of Accel 15 Click driver.
 */
#define ACCEL15_NV_ENABLE_I2C                         0x00 
#define ACCEL15_NV_DISABLE_I2C                        0x01 
#define ACCEL15_NV_ACCEL_OFFSET_POS                   3 
#define ACCEL15_NV_ACCEL_OFFSET_MSK                   0x08 

/**
 * @brief Accel 15 self-test.
 * @details Specified setting for self-test
 * of Accel 15 Click driver.
 */
#define ACCEL15_SELFTEST_PASS                         0 
#define ACCEL15_SELFTEST_FAIL                         1 
#define ACCEL15_SELFTEST_DIFF_X_AXIS_FAILED           1 
#define ACCEL15_SELFTEST_DIFF_Y_AXIS_FAILED           2 
#define ACCEL15_SELFTEST_DIFF_Z_AXIS_FAILED           3 
#define ACCEL15_SELFTEST_DIFF_X_AND_Y_AXIS_FAILED     4 
#define ACCEL15_SELFTEST_DIFF_X_AND_Z_AXIS_FAILED     5 
#define ACCEL15_SELFTEST_DIFF_Y_AND_Z_AXIS_FAILED     6 
#define ACCEL15_SELFTEST_DIFF_X_Y_AND_Z_AXIS_FAILED   7 

/**
 * @brief Accel 15 self-test position and mask.
 * @details Specified setting for self-test position and mask
 * of Accel 15 Click driver.
 */
#define ACCEL15_ACCEL_SELFTEST_ENABLE_MSK             0x01 
#define ACCEL15_ACCEL_SELFTEST_SIGN_POS               2 
#define ACCEL15_ACCEL_SELFTEST_SIGN_MSK               0x04 
#define ACCEL15_SELFTEST_AMP_POS                      3 
#define ACCEL15_SELFTEST_AMP_MSK                      0x08 

/**
 * @brief Accel 15 condition check for reading and wrting data.
 * @details Specified setting for condition check for reading and wrting data
 * of Accel 15 Click driver.
 */
#define ACCEL15_MAX_VALUE_FIFO_FILTER                 1 
#define ACCEL15_MAX_VALUE_SPI3                        1 
#define ACCEL15_MAX_VALUE_SELFTEST_AMP                1 
#define ACCEL15_MAX_IF_MODE                           3 
#define ACCEL15_MAX_VALUE_SELFTEST_SIGN               1 

/**
 * @brief Accel 15 Macro to define accelerometer configuration value for FOC.
 * @details Specified setting for Macro to define accelerometer configuration value for FOC
 * of Accel 15 Click driver.
 */
#define ACCEL15_FOC_ACC_CONF_VAL                      0xB7

/**
 * @brief Accel 15 SPI write/read command.
 * @details Specified setting for SPI write/read command
 * of Accel 15 Click driver.
 */
#define ACCEL15_SPI_WRITE                            0x00
#define ACCEL15_SPI_READ                             0x80

/**
 * @brief Accel 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 15 Click driver.
 */
#define ACCEL15_SET_DEV_ADDR_GND                     0x18
#define ACCEL15_SET_DEV_ADDR_VCC                     0x19

/*! @} */ // accel15_set

/**
 * @defgroup accel15_map Accel 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 15 Click driver.
 */

/**
 * @addtogroup accel15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 15 Click to the selected MikroBUS.
 */
#define ACCEL15_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel15_map
/*! @} */ // accel15

/**
 * @brief Accel 15 Click driver selector.
 * @details Selects target driver interface of Accel 15 Click driver.
 */
typedef enum
{
    ACCEL15_DRV_SEL_SPI,        /**< SPI driver descriptor. */
    ACCEL15_DRV_SEL_I2C         /**< I2C driver descriptor. */

} accel15_drv_t;

/**
 * @brief Accel 15 Click driver interface.
 * @details Definition of driver interface of Accel 15 Click driver.
 */
typedef err_t ( *accel15_master_io_t )( struct accel15_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 15 Click context object.
 * @details Context object definition of Accel 15 Click driver.
 */
typedef struct accel15_s
{
    digital_in_t in2;                   /**< Interrupt output 2. */
    digital_in_t in1;                   /**< Interrupt output 1. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t     slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    accel15_drv_t  drv_sel;             /**< Master driver interface selector. */

    accel15_master_io_t  write_f;       /**< Master write function. */
    accel15_master_io_t  read_f;        /**< Master read function. */

} accel15_t;

/**
 * @brief Accel 15 Click configuration object.
 * @details Configuration object definition of Accel 15 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  in2;        /**< Interrupt output 2. */
    pin_name_t  in1;        /**< Interrupt output 1. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    accel15_drv_t  drv_sel;     /**< Master driver interface selector. */

} accel15_cfg_t;

/**
 * @brief Accel axis data structure.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel15_axis_t;

/**
 * @brief Accel 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL15_OK = 0,
    ACCEL15_ERROR = -1

} accel15_return_value_t;

/*!
 * @addtogroup accel15 Accel 15 Click Driver
 * @brief API for configuring and manipulating Accel 15 Click driver.
 * @{
 */

/**
 * @brief Accel 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel15_cfg_setup ( accel15_cfg_t *cfg );

/**
 * @brief Accel 15 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel15_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel15_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel15_drv_interface_selection ( accel15_cfg_t *cfg, accel15_drv_t drv_sel );

/**
 * @brief Accel 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel15_init ( accel15_t *ctx, accel15_cfg_t *cfg );

/**
 * @brief Accel 15 default configuration function.
 * @details This function executes a default configuration of Accel 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel15_default_cfg ( accel15_t *ctx );

/**
 * @brief Accel 15 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel15_generic_write ( accel15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 15 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel15_generic_read ( accel15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 15 soft reset function.
 * @details This function executes a software reset 
 * of the BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void accel15_soft_reset ( accel15_t *ctx );

/**
 * @brief Accel 15 check ID function.
 * @details This function check ID and communication of the
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return @li @c  0 - Communication OK,
 *         @li @c -1 - Communication Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel15_check_id ( accel15_t *ctx );

/**
 * @brief Accel 15 get error function.
 * @details This function get internal error flags of the
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return Internal error flags.
 *
 * @note None.
 */
uint8_t accel15_get_error ( accel15_t *ctx );

/**
 * @brief Accel 15 status function.
 * @details This function get sensor status flags of the
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return Sensor status flags.
 *
 * @note None.
 */
uint8_t accel15_get_status ( accel15_t *ctx );

/**
 * @brief Accel 15 enable accel function.
 * @details This function enable accelerometer data of the
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void accel15_enable_accel ( accel15_t *ctx );

/**
 * @brief Accel 15 config accel function.
 * @details This function executes a configuration of the accelerometer data 
 * of the BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @param[in] acc_odr : 
 *            @li @c 0x05 - odr_12p5, 25/2.
 *            @li @c 0x06 - odr_25, 25.
 *            @li @c 0x07 - odr_50, 50.
 *            @li @c 0x08 - odr_100, 100.
 *            @li @c 0x09 - odr_200, 200.
 *            @li @c 0x0a - odr_400, 400.
 *            @li @c 0x0b - odr_800, 800.
 *            @li @c 0x0c - odr_1k6, 1600.
 * @param[in] g_range : 
 *            @li @c 0x00 - range_16g, +/-16g.
 *            @li @c 0x01 - range_8g, +/-8g.
 *            @li @c 0x02 - range_4g, +/-4g.
 *            @li @c 0x03 - range_2g, +/-2g.
 * @return Nothing.
 *
 * @note None.
 */
void accel15_cfg_accel ( accel15_t *ctx, uint8_t acc_odr, uint8_t g_range );

/**
 * @brief Accel 15 internal status function.
 * @details This function get internal status message of the
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return Internal status message.
 *
 * @note None.
 */
uint8_t accel15_get_internal_status ( accel15_t *ctx );

/**
 * @brief Accel 15 get accelerometer axis function.
 * @details This function get accelerometer data of the
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @param[in] axis : An object that contains X , Y and Z axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
err_t accel15_get_axis_data ( accel15_t *ctx, accel15_axis_t *axis );

/**
 * @brief Accel 15 get Interrupt 1 function.
 * @details This function get states of the Interrupt 1 ( INT pin )
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 *
 * @note None.
 */
uint8_t accel15_get_int_1 ( accel15_t *ctx );

/**
 * @brief Accel 15 get Interrupt 1 function.
 * @details This function get states of the Interrupt 2 ( AN pin )
 * BMA490L High-performance longevity acceleration sensor
 * on the Accel 15 click board.
 * @param[in] ctx : Click context object.
 * See #accel15_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 *
 * @note None.
 */
uint8_t accel15_get_int_2 ( accel15_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL15_H

/*! @} */ // accel15

// ------------------------------------------------------------------------ END

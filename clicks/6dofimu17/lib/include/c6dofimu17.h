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
 * @file c6dofimu17.h
 * @brief This file contains API for 6DOF IMU 17 Click Driver.
 */

#ifndef C6DOFIMU17_H
#define C6DOFIMU17_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
        

/*!
 * @addtogroup c6dofimu17 6DOF IMU 17 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 17 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu17_reg 6DOF IMU 17 Registers List
 * @brief List of registers of 6DOF IMU 17 Click driver.
 */

/**
 * @addtogroup c6dofimu17_reg
 * @{
 */

/**
 * @brief 6DOF IMU 17 description user bank 0 register.
 * @details Specified user bank 0 register for description of 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_REG_DEVICE_CONFIG                       0x11
#define C6DOFIMU17_REG_DRIVE_CONFIG                        0x13 
#define C6DOFIMU17_REG_INT_CONFIG                          0x14
#define C6DOFIMU17_REG_FIFO_CONFIG                         0x16
#define C6DOFIMU17_REG_TEMP_DATA1_UI                       0x1D 
#define C6DOFIMU17_REG_TEMP_DATA0_UI                       0x1E
#define C6DOFIMU17_REG_ACCEL_DATA_X1_UI                    0x1F
#define C6DOFIMU17_REG_ACCEL_DATA_X0_UI                    0x20
#define C6DOFIMU17_REG_ACCEL_DATA_Y1_UI                    0x21
#define C6DOFIMU17_REG_ACCEL_DATA_Y0_UI                    0x22
#define C6DOFIMU17_REG_ACCEL_DATA_Z1_UI                    0x23
#define C6DOFIMU17_REG_ACCEL_DATA_Z0_UI                    0x24
#define C6DOFIMU17_REG_GYRO_DATA_X1_UI                     0x25
#define C6DOFIMU17_REG_GYRO_DATA_X0_UI                     0x26
#define C6DOFIMU17_REG_GYRO_DATA_Y1_UI                     0x27
#define C6DOFIMU17_REG_GYRO_DATA_Y0_UI                     0x28
#define C6DOFIMU17_REG_GYRO_DATA_Z1_UI                     0x29
#define C6DOFIMU17_REG_GYRO_DATA_Z0_UI                     0x2A
#define C6DOFIMU17_REG_TMST_FSYNCH                         0x2B
#define C6DOFIMU17_REG_TMST_FSYNCL                         0x2C
#define C6DOFIMU17_REG_INT_STATUS                          0x2D
#define C6DOFIMU17_REG_FIFO_COUNTH                         0x2E
#define C6DOFIMU17_REG_FIFO_COUNTL                         0x2F
#define C6DOFIMU17_REG_FIFO_DATA                           0x30
#define C6DOFIMU17_REG_APEX_DATA0                          0x31
#define C6DOFIMU17_REG_APEX_DATA1                          0x32
#define C6DOFIMU17_REG_APEX_DATA2                          0x33
#define C6DOFIMU17_REG_APEX_DATA3                          0x34
#define C6DOFIMU17_REG_APEX_DATA4                          0x35
#define C6DOFIMU17_REG_APEX_DATA5                          0x36
#define C6DOFIMU17_REG_INT_STATUS2                         0x37
#define C6DOFIMU17_REG_INT_STATUS3                         0x38
#define C6DOFIMU17_REG_SIGNAL_PATH_RESET                   0x4B
#define C6DOFIMU17_REG_INTF_CONFIG0                        0x4C
#define C6DOFIMU17_REG_INTF_CONFIG1                        0x4D
#define C6DOFIMU17_REG_PWR_MGMT0                           0x4E
#define C6DOFIMU17_REG_GYRO_CONFIG0                        0x4F
#define C6DOFIMU17_REG_ACCEL_CONFIG0                       0x50
#define C6DOFIMU17_REG_GYRO_CONFIG1                        0x51
#define C6DOFIMU17_REG_GYRO_ACCEL_CONFIG0                  0x52
#define C6DOFIMU17_REG_ACCEL_CONFIG1                       0x53
#define C6DOFIMU17_REG_TMST_CONFIG                         0x54
#define C6DOFIMU17_REG_APEX_CONFIG0                        0x55
#define C6DOFIMU17_REG_SMD_CONFIG                          0x56
#define C6DOFIMU17_REG_FIFO_CONFIG1                        0x5F
#define C6DOFIMU17_REG_FIFO_CONFIG2                        0x60
#define C6DOFIMU17_REG_FIFO_CONFIG3                        0x61
#define C6DOFIMU17_REG_FSYNC_CONFIG                        0x62
#define C6DOFIMU17_REG_INT_CONFIG0                         0x63
#define C6DOFIMU17_REG_INT_CONFIG1                         0x64
#define C6DOFIMU17_REG_INT_SOURCE0                         0x65
#define C6DOFIMU17_REG_INT_SOURCE1                         0x66
#define C6DOFIMU17_REG_INT_SOURCE3                         0x68
#define C6DOFIMU17_REG_INT_SOURCE4                         0x69
#define C6DOFIMU17_REG_FIFO_LOST_PKT0                      0x6C
#define C6DOFIMU17_REG_FIFO_LOST_PKT1                      0x6D
#define C6DOFIMU17_REG_SELF_TEST_CONFIG                    0x70
#define C6DOFIMU17_REG_WHO_AM_I                            0x75
#define C6DOFIMU17_REG_BANK_SEL                            0x76
#define C6DOFIMU17_CHIP_ID                                 0x6F

/**
 * @brief 6DOF IMU 17 description user bank 1 register.
 * @details Specified user bank 1 registerfor description of 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_REG_SENSOR_CONFIG0                      0x03
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC2                 0x0B
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC3                 0x0C
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC4                 0x0D
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC5                 0x0E
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC6                 0x0F
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC7                 0x10
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC8                 0x11
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC9                 0x12
#define C6DOFIMU17_REG_GYRO_CONFIG_STATIC10                0x13
#define C6DOFIMU17_REG_XG_ST_DATA                          0x5F
#define C6DOFIMU17_REG_YG_ST_DATA                          0x60
#define C6DOFIMU17_REG_ZG_ST_DATA                          0x61
#define C6DOFIMU17_REG_TMSTVAL0                            0x62
#define C6DOFIMU17_REG_TMSTVAL1                            0x63
#define C6DOFIMU17_REG_TMSTVAL2                            0x64
#define C6DOFIMU17_REG_INTF_CONFIG4                        0x7A
#define C6DOFIMU17_REG_INTF_CONFIG5                        0x7B
#define C6DOFIMU17_REG_INTF_CONFIG6                        0x7C
    
/**
 * @brief 6DOF IMU 17 description user bank 2 register.
 * @details Specified user bank 2 register for description of 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_REG_ACCEL_CONFIG_STATIC2                0x03
#define C6DOFIMU17_REG_ACCEL_CONFIG_STATIC3                0x04
#define C6DOFIMU17_REG_ACCEL_CONFIG_STATIC4                0x05
#define C6DOFIMU17_REG_XA_ST_DATA                          0x3B
#define C6DOFIMU17_REG_YA_ST_DATA                          0x3C
#define C6DOFIMU17_REG_ZA_ST_DATA                          0x3D
    
/**
 * @brief 6DOF IMU 17 description user bank 3 register.
 * @details Specified user bank 3 register for description of 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_REG_PU_PD_CONFIG1                       0x06
#define C6DOFIMU17_REG_PU_PD_CONFIG2                       0x0E

/**
 * @brief 6DOF IMU 17 description user bank 4 register.
 * @details Specified user bank 4 register for description of 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_REG_FDR_CONFIG                          0x09
#define C6DOFIMU17_REG_APEX_CONFIG1                        0x40
#define C6DOFIMU17_REG_APEX_CONFIG2                        0x41
#define C6DOFIMU17_REG_APEX_CONFIG3                        0x42
#define C6DOFIMU17_REG_APEX_CONFIG4                        0x43
#define C6DOFIMU17_REG_APEX_CONFIG5                        0x44
#define C6DOFIMU17_REG_APEX_CONFIG6                        0x45
#define C6DOFIMU17_REG_APEX_CONFIG7                        0x46
#define C6DOFIMU17_REG_APEX_CONFIG8                        0x47
#define C6DOFIMU17_REG_APEX_CONFIG9                        0x48
#define C6DOFIMU17_REG_APEX_CONFIG10                       0x49
#define C6DOFIMU17_REG_ACCEL_WOM_X_THR                     0x4A
#define C6DOFIMU17_REG_ACCEL_WOM_Y_THR                     0x4B
#define C6DOFIMU17_REG_ACCEL_WOM_Z_THR                     0x4C
#define C6DOFIMU17_REG_INT_SOURCE6                         0x4D
#define C6DOFIMU17_REG_INT_SOURCE7                         0x4E
#define C6DOFIMU17_REG_INT_SOURCE8                         0x4F
#define C6DOFIMU17_REG_INT_SOURCE9                         0x50
#define C6DOFIMU17_REG_INT_SOURCE10                        0x51
#define C6DOFIMU17_REG_OFFSET_USER0                        0x77
#define C6DOFIMU17_REG_OFFSET_USER1                        0x78
#define C6DOFIMU17_REG_OFFSET_USER2                        0x79
#define C6DOFIMU17_REG_OFFSET_USER3                        0x7A
#define C6DOFIMU17_REG_OFFSET_USER4                        0x7B
#define C6DOFIMU17_REG_OFFSET_USER5                        0x7C
#define C6DOFIMU17_REG_OFFSET_USER6                        0x7D
#define C6DOFIMU17_REG_OFFSET_USER7                        0x7E
#define C6DOFIMU17_REG_OFFSET_USER8                        0x7F 

/*! @} */ // c6dofimu17_reg

/**
 * @defgroup c6dofimu17_set 6DOF IMU 17 Registers Settings
 * @brief Settings for registers of 6DOF IMU 17 Click driver.
 */

/**
 * @addtogroup c6dofimu17_set
 * @{
 */

/**
 * @brief 6DOF IMU 17 description setting.
 * @details Specified setting for description of 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_SET_TEMPERATURE_ENABLED                 0xDF
#define C6DOFIMU17_SET_TEMPERATURE_DISABLED                0x20
    
#define C6DOFIMU17_SET_GYRO_OFF_MODE                       0x00
#define C6DOFIMU17_SET_GYRO_STANDBY_MODE                   0x04
#define C6DOFIMU17_SET_GYRO_TLOW_NOISE_MODE                0x0C
    
#define C6DOFIMU17_SET_ACCEL_OFF_MODE                      0x00
#define C6DOFIMU17_SET_ACCEL_LOW_POWER_MODE                0x02
#define C6DOFIMU17_SET_ACCEL_LOW_NOISE_MODE                0x03
    
#define C6DOFIMU17_SET_GYRO_FS_SEL_2000_dps                0x00
#define C6DOFIMU17_SET_GYRO_FS_SEL_1000_dps                0x01
#define C6DOFIMU17_SET_GYRO_FS_SEL_500_dps                 0x02
#define C6DOFIMU17_SET_GYRO_FS_SEL_250_dps                 0x03
#define C6DOFIMU17_SET_GYRO_FS_SEL_125_dps                 0x04
#define C6DOFIMU17_SET_GYRO_FS_SEL_62_5_dps                0x05
#define C6DOFIMU17_SET_GYRO_FS_SEL_31_25_dps               0x06
#define C6DOFIMU17_SET_GYRO_FS_SEL_16_625_dps              0x07
    
#define C6DOFIMU17_SET_GYRO_ODR_32kHz                      0x01
#define C6DOFIMU17_SET_GYRO_ODR_16kHz                      0x02
#define C6DOFIMU17_SET_GYRO_ODR_8kHz                       0x03
#define C6DOFIMU17_SET_GYRO_ODR_4kHz                       0x04
#define C6DOFIMU17_SET_GYRO_ODR_2kHz                       0x05
#define C6DOFIMU17_SET_GYRO_ODR_1kHz                       0x06
#define C6DOFIMU17_SET_GYRO_ODR_200Hz                      0x07
#define C6DOFIMU17_SET_GYRO_ODR_100Hz                      0x08
#define C6DOFIMU17_SET_GYRO_ODR_50Hz                       0x09
#define C6DOFIMU17_SET_GYRO_ODR_25Hz                       0x0A
#define C6DOFIMU17_SET_GYRO_ODR_12_5Hz                     0x0B
    
#define C6DOFIMU17_SET_GYRO_UI_FILT_ORD_1st                0x00
#define C6DOFIMU17_SET_GYRO_UI_FILT_ORD_2st                0x01
#define C6DOFIMU17_SET_GYRO_UI_FILT_ORD_3st                0x02
    
#define C6DOFIMU17_SET_GYRO_DEC2_M2_ORD_3st                0x02
    
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_2               0x00
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_4               0x01
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_5               0x02
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_8               0x03
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_10              0x04
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_16              0x05
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_20              0x06
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_ODR_40              0x07
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_LOW_LATENCY_0       0x0E
#define C6DOFIMU17_SET_GYRO_UI_FILT_BW_LOW_LATENCY_1       0x0F
    
#define C6DOFIMU17_SET_ACCEL_FS_SEL_16g                    0x00
#define C6DOFIMU17_SET_ACCEL_FS_SEL_8g                     0x01
#define C6DOFIMU17_SET_ACCEL_FS_SEL_4g                     0x02
#define C6DOFIMU17_SET_ACCEL_FS_SEL_2g                     0x03
    
#define C6DOFIMU17_SET_ACCEL_ODR_32kHz                     0x01
#define C6DOFIMU17_SET_ACCEL_ODR_16kHz                     0x02
#define C6DOFIMU17_SET_ACCEL_ODR_8kHz                      0x03
#define C6DOFIMU17_SET_ACCEL_ODR_4kHz                      0x04
#define C6DOFIMU17_SET_ACCEL_ODR_2kHz                      0x05
#define C6DOFIMU17_SET_ACCEL_ODR_1kHz                      0x06
#define C6DOFIMU17_SET_ACCEL_ODR_200Hz                     0x07
#define C6DOFIMU17_SET_ACCEL_ODR_100Hz                     0x08
#define C6DOFIMU17_SET_ACCEL_ODR_50Hz                      0x09
#define C6DOFIMU17_SET_ACCEL_ODR_25Hz                      0x0A
#define C6DOFIMU17_SET_ACCEL_ODR_12_5Hz                    0x0B
    
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_2              0x00
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_4              0x01
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_5              0x02
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_8              0x03
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_10             0x04
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_16             0x05
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_20             0x06
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_ODR_40             0x07
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_LOW_LATENCY_0      0x0E
#define C6DOFIMU17_SET_ACCEL_UI_FILT_BW_LOW_LATENCY_1      0x0F
    
#define C6DOFIMU17_SET_ACCEL_UI_FILT_ORD_1st               0x00
#define C6DOFIMU17_SET_ACCEL_UI_FILT_ORD_2st               0x01
#define C6DOFIMU17_SET_ACCEL_UI_FILT_ORD_3st               0x02
    
#define C6DOFIMU17_SET_ACCEL_DEC2_M2_ORD_3st               0x02

#define C6DOFIMU17_SET_BANK_0                              0x00
#define C6DOFIMU17_SET_BANK_1                              0x01
#define C6DOFIMU17_SET_BANK_2                              0x02
#define C6DOFIMU17_SET_BANK_3                              0x03
#define C6DOFIMU17_SET_BANK_4                              0x04

/**
 * @brief 6DOF IMU 17 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 17 Click driver.
 */
#define C6DOFIMU17_SET_DEV_ADDR                            0x68

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu17_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU17_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU17_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu17_set

/**
 * @defgroup c6dofimu17_map 6DOF IMU 17 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 17 Click driver.
 */

/**
 * @addtogroup c6dofimu17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 17 Click to the selected MikroBUS.
 */
#define C6DOFIMU17_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu17_map
/*! @} */ // c6dofimu17

/**
 * @brief 6DOF IMU 17 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 17 Click driver.
 */
typedef enum
{
   C6DOFIMU17_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   C6DOFIMU17_DRV_SEL_I2C       /**< I2C driver descriptor. */

} c6dofimu17_drv_t;

/**
 * @brief 6DOF IMU 17 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 17 Click driver.
 */
typedef err_t ( *c6dofimu17_master_io_t )( struct c6dofimu17_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 17 Click context object.
 * @details Context object definition of 6DOF IMU 17 Click driver.
 */
typedef struct c6dofimu17_s
{
    digital_in_t  int_pin;             /**< Interrupt pin. */

    i2c_master_t  i2c;                 /**< I2C driver object. */
    spi_master_t  spi;                 /**< SPI driver object. */

    uint8_t     slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu17_drv_t  drv_sel;         /**< Master driver interface selector. */

    c6dofimu17_master_io_t  write_f;   /**< Master write function. */
    c6dofimu17_master_io_t  read_f;    /**< Master read function. */

} c6dofimu17_t;

/**
 * @brief 6DOF IMU 17 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

   c6dofimu17_drv_t  drv_sel;                           /**< Master driver interface selector. */

} c6dofimu17_cfg_t;

/**
 * @brief 6DOF IMU 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   C6DOFIMU17_OK = 0,
   C6DOFIMU17_ERROR = -1

} c6dofimu17_return_value_t;

/**
 * @brief 6DOF IMU 17 Axis structure object.
 * @details Axis structure object definition of 6DOF IMU 17 Click driver.
 */
typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;

} c6dofimu17_axis_t;

/**
 * @brief 6DOF IMU 17 Gyro configuration structure object.
 * @details Gyro configuration structure object definition of 6DOF IMU 17 Click driver.
 */
typedef struct 
{
    uint8_t gyro_fs_sel;
    uint8_t gyro_odr;
    uint8_t gyro_ui_filt_ord;
    uint8_t gyro_dec2_m2_ord;
    uint8_t gyro_ui_filt_bw;

} c6dofimu17_gyro_cfg_t;

/**
 * @brief 6DOF IMU 17 Accelerometer configuration structure object.
 * @details Accelerometer configuration structure object definition of 6DOF IMU 17 Click driver.
 */
typedef struct 
{
    uint8_t accel_fs_sel;
    uint8_t accel_odr;
    uint8_t accel_ui_filt_bw;
    uint8_t accel_ui_filt_ord;
    uint8_t accel_dec2_m2_ord;

} c6dofimu17_accel_cfg_t;

/*!
 * @addtogroup c6dofimu17 6DOF IMU 17 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 17 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu17_cfg_setup ( c6dofimu17_cfg_t *cfg );

/**
 * @brief 6DOF IMU 17 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu17_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu17_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu17_drv_interface_selection ( c6dofimu17_cfg_t *cfg, c6dofimu17_drv_t drv_sel );

/**
 * @brief 6DOF IMU 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_init ( c6dofimu17_t *ctx, c6dofimu17_cfg_t *cfg );

/**
 * @brief 6DOF IMU 17 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu17_default_cfg ( c6dofimu17_t *ctx );

/**
 * @brief 6DOF IMU 17 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_generic_write ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 17 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_generic_read ( c6dofimu17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 17 bank selection function.
 * @details This function accessible from all register bank 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] bank_sel : 
 *         @li @c 0 ( C6DOFIMU17_SET_BANK_0 )- Bank 0 (default),
 *         @li @c 1 ( C6DOFIMU17_SET_BANK_1 )- Bank 1,
 *         @li @c 2 ( C6DOFIMU17_SET_BANK_2 )- Bank 2,
 *         @li @c 3 ( C6DOFIMU17_SET_BANK_3 )- Bank 3,
 *         @li @c 4 ( C6DOFIMU17_SET_BANK_4 )- Bank 4.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_bank_selection ( c6dofimu17_t *ctx, uint8_t bank_sel );

/**
 * @brief 6DOF IMU 17 get interrupt function.
 * @details This function get states of the INT pin
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @return INT pin state.
 *
 * @note None.
 */
uint8_t c6dofimu17_get_interrupt ( c6dofimu17_t *ctx );

/**
 * @brief 6DOF IMU 17 get device ID function.
 * @details This function get device ID
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[out] device_id : device ID
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_get_device_id ( c6dofimu17_t *ctx, uint8_t *device_id );

/**
 * @brief 6DOF IMU 17 temperature enable function.
 * @details This function enable temperature data
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_temperature_enable ( c6dofimu17_t *ctx );

/**
 * @brief 6DOF IMU 17 gyroscope enable function.
 * @details This function enable gyroscope data
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_gyroscope_enable ( c6dofimu17_t *ctx );

/**
 * @brief 6DOF IMU 17 accelerometer enable function.
 * @details This function enable accelerometer data
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_accelerometer_enable ( c6dofimu17_t *ctx );

/**
 * @brief 6DOF IMU 17 set config gyroscope function.
 * @details This function set gyroscope configuration 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] gyro_cfg : Gyro configuration structure object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_set_config_gyroscope ( c6dofimu17_t *ctx, c6dofimu17_gyro_cfg_t gyro_cfg );

/**
 * @brief 6DOF IMU 17 get config gyroscope function.
 * @details This function get gyroscope configuration 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[out] gyro_cfg : Gyro configuration structure object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_get_config_gyroscope ( c6dofimu17_t *ctx, c6dofimu17_gyro_cfg_t *gyro_cfg );

/**
 * @brief 6DOF IMU 17 set config accelerometer function.
 * @details This function set accelerometer configuration 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[in] accel_cfg : Gyro configuration structure object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_set_config_accelerometer ( c6dofimu17_t *ctx, c6dofimu17_accel_cfg_t accel_cfg );

/**
 * @brief 6DOF IMU 17 get config accelerometer function.
 * @details This function get accelerometer configuration 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[out] accel_cfg : Gyro configuration structure object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_get_config_accelerometer ( c6dofimu17_t *ctx, c6dofimu17_accel_cfg_t *accel_cfg );

/**
 * @brief 6DOF IMU 17 soft reset function.
 * @details This function performs a software reset  
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_soft_reset ( c6dofimu17_t *ctx );

/**
 * @brief 6DOF IMU 17 get accel data function.
 * @details This function get accelerometer data 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[out] accel_data : An object that contains X , Y and Z axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_get_accel_data ( c6dofimu17_t *ctx, c6dofimu17_axis_t *accel_data );

/**
 * @brief 6DOF IMU 17 get gyroscope data function.
 * @details This function get gyroscope data 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[out] gyro_data : Gyroscope configuration structure object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_get_gyro_data ( c6dofimu17_t *ctx, c6dofimu17_axis_t *gyro_data );

/**
 * @brief 6DOF IMU 17 get temperature data function.
 * @details This function get temperature data 
 * of the IIM-42652 High-performance 6-Axis SmartIndustrial™ MotionTracking MEMS Device
 * on the 6DOF IMU 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu17_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degrees Celsius
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu17_get_temperature ( c6dofimu17_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU17_H

/*! @} */ // c6dofimu17

// ------------------------------------------------------------------------ END

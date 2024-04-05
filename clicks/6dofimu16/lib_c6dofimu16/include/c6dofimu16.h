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
 * @file c6dofimu16.h
 * @brief This file contains API for 6DOF IMU 16 Click Driver.
 */

#ifndef C6DOFIMU16_H
#define C6DOFIMU16_H

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
 * @addtogroup c6dofimu16 6DOF IMU 16 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 16 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu16_reg 6DOF IMU 16 Registers List
 * @brief List of registers of 6DOF IMU 16 Click driver.
 */

/**
 * @addtogroup c6dofimu16_reg
 * @{
 */

/**
 * @brief 6DOF IMU 16 description register.
 * @details Specified register for description of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_REG_ACCEL_DATA_X1_UI                         0x00
#define C6DOFIMU16_REG_ACCEL_DATA_X0_UI                         0x01
#define C6DOFIMU16_REG_ACCEL_DATA_Y1_UI                         0x02
#define C6DOFIMU16_REG_ACCEL_DATA_Y0_UI                         0x03
#define C6DOFIMU16_REG_ACCEL_DATA_Z1_UI                         0x04
#define C6DOFIMU16_REG_ACCEL_DATA_Z0_UI                         0x05
#define C6DOFIMU16_REG_GYRO_DATA_X1_UI                          0x06
#define C6DOFIMU16_REG_GYRO_DATA_X0_UI                          0x07
#define C6DOFIMU16_REG_GYRO_DATA_Y1_UI                          0x08
#define C6DOFIMU16_REG_GYRO_DATA_Y0_UI                          0x09
#define C6DOFIMU16_REG_GYRO_DATA_Z1_UI                          0x0A
#define C6DOFIMU16_REG_GYRO_DATA_Z0_UI                          0x0B
#define C6DOFIMU16_REG_TEMP_DATA1_UI                            0x0C
#define C6DOFIMU16_REG_TEMP_DATA0_UI                            0x0D
#define C6DOFIMU16_REG_TMST_FSYNCH                              0x0E
#define C6DOFIMU16_REG_TMST_FSYNCL                              0x0F
#define C6DOFIMU16_REG_PWR_MGMNT0                               0x10
#define C6DOFIMU16_REG_FIFO_COUNT_0                             0x12
#define C6DOFIMU16_REG_FIFO_COUNT_1                             0x13
#define C6DOFIMU16_REG_FIFO_DATA                                0x14
#define C6DOFIMU16_REG_INT1_CONFIG0                             0x16
#define C6DOFIMU16_REG_INT1_CONFIG1                             0x17
#define C6DOFIMU16_REG_INT1_CONFIG2                             0x18
#define C6DOFIMU16_REG_INT1_STATUS0                             0x19
#define C6DOFIMU16_REG_ACCEL_CONFIG0                            0x1B
#define C6DOFIMU16_REG_GYRO_CONFIG0                             0x1C
#define C6DOFIMU16_REG_FIFO_CONFIG0                             0x1D
#define C6DOFIMU16_REG_FIFO_CONFIG1_0                           0x1E
#define C6DOFIMU16_REG_FIFO_CONFIG1_1                           0x1F
#define C6DOFIMU16_REG_FIFO_CONFIG2                             0x20
#define C6DOFIMU16_REG_FIFO_CONFIG3                             0x21
#define C6DOFIMU16_REG_FIFO_CONFIG4                             0x22
#define C6DOFIMU16_REG_DMP_EXT_SEN_ODR_CFG                      0x27
#define C6DOFIMU16_REG_EDMP_APEX_EN0                            0x29
#define C6DOFIMU16_REG_EDMP_APEX_EN1                            0x2A
#define C6DOFIMU16_REG_APEX_BUFFER_MGMT                         0x2B
#define C6DOFIMU16_REG_INTF_CONFIG0                             0x2C
#define C6DOFIMU16_REG_INTF_CONFIG1_OVRD                        0x2D
#define C6DOFIMU16_REG_IOC_PAD_SCENARIO                         0x2F
#define C6DOFIMU16_REG_IOC_PAD_SCENARIO_AUX_OVRD                0x30
#define C6DOFIMU16_REG_IOC_PAD_SCENARIO_OVRD                    0x31
#define C6DOFIMU16_REG_DRIVE_CONFIG0                            0x32
#define C6DOFIMU16_REG_DRIVE_CONFIG1                            0x33
#define C6DOFIMU16_REG_DRIVE_CONFIG2                            0x34
#define C6DOFIMU16_REG_INT_APEX_CONFIG1                         0x3A
#define C6DOFIMU16_REG_INT_APEX_STATUS0                         0x3B
#define C6DOFIMU16_REG_INT_APEX_STATUS1                         0x3C
#define C6DOFIMU16_REG_INT2_CONFIG0                             0x56
#define C6DOFIMU16_REG_INT2_CONFIG1                             0x57
#define C6DOFIMU16_REG_INT2_CONFIG2                             0x58
#define C6DOFIMU16_REG_INT2_STATUS0                             0x59
#define C6DOFIMU16_REG_WHO_AM_I                                 0x72
#define C6DOFIMU16_REG_REG_HOST_MSG                             0x73
#define C6DOFIMU16_REG_IREG_ADDR_15_8                           0x7C
#define C6DOFIMU16_REG_IREG_ADDR_7_0                            0x7D
#define C6DOFIMU16_REG_IREG_DATA                                0x7E
#define C6DOFIMU16_REG_REG_MISC2                                0x7F

/*! @} */ // c6dofimu16_reg

/**
 * @defgroup c6dofimu16_set 6DOF IMU 16 Registers Settings
 * @brief Settings for registers of 6DOF IMU 16 Click driver.
 */

/**
 * @addtogroup c6dofimu16_set
 * @{
 */

/**
 * @brief 6DOF IMU 16 description setting.
 * @details Specified setting for description of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_GYRO_MODE_OFF                                0x00
#define C6DOFIMU16_GYRO_MODE_STANDBY                            0x04
#define C6DOFIMU16_GYRO_MODE_LOW_POWER                          0x08
#define C6DOFIMU16_GYRO_MODE_LOW_NOISE                          0x0C
#define C6DOFIMU16_ACCEL_MODE_OFF                               0x00
#define C6DOFIMU16_ACCEL_MODE_STANDBY                           0x01
#define C6DOFIMU16_ACCEL_MODE_LOW_POWER                         0x02
#define C6DOFIMU16_ACCEL_MODE_LOW_NOISE                         0x03

/**
 * @brief 6DOF IMU 16 gyro full-scale setting.
 * @details Specified setting for gyro full-scale of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_GYRO_UI_FS_SEL_MASK                          0xF0
#define C6DOFIMU16_GYRO_UI_FS_SEL_2000DPS                       0x10
#define C6DOFIMU16_GYRO_UI_FS_SEL_1000DPS                       0x20
#define C6DOFIMU16_GYRO_UI_FS_SEL_500DPS                        0x30
#define C6DOFIMU16_GYRO_UI_FS_SEL_250DPS                        0x40
#define C6DOFIMU16_GYRO_UI_FS_SEL_125DPS                        0x50
#define C6DOFIMU16_GYRO_UI_FS_SEL_62_5DPS                       0x60
#define C6DOFIMU16_GYRO_UI_FS_SEL_31_25DPS                      0x70
#define C6DOFIMU16_GYRO_UI_FS_SEL_15_625DPS                     0x80

/**
 * @brief 6DOF IMU 16 accel full-scale setting.
 * @details Specified setting for accel full-scale of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_ACCEL_UI_FS_SEL_MASK                         0x70
#define C6DOFIMU16_ACCEL_UI_FS_SEL_16g                          0x10
#define C6DOFIMU16_ACCEL_UI_FS_SEL_8g                           0x20
#define C6DOFIMU16_ACCEL_UI_FS_SEL_4g                           0x30
#define C6DOFIMU16_ACCEL_UI_FS_SEL_2g                           0x40

/**
 * @brief 6DOF IMU 16 accel ODR setting.
 * @details Specified setting for accel ODR of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_ACCEL_ODR_6_4_KHZ                            0x03
#define C6DOFIMU16_ACCEL_ODR_3_2_KHZ                            0x04
#define C6DOFIMU16_ACCEL_ODR_1_6_KHZ                            0x05
#define C6DOFIMU16_ACCEL_ODR_800_HZ                             0x06
#define C6DOFIMU16_ACCEL_ODR_400_HZ                             0x07
#define C6DOFIMU16_ACCEL_ODR_200_HZ                             0x08
#define C6DOFIMU16_ACCEL_ODR_100_HZ                             0x09
#define C6DOFIMU16_ACCEL_ODR_50_HZ                              0x0A
#define C6DOFIMU16_ACCEL_ODR_25_HZ                              0x0B
#define C6DOFIMU16_ACCEL_ODR_12_5_HZ                            0x0C
#define C6DOFIMU16_ACCEL_ODR_6_25_HZ                            0x0D
#define C6DOFIMU16_ACCEL_ODR_3_125_HZ                           0x0E
#define C6DOFIMU16_ACCEL_ODR_1_5625_HZ                          0x0F

/**
 * @brief 6DOF IMU 16 gyro ODR setting.
 * @details Specified setting for gyro ODR of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_GYRO_ODR_6_4_KHZ                             0x03
#define C6DOFIMU16_GYRO_ODR_3_2_KHZ                             0x04
#define C6DOFIMU16_GYRO_ODR_1_6_KHZ                             0x05
#define C6DOFIMU16_GYRO_ODR_800_HZ                              0x06
#define C6DOFIMU16_GYRO_ODR_400_HZ                              0x07
#define C6DOFIMU16_GYRO_ODR_200_HZ                              0x08
#define C6DOFIMU16_GYRO_ODR_100_HZ                              0x09
#define C6DOFIMU16_GYRO_ODR_50_HZ                               0x0A
#define C6DOFIMU16_GYRO_ODR_25_HZ                               0x0B
#define C6DOFIMU16_GYRO_ODR_12_5_HZ                             0x0C
#define C6DOFIMU16_GYRO_ODR_6_25_HZ                             0x0D
#define C6DOFIMU16_GYRO_ODR_3_125_HZ                            0x0E
#define C6DOFIMU16_GYRO_ODR_1_5625_HZ                           0x0F

/**
 * @brief 6DOF IMU 16 software reset setting.
 * @details Specified setting for software reset of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_SOFTWARE_RESET                               0x02

/**
 * @brief 6DOF IMU 16 device ID setting.
 * @details Specified setting for device ID of 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_DEVICE_ID                                    0xE5

/**
 * @brief 6DOF IMU 16 data conversion factor setting.
 * @details The specified value of data conversion factor of
 * 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_ACCEL_2G_CONV_MUL                            16384u
#define C6DOFIMU16_ACCEL_4G_CONV_MUL                            8192u
#define C6DOFIMU16_ACCEL_8G_CONV_MUL                            4096u
#define C6DOFIMU16_ACCEL_16G_CONV_MUL                           2048u
#define C6DOFIMU16_GYRO_2000DPS_CONV_MUL                        16.4f
#define C6DOFIMU16_GYRO_1000DPS_CONV_MUL                        32.8f
#define C6DOFIMU16_GYRO_500DPS_CONV_MUL                         65.5f
#define C6DOFIMU16_GYRO_250DPS_CONV_MUL                         131.0f
#define C6DOFIMU16_GYRO_125DPS_CONV_MUL                         262.0f
#define C6DOFIMU16_GYRO_62_5DPS_CONV_MUL                        524.3f
#define C6DOFIMU16_GYRO_31_25DPS_CONV_MUL                       1048.6f
#define C6DOFIMU16_GYRO_15_625DPS_CONV_MUL                      2097.2f

/**
 * @brief 6DOF IMU 16 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 16 Click driver.
 */
#define C6DOFIMU16_DEVICE_ADDRESS_0                             0x68
#define C6DOFIMU16_DEVICE_ADDRESS_1                             0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU16_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU16_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu16_set

/**
 * @defgroup c6dofimu16_map 6DOF IMU 16 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 16 Click driver.
 */

/**
 * @addtogroup c6dofimu16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 16 Click to the selected MikroBUS.
 */
#define C6DOFIMU16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu16_map
/*! @} */ // c6dofimu16

/**
 * @brief 6DOF IMU 16 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 16 Click driver.
 */
typedef enum
{
    C6DOFIMU16_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    C6DOFIMU16_DRV_SEL_I2C       /**< I2C driver descriptor. */

} c6dofimu16_drv_t;

/**
 * @brief 6DOF IMU 16 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 16 Click driver.
 */
struct c6dofimu16_s;
typedef err_t ( *c6dofimu16_master_io_t )( struct c6dofimu16_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 16 Click context object.
 * @details Context object definition of 6DOF IMU 16 Click driver.
 */
typedef struct c6dofimu16_s
{
    digital_in_t int1;                  /**< Interrupt 1 pin. */
    digital_in_t int2;                  /**< Interrupt 2 pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu16_drv_t drv_sel;           /**< Master driver interface selector. */

    c6dofimu16_master_io_t write_f;     /**< Master write function. */
    c6dofimu16_master_io_t read_f;      /**< Master read function. */

} c6dofimu16_t;

/**
 * @brief 6DOF IMU 16 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 16 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int1;            /**< Interrupt 1 pin. */
    pin_name_t int2;            /**< Interrupt 2 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    c6dofimu16_drv_t drv_sel;   /**< Master driver interface selector. */

} c6dofimu16_cfg_t;

/**
 * @brief 6DOF IMU 16 Click axes data structure.
 * @details Axes data object definition of 6DOF IMU 16 Click driver.
 */
typedef struct
{
    float x_data;
    float y_data;
    float z_data;

} c6dofimu16_axis_t;

/**
 * @brief 6DOF IMU 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU16_OK = 0,
    C6DOFIMU16_ERROR = -1

} c6dofimu16_return_value_t;

/*!
 * @addtogroup c6dofimu16 6DOF IMU 16 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 16 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu16_cfg_setup ( c6dofimu16_cfg_t *cfg );

/**
 * @brief 6DOF IMU 16 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu16_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu16_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu16_drv_interface_sel ( c6dofimu16_cfg_t *cfg, c6dofimu16_drv_t drv_sel );

/**
 * @brief 6DOF IMU 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_init ( c6dofimu16_t *ctx, c6dofimu16_cfg_t *cfg );

/**
 * @brief 6DOF IMU 16 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu16_default_cfg ( c6dofimu16_t *ctx );

/**
 * @brief 6DOF IMU 16 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_generic_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 16 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_generic_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 16 get int1 pin function.
 * @details This function returns the INT1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu16_get_int1_pin ( c6dofimu16_t *ctx );

/**
 * @brief 6DOF IMU 16 get int2 pin function.
 * @details This function returns the INT2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu16_get_int2_pin ( c6dofimu16_t *ctx );

/**
 * @brief 6DOF IMU 16 data writing function.
 * @details This function writes a data byte into the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_reg_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 6DOF IMU 16 register data reading function.
 * @details This function reads a data byte from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_reg_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 6DOF IMU 16 software reset device function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_sw_reset ( c6dofimu16_t *ctx );

/**
 * @brief 6DOF IMU 16 read gyro function.
 * @details This function reads the angular rate of X, Y, and Z axis in degrees per second (mdps).
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[out] gyro_data : Output gyro data.
 * See #c6dofimu16_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_get_gyro_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *gyro_data );

/**
 * @brief 6DOF IMU 16 read accel function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (mg).
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[out] accel_data : Output accelerometer data.
 * See #c6dofimu16_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu16_get_accel_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *accel_data );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU16_H

/*! @} */ // c6dofimu16

// ------------------------------------------------------------------------ END

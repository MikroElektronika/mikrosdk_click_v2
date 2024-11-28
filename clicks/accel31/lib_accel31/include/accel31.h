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
 * @file accel31.h
 * @brief This file contains API for Accel 31 Click Driver.
 */

#ifndef ACCEL31_H
#define ACCEL31_H

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
 * @addtogroup accel31 Accel 31 Click Driver
 * @brief API for configuring and manipulating Accel 31 Click driver.
 * @{
 */

/**
 * @defgroup accel31_reg Accel 31 Registers List
 * @brief List of registers of Accel 31 Click driver.
 */

/**
 * @addtogroup accel31_reg
 * @{
 */

/**
 * @brief Accel 31 register map.
 * @details Specified register map of Accel 31 Click driver.
 */
#define ACCEL31_REG_CHIP_ID                 0x00
#define ACCEL31_REG_HEALTH_STATUS           0x02
#define ACCEL31_REG_CMD_SUSPEND             0x04
#define ACCEL31_REG_CONFIG_STATUS           0x10
#define ACCEL31_REG_SENSOR_STATUS           0x11
#define ACCEL31_REG_INT_STATUS_INT1_0       0x12
#define ACCEL31_REG_INT_STATUS_INT1_1       0x13
#define ACCEL31_REG_INT_STATUS_INT2_0       0x14
#define ACCEL31_REG_INT_STATUS_INT2_1       0x15
#define ACCEL31_REG_INT_STATUS_I3C_0        0x16
#define ACCEL31_REG_INT_STATUS_I3C_1        0x17
#define ACCEL31_REG_ACC_DATA_0              0x18
#define ACCEL31_REG_ACC_DATA_1              0x19
#define ACCEL31_REG_ACC_DATA_2              0x1A
#define ACCEL31_REG_ACC_DATA_3              0x1B
#define ACCEL31_REG_ACC_DATA_4              0x1C
#define ACCEL31_REG_ACC_DATA_5              0x1D
#define ACCEL31_REG_TEMP_DATA               0x1E
#define ACCEL31_REG_SENSOR_TIME_0           0x1F
#define ACCEL31_REG_SENSOR_TIME_1           0x20
#define ACCEL31_REG_SENSOR_TIME_2           0x21
#define ACCEL31_REG_FIFO_LEVEL_0            0x22
#define ACCEL31_REG_FIFO_LEVEL_1            0x23
#define ACCEL31_REG_FIFO_DATA_OUT           0x24
#define ACCEL31_REG_AUX_DATA_0              0x2B
#define ACCEL31_REG_AUX_DATA_1              0x2C
#define ACCEL31_REG_ACC_CONF_0              0x30
#define ACCEL31_REG_ACC_CONF_1              0x31
#define ACCEL31_REG_ACC_CONF_2              0x32
#define ACCEL31_REG_TEMP_CONF               0x33
#define ACCEL31_REG_INT1_CONF               0x34
#define ACCEL31_REG_INT2_CONF               0x35
#define ACCEL31_REG_INT_MAP_0               0x36
#define ACCEL31_REG_INT_MAP_1               0x37
#define ACCEL31_REG_INT_MAP_2               0x38
#define ACCEL31_REG_INT_MAP_3               0x39
#define ACCEL31_REG_IF_CONF_0               0x3A
#define ACCEL31_REG_IF_CONF_1               0x3B
#define ACCEL31_REG_FIFO_CTRL               0x40
#define ACCEL31_REG_FIFO_CONF_0             0x41
#define ACCEL31_REG_FIFO_CONF_1             0x42
#define ACCEL31_REG_FIFO_WM_0               0x43
#define ACCEL31_REG_FIFO_WM_1               0x44
#define ACCEL31_REG_FEAT_ENG_CONF           0x50
#define ACCEL31_REG_FEAT_ENG_STATUS         0x51
#define ACCEL31_REG_FEAT_ENG_GP_FLAGS       0x52
#define ACCEL31_REG_FEAT_ENG_GPR_CONF       0x53
#define ACCEL31_REG_FEAT_ENG_GPR_CTRL       0x54
#define ACCEL31_REG_FEAT_ENG_GPR_0          0x55
#define ACCEL31_REG_FEAT_ENG_GPR_1          0x56
#define ACCEL31_REG_FEAT_ENG_GPR_2          0x57
#define ACCEL31_REG_FEATURE_DATA_ADDR       0x5E
#define ACCEL31_REG_FEATURE_DATA_TX         0x5F
#define ACCEL31_REG_ACC_OFFSET_0            0x70
#define ACCEL31_REG_ACC_OFFSET_1            0x71
#define ACCEL31_REG_ACC_OFFSET_2            0x72
#define ACCEL31_REG_ACC_OFFSET_3            0x73
#define ACCEL31_REG_ACC_OFFSET_4            0x74
#define ACCEL31_REG_ACC_OFFSET_5            0x75
#define ACCEL31_REG_ACC_SELF_TEST           0x76
#define ACCEL31_REG_CMD                     0x7E

/*! @} */ // accel31_reg

/**
 * @defgroup accel31_set Accel 31 Registers Settings
 * @brief Settings for registers of Accel 31 Click driver.
 */

/**
 * @addtogroup accel31_set
 * @{
 */

/**
 * @brief Accel 31 CHIP_ID register setting.
 * @details Specified setting for CHIP_ID register of Accel 31 Click driver.
 */
#define ACCEL31_CHIP_ID                     0xC4

/**
 * @brief Accel 31 CMD_SUSPEND register setting.
 * @details Specified setting for CMD_SUSPEND register of Accel 31 Click driver.
 */
#define ACCEL31_CMD_SUSPEND_MODE_NORMAL     0x00
#define ACCEL31_CMD_SUSPEND_MODE_SUSPEND    0x01
#define ACCEL31_CMD_SUSPEND_MODE_MASK       0x01

/**
 * @brief Accel 31 SENSOR_STATUS register setting.
 * @details Specified setting for SENSOR_STATUS register of Accel 31 Click driver.
 */
#define ACCEL31_SENSOR_STATUS_SENSOR_RDY    0x04
#define ACCEL31_SENSOR_STATUS_TEMP_RDY      0x02
#define ACCEL31_SENSOR_STATUS_ACC_RDY       0x01

/**
 * @brief Accel 31 ACC_CONF_0 register setting.
 * @details Specified setting for ACC_CONF_0 register of Accel 31 Click driver.
 */
#define ACCEL31_ACC_CONF_0_SENSOR_DISABLE   0x00
#define ACCEL31_ACC_CONF_0_SENSOR_ENABLE    0x0F
#define ACCEL31_ACC_CONF_0_SENSOR_WRONG_CFG 0x0E
#define ACCEL31_ACC_CONF_0_SENSOR_MASK      0x0F

/**
 * @brief Accel 31 ACC_CONF_1 register setting.
 * @details Specified setting for ACC_CONF_1 register of Accel 31 Click driver.
 */
#define ACCEL31_ACC_CONF_1_POWER_MODE_MASK  0x80
#define ACCEL31_ACC_CONF_1_ACC_BWP_MASK     0x70
#define ACCEL31_ACC_CONF_1_ACC_ODR_MASK     0x0F

/**
 * @brief Accel 31 ACC_CONF_2 register setting.
 * @details Specified setting for ACC_CONF_2 register of Accel 31 Click driver.
 */
#define ACCEL31_ACC_CONF_2_ACC_DRDY_MASK    0x80
#define ACCEL31_ACC_CONF_2_NOISE_MODE_MASK  0x10
#define ACCEL31_ACC_CONF_2_ACC_IIR_MASK     0x0C
#define ACCEL31_ACC_CONF_2_ACC_RANGE_MASK   0x03

/**
 * @brief Accel 31 TEMP_CONF register setting.
 * @details Specified setting for TEMP_CONF register of Accel 31 Click driver.
 */
#define ACCEL31_TEMP_CONF_EXT_SEL_MASK      0x10
#define ACCEL31_TEMP_CONF_MEAS_SRC_MASK     0x08
#define ACCEL31_TEMP_CONF_RATE_MASK         0x07

/**
 * @brief Accel 31 INT2_CONF register setting.
 * @details Specified setting for INT2_CONF register of Accel 31 Click driver.
 */
#define ACCEL31_INT2_CONF_LVL_MASK          0x08
#define ACCEL31_INT2_CONF_OD_MASK           0x04
#define ACCEL31_INT2_CONF_MODE_OUT_DIS      0x00
#define ACCEL31_INT2_CONF_MODE_LATCH        0x01
#define ACCEL31_INT2_CONF_MODE_PULSE_SHORT  0x02
#define ACCEL31_INT2_CONF_MODE_PULSE_LONG   0x03
#define ACCEL31_INT2_CONF_MODE_MASK         0x03

/**
 * @brief Accel 31 CMD register setting.
 * @details Specified setting for CMD register of Accel 31 Click driver.
 */
#define ACCEL31_CMD_SOFT_RESET              0xB6

/**
 * @brief Accel 31 accel output data rate setting.
 * @details Specified setting for accel output data rate of Accel 31 Click driver.
 */
#define ACCEL31_ACCEL_ODR_1_5625_HZ         0
#define ACCEL31_ACCEL_ODR_3_125_HZ          1
#define ACCEL31_ACCEL_ODR_6_25_HZ           2
#define ACCEL31_ACCEL_ODR_12_5_HZ           3
#define ACCEL31_ACCEL_ODR_25_HZ             4
#define ACCEL31_ACCEL_ODR_50_HZ             5
#define ACCEL31_ACCEL_ODR_100_HZ            6
#define ACCEL31_ACCEL_ODR_200_HZ            7
#define ACCEL31_ACCEL_ODR_400_HZ            8
#define ACCEL31_ACCEL_ODR_800_HZ            9
#define ACCEL31_ACCEL_ODR_1600_HZ           10
#define ACCEL31_ACCEL_ODR_3200_HZ           11
#define ACCEL31_ACCEL_ODR_6400_HZ           12

/**
 * @brief Accel 31 accel full scale setting.
 * @details Specified setting for accel full scale of Accel 31 Click driver.
 */
#define ACCEL31_ACCEL_FS_2G                 0
#define ACCEL31_ACCEL_FS_4G                 1
#define ACCEL31_ACCEL_FS_8G                 2
#define ACCEL31_ACCEL_FS_16G                3

/**
 * @brief Accel 31 temperature output data rate setting.
 * @details Specified setting for temperature output data rate of Accel 31 Click driver.
 */
#define ACCEL31_TEMP_ODR_1_5625_HZ          0
#define ACCEL31_TEMP_ODR_3_125_HZ           1
#define ACCEL31_TEMP_ODR_6_25_HZ            2
#define ACCEL31_TEMP_ODR_12_5_HZ            3
#define ACCEL31_TEMP_ODR_25_HZ              4
#define ACCEL31_TEMP_ODR_50_HZ              5
#define ACCEL31_TEMP_ODR_100_HZ             6
#define ACCEL31_TEMP_ODR_200_HZ             7

/**
 * @brief Accel 31 sensitivity setting.
 * @details Specified setting for sensitivity of Accel 31 Click driver.
 */
#define ACCEL31_ACCEL_SENS_G_PER_LSB        0.000061
#define ACCEL31_TEMP_OFFSET                 23

/**
 * @brief Accel 31 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 31 Click driver.
 */
#define ACCEL31_DEVICE_ADDRESS              0x18

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel31_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL31_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL31_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel31_set

/**
 * @defgroup accel31_map Accel 31 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 31 Click driver.
 */

/**
 * @addtogroup accel31_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 31 Click to the selected MikroBUS.
 */
#define ACCEL31_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel31_map
/*! @} */ // accel31

/**
 * @brief Accel 31 Click driver selector.
 * @details Selects target driver interface of Accel 31 Click driver.
 */
typedef enum
{
    ACCEL31_DRV_SEL_SPI,            /**< SPI driver descriptor. */
    ACCEL31_DRV_SEL_I2C             /**< I2C driver descriptor. */

} accel31_drv_t;

/**
 * @brief Accel 31 Click driver interface.
 * @details Definition of driver interface of Accel 31 Click driver.
 */
struct accel31_s;
typedef err_t ( *accel31_master_io_t )( struct accel31_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 31 Click context object.
 * @details Context object definition of Accel 31 Click driver.
 */
typedef struct accel31_s
{
    digital_in_t int2;              /**< Interrupt 2 pin. */
    digital_in_t int1;              /**< Interrupt 1 pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    accel31_drv_t drv_sel;          /**< Master driver interface selector. */

    accel31_master_io_t write_f;    /**< Master write function. */
    accel31_master_io_t read_f;     /**< Master read function. */

    float accel_sens;               /**< Accel sensitivity setting. */

} accel31_t;

/**
 * @brief Accel 31 Click configuration object.
 * @details Configuration object definition of Accel 31 Click driver.
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

    accel31_drv_t drv_sel;          /**< Master driver interface selector. */

} accel31_cfg_t;

/**
 * @brief Accel 31 Click axes data structure.
 * @details Axes data object definition of Accel 31 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel31_axes_t;

/**
 * @brief Accel 31 Click data structure.
 * @details Data object definition of Accel 31 Click driver.
 */
typedef struct
{
    accel31_axes_t accel;           /**< Accel data. */
    int8_t temperature;             /**< Temperature data. */

} accel31_data_t;

/**
 * @brief Accel 31 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL31_OK = 0,
    ACCEL31_ERROR = -1,
    ACCEL31_DATA_NOT_READY = -2

} accel31_return_value_t;

/*!
 * @addtogroup accel31 Accel 31 Click Driver
 * @brief API for configuring and manipulating Accel 31 Click driver.
 * @{
 */

/**
 * @brief Accel 31 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel31_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel31_cfg_setup ( accel31_cfg_t *cfg );

/**
 * @brief Accel 31 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel31_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel31_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel31_drv_interface_sel ( accel31_cfg_t *cfg, accel31_drv_t drv_sel );

/**
 * @brief Accel 31 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel31_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_init ( accel31_t *ctx, accel31_cfg_t *cfg );

/**
 * @brief Accel 31 default configuration function.
 * @details This function executes a default configuration of Accel 31
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel31_default_cfg ( accel31_t *ctx );

/**
 * @brief Accel 31 write reg function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_write_reg ( accel31_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 31 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_write_regs ( accel31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 31 read reg function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_read_reg ( accel31_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 31 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_read_regs ( accel31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 31 get int1 pin function.
 * @details This function returns the interrupt 1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel31_get_int1_pin ( accel31_t *ctx );

/**
 * @brief Accel 31 get int2 pin function.
 * @details This function returns the interrupt 2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel31_get_int2_pin ( accel31_t *ctx );

/**
 * @brief Accel 31 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_check_communication ( accel31_t *ctx );

/**
 * @brief Accel 31 sw reset function.
 * @details This function restores the default settings.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_sw_reset ( accel31_t *ctx );

/**
 * @brief Accel 31 set accel odr function.
 * @details This function sets the accel measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - 1.5625Hz,
 *                  @li @c 1 - 3.125Hz,
 *                  @li @c 2 - 6.25Hz,
 *                  @li @c 3 - 12.5Hz,
 *                  @li @c 4 - 25Hz,
 *                  @li @c 5 - 50Hz,
 *                  @li @c 6 - 100Hz,
 *                  @li @c 7 - 200Hz,
 *                  @li @c 8 - 400Hz,
 *                  @li @c 9 - 800Hz,
 *                  @li @c 10 - 1600Hz,
 *                  @li @c 11 - 3200Hz,
 *                  @li @c 12 - 6400Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_set_accel_odr ( accel31_t *ctx, uint8_t odr );

/**
 * @brief Accel 31 set accel fsr function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 2G,
 *                  @li @c 1 - 4G,
 *                  @li @c 2 - 8G,
 *                  @li @c 3 - 16G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_set_accel_fsr ( accel31_t *ctx, uint8_t fsr );

/**
 * @brief Accel 31 set temp odr function.
 * @details This function sets the temperature measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - 1.5625Hz,
 *                  @li @c 1 - 3.125Hz,
 *                  @li @c 2 - 6.25Hz,
 *                  @li @c 3 - 12.5Hz,
 *                  @li @c 4 - 25Hz,
 *                  @li @c 5 - 50Hz,
 *                  @li @c 6 - 100Hz,
 *                  @li @c 7 - 200Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_set_temp_odr ( accel31_t *ctx, uint8_t odr );

/**
 * @brief Accel 31 get accel drdy function.
 * @details This function gets the accel new data available flag.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_get_accel_drdy ( accel31_t *ctx, uint8_t *drdy );

/**
 * @brief Accel 31 get temp drdy function.
 * @details This function gets the temperature new data available flag.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_get_temp_drdy ( accel31_t *ctx, uint8_t *drdy );

/**
 * @brief Accel 31 get accel function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (g).
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[out] accel : Output accelerometer data.
 * See #accel31_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_get_accel ( accel31_t *ctx, accel31_axes_t *accel );

/**
 * @brief Accel 31 get temp function.
 * @details This function reads the temperature measurement in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_get_temp ( accel31_t *ctx, int8_t *temp );

/**
 * @brief Accel 31 get data function.
 * @details This function reads the accelerometer and temperature measurement data.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure read.
 * See #accel31_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel31_get_data ( accel31_t *ctx, accel31_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ACCEL31_H

/*! @} */ // accel31

// ------------------------------------------------------------------------ END

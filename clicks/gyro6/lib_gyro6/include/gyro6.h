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
 * @file gyro6.h
 * @brief This file contains API for Gyro 6 Click Driver.
 */

#ifndef GYRO6_H
#define GYRO6_H

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
 * @addtogroup gyro6 Gyro 6 Click Driver
 * @brief API for configuring and manipulating Gyro 6 Click driver.
 * @{
 */

/**
 * @defgroup gyro6_reg Gyro 6 Registers List
 * @brief List of registers of Gyro 6 Click driver.
 */

/**
 * @addtogroup gyro6_reg
 * @{
 */

/**
 * @brief Gyro 6 Register Map.
 * @details Specified register map of Gyro 6 Click driver.
 */
#define GYRO6_REG_SELF_TEST_X_GYRO          0x00
#define GYRO6_REG_SELF_TEST_Y_GYRO          0x01
#define GYRO6_REG_SELF_TEST_Z_GYRO          0x02
#define GYRO6_REG_XG_OFFS_USRH              0x13
#define GYRO6_REG_XG_OFFS_USRL              0x14
#define GYRO6_REG_YG_OFFS_USRH              0x15
#define GYRO6_REG_YG_OFFS_USRL              0x16
#define GYRO6_REG_ZG_OFFS_USRH              0x17
#define GYRO6_REG_ZG_OFFS_USRL              0x18
#define GYRO6_REG_SMPLRT_DIV                0x19
#define GYRO6_REG_CONFIG                    0x1A
#define GYRO6_REG_GYRO_CONFIG               0x1B
#define GYRO6_REG_LP_MODE_CFG               0x1E
#define GYRO6_REG_FIFO_EN                   0x23
#define GYRO6_REG_FSYNC_INT                 0x36
#define GYRO6_REG_INT_PIN_CFG               0x37
#define GYRO6_REG_INT_ENABLE                0x38
#define GYRO6_REG_INT_STATUS                0x3A
#define GYRO6_REG_TEMP_OUT_H                0x41
#define GYRO6_REG_TEMP_OUT_L                0x42
#define GYRO6_REG_GYRO_XOUT_H               0x43
#define GYRO6_REG_GYRO_XOUT_L               0x44
#define GYRO6_REG_GYRO_YOUT_H               0x45
#define GYRO6_REG_GYRO_YOUT_L               0x46
#define GYRO6_REG_GYRO_ZOUT_H               0x47
#define GYRO6_REG_GYRO_ZOUT_L               0x48
#define GYRO6_REG_SIGNAL_PATH_RESET         0x68
#define GYRO6_REG_USER_CTRL                 0x6A
#define GYRO6_REG_PWR_MGMT_1                0x6B
#define GYRO6_REG_PWR_MGMT_2                0x6C
#define GYRO6_REG_FIFO_COUNTH               0x72
#define GYRO6_REG_FIFO_COUNTL               0x73
#define GYRO6_REG_FIFO_R_W                  0x74
#define GYRO6_REG_WHO_AM_I                  0x75

/*! @} */ // gyro6_reg

/**
 * @defgroup gyro6_set Gyro 6 Registers Settings
 * @brief Settings for registers of Gyro 6 Click driver.
 */

/**
 * @addtogroup gyro6_set
 * @{
 */

/**
 * @brief Gyro 6 Configuration settings.
 * @details Specified settings for Configuration register of Gyro 6 Click driver.
 */
#define GYRO6_CONFIG_FIFO_MODE              0x40
#define GYRO6_CONFIG_EXT_SYNC_DIS           0x00
#define GYRO6_CONFIG_EXT_SYNC_TEMP_OUT_L    0x08
#define GYRO6_CONFIG_EXT_SYNC_GYRO_XOUT_L   0x10
#define GYRO6_CONFIG_EXT_SYNC_GYRO_YOUT_L   0x18
#define GYRO6_CONFIG_EXT_SYNC_GYRO_ZOUT_L   0x20
#define GYRO6_CONFIG_FIFO_MODE              0x40
#define GYRO6_CONFIG_DLPF_CFG_0             0x00
#define GYRO6_CONFIG_DLPF_CFG_1             0x01
#define GYRO6_CONFIG_DLPF_CFG_2             0x02
#define GYRO6_CONFIG_DLPF_CFG_3             0x03
#define GYRO6_CONFIG_DLPF_CFG_4             0x04
#define GYRO6_CONFIG_DLPF_CFG_5             0x05
#define GYRO6_CONFIG_DLPF_CFG_6             0x06
#define GYRO6_CONFIG_DLPF_CFG_7             0x07

/**
 * @brief Gyro 6 Gyro Configuration settings.
 * @details Specified settings for Gyro Configuration register of Gyro 6 Click driver.
 */
#define GYRO6_GYRO_CONFIG_XG_ST             0x80
#define GYRO6_GYRO_CONFIG_YG_ST             0x40
#define GYRO6_GYRO_CONFIG_ZG_ST             0x20
#define GYRO6_GYRO_CONFIG_FS_SEL_250DPS     0x00
#define GYRO6_GYRO_CONFIG_FS_SEL_500DPS     0x08
#define GYRO6_GYRO_CONFIG_FS_SEL_1000DPS    0x10
#define GYRO6_GYRO_CONFIG_FS_SEL_2000DPS    0x18
#define GYRO6_GYRO_CONFIG_FS_SEL_BITS_MASK  0x18
#define GYRO6_GYRO_CONFIG_FCHOICE_B_0       0x00
#define GYRO6_GYRO_CONFIG_FCHOICE_B_1       0x01
#define GYRO6_GYRO_CONFIG_FCHOICE_B_2       0x02
#define GYRO6_GYRO_CONFIG_FCHOICE_B_3       0x03

/**
 * @brief Gyro 6 Sample Rate settings.
 * @details Specified settings for Sample Rate register of Gyro 6 Click driver.
 * @note SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV), where INTERNAL_SAMPLE_RATE = 1 kHz.
 */
#define GYRO6_SAMPLE_RATE_3p9HZ             255
#define GYRO6_SAMPLE_RATE_10HZ              99
#define GYRO6_SAMPLE_RATE_15p4HZ            64
#define GYRO6_SAMPLE_RATE_30p3HZ            32
#define GYRO6_SAMPLE_RATE_50HZ              19
#define GYRO6_SAMPLE_RATE_100HZ             9
#define GYRO6_SAMPLE_RATE_125HZ             7
#define GYRO6_SAMPLE_RATE_200HZ             4
#define GYRO6_SAMPLE_RATE_250HZ             3
#define GYRO6_SAMPLE_RATE_333p3HZ           2
#define GYRO6_SAMPLE_RATE_500HZ             1
#define GYRO6_SAMPLE_RATE_1000HZ            0

/**
 * @brief Gyro 6 Low Power Mode Configuration settings.
 * @details Specified settings for Low Power Mode Configuration register of Gyro 6 Click driver.
 */
#define GYRO6_LP_MODE_CFG_GYRO_CYCLE        0x80
#define GYRO6_LP_MODE_CFG_G_AVGCFG_1X       0x00
#define GYRO6_LP_MODE_CFG_G_AVGCFG_2X       0x10
#define GYRO6_LP_MODE_CFG_G_AVGCFG_4X       0x20
#define GYRO6_LP_MODE_CFG_G_AVGCFG_8X       0x30
#define GYRO6_LP_MODE_CFG_G_AVGCFG_16X      0x40
#define GYRO6_LP_MODE_CFG_G_AVGCFG_32X      0x50
#define GYRO6_LP_MODE_CFG_G_AVGCFG_64X      0x60
#define GYRO6_LP_MODE_CFG_G_AVGCFG_128X     0x70

/**
 * @brief Gyro 6 FIFO Enable settings.
 * @details Specified settings for FIFO Enable register of Gyro 6 Click driver.
 */
#define GYRO6_FIFO_EN_TEMP_FIFO_EN          0x80
#define GYRO6_FIFO_EN_XG_FIFO_EN            0x40
#define GYRO6_FIFO_EN_YG_FIFO_EN            0x20
#define GYRO6_FIFO_EN_ZG_FIFO_EN            0x10

/**
 * @brief Gyro 6 FSYNC Interrupt Status settings.
 * @details Specified settings for FSYNC Interrupt Status register of Gyro 6 Click driver.
 */
#define GYRO6_FSYNC_INT                     0x80

/**
 * @brief Gyro 6 Interrupt PIN CFG settings.
 * @details Specified settings for Interrupt PIN CFG register of Gyro 6 Click driver.
 */
#define GYRO6_INT_PIN_CFG_INT_LEVEL         0x80
#define GYRO6_INT_PIN_CFG_INT_OPEN          0x40
#define GYRO6_INT_PIN_CFG_LATCH_INT_EN      0x20
#define GYRO6_INT_PIN_CFG_INT_RD_CLEAR      0x10
#define GYRO6_INT_PIN_CFG_FSYNC_INT_LEVEL   0x08
#define GYRO6_INT_PIN_CFG_FSYNC_INT_MODE_EN 0x04

/**
 * @brief Gyro 6 Interrupt Enable settings.
 * @details Specified settings for Interrupt Enable register of Gyro 6 Click driver.
 */
#define GYRO6_INT_ENABLE_FIFO_OFLOW_INT_EN  0x10
#define GYRO6_INT_ENABLE_GDRIVE_INT_EN      0x04
#define GYRO6_INT_ENABLE_DATA_RDY_INT_EN    0x01

/**
 * @brief Gyro 6 Interrupt Status values.
 * @details Specified values for Interrupt Status of Gyro 6 Click driver.
 */
#define GYRO6_INT_STATUS_FIFO_OFLOW_INT     0x10
#define GYRO6_INT_STATUS_GDRIVE_INT         0x04
#define GYRO6_INT_STATUS_DATA_RDY_INT       0x01

/**
 * @brief Gyro 6 Temperature Calculation constants.
 * @details Specified constants for Die temperature calculation of Gyro 6 Click driver.
 */
#define GYRO6_ROOM_TEMP_OFFSET              0
#define GYRO6_TEMP_SENSITIVITY              326.8
#define GYRO6_TEMP_NOMINAL                  25.0

/**
 * @brief Gyro 6 Gyro Sensitivity Scale Factor.
 * @details Specified values for Gyro Sensitivity Scale Factor of Gyro 6 Click driver.
 */
#define GYRO6_GYRO_SENSITIVITY_FS_SEL_0     131.0
#define GYRO6_GYRO_SENSITIVITY_FS_SEL_1     65.5
#define GYRO6_GYRO_SENSITIVITY_FS_SEL_2     32.8
#define GYRO6_GYRO_SENSITIVITY_FS_SEL_3     16.4

/**
 * @brief Gyro 6 Signal Path Reset settings.
 * @details Specified settings for Signal Path Reset register of Gyro 6 Click driver.
 */
#define GYRO6_SIGNAL_PATH_RESET_TEMP_RST    0x01

/**
 * @brief Gyro 6 User Control settings.
 * @details Specified settings for User Control register of Gyro 6 Click driver.
 */
#define GYRO6_USER_CTRL_FIFO_EN             0x40
#define GYRO6_USER_CTRL_I2C_IF_DIS          0x10
#define GYRO6_USER_CTRL_FIFO_RST            0x04
#define GYRO6_USER_CTRL_SIG_COND_RST        0x01

/**
 * @brief Gyro 6 Power Management 1 settings.
 * @details Specified settings for Power Management 1 register of Gyro 6 Click driver.
 */
#define GYRO6_PWR_MGMT_1_DEVICE_RESET       0x80
#define GYRO6_PWR_MGMT_1_SLEEP              0x40
#define GYRO6_PWR_MGMT_1_GYRO_STANDBY       0x10
#define GYRO6_PWR_MGMT_1_INTERNAL_OSC       0x00
#define GYRO6_PWR_MGMT_1_AUTO_SEL_CLOCK     0x01
#define GYRO6_PWR_MGMT_1_STOP_CLOCK         0x07

/**
 * @brief Gyro 6 Power Management 2 settings.
 * @details Specified settings for Power Management 2 register of Gyro 6 Click driver.
 */
#define GYRO6_PWR_MGMT_2_DISABLE_X_GYRO     0x04
#define GYRO6_PWR_MGMT_2_DISABLE_Y_GYRO     0x02
#define GYRO6_PWR_MGMT_2_DISABLE_Z_GYRO     0x01

/**
 * @brief Gyro 6 Device ID.
 * @details Specified Device ID value of Gyro 6 Click driver.
 */
#define GYRO6_DEVICE_ID                     0xB5

/**
 * @brief Gyro 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Gyro 6 Click driver.
 */
#define GYRO6_SET_DEV_ADDR_0                0x68
#define GYRO6_SET_DEV_ADDR_1                0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b gyro6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GYRO6_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define GYRO6_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gyro6_set

/**
 * @defgroup gyro6_map Gyro 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Gyro 6 Click driver.
 */

/**
 * @addtogroup gyro6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Gyro 6 Click to the selected MikroBUS.
 */
#define GYRO6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gyro6_map
/*! @} */ // gyro6

/**
 * @brief Gyro 6 Click driver selector.
 * @details Selects target driver interface of Gyro 6 Click driver.
 */
typedef enum
{
    GYRO6_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    GYRO6_DRV_SEL_I2C       /**< I2C driver descriptor. */

} gyro6_drv_t;

/**
 * @brief Gyro 6 Click driver interface.
 * @details Definition of driver interface of Gyro 6 Click driver.
 */
typedef err_t ( *gyro6_master_io_t )( struct gyro6_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Gyro 6 Click context object.
 * @details Context object definition of Gyro 6 Click driver.
 */
typedef struct gyro6_s
{
    digital_out_t   pwm;            /**< FSYNC PWM pin. */

    digital_in_t    int_pin;        /**< Interrupt pin. */

    i2c_master_t    i2c;            /**< I2C driver object. */
    spi_master_t    spi;            /**< SPI driver object. */

    uint8_t         slave_address;  /**< Device slave address (used for I2C driver). */
    pin_name_t      chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    gyro6_drv_t     drv_sel;        /**< Master driver interface selector. */

    gyro6_master_io_t  write_f;     /**< Master write function. */
    gyro6_master_io_t  read_f;      /**< Master read function. */

} gyro6_t;

/**
 * @brief Gyro 6 Click configuration object.
 * @details Configuration object definition of Gyro 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  pwm;                /**< FSYNC PWM pin. */
    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t    i2c_speed;          /**< I2C serial speed. */
    uint8_t     i2c_address;        /**< I2C slave address. */

    uint32_t                            spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                   spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t   cs_polarity;    /**< Chip select pin polarity. */

    gyro6_drv_t drv_sel;            /**< Master driver interface selector. */

} gyro6_cfg_t;

/**
 * @brief Gyro 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GYRO6_OK = 0,
    GYRO6_ERROR = -1

} gyro6_return_value_t;

/*!
 * @addtogroup gyro6 Gyro 6 Click Driver
 * @brief API for configuring and manipulating Gyro 6 Click driver.
 * @{
 */

/**
 * @brief Gyro 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gyro6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gyro6_cfg_setup ( gyro6_cfg_t *cfg );

/**
 * @brief Gyro 6 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gyro6_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gyro6_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gyro6_drv_interface_selection ( gyro6_cfg_t *cfg, gyro6_drv_t drv_sel );

/**
 * @brief Gyro 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gyro6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_init ( gyro6_t *ctx, gyro6_cfg_t *cfg );

/**
 * @brief Gyro 6 default configuration function.
 * @details This function executes a default configuration of Gyro 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gyro6_default_cfg ( gyro6_t *ctx );

/**
 * @brief Gyro 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_generic_write ( gyro6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_generic_read ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Gyro 6 write register function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_write_register ( gyro6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Gyro 6 read register function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_read_register ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Gyro 6 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gyro6_get_int_pin ( gyro6_t *ctx );

/**
 * @brief Gyro 6 set PWM pin function.
 * @details This function sets the PWM pin logic state.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gyro6_set_pwm_pin ( gyro6_t *ctx, uint8_t state );

/**
 * @brief Gyro 6 check communication function.
 * @details This function checks the communication by reading and verifying the device ID bytes.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_check_communication ( gyro6_t *ctx );

/**
 * @brief Gyro 6 read DIE temperature function.
 * @details This function reads the chip internal temperature.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_read_die_temperature ( gyro6_t *ctx, float *temperature );

/**
 * @brief Gyro 6 get axis function.
 * @details This function reads the gyroscope values for all three axis.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[out] x_axis : X axis value.
 * @param[out] y_axis : Y axis value.
 * @param[out] z_axis : Z axis value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro6_get_axis ( gyro6_t *ctx, float *x_axis, float *y_axis, float *z_axis );

/**
 * @brief Gyro 6 set low power mode function.
 * @details This function enables low power mode and sets the sample rate and average sample data.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] sample_rate : Sample Rate divider.
 * @param[in] average : Average sample data.
 * See #gyro6_set group for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV), where INTERNAL_SAMPLE_RATE = 1 kHz.
 */
err_t gyro6_set_low_power_mode ( gyro6_t *ctx, uint8_t sample_rate, uint8_t average );

#ifdef __cplusplus
}
#endif
#endif // GYRO6_H

/*! @} */ // gyro6

// ------------------------------------------------------------------------ END

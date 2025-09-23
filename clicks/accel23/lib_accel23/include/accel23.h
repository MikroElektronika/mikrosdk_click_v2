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
 * @file accel23.h
 * @brief This file contains API for Accel 23 Click Driver.
 */

#ifndef ACCEL23_H
#define ACCEL23_H

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
 * @addtogroup accel23 Accel 23 Click Driver
 * @brief API for configuring and manipulating Accel 23 Click driver.
 * @{
 */

/**
 * @defgroup accel23_reg Accel 23 Registers List
 * @brief List of registers of Accel 23 Click driver.
 */

/**
 * @addtogroup accel23_reg
 * @{
 */

/**
 * @brief Accel 23 description register.
 * @details Specified register for description of Accel 23 Click driver.
 */
#define ACCEL23_REG_EXT_CLK_CFG                 0x08
#define ACCEL23_REG_PIN_CTRL                    0x0C
#define ACCEL23_REG_WAKE_UP_DUR_EXT             0x0E
#define ACCEL23_REG_WHO_AM_I                    0x0F
#define ACCEL23_REG_CTRL1                       0x10
#define ACCEL23_REG_CTRL2                       0x11
#define ACCEL23_REG_CTRL3                       0x12
#define ACCEL23_REG_CTRL4                       0x13
#define ACCEL23_REG_CTRL5                       0x14
#define ACCEL23_REG_FIFO_CTRL                   0x15
#define ACCEL23_REG_FIFO_WTM                    0x16
#define ACCEL23_REG_INTERRUPT_CFG               0x17
#define ACCEL23_REG_SIXD                        0x18
#define ACCEL23_REG_WAKE_UP_THS                 0x1C
#define ACCEL23_REG_WAKE_UP_DUR                 0x1D
#define ACCEL23_REG_FREE_FALL                   0x1E
#define ACCEL23_REG_MD1_CFG                     0x1F
#define ACCEL23_REG_MD2_CFG                     0x20
#define ACCEL23_REG_WAKE_UP_SRC                 0x21
#define ACCEL23_REG_TAP_SRC                     0x22
#define ACCEL23_REG_SIXD_SRC                    0x23
#define ACCEL23_REG_ALL_INT_SRC                 0x24
#define ACCEL23_REG_STATUS                      0x25
#define ACCEL23_REG_FIFO_STATUS1                0x26
#define ACCEL23_REG_FIFO_STATUS2                0x27
#define ACCEL23_REG_OUT_X_L                     0x28
#define ACCEL23_REG_OUT_X_H                     0x29
#define ACCEL23_REG_OUT_Y_L                     0x2A
#define ACCEL23_REG_OUT_Y_H                     0x2B
#define ACCEL23_REG_OUT_Z_L                     0x2C
#define ACCEL23_REG_OUT_Z_H                     0x2D
#define ACCEL23_REG_OUT_T_AH_QVAR_L             0x2E
#define ACCEL23_REG_OUT_T_AH_QVAR_H             0x2F
#define ACCEL23_REG_AH_QVAR_CFG                 0x31
#define ACCEL23_REG_SELF_TEST                   0x32
#define ACCEL23_REG_I3C_IF_CTRL                 0x33
#define ACCEL23_REG_EMB_FUNC_STATUS_MAINPAGE    0x34
#define ACCEL23_REG_FSM_STATUS_MAINPAGE         0x35
#define ACCEL23_REG_MLC_STATUS_MAINPAGE         0x36
#define ACCEL23_REG_SLEEP                       0x3D
#define ACCEL23_REG_EN_DEVICE_CONFIG            0x3E
#define ACCEL23_REG_FUNC_CFG_ACCESS             0x3F
#define ACCEL23_REG_FIFO_DATA_OUT_TAG           0x40
#define ACCEL23_REG_FIFO_DATA_OUT_X_L           0x41
#define ACCEL23_REG_FIFO_DATA_OUT_X_H           0x42
#define ACCEL23_REG_FIFO_DATA_OUT_Y_L           0x43
#define ACCEL23_REG_FIFO_DATA_OUT_Y_H           0x44
#define ACCEL23_REG_FIFO_DATA_OUT_Z_L           0x45
#define ACCEL23_REG_FIFO_DATA_OUT_Z_H           0x46
#define ACCEL23_REG_FIFO_BATCH_DEC              0x47
#define ACCEL23_REG_TAP_CFG0                    0x6F
#define ACCEL23_REG_TAP_CFG1                    0x70
#define ACCEL23_REG_TAP_CFG2                    0x71
#define ACCEL23_REG_TAP_CFG3                    0x72
#define ACCEL23_REG_TAP_CFG4                    0x73
#define ACCEL23_REG_TAP_CFG5                    0x74
#define ACCEL23_REG_TAP_CFG6                    0x75
#define ACCEL23_REG_TIMESTAMP0                  0x7A
#define ACCEL23_REG_TIMESTAMP1                  0x7B
#define ACCEL23_REG_TIMESTAMP2                  0x7C
#define ACCEL23_REG_TIMESTAMP3                  0x7D

/*! @} */ // accel23_reg

/**
 * @defgroup accel23_set Accel 23 Registers Settings
 * @brief Settings for registers of Accel 23 Click driver.
 */

/**
 * @addtogroup accel23_set
 * @{
 */

/**
 * @brief Accel 23 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of Accel 23 Click driver.
 */
#define ACCEL23_WHO_AM_I                        0x47

/**
 * @brief Accel 23 CTRL1 register setting.
 * @details Specified setting for CTRL1 register of Accel 23 Click driver.
 */
#define ACCEL23_CTRL1_SMART_POWER_EN            0x80
#define ACCEL23_CTRL1_INT1_ON_RES               0x40
#define ACCEL23_CTRL1_SW_RESET                  0x20
#define ACCEL23_CTRL1_IF_ADD_INC                0x10
#define ACCEL23_CTRL1_DRDY_PULSED               0x08
#define ACCEL23_CTRL1_WU_X_EN                   0x04
#define ACCEL23_CTRL1_WU_Y_EN                   0x02
#define ACCEL23_CTRL1_WU_Z_EN                   0x01

/**
 * @brief Accel 23 CTRL5 register setting.
 * @details Specified setting for CTRL5 register of Accel 23 Click driver.
 */
#define ACCEL23_CTRL5_ODR_PWR_DOWN              0x00
#define ACCEL23_CTRL5_ODR_ULP_1_6_HZ            0x10
#define ACCEL23_CTRL5_ODR_ULP_3_HZ              0x20
#define ACCEL23_CTRL5_ODR_ULP_25_HZ             0x30
#define ACCEL23_CTRL5_ODR_6_HZ                  0x40
#define ACCEL23_CTRL5_ODR_12_5_HZ               0x50
#define ACCEL23_CTRL5_ODR_25_HZ                 0x60
#define ACCEL23_CTRL5_ODR_50_HZ                 0x70
#define ACCEL23_CTRL5_ODR_100_HZ                0x80
#define ACCEL23_CTRL5_ODR_200_HZ                0x90
#define ACCEL23_CTRL5_ODR_400_HZ                0xA0
#define ACCEL23_CTRL5_ODR_800_HZ                0xB0
#define ACCEL23_CTRL5_ODR_ONE_SHOT_INT2         0xE0
#define ACCEL23_CTRL5_ODR_ONE_SHOT_IFACE        0xF0
#define ACCEL23_CTRL5_ODR_MASK                  0xF0
#define ACCEL23_CTRL5_BW_ODR_2                  0x00
#define ACCEL23_CTRL5_BW_ODR_4                  0x04
#define ACCEL23_CTRL5_BW_ODR_8                  0x08
#define ACCEL23_CTRL5_BW_ODR_16                 0x0C
#define ACCEL23_CTRL5_BW_MASK                   0x0C
#define ACCEL23_CTRL5_FS_2_G                    0x00
#define ACCEL23_CTRL5_FS_4_G                    0x01
#define ACCEL23_CTRL5_FS_8_G                    0x02
#define ACCEL23_CTRL5_FS_16_G                   0x03
#define ACCEL23_CTRL5_FS_MASK                   0x03

/**
 * @brief Accel 23 STATUS register setting.
 * @details Specified setting for STATUS register of Accel 23 Click driver.
 */
#define ACCEL23_STATUS_INT_GLOBAL               0x20
#define ACCEL23_STATUS_DRDY                     0x01

/**
 * @brief Accel 23 EN_DEVICE_CONFIG register setting.
 * @details Specified setting for EN_DEVICE_CONFIG register of Accel 23 Click driver.
 */
#define ACCEL23_EN_DEVICE_CONFIG_SOFT_PD        0x01

/**
 * @brief Accel 23 output data rate setting.
 * @details Specified setting for output data rate of Accel 23 Click driver.
 */
#define ACCEL23_ODR_PWR_DOWN                    0
#define ACCEL23_ODR_ULP_1_6_HZ                  1
#define ACCEL23_ODR_ULP_3_HZ                    2
#define ACCEL23_ODR_ULP_25_HZ                   3
#define ACCEL23_ODR_6_HZ                        4
#define ACCEL23_ODR_12_5_HZ                     5
#define ACCEL23_ODR_25_HZ                       6
#define ACCEL23_ODR_50_HZ                       7
#define ACCEL23_ODR_100_HZ                      8
#define ACCEL23_ODR_200_HZ                      9
#define ACCEL23_ODR_400_HZ                      10
#define ACCEL23_ODR_800_HZ                      11
#define ACCEL23_ODR_ONE_SHOT_INT2               14
#define ACCEL23_ODR_ONE_SHOT_IFACE              15

/**
 * @brief Accel 23 full scale setting.
 * @details Specified setting for full scale of Accel 23 Click driver.
 */
#define ACCEL23_FS_2G                           0
#define ACCEL23_FS_4G                           1
#define ACCEL23_FS_8G                           2
#define ACCEL23_FS_16G                          3

/**
 * @brief Accel 23 sensitivity setting.
 * @details Specified setting for sensitivity of Accel 23 Click driver.
 */
#define ACCEL23_ACCEL_SENS_G_PER_LSB            0.000061
#define ACCEL23_TEMP_SENS_C_PER_LSB             0.045
#define ACCEL23_TEMP_OFFSET                     25.0

/**
 * @brief Accel 23 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 23 Click driver.
 */
#define ACCEL23_DEVICE_ADDRESS_0                0x18
#define ACCEL23_DEVICE_ADDRESS_1                0x19

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel23_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL23_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL23_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel23_set

/**
 * @defgroup accel23_map Accel 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 23 Click driver.
 */

/**
 * @addtogroup accel23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 23 Click to the selected MikroBUS.
 */
#define ACCEL23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.eck  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.it2  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel23_map
/*! @} */ // accel23

/**
 * @brief Accel 23 Click driver selector.
 * @details Selects target driver interface of Accel 23 Click driver.
 */
typedef enum
{
    ACCEL23_DRV_SEL_SPI,            /**< SPI driver descriptor. */
    ACCEL23_DRV_SEL_I2C             /**< I2C driver descriptor. */

} accel23_drv_t;

/**
 * @brief Accel 23 Click driver interface.
 * @details Definition of driver interface of Accel 23 Click driver.
 */
struct accel23_s;
typedef err_t ( *accel23_master_io_t )( struct accel23_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 23 Click context object.
 * @details Context object definition of Accel 23 Click driver.
 */
typedef struct accel23_s
{
    digital_out_t eck;              /**< External clock pin (unused). */

    digital_in_t it2;               /**< Interrupt 2 pin (unused). */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    accel23_drv_t drv_sel;          /**< Master driver interface selector. */

    accel23_master_io_t write_f;    /**< Master write function. */
    accel23_master_io_t read_f;     /**< Master read function. */

    float accel_sens;               /**< Accel sensitivity setting. */

} accel23_t;

/**
 * @brief Accel 23 Click configuration object.
 * @details Configuration object definition of Accel 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t eck;                 /**< External clock pin (unused). */
    pin_name_t it2;                 /**< Interrupt 2 pin (unused). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel23_drv_t drv_sel;          /**< Master driver interface selector. */

} accel23_cfg_t;

/**
 * @brief Accel 23 Click axes data structure.
 * @details Axes data object definition of Accel 23 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel23_axes_t;

/**
 * @brief Accel 23 Click data structure.
 * @details Data object definition of Accel 23 Click driver.
 */
typedef struct
{
    accel23_axes_t accel;           /**< Accel data. */
    accel23_axes_t gyro;            /**< Gyro data. */
    float temperature;              /**< Temperature data. */

} accel23_data_t;

/**
 * @brief Accel 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL23_OK = 0,
    ACCEL23_ERROR = -1,
    ACCEL23_NO_DRDY = -2

} accel23_return_value_t;

/*!
 * @addtogroup accel23 Accel 23 Click Driver
 * @brief API for configuring and manipulating Accel 23 Click driver.
 * @{
 */

/**
 * @brief Accel 23 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel23_cfg_setup ( accel23_cfg_t *cfg );

/**
 * @brief Accel 23 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel23_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel23_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel23_drv_interface_sel ( accel23_cfg_t *cfg, accel23_drv_t drv_sel );

/**
 * @brief Accel 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel23_init ( accel23_t *ctx, accel23_cfg_t *cfg );

/**
 * @brief Accel 23 default configuration function.
 * @details This function executes a default configuration of Accel 23
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel23_default_cfg ( accel23_t *ctx );

/**
 * @brief Accel 23 write register function.
 * @details This function writes a single byte of data to
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_write_reg ( accel23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 23 write registers function.
 * @details This function writes a sequence of bytes starting from
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_write_regs ( accel23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 23 read register function.
 * @details This function reads a single byte of data from
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data read from the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_read_reg ( accel23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 23 read registers function.
 * @details This function reads a sequence of bytes starting from
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_read_regs ( accel23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 23 set ECK pin function.
 * @details This function sets the state of the ECK pin.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] state : Pin state (0 or 1).
 * @return None.
 * @note None.
 */
void accel23_set_eck_pin ( accel23_t *ctx, uint8_t state );

/**
 * @brief Accel 23 get IT2 pin function.
 * @details This function returns the logic state of the IT2 pin.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel23_get_it2_pin ( accel23_t *ctx );

/**
 * @brief Accel 23 check communication function.
 * @details This function checks device communication by reading the WHO_AM_I register.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @return @li @c  0 - Communication OK,
 *         @li @c -1 - Communication Error.
 * @note None.
 */
err_t accel23_check_communication ( accel23_t *ctx );

/**
 * @brief Accel 23 SPI wake-up function.
 * @details This function wakes up the device from software power-down mode.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_spi_wake_up ( accel23_t *ctx );

/**
 * @brief Accel 23 software reset function.
 * @details This function performs a software reset by setting the SW_RESET bit in the control register.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_sw_reset ( accel23_t *ctx );

/**
 * @brief Accel 23 set output data rate function.
 * @details This function sets the output data rate (ODR) of the device.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] odr : Output data rate setting, see ACCEL23_ODR_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid ODR or Error.
 * @note None.
 */
err_t accel23_set_odr ( accel23_t *ctx, uint8_t odr );

/**
 * @brief Accel 23 set full-scale range function.
 * @details This function sets the full-scale measurement range.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale range value, see ACCEL23_FS_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid FSR or Error.
 * @note None.
 */
err_t accel23_set_fsr ( accel23_t *ctx, uint8_t fsr );

/**
 * @brief Accel 23 check data ready function.
 * @details This function checks whether new acceleration data is available.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @return @li @c  0 - Data ready,
 *         @li @c -1 - Error.
 *         @li @c -2 - Not ready.
 * @note None.
 */
err_t accel23_check_accel_drdy ( accel23_t *ctx );

/**
 * @brief Accel 23 get acceleration function.
 * @details This function reads and converts the X, Y, Z acceleration data.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[out] accel : Acceleration axes structure.
 * See #accel23_axes_t object definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Data not ready.
 * @note None.
 */
err_t accel23_get_accel ( accel23_t *ctx, accel23_axes_t *accel );

/**
 * @brief Accel 23 get temperature function.
 * @details This function reads and calculates the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[out] temp : Pointer to store temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel23_get_temp ( accel23_t *ctx, float *temp );

/**
 * @brief Accel 23 get all sensor data function.
 * @details This function retrieves acceleration and temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure containing both acceleration and temperature data.
 * See #accel23_data_t object definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Accel data not ready.
 * @note None.
 */
err_t accel23_get_data ( accel23_t *ctx, accel23_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ACCEL23_H

/*! @} */ // accel23

// ------------------------------------------------------------------------ END

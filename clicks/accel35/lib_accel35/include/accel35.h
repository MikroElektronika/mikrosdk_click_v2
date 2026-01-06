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
 * @file accel35.h
 * @brief This file contains API for Accel 35 Click Driver.
 */

#ifndef ACCEL35_H
#define ACCEL35_H

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
 * @addtogroup accel35 Accel 35 Click Driver
 * @brief API for configuring and manipulating Accel 35 Click driver.
 * @{
 */

/**
 * @defgroup accel35_reg Accel 35 Registers List
 * @brief List of registers of Accel 35 Click driver.
 */

/**
 * @addtogroup accel35_reg
 * @{
 */

/**
 * @brief Accel 35 register list.
 * @details Specified register list of Accel 35 Click driver.
 */
#define ACCEL35_REG_STATUS_AUX                  0x07
#define ACCEL35_REG_OUT_TEMP_L                  0x0C
#define ACCEL35_REG_OUT_TEMP_H                  0x0D
#define ACCEL35_REG_WHO_AM_I                    0x0F
#define ACCEL35_REG_CTRL0                       0x1E
#define ACCEL35_REG_TEMP_CFG                    0x1F
#define ACCEL35_REG_CTRL1                       0x20
#define ACCEL35_REG_CTRL2                       0x21
#define ACCEL35_REG_CTRL3                       0x22
#define ACCEL35_REG_CTRL4                       0x23
#define ACCEL35_REG_CTRL5                       0x24
#define ACCEL35_REG_CTRL6                       0x25
#define ACCEL35_REG_REFERENCE                   0x26
#define ACCEL35_REG_STATUS                      0x27
#define ACCEL35_REG_OUT_X_L                     0x28
#define ACCEL35_REG_OUT_X_H                     0x29
#define ACCEL35_REG_OUT_Y_L                     0x2A
#define ACCEL35_REG_OUT_Y_H                     0x2B
#define ACCEL35_REG_OUT_Z_L                     0x2C
#define ACCEL35_REG_OUT_Z_H                     0x2D
#define ACCEL35_REG_FIFO_CTRL                   0x2E
#define ACCEL35_REG_FIFO_SRC                    0x2F
#define ACCEL35_REG_INT1_CFG                    0x30
#define ACCEL35_REG_INT1_SRC                    0x31
#define ACCEL35_REG_INT1_THS                    0x32
#define ACCEL35_REG_INT1_DURATION               0x33
#define ACCEL35_REG_INT2_CFG                    0x34
#define ACCEL35_REG_INT2_SRC                    0x35
#define ACCEL35_REG_INT2_THS                    0x36
#define ACCEL35_REG_INT2_DURATION               0x37
#define ACCEL35_REG_CLICK_CFG                   0x38
#define ACCEL35_REG_CLICK_SRC                   0x39
#define ACCEL35_REG_CLICK_THS                   0x3A
#define ACCEL35_REG_TIME_LIMIT                  0x3B
#define ACCEL35_REG_TIME_LATENCY                0x3C
#define ACCEL35_REG_TIME_WINDOW                 0x3D
#define ACCEL35_REG_ACT_THS                     0x3E
#define ACCEL35_REG_ACT_DUR                     0x3F

/*! @} */ // accel35_reg

/**
 * @defgroup accel35_set Accel 35 Registers Settings
 * @brief Settings for registers of Accel 35 Click driver.
 */

/**
 * @addtogroup accel35_set
 * @{
 */

/**
 * @brief Accel 35 STATUS_AUX register setting.
 * @details Specified setting for STATUS_AUX register of Accel 35 Click driver.
 */
#define ACCEL35_STATUS_AUX_TOR                  0x40
#define ACCEL35_STATUS_AUX_TDA                  0x04

/**
 * @brief Accel 35 TEMP_CFG register setting.
 * @details Specified setting for TEMP_CFG register of Accel 35 Click driver.
 */
#define ACCEL35_TEMP_CFG_TEMP_DISABLE           0x00
#define ACCEL35_TEMP_CFG_TEMP_ENABLE            0xC0

/**
 * @brief Accel 35 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of Accel 35 Click driver.
 */
#define ACCEL35_WHO_AM_I                        0x33

/**
 * @brief Accel 35 CTRL1 register setting.
 * @details Specified setting for CTRL1 register of Accel 35 Click driver.
 */
#define ACCEL35_CTRL1_ODR_POWER_DOWN            0x00
#define ACCEL35_CTRL1_ODR_1_HZ                  0x10
#define ACCEL35_CTRL1_ODR_10_HZ                 0x20
#define ACCEL35_CTRL1_ODR_25_HZ                 0x30
#define ACCEL35_CTRL1_ODR_50_HZ                 0x40
#define ACCEL35_CTRL1_ODR_100_HZ                0x50
#define ACCEL35_CTRL1_ODR_200_HZ                0x60
#define ACCEL35_CTRL1_ODR_400_HZ                0x70
#define ACCEL35_CTRL1_ODR_1620_HZ               0x80
#define ACCEL35_CTRL1_ODR_5376_HZ               0x90
#define ACCEL35_CTRL1_ODR_MASK                  0xF0
#define ACCEL35_CTRL1_LPEN                      0x08
#define ACCEL35_CTRL1_ZEN                       0x04
#define ACCEL35_CTRL1_YEN                       0x02
#define ACCEL35_CTRL1_XEN                       0x01

/**
 * @brief Accel 35 CTRL4 register setting.
 * @details Specified setting for CTRL4 register of Accel 35 Click driver.
 */
#define ACCEL35_CTRL4_BDU                       0x80
#define ACCEL35_CTRL4_FS_2G                     0x00
#define ACCEL35_CTRL4_FS_4G                     0x10
#define ACCEL35_CTRL4_FS_8G                     0x20
#define ACCEL35_CTRL4_FS_16G                    0x30
#define ACCEL35_CTRL4_FS_MASK                   0x30
#define ACCEL35_CTRL4_ST_NORMAL                 0x00
#define ACCEL35_CTRL4_ST_SELF_TEST_0            0x02
#define ACCEL35_CTRL4_ST_SELF_TEST_1            0x04
#define ACCEL35_CTRL4_ST_MASK                   0x06
#define ACCEL35_CTRL4_SIM_4_WIRE                0x00
#define ACCEL35_CTRL4_SIM_3_WIRE                0x01
#define ACCEL35_CTRL4_SIM_MASK                  0x01

/**
 * @brief Accel 35 STATUS register setting.
 * @details Specified setting for STATUS register of Accel 35 Click driver.
 */
#define ACCEL35_STATUS_ZYXOR                    0x80
#define ACCEL35_STATUS_ZOR                      0x40
#define ACCEL35_STATUS_YOR                      0x20
#define ACCEL35_STATUS_XOR                      0x10
#define ACCEL35_STATUS_ZYXDA                    0x08
#define ACCEL35_STATUS_ZDA                      0x04
#define ACCEL35_STATUS_YDA                      0x02
#define ACCEL35_STATUS_XDA                      0x01

/**
 * @brief Accel 35 output data rate setting.
 * @details Specified setting for output data rate of Accel 35 Click driver.
 */
#define ACCEL35_ODR_POWER_DOWN                  0
#define ACCEL35_ODR_1_HZ                        1
#define ACCEL35_ODR_10_HZ                       2
#define ACCEL35_ODR_25_HZ                       3
#define ACCEL35_ODR_50_HZ                       4
#define ACCEL35_ODR_100_HZ                      5
#define ACCEL35_ODR_200_HZ                      6
#define ACCEL35_ODR_400_HZ                      7
#define ACCEL35_ODR_1620_HZ                     8
#define ACCEL35_ODR_5376_HZ                     9

/**
 * @brief Accel 35 full scale setting.
 * @details Specified setting for full scale of Accel 35 Click driver.
 */
#define ACCEL35_FS_2G                           0
#define ACCEL35_FS_4G                           1
#define ACCEL35_FS_8G                           2
#define ACCEL35_FS_16G                          3

/**
 * @brief Accel 35 sensitivity setting.
 * @details Specified setting for sensitivity of Accel 35 Click driver.
 */
#define ACCEL35_ACCEL_SENS_G_PER_LSB            0.0156
#define ACCEL35_TEMP_SENS_C_PER_LSB             1.0
#define ACCEL35_TEMP_OFFSET                     25.0

/**
 * @brief Accel 35 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 35 Click driver.
 */
#define ACCEL35_DEVICE_ADDRESS_0                0x18
#define ACCEL35_DEVICE_ADDRESS_1                0x19

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel35_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL35_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL35_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel35_set

/**
 * @defgroup accel35_map Accel 35 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 35 Click driver.
 */

/**
 * @addtogroup accel35_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 35 Click to the selected MikroBUS.
 */
#define ACCEL35_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.it2  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.it1  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel35_map
/*! @} */ // accel35

/**
 * @brief Accel 35 Click driver selector.
 * @details Selects target driver interface of Accel 35 Click driver.
 */
typedef enum
{
    ACCEL35_DRV_SEL_SPI,            /**< SPI driver descriptor. */
    ACCEL35_DRV_SEL_I2C             /**< I2C driver descriptor. */

} accel35_drv_t;

/**
 * @brief Accel 35 Click driver interface.
 * @details Definition of driver interface of Accel 35 Click driver.
 */
struct accel35_s;
typedef err_t ( *accel35_master_io_t )( struct accel35_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 35 Click context object.
 * @details Context object definition of Accel 35 Click driver.
 */
typedef struct accel35_s
{
    digital_in_t it2;               /**< Interrupt 2 pin (unused). */
    digital_in_t it1;               /**< Interrupt 1 pin (unused). */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    accel35_drv_t drv_sel;          /**< Master driver interface selector. */

    accel35_master_io_t write_f;    /**< Master write function. */
    accel35_master_io_t read_f;     /**< Master read function. */

    float accel_sens;               /**< Accel sensitivity setting. */

} accel35_t;

/**
 * @brief Accel 35 Click configuration object.
 * @details Configuration object definition of Accel 35 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t it2;                 /**< Interrupt 2 pin (unused). */
    pin_name_t it1;                 /**< Interrupt 1 pin (unused). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel35_drv_t drv_sel;          /**< Master driver interface selector. */

} accel35_cfg_t;

/**
 * @brief Accel 35 Click axes data structure.
 * @details Axes data object definition of Accel 35 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel35_axes_t;

/**
 * @brief Accel 35 Click data structure.
 * @details Data object definition of Accel 35 Click driver.
 */
typedef struct
{
    accel35_axes_t accel;           /**< Accel data. */
    float temperature;              /**< Temperature data. */

} accel35_data_t;

/**
 * @brief Accel 35 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL35_OK = 0,
    ACCEL35_ERROR = -1,
    ACCEL35_NO_DRDY = -2

} accel35_return_value_t;

/*!
 * @addtogroup accel35 Accel 35 Click Driver
 * @brief API for configuring and manipulating Accel 35 Click driver.
 * @{
 */

/**
 * @brief Accel 35 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel35_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel35_cfg_setup ( accel35_cfg_t *cfg );

/**
 * @brief Accel 35 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel35_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel35_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel35_drv_interface_sel ( accel35_cfg_t *cfg, accel35_drv_t drv_sel );

/**
 * @brief Accel 35 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel35_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel35_init ( accel35_t *ctx, accel35_cfg_t *cfg );

/**
 * @brief Accel 35 default configuration function.
 * @details This function executes a default configuration of Accel 35
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel35_default_cfg ( accel35_t *ctx );

/**
 * @brief Accel 35 write register function.
 * @details This function writes a single byte of data to
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_write_reg ( accel35_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 35 write registers function.
 * @details This function writes a sequence of bytes starting from
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_write_regs ( accel35_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 35 read register function.
 * @details This function reads a single byte of data from
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data read from the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_read_reg ( accel35_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 35 read registers function.
 * @details This function reads a sequence of bytes starting from
 * the selected register by using the communication interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_read_regs ( accel35_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 35 get IT1 pin function.
 * @details This function returns the logic state of the IT1 pin.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel35_get_it1_pin ( accel35_t *ctx );

/**
 * @brief Accel 35 get IT2 pin function.
 * @details This function returns the logic state of the IT2 pin.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel35_get_it2_pin ( accel35_t *ctx );

/**
 * @brief Accel 23 check communication function.
 * @details This function checks device communication by reading the WHO_AM_I register.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return @li @c  0 - Communication OK,
 *         @li @c -1 - Communication Error.
 * @note None.
 */
err_t accel35_check_communication ( accel35_t *ctx );

/**
 * @brief Accel 35 set output data rate function.
 * @details This function sets the output data rate (ODR) of the device.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] odr : Output data rate setting, see ACCEL35_ODR_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid ODR or Error.
 * @note None.
 */
err_t accel35_set_odr ( accel35_t *ctx, uint8_t odr );

/**
 * @brief Accel 35 set full-scale range function.
 * @details This function sets the full-scale measurement range.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale range value, see ACCEL35_FS_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid FSR or Error.
 * @note None.
 */
err_t accel35_set_fsr ( accel35_t *ctx, uint8_t fsr );

/**
 * @brief Accel 35 enable temp sensor function.
 * @details This function enables internal temperature sensor.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_enable_temp_sensor ( accel35_t *ctx );

/**
 * @brief Accel 35 disable temp sensor function.
 * @details This function disables internal temperature sensor.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_disable_temp_sensor ( accel35_t *ctx );

/**
 * @brief Accel 35 check data ready function.
 * @details This function checks whether new acceleration data is available.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return @li @c  0 - Data ready,
 *         @li @c -1 - Error.
 *         @li @c -2 - Not ready.
 * @note None.
 */
err_t accel35_check_accel_drdy ( accel35_t *ctx );

/**
 * @brief Accel 35 get acceleration function.
 * @details This function reads and converts the X, Y, Z acceleration data.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[out] accel : Acceleration axes structure.
 * See #accel35_axes_t object definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Data not ready.
 * @note None.
 */
err_t accel35_get_accel ( accel35_t *ctx, accel35_axes_t *accel );

/**
 * @brief Accel 35 check temp ready function.
 * @details This function checks whether new temperature data is available.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @return @li @c  0 - Data ready,
 *         @li @c -1 - Error.
 *         @li @c -2 - Not ready.
 * @note None.
 */
err_t accel35_check_temp_drdy ( accel35_t *ctx );

/**
 * @brief Accel 35 get temperature function.
 * @details This function reads and calculates the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[out] temp : Pointer to store temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel35_get_temp ( accel35_t *ctx, float *temp );

/**
 * @brief Accel 35 get all sensor data function.
 * @details This function retrieves acceleration and temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure containing both acceleration and temperature data.
 * See #accel35_data_t object definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Accel data not ready.
 * @note None.
 */
err_t accel35_get_data ( accel35_t *ctx, accel35_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ACCEL35_H

/*! @} */ // accel35

// ------------------------------------------------------------------------ END

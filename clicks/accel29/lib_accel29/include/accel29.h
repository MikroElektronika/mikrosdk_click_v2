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
 * @file accel29.h
 * @brief This file contains API for Accel 29 Click Driver.
 */

#ifndef ACCEL29_H
#define ACCEL29_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup accel29 Accel 29 Click Driver
 * @brief API for configuring and manipulating Accel 29 Click driver.
 * @{
 */

/**
 * @defgroup accel29_reg Accel 29 Registers List
 * @brief List of registers of Accel 29 Click driver.
 */

/**
 * @addtogroup accel29_reg
 * @{
 */

/**
 * @brief Accel 29 register map.
 * @details Specified register map of Accel 29 Click driver.
 */
#define ACCEL29_REG_DEVID                   0x00
#define ACCEL29_REG_OFSX                    0x1E
#define ACCEL29_REG_OFSY                    0x1F
#define ACCEL29_REG_OFSZ                    0x20
#define ACCEL29_REG_THRESH_ACT              0x24
#define ACCEL29_REG_THRESH_INACT            0x25
#define ACCEL29_REG_TIME_INACT              0x26
#define ACCEL29_REG_ACT_INACT_CTL           0x27
#define ACCEL29_REG_BW_RATE                 0x2C
#define ACCEL29_REG_POWER_CTL               0x2D
#define ACCEL29_REG_INT_ENABLE              0x2E
#define ACCEL29_REG_INT_MAP                 0x2F
#define ACCEL29_REG_INT_SOURCE              0x30
#define ACCEL29_REG_DATA_FORMAT             0x31
#define ACCEL29_REG_DATA_X0                 0x32
#define ACCEL29_REG_DATA_X1                 0x33
#define ACCEL29_REG_DATA_Y0                 0x34
#define ACCEL29_REG_DATA_Y1                 0x35
#define ACCEL29_REG_DATA_Z0                 0x36
#define ACCEL29_REG_DATA_Z1                 0x37
#define ACCEL29_REG_FIFO_CTL                0x38
#define ACCEL29_REG_FIFO_STATUS             0x39

/*! @} */ // accel29_reg

/**
 * @defgroup accel29_set Accel 29 Registers Settings
 * @brief Settings for registers of Accel 29 Click driver.
 */

/**
 * @addtogroup accel29_set
 * @{
 */

/**
 * @brief Accel 29 INT_ENABLE register setting.
 * @details Specified setting for INT_ENABLE register of Accel 29 Click driver.
 */
#define ACCEL29_INT_ENABLE_DATA_READY       0x80
#define ACCEL29_INT_ENABLE_ACTIVITY         0x10
#define ACCEL29_INT_ENABLE_INACTIVITY       0x08
#define ACCEL29_INT_ENABLE_OVERRUN          0x01

/**
 * @brief Accel 29 INT_MAP register setting.
 * @details Specified setting for INT_MAP register of Accel 29 Click driver.
 */
#define ACCEL29_INT_MAP_DATA_READY_INT2     0x80
#define ACCEL29_INT_MAP_DATA_READY_INT1     0x00
#define ACCEL29_INT_MAP_DATA_READY_MASK     0x80
#define ACCEL29_INT_MAP_ACTIVITY_INT2       0x10
#define ACCEL29_INT_MAP_ACTIVITY_INT1       0x00
#define ACCEL29_INT_MAP_ACTIVITY_MASK       0x10
#define ACCEL29_INT_MAP_INACTIVITY_INT2     0x08
#define ACCEL29_INT_MAP_INACTIVITY_INT1     0x00
#define ACCEL29_INT_MAP_INACTIVITY_MASK     0x08
#define ACCEL29_INT_MAP_OVERRUN_INT2        0x01
#define ACCEL29_INT_MAP_OVERRUN_INT1        0x00
#define ACCEL29_INT_MAP_OVERRUN_MASK        0x01

/**
 * @brief Accel 29 INT_SOURCE register setting.
 * @details Specified setting for INT_SOURCE register of Accel 29 Click driver.
 */
#define ACCEL29_INT_SOURCE_DATA_READY       0x80
#define ACCEL29_INT_SOURCE_ACTIVITY         0x10
#define ACCEL29_INT_SOURCE_INACTIVITY       0x08
#define ACCEL29_INT_SOURCE_OVERRUN          0x01

/**
 * @brief Accel 29 BW_RATE register setting.
 * @details Specified setting for BW_RATE register of Accel 29 Click driver.
 */
#define ACCEL29_BW_RATE_LOW_POWER           0x10
#define ACCEL29_BW_RATE_6_25_HZ             0x06
#define ACCEL29_BW_RATE_12_5_HZ             0x07
#define ACCEL29_BW_RATE_25_HZ               0x08
#define ACCEL29_BW_RATE_50_HZ               0x09
#define ACCEL29_BW_RATE_100_HZ              0x0A
#define ACCEL29_BW_RATE_200_HZ              0x0B
#define ACCEL29_BW_RATE_400_HZ              0x0C
#define ACCEL29_BW_RATE_800_HZ              0x0D
#define ACCEL29_BW_RATE_1600_HZ             0x0E
#define ACCEL29_BW_RATE_3200_HZ             0x0F

/**
 * @brief Accel 29 POWER_CTL register setting.
 * @details Specified setting for POWER_CTL register of Accel 29 Click driver.
 */
#define ACCEL29_POWER_CTL_LINK              0x20
#define ACCEL29_POWER_CTL_AUTO_SLEEP        0x10
#define ACCEL29_POWER_CTL_MEASURE           0x08
#define ACCEL29_POWER_CTL_SLEEP             0x04
#define ACCEL29_POWER_CTL_WAKEUP_8_HZ       0x00
#define ACCEL29_POWER_CTL_WAKEUP_4_HZ       0x01
#define ACCEL29_POWER_CTL_WAKEUP_2_HZ       0x02
#define ACCEL29_POWER_CTL_WAKEUP_1_HZ       0x03
#define ACCEL29_POWER_CTL_WAKEUP_MASK       0x03

/**
 * @brief Accel 29 device ID setting.
 * @details Specified setting for device ID of Accel 29 Click driver.
 */
#define ACCEL29_DEVID                       0xE5

/**
 * @brief Accel 29 offset settings.
 * @details Specified offset settings of Accel 29 Click driver.
 */
#define ACCEL29_OFS_RESET                   0
#define ACCEL29_OFS_SCALE_FACTOR_G_PER_LSB  0.195f

/**
 * @brief Accel 29 data resolution settings.
 * @details Specified data resolution settings of Accel 29 Click driver.
 */
#define ACCEL29_SCALE_FACTOR_LSB_PER_G      20.48f

/**
 * @brief Accel 29 number of data samples for averaging.
 * @details Specified number of data samples for averaging of Accel 29 Click driver.
 */
#define ACCEL29_NUM_OF_SAMPLES              100

/**
 * @brief Accel 29 communication frame setting.
 * @details Specified setting for communication frame of Accel 29 Click driver.
 */
#define ACCEL29_SPI_RW_BIT                  0x80
#define ACCEL29_SPI_MB_BIT                  0x40
#define ACCEL29_ADDRESS_MASK                0x3F

/**
 * @brief Accel 29 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 29 Click driver.
 */
#define ACCEL29_DEVICE_ADDRESS_0            0x53
#define ACCEL29_DEVICE_ADDRESS_1            0x1D

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel29_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL29_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL29_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel29_set

/**
 * @defgroup accel29_map Accel 29 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 29 Click driver.
 */

/**
 * @addtogroup accel29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 29 Click to the selected MikroBUS.
 */
#define ACCEL29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel29_map
/*! @} */ // accel29

/**
 * @brief Accel 29 Click driver selector.
 * @details Selects target driver interface of Accel 29 Click driver.
 */
typedef enum
{
    ACCEL29_DRV_SEL_SPI,                /**< SPI driver descriptor. */
    ACCEL29_DRV_SEL_I2C                 /**< I2C driver descriptor. */

} accel29_drv_t;

/**
 * @brief Accel 29 Click driver interface.
 * @details Definition of driver interface of Accel 29 Click driver.
 */
typedef err_t ( *accel29_master_io_t )( struct accel29_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 29 Click context object.
 * @details Context object definition of Accel 29 Click driver.
 */
typedef struct accel29_s
{
    digital_in_t int1;                  /**< Interrupt 1 pin. */
    digital_in_t int2;                  /**< Interrupt 2 pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    accel29_drv_t drv_sel;              /**< Master driver interface selector. */

    accel29_master_io_t write_f;        /**< Master write function. */
    accel29_master_io_t read_f;         /**< Master read function. */

} accel29_t;

/**
 * @brief Accel 29 Click configuration object.
 * @details Configuration object definition of Accel 29 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int1;                    /**< Interrupt 1 pin. */
    pin_name_t int2;                    /**< Interrupt 2 pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel29_drv_t drv_sel;              /**< Master driver interface selector. */

} accel29_cfg_t;

/**
 * @brief Accel 29 Click Axes data structure.
 * @details Axes data object definition of Accel 29 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel29_axes_t;

/**
 * @brief Accel 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL29_OK = 0,
    ACCEL29_ERROR = -1

} accel29_return_value_t;

/*!
 * @addtogroup accel29 Accel 29 Click Driver
 * @brief API for configuring and manipulating Accel 29 Click driver.
 * @{
 */

/**
 * @brief Accel 29 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel29_cfg_setup ( accel29_cfg_t *cfg );

/**
 * @brief Accel 29 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel29_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel29_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel29_drv_interface_selection ( accel29_cfg_t *cfg, accel29_drv_t drv_sel );

/**
 * @brief Accel 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_init ( accel29_t *ctx, accel29_cfg_t *cfg );

/**
 * @brief Accel 29 default configuration function.
 * @details This function executes a default configuration of Accel 29
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel29_default_cfg ( accel29_t *ctx );

/**
 * @brief Accel 29 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_generic_write ( accel29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 29 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_generic_read ( accel29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 29 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_write_register ( accel29_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 29 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_read_register ( accel29_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 29 check communication function.
 * @details This function checks the communication by reading and verifying the device ID bytes.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_check_communication ( accel29_t *ctx );

/**
 * @brief Accel 29 get int1 pin function.
 * @details This function returns the interrupt 1 (INT1) pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel29_get_int1_pin ( accel29_t *ctx );

/**
 * @brief Accel 29 get int2 pin function.
 * @details This function returns the interrupt 2 (INT2) pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel29_get_int2_pin ( accel29_t *ctx );

/**
 * @brief Accel 29 get axes function.
 * @details This function reads accel X, Y, and Z axis data in g.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[out] axes : X, Y, and Z axis data in g.
 * See #accel29_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_get_axes ( accel29_t *ctx, accel29_axes_t *axes );

/**
 * @brief Accel 29 get avg axes function.
 * @details This function reads a specified number of samples for accel X, Y, and Z axis data in g
 * and averages them.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] num_samples : Number of data samples for averaging.
 * @param[out] avg_axes : Average X, Y, and Z axis data in g.
 * See #accel29_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_get_avg_axes ( accel29_t *ctx, uint16_t num_samples, accel29_axes_t *avg_axes );

/**
 * @brief Accel 29 calibrate offset function.
 * @details This function calibrates accel offset to the specified values by setting the OFSX/Y/Z registers.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[out] calib_axes : Calibration X, Y, and Z axis data in g. Axis data should be in a range from -24.96 to 24.765 g.
 * Offset calibrating scale factor is 0.195 g per LSB.
 * See #accel29_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel29_calibrate_offset ( accel29_t *ctx, accel29_axes_t calib_axes );

#ifdef __cplusplus
}
#endif
#endif // ACCEL29_H

/*! @} */ // accel29

// ------------------------------------------------------------------------ END

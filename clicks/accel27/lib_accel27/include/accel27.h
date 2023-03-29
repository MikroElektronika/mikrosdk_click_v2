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
 * @file accel27.h
 * @brief This file contains API for Accel 27 Click Driver.
 */

#ifndef ACCEL27_H
#define ACCEL27_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup accel27 Accel 27 Click Driver
 * @brief API for configuring and manipulating Accel 27 Click driver.
 * @{
 */

/**
 * @defgroup accel27_reg Accel 27 Registers List
 * @brief List of registers of Accel 27 Click driver.
 */

/**
 * @addtogroup accel27_reg
 * @{
 */

/**
 * @brief Accel 27 register map.
 * @details Specified register map of Accel 27 Click driver.
 */
#define ACCEL27_REG_DEVID_AD                0x00
#define ACCEL27_REG_DEVID_MST               0x01
#define ACCEL27_REG_PARTID                  0x02
#define ACCEL27_REG_REVID                   0x03
#define ACCEL27_REG_STATUS                  0x04
#define ACCEL27_REG_STATUS2                 0x05
#define ACCEL27_REG_FIFO_ENTRIES2           0x06
#define ACCEL27_REG_FIFO_ENTRIES            0x07
#define ACCEL27_REG_XDATA_H                 0x08
#define ACCEL27_REG_XDATA_L                 0x09
#define ACCEL27_REG_YDATA_H                 0x0A
#define ACCEL27_REG_YDATA_L                 0x0B
#define ACCEL27_REG_ZDATA_H                 0x0C
#define ACCEL27_REG_ZDATA_L                 0x0D
#define ACCEL27_REG_MAXPEAK_X_H             0x15
#define ACCEL27_REG_MAXPEAK_X_L             0x16
#define ACCEL27_REG_MAXPEAK_Y_H             0x17
#define ACCEL27_REG_MAXPEAK_Y_L             0x18
#define ACCEL27_REG_MAXPEAK_Z_H             0x19
#define ACCEL27_REG_MAXPEAK_Z_L             0x1A
#define ACCEL27_REG_OFFSET_X                0x20
#define ACCEL27_REG_OFFSET_Y                0x21
#define ACCEL27_REG_OFFSET_Z                0x22
#define ACCEL27_REG_THRESH_ACT_X_H          0x23
#define ACCEL27_REG_THRESH_ACT_X_L          0x24
#define ACCEL27_REG_THRESH_ACT_Y_H          0x25
#define ACCEL27_REG_THRESH_ACT_Y_L          0x26
#define ACCEL27_REG_THRESH_ACT_Z_H          0x27
#define ACCEL27_REG_THRESH_ACT_Z_L          0x28
#define ACCEL27_REG_TIME_ACT                0x29
#define ACCEL27_REG_THRESH_INACT_X_H        0x2A
#define ACCEL27_REG_THRESH_INACT_X_L        0x2B
#define ACCEL27_REG_THRESH_INACT_Y_H        0x2C
#define ACCEL27_REG_THRESH_INACT_Y_L        0x2D
#define ACCEL27_REG_THRESH_INACT_Z_H        0x2E
#define ACCEL27_REG_THRESH_INACT_Z_L        0x2F
#define ACCEL27_REG_TIME_INACT_H            0x30
#define ACCEL27_REG_TIME_INACT_L            0x31
#define ACCEL27_REG_THRESH_ACT2_X_H         0x32
#define ACCEL27_REG_THRESH_ACT2_X_L         0x33
#define ACCEL27_REG_THRESH_ACT2_Y_H         0x34
#define ACCEL27_REG_THRESH_ACT2_Y_L         0x35
#define ACCEL27_REG_THRESH_ACT2_Z_H         0x36
#define ACCEL27_REG_THRESH_ACT2_Z_L         0x37
#define ACCEL27_REG_HPF                     0x38
#define ACCEL27_REG_FIFO_SAMPLES            0x39
#define ACCEL27_REG_FIFO_CTL                0x3A
#define ACCEL27_REG_INT1_MAP                0x3B
#define ACCEL27_REG_INT2_MAP                0x3C
#define ACCEL27_REG_TIMING                  0x3D
#define ACCEL27_REG_MEASURE                 0x3E
#define ACCEL27_REG_POWER_CTL               0x3F
#define ACCEL27_REG_SELF_TEST               0x40
#define ACCEL27_REG_RESET                   0x41
#define ACCEL27_REG_FIFO_DATA               0x42

/*! @} */ // accel27_reg

/**
 * @defgroup accel27_set Accel 27 Registers Settings
 * @brief Settings for registers of Accel 27 Click driver.
 */

/**
 * @addtogroup accel27_set
 * @{
 */

/**
 * @brief Accel 27 INT_MAP register settings.
 * @details Specified INT_MAP register settings of Accel 27 Click driver.
 */
#define ACCEL27_INT_MAP_INT_LOW             0x80
#define ACCEL27_INT_MAP_AWAKE               0x40
#define ACCEL27_INT_MAP_ACT                 0x20
#define ACCEL27_INT_MAP_INACT               0x10
#define ACCEL27_INT_MAP_DATA_RDY            0x01

/**
 * @brief Accel 27 TIMING register settings.
 * @details Specified TIMING register settings of Accel 27 Click driver.
 */
#define ACCEL27_TIMING_ODR_320HZ            0x00
#define ACCEL27_TIMING_ODR_640HZ            0x20
#define ACCEL27_TIMING_ODR_1280HZ           0x40
#define ACCEL27_TIMING_ODR_25600HZ          0x60
#define ACCEL27_TIMING_ODR_5120HZ           0x80
#define ACCEL27_TIMING_ODR_MASK             0xE0
#define ACCEL27_TIMING_WAKEUP_RATE_65_MS    0x00
#define ACCEL27_TIMING_WAKEUP_RATE_130_MS   0x04
#define ACCEL27_TIMING_WAKEUP_RATE_260_MS   0x08
#define ACCEL27_TIMING_WAKEUP_RATE_640_MS   0x0C
#define ACCEL27_TIMING_WAKEUP_RATE_2560_MS  0x10
#define ACCEL27_TIMING_WAKEUP_RATE_5120_MS  0x14
#define ACCEL27_TIMING_WAKEUP_RATE_10240_MS 0x18
#define ACCEL27_TIMING_WAKEUP_RATE_30720_MS 0x1C
#define ACCEL27_TIMING_WAKEUP_RATE_MASK     0x1C
#define ACCEL27_TIMING_EXT_CLK              0x02
#define ACCEL27_TIMING_EXT_SYNC             0x01

/**
 * @brief Accel 27 POWER_CTL register settings.
 * @details Specified POWER_CTL register settings of Accel 27 Click driver.
 */
#define ACCEL27_POWER_CTL_I2C_HSM_EN        0x80
#define ACCEL27_POWER_CTL_INSTANT_ON_THRESH 0x20
#define ACCEL27_POWER_CTL_FLT_SETL_462_5_MS 0x00
#define ACCEL27_POWER_CTL_FLT_SETL_4_OF_ODR 0x10
#define ACCEL27_POWER_CTL_FLT_SETL_MASK     0x10
#define ACCEL27_POWER_CTL_LPF_DISABLE       0x08
#define ACCEL27_POWER_CTL_HPF_DISABLE       0x04
#define ACCEL27_POWER_CTL_MODE_STANDBY      0x00
#define ACCEL27_POWER_CTL_MODE_WAKE_UP      0x01
#define ACCEL27_POWER_CTL_MODE_INSTANT_ON   0x02
#define ACCEL27_POWER_CTL_MODE_MEASUREMENT  0x03
#define ACCEL27_POWER_CTL_MODE_MASK         0x03

/**
 * @brief Accel 27 RESET register settings.
 * @details Specified RESET register settings of Accel 27 Click driver.
 */
#define ACCEL27_RESET                       0x52

/**
 * @brief Accel 27 device ID setting.
 * @details Specified setting for device ID of Accel 27 Click driver.
 */
#define ACCEL27_DEVID_AD                    0xAD
#define ACCEL27_DEVID_MST                   0x1D
#define ACCEL27_DEVID_PRODUCT               0xFA

/**
 * @brief Accel 27 data resolution settings.
 * @details Specified data resolution settings of Accel 27 Click driver.
 */
#define ACCEL27_SCALE_FACTOR_LSB_PER_G      5.0f

/**
 * @brief Accel 27 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 27 Click driver.
 */
#define ACCEL27_DEVICE_ADDRESS_0            0x1D
#define ACCEL27_DEVICE_ADDRESS_1            0x53

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel27_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL27_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL27_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel27_set

/**
 * @defgroup accel27_map Accel 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 27 Click driver.
 */

/**
 * @addtogroup accel27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 27 Click to the selected MikroBUS.
 */
#define ACCEL27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel27_map
/*! @} */ // accel27

/**
 * @brief Accel 27 Click driver selector.
 * @details Selects target driver interface of Accel 27 Click driver.
 */
typedef enum
{
    ACCEL27_DRV_SEL_SPI,            /**< SPI driver descriptor. */
    ACCEL27_DRV_SEL_I2C             /**< I2C driver descriptor. */

} accel27_drv_t;

/**
 * @brief Accel 27 Click driver interface.
 * @details Definition of driver interface of Accel 27 Click driver.
 */
typedef err_t ( *accel27_master_io_t )( struct accel27_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 27 Click context object.
 * @details Context object definition of Accel 27 Click driver.
 */
typedef struct accel27_s
{
    digital_in_t int2;              /**< Interrupt 2 pin. */
    digital_in_t int1;              /**< Interrupt 1 pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    accel27_drv_t drv_sel;          /**< Master driver interface selector. */

    accel27_master_io_t write_f;    /**< Master write function. */
    accel27_master_io_t read_f;     /**< Master read function. */

} accel27_t;

/**
 * @brief Accel 27 Click configuration object.
 * @details Configuration object definition of Accel 27 Click driver.
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

    accel27_drv_t drv_sel;          /**< Master driver interface selector. */

} accel27_cfg_t;

/**
 * @brief Accel 27 Click Axes data structure.
 * @details Axes data object definition of Accel 27 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel27_axes_t;

/**
 * @brief Accel 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL27_OK = 0,
    ACCEL27_ERROR = -1

} accel27_return_value_t;

/*!
 * @addtogroup accel27 Accel 27 Click Driver
 * @brief API for configuring and manipulating Accel 27 Click driver.
 * @{
 */

/**
 * @brief Accel 27 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel27_cfg_setup ( accel27_cfg_t *cfg );

/**
 * @brief Accel 27 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel27_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel27_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel27_drv_interface_selection ( accel27_cfg_t *cfg, accel27_drv_t drv_sel );

/**
 * @brief Accel 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_init ( accel27_t *ctx, accel27_cfg_t *cfg );

/**
 * @brief Accel 27 default configuration function.
 * @details This function executes a default configuration of Accel 27
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel27_default_cfg ( accel27_t *ctx );

/**
 * @brief Accel 27 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_generic_write ( accel27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 27 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_generic_read ( accel27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 27 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_write_register ( accel27_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 27 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_read_register ( accel27_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 27 check communication function.
 * @details This function checks the communication by reading and verifying the device ID bytes.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_check_communication ( accel27_t *ctx );

/**
 * @brief Accel 27 get int1 pin function.
 * @details This function returns the interrupt 1 (INT1) pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel27_get_int1_pin ( accel27_t *ctx );

/**
 * @brief Accel 27 get int2 pin function.
 * @details This function returns the interrupt 2 (INT2) pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel27_get_int2_pin ( accel27_t *ctx );

/**
 * @brief Accel 27 get axes function.
 * @details This function reads accel X, Y, and Z axis data in g.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[out] axes : X, Y, and Z axis data in g.
 * See #accel27_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_get_axes ( accel27_t *ctx, accel27_axes_t *axes );

/**
 * @brief Accel 27 reset device function.
 * @details This function performs the chip software reset.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel27_reset_device ( accel27_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL27_H

/*! @} */ // accel27

// ------------------------------------------------------------------------ END

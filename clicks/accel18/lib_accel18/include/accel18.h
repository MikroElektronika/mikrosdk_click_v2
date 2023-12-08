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
 * @file accel18.h
 * @brief This file contains API for Accel 18 Click Driver.
 */

#ifndef ACCEL18_H
#define ACCEL18_H

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
 * @addtogroup accel18 Accel 18 Click Driver
 * @brief API for configuring and manipulating Accel 18 Click driver.
 * @{
 */

/**
 * @defgroup accel18_reg Accel 18 Registers List
 * @brief List of registers of Accel 18 Click driver.
 */

/**
 * @addtogroup accel18_reg
 * @{
 */

/**
 * @brief Accel 18 description register.
 * @details Specified register for description of Accel 18 Click driver.
 */
#define ACCEL18_REG_DEVICE_STATUS                       0x05
#define ACCEL18_REG_INTERRUPT_ENABLE                    0x06
#define ACCEL18_REG_MODE                                0x07
#define ACCEL18_REG_SAMPLE_RATE                         0x08
#define ACCEL18_REG_MOTION_CONTROL                      0x09
#define ACCEL18_REG_FIFO_STATUS                         0x0A
#define ACCEL18_REG_FIFO_READ_POINTER                   0x0B
#define ACCEL18_REG_FIFO_WRITE_POINTER                  0x0C
#define ACCEL18_REG_XOUT_ACCEL_DATA_LSB                 0x0D
#define ACCEL18_REG_XOUT_ACCEL_DATA_MSB                 0x0E
#define ACCEL18_REG_YOUT_ACCEL_DATA_LSB                 0x0F
#define ACCEL18_REG_YOUT_ACCEL_DATA_MSB                 0x10
#define ACCEL18_REG_ZOUT_ACCEL_DATA_LSB                 0x11
#define ACCEL18_REG_ZOUT_ACCEL_DATA_MSB                 0x12
#define ACCEL18_REG_STATUS                              0x13
#define ACCEL18_REG_INTERRUPT_STATUS                    0x14
#define ACCEL18_REG_RANGE_SELECTION                     0x20
#define ACCEL18_REG_X_OFFSET_LSB                        0x21
#define ACCEL18_REG_X_OFFSET_MSB                        0x22
#define ACCEL18_REG_Y_OFFSET_LSB                        0x23
#define ACCEL18_REG_Y_OFFSET_MSB                        0x24
#define ACCEL18_REG_Z_OFFSET_LSB                        0x25
#define ACCEL18_REG_Z_OFFSET_MSB                        0x26
#define ACCEL18_REG_X_GAIN                              0x27
#define ACCEL18_REG_Y_GAIN                              0x28
#define ACCEL18_REG_Z_GAIN                              0x29
#define ACCEL18_REG_FIFO_CONTROL                        0x2D
#define ACCEL18_REG_FIFO_THRESHOLD                      0x2E
#define ACCEL18_REG_FIFO_INTERRUPT_STATUS               0x2F
#define ACCEL18_REG_FIFO_CONTROL2                       0x30
#define ACCEL18_REG_COMMUNICATION_CONTROL               0x31
#define ACCEL18_REG_GPIO_CONTROL                        0x33
#define ACCEL18_REG_TILT_FLIP_THRESHOLD_LSB             0x40
#define ACCEL18_REG_TILT_FLIP_THRESHOLD_MSB             0x41
#define ACCEL18_REG_TILT_FLIP_DEBOUNCE                  0x42
#define ACCEL18_REG_ANY_MOTION_THRESHOLD_LSB            0x43
#define ACCEL18_REG_ANY_MOTION_THRESHOLD_MSB            0x44
#define ACCEL18_REG_ANY_MOTION_DEBOUNCE                 0x45
#define ACCEL18_REG_SNAKE_THRESHOLD_LSB                 0x46
#define ACCEL18_REG_SNAKE_THRESHOLD_MSB                 0x47
#define ACCEL18_REG_PEAK_TO_PEAK_DURATION_LSB           0x48
#define ACCEL18_REG_SNAKE_PEAK_TO_PEAK_DURATION_MSB     0x49
#define ACCEL18_REG_TIMER                               0x4A
#define ACCEL18_REG_READ_COUNT                          0x4B


/*! @} */ // accel18_reg

/**
 * @defgroup accel18_set Accel 18 Registers Settings
 * @brief Settings for registers of Accel 18 Click driver.
 */

/**
 * @addtogroup accel18_set
 * @{
 */

/**
 * @brief Accel 18 state.
 * @details Specified setting for state of Accel 18 Click driver.
 */
#define ACCEL18_STATE_STANDBY                           0x00
#define ACCEL18_STATE_WAKE                              0x01

/**
 * @brief Accel 18 interrupt setting.
 * @details Specified setting for interrupt of Accel 18 Click driver.
 */
#define ACCEL18_INT_TILT_EN                             0x01
#define ACCEL18_INT_FLIP_EN                             0x02
#define ACCEL18_INT_ANYM_EN                             0x04
#define ACCEL18_INT_SHAKE_EN                            0x08
#define ACCEL18_INT_TILT_35_EN                          0x10
#define ACCEL18_INT_AUTO_CLR_EN                         0x40
#define ACCEL18_INT_ACQ_EN                              0x80

/**
 * @brief Accel 18 sample rate setting.
 * @details Specified setting for sample rate of Accel 18 Click driver.
 */
#define ACCEL18_RATE_25                                 0x10
#define ACCEL18_RATE_50                                 0x11
#define ACCEL18_RATE_62p5                               0x12
#define ACCEL18_RATE_100                                0x13
#define ACCEL18_RATE_125                                0x14
#define ACCEL18_RATE_250                                0x15
#define ACCEL18_RATE_500                                0x16
#define ACCEL18_RATE_1000                               0x17

/**
 * @brief Accel 18 fifo control 2 setting.
 * @details Specified setting for fifo control 2 of Accel 18 Click driver.
 */
#define ACCEL18_FIFO_CTRL2_BURST_MODE                   0x80
#define ACCEL18_FIFO_CTRL2_SELECT_WRAP_ADDR             0x20
#define ACCEL18_FIFO_CTRL2_ENABLE_WRAP_N                0x10
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DISABLE        0x00
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_2          0x01
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_4          0x02
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_5          0x03
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_8          0x04
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_10         0x05
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_16         0x06
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_20         0x07
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_40         0x08
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_67         0x09
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_80         0x0A
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_100        0x0B
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_200        0x0C
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_250        0x0D
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_500        0x0E
#define ACCEL18_FIFO_CTRL2_DEC_MODE_RATE_DIV_1000       0x0F

/**
 * @brief Accel 18 gpio control setting.
 * @details Specified setting for gpio control of Accel 18 Click driver.
 */
#define ACCEL18_GPIO_CTRL_INT1_ACTIVE_LOW               0x00
#define ACCEL18_GPIO_CTRL_INT1_ACTIVE_HIGH              0x04
#define ACCEL18_GPIO_CTRL_INT1_OPEN_DRAIN               0x00
#define ACCEL18_GPIO_CTRL_INT1_PUSH_PULL                0x08
#define ACCEL18_GPIO_CTRL_INT2_ACTIVE_LOW               0x00
#define ACCEL18_GPIO_CTRL_INT2_ACTIVE_HIGH              0x40
#define ACCEL18_GPIO_CTRL_INT2_OPEN_DRAIN               0x00
#define ACCEL18_GPIO_CTRL_INT2_PUSH_PULL                0x80

/**
 * @brief Accel 18 motion setting.
 * @details Specified setting for motion of Accel 18 Click driver.
 */
#define ACCEL18_MOTION_TF_EN                            0x01
#define ACCEL18_MOTION_LATCH                            0x02
#define ACCEL18_MOTION_ANYM_EN                          0x04
#define ACCEL18_MOTION_SHAKE_EN                         0x08
#define ACCEL18_MOTION_TILT_35                          0x10
#define ACCEL18_MOTION_Z_AXIS_ORT                       0x20
#define ACCEL18_MOTION_RAW_PROC_STAT                    0x40
#define ACCEL18_MOTION_RESET                            0x80

/**
 * @brief Accel 18 status.
 * @details Specified status for Accel 18 Click driver.
 */
#define ACCEL18_STATUS_TILT                             0x01
#define ACCEL18_STATUS_FLIP                             0x02
#define ACCEL18_STATUS_ANYM                             0x04
#define ACCEL18_STATUS_SHAKE                            0x08
#define ACCEL18_STATUS_TILT35                           0x10
#define ACCEL18_STATUS_FIFO                             0x20
#define ACCEL18_STATUS_NEW_DATA                         0x80

/**
 * @brief Accel 18 range and scale setting.
 * @details Specified setting for range and scale of Accel 18 Click driver.
 */
#define ACCEL18_RANGE_2G                                0x00
#define ACCEL18_RANGE_4G                                0x10
#define ACCEL18_RANGE_8G                                0x20
#define ACCEL18_RANGE_16G                               0x30
#define ACCEL18_RANGE_12G                               0x40
#define ACCEL18_LOW_PASS_FILTER_EN                      0x08
#define ACCEL18_LOW_PASS_FILTER_DIV4p255                0x01
#define ACCEL18_LOW_PASS_FILTER_DIV6                    0x02
#define ACCEL18_LOW_PASS_FILTER_DIV12                   0x03
#define ACCEL18_LOW_PASS_FILTER_DIV16                   0x05

/**
 * @brief Accel 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 18 Click driver.
 */
#define ACCEL18_GND_ADDR                                0x4C
#define ACCEL18_VCC_ADDR                                0x6C
#define ACCEL18_SET_DEV_ADDR                            ACCEL18_GND_ADDR

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b accel18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL18_SET_DATA_SAMPLE_EDGE                    SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL18_SET_DATA_SAMPLE_MIDDLE                  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel18_set

/**
 * @defgroup accel18_map Accel 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 18 Click driver.
 */

/**
 * @addtogroup accel18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 18 Click to the selected MikroBUS.
 */
#define ACCEL18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.i1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.i2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel18_map
/*! @} */ // accel18

/**
 * @brief Accel 18 Click driver selector.
 * @details Selects target driver interface of Accel 18 Click driver.
 */
typedef enum
{
    ACCEL18_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL18_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel18_drv_t;

/**
 * @brief Accel 18 Click driver interface.
 * @details Definition of driver interface of Accel 18 Click driver.
 */
typedef err_t ( *accel18_master_io_t )( struct accel18_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 18 Click context object.
 * @details Context object definition of Accel 18 Click driver.
 */
typedef struct accel18_s
{
    digital_in_t  i1;               /**< Interrupt 1. */
    digital_in_t  i2;               /**< Interrupt 2. */

    i2c_master_t  i2c;              /**< I2C driver object. */
    spi_master_t  spi;              /**< SPI driver object. */

    uint8_t     slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    accel18_drv_t  drv_sel;         /**< Master driver interface selector. */

    accel18_master_io_t  write_f;   /**< Master write function. */
    accel18_master_io_t  read_f;    /**< Master read function. */

    float range_resolution;         /**< Data range resolution. */

} accel18_t;

/**
 * @brief Accel 18 Click configuration object.
 * @details Configuration object definition of Accel 18 Click driver.
 */
typedef struct
{
    pin_name_t  scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;       /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;      /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;      /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;       /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;        /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  i1;        /**< Interrupt 1. */
    pin_name_t  i2;        /**< Interrupt 2. */

    uint32_t  i2c_speed;   /**< I2C serial speed. */
    uint8_t   i2c_address; /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    accel18_drv_t  drv_sel; /**< Master driver interface selector. */

} accel18_cfg_t;

/**
 * @brief Accel 18 Click axes data.
 * @details Axes data object definition of Accel 18 Click driver.
 */
typedef struct
{
    float x; /**< X axis. */
    float y; /**< Y axis. */
    float z; /**< Z axis. */

} accel18_axes_t;

/**
 * @brief Accel 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL18_OK = 0,
    ACCEL18_ERROR = -1

} accel18_return_value_t;

/*!
 * @addtogroup accel18 Accel 18 Click Driver
 * @brief API for configuring and manipulating Accel 18 Click driver.
 * @{
 */

/**
 * @brief Accel 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel18_cfg_setup ( accel18_cfg_t *cfg );

/**
 * @brief Accel 18 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel18_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel18_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel18_drv_interface_selection ( accel18_cfg_t *cfg, accel18_drv_t drv_sel );

/**
 * @brief Accel 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel18_init ( accel18_t *ctx, accel18_cfg_t *cfg );

/**
 * @brief Accel 18 default configuration function.
 * @details This function executes a default configuration of Accel 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel18_default_cfg ( accel18_t *ctx );

/**
 * @brief Accel 18 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel18_generic_write ( accel18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 18 byte writing function.
 * @details This function writes a byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel18_byte_write ( accel18_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 18 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel18_generic_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 18 byte reading function.
 * @details This function reads a byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel18_byte_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel data reading.
 * @details This function reads a accel data and calculates it with
 * resolution set in @b ctx object. Data will be set in @b axes object.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[out] axes : Axes data object.
 * See #acce18_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t accel18_read_axes ( accel18_t *ctx, accel18_axes_t *axes_data );

/**
 * @brief Set range configuration.
 * @details This function configures device range and resolution.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] range_macro : Range macro.
 * See Accel 18 range and scale setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Additionally function will set @b range_resolution in the @b ctx object.
 */
err_t accel18_set_range ( accel18_t *ctx, uint8_t range_macro );

/**
 * @brief Get interrupt 1 pin state.
 * @details This function reads logic state of interrupt 1 pin.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @return State of interrupt pin.
 */
uint8_t accel18_get_interrupt_1 ( accel18_t *ctx );

/**
 * @brief Get interrupt 2 pin state.
 * @details This function reads logic state of interrupt 2 pin.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @return State of interrupt pin.
 */
uint8_t accel18_get_interrupt_2 ( accel18_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL18_H

/*! @} */ // accel18

// ------------------------------------------------------------------------ END

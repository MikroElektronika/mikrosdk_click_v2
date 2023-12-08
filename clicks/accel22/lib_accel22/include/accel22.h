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
 * @file accel22.h
 * @brief This file contains API for Accel 22 Click Driver.
 */

#ifndef ACCEL22_H
#define ACCEL22_H

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
 * @addtogroup accel22 Accel 22 Click Driver
 * @brief API for configuring and manipulating Accel 22 Click driver.
 * @{
 */

/**
 * @defgroup accel22_reg Accel 22 Registers List
 * @brief List of registers of Accel 22 Click driver.
 */

/**
 * @addtogroup accel22_reg
 * @{
 */

/**
 * @brief Accel 22 register map.
 * @details Specified register map of Accel 22 Click driver.
 */
#define ACCEL22_REG_DEVID_AD                0x00
#define ACCEL22_REG_DEVID_MST               0x01
#define ACCEL22_REG_PART_ID                 0x02
#define ACCEL22_REG_REV_ID                  0x03
#define ACCEL22_REG_SERIAL_NUMBER_3         0x04
#define ACCEL22_REG_SERIAL_NUMBER_2         0x05
#define ACCEL22_REG_SERIAL_NUMBER_1         0x06
#define ACCEL22_REG_SERIAL_NUMBER_0         0x07
#define ACCEL22_REG_XDATA                   0x08
#define ACCEL22_REG_YDATA                   0x09
#define ACCEL22_REG_ZDATA                   0x0A
#define ACCEL22_REG_STATUS                  0x0B
#define ACCEL22_REG_FIFO_ENTRIES_L          0x0C
#define ACCEL22_REG_FIFO_ENTRIES_H          0x0D
#define ACCEL22_REG_XDATA_H                 0x0E
#define ACCEL22_REG_XDATA_L                 0x0F
#define ACCEL22_REG_YDATA_H                 0x10
#define ACCEL22_REG_YDATA_L                 0x11
#define ACCEL22_REG_ZDATA_H                 0x12
#define ACCEL22_REG_ZDATA_L                 0x13
#define ACCEL22_REG_TEMP_H                  0x14
#define ACCEL22_REG_TEMP_L                  0x15
#define ACCEL22_REG_EX_ADC_H                0x16
#define ACCEL22_REG_EX_ADC_L                0x17
#define ACCEL22_REG_I2C_FIFO_DATA           0x18
#define ACCEL22_REG_SOFT_RESET              0x19
#define ACCEL22_REG_THRESH_ACT_H            0x20
#define ACCEL22_REG_THRESH_ACT_L            0x21
#define ACCEL22_REG_TIME_ACT                0x22
#define ACCEL22_REG_THRESH_INACT_H          0x23
#define ACCEL22_REG_THRESH_INACT_L          0x24
#define ACCEL22_REG_TIME_INACT_H            0x25
#define ACCEL22_REG_TIME_INACT_L            0x26
#define ACCEL22_REG_ACT_INACT_CTL           0x27
#define ACCEL22_REG_FIFO_CONTROL            0x28
#define ACCEL22_REG_FIFO_SAMPLES            0x29
#define ACCEL22_REG_INTMAP1_LOWER           0x2A
#define ACCEL22_REG_INTMAP2_LOWER           0x2B
#define ACCEL22_REG_FILTER_CTL              0x2C
#define ACCEL22_REG_POWER_CTL               0x2D
#define ACCEL22_REG_SELF_TEST               0x2E
#define ACCEL22_REG_TAP_THRESH              0x2F
#define ACCEL22_REG_TAP_DUR                 0x30
#define ACCEL22_REG_TAP_LATENT              0x31
#define ACCEL22_REG_TAP_WINDOW              0x32
#define ACCEL22_REG_X_OFFSET                0x33
#define ACCEL22_REG_Y_OFFSET                0x34
#define ACCEL22_REG_Z_OFFSET                0x35
#define ACCEL22_REG_X_SENS                  0x36
#define ACCEL22_REG_Y_SENS                  0x37
#define ACCEL22_REG_Z_SENS                  0x38
#define ACCEL22_REG_TIMER_CTL               0x39
#define ACCEL22_REG_INTMAP1_UPPER           0x3A
#define ACCEL22_REG_INTMAP2_UPPER           0x3B
#define ACCEL22_REG_ADC_CTL                 0x3C
#define ACCEL22_REG_TEMP_CTL                0x3D
#define ACCEL22_REG_TEMP_ADC_OVER_THRSH_H   0x3E
#define ACCEL22_REG_TEMP_ADC_OVER_THRSH_L   0x3F
#define ACCEL22_REG_TEMP_ADC_UNDER_THRSH_H  0x40
#define ACCEL22_REG_TEMP_ADC_UNDER_THRSH_L  0x41
#define ACCEL22_REG_TEMP_ADC_TIMER          0x42
#define ACCEL22_REG_AXIS_MASK               0x43
#define ACCEL22_REG_STATUS_COPY             0x44
#define ACCEL22_REG_STATUS_2                0x45

/*! @} */ // accel22_reg

/**
 * @defgroup accel22_set Accel 22 Registers Settings
 * @brief Settings for registers of Accel 22 Click driver.
 */

/**
 * @addtogroup accel22_set
 * @{
 */

/**
 * @brief Accel 22 INTMAP1_LOWER register settings.
 * @details Specified INTMAP1_LOWER register settings of Accel 22 Click driver.
 */
#define ACCEL22_INTMAP1_LOWER_INT_LOW       0x80
#define ACCEL22_INTMAP1_LOWER_AWAKE         0x40
#define ACCEL22_INTMAP1_LOWER_INACT         0x20
#define ACCEL22_INTMAP1_LOWER_ACT           0x10
#define ACCEL22_INTMAP1_LOWER_FIFO_OR       0x08
#define ACCEL22_INTMAP1_LOWER_FIFO_WM       0x04
#define ACCEL22_INTMAP1_LOWER_FIFO_RDY      0x02
#define ACCEL22_INTMAP1_LOWER_DATA_RDY      0x01

/**
 * @brief Accel 22 POWER_CTL register settings.
 * @details Specified POWER_CTL register settings of Accel 22 Click driver.
 */
#define ACCEL22_POWER_CTL_EXT_CLK           0x40
#define ACCEL22_POWER_CTL_NOISE_NORMAL      0x00
#define ACCEL22_POWER_CTL_NOISE_LOW         0x10
#define ACCEL22_POWER_CTL_NOISE_ULTRALOW    0x20
#define ACCEL22_POWER_CTL_NOISE_BIT_MASK    0x30
#define ACCEL22_POWER_CTL_WAKEUP            0x08
#define ACCEL22_POWER_CTL_AUTOSLEEP         0x04
#define ACCEL22_POWER_CTL_STANDBY_MODE      0x00
#define ACCEL22_POWER_CTL_MEASUREMENT_MODE  0x02

/**
 * @brief Accel 22 soft reset value.
 * @details Specified soft reset value of Accel 22 Click driver.
 */
#define ACCEL22_SOFT_RESET                  0x52

/**
 * @brief Accel 22 enable temperature and adc measurement values.
 * @details Specified enable temperature and adc measurement values of Accel 22 Click driver.
 */
#define ACCEL22_ENABLE_TEMPERATURE          0x01
#define ACCEL22_ENABLE_ADC                  0x01

/**
 * @brief Accel 22 calculation values.
 * @details Specified calculation values of Accel 22 Click driver.
 */
#define ACCEL22_ACCEL_2G_RES                0.25
#define ACCEL22_ACCEL_4G_RES                0.5
#define ACCEL22_ACCEL_8G_RES                1.0
#define ACCEL22_ROOM_TEMPERATURE            25.0
#define ACCEL22_TEMPERATURE_BIAS            165
#define ACCEL22_TEMPERATURE_RES             54.0
#define ACCEL22_TEMPERATURE_CAL_SAMPLE_NUM  100
#define ACCEL22_ADC_VREG                    1.098
#define ACCEL22_ADC_RES                     0x3FFF
#define ACCEL22_ADC_OFFSET                  0x2000

/**
 * @brief Accel 22 device ID register values.
 * @details Specified device ID register values of Accel 22 Click driver.
 */
#define ACCEL22_ADI_DEVICE_ID               0xAD
#define ACCEL22_MEMS_DEVICE_ID              0x1D
#define ACCEL22_PART_ID                     0xF7

/**
 * @brief Accel 22 SPI command values.
 * @details Specified SPI command values of Accel 22 Click driver.
 */
#define ACCEL22_SPI_WRITE_REG               0x0A
#define ACCEL22_SPI_READ_REG                0x0B
#define ACCEL22_SPI_READ_FIFO               0x0D

/**
 * @brief Accel 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 22 Click driver.
 */
#define ACCEL22_DEVICE_ADDRESS_0            0x1D
#define ACCEL22_DEVICE_ADDRESS_1            0x53

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel22_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL22_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL22_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel22_set

/**
 * @defgroup accel22_map Accel 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 22 Click driver.
 */

/**
 * @addtogroup accel22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 22 Click to the selected MikroBUS.
 */
#define ACCEL22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel22_map
/*! @} */ // accel22

/**
 * @brief Accel 22 Click driver selector.
 * @details Selects target driver interface of Accel 22 Click driver.
 */
typedef enum
{
    ACCEL22_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL22_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel22_drv_t;

/**
 * @brief Accel 22 Click driver interface.
 * @details Definition of driver interface of Accel 22 Click driver.
 */
typedef err_t ( *accel22_master_io_t )( struct accel22_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 22 Click context object.
 * @details Context object definition of Accel 22 Click driver.
 */
typedef struct accel22_s
{
    digital_in_t  int2;             /**< Interrupt 2 pin. */
    digital_in_t  int1;             /**< Interrupt 1 pin. */

    i2c_master_t  i2c;              /**< I2C driver object. */
    spi_master_t  spi;              /**< SPI driver object. */

    uint8_t     slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    accel22_drv_t  drv_sel;         /**< Master driver interface selector. */

    accel22_master_io_t  write_f;   /**< Master write function. */
    accel22_master_io_t  read_f;    /**< Master read function. */
    float resolution;               /**< Accel range resolution. */
    float room_temp_offset;         /**< Room temperature offset, calibrate using accel22_calibrate_temperature function. */

} accel22_t;

/**
 * @brief Accel 22 Click configuration object.
 * @details Configuration object definition of Accel 22 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int2;               /**< Interrupt 2 pin. */
    pin_name_t  int1;               /**< Interrupt 1 pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    accel22_drv_t  drv_sel;         /**< Master driver interface selector. */

} accel22_cfg_t;

/**
 * @brief Accel 22 Click Axes data structure.
 * @details Axes data object definition of Accel 22 Click driver.
 */
typedef struct
{
    float x;    /**< X axis. */
    float y;    /**< Y axis. */
    float z;    /**< Z axis. */

} accel22_axes_t;

/**
 * @brief Accel 22 Click accel range selection.
 * @details Predefined enum values for driver accel range selection.
 */
typedef enum
{
    ACCEL22_2G = 0x00,
    ACCEL22_4G = 0x01,
    ACCEL22_8G = 0x02,
    ACCEL22_RANGE_BIT_MASK = 0xC0

} accel22_range_t;

/**
 * @brief Accel 22 Click output data rate.
 * @details Predefined enum values for driver output data rate.
 */
typedef enum
{
    ACCEL22_12p5HZ = 0x00,
    ACCEL22_25HZ,
    ACCEL22_50HZ,
    ACCEL22_100HZ,
    ACCEL22_200HZ,
    ACCEL22_400HZ,
    ACCEL22_ODR_BIT_MASK = 0x07

} accel22_odr_t;

/**
 * @brief Accel 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL22_OK = 0,
    ACCEL22_ERROR = -1

} accel22_return_value_t;

/*!
 * @addtogroup accel22 Accel 22 Click Driver
 * @brief API for configuring and manipulating Accel 22 Click driver.
 * @{
 */

/**
 * @brief Accel 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel22_cfg_setup ( accel22_cfg_t *cfg );

/**
 * @brief Accel 22 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel22_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel22_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel22_drv_interface_selection ( accel22_cfg_t *cfg, accel22_drv_t drv_sel );

/**
 * @brief Accel 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_init ( accel22_t *ctx, accel22_cfg_t *cfg );

/**
 * @brief Accel 22 default configuration function.
 * @details This function executes a default configuration of Accel 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel22_default_cfg ( accel22_t *ctx );

/**
 * @brief Accel 22 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_generic_write ( accel22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 22 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_generic_read ( accel22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 22 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_write_register ( accel22_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 22 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_read_register ( accel22_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 22 check communication function.
 * @details This function checks the communication by reading and verifying the device ID bytes.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_check_communication ( accel22_t *ctx );

/**
 * @brief Accel 22 get int1 pin function.
 * @details This function returns the interrupt 1 (INT1) pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel22_get_int1_pin ( accel22_t *ctx );

/**
 * @brief Accel 22 get int2 pin function.
 * @details This function returns the interrupt 2 (INT2) pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel22_get_int2_pin ( accel22_t *ctx );

/**
 * @brief Accel 22 set filter config function.
 * @details This function sets the accel range and output data rate (ODR) bits in FILTER_CTL register.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] range : Accel range bits setting.
 * See #accel22_range_t enum definition for detailed explanation.
 * @param[in] odr : Output data rate bits setting.
 * See #accel22_odr_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_set_filter_config ( accel22_t *ctx, accel22_range_t range, accel22_odr_t odr );

/**
 * @brief Accel 22 get axes function.
 * @details This function reads accel X, Y, and Z axis data in mg.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[out] axes : X, Y, and Z axis data in mg.
 * See #accel22_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_get_axes ( accel22_t *ctx, accel22_axes_t *axes );

/**
 * @brief Accel 22 enable temperature measurement function.
 * @details This function enables the temperature measurement and disables ADC measurement.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_enable_temperature_measurement ( accel22_t *ctx );

/**
 * @brief Accel 22 enable ADC measurement function.
 * @details This function enables the ADC measurement and disables temperature measurement.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_enable_adc_measurement ( accel22_t *ctx );

/**
 * @brief Accel 22 calibrate temperature function.
 * @details This function calibrates the temperature readings to the known room temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] room_temperature : Known room temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel22_calibrate_temperature ( accel22_t *ctx, float room_temperature );

/**
 * @brief Accel 22 get temperature function.
 * @details This function reads the temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The temperature measurement must be enabled using 
 * @b accel22_enable_temperature_measurement function.
 */
err_t accel22_get_temperature ( accel22_t *ctx, float *temperature );

/**
 * @brief Accel 22 get adc function.
 * @details This function reads the ADC voltage.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[out] v_adc : ADC voltage read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The ADC measurement must be enabled using 
 * @b accel22_enable_adc_measurement function.
 */
err_t accel22_get_adc ( accel22_t *ctx, float *v_adc );

#ifdef __cplusplus
}
#endif
#endif // ACCEL22_H

/*! @} */ // accel22

// ------------------------------------------------------------------------ END

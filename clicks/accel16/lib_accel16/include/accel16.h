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
 * @file accel16.h
 * @brief This file contains API for Accel 16 Click Driver.
 */

#ifndef ACCEL16_H
#define ACCEL16_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup accel16 Accel 16 Click Driver
 * @brief API for configuring and manipulating Accel 16 Click driver.
 * @{
 */

/**
 * @defgroup accel16_reg Accel 16 Registers List
 * @brief List of registers of Accel 16 Click driver.
 */

/**
 * @addtogroup accel16_reg
 * @{
 */

/**
 * @brief Accel 16 control commands.
 * @details Specified commands for control of Accel 16 Click driver.
 */
#define ACCEL16_CMD_WRITE_REG               0x0A
#define ACCEL16_CMD_READ_REG                0x0B
#define ACCEL16_CMD_READ_FIFO               0x0D

/**
 * @brief Accel 16 description register.
 * @details Specified register for description of Accel 16 Click driver.
 */
#define ACCEL16_REG_DEVID_AD                0x00
#define ACCEL16_REG_DEVID_MST               0x01
#define ACCEL16_REG_DEVID                   0x02
#define ACCEL16_REG_REVID                   0x03
#define ACCEL16_REG_XDATA                   0x08
#define ACCEL16_REG_YDATA                   0x09
#define ACCEL16_REG_ZDATA                   0x0A
#define ACCEL16_REG_STATUS                  0x0B
#define ACCEL16_REG_FIFO_ENTRIES_L          0x0C
#define ACCEL16_REG_FIFO_ENTRIES_H          0x0D
#define ACCEL16_REG_XDATA_L                 0x0E
#define ACCEL16_REG_XDATA_H                 0x0F
#define ACCEL16_REG_YDATA_L                 0x10
#define ACCEL16_REG_YDATA_H                 0x11
#define ACCEL16_REG_ZDATA_L                 0x12
#define ACCEL16_REG_ZDATA_H                 0x13
#define ACCEL16_REG_TEMP_L                  0x14
#define ACCEL16_REG_TEMP_H                  0x15
#define ACCEL16_REG_ADC_DATA_L              0x16
#define ACCEL16_REG_ADC_DATA_H              0x17
#define ACCEL16_REG_SOFT_RESET              0x1F
#define ACCEL16_REG_THRESH_ACT_L            0x20
#define ACCEL16_REG_THRESH_ACT_H            0x21
#define ACCEL16_REG_TIME_ACT                0x22
#define ACCEL16_REG_THRESH_INACT_L          0x23
#define ACCEL16_REG_THRESH_INACT_H          0x24
#define ACCEL16_REG_TIME_INACT_L            0x25
#define ACCEL16_REG_TIME_INACT_H            0x26
#define ACCEL16_REG_ACT_INACT_CTL           0x27
#define ACCEL16_REG_FIFO_CONTROL            0x28
#define ACCEL16_REG_FIFO_SAMPLES            0x29
#define ACCEL16_REG_INTMAP1                 0x2A
#define ACCEL16_REG_INTMAP2                 0x2B
#define ACCEL16_REG_FILTER_CTL              0x2C
#define ACCEL16_REG_POWER_CTL               0x2D
#define ACCEL16_REG_SELF_CTL                0x2E

/*! @} */ // accel16_reg

/**
 * @defgroup accel16_set Accel 16 Registers Settings
 * @brief Settings for registers of Accel 16 Click driver.
 */

/**
 * @addtogroup accel16_set
 * @{
 */

/**
 * @brief Accel 16 description setting.
 * @details Specified setting for description of Accel 16 Click driver.
 */
#define ACCEL16_APPLICATION_FIFO            0xAA
#define ACCEL16_APPLICATION_REG             0xBB

/**
 * @brief Accel 16 temperature calculation values.
 * @details Specified temperature calculation values of Accel 16 Click driver.
 */
#define ACCEL16_ROOM_TEMPERATURE            25.0
#define ACCEL16_TEMPERATURE_BIAS            350
#define ACCEL16_TEMPERATURE_RES             0.065
#define ACCEL16_TEMPERATURE_CAL_SAMPLE_NUM  100

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL16_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL16_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel16_set

/**
 * @defgroup accel16_map Accel 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 16 Click driver.
 */

/**
 * @addtogroup accel16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 16 Click to the selected MikroBUS.
 */
#define ACCEL16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel16_map
/*! @} */ // accel16

/**
 * @brief Accel 16 Click context object.
 * @details Context object definition of Accel 16 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int2;         /**< Interrupt 2. */
    digital_in_t  int1;         /**< Interrupt 1. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    float resolution;           /**< Accel range resolution. */
    float room_temp_offset;     /**< Room temperature offset, calibrate using accel16_calibrate_temperature function. */
    uint8_t application_type;   /**< FIFO or REG application type. */
    
} accel16_t;

/**
 * @brief Accel 16 Click configuration object.
 * @details Configuration object definition of Accel 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  int2;   /**< Interrupt 2. */
    pin_name_t  int1;   /**< Interrupt 1. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} accel16_cfg_t;

/**
 * @brief Accel 16 Click axes data.
 * @details Axes data object definition of Accel 16 Click driver.
 */
typedef struct
{
    float x; /**< X axis. */
    float y; /**< Y axis. */
    float z; /**< Z axis. */

} accel16_axes_t;

/**
 * @brief Accel 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL16_OK = 0,
    ACCEL16_ERROR = -1

} accel16_return_value_t;

/**
 * @brief Accel 16 Click gain.
 * @details Predefined enum values for driver gain.
 */
typedef enum
{
    ACCEL16_2G = 0,
    ACCEL16_4G = 1,
    ACCEL16_8G = 2

} accel16_gain_t;

/**
 * @brief Accel 16 Click output data rate.
 * @details Predefined enum values for driver output data rate.
 */
typedef enum
{
    ACCEL16_12p5HZ = 0,
    ACCEL16_25HZ,
    ACCEL16_50HZ,
    ACCEL16_100HZ,
    ACCEL16_200HZ,
    ACCEL16_400HZ

} accel16_output_rate_t;

/*!
 * @addtogroup accel16 Accel 16 Click Driver
 * @brief API for configuring and manipulating Accel 16 Click driver.
 * @{
 */

/**
 * @brief Accel 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel16_cfg_setup ( accel16_cfg_t *cfg );

/**
 * @brief Accel 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel16_init ( accel16_t *ctx, accel16_cfg_t *cfg );

/**
 * @brief Accel 16 default configuration function.
 * @details This function executes a default configuration of Accel 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel16_default_cfg ( accel16_t *ctx );

/**
 * @brief Write multiple registers.
 * @details This function writes a desired number of data
 * bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_multiple_reg_write ( accel16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Write single register.
 * @details This function writes a bytes to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_single_reg_write ( accel16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Read multiple registers.
 * @details This function reads a desired number of data 
 * bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_multiple_reg_read ( accel16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Read single registers.
 * @details This function reads a byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_single_reg_read ( accel16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Read fifo.
 * @details This function reads a desired number of data 
 * bytes from fifo buffer.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note You should always read even number of bytes from fifo.
 */
err_t accel16_fifo_read ( accel16_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Get interrupt 1 state.
 * @details This function reads @b int1 pin state.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @return Interrupt 1 pin state
 */
uint8_t accel16_get_interrupt_1 ( accel16_t *ctx );

/**
 * @brief Get interrupt 2 state.
 * @details This function reads @b int2 pin state.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @return Interrupt 2 pin state
 */
uint8_t accel16_get_interrupt_2 ( accel16_t *ctx );

/**
 * @brief Filter configuration.
 * @details This function changes configuration of filter register
 * of gain and output data rate.
 * @param[in,out] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] gain : Data resolution.
 * @param[in] odr : Output data rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_filter_configuration ( accel16_t *ctx, accel16_gain_t gain, accel16_output_rate_t odr );

/**
 * @brief Get axes data.
 * @details This function reads axes data from registers and calculates values in g.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[out] axes : Axes data.
 * See #accel16_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_get_axes ( accel16_t *ctx, accel16_axes_t *axes );

/**
 * @brief Get temperature data.
 * @details This function reads temperature data from registers 
 * and calculates values in degreese C.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data in degreese Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t accel16_get_temperature ( accel16_t *ctx, float *temperature );

/**
 * @brief Get adc data.
 * @details This function reads adc data from register and calculates
 * voltage level.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[out] v_adc : Voltage output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note ADC read data range is from 10% to 90% of VCC[ 0.33V-2.97V ].
 */
err_t accel16_get_adc ( accel16_t *ctx, float *v_adc );

/**
 * @brief Accel 16 calibrate temperature function.
 * @details This function calibrates the temperature readings to the known room temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #accel16_t object definition for detailed explanation.
 * @param[in] room_temperature : Known room temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel16_calibrate_temperature ( accel16_t *ctx, float room_temperature );

#ifdef __cplusplus
}
#endif
#endif // ACCEL16_H

/*! @} */ // accel16

// ------------------------------------------------------------------------ END

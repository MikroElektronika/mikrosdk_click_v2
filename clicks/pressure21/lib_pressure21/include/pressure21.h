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
 * @file pressure21.h
 * @brief This file contains API for Pressure 21 Click Driver.
 */

#ifndef PRESSURE21_H
#define PRESSURE21_H

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
 * @addtogroup pressure21 Pressure 21 Click Driver
 * @brief API for configuring and manipulating Pressure 21 Click driver.
 * @{
 */

/**
 * @defgroup pressure21_reg Pressure 21 Registers List
 * @brief List of registers of Pressure 21 Click driver.
 */

/**
 * @addtogroup pressure21_reg
 * @{
 */

/**
 * @brief Pressure 21 register map.
 * @details Specified register map of Pressure 21 Click driver.
 */
#define PRESSURE21_REG_CHIP_ID              0x01
#define PRESSURE21_REG_REV_ID               0x02
#define PRESSURE21_REG_CHIP_STATUS          0x11
#define PRESSURE21_REG_DRIVE_CONFIG         0x13
#define PRESSURE21_REG_INT_CONFIG           0x14
#define PRESSURE21_REG_INT_SOURCE           0x15
#define PRESSURE21_REG_FIFO_CONFIG          0x16
#define PRESSURE21_REG_FIFO_COUNT           0x17
#define PRESSURE21_REG_FIFO_SEL             0x18
#define PRESSURE21_REG_TEMP_DATA_XLSB       0x1D
#define PRESSURE21_REG_TEMP_DATA_LSB        0x1E
#define PRESSURE21_REG_TEMP_DATA_MSB        0x1F
#define PRESSURE21_REG_PRESS_DATA_XLSB      0x20
#define PRESSURE21_REG_PRESS_DATA_LSB       0x21
#define PRESSURE21_REG_PRESS_DATA_MSB       0x22
#define PRESSURE21_REG_INT_STATUS           0x27
#define PRESSURE21_REG_STATUS               0x28
#define PRESSURE21_REG_FIFO_DATA            0x29
#define PRESSURE21_REG_NVM_ADDR             0x2B
#define PRESSURE21_REG_NVM_DATA_LSB         0x2C
#define PRESSURE21_REG_NVM_DATA_MSB         0x2D
#define PRESSURE21_REG_DSP_CONFIG           0x30
#define PRESSURE21_REG_DSP_IIR              0x31
#define PRESSURE21_REG_OOR_THR_P_LSB        0x32
#define PRESSURE21_REG_OOR_THR_P_MSB        0x33
#define PRESSURE21_REG_OOR_RANGE            0x34
#define PRESSURE21_REG_OOR_CONFIG           0x35
#define PRESSURE21_REG_OSR_CONFIG           0x36
#define PRESSURE21_REG_ODR_CONFIG           0x37
#define PRESSURE21_REG_OSR_EFF              0x38
#define PRESSURE21_REG_CMD                  0x7E

/*! @} */ // pressure21_reg

/**
 * @defgroup pressure21_set Pressure 21 Registers Settings
 * @brief Settings for registers of Pressure 21 Click driver.
 */

/**
 * @addtogroup pressure21_set
 * @{
 */

/**
 * @brief Pressure 21 chip ID value.
 * @details Specified chip ID value of Pressure 21 Click driver.
 */
#define PRESSURE21_CHIP_ID                  0x50

/**
 * @brief Pressure 21 INT config register settings.
 * @details Specified settings for INT config register of Pressure 21 Click driver.
 */
#define PRESSURE21_PAD_INT_DRV_DEFAULT      0x30
#define PRESSURE21_INT_ENABLE               0x08
#define PRESSURE21_INT_DISABLE              0x00
#define PRESSURE21_INT_OPEN_DRAIN           0x04
#define PRESSURE21_INT_PUSH_PULL            0x00
#define PRESSURE21_INT_ACTIVE_HIGH          0x02
#define PRESSURE21_INT_ACTIVE_LOW           0x00
#define PRESSURE21_INT_LATCHED              0x01
#define PRESSURE21_INT_PULSED               0x00

/**
 * @brief Pressure 21 INT source register settings.
 * @details Specified settings for INT source register of Pressure 21 Click driver.
 */
#define PRESSURE21_OOR_P_EN                 0x08
#define PRESSURE21_FIFO_THS_EN              0x04
#define PRESSURE21_FIFO_FULL_EN             0x02
#define PRESSURE21_DRDY_DATA_REG_EN         0x01
#define PRESSURE21_DISABLE_INT              0x00

/**
 * @brief Pressure 21 INT status register settings.
 * @details Specified settings for INT status register of Pressure 21 Click driver.
 */
#define PRESSURE21_INT_STAT_POR             0x10
#define PRESSURE21_INT_STAT_OOR_P           0x08
#define PRESSURE21_INT_STAT_FIFO_THS        0x04
#define PRESSURE21_INT_STAT_FIFO_FULL       0x02
#define PRESSURE21_INT_STAT_DRDY_DATA_REG   0x01

/**
 * @brief Pressure 21 DSP config register settings.
 * @details Specified settings for DSP config register of Pressure 21 Click driver.
 */
#define PRESSURE21_OOR_SEL_IIR_P            0x80
#define PRESSURE21_FIFO_SEL_IIR_P           0x40
#define PRESSURE21_SHDW_SEL_IIR_P           0x20
#define PRESSURE21_FIFO_SEL_IIR_T           0x10
#define PRESSURE21_SHDW_SEL_IIR_T           0x08
#define PRESSURE21_IIR_FLUSH_FORCED_EN      0x04
#define PRESSURE21_DSP_CFG_RESERVED_BITS    0x03

/**
 * @brief Pressure 21 DSP IIR config register settings.
 * @details Specified settings for DSP IIR config register of Pressure 21 Click driver.
 */
#define PRESSURE21_SET_IIR_P_BYPASS         0x00
#define PRESSURE21_SET_IIR_P_FLT_COEF_1     0x08
#define PRESSURE21_SET_IIR_P_FLT_COEF_3     0x10
#define PRESSURE21_SET_IIR_P_FLT_COEF_7     0x18
#define PRESSURE21_SET_IIR_P_FLT_COEF_15    0x20
#define PRESSURE21_SET_IIR_P_FLT_COEF_31    0x28
#define PRESSURE21_SET_IIR_P_FLT_COEF_63    0x30
#define PRESSURE21_SET_IIR_P_FLT_COEF_127   0x38
#define PRESSURE21_SET_IIR_T_BYPASS         0x00
#define PRESSURE21_SET_IIR_T_FLT_COEF_1     0x01
#define PRESSURE21_SET_IIR_T_FLT_COEF_3     0x02
#define PRESSURE21_SET_IIR_T_FLT_COEF_7     0x03
#define PRESSURE21_SET_IIR_T_FLT_COEF_15    0x04
#define PRESSURE21_SET_IIR_T_FLT_COEF_31    0x05
#define PRESSURE21_SET_IIR_T_FLT_COEF_63    0x06
#define PRESSURE21_SET_IIR_T_FLT_COEF_127   0x07

/**
 * @brief Pressure 21 OSR config register settings.
 * @details Specified settings for OSR config register of Pressure 21 Click driver.
 */
#define PRESSURE21_PRESS_EN                 0x40
#define PRESSURE21_OSR_P_1X                 0x00
#define PRESSURE21_OSR_P_2X                 0x08
#define PRESSURE21_OSR_P_4X                 0x10
#define PRESSURE21_OSR_P_8X                 0x18
#define PRESSURE21_OSR_P_16X                0x20
#define PRESSURE21_OSR_P_32X                0x28
#define PRESSURE21_OSR_P_64X                0x30
#define PRESSURE21_OSR_P_128X               0x38
#define PRESSURE21_OSR_T_1X                 0x00
#define PRESSURE21_OSR_T_2X                 0x01
#define PRESSURE21_OSR_T_4X                 0x02
#define PRESSURE21_OSR_T_8X                 0x03
#define PRESSURE21_OSR_T_16X                0x04
#define PRESSURE21_OSR_T_32X                0x05
#define PRESSURE21_OSR_T_64X                0x06
#define PRESSURE21_OSR_T_128X               0x07

/**
 * @brief Pressure 21 ODR config register settings.
 * @details Specified settings for ODR config register of Pressure 21 Click driver.
 */
#define PRESSURE21_DEEP_DIS                 0x80
#define PRESSURE21_ODR_240_HZ               0x00
#define PRESSURE21_ODR_218p537_HZ           0x04
#define PRESSURE21_ODR_199p111_HZ           0x08
#define PRESSURE21_ODR_179p2_HZ             0x0C
#define PRESSURE21_ODR_160_HZ               0x10
#define PRESSURE21_ODR_149p333_HZ           0x14
#define PRESSURE21_ODR_140_HZ               0x18
#define PRESSURE21_ODR_129p855_HZ           0x1C
#define PRESSURE21_ODR_120_HZ               0x20
#define PRESSURE21_ODR_110p164_HZ           0x24
#define PRESSURE21_ODR_100p299_HZ           0x28
#define PRESSURE21_ODR_89p6_HZ              0x2C
#define PRESSURE21_ODR_80_HZ                0x30
#define PRESSURE21_ODR_70_HZ                0x34
#define PRESSURE21_ODR_60_HZ                0x38
#define PRESSURE21_ODR_50p056_HZ            0x3C
#define PRESSURE21_ODR_45p025_HZ            0x40
#define PRESSURE21_ODR_40_HZ                0x44
#define PRESSURE21_ODR_35_HZ                0x48
#define PRESSURE21_ODR_30_HZ                0x4C
#define PRESSURE21_ODR_25p005_HZ            0x50
#define PRESSURE21_ODR_20_HZ                0x54
#define PRESSURE21_ODR_15_HZ                0x58
#define PRESSURE21_ODR_10_HZ                0x5C
#define PRESSURE21_ODR_5_HZ                 0x60
#define PRESSURE21_ODR_4_HZ                 0x64
#define PRESSURE21_ODR_3_HZ                 0x68
#define PRESSURE21_ODR_2_HZ                 0x6C
#define PRESSURE21_ODR_1_HZ                 0x70
#define PRESSURE21_ODR_0p5_HZ               0x74
#define PRESSURE21_ODR_0p25_HZ              0x78
#define PRESSURE21_ODR_0p125_HZ             0x7C
#define PRESSURE21_PWR_MODE_STANDBY         0x00
#define PRESSURE21_PWR_MODE_NORMAL          0x01
#define PRESSURE21_PWR_MODE_FORCE           0x02
#define PRESSURE21_PWR_MODE_NON_STOP        0x03

/**
 * @brief Pressure 21 pressure and temperature calculation values.
 * @details Specified pressure and temperature calculation values of Pressure 21 Click driver.
 */
#define PRESSURE21_PRESS_RESOLUTION         64.0
#define PRESSURE21_TEMP_RESOLUTION          65536.0
#define PRESSURE21_PA_TO_MBAR               0.01

/**
 * @brief Pressure 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 21 Click driver.
 */
#define PRESSURE21_DEVICE_ADDRESS_0         0x46
#define PRESSURE21_DEVICE_ADDRESS_1         0x47

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure21_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE21_SET_DATA_SAMPLE_EDGE     SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE21_SET_DATA_SAMPLE_MIDDLE   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure21_set

/**
 * @defgroup pressure21_map Pressure 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 21 Click driver.
 */

/**
 * @addtogroup pressure21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 21 Click to the selected MikroBUS.
 */
#define PRESSURE21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure21_map
/*! @} */ // pressure21

/**
 * @brief Pressure 21 Click driver selector.
 * @details Selects target driver interface of Pressure 21 Click driver.
 */
typedef enum
{
    PRESSURE21_DRV_SEL_SPI,         /**< SPI driver descriptor. */
    PRESSURE21_DRV_SEL_I2C          /**< I2C driver descriptor. */

} pressure21_drv_t;

/**
 * @brief Pressure 21 Click driver interface.
 * @details Definition of driver interface of Pressure 21 Click driver.
 */
typedef err_t ( *pressure21_master_io_t )( struct pressure21_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Pressure 21 Click context object.
 * @details Context object definition of Pressure 21 Click driver.
 */
typedef struct pressure21_s
{
    digital_in_t int_pin;           /**< Interrupt pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    pressure21_drv_t drv_sel;       /**< Master driver interface selector. */

    pressure21_master_io_t write_f; /**< Master write function. */
    pressure21_master_io_t read_f;  /**< Master read function. */

} pressure21_t;

/**
 * @brief Pressure 21 Click configuration object.
 * @details Configuration object definition of Pressure 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;             /**< Interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t   spi_speed;           /**< SPI serial speed. */
    spi_master_mode_t spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    pressure21_drv_t drv_sel;       /**< Master driver interface selector. */

} pressure21_cfg_t;

/**
 * @brief Pressure 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE21_OK = 0,
    PRESSURE21_ERROR = -1

} pressure21_return_value_t;

/*!
 * @addtogroup pressure21 Pressure 21 Click Driver
 * @brief API for configuring and manipulating Pressure 21 Click driver.
 * @{
 */

/**
 * @brief Pressure 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure21_cfg_setup ( pressure21_cfg_t *cfg );

/**
 * @brief Pressure 21 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure21_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure21_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure21_drv_interface_selection ( pressure21_cfg_t *cfg, pressure21_drv_t drv_sel );

/**
 * @brief Pressure 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_init ( pressure21_t *ctx, pressure21_cfg_t *cfg );

/**
 * @brief Pressure 21 default configuration function.
 * @details This function executes a default configuration of Pressure 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure21_default_cfg ( pressure21_t *ctx );

/**
 * @brief Pressure 21 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_generic_write ( pressure21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 21 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_generic_read ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 21 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_write_register ( pressure21_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Pressure 21 read register function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_read_register ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Pressure 21 check communication function.
 * @details This function checks the communication by reading and verifying the chip ID value.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_check_communication ( pressure21_t *ctx );

/**
 * @brief Pressure 21 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pressure21_get_int_pin ( pressure21_t *ctx );

/**
 * @brief Pressure 21 get sensor data function.
 * @details This function reads the sensor measurements data: pressure in Pascals and temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[out] pressure : Pressure in Pascals.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure21_get_sensor_data ( pressure21_t *ctx, float *pressure, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE21_H

/*! @} */ // pressure21

// ------------------------------------------------------------------------ END

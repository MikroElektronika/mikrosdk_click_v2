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
 * @file pressure18.h
 * @brief This file contains API for Pressure 18 Click Driver.
 */

#ifndef PRESSURE18_H
#define PRESSURE18_H

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
 * @addtogroup pressure18 Pressure 18 Click Driver
 * @brief API for configuring and manipulating Pressure 18 Click driver.
 * @{
 */

/**
 * @defgroup pressure18_reg Pressure 18 Registers List
 * @brief List of registers of Pressure 18 Click driver.
 */

/**
 * @addtogroup pressure18_reg
 * @{
 */

/**
 * @brief Pressure 18 register map.
 * @details Specified register map of Pressure 18 Click driver.
 */
#define PRESSURE18_REG_CHIP_ID                  0x00
#define PRESSURE18_REG_ERR                      0x02
#define PRESSURE18_REG_STATUS                   0x03
#define PRESSURE18_REG_DATA_0                   0x04
#define PRESSURE18_REG_DATA_1                   0x05
#define PRESSURE18_REG_DATA_2                   0x06
#define PRESSURE18_REG_DATA_3                   0x07
#define PRESSURE18_REG_DATA_4                   0x08
#define PRESSURE18_REG_DATA_5                   0x09
#define PRESSURE18_REG_SENSOR_TIME_0            0x0C
#define PRESSURE18_REG_SENSOR_TIME_1            0x0D
#define PRESSURE18_REG_SENSOR_TIME_2            0x0E
#define PRESSURE18_REG_SENSOR_TIME_3            0x0F
#define PRESSURE18_REG_EVENT                    0x10
#define PRESSURE18_REG_INT_STATUS               0x11
#define PRESSURE18_REG_FIFO_LENGTH_0            0x12
#define PRESSURE18_REG_FIFO_LENGTH_1            0x13
#define PRESSURE18_REG_FIFO_DATA                0x14
#define PRESSURE18_REG_FIFO_WTM_0               0x15
#define PRESSURE18_REG_FIFO_WTM_1               0x16
#define PRESSURE18_REG_FIFO_CONFIG_1            0x17
#define PRESSURE18_REG_FIFO_CONFIG_2            0x18
#define PRESSURE18_REG_INT_CTRL                 0x19
#define PRESSURE18_REG_IF_CONF                  0x1A
#define PRESSURE18_REG_PWR_CTRL                 0x1B
#define PRESSURE18_REG_OSR                      0x1C
#define PRESSURE18_REG_ODR                      0x1D
#define PRESSURE18_REG_CONFIG                   0x1F
#define PRESSURE18_REG_CALIB_DATA               0x31
#define PRESSURE18_REG_CMD                      0x7E

/*! @} */ // pressure18_reg

/**
 * @defgroup pressure18_set Pressure 18 Registers Settings
 * @brief Settings for registers of Pressure 18 Click driver.
 */

/**
 * @addtogroup pressure18_set
 * @{
 */

/**
 * @brief Pressure 18 chip id setting.
 * @details Specified setting for chip id of Pressure 18 Click driver.
 */
#define PRESSURE18_CHIP_ID                      0x50

/**
 * @brief Pressure 18 ERR register settings.
 * @details Specified ERR register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_ERR_FATAL                    0x01
#define PRESSURE18_ERR_CMD                      0x02
#define PRESSURE18_ERR_CONF                     0x04

/**
 * @brief Pressure 18 STATUS register settings.
 * @details Specified STATUS register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_STATUS_CMD_RDY               0x10
#define PRESSURE18_STATUS_DRDY_PRESS            0x20
#define PRESSURE18_STATUS_DRDY_TEMP             0x40

/**
 * @brief Pressure 18 INT_CTRL register settings.
 * @details Specified INT_CTRL register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_INT_CTRL_OD_PUSH_PULL        0x00
#define PRESSURE18_INT_CTRL_OD_OPEN_DRAIN       0x01
#define PRESSURE18_INT_CTRL_LEVEL_ACTIVE_LOW    0x00
#define PRESSURE18_INT_CTRL_LEVEL_ACTIVE_HIGH   0x02
#define PRESSURE18_INT_CTRL_LATCH_DISABLED      0x00
#define PRESSURE18_INT_CTRL_LATCH_ENABLED       0x04
#define PRESSURE18_INT_CTRL_FWTM_DISABLED       0x00
#define PRESSURE18_INT_CTRL_FWTM_ENABLED        0x08
#define PRESSURE18_INT_CTRL_FFULL_DISABLED      0x00
#define PRESSURE18_INT_CTRL_FFULL_ENABLED       0x10
#define PRESSURE18_INT_CTRL_DRDY_DISABLED       0x00
#define PRESSURE18_INT_CTRL_DRDY_ENABLED        0x40

/**
 * @brief Pressure 18 PWR_CTRL register settings.
 * @details Specified PWR_CTRL register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_PWR_CTRL_PRESS_EN            0x01
#define PRESSURE18_PWR_CTRL_TEMP_EN             0x02
#define PRESSURE18_PWR_CTRL_MODE_SLEEP          0x00
#define PRESSURE18_PWR_CTRL_MODE_FORCED         0x10
#define PRESSURE18_PWR_CTRL_MODE_NORMAL         0x30

/**
 * @brief Pressure 18 OSR register settings.
 * @details Specified OSR register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_OSR_P_X1                     0x00
#define PRESSURE18_OSR_P_X2                     0x01
#define PRESSURE18_OSR_P_X4                     0x02
#define PRESSURE18_OSR_P_X8                     0x03
#define PRESSURE18_OSR_P_X16                    0x04
#define PRESSURE18_OSR_P_X32                    0x05
#define PRESSURE18_OSR_T_X1                     0x00
#define PRESSURE18_OSR_T_X2                     0x08
#define PRESSURE18_OSR_T_X4                     0x10
#define PRESSURE18_OSR_T_X8                     0x18
#define PRESSURE18_OSR_T_X16                    0x20
#define PRESSURE18_OSR_T_X32                    0x28

/**
 * @brief Pressure 18 ODR register settings.
 * @details Specified ODR register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_ODR_5_MS                     0x00
#define PRESSURE18_ODR_10_MS                    0x01
#define PRESSURE18_ODR_20_MS                    0x02
#define PRESSURE18_ODR_40_MS                    0x03
#define PRESSURE18_ODR_80_MS                    0x04
#define PRESSURE18_ODR_160_MS                   0x05
#define PRESSURE18_ODR_320_MS                   0x06
#define PRESSURE18_ODR_640_MS                   0x07
#define PRESSURE18_ODR_1p280_S                  0x08
#define PRESSURE18_ODR_2p560_S                  0x09
#define PRESSURE18_ODR_5p120_S                  0x0A
#define PRESSURE18_ODR_10p24_S                  0x0B
#define PRESSURE18_ODR_20p48_S                  0x0C
#define PRESSURE18_ODR_40p96_S                  0x0D
#define PRESSURE18_ODR_81p92_S                  0x0E
#define PRESSURE18_ODR_163p84_S                 0x0F
#define PRESSURE18_ODR_327p68_S                 0x10
#define PRESSURE18_ODR_655p36_S                 0x11        

/**
 * @brief Pressure 18 CMD register settings.
 * @details Specified CMD register settings of Pressure 18 Click driver.
 */
#define PRESSURE18_CMD_NOP                      0x00
#define PRESSURE18_CMD_EXTMODE_EN_MIDDLE        0x34
#define PRESSURE18_CMD_FIFO_FLUSH               0xB0
#define PRESSURE18_CMD_SOFT_RESET               0xB6

/**
 * @brief Pressure 18 Pascal to mBar conversion value.
 * @details Specified Pascal to mBar conversion value of Pressure 18 Click driver.
 */
#define PRESSURE18_PA_TO_MBAR                   0.01

/**
 * @brief Pressure 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 18 Click driver.
 */
#define PRESSURE18_DEVICE_ADDRESS_0             0x76
#define PRESSURE18_DEVICE_ADDRESS_1             0x77

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE18_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE18_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure18_set

/**
 * @defgroup pressure18_map Pressure 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 18 Click driver.
 */

/**
 * @addtogroup pressure18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 18 Click to the selected MikroBUS.
 */
#define PRESSURE18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure18_map
/*! @} */ // pressure18

/**
 * @brief Pressure 18 Click driver selector.
 * @details Selects target driver interface of Pressure 18 Click driver.
 */
typedef enum
{
    PRESSURE18_DRV_SEL_SPI,             /**< SPI driver descriptor. */
    PRESSURE18_DRV_SEL_I2C              /**< I2C driver descriptor. */

} pressure18_drv_t;

/**
 * @brief Pressure 18 Click driver interface.
 * @details Definition of driver interface of Pressure 18 Click driver.
 */
typedef err_t ( *pressure18_master_io_t )( struct pressure18_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Pressure 18 Click calibration coefficients object.
 * @details Calibration coefficients object definition of Pressure 18 Click driver.
 */
typedef struct
{
    float par_t1;
    float par_t2;
    float par_t3;
    float par_p1;
    float par_p2;
    float par_p3;
    float par_p4;
    float par_p5;
    float par_p6;
    float par_p7;
    float par_p8;
    float par_p9;
    float par_p10;
    float par_p11;
    float t_lin;
    
} pressure18_calib_coef_t;

/**
 * @brief Pressure 18 Click context object.
 * @details Context object definition of Pressure 18 Click driver.
 */
typedef struct pressure18_s
{
    digital_in_t int_pin;               /**< Interrupt pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    pressure18_drv_t drv_sel;           /**< Master driver interface selector. */

    pressure18_master_io_t write_f;     /**< Master write function. */
    pressure18_master_io_t read_f;      /**< Master read function. */
    
    pressure18_calib_coef_t calib_coef; /**< Calibration coefficients. */

} pressure18_t;

/**
 * @brief Pressure 18 Click configuration object.
 * @details Configuration object definition of Pressure 18 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;                 /**< Interrupt pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

    pressure18_drv_t drv_sel;           /**< Master driver interface selector. */

} pressure18_cfg_t;

/**
 * @brief Pressure 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE18_OK = 0,
    PRESSURE18_ERROR = -1

} pressure18_return_value_t;

/*!
 * @addtogroup pressure18 Pressure 18 Click Driver
 * @brief API for configuring and manipulating Pressure 18 Click driver.
 * @{
 */

/**
 * @brief Pressure 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure18_cfg_setup ( pressure18_cfg_t *cfg );

/**
 * @brief Pressure 18 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure18_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure18_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure18_drv_interface_selection ( pressure18_cfg_t *cfg, pressure18_drv_t drv_sel );

/**
 * @brief Pressure 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_init ( pressure18_t *ctx, pressure18_cfg_t *cfg );

/**
 * @brief Pressure 18 default configuration function.
 * @details This function executes a default configuration of Pressure 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure18_default_cfg ( pressure18_t *ctx );

/**
 * @brief Pressure 18 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_generic_write ( pressure18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 18 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_generic_read ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 18 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_write_register ( pressure18_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Pressure 18 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_read_register ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Pressure 18 check communication function.
 * @details This function checks communication by reading and verifying the chip ID value.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_check_communication ( pressure18_t *ctx );

/**
 * @brief Pressure 18 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pressure18_get_int_pin ( pressure18_t *ctx );

/**
 * @brief Pressure 18 soft reset function.
 * @details This function performs the software reset feature.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_soft_reset ( pressure18_t *ctx );

/**
 * @brief Pressure 18 read data function.
 * @details This function reads the sensor measurements data: pressure in Pascals and temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[out] pressure : Pressure in Pascals.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure18_read_data ( pressure18_t *ctx, float *pressure, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE18_H

/*! @} */ // pressure18

// ------------------------------------------------------------------------ END

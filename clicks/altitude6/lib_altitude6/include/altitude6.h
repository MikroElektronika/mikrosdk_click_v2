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
 * @file altitude6.h
 * @brief This file contains API for Altitude 6 Click Driver.
 */

#ifndef ALTITUDE6_H
#define ALTITUDE6_H

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
 * @addtogroup altitude6 Altitude 6 Click Driver
 * @brief API for configuring and manipulating Altitude 6 Click driver.
 * @{
 */

/**
 * @defgroup altitude6_reg Altitude 6 Registers List
 * @brief List of registers of Altitude 6 Click driver.
 */

/**
 * @addtogroup altitude6_reg
 * @{
 */

/**
 * @brief Altitude 6 description register.
 * @details Specified register for description of Altitude 6 Click driver.
 */
#define ALTITUDE6_CMD_RESET                           0x1E
#define ALTITUDE6_CMD_CONV_D1_OSR_256                 0x40
#define ALTITUDE6_CMD_CONV_D1_OSR_512                 0x42
#define ALTITUDE6_CMD_CONV_D1_OSR_1024                0x44
#define ALTITUDE6_CMD_CONV_D1_OSR_2048                0x46
#define ALTITUDE6_CMD_CONV_D1_OSR_4096                0x48
#define ALTITUDE6_CMD_CONV_D2_OSR_256                 0x50
#define ALTITUDE6_CMD_CONV_D2_OSR_512                 0x52
#define ALTITUDE6_CMD_CONV_D2_OSR_1024                0x54
#define ALTITUDE6_CMD_CONV_D2_OSR_2048                0x56
#define ALTITUDE6_CMD_CONV_D2_OSR_4096                0x58
#define ALTITUDE6_CMD_ADC_READ                        0x00
#define ALTITUDE6_CMD_PROM_READ_START                 0xA0

/*! @} */ // altitude6_reg

/**
 * @defgroup altitude6_set Altitude 6 Registers Settings
 * @brief Settings for registers of Altitude 6 Click driver.
 */

/**
 * @addtogroup altitude6_set
 * @{
 */

/**
 * @brief Altitude 6 description setting.
 * @details Specified setting for description of Altitude 6 Click driver.
 */
#define ALTITUDE6_RATIO_256                           0x00       
#define ALTITUDE6_RATIO_512                           0x01
#define ALTITUDE6_RATIO_1024                          0x02
#define ALTITUDE6_RATIO_2048                          0x03
#define ALTITUDE6_RATIO_4096                          0x04

/**
 * @brief Altitude 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Altitude 6 Click driver.
 */
#define ALTITUDE6_SET_DEV_ADDR_1                      0x76
#define ALTITUDE6_SET_DEV_ADDR_0                      0x77

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b altitude6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ALTITUDE6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ALTITUDE6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // altitude6_set

/**
 * @defgroup altitude6_map Altitude 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Altitude 6 Click driver.
 */

/**
 * @addtogroup altitude6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Altitude 6 Click to the selected MikroBUS.
 */
#define ALTITUDE6_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // altitude6_map
/*! @} */ // altitude6

/**
 * @brief Altitude 6 Click driver selector.
 * @details Selects target driver interface of Altitude 6 Click driver.
 */
typedef enum
{
    ALTITUDE6_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ALTITUDE6_DRV_SEL_I2C       /**< I2C driver descriptor. */

} altitude6_drv_t;

/**
 * @brief Altitude 6 Click driver interface.
 * @details Definition of driver interface of Altitude 6 Click driver.
 */
typedef err_t ( *altitude6_master_io_t )( struct altitude6_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Altitude 6 Click context object.
 * @details Context object definition of Altitude 6 Click driver.
 */
typedef struct altitude6_s
{
    i2c_master_t  i2c;                     /**< I2C driver object. */
    spi_master_t  spi;                     /**< SPI driver object. */

    uint8_t     slave_address;             /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;               /**< Chip select pin descriptor (used for SPI driver). */
    altitude6_drv_t  drv_sel;              /**< Master driver interface selector. */

    altitude6_master_io_t  write_f;        /**< Master write function. */
    altitude6_master_io_t  read_f;         /**< Master read function. */
    
    float sea_lvl_pressure;                /**< Sea-level pressure. */
    
    uint16_t press_sens_c1;       /**< Pressure sensitivity. */
    uint16_t press_off_c2;        /**< Pressure offset. */
    uint16_t press_tcs_c3;        /**< Temperature coefficient of pressure sensitivity. */
    uint16_t press_tco_c4;        /**< Temperature coefficient of pressure offset. */
    uint16_t press_tref_c5;       /**< Reference temperature. */
    uint16_t press_tempsens_c6;   /**< Temperature coefficient of the temperature. */
    
    uint8_t ratio_temp;           /**< Temperature ratio. */
    uint8_t ratio_press;          /**< Pressure ratio. */

} altitude6_t;

/**
 * @brief Altitude 6 Click configuration object.
 * @details Configuration object definition of Altitude 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    altitude6_drv_t  drv_sel;     /**< Master driver interface selector. */
    
    float sea_level_pressure;     /**< Sea-level pressure. */

} altitude6_cfg_t;

/**
 * @brief Altitude 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ALTITUDE6_OK = 0,
    ALTITUDE6_ERROR = -1

} altitude6_return_value_t;

/*!
 * @addtogroup altitude6 Altitude 6 Click Driver
 * @brief API for configuring and manipulating Altitude 6 Click driver.
 * @{
 */

/**
 * @brief Altitude 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #altitude6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void altitude6_cfg_setup ( altitude6_cfg_t *cfg );

/**
 * @brief Altitude 6 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #altitude6_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #altitude6_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void altitude6_drv_interface_selection ( altitude6_cfg_t *cfg, altitude6_drv_t drv_sel );

/**
 * @brief Altitude 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #altitude6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude6_init ( altitude6_t *ctx, altitude6_cfg_t *cfg );

/**
 * @brief Altitude 6 default configuration function.
 * @details This function executes a default configuration of Altitude 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t altitude6_default_cfg ( altitude6_t *ctx );

/**
 * @brief Altitude 6 set command function.
 * @details This function writes a desired command
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude6_set_command ( altitude6_t *ctx, uint8_t cmd );

/**
 * @brief Altitude 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude6_generic_read ( altitude6_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Altitude 6 set data ratio function.
 * @details This function set data ratio
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] temp_ratio : Determines oversampling ratio for temperature measurement.
 * @param[in] press_ratio : Determines oversampling ration for pressure measurement.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t altitude6_set_ratio ( altitude6_t *ctx, uint8_t temp_ratio, uint8_t press_ratio );

/**
 * @brief Altitude 6 software reset function.
 * @details This function performs a software reset
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a reset - reload delay of the 3 milliseconds.
 */
err_t altitude6_sw_reset ( altitude6_t *ctx );

/**
 * @brief Altitude 6 get calibration data function.
 * @details This function read and store calibration data
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t altitude6_get_calibration_data ( altitude6_t *ctx );

/**
 * @brief Altitude 6 get raw data function.
 * @details This function read raw temperature and pressure data
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[out] temp_data : Raw temperature data.
 * @param[out] press_data : Raw pressure data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 20 milliseconds.
 */
err_t altitude6_get_raw_data ( altitude6_t *ctx, uint32_t *temp_data, uint32_t *press_data );

/**
 * @brief Altitude 6 get temperature data function.
 * @details This function read temperature data and convert to the degree Celsius
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degree Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t altitude6_get_temperature ( altitude6_t *ctx, float *temperature );

/**
 * @brief Altitude 6 get pressure data function.
 * @details This function read pressure data and convert to the mbar
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[out] pressure : Pressure in mbar.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t altitude6_get_pressure ( altitude6_t *ctx, float *pressure );

/**
 * @brief Altitude 6 get data function.
 * @details This function read temperature and pressure data, 
 * convert temperature data to the degree Celsius and pressure data to the mbar 
 * of the MS5611 Barometric Pressure Sensor, with stainless steel cap
 * on the Altitude 6 click board™
 * Depending on the temperature and pressure data, function calculates altitude in meters
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degree Celsius.
 * @param[out] pressure : Pressure in mbar.
 * @param[out] altitude : Altitude data in meters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 20 milliseconds.
 */
err_t altitude6_get_data ( altitude6_t *ctx, float *temperature, float *pressure, float *altitude );



#ifdef __cplusplus
}
#endif
#endif // ALTITUDE6_H

/*! @} */ // altitude6

// ------------------------------------------------------------------------ END

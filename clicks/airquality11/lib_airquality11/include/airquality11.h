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
 * @file airquality11.h
 * @brief This file contains API for Air Quality 11 Click Driver.
 */

#ifndef AIRQUALITY11_H
#define AIRQUALITY11_H

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
 * @addtogroup airquality11 Air Quality 11 Click Driver
 * @brief API for configuring and manipulating Air Quality 11 Click driver.
 * @{
 */

/**
 * @defgroup airquality11_reg Air Quality 11 Registers List
 * @brief List of registers of Air Quality 11 Click driver.
 */

/**
 * @addtogroup airquality11_reg
 * @{
 */

/**
 * @brief Air Quality 11 description register.
 * @details Specified register for description of Air Quality 11 Click driver.
 */
#define AIRQUALITY11_REG_PART_ID               0x00
#define AIRQUALITY11_REG_OPMODE                0x10
#define AIRQUALITY11_REG_CONFIG                0x11
#define AIRQUALITY11_REG_COMMAND               0x12
#define AIRQUALITY11_REG_TEMP_IN               0x13
#define AIRQUALITY11_REG_RH_IN                 0x15
#define AIRQUALITY11_REG_DEVICE_STATUS         0x20
#define AIRQUALITY11_REG_DATA_AQI_UBA          0x21
#define AIRQUALITY11_REG_DATA_ETVOC            0x22
#define AIRQUALITY11_REG_DATA_ECO2             0x24
#define AIRQUALITY11_REG_DATA_AQI_S            0x26
#define AIRQUALITY11_REG_DATA_T                0x30
#define AIRQUALITY11_REG_DATA_RH               0x32
#define AIRQUALITY11_REG_DATA_MISR             0x38
#define AIRQUALITY11_REG_GPR_WRITE             0x40
#define AIRQUALITY11_REG_GPR_READ              0x48


/*! @} */ // airquality11_reg

/**
 * @defgroup airquality11_set Air Quality 11 Registers Settings
 * @brief Settings for registers of Air Quality 11 Click driver.
 */

/**
 * @addtogroup airquality11_set
 * @{
 */

/**
 * @brief Air Quality 11 measure conditions data values.
 * @details Measure conditions operating ranges of Air Quality 11 Click driver.
 */
#define AIRQUALITY11_TEMP_MIN                 -40.0f
#define AIRQUALITY11_TEMP_MAX                  80.0f
#define AIRQUALITY11_TEMP_CALC_KC              273.15f
#define AIRQUALITY11_TEMP_CALC_MLT             64.0f
#define AIRQUALITY11_HUM_MIN                   5.0f
#define AIRQUALITY11_HUM_MAX                   95.0f
#define AIRQUALITY11_HUM_CALC_MLT              512.0f

/**
 * @brief Air Quality 11 AQI-UBA rating values.
 * @details Specified AQI-UBA rating values of Air Quality 11 Click driver.
 */
#define AIRQUALITY11_AQI_UBA_EXELLENT          1
#define AIRQUALITY11_AQI_UBA_GOOD              2
#define AIRQUALITY11_AQI_UBA_MODERATE          3
#define AIRQUALITY11_AQI_UBA_POOR              4
#define AIRQUALITY11_AQI_UBA_UNHEALTHY         5

/**
 * @brief Air Quality 11 air quality index according to the UBA bitmask.
 * @details Air quality index according to the UBA bitmask of Air Quality 11 Click driver.
 */
#define AIRQUALITY11_AQI_UBA_BITMASK            0x07

/**
 * @brief Air Quality 11 device identity value.
 * @details Device identity value of Air Quality 11 Click driver.
 */
#define AIRQUALITY11_PART_ID                   0x0161u

/**
 * @brief Air Quality 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Air Quality 11 Click driver.
 */
#define AIRQUALITY11_DEVICE_ADDRESS_0          0x52
#define AIRQUALITY11_DEVICE_ADDRESS_1          0x53

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b airquality11_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define AIRQUALITY11_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define AIRQUALITY11_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // airquality11_set

/**
 * @defgroup airquality11_map Air Quality 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Air Quality 11 Click driver.
 */

/**
 * @addtogroup airquality11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Quality 11 Click to the selected MikroBUS.
 */
#define AIRQUALITY11_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // airquality11_map
/*! @} */ // airquality11

/**
 * @brief Air Quality 11 Click driver selector.
 * @details Selects target driver interface of Air Quality 11 Click driver.
 */
typedef enum
{
    AIRQUALITY11_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    AIRQUALITY11_DRV_SEL_I2C       /**< I2C driver descriptor. */

} airquality11_drv_t;

/**
 * @brief Air Quality 11 Click driver interface.
 * @details Definition of driver interface of Air Quality 11 Click driver.
 */
struct airquality11_s;
typedef err_t ( *airquality11_master_io_t )( struct airquality11_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Air Quality 11 Click context object.
 * @details Context object definition of Air Quality 11 Click driver.
 */
typedef struct airquality11_s
{
    digital_out_t en;        /**< Enable pin. */

    digital_in_t int_pin;    /**< Interrupt pin. */

    i2c_master_t i2c;        /**< I2C driver object. */
    spi_master_t spi;        /**< SPI driver object. */

    uint8_t      slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    airquality11_drv_t drv_sel;          /**< Master driver interface selector. */

    airquality11_master_io_t write_f;    /**< Master write function. */
    airquality11_master_io_t read_f;     /**< Master read function. */

    float temperature;   /**< Temperature used in its calculations. */
    float humidity;      /**< Relative humidity used in its calculations. */

} airquality11_t;

/**
 * @brief Air Quality 11 Click configuration object.
 * @details Configuration object definition of Air Quality 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t en;         /**< Enable pin. */
    pin_name_t int_pin;    /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    airquality11_drv_t drv_sel;                /**< Master driver interface selector. */

} airquality11_cfg_t;

/**
 * @brief Air Quality 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIRQUALITY11_OK = 0,
    AIRQUALITY11_ERROR = -1

} airquality11_return_value_t;

/**
 * @brief Air Quality 11 Click operating mode value data.
 * @details Predefined enum values for driver operating mode values.
 */
typedef enum
{
    AIRQUALITY11_DEEP_SLEEP = 0,  /**< Limited functionality. */
    AIRQUALITY11_IDLE,            /**< Intended for configuration before running an active sensing mode. */
    AIRQUALITY11_STANDARD,        /**< Active gas sensing mode to indicate the levels of air quality or for specific gas detection at 1 sample/second. */
    AIRQUALITY11_LOW_POWER,       /**< Active power-saving gas sensing mode, indicating the levels of air quality at 1 sample/minute. */
    AIRQUALITY11_ULTRA_LOW_POWER, /**< Active power-saving gas sensing mode, indicating the levels of air quality at 1 sample/5 minutes. */
    AIRQUALITY11_RESET = 0xF0     /**< Software reset. */

} airquality11_op_mode_t;

/**
 * @brief Air Quality 11 Click command value data.
 * @details Predefined enum values for driver command values.
 */
typedef enum
{
    AIRQUALITY11_CMD_NOP = 0x00,        /**< Command NOP. */
    AIRQUALITY11_CMD_GET_APPVER = 0x0E, /**< Firmware version of the ENS161 will be placed in General Purpose Registers. */
    AIRQUALITY11_CMD_CLRGPR = 0xCC      /**< Clear all GPR Read Registers. */

} airquality11_cmd_t;

/*!
 * @addtogroup airquality11 Air Quality 11 Click Driver
 * @brief API for configuring and manipulating Air Quality 11 Click driver.
 * @{
 */

/**
 * @brief Air Quality 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airquality11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airquality11_cfg_setup ( airquality11_cfg_t *cfg );

/**
 * @brief Air Quality 11 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #airquality11_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #airquality11_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void airquality11_drv_interface_sel ( airquality11_cfg_t *cfg, airquality11_drv_t drv_sel );

/**
 * @brief Air Quality 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airquality11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_init ( airquality11_t *ctx, airquality11_cfg_t *cfg );

/**
 * @brief Air Quality 11 default configuration function.
 * @details This function executes a default configuration of Air Quality 11
 * Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t airquality11_default_cfg ( airquality11_t *ctx );

/**
 * @brief Air Quality 11 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_generic_write ( airquality11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Quality 11 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_generic_read ( airquality11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Air Quality 11 word data writing function.
 * @details This function writes a desired 16-byte data to the selected register
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 16-byte data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_write_word ( airquality11_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Air Quality 11 word data reading function.
 * @details This function reads a 16-byte data from the selected register 
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : 16-byte output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_read_word ( airquality11_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Air Quality 11 get device ID function.
 * @details This function reads the device ID (part number)
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] device_id : Part number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_device_id ( airquality11_t *ctx, uint16_t *device_id );

/**
 * @brief Air Quality 11 set operating mode function.
 * @details This function sets the desired operating mode
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode selection.
 * See #airquality11_op_mode_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_set_op_mode ( airquality11_t *ctx, airquality11_op_mode_t op_mode );

/**
 * @brief Air Quality 11 set configures function.
 * @details This function configures the action of the interrupt (INT) pin
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] cfg : Configures the action of the interrupt pin.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_set_int_config ( airquality11_t *ctx, uint8_t int_cfg );

/**
 * @brief Air Quality 11 set command function.
 * @details This function sets the desired command
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] cmd : Additional commands to be executed.
 * See #airquality11_cmd_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_set_cmd ( airquality11_t *ctx, airquality11_cmd_t cmd );

/**
 * @brief Air Quality 11 set measure conditions function.
 * @details This function sets the desired temperature and humidity measure conditions 
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] temperature : Temperature in degrees Celsius [-40.0-80.0].
 * @param[in] humidity : Relative humidity in percent [5.0-95.0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_set_measure_c ( airquality11_t *ctx, float temperature, float humidity );

/**
 * @brief Air Quality 11 get status function.
 * @details This function reads the status register
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_status ( airquality11_t *ctx, uint8_t *status );

/**
 * @brief Air Quality 11 get AQI-UBA function.
 * @details This function reads the calculated Air Quality Index according to the UBA
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] aqi_uba : Air Quality Index according to the UBA [1-5].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_aqi_uba ( airquality11_t *ctx, uint8_t *aqi_uba );

/**
 * @brief Air Quality 11 get TVOC function.
 * @details This function reads the calculated equivalent TVOC concentration in ppb
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] tvoc_ppb : TVOC concentration in ppb [0-65000].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_tvoc ( airquality11_t *ctx, uint16_t *tvoc_ppb );

/**
 * @brief Air Quality 11 get CO2 function.
 * @details This function reads the calculated equivalent CO2 concentration in ppm
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] co2_ppm : CO2 concentration in ppm [400-65000].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_co2 ( airquality11_t *ctx, uint16_t *co2_ppm );

/**
 * @brief Air Quality 11 get AQI-S function.
 * @details This function reads the calculated relative Air Quality Index proprietary to ScioSense
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] aqi_s : Air Quality Index proprietary to ScioSense [0-500].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_aqi_s ( airquality11_t *ctx, uint16_t *aqi_s );

/**
 * @brief Air Quality 11 get measure conditions function.
 * @details This function reads the temperature and humidity measure conditions 
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degrees Celsius [-40.0-80.0].
 * @param[out] humidity : Relative humidity in percent [5.0-95.0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_get_measure_c ( airquality11_t *ctx, float *temperature, float *humidity );

/**
 * @brief Air Quality 11 GPR data writing function.
 * @details This function writes a 8 data bytes to the general purpose write registers
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] data_in : GPR data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_write_gpr_reg ( airquality11_t *ctx, uint8_t *data_in );

/**
 * @brief Air Quality 11 GPR data reading function.
 * @details This function reads a 8 data bytes to the general purpose read registers
 * of the ENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[out] data_out : GPR output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality11_read_gpr_reg ( airquality11_t *ctx, uint8_t *data_out );

/**
 * @brief Rotary O 2 get interrupt function.
 * @details This function return interrupt signal, states of the INT pin
 * of theENS161, Digital Metal-Oxide Multi-Gas Sensor with permanent and low power operating modes
 * on the Air Quality 11 Click board.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @return @li @c 0 - Low state,
 *         @li @c 1 - High state.
 * @note None.
 */
uint8_t airquality11_get_interrupt ( airquality11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AIRQUALITY11_H

/*! @} */ // airquality11

// ------------------------------------------------------------------------ END

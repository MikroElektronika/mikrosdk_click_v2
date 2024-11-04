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
 * @file gyro8.h
 * @brief This file contains API for Gyro 8 Click Driver.
 */

#ifndef GYRO8_H
#define GYRO8_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup gyro8 Gyro 8 Click Driver
 * @brief API for configuring and manipulating Gyro 8 Click driver.
 * @{
 */

/**
 * @defgroup gyro8_reg Gyro 8 Registers List
 * @brief List of registers of Gyro 8 Click driver.
 */

/**
 * @addtogroup gyro8_reg
 * @{
 */

/**
 * @brief Gyro 8 register list.
 * @details Specified register list of Gyro 8 Click driver.
 */
#define GYRO8_REG_RATE                  0x01
#define GYRO8_REG_TEMP                  0x07
#define GYRO8_REG_RATE_STATUS_1         0x09
#define GYRO8_REG_RATE_STATUS_2         0x0A
#define GYRO8_REG_ACC_STATUS            0x0F
#define GYRO8_REG_TEST                  0x15
#define GYRO8_REG_RESET_CONTROL         0x16
#define GYRO8_REG_SERIAL_ID0            0x18
#define GYRO8_REG_SERIAL_ID1            0x19
#define GYRO8_REG_COMMON_STATUS         0x1B
#define GYRO8_REG_ID                    0x1D
#define GYRO8_REG_STATUS_SUMMARY        0x1F

/*! @} */ // gyro8_reg

/**
 * @defgroup gyro8_set Gyro 8 Registers Settings
 * @brief Settings for registers of Gyro 8 Click driver.
 */

/**
 * @addtogroup gyro8_set
 * @{
 */

/**
 * @brief Gyro 8 identification setting.
 * @details Specified setting for identification of Gyro 8 Click driver.
 */
#define GYRO8_ID                        0x0500

/**
 * @brief Gyro 8 temperature and angular calculation values.
 * @details Specified temperature and angular calculation values of Gyro 8 Click driver.
 */
#define GYRO8_TEMP_SENS                 14.7f
#define GYRO8_TEMP_OFFSET               60.0f
#define GYRO8_GYRO_SENS                 50.0f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gyro8_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GYRO8_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define GYRO8_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gyro8_set

/**
 * @defgroup gyro8_map Gyro 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Gyro 8 Click driver.
 */

/**
 * @addtogroup gyro8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Gyro 8 Click to the selected MikroBUS.
 */
#define GYRO8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // gyro8_map
/*! @} */ // gyro8

/**
 * @brief Gyro 8 Click context object.
 * @details Context object definition of Gyro 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< External reset pin (Active Low). */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t    chip_select;      /**< Chip select pin descriptor (used for SPI driver). */

} gyro8_t;

/**
 * @brief Gyro 8 Click configuration object.
 * @details Configuration object definition of Gyro 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< External reset pin (Active Low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} gyro8_cfg_t;

/**
 * @brief Gyro 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GYRO8_OK = 0,
    GYRO8_ERROR = -1

} gyro8_return_value_t;

/*!
 * @addtogroup gyro8 Gyro 8 Click Driver
 * @brief API for configuring and manipulating Gyro 8 Click driver.
 * @{
 */

/**
 * @brief Gyro 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gyro8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gyro8_cfg_setup ( gyro8_cfg_t *cfg );

/**
 * @brief Gyro 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gyro8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_init ( gyro8_t *ctx, gyro8_cfg_t *cfg );

/**
 * @brief Gyro 8 default configuration function.
 * @details This function executes a default configuration of Gyro 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gyro8_default_cfg ( gyro8_t *ctx );

/**
 * @brief Gyro 8 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_write_register ( gyro8_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Gyro 8 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_read_register ( gyro8_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Gyro 8 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gyro8_set_rst_pin ( gyro8_t *ctx, uint8_t state );

/**
 * @brief Gyro 8 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gyro8_reset_device ( gyro8_t *ctx );

/**
 * @brief Gyro 8 check communication function.
 * @details This function checks the communication by reading and verifying the product ID.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_check_communication ( gyro8_t *ctx );

/**
 * @brief Gyro 8 read serial id function.
 * @details This function reads the serial ID which is laser marked on the sensor lid.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[out] serial_id : Serial ID laser marked on the sensor lid.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_read_serial_id ( gyro8_t *ctx, uint32_t *serial_id );

/**
 * @brief Gyro 8 read temperature function.
 * @details This function reads the temperature measurement in Celsius.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_read_temperature ( gyro8_t *ctx, float *temperature );

/**
 * @brief Gyro 8 read angular rate function.
 * @details This function reads the angular rate of X-axis in dps.
 * @param[in] ctx : Click context object.
 * See #gyro8_t object definition for detailed explanation.
 * @param[out] rate : Angular rate in dps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro8_read_angular_rate ( gyro8_t *ctx, float *rate );

#ifdef __cplusplus
}
#endif
#endif // GYRO8_H

/*! @} */ // gyro8

// ------------------------------------------------------------------------ END

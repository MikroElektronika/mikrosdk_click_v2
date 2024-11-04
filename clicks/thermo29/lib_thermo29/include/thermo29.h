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
 * @file thermo29.h
 * @brief This file contains API for Thermo 29 Click Driver.
 */

#ifndef THERMO29_H
#define THERMO29_H

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
 * @addtogroup thermo29 Thermo 29 Click Driver
 * @brief API for configuring and manipulating Thermo 29 Click driver.
 * @{
 */

/**
 * @defgroup thermo29_reg Thermo 29 Registers List
 * @brief List of registers of Thermo 29 Click driver.
 */

/**
 * @addtogroup thermo29_reg
 * @{
 */

/**
 * @brief Thermo 29 register map.
 * @details Specified register map of Thermo 29 Click driver.
 */
#define THERMO29_REG_TEMP_RESULT                0x00
#define THERMO29_REG_SLEW_RESULT                0x01
#define THERMO29_REG_ALERT_STATUS               0x02
#define THERMO29_REG_CONFIGURATION              0x03
#define THERMO29_REG_ALERT_ENABLE               0x04
#define THERMO29_REG_TLOW_LIMIT                 0x05
#define THERMO29_REG_THIGH_LIMIT                0x06
#define THERMO29_REG_HYSTERESIS                 0x07
#define THERMO29_REG_SLEW_LIMIT                 0x08
#define THERMO29_REG_UNIQUE_ID1                 0x09
#define THERMO29_REG_UNIQUE_ID2                 0x0A
#define THERMO29_REG_UNIQUE_ID3                 0x0B
#define THERMO29_REG_DEVICE_ID                  0x0C

/*! @} */ // thermo29_reg

/**
 * @defgroup thermo29_set Thermo 29 Registers Settings
 * @brief Settings for registers of Thermo 29 Click driver.
 */

/**
 * @addtogroup thermo29_set
 * @{
 */

/**
 * @brief Thermo 29 configuration register setting.
 * @details Specified setting for configuration register of Thermo 29 Click driver.
 */
#define THERMO29_CONFIGURATION_RESETS           0x0100u
#define THERMO29_CONFIGURATION_AVG              0x0080u
#define THERMO29_CONFIGURATION_INT_COMP         0x0020u
#define THERMO29_CONFIGURATION_ONE_SHOT         0x0010u
#define THERMO29_CONFIGURATION_MODE_CONT        0x0000u
#define THERMO29_CONFIGURATION_MODE_SHDN        0x0008u
#define THERMO29_CONFIGURATION_MODE_MASK        0x0008u
#define THERMO29_CONFIGURATION_CONV_PER_6MS     0x0000u
#define THERMO29_CONFIGURATION_CONV_PER_31_25MS 0x0001u
#define THERMO29_CONFIGURATION_CONV_PER_62_5MS  0x0002u
#define THERMO29_CONFIGURATION_CONV_PER_125MS   0x0003u
#define THERMO29_CONFIGURATION_CONV_PER_250MS   0x0004u
#define THERMO29_CONFIGURATION_CONV_PER_500MS   0x0005u
#define THERMO29_CONFIGURATION_CONV_PER_1S      0x0006u
#define THERMO29_CONFIGURATION_CONV_PER_2S      0x0007u
#define THERMO29_CONFIGURATION_CONV_PER_MASK    0x0007u

/**
 * @brief Thermo 29 alert enable register setting.
 * @details Specified setting for alert enable register of Thermo 29 Click driver.
 */
#define THERMO29_ALERT_ENABLE_CRC               0x0010u
#define THERMO29_ALERT_ENABLE_SLEW              0x0008u
#define THERMO29_ALERT_ENABLE_THIG              0x0004u
#define THERMO29_ALERT_ENABLE_TLOW              0x0002u
#define THERMO29_ALERT_ENABLE_DATA_READY        0x0001u

/**
 * @brief Thermo 29 command word setting.
 * @details Specified setting for command word of Thermo 29 Click driver.
 */
#define THERMO29_CRC_ENABLE                     0x40
#define THERMO29_CRC_DATA_BLOCK_LEN_MASK        0x3C
#define THERMO29_AUTO_INCREMENT                 0x02
#define THERMO29_READ_BIT                       0x01
#define THERMO29_WRITE_BIT                      0x00
#define THERMO29_DATA_LEN_MAX                   10

/**
 * @brief Thermo 29 temperature calculation setting.
 * @details Specified setting for temperature calculation of Thermo 29 Click driver.
 */
#define THERMO29_TEMP_RESOLUTION                0.03125f

/**
 * @brief Thermo 29 device ID setting.
 * @details Specified setting for device ID of Thermo 29 Click driver.
 */
#define THERMO29_DEVICE_REV_MASK                0xF000u
#define THERMO29_DEVICE_ID_MASK                 0x0FFFu
#define THERMO29_DEVICE_ID                      0x0126u

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thermo29_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THERMO29_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define THERMO29_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // thermo29_set

/**
 * @defgroup thermo29_map Thermo 29 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 29 Click driver.
 */

/**
 * @addtogroup thermo29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 29 Click to the selected MikroBUS.
 */
#define THERMO29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo29_map
/*! @} */ // thermo29

/**
 * @brief Thermo 29 Click context object.
 * @details Context object definition of Thermo 29 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alert;             /**< Alert pin (Active LOW). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    
    bool         crc_enable;        /**< CRC enable flag. */

} thermo29_t;

/**
 * @brief Thermo 29 Click configuration object.
 * @details Configuration object definition of Thermo 29 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t alert;               /**< Alert pin (Active LOW). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} thermo29_cfg_t;

/**
 * @brief Thermo 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO29_OK = 0,
    THERMO29_ERROR = -1

} thermo29_return_value_t;

/*!
 * @addtogroup thermo29 Thermo 29 Click Driver
 * @brief API for configuring and manipulating Thermo 29 Click driver.
 * @{
 */

/**
 * @brief Thermo 29 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo29_cfg_setup ( thermo29_cfg_t *cfg );

/**
 * @brief Thermo 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_init ( thermo29_t *ctx, thermo29_cfg_t *cfg );

/**
 * @brief Thermo 29 default configuration function.
 * @details This function executes a default configuration of Thermo 29
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo29_default_cfg ( thermo29_t *ctx );

/**
 * @brief Thermo 29 write register function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_write_register ( thermo29_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Thermo 29 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_read_register ( thermo29_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Thermo 29 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written ( up to 10 bytes ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_write_registers ( thermo29_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t len );

/**
 * @brief Thermo 29 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read ( up to 10 bytes ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_read_registers ( thermo29_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief Thermo 29 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermo29_get_alert_pin ( thermo29_t *ctx );

/**
 * @brief Thermo 29 enable crc function.
 * @details This function enables CRC for writing and reading transactions.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thermo29_enable_crc ( thermo29_t *ctx );

/**
 * @brief Thermo 29 disable crc function.
 * @details This function disables CRC for writing and reading transactions.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thermo29_disable_crc ( thermo29_t *ctx );

/**
 * @brief Thermo 29 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_check_communication ( thermo29_t *ctx );

/**
 * @brief Thermo 29 read unique id function.
 * @details This function reads the device unique ID words (6 bytes in total).
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[out] unique_id : Device unique ID words ( 3 x 16-bit data ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_read_unique_id ( thermo29_t *ctx, uint16_t *unique_id );

/**
 * @brief Thermo 29 read temperature function.
 * @details This function reads the temperature measurement in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_read_temperature ( thermo29_t *ctx, float *temperature );

/**
 * @brief Thermo 29 clear alert status function.
 * @details This function clears the alert status register.
 * @param[in] ctx : Click context object.
 * See #thermo29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo29_clear_alert_status ( thermo29_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THERMO29_H

/*! @} */ // thermo29

// ------------------------------------------------------------------------ END

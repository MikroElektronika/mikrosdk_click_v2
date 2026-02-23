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
 * @file pressure24.h
 * @brief This file contains API for Pressure 24 Click Driver.
 */

#ifndef PRESSURE24_H
#define PRESSURE24_H

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
 * @addtogroup pressure24 Pressure 24 Click Driver
 * @brief API for configuring and manipulating Pressure 24 Click driver.
 * @{
 */

/**
 * @defgroup pressure24_cmd Pressure 24 Commands List
 * @brief List of commands of Pressure 24 Click driver.
 */

/**
 * @addtogroup pressure24_cmd
 * @{
 */

/**
 * @brief Pressure 24 command list.
 * @details Specified command list of Pressure 24 Click driver.
 */
#define PRESSURE24_CMD_ACQUIRE_PRESSURE_10BIT       0x30
#define PRESSURE24_CMD_ACQUIRE_PRESSURE_12BIT       0x34
#define PRESSURE24_CMD_ACQUIRE_PRESSURE_14BIT       0x38
#define PRESSURE24_CMD_ACQUIRE_TEMPERATURE_10BIT    0x50
#define PRESSURE24_CMD_ACQUIRE_TEMPERATURE_12BIT    0x54
#define PRESSURE24_CMD_ACQUIRE_TEMPERATURE_14BIT    0x58
#define PRESSURE24_CMD_TRIGGER_DIAG_10BIT           0x90
#define PRESSURE24_CMD_TRIGGER_DIAG_12BIT           0x94
#define PRESSURE24_CMD_TRIGGER_DIAG_14BIT           0x98
#define PRESSURE24_CMD_TRIGGER_POWER_DOWN           0xA0
#define PRESSURE24_CMD_ACQUIRE_IDENTIFIER           0xF0
#define PRESSURE24_CMD_RESET_DIAG                   0x00

/*! @} */ // pressure24_cmd

/**
 * @defgroup pressure24_set Pressure 24 Commands Settings
 * @brief Settings for commands of Pressure 24 Click driver.
 */

/**
 * @addtogroup pressure24_set
 * @{
 */

/**
 * @brief Pressure 24 diagnosis bits.
 * @details Specified diagnosis bits of Pressure 24 Click driver.
 */
#define PRESSURE24_DIAG_ECC_ERROR                   0x8000
#define PRESSURE24_DIAG_ACQ_CHAIN_FAIL              0x4000
#define PRESSURE24_DIAG_SENSOR_SELL_FAIL            0x2000
#define PRESSURE24_DIAG_PRESS_HIGH                  0x1000
#define PRESSURE24_DIAG_PRESS_LOW                   0x0800
#define PRESSURE24_DIAG_OK                          0x5000

/**
 * @brief Pressure 24 ODD parity flag.
 * @details Specified flag for ODD parity of Pressure 24 Click driver.
 */
#define PRESSURE24_ODD_PARITY                       0x01

/**
 * @brief Pressure 24 identifier SPI ID.
 * @details Specified identifier SPI ID of Pressure 24 Click driver.
 */
#define PRESSURE24_IDENTIFIER_SPI_ID                0x67
#define PRESSURE24_IDENTIFIER_SPI_ID_MASK           0xFF

/**
 * @brief Pressure 24 pressure and temperature calculation.
 * @details Specified pressure and temperature calculation of Pressure 24 Click driver.
 */
#define PRESSURE24_SP_14BIT                         6.301
#define PRESSURE24_OFFSP_14BIT                   ( -3780.69 )
#define PRESSURE24_ST_14BIT                         99.29
#define PRESSURE24_OFFST_14BIT_5V                   3971.64
#define PRESSURE24_OFFST_14BIT_3V3                  3822.7

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure24_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE24_SET_DATA_SAMPLE_EDGE             SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE24_SET_DATA_SAMPLE_MIDDLE           SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure24_set

/**
 * @defgroup pressure24_map Pressure 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 24 Click driver.
 */

/**
 * @addtogroup pressure24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 24 Click to the selected MikroBUS.
 */
#define PRESSURE24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // pressure24_map
/*! @} */ // pressure24

/**
 * @brief Pressure 24 Click context object.
 * @details Context object definition of Pressure 24 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t      prev_cmd;          /**< Previous command. */

} pressure24_t;

/**
 * @brief Pressure 24 Click configuration object.
 * @details Configuration object definition of Pressure 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} pressure24_cfg_t;

/**
 * @brief Pressure 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE24_OK = 0,
    PRESSURE24_ERROR = -1

} pressure24_return_value_t;

/*!
 * @addtogroup pressure24 Pressure 24 Click Driver
 * @brief API for configuring and manipulating Pressure 24 Click driver.
 * @{
 */

/**
 * @brief Pressure 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure24_cfg_setup ( pressure24_cfg_t *cfg );

/**
 * @brief Pressure 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure24_init ( pressure24_t *ctx, pressure24_cfg_t *cfg );

/**
 * @brief Pressure 24 send command function.
 * @details This function sends a command over the SPI interface, reads the previous
 * response word and validates the odd parity bit.
 * @param[in] ctx : Click context object.
 * See #pressure24_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @param[out] prev_rsp : Pointer to the previous response word (can be NULL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure24_send_cmd ( pressure24_t *ctx, uint8_t cmd, uint16_t *prev_rsp );

/**
 * @brief Pressure 24 get pressure function.
 * @details This function triggers a 14-bit pressure acquisition and calculates the result in millibars.
 * @param[in] ctx : Click context object.
 * See #pressure24_t object definition for detailed explanation.
 * @param[out] press : Pressure value in millibars.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure24_get_pressure ( pressure24_t *ctx, float *press );

/**
 * @brief Pressure 24 get temperature function.
 * @details This function triggers a 14-bit temperature acquisition and calculates the result in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #pressure24_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure24_get_temperature ( pressure24_t *ctx, float *temp );

/**
 * @brief Pressure 24 get identifier function.
 * @details This function triggers an identifier acquisition and reads the identifier response word.
 * @param[in] ctx : Click context object.
 * See #pressure24_t object definition for detailed explanation.
 * @param[out] identifier : Pointer to the raw identifier value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure24_get_identifier ( pressure24_t *ctx, uint16_t *identifier );

/**
 * @brief Pressure 24 power down function.
 * @details This function sends the command that triggers the device power-down mode.
 * @param[in] ctx : Click context object.
 * See #pressure24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure24_power_down ( pressure24_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE24_H

/*! @} */ // pressure24

// ------------------------------------------------------------------------ END

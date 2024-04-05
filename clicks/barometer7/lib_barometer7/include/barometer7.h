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
 * @file barometer7.h
 * @brief This file contains API for Barometer 7 Click Driver.
 */

#ifndef BAROMETER7_H
#define BAROMETER7_H

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
 * @addtogroup barometer7 Barometer 7 Click Driver
 * @brief API for configuring and manipulating Barometer 7 Click driver.
 * @{
 */

/**
 * @defgroup barometer7_cmd Barometer 7 Registers List
 * @brief List of registers of Barometer 7 Click driver.
 */

/**
 * @addtogroup barometer7_cmd
 * @{
 */

/**
 * @brief Barometer 7 description commands.
 * @details Specified commands for description of Barometer 7 Click driver.
 */
#define BAROMETER7_CMD_TRIGGER_TEST_MODE        0x0C
#define BAROMETER7_CMD_RESET_BIT_MASK           0x10
#define BAROMETER7_CMD_ACQUIRE_PRESSURE         0x20
#define BAROMETER7_CMD_ACQUIRE_TEMPERATURE      0x40
#define BAROMETER7_CMD_TRIGGER_DIAGNOSIS        0x80
#define BAROMETER7_CMD_ACQUIRE_IDENTIFIER       0xE0

/*! @} */ // barometer7_cmd

/**
 * @defgroup barometer7_set Barometer 7 Registers Settings
 * @brief Settings for registers of Barometer 7 Click driver.
 */

/**
 * @addtogroup barometer7_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b barometer7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BAROMETER7_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define BAROMETER7_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // barometer7_set

/**
 * @defgroup barometer7_map Barometer 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 7 Click driver.
 */

/**
 * @addtogroup barometer7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 7 Click to the selected MikroBUS.
 */
#define BAROMETER7_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // barometer7_map
/*! @} */ // barometer7

/**
 * @brief Barometer 7 Click context object.
 * @details Context object definition of Barometer 7 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;        /**< SPI driver object. */

    pin_name_t  chip_select;  /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t   diagnosis;      /**< Diagnosis data. */
    uint8_t   parity;         /**< Parity bit. */

} barometer7_t;

/**
 * @brief Barometer 7 Click configuration object.
 * @details Configuration object definition of Barometer 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;      /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;      /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;       /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;        /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} barometer7_cfg_t;

/**
 * @brief Barometer 7 Click response structure for identifier.
 * @details Response structure for identifier of Barometer 7 Click driver.
 */
typedef struct
{
    uint8_t  supplier;           /**< Identifier supplier data. */
    uint8_t  silicon_version;    /**< Identifier silicon version data. */
    uint8_t  metal_version;      /**< Identifier metal version data. */
    uint8_t  asic_name;          /**< Identifier asic name data. */

} barometer7_identifier_t;

/**
 * @brief Barometer 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER7_OK = 0,
    BAROMETER7_ERROR = -1,
    BAROMETER7_CMD_ERROR = -2

} barometer7_return_value_t;

/**
 * @brief Barometer 7 Click diagnosis code data.
 * @details Predefined enum values for driver diagnosis code values.
 */
typedef enum
{
    BAROMETER7_EEPROM_FEC_ERROR = 0x10,
    BAROMETER7_ACQUISITION_CHAIN_FAILURE = 0x08,
    BAROMETER7_SENSOR_CELL_FAILURE = 0x04,
    BAROMETER7_PRESSURE_OUT_OF_RANGE_HIGH = 0x02,
    BAROMETER7_PRESSURE_OUT_OF_RANGE_LOW = 0x01,
    BAROMETER7_NO_ERROR = 0x0A

} barometer7_diagnosis_code_t;

/*!
 * @addtogroup barometer7 Barometer 7 Click Driver
 * @brief API for configuring and manipulating Barometer 7 Click driver.
 * @{
 */

/**
 * @brief Barometer 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer7_cfg_setup ( barometer7_cfg_t *cfg );

/**
 * @brief Barometer 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_init ( barometer7_t *ctx, barometer7_cfg_t *cfg );

/**
 * @brief Barometer 7 default configuration function.
 * @details This function executes a default configuration of Barometer 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer7_default_cfg ( barometer7_t *ctx );

/**
 * @brief Barometer 7 data transfer function.
 * @details This function writes a desired command and read response data
 * from the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[out] data_out : Output read 10-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_generic_transfer ( barometer7_t *ctx, uint8_t cmd, uint16_t *data_out );

/**
 * @brief Barometer 7 set command function.
 * @details This function writes a desired command 
 * and read response to the previous command
 * from the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[out] data_out : Output read 10-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_set_command ( barometer7_t *ctx, uint8_t cmd, uint16_t *data_out );

/**
 * @brief Barometer 7 set reset function.
 * @details This function set reset, determines how the diagnostic reset is handled
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[out] data_out : Output read 10-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note A detected failure is only transmitted by the responding diagnosis code
 * as long as the failure is present. 
 * The diagnosis code will be reset after once transmitted. 
 * Only if the failure is detected again, 
 * the diagnosis code will be transmitted again with the next response.
 */
err_t barometer7_set_reset ( barometer7_t *ctx, uint8_t cmd, uint16_t *data_out );

/**
 * @brief Barometer 7 get pressure data function.
 * @details This function read the 10-bit pressure data 
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] press_data : Output read 10-bit pressure data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_press_data ( barometer7_t *ctx, uint16_t *press_data );

/**
 * @brief Barometer 7 get temperature data function.
 * @details This function read the 10-bit temperature data 
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] temp_data : Output read 10-bit temperature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_temp_data ( barometer7_t *ctx, uint16_t *temp_data );

/**
 * @brief Barometer 7 get trigger diagnosis data function.
 * @details This function read the trigger diagnosis data 
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] td_data : Output read trigger diagnosis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_trigger_diagnosis_data ( barometer7_t *ctx, uint16_t *td_data );

/**
 * @brief Barometer 7 get trigger test mode data function.
 * @details This function read the trigger test mode data 
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] tdm_data : Output read trigger test mode data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_trigger_test_mode ( barometer7_t *ctx, uint16_t *tdm_data );

/**
 * @brief Barometer 7 get ID data function.
 * @details This function read the identifier data 
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] id_data : Output read identifier data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_id_data ( barometer7_t *ctx, uint16_t *id_data );

/**
 * @brief Barometer 7 get identifier function.
 * @details This function read the identifier data 
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] identifier : Pointer to the response structure for identifier.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_identifier ( barometer7_t *ctx, barometer7_identifier_t *identifier );

/**
 * @brief Barometer 7 get pressure function.
 * @details This function read the pressure data 
 * and calculate pressure ( mbar )
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data ( mbar ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_pressure ( barometer7_t *ctx, float *pressure );

/**
 * @brief Barometer 7 get temperature function.
 * @details This function read the temperature data 
 * and calculate temperature ( degree Celsius )
 * of the KP264, Digital Absolute Pressure Sensor
 * on the Barometer 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer7_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer7_get_temperature ( barometer7_t *ctx, float *temperature );



#ifdef __cplusplus
}
#endif
#endif // BAROMETER7_H

/*! @} */ // barometer7

// ------------------------------------------------------------------------ END

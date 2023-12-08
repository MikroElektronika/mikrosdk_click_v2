/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file uv.h
 *
 * \brief This file contains API for UV Click driver.
 *
 * \addtogroup uv UV Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UV_H
#define UV_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_analog_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macro Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define UV_MAP_MIKROBUS( cfg, mikrobus )            \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.an    = MIKROBUS( mikrobus, MIKROBUS_AN );   \
   cfg.en    = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click callback handler definition.
 */
typedef void ( *uv_callback_t )( uint8_t* );

/**
 * @brief Click context object definition.
 */
typedef struct
{
    // Digital Output pins.
    digital_out_t en;

    // Analog Input pins.
    analog_in_t an;

    // Comm Modules.
    spi_master_t spi;
    pin_name_t chip_select;

    // Callback handler.
    uv_callback_t handler;

} uv_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins.
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins.
    pin_name_t an;
    pin_name_t en;

    // Static variables.
    uint32_t spi_speed;                 /*!< SPI master speed. */
    spi_master_mode_t spi_mode;         /*!< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity; /*!< Chip select pin polarity. */

    analog_in_resolution_t resolution;  /*!< ADC resolution. */
    float vref_value;                   /*!< Voltage reference value. */

} uv_cfg_t;

/** \} */ // End group type
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param[out] cfg Click configuration structure.
 *
 * @details This function initializes click configuration structure to init
 * state.
 * @note All used pins will be set to unconnected state.
 */
void uv_cfg_setup ( uv_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param[out] ctx Click object.
 * @param[in] cfg Click configuration structure.
 *
 * @return See #err_t definition of data type.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @details This function initializes all necessary pins and peripherals
 * used for this click.
 */
err_t uv_init ( uv_t *ctx, uv_cfg_t *cfg );

/**
 * @brief Callback Handler Setting function.
 *
 * @param[out] ctx Click object.
 * @param[in] handler Callback handler function.
 *
 * @details This function sets a callback handler for the selected ctx
 * object.
 */
void uv_set_callback_handler ( uv_t *ctx, uv_callback_t handler );

/**
 * @brief ADC Reading function.
 *
 * @param[in] ctx Click object.
 * @param[out] data_out AD conversion result [12-bit].
 *
 * @return See #err_t definition of data type.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @details This function reads AD conversion results.
 */
err_t uv_read_adc_value ( uv_t *ctx, uint16_t *data_out );

/**
 * @brief ADC Voltage Reading function.
 *
 * @param[in] ctx Click object.
 * @param[out] data_out AD voltage value [V].
 *
 * @return See #err_t definition of data type.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @details This function reads AD voltage value.
 */
err_t uv_read_adc_voltage ( uv_t *ctx, float *data_out );

/**
 * @brief AN Pin Reading function.
 *
 * @param[in] ctx Click object.
 * @param[out] data_out AD conversion result [10-bit].
 *
 * @return See #err_t definition of data type.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @details This function reads Analog pin by using AD converter from MCU.
 * @note The resolution of AD conversion depends on the target MCU and must be
 * previously set on the right value.
 */
err_t uv_read_an_pin_value ( uv_t *ctx, uint16_t *data_out );

/**
 * @brief AN Pin Voltage Reading function.
 *
 * @param[in] ctx Click object.
 * @param[out] data_out AN pin voltage value [V].
 *
 * @return See #err_t definition of data type.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @details This function reads voltage on the Analog pin by using AD
 * converter from MCU.
 * @note The resolution and reference voltage of the AD converter must be
 * previously set on the right values.
 */
err_t uv_read_an_pin_voltage ( uv_t *ctx, float *data_out );

/**
 * @brief UV Index Calculation function.
 *
 * @param[in] ctx Click object.
 * @param[in] data_in ADC voltage value for conversion from ADC voltage to UV
 * index level.
 * @param[out] data_out UV index level.
 *
 * @details This function calculates UV index level depending on the
 * converted ADC voltage value.
 * @note If callback handler is properly set, this function will send a message
 * about risk of harm.
 */
void uv_calc_index ( uv_t *ctx, float data_in, uint8_t *data_out );

/**
 * @brief Device Power ON function.
 *
 * @param[in] ctx Click object.
 *
 * @details This function allows device to be powered ON / enabled.
 */
void uv_device_enable ( uv_t *ctx );

/**
 * @brief Device Power OFF function.
 *
 * @param[in] ctx Click object.
 *
 * @details This function allows device to be powered OFF / disabled.
 */
void uv_device_disable ( uv_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // UV_H

/** \} */ // End public_function group
/// \}    // End click driver group
/*! @} */
// ------------------------------------------------------------------------- END

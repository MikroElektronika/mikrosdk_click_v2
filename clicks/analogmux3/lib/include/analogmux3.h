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
 * @file analogmux3.h
 * @brief This file contains API for Analog MUX 3 Click Driver.
 */

#ifndef ANALOGMUX3_H
#define ANALOGMUX3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup analogmux3 Analog MUX 3 Click Driver
 * @brief API for configuring and manipulating Analog MUX 3 Click driver.
 * @{
 */


/**
 * @defgroup analogmux3_set Analog MUX 3 Registers Settings
 * @brief Settings for registers of Analog MUX 3 Click driver.
 */

/**
 * @addtogroup analogmux3_set
 * @{
 */

/**
 * @brief Analog MUX 3 description setting.
 * @details Specified setting for description of Analog MUX 3 Click driver.
 */
/**
 * @brief Analog MUX 3 set channel setting.
 * @details Specified set channel setting 
 * for description of Analog MUX 3 Click driver.
 */
#define ANALOGMUX3_SET_CHANNEL_0                  0x00
#define ANALOGMUX3_SET_CHANNEL_1                  0x01
#define ANALOGMUX3_SET_CHANNEL_2                  0x02
#define ANALOGMUX3_SET_CHANNEL_3                  0x03
#define ANALOGMUX3_SET_CHANNEL_4                  0x04
#define ANALOGMUX3_SET_CHANNEL_5                  0x05
#define ANALOGMUX3_SET_CHANNEL_6                  0x06
#define ANALOGMUX3_SET_CHANNEL_7                  0x07
#define ANALOGMUX3_SET_NO_CHANNEL                 0xFF

/**
 * @brief Analog MUX 3 channel value setting.
 * @details Specified channel value setting 
 * for description of Analog MUX 3 Click driver.
 */
#define ANALOGMUX3_VAL_CHANNEL_OFF                0x00
#define ANALOGMUX3_VAL_CHANNEL_0                  0x01
#define ANALOGMUX3_VAL_CHANNEL_1                  0x02
#define ANALOGMUX3_VAL_CHANNEL_2                  0x04
#define ANALOGMUX3_VAL_CHANNEL_3                  0x08
#define ANALOGMUX3_VAL_CHANNEL_4                  0x10
#define ANALOGMUX3_VAL_CHANNEL_5                  0x20
#define ANALOGMUX3_VAL_CHANNEL_6                  0x40
#define ANALOGMUX3_VAL_CHANNEL_7                  0x80

/**
 * @brief Analog MUX 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Analog MUX 3 Click driver.
 */
#define ANALOGMUX3_SET_DEV_ADDR_0                 0x4C
#define ANALOGMUX3_SET_DEV_ADDR_1                 0x4D
#define ANALOGMUX3_SET_DEV_ADDR_2                 0x4E
#define ANALOGMUX3_SET_DEV_ADDR_3                 0x4F

/*! @} */ // analogmux3_set

/**
 * @defgroup analogmux3_map Analog MUX 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Analog MUX 3 Click driver.
 */

/**
 * @addtogroup analogmux3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Analog MUX 3 Click to the selected MikroBUS.
 */
#define ANALOGMUX3_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );     \
     cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ) 

/*! @} */ // analogmux3_map
/*! @} */ // analogmux3

/**
 * @brief Analog MUX 3 Click context object.
 * @details Context object definition of Analog MUX 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  rst;         /**< Reset pin. */

    // Modules

    analog_in_t  adc;           /**< Analog input driver object. */
    spi_master_t  spi;          /**< SPI driver object. */
                                
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} analogmux3_t;

/**
 * @brief Analog MUX 3 Click configuration object.
 * @details Configuration object definition of Analog MUX 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  an;         /**< Analog input pin. */
    
    // Additional gpio pins

    pin_name_t  rst;        /**< Reset pin. */

    // Static variable

    uint32_t                           spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;    /**< Chip select pin polarity. */
    
    analog_in_resolution_t  resolution;                /**< ADC resolution. */
    float                   vref;                      /**< ADC reference voltage. */

} analogmux3_cfg_t;

/**
 * @brief Analog MUX 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANALOGMUX3_OK = 0,
    ANALOGMUX3_ERROR = -1

} analogmux3_return_value_t;

/*!
 * @addtogroup analogmux3 Analog MUX 3 Click Driver
 * @brief API for configuring and manipulating Analog MUX 3 Click driver.
 * @{
 */

/**
 * @brief Analog MUX 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #analogmux3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void analogmux3_cfg_setup ( analogmux3_cfg_t *cfg );

/**
 * @brief Analog MUX 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #analogmux3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux3_init ( analogmux3_t *ctx, analogmux3_cfg_t *cfg );

/**
 * @brief Analog MUX 3 default configuration function.
 * @details This function executes a default configuration of Analog MUX 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t analogmux3_default_cfg ( analogmux3_t *ctx );

/**
 * @brief Analog MUX 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux3_generic_write ( analogmux3_t *ctx, uint8_t data_in );

/**
 * @brief Analog MUX 3 reset the device function.
 * @details This function executes a hardware reset of
 * Analog MUX 3 click board.
 * @param[in] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void analogmux3_hw_reset ( analogmux3_t *ctx );

/**
 * @brief Analog MUX 3 set channel function.
 * @details This function sets the active channel by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @param[in] mux_ch : 
 *         @li @c 0x00 ( ANALOGMUX3_SET_CHANNEL_0 ) - Set active channel 0,
 *         @li @c 0x01 ( ANALOGMUX3_SET_CHANNEL_1 ) - Set active channel 1,
 *         @li @c 0x02 ( ANALOGMUX3_SET_CHANNEL_2 ) - Set active channel 2,
 *         @li @c 0x03 ( ANALOGMUX3_SET_CHANNEL_3 ) - Set active channel 3,
 *         @li @c 0x04 ( ANALOGMUX3_SET_CHANNEL_4 ) - Set active channel 4,
 *         @li @c 0x05 ( ANALOGMUX3_SET_CHANNEL_5 ) - Set active channel 5,
 *         @li @c 0x06 ( ANALOGMUX3_SET_CHANNEL_6 ) - Set active channel 6,
 *         @li @c 0x07 ( ANALOGMUX3_SET_CHANNEL_7 ) - Set active channel 7,
 *         @li @c 0xFF ( ANALOGMUX3_SET_NO_CHANNEL )- Disable all channels.
 *         
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t analogmux3_set_channel ( analogmux3_t *ctx, uint8_t mux_ch );

/**
 * @brief Analog MUX 3 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux3_read_an_pin_value ( analogmux3_t *ctx, uint16_t *data_out );

/**
 * @brief Analog MUX 3 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #analogmux3_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t analogmux3_read_an_pin_voltage ( analogmux3_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // ANALOGMUX3_H

/*! @} */ // analogmux3

// ------------------------------------------------------------------------ END

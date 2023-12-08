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
 * @file hbridge10.h
 * @brief This file contains API for H-Bridge 10 Click Driver.
 */

#ifndef HBRIDGE10_H
#define HBRIDGE10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup hbridge10 H-Bridge 10 Click Driver
 * @brief API for configuring and manipulating H-Bridge 10 Click driver.
 * @{
 */

/**
 * @defgroup hbridge10_set H-Bridge 10 Settings
 * @brief Settings of H-Bridge 10 Click driver.
 */

/**
 * @addtogroup hbridge10_set
 * @{
 */

/**
 * @brief H-Bridge 10 data input register setting.
 * @details Specified data input register setting of H-Bridge 10 Click driver.
 */
#define HBRIDGE10_IN_STATUS_RESET               0x8000
#define HBRIDGE10_IN_OUT_LS1_ON                 0x1000
#define HBRIDGE10_IN_OUT_HS1_ON                 0x0800
#define HBRIDGE10_IN_OUT_LS2_ON                 0x0100
#define HBRIDGE10_IN_OUT_HS2_ON                 0x0080
#define HBRIDGE10_IN_OUT_LS3_ON                 0x0010
#define HBRIDGE10_IN_OUT_HS3_ON                 0x0008
#define HBRIDGE10_IN_OPEN_LOAD_OFF              0x0004
#define HBRIDGE10_IN_SHORT_SD_DELAY_12MS        0x0002
#define HBRIDGE10_IN_SHORT_SD_DELAY_1p5MS       0x0000
#define HBRIDGE10_IN_SOFT_ENABLE                0x0001

/**
 * @brief H-Bridge 10 data output register setting.
 * @details Specified data output register setting of H-Bridge 10 Click driver.
 */
#define HBRIDGE10_OUT_OVER_TEMP_SD              0xFFFF
#define HBRIDGE10_OUT_OVER_TEMP_WARNING         0x8000
#define HBRIDGE10_OUT_STATUS_LS1_ON             0x1000
#define HBRIDGE10_OUT_STATUS_HS1_ON             0x0800
#define HBRIDGE10_OUT_STATUS_LS2_ON             0x0100
#define HBRIDGE10_OUT_STATUS_HS2_ON             0x0080
#define HBRIDGE10_OUT_STATUS_LS3_ON             0x0010
#define HBRIDGE10_OUT_STATUS_HS3_ON             0x0008
#define HBRIDGE10_OUT_SHORT_CIRCUIT_DETECTED    0x0004
#define HBRIDGE10_OUT_NORMAL_OPERATION          0x0002
#define HBRIDGE10_OUT_VS_UNDER_VOLTAGE          0x0001

/**
 * @brief H-Bridge 10 output setting.
 * @details Specified output setting of H-Bridge 10 Click driver.
 */
#define HBRIDGE10_CHANNEL_OUT1                  1
#define HBRIDGE10_CHANNEL_OUT2                  2
#define HBRIDGE10_CHANNEL_OUT3                  3
#define HBRIDGE10_OUT_OFF                       0
#define HBRIDGE10_OUT_HIGH                      1
#define HBRIDGE10_OUT_LOW                       2
#define HBRIDGE10_OUT_MASK                      3u

/**
 * @brief H-Bridge 10 ADC reading voltage reference setting.
 * @details Specified ADC reading voltage reference setting of H-Bridge 10 Click driver.
 */
#define HBRIDGE10_ADC_VREF                      3.3

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge10_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE10_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE10_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge10_set

/**
 * @defgroup hbridge10_map H-Bridge 10 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 10 Click driver.
 */

/**
 * @addtogroup hbridge10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 10 Click to the selected MikroBUS.
 */
#define HBRIDGE10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge10_map
/*! @} */ // hbridge10

/**
 * @brief H-Bridge 10 Click context object.
 * @details Context object definition of H-Bridge 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable device pin. */

    // Input pins
    digital_in_t  flt;          /**< Fault pin. */

    // Modules
    analog_in_t   adc;          /**< ADC module object. */
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t    chip_select;  /**< Chip select pin descriptor (used for SPI driver). */
    
    uint16_t      input_data;   /**< Data input register value. */

} hbridge10_t;

/**
 * @brief H-Bridge 10 Click configuration object.
 * @details Configuration object definition of H-Bridge 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  an;                                 /**< Analog pin descriptor. */
    pin_name_t  en;                                 /**< Enable device pin. */
    pin_name_t  flt;                                /**< Fault pin. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */
    
    analog_in_resolution_t  resolution;             /**< ADC resolution. */
    float                   vref;                   /**< ADC reference voltage. */

} hbridge10_cfg_t;

/**
 * @brief H-Bridge 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE10_OK = 0,
    HBRIDGE10_ERROR = -1

} hbridge10_return_value_t;

/*!
 * @addtogroup hbridge10 H-Bridge 10 Click Driver
 * @brief API for configuring and manipulating H-Bridge 10 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge10_cfg_setup ( hbridge10_cfg_t *cfg );

/**
 * @brief H-Bridge 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge10_init ( hbridge10_t *ctx, hbridge10_cfg_t *cfg );

/**
 * @brief H-Bridge 10 default configuration function.
 * @details This function executes a default configuration of H-Bridge 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge10_default_cfg ( hbridge10_t *ctx );

/**
 * @brief H-Bridge 10 transfer data function.
 * @details This function writes 16-bit data from input and performs an immediate read of 16-bit output data 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge10_transfer_data ( hbridge10_t *ctx, uint16_t data_in, uint16_t *data_out );

/**
 * @brief H-Bridge 10 set output state function.
 * @details This function sets the output channel state.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @param[in] channel : Output channel selection [1-3].
 * @param[in] state : Channel state - @li @c 0 - OFF,
 *                                    @li @c 1 - HIGH,
 *                                    @li @c 2 - LOW.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function affects only those bits related to the selected channel in the input register.
 */
err_t hbridge10_set_output_state ( hbridge10_t *ctx, uint8_t channel, uint8_t state );

/**
 * @brief H-Bridge 10 get status function.
 * @details This function reads the status of output register.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @param[out] status : Status read from output register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't change the input register settings.
 */
err_t hbridge10_get_status ( hbridge10_t *ctx, uint16_t *status );

/**
 * @brief H-Bridge 10 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge10_read_an_pin_value ( hbridge10_t *ctx, uint16_t *data_out );

/**
 * @brief H-Bridge 10 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t hbridge10_read_an_pin_voltage ( hbridge10_t *ctx, float *data_out );

/**
 * @brief H-Bridge 10 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge10_enable_device ( hbridge10_t *ctx );

/**
 * @brief H-Bridge 10 disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge10_disable_device ( hbridge10_t *ctx );

/**
 * @brief H-Bridge 10 get fault function.
 * @details This function returns the fault (FLT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hbridge10_get_fault_pin ( hbridge10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE10_H

/*! @} */ // hbridge10

// ------------------------------------------------------------------------ END

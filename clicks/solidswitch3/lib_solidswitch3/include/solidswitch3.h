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
 * @file solidswitch3.h
 * @brief This file contains API for SolidSwitch 3 Click Driver.
 */

#ifndef SOLIDSWITCH3_H
#define SOLIDSWITCH3_H

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
 * @addtogroup solidswitch3 SolidSwitch 3 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 3 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch3_set SolidSwitch 3 Settings
 * @brief Settings of SolidSwitch 3 Click driver.
 */

/**
 * @addtogroup solidswitch3_set
 * @{
 */

/**
 * @brief SolidSwitch3 channel selection.
 * @details Specified channel selection of SolidSwitch Click driver.
 */
#define SOLIDSWITCH3_CH_OUT1                    0x01
#define SOLIDSWITCH3_CH_OUT2                    0x02
#define SOLIDSWITCH3_CH_OUT3                    0x04
#define SOLIDSWITCH3_CH_OUT4                    0x08
#define SOLIDSWITCH3_CH_OUT5                    0x10
#define SOLIDSWITCH3_CH_OUT6                    0x20
#define SOLIDSWITCH3_CH_OUT7                    0x40
#define SOLIDSWITCH3_CH_OUT8                    0x80
#define SOLIDSWITCH3_ALL_CHANNELS               0xFF

/**
 * @brief SolidSwitch 3 DIR mode settings.
 * @details Specified setting for DIR mode of SolidSwitch 3 Click driver.
 */
#define SOLIDSWITCH3_DIR_MODE_SPI               0
#define SOLIDSWITCH3_DIR_MODE_GPIO              1

/**
 * @brief SolidSwitch 3 output settings.
 * @details Specified output settings of SolidSwitch 3 Click driver.
 */
#define SOLIDSWITCH3_OUT_DISABLE                0u
#define SOLIDSWITCH3_OUT_IN_TERMINAL            1u
#define SOLIDSWITCH3_OUT_ENABLE                 2u
#define SOLIDSWITCH3_OUT_BITS_MASK              3u

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b solidswitch3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SOLIDSWITCH3_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SOLIDSWITCH3_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // solidswitch3_set

/**
 * @defgroup solidswitch3_map SolidSwitch 3 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 3 Click driver.
 */

/**
 * @addtogroup solidswitch3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 3 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in2  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch3_map
/*! @} */ // solidswitch3

/**
 * @brief SolidSwitch 3 Click context object.
 * @details Context object definition of SolidSwitch 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  dir;                 /**< DIR mode change input terminal. */
    digital_out_t  rst;                 /**< Reset terminal. */
    digital_out_t  in1;                 /**< Control input for channel 1 and 5. */
    digital_out_t  in2;                 /**< Control input for channel 2 and 6. */

    // Modules
    spi_master_t  spi;                  /**< SPI driver object. */

    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    
    uint16_t    output_state;           /**< Output data state. */

} solidswitch3_t;

/**
 * @brief SolidSwitch 3 Click configuration object.
 * @details Configuration object definition of SolidSwitch 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  dir;                                    /**< DIR mode change input terminal. */
    pin_name_t  rst;                                    /**< Reset terminal. */
    pin_name_t  in1;                                    /**< Control input for channel 1 and 5. */
    pin_name_t  in2;                                    /**< Control input for channel 2 and 6. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} solidswitch3_cfg_t;

/**
 * @brief SolidSwitch 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH3_OK = 0,
    SOLIDSWITCH3_ERROR = -1

} solidswitch3_return_value_t;

/*!
 * @addtogroup solidswitch3 SolidSwitch 3 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 3 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch3_cfg_setup ( solidswitch3_cfg_t *cfg );

/**
 * @brief SolidSwitch 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch3_init ( solidswitch3_t *ctx, solidswitch3_cfg_t *cfg );

/**
 * @brief SolidSwitch 3 default configuration function.
 * @details This function executes a default configuration of SolidSwitch 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solidswitch3_default_cfg ( solidswitch3_t *ctx );

/**
 * @brief SolidSwitch 3 write data function.
 * @details This function writes a desired data and verifies if it is written correctly by reading
 * it back by using SPI serial interface. The read data will be stored in @b ctx->output_state. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] data_in : 16bit data input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch3_write_data ( solidswitch3_t *ctx, uint16_t data_in );

/**
 * @brief SolidSwitch 3 enable output function.
 * @details This function enables the specified output channel. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] channel : Bit mask representing the channel number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch3_enable_output ( solidswitch3_t *ctx, uint8_t channel );

/**
 * @brief SolidSwitch 3 disable output function.
 * @details This function disables the specified output channel. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] channel : Bit mask representing the channel number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch3_disable_output ( solidswitch3_t *ctx, uint8_t channel );

/**
 * @brief SolidSwitch 3 reset function.
 * @details This function resets the device by toggling the reset pin. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch3_reset ( solidswitch3_t *ctx );

/**
 * @brief SolidSwitch 3 set dir mode function.
 * @details This function sets the communication protocol via the DIR pin. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] dir_mode : @li @c 0 - SPI,
 *                       @li @c 1 - GPIO.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void solidswitch3_set_dir_mode ( solidswitch3_t *ctx, uint8_t dir_mode );

/**
 * @brief SolidSwitch 3 set rst pin function.
 * @details This function sets the reset pin logic state. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None
 * @note None.
 */
void solidswitch3_set_rst_pin ( solidswitch3_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 3 set in1 pin function.
 * @details This function sets the input 1 pin logic state. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None
 * @note None.
 */
void solidswitch3_set_in1_pin ( solidswitch3_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 3 set in2 pin function.
 * @details This function sets the input 2 pin logic state. 
 * @param[in] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None
 * @note None.
 */
void solidswitch3_set_in2_pin ( solidswitch3_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH3_H

/*! @} */ // solidswitch3

// ------------------------------------------------------------------------ END

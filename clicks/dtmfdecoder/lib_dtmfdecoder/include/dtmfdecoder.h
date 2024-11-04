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
 * @file dtmfdecoder.h
 * @brief This file contains API for DTMF Decoder Click Driver.
 */

#ifndef DTMFDECODER_H
#define DTMFDECODER_H

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

/*!
 * @addtogroup dtmfdecoder DTMF Decoder Click Driver
 * @brief API for configuring and manipulating DTMF Decoder Click driver.
 * @{
 */

/**
 * @defgroup dtmfdecoder_cmd DTMF Decoder Command List
 * @brief List of command bytes of DTMF Decoder Click driver.
 */

/**
 * @addtogroup dtmfdecoder_cmd
 * @{
 */

#define DTMFDECODER_CMD_BYTE_INPUT                     0x00
#define DTMFDECODER_CMD_BYTE_OUTPUT                    0x01
#define DTMFDECODER_CMD_BYTE_POL_INV                   0x02
#define DTMFDECODER_CMD_BYTE_CONFIG                    0x03

/*! @} */ // dtmfdecoder_cmd

/**
 * @defgroup dtmfdecoder_set DTMF Decoder Registers Settings
 * @brief Settings for registers of DTMF Decoder Click driver.
 */

/**
 * @addtogroup dtmfdecoder_set
 * @{
 */

/**
 * @brief DTMF Decoder device address setting.
 * @details Specified setting for device slave address selection of
 * DTMF Decoder Click driver.
 */
#define DTMFDECODER_SET_DEV_ADDR  0x41

/*! @} */ // dtmfdecoder_set

/**
 * @defgroup dtmfdecoder_map DTMF Decoder MikroBUS Map
 * @brief MikroBUS pin mapping of DTMF Decoder Click driver.
 */

/**
 * @addtogroup dtmfdecoder_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DTMF Decoder Click to the selected MikroBUS.
 */
#define DTMFDECODER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwd = MIKROBUS( mikrobus, MIKROBUS_CS );  \
    cfg.inh = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.std = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dtmfdecoder_map
/*! @} */ // dtmfdecoder

/**
 * @brief DTMF Decoder Click context object.
 * @details Context object definition of DTMF Decoder Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  pwd;                              /**< Output pin for device power down. */
    digital_out_t  inh;                              /**< Output pin for character inhibit. */

    // Input pins

    digital_in_t   std;                              /**< Input pin for delayed steering. */

    // Modules

    i2c_master_t   i2c;                              /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} dtmfdecoder_t;

/**
 * @brief DTMF Decoder Click configuration object.
 * @details Configuration object definition of DTMF Decoder Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  pwd;                                 /**< Output pin for device power down. */
    pin_name_t  inh;                                 /**< Output pin for character inhibit. */
    pin_name_t  std;                                 /**< Input pin for delayed steering. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} dtmfdecoder_cfg_t;

/**
 * @brief DTMF Decoder Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DTMFDECODER_OK = 0,
    DTMFDECODER_ERROR = -1

} dtmfdecoder_return_value_t;

/*!
 * @addtogroup dtmfdecoder DTMF Decoder Click Driver
 * @brief API for configuring and manipulating DTMF Decoder Click driver.
 * @{
 */

/**
 * @brief DTMF Decoder configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dtmfdecoder_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void dtmfdecoder_cfg_setup ( dtmfdecoder_cfg_t *cfg );

/**
 * @brief DTMF Decoder initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dtmfdecoder_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t dtmfdecoder_init ( dtmfdecoder_t *ctx, dtmfdecoder_cfg_t *cfg );

/**
 * @brief DTMF Decoder default configuration function.
 * @details This function executes a default configuration of DTMF Decoder
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
void dtmfdecoder_default_cfg ( dtmfdecoder_t *ctx );

/**
 * @brief DTMF Decoder I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t dtmfdecoder_generic_write ( dtmfdecoder_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief DTMF Decoder I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t dtmfdecoder_generic_read ( dtmfdecoder_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief DTMF Decoder inhibit on function.
 * @details This function inhibits the detection of tones representing characters A, B, C and D. 
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * 
 * @note None.
 *
 * @endcode
 */
void dtmfdecoder_inhibit_on ( dtmfdecoder_t *ctx );

/**
 * @brief DTMF Decoder inhibit off function.
 * @details This function allows the detection of tones representing characters A, B, C and D. 
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * 
 * @note None.
 *
 * @endcode
 */
void dtmfdecoder_inhibit_off ( dtmfdecoder_t *ctx );

/**
 * @brief DTMF Decoder power down on function.
 * @details This function powers down the device and inhibits the oscillator.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * 
 * @note None.
 *
 * @endcode
 */
void dtmfdecoder_powerdown_on ( dtmfdecoder_t *ctx );

/**
 * @brief DTMF Decoder power down off function.
 * @details This function powers up the device and along with the oscillator.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * 
 * @note None.
 *
 * @endcode
 */
void dtmfdecoder_powerdown_off ( dtmfdecoder_t *ctx );

/**
 * @brief DTMF Decoder check delayed steering function.
 * @details This function checks the state of the StD pin.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * @return @li @c 1 - Tone-pair has been registered,
 *         @li @c 0 - Voltage on St/GT is below VTSt.
 * @note None.
 *
 * @endcode
 */
uint8_t dtmfdecoder_delayed_steering_check ( dtmfdecoder_t *ctx );

/**
 * @brief DTMF Decoder read tone function.
 * @details This function reads a last registered tone and returns
 * decoded data in character format.
 * @param[in] ctx : Click context object.
 * See #dtmfdecoder_t object definition for detailed explanation.
 * @return Ascii decoded tone.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t dtmfdecoder_tone_read ( dtmfdecoder_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DTMFDECODER_H

/*! @} */ // dtmfdecoder

// ------------------------------------------------------------------------ END

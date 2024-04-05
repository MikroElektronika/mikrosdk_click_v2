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
 * @file spiisolator3.h
 * @brief This file contains API for SPI Isolator 3 Click Driver.
 */

#ifndef SPIISOLATOR3_H
#define SPIISOLATOR3_H

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
    


/*!
 * @addtogroup spiisolator3 SPI Isolator 3 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 3 Click driver.
 * @{
 */


/**
 * @defgroup spiisolator3_set SPI Isolator 3 Registers Settings
 * @brief Settings for registers of SPI Isolator 3 Click driver.
 */

/**
 * @addtogroup spiisolator3_set
 * @{
 */

/**
 * @brief SPI Isolator 3 description pin state.
 * @details Specified setting for pin state of SPI Isolator 3 Click driver.
 */
#define SPIISOLATOR3_PIN_STATE_LOW                   0
#define SPIISOLATOR3_PIN_STATE_HIGH                  1

/*! @} */ // spiisolator3_set

/**
 * @defgroup spiisolator3_map SPI Isolator 3 MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Isolator 3 Click driver.
 */

/**
 * @addtogroup spiisolator3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Isolator 3 Click to the selected MikroBUS.
 */
#define SPIISOLATOR3_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.saa = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.oen = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.aux = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // spiisolator3_map
/*! @} */ // spiisolator3

/**
 * @brief SPI Isolator 3 Click context object.
 * @details Context object definition of SPI Isolator 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  saa;         /**< Side A Active pin. */
    digital_out_t  oen;         /**< SDO Enable pin.    */
    digital_out_t  aux;         /**< AUX channel pin.   */
                                
    // Input pins               
                                
    digital_in_t  flt;          /**< FAULT channel.     */

    // Modules

    spi_master_t  spi;          /**< SPI driver object. */
                                
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} spiisolator3_t;

/**
 * @brief SPI Isolator 3 Click configuration object.
 * @details Configuration object definition of SPI Isolator 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  saa;            /**< Side A Active pin. */
    pin_name_t  oen;            /**< SDO Enable pin.    */
    pin_name_t  aux;            /**< AUX channel pin.   */
    pin_name_t  flt;            /**< FAULT channel.     */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} spiisolator3_cfg_t;

/**
 * @brief SPI Isolator 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SPIISOLATOR3_OK = 0,
   SPIISOLATOR3_ERROR = -1

} spiisolator3_return_value_t;

/*!
 * @addtogroup spiisolator3 SPI Isolator 3 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 3 Click driver.
 * @{
 */

/**
 * @brief SPI Isolator 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiisolator3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiisolator3_cfg_setup ( spiisolator3_cfg_t *cfg );

/**
 * @brief SPI Isolator 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiisolator3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator3_init ( spiisolator3_t *ctx, spiisolator3_cfg_t *cfg );

/**
 * @brief SPI Isolator 3 default configuration function.
 * @details This function executes a default configuration of SPI Isolator 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t spiisolator3_default_cfg ( spiisolator3_t *ctx );

/**
 * @brief SPI Isolator 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator3_generic_write ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI Isolator 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator3_generic_read ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SPI Isolator 3 set side A active function.
 * @details This function set state of the side A by set state of the SAA ( AN ) pin
 * of the SPI Isolator 3 click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @param[in] saa_state : SAA pin state.
 * @return Nothing.
 * 
 * @note None.
 */
void spiisolator3_set_side_a_active ( spiisolator3_t *ctx, uint8_t saa_state );

/**
 * @brief SPI Isolator 3 set SDO enable function.
 * @details This function set state of the SDO enable by set state of the OEN ( RST ) pin
 * of the SPI Isolator 3 click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @param[in] sdo_state : OEN pin state.
 * @return Nothing.
 * 
 * @note None.
 */
void spiisolator3_set_sdo_enable ( spiisolator3_t *ctx, uint8_t sdo_state );

/**
 * @brief SPI Isolator 3 set AUX function.
 * @details This function set state of the AUX by set state of the AUX ( PWM ) pin
 * of the SPI Isolator 3 click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @param[in] sdo_state : OEN pin state.
 * @return Nothing.
 * 
 * @note None.
 */
void spiisolator3_set_aux ( spiisolator3_t *ctx, uint8_t aux_state );

/**
 * @brief SPI Isolator 3 get fault state function.
 * @details This function get fault state
 * of the SPI Isolator 3 click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator3_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * 
 * @note None.
 */
uint8_t spiisolator3_get_fault ( spiisolator3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SPIISOLATOR3_H

/*! @} */ // spiisolator3

// ------------------------------------------------------------------------ END

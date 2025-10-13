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
 * @file c2wirespiiso.h
 * @brief This file contains API for 2-Wire SPI ISO Click Driver.
 */

#ifndef C2WIRESPIISO_H
#define C2WIRESPIISO_H

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
 * @addtogroup c2wirespiiso 2-Wire SPI ISO Click Driver
 * @brief API for configuring and manipulating 2-Wire SPI ISO Click driver.
 * @{
 */

/**
 * @defgroup c2wirespiiso_set 2-Wire SPI ISO Settings
 * @brief Settings of 2-Wire SPI ISO Click driver.
 */

/**
 * @addtogroup c2wirespiiso_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c2wirespiiso_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C2WIRESPIISO_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define C2WIRESPIISO_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c2wirespiiso_set

/**
 * @defgroup c2wirespiiso_map 2-Wire SPI ISO MikroBUS Map
 * @brief MikroBUS pin mapping of 2-Wire SPI ISO Click driver.
 */

/**
 * @addtogroup c2wirespiiso_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 2-Wire SPI ISO Click to the selected MikroBUS.
 */
#define C2WIRESPIISO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dis = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.txen = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.bne = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c2wirespiiso_map
/*! @} */ // c2wirespiiso

/**
 * @brief 2-Wire SPI ISO Click context object.
 * @details Context object definition of 2-Wire SPI ISO Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t txen;         /**< Transmitter enable pin (Active high). */
    digital_out_t dis;          /**< Disable pin input (Active high). */

    // Input pins
    digital_in_t bne;           /**< SDO Buffer Not Empty flag pin (Active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} c2wirespiiso_t;

/**
 * @brief 2-Wire SPI ISO Click configuration object.
 * @details Configuration object definition of 2-Wire SPI ISO Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t dis;             /**< Disable pin input (Active high). */
    pin_name_t txen;            /**< Transmitter enable pin (Active high). */
    pin_name_t bne;             /**< SDO Buffer Not Empty flag pin (Active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} c2wirespiiso_cfg_t;

/**
 * @brief 2-Wire SPI ISO Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C2WIRESPIISO_OK = 0,
    C2WIRESPIISO_ERROR = -1

} c2wirespiiso_return_value_t;

/*!
 * @addtogroup c2wirespiiso 2-Wire SPI ISO Click Driver
 * @brief API for configuring and manipulating 2-Wire SPI ISO Click driver.
 * @{
 */

/**
 * @brief 2-Wire SPI ISO configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c2wirespiiso_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c2wirespiiso_cfg_setup ( c2wirespiiso_cfg_t *cfg );

/**
 * @brief 2-Wire SPI ISO initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c2wirespiiso_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2wirespiiso_init ( c2wirespiiso_t *ctx, c2wirespiiso_cfg_t *cfg );

/**
 * @brief 2-Wire SPI ISO default configuration function.
 * @details This function executes a default configuration of 2-Wire SPI ISO Click board.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void c2wirespiiso_default_cfg ( c2wirespiiso_t *ctx );

/**
 * @brief 2-Wire SPI ISO write function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2wirespiiso_write ( c2wirespiiso_t *ctx, uint8_t *data_in, uint8_t in_len );

/**
 * @brief 2-Wire SPI ISO read function.
 * @details This function reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2wirespiiso_read ( c2wirespiiso_t *ctx, uint8_t *data_out, uint8_t out_len );

/**
 * @brief 2-Wire SPI ISO write then read function.
 * @details This function writes and then reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2wirespiiso_write_then_read ( c2wirespiiso_t *ctx, uint8_t *data_in, uint8_t in_len, 
                                                          uint8_t *data_out, uint8_t out_len );

/**
 * @brief 2-Wire SPI ISO disable device function.
 * @details This function disables the device by setting the DIS pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c2wirespiiso_disable_device ( c2wirespiiso_t *ctx );

/**
 * @brief 2-Wire SPI ISO enable device function.
 * @details This function enables the device by setting the DIS pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c2wirespiiso_enable_device ( c2wirespiiso_t *ctx );

/**
 * @brief 2-Wire SPI ISO disable tx function.
 * @details This function disables the transmitter by setting the TXEN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c2wirespiiso_disable_tx ( c2wirespiiso_t *ctx );

/**
 * @brief 2-Wire SPI ISO enable tx function.
 * @details This function enables the transmitter by setting the TXEN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c2wirespiiso_enable_tx ( c2wirespiiso_t *ctx );

/**
 * @brief 2-Wire SPI ISO get bne pin function.
 * @details This function returns the RX buffer not empty (BNE) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c2wirespiiso_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c2wirespiiso_get_bne_pin ( c2wirespiiso_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C2WIRESPIISO_H

/*! @} */ // c2wirespiiso

// ------------------------------------------------------------------------ END

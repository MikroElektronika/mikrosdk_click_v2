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
 * @file dcmotor16.h
 * @brief This file contains API for DC Motor 16 Click Driver.
 */

#ifndef DCMOTOR16_H
#define DCMOTOR16_H

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
 * @addtogroup dcmotor16 DC Motor 16 Click Driver
 * @brief API for configuring and manipulating DC Motor 16 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor16_set DC Motor 16 Registers Settings
 * @brief Settings for registers of DC Motor 16 Click driver.
 */

/**
 * @addtogroup dcmotor16_set
 * @{
 */

/**
 * @brief DC Motor 16 description setting.
 * @details Specified setting for description of DC Motor 16 Click driver.
 */
#define DCMOTOR16_DIR_FORWARD                 0
#define DCMOTOR16_DIR_BACKWARD                1

#define DCMOTOR16_ENABLE                      1
#define DCMOTOR16_DISABLE                     0
/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dcmotor16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DCMOTOR16_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DCMOTOR16_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dcmotor16_set

/**
 * @defgroup dcmotor16_map DC Motor 16 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 16 Click driver.
 */

/**
 * @addtogroup dcmotor16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 16 Click to the selected MikroBUS.
 */
#define DCMOTOR16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fwd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rev = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // dcmotor16_map
/*! @} */ // dcmotor16

/**
 * @brief DC Motor 16 Click context object.
 * @details Context object definition of DC Motor 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  fwd;     /**< Description. */
    digital_out_t  rev;     /**< Description. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} dcmotor16_t;

/**
 * @brief DC Motor 16 Click configuration object.
 * @details Configuration object definition of DC Motor 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  fwd;        /**< Description. */
    pin_name_t  rev;        /**< Description. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} dcmotor16_cfg_t;

/**
 * @brief DC Motor 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DCMOTOR16_OK = 0,
   DCMOTOR16_ERROR = -1

} dcmotor16_return_value_t;

/*!
 * @addtogroup dcmotor16 DC Motor 16 Click Driver
 * @brief API for configuring and manipulating DC Motor 16 Click driver.
 * @{
 */

/**
 * @brief DC Motor 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor16_cfg_setup ( dcmotor16_cfg_t *cfg );

/**
 * @brief DC Motor 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor16_init ( dcmotor16_t *ctx, dcmotor16_cfg_t *cfg );

/**
 * @brief DC Motor 16 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor16_generic_write ( dcmotor16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DC Motor 16 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor16_generic_read ( dcmotor16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );


/**
 * @brief Set motor direction.
 * @details This function sets the direction of the motor.
 * @param[out] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] dir : Motor direction ( FORWARD / BACKWARD )
 * @return Nothing.
 */
void dcmotor16_set_direction( dcmotor16_t *ctx, uint8_t dir );

/**
 * @brief Control FWD pin.
 * @details This function controls the state of the FWD pin.
 * @param[out] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] state : Pin State ( 1 - ACTIVE / 0 - DEACTIVE )
 * @return Nothing.
 */
void dcmotor16_ctrl_fwd_pin( dcmotor16_t *ctx, uint8_t state );

/**
 * @brief Control REV pin.
 * @details This function controls the state of the REV pin.
 * @param[out] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] state : Pin State ( 1 - ACTIVE / 0 - DEACTIVE )
 * @return Nothing.
 */
void dcmotor16_ctrl_rev_pin( dcmotor16_t *ctx, uint8_t state );

/**
 * @brief Control motor VRef (speed).
 * @details This function sets the VRef value used for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @param[in] value : Motor Vref ( 0x0000 to 0x0100 )
 * @return Nothing.
 */
void dcmotor16_ctrl_vref( dcmotor16_t *ctx, uint16_t value );

/**
 * @brief Motor stop.
 * @details This function stops the motor.
 * @param[out] ctx : Click context object.
 * See #dcmotor16_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor16_stop( dcmotor16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR16_H

/*! @} */ // dcmotor16

// ------------------------------------------------------------------------ END

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
 * @file digipot8.h
 * @brief This file contains API for DIGI POT 8 Click Driver.
 */

#ifndef DIGIPOT8_H
#define DIGIPOT8_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup digipot8 DIGI POT 8 Click Driver
 * @brief API for configuring and manipulating DIGI POT 8 Click driver.
 * @{
 */

/**
 * @defgroup digipot8_reg DIGI POT 8 Registers List
 * @brief List of registers of DIGI POT 8 Click driver.
 */

/**
 * @addtogroup digipot8_reg
 * @{
 */

/**
 * @brief DIGI POT 8 description register.
 * @details Specified register for description of DIGI POT 8 Click driver.
 */
#define DIGIPOT8_REG_RDAC1 0x00
#define DIGIPOT8_REG_RDAC2 0x01
#define DIGIPOT8_REG_RDAC3 0x02
#define DIGIPOT8_REG_RDAC4 0x03
#define DIGIPOT8_REG_RDAC5 0x04
#define DIGIPOT8_REG_RDAC6 0x05

/*! @} */ // digipot8_reg

/**
 * @defgroup digipot8_set DIGI POT 8 Registers Settings
 * @brief Settings for registers of DIGI POT 8 Click driver.
 */

/**
 * @addtogroup digipot8_set
 * @{
 */

/**
 * @brief DIGI POT 8 description setting.
 * @details Specified setting for description of DIGI POT 8 Click driver.
 */
#define DIGIPOT8_WIPER_POSITION_MIN 0x00
#define DIGIPOT8_WIPER_POSITION_MAX 0xFF

/*! @} */ // digipot8_set

/**
 * @defgroup digipot8_map DIGI POT 8 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 8 Click driver.
 */

/**
 * @addtogroup digipot8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 8 Click to the selected MikroBUS.
 */
#define DIGIPOT8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \

/*! @} */ // digipot8_map
/*! @} */ // digipot8

/**
 * @brief DIGI POT 8 Click context object.
 * @details Context object definition of DIGI POT 8 Click driver.
 */
typedef struct
{
    // Modules
    analog_in_t   adc;                               /**< ADC module. */
    spi_master_t  spi;                               /**< SPI driver object. */

    float        vref;                               /**< ADC reference voltage. */
    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} digipot8_t;

/**
 * @brief DIGI POT 8 Click configuration object.
 * @details Configuration object definition of DIGI POT 8 Click driver.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t an_pin;                                   /**< AN pin descriptor. */
    
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // static variable

    analog_in_resolution_t             resolution;       /**< ADC resolution. */
    float                              vref;             /**< ADC reference voltage. */
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} digipot8_cfg_t;

/**
 * @brief DIGI POT 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT8_OK = 0,
    DIGIPOT8_ERROR = -1

} digipot8_return_value_t;

/*!
 * @addtogroup digipot8 DIGI POT 8 Click Driver
 * @brief API for configuring and manipulating DIGI POT 8 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot8_cfg_setup ( digipot8_cfg_t *cfg );

/**
 * @brief DIGI POT 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_init ( digipot8_t *ctx, digipot8_cfg_t *cfg );

/**
 * @brief DIGI POT 8 write data function.
 * @details This function writes a data byte to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_write_data ( digipot8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DIGI POT 8 set wiper 1 function.
 * @details This function sets wiper 1 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 1 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_set_wiper_1 ( digipot8_t *ctx, uint8_t data_in );

/**
 * @brief DIGI POT 8 set wiper 2 function.
 * @details This function sets wiper 2 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 2 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_set_wiper_2 ( digipot8_t *ctx, uint8_t data_in );

/**
 * @brief DIGI POT 8 set wiper 3 function.
 * @details This function sets wiper 3 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 3 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_set_wiper_3 ( digipot8_t *ctx, uint8_t data_in );

/**
 * @brief DIGI POT 8 set wiper 4 function.
 * @details This function sets wiper 4 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 4 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_set_wiper_4 ( digipot8_t *ctx, uint8_t data_in );

/**
 * @brief DIGI POT 8 set wiper 5 function.
 * @details This function sets wiper 5 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 5 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_set_wiper_5 ( digipot8_t *ctx, uint8_t data_in );

/**
 * @brief DIGI POT 8 set wiper 6 function.
 * @details This function sets wiper 6 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 6 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot8_set_wiper_6 ( digipot8_t *ctx, uint8_t data_in );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @return ADC data result.
 *
 * @description This function read ADC data.
 */
uint16_t digipot8_generic_read ( digipot8_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @return ADC data result.
 *
 * @description This function read ADC data.
 */
float digipot8_read_voltage ( digipot8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT8_H

/*! @} */ // digipot8

// ------------------------------------------------------------------------ END

/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file digipot16.h
 * @brief This file contains API for DIGI POT 16 Click Driver.
 */

#ifndef DIGIPOT16_H
#define DIGIPOT16_H

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
 * @addtogroup digipot16 DIGI POT 16 Click Driver
 * @brief API for configuring and manipulating DIGI POT 16 Click driver.
 * @{
 */

/**
 * @defgroup digipot16_cmd DIGI POT 16 Commands List
 * @brief List of Commands of DIGI POT 16 Click driver.
 */

/**
 * @addtogroup digipot16_cmd
 * @{
 */

/**
 * @brief DIGI POT 16 command list.
 * @details Specified command list of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_CMD_NOP                   0x0000
#define DIGIPOT16_CMD_WRITE_RDAC            0x0400
#define DIGIPOT16_CMD_READ_RDAC             0x0800
#define DIGIPOT16_CMD_SOFT_RESET            0x1000
#define DIGIPOT16_CMD_WRITE_CTRL            0x1800
#define DIGIPOT16_CMD_READ_CTRL             0x1C00
#define DIGIPOT16_CMD_SHUTDOWN              0x2000

/*! @} */ // digipot16_cmd

/**
 * @defgroup digipot16_set DIGI POT 16 Registers Settings
 * @brief Settings for registers of DIGI POT 16 Click driver.
 */

/**
 * @addtogroup digipot16_set
 * @{
 */

/**
 * @brief DIGI POT 16 control register setting.
 * @details Specified setting for control register of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_CTRL_NORMAL_MODE          0x0004
#define DIGIPOT16_CTRL_WRITE_ENABLE         0x0002

/**
 * @brief DIGI POT 16 shutdown mode setting.
 * @details Specified setting for shutdown mode of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_SHUTDOWN_ON               0x0001
#define DIGIPOT16_SHUTDOWN_OFF              0x0000

/**
 * @brief DIGI POT 16 wiper position setting.
 * @details Specified setting for wiper position of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_WIPER_FULL_SCALE          0x03FF
#define DIGIPOT16_WIPER_MID_SCALE           0x0200
#define DIGIPOT16_WIPER_ZERO_SCALE          0x0000
#define DIGIPOT16_WIPER_MASK                0x03FF

/**
 * @brief DIGI POT 16 timeout setting.
 * @details Specified setting for timeout of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_RDY_TIMEOUT_MS            10

/**
 * @brief DIGI POT 16 byte mask setting.
 * @details Specified setting for byte mask of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_BYTE_MASK                 0xFF

/**
 * @brief DIGI POT 16 resistance constants setting.
 * @details Specified setting for resistance constants of DIGI POT 16 Click driver.
 */
#define DIGIPOT16_RAB_OHM                   20000
#define DIGIPOT16_RW_OHM                    60
#define DIGIPOT16_RESIS_1024_CONST          1024 

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digipot16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIPOT16_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DIGIPOT16_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digipot16_set

/**
 * @defgroup digipot16_map DIGI POT 16 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 16 Click driver.
 */

/**
 * @addtogroup digipot16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 16 Click to the selected MikroBUS.
 */
#define DIGIPOT16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digipot16_map
/*! @} */ // digipot16

/**
 * @brief DIGI POT 16 Click context object.
 * @details Context object definition of DIGI POT 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin, active on LOW-to-HIGH transition, resets wiper to midscale. */

    // Input pins
    digital_in_t rdy;                           /**< Ready pin, active-high. */

    // Modules
    spi_master_t spi;                           /**< SPI driver object. */

    pin_name_t   chip_select;                   /**< Chip select pin descriptor (used for SPI driver). */

} digipot16_t;

/**
 * @brief DIGI POT 16 Click configuration object.
 * @details Configuration object definition of DIGI POT 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;             /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;             /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;              /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;               /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;              /**< Reset pin, active on LOW-to-HIGH transition, resets wiper to midscale. */
    pin_name_t rdy;              /**< Ready pin, active-high. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} digipot16_cfg_t;

/**
 * @brief DIGI POT 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT16_OK = 0,
    DIGIPOT16_ERROR = -1

} digipot16_return_value_t;

/*!
 * @addtogroup digipot16 DIGI POT 16 Click Driver
 * @brief API for configuring and manipulating DIGI POT 16 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot16_cfg_setup ( digipot16_cfg_t *cfg );

/**
 * @brief DIGI POT 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_init ( digipot16_t *ctx, digipot16_cfg_t *cfg );

/**
 * @brief DIGI POT 16 default configuration function.
 * @details This function executes a default configuration of DIGI POT 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digipot16_default_cfg ( digipot16_t *ctx );

/**
 * @brief DIGI POT 16 hardware reset function.
 * @details This function performs a hardware reset by pulsing the RST pin LOW then HIGH.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void digipot16_hw_reset ( digipot16_t *ctx );

/**
 * @brief DIGI POT 16 send command function.
 * @details This function sends a 16-bit command word via SPI.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @param[in] cmd_word : 16-bit command word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_send_command ( digipot16_t *ctx, uint16_t cmd_word );

/**
 * @brief DIGI POT 16 send command read function.
 * @details This function sends a 16-bit NOP command via SPI and reads back a 16-bit response.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to 16-bit response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_send_command_read ( digipot16_t *ctx, uint16_t *data_out );

/**
 * @brief DIGI POT 16 wait ready function.
 * @details This function polls the RDY pin until it goes HIGH or
 * until the timeout counter expires.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_wait_ready ( digipot16_t *ctx );

/**
 * @brief DIGI POT 16 software reset function.
 * @details This function sends Command 3 via SPI to reset the wiper to midscale
 * and restore default control register values.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_soft_reset ( digipot16_t *ctx );

 /**
 * @brief DIGI POT 16 set wiper function.
 * @details This function sets the wiper position by sending Command 1 via SPI.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @param[in] wiper : Wiper position value [0-1023].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_set_wiper ( digipot16_t *ctx, uint16_t wiper );

/**
 * @brief DIGI POT 16 get wiper function.
 * @details This function reads back the current wiper position from the RDAC register.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @param[out] wiper : Pointer to output wiper position value [0-1023].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_get_wiper ( digipot16_t *ctx, uint16_t *wiper );

/**
 * @brief DIGI POT 16 get resistance function.
 * @details This function calculates the resistance values between the wiper
 * and both terminals (RWB and RWA).
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @param[out] rwb_ohm : Pointer to the output resistance between wiper (W) and terminal B in Ohms [60 - 20060]
 * @param[out] rwa_ohm : Pointer to the output resistance between wiper (W) and terminal A in Ohms [60 - 20060].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot16_get_resistance ( digipot16_t *ctx, uint32_t *rwb_ohm, uint32_t *rwa_ohm );

/**
 * @brief DIGI POT 16 get RDY pin function.
 * @details This function reads the logic state of the RDY pin.
 * @param[in] ctx : Click context object.
 * See #digipot16_t object definition for detailed explanation.
 * @return RDY pin logic state.
 * @note None.
 */
uint8_t digipot16_get_rdy_pin ( digipot16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT16_H

/*! @} */ // digipot16

// ------------------------------------------------------------------------ END

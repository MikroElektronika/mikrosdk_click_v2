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
 * @file rcpulse.h
 * @brief This file contains API for RC Pulse Click Driver.
 */

#ifndef RCPULSE_H
#define RCPULSE_H

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
 * @addtogroup rcpulse RC Pulse Click Driver
 * @brief API for configuring and manipulating RC Pulse Click driver.
 * @{
 */

/**
 * @defgroup rcpulse_cmd RC Pulse Commands List
 * @brief List of commands of RC Pulse Click driver.
 */

/**
 * @addtogroup rcpulse_cmd
 * @{
 */

/**
 * @brief RC Pulse command list.
 * @details Specified command list of RC Pulse Click driver.
 */
#define RCPULSE_CMD_NOP                   0x00
#define RCPULSE_CMD_RESTORE_EEMEM         0x01
#define RCPULSE_CMD_STORE_EEMEM           0x02
#define RCPULSE_CMD_STORE_USER            0x03
#define RCPULSE_CMD_DEC_6DB               0x04
#define RCPULSE_CMD_DEC_ALL_6DB           0x05
#define RCPULSE_CMD_DEC_STEP              0x06
#define RCPULSE_CMD_DEC_ALL_STEP          0x07
#define RCPULSE_CMD_RESET                 0x08
#define RCPULSE_CMD_READ_EEMEM            0x09
#define RCPULSE_CMD_READ_RDAC             0x0A
#define RCPULSE_CMD_WRITE_RDAC            0x0B
#define RCPULSE_CMD_INC_6DB               0x0C
#define RCPULSE_CMD_INC_ALL_6DB           0x0D
#define RCPULSE_CMD_INC_STEP              0x0E
#define RCPULSE_CMD_INC_ALL_STEP          0x0F

/*! @} */ // rcpulse_cmd

/**
 * @defgroup rcpulse_set RC Pulse Registers Settings
 * @brief Settings for registers of RC Pulse Click driver.
 */

/**
 * @addtogroup rcpulse_set
 * @{
 */

/**
 * @brief RC Pulse address setting.
 * @details Specified setting for address of RC Pulse Click driver.
 */
#define RCPULSE_ADDR_RDAC1                0x00
#define RCPULSE_ADDR_RDAC2                0x01
#define RCPULSE_ADDR_TOLERANCE            0x0F

/**
 * @brief RC Pulse channel selection setting.
 * @details Specified setting for channel selection of RC Pulse Click driver.
 */
#define RCPULSE_CHANNEL_1                 0x00
#define RCPULSE_CHANNEL_2                 0x01

/**
 * @brief RC Pulse wiper setting.
 * @details Specified setting for wiper of RC Pulse Click driver.
 */
#define RCPULSE_WIPER_MIN                 0x0000
#define RCPULSE_WIPER_MIDSCALE            0x0200
#define RCPULSE_WIPER_MAX                 0x03FF
#define RCPULSE_WIPER_RESOLUTION          0x0400

/**
 * @brief RC Pulse data word, address and command setting.
 * @details Specified setting for data word, address and command of RC Pulse Click driver.
 */
#define RCPULSE_DATA_WORD_LEN             3
#define RCPULSE_CMD_MASK                  0x0F
#define RCPULSE_ADDR_MASK                 0x0F
#define RCPULSE_DATA_BYTE_MASK            0xFF

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b rcpulse_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define RCPULSE_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define RCPULSE_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // rcpulse_set

/**
 * @defgroup rcpulse_map RC Pulse MikroBUS Map
 * @brief MikroBUS pin mapping of RC Pulse Click driver.
 */

/**
 * @addtogroup rcpulse_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RC Pulse Click to the selected MikroBUS.
 */
#define RCPULSE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cl   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rcpulse_map
/*! @} */ // rcpulse

/**
 * @brief RC Pulse Click context object.
 * @details Context object definition of RC Pulse Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cl;                               /**< Clear pin(active low). */
    digital_out_t pwm;                              /**< Trigger pin. */

    // Input pins
    digital_in_t rdy;                               /**< Ready pin(active high). */

    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} rcpulse_t;

/**
 * @brief RC Pulse Click configuration object.
 * @details Configuration object definition of RC Pulse Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t cl;                                  /**< Clear pin descriptor. */
    pin_name_t pwm;                                 /**< Trigger pin descriptor. */
    pin_name_t rdy;                                 /**< Ready pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} rcpulse_cfg_t;

/**
 * @brief RC Pulse Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RCPULSE_OK = 0,
    RCPULSE_ERROR = -1

} rcpulse_return_value_t;

/*!
 * @addtogroup rcpulse RC Pulse Click Driver
 * @brief API for configuring and manipulating RC Pulse Click driver.
 * @{
 */

/**
 * @brief RC Pulse configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rcpulse_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rcpulse_cfg_setup ( rcpulse_cfg_t *cfg );

/**
 * @brief RC Pulse initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rcpulse_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rcpulse_init ( rcpulse_t *ctx, rcpulse_cfg_t *cfg );

/**
 * @brief RC Pulse default configuration function.
 * @details This function executes a default configuration of RC Pulse
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rcpulse_default_cfg ( rcpulse_t *ctx );

/**
 * @brief RC Pulse write data function.
 * @details This function writes a 24-bit data word to the AD5235 via
 * the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @param[in] cmd : 4-bit command.
 * @param[in] addr : 4-bit address ( 0x00 - 0x0F ).
 * @param[in] data_in : 16-bit data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rcpulse_write_data ( rcpulse_t *ctx, uint8_t cmd, uint8_t addr, uint16_t data_in );

/**
 * @brief RC Pulse read data function.
 * @details This function reads a 16-bit data word from the AD5235 via
 * the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @param[in] cmd : 4-bit command.
 * @param[in] addr : 4-bit address ( 0x00 - 0x0F ).
 * @param[out] data_out : Pointer to the 16-bit data word read from the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rcpulse_read_data ( rcpulse_t *ctx, uint8_t cmd, uint8_t addr, uint16_t *data_out );

/**
 * @brief RC Pulse set wiper function.
 * @details This function sets the wiper position of the selected channel
 * via the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @param[in] channel : @li @c 0x00 - Channel 1,
 *                      @li @c 0x01 - Channel 2.
 * @param[in] wiper : Wiper position ( 0x0000 - 0x03FF ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rcpulse_set_wiper ( rcpulse_t *ctx, uint8_t channel, uint16_t wiper );

/**
 * @brief RC Pulse get wiper function.
 * @details This function reads the current wiper position of the selected channel 
 * via the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @param[in] channel : @li @c 0x00 - Channel 1,
 *                      @li @c 0x01 - Channel 2.
 * @param[out] wiper : Pointer to the read wiper position ( 0x0000 - 0x03FF ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rcpulse_get_wiper ( rcpulse_t *ctx, uint8_t channel, uint16_t *wiper );

/**
 * @brief RC Pulse trigger function.
 * @details This function generates a trigger pulse on the PWM pin.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rcpulse_trigger ( rcpulse_t *ctx );

/**
 * @brief RC Pulse clear function.
 * @details This function asserts the asynchronous clear by pulsing the CL pin low.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rcpulse_clear ( rcpulse_t *ctx );

/**
 * @brief RC Pulse get ready pin function.
 * @details This function returns the logic state of the RDY pin.
 * @param[in] ctx : Click context object.
 * See #rcpulse_t object definition for detailed explanation.
 * @return RDY pin logic state.
 * @note None.
 */
uint8_t rcpulse_get_ready ( rcpulse_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RCPULSE_H

/*! @} */ // rcpulse

// ------------------------------------------------------------------------ END

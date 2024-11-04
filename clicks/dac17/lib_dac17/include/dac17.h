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
 * @file dac17.h
 * @brief This file contains API for DAC 17 Click Driver.
 */

#ifndef DAC17_H
#define DAC17_H

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
 * @addtogroup dac17 DAC 17 Click Driver
 * @brief API for configuring and manipulating DAC 17 Click driver.
 * @{
 */

/**
 * @defgroup dac17_reg DAC 17 Registers List
 * @brief List of registers of DAC 17 Click driver.
 */

/**
 * @addtogroup dac17_reg
 * @{
 */

/**
 * @brief DAC 17 description register.
 * @details Specified register for description of DAC 17 Click driver.
 */
#define DAC17_CMD_WRITE_BUFER                   0x00
#define DAC17_CMD_WRITE_BUFER_AND_LOAD          0x10
#define DAC17_CMD_WRITE_BUFER_AND_LOAD_ALL      0x20
#define DAC17_CMD_WRITE_LOAD_BUFF               0x30

/*! @} */ // dac17_reg

/**
 * @defgroup dac17_set DAC 17 Registers Settings
 * @brief Settings for registers of DAC 17 Click driver.
 */

/**
 * @addtogroup dac17_set
 * @{
 */

/**
 * @brief DAC 17 description setting.
 * @details Specified setting for description of DAC 17 Click driver.
 */
#define DAC17_SELECTED_CH_A                     0x00
#define DAC17_SELECTED_CH_B                     0x01
#define DAC17_SELECTED_CH_C                     0x02
#define DAC17_SELECTED_CH_D                     0x03
#define DAC17_SELECTED_CH_E                     0x04
#define DAC17_SELECTED_CH_F                     0x05
#define DAC17_SELECTED_CH_G                     0x06
#define DAC17_SELECTED_CH_H                     0x07

/**
 * @brief DAC 17 load channel data setting.
 * @details Specified setting for loading channel data of DAC 17 Click driver.
 */
#define DAC17_LOAD_CH_AB                        0x00
#define DAC17_LOAD_CH_ABCD                      0x01
#define DAC17_LOAD_CH_ABCDEF                    0x02
#define DAC17_LOAD_CH_ALL                       0x03

/**
 * @brief DAC 17 load and write channel data setting.
 * @details Specified setting for loading and writing channel data of DAC 17 Click driver.
 */
#define DAC17_LOAD_AND_WRITE_CH_AB              0x04
#define DAC17_LOAD_AND_WRITE_CH_ABCD            0x05
#define DAC17_LOAD_AND_WRITE_CH_ABCDEF          0x06
#define DAC17_LOAD_AND_WRITE_CH_ALL             0x07

/**
 * @brief DAC 17 pin state setting.
 * @details Specified setting for pin state of DAC 17 Click driver.
 */
#define DAC17_PIN_STATE_LOW                     0x00
#define DAC17_PIN_STATE_HIGH                    0x01

/**
 * @brief DAC 17 DAC value setting.
 * @details Specified setting for DAC value of DAC 17 Click driver.
 */
#define DAC17_12BIT_VALUE                       0x0FFFu

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac17_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC17_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DAC17_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac17_set

/**
 * @defgroup dac17_map DAC 17 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 17 Click driver.
 */

/**
 * @addtogroup dac17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 17 Click to the selected MikroBUS.
 */
#define DAC17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pd = MIKROBUS( mikrobus, MIKROBUS_PWM ) 

/*! @} */ // dac17_map
/*! @} */ // dac17

/**
 * @brief DAC 17 Click context object.
 * @details Context object definition of DAC 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t pd;           /**< Power down. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} dac17_t;

/**
 * @brief DAC 17 Click configuration object.
 * @details Configuration object definition of DAC 17 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t pd;              /**< Power down. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} dac17_cfg_t;

/**
 * @brief DAC 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC17_OK = 0,
    DAC17_ERROR = -1

} dac17_return_value_t;

/*!
 * @addtogroup dac17 DAC 17 Click Driver
 * @brief API for configuring and manipulating DAC 17 Click driver.
 * @{
 */

/**
 * @brief DAC 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac17_cfg_setup ( dac17_cfg_t *cfg );

/**
 * @brief DAC 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac17_init ( dac17_t *ctx, dac17_cfg_t *cfg );

/**
 * @brief DAC 17 default configuration function.
 * @details This function executes a default configuration of DAC 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac17_default_cfg ( dac17_t *ctx );

/**
 * @brief DAC 17 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac17_generic_write ( dac17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 17 set RST pin function.
 * @details This function is used to set state of RST pin of the DAC 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void dac17_set_rst_pin ( dac17_t *ctx, uint8_t pin_state );

/**
 * @brief DAC 17 set PD pin function.
 * @details This function is used to set state of PD pin of the DAC 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] pin_state : State of the PD pin.
 * @return Nothing.
 * @note None.
 */
void dac17_set_pd_pin ( dac17_t *ctx, uint8_t pin_state );

/**
 * @brief DAC 17 hardware reset function.
 * @details This function is used to perform hardware reset of DAC 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dac17_hw_reset ( dac17_t *ctx );

/**
 * @brief DAC 17 send command function.
 * @details This function is used to send specific command of the DAC 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] command : Command to be sent.
 * @param[in] ch_sel : Selected channel.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac17_send_command ( dac17_t *ctx, uint8_t command, uint8_t ch_sel, uint16_t data_in );

/**
 * @brief DAC 17 set output level the selected channel function.
 * @details This function is used to set output level of the sellected channel
 * of the DAC 17 Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] ch_sel : Selected channel.
 * @param[in] dac_data : Value of the DAC output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac17_set_dac_output ( dac17_t *ctx, uint8_t ch_sel, uint16_t dac_data );

/**
 * @brief DAC 17 set output level of all channels function.
 * @details This function is used to set output level of the DAC 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac17_t object definition for detailed explanation.
 * @param[in] dac_data : Value of the DAC output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac17_set_all_dac_output ( dac17_t *ctx, uint16_t dac_data );

#ifdef __cplusplus
}
#endif
#endif // DAC17_H

/*! @} */ // dac17

// ------------------------------------------------------------------------ END

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
 * @file ismrx3.h
 * @brief This file contains API for ISM RX 3 Click Driver.
 */

#ifndef ISMRX3_H
#define ISMRX3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup ismrx3 ISM RX 3 Click Driver
 * @brief API for configuring and manipulating ISM RX 3 Click driver.
 * @{
 */

/**
 * @defgroup ismrx3_reg ISM RX 3 Registers List
 * @brief List of registers of ISM RX 3 Click driver.
 */

/**
 * @addtogroup ismrx3_reg
 * @{
 */

/**
 * @brief ISM RX 3 description register.
 * @details Specified register for description of ISM RX 3 Click driver.
 */
#define ISMRX3_DEMOD            0x00
#define ISMRX3_AGC              0x01
#define ISMRX3_IF_CHF_SEL       0x02
#define ISMRX3_PDF_CFG          0x03
#define ISMRX3_ATH_CFG_1        0x04
#define ISMRX3_ATH_CFG_2        0x05
#define ISMRX3_ATH_CFG_3        0x06
#define ISMRX3_AFC_CFG_1        0x07
#define ISMRX3_AFC_CFG_2        0x08
#define ISMRX3_LO_CTR_FREQ_3    0x09
#define ISMRX3_LO_CTR_FREQ_2    0x0A
#define ISMRX3_LO_CTR_FREQ_1    0x0B
#define ISMRX3_PREAMBLE_CFG_1   0x0C
#define ISMRX3_PREAMBLE_WORD_1  0x0D
#define ISMRX3_PREAMBLE_WROD_2  0x0E
#define ISMRX3_RSS              0x10
#define ISMRX3_FEI              0x11
#define ISMRX3_PDF_OUT          0x12
#define ISMRX3_ISR              0x13
#define ISMRX3_CDR_CFG          0x35
#define ISMRX3_STATE_CTRL_1     0x14
#define ISMRX3_STATE_CTRL_2     0x15
#define ISMRX3_STATE_CTRL_3     0x16
#define ISMRX3_WUT_1            0x17
#define ISMRX3_WUT_2            0x18
#define ISMRX3_AFE_CTL_1        0x19
#define ISMRX3_IR_ADJUST        0x1A
#define ISMRX3_PART_NUM         0x1E
#define ISMRX3_REV_NUM          0x1F
#define ISMRX3_STATUS           0x27

/*! @} */ // ismrx3_reg

/**
 * @defgroup ismrx3_set ISM RX 3 Registers Settings
 * @brief Settings for registers of ISM RX 3 Click driver.
 */

/**
 * @addtogroup ismrx3_set
 * @{
 */

/**
 * @brief ISM RX 3 data modulation setting.
 * @details Specified setting for data modulation of ISM RX 3 Click driver.
 */
#define ISMRX3_MODULATION_ASK           0x01
#define ISMRX3_MODULATION_FSK           0x02

/**
 * @brief ISM RX 3 frequency setting.
 * @details Specified setting for frequency of ISM RX 3 Click driver.
 */
#define ISMRX3_FREQUENCY_MHZ_315        0x01
#define ISMRX3_FREQUENCY_MHZ_433p92     0x02
#define ISMRX3_FREQUENCY_MHZ_868p3      0x03

/**
 * @brief ISM RX 3 frequency deviation setting.
 * @details Specified setting for frequency deviation of ISM RX 3 Click driver.
 */
#define ISMRX3_DEVIATION_KHZ_5          0x01
#define ISMRX3_DEVIATION_KHZ_10         0x02
#define ISMRX3_DEVIATION_KHZ_40         0x03
#define ISMRX3_DEVIATION_KHZ_80         0x04

/**
 * @brief ISM RX 3 data rate setting.
 * @details Specified setting for data rate of ISM RX 3 Click driver.
 */
#define ISMRX3_DATA_RATE_KBPS_1         0x01
#define ISMRX3_DATA_RATE_KBPS_2         0x02
#define ISMRX3_DATA_RATE_KBPS_5         0x03
#define ISMRX3_DATA_RATE_KBPS_10        0x04
#define ISMRX3_DATA_RATE_KBPS_50        0x05
#define ISMRX3_DATA_RATE_KBPS_100       0x06

/*! @} */ // ismrx3_set

/**
 * @defgroup ismrx3_map ISM RX 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ISM RX 3 Click driver.
 */

/**
 * @addtogroup ismrx3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM RX 3 Click to the selected MikroBUS.
 */
#define ISMRX3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dat = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pdn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sw = MIKROBUS( mikrobus, MIKROBUS_PWM );\
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ismrx3_map
/*! @} */ // ismrx3

/**
 * @brief ISM RX 3 Click context object.
 * @details Context object definition of ISM RX 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  pdn;     /**< Power Down. */
    digital_out_t  sw;      /**< Multiplexer. */

    // Input pins
    digital_in_t  dat;      /**< Data pin. */
    digital_in_t  int_pin;  /**< Clock input. */

    // Modules
    spi_master_t  spi;       /**< SPI driver object. */
    pin_name_t  chip_select; /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t modulation;      /**< Data modulation. */
    uint8_t reference_freq;  /**< Frequency. */
    uint8_t freq_deviation;  /**< Frequency deviation. */
    uint8_t data_rate;       /**< Data rate. */
} ismrx3_t;

/**
 * @brief ISM RX 3 Click configuration object.
 * @details Configuration object definition of ISM RX 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  dat;    /**< Data pin. */
    pin_name_t  pdn;    /**< Power down. */
    pin_name_t  sw;     /**< Multiplexer. */
    pin_name_t  int_pin;/**< Clock input. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} ismrx3_cfg_t;

/**
 * @brief ISM RX 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISMRX3_OK = 0,
    ISMRX3_ERROR = -1,
    ISMRX3_ERROR_BUF_LEN = -2

} ismrx3_return_value_t;

/*!
 * @addtogroup ismrx3 ISM RX 3 Click Driver
 * @brief API for configuring and manipulating ISM RX 3 Click driver.
 * @{
 */

/**
 * @brief ISM RX 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ismrx3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ismrx3_cfg_setup ( ismrx3_cfg_t *cfg );

/**
 * @brief ISM RX 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ismrx3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ismrx3_init ( ismrx3_t *ctx, ismrx3_cfg_t *cfg );

/**
 * @brief ISM RX 3 default configuration function.
 * @details This function executes a default configuration of ISM RX 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ismrx3_default_cfg ( ismrx3_t *ctx );

/**
 * @brief ISM RX 3 data writing function.
 * @details This function writes a byte to the register.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ismrx3_generic_write ( ismrx3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ISM RX 3 data reading function.
 * @details This function reads a byte from register.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ismrx3_generic_read ( ismrx3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Reset function.
 * @details This function resets device by toggling @b pdn pin.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return Nothing.
 */
void ismrx3_reset( ismrx3_t *ctx );

/**
 * @brief Read clock output.
 * @details This function reads @b int_pin state.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return Clock state.
 */
uint8_t ismrx3_get_clk( ismrx3_t *ctx );

/**
 * @brief Read data output.
 * @details This function reads @b dat pin state.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return Data state.
 */
uint8_t ismrx3_get_data( ismrx3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ISMRX3_H

/*! @} */ // ismrx3

// ------------------------------------------------------------------------ END

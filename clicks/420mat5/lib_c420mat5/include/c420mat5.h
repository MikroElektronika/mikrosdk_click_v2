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
 * @file c420mat5.h
 * @brief This file contains API for 4-20mA T 5 Click Driver.
 */

#ifndef C420MAT5_H
#define C420MAT5_H

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
 * @addtogroup c420mat5 4-20mA T 5 Click Driver
 * @brief API for configuring and manipulating 4-20mA T 5 Click driver.
 * @{
 */

/**
 * @defgroup c420mat5_reg 4-20mA T 5 Registers List
 * @brief List of registers of 4-20mA T 5 Click driver.
 */

/**
 * @addtogroup c420mat5_reg
 * @{
 */

/**
 * @brief 4-20mA T 5 register list.
 * @details Specified register list of 4-20mA T 5 Click driver.
 */
#define C420MAT5_REG_DAC0                       0x00
#define C420MAT5_REG_VREF                       0x08
#define C420MAT5_REG_PWR_DOWN                   0x09
#define C420MAT5_REG_GAIN_STATUS                0x0A

/*! @} */ // c420mat5_reg

/**
 * @defgroup c420mat5_set 4-20mA T 5 Registers Settings
 * @brief Settings for registers of 4-20mA T 5 Click driver.
 */

/**
 * @addtogroup c420mat5_set
 * @{
 */

/**
 * @brief 4-20mA T 5 command bits setting.
 * @details Specified setting for command bits of 4-20mA T 5 Click driver.
 */
#define C420MAT5_CMD_WRITE                      0x00
#define C420MAT5_CMD_READ                       0x06

/**
 * @brief 4-20mA T 5 DAC output value register setting.
 * @details Specified setting for DAC output value register of 4-20mA T 5 Click driver.
 */
#define C420MAT5_DAC_ZERO_SCALE                 0x0000
#define C420MAT5_DAC_MID_SCALE                  0x0800
#define C420MAT5_DAC_FULL_SCALE                 0x0FFF
#define C420MAT5_DAC_BIT_MASK                   0x0FFF

/**
 * @brief 4-20mA T 5 voltage reference register setting.
 * @details Specified setting for voltage reference register of 4-20mA T 5 Click driver.
 */
#define C420MAT5_VREF_VDD_UNBUFFERED            0x0000
#define C420MAT5_VREF_BAND_GAP                  0x0001
#define C420MAT5_VREF_PIN_UNBUFFERED            0x0002
#define C420MAT5_VREF_PIN_BUFFERED              0x0003
#define C420MAT5_VREF_BIT_MASK                  0x0003

/**
 * @brief 4-20mA T 5 power-down register setting.
 * @details Specified setting for power-down register of 4-20mA T 5 Click driver.
 */
#define C420MAT5_PWR_DOWN_NORMAL                0x0000
#define C420MAT5_PWR_DOWN_1K_TO_GND             0x0001
#define C420MAT5_PWR_DOWN_100K_TO_GND           0x0002
#define C420MAT5_PWR_DOWN_OPEN_CIRCUIT          0x0003
#define C420MAT5_PWR_DOWN_BIT_MASK              0x0003

/**
 * @brief 4-20mA T 5 gain and status register setting.
 * @details Specified setting for gain and status register of 4-20mA T 5 Click driver.
 */
#define C420MAT5_GAIN_1X                        0x0000
#define C420MAT5_GAIN_2X                        0x0100
#define C420MAT5_GAIN_BIT_MASK                  0x0100
#define C420MAT5_STATUS_POR_BIT_MASK            0x0080
#define C420MAT5_STATUS_MTPMA_BIT_MASK          0x0040

/**
 * @brief 4-20mA T 5 error flag pin state setting.
 * @details Specified setting for error flag pin state of 4-20mA T 5 Click driver.
 */
#define C420MAT5_ERR_FLAG_ACTIVE                0
#define C420MAT5_ERR_FLAG_INACTIVE              1

/**
 * @brief 4-20mA T 5 transfer function setting.
 * @details Specified setting for transfer function of 4-20mA T 5 Click driver.
 */
#define C420MAT5_VREF_MV                        5000
#define C420MAT5_RSET_OHM                       1500
#define C420MAT5_XTR_CURRENT_GAIN               10
#define C420MAT5_DAC_RESOLUTION                 4096

/**
 * @brief 4-20mA T 5 output current setting.
 * @details Specified setting for output current of 4-20mA T 5 Click driver.
 */
#define C420MAT5_CURRENT_MIN_MA                 4.0
#define C420MAT5_CURRENT_MAX_MA                 20.0
#define C420MAT5_DAC_MIN_VALUE                  492
#define C420MAT5_DAC_MAX_VALUE                  2458

/**
 * @brief 4-20mA T 5 frame format setting.
 * @details Specified setting for frame format of 4-20mA T 5 Click driver.
 */
#define C420MAT5_FRAME_LEN                      3
#define C420MAT5_CMD_LEN                        1
#define C420MAT5_DATA_LEN                       2
#define C420MAT5_REG_ADDR_SHIFT                 3

/**
 * @brief 4-20mA T 5 rounding offset setting.
 * @details Specified setting for rounding offset of 4-20mA T 5 Click driver.
 */
#define C420MAT5_ROUND_OFFSET                   0.5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c420mat5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C420MAT5_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define C420MAT5_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c420mat5_set

/**
 * @defgroup c420mat5_map 4-20mA T 5 MikroBUS Map
 * @brief MikroBUS pin mapping of 4-20mA T 5 Click driver.
 */

/**
 * @addtogroup c420mat5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 4-20mA T 5 Click to the selected MikroBUS.
 */
#define C420MAT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.od   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.err  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c420mat5_map
/*! @} */ // c420mat5

/**
 * @brief 4-20mA T 5 Click context object.
 * @details Context object definition of 4-20mA T 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t od;                               /**< Output disable pin (active high). */

    // Input pins
    digital_in_t err;                               /**< Error pin (active low). */

    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} c420mat5_t;

/**
 * @brief 4-20mA T 5 Click configuration object.
 * @details Configuration object definition of 4-20mA T 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t od;                                  /**< Output disable pin descriptor. */
    pin_name_t err;                                 /**< Error pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} c420mat5_cfg_t;

/**
 * @brief 4-20mA T 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C420MAT5_OK = 0,
    C420MAT5_ERROR = -1

} c420mat5_return_value_t;

/*!
 * @addtogroup c420mat5 4-20mA T 5 Click Driver
 * @brief API for configuring and manipulating 4-20mA T 5 Click driver.
 * @{
 */

/**
 * @brief 4-20mA T 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c420mat5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c420mat5_cfg_setup ( c420mat5_cfg_t *cfg );

/**
 * @brief 4-20mA T 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c420mat5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat5_init ( c420mat5_t *ctx, c420mat5_cfg_t *cfg );

/**
 * @brief 4-20mA T 5 default configuration function.
 * @details This function executes a default configuration of 4-20mA T 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c420mat5_default_cfg ( c420mat5_t *ctx );

/**
 * @brief 4-20mA T 5 write register function.
 * @details This function writes a 16-bit data word to the selected register.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat5_write_reg ( c420mat5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief 4-20mA T 5 read register function.
 * @details This function reads a 16-bit data word from the selected register.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat5_read_reg ( c420mat5_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief 4-20mA T 5 set DAC value function.
 * @details This function writes a raw 12-bit value to the volatile DAC output
 * value register.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @param[in] dac_value : Raw DAC value to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat5_set_dac_value ( c420mat5_t *ctx, uint16_t dac_value );

/**
 * @brief 4-20mA T 5 set output current function.
 * @details This function sets the analog output current of the current loop.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @param[in] current_ma : Output loop current in milliamperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c420mat5_set_output_current ( c420mat5_t *ctx, float current_ma );

/**
 * @brief 4-20mA T 5 enable output function.
 * @details This function enables the loop output by setting the OD pin to
 * the low logic level.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c420mat5_enable_output ( c420mat5_t *ctx );

/**
 * @brief 4-20mA T 5 disable output function.
 * @details This function disables the loop output by setting the OD pin to
 * the high logic level.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c420mat5_disable_output ( c420mat5_t *ctx );

/**
 * @brief 4-20mA T 5 get ERR pin function.
 * @details This function returns the logic state of the ERR pin.
 * @param[out] ctx : Click context object.
 * See #c420mat5_t object definition for detailed explanation.
 * @return ERR pin logic state.
 * @note None.
 */
uint8_t c420mat5_get_err_pin ( c420mat5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C420MAT5_H

/*! @} */ // c420mat5

// ------------------------------------------------------------------------ END

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
 * @file brushless30.h
 * @brief This file contains API for Brushless 30 Click Driver.
 */

#ifndef BRUSHLESS30_H
#define BRUSHLESS30_H

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
 * @addtogroup brushless30 Brushless 30 Click Driver
 * @brief API for configuring and manipulating Brushless 30 Click driver.
 * @{
 */

/**
 * @defgroup brushless30_reg Brushless 30 Registers List
 * @brief List of registers of Brushless 30 Click driver.
 */

/**
 * @addtogroup brushless30_reg
 * @{
 */

/**
 * @brief Brushless 30 register list.
 * @details Specified register list of Brushless 30 Click driver.
 */
#define BRUSHLESS30_REG_OPSEL1                  0x00
#define BRUSHLESS30_REG_OPSEL2                  0x04
#define BRUSHLESS30_REG_STAT1                   0x08
#define BRUSHLESS30_REG_STAT2                   0x0C
#define BRUSHLESS30_REG_CP_RLY_CTRL             0x14
#define BRUSHLESS30_REG_PL_CTRL                 0x18
#define BRUSHLESS30_REG_T_ILIM                  0x1C
#define BRUSHLESS30_REG_FET_OPSEL               0x24
#define BRUSHLESS30_REG_HS_VDS_SEL              0x28
#define BRUSHLESS30_REG_LS_VDS_SEL              0x2C
#define BRUSHLESS30_REG_FET_DET_SEL             0x30
#define BRUSHLESS30_REG_AMP_CTRL                0x40
#define BRUSHLESS30_REG_AMP_STAT                0x44
#define BRUSHLESS30_REG_ALM_CTRL                0x48
#define BRUSHLESS30_REG_QA_CTRL                 0x4C
#define BRUSHLESS30_REG_ANSWER                  0x50
#define BRUSHLESS30_REG_BIST_DIAG               0x54
#define BRUSHLESS30_REG_BIST_STAT               0x58
#define BRUSHLESS30_REG_FET_TEST_CNT1           0x5C
#define BRUSHLESS30_REG_FET_TEST_CNT2           0x60
#define BRUSHLESS30_REG_FET_TEST_STAT           0x64
#define BRUSHLESS30_REG_VDS_COMP_STAT           0x68
#define BRUSHLESS30_REG_DUMMY                   0x7C

/*! @} */ // brushless30_reg

/**
 * @defgroup brushless30_set Brushless 30 Registers Settings
 * @brief Settings for registers of Brushless 30 Click driver.
 */

/**
 * @addtogroup brushless30_set
 * @{
 */

/**
 * @brief Brushless 30 default config setting.
 * @details Specified setting for default config of Brushless 30 Click driver.
 */
#define BRUSHLESS30_HS_VDS_SEL                  0x2444
#define BRUSHLESS30_LS_VDS_SEL                  0x2444
#define BRUSHLESS30_AMP_CTRL                    0x0333
#define BRUSHLESS30_CP_RLY_CTRL                 0x1111

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b brushless30_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BRUSHLESS30_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define BRUSHLESS30_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // brushless30_set

/**
 * @defgroup brushless30_map Brushless 30 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 30 Click driver.
 */

/**
 * @addtogroup brushless30_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 30 Click to the selected MikroBUS.
 */
#define BRUSHLESS30_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.alarm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.diag = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless30_map
/*! @} */ // brushless30

/**
 * @brief Brushless 30 Click context object.
 * @details Context object definition of Brushless 30 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t alarm;        /**< Pre-driver enable pin (active high). */

    // Input pins
    digital_in_t diag;          /**< Diagnostics pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} brushless30_t;

/**
 * @brief Brushless 30 Click configuration object.
 * @details Configuration object definition of Brushless 30 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t alarm;           /**< Pre-driver enable pin (active high). */
    pin_name_t diag;            /**< Diagnostics pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} brushless30_cfg_t;

/**
 * @brief Brushless 30 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS30_OK = 0,
    BRUSHLESS30_ERROR = -1

} brushless30_return_value_t;

/*!
 * @addtogroup brushless30 Brushless 30 Click Driver
 * @brief API for configuring and manipulating Brushless 30 Click driver.
 * @{
 */

/**
 * @brief Brushless 30 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless30_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless30_cfg_setup ( brushless30_cfg_t *cfg );

/**
 * @brief Brushless 30 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless30_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless30_init ( brushless30_t *ctx, brushless30_cfg_t *cfg );

/**
 * @brief Brushless 30 default configuration function.
 * @details This function executes a default configuration of Brushless 30
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless30_default_cfg ( brushless30_t *ctx );

/**
 * @brief Brushless 30 write reg function.
 * @details This function writes a data word to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless30_write_reg ( brushless30_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Brushless 30 read reg function.
 * @details This function reads a data word from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless30_read_reg ( brushless30_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Brushless 30 enable driver function.
 * @details This function enables driver by setting the ALARM pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless30_enable_driver ( brushless30_t *ctx );

/**
 * @brief Brushless 30 disable driver function.
 * @details This function disables driver by setting the ALARM pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless30_disable_driver ( brushless30_t *ctx );

/**
 * @brief Brushless 30 get diag pin function.
 * @details This function returns the DIAG pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless30_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless30_get_diag_pin ( brushless30_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS30_H

/*! @} */ // brushless30

// ------------------------------------------------------------------------ END

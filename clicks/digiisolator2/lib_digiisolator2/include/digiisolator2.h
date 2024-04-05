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
 * @file digiisolator2.h
 * @brief This file contains API for DIGI Isolator 2 Click Driver.
 */

#ifndef DIGIISOLATOR2_H
#define DIGIISOLATOR2_H

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
 * @addtogroup digiisolator2 DIGI Isolator 2 Click Driver
 * @brief API for configuring and manipulating DIGI Isolator 2 Click driver.
 * @{
 */

/**
 * @defgroup digiisolator2_reg DIGI Isolator 2 Registers List
 * @brief List of registers of DIGI Isolator 2 Click driver.
 */

/**
 * @addtogroup digiisolator2_reg
 * @{
 */

/**
 * @brief DIGI Isolator 2 register list.
 * @details Specified register list of DIGI Isolator 2 Click driver.
 */
#define DIGIISOLATOR2_REG_INPUT_DATA            0x00
#define DIGIISOLATOR2_REG_WIRE_BREAK            0x01
#define DIGIISOLATOR2_REG_FAULT                 0x02
#define DIGIISOLATOR2_REG_FILTER_CH1_CH2        0x03
#define DIGIISOLATOR2_REG_FILTER_CH3_CH4        0x04
#define DIGIISOLATOR2_REG_FILTER_CH5_CH6        0x05
#define DIGIISOLATOR2_REG_FILTER_CH7_CH8        0x06

/*! @} */ // digiisolator2_reg

/**
 * @defgroup digiisolator2_set DIGI Isolator 2 Registers Settings
 * @brief Settings for registers of DIGI Isolator 2 Click driver.
 */

/**
 * @addtogroup digiisolator2_set
 * @{
 */

/**
 * @brief DIGI Isolator 2 input channel setting.
 * @details Specified setting for input channel of DIGI Isolator 2 Click driver.
 */
#define DIGIISOLATOR2_CHANNEL_IN1               0x01
#define DIGIISOLATOR2_CHANNEL_IN2               0x02
#define DIGIISOLATOR2_CHANNEL_IN3               0x04
#define DIGIISOLATOR2_CHANNEL_IN4               0x08
#define DIGIISOLATOR2_CHANNEL_IN5               0x10
#define DIGIISOLATOR2_CHANNEL_IN6               0x20
#define DIGIISOLATOR2_CHANNEL_IN7               0x40
#define DIGIISOLATOR2_CHANNEL_IN8               0x80
#define DIGIISOLATOR2_CHANNEL_ALL               0xFF

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digiisolator2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIISOLATOR2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DIGIISOLATOR2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digiisolator2_set

/**
 * @defgroup digiisolator2_map DIGI Isolator 2 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI Isolator 2 Click driver.
 */

/**
 * @addtogroup digiisolator2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI Isolator 2 Click to the selected MikroBUS.
 */
#define DIGIISOLATOR2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sync = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digiisolator2_map
/*! @} */ // digiisolator2

/**
 * @brief DIGI Isolator 2 Click driver selector.
 * @details Selects target driver interface of DIGI Isolator 2 Click driver.
 */
typedef enum
{
    DIGIISOLATOR2_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    DIGIISOLATOR2_DRV_SEL_GPIO      /**< GPIO driver descriptor. */

} digiisolator2_drv_t;

/**
 * @brief DIGI Isolator 2 Click context object.
 * @details Context object definition of DIGI Isolator 2 Click driver.
 */
typedef struct
{
    // Output pins in SPI mode
    digital_out_t en;               /**< Output enable pin (Active high). */
    digital_out_t rst;              /**< Reset pin. */

    // Input pins in SPI mode
    digital_in_t sync;              /**< Sync pin in burst mode. */
    digital_in_t int_pin;           /**< Interrupt pin. */
    
    // Input pins in GPIO mode
    digital_in_t out1;              /**< OUT1 pin. */
    digital_in_t out2;              /**< OUT2 pin. */
    digital_in_t out3;              /**< OUT3 pin. */
    digital_in_t out4;              /**< OUT4 pin. */
    digital_in_t out5;              /**< OUT5 pin. */
    digital_in_t out6;              /**< OUT6 pin. */
    digital_in_t out8;              /**< OUT8 pin. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

    digiisolator2_drv_t drv_sel;    /**< Driver interface selector. */

} digiisolator2_t;

/**
 * @brief DIGI Isolator 2 Click configuration object.
 * @details Configuration object definition of DIGI Isolator 2 Click driver.
 */
typedef struct
{
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    pin_name_t en;                  /**< Output enable pin (Active high). */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t sync;                /**< Sync pin in burst mode. */
    pin_name_t int_pin;             /**< Interrupt pin. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    digiisolator2_drv_t drv_sel;    /**< Driver interface selector. */

} digiisolator2_cfg_t;

/**
 * @brief DIGI Isolator 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIISOLATOR2_OK = 0,
    DIGIISOLATOR2_ERROR = -1

} digiisolator2_return_value_t;

/*!
 * @addtogroup digiisolator2 DIGI Isolator 2 Click Driver
 * @brief API for configuring and manipulating DIGI Isolator 2 Click driver.
 * @{
 */

/**
 * @brief DIGI Isolator 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digiisolator2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digiisolator2_cfg_setup ( digiisolator2_cfg_t *cfg );

/**
 * @brief DIGI Isolator 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #digiisolator2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #digiisolator2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void digiisolator2_drv_interface_sel ( digiisolator2_cfg_t *cfg, digiisolator2_drv_t drv_sel );

/**
 * @brief DIGI Isolator 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digiisolator2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator2_init ( digiisolator2_t *ctx, digiisolator2_cfg_t *cfg );

/**
 * @brief DIGI Isolator 2 SPI writing function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function is used only in SPI mode.
 */
err_t digiisolator2_spi_write ( digiisolator2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DIGI Isolator 2 SPI reading function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function is used only in SPI mode.
 */
err_t digiisolator2_spi_read ( digiisolator2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DIGI Isolator 2 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note This function is used only in SPI mode.
 */
void digiisolator2_set_rst_pin ( digiisolator2_t *ctx, uint8_t state );

/**
 * @brief DIGI Isolator 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in SPI mode.
 */
uint8_t digiisolator2_get_int_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get sync pin function.
 * @details This function returns the SYNC pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in SPI mode.
 */
uint8_t digiisolator2_get_sync_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 read inputs function.
 * @details This function reads all inputs state via the selected driver interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @param[out] data_out : Inputs state read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator2_read_inputs ( digiisolator2_t *ctx, uint8_t *data_out );

/**
 * @brief DIGI Isolator 2 get out1 pin function.
 * @details This function returns the OUT1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out1_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get out2 pin function.
 * @details This function returns the OUT2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out2_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get out3 pin function.
 * @details This function returns the OUT3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out3_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get out4 pin function.
 * @details This function returns the OUT4 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out4_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get out5 pin function.
 * @details This function returns the OUT5 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out5_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get out6 pin function.
 * @details This function returns the OUT6 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out6_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 get out8 pin function.
 * @details This function returns the OUT8 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function is used only in GPIO mode.
 */
uint8_t digiisolator2_get_out8_pin ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 enable output function.
 * @details This function enables output by setting the EN pin to high state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void digiisolator2_enable_output ( digiisolator2_t *ctx );

/**
 * @brief DIGI Isolator 2 disable output function.
 * @details This function disables output by setting the EN pin to low state.
 * @param[in] ctx : Click context object.
 * See #digiisolator2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void digiisolator2_disable_output ( digiisolator2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIISOLATOR2_H

/*! @} */ // digiisolator2

// ------------------------------------------------------------------------ END

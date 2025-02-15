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
 * @file mux5.h
 * @brief This file contains API for MUX 5 Click Driver.
 */

#ifndef MUX5_H
#define MUX5_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup mux5 MUX 5 Click Driver
 * @brief API for configuring and manipulating MUX 5 Click driver.
 * @{
 */

/**
 * @defgroup mux5_reg MUX 5 Registers List
 * @brief List of registers of MUX 5 Click driver.
 */

/**
 * @addtogroup mux5_reg
 * @{
 */

/**
 * @brief MUX 5 I2C registers list.
 * @details Specified I2C registers list of MUX 5 Click driver.
 */
#define MUX5_REG_DIR0                   0x00
#define MUX5_REG_DIR1                   0x01
#define MUX5_REG_DIR2                   0x02
#define MUX5_REG_DIR3                   0x03
#define MUX5_REG_SHDW0                  0x10
#define MUX5_REG_SHDW1                  0x11
#define MUX5_REG_SHDW2                  0x12
#define MUX5_REG_SHDW3                  0x13
#define MUX5_REG_CMD_A                  0x14
#define MUX5_REG_CMD_B                  0x15

/*! @} */ // mux5_reg

/**
 * @defgroup mux5_set MUX 5 Registers Settings
 * @brief Settings for registers of MUX 5 Click driver.
 */

/**
 * @addtogroup mux5_set
 * @{
 */

/**
 * @brief MUX 5 driver interface selection setting.
 * @details Specified setting for driver interface selection of MUX 5 Click driver.
 */
#define MUX5_I2C_DRIVER                 0
#define MUX5_SPI_DRIVER                 1
#define MUX5_DRIVER_SEL                 MUX5_I2C_DRIVER

/**
 * @brief MUX 5 channel selection macros.
 * @details Specified channel selection macros of MUX 5 Click driver.
 */
#define MUX5_CHANNEL_1                  0x0001
#define MUX5_CHANNEL_2                  0x0002
#define MUX5_CHANNEL_3                  0x0004
#define MUX5_CHANNEL_4                  0x0008
#define MUX5_CHANNEL_5                  0x0010
#define MUX5_CHANNEL_6                  0x0020
#define MUX5_CHANNEL_7                  0x0040
#define MUX5_CHANNEL_8                  0x0080
#define MUX5_CHANNEL_9                  0x0100
#define MUX5_CHANNEL_10                 0x0200
#define MUX5_CHANNEL_11                 0x0400
#define MUX5_CHANNEL_12                 0x0800
#define MUX5_CHANNEL_13                 0x1000
#define MUX5_CHANNEL_14                 0x2000
#define MUX5_CHANNEL_15                 0x4000
#define MUX5_CHANNEL_16                 0x8000
#define MUX5_CHANNEL_ALL                0xFFFF

/**
 * @brief MUX 5 channel state macros.
 * @details Specified channel state macros of MUX 5 Click driver.
 */
#define MUX5_CHANNEL_STATE_HIGH_Z       0
#define MUX5_CHANNEL_STATE_COM_A        1
#define MUX5_CHANNEL_STATE_COM_B        2
#define MUX5_CHANNEL_STATE_COM_AB       3

/**
 * @brief MUX 5 device address setting.
 * @details Specified setting for device slave address selection of
 * MUX 5 Click driver.
 */
#define MUX5_DEVICE_ADDRESS_0           0x4C
#define MUX5_DEVICE_ADDRESS_1           0x4D

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mux5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MUX5_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define MUX5_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mux5_set

/**
 * @defgroup mux5_map MUX 5 MikroBUS Map
 * @brief MikroBUS pin mapping of MUX 5 Click driver.
 */

/**
 * @addtogroup mux5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MUX 5 Click to the selected MikroBUS.
 */
#define MUX5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.com_b = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sd    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.com_a = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // mux5_map
/*! @} */ // mux5

/**
 * @brief MUX 5 Click context object.
 * @details Context object definition of MUX 5 Click driver.
 */
typedef struct mux5_s
{
    digital_out_t sd;               /**< Shutdown pin (Active low). */

    digital_in_t com_b;             /**< Common B channels input pin. */
    digital_in_t com_a;             /**< Common A channels input pin. */

#if ( MUX5_DRIVER_SEL == MUX5_SPI_DRIVER )
    spi_master_t spi;               /**< SPI driver object. */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
#else
    i2c_master_t i2c;               /**< I2C driver object. */
    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
#endif
    uint16_t     ch_a;              /**< Channel A setting. */
    uint16_t     ch_b;              /**< Channel B setting. */

} mux5_t;

/**
 * @brief MUX 5 Click configuration object.
 * @details Configuration object definition of MUX 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t com_b;               /**< Common B channels input pin. */
    pin_name_t sd;                  /**< Shutdown pin (Active low). */
    pin_name_t com_a;               /**< Common A channels input pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} mux5_cfg_t;

/**
 * @brief MUX 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MUX5_OK = 0,
    MUX5_ERROR = -1

} mux5_return_value_t;

/*!
 * @addtogroup mux5 MUX 5 Click Driver
 * @brief API for configuring and manipulating MUX 5 Click driver.
 * @{
 */

/**
 * @brief MUX 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mux5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mux5_cfg_setup ( mux5_cfg_t *cfg );

/**
 * @brief MUX 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mux5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux5_init ( mux5_t *ctx, mux5_cfg_t *cfg );

/**
 * @brief MUX 5 default configuration function.
 * @details This function executes a default configuration of MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mux5_default_cfg ( mux5_t *ctx );

#if ( MUX5_DRIVER_SEL == MUX5_I2C_DRIVER )
/**
 * @brief MUX 5 I2C write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux5_i2c_write_register ( mux5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief MUX 5 I2C read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux5_i2c_read_register ( mux5_t *ctx, uint8_t reg, uint8_t *data_out );
#endif

/**
 * @brief MUX 5 set channels state function.
 * @details This function sets a desired @b ch_state of the channels selected with @b ch_mask.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @param[in] ch_mask : Bit mask of channels to set.
 * @param[in] ch_state : Channel state. @li @c 0 - High Z,
 *                                      @li @c 1 - COM A,
 *                                      @li @c 2 - COM B,
 *                                      @li @c 3 - COM AB (Be careful when setting this state and combining it 
 *                                                 with states 1 and 2, since the COM_A and COM_B are going to be shorted. 
 *                                                 Refer to the functional diagram from the datasheet for more details.).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux5_set_channels_state ( mux5_t *ctx, uint16_t ch_mask, uint8_t ch_state );

/**
 * @brief MUX 5 enable device function.
 * @details This function enables the device by setting the shutdown (SD) pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mux5_enable_device ( mux5_t *ctx );

/**
 * @brief MUX 5 disable device function.
 * @details This function disables the device by setting the shutdown (SD) pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mux5_disable_device ( mux5_t *ctx );

/**
 * @brief MUX 5 get com a pin function.
 * @details This function returns the COM A pin logic state.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mux5_get_com_a_pin ( mux5_t *ctx );

/**
 * @brief MUX 5 get com b pin function.
 * @details This function returns the COM B pin logic state.
 * @param[in] ctx : Click context object.
 * See #mux5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mux5_get_com_b_pin ( mux5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MUX5_H

/*! @} */ // mux5

// ------------------------------------------------------------------------ END

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
 * @file dac12.h
 * @brief This file contains API for DAC 12 Click Driver.
 */

#ifndef DAC12_H
#define DAC12_H

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
 * @addtogroup dac12 DAC 12 Click Driver
 * @brief API for configuring and manipulating DAC 12 Click driver.
 * @{
 */

/**
 * @defgroup dac12_reg DAC 12 Registers List
 * @brief List of registers of DAC 12 Click driver.
 */

/**
 * @addtogroup dac12_reg
 * @{
 */

/**
 * @brief DAC 12 Register Map.
 * @details Specified register map of DAC 12 Click driver.
 */
#define DAC12_REG_NOP                   0x00
#define DAC12_REG_DEVICE_ID             0x01
#define DAC12_REG_SYNC                  0x02
#define DAC12_REG_CONFIG                0x03
#define DAC12_REG_GAIN                  0x04
#define DAC12_REG_TRIGGER               0x05
#define DAC12_REG_BROADCAST             0x06
#define DAC12_REG_STATUS                0x07
#define DAC12_REG_DAC0                  0x08
#define DAC12_REG_DAC1                  0x09
#define DAC12_REG_DAC2                  0x0A
#define DAC12_REG_DAC3                  0x0B
#define DAC12_REG_DAC4                  0x0C
#define DAC12_REG_DAC5                  0x0D
#define DAC12_REG_DAC6                  0x0E
#define DAC12_REG_DAC7                  0x0F

/*! @} */ // dac12_reg

/**
 * @defgroup dac12_set DAC 12 Control register Settings
 * @brief Settings for control registers of DAC 12 Click driver.
 */

/**
 * @addtogroup dac12_set
 * @{
 */

/**
 * @brief DAC 12 select channel flags.
 * @details Specified channel selection flags of DAC 12 Click driver.
 */
#define DAC12_SELECT_CHANNEL_NONE       0x00
#define DAC12_SELECT_CHANNEL_0          0x01
#define DAC12_SELECT_CHANNEL_1          0x02
#define DAC12_SELECT_CHANNEL_2          0x04
#define DAC12_SELECT_CHANNEL_3          0x08
#define DAC12_SELECT_CHANNEL_4          0x10
#define DAC12_SELECT_CHANNEL_5          0x20
#define DAC12_SELECT_CHANNEL_6          0x40
#define DAC12_SELECT_CHANNEL_7          0x80
#define DAC12_SELECT_CHANNEL_ALL        0xFF

/**
 * @brief DAC 12 gain register settings.
 * @details Specified gain register settings of DAC 12 Click driver.
 */
#define DAC12_GAIN_REFDIV_EN            0x0100

/**
 * @brief DAC 12 range values.
 * @details DAC range values of DAC 12 Click driver.
 */
#define DAC12_MIN_DAC_VALUE             0x0000
#define DAC12_MAX_DAC_VALUE             0x0FFF

/**
 * @brief DAC 12 vref values.
 * @details DAC vref values of DAC 12 Click driver.
 */
#define DAC12_INTERNAL_VREF             2.5

/**
 * @brief DAC 12 soft reset value.
 * @details Specified soft reset value of DAC 12 Click driver.
 */
#define DAC12_SOFT_RESET                0x000A

/**
 * @brief DAC 12 device ID value.
 * @details Specified device ID value of DAC 12 Click driver.
 */
#define DAC12_DEVICE_ID                 0x2894
#define DAC12_DEVICE_ID_MASK            0xFFFC

/**
 * @brief DAC 12 SPI read bit.
 * @details Specified SPI read bit of DAC 12 Click driver.
 */
#define DAC12_SPI_READ                  0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac12_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC12_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DAC12_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac12_set

/**
 * @defgroup dac12_map DAC 12 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 12 Click driver.
 */

/**
 * @addtogroup dac12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 12 Click to the selected MikroBUS.
 */
#define DAC12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // dac12_map
/*! @} */ // dac12

/**
 * @brief DAC 12 Click context object.
 * @details Context object definition of DAC 12 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;                                  /**< SPI driver object. */

    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */
    
    pin_name_t  channel_gain;                           /**< Channel gain value. */

} dac12_t;

/**
 * @brief DAC 12 Click configuration object.
 * @details Configuration object definition of DAC 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} dac12_cfg_t;

/**
 * @brief DAC 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC12_OK = 0,
    DAC12_ERROR = -1

} dac12_return_value_t;

/*!
 * @addtogroup dac12 DAC 12 Click Driver
 * @brief API for configuring and manipulating DAC 12 Click driver.
 * @{
 */

/**
 * @brief DAC 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac12_cfg_setup ( dac12_cfg_t *cfg );

/**
 * @brief DAC 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_init ( dac12_t *ctx, dac12_cfg_t *cfg );

/**
 * @brief DAC 12 default configuration function.
 * @details This function executes a default configuration of DAC 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac12_default_cfg ( dac12_t *ctx );

/**
 * @brief DAC 12 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written [2 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_write_register ( dac12_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 12 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data [2 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_read_register ( dac12_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 12 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_check_communication ( dac12_t *ctx );

/**
 * @brief DAC 12 soft reset function.
 * @details This function executes the software reset command.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_soft_reset ( dac12_t *ctx );

/**
 * @brief DAC 12 set gain function.
 * @details This function sets the gain of 2 to the selected channels, the other channels will have
 * their gain disabled.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @param[in] channel : Output channel mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_set_gain ( dac12_t *ctx, uint8_t channel );

/**
 * @brief DAC 12 set channel value function.
 * @details This function sets the raw DAC value to the specific channels output.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @param[in] channel : Output channel mask.
 * @param[in] dac_value : 12-bit raw DAC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_set_channel_value ( dac12_t *ctx, uint8_t channel, uint16_t dac_value );

/**
 * @brief DAC 12 set channel voltage function.
 * @details This function sets the output voltage of the specific channels.
 * @param[in] ctx : Click context object.
 * See #dac12_t object definition for detailed explanation.
 * @param[in] channel : Output channel mask.
 * @param[in] voltage : Float value of voltage to be set (up to 2.5 V).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac12_set_channel_voltage ( dac12_t *ctx, uint8_t channel, float voltage );

#ifdef __cplusplus
}
#endif
#endif // DAC12_H

/*! @} */ // dac12

// ------------------------------------------------------------------------ END

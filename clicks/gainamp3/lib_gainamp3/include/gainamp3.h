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
 * @file gainamp3.h
 * @brief This file contains API for GainAMP 3 Click Driver.
 */

#ifndef GAINAMP3_H
#define GAINAMP3_H

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
 * @addtogroup gainamp3 GainAMP 3 Click Driver
 * @brief API for configuring and manipulating GainAMP 3 Click driver.
 * @{
 */

/**
 * @defgroup gainamp3_reg GainAMP 3 Registers List
 * @brief List of registers of GainAMP 3 Click driver.
 */

/**
 * @addtogroup gainamp3_reg
 * @{
 */

/**
 * @brief GainAMP 3 register summary.
 * @details Specified register summary of GainAMP 3 Click driver.
 */
#define GAINAMP3_REG_GAIN_MUX               0x00
#define GAINAMP3_REG_RESET                  0x01
#define GAINAMP3_REG_SYNC_CFG               0x02
#define GAINAMP3_REG_DIGITAL_ERR            0x03
#define GAINAMP3_REG_ANALOG_ERR             0x04
#define GAINAMP3_REG_GPIO_DATA              0x05
#define GAINAMP3_REG_INPUT_MUX              0x06
#define GAINAMP3_REG_WB_DETECT              0x07
#define GAINAMP3_REG_GPIO_DIR               0x08
#define GAINAMP3_REG_SCS                    0x09
#define GAINAMP3_REG_ANALOG_ERR_DIS         0x0A
#define GAINAMP3_REG_DIGITAL_ERR_DIS        0x0B
#define GAINAMP3_REG_SF_CFG                 0x0C
#define GAINAMP3_REG_ERR_CFG                0x0D
#define GAINAMP3_REG_TEST_MUX               0x0E
#define GAINAMP3_REG_EX_CURRENT_CFG         0x0F
#define GAINAMP3_REG_GAIN_CAL1              0x10
#define GAINAMP3_REG_GAIN_CAL2              0x11
#define GAINAMP3_REG_GAIN_CAL3              0x12
#define GAINAMP3_REG_GAIN_CAL4              0x13
#define GAINAMP3_REG_GAIN_CAL5              0x14
#define GAINAMP3_REG_GAIN_CAL6              0x15
#define GAINAMP3_REG_GAIN_CAL7              0x16
#define GAINAMP3_REG_GAIN_CAL8              0x17
#define GAINAMP3_REG_GAIN_CAL9              0x18
#define GAINAMP3_REG_GAIN_CAL10             0x19
#define GAINAMP3_REG_GAIN_CAL11             0x1A
#define GAINAMP3_REG_GAIN_CAL12             0x1B
#define GAINAMP3_REG_GAIN_CAL13             0x1C
#define GAINAMP3_REG_GAIN_CAL14             0x1D
#define GAINAMP3_REG_GAIN_CAL15             0x1E
#define GAINAMP3_REG_GAIN_CAL16             0x1F
#define GAINAMP3_REG_GAIN_CAL17             0x20
#define GAINAMP3_REG_GAIN_CAL18             0x21
#define GAINAMP3_REG_GAIN_CAL19             0x22
#define GAINAMP3_REG_GAIN_CAL20             0x23
#define GAINAMP3_REG_GAIN_CAL21             0x24
#define GAINAMP3_REG_GAIN_CAL22             0x25
#define GAINAMP3_REG_GAIN_CAL23             0x26
#define GAINAMP3_REG_GAIN_CAL24             0x27
#define GAINAMP3_REG_TRIG_CAL               0x2A
#define GAINAMP3_REG_M_CLK_CNT              0x2E
#define GAINAMP3_REG_DIE_REV_ID             0x2F
#define GAINAMP3_REG_PART_ID                0x64

/*! @} */ // gainamp3_reg

/**
 * @defgroup gainamp3_set GainAMP 3 Registers Settings
 * @brief Settings for registers of GainAMP 3 Click driver.
 */

/**
 * @addtogroup gainamp3_set
 * @{
 */

/**
 * @brief GainAMP 3 SPI CRC enable values.
 * @details Specified values for SPI CRC enable of GainAMP 3 Click driver.
 */
#define GAINAMP3_SPI_CRC_ERR_DISABLE_BIT    0x20
#define GAINAMP3_SPI_CRC_ENABLE             0x01
#define GAINAMP3_SPI_CRC_DISABLE            0x00

/**
 * @brief GainAMP 3 DIE revision identification value.
 * @details Specified value for DIE revision identification of GainAMP 3 Click driver.
 */
#define GAINAMP3_DIE_REV_ID                 0x30

/**
 * @brief GainAMP 3 input amplifier gain levels values.
 * @details Specified values for input amplifier gain levels of GainAMP 3 Click driver.
 */
#define GAINAMP3_GAIN_1_OVER_16             0x00
#define GAINAMP3_GAIN_1_OVER_8              0x01
#define GAINAMP3_GAIN_1_OVER_4              0x02
#define GAINAMP3_GAIN_1_OVER_2              0x03
#define GAINAMP3_GAIN_1                     0x04
#define GAINAMP3_GAIN_2                     0x05
#define GAINAMP3_GAIN_4                     0x06
#define GAINAMP3_GAIN_8                     0x07
#define GAINAMP3_GAIN_16                    0x08
#define GAINAMP3_GAIN_32                    0x09
#define GAINAMP3_GAIN_64                    0x0A
#define GAINAMP3_GAIN_128                   0x0B
#define GAINAMP3_GAIN_BITS_MASK             0x78

/**
 * @brief GainAMP 3 input channel values.
 * @details Specified values for input channels of GainAMP 3 Click driver.
 */
#define GAINAMP3_CHANNEL_1                  0x00
#define GAINAMP3_CHANNEL_2                  0x01
#define GAINAMP3_CHANNEL_TEST               0x02
#define GAINAMP3_CHANNEL_SHORT_SWITCH       0x03
#define GAINAMP3_CHANNEL_BITS_MASK          0x60

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gainamp3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GAINAMP3_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define GAINAMP3_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gainamp3_set

/**
 * @defgroup gainamp3_map GainAMP 3 MikroBUS Map
 * @brief MikroBUS pin mapping of GainAMP 3 Click driver.
 */

/**
 * @addtogroup gainamp3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GainAMP 3 Click to the selected MikroBUS.
 */
#define GAINAMP3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // gainamp3_map
/*! @} */ // gainamp3

/**
 * @brief GainAMP 3 Click context object.
 * @details Context object definition of GainAMP 3 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;                                  /**< SPI driver object. */

    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t spi_crc_enable;                             /**< SPI CRC enable flag */

} gainamp3_t;

/**
 * @brief GainAMP 3 Click configuration object.
 * @details Configuration object definition of GainAMP 3 Click driver.
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

} gainamp3_cfg_t;

/**
 * @brief GainAMP 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GAINAMP3_OK = 0,
    GAINAMP3_ERROR = -1

} gainamp3_return_value_t;

/*!
 * @addtogroup gainamp3 GainAMP 3 Click Driver
 * @brief API for configuring and manipulating GainAMP 3 Click driver.
 * @{
 */

/**
 * @brief GainAMP 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gainamp3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gainamp3_cfg_setup ( gainamp3_cfg_t *cfg );

/**
 * @brief GainAMP 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gainamp3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_init ( gainamp3_t *ctx, gainamp3_cfg_t *cfg );

/**
 * @brief GainAMP 3 default configuration function.
 * @details This function executes a default configuration of GainAMP 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gainamp3_default_cfg ( gainamp3_t *ctx );

/**
 * @brief GainAMP 3 continuous write function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_continuous_write ( gainamp3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief GainAMP 3 continuous read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_continuous_read ( gainamp3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief GainAMP 3 write register function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_write_register ( gainamp3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief GainAMP 3 read register function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_read_register ( gainamp3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief GainAMP 3 verify communication function.
 * @details This function verifies the communication by reading and verifying the DIE revision ID number.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_verify_communication ( gainamp3_t *ctx );

/**
 * @brief GainAMP 3 set amplifier gain function.
 * @details This function sets the amplifier gain level.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] gain : Amplifier gain level [0x00-0x0B].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_set_amplifier_gain ( gainamp3_t *ctx, uint8_t gain );

/**
 * @brief GainAMP 3 set input channel function.
 * @details This function sets the input channel.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @param[in] channel : Input channel [0x00-0x03].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_set_input_channel ( gainamp3_t *ctx, uint8_t channel );

/**
 * @brief GainAMP 3 software reset function.
 * @details This function performs the software reset.
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp3_software_reset ( gainamp3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GAINAMP3_H

/*! @} */ // gainamp3

// ------------------------------------------------------------------------ END

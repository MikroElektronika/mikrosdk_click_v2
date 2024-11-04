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
 * @file adc20.h
 * @brief This file contains API for ADC 20 Click Driver.
 */

#ifndef ADC20_H
#define ADC20_H

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
 * @addtogroup adc20 ADC 20 Click Driver
 * @brief API for configuring and manipulating ADC 20 Click driver.
 * @{
 */

/**
 * @defgroup adc20_reg ADC 20 Registers List
 * @brief List of registers of ADC 20 Click driver.
 */

/**
 * @addtogroup adc20_reg
 * @{
 */

/**
 * @brief ADC 20 opcodes for commands list.
 * @details Specified opcodes for commands list of ADC 20 Click driver.
 */
#define ADC20_CMD_NOP                       0x00
#define ADC20_CMD_REG_READ                  0x10
#define ADC20_CMD_REG_WRITE                 0x08
#define ADC20_CMD_SET_BIT                   0x18
#define ADC20_CMD_CLEAR_BIT                 0x20

/**
 * @brief ADC 20 registers list.
 * @details Specified registers list of ADC 20 Click driver.
 */
#define ADC20_REG_SYSTEM_STATUS             0x00
#define ADC20_REG_GENERAL_CFG               0x01
#define ADC20_REG_DATA_CFG                  0x02
#define ADC20_REG_OSR_CFG                   0x03
#define ADC20_REG_OPMODE_CFG                0x04
#define ADC20_REG_PIN_CFG                   0x05
#define ADC20_REG_GPIO_CFG                  0x07
#define ADC20_REG_GPO_DRIVE_CFG             0x09
#define ADC20_REG_GPO_VALUE                 0x0B
#define ADC20_REG_GPI_VALUE                 0x0D
#define ADC20_REG_SEQUENCE_CFG              0x10
#define ADC20_REG_CHANNEL_SEL               0x11
#define ADC20_REG_AUTO_SEQ_CH_SEL           0x12

/*! @} */ // adc20_reg

/**
 * @defgroup adc20_set ADC 20 Registers Settings
 * @brief Settings for registers of ADC 20 Click driver.
 */

/**
 * @addtogroup adc20_set
 * @{
 */

/**
 * @brief ADC 20 DATA_CFG register setting.
 * @details Specified setting for DATA_CFG register of ADC 20 Click driver.
 */
#define ADC20_DATA_CFG_FIX_PAT              0x80
#define ADC20_DATA_CFG_APPEND_CHANNEL_ID    0x10
#define ADC20_DATA_CFG_SPI_MODE_0           0x00
#define ADC20_DATA_CFG_SPI_MODE_1           0x01
#define ADC20_DATA_CFG_SPI_MODE_2           0x02
#define ADC20_DATA_CFG_SPI_MODE_3           0x03
#define ADC20_DATA_CFG_SPI_MODE_MASK        0x03

/**
 * @brief ADC 20 Fixed code value.
 * @details Specified Fixed code value of ADC 20 Click driver.
 */
#define ADC20_FIXED_CODE                    0xA5A0

/**
 * @brief ADC 20 channel mask.
 * @details Specified channel mask of ADC 20 Click driver.
 */
#define ADC20_CHANNEL_0                     0x01
#define ADC20_CHANNEL_1                     0x02
#define ADC20_CHANNEL_2                     0x04
#define ADC20_CHANNEL_3                     0x08
#define ADC20_CHANNEL_4                     0x10
#define ADC20_CHANNEL_5                     0x20
#define ADC20_CHANNEL_6                     0x40
#define ADC20_CHANNEL_7                     0x80
#define ADC20_CHANNEL_NONE                  0x00
#define ADC20_CHANNEL_MASK                  0xFF

/**
 * @brief ADC 20 channel ID values.
 * @details Specified channel ID values of ADC 20 Click driver.
 */
#define ADC20_CHANNEL_ID_0                  0
#define ADC20_CHANNEL_ID_1                  1
#define ADC20_CHANNEL_ID_2                  2
#define ADC20_CHANNEL_ID_3                  3
#define ADC20_CHANNEL_ID_4                  4
#define ADC20_CHANNEL_ID_5                  5
#define ADC20_CHANNEL_ID_6                  6
#define ADC20_CHANNEL_ID_7                  7
#define ADC20_CHANNEL_ID_MASK               0x0F

/**
 * @brief ADC 20 PIN_CFG register settings.
 * @details Specified settings for PIN_CFG register of ADC 20 Click driver.
 */
#define ADC20_PIN_CFG_ANALOG                0
#define ADC20_PIN_CFG_GPIO                  1

/**
 * @brief ADC 20 GPIO_CFG register settings.
 * @details Specified settings for GPIO_CFG register of ADC 20 Click driver.
 */
#define ADC20_GPIO_CFG_DIG_INPUT            0
#define ADC20_GPIO_CFG_DIG_OUTPUT           1

/**
 * @brief ADC 20 GPO_DRIVE_CFG register settings.
 * @details Specified settings for GPO_DRIVE_CFG register of ADC 20 Click driver.
 */
#define ADC20_GPO_DRIVE_CFG_OPEN_DRAIN      0
#define ADC20_GPO_DRIVE_CFG_PUSH_PULL       1

/**
 * @brief ADC 20 GPIO value settings.
 * @details Specified settings for GPIO value of ADC 20 Click driver.
 */
#define ADC20_GPIO_VALUE_LOW                0
#define ADC20_GPIO_VALUE_HIGH               1

/**
 * @brief ADC 20 OSR_CFG register setting.
 * @details Specified setting for OSR_CFG register of ADC 20 Click driver.
 */
#define ADC20_OSR_NO_AVERAGING              0x00
#define ADC20_OSR_2_SAMPLES                 0x01
#define ADC20_OSR_4_SAMPLES                 0x02
#define ADC20_OSR_8_SAMPLES                 0x03
#define ADC20_OSR_16_SAMPLES                0x04
#define ADC20_OSR_32_SAMPLES                0x05
#define ADC20_OSR_64_SAMPLES                0x06
#define ADC20_OSR_128_SAMPLES               0x07
#define ADC20_OSR_MASK                      0x07

/**
 * @brief ADC 20 SEQUENCE_CFG register setting.
 * @details Specified setting for SEQUENCE_CFG register of ADC 20 Click driver.
 */
#define ADC20_SEQ_STOP                      0x00
#define ADC20_SEQ_START                     0x10
#define ADC20_SEQ_MODE_MANUAL               0x00
#define ADC20_SEQ_MODE_AUTO                 0x01
#define ADC20_SEQ_MODE_OTF                  0x02
#define ADC20_SEQ_MODE_MASK                 0x03

/**
 * @brief ADC 20 ADC setting.
 * @details Specified setting for ADC of ADC 20 Click driver.
 */
#define ADC20_ADC_OFFSET                    4
#define ADC20_RES_12BIT                     0x0FFF
#define ADC20_VREF_3V3                      3.3f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc20_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC20_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define ADC20_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc20_set

/**
 * @defgroup adc20_map ADC 20 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 20 Click driver.
 */

/**
 * @addtogroup adc20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 20 Click to the selected MikroBUS.
 */
#define ADC20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // adc20_map
/*! @} */ // adc20

/**
 * @brief ADC 20 Click context object.
 * @details Context object definition of ADC 20 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;                   /**< SPI driver object. */

    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */

} adc20_t;

/**
 * @brief ADC 20 Click configuration object.
 * @details Configuration object definition of ADC 20 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc20_cfg_t;

/**
 * @brief ADC 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC20_OK = 0,
    ADC20_ERROR = -1

} adc20_return_value_t;

/*!
 * @addtogroup adc20 ADC 20 Click Driver
 * @brief API for configuring and manipulating ADC 20 Click driver.
 * @{
 */

/**
 * @brief ADC 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc20_cfg_setup ( adc20_cfg_t *cfg );

/**
 * @brief ADC 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_init ( adc20_t *ctx, adc20_cfg_t *cfg );

/**
 * @brief ADC 20 default configuration function.
 * @details This function executes a default configuration of ADC 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc20_default_cfg ( adc20_t *ctx );

/**
 * @brief ADC 20 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_write_register ( adc20_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ADC 20 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_read_register ( adc20_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ADC 20 read data function.
 * @details This function reads two bytes of data by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_read_data ( adc20_t *ctx, uint16_t *data_out );

/**
 * @brief ADC 20 check communication function.
 * @details This function checks the communication by reading and verifying the fixed code bytes.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The FIX PAT bit must be set in the DATA_CFG register.
 */
err_t adc20_check_communication ( adc20_t *ctx );

/**
 * @brief ADC 20 start auto sequence function.
 * @details This function starts the auto sequencing by setting the SEQUENCE_CFG register.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_start_auto_sequence ( adc20_t *ctx );

/**
 * @brief ADC 20 stop auto sequence function.
 * @details This function stops the auto sequencing by setting the manual sequence mode.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_stop_auto_sequence ( adc20_t *ctx );

/**
 * @brief ADC 20 set pin config function.
 * @details This function sets the pin config value for the selected channels.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] ch_mask : Channel selection mask.
 * @param[in] pin_cfg : Pin config value @li @c 0 - Analog,
 *                                       @li @c 1 - GPIO.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_set_pin_config ( adc20_t *ctx, uint8_t ch_mask, uint8_t pin_cfg );

/**
 * @brief ADC 20 set gpio config function.
 * @details This function sets the gpio config value for the selected channels.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] ch_mask : Channel selection mask.
 * @param[in] gpio_cfg : GPIO config value @li @c 0 - Input,
 *                                         @li @c 1 - Output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_set_gpio_config ( adc20_t *ctx, uint8_t ch_mask, uint8_t gpio_cfg );

/**
 * @brief ADC 20 set gpo drive config function.
 * @details This function sets the gpo drive config value for the selected channels.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] ch_mask : Channel selection mask.
 * @param[in] gpo_drive_cfg : GPO drive config value @li @c 0 - Open-Drain,
 *                                                   @li @c 1 - Push-Pull.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_set_gpo_drive_config ( adc20_t *ctx, uint8_t ch_mask, uint8_t gpo_drive_cfg );

/**
 * @brief ADC 20 set gpo value function.
 * @details This function sets the gpo value for the selected channels.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[in] ch_mask : Channel selection mask.
 * @param[in] value : GPO value @li @c 0 - Low,
 *                              @li @c 1 - High.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_set_gpo_value ( adc20_t *ctx, uint8_t ch_mask, uint8_t value );

/**
 * @brief ADC 20 read gpio value function.
 * @details This function reads the gpio pins value.
 * @param[in] ctx : Click context object.
 * See #adc20_t object definition for detailed explanation.
 * @param[out] gpio_value : GPIO pins value, whole port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc20_read_gpio_value ( adc20_t *ctx, uint8_t *gpio_value );

#ifdef __cplusplus
}
#endif
#endif // ADC20_H

/*! @} */ // adc20

// ------------------------------------------------------------------------ END

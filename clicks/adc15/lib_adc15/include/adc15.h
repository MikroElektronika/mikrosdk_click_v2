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
 * @file adc15.h
 * @brief This file contains API for ADC 15 Click Driver.
 */

#ifndef ADC15_H
#define ADC15_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup adc15 ADC 15 Click Driver
 * @brief API for configuring and manipulating ADC 15 Click driver.
 * @{
 */

/**
 * @defgroup adc15_reg ADC 15 Registers List
 * @brief List of registers of ADC 15 Click driver.
 */

/**
 * @addtogroup adc15_reg
 * @{
 */

/**
 * @brief ADC 15 control commands.
 * @details Specified commands for control of ADC 15 Click driver.
 */
#define ADC15_CMD_NULL              0x0000
#define ADC15_CMD_RESET             0x0011
#define ADC15_CMD_STANDBY           0x0022
#define ADC15_CMD_WAKEUP            0x0033
#define ADC15_CMD_LOCK              0x0555
#define ADC15_CMD_UNLOCK            0x0655
#define ADC15_CMD_RREG              0xA000
#define ADC15_CMD_WREG              0x6000

/**
 * @brief ADC 15 description register.
 * @details Specified register for description of ADC 15 Click driver.
 */
#define ADC15_REG_ID                0x00
#define ADC15_REG_STATUS            0x01
#define ADC15_REG_MODE              0x02
#define ADC15_REG_CLOCK             0x03
#define ADC15_REG_GAIN              0x04
#define ADC15_REG_CFG               0x06
#define ADC15_REG_THRSHLD_MSB       0x07
#define ADC15_REG_THRSHLD_LSB       0x08
#define ADC15_REG_CH0_CFG           0x09
#define ADC15_REG_CH0_OCAL_MSB      0x0A
#define ADC15_REG_CH0_OCAL_LSB      0x0B
#define ADC15_REG_CH0_GCAL_MSB      0x0C
#define ADC15_REG_CH0_GCAL_LSB      0x0D
#define ADC15_REG_CH1_CFG           0x0E
#define ADC15_REG_CH1_OCAL_MSB      0x0F
#define ADC15_REG_CH1_OCAL_LSB      0x10
#define ADC15_REG_CH1_GCAL_MSB      0x11
#define ADC15_REG_CH1_GCAL_LSB      0x12
#define ADC15_REG_REGMAP_CRC        0x3E

/*! @} */ // adc15_reg

/**
 * @defgroup adc15_set ADC 15 Registers Settings
 * @brief Settings for registers of ADC 15 Click driver.
 */

/**
 * @addtogroup adc15_set
 * @{
 */

/**
 * @brief ADC 15 frequency mode settings.
 * @details Specified setting for frequency-mode of ADC 15 Click driver.
 * @note Values are in Hz units.
 */
#define ADC15_FREQ_MODE_HIGH_RESOLUTION 8192000
#define ADC15_FREQ_MODE_LOW_POWER       4096000
#define ADC15_FREQ_MODE_VERY_LOW_POWER  2048000

/**
 * @brief ADC 15 LDC power settings.
 * @details Specified setting for LDC power of ADC 15 Click driver.
 */
#define ADC15_LDC_CFG_POWER_ON      2
#define ADC15_LDC_CFG_POWER_DOWN    3

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc15_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC15_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADC15_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc15_set

/**
 * @defgroup adc15_map ADC 15 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 15 Click driver.
 */

/**
 * @addtogroup adc15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 15 Click to the selected MikroBUS.
 */
#define ADC15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.drdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc15_map
/*! @} */ // adc15

/**
 * @brief ADC 15 Click context object.
 * @details Context object definition of ADC 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset. */
    digital_out_t  cs2;         /**< Chip select for LTC6903. */

    // Input pins
    digital_in_t  drdy;         /**< Data ready. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t gain1;              /**< Gain for channel 1*/
    uint8_t gain2;              /**< Gain for channel 2*/
    uint8_t word_len;           /**< Word len */
    uint32_t resolution;        /**< Resolution */

} adc15_t;

/**
 * @brief ADC 15 Click configuration object.
 * @details Configuration object definition of ADC 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;    /**< Reset. */
    pin_name_t  cs2;    /**< Chip select. */
    pin_name_t  drdy;   /**< Data ready. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} adc15_cfg_t;

/**
 * @brief ADC 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ADC15_OK = 0,
   ADC15_ERROR = -1

} adc15_return_value_t;

/**
 * @brief ADC 15 Click channel selection.
 * @details Predefined enum values for driver channel selection.
 */
typedef enum
{
   ADC15_CHANNEL1 = 0,
   ADC15_CHANNEL2 = 4

} adc15_channel_t;

/**
 * @brief ADC 15 Click ADC gain configuration.
 * @details Predefined enum values for driver ADC gain configuration.
 */
typedef enum
{
   ADC15_GAIN1 = 0, /**< +/-1.2V */
   ADC15_GAIN2,     /**< +/-600mV */ 
   ADC15_GAIN4,     /**< +/-300mV */
   ADC15_GAIN8,     /**< +/-150mV */
   ADC15_GAIN16,    /**< +/-75mV */
   ADC15_GAIN32,    /**< +/-37.5mV */
   ADC15_GAIN64,    /**< +/-18.75mV */
   ADC15_GAIN128    /**< +/-9.375mV */

} adc15_gain_t;

/**
 * @brief ADC 15 Click communication word data length.
 * @details Predefined enum values for driver communication word data length.
 */
typedef enum
{
   ADC15_16bit = 0,
   ADC15_24bit,
   ADC15_32bit

} adc15_word_t;

/*!
 * @addtogroup adc15 ADC 15 Click Driver
 * @brief API for configuring and manipulating ADC 15 Click driver.
 * @{
 */

/**
 * @brief ADC 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc15_cfg_setup ( adc15_cfg_t *cfg );

/**
 * @brief ADC 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t adc15_init ( adc15_t *ctx, adc15_cfg_t *cfg );

/**
 * @brief ADC 15 default configuration function.
 * @details This function executes a default configuration of ADC 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc15_default_cfg ( adc15_t *ctx );

/**
 * @brief Data writing function.
 * @details This function writes a desired number of data
 * bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_adc_write ( adc15_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Register writing function.
 * @details This function writes a data to the selected 
 * register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_reg_write ( adc15_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Multiple register writing function.
 * @details This function writes a desired number of data words 
 * starting from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] data_size : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_multiple_reg_write ( adc15_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t data_size );

/**
 * @brief Data reading function.
 * @details This function reads a desired number of data 
 * bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_adc_read ( adc15_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Register reading function.
 * @details This function reads a data from the selected
 * register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_reg_read ( adc15_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Multiple registern reading function.
 * @details This function reads a desired number of data words 
 * starting from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] data_size : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_multiple_reg_read ( adc15_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t data_size );

/**
 * @brief Data transfer function.
 * @details This function transfers a desired number of data 
 * bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len : Transfer size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_adc_transfer ( adc15_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );

/**
 * @brief LTC writing function.
 * @details This function writes a data to the 
 * LTC by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] oct : Octet.
 * @param[in] dac : DAC.
 * @param[in] cfg : Configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_ltc_write ( adc15_t *ctx, uint8_t oct, uint16_t dac, uint8_t cfg );

/**
 * @brief Set sampling frequency.
 * @details This function sets output frequency of LTC 
 * that controls sample rate of ADS131M02.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] frequency : Frequency to set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_set_frequency ( adc15_t *ctx, uint32_t frequency );

/**
 * @brief Get raw adc value.
 * @details This function reads status and raw adc data
 * from both channels.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[out] status : Output status.
 * @param[out] ch1_out : Channel 1 raw adc output.
 * @param[out] ch2_out : Channel 2 raw adc output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_read_adc_value ( adc15_t *ctx, uint16_t *status, int32_t *ch1_out, int32_t *ch2_out );

/**
 * @brief Get voltage value.
 * @details This function reads status and voltage level
 * from both channels.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[out] status : Output status.
 * @param[out] ch1_out : Channel 1 voltage value.
 * @param[out] ch2_out : Channel 2 voltage value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Voltage values are in V unit.
 */
err_t adc15_read_voltage ( adc15_t *ctx, uint16_t *status, float *ch1_out, float *ch2_out );

/**
 * @brief Get data ready state.
 * @details This function reads @b drdy pin status.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @return State of data ready.
 * @note Active low.
 */
uint8_t adc15_data_ready ( adc15_t *ctx );

/**
 * @brief Set gain for channel.
 * @details This function sets gain for channel selected channel.
 * @param[in,out] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] channel : Channel to change gain.
 * See #adc15_channel_t enum definition for detailed explanation.
 * @param[in] gain : Gain to set.
 * See #adc15_gain_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_set_gain ( adc15_t *ctx, adc15_channel_t channel, adc15_gain_t gain );

/**
 * @brief Set word len.
 * @details This function sets communication word length.
 * @param[in,out] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] word_len : Word len to set.
 * See #adc15_word_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t adc15_set_word_len ( adc15_t *ctx, adc15_word_t word_len );

#ifdef __cplusplus
}
#endif
#endif // ADC15_H

/*! @} */ // adc15

// ------------------------------------------------------------------------ END

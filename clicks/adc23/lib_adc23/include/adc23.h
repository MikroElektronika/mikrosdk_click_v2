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
 * @file adc23.h
 * @brief This file contains API for ADC 23 Click Driver.
 */

#ifndef ADC23_H
#define ADC23_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup adc23 ADC 23 Click Driver
 * @brief API for configuring and manipulating ADC 23 Click driver.
 * @{
 */

/**
 * @defgroup adc23_reg ADC 23 Registers List
 * @brief List of registers of ADC 23 Click driver.
 */

/**
 * @addtogroup adc23_reg
 * @{
 */

/**
 * @brief ADC 23 description register.
 * @details Specified register for description of ADC 23 Click driver.
 */
#define ADC_REG_DEV_ID                       0x00
#define ADC_REG_REV_ID                       0x01
#define ADC_REG_STATUS                       0x02
#define ADC_REG_CONTROL                      0x03
#define ADC_REG_MUX                          0x04
#define ADC_REG_CONFIG1                      0x05
#define ADC_REG_CONFIG2                      0x06
#define ADC_REG_CONFIG3                      0x07
#define ADC_REG_CONFIG4                      0x08
#define ADC_REG_OFFSET2                      0x09
#define ADC_REG_OFFSET1                      0x0A
#define ADC_REG_OFFSET0                      0x0B
#define ADC_REG_GAIN2                        0x0C
#define ADC_REG_GAIN1                        0x0D
#define ADC_REG_GAIN0                        0x0E
#define ADC_REG_CRC                          0x0F

/*! @} */ // adc23_reg

/**
 * @addtogroup adc23_cmd
 * @{
 */

/**
 * @brief ADC 23 description commands.
 * @details Specified command for description of ADC 23 Click driver.
 */
#define ADC_CMD_NO_OPERATION                 0x00
#define ADC_CMD_READ_REG                     0x40
#define ADC_CMD_WRITE_REG                    0x80

/*! @} */ // adc23_cmd

/**
 * @defgroup adc23_set ADC 23 Registers Settings
 * @brief Settings for registers of ADC 23 Click driver.
 */

/**
 * @addtogroup adc23_set
 * @{
 */

/**
 * @brief ADC 23 default value of the internal voltage reference.
 * @details Default value of the internal voltage reference of ADC 23 Click driver.
 */
#define ADC23_INT_VREF_2_5V                  2.5f

/**
 * @brief ADC 23 description of CONTROL register data values.
 * @details Specified CONTROL register data values of ADC 23 Click driver.
 */
#define ADC23_SET_CTRL_STOP                  0x01
#define ADC23_SET_CTRL_START                 0x02
#define ADC23_SET_CTRL_SW_RESET              0x58
#define ADC23_MAX_REG_ADDR                   0x0F

/**
 * @brief ADC 23 description of calculation data values.
 * @details Specified calculation data values of ADC 23 Click driver.
 */
#define ADC23_CONV_V_TO_MV                    1000.0f

/**
 * @brief ADC 23 description of the ADC data range.
 * @details Specified ADC data range of ADC 23 Click driver.
 */
#define ADC23_FULL_SCALE_OUT_DATA_RANGE      0x7FFFFFul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc23_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC23_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define ADC23_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc23_set

/**
 * @defgroup adc23_map ADC 23 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 23 Click driver.
 */

/**
 * @addtogroup adc23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 23 Click to the selected MikroBUS.
 */
#define ADC23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.str = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc23_map
/*! @} */ // adc23

/**
 * @brief ADC 23 Click context object.
 * @details Context object definition of ADC 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;   /**< Reset pin. */
    digital_out_t str;   /**< Conversion start pin. */

    // Input pins
    digital_in_t rdy;    /**< Data ready pin. */

    // Modules
    spi_master_t spi;          /**< SPI driver object. */

    pin_name_t   chip_select;  /**< Chip select pin descriptor (used for SPI driver). */
    
    float vref;

} adc23_t;

/**
 * @brief ADC 23 Click configuration object.
 * @details Configuration object definition of ADC 23 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;     /**< Reset pin. */
    pin_name_t str;     /**< Conversion start pin. */
    pin_name_t rdy;     /**< Data ready pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    float vref;

} adc23_cfg_t;

/**
 * @brief ADC 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC23_OK = 0,
    ADC23_ERROR = -1

} adc23_return_value_t;

/*!
 * @addtogroup adc23 ADC 23 Click Driver
 * @brief API for configuring and manipulating ADC 23 Click driver.
 * @{
 */

/**
 * @brief ADC 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc23_cfg_setup ( adc23_cfg_t *cfg );

/**
 * @brief ADC 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_init ( adc23_t *ctx, adc23_cfg_t *cfg );

/**
 * @brief ADC 23 default configuration function.
 * @details This function executes a default configuration of ADC 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc23_default_cfg ( adc23_t *ctx );

/**
 * @brief ADC 23 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_generic_write ( adc23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ADC 23 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_generic_read ( adc23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ADC 23 data transfer function.
 * @details This function writes and reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be transferred (write/read).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_generic_transfer ( adc23_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );

/**
 * @brief ADC 23 read register command function.
 * @details This function is used to read register data and follows an off-frame protocol in which
 * the read command is sent in one frame and the 16-Bit ADC responds with register data in the next frame
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data, 16-Bit ADC value.
 * @param[out] reg_data_out : Output read of register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_read_reg_cmd ( adc23_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t *reg_data_out );

/**
 * @brief ADC 23 read register data function.
 * @details This function is used to read register operation using the maximum 40-bit frame size 
 * in full-duplex operation and follows an off-frame protocol in which
 * the read command is sent in one frame and the 24-Bit ADC responds with register data in the next frame
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data, 24-Bit ADC value.
 * @param[out] reg_data_out : Output read of register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_read_reg_data ( adc23_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t *reg_data_out );

/**
 * @brief ADC 23 write register command function.
 * @details This function is used to write register data performed in a single frame
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data, 16-Bit ADC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_write_reg_cmd ( adc23_t *ctx, uint8_t reg, uint8_t data_in, uint16_t *data_out );

/**
 * @brief ADC 23 write register data function.
 * @details This function is used to write register data performed in a 24-Bit frame size
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data, 24-Bit ADC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_write_reg_data ( adc23_t *ctx, uint8_t reg, uint8_t data_in, uint32_t *data_out );

/**
 * @brief ADC 23 software reset function.
 * @details This function performs the reset sequence
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_sw_reset ( adc23_t *ctx );

/**
 * @brief ADC 23 start conversion function.
 * @details This function performs the conversion start command
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_start_conversion ( adc23_t *ctx );

/**
 * @brief ADC 23 stop conversion function.
 * @details This function performs the conversion stop command
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_stop_conversion ( adc23_t *ctx );

/**
 * @brief ADC 23 read conversion data function.
 * @details This function is used to read 24-Bit ADC raw data value
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[out] adc_data : 24-Bit ADC data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_read_conversion_data ( adc23_t *ctx, int32_t *adc_data );

/**
 * @brief ADC 23 read get voltage level function.
 * @details This function reads results of 24-bit ADC raw data 
 * and converts them to proportional voltage level [mV], 
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc23_get_voltage ( adc23_t *ctx, float *voltage );

/**
 * @brief ADC 23 set start function.
 * @details This function is used for the synchronization control of the ADC converts continuously
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void adc23_set_start ( adc23_t *ctx );

/**
 * @brief ADC 23 set stop function.
 * @details This function is used to stop the ADC converts continuously
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void adc23_set_stop ( adc23_t *ctx );

/**
 * @brief ADC 23 hardware reset function.
 * @details This function resets the module by toggling the reset [RST] pin
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void adc23_hw_reset ( adc23_t *ctx );

/**
 * @brief ADC 23 get data ready function.
 * @details This function get states of the data ready [DRY] pin
 * of the ADS127L11, 400-kSPS, Wide-Bandwidth, 24-Bit, Delta-Sigma ADC
 * on the ADC 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc23_t object definition for detailed explanation.
 * @return @li @c 0 - Conversion data are ready,
 *         @li @c 1 - Conversions are started or resynchronized.
 * @note None.
 */
uint8_t adc23_get_data_ready ( adc23_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ADC23_H

/*! @} */ // adc23

// ------------------------------------------------------------------------ END

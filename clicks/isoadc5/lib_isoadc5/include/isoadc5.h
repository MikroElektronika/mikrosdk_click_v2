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
 * @file isoadc5.h
 * @brief This file contains API for ISO ADC 5 Click Driver.
 */

#ifndef ISOADC5_H
#define ISOADC5_H

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

/*!
 * @addtogroup isoadc5 ISO ADC 5 Click Driver
 * @brief API for configuring and manipulating ISO ADC 5 Click driver.
 * @{
 */

/**
 * @defgroup isoadc5_reg ISO ADC 5 Registers List
 * @brief List of registers of ISO ADC 5 Click driver.
 */

/**
 * @addtogroup isoadc5_reg
 * @{
 */

/**
 * @brief ISO ADC 5 Register Map.
 * @details Specified register map of ISO ADC 5 Click driver.
 */
#define ISOADC5_REG_PROD_ID                 0x00
#define ISOADC5_REG_ADC_1                   0x01
#define ISOADC5_REG_ADC_2                   0x02
#define ISOADC5_REG_ADC_3                   0x03
#define ISOADC5_REG_ADC_4                   0x04
#define ISOADC5_REG_FADC_1                  0x05
#define ISOADC5_REG_FADC_2                  0x06
#define ISOADC5_REG_FADC_3                  0x07
#define ISOADC5_REG_FADC_4                  0x08
#define ISOADC5_REG_COUNTHI_1               0x09
#define ISOADC5_REG_COUNTHI_2               0x0A
#define ISOADC5_REG_COUNTHI_3               0x0B
#define ISOADC5_REG_COUNTHI_4               0x0C
#define ISOADC5_REG_COUNTLO_1               0x0D
#define ISOADC5_REG_COUNTLO_2               0x0E
#define ISOADC5_REG_COUNTLO_3               0x0F
#define ISOADC5_REG_COUNTLO_4               0x10
#define ISOADC5_REG_COUT_STATUS             0x11
#define ISOADC5_REG_INTERRUPT_STATUS        0x12
#define ISOADC5_REG_INTERRUPT_ENABLE        0x13
#define ISOADC5_REG_CONTROL                 0x14

/*! @} */ // isoadc5_reg

/**
 * @defgroup isoadc5_set ISO ADC 5 Registers Settings
 * @brief Settings for registers of ISO ADC 5 Click driver.
 */

/**
 * @addtogroup isoadc5_set
 * @{
 */

/**
 * @brief ISO ADC 5 PROD_ID register.
 * @details Specified bits of PROD_ID register of ISO ADC 5 Click driver.
 */
#define ISOADC5_DEVICE_ID                   0x00
#define ISOADC5_NORMAL_OPERATION            0x00
#define ISOADC5_WAKE_UP_FROM_POR            0x80
#define ISOADC5_DEVICE_REV                  0x01

/**
 * @brief ISO ADC 5 ADC register.
 * @details Specified bits of ADC registers of ISO ADC 5 Click driver.
 */
#define ISOADC5_ADC_NOT_UPDATED             0x8000
#define ISOADC5_ADC_12BIT_MASK              0x0FFF

/**
 * @brief ISO ADC 5 COUTHI register.
 * @details Specified bits of COUTHI registers of ISO ADC 5 Click driver.
 */
#define ISOADC5_CO_MODE_STATUS              0x80
#define ISOADC5_CO_IN_SEL_FILTERED_ADC      0x40

/**
 * @brief ISO ADC 5 COUT STATUS register.
 * @details Specified bits of COUT STATUS register of ISO ADC 5 Click driver.
 */
#define ISOADC5_STATUS_CO_4                 0x08
#define ISOADC5_STATUS_CO_3                 0x04
#define ISOADC5_STATUS_CO_2                 0x02
#define ISOADC5_STATUS_CO_1                 0x01

/**
 * @brief ISO ADC 5 INTERRUPT STATUS register.
 * @details Specified bits of INTERRUPT STATUS register of ISO ADC 5 Click driver.
 */
#define ISOADC5_INT_STATUS_EOC              0x1000
#define ISOADC5_INT_STATUS_ADCF             0x0800
#define ISOADC5_INT_STATUS_FLD              0x0400
#define ISOADC5_INT_STATUS_SPIFRM           0x0200
#define ISOADC5_INT_STATUS_SPICRC           0x0100
#define ISOADC5_INT_STATUS_CO_POS_4         0x0080
#define ISOADC5_INT_STATUS_CO_POS_3         0x0040
#define ISOADC5_INT_STATUS_CO_POS_2         0x0020
#define ISOADC5_INT_STATUS_CO_POS_1         0x0010
#define ISOADC5_INT_STATUS_CO_NEG_4         0x0008
#define ISOADC5_INT_STATUS_CO_NEG_3         0x0004
#define ISOADC5_INT_STATUS_CO_NEG_2         0x0002
#define ISOADC5_INT_STATUS_CO_NEG_1         0x0001

/**
 * @brief ISO ADC 5 CONTROL register.
 * @details Specified bits of CONTROL register of ISO ADC 5 Click driver.
 */
#define ISOADC5_EN_CRC                      0x8000
#define ISOADC5_EN_COMMON_COMP              0x4000
#define ISOADC5_CLEAR_FLT_4                 0x0080
#define ISOADC5_CLEAR_FLT_3                 0x0040
#define ISOADC5_CLEAR_FLT_2                 0x0020
#define ISOADC5_CLEAR_FLT_1                 0x0010
#define ISOADC5_DISABLE_PWR                 0x0008
#define ISOADC5_CLEAR_POR                   0x0004
#define ISOADC5_SOFT_RESET                  0x0002
#define ISOADC5_HARD_RESET                  0x0001

/**
 * @brief ISO ADC 5 ADC channel number.
 * @details Specified ADC channel numbers of ISO ADC 5 Click driver.
 */
#define ISOADC5_ADC_CHANNEL_1               0x01
#define ISOADC5_ADC_CHANNEL_2               0x02
#define ISOADC5_ADC_CHANNEL_3               0x03
#define ISOADC5_ADC_CHANNEL_4               0x04

/**
 * @brief ISO ADC 5 ADC filtered flag.
 * @details Specified ADC filtered flags of ISO ADC 5 Click driver.
 */
#define ISOADC5_ADC_UNFILTERED              0x00
#define ISOADC5_ADC_FILTERED                0x01

/**
 * @brief ISO ADC 5 Maximal voltage input.
 * @details Maximal voltage input value of ISO ADC 5 Click driver.
 */
#define ISOADC5_MAX_VOLTAGE                 48.0

/**
 * @brief ISO ADC 5 SPI mask.
 * @details Specified SPI mask bits of ISO ADC 5 Click driver.
 */
#define ISOADC5_SPI_READ                    0x00
#define ISOADC5_SPI_WRITE                   0x02
#define ISOADC5_SPI_BURST                   0x01

/*! @} */ // isoadc5_set

/**
 * @defgroup isoadc5_map ISO ADC 5 MikroBUS Map
 * @brief MikroBUS pin mapping of ISO ADC 5 Click driver.
 */

/**
 * @addtogroup isoadc5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO ADC 5 Click to the selected MikroBUS.
 */
#define ISOADC5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // isoadc5_map
/*! @} */ // isoadc5

/**
 * @brief ISO ADC 5 Click context object.
 * @details Context object definition of ISO ADC 5 Click driver.
 */
typedef struct
{
    digital_in_t  int_pin;       /**< Interrupt pin. */

    // Modules
    spi_master_t  spi;           /**< SPI driver object. */

    pin_name_t  chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

} isoadc5_t;

/**
 * @brief ISO ADC 5 Click configuration object.
 * @details Configuration object definition of ISO ADC 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  int_pin;                                /**< Interrupt pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} isoadc5_cfg_t;

/**
 * @brief ISO ADC 5 Click burst payload structure object.
 * @details Burst payload structure object definition of ISO ADC 5 Click driver.
 */
typedef struct
{
    uint16_t adc_1;
    uint16_t adc_2;
    uint16_t adc_3;
    uint16_t adc_4;
    uint16_t int_status;

} isoadc5_burst_payload_t;

/**
 * @brief ISO ADC 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISOADC5_OK = 0,
    ISOADC5_ERROR = -1

} isoadc5_return_value_t;

/*!
 * @addtogroup isoadc5 ISO ADC 5 Click Driver
 * @brief API for configuring and manipulating ISO ADC 5 Click driver.
 * @{
 */

/**
 * @brief ISO ADC 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #isoadc5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void isoadc5_cfg_setup ( isoadc5_cfg_t *cfg );

/**
 * @brief ISO ADC 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #isoadc5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc5_init ( isoadc5_t *ctx, isoadc5_cfg_t *cfg );

/**
 * @brief ISO ADC 5 write register function.
 * @details This function writes two bytes of data to the selected register 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @param[in] reg : Register address [0x00-0x14].
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function also calculates and sends the CRC byte when it is enabled.
 */
err_t isoadc5_write_register ( isoadc5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief ISO ADC 5 read register function.
 * @details This function reads two bytes of data from the selected register
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @param[in] reg : Register address [0x00-0x14].
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function also calculates and checks the CRC byte when it is enabled.
 */
err_t isoadc5_read_register ( isoadc5_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief ISO ADC 5 read register function.
 * @details This function reads all filtered or unfiltered ADC data registers as well as the interrupt status
 * register and stores data in the payload structure.
 * @param[in] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @param[in] filt : @li @c 0 - Unfiltered ADC
 *                   @li @c 1 - Filtered ADC.
 * @param[out] payload : Burst payload structure where the read data is being stored.
 * See isoadc5_burst_payload_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function also calculates and checks the CRC byte when it is enabled.
 */
err_t isoadc5_read_register_burst ( isoadc5_t *ctx, uint8_t filt, isoadc5_burst_payload_t *payload );

/**
 * @brief ISO ADC 5 read voltage function.
 * @details This function reads the raw adc data from a desired input channel and converts it to voltage.
 * @param[in] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @param[in] filt : @li @c 0 - Unfiltered ADC
 *                   @li @c 1 - Filtered ADC.
 * @param[in] ch : Input channel selection [1-4].
 * @param[out] volt : Voltage read from a desired input channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function also calculates and checks the CRC byte when it is enabled.
 */
err_t isoadc5_read_voltage( isoadc5_t *ctx, uint8_t filt, uint8_t ch, float *volt );

/**
 * @brief ISO ADC 5 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t isoadc5_get_int_pin ( isoadc5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ISOADC5_H

/*! @} */ // isoadc5

// ------------------------------------------------------------------------ END

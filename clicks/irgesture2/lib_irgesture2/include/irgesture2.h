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
 * @file irgesture2.h
 * @brief This file contains API for IR Gesture 2 Click Driver.
 */

#ifndef IRGESTURE2_H
#define IRGESTURE2_H

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
 * @addtogroup irgesture2 IR Gesture 2 Click Driver
 * @brief API for configuring and manipulating IR Gesture 2 Click driver.
 * @{
 */

/**
 * @defgroup irgesture2_reg IR Gesture 2 Registers List
 * @brief List of registers of IR Gesture 2 Click driver.
 */

/**
 * @addtogroup irgesture2_reg
 * @{
 */

/**
 * @brief IR Gesture 2 register map.
 * @details Specified register map of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_REG_INT_STATUS               0x00
#define IRGESTURE2_REG_MAIN_CONFIG_1            0x01
#define IRGESTURE2_REG_MAIN_CONFIG_2            0x02
#define IRGESTURE2_REG_SEQ_CONFIG_1             0x03
#define IRGESTURE2_REG_SEQ_CONFIG_2             0x04
#define IRGESTURE2_REG_AFE_CONFIG               0x05
#define IRGESTURE2_REG_LED_CONFIG               0x06
#define IRGESTURE2_REG_ADC00H                   0x10
#define IRGESTURE2_REG_ADC00L                   0x11
#define IRGESTURE2_REG_ADC01H                   0x12
#define IRGESTURE2_REG_ADC01L                   0x13
#define IRGESTURE2_REG_ADC02H                   0x14
#define IRGESTURE2_REG_ADC02L                   0x15
#define IRGESTURE2_REG_ADC03H                   0x16
#define IRGESTURE2_REG_ADC03L                   0x17
#define IRGESTURE2_REG_ADC04H                   0x18
#define IRGESTURE2_REG_ADC04L                   0x19
#define IRGESTURE2_REG_ADC05H                   0x1A
#define IRGESTURE2_REG_ADC05L                   0x1B
#define IRGESTURE2_REG_ADC06H                   0x1C
#define IRGESTURE2_REG_ADC06L                   0x1D
#define IRGESTURE2_REG_ADC07H                   0x1E
#define IRGESTURE2_REG_ADC07L                   0x1F
#define IRGESTURE2_REG_ADC08H                   0x20
#define IRGESTURE2_REG_ADC08L                   0x21
#define IRGESTURE2_REG_ADC09H                   0x22
#define IRGESTURE2_REG_ADC09L                   0x23
#define IRGESTURE2_REG_ADC10H                   0x24
#define IRGESTURE2_REG_ADC10L                   0x25
#define IRGESTURE2_REG_ADC11H                   0x26
#define IRGESTURE2_REG_ADC11L                   0x27
#define IRGESTURE2_REG_ADC12H                   0x28
#define IRGESTURE2_REG_ADC12L                   0x29
#define IRGESTURE2_REG_ADC13H                   0x2A
#define IRGESTURE2_REG_ADC13L                   0x2B
#define IRGESTURE2_REG_ADC14H                   0x2C
#define IRGESTURE2_REG_ADC14L                   0x2D
#define IRGESTURE2_REG_ADC15H                   0x2E
#define IRGESTURE2_REG_ADC15L                   0x2F
#define IRGESTURE2_REG_ADC16H                   0x30
#define IRGESTURE2_REG_ADC16L                   0x31
#define IRGESTURE2_REG_ADC17H                   0x32
#define IRGESTURE2_REG_ADC17L                   0x33
#define IRGESTURE2_REG_ADC18H                   0x34
#define IRGESTURE2_REG_ADC18L                   0x35
#define IRGESTURE2_REG_ADC19H                   0x36
#define IRGESTURE2_REG_ADC19L                   0x37
#define IRGESTURE2_REG_ADC20H                   0x38
#define IRGESTURE2_REG_ADC20L                   0x39
#define IRGESTURE2_REG_ADC21H                   0x3A
#define IRGESTURE2_REG_ADC21L                   0x3B
#define IRGESTURE2_REG_ADC22H                   0x3C
#define IRGESTURE2_REG_ADC22L                   0x3D
#define IRGESTURE2_REG_ADC23H                   0x3E
#define IRGESTURE2_REG_ADC23L                   0x3F
#define IRGESTURE2_REG_ADC24H                   0x40
#define IRGESTURE2_REG_ADC24L                   0x41
#define IRGESTURE2_REG_ADC25H                   0x42
#define IRGESTURE2_REG_ADC25L                   0x43
#define IRGESTURE2_REG_ADC26H                   0x44
#define IRGESTURE2_REG_ADC26L                   0x45
#define IRGESTURE2_REG_ADC27H                   0x46
#define IRGESTURE2_REG_ADC27L                   0x47
#define IRGESTURE2_REG_ADC28H                   0x48
#define IRGESTURE2_REG_ADC28L                   0x49
#define IRGESTURE2_REG_ADC29H                   0x4A
#define IRGESTURE2_REG_ADC29L                   0x4B
#define IRGESTURE2_REG_ADC30H                   0x4C
#define IRGESTURE2_REG_ADC30L                   0x4D
#define IRGESTURE2_REG_ADC31H                   0x4E
#define IRGESTURE2_REG_ADC31L                   0x4F
#define IRGESTURE2_REG_ADC32H                   0x50
#define IRGESTURE2_REG_ADC32L                   0x51
#define IRGESTURE2_REG_ADC33H                   0x52
#define IRGESTURE2_REG_ADC33L                   0x53
#define IRGESTURE2_REG_ADC34H                   0x54
#define IRGESTURE2_REG_ADC34L                   0x55
#define IRGESTURE2_REG_ADC35H                   0x56
#define IRGESTURE2_REG_ADC35L                   0x57
#define IRGESTURE2_REG_ADC36H                   0x58
#define IRGESTURE2_REG_ADC36L                   0x59
#define IRGESTURE2_REG_ADC37H                   0x5A
#define IRGESTURE2_REG_ADC37L                   0x5B
#define IRGESTURE2_REG_ADC38H                   0x5C
#define IRGESTURE2_REG_ADC38L                   0x5D
#define IRGESTURE2_REG_ADC39H                   0x5E
#define IRGESTURE2_REG_ADC39L                   0x5F
#define IRGESTURE2_REG_ADC40H                   0x60
#define IRGESTURE2_REG_ADC40L                   0x61
#define IRGESTURE2_REG_ADC41H                   0x62
#define IRGESTURE2_REG_ADC41L                   0x63
#define IRGESTURE2_REG_ADC42H                   0x64
#define IRGESTURE2_REG_ADC42L                   0x65
#define IRGESTURE2_REG_ADC43H                   0x66
#define IRGESTURE2_REG_ADC43L                   0x67
#define IRGESTURE2_REG_ADC44H                   0x68
#define IRGESTURE2_REG_ADC44L                   0x69
#define IRGESTURE2_REG_ADC45H                   0x6A
#define IRGESTURE2_REG_ADC45L                   0x6B
#define IRGESTURE2_REG_ADC46H                   0x6C
#define IRGESTURE2_REG_ADC46L                   0x6D
#define IRGESTURE2_REG_ADC47H                   0x6E
#define IRGESTURE2_REG_ADC47L                   0x6F
#define IRGESTURE2_REG_ADC48H                   0x70
#define IRGESTURE2_REG_ADC48L                   0x71
#define IRGESTURE2_REG_ADC49H                   0x72
#define IRGESTURE2_REG_ADC49L                   0x73
#define IRGESTURE2_REG_ADC50H                   0x74
#define IRGESTURE2_REG_ADC50L                   0x75
#define IRGESTURE2_REG_ADC51H                   0x76
#define IRGESTURE2_REG_ADC51L                   0x77
#define IRGESTURE2_REG_ADC52H                   0x78
#define IRGESTURE2_REG_ADC52L                   0x79
#define IRGESTURE2_REG_ADC53H                   0x7A
#define IRGESTURE2_REG_ADC53L                   0x7B
#define IRGESTURE2_REG_ADC54H                   0x7C
#define IRGESTURE2_REG_ADC54L                   0x7D
#define IRGESTURE2_REG_ADC55H                   0x7E
#define IRGESTURE2_REG_ADC55L                   0x7F
#define IRGESTURE2_REG_ADC56H                   0x80
#define IRGESTURE2_REG_ADC56L                   0x81
#define IRGESTURE2_REG_ADC57H                   0x82
#define IRGESTURE2_REG_ADC57L                   0x83
#define IRGESTURE2_REG_ADC58H                   0x84
#define IRGESTURE2_REG_ADC58L                   0x85
#define IRGESTURE2_REG_ADC59H                   0x86
#define IRGESTURE2_REG_ADC59L                   0x87
#define IRGESTURE2_REG_COLUMN_GAIN_2_1          0xA5
#define IRGESTURE2_REG_COLUMN_GAIN_4_3          0xA6
#define IRGESTURE2_REG_COLUMN_GAIN_6_5          0xA7
#define IRGESTURE2_REG_COLUMN_GAIN_8_7          0xA8
#define IRGESTURE2_REG_COLUMN_GAIN_10_9         0xA9
#define IRGESTURE2_REG_LED_CTRL                 0xC1

/*! @} */ // irgesture2_reg

/**
 * @defgroup irgesture2_set IR Gesture 2 Registers Settings
 * @brief Settings for registers of IR Gesture 2 Click driver.
 */

/**
 * @addtogroup irgesture2_set
 * @{
 */

/**
 * @brief IR Gesture 2 main configuration 1 register settings.
 * @details Specified main configuration 1 register settings of IR Gesture 2 Click driver.
 */
#define IRGESTRURE2_EXSYNC_INPUT                0x00
#define IRGESTRURE2_EXSYNC_INPUT_SLAVE          0x10
#define IRGESTRURE2_EXSYNC_INPUT_MASTER         0x20
#define IRGESTRURE2_EOCINTE_ENABLE              0x04

/**
 * @brief IR Gesture 2 main configuration 2 register settings.
 * @details Specified main configuration 2 register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_SHUTDOWN                     0x80
#define IRGESTURE2_RESET                        0x40
#define IRGESTURE2_SYNC                         0x10
#define IRGESTURE2_ONE_SHOT_ENABLE              0x08
#define IRGESTURE2_ONE_SHOT_TRIGGER             0x04
#define IRGESTURE2_CONTINUOUS_CONVERSION        0x02

/**
 * @brief IR Gesture 2 seq configuration 1 register settings.
 * @details Specified seq configuration 1 register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_EOC_DELAY_0MS                0x00
#define IRGESTURE2_EOC_DELAY_1p56MS             0x10
#define IRGESTURE2_EOC_DELAY_3p12MS             0x20
#define IRGESTURE2_EOC_DELAY_6p25MS             0x30
#define IRGESTURE2_EOC_DELAY_12p49MS            0x40
#define IRGESTURE2_EOC_DELAY_24p98MS            0x50
#define IRGESTURE2_EOC_DELAY_49p97MS            0x60
#define IRGESTURE2_EOC_DELAY_99p94MS            0x70
#define IRGESTURE2_EOC_DELAY_199p98MS           0x80
#define IRGESTURE2_EOC_DELAY_399p75MS           0x90
#define IRGESTURE2_EOC_DELAY_799p5MS            0xA0
#define IRGESTURE2_EOC_DELAY_1599MS             0xB0
#define IRGESTURE2_INTEGRATION_TIME_6p25US      0x00
#define IRGESTURE2_INTEGRATION_TIME_12p5US      0x02
#define IRGESTURE2_INTEGRATION_TIME_25US        0x04
#define IRGESTURE2_INTEGRATION_TIME_50US        0x06
#define IRGESTURE2_INTEGRATION_TIME_100US       0x08
#define IRGESTURE2_INTEGRATION_TIME_200US       0x0A
#define IRGESTURE2_INTEGRATION_TIME_400US       0x0C
#define IRGESTURE2_INTEGRATION_TIME_800US       0x0E

/**
 * @brief IR Gesture 2 seq configuration 2 register settings.
 * @details Specified seq configuration 2 register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_NRPT_1                       0x00
#define IRGESTURE2_NRPT_2                       0x20
#define IRGESTURE2_NRPT_4                       0x40
#define IRGESTURE2_NRPT_8                       0x60
#define IRGESTURE2_NRPT_16                      0x80
#define IRGESTURE2_NRPT_32                      0xA0
#define IRGESTURE2_NRPT_64                      0xC0
#define IRGESTURE2_NRPT_128                     0xE0
#define IRGESTURE2_NCDS_1                       0x00
#define IRGESTURE2_NCDS_2                       0x04
#define IRGESTURE2_NCDS_4                       0x08
#define IRGESTURE2_NCDS_8                       0x0C
#define IRGESTURE2_NCDS_16                      0x10
#define IRGESTURE2_NCDS_32                      0x14
#define IRGESTURE2_NCDS_64                      0x18
#define IRGESTURE2_NCDS_128                     0x1C
#define IRGESTURE2_CDSMODE                      0x02

/**
 * @brief IR Gesture 2 afe configuration register settings.
 * @details Specified afe configuration register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_ALC_COARSE                   0x40
#define IRGESTURE2_ALCEN_ENABLE                 0x08
#define IRGESTURE2_PGA_1                        0x00
#define IRGESTURE2_PGA_1_PER_4                  0x01
#define IRGESTURE2_PGA_1_PER_16                 0x02
#define IRGESTURE2_PGA_1_PER_32                 0x03

/**
 * @brief IR Gesture 2 led configuration register settings.
 * @details Specified led configuration register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_DUTY_CYCLE_1                 0x00
#define IRGESTURE2_DUTY_CYCLE_2                 0x01
#define IRGESTURE2_DUTY_CYCLE_3                 0x02
#define IRGESTURE2_DUTY_CYCLE_4                 0x03
#define IRGESTURE2_DUTY_CYCLE_5                 0x04
#define IRGESTURE2_DUTY_CYCLE_6                 0x05
#define IRGESTURE2_DUTY_CYCLE_7                 0x06
#define IRGESTURE2_DUTY_CYCLE_8                 0x07
#define IRGESTURE2_DUTY_CYCLE_9                 0x08
#define IRGESTURE2_DUTY_CYCLE_10                0x09
#define IRGESTURE2_DUTY_CYCLE_11                0x0A
#define IRGESTURE2_DUTY_CYCLE_12                0x0B
#define IRGESTURE2_DUTY_CYCLE_13                0x0C
#define IRGESTURE2_DUTY_CYCLE_14                0x0D
#define IRGESTURE2_DUTY_CYCLE_15                0x0E
#define IRGESTURE2_DUTY_CYCLE_16                0x0F

/**
 * @brief IR Gesture 2 column gain register settings.
 * @details Specified column gain register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p33      0x00
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p37      0x10
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p43      0x20
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p49      0x30
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p56      0x40
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p65      0x50
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p75      0x60
#define IRGESTURE2_UPPER_CGAIN_FACTOR_0p86      0x70
#define IRGESTURE2_UPPER_CGAIN_FACTOR_1p00      0x80
#define IRGESTURE2_UPPER_CGAIN_FACTOR_1p14      0x90
#define IRGESTURE2_UPPER_CGAIN_FACTOR_1p33      0xA0
#define IRGESTURE2_UPPER_CGAIN_FACTOR_1p53      0xB0
#define IRGESTURE2_UPPER_CGAIN_FACTOR_1p79      0xC0
#define IRGESTURE2_UPPER_CGAIN_FACTOR_2p04      0xD0
#define IRGESTURE2_UPPER_CGAIN_FACTOR_2p38      0xE0
#define IRGESTURE2_UPPER_CGAIN_FACTOR_2p70      0xF0
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p33      0x00
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p37      0x01
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p43      0x02
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p49      0x03
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p56      0x04
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p65      0x05
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p75      0x06
#define IRGESTURE2_LOWER_CGAIN_FACTOR_0p86      0x07
#define IRGESTURE2_LOWER_CGAIN_FACTOR_1p00      0x08
#define IRGESTURE2_LOWER_CGAIN_FACTOR_1p14      0x09
#define IRGESTURE2_LOWER_CGAIN_FACTOR_1p33      0x0A
#define IRGESTURE2_LOWER_CGAIN_FACTOR_1p53      0x0B
#define IRGESTURE2_LOWER_CGAIN_FACTOR_1p79      0x0C
#define IRGESTURE2_LOWER_CGAIN_FACTOR_2p04      0x0D
#define IRGESTURE2_LOWER_CGAIN_FACTOR_2p38      0x0E
#define IRGESTURE2_LOWER_CGAIN_FACTOR_2p70      0x0F

/**
 * @brief IR Gesture 2 led ctrl register settings.
 * @details Specified led ctrl register settings of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_GAINSEL_CGAIN                0x00
#define IRGESTURE2_GAINSEL_INTERNAL_TRIM        0x08
#define IRGESTURE2_DRV_EN_DISABLE               0x00
#define IRGESTURE2_DRV_EN_ENABLE                0x04
#define IRGESTURE2_ELED_EN_DISABLE              0x00
#define IRGESTURE2_ELED_EN_ENABLE               0x02
#define IRGESTURE2_ELED_POL_NMOS                0x00
#define IRGESTURE2_ELED_POL_PMOS                0x01

/**
 * @brief IR Gesture 2 SPI read/write command.
 * @details Specified SPI read/write command of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_SPI_READ                     0x80
#define IRGESTURE2_SPI_WRITE                    0x00

/**
 * @brief IR Gesture 2 sensor pixels size.
 * @details Specified sensor pixels size of IR Gesture 2 Click driver.
 */
#define IRGESTURE2_SENSOR_X_SIZE                10
#define IRGESTURE2_SENSOR_Y_SIZE                6
#define IRGESTURE2_NUM_SENSOR_PIXELS            ( IRGESTURE2_SENSOR_X_SIZE * IRGESTURE2_SENSOR_Y_SIZE )

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b irgesture2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define IRGESTURE2_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define IRGESTURE2_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // irgesture2_set

/**
 * @defgroup irgesture2_map IR Gesture 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Gesture 2 Click driver.
 */

/**
 * @addtogroup irgesture2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Gesture 2 Click to the selected MikroBUS.
 */
#define IRGESTURE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // irgesture2_map
/*! @} */ // irgesture2

/**
 * @brief IR Gesture 2 Click context object.
 * @details Context object definition of IR Gesture 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} irgesture2_t;

/**
 * @brief IR Gesture 2 Click configuration object.
 * @details Configuration object definition of IR Gesture 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  int_pin;        /**< Interrupt pin. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} irgesture2_cfg_t;

/**
 * @brief IR Gesture 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRGESTURE2_OK = 0,
    IRGESTURE2_ERROR = -1

} irgesture2_return_value_t;

/*!
 * @addtogroup irgesture2 IR Gesture 2 Click Driver
 * @brief API for configuring and manipulating IR Gesture 2 Click driver.
 * @{
 */

/**
 * @brief IR Gesture 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irgesture2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irgesture2_cfg_setup ( irgesture2_cfg_t *cfg );

/**
 * @brief IR Gesture 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irgesture2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture2_init ( irgesture2_t *ctx, irgesture2_cfg_t *cfg );

/**
 * @brief IR Gesture 2 default configuration function.
 * @details This function executes a default configuration of IR Gesture 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irgesture2_default_cfg ( irgesture2_t *ctx );

/**
 * @brief IR Gesture 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture2_generic_write ( irgesture2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief IR Gesture 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture2_generic_read ( irgesture2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief IR Gesture 2 write register function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture2_write_register ( irgesture2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief IR Gesture 2 read register function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture2_read_register ( irgesture2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief IR Gesture 2 read pixels function.
 * @details This function reads the raw ADC values of entire 60-pixel IR photodiode array.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @param[out] pixels : Array of 60 int16_t elements where to store the pixels values.
 * @param[in] flip_pixels : Flip pixels, set to true if the click board is mounted upside-down.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture2_read_pixels ( irgesture2_t *ctx, int16_t *pixels, bool flip_pixels );

/**
 * @brief IR Gesture 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #irgesture2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t irgesture2_get_int_pin ( irgesture2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IRGESTURE2_H

/*! @} */ // irgesture2

// ------------------------------------------------------------------------ END

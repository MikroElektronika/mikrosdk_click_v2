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
 * @file isoadc7.h
 * @brief This file contains API for ISO ADC 7 Click Driver.
 */

#ifndef ISOADC7_H
#define ISOADC7_H

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
 * @addtogroup isoadc7 ISO ADC 7 Click Driver
 * @brief API for configuring and manipulating ISO ADC 7 Click driver.
 * @{
 */

/**
 * @defgroup isoadc7_reg ISO ADC 7 Registers List
 * @brief List of registers of ISO ADC 7 Click driver.
 */

/**
 * @addtogroup isoadc7_reg
 * @{
 */

/**
 * @brief ISO ADC 7 command list.
 * @details Specified command list of ISO ADC 7 Click driver.
 */
#define ISOADC7_CMD_NULL                    0x0000
#define ISOADC7_CMD_RESET                   0x0011
#define ISOADC7_CMD_STANDBY                 0x0022
#define ISOADC7_CMD_WAKEUP                  0x0033
#define ISOADC7_CMD_LOCK                    0x0555
#define ISOADC7_CMD_UNLOCK                  0x0655
#define ISOADC7_CMD_RREG                    0xA000
#define ISOADC7_CMD_WREG                    0x6000

/**
 * @brief ISO ADC 7 response list.
 * @details Specified response list of ISO ADC 7 Click driver.
 */
#define ISOADC7_RSP_RESET                   0xFF23
#define ISOADC7_RSP_STANDBY                 0x0022
#define ISOADC7_RSP_WAKEUP                  0x0033
#define ISOADC7_RSP_LOCK                    0x0555
#define ISOADC7_RSP_UNLOCK                  0x0655
#define ISOADC7_RSP_RREG                    0xE000
#define ISOADC7_RSP_WREG                    0x4000

/**
 * @brief ISO ADC 7 register list.
 * @details Specified register list of ISO ADC 7 Click driver.
 */
#define ISOADC7_REG_ID                      0x00
#define ISOADC7_REG_STATUS                  0x01
#define ISOADC7_REG_MODE                    0x02
#define ISOADC7_REG_CLOCK                   0x03
#define ISOADC7_REG_GAIN                    0x04
#define ISOADC7_REG_CFG                     0x06
#define ISOADC7_REG_CH0_CFG                 0x09
#define ISOADC7_REG_CH0_OCAL_MSB            0x0A
#define ISOADC7_REG_CH0_OCAL_LSB            0x0B
#define ISOADC7_REG_CH0_GCAL_MSB            0x0C
#define ISOADC7_REG_CH0_GCAL_LSB            0x0D
#define ISOADC7_REG_CH1_CFG                 0x0E
#define ISOADC7_REG_CH1_OCAL_MSB            0x0F
#define ISOADC7_REG_CH1_OCAL_LSB            0x10
#define ISOADC7_REG_CH1_GCAL_MSB            0x11
#define ISOADC7_REG_CH1_GCAL_LSB            0x12
#define ISOADC7_REG_CH2_CFG                 0x13
#define ISOADC7_REG_CH2_OCAL_MSB            0x14
#define ISOADC7_REG_CH2_OCAL_LSB            0x15
#define ISOADC7_REG_CH2_GCAL_MSB            0x16
#define ISOADC7_REG_CH2_GCAL_LSB            0x17
#define ISOADC7_REG_DCDC_CTRL               0x31
#define ISOADC7_REG_REGMAP_CRC              0x3E

/*! @} */ // isoadc7_reg

/**
 * @defgroup isoadc7_set ISO ADC 7 Registers Settings
 * @brief Settings for registers of ISO ADC 7 Click driver.
 */

/**
 * @addtogroup isoadc7_set
 * @{
 */

/**
 * @brief ISO ADC 7 ID register setting.
 * @details Specified setting for ID register of ISO ADC 7 Click driver.
 */
#define ISOADC7_DEVICE_ID                   0x2300
#define ISOADC7_DEVICE_ID_MASK              0xFF00

/**
 * @brief ISO ADC 7 STATUS register setting.
 * @details Specified setting for STATUS register of ISO ADC 7 Click driver.
 */
#define ISOADC7_STATUS_LOCK                 0x8000
#define ISOADC7_STATUS_F_RESYNC             0x4000
#define ISOADC7_STATUS_REG_MAP              0x2000
#define ISOADC7_STATUS_CRC_ERR              0x1000
#define ISOADC7_STATUS_CRC_TYPE_CCITT       0x0000
#define ISOADC7_STATUS_CRC_TYPE_ANSI        0x0800
#define ISOADC7_STATUS_CRC_TYPE_MASK        0x0800
#define ISOADC7_STATUS_RESET                0x0400
#define ISOADC7_STATUS_WLENGTH_16BIT        0x0000
#define ISOADC7_STATUS_WLENGTH_24BIT        0x0100
#define ISOADC7_STATUS_WLENGTH_32BIT_ZERO   0x0200
#define ISOADC7_STATUS_WLENGTH_32BIT_MSB    0x0300
#define ISOADC7_STATUS_WLENGTH_MASK         0x0300
#define ISOADC7_STATUS_FUSE_FAIL            0x0080
#define ISOADC7_STATUS_SEC_FAIL             0x0040
#define ISOADC7_STATUS_DRDY2                0x0004
#define ISOADC7_STATUS_DRDY1                0x0002
#define ISOADC7_STATUS_DRDY0                0x0001

/**
 * @brief ISO ADC 7 MODE register setting.
 * @details Specified setting for MODE register of ISO ADC 7 Click driver.
 */
#define ISOADC7_MODE_REG_CRC_EN             0x2000
#define ISOADC7_MODE_RX_CRC_EN              0x1000
#define ISOADC7_MODE_CRC_TYPE_CCITT         0x0000
#define ISOADC7_MODE_CRC_TYPE_ANSI          0x0800
#define ISOADC7_MODE_CRC_TYPE_MASK          0x0800
#define ISOADC7_MODE_RESET                  0x0400
#define ISOADC7_MODE_WLENGTH_16BIT          0x0000
#define ISOADC7_MODE_WLENGTH_24BIT          0x0100
#define ISOADC7_MODE_WLENGTH_32BIT_ZERO     0x0200
#define ISOADC7_MODE_WLENGTH_32BIT_MSB      0x0300
#define ISOADC7_MODE_WLENGTH_MASK           0x0300
#define ISOADC7_MODE_TIMEOUT_ENABLE         0x0010
#define ISOADC7_MODE_DRDY_SEL_MOST_LAGGING  0x0000
#define ISOADC7_MODE_DRDY_SEL_LOGIC_OR      0x0004
#define ISOADC7_MODE_DRDY_SEL_MOST_LEADING  0x0008
#define ISOADC7_MODE_DRDY_SEL_MASK          0x000C
#define ISOADC7_MODE_DRDY_HIZ               0x0002
#define ISOADC7_MODE_DRDY_FMT               0x0001

/**
 * @brief ISO ADC 7 CLOCK register setting.
 * @details Specified setting for CLOCK register of ISO ADC 7 Click driver.
 */
#define ISOADC7_CLOCK_CH2_EN                0x0400
#define ISOADC7_CLOCK_CH1_EN                0x0200
#define ISOADC7_CLOCK_CH0_EN                0x0100
#define ISOADC7_CLOCK_CLK_DIV_2             0x0000
#define ISOADC7_CLOCK_CLK_DIV_4             0x0040
#define ISOADC7_CLOCK_CLK_DIV_8             0x0080
#define ISOADC7_CLOCK_CLK_DIV_12            0x00C0
#define ISOADC7_CLOCK_CLK_DIV_MASK          0x00C0
#define ISOADC7_CLOCK_TURBO_EN              0x0020
#define ISOADC7_CLOCK_OSR_128               0x0000
#define ISOADC7_CLOCK_OSR_256               0x0004
#define ISOADC7_CLOCK_OSR_512               0x0008
#define ISOADC7_CLOCK_OSR_1024              0x000C
#define ISOADC7_CLOCK_OSR_2048              0x0010
#define ISOADC7_CLOCK_OSR_4096              0x0014
#define ISOADC7_CLOCK_OSR_8192              0x0018
#define ISOADC7_CLOCK_OSR_16384             0x001C
#define ISOADC7_CLOCK_OSR_MASK              0x001C
#define ISOADC7_CLOCK_PWR_LOW               0x0001
#define ISOADC7_CLOCK_PWR_HIGH              0x0002
#define ISOADC7_CLOCK_PWR_MASK              0x0003

/**
 * @brief ISO ADC 7 CFG register setting.
 * @details Specified setting for CFG register of ISO ADC 7 Click driver.
 */
#define ISOADC7_CFG_GPO_EN                  0x4000
#define ISOADC7_CFG_GPO_DAT_ONE             0x2000
#define ISOADC7_CFG_GC_DLY_2                0x0000
#define ISOADC7_CFG_GC_DLY_4                0x0200
#define ISOADC7_CFG_GC_DLY_8                0x0400
#define ISOADC7_CFG_GC_DLY_16               0x0600
#define ISOADC7_CFG_GC_DLY_32               0x0800
#define ISOADC7_CFG_GC_DLY_64               0x0A00
#define ISOADC7_CFG_GC_DLY_128              0x0C00
#define ISOADC7_CFG_GC_DLY_256              0x0E00
#define ISOADC7_CFG_GC_DLY_512              0x1000
#define ISOADC7_CFG_GC_DLY_1024             0x1200
#define ISOADC7_CFG_GC_DLY_2048             0x1400
#define ISOADC7_CFG_GC_DLY_4096             0x1600
#define ISOADC7_CFG_GC_DLY_8192             0x1800
#define ISOADC7_CFG_GC_DLY_16384            0x1A00
#define ISOADC7_CFG_GC_DLY_32768            0x1C00
#define ISOADC7_CFG_GC_DLY_65536            0x1E00
#define ISOADC7_CFG_GC_DLY_MASK             0x1E00
#define ISOADC7_CFG_GC_EN                   0x0100

/**
 * @brief ISO ADC 7 CH0_CFG register setting.
 * @details Specified setting for CH0_CFG register of ISO ADC 7 Click driver.
 */
#define ISOADC7_CH0_CFG_PHASE_MASK          0xFFC0
#define ISOADC7_CH0_CFG_MUX_AIN0P_AIN0N     0x0000
#define ISOADC7_CH0_CFG_MUX_AIN0_DISCON     0x0001
#define ISOADC7_CH0_CFG_MUX_DC_DIAG         0x0002
#define ISOADC7_CH0_CFG_MUX_AC_DIAG         0x0003
#define ISOADC7_CH0_CFG_MUX_MASK            0x0003

/**
 * @brief ISO ADC 7 CH1_CFG register setting.
 * @details Specified setting for CH1_CFG register of ISO ADC 7 Click driver.
 */
#define ISOADC7_CH1_CFG_PHASE_MASK          0xFFC0
#define ISOADC7_CH1_CFG_MUX_AIN1P_AIN12N    0x0000
#define ISOADC7_CH1_CFG_MUX_AIN1_DISCON     0x0001
#define ISOADC7_CH1_CFG_MUX_DC_DIAG         0x0002
#define ISOADC7_CH1_CFG_MUX_AC_DIAG         0x0003
#define ISOADC7_CH1_CFG_MUX_MASK            0x0003

/**
 * @brief ISO ADC 7 CH2_CFG register setting.
 * @details Specified setting for CH2_CFG register of ISO ADC 7 Click driver.
 */
#define ISOADC7_CH2_CFG_PHASE_MASK          0xFFC0
#define ISOADC7_CH2_CFG_TS_SEL_INT          0x0000
#define ISOADC7_CH2_CFG_TS_SEL_EXT          0x0020
#define ISOADC7_CH2_CFG_TS_SEL_MASK         0x0020
#define ISOADC7_CH2_CFG_TS_EN               0x0010
#define ISOADC7_CH2_CFG_TS_CHOP_INV         0x0004
#define ISOADC7_CH2_CFG_MUX_AIN2P_AIN12N    0x0000
#define ISOADC7_CH2_CFG_MUX_AIN2_DISCON     0x0001
#define ISOADC7_CH2_CFG_MUX_DC_DIAG         0x0002
#define ISOADC7_CH2_CFG_MUX_AC_DIAG         0x0003
#define ISOADC7_CH2_CFG_MUX_MASK            0x0003

/**
 * @brief ISO ADC 7 DCDC_CTRL register setting.
 * @details Specified setting for DCDC_CTRL register of ISO ADC 7 Click driver.
 */
#define ISOADC7_DCDC_CTRL_FREQ_3_78_TO_4_10 0x0000
#define ISOADC7_DCDC_CTRL_FREQ_3_52_TO_3_84 0x0100
#define ISOADC7_DCDC_CTRL_FREQ_3_30_TO_3_59 0x0200
#define ISOADC7_DCDC_CTRL_FREQ_3_09_TO_3_36 0x0300
#define ISOADC7_DCDC_CTRL_FREQ_2_89_TO_3_15 0x0400
#define ISOADC7_DCDC_CTRL_FREQ_2_71_TO_2_95 0x0500
#define ISOADC7_DCDC_CTRL_FREQ_2_53_TO_2_76 0x0600
#define ISOADC7_DCDC_CTRL_FREQ_2_37_TO_2_59 0x0700
#define ISOADC7_DCDC_CTRL_FREQ_2_22_TO_2_42 0x0800
#define ISOADC7_DCDC_CTRL_FREQ_2_08_TO_2_27 0x0900
#define ISOADC7_DCDC_CTRL_FREQ_1_95_TO_2_12 0x0A00
#define ISOADC7_DCDC_CTRL_FREQ_1_82_TO_1_99 0x0B00
#define ISOADC7_DCDC_CTRL_FREQ_1_71_TO_1_86 0x0C00
#define ISOADC7_DCDC_CTRL_FREQ_1_60_TO_1_74 0x0D00
#define ISOADC7_DCDC_CTRL_FREQ_1_50_TO_1_63 0x0E00
#define ISOADC7_DCDC_CTRL_FREQ_1_40_TO_1_53 0x0F00
#define ISOADC7_DCDC_CTRL_DCDC_EN           0x0001

/**
 * @brief ISO ADC 7 GAIN setting.
 * @details Specified setting for GAIN of ISO ADC 7 Click driver.
 */
#define ISOADC7_GAIN_1                      0x00
#define ISOADC7_GAIN_2                      0x01
#define ISOADC7_GAIN_4                      0x02
#define ISOADC7_GAIN_8                      0x03
#define ISOADC7_GAIN_16                     0x04
#define ISOADC7_GAIN_32                     0x05
#define ISOADC7_GAIN_64                     0x06
#define ISOADC7_GAIN_128                    0x07

/**
 * @brief ISO ADC 7 VREF setting.
 * @details Specified setting for VREF of ISO ADC 7 Click driver.
 */
#define ISOADC7_INTERNAL_VREF_MV            1200.0f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b isoadc7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ISOADC7_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ISOADC7_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // isoadc7_set

/**
 * @defgroup isoadc7_map ISO ADC 7 MikroBUS Map
 * @brief MikroBUS pin mapping of ISO ADC 7 Click driver.
 */

/**
 * @addtogroup isoadc7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO ADC 7 Click to the selected MikroBUS.
 */
#define ISOADC7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.xen = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.drdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // isoadc7_map
/*! @} */ // isoadc7

/**
 * @brief ISO ADC 7 Click data object.
 * @details Data object definition of ISO ADC 7 Click driver.
 */
typedef struct
{
    uint16_t status;            /**< Status register data. */
    int32_t ch0_data;           /**< CH0 raw ADC data. */
    int32_t ch1_data;           /**< CH1 raw ADC data. */
    int32_t ch2_data;           /**< CH2 raw ADC data. */

} isoadc7_data_t;

/**
 * @brief ISO ADC 7 Click context object.
 * @details Context object definition of ISO ADC 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t xen;          /**< 8.192 MHz oscillator enable pin (active high). */

    // Input pins
    digital_in_t drdy;          /**< Data ready pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t      word_size;     /**< Number of bytes in a word, configurable to 2, 3, and 4 bytes. */
    float        fsr_ch0;       /**< Full-scale range +- for CH0. */
    float        fsr_ch1;       /**< Full-scale range +- for CH1. */
    float        fsr_ch2;       /**< Full-scale range +- for CH2. */

} isoadc7_t;

/**
 * @brief ISO ADC 7 Click configuration object.
 * @details Configuration object definition of ISO ADC 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t xen;             /**< 8.192 MHz oscillator enable pin (active high). */
    pin_name_t drdy;            /**< Data ready pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} isoadc7_cfg_t;

/**
 * @brief ISO ADC 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISOADC7_OK = 0,
    ISOADC7_ERROR = -1

} isoadc7_return_value_t;

/*!
 * @addtogroup isoadc7 ISO ADC 7 Click Driver
 * @brief API for configuring and manipulating ISO ADC 7 Click driver.
 * @{
 */

/**
 * @brief ISO ADC 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #isoadc7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void isoadc7_cfg_setup ( isoadc7_cfg_t *cfg );

/**
 * @brief ISO ADC 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #isoadc7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_init ( isoadc7_t *ctx, isoadc7_cfg_t *cfg );

/**
 * @brief ISO ADC 7 default configuration function.
 * @details This function executes a default configuration of ISO ADC 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t isoadc7_default_cfg ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 write reg function.
 * @details This function writes a data word to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_write_reg ( isoadc7_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief ISO ADC 7 write regs function.
 * @details This function writes a desired number of data words starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of words to be written [1-23].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_write_regs ( isoadc7_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t len );

/**
 * @brief ISO ADC 7 read reg function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_read_reg ( isoadc7_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief ISO ADC 7 read regs function.
 * @details This function reads a desired number of data words starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of words to be read [2-23].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_read_regs ( isoadc7_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief ISO ADC 7 standby function.
 * @details This function sets the device to standby mode.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_standby ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 wakeup function.
 * @details This function wakes up the device from standby mode.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_wakeup ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 lock function.
 * @details This function locks the device settings.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_lock ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 unlock function.
 * @details This function unlocks the device settings.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_unlock ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 sw reset function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_sw_reset ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void isoadc7_reset_device ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void isoadc7_set_rst_pin ( isoadc7_t *ctx, uint8_t state );

/**
 * @brief ISO ADC 7 enable osc function.
 * @details This function enables the 8.192 MHz oscillator by setting the XEN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void isoadc7_enable_osc ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 disable osc function.
 * @details This function disables the 8.192 MHz oscillator by setting the XEN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void isoadc7_disable_osc ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 get DRDY pin function.
 * @details This function returns the DRDY pin logic state.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t isoadc7_get_drdy_pin ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 check ID function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_check_id ( isoadc7_t *ctx );

/**
 * @brief ISO ADC 7 set word size function.
 * @details This function sets the data word size to 2, 3, or 4 bytes.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] word_size : Word size in bytes [2-4].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_set_word_size ( isoadc7_t *ctx, uint8_t word_size );

/**
 * @brief ISO ADC 7 set gain function.
 * @details This function sets the gain level for all channels.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[in] gain_ch0 : Gain level of channel 0 [0-7].
 * @param[in] gain_ch1 : Gain level of channel 1 [0-7].
 * @param[in] gain_ch2 : Gain level of channel 2 [0-7].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_set_gain ( isoadc7_t *ctx, uint8_t gain_ch0, uint8_t gain_ch1, uint8_t gain_ch2 );

/**
 * @brief ISO ADC 7 read data function.
 * @details This function reads the status register and raw data of all three channels.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * See #isoadc7_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_read_data ( isoadc7_t *ctx, isoadc7_data_t *data_out );

/**
 * @brief ISO ADC 7 read voltage function.
 * @details This function reads the voltage measurements of all three channels.
 * @param[in] ctx : Click context object.
 * See #isoadc7_t object definition for detailed explanation.
 * @param[out] ch0 : Voltage measurement from channel 0 in millivolts.
 * @param[out] ch1 : Voltage measurement from channel 1 in millivolts.
 * @param[out] ch2 : Voltage measurement from channel 2 in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc7_read_voltage ( isoadc7_t *ctx, float *ch0, float *ch1, float *ch2 );

#ifdef __cplusplus
}
#endif
#endif // ISOADC7_H

/*! @} */ // isoadc7

// ------------------------------------------------------------------------ END

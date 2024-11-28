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
 * @file piezoaccel250g.h
 * @brief This file contains API for Piezo Accel 2 50g Click Driver.
 */

#ifndef PIEZOACCEL250G_H
#define PIEZOACCEL250G_H

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
 * @addtogroup piezoaccel250g Piezo Accel 2 50g Click Driver
 * @brief API for configuring and manipulating Piezo Accel 2 50g Click driver.
 * @{
 */
 
/**
 * @defgroup piezoaccel250g_cmd Piezo Accel 2 50g Fast Commands List
 * @brief List of fast commands of Piezo Accel 2 50g Click driver.
 */

/**
 * @addtogroup piezoaccel250g_cmd
 * @{
 */

/**
 * @brief Piezo Accel 2 50g fast commands.
 * @details Specified fast commands of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_FAST_CMD_ADC_START          0x0A
#define PIEZOACCEL250G_FAST_CMD_ADC_STANDBY        0x0B
#define PIEZOACCEL250G_FAST_CMD_ADC_SHUTDOWN       0x0C
#define PIEZOACCEL250G_FAST_CMD_FULL_SHUTDOWN      0x0D
#define PIEZOACCEL250G_FAST_CMD_FULL_RESET         0x0E

/*! @} */ // piezoaccel250g_cmd

/**
 * @defgroup piezoaccel250g_reg Piezo Accel 2 50g Registers List
 * @brief List of registers of Piezo Accel 2 50g Click driver.
 */

/**
 * @addtogroup piezoaccel250g_reg
 * @{
 */

/**
 * @brief Piezo Accel 2 50g registers list.
 * @details Specified registers list of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_REG_ADCDATA                 0x00
#define PIEZOACCEL250G_REG_CONFIG0                 0x01
#define PIEZOACCEL250G_REG_CONFIG1                 0x02
#define PIEZOACCEL250G_REG_CONFIG2                 0x03
#define PIEZOACCEL250G_REG_CONFIG3                 0x04
#define PIEZOACCEL250G_REG_IRQ                     0x05
#define PIEZOACCEL250G_REG_MUX                     0x06
#define PIEZOACCEL250G_REG_SCAN                    0x07
#define PIEZOACCEL250G_REG_TIMER                   0x08
#define PIEZOACCEL250G_REG_OFFSETCAL               0x09
#define PIEZOACCEL250G_REG_GAINCAL                 0x0A
#define PIEZOACCEL250G_REG_LOCK                    0x0D
#define PIEZOACCEL250G_REG_CRCCFG                  0x0F

/*! @} */ // piezoaccel250g_reg

/**
 * @defgroup piezoaccel250g_set Piezo Accel 2 50g Registers Settings
 * @brief Settings for registers of Piezo Accel 2 50g Click driver.
 */

/**
 * @addtogroup piezoaccel250g_set
 * @{
 */

/**
 * @brief Piezo Accel 2 50g CONFIG0 register setting.
 * @details Specified setting for CONFIG0 register of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_CONFIG0_VREF_SEL_INT_2_4_V  0x80
#define PIEZOACCEL250G_CONFIG0_VREF_SEL_EXT        0x00
#define PIEZOACCEL250G_CONFIG0_VREF_SEL_MASK       0x80
#define PIEZOACCEL250G_CONFIG0_EXIT_PART_SHUTDOWN  0x40
#define PIEZOACCEL250G_CONFIG0_CLK_SEL_INT_CLKOUT  0x30
#define PIEZOACCEL250G_CONFIG0_CLK_SEL_INT         0x20
#define PIEZOACCEL250G_CONFIG0_CLK_SEL_EXT         0x00
#define PIEZOACCEL250G_CONFIG0_CLK_SEL_MASK        0x30
#define PIEZOACCEL250G_CONFIG0_CS_SEL_15_UA        0x0C
#define PIEZOACCEL250G_CONFIG0_CS_SEL_3_7_UA       0x08
#define PIEZOACCEL250G_CONFIG0_CS_SEL_0_9_UA       0x04
#define PIEZOACCEL250G_CONFIG0_CS_SEL_NO_IN_CURR   0x00
#define PIEZOACCEL250G_CONFIG0_CS_SEL_MASK         0x0C
#define PIEZOACCEL250G_CONFIG0_ADC_MODE_CONVERSION 0x03
#define PIEZOACCEL250G_CONFIG0_ADC_MODE_STANDBY    0x02
#define PIEZOACCEL250G_CONFIG0_ADC_MODE_SHUTDOWN   0x00
#define PIEZOACCEL250G_CONFIG0_ADC_MODE_MASK       0x03

/**
 * @brief Piezo Accel 2 50g CONFIG1 register setting.
 * @details Specified setting for CONFIG1 register of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_CONFIG1_PRE_DIV_8           0xC0
#define PIEZOACCEL250G_CONFIG1_PRE_DIV_4           0x80
#define PIEZOACCEL250G_CONFIG1_PRE_DIV_2           0x40
#define PIEZOACCEL250G_CONFIG1_PRE_DIV_1           0x00
#define PIEZOACCEL250G_CONFIG1_PRE_MASK            0xC0
#define PIEZOACCEL250G_CONFIG1_OSR_98304           0x3C
#define PIEZOACCEL250G_CONFIG1_OSR_81920           0x38
#define PIEZOACCEL250G_CONFIG1_OSR_49152           0x34
#define PIEZOACCEL250G_CONFIG1_OSR_40960           0x30
#define PIEZOACCEL250G_CONFIG1_OSR_24576           0x2C
#define PIEZOACCEL250G_CONFIG1_OSR_20480           0x28
#define PIEZOACCEL250G_CONFIG1_OSR_16384           0x24
#define PIEZOACCEL250G_CONFIG1_OSR_8192            0x20
#define PIEZOACCEL250G_CONFIG1_OSR_4096            0x1C
#define PIEZOACCEL250G_CONFIG1_OSR_2048            0x18
#define PIEZOACCEL250G_CONFIG1_OSR_1024            0x14
#define PIEZOACCEL250G_CONFIG1_OSR_512             0x10
#define PIEZOACCEL250G_CONFIG1_OSR_256             0x0C
#define PIEZOACCEL250G_CONFIG1_OSR_128             0x08
#define PIEZOACCEL250G_CONFIG1_OSR_64              0x04
#define PIEZOACCEL250G_CONFIG1_OSR_32              0x00
#define PIEZOACCEL250G_CONFIG1_OSR_MASK            0x3C

/**
 * @brief Piezo Accel 2 50g CONFIG2 register setting.
 * @details Specified setting for CONFIG2 register of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_CONFIG2_BOOST_X2            0xC0
#define PIEZOACCEL250G_CONFIG2_BOOST_X1            0x80
#define PIEZOACCEL250G_CONFIG2_BOOST_X0_66         0x40
#define PIEZOACCEL250G_CONFIG2_BOOST_X0_5          0x00
#define PIEZOACCEL250G_CONFIG2_BOOST_MASK          0xC0
#define PIEZOACCEL250G_CONFIG2_GAIN_X64            0x38
#define PIEZOACCEL250G_CONFIG2_GAIN_X32            0x30
#define PIEZOACCEL250G_CONFIG2_GAIN_X16            0x28
#define PIEZOACCEL250G_CONFIG2_GAIN_X8             0x20
#define PIEZOACCEL250G_CONFIG2_GAIN_X4             0x18
#define PIEZOACCEL250G_CONFIG2_GAIN_X2             0x10
#define PIEZOACCEL250G_CONFIG2_GAIN_X1             0x08
#define PIEZOACCEL250G_CONFIG2_GAIN_X1_PER_3       0x00
#define PIEZOACCEL250G_CONFIG2_GAIN_MASK           0x38
#define PIEZOACCEL250G_CONFIG2_AZ_MUX_EN           0x04
#define PIEZOACCEL250G_CONFIG2_AZ_REF_EN           0x02
#define PIEZOACCEL250G_CONFIG2_RESERVED            0x01

/**
 * @brief Piezo Accel 2 50g CONFIG3 register setting.
 * @details Specified setting for CONFIG3 register of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_CONFIG3_CONV_MODE_CONT      0xC0
#define PIEZOACCEL250G_CONFIG3_CONV_MODE_ONES_STB  0x80
#define PIEZOACCEL250G_CONFIG3_CONV_MODE_ONES_SHD  0x00
#define PIEZOACCEL250G_CONFIG3_CONV_MODE_MASK      0xC0
#define PIEZOACCEL250G_CONFIG3_DATA_FMT_32B_R_CHID 0x30
#define PIEZOACCEL250G_CONFIG3_DATA_FMT_32B_R      0x20
#define PIEZOACCEL250G_CONFIG3_DATA_FMT_32B_L      0x10
#define PIEZOACCEL250G_CONFIG3_DATA_FMT_24B        0x00
#define PIEZOACCEL250G_CONFIG3_DATA_FMT_MASK       0x30
#define PIEZOACCEL250G_CONFIG3_CRC_FMT_32B         0x08
#define PIEZOACCEL250G_CONFIG3_CRC_FMT_16B         0x00
#define PIEZOACCEL250G_CONFIG3_CRC_FMT_MASK        0x08
#define PIEZOACCEL250G_CONFIG3_EN_CRCCOM           0x04
#define PIEZOACCEL250G_CONFIG3_EN_OFFCAL           0x02
#define PIEZOACCEL250G_CONFIG3_EN_GAINCAL          0x01

/**
 * @brief Piezo Accel 2 50g IRQ register setting.
 * @details Specified setting for IRQ register of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_IRQ_DR_STATUS               0x40
#define PIEZOACCEL250G_IRQ_CRCCFG_STATUS           0x20
#define PIEZOACCEL250G_IRQ_POR_STATUS              0x10
#define PIEZOACCEL250G_IRQ_MODE1_MDAT              0x08
#define PIEZOACCEL250G_IRQ_MODE1_IRQOUT            0x00
#define PIEZOACCEL250G_IRQ_MODE1_MASK              0x08
#define PIEZOACCEL250G_IRQ_MODE0_INACT_HIGH        0x04
#define PIEZOACCEL250G_IRQ_MODE0_INACT_HIGH_Z      0x00
#define PIEZOACCEL250G_IRQ_MODE0_MASK              0x04
#define PIEZOACCEL250G_IRQ_EN_FAST_CMD             0x02
#define PIEZOACCEL250G_IRQ_EN_STP                  0x01

/**
 * @brief Piezo Accel 2 50g SCAN register setting.
 * @details Specified setting for SCAN register of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_SCAN_DLY_512_DMCLK          0xE00000ul
#define PIEZOACCEL250G_SCAN_DLY_256_DMCLK          0xC00000ul
#define PIEZOACCEL250G_SCAN_DLY_128_DMCL           0xA00000ul
#define PIEZOACCEL250G_SCAN_DLY_64_DMCLK           0x800000ul
#define PIEZOACCEL250G_SCAN_DLY_32_DMCLK           0x600000ul
#define PIEZOACCEL250G_SCAN_DLY_16_DMCLK           0x400000ul
#define PIEZOACCEL250G_SCAN_DLY_8_DMCLK            0x200000ul
#define PIEZOACCEL250G_SCAN_DLY_NO_DELAY           0x000000ul
#define PIEZOACCEL250G_SCAN_DLY_MASK               0xE00000ul
#define PIEZOACCEL250G_SCAN_CH_OFFSET              0x008000ul
#define PIEZOACCEL250G_SCAN_CH_VCM                 0x004000ul
#define PIEZOACCEL250G_SCAN_CH_AVDD                0x002000ul
#define PIEZOACCEL250G_SCAN_CH_TEMP                0x001000ul
#define PIEZOACCEL250G_SCAN_CH_DIFF_CH2_CH3        0x000200ul
#define PIEZOACCEL250G_SCAN_CH_DIFF_CH0_CH1        0x000100ul
#define PIEZOACCEL250G_SCAN_CH_SINGLE_ENDED_CH3    0x000008ul
#define PIEZOACCEL250G_SCAN_CH_SINGLE_ENDED_CH2    0x000004ul
#define PIEZOACCEL250G_SCAN_CH_SINGLE_ENDED_CH1    0x000002ul
#define PIEZOACCEL250G_SCAN_CH_SINGLE_ENDED_CH0    0x000001ul

/**
 * @brief Piezo Accel 2 50g status byte setting.
 * @details Specified setting for status byte of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_STATUS_DEV_ADDR_MASK        0x30
#define PIEZOACCEL250G_STATUS_DEV_ADDR_FLAG        0x08
#define PIEZOACCEL250G_STATUS_DR_FLAG              0x04
#define PIEZOACCEL250G_STATUS_CRCCFG_FLAG          0x02
#define PIEZOACCEL250G_STATUS_POR_FLAG             0x01

/**
 * @brief Piezo Accel 2 50g command type setting.
 * @details Specified setting for command byte of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_CMD_TYPE_FAST_CMD           0x00
#define PIEZOACCEL250G_CMD_TYPE_STATIC_REG_READ    0x01
#define PIEZOACCEL250G_CMD_TYPE_INC_REG_WRITE      0x02
#define PIEZOACCEL250G_CMD_TYPE_INC_REG_READ       0x03

/**
 * @brief Piezo Accel 2 50g device address setting.
 * @details Specified setting for device address of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_CMD_DEV_ADDR                0x01

/**
 * @brief Piezo Accel 2 50g lock setting.
 * @details Specified setting for lock of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_LOCK_BYTE                   0x00
#define PIEZOACCEL250G_UNLOCK_BYTE                 0xA5

/**
 * @brief Piezo Accel 2 50g data ready timeout setting.
 * @details Specified setting for data ready timeout of Piezo Accel 2 50g Click driver.
 */
#define PIEZOACCEL250G_DATA_READY_TIMEOUT_MS       1000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b piezoaccel250g_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PIEZOACCEL250G_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define PIEZOACCEL250G_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // piezoaccel250g_set

/**
 * @defgroup piezoaccel250g_map Piezo Accel 2 50g MikroBUS Map
 * @brief MikroBUS pin mapping of Piezo Accel 2 50g Click driver.
 */

/**
 * @addtogroup piezoaccel250g_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Piezo Accel 2 50g Click to the selected MikroBUS.
 */
#define PIEZOACCEL250G_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // piezoaccel250g_map
/*! @} */ // piezoaccel250g

/**
 * @brief Piezo Accel 2 50g Click adc data object.
 * @details ADC data object definition of Piezo Accel 2 50g Click driver.
 */
typedef struct
{
    uint32_t raw_x;             /**< RAW ADC value of X axis. */
    uint32_t raw_y;             /**< RAW ADC value of Y axis. */
    uint32_t raw_z;             /**< RAW ADC value of Z axis. */
    uint32_t raw_temp;          /**< RAW ADC value of temperature measurement. */

} piezoaccel250g_adc_data_t;

/**
 * @brief Piezo Accel 2 50g Click context object.
 * @details Context object definition of Piezo Accel 2 50g Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t clk;           /**< AMCLK pin. */
    digital_in_t irq;           /**< IRQ pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t      status;        /**< Status byte of the last command write/read. */

} piezoaccel250g_t;

/**
 * @brief Piezo Accel 2 50g Click configuration object.
 * @details Configuration object definition of Piezo Accel 2 50g Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t clk;             /**< AMCLK pin. */
    pin_name_t irq;             /**< IRQ pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} piezoaccel250g_cfg_t;

/**
 * @brief Piezo Accel 2 50g Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PIEZOACCEL250G_OK = 0,
    PIEZOACCEL250G_ERROR = -1

} piezoaccel250g_return_value_t;

/*!
 * @addtogroup piezoaccel250g Piezo Accel 2 50g Click Driver
 * @brief API for configuring and manipulating Piezo Accel 2 50g Click driver.
 * @{
 */

/**
 * @brief Piezo Accel 2 50g configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #piezoaccel250g_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void piezoaccel250g_cfg_setup ( piezoaccel250g_cfg_t *cfg );

/**
 * @brief Piezo Accel 2 50g initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #piezoaccel250g_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_init ( piezoaccel250g_t *ctx, piezoaccel250g_cfg_t *cfg );

/**
 * @brief Piezo Accel 2 50g default configuration function.
 * @details This function executes a default configuration of Piezo Accel 2 50g
 * Click board.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t piezoaccel250g_default_cfg ( piezoaccel250g_t *ctx );

/**
 * @brief Piezo Accel 2 50g fast cmd write function.
 * @details This function writes the selected fast command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] fast_cmd : Fast command to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_fast_cmd_write ( piezoaccel250g_t *ctx, uint8_t fast_cmd );

/**
 * @brief Piezo Accel 2 50g reg write multi function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_write_multi ( piezoaccel250g_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Piezo Accel 2 50g reg write 8 function.
 * @details This function writes 8-bit data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 8-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_write_8 ( piezoaccel250g_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Piezo Accel 2 50g reg write 24 function.
 * @details This function writes 24-bit data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 24-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_write_24 ( piezoaccel250g_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Piezo Accel 2 50g reg read multi function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_read_multi ( piezoaccel250g_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Piezo Accel 2 50g reg read 8 function.
 * @details This function reads 8-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 8-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_read_8 ( piezoaccel250g_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Piezo Accel 2 50g reg read 24 function.
 * @details This function reads 24-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 24-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_read_24 ( piezoaccel250g_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Piezo Accel 2 50g reg read 32 function.
 * @details This function reads 32-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 32-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_reg_read_32 ( piezoaccel250g_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Piezo Accel 2 50g unlock reg write function.
 * @details This function unlocks writing to registers.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_unlock_reg_write ( piezoaccel250g_t *ctx );

/**
 * @brief Piezo Accel 2 50g lock reg write function.
 * @details This function locks writing to registers.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_lock_reg_write ( piezoaccel250g_t *ctx );

/**
 * @brief Piezo Accel 2 50g get clk pin function.
 * @details This function returns the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t piezoaccel250g_get_clk_pin ( piezoaccel250g_t *ctx );

/**
 * @brief Piezo Accel 2 50g get irq pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t piezoaccel250g_get_irq_pin ( piezoaccel250g_t *ctx );

/**
 * @brief Piezo Accel 2 50g wait data ready function.
 * @details This function waits a desired period for a data ready indication.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] timeout_ms : Waiting timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_wait_data_ready ( piezoaccel250g_t *ctx, uint16_t timeout_ms );

/**
 * @brief Piezo Accel 2 50g read adc data function.
 * @details This function reads raw ADC values of X, Y, and Z axis, and the internal 
 * temperature sensor measurements.
 * @param[in] ctx : Click context object.
 * See #piezoaccel250g_t object definition for detailed explanation.
 * @param[in] data_out : RAW ADC data read.
 * See #piezoaccel250g_adc_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezoaccel250g_read_adc_data ( piezoaccel250g_t *ctx, piezoaccel250g_adc_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // PIEZOACCEL250G_H

/*! @} */ // piezoaccel250g

// ------------------------------------------------------------------------ END

/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file mcurrentsens.h
 * @brief This file contains API for mCurrent Sens Click Driver.
 */

#ifndef MCURRENTSENS_H
#define MCURRENTSENS_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup mcurrentsens mCurrent Sens Click Driver
 * @brief API for configuring and manipulating mCurrent Sens Click driver.
 * @{
 */

/**
 * @defgroup mcurrentsens_reg mCurrent Sens Registers List
 * @brief List of registers of mCurrent Sens Click driver.
 */

/**
 * @addtogroup mcurrentsens_reg
 * @{
 */

/**
 * @brief mCurrent Sens register map.
 * @details Specified register map of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_REG_ADCDATA                        0x00
#define MCURRENTSENS_REG_CONFIG0                        0x01
#define MCURRENTSENS_REG_CONFIG1                        0x02
#define MCURRENTSENS_REG_CONFIG2                        0x03
#define MCURRENTSENS_REG_CONFIG3                        0x04
#define MCURRENTSENS_REG_IRQ                            0x05
#define MCURRENTSENS_REG_MUX                            0x06
#define MCURRENTSENS_REG_SCAN                           0x07
#define MCURRENTSENS_REG_TIMER                          0x08
#define MCURRENTSENS_REG_OFFSETCAL                      0x09
#define MCURRENTSENS_REG_GAINCAL                        0x0A
#define MCURRENTSENS_REG_RESERVED_24                    0x0B
#define MCURRENTSENS_REG_RESERVED_8                     0x0C
#define MCURRENTSENS_REG_LOCK                           0x0D
#define MCURRENTSENS_REG_RESERVED_16                    0x0E
#define MCURRENTSENS_REG_CRCCFG                         0x0F

/**
 * @brief mCurrent Sens SPI command setting.
 * @details Specified SPI command setting of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_CMD_DEV_ADDR                       0x40
#define MCURRENTSENS_CMD_DEV_ADDR_MASK                  0xC0
#define MCURRENTSENS_CMD_REG_ADDR_SHIFT                 2
#define MCURRENTSENS_CMD_REG_ADDR_MASK                  0x3C
#define MCURRENTSENS_CMD_TYPE_STATIC_READ               0x01
#define MCURRENTSENS_CMD_TYPE_INC_WRITE                 0x02
#define MCURRENTSENS_CMD_TYPE_INC_READ                  0x03
#define MCURRENTSENS_CMD_TYPE_MASK                      0x03
#define MCURRENTSENS_FAST_CMD_CONV_START                ( 0x28 | MCURRENTSENS_CMD_DEV_ADDR )
#define MCURRENTSENS_FAST_CMD_STANDBY                   ( 0x2C | MCURRENTSENS_CMD_DEV_ADDR )
#define MCURRENTSENS_FAST_CMD_SHUTDOWN                  ( 0x30 | MCURRENTSENS_CMD_DEV_ADDR )
#define MCURRENTSENS_FAST_CMD_FULL_SHUTDOWN             ( 0x34 | MCURRENTSENS_CMD_DEV_ADDR )
#define MCURRENTSENS_FAST_CMD_FULL_RESET                ( 0x38 | MCURRENTSENS_CMD_DEV_ADDR )

/*! @} */ // mcurrentsens_reg

/**
 * @defgroup mcurrentsens_set mCurrent Sens Registers Settings
 * @brief Settings for registers of mCurrent Sens Click driver.
 */

/**
 * @addtogroup mcurrentsens_set
 * @{
 */

/**
 * @brief mCurrent Sens CONFIG0 register setting.
 * @details Specified setting for CONFIG0 register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_CONFIG0_VREF_SEL_EXT               0x00
#define MCURRENTSENS_CONFIG0_VREF_SEL_INT               0x80
#define MCURRENTSENS_CONFIG0_VREF_SEL_MASK              0x80
#define MCURRENTSENS_CONFIG0_PARTIAL_SHUTDOWN_EN        0x00
#define MCURRENTSENS_CONFIG0_PARTIAL_SHUTDOWN_DIS       0x40
#define MCURRENTSENS_CONFIG0_PARTIAL_SHUTDOWN_MASK      0x40
#define MCURRENTSENS_CONFIG0_CLK_SEL_EXT                0x00
#define MCURRENTSENS_CONFIG0_CLK_SEL_INT_NO_OUT         0x20
#define MCURRENTSENS_CONFIG0_CLK_SEL_INT_OUT            0x30
#define MCURRENTSENS_CONFIG0_CLK_SEL_MASK               0x30
#define MCURRENTSENS_CONFIG0_CS_SEL_NONE                0x00
#define MCURRENTSENS_CONFIG0_CS_SEL_0P9UA               0x04
#define MCURRENTSENS_CONFIG0_CS_SEL_3P7UA               0x08
#define MCURRENTSENS_CONFIG0_CS_SEL_15UA                0x0C
#define MCURRENTSENS_CONFIG0_CS_SEL_MASK                0x0C
#define MCURRENTSENS_CONFIG0_ADC_MODE_SHUTDOWN          0x00
#define MCURRENTSENS_CONFIG0_ADC_MODE_STANDBY           0x02
#define MCURRENTSENS_CONFIG0_ADC_MODE_CONVERSION        0x03
#define MCURRENTSENS_CONFIG0_ADC_MODE_MASK              0x03

/**
 * @brief mCurrent Sens CONFIG1 register setting.
 * @details Specified setting for CONFIG1 register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_CONFIG1_PRE_DIV_1                  0x00
#define MCURRENTSENS_CONFIG1_PRE_DIV_2                  0x40
#define MCURRENTSENS_CONFIG1_PRE_DIV_4                  0x80
#define MCURRENTSENS_CONFIG1_PRE_DIV_8                  0xC0
#define MCURRENTSENS_CONFIG1_PRE_DIV_MASK               0xC0
#define MCURRENTSENS_CONFIG1_OSR_32                     0x00
#define MCURRENTSENS_CONFIG1_OSR_64                     0x04
#define MCURRENTSENS_CONFIG1_OSR_128                    0x08
#define MCURRENTSENS_CONFIG1_OSR_256                    0x0C
#define MCURRENTSENS_CONFIG1_OSR_512                    0x10
#define MCURRENTSENS_CONFIG1_OSR_1024                   0x14
#define MCURRENTSENS_CONFIG1_OSR_2048                   0x18
#define MCURRENTSENS_CONFIG1_OSR_4096                   0x1C
#define MCURRENTSENS_CONFIG1_OSR_8192                   0x20
#define MCURRENTSENS_CONFIG1_OSR_16384                  0x24
#define MCURRENTSENS_CONFIG1_OSR_20480                  0x28
#define MCURRENTSENS_CONFIG1_OSR_24576                  0x2C
#define MCURRENTSENS_CONFIG1_OSR_40960                  0x30
#define MCURRENTSENS_CONFIG1_OSR_49152                  0x34
#define MCURRENTSENS_CONFIG1_OSR_81920                  0x38
#define MCURRENTSENS_CONFIG1_OSR_98304                  0x3C
#define MCURRENTSENS_CONFIG1_OSR_MASK                   0x3C

/**
 * @brief mCurrent Sens CONFIG2 register setting.
 * @details Specified setting for CONFIG2 register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_CONFIG2_BOOST_X0P5                 0x00
#define MCURRENTSENS_CONFIG2_BOOST_X0P66                0x40
#define MCURRENTSENS_CONFIG2_BOOST_X1                   0x80
#define MCURRENTSENS_CONFIG2_BOOST_X2                   0xC0
#define MCURRENTSENS_CONFIG2_BOOST_MASK                 0xC0
#define MCURRENTSENS_CONFIG2_GAIN_X0P33                 0x00
#define MCURRENTSENS_CONFIG2_GAIN_X1                    0x08
#define MCURRENTSENS_CONFIG2_GAIN_X2                    0x10
#define MCURRENTSENS_CONFIG2_GAIN_X4                    0x18
#define MCURRENTSENS_CONFIG2_GAIN_X8                    0x20
#define MCURRENTSENS_CONFIG2_GAIN_X16                   0x28
#define MCURRENTSENS_CONFIG2_GAIN_X32                   0x30
#define MCURRENTSENS_CONFIG2_GAIN_X64                   0x38
#define MCURRENTSENS_CONFIG2_GAIN_MASK                  0x38
#define MCURRENTSENS_CONFIG2_AZ_MUX_DIS                 0x00
#define MCURRENTSENS_CONFIG2_AZ_MUX_EN                  0x04
#define MCURRENTSENS_CONFIG2_AZ_MUX_MASK                0x04
#define MCURRENTSENS_CONFIG2_AZ_REF_DIS                 0x00
#define MCURRENTSENS_CONFIG2_AZ_REF_EN                  0x02
#define MCURRENTSENS_CONFIG2_AZ_REF_MASK                0x02
#define MCURRENTSENS_CONFIG2_RESERVED                   0x01

/**
 * @brief mCurrent Sens CONFIG3 register setting.
 * @details Specified setting for CONFIG3 register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_CONFIG3_CONV_MODE_ONE_SHOT_SHUT    0x00
#define MCURRENTSENS_CONFIG3_CONV_MODE_ONE_SHOT_STBY    0x80
#define MCURRENTSENS_CONFIG3_CONV_MODE_CONTINUOUS       0xC0
#define MCURRENTSENS_CONFIG3_CONV_MODE_MASK             0xC0
#define MCURRENTSENS_CONFIG3_DATA_FORMAT_24BIT          0x00
#define MCURRENTSENS_CONFIG3_DATA_FORMAT_32BIT_LEFT     0x10
#define MCURRENTSENS_CONFIG3_DATA_FORMAT_32BIT_RIGHT    0x20
#define MCURRENTSENS_CONFIG3_DATA_FORMAT_32BIT_CHID     0x30
#define MCURRENTSENS_CONFIG3_DATA_FORMAT_MASK           0x30
#define MCURRENTSENS_CONFIG3_CRC_FORMAT_16BIT           0x00
#define MCURRENTSENS_CONFIG3_CRC_FORMAT_32BIT           0x08
#define MCURRENTSENS_CONFIG3_CRC_FORMAT_MASK            0x08
#define MCURRENTSENS_CONFIG3_EN_CRCCOM_DIS              0x00
#define MCURRENTSENS_CONFIG3_EN_CRCCOM_EN               0x04
#define MCURRENTSENS_CONFIG3_EN_CRCCOM_MASK             0x04
#define MCURRENTSENS_CONFIG3_EN_OFFCAL_DIS              0x00
#define MCURRENTSENS_CONFIG3_EN_OFFCAL_EN               0x02
#define MCURRENTSENS_CONFIG3_EN_OFFCAL_MASK             0x02
#define MCURRENTSENS_CONFIG3_EN_GAINCAL_DIS             0x00
#define MCURRENTSENS_CONFIG3_EN_GAINCAL_EN              0x01
#define MCURRENTSENS_CONFIG3_EN_GAINCAL_MASK            0x01

/**
 * @brief mCurrent Sens IRQ register setting.
 * @details Specified setting for IRQ register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_IRQ_DR_STATUS                      0x40
#define MCURRENTSENS_IRQ_CRCCFG_STATUS                  0x20
#define MCURRENTSENS_IRQ_POR_STATUS                     0x10
#define MCURRENTSENS_IRQ_MODE_IRQ_HIGH_Z                0x00
#define MCURRENTSENS_IRQ_MODE_IRQ_LOGIC_HIGH            0x04
#define MCURRENTSENS_IRQ_MODE_MDAT_HIGH_Z               0x08
#define MCURRENTSENS_IRQ_MODE_MDAT_LOGIC_HIGH           0x0C
#define MCURRENTSENS_IRQ_MODE_MASK                      0x0C
#define MCURRENTSENS_IRQ_EN_FASTCMD_DIS                 0x00
#define MCURRENTSENS_IRQ_EN_FASTCMD_EN                  0x02
#define MCURRENTSENS_IRQ_EN_FASTCMD_MASK                0x02
#define MCURRENTSENS_IRQ_EN_STP_DIS                     0x00
#define MCURRENTSENS_IRQ_EN_STP_EN                      0x01
#define MCURRENTSENS_IRQ_EN_STP_MASK                    0x01

/**
 * @brief mCurrent Sens MUX register setting.
 * @details Specified setting for MUX register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_MUX_VIN_P_SHIFT                    4
#define MCURRENTSENS_MUX_VIN_P_MASK                     0xF0
#define MCURRENTSENS_MUX_VIN_N_SHIFT                    0
#define MCURRENTSENS_MUX_VIN_N_MASK                     0x0F
#define MCURRENTSENS_MUX_CH0                            0x00
#define MCURRENTSENS_MUX_CH1                            0x01
#define MCURRENTSENS_MUX_CH2                            0x02
#define MCURRENTSENS_MUX_CH3                            0x03
#define MCURRENTSENS_MUX_CH4                            0x04
#define MCURRENTSENS_MUX_CH5                            0x05
#define MCURRENTSENS_MUX_CH6                            0x06
#define MCURRENTSENS_MUX_CH7                            0x07
#define MCURRENTSENS_MUX_AGND                           0x08
#define MCURRENTSENS_MUX_AVDD                           0x09
#define MCURRENTSENS_MUX_RESERVED                       0x0A
#define MCURRENTSENS_MUX_REFIN_OUT                      0x0B
#define MCURRENTSENS_MUX_REFIN_IN                       0x0C
#define MCURRENTSENS_MUX_TEMP_P                         0x0D
#define MCURRENTSENS_MUX_TEMP_M                         0x0E
#define MCURRENTSENS_MUX_VCM                            0x0F

/**
 * @brief mCurrent Sens board channel mapping.
 * @details Specified board channel mapping of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_MUX_CH1_CURRENT_P                  MCURRENTSENS_MUX_CH0
#define MCURRENTSENS_MUX_CH1_CURRENT_N                  MCURRENTSENS_MUX_CH1
#define MCURRENTSENS_MUX_CH1_VOLTAGE_P                  MCURRENTSENS_MUX_CH2
#define MCURRENTSENS_MUX_CH1_VOLTAGE_N                  MCURRENTSENS_MUX_CH3
#define MCURRENTSENS_MUX_CH2_VOLTAGE_P                  MCURRENTSENS_MUX_CH4
#define MCURRENTSENS_MUX_CH2_VOLTAGE_N                  MCURRENTSENS_MUX_CH5
#define MCURRENTSENS_MUX_CH2_CURRENT_P                  MCURRENTSENS_MUX_CH6
#define MCURRENTSENS_MUX_CH2_CURRENT_N                  MCURRENTSENS_MUX_CH7

/**
 * @brief mCurrent Sens reserved register setting.
 * @details Specified reserved register setting of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_RESERVED_24_DEFAULT                0x900000ul
#define MCURRENTSENS_RESERVED_8_DEFAULT                 0x30
#define MCURRENTSENS_RESERVED_16_DEFAULT                0x000F

/**
 * @brief mCurrent Sens calibration register setting.
 * @details Specified calibration register setting of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_OFFSETCAL_DEFAULT                  0x000000ul
#define MCURRENTSENS_GAINCAL_DEFAULT                    0x800000ul

/**
 * @brief mCurrent Sens LOCK register setting.
 * @details Specified setting for LOCK register of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_LOCK_UNLOCK                        0xA5
#define MCURRENTSENS_LOCK_LOCK                          0x00

/**
 * @brief mCurrent Sens board coefficient setting.
 * @details Specified board coefficient setting of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_CH1_GAIN_OPAMP                     50.0f
#define MCURRENTSENS_CH1_R5_RSHUNT                      0.05f
#define MCURRENTSENS_CH1_CURRENT_COEFF                 ( MCURRENTSENS_CH1_GAIN_OPAMP * MCURRENTSENS_CH1_R5_RSHUNT )
#define MCURRENTSENS_CH2_GAIN_OPAMP                     50.0f
#define MCURRENTSENS_CH2_R8_RSHUNT                      0.05f
#define MCURRENTSENS_CH2_CURRENT_COEFF                 ( MCURRENTSENS_CH2_GAIN_OPAMP * MCURRENTSENS_CH2_R8_RSHUNT )
#define MCURRENTSENS_CH1_GAIN                           1.0f
#define MCURRENTSENS_CH1_R16_TOP                        1000.0f
#define MCURRENTSENS_CH1_R21_BOTTOM                     38.3f
#define MCURRENTSENS_CH1_VOLTAGE_COEFF                 ( MCURRENTSENS_CH1_GAIN * \
                                                         ( MCURRENTSENS_CH1_R21_BOTTOM / \
                                                           ( MCURRENTSENS_CH1_R16_TOP + MCURRENTSENS_CH1_R21_BOTTOM ) ) )
#define MCURRENTSENS_CH2_GAIN                           0.5f
#define MCURRENTSENS_CH2_R15_TOP                        1000.0f
#define MCURRENTSENS_CH2_R17_BOTTOM                     38.3f
#define MCURRENTSENS_CH2_VOLTAGE_COEFF                 ( MCURRENTSENS_CH2_GAIN * \
                                                         ( MCURRENTSENS_CH2_R17_BOTTOM / \
                                                           ( MCURRENTSENS_CH2_R15_TOP + MCURRENTSENS_CH2_R17_BOTTOM ) ) )
#define MCURRENTSENS_TEMPERATURE_OFFSET                 80.0f
#define MCURRENTSENS_TEMPERATURE_COEFF                  0.2973f
#define MCURRENTSENS_VREF_INTERNAL                      2.4f
#define MCURRENTSENS_V_TO_MV                            1000.0f
#define MCURRENTSENS_GAIN_ADC                           1.0f
#define MCURRENTSENS_ADC_FS_CODE                        8388608.0f
#define MCURRENTSENS_SAMPLE_COUNT                       50
#define MCURRENTSENS_DATA_READY_TIMEOUT_MS              200
#define MCURRENTSENS_CURRENT_TARGET_0_MA                0.0f
#define MCURRENTSENS_CURRENT_TARGET_10_MA               10.0f
#define MCURRENTSENS_VOLTAGE_TARGET_0_MV                0.0f
#define MCURRENTSENS_VOLTAGE_TARGET_3000_MV             3000.0f

/**
 * @brief mCurrent Sens memory size setting.
 * @details Specified setting for memory size of mCurrent Sens Click driver.
 */
#define MCURRENTSENS_EEPROM_ADDR_START                  0x00
#define MCURRENTSENS_EEPROM_ADDR_END                    0xFF
#define MCURRENTSENS_EEPROM_PAGE_SIZE                   16

/**
 * @brief mCurrent Sens device address setting.
 * @details Specified setting for device slave address selection of
 * mCurrent Sens Click driver.
 */
#define MCURRENTSENS_DEVICE_ADDRESS                     0x57
#define MCURRENTSENS_DEVICE_ADDRESS_WP                  0x37

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mcurrentsens_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MCURRENTSENS_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define MCURRENTSENS_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mcurrentsens_set

/**
 * @defgroup mcurrentsens_map mCurrent Sens MikroBUS Map
 * @brief MikroBUS pin mapping of mCurrent Sens Click driver.
 */

/**
 * @addtogroup mcurrentsens_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of mCurrent Sens Click to the selected MikroBUS.
 */
#define MCURRENTSENS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.clk  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // mcurrentsens_map
/*! @} */ // mcurrentsens

/**
 * @brief mCurrent Sens calibration data structure.
 * @details Specified calibration data structure of mCurrent Sens Click driver.
 */
typedef struct
{
    int32_t offset_cal;
    uint32_t gain_cal;

} mcurrentsens_calib_t;

/**
 * @brief mCurrent Sens Click context object.
 * @details Context object definition of mCurrent Sens Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t clk;           /**< 4.9152MHz master clock pin. */
    digital_in_t irq;           /**< Interrupt pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    mcurrentsens_calib_t ch1_curr_cal;  /**< Channel 1 current calibration values. */
    mcurrentsens_calib_t ch1_volt_cal;  /**< Channel 1 voltage calibration values. */
    mcurrentsens_calib_t ch2_curr_cal;  /**< Channel 2 current calibration values. */
    mcurrentsens_calib_t ch2_volt_cal;  /**< Channel 2 voltage calibration values. */
    bool calibrated;            /**< Device calibrated flag. */

} mcurrentsens_t;

/**
 * @brief mCurrent Sens Click configuration object.
 * @details Configuration object definition of mCurrent Sens Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t clk;             /**< 4.9152MHz master clock pin. */
    pin_name_t irq;             /**< Interrupt pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} mcurrentsens_cfg_t;

/**
 * @brief mCurrent Sens Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MCURRENTSENS_OK = 0,
    MCURRENTSENS_ERROR = -1

} mcurrentsens_return_value_t;

/*!
 * @addtogroup mcurrentsens mCurrent Sens Click Driver
 * @brief API for configuring and manipulating mCurrent Sens Click driver.
 * @{
 */

/**
 * @brief mCurrent Sens configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mcurrentsens_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mcurrentsens_cfg_setup ( mcurrentsens_cfg_t *cfg );

/**
 * @brief mCurrent Sens initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mcurrentsens_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mcurrentsens_init ( mcurrentsens_t *ctx, mcurrentsens_cfg_t *cfg );

/**
 * @brief mCurrent Sens default configuration function.
 * @details This function executes a default configuration of mCurrent Sens
 * Click board.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mcurrentsens_default_cfg ( mcurrentsens_t *ctx );

/**
 * @brief mCurrent Sens write register function.
 * @details This function writes a byte to the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_write_reg ( mcurrentsens_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief mCurrent Sens read register function.
 * @details This function reads a byte from the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory location where data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_reg ( mcurrentsens_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief mCurrent Sens write multiple registers function.
 * @details This function writes multiple bytes starting from the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to data buffer.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Uses incremental write command.
 */
err_t mcurrentsens_write_regs ( mcurrentsens_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief mCurrent Sens read multiple registers function.
 * @details This function reads multiple bytes starting from the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to output buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Uses incremental read command.
 */
err_t mcurrentsens_read_regs ( mcurrentsens_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief mCurrent Sens write 16-bit register function.
 * @details This function writes two bytes to the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_write_reg16 ( mcurrentsens_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief mCurrent Sens read 16-bit register function.
 * @details This function reads two bytes from the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory location where data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_reg16 ( mcurrentsens_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief mCurrent Sens write 24-bit register function.
 * @details This function writes three bytes to the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 24-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_write_reg24 ( mcurrentsens_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief mCurrent Sens read 24-bit register function.
 * @details This function reads three bytes from the specified register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory location where data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_reg24 ( mcurrentsens_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief mCurrent Sens send fast command function.
 * @details This function sends a fast command to the device.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] cmd : Fast command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_send_fast_cmd ( mcurrentsens_t *ctx, uint8_t cmd );

/**
 * @brief mCurrent Sens communication check function.
 * @details This function verifies device communication by reading the RESERVED_16 register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Device detected,
 *         @li @c -1 - Communication error.
 * @note Uses RESERVED_16 register as device ID check.
 */
err_t mcurrentsens_check_com ( mcurrentsens_t *ctx );

/**
 * @brief mCurrent Sens set MUX function.
 * @details This function selects the positive and negative ADC input channels.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] vin_p : Positive ADC input channel.
 * @param[in] vin_n : Negative ADC input channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_set_mux ( mcurrentsens_t *ctx, uint8_t vin_p, uint8_t vin_n );

/**
 * @brief mCurrent Sens set gain function.
 * @details This function sets the programmable gain amplifier value.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] gain : Gain setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_set_gain ( mcurrentsens_t *ctx, uint8_t gain );

/**
 * @brief mCurrent Sens set OSR function.
 * @details This function sets the oversampling ratio.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] osr : Oversampling ratio setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_set_osr ( mcurrentsens_t *ctx, uint8_t osr );

/**
 * @brief mCurrent Sens set mode function.
 * @details This function sets the ADC operating mode.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] mode : ADC operating mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_set_mode ( mcurrentsens_t *ctx, uint8_t mode );

/**
 * @brief mCurrent Sens get IRQ function.
 * @details This function reads the IRQ register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where IRQ data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_get_irq ( mcurrentsens_t *ctx, uint8_t *data_out );

/**
 * @brief mCurrent Sens set offset calibration function.
 * @details This function writes the OFFSETCAL register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] data_in : Signed 24-bit offset calibration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_set_offset_cal ( mcurrentsens_t *ctx, int32_t data_in );

/**
 * @brief mCurrent Sens get offset calibration function.
 * @details This function reads the OFFSETCAL register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where signed 24-bit offset calibration value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_get_offset_cal ( mcurrentsens_t *ctx, int32_t *data_out );

/**
 * @brief mCurrent Sens set gain calibration function.
 * @details This function writes the GAINCAL register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] data_in : Unsigned 24-bit gain calibration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_set_gain_cal ( mcurrentsens_t *ctx, uint32_t data_in );

/**
 * @brief mCurrent Sens get gain calibration function.
 * @details This function reads the GAINCAL register.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where unsigned 24-bit gain calibration value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_get_gain_cal ( mcurrentsens_t *ctx, uint32_t *data_out );

/**
 * @brief mCurrent Sens enable digital calibration function.
 * @details This function enables or disables digital offset and gain calibration.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] en_offset : Offset calibration enable setting.
 * @param[in] en_gain : Gain calibration enable setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_en_dig_cal ( mcurrentsens_t *ctx, uint8_t en_offset, uint8_t en_gain );

/**
 * @brief mCurrent Sens apply channel calibration function.
 * @details This function applies the specified channel calibration values.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] cal : Channel calibration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_apply_calib ( mcurrentsens_t *ctx, mcurrentsens_calib_t cal );

/**
 * @brief mCurrent Sens wait data ready function.
 * @details This function waits until ADC conversion is complete.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Data ready,
 *         @li @c -1 - Timeout.
 * @note Uses IRQ pin and DR_STATUS flag.
 */
err_t mcurrentsens_wait_data_ready ( mcurrentsens_t *ctx );

/**
 * @brief mCurrent Sens read ADC data function.
 * @details This function reads the signed 24-bit ADC conversion data.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_adc ( mcurrentsens_t *ctx, int32_t *data_out );

/**
 * @brief mCurrent Sens read averaged ADC function.
 * @details This function reads multiple ADC samples and returns averaged data.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] sample_count : Number of samples.
 * @param[out] data_out : Pointer to memory location where averaged ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note First sample is discarded.
 */
err_t mcurrentsens_read_adc_avg ( mcurrentsens_t *ctx, uint8_t sample_count, int32_t *data_out );

/**
 * @brief mCurrent Sens read averaged voltage function.
 * @details This function reads ADC samples and converts them to millivolts.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] sample_count : Number of samples.
 * @param[out] data_out : Pointer to memory location where voltage data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Uses internal reference and ADC gain.
 */
err_t mcurrentsens_read_voltage_avg ( mcurrentsens_t *ctx, uint8_t sample_count, float *data_out );

/**
 * @brief mCurrent Sens read channel 1 current function.
 * @details This function reads channel 1 current measurement in mA.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_ch1_current ( mcurrentsens_t *ctx, float *data_out );

/**
 * @brief mCurrent Sens read channel 1 voltage function.
 * @details This function reads channel 1 voltage measurement in mV.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_ch1_voltage ( mcurrentsens_t *ctx, float *data_out );

/**
 * @brief mCurrent Sens read channel 2 current function.
 * @details This function reads channel 2 current measurement in mA.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_ch2_current ( mcurrentsens_t *ctx, float *data_out );

/**
 * @brief mCurrent Sens read channel 2 voltage function.
 * @details This function reads channel 2 voltage measurement in mV.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mcurrentsens_read_ch2_voltage ( mcurrentsens_t *ctx, float *data_out );

/**
 * @brief mCurrent Sens read temperature function.
 * @details This function reads internal temperature data.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to memory location where temperature data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Temperature data is returned in degrees Celsius.
 */
err_t mcurrentsens_read_temperature ( mcurrentsens_t *ctx, float *data_out );

/**
 * @brief mCurrent Sens convert ADC code to millivolts function.
 * @details This function converts signed ADC code to millivolt value.
 * @param[in] adc_code : Signed ADC conversion code.
 * @param[in] gain_adc : ADC gain value.
 * @return Converted millivolt value.
 * @note None.
 */
float mcurrentsens_adc_to_mv ( int32_t adc_code, float gain_adc );

/**
 * @brief mCurrent Sens calculate calibration function.
 * @details This function calculates gain and offset calibration registers
 * based on two-point linear calibration.
 * @param[out] calib : Calibration structure.
 * @param[in] offset_coeff : Channel coefficient.
 * @param[in] target_1 : First reference value.
 * @param[in] measured_1 : Measured value at first point.
 * @param[in] target_2 : Second reference value.
 * @param[in] measured_2 : Measured value at second point.
 * @return None.
 * @note Implements linear fit equivalent to polyfit.
 */
void mcurrentsens_calculate_calib ( mcurrentsens_calib_t *calib, float offset_coeff,
                                    float target_1, float measured_1,
                                    float target_2, float measured_2 );

/**
 * @brief mCurrent Sens write memory function.
 * @details This function writes a sequence of bytes to the device memory over I2C,
 * starting at the selected 8-bit address. The write length must not exceed the
 * page size (16 bytes) and the transfer must not cross the device end address.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] address : Start memory address (8-bit).
 * @param[in] data_in : Pointer to input data buffer.
 * @param[in] len : Number of bytes to write (max page size).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mcurrentsens_write_memory ( mcurrentsens_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief mCurrent Sens read memory function.
 * @details This function reads a sequence of bytes from the device memory over I2C,
 * starting at the selected 8-bit address. The read length must not exceed the
 * page size (16 bytes) and the transfer must not cross the device end address.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @param[in] address : Start memory address (8-bit).
 * @param[out] data_out : Pointer to output data buffer.
 * @param[in] len : Number of bytes to read (max page size).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mcurrentsens_read_memory ( mcurrentsens_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief mCurrent Sens store calibration function.
 * @details This function stores calibration values to external EEPROM.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Stores calibration data in two EEPROM pages.
 */
err_t mcurrentsens_store_calib ( mcurrentsens_t *ctx );

/**
 * @brief mCurrent Sens fetch calibration function.
 * @details This function reads calibration values from external EEPROM.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Sets calibrated flag when calibration data is valid.
 */
err_t mcurrentsens_fetch_calib ( mcurrentsens_t *ctx );

/**
 * @brief mCurrent Sens get IRQ pin function.
 * @details This function reads the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return IRQ pin logic state.
 * @note None.
 */
uint8_t mcurrentsens_get_irq_pin ( mcurrentsens_t *ctx );

/**
 * @brief mCurrent Sens get CLK pin function.
 * @details This function reads the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #mcurrentsens_t object definition for detailed explanation.
 * @return CLK pin logic state.
 * @note None.
 */
uint8_t mcurrentsens_get_clk_pin ( mcurrentsens_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MCURRENTSENS_H

/*! @} */ // mcurrentsens

// ------------------------------------------------------------------------ END

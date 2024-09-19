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
 * @file dac16.h
 * @brief This file contains API for DAC 16 Click Driver.
 */

#ifndef DAC16_H
#define DAC16_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup dac16 DAC 16 Click Driver
 * @brief API for configuring and manipulating DAC 16 Click driver.
 * @{
 */

/**
 * @defgroup dac16_reg DAC 16 Registers List
 * @brief List of registers of DAC 16 Click driver.
 */

/**
 * @addtogroup dac16_reg
 * @{
 */

/**
 * @brief DAC 16 register list.
 * @details Specified register list of DAC 16 Click driver.
 */
#define DAC16_REG_NOP                       0x00
#define DAC16_REG_DAC0_MARGIN_HIGH          0x01
#define DAC16_REG_DAC0_MARGIN_LOW           0x02
#define DAC16_REG_DAC0_VOUT_CMP_CONFIG      0x03
#define DAC16_REG_DAC0_IOUT_MISC_CONFIG     0x04
#define DAC16_REG_DAC0_CMP_MODE_CONFIG      0x05
#define DAC16_REG_DAC0_FUNC_CONFIG          0x06
#define DAC16_REG_DAC1_MARGIN_HIGH          0x07
#define DAC16_REG_DAC1_MARGIN_LOW           0x08
#define DAC16_REG_DAC1_VOUT_CMP_CONFIG      0x09
#define DAC16_REG_DAC1_IOUT_MISC_CONFIG     0x0A
#define DAC16_REG_DAC1_CMP_MODE_CONFIG      0x0B
#define DAC16_REG_DAC1_FUNC_CONFIG          0x0C
#define DAC16_REG_DAC2_MARGIN_HIGH          0x0D
#define DAC16_REG_DAC2_MARGIN_LOW           0x0E
#define DAC16_REG_DAC2_VOUT_CMP_CONFIG      0x0F
#define DAC16_REG_DAC2_IOUT_MISC_CONFIG     0x10
#define DAC16_REG_DAC2_CMP_MODE_CONFIG      0x11
#define DAC16_REG_DAC2_FUNC_CONFIG          0x12
#define DAC16_REG_DAC3_MARGIN_HIGH          0x13
#define DAC16_REG_DAC3_MARGIN_LOW           0x14
#define DAC16_REG_DAC3_VOUT_CMP_CONFIG      0x15
#define DAC16_REG_DAC3_IOUT_MISC_CONFIG     0x16
#define DAC16_REG_DAC3_CMP_MODE_CONFIG      0x17
#define DAC16_REG_DAC3_FUNC_CONFIG          0x18
#define DAC16_REG_DAC0_DATA                 0x19
#define DAC16_REG_DAC1_DATA                 0x1A
#define DAC16_REG_DAC2_DATA                 0x1B
#define DAC16_REG_DAC3_DATA                 0x1C
#define DAC16_REG_COMMON_CONFIG             0x1F
#define DAC16_REG_COMMON_TRIGGER            0x20
#define DAC16_REG_COMMON_DAC_TRIG           0x21
#define DAC16_REG_GENERAL_STATUS            0x22
#define DAC16_REG_CMP_STATUS                0x23
#define DAC16_REG_GPIO_CONFIG               0x24
#define DAC16_REG_DEVICE_MODE_CONFIG        0x25
#define DAC16_REG_INTERFACE_CONFIG          0x26
#define DAC16_REG_SRAM_CONFIG               0x2B
#define DAC16_REG_SRAM_DATA                 0x2C
#define DAC16_REG_DAC0_DATA_8BIT            0x40
#define DAC16_REG_DAC1_DATA_8BIT            0x41
#define DAC16_REG_DAC2_DATA_8BIT            0x42
#define DAC16_REG_DAC3_DATA_8BIT            0x43
#define DAC16_REG_BRDCAST_DATA              0x50

/*! @} */ // dac16_reg

/**
 * @defgroup dac16_set DAC 16 Registers Settings
 * @brief Settings for registers of DAC 16 Click driver.
 */

/**
 * @addtogroup dac16_set
 * @{
 */

/**
 * @brief DAC 16 COMMON_CONFIG register setting.
 * @details Specified setting for COMMON_CONFIG register of DAC 16 Click driver.
 */
#define DAC16_CC_WIN_LATCH_EN               0x8000
#define DAC16_CC_DEV_LOCK                   0x4000
#define DAC16_CC_EE_READ_ADDR               0x2000
#define DAC16_CC_EN_INT_REF                 0x1000
#define DAC16_CC_VOUT_PDN_3_POWER_UP        0x0000
#define DAC16_CC_VOUT_PDN_3_POWER_DOWN_10K  0x0400
#define DAC16_CC_VOUT_PDN_3_POWER_DOWN_100K 0x0800
#define DAC16_CC_VOUT_PDN_3_POWER_DOWN_Z    0x0C00
#define DAC16_CC_VOUT_PDN_3_MASK            0x0C00
#define DAC16_CC_IOUT_PDN_3_POWER_UP        0x0000
#define DAC16_CC_IOUT_PDN_3_POWER_DOWN      0x0200
#define DAC16_CC_IOUT_PDN_3_MASK            0x0200
#define DAC16_CC_VOUT_PDN_2_POWER_UP        0x0000
#define DAC16_CC_VOUT_PDN_2_POWER_DOWN_10K  0x0080
#define DAC16_CC_VOUT_PDN_2_POWER_DOWN_100K 0x0100
#define DAC16_CC_VOUT_PDN_2_POWER_DOWN_Z    0x0180
#define DAC16_CC_VOUT_PDN_2_MASK            0x0180
#define DAC16_CC_IOUT_PDN_2_POWER_UP        0x0000
#define DAC16_CC_IOUT_PDN_2_POWER_DOWN      0x0040
#define DAC16_CC_IOUT_PDN_2_MASK            0x0040
#define DAC16_CC_VOUT_PDN_1_POWER_UP        0x0000
#define DAC16_CC_VOUT_PDN_1_POWER_DOWN_10K  0x0010
#define DAC16_CC_VOUT_PDN_1_POWER_DOWN_100K 0x0020
#define DAC16_CC_VOUT_PDN_1_POWER_DOWN_Z    0x0030
#define DAC16_CC_VOUT_PDN_1_MASK            0x0030
#define DAC16_CC_IOUT_PDN_1_POWER_UP        0x0000
#define DAC16_CC_IOUT_PDN_1_POWER_DOWN      0x0008
#define DAC16_CC_IOUT_PDN_1_MASK            0x0008
#define DAC16_CC_VOUT_PDN_0_POWER_UP        0x0000
#define DAC16_CC_VOUT_PDN_0_POWER_DOWN_10K  0x0002
#define DAC16_CC_VOUT_PDN_0_POWER_DOWN_100K 0x0004
#define DAC16_CC_VOUT_PDN_0_POWER_DOWN_Z    0x0006
#define DAC16_CC_VOUT_PDN_0_MASK            0x0006
#define DAC16_CC_IOUT_PDN_0_POWER_UP        0x0000
#define DAC16_CC_IOUT_PDN_0_POWER_DOWN      0x0001
#define DAC16_CC_IOUT_PDN_0_MASK            0x0001

/**
 * @brief DAC 16 COMMON_DAC_TRIG register setting.
 * @details Specified setting for COMMON_DAC_TRIG register of DAC 16 Click driver.
 */
#define DAC16_CDT_RESET_CMP_FLAG_0          0x8000
#define DAC16_CDT_TRIG_MAR_LO_0             0x4000
#define DAC16_CDT_TRIG_MAR_HI_0             0x2000
#define DAC16_CDT_STOP_FUNC_0               0x0000
#define DAC16_CDT_START_FUNC_0              0x1000
#define DAC16_CDT_RESET_CMP_FLAG_1          0x0800
#define DAC16_CDT_TRIG_MAR_LO_1             0x0400
#define DAC16_CDT_TRIG_MAR_HI_1             0x0200
#define DAC16_CDT_STOP_FUNC_1               0x0000
#define DAC16_CDT_START_FUNC_1              0x0100
#define DAC16_CDT_RESET_CMP_FLAG_2          0x0080
#define DAC16_CDT_TRIG_MAR_LO_2             0x0040
#define DAC16_CDT_TRIG_MAR_HI_2             0x0020
#define DAC16_CDT_STOP_FUNC_2               0x0000
#define DAC16_CDT_START_FUNC_2              0x0010
#define DAC16_CDT_RESET_CMP_FLAG_3          0x0008
#define DAC16_CDT_TRIG_MAR_LO_3             0x0004
#define DAC16_CDT_TRIG_MAR_HI_3             0x0002
#define DAC16_CDT_START_FUNC_3              0x0001
#define DAC16_CDT_STOP_FUNC_3               0x0000

/**
 * @brief DAC 16 DAC_X_FUNC_CONFIG register setting.
 * @details Specified setting for DAC_X_FUNC_CONFIG register of DAC 16 Click driver.
 */
#define DAC16_DXFC_CLR_SEL_X                0x8000
#define DAC16_DXFC_SYNC_CONFIG_X            0x4000
#define DAC16_DXFC_BRD_CONFIG_X             0x2000
#define DAC16_DXFC_PHASE_SEL_X_0_DEG        0x0000
#define DAC16_DXFC_PHASE_SEL_X_120_DEG      0x0800
#define DAC16_DXFC_PHASE_SEL_X_240_DEG      0x1000
#define DAC16_DXFC_PHASE_SEL_X_90_DEG       0x1800
#define DAC16_DXFC_PHASE_SEL_X_MASK         0x1800
#define DAC16_DXFC_FUNC_CONFIG_X_TRIANGULAR 0x0000
#define DAC16_DXFC_FUNC_CONFIG_X_SAWTH      0x0100
#define DAC16_DXFC_FUNC_CONFIG_X_INV_SAWTH  0x0200
#define DAC16_DXFC_FUNC_CONFIG_X_SINE       0x0400
#define DAC16_DXFC_FUNC_CONFIG_X_DIS_FC     0x0700
#define DAC16_DXFC_FUNC_CONFIG_X_MASK       0x0700
#define DAC16_DXFC_LOG_SLEW_EN_X            0x0080
#define DAC16_DXFC_CODE_STEP_X_1            0x0000
#define DAC16_DXFC_CODE_STEP_X_2            0x0010
#define DAC16_DXFC_CODE_STEP_X_3            0x0020
#define DAC16_DXFC_CODE_STEP_X_4            0x0030
#define DAC16_DXFC_CODE_STEP_X_6            0x0040
#define DAC16_DXFC_CODE_STEP_X_8            0x0050
#define DAC16_DXFC_CODE_STEP_X_16           0x0060
#define DAC16_DXFC_CODE_STEP_X_32           0x0070
#define DAC16_DXFC_CODE_STEP_X_MASK         0x0070
#define DAC16_DXFC_SLEW_RATE_X_NO_SR        0x0000
#define DAC16_DXFC_SLEW_RATE_X_4_US         0x0001
#define DAC16_DXFC_SLEW_RATE_X_8_US         0x0002
#define DAC16_DXFC_SLEW_RATE_X_12_US        0x0003
#define DAC16_DXFC_SLEW_RATE_X_18_US        0x0004
#define DAC16_DXFC_SLEW_RATE_X_27_04_US     0x0005
#define DAC16_DXFC_SLEW_RATE_X_40_48_US     0x0006
#define DAC16_DXFC_SLEW_RATE_X_60_72_US     0x0007
#define DAC16_DXFC_SLEW_RATE_X_91_12_US     0x0008
#define DAC16_DXFC_SLEW_RATE_X_136_72_US    0x0009
#define DAC16_DXFC_SLEW_RATE_X_239_2_US     0x000A
#define DAC16_DXFC_SLEW_RATE_X_418_64_US    0x000B
#define DAC16_DXFC_SLEW_RATE_X_732_56_US    0x000C
#define DAC16_DXFC_SLEW_RATE_X_1282_US      0x000D
#define DAC16_DXFC_SLEW_RATE_X_2563_96_US   0x000E
#define DAC16_DXFC_SLEW_RATE_X_5127_92_US   0x000F
#define DAC16_DXFC_SLEW_RATE_X_MASK         0x000F

/**
 * @brief DAC 16 DAC_X_VOUT_CMP_CONFIG register setting.
 * @details Specified setting for DAC_X_VOUT_CMP_CONFIG register of DAC 16 Click driver.
 */
#define DAC16_VCC_VOUT_GAIN_X_EXT_VREF      0x0000
#define DAC16_VCC_VOUT_GAIN_X_VDD           0x0400
#define DAC16_VCC_VOUT_GAIN_X_INT_1_5X      0x0800
#define DAC16_VCC_VOUT_GAIN_X_INT_2X        0x0C00
#define DAC16_VCC_VOUT_GAIN_X_INT_3X        0x1000
#define DAC16_VCC_VOUT_GAIN_X_INT_4X        0x1400
#define DAC16_VCC_VOUT_GAIN_X_MASK          0x1C00
#define DAC16_VCC_CMP_X_OD_EN               0x0010
#define DAC16_VCC_CMP_X_OUT_EN              0x0008
#define DAC16_VCC_CMP_X_HIZ_IN_EN           0x0004
#define DAC16_VCC_CMP_X_INV_EN              0x0002
#define DAC16_VCC_CMP_X_EN                  0x0001

/**
 * @brief DAC 16 INTERFACE_CONFIG register setting.
 * @details Specified setting for INTERFACE_CONFIG register of DAC 16 Click driver.
 */
#define DAC16_IC_TIMEOUT_EN                 0x1000
#define DAC16_IC_EN_PMBUS                   0x0100
#define DAC16_IC_FSDO_EN                    0x0004
#define DAC16_IC_SDO_EN                     0x0001
#define DAC16_IC_SDO_DIS                    0x0000

/**
 * @brief DAC 16 DAC setting.
 * @details Specified setting for DAC setting of DAC 16 Click driver.
 */
#define DAC16_DAC_DATA_MAX                  4095
#define DAC16_DAC_DATA_MIN                  0

/**
 * @brief DAC 16 device ID setting.
 * @details Specified setting for device ID of DAC 16 Click driver.
 */
#define DAC16_DEVICE_ID_MASK                0xFC
#define DAC16_DEVICE_ID                     0x4C

/**
 * @brief DAC 16 DAC selection setting.
 * @details Specified setting for DAC selection of DAC 16 Click driver.
 */
#define DAC16_SEL_DAC_0                     0
#define DAC16_SEL_DAC_1                     1
#define DAC16_SEL_DAC_2                     2
#define DAC16_SEL_DAC_3                     3

/**
 * @brief DAC 16 DAC enable setting.
 * @details Specified setting for DAC enable of DAC 16 Click driver.
 */
#define DAC16_EN_VOUT_POWER_UP              0
#define DAC16_EN_VOUT_POWER_DOWN_10K_AGND   1
#define DAC16_EN_VOUT_POWER_DOWN_100K_AGND  2
#define DAC16_EN_VOUT_POWER_DOWN_HI_Z_AGND  3

/**
 * @brief DAC 16 DAC waveform setting.
 * @details Specified setting for DAC waveform of DAC 16 Click driver.
 */
#define DAC16_WAVEFORM_TRIANGULAR           0
#define DAC16_WAVEFORM_SAWTOOTH             1
#define DAC16_WAVEFORM_INV_SAWTOOTH         2
#define DAC16_WAVEFORM_SINE                 4
#define DAC16_WAVEFORM_DISABLE              7

/**
 * @brief DAC 16 DAC code step setting.
 * @details Specified setting for DAC code step of DAC 16 Click driver.
 */
#define DAC16_CODE_STEP_1_LSB               0
#define DAC16_CODE_STEP_2_LSB               1
#define DAC16_CODE_STEP_3_LSB               2
#define DAC16_CODE_STEP_4_LSB               3
#define DAC16_CODE_STEP_6_LSB               4
#define DAC16_CODE_STEP_8_LSB               5
#define DAC16_CODE_STEP_16_LSB              6
#define DAC16_CODE_STEP_32_LSB              7

/**
 * @brief DAC 16 DAC slew rate setting.
 * @details Specified setting for DAC slew rate of DAC 16 Click driver.
 */
#define DAC16_SLEW_RATE_NO_SLEW             0
#define DAC16_SLEW_RATE_4_US                1
#define DAC16_SLEW_RATE_8_US                2
#define DAC16_SLEW_RATE_12_US               3
#define DAC16_SLEW_RATE_18_US               4
#define DAC16_SLEW_RATE_27_04_US            5
#define DAC16_SLEW_RATE_40_48_US            6
#define DAC16_SLEW_RATE_60_72_US            7
#define DAC16_SLEW_RATE_91_12_US            8
#define DAC16_SLEW_RATE_136_72_US           9
#define DAC16_SLEW_RATE_239_2_US            10
#define DAC16_SLEW_RATE_418_64_US           11
#define DAC16_SLEW_RATE_732_56_US           12
#define DAC16_SLEW_RATE_1282_US             13
#define DAC16_SLEW_RATE_2563_96_US          14
#define DAC16_SLEW_RATE_5127_92_US          15

/**
 * @brief DAC 16 DAC VREF setting.
 * @details Specified setting for DAC VREF of DAC 16 Click driver.
 */
#define DAC16_VREF_EXT                      0
#define DAC16_VREF_VDD                      1
#define DAC16_VREF_INT_1_5X                 2
#define DAC16_VREF_INT_2X                   3
#define DAC16_VREF_INT_3X                   4
#define DAC16_VREF_INT_4X                   5

/**
 * @brief DAC 16 DAC VDD setting.
 * @details Specified setting for DAC VDD of DAC 16 Click driver.
 */
#define DAC16_VDD_3V3                       3.3f
#define DAC16_VDD_5V                        5.0f

/**
 * @brief DAC 16 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 16 Click driver.
 */
#define DAC16_DEVICE_ADDRESS_GND            0x48
#define DAC16_DEVICE_ADDRESS_VCC            0x49
#define DAC16_DEVICE_ADDRESS_SDA            0x4A
#define DAC16_DEVICE_ADDRESS_SCL            0x4B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC16_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define DAC16_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac16_set

/**
 * @defgroup dac16_map DAC 16 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 16 Click driver.
 */

/**
 * @addtogroup dac16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 16 Click to the selected MikroBUS.
 */
#define DAC16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gp = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dac16_map
/*! @} */ // dac16

/**
 * @brief DAC 16 Click driver selector.
 * @details Selects target driver interface of DAC 16 Click driver.
 */
typedef enum
{
    DAC16_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    DAC16_DRV_SEL_I2C       /**< I2C driver descriptor. */

} dac16_drv_t;

/**
 * @brief DAC 16 Click driver interface.
 * @details Definition of driver interface of DAC 16 Click driver.
 */
struct dac16_s;
typedef err_t ( *dac16_master_io_t )( struct dac16_s*, uint8_t, uint16_t* ); /**< Driver serial interface. */

/**
 * @brief DAC 16 Click context object.
 * @details Context object definition of DAC 16 Click driver.
 */
typedef struct dac16_s
{
    digital_in_t gp;            /**< General-purpose input/output configurable as LDAC, PD, PROTECT, RESET, SDO, and STATUS. */

    i2c_master_t i2c;           /**< I2C driver object. */
    spi_master_t spi;           /**< SPI driver object. */

    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
    dac16_drv_t drv_sel;        /**< Master driver interface selector. */

    dac16_master_io_t write_f;  /**< Master write function. */
    dac16_master_io_t read_f;   /**< Master read function. */

} dac16_t;

/**
 * @brief DAC 16 Click configuration object.
 * @details Configuration object definition of DAC 16 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t gp;              /**< General-purpose input/output configurable as LDAC, PD, PROTECT, RESET, SDO, and STATUS. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    dac16_drv_t drv_sel;        /**< Master driver interface selector. */

} dac16_cfg_t;

/**
 * @brief DAC 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC16_OK = 0,
    DAC16_ERROR = -1

} dac16_return_value_t;

/*!
 * @addtogroup dac16 DAC 16 Click Driver
 * @brief API for configuring and manipulating DAC 16 Click driver.
 * @{
 */

/**
 * @brief DAC 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac16_cfg_setup ( dac16_cfg_t *cfg );

/**
 * @brief DAC 16 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #dac16_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #dac16_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void dac16_drv_interface_sel ( dac16_cfg_t *cfg, dac16_drv_t drv_sel );

/**
 * @brief DAC 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_init ( dac16_t *ctx, dac16_cfg_t *cfg );

/**
 * @brief DAC 16 default configuration function.
 * @details This function executes a default configuration of DAC 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac16_default_cfg ( dac16_t *ctx );

/**
 * @brief DAC 16 write register function.
 * @details This function writes a desired data word to the selected register.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_write_register ( dac16_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 16 read register function.
 * @details This function reads data word from the selected register.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_read_register ( dac16_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 16 get GP pin function.
 * @details This function returns the GP pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This pin is available only in I2C mode.
 */
uint8_t dac16_get_gp_pin ( dac16_t *ctx );

/**
 * @brief DAC 16 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_check_communication ( dac16_t *ctx );

/**
 * @brief DAC 16 set dac vout enable function.
 * @details This function sets the VOUT power enable bits for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @param[in] vout_pdn : VOUT PDN bits: @li @c 0 - Power-up VOUT-X,
 *                                      @li @c 1 - Power-down VOUT-X with 10 kOhm to AGND,
 *                                      @li @c 2 - Power-down VOUT-X with 100 kOhm to AGND,
 *                                      @li @c 3 - Power-down VOUT-X with Hi-Z to AGND.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_set_dac_vout_enable ( dac16_t *ctx, uint8_t dac, uint8_t vout_pdn );

/**
 * @brief DAC 16 set dac vref function.
 * @details This function sets the voltage reference for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @param[in] vref : Voltage reference: @li @c 0 - Gain = 1x, external reference on VREF pin,
 *                                      @li @c 1 - Gain = 1x, VDD as reference,
 *                                      @li @c 2 - Gain = 1.5x, internal reference,
 *                                      @li @c 3 - Gain = 2x, internal reference,
 *                                      @li @c 4 - Gain = 3x, internal reference,
 *                                      @li @c 5 - Gain = 4x, internal reference.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_set_dac_vref ( dac16_t *ctx, uint8_t dac, uint8_t vref );

/**
 * @brief DAC 16 set dac margins function.
 * @details This function sets the DAC margin levels for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @param[in] margin_l : Margin LOW (must be <= Margin HIGH) in a range of DAC data (0-1023).
 * @param[in] margin_h : Margin HIGH (must be >= Margin LOW) in a range of DAC data (0-1023).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_set_dac_margins ( dac16_t *ctx, uint8_t dac, uint16_t margin_l, uint16_t margin_h );

/**
 * @brief DAC 16 set dac data function.
 * @details This function sets the raw DAC data for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @param[in] dac_data : Raw DAC data (0-1023).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_set_dac_data ( dac16_t *ctx, uint8_t dac, uint16_t dac_data );

/**
 * @brief DAC 16 start function gen function.
 * @details This function starts the function generator for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_start_function_gen ( dac16_t *ctx, uint8_t dac );

/**
 * @brief DAC 16 stop function gen function.
 * @details This function stops the function generator for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac16_stop_function_gen ( dac16_t *ctx, uint8_t dac );

/**
 * @brief DAC 16 config function gen function.
 * @details This function configures the function generator for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1,
 *                               @li @c 2 - DAC2,
 *                               @li @c 3 - DAC3.
 * @param[in] waveform : Waveform signal: @li @c 0 - Triangular wave,
 *                                        @li @c 1 - Sawtooth wave,
 *                                        @li @c 2 - Inverse sawtooth wave,
 *                                        @li @c 4 - Sine wave,
 *                                        @li @c 7 - Disable function generation.
 * @param[in] code_step : Code step setting. Refer to DAC16_CODE_STEP_x macro definitions for more details.
 * @param[in] slew_rate : Slew rate setting. Refer to DAC16_SLEW_RATE_x macro definitions for more details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Each wave has its own output frequency calculation which relies on 
 * CODE_STEP, SLEW_RATE, and MARGIN LOW/HIGH settings. It should be calculated as follows:
 * TRIANGLE_FREQUENCY = 1 / ( 2 * SLEW_RATE_US * ( MARGIN_HIGH - MARGIN_LOW + 1 ) / CODE_STEP )
 * SAWTOOTH_FREQUENCY = 1 / ( SLEW_RATE_US * ( MARGIN_HIGH - MARGIN_LOW + 1 ) / CODE_STEP )
 * SINE_FREQUENCY = 1 / ( 24 * SLEW_RATE_US )
 * By default, those parameters are set for DAC1 to output triangular wave at about 4kHz.
 */
err_t dac16_config_function_gen ( dac16_t *ctx, uint8_t dac, uint8_t waveform, 
                                  uint8_t code_step, uint8_t slew_rate );

#ifdef __cplusplus
}
#endif
#endif // DAC16_H

/*! @} */ // dac16

// ------------------------------------------------------------------------ END

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
 * @file dac14.h
 * @brief This file contains API for DAC 14 Click Driver.
 */

#ifndef DAC14_H
#define DAC14_H

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
 * @addtogroup dac14 DAC 14 Click Driver
 * @brief API for configuring and manipulating DAC 14 Click driver.
 * @{
 */

/**
 * @defgroup dac14_reg DAC 14 Registers List
 * @brief List of registers of DAC 14 Click driver.
 */

/**
 * @addtogroup dac14_reg
 * @{
 */

/**
 * @brief DAC 14 register list.
 * @details Specified register list of DAC 14 Click driver.
 */
#define DAC14_REG_NOP                       0x00
#define DAC14_REG_DAC1_MARGIN_HIGH          0x01
#define DAC14_REG_DAC1_MARGIN_LOW           0x02
#define DAC14_REG_DAC1_VOUT_CMP_CONFIG      0x03
#define DAC14_REG_DAC1_IOUT_MISC_CONFIG     0x04
#define DAC14_REG_DAC1_CMP_MODE_CONFIG      0x05
#define DAC14_REG_DAC1_FUNC_CONFIG          0x06
#define DAC14_REG_DAC0_MARGIN_HIGH          0x13
#define DAC14_REG_DAC0_MARGIN_LOW           0x14
#define DAC14_REG_DAC0_VOUT_CMP_CONFIG      0x15
#define DAC14_REG_DAC0_IOUT_MISC_CONFIG     0x16
#define DAC14_REG_DAC0_CMP_MODE_CONFIG      0x17
#define DAC14_REG_DAC0_FUNC_CONFIG          0x18
#define DAC14_REG_DAC1_DATA                 0x19
#define DAC14_REG_DAC0_DATA                 0x1C
#define DAC14_REG_COMMON_CONFIG             0x1F
#define DAC14_REG_COMMON_TRIGGER            0x20
#define DAC14_REG_COMMON_DAC_TRIG           0x21
#define DAC14_REG_GENERAL_STATUS            0x22
#define DAC14_REG_CMP_STATUS                0x23
#define DAC14_REG_GPIO_CONFIG               0x24
#define DAC14_REG_DEVICE_MODE_CONFIG        0x25
#define DAC14_REG_INTERFACE_CONFIG          0x26
#define DAC14_REG_SRAM_CONFIG               0x2B
#define DAC14_REG_SRAM_DATA                 0x2C
#define DAC14_REG_BRDCAST_DATA              0x50

/*! @} */ // dac14_reg

/**
 * @defgroup dac14_set DAC 14 Registers Settings
 * @brief Settings for registers of DAC 14 Click driver.
 */

/**
 * @addtogroup dac14_set
 * @{
 */

/**
 * @brief DAC 14 COMMON_CONFIG register setting.
 * @details Specified setting for COMMON_CONFIG register of DAC 14 Click driver.
 */
#define DAC14_CC_WIN_LATCH_EN               0x8000
#define DAC14_CC_DEV_LOCK                   0x4000
#define DAC14_CC_EE_READ_ADDR               0x2000
#define DAC14_CC_EN_INT_REF                 0x1000
#define DAC14_CC_VOUT_PDN_0_POWER_UP        0x0000
#define DAC14_CC_VOUT_PDN_0_POWER_DOWN_10K  0x0400
#define DAC14_CC_VOUT_PDN_0_POWER_DOWN_100K 0x0800
#define DAC14_CC_VOUT_PDN_0_POWER_DOWN_Z    0x0C00
#define DAC14_CC_VOUT_PDN_0_MASK            0x0C00
#define DAC14_CC_IOUT_PDN_0_POWER_UP        0x0000
#define DAC14_CC_IOUT_PDN_0_POWER_DOWN      0x0200
#define DAC14_CC_IOUT_PDN_0_MASK            0x0200
#define DAC14_CC_RESERVED                   0x0088
#define DAC14_CC_VOUT_PDN_1_POWER_UP        0x0000
#define DAC14_CC_VOUT_PDN_1_POWER_DOWN_10K  0x0002
#define DAC14_CC_VOUT_PDN_1_POWER_DOWN_100K 0x0004
#define DAC14_CC_VOUT_PDN_1_POWER_DOWN_Z    0x0006
#define DAC14_CC_VOUT_PDN_1_MASK            0x0006
#define DAC14_CC_IOUT_PDN_1_POWER_UP        0x0000
#define DAC14_CC_IOUT_PDN_1_POWER_DOWN      0x0001
#define DAC14_CC_IOUT_PDN_1_MASK            0x0001

/**
 * @brief DAC 14 COMMON_DAC_TRIG register setting.
 * @details Specified setting for COMMON_DAC_TRIG register of DAC 14 Click driver.
 */
#define DAC14_CDT_RESET_CMP_FLAG_1          0x8000
#define DAC14_CDT_TRIG_MAR_LO_1             0x4000
#define DAC14_CDT_TRIG_MAR_HI_1             0x2000
#define DAC14_CDT_STOP_FUNC_1               0x0000
#define DAC14_CDT_START_FUNC_1              0x1000
#define DAC14_CDT_RESET_CMP_FLAG_0          0x0008
#define DAC14_CDT_TRIG_MAR_LO_0             0x0004
#define DAC14_CDT_TRIG_MAR_HI_0             0x0002
#define DAC14_CDT_START_FUNC_0              0x0001
#define DAC14_CDT_STOP_FUNC_0               0x0000

/**
 * @brief DAC 14 DAC_X_FUNC_CONFIG register setting.
 * @details Specified setting for DAC_X_FUNC_CONFIG register of DAC 14 Click driver.
 */
#define DAC14_DXFC_CLR_SEL_X                0x8000
#define DAC14_DXFC_SYNC_CONFIG_X            0x4000
#define DAC14_DXFC_BRD_CONFIG_X             0x2000
#define DAC14_DXFC_PHASE_SEL_X_0_DEG        0x0000
#define DAC14_DXFC_PHASE_SEL_X_120_DEG      0x0800
#define DAC14_DXFC_PHASE_SEL_X_240_DEG      0x1000
#define DAC14_DXFC_PHASE_SEL_X_90_DEG       0x1800
#define DAC14_DXFC_PHASE_SEL_X_MASK         0x1800
#define DAC14_DXFC_FUNC_CONFIG_X_TRIANGULAR 0x0000
#define DAC14_DXFC_FUNC_CONFIG_X_SAWTH      0x0100
#define DAC14_DXFC_FUNC_CONFIG_X_INV_SAWTH  0x0200
#define DAC14_DXFC_FUNC_CONFIG_X_SINE       0x0400
#define DAC14_DXFC_FUNC_CONFIG_X_DIS_FC     0x0700
#define DAC14_DXFC_FUNC_CONFIG_X_MASK       0x0700
#define DAC14_DXFC_LOG_SLEW_EN_X            0x0080
#define DAC14_DXFC_CODE_STEP_X_1            0x0000
#define DAC14_DXFC_CODE_STEP_X_2            0x0010
#define DAC14_DXFC_CODE_STEP_X_3            0x0020
#define DAC14_DXFC_CODE_STEP_X_4            0x0030
#define DAC14_DXFC_CODE_STEP_X_6            0x0040
#define DAC14_DXFC_CODE_STEP_X_8            0x0050
#define DAC14_DXFC_CODE_STEP_X_16           0x0060
#define DAC14_DXFC_CODE_STEP_X_32           0x0070
#define DAC14_DXFC_CODE_STEP_X_MASK         0x0070
#define DAC14_DXFC_SLEW_RATE_X_NO_SR        0x0000
#define DAC14_DXFC_SLEW_RATE_X_4_US         0x0001
#define DAC14_DXFC_SLEW_RATE_X_8_US         0x0002
#define DAC14_DXFC_SLEW_RATE_X_12_US        0x0003
#define DAC14_DXFC_SLEW_RATE_X_18_US        0x0004
#define DAC14_DXFC_SLEW_RATE_X_27_04_US     0x0005
#define DAC14_DXFC_SLEW_RATE_X_40_48_US     0x0006
#define DAC14_DXFC_SLEW_RATE_X_60_72_US     0x0007
#define DAC14_DXFC_SLEW_RATE_X_91_12_US     0x0008
#define DAC14_DXFC_SLEW_RATE_X_136_72_US    0x0009
#define DAC14_DXFC_SLEW_RATE_X_239_2_US     0x000A
#define DAC14_DXFC_SLEW_RATE_X_418_64_US    0x000B
#define DAC14_DXFC_SLEW_RATE_X_732_56_US    0x000C
#define DAC14_DXFC_SLEW_RATE_X_1282_US      0x000D
#define DAC14_DXFC_SLEW_RATE_X_2563_96_US   0x000E
#define DAC14_DXFC_SLEW_RATE_X_5127_92_US   0x000F
#define DAC14_DXFC_SLEW_RATE_X_MASK         0x000F

/**
 * @brief DAC 14 DAC_X_VOUT_CMP_CONFIG register setting.
 * @details Specified setting for DAC_X_VOUT_CMP_CONFIG register of DAC 14 Click driver.
 */
#define DAC14_VCC_VOUT_GAIN_X_EXT_VREF      0x0000
#define DAC14_VCC_VOUT_GAIN_X_VDD           0x0400
#define DAC14_VCC_VOUT_GAIN_X_INT_1_5X      0x0800
#define DAC14_VCC_VOUT_GAIN_X_INT_2X        0x0C00
#define DAC14_VCC_VOUT_GAIN_X_INT_3X        0x1000
#define DAC14_VCC_VOUT_GAIN_X_INT_4X        0x1400
#define DAC14_VCC_VOUT_GAIN_X_MASK          0x1C00
#define DAC14_VCC_CMP_X_OD_EN               0x0010
#define DAC14_VCC_CMP_X_OUT_EN              0x0008
#define DAC14_VCC_CMP_X_HIZ_IN_EN           0x0004
#define DAC14_VCC_CMP_X_INV_EN              0x0002
#define DAC14_VCC_CMP_X_EN                  0x0001

/**
 * @brief DAC 14 INTERFACE_CONFIG register setting.
 * @details Specified setting for INTERFACE_CONFIG register of DAC 14 Click driver.
 */
#define DAC14_IC_TIMEOUT_EN                 0x1000
#define DAC14_IC_EN_PMBUS                   0x0100
#define DAC14_IC_FSDO_EN                    0x0004
#define DAC14_IC_SDO_EN                     0x0001
#define DAC14_IC_SDO_DIS                    0x0000

/**
 * @brief DAC 14 DAC setting.
 * @details Specified setting for DAC setting of DAC 14 Click driver.
 */
#define DAC14_DAC_DATA_MAX                  1023
#define DAC14_DAC_DATA_MIN                  0

/**
 * @brief DAC 14 device ID setting.
 * @details Specified setting for device ID of DAC 14 Click driver.
 */
#define DAC14_DEVICE_ID_MASK                0xFC
#define DAC14_DEVICE_ID                     0x1C

/**
 * @brief DAC 14 DAC selection setting.
 * @details Specified setting for DAC selection of DAC 14 Click driver.
 */
#define DAC14_SEL_DAC_0                     0
#define DAC14_SEL_DAC_1                     1

/**
 * @brief DAC 14 DAC enable setting.
 * @details Specified setting for DAC enable of DAC 14 Click driver.
 */
#define DAC14_EN_VOUT_POWER_UP              0
#define DAC14_EN_VOUT_POWER_DOWN_10K_AGND   1
#define DAC14_EN_VOUT_POWER_DOWN_100K_AGND  2
#define DAC14_EN_VOUT_POWER_DOWN_HI_Z_AGND  3

/**
 * @brief DAC 14 DAC waveform setting.
 * @details Specified setting for DAC waveform of DAC 14 Click driver.
 */
#define DAC14_WAVEFORM_TRIANGULAR           0
#define DAC14_WAVEFORM_SAWTOOTH             1
#define DAC14_WAVEFORM_INV_SAWTOOTH         2
#define DAC14_WAVEFORM_SINE                 4
#define DAC14_WAVEFORM_DISABLE              7

/**
 * @brief DAC 14 DAC code step setting.
 * @details Specified setting for DAC code step of DAC 14 Click driver.
 */
#define DAC14_CODE_STEP_1_LSB               0
#define DAC14_CODE_STEP_2_LSB               1
#define DAC14_CODE_STEP_3_LSB               2
#define DAC14_CODE_STEP_4_LSB               3
#define DAC14_CODE_STEP_6_LSB               4
#define DAC14_CODE_STEP_8_LSB               5
#define DAC14_CODE_STEP_16_LSB              6
#define DAC14_CODE_STEP_32_LSB              7

/**
 * @brief DAC 14 DAC slew rate setting.
 * @details Specified setting for DAC slew rate of DAC 14 Click driver.
 */
#define DAC14_SLEW_RATE_NO_SLEW             0
#define DAC14_SLEW_RATE_4_US                1
#define DAC14_SLEW_RATE_8_US                2
#define DAC14_SLEW_RATE_12_US               3
#define DAC14_SLEW_RATE_18_US               4
#define DAC14_SLEW_RATE_27_04_US            5
#define DAC14_SLEW_RATE_40_48_US            6
#define DAC14_SLEW_RATE_60_72_US            7
#define DAC14_SLEW_RATE_91_12_US            8
#define DAC14_SLEW_RATE_136_72_US           9
#define DAC14_SLEW_RATE_239_2_US            10
#define DAC14_SLEW_RATE_418_64_US           11
#define DAC14_SLEW_RATE_732_56_US           12
#define DAC14_SLEW_RATE_1282_US             13
#define DAC14_SLEW_RATE_2563_96_US          14
#define DAC14_SLEW_RATE_5127_92_US          15

/**
 * @brief DAC 14 DAC VREF setting.
 * @details Specified setting for DAC VREF of DAC 14 Click driver.
 */
#define DAC14_VREF_EXT                      0
#define DAC14_VREF_VDD                      1
#define DAC14_VREF_INT_1_5X                 2
#define DAC14_VREF_INT_2X                   3
#define DAC14_VREF_INT_3X                   4
#define DAC14_VREF_INT_4X                   5

/**
 * @brief DAC 14 DAC VDD setting.
 * @details Specified setting for DAC VDD of DAC 14 Click driver.
 */
#define DAC14_VDD_3V3                       3.3f
#define DAC14_VDD_5V                        5.0f

/**
 * @brief DAC 14 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 14 Click driver.
 */
#define DAC14_DEVICE_ADDRESS_GND            0x48
#define DAC14_DEVICE_ADDRESS_VCC            0x49
#define DAC14_DEVICE_ADDRESS_SDA            0x4A
#define DAC14_DEVICE_ADDRESS_SCL            0x4B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac14_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC14_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define DAC14_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac14_set

/**
 * @defgroup dac14_map DAC 14 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 14 Click driver.
 */

/**
 * @addtogroup dac14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 14 Click to the selected MikroBUS.
 */
#define DAC14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dac14_map
/*! @} */ // dac14

/**
 * @brief DAC 14 Click driver selector.
 * @details Selects target driver interface of DAC 14 Click driver.
 */
typedef enum
{
    DAC14_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    DAC14_DRV_SEL_I2C       /**< I2C driver descriptor. */

} dac14_drv_t;

/**
 * @brief DAC 14 Click driver interface.
 * @details Definition of driver interface of DAC 14 Click driver.
 */
typedef err_t ( *dac14_master_io_t )( struct dac14_s*, uint8_t, uint16_t* ); /**< Driver serial interface. */

/**
 * @brief DAC 14 Click context object.
 * @details Context object definition of DAC 14 Click driver.
 */
typedef struct dac14_s
{
    digital_in_t int_pin;           /**< Interrupt pin, available only in I2C mode. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    dac14_drv_t  drv_sel;           /**< Master driver interface selector. */

    dac14_master_io_t write_f;      /**< Master write function. */
    dac14_master_io_t read_f;       /**< Master read function. */

} dac14_t;

/**
 * @brief DAC 14 Click configuration object.
 * @details Configuration object definition of DAC 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;             /**< Interrupt pin, available only in I2C mode. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    dac14_drv_t drv_sel;            /**< Master driver interface selector. */

} dac14_cfg_t;

/**
 * @brief DAC 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC14_OK = 0,
    DAC14_ERROR = -1

} dac14_return_value_t;

/*!
 * @addtogroup dac14 DAC 14 Click Driver
 * @brief API for configuring and manipulating DAC 14 Click driver.
 * @{
 */

/**
 * @brief DAC 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac14_cfg_setup ( dac14_cfg_t *cfg );

/**
 * @brief DAC 14 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #dac14_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #dac14_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void dac14_drv_interface_selection ( dac14_cfg_t *cfg, dac14_drv_t drv_sel );

/**
 * @brief DAC 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_init ( dac14_t *ctx, dac14_cfg_t *cfg );

/**
 * @brief DAC 14 default configuration function.
 * @details This function executes a default configuration of DAC 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac14_default_cfg ( dac14_t *ctx );

/**
 * @brief DAC 14 write register function.
 * @details This function writes a desired data word to the selected register.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_write_register ( dac14_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 14 read register function.
 * @details This function reads data word from the selected register.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_read_register ( dac14_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 14 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This pin is available only in I2C mode.
 */
uint8_t dac14_get_int_pin ( dac14_t *ctx );

/**
 * @brief DAC 14 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_check_communication ( dac14_t *ctx );

/**
 * @brief DAC 14 set dac vout enable function.
 * @details This function sets the VOUT power enable bits for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
 * @param[in] vout_pdn : VOUT PDN bits: @li @c 0 - Power-up VOUT-X,
 *                                      @li @c 1 - Power-down VOUT-X with 10 kOhm to AGND,
 *                                      @li @c 2 - Power-down VOUT-X with 100 kOhm to AGND,
 *                                      @li @c 3 - Power-down VOUT-X with Hi-Z to AGND.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_set_dac_vout_enable ( dac14_t *ctx, uint8_t dac, uint8_t vout_pdn );

/**
 * @brief DAC 14 set dac vref function.
 * @details This function sets the voltage reference for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
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
err_t dac14_set_dac_vref ( dac14_t *ctx, uint8_t dac, uint8_t vref );

/**
 * @brief DAC 14 set dac margins function.
 * @details This function sets the DAC margin levels for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
 * @param[in] margin_l : Margin LOW (must be <= Margin HIGH) in a range of DAC data (0-1023).
 * @param[in] margin_h : Margin HIGH (must be >= Margin LOW) in a range of DAC data (0-1023).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_set_dac_margins ( dac14_t *ctx, uint8_t dac, uint16_t margin_l, uint16_t margin_h );

/**
 * @brief DAC 14 set dac data function.
 * @details This function sets the raw DAC data for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
 * @param[in] dac_data : Raw DAC data (0-1023).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_set_dac_data ( dac14_t *ctx, uint8_t dac, uint16_t dac_data );

/**
 * @brief DAC 14 start function gen function.
 * @details This function starts the function generator for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_start_function_gen ( dac14_t *ctx, uint8_t dac );

/**
 * @brief DAC 14 stop function gen function.
 * @details This function stops the function generator for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac14_stop_function_gen ( dac14_t *ctx, uint8_t dac );

/**
 * @brief DAC 14 config function gen function.
 * @details This function configures the function generator for the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] dac : DAC channel: @li @c 0 - DAC0,
 *                               @li @c 1 - DAC1.
 * @param[in] waveform : Waveform signal: @li @c 0 - Triangular wave,
 *                                        @li @c 1 - Sawtooth wave,
 *                                        @li @c 2 - Inverse sawtooth wave,
 *                                        @li @c 4 - Sine wave,
 *                                        @li @c 7 - Disable function generation.
 * @param[in] code_step : Code step setting. Refer to DAC14_CODE_STEP_x macro definitions for more details.
 * @param[in] slew_rate : Slew rate setting. Refer to DAC14_SLEW_RATE_x macro definitions for more details.
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
err_t dac14_config_function_gen ( dac14_t *ctx, uint8_t dac, uint8_t waveform, 
                                  uint8_t code_step, uint8_t slew_rate );

#ifdef __cplusplus
}
#endif
#endif // DAC14_H

/*! @} */ // dac14

// ------------------------------------------------------------------------ END

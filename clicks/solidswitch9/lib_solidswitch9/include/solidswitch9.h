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
 * @file solidswitch9.h
 * @brief This file contains API for SolidSwitch 9 Click Driver.
 */

#ifndef SOLIDSWITCH9_H
#define SOLIDSWITCH9_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup solidswitch9 SolidSwitch 9 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 9 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch9_reg SolidSwitch 9 Registers List
 * @brief List of registers of SolidSwitch 9 Click driver.
 */

/**
 * @addtogroup solidswitch9_reg
 * @{
 */

/**
 * @brief SolidSwitch 9 RAM register list.
 * @details Specified register for RAM register list of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_REG_OUTCTRCR0              0x00
#define SOLIDSWITCH9_REG_OUTCTRCR1              0x01
#define SOLIDSWITCH9_REG_OUTCTRCR2              0x02
#define SOLIDSWITCH9_REG_OUTCTRCR3              0x03
#define SOLIDSWITCH9_REG_OUTCFGR0               0x08
#define SOLIDSWITCH9_REG_OUTCFGR1               0x09
#define SOLIDSWITCH9_REG_OUTCFGR2               0x0A
#define SOLIDSWITCH9_REG_OUTCFGR3               0x0B
#define SOLIDSWITCH9_REG_CHLOFFTCR0             0x10
#define SOLIDSWITCH9_REG_CHLOFFTCR1             0x11
#define SOLIDSWITCH9_REG_SOCR                   0x13
#define SOLIDSWITCH9_REG_CTRL                   0x14
#define SOLIDSWITCH9_REG_OUTSR0                 0x20
#define SOLIDSWITCH9_REG_OUTSR1                 0x21
#define SOLIDSWITCH9_REG_OUTSR2                 0x22
#define SOLIDSWITCH9_REG_OUTSR3                 0x23
#define SOLIDSWITCH9_REG_ADC0SR                 0x28
#define SOLIDSWITCH9_REG_ADC1SR                 0x29
#define SOLIDSWITCH9_REG_ADC2SR                 0x2A
#define SOLIDSWITCH9_REG_ADC3SR                 0x2B
#define SOLIDSWITCH9_REG_ADC9SR                 0x2C
#define SOLIDSWITCH9_REG_CLEAR_ALL_STATUS       0x3F

/**
 * @brief SolidSwitch 9 ROM register list.
 * @details Specified register for ROM register list of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_ROM_COMPANY_CODE           0x00
#define SOLIDSWITCH9_ROM_DEVICE_FAMILY          0x01
#define SOLIDSWITCH9_ROM_PRODUCT_CODE_1         0x02
#define SOLIDSWITCH9_ROM_PRODUCT_CODE_2         0x03
#define SOLIDSWITCH9_ROM_PRODUCT_CODE_3         0x04
#define SOLIDSWITCH9_ROM_VERSION                0x0A
#define SOLIDSWITCH9_ROM_SPI_MODE               0x10
#define SOLIDSWITCH9_ROM_WD_TYPE_1              0x11
#define SOLIDSWITCH9_ROM_WD_BIT_POSITION_1      0x13
#define SOLIDSWITCH9_ROM_WD_BIT_POSITION_2      0x14
#define SOLIDSWITCH9_ROM_SPI_CPHA               0x20
#define SOLIDSWITCH9_ROM_GSB_OPTIONS            0x3E
#define SOLIDSWITCH9_ROM_SW_RESET               0x3F

/*! @} */ // solidswitch9_reg

/**
 * @defgroup solidswitch9_set SolidSwitch 9 Registers Settings
 * @brief Settings for registers of SolidSwitch 9 Click driver.
 */

/**
 * @addtogroup solidswitch9_set
 * @{
 */

/**
 * @brief SolidSwitch 9 global status byte setting.
 * @details Specified setting for global status byte of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_GSB_GSBN                   0x80
#define SOLIDSWITCH9_GSB_RESET                  0x40
#define SOLIDSWITCH9_GSB_SPI_ERROR              0x20
#define SOLIDSWITCH9_GSB_OT_PL_VDS              0x10
#define SOLIDSWITCH9_GSB_T_CASE                 0x08
#define SOLIDSWITCH9_GSB_LOFF                   0x04
#define SOLIDSWITCH9_GSB_OLOFF                  0x02
#define SOLIDSWITCH9_GSB_FAIL_SAFE              0x01

/**
 * @brief SolidSwitch 9 OUTCTRCRx registers setting.
 * @details Specified setting for OUTCTRCRx registers of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_0_PCT    0x0000
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_5_PCT    0x0330
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_10_PCT   0x0660
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_15_PCT   0x0990
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_20_PCT   0x0CC0
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_25_PCT   0x1000
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_30_PCT   0x1330
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_35_PCT   0x1660
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_40_PCT   0x1990
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_45_PCT   0x1CC0
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_50_PCT   0x2000
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_55_PCT   0x2330
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_60_PCT   0x2660
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_65_PCT   0x2990
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_70_PCT   0x2CC0
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_75_PCT   0x3000
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_80_PCT   0x3330
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_85_PCT   0x3660
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_90_PCT   0x3990
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_95_PCT   0x3CC0
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_100_PCT  0x3FF0
#define SOLIDSWITCH9_OUTCTRCRX_DUTY_CR_MASK     0x3FF0
#define SOLIDSWITCH9_OUTCTRCRX_OLOFFCR_EN       0x0004
#define SOLIDSWITCH9_OUTCTRCRX_WDTB             0x0002

/**
 * @brief SolidSwitch 9 OUTCFGRx registers setting.
 * @details Specified setting for OUTCFGRx registers of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_OUTCFGRX_SLOPECR_STANDARD  0x0000
#define SOLIDSWITCH9_OUTCFGRX_SLOPECR_FAST      0x4000
#define SOLIDSWITCH9_OUTCFGRX_SLOPECR_FASTER    0x8000
#define SOLIDSWITCH9_OUTCFGRX_SLOPECR_FASTEST   0xC000
#define SOLIDSWITCH9_OUTCFGRX_SLOPECR_MASK      0xC000
#define SOLIDSWITCH9_OUTCFGRX_CHPHA_MASK        0x1F00
#define SOLIDSWITCH9_OUTCFGRX_CPCR_STOP         0x0000
#define SOLIDSWITCH9_OUTCFGRX_CPCR_START        0x0040
#define SOLIDSWITCH9_OUTCFGRX_CPCR_CONTINUOUS   0x0080
#define SOLIDSWITCH9_OUTCFGRX_CPCR_FILTERED     0x00C0
#define SOLIDSWITCH9_OUTCFGRX_CPCR_MASK         0x00C0
#define SOLIDSWITCH9_OUTCFGRX_PWMFCY_1024       0x0000
#define SOLIDSWITCH9_OUTCFGRX_PWMFCY_2048       0x0010
#define SOLIDSWITCH9_OUTCFGRX_PWMFCY_4096       0x0020
#define SOLIDSWITCH9_OUTCFGRX_PWMFCY_512        0x0030
#define SOLIDSWITCH9_OUTCFGRX_PWMFCY_MASK       0x0030
#define SOLIDSWITCH9_OUTCFGRX_CCR_BULB          0x0000
#define SOLIDSWITCH9_OUTCFGRX_CCR_LED           0x0008
#define SOLIDSWITCH9_OUTCFGRX_CCR_MASK          0x0008
#define SOLIDSWITCH9_OUTCFGRX_DIENCR_EN         0x0004
#define SOLIDSWITCH9_OUTCFGRX_VDSMASK           0x0002

/**
 * @brief SolidSwitch 9 CHLOFFTCR0 register setting.
 * @details Specified setting for CHLOFFTCR0 register of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_CHLOFFTCR0_CH2_LATCH_OFF   0x0000
#define SOLIDSWITCH9_CHLOFFTCR0_CH2_16MS        0x1000
#define SOLIDSWITCH9_CHLOFFTCR0_CH2_32MS        0x2000
#define SOLIDSWITCH9_CHLOFFTCR0_CH2_240MS       0xF000
#define SOLIDSWITCH9_CHLOFFTCR0_CH2_MASK        0xF000
#define SOLIDSWITCH9_CHLOFFTCR0_CH1_LATCH_OFF   0x0000
#define SOLIDSWITCH9_CHLOFFTCR0_CH1_16MS        0x0100
#define SOLIDSWITCH9_CHLOFFTCR0_CH1_32MS        0x0200
#define SOLIDSWITCH9_CHLOFFTCR0_CH1_240MS       0x0F00
#define SOLIDSWITCH9_CHLOFFTCR0_CH1_MASK        0x0F00
#define SOLIDSWITCH9_CHLOFFTCR0_CH0_LATCH_OFF   0x0000
#define SOLIDSWITCH9_CHLOFFTCR0_CH0_16MS        0x0010
#define SOLIDSWITCH9_CHLOFFTCR0_CH0_32MS        0x0020
#define SOLIDSWITCH9_CHLOFFTCR0_CH0_240MS       0x00F0
#define SOLIDSWITCH9_CHLOFFTCR0_CH0_MASK        0x00F0

/**
 * @brief SolidSwitch 9 CHLOFFTCR1 register setting.
 * @details Specified setting for CHLOFFTCR1 register of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_CHLOFFTCR1_CH3_LATCH_OFF   0x0000
#define SOLIDSWITCH9_CHLOFFTCR1_CH3_16MS        0x0010
#define SOLIDSWITCH9_CHLOFFTCR1_CH3_32MS        0x0020
#define SOLIDSWITCH9_CHLOFFTCR1_CH3_240MS       0x00F0
#define SOLIDSWITCH9_CHLOFFTCR1_CH3_MASK        0x00F0

/**
 * @brief SolidSwitch 9 SOCR register setting.
 * @details Specified setting for SOCR register of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_SOCR_CH3_EN                0x0800
#define SOLIDSWITCH9_SOCR_CH2_EN                0x0400
#define SOLIDSWITCH9_SOCR_CH1_EN                0x0200
#define SOLIDSWITCH9_SOCR_CH0_EN                0x0100
#define SOLIDSWITCH9_SOCR_CHX_MASK              0x0F00
#define SOLIDSWITCH9_SOCR_WDTB                  0x0002

/**
 * @brief SolidSwitch 9 CTRL register setting.
 * @details Specified setting for CTRL register of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_CTRL_GOSTBY                0x8000
#define SOLIDSWITCH9_CTRL_UNLOCK                0x4000
#define SOLIDSWITCH9_CTRL_CTDTH_120C            0x0000
#define SOLIDSWITCH9_CTRL_CTDTH_130C            0x1000
#define SOLIDSWITCH9_CTRL_CTDTH_140C            0x2000
#define SOLIDSWITCH9_CTRL_CTDTH_MASK            0x3000
#define SOLIDSWITCH9_CTRL_EN                    0x0800
#define SOLIDSWITCH9_CTRL_PWM_TRIG_RISING       0x0000
#define SOLIDSWITCH9_CTRL_PWM_TRIG_FALLING      0x0400
#define SOLIDSWITCH9_CTRL_PWM_TRIG_MASK         0x0400
#define SOLIDSWITCH9_CTRL_LOCKEN_SLOPECRX       0x0040
#define SOLIDSWITCH9_CTRL_LOCKEN_CCRX           0x0020
#define SOLIDSWITCH9_CTRL_LOCKEN_CHPHAX         0x0010
#define SOLIDSWITCH9_CTRL_LOCKEN_CHLOFFTCRX     0x0008
#define SOLIDSWITCH9_CTRL_LOCKEN_PWM_CLK_SYNC   0x0004
#define SOLIDSWITCH9_CTRL_LOCKEN_MASK           0x007C
#define SOLIDSWITCH9_CTRL_PWMSYNC               0x0002

/**
 * @brief SolidSwitch 9 OUTSRx registers setting.
 * @details Specified setting for OUTSRx registers of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_OUTSRX_DIENSR              0x8000
#define SOLIDSWITCH9_OUTSRX_DIOTP1              0x4000
#define SOLIDSWITCH9_OUTSRX_DIOTP0              0x2000
#define SOLIDSWITCH9_OUTSRX_CHFBSRX             0x1000
#define SOLIDSWITCH9_OUTSRX_VDSFSRX             0x0800
#define SOLIDSWITCH9_OUTSRX_STKFLTRX            0x0400
#define SOLIDSWITCH9_OUTSRX_OLPUSRX             0x0200
#define SOLIDSWITCH9_OUTSRX_CHLOFFSRX           0x0100
#define SOLIDSWITCH9_OUTSRX_RST                 0x0080
#define SOLIDSWITCH9_OUTSRX_SPIE                0x0040
#define SOLIDSWITCH9_OUTSRX_PWMCLOCKLOW         0x0020
#define SOLIDSWITCH9_OUTSRX_VCCUV               0x0010

/**
 * @brief SolidSwitch 9 ADCxSR registers setting.
 * @details Specified setting for ADCxSR registers of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_ADCXSR_ADCXSR_MASK         0x3FF0
#define SOLIDSWITCH9_ADCXSR_SOCRX_EN            0x0004
#define SOLIDSWITCH9_ADCXSR_UPDTSR              0x0002

/**
 * @brief SolidSwitch 9 ADC9SR registers setting.
 * @details Specified setting for ADC9SR registers of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_ADC9SR_ADC9SR_MASK         0x3FF0
#define SOLIDSWITCH9_ADC9SR_UPDTSR              0x0002

/**
 * @brief SolidSwitch 9 device info setting.
 * @details Specified setting for device info of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_INFO_COMPANY_CODE          0x00
#define SOLIDSWITCH9_INFO_DEVICE_FAMILY         0x01
#define SOLIDSWITCH9_INFO_PRODUCT_CODE_1        0x58
#define SOLIDSWITCH9_INFO_PRODUCT_CODE_2        0x56
#define SOLIDSWITCH9_INFO_PRODUCT_CODE_3        0x61

/**
 * @brief SolidSwitch 9 output setting.
 * @details Specified setting for output of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_OUT3                       0x08
#define SOLIDSWITCH9_OUT2                       0x04
#define SOLIDSWITCH9_OUT1                       0x02
#define SOLIDSWITCH9_OUT0                       0x01
#define SOLIDSWITCH9_OUT_MASK                   0x0F
#define SOLIDSWITCH9_OUT_DUTY_0_PCT             0x0000
#define SOLIDSWITCH9_OUT_DUTY_5_PCT             0x0033
#define SOLIDSWITCH9_OUT_DUTY_10_PCT            0x0066
#define SOLIDSWITCH9_OUT_DUTY_15_PCT            0x0099
#define SOLIDSWITCH9_OUT_DUTY_20_PCT            0x00CC
#define SOLIDSWITCH9_OUT_DUTY_25_PCT            0x0100
#define SOLIDSWITCH9_OUT_DUTY_30_PCT            0x0133
#define SOLIDSWITCH9_OUT_DUTY_35_PCT            0x0166
#define SOLIDSWITCH9_OUT_DUTY_40_PCT            0x0199
#define SOLIDSWITCH9_OUT_DUTY_45_PCT            0x01CC
#define SOLIDSWITCH9_OUT_DUTY_50_PCT            0x0200
#define SOLIDSWITCH9_OUT_DUTY_55_PCT            0x0233
#define SOLIDSWITCH9_OUT_DUTY_60_PCT            0x0266
#define SOLIDSWITCH9_OUT_DUTY_65_PCT            0x0299
#define SOLIDSWITCH9_OUT_DUTY_70_PCT            0x02CC
#define SOLIDSWITCH9_OUT_DUTY_75_PCT            0x0300
#define SOLIDSWITCH9_OUT_DUTY_80_PCT            0x0333
#define SOLIDSWITCH9_OUT_DUTY_85_PCT            0x0366
#define SOLIDSWITCH9_OUT_DUTY_90_PCT            0x0399
#define SOLIDSWITCH9_OUT_DUTY_95_PCT            0x03CC
#define SOLIDSWITCH9_OUT_DUTY_100_PCT           0x03FF

/**
 * @brief SolidSwitch 9 default PWM frequency.
 * @details Specified setting for default PWM frequency of SolidSwitch 9 Click driver.
 */
#define SOLIDSWITCH9_DEF_FREQ                   400000
#define SOLIDSWITCH9_DEF_DUTY_CYCLE             0.5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b solidswitch9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SOLIDSWITCH9_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SOLIDSWITCH9_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // solidswitch9_set

/**
 * @defgroup solidswitch9_map SolidSwitch 9 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 9 Click driver.
 */

/**
 * @addtogroup solidswitch9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 9 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.di0  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.di1  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch9_map
/*! @} */ // solidswitch9

/**
 * @brief SolidSwitch 9 Click context object.
 * @details Context object definition of SolidSwitch 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t di0;          /**< Direct input 0 pin. */
    digital_out_t di1;          /**< Direct input 1 pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t pwm_freq;          /**< PWM frequency value. */
    uint8_t status;             /**< Global Status byte, updates on each read/write. */
    uint8_t wdtb;               /**< WDT toggle bit. */

} solidswitch9_t;

/**
 * @brief SolidSwitch 9 Click configuration object.
 * @details Configuration object definition of SolidSwitch 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t di0;             /**< Direct input 0 pin. */
    pin_name_t pwm;             /**< PWM pin. */
    pin_name_t di1;             /**< Direct input 1 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} solidswitch9_cfg_t;

/**
 * @brief SolidSwitch 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH9_OK = 0,
    SOLIDSWITCH9_ERROR = -1

} solidswitch9_return_value_t;

/*!
 * @addtogroup solidswitch9 SolidSwitch 9 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 9 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch9_cfg_setup ( solidswitch9_cfg_t *cfg );

/**
 * @brief SolidSwitch 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch9_init ( solidswitch9_t *ctx, solidswitch9_cfg_t *cfg );

/**
 * @brief SolidSwitch 9 default configuration function.
 * @details This function executes a default configuration of SolidSwitch 9
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solidswitch9_default_cfg ( solidswitch9_t *ctx );
/**
 * @brief SolidSwitch 9 write register function.
 * @details This function writes a 16-bit data value to the specified register 
 * of the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_write_reg ( solidswitch9_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief SolidSwitch 9 read register function.
 * @details This function reads a 16-bit data value from the specified register 
 * of the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_read_reg ( solidswitch9_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief SolidSwitch 9 read and clear register function.
 * @details This function reads and clears a 16-bit register from the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_read_reg_clear ( solidswitch9_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief SolidSwitch 9 read ROM function.
 * @details This function reads an 8-bit value from the ROM address 
 * of the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] addr : ROM address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_read_rom ( solidswitch9_t *ctx, uint8_t addr, uint8_t *data_out );

/**
 * @brief SolidSwitch 9 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch9_set_duty_cycle ( solidswitch9_t *ctx, float duty_cycle );

/**
 * @brief SolidSwitch 9 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch9_pwm_stop ( solidswitch9_t *ctx );

/**
 * @brief SolidSwitch 9 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch9_pwm_start ( solidswitch9_t *ctx );

/**
 * @brief SolidSwitch 9 set DI0 pin function.
 * @details This function sets the logic state of the DI0 pin.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solidswitch9_set_di0_pin ( solidswitch9_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 9 set DI1 pin function.
 * @details This function sets the logic state of the DI1 pin.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solidswitch9_set_di1_pin ( solidswitch9_t *ctx, uint8_t state );

/**
 * @brief SolidSwitch 9 software reset function.
 * @details This function performs a software reset of the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_sw_reset ( solidswitch9_t *ctx );

/**
 * @brief SolidSwitch 9 clear all status function.
 * @details This function clears all status registers on the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_clear_all_status ( solidswitch9_t *ctx );

/**
 * @brief SolidSwitch 9 check information function.
 * @details This function checks the basic device information (company code, family, product code).
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_check_info ( solidswitch9_t *ctx );

/**
 * @brief SolidSwitch 9 unlock write function.
 * @details This function unlocks protected register writing on the SolidSwitch 9 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_unlock_write ( solidswitch9_t *ctx );

/**
 * @brief SolidSwitch 9 set output duty function.
 * @details This function sets the output duty cycle for the selected output channels.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] out_mask : Output mask to select channels.
 * @param[in] duty : Output duty cycle (0-1023).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solidswitch9_set_out_duty ( solidswitch9_t *ctx, uint8_t out_mask, uint16_t duty );

/**
 * @brief SolidSwitch 9 enable outputs function.
 * @details This function enables the selected outputs.
 * @param[in] ctx : Click context object.
 * See #solidswitch9_t object definition for detailed explanation.
 * @param[in] out_mask : Output mask to enable channels.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Must be called at least every 30ms to avoid entering fail-safe mode.
 */
err_t solidswitch9_enable_out ( solidswitch9_t *ctx, uint8_t out_mask );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH9_H

/*! @} */ // solidswitch9

// ------------------------------------------------------------------------ END

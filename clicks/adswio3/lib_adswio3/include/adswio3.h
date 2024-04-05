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
 * @file adswio3.h
 * @brief This file contains API for AD-SWIO 3 Click Driver.
 */

#ifndef ADSWIO3_H
#define ADSWIO3_H

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
 * @addtogroup adswio3 AD-SWIO 3 Click Driver
 * @brief API for configuring and manipulating AD-SWIO 3 Click driver.
 * @{
 */

/**
 * @defgroup adswio3_reg AD-SWIO 3 Registers List
 * @brief List of registers of AD-SWIO 3 Click driver.
 */

/**
 * @addtogroup adswio3_reg
 * @{
 */

/**
 * @brief AD-SWIO 3 description register.
 * @details Specified register for description of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_REG_NOP                               0x00
#define ADSWIO3_REG_CH_FUNC_SETUP                     0x01
#define ADSWIO3_REG_ADC_CONFIG                        0x02
#define ADSWIO3_REG_PWR_OPTIM_CONFIG                  0x03
#define ADSWIO3_REG_DIN_CONFIG1                       0x04
#define ADSWIO3_REG_DIN_CONFIG2                       0x05
#define ADSWIO3_REG_OUTPUT_CONFIG                     0x06
#define ADSWIO3_REG_RTD3W4W_CONFIG                    0x07
#define ADSWIO3_REG_DO_INT_CONFIG                     0x08
#define ADSWIO3_REG_DO_EXT_CONFIG                     0x09
#define ADSWIO3_REG_I_BURNOUT_CONFIG                  0x0A
#define ADSWIO3_REG_DAC_CODE                          0x0B
#define ADSWIO3_REG_DAC_ACTIVE                        0x0D
#define ADSWIO3_REG_GPIO_CONFIG0                      0x35
#define ADSWIO3_REG_GPIO_CONFIG1                      0x36
#define ADSWIO3_REG_GPIO_CONFIG2                      0x37
#define ADSWIO3_REG_GPIO_CONFIG3                      0x38
#define ADSWIO3_REG_FET_LKG_COMP                      0x39
#define ADSWIO3_REG_CHARGE_PUMP                       0x3A
#define ADSWIO3_REG_ADC_CONV_CTRL                     0x3B
#define ADSWIO3_REG_DIAG_ASSIGN                       0x3C
#define ADSWIO3_REG_DIN_COMP_OUT                      0x40
#define ADSWIO3_REG_ALERT_STATUS                      0x41
#define ADSWIO3_REG_LIVE_STATUS                       0x42
#define ADSWIO3_REG_ADC_RESULT1                       0x44
#define ADSWIO3_REG_ADC_RESULT2                       0x46
#define ADSWIO3_REG_ADC_DIAG_RESULT0                  0x53
#define ADSWIO3_REG_ADC_DIAG_RESULT1                  0x54
#define ADSWIO3_REG_ADC_DIAG_RESULT2                  0x55
#define ADSWIO3_REG_ADC_DIAG_RESULT3                  0x56
#define ADSWIO3_REG_DIN_COUNTER                       0x57
#define ADSWIO3_REG_SUPPLY_ALERT_STATUS               0x5B
#define ADSWIO3_REG_ALERT_MASK                        0x5F
#define ADSWIO3_REG_SUPPLY_ALERT_MASK                 0x60
#define ADSWIO3_REG_READ_SELECT                       0x64
#define ADSWIO3_REG_BURST_READ_SEL                    0x65
#define ADSWIO3_REG_PPC_TX                            0x66
#define ADSWIO3_REG_PPC_ACTIVE                        0x6E
#define ADSWIO3_REG_THERM_RST                         0x77
#define ADSWIO3_REG_CMD_KEY                           0x78
#define ADSWIO3_REG_SCRATCH_0                         0x79
#define ADSWIO3_REG_SCRATCH_1                         0x7A
#define ADSWIO3_REG_SILICON_REV                       0x7B
#define ADSWIO3_REG_SILICON_ID0                       0x7C
#define ADSWIO3_REG_SILICON_ID1                       0x7D
#define ADSWIO3_REG_SILICON_ID2                       0x7E
#define ADSWIO3_REG_SILICON_ID3                       0x7F
#define ADSWIO3_REG_HART_ALERT_STATUS                 0x80
#define ADSWIO3_REG_HART_RX                           0x81
#define ADSWIO3_REG_HART_TX                           0x82
#define ADSWIO3_REG_HART_FCR                          0x83
#define ADSWIO3_REG_HART_MCR                          0x84
#define ADSWIO3_REG_HART_RFC                          0x85
#define ADSWIO3_REG_HART_TFC                          0x86
#define ADSWIO3_REG_HART_ALERT_MASK                   0x87
#define ADSWIO3_REG_HART_CONFIG                       0x88
#define ADSWIO3_REG_HART_EVDET_COUNT                  0x89

/*! @} */ // adswio3_reg

/**
 * @defgroup adswio3_set AD-SWIO 3 Registers Settings
 * @brief Settings for registers of AD-SWIO 3 Click driver.
 */

/**
 * @addtogroup adswio3_set
 * @{
 */

/**
 * @brief AD-SWIO 3 function setup selection.
 * @details Function setup selection of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_CH_FUNC_SETUP_ADC                     0x00
#define ADSWIO3_CH_FUNC_SETUP_VTG_OUT                 0x01
#define ADSWIO3_CH_FUNC_SETUP_CURR_OUT                0x02
#define ADSWIO3_CH_FUNC_SETUP_VTG_IN                  0x03
#define ADSWIO3_CH_FUNC_SETUP_CURR_IN_EXT             0x04
#define ADSWIO3_CH_FUNC_SETUP_CURR_IN_LOOP            0x05
#define ADSWIO3_CH_FUNC_SETUP_2WIRE_RES_MEASURE       0x06
#define ADSWIO3_CH_FUNC_SETUP_3WIRE_RES_MEASURE       0x07
#define ADSWIO3_CH_FUNC_SETUP_DIGI_IN_LOG             0x08
#define ADSWIO3_CH_FUNC_SETUP_DIGI_IN_LOOP            0x09
#define ADSWIO3_CH_FUNC_SETUP_CURR_OUT_HART           0x0A
#define ADSWIO3_CH_FUNC_SETUP_CURR_IN_HART_EXT        0x0B
#define ADSWIO3_CH_FUNC_SETUP_CURR_IN_HART_LOOP       0x0C

/**
 * @brief AD-SWIO 3 diagnostics select.
 * @details Diagnostics select of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_DIAG_ASSIGN_AGND                      0x00
#define ADSWIO3_DIAG_ASSIGN_TEMP_SENS                 0x01
#define ADSWIO3_DIAG_ASSIGN_DVCC                      0x02
#define ADSWIO3_DIAG_ASSIGN_AVCC                      0x03
#define ADSWIO3_DIAG_ASSIGN_ALDO1V8                   0x04
#define ADSWIO3_DIAG_ASSIGN_DLDO1V8                   0x05
#define ADSWIO3_DIAG_ASSIGN_REFOUT                    0x06
#define ADSWIO3_DIAG_ASSIGN_AVDD                      0x07
#define ADSWIO3_DIAG_ASSIGN_AVSS                      0x08
#define ADSWIO3_DIAG_ASSIGN_LVIN                      0x09
#define ADSWIO3_DIAG_ASSIGN_SENSEL                    0x0A
#define ADSWIO3_DIAG_ASSIGN_SENSE_EXT1                0x0B
#define ADSWIO3_DIAG_ASSIGN_SENSE_EXT2                0x0C
#define ADSWIO3_DIAG_ASSIGN_DO_VDD                    0x0D
#define ADSWIO3_DIAG_ASSIGN_AGND0                     0x0E
#define ADSWIO3_DIAG_ASSIGN_CURRENT_EXT               0x0F
#define ADSWIO3_DIAG_RESULT_SEL_0                     0x00
#define ADSWIO3_DIAG_RESULT_SEL_1                     0x01
#define ADSWIO3_DIAG_RESULT_SEL_2                     0x02
#define ADSWIO3_DIAG_RESULT_SEL_3                     0x03

/**
 * @brief AD-SWIO 3 readback select register data values.
 * @details Readback select register data values of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_READ_SELECT_SPI_RD_RET_INFO           0x01
#define ADSWIO3_READ_SELECT_AUTO_RD_EN                0x02
#define ADSWIO3_READ_REG_STATUS_BIT                   0x7F

/**
 * @brief AD-SWIO 3 Power Optimization Configuration Register data values.
 * @details Power Optimization Configuration Register data values of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_PWR_OPTIM_CONFIG_SEL_SEN_EXT1         0x00
#define ADSWIO3_PWR_OPTIM_CONFIG_SEL_SEN_EXT2         0x01
#define ADSWIO3_PWR_OPTIM_CONFIG_SEL_SEN_HF           0x02
#define ADSWIO3_PWR_OPTIM_CONFIG_SEL_SEN_LF           0x03
#define ADSWIO3_PWR_OPTIM_CONFIG_SEL_SEN_AGND         0x04
#define ADSWIO3_PWR_OPTIM_CONFIG_LOW_PWR              0x00
#define ADSWIO3_PWR_OPTIM_CONFIG_FULL_PWR             0x01

/**
 * @brief AD-SWIO 3 3-Wire and 4-Wire RTD Configuration Register data values.
 * @details 3-Wire and 4-Wire RTD Configuration Register data values of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_RTD3W4W_CONFIG_RTD_CURR_250UA         0x00
#define ADSWIO3_RTD3W4W_CONFIG_RTD_CURR_500UA         0x01
#define ADSWIO3_RTD3W4W_CONFIG_RTD_CURR_750UA         0x02
#define ADSWIO3_RTD3W4W_CONFIG_RTD_CURR_1MA           0x03
#define ADSWIO3_RTD3W4W_CONFIG_RTD_EXC                0x00
#define ADSWIO3_RTD3W4W_CONFIG_RTD_EXC_SWAP           0x01
#define ADSWIO3_RTD3W4W_CONFIG_RTD_3_WIRE             0x00
#define ADSWIO3_RTD3W4W_CONFIG_RTD_4_WIRE             0x01
#define ADSWIO3_RTD3W4W_CONFIG_BIT_MASK               0xFFF0u

/**
 * @brief AD-SWIO 3 ADC Conversion Control Register data values.
 * @details ADC Conversion Control Register data values of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_ADC_CONV_CTRL_CONV_DIS                0x00
#define ADSWIO3_ADC_CONV_CTRL_CONV_EN                 0x01
#define ADSWIO3_ADC_CONV_CTRL_CONV_DIS                0x00
#define ADSWIO3_ADC_CONV_DIAG_DIS                     0x00
#define ADSWIO3_ADC_CONV_DIAG_EN                      0x01
#define ADSWIO3_ADC_CONV_SEQ_MODE_STBY                0x00
#define ADSWIO3_ADC_CONV_SEQ_START_SGL_CNV            0x01
#define ADSWIO3_ADC_CONV_SEQ_START_CONT_CNV           0x02
#define ADSWIO3_ADC_CONV_SEQ_STOP_CONT_CNV            0x03
#define ADSWIO3_ADC_CONV_RATE_DIAG_20_SPS             0x00
#define ADSWIO3_ADC_CONV_RATE_DIAG_4_8K_SPS           0x01
#define ADSWIO3_ADC_CONV_RATE_DIAG_9_6K_SPS           0x02

/**
 * @brief AD-SWIO 3 ADC Configuration Register data values.
 * @details ADC Configuration Register data values of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_ADC_CONFIG_CNV_RATE_10_SPS            0x00
#define ADSWIO3_ADC_CONFIG_CNV_RATE_20_SPS            0x01
#define ADSWIO3_ADC_CONFIG_CNV_RATE_1_2K_SPS          0x02
#define ADSWIO3_ADC_CONFIG_CNV_RATE_4_8K_SPS          0x03
#define ADSWIO3_ADC_CONFIG_CNV_RATE_9_6K_SPS          0x04
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_P_12V            0x00
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_PM_12V           0x01
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_PM_2_5V          0x02
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_M_2_5V           0x03
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_P_2_5V           0x04
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_P_0_625V         0x05
#define ADSWIO3_ADC_CONFIG_CNV_RANGE_PM_0_104V        0x06
#define ADSWIO3_ADC_CONFIG_CNV1_SENSELF_AGND_SEN      0x00
#define ADSWIO3_ADC_CONFIG_CNV1_SENSELF_SENSELF       0x01
#define ADSWIO3_ADC_CONFIG_CNV1_SENSE_EXT2_EXT1       0x02
#define ADSWIO3_ADC_CONFIG_CNV1_SENSELF_SENSE_EXT1    0x03
#define ADSWIO3_ADC_CONFIG_CNV2_EXT1_AGND_SEN         0x00
#define ADSWIO3_ADC_CONFIG_CNV2_EXT2_AGND_SEN         0x01
#define ADSWIO3_ADC_CONFIG_CNV2_SENSE_EXT2_EXT1       0x02
#define ADSWIO3_ADC_CONFIG_CNV2_AGND_AGND             0x03

/**
 * @brief AD-SWIO 3 DAC resolution value.
 * @details DAC resolution value of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_DAC_CODE_RESOLUTION                   0x3FFFu

/**
 * @brief AD-SWIO 3 GPIO Configuration Register bit mask.
 * @details GPIO Configuration Register bit mask of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_GPIO_CONFIG_SEL_A                     0x00
#define ADSWIO3_GPIO_CONFIG_SEL_B                     0x01
#define ADSWIO3_GPIO_CONFIG_SEL_C                     0x02
#define ADSWIO3_GPIO_CONFIG_SEL_D                     0x03
#define ADSWIO3_GPIO_CONFIG_GPO_DATA_LOW              0x00
#define ADSWIO3_GPIO_CONFIG_GPO_DATA_HIGH             0x01
#define ADSWIO3_GPIO_CONFIG_GP_WK_PD_DIS              0x00
#define ADSWIO3_GPIO_CONFIG_GP_WK_PD_EN               0x01
#define ADSWIO3_GPIO_CONFIG_DATA_LOGIC_LOW            0x00
#define ADSWIO3_GPIO_CONFIG_DATA_LOGIC_HIGH           0x01
#define ADSWIO3_GPIO_CONFIG_MODE_HI                   0x00
#define ADSWIO3_GPIO_CONFIG_MODE_OUT                  0x01
#define ADSWIO3_GPIO_CONFIG_MODE_OUT_IN               0x02
#define ADSWIO3_GPIO_CONFIG_MODE_IN                   0x03
#define ADSWIO3_GPIO_CONFIG_MODE_FET                  0x04
#define ADSWIO3_GPIO_CONFIG_MODE_C_TXD_IN             0x05
#define ADSWIO3_GPIO_CONFIG_MODE_C_TXD_OUT            0x06
#define ADSWIO3_GPIO_CONFIG_MODE_TX_COM               0x07

/**
 * @brief AD-SWIO 3 ADC conversion result selection.
 * @details ADC conversion result selection of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_ADC_RESULT_SEL_1                      0x00
#define ADSWIO3_ADC_RESULT_SEL_2                      0x01
#define ADSWIO3_ADC_RESULT_RESOLUTION                 65536.0f
#define ADSWIO3_ADC_RESULT_RANGE                      12.0f

/**
 * @brief AD-SWIO 3 NTC temperature calculation data.
 * @details NTC temperature calculation data of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_NTC_VTG_AT_25_C                       1.0f
#define ADSWIO3_NTC_TABLE_POS_CALC_N                  0.2f
#define ADSWIO3_NTC_TABLE_POS_CALC_P                  0.5f
#define ADSWIO3_NTC_TABLE_POS_MAX                     9
#define ADSWIO3_NTC_TABLE_NEG_MAX                     13
#define ADSWIO3_NTC_TEMP_AT_1_V                       25.0f

/**
 * @brief AD-SWIO 3 Alert Mask Register bit mask.
 * @details Alert Mask Register bit mask of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_ALERT_SPI_ERR_MASK                    0x0004u
#define ADSWIO3_ALERT_PPC_ERR_MASK                    0x0008u
#define ADSWIO3_ALERT_TEMP_ALERT_MASK                 0x0010u
#define ADSWIO3_ALERT_ADC_ERR_MASK                    0x0020u
#define ADSWIO3_ALERT_DI_SC_ERR_MASK                  0x0040u
#define ADSWIO3_ALERT_DI_OC_ERR_MASK                  0x0080u
#define ADSWIO3_ALERT_DO_THERM_RESET_MASK             0x0100u
#define ADSWIO3_ALERT_DO_EXT_SC_MASK                  0x0200u
#define ADSWIO3_ALERT_DO_INT_SC_MASK                  0x0400u
#define ADSWIO3_ALERT_DO_EXT_TIMEOUT_MASK             0x0800u
#define ADSWIO3_ALERT_DO_INT_TIMEOUT_MASK             0x1000u
#define ADSWIO3_ALERT_ANALOG_IO_SC_MASK               0x2000u
#define ADSWIO3_ALERT_ANALOG_IO_OC_MASK               0x4000u

/**
 * @brief AD-SWIO 3 PPC Transmit and Status Register bit mask.
 * @details PPC Transmit and Status Register bit mask of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_PPC_TX_DATA_BIT_MASK                  0x00FFu
#define ADSWIO3_PPC_TX_AVDD_VTG_MIN                   6.0f
#define ADSWIO3_PPC_TX_AVDD_VTG_DEFAULT               24.00f
#define ADSWIO3_PPC_TX_AVDD_VTG_MAX                   24.20f
#define ADSWIO3_PPC_TX_AVDD_DATA_MAX                  255.0f
#define ADSWIO3_PPC_TX_AVDD_DATA_CALC                 1.0f
#define ADSWIO3_PPC_ACTIVE_TX_BUSY                    0x0100u
#define ADSWIO3_PPC_ACTIVE_PPC_TX_BUSY_ERR            0x0200u
#define ADSWIO3_PPC_ACTIVE_PPC_TX_ACK_ERR             0x0400u

/**
 * @brief AD-SWIO 3 Digital Input Configuration Register bit mask.
 * @details Digital Input Configuration Register bit mask of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_DIN_CONFIG2_DIN_THRESH_MODE           0x0080u
#define ADSWIO3_SENS_SEL_TRSH_MULTI                   50.0f
#define ADSWIO3_SENS_SEL_SCALE_MULTI                  60.0f
#define ADSWIO3_SENS_SEL_TRSH_CORR_VAL                20.0f

/**
 * @brief AD-SWIO 3 Current Flowing Through RSET in Internal Digital Output Mode Selection.
 * @details Current Flowing Through RSET in Internal Digital Output Mode Selection
 * of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_DIGI_OUT_MODE_SRC                      0.3125f
#define ADSWIO3_DIGI_OUT_MODE_SNK                      2.5f

/**
 * @brief AD-SWIO 3 diagnostic function voltage calculation.
 * @details Diagnostic function voltage calculation of AD-SWIO 3 Click driver.
 */
#define ADSWIO3_CALC_DIAG_AGND( DIAG_ADC )         ( DIAG_ADC / 65536.0f ) * 2.5f
#define ADSWIO3_CALC_DIAG_SENS_TEMP( DIAG_ADC )    ( DIAG_ADC / 8.95f ) - 40.0f
#define ADSWIO3_CALC_DIAG_DVCC( DIAG_ADC )         ( DIAG_ADC / 65536.0f ) * 8.25f
#define ADSWIO3_CALC_DIAG_ALDO1V8( DIAG_ADC )      ( DIAG_ADC / 65536.0f ) * 5.825f
#define ADSWIO3_CALC_DIAG_DLDO1V8( DIAG_ADC )      ( DIAG_ADC / 65536.0f ) * 7.5f
#define ADSWIO3_CALC_DIAG_REFOUT( DIAG_ADC )       ( DIAG_ADC / 65536.0f ) * 3.125f
#define ADSWIO3_CALC_DIAG_LVIN( DIAG_ADC )         ( DIAG_ADC / 65536.0f ) * 2.5f
#define ADSWIO3_CALC_DIAG_SENSE_EXT( DIAG_ADC )    ( ( DIAG_ADC / 65536.0f ) * 50.0f ) - 20.0f
#define ADSWIO3_CALC_DIAG_DO_VDD( DIAG_ADC )       ( DIAG_ADC / 65536.0f ) * 49.2f
#define ADSWIO3_CALC_DIAG_CURRENT( DIAG_ADC )      ( DIAG_ADC / 65536.0f ) / 1.38f
#define ADSWIO3_CALC_DIAG_VTG_AVDD( DIAG_ADC )     ( DIAG_ADC / 65536.0f ) * 50.0f
#define ADSWIO3_CALC_DIAG_VTG_AVSS( DIAG_ADC )     ( ( DIAG_ADC / 65536.0f ) * 31.017f ) - 20.0f
#define ADSWIO3_CALC_DIAG_VTG_AVCC( DIAG_ADC )     ( DIAG_ADC / 65536.0f ) * 17.5f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adswio3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADSWIO3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADSWIO3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adswio3_set

/**
 * @defgroup adswio3_map AD-SWIO 3 MikroBUS Map
 * @brief MikroBUS pin mapping of AD-SWIO 3 Click driver.
 */

/**
 * @addtogroup adswio3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AD-SWIO 3 Click to the selected MikroBUS.
 */
#define ADSWIO3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.alr  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adswio3_map
/*! @} */ // adswio3

/**
 * @brief AD-SWIO 3 Click context object.
 * @details Context object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;  /**< Reset pin. */

    // Input pins
    digital_in_t rdy;    /**< Ready pin. */
    digital_in_t alr;    /**< Alarm pin. */

    // Modules
    spi_master_t spi;          /**< SPI driver object. */

    pin_name_t   chip_select;  /**< Chip select pin descriptor (used for SPI driver). */

    float dig_out_mode;    /**< Internal digital output mode selection (sourcing/sinking). */

} adswio3_t;

/**
 * @brief AD-SWIO 3 Click configuration object.
 * @details Configuration object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t rdy;    /**< Ready pin. */
    pin_name_t alr;    /**< Alarm pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adswio3_cfg_t;

/**
 * @brief AD-SWIO 3 Click ADC configuration object.
 * @details ADC configuration object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    uint8_t  conv2_rate;     /**< ADC Conversion Rate 2. */
    uint8_t  conv1_rate;     /**< ADC Conversion Rate 1. */
    uint8_t  conv2_range;    /**< ADC Range for Conversion 2. */
    uint8_t  conv1_range;    /**< ADC Range for Conversion 1. */
    uint8_t  conv2_mux;      /**< ADC Input Node for Conversion 2. */
    uint8_t  conv1_mux;      /**< ADC Input Node for Conversion 1. */

} adswio3_adc_cfg_t;

/**
 * @brief AD-SWIO 3 Click output configuration object.
 * @details Output configuration object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    uint8_t  vout_range;       /**< Voltage Output Range. */
    uint8_t  slew_en;          /**< Selects DAC Slew Option. */
    uint8_t  slew_lin_step;    /**< Step Size for Digital Linear Slew. */
    uint8_t  slew_lin_rate;    /**< Update Rate for Digital Linear Slew. */
    uint8_t  i_limit;          /**< Sink and Source Current Limits in Output Modes. */

} adswio3_output_cfg_t;

/**
 * @brief AD-SWIO 3 Click ADC conversion control object.
 * @details ADC conversion control object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    uint8_t  conv_rate_diag;    /**< Conversion Rate for Diagnostics. */
    uint8_t  conv_seq;          /**< Single or Continuous Mode. */
    uint8_t  diag_3_en;         /**< Enable Conversions on Diagnostic 3. */
    uint8_t  diag_2_en;         /**< Enable Conversions on Diagnostic 2. */
    uint8_t  diag_1_en;         /**< Enable Conversions on Diagnostic 1. */
    uint8_t  diag_0_en;         /**< Enable Conversions on Diagnostic 0. */
    uint8_t  conv2_en;          /**< Enable Conversions on Conversion 2. */
    uint8_t  conv1_en;          /**< Enable Conversions on Conversion 1. */

} adswio3_adc_cnv_ctrl_t;

/**
 * @brief AD-SWIO 3 Click the alert status object.
 * @details Alert status object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    uint8_t  hart_alert;        /**< HART Communications Alert. */
    uint8_t  analog_io_oc;      /**< Analog Input or Output Open-Circuit Detected. */
    uint8_t  analog_io_sc;      /**< Analog Input or Output Short-Circuit Detected. */
    uint8_t  do_int_timeout;    /**< Digital Output Internal Short-Circuit Timeout. */
    uint8_t  do_ext_timeout;    /**< Digital Output External Short-Circuit Timeout. */
    uint8_t  do_int_sc;         /**< Digital Output Internal Short-Circuit Detected. */
    uint8_t  do_ext_sc;         /**< Digital Output External Short-Circuit Detected. */
    uint8_t  do_therm_reset;    /**< Internal Digital Output Thermal Reset Occurred. */
    uint8_t  di_oc_err;         /**< Digital Input Open-Circuit Error. */
    uint8_t  di_sc_err;         /**< Digital Input Short-Circuit Error. */
    uint8_t  adc_err;           /**< ADC Conversion or Saturation Error. */
    uint8_t  temp_alert;        /**< High Temperature Detected. */
    uint8_t  ppc_err;           /**< PPC Error Detected. */
    uint8_t  spi_err;           /**< SPI Error Detected. */
    uint8_t  supply_err;        /**< Supply Error. */
    uint8_t  reset_occurred;    /**< Reset Occurred. */

} adswio3_alert_status_t;

/**
 * @brief AD-SWIO 3 Click live status object.
 * @details Live status object definition of AD-SWIO 3 Click driver.
 */
typedef struct
{
    uint8_t  analog_io_oc_status;      /**< Current Status of Analog Input or Output Open-Circuit. */
    uint8_t  analog_io_sc_status;      /**< Current Status of Analog Input or Output Short-Circuit. */
    uint8_t  do_int_sc_status;         /**< Current Status of Internal Digital Output Short-Circuit Alert. */
    uint8_t  do_ext_sc_status;         /**< Current Status of External Digital Output Short-Circuit Alert. */
    uint8_t  do_therm_reset_status;    /**< Current Status of Digital Output Thermal Reset. */
    uint8_t  di_oc_status;             /**< Current Status of Digital Input Open-Circuit.  */
    uint8_t  di_sc_status;             /**< Current Status of Digital Input Short-Circuit.  */
    uint8_t  temp_alert_status;        /**< Current Status of TEMP_ALERT. */
    uint8_t  adc_data_rdy;             /**< ADC Data Ready. */
    uint8_t  adc_busy;                 /**< ADC Busy Status. */
    uint8_t  supply_status;            /**< Current Status of the SUPPLY_ALERT_STATUS. */

} adswio3_live_status_t;


/**
 * @brief AD-SWIO 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADSWIO3_OK = 0,
    ADSWIO3_ERROR = -1

} adswio3_return_value_t;

/*!
 * @addtogroup adswio3 AD-SWIO 3 Click Driver
 * @brief API for configuring and manipulating AD-SWIO 3 Click driver.
 * @{
 */

/**
 * @brief AD-SWIO 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adswio3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adswio3_cfg_setup ( adswio3_cfg_t *cfg );

/**
 * @brief AD-SWIO 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adswio3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_init ( adswio3_t *ctx, adswio3_cfg_t *cfg );

/**
 * @brief AD-SWIO 3 default configuration function.
 * @details This function executes a default configuration of AD-SWIO 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adswio3_default_cfg ( adswio3_t *ctx );

/**
 * @brief AD-SWIO 3 HW reset function.
 * @details This function performs a hardware reset 
 * of the ADP1034, 3-Channel Isolated Micropower Management Unit 
 * with Seven Digital Isolators and Programmable Power Control
 * on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void adswio3_hw_reset ( adswio3_t *ctx );

/**
 * @brief AD-SWIO 3 data writing function.
 * @details This function writes a desired data byte to
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_register_write ( adswio3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief AD-SWIO 3 data reading function.
 * @details This function reads a desired data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_register_read ( adswio3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief AD-SWIO 3 select the channel function.
 * @details This function sets the channel function
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] ch_fun : Sets the channel function [0x00-0x0C].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Values other than those listed as follows select the high impedance function.
 */
err_t adswio3_function_setup ( adswio3_t *ctx, uint8_t ch_fun );

/**
 * @brief AD-SWIO 3 select the ADC config function.
 * @details This function selects the ADC configuration for the input and output channel
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] adc_config : ADC config object.
 * See #adswio3_adc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_adc_config ( adswio3_t *ctx, adswio3_adc_cfg_t adc_config );

/**
 * @brief AD-SWIO 3 set power optimization function.
 * @details This function settings to allow for power optimization of the channel
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] buff_sel : Buffer selection.
 * @param[in] buff_mode : Buffer mode (Enable/Disable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_pwr_optim_config ( adswio3_t *ctx, uint8_t buff_sel, uint8_t buff_mode );

/**
 * @brief AD-SWIO 3 configures the output settings function.
 * @details This function configures the output settings of the channel
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] out_cfg : Output settings of the channel object.
 * See #adswio3_output_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_output_config ( adswio3_t *ctx, adswio3_output_cfg_t out_cfg );

/**
 * @brief AD-SWIO 3 RTD configuration function.
 * @details This function configures the 3-wire and 4-wire RTD measurements
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] rtd_mode_sel : 3-Wire or 4-Wire RTD Mode Select. 
 * @param[in] rtd_exc_swap : 3-Wire RTD Excitation Swap.
 * @param[in] rtd_current : RTD Current.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_rtd_config ( adswio3_t *ctx, uint8_t rtd_mode_sel, uint8_t rtd_exc_swap, uint8_t rtd_current );

/**
 * @brief AD-SWIO 3 sets the DAC code for the output function.
 * @details This function is used to set the DAC code for the output functions
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] dac_code : DAC Code Data for the Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_set_dac_code ( adswio3_t *ctx, uint16_t dac_code );

/**
 * @brief AD-SWIO 3 GPIO configuration function.
 * @details This function is used to configure the four GPIO_x pins
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO selection.
 * @param[in] gpo_data : GPIO drive a logic data.
 * @param[in] gp_wk_pd_en : Pad Weak Pull-Down Enable.
 * @param[in] out_mode : Select the General-Purpose Output Mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_set_gpio_config ( adswio3_t *ctx, uint8_t gpio_sel, uint8_t gpo_data, 
                                                uint8_t gp_wk_pd_en, uint8_t out_mode );

/**
 * @brief AD-SWIO 3 ADC conversion control function.
 * @details This function is used to control the ADC conversions that must be performed
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] out_cfg : ADC conversion control object.
 * See #adswio3_adc_cnv_ctrl_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_set_adc_cnv ( adswio3_t *ctx, adswio3_adc_cnv_ctrl_t adc_cnv_ctrl );

/**
 * @brief AD-SWIO 3 assigns diagnostics function.
 * @details This function is used to assign diagnostics 
 * to the four available diagnostics inputs
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] diag_0 : Select the Diagnostic Assigned to Diagnostic 0.
 * @param[in] diag_1 : Select the Diagnostic Assigned to Diagnostic 1.
 * @param[in] diag_2 : Select the Diagnostic Assigned to Diagnostic 2.
 * @param[in] diag_3 : Select the Diagnostic Assigned to Diagnostic 3.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_set_diag_assign ( adswio3_t *ctx, uint8_t diag_0, uint8_t diag_1, 
                                                uint8_t diag_2, uint8_t diag_3 );

/**
 * @brief AD-SWIO 3 get status function.
 * @details This function is used to read alert status and live status
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] alert_status : Alert status object.
 * See #adswio3_alert_status_t object definition for detailed explanation.
 * @param[in] live_status : Live status object.
 * See #adswio3_live_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_get_status ( adswio3_t *ctx, adswio3_alert_status_t *alert_status, 
                                           adswio3_live_status_t *live_status );

/**
 * @brief AD-SWIO 3 gets the ADC conversion result function.
 * @details This function is used to read the result of the desired ADC conversion
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] adc_sel : ADC conversion result selection [0-1].
 * @param[out] adc_data : 16-bit ADC conversion result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_get_adc_res ( adswio3_t *ctx, uint8_t adc_sel, uint16_t *adc_data );

/**
 * @brief AD-SWIO 3 gets the voltage input function.
 * @details This function reads the raw ADC value 
 * and converts them to a proportional voltage level 
 * measured by the voltage between the I/OP and I/ON screw terminals
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] adc_sel : ADC conversion result selection [0-1].
 * @param[out] voltage : Input voltage level [0V-12V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_get_voltage_input ( adswio3_t *ctx, uint8_t adc_sel, float *voltage );

/**
 * @brief AD-SWIO 3 gets the diagnostic conversion results function.
 * @details This function is used to read the desired diagnostic conversion results
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] diag_sel : Diagnostic conversion results selection [0-3].
 * @param[out] adc_diag_data : 16-bit diagnostic conversion results.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_get_diag_res ( adswio3_t *ctx, uint8_t diag_sel, uint16_t *adc_diag_data );

/**
 * @brief AD-SWIO 3 gets the diagnostic conversion results function.
 * @details This function reads the diagnostic conversion results 
 * and converts them to a proportional voltage level 
 * by calculating the value of the measured quantity
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] diag_sel : Diagnostic conversion results selection [0-3].
 * @param[out] diag_vtg : The voltage level of the selected diagnostics.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Voltage level depends on the diagnostics assigned 
 * to the one of four available diagnostics inputs.
 */
err_t adswio3_get_diag_vtg ( adswio3_t *ctx, uint8_t diag_sel, float *diag_vtg );

/**
 * @brief AD-SWIO 3 gets the NTC temperature function.
 * @details This function reads the diagnostic conversion results 
 * and converts them to an NTC thermistor temperature in degrees Celsius
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] diag_sel : Diagnostic conversion results selection [0-3].
 * @param[out] ntc_temp : NTC temperature (degrees Celsius).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_get_ntc_temp ( adswio3_t *ctx, uint8_t diag_sel, float *ntc_temp );

/**
 * @brief AD-SWIO 3 sets the alert mask function.
 * @details This function is used to mask specific status bits 
 * from activating the ALERT pin
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] alert_mask : Alert bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adswio3_set_alert_mask ( adswio3_t *ctx, uint16_t alert_mask );

/**
 * @brief AD-SWIO 3 power control voltage configuration function.
 * @details This function configures power control voltage level
 * of the AD74115H, Single-Channel, Software Configurable Input 
 * and Output with HART Modem on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @param[in] ppc_vtg : Alert bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note  PPC voltage reset to the maximum power supply voltage 
 * that matches the ADP1034 configuration. 
 * Note that once these PPC voltages are updated, 
 * further writes are blocked until the transmission completes.
 */
err_t adswio3_set_ppc_vtg ( adswio3_t *ctx, float ppc_vtg );

/**
 * @brief AD-SWIO 3 gets the ready pin function.
 * @details This function gets states of the RDY [PWM] pin
 * of the ADP1034, 3-Channel Isolated Micropower Management Unit 
 * with Seven Digital Isolators and Programmable Power Control
 * on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t adswio3_get_ready ( adswio3_t *ctx );

/**
 * @brief AD-SWIO 3 gets the alarm pin function.
 * @details This function gets states of the ALR [INT] pin
 * of the ADP1034, 3-Channel Isolated Micropower Management Unit 
 * with Seven Digital Isolators and Programmable Power Control
 * on the AD-SWIO 3 Click board.
 * @param[in] ctx : Click context object.
 * See #adswio3_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t adswio3_get_alarm ( adswio3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ADSWIO3_H

/*! @} */ // adswio3

// ------------------------------------------------------------------------ END

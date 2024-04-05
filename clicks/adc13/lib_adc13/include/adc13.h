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
 * @file adc13.h
 * @brief This file contains API for ADC 13 Click Driver.
 */

#ifndef ADC13_H
#define ADC13_H

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
#include "math.h"

/*!
 * @addtogroup adc13 ADC 13 Click Driver
 * @brief API for configuring and manipulating ADC 13 Click driver.
 * @{
 */

/**
 * @defgroup adc13_cmd ADC 13 Commands List
 * @brief List of commands of ADC 13 Click driver.
 */

/**
 * @addtogroup adc13_cmd
 * @{
 */

/**
 * @brief ADC 13 commands list.
 * @details Specified commands for ADC of ADC 13 Click driver.
 */
#define ADC13_CMD_NOP                       0x00
#define ADC13_CMD_RESET                     0x06
#define ADC13_CMD_START1                    0x08
#define ADC13_CMD_STOP1                     0x0A
#define ADC13_CMD_START2                    0x0C
#define ADC13_CMD_STOP2                     0x0E
#define ADC13_CMD_RDATA1                    0x12
#define ADC13_CMD_RDATA2                    0x14
#define ADC13_CMD_SYOCAL1                   0x16
#define ADC13_CMD_SYGCAL1                   0x17
#define ADC13_CMD_SFOCAL1                   0x19
#define ADC13_CMD_SYOCAL2                   0x1B
#define ADC13_CMD_SYGCAL2                   0x1C
#define ADC13_CMD_SFOCAL2                   0x1E
#define ADC13_CMD_RREG                      0x20 
#define ADC13_CMD_WREG                      0x40 

/*! @} */ // adc13_cmd

/**
 * @defgroup adc13_reg ADC 13 Registers List
 * @brief List of registers of ADC 13 Click driver.
 */

/**
 * @addtogroup adc13_reg
 * @{
 */

/**
 * @brief ADC 13 register map.
 * @details Specified register map of ADC 13 Click driver.
 */
#define ADC13_REG_ID                        0x00
#define ADC13_REG_POWER                     0x01
#define ADC13_REG_INTERFACE                 0x02
#define ADC13_REG_MODE0                     0x03
#define ADC13_REG_MODE1                     0x04
#define ADC13_REG_MODE2                     0x05
#define ADC13_REG_INPMUX                    0x06
#define ADC13_REG_OFCAL0                    0x07
#define ADC13_REG_OFCAL1                    0x08
#define ADC13_REG_OFCAL2                    0x09
#define ADC13_REG_FSCAL0                    0x0A
#define ADC13_REG_FSCAL1                    0x0B
#define ADC13_REG_FSCAL2                    0x0C
#define ADC13_REG_IDACMUX                   0x0D
#define ADC13_REG_IDACMAG                   0x0E
#define ADC13_REG_REFMUX                    0x0F
#define ADC13_REG_TDACP                     0x10
#define ADC13_REG_TDACN                     0x11
#define ADC13_REG_GPIOCON                   0x12
#define ADC13_REG_GPIODIR                   0x13
#define ADC13_REG_GPIODAT                   0x14

/*! @} */ // adc13_reg

/**
 * @defgroup adc13_set ADC 13 Registers Settings
 * @brief Settings for registers of ADC 13 Click driver.
 */

/**
 * @addtogroup adc13_set
 * @{
 */

/**
 * @brief ADC 13 register mask summary.
 * @details The list of register masks.
 */
#define ADC13_ID_DEV_MASK                   0xE0
#define ADC13_ID_REV_MASK                   0x1F
#define ADC13_POWER_RESET_MASK              0x10
#define ADC13_POWER_VBIAS_MASK              0x02
#define ADC13_POWER_INTREF_MASK             0x01
#define ADC13_INTERFACE_TIMEOUT_MASK        0x08
#define ADC13_INTERFACE_STATUS_MASK         0x04
#define ADC13_INTERFACE_CRC_MASK            0x03
#define ADC13_MODE0_REFREV_MASK             0x80
#define ADC13_MODE0_RUN_MODE_MASK           0x40
#define ADC13_MODE0_CHOP_MASK               0x30
#define ADC13_MODE0_DELAY_MASK              0x0F
#define ADC13_MODE1_FILTER_MASK             0xE0
#define ADC13_MODE1_SBADC_MASK              0x10
#define ADC13_MODE1_SBPOL_MASK              0x08
#define ADC13_MODE1_SBMAG_MASK              0x07
#define ADC13_MODE2_BYPASS_MASK             0x80
#define ADC13_MODE2_GAIN_MASK               0x70
#define ADC13_MODE2_DR_MASK                 0x0F
#define ADC13_INPMUX_MUXP_MASK              0xF0
#define ADC13_INPMUX_MUXN_MASK              0x0F
#define ADC13_IDACMUX_MUX2_MASK             0xF0
#define ADC13_IDACMUX_MUX1_MASK             0x0F
#define ADC13_IDACMAG_MAG2_MASK             0xF0
#define ADC13_IDACMAG_MAG1_MASK             0x0F
#define ADC13_REFMUX_RMUXP_MASK             0x38
#define ADC13_REFMUX_RMUXN_MASK             0x07
#define ADC13_TDACP_OUTP_MASK               0x80
#define ADC13_TDACP_MAGP_MASK               0x1F
#define ADC13_TDACN_OUTN_MASK               0x80
#define ADC13_TDACN_MAGN_MASK               0x1F
#define ADC13_REG_COUNT_MASK                0x1F

/**
 * @brief ADC 13 STATUS byte field bits.
 * @details Specified bits for STATUS byte field of ADC 13 Click driver.
 */
#define ADC13_STATUS_ADC2_NEW_DATA          0x80
#define ADC13_STATUS_ADC1_NEW_DATA          0x40
#define ADC13_STATUS_EXTCLK_EXTERNAL        0x20
#define ADC13_STATUS_REF_ALM_LOW_REF        0x10
#define ADC13_STATUS_PGAL_ALM_LOW_VOLTAGE   0x08
#define ADC13_STATUS_PGAH_ALM_HIGH_VOLTAGE  0x04
#define ADC13_STATUS_PGAD_ALM_DIFF_RANGE    0x02
#define ADC13_STATUS_RESET_OCCURRED         0x01

/**
 * @brief ADC 13 POWER register setting.
 * @details Specified setting for POWER register of ADC 13 Click driver.
 */
#define ADC13_POWER_RESET_NO_NEW_RESET      0
#define ADC13_POWER_RESET_OCCURRED          1
#define ADC13_POWER_VBIAS_DISABLE           0
#define ADC13_POWER_VBIAS_ENABLE            1
#define ADC13_POWER_INTREF_DISABLE          0
#define ADC13_POWER_INTREF_ENABLE           1

/**
 * @brief ADC 13 INTERFACE register setting.
 * @details Specified setting for INTERFACE register of ADC 13 Click driver.
 */
#define ADC13_INTERFACE_TIMEOUT_DISABLE     0
#define ADC13_INTERFACE_TIMEOUT_ENABLE      1
#define ADC13_INTERFACE_STATUS_DISABLE      0
#define ADC13_INTERFACE_STATUS_ENABLE       1
#define ADC13_INTERFACE_CRC_DISABLE         0
#define ADC13_INTERFACE_CRC_ENABLE_CHECKSUM 1
#define ADC13_INTERFACE_CRC_ENABLE_CRC      2

/**
 * @brief ADC 13 MODE0 register setting.
 * @details Specified setting for MODE0 register of ADC 13 Click driver.
 */
#define ADC13_MODE0_REFREV_NORMAL           0
#define ADC13_MODE0_REFREV_REVERSE          1
#define ADC13_MODE0_RUN_MODE_CONTINUOUS     0
#define ADC13_MODE0_RUN_MODE_ONE_SHOT       1
#define ADC13_MODE0_CHOP_DISABLE            0
#define ADC13_MODE0_CHOP_ENABLE             1
#define ADC13_MODE0_CHOP_IDAC_ENABLE        2
#define ADC13_MODE0_CHOP_AND_IDAC_ENABLE    3
#define ADC13_MODE0_DELAY_NO_DELAY          0
#define ADC13_MODE0_DELAY_8p7uS             1
#define ADC13_MODE0_DELAY_17uS              2
#define ADC13_MODE0_DELAY_35uS              3
#define ADC13_MODE0_DELAY_69uS              4
#define ADC13_MODE0_DELAY_139uS             5
#define ADC13_MODE0_DELAY_278uS             6
#define ADC13_MODE0_DELAY_555uS             7
#define ADC13_MODE0_DELAY_1p1mS             8
#define ADC13_MODE0_DELAY_2p2mS             9
#define ADC13_MODE0_DELAY_4p4mS             10
#define ADC13_MODE0_DELAY_8p8mS             11

/**
 * @brief ADC 13 MODE1 register setting.
 * @details Specified setting for MODE1 register of ADC 13 Click driver.
 */
#define ADC13_MODE1_FILTER_SINC1_MODE       0
#define ADC13_MODE1_FILTER_SINC2_MODE       1
#define ADC13_MODE1_FILTER_SINC3_MODE       2
#define ADC13_MODE1_FILTER_SINC4_MODE       3
#define ADC13_MODE1_FILTER_FIR_MODE         4
#define ADC13_MODE1_SBADC_ADC1_OUT          0
#define ADC13_MODE1_SBADC_ADC2_OUT          1
#define ADC13_MODE1_SBPOL_PULLUP_MODE       0
#define ADC13_MODE1_SBPOL_PULLDOWN_MODE     1
#define ADC13_MODE1_SBMAG_NO_CURR_NO_RES    0
#define ADC13_MODE1_SBMAG_0p5uA_CURR        1
#define ADC13_MODE1_SBMAG_2uA_CURR          2
#define ADC13_MODE1_SBMAG_10uA_CURR         3
#define ADC13_MODE1_SBMAG_50uA_CURR         4
#define ADC13_MODE1_SBMAG_200uA_CURR        5
#define ADC13_MODE1_SBMAG_10MOHM_RES        6

/**
 * @brief ADC 13 MODE2 register setting.
 * @details Specified setting for MODE2 register of ADC 13 Click driver.
 */
#define ADC13_MODE2_BYPASS_PGA_ENABLED      0
#define ADC13_MODE2_BYPASS_PGA_BYPASSED     1
#define ADC13_MODE2_GAIN_1                  0
#define ADC13_MODE2_GAIN_2                  1
#define ADC13_MODE2_GAIN_4                  2
#define ADC13_MODE2_GAIN_8                  3
#define ADC13_MODE2_GAIN_16                 4
#define ADC13_MODE2_GAIN_32                 5
#define ADC13_MODE2_DR_2p5SPS               0
#define ADC13_MODE2_DR_5SPS                 1
#define ADC13_MODE2_DR_10SPS                2
#define ADC13_MODE2_DR_16p6SPS              3
#define ADC13_MODE2_DR_20SPS                4
#define ADC13_MODE2_DR_50SPS                5
#define ADC13_MODE2_DR_60SPS                6
#define ADC13_MODE2_DR_100SPS               7
#define ADC13_MODE2_DR_400SPS               8
#define ADC13_MODE2_DR_1200SPS              9
#define ADC13_MODE2_DR_2400SPS              10
#define ADC13_MODE2_DR_4800SPS              11
#define ADC13_MODE2_DR_7200SPS              12
#define ADC13_MODE2_DR_14400SPS             13
#define ADC13_MODE2_DR_19200SPS             14
#define ADC13_MODE2_DR_38400SPS             15

/**
 * @brief ADC 13 INPMUX register setting.
 * @details Specified setting for INPMUX register of ADC 13 Click driver.
 */
#define ADC13_INPMUX_MUXP_AIN0              0
#define ADC13_INPMUX_MUXP_AIN1              1
#define ADC13_INPMUX_MUXP_AIN2              2
#define ADC13_INPMUX_MUXP_AIN3              3
#define ADC13_INPMUX_MUXP_AIN4              4
#define ADC13_INPMUX_MUXP_AIN5              5
#define ADC13_INPMUX_MUXP_AIN6              6
#define ADC13_INPMUX_MUXP_AIN7              7
#define ADC13_INPMUX_MUXP_AIN8              8
#define ADC13_INPMUX_MUXP_AIN9              9
#define ADC13_INPMUX_MUXP_AINCOM            10
#define ADC13_INPMUX_MUXP_TEMP_SENSOR_POS   11
#define ADC13_INPMUX_MUXP_AN_POW_SUPP_POS   12
#define ADC13_INPMUX_MUXP_DIG_POW_SUPP_POS  13
#define ADC13_INPMUX_MUXP_TDAC_POS          14
#define ADC13_INPMUX_MUXP_FLOAT             15
#define ADC13_INPMUX_MUXN_AIN0              0
#define ADC13_INPMUX_MUXN_AIN1              1
#define ADC13_INPMUX_MUXN_AIN2              2
#define ADC13_INPMUX_MUXN_AIN3              3
#define ADC13_INPMUX_MUXN_AIN4              4
#define ADC13_INPMUX_MUXN_AIN5              5
#define ADC13_INPMUX_MUXN_AIN6              6
#define ADC13_INPMUX_MUXN_AIN7              7
#define ADC13_INPMUX_MUXN_AIN8              8
#define ADC13_INPMUX_MUXN_AIN9              9
#define ADC13_INPMUX_MUXN_AINCOM            10
#define ADC13_INPMUX_MUXN_TEMP_SENSOR_NEG   11
#define ADC13_INPMUX_MUXN_AN_POW_SUPP_NEG   12
#define ADC13_INPMUX_MUXN_DIG_POW_SUPP_NEG  13
#define ADC13_INPMUX_MUXN_TDAC_NEG          14
#define ADC13_INPMUX_MUXN_FLOAT             15

/**
 * @brief ADC 13 IDACMUX register setting.
 * @details Specified setting for IDACMUX register of ADC 13 Click driver.
 */
#define ADC13_IDACMUX_MUX2_AIN0              0
#define ADC13_IDACMUX_MUX2_AIN1              1
#define ADC13_IDACMUX_MUX2_AIN2              2
#define ADC13_IDACMUX_MUX2_AIN3              3
#define ADC13_IDACMUX_MUX2_AIN4              4
#define ADC13_IDACMUX_MUX2_AIN5              5
#define ADC13_IDACMUX_MUX2_AIN6              6
#define ADC13_IDACMUX_MUX2_AIN7              7
#define ADC13_IDACMUX_MUX2_AIN8              8
#define ADC13_IDACMUX_MUX2_AIN9              9
#define ADC13_IDACMUX_MUX2_AINCOM            10
#define ADC13_IDACMUX_MUX2_NO_CONNECTION     11
#define ADC13_IDACMUX_MUX1_AIN0              0
#define ADC13_IDACMUX_MUX1_AIN1              1
#define ADC13_IDACMUX_MUX1_AIN2              2
#define ADC13_IDACMUX_MUX1_AIN3              3
#define ADC13_IDACMUX_MUX1_AIN4              4
#define ADC13_IDACMUX_MUX1_AIN5              5
#define ADC13_IDACMUX_MUX1_AIN6              6
#define ADC13_IDACMUX_MUX1_AIN7              7
#define ADC13_IDACMUX_MUX1_AIN8              8
#define ADC13_IDACMUX_MUX1_AIN9              9
#define ADC13_IDACMUX_MUX1_AINCOM            10
#define ADC13_IDACMUX_MUX1_NO_CONNECTION     11

/**
 * @brief ADC 13 IDACMAG register setting.
 * @details Specified setting for IDACMAG register of ADC 13 Click driver.
 */
#define ADC13_IDACMAG_MAG2_OFF               0
#define ADC13_IDACMAG_MAG2_50uA              1
#define ADC13_IDACMAG_MAG2_100uA             2
#define ADC13_IDACMAG_MAG2_250uA             3
#define ADC13_IDACMAG_MAG2_500uA             4
#define ADC13_IDACMAG_MAG2_750uA             5
#define ADC13_IDACMAG_MAG2_1000uA            6
#define ADC13_IDACMAG_MAG2_1500uA            7
#define ADC13_IDACMAG_MAG2_2000uA            8
#define ADC13_IDACMAG_MAG2_2500uA            9
#define ADC13_IDACMAG_MAG2_3000uA            10
#define ADC13_IDACMAG_MAG1_OFF               0
#define ADC13_IDACMAG_MAG1_50uA              1
#define ADC13_IDACMAG_MAG1_100uA             2
#define ADC13_IDACMAG_MAG1_250uA             3
#define ADC13_IDACMAG_MAG1_500uA             4
#define ADC13_IDACMAG_MAG1_750uA             5
#define ADC13_IDACMAG_MAG1_1000uA            6
#define ADC13_IDACMAG_MAG1_1500uA            7
#define ADC13_IDACMAG_MAG1_2000uA            8
#define ADC13_IDACMAG_MAG1_2500uA            9
#define ADC13_IDACMAG_MAG1_3000uA            10

/**
 * @brief ADC 13 REFMUX register setting.
 * @details Specified setting for REFMUX register of ADC 13 Click driver.
 */
#define ADC13_REFMUX_RMUXP_INTERNAL          0
#define ADC13_REFMUX_RMUXP_EXT_AIN0          1
#define ADC13_REFMUX_RMUXP_EXT_AIN2          2
#define ADC13_REFMUX_RMUXP_EXT_AIN4          3
#define ADC13_REFMUX_RMUXP_INTERNAL_AVDD     4
#define ADC13_REFMUX_RMUXN_INTERNAL          0
#define ADC13_REFMUX_RMUXN_EXT_AIN1          1
#define ADC13_REFMUX_RMUXN_EXT_AIN3          2
#define ADC13_REFMUX_RMUXN_EXT_AIN5          3
#define ADC13_REFMUX_RMUXN_INTERNAL_AVSS     4

/**
 * @brief ADC 13 TDACP register setting.
 * @details Specified setting for TDACP register of ADC 13 Click driver.
 */
#define ADC13_TDACP_OUTP_NO_CONNECTION       0
#define ADC13_TDACP_OUTP_AIN6                1
#define ADC13_TDACP_MAGP_4p5V                9
#define ADC13_TDACP_MAGP_3p5V                8
#define ADC13_TDACP_MAGP_3V                  7
#define ADC13_TDACP_MAGP_2p75V               6
#define ADC13_TDACP_MAGP_2p625V              5
#define ADC13_TDACP_MAGP_2p5625V             4
#define ADC13_TDACP_MAGP_2p53125V            3
#define ADC13_TDACP_MAGP_2p515625V           2
#define ADC13_TDACP_MAGP_2p5078125V          1
#define ADC13_TDACP_MAGP_2p5V                0
#define ADC13_TDACP_MAGP_2p4921875V          17
#define ADC13_TDACP_MAGP_2p484375V           18
#define ADC13_TDACP_MAGP_2p46875V            19
#define ADC13_TDACP_MAGP_2p4375V             20
#define ADC13_TDACP_MAGP_2p375V              21
#define ADC13_TDACP_MAGP_2p25V               22
#define ADC13_TDACP_MAGP_2V                  23
#define ADC13_TDACP_MAGP_1p5V                24
#define ADC13_TDACP_MAGP_0p5V                25

/**
 * @brief ADC 13 TDACN register setting.
 * @details Specified setting for TDACN register of ADC 13 Click driver.
 */
#define ADC13_TDACN_OUTN_NO_CONNECTION       0
#define ADC13_TDACN_OUTN_AIN7                1
#define ADC13_TDACN_MAGN_4p5V                9
#define ADC13_TDACN_MAGN_3p5V                8
#define ADC13_TDACN_MAGN_3V                  7
#define ADC13_TDACN_MAGN_2p75V               6
#define ADC13_TDACN_MAGN_2p625V              5
#define ADC13_TDACN_MAGN_2p5625V             4
#define ADC13_TDACN_MAGN_2p53125V            3
#define ADC13_TDACN_MAGN_2p515625V           2
#define ADC13_TDACN_MAGN_2p5078125V          1
#define ADC13_TDACN_MAGN_2p5V                0
#define ADC13_TDACN_MAGN_2p4921875V          17
#define ADC13_TDACN_MAGN_2p484375V           18
#define ADC13_TDACN_MAGN_2p46875V            19
#define ADC13_TDACN_MAGN_2p4375V             20
#define ADC13_TDACN_MAGN_2p375V              21
#define ADC13_TDACN_MAGN_2p25V               22
#define ADC13_TDACN_MAGN_2V                  23
#define ADC13_TDACN_MAGN_1p5V                24
#define ADC13_TDACN_MAGN_0p5V                25

/**
 * @brief ADC 13 GPIO pin high setting.
 * @details Specified setting for GPIO pins of ADC 13 Click driver.
 */
#define ADC13_GPIO0                          0x01
#define ADC13_GPIO1                          0x02
#define ADC13_GPIO2                          0x04
#define ADC13_GPIO3                          0x08
#define ADC13_GPIO4                          0x10
#define ADC13_GPIO5                          0x20
#define ADC13_GPIO6                          0x40
#define ADC13_GPIO7                          0x80

/**
 * @brief Voltage reference.
 * @details Voltage reference definition in voltages.
 */
#define ADC13_VREF_INTERNAL                  2.5
#define ADC13_VREF_INTERNAL_AVDD             5
#define ADC13_VREF_3V3                       3.3
#define ADC13_VREF_5V                        5

/**
 * @brief Checksum constant.
 * @details Checksum constant definition.
 */
#define ADC13_CHECKSUM_CONSTANT              0x9B

/**
 * @brief Temperature constant.
 * @details Temperature constants definition.
 */
#define ADC13_TEMP_MILIVOLTS                 122.4
#define ADC13_TEMP_V_TO_MV                   1000
#define ADC13_TEMP_COEFF                     0.42
#define ADC13_TEMP_OFFSET                    25.0
#define ADC13_TEMP_HEAT_OFFSET               0.7

/**
 * @brief Calculate position of rightmost set bit.
 * @details Macro which calculates and returns the position of the rightmost set bit.
 */
#define GET_RIGHTMOST_SET_BIT( bit_mask )               ( uint8_t )( log10( ( double ) \
                                                        ( bit_mask & ~( bit_mask - 1 ) ) ) / log10( 2.0 ) )

/**
 * @brief Set reg bits macro.
 * @details Macro to set a desired bits of the reg_data variable.
 */
#define SET_REG_BITS( reg_data, bit_mask, in_data )     ( ( reg_data & ~( bit_mask ) ) | \
                                                        ( ( in_data << GET_RIGHTMOST_SET_BIT( bit_mask ) ) \
                                                        & bit_mask ) )

/**
 * @brief Get reg bits macro.
 * @details Macro to get a desired bits of the reg_data variable.
 */
#define GET_REG_BITS( reg_data, bit_mask )              ( ( reg_data & bit_mask ) >> GET_RIGHTMOST_SET_BIT( bit_mask ) )

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b $adc13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC13_SET_DATA_SAMPLE_EDGE                      SET_SPI_DATA_SAMPLE_EDGE
#define ADC13_SET_DATA_SAMPLE_MIDDLE                    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc13_set

/**
 * @defgroup adc13_map ADC 13 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 13 Click driver.
 */

/**
 * @addtogroup adc13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 13 Click to the selected MikroBUS.
 */
#define ADC13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.str  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dtr  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc13_map
/*! @} */ // adc13

/**
 * @brief ADC 13 Click context object.
 * @details Context object definition of ADC 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset (active low); hold low to power down the ADC. */
    digital_out_t  str;         /**< Start conversion control. */

    // Input pins
    digital_in_t  dtr;          /**< Data ready indicator (active low). */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} adc13_t;

/**
 * @brief ADC 13 Click configuration object.
 * @details Configuration object definition of ADC 13 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;                                    /**< Reset (active low); hold low to power down the ADC. */
    pin_name_t  str;                                    /**< Start conversion control. */
    pin_name_t  dtr;                                    /**< Data ready indicator (active low). */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} adc13_cfg_t;

/**
 * @brief ADC 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC13_OK = 0,
    ADC13_ERROR = -1

} adc13_return_value_t;

/*!
 * @addtogroup adc13 ADC 13 Click Driver
 * @brief API for configuring and manipulating ADC 13 Click driver.
 * @{
 */

/**
 * @brief ADC 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc13_cfg_setup ( adc13_cfg_t *cfg );

/**
 * @brief ADC 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_init ( adc13_t *ctx, adc13_cfg_t *cfg );

/**
 * @brief ADC 13 default configuration function.
 * @details This function executes a default configuration of ADC 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc13_default_cfg ( adc13_t *ctx );

/**
 * @brief ADC 13 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_generic_write ( adc13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ADC 13 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_generic_read ( adc13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ADC 13 send command function.
 * @details This function writes a command byte to the module by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function toggles chip select, so it is used only when a command byte needs to be 
 * executed without following bytes.
 */
err_t adc13_send_command ( adc13_t *ctx, uint8_t cmd );

/**
 * @brief ADC 13 set STR pin function.
 * @details This function sets start conversion control by setting the STR pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void adc13_set_str_pin ( adc13_t *ctx, uint8_t state );

/**
 * @brief ADC 13 set RST pin function.
 * @details This function sets reset or power down by setting the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void adc13_set_rst_pin ( adc13_t *ctx, uint8_t state );

/**
 * @brief ADC 13 get DTR pin function.
 * @details This function returns the DTR (data ready indicator) pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adc13_get_dtr_pin ( adc13_t *ctx );

/**
 * @brief ADC 13 reset by pin function.
 * @details This function resets the chip by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void adc13_reset_by_pin ( adc13_t *ctx );

/**
 * @brief ADC 13 reset by command function.
 * @details This function resets the chip by issuing the RESET command.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_reset_by_command ( adc13_t *ctx );

/**
 * @brief ADC 13 power down function.
 * @details This function powers down the chip via the RST pin.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void adc13_power_down ( adc13_t *ctx );

/**
 * @brief ADC 13 power up function.
 * @details This function powers up the chip via the RST pin.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void adc13_power_up ( adc13_t *ctx );

/**
 * @brief ADC 13 read register function.
 * @details This function reads a data byte from a desider register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_read_register ( adc13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ADC 13 write register function.
 * @details This function writes a data byte to a desider register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_write_register ( adc13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ADC 13 read registers function.
 * @details This function reads a desired number of registers starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] count : Number of registers to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_read_registers ( adc13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t count );

/**
 * @brief ADC 13 write registers function.
 * @details This function writes a desired number of registers starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] count : Number of registers to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_write_registers ( adc13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t count );

/**
 * @brief ADC 13 set register bits function.
 * @details This function sets a desired bits of input register using the appropriate bit mask, 
 * other bits remain unchanged.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] bit_mask : Bit mask.
 * @param[in] data_in : Bits to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_set_register_bits ( adc13_t *ctx, uint8_t reg, uint8_t bit_mask, uint8_t data_in );

/**
 * @brief ADC 13 get register bits function.
 * @details This function reads a desired bits of input register using the appropriate bit mask.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] bit_mask : Bit mask.
 * @param[out] data_out : Readout bits.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_get_register_bits ( adc13_t *ctx, uint8_t reg, uint8_t bit_mask, uint8_t *data_out );

/**
 * @brief ADC 13 read raw data function.
 * @details This function reads raw ADC data after the conversation is finished.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[out] data_out : RAW ADC data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_read_raw_data ( adc13_t *ctx, int32_t *data_out );

/**
 * @brief ADC 13 measure voltage function.
 * @details This function starts ADC conversation, reads RAW ADC data then calculates the
 * voltage using the input vref for calculations.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] vref : Voltage reference (either in volts or milivolts).
 * @param[out] data_out : RAW ADC data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_measure_voltage ( adc13_t *ctx, float vref, float *voltage );

/**
 * @brief ADC 13 measure temperature function.
 * @details This function measures the internal temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_measure_temperature ( adc13_t *ctx, float *temperature );

/**
 * @brief ADC 13 set input channel function.
 * @details This function sets the ADC input positive and negative channels.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] pos : Positive channel.
 * @param[in] neg : Negative channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_set_input_channel ( adc13_t *ctx, uint8_t pos, uint8_t neg );

/**
 * @brief ADC 13 set voltage reference function.
 * @details This function sets the ADC inputs for positive and negative voltage reference.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] pos : Positive reference.
 * @param[in] neg : Negative reference.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_set_voltage_reference ( adc13_t *ctx, uint8_t pos, uint8_t neg );

/**
 * @brief ADC 13 set gain function.
 * @details This function sets the ADC gain.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] gain : Gain value [0-5].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_set_gain ( adc13_t *ctx, uint8_t gain );

/**
 * @brief ADC 13 set sample rate function.
 * @details This function sets the ADC sample rate.
 * @param[in] ctx : Click context object.
 * See #adc13_t object definition for detailed explanation.
 * @param[in] s_rate : Sample rate value [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc13_set_sample_rate ( adc13_t *ctx, uint8_t s_rate );

#ifdef __cplusplus
}
#endif
#endif // ADC13_H

/*! @} */ // adc13

// ------------------------------------------------------------------------ END

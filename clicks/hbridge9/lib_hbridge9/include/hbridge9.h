/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file hbridge9.h
 * @brief This file contains API for H-Bridge 9 Click Driver.
 */

#ifndef HBRIDGE9_H
#define HBRIDGE9_H

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
 * @addtogroup hbridge9 H-Bridge 9 Click Driver
 * @brief API for configuring and manipulating H-Bridge 9 Click driver.
 * @{
 */

/**
 * @defgroup hbridge9_reg H-Bridge 9 Registers List
 * @brief List of registers of H-Bridge 9 Click driver.
 */

/**
 * @addtogroup hbridge9_reg
 * @{
 */

/**
 * @brief H-Bridge 9 operating codes.
 * @details Specified operating codes of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_OPCODE_WRITE               0x00
#define HBRIDGE9_OPCODE_READ                0x40
#define HBRIDGE9_OPCODE_READ_CLEAR          0x80
#define HBRIDGE9_OPCODE_READ_DEV_INFO       0xC0
#define HBRIDGE9_ADV_OPCODE_SET_DEFAULT     0xFF
#define HBRIDGE9_ADV_OPCODE_CLEAR_STATUS    0xBF
#define HBRIDGE9_OPCODE_BITS_MASK           0xC0

/**
 * @brief H-Bridge 9 control register addresses.
 * @details Specified addresses of control registers of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_REG_CR0                    0x00
#define HBRIDGE9_REG_CR1                    0x01
#define HBRIDGE9_REG_CR2                    0x02
#define HBRIDGE9_REG_CR3                    0x03
#define HBRIDGE9_REG_CR4                    0x04
#define HBRIDGE9_REG_CR5                    0x05
#define HBRIDGE9_REG_CR6                    0x06
#define HBRIDGE9_REG_CR7                    0x07
#define HBRIDGE9_REG_CR8                    0x08

/**
 * @brief H-Bridge 9 status register addresses.
 * @details Specified addresses of status registers of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_REG_SR0                    0x10
#define HBRIDGE9_REG_SR1                    0x11
#define HBRIDGE9_REG_SR2                    0x12
#define HBRIDGE9_REG_SR3                    0x13
#define HBRIDGE9_REG_SR4                    0x14
#define HBRIDGE9_REG_SR5                    0x15
#define HBRIDGE9_REG_SR6                    0x16
#define HBRIDGE9_REG_SR7                    0x17
#define HBRIDGE9_REG_SR8                    0x18

/**
 * @brief H-Bridge 9 info register addresses.
 * @details Specified addresses of info registers of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_REG_INFO_COMPANY_CODE      0x00
#define HBRIDGE9_REG_INFO_DEVICE_FAMILY     0x01
#define HBRIDGE9_REG_INFO_DEVICE_NO_1       0x02
#define HBRIDGE9_REG_INFO_DEVICE_NO_2       0x03
#define HBRIDGE9_REG_INFO_DEVICE_NO_3       0x04
#define HBRIDGE9_REG_INFO_DEVICE_NO_4       0x05
#define HBRIDGE9_REG_INFO_SILICON_VER       0x0A
#define HBRIDGE9_REG_INFO_SPI_MODE          0x10
#define HBRIDGE9_REG_INFO_SPI_CPHA_TEST     0x20

/*! @} */ // hbridge9_reg

/**
 * @defgroup hbridge9_set H-Bridge 9 Registers Settings
 * @brief Settings for registers of H-Bridge 9 Click driver.
 */

/**
 * @addtogroup hbridge9_set
 * @{
 */

/**
 * @brief H-Bridge 9 SPI CPHA test bits.
 * @details Specified bits for SPI CPHA test of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_SPI_CPHA_TEST              0x55

/**
 * @brief H-Bridge 9 ODD parity flag.
 * @details Specified flag for ODD parity of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_ODD_PARITY                 0x01

/**
 * @brief H-Bridge 9 Control register 0 bits.
 * @details Specified bits for Control register 0 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR0_PWM_FREQ_10p240        0x0000
#define HBRIDGE9_CR0_PWM_FREQ_12p288        0x2000
#define HBRIDGE9_CR0_PWM_FREQ_14p336        0x4000
#define HBRIDGE9_CR0_PWM_FREQ_16p384        0x6000
#define HBRIDGE9_CR0_PWM_FREQ_18p432        0x8000
#define HBRIDGE9_CR0_PWM_FREQ_20p480        0xA000
#define HBRIDGE9_CR0_PWM_FREQ_22p528        0xC000
#define HBRIDGE9_CR0_PWM_FREQ_24p576        0xE000
#define HBRIDGE9_CR0_PWM_FREQ_MASK          0xE000
#define HBRIDGE9_CR0_OUT6_POL_HIGH          0x1000
#define HBRIDGE9_CR0_OUT6_POL_LOW           0x0040
#define HBRIDGE9_CR0_OUT6_POL_MASK          0x1040
#define HBRIDGE9_CR0_OUT5_POL_HIGH          0x0800
#define HBRIDGE9_CR0_OUT5_POL_LOW           0x0020
#define HBRIDGE9_CR0_OUT5_POL_MASK          0x0820
#define HBRIDGE9_CR0_OUT4_POL_HIGH          0x0400
#define HBRIDGE9_CR0_OUT4_POL_LOW           0x0010
#define HBRIDGE9_CR0_OUT4_POL_MASK          0x0410
#define HBRIDGE9_CR0_OUT3_POL_HIGH          0x0200
#define HBRIDGE9_CR0_OUT3_POL_LOW           0x0008
#define HBRIDGE9_CR0_OUT3_POL_MASK          0x0208
#define HBRIDGE9_CR0_OUT2_POL_HIGH          0x0100
#define HBRIDGE9_CR0_OUT2_POL_LOW           0x0004
#define HBRIDGE9_CR0_OUT2_POL_MASK          0x0104
#define HBRIDGE9_CR0_OUT1_POL_HIGH          0x0080
#define HBRIDGE9_CR0_OUT1_POL_LOW           0x0002
#define HBRIDGE9_CR0_OUT1_POL_MASK          0x0082

/**
 * @brief H-Bridge 9 Control register 1 bits.
 * @details Specified bits for Control register 1 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR1_EX_OUT2_ON             0x8000
#define HBRIDGE9_CR1_EX_OUT1_ON             0x4000
#define HBRIDGE9_CR1_EX_OUT_MASK            0xC000
#define HBRIDGE9_CR1_OUT6_ON                0x2000
#define HBRIDGE9_CR1_OUT5_ON                0x1000
#define HBRIDGE9_CR1_OUT4_ON                0x0800
#define HBRIDGE9_CR1_OUT3_ON                0x0400
#define HBRIDGE9_CR1_OUT2_ON                0x0200
#define HBRIDGE9_CR1_OUT1_ON                0x0100
#define HBRIDGE9_CR1_OUT_MASK               0x3F00
#define HBRIDGE9_CR1_EMCY_NORMAL_MODE       0x0000
#define HBRIDGE9_CR1_EMCY_EMERGENCY_MODE    0x0080
#define HBRIDGE9_CR1_EMCY_MASK              0x00C0
#define HBRIDGE9_CR1_EX_OUT2_POL_HIGH       0x0020
#define HBRIDGE9_CR1_EX_OUT2_POL_LOW        0x0008
#define HBRIDGE9_CR1_EX_OUT2_POL_MASK       0x0028
#define HBRIDGE9_CR1_EX_OUT1_POL_HIGH       0x0010
#define HBRIDGE9_CR1_EX_OUT1_POL_LOW        0x0004
#define HBRIDGE9_CR1_EX_OUT1_POL_MASK       0x0014
#define HBRIDGE9_CR1_OUT_ON                 0x0002

/**
 * @brief H-Bridge 9 Control register 2 bits.
 * @details Specified bits for Control register 2 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR2_DBN_EX2                0x8000
#define HBRIDGE9_CR2_DBN_EX1                0x4000
#define HBRIDGE9_CR2_DBN_EX_MASK            0xC000
#define HBRIDGE9_CR2_DBN_6                  0x2000
#define HBRIDGE9_CR2_DBN_5                  0x1000
#define HBRIDGE9_CR2_DBN_4                  0x0800
#define HBRIDGE9_CR2_DBN_3                  0x0400
#define HBRIDGE9_CR2_DBN_2                  0x0200
#define HBRIDGE9_CR2_DBN_1                  0x0100
#define HBRIDGE9_CR2_DBN_MASK               0x3F00
#define HBRIDGE9_CR2_ON_TIME_DUR_100MS      0x0000
#define HBRIDGE9_CR2_ON_TIME_DUR_120MS      0x0008
#define HBRIDGE9_CR2_ON_TIME_DUR_140MS      0x0010
#define HBRIDGE9_CR2_ON_TIME_DUR_160MS      0x0018
#define HBRIDGE9_CR2_ON_TIME_DUR_180MS      0x0020
#define HBRIDGE9_CR2_ON_TIME_DUR_200MS      0x0028
#define HBRIDGE9_CR2_ON_TIME_DUR_220MS      0x0030
#define HBRIDGE9_CR2_ON_TIME_DUR_240MS      0x0038
#define HBRIDGE9_CR2_ON_TIME_DUR_260MS      0x0040
#define HBRIDGE9_CR2_ON_TIME_DUR_280MS      0x0048
#define HBRIDGE9_CR2_ON_TIME_DUR_300MS      0x0050
#define HBRIDGE9_CR2_ON_TIME_DUR_320MS      0x0058
#define HBRIDGE9_CR2_ON_TIME_DUR_340MS      0x0060
#define HBRIDGE9_CR2_ON_TIME_DUR_360MS      0x0068
#define HBRIDGE9_CR2_ON_TIME_DUR_380MS      0x0070
#define HBRIDGE9_CR2_ON_TIME_DUR_400MS      0x0078
#define HBRIDGE9_CR2_ON_TIME_DUR_440MS      0x0080
#define HBRIDGE9_CR2_ON_TIME_DUR_480MS      0x0088
#define HBRIDGE9_CR2_ON_TIME_DUR_520MS      0x0090
#define HBRIDGE9_CR2_ON_TIME_DUR_560MS      0x0098
#define HBRIDGE9_CR2_ON_TIME_DUR_600MS      0x00A0
#define HBRIDGE9_CR2_ON_TIME_DUR_640MS      0x00A8
#define HBRIDGE9_CR2_ON_TIME_DUR_680MS      0x00B0
#define HBRIDGE9_CR2_ON_TIME_DUR_720MS      0x00B8
#define HBRIDGE9_CR2_ON_TIME_DUR_760MS      0x00C0
#define HBRIDGE9_CR2_ON_TIME_DUR_800MS      0x00C8
#define HBRIDGE9_CR2_ON_TIME_DUR_840MS      0x00D0
#define HBRIDGE9_CR2_ON_TIME_DUR_880MS      0x00D8
#define HBRIDGE9_CR2_ON_TIME_DUR_920MS      0x00E0
#define HBRIDGE9_CR2_ON_TIME_DUR_960MS      0x00E8
#define HBRIDGE9_CR2_ON_TIME_DUR_1000MS     0x00F0
#define HBRIDGE9_CR2_ON_TIME_DUR_1040MS     0x00F8
#define HBRIDGE9_CR2_ON_TIME_DUR_MASK       0x00F8
#define HBRIDGE9_CR2_BRAKING_DUR_0MS        0x0000
#define HBRIDGE9_CR2_BRAKING_DUR_100MS      0x0002
#define HBRIDGE9_CR2_BRAKING_DUR_200MS      0x0004
#define HBRIDGE9_CR2_BRAKING_DUR_100MS_IND  0x0006
#define HBRIDGE9_CR2_BRAKING_DUR_MASK       0x0006

/**
 * @brief H-Bridge 9 Control register 3 bits.
 * @details Specified bits for Control register 3 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR3_GFI                    0x0080
#define HBRIDGE9_CR3_TSD_ACT                0x0040
#define HBRIDGE9_CR3_DITHN                  0x0020
#define HBRIDGE9_CR3_NO_GROUP               0x0000
#define HBRIDGE9_CR3_GROUP_1_2              0x0002
#define HBRIDGE9_CR3_GROUP_1_3              0x0004
#define HBRIDGE9_CR3_GROUP_1_2_3            0x0006
#define HBRIDGE9_CR3_GROUP_4_5              0x0008
#define HBRIDGE9_CR3_GROUP_4_6              0x0010
#define HBRIDGE9_CR3_GROUP_4_5_6            0x0018
#define HBRIDGE9_CR3_GROUP_MASK             0x001E

/**
 * @brief H-Bridge 9 Control register 4 and 5 bits.
 * @details Specified bits for Control register 4 and 5 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR4_OCP1_SHIFT_BITS        0x0001
#define HBRIDGE9_CR4_OCP2_SHIFT_BITS        0x0006
#define HBRIDGE9_CR4_OCP3_SHIFT_BITS        0x000B
#define HBRIDGE9_CR5_OCP4_SHIFT_BITS        0x0001
#define HBRIDGE9_CR5_OCP5_SHIFT_BITS        0x0006
#define HBRIDGE9_CR5_OCP6_SHIFT_BITS        0x000B
#define HBRIDGE9_DUTY_CYCLE_6p25            0x0000
#define HBRIDGE9_DUTY_CYCLE_12p5            0x0001
#define HBRIDGE9_DUTY_CYCLE_18p75           0x0002
#define HBRIDGE9_DUTY_CYCLE_25              0x0003
#define HBRIDGE9_DUTY_CYCLE_31p25           0x0004
#define HBRIDGE9_DUTY_CYCLE_37p5            0x0005
#define HBRIDGE9_DUTY_CYCLE_43p75           0x0006
#define HBRIDGE9_DUTY_CYCLE_50              0x0007
#define HBRIDGE9_DUTY_CYCLE_56p25           0x0008
#define HBRIDGE9_DUTY_CYCLE_62p5            0x0009
#define HBRIDGE9_DUTY_CYCLE_68p75           0x000A
#define HBRIDGE9_DUTY_CYCLE_75              0x000B
#define HBRIDGE9_DUTY_CYCLE_81p25           0x000C
#define HBRIDGE9_DUTY_CYCLE_87p5            0x000D
#define HBRIDGE9_DUTY_CYCLE_93p75           0x000E
#define HBRIDGE9_DUTY_CYCLE_100             0x000F
#define HBRIDGE9_DUTY_CYCLE_MASK            0x001F
#define HBRIDGE9_CURRENT_1A                 0x0010
#define HBRIDGE9_CURRENT_1p2A               0x0011
#define HBRIDGE9_CURRENT_1p4A               0x0012
#define HBRIDGE9_CURRENT_1p6A               0x0013
#define HBRIDGE9_CURRENT_1p8A               0x0014
#define HBRIDGE9_CURRENT_2A                 0x0015
#define HBRIDGE9_CURRENT_2p2A               0x0016
#define HBRIDGE9_CURRENT_2p4A               0x0017
#define HBRIDGE9_CURRENT_2p6A               0x0018
#define HBRIDGE9_CURRENT_2p8A               0x0019
#define HBRIDGE9_CURRENT_3A                 0x001A
#define HBRIDGE9_CURRENT_3p2A               0x001B
#define HBRIDGE9_CURRENT_3p4A               0x001C
#define HBRIDGE9_CURRENT_3p6A               0x001D
#define HBRIDGE9_CURRENT_3p8A               0x001E
#define HBRIDGE9_CURRENT_4A                 0x001F
#define HBRIDGE9_CURRENT_MASK               0x001F

/**
 * @brief H-Bridge 9 Control register 6 bits.
 * @details Specified bits for Control register 6 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR6_HBDCL2                 0x8000
#define HBRIDGE9_CR6_HBDCH2                 0x4000
#define HBRIDGE9_CR6_HBDC2_MASK             0xC000
#define HBRIDGE9_CR6_STBY1                  0x2000
#define HBRIDGE9_CR6_EXT2_VDT_1US           0x0000
#define HBRIDGE9_CR6_EXT2_VDT_2US           0x0800
#define HBRIDGE9_CR6_EXT2_VDT_3US           0x1000
#define HBRIDGE9_CR6_EXT2_VDT_4US           0x1800
#define HBRIDGE9_CR6_EXT2_VDT_MASK          0x1800
#define HBRIDGE9_CR6_EXT1_VDT_1US           0x0000
#define HBRIDGE9_CR6_EXT1_VDT_2US           0x0200
#define HBRIDGE9_CR6_EXT1_VDT_3US           0x0400
#define HBRIDGE9_CR6_EXT1_VDT_4US           0x0600
#define HBRIDGE9_CR6_EXT1_VDT_MASK          0x0600
#define HBRIDGE9_CR6_EXT2_VDS_OFF           0x0000
#define HBRIDGE9_CR6_EXT2_VDS_0p25V         0x0100
#define HBRIDGE9_CR6_EXT2_VDS_0p5V          0x0120
#define HBRIDGE9_CR6_EXT2_VDS_0p75V         0x0140
#define HBRIDGE9_CR6_EXT2_VDS_1V            0x0160
#define HBRIDGE9_CR6_EXT2_VDS_1p25V         0x0180
#define HBRIDGE9_CR6_EXT2_VDS_1p5V          0x01A0
#define HBRIDGE9_CR6_EXT2_VDS_1p75V         0x01C0
#define HBRIDGE9_CR6_EXT2_VDS_2V            0x01E0
#define HBRIDGE9_CR6_EXT2_VDS_MASK          0x01E0
#define HBRIDGE9_CR6_EXT1_VDS_OFF           0x0000
#define HBRIDGE9_CR6_EXT1_VDS_0p25V         0x0010
#define HBRIDGE9_CR6_EXT1_VDS_0p5V          0x0012
#define HBRIDGE9_CR6_EXT1_VDS_0p75V         0x0014
#define HBRIDGE9_CR6_EXT1_VDS_1V            0x0016
#define HBRIDGE9_CR6_EXT1_VDS_1p25V         0x0018
#define HBRIDGE9_CR6_EXT1_VDS_1p5V          0x001A
#define HBRIDGE9_CR6_EXT1_VDS_1p75V         0x001C
#define HBRIDGE9_CR6_EXT1_VDS_2V            0x001E
#define HBRIDGE9_CR6_EXT1_VDS_MASK          0x001E

/**
 * @brief H-Bridge 9 Control register 7 bits.
 * @details Specified bits for Control register 7 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR7_HBDCL1                 0x8000
#define HBRIDGE9_CR7_HBDCH1                 0x4000
#define HBRIDGE9_CR7_HBDC1_MASK             0xC000
#define HBRIDGE9_CR7_STBY2                  0x2000
#define HBRIDGE9_CR7_ODCL6                  0x1000
#define HBRIDGE9_CR7_ODCH6                  0x0800
#define HBRIDGE9_CR7_ODC6_MASK              0x1800
#define HBRIDGE9_CR7_ODCL5                  0x0400
#define HBRIDGE9_CR7_ODCH5                  0x0200
#define HBRIDGE9_CR7_ODC5_MASK              0x0600
#define HBRIDGE9_CR7_ODCL4                  0x0100
#define HBRIDGE9_CR7_ODCH4                  0x0080
#define HBRIDGE9_CR7_ODC4_MASK              0x0180
#define HBRIDGE9_CR7_ODCL3                  0x0040
#define HBRIDGE9_CR7_ODCH3                  0x0020
#define HBRIDGE9_CR7_ODC3_MASK              0x0060
#define HBRIDGE9_CR7_ODCL2                  0x0010
#define HBRIDGE9_CR7_ODCH2                  0x0008
#define HBRIDGE9_CR7_ODC2_MASK              0x0018
#define HBRIDGE9_CR7_ODCL1                  0x0004
#define HBRIDGE9_CR7_ODCH1                  0x0002
#define HBRIDGE9_CR7_ODC1_MASK              0x0006

/**
 * @brief H-Bridge 9 Control register 8 bits.
 * @details Specified bits for Control register 8 of H-Bridge 9 Click driver.
 */
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_128     0x0000
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_64      0x0010
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_32      0x0020
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_16      0x0030
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_8       0x0040
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_4       0x0050
#define HBRIDGE9_CR8_KI_GAIN_1_OVER_2       0x0060
#define HBRIDGE9_CR8_KI_GAIN_1              0x0070
#define HBRIDGE9_CR8_KI_GAIN_MASK           0x0070
#define HBRIDGE9_CR8_KP_GAIN_2              0x0000
#define HBRIDGE9_CR8_KP_GAIN_4              0x0001
#define HBRIDGE9_CR8_KP_GAIN_8              0x0002
#define HBRIDGE9_CR8_KP_GAIN_16             0x0003
#define HBRIDGE9_CR8_KP_GAIN_32             0x0004
#define HBRIDGE9_CR8_KP_GAIN_64             0x0005
#define HBRIDGE9_CR8_KP_GAIN_128            0x0006
#define HBRIDGE9_CR8_KP_GAIN_256            0x0007
#define HBRIDGE9_CR8_KP_GAIN_MASK           0x0007

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE9_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE9_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge9_set

/**
 * @defgroup hbridge9_map H-Bridge 9 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 9 Click driver.
 */

/**
 * @addtogroup hbridge9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 9 Click to the selected MikroBUS.
 */
#define HBRIDGE9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en_out = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dout = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge9_map
/*! @} */ // hbridge9

/**
 * @brief H-Bridge 9 Click context object.
 * @details Context object definition of H-Bridge 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en_out;          /**< Failsafe logic pin. */

    // Input pins
    digital_in_t   dout;            /**< Global fault flag. */

    // Modules
    spi_master_t   spi;             /**< SPI driver object. */

    pin_name_t     chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t        global_status;   /**< Global status byte. */

} hbridge9_t;

/**
 * @brief H-Bridge 9 Click configuration object.
 * @details Configuration object definition of H-Bridge 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  en_out;                                 /**< Failsafe logic pin. */
    pin_name_t  dout;                                   /**< Global fault flag. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} hbridge9_cfg_t;

/**
 * @brief H-Bridge 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE9_OK = 0,
    HBRIDGE9_ERROR = -1

} hbridge9_return_value_t;

/*!
 * @addtogroup hbridge9 H-Bridge 9 Click Driver
 * @brief API for configuring and manipulating H-Bridge 9 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge9_cfg_setup ( hbridge9_cfg_t *cfg );

/**
 * @brief H-Bridge 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_init ( hbridge9_t *ctx, hbridge9_cfg_t *cfg );

/**
 * @brief H-Bridge 9 default configuration function.
 * @details This function executes a default configuration of H-Bridge 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge9_default_cfg ( hbridge9_t *ctx );

/**
 * @brief H-Bridge 9 spi transfer function.
 * @details This function writes and reads a desired number of data bytes simultaneously 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_spi_transfer ( hbridge9_t *ctx, uint8_t *data_in, uint8_t tx_len, uint8_t *data_out, uint8_t rx_len );

/**
 * @brief H-Bridge 9 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written ( without parity bit ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_write_register ( hbridge9_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief H-Bridge 9 read register function.
 * @details This function reads a desired data from the selected register.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Read data ( with parity bit ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_read_register ( hbridge9_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief H-Bridge 9 modify register bits function.
 * @details This function modifies the specified register bits.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] clr_mask : Clear bit mask.
 * @param[in] set_mask : Set bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_modify_register_bits ( hbridge9_t *ctx, uint8_t reg, uint16_t clr_mask, uint16_t set_mask );

/**
 * @brief H-Bridge 9 read register and clear function.
 * @details This function reads the selected register and clears its status if needed.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Read data ( with parity bit ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_read_register_and_clear ( hbridge9_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief H-Bridge 9 read info register function.
 * @details This function reads the selected info register.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_read_info_register ( hbridge9_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 9 set default function.
 * @details This function sends the set all register to default state command.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_set_default ( hbridge9_t *ctx );

/**
 * @brief H-Bridge 9 clear all status function.
 * @details This function sends the clear all status registers command.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_clear_all_status ( hbridge9_t *ctx );

/**
 * @brief H-Bridge 9 check communication function.
 * @details This function checks the communication by reading and verifying the SPI CPHA Test register.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge9_check_communication ( hbridge9_t *ctx );

/**
 * @brief H-Bridge 9 set en out pin function.
 * @details This function sets the ENO pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void hbridge9_set_en_out_pin ( hbridge9_t *ctx, uint8_t state );

/**
 * @brief H-Bridge 9 send actuation pulse function.
 * @details This function sends an actuation pulse by toggling the ENO pin.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge9_send_actuation_pulse ( hbridge9_t *ctx );

/**
 * @brief H-Bridge 9 get dout pin function.
 * @details This function returns the DO pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hbridge9_get_dout_pin ( hbridge9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE9_H

/*! @} */ // hbridge9

// ------------------------------------------------------------------------ END

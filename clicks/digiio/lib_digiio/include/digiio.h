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
 * @file digiio.h
 * @brief This file contains API for DIGI IO Click Driver.
 */

#ifndef DIGIIO_H
#define DIGIIO_H

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
 * @addtogroup digiio DIGI IO Click Driver
 * @brief API for configuring and manipulating DIGI IO Click driver.
 * @{
 */

/**
 * @defgroup digiio_reg DIGI IO Registers List
 * @brief List of registers of DIGI IO Click driver.
 */

/**
 * @addtogroup digiio_reg
 * @{
 */

/**
 * @brief DIGI IO register list.
 * @details Specified register list of DIGI IO Click driver.
 */
#define DIGIIO_REG_SET_OUT                      0x00
#define DIGIIO_REG_SET_LED                      0x01
#define DIGIIO_REG_DOI_LEVEL                    0x02
#define DIGIIO_REG_INTERRUPT                    0x03
#define DIGIIO_REG_OVR_LD_CH_F                  0x04
#define DIGIIO_REG_OPN_WIR_CH_F                 0x05
#define DIGIIO_REG_SHT_VDD_CH_F                 0x06
#define DIGIIO_REG_GLOBAL_ERR                   0x07
#define DIGIIO_REG_OPN_WR_EN                    0x08
#define DIGIIO_REG_SHT_VDD_EN                   0x09
#define DIGIIO_REG_CONFIG_1                     0x0A
#define DIGIIO_REG_CONFIG_2                     0x0B
#define DIGIIO_REG_CONFIG_DI                    0x0C
#define DIGIIO_REG_CONFIG_DO                    0x0D
#define DIGIIO_REG_CURR_LIM                     0x0E
#define DIGIIO_REG_MASK                         0x0F

/*! @} */ // digiio_reg

/**
 * @defgroup digiio_set DIGI IO Registers Settings
 * @brief Settings for registers of DIGI IO Click driver.
 */

/**
 * @addtogroup digiio_set
 * @{
 */

/**
 * @brief DIGI IO SET_OUT register setting.
 * @details Specified setting for SET_OUT register of DIGI IO Click driver.
 */
#define DIGIIO_SET_OUT_SET_DI4_OUTPUT           0x00
#define DIGIIO_SET_OUT_SET_DI4_INPUT            0x80
#define DIGIIO_SET_OUT_SET_DI4_MASK             0x80
#define DIGIIO_SET_OUT_SET_DI3_OUTPUT           0x00
#define DIGIIO_SET_OUT_SET_DI3_INPUT            0x40
#define DIGIIO_SET_OUT_SET_DI3_MASK             0x40
#define DIGIIO_SET_OUT_SET_DI2_OUTPUT           0x00
#define DIGIIO_SET_OUT_SET_DI2_INPUT            0x20
#define DIGIIO_SET_OUT_SET_DI2_MASK             0x20
#define DIGIIO_SET_OUT_SET_DI1_OUTPUT           0x00
#define DIGIIO_SET_OUT_SET_DI1_INPUT            0x10
#define DIGIIO_SET_OUT_SET_DI1_MASK             0x10
#define DIGIIO_SET_OUT_HIGH_O4_LOW              0x00
#define DIGIIO_SET_OUT_HIGH_O4_HIGH             0x08
#define DIGIIO_SET_OUT_HIGH_O4_MASK             0x08
#define DIGIIO_SET_OUT_HIGH_O3_LOW              0x00
#define DIGIIO_SET_OUT_HIGH_O3_HIGH             0x04
#define DIGIIO_SET_OUT_HIGH_O3_MASK             0x04
#define DIGIIO_SET_OUT_HIGH_O2_LOW              0x00
#define DIGIIO_SET_OUT_HIGH_O2_HIGH             0x02
#define DIGIIO_SET_OUT_HIGH_O2_MASK             0x02
#define DIGIIO_SET_OUT_HIGH_O1_LOW              0x00
#define DIGIIO_SET_OUT_HIGH_O1_HIGH             0x01
#define DIGIIO_SET_OUT_HIGH_O1_MASK             0x01

/**
 * @brief DIGI IO SET_LED register setting.
 * @details Specified setting for SET_LED register of DIGI IO Click driver.
 */
#define DIGIIO_SET_LED_SLED4_OFF                0x00
#define DIGIIO_SET_LED_SLED4_ON                 0x80
#define DIGIIO_SET_LED_SLED4_MASK               0x80
#define DIGIIO_SET_LED_SLED3_OFF                0x00
#define DIGIIO_SET_LED_SLED3_ON                 0x40
#define DIGIIO_SET_LED_SLED3_MASK               0x40
#define DIGIIO_SET_LED_SLED2_OFF                0x00
#define DIGIIO_SET_LED_SLED2_ON                 0x20
#define DIGIIO_SET_LED_SLED2_MASK               0x20
#define DIGIIO_SET_LED_SLED1_OFF                0x00
#define DIGIIO_SET_LED_SLED1_ON                 0x10
#define DIGIIO_SET_LED_SLED1_MASK               0x10
#define DIGIIO_SET_LED_FLED4_OFF                0x00
#define DIGIIO_SET_LED_FLED4_ON                 0x08
#define DIGIIO_SET_LED_FLED4_MASK               0x08
#define DIGIIO_SET_LED_FLED3_OFF                0x00
#define DIGIIO_SET_LED_FLED3_ON                 0x04
#define DIGIIO_SET_LED_FLED3_MASK               0x04
#define DIGIIO_SET_LED_FLED2_OFF                0x00
#define DIGIIO_SET_LED_FLED2_ON                 0x02
#define DIGIIO_SET_LED_FLED2_MASK               0x02
#define DIGIIO_SET_LED_FLED1_OFF                0x00
#define DIGIIO_SET_LED_FLED1_ON                 0x01
#define DIGIIO_SET_LED_FLED1_MASK               0x01

/**
 * @brief DIGI IO DOI_LEVEL register setting.
 * @details Specified setting for DOI_LEVEL register of DIGI IO Click driver.
 */
#define DIGIIO_DOI_LEVEL_SAFE_DEMAG_F4          0x80
#define DIGIIO_DOI_LEVEL_SAFE_DEMAG_F3          0x40
#define DIGIIO_DOI_LEVEL_SAFE_DEMAG_F2          0x20
#define DIGIIO_DOI_LEVEL_SAFE_DEMAG_F1          0x10
#define DIGIIO_DOI_LEVEL_DOI4                   0x08
#define DIGIIO_DOI_LEVEL_DOI3                   0x04
#define DIGIIO_DOI_LEVEL_DOI2                   0x02
#define DIGIIO_DOI_LEVEL_DOI1                   0x01

/**
 * @brief DIGI IO INTERRUPT register setting.
 * @details Specified setting for INTERRUPT register of DIGI IO Click driver.
 */
#define DIGIIO_INTERRUPT_COMM_ERR               0x80
#define DIGIIO_INTERRUPT_SUPPLY_ERR             0x40
#define DIGIIO_INTERRUPT_DEMAG_FAULT            0x20
#define DIGIIO_INTERRUPT_SHT_VDD_FAULT          0x10
#define DIGIIO_INTERRUPT_ABOVE_VDD_FAULT        0x08
#define DIGIIO_INTERRUPT_OW_OFF_FAULT           0x04
#define DIGIIO_INTERRUPT_CURR_LIM               0x02
#define DIGIIO_INTERRUPT_OVER_LD_FAULT          0x01

/**
 * @brief DIGI IO OVR_LD_CH_F register setting.
 * @details Specified setting for OVR_LD_CH_F register of DIGI IO Click driver.
 */
#define DIGIIO_OVR_LD_CH_F_CL4                  0x80
#define DIGIIO_OVR_LD_CH_F_CL3                  0x40
#define DIGIIO_OVR_LD_CH_F_CL2                  0x20
#define DIGIIO_OVR_LD_CH_F_CL1                  0x10
#define DIGIIO_OVR_LD_CH_F_OVL4                 0x08
#define DIGIIO_OVR_LD_CH_F_OVL3                 0x04
#define DIGIIO_OVR_LD_CH_F_OVL2                 0x02
#define DIGIIO_OVR_LD_CH_F_OVL1                 0x01

/**
 * @brief DIGI IO OPN_WIR_CH_F register setting.
 * @details Specified setting for OPN_WIR_CH_F register of DIGI IO Click driver.
 */
#define DIGIIO_OPN_WIR_CH_F_ABOVE_VDD4          0x80
#define DIGIIO_OPN_WIR_CH_F_ABOVE_VDD3          0x40
#define DIGIIO_OPN_WIR_CH_F_ABOVE_VDD2          0x20
#define DIGIIO_OPN_WIR_CH_F_ABOVE_VDD1          0x10
#define DIGIIO_OPN_WIR_CH_F_OW_OFF4             0x08
#define DIGIIO_OPN_WIR_CH_F_OW_OFF3             0x04
#define DIGIIO_OPN_WIR_CH_F_OW_OFF2             0x02
#define DIGIIO_OPN_WIR_CH_F_OW_OFF1             0x01

/**
 * @brief DIGI IO SHT_VDD_CH_F register setting.
 * @details Specified setting for SHT_VDD_CH_F register of DIGI IO Click driver.
 */
#define DIGIIO_SHT_VDD_CH_F_VDD_OV4             0x80
#define DIGIIO_SHT_VDD_CH_F_VDD_OV3             0x40
#define DIGIIO_SHT_VDD_CH_F_VDD_OV2             0x20
#define DIGIIO_SHT_VDD_CH_F_VDD_OV1             0x10
#define DIGIIO_SHT_VDD_CH_F_SH_VDD4             0x08
#define DIGIIO_SHT_VDD_CH_F_SH_VDD3             0x04
#define DIGIIO_SHT_VDD_CH_F_SH_VDD2             0x02
#define DIGIIO_SHT_VDD_CH_F_SH_VDD1             0x01

/**
 * @brief DIGI IO GLOBAL_ERR register setting.
 * @details Specified setting for GLOBAL_ERR register of DIGI IO Click driver.
 */
#define DIGIIO_GLOBAL_ERR_W_DOG_ERR             0x80
#define DIGIIO_GLOBAL_ERR_LOSS_GND              0x40
#define DIGIIO_GLOBAL_ERR_THRM_SHUTD            0x20
#define DIGIIO_GLOBAL_ERR_VDD_UVLO              0x10
#define DIGIIO_GLOBAL_ERR_VDD_WARN              0x08
#define DIGIIO_GLOBAL_ERR_VDD_LOW               0x04
#define DIGIIO_GLOBAL_ERR_V5_UVLO               0x02
#define DIGIIO_GLOBAL_ERR_VINT_UV               0x01

/**
 * @brief DIGI IO OPN_WR_EN register setting.
 * @details Specified setting for OPN_WR_EN register of DIGI IO Click driver.
 */
#define DIGIIO_OPN_WR_EN_G_DRV_EN4_OFF          0x00
#define DIGIIO_OPN_WR_EN_G_DRV_EN4_ON           0x80
#define DIGIIO_OPN_WR_EN_G_DRV_EN4_MASK         0x80
#define DIGIIO_OPN_WR_EN_G_DRV_EN3_OFF          0x00
#define DIGIIO_OPN_WR_EN_G_DRV_EN3_ON           0x40
#define DIGIIO_OPN_WR_EN_G_DRV_EN3_MASK         0x40
#define DIGIIO_OPN_WR_EN_G_DRV_EN2_OFF          0x00
#define DIGIIO_OPN_WR_EN_G_DRV_EN2_ON           0x20
#define DIGIIO_OPN_WR_EN_G_DRV_EN2_MASK         0x20
#define DIGIIO_OPN_WR_EN_G_DRV_EN1_OFF          0x00
#define DIGIIO_OPN_WR_EN_G_DRV_EN1_ON           0x10
#define DIGIIO_OPN_WR_EN_G_DRV_EN1_MASK         0x10
#define DIGIIO_OPN_WR_EN_OW_OFF_EN4_OFF         0x00
#define DIGIIO_OPN_WR_EN_OW_OFF_EN4_ON          0x08
#define DIGIIO_OPN_WR_EN_OW_OFF_EN4_MASK        0x08
#define DIGIIO_OPN_WR_EN_OW_OFF_EN3_OFF         0x00
#define DIGIIO_OPN_WR_EN_OW_OFF_EN3_ON          0x04
#define DIGIIO_OPN_WR_EN_OW_OFF_EN3_MASK        0x04
#define DIGIIO_OPN_WR_EN_OW_OFF_EN2_OFF         0x00
#define DIGIIO_OPN_WR_EN_OW_OFF_EN2_ON          0x02
#define DIGIIO_OPN_WR_EN_OW_OFF_EN2_MASK        0x02
#define DIGIIO_OPN_WR_EN_OW_OFF_EN1_OFF         0x00
#define DIGIIO_OPN_WR_EN_OW_OFF_EN1_ON          0x01
#define DIGIIO_OPN_WR_EN_OW_OFF_EN1_MASK        0x01

/**
 * @brief DIGI IO SHT_VDD_EN register setting.
 * @details Specified setting for SHT_VDD_EN register of DIGI IO Click driver.
 */
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN4_OFF        0x00
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN4_ON         0x80
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN4_MASK       0x80
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN3_OFF        0x00
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN3_ON         0x40
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN3_MASK       0x40
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN2_OFF        0x00
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN2_ON         0x20
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN2_MASK       0x20
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN1_OFF        0x00
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN1_ON         0x10
#define DIGIIO_SHT_VDD_EN_VDD_OV_EN1_MASK       0x10
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN4_OFF        0x00
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN4_ON         0x08
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN4_MASK       0x08
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN3_OFF        0x00
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN3_ON         0x04
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN3_MASK       0x04
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN2_OFF        0x00
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN2_ON         0x02
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN2_MASK       0x02
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN1_OFF        0x00
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN1_ON         0x01
#define DIGIIO_SHT_VDD_EN_SH_VDD_EN1_MASK       0x01

/**
 * @brief DIGI IO CONFIG_1 register setting.
 * @details Specified setting for CONFIG_1 register of DIGI IO Click driver.
 */
#define DIGIIO_CONFIG_1_LED_CURR_LIM_OFF        0x00
#define DIGIIO_CONFIG_1_LED_CURR_LIM_ON         0x80
#define DIGIIO_CONFIG_1_LED_CURR_LIM_MASK       0x80
#define DIGIIO_CONFIG_1_FLATCH_EN_OFF           0x00
#define DIGIIO_CONFIG_1_FLATCH_EN_ON            0x40
#define DIGIIO_CONFIG_1_FLATCH_EN_MASK          0x40
#define DIGIIO_CONFIG_1_FILTER_LONG_4_MS        0x00
#define DIGIIO_CONFIG_1_FILTER_LONG_8_MS        0x20
#define DIGIIO_CONFIG_1_FILTER_LONG_MASK        0x20
#define DIGIIO_CONFIG_1_FFILTER_EN_OFF          0x00
#define DIGIIO_CONFIG_1_FFILTER_EN_ON           0x10
#define DIGIIO_CONFIG_1_FFILTER_EN_MASK         0x10
#define DIGIIO_CONFIG_1_FLED_STRETCH_OFF        0x00
#define DIGIIO_CONFIG_1_FLED_STRETCH_1_S        0x04
#define DIGIIO_CONFIG_1_FLED_STRETCH_2_S        0x08
#define DIGIIO_CONFIG_1_FLED_STRETCH_3_S        0x0C
#define DIGIIO_CONFIG_1_FLED_STRETCH_MASK       0x0C
#define DIGIIO_CONFIG_1_SLED_SET_DOI            0x00
#define DIGIIO_CONFIG_1_SLED_SET_REG            0x02
#define DIGIIO_CONFIG_1_SLED_SET_MASK           0x02
#define DIGIIO_CONFIG_1_FLED_SET_DOI            0x00
#define DIGIIO_CONFIG_1_FLED_SET_REG            0x01
#define DIGIIO_CONFIG_1_FLED_SET_MASK           0x01

/**
 * @brief DIGI IO CONFIG_2 register setting.
 * @details Specified setting for CONFIG_2 register of DIGI IO Click driver.
 */
#define DIGIIO_CONFIG_2_WDTO_OFF                0x00
#define DIGIIO_CONFIG_2_WDTO_200_MS             0x40
#define DIGIIO_CONFIG_2_WDTO_600_MS             0x80
#define DIGIIO_CONFIG_2_WDTO_1200_MS            0xC0
#define DIGIIO_CONFIG_2_WDTO_MASK               0xC0
#define DIGIIO_CONFIG_2_OW_OFF_C_S_60_UA        0x00
#define DIGIIO_CONFIG_2_OW_OFF_C_S_100_UA       0x10
#define DIGIIO_CONFIG_2_OW_OFF_C_S_300_UA       0x20
#define DIGIIO_CONFIG_2_OW_OFF_C_S_600_UA       0x30
#define DIGIIO_CONFIG_2_OW_OFF_C_S_MASK         0x30
#define DIGIIO_CONFIG_2_SHT_VDD_THR_9_V         0x00
#define DIGIIO_CONFIG_2_SHT_VDD_THR_10_V        0x04
#define DIGIIO_CONFIG_2_SHT_VDD_THR_12_V        0x08
#define DIGIIO_CONFIG_2_SHT_VDD_THR_14_V        0x0C
#define DIGIIO_CONFIG_2_SHT_VDD_THR_MASK        0x0C
#define DIGIIO_CONFIG_2_SYNCH_WD_EN_OFF         0x00
#define DIGIIO_CONFIG_2_SYNCH_WD_EN_ON          0x02
#define DIGIIO_CONFIG_2_SYNCH_WD_EN_MASK        0x02
#define DIGIIO_CONFIG_2_VDD_ON_THR_OFF          0x00
#define DIGIIO_CONFIG_2_VDD_ON_THR_ON           0x01
#define DIGIIO_CONFIG_2_VDD_ON_THR_MASK         0x01

/**
 * @brief DIGI IO CONFIG_DI register setting.
 * @details Specified setting for CONFIG_DI register of DIGI IO Click driver.
 */
#define DIGIIO_CONFIG_DI_TYP_2_DI_TYPE_1_3      0x00
#define DIGIIO_CONFIG_DI_TYP_2_DI_TYPE_2        0x80
#define DIGIIO_CONFIG_DI_TYP_2_DI_MASK          0x80
#define DIGIIO_CONFIG_DI_VDD_FAULT_DIS_OFF      0x00
#define DIGIIO_CONFIG_DI_VDD_FAULT_DIS_ON       0x20
#define DIGIIO_CONFIG_DI_VDD_FAULT_DIS_MASK     0x20
#define DIGIIO_CONFIG_DI_VDD_FAULT_SEL_DOI      0x00
#define DIGIIO_CONFIG_DI_VDD_FAULT_SEL_VDDOK    0x10
#define DIGIIO_CONFIG_DI_VDD_FAULT_SEL_MASK     0x10
#define DIGIIO_CONFIG_DI_ABOVE_VDD_PROT_EN_OFF  0x00
#define DIGIIO_CONFIG_DI_ABOVE_VDD_PROT_EN_ON   0x08
#define DIGIIO_CONFIG_DI_ABOVE_VDD_PROT_EN_MASK 0x08
#define DIGIIO_CONFIG_DI_OVL_STRETCH_EN_OFF     0x00
#define DIGIIO_CONFIG_DI_OVL_STRETCH_EN_ON      0x04
#define DIGIIO_CONFIG_DI_OVL_STRETCH_EN_MASK    0x04
#define DIGIIO_CONFIG_DI_OVL_BLANK_OFF          0x00
#define DIGIIO_CONFIG_DI_OVL_BLANK_8_MS         0x01
#define DIGIIO_CONFIG_DI_OVL_BLANK_50_MS        0x02
#define DIGIIO_CONFIG_DI_OVL_BLANK_300_MS       0x03
#define DIGIIO_CONFIG_DI_OVL_BLANK_MASK         0x03

/**
 * @brief DIGI IO CONFIG_DO register setting.
 * @details Specified setting for CONFIG_DO register of DIGI IO Click driver.
 */
#define DIGIIO_CONFIG_DO_MODE4_HIGH_SIDE        0x00
#define DIGIIO_CONFIG_DO_MODE4_HIGH_SIDE_2X     0x40
#define DIGIIO_CONFIG_DO_MODE4_ACTIVE_CLAMP_PP  0x80
#define DIGIIO_CONFIG_DO_MODE4_SIMPLE_PP        0xC0
#define DIGIIO_CONFIG_DO_MODE4_MASK             0xC0
#define DIGIIO_CONFIG_DO_MODE3_HIGH_SIDE        0x00
#define DIGIIO_CONFIG_DO_MODE3_HIGH_SIDE_2X     0x10
#define DIGIIO_CONFIG_DO_MODE3_ACTIVE_CLAMP_PP  0x20
#define DIGIIO_CONFIG_DO_MODE3_SIMPLE_PP        0x30
#define DIGIIO_CONFIG_DO_MODE3_MASK             0x30
#define DIGIIO_CONFIG_DO_MODE2_HIGH_SIDE        0x00
#define DIGIIO_CONFIG_DO_MODE2_HIGH_SIDE_2X     0x04
#define DIGIIO_CONFIG_DO_MODE2_ACTIVE_CLAMP_PP  0x08
#define DIGIIO_CONFIG_DO_MODE2_SIMPLE_PP        0x0C
#define DIGIIO_CONFIG_DO_MODE2_MASK             0x0C
#define DIGIIO_CONFIG_DO_MODE1_HIGH_SIDE        0x00
#define DIGIIO_CONFIG_DO_MODE1_HIGH_SIDE_2X     0x01
#define DIGIIO_CONFIG_DO_MODE1_ACTIVE_CLAMP_PP  0x02
#define DIGIIO_CONFIG_DO_MODE1_SIMPLE_PP        0x03
#define DIGIIO_CONFIG_DO_MODE1_MASK             0x03

/**
 * @brief DIGI IO CURR_LIM register setting.
 * @details Specified setting for CURR_LIM register of DIGI IO Click driver.
 */
#define DIGIIO_CURR_LIM_CL4_600_MA              0x00
#define DIGIIO_CURR_LIM_CL4_130_MA              0x40
#define DIGIIO_CURR_LIM_CL4_300_MA              0x80
#define DIGIIO_CURR_LIM_CL4_1200_MA             0xC0
#define DIGIIO_CURR_LIM_CL4_MASK                0xC0
#define DIGIIO_CURR_LIM_CL3_600_MA              0x00
#define DIGIIO_CURR_LIM_CL3_130_MA              0x10
#define DIGIIO_CURR_LIM_CL3_300_MA              0x20
#define DIGIIO_CURR_LIM_CL3_1200_MA             0x30
#define DIGIIO_CURR_LIM_CL3_MASK                0x30
#define DIGIIO_CURR_LIM_CL2_600_MA              0x00
#define DIGIIO_CURR_LIM_CL2_130_MA              0x04
#define DIGIIO_CURR_LIM_CL2_300_MA              0x08
#define DIGIIO_CURR_LIM_CL2_1200_MA             0x0C
#define DIGIIO_CURR_LIM_CL2_MASK                0x0C
#define DIGIIO_CURR_LIM_CL1_600_MA              0x00
#define DIGIIO_CURR_LIM_CL1_130_MA              0x01
#define DIGIIO_CURR_LIM_CL1_300_MA              0x02
#define DIGIIO_CURR_LIM_CL1_1200_MA             0x03
#define DIGIIO_CURR_LIM_CL1_MASK                0x03

/**
 * @brief DIGI IO MASK register setting.
 * @details Specified setting for MASK register of DIGI IO Click driver.
 */
#define DIGIIO_MASK_COMM_ERR_M                  0x80
#define DIGIIO_MASK_SUPPLY_ERR_M                0x40
#define DIGIIO_MASK_VDD_OK_M                    0x20
#define DIGIIO_MASK_SHT_VDD_M                   0x10
#define DIGIIO_MASK_ABOVE_VDD_M                 0x08
#define DIGIIO_MASK_OW_OFF_M                    0x04
#define DIGIIO_MASK_CURR_LIM_M                  0x02
#define DIGIIO_MASK_OVER_LD_M                   0x01

/**
 * @brief DIGI IO CRC Settings setting.
 * @details Specified setting for CRC Settings of DIGI IO Click driver.
 */
#define DIGIIO_CRC_ENABLED                      0x01
#define DIGIIO_CRC_DISABLED                     0x00

/**
 * @brief DIGI IO chip address setting.
 * @details Specified setting for chip address of DIGI IO Click driver.
 */
#define DIGIIO_DEVICE_ADDRESS_0                 0x00
#define DIGIIO_DEVICE_ADDRESS_1                 0x40
#define DIGIIO_DEVICE_ADDRESS_2                 0x80
#define DIGIIO_DEVICE_ADDRESS_3                 0xC0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digiio_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIIO_SET_DATA_SAMPLE_EDGE             SET_SPI_DATA_SAMPLE_EDGE
#define DIGIIO_SET_DATA_SAMPLE_MIDDLE           SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digiio_set

/**
 * @defgroup digiio_map DIGI IO MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI IO Click driver.
 */

/**
 * @addtogroup digiio_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI IO Click to the selected MikroBUS.
 */
#define DIGIIO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.syn  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digiio_map
/*! @} */ // digiio

/**
 * @brief DIGI IO Click context object.
 * @details Context object definition of DIGI IO Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */
    digital_out_t syn;          /**< Synchronize pin (falling edge). */

    // Input pins
    digital_in_t rdy;           /**< Ready pin (active high). */
    digital_in_t flt;           /**< Fault pin (active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t device_address;     /**< Chip device Address. */
    uint8_t crc_en;             /**< CRC enable selection. */

} digiio_t;

/**
 * @brief DIGI IO Click configuration object.
 * @details Configuration object definition of DIGI IO Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rdy;             /**< Ready pin (active high). */
    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t syn;             /**< Synchronize pin (falling edge). */
    pin_name_t flt;             /**< Fault pin (active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} digiio_cfg_t;

/**
 * @brief DIGI IO Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIIO_OK = 0,
    DIGIIO_ERROR = -1

} digiio_return_value_t;

/*!
 * @addtogroup digiio DIGI IO Click Driver
 * @brief API for configuring and manipulating DIGI IO Click driver.
 * @{
 */

/**
 * @brief DIGI IO configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digiio_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digiio_cfg_setup ( digiio_cfg_t *cfg );

/**
 * @brief DIGI IO initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digiio_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiio_init ( digiio_t *ctx, digiio_cfg_t *cfg );

/**
 * @brief DIGI IO default configuration function.
 * @details This function executes a default configuration of DIGI IO
 * Click board.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digiio_default_cfg ( digiio_t *ctx );

/**
 * @brief DIGI IO set address function.
 * @details This function sets the device address.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @param[in] device_address : Selected device address.
 * @return None.
 * @note None.
 */
void digiio_set_address ( digiio_t *ctx, uint8_t device_address );

/**
 * @brief DIGI IO write reg function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiio_write_reg ( digiio_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DIGI IO read reg function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiio_read_reg ( digiio_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DIGI IO enable output function.
 * @details This function enables output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void digiio_enable_output ( digiio_t *ctx );

/**
 * @brief DIGI IO disable output function.
 * @details This function disables output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void digiio_disable_output ( digiio_t *ctx );

/**
 * @brief DIGI IO sync io function.
 * @details This function synchronizes registers by toggling the SYNC pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void digiio_sync_io ( digiio_t *ctx );

/**
 * @brief DIGI IO set sync pin function.
 * @details This function sets the SYNC pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void digiio_set_sync_pin ( digiio_t *ctx, uint8_t state );

/**
 * @brief DIGI IO get ready pin function.
 * @details This function returns the READY pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t digiio_get_ready_pin ( digiio_t *ctx );

/**
 * @brief DIGI IO get fault pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiio_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t digiio_get_fault_pin ( digiio_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIIO_H

/*! @} */ // digiio

// ------------------------------------------------------------------------ END

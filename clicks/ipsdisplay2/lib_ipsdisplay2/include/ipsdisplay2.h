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
 * @file ipsdisplay2.h
 * @brief This file contains API for IPS Display 2 Click Driver.
 */

#ifndef IPSDISPLAY2_H
#define IPSDISPLAY2_H

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
 * @addtogroup ipsdisplay2 IPS Display 2 Click Driver
 * @brief API for configuring and manipulating IPS Display 2 Click driver.
 * @{
 */

/**
 * @defgroup ipsdisplay2_reg IPS Display 2 Commands List
 * @brief List of commands of IPS Display 2 Click driver.
 */

/**
 * @addtogroup ipsdisplay2_cmd
 * @{
 */

/**
 * @brief IPS Display 2 system function command list 1.
 * @details Specified system function command list 1 of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_CMD_NOP                     0x00
#define IPSDISPLAY2_CMD_SWRESET                 0x01
#define IPSDISPLAY2_CMD_RDDID                   0x04
#define IPSDISPLAY2_CMD_RDDST                   0x09
#define IPSDISPLAY2_CMD_RDDPM                   0x0A
#define IPSDISPLAY2_CMD_RDDMADCTL               0x0B
#define IPSDISPLAY2_CMD_RDDCOLMOD               0x0C
#define IPSDISPLAY2_CMD_RDDIM                   0x0D
#define IPSDISPLAY2_CMD_RDDSM                   0x0E
#define IPSDISPLAY2_CMD_RDDSDR                  0x0F
#define IPSDISPLAY2_CMD_SLPIN                   0x10
#define IPSDISPLAY2_CMD_SLPOUT                  0x11
#define IPSDISPLAY2_CMD_PTLON                   0x12
#define IPSDISPLAY2_CMD_NORON                   0x13
#define IPSDISPLAY2_CMD_INVOFF                  0x20
#define IPSDISPLAY2_CMD_INVON                   0x21
#define IPSDISPLAY2_CMD_GAMSET                  0x26
#define IPSDISPLAY2_CMD_DISPOFF                 0x28
#define IPSDISPLAY2_CMD_DISPON                  0x29
#define IPSDISPLAY2_CMD_CASET                   0x2A
#define IPSDISPLAY2_CMD_RASET                   0x2B
#define IPSDISPLAY2_CMD_RAMWR                   0x2C
#define IPSDISPLAY2_CMD_RAMRD                   0x2E
#define IPSDISPLAY2_CMD_PTLAR                   0x30
#define IPSDISPLAY2_CMD_VSCRDEF                 0x33
#define IPSDISPLAY2_CMD_TEOFF                   0x34
#define IPSDISPLAY2_CMD_TEON                    0x35
#define IPSDISPLAY2_CMD_MADCTL                  0x36
#define IPSDISPLAY2_CMD_VSCRSADD                0x37
#define IPSDISPLAY2_CMD_IDMOFF                  0x38
#define IPSDISPLAY2_CMD_IDMON                   0x39
#define IPSDISPLAY2_CMD_COLMOD                  0x3A
#define IPSDISPLAY2_CMD_RAMWRC                  0x3C
#define IPSDISPLAY2_CMD_RAMRDC                  0x3E
#define IPSDISPLAY2_CMD_TESCAN                  0x44
#define IPSDISPLAY2_CMD_RDTESCAN                0x45
#define IPSDISPLAY2_CMD_WRDISBV                 0x51
#define IPSDISPLAY2_CMD_RDDISBV                 0x52
#define IPSDISPLAY2_CMD_WRCTRLD                 0x53
#define IPSDISPLAY2_CMD_RDCTRLD                 0x54
#define IPSDISPLAY2_CMD_WRCACE                  0x55
#define IPSDISPLAY2_CMD_RDCABC                  0x56
#define IPSDISPLAY2_CMD_WRCABCMB                0x5E
#define IPSDISPLAY2_CMD_RDCABCMB                0x5F
#define IPSDISPLAY2_CMD_RDABCSDR                0x68
#define IPSDISPLAY2_CMD_RDID1                   0xDA
#define IPSDISPLAY2_CMD_RDID2                   0xDB
#define IPSDISPLAY2_CMD_RDID3                   0xDC

/**
 * @brief IPS Display 2 system function command list 2.
 * @details Specified system function command list 2 of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_CMD_RAMCTRL                 0xB0
#define IPSDISPLAY2_CMD_RGBCTRL                 0xB1
#define IPSDISPLAY2_CMD_PORCTRL                 0xB2
#define IPSDISPLAY2_CMD_FRCTRL1                 0xB3
#define IPSDISPLAY2_CMD_PARCTRL                 0xB5
#define IPSDISPLAY2_CMD_GCTRL                   0xB7
#define IPSDISPLAY2_CMD_GTADJ                   0xB8
#define IPSDISPLAY2_CMD_DGMEN                   0xBA
#define IPSDISPLAY2_CMD_VCOMS                   0xBB
#define IPSDISPLAY2_CMD_POWSAVE                 0xBC
#define IPSDISPLAY2_CMD_DLPOFFSAVE              0xBD
#define IPSDISPLAY2_CMD_LCMCTRL                 0xC0
#define IPSDISPLAY2_CMD_IDSET                   0xC1
#define IPSDISPLAY2_CMD_VDVVRHEN                0xC2
#define IPSDISPLAY2_CMD_VRHS                    0xC3
#define IPSDISPLAY2_CMD_VDVSET                  0xC4
#define IPSDISPLAY2_CMD_VCMOFSET                0xC5
#define IPSDISPLAY2_CMD_FRCTR2                  0xC6
#define IPSDISPLAY2_CMD_CABCCTRL                0xC7
#define IPSDISPLAY2_CMD_REGSEL1                 0xC8
#define IPSDISPLAY2_CMD_REGSEL2                 0xCA
#define IPSDISPLAY2_CMD_PWMFRSEL                0xCC
#define IPSDISPLAY2_CMD_PWCTRL1                 0xD0
#define IPSDISPLAY2_CMD_VAPVANEN                0xD2
#define IPSDISPLAY2_CMD_CMD2EN0                 0xDF
#define IPSDISPLAY2_CMD_CMD2EN1                 0x5A
#define IPSDISPLAY2_CMD_CMD2EN2                 0x69
#define IPSDISPLAY2_CMD_CMD2EN3                 0x02
#define IPSDISPLAY2_CMD_PVGAMCTRL               0xE0
#define IPSDISPLAY2_CMD_NVGAMCTRL               0xE1
#define IPSDISPLAY2_CMD_DGMLUTR                 0xE2
#define IPSDISPLAY2_CMD_DGMLUTB                 0xE3
#define IPSDISPLAY2_CMD_GATECTRL                0xE4
#define IPSDISPLAY2_CMD_SPI2EN                  0xE7
#define IPSDISPLAY2_CMD_PWCTRL2                 0xE8
#define IPSDISPLAY2_CMD_EQCTRL                  0xE9
#define IPSDISPLAY2_CMD_PROMCTRL                0xEC
#define IPSDISPLAY2_CMD_PROMEN                  0xFA
#define IPSDISPLAY2_CMD_NVMSET                  0xFC
#define IPSDISPLAY2_CMD_PROMACT                 0xFE

/*! @} */ // ipsdisplay2_cmd

/**
 * @defgroup ipsdisplay2_set IPS Display 2 Registers Settings
 * @brief Settings for registers of IPS Display 2 Click driver.
 */

/**
 * @addtogroup ipsdisplay2_set
 * @{
 */

/**
 * @brief IPS Display 2 MADCTL command setting.
 * @details Specified setting for MADCTL command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_MADCTL_DEFAULT              0x00
#define IPSDISPLAY2_MADCTL_MY                   0x80
#define IPSDISPLAY2_MADCTL_MX                   0x40
#define IPSDISPLAY2_MADCTL_MV                   0x20
#define IPSDISPLAY2_MADCTL_ML                   0x10
#define IPSDISPLAY2_MADCTL_RGB                  0x08
#define IPSDISPLAY2_MADCTL_MH                   0x04

/**
 * @brief IPS Display 2 COLMOD command setting.
 * @details Specified setting for COLMOD command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_COLMOD_RGB_65K              0x50
#define IPSDISPLAY2_COLMOD_RGB_262K             0x60
#define IPSDISPLAY2_COLMOD_RGB_MASK             0x70
#define IPSDISPLAY2_COLMOD_CTRL_12BIT_PIXEL     0x03
#define IPSDISPLAY2_COLMOD_CTRL_16BIT_PIXEL     0x05
#define IPSDISPLAY2_COLMOD_CTRL_18BIT_PIXEL     0x06
#define IPSDISPLAY2_COLMOD_CTRL_16M_TRUNCATED   0x07
#define IPSDISPLAY2_COLMOD_CTRL_MASK            0x07

/**
 * @brief IPS Display 2 PORCTRL command setting.
 * @details Specified setting for PORCTRL command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_PORCTRL_0_BPA_DEFAULT       0x0C
#define IPSDISPLAY2_PORCTRL_0_BPA_MASK          0x7F
#define IPSDISPLAY2_PORCTRL_1_FPA_DEFAULT       0x0C
#define IPSDISPLAY2_PORCTRL_1_FPA_MASK          0x7F
#define IPSDISPLAY2_PORCTRL_2_PSEN_DISABLE      0x00
#define IPSDISPLAY2_PORCTRL_2_PSEN_ENABLE       0x01
#define IPSDISPLAY2_PORCTRL_3_BPB_DEFAULT       0x30
#define IPSDISPLAY2_PORCTRL_3_BPB_MASK          0xF0
#define IPSDISPLAY2_PORCTRL_3_FPB_DEFAULT       0x03
#define IPSDISPLAY2_PORCTRL_3_FPB_MASK          0x0F
#define IPSDISPLAY2_PORCTRL_4_BPC_DEFAULT       0x30
#define IPSDISPLAY2_PORCTRL_4_BPC_MASK          0xF0
#define IPSDISPLAY2_PORCTRL_4_FPC_DEFAULT       0x03
#define IPSDISPLAY2_PORCTRL_4_FPC_MASK          0x0F

/**
 * @brief IPS Display 2 GCTRL command setting.
 * @details Specified setting for GCTRL command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_GCTRL_VGHS_DEFAULT          0x30
#define IPSDISPLAY2_GCTRL_VGHS_MASK             0x70
#define IPSDISPLAY2_GCTRL_VGLS_DEFAULT          0x05
#define IPSDISPLAY2_GCTRL_VGLS_MASK             0x07

/**
 * @brief IPS Display 2 VCOMS command setting.
 * @details Specified setting for VCOMS command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_VCOMS_VCOM_DEFAULT          0x3A
#define IPSDISPLAY2_VCOMS_VCOM_MASK             0x3F

/**
 * @brief IPS Display 2 LCMCTRL command setting.
 * @details Specified setting for LCMCTRL command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_LCMCTRL_XMY                 0x40
#define IPSDISPLAY2_LCMCTRL_XBGR                0x20
#define IPSDISPLAY2_LCMCTRL_XINV                0x10
#define IPSDISPLAY2_LCMCTRL_XMX                 0x08
#define IPSDISPLAY2_LCMCTRL_XMH                 0x04
#define IPSDISPLAY2_LCMCTRL_XMV                 0x02
#define IPSDISPLAY2_LCMCTRL_XGS                 0x01

/**
 * @brief IPS Display 2 VDVVRHEN command setting.
 * @details Specified setting for VDVVRHEN command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_VDVVRHEN_CMDEN_DISABLE      0x00
#define IPSDISPLAY2_VDVVRHEN_CMDEN_ENABLE       0x01

/**
 * @brief IPS Display 2 VRHS command setting.
 * @details Specified setting for VRHS command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_VRHS_DEFAULT                0x19
#define IPSDISPLAY2_VRHS_MASK                   0x3F

/**
 * @brief IPS Display 2 VDVSET command setting.
 * @details Specified setting for VDVSET command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_VDVSET_DEFAULT              0x20
#define IPSDISPLAY2_VDVSET_MASK                 0x3F

/**
 * @brief IPS Display 2 FRCTR2 command setting.
 * @details Specified setting for FRCTR2 command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_FRCTR2_NLA_DEFAULT          0x00
#define IPSDISPLAY2_FRCTR2_NLA_MASK             0xE0
#define IPSDISPLAY2_FRCTR2_RTNA_DEFAULT         0x0F
#define IPSDISPLAY2_FRCTR2_RTNA_MASK            0x1F

/**
 * @brief IPS Display 2 PWCTRL1 command setting.
 * @details Specified setting for PWCTRL1 command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_PWCTRL1_0_DEFAULT           0xA4
#define IPSDISPLAY2_PWCTRL1_1_AVDD_DEFAULT      0x80
#define IPSDISPLAY2_PWCTRL1_1_AVDD_MASK         0xC0
#define IPSDISPLAY2_PWCTRL1_1_AVCL_DEFAULT      0x20
#define IPSDISPLAY2_PWCTRL1_1_AVCL_MASK         0x30
#define IPSDISPLAY2_PWCTRL1_1_VDS_DEFAULT       0x01
#define IPSDISPLAY2_PWCTRL1_1_VDS_MASK          0x03

/**
 * @brief IPS Display 2 PVGAMCTRL command setting.
 * @details Specified setting for PVGAMCTRL command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_PVGAMCTRL_0_V63P_DEFAULT    0xD0
#define IPSDISPLAY2_PVGAMCTRL_0_V63P_MASK       0xF0
#define IPSDISPLAY2_PVGAMCTRL_0_V0P_DEFAULT     0x00
#define IPSDISPLAY2_PVGAMCTRL_0_V0P_MASK        0x0F
#define IPSDISPLAY2_PVGAMCTRL_1_V1P_DEFAULT     0x08
#define IPSDISPLAY2_PVGAMCTRL_1_V1P_MASK        0x3F
#define IPSDISPLAY2_PVGAMCTRL_2_V2P_DEFAULT     0x0E
#define IPSDISPLAY2_PVGAMCTRL_2_V2P_MASK        0x3F
#define IPSDISPLAY2_PVGAMCTRL_3_V4P_DEFAULT     0x09
#define IPSDISPLAY2_PVGAMCTRL_3_V4P_MASK        0x1F
#define IPSDISPLAY2_PVGAMCTRL_4_V6P_DEFAULT     0x09
#define IPSDISPLAY2_PVGAMCTRL_4_V6P_MASK        0x1F
#define IPSDISPLAY2_PVGAMCTRL_5_J0P_DEFAULT     0x00
#define IPSDISPLAY2_PVGAMCTRL_5_J0P_MASK        0x30
#define IPSDISPLAY2_PVGAMCTRL_5_J13P_DEFAULT    0x05
#define IPSDISPLAY2_PVGAMCTRL_5_J13P_MASK       0x0F
#define IPSDISPLAY2_PVGAMCTRL_6_V20P_DEFAULT    0x31
#define IPSDISPLAY2_PVGAMCTRL_6_V20P_MASK       0x7F
#define IPSDISPLAY2_PVGAMCTRL_7_V36P_DEFAULT    0x30
#define IPSDISPLAY2_PVGAMCTRL_7_V36P_MASK       0x70
#define IPSDISPLAY2_PVGAMCTRL_7_V27P_DEFAULT    0x03
#define IPSDISPLAY2_PVGAMCTRL_7_V27P_MASK       0x07
#define IPSDISPLAY2_PVGAMCTRL_8_V43P_DEFAULT    0x48
#define IPSDISPLAY2_PVGAMCTRL_8_V43P_MASK       0x7F
#define IPSDISPLAY2_PVGAMCTRL_9_J1P_DEFAULT     0x10
#define IPSDISPLAY2_PVGAMCTRL_9_11P_MASK        0x30
#define IPSDISPLAY2_PVGAMCTRL_9_V50P_DEFAULT    0x07
#define IPSDISPLAY2_PVGAMCTRL_9_V50P_MASK       0x0F
#define IPSDISPLAY2_PVGAMCTRL_10_V57P_DEFAULT   0x14
#define IPSDISPLAY2_PVGAMCTRL_10_V57P_MASK      0x1F
#define IPSDISPLAY2_PVGAMCTRL_11_V59P_DEFAULT   0x15
#define IPSDISPLAY2_PVGAMCTRL_11_V59P_MASK      0x1F
#define IPSDISPLAY2_PVGAMCTRL_12_V61P_DEFAULT   0x31
#define IPSDISPLAY2_PVGAMCTRL_12_V61P_MASK      0x3F
#define IPSDISPLAY2_PVGAMCTRL_13_V62P_DEFAULT   0x34
#define IPSDISPLAY2_PVGAMCTRL_13_V62P_MASK      0x3F

/**
 * @brief IPS Display 2 NVGAMCTRL command setting.
 * @details Specified setting for NVGAMCTRL command of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_NVGAMCTRL_0_V63N_DEFAULT    0xD0
#define IPSDISPLAY2_NVGAMCTRL_0_V63N_MASK       0xF0
#define IPSDISPLAY2_NVGAMCTRL_0_V0N_DEFAULT     0x00
#define IPSDISPLAY2_NVGAMCTRL_0_V0N_MASK        0x0F
#define IPSDISPLAY2_NVGAMCTRL_1_V1N_DEFAULT     0x08
#define IPSDISPLAY2_NVGAMCTRL_1_V1N_MASK        0x3F
#define IPSDISPLAY2_NVGAMCTRL_2_V2N_DEFAULT     0x0E
#define IPSDISPLAY2_NVGAMCTRL_2_V2N_MASK        0x3F
#define IPSDISPLAY2_NVGAMCTRL_3_V4N_DEFAULT     0x09
#define IPSDISPLAY2_NVGAMCTRL_3_V4N_MASK        0x1F
#define IPSDISPLAY2_NVGAMCTRL_4_V6N_DEFAULT     0x09
#define IPSDISPLAY2_NVGAMCTRL_4_V6N_MASK        0x1F
#define IPSDISPLAY2_NVGAMCTRL_5_J0N_DEFAULT     0x10
#define IPSDISPLAY2_NVGAMCTRL_5_J0N_MASK        0x30
#define IPSDISPLAY2_NVGAMCTRL_5_J13N_DEFAULT    0x05
#define IPSDISPLAY2_NVGAMCTRL_5_J13N_MASK       0x0F
#define IPSDISPLAY2_NVGAMCTRL_6_V20N_DEFAULT    0x31
#define IPSDISPLAY2_NVGAMCTRL_6_V20N_MASK       0x7F
#define IPSDISPLAY2_NVGAMCTRL_7_V36N_DEFAULT    0x30
#define IPSDISPLAY2_NVGAMCTRL_7_V36N_MASK       0x70
#define IPSDISPLAY2_NVGAMCTRL_7_V27N_DEFAULT    0x03
#define IPSDISPLAY2_NVGAMCTRL_7_V27N_MASK       0x07
#define IPSDISPLAY2_NVGAMCTRL_8_V43N_DEFAULT    0x48
#define IPSDISPLAY2_NVGAMCTRL_8_V43N_MASK       0x7F
#define IPSDISPLAY2_NVGAMCTRL_9_J1N_DEFAULT     0x10
#define IPSDISPLAY2_NVGAMCTRL_9_11N_MASK        0x30
#define IPSDISPLAY2_NVGAMCTRL_9_V50N_DEFAULT    0x07
#define IPSDISPLAY2_NVGAMCTRL_9_V50N_MASK       0x0F
#define IPSDISPLAY2_NVGAMCTRL_10_V57N_DEFAULT   0x14
#define IPSDISPLAY2_NVGAMCTRL_10_V57N_MASK      0x1F
#define IPSDISPLAY2_NVGAMCTRL_11_V59N_DEFAULT   0x15
#define IPSDISPLAY2_NVGAMCTRL_11_V59N_MASK      0x1F
#define IPSDISPLAY2_NVGAMCTRL_12_V61N_DEFAULT   0x31
#define IPSDISPLAY2_NVGAMCTRL_12_V61N_MASK      0x3F
#define IPSDISPLAY2_NVGAMCTRL_13_V62N_DEFAULT   0x34
#define IPSDISPLAY2_NVGAMCTRL_13_V62N_MASK      0x3F

/**
 * @brief IPS Display 2 resolution setting.
 * @details Specified setting for display resolution of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_RES_WIDTH                   240
#define IPSDISPLAY2_RES_HEIGHT                  240
#define IPSDISPLAY2_NUM_PIXELS                  ( ( uint16_t ) IPSDISPLAY2_RES_WIDTH * IPSDISPLAY2_RES_HEIGHT )

/**
 * @brief IPS Display 2 position and coordinates setting.
 * @details Specified setting for display position and coordinates of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_POS_WIDTH_MIN               0
#define IPSDISPLAY2_POS_WIDTH_MAX               ( IPSDISPLAY2_RES_WIDTH - 1 )
#define IPSDISPLAY2_POS_HEIGHT_MIN              0
#define IPSDISPLAY2_POS_HEIGHT_MAX              ( IPSDISPLAY2_RES_HEIGHT - 1 )
#define IPSDISPLAY2_POS_OFFSET_LEFT             0
#define IPSDISPLAY2_POS_OFFSET_RIGHT            0
#define IPSDISPLAY2_POS_OFFSET_UP               0
#define IPSDISPLAY2_POS_OFFSET_DOWN             80

/**
 * @brief IPS Display 2 font setting.
 * @details Specified setting for font of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_FONT_WIDTH                  6
#define IPSDISPLAY2_FONT_HEIGHT                 12
#define IPSDISPLAY2_FONT_TEXT_SPACE             1
#define IPSDISPLAY2_FONT_ASCII_OFFSET           32
#define IPSDISPLAY2_FONT_WIDTH_MSB              0x80

/**
 * @brief IPS Display 2 rotation setting.
 * @details Specified setting for rotation of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_ROTATION_VERTICAL_0         0
#define IPSDISPLAY2_ROTATION_VERTICAL_180       1
#define IPSDISPLAY2_ROTATION_HORIZONTAL_0       2
#define IPSDISPLAY2_ROTATION_HORIZONTAL_180     3

/**
 * @brief IPS Display 2 RGB565 colors definition.
 * @details Specified definition for RGB565 colors of IPS Display 2 Click driver.
 */
#define IPSDISPLAY2_COLOR_BLACK                 0x0000
#define IPSDISPLAY2_COLOR_WHITE                 0xFFFF
#define IPSDISPLAY2_COLOR_RED                   0xF800
#define IPSDISPLAY2_COLOR_LIME                  0x07E0
#define IPSDISPLAY2_COLOR_BLUE                  0x001F
#define IPSDISPLAY2_COLOR_YELLOW                0xFFE0
#define IPSDISPLAY2_COLOR_CYAN                  0x07FF
#define IPSDISPLAY2_COLOR_MAGENTA               0xF81F
#define IPSDISPLAY2_COLOR_SILVER                0xBDF7
#define IPSDISPLAY2_COLOR_GRAY                  0x8410
#define IPSDISPLAY2_COLOR_MAROON                0x8000
#define IPSDISPLAY2_COLOR_OLIVE                 0x8400
#define IPSDISPLAY2_COLOR_GREEN                 0x0400
#define IPSDISPLAY2_COLOR_PURPLE                0x8010
#define IPSDISPLAY2_COLOR_TEAL                  0x0410
#define IPSDISPLAY2_COLOR_NAVY                  0x0010

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ipsdisplay2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define IPSDISPLAY2_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define IPSDISPLAY2_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ipsdisplay2_set

/**
 * @defgroup ipsdisplay2_map IPS Display 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IPS Display 2 Click driver.
 */

/**
 * @addtogroup ipsdisplay2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IPS Display 2 Click to the selected MikroBUS.
 */
#define IPSDISPLAY2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bck  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dc   = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ipsdisplay2_map
/*! @} */ // ipsdisplay2

/**
 * @brief IPS Display 2 Click context object.
 * @details Context object definition of IPS Display 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< This signal will reset the device, Signal is active low. */
    digital_out_t dc;               /**< Display data/command selection pin in 4-line serial interface. */
    digital_out_t cs;               /**< Display chip select pin. */
    digital_out_t bck;              /**< Backlight enable pin (Active High). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      rotation;          /**< Screen rotation settings. */

} ipsdisplay2_t;

/**
 * @brief IPS Display 2 Click configuration object.
 * @details Configuration object definition of IPS Display 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< This signal will reset the device, Signal is active low. */
    pin_name_t dc;                  /**< Display data/command selection pin in 4-line serial interface. */
    pin_name_t bck;                 /**< Backlight enable pin (Active High). */

    // static variable
    uint32_t            spi_speed;  /**< SPI serial speed. */
    spi_master_mode_t   spi_mode;   /**< SPI master mode. */

} ipsdisplay2_cfg_t;

/**
 * @brief IPS Display 2 Click point coordinates object.
 * @details Point coordinates object definition of IPS Display 2 Click driver.
 */
typedef struct
{
    uint16_t x;                     /**< X coordinate. */
    uint16_t y;                     /**< Y coordinate. */

} ipsdisplay2_point_t;

/**
 * @brief IPS Display 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IPSDISPLAY2_OK = 0,
    IPSDISPLAY2_ERROR = -1

} ipsdisplay2_return_value_t;

/*!
 * @addtogroup ipsdisplay2 IPS Display 2 Click Driver
 * @brief API for configuring and manipulating IPS Display 2 Click driver.
 * @{
 */

/**
 * @brief IPS Display 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ipsdisplay2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ipsdisplay2_cfg_setup ( ipsdisplay2_cfg_t *cfg );

/**
 * @brief IPS Display 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ipsdisplay2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_init ( ipsdisplay2_t *ctx, ipsdisplay2_cfg_t *cfg );

/**
 * @brief IPS Display 2 default configuration function.
 * @details This function executes a default configuration of IPS Display 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ipsdisplay2_default_cfg ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 write cmd function.
 * @details This function writes a command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_write_cmd ( ipsdisplay2_t *ctx, uint8_t cmd );

/**
 * @brief IPS Display 2 write cmd par function.
 * @details This function writes a desired number of data parameters to the selected command
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_write_cmd_par ( ipsdisplay2_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief IPS Display 2 write data function.
 * @details This function writes a desired number of data words by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written (16-bit array).
 * @param[in] len : Number of words to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_write_data ( ipsdisplay2_t *ctx, uint16_t *data_in, uint16_t len );

/**
 * @brief IPS Display 2 disable device function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_disable_device ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 enable device function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_enable_device ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_reset_device ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 disable backlight function.
 * @details This function disables the backlight by setting the BCK pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_disable_backlight ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 enable backlight function.
 * @details This function enables the backlight by setting the BCK pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_enable_backlight ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 enter cmd mode function.
 * @details This function enters the command mode by setting the DC pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_enter_cmd_mode ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 enter data mode function.
 * @details This function enters the data mode by setting the DC pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay2_enter_data_mode ( ipsdisplay2_t *ctx );

/**
 * @brief IPS Display 2 set rotation function.
 * @details This function sets the display rotation.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] rotation : @li @c 0 - Vertical 0 - Normal,
 *                       @li @c 1 - Vertical 180 - XY mirrored,
 *                       @li @c 2 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 3 - Horizontal 180 - XY exchanged, Y mirrored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_set_rotation ( ipsdisplay2_t *ctx, uint8_t rotation );

/**
 * @brief IPS Display 2 set pos function.
 * @details This function sets the coordinates of editable display area.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] end_pt : End point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay2_set_pos ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, ipsdisplay2_point_t end_pt );

/**
 * @brief IPS Display 2 fill screen function.
 * @details This function fills the screen with the selected color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_fill_screen ( ipsdisplay2_t *ctx, uint16_t color );

/**
 * @brief IPS Display 2 write char function.
 * @details This function writes a single ASCII character on the selected position in a 6x12 font size
 * with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] data_in : ASCII(32-126) char to write.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_write_char ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, uint8_t data_in, uint16_t color );

/**
 * @brief IPS Display 2 write string function.
 * @details This function writes a text string starting from the selected position in a 6x12 font size
 * with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] data_in : ASCII(32-126) string to write (must end with \0).
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_write_string ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, uint8_t *data_in, uint16_t color );

/**
 * @brief IPS Display 2 draw pixel function.
 * @details This function draws a pixel on the selected position with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay2_draw_pixel ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, uint16_t color );

/**
 * @brief IPS Display 2 draw line function.
 * @details This function draws a line with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] end_pt : End point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay2_draw_line ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, 
                              ipsdisplay2_point_t end_pt, uint16_t color );

/**
 * @brief IPS Display 2 draw rectangle function.
 * @details This function draws a rectangle with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] end_pt : End point coordinates.
 * See #iipsdisplay2_point_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay2_draw_rectangle ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, 
                                   ipsdisplay2_point_t end_pt, uint16_t color );

/**
 * @brief IPS Display 2 draw circle function.
 * @details This function draws a circle with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] center_pt : Center point coordinates.
 * @param[in] radius : Circle radius.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay2_draw_circle ( ipsdisplay2_t *ctx, ipsdisplay2_point_t center_pt, uint8_t radius, uint16_t color );

/**
 * @brief IPS Display 2 draw picture function.
 * @details This function draws a picture with a specified color in a desired display orientation.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay2_t object definition for detailed explanation.
 * @param[in] rotation : @li @c 0 - Vertical 0 - Normal,
 *                       @li @c 1 - Vertical 180 - XY mirrored,
 *                       @li @c 2 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 3 - Horizontal 180 - XY exchanged, Y mirrored.
 * @param[in] image : Image array.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay2_draw_picture ( ipsdisplay2_t *ctx, uint8_t rotation, const uint16_t *image );

#ifdef __cplusplus
}
#endif
#endif // IPSDISPLAY2_H

/*! @} */ // ipsdisplay2

// ------------------------------------------------------------------------ END

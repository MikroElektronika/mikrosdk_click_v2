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
 * @file ipsdisplay3.h
 * @brief This file contains API for IPS Display 3 Click Driver.
 */

#ifndef IPSDISPLAY3_H
#define IPSDISPLAY3_H

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
 * @addtogroup ipsdisplay3 IPS Display 3 Click Driver
 * @brief API for configuring and manipulating IPS Display 3 Click driver.
 * @{
 */

/**
 * @defgroup ipsdisplay3_reg IPS Display 3 Commands List
 * @brief List of commands of IPS Display 3 Click driver.
 */

/**
 * @addtogroup ipsdisplay3_cmd
 * @{
 */

/**
 * @brief IPS Display 3 regulative command set.
 * @details Specified regulative command set of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_CMD_NOP                     0x00
#define IPSDISPLAY3_CMD_SWRESET                 0x01
#define IPSDISPLAY3_CMD_RDDID                   0x04
#define IPSDISPLAY3_CMD_RDDST                   0x09
#define IPSDISPLAY3_CMD_RDDPM                   0x0A
#define IPSDISPLAY3_CMD_RDDMADCTL               0x0B
#define IPSDISPLAY3_CMD_RDDCOLMOD               0x0C
#define IPSDISPLAY3_CMD_RDDIM                   0x0D
#define IPSDISPLAY3_CMD_RDDSM                   0x0E
#define IPSDISPLAY3_CMD_RDDSDR                  0x0F
#define IPSDISPLAY3_CMD_SLPIN                   0x10
#define IPSDISPLAY3_CMD_SLPOUT                  0x11
#define IPSDISPLAY3_CMD_PTLON                   0x12
#define IPSDISPLAY3_CMD_NORON                   0x13
#define IPSDISPLAY3_CMD_INVOFF                  0x20
#define IPSDISPLAY3_CMD_INVON                   0x21
#define IPSDISPLAY3_CMD_DISPOFF                 0x28
#define IPSDISPLAY3_CMD_DISPON                  0x29
#define IPSDISPLAY3_CMD_CASET                   0x2A
#define IPSDISPLAY3_CMD_RASET                   0x2B
#define IPSDISPLAY3_CMD_RAMWR                   0x2C
#define IPSDISPLAY3_CMD_RAMRD                   0x2E
#define IPSDISPLAY3_CMD_PTLAR                   0x30
#define IPSDISPLAY3_CMD_VSCRDEF                 0x33
#define IPSDISPLAY3_CMD_TEOFF                   0x34
#define IPSDISPLAY3_CMD_TEON                    0x35
#define IPSDISPLAY3_CMD_MADCTL                  0x36
#define IPSDISPLAY3_CMD_VSCRSADD                0x37
#define IPSDISPLAY3_CMD_IDMOFF                  0x38
#define IPSDISPLAY3_CMD_IDMON                   0x39
#define IPSDISPLAY3_CMD_COLMOD                  0x3A
#define IPSDISPLAY3_CMD_TESCAN                  0x44
#define IPSDISPLAY3_CMD_RDTESCAN                0x45
#define IPSDISPLAY3_CMD_CUSDID                  0xD3
#define IPSDISPLAY3_CMD_RDID1                   0xDA
#define IPSDISPLAY3_CMD_RDID2                   0xDB
#define IPSDISPLAY3_CMD_RDID3                   0xDC

/**
 * @brief IPS Display 3 internal command set.
 * @details Specified internal command set of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_CMD_FRS                     0xA8
#define IPSDISPLAY3_CMD_AB                      0xAB
#define IPSDISPLAY3_CMD_CPRRGB565               0xAC
#define IPSDISPLAY3_CMD_BLPCTRL                 0xAD
#define IPSDISPLAY3_CMD_B0                      0xB0
#define IPSDISPLAY3_CMD_B1                      0xB1
#define IPSDISPLAY3_CMD_B2                      0xB2
#define IPSDISPLAY3_CMD_B3                      0xB3
#define IPSDISPLAY3_CMD_INVCTRL                 0xB4
#define IPSDISPLAY3_CMD_B6                      0xB6
#define IPSDISPLAY3_CMD_B7                      0xB7
#define IPSDISPLAY3_CMD_B8                      0xB8
#define IPSDISPLAY3_CMD_C6                      0xC6
#define IPSDISPLAY3_CMD_C7                      0xC7
#define IPSDISPLAY3_CMD_AVDDVCLSET              0xE2
#define IPSDISPLAY3_CMD_AVDDVCLCLK              0xE3
#define IPSDISPLAY3_CMD_VREGCTL                 0xE7
#define IPSDISPLAY3_CMD_VGHSET                  0xE8
#define IPSDISPLAY3_CMD_VGLSET                  0xE9
#define IPSDISPLAY3_CMD_VGHVGLCLK               0xEA
#define IPSDISPLAY3_CMD_IREGEN2                 0xEF
#define IPSDISPLAY3_CMD_SETGAMMA0               0xF0
#define IPSDISPLAY3_CMD_SETGAMMA1               0xF1
#define IPSDISPLAY3_CMD_IREGEN1                 0xFE

/*! @} */ // ipsdisplay3_cmd

/**
 * @defgroup ipsdisplay3_set IPS Display 3 Registers Settings
 * @brief Settings for registers of IPS Display 3 Click driver.
 */

/**
 * @addtogroup ipsdisplay3_set
 * @{
 */

/**
 * @brief IPS Display 3 MADCTL command setting.
 * @details Specified setting for MADCTL command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_MADCTL_DEFAULT              0x00
#define IPSDISPLAY3_MADCTL_MY                   0x80
#define IPSDISPLAY3_MADCTL_MX                   0x40
#define IPSDISPLAY3_MADCTL_MV                   0x20
#define IPSDISPLAY3_MADCTL_ML                   0x10
#define IPSDISPLAY3_MADCTL_RGB                  0x08

/**
 * @brief IPS Display 3 COLMOD command setting.
 * @details Specified setting for COLMOD command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_COLMOD_CTRL_12BIT_PIXEL     0x01
#define IPSDISPLAY3_COLMOD_CTRL_16BIT_PIXEL     0x05
#define IPSDISPLAY3_COLMOD_CTRL_18BIT_PIXEL     0x06
#define IPSDISPLAY3_COLMOD_CTRL_MASK            0x07

/**
 * @brief IPS Display 3 unknown commands setting.
 * @details Specified setting for unknown commands of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_AB_DEFAULT                  0x0F
#define IPSDISPLAY3_B0_DEFAULT                  0xC0
#define IPSDISPLAY3_B1_DEFAULT                  0x80
#define IPSDISPLAY3_B2_DEFAULT                  0x2F
#define IPSDISPLAY3_B3_DEFAULT                  0x03
#define IPSDISPLAY3_B6_DEFAULT                  0x19
#define IPSDISPLAY3_B7_DEFAULT                  0x01
#define IPSDISPLAY3_B8_DEFAULT                  0x08
#define IPSDISPLAY3_C6_DEFAULT                  0x30
#define IPSDISPLAY3_C7_DEFAULT                  0x1F

/**
 * @brief IPS Display 3 FRS command setting.
 * @details Specified setting for FRS command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_FRS_RTN1_DEFAULT            0x07
#define IPSDISPLAY3_FRS_RTN1_MASK               0x7F

/**
 * @brief IPS Display 3 CPRRGB565 command setting.
 * @details Specified setting for CPRRGB565 command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_CPRRGB565_EPF_DEFAULT       0xC0
#define IPSDISPLAY3_CPRRGB565_EPF_MASK          0xC0
#define IPSDISPLAY3_CPRRGB565_RESERVED          0x08

/**
 * @brief IPS Display 3 INVCTRL command setting.
 * @details Specified setting for INVCTRL command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_INVCTRL_DEFAULT             0x04
#define IPSDISPLAY3_INVCTRL_MASK                0x07

/**
 * @brief IPS Display 3 VREGCTL command setting.
 * @details Specified setting for VREGCTL command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_VREGCTL_AD_MIN_2921_MV      0x04
#define IPSDISPLAY3_VREGCTL_AD_DEFAULT_4637_MV  0x5A
#define IPSDISPLAY3_VREGCTL_AD_MAX_5192_MV      0x7F
#define IPSDISPLAY3_VREGCTL_AD_MASK             0x7F

/**
 * @brief IPS Display 3 VGHSET command setting.
 * @details Specified setting for VGHSET command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_VGHSET_D2A_10V              0x00
#define IPSDISPLAY3_VGHSET_D2A_11V              0x01
#define IPSDISPLAY3_VGHSET_D2A_12V              0x02
#define IPSDISPLAY3_VGHSET_D2A_13V              0x03
#define IPSDISPLAY3_VGHSET_D2A_14V              0x04
#define IPSDISPLAY3_VGHSET_D2A_15V              0x05
#define IPSDISPLAY3_VGHSET_D2A_MASK             0x07
#define IPSDISPLAY3_VGHSET_RESERVED             0x20

/**
 * @brief IPS Display 3 VGLSET command setting.
 * @details Specified setting for VGLSET command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_VGLSET_D2A_MIN_7_5V         0x00
#define IPSDISPLAY3_VGLSET_D2A_MIN_8_5V         0x01
#define IPSDISPLAY3_VGLSET_D2A_MIN_9_5V         0x02
#define IPSDISPLAY3_VGLSET_D2A_MIN_10V          0x03
#define IPSDISPLAY3_VGLSET_D2A_MIN_10_5V        0x04
#define IPSDISPLAY3_VGLSET_D2A_MIN_11V          0x05
#define IPSDISPLAY3_VGLSET_D2A_MIN_12V          0x06
#define IPSDISPLAY3_VGLSET_D2A_MIN_13V          0x07
#define IPSDISPLAY3_VGLSET_D2A_MASK             0x07
#define IPSDISPLAY3_VGLSET_RESERVED             0x40

/**
 * @brief IPS Display 3 VGHVGLCLK command setting.
 * @details Specified setting for VGHVGLCLK command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_2     0x00
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_3     0x10
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_4     0x20
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_5     0x30
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_6     0x40
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_7     0x50
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_8     0x60
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_9     0x70
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_10    0x80
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_12    0x90
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_15    0xA0
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_20    0xB0
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_24    0xC0
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_30    0xD0
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_40    0xE0
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_60    0xF0
#define IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_MASK  0xF0
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_2     0x00
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_3     0x01
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_4     0x02
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_5     0x03
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_6     0x04
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_7     0x05
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_8     0x06
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_9     0x07
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_10    0x08
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_12    0x09
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_15    0x0A
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_20    0x0B
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_24    0x0C
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_30    0x0D
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_40    0x0E
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_60    0x0F
#define IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_MASK  0x0F

/**
 * @brief IPS Display 3 SETGAMMA0 command setting.
 * @details Specified setting for SETGAMMA0 command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_SETGAMMA0_0_VR2N_DEFAULT    0x05
#define IPSDISPLAY3_SETGAMMA0_0_VR2N_MASK       0x3F
#define IPSDISPLAY3_SETGAMMA0_1_VR20N_DEFAULT   0x1D
#define IPSDISPLAY3_SETGAMMA0_1_VR20N_MASK      0x7F
#define IPSDISPLAY3_SETGAMMA0_2_VR36N_DEFAULT   0x10
#define IPSDISPLAY3_SETGAMMA0_2_VR36N_MASK      0x38
#define IPSDISPLAY3_SETGAMMA0_2_VR27N_DEFAULT   0x01
#define IPSDISPLAY3_SETGAMMA0_2_VR27N_MASK      0x07
#define IPSDISPLAY3_SETGAMMA0_2_RESERVED        0x40
#define IPSDISPLAY3_SETGAMMA0_3_VR43N_DEFAULT   0x2F
#define IPSDISPLAY3_SETGAMMA0_3_VR43N_MASK      0x7F
#define IPSDISPLAY3_SETGAMMA0_4_VR50N_DEFAULT   0x80
#define IPSDISPLAY3_SETGAMMA0_4_VR50N_MASK      0xF0
#define IPSDISPLAY3_SETGAMMA0_4_VR13N_DEFAULT   0x05
#define IPSDISPLAY3_SETGAMMA0_4_VR13N_MASK      0x0F
#define IPSDISPLAY3_SETGAMMA0_5_VR61N_DEFAULT   0x2A
#define IPSDISPLAY3_SETGAMMA0_5_VR61N_MASK      0x3F
#define IPSDISPLAY3_SETGAMMA0_6_VR62N_DEFAULT   0x11
#define IPSDISPLAY3_SETGAMMA0_6_VR62N_MASK      0x3F
#define IPSDISPLAY3_SETGAMMA0_7_J0N_DEFAULT     0x40
#define IPSDISPLAY3_SETGAMMA0_7_J0N_MASK        0xC0
#define IPSDISPLAY3_SETGAMMA0_7_J1N_DEFAULT     0x20
#define IPSDISPLAY3_SETGAMMA0_7_J1N_MASK        0x30
#define IPSDISPLAY3_SETGAMMA0_7_VR0N_DEFAULT    0x02
#define IPSDISPLAY3_SETGAMMA0_7_VR0N_MASK       0x0F
#define IPSDISPLAY3_SETGAMMA0_8_VR1N_DEFAULT    0x00
#define IPSDISPLAY3_SETGAMMA0_8_VR1N_MASK       0x3F
#define IPSDISPLAY3_SETGAMMA0_9_VR4N_DEFAULT    0x07
#define IPSDISPLAY3_SETGAMMA0_9_VR4N_MASK       0x1F
#define IPSDISPLAY3_SETGAMMA0_10_VR6N_DEFAULT   0x07
#define IPSDISPLAY3_SETGAMMA0_10_VR6N_MASK      0x1F
#define IPSDISPLAY3_SETGAMMA0_11_VR57N_DEFAULT  0x0F
#define IPSDISPLAY3_SETGAMMA0_11_VR57N_MASK     0x1F
#define IPSDISPLAY3_SETGAMMA0_12_VR59N_DEFAULT  0x08
#define IPSDISPLAY3_SETGAMMA0_12_VR59N_MASK     0x1F
#define IPSDISPLAY3_SETGAMMA0_13_VR63N_DEFAULT  0x1F
#define IPSDISPLAY3_SETGAMMA0_13_VR63N_MASK     0x1F

/**
 * @brief IPS Display 3 SETGAMMA1 command setting.
 * @details Specified setting for SETGAMMA1 command of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_SETGAMMA1_0_VR2P_DEFAULT    0x2E
#define IPSDISPLAY3_SETGAMMA1_0_VR2P_MASK       0x3F
#define IPSDISPLAY3_SETGAMMA1_1_VR20P_DEFAULT   0x41
#define IPSDISPLAY3_SETGAMMA1_1_VR20P_MASK      0x7F
#define IPSDISPLAY3_SETGAMMA1_2_VR36P_DEFAULT   0x20
#define IPSDISPLAY3_SETGAMMA1_2_VR36P_MASK      0x38
#define IPSDISPLAY3_SETGAMMA1_2_VR27P_DEFAULT   0x02
#define IPSDISPLAY3_SETGAMMA1_2_VR27P_MASK      0x07
#define IPSDISPLAY3_SETGAMMA1_2_RESERVED        0x40
#define IPSDISPLAY3_SETGAMMA1_3_VR43P_DEFAULT   0x56
#define IPSDISPLAY3_SETGAMMA1_3_VR43P_MASK      0x7F
#define IPSDISPLAY3_SETGAMMA1_4_VR50P_DEFAULT   0xA0
#define IPSDISPLAY3_SETGAMMA1_4_VR50P_MASK      0xF0
#define IPSDISPLAY3_SETGAMMA1_4_VR13P_DEFAULT   0x05
#define IPSDISPLAY3_SETGAMMA1_4_VR13P_MASK      0x0F
#define IPSDISPLAY3_SETGAMMA1_5_VR61P_DEFAULT   0x3A
#define IPSDISPLAY3_SETGAMMA1_5_VR61P_MASK      0x3F
#define IPSDISPLAY3_SETGAMMA1_6_VR62P_DEFAULT   0x3F
#define IPSDISPLAY3_SETGAMMA1_6_VR62P_MASK      0x3F
#define IPSDISPLAY3_SETGAMMA1_7_J0P_DEFAULT     0x40
#define IPSDISPLAY3_SETGAMMA1_7_J0P_MASK        0xC0
#define IPSDISPLAY3_SETGAMMA1_7_J1P_DEFAULT     0x20
#define IPSDISPLAY3_SETGAMMA1_7_J1P_MASK        0x30
#define IPSDISPLAY3_SETGAMMA1_7_VR0P_DEFAULT    0x00
#define IPSDISPLAY3_SETGAMMA1_7_VR0P_MASK       0x0F
#define IPSDISPLAY3_SETGAMMA1_8_VR1P_DEFAULT    0x0F
#define IPSDISPLAY3_SETGAMMA1_8_VR1P_MASK       0x3F
#define IPSDISPLAY3_SETGAMMA1_9_VR4P_DEFAULT    0x07
#define IPSDISPLAY3_SETGAMMA1_9_VR4P_MASK       0x1F
#define IPSDISPLAY3_SETGAMMA1_10_VR6P_DEFAULT   0x0A
#define IPSDISPLAY3_SETGAMMA1_10_VR6P_MASK      0x1F
#define IPSDISPLAY3_SETGAMMA1_11_VR57P_DEFAULT  0x18
#define IPSDISPLAY3_SETGAMMA1_11_VR57P_MASK     0x1F
#define IPSDISPLAY3_SETGAMMA1_12_VR59P_DEFAULT  0x18
#define IPSDISPLAY3_SETGAMMA1_12_VR59P_MASK     0x1F
#define IPSDISPLAY3_SETGAMMA1_13_VR63P_DEFAULT  0x1D
#define IPSDISPLAY3_SETGAMMA1_13_VR63P_MASK     0x1F

/**
 * @brief IPS Display 3 resolution setting.
 * @details Specified setting for display resolution of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_RES_WIDTH                   128
#define IPSDISPLAY3_RES_HEIGHT                  115
#define IPSDISPLAY3_NUM_PIXELS                  ( ( uint16_t ) IPSDISPLAY3_RES_WIDTH * IPSDISPLAY3_RES_HEIGHT )

/**
 * @brief IPS Display 3 position and coordinates setting.
 * @details Specified setting for display position and coordinates of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_POS_WIDTH_MIN               0
#define IPSDISPLAY3_POS_WIDTH_MAX               ( IPSDISPLAY3_RES_WIDTH - 1 )
#define IPSDISPLAY3_POS_HEIGHT_MIN              0
#define IPSDISPLAY3_POS_HEIGHT_MAX              ( IPSDISPLAY3_RES_HEIGHT - 1 )
#define IPSDISPLAY3_POS_OFFSET_LEFT             0
#define IPSDISPLAY3_POS_OFFSET_RIGHT            0
#define IPSDISPLAY3_POS_OFFSET_UP               13
#define IPSDISPLAY3_POS_OFFSET_DOWN             0

/**
 * @brief IPS Display 3 font setting.
 * @details Specified setting for font of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_FONT_TEXT_SPACE             1
#define IPSDISPLAY3_FONT_ASCII_OFFSET           32
#define IPSDISPLAY3_FONT_WIDTH_MSB              0x80

/**
 * @brief IPS Display 3 rotation setting.
 * @details Specified setting for rotation of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_ROTATION_VERTICAL_0         0
#define IPSDISPLAY3_ROTATION_VERTICAL_180       1
#define IPSDISPLAY3_ROTATION_HORIZONTAL_0       2
#define IPSDISPLAY3_ROTATION_HORIZONTAL_180     3

/**
 * @brief IPS Display 3 RGB565 colors definition.
 * @details Specified definition for RGB565 colors of IPS Display 3 Click driver.
 */
#define IPSDISPLAY3_COLOR_BLACK                 0x0000
#define IPSDISPLAY3_COLOR_WHITE                 0xFFFF
#define IPSDISPLAY3_COLOR_RED                   0xF800
#define IPSDISPLAY3_COLOR_LIME                  0x07E0
#define IPSDISPLAY3_COLOR_BLUE                  0x001F
#define IPSDISPLAY3_COLOR_YELLOW                0xFFE0
#define IPSDISPLAY3_COLOR_CYAN                  0x07FF
#define IPSDISPLAY3_COLOR_MAGENTA               0xF81F
#define IPSDISPLAY3_COLOR_SILVER                0xBDF7
#define IPSDISPLAY3_COLOR_GRAY                  0x8410
#define IPSDISPLAY3_COLOR_MAROON                0x8000
#define IPSDISPLAY3_COLOR_OLIVE                 0x8400
#define IPSDISPLAY3_COLOR_GREEN                 0x0400
#define IPSDISPLAY3_COLOR_PURPLE                0x8010
#define IPSDISPLAY3_COLOR_TEAL                  0x0410
#define IPSDISPLAY3_COLOR_NAVY                  0x0010

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ipsdisplay3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define IPSDISPLAY3_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define IPSDISPLAY3_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ipsdisplay3_set

/**
 * @defgroup ipsdisplay3_map IPS Display 3 MikroBUS Map
 * @brief MikroBUS pin mapping of IPS Display 3 Click driver.
 */

/**
 * @addtogroup ipsdisplay3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IPS Display 3 Click to the selected MikroBUS.
 */
#define IPSDISPLAY3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bck  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dc   = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ipsdisplay3_map
/*! @} */ // ipsdisplay3

/**
 * @brief IPS Display 3 Click font object.
 * @details Font object definition of IPS Display 3 Click driver.
 */
typedef struct
{
    const uint8_t *font_buf;        /**< Pointer to font array. */ 
    uint8_t width;                  /**< Font width. */ 
    uint8_t height;                 /**< Font height. */ 

} ipsdisplay3_font_t;

/**
 * @brief IPS Display 3 Click point coordinates object.
 * @details Point coordinates object definition of IPS Display 3 Click driver.
 */
typedef struct
{
    uint16_t x;                     /**< X coordinate. */
    uint16_t y;                     /**< Y coordinate. */

} ipsdisplay3_point_t;

/**
 * @brief IPS Display 3 Click context object.
 * @details Context object definition of IPS Display 3 Click driver.
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
    ipsdisplay3_font_t font;        /**< Font setting. */ 
    ipsdisplay3_point_t center;     /**< Center point. */

} ipsdisplay3_t;

/**
 * @brief IPS Display 3 Click configuration object.
 * @details Configuration object definition of IPS Display 3 Click driver.
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

} ipsdisplay3_cfg_t;

/**
 * @brief IPS Display 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IPSDISPLAY3_OK = 0,
    IPSDISPLAY3_ERROR = -1

} ipsdisplay3_return_value_t;

/*!
 * @addtogroup ipsdisplay3 IPS Display 3 Click Driver
 * @brief API for configuring and manipulating IPS Display 3 Click driver.
 * @{
 */

/**
 * @brief IPS Display 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ipsdisplay3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ipsdisplay3_cfg_setup ( ipsdisplay3_cfg_t *cfg );

/**
 * @brief IPS Display 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ipsdisplay3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_init ( ipsdisplay3_t *ctx, ipsdisplay3_cfg_t *cfg );

/**
 * @brief IPS Display 3 default configuration function.
 * @details This function executes a default configuration of IPS Display 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ipsdisplay3_default_cfg ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 write cmd function.
 * @details This function writes a command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_write_cmd ( ipsdisplay3_t *ctx, uint8_t cmd );

/**
 * @brief IPS Display 3 write cmd par function.
 * @details This function writes a desired number of data parameters to the selected command
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_write_cmd_par ( ipsdisplay3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief IPS Display 3 write data function.
 * @details This function writes a desired number of data words by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written (16-bit array).
 * @param[in] len : Number of words to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_write_data ( ipsdisplay3_t *ctx, uint16_t *data_in, uint16_t len );

/**
 * @brief IPS Display 3 disable device function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_disable_device ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 enable device function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_enable_device ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_reset_device ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 disable backlight function.
 * @details This function disables the backlight by setting the BCK pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_disable_backlight ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 enable backlight function.
 * @details This function enables the backlight by setting the BCK pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_enable_backlight ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 enter cmd mode function.
 * @details This function enters the command mode by setting the DC pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_enter_cmd_mode ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 enter data mode function.
 * @details This function enters the data mode by setting the DC pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipsdisplay3_enter_data_mode ( ipsdisplay3_t *ctx );

/**
 * @brief IPS Display 3 set rotation function.
 * @details This function sets the display rotation.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] rotation : @li @c 0 - Vertical 0 - Normal,
 *                       @li @c 1 - Vertical 180 - XY mirrored,
 *                       @li @c 2 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 3 - Horizontal 180 - XY exchanged, Y mirrored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_set_rotation ( ipsdisplay3_t *ctx, uint8_t rotation );

/**
 * @brief IPS Display 3 set font function.
 * @details This function sets the active font size.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] font_sel : @li @c 0 - 6x8 font,
 *                       @li @c 1 - 8x16 font,
 *                       @li @c 2 - 12x24 font.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void ipsdisplay3_set_font ( ipsdisplay3_t *ctx, uint8_t font_sel );

/**
 * @brief IPS Display 3 set pos function.
 * @details This function sets the coordinates of editable display area.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] end_pt : End point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay3_set_pos ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, ipsdisplay3_point_t end_pt );

/**
 * @brief IPS Display 3 fill screen function.
 * @details This function fills the screen with the selected color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_fill_screen ( ipsdisplay3_t *ctx, uint16_t color );

/**
 * @brief IPS Display 3 write char function.
 * @details This function writes a single ASCII character on the selected position in configured font size
 * with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] data_in : ASCII(32-126) char to write.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_write_char ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint8_t data_in, uint16_t color );

/**
 * @brief IPS Display 3 write string function.
 * @details This function writes a text string starting from the selected position in configured font size
 * with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] data_in : ASCII(32-126) string to write (must end with \0).
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipsdisplay3_write_string ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint8_t *data_in, uint16_t color );

/**
 * @brief IPS Display 3 draw pixel function.
 * @details This function draws a pixel on the selected position with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay3_draw_pixel ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint16_t color );

/**
 * @brief IPS Display 3 draw line function.
 * @details This function draws a line with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] end_pt : End point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay3_draw_line ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, 
                              ipsdisplay3_point_t end_pt, uint16_t color );

/**
 * @brief IPS Display 3 draw rectangle function.
 * @details This function draws a rectangle with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] start_pt : Start point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] end_pt : End point coordinates.
 * See #iipsdisplay3_point_t object definition for detailed explanation.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay3_draw_rectangle ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, 
                                   ipsdisplay3_point_t end_pt, uint16_t color );

/**
 * @brief IPS Display 3 draw circle function.
 * @details This function draws a circle with a specified color.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
 * @param[in] center_pt : Center point coordinates.
 * @param[in] radius : Circle radius.
 * @param[in] color : RGB565 color.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note X and Y are swapped in Horizontal display orientation.
 */
err_t ipsdisplay3_draw_circle ( ipsdisplay3_t *ctx, ipsdisplay3_point_t center_pt, uint8_t radius, uint16_t color );

/**
 * @brief IPS Display 3 draw picture function.
 * @details This function draws a picture with a specified color in a desired display orientation.
 * @param[in] ctx : Click context object.
 * See #ipsdisplay3_t object definition for detailed explanation.
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
err_t ipsdisplay3_draw_picture ( ipsdisplay3_t *ctx, uint8_t rotation, const uint16_t *image );

#ifdef __cplusplus
}
#endif
#endif // IPSDISPLAY3_H

/*! @} */ // ipsdisplay3

// ------------------------------------------------------------------------ END

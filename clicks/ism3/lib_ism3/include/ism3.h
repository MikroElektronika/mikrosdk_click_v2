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
 * @file ism3.h
 * @brief This file contains API for ISM 3 Click Driver.
 */

#ifndef ISM3_H
#define ISM3_H

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
 * @addtogroup ism3 ISM 3 Click Driver
 * @brief API for configuring and manipulating ISM 3 Click driver.
 * @{
 */

/**
 * @defgroup ism3_reg ISM 3 Registers List
 * @brief List of registers of ISM 3 Click driver.
 */

/**
 * @addtogroup ism3_reg
 * @{
 */

/**
 * @brief ISM 3 register list.
 * @details Specified register list of ISM 3 Click driver.
 */
#define ISM3_REG_GPIO0_CONF                             0x00
#define ISM3_REG_GPIO1_CONF                             0x01
#define ISM3_REG_GPIO2_CONF                             0x02
#define ISM3_REG_GPIO3_CONF                             0x03
#define ISM3_REG_SYNT3                                  0x05
#define ISM3_REG_SYNT2                                  0x06
#define ISM3_REG_SYNT1                                  0x07
#define ISM3_REG_SYNT0                                  0x08
#define ISM3_REG_IF_OFFSET_ANA                          0x09
#define ISM3_REG_IF_OFFSET_DIG                          0x0A
#define ISM3_REG_CHSPACE                                0x0C
#define ISM3_REG_CHNUM                                  0x0D
#define ISM3_REG_MOD4                                   0x0E
#define ISM3_REG_MOD3                                   0x0F
#define ISM3_REG_MOD2                                   0x10
#define ISM3_REG_MOD1                                   0x11
#define ISM3_REG_MOD0                                   0x12
#define ISM3_REG_CHFLT                                  0x13
#define ISM3_REG_AFC2                                   0x14
#define ISM3_REG_AFC1                                   0x15
#define ISM3_REG_AFC0                                   0x16
#define ISM3_REG_RSSI_FLT                               0x17
#define ISM3_REG_RSSI_TH                                0x18
#define ISM3_REG_AGCCTRL4                               0x1A
#define ISM3_REG_AGCCTRL3                               0x1B
#define ISM3_REG_AGCCTRL2                               0x1C
#define ISM3_REG_AGCCTRL1                               0x1D
#define ISM3_REG_AGCCTRL0                               0x1E
#define ISM3_REG_ANT_SELECT_CONF                        0x1F
#define ISM3_REG_CLOCKREC2                              0x20
#define ISM3_REG_CLOCKREC1                              0x21
#define ISM3_REG_PCKTCTRL6                              0x2B
#define ISM3_REG_PCKTCTRL5                              0x2C
#define ISM3_REG_PCKTCTRL4                              0x2D
#define ISM3_REG_PCKTCTRL3                              0x2E
#define ISM3_REG_PCKTCTRL2                              0x2F
#define ISM3_REG_PCKTCTRL1                              0x30
#define ISM3_REG_PCKTLEN1                               0x31
#define ISM3_REG_PCKTLEN0                               0x32
#define ISM3_REG_SYNC3                                  0x33
#define ISM3_REG_SYNC2                                  0x34
#define ISM3_REG_SYNC1                                  0x35
#define ISM3_REG_SYNC0                                  0x36
#define ISM3_REG_QI                                     0x37
#define ISM3_REG_PCKT_PSTMBL                            0x38
#define ISM3_REG_PROTOCOL2                              0x39
#define ISM3_REG_PROTOCOL1                              0x3A
#define ISM3_REG_PROTOCOL0                              0x3B
#define ISM3_REG_FIFO_CONFIG3                           0x3C
#define ISM3_REG_FIFO_CONFIG2                           0x3D
#define ISM3_REG_FIFO_CONFIG1                           0x3E
#define ISM3_REG_FIFO_CONFIG0                           0x3F
#define ISM3_REG_PCKT_FLT_OPTIONS                       0x40
#define ISM3_REG_PCKT_FLT_GOALS4                        0x41
#define ISM3_REG_PCKT_FLT_GOALS3                        0x42
#define ISM3_REG_PCKT_FLT_GOALS2                        0x43
#define ISM3_REG_PCKT_FLT_GOALS1                        0x44
#define ISM3_REG_PCKT_FLT_GOALS0                        0x45
#define ISM3_REG_TIMERS5                                0x46
#define ISM3_REG_TIMERS4                                0x47
#define ISM3_REG_TIMERS3                                0x48
#define ISM3_REG_TIMERS2                                0x49
#define ISM3_REG_TIMERS1                                0x4A
#define ISM3_REG_TIMERS0                                0x4B
#define ISM3_REG_CSMA_CONF3                             0x4C
#define ISM3_REG_CSMA_CONF2                             0x4D
#define ISM3_REG_CSMA_CONF1                             0x4E
#define ISM3_REG_CSMA_CONF0                             0x4F
#define ISM3_REG_IRQ_MASK3                              0x50
#define ISM3_REG_IRQ_MASK2                              0x51
#define ISM3_REG_IRQ_MASK1                              0x52
#define ISM3_REG_IRQ_MASK0                              0x53
#define ISM3_REG_FAST_RX_TIMER                          0x54
#define ISM3_REG_PA_POWER8                              0x5A
#define ISM3_REG_PA_POWER7                              0x5B
#define ISM3_REG_PA_POWER6                              0x5C
#define ISM3_REG_PA_POWER5                              0x5D
#define ISM3_REG_PA_POWER4                              0x5E
#define ISM3_REG_PA_POWER3                              0x5F
#define ISM3_REG_PA_POWER2                              0x60
#define ISM3_REG_PA_POWER1                              0x61
#define ISM3_REG_PA_POWER0                              0x62
#define ISM3_REG_PA_CONFIG1                             0x63
#define ISM3_REG_PA_CONFIG0                             0x64
#define ISM3_REG_SYNTH_CONFIG2                          0x65
#define ISM3_REG_VCO_CONFIG                             0x68
#define ISM3_REG_VCO_CALIBR_IN2                         0x69
#define ISM3_REG_VCO_CALIBR_IN1                         0x6A
#define ISM3_REG_VCO_CALIBR_IN0                         0x6B
#define ISM3_REG_XO_RCO_CONF1                           0x6C
#define ISM3_REG_XO_RCO_CONF0                           0x6D
#define ISM3_REG_RCO_CALIBR_CONF3                       0x6E
#define ISM3_REG_RCO_CALIBR_CONF2                       0x6F
#define ISM3_REG_PM_CONF4                               0x75
#define ISM3_REG_PM_CONF3                               0x76
#define ISM3_REG_PM_CONF2                               0x77
#define ISM3_REG_PM_CONF1                               0x78
#define ISM3_REG_PM_CONF0                               0x79
#define ISM3_REG_MC_STATE1                              0x8D
#define ISM3_REG_MC_STATE0                              0x8E
#define ISM3_REG_TX_FIFO_STATUS                         0x8F
#define ISM3_REG_RX_FIFO_STATUS                         0x90
#define ISM3_REG_RCO_CALIBR_OUT4                        0x94
#define ISM3_REG_RCO_CALIBR_OUT3                        0x95
#define ISM3_REG_VCO_CALIBR_OUT1                        0x99
#define ISM3_REG_VCO_CALIBR_OUT0                        0x9A
#define ISM3_REG_TX_PCKT_INFO                           0x9C
#define ISM3_REG_RX_PCKT_INFO                           0x9D
#define ISM3_REG_AFC_CORR                               0x9E
#define ISM3_REG_LINK_QUALIF2                           0x9F
#define ISM3_REG_LINK_QUALIF1                           0xA0
#define ISM3_REG_RSSI_LEVEL                             0xA2
#define ISM3_REG_RX_PCKT_LEN1                           0xA4
#define ISM3_REG_RX_PCKT_LEN0                           0xA5
#define ISM3_REG_CRC_FIELD3                             0xA6
#define ISM3_REG_CRC_FIELD2                             0xA7
#define ISM3_REG_CRC_FIELD1                             0xA8
#define ISM3_REG_CRC_FIELD0                             0xA9
#define ISM3_REG_RX_ADDRE_FIELD1                        0xAA
#define ISM3_REG_RX_ADDRE_FIELD0                        0xAB
#define ISM3_REG_RSSI_LEVEL_RUN                         0xEF
#define ISM3_REG_DEVICE_INFO1                           0xF0
#define ISM3_REG_DEVICE_INFO0                           0xF1
#define ISM3_REG_IRQ_STATUS3                            0xFA
#define ISM3_REG_IRQ_STATUS2                            0xFB
#define ISM3_REG_IRQ_STATUS1                            0xFC
#define ISM3_REG_IRQ_STATUS0                            0xFD
#define ISM3_REG_LINEAR_FIFO                            0xFF

/**
 * @brief ISM 3 commands list.
 * @details Specified commands list of ISM 3 Click driver.
 */
#define ISM3_CMD_TX                                     0x60
#define ISM3_CMD_RX                                     0x61
#define ISM3_CMD_READY                                  0x62
#define ISM3_CMD_STANDBY                                0x63
#define ISM3_CMD_SLEEP                                  0x64
#define ISM3_CMD_LOCKRX                                 0x65
#define ISM3_CMD_LOCKTX                                 0x66
#define ISM3_CMD_SABORT                                 0x67
#define ISM3_CMD_LDC_RELOAD                             0x68
#define ISM3_CMD_SRES                                   0x70
#define ISM3_CMD_FLUSHRXFIFO                            0x71
#define ISM3_CMD_FLUSHTXFIFO                            0x72
#define ISM3_CMD_SEQUENCE_UPDATE                        0x73

/*! @} */ // ism3_reg

/**
 * @defgroup ism3_set ISM 3 Registers Settings
 * @brief Settings for registers of ISM 3 Click driver.
 */

/**
 * @addtogroup ism3_set
 * @{
 */

/**
 * @brief ISM 3 GPIO1_CONF register setting.
 * @details Specified setting for GPIO1_CONF register of ISM 3 Click driver.
 */
#define ISM3_GPIO1_CONF_GPIO_SELECT_NIRQ                0x00
#define ISM3_GPIO1_CONF_GPIO_SELECT_POR_INVERTED        0x08
#define ISM3_GPIO1_CONF_GPIO_SELECT_WUT                 0x10
#define ISM3_GPIO1_CONF_GPIO_SELECT_LOW_BATTERY         0x18
#define ISM3_GPIO1_CONF_GPIO_SELECT_TX_INT_CLKOUT       0x20
#define ISM3_GPIO1_CONF_GPIO_SELECT_TX_STATE            0x28
#define ISM3_GPIO1_CONF_GPIO_SELECT_TXRX_FIFO_EMPTY     0x30
#define ISM3_GPIO1_CONF_GPIO_SELECT_TXRX_FIFO_FULL      0x38
#define ISM3_GPIO1_CONF_GPIO_SELECT_RX_DATA_OUT         0x40
#define ISM3_GPIO1_CONF_GPIO_SELECT_RX_CLKOUT           0x48
#define ISM3_GPIO1_CONF_GPIO_SELECT_RX_STATE            0x50
#define ISM3_GPIO1_CONF_GPIO_SELECT_NO_SLEEP_STANDBY    0x58
#define ISM3_GPIO1_CONF_GPIO_SELECT_STANDBY             0x60
#define ISM3_GPIO1_CONF_GPIO_SELECT_ANT_DIVERSITY       0x68
#define ISM3_GPIO1_CONF_GPIO_SELECT_PREAMBLE            0x70
#define ISM3_GPIO1_CONF_GPIO_SELECT_SYNC                0x78
#define ISM3_GPIO1_CONF_GPIO_SELECT_RSSI                0x80
#define ISM3_GPIO1_CONF_GPIO_SELECT_TX_RX_MODE          0x90
#define ISM3_GPIO1_CONF_GPIO_SELECT_VDD                 0x98
#define ISM3_GPIO1_CONF_GPIO_SELECT_GND                 0xA0
#define ISM3_GPIO1_CONF_GPIO_SELECT_EXT_SMPS            0xA8
#define ISM3_GPIO1_CONF_GPIO_SELECT_SLEEP               0xB0
#define ISM3_GPIO1_CONF_GPIO_SELECT_READY               0xB8
#define ISM3_GPIO1_CONF_GPIO_SELECT_LOCK                0xC0
#define ISM3_GPIO1_CONF_GPIO_SELECT_LOCK_DETECTOR       0xC8
#define ISM3_GPIO1_CONF_GPIO_SELECT_TX_DATA_OOK         0xD0
#define ISM3_GPIO1_CONF_GPIO_SELECT_READY2              0xD8
#define ISM3_GPIO1_CONF_GPIO_SELECT_TIMER_EXP           0xE0
#define ISM3_GPIO1_CONF_GPIO_SELECT_VCO_CALIB           0xE8
#define ISM3_GPIO1_CONF_GPIO_SELECT_SYNTH               0xF0
#define ISM3_GPIO1_CONF_GPIO_SELECT_MASK                0xF8
#define ISM3_GPIO1_CONF_GPIO_MODE_ANALOG                0x00
#define ISM3_GPIO1_CONF_GPIO_MODE_DIG_INPUT             0x01
#define ISM3_GPIO1_CONF_GPIO_MODE_DIG_OUTPUT_LP         0x02
#define ISM3_GPIO1_CONF_GPIO_MODE_DIG_OUTPUT_HP         0x03
#define ISM3_GPIO1_CONF_GPIO_MODE_MASK                  0x03

/**
 * @brief ISM 3 SYNTx registers setting.
 * @details Specified setting for SYNTx registers of ISM 3 Click driver.
 */
#define ISM3_SYNT3_PLL_CP_ISEL_MASK                     0xE0
#define ISM3_SYNT3_PLL_CP_ISEL_DEFAULT                  0x40
#define ISM3_SYNT3_BS_MASK                              0x10
#define ISM3_SYNT3_BS_4_HIGH_BAND                       0x00
#define ISM3_SYNT3_BS_8_MIDDLE_BAND                     0x10
#define ISM3_SYNT3_SYNT_27_24_MASK                      0x0F
#define ISM3_SYNT3_SYNT_27_24_DEFAULT                   0x04
#define ISM3_SYNT2_SYNT_23_16_DEFAULT                   0x54
#define ISM3_SYNT1_SYNT_15_8_DEFAULT                    0x7A
#define ISM3_SYNT0_SYNT_7_0_DEFAULT                     0xE1

/**
 * @brief ISM 3 IF_OFFSET_ANA and IF_OFFSET_DIG registers setting.
 * @details Specified setting for IF_OFFSET_ANA and IF_OFFSET_DIG registers of ISM 3 Click driver.
 */
#define ISM3_IF_OFFSET_ANA_DEFAULT                      0xC2
#define ISM3_IF_OFFSET_DIG_DEFAULT                      0xC2

/**
 * @brief ISM 3 MODx and CHFLT registers setting.
 * @details Specified setting for MODx and CHFLT registers of ISM 3 Click driver.
 */
#define ISM3_MOD4_DATARATE_M_15_8_DEFAULT               0x92
#define ISM3_MOD3_DATARATE_M_7_0_DEFAULT                0xA7
#define ISM3_MOD2_MOD_TYPE_2FSK                         0x00
#define ISM3_MOD2_MOD_TYPE_4FSK                         0x10
#define ISM3_MOD2_MOD_TYPE_2GFSK_BT_1                   0x20
#define ISM3_MOD2_MOD_TYPE_4GFSK_BT_1                   0x30
#define ISM3_MOD2_MOD_TYPE_ASK_OOK                      0x50
#define ISM3_MOD2_MOD_TYPE_UNMODULATED                  0x70
#define ISM3_MOD2_MOD_TYPE_2GFSK_BT_0_5                 0xA0
#define ISM3_MOD2_MOD_TYPE_4GFSK_BT_0_5                 0xB0
#define ISM3_MOD2_MOD_TYPE_MASK                         0xF0
#define ISM3_MOD2_DATARATE_E_DEFAULT                    0x07
#define ISM3_MOD2_DATARATE_E_MASK                       0x0F
#define ISM3_MOD1_PA_INTERP_EN                          0x80
#define ISM3_MOD1_MOD_INTERP_EN                         0x40
#define ISM3_MOD1_CONST_MAP_MASK                        0x30
#define ISM3_MOD1_FDEV_E_DEFAULT                        0x04
#define ISM3_MOD1_FDEV_E_MASK                           0x0F
#define ISM3_MOD0_FDEV_M_DEFAULT                        0xA3
#define ISM3_CHFLT_M_DEFAULT                            0x10
#define ISM3_CHFLT_M_MASK                               0xF0
#define ISM3_CHFLT_E_DEFAULT                            0x03
#define ISM3_CHFLT_E_MASK                               0x0F

/**
 * @brief ISM 3 AFC2 register setting.
 * @details Specified setting for AFC2 register of ISM 3 Click driver.
 */
#define ISM3_AFC2_AFC_FREEZE_ON_SYNC                    0x80
#define ISM3_AFC2_AFC_ENABLED                           0x40
#define ISM3_AFC2_AFC_MODE                              0x20

/**
 * @brief ISM 3 PCKTCTRLx registers setting.
 * @details Specified setting for PCKTCTRLx registers of ISM 3 Click driver.
 */
#define ISM3_PCKTCTRL6_SYNC_LEN_MASK                    0xFC
#define ISM3_PCKTCTRL6_SYNC_LEN_DEFAULT                 0x80
#define ISM3_PCKTCTRL6_PREAMBLE_LEN_MASK                0x03
#define ISM3_PCKTCTRL6_PREAMBLE_LEN_DEFAULT             0x00
#define ISM3_PCKTCTRL5_PREAMBLE_LEN_MASK                0xFF
#define ISM3_PCKTCTRL5_PREAMBLE_LEN_DEFAULT             0x10
#define ISM3_PCKTCTRL4_LEN_WID_1BYTE                    0x00
#define ISM3_PCKTCTRL4_LEN_WID_2BYTE                    0x80
#define ISM3_PCKTCTRL4_LEN_WID_MASK                     0x80
#define ISM3_PCKTCTRL4_ADDRESS_LEN_NOT_INCLUDED         0x00
#define ISM3_PCKTCTRL4_ADDRESS_LEN_INCLUDED             0x08
#define ISM3_PCKTCTRL4_ADDRESS_LEN_MASK                 0x08
#define ISM3_PCKTCTRL3_PCKT_FRMT_BASIC                  0x00
#define ISM3_PCKTCTRL3_PCKT_FRMT_802_15_4G              0x40
#define ISM3_PCKTCTRL3_PCKT_FRMT_UART_OTA               0x80
#define ISM3_PCKTCTRL3_PCKT_FRMT_STACK                  0xC0
#define ISM3_PCKTCTRL3_PCKT_FRMT_MASK                   0xC0
#define ISM3_PCKTCTRL3_RX_MODE_NORMAL                   0x00
#define ISM3_PCKTCTRL3_RX_MODE_DIRECT_FIFO              0x10
#define ISM3_PCKTCTRL3_RX_MODE_DIRECT_GPIO              0x20
#define ISM3_PCKTCTRL3_RX_MODE_MASK                     0x30
#define ISM3_PCKTCTRL3_FSK4_SYM_SWAP                    0x08
#define ISM3_PCKTCTRL3_BYTE_SWAP                        0x04
#define ISM3_PCKTCTRL3_PREAMBLE_SEL_MASK                0x03
#define ISM3_PCKTCTRL2_FSC_TYPE_4G                      0x20
#define ISM3_PCKTCTRL2_FEC_TYPE_4G                      0x10
#define ISM3_PCKTCTRL2_INT_EN_4G                        0x08
#define ISM3_PCKTCTRL2_MBUS_3OF6_EN                     0x04
#define ISM3_PCKTCTRL2_MANCHESTER_EN                    0x02
#define ISM3_PCKTCTRL2_FIX_VAR_LEN                      0x01
#define ISM3_PCKTCTRL1_CRC_MODE_NO_CRC                  0x00
#define ISM3_PCKTCTRL1_CRC_MODE_POLY_07                 0x20
#define ISM3_PCKTCTRL1_CRC_MODE_POLY_8005               0x40
#define ISM3_PCKTCTRL1_CRC_MODE_POLY_1021               0x60
#define ISM3_PCKTCTRL1_CRC_MODE_POLY_864CBF             0x80
#define ISM3_PCKTCTRL1_CRC_MODE_POLY                    0xA0
#define ISM3_PCKTCTRL1_CRC_MODE_MASK                    0xE0
#define ISM3_PCKTCTRL1_WHIT_EN                          0x10
#define ISM3_PCKTCTRL1_TXSOURCE_NORMAL                  0x00
#define ISM3_PCKTCTRL1_TXSOURCE_DIRECT_FIFO             0x04
#define ISM3_PCKTCTRL1_TXSOURCE_DIRECT_GPIO             0x08
#define ISM3_PCKTCTRL1_TXSOURCE_PN9                     0x0C
#define ISM3_PCKTCTRL1_TXSOURCE_MASK                    0x0C
#define ISM3_PCKTCTRL1_SECOND_SYNC_SEL                  0x02
#define ISM3_PCKTCTRL1_FEC_EN                           0x01

/**
 * @brief ISM 3 PROTOCOL1 register setting.
 * @details Specified setting for PROTOCOL1 register of ISM 3 Click driver.
 */
#define ISM3_PROTOCOL1_LDC_MODE                         0x80
#define ISM3_PROTOCOL1_LDC_RELOAD_ON_SYNC               0x40
#define ISM3_PROTOCOL1_PIGGYBACKING                     0x20
#define ISM3_PROTOCOL1_FAST_CS_TERM_EN                  0x10
#define ISM3_PROTOCOL1_SEED_RELOAD                      0x08
#define ISM3_PROTOCOL1_CSMA_ON                          0x04
#define ISM3_PROTOCOL1_CSMA_PERS_ON                     0x02
#define ISM3_PROTOCOL1_AUTO_PCKT_FLT                    0x01

/**
 * @brief ISM 3 PCKT_FLT_OPTIONS register setting.
 * @details Specified setting for PCKT_FLT_OPTIONS register of ISM 3 Click driver.
 */
#define ISM3_PCKT_FLT_OPTIONS_RX_TIMEOUT_AND_OR_SEL     0x40
#define ISM3_PCKT_FLT_OPTIONS_SOURCE_ADDR_FLT           0x10
#define ISM3_PCKT_FLT_OPTIONS_DEST_VS_BROADCAST_ADDR    0x08
#define ISM3_PCKT_FLT_OPTIONS_DEST_VS_MULTICAST_ADDR    0x04
#define ISM3_PCKT_FLT_OPTIONS_DEST_VS_SOURCE_ADDR       0x02
#define ISM3_PCKT_FLT_OPTIONS_CRC_FLT                   0x01

/**
 * @brief ISM 3 PA_POWER8 register setting.
 * @details Specified setting for PA_POWER8 register of ISM 3 Click driver.
 */
#define ISM3_PA_POWER8_PA_LEVEL8_MASK                   0x7F
#define ISM3_PA_POWER8_PA_LEVEL8_DEFAULT                0x01

/**
 * @brief ISM 3 PA_POWER0 register setting.
 * @details Specified setting for PA_POWER0 register of ISM 3 Click driver.
 */
#define ISM3_PA_POWER0_DIG_SMOOTH_EN                    0x80
#define ISM3_PA_POWER0_PA_MAXDBM                        0x40
#define ISM3_PA_POWER0_PA_RAMP_EN                       0x20
#define ISM3_PA_POWER0_PA_RAMP_STEP_LEN_MASK            0x18
#define ISM3_PA_POWER0_PA_LEVEL_MAX_IDX_DEFAULT         0x07
#define ISM3_PA_POWER0_PA_LEVEL_MAX_IDX_MASK            0x07

/**
 * @brief ISM 3 PA_CONFIG1 register setting.
 * @details Specified setting for PA_CONFIG1 register of ISM 3 Click driver.
 */
#define ISM3_PA_CONFIG1_FIR_CFG_FILTERING               0x00
#define ISM3_PA_CONFIG1_FIR_CFG_RAMPING                 0x04
#define ISM3_PA_CONFIG1_FIR_CFG_SWITCHING               0x08
#define ISM3_PA_CONFIG1_FIR_CFG_MASK                    0x0C
#define ISM3_PA_CONFIG1_FIR_EN                          0x02

/**
 * @brief ISM 3 PA_CONFIG0 register setting.
 * @details Specified setting for PA_CONFIG0 register of ISM 3 Click driver.
 */
#define ISM3_PA_CONFIG0_PA_DEGEN_TRIM_MASK              0xF0
#define ISM3_PA_CONFIG0_PA_DEGEN_ON                     0x08
#define ISM3_PA_CONFIG0_SAFE_ASK_CAL                    0x04
#define ISM3_PA_CONFIG0_PA_FC_12_5_KHZ                  0x00
#define ISM3_PA_CONFIG0_PA_FC_25_KHZ                    0x01
#define ISM3_PA_CONFIG0_PA_FC_50_KHZ                    0x02
#define ISM3_PA_CONFIG0_PA_FC_100_KHZ                   0x03
#define ISM3_PA_CONFIG0_PA_FC_MASK                      0x03

/**
 * @brief ISM 3 SYNTH_CONFIG2 register setting.
 * @details Specified setting for SYNTH_CONFIG2 register of ISM 3 Click driver.
 */
#define ISM3_SYNTH_CONFIG2_PLL_PFD_SPLIT_EN             0x04

/**
 * @brief ISM 3 XO_RCO_CONF1 register setting.
 * @details Specified setting for XO_RCO_CONF1 register of ISM 3 Click driver.
 */
#define ISM3_XO_RCO_CONF1_PD_CLKDIV                     0x10

/**
 * @brief ISM 3 PM_CONF3 register setting.
 * @details Specified setting for PM_CONF3 register of ISM 3 Click driver.
 */
#define ISM3_PM_CONF3_RX                                0x90
#define ISM3_PM_CONF3_TX                                0x9C

/**
 * @brief ISM 3 operating state setting.
 * @details Specified setting for operating state of ISM 3 Click driver.
 */
#define ISM3_MC_STATE_READY                             0x00
#define ISM3_MC_STATE_SLEEP_NOFIFO                      0x01
#define ISM3_MC_STATE_STANDBY                           0x02
#define ISM3_MC_STATE_SLEEP                             0x03
#define ISM3_MC_STATE_LOCKON                            0x0C
#define ISM3_MC_STATE_RX                                0x30
#define ISM3_MC_STATE_LOCKST                            0x14
#define ISM3_MC_STATE_TX                                0x5C
#define ISM3_MC_STATE_SYNTH_SETUP                       0x50
#define ISM3_MC_STATE_WAIT_SLEEP                        0x7C
#define ISM3_MC_STATE_MASK                              0x7F

/**
 * @brief ISM 3 irq mask setting.
 * @details Specified setting for irq mask of ISM 3 Click driver.
 */
#define ISM3_IRQ_NONE                                   0x00000000ul
#define ISM3_IRQ_RX_DATA_READY                          0x00000001ul
#define ISM3_IRQ_RX_DATA_DISC                           0x00000002ul
#define ISM3_IRQ_TX_DATA_SENT                           0x00000004ul
#define ISM3_IRQ_MAX_RE_TX_REACH                        0x00000008ul
#define ISM3_IRQ_CRC_ERROR                              0x00000010ul
#define ISM3_IRQ_TX_FIFO_ERROR                          0x00000020ul
#define ISM3_IRQ_RX_FIFO_ERROR                          0x00000040ul
#define ISM3_IRQ_TX_FIFO_ALMOST_FULL                    0x00000080ul
#define ISM3_IRQ_TX_FIFO_ALMOST_EMPTY                   0x00000100ul
#define ISM3_IRQ_RX_FIFO_ALMOST_FULL                    0x00000200ul
#define ISM3_IRQ_RX_FIFO_ALMOST_EMPTY                   0x00000400ul
#define ISM3_IRQ_MAX_BO_CCA_REACH                       0x00000800ul
#define ISM3_IRQ_VALID_PREAMBLE                         0x00001000ul
#define ISM3_IRQ_VALID_SYNC                             0x00002000ul
#define ISM3_IRQ_RSSI_ABOVE_TH                          0x00004000ul
#define ISM3_IRQ_WKUP_TOUT_LDC                          0x00008000ul
#define ISM3_IRQ_READY                                  0x00010000ul
#define ISM3_IRQ_STANDBY_DELAYED                        0x00020000ul
#define ISM3_IRQ_LOW_BATT_LVL                           0x00040000ul
#define ISM3_IRQ_POR                                    0x00080000ul
#define ISM3_IRQ_BOR                                    0x00100000ul
#define ISM3_IRQ_LOCK                                   0x00200000ul
#define ISM3_IRQ_VCO_CALIBRATION_END                    0x00400000ul
#define ISM3_IRQ_PA_CALIBRATION_END                     0x00800000ul
#define ISM3_IRQ_RX_TIMEOUT                             0x01000000ul
#define ISM3_IRQ_RX_SNIFF_TIMEOUT                       0x02000000ul

/**
 * @brief ISM 3 default packet len setting.
 * @details Specified setting for default packet len of ISM 3 Click driver.
 */
#define ISM3_PACKET_LEN                                 64

/**
 * @brief ISM 3 rx timer counter and prescaler setting.
 * @details Specified setting for rx timer counter and prescaler of ISM 3 Click driver.
 */
#define ISM3_RX_TIMER_CNT_2000MS                        251
#define ISM3_RX_TIMER_PSC_2000MS                        164
#define ISM3_RX_TIMER_CNT_1000MS                        25
#define ISM3_RX_TIMER_PSC_1000MS                        10
#define ISM3_RX_TIMER_CNT_100MS                         248
#define ISM3_RX_TIMER_PSC_100MS                         83

/**
 * @brief ISM 3 timeout setting.
 * @details Specified setting for timeout of ISM 3 Click driver.
 */
#define ISM3_DEFAULT_TIMEOUT_MS                         1000
#define ISM3_DEFAULT_RX_TIMEOUT_MS                      3000

/**
 * @brief ISM 3 part number setting.
 * @details Specified setting for part number of ISM 3 Click driver.
 */
#define ISM3_PART_NUMBER                                0x03

/**
 * @brief ISM 3 header byte setting.
 * @details Specified setting for header byte of ISM 3 Click driver.
 */
#define ISM3_HEADER_WRITE_REG                           0x00
#define ISM3_HEADER_READ_REG                            0x01
#define ISM3_HEADER_WRITE_CMD                           0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ism3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ISM3_SET_DATA_SAMPLE_EDGE                       SET_SPI_DATA_SAMPLE_EDGE
#define ISM3_SET_DATA_SAMPLE_MIDDLE                     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ism3_set

/**
 * @defgroup ism3_map ISM 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ISM 3 Click driver.
 */

/**
 * @addtogroup ism3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM 3 Click to the selected MikroBUS.
 */
#define ISM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gp0  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp2  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ism3_map
/*! @} */ // ism3

/**
 * @brief ISM 3 Click context object.
 * @details Context object definition of ISM 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */
    digital_out_t cs;           /**< Chip select pin (Active low). */

    // Input pins
    digital_in_t gp0;           /**< GPIO 0 pin. */
    digital_in_t gp1;           /**< GPIO 1 pin. */
    digital_in_t gp2;           /**< GPIO 2 pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    uint16_t status;            /**< Status word of the last read/write sequence. */

} ism3_t;

/**
 * @brief ISM 3 Click configuration object.
 * @details Configuration object definition of ISM 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t gp0;             /**< GPIO 0 pin. */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t gp2;             /**< GPIO 2 pin. */
    pin_name_t gp1;             /**< GPIO 1 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} ism3_cfg_t;

/**
 * @brief ISM 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISM3_OK = 0,
    ISM3_ERROR = -1,
    ISM3_TIMEOUT = -2

} ism3_return_value_t;

/*!
 * @addtogroup ism3 ISM 3 Click Driver
 * @brief API for configuring and manipulating ISM 3 Click driver.
 * @{
 */

/**
 * @brief ISM 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ism3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ism3_cfg_setup ( ism3_cfg_t *cfg );

/**
 * @brief ISM 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ism3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_init ( ism3_t *ctx, ism3_cfg_t *cfg );

/**
 * @brief ISM 3 default configuration function.
 * @details This function executes a default configuration of ISM 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ism3_default_cfg ( ism3_t *ctx );

/**
 * @brief ISM 3 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_write_regs ( ism3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 3 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_read_regs ( ism3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ISM 3 write reg function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_write_reg ( ism3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ISM 3 read reg function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_read_reg ( ism3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ISM 3 write cmd function.
 * @details This function writes a command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_write_cmd ( ism3_t *ctx, uint8_t cmd );

/**
 * @brief ISM 3 enable device function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ism3_enable_device ( ism3_t *ctx );

/**
 * @brief ISM 3 disable device function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ism3_disable_device ( ism3_t *ctx );

/**
 * @brief ISM 3 get gp0 pin function.
 * @details This function returns the GP0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ism3_get_gp0_pin ( ism3_t *ctx );

/**
 * @brief ISM 3 get gp1 pin function.
 * @details This function returns the GP1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ism3_get_gp1_pin ( ism3_t *ctx );

/**
 * @brief ISM 3 get gp2 pin function.
 * @details This function returns the GP2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ism3_get_gp2_pin ( ism3_t *ctx );

/**
 * @brief ISM 3 check communication function.
 * @details This function checks the communication by reading and verifying the device part number.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_check_communication ( ism3_t *ctx );

/**
 * @brief ISM 3 wait mc state function.
 * @details This function waits for the device to enter the selected MC state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] mc_state : Device MC state to wait for.
 * @param[in] timeout_ms : Maximal time to wait in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_wait_mc_state ( ism3_t *ctx, uint8_t mc_state, uint16_t timeout_ms );

/**
 * @brief ISM 3 go to ready function.
 * @details This function switches the device to ready state.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_go_to_ready ( ism3_t *ctx );

/**
 * @brief ISM 3 go to rx function.
 * @details This function switches the device to RX state (initial).
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_go_to_rx ( ism3_t *ctx );

/**
 * @brief ISM 3 set irq mask function.
 * @details This function sets the IRQ mask.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] irq_mask : IRQ mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_set_irq_mask ( ism3_t *ctx, uint32_t irq_mask );

/**
 * @brief ISM 3 read irq mask function.
 * @details This function reads the IRQ mask.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[out] irq_mask : IRQ mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_read_irq_mask ( ism3_t *ctx, uint32_t *irq_mask );

/**
 * @brief ISM 3 clear irq status function.
 * @details This function clears the IRQ status.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_clear_irq_status ( ism3_t *ctx );

/**
 * @brief ISM 3 read irq status function.
 * @details This function reads the IRQ status.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[out] irq_status : IRQ status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_read_irq_status ( ism3_t *ctx, uint32_t *irq_status );

/**
 * @brief ISM 3 transmit packet function.
 * @details This function transmits a desired data packet.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be transmitted.
 * @param[in] len : Number of data bytes to transmit (up to 64 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_transmit_packet ( ism3_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 3 receive packet function.
 * @details This function waits for a data packet to arrive and reads it.
 * @param[in] ctx : Click context object.
 * See #ism3_t object definition for detailed explanation.
 * @param[out] data_out : Received data (Required) (up to 64 bytes).
 * @param[out] len : Number of data bytes that were available in RX FIFO (Optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism3_receive_packet ( ism3_t *ctx, uint8_t *data_out, uint8_t *len );

#ifdef __cplusplus
}
#endif
#endif // ISM3_H

/*! @} */ // ism3

// ------------------------------------------------------------------------ END

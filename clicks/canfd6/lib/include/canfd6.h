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
 * @file canfd6.h
 * @brief This file contains API for CAN FD 6 Click Driver.
 */

#ifndef CANFD6_H
#define CANFD6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup canfd6 CAN FD 6 Click Driver
 * @brief API for configuring and manipulating CAN FD 6 Click driver.
 * @{
 */

/**
 * @brief CAN FD 6 MCAN cache configuration.
 * @details Define MCAN cache configuration to reduce the number of
 * SPI reads necessary to send or receive a packet by caching certain values.
 */
#define CANFD6_MCAN_CACHE_CONFIGURATION

#ifdef CANFD6_MCAN_CACHE_CONFIGURATION
#define CANFD6_MCAN_CACHE_SIDFC                                 0
#define CANFD6_MCAN_CACHE_XIDFC                                 1
#define CANFD6_MCAN_CACHE_RXF0C                                 2
#define CANFD6_MCAN_CACHE_RXF1C                                 3
#define CANFD6_MCAN_CACHE_RXBC                                  4
#define CANFD6_MCAN_CACHE_TXEFC                                 5
#define CANFD6_MCAN_CACHE_TXBC                                  6
#define CANFD6_MCAN_CACHE_RXESC                                 7
#define CANFD6_MCAN_CACHE_TXESC                                 8
#endif

/**
 * @brief CAN FD 6 MRAM size.
 * @details Specified MRAM size.
 */
#define CANFD6_MRAM_SIZE                                        2048

/**
 * @defgroup canfd6_reg1 CAN FD 6 Register address sections.
 * @brief List of register address sections of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg1
 * @{
 */

#define CANFD6_REG_SPI_CONFIG                                   0x0000
#define CANFD6_REG_DEV_CONFIG                                   0x0800
#define CANFD6_REG_MCAN                                         0x1000
#define CANFD6_REG_MRAM                                         0x8000

/*! @} */ // canfd6_reg1

/**
 * @defgroup canfd6_reg2 CAN FD 6 SPI and device ID register addresses.
 * @brief List of SPI registers and device ID register addresses of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg2
 * @{
 */

#define CANFD6_REG_SPI_DEVICE_ID0                               0x0000
#define CANFD6_REG_SPI_DEVICE_ID1                               0x0004
#define CANFD6_REG_SPI_REVISION                                 0x0008
#define CANFD6_REG_SPI_STATUS                                   0x000C
#define CANFD6_REG_SPI_ERROR_STATUS_MASK                        0x0010

/*! @} */ // canfd6_reg2

/**
 * @defgroup canfd6_reg3 CAN FD 6 device configuration register addresses.
 * @brief List of device configuration register addresses of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg3
 * @{
 */

#define CANFD6_REG_DEV_MODES_AND_PINS                           0x0800
#define CANFD6_REG_DEV_TIMESTAMP_PRESCALER                      0x0804
#define CANFD6_REG_DEV_TEST_REGISTERS                           0x0808
#define CANFD6_REG_DEV_IR                                       0x0820
#define CANFD6_REG_DEV_IE                                       0x0830

/*! @} */ // canfd6_reg3

/**
 * @defgroup canfd6_reg4 CAN FD 6 MCAN register addresses.
 * @brief List of MCAN register addresses of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg4
 * @{
 */

#define CANFD6_REG_MCAN_CREL                                    0x1000
#define CANFD6_REG_MCAN_ENDN                                    0x1004
#define CANFD6_REG_MCAN_CUST                                    0x1008
#define CANFD6_REG_MCAN_DBTP                                    0x100C
#define CANFD6_REG_MCAN_TEST                                    0x1010
#define CANFD6_REG_MCAN_RWD                                     0x1014
#define CANFD6_REG_MCAN_CCCR                                    0x1018
#define CANFD6_REG_MCAN_NBTP                                    0x101C
#define CANFD6_REG_MCAN_TSCC                                    0x1020
#define CANFD6_REG_MCAN_TSCV                                    0x1024
#define CANFD6_REG_MCAN_TOCC                                    0x1028
#define CANFD6_REG_MCAN_TOCV                                    0x102C
#define CANFD6_REG_MCAN_ECR                                     0x1040
#define CANFD6_REG_MCAN_PSR                                     0x1044
#define CANFD6_REG_MCAN_TDCR                                    0x1048
#define CANFD6_REG_MCAN_IR                                      0x1050
#define CANFD6_REG_MCAN_IE                                      0x1054
#define CANFD6_REG_MCAN_ILS                                     0x1058
#define CANFD6_REG_MCAN_ILE                                     0x105C
#define CANFD6_REG_MCAN_GFC                                     0x1080
#define CANFD6_REG_MCAN_SIDFC                                   0x1084
#define CANFD6_REG_MCAN_XIDFC                                   0x1088
#define CANFD6_REG_MCAN_XIDAM                                   0x1090
#define CANFD6_REG_MCAN_HPMS                                    0x1094
#define CANFD6_REG_MCAN_NDAT1                                   0x1098
#define CANFD6_REG_MCAN_NDAT2                                   0x109C
#define CANFD6_REG_MCAN_RXF0C                                   0x10A0
#define CANFD6_REG_MCAN_RXF0S                                   0x10A4
#define CANFD6_REG_MCAN_RXF0A                                   0x10A8
#define CANFD6_REG_MCAN_RXBC                                    0x10AC
#define CANFD6_REG_MCAN_RXF1C                                   0x10B0
#define CANFD6_REG_MCAN_RXF1S                                   0x10B4
#define CANFD6_REG_MCAN_RXF1A                                   0x10B8
#define CANFD6_REG_MCAN_RXESC                                   0x10BC
#define CANFD6_REG_MCAN_TXBC                                    0x10C0
#define CANFD6_REG_MCAN_TXFQS                                   0x10C4
#define CANFD6_REG_MCAN_TXESC                                   0x10C8
#define CANFD6_REG_MCAN_TXBRP                                   0x10CC
#define CANFD6_REG_MCAN_TXBAR                                   0x10D0
#define CANFD6_REG_MCAN_TXBCR                                   0x10D4
#define CANFD6_REG_MCAN_TXBTO                                   0x10D8
#define CANFD6_REG_MCAN_TXBCF                                   0x10DC
#define CANFD6_REG_MCAN_TXBTIE                                  0x10E0
#define CANFD6_REG_MCAN_TXBCIE                                  0x10E4
#define CANFD6_REG_MCAN_TXEFC                                   0x10F0
#define CANFD6_REG_MCAN_TXEFS                                   0x10F4
#define CANFD6_REG_MCAN_TXEFA                                   0x10F8

/*! @} */ // canfd6_reg4

/**
 * @defgroup canfd6_reg5 CAN FD 6 DLC value defines.
 * @brief List of DLC value defines of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg5
 * @{
 */

#define CANFD6_MCAN_DLC_0B                                      0x00000000
#define CANFD6_MCAN_DLC_1B                                      0x00000001
#define CANFD6_MCAN_DLC_2B                                      0x00000002
#define CANFD6_MCAN_DLC_3B                                      0x00000003
#define CANFD6_MCAN_DLC_4B                                      0x00000004
#define CANFD6_MCAN_DLC_5B                                      0x00000005
#define CANFD6_MCAN_DLC_6B                                      0x00000006
#define CANFD6_MCAN_DLC_7B                                      0x00000007
#define CANFD6_MCAN_DLC_8B                                      0x00000008
#define CANFD6_MCAN_DLC_12B                                     0x00000009
#define CANFD6_MCAN_DLC_16B                                     0x0000000A
#define CANFD6_MCAN_DLC_20B                                     0x0000000B
#define CANFD6_MCAN_DLC_24B                                     0x0000000C
#define CANFD6_MCAN_DLC_32B                                     0x0000000D
#define CANFD6_MCAN_DLC_48B                                     0x0000000E
#define CANFD6_MCAN_DLC_64B                                     0x0000000F

/*! @} */ // canfd6_reg5

/**
 * @brief CAN FD 6 DBTP.
 * @details Data timing fd bit.
 */
#define CANFD6_REG_BITS_MCAN_DBTP_TDC_EN                        0x00800000

/**
 * @defgroup canfd6_reg6 CAN FD 6 test.
 * @brief List of test cmd of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg6
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TEST_RX_DOM                        0x00000000
#define CANFD6_REG_BITS_MCAN_TEST_RX_REC                        0x00000080
#define CANFD6_REG_BITS_MCAN_TEST_TX_SP                         0x00000020
#define CANFD6_REG_BITS_MCAN_TEST_TX_DOM                        0x00000040
#define CANFD6_REG_BITS_MCAN_TEST_TX_REC                        0x00000060
#define CANFD6_REG_BITS_MCAN_TEST_LOOP_BACK                     0x00000010

/*! @} */ // canfd6_reg6

/**
 * @defgroup canfd6_reg7 CAN FD 6 CCCR bit masks.
 * @brief List of CCCR bit masks of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg7
 * @{
 */

#define CANFD6_REG_BITS_MCAN_CCCR_RESERVED_MASK                 0xFFFF0C00
#define CANFD6_REG_BITS_MCAN_CCCR_NISO_ISO                      0x00000000
#define CANFD6_REG_BITS_MCAN_CCCR_NISO_BOSCH                    0x00008000
#define CANFD6_REG_BITS_MCAN_CCCR_TXP                           0x00004000
#define CANFD6_REG_BITS_MCAN_CCCR_EFBI                          0x00002000
#define CANFD6_REG_BITS_MCAN_CCCR_PXHD_DIS                      0x00001000
#define CANFD6_REG_BITS_MCAN_CCCR_BRSE                          0x00000200
#define CANFD6_REG_BITS_MCAN_CCCR_FDOE                          0x00000100
#define CANFD6_REG_BITS_MCAN_CCCR_TEST                          0x00000080
#define CANFD6_REG_BITS_MCAN_CCCR_DAR_DIS                       0x00000040
#define CANFD6_REG_BITS_MCAN_CCCR_MON                           0x00000020
#define CANFD6_REG_BITS_MCAN_CCCR_CSR                           0x00000010
#define CANFD6_REG_BITS_MCAN_CCCR_CSA                           0x00000008
#define CANFD6_REG_BITS_MCAN_CCCR_ASM                           0x00000004
#define CANFD6_REG_BITS_MCAN_CCCR_CCE                           0x00000002
#define CANFD6_REG_BITS_MCAN_CCCR_INIT                          0x00000001

/*! @} */ // canfd6_reg7

/**
 * @defgroup canfd6_reg8 CAN FD 6 IE bits.
 * @brief List of IE bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg8
 * @{
 */

#define CANFD6_REG_BITS_MCAN_IE_ARAE                            0x20000000
#define CANFD6_REG_BITS_MCAN_IE_PEDE                            0x10000000
#define CANFD6_REG_BITS_MCAN_IE_PEAE                            0x08000000
#define CANFD6_REG_BITS_MCAN_IE_WDIE                            0x04000000
#define CANFD6_REG_BITS_MCAN_IE_BOE                             0x02000000
#define CANFD6_REG_BITS_MCAN_IE_EWE                             0x01000000
#define CANFD6_REG_BITS_MCAN_IE_EPE                             0x00800000
#define CANFD6_REG_BITS_MCAN_IE_ELOE                            0x00400000
#define CANFD6_REG_BITS_MCAN_IE_BEUE                            0x00200000
#define CANFD6_REG_BITS_MCAN_IE_BECE                            0x00100000
#define CANFD6_REG_BITS_MCAN_IE_DRXE                            0x00080000
#define CANFD6_REG_BITS_MCAN_IE_TOOE                            0x00040000
#define CANFD6_REG_BITS_MCAN_IE_MRAFE                           0x00020000
#define CANFD6_REG_BITS_MCAN_IE_TSWE                            0x00010000
#define CANFD6_REG_BITS_MCAN_IE_TEFLE                           0x00008000
#define CANFD6_REG_BITS_MCAN_IE_TEFFE                           0x00004000
#define CANFD6_REG_BITS_MCAN_IE_TEFWE                           0x00002000
#define CANFD6_REG_BITS_MCAN_IE_TEFNE                           0x00001000
#define CANFD6_REG_BITS_MCAN_IE_TFEE                            0x00000800
#define CANFD6_REG_BITS_MCAN_IE_TCFE                            0x00000400
#define CANFD6_REG_BITS_MCAN_IE_TCE                             0x00000200
#define CANFD6_REG_BITS_MCAN_IE_HPME                            0x00000100
#define CANFD6_REG_BITS_MCAN_IE_RF1LE                           0x00000080
#define CANFD6_REG_BITS_MCAN_IE_RF1FE                           0x00000040
#define CANFD6_REG_BITS_MCAN_IE_RF1WE                           0x00000020
#define CANFD6_REG_BITS_MCAN_IE_RF1NE                           0x00000010
#define CANFD6_REG_BITS_MCAN_IE_RF0LE                           0x00000008
#define CANFD6_REG_BITS_MCAN_IE_RF0FE                           0x00000004
#define CANFD6_REG_BITS_MCAN_IE_RF0WE                           0x00000002
#define CANFD6_REG_BITS_MCAN_IE_RF0NE                           0x00000001

/*! @} */ // canfd6_reg8

/**
 * @defgroup canfd6_reg9 CAN FD 6 IR bits.
 * @brief List of IR bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg9
 * @{
 */

#define CANFD6_REG_BITS_MCAN_IR_ARA                             0x20000000
#define CANFD6_REG_BITS_MCAN_IR_PED                             0x10000000
#define CANFD6_REG_BITS_MCAN_IR_PEA                             0x08000000
#define CANFD6_REG_BITS_MCAN_IR_WDI                             0x04000000
#define CANFD6_REG_BITS_MCAN_IR_BO                              0x02000000
#define CANFD6_REG_BITS_MCAN_IR_EW                              0x01000000
#define CANFD6_REG_BITS_MCAN_IR_EP                              0x00800000
#define CANFD6_REG_BITS_MCAN_IR_ELO                             0x00400000
#define CANFD6_REG_BITS_MCAN_IR_BEU                             0x00200000
#define CANFD6_REG_BITS_MCAN_IR_BEC                             0x00100000
#define CANFD6_REG_BITS_MCAN_IR_DRX                             0x00080000
#define CANFD6_REG_BITS_MCAN_IR_TOO                             0x00040000
#define CANFD6_REG_BITS_MCAN_IR_MRAF                            0x00020000
#define CANFD6_REG_BITS_MCAN_IR_TSW                             0x00010000
#define CANFD6_REG_BITS_MCAN_IR_TEFL                            0x00008000
#define CANFD6_REG_BITS_MCAN_IR_TEFF                            0x00004000
#define CANFD6_REG_BITS_MCAN_IR_TEFW                            0x00002000
#define CANFD6_REG_BITS_MCAN_IR_TEFN                            0x00001000
#define CANFD6_REG_BITS_MCAN_IR_TFE                             0x00000800
#define CANFD6_REG_BITS_MCAN_IR_TCF                             0x00000400
#define CANFD6_REG_BITS_MCAN_IR_TC                              0x00000200
#define CANFD6_REG_BITS_MCAN_IR_HPM                             0x00000100
#define CANFD6_REG_BITS_MCAN_IR_RF1L                            0x00000080
#define CANFD6_REG_BITS_MCAN_IR_RF1F                            0x00000040
#define CANFD6_REG_BITS_MCAN_IR_RF1W                            0x00000020
#define CANFD6_REG_BITS_MCAN_IR_RF1N                            0x00000010
#define CANFD6_REG_BITS_MCAN_IR_RF0L                            0x00000008
#define CANFD6_REG_BITS_MCAN_IR_RF0F                            0x00000004
#define CANFD6_REG_BITS_MCAN_IR_RF0W                            0x00000002
#define CANFD6_REG_BITS_MCAN_IR_RF0N                            0x00000001

/*! @} */ // canfd6_reg9

/**
 * @defgroup canfd6_reg10 CAN FD 6 ILS bits.
 * @brief List of ILS bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg10
 * @{
 */

#define CANFD6_REG_BITS_MCAN_IE_ARAL                            0x20000000
#define CANFD6_REG_BITS_MCAN_IE_PEDL                            0x10000000
#define CANFD6_REG_BITS_MCAN_IE_PEAL                            0x08000000
#define CANFD6_REG_BITS_MCAN_IE_WDIL                            0x04000000
#define CANFD6_REG_BITS_MCAN_IE_BOL                             0x02000000
#define CANFD6_REG_BITS_MCAN_IE_EWL                             0x01000000
#define CANFD6_REG_BITS_MCAN_IE_EPL                             0x00800000
#define CANFD6_REG_BITS_MCAN_IE_ELOL                            0x00400000
#define CANFD6_REG_BITS_MCAN_IE_BEUL                            0x00200000
#define CANFD6_REG_BITS_MCAN_IE_BECL                            0x00100000
#define CANFD6_REG_BITS_MCAN_IE_DRXL                            0x00080000
#define CANFD6_REG_BITS_MCAN_IE_TOOL                            0x00040000
#define CANFD6_REG_BITS_MCAN_IE_MRAFL                           0x00020000
#define CANFD6_REG_BITS_MCAN_IE_TSWL                            0x00010000
#define CANFD6_REG_BITS_MCAN_IE_TEFLL                           0x00008000
#define CANFD6_REG_BITS_MCAN_IE_TEFFL                           0x00004000
#define CANFD6_REG_BITS_MCAN_IE_TEFWL                           0x00002000
#define CANFD6_REG_BITS_MCAN_IE_TEFNL                           0x00001000
#define CANFD6_REG_BITS_MCAN_IE_TFEL                            0x00000800
#define CANFD6_REG_BITS_MCAN_IE_TCFL                            0x00000400
#define CANFD6_REG_BITS_MCAN_IE_TCL                             0x00000200
#define CANFD6_REG_BITS_MCAN_IE_HPML                            0x00000100
#define CANFD6_REG_BITS_MCAN_IE_RF1LL                           0x00000080
#define CANFD6_REG_BITS_MCAN_IE_RF1FL                           0x00000040
#define CANFD6_REG_BITS_MCAN_IE_RF1WL                           0x00000020
#define CANFD6_REG_BITS_MCAN_IE_RF1NL                           0x00000010
#define CANFD6_REG_BITS_MCAN_IE_RF0LL                           0x00000008
#define CANFD6_REG_BITS_MCAN_IE_RF0FL                           0x00000004
#define CANFD6_REG_BITS_MCAN_IE_RF0WL                           0x00000002
#define CANFD6_REG_BITS_MCAN_IE_RF0NL                           0x00000001

/*! @} */ // canfd6_reg10

/**
 * @defgroup canfd6_reg11 CAN FD 6 ILE ( interrupt enable ).
 * @brief List of ILE ( interrupt enable ) of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg11
 * @{
 */

#define CANFD6_REG_BITS_MCAN_ILE_EINT1                          0x00000002
#define CANFD6_REG_BITS_MCAN_ILE_EINT0                          0x00000001

/*! @} */ // canfd6_reg11

/**
 * @defgroup canfd6_reg12 CAN FD 6 GFC bits.
 * @brief List of GFC bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg12
 * @{
 */

#define CANFD6_REG_BITS_MCAN_GFC_ANFS_FIFO0                     0x00000000
#define CANFD6_REG_BITS_MCAN_GFC_ANFS_FIFO1                     0x00000010
#define CANFD6_REG_BITS_MCAN_GFC_ANFE_FIFO0                     0x00000000
#define CANFD6_REG_BITS_MCAN_GFC_ANFE_FIFO1                     0x00000004
#define CANFD6_REG_BITS_MCAN_GFC_RRFS                           0x00000002
#define CANFD6_REG_BITS_MCAN_GFC_RRFE                           0x00000001
#define CANFD6_REG_BITS_MCAN_GFC_MASK                           0x0000003F

/*! @} */ // canfd6_reg12

/**
 * @brief CAN FD 6 MCAN RXF0C overwrite bit.
 * @details Specified MCAN RXF0C overwrite bit.
 */
#define CANFD6_REG_BITS_MCAN_RXF0C_F0OM_OVERWRITE               0x80000000

/**
 * @defgroup canfd6_reg13 CAN FD 6 RXESC bits.
 * @brief List of RXESC bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg13
 * @{
 */

#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_8B                      0x00000000
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_12B                     0x00000100
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_16B                     0x00000200
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_20B                     0x00000300
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_24B                     0x00000400
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_32B                     0x00000500
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_48B                     0x00000600
#define CANFD6_REG_BITS_MCAN_RXESC_RBDS_64B                     0x00000700
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_8B                      0x00000000
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_12B                     0x00000010
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_16B                     0x00000020
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_20B                     0x00000030
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_24B                     0x00000040
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_32B                     0x00000050
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_48B                     0x00000060
#define CANFD6_REG_BITS_MCAN_RXESC_F1DS_64B                     0x00000070
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_8B                      0x00000000
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_12B                     0x00000001
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_16B                     0x00000002
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_20B                     0x00000003
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_24B                     0x00000004
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_32B                     0x00000005
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_48B                     0x00000006
#define CANFD6_REG_BITS_MCAN_RXESC_F0DS_64B                     0x00000007

/*! @} */ // canfd6_reg13

/**
 * @brief CAN FD 6 TXBC bit.
 * @details Specified TXBC bit.
 */
#define CANFD6_REG_BITS_MCAN_TXBC_TFQM                          0x40000000

/**
 * @defgroup canfd6_reg14 CAN FD 6 TXESC bits.
 * @brief List of TXESC bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg14
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_8                       0x00000000
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_12                      0x00000001
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_16                      0x00000002
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_20                      0x00000003
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_24                      0x00000004
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_32                      0x00000005
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_48                      0x00000006
#define CANFD6_REG_BITS_MCAN_TXESC_TBDS_64                      0x00000007

/*! @} */ // canfd6_reg14

/**
 * @defgroup canfd6_reg15 CAN FD 6 TSCC bits.
 * @brief List of TSCC bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg15
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TSCC_PRESCALER_MASK                0x000F0000
#define CANFD6_REG_BITS_MCAN_TSCC_COUNTER_ALWAYS_0              0x00000000
#define CANFD6_REG_BITS_MCAN_TSCC_COUNTER_USE_TCP               0x00000001
#define CANFD6_REG_BITS_MCAN_TSCC_COUNTER_EXTERNAL              0x00000002

/*! @} */ // canfd6_reg15

/**
 * @defgroup canfd6_reg16 CAN FD 6 TXBAR bits.
 * @brief List of TXBAR bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg16
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TXBAR_AR31                         0x80000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR30                         0x40000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR29                         0x20000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR28                         0x10000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR27                         0x08000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR26                         0x04000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR25                         0x02000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR24                         0x01000000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR23                         0x00800000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR22                         0x00400000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR21                         0x00200000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR20                         0x00100000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR19                         0x00080000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR18                         0x00040000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR17                         0x00020000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR16                         0x00010000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR15                         0x00008000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR14                         0x00004000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR13                         0x00002000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR12                         0x00001000
#define CANFD6_REG_BITS_MCAN_TXBAR_AR11                         0x00000800
#define CANFD6_REG_BITS_MCAN_TXBAR_AR10                         0x00000400
#define CANFD6_REG_BITS_MCAN_TXBAR_AR9                          0x00000200
#define CANFD6_REG_BITS_MCAN_TXBAR_AR8                          0x00000100
#define CANFD6_REG_BITS_MCAN_TXBAR_AR7                          0x00000080
#define CANFD6_REG_BITS_MCAN_TXBAR_AR6                          0x00000040
#define CANFD6_REG_BITS_MCAN_TXBAR_AR5                          0x00000020
#define CANFD6_REG_BITS_MCAN_TXBAR_AR4                          0x00000010
#define CANFD6_REG_BITS_MCAN_TXBAR_AR3                          0x00000008
#define CANFD6_REG_BITS_MCAN_TXBAR_AR2                          0x00000004
#define CANFD6_REG_BITS_MCAN_TXBAR_AR1                          0x00000002
#define CANFD6_REG_BITS_MCAN_TXBAR_AR0                          0x00000001

/*! @} */ // canfd6_reg16

/**
 * @defgroup canfd6_reg17 CAN FD 6 TXBCR bits.
 * @brief List of TXBCR bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg17
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TXBCR_CR31                         0x80000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR30                         0x40000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR29                         0x20000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR28                         0x10000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR27                         0x08000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR26                         0x04000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR25                         0x02000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR24                         0x01000000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR23                         0x00800000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR22                         0x00400000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR21                         0x00200000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR20                         0x00100000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR19                         0x00080000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR18                         0x00040000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR17                         0x00020000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR16                         0x00010000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR15                         0x00008000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR14                         0x00004000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR13                         0x00002000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR12                         0x00001000
#define CANFD6_REG_BITS_MCAN_TXBCR_CR11                         0x00000800
#define CANFD6_REG_BITS_MCAN_TXBCR_CR10                         0x00000400
#define CANFD6_REG_BITS_MCAN_TXBCR_CR9                          0x00000200
#define CANFD6_REG_BITS_MCAN_TXBCR_CR8                          0x00000100
#define CANFD6_REG_BITS_MCAN_TXBCR_CR7                          0x00000080
#define CANFD6_REG_BITS_MCAN_TXBCR_CR6                          0x00000040
#define CANFD6_REG_BITS_MCAN_TXBCR_CR5                          0x00000020
#define CANFD6_REG_BITS_MCAN_TXBCR_CR4                          0x00000010
#define CANFD6_REG_BITS_MCAN_TXBCR_CR3                          0x00000008
#define CANFD6_REG_BITS_MCAN_TXBCR_CR2                          0x00000004
#define CANFD6_REG_BITS_MCAN_TXBCR_CR1                          0x00000002
#define CANFD6_REG_BITS_MCAN_TXBCR_CR0                          0x00000001

/*! @} */ // canfd6_reg17

/**
 * @defgroup canfd6_reg18 CAN FD 6 TXBTIE bits.
 * @brief List of TXBTIE bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg18
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE31                       0x80000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE30                       0x40000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE29                       0x20000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE28                       0x10000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE27                       0x08000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE26                       0x04000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE25                       0x02000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE24                       0x01000000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE23                       0x00800000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE22                       0x00400000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE21                       0x00200000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE20                       0x00100000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE19                       0x00080000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE18                       0x00040000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE17                       0x00020000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE16                       0x00010000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE15                       0x00008000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE14                       0x00004000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE13                       0x00002000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE12                       0x00001000
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE11                       0x00000800
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE10                       0x00000400
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE9                        0x00000200
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE8                        0x00000100
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE7                        0x00000080
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE6                        0x00000040
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE5                        0x00000020
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE4                        0x00000010
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE3                        0x00000008
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE2                        0x00000004
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE1                        0x00000002
#define CANFD6_REG_BITS_MCAN_TXBTIE_TIE0                        0x00000001

/*! @} */ // canfd6_reg18

/**
 * @defgroup canfd6_reg19 CAN FD 6 TXBCIE bits.
 * @brief List of TXBCIE bits of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg19
 * @{
 */

#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE31                      0x80000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE30                      0x40000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE29                      0x20000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE28                      0x10000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE27                      0x08000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE26                      0x04000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE25                      0x02000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE24                      0x01000000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE23                      0x00800000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE22                      0x00400000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE21                      0x00200000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE20                      0x00100000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE19                      0x00080000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE18                      0x00040000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE17                      0x00020000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE16                      0x00010000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE15                      0x00008000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE14                      0x00004000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE13                      0x00002000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE12                      0x00001000
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE11                      0x00000800
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE10                      0x00000400
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE9                       0x00000200
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE8                       0x00000100
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE7                       0x00000080
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE6                       0x00000040
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE5                       0x00000020
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE4                       0x00000010
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE3                       0x00000008
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE2                       0x00000004
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE1                       0x00000002
#define CANFD6_REG_BITS_MCAN_TXBCIE_CFIE0                       0x00000001

/*! @} */ // canfd6_reg19

/**
 * @defgroup canfd6_reg20 CAN FD 6 device register bit field defines.
 * @brief List of device register bit field defines of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg20
 * @{
 */

#define CANFD6_REG_BITS_DEVICE_MODE_FORCED_SET_BITS             0x00000020

#define CANFD6_REG_BITS_DEVICE_MODE_WAKE_PIN_MASK               0xC0000000
#define CANFD6_REG_BITS_DEVICE_MODE_WAKE_PIN_DIS                0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_WAKE_PIN_RISING             0x40000000
#define CANFD6_REG_BITS_DEVICE_MODE_WAKE_PIN_FALLING            0x80000000
#define CANFD6_REG_BITS_DEVICE_MODE_WAKE_PIN_BOTHEDGES          0xC0000000

#define CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_MASK               0x30000000
#define CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_60MS               0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_600MS              0x10000000
#define CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_3S                 0x20000000
#define CANFD6_REG_BITS_DEVICE_MODE_WD_TIMER_6S                 0x30000000

#define CANFD6_REG_BITS_DEVICE_MODE_WD_CLK_MASK                 0x08000000
#define CANFD6_REG_BITS_DEVICE_MODE_WD_CLK_20MHZ                0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_WD_CLK_40MHZ                0x08000000

#define CANFD6_REG_BITS_DEVICE_MODE_GPO2_MASK                   0x00C00000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO2_CAN_FAULT              0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO2_MCAN_INT0              0x00400000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO2_WDT                    0x00800000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO2_NINT                   0x00C00000

#define CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_ENMASK             0x00200000
#define CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_EN                 0x00200000
#define CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_DIS                0x00000000

#define CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_VOLT_MASK             0x00080000
#define CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_VOLT_INTERNAL         0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_VOLT_VIO              0x00080000

#define CANFD6_REG_BITS_DEVICE_MODE_WDT_RESET_BIT               0x00040000

#define CANFD6_REG_BITS_DEVICE_MODE_WDT_ACTION_MASK             0x00020000
#define CANFD6_REG_BITS_DEVICE_MODE_WDT_ACTION_INT              0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_WDT_ACTION_INH_PULSE        0x00010000
#define CANFD6_REG_BITS_DEVICE_MODE_WDT_ACTION_WDT_PULSE        0x00020000

#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_MODE_MASK              0x0000C000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_MODE_GPO               0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_MODE_CLKOUT            0x00004000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_MODE_GPI               0x00008000

#define CANFD6_REG_BITS_DEVICE_MODE_FAIL_SAFE_MASK              0x00002000
#define CANFD6_REG_BITS_DEVICE_MODE_FAIL_SAFE_EN                0x00002000
#define CANFD6_REG_BITS_DEVICE_MODE_FAIL_SAFE_DIS               0x00000000

#define CANFD6_REG_BITS_DEVICE_MODE_CLKOUT_MASK                 0x00001000
#define CANFD6_REG_BITS_DEVICE_MODE_CLKOUT_DIV1                 0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_CLKOUT_DIV2                 0x00001000

#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_FUNC_MASK              0x00000C00
#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_FUNC_SPI_INT           0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_FUNC_MCAN_INT1         0x00000400
#define CANFD6_REG_BITS_DEVICE_MODE_GPO1_FUNC_UVLO_THERM        0x00000800

#define CANFD6_REG_BITS_DEVICE_MODE_INH_MASK                    0x00000200
#define CANFD6_REG_BITS_DEVICE_MODE_INH_DIS                     0x00000200
#define CANFD6_REG_BITS_DEVICE_MODE_INH_EN                      0x00000000

#define CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_CONFIG_MASK           0x00000100
#define CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_CONFIG_INH            0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_NWKRQ_CONFIG_WKRQ           0x00000100

#define CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_MASK             0x000000C0
#define CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_SLEEP            0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_STANDBY          0x00000040
#define CANFD6_REG_BITS_DEVICE_MODE_DEVICEMODE_NORMAL           0x00000080

#define CANFD6_REG_BITS_DEVICE_MODE_WDT_MASK                    0x00000008
#define CANFD6_REG_BITS_DEVICE_MODE_WDT_EN                      0x00000008
#define CANFD6_REG_BITS_DEVICE_MODE_WDT_DIS                     0x00000000

#define CANFD6_REG_BITS_DEVICE_MODE_DEVICE_RESET                0x00000004

#define CANFD6_REG_BITS_DEVICE_MODE_SWE_MASK                    0x00000002
#define CANFD6_REG_BITS_DEVICE_MODE_SWE_DIS                     0x00000002
#define CANFD6_REG_BITS_DEVICE_MODE_SWE_EN                      0x00000000

#define CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_MASK               0x00000001
#define CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_PHY                0x00000000
#define CANFD6_REG_BITS_DEVICE_MODE_TESTMODE_CONTROLLER         0x00000001

/*! @} */ // canfd6_reg20

/**
 * @defgroup canfd6_reg21 CAN FD 6 device interrupt register values.
 * @brief List of device interrupt register values of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg21
 * @{
 */

#define CANFD6_REG_BITS_DEVICE_IR_CANLGND                       0x08000000
#define CANFD6_REG_BITS_DEVICE_IR_CANBUSOPEN                    0x04000000
#define CANFD6_REG_BITS_DEVICE_IR_CANBUSGND                     0x02000000
#define CANFD6_REG_BITS_DEVICE_IR_CANBUSBAT                     0x01000000
#define CANFD6_REG_BITS_DEVICE_IR_UVSUP                         0x00400000
#define CANFD6_REG_BITS_DEVICE_IR_UVIO                          0x00200000
#define CANFD6_REG_BITS_DEVICE_IR_PWRON                         0x00100000
#define CANFD6_REG_BITS_DEVICE_IR_TSD                           0x00080000
#define CANFD6_REG_BITS_DEVICE_IR_WDTO                          0x00040000
#define CANFD6_REG_BITS_DEVICE_IR_ECCERR                        0x00010000
#define CANFD6_REG_BITS_DEVICE_IR_CANINT                        0x00008000
#define CANFD6_REG_BITS_DEVICE_IR_LWU                           0x00004000
#define CANFD6_REG_BITS_DEVICE_IR_WKERR                         0x00002000
#define CANFD6_REG_BITS_DEVICE_IR_FRAME_OVF                     0x00001000
#define CANFD6_REG_BITS_DEVICE_IR_CANSLNT                       0x00000400
#define CANFD6_REG_BITS_DEVICE_IR_CANDOM                        0x00000100
#define CANFD6_REG_BITS_DEVICE_IR_GLOBALERR                     0x00000080
#define CANFD6_REG_BITS_DEVICE_IR_nWKRQ                         0x00000040
#define CANFD6_REG_BITS_DEVICE_IR_CANERR                        0x00000020
#define CANFD6_REG_BITS_DEVICE_IR_CANBUSFAULT                   0x00000010
#define CANFD6_REG_BITS_DEVICE_IR_SPIERR                        0x00000008
#define CANFD6_REG_BITS_DEVICE_IR_SWERR                         0x00000004
#define CANFD6_REG_BITS_DEVICE_IR_M_CAN_INT                     0x00000002
#define CANFD6_REG_BITS_DEVICE_IR_VTWD                          0x00000001

/*! @} */ // canfd6_reg21

/**
 * @defgroup canfd6_reg22 CAN FD 6 device interrupt enable values.
 * @brief List of device interrupt enable values of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_reg22
 * @{
 */

#define CANFD6_REG_BITS_DEVICE_IE_UVCCOUT                       0x00800000
#define CANFD6_REG_BITS_DEVICE_IE_UVSUP                         0x00400000
#define CANFD6_REG_BITS_DEVICE_IE_UVIO                          0x00200000
#define CANFD6_REG_BITS_DEVICE_IE_PWRON                         0x00100000
#define CANFD6_REG_BITS_DEVICE_IE_TSD                           0x00080000
#define CANFD6_REG_BITS_DEVICE_IE_WDTO                          0x00040000
#define CANFD6_REG_BITS_DEVICE_IE_ECCERR                        0x00010000
#define CANFD6_REG_BITS_DEVICE_IE_CANINT                        0x00008000
#define CANFD6_REG_BITS_DEVICE_IE_LWU                           0x00004000
#define CANFD6_REG_BITS_DEVICE_IE_WKERR                         0x00002000
#define CANFD6_REG_BITS_DEVICE_IE_FRAME_OVF                     0x00001000
#define CANFD6_REG_BITS_DEVICE_IE_CANSLNT                       0x00000400
#define CANFD6_REG_BITS_DEVICE_IE_CANDOM                        0x00000100
#define CANFD6_REG_BITS_DEVICE_IE_MASK                          0x7F69D700

/*! @} */ // canfd6_reg22

/**
 * @defgroup canfd6_map CAN FD 6 MikroBUS Map
 * @brief MikroBUS pin mapping of CAN FD 6 Click driver.
 */

/**
 * @addtogroup canfd6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CAN FD 6 Click to the selected MikroBUS.
 */
#define CANFD6_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.wkr  = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.wkp  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // canfd6_map
/*! @} */ // canfd6

/**
 * @brief CAN FD 6 Click context object.
 * @details Context object definition of CAN FD 6 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  wkr;                                  /**< Digital output wkr pin. */
    digital_out_t  rst;                                  /**< Digital output rst pin. */
    digital_out_t  wkp;                                  /**< Digital output wkp pin. */

    // Input pins

    digital_in_t  int_pin;                               /**< Digital input int pin. */

    // Modules

    spi_master_t  spi;                                   /**< SPI driver object. */

    pin_name_t  chip_select;                             /**< Chip select pin descriptor (used for SPI driver). */

} canfd6_t;

/**
 * @brief CAN FD 6 Click configuration object.
 * @details Configuration object definition of CAN FD 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  wkr;                                     /**< Wake request pin. */
    pin_name_t  rst;                                     /**< Device reset pin. */
    pin_name_t  wkp;                                     /**< Device wake pin. */
    pin_name_t  int_pin;                                 /**< Interrupt pin. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} canfd6_cfg_t;

/**
 * @brief CAN FD 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CANFD6_OK = 0,
    CANFD6_ERROR = -1

} canfd6_return_value_t;

/**
 * @brief CAN FD 6 Click pin states.
 * @details Predefined logic level states for pin gpio status.
 */
typedef enum
{
    CANFD6_PIN_STATE_LOW = 0,
    CANFD6_PIN_STATE_HIGH
    
} canfd6_pin_state_t;

/**
 * @brief CAN FD 6 Click RX FIFO enum.
 * @details Predefined RX FIFO enum values.
 */
typedef enum
{
    CANFD6_RXFIFO0,
    CANFD6_RXFIFO1
    
} canfd6_mcan_fifo_enum_t;

/**
 * @brief CAN FD 6 Click WDT timer enum.
 * @details Predefined watchdog timer enum values.
 */
typedef enum
{
    CANFD6_WDT_60MS,
    CANFD6_WDT_600MS,
    CANFD6_WDT_3S,
    CANFD6_WDT_6S
    
} canfd6_wdt_timer_enum_t;

/**
 * @brief CAN FD 6 Click device test enum.
 * @details Predefined device test enum values.
 */
typedef enum
{
    CANFD6_DEVICE_TEST_MODE_NORMAL,
    CANFD6_DEVICE_TEST_MODE_PHY,
    CANFD6_DEVICE_TEST_MODE_CONTROLLER
    
} canfd6_device_test_mode_enum_t;

/**
 * @brief CAN FD 6 Click device mode enum.
 * @details Predefined device mode enum values.
 */
typedef enum
{
    CANFD6_DEVICE_MODE_NORMAL,
    CANFD6_DEVICE_MODE_STANDBY,
    CANFD6_DEVICE_MODE_SLEEP
    
} canfd6_device_mode_enum_t;

/**
 * @brief CAN FD 6 Click MRAM element data size.
 * @details Predefined MRAM element data size enum values.
 */
typedef enum
{
    CANFD6_MRAM_8_Byte_Data  = 0,
    CANFD6_MRAM_12_Byte_Data = 0x1,
    CANFD6_MRAM_16_Byte_Data = 0x2,
    CANFD6_MRAM_20_Byte_Data = 0x3,
    CANFD6_MRAM_24_Byte_Data = 0x4,
    CANFD6_MRAM_32_Byte_Data = 0x5,
    CANFD6_MRAM_48_Byte_Data = 0x6,
    CANFD6_MRAM_64_Byte_Data = 0x7
    
} canfd6_mram_elem_data_size_t;

/**
 * @brief CAN FD 6 SID SFEC enum.
 * @details Predefined SID SFEC enum values.
 */
typedef enum
{
    CANFD6_SID_SFEC_DISABLED          = 0x0,       /**< Disabled filter. This filter will do nothing if it matches a packet. */
    CANFD6_SID_SFEC_STORERX0          = 0x1,       /**< Store in RX FIFO 0 if the filter matches the incoming message. */
    CANFD6_SID_SFEC_STORERX1          = 0x2,       /**< Store in RX FIFO 1 if the filter matches the incoming message. */
    CANFD6_SID_SFEC_REJECTMATCH       = 0x3,       /**< Reject the packet (do not store, do not notify MCU) if the filter matches the incoming message. */
    CANFD6_SID_SFEC_PRIORITY          = 0x4,       /**< Store in default location but set a high priority message interrupt if the filter matches the incoming message. */
    CANFD6_SID_SFEC_PRIORITYSTORERX0  = 0x5,       /**< Store in RX FIFO 0 and set a high priority message interrupt if the filter matches the incoming message. */
    CANFD6_SID_SFEC_PRIORITYSTORERX1  = 0x6,       /**< Store in RX FIFO 1 and set a high priority message interrupt if the filter matches the incoming message. */
    CANFD6_SID_SFEC_STORERXBUFORDEBUG = 0x7        /**< Store in RX Buffer for debug if the filter matches the incoming message. SFT is ignored if this is selected. */
    
} canfd6_sid_sfec_values_t;

/**
 * @brief CAN FD 6 SID SFT enum.
 * @details Predefined SID SFT enum values.
 */
typedef enum
{
    CANFD6_SID_SFT_DISABLED           = 0x3,       /**< Disabled filter. This filter will match nothing. */
    CANFD6_SID_SFT_CLASSIC            = 0x2,       /**< Classic filter with SFID1 as the ID to match, and SFID2 as the bit mask that applies to SFID1. */
    CANFD6_SID_SFT_DUALID             = 0x1,       /**< Dual ID filter, where both SFID1 and SFID2 hold IDs that can match (must match exactly). */
    CANFD6_SID_SFT_RANGE              = 0x0        /**< Range Filter. SFID1 holds the start address, and SFID2 holds the end address. Any address in between will match. */
    
} canfd6_sid_sft_values_t;

/**
 * @brief CAN FD 6 XID EFEC enum.
 * @details Predefined XID EFEC enum values.
 */
typedef enum
{
    CANFD6_XID_EFEC_DISABLED          = 0x0,       /**< Disabled filter. This filter will do nothing if it matches a packet. */
    CANFD6_XID_EFEC_STORERX0          = 0x1,       /**< Store in RX FIFO 0 if the filter matches the incoming message. */
    CANFD6_XID_EFEC_STORERX1          = 0x2,       /**< Store in RX FIFO 1 if the filter matches the incoming message. */
    CANFD6_XID_EFEC_REJECTMATCH       = 0x3,       /**< Reject the packet (do not store, do not notify MCU) if the filter matches the incoming message. */
    CANFD6_XID_EFEC_PRIORITY          = 0x4,       /**< Store in default location but set a high priority message interrupt if the filter matches the incoming message. */
    CANFD6_XID_EFEC_PRIORITYSTORERX0  = 0x5,       /**< Store in RX FIFO 0 and set a high priority message interrupt if the filter matches the incoming message. */
    CANFD6_XID_EFEC_PRIORITYSTORERX1  = 0x6,       /**< Store in RX FIFO 1 and set a high priority message interrupt if the filter matches the incoming message. */
    CANFD6_XID_EFEC_STORERXBUFORDEBUG = 0x7        /**< Store in RX Buffer for debug if the filter matches the incoming message. */
    
} canfd6_xid_efec_values_t;

/**
 * @brief CAN FD 6 XID EFT enum.
 * @details Predefined XID EFT enum values.
 */
typedef enum
{
    CANFD6_XID_EFT_RANGENOMASK        = 0x3,       /**< Range filter from EFID1 to EFID2, The XIDAM mask is not applied. */
    CANFD6_XID_EFT_CLASSIC            = 0x2,       /**< Classic Filter, EFID1 is the ID/filter, and EFID2 is the mask. */
    CANFD6_XID_EFT_DUALID             = 0x1,       /**< Dual ID filter matches if the incoming ID matches EFID1 or EFID2. */
    CANFD6_XID_EFT_RANGE              = 0x0        /**< Range filter from EFID1 to EFID2. */
    
} canfd6_xid_eft_values_t;

/**
 * @brief CAN FD 6 GFC enum.
 * @details Predefined GFC enum values.
 */
typedef enum
{
    CANFD6_GFC_ACCEPT_INTO_RXFIFO0 = 0,            /**< Accept into RXFIFO0. */
    CANFD6_GFC_ACCEPT_INTO_RXFIFO1 = 1,            /**< Accept into RXFIFO1. */
    CANFD6_GFC_REJECT = 2                          /**< Reject. */
    
} canfd6_gfc_no_match_behavior_t;

/**
 * @brief CAN FD 6 GPO1 config enum.
 * @details Predefined GPO1 config enum values.
 */
typedef enum
{
    CANFD6_DEV_CONFIG_GPO1_SPI_FAULT_INT = 0,      /**< Active low output for a SPIERR. */
    CANFD6_DEV_CONFIG_GPO1_MCAN_INT1 = 1,          /**< Active low output for MCAN_INT1 output (See MCAN ILE and ILS registers to use). */
    CANFD6_DEV_CONFIG_GPO1_UVO_OR_THERMAL_INT = 2, /**< Active low output for any under voltage or over temp interrupt. */
    
} canfd6_dev_config_gpo1_t;

/**
 * @brief CAN FD 6 GPIO1 config enum.
 * @details Predefined GPIO1 config enum values.
 */
typedef enum
{
    CANFD6_DEV_CONFIG_GPIO1_CONFIG_GPO = 0,        /**< Sets GPIO1 as an output. Be sure to see GPIO1_GPO_CONFIG field to set the behavior. */
    CANFD6_DEV_CONFIG_GPIO1_CONFIG_WDT_INPUT = 2   /**< Sets GPIO1 as an input for the watchdog timer. Watchdog will need to be enabled. */
    
} canfd6_dev_config_gpio1_t;

/**
 * @brief CAN FD 6 WDT action enum.
 * @details Predefined watchdog action enum values.
 */
typedef enum
{
    CANFD6_DEV_CONFIG_WDT_ACTION_nINT = 0,         /**< Sets an interrupt flag and the interrupt pin will be pulled low. */
    CANFD6_DEV_CONFIG_WDT_ACTION_PULSE_INH = 1,    /**< Pulse INH low for ~300 ms then high. */
    CANFD6_DEV_CONFIG_WDT_ACTION_PULSE_WDT_OUT = 2 /**< Pulse the watchdog output pin low for ~300 ms and high. */
    
} canfd6_dev_config_wdt_action_t;

/**
 * @brief CAN FD 6 GPO2 config enum.
 * @details Predefined GPO2 config enum values.
 */
typedef enum
{
    CANFD6_DEV_CONFIG_GPO2_NO_ACTION = 0,          /**< No action for GPO2. */
    CANFD6_DEV_CONFIG_GPO2_MCAN_INT0 = 1,          /**< Used as an output for MCAN INT0. */
    CANFD6_DEV_CONFIG_GPO2_WATCHDOG = 2,           /**< Used as a watchdog output. */
    CANFD6_DEV_CONFIG_GPO2_MIRROR_INT = 3          /**< Mirror nINT pin. */
    
} canfd6_dev_config_gpo2_t;

/**
 * @brief CAN FD 6 wake config enum.
 * @details Predefined wake config enum values.
 */
typedef enum
{
    CANFD6_DEV_CONFIG_WAKE_DISABLED = 0,           /**< Disabled. Wake pin is not used. */
    CANFD6_DEV_CONFIG_WAKE_RISING_EDGE = 1,        /**< Low to high transition will wake the part. */
    CANFD6_DEV_CONFIG_WAKE_FALLING_EDGE = 2,       /**< High to low transition will wake the part. */
    CANFD6_DEV_CONFIG_WAKE_BOTH_EDGES = 3          /**< Either transition will wake the part. */
    
} canfd6_dev_config_wake_t;

/**
 * @brief CAN FD 6 Click data timing simple structure.
 * @details Used to setup the data timing parameters of the MCAN module.
 */
typedef struct
{
    uint8_t data_bitrate_prescaler : 6;            /**< Prescaler value, interpreted as 1:x, valid range is: 1 to 32. */
    uint8_t data_tqbefore_samplepoint : 6;         /**< Number of time quanta before sample point, valid values are: 2 to 33. */
    uint8_t data_tqafter_samplepoint : 5;          /**< Number of time quanta after sample point, valid values are: 1 to 16. */

} canfd6_mcan_data_timing_simple_t;

/**
 * @brief CAN FD 6 Click data timing raw structure.
 * @details Used to setup the data timing parameters of the MCAN module.
 */
typedef struct
{
    uint8_t data_bitrate_prescaler : 5;              /**< The prescaler value from the MCAN system clock, valid range is: 0 to 31. */
    uint8_t data_time_seg1_and_prop : 5;             /**< Data time segment 1 + prop segment value, valid values are: 0 to 31. */
    uint8_t data_time_seg2 : 4;                      /**< Data time segment 2, valid values are: 0 to 15. */
    uint8_t data_sync_jumpwidth : 4;                 /**< Data resynchronization jump width, valid values are: 0 to 15. */
    uint8_t tdc_offset : 7;                          /**< Transmitter delay compensation offset, valid values are 0 to 127 mtq. */
    uint8_t tdc_filter : 7;                          /**< Transmitter delay compensation Filter Window Length, valid values are 0 to 127 mtq. */

} canfd6_mcan_data_timing_raw_t;

/**
 * @brief CAN FD 6 Click nominal timing simple structure.
 * @details Used to setup the nominal timing parameters of the MCAN module.
 */
typedef struct
{
    uint16_t nominal_bitrate_prescaler : 10;         /**< The prescaler value from the MCAN system clock, interpreted as 1:x, valid range is: 1 to 512. */
    uint16_t nominal_tqbefore_samplepoint : 9;       /**< The total number of time quanta prior to sample point, valid values are: 2 to 257. */
    uint8_t nominal_tqafter_samplepoint : 8;         /**< The total number of time quanta after the sample point, valid values are: 2 to 128. */

} canfd6_mcan_nominal_timing_simple_t;

/**
 * @brief CAN FD 6 Click nominal timing raw structure.
 * @details Used to setup the nominal timing parameters of the MCAN module.
 */
typedef struct
{
    uint16_t nominal_bitrate_prescaler : 9;          /**< The prescaler value from the MCAN system clock, valid range is: 0 to 511. */
    uint8_t nominal_time_seg1_and_prop : 8;          /**< Data time segment 1 + prop segment value, valid values are: 0 to 255. */
    uint8_t nominal_time_seg2 : 7;                   /**< Data time segment 2, valid values are: 0 to 127. */
    uint8_t nominal_sync_jumpwidth : 7;              /**< Nominal time resynchronization jump width, valid values are: 0 to 127. */
    
} canfd6_mcan_nominal_timing_raw_t;

/**
 * @brief CAN FD 6 Click MRAM config.
 * @details Defines the number of MRAM elements and the size of the elements.
 */
typedef struct
{
    uint8_t sid_num_elements : 8;                    /**< Standard 11-bit ID Number of Filter Elements, valid range is: 0 to 128. */
    uint8_t xid_num_elements : 7;                    /**< Extended 29-bit ID Number of Filter Elements, valid range is: 0 to 64. */
    uint8_t rx0_num_elements : 7;                    /**< RX FIFO 0 number of elements, valid range is: 0 to 64. */
    canfd6_mram_elem_data_size_t rx0_element_size : 3; /**< RX FIFO 0 element size: The number of bytes for the RX 0 FIFO (data payload). */
    uint8_t rx1_num_elements : 7;                    /**< RX FIFO 1 number of elements, valid range is: 0 to 64. */
    canfd6_mram_elem_data_size_t rx1_element_size : 3; /**< RX FIFO 1 element size: The number of bytes for the RX 1 FIFO (data payload). */
    uint8_t rx_buf_num_elements : 7;                 /**< RX Buffers number of elements, valid range is: 0 to 64. */
    canfd6_mram_elem_data_size_t rx_buf_element_size : 3; /**< RX Buffers element size. */
    uint8_t tx_event_fifo_num_elements : 6;          /**< TX Event FIFO number of elements, valid range is: 0 to 32. */
    uint8_t tx_buffer_num_elements : 6;              /**< TX Buffers number of elements, valid range is: 0 to 32. */
    canfd6_mram_elem_data_size_t tx_buf_element_size : 3; /**< TX Buffers element size. */

} canfd6_mram_config_t;

/**
 * @brief CAN FD 6 Click CCCR config.
 * @details Struct containing the bit fields of the MCAN CCCR register.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t reserved : 2;                    /**< RESERVED. */
            uint8_t ASM : 1;                         /**< Restricted Operation Mode. The device can only listen to CAN traffic and acknowledge, but not send anything. */
            uint8_t reserved2 : 1;                   /**< RESERVED. */
            uint8_t CSR : 1;                         /**< Clock stop request. */
            uint8_t MON : 1;                         /**< Bus monitoring mode. The device may only listen to CAN traffic, and is not allowed to acknowledge or send error frames. */
            uint8_t DAR : 1;                         /**< Disable automatic retransmission. */
            uint8_t TEST : 1;                        /**< MCAN Test mode enable. */
            uint8_t FDOE : 1;                        /**< Can FD mode enabled, master enable for CAN FD support. */
            uint8_t BRSE : 1;                        /**< Bit rate switch enabled for can FD. Master enable for bit rate switching support. */
            uint8_t reserved3 : 2;                   /**< RESERVED. */
            uint8_t PXHD : 1;                        /**< Protocol exception handling disable. */
            uint8_t EFBI : 1;                        /**< Edge filtering during bus integration. 0 Disables this [default]. */
            uint8_t TXP : 1;                         /**< Transmit Pause Enable: Pause for 2 can bit times before next transmission. */
            uint8_t NISO : 1;                        /**< Non Iso Operation. */
        };
    };
} canfd6_mcan_cccr_config_t;

/**
 * @brief CAN FD 6 Click MCAN interrupts.
 * @details Struct containing the MCAN interrupt bit field.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t RF0N : 1;                        /**< IR[0] RF0N: Rx FIFO 0 new message. */
            uint8_t RF0W : 1;                        /**< IR[1] RF0W: Rx FIFO 0 watermark reached. */
            uint8_t RF0F : 1;                        /**< IR[2] RF0F: Rx FIFO 0 full. */
            uint8_t RF0L : 1;                        /**< IR[3] RF0L: Rx FIFO 0 message lost. */
            uint8_t RF1N : 1;                        /**< IR[4] RF1N: Rx FIFO 1 new message. */
            uint8_t RF1W : 1;                        /**< IR[5] RF1W: RX FIFO 1 watermark reached. */
            uint8_t RF1F : 1;                        /**< IR[6] RF1F: Rx FIFO 1 full. */
            uint8_t RF1L : 1;                        /**< IR[7] RF1L: Rx FIFO 1 message lost. */
            uint8_t HPM : 1;                         /**< IR[8] HPM: High priority message. */
            uint8_t TC : 1;                          /**< IR[9] TC: Transmission completed. */
            uint8_t TCF : 1;                         /**< IR[10] TCF: Transmission cancellation finished. */
            uint8_t TFE : 1;                         /**< IR[11] TFE: Tx FIFO Empty. */
            uint8_t TEFN : 1;                        /**< IR[12] TEFN: Tx Event FIFO new entry. */
            uint8_t TEFW : 1;                        /**< IR[13] TEFW: Tx Event FIFO water mark reached. */
            uint8_t TEFF : 1;                        /**< IR[14] TEFF: Tx Event FIFO full. */
            uint8_t TEFL : 1;                        /**< IR[15] TEFL: Tx Event FIFO element lost. */
            uint8_t TSW : 1;                         /**< IR[16] TSW: Timestamp wrapped around. */
            uint8_t MRAF : 1;                        /**< IR[17] MRAF: Message RAM access failure. */
            uint8_t TOO : 1;                         /**< IR[18] TOO: Time out occurred. */
            uint8_t DRX : 1;                         /**< IR[19] DRX: Message stored to dedicated RX buffer. */
            uint8_t BEC : 1;                         /**< IR[20] BEC: MRAM Bit error corrected. */
            uint8_t BEU : 1;                         /**< IR[21] BEU: MRAM Bit error uncorrected. */
            uint8_t ELO : 1;                         /**< IR[22] ELO: Error logging overflow. */
            uint8_t EP : 1;                          /**< IR[23] EP: Error_passive status changed. */
            uint8_t EW : 1;                          /**< IR[24] EW: Error_warning status changed. */
            uint8_t BO : 1;                          /**< IR[25] BO: Bus_off status changed. */
            uint8_t WDI : 1;                         /**< IR[26] WDI: MRAM Watchdog Interrupt. */
            uint8_t PEA : 1;                         /**< IR[27] PEA Protocol Error in arbitration phase (nominal bit time used). */
            uint8_t PED : 1;                         /**< IR[28] PED: Protocol error in data phase (data bit time is used). */
            uint8_t ARA : 1;                         /**< IR[29] ARA: Access to reserved address. */
            uint8_t reserved : 2;                    /**< IR[30:31] Reserved, not writable. */
        };
    };
} canfd6_mcan_interrupts_t;

/**
 * @brief CAN FD 6 Click MCAN interrupt enable.
 * @details Struct containing the MCAN interrupt enable bit field.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t RF0NE : 1;                       /**< IE[0] RF0NE: Rx FIFO 0 new message. */
            uint8_t RF0WE : 1;                       /**< IE[1] RF0WE: Rx FIFO 0 watermark reached. */
            uint8_t RF0FE : 1;                       /**< IE[2] RF0FE: Rx FIFO 0 full. */
            uint8_t RF0LE : 1;                       /**< IE[3] RF0LE: Rx FIFO 0 message lost. */
            uint8_t RF1NE : 1;                       /**< IE[4] RF1NE: Rx FIFO 1 new message. */
            uint8_t RF1WE : 1;                       /**< IE[5] RF1WE: RX FIFO 1 watermark reached. */
            uint8_t RF1FE : 1;                       /**< IE[6] RF1FE: Rx FIFO 1 full. */
            uint8_t RF1LE : 1;                       /**< IE[7] RF1LE: Rx FIFO 1 message lost. */
            uint8_t HPME : 1;                        /**< IE[8] HPME: High priority message. */
            uint8_t TCE : 1;                         /**< IE[9] TCE: Transmission completed. */
            uint8_t TCFE : 1;                        /**< IE[10] TCFE: Transmission cancellation finished. */
            uint8_t TFEE : 1;                        /**< IE[11] TFEE: Tx FIFO Empty. */
            uint8_t TEFNE : 1;                       /**< IE[12] TEFNE: Tx Event FIFO new entry. */
            uint8_t TEFWE : 1;                       /**< IE[13] TEFWE: Tx Event FIFO watermark reached. */
            uint8_t TEFFE : 1;                       /**< IE[14] TEFFE: Tx Event FIFO full. */
            uint8_t TEFLE : 1;                       /**< IE[15] TEFLE: Tx Event FIFO element lost. */
            uint8_t TSWE : 1;                        /**< IE[16] TSWE: Timestamp wraparound. */
            uint8_t MRAFE : 1;                       /**< IE[17] MRAFE: Message RAM access failure. */
            uint8_t TOOE : 1;                        /**< IE[18] TOOE: Time out occured. */
            uint8_t DRXE : 1;                        /**< IE[19] DRXE: Message stored to dedicated RX buffer. */
            uint8_t BECE : 1;                        /**< IE[20] BECE: MRAM Bit error corrected. */
            uint8_t BEUE : 1;                        /**< IE[21] BEUE: MRAM Bit error uncorrected. */
            uint8_t ELOE : 1;                        /**< IE[22] ELOE: Error logging overflow. */
            uint8_t EPE : 1;                         /**< IE[23] EPE: Error_passive status changed. */
            uint8_t EWE : 1;                         /**< IE[24] EWE: Error_warning status changed. */
            uint8_t BOE : 1;                         /**< IE[25] BOE: Bus_off status changed. */
            uint8_t WDIE : 1;                        /**< IE[26] WDIE: MRAM Watchdog Interrupt. */
            uint8_t PEAE : 1;                        /**< IE[27] PEAE Protocol Error in arbitration phase (nominal bit time used). */
            uint8_t PEDE : 1;                        /**< IE[28] PEDE: Protocol error in data phase (data bit time is used). */
            uint8_t ARAE : 1;                        /**< IE[29] ARAE: Access to reserved address. */
            uint8_t reserved : 2;                    /**< IE[30:31] Reserved, not writable. */
        };
    };
} canfd6_mcan_interrupt_enable_t;

/**
 * @brief CAN FD 6 Click CAN message header.
 * @details Struct containing the CAN message header.
 */
typedef struct
{
    uint32_t ID : 29;                                /**< CAN ID received. */
    uint8_t RTR : 1;                                 /**< Remote Transmission Request flag. */
    uint8_t XTD : 1;                                 /**< Extended Identifier flag. */
    uint8_t ESI : 1;                                 /**< Error state indicator flag. */
    uint16_t RXTS : 16;                              /**< Receive time stamp. */
    uint8_t DLC : 4;                                 /**< Data length code. */
    uint8_t BRS : 1;                                 /**< Bit rate switch used flag. */
    uint8_t FDF : 1;                                 /**< CAN FD Format flag. */
    uint8_t reserved : 2;                            /**< RESERVED. */
    uint8_t FIDX : 7;                                /**< Filter index that this message matched. */
    uint8_t ANMF : 1;                                /**< Accepted non matching frame flag. */

} canfd6_mcan_rx_header_t;

/**
 * @brief CAN FD 6 Click CAN message header for transmitted messages.
 * @details Struct containing the CAN message header for transmitted messages.
 */
typedef struct
{
    uint32_t ID : 29;                                /**< CAN ID to send. */
    uint8_t RTR : 1;                                 /**< Remote Transmission Request flag. */
    uint8_t XTD : 1;                                 /**< Extended Identifier flag. */
    uint8_t ESI : 1;                                 /**< Error state indicator flag. */
    uint8_t DLC : 4;                                 /**< Data length code. */
    uint8_t BRS : 1;                                 /**< Bit rate switch used flag. */
    uint8_t FDF : 1;                                 /**< CAN FD Format flag. */
    uint8_t reserved : 1;                            /**< RESERVED. */
    uint8_t EFC : 1;                                 /**< Event FIFO Control flag, to store tx events or not. */
    uint8_t MM : 8;                                  /**< Message Marker, used if @c EFC is set to 1. */

} canfd6_mcan_tx_header_t;

/**
 * @brief CAN FD 6 Click standard ID filter struct.
 * @details Struct containing the standard ID filter.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint16_t SFID2 : 11;                     /**< SFID2[10:0]. */
            uint8_t reserved : 5;                    /**< RESERVED. */
            uint16_t SFID1 : 11;                     /**< SFID1[10:0]. */
            canfd6_sid_sfec_values_t SFEC : 3;       /**< SFEC[2:0] : Standard filter element configuration. */
            canfd6_sid_sfec_values_t SFT : 2;        /**< SFT Standard Filter Type. */
        };
    };
} canfd6_mcan_sid_filter_t;

/**
 * @brief CAN FD 6 Click extended ID filter struct.
 * @details Struct containing the extended ID filter.
 */
typedef struct
{
    uint32_t EFID2 : 29;                             /**< EFID2[28:0]. */
    uint8_t reserved : 1;                            /**< RESERVED. */
    canfd6_xid_eft_values_t EFT : 2;                 /**< EFT[1:0]. */
    uint32_t EFID1 : 29;                             /**< EFID1[28:0]. */
    canfd6_xid_efec_values_t EFEC : 3;               /**< SFT Standard Filter Type. */
    
} canfd6_mcan_xid_filter_t;

/**
 * @brief CAN FD 6 Click Global Filter Configuration Register struct.
 * @details Struct containing the register values for the Global Filter Configuration Register.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t RRFE : 1;                        /**< GFC[0] : Reject Remote Frames for Extended IDs. */
            uint8_t RRFS : 1;                        /**< GFC[1] : Reject Remote Frames for Standard IDs. */
            canfd6_gfc_no_match_behavior_t ANFE : 2; /**< GFC[3:2] : Accept Non-matching Frames Extended. */
            canfd6_gfc_no_match_behavior_t ANFS : 2; /**< GFC[5:4] : Accept Non-matching Frames Standard. */
            uint32_t reserved : 26;                  /**< RESERVED. */
        };
    };
} canfd6_mcan_global_filter_configuration_t;

/**
 * @brief CAN FD 6 Click device interrupt bit field struct.
 * @details Struct containing the device interrupt bit field.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t VTWD : 1;                        /**< DEV_IR[0] VTWD: Global Voltage, Temp, or Watchdog (if equipped) Interrupt. */
            uint8_t M_CAN_INT : 1;                   /**< DEV_IR[1] M_CAN_INT: There are MCAN interrupts pending. */
            uint8_t SWERR : 1;                       /**< DEV_IR[2] : Selective Wake Error (If equipped). */
            uint8_t SPIERR : 1;                      /**< DEV_IR[3] : SPI Error. */
            uint8_t CBF : 1;                         /**< DEV_IR[4] : CBF, CAN Bus Fault. */
            uint8_t CANERR : 1;                      /**< DEV_IR[5] : CANERR, CAN Error. */
            uint8_t WKRQ : 1;                        /**< DEV_IR[6] : WKRQ, Wake Request. */
            uint8_t GLOBALERR : 1;                   /**< DEV_IR[7] : GLOBALERR, Global Error. Is the OR output of all interrupts. */
            uint8_t CANDOM : 1;                      /**< DEV_IR[8] : CANDOM, Can bus stuck dominant. */
            uint8_t RESERVED : 1;                    /**< DEV_IR[9] : RESERVED. */
            uint8_t CANTO : 1;                       /**< DEV_IR[10] : CANTO, CAN Timeout. */
            uint8_t RESERVED2 : 1;                   /**< DEV_IR[11] : RESERVED. */
            uint8_t FRAME_OVF : 1;                   /**< DEV_IR[12] : FRAME_OVF, Frame Error Overflow (If Selective Wake is equipped). */
            uint8_t WKERR : 1;                       /**< DEV_IR[13] : WKERR, Wake Error. */
            uint8_t LWU : 1;                         /**< DEV_IR[14] : LWU, Local Wake Up. */
            uint8_t CANINT : 1;                      /**< DEV_IR[15] : CANINT, CAN Bus Wake Up Interrupt. */
            uint8_t ECCERR : 1;                      /**< DEV_IR[16] : ECCERR, MRAM ECC Error. */
            uint8_t RESERVED3 : 1;                   /**< DEV_IR[17] : RESERVED. */
            uint8_t WDTO : 1;                        /**< DEV_IR[18] : WDTO, Watchdog Time Out. */
            uint8_t TSD : 1;                         /**< DEV_IR[19] : TSD, Thermal Shut Down. */
            uint8_t PWRON : 1;                       /**< DEV_IR[20] : PWRON, Power On Interrupt. */
            uint8_t UVIO : 1;                        /**< DEV_IR[21] : UVIO, Undervoltage on UVIO. */
            uint8_t UVSUP : 1;                       /**< DEV_IR[22] : UVSUP, Undervoltage on VSUP and VCCOUT. */
            uint8_t SMS : 1;                         /**< DEV_IR[23] : SMS, Sleep Mode Status Flag. Set when sleep mode is entered due to WKERR, UVIO, or TSD faults. */
            uint8_t CANBUSBAT : 1;                   /**< DEV_IR[24] : CANBUSBAT, CAN Shorted to VBAT. */
            uint8_t CANBUSGND : 1;                   /**< DEV_IR[25] : CANBUSGND, CAN Shorted to GND. */
            uint8_t CANBUSOPEN : 1;                  /**< DEV_IR[26] : CANBUSOPEN, CAN Open fault. */
            uint8_t CANLGND : 1;                     /**< DEV_IR[27] : CANLGND, CANL GND. */
            uint8_t CANHBAT : 1;                     /**< DEV_IR[28] : CANHBAT, CANH to VBAT. */
            uint8_t CANHCANL : 1;                    /**< DEV_IR[29] : CANHCANL, CANH and CANL shorted. */
            uint8_t CANBUSTERMOPEN : 1;              /**< DEV_IR[30] : CANBUSTERMOPEN, CAN Bus has termination point open. */
            uint8_t CANBUSNORM : 1;                  /**< DEV_IR[31] : CANBUSNOM, CAN Bus is normal flag. */
        };
    };
} canfd6_device_interrupts_t;

/**
 * @brief CAN FD 6 Click device interrupt enable bit field struct.
 * @details Struct containing the device interrupt enable bit field.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t RESERVED1 : 8;                   /**< DEV_IE[7:0] : RESERVED. */
            uint8_t CANDOMEN : 1;                    /**< DEV_IE[8] : CANDOM, Can bus stuck dominant. */
            uint8_t RESERVED2 : 1;                   /**< DEV_IE[9] : RESERVED. */
            uint8_t CANTOEN : 1;                     /**< DEV_IE[10] : CANTO, CAN Timeout. */
            uint8_t RESERVED3 : 1;                   /**< DEV_IE[11] : RESERVED. */
            uint8_t FRAME_OVFEN : 1;                 /**< DEV_IE[12] : FRAME_OVF, Frame Error Overflow (If Selective Wake is equipped). */
            uint8_t WKERREN : 1;                     /**< DEV_IE[13] : WKERR, Wake Error. */
            uint8_t LWUEN : 1;                       /**< DEV_IE[14] : LWU, Local Wake Up. */
            uint8_t CANINTEN : 1;                    /**< DEV_IE[15] : CANINT, CAN Bus Wake Up Interrupt. */
            uint8_t ECCERREN : 1;                    /**< DEV_IE[16] : ECCERR, MRAM ECC Error. */
            uint8_t RESERVED4 : 1;                   /**< DEV_IE[17] : RESERVED. */
            uint8_t WDTOEN : 1;                      /**< DEV_IE[18] : WDTO, Watchdog Time Out. */
            uint8_t TSDEN : 1;                       /**< DEV_IE[19] : TSD, Thermal Shut Down. */
            uint8_t PWRONEN : 1;                     /**< DEV_IE[20] : PWRON, Power On Interrupt. */
            uint8_t UVIOEN : 1;                      /**< DEV_IE[21] : UVIO, Undervoltage on UVIO. */
            uint8_t UVSUPEN : 1;                     /**< DEV_IE[22] : UVSUP, Undervoltage on VSUP and VCCOUT. */
            uint8_t SMSEN : 1;                       /**< DEV_IE[23] : SMS, Sleep Mode Status Flag. Set when sleep mode is entered due to WKERR, UVIO, or TSD faults. */
            uint8_t CANBUSBATEN : 1;                 /**< DEV_IE[24] : CANBUSBAT, CAN Shorted to VBAT. */
            uint8_t CANBUSGNDEN : 1;                 /**< DEV_IE[25] : CANBUSGND, CAN Shorted to GND. */
            uint8_t CANBUSOPENEN : 1;                /**< DEV_IE[26] : CANBUSOPEN, CAN Open fault. */
            uint8_t CANLGNDEN : 1;                   /**< DEV_IE[27] : CANLGND, CANL GND. */
            uint8_t CANHBATEN : 1;                   /**< DEV_IE[28] : CANHBAT, CANH to VBAT. */
            uint8_t CANHCANLEN : 1;                  /**< DEV_IE[29] : CANHCANL, CANH and CANL shorted. */
            uint8_t CANBUSTERMOPENEN : 1;            /**< DEV_IE[30] : CANBUSTERMOPEN, CAN Bus has termination point open. */
            uint8_t CANBUSNORMEN : 1;                /**< DEV_IE[31] : CANBUSNOM, CAN Bus is normal flag. */
        };
    };
} canfd6_device_interrupt_enable_t;

/**
 * @brief CAN FD 6 Click device config struct.
 * @details Struct containing the device global configuration.
 */
typedef struct
{
    union
    {
        uint32_t word;                               /**< Full register represented as a 32-bit word. */
        struct
        {
            uint8_t RESERVED0 : 1;                   /**< DEV_MODE_PINS[0] : Test mode configuration. Reserved in this struct. */
            uint8_t SWE_DIS: 1;                      /**< DEV_MODE_PINS[1] : Sleep wake error disable, setting this to '1' will disable the 4 minute timer. */
            uint8_t DEVICE_RESET : 1;                /**< DEV_MODE_PINS[2] : Device reset. Write a 1 to perform a reset on the part. */
            uint8_t WD_EN : 1;                       /**< DEV_MODE_PINS[3] : Watchdog Enable. Use the watchdog functions to control enabling the watchdog. */
            uint8_t RESERVED1 : 4;                   /**< DEV_MODE_PINS[7:6] : Mode Selection. Use the mode functions to change the mode. */
            uint8_t nWKRQ_CONFIG : 1;                /**< DEV_MODE_PINS[8] : nWKRQ Configuration [0]: Mirrors INH function / [1]: Wake request interrupt. */
            uint8_t INH_DIS : 1;                     /**< DEV_MODE_PINS[9] : Inhibit pin disable. */
            canfd6_dev_config_gpo1_t GPIO1_GPO_CONFIG : 2; /**< DEV_MODE_PINS[11:10] : GPIO1 pin as a GPO function configuration. */
            uint8_t RESERVED2 : 1;                   /**< DEV_MODE_PINS[12] : RESERVED. */
            uint8_t FAIL_SAFE_EN : 1;                /**< DEV_MODE_PINS[13] : Fail safe mode enable. Excludes power up fail safe. */
            canfd6_dev_config_gpio1_t GPIO1_CONFIG : 2; /**< DEV_MODE_PINS[15:14] : GPIO1 configuration. */
            canfd6_dev_config_wdt_action_t WD_ACTION : 2; /**< DEV_MODE_PINS[17:16] : Watchdog action. Defines the behavior of the watchdog timer when it times out. */
            uint8_t WD_BIT_RESET : 1;                /**< DEV_MODE_PINS[18] : Watchdog reset bit, write '1' to reset the watchdog timer. */
            uint8_t nWKRQ_VOLTAGE : 1;               /**< DEV_MODE_PINS[19] : nWKRQ_VOLTAGE, set the voltage rail used by the nWKRQ pin [0]: Internal / [1]: VIO. */
            uint8_t RESERVED3 : 2;                   /**< DEV_MODE_PINS[21:20] : RESERVED. Use test mode functions to enable test modes. */
            canfd6_dev_config_gpo2_t GPO2_CONFIG : 2; /**< DEV_MODE_PINS[23:22] : nWKRQ_VOLTAGE, set the voltage rail used by the nWKRQ pin. */
            uint8_t RESERVED4 : 3;                   /**< DEV_MODE_PINS[26:24] : RESERVED. */
            uint8_t CLK_REF : 1;                     /**< DEV_MODE_PINS[27] : CLK_REF, used to tell the device what the input clock/crystal frequency is [0]: 20 MHz / [1]: 40 MHz. */
            uint8_t RESERVED5 : 2;                   /**< DEV_MODE_PINS[29:28] : RESERVED. Use watchdog functions to set watchdog parameters. */
            canfd6_dev_config_wake_t WAKE_CONFIG : 2; /**< DEV_MODE_PINS[31:30] : WAKE_CONFIG, used to configure the direction required to wake a part up. */
        };
    };
} canfd6_dev_config_t;

/*!
 * @addtogroup canfd6 CAN FD 6 Click Driver
 * @brief API for configuring and manipulating CAN FD 6 Click driver.
 * @{
 */

/**
 * @brief CAN FD 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #canfd6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void canfd6_cfg_setup ( canfd6_cfg_t *cfg );

/**
 * @brief CAN FD 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #canfd6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_init ( canfd6_t *ctx, canfd6_cfg_t *cfg );

/**
 * @brief CAN FD 6 default configuration function.
 * @details This function executes a default configuration of CAN FD 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void canfd6_default_cfg ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 wkr pin state function.
 * @details This function sets the pin state of the wake request pin.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * 
 * @note None.
 */
void canfd6_wkr_pin_state ( canfd6_t *ctx, canfd6_pin_state_t state );

/**
 * @brief CAN FD 6 rst pin state function.
 * @details This function sets the pin state of the reset pin.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * 
 * @note None.
 */
void canfd6_rst_pin_state ( canfd6_t *ctx, canfd6_pin_state_t state );

/**
 * @brief CAN FD 6 wkp pin state function.
 * @details This function sets the pin state of the wake pin.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * 
 * @note None.
 */
void canfd6_wkp_pin_state ( canfd6_t *ctx, canfd6_pin_state_t state );

/**
 * @brief CAN FD 6 get int pin function.
 * @details This function checks the interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return Pin state.
 * 
 * @note None.
 */
uint8_t canfd6_get_int_pin ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 enable protected registers function.
 * @details This function attempts to enable CCCR.CCE and CCCR.INIT to allow
 * writes to protected registers, needed for MCAN configuration.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_enable_protected_registers ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 disable protected registers function.
 * @details This function attempts to disable CCCR.CCE and CCCR.INIT to
 * disallow writes to protected registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_disable_protected_registers ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 configure cccr register function.
 * @details This function configures the bits of the CCCR register to match
 * the CCCR config struct. This function writes to protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] cccr_config : Struct containing the configuration bits.
 *
 * @note Requires that protected registers have been unlocked.
 */
void canfd6_configure_cccr_register ( canfd6_t *ctx, canfd6_mcan_cccr_config_t *cccr_config );

/**
 * @brief CAN FD 6 read cccr register function.
 * @details This function reads the MCAN CCCR configuration register and
 * updates the MCAN CCCR Config struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] cccr_config : Struct containing the configuration bits.
 *
 * @note None.
 */
void canfd6_read_cccr_register ( canfd6_t *ctx, canfd6_mcan_cccr_config_t *cccr_config );

/**
 * @brief CAN FD 6 read data timing fd simple function.
 * @details This function reads the MCAN data timing registers and updates
 * the data timing simple struct. This function writes to protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] data_timing : Struct containing the simplified data timing information.
 *
 * @note None.
 */
void canfd6_mcan_read_datatimingfd_simple ( canfd6_t *ctx, canfd6_mcan_data_timing_simple_t *data_timing );

/**
 * @brief CAN FD 6 read data timing fd raw function.
 * @details This function reads the MCAN data timing registers and updates
 * the data timing raw struct. This function writes to protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] data_timing : Struct containing the raw data timing information.
 *
 * @note None.
 */
void canfd6_mcan_read_datatimingfd_raw ( canfd6_t *ctx, canfd6_mcan_data_timing_raw_t *data_timing );

/**
 * @brief CAN FD 6 configure data timing simple function.
 * @details This function writes the data timing information to MCAN using
 * the input from the data timing simple struct. This function writes to
 * protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] data_timing : Struct containing the simplified data timing information.
 *
 * @note Requires that protected registers have been unlocked.
 */
void canfd6_mcan_configure_datatiming_simple ( canfd6_t *ctx, canfd6_mcan_data_timing_simple_t *data_timing );

/**
 * @brief CAN FD 6 configure data timing raw function.
 * @details This function writes the data timing information to MCAN using
 * the input from the data timing raw struct. This function writes to protected
 * MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] data_timing : Struct containing the raw data timing information.
 *
 * @note Requires that protected registers have been unlocked.
 */
void canfd6_mcan_configure_datatiming_raw ( canfd6_t *ctx, canfd6_mcan_data_timing_raw_t *data_timing );

/**
 * @brief CAN FD 6 read nominal timing simple function.
 * @details This function reads the MCAN nominal timing registers and
 * updates the nominal timing simple struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] nom_timing : Struct containing the simplified nominal timing information.
 *
 * @note None.
 */
void canfd6_mcan_read_nominaltiming_simple ( canfd6_t *ctx, canfd6_mcan_nominal_timing_simple_t *nom_timing );

/**
 * @brief CAN FD 6 read nominal timing raw function.
 * @details This function reads the MCAN nominal timing registers and
 * updates the nominal timing raw struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] nom_timing : Struct containing the raw nominal timing information.
 *
 * @note None.
 */
void canfd6_mcan_read_nominaltiming_raw ( canfd6_t *ctx, canfd6_mcan_nominal_timing_raw_t *nom_timing );

/**
 * @brief CAN FD 6 configure nominal timing simple function.
 * @details This function writes the data timing information to MCAN using the
 * input from the nominal timing simple struct. This function writes to
 * protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] nom_timing : Struct containing the simplified nominal timing information.
 *
 * @note Requires that protected registers have been unlocked.
 */
void canfd6_mcan_configure_nominaltiming_simple ( canfd6_t *ctx, canfd6_mcan_nominal_timing_simple_t *nom_timing );

/**
 * @brief CAN FD 6 configure nominal timing raw function.
 * @details This function writes the data timing information to MCAN using the
 * input from the nominal timing raw struct. This function writes to
 * protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] nom_timing : Struct containing the raw nominal timing information.
 *
 * @note Requires that protected registers have been unlocked.
 */
void canfd6_mcan_configure_nominaltiming_raw ( canfd6_t *ctx, canfd6_mcan_nominal_timing_raw_t *nom_timing );

/**
 * @brief CAN FD 6 configure global filter function.
 * @details This function configures the default behavior of the MCAN controller
 * when receiving messages. This can include accepting or rejecting CAN messages
 * by default. This function writes to protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] gfc : Struct containing the global filter register values.
 *
 * @note Requires that protected registers have been unlocked.
 */
void canfd6_mcan_configure_globalfilter ( canfd6_t *ctx, canfd6_mcan_global_filter_configuration_t *gfc );

/**
 * @brief CAN FD 6 mram configure function.
 * @details This function uses the mram_config pointer to set up the various
 * sections of the MRAM memory space. There are several different elements that
 * may be configured in the MRAM, including their number of elements, as well
 * as size of elements. This function will automatically generate the start
 * addresses for each of the appropriate MRAM sections, attempting to place
 * them immediately back-to-back. This function will check for over allocated
 * memory conditions, and return error if this is found to be the case.
 * This function writes to protected MCAN registers.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] mram_config : Struct containing the desired MRAM configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note Requires that protected registers have been unlocked.
 */
err_t canfd6_mram_configure ( canfd6_t *ctx, canfd6_mram_config_t *mram_config );

/**
 * @brief CAN FD 6 mram clear function.
 * @details This function clears every address in MRAM. Useful for initializing
 * the MRAM to known values during initial configuration so that accidental ECC
 * errors do not happen.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 *
 * @note None.
 */
void canfd6_mram_clear ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 read next fifo function.
 * @details This function will read the next MCAN FIFO element specified and
 * return the corresponding header information and data payload. The start
 * address of the elment is automatically calculated by looking at the MCAN's
 * register that says where the next element to read exists.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] fifo_def : Enum corresponding to either RXFIFO0 or RXFIFO1.
 * @param[out] header : Struct containing the CAN-specific header information.
 * @param[out] data_payload[ ] : Byte array that will be updated with the read data.
 * @return The number of bytes that were read.
 * 
 * @note data_payload[ ] must be at least as big as the largest possible data payload,
 * otherwise writing to out of bounds memory may occur.
 */
uint8_t canfd6_mcan_read_nextfifo ( canfd6_t *ctx, canfd6_mcan_fifo_enum_t fifo_def, canfd6_mcan_rx_header_t *header, uint8_t data_payload[ ] );

/**
 * @brief CAN FD 6 read rx buffer function.
 * @details This function will read the specified MCAN buffer element and return
 * the corresponding header information and data payload. The start address of the
 * element is automatically calculated.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] buf_index : RX buffer index to read from (starts at 0).
 * @param[out] header : Struct containing the CAN-specific header information.
 * @param[out] data_payload[ ] : Byte array that will be updated with the read data.
 * @return The number of bytes that were read.
 * 
 * @note data_payload[ ] must be at least as big as the largest possible data payload,
 * otherwise writing to out of bounds memory may occur.
 */
uint8_t canfd6_mcan_read_rxbuffer ( canfd6_t *ctx, uint8_t buf_index, canfd6_mcan_rx_header_t *header, uint8_t data_payload[ ] );

/**
 * @brief CAN FD 6 write tx buffer function.
 * @details This function will write a CAN message to a specified TX buffer that
 * can be transmitted at a later time with the transmit buffer contents function.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] buf_index : TX buffer index to write to (starts at 0).
 * @param[in] header : Struct containing the CAN-specific header information.
 * @param[in] data_payload[ ] : Byte array that will be updated with the read data.
 * @return The number of bytes that were read.
 * 
 * @note data_payload[ ] must be at least as big as the largest possible data payload,
 * otherwise writing to out of bounds memory may occur.
 */
uint32_t canfd6_mcan_write_txbuffer ( canfd6_t *ctx, uint8_t buf_index, canfd6_mcan_tx_header_t *header, uint8_t data_payload[ ] );

/**
 * @brief CAN FD 6 transmit buffer contents function.
 * @details This function writes the specified buffer index bit value into the
 * TXBAR register to request a message to send.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] buf_index : TX buffer index to write to (starts at 0).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note Function does NOT check if the buffer contents are valid.
 */
err_t canfd6_mcan_transmit_buffer_contents ( canfd6_t *ctx, uint8_t buf_index );

/**
 * @brief CAN FD 6 write sid filter function.
 * @details This function will write a standard ID MCAN filter to a specified
 * filter element.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] filter_index : SID filter index in MRAM to write to (starts at 0).
 * @param[in] filter : Struct containing the MCAN filter information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_mcan_write_sid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_sid_filter_t *filter );

/**
 * @brief CAN FD 6 read sid filter function.
 * @details This function will read a standard ID MCAN filter from a specified
 * filter element.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] filter_index : SID filter index in MRAM to read from (starts at 0).
 * @param[out] filter : Struct containing the MCAN filter information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_mcan_read_sid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_sid_filter_t *filter );

/**
 * @brief CAN FD 6 write xid filter function.
 * @details This function will write an extended ID MCAN filter to a specified
 * filter element.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] filter_index : XID filter index in MRAM to write to (starts at 0).
 * @param[in] filter : Struct containing the MCAN filter information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_mcan_write_xid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_xid_filter_t *filter );

/**
 * @brief CAN FD 6 read xid filter function.
 * @details This function will read an extended ID MCAN filter from a specified
 * filter element.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] filter_index : XID filter index in MRAM to read from (starts at 0).
 * @param[out] filter : Struct containing the MCAN filter information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_mcan_read_xid_filter ( canfd6_t *ctx, uint8_t filter_index, canfd6_mcan_xid_filter_t *filter );

/**
 * @brief CAN FD 6 read interrupts function.
 * @details Reads and updates the mcan interrupts struct that is passed to the function.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] ir : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_mcan_read_interrupts ( canfd6_t *ctx, canfd6_mcan_interrupts_t *ir );

/**
 * @brief CAN FD 6 clear interrupts function.
 * @details This function will attempt to clear any interrupts that are marked as
 * a '1' in the passed mcan interrupt struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] ir : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_mcan_clear_interrupts ( canfd6_t *ctx, canfd6_mcan_interrupts_t *ir );

/**
 * @brief CAN FD 6 clear interrupts all function.
 * @details This function clears all MCAN interrupts.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_mcan_clear_interrupts_all ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 read interrupt enable function.
 * @details This function reads the MCAN interrupt enable register and updates
 * the passed mcan interrupt enable struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] ie : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_mcan_read_interrupt_enable ( canfd6_t *ctx, canfd6_mcan_interrupt_enable_t *ie );

/**
 * @brief CAN FD 6 configure interrupt enable function.
 * @details This function configures the MCAN interrupt enable register based on
 * the passed struct. Also enables MCAN interrupts out to the INT1 pin.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] ie : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_mcan_configure_interrupt_enable ( canfd6_t *ctx, canfd6_mcan_interrupt_enable_t *ie );

/**
 * @brief CAN FD 6 dlc to bytes function.
 * @details This function converts the CAN message DLC hex value to the number
 * of bytes it corresponds to.
 * @param[in] input_dlc : DLC value from/to a CAN message struct.
 * @return The number of bytes of data (0-64 bytes).
 * 
 * @note None.
 */
uint8_t canfd6_mcan_dlc_to_bytes ( uint8_t input_dlc );

/**
 * @brief CAN FD 6 txrxesc data byte value function.
 * @details This function converts the MCAN ESC (Element Size) value to number
 * of bytes that it corresponds to.
 * @param[in] input_esc_value : Value from an element size configuration register.
 * @return The number of bytes of data (8-64 bytes).
 * 
 * @note None.
 */
uint8_t canfd6_mcan_txrxesc_data_byte_value ( uint8_t input_esc_value );

/**
 * @brief CAN FD 6 device read version function.
 * @details This function reads the TCAN4550 device version register.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return The value of the device version register.
 * 
 * @note None.
 */
uint16_t canfd6_device_read_version ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 device configure function.
 * @details This function configures the device mode and pin register
 * based on the dev config struct masking out the reserved bits on a write.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] dev_cfg : Struct containing the desired device mode and pin register values.
 * 
 * @note None.
 */
void canfd6_device_configure ( canfd6_t *ctx, canfd6_dev_config_t *dev_cfg );

/**
 * @brief CAN FD 6 device read config function.
 * @details This function reads the device mode and pin register and
 * updates the passed dev cfg struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] dev_cfg : Struct containing the desired device mode and pin register values.
 * 
 * @note None.
 */
void canfd6_device_read_config ( canfd6_t *ctx, canfd6_dev_config_t *dev_cfg );

/**
 * @brief CAN FD 6 device read interrupts function.
 * @details This function reads the device interrupts and updates the device
 * interrupts struct that is passed to the function.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] ir : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_device_read_interrupts ( canfd6_t *ctx, canfd6_device_interrupts_t *ir );

/**
 * @brief CAN FD 6 device clear interrupts function.
 * @details This function will attempt to clear any interrupts that are
 * marked as a '1' in the passed struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] ir : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_device_clear_interrupts ( canfd6_t *ctx, canfd6_device_interrupts_t *ir );

/**
 * @brief CAN FD 6 device clear interrupts all function.
 * @details This function clears all device interrupts.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_device_clear_interrupts_all ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 device clear spierr function.
 * @details This function clears a SPIERR flag that may be set.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_device_clear_spierr ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 device read interrupt enable function.
 * @details This function reads the device interrupt enable register
 * and updates the passed struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[out] ie : Struct containing the interrupt bit fields that will be updated.
 * 
 * @note None.
 */
void canfd6_device_read_interrupt_enable ( canfd6_t *ctx, canfd6_device_interrupt_enable_t *ie );

/**
 * @brief CAN FD 6 device configure ie function.
 * @details This function configures the device interrupt enable
 * register based on the passed struct.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] ie : Struct containing the desired enabled interrupt bits.
 * 
 * @note None.
 */
void canfd6_device_configure_ie ( canfd6_t *ctx, canfd6_device_interrupt_enable_t *ie );

/**
 * @brief CAN FD 6 device set mode function.
 * @details This function sets the TCAN4550 device mode based on
 * the input mode define enum.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] mode_define : Mode define enum.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_device_set_mode ( canfd6_t *ctx, canfd6_device_mode_enum_t mode_define );

/**
 * @brief CAN FD 6 device read mode function.
 * @details This function reads the TCAN4550 device mode and
 * returns a mode define enum.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return Mode define enum.
 * 
 * @note None.
 */
canfd6_device_mode_enum_t canfd6_device_read_mode ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 device enable testmode function.
 * @details This function sets the TCAN4550 device test mode
 * based on the input mode define enum.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] mode_define : Mode define enum.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_device_enable_testmode ( canfd6_t *ctx, canfd6_device_test_mode_enum_t mode_define );

/**
 * @brief CAN FD 6 device disable testmode function.
 * @details This function disables the TCAN4550 device test mode.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_device_disable_testmode ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 device read testmode function.
 * @details This function reads the TCAN4550 device test mode.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return Device test mode enum.
 * 
 * @note None.
 */
canfd6_device_test_mode_enum_t canfd6_device_read_testmode ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 wdt configure function.
 * @details This function configures the watchdog.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @param[in] wdt_timeout : WDT timer enum of different times
 * for the watch dog window.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd6_wdt_configure ( canfd6_t *ctx, canfd6_wdt_timer_enum_t wdt_timeout );

/**
 * @brief CAN FD 6 wdt read function.
 * @details This function reads the watchdog configuration.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * @return WDT timer enum of the currently configured time window.
 * 
 * @note None.
 */
canfd6_wdt_timer_enum_t canfd6_wdt_read ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 wdt enable function.
 * @details This function enables the watchdog timer.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_wdt_enable ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 wdt disable function.
 * @details This function disables the watchdog timer.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_wdt_disable ( canfd6_t *ctx );

/**
 * @brief CAN FD 6 wdt reset function.
 * @details This function resets the watchdog timer.
 * @param[out] ctx : Click context object.
 * See #canfd6_t object definition for detailed explanation.
 * 
 * @note None.
 */
void canfd6_wdt_reset ( canfd6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CANFD6_H

/*! @} */ // canfd6

// ------------------------------------------------------------------------ END

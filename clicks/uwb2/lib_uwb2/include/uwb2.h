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
 * @file uwb2.h
 * @brief This file contains API for UWB 2 Click Driver.
 */

#ifndef UWB2_H
#define UWB2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup uwb2 UWB 2 Click Driver
 * @brief API for configuring and manipulating UWB 2 Click driver.
 * @{
 */

/**
 * @defgroup uwb2_reg UWB 2 Registers List
 * @brief List of registers of UWB 2 Click driver.
 */

/**
 * @addtogroup uwb2_reg
 * @{
 */

/**
 * @brief UWB 2 fast commands list.
 * @details Specified fast commands list of UWB 2 Click driver.
 */
#define UWB2_CMD_TXRXOFF                        0x00
#define UWB2_CMD_TX                             0x01
#define UWB2_CMD_RX                             0x02
#define UWB2_CMD_DTX                            0x03
#define UWB2_CMD_DRX                            0x04
#define UWB2_CMD_DTX_TS                         0x05
#define UWB2_CMD_DRX_TS                         0x06
#define UWB2_CMD_DTX_RS                         0x07
#define UWB2_CMD_DRX_RS                         0x08
#define UWB2_CMD_DTX_REF                        0x09
#define UWB2_CMD_DRX_REF                        0x0A
#define UWB2_CMD_CCA_TX                         0x0B
#define UWB2_CMD_TX_W4R                         0x0C
#define UWB2_CMD_DTX_W4R                        0x0D
#define UWB2_CMD_DTX_TS_W4R                     0x0E
#define UWB2_CMD_DTX_RS_W4R                     0x0F
#define UWB2_CMD_DTX_REF_W4R                    0x10
#define UWB2_CMD_CCA_TX_W4R                     0x11
#define UWB2_CMD_CLR_IRQS                       0x12
#define UWB2_CMD_DB_TOGGLE                      0x13

/**
 * @brief UWB 2 registers list.
 * @details Specified registers list of UWB 2 Click driver.
 * @note Register format is 0xBBAA, where BB represents the base address byte and
 * AA represents the sub address i.e. the address offset. 
 */
#define UWB2_REG_DEV_ID                         0x0000u
#define UWB2_REG_EUI_64                         0x0004u
#define UWB2_REG_PANADR                         0x000Cu
#define UWB2_REG_SYS_CFG                        0x0010u
#define UWB2_REG_FF_CFG                         0x0014u
#define UWB2_REG_SPI_RD_CRC                     0x0018u
#define UWB2_REG_SYS_TIME                       0x001Cu
#define UWB2_REG_TX_FCTRL_LO                    0x0024u
#define UWB2_REG_TX_FCTRL_HI                    0x0028u
#define UWB2_REG_DX_TIME                        0x002Cu
#define UWB2_REG_DREF_TIME                      0x0030u
#define UWB2_REG_RX_FWTO                        0x0034u
#define UWB2_REG_SYS_CTRL                       0x0038u
#define UWB2_REG_SYS_ENABLE_LO                  0x003Cu
#define UWB2_REG_SYS_ENABLE_HI                  0x0040u
#define UWB2_REG_SYS_STATUS_LO                  0x0044u
#define UWB2_REG_SYS_STATUS_HI                  0x0048u
#define UWB2_REG_RX_FINFO                       0x004Cu
#define UWB2_REG_RX_TIME                        0x0064u
#define UWB2_REG_TX_TIME                        0x0074u
#define UWB2_REG_TX_RAWST                       0x0100u
#define UWB2_REG_TX_ANTD                        0x0104u
#define UWB2_REG_ACK_RESP_T                     0x0108u
#define UWB2_REG_TX_POWER                       0x010Cu
#define UWB2_REG_CHAN_CTRL                      0x0114u
#define UWB2_REG_LE_PEND_01                     0x0118u
#define UWB2_REG_LE_PEND_23                     0x011Cu
#define UWB2_REG_SPI_COLLISION                  0x0120u
#define UWB2_REG_RDB_STATUS                     0x0124u
#define UWB2_REG_RDB_DIAG                       0x0128u
#define UWB2_REG_AES_CFG                        0x0130u
#define UWB2_REG_AES_IV0                        0x0134u
#define UWB2_REG_AES_IV1                        0x0138u
#define UWB2_REG_AES_IV2                        0x013Cu
#define UWB2_REG_AES_IV3                        0x0140u
#define UWB2_REG_DMA_CFG                        0x0144u
#define UWB2_REG_AES_START                      0x014Cu
#define UWB2_REG_AES_STS                        0x0150u
#define UWB2_REG_AES_KEY                        0x0154u
#define UWB2_REG_STS_CFG                        0x0200u
#define UWB2_REG_STS_CTRL                       0x0204u
#define UWB2_REG_STS_STS                        0x0208u
#define UWB2_REG_STS_KEY                        0x020Cu
#define UWB2_REG_STS_IV                         0x021Cu
#define UWB2_REG_DGC_CFG                        0x0318u
#define UWB2_REG_DGC_CFG_0                      0x031Cu
#define UWB2_REG_DGC_CFG_1                      0x0320u
#define UWB2_REG_DGC_LUT_0                      0x0338u
#define UWB2_REG_DGC_LUT_1                      0x033Cu
#define UWB2_REG_DGC_LUT_2                      0x0340u
#define UWB2_REG_DGC_LUT_3                      0x0344u
#define UWB2_REG_DGC_LUT_4                      0x0348u
#define UWB2_REG_DGC_LUT_5                      0x034Cu
#define UWB2_REG_DGC_LUT_6                      0x0350u
#define UWB2_REG_DGC_DBG                        0x0360u
#define UWB2_REG_EC_CTRL                        0x0400u
#define UWB2_REG_RX_CAL                         0x040Cu
#define UWB2_REG_RX_CAL_RESI                    0x0414u
#define UWB2_REG_RX_CAL_RESQ                    0x041Cu
#define UWB2_REG_RX_CAL_STS                     0x0420u
#define UWB2_REG_GPIO_MODE                      0x0500u
#define UWB2_REG_GPIO_PULL_EN                   0x0504u
#define UWB2_REG_GPIO_DIR                       0x0508u
#define UWB2_REG_GPIO_OUT                       0x050Cu
#define UWB2_REG_GPIO_IRQE                      0x0510u
#define UWB2_REG_GPIO_ISTS                      0x0514u
#define UWB2_REG_GPIO_ISEN                      0x0518u
#define UWB2_REG_GPIO_IMODE                     0x051Cu
#define UWB2_REG_GPIO_IBES                      0x0520u
#define UWB2_REG_GPIO_ICLR                      0x0524u
#define UWB2_REG_GPIO_IDBE                      0x0528u
#define UWB2_REG_GPIO_RAW                       0x052Cu
#define UWB2_REG_DTUNE_0                        0x0600u
#define UWB2_REG_RX_SFD_TOC                     0x0602u
#define UWB2_REG_PRE_TOC                        0x0604u
#define UWB2_REG_DTUNE_3                        0x060Cu
#define UWB2_REG_DTUNE_4                        0x0610u
#define UWB2_REG_DTUNE_5                        0x0614u
#define UWB2_REG_DRX_CAR_INT                    0x0629u
#define UWB2_REG_RF_ENABLE                      0x0700u
#define UWB2_REG_RF_CTRL_MASK                   0x0704u
#define UWB2_REG_RF_SWITCH                      0x0714u
#define UWB2_REG_RF_TX_CTRL_1                   0x071Au
#define UWB2_REG_RF_TX_CTRL_2                   0x071Cu
#define UWB2_REG_TX_TEST                        0x0728u
#define UWB2_REG_SAR_TEST                       0x0734u
#define UWB2_REG_LDO_TUNE_LO                    0x0740u
#define UWB2_REG_LDO_TUNE_HI                    0x0744u
#define UWB2_REG_LDO_CTRL                       0x0748u
#define UWB2_REG_LDO_RLOAD                      0x0751u
#define UWB2_REG_SAR_CTRL                       0x0800u
#define UWB2_REG_SAR_STATUS                     0x0804u
#define UWB2_REG_SAR_READING                    0x0808u
#define UWB2_REG_SAR_WAKE_RD                    0x080Cu
#define UWB2_REG_PGC_CTRL                       0x0810u
#define UWB2_REG_PGC_STATUS                     0x0814u
#define UWB2_REG_PG_TEST                        0x0818u
#define UWB2_REG_PG_CAL_TARGET                  0x081Cu
#define UWB2_REG_PLL_CFG                        0x0900u
#define UWB2_REG_PLL_CC                         0x0904u
#define UWB2_REG_PLL_CAL                        0x0908u
#define UWB2_REG_XTAL                           0x0914u
#define UWB2_REG_AON_DIG_CFG                    0x0A00u
#define UWB2_REG_AON_CTRL                       0x0A04u
#define UWB2_REG_AON_RDATA                      0x0A08u
#define UWB2_REG_AON_ADDR                       0x0A0Cu
#define UWB2_REG_AON_WDATA                      0x0A10u
#define UWB2_REG_AON_CFG                        0x0A14u
#define UWB2_REG_OTP_WDATA                      0x0B00u
#define UWB2_REG_OTP_ADDR                       0x0B04u
#define UWB2_REG_OTP_CFG                        0x0B08u
#define UWB2_REG_OTP_STAT                       0x0B0Cu
#define UWB2_REG_OTP_RDATA                      0x0B10u
#define UWB2_REG_OTP_SRDATA                     0x0B14u
#define UWB2_REG_IP_TS                          0x0C00u
#define UWB2_REG_STS_TS                         0x0C08u
#define UWB2_REG_STS1_TS                        0x0C10u
#define UWB2_REG_TDOA                           0x0C18u
#define UWB2_REG_PDOA                           0x0C1Eu
#define UWB2_REG_CIA_DIAG_0                     0x0C20u
#define UWB2_REG_IP_DIAG_0                      0x0C28u
#define UWB2_REG_IP_DIAG_1                      0x0C2Cu
#define UWB2_REG_IP_DIAG_2                      0x0C30u
#define UWB2_REG_IP_DIAG_3                      0x0C34u
#define UWB2_REG_IP_DIAG_4                      0x0C38u
#define UWB2_REG_IP_DIAG_8                      0x0C48u
#define UWB2_REG_IP_DIAG_12                     0x0C58u
#define UWB2_REG_STS_DIAG_0                     0x0C5Cu
#define UWB2_REG_STS_DIAG_1                     0x0C60u
#define UWB2_REG_STS_DIAG_2                     0x0C64u
#define UWB2_REG_STS_DIAG_3                     0x0C68u
#define UWB2_REG_STS_DIAG_4                     0x0D00u
#define UWB2_REG_STS_DIAG_8                     0x0D10u
#define UWB2_REG_STS_DIAG_12                    0x0D20u
#define UWB2_REG_STS1_DIAG_0                    0x0D38u
#define UWB2_REG_STS1_DIAG_1                    0x0D3Cu
#define UWB2_REG_STS1_DIAG_2                    0x0D40u
#define UWB2_REG_STS1_DIAG_3                    0x0D44u
#define UWB2_REG_STS1_DIAG_4                    0x0D48u
#define UWB2_REG_STS1_DIAG_8                    0x0D58u
#define UWB2_REG_STS1_DIAG_12                   0x0D68u
#define UWB2_REG_CIA_CONF                       0x0E00u
#define UWB2_REG_FP_CONF                        0x0E04u
#define UWB2_REG_IP_CONF                        0x0E0Cu
#define UWB2_REG_STS_CONF_0                     0x0E12u
#define UWB2_REG_STS_CONF_1                     0x0E16u
#define UWB2_REG_CIA_ADJUST                     0x0E1Au
#define UWB2_REG_EVC_CTRL                       0x0F00u
#define UWB2_REG_EVC_PHE                        0x0F04u
#define UWB2_REG_EVC_RSE                        0x0F06u
#define UWB2_REG_EVC_FCG                        0x0F08u
#define UWB2_REG_EVC_FCE                        0x0F0Au
#define UWB2_REG_EVC_FFR                        0x0F0Cu
#define UWB2_REG_EVC_OVR                        0x0F0Eu
#define UWB2_REG_EVC_STO                        0x0F10u
#define UWB2_REG_EVC_PTO                        0x0F12u
#define UWB2_REG_EVC_FWTO                       0x0F14u
#define UWB2_REG_EVC_TXFS                       0x0F16u
#define UWB2_REG_EVC_HPW                        0x0F18u
#define UWB2_REG_EVC_SWCE                       0x0F1Au
#define UWB2_REG_EVC_RES1                       0x0F1Cu
#define UWB2_REG_DIAG_TMC                       0x0F24u
#define UWB2_REG_EVC_CPQE                       0x0F28u
#define UWB2_REG_EVC_VWARN                      0x0F2Au
#define UWB2_REG_SPI_MODE                       0x0F2Cu
#define UWB2_REG_SYS_STATE                      0x0F30u
#define UWB2_REG_FCMD_STAT                      0x0F3Cu
#define UWB2_REG_CTR_DBG                        0x0F48u
#define UWB2_REG_SPICRCINIT                     0x0F4Cu
#define UWB2_REG_SOFT_RST                       0x1100u
#define UWB2_REG_CLK_CTRL                       0x1104u
#define UWB2_REG_SEQ_CTRL                       0x1108u
#define UWB2_REG_TXFSEQ                         0x1112u
#define UWB2_REG_LED_CTRL                       0x1116u
#define UWB2_REG_RX_SNIFF                       0x111Au
#define UWB2_REG_BIAS_CTRL                      0x111Fu
#define UWB2_REG_RX_BUFFER_0                    0x1200u
#define UWB2_REG_RX_BUFFER_1                    0x1300u
#define UWB2_REG_TX_BUFFER                      0x1400u
#define UWB2_REG_ACC_MEM                        0x1500u
#define UWB2_REG_SCRATCH_RAM                    0x1600u
#define UWB2_REG_AES_KEY_1                      0x1700u
#define UWB2_REG_AES_KEY_2                      0x1710u
#define UWB2_REG_AES_KEY_3                      0x1720u
#define UWB2_REG_AES_KEY_4                      0x1730u
#define UWB2_REG_AES_KEY_5                      0x1740u
#define UWB2_REG_AES_KEY_6                      0x1750u
#define UWB2_REG_AES_KEY_7                      0x1760u
#define UWB2_REG_AES_KEY_8                      0x1770u
#define UWB2_REG_SET1_SET2                      0x1800u
#define UWB2_REG_INDIRECT_PTR_A                 0x1D00u
#define UWB2_REG_INDIRECT_PTR_B                 0x1E00u
#define UWB2_REG_FINT_STAT                      0x1F00u
#define UWB2_REG_PTR_ADDR_A                     0x1F04u
#define UWB2_REG_PTR_OFFSET_A                   0x1F08u
#define UWB2_REG_PTR_ADDR_B                     0x1F0Cu
#define UWB2_REG_PTR_OFFSET_B                   0x1F10u

/**
 * @brief UWB 2 OTP memory address list.
 * @details Specified OTP memory address list of UWB 2 Click driver.
 */
#define UWB2_OTP_ADR_EUID_LO                    0x0000u
#define UWB2_OTP_ADR_EUID_HI                    0x0001u
#define UWB2_OTP_ADR_AEUID_LO                   0x0002u
#define UWB2_OTP_ADR_AEUID_HI                   0x0003u
#define UWB2_OTP_ADR_LDOTUNE_LO                 0x0004u
#define UWB2_OTP_ADR_LDOTUNE_HI                 0x0005u
#define UWB2_OTP_ADR_PART_ID                    0x0006u
#define UWB2_OTP_ADR_LOT_ID                     0x0007u
#define UWB2_OTP_ADR_VBAT                       0x0008u
#define UWB2_OTP_ADR_TEMP                       0x0009u
#define UWB2_OTP_ADR_BIASTUNE                   0x000Au
#define UWB2_OTP_ADR_ANTENNA_DELAY              0x000Bu
#define UWB2_OTP_ADR_AOA_ISO                    0x000Cu
#define UWB2_OTP_ADR_WS_LOT_ID_LO               0x000Du
#define UWB2_OTP_ADR_WS_LOT_ID_HI               0x000Eu
#define UWB2_OTP_ADR_WS_LOC                     0x000Fu
#define UWB2_OTP_ADR_XTAL_TRIM                  0x001Eu
#define UWB2_OTP_ADR_OTP_REVISION               0x001Fu
#define UWB2_OTP_ADR_DGC_TUNE                   0x0020u
#define UWB2_OTP_ADR_PLL_LOCK_CODE              0x0035u
#define UWB2_OTP_ADR_AES_KEY_START              0x0078u
#define UWB2_OTP_ADR_AES_KEY_END                0x007Fu

/*! @} */ // uwb2_reg

/**
 * @defgroup uwb2_set UWB 2 Registers Settings
 * @brief Settings for registers of UWB 2 Click driver.
 */

/**
 * @addtogroup uwb2_set
 * @{
 */

/**
 * @brief UWB 2 SYS_CFG register settings.
 * @details Specified SYS_CFG register settings of UWB 2 Click driver.
 */
#define UWB2_SYS_CFG_FAST_AAT_MASK              0x00040000ul
#define UWB2_SYS_CFG_PDOA_MODE_MASK             0x00030000ul
#define UWB2_SYS_CFG_CP_SDC_SPC_MASK            0x0000B000ul
#define UWB2_SYS_CFG_AUTO_ACK_MASK              0x00000800ul
#define UWB2_SYS_CFG_RXAUTR_MASK                0x00000400ul
#define UWB2_SYS_CFG_RXWTOE_MASK                0x00000200ul
#define UWB2_SYS_CFG_CIA_STS_MASK               0x00000100ul
#define UWB2_SYS_CFG_CIA_IPATOV_MASK            0x00000080ul
#define UWB2_SYS_CFG_SPI_CRCEN_MASK             0x00000040ul
#define UWB2_SYS_CFG_PHR_6M8_MASK               0x00000020ul
#define UWB2_SYS_CFG_PHR_MODE_MASK              0x00000010ul
#define UWB2_SYS_CFG_DIS_DRXB_MASK              0x00000008ul
#define UWB2_SYS_CFG_DIS_FCE_MASK               0x00000004ul
#define UWB2_SYS_CFG_DIS_FCS_TX_MASK            0x00000002ul
#define UWB2_SYS_CFG_FFEN_MASK                  0x00000001ul

/**
 * @brief UWB 2 TX_FCTRL_LO register settings.
 * @details Specified TX_FCTRL_LO register settings of UWB 2 Click driver.
 */
#define UWB2_TX_FCTRL_LO_TXB_OFFSET_MASK        0x03FF0000ul
#define UWB2_TX_FCTRL_LO_TXPSR_MASK             0x0000F000ul
#define UWB2_TX_FCTRL_LO_TR_MASK                0x00000800ul
#define UWB2_TX_FCTRL_LO_TX_BR_MASK             0x00000400ul
#define UWB2_TX_FCTRL_LO_TXFLEN_MASK            0x000003FFul

/**
 * @brief UWB 2 TX_FCTRL_HI register settings.
 * @details Specified TX_FCTRL_HI register settings of UWB 2 Click driver.
 */
#define UWB2_TX_FCTRL_HI_FINE_PLEN_MASK         0xFF00u

/**
 * @brief UWB 2 SYS_ENABLE_LO register settings.
 * @details Specified SYS_ENABLE_LO register settings of UWB 2 Click driver.
 */
#define UWB2_SYS_ENABLE_LO_ARFE_EN_MASK         0x20000000ul
#define UWB2_SYS_ENABLE_LO_CPERR_EN_MASK        0x10000000ul
#define UWB2_SYS_ENABLE_LO_HPDWARN_EN_MASK      0x08000000ul
#define UWB2_SYS_ENABLE_LO_RXSTO_EN_MASK        0x04000000ul
#define UWB2_SYS_ENABLE_LO_PLLHILO_EN_MASK      0x02000000ul
#define UWB2_SYS_ENABLE_LO_RCINIT_EN_MASK       0x01000000ul
#define UWB2_SYS_ENABLE_LO_SPIRDY_EN_MASK       0x00800000ul
#define UWB2_SYS_ENABLE_LO_RXPTO_EN_MASK        0x00200000ul
#define UWB2_SYS_ENABLE_LO_RXOVRR_EN_MASK       0x00100000ul
#define UWB2_SYS_ENABLE_LO_VWARN_EN_MASK        0x00080000ul
#define UWB2_SYS_ENABLE_LO_CIAERR_EN_MASK       0x00040000ul
#define UWB2_SYS_ENABLE_LO_RXFTO_EN_MASK        0x00020000ul
#define UWB2_SYS_ENABLE_LO_RXFSL_EN_MASK        0x00010000ul
#define UWB2_SYS_ENABLE_LO_RXFCE_EN_MASK        0x00008000ul
#define UWB2_SYS_ENABLE_LO_RXFCG_EN_MASK        0x00004000ul
#define UWB2_SYS_ENABLE_LO_RXFR_EN_MASK         0x00002000ul
#define UWB2_SYS_ENABLE_LO_RXPHE_EN_MASK        0x00001000ul
#define UWB2_SYS_ENABLE_LO_RXPHD_EN_MASK        0x00000800ul
#define UWB2_SYS_ENABLE_LO_CIADONE_EN_MASK      0x00000400ul
#define UWB2_SYS_ENABLE_LO_RXSFDD_EN_MASK       0x00000200ul
#define UWB2_SYS_ENABLE_LO_RXPRD_EN_MASK        0x00000100ul
#define UWB2_SYS_ENABLE_LO_TXFRS_EN_MASK        0x00000080ul
#define UWB2_SYS_ENABLE_LO_TXPHS_EN_MASK        0x00000040ul
#define UWB2_SYS_ENABLE_LO_TXPRS_EN_MASK        0x00000020ul
#define UWB2_SYS_ENABLE_LO_TXFRB_EN_MASK        0x00000010ul
#define UWB2_SYS_ENABLE_LO_AAT_EN_MASK          0x00000008ul
#define UWB2_SYS_ENABLE_LO_SPICRCE_EN_MASK      0x00000004ul
#define UWB2_SYS_ENABLE_LO_CPLOCK_EN_MASK       0x00000002ul

/**
 * @brief UWB 2 SYS_STATUS_LO register settings.
 * @details Specified SYS_STATUS_LO register settings of UWB 2 Click driver.
 */
#define UWB2_SYS_STATUS_LO_ARFE_MASK            0x20000000ul
#define UWB2_SYS_STATUS_LO_CPERR_MASK           0x10000000ul
#define UWB2_SYS_STATUS_LO_HPDWARN_MASK         0x08000000ul
#define UWB2_SYS_STATUS_LO_RXSTO_MASK           0x04000000ul
#define UWB2_SYS_STATUS_LO_PLLHILO_MASK         0x02000000ul
#define UWB2_SYS_STATUS_LO_RCINIT_MASK          0x01000000ul
#define UWB2_SYS_STATUS_LO_SPIRDY_MASK          0x00800000ul
#define UWB2_SYS_STATUS_LO_RXPTO_MASK           0x00200000ul
#define UWB2_SYS_STATUS_LO_RXOVRR_MASK          0x00100000ul
#define UWB2_SYS_STATUS_LO_VWARN_MASK           0x00080000ul
#define UWB2_SYS_STATUS_LO_CIAERR_MASK          0x00040000ul
#define UWB2_SYS_STATUS_LO_RXFTO_MASK           0x00020000ul
#define UWB2_SYS_STATUS_LO_RXFSL_MASK           0x00010000ul
#define UWB2_SYS_STATUS_LO_RXFCE_MASK           0x00008000ul
#define UWB2_SYS_STATUS_LO_RXFCG_MASK           0x00004000ul
#define UWB2_SYS_STATUS_LO_RXFR_MASK            0x00002000ul
#define UWB2_SYS_STATUS_LO_RXPHE_MASK           0x00001000ul
#define UWB2_SYS_STATUS_LO_RXPHD_MASK           0x00000800ul
#define UWB2_SYS_STATUS_LO_CIADONE_MASK         0x00000400ul
#define UWB2_SYS_STATUS_LO_RXSFDD_MASK          0x00000200ul
#define UWB2_SYS_STATUS_LO_RXPRD_MASK           0x00000100ul
#define UWB2_SYS_STATUS_LO_TXFRS_MASK           0x00000080ul
#define UWB2_SYS_STATUS_LO_TXPHS_MASK           0x00000040ul
#define UWB2_SYS_STATUS_LO_TXPRS_MASK           0x00000020ul
#define UWB2_SYS_STATUS_LO_TXFRB_MASK           0x00000010ul
#define UWB2_SYS_STATUS_LO_AAT_MASK             0x00000008ul
#define UWB2_SYS_STATUS_LO_SPICRCE_MASK         0x00000004ul
#define UWB2_SYS_STATUS_LO_CPLOCK_MASK          0x00000002ul
#define UWB2_SYS_STATUS_LO_IRQS_MASK            0x00000001ul

/**
 * @brief UWB 2 SYS_STATUS_HI register settings.
 * @details Specified SYS_STATUS_HI register settings of UWB 2 Click driver.
 */
#define UWB2_SYS_STATUS_HI_CCA_FAIL_MASK        0x1000u
#define UWB2_SYS_STATUS_HI_SPIERR_MASK          0x0800u
#define UWB2_SYS_STATUS_HI_SPI_UNF_MASK         0x0400u
#define UWB2_SYS_STATUS_HI_SPI_OVF_MASK         0x0200u
#define UWB2_SYS_STATUS_HI_CMD_ERR_MASK         0x0100u
#define UWB2_SYS_STATUS_HI_AER_ERR_MASK         0x0080u
#define UWB2_SYS_STATUS_HI_AES_DONE_MASK        0x0040u
#define UWB2_SYS_STATUS_HI_GPIOIRQ_MASK         0x0020u
#define UWB2_SYS_STATUS_HI_VT_DET_MASK          0x0010u
#define UWB2_SYS_STATUS_HI_RXPREJ_MASK          0x0002u

/**
 * @brief UWB 2 CHAN_CTRL register settings.
 * @details Specified CHAN_CTRL register settings of UWB 2 Click driver.
 */
#define UWB2_CHAN_CTRL_RX_PCODE_MASK            0x1F00u
#define UWB2_CHAN_CTRL_TX_PCODE_MASK            0x00F8u
#define UWB2_CHAN_CTRL_SFD_TYPE_IEEE_4A         0x0000u
#define UWB2_CHAN_CTRL_SFD_TYPE_DW_8            0x0002u
#define UWB2_CHAN_CTRL_SFD_TYPE_DW_16           0x0004u
#define UWB2_CHAN_CTRL_SFD_TYPE_IEEE_4Z         0x0006u
#define UWB2_CHAN_CTRL_SFD_TYPE_MASK            0x0006u
#define UWB2_CHAN_CTRL_RF_CHAN_MASK             0x0001u

/**
 * @brief UWB 2 RX_FINFO register settings.
 * @details Specified RX_FINFO register settings of UWB 2 Click driver.
 */
#define UWB2_RX_FINFO_RXPACC_MASK               0xFFF00000ul
#define UWB2_RX_FINFO_RXPSR_MASK                0x000C0000ul
#define UWB2_RX_FINFO_RXPRF_MASK                0x00030000ul
#define UWB2_RX_FINFO_RNG_MASK                  0x00008000ul
#define UWB2_RX_FINFO_RXBR_MASK                 0x00002000ul
#define UWB2_RX_FINFO_RXNSPL_MASK               0x00001800ul
#define UWB2_RX_FINFO_RXFLEN_MASK               0x000003FFul

/**
 * @brief UWB 2 STS_CFG register settings.
 * @details Specified STS_CFG register settings of UWB 2 Click driver.
 */
#define UWB2_STS_CFG_CPS_LEN_64                 0x0007u
#define UWB2_STS_CFG_CPS_LEN_MASK               0x00FFu
#define UWB2_STS_CFG_RESERVED_BITS              0x1000u

/**
 * @brief UWB 2 RX_TUNE register settings.
 * @details Specified RX_TUNE register settings of UWB 2 Click driver.
 */
#define UWB2_RX_TUNE_DGC_CFG_THR_64_OPTIMISED   0x6400u
#define UWB2_RX_TUNE_DGC_CFG_THR_64_MASK        0x7E00u
#define UWB2_RX_TUNE_DGC_CFG_RX_TUNE_EN_MASK    0x0001u
#define UWB2_RX_TUNE_DGC_CFG_RESERVED_BITS      0x80F4u
#define UWB2_RX_TUNE_DGC_CFG_0                  0x10000240ul
#define UWB2_RX_TUNE_DGC_CFG_1                  0x1B6DA489ul
#define UWB2_RX_TUNE_DGC_LUT_0_CH5              0x0001C0FDul
#define UWB2_RX_TUNE_DGC_LUT_0_CH9              0x0002A8FEul
#define UWB2_RX_TUNE_DGC_LUT_1_CH5              0x0001C43Eul
#define UWB2_RX_TUNE_DGC_LUT_1_CH9              0x0002AC36ul
#define UWB2_RX_TUNE_DGC_LUT_2_CH5              0x0001C6BEul
#define UWB2_RX_TUNE_DGC_LUT_2_CH9              0x0002A5FEul
#define UWB2_RX_TUNE_DGC_LUT_3_CH5              0x0001C77Eul
#define UWB2_RX_TUNE_DGC_LUT_3_CH9              0x0002AF3Eul
#define UWB2_RX_TUNE_DGC_LUT_4_CH5              0x0001C736ul
#define UWB2_RX_TUNE_DGC_LUT_4_CH9              0x0002AF7Dul
#define UWB2_RX_TUNE_DGC_LUT_5_CH5              0x0001CFB5ul
#define UWB2_RX_TUNE_DGC_LUT_5_CH9              0x0002AFB5ul
#define UWB2_RX_TUNE_DGC_LUT_6_CH5              0x0001CFF5ul
#define UWB2_RX_TUNE_DGC_LUT_6_CH9              0x0002AFB5ul

/**
 * @brief UWB 2 RX_CAL register settings.
 * @details Specified RX_CAL register settings of UWB 2 Click driver.
 */
#define UWB2_RX_CAL_COMP_DLY_EN_READ            0x00010000ul
#define UWB2_RX_CAL_COMP_DLY_OPTIMAL            0x00020000ul
#define UWB2_RX_CAL_COMP_DLY_MASK               0x000F0000ul
#define UWB2_RX_CAL_CAL_EN_MASK                 0x00000010ul
#define UWB2_RX_CAL_CAL_MODE_NORMAL             0x00000000ul
#define UWB2_RX_CAL_CAL_MODE_CALIBRATION        0x00000001ul
#define UWB2_RX_CAL_CAL_MODE_MASK               0x00000003ul

/**
 * @brief UWB 2 RX_CAL_STS register settings.
 * @details Specified RX_CAL_STS register settings of UWB 2 Click driver.
 */
#define UWB2_RX_CAL_STS_CALIBRATION_DONE        0x01

/**
 * @brief UWB 2 RX_CAL_RESI register settings.
 * @details Specified RX_CAL_RESI register settings of UWB 2 Click driver.
 */
#define UWB2_RX_CAL_RESI_CALIBRATION_FAILED     0x1FFFFFFFul

/**
 * @brief UWB 2 RX_CAL_RESQ register settings.
 * @details Specified RX_CAL_RESQ register settings of UWB 2 Click driver.
 */
#define UWB2_RX_CAL_RESQ_CALIBRATION_FAILED     0x1FFFFFFFul

/**
 * @brief UWB 2 GPIO_MODE register settings.
 * @details Specified GPIO_MODE register settings of UWB 2 Click driver.
 */
#define UWB2_GPIO_MODE_MSGP8_GPIO8              0x01000000ul
#define UWB2_GPIO_MODE_MSGP8_IRQ                0x00000000ul
#define UWB2_GPIO_MODE_MSGP8_MASK               0x07000000ul
#define UWB2_GPIO_MODE_MSGP7_GPIO7              0x00200000ul
#define UWB2_GPIO_MODE_MSGP7_SYNC               0x00000000ul
#define UWB2_GPIO_MODE_MSGP7_MASK               0x00E00000ul
#define UWB2_GPIO_MODE_MSGP6_EXTRXE             0x00040000ul
#define UWB2_GPIO_MODE_MSGP6_GPIO6              0x00000000ul
#define UWB2_GPIO_MODE_MSGP6_MASK               0x001C0000ul
#define UWB2_GPIO_MODE_MSGP5_EXTTXE             0x00008000ul
#define UWB2_GPIO_MODE_MSGP5_GPIO5              0x00000000ul
#define UWB2_GPIO_MODE_MSGP5_MASK               0x00038000ul
#define UWB2_GPIO_MODE_MSGP4_IRQ                0x00002000ul
#define UWB2_GPIO_MODE_MSGP4_EXTPA              0x00001000ul
#define UWB2_GPIO_MODE_MSGP4_GPIO4              0x00000000ul
#define UWB2_GPIO_MODE_MSGP4_MASK               0x00007000ul
#define UWB2_GPIO_MODE_MSGP3_PDOA_SW_3          0x00000400ul
#define UWB2_GPIO_MODE_MSGP3_TXLED              0x00000200ul
#define UWB2_GPIO_MODE_MSGP3_GPIO3              0x00000000ul
#define UWB2_GPIO_MODE_MSGP3_MASK               0x00000E00ul
#define UWB2_GPIO_MODE_MSGP2_PDOA_SW_2          0x00000080ul
#define UWB2_GPIO_MODE_MSGP2_RXLED              0x00000040ul
#define UWB2_GPIO_MODE_MSGP2_GPIO2              0x00000000ul
#define UWB2_GPIO_MODE_MSGP2_MASK               0x000001C0ul
#define UWB2_GPIO_MODE_MSGP1_PDOA_SW_1          0x00000010ul
#define UWB2_GPIO_MODE_MSGP1_SFDLED             0x00000008ul
#define UWB2_GPIO_MODE_MSGP1_GPIO1              0x00000000ul
#define UWB2_GPIO_MODE_MSGP1_MASK               0x00000038ul
#define UWB2_GPIO_MODE_MSGP0_PDOA_SW_0          0x00000002ul
#define UWB2_GPIO_MODE_MSGP0_RXOKLED            0x00000001ul
#define UWB2_GPIO_MODE_MSGP0_GPIO0              0x00000000ul
#define UWB2_GPIO_MODE_MSGP0_MASK               0x00000007ul

/**
 * @brief UWB 2 DTUNE_0 register settings.
 * @details Specified DTUNE_0 register settings of UWB 2 Click driver.
 */
#define UWB2_DTUNE_0_DTOB4_MASK                 0x0010u
#define UWB2_DTUNE_0_PAC_MASK                   0x0003u
#define UWB2_DTUNE_0_RESERVED_BITS              0x100Cu

/**
 * @brief UWB 2 RX_SFD_TOC register settings.
 * @details Specified RX_SFD_TOC register settings of UWB 2 Click driver.
 */
#define UWB2_RX_SFD_TOC_DEFAULT                 0x0081u

/**
 * @brief UWB 2 DTUNE_3 register settings.
 * @details Specified DTUNE_3 register settings of UWB 2 Click driver.
 */
#define UWB2_DTUNE_3_DEFAULT                    0xAF5F584Cul
#define UWB2_DTUNE_3_OPTIMAL                    0xAF5F35CCul

/**
 * @brief UWB 2 DTUNE_4 register settings.
 * @details Specified DTUNE_4 register settings of UWB 2 Click driver.
 */
#define UWB2_DTUNE_4_RX_SFD_HLDOFF              0x20000000ul
#define UWB2_DTUNE_4_RX_SFD_HLDOFF_DEFAULT      0x14000000ul
#define UWB2_DTUNE_4_RX_SFD_HLDOFF_MASK         0xFF000000ul

/**
 * @brief UWB 2 RF_TX_CTRL_1 register settings.
 * @details Specified RF_TX_CTRL_1 register settings of UWB 2 Click driver.
 */
#define UWB2_RF_TX_CTRL_1_OPTIMAL               0x0E

/**
 * @brief UWB 2 RF_TX_CTRL_2 register settings.
 * @details Specified RF_TX_CTRL_2 register settings of UWB 2 Click driver.
 */
#define UWB2_RF_TX_CTRL_2_CHANNEL_5             0x1C071134ul
#define UWB2_RF_TX_CTRL_2_CHANNEL_9             0x1C010034ul

/**
 * @brief UWB 2 LDO_CTRL register settings.
 * @details Specified LDO_CTRL register settings of UWB 2 Click driver.
 */
#define UWB2_LDO_CTRL_VDDHVTX_VREF_MASK         0x08000000ul
#define UWB2_LDO_CTRL_VDDTX2_VREF_MASK          0x00400000ul
#define UWB2_LDO_CTRL_VDDTX1_VREF_MASK          0x00200000ul
#define UWB2_LDO_CTRL_VDDHVTX_EN_MASK           0x00000800ul
#define UWB2_LDO_CTRL_VDDIF2_EN_MASK            0x00000100ul
#define UWB2_LDO_CTRL_VDDTX2_EN_MASK            0x00000040ul
#define UWB2_LDO_CTRL_VDDTX1_EN_MASK            0x00000020ul
#define UWB2_LDO_CTRL_VDDPLL_EN_MASK            0x00000010ul
#define UWB2_LDO_CTRL_VDDMS3_EN_MASK            0x00000004ul
#define UWB2_LDO_CTRL_VDDMS2_EN_MASK            0x00000002ul
#define UWB2_LDO_CTRL_VDDMS1_EN_MASK            0x00000001ul

/**
 * @brief UWB 2 LDO_RLOAD register settings.
 * @details Specified LDO_RLOAD register settings of UWB 2 Click driver.
 */
#define UWB2_LDO_RLOAD_OPTIMAL                  0x14

/**
 * @brief UWB 2 PLL_CFG register settings.
 * @details Specified PLL_CFG register settings of UWB 2 Click driver.
 */
#define UWB2_PLL_CFG_CHANNEL_5                  0x1F3Cu
#define UWB2_PLL_CFG_CHANNEL_9                  0x0F3Cu

/**
 * @brief UWB 2 PLL_CAL register settings.
 * @details Specified PLL_CAL register settings of UWB 2 Click driver.
 */
#define UWB2_PLL_CAL_CAL_EN_MASK                0x0100u
#define UWB2_PLL_CAL_PLL_CFG_LD_MASK            0x0030u
#define UWB2_PLL_CAL_USE_OLD_MASK               0x0002u
#define UWB2_PLL_CAL_RESERVED_BITS              0x0001u
#define UWB2_PLL_CAL_OPTIMAL                    0x0081u

/**
 * @brief UWB 2 XTAL register settings.
 * @details Specified XTAL register settings of UWB 2 Click driver.
 */
#define UWB2_XTAL_TRIM_DEFAULT                  0x2E
#define UWB2_XTAL_TRIM_MASK                     0x3F

/**
 * @brief UWB 2 OTP_CFG register settings.
 * @details Specified OTP_CFG register settings of UWB 2 Click driver.
 */
#define UWB2_OTP_CFG_DGC_SEL_MASK               0x2000u
#define UWB2_OTP_CFG_OPS_SEL_LONG               0x0000u
#define UWB2_OTP_CFG_OPS_SEL_SHORT              0x1000u
#define UWB2_OTP_CFG_OPS_SEL_MASK               0x1800u
#define UWB2_OTP_CFG_OPS_KICK_MASK              0x0400u
#define UWB2_OTP_CFG_BIAS_KICK_MASK             0x0100u
#define UWB2_OTP_CFG_LDO_KICK_MASK              0x0080u
#define UWB2_OTP_CFG_DGC_KICK_MASK              0x0040u
#define UWB2_OTP_CFG_OTP_WRITE_MR_MASK          0x0008u
#define UWB2_OTP_CFG_OTP_WRITE_MASK             0x0004u
#define UWB2_OTP_CFG_OTP_READ_MASK              0x0002u
#define UWB2_OTP_CFG_OTP_MAN_MASK               0x0001u

/**
 * @brief UWB 2 STS_CONF_1 register settings.
 * @details Specified STS_CONF_1 register settings of UWB 2 Click driver.
 */
#define UWB2_STS_CONF_1_STS_PGR_EN_MASK         0x80000000ul
#define UWB2_STS_CONF_1_STS_SS_EN_MASK          0x40000000ul
#define UWB2_STS_CONF_1_STS_CQ_EN_MASK          0x20000000ul
#define UWB2_STS_CONF_1_FP_AGREED_EN_MASK       0x10000000ul
#define UWB2_STS_CONF_1_RES_B0_DEFAULT          0x00000094ul
#define UWB2_STS_CONF_1_RES_B0_MASK             0x000000FFul
#define UWB2_STS_CONF_1_RESERVED_BITS           0x003EED00ul

/**
 * @brief UWB 2 DIAG_TMC register settings.
 * @details Specified DIAG_TMC register settings of UWB 2 Click driver.
 */
#define UWB2_DIAG_TMC_CIA_RUN_MASK              0x04000000ul
#define UWB2_DIAG_TMC_CIA_WDEN_MASK             0x01000000ul
#define UWB2_DIAG_TMC_HIRQ_POL_MASK             0x00200000ul
#define UWB2_DIAG_TMC_TX_PSTM_MASK              0x00000010ul

/**
 * @brief UWB 2 SYS_STATE register settings.
 * @details Specified SYS_STATE register settings of UWB 2 Click driver.
 */
#define UWB2_SYS_STATE_PMSC_STATE_WAKEUP        0x00000000ul
#define UWB2_SYS_STATE_PMSC_STATE_IDLE_RC       0x00010000ul
#define UWB2_SYS_STATE_PMSC_STATE_IDLE          0x00030000ul
#define UWB2_SYS_STATE_PMSC_STATE_TX            0x00080000ul
#define UWB2_SYS_STATE_PMSC_STATE_RX            0x00120000ul
#define UWB2_SYS_STATE_PMSC_STATE_MASK          0x001F0000ul
#define UWB2_SYS_STATE_RX_STATE_IDLE            0x00000000ul
#define UWB2_SYS_STATE_RX_STATE_START_ANALOG    0x00000100ul
#define UWB2_SYS_STATE_RX_STATE_RX_RDY          0x00000400ul
#define UWB2_SYS_STATE_RX_STATE_PREAMBLE_FND    0x00000500ul
#define UWB2_SYS_STATE_RX_STATE_PREAMBLE_TO     0x00000600ul
#define UWB2_SYS_STATE_RX_STATE_SFD_FND         0x00000700ul
#define UWB2_SYS_STATE_RX_STATE_CNFG_PHR_RX     0x00000800ul
#define UWB2_SYS_STATE_RX_STATE_PHR_RX_STRT     0x00000900ul
#define UWB2_SYS_STATE_RX_STATE_DATA_RATE_RDY   0x00000A00ul
#define UWB2_SYS_STATE_RX_STATE_DATA_RX_SEQ     0x00000C00ul
#define UWB2_SYS_STATE_RX_STATE_CNFG_DATA_RX    0x00000D00ul
#define UWB2_SYS_STATE_RX_STATE_PHR_NOT_OK      0x00000E00ul
#define UWB2_SYS_STATE_RX_STATE_LAST_SYMBOL     0x00000F00ul
#define UWB2_SYS_STATE_RX_STATE_WAIT_RSD_DONE   0x00001000ul
#define UWB2_SYS_STATE_RX_STATE_RSP_OK          0x00001100ul
#define UWB2_SYS_STATE_RX_STATE_RSP_NOT_OK      0x00001200ul
#define UWB2_SYS_STATE_RX_STATE_MASK            0x00003F00ul
#define UWB2_SYS_STATE_TX_STATE_IDLE            0x00000000ul
#define UWB2_SYS_STATE_TX_STATE_PREAMBLE        0x00000001ul
#define UWB2_SYS_STATE_TX_STATE_SFD             0x00000002ul
#define UWB2_SYS_STATE_TX_STATE_PHR             0x00000003ul
#define UWB2_SYS_STATE_TX_STATE_SDE             0x00000004ul
#define UWB2_SYS_STATE_TX_STATE_DATA            0x00000005ul
#define UWB2_SYS_STATE_TX_STATE_MASK            0x0000000Ful

/**
 * @brief UWB 2 CLK_CTRL register settings.
 * @details Specified CLK_CTRL register settings of UWB 2 Click driver.
 */
#define UWB2_CLK_CTRL_LP_CLK_EN_MASK            0x00800000ul
#define UWB2_CLK_CTRL_GPIO_DRST_N_MASK          0x00080000ul
#define UWB2_CLK_CTRL_GPIO_DCLK_EN_MASK         0x00040000ul
#define UWB2_CLK_CTRL_GPIO_CLK_EN_MASK          0x00010000ul
#define UWB2_CLK_CTRL_ACC_MCLK_EN_MASK          0x00008000ul
#define UWB2_CLK_CTRL_SAR_CLK_EN_MASK           0x00000400ul
#define UWB2_CLK_CTRL_CIA_CLK_EN_MASK           0x00000100ul
#define UWB2_CLK_CTRL_ACC_CLK_EN_MASK           0x00000040ul
#define UWB2_CLK_CTRL_TX_CLK_AUTO               0x00000000ul
#define UWB2_CLK_CTRL_TX_CLK_FORCE              0x00000010ul
#define UWB2_CLK_CTRL_TX_CLK_MASK               0x00000030ul
#define UWB2_CLK_CTRL_RX_CLK_AUTO               0x00000000ul
#define UWB2_CLK_CTRL_RX_CLK_FORCE              0x00000004ul
#define UWB2_CLK_CTRL_RX_CLK_MASK               0x0000000Cul
#define UWB2_CLK_CTRL_SYS_CLK_AUTO              0x00000000ul
#define UWB2_CLK_CTRL_SYS_CLK_FORCE_FC_4        0x00000001ul
#define UWB2_CLK_CTRL_SYS_CLK_FORCE_PLL         0x00000002ul
#define UWB2_CLK_CTRL_SYS_CLK_FORCE_FC          0x00000003ul
#define UWB2_CLK_CTRL_SYS_CLK_MASK              0x00000003ul
#define UWB2_CLK_CTRL_RESERVED_BITS             0xF0300200ul

/**
 * @brief UWB 2 SEQ_CTRL register settings.
 * @details Specified SEQ_CTRL register settings of UWB 2 Click driver.
 */
#define UWB2_SEQ_CTRL_LP_CLK_DIV_MASK           0xFC000000ul
#define UWB2_SEQ_CTRL_FORCE2INIT_MASK           0x00800000ul
#define UWB2_SEQ_CTRL_CIARUNE_MASK              0x00020000ul
#define UWB2_SEQ_CTRL_PLL_SYNC_MASK             0x00008000ul
#define UWB2_SEQ_CTRL_ARXSLP_MASK               0x00001000ul
#define UWB2_SEQ_CTRL_ATXSLP_MASK               0x00000800ul
#define UWB2_SEQ_CTRL_AINIT2IDLE_MASK           0x00000100ul
#define UWB2_SEQ_CTRL_RESERVED_BITS             0x00010638ul

/**
 * @brief UWB 2 LED_CTRL register settings.
 * @details Specified LED_CTRL register settings of UWB 2 Click driver.
 */
#define UWB2_LED_CTRL_FORCE_TRIG_MASK           0x000F0000ul
#define UWB2_LED_CTRL_BLINK_EN_MASK             0x00000100ul
#define UWB2_LED_CTRL_BLINK_TIM_200MS           0x00000010ul
#define UWB2_LED_CTRL_BLINK_TIM_400MS           0x00000020ul
#define UWB2_LED_CTRL_BLINK_TIM_MASK            0x000000FFul

/**
 * @brief UWB 2 BIAS_CTRL register settings.
 * @details Specified BIAS_CTRL register settings of UWB 2 Click driver.
 */
#define UWB2_BIAS_CTRL_MASK                     0x1F

/**
 * @brief UWB 2 chip configuration settings.
 * @details Specified chip configuration settings of UWB 2 Click driver.
 */
#define UWB2_CHANNEL_5                          0x05
#define UWB2_CHANNEL_9                          0x09
#define UWB2_TX_PLEN_32                         0x04
#define UWB2_TX_PLEN_64                         0x01
#define UWB2_TX_PLEN_128                        0x05
#define UWB2_TX_PLEN_256                        0x09
#define UWB2_TX_PLEN_512                        0x0D
#define UWB2_TX_PLEN_1024                       0x02
#define UWB2_TX_PLEN_1536                       0x06
#define UWB2_TX_PLEN_2048                       0x0A
#define UWB2_TX_PLEN_4096                       0x03
#define UWB2_PAC_SIZE_4                         0x03
#define UWB2_PAC_SIZE_8                         0x00
#define UWB2_PAC_SIZE_16                        0x01
#define UWB2_PAC_SIZE_32                        0x02
#define UWB2_TX_CODE_MIN                        0x01
#define UWB2_TX_CODE_9                          0x09
#define UWB2_TX_CODE_24                         0x18
#define UWB2_TX_CODE_MAX                        0x1D
#define UWB2_RX_CODE_MIN                        0x01
#define UWB2_RX_CODE_9                          0x09
#define UWB2_RX_CODE_24                         0x18
#define UWB2_RX_CODE_MAX                        0x1D
#define UWB2_SFD_TYPE_IEEE_4A                   0x00
#define UWB2_SFD_TYPE_DW_8                      0x01
#define UWB2_SFD_TYPE_DW_16                     0x02
#define UWB2_SFD_TYPE_IEEE_4Z                   0x03
#define UWB2_DATA_RATE_850KBS                   0x00
#define UWB2_DATA_RATE_6800KBS                  0x01

/**
 * @brief UWB 2 chip default configuration.
 * @details Specified chip default configuration of UWB 2 Click driver.
 */
#define UWB2_DEFAULT_CHANNEL                    UWB2_CHANNEL_5
#define UWB2_DEFAULT_TX_PLEN                    UWB2_TX_PLEN_128
#define UWB2_DEFAULT_PAC                        UWB2_PAC_SIZE_8
#define UWB2_DEFAULT_TX_CODE                    UWB2_TX_CODE_9
#define UWB2_DEFAULT_RX_CODE                    UWB2_RX_CODE_9
#define UWB2_DEFAULT_SFD_TYPE                   UWB2_SFD_TYPE_DW_8
#define UWB2_DEFAULT_DATA_RATE                  UWB2_DATA_RATE_6800KBS
#define UWB2_DEFAULT_SFD_TO                     ( 128 + 1 + 8 - 8 ) // preamble length + 1 + SFD length - PAC size.

/**
 * @brief UWB 2 RX TX LEDs settings.
 * @details Specified RX TX LEDs settings of UWB 2 Click driver.
 */
#define UWB2_RX_TX_LEDS_DISABLE                 0
#define UWB2_RX_TX_LEDS_ENABLE                  1

/**
 * @brief UWB 2 IC state settings.
 * @details Specified IC state settings of UWB 2 Click driver.
 */
#define UWB2_IC_STATE_INIT                      0
#define UWB2_IC_STATE_IDLE                      1
#define UWB2_IC_STATE_IDLE_RC                   2

/**
 * @brief UWB 2 device ID value.
 * @details Specified device ID value of UWB 2 Click driver.
 */
#define UWB2_DEV_ID                             0xDECA0302ul
#define UWB2_DEV_ID_RIDTAG_MASK                 0xFFFF0000ul
#define UWB2_DEV_ID_MODEL_MASK                  0x0000FF00ul
#define UWB2_DEV_ID_VER_MASK                    0x000000F0ul
#define UWB2_DEV_ID_REV_MASK                    0x0000000Ful

/**
 * @brief UWB 2 modify register mask setting.
 * @details Specified modify register mask setting of UWB 2 Click driver.
 */
#define UWB2_MASK_ALL_32                        0xFFFFFFFFul
#define UWB2_MASK_NONE_32                       0x00000000ul
#define UWB2_MASK_ALL_16                        0xFFFFu
#define UWB2_MASK_NONE_16                       0x0000u
#define UWB2_MASK_ALL_8                         0xFF
#define UWB2_MASK_NONE_8                        0x00

/**
 * @brief UWB 2 spi command frame setting.
 * @details Specified spi command frame setting of UWB 2 Click driver.
 */
#define UWB2_SPI_WRITE                          0x8000u
#define UWB2_SPI_16BIT_ADDR                     0x4000u
#define UWB2_SPI_FAST_CMD                       0x0100u
#define UWB2_SPI_MASKED_WRITE_8BIT              0x0001u
#define UWB2_SPI_MASKED_WRITE_16BIT             0x0002u
#define UWB2_SPI_MASKED_WRITE_32BIT             0x0003u
#define UWB2_SPI_BASE_ADDR_MASK                 0x3E00u
#define UWB2_SPI_SUB_ADDR_MASK                  0x01FCu
#define UWB2_SPI_MODE_MASK                      0x0003u

/**
 * @brief UWB 2 wait status timeout setting.
 * @details Specified wait status timeout setting of UWB 2 Click driver.
 */
#define UWB2_WAIT_TIMEOUT_MS                    5000u

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b uwb2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define UWB2_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define UWB2_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // uwb2_set

/**
 * @defgroup uwb2_map UWB 2 MikroBUS Map
 * @brief MikroBUS pin mapping of UWB 2 Click driver.
 */

/**
 * @addtogroup uwb2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UWB 2 Click to the selected MikroBUS.
 */
#define UWB2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ext = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // uwb2_map
/*! @} */ // uwb2

/**
 * @brief UWB 2 Click chip configuration object.
 * @details Chip configuration object definition of UWB 2 Click driver.
 */
typedef struct
{
    uint8_t channel;    /**< Channel number (5 or 9). */
    uint8_t tx_plen;    /**< Transmit preample length (UWB2_TX_PLEN_32..UWB2_TX_PLEN_4096). */
    uint8_t pac;        /**< Preamble Acquisition Chunk Size (UWB2_PAC_SIZE_4..UWB2_PAC_SIZE_32). */
    uint8_t tx_code;    /**< TX preamble code (1 to 24, where 1-8 set PRF to 16 MHz and others set to 64 MHz). */
    uint8_t rx_code;    /**< RX preamble code (1 to 24, where 1-8 set PRF to 16 MHz and others set to 64 MHz). */
    uint8_t sfd_type;   /**< SFD type (0 - IEEE 8-bit standard, 1 - DW 8-bit, 2 - DW 16-bit, 3 - 4z BPRF). */
    uint8_t data_rate;  /**< Data rate (0 - 850Kbs, 1 - 6.8Mbs). */
    uint16_t sfd_to;    /**< SFD timeout value (in symbols). */
    
} uwb2_chip_cfg_t;

/**
 * @brief UWB 2 Click context object.
 * @details Context object definition of UWB 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wup;          /**< Wake-up pin (Active high). */
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t ext;           /**< External ON pin (Active high). */
    digital_in_t irq;           /**< Interrupt request pin (Active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} uwb2_t;

/**
 * @brief UWB 2 Click configuration object.
 * @details Configuration object definition of UWB 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wup;             /**< Wake-up pin (Active high). */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t ext;             /**< External ON pin (Active high). */
    pin_name_t irq;             /**< Interrupt request pin (Active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} uwb2_cfg_t;

/**
 * @brief UWB 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UWB2_OK = 0,
    UWB2_ERROR = -1

} uwb2_return_value_t;

/*!
 * @addtogroup uwb2 UWB 2 Click Driver
 * @brief API for configuring and manipulating UWB 2 Click driver.
 * @{
 */

/**
 * @brief UWB 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uwb2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uwb2_cfg_setup ( uwb2_cfg_t *cfg );

/**
 * @brief UWB 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uwb2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_init ( uwb2_t *ctx, uwb2_cfg_t *cfg );

/**
 * @brief UWB 2 default configuration function.
 * @details This function executes a default configuration of UWB 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uwb2_default_cfg ( uwb2_t *ctx );

/**
 * @brief UWB 2 send cmd function.
 * @details This function send fast command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] cmd : Fast command to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_send_cmd ( uwb2_t *ctx, uint8_t cmd );

/**
 * @brief UWB 2 read register function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_read_reg ( uwb2_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief UWB 2 write register function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_write_reg ( uwb2_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief UWB 2 read register 8bit function.
 * @details This function reads 8-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 8-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_read_reg_8bit ( uwb2_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief UWB 2 read register 16bit function.
 * @details This function reads 16-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_read_reg_16bit ( uwb2_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief UWB 2 read register 32bit function.
 * @details This function reads 32-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 32-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_read_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t *data_out );

/**
 * @brief UWB 2 write register 8bit function.
 * @details This function writes 8-bit data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 8-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_write_reg_8bit ( uwb2_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief UWB 2 write register 16bit function.
 * @details This function writes 16-bit data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_write_reg_16bit ( uwb2_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief UWB 2 write register 32bit function.
 * @details This function writes 32-bit data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_write_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t data_in );

/**
 * @brief UWB 2 modify register 8bit function.
 * @details This function modifies 8-bit data with AND and OR masks of the selected register.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] and_mask : 8-bit AND mask.
 * @param[in] or_mask : 8-bit OR mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_modify_reg_8bit ( uwb2_t *ctx, uint16_t reg, uint8_t and_mask, uint8_t or_mask );

/**
 * @brief UWB 2 modify register 16bit function.
 * @details This function modifies 16-bit data with AND and OR masks of the selected register.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] and_mask : 16-bit AND mask.
 * @param[in] or_mask : 16-bit OR mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_modify_reg_16bit ( uwb2_t *ctx, uint16_t reg, uint16_t and_mask, uint16_t or_mask );

/**
 * @brief UWB 2 modify register 32bit function.
 * @details This function modifies 32-bit data with AND and OR masks of the selected register.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] and_mask : 32-bit AND mask.
 * @param[in] or_mask : 32-bit OR mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_modify_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t and_mask, uint32_t or_mask );

/**
 * @brief UWB 2 read otp function.
 * @details This function reads a desired number of data bytes starting from the selected OTP memory address.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] address : Start OTP memory address.
 * @param[out] data_out : Output data read (32-bit array).
 * @param[in] len : Number of data DWORDs to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_read_otp ( uwb2_t *ctx, uint16_t address, uint32_t *data_out, uint16_t len );

/**
 * @brief UWB 2 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void uwb2_set_rst_pin ( uwb2_t *ctx, uint8_t state );

/**
 * @brief UWB 2 set wup pin function.
 * @details This function sets the WAKEUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void uwb2_set_wup_pin ( uwb2_t *ctx, uint8_t state );

/**
 * @brief UWB 2 get ext pin function.
 * @details This function returns the EXTON pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t uwb2_get_ext_pin ( uwb2_t *ctx );

/**
 * @brief UWB 2 get irq pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t uwb2_get_irq_pin ( uwb2_t *ctx );

/**
 * @brief UWB 2 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uwb2_reset_device ( uwb2_t *ctx );

/**
 * @brief UWB 2 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_check_communication ( uwb2_t *ctx );

/**
 * @brief UWB 2 power up IC function.
 * @details This function resets the device, checks the communication, and waits
 * until the IC enters the IDLE_RC state.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_power_up_ic ( uwb2_t *ctx );

/**
 * @brief UWB 2 initialize IC function.
 * @details This function initializes the device transceiver by performing the initially
 * required device configurations which reads and applies LDO and BIAS tune and crystal trim
 * values from OTP memory.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must be called after a reset or on power up of the device.
 */
err_t uwb2_initialize_ic ( uwb2_t *ctx );

/**
 * @brief UWB 2 configure IC function.
 * @details This function configures the device as per the provided IC config structure.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in,out] config : The IC config structure.
 * See #uwb2_chip_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must be called after initializing the device.
 */
err_t uwb2_configure_ic ( uwb2_t *ctx, uwb2_chip_cfg_t *config );

/**
 * @brief UWB 2 set IC state function.
 * @details This function can place the IC into IDLE/IDLE_PLL or IDLE_RC mode when
 * it is not actively in TX or RX.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - INIT,
 *                    @li @c 1 - IDLE/IDLE_PLL,
 *                    @li @c 2 - IDLE_RC.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_set_ic_state ( uwb2_t *ctx, uint8_t state );

/**
 * @brief UWB 2 load IC RX lut function.
 * @details This function load RX lookup tables from OTP or by manually programming
 * hard-coded values into the DGC registers for the selected channel.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] channel : @li @c 0x05 - Channel 5,
 *                      @li @c 0x09 - Channel 9.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_load_ic_rx_lut ( uwb2_t *ctx, uint8_t channel );

/**
 * @brief UWB 2 calibrate IC PGF function.
 * @details This function runs the PGF calibration. This is needed prior to reception.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If the RX calibration routine fails the device receiver performance will be severely affected,
 * the application should reset and try again.
 */
err_t uwb2_calibrate_ic_pgf ( uwb2_t *ctx );

/**
 * @brief UWB 2 set RX TX LEDs function.
 * @details This function sets the GPIO0 as RX LED - the output is asserted briefly when the receiver
 * completes the reception of a frame with a good FCS/CRC, and the GPIO3 as TX LED - the output is asserted
 * briefly when the transmitter completes sending a packet.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Disable RX/TX LEDs,
 *                   @li @c 1 - Enable RX/TX LEDs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_set_rx_tx_leds ( uwb2_t *ctx, uint8_t mode );

/**
 * @brief UWB 2 wait for status lo function.
 * @details This function will continuously read lower 32 bits of the system status register
 * for a @b UWB2_WAIT_TIMEOUT_MS period or until it matches the bits set in the status
 * input parameter.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] status : Status bits mask to wait for (lower 32 bits of system status register).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout (Desired status bits are not set in expected period).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_wait_for_status_lo ( uwb2_t *ctx, uint32_t status );

/**
 * @brief UWB 2 clear status function.
 * @details This function reads and clears all 48 bits of the system status register.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout (Desired status bits are not set in expected period).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_clear_status ( uwb2_t *ctx );

/**
 * @brief UWB 2 send message function.
 * @details This function write a desired number of data bytes to the TX buffer, sets the TX message size,
 * starts transmission and waits for a TX frame sent event.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be sent.
 * @param[in] len : Number of data bytes to send.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_send_message ( uwb2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief UWB 2 read message function.
 * @details This function activates the reception and then waits for a frame with a good FCS/CRC
 * then reads up to @a len number of data bytes from the RX buffer and adjust the @a len parameter
 * with the number of data bytes actually read.
 * @param[in] ctx : Click context object.
 * See #uwb2_t object definition for detailed explanation.
 * @param[out] data_out : Output data buffer read.
 * @param[in,out] len : Input - the maximal number of data bytes that can be read, 
 *                      Output - the number of data bytes actually read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb2_read_message ( uwb2_t *ctx, uint8_t *data_out, uint16_t *len );

#ifdef __cplusplus
}
#endif
#endif // UWB2_H

/*! @} */ // uwb2

// ------------------------------------------------------------------------ END

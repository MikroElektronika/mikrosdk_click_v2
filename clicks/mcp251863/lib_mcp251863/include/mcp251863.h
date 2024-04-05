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
 * @file mcp251863.h
 * @brief This file contains API for MCP251863 Click Driver.
 */

#ifndef MCP251863_H
#define MCP251863_H

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
 * @addtogroup mcp251863 MCP251863 Click Driver
 * @brief API for configuring and manipulating MCP251863 Click driver.
 * @{
 */

/**
 * @defgroup mcp251863_reg MCP251863 Registers List
 * @brief List of registers of MCP251863 Click driver.
 */
#define MCP251863

/**
 * @brief MCP251863 Revision.
 * @details Specified setting for Revision of MCP251863 Click driver.
 */
//#define REV_A
#define REV_B

#ifdef REV_A
    #define FIXED_FILTER_ADDRESS
#endif

/**
 * @brief MCP251863 Number of implemented FIFOs.
 * @details Specified setting for number of implemented FIFOs of MCP251863 Click driver.
 */
#ifndef FPGA
    #define MCP251863_FIFO_08TO15_IMPLEMENTED
    #define MCP251863_FIFO_16TO31_IMPLEMENTED
#endif

/**
 * @brief MCP251863 Number of implemented Filters.
 * @details Specified setting for number of implemented Filters of MCP251863 Click driver.
 */
#ifndef FPGA
    #define MCP251863_FILT_08TO15_IMPLEMENTED
    #define MCP251863_FILT_16TO31_IMPLEMENTED
#endif

/**
 * @brief MCP251863 Internal oscillator implemented.
 * @details Specified setting for Internal oscillator implemented of MCP251863 Click driver.
 */
#ifdef MCP2520FD
    #define CAN_INTERNAL_OSC_PRESENT
#endif

/**
 * @brief MCP251863 Restricted Operation Mode implemented.
 * @details Specified setting for restricted operation mode implemented of MCP251863 Click driver.
 */
#ifdef REV_B
    #define CAN_RESTRICTED_MODE_PRESENT
#endif

/**
 * @brief MCP251863 Transmit Queue.
 * @details Specified setting for transmit queue of MCP251863 Click driver.
 */
#ifdef REV_B
    #define CAN_TXQUEUE_IMPLEMENTED
#endif

/**
 * @brief MCP251863 Up to A1 silicon we had to multiply user address by 4.
 * @details Specified setting for Up to A1 silicon we had to multiply user 
 * address by 4 of MCP251863 Click driver.
 */
#ifdef REV_A
    #define USERADDRESS_TIMES_FOUR
#endif

#ifdef MCP251863
    #define N_MCP2518_CTRL_REGS                         5
#endif

#define MCP251863_MAX_TXQUEUE_ATTEMPTS                  50
#define MCP251863_TX_REQUEST_ID                         0x300
#define MCP251863_TX_RESPONSE_ID                        0x301

#define MCP251863_CRCBASE                               0xFFFF
#define MCP251863_CRCUPPER                              1
#define MCP251863_DRV_CANFDSPI_INDEX_0                  0
#define MCP251863_SPI_DEFAULT_BUFFER_LENGTH             96

#define MCP251863_ISO_CRC                               1

#define MCP251863_MAX_MSG_SIZE                          76

#define MCP251863_MAX_DATA_BYTES                        64

#define MCP251863_INS_RESET                             0x00
#define MCP251863_INS_READ                              0x03
#define MCP251863_INS_READ_CRC                          0x0B
#define MCP251863_INS_WRITE                             0x02
#define MCP251863_INS_WRITE_CRC                         0x0A
#define MCP251863_INS_WRITE_SAFE                        0x0C


#define MCP251863_FIFO_OFFSET                           ( 3 * 4 )
#define MCP251863_FILTER_OFFSET                         ( 2 * 4 )

#ifdef CAN_TXQUEUE_IMPLEMENTED
    #define MCP251863_REG_CITXQCON                      0x050
    #define MCP251863_REG_CITXQSTA                      0x054
    #define MCP251863_REG_CITXQUA                       0x058
#endif

#ifdef FIXED_FILTER_ADDRESS
    #define MCP251863_REG_CIFLTCON                      0x1D0
    #define MCP251863_REG_CIFLTOBJ                      0x1F0
    #define MCP251863_REG_CIMASK                        0x1F4
#else
    #define MCP251863_REG_CIFLTCON                      ( MCP251863_REG_CIFIFOCON + ( MCP251863_FIFO_OFFSET * MCP251863_FIFO_TOTAL_CHANNELS ) )
    #define MCP251863_REG_CIFLTOBJ                      ( MCP251863_REG_CIFLTCON + MCP251863_FIFO_TOTAL_CHANNELS )
    #define MCP251863_REG_CIMASK                        ( MCP251863_REG_CIFLTOBJ + 4 )
#endif

#define MCP251863_REG_OSC                               0xE00
#define MCP251863_REG_IOCON                             0xE04
#define MCP251863_REG_CRC                               0xE08
#define MCP251863_REG_ECCCON                            0xE0C
#define MCP251863_REG_ECCSTA                            0xE10

#define MCP251863_RAM_SIZE                              2048
#define MCP251863_RAMADDR_START                         0x400
#define MCP251863_RAMADDR_END                           ( MCP251863_RAMADDR_START + MCP251863_RAM_SIZE )

#define MCP251863_LOW_POWER_MODE_EN                     0x08
#define MCP251863_LOW_POWER_MODE_DIS                    0x00
#define MCP251863_WAKEUP_INTERR_EN                      0x40

#define MCP251863_REG_CICON                             0x000
#define MCP251863_REG_CINBTCFG                          0x004
#define MCP251863_REG_CIDBTCFG                          0x008
#define MCP251863_REG_CITDC                             0x00C

#define MCP251863_REG_CITBC                             0x010
#define MCP251863_REG_CITSCON                           0x014
#define MCP251863_REG_CIVEC                             0x018
#define MCP251863_REG_CIINT                             0x01C
#define MCP251863_REG_CIINTFLAG                         MCP251863_REG_CIINT
#define MCP251863_REG_CIINTENABLE                       ( MCP251863_REG_CIINT + 2 ) 

#define MCP251863_REG_CIRXIF                            0x020
#define MCP251863_REG_CITXIF                            0x024
#define MCP251863_REG_CIRXOVIF                          0x028
#define MCP251863_REG_CITXATIF                          0x02C

#define MCP251863_REG_CITXREQ                           0x030
#define MCP251863_REG_CITREC                            0x034
#define MCP251863_REG_CIBDIAG0                          0x038
#define MCP251863_REG_CIBDIAG1                          0x03C

#define MCP251863_REG_CITEFCON                          0x040
#define MCP251863_REG_CITEFSTA                          0x044
#define MCP251863_REG_CITEFUA                           0x048
#define MCP251863_REG_CIFIFOBA                          0x04C

#define MCP251863_REG_CIFIFOCON                         0x050
#define MCP251863_REG_CIFIFOSTA                         0x054
#define MCP251863_REG_CIFIFOUA                          0x058

/**
 * @addtogroup mcp251863_reg
 * @{
 */

/**
 * @brief MCP251863 description register.
 * @details Specified register for description of MCP251863 Click driver.
 */

/*! @} */ // mcp251863_reg

/**
 * @defgroup mcp251863_set MCP251863 Registers Settings
 * @brief Settings for registers of MCP251863 Click driver.
 */

/**
 * @addtogroup mcp251863_set
 * @{
 */

/**
 * @brief MCP251863 description setting.
 * @details Specified setting for description of MCP251863 Click driver.
 */

/**
 * @brief MCP251863 CAN FIFO Channels.
 * @details Specified setting for CAN FIFO channels of MCP251863 Click driver.
 */
#define MCP251863_FIFO_CH0                              0
#define MCP251863_FIFO_CH1                              1
#define MCP251863_FIFO_CH2                              2
#define MCP251863_FIFO_CH3                              3
#define MCP251863_FIFO_CH4                              4
#define MCP251863_FIFO_CH5                              5
#define MCP251863_FIFO_CH6                              6
#define MCP251863_FIFO_CH7                              7

#ifdef MCP251863_FIFO_08TO15_IMPLEMENTED
    #define MCP251863_FIFO_CH8                          8
    #define MCP251863_FIFO_CH9                          9
    #define MCP251863_FIFO_CH10                         10
    #define MCP251863_FIFO_CH11                         11
    #define MCP251863_FIFO_CH12                         12
    #define MCP251863_FIFO_CH13                         13
    #define MCP251863_FIFO_CH14                         14
    #define MCP251863_FIFO_CH15                         15
#endif

#ifdef MCP251863_FIFO_16TO31_IMPLEMENTED
    #define MCP251863_FIFO_CH16                         16
    #define MCP251863_FIFO_CH17                         17
    #define MCP251863_FIFO_CH18                         18
    #define MCP251863_FIFO_CH19                         19
    #define MCP251863_FIFO_CH20                         20
    #define MCP251863_FIFO_CH21                         21
    #define MCP251863_FIFO_CH22                         22
    #define MCP251863_FIFO_CH23                         23
    #define MCP251863_FIFO_CH24                         24
    #define MCP251863_FIFO_CH25                         25
    #define MCP251863_FIFO_CH26                         26
    #define MCP251863_FIFO_CH27                         27
    #define MCP251863_FIFO_CH28                         28
    #define MCP251863_FIFO_CH29                         29
    #define MCP251863_FIFO_CH30                         30
    #define MCP251863_FIFO_CH31                         31
#endif


#define MCP251863_FIFO_TOTAL_CHANNELS                   32

#ifdef CAN_TXQUEUE_IMPLEMENTED
    #define MCP251863_FIFO_FIRST_CHANNEL                MCP251863_FIFO_CH1
    #define CAN_TXQUEUE_CH0                             MCP251863_FIFO_CH0
#else
    #define MCP251863_FIFO_FIRST_CHANNEL                MCP251863_FIFO_CH0
#endif

/**
 * @brief MCP251863 CAN Filter Channels.
 * @details Specified setting for CAN filter channels of MCP251863 Click driver.
 */
#define MCP251863_FILT0                                 0
#define MCP251863_FILT1                                 1
#define MCP251863_FILT2                                 2
#define MCP251863_FILT3                                 3
#define MCP251863_FILT4                                 4
#define MCP251863_FILT5                                 5
#define MCP251863_FILT6                                 6
#define MCP251863_FILT7                                 7

#ifdef MCP251863_FILT_08TO15_IMPLEMENTED
    #define MCP251863_FILT8                             8
    #define MCP251863_FILT9                             9
    #define MCP251863_FILT10                            10
    #define MCP251863_FILT11                            11
    #define MCP251863_FILT12                            12
    #define MCP251863_FILT13                            13
    #define MCP251863_FILT14                            14
    #define MCP251863_FILT15                            15
#endif

#ifdef MCP251863_FILT_16TO31_IMPLEMENTED
    #define MCP251863_FILT16                            16
    #define MCP251863_FILT17                            17
    #define MCP251863_FILT18                            18
    #define MCP251863_FILT19                            19
    #define MCP251863_FILT20                            20
    #define MCP251863_FILT21                            21
    #define MCP251863_FILT22                            22
    #define MCP251863_FILT23                            23
    #define MCP251863_FILT24                            24
    #define MCP251863_FILT25                            25
    #define MCP251863_FILT26                            26
    #define MCP251863_FILT27                            27
    #define MCP251863_FILT28                            28
    #define MCP251863_FILT29                            29
    #define MCP251863_FILT30                            30
    #define MCP251863_FILT31                            31
#endif

#define MCP251863_FILT_TOTAL                            32

/**
 * @brief MCP251863 CAN Operation Modes.
 * @details Specified setting for CAN operation modes of MCP251863 Click driver.
 */
#define MCP251863_NORMAL_MODE                           0x00
#define MCP251863_SLEEP_MODE                            0x01
#define MCP251863_INT_LOOP_MODE                         0x02
#define MCP251863_LISTEN_ONLY_MODE                      0x03
#define MCP251863_CONFIG_MODE                           0x04
#define MCP251863_EXT_LOOP_MODE                         0x05
#define MCP251863_CLASSIC_MODE                          0x06
#define MCP251863_RESTRICT_MODE                         0x07
#define MCP251863_INVALID_MODE                          0xFF

/**
 * @brief MCP251863 Transmit Bandwidth Sharing.
 * @details Specified setting for transmit bandwidth sharing of MCP251863 Click driver.
 */
#define MCP251863_TXBWS_NO_DELAY                        0
#define MCP251863_TXBWS_2                               1
#define MCP251863_TXBWS_4                               2
#define MCP251863_TXBWS_8                               3
#define MCP251863_TXBWS_16                              4
#define MCP251863_TXBWS_32                              5
#define MCP251863_TXBWS_64                              6
#define MCP251863_TXBWS_128                             7
#define MCP251863_TXBWS_256                             8
#define MCP251863_TXBWS_512                             9
#define MCP251863_TXBWS_1024                            10
#define MCP251863_TXBWS_2048                            11
#define MCP251863_TXBWS_4096                            12

/**
 * @brief MCP251863 Wake-up Filter Time.
 * @details Specified setting for wake-up filter time of MCP251863 Click driver.
 */
#define MCP251863_WFT00                                 0
#define MCP251863_WFT01                                 1
#define MCP251863_WFT10                                 2
#define MCP251863_WFT11                                 3

/**
 * @brief MCP251863 Data Byte Filter Number.
 * @details Specified setting for data byte filter number of MCP251863 Click driver.
 */
#define MCP251863_DNET_FILT_DISABLE                     0
#define MCP251863_DNET_FILT_SIZE_1_BIT                  1
#define MCP251863_DNET_FILT_SIZE_2_BIT                  2
#define MCP251863_DNET_FILT_SIZE_3_BIT                  3
#define MCP251863_DNET_FILT_SIZE_4_BIT                  4
#define MCP251863_DNET_FILT_SIZE_5_BIT                  5
#define MCP251863_DNET_FILT_SIZE_6_BIT                  6
#define MCP251863_DNET_FILT_SIZE_7_BIT                  7
#define MCP251863_DNET_FILT_SIZE_8_BIT                  8
#define MCP251863_DNET_FILT_SIZE_9_BIT                  9
#define MCP251863_DNET_FILT_SIZE_10_BIT                 10
#define MCP251863_DNET_FILT_SIZE_11_BIT                 11
#define MCP251863_DNET_FILT_SIZE_12_BIT                 12
#define MCP251863_DNET_FILT_SIZE_13_BIT                 13
#define MCP251863_DNET_FILT_SIZE_14_BIT                 14
#define MCP251863_DNET_FILT_SIZE_15_BIT                 15
#define MCP251863_DNET_FILT_SIZE_16_BIT                 16
#define MCP251863_DNET_FILT_SIZE_17_BIT                 17
#define MCP251863_DNET_FILT_SIZE_18_BIT                 18

/**
 * @brief MCP251863 FIFO Payload Size.
 * @details Specified setting for FIFO payload size of MCP251863 Click driver.
 */
#define MCP251863_PLSIZE_8                              0
#define MCP251863_PLSIZE_12                             1
#define MCP251863_PLSIZE_16                             2
#define MCP251863_PLSIZE_20                             3
#define MCP251863_PLSIZE_24                             4
#define MCP251863_PLSIZE_32                             5
#define MCP251863_PLSIZE_48                             6
#define MCP251863_PLSIZE_64                             7

/**
 * @brief MCP251863 CAN Data Length Code.
 * @details Specified setting for CAN data length code of MCP251863 Click driver.
 */
#define MCP251863_DLC_0                                 0
#define MCP251863_DLC_1                                 1
#define MCP251863_DLC_2                                 2
#define MCP251863_DLC_3                                 3
#define MCP251863_DLC_4                                 4
#define MCP251863_DLC_5                                 5
#define MCP251863_DLC_6                                 6
#define MCP251863_DLC_7                                 7
#define MCP251863_DLC_8                                 8
#define MCP251863_DLC_12                                9
#define MCP251863_DLC_16                                10
#define MCP251863_DLC_20                                11
#define MCP251863_DLC_24                                12
#define MCP251863_DLC_32                                13
#define MCP251863_DLC_48                                14
#define MCP251863_DLC_64                                15

/**
 * @brief MCP251863 CAN RX FIFO Status.
 * @details Specified setting for CAN RX FIFO status of MCP251863 Click driver.
 */
#define MCP251863_RX_FIFO_EMPTY                         0
#define MCP251863_RX_FIFO_STATUS_MASK                   0x0F
#define MCP251863_RX_FIFO_NOT_EMPTY                     0x01
#define MCP251863_RX_FIFO_HALF_FULL                     0x02
#define MCP251863_RX_FIFO_FULL                          0x04
#define MCP251863_RX_FIFO_OVERFLOW                      0x08

/**
 * @brief MCP251863 CAN TX FIFO Status.
 * @details Specified setting for CAN TX FIFO status of MCP251863 Click driver.
 */
#define MCP251863_TX_FIFO_FULL                          0
#define MCP251863_TX_FIFO_STATUS_MASK                   0x1F7
#define MCP251863_TX_FIFO_NOT_FULL                      0x01
#define MCP251863_TX_FIFO_HALF_FULL                     0x02
#define MCP251863_TX_FIFO_EMPTY                         0x04
#define MCP251863_TX_FIFO_ATTEMPTS_EXHAUSTED            0x10
#define MCP251863_TX_FIFO_ERROR                         0x20
#define MCP251863_TX_FIFO_ARBITRATION_LOST              0x40
#define MCP251863_TX_FIFO_ABORTED                       0x80
#define MCP251863_TX_FIFO_TRANSMITTING                  0x100

/**
 * @brief MCP251863 CAN TEF FIFO Status.
 * @details Specified setting for CAN TEF FIFO status of MCP251863 Click driver.
 */
#define MCP251863_TEF_FIFO_EMPTY                        0
#define MCP251863_TEF_FIFO_STATUS_MASK                  0x0F
#define MCP251863_TEF_FIFO_NOT_EMPTY                    0x01
#define MCP251863_TEF_FIFO_HALF_FULL                    0x02
#define MCP251863_TEF_FIFO_FULL                         0x04
#define MCP251863_TEF_FIFO_OVERFLOW                     0x08

/**
 * @brief MCP251863 CAN Module Events.
 * @details Specified setting for CAN module events of MCP251863 Click driver.
 */
#define MCP251863_TX_FIFO_NO_EVENT                      0
#define MCP251863_TX_FIFO_ALL_EVENTS                    0x17
#define MCP251863_TX_FIFO_NOT_FULL_EVENT                0x01
#define MCP251863_TX_FIFO_HALF_FULL_EVENT               0x02
#define MCP251863_TX_FIFO_EMPTY_EVENT                   0x04
#define MCP251863_TX_FIFO_ATTEMPTS_EXHAUSTED_EVENT      0x10

#define MCP251863_RX_FIFO_NO_EVENT                      0
#define MCP251863_RX_FIFO_ALL_EVENTS                    0x0F
#define MCP251863_RX_FIFO_NOT_EMPTY_EVENT               0x01
#define MCP251863_RX_FIFO_HALF_FULL_EVENT               0x02
#define MCP251863_RX_FIFO_FULL_EVENT                    0x04
#define MCP251863_RX_FIFO_OVERFLOW_EVENT                0x08

#define MCP251863_TEF_FIFO_NO_EVENT                     0
#define MCP251863_TEF_FIFO_ALL_EVENTS                   0x0F
#define MCP251863_TEF_FIFO_NOT_EMPTY_EVENT              0x01
#define MCP251863_TEF_FIFO_HALF_FULL_EVENT              0x02
#define MCP251863_TEF_FIFO_FULL_EVENT                   0x04
#define MCP251863_TEF_FIFO_OVERFLOW_EVENT               0x08

#define MCP251863_NO_EVENT                              0
#define MCP251863_ALL_EVENTS                            0xFF1F
#define MCP251863_TX_EVENT                              0x0001
#define MCP251863_RX_EVENT                              0x0002
#define MCP251863_TIME_BASE_COUNTER_EVENT               0x0004
#define MCP251863_OPERATION_MODE_CHANGE_EVENT           0x0008
#define MCP251863_TEF_EVENT                             0x0010

#define MCP251863_RAM_ECC_EVENT                         0x0100
#define MCP251863_SPI_CRC_EVENT                         0x0200
#define MCP251863_TX_ATTEMPTS_EVENT                     0x0400
#define MCP251863_RX_OVERFLOW_EVENT                     0x0800
#define MCP251863_SYSTEM_ERROR_EVENT                    0x1000
#define MCP251863_BUS_ERROR_EVENT                       0x2000
#define MCP251863_BUS_WAKEUP_EVENT                      0x4000
#define MCP251863_RX_INVALID_MESSAGE_EVENT              0x8000

#define MCP251863_500K_1M                               0
#define MCP251863_500K_2M                               1
#define MCP251863_500K_3M                               2
#define MCP251863_500K_4M                               3
#define MCP251863_500K_5M                               4
#define MCP251863_500K_6M7                              5
#define MCP251863_500K_8M                               6
#define MCP251863_500K_10M                              7
#define MCP251863_250K_500K                             8
#define MCP251863_250K_833K                             9
#define MCP251863_250K_1M                               10
#define MCP251863_250K_1M5                              11
#define MCP251863_250K_2M                               12
#define MCP251863_250K_3M                               13
#define MCP251863_250K_4M                               14
#define MCP251863_1000K_4M                              15
#define MCP251863_1000K_8M                              16
#define MCP251863_125K_500K                             17

#define MCP251863_NBT_125K                              0
#define MCP251863_NBT_250K                              1
#define MCP251863_NBT_500K                              2
#define MCP251863_NBT_1M                                3

#define MCP251863_DBT_500K                              0
#define MCP251863_DBT_833K                              1
#define MCP251863_DBT_1M                                2
#define MCP251863_DBT_1M5                               3
#define MCP251863_DBT_2M                                4
#define MCP251863_DBT_3M                                5
#define MCP251863_DBT_4M                                6
#define MCP251863_DBT_5M                                7
#define MCP251863_DBT_6M7                               8
#define MCP251863_DBT_8M                                9
#define MCP251863_DBT_10M                               10

#define MCP251863_SSP_MODE_OFF                          0
#define MCP251863_SSP_MODE_MANUAL                       1
#define MCP251863_SSP_MODE_AUTO                         2

#define MCP251863_ERROR_FREE_STATE                      0
#define MCP251863_ERROR_ALL                             0x3F
#define MCP251863_TX_RX_WARNING_STATE                   0x01
#define MCP251863_RX_WARNING_STATE                      0x02
#define MCP251863_TX_WARNING_STATE                      0x04
#define MCP251863_RX_BUS_PASSIVE_STATE                  0x08
#define MCP251863_TX_BUS_PASSIVE_STATE                  0x10
#define MCP251863_TX_BUS_OFF_STATE                      0x20

#define MCP251863_TS_SOF                                0x00
#define MCP251863_TS_EOF                                0x01
#define MCP251863_TS_RES                                0x02

#define MCP2518_ECC_NO_EVENT                            0x00
#define MCP2518_ECC_ALL_EVENTS                          0x06
#define MCP2518_ECC_SEC_EVENT                           0x02
#define MCP2518_ECC_DED_EVENT                           0x04

#define MCP251863_CRC_NO_EVENT                          0x00
#define MCP251863_CRC_ALL_EVENTS                        0x03
#define MCP251863_CRC_CRCERR_EVENT                      0x01
#define MCP251863_CRC_FORMERR_EVENT                     0x02

/**
 * @brief MCP251863 Pin mode.
 * @details Specified setting for pin mode of MCP251863 Click driver.
 */
#define MCP251863_PIN_0                                 0
#define MCP251863_PIN_1                                 1

#define MCP251863_PINMODE_INT                           0
#define MCP251863_PINMODE_GPIO                          1

#define MCP251863_PINOUT                                0
#define MCP251863_PININ                                 1

#define MCP251863_PINLOW                                0
#define MCP251863_PINHIGH                               1

#define MCP251863_PUSHPULL                              0
#define MCP251863_OPENDRAIN                             1

#define MCP251863_CLKO_CLOCK                            0
#define MCP251863_CLKO_SOF                              1

/**
 * @brief MCP251863 TX req channel.
 * @details Specified setting for TX req channel of MCP251863 Click driver.
 */
#define MCP251863_TXREQ_CH0                             0x00000001
#define MCP251863_TXREQ_CH1                             0x00000002
#define MCP251863_TXREQ_CH2                             0x00000004
#define MCP251863_TXREQ_CH3                             0x00000008
#define MCP251863_TXREQ_CH4                             0x00000010
#define MCP251863_TXREQ_CH5                             0x00000020
#define MCP251863_TXREQ_CH6                             0x00000040
#define MCP251863_TXREQ_CH7                             0x00000080

#define MCP251863_TXREQ_CH8                             0x00000100
#define MCP251863_TXREQ_CH9                             0x00000200
#define MCP251863_TXREQ_CH10                            0x00000400
#define MCP251863_TXREQ_CH11                            0x00000800
#define MCP251863_TXREQ_CH12                            0x00001000
#define MCP251863_TXREQ_CH13                            0x00002000
#define MCP251863_TXREQ_CH14                            0x00004000
#define MCP251863_TXREQ_CH15                            0x00008000

#define MCP251863_TXREQ_CH16                            0x00010000
#define MCP251863_TXREQ_CH17                            0x00020000
#define MCP251863_TXREQ_CH18                            0x00040000
#define MCP251863_TXREQ_CH19                            0x00080000
#define MCP251863_TXREQ_CH20                            0x00100000
#define MCP251863_TXREQ_CH21                            0x00200000
#define MCP251863_TXREQ_CH22                            0x00400000
#define MCP251863_TXREQ_CH23                            0x00800000

#define MCP251863_TXREQ_CH24                            0x01000000
#define MCP251863_TXREQ_CH25                            0x02000000
#define MCP251863_TXREQ_CH26                            0x04000000
#define MCP251863_TXREQ_CH27                            0x08000000
#define MCP251863_TXREQ_CH28                            0x10000000
#define MCP251863_TXREQ_CH29                            0x20000000
#define MCP251863_TXREQ_CH30                            0x40000000
#define MCP251863_TXREQ_CH31                            0x80000000

/**
 * @brief MCP251863 FIFO channel.
 * @details Specified setting for FIFO channel of MCP251863 Click driver.
 */
#define MCP251863_ICODE_FIFO_CH0                        0
#define MCP251863_ICODE_FIFO_CH1                        1
#define MCP251863_ICODE_FIFO_CH2                        2
#define MCP251863_ICODE_FIFO_CH3                        3
#define MCP251863_ICODE_FIFO_CH4                        4
#define MCP251863_ICODE_FIFO_CH5                        5
#define MCP251863_ICODE_FIFO_CH6                        6
#define MCP251863_ICODE_FIFO_CH7                        7

#ifdef MCP251863_FIFO_08TO15_IMPLEMENTED
    #define MCP251863_ICODE_FIFO_CH8                    8
    #define MCP251863_ICODE_FIFO_CH9                    9
    #define MCP251863_ICODE_FIFO_CH10                   10
    #define MCP251863_ICODE_FIFO_CH11                   11
    #define MCP251863_ICODE_FIFO_CH12                   12
    #define MCP251863_ICODE_FIFO_CH13                   13
    #define MCP251863_ICODE_FIFO_CH14                   14
    #define MCP251863_ICODE_FIFO_CH15                   15
#endif

#ifdef MCP251863_FIFO_16TO31_IMPLEMENTED
    #define MCP251863_ICODE_FIFO_CH16                   16
    #define MCP251863_ICODE_FIFO_CH17                   17
    #define MCP251863_ICODE_FIFO_CH18                   18
    #define MCP251863_ICODE_FIFO_CH19                   19
    #define MCP251863_ICODE_FIFO_CH20                   20
    #define MCP251863_ICODE_FIFO_CH21                   21
    #define MCP251863_ICODE_FIFO_CH22                   22
    #define MCP251863_ICODE_FIFO_CH23                   23
    #define MCP251863_ICODE_FIFO_CH24                   24
    #define MCP251863_ICODE_FIFO_CH25                   25
    #define MCP251863_ICODE_FIFO_CH26                   26
    #define MCP251863_ICODE_FIFO_CH27                   27
    #define MCP251863_ICODE_FIFO_CH28                   28
    #define MCP251863_ICODE_FIFO_CH29                   29
    #define MCP251863_ICODE_FIFO_CH30                   30
    #define MCP251863_ICODE_FIFO_CH31                   31
#endif

#define MCP251863_ICODE_TOTAL_CHANNELS                  32
#define MCP251863_ICODE_NO_INT                          64
#define MCP251863_ICODE_CERRIF                          65
#define MCP251863_ICODE_WAKIF                           66
#define MCP251863_ICODE_RXOVIF                          67
#define MCP251863_ICODE_ADDRERR_SERRIF                  68
#define MCP251863_ICODE_MABOV_SERRIF                    69
#define MCP251863_ICODE_TBCIF                           70
#define MCP251863_ICODE_MODIF                           71
#define MCP251863_ICODE_IVMIF                           72
#define MCP251863_ICODE_TEFIF                           73
#define MCP251863_ICODE_TXATIF                          74
#define MCP251863_ICODE_RESERVED                        75

/**
 * @brief MCP251863 RX FIFO channel.
 * @details Specified setting for RX FIFO channel of MCP251863 Click driver.
 */
#define MCP251863_RXCODE_FIFO_CH0                       0
#define MCP251863_RXCODE_FIFO_CH1                       1
#define MCP251863_RXCODE_FIFO_CH2                       2
#define MCP251863_RXCODE_FIFO_CH3                       3
#define MCP251863_RXCODE_FIFO_CH4                       4
#define MCP251863_RXCODE_FIFO_CH5                       5
#define MCP251863_RXCODE_FIFO_CH6                       6
#define MCP251863_RXCODE_FIFO_CH7                       7

#ifdef MCP251863_FIFO_08TO15_IMPLEMENTED
    #define MCP251863_RXCODE_FIFO_CH8                   8
    #define MCP251863_RXCODE_FIFO_CH9                   9
    #define MCP251863_RXCODE_FIFO_CH10                  10
    #define MCP251863_RXCODE_FIFO_CH11                  11
    #define MCP251863_RXCODE_FIFO_CH12                  12
    #define MCP251863_RXCODE_FIFO_CH13                  13
    #define MCP251863_RXCODE_FIFO_CH14                  14
    #define MCP251863_RXCODE_FIFO_CH15                  15
#endif

#ifdef MCP251863_FIFO_16TO31_IMPLEMENTED
    #define MCP251863_RXCODE_FIFO_CH16                  16
    #define MCP251863_RXCODE_FIFO_CH17                  17
    #define MCP251863_RXCODE_FIFO_CH18                  18
    #define MCP251863_RXCODE_FIFO_CH19                  19
    #define MCP251863_RXCODE_FIFO_CH20                  20
    #define MCP251863_RXCODE_FIFO_CH21                  21
    #define MCP251863_RXCODE_FIFO_CH22                  22
    #define MCP251863_RXCODE_FIFO_CH23                  23
    #define MCP251863_RXCODE_FIFO_CH24                  24
    #define MCP251863_RXCODE_FIFO_CH25                  25
    #define MCP251863_RXCODE_FIFO_CH26                  26
    #define MCP251863_RXCODE_FIFO_CH27                  27
    #define MCP251863_RXCODE_FIFO_CH28                  28
    #define MCP251863_RXCODE_FIFO_CH29                  29
    #define MCP251863_RXCODE_FIFO_CH30                  30
    #define MCP251863_RXCODE_FIFO_CH31                  31
#endif

#define MCP251863_RXCODE_TOTAL_CHANNELS                 32
#define MCP251863_RXCODE_NO_INT                         64
#define MCP251863_RXCODE_RESERVED                       65

/**
 * @brief MCP251863 TX FIFO channel.
 * @details Specified setting for TX FIFO channel of MCP251863 Click driver.
 */
#define MCP251863_TXCODE_FIFO_CH0                       0
#define MCP251863_TXCODE_FIFO_CH1                       1
#define MCP251863_TXCODE_FIFO_CH2                       2
#define MCP251863_TXCODE_FIFO_CH3                       3
#define MCP251863_TXCODE_FIFO_CH4                       4
#define MCP251863_TXCODE_FIFO_CH5                       5
#define MCP251863_TXCODE_FIFO_CH6                       6
#define MCP251863_TXCODE_FIFO_CH7                       7

#ifdef MCP251863_FIFO_08TO15_IMPLEMENTED
    #define MCP251863_TXCODE_FIFO_CH8                   8
    #define MCP251863_TXCODE_FIFO_CH9                   9
    #define MCP251863_TXCODE_FIFO_CH10                  10
    #define MCP251863_TXCODE_FIFO_CH11                  11
    #define MCP251863_TXCODE_FIFO_CH12                  12
    #define MCP251863_TXCODE_FIFO_CH13                  13
    #define MCP251863_TXCODE_FIFO_CH14                  14
    #define MCP251863_TXCODE_FIFO_CH15                  15
#endif

#ifdef MCP251863_FIFO_16TO31_IMPLEMENTED
    #define MCP251863_TXCODE_FIFO_CH16                  16
    #define MCP251863_TXCODE_FIFO_CH17                  17
    #define MCP251863_TXCODE_FIFO_CH18                  18
    #define MCP251863_TXCODE_FIFO_CH19                  19
    #define MCP251863_TXCODE_FIFO_CH20                  20
    #define MCP251863_TXCODE_FIFO_CH21                  21
    #define MCP251863_TXCODE_FIFO_CH22                  22
    #define MCP251863_TXCODE_FIFO_CH23                  23
    #define MCP251863_TXCODE_FIFO_CH24                  24
    #define MCP251863_TXCODE_FIFO_CH25                  25
    #define MCP251863_TXCODE_FIFO_CH26                  26
    #define MCP251863_TXCODE_FIFO_CH27                  27
    #define MCP251863_TXCODE_FIFO_CH28                  28
    #define MCP251863_TXCODE_FIFO_CH29                  29
    #define MCP251863_TXCODE_FIFO_CH30                  30
    #define MCP251863_TXCODE_FIFO_CH31                  31
#endif

#define MCP251863_TXCODE_TOTAL_CHANNELS                 32
#define MCP251863_TXCODE_NO_INT                         64
#define MCP251863_TXCODE_RESERVED                       65

/**
 * @brief MCP251863 system clock.
 * @details Specified setting for system clock of MCP251863 Click driver.
 */
#define MCP251863_SYSCLK_40M                            0
#define MCP251863_SYSCLK_20M                            1
#define MCP251863_SYSCLK_10M                            2

/**
 * @brief MCP251863 clock devider.
 * @details Specified setting for clock devider of MCP251863 Click driver.
 */
#define MCP251863_CLKO_DIV1                             0
#define MCP251863_CLKO_DIV2                             1
#define MCP251863_CLKO_DIV4                             2
#define MCP251863_CLKO_DIV10                            3

#define N_MCP251863_FIFO_REGS                           ( MCP251863_FIFO_TOTAL_CHANNELS * MCP251863_FIFO_OFFSET )
#define N_MCP251863_FILT_CTRL_REGS                      ( MCP251863_FILT_TOTAL / 4 )
#define N_MCP251863_FILT_OBJ_REGS                       ( MCP251863_FILT_TOTAL * MCP251863_FILTER_OFFSET )

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mcp251863_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MCP251863_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define MCP251863_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mcp251863_set

/**
 * @defgroup mcp251863_map MCP251863 MikroBUS Map
 * @brief MikroBUS pin mapping of MCP251863 Click driver.
 */

/**
 * @addtogroup mcp251863_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MCP251863 Click to the selected MikroBUS.
 */
#define MCP251863_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.stby = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.clk  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // mcp251863_map
/*! @} */ // mcp251863

/**
 * @brief MCP251863 Click CAN Configure.
 * @details CAN Configure definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t d_net_filter_count;
    uint32_t iso_crc_enable;
    uint32_t protocol_expection_event_disable;
    uint32_t wake_up_filter_enable;
    uint32_t wake_up_filter_time;
    uint32_t bit_rate_switch_disable;
    uint32_t restrict_re_tx_attempts;
    uint32_t esi_in_gateway_mode;
    uint32_t system_error_to_listen_only;
    uint32_t store_in_tef;
    uint32_t txq_enable;
    uint32_t tx_band_width_sharing;

} mcp251863_can_cfg_t;

/**
 * @brief MCP251863 Click CAN Message Configuration.
 * @details CAN Message Configuration definition of MCP251863 Click driver.
 */
typedef struct
{
    uint8_t   iso_crc_enable;
    uint8_t   store_in_tef;
    uint8_t   tx_fifo_size;
    uint8_t   tx_pay_load_size;
    uint8_t   tx_priority;
    uint8_t   rx_fifo_size;
    uint8_t   rx_pay_load_size;
    uint16_t  standard_id;
    uint32_t  extended_id;
    uint8_t   fd_frame;
    uint8_t   switch_bit_rate;
    uint8_t   ide;
    uint8_t   remote_frame_req;
    uint8_t   seq;

} mcp251863_config_t;

/**
 * @brief MCP251863 Click Module ID.
 * @details Module ID definition of MCP251863 Click driver.
 */
typedef uint8_t mcp251863_id_t;

/**
 * @brief MCP251863 Click CAN Message Time Stamp.
 * @details CAN Message Time Stamp definition of MCP251863 Click driver.
 */
typedef uint32_t mcp251863_msg_time_stamp_t;

/**
 * @brief MCP251863 Click CAN Message Object ID.
 * @details CAN Message Object ID definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t sid            : 11;
    uint32_t eid            : 18;
    uint32_t sid11          : 1;
    uint32_t unimplemented1 : 2;

} mcp251863_msg_obj_id_t;

/**
 * @brief MCP251863 Click CAN TX Message Object Control.
 * @details CAN TX Message Object Control definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t dlc;
    uint32_t ide;
    uint32_t rtr;
    uint32_t brs;
    uint32_t fdf;
    uint32_t esi;
    uint32_t seq;
    uint32_t unimplemented1;

} mcp251863_tx_msg_obj_ctl_t;

/**
 * @brief MCP251863 Click CAN TX Message Object.
 * @details CAN TX Message Object definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        mcp251863_msg_obj_id_t id;
        mcp251863_tx_msg_obj_ctl_t ctrl;
        mcp251863_msg_time_stamp_t time_stamp;
    } bf;
    uint32_t word[ 3 ];
    uint8_t byte[ 12 ];

} mcp251863_tx_msg_obj_t;

/**
 * @brief MCP251863 Click CAN RX Message Object Control.
 * @details CAN RX Message Object Control definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t dlc            : 4;
    uint32_t ide            : 1;
    uint32_t rtr            : 1;
    uint32_t brs            : 1;
    uint32_t fdf            : 1;
    uint32_t esi            : 1;
    uint32_t unimplemented1 : 2;
    uint32_t filter_hit     : 5;
    uint32_t unimplemented2 : 16;

} mcp251863_rx_msg_obj_ctl_t;

/**
 * @brief MCP251863 Click CAN RX Message Object.
 * @details CAN RX Message Object definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        mcp251863_msg_obj_id_t id;
        mcp251863_rx_msg_obj_ctl_t ctrl;
        mcp251863_msg_time_stamp_t time_stamp;
    } bf;
    uint32_t word[ 3 ];
    uint8_t byte[ 12 ];

} mcp251863_rx_msg_obj_t;

/**
 * @brief MCP251863 Click CAN TEF Message Object.
 * @details CAN TEF Message Object definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        mcp251863_msg_obj_id_t id;
        mcp251863_tx_msg_obj_ctl_t ctrl;
        mcp251863_msg_time_stamp_t time_stamp;
    } bf;
    uint32_t word[ 3 ];
    uint8_t byte[ 12 ];

} mcp251863_tef_msg_obj_t;

/**
 * @brief MCP251863 Click CAN Filter Object ID.
 * @details CAN Filter Object ID definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t sid;
    uint32_t eid;
    uint32_t sid11;
    uint32_t exide;
    uint32_t unimplemented1;

} mcp251863_filt_obj_id_t;

/**
 * @brief MCP251863 Click Filter Object Register.
 * @details Filter Object Register definition of MCP251863 Click driver.
 */
typedef union
{
    mcp251863_filt_obj_id_t bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_filt_obj_t;

/**
 * @brief MCP251863 Click CAN Mask Object ID.
 * @details CAN Mask Object ID definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t msid;
    uint32_t meid;
    uint32_t msid11;
    uint32_t mide;
    uint32_t unimplemented1;

} mcp251863_mask_obj_id_t;

/**
 * @brief MCP251863 Click Mask Object Register.
 * @details Mask Object Register definition of MCP251863 Click driver.
 */
typedef union
{
    mcp251863_mask_obj_id_t bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_mask_obj_t;

typedef union
{
    uint8_t byte[ 4 ];
    uint32_t word;

} mcp251863_reg_t;

/**
 * @brief MCP251863 Click CAN Control Register.
 * @details CAN Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t d_net_filter_count               : 5;
        uint32_t iso_crc_enable                   : 1;
        uint32_t protocol_exception_event_disable : 1;
        uint32_t unimplemented1                   : 1;
        uint32_t wake_up_filter_enable            : 1;
        uint32_t wake_up_filter_time              : 2;
        uint32_t unimplemented2                   : 1;
        uint32_t bit_rate_switch_disable          : 1;
        uint32_t unimplemented3                   : 3;
        uint32_t restrict_re_tx_attempts          : 1;
        uint32_t esi_in_gateway_mode              : 1;
        uint32_t system_error_to_listen_only      : 1;
        uint32_t store_in_tef                     : 1;
        uint32_t txq_enable                       : 1;
        uint32_t op_mode                          : 3;
        uint32_t request_op_mode                  : 3;
        uint32_t abort_all_tx                     : 1;
        uint32_t tx_band_width_sharing            : 4;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_ctl_t;

/**
 * @brief MCP251863 Click Transmit Queue Control Register.
 * @details Transmit Queue Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tx_not_full_ie : 1;
        uint32_t unimplemented1 : 1;
        uint32_t tx_empty_ie    : 1;
        uint32_t unimplemented2 : 1;
        uint32_t tx_attempt_ie  : 1;
        uint32_t unimplemented3 : 2;
        uint32_t tx_enable      : 1;
        uint32_t uinc           : 1;
        uint32_t tx_request     : 1;
        uint32_t freset         : 1;
        uint32_t unimplemented4 : 5;
        uint32_t tx_priority    : 5;
        uint32_t tx_attempts    : 2;
        uint32_t unimplemented5 : 1;
        uint32_t fifo_size      : 5;
        uint32_t pay_load_size  : 3;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_tx_que_ctl_t;

/**
 * @brief MCP251863 Click Transmit Event FIFO Control Register.
 * @details Transmit Event FIFO Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tefneie           : 1;
        uint32_t tefhfie           : 1;
        uint32_t teffulie          : 1;
        uint32_t tefovie           : 1;
        uint32_t unimplemented1    : 1;
        uint32_t time_stamp_enable : 1;
        uint32_t unimplemented2    : 2;
        uint32_t uinc              : 1;
        uint32_t unimplemented3    : 1;
        uint32_t freset            : 1;
        uint32_t unimplemented4    : 13;
        uint32_t fifo_size         : 5;
        uint32_t unimplemented5    : 3;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_tef_ctl_t;

/**
 * @brief MCP251863 Click FIFO Control Register.
 * @details FIFO Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t rx_not_empty_ie      : 1;
        uint32_t rx_half_full_ie      : 1;
        uint32_t rx_full_ie           : 1;
        uint32_t rx_over_flow_ie      : 1;
        uint32_t unimplemented1       : 1;
        uint32_t rx_time_stamp_enable : 1;
        uint32_t unimplemented2       : 1;
        uint32_t tx_enable            : 1;
        uint32_t uinc                 : 1;
        uint32_t unimplemented3       : 1;
        uint32_t freset               : 1;
        uint32_t unimplemented4       : 13;
        uint32_t fifo_size            : 5;
        uint32_t pay_load_size        : 3;
    } rx_bf;

    struct {
        uint32_t tx_not_full_ie  : 1;
        uint32_t tx_half_full_ie : 1;
        uint32_t tx_empty_ie     : 1;
        uint32_t unimplemented1  : 1;
        uint32_t tx_attempt_ie   : 1;
        uint32_t unimplemented2  : 1;
        uint32_t rtr_enable      : 1;
        uint32_t tx_enable       : 1;
        uint32_t uinc            : 1;
        uint32_t tx_request      : 1;
        uint32_t freset          : 1;
        uint32_t unimplemented3  : 5;
        uint32_t tx_priority     : 5;
        uint32_t tx_attempts     : 2;
        uint32_t unimplemented4  : 1;
        uint32_t fifo_size       : 5;
        uint32_t pay_load_size   : 3;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_fifo_ctl_t;

/**
 * @brief MCP251863 Click Filter Control Register.
 * @details Filter Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t buffer_pointer : 5;
        uint32_t unimplemented1 : 2;
        uint32_t enable         : 1;
    } bf;
    uint8_t byte;

} mcp251863_filt_ctl_t;

/**
 * @brief MCP251863 Click Oscillator Control Register.
 * @details Oscillator Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t pll_enable     : 1;
        uint32_t unimplemented1 : 1;
        uint32_t osc_disable    : 1;
        uint32_t unimplemented2 : 1;
        uint32_t sclk_divide    : 1;
        uint32_t clk_out_divide : 2;
        uint32_t unimplemented3 : 1;
        uint32_t pll_ready      : 1;
        uint32_t unimplemented4 : 1;
        uint32_t osc_ready      : 1;
        uint32_t unimplemented5 : 1;
        uint32_t sclk_ready     : 1;
        uint32_t unimplemented6 : 19;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_osc_ctl_t;

/**
 * @brief MCP251863 Click Oscillator Control.
 * @details Oscillator Control definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t pll_enable;
    uint32_t osc_disable;
    uint32_t sclk_divide;
    uint32_t clk_out_divide;

} mcp251863_div_ctl_t;

/**
 * @brief MCP251863 Click I/O Control Register.
 * @details I/O Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tris0                     : 1;
        uint32_t tris1                     : 1;
        uint32_t unimplemented1            : 2;
        uint32_t clear_auto_sleep_on_match : 1;
        uint32_t auto_sleep_enable         : 1;
        uint32_t xcr_stby_enable           : 1;
        uint32_t unimplemented2            : 1;
        uint32_t lat0                      : 1;
        uint32_t lat1                      : 1;
        uint32_t unimplemented3            : 5;
        uint32_t hvdetsel                  : 1;
        uint32_t gpio0                     : 1;
        uint32_t gpio1                     : 1;
        uint32_t unimplemented4            : 6;
        uint32_t pin_mode0                 : 1;
        uint32_t pin_mode1                 : 1;
        uint32_t unimplemented5            : 2;
        uint32_t tx_can_open_drain         : 1;
        uint32_t sof_output_enable         : 1;
        uint32_t int_pin_open_drain        : 1;
        uint32_t unimplemented6            : 1;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_io_ctl_t;

/**
 * @brief MCP251863 Click ECC Control Register.
 * @details ECC Control Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {/* can_fd_ubp */
        uint32_t ecc_en         : 1;
        uint32_t secie          : 1;
        uint32_t dedie          : 1;
        uint32_t unimplemented1 : 5;
        uint32_t parity         : 7;
        uint32_t unimplemented2 : 17;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_ecc_ctl_t;

/**
 * @brief MCP251863 Click CAN Configure.
 * @details CAN Configure definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t d_net_filter_count               : 5;
    uint32_t iso_crc_enable                   : 1;
    uint32_t protocol_expection_event_disable : 1;
    uint32_t wake_up_filter_enable            : 1;
    uint32_t wake_up_filter_time              : 2;
    uint32_t bit_rate_switch_disable          : 1;
    uint32_t restrict_re_tx_attempts          : 1;
    uint32_t esi_in_gateway_mode              : 1;
    uint32_t system_error_to_listen_only      : 1;
    uint32_t store_in_tef                     : 1;
    uint32_t txq_enable                       : 1;
    uint32_t tx_band_width_sharing            : 4;

} T_MCP251863_cfg_t;

/**
 * @brief MCP251863 Click CAN Transmit Channel Configure.
 * @details CAN Transmit Channel Configure definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t rtr_enable;
    uint32_t tx_priority;
    uint32_t tx_attempts;
    uint32_t fifo_size;
    uint32_t pay_load_size;

} mcp251863_tx_fifo_cfg_t;

/**
 * @brief MCP251863 Click CAN Transmit Queue Configure.
 * @details CAN Transmit Queue Configure definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t tx_priority   : 5;
    uint32_t tx_attempts   : 2;
    uint32_t fifo_size     : 5;
    uint32_t pay_load_size : 3;

} mcp251863_tx_que_cfg_t;

/**
 * @brief MCP251863 Click CAN Receive Channel Configure.
 * @details CAN Receive Channel Configure definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t rx_time_stamp_enable;
    uint32_t fifo_size;
    uint32_t pay_load_size;

} mcp251863_rx_fifo_cfg_t;


/**
 * @brief MCP251863 Click FIFO User Address Register.
 * @details FIFO User Address Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t user_address   : 12;
        uint32_t unimplemented1 : 20;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_fifo_user_cfg_t;

/**
 * @brief MCP251863 Click CAN Transmit Event FIFO Configure.
 * @details CAN Transmit Event FIFO Configure definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t time_stamp_enable;
    uint32_t fifo_size;

} mcp251863_tef_cfg_t;

/**
 * @brief MCP251863 Click Nominal Bit Time Configuration Register.
 * @details Nominal Bit Time Configuration Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t swj            : 7;
        uint32_t unimplemented1 : 1;
        uint32_t tseg2          : 7;
        uint32_t unimplemented2 : 1;
        uint32_t tseg1          : 8;
        uint32_t brp            : 8;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_nbt_cfg_t;

/**
 * @brief MCP251863 Click Data Bit Time Configuration Register.
 * @details Data Bit Time Configuration Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t swj            : 4;
        uint32_t unimplemented1 : 4;
        uint32_t tseg2          : 4;
        uint32_t unimplemented2 : 4;
        uint32_t tseg1          : 5;
        uint32_t unimplemented3 : 3;
        uint32_t brp            : 8;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_dbt_cfg_t;

/**
 * @brief MCP251863 Click Transmitter Delay Compensation Register.
 * @details Transmitter Delay Compensation Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tdc_value          : 6;
        uint32_t unimplemented1     : 2;
        uint32_t tdc_offset         : 7;
        uint32_t unimplemented2     : 1;
        uint32_t tdc_mode           : 2;
        uint32_t unimplemented3     : 6;
        uint32_t sid11_enable       : 1;
        uint32_t edge_filter_enable : 1;
        uint32_t unimplemented4     : 6;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_tdc_cfg_t;

/**
 * @brief MCP251863 Click Time Stamp Configuration Register.
 * @details Time Stamp Configuration Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tbc_prescaler  : 10;
        uint32_t unimplemented1 : 6;
        uint32_t tbc_enable     : 1;
        uint32_t time_stamp_eof : 1;
        uint32_t unimplemented2 : 14;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_ts_cfg_t;

/**
 * @brief MCP251863 Click Interrupt Enables.
 * @details Interrupt Enables definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t txie           : 1;
    uint32_t rxie           : 1;
    uint32_t tbcie          : 1;
    uint32_t modie          : 1;
    uint32_t tefie          : 1;
    uint32_t unimplemented2 : 3;

    uint32_t eccie          : 1;
    uint32_t spicrcie       : 1;
    uint32_t txatie         : 1;
    uint32_t rxovie         : 1;
    uint32_t serrie         : 1;
    uint32_t cerrie         : 1;
    uint32_t wakie          : 1;
    uint32_t ivmie          : 1;

} mcp251863_int_en_t;

/**
 * @brief MCP251863 Click Interrupt Configuration.
 * @details Interrupt Configuration definition of MCP251863 Click driver.
 */
typedef union
{
    mcp251863_int_en_t ie;
    uint16_t word;
    uint8_t byte[ 2 ];

} mcp251863_int_cfg_t;

/**
 * @brief MCP251863 Click Interrupt Vector Register.
 * @details Interrupt Vector Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t icode          : 7;
        uint32_t unimplemented1 : 1;
        uint32_t filter_hit     : 5;
        uint32_t unimplemented2 : 3;
        uint32_t tx_code        : 7;
        uint32_t unimplemented3 : 1;
        uint32_t rx_code        : 7;
        uint32_t unimplemented4 : 1;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_int_vec_t;

/**
 * @brief MCP251863 Click Interrupt Flags.
 * @details Interrupt Flags definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t TXIF           : 1;
    uint32_t RXIF           : 1;
    uint32_t TBCIF          : 1;
    uint32_t MODIF          : 1;
    uint32_t TEFIF          : 1;
    uint32_t unimplemented1 : 3;

    uint32_t ECCIF    : 1;
    uint32_t SPICRCIF : 1;
    uint32_t TXATIF   : 1;
    uint32_t RXOVIF   : 1;
    uint32_t SERRIF   : 1;
    uint32_t CERRIF   : 1;
    uint32_t WAKIF    : 1;
    uint32_t IVMIF    : 1;

} mcp251863_int_flags_stat_t;

/**
 * @brief MCP251863 Click Interrupt Flag Register.
 * @details Interrupt Flag Register definition of MCP251863 Click driver.
 */
typedef union
{
    mcp251863_int_flags_stat_t if_stat;
    uint16_t word;
    uint8_t byte[ 2 ];

} mcp251863_int_flag_t;

/**
 * @brief MCP251863 Click Interrupt Register.
 * @details Interrupt Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        mcp251863_int_flags_stat_t if_stat;
        mcp251863_int_en_t ie;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_int_t;

/**
 * @brief MCP251863 Click Transmit/Receive Error Count Register.
 * @details Transmit/Receive Error Count Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t rx_error_count         : 8;
        uint32_t tx_error_count         : 8;
        uint32_t error_state_warning    : 1;
        uint32_t rx_error_state_warning : 1;
        uint32_t tx_error_state_warning : 1;
        uint32_t rx_error_state_passive : 1;
        uint32_t tx_error_state_passive : 1;
        uint32_t tx_error_state_bus_off : 1;
        uint32_t unimplemented1         : 10;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_trec_t;

/**
 * @brief MCP251863 Click Transmit Event FIFO Status Register.
 * @details Transmit Event FIFO Status Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tef_not_empty_if : 1;
        uint32_t tef_half_full_if : 1;
        uint32_t tef_full_if      : 1;
        uint32_t tef_ov_if        : 1;
        uint32_t unimplemented1   : 28;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_tef_t;

/**
 * @brief MCP251863 Click Transmit Queue Status Register.
 * @details Transmit Queue Status Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t tx_not_full_if      : 1;
        uint32_t unimplemented1      : 1;
        uint32_t tx_empty_if         : 1;
        uint32_t unimplemented2      : 1;
        uint32_t tx_attempt_if       : 1;
        uint32_t tx_error            : 1;
        uint32_t tx_lost_arbitration : 1;
        uint32_t tx_aborted          : 1;
        uint32_t fifo_index          : 5;
        uint32_t unimplemented3      : 19;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_tx_que_stat_t;

/**
 * @brief MCP251863 Click FIFO Status Register.
 * @details FIFO Status Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t rx_not_empty_if : 1;
        uint32_t rx_half_full_if : 1;
        uint32_t rx_full_if      : 1;
        uint32_t rx_over_flow_if : 1;
        uint32_t unimplemented1  : 4;
        uint32_t fifo_index      : 5;
        uint32_t unimplemented2  : 19;
    } rx_bf;

    struct {
        uint32_t tx_not_full_if      : 1;
        uint32_t tx_half_full_if     : 1;
        uint32_t tx_empty_if         : 1;
        uint32_t unimplemented1      : 1;
        uint32_t tx_attempt_if       : 1;
        uint32_t tx_error            : 1;
        uint32_t tx_lost_arbitration : 1;
        uint32_t tx_aborted          : 1;
        uint32_t fifo_index          : 5;
        uint32_t unimplemented2      : 19;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_fifo_stat_t;

/**
 * @brief MCP251863 Click CRC Regsiter.
 * @details CRC Regsiter definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t crc            : 16;
        uint32_t crcerrif       : 1;
        uint32_t ferrif         : 1;
        uint32_t unimplemented1 : 6;
        uint32_t crcerrie       : 1;
        uint32_t ferrie         : 1;
        uint32_t unimplemented2 : 6;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_crc_t;

/**
 * @brief MCP251863 Click ECC Status Register.
 * @details ECC Status Register definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t unimplemented1 : 1;
        uint32_t secif          : 1;
        uint32_t dedif          : 1;
        uint32_t unimplemented2 : 13;
        uint32_t error_address  : 12;
        uint32_t unimplemented3 : 4;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_ecc_sta_t;

/**
 * @brief MCP251863 Click Oscillator Status.
 * @details Oscillator Status definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t pll_ready  : 1;
    uint32_t osc_ready  : 1;
    uint32_t sclk_ready : 1;

} mcp251863_osc_sta_t;

/**
 * @brief MCP251863 Click CAN Bus Diagnostic flags.
 * @details CAN Bus Diagnostic flags definition of MCP251863 Click driver.
 */
typedef struct
{
    uint32_t n_bit0_err     : 1;
    uint32_t n_bit1_err     : 1;
    uint32_t n_ack_err      : 1;
    uint32_t n_form_err     : 1;
    uint32_t n_stuff_err    : 1;
    uint32_t n_crc_err      : 1;
    uint32_t unimplemented1 : 1;
    uint32_t txbo_err       : 1;
    uint32_t d_bit0_err     : 1;
    uint32_t d_bit1_err     : 1;
    uint32_t unimplemented2 : 1;
    uint32_t d_form_err     : 1;
    uint32_t d_stuff_err    : 1;
    uint32_t d_crc_err      : 1;
    uint32_t esi            : 1;
    uint32_t dlc_mismatch   : 1;

} mcp251863_bus_diag_flags_t;

/**
 * @brief MCP251863 Click CAN Bus Diagnostic Error Counts.
 * @details CAN Bus Diagnostic Error Counts definition of MCP251863 Click driver.
 */
typedef struct
{
    uint8_t n_rec;
    uint8_t n_tec;
    uint8_t d_rec;
    uint8_t d_tec;

} mcp251863_bus_error_count_t;

/**
 * @brief MCP251863 Click CAN BUS DIAGNOSTICS.
 * @details CAN BUS DIAGNOSTICS definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        mcp251863_bus_error_count_t error_count;
        uint16_t error_free_msg_count;
        mcp251863_bus_diag_flags_t flag;
    } bf;
    uint32_t word[ 2 ];
    uint8_t byte[ 8 ];

} mcp251863_bus_diag_t;

/**
 * @brief MCP251863 Click Diagnostic register 0.
 * @details CDiagnostic register 0 definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t n_rx_error_count : 8;
        uint32_t n_tx_error_count : 8;
        uint32_t d_rx_error_count : 8;
        uint32_t d_tx_error_count : 8;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_bus_diag0_t;

/**
 * @brief MCP251863 Click Diagnostic register 1.
 * @details CDiagnostic register 1 definition of MCP251863 Click driver.
 */
typedef union
{
    struct {
        uint32_t error_free_msg_count : 16;
        uint32_t n_bit0_error         : 1;
        uint32_t n_bit1_error         : 1;
        uint32_t n_ack_error          : 1;
        uint32_t n_form_error         : 1;
        uint32_t n_stuff_error        : 1;
        uint32_t n_crc_error          : 1;
        uint32_t unimplemented1       : 1;
        uint32_t txbo_error           : 1;
        uint32_t d_bit0_error         : 1;
        uint32_t d_bit1_error         : 1;
        uint32_t d_ack_error          : 1;
        uint32_t d_form_error         : 1;
        uint32_t d_stuff_error        : 1;
        uint32_t d_crc_error          : 1;
        uint32_t esi                  : 1;
        uint32_t unimplemented2       : 1;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp251863_bus_diag1_t;

/**
 * @brief MCP251863 Click CAN message configuration.
 * @details CAN message configuration definition of MCP251863 Click driver.
 */
typedef struct
{
    uint16_t address; 
    uint8_t *rxd; 
    uint16_t n_bytes;
    uint8_t *txd;
    uint32_t txd_num_bytes;

} mcp251863_func_data_t;

/**
 * @brief MCP251863 Click CAN message configuration.
 * @details CAN message configuration definition of MCP251863 Click driver.
 */
typedef struct
{
    uint8_t                         selected_bit_time;
    uint8_t                         tx_flags;
    uint8_t                         rx_flags;
    uint8_t                         error_flags;
    uint8_t                         tec;
    uint8_t                         rec;
    uint8_t                         op_mode;
    uint32_t                        tx_id;

    mcp251863_can_cfg_t             config;
    mcp251863_tx_fifo_cfg_t         tx_config;
    mcp251863_rx_fifo_cfg_t         rx_config;
    mcp251863_tx_msg_obj_t          tx_obj;
    mcp251863_rx_msg_obj_t          rx_obj;
    mcp251863_filt_obj_t            f_obj;
    mcp251863_mask_obj_t            m_obj;
    mcp251863_bus_diag_t            bus_diagnostics;

} mcp251863_data_t;

/**
 * @brief MCP251863 Click context object.
 * @details Context object definition of MCP251863 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  stby;        /**< Standby control IP. */

    // Input pins
    digital_in_t  clk;          /**< Clock OP. */
    digital_in_t  int_pin;      /**< Interrupt OP. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

    mcp251863_data_t glb_data;
    mcp251863_func_data_t func_data;
    
} mcp251863_t;

/**
 * @brief MCP251863 Click configuration object.
 * @details Configuration object definition of MCP251863 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;         /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;         /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;          /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;           /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t   stby;         /**< Standby control IP. */
    pin_name_t  clk;           /**< Clock OP. */
    pin_name_t  int_pin;       /**< Interrupt OP. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} mcp251863_cfg_t;

/**
 * @brief MCP251863 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MCP251863_OK = 0,
    MCP251863_ERROR = -1

} mcp251863_return_value_t;

/*!
 * @addtogroup mcp251863 MCP251863 Click Driver
 * @brief API for configuring and manipulating MCP251863 Click driver.
 * @{
 */

/**
 * @brief MCP251863 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mcp251863_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mcp251863_cfg_setup ( mcp251863_cfg_t *cfg );

/**
 * @brief MCP251863 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mcp251863_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_init ( mcp251863_t *ctx, mcp251863_cfg_t *cfg );

/**
 * @brief MCP251863 default configuration function.
 * @details This function executes a default configuration of MCP251863
 * click board.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mcp251863_default_cfg ( mcp251863_t *ctx );

/**
 * @brief MCP251863 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_generic_write ( mcp251863_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief MCP251863 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_generic_read ( mcp251863_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Message Transmit function.
 * @details Transmits the desired message and checks is message successfully sent.
 * @param[in] ctx : Click object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] data_in : Message to be sent.
 * @param[in] data_len : Determines the length of message.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_message ( mcp251863_t *ctx, uint8_t *data_in, uint16_t data_len );

/**
 * @brief Message Receive function
 * @details Receives the message and checks is message successfully received.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[out] data_out : Buffer where message be received
 * @param[out] data_len : Number of data bytes read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_message ( mcp251863_t *ctx, uint8_t *data_out, uint16_t *data_len );

/**
 * @brief Reset function
 * @details Function for reset using generic transfer
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_reset ( mcp251863_t *ctx );

/**
 * @brief SPI Read Byte function.
 * @details Function for read byte.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[out] data_out : Buffer where data will be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_read_byte ( mcp251863_t *ctx, uint16_t address, uint8_t *data_out );

/**
 * @brief SPI Write Byte.
 * @details Function for write byte.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_write_byte ( mcp251863_t *ctx, uint16_t address, uint8_t data_in );

/**
 * @brief SPI Read Word.
 * @details Function for read word.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[out] data_out : Buffer where data will be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_read_word ( mcp251863_t *ctx, uint16_t address, uint32_t *data_out );

/**
 * @brief SPI Write Word.
 * @details Function for write word.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_write_word ( mcp251863_t *ctx, uint16_t address, uint32_t data_in );

/**
 * @brief SPI Read Half Word.
 * @details Function for read half word.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[out] data_out : Buffer where data will be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_read_half_word ( mcp251863_t *ctx, uint16_t address, uint16_t *data_out );

/**
 * @brief SPI Write Half Word.
 * @details Function for write half word.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_write_half_word ( mcp251863_t *ctx, uint16_t address, uint16_t data_in );

/**
 * @brief SPI SFR Write Byte Safe.
 * @details Writes Byte to SFR at address using SPI CRC. Byte gets only written if CRC
 * matches.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 *
 * @note The function doesn't check if the address is an SFR address.
 */
err_t mcp251863_write_byte_safe ( mcp251863_t *ctx, uint16_t address, uint8_t data_in );

/**
 * @brief SPI RAM Write Word Safe.
 * @details Writes Word to RAM at address using SPI CRC. Word gets only written if CRC
 * matches.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 *
 * @note The function doesn't check if the address is a RAM address.
 */
err_t mcp251863_write_word_safe ( mcp251863_t *ctx, uint16_t address, uint32_t data_in );

/**
 * @brief SPI Read Byte Array.
 * @details Function for read byte array.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[out] data_out : Buffer where data will be read.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_read_byte_array ( mcp251863_t *ctx, uint16_t address, uint8_t *data_out, uint16_t n_bytes );

 /**
 * @brief SPI Read Byte Array with CRC.
 * @details Function for read byte with CRC.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] from_ram : Byte for array size.
 * @param[in] crc_is_correct : Compare CRC readings ( true - if equal, false - if not ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_read_byte_array_with_crc ( mcp251863_t *ctx, bool from_ram, bool *crc_is_correct );

/**
 * @brief SPI Write Byte Array.
 * @details Function for write byte array.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param data_in : Buffer of data to be written.
 * @param n_bytes : Number of bytes to be write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_write_byte_array ( mcp251863_t *ctx, uint16_t address, uint8_t *data_in, uint16_t n_bytes );

/**
 * @brief SPI Write Byte Array with CRC.
 * @details Function for write byte array with CRC.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] from_ram : Byte for array size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_write_byte_array_with_crc ( mcp251863_t *ctx, bool from_ram );

/**
 * @brief SPI Read Word Array.
 * @details Function for read word array.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[out] data_out : Buffer where data will be read.
 * @param[in] n_words : Number of words to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_read_word_array ( mcp251863_t *ctx, uint16_t address, uint32_t *data_out, uint16_t n_words );

/**
 * @brief SPI Write Word Array.
 * @details Function for write word array.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] address : Register adress.
 * @param[in] data_in : Buffer of data to be written.
 * @param[in] n_words : Number of words to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_write_word_array ( mcp251863_t *ctx, uint16_t address, uint32_t *data_in, uint16_t n_words );

/**
 * @brief CAN Control register configuration.
 * @details Function for CAN control register configuration.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] config : CAN config object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_configure ( mcp251863_t *ctx, mcp251863_can_cfg_t *config );

/**
 * @brief Reset Configure object to reset values.
 * @details Function for reset configure object.
 * @param[in] config : CAN config object.
 * @return Nothing.
 */
void mcp251863_configure_object_reset( mcp251863_can_cfg_t *config );

/**
 * @brief Select Operation Mode.
 * @details Function for select operation mode.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] op_mode : Operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error.
 *         @li @c -2 - Writte error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_operation_mode_select ( mcp251863_t *ctx, uint8_t op_mode );

/**
 * @brief Get Operation Mode.
 * @details Function for get operation mode.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @returns Operation mode.
 */
err_t mcp251863_operation_mode_get ( mcp251863_t *ctx );

/**
 * @brief Configure Transmit FIFO.
 * @details Function for configuring transmit FIFO.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] cannel : Channel.
 * @param[in] config : Tx QUEUE config object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_configure ( mcp251863_t *ctx, uint8_t channel, mcp251863_tx_fifo_cfg_t *config );

/**
 * @brief Reset Transmit Channel Configure object to reset values.
 * @details Function for reseting values of Transmit channel configure object.
 * @param[in] config : Tx QUEUE config object.
 * @return Nothing.
 */
void mcp251863_transmit_channel_configure_object_reset ( mcp251863_tx_fifo_cfg_t *config );

/**
 * @brief Configure Transmit Queue.
 * @details Function for configuring transmit Queue.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param[in] config : Tx QUEUE config object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_queue_configure ( mcp251863_t *ctx, mcp251863_tx_que_cfg_t *config );

/**
 * @brief Reset Transmit Queue Configure object to reset values.
 * @details Function for reseting values of Transmit Queue Configure object.
 * @param[in] config : Tx QUEUE config object.
 * @return Nothing.
 */
void mcp251863_transmit_queue_configure_object_reset ( mcp251863_tx_que_cfg_t *config );

/**
 * @brief TX Channel Load.
 * @details Loads data into Transmit channel.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[in] tx_obj : Tx Message object.
 * @param[in] flush : If TRUE - Requests transmission
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_load ( mcp251863_t *ctx, uint8_t channel, mcp251863_tx_msg_obj_t *tx_obj, bool flush );

/**
 * @brief TX Channel Flush.
 * @details Set TXREG of one channel.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_flush ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Transmit Channel Status Get
 * @details Function for getting Transmit Channel Status.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[in] status : Status to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_status_get ( mcp251863_t *ctx, uint8_t channel, uint16_t *status );

/**
 * @brief Transmit FIFO Reset.
 * @details Function for resetting FIFO Transmit.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
int8_t mcp251863_transmit_channel_reset ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Transmit FIFO Update.
 * @details Sets UINC of the transmit channel. Keeps TXREQ unchanged.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[in] flush : If TRUE - Requests transmission 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_update ( mcp251863_t *ctx, uint8_t channel, bool flush );

/**
 * @brief Request transmissions using TXREQ register.
 * @details Function for requesting transmissions using TXREQ register.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] tx_req : TXREQ register to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_request_set ( mcp251863_t *ctx, uint32_t tx_req );

/**
 * @brief Get TXREQ register.
 * @details Function for getting TXREQ register. 
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] tx_req : TXREQ register to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_request_get ( mcp251863_t *ctx, uint32_t* tx_req );

/**
 * @brief Abort transmission of single FIFO.
 * @details Function for aborting transmission of single FIFO.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_abort ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Abort All transmissions.
 * @details Function for aborting all transmission.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_abort_all ( mcp251863_t *ctx );

/**
 * @brief Set Transmit Bandwidth Sharing Delay.
 * @details Function for setting transmit bandwidth sharing delay.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param tx_bws : Transmit Bandwidth to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_band_width_sharing_set ( mcp251863_t *ctx, uint8_t tx_bws );

/**
 * @brief Filter Object Configuration.
 * @details Configures ID of filter object.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] filter : Filter.
 * @param[in] id : Filter object id.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_filter_object_configure ( mcp251863_t *ctx, uint8_t filter, mcp251863_filt_obj_id_t *id );

/**
 * @brief Filter Mask Configuration.
 * @details Configures Mask of filter object.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] filter : Filter.
 * @param[in] mask : Filter mask id
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_filter_mask_configure ( mcp251863_t *ctx, uint8_t filter, mcp251863_mask_obj_id_t *mask );

/**
 * @brief Link Filter to FIFO.
 * @details Initializes the Pointer from Filter to FIFO. Enables or disables the Filter.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] filter : Filter.
 * @param[in channel : Channel.
 * @param[in] enable : If TRUE - sets 1 on enable field ( of filter ctl object ) 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_filter_to_fifo_link ( mcp251863_t *ctx, uint8_t filter, uint8_t channel, bool enable );

/**
 * @brief Filter Enable.
 * @details Function for enabling specific filter.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] filter : Filter.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_filter_enable ( mcp251863_t *ctx, uint8_t filter );

/**
 * @brief Filter Disable.
 * @details Function for disabling specific filter.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] filter : Filter.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_filter_disable ( mcp251863_t *ctx, uint8_t filter );

/**
 * @brief  Set Device Net Filter Count.
 * @details Function for setting device net filter count.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] dnfc : Device Net Filter Count
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_device_net_filter_count_set ( mcp251863_t *ctx, uint8_t dnfc );

/**
 * @brief Configure Receive FIFO.
 * @details Function for configuring recive FIFO.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[in] config : Rx FIFO cfg object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_configure ( mcp251863_t *ctx, uint8_t channel, 
                                            mcp251863_rx_fifo_cfg_t *config );

/**
 * @brief Reset Receive Channel Configure object to reset value.
 * @details Function for resetting Receive Channel Configure object to reset value.
 * @param[in] config : Rx FIFO cfg object.
 * @return Nothing. 
 */
void mcp251863_receive_channel_configure_object_reset ( mcp251863_rx_fifo_cfg_t *config );

/**
 * @brief Receive Channel Status Get.
 * @details Function for getting Receive Channel Status.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[out] status : Status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_status_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *status );

/**
 * @brief Get Received Message.
 * @details Reads Received message from channel.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[out] rx_obj : Rx Message object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error,
 *         @li @c -3 - Read byte array error,
 *         @li @c -4 - Receiver channel update.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_message_get ( mcp251863_t *ctx, uint8_t channel, mcp251863_rx_msg_obj_t *rx_obj );

/**
 * @brief Receive FIFO Reset.
 * @details Function for resetting Receive FIFO.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_reset ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Receive FIFO Update
 * @details Sets UINC of the receive channel.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_update ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Transmit Event FIFO Status Get.
 * @details Function for getting Transmit Event FIFO Status.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] status : Status. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_status_get ( mcp251863_t *ctx, uint8_t *status );

/**
 * @brief Get Transmit Event FIFO Message
 * @details Reads Transmit Event FIFO message
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] tef_obj : TEF Message object. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error,
 *         @li @c -3 - Update error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_message_get ( mcp251863_t *ctx, mcp251863_tef_msg_obj_t *tef_obj );

/**
 * @brief Transmit Event FIFO Reset.
 * @details Function for resetting Transmit Event FIFO.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_reset ( mcp251863_t *ctx );

/**
 * @brief Transmit Event FIFO Update.
 * @details Sets UINC of the TEF.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_update ( mcp251863_t *ctx );

/**
 * @brief Configure Transmit Event FIFO.
 * @details Function for configuring Transmit Event FIFO.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] config : TEF configure object.    
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_configure ( mcp251863_t *ctx, mcp251863_tef_cfg_t *config );

/**
 * @brief Reset TefConfigure object to reset value
 * @details Function for resetting value of TEF configure object.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] config : TEF configure object.   
 * @return Nothing. 
 */
void mcp251863_tef_configure_object_reset ( mcp251863_tef_cfg_t *config );

/**
 * @brief Module Event Get
 * @details Reads interrupt Flags
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] flags : Interrupt disables to be read.   
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_get ( mcp251863_t *ctx, uint16_t *flags );

/**
 * @brief Module Event Enable.
 * @details Enables interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] flags : Interrupt disables to be read.   
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_enable ( mcp251863_t *ctx, uint16_t flags );

/**
 * @brief Module Event Disable.
 * @details Disables interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] flags : Interrupt disables to be read.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_disable ( mcp251863_t *ctx, uint16_t flags );

/**
 * @brief Module Event Clear.
 * @details Clears interrupt Flags.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] flags : Interrupt clears to be read.  
 * @returns  spi transfer error ( 0 : if succeed, -2 : write_half_word error )
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Write half word error.
 * 
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_clear ( mcp251863_t *ctx, uint16_t flags );

/**
 * @brief Get RX Code.
 * @details Function for getting RX Code.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[out] rx_code : Decode data_pointer. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_rx_code_get ( mcp251863_t *ctx, uint8_t *rx_code );

/**
 * @brief Get TX Code.
 * @details Function for getting TX Code.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] tx_code : Decode data_pointer. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_tx_code_get ( mcp251863_t *ctx, uint8_t *tx_code );

/**
 * @brief Get Filter Hit.
 * @details Function for getting Filter Hit.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[out] filter_hit : Filter hit. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_filter_hit_get ( mcp251863_t *ctx, uint8_t* filter_hit );

/**
 * @brief Get ICODE.
 * @details Function for getting ICODE.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] icode : Decode. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_module_event_icode_get ( mcp251863_t *ctx, uint8_t *icode );

/**
 * @brief Transmit FIFO Event Get.
 * @details Reads Transmit FIFO interrupt Flags.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] cannel : Channel. 
 * @param[in] flags : Interrupt flags.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_event_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *flags );

/**
 * @brief Get pending interrupts of all transmit FIFOs.
 * @details Function for gettingg pending interrupts of all transmit FIFOs.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] txif :  Buffer to be read. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_event_get ( mcp251863_t *ctx, uint32_t *txif );
 
/**
 * @brief Get pending TXATIF of all transmit FIFOs.
 * @details Function for gettingg pending TXATIF of all transmit FIFOs.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.  
 * @param[in] txatif : Buffer to be read. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_event_attempt_get ( mcp251863_t *ctx, uint32_t *txatif );

/**
 * @brief Transmit FIFO Index Get.
 * @details Reads Transmit FIFO Index.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.  
 * @param[in] idx : Update data. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_index_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *idx );

/**
 * @brief Transmit FIFO Event Enable.
 * @details Enables Transmit FIFO interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.  
 * @param[in] flags : Interrupt Enables. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_event_enable( mcp251863_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Transmit FIFO Event Disable.
 * @details Disables Transmit FIFO interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.  
 * @param[in] flags : Interrupt Enables. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_event_disable ( mcp251863_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Transmit FIFO Event Clear.
 * @details Clears Transmit FIFO Attempts Exhausted interrupt Flag.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_transmit_channel_event_attempt_clear ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Receive FIFO Event Get.
 * @details Reads Receive FIFO interrupt Flags.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.  
 * @param[in] flags : Interrupt Enables.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_event_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *flags );

/**
 * @brief Get pending interrupts of all receive FIFOs.
 * @details Function for get pending interrupts of all receive FIFOs.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] rxif :  Buffer to be read.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_event_get ( mcp251863_t *ctx, uint32_t *rxif );

/**
 * @brief Get pending RXOVIF of all receive FIFOs.
 * @details Function for get pending RXOVIF of all receive FIFOs.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] rxovif : Buffer to be read.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_event_overflow_get ( mcp251863_t *ctx, uint32_t *rxovif );

/**
 * @brief Receive FIFO Index Get.
 * @details Function for getting Receive FIFO Index.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param idx : Transmit Channel Index to be read.  
 * @returns  Transmit channel index.
 */
int8_t mcp251863_receive_channel_index_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *idx );

/**
 * @brief Receive FIFO Event Enable
 * @details Enables Receive FIFO interrupts
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[in] flags : Interrupt Enables.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_event_enable ( mcp251863_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Receive FIFO Event Disable.
 * @details Disables Receive FIFO interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] cannel : Channel.
 * @param[in] flags : Interrupt Disables.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_event_disable ( mcp251863_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Receive FIFO Event Clear.
 * @details Clears Receive FIFO Overflow interrupt Flag.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param cannel : Channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_receive_channel_event_overflow_clear ( mcp251863_t *ctx, uint8_t channel );

/**
 * @brief Transmit Event FIFO Event Get.
 * @details Reads Transmit Event FIFO interrupt Flags.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] flags : Interrupt flags.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_event_get ( mcp251863_t *ctx, uint8_t* flags );

/**
 * @brief Transmit Event FIFO Event Enable.
 * @details Enables Transmit Event FIFO interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] flags : Interrupt enables.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_event_enable ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief Transmit Event FIFO Event Disable.
 * @details Disables Transmit Event FIFO interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] flags : Interrupt disables.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_event_disable ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief Transmit Event FIFO Event Clear.
 * @details Clears Transmit Event FIFO Overflow interrupt Flag.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] flags : Interrupt flags.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_tef_event_overflow_clear ( mcp251863_t *ctx );

/**
 * @brief Transmit Error Count Get.
 * @details Function for clearing Transmit Event FIFO Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param tec : Buffer to be read.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_error_count_transmit_get ( mcp251863_t *ctx, uint8_t *tec );

/**
 * @brief Receive Error Count Get.
 * @details Function for getting Receive Error Count.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] rec : Buffer to be read.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_error_count_receive_get ( mcp251863_t *ctx, uint8_t *rec );

/**
 * @brief Error State Get.
 * @details Function for getting Error State.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] flags : Interrupt flags.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_error_state_get ( mcp251863_t *ctx, uint8_t *flags );

/**
 * @brief Error Counts and Error State Get.
 * @details Returns content of complete CITREC.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] tec : Buffer to be read. 
 * @param[out] rec : Buffer to be read. 
 * @param[out] flags : Interrupt flags.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_error_count_state_get ( mcp251863_t *ctx, uint8_t *tec, uint8_t *rec, uint8_t *flags );

/**
 * @brief Get Bus Diagnostic Registers: all data_ at once, since we want to keep them in synch
 * @details Function for getting Bus Diagnostic Registers: 
 * all data_ at once, since we want to keep them in synch
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param bus_diag : Bus diag object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bus_diagnostics_get ( mcp251863_t *ctx, mcp251863_bus_diag_t *bus_diag );

/**
 * @brief Clear Bus Diagnostic Registers.
 * @details Function for clearing Bus Diagnostic Registers.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bus_diagnostics_clear ( mcp251863_t *ctx );

/**
 * @brief Enable ECC.
 * @details Function for enabling ECC.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_enable ( mcp251863_t *ctx );

/**
 * @brief Disable ECC.
 * @details Function for disabling ECC.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_disable ( mcp251863_t *ctx );

/**
 * @brief ECC Event Get.
 * @details Function for getting ECC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation.
 * @param flags : Interrupt flags. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_event_get ( mcp251863_t *ctx, uint8_t *flags );

/**
 * @brief Set ECC Parity.
 * @details Function for setting ECC Parity.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param parity : Write command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_parity_set ( mcp251863_t *ctx, uint8_t parity );

/**
 * @brief Get ECC Parity.
 * @details Function for getting ECC Parity.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param parity : Data to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_parity_get ( mcp251863_t *ctx, uint8_t *parity );

/**
 * @brief Get ECC Error Address.
 * @details Function for getting ECC Error Address.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] address : Adress to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_error_address_get ( mcp251863_t *ctx, uint16_t *address );

/**
 * @brief  ECC Event Enable.
 * @details Function for enabling ECC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param flags : ECC interrupt.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_event_enable ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief  ECC Event Disable.
 * @details Function for disabling ECC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param flags : ECC interrupt.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_event_disable ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief  ECC Event Clear.
 * @details Function for clearing ECC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param flags : ECC status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ecc_event_clear ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Enable.
 * @details Function for enabling CRC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param flags : Interrupt control bits of CRC Register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_crc_event_enable ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Disnable.
 * @details Function for disabling CRC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] flags : Interrupt control bits of CRC Register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_crc_event_disable ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Clear.
 * @details Function for clearing CRC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] flags : Interrupt flags of CRC Register
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_crc_event_clear ( mcp251863_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Get.
 * @details Function for getting CRC Event.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] flags : Interrupt flags of CRC Register
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_crc_event_get ( mcp251863_t *ctx, uint8_t *flags );

/**
 * @brief  Get CRC Value from device.
 * @details Function for getting CRC Value from device.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] crc : CRC value from CRC Register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_crc_value_get ( mcp251863_t *ctx, uint16_t *crc );

/**
 * @brief  Initialize RAM.
 * @details Function for initialising RAM.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] rx_data : Data_pointer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_ram_init ( mcp251863_t *ctx, uint8_t rx_data );

/**
 * @brief  Time Stamp Enable.
 * @details Function for enabling Time Stamp.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_time_stamp_enable ( mcp251863_t *ctx );

/**
 * @brief  Time Stamp Disable.
 * @details Function for disabling Time Stamp.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_time_stamp_disable ( mcp251863_t *ctx );

/**
 * @brief  Time Stamp Get.
 * @details Function for getting Time Stamp.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[out] time_stamp : Buffer to be read. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_time_stamp_get ( mcp251863_t *ctx, uint32_t *time_stamp );

/**
 * @brief  Time Stamp Set
 * @details Function for setting Time Stamp.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] time_stamp : Time stamp data to be write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_time_stamp_set ( mcp251863_t *ctx, uint32_t ts );

/**
 * @brief  Time Stamp Mode Configure
 * @details Function for configuring Time Stamp Mode.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] mode : Mode. data to be write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_time_stamp_mode_configure ( mcp251863_t *ctx, uint8_t mode );

/**
 * @brief Time Stamp Prescaler Set.
 * @details Function for setting Time Stamp Prescaler.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] time_stamp : Time stamp prescaler.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_time_stamp_prescaler_set ( mcp251863_t *ctx, uint16_t time_stamp );

/**
 * @brief  Enable oscillator to wake-up from sleep.
 * @details Function for enabling oscillator to wake-up from sleep.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_oscillator_enable ( mcp251863_t *ctx );

/**
 * @brief  Set Oscillator Control
 *
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param ctrl :  Div ctl  object.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * 
 * @details Function for setting Oscillator Control
 */
err_t mcp251863_oscillator_control_set ( mcp251863_t *ctx, mcp251863_div_ctl_t ctrl );

/**
 * @brief  Reset Oscillator Control.
 * @details Function for resetting Oscillator Control.
 * @param[in] ctrl : Div ctrl object.
 * @return Nothing. 
 */
void mcp251863_oscillator_control_object_reset ( mcp251863_div_ctl_t *ctrl );

/**
 * @brief  Get Oscillator Status.
 * @details Function for gettting Oscillator Status.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] status : Oscillator status object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_oscillator_status_get ( mcp251863_t *ctx, mcp251863_osc_sta_t *status );

/**
 * @brief  Configure Bit Time registers (based on CAN clock speed).
 * @details Function for configuring Bit Time registers ( based on CAN clock speed ).
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @param[in] clk : Decode clk. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure ( mcp251863_t *ctx, uint8_t bit_time, uint8_t clk );

/**
 * @brief  Configure Nominal bit time for 40MHz system clock.
 * @details Function for configuring Nominal bit time for 40MHz system clock.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure_nominal_40_mhz ( mcp251863_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Data bit time for 40MHz system clock.
 * @details Function for configuring Data bit time for 40MHz system clock.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure_data_40_mhz ( mcp251863_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Nominal bit time for 20MHz system clock.
 * @details Function for configuring Nominal bit time for 20MHz system clock.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure_nominal_20_mhz ( mcp251863_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Nominal bit time for 20MHz system clock.
 * @details Function for configuring Nominal bit time for 20MHz system clock.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure_data_20_mhz ( mcp251863_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Nominal bit time for 10MHz system clock.
 * @details Function for configuring Nominal bit time for 10MHz system clock.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure_nominal_10_mhz ( mcp251863_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Data bit time for 10MHz system clock.
 * @details Function for configuring Data bit time for 10MHz system clock.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] bit_time : Bit time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_bit_time_configure_data_10_mhz ( mcp251863_t *ctx, uint8_t bit_time );

/**
 * @brief  Initialize GPIO Mode.
 * @details Function for initialising GPIO Mode.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] gpio0 : GPIO 0.
 * @param[in] gpio1 : GPIO 1.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_mode_configure ( mcp251863_t *ctx, uint8_t gpio0, uint8_t gpio1 );

/**
 * @brief  Initialize GPIO Direction.
 * @details Function for initialising GPIO Direction.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] gpio0 : GPIO 0.
 * @param[in] gpio1 : GPIO 1.  
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_direction_configure ( mcp251863_t *ctx, uint8_t gpio0, uint8_t gpio1 );

/**
 * @brief  Enable Transceiver Standby Control.
 * @details Function for enabling Transceiver Standby Control.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_standby_control_enable ( mcp251863_t *ctx );

/**
 * @brief  Disable Transceiver Standby Control.
 * @details Function for disabling Transceiver Standby Control.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_standby_control_disable ( mcp251863_t *ctx );

/**
 * @brief  Configure Open Drain Interrupts
 * @details Function for configuring Open Drain Interrupts.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] mode : Mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_interrupt_pins_open_drain_configure ( mcp251863_t *ctx, uint8_t mode );

/**
 * @brief  Configure Open Drain TXCAN.
 * @details Function for configuring Open Drain TXCAN.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] mode : Mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_transmit_pin_open_drain_configure ( mcp251863_t *ctx, uint8_t mode );

/**
 * @brief  GPIO Output Pin Set.
 * @details Function for setting GPIO Output Pin.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] pos : Pin flag.
 * @param[in] latch : Pin latch.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_pin_set ( mcp251863_t *ctx, uint8_t pos, uint8_t latch );

/**
 * @brief  Input Pin Read
 * @details Function for reading GPIO Input Pin Read.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] pos : Pin flag.
 * @param[in] state : State to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_pin_read ( mcp251863_t *ctx, uint8_t pos, uint8_t *state );

/**
 * @brief  Configure CLKO Pin
 * @details Function for configuring CLKO Pin.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] mode : Mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Read error,
 *         @li @c -2 - Write error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_gpio_clock_output_configure ( mcp251863_t *ctx, int8_t mode );

/**
 * @brief  DLC to number of actual data_bytes conversion.
 * @details Function for conversion DLC to number of actual data bytes.
 * @param[in] dlc : DLC
 * @returns  Data pointerbytes in object.
 */
uint32_t mcp251863_dlc_to_data_bytes ( uint8_t dlc );

/**
 * @brief  FIFO Index Get.
 * @details Function for getting FIFO Index.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] channel : Channel.
 * @param[in] data_out : Buffer for status register to be read
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mcp251863_fifo_index_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *data_out );

/**
 * @brief  Calculate CRC16.
 * @details Function for calculate CRC16.
 * @param[in] ctx : Click context object.
 * See #mcp251863_t object definition for detailed explanation. 
 * @param[in] data_pointer : Data pointer.
 * @param[in] size : Size of array ( table for CRC calculation ).
 * @returns CRC base 
 */
uint16_t mcp251863_calculate_crc16 ( uint8_t *data_pointer, uint16_t size );

/**
 * @brief  Data bytes to DLC conversion
 * @details Function for conversion Data bytes to DLC 
 * @param[in] num : Number of bytes
 * @returns Dcl macro value.
 */
uint8_t mcp251863_data_bytes_to_dlc ( uint8_t num );

#ifdef __cplusplus
}
#endif
#endif // MCP251863_H

/*! @} */ // mcp251863

// ------------------------------------------------------------------------ END

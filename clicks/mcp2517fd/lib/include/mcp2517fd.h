/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for MCP2517FD Click driver.
 *
 * \addtogroup mcp2517fd MCP2517FD Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MCP2517DF_H
#define MCP2517DF_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define MCP2517DF_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.stby  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.clko  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup mcp2517fd_var Variables
 * \{
 */

// Device selection
#define MCP2517FD

// Revision
//#define REV_A
#define REV_B

// Before B0 address of filter registers was fixed
#ifdef REV_A
    #define FIXED_FILTER_ADDRESS
#endif

// Number of implemented FIFOs
#ifndef FPGA
    #define MCP2517FD_FIFO_08TO15_IMPLEMENTED
    #define MCP2517FD_FIFO_16TO31_IMPLEMENTED
#endif

// Number of implemented Filters
#ifndef FPGA
    #define MCP2517FD_FILT_08TO15_IMPLEMENTED
    #define MCP2517FD_FILT_16TO31_IMPLEMENTED
#endif

// Internal oscillator implemented
#ifdef MCP2520FD
    #define CAN_INTERNAL_OSC_PRESENT
#endif

// Restricted Operation Mode implemented
#ifdef REV_B
    #define CAN_RESTRICTED_MODE_PRESENT
#endif

// Transmit Queue
#ifdef REV_B
    #define CAN_TXQUEUE_IMPLEMENTED
#endif

// Up to A1 silicon we had to multiply user address by 4.
#ifdef REV_A
    #define USERADDRESS_TIMES_FOUR
#endif

#ifdef MCP2517FD
    #define N_MCP2517_CTRL_REGS                         5
#endif
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MCP2517DF_RETVAL  uint8_t
#define MCP2517FD_P    const uint8_t*

#define MCP2517DF_OK                                    0x00
#define MCP2517DF_INIT_ERROR                            0xFF
/** \} */

/**
 * \defgroup other_macros Other Macros
 * \{
 */
#define MAX_TXQUEUE_ATTEMPTS                            50
#define TX_REQUEST_ID                                   0x300
#define TX_RESPONSE_ID                                  0x301

#define CRCBASE                                         0xFFFF
#define CRCUPPER                                        1
#define DRV_CANFDSPI_INDEX_0                            0
#define SPI_DEFAULT_BUFFER_LENGTH                       96


// Select ISO/non-ISO CRC
#define ISO_CRC                                         1

// Maximum Size of TX/RX Object
#define MAX_MSG_SIZE                                    76

// Maximum number of data_ bytes in message
#define MAX_DATA_BYTES                                  64
/** \} */

/**
 * \defgroup spi_instruction_set SPI Instruction Set
 * \{
 */
#define MCP2517FD_INS_RESET                             0x00
#define MCP2517FD_INS_READ                              0x03
#define MCP2517FD_INS_READ_CRC                          0x0B
#define MCP2517FD_INS_WRITE                             0x02
#define MCP2517FD_INS_WRITE_CRC                         0x0A
#define MCP2517FD_INS_WRITE_SAFE                        0x0C
/** \} */

/**
 * \defgroup reg_addr Register Addresses 
 * \{
 */
#define MCP2517FD_REG_CiCON                             0x000
#define MCP2517FD_REG_CiNBTCFG                          0x004
#define MCP2517FD_REG_CiDBTCFG                          0x008
#define MCP2517FD_REG_CiTDC                             0x00C

#define MCP2517FD_REG_CiTBC                             0x010
#define MCP2517FD_REG_CiTSCON                           0x014
#define MCP2517FD_REG_CiVEC                             0x018
#define MCP2517FD_REG_CiINT                             0x01C
#define MCP2517FD_REG_CiINTFLAG                         MCP2517FD_REG_CiINT
#define MCP2517FD_REG_CiINTENABLE                       ( MCP2517FD_REG_CiINT + 2 ) 

#define MCP2517FD_REG_CiRXIF                            0x020
#define MCP2517FD_REG_CiTXIF                            0x024
#define MCP2517FD_REG_CiRXOVIF                          0x028
#define MCP2517FD_REG_CiTXATIF                          0x02C

#define MCP2517FD_REG_CiTXREQ                           0x030
#define MCP2517FD_REG_CiTREC                            0x034
#define MCP2517FD_REG_CiBDIAG0                          0x038
#define MCP2517FD_REG_CiBDIAG1                          0x03C

#define MCP2517FD_REG_CiTEFCON                          0x040
#define MCP2517FD_REG_CiTEFSTA                          0x044
#define MCP2517FD_REG_CiTEFUA                           0x048
#define MCP2517FD_REG_CiFIFOBA                          0x04C

#define MCP2517FD_REG_CiFIFOCON                         0x050
#define MCP2517FD_REG_CiFIFOSTA                         0x054
#define MCP2517FD_REG_CiFIFOUA                          0x058
#define MCP2517FD_FIFO_OFFSET                           ( 3 * 4 )
#define MCP2517FD_FILTER_OFFSET                         ( 2 * 4 )

#ifdef CAN_TXQUEUE_IMPLEMENTED
    #define MCP2517FD_REG_CiTXQCON                      0x050
    #define MCP2517FD_REG_CiTXQSTA                      0x054
    #define MCP2517FD_REG_CiTXQUA                       0x058
#endif

#ifdef FIXED_FILTER_ADDRESS
    #define MCP2517FD_REG_CiFLTCON                          0x1D0
    #define MCP2517FD_REG_CiFLTOBJ                          0x1F0
    #define MCP2517FD_REG_CiMASK                            0x1F4
#else
    #define MCP2517FD_REG_CiFLTCON                         ( MCP2517FD_REG_CiFIFOCON + ( MCP2517FD_FIFO_OFFSET * MCP2517FD_FIFO_TOTAL_CHANNELS ) )
    #define MCP2517FD_REG_CiFLTOBJ                         ( MCP2517FD_REG_CiFLTCON + MCP2517FD_FIFO_TOTAL_CHANNELS )
    #define MCP2517FD_REG_CiMASK                           ( MCP2517FD_REG_CiFLTOBJ + 4 )
#endif
/** \} */

/**
 * \defgroup mcp2517_specific MCP2517 Specific
 * \{
 */
#define MCP2517FD_REG_OSC                               0xE00
#define MCP2517FD_REG_IOCON                             0xE04
#define MCP2517FD_REG_CRC                               0xE08
#define MCP2517FD_REG_ECCCON                            0xE0C
#define MCP2517FD_REG_ECCSTA                            0xE10
/** \} */

/**
 * \defgroup ram_addresses RAM addresses
 * \{
 */
#define MCP2517FD_RAM_SIZE                              2048
#define MCP2517FD_RAMADDR_START                         0x400
#define MCP2517FD_RAMADDR_END                           ( MCP2517FD_RAMADDR_START + MCP2517FD_RAM_SIZE )

#define MCP2517FD_LOW_POWER_MODE_EN                     0x08
#define MCP2517FD_LOW_POWER_MODE_DIS                    0x00
#define MCP2517FD_WAKEUP_INTERR_EN                      0x40
/** \} */

/**
 * \defgroup can_fifo_channels CAN FIFO Channels
 * \{
 */
#define MCP2517FD_FIFO_CH0                              0
#define MCP2517FD_FIFO_CH1                              1
#define MCP2517FD_FIFO_CH2                              2
#define MCP2517FD_FIFO_CH3                              3
#define MCP2517FD_FIFO_CH4                              4
#define MCP2517FD_FIFO_CH5                              5
#define MCP2517FD_FIFO_CH6                              6
#define MCP2517FD_FIFO_CH7                              7

#ifdef MCP2517FD_FIFO_08TO15_IMPLEMENTED
    #define MCP2517FD_FIFO_CH8                          8
    #define MCP2517FD_FIFO_CH9                          9
    #define MCP2517FD_FIFO_CH10                         10
    #define MCP2517FD_FIFO_CH11                         11
    #define MCP2517FD_FIFO_CH12                         12
    #define MCP2517FD_FIFO_CH13                         13
    #define MCP2517FD_FIFO_CH14                         14
    #define MCP2517FD_FIFO_CH15                         15
#endif

#ifdef MCP2517FD_FIFO_16TO31_IMPLEMENTED
    #define MCP2517FD_FIFO_CH16                         16
    #define MCP2517FD_FIFO_CH17                         17
    #define MCP2517FD_FIFO_CH18                         18
    #define MCP2517FD_FIFO_CH19                         19
    #define MCP2517FD_FIFO_CH20                         20
    #define MCP2517FD_FIFO_CH21                         21
    #define MCP2517FD_FIFO_CH22                         22
    #define MCP2517FD_FIFO_CH23                         23
    #define MCP2517FD_FIFO_CH24                         24
    #define MCP2517FD_FIFO_CH25                         25
    #define MCP2517FD_FIFO_CH26                         26
    #define MCP2517FD_FIFO_CH27                         27
    #define MCP2517FD_FIFO_CH28                         28
    #define MCP2517FD_FIFO_CH29                         29
    #define MCP2517FD_FIFO_CH30                         30
    #define MCP2517FD_FIFO_CH31                         31
#endif

#define MCP2517FD_FIFO_TOTAL_CHANNELS                   32

#ifdef CAN_TXQUEUE_IMPLEMENTED
    #define MCP2517FD_FIFO_FIRST_CHANNEL                MCP2517FD_FIFO_CH1
    #define CAN_TXQUEUE_CH0                             MCP2517FD_FIFO_CH0
#else
    #define MCP2517FD_FIFO_FIRST_CHANNEL                MCP2517FD_FIFO_CH0
#endif
/** \} */

/**
 * \defgroup can_filter_channels CAN Filter Channels
 * \{
 */
#define MCP2517FD_FILT0                                 0
#define MCP2517FD_FILT1                                 1
#define MCP2517FD_FILT2                                 2
#define MCP2517FD_FILT3                                 3
#define MCP2517FD_FILT4                                 4
#define MCP2517FD_FILT5                                 5
#define MCP2517FD_FILT6                                 6
#define MCP2517FD_FILT7                                 7

#ifdef MCP2517FD_FILT_08TO15_IMPLEMENTED
    #define MCP2517FD_FILT8                             8
    #define MCP2517FD_FILT9                             9
    #define MCP2517FD_FILT10                            10
    #define MCP2517FD_FILT11                            11
    #define MCP2517FD_FILT12                            12
    #define MCP2517FD_FILT13                            13
    #define MCP2517FD_FILT14                            14
    #define MCP2517FD_FILT15                            15
#endif

#ifdef MCP2517FD_FILT_16TO31_IMPLEMENTED
    #define MCP2517FD_FILT16                            16
    #define MCP2517FD_FILT17                            17
    #define MCP2517FD_FILT18                            18
    #define MCP2517FD_FILT19                            19
    #define MCP2517FD_FILT20                            20
    #define MCP2517FD_FILT21                            21
    #define MCP2517FD_FILT22                            22
    #define MCP2517FD_FILT23                            23
    #define MCP2517FD_FILT24                            24
    #define MCP2517FD_FILT25                            25
    #define MCP2517FD_FILT26                            26
    #define MCP2517FD_FILT27                            27
    #define MCP2517FD_FILT28                            28
    #define MCP2517FD_FILT29                            29
    #define MCP2517FD_FILT30                            30
    #define MCP2517FD_FILT31                            31
#endif

#define MCP2517FD_FILT_TOTAL                            32
/** \} */

/**
 * \defgroup can_operation_modes CAN Operation Modes
 * \{
 */
#define MCP2517FD_NORMAL_MODE                           0x00
#define MCP2517FD_SLEEP_MODE                            0x01
#define MCP2517FD_INT_LOOP_MODE                         0x02
#define MCP2517FD_LISTEN_ONLY_MODE                      0x03
#define MCP2517FD_CONFIG_MODE                           0x04
#define MCP2517FD_EXT_LOOP_MODE                         0x05
#define MCP2517FD_CLASSIC_MODE                          0x06
#define MCP2517FD_RESTRICT_MODE                         0x07
#define MCP2517FD_INVALID_MODE                          0xFF
/** \} */

/**
 * \defgroup Transmit Bandwidth Sharing transmit_bandwidth_sharing
 * \{
 */
#define MCP2517FD_TXBWS_NO_DELAY                        0
#define MCP2517FD_TXBWS_2                               1
#define MCP2517FD_TXBWS_4                               2
#define MCP2517FD_TXBWS_8                               3
#define MCP2517FD_TXBWS_16                              4
#define MCP2517FD_TXBWS_32                              5
#define MCP2517FD_TXBWS_64                              6
#define MCP2517FD_TXBWS_128                             7
#define MCP2517FD_TXBWS_256                             8
#define MCP2517FD_TXBWS_512                             9
#define MCP2517FD_TXBWS_1024                            10
#define MCP2517FD_TXBWS_2048                            11
#define MCP2517FD_TXBWS_4096                            12
/** \} */

/**
 * \defgroup wake_up_filter_time Wake-up Filter Time
 * \{
 */
#define MCP2517FD_WFT00                                 0
#define MCP2517FD_WFT01                                 1
#define MCP2517FD_WFT10                                 2
#define MCP2517FD_WFT11                                 3
/** \} */

/**
 * \defgroup data_byte_filter_number Data Byte Filter Number
 * \{
 */
#define MCP2517FD_DNET_FILT_DISABLE                     0
#define MCP2517FD_DNET_FILT_SIZE_1_BIT                  1
#define MCP2517FD_DNET_FILT_SIZE_2_BIT                  2
#define MCP2517FD_DNET_FILT_SIZE_3_BIT                  3
#define MCP2517FD_DNET_FILT_SIZE_4_BIT                  4
#define MCP2517FD_DNET_FILT_SIZE_5_BIT                  5
#define MCP2517FD_DNET_FILT_SIZE_6_BIT                  6
#define MCP2517FD_DNET_FILT_SIZE_7_BIT                  7
#define MCP2517FD_DNET_FILT_SIZE_8_BIT                  8
#define MCP2517FD_DNET_FILT_SIZE_9_BIT                  9
#define MCP2517FD_DNET_FILT_SIZE_10_BIT                 10
#define MCP2517FD_DNET_FILT_SIZE_11_BIT                 11
#define MCP2517FD_DNET_FILT_SIZE_12_BIT                 12
#define MCP2517FD_DNET_FILT_SIZE_13_BIT                 13
#define MCP2517FD_DNET_FILT_SIZE_14_BIT                 14
#define MCP2517FD_DNET_FILT_SIZE_15_BIT                 15
#define MCP2517FD_DNET_FILT_SIZE_16_BIT                 16
#define MCP2517FD_DNET_FILT_SIZE_17_BIT                 17
#define MCP2517FD_DNET_FILT_SIZE_18_BIT                 18
/** \} */

/**
 * \defgroup fifo_payload_size FIFO Payload Size
 * \{
 */
#define MCP2517FD_PLSIZE_8                              0
#define MCP2517FD_PLSIZE_12                             1
#define MCP2517FD_PLSIZE_16                             2
#define MCP2517FD_PLSIZE_20                             3
#define MCP2517FD_PLSIZE_24                             4
#define MCP2517FD_PLSIZE_32                             5
#define MCP2517FD_PLSIZE_48                             6
#define MCP2517FD_PLSIZE_64                             7
/** \} */

/**
 * \defgroup can_data_length_code CAN Data Length Code
 * \{
 */
#define MCP2517FD_DLC_0                                 0
#define MCP2517FD_DLC_1                                 1
#define MCP2517FD_DLC_2                                 2
#define MCP2517FD_DLC_3                                 3
#define MCP2517FD_DLC_4                                 4
#define MCP2517FD_DLC_5                                 5
#define MCP2517FD_DLC_6                                 6
#define MCP2517FD_DLC_7                                 7
#define MCP2517FD_DLC_8                                 8
#define MCP2517FD_DLC_12                                9
#define MCP2517FD_DLC_16                                10
#define MCP2517FD_DLC_20                                11
#define MCP2517FD_DLC_24                                12
#define MCP2517FD_DLC_32                                13
#define MCP2517FD_DLC_48                                14
#define MCP2517FD_DLC_64                                15
/** \} */

/**
 * \defgroup can_rx_fifo_status CAN RX FIFO Status
 * \{
 */
#define MCP2517FD_RX_FIFO_EMPTY                         0
#define MCP2517FD_RX_FIFO_STATUS_MASK                   0x0F
#define MCP2517FD_RX_FIFO_NOT_EMPTY                     0x01
#define MCP2517FD_RX_FIFO_HALF_FULL                     0x02
#define MCP2517FD_RX_FIFO_FULL                          0x04
#define MCP2517FD_RX_FIFO_OVERFLOW                      0x08
/** \} */

/**
 * \defgroup can_tx_fifo_status CAN TX FIFO Status
 * \{
 */
#define MCP2517FD_TX_FIFO_FULL                          0
#define MCP2517FD_TX_FIFO_STATUS_MASK                   0x1F7
#define MCP2517FD_TX_FIFO_NOT_FULL                      0x01
#define MCP2517FD_TX_FIFO_HALF_FULL                     0x02
#define MCP2517FD_TX_FIFO_EMPTY                         0x04
#define MCP2517FD_TX_FIFO_ATTEMPTS_EXHAUSTED            0x10
#define MCP2517FD_TX_FIFO_ERROR                         0x20
#define MCP2517FD_TX_FIFO_ARBITRATION_LOST              0x40
#define MCP2517FD_TX_FIFO_ABORTED                       0x80
#define MCP2517FD_TX_FIFO_TRANSMITTING                  0x100
/** \} */

/**
 * \defgroup can_tef_fifo_status CAN TEF FIFO Status
 * \{
 */
#define MCP2517FD_TEF_FIFO_EMPTY                        0
#define MCP2517FD_TEF_FIFO_STATUS_MASK                  0x0F
#define MCP2517FD_TEF_FIFO_NOT_EMPTY                    0x01
#define MCP2517FD_TEF_FIFO_HALF_FULL                    0x02
#define MCP2517FD_TEF_FIFO_FULL                         0x04
#define MCP2517FD_TEF_FIFO_OVERFLOW                     0x08
/** \} */

/**
 * \defgroup can_tx_fifo_event_interrupts CAN TX FIFO Event (Interrupts)
 * \{
 */
#define MCP2517FD_TX_FIFO_NO_EVENT                      0
#define MCP2517FD_TX_FIFO_ALL_EVENTS                    0x17
#define MCP2517FD_TX_FIFO_NOT_FULL_EVENT                0x01
#define MCP2517FD_TX_FIFO_HALF_FULL_EVENT               0x02
#define MCP2517FD_TX_FIFO_EMPTY_EVENT                   0x04
#define MCP2517FD_TX_FIFO_ATTEMPTS_EXHAUSTED_EVENT      0x10
/** \} */

/**
 * \defgroup can_rx_fifo_event_interrupts CAN RX FIFO Event (Interrupts)
 * \{
 */
#define MCP2517FD_RX_FIFO_NO_EVENT                      0
#define MCP2517FD_RX_FIFO_ALL_EVENTS                    0x0F
#define MCP2517FD_RX_FIFO_NOT_EMPTY_EVENT               0x01
#define MCP2517FD_RX_FIFO_HALF_FULL_EVENT               0x02
#define MCP2517FD_RX_FIFO_FULL_EVENT                    0x04
#define MCP2517FD_RX_FIFO_OVERFLOW_EVENT                0x08
/** \} */

/**
 * \defgroup can_tef_fifo_event_interrupts CAN TEF FIFO Event (Interrupts)
 * \{
 */
#define MCP2517FD_TEF_FIFO_NO_EVENT                     0
#define MCP2517FD_TEF_FIFO_ALL_EVENTS                   0x0F
#define MCP2517FD_TEF_FIFO_NOT_EMPTY_EVENT              0x01
#define MCP2517FD_TEF_FIFO_HALF_FULL_EVENT              0x02
#define MCP2517FD_TEF_FIFO_FULL_EVENT                   0x04
#define MCP2517FD_TEF_FIFO_OVERFLOW_EVENT               0x08
/** \} */

/**
 * \defgroup can_module_event_interrupts CAN Module Event (Interrupts)
 * \{
 */
#define MCP2517FD_NO_EVENT                              0
#define MCP2517FD_ALL_EVENTS                            0xFF1F
#define MCP2517FD_TX_EVENT                              0x0001
#define MCP2517FD_RX_EVENT                              0x0002
#define MCP2517FD_TIME_BASE_COUNTER_EVENT               0x0004
#define MCP2517FD_OPERATION_MODE_CHANGE_EVENT           0x0008
#define MCP2517FD_TEF_EVENT                             0x0010

#define MCP2517FD_RAM_ECC_EVENT                         0x0100
#define MCP2517FD_SPI_CRC_EVENT                         0x0200
#define MCP2517FD_TX_ATTEMPTS_EVENT                     0x0400
#define MCP2517FD_RX_OVERFLOW_EVENT                     0x0800
#define MCP2517FD_SYSTEM_ERROR_EVENT                    0x1000
#define MCP2517FD_BUS_ERROR_EVENT                       0x2000
#define MCP2517FD_BUS_WAKEUP_EVENT                      0x4000
#define MCP2517FD_RX_INVALID_MESSAGE_EVENT              0x8000
/** \} */

/**
 * \defgroup can_bit_time_setup_arbitration_data_bit_phase CAN Bit Time Setup: Arbitration/Data Bit Phase
 * \{
 */
#define MCP2517FD_500K_1M                               0
#define MCP2517FD_500K_2M                               1
#define MCP2517FD_500K_3M                               2
#define MCP2517FD_500K_4M                               3
#define MCP2517FD_500K_5M                               4
#define MCP2517FD_500K_6M7                              5
#define MCP2517FD_500K_8M                               6
#define MCP2517FD_500K_10M                              7
#define MCP2517FD_250K_500K                             8
#define MCP2517FD_250K_833K                             9
#define MCP2517FD_250K_1M                               10
#define MCP2517FD_250K_1M5                              11
#define MCP2517FD_250K_2M                               12
#define MCP2517FD_250K_3M                               13
#define MCP2517FD_250K_4M                               14
#define MCP2517FD_1000K_4M                              15
#define MCP2517FD_1000K_8M                              16
#define MCP2517FD_125K_500K                             17
/** \} */

/**
 * \defgroup can_nominal_bit_time_setup CAN Nominal Bit Time Setup
 * \{
 */
#define MCP2517FD_NBT_125K                              0
#define MCP2517FD_NBT_250K                              1
#define MCP2517FD_NBT_500K                              2
#define MCP2517FD_NBT_1M                                3
/** \} */

/**
 * \defgroup can_data_bit_time_setup CAN Data Bit Time Setup
 * \{
 */
#define MCP2517FD_DBT_500K                              0
#define MCP2517FD_DBT_833K                              1
#define MCP2517FD_DBT_1M                                2
#define MCP2517FD_DBT_1M5                               3
#define MCP2517FD_DBT_2M                                4
#define MCP2517FD_DBT_3M                                5
#define MCP2517FD_DBT_4M                                6
#define MCP2517FD_DBT_5M                                7
#define MCP2517FD_DBT_6M7                               8
#define MCP2517FD_DBT_8M                                9
#define MCP2517FD_DBT_10M                               10
/** \} */

/**
 * \defgroup  secondary_sample_point_mode  Secondary Sample Point Mode
 * \{
 */
#define MCP2517FD_SSP_MODE_OFF                          0
#define MCP2517FD_SSP_MODE_MANUAL                       1
#define MCP2517FD_SSP_MODE_AUTO                         2
/** \} */

/**
 * \defgroup can_error_state CAN Error State
 * \{
 */
#define MCP2517FD_ERROR_FREE_STATE                      0
#define MCP2517FD_ERROR_ALL                             0x3F
#define MCP2517FD_TX_RX_WARNING_STATE                   0x01
#define MCP2517FD_RX_WARNING_STATE                      0x02
#define MCP2517FD_TX_WARNING_STATE                      0x04
#define MCP2517FD_RX_BUS_PASSIVE_STATE                  0x08
#define MCP2517FD_TX_BUS_PASSIVE_STATE                  0x10
#define MCP2517FD_TX_BUS_OFF_STATE                      0x20
/** \} */

/**
 * \defgroup  can_time_stamp_mode_select CAN Time Stamp Mode Select
 * \{
 */
#define MCP2517FD_TS_SOF                                0x00
#define MCP2517FD_TS_EOF                                0x01
#define MCP2517FD_TS_RES                                0x02
/** \} */

/**
 * \defgroup can_ecc_event CAN ECC EVENT
 * \{
 */
#define MCP2517_ECC_NO_EVENT                            0x00
#define MCP2517_ECC_ALL_EVENTS                          0x06
#define MCP2517_ECC_SEC_EVENT                           0x02
#define MCP2517_ECC_DED_EVENT                           0x04
/** \} */

/**
 * \defgroup can_crc_event CAN CRC EVENT
 * \{
 */
#define MCP2517FD_CRC_NO_EVENT                          0x00
#define MCP2517FD_CRC_ALL_EVENTS                        0x03
#define MCP2517FD_CRC_CRCERR_EVENT                      0x01
#define MCP2517FD_CRC_FORMERR_EVENT                     0x02
/** \} */

/**
 * \defgroup gpio_pin_position GPIO Pin Position
 * \{
 */
#define MCP2517FD_PIN_0                                 0
#define MCP2517FD_PIN_1                                 1
/** \} */

/**
 * \defgroup gpio_pin_modes GPIO Pin Modes
 * \{
 */
#define MCP2517FD_PINMODE_INT                           0
#define MCP2517FD_PINMODE_GPIO                          1
/** \} */

/**
 * \defgroup gpio_pin_state GPIO Pin State
 * \{
 */
#define MCP2517FD_PINOUT                                0
#define MCP2517FD_PININ                                 1
/** \} */

/**
 * \defgroup gpio_open_drain_mode GPIO Open Drain Mode
 * \{
 */
#define MCP2517FD_PINLOW                                0
#define MCP2517FD_PINHIGH                               1
/** \} */

/**
 * \defgroup clock_output_mode Clock Output Mode
 * \{
 */
#define MCP2517FD_PUSHPULL                              0
#define MCP2517FD_OPENDRAIN                             1
/** \} */

/**
 * \defgroup clock_output_mode Clock Output Mode
 * \{
 */
#define MCP2517FD_CLKO_CLOCK                            0
#define MCP2517FD_CLKO_SOF                              1
/** \} */

/**
 * \defgroup txreq_channel_bits TXREQ Channel Bits
 * \{
 */
#define MCP2517FD_TXREQ_CH0                             0x00000001
#define MCP2517FD_TXREQ_CH1                             0x00000002
#define MCP2517FD_TXREQ_CH2                             0x00000004
#define MCP2517FD_TXREQ_CH3                             0x00000008
#define MCP2517FD_TXREQ_CH4                             0x00000010
#define MCP2517FD_TXREQ_CH5                             0x00000020
#define MCP2517FD_TXREQ_CH6                             0x00000040
#define MCP2517FD_TXREQ_CH7                             0x00000080

#define MCP2517FD_TXREQ_CH8                             0x00000100
#define MCP2517FD_TXREQ_CH9                             0x00000200
#define MCP2517FD_TXREQ_CH10                            0x00000400
#define MCP2517FD_TXREQ_CH11                            0x00000800
#define MCP2517FD_TXREQ_CH12                            0x00001000
#define MCP2517FD_TXREQ_CH13                            0x00002000
#define MCP2517FD_TXREQ_CH14                            0x00004000
#define MCP2517FD_TXREQ_CH15                            0x00008000

#define MCP2517FD_TXREQ_CH16                            0x00010000
#define MCP2517FD_TXREQ_CH17                            0x00020000
#define MCP2517FD_TXREQ_CH18                            0x00040000
#define MCP2517FD_TXREQ_CH19                            0x00080000
#define MCP2517FD_TXREQ_CH20                            0x00100000
#define MCP2517FD_TXREQ_CH21                            0x00200000
#define MCP2517FD_TXREQ_CH22                            0x00400000
#define MCP2517FD_TXREQ_CH23                            0x00800000

#define MCP2517FD_TXREQ_CH24                            0x01000000
#define MCP2517FD_TXREQ_CH25                            0x02000000
#define MCP2517FD_TXREQ_CH26                            0x04000000
#define MCP2517FD_TXREQ_CH27                            0x08000000
#define MCP2517FD_TXREQ_CH28                            0x10000000
#define MCP2517FD_TXREQ_CH29                            0x20000000
#define MCP2517FD_TXREQ_CH30                            0x40000000
#define MCP2517FD_TXREQ_CH31                            0x80000000
/** \} */

/**
 * \defgroup icode ICODE
 * \{
 */

#define MCP2517FD_ICODE_FIFO_CH0                        0
#define MCP2517FD_ICODE_FIFO_CH1                        1
#define MCP2517FD_ICODE_FIFO_CH2                        2
#define MCP2517FD_ICODE_FIFO_CH3                        3
#define MCP2517FD_ICODE_FIFO_CH4                        4
#define MCP2517FD_ICODE_FIFO_CH5                        5
#define MCP2517FD_ICODE_FIFO_CH6                        6
#define MCP2517FD_ICODE_FIFO_CH7                        7

#ifdef MCP2517FD_FIFO_08TO15_IMPLEMENTED
    #define MCP2517FD_ICODE_FIFO_CH8                    8
    #define MCP2517FD_ICODE_FIFO_CH9                    9
    #define MCP2517FD_ICODE_FIFO_CH10                   10
    #define MCP2517FD_ICODE_FIFO_CH11                   11
    #define MCP2517FD_ICODE_FIFO_CH12                   12
    #define MCP2517FD_ICODE_FIFO_CH13                   13
    #define MCP2517FD_ICODE_FIFO_CH14                   14
    #define MCP2517FD_ICODE_FIFO_CH15                   15
#endif

#ifdef MCP2517FD_FIFO_16TO31_IMPLEMENTED
    #define MCP2517FD_ICODE_FIFO_CH16                   16
    #define MCP2517FD_ICODE_FIFO_CH17                   17
    #define MCP2517FD_ICODE_FIFO_CH18                   18
    #define MCP2517FD_ICODE_FIFO_CH19                   19
    #define MCP2517FD_ICODE_FIFO_CH20                   20
    #define MCP2517FD_ICODE_FIFO_CH21                   21
    #define MCP2517FD_ICODE_FIFO_CH22                   22
    #define MCP2517FD_ICODE_FIFO_CH23                   23
    #define MCP2517FD_ICODE_FIFO_CH24                   24
    #define MCP2517FD_ICODE_FIFO_CH25                   25
    #define MCP2517FD_ICODE_FIFO_CH26                   26
    #define MCP2517FD_ICODE_FIFO_CH27                   27
    #define MCP2517FD_ICODE_FIFO_CH28                   28
    #define MCP2517FD_ICODE_FIFO_CH29                   29
    #define MCP2517FD_ICODE_FIFO_CH30                   30
    #define MCP2517FD_ICODE_FIFO_CH31                   31
#endif

#define MCP2517FD_ICODE_TOTAL_CHANNELS                  32
#define MCP2517FD_ICODE_NO_INT                          64
#define MCP2517FD_ICODE_CERRIF                          65
#define MCP2517FD_ICODE_WAKIF                           66
#define MCP2517FD_ICODE_RXOVIF                          67
#define MCP2517FD_ICODE_ADDRERR_SERRIF                  68
#define MCP2517FD_ICODE_MABOV_SERRIF                    69
#define MCP2517FD_ICODE_TBCIF                           70
#define MCP2517FD_ICODE_MODIF                           71
#define MCP2517FD_ICODE_IVMIF                           72
#define MCP2517FD_ICODE_TEFIF                           73
#define MCP2517FD_ICODE_TXATIF                          74
#define MCP2517FD_ICODE_RESERVED                        75
/** \} */

/**
 * \defgroup rxcode RXCODE
 * \{
 */
#define MCP2517FD_RXCODE_FIFO_CH0                       0
#define MCP2517FD_RXCODE_FIFO_CH1                       1
#define MCP2517FD_RXCODE_FIFO_CH2                       2
#define MCP2517FD_RXCODE_FIFO_CH3                       3
#define MCP2517FD_RXCODE_FIFO_CH4                       4
#define MCP2517FD_RXCODE_FIFO_CH5                       5
#define MCP2517FD_RXCODE_FIFO_CH6                       6
#define MCP2517FD_RXCODE_FIFO_CH7                       7

#ifdef MCP2517FD_FIFO_08TO15_IMPLEMENTED
    #define MCP2517FD_RXCODE_FIFO_CH8                   8
    #define MCP2517FD_RXCODE_FIFO_CH9                   9
    #define MCP2517FD_RXCODE_FIFO_CH10                  10
    #define MCP2517FD_RXCODE_FIFO_CH11                  11
    #define MCP2517FD_RXCODE_FIFO_CH12                  12
    #define MCP2517FD_RXCODE_FIFO_CH13                  13
    #define MCP2517FD_RXCODE_FIFO_CH14                  14
    #define MCP2517FD_RXCODE_FIFO_CH15                  15
#endif

#ifdef MCP2517FD_FIFO_16TO31_IMPLEMENTED
    #define MCP2517FD_RXCODE_FIFO_CH16                  16
    #define MCP2517FD_RXCODE_FIFO_CH17                  17
    #define MCP2517FD_RXCODE_FIFO_CH18                  18
    #define MCP2517FD_RXCODE_FIFO_CH19                  19
    #define MCP2517FD_RXCODE_FIFO_CH20                  20
    #define MCP2517FD_RXCODE_FIFO_CH21                  21
    #define MCP2517FD_RXCODE_FIFO_CH22                  22
    #define MCP2517FD_RXCODE_FIFO_CH23                  23
    #define MCP2517FD_RXCODE_FIFO_CH24                  24
    #define MCP2517FD_RXCODE_FIFO_CH25                  25
    #define MCP2517FD_RXCODE_FIFO_CH26                  26
    #define MCP2517FD_RXCODE_FIFO_CH27                  27
    #define MCP2517FD_RXCODE_FIFO_CH28                  28
    #define MCP2517FD_RXCODE_FIFO_CH29                  29
    #define MCP2517FD_RXCODE_FIFO_CH30                  30
    #define MCP2517FD_RXCODE_FIFO_CH31                  31
#endif

#define MCP2517FD_RXCODE_TOTAL_CHANNELS                 32
#define MCP2517FD_RXCODE_NO_INT                         64
#define MCP2517FD_RXCODE_RESERVED                       65
/** \} */

/**
 * \defgroup txcode TXCODE
 * \{
 */
#define MCP2517FD_TXCODE_FIFO_CH0                       0
#define MCP2517FD_TXCODE_FIFO_CH1                       1
#define MCP2517FD_TXCODE_FIFO_CH2                       2
#define MCP2517FD_TXCODE_FIFO_CH3                       3
#define MCP2517FD_TXCODE_FIFO_CH4                       4
#define MCP2517FD_TXCODE_FIFO_CH5                       5
#define MCP2517FD_TXCODE_FIFO_CH6                       6
#define MCP2517FD_TXCODE_FIFO_CH7                       7

#ifdef MCP2517FD_FIFO_08TO15_IMPLEMENTED
    #define MCP2517FD_TXCODE_FIFO_CH8                   8
    #define MCP2517FD_TXCODE_FIFO_CH9                   9
    #define MCP2517FD_TXCODE_FIFO_CH10                  10
    #define MCP2517FD_TXCODE_FIFO_CH11                  11
    #define MCP2517FD_TXCODE_FIFO_CH12                  12
    #define MCP2517FD_TXCODE_FIFO_CH13                  13
    #define MCP2517FD_TXCODE_FIFO_CH14                  14
    #define MCP2517FD_TXCODE_FIFO_CH15                  15
#endif

#ifdef MCP2517FD_FIFO_16TO31_IMPLEMENTED
    #define MCP2517FD_TXCODE_FIFO_CH16                  16
    #define MCP2517FD_TXCODE_FIFO_CH17                  17
    #define MCP2517FD_TXCODE_FIFO_CH18                  18
    #define MCP2517FD_TXCODE_FIFO_CH19                  19
    #define MCP2517FD_TXCODE_FIFO_CH20                  20
    #define MCP2517FD_TXCODE_FIFO_CH21                  21
    #define MCP2517FD_TXCODE_FIFO_CH22                  22
    #define MCP2517FD_TXCODE_FIFO_CH23                  23
    #define MCP2517FD_TXCODE_FIFO_CH24                  24
    #define MCP2517FD_TXCODE_FIFO_CH25                  25
    #define MCP2517FD_TXCODE_FIFO_CH26                  26
    #define MCP2517FD_TXCODE_FIFO_CH27                  27
    #define MCP2517FD_TXCODE_FIFO_CH28                  28
    #define MCP2517FD_TXCODE_FIFO_CH29                  29
    #define MCP2517FD_TXCODE_FIFO_CH30                  30
    #define MCP2517FD_TXCODE_FIFO_CH31                  31
#endif

#define MCP2517FD_TXCODE_TOTAL_CHANNELS                 32
#define MCP2517FD_TXCODE_NO_INT                         64
#define MCP2517FD_TXCODE_RESERVED                       65
/** \} */

/**
 * \defgroup system_clock_selection System Clock Selection
 * \{
 */
#define MCP2517FD_SYSCLK_40M                            0
#define MCP2517FD_SYSCLK_20M                            1
#define MCP2517FD_SYSCLK_10M                            2
/** \} */

/**
 * \defgroup clko_divide CLKO Divide
 * \{
 */
#define MCP2517FD_CLKO_DIV1                             0
#define MCP2517FD_CLKO_DIV2                             1
#define MCP2517FD_CLKO_DIV4                             2
#define MCP2517FD_CLKO_DIV10                            3
/** \} */

/**
 * \defgroup fifo_reg FIFO registers
 * \{
 */
#define N_MCP2517FD_FIFO_REGS                           ( MCP2517FD_FIFO_TOTAL_CHANNELS * MCP2517FD_FIFO_OFFSET )
#define N_MCP2517FD_FILT_CTRL_REGS                      ( MCP2517FD_FILT_TOTAL / 4 )
#define N_MCP2517FD_FILT_OBJ_REGS                       ( MCP2517FD_FILT_TOTAL * MCP2517FD_FILTER_OFFSET )
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief CAN Configure
 */
typedef struct
{
    uint32_t d_net_filter_count : 5;
    uint32_t iso_crc_enable : 1;
    uint32_t protocol_expection_event_disable : 1;
    uint32_t wake_up_filter_enable : 1;
    uint32_t wake_up_filter_time : 2;
    uint32_t bit_rate_switch_disable : 1;
    uint32_t restrict_re_tx_attempts : 1;
    uint32_t esi_in_gateway_mode : 1;
    uint32_t system_error_to_listen_only : 1;
    uint32_t store_in_tef : 1;
    uint32_t txq_enable : 1;
    uint32_t tx_band_width_sharing : 4;

} mcp2517fd_can_cfg_t;

/**
 * @brief CAN Message Configuration
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

} mcp2517fd_config_t;


/**
 * @brief Module ID
 */
typedef uint8_t mcp2517fd_id_t;

/**
 * @brief CAN Message Time Stamp
 */
typedef uint32_t mcp2517fd_msg_time_stamp_t;

/**
 * @brief CAN Message Object ID
 */
typedef struct
{
    uint32_t sid   : 11;
    uint32_t eid   : 18;
    uint32_t sid11 : 1;
    uint32_t unimplemented1 : 2;

} mcp2517fd_msg_obj_id_t;

/**
 * @brief CAN TX Message Object Control
 */
typedef struct
{
    uint32_t dlc : 4;
    uint32_t ide : 1;
    uint32_t rtr : 1;
    uint32_t brs : 1;
    uint32_t fdf : 1;
    uint32_t esi : 1;
    uint32_t seq : 7;
    uint32_t unimplemented1 : 16;

} mcp2517fd_tx_msg_obj_ctl_t;

/**
 * @brief CAN TX Message Object
 */
typedef union
{
    struct {
        mcp2517fd_msg_obj_id_t id;
        mcp2517fd_tx_msg_obj_ctl_t ctrl;
        mcp2517fd_msg_time_stamp_t time_stamp;
    } bf;
    uint32_t word[ 3 ];
    uint8_t byte[ 12 ];

} mcp2517fd_tx_msg_obj_t;

/**
 * @brief CAN RX Message Object Control
 */
typedef struct
{
    uint32_t dlc : 4;
    uint32_t ide : 1;
    uint32_t rtr : 1;
    uint32_t brs : 1;
    uint32_t fdf : 1;
    uint32_t esi : 1;
    uint32_t unimplemented1 : 2;
    uint32_t filter_hit : 5;
    uint32_t unimplemented2 : 16;

} mcp2517fd_rx_msg_obj_ctl_t;

/**
 * @brief CAN RX Message Object
 */
typedef union
{
    struct {
        mcp2517fd_msg_obj_id_t id;
        mcp2517fd_rx_msg_obj_ctl_t ctrl;
        mcp2517fd_msg_time_stamp_t time_stamp;
    } bf;
    uint32_t word[ 3 ];
    uint8_t byte[ 12 ];

} mcp2517fd_rx_msg_obj_t;

/**
 * @brief CAN TEF Message Object
 */
typedef union
{
    struct {
        mcp2517fd_msg_obj_id_t id;
        mcp2517fd_tx_msg_obj_ctl_t ctrl;
        mcp2517fd_msg_time_stamp_t time_stamp;
    } bf;
    uint32_t word[ 3 ];
    uint8_t byte[ 12 ];

} mcp2517fd_tef_msg_obj_t;

/**
 * @brief CAN Filter Object ID
 */
typedef struct
{
    uint32_t sid : 11;
    uint32_t eid : 18;
    uint32_t sid11 : 1;
    uint32_t exide : 1;
    uint32_t unimplemented1 : 1;

} mcp2517fd_filt_obj_id_t;

/**
 * @brief Filter Object Register
 */
typedef union
{
    mcp2517fd_filt_obj_id_t bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_filt_obj_t;

/**
 * @brief CAN Mask Object ID
 */
typedef struct
{
    uint32_t msid : 11;
    uint32_t meid : 18;
    uint32_t msid11 : 1;
    uint32_t mide : 1;
    uint32_t unimplemented1 : 1;

} mcp2517fd_mask_obj_id_t;

/**
 * @brief Mask Object Register
 */
typedef union
{
    mcp2517fd_mask_obj_id_t bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_mask_obj_t;

///@}
/**
 * @name    MCP2517FD General 32-bit Registers
 ******************************************************************************/
///@{

typedef union
{
    uint8_t byte[ 4 ];
    uint32_t word;

} mcp2517fd_reg_t;

///@}
/**
 * @name Control Registers
 ******************************************************************************/
///@{

/**
 * @brief CAN Control Register
 */
typedef union
{
    struct {
        uint32_t d_net_filter_count : 5;
        uint32_t iso_crc_enable : 1;
        uint32_t protocol_exception_event_disable : 1;
        uint32_t unimplemented1 : 1;
        uint32_t wake_up_filter_enable : 1;
        uint32_t wake_up_filter_time : 2;
        uint32_t unimplemented2 : 1;
        uint32_t bit_rate_switch_disable : 1;
        uint32_t unimplemented3 : 3;
        uint32_t restrict_re_tx_attempts : 1;
        uint32_t esi_in_gateway_mode : 1;
        uint32_t system_error_to_listen_only : 1;
        uint32_t store_in_tef : 1;
        uint32_t txq_enable : 1;
        uint32_t op_mode : 3;
        uint32_t request_op_mode : 3;
        uint32_t abort_all_tx : 1;
        uint32_t tx_band_width_sharing : 4;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_ctl_t;

/**
 * @brief Transmit Queue Control Register
 */
typedef union
{
    struct {
        uint32_t tx_not_full_ie : 1;
        uint32_t unimplemented1 : 1;
        uint32_t tx_empty_ie : 1;
        uint32_t unimplemented2 : 1;
        uint32_t tx_attempt_ie : 1;
        uint32_t unimplemented3 : 2;
        uint32_t tx_enable : 1;
        uint32_t uinc : 1;
        uint32_t tx_request : 1;
        uint32_t freset : 1;
        uint32_t unimplemented4 : 5;
        uint32_t tx_priority : 5;
        uint32_t tx_attempts : 2;
        uint32_t unimplemented5 : 1;
        uint32_t fifo_size : 5;
        uint32_t pay_load_size : 3;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_tx_que_ctl_t;

/**
 * @brief Transmit Event FIFO Control Register
 */
typedef union
{
    struct {
        uint32_t tefneie : 1;
        uint32_t tefhfie : 1;
        uint32_t teffulie : 1;
        uint32_t tefovie : 1;
        uint32_t unimplemented1 : 1;
        uint32_t time_stamp_enable : 1;
        uint32_t unimplemented2 : 2;
        uint32_t uinc : 1;
        uint32_t unimplemented3 : 1;
        uint32_t freset : 1;
        uint32_t unimplemented4 : 13;
        uint32_t fifo_size : 5;
        uint32_t unimplemented5 : 3;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_tef_ctl_t;

/**
 * @brief FIFO Control Register
 */
typedef union
{
    // Receive FIFO
    struct {
        uint32_t rx_not_empty_ie : 1;
        uint32_t rx_half_full_ie : 1;
        uint32_t rx_full_ie : 1;
        uint32_t rx_over_flow_ie : 1;
        uint32_t unimplemented1 : 1;
        uint32_t rx_time_stamp_enable : 1;
        uint32_t unimplemented2 : 1;
        uint32_t tx_enable : 1;
        uint32_t uinc : 1;
        uint32_t unimplemented3 : 1;
        uint32_t freset : 1;
        uint32_t unimplemented4 : 13;
        uint32_t fifo_size : 5;
        uint32_t pay_load_size : 3;
    } rx_bf;

    // Transmit FIFO
    struct {
        uint32_t tx_not_full_ie : 1;
        uint32_t tx_half_full_ie : 1;
        uint32_t tx_empty_ie : 1;
        uint32_t unimplemented1 : 1;
        uint32_t tx_attempt_ie : 1;
        uint32_t unimplemented2 : 1;
        uint32_t rtr_enable : 1;
        uint32_t tx_enable : 1;
        uint32_t uinc : 1;
        uint32_t tx_request : 1;
        uint32_t freset : 1;
        uint32_t unimplemented3 : 5;
        uint32_t tx_priority : 5;
        uint32_t tx_attempts : 2;
        uint32_t unimplemented4 : 1;
        uint32_t fifo_size : 5;
        uint32_t pay_load_size : 3;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_fifo_ctl_t;

/**
 * @brief Filter Control Register
 */
typedef union
{
    struct {
        uint32_t buffer_pointer : 5;
        uint32_t unimplemented1 : 2;
        uint32_t enable : 1;
    } bf;
    uint8_t byte;

} mcp2517fd_filt_ctl_t;

/**
 * @brief Oscillator Control Register
 */
typedef union
{
    struct {
        uint32_t pll_enable : 1;
        uint32_t unimplemented1 : 1;
        uint32_t osc_disable : 1;
        uint32_t unimplemented2 : 1;
        uint32_t sclk_divide : 1;
        uint32_t clk_out_divide : 2;
        uint32_t unimplemented3 : 1;
        uint32_t pll_ready : 1;
        uint32_t unimplemented4 : 1;
        uint32_t osc_ready : 1;
        uint32_t unimplemented5 : 1;
        uint32_t sclk_ready : 1;
        uint32_t unimplemented6 : 19;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_osc_ctl_t;

/**
 * @brief Oscillator Control
 */
typedef struct
{
    uint32_t pll_enable : 1;
    uint32_t osc_disable : 1;
    uint32_t sclk_divide : 1;
    uint32_t clk_out_divide : 2;

} mcp2517fd_div_ctl_t;

/**
 * @brief I/O Control Register
 */
typedef union
{
    struct {
        uint32_t tris0 : 1;
        uint32_t tris1 : 1;
        uint32_t unimplemented1 : 2;
        uint32_t clear_auto_sleep_on_match : 1;
        uint32_t auto_sleep_enable : 1;
        uint32_t xcr_stby_enable : 1;
        uint32_t unimplemented2 : 1;
        uint32_t lat0 : 1;
        uint32_t lat1 : 1;
        uint32_t unimplemented3 : 5;
        uint32_t hvdetsel : 1;
        uint32_t gpio0 : 1;
        uint32_t gpio1 : 1;
        uint32_t unimplemented4 : 6;
        uint32_t pin_mode0 : 1;
        uint32_t pin_mode1 : 1;
        uint32_t unimplemented5 : 2;
        uint32_t tx_can_open_drain : 1;
        uint32_t sof_output_enable : 1;
        uint32_t int_pin_open_drain : 1;
        uint32_t unimplemented6 : 1;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_io_ctl_t;

/**
 * @brief ECC Control Register
 */
typedef union
{
    struct {/* can_fd_ubp */
        uint32_t ecc_en : 1;
        uint32_t secie : 1;
        uint32_t dedie : 1;
        uint32_t unimplemented1 : 5;
        uint32_t parity : 7;
        uint32_t unimplemented2 : 17;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_ecc_ctl_t;

///@}
/**
 * @name Configuration Registers
 ******************************************************************************/
///@{

/**
 * @brief CAN Configure
 */
typedef struct
{
    uint32_t d_net_filter_count : 5;
    uint32_t iso_crc_enable : 1;
    uint32_t protocol_expection_event_disable : 1;
    uint32_t wake_up_filter_enable : 1;
    uint32_t wake_up_filter_time : 2;
    uint32_t bit_rate_switch_disable : 1;
    uint32_t restrict_re_tx_attempts : 1;
    uint32_t esi_in_gateway_mode : 1;
    uint32_t system_error_to_listen_only : 1;
    uint32_t store_in_tef : 1;
    uint32_t txq_enable : 1;
    uint32_t tx_band_width_sharing : 4;

} T_MCP2517FD_cfg_t;

/**
 * @brief CAN Transmit Channel Configure
 */
typedef struct
{
    uint32_t rtr_enable : 1;
    uint32_t tx_priority : 5;
    uint32_t tx_attempts : 2;
    uint32_t fifo_size : 5;
    uint32_t pay_load_size : 3;

} mcp2517fd_tx_fifo_cfg_t;

/**
 * @brief CAN Transmit Queue Configure
 */
typedef struct
{
    uint32_t tx_priority : 5;
    uint32_t tx_attempts : 2;
    uint32_t fifo_size : 5;
    uint32_t pay_load_size : 3;

} mcp2517fd_tx_que_cfg_t;

/**
 * @brief CAN Receive Channel Configure
 */
typedef struct
{
    uint32_t rx_time_stamp_enable : 1;
    uint32_t fifo_size : 5;
    uint32_t pay_load_size : 3;

} mcp2517fd_rx_fifo_cfg_t;

/**
 * @brief FIFO User Address Register
 */
typedef union
{
    struct {
        uint32_t user_address : 12;
        uint32_t unimplemented1 : 20;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_fifo_user_cfg_t;

/**
 * @brief CAN Transmit Event FIFO Configure
 */
typedef struct
{
    uint32_t time_stamp_enable : 1;
    uint32_t fifo_size : 5;

} mcp2517fd_tef_cfg_t;


/**
 * @brief Nominal Bit Time Configuration Register
 */
typedef union
{
    struct {
        uint32_t swj : 7;
        uint32_t unimplemented1 : 1;/* can_fd_ubp */
        uint32_t tseg2 : 7;
        uint32_t unimplemented2 : 1;
        uint32_t tseg1 : 8;
        uint32_t brp : 8;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_nbt_cfg_t;

/**
 * @brief Data Bit Time Configuration Register
 */
typedef union
{
    struct {
        uint32_t swj : 4;
        uint32_t unimplemented1 : 4;
        uint32_t tseg2 : 4;
        uint32_t unimplemented2 : 4;
        uint32_t tseg1 : 5;
        uint32_t unimplemented3 : 3;
        uint32_t brp : 8;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_dbt_cfg_t;

/**
 * @brief Transmitter Delay Compensation Register
 */
typedef union
{
    struct {
        uint32_t tdc_value : 6;
        uint32_t unimplemented1 : 2;
        uint32_t tdc_offset : 7;
        uint32_t unimplemented2 : 1;
        uint32_t tdc_mode : 2;
        uint32_t unimplemented3 : 6;
        uint32_t sid11_enable : 1;
        uint32_t edge_filter_enable : 1;
        uint32_t unimplemented4 : 6;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_tdc_cfg_t;

/**
 * @brief Time Stamp Configuration Register
 */
typedef union
{
    struct {
        uint32_t tbc_prescaler : 10;
        uint32_t unimplemented1 : 6;
        uint32_t tbc_enable : 1;
        uint32_t time_stamp_eof : 1;
        uint32_t unimplemented2 : 14;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_ts_cfg_t;

/**
 * @brief Interrupt Enables
 */
typedef struct
{
    uint32_t txie : 1;
    uint32_t rxie : 1;
    uint32_t tbcie : 1;
    uint32_t modie : 1;
    uint32_t tefie : 1;
    uint32_t unimplemented2 : 3;

    uint32_t eccie : 1;
    uint32_t spicrcie : 1;
    uint32_t txatie : 1;
    uint32_t rxovie : 1;
    uint32_t serrie : 1;
    uint32_t cerrie : 1;
    uint32_t wakie : 1;
    uint32_t ivmie : 1;

} mcp2517fd_int_en_t;

/**
 * @brief Interrupt Configuration
 */
typedef union
{
    mcp2517fd_int_en_t ie;
    uint16_t word;
    uint8_t byte[ 2 ];

} mcp2517fd_int_cfg_t;

///@}
/**
 * @name Status Registers
 ******************************************************************************/
///@{

/**
 * @brief Interrupt Vector Register
 */
typedef union
{
    struct {
        uint32_t icode : 7;
        uint32_t unimplemented1 : 1;
        uint32_t filter_hit : 5;
        uint32_t unimplemented2 : 3;
        uint32_t tx_code : 7;
        uint32_t unimplemented3 : 1;
        uint32_t rx_code : 7;
        uint32_t unimplemented4 : 1;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_int_vec_t;

/**
 * @brief Interrupt Flags
 */
typedef struct
{
    uint32_t TXIF : 1;
    uint32_t RXIF : 1;
    uint32_t TBCIF : 1;
    uint32_t MODIF : 1;
    uint32_t TEFIF : 1;
    uint32_t unimplemented1 : 3;

    uint32_t ECCIF : 1;
    uint32_t SPICRCIF : 1;
    uint32_t TXATIF : 1;
    uint32_t RXOVIF : 1;
    uint32_t SERRIF : 1;
    uint32_t CERRIF : 1;
    uint32_t WAKIF : 1;
    uint32_t IVMIF : 1;

} mcp2517fd_int_flags_stat_t;

/**
 * @brief Interrupt Flag Register
 */
typedef union
{
    mcp2517fd_int_flags_stat_t if_stat;
    uint16_t word;
    uint8_t byte[ 2 ];

} mcp2517fd_int_flag_t;

/**
 * @brief Interrupt Register
 */
typedef union
{
    struct {
        mcp2517fd_int_flags_stat_t if_stat;
        mcp2517fd_int_en_t ie;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_int_t;

/**
 * @brief Transmit/Receive Error Count Register
 */
typedef union
{
    struct {
        uint32_t rx_error_count : 8;
        uint32_t tx_error_count : 8;
        uint32_t error_state_warning : 1;
        uint32_t rx_error_state_warning : 1;
        uint32_t tx_error_state_warning : 1;
        uint32_t rx_error_state_passive : 1;
        uint32_t tx_error_state_passive : 1;
        uint32_t tx_error_state_bus_off : 1;
        uint32_t unimplemented1 : 10;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_trec_t;

/**
 * @brief Transmit Event FIFO Status Register
 */
typedef union
{
    struct {
        uint32_t tef_not_empty_if : 1;
        uint32_t tef_half_full_if : 1;
        uint32_t tef_full_if : 1;
        uint32_t tef_ov_if : 1;
        uint32_t unimplemented1 : 28;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_tef_t;

/**
 * @brief Transmit Queue Status Register
 */
typedef union
{
    struct {
        uint32_t tx_not_full_if : 1;
        uint32_t unimplemented1 : 1;
        uint32_t tx_empty_if : 1;
        uint32_t unimplemented2 : 1;
        uint32_t tx_attempt_if : 1;
        uint32_t tx_error : 1;
        uint32_t tx_lost_arbitration : 1;
        uint32_t tx_aborted : 1;
        uint32_t fifo_index : 5;
        uint32_t unimplemented3 : 19;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_tx_que_stat_t;

/**
 * @brief FIFO Status Register
 */
typedef union
{
    // Receive FIFO
    struct {
        uint32_t rx_not_empty_if : 1;
        uint32_t rx_half_full_if : 1;
        uint32_t rx_full_if : 1;
        uint32_t rx_over_flow_if : 1;
        uint32_t unimplemented1 : 4;
        uint32_t fifo_index : 5;
        uint32_t unimplemented2 : 19;
    } rx_bf;

    // Transmit FIFO
    struct {
        uint32_t tx_not_full_if : 1;
        uint32_t tx_half_full_if : 1;
        uint32_t tx_empty_if : 1;
        uint32_t unimplemented1 : 1;
        uint32_t tx_attempt_if : 1;
        uint32_t tx_error : 1;
        uint32_t tx_lost_arbitration : 1;
        uint32_t tx_aborted : 1;
        uint32_t fifo_index : 5;
        uint32_t unimplemented2 : 19;
    } tx_bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_fifo_stat_t;

/**
 * @brief CRC Regsiter
 */
typedef union
{
    struct {
        uint32_t crc : 16;
        uint32_t crcerrif : 1;
        uint32_t ferrif : 1;
        uint32_t unimplemented1 : 6;
        uint32_t crcerrie : 1;
        uint32_t ferrie : 1;
        uint32_t unimplemented2 : 6;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_crc_t;

/**
 * @brief ECC Status Register
 */
typedef union
{
    struct {
        uint32_t unimplemented1 : 1;
        uint32_t secif : 1;
        uint32_t dedif : 1;
        uint32_t unimplemented2 : 13;
        uint32_t error_address : 12;
        uint32_t unimplemented3 : 4;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_ecc_sta_t;

/**
 * @brief Oscillator Status
 */
typedef struct
{
    uint32_t pll_ready : 1;
    uint32_t osc_ready : 1;
    uint32_t sclk_ready : 1;

} mcp2517fd_osc_sta_t;

/**
 * @brief CAN Bus Diagnostic flags
 */
typedef struct
{
    uint32_t n_bit0_err : 1;
    uint32_t n_bit1_err : 1;
    uint32_t n_ack_err : 1;
    uint32_t n_form_err : 1;
    uint32_t n_stuff_err : 1;
    uint32_t n_crc_err : 1;
    uint32_t unimplemented1 : 1;
    uint32_t txbo_err : 1;
    uint32_t d_bit0_err : 1;
    uint32_t d_bit1_err : 1;
    uint32_t unimplemented2 : 1;
    uint32_t d_form_err : 1;
    uint32_t d_stuff_err : 1;
    uint32_t d_crc_err : 1;
    uint32_t esi : 1;
    uint32_t dlc_mismatch : 1;

} mcp2517fd_bus_diag_flags_t;

/**
 * @brief CAN Bus Diagnostic Error Counts
 */
typedef struct
{
    uint8_t n_rec;
    uint8_t n_tec;
    uint8_t d_rec;
    uint8_t d_tec;

} mcp2517fd_bus_error_count_t;

/**
 * @brief CAN BUS DIAGNOSTICS
 */
typedef union
{
    struct {
        mcp2517fd_bus_error_count_t error_count;
        uint16_t error_free_msg_count;
        mcp2517fd_bus_diag_flags_t flag;
    } bf;
    uint32_t word[ 2 ];
    uint8_t byte[ 8 ];

} mcp2517fd_bus_diag_t;

/**
 * @brief Diagnostic Register 0
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

} mcp2517fd_bus_diag0_t;

/**
 * @brief Diagnostic Register 1
 */
typedef union
{
    struct {
        uint32_t error_free_msg_count : 16;

        uint32_t n_bit0_error : 1;
        uint32_t n_bit1_error : 1;
        uint32_t n_ack_error : 1;
        uint32_t n_form_error : 1;
        uint32_t n_stuff_error : 1;
        uint32_t n_crc_error : 1;
        uint32_t unimplemented1 : 1;
        uint32_t txbo_error : 1;
        uint32_t d_bit0_error : 1;
        uint32_t d_bit1_error : 1;
        uint32_t d_ack_error : 1;
        uint32_t d_form_error : 1;
        uint32_t d_stuff_error : 1;
        uint32_t d_crc_error : 1;
        uint32_t esi : 1;
        uint32_t unimplemented2 : 1;
    } bf;
    uint32_t word;
    uint8_t byte[ 4 ];

} mcp2517fd_bus_diag1_t;

/**
 * @brief CAN Message Configuration
 */
typedef struct
{
    uint16_t address; 
    uint8_t *rxd; 
    uint16_t n_bytes;
    uint8_t *txd;
    uint32_t txd_num_bytes;

} mcp2517fd_func_data_t;


/**
 * @brief CAN Message Configuration
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

    mcp2517fd_can_cfg_t             config;
    mcp2517fd_tx_fifo_cfg_t         tx_config;
    mcp2517fd_rx_fifo_cfg_t         rx_config;
    mcp2517fd_tx_msg_obj_t          tx_obj;
    mcp2517fd_rx_msg_obj_t          rx_obj;
    mcp2517fd_filt_obj_t            f_obj;
    mcp2517fd_mask_obj_t            m_obj;
    mcp2517fd_bus_diag_t            bus_diagnostics;

} mcp2517fd_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs;
    digital_out_t stby;

    // Input pins 

    digital_in_t clko;
    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    
    mcp2517fd_data_t glb_data;
    mcp2517fd_func_data_t func_data;

} mcp2517fd_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t stby;
    pin_name_t clko;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} mcp2517fd_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void mcp2517fd_cfg_setup ( mcp2517fd_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MCP2517DF_RETVAL mcp2517fd_init ( mcp2517fd_t *ctx, mcp2517fd_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for MCP2517FD click.
 */
void mcp2517fd_default_cfg ( mcp2517fd_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void mcp2517fd_generic_transfer ( mcp2517fd_t *ctx,  uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Chip Select Set function
 *
 * @param ctx          Click object. 
 * @param state        0 - active state, 1 - inactive state
 *
 * @description Offers a choice to enable or disable the SPI driver communication.
 */
void mcp2517fd_set_cs ( mcp2517fd_t *ctx, uint8_t state );

/**
 * @brief Message Transmit function
 *
 * @param ctx                   Click object.
 * @param num_data_bytes        Determines the length of message
 * @param transmit_flag         0 - failed, 1 - succeed
 * @param data_in               Meesage to be sent
 *
 * @description Transmits the desired message and checks is message successfully sent.
 */
void mcp2517fd_transmit_message ( mcp2517fd_t *ctx, uint8_t num_data_bytes, uint8_t *transmit_flag, uint8_t *data_in );

/**
 * @brief Message Receive function
 *
 * @param ctx                  Click object. 
 * @param receive_flag         0 - failed, 1 - succeed
 * @param data_out             Buffer where message be received
 *
 * @description Receives the message and checks is message successfully received.
 */
void mcp2517fd_receive_message ( mcp2517fd_t *ctx, uint8_t *receive_flag, uint8_t *data_out );

/**
 * @brief Reset function
 *
 * @param ctx                   Click object.
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for reset using generic transfer
 */
int8_t mcp2517fd_reset ( mcp2517fd_t *ctx );

/**
 * @brief SPI Read Byte function
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param rxd                   Buffer where data will be read
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for read byte
 */
int8_t mcp2517fd_read_byte ( mcp2517fd_t *ctx, uint16_t address, uint8_t *rxd );

/**
 * @brief SPI Write Byte
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Data to be written
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for write byte
 */
int8_t mcp2517fd_write_byte ( mcp2517fd_t *ctx, uint16_t address, uint8_t txd );

/**
 * @brief SPI Read Word
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param rxd                   Buffer where data will be read
 * 
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for read word
 */
int8_t mcp2517fd_read_word ( mcp2517fd_t *ctx, uint16_t address, uint32_t *rxd );

/**
 * @brief SPI Write Word
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Data to be written
 *  
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for write word
 */
int8_t mcp2517fd_write_word ( mcp2517fd_t *ctx, uint16_t address, uint32_t txd );

/**
 * @brief SPI Read Half Word
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param rxd                   Buffer where data will be read
 *  
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for read half word
 */
int8_t mcp2517fd_read_half_word ( mcp2517fd_t *ctx, uint16_t address, uint16_t *rxd );

/**
 * @brief SPI Write Half Word
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Data to be written
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for write half word
 */
int8_t mcp2517fd_write_half_word ( mcp2517fd_t *ctx, uint16_t address, uint16_t txd );

/**
 * @brief SPI SFR Write Byte Safe
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Data to be written
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Writes Byte to SFR at address using SPI CRC. Byte gets only written if CRC
 * matches.
 *
 * @note The function doesn't check if the address is an SFR address.
 */
int8_t mcp2517fd_write_byte_safe ( mcp2517fd_t *ctx, uint16_t address, uint8_t txd );

/**
 * @brief SPI RAM Write Word Safe
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Data to be written
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Writes Word to RAM at address using SPI CRC. Word gets only written if CRC
 * matches.
 *
 * @note The function doesn't check if the address is a RAM address.
 */
int8_t mcp2517fd_write_word_safe ( mcp2517fd_t *ctx, uint16_t address, uint32_t txd );

/**
 * @brief SPI Read Byte Array
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param rxd                   Buffer where data will be read
 * @param n_bytes               Number of bytes to be read
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for read byte array
 */
int8_t mcp2517fd_read_byte_array ( mcp2517fd_t *ctx, uint16_t address, uint8_t *rxd, uint16_t n_bytes );

 /**
 * @brief SPI Read Byte Array with CRC
 *
 * @param ctx                   Click object.
 * @param from_ram              Byte for array size.
 * @param crc_is_correct Compare CRC readings ( true - if equal, false - if not )
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for read byte with CRC
 */
int8_t mcp2517fd_read_byte_array_with_crc ( mcp2517fd_t *ctx, bool from_ram, bool *crc_is_correct );

/**
 * @brief SPI Write Byte Array
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Buffer of data to be written
 * @param n_bytes               Number of bytes to be write
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for write byte array
 */
int8_t mcp2517fd_write_byte_array ( mcp2517fd_t *ctx, uint16_t address, uint8_t *txd, uint16_t n_bytes );

/**
 * @brief SPI Write Byte Array with CRC
 *
 * @param ctx                   Click object.
 * @param from_ram              Byte for array size.
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for write byte array with CRC
 */
int8_t mcp2517fd_write_byte_array_with_crc ( mcp2517fd_t *ctx, bool from_ram );

/**
 * @brief SPI Read Word Array
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param rxd                   Buffer where data will be read
 * @param n_words               Number of words to be read
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for read word array
 */
int8_t mcp2517fd_read_word_array ( mcp2517fd_t *ctx, uint16_t address, uint32_t *rxd, uint16_t n_words );

/**
 * @brief SPI Write Word Array
 *
 * @param ctx                   Click object.
 * @param address               Register adress
 * @param txd                   Buffer of data to be written
 * @param n_words               Number of words to be read
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for write word array
 */
int8_t mcp2517fd_write_word_array ( mcp2517fd_t *ctx, uint16_t address, uint32_t *txd, uint16_t n_words );

/**
 * @brief CAN Control register configuration
 *
 * @param ctx                   Click object.
 * @param config                CAN config object.
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for CAN control register configuration
 */
int8_t mcp2517fd_configure ( mcp2517fd_t *ctx, mcp2517fd_can_cfg_t *config );

/**
 * @brief Reset Configure object to reset values
 *
 * @param config                CAN config object.
 * @returns  0 - if succeed 
 *
 * @description Function for reset configure object 
 */
int8_t mcp2517fd_configure_object_reset( mcp2517fd_can_cfg_t *config );

/**
 * @brief Select Operation Mode
 *
 * @param ctx                   Click object.
 * @param op_mode               Operation mode.
 *
 * @returns spi transfer error ( 0 : succeed, -1 : read error, -2 : write error )
 *
 * @description Function for select operation mode
 */
int8_t mcp2517fd_operation_mode_select ( mcp2517fd_t *ctx, uint8_t op_mode );

/**
 * @brief Get Operation Mode
 *
 * @param ctx                   Click object.
 *
 * @returns Operation mode.
 *
 * @description Function for get operation mode
 */
uint8_t mcp2517fd_operation_mode_get ( mcp2517fd_t *ctx );

/**
 * @brief Configure Transmit FIFO
 *
 * @param ctx                   Click object.
 * @param channel               Channel.
 * @param config                Tx FIFO config object.
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for configuring transmit FIFO
 */
int8_t mcp2517fd_transmit_channel_configure ( mcp2517fd_t *ctx, uint8_t channel, mcp2517fd_tx_fifo_cfg_t *config );

/**
 * @brief Reset Transmit Channel Configure object to reset values
 *
 * @param config                Tx FIFO config object.
 *
 * @returns 0 - if succeed
 *
 * @description Function for reseting values of Transmit channel configure object
 */
int8_t mcp2517fd_transmit_channel_configure_object_reset ( mcp2517fd_tx_fifo_cfg_t *config );

/**
 * @brief Configure Transmit Queue
 *
 * @param ctx                   Click object.
 * @param config                Tx QUEUE config object.
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for configuring transmit Queue
 */
int8_t mcp2517fd_transmit_queue_configure ( mcp2517fd_t *ctx, mcp2517fd_tx_que_cfg_t *config );

/**
 * @brief Reset Transmit Queue Configure object to reset values
 *
 * @param config                Tx QUEUE config object.
 *
 * @returns spi transfer error ( 0 - succeed, 1 - failed )
 *
 * @description Function for reseting values of Transmit Queue Configure object
 */
int8_t mcp2517fd_transmit_queue_configure_object_reset ( mcp2517fd_tx_que_cfg_t *config );

/**
 * @brief TX Channel Load
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param tx_obj                Tx Message object.
 * @param flush                 If TRUE - Requests transmission
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Loads data into Transmit channel
 */
int8_t mcp2517fd_transmit_channel_load ( mcp2517fd_t *ctx, uint8_t channel, mcp2517fd_tx_msg_obj_t *tx_obj, bool flush );

/**
 * @brief TX Channel Flush
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Set TXREG of one channel
 */
int8_t mcp2517fd_transmit_channel_flush ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Transmit Channel Status Get
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param status                Status to be read.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for getting Transmit Channel Status
 */
int8_t mcp2517fd_transmit_channel_status_get ( mcp2517fd_t *ctx, uint8_t channel, uint16_t *status );

/**
 * @brief Transmit FIFO Reset
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for resetting FIFO Transmit
 */
int8_t mcp2517fd_transmit_channel_reset ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Transmit FIFO Update
 * 
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param flush                 If TRUE - Requests transmission 
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Sets UINC of the transmit channel. Keeps TXREQ unchanged.
 */
int8_t mcp2517fd_transmit_channel_update ( mcp2517fd_t *ctx, uint8_t channel, bool flush );

/**
 * @brief Request transmissions using TXREQ register
 * 
 * @param ctx                   Click object. 
 * @param tx_req                TXREQ register to be written.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for requesting transmissions using TXREQ register
 */
int8_t mcp2517fd_transmit_request_set ( mcp2517fd_t *ctx, uint32_t tx_req );

/**
 * @brief Get TXREQ register
 * 
 * @param ctx                   Click object. 
 * @param tx_req                TXREQ register to be read.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for getting TXREQ register
 */
int8_t mcp2517fd_transmit_request_get ( mcp2517fd_t *ctx, uint32_t* tx_req );

/**
 * @brief Abort transmission of single FIFO
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for aborting transmission of single FIFO
 */
int8_t mcp2517fd_transmit_channel_abort ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Abort All transmissions
 *
 * @param ctx                   Click object. 
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for aborting all transmission
 */
int8_t mcp2517fd_transmit_abort_all ( mcp2517fd_t *ctx );

/**
 * @brief Set Transmit Bandwidth Sharing Delay
 *
 * @param ctx                   Click object. 
 * @param tx_bws                Transmit Bandwidth to be set
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for setting transmit bandwidth sharing delay
 */
int8_t mcp2517fd_transmit_band_width_sharing_set ( mcp2517fd_t *ctx, uint8_t tx_bws );

/**
 * @brief Filter Object Configuration
 *
 * @param ctx                   Click object. 
 * @param filter                Filter
 * @param id                    Filter object id
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Configures ID of filter object
 */
int8_t mcp2517fd_filter_object_configure ( mcp2517fd_t *ctx, uint8_t filter, mcp2517fd_filt_obj_id_t *id );

/**
 * @brief Filter Mask Configuration
 *
 * @param ctx                   Click object. 
 * @param filter                Filter
 * @param mask                  Filter mask id
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Configures Mask of filter object
 */
int8_t mcp2517fd_filter_mask_configure ( mcp2517fd_t *ctx, uint8_t filter, mcp2517fd_mask_obj_id_t *mask );

/**
 * @brief Link Filter to FIFO
 *
 * @param ctx                   Click object. 
 * @param filter                Filter
 * @param channel               Channel
 * @param enable                If TRUE - sets 1 on enable field ( of filter ctl object ) 
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Initializes the Pointer from Filter to FIFO. Enables or disables the Filter
 */
int8_t mcp2517fd_filter_to_fifo_link ( mcp2517fd_t *ctx, uint8_t filter, uint8_t channel, bool enable );

/**
 * @brief Filter Enable
 *
 * @param ctx                   Click object. 
 * @param filter                Filter
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for enabling specific filter
 */
int8_t mcp2517fd_filter_enable ( mcp2517fd_t *ctx, uint8_t filter );

/**
 * @brief Filter Disable
 *
 * @param ctx                   Click object. 
 * @param filter                Filter
 *
 * @returns spi transfer error ( 0 - succeed, -1 : read error, -2 : write error ) 
 * 
 * @description Function for disabling specific filter
 */
int8_t mcp2517fd_filter_disable ( mcp2517fd_t *ctx, uint8_t filter );

/**
 * @brief  Set Device Net Filter Count
 *
 * @param ctx                 Click object. 
 * @param dnfc                Device Net Filter Count
 *
 * @returns spi transfer error ( 0 - succeed, -1 : read error, -2 : write error ) 
 * 
 * @description Function for setting device net filter count
 */
int8_t mcp2517fd_device_net_filter_count_set ( mcp2517fd_t *ctx, uint8_t dnfc );

/**
 * @brief Configure Receive FIFO
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param config                Rx FIFO cfg object.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for configuring recive FIFO
 */
int8_t mcp2517fd_receive_channel_configure ( mcp2517fd_t *ctx, uint8_t channel, mcp2517fd_rx_fifo_cfg_t *config );

/**
 * @brief Reset Receive Channel Configure object to reset value
 *
 * @param config                Rx FIFO cfg object.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for resetting Receive Channel Configure object to reset value
 */
int8_t mcp2517fd_receive_channel_configure_object_reset ( mcp2517fd_rx_fifo_cfg_t *config );

/**
 * @brief Receive Channel Status Get
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param status                Status.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for getting Receive Channel Status
 */
int8_t mcp2517fd_receive_channel_status_get ( mcp2517fd_t *ctx, uint8_t channel, uint8_t *status );

/**
 * @brief Get Received Message
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param rx_obj                Rx Message object.
 *
 * @returns spi transfer error ( 0 : succeed, -1 : read_word_array error, 
 *     -2: if it's not receive buffer, -3 : read_byte_array error, -4 : receive_channel_update ) 
 *
 * @description Reads Received message from channel
 */
int8_t mcp2517fd_receive_message_get ( mcp2517fd_t *ctx, uint8_t channel, mcp2517fd_rx_msg_obj_t *rx_obj );

/**
 * @brief Receive FIFO Reset
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Function for resetting Receive FIFO
 */
int8_t mcp2517fd_receive_channel_reset ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Receive FIFO Update
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 *
 * @returns spi transfer error ( 0 - if succeed ) 
 * 
 * @description Sets UINC of the receive channel.
 */
int8_t mcp2517fd_receive_channel_update ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Transmit Event FIFO Status Get
 *
 * @param ctx                   Click object. 
 * @param status                Status 
 *
 * @returns spi transfer error ( 0 : if succeed, -1 : read_byte error ) 
 * 
 * @description Function for getting Transmit Event FIFO Status
 */
int8_t mcp2517fd_tef_status_get ( mcp2517fd_t *ctx, uint8_t *status );

/**
 * @brief Get Transmit Event FIFO Message
 *
 * @param ctx                   Click object. 
 * @param tef_obj               TEF Message object. 
 *
 * @returns spi transfer error ( 0 : if succeed. -1 : read_word_arrayread_word_array error 
 *          -2 : read_byte_array error, -3 : mcp2517fd_tef_update error ) 
 * 
 * @description Reads Transmit Event FIFO message
 */
int8_t mcp2517fd_tef_message_get ( mcp2517fd_t *ctx, mcp2517fd_tef_msg_obj_t *tef_obj );

/**
 * @brief Transmit Event FIFO Reset
 *
 * @param ctx                   Click object. 
 *
 * @returns spi transfer error ( 0 : if write_byte succeed ) 
 * 
 * @description Function for resetting Transmit Event FIFO
 */
int8_t mcp2517fd_tef_reset ( mcp2517fd_t *ctx );

/**
 * @brief Transmit Event FIFO Update
 *
 * @param ctx                   Click object.  
 *
 * @returns spi transfer error ( 0 : if write_byte succeed ) 
 * 
 * @description Sets UINC of the TEF.
 */
int8_t mcp2517fd_tef_update ( mcp2517fd_t *ctx );

/**
 * @brief Configure Transmit Event FIFO
 *
 * @param ctx                   Click object.  
 * @param config                TEF configure object.   
 *
 * @returns  spi transfer error ( 0 : if write_word succeed ) 
 * 
 * @description Function for configuring Transmit Event FIFO
 */
int8_t mcp2517fd_tef_configure ( mcp2517fd_t *ctx, mcp2517fd_tef_cfg_t *config );

/**
 * @brief Reset TefConfigure object to reset value
 *
 * @param ctx                   Click object.  
 * @param config                TEF configure object.   
 *
 * @returns  0 : if succeed 
 * 
 * @description Function for resetting value of TEF configure object. 
 */
int8_t mcp2517fd_tef_configure_object_reset ( mcp2517fd_tef_cfg_t *config );

/**
 * @brief Module Event Get
 *
 * @param ctx                   Click object.  
 * @param flags                 Interrupt flags to be read.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_half_word error )
 * 
 * @description Reads interrupt Flags
 */
int8_t mcp2517fd_module_event_get ( mcp2517fd_t *ctx, uint16_t *flags );

/**
 * @brief Module Event Enable
 *
 * @param ctx                   Click object.  
 * @param flags                 Interrupt enables to be read.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_half_word error,
 *            -2 : write_half_word error )
 * 
 * @description Enables interrupts
 */
int8_t mcp2517fd_module_event_enable ( mcp2517fd_t *ctx, uint16_t flags );

/**
 * @brief Module Event Disable
 *
 * @param ctx                   Click object.  
 * @param flags                 Interrupt disables to be read.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_half_word error,
 *            -2 : write_half_word error )
 *
 * @description Disables interrupts
 */
int8_t mcp2517fd_module_event_disable ( mcp2517fd_t *ctx, uint16_t flags );

/**
 * @brief Module Event Clear
 *
 * @param ctx                   Click object.  
 * @param flags                 Interrupt clears to be read.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -2 : write_half_word error )
 *
 * @description Clears interrupt Flags
 */
int8_t mcp2517fd_module_event_clear ( mcp2517fd_t *ctx, uint16_t flags );

/**
 * @brief Get RX Code
 *
 * @param ctx                   Click object.  
 * @param rx_code               Decode data_pointer. 
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error )
 *
 * @description Function for getting RX Code
 */
int8_t mcp2517fd_module_event_rx_code_get ( mcp2517fd_t *ctx, uint8_t *rx_code );

/**
 * @brief Get TX Code
 *
 * @param ctx                   Click object.  
 * @param tx_code               Decode data_pointer. 
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error )
 *
 * @description Function for getting TX Code
 */
int8_t mcp2517fd_module_event_tx_code_get ( mcp2517fd_t *ctx, uint8_t *tx_code );

/**
 * @brief Get Filter Hit
 *
 * @param ctx                   Click object.  
 * @param filter_hit            Filter hit. 
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error )
 *
 * @description Function for getting Filter Hit
 */
int8_t mcp2517fd_module_event_filter_hit_get ( mcp2517fd_t *ctx, uint8_t* filter_hit );

/**
 * @brief Get ICODE
 *
 * @param ctx                   Click object.  
 * @param icode                 Decode. 
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error )
 *
 * @description Function for getting ICODE
 */
int8_t mcp2517fd_module_event_icode_get ( mcp2517fd_t *ctx, uint8_t *icode );

/**
 * @brief Transmit FIFO Event Get
 *
 * @param ctx                   Click object.  
 * @param channel               Channel. 
 * @param flags                 Interrupt flags.
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error )
 *
 * @description Reads Transmit FIFO interrupt Flags
 */
int8_t mcp2517fd_transmit_channel_event_get ( mcp2517fd_t *ctx, uint8_t channel, uint8_t *flags );

/**
 * @brief Get pending interrupts of all transmit FIFOs
 *
 * @param ctx                   Click object.  
 * @param txif                  Buffer to be read. 
 *
 * @returns  spi transfer error ( 0 : if read_word error succeed )
 *
 * @description Function for gettingg pending interrupts of all transmit FIFOs
 */
int8_t mcp2517fd_transmit_event_get ( mcp2517fd_t *ctx, uint32_t *txif );
 
/**
 * @brief Get pending TXATIF of all transmit FIFOs
 *
 * @param ctx                   Click object.  
 * @param txatif                Buffer to be read. 
 *
 * @returns  spi transfer error ( 0 : if read_word error succeed )
 *
 * @description Function for gettingg pending TXATIF of all transmit FIFOs
 */
int8_t mcp2517fd_transmit_event_attempt_get ( mcp2517fd_t *ctx, uint32_t *txatif );

/**
 * @brief Transmit FIFO Index Get
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.  
 * @param idx                   Update data. 
 *
 * @returns  spi transfer error ( 0 : if read_word error succeed )
 *
 * @description Reads Transmit FIFO Index
 */
int8_t mcp2517fd_transmit_channel_index_get ( mcp2517fd_t *ctx, uint8_t channel, uint8_t *idx );

/**
 * @brief Transmit FIFO Event Enable
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.  
 * @param flags                 Interrupt Enables. 
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 *
 * @description Enables Transmit FIFO interrupts
 */
int8_t mcp2517fd_transmit_channel_event_enable( mcp2517fd_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Transmit FIFO Event Disable
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.  
 * @param flags                 Interrupt Enables. 
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 *
 * @description Disables Transmit FIFO interrupts
 */
int8_t mcp2517fd_transmit_channel_event_disable ( mcp2517fd_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Transmit FIFO Event Clear
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 *
 * @description Clears Transmit FIFO Attempts Exhausted interrupt Flag
 */
int8_t mcp2517fd_transmit_channel_event_attempt_clear ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Receive FIFO Event Get
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.  
 * @param flags                 Interrupt Enables.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error )
 * 
 * @description Reads Receive FIFO interrupt Flags
 */
int8_t mcp2517fd_receive_channel_event_get ( mcp2517fd_t *ctx, uint8_t channel, uint8_t *flags );

/**
 * @brief Get pending interrupts of all receive FIFOs
 *
 * @param ctx                   Click object. 
 * @param rxif                  Buffer to be read.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_word error )
 * 
 * @description Function for get pending interrupts of all receive FIFOs
 */
int8_t mcp2517fd_receive_event_get ( mcp2517fd_t *ctx, uint32_t *rxif );

/**
 * @brief Get pending RXOVIF of all receive FIFOs
 *
 * @param ctx                   Click object. 
 * @param rxovif                Buffer to be read.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_word error )
 * 
 * @description Function for get pending RXOVIF of all receive FIFOs
 */
int8_t mcp2517fd_receive_event_overflow_get ( mcp2517fd_t *ctx, uint32_t *rxovif );

/**
 * @brief Receive FIFO Index Get
 *
 * @param ctx                   Click object. 
 * @param cannel                Channel.
 * @param idx                   Transmit Channel Index to be read.  
 *
 * @returns  transmit_channel_index
 * 
 * @description Function for getting Receive FIFO Index
 */
int8_t mcp2517fd_receive_channel_index_get ( mcp2517fd_t *ctx, uint8_t channel, uint8_t *idx );

/**
 * @brief Receive FIFO Event Enable
 *
 * @param ctx                   Click object. 
 * @param cannel                Channel.
 * @param flags                 Interrupt Enables.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Enables Receive FIFO interrupts
 */
int8_t mcp2517fd_receive_channel_event_enable ( mcp2517fd_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Receive FIFO Event Disable
 *
 * @param ctx                   Click object. 
 * @param cannel                Channel.
 * @param flags                 Interrupt Disables.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Disables Receive FIFO interrupts
 */
int8_t mcp2517fd_receive_channel_event_disable ( mcp2517fd_t *ctx, uint8_t channel, uint8_t flags );

/**
 * @brief Receive FIFO Event Clear
 *
 * @param ctx                   Click object. 
 * @param cannel                Channel.
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Clears Receive FIFO Overflow interrupt Flag
 */
int8_t mcp2517fd_receive_channel_event_overflow_clear ( mcp2517fd_t *ctx, uint8_t channel );

/**
 * @brief Transmit Event FIFO Event Get
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt flags.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Reads Transmit Event FIFO interrupt Flags
 */
int8_t mcp2517fd_tef_event_get ( mcp2517fd_t *ctx, uint8_t* flags );

/**
 * @brief Transmit Event FIFO Event Enable
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt enables.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Enables Transmit Event FIFO interrupts
 */
int8_t mcp2517fd_tef_event_enable ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief Transmit Event FIFO Event Disable
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt disables.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Disables Transmit Event FIFO interrupts
 */
int8_t mcp2517fd_tef_event_disable ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief Transmit Event FIFO Event Clear
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt flags.  
 *
 * @returns  spi transfer error ( 0 : if succeed, -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Clears Transmit Event FIFO Overflow interrupt Flag
 */
int8_t mcp2517fd_tef_event_overflow_clear ( mcp2517fd_t *ctx );

/**
 * @brief Transmit Error Count Get
 *
 * @param ctx                   Click object. 
 * @param tec                   Buffer to be read.  
 *
 * @returns  spi transfer error ( if succeed read_byte )
 * 
 * @description Function for clearing Transmit Event FIFO Event
 */
int8_t mcp2517fd_error_count_transmit_get ( mcp2517fd_t *ctx, uint8_t *tec );

/**
 * @brief Receive Error Count Get
 *
 * @param ctx                   Click object. 
 * @param rec                   Buffer to be read.  
 *
 * @returns  spi transfer error ( if succeed read_byte )
 * 
 * @description Function for getting Receive Error Count
 */
int8_t mcp2517fd_error_count_receive_get ( mcp2517fd_t *ctx, uint8_t *rec );

/**
 * @brief Error State Get
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt flags.  
 *
 * @returns  spi transfer error ( if succeed read_byte )
 * 
 * @description Function for getting Error State
 */
int8_t mcp2517fd_error_state_get ( mcp2517fd_t *ctx, uint8_t *flags );

/**
 * @brief Error Counts and Error State Get
 *
 * @param ctx                   Click object. 
 * @param tec                   Buffer to be read. 
 * @param rec                   Buffer to be read. 
 * @param flags                 Interrupt flags.
 *
 * @returns  spi transfer error ( if succeed read_byte )
 * 
 * @description Returns content of complete CiTREC
 */
int8_t mcp2517fd_error_count_state_get ( mcp2517fd_t *ctx, uint8_t *tec, uint8_t *rec, uint8_t *flags );

/**
 * @brief Get Bus Diagnostic Registers: all data_ at once, since we want to keep them in synch
 *
 * @param ctx                   Click object. 
 * @param bd                    Bus diag object.
 *
 * @returns  spi transfer error ( if succeed read_word_array )
 * 
 * @description Function for getting Bus Diagnostic Registers: all data_ at once, since we want to keep them in synch
 */
int8_t mcp2517fd_bus_diagnostics_get ( mcp2517fd_t *ctx, mcp2517fd_bus_diag_t *bd );

/**
 * @brief Clear Bus Diagnostic Registers
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( if succeed write_word_array )
 * 
 * @description Function for clearing Bus Diagnostic Registers
 */
int8_t mcp2517fd_bus_diagnostics_clear ( mcp2517fd_t *ctx );

/**
 * @brief Enable ECC
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for enabling ECC
 */
int8_t mcp2517fd_ecc_enable ( mcp2517fd_t *ctx );

/**
 * @brief Disable ECC
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for disabling ECC
 */
int8_t mcp2517fd_ecc_disable ( mcp2517fd_t *ctx );

/**
 * @brief ECC Event Get
 *
 * @param ctx                   Click object.
 * @param flags                 Interrupt flags. 
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for getting ECC Event
 */
int8_t mcp2517fd_ecc_event_get ( mcp2517fd_t *ctx, uint8_t *flags );

/**
 * @brief Set ECC Parity
 *
 * @param ctx                   Click object. 
 * @param parity                Write command.
 *
 * @returns  spi transfer error ( write_byte error )
 * 
 * @description Function for setting ECC Parity
 */
int8_t mcp2517fd_ecc_parity_set ( mcp2517fd_t *ctx, uint8_t parity );

/**
 * @brief Get ECC Parity
 *
 * @param ctx                   Click object. 
 * @param parity                Data to be read.
 *
 * @returns  spi transfer error ( read_byte error )
 * 
 * @description Function for getting ECC Parity
 */
int8_t mcp2517fd_ecc_parity_get ( mcp2517fd_t *ctx, uint8_t *parity );

/**
 * @brief Get ECC Error Address
 *
 * @param ctx                   Click object. 
 * @param a                     Adress to be read.
 *
 * @returns  spi transfer error ( read_word error )
 * 
 * @description Function for getting ECC Error Address
 */
int8_t mcp2517fd_ecc_error_address_get ( mcp2517fd_t *ctx, uint16_t *a );

/**
 * @brief  ECC Event Enable
 *
 * @param ctx                   Click object. 
 * @param flags                 ECC interrupt.
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for enabling ECC Event
 */
int8_t mcp2517fd_ecc_event_enable ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief  ECC Event Disable
 *
 * @param ctx                   Click object. 
 * @param flags                 ECC interrupt.
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for disabling ECC Event
 */
int8_t mcp2517fd_ecc_event_disable ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief  ECC Event Clear
 *
 * @param ctx                   Click object. 
 * @param flags                 ECC status.
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for clearing ECC Event
 */
int8_t mcp2517fd_ecc_event_clear ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Enable
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt control bits of CRC Register.
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for enabling CRC Event
 */
int8_t mcp2517fd_crc_event_enable ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Disnable
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt control bits of CRC Register.
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for disabling CRC Event
 */
int8_t mcp2517fd_crc_event_disable ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Clear
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt flags of CRC Register
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for clearing CRC Event
 */
int8_t mcp2517fd_crc_event_clear ( mcp2517fd_t *ctx, uint8_t flags );

/**
 * @brief  CRC Event Get
 *
 * @param ctx                   Click object. 
 * @param flags                 Interrupt flags of CRC Register
 *
 * @returns  spi transfer error ( -1 : read_byte error )
 * 
 * @description Function for getting CRC Event
 */
int8_t mcp2517fd_crc_event_get ( mcp2517fd_t *ctx, uint8_t *flags );

/**
 * @brief  Get CRC Value from device
 *
 * @param ctx                   Click object. 
 * @param crc                   CRC value from CRC Register
 *
 * @returns  spi transfer error ( -1 : read_byte error )
 * 
 * @description Function for getting CRC Value from device
 */
int8_t mcp2517fd_crc_value_get ( mcp2517fd_t *ctx, uint16_t *crc );

/**
 * @brief  Initialize RAM
 *
 * @param ctx                   Click object. 
 * @param d                     Data_pointer
 *
 * @returns  spi transfer error ( -1 : write_byte_array error )
 * 
 * @description Function for initialising RAM
 */
int8_t mcp2517fd_ram_init ( mcp2517fd_t *ctx, uint8_t d );

/**
 * @brief  Time Stamp Enable
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for enabling Time Stamp
 */
int8_t mcp2517fd_time_stamp_enable ( mcp2517fd_t *ctx );

/**
 * @brief  Time Stamp Disable
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for disabling Time Stamp
 */
int8_t mcp2517fd_time_stamp_disable ( mcp2517fd_t *ctx );

/**
 * @brief  Time Stamp Get
 *
 * @param ctx                   Click object. 
 * @param ts                    Buffer to be read. 
 *
 * @returns  spi transfer error ( read_word error )
 * 
 * @description Function for getting Time Stamp
 */
int8_t mcp2517fd_time_stamp_get ( mcp2517fd_t *ctx, uint32_t *ts );

/**
 * @brief  Time Stamp Set
 *
 * @param ctx                   Click object. 
 * @param ts                    Data to be write.
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for setting Time Stamp
 */
int8_t mcp2517fd_time_stamp_set ( mcp2517fd_t *ctx, uint32_t ts );

/**
 * @brief  Time Stamp Mode Configure
 *
 * @param ctx                   Click object. 
 * @param mode                  Mode data to be write.
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for configuring Time Stamp Mode
 */
int8_t mcp2517fd_time_stamp_mode_configure ( mcp2517fd_t *ctx, uint8_t mode );

/**
 * @brief  Time Stamp Prescaler Set
 *
 * @param ctx                   Click object. 
 * @param ps                    Time stamp prescaler
 *
 * @returns  spi transfer error ( write_half_word error )
 * 
 * @description Function for setting Time Stamp Prescaler
 */
int8_t mcp2517fd_time_stamp_prescaler_set ( mcp2517fd_t *ctx, uint16_t ps );

/**
 * @brief  Enable oscillator to wake-up from sleep
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 : read_byte error, -2 : write_byte error )
 * 
 * @description Function for enabling oscillator to wake-up from sleep
 */
int8_t mcp2517fd_oscillator_enable ( mcp2517fd_t *ctx );

/**
 * @brief  Set Oscillator Control
 *
 * @param ctx                   Click object. 
 * @param ctrl                  Div ctl  object.
 *
 * @returns  spi transfer error ( write_byte error )
 * 
 * @description Function for setting Oscillator Control
 */
int8_t mcp2517fd_oscillator_control_set ( mcp2517fd_t *ctx, mcp2517fd_div_ctl_t ctrl );

/**
 * @brief  Reset Oscillator Control
 *
 * @param ctrl                  Div ctl  object.
 *
 * @returns  0 if success
 * 
 * @description Function for resetting Oscillator Control
 */
int8_t mcp2517fd_oscillator_control_object_reset ( mcp2517fd_div_ctl_t *ctrl );

/**
 * @brief  Get Oscillator Status
 *
 * @param ctx                   Click object. 
 * @param status                Oscillator status object.
 *
 * @returns  spi transfer error ( read_byte error )
 * 
 * @description Function for gettting Oscillator Status
 */
int8_t mcp2517fd_oscillator_status_get ( mcp2517fd_t *ctx, mcp2517fd_osc_sta_t *status );

/**
 * @brief  Configure Bit Time registers (based on CAN clock speed)
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 * @param ssp_mode              SSP Mode.
 * @param clk                   Decode clk. 
 *
 * @returns  spi transfer error ( read_byte error )
 * 
 * @description Function for configuring Bit Time registers ( based on CAN clock speed )
 */
int8_t mcp2517fd_bit_time_configure ( mcp2517fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode, uint8_t clk );

/**
 * @brief  Configure Nominal bit time for 40MHz system clock
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for configuring Nominal bit time for 40MHz system clock
 */
int8_t mcp2517fd_bit_time_configure_nominal_40_mhz ( mcp2517fd_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Data bit time for 40MHz system clock
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 * @param ssp_mode              SSP Mode. 
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for configuring Data bit time for 40MHz system clock
 */
int8_t mcp2517fd_bit_time_configure_data_40_mhz ( mcp2517fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode );

/**
 * @brief  Configure Nominal bit time for 20MHz system clock
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for configuring Nominal bit time for 20MHz system clock
 */
int8_t mcp2517fd_bit_time_configure_nominal_20_mhz ( mcp2517fd_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Nominal bit time for 20MHz system clock
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 * @param ssp_mode              SSP Mode.  
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for configuring Nominal bit time for 20MHz system clock
 */
int8_t mcp2517fd_bit_time_configure_data_20_mhz ( mcp2517fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode );

/**
 * @brief  Configure Nominal bit time for 10MHz system clock
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for configuring Nominal bit time for 10MHz system clock
 */
int8_t mcp2517fd_bit_time_configure_nominal_10_mhz ( mcp2517fd_t *ctx, uint8_t bit_time );

/**
 * @brief  Configure Data bit time for 10MHz system clock
 *
 * @param ctx                   Click object. 
 * @param bit_time              Bit time.
 * @param ssp_mode              SSP Mode.  
 *
 * @returns  spi transfer error ( write_word error )
 * 
 * @description Function for configuring Data bit time for 10MHz system clock
 */
int8_t mcp2517fd_bit_time_configure_data_10_mhz ( mcp2517fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode );

/**
 * @brief  Initialize GPIO Mode
 *
 * @param ctx                   Click object. 
 * @param gpio0                 GPIO 0.
 * @param gpio1                 GPIO 1.  
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for initialising GPIO Mode
 */
int8_t mcp2517fd_gpio_mode_configure ( mcp2517fd_t *ctx, uint8_t gpio0, uint8_t gpio1 );

/**
 * @brief  Initialize GPIO Direction
 *
 * @param ctx                   Click object. 
 * @param gpio0                 GPIO 0.
 * @param gpio1                 GPIO 1.  
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for initialising GPIO Direction
 */
int8_t mcp2517fd_gpio_direction_configure ( mcp2517fd_t *ctx, uint8_t gpio0, uint8_t gpio1 );

/**
 * @brief  Enable Transceiver Standby Control
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for enabling Transceiver Standby Control
 */
int8_t mcp2517fd_gpio_standby_control_enable ( mcp2517fd_t *ctx );

/**
 * @brief  Disable Transceiver Standby Control
 *
 * @param ctx                   Click object. 
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for disabling Transceiver Standby Control
 */
int8_t mcp2517fd_gpio_standby_control_disable ( mcp2517fd_t *ctx );

/**
 * @brief  Configure Open Drain Interrupts
 *
 * @param ctx                   Click object. 
 * @param mode                  Mode
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for configuring Open Drain Interrupts
 */
int8_t mcp2517fd_gpio_interrupt_pins_open_drain_configure ( mcp2517fd_t *ctx, uint8_t mode );

/**
 * @brief  Configure Open Drain TXCAN
 *
 * @param ctx                   Click object. 
 * @param mode                  Mode
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for configuring Open Drain TXCAN
 */
int8_t mcp2517fd_gpio_transmit_pin_open_drain_configure ( mcp2517fd_t *ctx, uint8_t mode );

/**
 * @brief  GPIO Output Pin Set
 *
 * @param ctx                   Click object. 
 * @param pos                   Pin flag
 * @param latch                 Pin latch
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for setting GPIO Output Pin
 */
int8_t mcp2517fd_gpio_pin_set ( mcp2517fd_t *ctx, uint8_t pos, uint8_t latch );

/**
 * @brief  Input Pin Read
 *
 * @param ctx                   Click object. 
 * @param pos                   Pin flag
 * @param state                 State to be read
 *
 * @returns  spi transfer error ( -1 read_byte error )
 * 
 * @description Function for reading GPIO Input Pin Read
 */
int8_t mcp2517fd_gpio_pin_read ( mcp2517fd_t *ctx, uint8_t pos, uint8_t *state );

/**
 * @brief  Configure CLKO Pin
 *
 * @param ctx                   Click object. 
 * @param mode                  Mode.
 *
 * @returns  spi transfer error ( -1 read_byte error, -2 write_byte error )
 * 
 * @description Function for configuring CLKO Pin
 */
int8_t mcp2517fd_gpio_clock_output_configure ( mcp2517fd_t *ctx, uint8_t mode );

/**
 * @brief  DLC to number of actual data_bytes conversion
 *
 * @param dlc           DLC
 *
 * @returns  data_pointerbytes_in_object
 * 
 * @description Function for conversion DLC to number of actual data_bytes
 */
uint32_t mcp2517fd_dlc_to_data_bytes ( uint8_t dlc );

/**
 * @brief  FIFO Index Get
 *
 * @param ctx                   Click object. 
 * @param channel               Channel.
 * @param mi                    Buffer for status register to be read
 *
 * @returns  spi transfer error ( -1 read_byte error )
 * 
 * @description Function for getting FIFO Index 
 */
int8_t mcp2517fd_fifo_index_get ( mcp2517fd_t *ctx, uint8_t channel, uint8_t *mi );

/**
 * @brief  Calculate CRC16
 *
 * @param ctx                   Click object. 
 * @param data_pointer          Data pointer.
 * @param size                  Size of array ( table for CRC calculation )
 *
 * @returns  init ( CRC base )
 * 
 * @description Function for calculate CRC16
 */
uint16_t mcp2517fd_calculate_crc16 ( uint8_t *data_pointer, uint16_t size );

/**
 * @brief  Data bytes to DLC conversion
 *
 * @param n         N bytes
 *
 * @returns dcl macro value
 * 
 * @description Function for conversion Data bytes to DLC 
 */
uint8_t mcp2517fd_data_bytes_to_dlc ( uint8_t n );


#ifdef __cplusplus
}
#endif
#endif  // _MCP2517DF_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

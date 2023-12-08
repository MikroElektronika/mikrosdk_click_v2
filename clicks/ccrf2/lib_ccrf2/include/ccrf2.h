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
 * \brief This file contains API for ccRF2 Click driver.
 *
 * \addtogroup ccrf2 ccRF2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CCRF2_H
#define CCRF2_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define CCRF2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.gp3 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CCRF2_RETVAL  uint8_t

#define CCRF2_OK           0x00
#define CCRF2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver_abstract_type  Driver Abstract type 
 * \{
 */
#define CCRF2_STATUS_T     uint8_t
/** \} */

/**
 * \defgroup configuration_registers Configuration Registers
 * \{
 */
#define CCRF2_IOCFG3                        0x0000
#define CCRF2_IOCFG2                        0x0001
#define CCRF2_IOCFG1                        0x0002
#define CCRF2_IOCFG0                        0x0003
#define CCRF2_SYNC3                         0x0004
#define CCRF2_SYNC2                         0x0005
#define CCRF2_SYNC1                         0x0006
#define CCRF2_SYNC0                         0x0007
#define CCRF2_SYNC_CFG1                     0x0008
#define CCRF2_SYNC_CFG0                     0x0009
#define CCRF2_DEVIATION_M                   0x000A
#define CCRF2_MODCFG_DEV_E                  0x000B
#define CCRF2_DCFILT_CFG                    0x000C
#define CCRF2_PREAMBLE_CFG1                 0x000D
#define CCRF2_PREAMBLE_CFG0                 0x000E
#define CCRF2_FREQ_IF_CFG                   0x000F
#define CCRF2_IQIC                          0x0010
#define CCRF2_CHAN_BW                       0x0011
#define CCRF2_MDMCFG1                       0x0012
#define CCRF2_MDMCFG0                       0x0013
#define CCRF2_SYMBOL_RATE2                  0x0014
#define CCRF2_SYMBOL_RATE1                  0x0015
#define CCRF2_SYMBOL_RATE0                  0x0016
#define CCRF2_AGC_REF                       0x0017
#define CCRF2_AGC_CS_THR                    0x0018
#define CCRF2_AGC_GAIN_ADJUST               0x0019
#define CCRF2_AGC_CFG3                      0x001A
#define CCRF2_AGC_CFG2                      0x001B
#define CCRF2_AGC_CFG1                      0x001C
#define CCRF2_AGC_CFG0                      0x001D
#define CCRF2_FIFO_CFG                      0x001E
#define CCRF2_DEV_ADDR                      0x001F
#define CCRF2_SETTLING_CFG                  0x0020
#define CCRF2_FS_CFG                        0x0021
#define CCRF2_WOR_CFG1                      0x0022
#define CCRF2_WOR_CFG0                      0x0023
#define CCRF2_WOR_EVENT0_MSB                0x0024
#define CCRF2_WOR_EVENT0_LSB                0x0025
#define CCRF2_PKT_CFG2                      0x0026
#define CCRF2_PKT_CFG1                      0x0027
#define CCRF2_PKT_CFG0                      0x0028
#define CCRF2_RFEND_CFG1                    0x0029
#define CCRF2_RFEND_CFG0                    0x002A
#define CCRF2_PA_CFG2                       0x002B
#define CCRF2_PA_CFG1                       0x002C
#define CCRF2_PA_CFG0                       0x002D
#define CCRF2_PKT_LEN                       0x002E
/** \} */

/**
 * \defgroup extended_cfg_reg Extended Configuration Registers
 * \{
 */
#define CCRF2_IF_MIX_CFG                    0x2F00
#define CCRF2_FREQOFF_CFG                   0x2F01
#define CCRF2_TOC_CFG                       0x2F02
#define CCRF2_MARC_SPARE                    0x2F03
#define CCRF2_ECG_CFG                       0x2F04
#define CCRF2_CFM_DATA_CFG                  0x2F05
#define CCRF2_EXT_CTRL                      0x2F06
#define CCRF2_RCCAL_FINE                    0x2F07
#define CCRF2_RCCAL_COARSE                  0x2F08
#define CCRF2_RCCAL_OFFSET                  0x2F09
#define CCRF2_FREQOFF1                      0x2F0A
#define CCRF2_FREQOFF0                      0x2F0B
#define CCRF2_FREQ2                         0x2F0C
#define CCRF2_FREQ1                         0x2F0D
#define CCRF2_FREQ0                         0x2F0E
#define CCRF2_IF_ADC2                       0x2F0F
#define CCRF2_IF_ADC1                       0x2F10
#define CCRF2_IF_ADC0                       0x2F11
#define CCRF2_FS_DIG1                       0x2F12
#define CCRF2_FS_DIG0                       0x2F13
#define CCRF2_FS_CAL3                       0x2F14
#define CCRF2_FS_CAL2                       0x2F15
#define CCRF2_FS_CAL1                       0x2F16
#define CCRF2_FS_CAL0                       0x2F17
#define CCRF2_FS_CHP                        0x2F18
#define CCRF2_FS_DIVTWO                     0x2F19
#define CCRF2_FS_DSM1                       0x2F1A
#define CCRF2_FS_DSM0                       0x2F1B
#define CCRF2_FS_DVC1                       0x2F1C
#define CCRF2_FS_DVC0                       0x2F1D
#define CCRF2_FS_LBI                        0x2F1E
#define CCRF2_FS_PFD                        0x2F1F
#define CCRF2_FS_PRE                        0x2F20
#define CCRF2_FS_REG_DIV_CML                0x2F21
#define CCRF2_FS_SPARE                      0x2F22
#define CCRF2_FS_VCO4                       0x2F23
#define CCRF2_FS_VCO3                       0x2F24
#define CCRF2_FS_VCO2                       0x2F25
#define CCRF2_FS_VCO1                       0x2F26
#define CCRF2_FS_VCO0                       0x2F27
#define CCRF2_GBIAS6                        0x2F28
#define CCRF2_GBIAS5                        0x2F29
#define CCRF2_GBIAS4                        0x2F2A
#define CCRF2_GBIAS3                        0x2F2B
#define CCRF2_GBIAS2                        0x2F2C
#define CCRF2_GBIAS1                        0x2F2D
#define CCRF2_GBIAS0                        0x2F2E
#define CCRF2_IFAMP                         0x2F2F
#define CCRF2_LNA                           0x2F30
#define CCRF2_RXMIX                         0x2F31
#define CCRF2_XOSC5                         0x2F32
#define CCRF2_XOSC4                         0x2F33
#define CCRF2_XOSC3                         0x2F34
#define CCRF2_XOSC2                         0x2F35
#define CCRF2_XOSC1                         0x2F36
#define CCRF2_XOSC0                         0x2F37
#define CCRF2_ANALOG_SPARE                  0x2F38
#define CCRF2_PA_CFG3                       0x2F39
#define CCRF2_IRQ0M                         0x2F3F
#define CCRF2_IRQ0F                         0x2F40
/** \} */

/**
 * \defgroup status_reg Status Registers
 * \{
 */
#define CCRF2_WOR_TIME1                     0x2F64
#define CCRF2_WOR_TIME0                     0x2F65
#define CCRF2_WOR_CAPTURE1                  0x2F66
#define CCRF2_WOR_CAPTURE0                  0x2F67
#define CCRF2_BIST                          0x2F68
#define CCRF2_DCFILTOFFSET_I1               0x2F69
#define CCRF2_DCFILTOFFSET_I0               0x2F6A
#define CCRF2_DCFILTOFFSET_Q1               0x2F6B
#define CCRF2_DCFILTOFFSET_Q0               0x2F6C
#define CCRF2_IQIE_I1                       0x2F6D
#define CCRF2_IQIE_I0                       0x2F6E
#define CCRF2_IQIE_Q1                       0x2F6F
#define CCRF2_IQIE_Q0                       0x2F70
#define CCRF2_RSSI1                         0x2F71
#define CCRF2_RSSI0                         0x2F72
#define CCRF2_MARCSTATE                     0x2F73
#define CCRF2_LQI_VAL                       0x2F74
#define CCRF2_PQT_SYNC_ERR                  0x2F75
#define CCRF2_DEM_STATUS                    0x2F76
#define CCRF2_FREQOFF_EST1                  0x2F77
#define CCRF2_FREQOFF_EST0                  0x2F78
#define CCRF2_AGC_GAIN3                     0x2F79
#define CCRF2_AGC_GAIN2                     0x2F7A
#define CCRF2_AGC_GAIN1                     0x2F7B
#define CCRF2_AGC_GAIN0                     0x2F7C
#define CCRF2_CFM_RX_DATA_OUT               0x2F7D
#define CCRF2_CFM_TX_DATA_IN                0x2F7E
#define CCRF2_ASK_SOFT_RX_DATA              0x2F7F
#define CCRF2_RNDGEN                        0x2F80
#define CCRF2_MAGN2                         0x2F81
#define CCRF2_MAGN1                         0x2F82
#define CCRF2_MAGN0                         0x2F83
#define CCRF2_ANG1                          0x2F84
#define CCRF2_ANG0                          0x2F85
#define CCRF2_CHFILT_I2                     0x2F86
#define CCRF2_CHFILT_I1                     0x2F87
#define CCRF2_CHFILT_I0                     0x2F88
#define CCRF2_CHFILT_Q2                     0x2F89
#define CCRF2_CHFILT_Q1                     0x2F8A
#define CCRF2_CHFILT_Q0                     0x2F8B
#define CCRF2_GPIO_STATUS                   0x2F8C
#define CCRF2_FSCAL_CTRL                    0x2F8D
#define CCRF2_PHASE_ADJUST                  0x2F8E
#define CCRF2_PARTNUMBER                    0x2F8F
#define CCRF2_PARTVERSION                   0x2F90
#define CCRF2_SERIAL_STATUS                 0x2F91
#define CCRF2_MODEM_STATUS1                 0x2F92
#define CCRF2_MODEM_STATUS0                 0x2F93
#define CCRF2_MARC_STATUS1                  0x2F94
#define CCRF2_MARC_STATUS0                  0x2F95
#define CCRF2_PA_IFAMP_TEST                 0x2F96
#define CCRF2_FSRF_TEST                     0x2F97
#define CCRF2_PRE_TEST                      0x2F98
#define CCRF2_PRE_OVR                       0x2F99
#define CCRF2_ADC_TEST                      0x2F9A
#define CCRF2_DVC_TEST                      0x2F9B
#define CCRF2_ATEST                         0x2F9C
#define CCRF2_ATEST_LVDS                    0x2F9D
#define CCRF2_ATEST_MODE                    0x2F9E
#define CCRF2_XOSC_TEST1                    0x2F9F
#define CCRF2_XOSC_TEST0                    0x2FA0

#define CCRF2_RXFIRST                       0x2FD2
#define CCRF2_TXFIRST                       0x2FD3
#define CCRF2_RXLAST                        0x2FD4
#define CCRF2_TXLAST                        0x2FD5
#define CCRF2_NUM_TXBYTES                   0x2FD6
#define CCRF2_NUM_RXBYTES                   0x2FD7
#define CCRF2_FIFO_NUM_TXBYTES              0x2FD8
#define CCRF2_FIFO_NUM_RXBYTES              0x2FD9
/** \} */

/**
 * \defgroup data_fifo_access DATA FIFO Access
 * \{
 */
#define CCRF2_SINGLE_TXFIFO                 0x003F
#define CCRF2_BURST_TXFIFO                  0x007F
#define CCRF2_SINGLE_RXFIFO                 0x00BF
#define CCRF2_BURST_RXFIFO                  0x00FF

#define CCRF2_LQI_CRC_OK_BM                 0x80
#define CCRF2_LQI_EST_BM                    0x7F
/** \} */

/**
 * \defgroup command_strobe_reg Command strobe registers
 * \{
 */
#define CCRF2_SRES                          0x30
#define CCRF2_SFSTXON                       0x31
#define CCRF2_SXOFF                         0x32
#define CCRF2_SCAL                          0x33
#define CCRF2_SRX                           0x34
#define CCRF2_STX                           0x35
#define CCRF2_SIDLE                         0x36
#define CCRF2_SWOR                          0x38
#define CCRF2_SPWD                          0x39
#define CCRF2_SFRX                          0x3A
#define CCRF2_SFTX                          0x3B
#define CCRF2_SWORRST                       0x3C
#define CCRF2_SNOP                          0x3D
#define CCRF2_AFC                           0x37
/** \} */

/**
 * \defgroup chip_states_returned_in_status_byte Chip states returned in status byte 
 * \{
 */
#define CCRF2_STATE_IDLE                    0x00
#define CCRF2_STATE_RX                      0x10
#define CCRF2_STATE_TX                      0x20
#define CCRF2_STATE_FSTXON                  0x30
#define CCRF2_STATE_CALIBRATE               0x40
#define CCRF2_STATE_SETTLING                0x50
#define CCRF2_STATE_RXFIFO_ERROR            0x60
#define CCRF2_STATE_TXFIFO_ERROR            0x70

#define CCRF2_RADIO_BURST_ACCESS            0x40
#define CCRF2_RADIO_SINGLE_ACCESS           0x00
#define CCRF2_RADIO_READ_ACCESS             0x80
#define CCRF2_RADIO_WRITE_ACCESS            0x00
/** \} */

/**
 * \defgroup bit_fields_in_the_chip_status_byte Bit fields in the chip status byte 
 * \{
 */
#define CCRF2_STATUS_CHIP_RDYn_BM           0x80
#define CCRF2_STATUS_STATE_BM               0x70
#define CCRF2_STATUS_FIFO_BYTES_AVA_BM      0x0F

#define CCRF2_STATUS_ERROR                  0x00
#define CCRF2_STATUS_OK                     0x01

#define CCRF2_IDLE_MODE                     0x01
#define CCRF2_TX_MODE                       0x02
#define CCRF2_RX_MODE                       0x03
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs;
    digital_out_t rst;

    // Input pins 

    digital_in_t gp0;
    digital_in_t gp2;
    digital_in_t gp3;
    digital_in_t miso;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    uint16_t packet_counter;
} ccrf2_t;

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

    pin_name_t gp0;
    pin_name_t rst;
    pin_name_t gp2;
    pin_name_t gp3;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
} ccrf2_cfg_t;

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
void ccrf2_cfg_setup ( ccrf2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CCRF2_RETVAL ccrf2_init ( ccrf2_t *ctx, ccrf2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for ccRF2 click.
 */
void ccrf2_default_cfg ( ccrf2_t *ctx );

/**
 * @brief Hardware reset function
 *
 * @param ctx          Click object.
 *
 * @description The function Hardware reset - resets the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 *
 * @note Delay aprox. 300 ms.
 */
void ccrf2_hw_reset ( ccrf2_t *ctx );

/**
 * @brief Set command strobe function
 *
 * @param ctx          Click object.
 * @param cmd          8-bit command
 *
 * @returns     8-bit status data
 * 
 * @description Function sets 8-bit strobe command to the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_cmd_strobe ( ccrf2_t *ctx, uint8_t cmd );

/**
 * @brief Read or write burst single function
 *
 * @param ctx               Click object.
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be written/read
 * @param n_bytes           number of bytes to be written/read
 *
 * @description Function reads or writes a sequential data starting to the targeted 8-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
void ccrf2_read_write_burst_single ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes );

/**
 * @brief Access 8-bit register function
 *
 * @param ctx               Click object.
 * @param access_type       Access type
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be written/read
 * @param n_bytes           number of bytes to be written/read
 *
 * @returns     8-bit status data
 * 
 * @description Function access to the targeted 8-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_8bit_reg_access ( ccrf2_t *ctx, char access_type, uint8_t reg_address, uint8_t *rw_data, 
                                              uint16_t n_bytes );

/**
 * @brief Access 16-bit register function
 *
 * @param ctx               Click object. 
 * @param access_type       Access type
 * @param ext_address       Ext address
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be written/read
 * @param n_bytes           number of bytes to be written/read
 *
 * @returns     8-bit status data
 * 
 * @description Function access to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_16bit_reg_access ( ccrf2_t *ctx, uint8_t access_type, uint8_t ext_address, 
                                               uint8_t reg_address, uint8_t *rw_data, uint8_t n_bytes );

/**
 * @brief Read the byte of data function
 *
 * @param ctx               Click object.  
 * @param reg_address       16-bit register address
 * @param read_data         pointer to the data to be read
 * @param n_bytes           number of bytes to be read
 *
 * @returns     8-bit status data
 * 
 * @description Function read the byte of data of the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_read_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Write sequential data function
 *
 * @param ctx               Click object.   
 * @param reg_address       16-bit register address
 * @param write_data        pointer to the data to be written
 * @param n_bytes           number of bytes to be written
 *
 * @returns     8-bit status data
 * 
 * @description Function write a sequential data starting to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_write_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Write one byte data function
 *
 * @param ctx               Click object.   
 * @param reg_address       16-bit register address
 * @param write_data        data to be written
 *
 * @returns     8-bit status data
 * 
 * @description Function write a single byte data to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_write_reg_single( ccrf2_t *ctx, uint16_t reg_address, uint8_t write_data );

/**
 * @brief Write TX FIFO register function
 *
 * @param ctx                        Click object.  
 * @param write_data                 pointer to the data to be written
 * @param n_bytes                    number of bytes to be written
 *
 * @returns 8-bit status data
 *
 * @description Function write sequential data to the targeted 8-bit TX FIFO register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_write_tx_fifo ( ccrf2_t *ctx, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Read RX FIFO register function
 *
 * @param ctx                        Click object.  
 * @param read_data                  pointer to the data to be read
 * @param n_bytes                    number of bytes to be read
 *
 * @returns
 * 8-bit status data
 *
 * @description Function read sequential data from the targeted 8-bit RX FIFO register address of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_read_rx_fifo ( ccrf2_t *ctx, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Manual calibration function
 *
 * @param ctx               Click object.  
 *
 * @description Function manual calibration the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
void ccrf2_manual_calibration ( ccrf2_t *ctx );

/**
 * @brief Set RX mode function
 *
 * @param ctx               Click object.  
 *
 * @description Function set RX mode of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
void ccrf2_set_rx_mode ( ccrf2_t *ctx );

/**
 * @brief Set TX mode function
 *
 * @param ctx               Click object.  
 *
 * @description Function set TX mode of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 *
 */
void ccrf2_set_tx_mode ( ccrf2_t *ctx );

/**
 * @brief Read state of GP0 pin function
 *
 * @param ctx               Click object.
 *
 * @description Function reads state of GP0 pin of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_read_gp0 ( ccrf2_t *ctx );

/**
 * @brief Read state of GP2 pin function
 *
 * @param ctx               Click object.
 *
 * @description Function reads state of GP2 pin of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_read_gp2 ( ccrf2_t *ctx );

/**
 * @brief Read state of GP3 pin function
 *
 * @param ctx               Click object.
 *
 * @description Function reads state of GP3 pin of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_read_gp3 ( ccrf2_t *ctx );

/**
 * @brief Send TX data function
 *
 * @param ctx               Click object.  
 * @param tx_data           pointer to the data to be send
 * @param n_bytes           number of bytes to be send
 *
 * @description Function send TX data to the receive module of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
void ccrf2_send_tx_data ( ccrf2_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

/**
 * @brief Receive RX data function
 *
 * @param ctx               Click object.  
 *
 * @param rx_data           pointer to the data to be receive
 *
 * @returns                 Number of the received data bytes.
 * 
 * @description Function receive RX data from the transmit module of the
 * CC1120 single-chip radio transceiver on the ccRF 2 Click board.
 */
uint8_t ccrf2_receive_rx_data ( ccrf2_t *ctx, uint8_t *rx_data );

#ifdef __cplusplus
}
#endif
#endif  // _CCRF2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

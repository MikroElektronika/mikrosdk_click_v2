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
 * \brief This file contains API for ccRF 3 Click driver.
 *
 * \addtogroup ccrf3 ccRF 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CCRF3_H
#define CCRF3_H

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

#define CCRF3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.gp0   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.gp2   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.gp3   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CCRF3_RETVAL  uint8_t

#define CCRF3_OK           0x00
#define CCRF3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup d_river_abstract_type  Driver Abstract type 
 * \{
 */
#define CCRF3_STATUS_T     uint8_t
/** \} */

/**
 * \defgroup configuration_registers Configuration Registers
 * \{
 */
#define CCRF3_IOCFG3                        0x0000
#define CCRF3_IOCFG2                        0x0001
#define CCRF3_IOCFG1                        0x0002
#define CCRF3_IOCFG0                        0x0003
#define CCRF3_SYNC3                         0x0004
#define CCRF3_SYNC2                         0x0005
#define CCRF3_SYNC1                         0x0006
#define CCRF3_SYNC0                         0x0007
#define CCRF3_SYNC_CFG1                     0x0008
#define CCRF3_SYNC_CFG0                     0x0009
#define CCRF3_DEVIATION_M                   0x000A
#define CCRF3_MODCFG_DEV_E                  0x000B
#define CCRF3_DCFILT_CFG                    0x000C
#define CCRF3_PREAMBLE_CFG1                 0x000D
#define CCRF3_PREAMBLE_CFG0                 0x000E
#define CCRF3_FREQ_IF_CFG                   0x000F
#define CCRF3_IQIC                          0x0010
#define CCRF3_CHAN_BW                       0x0011
#define CCRF3_MDMCFG1                       0x0012
#define CCRF3_MDMCFG0                       0x0013
#define CCRF3_SYMBOL_RATE2                  0x0014
#define CCRF3_SYMBOL_RATE1                  0x0015
#define CCRF3_SYMBOL_RATE0                  0x0016
#define CCRF3_AGC_REF                       0x0017
#define CCRF3_AGC_CS_THR                    0x0018
#define CCRF3_AGC_GAIN_ADJUST               0x0019
#define CCRF3_AGC_CFG3                      0x001A
#define CCRF3_AGC_CFG2                      0x001B
#define CCRF3_AGC_CFG1                      0x001C
#define CCRF3_AGC_CFG0                      0x001D
#define CCRF3_FIFO_CFG                      0x001E
#define CCRF3_DEV_ADDR                      0x001F
#define CCRF3_SETTLING_CFG                  0x0020
#define CCRF3_FS_CFG                        0x0021
#define CCRF3_WOR_CFG1                      0x0022
#define CCRF3_WOR_CFG0                      0x0023
#define CCRF3_WOR_EVENT0_MSB                0x0024
#define CCRF3_WOR_EVENT0_LSB                0x0025
#define CCRF3_PKT_CFG2                      0x0026
#define CCRF3_PKT_CFG1                      0x0027
#define CCRF3_PKT_CFG0                      0x0028
#define CCRF3_RFEND_CFG1                    0x0029
#define CCRF3_RFEND_CFG0                    0x002A
#define CCRF3_PA_CFG2                       0x002B
#define CCRF3_PA_CFG1                       0x002C
#define CCRF3_PA_CFG0                       0x002D
#define CCRF3_PKT_LEN                       0x002E
/** \} */

/**
 * \defgroup extended_cfg_reg Extended Configuration Registers
 * \{
 */
#define CCRF3_IF_MIX_CFG                    0x2F00
#define CCRF3_FREQOFF_CFG                   0x2F01
#define CCRF3_TOC_CFG                       0x2F02
#define CCRF3_MARC_SPARE                    0x2F03
#define CCRF3_ECG_CFG                       0x2F04
#define CCRF3_CFM_DATA_CFG                  0x2F05
#define CCRF3_EXT_CTRL                      0x2F06
#define CCRF3_RCCAL_FINE                    0x2F07
#define CCRF3_RCCAL_COARSE                  0x2F08
#define CCRF3_RCCAL_OFFSET                  0x2F09
#define CCRF3_FREQOFF1                      0x2F0A
#define CCRF3_FREQOFF0                      0x2F0B
#define CCRF3_FREQ2                         0x2F0C
#define CCRF3_FREQ1                         0x2F0D
#define CCRF3_FREQ0                         0x2F0E
#define CCRF3_IF_ADC2                       0x2F0F
#define CCRF3_IF_ADC1                       0x2F10
#define CCRF3_IF_ADC0                       0x2F11
#define CCRF3_FS_DIG1                       0x2F12
#define CCRF3_FS_DIG0                       0x2F13
#define CCRF3_FS_CAL3                       0x2F14
#define CCRF3_FS_CAL2                       0x2F15
#define CCRF3_FS_CAL1                       0x2F16
#define CCRF3_FS_CAL0                       0x2F17
#define CCRF3_FS_CHP                        0x2F18
#define CCRF3_FS_DIVTWO                     0x2F19
#define CCRF3_FS_DSM1                       0x2F1A
#define CCRF3_FS_DSM0                       0x2F1B
#define CCRF3_FS_DVC1                       0x2F1C
#define CCRF3_FS_DVC0                       0x2F1D
#define CCRF3_FS_LBI                        0x2F1E
#define CCRF3_FS_PFD                        0x2F1F
#define CCRF3_FS_PRE                        0x2F20
#define CCRF3_FS_REG_DIV_CML                0x2F21
#define CCRF3_FS_SPARE                      0x2F22
#define CCRF3_FS_VCO4                       0x2F23
#define CCRF3_FS_VCO3                       0x2F24
#define CCRF3_FS_VCO2                       0x2F25
#define CCRF3_FS_VCO1                       0x2F26
#define CCRF3_FS_VCO0                       0x2F27
#define CCRF3_GBIAS6                        0x2F28
#define CCRF3_GBIAS5                        0x2F29
#define CCRF3_GBIAS4                        0x2F2A
#define CCRF3_GBIAS3                        0x2F2B
#define CCRF3_GBIAS2                        0x2F2C
#define CCRF3_GBIAS1                        0x2F2D
#define CCRF3_GBIAS0                        0x2F2E
#define CCRF3_IFAMP                         0x2F2F
#define CCRF3_LNA                           0x2F30
#define CCRF3_RXMIX                         0x2F31
#define CCRF3_XOSC5                         0x2F32
#define CCRF3_XOSC4                         0x2F33
#define CCRF3_XOSC3                         0x2F34
#define CCRF3_XOSC2                         0x2F35
#define CCRF3_XOSC1                         0x2F36
#define CCRF3_XOSC0                         0x2F37
#define CCRF3_ANALOG_SPARE                  0x2F38
#define CCRF3_PA_CFG3                       0x2F39
#define CCRF3_IRQ0M                         0x2F3F
#define CCRF3_IRQ0F                         0x2F40
/** \} */

/**
 * \defgroup status_reg Status Registers
 * \{
 */
#define CCRF3_WOR_TIME1                     0x2F64
#define CCRF3_WOR_TIME0                     0x2F65
#define CCRF3_WOR_CAPTURE1                  0x2F66
#define CCRF3_WOR_CAPTURE0                  0x2F67
#define CCRF3_BIST                          0x2F68
#define CCRF3_DCFILTOFFSET_I1               0x2F69
#define CCRF3_DCFILTOFFSET_I0               0x2F6A
#define CCRF3_DCFILTOFFSET_Q1               0x2F6B
#define CCRF3_DCFILTOFFSET_Q0               0x2F6C
#define CCRF3_IQIE_I1                       0x2F6D
#define CCRF3_IQIE_I0                       0x2F6E
#define CCRF3_IQIE_Q1                       0x2F6F
#define CCRF3_IQIE_Q0                       0x2F70
#define CCRF3_RSSI1                         0x2F71
#define CCRF3_RSSI0                         0x2F72
#define CCRF3_MARCSTATE                     0x2F73
#define CCRF3_LQI_VAL                       0x2F74
#define CCRF3_PQT_SYNC_ERR                  0x2F75
#define CCRF3_DEM_STATUS                    0x2F76
#define CCRF3_FREQOFF_EST1                  0x2F77
#define CCRF3_FREQOFF_EST0                  0x2F78
#define CCRF3_AGC_GAIN3                     0x2F79
#define CCRF3_AGC_GAIN2                     0x2F7A
#define CCRF3_AGC_GAIN1                     0x2F7B
#define CCRF3_AGC_GAIN0                     0x2F7C
#define CCRF3_CFM_RX_DATA_OUT               0x2F7D
#define CCRF3_CFM_TX_DATA_IN                0x2F7E
#define CCRF3_ASK_SOFT_RX_DATA              0x2F7F
#define CCRF3_RNDGEN                        0x2F80
#define CCRF3_MAGN2                         0x2F81
#define CCRF3_MAGN1                         0x2F82
#define CCRF3_MAGN0                         0x2F83
#define CCRF3_ANG1                          0x2F84
#define CCRF3_ANG0                          0x2F85
#define CCRF3_CHFILT_I2                     0x2F86
#define CCRF3_CHFILT_I1                     0x2F87
#define CCRF3_CHFILT_I0                     0x2F88
#define CCRF3_CHFILT_Q2                     0x2F89
#define CCRF3_CHFILT_Q1                     0x2F8A
#define CCRF3_CHFILT_Q0                     0x2F8B
#define CCRF3_GPIO_STATUS                   0x2F8C
#define CCRF3_FSCAL_CTRL                    0x2F8D
#define CCRF3_PHASE_ADJUST                  0x2F8E
#define CCRF3_PARTNUMBER                    0x2F8F
#define CCRF3_PARTVERSION                   0x2F90
#define CCRF3_SERIAL_STATUS                 0x2F91
#define CCRF3_MODEM_STATUS1                 0x2F92
#define CCRF3_MODEM_STATUS0                 0x2F93
#define CCRF3_MARC_STATUS1                  0x2F94
#define CCRF3_MARC_STATUS0                  0x2F95
#define CCRF3_PA_IFAMP_TEST                 0x2F96
#define CCRF3_FSRF_TEST                     0x2F97
#define CCRF3_PRE_TEST                      0x2F98
#define CCRF3_PRE_OVR                       0x2F99
#define CCRF3_ADC_TEST                      0x2F9A
#define CCRF3_DVC_TEST                      0x2F9B
#define CCRF3_ATEST                         0x2F9C
#define CCRF3_ATEST_LVDS                    0x2F9D
#define CCRF3_ATEST_MODE                    0x2F9E
#define CCRF3_XOSC_TEST1                    0x2F9F
#define CCRF3_XOSC_TEST0                    0x2FA0

#define CCRF3_RXFIRST                       0x2FD2
#define CCRF3_TXFIRST                       0x2FD3
#define CCRF3_RXLAST                        0x2FD4
#define CCRF3_TXLAST                        0x2FD5
#define CCRF3_NUM_TXBYTES                   0x2FD6
#define CCRF3_NUM_RXBYTES                   0x2FD7
#define CCRF3_FIFO_NUM_TXBYTES              0x2FD8
#define CCRF3_FIFO_NUM_RXBYTES              0x2FD9
/** \} */

/**
 * \defgroup data_fifo_access DATA FIFO Access
 * \{
 */
#define CCRF3_SINGLE_TXFIFO                 0x003F
#define CCRF3_BURST_TXFIFO                  0x007F
#define CCRF3_SINGLE_RXFIFO                 0x00BF
#define CCRF3_BURST_RXFIFO                  0x00FF

#define CCRF3_LQI_CRC_OK_BM                 0x80
#define CCRF3_LQI_EST_BM                    0x7F
/** \} */

/**
 * \defgroup command_strobe_reg Command strobe registers
 * \{
 */
#define CCRF3_SRES                          0x30
#define CCRF3_SFSTXON                       0x31
#define CCRF3_SXOFF                         0x32
#define CCRF3_SCAL                          0x33
#define CCRF3_SRX                           0x34
#define CCRF3_STX                           0x35
#define CCRF3_SIDLE                         0x36
#define CCRF3_SWOR                          0x38
#define CCRF3_SPWD                          0x39
#define CCRF3_SFRX                          0x3A
#define CCRF3_SFTX                          0x3B
#define CCRF3_SWORRST                       0x3C
#define CCRF3_SNOP                          0x3D
#define CCRF3_AFC                           0x37
/** \} */

/**
 * \defgroup chip_states_returned_in_status_byte Chip states returned in status byte 
 * \{
 */
#define CCRF3_STATE_IDLE                    0x00
#define CCRF3_STATE_RX                      0x10
#define CCRF3_STATE_TX                      0x20
#define CCRF3_STATE_FSTXON                  0x30
#define CCRF3_STATE_CALIBRATE               0x40
#define CCRF3_STATE_SETTLING                0x50
#define CCRF3_STATE_RXFIFO_ERROR            0x60
#define CCRF3_STATE_TXFIFO_ERROR            0x70

#define CCRF3_RADIO_BURST_ACCESS            0x40
#define CCRF3_RADIO_SINGLE_ACCESS           0x00
#define CCRF3_RADIO_READ_ACCESS             0x80
#define CCRF3_RADIO_WRITE_ACCESS            0x00
/** \} */

/**
 * \defgroup bit_fields_in_the_chip_status_byte Bit fields in the chip status byte 
 * \{
 */
#define CCRF3_STATUS_CHIP_RDYn_BM           0x80
#define CCRF3_STATUS_STATE_BM               0x70
#define CCRF3_STATUS_FIFO_BYTES_AVA_BM      0x0F

#define CCRF3_STATUS_ERROR                  0x00
#define CCRF3_STATUS_OK                     0x01

#define CCRF3_IDLE_MODE                     0x01
#define CCRF3_TX_MODE                       0x02
#define CCRF3_RX_MODE                       0x03
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
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // Additional variable 

    uint8_t access_type; 
    uint8_t ext_addr;
    uint16_t packet_counter;

} ccrf3_t;

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
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    uint16_t packet_counter_cfg;

} ccrf3_cfg_t;

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
void ccrf3_cfg_setup ( ccrf3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CCRF3_RETVAL ccrf3_init ( ccrf3_t *ctx, ccrf3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for ccRF 3 click.
 */
void ccrf3_default_cfg ( ccrf3_t *ctx );

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
void ccrf3_generic_transfer ( ccrf3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Hardware reset function
 *
 * @param ctx          Click object.
 *
 * @description The function Hardware reset - resets the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 *
 * @note Delay aprox. 300 ms.
 */
void ccrf3_hw_reset ( ccrf3_t *ctx );

/**
 * @brief Set command strobe function
 *
 * @param ctx          Click object.
 * @param cmd          8-bit command
 *
 * @description Function sets 8-bit strobe command to the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_cmd_strobe ( ccrf3_t *ctx, uint8_t cmd );

/**
 * @brief Get TX data status function
 *
 * @param ctx          Click object.
 *
 * @description Function gets TX data status of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_tx_status ( ccrf3_t *ctx );

/**
 * @brief Get RX data status function
 *
 * @param ctx          Click object.
 * 
 * @description Function gets RX data status of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_rx_status ( ccrf3_t *ctx );

/**
 * @brief Read or write burst single function
 *
 * @param ctx               Click object.
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be written/read
 * @param n_bytes           number of bytes to be written/read
 *
 * @description Function reads or writes a sequential data starting to the targeted 8-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_read_write_burst_single ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes );

/**
 * @brief Access 8-bit register function
 *
 * @param ctx               Click object.
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be written/read
 * @param n_bytes           number of bytes to be written/read
 *
 * @description Function access to the targeted 8-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
CCRF3_STATUS_T ccrf3_byte_reg_access ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes );

/**
 * @brief Access 16-bit register function
 *
 * @param ctx               Click object. 
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be written/read
 * @param n_bytes           number of bytes to be written/read
 *
 * @description Function access to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
CCRF3_STATUS_T ccrf3_bytes_reg_access ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint8_t n_bytes );

/**
 * @brief Read the byte of data function
 *
 * @param ctx               Click object.  
 * @param reg_address       16-bit register address
 * @param read_data         pointer to the data to be read
 * @param n_bytes           number of bytes to be read
 *
 * @description Function read the byte of data of the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
CCRF3_STATUS_T ccrf3_read_bytes_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Read the byte of data function
 *
 * @param ctx               Click object.  
 * @param reg_address       16-bit register address
 *
 * @returns 8-bit read data
 *
 * @description Function read the byte of data from the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_read_byte_reg ( ccrf3_t *ctx, uint16_t reg_address );

/**
 * @brief Write sequential data function
 *
 * @param ctx               Click object.   
 * @param reg_address       16-bit register address
 * @param write_data        pointer to the data to be written
 * @param n_bytes           number of bytes to be written
 *
 * @description Function write a sequential data starting to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_write_bytes_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Write the byte of data function
 *
 * @param ctx               Click object.   
 * @param reg_address       16-bit register address
 * @param write_data        pointer to the data to be written
 *
 * @returns     8-bit status data
 *
 * @description Function write the byte of data to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_write_byte_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t write_data );

/**
 * @brief Write the burst single1 function
 *
 * @param ctx               Click object.  
 * @param reg_address       16-bit register address
 * @param write_data        pointer to the data to be written
 * @param n_bytes           number of bytes to be written
 *
 * @description Function write the burst single1 to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_read_write_burst_single1 ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Access 8-bit register function
 *
 * @param ctx               Click object.  
 * @param reg_address       8-bit register address
 * @param rw_data           pointer to the data to be read
 * @param n_bytes           number of bytes to be read
 *
 * @description Function access to the targeted 8-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_access_byte_register ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes );

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
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_write_tx_fifo ( ccrf3_t *ctx, uint8_t *write_data, uint8_t n_bytes );

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
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_read_rx_fifo ( ccrf3_t *ctx, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Manual calibration function
 *
 * @param ctx               Click object.  
 *
 * @description Function manual calibration the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_manual_calibration ( ccrf3_t *ctx );

/**
 * @brief Set RX mode function
 *
 * @param ctx               Click object.  
 *
 * @description Function set RX mode of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_rx_mode ( ccrf3_t *ctx );

/**
 * @brief Set TX mode function
 *
 * @param ctx               Click object.  
 *
 * @description Function set TX mode of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 *
 */
void ccrf3_set_tx_mode ( ccrf3_t *ctx );

/**
 * @brief Send TX data function
 *
 * @param ctx               Click object.  
 * @param tx_data           pointer to the data to be send
 * @param n_bytes           number of bytes to be send
 *
 * @description Function send TX data to the receive module of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_send_tx_data ( ccrf3_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

/**
 * @brief Receive RX data function
 *
 * @param ctx               Click object.  
 *
 * @param rx_data           pointer to the data to be receive
 *
 * @description Function receive RX data from the transmit module of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_receive_rx_data ( ccrf3_t *ctx, uint8_t *rx_data );

/**
 * @brief Set GPIO3 analog transfer enable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO3 analog transfer enable
 * by sets to '1' [ bit 7 ] to the CCRF2_IOCFG3 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_analog_transfer_gpio3 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO3 analog transfer disable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO3 analog transfer disable
 * by cleared to '0' [ bit 7 ] to the CCRF2_IOCFG3 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_analog_transfer_gpio3 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO3 invert output enable function
 *
 * @param ctx               Click object. 
 * 
 * @description Function set GPIO3 invert output enable
 * by sets to '1' [ bit 6 ] to the CCRF2_IOCFG3 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_invert_output_gpio3 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO3 invert output disable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO3 invert output disable
 * by cleared to '0' [ bit 6 ] to the CCRF2_IOCFG3 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_invert_output_gpio3 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO2 analog transfer enable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO2 analog transfer enable
 * by sets to '1' [ bit 7 ] to the CCRF2_IOCFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_analog_transfer_gpio2 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO2 analog transfer disable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO2 analog transfer disable
 * by cleared to '0' [ bit 7 ] to the CCRF2_IOCFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_analog_transfer_gpio2 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO2 invert output enable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO2 invert output enable
 * by sets to '1' [ bit 6 ] to the CCRF2_IOCFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_invert_output_gpio2 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO2 invert output disable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO2 invert output disable
 * by cleared to '0' [ bit 6 ] to the CCRF2_IOCFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_invert_output_gpio2( ccrf3_t *ctx );

/**
 * @brief Set GPIO0 analog transfer enable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO0 analog transfer enable
 * by sets to '1' [ bit 7 ] to the CCRF2_IOCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_analog_transfer_gpio0 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO0 analog transfer disable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO0 analog transfer disable
 * by cleared to '0' [ bit 7 ] to the CCRF2_IOCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_analog_transfer_gpio0 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO0 invert output enable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO0 invert output enable
 * by sets to '1' [ bit 6 ] to the CCRF2_IOCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_invert_output_gpio0 ( ccrf3_t *ctx );

/**
 * @brief Set GPIO0 invert output disable function
 *
 * @param ctx               Click object.  
 *
 * @description Function set GPIO0 invert output disable
 * by cleared to '0' [ bit 6 ] to the CCRF2_IOCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_invert_output_gpio0 ( ccrf3_t *ctx );

/**
 * @brief Set sync mode function
 *
 * @param ctx               Click object.  
 *
 * @param s_mode
 * <pre>
 * Sync word configuration:
 * - 0x00 : No sync word
 * - 0x01 : 11 bits;
 * - 0x02 : 16 bits;
 * - 0x03 : 18 bits;
 * - 0x04 : 24 bits;
 * - 0x05 : 32 bits;
 * - 0x06 : 16H bits;
 * - 0x07 : 16D bits (DualSync search). When this setting is used in TX mode is transmitted;
 * </pre>
 *
 * @description Function set sync mode
 * by write s_mode value to the CCRF2_SYNC_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_sync_mode ( ccrf3_t *ctx, uint8_t s_mode );

/**
 * @brief Set sync number error function
 *
 * @param ctx               Click object.  
 *
 * @param num_err
 * <pre>
 * Bit check on sync word:
 * - 0x00 : 0 bit error in last received sync byte (normally SYNC0);
 * - 0x01 : < 2 bit error in last received sync byte (normally SYNC0);
 * - 0x02 : Reserved;
 * - 0x03 : Bit error qualifier disabled. No check on bit errors;
 * </pre>
 *
 * @description Function set sync number error
 * by write num_err value to the CCRF2_SYNC_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_sync_num_error ( ccrf3_t *ctx, uint8_t num_err );

/**
 * @brief Configuration modem mode function
 *
 * @param ctx               Click object. 
 * @param m_mode
 * <pre>
 * Modem mode configuration:
 * - 0x00 : Normal mode;
 * - 0x01 : DSSS repeat mode;
 * - 0x02 : DSSS PN mode;
 * - 0x03 : Reserved;
 * </pre>
 *
 * @description Function set configuration modem mode
 * by write m_mode value to the CCRF2_MODCFG_DEV_E register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_config_modem_mode ( ccrf3_t *ctx, uint8_t m_mode );

/**
 * @brief Set modulation format function
 *
 * @param ctx               Click object. 
 * @param m_format
 * <pre>
 * Modulation format:
 * - 0x00 : 2-FSK;
 * - 0x01 : 2-GFSK;
 * - 0x02 : Reserved;
 * - 0x03 : ASK/OOK;
 * - 0x04 : 4-FSK;
 * - 0x05 : 4-GFSK;
 * - 0x06 : Reserved;
 * - 0x07 : Reserved;
 * </pre>
 *
 * @description Function set modulation format
 * by write m_format value to the CCRF2_MODCFG_DEV_E register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_modulation_format ( ccrf3_t *ctx, uint8_t m_format );

/**
 * @brief Set digital DC removal configuration function
 *
 * @param ctx               Click object. 
 * @param n_samples
 * <pre>
 * Settling period of high pass DC filter after AGC adjustment:
 * - 32 :  32 samples;
 * - 64 :  64 samples;
 * - 128 : 128 samples;
 * - 256 : 256 samples;
 * - 512 : 512 samples;
 * </pre>
 *
 * @description Function set digital DC removal configuration
 * by write n_samples value to the CCRF2_DCFILT_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_dc_period_filter ( ccrf3_t *ctx, uint16_t n_samples );

/**
 * @brief Set the minimum number of preamble bits to be transmitted function
 *
 * @param ctx               Click object. 
 * @param m_number
 * <pre>
 * Minimum number of preamble bits to be transmitted:
 * - 0x00 : No preamble;
 * - 0x01 :  0.5 byte;
 * - 0x02 :  1   byte;
 * - 0x03 :  1.5 bytes;
 * - 0x04 :  2 bits;
 * - 0x05 :  3 bits;
 * - 0x06 :  4 bits;
 * - 0x07 :  5 bits;
 * - 0x08 :  6 bits;
 * - 0x09 :  7 bits;
 * - 0x0A :  8 bits;
 * - 0x0B : 12 bits;
 * - 0x0C : 24 bits;
 * - 0x0D : 30 bits;
 * - 0x0E : Reserved;
 * - 0x0F : Reserved;
 * </pre>
 *
 * @description Function set the minimum number of preamble bits to be transmitted
 * by write m_number value to the CCRF2_PREAMBLE_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_min_num_transmitted ( ccrf3_t *ctx, uint8_t m_number );

/**
 * @brief Configuration preamble byte function
 *
 * @param ctx               Click object. 
 * @param p_value
 * <pre>
 * Preamble byte configuration:
 * - 0x00 : 10101010 ( 0xAA );
 * - 0x01 : 01010101 ( 0x55 );
 * - 0x02 : 00110011 ( 0x33 );
 * - 0x03 : 11001100 ( 0xCC );
 * </pre>
 *
 * @description Function set configuration preamble byte
 * by write p_value value to the CCRF2_PREAMBLE_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_config_preamble ( ccrf3_t *ctx, uint8_t p_value );

/**
 * @brief Disabled preamble detection function
 *
 * @param ctx               Click object.
 * 
 * @description Function disabled preamble detection
 * by cleared to '0' [ bit 5 ] to the CCRF2_PREAMBLE_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_preamble_detection ( ccrf3_t *ctx );

/**
 * @brief Enabled preamble detection function
 *
 * @description Function enable preamble detection
 * by sets to '1' [ bit 5 ] to the CCRF2_PREAMBLE_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_preamble_detection ( ccrf3_t *ctx );

/**
 * @brief Sets the PQT start-up timer function
 *
 * @param ctx               Click object. 
 * @param v_timer
 * <pre>
 * Preamble byte configuration:
 * - 0x00 : Preamble detection disabled;
 * - 0x01 : Preamble detection enabled;
 * </pre>
 *
 * @description Function set the PQT start-up timer
 * by write v_timer value to the CCRF2_PREAMBLE_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_start_up_timer_pqt ( ccrf3_t *ctx, uint8_t v_timer );

/**
 * @brief Disabled IQ image compensation function
 *
 * @param ctx               Click object.
 * 
 * @description Function disabled preamble detection
 * by cleared to '0' [ bit 7 ] to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_iq_comp ( ccrf3_t *ctx );

/**
 * @brief Enabled IQ image compensation function
 *
 * @param ctx               Click object.
 * 
 * @description Function enable preamble detection
 * by sets to '1' [ bit 7 ] to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_iq_comp ( ccrf3_t *ctx );

/**
 * @brief Disabled IQIC update coefficients function
 *
 * @param ctx               Click object.
 * 
 * @description Function disabled preamble detection
 * by cleared to '0' [ bit 6 ] to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_iqic_coef ( ccrf3_t *ctx );

/**
 * @brief Enabled IQIC update coefficients function
 *
 * @param ctx               Click object.
 * 
 * @description Function enable preamble detection
 * by sets to '1' [ bit 6 ] to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_iqic_coef ( ccrf3_t *ctx );

/**
 * @brief Sets IQIC block length settling function
 *
 * @param ctx               Click object.
 *  
 * @param iqic_len
 * <pre>
 * IQIC block length when settling:
 * - 0x00 :   8 samples;
 * - 0x01 :  32 samples;
 * - 0x02 : 128 samples;
 * - 0x03 : 256 samples;
 * </pre>
 *
 * @description Function set IQIC block length settling
 * by write iqic_len value to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_iqic_block_length_settling ( ccrf3_t *ctx, uint8_t iqic_len );

/**
 * @brief Sets IQIC block length function
 *
 * @param ctx               Click object.
 *  
 * @param iqic_len
 * <pre> 
 * IQIC block length when:
 * - 0x00 :   8 samples;
 * - 0x01 :  32 samples;
 * - 0x02 : 128 samples;
 * - 0x03 : 256 samples;
 * </pre> 
 *
 * @description Function set IQIC block length
 * by write iqic_len value to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_iqic_block_length ( ccrf3_t *ctx, uint8_t iqic_len );

/**
 * @brief Sets IQIC image channel level threshold function
 *
 * @param ctx               Click object.
 *  
 * @param iqic_thr
 * <pre> 
 * IQIC block length when:
 * - 0x00 : >  256;
 * - 0x01 : >  512;
 * - 0x02 : > 1024;
 * - 0x03 : > 2048;
 * </pre>
 *
 * @description Function set IQIC image channel level threshold
 * by write iqic_len value to the CCRF2_IQIC register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_iqic_ch_lvl_threshold ( ccrf3_t *ctx, uint8_t iqic_thr );

/**
 * @brief Disabled channel filter ( bypassed ) function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled channel filter ( bypassed )
 * by cleared to '0' [ bit 7 ] to the CCRF2_CHAN_BW register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_ch_filter ( ccrf3_t *ctx );

/**
 * @brief Enabled channel filter function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable channel filter
 * by sets to '1' [ bit 7 ] to the CCRF2_CHAN_BW register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_ch_filter ( ccrf3_t *ctx );

/**
 * @brief Disabled FIFO function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled FIFO
 * by cleared to '0' [ bit 6 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_fifo ( ccrf3_t *ctx );

/**
 * @brief Enabled FIFO function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable FIFO
 * by sets to '1' [ bit 6 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_fifo ( ccrf3_t *ctx );

/**
 * @brief Disabled the Manchester mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the Manchester mode
 * by cleared to '0' [ bit 5 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_manchester_mode ( ccrf3_t *ctx );

/**
 * @brief Enabled the Manchester mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the Manchester mode
 * by sets to '1' [ bit 5 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_manchester_mode ( ccrf3_t *ctx );

/**
 * @brief Disabled the invert data function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the invert data
 * by cleared to '0' [ bit 4 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_invert_data ( ccrf3_t *ctx );

/**
 * @brief Enabled the invert data function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the invert data
 * by sets to '1' [ bit 4 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_invert_data ( ccrf3_t *ctx );

/**
 * @brief Disabled the collision detect function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the collision detect
 * by cleared to '0' [ bit 3 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_collision_detect ( ccrf3_t *ctx );

/**
 * @brief Enabled the collision detect function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the collision detect
 * by sets to '1' [ bit 3 ] to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_collision_detect ( ccrf3_t *ctx );

/**
 * @brief Sets fixed DVGA gain configuration function
 *
 * @param ctx               Click object. 
 * @param dvga_gain
 * <pre>
 * Fixed DVGA gain configuration:
 * - 0x00 : 0 dB DVGA;
 * - 0x01 : 3 dB DVGA;
 * - 0x02 : 6 dB DVGA;
 * - 0x03 : 9 dB DVGA;
 * </pre>
 *
 * @description Function set fixed DVGA gain configuration
 * by write dvga_gain value to the CCRF2_MDMCFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_dvga_gain ( ccrf3_t *ctx, uint8_t dvga_gain );

/**
 * @brief Disabled the transparent mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the transparent mode
 * by cleared to '0' [ bit 3 ] to the CCRF2_MDMCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_transparent_mode ( ccrf3_t *ctx );

/**
 * @brief Enabled the transparent mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the transparent mode
 * by sets to '1' [ bit 3 ] to the CCRF2_MDMCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_transparent_mode ( ccrf3_t *ctx );

/**
 * @brief Sets transparent data filter function
 *
 * @param ctx               Click object. 
 * @param t_data
 * <pre>
 * - 0x00 : Transparent data filter disabled and extended data filter disabled;
 * - 0x01 : Transparent data filter disabled and extended data filter enabled;
 * </pre>
 *
 * @description Function set transparent data filter
 * by write t_data value to the CCRF2_MDMCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_transparent_data_filter ( ccrf3_t *ctx, uint8_t t_data );

/**
 * @brief Disabled the viterbi detection function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the viterbi detection
 * by cleared to '0' [ bit 2 ] to the CCRF2_MDMCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_viterbi_detection ( ccrf3_t *ctx );

/**
 * @brief Enabled the viterbi detection function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the viterbi detection
 * by sets to '1' [ bit 2 ] to the CCRF2_MDMCFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_viterbi_detection ( ccrf3_t *ctx );

/**
 * @brief Sets the RSSI threshold function
 *
 * @param ctx               Click object. 
 * @param rssi_thr
 * <pre>
 * - 0x00 : Viterbi detection disabled;
 * - 0x01 : Viterbi detection enabled;
 * </pre>
 *
 * @description Function set the RSSI threshold
 * by write rssi_thr value to the CCRF2_AGC_CFG3 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_rssi_threshold ( ccrf3_t *ctx, uint8_t rssi_thr );

/**
 * @brief Set receiver starts with maximum gain value function
 *
 * @param ctx               Click object.
 *  
 * @description Function set receiver starts with maximum gain value
 * by cleared to '0' [ bit 7 ] to the CCRF2_AGC_CFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_receiver_max_gain ( ccrf3_t *ctx );

/**
 * @brief Set receiver starts from previous gain value function
 *
 * @param ctx               Click object.
 *  
 * @description Function set receiver starts from previous gain value
 * by sets to '1' [ bit 7 ] to the CCRF2_AGC_CFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_receiver_previous_gain ( ccrf3_t *ctx );

/**
 * @brief Sets the performance mode function
 *
 * @param ctx               Click object. 
 * @param p_mode
 * <pre> 
 * - 0x00 : Optimized linearity mode;
 * - 0x01 : Normal operation mode;
 * - 0x02 : Low power mode with reduced gain range;
 * - 0x03 : Reserved;
 * </pre>
 *
 * @description Function set the performance mode
 * by write p_mode value to the CCRF2_AGC_CFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_performance_mode ( ccrf3_t *ctx, uint8_t p_mode );

/**
 * @brief Sets the AGC behavior after sync word detection function
 *
 * @param ctx               Click object. 
 * @param agc_value
 * <pre>
 * AGC behavior after sync word detection:
 * - 0x00 : No AGC gain freeze. Keep computing/updating RSSI;
 * - 0x01 : AGC gain freeze. Keep computing/updating RSSI;
 * - 0x02 : No AGC gain freeze. Keep computing/updating RSSI;
 * - 0x03 : Freeze both AGC gain and RSSI;
 * - 0x04 : No AGC gain freeze. Keep computing/updating RSSI;
 * - 0x05 : Freeze both AGC gain and RSSI;
 * - 0x06 : No AGC gain freeze. Keep computing/updating RSSI;
 * - 0x07 : Freeze both AGC gain and RSSI;
 * </pre> 
 *
 * @description Function set the AGC behavior after sync word detection
 * by write agc_value value to the CCRF2_AGC_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_agc_behavior ( ccrf3_t *ctx, uint8_t agc_value );

/**
 * @brief Sets the AGC integration window size for each value function
 *
 * @param ctx               Click object. 
 * @param agc_value
 * <pre>
 * AGC integration window size for each value:
 * - 0x00 :   8 samples;
 * - 0x01 :  16 samples;
 * - 0x02 :  32 samples;
 * - 0x03 :  64 samples;
 * - 0x04 : 128 samples;
 * - 0x05 : 256 samples;
 * - 0x06 : Reserved;
 * - 0x07 : Reserved;
 * </pre>
 *
 * @description Function set the AGC integration window size for each value
 * by write agc_value value to the CCRF2_AGC_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_agc_integration ( ccrf3_t *ctx, uint8_t agc_value );

/**
 * @brief Sets the wait time between AGC gain adjustments function
 *
 * @param ctx               Click object. 
 * @param agc_value
 * <pre>
 * Wait time between AGC gain adjustments:
 * - 0x00 : 24 samples;
 * - 0x01 : 32 samples;
 * - 0x02 : 40 samples;
 * - 0x03 : 48 samples;
 * </pre>
 *
 * @description Function set the wait time between AGC gain adjustments
 * by write agc_value value to the CCRF2_AGC_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_wait_time_agc_gain ( ccrf3_t *ctx, uint8_t w_time );

/**
 * @brief Sets the AGC hysteresis level function
 *
 * @param ctx               Click object. 
 * @param agc_value
 * <pre>
 * AGC hysteresis level:
 * - 0x00 :  2 dB;
 * - 0x01 :  4 dB;
 * - 0x02 :  7 dB;
 * - 0x03 : 10 dB;
 * </pre>
 *
 * @description Function set the AGC hysteresis level
 * by write agc_value value to the CCRF2_AGC_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_agc_hysteresis_lvl ( ccrf3_t *ctx, uint8_t agc_value );

/**
 * @brief Sets the AGC slew rate limit function
 *
 * @param ctx               Click object. 
 * @param agc_value
 * <pre>
 * AGC slew rate limit:
 * - 0x00 : 60 dB;
 * - 0x01 : 30 dB;
 * - 0x02 : 18 dB;
 * - 0x03 :  9 dB;
 *  </pre>
 * @description Function set the AGC slew rate limit
 * by write agc_value value to the CCRF2_AGC_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_agc_slew_rate_limit ( ccrf3_t *ctx, uint8_t agc_value );

/**
 * @brief Sets the number of new input samples before the next update of the RSSI function
 *
 * @param ctx               Click object. 
 * @param rssi_cnt
 * <pre>
 * - 0x00 : 2;
 * - 0x01 : 3;
 * - 0x02 : 5;
 * - 0x03 : 9;
 * </pre> 
 *
 * @description Function set the the number of new input samples before the next update of the RSSI
 * by write rssi_cnt value to the CCRF2_AGC_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_rssi_valid_cnt ( ccrf3_t *ctx, uint8_t rssi_cnt );

/**
 * @brief Sets the decimation factor function
 *
 * @param ctx               Click object. 
 * @param dec_factor
 * <pre> 
 * The decimation factor is given:
 * - 0x00 :  600 samples;
 * - 0x01 : 1200 samples;
 * - 0x02 : 2500 samples;
 * - 0x03 : 5000 samples;
 * </pre>
 *
 * @description Function set the decimation factor
 * by write dec_factor value to the CCRF2_AGC_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_decimation_factor ( ccrf3_t *ctx, uint8_t dec_factor );

/**
 * @brief Sets the address used for packet filtering in RX function
 *
 * @param ctx               Click object. 
 * @param dev_addr 8-bit device address used for packet filtering
 *
 * @description Function set the address used for packet filtering in RX
 * by write dev_addr value to the CCRF2_DEV_ADDR register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_address_packet_rx ( ccrf3_t *ctx, uint8_t dev_addr );

/**
 * @brief Disabled the out of lock detector function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the out of lock detector
 * by cleared to '0' [ bit 4 ] to the CCRF2_FS_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_out_of_lock_detector ( ccrf3_t *ctx );

/**
 * @brief Enabled the out of lock detector function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the out of lock detector
 * by sets to '1' [ bit 4 ] to the CCRF2_FS_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_out_of_lock_detector ( ccrf3_t *ctx );

/**
 * @brief Select the band setting for LO divider function
 *
 * @param ctx               Click object. 
 * @param band_settings
 * <pre>
 * Band setting for LO divider:
 * - 0x00 : Not in use;
 * - 0x01 : Not in use;
 * - 0x02 : 820.0 - 960.0 MHz band;
 * - 0x03 : Not in use;
 * - 0x04 : 410.0 - 480.0 MHz band;
 * - 0x05 : Not in use;
 * - 0x06 : 273.3 - 320.0 MHz band;
 * - 0x07 : Not in use;
 * - 0x08 : 205.0 - 240.0 MHz band;
 * - 0x09 : Not in use;
 * - 0x0A : 164.0 - 192.0 MHz band;
 * - 0x0B : 136.7 - 160.0 MHz band;
 * - 0x0C : Not in use;
 * - 0x0D : Not in use;
 * - 0x0E : Not in use;
 * - 0x0F : Not in use;
 * </pre>
 *
 * @description Function set the band setting for LO divider
 * by write band_settings value to the CCRF2_FS_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_select_band_settings ( ccrf3_t *ctx, uint8_t band_settings );

/**
 * @brief Set the eWOR timer resolution function
 *
 * @param ctx               Click object.
 * @param wor_res
 * <pre>
 * - 0x00 : High resolution;
 * - 0x01 : Medium high resolution;
 * - 0x02 : Medium low resolution;
 * - 0x03 : Low resolution;
 * </pre>
 *
 * @description Function set the eWOR timer resolution
 * by write wor_res value to the CCRF2_WOR_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_wor_resolution ( ccrf3_t *ctx, uint8_t wor_res );

/**
 * @brief Set the eWOR mode resolution function
 *
 * @param ctx               Click object. 
 * @param w_mode
 * <pre>
 * eWOR mode:
 * - 0x00 : Feedback mode;
 * - 0x01 : Normal mode;
 * - 0x02 : Legacy mode;
 * - 0x03 : Event1 mask mode;
 * - 0x04 : Event0 mask mode;
 * - 0x05 : Reserved;
 * - 0x06 : Reserved;
 * - 0x07 : Reserved;
 * </pre>
 *
 * @description Function set the eWOR mode
 * by write w_mode value to the CCRF2_WOR_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_wor_mode ( ccrf3_t *ctx, uint8_t w_mode );

/**
 * @brief Set the event timeout function
 *
 * @param ctx               Click object. 
 * @param e_timeout
 * <pre> 
 * Event 1 timeout:
 * - 0x00 :  4;
 * - 0x01 :  6;
 * - 0x02 :  8;
 * - 0x03 : 12;
 * - 0x04 : 16;
 * - 0x05 : 24;
 * - 0x06 : 32;
 * - 0x07 : 48;
 * </pre>
 *
 * @description Function set the event timeout
 * by write e_timeout value to the CCRF2_WOR_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_event_timeout ( ccrf3_t *ctx, uint8_t e_timeout );

/**
 * @brief Disabled the clock division in SLEEP mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the clock division in SLEEP mode
 * by cleared to '0' [ bit 5 ] to the CCRF2_WOR_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_clock_division ( ccrf3_t *ctx );

/**
 * @brief Enabled the clock division in SLEEP mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the clock division in SLEEP mode
 * by sets to '1' [ bit 5 ] to the CCRF2_WOR_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_clock_division ( ccrf3_t *ctx );

/**
 * @brief Set the definition of a clear channel function
 *
 * @param ctx               Click object. 
 * @param cca_mode
 * <pre> 
 * CCA mode:
 * - 0x00 : Always give a clear channel indication;
 * - 0x01 : Indicates clear channel when RSSI is below threshold;
 * - 0x02 : Indicates clear channel unless currently receiving a packet;
 * - 0x03 : Indicates clear channel when RSSI is below threshold and currently not receiving a packet;
 * - 0x04 : Indicates clear channel when RSSI is below threshold and ETSI LBT requirements are met;
 * - 0x05 : Reserved;
 * - 0x06 : Reserved;
 * - 0x07 : Reserved;
 * </pre> 
 *
 * @description Function set the definition of a clear channel
 * by write cca_mode value to the CCRF2_PKT_CFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_cca_mode ( ccrf3_t *ctx, uint8_t cca_mode );

/**
 * @brief Set the packet format configuration function
 *
 * @param ctx               Click object. 
 * @param p_format
 * <pre> 
 * Packet format configuration:
 * - 0x00 : Normal mode/FIFO mode;
 * - 0x01 : Synchronous serial mode;
 * - 0x02 : Random mode;
 * - 0x03 : Transparent serial mode;
 * </pre> 
 *
 * @description Function set the packet format configuration
 * by write p_format value to the CCRF2_PKT_CFG2 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_packet_format( ccrf3_t *ctx, uint8_t p_format );

/**
 * @brief Disabled the data whitening function
 *
 * @param ctx               Click object.
 * 
 * @description Function disabled the data whitening
 * by cleared to '0' [ bit 6 ] to the CCRF2_PKT_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_data_whitening ( ccrf3_t *ctx );

/**
 * @brief Enabled the data whitening function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the data whitening
 * by sets to '1' [ bit 6 ] to the CCRF2_PKT_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_data_whitening ( ccrf3_t *ctx );

/**
 * @brief Set the CRC configuration function
 *
 * @param ctx               Click object. 
 * @param crc_config
 * <pre> 
 * CRC configuration:
 * - 0x00 : CRC disabled for TX and RX;
 * - 0x01 : CRC calculation in TX mode and CRC check in RX mode enabled. Initialized to 0xFFFF;
 * - 0x02 : CRC calculation in TX mode and CRC check in RX mode enabled. Initialized to 0x0000;
 * - 0x03 : Reserved;
 * </pre> 
 *
 * @description Function set the CRC configuration
 * by write crc_config value to the CCRF2_PKT_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_crc_config ( ccrf3_t *ctx, uint8_t crc_config );

/**
 * @brief Disabled the data byte swap function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the data byte swap
 * by cleared to '0' [ bit 1 ] to the CCRF2_PKT_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_data_swap ( ccrf3_t *ctx );

/**
 * @brief Enabled the data byte swap function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the data byte swap
 * by sets to '1' [ bit 1 ] to the CCRF2_PKT_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_data_swap ( ccrf3_t *ctx );

/**
 * @brief Append status bytes to RX FIFO function
 *
 * @param ctx               Click object. 
 * @param crc_config
 * <pre> 
 * CRC configuration:
 * - 0x00 : Data byte swap disabled;
 * - 0x01 : Data byte swap enabled;
 * </pre>
 *
 * @description Function set append status bytes to RX FIFO
 * by write appStatus value to the CCRF2_PKT_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_append_status ( ccrf3_t *ctx, uint8_t app_status );

/**
 * @brief Disabled the UART mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the UART mode
 * by cleared to '0' [ bit 1 ] to the CCRF2_PKT_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_uart_mode ( ccrf3_t *ctx );


/**
 * @brief Enabled the UART mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function enable the UART mode
 * by sets to '1' [ bit 1 ] to the CCRF2_PKT_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_uart_mode ( ccrf3_t *ctx );

/**
 * @brief Disabled the UART swap function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the UART mode
 * by cleared to '0' [ bit 0 ] to the CCRF2_PKT_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_uart_swap ( ccrf3_t *ctx );

/**
 * @brief Enabled the UART swap function
 *
 * @param ctx               Click object.
 * 
 * @description Function enabled the UART mode
 * by sets to '1' [ bit 0 ] to the CCRF2_PKT_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_uart_swap ( ccrf3_t *ctx );

/**
 * @brief Set RXOFF mode function
 *
 * @param ctx               Click object.
 * @param rxoff_mode
 * <pre> 
 * RXOFF mode:
 * - 0x00 : IDLE;
 * - 0x01 : FSTXON;
 * - 0x02 : TX;
 * - 0x03 : RX;
 * </pre>
 *
 * @description Function set RXOFF mode
 * by write rxoff_mode value to the CCRF2_RFEND_CFG1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_rx_off_mode ( ccrf3_t *ctx, uint8_t rx_off_mode );

/**
 * @brief Set TXOFF mode function
 *
 * @param ctx               Click object. 
 * @param txoff_mode
 * <pre>
 * TXOFF mode:
 * - 0x00 : IDLE;
 * - 0x01 : FSTXON;
 * - 0x02 : TX;
 * - 0x03 : RX;
 * </pre>
 *
 * @description Function set TXOFF mode
 * by write txoff_mode value to the CCRF2_RFEND_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_tx_off_mode ( ccrf3_t *ctx, uint8_t tx_off_mode );

/**
 * @brief Set TX upsampler function
 *
 * @param ctx               Click object. 
 * @param tx_upsampler
 * <pre> 
 * The upsampler reduces repetitive spectrum at 16�symbol rate:
 * - 0x00 : TX upsampler factor P = 1 (bypassed);
 * - 0x01 : TX upsampler factor P = 2;
 * - 0x02 : TX upsampler factor P = 4;
 * - 0x03 : TX upsampler factor P = 8;
 * - 0x04 : TX upsampler factor P = 16;
 * - 0x05 : TX upsampler factor P = 32;
 * - 0x06 : TX upsampler factor P = 64;
 * - 0x07 : Not used;
 * </pre>
 *
 * @description Function set TX upsampler
 * by write tx_upsampler value to the CCRF2_RFEND_CFG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_tx_upsampler ( ccrf3_t *ctx, uint8_t tx_upsampler );

/**
 * @brief Set the packet length function
 *
 * @param ctx               Click object. 
 * @param pack_len 8-bit packet length data
 *
 * @description Function set the packet length
 * by write pack_len value to the CCRF2_PKT_LEN register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_packet_length ( ccrf3_t *ctx, uint8_t pack_len );

/**
 * @brief Disabled the frequency offset correction function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the frequency offset correction
 * by cleared to '0' [ bit 5 ] to the CCRF2_FREQOFF_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_freq_offset_correction ( ccrf3_t *ctx );

/**
 * @brief Enabled the frequency offset correction function
 *
 * @param ctx               Click object.
 *  
 * @description Function enabled the frequency offset correction
 * by sets to '1' [ bit 5 ] to the CCRF2_FREQOFF_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_freq_offset_correction ( ccrf3_t *ctx );

/**
 * @brief Set the external clock frequency function
 *
 * @param ctx               Click object. 
 * @param ec_freq
 * <pre> 
 * External clock frequency. Controls division factor:
 * - 0x00 : 64;
 * - 0x01 : 62;
 * - 0x02 : 60;
 * - 0x03 : 58;
 * - 0x04 : 56;
 * - 0x05 : 54;
 * - 0x06 : 52;
 * - 0x07 : 50;
 * - 0x08 : 48;
 * - 0x09 : 46;
 * - 0x0A : 44;
 * - 0x0B : 42;
 * - 0x0C : 40;
 * - 0x0D : 38;
 * - 0x0E : 36;
 * - 0x0F : 34;
 * - 0x10 : 32;
 * - 0x11 : 30;
 * - 0x12 : 28;
 * - 0x13 : 26;
 * - 0x14 : 24;
 * - 0x15 : 22;
 * - 0x16 : 20;
 * - 0x17 : 18;
 * - 0x18 : 16;
 * - 0x19 : 14;
 * - 0x1A : 12;
 * - 0x1B : 10;
 * - 0x1C :  8;
 * - 0x1D :  6;
 * - 0x1E :  4;
 * - 0x1F :  6;
 * </pre>
 *
 * @description Function set the external clock frequency
 * by write ec_freq value to the CCRF2_ECG_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_ext_clock_freq ( ccrf3_t *ctx, uint8_t ec_freq );

/**
 * @brief Disabled the CFM mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function disabled the CFM mode
 * by cleared to '0' [ bit 0 ] to the CCRF2_FREQOFF_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_disable_cfm_mode ( ccrf3_t *ctx );

/**
 * @brief Enabled the CFM mode function
 *
 * @param ctx               Click object.
 *  
 * @description Function enabled the CFM mode
 * by sets to '1' [ bit 0 ] to the CCRF2_FREQOFF_CFG register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_enable_cfm_mode ( ccrf3_t *ctx );

/**
 * @brief Set frequency offset function
 *
 * @param ctx               Click object. 
 * @param freq_offset 16-bit frequency offset value
 *
 * @description Function sets frequency offset by write freq_offset value
 * to the CCRF2_FREQOFF1 and CCRF2_FREQOFF0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_freq_offset ( ccrf3_t *ctx, uint16_t freq_offset );

/**
 * @brief Set frequency synthesizer loop bandwidth in RX function
 *
 * @param ctx               Click object. 
 * @param fslb_rx
 * <pre> 
 * FS loop bandwidth in RX:
 * - 0x00 : 101.6 kHz;
 * - 0x01 : 131.7 kHz;
 * - 0x02 : 150   kHz;
 * - 0x03 : 170.8 kHz;
 * </pre> 
 *
 * @description Function sets frequency synthesizer loop bandwidth in RX
 * by write fslb_rx value to the CCRF2_FS_DIG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_fs_loop_bandwidth_rx ( ccrf3_t *ctx, uint8_t fslb_rx );

/**
 * @brief Set frequency synthesizer loop bandwidth in TX function
 *
 * @param ctx               Click object. 
 * @param fslb_tx
 * <pre> 
 * FS loop bandwidth in TX:
 * - 0x00 : 101.6 kHz;
 * - 0x01 : 131.7 kHz;
 * - 0x02 : 150   kHz;
 * - 0x03 : 170.8 kHz;
 * </pre> 
 *
 * @description Function sets frequency synthesizer loop bandwidth in TX
 * by write fslb_tx value to the CCRF2_FS_DIG0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_fs_loop_bandwidth_tx ( ccrf3_t *ctx, uint8_t fslb_tx );

/**
 * @brief Set out of lock detector average time function
 *
 * @param ctx               Click object. 
 * @param avr_time
 * <pre> 
 * Out of lock detector average time:
 * - 0x00 : Average the measurement over 512 cycles;
 * - 0x01 : Average the measurement over 1024 cycles;
 * - 0x02 : Average the measurement over 256 cycles;
 * - 0x03 : Infinite average;
 * </pre>
 *
 * @description Function sets out of lock detector average time
 * by write avr_time value to the CCRF2_FS_CAL0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_out_of_lock_avr_time ( ccrf3_t *ctx, uint8_t avr_time );

/**
 * @brief Set DC compensation real value function
 *
 * @param ctx               Click object. 
 * @param dc_comp_real 16-bit DC compensation, real value
 *
 * @description Function sets DC compensation real value by write dc_comp_real value
 * to the CCRF2_DCFILTOFFSET_I1 and CCRF2_DCFILTOFFSET_I0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_dc_comp_real ( ccrf3_t *ctx, uint16_t dc_comp_real );

/**
 * @brief Set DC compensation imaginary value function
 *
 * @param ctx               Click object. 
 * @param dc_comp_real 16-bit DC compensation, imaginary value
 *
 * @description Function sets DC compensation imaginary value by write dcCompIm value
 * to the CCRF2_DCFILTOFFSET_Q1 and CCRF2_DCFILTOFFSET_Q0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_dc_comp_imaginary ( ccrf3_t *ctx, uint16_t dc_comp_im );

/**
 * @brief Set IQ imbalance real value function
 *
 * @param ctx               Click object. 
 * @param dc_imb_real 16-bit IQ imbalance value, real value
 *
 * @description Function sets IQ imbalance real value by write dc_imb_real value
 * to the CCRF2_IQIE_I1 and CCRF2_IQIE_I0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_iq_imbalance_real ( ccrf3_t *ctx, uint16_t dc_imb_real );

/**
 * @brief Set IQ imbalance imaginary value function
 *
 * @param ctx               Click object. 
 * @param dc_imb_im 16-bit IQ imbalance value, imaginary value
 *
 * @description Function sets IQ imbalance imaginary value by write dc_imb_im value
 * to the CCRF2_IQIE_Q1 and CCRF2_IQIE_Q0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
void ccrf3_set_iq_imbalance_imaginary ( ccrf3_t *ctx, uint16_t dc_imb_im );

/**
 * @brief Get MARC state function
 *
 * @param ctx               Click object.
 * 
 * @returns
 * <pre>
 *          MARC state     | MARC 2 pin state value:
 * - 0x00 : SLEEP          | Depends on the GPIO pins used;
 * - 0x01 : IDLE           | IDLE;
 * - 0x02 : XOFF           | SETTLING;
 * - 0x03 : BIAS_SETTLE_MC | SETTLING;
 * - 0x04 : REG_SETTLE_MC  | SETTLING;
 * - 0x05 : MANCAL         | SETTLING;
 * - 0x06 : BIAS_SETTLE    | SETTLING;
 * - 0x07 : REG_SETTLE     | SETTLING;
 * - 0x08 : STARTCAL       | SETTLING;
 * - 0x09 : BWBOOST        | SETTLING;
 * - 0x0A : FS_LOCK        | SETTLING;
 * - 0x0B : IFADCON        | SETTLING;
 * - 0x0C : ENDCAL         | SETTLING;
 * - 0x0D : RX             | RX;
 * - 0x0E : RX_END         | RX;
 * - 0x0F : Reserved       | RX;
 * - 0x10 : TXRX_SWITCH    | SETTLING;
 * - 0x11 : RX_FIFO_ERR    | SETTLING;
 * - 0x12 : FSTXON         | SETTLING;
 * - 0x13 : TX             | TX;
 * - 0x14 : TX_END         | TX;
 * - 0x15 : RXTX_SWITCH    | SETTLING;
 * - 0x16 : TX_FIFO_ERR    | SETTLING;
 * - 0x17 : IFADCON_TXRX   | SETTLING;
 * - 0x18 : Not used;
 * - 0x19 : Not used;
 * - 0x1A : Not used;
 * - 0x1B : Not used;
 * - 0x1C : Not used;
 * - 0x1D : Not used;
 * - 0x1E : Not used;
 * - 0x1F : Not used;
 * </pre> 
 *
 * @description Function gets MARC state by read 8-bit value
 * from the CCRF2_MARCSTATE register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_marc_state ( ccrf3_t *ctx );

/**
 * @brief Get Chip ID function
 *
 * @param ctx               Click object.
 *  
 * @returns
 * <pre>
 * 8-bit Chip ID value
 * - 0x40 : CC1121;
 * - 0x48 : CC1120;
 * - 0x58 : CC1125;
 * - 0x5A : CC1175;
 * </pre>
 *
 * @description Function gets Chip ID by read 8-bit value
 * from the CCRF2_PARTNUMBER register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_chip_id ( ccrf3_t *ctx );

/**
 * @brief Get part revision function
 *
 * @param ctx               Click object.
 *  
 * @returns 8-bit Chip revision
 *
 * @description Function gets part revision by read 8-bit value
 * from the CCRF2_PARTVERSION register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_part_vision ( ccrf3_t *ctx );

/**
 * @brief Get serial status function
 *
 * @param ctx               Click object.
 *  
 * @returns  8-bit Chip ID value
 * <pre> 
 * - [ bit 7:5 ] : Not used;
 * - [ bit 4 ]   : Internal 32/40 kHz RC oscillator clock;
 * - [ bit 3 ]   : Enable synchronizer for IO pins. Required for transparent TX and for reading;
 * - [ bit 2 ]   : Modulator soft data clock ( 16 times higher than the programmed symbol rate );
 * - [ bit 1 ]   : Serial RX data;
 * - [ bit 0 ]   : Serial RX data clock;
 * </pre> 
 *
 * @description Function gets serial status by read 8-bit value
 * from the CCRF2_SERIAL_STATUS register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_serial_status ( ccrf3_t *ctx );

/**
 * @brief Get modem status register 1 function
 *
 * @param ctx               Click object.
 *  
 * @returns
 * <pre> 
 * modem status register 1:
 * - [ bit 7 ] : Asserted simultaneously;
 * - [ bit 6 ] : Asserted when number of bytes is greater than the RX FIFO threshold;
 * - [ bit 5 ] : Asserted when number of bytes is greater than the RX FIFO threshold;
 * - [ bit 4 ] : High when no bytes reside in the RX FIFO;
 * - [ bit 3 ] : Asserted when the RX FIFO has overflowed (the radio has received more bytes after the RXFIFO is full);
 * - [ bit 2 ] : Asserted if the user try to read from an empty RX FIFO;
 * - [ bit 1 ] : Asserted when a preamble is detected (the preamble qualifier value is less than the programmed PQT threshold);
 * - [ bit 0 ] : Asserted after 16 or 43 bits are received or after a preamble is detected;
 * </pre>
 *
 * @description Function gets modem status register 1 by read 8-bit value
 * from the CCRF2_MODEM_STATUS1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_modem_status1 ( ccrf3_t *ctx );

/**
 * @brief Get modem status register 0 function
 *
 * @param ctx               Click object.
 *  
 * @returns
 * <pre> 
 * modem status register 0:
 * - [ bit 7:6 ] : Not used;
 * - [ bit 5 ]   : For test purposes only;
 * - [ bit 4 ]   : Last bit of sync word has been sent;
 * - [ bit 3 ]   : Asserted when the TX FIFO is full. De-asserted when the number of bytes is below threshold;
 * - [ bit 2 ]   : Asserted when number of bytes is greater than or equal to the TX FIFO threshold. De-asserted when the TX FIFO is drained below the same threshold;
 * - [ bit 1 ]   : Asserted when the TX FIFO has overflowed (The user have tried to write to a full TX FIFO). De-asserted when the TX FIFO is flushed;
 * - [ bit 0 ]   : Asserted when the TX FIFO has underflowed (TX FIFO is empty before the complete packet is sent). De-asserted when the TX FIFO is flushed;
 * </pre>
 *
 * @description Function gets modem status register 0 by read 8-bit value
 * from the CCRF2_MODEM_STATUS0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_modem_status0 ( ccrf3_t *ctx );

/**
 * @brief Get MARC status register 1 function
 *
 * @param ctx               Click object.
 *  
 * @returns
 * <pre> 
 * MARC status register 1:
 * - 0x00 ( 00000000 ) : No failure;
 * - 0x01 ( 00000001 ) : RX timeout occurred;
 * - 0x02 ( 00000010 ) : RX termination based on CS or PQT;
 * - 0x03 ( 00000011 ) : eWOR sync lost ( 16 slots with no successful reception );
 * - 0x04 ( 00000100 ) : Packet discarded due to maximum length filtering;
 * - 0x05 ( 00000101 ) : Packet discarded due to address filtering;
 * - 0x06 ( 00000110 ) : Packet discarded due to CRC filtering;
 * - 0x07 ( 00000111 ) : TX FIFO overflow error occurred;
 * - 0x08 ( 00001000 ) : TX FIFO underflow error occurred;
 * - 0x09 ( 00001001 ) : RX FIFO overflow error occurred;
 * - 0x0A ( 00001010 ) : RX FIFO underflow error occurred;
 * - 0x0B ( 00001011 ) : TX ON CCA failed;
 * - 0x40 ( 01000000 ) : TX finished successfully;
 * - 0x80 ( 10000000 ) : RX finis;
 * </pre> 
 *
 * @description Function gets MARC status register 1 by read 8-bit value
 * from the CCRF2_MARC_STATUS1 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_marc_status1 ( ccrf3_t *ctx );

/**
 * @brief Get MARC status register 0 function
 *
 * @param ctx               Click object.
 *  
 * @returns
 * <pre> 
 * MARC status register 0:
 * - [ bit 7:4 ] : Not used;
 * - [ bit 3 ]   : For test purposes only;
 * - [ bit 2 ]   : This bit can be read after the TXONCCA_DONE signal has been asserted;
 * - [ bit 1 ]   : For test purposes only;
 * - [ bit 0 ]   : RCOSC has been calibrated at least once;
 * </pre>
 *
 * @description Function gets MARC status register 0 by read 8-bit value
 * from the CCRF2_MARC_STATUS0 register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_marc_status0 ( ccrf3_t *ctx );

/**
 * @brief Get RX FIFO pointer first entry function
 *
 * @param ctx               Click object.
 *  
 * @returns Pointer to the first entry in the RX FIFO
 *
 * @description Function gets RX FIFO pointer first entry by read 8-bit value
 * from the CCRF2_RXFIRST register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_rx_fifo_pointer_first ( ccrf3_t *ctx );

/**
 * @brief Get TX FIFO pointer first entry function
 *
 * @param ctx               Click object.
 *  
 * @returns Pointer to the first entry in the TX FIFO
 *
 * @description Function gets TX FIFO pointer first entry by read 8-bit value
 * from the CCRF2_TXFIRST register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_tx_fifo_pointer_first ( ccrf3_t *ctx );

/**
 * @brief Get RX FIFO pointer last entry function
 *
 * @param ctx               Click object.
 *  
 * @returns Pointer to the last entry in the RX FIFO
 *
 * @description Function gets RX FIFO pointer last entry by read 8-bit value
 * from the CCRF2_RXLAST register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_rx_fifo_pointer_last ( ccrf3_t *ctx );

/**
 * @brief Get TX FIFO pointer last entry function
 *
 * @param ctx               Click object.
 *  
 * @returns Pointer to the last entry in the TX FIFO
 *
 * @description Function gets TX FIFO pointer last entry by read 8-bit value
 * from the CCRF2_TXLAST register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_tx__fifo_pointer_last ( ccrf3_t *ctx );

/**
 * @brief Get number of bytes in the TX FIFO function
 *
 * @param ctx               Click object.
 *  
 * @returns Number of bytes in the TX FIFO
 *
 * @description Function gets number of bytes in the TX FIFO entry by read 8-bit value
 * from the CCRF2_NUM_TXBYTES register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_rx_fifo_status ( ccrf3_t *ctx );

/**
 * @brief Get number of bytes in the RX FIFO function
 *
 * @param ctx               Click object.
 *  
 * @returns Number of bytes in the RX FIFO
 *
 * @description Function gets number of bytes in the RX FIFO entry by read 8-bit value
 * from the CCRF2_NUM_RXBYTES register of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_tx_fifo_status ( ccrf3_t *ctx );

/**
 * @brief Get state of interrupt function
 *
 * @param ctx               Click object.
 *  
 * @returns
 * <pre>
 * States of interrupt
 * - 0 : No active;
 * - 1 : Active;
 * </pre>
 *
 * @description Function getsstate of interrupt of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 */
uint8_t ccrf3_get_interrupt ( ccrf3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CCRF3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

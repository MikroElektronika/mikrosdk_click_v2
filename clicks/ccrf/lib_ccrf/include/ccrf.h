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
 * \brief This file contains API for ccRF Click driver.
 *
 * \addtogroup ccrf ccRF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CCRF_H
#define CCRF_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define CCRF_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.gd0   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.gd2   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CCRF_OK                     0
#define CCRF_ERROR                 -1
/** \} */

// Configuration Registers
#define CCRF_IOCFG2                 0x00
#define CCRF_IOCFG1                 0x01
#define CCRF_IOCFG0                 0x02
#define CCRF_FIFOTHR                0x03
#define CCRF_SYNC1                  0x04
#define CCRF_SYNC0                  0x05
#define CCRF_PKTLEN                 0x06
#define CCRF_PKTCTRL1               0x07
#define CCRF_PKTCTRL0               0x08
#define CCRF_ADDR                   0x09
#define CCRF_CHANNR                 0x0A
#define CCRF_FSCTRL1                0x0B
#define CCRF_FSCTRL0                0x0C
#define CCRF_FREQ2                  0x0D
#define CCRF_FREQ1                  0x0E
#define CCRF_FREQ0                  0x0F
#define CCRF_MDMCFG4                0x10
#define CCRF_MDMCFG3                0x11
#define CCRF_MDMCFG2                0x12
#define CCRF_MDMCFG1                0x13
#define CCRF_MDMCFG0                0x14
#define CCRF_DEVIATN                0x15
#define CCRF_MCSM2                  0x16
#define CCRF_MCSM1                  0x17
#define CCRF_MCSM0                  0x18
#define CCRF_FOCCFG                 0x19
#define CCRF_BSCFG                  0x1A
#define CCRF_AGCCTRL2               0x1B
#define CCRF_AGCCTRL1               0x1C
#define CCRF_AGCCTRL0               0x1D
#define CCRF_WOREVT1                0x1E
#define CCRF_WOREVT0                0x1F
#define CCRF_WORCTRL                0x20
#define CCRF_FREND1                 0x21
#define CCRF_FREND0                 0x22
#define CCRF_FSCAL3                 0x23
#define CCRF_FSCAL2                 0x24
#define CCRF_FSCAL1                 0x25
#define CCRF_FSCAL0                 0x26
#define CCRF_RCCTRL1                0x27
#define CCRF_RCCTRL0                0x28
#define CCRF_FSTEST                 0x29
#define CCRF_PTEST                  0x2A
#define CCRF_AGCTEST                0x2B
#define CCRF_TEST2                  0x2C
#define CCRF_TEST1                  0x2D
#define CCRF_TEST0                  0x2E

// Strobe commands
#define CCRF_SRES                   0x30
#define CCRF_SFSTXON                0x31
#define CCRF_SXOFF                  0x32
#define CCRF_SCAL                   0x33
#define CCRF_SRX                    0x34
#define CCRF_STX                    0x35
#define CCRF_SIDLE                  0x36
#define CCRF_SAFC                   0x37
#define CCRF_SWOR                   0x38
#define CCRF_SPWD                   0x39
#define CCRF_SFRX                   0x3A
#define CCRF_SFTX                   0x3B
#define CCRF_SWORRST                0x3C
#define CCRF_SNOP                   0x3D

// Status registers
#define CCRF_PARTNUM                0x30
#define CCRF_VERSION                0x31
#define CCRF_FREQEST                0x32
#define CCRF_LQI                    0x33
#define CCRF_RSSI                   0x34
#define CCRF_MARCSTATE              0x35
#define CCRF_WORTIME1               0x36
#define CCRF_WORTIME0               0x37
#define CCRF_PKTSTATUS              0x38
#define CCRF_VCO_VC_DAC             0x39
#define CCRF_TXBYTES                0x3A
#define CCRF_RXBYTES                0x3B
#define CCRF_RCCTRL1_STATUS         0x3C
#define CCRF_RCCTRL0_STATUS         0x3D
#define CCRF_NUM_RXBYTES            0x7F

// Other memory locations
#define CCRF_PATABLE                0x3E
#define CCRF_TXFIFO                 0x3F
#define CCRF_RXFIFO                 0x3F

// Masks for appended status bytes
#define CCRF_LQI_RX                 0x01
#define CCRF_CRC_OK                 0x80

// Definitions to support burst/single access:
#define CCRF_WRITE_BURST            0x40
#define CCRF_READ_SINGLE            0x80
#define CCRF_READ_BURST             0xC0

#define CCRF_RECEIVE_CRC_ERROR      0x00
#define CCRF_RECEIVE_CRC_OK         0x80
#define CCRF_BURST_IN_RXFIFO        0x7F

#define CCRF_SINGLE_TXFIFO          0x3F
#define CCRF_BURST_TXFIFO           0x7F
#define CCRF_SINGLE_RXFIFO          0xBF
#define CCRF_BURST_RXFIFO           0xFF

#define CCRF_TX_MODE                0
#define CCRF_RX_MODE                1
#define CCRF_IDLE_MODE              2

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
    digital_out_t gd2;

    // Input pins 
    digital_in_t gd0;
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;

} ccrf_t;

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
    pin_name_t gd0;
    pin_name_t gd2;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ccrf_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void ccrf_cfg_setup ( ccrf_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t ccrf_init ( ccrf_t *ctx, ccrf_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for ccRF Click.
 */
void ccrf_default_cfg ( ccrf_t *ctx );

/**
 * @brief Get state of GD0 pin function
 *
 * @param ctx          Click object.
 *
 * @details Function for getting state of GD0 pin function
 */
uint8_t ccrf_get_start( ccrf_t *ctx );

/**
 * @brief Write the byte of data to the 8-bit register address function
 *
 * @param ctx                        Click object. 
 * @param reg_address                8-bit register address
 * @param write_data                 Byte of data to write
 *
 * @details Function writes the byte of data to the targeted 8-bit register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_write_byte ( ccrf_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Sequential write function
 *
 * @param ctx                        Click object.  
 * @param reg_address                8-bit register address
 * @param write_data                 pointer to the data to be written
 * @param n_bytes                    number of bytes to be written
 *
 * @details Function writes a sequential data starting to the targeted 8-bit register 
 * address of the CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_write_bytes ( ccrf_t *ctx, uint8_t reg_address, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Write a strobe command function
 *
 * @param ctx                        Click object.   
 * @param strobe                     8-bit strobe command
 *
 * @details Function writes a strobe command to the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_write_strobe ( ccrf_t *ctx, uint8_t strobe ); 

/**
 * @brief Read the byte of data from the 8-bit register address function
 *
 * @param ctx                        Click object.   
 * @param reg_address                8-bit register address
 *
 * @returns 8-bit read data
 *
 * @details Function reads the byte of data from the targeted 8-bit register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_read_byte ( ccrf_t *ctx, uint8_t reg_address );

/**
 * @brief Read the byte of data from the 8-bit status register address function
 *
 * @param ctx                        Click object.   
 * @param reg_address                8-bit status register address
 *
 * @returns 8-bit read data
 *
 * @details Function reads the byte of data from the targeted 8-bit status register address 
 * of the CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_read_byte_status ( ccrf_t *ctx, uint8_t reg_address );

/**
 * @brief Sequential read function
 *
 * @param ctx                        Click object.   
 * @param reg_address                8-bit register address
 * @param read_data                  pointer to the memory location where data be stored
 * @param n_bytes                    number of bytes to be read
 *
 * @details Function read a sequential data ( burst read ) starting from the targeted 8-bit 
 * register address of the CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_read_bytes( ccrf_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Softwere reset function
 *
 * @param ctx                        Click object.  
 * 
 * @details The function Softwere reset - resets the CC2500 Low-Power 2.4 GHz RF 
 * transceiver on the ccRF Click board by write CCRF_SRES, a strobe command.
 */
void ccrf_sw_reset ( ccrf_t *ctx );

/**
 * @brief Hardware reset function
 *
 * @param ctx                        Click object.  
 * 
 * @details The function Hardware reset - resets the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 *
 * @note Delay aprox. 3 ms.
 */
void ccrf_hw_reset ( ccrf_t *ctx );

/**
 * @brief Transmit packet data function
 *
 * @param ctx           Click object.   
 * @param tx_buffer     pointer to a buffer containing the data that are going to be transmitted
 * @param n_bytes       number of bytes that are going to be transmitted
 *
 * @details Function transmit a packet with packet length up to 63 bytes to the targeted
 * 8-bit register address of the CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 *
 * @note
 * <pre>
 *  To use this function, GD0 pin must be configured to be asserted when sync word is sent and
 *  de-asserted at the end of the packet.
 *  The function implements polling of GD0 pin. First it waits for GD0 to be set and then it waits
 *  for it to be cleared.
 * </pre>
 */
void ccrf_transmit_packet ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes );

/**
 * @brief Receive packet data function
 *
 * @param ctx           Click object.    
 * @param rx_buffer     Pointer to a buffer containing the data that are going to be received
 * @param length_buff   Pointer to a variable containing the data length that are going to be received
 *
 * @details Function receive a packet of variable packet length from the CC2500 Low-Power
 * 2.4 GHz RF transceiver on the ccRF Click board.
 *
 * @note
 * <pre> 
 *  To use this function, GD0 must be configured to be asserted when sync word is sent and
 *  de-asserted at the end of the packet.
 *  Also, CCRF_APPEND_STATUS in the CCRF_PKTCTRL1 register must be enabled.
 *  The function implements polling of GD0. First it waits for GD0 to be set and then it waits
 *  for it to be cleared.
 *  After the GD0 pin has been de-asserted, the CCRF_RXBYTES register is read to make sure that there
 *  are bytes in the FIFO. This is because the GDO signal will indicate sync received even if the
 *  FIFO is flushed due to address filtering, CRC filtering, or packet length filtering.
 * </pre> 
 */
uint8_t ccrf_receive_packet ( ccrf_t *ctx, uint8_t *rx_buffer, uint8_t *length_buff );

/**
 * @brief Transmit packet data with address function
 *
 * @param ctx           Click object.  
 * @param tx_buffer     Pointer to a buffer containing the data that are going to be transmitted
 * @param n_bytes       Number of bytes that are going to be transmitted
 * @param attempts      Pointer to a buffer containing the attempts data
 *
 * @details Function transmit a packet with packet length up to 63 bytes to the targeted 8-bit
 * register attempts address of the CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_transmit_packet_with_address ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes, uint8_t *attempts );

/**
 * @brief GD2 select active low function
 *
 * @param ctx           Click object. 
 *  
 * @details Function GD2 pin ( PWM ) select active low by set to '1' states of [ bit 6 ]
 * of the CCRF_IOCFG2 register address of the 
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_gd2_active_low ( ccrf_t *ctx );

/**
 * @brief GD2 select active high function
 *
 * @param ctx           Click object. 
 * 
 * @details Function GD2 pin ( PWM ) select active high by clearde to '0' states of [ bit 6 ]
 * of the CCRF_IOCFG2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_gd2_active_high ( ccrf_t *ctx );

/**
 * @brief GD0 select active low function
 *
 * @param ctx           Click object. 
 * 
 * @details Function GD0 pin ( PWM ) select active low by set to '1' states of [ bit 6 ]
 * of the CCRF_IOCFG0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_gd0_active_low ( ccrf_t *ctx );

/**
 * @brief GD0 select active high function
 *
 * @param ctx           Click object. 
 * 
 * @details Function GD0 pin ( PWM ) select active high by clearde to '0' states of [ bit 6 ]
 * of the CCRF_IOCFG0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_gd0_active_high ( ccrf_t *ctx );

/**
 * @brief Enable analog temperature sensor function
 *
 * @param ctx           Click object. 
 * 
 * @details Function enable analog temperature sensor by clearde to '0' states of [ bit 7 ]
 * of the CCRF_IOCFG0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 *
 * @note Write '0' in all other register bits when using temperature sensor.
 */
void ccrf_enable_temperature_sensor ( ccrf_t *ctx );

/**
 * @brief Disable analog temperature sensor function
 *
 * @param ctx           Click object. 
 *
 * @details Function enable analog temperature sensor by sets to '1' states of [ bit 7 ]
 * of the CCRF_IOCFG0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_disable_temperature_sensor ( ccrf_t *ctx );

/**
 * @brief Set the threshold for the TX FIFO and RX FIFO function
 *
 * @param ctx           Click object.  
 * @param threshold_rx_tx
 * <pre>
 *   number of bytes in the FIFO :
 *      -  0 : TX = 61, RX =  4;
 *      -  1 : TX = 57, RX =  8;
 *      -  2 : TX = 53, RX = 12;
 *      -  3 : TX = 49, RX = 16;
 *      -  4 : TX = 45, RX = 20;
 *      -  5 : TX = 41, RX = 24;
 *      -  6 : TX = 37, RX = 28;
 *      -  7 : TX = 33, RX = 32;
 *      -  8 : TX = 29, RX = 36;
 *      -  9 : TX = 25, RX = 40;
 *      - 10 : TX = 21, RX = 44;
 *      - 11 : TX = 17, RX = 48;
 *      - 12 : TX = 13, RX = 52;
 *      - 13 : TX =  9, RX = 56;
 *      - 14 : TX =  5, RX = 60;
 *      - 15 : TX =  1, RX = 64;
 * </pre>
 *
 * @details Function sets the threshold for the TX FIFO and RX FIFO to the
 * CCRF_FIFOTHR register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_fifo_threshold ( ccrf_t *ctx, uint8_t threshold_rx_tx );

/**
 * @brief Set maximum length packets allowed function
 *
 * @param ctx                       Click object.  
 * @param max_length                8-bit max length value
 *
 * @details Function sets the maximum length packets allowed
 * when fixed packet length is enabled by write maxLength to the
 * CCRF_FIFOTHR register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 *
 * @note
 * If variable length packets are used, this value indicates the maximum length packets allowed.
 */
void ccrf_set_max_length_packets ( ccrf_t *ctx, uint8_t max_length );

/**
 * @brief Turn data whitening on function
 *
 * @param ctx                       Click object.  
 *
 * @details Function turn data whitening ON by sets to '1' states of [ bit 6 ] of the
 * CCRF_PKTCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_turn_data_whitening_on ( ccrf_t *ctx );

/**
 * @brief Turn data whitening off function
 *
 * @param ctx                       Click object.  
 * 
 * @details Function turn data whitening ON by cleared to '0' states of [ bit 6 ] of the
 * CCRF_PKTCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_turn_data_whitening_off ( ccrf_t *ctx );

/**
 * @brief Set format of RX and TX data function
 *
 * @param ctx                       Click object.   
 * @param rx_tx_data_format :
 * <pre>
 *  - 0 : Normal mode, use FIFOs for RX and TX;
 *  - 1 : Synchronous serial mode, used for backwards
 *        compatibility. Data in on GD0 ( RST ) pin;
 *  - 2 : Random TX mode; sends random data. Used for test.
 *        Works as normal mode, setting in RX;
 *  - 3 : Asynchronous serial mode. Data in on GD0 ( RST ) and
 *        data out on either of the GD0 ( RST ) pin;
 * </pre> 
 *
 * @details Function sets the format of RX and TX data to the
 * CCRF_PKTCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_format_rx_tx_data ( ccrf_t *ctx, uint8_t rx_tx_data_format );

/**
 * @brief Set device address function
 *
 * @param ctx                       Click object.    
 * @param dev_addr                  8-bit address used for packet filtration
 *
 * @details Function sets the device address ( optional broadcast addresses are 0 (0x00) 
 * and 255 (0xFF) ) to the CCRF_ADDR register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_device_address ( ccrf_t *ctx, uint8_t dev_addr );

/**
 * @brief Set channel number function
 *
 * @param ctx                       Click object.  
 * @param ch_num                    8-bit channel number
 *
 * @details Function sets the channel number which is multiplied by the
 * channel spacing setting and added to the base frequency
 * to the CCRF_CHANNR register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_channel_number ( ccrf_t *ctx, uint8_t ch_num );

/**
 * @brief Set desired IF frequency function
 *
 * @param ctx                       Click object.  
 * @param if_freq                   8-bit desired IF frequency to employ in RX
 *
 * @details Function sets the desired IF frequency by vrite ifFreq value
 * to the CCRF_FSCTRL1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_if_frequency ( ccrf_t *ctx, uint8_t if_freq );

/**
 * @brief Set frequency offset function
 *
 * @param ctx                       Click object.   
 * @param freq_offset               8-bit frequency before being used by the FS
 *
 * @details Function sets the frequency offset by vrite freqOffset value
 * to the CCRF_FSCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_frequency_offset ( ccrf_t *ctx, uint8_t freq_offset );

/**
 * @brief Disable digital DC blocking filter function
 *
 * @param ctx                       Click object. 
 * 
 * @details Function disable digital DC blocking filter by sets to '1' states of [ bit 7 ]
 * of the CCRF_MDMCFG2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 *
 * @note Only for data rates < 250 kBaud
 */
void ccrf_disable_dc_blocking_filter ( ccrf_t *ctx );

/**
 * @brief Enable digital DC blocking filter function
 *
 * @param ctx                       Click object. 
 * 
 * @details Function enable ( better sensitivity ) digital DC blocking filter
 * by cleared to '0' states of [ bit 7 ] of the CCRF_MDMCFG2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_enable_dc_blocking_filter ( ccrf_t *ctx );

/**
 * @brief Set the modulation format of the radio signal function
 *
 * @param ctx                       Click object.  
 * @param rf_modulation
 * <pre>
 * Modulation format of the radio signal :
 * - 0 : 2-FSK;
 * - 1 : GFSK;
 * - 2 : OOK;
 * - 3 : MSK;
 * </pre>
 *
 * @details Function sets the modulation format of the radio signal by vrite rfModulation value
 * to the CCRF_FSCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_modulation ( ccrf_t *ctx, uint8_t rf_modulation );

/**
 * @brief Enable Manchester encoding function
 *
 * @param ctx                       Click object. 
 * 
 * @details Function enable Manchester encoding by sets to '1' states of [ bit 3 ]
 * of the CCRF_MDMCFG2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_enable_manchester_encoding ( ccrf_t *ctx );

/**
 * @brief Disable Manchester encoding function
 *
 * @param ctx                       Click object. 
 * 
 * @details Function disable Manchester encoding by cleared to '0' states of [ bit 3 ]
 * of the CCRF_MDMCFG2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_disable_manchester_encoding ( ccrf_t *ctx );

/**
 * @brief Set sync-word qualifier mode function
 *
 * @param ctx                       Click object.  
 * @param q_mode
 * <pre>
 * Sync-word qualifier mode :
 * - 0 : No preamble/sync;
 * - 1 : 15/16 sync word bits detected;
 * - 2 : 16/16 sync word bits detected;
 * - 3 : 30/32 sync word bits detected;
 * - 4 : No preamble/sync, carrier-sense above threshold;
 * - 5 : 15/16 + carrier-sense above threshold;
 * - 6 : 16/16 + carrier-sense above threshold;
 * - 7 : 30/32 + carrier-sense above threshold;
 * </pre>
 *
 * @details Function sets the sync-word qualifier mode by vrite qMode value
 * to the CCRF_MDMCFG2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_sync_word_qualifier_mode ( ccrf_t *ctx, uint8_t q_mode );

/**
 * @brief Disable forward error correction function
 *
 * @param ctx                       Click object.
 * 
 * @details Function disable the forward error correction by cleared to '0' states of 
 * [ bit 7 ] of the CCRF_MDMCFG1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_disable_fec ( ccrf_t *ctx );

/**
 * @brief Enable forward error correction function
 *
 * @param ctx                       Click object.
 * 
 * @details Function enable the forward error correction by sets to '1' states of [ bit 7 ]
 * of the CCRF_MDMCFG1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_enable_fec ( ccrf_t *ctx );

/**
 * @brief Set the minimum number of preamble bytes to be transmitted function
 *
 * @param ctx                       Click object. 
 * @param p_num
 * <pre>
 * Number of preamble bytes :
 *    - 0 : 2;
 *    - 1 : 3;
 *    - 2 : 4;
 *    - 3 : 6;
 *    - 4 : 6;
 *    - 5 : 12;
 *    - 6 : 16;
 *    - 7 : 24;
 * </pre>
 *
 * @details Function sets the the minimum number of preamble bytes to be transmitted by 
 * vrite p_num value to the CCRF_MDMCFG1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_min_num_preamble ( ccrf_t *ctx, uint8_t p_num );

/**
 * @brief Set CCA mode function
 *
 * @param ctx                       Click object.  
 * @param cca_mode
 * <pre> 
 * Clear channel indication :
 *    - 0 : Always;
 *    - 1 : If RSSI below threshold;
 *    - 2 : Unless currently receiving a packet;
 *    - 3 : If RSSI below threshold unless currently receiving a packet;
 * </pre>
 *
 * @details Function sets the clear channel indication by vrite ccaMode value
 * to the CCRF_MDMCFG1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_cca_mode ( ccrf_t *ctx, uint8_t cca_mode );


/**
 * @brief Set state after finishing packet reception function
 *
 * @param ctx                       Click object.  
 * @param pr_state
 * <pre>
 * Next state after finishing packet reception :
 *      - 0 : IDLE;
 *      - 1 : FSTXON;
 *      - 2 : TX;
 *      - 3 : Stay in RX;
 * </pre>
 *
 * @details Function sets the state after finishing packet reception by vrite prState value
 * to the CCRF_MDMCFG1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_state_packet_recived ( ccrf_t *ctx, uint8_t pr_state );

/**
 * @brief Set state when a packet has been sent function
 *
 * @param ctx                       Click object.  
 * @param ps_state
 * <pre> 
 * Next state after finishing packet transmission :
 *      - 0 : IDLE;
 *      - 1 : FSTXON;
 *      - 2 : Stay in TX (start sending preamble);
 *      - 3 : RX;
 * </pre> 
 *
 * @details Function sets the state when a packet has been sent by vrite ps_state value
 * to the CCRF_MDMCFG1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_state_packet_sent ( ccrf_t *ctx, uint8_t ps_state );

/**
 * @brief Set automatically calibrate function
 *
 * @param ctx                       Click object.   
 * @param ac_mode
 * <pre> 
 * When to perform automatic calibration :
 *      - 0 : Never (manually calibrate using SCAL strobe);
 *      - 1 : When going from IDLE to RX or TX (or FSTXON);
 *      - 2 : When going from RX or TX back to IDLE automatically;
 *      - 3 : Every 4th time when going from RX or TX to IDLE automatically;
 * </pre>
 *
 * @details Function sets the automatically calibrate by vrite ac_mode value
 * to the CCRF_MCSM0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_auto_calibrate_mode ( ccrf_t *ctx, uint8_t ac_mode );

/**
 * @brief Set frequency compensation loop gain before a sync function
 *
 * @param ctx                       Click object.   
 * @param fcl_gain
 * <pre> 
 * Freq. compensation loop gain before sync word :
 * - 0 : 1K;
 * - 1 : 2K;
 * - 2 : 3K;
 * - 3 : 4K;
 * </pre> 
 *
 * @details Function sets the frequency compensation loop gain before a sync by vrite 
 * fcl_gain value to the CCRF_FOCCFG register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_freq_loop_gain_bs ( ccrf_t *ctx, uint8_t fcl_gain );

/**
 * @brief Set frequency compensation loop gain after a sync function
 *
 * @param ctx                       Click object.   
 * @param fcl_gain
 * <pre>  
 * Freq. compensation loop gain after sync word :
 * - 0 : Same as FOC_PRE_K;
 * - 1 : K/2;
 * </pre>  
 *
 * @details Function sets the frequency compensation loop gain after a sync by vrite fcl_gain value
 * to the CCRF_FOCCFG register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_freq_loop_gain_as ( ccrf_t *ctx, uint8_t fcl_gain );

/**
 * @brief Set bit synchronization configuration function
 *
 * @param ctx                       Click object.   
 * @param bsConfig
 * <pre>  
 * Freq. compensation loop gain before sync word :
 *  - [ bit 7:6 ] : Clock recovery loop integral gain before sync word:
 *       - 0 : 1Ki;
 *       - 1 : 2Ki;
 *       - 2 : 3Ki;
 *       - 3 : 4Ki;
 *  - [ bit 5:4 ] : Clock recovery loop proportional gain before sync word:
 *       - 0 : 1Kp;
 *       - 1 : 2Kp;
 *       - 2 : 3Kp;
 *       - 3 : 4Kp;
 *  - [ bit 3 ]   : Clock recovery loop integral gain after sync word:
 *       - 0 : Same as BS_PRE_KI;
 *       - 1 : Ki/2;
 *  - [ bit 2 ]   : Clock recovery loop proportional gain after sync word:
 *       - 0 : Same as BS_PRE_KP;
 *       - 1 : Kp;
 *  - [ bit 1:0 ] : Data rate offset saturation (max data rate difference):
 *       - 0 : �0 (No data rate offset compensation performed);
 *       - 1 : �3.125% data rate offset;
 *       - 2 : �6.25% data rate offset;
 *       - 3 : �12.5% data rate offset;
 * </pre>  
 *
 * @details Function sets the bit synchronization configuration by vrite bsConfig value
 * to the CCRF_BSCFG register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_bit_sync_config ( ccrf_t *ctx, uint8_t bs_config );

/**
 * @brief Set the maximum allowable DVGA gain function
 *
 * @param ctx                       Click object.    
 * @param dvga_gain
 * <pre>
 * Allowable DVGA settings :
 *      - 0 : All gain settings can be used;
 *      - 1 : The highest gain setting can not be used;
 *      - 2 : The 2 highest gain settings can not be used;
 *      - 3 : The 3 highest gain settings can not be used;
 * </pre>
 *
 * @details Function sets the maximum allowable DVGA gain by vrite dvgaGain value
 * to the CCRF_MCSM0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_dvga_gain ( ccrf_t *ctx, uint8_t dvga_gain );

/**
 * @brief Set the maximum allowable LNA gain function
 *
 * @param ctx                       Click object.    
 * @param lna_gain
 * <pre> 
 * Maximum allowable LNA + LNA 2 gain :
 *      - 0 : Maximum possible LNA + LNA 2 gain;
 *      - 1 : Approx. 2.6 dB below maximum possible gain;
 *      - 2 : Approx. 6.1 dB below maximum possible gain;
 *      - 3 : Approx. 7.4 dB below maximum possible gain;
 *      - 4 : Approx. 9.2 dB below maximum possible gain;
 *      - 5 : Approx. 11.5 dB below maximum possible gain;
 *      - 6 : Approx. 14.6 dB below maximum possible gain;
 *      - 7 : Approx. 17.1 dB below maximum possible gain;
 * </pre>
 *
 * @details Function sets the maximum allowable LNA + LNA 2 gain by vrite lnaGain value
 * to the CCRF_AGCCTRL2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_lna_gain ( ccrf_t *ctx, uint8_t lna_gain );

/**
 * @brief Set the target amplitude from channel filter function
 *
 * @param ctx                       Click object.    
 * @param ach_filter
 * <pre> 
 * Maximum allowable LNA + LNA 2 gain :
 *      - 0 : 24 dB;
 *      - 1 : 27 dB;
 *      - 2 : 30 dB;
 *      - 3 : 33 dB;
 *      - 4 : 36 dB;
 *      - 5 : 38 dB;
 *      - 6 : 40 dB;
 *      - 7 : 42 dB;
 * </pre>  
 *
 * @details Function sets the target amplitude from channel filter by vrite ach_filter value
 * to the CCRF_AGCCTRL2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_amplitude_ch_filter ( ccrf_t *ctx, uint8_t ach_filter );

/**
 * @brief Set the LNA strategies function
 *
 * @param ctx                       Click object.    
 * @param lna_strat
 * <pre>  
 *      - 0 : LNA2 gain is decreased to minimum beforedecreasing LNA gain;
 *      - 1 : LNA gain is decreased first.;
 * </pre> 
 *
 * @details Function sets the tLNA strategies by vrite lna_strat value
 * to the CCRF_AGCCTRL1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_lna_strategies ( ccrf_t *ctx, uint8_t lna_strat );

/**
 * @brief Set the relative change threshold for asserting carrier sense function
 *
 * @param ctx                       Click object.    
 * @param rssi_threshold
 * <pre>  
 * Carrier sense relative threshold :
 *      - 0 : Relative carrier sense threshold disabled;
 *      - 1 : 6 dB increase in RSSI value;
 *      - 2 : 10 dB increase in RSSI value;
 *      - 3 : 14 dB increase in RSSI value;
 * </pre>  
 *
 * @details Function sets the relative change threshold for asserting carrier sense by vrite 
 * rssi_threshold value to the CCRF_AGCCTRL1 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_relative_rssi_threshold ( ccrf_t *ctx, uint8_t rssi_threshold );

/**
 * @brief Set the rabsolute RSSI threshold for asserting carrier sense function
 *
 * @param ctx                       Click object.    
 * @param rssi_threshold
 * <pre>   
 * Carrier sense absolute threshold :
 *      - -8 : Absolute carrier sense threshold disabled;
 *      - -7 : 7 dB below MAGN_TARGET setting;
 *      - -6 : 6 dB below MAGN_TARGET setting;
 *      - -5 : 5 dB below MAGN_TARGET setting;
 *      - -4 : 4 dB below MAGN_TARGET setting;
 *      - -3 : 3 dB below MAGN_TARGET setting;
 *      - -2 : 2 dB below MAGN_TARGET setting;
 *      - -1 : 1 dB below MAGN_TARGET setting;
 *      -  0 : At MAGN_TARGET setting;
 *      -  1 : 1 dB above MAGN_TARGET setting;
 *      -  2 : 2 dB above MAGN_TARGET setting;
 *      -  3 : 3 dB above MAGN_TARGET setting;
 *      -  4 : 4 dB above MAGN_TARGET setting;
 *      -  5 : 5 dB above MAGN_TARGET setting;
 *      -  6 : 6 dB above MAGN_TARGET setting;
 *      -  7 : 7 dB above MAGN_TARGET setting;
 * </pre>  
 *
 * @details Function sets the rabsolute RSSI threshold for asserting carrier sense by vrite rssi_threshold value
 * to the CCRF_AGCCTRL2 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_absolute_rssi_threshold ( ccrf_t *ctx, uint8_t rssi_threshold );

/**
 * @brief Set the level of hysteresis on the magnitude deviation function
 *
 * @param ctx                       Click object. 
 * @param hyst_lvl
 * <pre>   
 * Hysteresis on the magnitude deviation :
 *      - 0 : No hysteresis, small symmetric dead zone, high gain;
 *      - 1 : Low hysteresis, small asymmetric dead zone, medium gain;
 *      - 2 : Medium hysteresis, medium asymmetric dead zone, medium gain;
 *      - 3 : Large hysteresis, large asymmetric dead zone, low gain;
 * </pre>  
 *
 * @details Function sets the level of hysteresis on the magnitude deviation by vrite 
 * hyst_lvl value to the CCRF_AGCCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_hysteresis_lvl ( ccrf_t *ctx, uint8_t hyst_lvl );

/**
 * @brief Set the number of channel filter samples function
 *
 * @param ctx                       Click object.  
 * @param num_ch_filter
 * <pre>  
 * Channel filter samples :
 * - 0 :  8;
 * - 1 : 16;
 * - 2 : 24;
 * - 3 : 32;
 * </pre>   
 *
 * @details Function sets the number of channel filter samples by vrite numChFilter value
 * to the CCRF_AGCCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_num_ch_filter ( ccrf_t *ctx, uint8_t num_ch_filter );

/**
 * @brief Set the AGC gain function
 *
 * @param ctx                       Click object.  
 * @param agc_gain
 * <pre>   
 * - 0 : Normal operation. Always adjust gain when required;
 * - 1 : The gain setting is frozen when a sync word has been found;
 * - 2 : Manually freezes the analog gain setting and continue to adjust the digital gain;
 * - 3 : Manually freezes both the analog and the digital gain settings. Used for manually overriding the gain;
 * </pre>  
 *
 * @details Function sets the AGC gain by vrite agc_gain value
 * to the CCRF_AGCCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_agc_gain ( ccrf_t *ctx, uint8_t agc_gain );

/**
 * @brief Set the averaging length for the amplitude from the channel filter function
 *
 * @param ctx                       Click object.  
 * @param al_amp
 * <pre>   
 * Channel filter samples | OOK decision :
 * - 0 :  8 |  4 dB;
 * - 1 : 16 |  8 dB;
 * - 2 : 32 | 12 dB;
 * - 3 : 64 | 16 dB;
 * </pre>   
 *
 * @details Function sets the averaging length for the amplitude from the channel filter 
 * by vrite numChFilter value to the CCRF_AGCCTRL0 register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_avr_len_ampitude ( ccrf_t *ctx, uint8_t al_amp );

/**
 * @brief Set automatic initial calibration function
 *
 * @param ctx                       Click object.  
 * 
 * @details Function sets the automatic initial calibration by cleared to '0' states of 
 * [ bit 7 ] of the CCRF_WORCTRL register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_auto_initial_calibration ( ccrf_t *ctx );

/**
 * @brief Set the averaging length for the amplitude from the channel filter function
 *
 * @param ctx                       Click object.  
 * @param timeout
 * <pre>
 * t_event1 :
 *      - 0 :  4 ( 0.111 � 0.115 ms );
 *      - 1 :  6 ( 0.167 � 0.173 ms );
 *      - 2 :  8 ( 0.222 � 0.230 ms );
 *      - 3 : 12 ( 0.333 � 0.346 ms );
 *      - 4 : 16 ( 0.444 � 0.462 ms );
 *      - 5 : 24 ( 0.667 � 0.692 ms );
 *      - 6 : 32 ( 0.889 � 0.923 ms );
 *      - 7 : 48 ( 1.333 � 1.385 ms );
 * </pre>
 *
 * @details Function sets the averaging length for the amplitude from the channel filter 
 * by vrite timeout value to the CCRF_WORCTRL register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_timeout_reg_block ( ccrf_t *ctx, uint8_t timeout );

/**
 * @brief Disables the RC oscillator calibration function
 *
 * @param ctx                       Click object. 
 * 
 * @details Function disables the RC oscillator calibration by cleared to '0' states of 
 * [ bit 3 ] of the CCRF_WORCTRL register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_disable_osc_rc ( ccrf_t *ctx );

/**
 * @brief Enable the RC oscillator calibration function
 *
 * @param ctx                       Click object. 
 * 
 * @details Function enable the RC oscillator calibration by sets to '1' states of [ bit 3 ]
 * of the CCRF_WORCTRL register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_enable_osc_rc ( ccrf_t *ctx );

/**
 * @brief Set the maximum timeout of the WOR module function
 *
 * @param ctx                       Click object.  
 * @param timeout
 * <pre>
 * Resolution  | Max timeout :
 *      - 0 : 1    period  ( 28    � 29    �s ) |   1.8 �  1.9 seconds;
 *      - 1 : 2^5  periods (  0.89 �  0.92 ms ) |  58   � 61   seconds;
 *      - 2 : 2^10 periods ( 28    � 30    ms ) |  31   � 32    minutes;
 *      - 3 : 2^15 periods (  0.91 �  0.94 s)   |  16.5 � 17.2  hours;
 * </pre> 
 *
 * @details Function sets the maximum timeout of the WOR module by vrite timeout value
 * to the CCRF_WORCTRL register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
void ccrf_set_timeout_wor ( ccrf_t *ctx, uint8_t timeout );

/**
 * @brief Get chip part number function
 *
 * @param ctx                       Click object.   
 * @returns 8-bit chip part number value
 *
 * @details Function get chip part number by read chip part number value
 * from the CCRF_PARTNUM register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_chip_part_number ( ccrf_t *ctx );

/**
 * @brief Get chip version number function
 *
 * @param ctx                       Click object.   
 * @returns 8-bit chip version number value
 *
 * @details Function get chip version number by read chip version number value
 * from the CCRF_VERSION register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_chip_version_number ( ccrf_t *ctx );

/**
 * @brief Get received signal strength indication function
 *
 * @param ctx                       Click object.    
 * @returns 8-bit RSSI value
 *
 * @details Function get creceived signal strength indication by RSSI value
 * from the CCRF_RSSI register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_rssi ( ccrf_t *ctx );

/**
 * @brief Get main radio control state machine state function
 *
 * @param ctx                       Click object.   
 *
 * @returns
 * <pre>
 * Main Radio Control FSM State
 * - [ bit 7:5 ] : Reserved;
 * - [ bit 4:0 ] :      State name       | State :
 *      -  0 ( 0x00 ) : SLEEP            | SLEEP;
 *      -  1 ( 0x01 ) : IDLE             | IDLE;
 *      -  2 ( 0x02 ) : XOFF             | XOFF;
 *      -  3 ( 0x03 ) : VCOON_MC         | MANCAL;
 *      -  4 ( 0x04 ) : REGON_MC         | MANCAL;
 *      -  5 ( 0x05 ) : MANCAL           | MANCAL;
 *      -  6 ( 0x06 ) : VCOON            | FS_WAKEUP;
 *      -  7 ( 0x07 ) : REGON            | FS_WAKEUP;
 *      -  8 ( 0x08 ) : STARTCAL         | CALIBRATE;
 *      -  9 ( 0x09 ) : BWBOOST          | SETTLING;
 *      - 10 ( 0x0A ) : FS_LOCK          | SETTLING;
 *      - 11 ( 0x0B ) : IFADCON          | SETTLING;
 *      - 12 ( 0x0C ) : ENDCAL           | CALIBRATE;
 *      - 13 ( 0x0D ) : RX               | RX;
 *      - 14 ( 0x0E ) : RX_END           | RX;
 *      - 15 ( 0x0F ) : RX_RST           | RX;
 *      - 16 ( 0x10 ) : TXRX_SWITCH      | TXRX_SETTLING3Kp;
 *      - 17 ( 0x11 ) : RXFIFO_OVERFLOW  | RXFIFO_OVERFLOW;
 *      - 18 ( 0x12 ) : FSTXON           | FSTXON;
 *      - 19 ( 0x13 ) : TX               | TX;
 *      - 20 ( 0x14 ) : TX_END           | TX;
 *      - 21 ( 0x15 ) : RXTX_SWITCH      | RXTX_SETTLING;
 *      - 22 ( 0x16 ) : TXFIFO_UNDERFLOW | TXFIFO_UNDERFLOW;
 * </pre> 
 *
 * @details Function get main radio control state machine state by RSSI status value
 * from the CCRF_MARCSTATE register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_mrc_state ( ccrf_t *ctx );

/**
 * @brief Get current GDO status and packet status function
 *
 * @param ctx                       Click object.
 * 
 * @returns
 * <pre>
 * Freq. compensation loop gain before sync word :
 * - [ bit 7 ] : The last CRC comparison matched. Cleared when entering/restarting RX mode;
 * - [ bit 6 ] : Carrier sense;
 * - [ bit 5 ] : Preamble Quality reached;
 * - [ bit 4 ] : Channel is clear;
 * - [ bit 3 ] : Sync word found;
 * - [ bit 2 ] : Current GDO2 value;
 * - [ bit 1 ] : Reserved;
 * - [ bit 0 ] : Current GDO0 value;
 * </pre>
 *
 * @details Function get current GDO status and packet status by read status value
 * from the CCRF_PKTSTATUS register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_gd0_and_packet_state ( ccrf_t *ctx );

/**
 * @brief Get underflow RX FIFO status function
 *
 * @param ctx                       Click object.
 * 
 * @returns 0 - ok; 1 - underflow;
 *
 * @details Function get underflow RX FIFO status by read status of underflow
 * from the CCRF_RXBYTES register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_underflow_rx_fifo ( ccrf_t *ctx );

/**
 * @brief Get number of bytes in RX FIFO function
 *
 * @param ctx                       Click object.
 * 
 * @returns number of bytes in RX FIFO ( max. 128 )
 *
 * @details Function get underflow RX FIFO status by read value number of bytes in RX FIFO
 * from the CCRF_RXBYTES register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_rx_fifo_num_bytes ( ccrf_t *ctx );

/**
 * @brief Get RC oscillator calibration result function
 *
 * @param ctx                       Click object.
 *
 * @returns RC oscillator calibration result ( max. 128 )
 *
 * @details Function get RC oscillator calibration result by read RC osc. result
 * from the CCRF_RCCTRL1_STATUS register address of the
 * CC2500 Low-Power 2.4 GHz RF transceiver on the ccRF Click board.
 */
uint8_t ccrf_get_rc_osc_cal_result ( ccrf_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // CCRF_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for BEE Click driver.
 *
 * \addtogroup bee BEE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BEE_H
#define BEE_H

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

#define BEE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.wa = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BEE_RETVAL  uint8_t

#define BEE_OK           0x00
#define BEE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup short_registers_address    Short Registers Address
 * \{
 */
#define BEE_RXMCR                                                         0x00
#define BEE_PANIDL                                                        0x01
#define BEE_PANIDH                                                        0x02
#define BEE_SADRL                                                         0x03
#define BEE_SADRH                                                         0x04
#define BEE_EADR0                                                         0x05
#define BEE_EADR1                                                         0x06
#define BEE_EADR2                                                         0x07
#define BEE_EADR3                                                         0x08
#define BEE_EADR4                                                         0x09
#define BEE_EADR5                                                         0x0A
#define BEE_EADR6                                                         0x0B
#define BEE_EADR7                                                         0x0C
#define BEE_RXFLUSH                                                       0x0D
#define BEE_ORDER                                                         0x10
#define BEE_TXMCR                                                         0x11
#define BEE_ACKTMOUT                                                      0x12
#define BEE_ESLOTG1                                                       0x13
#define BEE_SYMTICKL                                                      0x14
#define BEE_SYMTICKH                                                      0x15
#define BEE_PACON0                                                        0x16
#define BEE_PACON1                                                        0x17
#define BEE_PACON2                                                        0x18
#define BEE_TXBCON0                                                       0x1A
#define BEE_TXNCON                                                        0x1B
#define BEE_TXG1CON                                                       0x1C
#define BEE_TXG2CON                                                       0x1D
#define BEE_ESLOTG23                                                      0x1E
#define BEE_ESLOTG45                                                      0x1F
#define BEE_ESLOTG67                                                      0x20
#define BEE_TXPEND                                                        0x21
#define BEE_WAKECON                                                       0x22
#define BEE_FRMOFFSET                                                     0x23
#define BEE_TXSTAT                                                        0x24
#define BEE_TXBCON1                                                       0x25
#define BEE_GATECLK                                                       0x26
#define BEE_TXTIME                                                        0x27
#define BEE_HSYMTMRL                                                      0x28
#define BEE_HSYMTMRH                                                      0x29
#define BEE_SOFTRST                                                       0x2A
#define BEE_SECCON0                                                       0x2C
#define BEE_SECCON1                                                       0x2D
#define BEE_TXSTBL                                                        0x2E
#define BEE_RXSR                                                          0x30
#define BEE_INTSTAT                                                       0x31
#define BEE_INTCON_M                                                      0x32
#define BEE_GPIO                                                          0x33
#define BEE_TRISGPIO                                                      0x34
#define BEE_SLPACK                                                        0x35
#define BEE_RFCTL                                                         0x36
#define BEE_SECCR2                                                        0x37
#define BEE_BBREG0                                                        0x38
#define BEE_BBREG1                                                        0x39
#define BEE_BBREG2                                                        0x3A
#define BEE_BBREG3                                                        0x3B
#define BEE_BBREG4                                                        0x3C
#define BEE_BBREG6                                                        0x3E
#define BEE_CCAEDTH                                                       0x3F
/** \} */

/**
 * \defgroup long_registers_address    Long Registers Address
 * \{
 */
#define BEE_RFCON0                                                       0x0200
#define BEE_RFCON1                                                       0x0201
#define BEE_RFCON2                                                       0x0202
#define BEE_RFCON3                                                       0x0203
#define BEE_RFCON5                                                       0x0205
#define BEE_RFCON6                                                       0x0206
#define BEE_RFCON7                                                       0x0207
#define BEE_RFCON8                                                       0x0208
#define BEE_SLPCAL0                                                      0x0209
#define BEE_SLPCAL1                                                      0x020A
#define BEE_SLPCAL2                                                      0x020B
#define BEE_RFSTATE                                                      0x020F
#define BEE_RSSI                                                         0x0210
#define BEE_SLPCON0                                                      0x0211
#define BEE_SLPCON1                                                      0x0220
#define BEE_WAKETIMEL                                                    0x0222
#define BEE_WAKETIMEH                                                    0x0223
#define BEE_REMCNTL                                                      0x0224
#define BEE_REMCNTH                                                      0x0225
#define BEE_MAINCNT0                                                     0x0226
#define BEE_MAINCNT1                                                     0x0227
#define BEE_MAINCNT2                                                     0x0228
#define BEE_MAINCNT3                                                     0x0229
#define BEE_ASSOEADR0                                                    0x0230
#define BEE_ASSOEADR1                                                    0x0231
#define BEE_ASSOEADR2                                                    0x0232
#define BEE_ASSOEADR3                                                    0x0233
#define BEE_ASSOEADR4                                                    0x0234
#define BEE_ASSOEADR5                                                    0x0235
#define BEE_ASSOEADR6                                                    0x0236
#define BEE_ASSOEADR7                                                    0x0237
#define BEE_ASSOSADR0                                                    0x0238
#define BEE_ASSOSADR1                                                    0x0239
#define BEE_UPNONCE0                                                     0x0240
#define BEE_UPNONCE1                                                     0x0241
#define BEE_UPNONCE2                                                     0x0242
#define BEE_UPNONCE3                                                     0x0243
#define BEE_UPNONCE4                                                     0x0244
#define BEE_UPNONCE5                                                     0x0245
#define BEE_UPNONCE6                                                     0x0246
#define BEE_UPNONCE7                                                     0x0247
#define BEE_UPNONCE8                                                     0x0248
#define BEE_UPNONCE9                                                     0x0249
#define BEE_UPNONCE10                                                    0x024A
#define BEE_UPNONCE11                                                    0x024B
#define BEE_UPNONCE12                                                    0x024C
#define BEE_RX_FIFO                                                              0x0300
#define BEE_DATA_LENGHT                                                          1
#define BEE_HEADER_LENGHT                                                        11
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
    digital_out_t wa;
    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} bee_t;

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

    pin_name_t wa;
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} bee_cfg_t;

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
void bee_cfg_setup ( bee_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BEE_RETVAL bee_init ( bee_t *ctx, bee_cfg_t *cfg );

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
void bee_generic_transfer ( bee_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Write the byte of data to the short register address function
 *
 * @param ctx                        Click object.
 * @param reg_address                8-bit register address
 * @param write_data                 Byte of data to write
 *
 * @description The function writes the byte of data to the
 * targeted short 8-bit register address of
 * MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_write_byte_short ( bee_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Read the byte of data from the short register address function
 *
 * @param ctx                        Click object.
 * @param reg_address                8-bit register address
 *
 * @description The function write the 8-bit of data to the
 * targeted short 8-bit register address of
 * MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
uint8_t bee_read_byte_short ( bee_t *ctx, uint8_t reg_address );

/**
 * @brief Write the byte of data to the long register address function
 *
 * @param reg_address                16-bit register address
 * @param write_data                 Byte of data to write
 *
 * @description The function writes the byte of data to the
 * targeted long 16-bit register address of
 * MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_write_byte_long ( bee_t *ctx, uint16_t reg_address, uint8_t write_data );

/**
 * @brief Read the byte of data from the long register address function
 *
 * @param reg_address                16-bit register address
 *
 * @description The function write the 8-bit of data to the
 * targeted long 16-bit register address of
 * MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
uint8_t bee_read_byte_long ( bee_t *ctx, uint16_t reg_address );

/**
 * @brief Hardware reset function
 *
 * 
 * @param ctx                        Click object.
 * 
 * @description The function Hardware reset - resets the MRF24J40MA 2.4GHz transceiver module
 * by cleared to '0' RST state pin, wait 5 ms and set to '1' RST state pin
 * on BEE Click board.
 *
 * @note
 * Delay is 10 ms.
 */
void bee_hw_reset ( bee_t *ctx );

/**
 * @brief Power reset function
 *
 * @param ctx                        Click object.
 * 
 * @description The function Power reset - reset power management circuitry
 * by sets to '1' [ bit 2 ] states of _BEE_SOFTRST register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * bit is automatically cleared to '0' by hardware
 */
void bee_power_reset ( bee_t *ctx );

/**
 * @brief Baseband reset function
 *
 * @param ctx                        Click object.
 * 
 * @description The function Baseband reset - reset baseband circuitry
 * by sets to '1' [ bit 1 ] states of _BEE_SOFTRST register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * bit is automatically cleared to '0' by hardware
 */
void bee_bb_reset ( bee_t *ctx );

/**
 * @brief MAC reset function
 * 
 * @param ctx                        Click object.
 * 
 * @description The function MAC reset - reset MAC circuitry
 * by sets to '1' [ bit 0 ] states of _BEE_SOFTRST register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * bit is automatically cleared to '0' by hardware
 */
void bee_mac_reset ( bee_t *ctx );

/**
 * @brief Soft reset function
 * 
 * @param ctx                        Click object.
 * 
 * @description The function soft reset - reset power, baseband and MAC circuitry
 * by sets to '1' [ bit 3 : bit 0 ] states of _BEE_SOFTRST register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * bits is automatically cleared to '0' by hardware
 */
void bee_soft_reset ( bee_t *ctx );

/**
 * @brief RF state machine reset function
 *
 * @param ctx                        Click object.
 * 
 * @description The function RF state machine reset activate normal operation of RF state machine
 * by clear to '0' [ bit 2 ] states of _BEE_RFCTL register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * Delay is 1 ms.
 */
void bee_rf_reset ( bee_t *ctx );

/**
 * @brief Enable interrupt function
 *
 * @param ctx                        Click object.
 * 
 * @description The function enable all interrupts:
 * - sleep alert interrupt,
 * - wake-up alert interrupt,
 * - half symbol timer interrupt,
 * - security key request interrupt,
 * - RX FIFO reception interrupt,
 * - TX GTS2 FIFO transmission interrupt,
 * - TX GTS1 FIFO transmission interrupt,
 * - TX Normal FIFO transmission interrupt
 * by clear to '0' [ bit 7 : bit 0 ] states of _BEE_INTCON_M register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_enable_interrupt ( bee_t *ctx );

/**
 * @brief Set channel function
 *
 * @param ctx                        Click object.
 * @param n_nhannel
 * - 0x0B : Channel 11 (2405 MHz) (default);
 * - 0x0C : Channel 12 (2410 MHz);
 * - 0x0D : Channel 13 (2415 MHz);
 * - 0x1A : Channel 26 (2480 MHz);
 *
 * @description The function set channel by write number of channel value
 * to the _BEE_RFCON0 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_channel ( bee_t *ctx, uint8_t n_channel );

/**
 * @brief Set CCA mode function
 *
 * @param ctx                        Click object.
 * @param cca_mode:
 * - 0x01 : CCA Mode 1, Energy above threshold.
 * CCA shall report a busy medium upon detecting any
 * energy above the Energy Detection (ED) threshold.
 * - 0x02 : CCA Mode 2, Carrier sense only.
 * CCA shall report a busy medium only upon the detection of a
 * signal with the modulation and spreading characteristics of IEEE 802.15.4. 
 * This signal may be above or below the Energy Detection (ED) threshold (default).
 * - 0x03 : CCA Mode 3, Carrier sense with energy above threshold.
 * CCA shall report a busy medium only
 * upon the detection of a signal with the modulation and spreading characteristics of IEEE 802.15.4.
 * with energy above the Energy Detection (ED) threshold.
 *
 * @description The function set CCA mode 1, 2 or 3 by write ccaMode value
 * to the _BEE_RFCON0 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_cca_mode ( bee_t *ctx, uint8_t cca_mode );

/**
 * @brief Set RSSI mode function
 *
 * @param ctx                        Click object.
 * @param rssi_mode:
 * - 0x01 : RSSI Mode 1, Initiate RSSI calculation;
 * - 0x02 : RSSI Mode 2, Calculate RSSI for each received packet. The RSSI value is stored in RXFIFO;
 *
 * @description The function set RSSI mode 1 or 2 by write rssiMode value
 * to the _BEE_RFCON0 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_rssi_mode ( bee_t *ctx, uint8_t rssi_mode );

/**
 * @brief Set device as PAN coordinator function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set device as PAN coordinator and disable Slotted CSMA-CA mode
 * by sets to '1' [ bit 3 ] states of _BEE_RXMCR register address
 * and cleared to '0' [ bit 5 ] states of _BEE_TXMCR register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_nonbeacon_pan_coordinator_device ( bee_t *ctx );

/**
 * @brief Set device as coordinator function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set device as coordinator and disable Slotted CSMA-CA mode
 * by sets to '1' [ bit 2 ] states of _BEE_RXMCR register address
 * and cleared to '0' [ bit 5 ] states of _BEE_TXMCR register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_nonbeacon_coordinator_device ( bee_t *ctx );

/**
 * @brief Set nonbeacon device function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set device is not set as PAN coordinator and device is not set as coordinator
 * by cleared to '0' [ bit 3 : bit 2 ] states of _BEE_RXMCR register address
 * and cleared to '0' [ bit 5 ] states of _BEE_TXMCR register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_nonbeacon_device ( bee_t *ctx );

/**
 * @brief Set ACK request function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set TX Normal FIFO Acknowledgement Request
 * by sets to '1' [ bit 2 ] states of _BEE_TXNCON register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_ack ( bee_t *ctx );

/**
 * @brief Set not ACK request function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set TX Normal FIFO No Acknowledgement Request
 * by cleared to '0' [ bit 2 ] states of _BEE_TXNCON register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_not_ack ( bee_t *ctx );

/**
 * @brief Set enable encrypt function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set Encrypt TX Normal FIFO Security Enabled
 * by set to '1' [ bit 1 ] states of _BEE_TXNCON register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_enable_encrypt ( bee_t *ctx );

/**
 * @brief Disable encrypt function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set Encrypt TX Normal FIFO Security Disabled
 * by cleared to '0' [ bit 1 ] states of _BEE_TXNCON register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_disabl_encrypt ( bee_t *ctx );

/**
 * @brief Set interframe spacing function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set interframe spacing recomended by sets:
 * - minimum number of symbols forming a Long Interframe Spacing (LIFS) period;
 * - GTS1 and GTS2 FIFO will stop toggling with each other if the transmission fails;
 * - Clears frame pending bit;
 * - VCO Stabilization Period recomended;
 * - Transmission to reception and reception to transmission turnaround time recomended;
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_ifs_recomended ( bee_t *ctx );

/**
 * @brief Set default interframe spacing function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set default interframe spacing by sets:
 * - Disables automatic Acknowledgement response;
 * - Device is not set as PAN coordinator;
 * - Set device as coordinator;
 * - Accept only packets with good CRC;
 * - Receive all packet types with good CRC;
 * - Minimum Long Interframe Spacing ( default );
 * - VCO Stabilization Period ( default );
 * - Turnaround Time ( default );
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_ifs_default ( bee_t *ctx );

/**
 * @brief Set reception mode function
 *
 * 
 * @param ctx                        Click object.
 * @param r_mode:
 * - 0x01 : Reception Mode 1:
 *     - Discard packet when there is a MAC address mismatch, illegal frame type, dPAN/sPAN or MAC short address mismatch (default)
 *     - Accept only packets with good CRC (default)
 * - 0x02 : Reception Mode 2:
 *     - Discard packet when there is a MAC address mismatch, illegal frame type, dPAN/sPAN or MAC short address mismatch (default)
 *     - Accept all packets including those with CRC error
 * - 0x03 : Reception Mode 3:
 *     - Receive all packet types with good CRC
 *     - Accept only packets with good CRC (default)
 *
 * @description The function set reception mode
 * by write rMode value to the _BEE_RXMCR register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_reception_mode ( bee_t *ctx, uint8_t r_mode );

/**
 * @brief Set frame format filter function
 *
 * @param ctx                        Click object.
 * @param fff_mode:
 * - 0x01 : Frame Format Filter Mode 1:
 *     - All valid frames are received (default)
 * - 0x02 : Frame Format Filter Mode 2:
 *     - Only command frames are received, all other frames are filtered out
 * - 0x03 : Frame Format Filter Mode 3:
 *     - Only data frames are received, all other frames are filtered out
 * - 0x04 : Frame Format Filter Mode 4:
 *     - Only beacon frames are received, all other frames are filtered out
 *
 * @description The function set reception mode
 * by write fffMode value to the _BEE_RXFLUSH register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_frame_format_filter ( bee_t *ctx, uint8_t fff_mode );

/**
 * @brief Set flush RX FIFO pointer function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set flush RX FIFO pointer
 * by resets the RXFIFO address pointer to zero
 * and RXFIFO data is not modified of the _BEE_RXFLUSH register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_flush_rx_fifo_pointer ( bee_t *ctx );

/**
 * @brief Set short address function
 *
 * @param short_address          pointer of the short address value
 *
 * @description The function set short address
 * by write shortAddress value to the _BEE_SADRL and _BEE_SADRH register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_short_address (  bee_t *ctx, uint8_t *short_address );

/**
 * @brief Set long address function
 *
 * @param ctx                        Click object.
 * @param long_address           pointer of the long address value
 *
 * @description The function set long address
 * by write longAddress value start on _BEE_EADR0 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_long_address ( bee_t *ctx, uint8_t *long_address );

/**
 * @brief Set PAN ID function
 *
 * @param ctx                        Click object.
 * @param pan_id                 pointer of the PAN ID value
 *
 * @description The function set PAN ID
 * by write panId value to the _BEE_PANIDL and _BEE_PANIDH register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_pan_id ( bee_t *ctx, uint8_t *pan_id );

/**
 * @brief Enable Immediate Wake-up mode function
 *
 * @param ctx                        Click object.
 * 
 * @description Function enable immediate wake-up mode
 * by wake signal polarity is active-high, enable wake I/O pin
 * and by sets to '1' [ bit 7 ] states of _BEE_WAKECON register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_enable_immediate_wake_up ( bee_t *ctx );

/**
 * @brief Hardware Wake Up function
 *
 * @param ctx                        Click object.
 * 
 * @description The function hardware Wake Up by set to '1' RST pin state
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * Delay is 5 ms
 */
void bee_hw_wake_up ( bee_t *ctx );

/**
 * @brief Enable PLL function
 *
 * @param ctx                        Click object.
 * 
 * @description The function enable PLL
 * by sets to '1' [ bit 7 ] states of _BEE_RFCON2 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_enable_pll ( bee_t *ctx );

/**
 * @brief Disable PLL function
 *
 * @param ctx                        Click object.
 * 
 * @description The function enable PLL
 * by cleared to '0' [ bit 7 ] states of _BEE_RFCON2 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_disable_pll ( bee_t *ctx );

/**
 * @brief Set scale control for Tx power function
 *
 * @param ctx                        Click object.
 * @param tx_power               TX power value from 0 to 31
 *
 * @description The function set scale control for Tx power
 * by write txPower value to the _BEE_RFCON3 register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_set_tx_power ( bee_t *ctx, uint8_t tx_power );

/**
 * @brief Basic initialization module function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set basic initialization module:
 * - Power amplifier control 2 register sets:
 *   - FIFO Enable;
 *   - Transmitter Enable On Time Symbol ( recommended value: 0x60 );
 * - TX stabilization register sets:
 *   - VCO Stabilization Period ( recommended value: 0x90 );
 * -  RF control 1 register sets:
 *   -  VCO Optimize Control;
 * - RF control 6 register sets:
 *   - Recovery from Sleep control less than 1 ms;
 *   - Battery Monitor Disabled;
 * -  RF control 7 register sets:
 *   - Sleep Clock Selection 100 kHz internal oscillator;
 * - RF control 8 register sets:
 *   - VCO Control;
 * - Sleep calibration 1 register sets:
 *   - Sleep Calibration Counter;
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_basic_init ( bee_t *ctx ); 

/**
 * @brief Initialization nonbeacon module function
 *
 * @param ctx                        Click object.
 * 
 * @description The function set initialization nonbeacon mode by:
 * - sets basic initialization module;
 * - set CCA mode to value 1;
 * - set RSSI mode to value 2;
 * - enable interrupt;
 * - set channel to value 11;
 * - RF state machine reset;
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_nonbeacon_init ( bee_t *ctx );

/**
 * @brief Check interrupt activity function
 *
 * 
 * @param ctx                        Click object.
 * 
 * @return interrupt status:
 * - 0 : interrupt is not active;
 * - 1 : interrupt is active;
 *
 * @description The function check interrupt status
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
uint8_t bee_interrupt_activity ( bee_t *ctx );

/**
 * @brief Start transmission function
 *
 * @param ctx                        Click object.
 * 
 * @description The function start transmission
 * by sets transmit the frame in the TX Normal FIFO
 * to the _BEE_TXNCON register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 *
 * @note
 * bits is automatically cleared to '0' by hardware
 */
void bee_start_transmit ( bee_t *ctx );

/**
 * @brief Read RX FIFO function
 *
 * @param ctx                        Click object.
 * @param rx_data                    pointer to the memory location where rxData be stored
 *
 * @description The function set short address
 * by write shortAddress value to the _BEE_SADRL and _BEE_SADRH register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_read_rx_fifo ( bee_t *ctx, uint8_t *rx_data );

/**
 * @brief Write TX normal FIFO function
 *
 * @param ctx                         Click object.
 * @param address_tx_normal_fifo      16-bit normal FIFO register address from 0x000 to 0x07F
 * @param tx_data                     pointer to the memory location where txData be stored
 *
 * @description The function write TX normal FIFO
 * by write txData value to the starts from addressTXnormalFIFO register address
 * of MRF24J40MA 2.4GHz transceiver module on BEE Click board.
 */
void bee_write_tx_normal_fifo ( bee_t *ctx, uint16_t address_tx_normal_fifo, uint8_t *tx_data );

/**
 * @brief Get interrupt state function
 *
 * @param ctx                         Click object.
 * 
 * @return interrupt state
 * - 0 : not active
 * - 1 : active
 *
 * @description The function gets interrupt state
 * by return status of INT pin of BEE Click board.
 */
uint8_t bee_interrupt ( bee_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BEE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

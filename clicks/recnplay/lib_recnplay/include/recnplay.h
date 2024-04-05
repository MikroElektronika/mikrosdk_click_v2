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
 * \brief This file contains API for Rec & Play Click Click driver.
 *
 * \addtogroup recnplay Rec & Play Click Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RECNPLAY_H
#define RECNPLAY_H

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

#define RECNPLAY_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup general_macros General macros
 * \{
 */
#define    RECPLAY_PLAY_VP                      0xA6
#define    RECPLAY_PLAY_VP_RN                   0xAE
#define    RECPLAY_EXE_VM                       0xB0
#define    RECPLAY_REC_MSG                      0x38
#define    RECPLAY_REC_MSG_ADDR                 0x3A
#define    RECPLAY_PLAY_MSG                     0x3C
#define    RECPLAY_PLAY_SIL                     0xA8
#define    RECPLAY_STOP                         0x2A
#define    RECPLAY_ERASE_MSG                    0x3E
#define    RECPLAY_SPI_PCM_WRITE                0xAA
#define    RECPLAY_SPI_PCM_READ                 0xAC
#define    RECPLAY_SPI_SND_DEC                  0xC0
#define    RECPLAY_SPI_RCV_ENC                  0xC2
#define    RECPLAY_READ_STATUS                  0x40
#define    RECPLAY_READ_INT                     0x46
#define    RECPLAY_READ_MSG_ADDR                0x42
#define    RECPLAY_READ_MSG_LEN                 0x44
#define    RECPLAY_READ_ID                      0x48
#define    RECPLAY_DIG_READ                     0xA2
#define    RECPLAY_DIG_WRITE                    0xA0
#define    RECPLAY_ERASE_MEM                    0x24
#define    RECPLAY_CHIP_ERASE                   0x26
#define    RECPLAY_PWR_UP                       0x10
#define    RECPLAY_PWR_DOWN                     0x12
#define    RECPLAY_SET_CLK_CFG                  0xB4
#define    RECPLAY_READ_CLK_CFG                 0xB6
#define    RECPLAY_WRITE_CFG_REG                0xB8
#define    RECPLAY_READ_CFG_REG                 0xBA
/** \} */

/**
 * \defgroup interrupt Interrupt macros
 * \{
 */
#define    RECPLAY_INT_PEAK_DET_MASK            0x80
#define    RECPLAY_INT_MEM_PROT_ERR_MASK        0x40
#define    RECPLAY_INT_WR_FIN_MASK              0x20
#define    RECPLAY_INT_CMD_ERR_MASK             0x10
#define    RECPLAY_INT_OVF_ERR_MASK             0x08
#define    RECPLAY_INT_CMD_FIN_MASK             0x04
#define    RECPLAY_INT_ADDR_ERR_MASK            0x02
#define    RECPLAY_INT_FULL_ERR_MASK            0x01
/** \} */

/**
 * \defgroup status Status macros
 * \{
 */
#define    RECPLAY_STAT_PWR_DOWN_MASK           0x80
#define    RECPLAY_STAT_DBUF_RDY_MASK           0x40
#define    RECPLAY_STAT_INT_GEN_MASK            0x20
#define    RECPLAY_STAT_REC_MEM_FULL_MASK       0x10
#define    RECPLAY_STAT_VM_BSY_MASK             0x04
#define    RECPLAY_STAT_CBUF_FULL_MASK          0x02
#define    RECPLAY_STAT_CMD_BSY_MASK            0x01
/** \} */

/**
 * \defgroup pins Pin macros
 * \{
 */
#define    RECPLAY_INT_GEN_PIN                  0x00
#define    RECPLAY_INT_NO_GEN_PIN               0x01
#define    RECPLAY_SPI_RDY_PIN                  0x01
#define    RECPLAY_SPI_BSY_PIN                  0x00
/** \} */

/**
* \defgroup configuration_registers Configuration registers
* \{
*/
#define    RECPLAY_CFG00_REG                   0x00
#define    RECPLAY_CFG01_REG                   0x01
#define    RECPLAY_CFG02_REG                   0x02
#define    RECPLAY_CFG03_REG                   0x03
#define    RECPLAY_CFG04_REG                   0x04
#define    RECPLAY_CFG05_REG                   0x05
#define    RECPLAY_CFG06_REG                   0x06
#define    RECPLAY_CFG07_REG                   0x07
#define    RECPLAY_CFG08_REG                   0x08
#define    RECPLAY_CFG09_REG                   0x09
#define    RECPLAY_CFG0A_REG                   0x0A
#define    RECPLAY_CFG0B_REG                   0x0B
#define    RECPLAY_CFG0C_REG                   0x0C
#define    RECPLAY_CFG0D_REG                   0x0D
#define    RECPLAY_CFG0E_REG                   0x0E
#define    RECPLAY_CFG0F_REG                   0x0F
#define    RECPLAY_CFG10_REG                   0x10
#define    RECPLAY_CFG11_REG                   0x11
#define    RECPLAY_CFG12_REG                   0x12
#define    RECPLAY_CFG13_REG                   0x13
#define    RECPLAY_CFG14_REG                   0x14
#define    RECPLAY_CFG15_REG                   0x15
#define    RECPLAY_CFG16_REG                   0x16
#define    RECPLAY_CFG17_REG                   0x17
#define    RECPLAY_CFG18_REG                   0x18
#define    RECPLAY_CFG19_REG                   0x19
#define    RECPLAY_CFG1A_REG                   0x1A
#define    RECPLAY_CFG1B_REG                   0x1B
#define    RECPLAY_CFG1C_REG                   0x1C
#define    RECPLAY_CFG1D_REG                   0x1D
#define    RECPLAY_CFG1E_REG                   0x1E
#define    RECPLAY_CFG1F_REG                   0x1F
#define    RECPLAY_CFG20_REG                   0x20
#define    RECPLAY_CFG21_REG                   0x21
#define    RECPLAY_CFG22_REG                   0x22
#define    RECPLAY_CFG23_REG                   0x23
#define    RECPLAY_CFG24_REG                   0x24
#define    RECPLAY_CFG25_REG                   0x25
#define    RECPLAY_CFG26_REG                   0x26
#define    RECPLAY_CFG27_REG                   0x27
#define    RECPLAY_CFG28_REG                   0x28
#define    RECPLAY_CFG29_REG                   0x29
#define    RECPLAY_CFG2A_REG                   0x2A
#define    RECPLAY_CFG2B_REG                   0x2B
#define    RECPLAY_CFG2C_REG                   0x2C
#define    RECPLAY_CFG2D_REG                   0x2D
#define    RECPLAY_CFG2E_REG                   0x2E
#define    RECPLAY_CFG2F_REG                   0x2F
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RECNPLAY_RETVAL  uint8_t

#define RECNPLAY_OK           0x00
#define RECNPLAY_INIT_ERROR   0xFF
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

    digital_in_t rdy;
    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} recnplay_t;

/**
 * @brief Device ID data
 */
typedef struct
{
    uint8_t part_id;
    uint8_t man_id;
    uint8_t mem_type;
    uint8_t dev_id;

} recnplay_dev_id_t;

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

    pin_name_t rdy;
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} recnplay_cfg_t;

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
void recnplay_cfg_setup ( recnplay_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RECNPLAY_RETVAL recnplay_init ( recnplay_t *ctx, recnplay_cfg_t *cfg );

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
void recnplay_generic_transfer ( recnplay_t *ctx,  uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Voice Prompt Play Command
 *
 * @param ctx    Click object. 
 * @param index  Index of Voice Prompt
 *
 * @returns Status byte
 *
 * @description Function initiates a play of a pre-recorded voice prompt.
 *
 * @note Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when playback is finished.
 */
RECNPLAY_RETVAL recplay_play_vp ( recnplay_t* ctx, uint16_t index );

/**
 * @brief Voice Prompt @Rn Play Command
 *
 * @param ctx       Click object.
 * @param value_rn  R(n) selection from 0 to 7
 *
 * @returns Status byte
 *
 * @description Function initiates a play of a pre-recorded voice prompt, but 16bit index is stored in Rn.
 * The 16 bit value of Rn, user can find in Configuration registers from CFG20 to CFG2F.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when playback is finished.
 */
RECNPLAY_RETVAL recplay_play_vp_rn ( recnplay_t* ctx, uint8_t value_rn );

/**
 * @brief Voice Macro Execute Command
 *
 * @param ctx       Click object.
 * @param index     Index of Voice Macro
 *
 * @returns Status byte
 *
 *  @description Function initiates the execution of a pre-recorded voice group.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when playback is finished.
 */
RECNPLAY_RETVAL recplay_execute_vm ( recnplay_t* ctx, uint16_t index );

/**
 * @brief Message Record Command
 *
 * @param ctx       Click object.
 *
 * @returns Status byte
 *
 * @description Function initiates a managed record at first available location in memory.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when recording complete,
 *                       FULL_ERR when device fills available memory.
 */
RECNPLAY_RETVAL recplay_record_msg ( recnplay_t* ctx );

/**
 * @brief Message Record at Address Command
 *
 * @param ctx       Click object.
 * @param mem_addr  Memory location
 *
 * @returns Status byte
 *
 * @description Function initiates a managed record starting at a specified address.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when recording complete,
 *                       FULL_ERR when device fills available memory, ADDR_ERR if invalid address sent.
 */
RECNPLAY_RETVAL recplay_record_msg_addr ( recnplay_t* ctx, uint32_t mem_addr );

/**
 * @brief Message Play at Address Command
 *
 * @param ctx            Click object.
 * @param mem_addr       Memory location
 * @param sector_offset  Sector offset
 *
 * @returns Status byte
 *
 * @description Function initiates a play of a recorded message starting at a specified address, with a specified sector offset.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when playback complete,
 *                       ADDR_ERR if invalid address sent.
 */
RECNPLAY_RETVAL recplay_play_msg ( recnplay_t* ctx, uint32_t mem_addr, uint16_t sector_offset );

/**
 * @brief Silence Play Command
 *
 * @param ctx             Click object.
 * @param silence_length  Silence length * 32ms
 *
 * @returns Status byte
 *
 * @description Function plays a period of silence to the signal path.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when silence playback complete.
 */
RECNPLAY_RETVAL recplay_play_silence ( recnplay_t* ctx, uint8_t silence_length );

/**
 * @brief Stop Command
 *
 * @param ctx      Click object.
 *
 * @returns Status byte
 *
 * @description Function stops any current audio command.
 * Interrupt Generation: Command itself does not generate interrupt, only those commands that it is stopping.
 */
RECNPLAY_RETVAL recplay_stop ( recnplay_t* ctx );

/**
 * @brief Message Erase at Address Command
 *
 * @param ctx       Click object.
 * @param mem_addr  Memory location
 *
 * @returns Status byte
 *
 * @description Function erases the message starting at the specified address.
 * Interrupt Generation: CMD_ERR if not accepted, CMD_FIN when erase complete,
 *                       ADDR_ERR if invalid address sent.
 */
RECNPLAY_RETVAL recplay_erase_msg ( recnplay_t* ctx, uint32_t mem_addr );

/**
 * @brief PCM Data SPI Write Command
 *
 * @param ctx       Click object.
 * @param data_pcm  Audio data in 16bit PCM format
 * @param num_pcm   Number of PCM words
 *
 * @returns Status byte
 *
 * @description Function writes audio data in 16bit PCM format via SPI interface.
 * Interrupt Generation: OVF_ERR if RDY/BSY violated.
 */
RECNPLAY_RETVAL recplay_spi_write_pcm ( recnplay_t* ctx, uint16_t* data_pcm, uint8_t num_pcm );

/**
 * @brief PCM Data SPI Read Command
 *
 * @param ctx       Click object.
 * @param data_pcm  Memory where PCM data be stored
 * @param num_pcm   Number of PCM words
 *
 * @returns Status byte
 *
 * @description Function reads audio data in 16bit PCM format via SPI interface.
 * Interrupt Generation: OVF_ERR if RDY/BSY violated.
 */
RECNPLAY_RETVAL recplay_spi_read_pcm ( recnplay_t* ctx, uint16_t* data_pcm, uint8_t num_pcm );

/**
 * @brief SPI Send Compressed Data to Decode Command
 *
 * @param ctx          Click object.
 * @param cmprsd_data  Compressed audio data
 * @param n_data       Number of compressed data bytes
 *
 * @returns Status byte
 *
 * @description Function writes compressed audio data via SPI interface.
 * Interrupt Generation: OVF_ERR if RDY/BSYB violated.
 */
RECNPLAY_RETVAL recplay_spi_send_cmprsd_data ( recnplay_t* ctx, uint8_t* cmprsd_data, uint8_t n_data );

/**
 * @brief SPI Receive Encoded Data Command
 *
 * @param ctx           Click object.
 * @param encoded_data  Memory where compressed audio data be stored
 * @param n_data        Number of compressed data bytes
 *
 * @returns Status byte
 *
 * @description Function reads compressed audio data via SPI intreface.
 * Interrupt Generation: OVF_ERR if RDY/BSYB violated.
 */
RECNPLAY_RETVAL recplay_spi_receive_enc_data ( recnplay_t* ctx, uint8_t* encoded_data, uint8_t n_data );

/**
 * @brief Status Read Command
 *
 * @param ctx            Click object.
 * @param interr_status  Memory where interrupt status byte be stored
 *
 * @returns Status byte
 *
 * @description Function queries the ISD3900 device status.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_status ( recnplay_t* ctx, uint8_t* interr_status );

/**
 * @brief Interrupt Read Command
 *
 * @param ctx            Click object.
 * @param interr_status  Memory where interrupt status byte be stored
 *
 * @returns Status byte
 *
 * @description Function queries the ISD3900 device status and clears any pending interrupts.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_interr ( recnplay_t* ctx, uint8_t* interr_status );

/**
 * @brief Recorded Message Address Read Command
 *
 * @param ctx            Click object.
 * @param msg_addr       Memory where recorded message address will be stored
 * @param msg_length     Memory where recorded message length will be stored
 *
 * @returns Status byte
 *
 * @description Function reports the start address of the last or current message and message length.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_msg_addr ( recnplay_t* ctx, uint32_t* msg_addr, uint16_t* msg_length );

/**
 * @brief Message Length Read Command
 *
 * @param ctx            Click object.
 * @param msg_length     Memory where message length be stored
 *
 * @returns Status byte
 *
 * @description Function reads number of sectors played by the last or current PLAY command.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_msg_length ( recnplay_t* ctx, uint16_t* msg_length );

/**
 * @brief ISD3900 ID Read Command
 *
 * @param ctx            Click object.
 * @param dev_id_data    Device ID data object
 *
 * @returns Status byte
 *
 * @description Function reads device and memory ID.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_id ( recnplay_t* ctx, recnplay_dev_id_t* dev_id_data );

/**
 * @brief Digital Read Command
 *
 * @param ctx       Click object.
 * @param mem_addr  Memory address
 * @param data_out  Memory where data be stored
 * @param n_data    Number of data bytes to be read
 *
 * @returns Status byte
 *
 * @description Function initiates a read of flash memory from specified address.
 * Interrupt Generation: ADDR_ERR if memory protected or RDY/BSYB violated,
 *                       OVF_ERR if read past end of array.
 */
RECNPLAY_RETVAL recplay_dig_read ( recnplay_t* ctx, uint32_t mem_addr, uint8_t* data_out, uint8_t n_data );

/**
 * @brief Digital Write Command
 *
 * @param ctx       Click object.
 * @param mem_addr  Memory address
 * @param data_in   Data to be written
 * @param n_data    Number of data bytes to be written
 *
 * @returns Status byte
 *
 * @description Function initiates a write to flash memory from specified address.
 * Interrupt Generation: ADDR_ERR if memory protected or RDY/BSYB violated,
 *                       OVF_ERR if write past end of array.
 */
RECNPLAY_RETVAL recplay_dig_write ( recnplay_t* ctx, uint32_t mem_addr, uint8_t* data_in, uint8_t n_data );

/**
 * @brief Memory Erase Command
 *
 * @param ctx         Click object.
 * @param start_addr  Start address
 * @param end_addr    End address
 *
 * @returns Status byte
 *
 * @description Function erases memory from sector containing Start address to sector containing End address.
 * Interrupt Generation: ADDR_ERR if memory protected, CMD_ERR if device is busy,
 *                       CMD_FIN when erase operation complete.
 */
RECNPLAY_RETVAL recplay_erase_mem ( recnplay_t* ctx, uint32_t start_addr, uint32_t end_addr );

/**
 * @brief Chip Erase Command
 *
 * @param ctx         Click object.
 *
 * @returns Status byte
 *
 * @description Function erases the entire contents of the external memory.
 * Interrupt Generation: CMD_ERR if device is busy and cannot accept command,
 *                       CMD_FIN when erase operation complete.
 */
RECNPLAY_RETVAL recplay_erase_chip ( recnplay_t* ctx );

/**
 * @brief Power Up Command
 *
 * @param ctx         Click object.
 *
 * @returns Status byte
 *
 * @description Function powers up the device.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_pwr_up ( recnplay_t* ctx );

/**
 * @brief Power Down Command
 *
 * @param ctx         Click object.
 *
 * @returns Status byte
 *
 * @description Function powers down the device.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_pwr_down ( recnplay_t* ctx );

/**
 * @brief Clock Configuration Set Command
 *
 * @param clk_cnfg  Configuration byte for clock
 *
 * @returns Status byte
 *
 * @description Function loads the clock configuration register.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_set_clk_cnfg ( recnplay_t* ctx, uint8_t clk_cnfg );

/**
 * @brief Clock Configuration Read Command
 *
 * @param ctx         Click object.
 * @param clk_cnfg    Memory where clock configuration byte be stored
 *
 * @returns Status byte
 *
 * @description Function reads the clock configuration register.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_clk_cnfg ( recnplay_t* ctx, uint8_t* clk_cnfg );

/**
 * @brief Configuration Write Command
 *
 * @param ctx         Click object.
 * @param reg_addr    Configuration register address (from 0x00 to 0x2F)
 * @param cnfg_data   Configuration data to be written
 * @param n_data      Number of data bytes to be written
 *
 * @returns Status byte
 *
 * @description Function loads configuration registers starting at the specified address.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_write_cnfg_reg ( recnplay_t* ctx, uint8_t reg_addr, uint8_t* cnfg_data, uint8_t n_data );

/**
 * @brief Configuration Read Command
 *
 * @param ctx         Click object.
 * @param reg_addr    Configuration register address (from 0x00 to 0x2F)
 * @param cnfg_data   Memory where configuration data be stored
 * @param n_data      Number of data bytes to be read
 *
 * @returns Status byte
 *
 * @description Function reads the configuration registers starting at the specified address.
 * Interrupt Generation: This command does not generate interrupt.
 */
RECNPLAY_RETVAL recplay_read_cnfg_reg ( recnplay_t* ctx, uint8_t reg_addr, uint8_t* cnfg_data, uint8_t n_data );

/**
 * @brief SPI Data Transfer Status Check Command
 *
 * @param ctx         Click object.
 *
 * @returns 1 - ISD3900 is ready for new command, 0 - ISD3900 is busy
 *
 * @description Function reports the status of data transfer on the SPI interface.
 */
uint8_t recplay_check_rdy ( recnplay_t* ctx );

/**
 * @brief Interrupt Request Pin Check Command
 *
 * @param ctx         Click object.
 *
 * @returns 0 - Interrupt is generated, 1 - Interrupt is not generated
 *
 * @description Function reports the status of the INT pin, does interrupt generated or not.
 */
uint8_t recplay_check_int ( recnplay_t* ctx );

/**
 * @brief ISD3900 Reset Command
 *
 * @param ctx     Click object.
 *
 * @description Function performs the device reset and after that puts the device in normal operation mode.
 */
void recplay_reset ( recnplay_t* ctx );


#ifdef __cplusplus
}
#endif
#endif  // _RECNPLAY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

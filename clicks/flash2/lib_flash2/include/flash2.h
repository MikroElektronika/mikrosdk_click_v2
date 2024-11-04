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
 * \brief This file contains API for Flash 2 Click driver.
 *
 * \addtogroup flash2 Flash 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FLASH2_H
#define FLASH2_H

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

#define FLASH2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.hld = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

#define            FLASH2_STATUS_WEL             0x02 
#define            FLASH2_STATUS_WSE             0x04 
#define            FLASH2_STATUS_WSP             0x08 
#define            FLASH2_STATUS_WPLD            0x10 
#define            FLASH2_STATUS_SEC             0x20 
#define            FLASH2_STATUS_RES             0x40  
#define            FLASH2_STATUS_BUSY            0x80


#define            FLASH2_CFG_RES                0x01 
#define            FLASH2_CFG_IOC                0x02 
#define            FLASH2_CFG_BPNV               0x08 
#define            FLASH2_CFG_WPEN               0x80 


#define            FLASH2_INSTR_NOP              0x00 /**< No Operation */
#define            FLASH2_INSTR_RSTEN            0x66 /**< Reset Enable */
#define            FLASH2_INSTR_RST              0x99 /**< Reset Memory */
#define            FLASH2_INSTR_EQIO             0x38 /**< Enable Quad I/O */
#define            FLASH2_INSTR_RSTQIO           0xFF /**< Reset Quad I/O */
#define            FLASH2_INSTR_RDSR             0x05 /**< Read Status Register */
#define            FLASH2_INSTR_WRSR             0x01 /**< Write Status Register */
#define            FLASH2_INSTR_RDCR             0x35 /**< Read Configuration Register */
#define            FLASH2_INSTR_READ             0x03 /**< Read Memory */
#define            FLASH2_INSTR_HS_READ          0x0B /**< Read Memory at Higher Speed */
#define            FLASH2_INSTR_SQOR             0x6B /**< SPI Quad Output Read */
#define            FLASH2_INSTR_SQIOR            0xEB /**< SPI Quad I/O Read */
#define            FLASH2_INSTR_SDOR             0x3B /**< SPI Dual Output Read */
#define            FLASH2_INSTR_SDIOR            0xBB /**< SPI Dual I/O Read */
#define            FLASH2_INSTR_SB               0xC0 /**< Set Burst Length */
#define            FLASH2_INSTR_RBSQI            0x0C /**< SQI Read Burst with Wrap */
#define            FLASH2_INSTR_RBSPI            0xEC /**< SPI Read Burst with Wrap */
#define            FLASH2_INSTR_JEDECID          0x9F /**< JEDEC-ID Read */
#define            FLASH2_INSTR_QUAD_JID         0xAF /**< Quad I/O J-ID read */
#define            FLASH2_INSTR_SFDP             0x5A /**< Serial Flash Discoverable Parameters */
#define            FLASH2_INSTR_WREN             0x06 /**< Write Enable */
#define            FLASH2_INSTR_WRDI             0x04 /**< Write Disable */
#define            FLASH2_INSTR_SE               0x20 /**< Erase 4 KBytes of Memory Array */
#define            FLASH2_INSTR_BE               0xD8 /**< Erase 64, 32 or 8 KBytes of Memory Array */
#define            FLASH2_INSTR_CE               0xC7 /**< Erase Full Array */
#define            FLASH2_INSTR_PP               0x02 /**< Page Program */
#define            FLASH2_INSTR_SPI_QUAD         0x32 /**< SQI Quad Page Program */
#define            FLASH2_INSTR_WRSU             0xB0 /**< Suspends Program / Erase */
#define            FLASH2_INSTR_WRRE             0x30 /**< Resumes Program / Erase */
#define            FLASH2_INSTR_RBPR             0x72 /**< Read Block-Protection Register */
#define            FLASH2_INSTR_WBPR             0x42 /**< Write Block-Protection Register */
#define            FLASH2_INSTR_LBPR             0x8D /**< Lock Down Block-Protection Register */
#define            FLASH2_INSTR_NVWLDR           0xE8 /**< Non-Volatile Write Lock-Down Register */
#define            FLASH2_INSTR_ULBPR            0x98 /**< Global Block Protection Unlock */
#define            FLASH2_INSTR_RSID             0x88 /**< Read Security ID */
#define            FLASH2_INSTR_PSID             0xA5 /**< Program User Security ID Area */
#define            FLASH2_INSTR_LSID             0x85 /**< Lockout Security ID Programming */


#define            FLASH2_START_PAGE_ADDRESS 0x010000
#define            FLASH2_END_PAGE_ADDRESS   0x7FFFFF
#define            FLASH2_FLASH_PAGE_SIZE    256
/**
 * \defgroup error_code Error Code
 * \{
 */
#define FLASH2_RETVAL  uint8_t

#define FLASH2_OK           0x00
#define FLASH2_INIT_ERROR   0xFF
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
    digital_out_t cs;

    // Output pins 

    digital_out_t hld;
    digital_out_t wp;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} flash2_t;

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

    pin_name_t hld;
    pin_name_t wp;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} flash2_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void flash2_cfg_setup ( flash2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FLASH2_RETVAL flash2_init ( flash2_t *ctx, flash2_cfg_t *cfg );

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
void flash2_generic_transfer ( flash2_t *ctx, uint8_t *wr_buf, 
                               uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief  Flash 2 Busy 
 *
 * @param ctx               Click object.
 * @returns                 0 - Success, else - failure.
 * @description Checks if Click is busy reading/writing
 *
 * @note Used to check when Click is ready to be written to / read from.
 *
 */
uint8_t flash2_busy( flash2_t *ctx );

/**
 * @brief  Flash 2 Get Status Register 
 *
 * @param ctx               Click object.
 * @returns                 Status register.
 * 
 * @description The Read-Status Register command outputs the contents
 * of the Status register.
 *
 */
uint8_t flash2_get_status_reg( flash2_t *ctx );

/**
 * @brief  Flash 2 Erase Status 
 *
 * @param ctx             Click object.
 * @returns               0-erase not suspended, 1-erase suspended.
 * @description Checks if Click erase is suspended
 *
 */
uint8_t flash2_erase_status( flash2_t *ctx );

/**
 * @brief  Flash 2 Write Status 
 *
 * @param ctx             Click object.
 * @description Checks if Click write is suspended
 *
 * @returns 0 - write not suspended
 * @returns 1 - write suspended
 *
 */
uint8_t flash2_write_status( flash2_t *ctx );

/**
 * @brief  Flash 2 Program Status 
 *
 * @param ctx             Click object.
 * @description Checks if Click write-program is suspended
 *
 * @returns 0 - write program not suspended
 * @returns 1 - write program suspended
 *
 */
uint8_t flash2_program_status( flash2_t *ctx );

/**
 * @brief  Flash 2 Protect Status 
 *
 * @param ctx             Click object.
 * @description Checks if Click write-protect lock-down is suspended
 *
 * @returns 0 - write-protect not suspended
 * @returns 1 - write protect suspended
 *
 */
uint8_t flash2_protect_status( flash2_t *ctx );

/**
 * @brief flash2_lock_security_id
 *
 * @param ctx             Click object.
 * @description The Lockout Security ID instruction prevents any future
 * changes to the Security ID, and is supported in both
 * SPI and SQI modes.
 *
 */
void flash2_lock_security_id( flash2_t *ctx );

/**
 * @brief  Flash 2 Security Status 
 *
 * @param ctx             Click object.
 * @description Checks if Click security ID is locked
 *
 * @returns 0 - security ID not locked
 * @returns 1 - security ID locked
 *
 */
uint8_t flash2_security_status( flash2_t *ctx );

/**
 * @brief  Flash 2 Write Protect Enable 
 *
 * @param ctx             Click object.
 * @description Enables Write Protect on Flash 2 Click
 *
 *
 */
void flash2_write_protect_enable( flash2_t *ctx );

/**
 * @brief  Flash 2 Write Protect Disable 
 *
 * @param ctx             Click object.
 * @description Disables Write Protect on Flash 2 Click
 *
 *
 */
void flash2_write_protect_disable( flash2_t *ctx );

/**
 * @brief  Flash 2 Hold Enable 
 *
 * @param ctx             Click object.
 * @description Enables Hold on Flash 2 Click
 *
 *
 */
void flash2_hold_enable( flash2_t *ctx );

/**
 * @brief  Flash 2 Hold Disable 
 *
 * @param ctx             Click object.
 * @description Enables Hold on Flash 2 Click
 *
 *
 */
void flash2_hold_disable( flash2_t *ctx );

/**
 * @brief  Flash 2 Write Suspend 
 *
 * @param ctx             Click object.
 * @description Write-Suspend allows the interruption of Sector-Erase,
 * Block-Erase, SPI Quad Page-Program, or Page-Pro-
 * gram operations in order to erase, program, or read
 * data in another portion of memory. The original opera-
 * tion can be continued with the Write-Resume com-
 * mand. This operation is supported in both SQI and SPI
 * protocols.
 *  Only one write operation can be suspended at a time;
 * if an operation is already suspended, the device will
 * ignore the Write-Suspend command. Write-Suspend
 * during Chip-Erase is ignored; Chip-Erase is not a valid
 * command while a write is suspended. The Write-
 * Resume command is ignored until any write operation
 * (Program or Erase) initiated during the Write-Suspend
 * is complete. The device requires a minimum of 500 μs
 * between each Write-Suspend command.
 *
 *
 */
void flash2_write_suspend( flash2_t *ctx );


/**
 * @brief  Flash 2 Write Resume 
 *
 * @param ctx             Click object.
 * @description Write-Suspend allows the interruption of Sector-Erase,
 * Block-Erase, SPI Quad Page-Program, or Page-Pro-
 * gram operations in order to erase, program, or read
 * data in another portion of memory. The original opera-
 * tion can be continued with the Write-Resume com-
 * mand. This operation is supported in both SQI and SPI
 * protocols.
 *  Only one write operation can be suspended at a time;
 * if an operation is already suspended, the device will
 * ignore the Write-Suspend command. Write-Suspend
 * during Chip-Erase is ignored; Chip-Erase is not a valid
 * command while a write is suspended. The Write-
 * Resume command is ignored until any write operation
 * (Program or Erase) initiated during the Write-Suspend
 * is complete. The device requires a minimum of 500 μs
 * between each Write-Suspend command.
 *
 */
void flash2_write_resume( flash2_t *ctx );

/**
 * @brief  Flash 2 Get Security ID SPI 
 *
 * @param ctx             Click object.
 * @description Reads the Unique ID Pre-Programmed at factory
 *
 * @param buffer - Buffer to read data into.
 * @param data_count - Amount of bytes to read.
 */
void flash2_spi_get_security_id( flash2_t *ctx, uint8_t *buffer, uint32_t data_count);

/**
 * @brief  Flash 2 Get Security ID SQI 
 *
 * @param ctx             Click object.
 * @description Reads the Unique ID Pre-Programmed at factory
 *
 * @param buffer - Buffer to read data into.
 * @param data_count - Amount of bytes to read.
 *
 */
void flash2_sqi_get_security_id( flash2_t *ctx, uint8_t *buffer, uint32_t data_count);

/**
 * @brief  Flash 2 Set Security ID 
 *
 * @param ctx             Click object.
 * @description The Program Security ID instruction programs one to
 * 2040 Bytes of data in the user-programmable, Security
 * ID space. This Security ID space is one-time program-
 * mable (OTP). The device ignores a Program Security
 * ID instruction pointing to an invalid or protected
 * address
 *
 * @param buffer - Buffer to write into.
 * @param data_count - Amount of bytes to write.
 *
 */
void flash2_set_security_id( flash2_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief  Flash 2 Write Disable 
 *
 * @param ctx             Click object.
 * @description The Write Disable instruction sets the Write-
 * Enable-Latch bit in the Status register to ‘0,’ not allowing
 * Write operations to occur.
 *
 */
void flash2_write_disable( flash2_t *ctx );

/**
 * @brief  Flash 2 Get Block Protection Register SPI 
 *
 * @param ctx             Click object.
 * @description The Read Block-Protection Register instruction outputs
 * the Block-Protection register data which determines
 * the protection status.
 *
 * @param buffer - Buffer to read data into.
 * @param data_count - Amount of bytes to read.
 *
 */
void flash2_spi_get_bpr( flash2_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief  Flash 2 Get Block Protection Register SQI 
 *
 * @param ctx             Click object.
 * @description The Read Block-Protection Register instruction outputs
 * the Block-Protection register data which determines
 * the protection status.
 *
 * @param buffer - Buffer to read data into.
 * @param data_count - Amount of bytes to read.
 *
 */
void flash2_sqi_get_bpr( flash2_t *ctx, uint8_t *buffer, uint32_t data_count  );

/**
 * @brief  Flash 2 Set Block Protection Register 
 *
 * @param ctx             Click object.
 * @description The Write Block-Protection Register command changes
 * the Block-Protection register data to indicate the protection status.
 *
 * @param buffer - Buffer with new BPR register values to write.
 *
 */
void flash2_set_bpr( flash2_t *ctx, uint8_t *buffer );

/**
 * @brief  Flash 2 Lock Block Protection Register 
 *
 * @param ctx             Click object.
 * @description The Lock-Down Block-Protection Register instruction
 * prevents changes to the Block-Protection register
 * during device operation. Lock-Down resets after power
 * cycling; this allows the Block-Protection register to be
 * changed.
 *
 *
 */
void flash2_lockBpr( flash2_t *ctx );

/**
 * @brief  Flash 2 Non-Volatile Write-Lock 
 *
 * @param ctx             Click object.
 * @description The Non-Volatile Write-Lock Lock-Down Register
 * (nVWLDR) instruction controls the ability to change the
 * Write-Lock bits in the Block-Protection register.
 *
 * @param buffer - Buffer with new values for BPR register.
 *
 */
void flash2_nonvolatile_write_lock( flash2_t *ctx, uint8_t *buffer);

/**
 * @brief  Flash 2 Global Block Unlock 
 *
 * @param ctx             Click object.
 * @description The Global Block-Protection Unlock instruction clears all
 * write-protection bits in the Block-Protection register,
 * except for those bits that have been locked down with the
 * nVWLDR command.
 *
 *
 */
void flash2_global_block_unlock( flash2_t *ctx );

/**
 * @brief  Flash 2 Read 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description The Read instruction, 03H, is supported in SPI bus pro-
 * tocol only with clock frequencies up to 40 MHz. This
 * command is not supported in SQI bus protocol. The
 * device outputs the data starting from the specified
 * address location, theand Configuration n continuously streams the data
 * output through all addresses until terminated by a low-
 * to-high transition on CE#. The internal address pointer
 * will automatically increment until the highest memory
 * address is reached. Once the highest memory address
 * is reached, the address pointer will automatically return
 * to the beginning (wrap-around) of the address space.
 *
 *
 */
void flash2_read_generic( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief  Flash 2 High Speed Read 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description The High-Speed Read instruction, 0BH, is supported in
 * both SPI bus protocol and SQI protocol. This instruction
 * supports frequencies of up to 104 MHz from 2.7-3.6V
 * and up to 80 MHz from 2.3-3.6V.On power-up, the
 * device is set to use SPI.
 *
 *
 */
void flash2_highspeedRread( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief  Flash 2 Quad Write 
 *
 * @param ctx             Click object.
 * @param address - Address to start write at.
 * @param buffer - Buffer with data to write.
 * @param data_count - Amount of bytes to write.
 * 
 * @description The SPI Quad Page-Program instruction programs up
 * to 256 Bytes of data in the memory. The data for the
 * selected page address must be in the erased state
 * (FFH) before initiating the SPI Quad Page-Program
 * operation. A SPI Quad Page-Program applied to a pro-
 * tected memory area will be ignored. SST26VF064B
 * requires the ICO bit in the configuration register to be
 * set to ‘1’ prior to executing the command.
 *
 */
void flash2_quadWrite( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief  Flash 2 Write 
 *
 * @param ctx             Click object.
 * @param address - Address to start write at.
 * @param buffer - Buffer with data to write.
 * @param data_count - Amount of bytes to write.
 * 
 * @description The Page-Program instruction programs up to 256
 * Bytes of data in the memory, and supports both SPI
 * and SQI protocols. The data for the selected page
 * address must be in the erased state (FFH) before initi-
 * ating the Page-Program operation. A Page-Program
 * applied to a protected memory area will be ignored.
 *
 *
 */
void flash2_write_generic( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                        uint32_t data_count );

/**
 * @brief  Flash 2 Quad Enable 
 *
 * @param ctx             Click object.
 * 
 * The Enable Quad I/O (EQIO) instruction, 38H, enables
 * the flash device for SQI bus operation. Upon comple-
 * tion of the instruction, all instructions thereafter are
 * expected to be 4-bit multiplexed input/output (SQI
 * mode) until a power cycle or a “Reset Quad I/O instruc-
 * tion” is executed.
 *
 *
 */
void flash2_quad_enable( flash2_t *ctx );

/**
 * @brief  Flash 2 Quad Output Read 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description The SPI Quad-Output Read instruction supports fre-
 * quencies of up to 104 MHz from 2.7-3.6V and up to 80
 * MHz from 2.3-3.6V. SST26VF064B requires the IOC bit
 * in the configuration register to be set to ‘1’ prior to exe-
 * cuting the command.
 *
 *
 */
void flash2_quad_out_read( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                            uint32_t data_count);

/**
 * @brief  Flash 2 Quad I/O Read 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * @param mode - Mode to put Quad I/O in.
 * 
 * @description The SPI Quad I/O Read (SQIOR) instruction supports
 * frequencies of up to 104 MHz from 2.7-3.6V and up to
 * 80 MHz from 2.3-3.6V. SST26VF064B requires the
 * IOC bit in the configuration register to be set to ‘1’ prior
 * to executing the command.
 *
 *
 */
void flash2_quad_io_read( flash2_t *ctx, uint32_t address, uint8_t mode, uint8_t *buffer, uint32_t data_count);

/**
 * @brief  Flash 2 Quad Reset 
 *
 * @param ctx             Click object.
 * 
 * @description The Reset Quad I/O instruction, FFH, resets the device
 * to 1-bit SPI protocol operation or exits the Set Mode
 * configuration during a read sequence. This command
 * allows the flash device to return to the default I/O state
 * (SPI) without a power cycle, and executes in either 1-
 * bit or 4-bit mode. If the device is in the Set Mode con-
 * figuration, while in SQI High-Speed Read mode, the
 * RSTQIO command will only return the device to a state
 * where it can accept new command instruction. An addi-
 * tional RSTQIO is required to reset the device to SPI
 * mode.
 *
 *
 */
void flash2_quad_reset( flash2_t *ctx );

/**
 * @brief  Flash 2 Set Burst 
 *
 * @param ctx             Click object.
 * @param length
 * 
 * @description The Set Burst command specifies the number of bytes
 * to be output during a Read Burst command before the
 * device wraps around. It supports both SPI and SQI pro-
 * tocols.
 *
 * @brief
 *      - length = 0x00 = 8 bytes
 *      - length = 0x01 = 16 bytes
 *      - length = 0x02 = 32 bytes
 *      - length - 0x03 = 64 bytes
 *
 *
 */
void flash2_set_burst( flash2_t *ctx, uint8_t length );

/**
 * @brief  Flash 2 Read Burst with Wrap through SQI 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description During RBSQI, the internal address pointer automati-
 * cally increments until the last byte of the burst is
 * reached, then it wraps around to the first byte of the
 * burst. For example, if the burst length is eight Bytes,
 * and the start address is 06h, the burst sequence would be:
 * 06h, 07h, 00h, 01h, 02h, 03h, 04h, 05h, 06h, etc. The pattern
 * repeats until the command is terminated by a low-to-high
 * transition on CE#.
 *  During this operation, blocks that are Read-locked will
 * output data 00H.
 *
 * 8 Bytes 00-07H, 08-0FH, 10-17H, 18-1FH...
 * 16 Bytes 00-0FH, 10-1FH, 20-2FH, 30-3FH...
 * 32 Bytes 00-1FH, 20-3FH, 40-5FH, 60-7FH...
 * 64 Bytes 00-3FH, 40-7FH, 80-BFH, C0-FFH
 *
 *
 */
void flash2_read_sqi_burst_wrap( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief  Flash 2 Read Burst with Wrap through SPI 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description During RBSPI, the internal address pointer automati-
 * cally increments until the last byte of the burst is
 * reached, then it wraps around to the first byte of the
 * burst. For example, if the burst length is eight Bytes,
 * and the start address is 06h, the burst sequence would be:
 * 06h, 07h, 00h, 01h, 02h, 03h, 04h, 05h, 06h, etc. The pattern
 * repeats until the command is terminated by a low-to-high
 * transition on CE#.
 *  During this operation, blocks that are Read-locked will
 * output data 00H.
 *
 * 8 Bytes 00-07H, 08-0FH, 10-17H, 18-1FH...
 * 16 Bytes 00-0FH, 10-1FH, 20-2FH, 30-3FH...
 * 32 Bytes 00-1FH, 20-3FH, 40-5FH, 60-7FH...
 * 64 Bytes 00-3FH, 40-7FH, 80-BFH, C0-FFH
 *
 *
 *
 *
 */
void flash2_read_spi_burst_wrap( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                              uint32_t data_count );

/**
 * @brief  Flash 2 Read Dual Output 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description  The SPI Dual-Output Read instruction supports fre-
 * quencies of up to 104 MHz from 2.7-3.6V and up to 80
 * MHz from 2.3-3.6V.
 *
 */
void flash2_read_dual_output( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                                uint32_t data_count );

/**
 * @brief  Flash 2 Read Dual I/O 
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data to.
 * @param data_count - Amount of bytes to read.
 * 
 * @description Following the Set Mode configuration bits, the
 * SST26VF064B/064BA outputs data from the specified
 * address location. The device continually streams data
 * output through all addresses until terminated by a low-
 * to-high transition on CE#.
 *
 *  The Set Mode Configuration bit M[7:0] indicates if the
 * next instruction cycle is another SPI Dual I/O Read
 * command. When M[7:0] = AXH, the device expects the
 * next continuous instruction to be another SDIOR com-
 * mand, BBH, and does not require the op-code to be
 * entered again. The host may set the next SDIOR cycle
 * by driving CE# low, then sending the two-bit wide input
 * for address A[23:0], followed by the Set Mode configu-
 * ration bits M[7:0]. After the Set Mode configuration bits,
 * the device outputs the data starting from the specified
 * address location. There are no restrictions on address
 * location access.
 *
 *  When M[7:0] is any value other than AXH, the device
 * expects the next instruction initiated to be a command
 * instruction. To reset/exit the Set Mode configuration,
 * To reset/exit the Set Mode configuration, execute the
 * Reset Quad I/O command.
 *
 * @todo Mode Selection must be implemented
 *
 *
 *
 *
 */
void flash2_read_dual_io ( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                          uint32_t data_count );

/**
 * @brief  Flash 2 Sector Erase 
 *
 * @param ctx             Click object.
 * @param address - Address to start sector erase from.
 * 
 * @description The Sector-Erase instruction clears all bits in the
 * selected 4 KByte sector to ‘1,’ but it does not change a
 * protected memory area.
 *
 */
void flash2_sector_erase( flash2_t *ctx, uint32_t address );

/**
 * @brief  Flash 2 Block Erase 
 *
 * @param ctx             Click object.
 * @param address - Address to start block erase from.
 *
 * @description The Block-Erase instruction clears all bits in the
 * selected block to ‘1’. Block sizes can be 8 KByte, 32
 * KByte or 64 KByte depending on address.
 * A Block-Erase instruction applied to a protected memory
 * area will be ignored.
 *
 *
 */
void flash2_block_erase( flash2_t *ctx, uint32_t address );

/**
 * @brief  Flash 2 Chip Erase 
 *
 * @param ctx             Click object.
 * 
 * @description The Chip-Erase instruction clears all bits in the device
 * to ‘1.’ The Chip-Erase instruction is ignored if any of the
 * memory area is protected.
 *
 *
 */
void flash2_chip_erase( flash2_t *ctx );

/**
 * @brief  Flash 2 get Serial Flash Discoverable \
 *  Parameters
 *
 * @param ctx             Click object.
 * @param address - Address to start reading from.
 * @param buffer - Buffer to read data into.
 * @param data_count - Amount of bytes to read.
 * 
 * @description The Serial Flash Discoverable Parameters (SFDP)
 * contain information describing the characteristics of the
 * device. This allows device-independent, JEDEC ID-
 * independent, and forward/backward compatible soft-
 * ware support for all future Serial Flash device families.
 *
 */
void flash2_get_sfdp_params( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                         uint32_t data_count );

/**
 * @brief  Flash 2 Quad Device Manufacturer 
 *
 * @param ctx             Click object.
 * @description The Read Quad J-ID Read instruction identifies the
 * device as SST26VF064B/064BA and manufacturer as
 * Microchip.
 *
 * @returns - Device Manufacturer
 *
 *
 */
uint8_t flash2_quad_device_manufac( flash2_t *ctx );

/**
 * @brief  Flash 2 Quad Device Type 
 *
 * @param ctx             Click object.
 * @description The Read Quad J-ID Read instruction identifies the
 * device as SST26VF064B/064BA and manufacturer as
 * Microchip.
 *
 * @returns - Device Type
 *
 *
 */
uint8_t flash2_quad_device_type( flash2_t *ctx );

/**
 * @brief  Flash 2 Quad Device ID 
 *
 * @param ctx             Click object.
 * @description The Read Quad J-ID Read instruction identifies the
 * device as SST26VF064B/064BA and manufacturer as
 * Microchip.
 *
 * @returns - Device ID
 *
 *
 */
uint8_t flash2_quad_device_id( flash2_t *ctx  );

/**
 * @brief  Flash 2 Device Manufacturer 
 *
 * @param ctx             Click object.
 * @description Using traditional SPI protocol, the JEDEC-ID Read
 * instruction identifies the device as SST26VF064B/
 * 064BA and the manufacturer as Microchip®.
 *
 * @returns - Device Manufacturer
 *
 *
 */
uint8_t flash2_device_manufac( flash2_t *ctx );

/**
 * @brief  Flash 2 Device Type 
 *
 * @param ctx             Click object.
 * @description Using traditional SPI protocol, the JEDEC-ID Read
 * instruction identifies the device as SST26VF064B/
 * 064BA and the manufacturer as Microchip®.
 *
 * @returns - Device Type
 *
 *
 */
uint8_t flash2_device_type( flash2_t *ctx );

/**
 * @brief  Flash 2 Device ID 
 *
 * @param ctx             Click object.
 * @description Using traditional SPI protocol, the JEDEC-ID Read
 * instruction identifies the device as SST26VF064B/
 * 064BA and the manufacturer as Microchip®.
 *
 * @returns - Device ID
 *
 *
 */
uint8_t flash2_device_id( flash2_t *ctx );

/**
 * @brief  Flash 2 Reset 
 *
 * @param ctx             Click object.
 * @description The Reset operation is used as a system (software)
 * reset that puts the device in normal operating Ready
 * mode. This operation consists of two commands:
 * Reset-Enable (RSTEN) followed by Reset (RST).
 *
 */
void flash2_reset( flash2_t *ctx );

/**
 * @brief  Flash 2 Write Status Register 
 *
 * @param ctx             Click object.
 * @description The Write-Status Register (WRSR) command writes
 * new values to the Configuration register.
 *
 * @param s_reg - New Conifuration Register Values
 */
void flash2_write_status_reg( flash2_t *ctx, uint8_t s_reg );

/**
 * @brief  Flash 2 Get Config Register 
 *
 * @param ctx             Click object.
 * @description The Read-Configuration Register command outputs the contents
 * of the Configuration register.
 *
 * @returns Contents of Configuration Register
 *
 */
uint8_t flash2_get_config_reg( flash2_t *ctx );

/**
 * @brief  Flash 2 Write Enable 
 *
 * @param ctx             Click object.
 * @description The Write Enable (WREN) instruction sets the Write-
 * Enable-Latch bit in the Status register to ‘1,’ allowing
 * Write operations to occur.
 *
 */
void flash2_write_enable( flash2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FLASH2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

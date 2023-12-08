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
 * @file sqiflash.h
 * @brief This file contains API for SQI FLASH Click Driver.
 */

#ifndef SQIFLASH_H
#define SQIFLASH_H

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
 * @addtogroup sqiflash SQI FLASH Click Driver
 * @brief API for configuring and manipulating SQI FLASH Click driver.
 * @{
 */

/**
 * @defgroup sqiflash_set SQI FLASH Registers Settings
 * @brief Settings for registers of SQI FLASH Click driver.
 */

/**
 * @addtogroup sqiflash_set
 * @{
 */

/**
 * @brief SQI FLASH description setting.
 * @details Specified setting for description of SQI FLASH Click driver.
 */
#define SQIFLASH_STATUS_WEL             0x02 
#define SQIFLASH_STATUS_WSE             0x04 
#define SQIFLASH_STATUS_WSP             0x08 
#define SQIFLASH_STATUS_WPLD            0x10 
#define SQIFLASH_STATUS_SEC             0x20 
#define SQIFLASH_STATUS_RES             0x40  
#define SQIFLASH_STATUS_BUSY            0x80
#define SQIFLASH_CFG_RES                0x01 
#define SQIFLASH_CFG_IOC                0x02 
#define SQIFLASH_CFG_BPNV               0x08 
#define SQIFLASH_CFG_WPEN               0x80 

/**
 * @brief SQI FLASH Instructions.
 * @details Specified instructions for description of SQI FLASH Click driver.
 */
#define SQIFLASH_INSTR_NOP              0x00 
#define SQIFLASH_INSTR_RSTEN            0x66 
#define SQIFLASH_INSTR_RST              0x99 
#define SQIFLASH_INSTR_EQIO             0x38 
#define SQIFLASH_INSTR_RSTQIO           0xFF 
#define SQIFLASH_INSTR_RDSR             0x05 
#define SQIFLASH_INSTR_WRSR             0x01 
#define SQIFLASH_INSTR_RDCR             0x35 
#define SQIFLASH_INSTR_READ             0x03 
#define SQIFLASH_INSTR_HS_READ          0x0B 
#define SQIFLASH_INSTR_SQOR             0x6B 
#define SQIFLASH_INSTR_SQIOR            0xEB 
#define SQIFLASH_INSTR_SDOR             0x3B 
#define SQIFLASH_INSTR_SDIOR            0xBB 
#define SQIFLASH_INSTR_SB               0xC0 
#define SQIFLASH_INSTR_RBSQI            0x0C 
#define SQIFLASH_INSTR_RBSPI            0xEC 
#define SQIFLASH_INSTR_JEDECID          0x9F 
#define SQIFLASH_INSTR_QUAD_JID         0xAF 
#define SQIFLASH_INSTR_SFDP             0x5A 
#define SQIFLASH_INSTR_WREN             0x06 
#define SQIFLASH_INSTR_WRDI             0x04 
#define SQIFLASH_INSTR_SE               0x20 
#define SQIFLASH_INSTR_BE               0xD8 
#define SQIFLASH_INSTR_CE               0xC7 
#define SQIFLASH_INSTR_PP               0x02 
#define SQIFLASH_INSTR_SPI_QUAD         0x32 
#define SQIFLASH_INSTR_WRSU             0xB0 
#define SQIFLASH_INSTR_WRRE             0x30 
#define SQIFLASH_INSTR_RBPR             0x72 
#define SQIFLASH_INSTR_WBPR             0x42 
#define SQIFLASH_INSTR_LBPR             0x8D 
#define SQIFLASH_INSTR_NVWLDR           0xE8 
#define SQIFLASH_INSTR_ULBPR            0x98 
#define SQIFLASH_INSTR_RSID             0x88 
#define SQIFLASH_INSTR_PSID             0xA5 
#define SQIFLASH_INSTR_LSID             0x85 
#define SQIFLASH_START_PAGE_ADDRESS     0x010000ul
#define SQIFLASH_END_PAGE_ADDRESS       0x7FFFFFul
#define SQIFLASH_FLASH_PAGE_SIZE        256

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b sqiflash_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SQIFLASH_SET_DATA_SAMPLE_EDGE   SET_SPI_DATA_SAMPLE_EDGE
#define SQIFLASH_SET_DATA_SAMPLE_MIDDLE SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // sqiflash_set

/**
 * @defgroup sqiflash_map SQI FLASH MikroBUS Map
 * @brief MikroBUS pin mapping of SQI FLASH Click driver.
 */

/**
 * @addtogroup sqiflash_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SQI FLASH Click to the selected MikroBUS.
 */
#define SQIFLASH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sq3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sq2 = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // sqiflash_map
/*! @} */ // sqiflash

/**
 * @brief SQI FLASH Click context object.
 * @details Context object definition of SQI FLASH Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sq3;                                  /**< Hold. */
    digital_out_t sq2;                                  /**< Write Protect. */

    // Modules
    spi_master_t  spi;                                  /**< SPI driver object. */

    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */

} sqiflash_t;

/**
 * @brief SQI FLASH Click configuration object.
 * @details Configuration object definition of SQI FLASH Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  sq3;                                    /**< Hold . */
    pin_name_t  sq2;                                    /**< Write Protect. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} sqiflash_cfg_t;

/**
 * @brief SQI FLASH Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SQIFLASH_OK = 0,
    SQIFLASH_ERROR = -1

} sqiflash_return_value_t;

/*!
 * @addtogroup sqiflash SQI FLASH Click Driver
 * @brief API for configuring and manipulating SQI FLASH Click driver.
 * @{
 */

/**
 * @brief SQI FLASH configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #sqiflash_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void sqiflash_cfg_setup ( sqiflash_cfg_t *cfg );

/**
 * @brief SQI FLASH initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #sqiflash_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t sqiflash_init ( sqiflash_t *ctx, sqiflash_cfg_t *cfg );

/**
 * @brief SQI FLASH data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t sqiflash_generic_write ( sqiflash_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SQI FLASH data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t sqiflash_generic_read ( sqiflash_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SQI FLASH Busy. 
 * @details Checks if click is busy reading/writing.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return 0 - Success, else - failure.
 *
 * @note Used to check when click is ready to be written to / read from.
 */
uint8_t sqiflash_busy ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Get Status Register. 
 * @details The Read-Status Register command outputs the contents
 * of the Status register.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Status register.
 */
uint8_t sqiflash_get_status_reg ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Erase Status.
 * @details Checks if click erase is suspended.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return 0-erase not suspended, 1-erase suspended.
 */
uint8_t sqiflash_erase_status ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Write Status.
 * @details Checks if click write is suspended.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return @li @c 0 - Write not suspended
 *          @li @c 1 - Write suspended
 */
uint8_t sqiflash_write_status ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Program Status.
 * @details Checks if click write-program is suspended.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return @li @c 0 - Write program not suspended.
 *          @li @c 1 - Write program suspended.
 */
uint8_t sqiflash_program_status ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Protect Status.
 * @details Checks if click write-protect lock-down is suspended.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return @li @c 0 - write-protect not suspended
 *          @li @c 1 - write protect suspended
 */
uint8_t sqiflash_protect_status ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Lock Security Status.
 * @details The Lockout Security ID instruction prevents any future
 * changes to the Security ID, and is supported in both
 * SPI and SQI modes. 
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_lock_security_id ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Security Status.
 * @details Checks if click security ID is locked.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return @li @c 0 - Security ID not locked.
 *          @li @c 1 - Security ID locked.
 */
uint8_t sqiflash_security_status ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Write Protect Enable .
 * @details Enables Write Protect on SQI FLASH Click.
 * @param[out] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_write_protect_enable ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Write Protect Disable. 
 * @details Disables Write Protect on SQI FLASH Click.
 * @param[out] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_write_protect_disable ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Hold Enable.
 * @details Enables Hold on SQI FLASH Click.
 * @param[out] ctx Click object.
 * @return Nothing.
 */
void sqiflash_hold_enable ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Hold Disable.
 * @details Enables Hold on SQI FLASH Click.
 * @param[out] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_hold_disable ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Write Suspend.
 * @details Write-Suspend allows the interruption of Sector-Erase,
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
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_write_suspend ( sqiflash_t *ctx );


/**
 * @brief SQI FLASH Write Resume.
 * @details Write-Suspend allows the interruption of Sector-Erase,
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
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_write_resume ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Get Security ID SPI.
 * @details Reads the Unique ID Pre-Programmed at factory.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[out] buffer : Buffer to read data into.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_spi_get_security_id ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Get Security ID SQI. 
 * @details Reads the Unique ID Pre-Programmed at factory
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[out] buffer : Buffer to read data into.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_sqi_get_security_id ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Set Security ID. 
 * @details The Program Security ID instruction programs one to
 * 2040 Bytes of data in the user-programmable, Security
 * ID space. This Security ID space is one-time program-
 * mable (OTP). The device ignores a Program Security
 * ID instruction pointing to an invalid or protected
 * address
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] buffer : Buffer to write into.
 * @param[in] data_count : Amount of bytes to write.
 * @return Nothing.
 */
void sqiflash_set_security_id ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Write Disable. 
 * @details The Write Disable instruction sets the Write-
 * Enable-Latch bit in the Status register to ‘0,’ not allowing
 * Write operations to occur.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_write_disable ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Get Block Protection Register SPI. 
 * @details The Read Block-Protection Register instruction outputs
 * the Block-Protection register data which determines
 * the protection status.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[out] buffer : Buffer to read data into.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_spi_get_bpr ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Get Block Protection Register SQI.
 * @details The Read Block-Protection Register instruction outputs
 * the Block-Protection register data which determines
 * the protection status.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[out] buffer : Buffer to read data into.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_sqi_get_bpr ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Set Block Protection Register. 
 * @details The Write Block-Protection Register command changes
 * the Block-Protection register data to indicate the protection status.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] buffer : Buffer with new BPR register values to write.
 * @return Nothing.
 */
void sqiflash_set_bpr ( sqiflash_t *ctx, uint8_t *buffer );

/**
 * @brief SQI FLASH Lock Block Protection Register. 
 * @details The Lock-Down Block-Protection Register instruction
 * prevents changes to the Block-Protection register
 * during device operation. Lock-Down resets after power
 * cycling; this allows the Block-Protection register to be
 * changed.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_lock_bpr ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Non-Volatile Write-Lock. 
 * @details The Non-Volatile Write-Lock Lock-Down Register
 * (nVWLDR) instruction controls the ability to change the
 * Write-Lock bits in the Block-Protection register.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] buffer : Buffer with new values for BPR register.
 * @return Nothing.
 */
void sqiflash_nonvolatile_write_lock ( sqiflash_t *ctx, uint8_t *buffer );

/**
 * @brief SQI FLASH Global Block Unlock.
 * @details The Global Block-Protection Unlock instruction clears all
 * write-protection bits in the Block-Protection register,
 * except for those bits that have been locked down with the
 * nVWLDR command.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_global_block_unlock ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Read. 
 * @details The Read instruction, 03H, is supported in SPI bus pro-
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
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_read_generic ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH High Speed Read. 
 * @details The High-Speed Read instruction, 0BH, is supported in
 * both SPI bus protocol and SQI protocol. This instruction
 * supports frequencies of up to 104 MHz from 2.7-3.6V
 * and up to 80 MHz from 2.3-3.6V.On power-up, the
 * device is set to use SPI.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_highspeed_r_read ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Quad Write.
 * @details The SPI Quad Page-Program instruction programs up
 * to 256 Bytes of data in the memory. The data for the
 * selected page address must be in the erased state
 * (FFH) before initiating the SPI Quad Page-Program
 * operation. A SPI Quad Page-Program applied to a pro-
 * tected memory area will be ignored. SST26VF064B
 * requires the ICO bit in the configuration register to be
 * set to ‘1’ prior to executing the command.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start write at.
 * @param[in] buffer : Buffer with data to write.
 * @param[in] data_count : Amount of bytes to write.
 * @return Nothing.
 */
void sqiflash_quad_write ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Write.
 * @details The Page-Program instruction programs up to 256
 * Bytes of data in the memory, and supports both SPI
 * and SQI protocols. The data for the selected page
 * address must be in the erased state (FFH) before initi-
 * ating the Page-Program operation. A Page-Program
 * applied to a protected memory area will be ignored.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start write at.
 * @param[in] buffer : Buffer with data to write.
 * @param[in] data_count : Amount of bytes to write.
 * @return Nothing.
 */
void sqiflash_write_generic ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Quad Enable. 
 * @details The Enable Quad I/O (EQIO) instruction, 38H, enables
 * the flash device for SQI bus operation. Upon comple-
 * tion of the instruction, all instructions thereafter are
 * expected to be 4-bit multiplexed input/output (SQI
 * mode) until a power cycle or a “Reset Quad I/O instruc-
 * tion” is executed.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_quad_enable ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Quad Output Read.
 * @details The SPI Quad-Output Read instruction supports fre-
 * quencies of up to 104 MHz from 2.7-3.6V and up to 80
 * MHz from 2.3-3.6V. SST26VF064B requires the IOC bit
 * in the configuration register to be set to ‘1’ prior to exe-
 * cuting the command.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_quad_out_read ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Quad I/O Read.
 * @details The SPI Quad I/O Read (SQIOR) instruction supports
 * frequencies of up to 104 MHz from 2.7-3.6V and up to
 * 80 MHz from 2.3-3.6V. SST26VF064B requires the
 * IOC bit in the configuration register to be set to ‘1’ prior
 * to executing the command.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @param[in] mode : Mode to put Quad I/O in.
 * @return Nothing.
 */
void sqiflash_quad_io_read ( sqiflash_t *ctx, uint32_t address, uint8_t mode, 
                             uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Quad Reset. 
 * @details The Reset Quad I/O instruction, FFH, resets the device
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
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_quad_reset ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Set Burst. 
 * @details The Set Burst command specifies the number of bytes
 * to be output during a Read Burst command before the
 * device wraps around. It supports both SPI and SQI pro-
 * tocols.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] length : Number of data to be read.
 * @return Nothing.
 *
 * @note - length = 0x00 = 8 bytes
 *       - length = 0x01 = 16 bytes
 *       - length = 0x02 = 32 bytes
 *       - length - 0x03 = 64 bytes
 */
void sqiflash_set_burst ( sqiflash_t *ctx, uint8_t length );

/**
 * @brief SQI FLASH Read Burst with Wrap through SQI.
 * @details During RBSQI, the internal address pointer automati-
 * cally increments until the last byte of the burst is
 * reached, then it wraps around to the first byte of the
 * burst. For example, if the burst length is eight Bytes,
 * and the start address is 06h, the burst sequence would be:
 * 06h, 07h, 00h, 01h, 02h, 03h, 04h, 05h, 06h, etc. The pattern
 * repeats until the command is terminated by a low-to-high
 * transition on CE#.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 * 
 * @note During this operation, blocks that are Read-locked will
 * output data 00H.
 * 
 * 8 Bytes 00-07H, 08-0FH, 10-17H, 18-1FH...
 * 16 Bytes 00-0FH, 10-1FH, 20-2FH, 30-3FH...
 * 32 Bytes 00-1FH, 20-3FH, 40-5FH, 60-7FH...
 * 64 Bytes 00-3FH, 40-7FH, 80-BFH, C0-FFH
 */
void sqiflash_read_sqi_burst_wrap ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Read Burst with Wrap through SPI. 
 * @details During RBSPI, the internal address pointer automati-
 * cally increments until the last byte of the burst is
 * reached, then it wraps around to the first byte of the
 * burst. For example, if the burst length is eight Bytes,
 * and the start address is 06h, the burst sequence would be:
 * 06h, 07h, 00h, 01h, 02h, 03h, 04h, 05h, 06h, etc. The pattern
 * repeats until the command is terminated by a low-to-high
 * transition on CE#.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 * 
 * @note During this operation, blocks that are Read-locked will
 * output data 00H.
 *
 * 8 Bytes 00-07H, 08-0FH, 10-17H, 18-1FH...
 * 16 Bytes 00-0FH, 10-1FH, 20-2FH, 30-3FH...
 * 32 Bytes 00-1FH, 20-3FH, 40-5FH, 60-7FH...
 * 64 Bytes 00-3FH, 40-7FH, 80-BFH, C0-FFH
 */
void sqiflash_read_spi_burst_wrap ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Read Dual Output. 
 * @details  The SPI Dual-Output Read instruction supports fre-
 * quencies of up to 104 MHz from 2.7-3.6V and up to 80
 * MHz from 2.3-3.6V.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_read_dual_output ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Read Dual I/O. 
 * @details Following the Set Mode configuration bits, the
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
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read to.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 *
 * @note Mode Selection must be implemented
 */
void sqiflash_read_dual_io ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Sector Erase.
 * @details The Sector-Erase instruction clears all bits in the
 * selected 4 KByte sector to ‘1,’ but it does not change a
 * protected memory area.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start sector erase from.
 * @return Nothing.
 */
void sqiflash_sector_erase ( sqiflash_t *ctx, uint32_t address );

/**
 * @brief SQI FLASH Block Erase. 
 * @details The Block-Erase instruction clears all bits in the
 * selected block to ‘1’. Block sizes can be 8 KByte, 32
 * KByte or 64 KByte depending on address.
 * A Block-Erase instruction applied to a protected memory
 * area will be ignored.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start block erase from.
 * @return Nothing.
 */
void sqiflash_block_erase ( sqiflash_t *ctx, uint32_t address );

/**
 * @brief SQI FLASH Chip Erase.
 * @details The Chip-Erase instruction clears all bits in the device
 * to ‘1.’ The Chip-Erase instruction is ignored if any of the
 * memory area is protected.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_chip_erase ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH get Serial Flash Discoverable.
 * @details The Serial Flash Discoverable Parameters (SFDP)
 * contain information describing the characteristics of the
 * device. This allows device-independent, JEDEC ID-
 * independent, and forward/backward compatible soft-
 * ware support for all future Serial Flash device families.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] address : Address to start reading from.
 * @param[out] buffer : Buffer to read data into.
 * @param[in] data_count : Amount of bytes to read.
 * @return Nothing.
 */
void sqiflash_get_sfdp_params ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );

/**
 * @brief SQI FLASH Quad Device Manufacturer. 
 * @details The Read Quad J-ID Read instruction identifies the
 * device as SST26VF064B/064BA and manufacturer as
 * Microchip.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Device Manufacturer
 */
uint8_t sqiflash_quad_device_manufac ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Quad Device Type. 
 * @details The Read Quad J-ID Read instruction identifies the
 * device as SST26VF064B/064BA and manufacturer as
 * Microchip.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Device Type
 */
uint8_t sqiflash_quad_device_type ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Quad Device ID. 
 * @details The Read Quad J-ID Read instruction identifies the
 * device as SST26VF064B/064BA and manufacturer as
 * Microchip.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Device ID
 */
uint8_t sqiflash_quad_device_id ( sqiflash_t *ctx  );

/**
 * @brief SQI FLASH Device Manufacturer. 
 * @details Using traditional SPI protocol, the JEDEC-ID Read
 * instruction identifies the device as SST26VF064B/
 * 064BA and the manufacturer as Microchip®.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Device Manufacturer
 */
uint8_t sqiflash_device_manufac ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Device Type. 
 * @details Using traditional SPI protocol, the JEDEC-ID Read
 * instruction identifies the device as SST26VF064B/
 * 064BA and the manufacturer as Microchip®.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Device Type
 */
uint8_t sqiflash_device_type ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Device ID.
 * @details Using traditional SPI protocol, the JEDEC-ID Read
 * instruction identifies the device as SST26VF064B/
 * 064BA and the manufacturer as Microchip®.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Device ID
 */
uint8_t sqiflash_device_id ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Reset.
 * @details The Reset operation is used as a system (software)
 * reset that puts the device in normal operating Ready
 * mode. This operation consists of two commands:
 * Reset-Enable (RSTEN) followed by Reset (RST).
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_reset ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Write Status Register 
 * @details The Write-Status Register (WRSR) command writes
 * new values to the Configuration register.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @param[in] s_reg : New Conifuration Register Values
 * @return Nothing.
 */
void sqiflash_write_status_reg ( sqiflash_t *ctx, uint8_t s_reg );

/**
 * @brief SQI FLASH Get Config Register 
 * @details The Read-Configuration Register command outputs the contents
 * of the Configuration register.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Contents of Configuration Register
 */
uint8_t sqiflash_get_config_reg ( sqiflash_t *ctx );

/**
 * @brief SQI FLASH Write Enable 
 * @details The Write Enable (WREN) instruction sets the Write-
 * Enable-Latch bit in the Status register to ‘1,’ allowing
 * Write operations to occur.
 * @param[in] ctx : Click context object.
 * See #sqiflash_t object definition for detailed explanation.
 * @return Nothing.
 */
void sqiflash_write_enable ( sqiflash_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SQIFLASH_H

/*! @} */ // sqiflash

// ------------------------------------------------------------------------ END

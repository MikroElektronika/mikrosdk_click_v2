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
 * \file flash.h
 *
 * \brief This file contains API for Flash Click driver.
 *
 * \addtogroup flash Flash Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _FLASH_H_
#define _FLASH_H_

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
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup mem_org Memory Organization
 * \{
 */
#define FLASH_MEM_ADDR_FIRST_PAGE_START    0x0
#define FLASH_MEM_ADDR_FIRST_PAGE_END      0xFF
#define FLASH_MEM_ADDR_SECOND_PAGE_START   0x100
#define FLASH_MEM_ADDR_SECOND_PAGE_END     0x1FF
#define FLASH_MEM_ADDR_LAST_PAGE_START     0xFFF00
#define FLASH_MEM_ADDR_LAST_PAGE_END       0xFFFFF
#define FLASH_MEM_ADDR_FIRST_SECTOR_START  0x0
#define FLASH_MEM_ADDR_FIRST_SECTOR_END    0xFFF
#define FLASH_MEM_ADDR_LAST_SECTOR_START   0xFF000
#define FLASH_MEM_ADDR_LAST_SECTOR_END     0xFFFFF
#define FLASH_MEM_ADDR_FIRST_BLOCK_START   0x0
#define FLASH_MEM_ADDR_FIRST_BLOCK_END     0xFFFF
#define FLASH_MEM_ADDR_LAST_BLOCK_START    0xF0000
#define FLASH_MEM_ADDR_LAST_BLOCK_END      0xFFFFF
/** \} */

/**
 * \defgroup ndata_lim Data Transfer Limits
 * \{
 */
#define FLASH_NDATA_TRANSFER_MIN  1
#define FLASH_NDATA_TRANSFER_MAX  256
/** \} */

/**
 * \defgroup status Status Register
 * \{
 */

/**
 * \defgroup flag_mask Flag Mask
 * \{
 */
#define FLASH_STATUS_MASK_WRITE_BUSY      0x1
#define FLASH_STATUS_MASK_WRITE_EN        0x2
#define FLASH_STATUS_MASK_BLOCK_PROTECT   0x3C
#define FLASH_STATUS_MASK_WP_DIS          0x40
#define FLASH_STATUS_MASK_OTP_LOCK        0x80
/** \} */

/**
 * \defgroup settings Settings
 * \{
 */
#define FLASH_STATUS_SET_BLOCK_PROT_BIT0  0x4
#define FLASH_STATUS_SET_BLOCK_PROT_BIT1  0x8
#define FLASH_STATUS_SET_BLOCK_PROT_BIT2  0x10
#define FLASH_STATUS_SET_BLOCK_PROT_BIT3  0x20
#define FLASH_STATUS_SET_WP_DIS           0x40
#define FLASH_STATUS_SET_OTP_LOCK         0x80
/** \} */

/** \} */ //  End status group

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define FLASH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sdi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS   ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_RST  ); \
    cfg.wp  = MIKROBUS( mikrobus, MIKROBUS_PWM  )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click error code definition.
 */
typedef enum
{
    FLASH_OK = 0x0,
    FLASH_ERR_INIT_DRV = 0xFD,
    FLASH_ERR_MEM_ADDR,
    FLASH_ERR_NDATA

} flash_err_t;

/**
 * @brief Click pin states.
 */
typedef enum
{
    FLASH_PIN_STATE_LOW = 0,
    FLASH_PIN_STATE_HIGH

} flash_pin_state_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;

    //  Control pins.
    digital_out_t  hld;
    digital_out_t  wp;

    //  Module.
    spi_master_t spi;
    pin_name_t chip_select;

} flash_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  sdo;
    pin_name_t  sdi;
    pin_name_t  sck;
    pin_name_t  cs;

    //  Additional gpio pins.
    pin_name_t  hld;
    pin_name_t  wp;

    //  SPI configuration.
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} flash_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void flash_cfg_setup( flash_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok,
 *          0xFD - Driver init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this Click.
 */
flash_err_t flash_init( flash_t *ctx, flash_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Flash Click.
 */
void flash_default_cfg( flash_t *ctx );

/**
 * @brief Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used as a system (software) reset that puts
 * the device in normal operating Ready mode.
 * @note This function will make a delay of 1 second.
 */
void flash_reset( flash_t *ctx );

/**
 * @brief Write Enable function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the Write Enable Latch to allow user to
 * execute memory programming, status register writing and chip/sector erasing.
 */
void flash_write_enable( flash_t *ctx );

/**
 * @brief Write Disable function.
 *
 * @param ctx  Click object.
 *
 * @description This function will reset the Write Enable Latch to protect the
 * memory programming, status register writing and chip/sector erasing.
 * @note This function also can be used to exit from OTP mode to normal mode.
 */
void flash_write_disable( flash_t *ctx );

/**
 * @brief Status Write function.
 *
 * @param ctx  Click object.
 * @param data_tx  Data to be written.
 *
 * @description This function writes one byte to Status register.
 * @note Write Enable Latch will be set automatically and reset after cycle was
 * done.
 */
void flash_write_status( flash_t *ctx, uint8_t data_tx );

/**
 * @brief Status Read function.
 *
 * @param ctx  Click object.
 *
 * @returns Status byte.
 *
 * @description This function reads Status register.
 */
uint8_t flash_read_status( flash_t *ctx );

/**
 * @brief ID Read function.
 *
 * @param ctx  Click object.
 * @param manufact_id  Manufacturer identification.
 * @param dev_id  Device identification.
 *
 * @description This function reads one byte of manufacturer identification and
 * two bytes of device identification.
 */
void flash_read_id( flash_t *ctx, uint8_t *manufact_id, uint16_t *dev_id );

/**
 * @brief Byte Write function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 * @param data_tx  Data to be written.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address.
 *
 * @description This function writes one byte data to the selected memory
 * address.
 * @note Write Enable Latch will be set automatically and reset after cycle was
 *       done.
 */
flash_err_t flash_write_byte( flash_t *ctx, uint32_t mem_addr, uint8_t data_tx );

/**
 * @brief Byte Read function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 * @param data_rx  Data which was read.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address.
 *
 * @description This function reads one byte data from the selected memory
 * address.
 */
flash_err_t flash_read_byte( flash_t *ctx, uint32_t mem_addr, uint8_t *data_rx );

/**
 * @brief Page Write function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 * @param data_tx  Data to be written.
 * @param n_data  Number of bytes to be written.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address,
 *          0xFF - Number of data bytes is out of range.
 *
 * @description This function allows memory to be programmed up to 256 bytes,
 * starting from the selected memory address.
 * @note Write Enable Latch will be set automatically and reset after cycle was
 *       done.
 */
flash_err_t flash_write_page( flash_t *ctx, uint32_t mem_addr, uint8_t *data_tx,
                  uint16_t n_data );

/**
 * @brief Page Read function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 * @param data_rx  Data which was read.
 * @param n_data  Number of bytes to be read.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address,
 *          0xFF - Number of data bytes is out of range.
 *
 * @description This function allows memory to be read up to 256 bytes,
 * starting from the selected memory address.
 */
flash_err_t flash_read_page( flash_t *ctx, uint32_t mem_addr, uint8_t *data_rx,
                 uint16_t n_data );

/**
 * @brief Chip Erase function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets all bits to 1 (FFh).
 * @note Write Enable Latch will be set automatically and reset after cycle was
 *       done.
 */
void flash_erase_chip( flash_t *ctx );

/**
 * @brief Block Erase function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address.
 *
 * @description This function sets to 1 (FFh) all bits inside the chosen block.
 * @note Write Enable Latch will be set automatically and reset after cycle was
 *       done.
 */
flash_err_t flash_erase_block( flash_t *ctx, uint32_t mem_addr );

/**
 * @brief Half Block Erase function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address.
 *
 * @description This function sets to 1 (FFh) all bits inside the chosen block
 * of memory.
 * @note Write Enable Latch will be set automatically and reset after cycle was
 *       done.
 */
flash_err_t flash_erase_half_block( flash_t *ctx, uint32_t mem_addr );

/**
 * @brief Sector Erase function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address.
 *
 * @description This function sets to 1 (FFh) all bits inside the chosen sector.
 * @note Write Enable Latch will be set automatically and reset after cycle was
 *       done.
 */
flash_err_t flash_erase_sector( flash_t *ctx, uint32_t mem_addr );

/**
 * @brief WP Pin Set function.
 *
 * @param ctx  Click object.
 * @param state  The desired pin state to be set. (active low)
 *
 * @description This function sets the WP pin to the desired state.
 */
void flash_set_write_protect_pin( flash_t *ctx, flash_pin_state_t state );

/**
 * @brief HLD Pin Set function.
 *
 * @param ctx  Click object.
 * @param state  The desired pin state to be set. (active low)
 *
 * @description This function sets the HLD pin to the desired state.
 */
void flash_set_hold_pin( flash_t *ctx, flash_pin_state_t state );

#ifdef __cplusplus
}
#endif
#endif  //  _FLASH_H_

/** \} */ //  End public_function group
/// \}    //  End flash group
/*! @} */
// ------------------------------------------------------------------------ END

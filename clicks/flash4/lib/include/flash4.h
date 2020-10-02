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
 * \brief This file contains API for Flash 4 Click driver.
 *
 * \addtogroup flash4 Flash 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FLASH4_H
#define FLASH4_H

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

#define FLASH4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.io2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.io3 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FLASH4_RETVAL  uint8_t

#define FLASH4_OK           0x00
#define FLASH4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup id     Id
 */
#define FLASH4_MANUFACTURER_ID  0x01
#define FLASH4_DEVICE_ID        0x19
/** \} */

/**
 * \defgroup commands   Commands
 */
#define FLASH4_CMD_READ_ID                       0x90
#define FLASH4_CMD_READ_IDENTIFICATION           0x9F
#define FLASH4_CMD_READ_ELECTRONIC_SIGNATURE     0xAB
#define FLASH4_CMD_READ_SERIAL_FLASH_PARAMETERS  0x5A
#define FLASH4_CMD_READ_STATUS_REG_1             0x05
#define FLASH4_CMD_READ_STATUS_REG_2             0x07
#define FLASH4_CMD_READ_CONFIGURATION_REG        0x35
#define FLASH4_CMD_READ_BANK_REG                 0x16
#define FLASH4_CMD_WRITE_BANK_REG                0x17
#define FLASH4_CMD_ACCESS_BANK_REG               0xB9
#define FLASH4_CMD_WRITE_REGISTER_WRR            0x01
#define FLASH4_CMD_WRITE_ENABLE_WREN             0x06
#define FLASH4_CMD_WRITE_DISABLE_WRDI            0x04
#define FLASH4_CMD_CLEAR_STATUS_REG              0x30
#define FLASH4_CMD_READ_ECC_STATUS_REG           0x18
#define FLASH4_CMD_READ_AUTO_BOOT_REG            0x14
#define FLASH4_CMD_WRITE_AUTO_BOOT_REG           0x15
#define FLASH4_CMD_PROGRAM_NVDLR                 0x43
#define FLASH4_CMD_WRITE_VDLR                    0x4A
#define FLASH4_CMD_READ_DATA_LEARNING_PATTERN    0x41
#define FLASH4_CMD_READ_FLASH                    0x03
#define FLASH4_CMD_4READ_FLASH                   0x13
#define FLASH4_CMD_FAST_READ_FLASH               0x0B
#define FLASH4_CMD_FAST_4READ_FLASH              0x0C
#define FLASH4_CMD_FAST_READ_DDR                 0x0D
#define FLASH4_CMD_FAST_4READ_DDR                0x0E
#define FLASH4_CMD_PAGE_PROGRAM                  0x02
#define FLASH4_CMD_PAGE_4PROGRAM                 0x12
#define FLASH4_CMD_PROGRAM_SUSPEND               0x85
#define FLASH4_CMD_PROGRAM_RESUME                0x8A
#define FLASH4_CMD_SECTOR_ERASE                  0xD8
#define FLASH4_CMD_SECTOR_4ERASE                 0xDC
#define FLASH4_CMD_BULK_ERASE                    0xC7
#define FLASH4_CMD_ERASE_SUSPEND                 0x75
#define FLASH4_CMD_ERASE_RESUME                  0x7A
#define FLASH4_CMD_WRITE_OTP_PROGRAM             0x42
#define FLASH4_CMD_READ_OTP                      0x4B
#define FLASH4_CMD_READ_ASP                      0x2B
#define FLASH4_CMD_WRITE_ASP_PROGRAM             0x2F
#define FLASH4_CMD_READ_DYB                      0xE0
#define FLASH4_CMD_WRITE_DYB                     0xE1
#define FLASH4_CMD_READ_PPB                      0xE2
#define FLASH4_CMD_WRITE_PPB                     0xE3
#define FLASH4_CMD_ERASE_PPB                     0xE4
#define FLASH4_CMD_READ_PPB_LOCK_BIT             0xA7
#define FLASH4_CMD_WRITE_PPB_LOCK_BIT            0xA6
#define FLASH4_CMD_SOFTWARE_RESET                0xF0
#define FLASH4_CMD_MODE_BIT_RESET                0xFF

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
    digital_in_t io3;

    // Input pins 

    digital_in_t io2;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} flash4_t;

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

    pin_name_t rst;
    pin_name_t io2;
    pin_name_t io3;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} flash4_cfg_t;

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
void flash4_cfg_setup ( flash4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FLASH4_RETVAL flash4_init ( flash4_t *ctx, flash4_cfg_t *cfg );

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
void flash4_generic_transfer ( flash4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Functions for read Manufacturer ID.
 *
 * @param ctx          Click object.
 * @param device_id    [ 0 ] - Manufacturer ID and [ 1 ] - Device ID (hex).
 *
 * @description Read manufacturer id.
 */
void flash4_read_manufacturer_id ( flash4_t *ctx, uint8_t *device_id );

/**
 * @brief Functions for Read Identification.
 *
 * @param ctx          Click object.
 * @param out_data     Data output.
 * @param n_data       Number of data.
 *
 * @description This functions for Read Identification.
 */
void flash4_read_identification ( flash4_t *ctx, uint8_t *out_data, uint8_t n_data );


/**
 * @brief Functions for Read Electronic Signature.
 *
 * @param ctx          Click object.
 *
 * @description This functions for Read Electronic Signature.
 */
uint8_t flash4_read_electronic_id ( flash4_t *ctx );

/**
 * @brief Functions for Read Serial Flash Discoverable Parameters.
 *
 * @param ctx          Click object.
 * @param out_params   Data output.
 * @param n_data       Number of data.
 *
 * @description This functions for Read Serial Flash Discoverable Parameters.
 */
void flash4_read_serial_flash_parameters ( flash4_t *ctx, uint8_t *out_params, uint8_t c );

/**
 * @brief Functions for read byte from register.
 *
 * @param ctx          Click object.
 * @param reg          Register which will be read.
 *
 * @description This functions for read byte from register.
 */
uint8_t flash4_read_byte ( flash4_t *ctx, uint8_t reg );

/**
 * @brief Functions for write one byte in register.
 *
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written.
 * @param data_buff    Data which be written in the register.
 *
 * @description This functions for write one byte in register.
 */
void flash4_write_byte ( flash4_t *ctx, uint8_t reg, uint8_t data_buff );

/**
 * @brief Functions for write command.
 *
 * @param ctx          Click object.
 * @param cmd          Command.
 *
 * @description This functions for write command.
 */
void flash4_write_command ( flash4_t *ctx, uint8_t cmd );

/**
 * @brief Functions for write command.
 *
 * @param ctx          Click object.
 * @param status          Command.
 * @param config          Config.
 *
 * @description This functions for write command.
 */
void flash4_write_reg ( flash4_t *ctx, uint8_t status, uint8_t config );

/**
 * @brief Functions for read ECC Status Register.
 *
 * @param ctx          Click object.
 * @param out_ecc      Data output.
 * @param n_dummy      Number of data(max 200 byte).
 *
 * @description This functions for read ECC Status Register.
 */
void flash4_read_ecc ( flash4_t *ctx, uint8_t *out_ecc, uint8_t n_dummy);

/**
 * @brief Functions for read AutoBoot Register.
 *
 * @param ctx          Click object.
 * @param out_ab       Data output.
 *
 * @description This fFunctions for read AutoBoot Register.
 */
void flash4_read_auto_boot ( flash4_t *ctx, uint8_t *out_ab );

/**
 * @brief Functions for read Flash.
 *
 * @param ctx          Click object.
 * @param out_data     Data output.
 * @param addr         Start address.
 * @param n_data       Number of data.
 *
 * @description This functions for read Flash..
 */
void flash4_read_flash( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data);

/**
 * @brief Functions for read Flash with 4 byte address.
 *
 * @param ctx          Click object.
 * @param out_data     Data output.
 * @param addr         Start address.
 * @param n_data       Number of data.
 *
 * @description This functions for read Flash with 4 byte address.
 */
void flash4_4_read_flash ( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data );

/**
 * @brief Functions for fast read Flash.
 *
 * @param ctx                Click object.
 * @param out_data           Data output.
 * @param addr               Start address.
 * @param n_data_dummy       Number of data.
 *
 * @description This functions for fast read Flash.
 */
void flash4_fast_read_flash ( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data_dummy);

/**
 * @brief Functions for fast read Flash with 4 byte address.
 *
 * @param ctx                Click object.
 * @param out_data           Data output.
 * @param addr               Start address.
 * @param n_data             Number of data.
 *
 * @description This functions for fast read Flash with 4 byte address.
 */
void flash4_4_fast_read_flash ( flash4_t *ctx, uint8_t *out_data,uint8_t addr, uint8_t n_data );

/**
 * @brief Functions for write data in address with 4 byte address.
 *
 * @param ctx                Click object.
 * @param in_data            Data output.
 * @param addr               Start address.
 * @param n_data             Number of data.
 *
 * @description This functions for write data in address with 4 byte address.
 */
void flash4_4_page_program ( flash4_t *ctx, uint8_t *in_data, uint32_t addr, uint8_t n_data );

/**
 * @brief Functions for sector Erase.
 *
 * @param ctx                Click object.
 * @param addr               Start address.
 *
 * @description This functions for sector Erase.
 */
void flash4_sector_erase ( flash4_t *ctx, uint32_t addr );

/**
 * @brief Functions for sector Erase for 4 bytes address.
 *
 * @param ctx                Click object.
 * @param addr               Start address.
 *
 * @description This functions for sector Erase for 4 bytes address.
 */
void flash4_4sector_erase( flash4_t *ctx, uint32_t addr );

/**
 * @brief Functions for wip.
 *
 * @param ctx                Click object.
 *
 * @description This functions for wip.
 */
uint8_t flash4_check_wip ( flash4_t *ctx );

/**
 * @brief Functions for wip.
 *
 * @param ctx                Click object.
 *
 * @description This functions for wip.
 */
uint8_t flash4_check_wel ( flash4_t *ctx );

/**
 * @brief Functions for ps.
 *
 * @param ctx                Click object.
 *
 * @description This functions for ps.
 */
uint8_t flash4_check_ps ( flash4_t *ctx );

/**
 * @brief Functions for es.
 *
 * @param ctx                Click object.
 *
 * @description This functions for es.
 */
uint8_t flash4_check_es ( flash4_t *ctx );

/**
 * @brief Functions for reset.
 *
 * @param ctx                Click object.
 *
 * @description This functions for reset.
 */
void flash4_reset ( flash4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FLASH4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

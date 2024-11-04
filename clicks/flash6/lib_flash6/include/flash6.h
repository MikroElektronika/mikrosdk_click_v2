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
 * \brief This file contains API for Flash 6 Click driver.
 *
 * \addtogroup flash6 Flash 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FLASH6_H
#define FLASH6_H

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

#define FLASH6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FLASH6_RETVAL  uint8_t

#define FLASH6_OK           0x00
#define FLASH6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup commands  Commands
 * \{
 */
#define FLASH6_CMD_WRITE_ENABLE                     0x06
#define FLASH6_CMD_VOL_SR_WRITE_ENABLE              0x50
#define FLASH6_CMD_WRITE_DISABLE                    0x04
#define FLASH6_CMD_RELEASE_POWER_DOWN_ID            0xAB
#define FLASH6_CMD_MANUFACTURER_DEVICE_ID           0x90
#define FLASH6_CMD_JEDEC_ID                         0x9F
#define FLASH6_CMD_UINQUE_ID                        0x4B
#define FLASH6_CMD_READ_DATA                        0x03
#define FLASH6_CMD_FAST_READ_DATA                   0x0B
#define FLASH6_CMD_PAGE_PROGRAM                     0x02
#define FLASH6_CMD_SECTOR_ERASE_4KB                 0x20
#define FLASH6_CMD_BLOCK_ERASE_32KB                 0x52
#define FLASH6_CMD_BLOCK_ERASE_64KB                 0xD8
#define FLASH6_CMD_CHIP_ERASE                       0xC7 //0x60
#define FLASH6_CMD_READ_STATUS_1                    0x05 
#define FLASH6_CMD_WRITE_STATUS_1                   0x01 
#define FLASH6_CMD_READ_STATUS_2                    0x35 
#define FLASH6_CMD_WRITE_STATUS_2                   0x31 
#define FLASH6_CMD_READ_STATUS_3                    0x15 
#define FLASH6_CMD_WRITE_STATUS_3                   0x11
#define FLASH6_CMD_READ_SFDP_REG                    0x5A
#define FLASH6_CMD_ERASE_SECURITY_REG               0x44
#define FLASH6_CMD_PROGRAM_SECURITY_REG             0x42
#define FLASH6_CMD_READ_SECURITY_REG                0x48
#define FLASH6_CMD_GLOBAL_BLOCK_LOCK                0x7E
#define FLASH6_CMD_GLOBAL_BLOCK_UNLOCK              0x98
#define FLASH6_CMD_READ_BLOCK_LOCK                  0x3D
#define FLASH6_CMD_INDIVIDUAL_BLOCK_LOCK            0x36
#define FLASH6_CMD_INDIVIDUAL_BLOCK_UNLOCK          0x39
#define FLASH6_CMD_ERASE_PROGRAM_SUSPEND            0x75
#define FLASH6_CMD_ERASE_PROGRAM_RESUME             0x7A
#define FLASH6_CMD_POWER_DOWN                       0xB9
#define FLASH6_CMD_ENABLE_RESET                     0x66
#define FLASH6_CMD_RESET_DEVICE                     0x99
/** \} */

/**
 * \defgroup device_manufac_id  Device Manufac id
 * \{
 */
#define FLASH6_DEVICE_ID                            0x17
#define FLASH6_MANIFACTURE_ID                       0xEF
/** \} */

/**
 * \defgroup device_status Device status
 * \{
 */
#define FLASH6_DEVICE_OK                            0xFF
#define FLASH6_DEVICE_ERROR                         0xAA
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
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} flash6_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} flash6_cfg_t;

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
void flash6_cfg_setup ( flash6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param flash6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FLASH6_RETVAL flash6_init ( flash6_t *ctx, flash6_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param block        Transfer block structure.
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void flash6_generic_transfer
( 
    flash6_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic funcion for reading
 *
 * @param ctx         Click object.
 * @param reg_addr    Registar of reading buf
 * @param data_buf    Pointer to array of output data
 * @param len         Size of array of output data
 */
void flash6_read_data ( flash6_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic funcion for writing
 *
 * @param ctx         Click object.
 * @param reg_addr    Registar of writing buf
 * @param data_buf    Pointer to array of input data
 * @param len         Size of array of input data
 */
void flash6_write_data ( flash6_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for sending one Byte od data
 *
 * @param cmd_data    Byte to be sent
 */
void flash6_send_cmd ( flash6_t *ctx, uint8_t cmd_data );

/**
 * @brief Funcion for checking manufacture and device id
 *
 * @param ctx              Click object.
 * @param manufacture_id      
 * @param device_id
 * 
 * @return either FLASH5_DEVICE_ERROR or FLASH5_DEVICE_OK.
 */
uint8_t flash6_get_manufacture_device_id ( flash6_t *ctx, uint8_t *manufacture_id, uint8_t *device_id );

/**
 * @brief Function for eraseing segment
 *
 * @param ctx         Click object.
 * @param segment     Segment to be deleted
 * @param page_addr   Address for start erase
 *
 * @note segment can be: - Sector Erase (4KB)
 *                       - Block Erase (32KB)
 *                       - Block Erase (64KB)
 */
void flash6_erase_memory_segment( flash6_t *ctx, uint8_t segment, uint32_t start_addr );

/**
 * @brief Function for reading status register
 *
 * @param ctx           Click object.
 * @param status_cmd    Command status
 *
 */
uint8_t flash6_read_status_reg ( flash6_t *ctx, uint8_t status_cmd );

/**
 * @brief Function for writing status register
 *
 * @param ctx           Click object.
 * @param status_cmd    Command status
 * @param status_data   Input status
 */
void flash6_write_status_reg ( flash6_t *ctx, uint8_t status_cmd, uint8_t status_data );

/**
 * @brief Function used for writing in memory
 *
 * @param ctx            Click object.
 * @param addr           Address from which data will be written
 * @param data_buf       Pointer to input array
 * @param buf_size       Size of iutput array
 */
void flash6_write_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size );

/**
 * @brief Function used for reading from memory
 *
 * @param ctx            Click object.
 * @param addr           Address from which data will be read
 * @param data_buf       Pointer to output array
 * @param buf_size       Size of intput array
 */
void flash6_read_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size );

/**
 * @brief Function for reseting device
 * 
 * @param ctx         Click object.
 */
void flash6_software_reset ( flash6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FLASH6_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

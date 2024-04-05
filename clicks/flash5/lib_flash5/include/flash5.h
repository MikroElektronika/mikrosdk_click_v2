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
 * \brief This file contains API for Flash 5 Click driver.
 *
 * \addtogroup flash5 Flash 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FLASH5_H
#define FLASH5_H

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

#define FLASH5_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.wp    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.hld   = MIKROBUS( mikrobus, MIKROBUS_PWM );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FLASH5_RETVAL  uint8_t

#define FLASH5_OK           0x00
#define FLASH5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup max_size  Max size
 * \{
 */
#define FLASH5_MAX_addr  0xFFFF  
#define FLASH5_PAGESIZE    2048  
/** \} */

/**
 * \defgroup commands  Commands
 * \{
 */
#define FLASH5_CMD_RESET                                 0xFF  
#define FLASH5_CMD_DEVICE_ID                             0x9F  
#define FLASH5_CMD_READ_REG_STATUS1                      0x05  
#define FLASH5_CMD_READ_REG_STATUS2                      0x0F  
#define FLASH5_CMD_WRITE_REG_STATUS1                     0x01  
#define FLASH5_CMD_WRITE_REG_STATUS2                     0x1F  
#define FLASH5_CMD_WRITE_ENABLE                          0x06  
#define FLASH5_CMD_WRITE_DISABLE                         0x04  
#define FLASH5_CMD_BAD_BLOCK_MANAGE                      0xA1  
#define FLASH5_CMD_READ_BBM_TABLE                        0xA5  
#define FLASH5_CMD_LAST_ECC_FAIL_PAGE                    0xA9  
#define FLASH5_CMD_BLOCK_ERASE                           0xD8  
#define FLASH5_CMD_LOAD_DATA                             0x02  
#define FLASH5_CMD__RND_LOAD_DATA                        0x84  
#define FLASH5_CMD_QUAD_LOAD_DATA                        0x32  
#define FLASH5_CMD_QUAD_RND_LOAD_DATA                    0x34  
#define FLASH5_CMD_EXECUTE                               0x10  
#define FLASH5_CMD_PAGE_READ_DATA                        0x13  
#define FLASH5_CMD_READ_DATA                             0x03  
#define FLASH5_CMD_FAST_READ                             0x0B  
#define FLASH5_CMD_FAST_READ_4BYTE_addr                  0x0C  
#define FLASH5_CMD_FAST_READ_DUAL_OUT                    0x3B  
#define FLASH5_CMD_FAST_READ_DUAL_OUT_4BYTE_addr         0x3C  
#define FLASH5_CMD_FAST_READ_QUAD_OUT                    0x6B  
#define FLASH5_CMD_FAST_READ_QUAD_OUT_4BYTE_addr         0x6C  
#define FLASH5_CMD_FAST_READ_DUAL_IO                     0xBB  
#define FLASH5_CMD_FAST_READ_IO_4BYTE_addr               0xBC  
#define FLASH5_CMD_FAST_READ_QUAD_IO                     0xEB  
#define FLASH5_CMD_FAST_READ_QUAD_IO_4BYTE_addr          0xEC  
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define FLASH5_REG_STATUS_1   0xA0  
#define FLASH5_REG_STATUS_2   0xB0  
#define FLASH5_REG_STATUS_3   0xC0  
/** \} */

/**
 * \defgroup status_register_1_command Status register 1 command
 * \{
 */
#define FLASH5_RS1_WRITE_PROTECTION_ENABLE    0x02  
#define FLASH5_RS1_WRITE_PROTECTION_DISABLE   0x00  
#define FLASH5_RS1_SRP1_ENABLE                0x01  
#define FLASH5_RS1_SRP2_ENABLE                0x80  
/** \} */

/**
 * \defgroup status_register_2_command Status register 2 command
 * \{
 */
#define FLASH5_RS2_PAGE_READ_MODE             0x08  
#define FLASH5_RS2_PAGE_CONTINOUS_READ_MODE   0x00  
#define FLASH5_RS2_ECC_ENABLED                0x10  
#define FLASH5_RS2_ECC_DISABLED               0x10  
#define FLASH5_RS2_OTP_LOCK                   0x80  
#define FLASH5_RS2_OTP_ACCESS                 0x40  
#define FLASH5_RS2_REG_STATUS_1_LOCK          0x20  
/** \} */

/**
 * \defgroup device_status  Device status
 * \{
 */
#define FLASH5_DEVICE_OK      0xFF  
#define FLASH5_DEVICE_ERROR   0xAA  
/** \} */

/**
 * \defgroup pin_status  Pin status
 * \{
 */
#define FLASH5_PIN_STATUS_HIGH   1  
#define FLASH5_PIN_STATUS_LOW    0  
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
    digital_out_t wp;
    digital_out_t hld;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} flash5_t;

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

    pin_name_t wp;
    pin_name_t hld;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} flash5_cfg_t;

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
void flash5_cfg_setup ( flash5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FLASH5_RETVAL flash5_init ( flash5_t *ctx, flash5_cfg_t *cfg );

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
void flash5_generic_transfer ( flash5_t *ctx, uint8_t *wr_buf, 
                              uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic funcion for reading
 *
 * @param ctx         Click object.
 * @param reg_addr    Registar of reading buf
 * @param data_buf    Pointer to array of output data
 * @param n_buf_size  Size of array of output data
 */
void flash5_read_data ( flash5_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint16_t n_buf_size );

/**
 * @brief Generic funcion for writing
 *
 * @param ctx         Click object.
 * @param reg_addr    Registar of writing buf
 * @param data_buf    Pointer to array of input data
 * @param n_buf_size  Size of array of input data
 */
void flash5_write_data ( flash5_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint16_t n_buf_size );

/**
 * @brief Function for sending one Byte od data
 *
 * @param ctx         Click object.
 * @param cmd_data    Byte to be sent
 */
void flash5_send_cmd ( flash5_t *ctx, uint8_t cmd_data );

/**
 * @brief Sets wp pin to one state
 *
 * @param ctx       Click object.
 * @param status    Registar of sending target
 * 
 * @return either FLASH5_DEVICE_ERROR or FLASH5_DEVICE_OK.
 */
uint8_t flash5_set_wp_pin ( flash5_t *ctx, uint8_t status );

/**
 * @brief Sets hold pin to one state
 *
 * @param ctx       Click object.
 * @param status    Registar of sending target
 * 
 * @return either FLASH5_DEVICE_ERROR or FLASH5_DEVICE_OK.
 */
uint8_t flash5_set_hold_pin ( flash5_t *ctx, uint8_t status );

/**
 * @brief Funcion for checking device id
 * 
 * @param ctx         Click object.
 * 
 * @return either FLASH5_DEVICE_ERROR or FLASH5_DEVICE_OK.
 */
uint8_t flash5_device_id_check ( flash5_t *ctx );

/**
 * @brief Function for setting page read
 *
 * @param ctx         Click object.
 * @param page_num    Address of page
 */
void flash5_page_read ( flash5_t *ctx, uint16_t page_num );

/**
 * @brief Function for executing page load
 *
 * @param ctx         Click object.
 * @param page_num    Address of page
 */
void flash5_execute_load ( flash5_t *ctx, uint16_t page_num );

/**
 * @brief Function for reading one page
 *
 * @param ctx            Click object.
 * @param column_addr    Address from which data will be read
 * @param data_buf       Pointer to output array
 * @param buf_size       Size of iutput array
 */
void flash5_page_read_memory ( flash5_t *ctx, uint16_t column_addr, uint8_t *data_buf, uint16_t buf_size );

/**
 * @brief Function for continous reading
 * 
 * @param ctx            Click object.
 * @param data_buf       Pointer to output array
 * @param buf_size       Size of iutput array
 * 
 * @note When you do continous reading you should set execute load and page read
 */
void flash5_continous_read_memory ( flash5_t *ctx, uint8_t *data_buf, uint16_t buf_size );

/**
 * @brief Function for loading one page
 *
 * @param ctx            Click object.
 * @param column_addr    Address from which data will be written
 * @param data_buf       Pointer to input array
 * @param buf_size       Size of iutput array
 */
void flash5_page_load_memory ( flash5_t *ctx, uint16_t column_addr, uint8_t *data_buf, uint16_t buf_size );

/**
 * @brief Function for reading status data
 *
 * @param ctx           Click object.
 * @param status_cmd    Command status
 * @param status_addr   Address of status
 * 
 * @return status of status_addr you inputed.
 */
uint8_t flash5_read_status_data ( flash5_t *ctx, uint8_t status_cmd, uint8_t status_addr );

/**
 * @brief Function for writing status data
 *
 * @param ctx           Click object.
 * @param status_cmd    Command status
 * @param status_addr   Address of status
 * @param status_data   Input status
 */
void flash5_write_status_data ( flash5_t *ctx, uint8_t status_cmd, uint8_t status_addr, uint8_t status_data );

/**
 * @brief Function for reseting device
 * 
 * @param ctx         Click object.
 */
void flash5_software_reset ( flash5_t *ctx );

/**
 * @brief Function for eraseing one page
 *
 * @param ctx         Click object.
 * @param page_addr   Page to be erased
 */
void flash5_erase_page_data ( flash5_t *ctx, uint16_t page_addr );

#ifdef __cplusplus
}
#endif
#endif  // _FLASH5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for EERAM 2 Click driver.
 *
 * \addtogroup eeram2 EERAM 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EERAM2_H
#define EERAM2_H

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

#define EERAM2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EERAM2_RETVAL  uint8_t

#define EERAM2_OK           0x00
#define EERAM2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup Write Control Commands
 * \{
 */
#define EERAM2_CMD_WREN                                            0x06
#define EERAM2_CMD_WRDI                                            0x04
/** \} */

/**
 * \defgroup SRAM Commands
 * \{
 */
#define EERAM2_CMD_WRITE                                           0x02
#define EERAM2_CMD_READ                                            0x03
#define EERAM2_CMD_SECURE_WRITE                                    0x12
#define EERAM2_CMD_SECURE_READ                                     0x13
/** \} */

/**
 * \defgroup STATUS Register Commands
 * \{
 */
#define EERAM2_CMD_WRSR                                            0x01
#define EERAM2_CMD_RDSR                                            0x05
/** \} */

/**
 * \defgroup Store/Recall Commands
 * \{
 */
#define EERAM2_CMD_STORE                                           0x08
#define EERAM2_CMD_RECALL                                          0x09
/** \} */

/**
 * \defgroup Nonvolatile User Space Commands
 * \{
 */
#define EERAM2_CMD_WRNUR                                           0xC2
#define EERAM2_CMD_RDNUR                                           0xC3
/** \} */

/**
 * \defgroup Hibernate Commands
 * \{
 */
#define EERAM2_CMD_HIBERNATE                                        0xB9
/** \} */

/**
 * \defgroup Pause status
 * \{
 */
#define EERAM2_HOLD_DISABLE                                         0x00
#define EERAM2_HOLD_ENABLE                                          0x01
/** \} */

/**
 * \defgroup Write Status (WEL)
 * \{
 */
#define EERAM2_WRITE_DISABLE                                        0x00
#define EERAM2_WRITE_ENABLE                                         0x01
/** \} */
\
/**
 * \defgroup Status register bit mask
 * \{
 */
#define EERAM2_STATUS_ASE_ENABLE                                    0x00
#define EERAM2_STATUS_ASE_DISABLE                                   0x40
#define EERAM2_STATUS_BP_LVL_0                                      0x00
#define EERAM2_STATUS_BP_LVL_1                                      0x04
#define EERAM2_STATUS_BP_LVL_2                                      0x08
#define EERAM2_STATUS_BP_LVL_3                                      0x0C
/** \} */

/**
 * \defgroup Retval
 * \{
 */
#define EERAM2_ERROR                                                0x00
#define EERAM2_SUCCESS                                              0x01
/** \} */

/**
 * \defgroup SRAM address
 * \{
 */
#define EERAM2_SRAM_ADDR_FIRST                                      0x00000000
#define EERAM2_SRAM_ADDR_LAST                                       0x00FFFFFF
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
    digital_out_t hld;
 
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} eeram2_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} eeram2_cfg_t;

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
void eeram2_cfg_setup ( eeram2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EERAM2_RETVAL eeram2_init ( eeram2_t *ctx, eeram2_cfg_t *cfg );

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
void eeram2_generic_transfer ( eeram2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Set On-hold status function.
 *
 * @param ctx          Click object.
 * @param en_hold
 * - 0x00 ( EERAM2_HOLD_DISABLE ) : Pause the SPI communication with the device.
 * - 0x01 ( EERAM2_HOLD_ENABLE )  : Resume the SPI communication.
 *
 * @description Function sets the states of the HLD ( PWM ) pin
 * depending on the function argument.
 */
void eeram2_set_on_hold_status ( eeram2_t *ctx, uint8_t en_hold );

/**
 * @brief Set command function.
 *
 * @param ctx          Click object.
 * @param command      8-bit Commands Opcode.
 *
 * @description Function set command to the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
void eeram2_set_command ( eeram2_t *ctx, uint8_t command );

/**
 * @brief Set write status function.
 *
 * @param ctx          Click object.
 * @param en_write
 * - 0x00 ( EERAM2_WRITE_DISABLE ) : Write enable instruction.
 * - 0x01 ( EERAM2_WRITE_ENABLE )  : Write disable instruction.
 *
 * @description Function set write enable instruction of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
void eeram2_set_write_status ( eeram2_t *ctx, uint8_t en_write );

/**
 * @brief Set status register function.
 *
 * @param ctx          Click object.
 * @param tx_data
 * bit [ 6 ] :
 * - EERAM2_STATUS_ASE_DISABLE : AutoStore is disabled.
 * - EERAM2_STATUS_ASE_ENABLE  : AutoStore is enabled (factory default).
 * bit [ 3:2 ] :
 * - EERAM2_STATUS_BP_LVL_0 : No SRAM array write protection (factory default).
 * - EERAM2_STATUS_BP_LVL_1 : Upper quarter SRAM memory array protection.
 * - EERAM2_STATUS_BP_LVL_2 : Upper half SRAM memory array protection.
 * - EERAM2_STATUS_BP_LVL_3 :  Entire SRAM memory array protection.
 *
 * @description Function set status register of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
void eeram2_set_status ( eeram2_t *ctx, uint8_t tx_data );

/**
 * @brief Read status register function.
 *
 * @param ctx          Click object.
 * @return status
 * bit [ 7 ] : Reserved, Must be set to 0.
 * bit [ 6 ] : AutoStore Enable bit;
 *             - 0 : AutoStore is enabled (factory default).
 *             - 1 : AutoStore is disabled.
 * bit [ 5 ] : Reserved, Must be set to 0.
 * bit [ 4 ] : Secure Write Monitoring bit � Read-Only;
 *             - 0 : No error reported in Secure Write.
 *             - 1 : The last secure write operation has failed.
 * bit [ 3:2 ] : Block Protection bits;
 *             - 0 : ( Lvl 0 ) No SRAM array write protection (factory default).
 *             - 1 : ( Lvl 1 ) Upper quarter SRAM memory array protection.
 *             - 2 : ( Lvl 2 ) Upper half SRAM memory array protection.
 *             - 3 : ( Lvl 3 ) Entire SRAM memory array protection.
 * bit [ 1 ] : Write Enable Latch bit � Read-Only;
 *             - 0 : Device is not write-enabled.
 *             - 1 : WREN has been executed and device is enabled for writing.
 * bit [ 0 ] : Ready/Busy Status bit � Read-Only;
 *             - 0 : Device is ready for standard SRAM Read/Write commands.
 *             - 1 : Device is busy with an internal store or recall operation.
 *
 * @description Function set status register of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_get_status ( eeram2_t *ctx );

/**
 * @brief Write the data byte into SRAM function.
 *
 * @param ctx          Click object.
 * @param reg      24-bit register address.
 *
 * @param tx_data  8-bit write data.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : Write error;
 * - 1 ( EERAM2_SUCCESS ) : Successful writing;
 *
 * @description Function write the data byte
 * to the desired register address of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_write_byte ( eeram2_t *ctx, uint32_t reg, uint8_t tx_data );

/**
 * @brief Read the data byte from SRAM function.
 *
 * @param ctx          Click object.
 * @param reg      24-bit register address.
 *
 * @return
 * 8-bit read data.
 *
 * @description Function read the data byte
 * of the desired register address of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_read_byte ( eeram2_t *ctx, uint32_t reg );

/**
 * @brief Continuous write the data into SRAM function.
 *
 * @param ctx          Click object.
 * @param reg         24-bit register address.
 *
 * @param p_tx_data   pointer to the data to be written.
 *
 * @param n_bytes     number of bytes to be written.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : ERROR writing;
 * - 1 ( EERAM2_SUCCESS ) : Successful writing;
 *
 * @description Function writes a sequential data starting
 * to the targeted register address of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_write_continuous ( eeram2_t *ctx, uint32_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Continuous read the data into SRAM function.
 *
 * @param ctx          Click object.
 * @param reg         24-bit register address.
 *
 * @param p_rx_data   pointer to the memory location where data be stored.
 *
 * @param n_bytes     number of bytes to be read.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : ERROR reading;
 * - 1 ( EERAM2_SUCCESS ) : Successful reading;
 *
 * @description Function read a sequential data starting
 * from the targeted register address of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_read_continuous ( eeram2_t *ctx, uint32_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Nonvolatile user space write function.
 *
 * @param ctx          Click object.
 * @param p_tx_data   pointer to the data to be written.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : ERROR writing;
 * - 1 ( EERAM2_SUCCESS ) : Successful writing;
 *
 * @description Function writes a nonvolatile user space of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_read_nonvolatile ( eeram2_t *ctx, uint8_t *p_rx_data );

/**
 * @brief Nonvolatile user space read function.
 *
 * @param ctx          Click object.
 * @param p_tx_data   pointer to the memory location where data be stored.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : ERROR reading;
 * - 1 ( EERAM2_SUCCESS ) : Successful reading;
 *
 * @description Function read a nonvolatile user space of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_write_nonvolatile ( eeram2_t *ctx, uint8_t *p_tx_data );

/**
 * @brief Secure SRAM write function.
 *
 * @param ctx          Click object.
 * @param p_tx_data   pointer to the data to be written.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : ERROR writing;
 * - 1 ( EERAM2_SUCCESS ) : Successful writing;
 *
 * @description Function secure SRAM write,
 * which add another layer of protection to data of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_secure_write ( eeram2_t *ctx, uint16_t reg, uint8_t *p_tx_data );

/**
 * @brief Secure SRAM read function.
 *
 * @param ctx          Click object.
 * @param p_tx_data   pointer to the memory location where data be stored.
 *
 * @return
 * - 0 ( EERAM2_ERROR )   : ERROR reading;
 * - 1 ( EERAM2_SUCCESS ) : Successful reading;
 *
 * @description Function read data from the secure SRAM memory space of the
 * 48LM01 1-Mbit SPI Serial EERAM on the EERAM 2 click board.
 */
uint8_t eeram2_secure_read ( eeram2_t *ctx, uint16_t reg, uint8_t *p_rx_data );

#ifdef __cplusplus
}
#endif
#endif  // _EERAM2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

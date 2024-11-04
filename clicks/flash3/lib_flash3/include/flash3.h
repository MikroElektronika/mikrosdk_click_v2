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
 * \brief This file contains API for Flash 3 Click driver.
 *
 * \addtogroup flash3 Flash 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FLASH3_H
#define FLASH3_H

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

#define FLASH3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso= MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi= MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck= MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs= MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.hlo= MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.wp= MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FLASH3_RETVAL  uint8_t

#define FLASH3_OK           0x00
#define FLASH3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup status_register    Status Register
 * \{
 */
#define FLASH3_STATUS_WIP                                  0x01
#define FLASH3_STATUS_WEL                                  0x02
#define FLASH3_STATUS_BP_0                                 0x04
#define FLASH3_STATUS_BP_1                                 0x08
#define FLASH3_STATUS_BP_2                                 0x10
#define FLASH3_STATUS_BP_3                                 0x20
#define FLASH3_STATUS_QE                                   0x40
#define FLASH3_STATUS_SRWD                                 0x80
/** \} */

/**
 * \defgroup function_register    Function Register
 * \{
 */
#define FLASH3_FUNC_TBS                                    0x02
#define FLASH3_FUNC_PSUS                                   0x04
#define FLASH3_FUNC_ESUS                                   0x08
#define FLASH3_FUNC_IRL_0                                  0x10
#define FLASH3_FUNC_IRL_1                                  0x20
#define FLASH3_FUNC_IRL_2                                  0x40
#define FLASH3_FUNC_IRL_3                                  0x80
/** \} */

/**
 * \defgroup commands    Commands
 * \{
 */
#define FLASH3_NOP                                         0x00
#define FLASH3_WRSR                                        0x01
#define FLASH3_PP                                          0x02
#define FLASH3_WRDI                                        0x04
#define FLASH3_RDSR                                        0x05
#define FLASH3_WREN                                        0x06
#define FLASH3_RDFR                                        0x48
#define FLASH3_WRFR                                        0x42
#define FLASH3_PERSUS                                      0x75
#define FLASH3_PERRSM                                      0x7A
#define FLASH3_DP                                          0xB9
#define FLASH3_RDID                                        0xAB
#define FLASH3_SRP                                         0xC0
#define FLASH3_RDJDID                                      0x9F
#define FLASH3_RDMDID                                      0x90
#define FLASH3_RDJDIDQ                                     0xAF
#define FLASH3_RDUID                                       0x4B
#define FLASH3_RDSFDP                                      0x5A
#define FLASH3_RSTEN                                       0x66
#define FLASH3_RST                                         0x99
#define FLASH3_IRER                                        0x64
#define FLASH3_IRP                                         0x62
#define FLASH3_IRRD                                        0x68
#define FLASH3_SECUN_LOCK                                  0x26
#define FLASH3_SECLOCK                                     0x24
/** \} */

/**
 * \defgroup erese_modes    Erase Modes
 * \{
 */
#define FLASH3_SECTOR_ER                                   0xD7
#define FLASH3_BLOCK_ER32                                  0x52
#define FLASH3_BLOCK_ER64                                  0xD8
#define FLASH3_CHIP_ER                                     0xC7
/** \} */

/**
 * \defgroup read_modes    Read Modes
 * \{
 */
#define FLASH3_NORMAL_RD                                   0x03
#define FLASH3_FAST_RD                                     0x0B
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

    digital_out_t hlo;
    digital_out_t wp;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} flash3_t;

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

    pin_name_t hlo;
    pin_name_t wp;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} flash3_cfg_t;

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
void flash3_cfg_setup ( flash3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FLASH3_RETVAL flash3_init ( flash3_t *ctx, flash3_cfg_t *cfg );

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
void flash3_generic_transfer ( flash3_t *ctx, uint8_t *wr_buf, 
                            uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Pause function.
 *
 * @param ctx          Click object.
 *
 * @description This function pauses serial communication, without resetting the serial sequence.
 */
void flash3_pause ( flash3_t *ctx );

/**
 * @brief Unpause function.
 *
 * @param ctx          Click object.
 *
 * @description This function unpauses serial communication.
 */
void flash3_unpause ( flash3_t *ctx );

/**
 * @brief Write Protect enable function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to enable write protect.
 */
void flash3_wr_prot_enable ( flash3_t *ctx );

/**
 * @brief Disable write function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to to disable write function.
 */
void flash3_wr_prot_disable ( flash3_t *ctx );

/**
 * @brief Initialisation function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to set needed values to default.
 */
void flash3_setting ( flash3_t *ctx );

/**
 * @brief Enable write function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to to enable write function.
 */
void flash3_write_enable ( flash3_t *ctx );

/**
 * @brief Enable write function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to to enable write function.
 */
void flash3_write_disable ( flash3_t *ctx );

/**
 * @brief Write command function.
 *
 * @param ctx          Click object.
 * @param cmd          8-bit data representing command.
 *
 * @description This function is used to executes various commands.
 */
void flash3_write_cmd ( flash3_t *ctx, uint8_t cmd );

/**
 * @brief Flash 3 Command Advanced  function.
 *
 * @param ctx          Click object.
 * @param cmd          8-bit data representing command.
 * @param arg          data representing required arguments.
 * @param cnt          32-bit data representing number of bytes used for arguments.
 *
 * @description This function is used to executes various commands that requires arguments.
 */
void flash3_write_adv_cmd ( flash3_t *ctx, uint8_t cmd, uint8_t *arg, uint32_t cnt );

/**
 * @brief Reads Status Register function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to read status register.
 */
uint8_t flash3_rd_stat_reg ( flash3_t *ctx );

/**
 * @brief Write Status Register function.
 *
 * @param ctx          Click object.
 *
 * @description This function writes 8-bit data into status register.
 */
void flash3_wr_stat_reg ( flash3_t *ctx, uint8_t status );

/**
 * @brief Reads Function Register function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to read function register.
 */
uint8_t flash3_rd_func_reg ( flash3_t *ctx );

/**
 * @brief Reads Function Register function.
 *
 * @param ctx          Click object.
 * @param function     Function writes 8-bit data into function register.
 *
 * @description This function writes 8-bit data into function register.
 */
void flash3_wr_func_reg ( flash3_t *ctx, uint8_t function );

/**
 * @brief Normal data read function.
 *
 * @param ctx          Click object.
 * @param addr         Function writes 8-bit data into function register.
 * @param buff         data array read from memory.
 * @param cnt          32-bit data representing number of bytes user wants to read.
 *
 * @description This function is used to read memory contents at a maximum frequency of 50MHz.
 */
void flash3_normal_read( flash3_t *ctx, uint32_t addr, uint8_t *buff, uint32_t cnt );

/**
 * @brief Fast data read function.
 *
 * @param ctx          Click object.
 * @param addr         Function writes 8-bit data into function register.
 * @param buff         data array read from memory.
 * @param cnt          32-bit data representing number of bytes user wants to read.
 *
 * @description This function is used to read memory contents at a maximum frequency of 133MHz.
 */
void flash3_fast_read ( flash3_t *ctx, uint32_t addr, uint8_t *buff, uint32_t cnt );

/**
 * @brief Fast data read function.
 *
 * @param ctx          Click object.
 * @param addr         Function writes 8-bit data into function register.
 * @param buff         data array read from memory.
 * @param cnt          32-bit data representing number of bytes user wants to read.
 *
 * @description This function is used to read memory contents at a maximum frequency of 133MHz.
 */
void flash3_write ( flash3_t *ctx, uint32_t addr, uint8_t *buff, uint32_t cnt );

/**
 * @brief Chip erase function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to erase the entire memory array of a Flash 3 device.
 */
void flash3_chip_erase ( flash3_t *ctx );

/**
 * @brief Sector erase function.
 *
 * @param ctx          Click object.
 * @param addr         Function writes 8-bit data into function register.
 *
 * @description This function is used to erase a chosen 4 Kbyte sector.
 */
void flash3_sector_erase ( flash3_t *ctx, uint32_t address );

/**
 * @brief Block 32 erase function.
 *
 * @param ctx          Click object.
 * @param address         Function writes 8-bit data into function register.
 *
 * @description This function can take as long as 750 milliseconds to finish erasing chosen block.
 */
void flash3_block32_erase( flash3_t *ctx, uint32_t address );

/**
 * @brief Block 64 erase function.
 *
 * @param ctx          Click object.
 * @param address      Function writes 8-bit data into function register.
 *
 * @description This function can take as long as 1.5 seconds to finish erasing chosen block.
 */
void flash3_block64_erase( flash3_t *ctx, uint32_t address );


#ifdef __cplusplus
}
#endif
#endif  // _FLASH3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

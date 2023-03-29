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
 * \brief This file contains API for Excelon LP Click driver.
 *
 * \addtogroup excelonlp Excelon LP Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EXCELONLP_H
#define EXCELONLP_H

#include "drv_digital_out.h"
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

#define EXCELONLP_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.wp    = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EXCELONLP_RETVAL  uint8_t

#define EXCELONLP_OK           0x00
#define EXCELONLP_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup  opcode_commands Opcode Commands
 * \{
 */
#define EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH       0x06
#define EXCELONLP_OPCODE_RESET_WRITE_ENABLE_LATCH     0x04
#define EXCELONLP_OPCODE_READ_STATUS_REGISTER         0x05
#define EXCELONLP_OPCODE_WRITE_STATUS_REGISTER        0x01
#define EXCELONLP_OPCODE_WRITE_MEMORY_DATA            0x02
#define EXCELONLP_OPCODE_READ_MEMORY_DATA             0x03
#define EXCELONLP_OPCODE_FAST_READ_MEMORY_DATA        0x0B
#define EXCELONLP_OPCODE_SPECIAL_SECTOR_WRITE         0x42
#define EXCELONLP_OPCODE_SPECIAL_SECTOR_READ          0x4B
#define EXCELONLP_OPCODE_READ_DEVICE_ID               0x9F
#define EXCELONLP_OPCODE_READ_UNIQUE_ID               0x4C
#define EXCELONLP_OPCODE_WRITE_SERIAL_NUMBER          0xC2
#define EXCELONLP_OPCODE_READ_SERIAL_NUMBER           0xC3
#define EXCELONLP_OPCODE_ENTER_DEEP_POWER_DOWN        0xBA
#define EXCELONLP_OPCODE_Enter_Hibernate_Mode         0xB9
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

    digital_out_t wp;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} excelonlp_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} excelonlp_cfg_t;

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
void excelonlp_cfg_setup ( excelonlp_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EXCELONLP_RETVAL excelonlp_init ( excelonlp_t *ctx, excelonlp_cfg_t *cfg );

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
void excelonlp_generic_transfer ( excelonlp_t *ctx, uint8_t *wr_buf, 
    uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Functions for send opcode command
 *
 * @param ctx          Click object.
 * @param opcode       command to be sent
 *
 */
void excelonlp_send_command ( excelonlp_t *ctx, uint8_t opcode );

/**
 * @brief Functions for read data
 *
 * @param ctx          Click object.
 * @param opcode       Command to be sent
 * @param out_buf      Buffer in which data will be storage
 * @param n_data       Number of bytes to be read
 *
 */
void excelonlp_read_data ( excelonlp_t *ctx, uint8_t opcode, uint8_t *out_buf, uint8_t n_data);

/**
 * @brief Functions for write data to memory
 *
 * @param ctx          Click object.
 * @param opcode       Command to be sent
 * @param addr         addres in memmory
 * @param c_data       Data to be written
 *
 */
void excelonlp_write_memory_data ( excelonlp_t *ctx, uint8_t opcode, uint32_t addr, uint8_t c_data);

/**
 * @brief Functions for read data form memory
 *
 * @param ctx          Click object.
 * @param opcode       Transfer block structure.
 * @param addr         addres in memmory
 *
 */
uint8_t excelonlp_read_memory_data ( excelonlp_t *ctx, uint8_t opcode, uint32_t addr );


#ifdef __cplusplus
}
#endif
#endif  // _EXCELONLP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

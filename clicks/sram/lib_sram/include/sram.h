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
 * \brief This file contains API for SRAM Click driver.
 *
 * \addtogroup sram SRAM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SRAM_H
#define SRAM_H

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

#define SRAM_MAP_MIKROBUS( cfg, mikrobus )          \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.hld   = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SRAM_RETVAL  uint8_t

#define SRAM_OK                       0x00
#define SRAM_INIT_ERROR               0xFF
/** \} */

/**
 * \defgroup cmd_reg Command registers
 * \{
 */
#define SRAM_CMD_WRMR                 0x01
#define SRAM_CMD_WRITE                0x02
#define SRAM_CMD_READ                 0x03
#define SRAM_CMD_RDMR                 0x05
#define SRAM_CMD_EQIO                 0x38
#define SRAM_CMD_EDIO                 0x3B
#define SRAM_CMD_RSTIO                0xFF
/** \} */

/**
 * \defgroup mode Mode registers
 * \{
 */
#define SRAM_MODE_REG_BM              0x00
#define SRAM_MODE_REG_PM              0x80
#define SRAM_MODE_REG_SM              0x40
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

    digital_out_t hld;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} sram_t;

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
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} sram_cfg_t;

/** \} */ // End types group

// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 
/** \} */ // End constants group

// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group

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
 * @param cfg            Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void sram_cfg_setup ( sram_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param sram           Click object.
 * @param cfg            Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SRAM_RETVAL sram_init ( sram_t *ctx, sram_cfg_t *cfg );

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
void sram_generic_transfer 
( 
    sram_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 *
 * @description Generic SPI write, for sending packages
 */
void sram_generic_write 
( 
    sram_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len
);

/**
 * @brief Generic write byte of data funcion.
 *
 * @param ctx            Click object.
 * @param reg_address    24-bit register address.
 * @param write_data     8-bit data to write.
 *
 * @description Function write the 8-bit data to the target 24-bit register address of 23LC1024 chip.
 */
void sram_write_byte( sram_t *ctx, uint32_t reg_address, uint8_t write_data );

/**
 * @brief Generic read byte of data funcion.
 *
 * @param ctx            Click object.
 * @param reg_address    24-bit register address.
 *
 * @description Function read the 8-bit data to the target 24-bit register address of 23LC1024 chip.
 */
uint8_t sram_read_byte( sram_t *ctx, uint32_t reg_address );

/**
 * @brief Write mode register instruction funcion.
 *
 * @param ctx            Click object.
 * @param ins_data       8-bit instruction data.
 *
 * @description Function write the 8-bit instruction data to the target MODE register address of 23LC1024 chip.
 */
void sram_write_mode_reg_ins ( sram_t *ctx, uint8_t ins_data );

/**
 * @brief Read mode register instruction funcion.
 *
 * @param ctx            Click object.
 *
 * @description Function read the 8-bit instruction data to the target MODE register address of 23LC1024 chip.
 */
uint8_t sram_read_mode_reg_ins ( sram_t *ctx );

/**
 * @brief Soft reset funcion.
 *
 * @param ctx            Click object.
 *
 * @description This function writing reset instruction on the target RSTIO register.
 */
void sram_soft_reset ( sram_t *ctx );

/**
 * @brief Suspend transmission funcion.
 *
 * @param ctx            Click object.
 *
 * @description Thisfuncion sets RST pin in low state.
 */
void sram_hold_transmission ( sram_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SRAM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

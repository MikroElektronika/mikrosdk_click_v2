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
 * \brief This file contains API for DIGI POT 6 Click driver.
 *
 * \addtogroup digipot6 DIGI POT 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DIGIPOT6_H
#define DIGIPOT6_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define DIGIPOT6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DIGIPOT6_RETVAL  uint8_t

#define DIGIPOT6_OK           0x00
#define DIGIPOT6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup dev_cmds Device Commands
 * \{
 */
#define DIGIPOT6_CMD_WRITE          0x00
#define DIGIPOT6_CMD_INCREMENT      0x01
#define DIGIPOT6_CMD_DECREMENT      0x02
#define DIGIPOT6_CMD_READ           0x03
/** \} */

/**
 * \defgroup reg_map Register Map
 * \{
 */
#define DIGIPOT6_VOLATILE_WIPER_0     0x00
#define DIGIPOT6_TCON_REG             0x04
/** \} */

/**
 * \defgroup trm_ctrl_reg Terminal Control Register
 * \{
 */
#define DIGIPOT6_TCON_R0B           0xF1
#define DIGIPOT6_TCON_R0W           0xF2
#define DIGIPOT6_TCON_R0A           0xF4
#define DIGIPOT6_TCON_R0HW          0xF8

#define DIGIPOT6_TCON_MASK_R0B      0xFE
#define DIGIPOT6_TCON_MASK_R0W      0xFD
#define DIGIPOT6_TCON_MASK_R0A      0xFB
#define DIGIPOT6_TCON_MASK_R0HW     0xF7
/** \} */

/**
 * \defgroup connect_dc Connect / Disconnect
 * \{
 */
#define DIGIPOT6_CONNECT            0x01
#define DIGIPOT6_DISCONNECT         0x00
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

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} digipot6_t;

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

} digipot6_cfg_t;

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
void digipot6_cfg_setup ( digipot6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DIGIPOT6_RETVAL digipot6_init ( digipot6_t *ctx, digipot6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for DIGI POT 6 click.
 */
void digipot6_default_cfg ( digipot6_t *ctx );

/**
 * @brief Write data function.
 *
 * @param ctx       Click object.
 * @param reg       Register address.
 * @param w_data    Write data.
 *
 * @description This function writes data to the specified address.
 */
void digipot6_write_data ( digipot6_t *ctx, uint8_t reg, uint8_t w_data );

/**
 * @brief Write wiper command function.
 *
 * @param ctx       Click object.
 * @param cmd       Command.
 *
 * @description This function writes a wiper configuration command to the click module.
 */
void digipot6_write_wiper_cmd ( digipot6_t *ctx, uint8_t cmd );

/**
 * @brief Read data function.
 *
 * @param ctx       Click object.
 * @param reg       Register address.
 *
 * @description This function reads data from the specified register address.
 */
uint8_t digipot6_read_data ( digipot6_t *ctx, uint8_t reg ) ;

/**
 * @brief Set resistor function.
 *
 * @param ctx       Click object.
 * @param state     Resistor state.
 * @param mask      Module mask.
 * @param tcon      TCON module.
 *
 * @description This function reads data from the specified register address.
 */
void digipot6_set_resistor ( digipot6_t *ctx, uint8_t state, uint8_t mask, uint8_t tcon );

#ifdef __cplusplus
}
#endif
#endif  // _DIGIPOT6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

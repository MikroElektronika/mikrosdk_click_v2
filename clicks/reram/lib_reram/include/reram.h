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
 * \file reram.h
 *
 * \brief This file contains API for ReRAM Click driver.
 *
 * \addtogroup reram ReRAM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _RERAM_H_
#define _RERAM_H_

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

#define RERAM_ID_DATA                0x047FC903

/**
 * \defgroup commands Commands
 * \{
 */
#define RERAM_CMD_WREN               0x6
#define RERAM_CMD_WRDI               0x4
#define RERAM_CMD_SLEEP              0xB9
/** \} */

/**
 * \defgroup write_protect_set Write Protect Settings
 * \{
 */

/**
 * \defgroup block_protect Memory Block Protect
 * \{
 */
#define RERAM_BLOCK_PROT_NONE        0x0
#define RERAM_BLOCK_PROT_UPPER_1_4   0x4
#define RERAM_BLOCK_PROT_UPPER_1_2   0x8
#define RERAM_BLOCK_PROT_ALL         0xC
#define RERAM_BLOCK_PROT_MASK        0xC
/** \} */

/**
 * \defgroup write_protect Write Memory Protect
 * \{
 */
#define RERAM_WP_STAT_EN             0x80
#define RERAM_WP_STAT_DIS            0x0
#define RERAM_WP_STAT_MASK           0x80
/** \} */

/** \} */ //  End write_protect_set group

/**
 * \defgroup status Status
 * \{
 */
#define RERAM_FLAG_MASK_WEL          0x2
#define RERAM_FLAG_MASK_WIP          0x1
/** \} */

/**
 * \defgroup range Memory Range
 * \{
 */
#define RERAM_MEM_ADDR_START         0x0
#define RERAM_MEM_ADDR_END           0x7FFFF
#define RERAM_TRANSFER_BYTES_MIN     1
#define RERAM_TRANSFER_BYTES_MAX     256
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RERAM_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ho  = MIKROBUS( mikrobus, MIKROBUS_RST  ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS   ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sdi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.wp  = MIKROBUS( mikrobus, MIKROBUS_PWM  )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

//typedef spi_master_data_t  uint8_t;

/**
 * @brief Click error code.
 */
typedef enum
{
    RERAM_OK = 0,
    RERAM_ERR_DRV_INIT = 0xFC,
    RERAM_ERR_CMD,
    RERAM_ERR_MEM_ADDR,
    RERAM_ERR_NBYTES

} reram_err_t;

/**
 * @brief Click pin state.
 */
typedef enum
{
    RERAM_PIN_STATE_LOW = 0,
    RERAM_PIN_STATE_HIGH

} reram_pin_state_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    digital_out_t cs;
    
    //  Control pins.
    digital_out_t  wp;
    digital_out_t  ho;

    //  Module.
    spi_master_t  spi;
    pin_name_t chip_select;

} reram_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Used mikrobus pins.
    pin_name_t  ho;
    pin_name_t  cs;
    pin_name_t  sck;
    pin_name_t  sdo;
    pin_name_t  sdi;
    pin_name_t  wp;

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;  

} reram_cfg_t;

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
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes all used pins to unconnected state.
 */
void
reram_cfg_setup( reram_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok, 0xFC - Driver init error.
 *
 * @description This function initializes all peripherals and pins used by
 * ReRAM Click.
 */
reram_err_t
reram_init( reram_t *ctx, reram_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a default configuration for ReRAM Click.
 */
void
reram_default_cfg( reram_t *ctx );

/**
 * @brief Command Send function.
 *
 * @param ctx  Click object.
 * @param cmd_code  Command to be sent.
 *
 * @returns 0x0 - Ok, 0xFD - Command error.
 *
 * @description This function allows user to send a desired command to the
 * device.
 */
reram_err_t
reram_send_cmd( reram_t *ctx, uint8_t cmd_code );

/**
 * @brief Status Read function.
 *
 * @param ctx  Click object.
 *
 * @returns Status byte.
 *
 * @description This function reads status byte.
 */
uint8_t
reram_read_status( reram_t *ctx );

/**
 * @brief Status Write function.
 *
 * @param ctx  Click object.
 * @param data_in  Data to be written.
 *
 * @description This function writes data byte to Status register.
 */
void
reram_write_status( reram_t *ctx, uint8_t data_in );

/**
 * @brief Memory Read function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 * @param data_out  Memory where data be stored.
 * @param n_bytes  Number of bytes to be read.
 *
 * @returns 0x0 - Ok, 0xFE - Memory address error, 0xFF - Nbytes error.
 *
 * @description This function reads a selected block of memory, starting
 * from the selected address.
 */
reram_err_t
reram_read_memory( reram_t *ctx, uint32_t mem_addr,
                   uint8_t *data_out, uint16_t n_bytes );

/**
 * @brief Memory Write function.
 *
 * @param ctx  Click object.
 * @param mem_addr  Memory address.
 * @param data_in  Data to be written.
 * @param n_bytes  Number of bytes to be written.
 *
 * @returns 0x0 - Ok, 0xFE - Memory address error, 0xFF - Nbytes error.
 *
 * @description This function writes data to the selected memory block,
 * starting from the selected address.
 */
reram_err_t
reram_write_memory( reram_t *ctx, uint32_t mem_addr,
                    uint8_t *data_in, uint16_t n_bytes );

/**
 * @brief ID Read function.
 *
 * @param ctx  Click object.
 *
 * @returns Device ID.
 *
 * @description This function returns the 32-bit device ID.
 */
uint32_t
reram_read_id( reram_t *ctx );

/**
 * @brief Hold Pin Set function.
 *
 * @param ctx  Click object.
 * @param state  Pin state to be set.
 *
 * @description This function sets Hold pin to the desired state.
 */
void
reram_set_hold_pin( reram_t *ctx, reram_pin_state_t state );

/**
 * @brief Write Protect Pin Set function.
 *
 * @param ctx  Click object.
 * @param state  Pin state to be set.
 *
 * @description This function sets Write Protect pin to the desired state.
 */
void
reram_set_write_protect_pin( reram_t *ctx, reram_pin_state_t state );

/**
 * @brief Wake Up function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a device wake up sequence.
 */
void
reram_wake_up( reram_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _RERAM_H_

/** \} */ //  End public_function group
/// \}    //  End reram group
/*! @} */
// ------------------------------------------------------------------------ END

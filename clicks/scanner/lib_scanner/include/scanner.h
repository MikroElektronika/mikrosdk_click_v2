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
 * \brief This file contains API for Scanner Click driver.
 *
 * \addtogroup scanner Scanner Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SCANNER_H
#define SCANNER_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define SCANNER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SCANNER_RETVAL  uint8_t

#define SCANNER_OK           0x00
#define SCANNER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_map Register map 
 * \{
 */
#define SCANNER_REG_OFFSET_LEFT         0x00
#define SCANNER_REG_GAIN_LEFT           0x01
#define SCANNER_REG_OFFSET_CENTER       0x02
#define SCANNER_REG_GAIN_CENTER         0x03
#define SCANNER_REG_OFFSET_RIGHT        0x04
#define SCANNER_REG_GAIN_RIGHT          0x05
#define SCANNER_REG_MODE                0x1F
/** \} */

/**
 * \defgroup command  Command
 * \{
 */
#define SCANNER_CMD_IRESET              0x00
#define SCANNER_CMD_RESET               0x1B
#define SCANNER_CMD_STARTINT            0x08
#define SCANNER_CMD_SAMPLEINT           0x10
#define SCANNER_CMD_READPIXEL           0x02
#define SCANNER_CMD_ABORTPIXEL          0x19
#define SCANNER_CMD_READHOLD            0x12
#define SCANNER_CMD_READHOLD_START      0x16
#define SCANNER_CMD_REGWRITE            0x40
#define SCANNER_CMD_REGREAD             0x60
/** \} */

/**
 * \defgroup reg_command  Reg command
 * \{
 */
#define SCANNER_DATA_SLEEP_MODE         0x10
#define SCANNER_DATA_NORMAL_MODE        0x00
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

    digital_out_t mosi;
    digital_out_t sck;

    // Input pins 

    digital_in_t miso;

} scanner_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t mosi;
    pin_name_t miso;
    pin_name_t sck;

} scanner_cfg_t;

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
void scanner_cfg_setup ( scanner_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx     Click object.
 * @param cfg     Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
SCANNER_RETVAL scanner_init ( scanner_t *ctx, scanner_cfg_t *cfg );

/**
 * @brief Set SDI Pin function
 *
 * @param ctx         Click object.
 * @param sdi_mode    Defines state of the pin.
 * - 1 : Pin high
 * - 0 : Pin low
 *
 * @description Function is used to maipulate the state of the SDI pin.
**/
void scanner_set_sdi ( scanner_t *ctx, uint8_t sdi_mode );

/**
 * @brief Get SDO Pin state function
 *
 * @param ctx      Click object.
 * 
 * @return
 * - 1 : Pin high
 * - 0 : Pin low
 *
 * @description Function is used to get pin state.
**/
uint8_t scanner_get_sdo ( scanner_t *ctx );

/**
 * @brief Pulse function
 *
 * @param ctx      Click object.
 * 
 * @description Function is used to make SCK pulse.
**/
void scanner_clock ( scanner_t *ctx );

/**
 * @brief Write function
 *
 * @param ctx      Click object.
 * @param cmd      Write cmd.
 *
 * @description Function is used to write command to the device.
**/
void scanner_serial_cmd ( scanner_t *ctx, uint8_t cmd );

/**
 * @brief Read function
 *
 * @param ctx       Click object.
 * @param reg_adr   Register address.
 *
 * @return
 * - Returns read data.
 *
 * @description Function is used to read from the device.
**/
uint8_t scanner_serial_read_reg ( scanner_t *ctx, uint8_t reg_adr );

/**
 * @brief Write function
 *
 * @param ctx         Click object.
 * @param reg_adr     Register address.
 * @param write_data  Data to be written.
 *
 * @description Function is used to write to the device.
**/
void scanner_serial_write_reg ( scanner_t *ctx, uint8_t reg_adr, uint8_t write_data );

/**
 * @brief Start function
 *
 * @param ctx        Click object.
 * 
 * @description Function is used to start up the linear array sensor.
 * @note It is necessary to use this function in the application initialization stage.
**/
void scanner_startup ( scanner_t *ctx );

/**
 * @brief Read pixels
 *
 * @param ctx         Click object. 
 * @param pixel_data  Pixel buffer data.
 *
 * @description Function is used to read pixel status.
 * @note pixel_data should be buffer of 102 elements so that every data can be stored
**/
void scanner_read_pixel ( scanner_t *ctx, uint8_t *pixel_data );

#ifdef __cplusplus
}
#endif
#endif  // _SCANNER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

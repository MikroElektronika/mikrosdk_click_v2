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
 * \brief This file contains API for TouchKey 3 Click driver.
 *
 * \addtogroup touchkey3 TouchKey 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TOUCHKEY3_H
#define TOUCHKEY3_H

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
#define TOUCHKEY3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TOUCHKEY3_RETVAL  uint8_t

#define TOUCHKEY3_OK           0x00
#define TOUCHKEY3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup eeprom_settings EEPROM settings
 * \{
 */
#define TOUCHKEY3_CMD_SENDSETUP             0x01
#define TOUCHKEY3_CMD_RESET                 0x04
#define TOUCHKEY3_CMD_SLEEP                 0x05
#define TOUCHKEY3_CMD_EEPROM_STORE          0x0A
#define TOUCHKEY3_CMD_EEPROM_RESTORE        0x0B
#define TOUCHKEY3_CMD_EEPROM_ERASE          0x0C
#define TOUCHKEY3_CMD_EEPROM_RECOVER        0x0D
/** \} */

/**
 * \defgroup callibrate_keys Callibrate keys
 * \{
 */
#define TOUCHKEY3_CMD_CALLIBRATE_ALL        0x03
#define TOUCHKEY3_CMD_CALLIBRATE_0          0x10
#define TOUCHKEY3_CMD_CALLIBRATE_1          0x11
#define TOUCHKEY3_CMD_CALLIBRATE_2          0x12
#define TOUCHKEY3_CMD_CALLIBRATE_3          0x13
#define TOUCHKEY3_CMD_CALLIBRATE_4          0x14
#define TOUCHKEY3_CMD_CALLIBRATE_5          0x15
#define TOUCHKEY3_CMD_CALLIBRATE_6          0x16
/** \} */

/**
 * \defgroup keys_status_returned Keys status returned
 * \{
 */   
#define TOUCHKEY3_REQ_FIRST_KEY             0xC0
#define TOUCHKEY3_REQ_ALL_KEYS              0xC1
#define TOUCHKEY3_REQ_DEVICE_STATUS         0xC2
#define TOUCHKEY3_REQ_EEPROM_CRC            0xC3
#define TOUCHKEY3_REQ_RAM_CRC               0xC4
#define TOUCHKEY3_REQ_ERROR_KEYS            0xC5
/** \} */

/**
 * \defgroup other_macros Other macros
 * \{
 */
#define TOUCHKEY3_REQ_LAST_COMMAND          0xC7
#define TOUCHKEY3_REQ_SETUP_DATA            0xC8
#define TOUCHKEY3_REQ_DEVICE_ID             0xC9
#define TOUCHKEY3_REQ_FIRMWARE_VERSION      0xCA
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

    digital_out_t rst;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} touchkey3_t;

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
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} touchkey3_cfg_t;

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
void touchkey3_cfg_setup ( touchkey3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param touchkey3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TOUCHKEY3_RETVAL touchkey3_init ( touchkey3_t *ctx, touchkey3_cfg_t *cfg );

/**
 * @brief Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets RST pin first to low and then to high.
 */
void touchkey3_reset ( touchkey3_t *ctx );

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
void touchkey3_generic_transfer 
( 
    touchkey3_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Send command
 *
 * @param ctx                  Click object.
 * @param command              Command to execute.
 *
 * @description Function executes one of the possible commands.
 */
void touchkey3_send_command ( touchkey3_t *ctx, uint8_t command );

/**
 * @brief Send setup data
 *
 * @param ctx                       Click object.
 * @param p_setup_data              Pointer to 42 bytes of setup data.
 *
 * @description Function executes send setup command, which enters 42 bytes of configuration data.
 */
void touchkey3_send_setup ( touchkey3_t *ctx, uint8_t *p_setup_data );

/**
 * @brief Send request
 *
 * @param ctx                  Click object.
 * @param request              Type of request to send.
 * @param p_response           Pointer to the responce data (1, 2 or 42 bytes).
 *
 * @description Function sends a request command, and returns the response.
 */
void touchkey3_send_request ( touchkey3_t *ctx, uint8_t request, uint8_t *p_response );

/**
 * @brief Set configuration data
 *
 * @param ctx                   Click object.
 * @param data_address          Address of the configuration byte.
 * @param write_data            New value of the configuration data byte.
 *
 * @description Function sets a selected configuration byte to a desired value.
 */
void touchkey3_set_data ( touchkey3_t *ctx, uint8_t data_address, uint8_t write_data );

/**
 * @brief Read configuration data
 *
 * @param ctx                   Click object.
 * @param data_address          Address of the register to read from.
 * @param read_data             Value in register.
 *
 * @description Function reads from a selected configuration register.
 */
void touchkey3_get_data ( touchkey3_t *ctx, uint8_t data_address, uint8_t *read_data );

#ifdef __cplusplus
}
#endif
#endif  // _TOUCHKEY3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

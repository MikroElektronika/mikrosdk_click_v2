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
 * \brief This file contains API for MAGNETO Click driver.
 *
 * \addtogroup magneto MAGNETO Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MAGNETO_H
#define MAGNETO_H

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

#define MAGNETO_MAP_MIKROBUS( cfg, mikrobus )         \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.out     = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MAGNETO_RETVAL  uint8_t

#define MAGNETO_OK                                0x00
#define MAGNETO_INIT_ERROR                        0xFF
/** \} */

/**
 * \defgroup register Register Address
 * \{
 */
#define MAGNETO_REG_CLEAR_ERROR_FLAG              0x0001
#define MAGNETO_REG_PROGRAMMING_CONTROL           0x0003
#define MAGNETO_REG_OTP_ZERO_POS_HIGH             0x0016
#define MAGNETO_REG_OTP_ZERO_POS_LOW              0x0017
#define MAGNETO_REG_DIAG_AGC                      0x3FFD
#define MAGNETO_REG_MAGNITUDE                     0x3FFF
#define MAGNETO_REG_ANGLE                         0x3FFF
/** \} */

/**
 * \defgroup cmd_reg Command registers
 * \{
 */
#define MAGNETO_CMD_RESET_VALUE                   0x0000
#define MAGNETO_CMD_SET_VALUE                     0xFFFE
#define MAGNETO_CMD_MAGNITUDE_VALUE               0x1FFE
#define MAGNETO_CMD_PARITY_VALUE                  0x000F
#define MAGNETO_CMD_READ_COMMAND_BIT              0x4000
#define MAGNETO_CMD_HIGH_BYTE                     0xFF00
#define MAGNETO_CMD_LOW_BYTE                      0x00FF
/** \} */

/**
 * \defgroup flag Diagnostics flags
 * \{
 */
#define MAGNETO_FLAG_OK                           0
#define MAGNETO_FLAG_ERROR                        1
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

    digital_out_t out;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} magneto_t;

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

    pin_name_t out;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} magneto_cfg_t;

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
 * @param cfg                     Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void magneto_cfg_setup ( magneto_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param magneto                 Click object.
 * @param cfg                     Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MAGNETO_RETVAL magneto_init ( magneto_t *ctx, magneto_cfg_t *cfg );

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
void magneto_generic_transfer 
( 
    magneto_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief 16-bit command generic read function.
 *
 * @param ctx                     Click object.
 * @param address_command         14-bit command address.
 * 
 * @return 14-bit read data.
 *
 * @description This function takes 16-bit address commnand of the target register to be written to that register.
 */
uint16_t magneto_read_data ( magneto_t *ctx, uint16_t address_command );

/**
 * @brief 16-bit command generic write function.
 *
 * @param ctx                     Click object.
 * @param address_command         14-bit command address.
 * @param write_data              14-bit data to write.
 *
 * @description This function takes 16-bit address commnand of the target register 
 * and the 16-bit write data to be written to that register.
 */
void magneto_write_data ( magneto_t *ctx, uint16_t address_command, uint16_t write_data );

/**
 * @brief Get state function.
 *
 * @param ctx                     Click object.
 * 
 * @return 16-bit data containing flags.
 *
 * @description This function read and returns the value of the state register.
 */
uint16_t magneto_get_state ( magneto_t *ctx );

/**
 * @brief Check state function.
 *
 * @param ctx                     Click object.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0 = MAGNETO_FLAG_OK
 *     1 = MAGNETO_FLAG_ERROR
 * </pre>
 * -------------------------------------
 *
 * @description This function check and returns 0 or 1.
 */
uint8_t magneto_check_state ( magneto_t *ctx );

/**
 * @brief Calculate angle function.
 *
 * @param ctx                     Click object.
 * 
 * @return Float value of angle.
 *
 * @description This function read the 16-bit data from register then calculate and convert 
 * to float angle value from 0deg to 360deg.
 */
float magneto_get_angle ( magneto_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MAGNETO_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

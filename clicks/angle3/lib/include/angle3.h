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
 * \brief This file contains API for Angle 3 Click driver.
 *
 * \addtogroup angle3 Angle 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANGLE3_H
#define ANGLE3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANGLE3_RETVAL  uint8_t

#define ANGLE3_OK           0x00
#define ANGLE3_INIT_ERROR   0xFF
/** \} */

 /**
 * \defgroup register Register
 * \{
 */
#define ANGLE3_REG_ANG                            0x00
#define ANGLE3_REG_MAG                            0x01
#define ANGLE3_REG_CHMD                           0x02
#define ANGLE3_REG_ERRMON                         0x03
#define ANGLE3_REG_ZP                             0x06
#define ANGLE3_REG_RDABZ                          0x07
#define ANGLE3_REG_MLK                            0x08
#define ANGLE3_REG_EBDIS                          0x09
#define ANGLE3_REG_UVW                            0x0A
 /** \} */ // End group register 

 /**
 * \defgroup EEPROM_locations EEPROM locations
 * \{
 */
#define ANGLE3_EEPROM_ID1                         0x04
#define ANGLE3_EEPROM_ID2                         0x05
#define ANGLE3_EEPROM_ZP                          0x06
#define ANGLE3_EEPROM_RDABZ                       0x07
#define ANGLE3_EEPROM_MLK                         0x08
#define ANGLE3_EEPROM_EBDIS                       0x09
#define ANGLE3_EEPROM_UVW                         0x0A
 /** \} */ // End group EEPROM_locations 

 /**
 * \defgroup operation_code Operation Code
 * \{
 */
#define ANGLE3_OPCODE_LOCK_EEPROM                 0x00
#define ANGLE3_OPCODE_WRITE_EEPROM                0x01
#define ANGLE3_OPCODE_READ_EEPROM                 0x02
#define ANGLE3_OPCODE_WRITE_REG                   0x03
#define ANGLE3_OPCODE_READ_REG                    0x04
#define ANGLE3_OPCODE_CHANGE_MODE                 0x05
#define ANGLE3_OPCODE_ANGLE_DATA_RENEW            0x08
#define ANGLE3_OPCODE_READ_ANGLE                  0x09
 /** \} */ // End group operation_code

 /**
 * \defgroup command Command
 * \{
 */
#define ANGLE3_NORMAL_MODE                      0x0000
#define ANGLE3_USER_MODE                        0x050F
 /** \} */ // End group command

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define ANGLE3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
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
    
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} angle3_t;

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

    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} angle3_cfg_t;

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
void angle3_cfg_setup ( angle3_cfg_t *cfg );

/**
 * @brief Default Config Object Initialization function.
 *
 * @param ctx  Click configuration structure.
 *
 * @description This function initializes default click configuration structure to init state.
 * <pre>
 * Configuration sets default normal operating mode.
 * </pre>
 */
void angle3_default_cfg ( angle3_t *ctx );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANGLE3_RETVAL angle3_init ( angle3_t *ctx, angle3_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param opcode       Operation code.
 * @param reg          Address of data to write.
 * @param write_data   Data to write.
 *
 * @description Writes given data to given address.
 */
void angle3_write_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg,
	                     uint16_t write_data );
/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param opcode       Operation code.
 * @param reg          Address of data to read.
 *
 * @return result      16-bit read data.
 *
 * @description Reads data from given address.
 */
uint16_t angle3_read_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg );

/**
 * @brief Write EEPROM function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Address in EEPROM to write to.
 * @param write_data   Data to write.
 *
 * @description Function writes given 16-bit data to given 8-bit register address in EEPROM.
 * Only write to EEPROM before calling the lock function,
 * and provide only the valid EEPROM addresses.
 */
void angle3_write_EEPROM ( angle3_t* ctx, uint8_t reg_addr, uint16_t write_data );

/**
 * @brief Read EEPROM function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Address in EEPROM to write to.
 *
 * @return result      12-bit read data.
 *
 * @description Function reads 12-bit read data from given 8-bit register address in EEPROM.
 */
uint16_t angle3_read_EEPROM ( angle3_t* ctx, uint8_t reg_addr );

/**
 * @brief  EEPROM lock function.
 *
 * @param ctx          Click object.
 *
 * @description Function locks the EEPROM so that it cannot be written to until
 * the next reset.After calling this routine it will be impossible to
 * modify the EEPROM, so all writes to it should be done before calling this.
 *
 */
void angle3_lock_EEPROM ( angle3_t* ctx );

/**
 * @brief  Write register function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Address of register to write to.
 * @param write_data   Data to write.
 *
 * @description  Function writes given data to Register at given address.
 *
 */
void angle3_write_register ( angle3_t* ctx, uint8_t reg_addr, uint16_t write_data );

/**
 * @brief  Read register function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Address of register to read from.
 *
 * @return result      12-bit read data.
 *
 * @description  Function reads 12-bit data from given 8-bit register address.
 *
 */
uint16_t angle3_read_register ( angle3_t* ctx, uint8_t reg_addr );

/**
 * @brief  Set mode function.
 *
 * @param ctx          Click object.
 * @param set_mode     Mode to set Angle3 to.
 *
 * @description  Function sets mode of Angle3 click to the one provided.
 * The two valid modes are: normal with value 0x0000,
 * and user with value 0x050F.
 *
 */
void angle3_set_mode( angle3_t* ctx, uint16_t set_mode );

/**
 * @brief  Set normal mode function.
 *
 * @param ctx          Click object.
 *
 * @description  Function sets mode of Angle3 click to normal.
 * Set value 0x0000 for normal mode.
 *
 */
void angle3_set_normal_mode ( angle3_t* ctx );

/**
 * @brief  Set user mode function.
 *
 * @param ctx          Click object.
 *
 * @description  Function sets mode of Angle3 click to user. 
 * Set value 0x050F for user mode.
 *
 */
void angle3_set_user_mode ( angle3_t* ctx );

/**
 * @brief  Read angle data function.
 * @param ctx          Click object.
 *
 * @return result      12-bit Read angle data.
 *
 * @description  Function reads the latest angle output data.
 *
 */
uint16_t angle3_read_angle_data ( angle3_t* ctx );


/**
 * @brief  Degrees Calculation function.
 * @param ctx          Click object.
 * @param angle        Angle to convert to degrees.
 * 
 *
 * @return result      Float value of angle in degrees.
 *
 * @description  Function converts an angle value read from Angle3
 * click to degrees.
 *
 */
float angle3_calculate_degrees ( angle3_t* ctx, uint16_t angle );

/**
 * @brief  Read state of Error INT Pin.
 * @param ctx                  Click object.
 *
 *
 * @return INT Pin state       0 - Error, 1- No Error.
 *
 * @description  Function read state of Error INT Pin function.
 *
 */
uint8_t angle3_read_error ( angle3_t* ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ANGLE3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

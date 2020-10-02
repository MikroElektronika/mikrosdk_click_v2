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
 * \brief This file contains API for I2C 1 Wire Click driver.
 *
 * \addtogroup i2c1wire I2C 1 Wire Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2C1WIRE_H
#define I2C1WIRE_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define I2C1WIRE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2C1WIRE_RETVAL  uint8_t

#define I2C1WIRE_OK           0x00
#define I2C1WIRE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup settings_config Settings & Config
 * \{
 */
#define I2CONEWIRE_RESULT_ERROR              0x00
#define I2CONEWIRE_RESULT_OK                 0x01
#define I2CONEWIRE_WIRE_RESULT_OK            0xFF

#define I2CONEWIRE_I2C_ADDRESS_0             0x18
#define I2CONEWIRE_I2C_ADDRESS_1             0x19
#define I2CONEWIRE_I2C_ADDRESS_2             0x1A
#define I2CONEWIRE_I2C_ADDRESS_3             0x1B
#define I2CONEWIRE_I2C_ADDRESS_4             0x1C
#define I2CONEWIRE_I2C_ADDRESS_5             0x1D
#define I2CONEWIRE_I2C_ADDRESS_6             0x1E
#define I2CONEWIRE_I2C_ADDRESS_7             0x1F

#define I2CONEWIRE_COMMAND_RESET             0xF0
#define I2CONEWIRE_COMMAND_SRP               0xE1
#define I2CONEWIRE_POINTER_STATUS            0xF0
#define I2CONEWIRE_STATUS_BUSY               0x01
#define I2CONEWIRE_STATUS_PPD                0x02
#define I2CONEWIRE_STATUS_SD                 0x04
#define I2CONEWIRE_STATUS_LL                 0x08
#define I2CONEWIRE_STATUS_RST                0x10
#define I2CONEWIRE_STATUS_SBR                0x20
#define I2CONEWIRE_STATUS_TSB                0x40
#define I2CONEWIRE_STATUS_DIR                0x80
#define I2CONEWIRE_POINTER_DATA              0xE1
#define I2CONEWIRE_POINTER_CONFIG            0xC3
#define I2CONEWIRE_CONFIG_APU_HIGH           0x30
#define I2CONEWIRE_CONFIG_APU_LOW            0x01
#define I2CONEWIRE_CONFIG_SPU_HIGH           0x60
#define I2CONEWIRE_CONFIG_SPU_LOW            0x04
#define I2CONEWIRE_CONFIG_1WS_HIGH           0xA0
#define I2CONEWIRE_CONFIG_1WS_LOW            0x08
#define I2CONEWIRE_COMMAND_WRITECONFIG       0xD2
#define I2CONEWIRE_COMMAND_RESETWIRE         0xB4
#define I2CONEWIRE_COMMAND_WRITEBYTE         0xA5
#define I2CONEWIRE_COMMAND_READBYTE          0x96
#define I2CONEWIRE_COMMAND_SINGLEBIT         0x87
#define I2CONEWIRE_COMMAND_TRIPLET           0x78
#define I2CONEWIRE_WIRE_COMMAND_SKIP         0xCC
#define I2CONEWIRE_WIRE_COMMAND_SELECT       0x55
#define I2CONEWIRE_WIRE_COMMAND_READ_ROM     0x33
#define I2CONEWIRE_WIRE_COMMAND_SEARCH       0xF0
#define I2CONEWIRE_ERROR_TIMEOUT             0x01
#define I2CONEWIRE_ERROR_SHORT               0x02
#define I2CONEWIRE_ERROR_CONFIG              0x04
#define I2CONEWIRE_CMD_CHSL                  0xC3
#define I2CONEWIRE_CH_IO0                    0xF0
#define I2CONEWIRE_CH_IO1                    0xE1
#define I2CONEWIRE_CH_IO2                    0xD2
#define I2CONEWIRE_CH_IO3                    0xC3
#define I2CONEWIRE_CH_IO4                    0xB4
#define I2CONEWIRE_CH_IO5                    0xA5
#define I2CONEWIRE_CH_IO6                    0x96
#define I2CONEWIRE_CH_IO7                    0x87
#define I2CONEWIRE_RCH_IO0	                 0xB8
#define I2CONEWIRE_RCH_IO1	                 0xB1
#define I2CONEWIRE_RCH_IO2                   0xAA
#define I2CONEWIRE_RCH_IO3                   0xA3
#define I2CONEWIRE_RCH_IO4                   0x9C
#define I2CONEWIRE_RCH_IO5                   0x95
#define I2CONEWIRE_RCH_IO6                   0x8E
#define I2CONEWIRE_RCH_IO7                   0x87
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
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} i2c1wire_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2c1wire_cfg_t;

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
void i2c1wire_cfg_setup ( i2c1wire_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
I2C1WIRE_RETVAL i2c1wire_init ( i2c1wire_t *ctx, i2c1wire_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void i2c1wire_generic_write ( i2c1wire_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void i2c1wire_generic_read ( i2c1wire_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Software reset function.
 * 
 * @param ctx          Click object.
 *
 * @description This function does a software reset of the click module.
 */
void i2c1wire_soft_reset ( i2c1wire_t *ctx );

/**
 * @brief Set configuration function.
 * 
 * @param ctx          Click object.
 * @param cfg          Configuration.
 *
 * @description This function configures the click module using the specified settings.
 */
uint8_t i2c1wire_set_config ( i2c1wire_t *ctx, uint8_t cfg );

/**
 * @brief Set channel function.
 * 
 * @param ctx          Click object.
 * @param chan         Channel.
 *
 * @description This function configures the click module using the specified settings.
 */
uint8_t i2c1wire_set_channel ( i2c1wire_t *ctx, uint8_t chan );

/**
 * @brief Set read pointer function.
 * 
 * @param ctx          Click object.
 * @param ptr          Pointer.
 *
 * @description This function sets the read pointer for the click module.
 */
void i2c1wire_set_read_pointer ( i2c1wire_t *ctx, uint8_t ptr );

/**
 * @brief Reset function.
 * 
 * @param ctx          Click object.
 *
 * @description This function does a hardware reset of the click module.
 */
void i2c1wire_one_wire_reset ( i2c1wire_t *ctx );

/**
 * @brief Write byte function.
 * 
 * @param ctx          Click object.
 * @param input        Write data.
 *
 * @description This function writes one byte to the click module.
 */
void i2c1wire_write_byte_one_wire ( i2c1wire_t *ctx, uint8_t input );

/**
 * @brief Read byte function.
 * 
 * @param ctx          Click object.
 *
 * @description This function reads one byte from the click module.
 */
uint8_t i2c1wire_read_byte_one_wire ( i2c1wire_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _I2C1WIRE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

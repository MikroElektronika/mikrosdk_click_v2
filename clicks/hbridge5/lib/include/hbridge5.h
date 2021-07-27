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
 * \brief This file contains API for H Bridge 5 Click driver.
 *
 * \addtogroup hbridge5 H Bridge 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HBRIDGE5_H
#define HBRIDGE5_H

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
#define HBRIDGE5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HBRIDGE5_RETVAL  uint8_t

#define HBRIDGE5_OK           0x00
#define HBRIDGE5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_slave_address Device Slave Address
 * \{
 */
#define HBRIDGE5_DEVICE_SLAVE_ADDR_0_0   0x70
#define HBRIDGE5_DEVICE_SLAVE_ADDR_0_1   0x71
#define HBRIDGE5_DEVICE_SLAVE_ADDR_1_0   0x72
#define HBRIDGE5_DEVICE_SLAVE_ADDR_1_1   0x73
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define HBRIDGE5_CMD_INPUT_PORT          0x00
#define HBRIDGE5_CMD_OUTPUT_PORT         0x01
#define HBRIDGE5_CMD_POLARITY_INVERSION  0x02
#define HBRIDGE5_CMD_CONFIGURATION       0x03
/** \} */

/**
 * \defgroup port_status Port Status
 * \{
 */
#define HBRIDGE5_PORT_PHASE              0x01
#define HBRIDGE5_PORT_ENABLE             0x02
#define HBRIDGE5_PORT_BRAKE              0x04
#define HBRIDGE5_PORT_B_MODE             0x08
#define HBRIDGE5_PORT_N_SLEEP            0x10
#define HBRIDGE5_PORT_N_FAULT            0x20
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define HBRIDGE5_ENABLE_ALL_OUTPUT_PORT  0xE0
#define HBRIDGE5_DISABLE_ALL_OUTPUT_PORT 0xFF
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

    // Input pins 

    digital_in_t an;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} hbridge5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} hbridge5_cfg_t;

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
void hbridge5_cfg_setup ( hbridge5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HBRIDGE5_RETVAL hbridge5_init ( hbridge5_t *ctx, hbridge5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HBridge5 click.
 */
void hbridge5_default_cfg ( hbridge5_t *ctx );

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
void hbridge5_generic_write ( hbridge5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void hbridge5_generic_read ( hbridge5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Resets pin state.
 *
 * @param ctx    Click object.
 * @param state  0 - pin cleared  / 1 - pin set.

 * @description Function is used to set the state of RST pin in order to reset the device.
 */
void hbridge5_rst_state ( hbridge5_t *ctx, uint8_t state );

/**
 * @brief Reads interrupt pin state.
 *
 * @param ctx  Click object.
 *
 * @description This function reads int_pin state.
 */
uint8_t hbridge5_get_interrupt_state ( hbridge5_t *ctx );

/**
 * @brief Function reads byte from register.
 *
 * @param ctx  Click object.
 * @param cmd  Command register which will be read.
 * 
 * @retval one byte data which is read from the register
 *
 * @description This function reads one byte from register.
 */
uint8_t hbridge5_read_byte ( hbridge5_t *ctx, uint8_t cmd );

/**
 * @brief Function writes one byte in register.
 *
 * @param ctx       Click object.
 * @param cmd       Command in which the data will be written.
 * @param data_in   Data which will be written in the register.
 *
 * @description This function writes one byte in register.
 */
void hbridge5_write_byte ( hbridge5_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief Function sets port.
 *
 * @param ctx       Click object.
 * @param port      Port to be set up.
 * @param value     Value to which the selected port is being set.
 *
 * @description This function sets port.
 */
void hbridge5_set_port ( hbridge5_t *ctx, uint8_t port, uint8_t value );

/**
 * @brief Puts motor into reverse motion.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to put motor into reverse motion.

 */
void hbridge5_reverse ( hbridge5_t *ctx );

/**
 * @brief Puts motor into forward motion.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to put motor into forward motion.
 */
void hbridge5_forward ( hbridge5_t *ctx );

/**
 * @brief Puts motor to a halt.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to brake motor to a halt.
 */
void hbridge5_brake_low ( hbridge5_t *ctx );

/**
 * @brief Puts motor to a halt.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to brake motor to a halt.
 */
void hbridge5_brake_high ( hbridge5_t *ctx );

/**
 * @brief Synchronization fast decay foreward function.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to apply synchronization fast decay.
 */
void hbridge5_sync_decay_fwd ( hbridge5_t *ctx );

/**
 * @brief Synchronization fast decay reverse function.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to apply synchronization fast decay.
 */
void hbridge5_sync_decay_rev ( hbridge5_t *ctx );

/**
 * @brief Sleep function.
 *
 * @param ctx    Click object.
 * @param state  0 - pin cleared  / 1 - pin set.
 *
 * @description Function is used to put device into sleep mode or to wake it up.
 */
void hbridge5_sleep( hbridge5_t *ctx, uint8_t state );

/**
 * @brief Configuration function.
 *
 * @param ctx         Click object.
 * @param cfg_data    Configuration data.
 *
 * @description Function is used to configure the device.
 */
void hbridge5_configuration ( hbridge5_t *ctx, uint8_t cfg_data );

/**
 * @brief N fault check function.
 *
 * @param ctx  Click object.
 *
 * @description Function is used to check n fault.
 */
uint8_t hbridge5_n_fault_check ( hbridge5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HBRIDGE5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

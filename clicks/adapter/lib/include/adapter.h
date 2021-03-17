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
 * \brief This file contains API for Adapter Click driver.
 *
 * \addtogroup adapter Adapter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADAPTER_H
#define ADAPTER_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
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

#define ADAPTER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); \
   cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
   cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ADAPTER_MASTER_I2C 0
#define ADAPTER_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADAPTER_RETVAL  uint8_t

#define ADAPTER_OK           0x00
#define ADAPTER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define I2C_SLAVE_ADDR_DEMO  0x4C
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  adapter_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *adapter_master_io_t )( struct adapter_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct adapter_s
{
    // Output pins 

    digital_out_t cs;
    digital_out_t pwm;
    digital_out_t tx_pin;
    digital_out_t rx_pin;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    
    uint8_t slave_address;
    pin_name_t chip_select;
    adapter_master_io_t  write_f;
    adapter_master_io_t  read_f;
    adapter_select_t master_sel;

} adapter_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   adapter_select_t sel;

} adapter_cfg_t;

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
void adapter_cfg_setup ( adapter_cfg_t *cfg );

/**
 * @brief Initialization function.

 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ADAPTER_RETVAL adapter_init ( adapter_t *ctx, adapter_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void adapter_generic_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Data buf to be written.
 * @param len        Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void adapter_generic_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void adapter_generic_transfer( adapter_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Turn TX on function
 *
 * @param ctx      Click object.
 *
 * @description Function is used to set TX pin to 1.
**/
void adapter_turn_tx_on ( adapter_t *ctx );

/**
 * @brief Turn RX on function
 *
 * @param ctx      Click object.
 *
 * @description Function is used to set RX pin to 1.
**/
void adapter_turn_rx_on ( adapter_t *ctx );

/**
 * @brief Turn PWM on function
 *
 * @param ctx      Click object.
 *
 * @description Function is used to set PWM pin to 1.
**/
void adapter_turn_pwm_on ( adapter_t *ctx );

/**
 * @brief Turn TX off function
 *
 * @param ctx      Click object.
 *
 * @description Function is used to set TX pin to 0.
**/
void adapter_turn_tx_off ( adapter_t *ctx );

/**
 * @brief Turn RX off function
 *
 * @param ctx      Click object.
 *
 * @description Function is used to set RX pin to 0.
**/
void adapter_turn_rx_off ( adapter_t *ctx );

/**
 * @brief Turn PWM off function
 *
 * @param ctx      Click object.
 *
 * @description Function is used to set PWM pin to 0.
**/
void adapter_turn_pwm_off ( adapter_t *ctx );

/**
 * @brief Check INT function
 *
 * @param ctx      Click object.
 *
 * @returns  State of the INT pin
 *
 * @description Function is used to check the state of INT pin.
**/
uint8_t adapter_check_int ( adapter_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ADAPTER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

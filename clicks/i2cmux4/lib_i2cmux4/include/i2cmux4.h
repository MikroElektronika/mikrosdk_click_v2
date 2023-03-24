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
 * \brief This file contains API for I2C MUX 4 Click driver.
 *
 * \addtogroup i2cmux4 I2C MUX 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CMUX4_H
#define I2CMUX4_H

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
#define I2CMUX4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */
 
/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CMUX4_RETVAL  uint8_t

#define I2CMUX4_OK           0x00
#define I2CMUX4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address  Device address
 * \{
 */
#define I2CMUX4_I2C_SLAVE_ADDRESS_0               0x70
#define I2CMUX4_I2C_SLAVE_ADDRESS_1               0x71
#define I2CMUX4_I2C_SLAVE_ADDRESS_2               0x72
#define I2CMUX4_I2C_SLAVE_ADDRESS_3               0x73
/** \} */
 
/**
 * \defgroup power_on  Power on 
 * \{
 */
#define I2CMUX4_ENABLE_POWER_OFF                  0x00
#define I2CMUX4_ENABLE_POWER_ON                   0x01
/** \} */
 
/**
 * \defgroup channel_selected  Channel selected
 * \{
 */
#define I2CMUX4_SEL_CH_ALL_DISABLE                0x00
#define I2CMUX4_SEL_CH_0                          0x01
#define I2CMUX4_SEL_CH_1                          0x02
/** \} */
 
/**
 * \defgroup interupt_handling  Interupt handling
 * \{
 */
#define I2CMUX4_INTERRUPT_CH_0                    0x10
#define I2CMUX4_INTERRUPT_CH_1                    0x20
#define I2CMUX4_INTERRUPT_BIT_MASK                0x30
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint8_t rmt_slave_addr;

} i2cmux4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2cmux4_cfg_t;

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
void i2cmux4_cfg_setup ( i2cmux4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param i2cmux4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
I2CMUX4_RETVAL i2cmux4_init ( i2cmux4_t *ctx, i2cmux4_cfg_t *cfg );

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
void i2cmux4_generic_write ( i2cmux4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void i2cmux4_generic_read ( i2cmux4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Power On function.
 *
 * @param ctx          Click object.
 * 
 * @description The function enable or disable the I2C MUX 4 click board
 * by set to '1' or cleared to '0' state of the RST pin.
**/
void i2cmux4_power_on ( i2cmux4_t *ctx, uint8_t enable );

/**
 * @brief Hardware reset function.
 *
 * @param ctx          Click object.
 * 
 * @description The function hardware reset I2C MUX 4 click board
 * by cleared to '0' state of the RST pin,
 * wait the 100 ms, sets to '1' state of the RST pin
 * and wait another the 100 ms.
**/
void i2cmux4_hw_reset ( i2cmux4_t *ctx );

/**
 * @brief Write command function.
 *
 * @param ctx          Click object.
 * @param cmd_data      
 * 8-bit command data to be transmitted.
 *
 * @description The function executes writes command to the
 * TCA9543A Low Voltage 2-Channel I2C Bus Switch With Interrupt Logic And Reset
 * on the I2C MUX 4 click board.
**/
void i2cmux4_write_cmd ( i2cmux4_t *ctx, uint8_t cmd_data );

/**
 * @brief Read command function.
 *
 * @param ctx          Click object.
 * 
 * @return
 * 8-bit read data.
 *
 * Function executes read command from the
 * TCA9543A Low Voltage 2-Channel I2C Bus Switch With Interrupt Logic And Reset
 * on the I2C MUX 4 click board.
**/
uint8_t i2cmux4_read_cmd ( i2cmux4_t *ctx );

/**
 * @brief Set channel function
 *
 * @param ctx          Click object.
 * @param sel_ch              
 * select channel:
 * - 0x00 ( I2CMUX4_SEL_CH_ALL_DISABLE ) :
 *   No channel selected; power-up/reset default state.
 * - 0x01 ( I2CMUX4_SEL_CH_0 ) :
 *   Channel 0 enabled.
 * - 0x02 ( I2CMUX4_SEL_CH_1 ) :
 *   Channel 1 enabled.
 *
 * @param ch_slave_addr
 * 7-bit i2c slave address of the device connected to the selected channel.
 *
 * @description The function sets channel and slave address of the 
 * device connected to the selected channel 
 * of the I2C MUX 4 click board.
**/
void i2cmux4_set_channel ( i2cmux4_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr );

/**
 * @brief Get channel interrupt function
 *
 * @param ctx          Click object.
 * 
 * @return 
 * channel interrupt bit
 *
 * @description The function get channel interrupt
 * of the I2C MUX 4 click board.
**/
uint8_t i2cmux4_get_ch_interrupt ( i2cmux4_t *ctx );

/**
 * @brief Generic rmt write data function
 *
 * @param ctx          Click object.
 * @param reg            
 * 8-bit register address.
 *
 * @param p_tx_data     
 * pointer to the data to be written.
 *
 * @param n_bytes       
 * number of bytes to be written.
 *
 * @description The function writes a sequential data starting 
 * to the targeted 8-bit
 * register address of the device connected to the desired channel
 * of the I2C MUX 4 click board.
 */
void i2cmux4_rmt_write_bytes ( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Generic read data function
 *
 * @param ctx          Click object.
 * @param reg         
 * 8-bit register address.
 *
 * @param p_rx_data   
 * pointer to the memory location where data be stored.
 *
 * @param n_bytes     
 * number of bytes to be read.
 *
 * @description The function read a sequential data starting
 * from the targeted 8-bit register address of
 * register address of the device connected to the desired channel
 * of the I2C MUX 4 click board.
 */
void i2cmux4_rmt_read_bytes ( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Check interrupt function.
 *
 * @param ctx          Click object.
 * 
 * @return
 * state of the INT pin.
 *
 * @description The function get INT pin state
 * of I2C MUX 4 click board.
**/
uint8_t i2cmux4_check_int ( i2cmux4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _I2CMUX4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

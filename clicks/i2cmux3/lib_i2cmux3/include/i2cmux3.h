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
 * \brief This file contains API for I2C Mux 3 Click driver.
 *
 * \addtogroup i2cmux3 I2C Mux 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CMUX3_H
#define I2CMUX3_H

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
#define I2CMUX3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CMUX3_RETVAL  uint8_t

#define I2CMUX3_OK           0x00
#define I2CMUX3_INIT_ERROR   0xFF
/** \} */
 
/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define I2CMUX3_DEV_ADR_0   0x70
#define I2CMUX3_DEV_ADR_1   0x71
#define I2CMUX3_DEV_ADR_2   0x72
#define I2CMUX3_DEV_ADR_3   0x73
#define I2CMUX3_DEV_ADR_4   0x74
#define I2CMUX3_DEV_ADR_5   0x75
#define I2CMUX3_DEV_ADR_6   0x76
#define I2CMUX3_DEV_ADR_7   0x77
/** \} */
 
/**
 * \defgroup channel_select  Channel select
 * \{
 */
#define I2CMUX3_DIS_ALL_CH  0x00
#define I2CMUX3_SEL_CH_0    0x01
#define I2CMUX3_SEL_CH_1    0x02
#define I2CMUX3_SEL_CH_2    0x04
#define I2CMUX3_SEL_CH_3    0x08
#define I2CMUX3_SEL_CH_4    0x10
#define I2CMUX3_SEL_CH_5    0x20
#define I2CMUX3_SEL_CH_6    0x40
#define I2CMUX3_SEL_CH_7    0x80
/** \} */
 
/**
 * \defgroup device_power_state  Device power state
 * \{
 */
#define I2CMUX3_DEV_DIS     0x00
#define I2CMUX3_DEV_EN      0x01
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
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} i2cmux3_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2cmux3_cfg_t;

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
void i2cmux3_cfg_setup ( i2cmux3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param i2cmux3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
I2CMUX3_RETVAL i2cmux3_init ( i2cmux3_t *ctx, i2cmux3_cfg_t *cfg );

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
void i2cmux3_generic_write ( i2cmux3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void i2cmux3_generic_read ( i2cmux3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write Control Register function
 *
 * @param ctx          Click object.
 * @param wr_data  8-bit input data
 *
 * Function is used to write to TCA9548A's control register.
**/
void i2cmux3_write_ctl ( i2cmux3_t *ctx, uint8_t wr_data );

/**
 * @brief Read Control Register function
 *
 * @param ctx          Click object.
 * 
 * @returns 8-bit content of control register
 *
 * Function is used to read from TCA9548A's control register.
**/
uint8_t i2cmux3_read_ctl ( i2cmux3_t *ctx );

/**
 * @brief Select Channel function
 *
 * @param ctx          Click object.
 * @param sel_ch  8-bit data ranging from 0 to 7 that defines channel
 *
 * Function is used to select communication channel.
 * @note User can use values ranging from 0 to 7 
 * in order to select wanted channel.
**/
void i2cmux3_ch_sel ( i2cmux3_t *ctx, uint8_t sel_ch );

/**
 * @brief Slave Device Write function
 *
 * @param ctx          Click object.
 * @param slv_sel_adr  I2C address of the connected slave device
 * @param reg          8-bit register address
 * @param p_wr_data    pointer to the data to be written
 * @param n_bytes      number of bytes to be written
 *
 * Function is used to write a sequential data starting from the targeted 8-bit
 * register address of the device connected to the desired channel 
 * of the I2C MUX 3 click board.
**/
void i2cmux3_wr_slv ( i2cmux3_t *ctx, uint8_t slv_sel_adr, uint8_t reg, uint8_t *p_wr_data, 
                      uint8_t n_bytes );

/**
 * @brief Slave Device Read function
 *
 * @param ctx          Click object.
 * @param slv_sel_adr  I2C address of the connected slave device
 * @param reg          8-bit register address
 * @param p_rd_data    pointer to the data to be read
 * @param n_bytes      number of bytes to be written
 *
 * Function is used to read a sequential data starting from the targeted 8-bit 
 * register address of the device connected to the desired channel
 * of the I2C MUX 3 click board.
**/
void i2cmux3_rd_slv ( i2cmux3_t *ctx, uint8_t slv_sel_adr, uint8_t reg, uint8_t *p_rd_data, 
                      uint8_t n_bytes );
                      
/**
 * @brief Device enable function
 *
 * @param ctx          Click object.
 * @param stat value defines state of the device
 *             '1'  Device enabled
 *             '0'  Device disabled
 *
 * Function is used to enable or disable the device.
**/
void i2cmux3_dev_enable ( i2cmux3_t *ctx, uint8_t stat );

/**
 * @brief Hardware reset function
 *
 * @param ctx          Click object.
 * 
 * Function is used to perform hardware reset of the I2C MUX 4 click board.
 * @note Function holds two 100 milliseconds delay.
**/
void i2cmux3_hw_rst ( i2cmux3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _I2CMUX3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

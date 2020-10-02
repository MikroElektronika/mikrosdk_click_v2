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
 * \brief This file contains API for Gyro 4 Click driver.
 *
 * \addtogroup gyro4 Gyro 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GYRO4_H
#define GYRO4_H

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

#define GYRO4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GYRO4_RETVAL  uint8_t

#define GYRO4_OK           0x00
#define GYRO4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_addresses  Register addresses
 * \{
 */
#define GYRO4_REG_WHO_AM_I         0x00
#define GYRO4_REG_TEMP_OUT_L       0x01
#define GYRO4_REG_TEMP_OUT_H       0x02
#define GYRO4_REG_OUT_X_L          0x03
#define GYRO4_REG_OUT_X_H          0x04
#define GYRO4_REG_OUT_Y_L          0x05
#define GYRO4_REG_OUT_Y_H          0x06
#define GYRO4_REG_DATA_STATUS_OIS  0x0A
#define GYRO4_REG_CTRL1_OIS        0x0B
#define GYRO4_REG_CTRL2_OIS        0x0C
#define GYRO4_REG_CTRL3_OIS        0x0D
#define GYRO4_REG_CTRL4_OIS        0x0E
#define GYRO4_REG_OFF_X            0x0F
#define GYRO4_REG_OFF_Y            0x10
#define GYRO4_REG_OIS_CFG          0x1F
/** \} */

/**
 * \defgroup power_modes  Power modes
 * \{
 */
#define GYRO4_POWER_DOWN_MODE  0x01
#define GYRO4_SLEEP_MODE       0x02
#define GYRO4_NORMAL_MODE      0x03
/** \} */

/**
 * \defgroup full_scale_ranges  Full scale ranges
 * \{
 */
#define GYRO4_100_DPS  0x01
#define GYRO4_200_DPS  0x02
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

    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    uint8_t aux_buffer [ 6 ];

} gyro4_t;

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
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} gyro4_cfg_t;

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
void gyro4_cfg_setup ( gyro4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gyro4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GYRO4_RETVAL gyro4_init ( gyro4_t *ctx, gyro4_cfg_t *cfg );

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
void gyro4_generic_transfer ( gyro4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Getting INT pin state
 *
 * @param ctx      Click object.
 *
 * @returns 0 if INT pin is LOW
 * @returns 1 if INT pin is HIGH
 *
 * @description This function gets INT pin state
 */
uint8_t gyro4_int_get( gyro4_t *ctx );

/**
 * @brief Setting CS pin state
 *
 * @param ctx         Click object. 
 * @param pin_state   pin state (0 for LOW and 1 for HIGH)
 *
 *
 * @description This function gets INT pin state
 */
void gyro4_cs_set( gyro4_t *ctx, uint8_t pin_state );

/**
 * @brief Getting register content
 *
 * @param ctx                Click object. 
 * @param register_address   register address
 * @param register_buffer    register buffer
 * @param n_registers        number of registers
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function gets specified number of registers (max. 4 registers) starting at specified registered address and stores register values into register buffer
 */
uint8_t gyro4_spi_get ( gyro4_t *ctx, uint8_t register_address, uint8_t * register_buffer, uint16_t n_registers );

/**
 * @brief Setting register content
 *
 * @param ctx                Click object. 
 * @param register_address   register address
 * @param data_in            register buffer
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function sets values from register buffer to specified number of registers (max. 1 registers) starting at specified registered address
 */
uint8_t gyro4_spi_set ( gyro4_t *ctx, uint8_t register_address, uint8_t data_in );

/**
 * @brief Device initialization
 *
 * @param ctx        Click object.
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @note        
 * <pre>
 *       This function initializes the device
 *       This function sets _GYRO4_REG_CTRL1_OIS register value to 0x4B
 *       This function sets _GYRO4_REG_CTRL2_OIS register value to 0x00
 *       This function sets _GYRO4_REG_CTRL3_OIS register value to 0x02
 *       This function sets _GYRO4_REG_CTRL4_OIS register value to 0x10
 *       This function sets _GYRO4_REG_OIS_CFG register value to 0x08
 *</pre>
 */
uint8_t gyro4_initialize ( gyro4_t *ctx );

/**
 * @brief Getting die temperature value
 *
 * @param ctx                Click object.  
 * @param temperature        temperature value
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @desrciption This function gets values of temperature registers and convets those values to [deg C]
 */
uint8_t gyro4_get_temperature ( gyro4_t *ctx, float * temperature );

/**
 * @brief Getting axes values
 *
 * @param ctx                Click object. 
 * @param x_axis             X axis value
 * @param y_axis             Y axis value
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function gets values from axes registers and converts those values to [deg/s]
 */
uint8_t gyro4_get_axes( gyro4_t *ctx, float * x_axis, float * y_axis );

/**
 * @brief Performing software reset
 *
 * @param ctx                Click object. 
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function activates software reset and makes 1 second delay
 */
uint8_t gyro4_software_reset ( gyro4_t *ctx );

/**
 *
 * @brief Setting power mode
 *
 * @param ctx                Click object. 
 * @param power_mode         power mode (use macros)
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function sets power mode to POWER DOWN, SLEEP or NORMAL mode
 */
uint8_t gyro4_set_power_mode ( gyro4_t *ctx, uint8_t power_mode );

/**
 * @brief Settinf full scale range
 *
 * @param ctx                Click object. 
 * @param full_scale_range   Full scale range (use macros)
 *
 * @returns 0 for successful operation
 * @returns 1 for unsuccessful operation
 *
 * @description This function sets full scale range to plus/minus 100 or plus/minus 200 degrees per second
 */
uint8_t gyro4_set_full_scale_range( gyro4_t *ctx, uint8_t full_scale_range );

#ifdef __cplusplus
}
#endif
#endif  // _GYRO4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

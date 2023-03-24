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
 * \brief This file contains API for Thermo 9 Click driver.
 *
 * \addtogroup thermo9 Thermo 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO9_H
#define THERMO9_H

#include "drv_digital_out.h"
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

#define THERMO9_MAP_MIKROBUS( cfg, mikrobus )       \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ) 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define THERMO9_MASTER_I2C 0
#define THERMO9_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO9_RETVAL  uint8_t

#define THERMO9_OK           0x00
#define THERMO9_INIT_ERROR   0xFF
/** \} */
/**
 * \defgroup slave_adr Slave addresses
 * \{
 */
#define THERMO9_ADDR_VCC   0x76
#define THERMO9_ADDR_GND   0x77
/** \} */

/**
 * \defgroup cmd Commands
 * \{
 */
#define THERMO9_DUMMY_BYTE                       0x00
#define THERMO9_RESET_CMD                        0x1E
#define THERMO9_START_ADC_TEMP_CONV              0x48
#define THERMO9_READ_ADC_TEMP_RES                0x00
#define THERMO9_PROM_READ_ADR_0                  0xA0
#define THERMO9_PROM_READ_ADR_1_COEF_K4          0xA2
#define THERMO9_PROM_READ_ADR_2_COEF_K3          0xA4
#define THERMO9_PROM_READ_ADR_3_COEF_K2          0xA6
#define THERMO9_PROM_READ_ADR_4_COEF_K1          0xA8
#define THERMO9_PROM_READ_ADR_5_COEF_K0          0xAA
#define THERMO9_PROM_READ_ADR_6_SN23_8           0xAC
#define THERMO9_PROM_READ_ADR_7_SN7_0_CHECKSUM   0xAE
/** \} */

/**
 * \defgroup coef_calc Coefficient Calculations
 * \{
 */
#define THERMO9_COEF_CALC_4_2                    -2
#define THERMO9_COEF_CALC_3                      4
#define THERMO9_COEF_CALC_0                      -1.5
#define THERMO9_CALC_COEF_4                      1000000000000000000000.0
#define THERMO9_CALC_COEF_3                      10000000000000000.0
#define THERMO9_CALC_COEF_2                      100000000000.0
#define THERMO9_CALC_COEF_1                      1000000.0
#define THERMO9_CALC_COEF_0                      100.0
#define THERMO9_RES_MOD                          256.0
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
typedef uint8_t  thermo9_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *thermo9_master_io_t )( struct thermo9_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Temperature calibration coefficient.
 */
typedef struct
{
     uint16_t coef0;
     uint16_t coef1;
     uint16_t coef2;
     uint16_t coef3;
     uint16_t coef4;

} thermo9_temp_coef_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct thermo9_s
{
    // Output pins 
    
    digital_out_t cs;

    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    thermo9_master_io_t  write_f;
    thermo9_master_io_t  read_f;
    thermo9_select_t master_sel;
    
   // Temperature calibration coefficient 
    
    thermo9_temp_coef_t temp_coef;

} thermo9_t;

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

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   thermo9_select_t sel;

} thermo9_cfg_t;

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
void thermo9_cfg_setup ( thermo9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO9_RETVAL thermo9_init ( thermo9_t *ctx, thermo9_cfg_t *cfg );

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
void thermo9_generic_write ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                             uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void thermo9_generic_read ( thermo9_t *ctx, uint8_t reg, uint8_t *data_buf, 
                            uint8_t len );

/**
 * @brief Send command function
 *
 * @param ctx      Click object.
 * @param cmd_byte  Command Byte.
 *
 * @description Function is used to send the command to the device.
**/
void thermo9_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte );

/**
 * @brief Calibration function
 *
 * @param ctx      Click object.
 * 
 * @description Function resets and calibrates the device in order for it to work properly.
 * @note This function must be used once in order to get calibrations!
**/
void thermo9_calibation ( thermo9_t *ctx );

/**
 * @brief Read temperature function
 *
 * @param ctx      Click object.
 * 
 * @returns result float temperature value in degree centigrade.
 *
 * @description Function is used to read temperature in degree centigrade.
**/
float thermo9_read_temp ( thermo9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

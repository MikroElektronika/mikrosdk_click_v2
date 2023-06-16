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
 * \brief This file contains API for Pressure 4 Click driver.
 *
 * \addtogroup pressure4 Pressure 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE4_H
#define PRESSURE4_H

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

#define PRESSURE4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define PRESSURE4_MASTER_I2C                0
#define PRESSURE4_MASTER_SPI                1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE4_OK                        0
#define PRESSURE4_ERROR                    -1
/** \} */

/**
 * \defgroup addr Addr
 * \{
 */
#define PRESSURE4_ADDR0                     0x76
#define PRESSURE4_ADDR1                     0x77
#define PRESSURE4_ID                        0xD0
#define PRESSURE4_RESET                     0xE0
#define PRESSURE4_STATUS                    0xF3
#define PRESSURE4_CTL_MEAS                  0xF4
#define PRESSURE4_CONFIG                    0xF5
#define PRESSURE4_PRESS_MSB                 0xF7
#define PRESSURE4_PRESS_LSB                 0xF8
#define PRESSURE4_PRESS_XLSB                0xF9
#define PRESSURE4_TEMP_MSB                  0xFA
#define PRESSURE4_TEMP_LSB                  0xFB
#define PRESSURE4_TEMP_XLSB                 0xFC
/** \} */

/**
 * \defgroup calibration_dig Calibration Dig
 * \{
 */
#define PRESSURE4_CALIBRATION_DIG_T1        0x88
#define PRESSURE4_CALIBRATION_DIG_T2        0x8A
#define PRESSURE4_CALIBRATION_DIG_T3        0x8C
#define PRESSURE4_CALIBRATION_DIG_P1        0x8E
#define PRESSURE4_CALIBRATION_DIG_P2        0x90
#define PRESSURE4_CALIBRATION_DIG_P3        0x92
#define PRESSURE4_CALIBRATION_DIG_P4        0x94
#define PRESSURE4_CALIBRATION_DIG_P5        0x96
#define PRESSURE4_CALIBRATION_DIG_P6        0x98
#define PRESSURE4_CALIBRATION_DIG_P7        0x9A
#define PRESSURE4_CALIBRATION_DIG_P8        0x9C
#define PRESSURE4_CALIBRATION_DIG_P9        0x9E
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Master Input/Output type.
 */
typedef void ( *pressure4_master_io_t )( struct pressure4_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct pressure4_s
{   
    // Output pins 
    digital_out_t cs;

    // Modules 
    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 
    uint8_t slave_address;
    pin_name_t chip_select;
    pressure4_master_io_t write_f;
    pressure4_master_io_t read_f;
    uint8_t master_sel;
    
    uint16_t dig_t1;
    int16_t  dig_t2;
    int16_t  dig_t3;
    
    uint16_t dig_p1;
    int16_t  dig_p2;
    int16_t  dig_p3;
    int16_t  dig_p4;
    int16_t  dig_p5;
    int16_t  dig_p6;
    int16_t  dig_p7;
    int16_t  dig_p8;
    int16_t  dig_p9;
    
    int32_t t_fine;
    float t1_calc_1;
    float p3_calc_1;

} pressure4_t;

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

    uint8_t sel;

} pressure4_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void pressure4_cfg_setup ( pressure4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t pressure4_init ( pressure4_t *ctx, pressure4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for Pressure 4 click.
 */
void pressure4_default_cfg ( pressure4_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @details This function writes data to the desired register.
 */
void pressure4_generic_write ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function reads data from the desired register.
 */
void pressure4_generic_read ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief 8 bit writing function.
 *
 * @param ctx        Click object.
 * @param w_reg      Register address.
 * @param w_data     Data to be written.
 *
 * @details This function writes 8 bit to Pressure 4 registers.
 */
void pressure4_write_reg_8_bit ( pressure4_t *ctx, uint8_t w_reg, uint8_t w_data );

/**
 * @brief 8 bit reading function.
 *
 * @param ctx        Click object.
 * @param r_reg      Register address.
 *
 * @details This function reads 8 bit to Pressure 4 registers.
 */
uint8_t pressure4_read_reg_8_bit ( pressure4_t *ctx, uint8_t r_reg );

/**
 * @brief Read ID function.
 *
 * @param ctx        Click object.
 *
 * @details This function returns the contents of the chipid register.
 */
uint8_t pressure4_read_id ( pressure4_t *ctx );

/**
 * @brief Get status function.
 *
 * @param ctx        Click object.
 *
 * @details This function returning the state of the status register.
 */
uint8_t pressure4_get_status ( pressure4_t *ctx );

/**
 * @brief Get temperature function.
 *
 * @param ctx        Click object.
 *
 * @details This function returning the calculated temperature value.
 */
float pressure4_get_temperature ( pressure4_t *ctx );

/**
 * @brief Get pressure function.
 *
 * @param ctx        Click object.
 *
 * @details This function returning the calculated value of the pressure.
 */
float pressure4_get_pressure ( pressure4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for 3D Hall 3 Click driver.
 *
 * \addtogroup c3dhall3 3D Hall 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3DHALL3_H
#define C3DHALL3_H

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

#define C3DHALL3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.ccs   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C3DHALL3_MASTER_I2C 0
#define C3DHALL3_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C3DHALL3_RETVAL  uint8_t

#define C3DHALL3_OK           0x00
#define C3DHALL3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_addresses Register Addresses
 * \{
 */
#define C3DHALL3_OFFSET_X_REG_L                          0x45 
#define C3DHALL3_OFFSET_Y_REG_L                          0x47 
#define C3DHALL3_OFFSET_Z_REG_L                          0x49 
#define C3DHALL3_INT_CRTL                                0x63 
#define C3DHALL3_INT_SOURCE                              0x64 
#define C3DHALL3_INT_THS_L                               0x65 
#define C3DHALL3_STATUS                                  0x67 
#define C3DHALL3_OUTX_L                                  0x68 
#define C3DHALL3_OUTY_L                                  0x6A 
#define C3DHALL3_OUTZ_L                                  0x6C 
#define C3DHALL3_CONFIGURATION_REGISTER_A                0x60 
#define C3DHALL3_CONFIGURATION_REGISTER_B                0x61 
#define C3DHALL3_CONFIGURATION_REGISTER_C                0x62 
#define C3DHALL3_INTERRUPT_CONTROL                       0x63 
#define C3DHALL3_TEMPERATURE_L                           0x6E 
#define C3DHALL3_TEMPERATURE_H                           0x6F 
/** \} */

/**
 * \defgroup cfg_a_register_bits CFG-A Register bits
 * \{
 */
#define C3DHALL3_CFGA_TEMPERATURE_COMPENSATION           0x80 
#define C3DHALL3_CFGA_REBOOT_MEMORY                      0x40 
#define C3DHALL3_CFGA_SOFT_RESET                         0x20 
#define C3DHALL3_CFGA_LOW_POWER_MODE                     0x10 
#define C3DHALL3_CFGA_OUTPUT_DATA_RATE_10                0x00 
#define C3DHALL3_CFGA_OUTPUT_DATA_RATE_20                0x04 
#define C3DHALL3_CFGA_OUTPUT_DATA_RATE_50                0x08 
#define C3DHALL3_CFGA_OUTPUT_DATA_RATE_100               0x0C 
#define C3DHALL3_CFGA_MODE_CONTINIOUS                    0x00 
#define C3DHALL3_CFGA_MODE_SINGLE                        0x01 
#define C3DHALL3_CFGA_MODE_IDLE                          0x02 
#define C3DHALL3_CFGA_MODE_IDLE_DEFAULT                  0x03 
/** \} */
/**
 * \defgroup cfg_b_register_bits CFG-B Register bits
 * \{
 */
#define C3DHALL3_CFGB_OFFSET_CANCELLATION_SINGLE_MODE    0x10 
#define C3DHALL3_CFGB_INT_ON_DATAOFF                     0x08 
#define C3DHALL3_CFGB_SET_PULSE_FREQUENCY_EVERY_63_ODR   0x00 
#define C3DHALL3_CFGB_SET_PULSE_FREQUENCY_AFTER_PD       0x04 
#define C3DHALL3_CFGB_OFFSET_CANCELLATION                0x02 
#define C3DHALL3_CFGB_LOW_PASS_FILTER_ODR_2              0x00 
#define C3DHALL3_CFGB_LOW_PASS_FILTER_ODR_4              0x01 
/** \} */

/**
 * \defgroup cfg_c_register_bits CFG-C Register bits
 * \{
 */
#define C3DHALL3_CFGC_INTERRUPT_ON_INT            0x40 
#define C3DHALL3_CFGC_I2C_DISABLE                 0x20 
#define C3DHALL3_CFGC_ASYNC_DATA_READ             0x10 
#define C3DHALL3_CFGC_DATA_INVERT                 0x08 
#define C3DHALL3_CFGC_SELF_TEST                   0x02 
#define C3DHALL3_CFGC_DATA_READY_ON_INT           0x01 
/** \} */

/**
 * \defgroup int_control_registers Int control registers
 * \{
 */
#define C3DHALL3_INTCTRL_INTERRUPT_ON_X_AXIS            0x80 
#define C3DHALL3_INTCTRL_INTERRUPT_ON_Y_AXIS            0x40 
#define C3DHALL3_INTCTRL_INTERRUPT_ON_Z_AXIS            0x20 
#define C3DHALL3_INTCTRL_INTERRUPT_POLARITY_LOW         0x00 
#define C3DHALL3_INTCTRL_INTERRUPT_POLARITY_HIGH        0x40 
#define C3DHALL3_INTCTRL_INTERRUPT_BIT_LATCHED          0x00 
#define C3DHALL3_INTCTRL_INTERRUPT_BIT_PULSED           0x20 
#define C3DHALL3_INTCTRL_INTERRUPT_ENABLE               0x01 
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
typedef uint8_t  c3dhall3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c3dhall3_master_io_t )( struct c3dhall3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c3dhall3_s
{
    // Output pins 

    digital_out_t ccs;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c3dhall3_master_io_t  write_f;
    c3dhall3_master_io_t  read_f;
    c3dhall3_select_t master_sel;

} c3dhall3_t;

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
    
    // Additional gpio pins 

    pin_name_t ccs;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;    

    c3dhall3_select_t sel;

} c3dhall3_cfg_t;

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
void c3dhall3_cfg_setup ( c3dhall3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c3dhall3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C3DHALL3_RETVAL c3dhall3_init ( c3dhall3_t *ctx, c3dhall3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 3D Hall 3 click.
 */
void c3dhall3_default_cfg ( c3dhall3_t *ctx );

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
void c3dhall3_generic_write ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c3dhall3_generic_read ( c3dhall3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read status register
 *
 * @param ctx      Click object.
 *
 * @description This function reads status from the register.
 */
uint8_t c3dhall3_read_status ( c3dhall3_t *ctx );

/**
 * @brief Read X value
 *
 * @param ctx      Click object.
 *
 * @description This function reads x value from the module.
 */
int16_t c3dhall3_read_x ( c3dhall3_t *ctx );

/**
 * @brief Read Y value
 *
 * @param ctx      Click object.
 *
 * @description This function reads y value from the module.
 */
int16_t c3dhall3_read_y ( c3dhall3_t *ctx );

/**
 * @brief Read Z value
 *
 * @param ctx      Click object.
 *
 * @description This function reads z value from the module.
 */
int16_t c3dhall3_read_z ( c3dhall3_t *ctx );

/**
 * @brief Read XYZ value
 *
 * @param ctx      Click object.
 * @param out_xyz  XYZ register
 *
 * @description This function reads xyz values from the module.
 */
void c3dhall3_read_xyz ( c3dhall3_t *ctx, int16_t *out_xyz );

/**
 * @brief Write offset value
 *
 * @param ctx      Click object.
 * @param axis     Axis value
 * @param offset   Offset value
 *
 * @description This function writes offest values to the module.
 */
void c3dhall3_write_offset (c3dhall3_t *ctx, uint8_t axis, uint16_t offset );

/**
 * @brief Read interrupt source
 *
 * @param ctx      Click object.
 *
 * @description This function returns interrupt source value.
 */
uint8_t c3dhall3_read_interrupt_source ( c3dhall3_t *ctx );

/**
 * @brief Set Interrupt Threshold
 *
 * @param ctx      Click object.
 * @param threshold Threshold value
 *
 * @description This function sets desired threshold value.
 */
void c3dhall3_interrupt_threshold ( c3dhall3_t *ctx, uint16_t threshold );

/**
 * @brief Check status of the int pin
 *
 * @param ctx      Click object.
 *
 * @description This function gets status of the interrupt pin.
 */
uint8_t c3dhall3_check_int_pin ( c3dhall3_t *ctx );
#ifdef __cplusplus
}
#endif
#endif  // _C3DHALL3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

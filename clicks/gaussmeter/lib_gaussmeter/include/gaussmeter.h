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
 * \brief This file contains API for Gaussmeter Click driver.
 *
 * \addtogroup gaussmeter Gaussmeter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GAUSSMETER_H
#define GAUSSMETER_H

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

#define GAUSSMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.trg     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup select_communication Select Communication
 * \{
 */
#define GAUSSMETER_MASTER_I2C 0
#define GAUSSMETER_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GAUSSMETER_RETVAL  uint8_t

#define GAUSSMETER_OK           0x00
#define GAUSSMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define GAUSSMETER_CONFIG1_REG                   0x00 
#define GAUSSMETER_CONFIG2_REG                   0x01 
#define GAUSSMETER_CONFIG3_REG                   0x02 
#define GAUSSMETER_CONFIG4_REG                   0x03 
#define GAUSSMETER_OFFSET_X_REG                  0x04 
#define GAUSSMETER_OFFSET_Y_REG                  0x05 
#define GAUSSMETER_OFFSET_Z_REG                  0x06 
#define GAUSSMETER_WOCXY_THRESHOLD_REG           0x07 
#define GAUSSMETER_WOCZ_THRESHOLD_REG            0x08 
#define GAUSSMETER_WOCT_THRESHOLD_REG            0x09 

#define GAUSSMETER_GAIN_0                        0x0000 
#define GAUSSMETER_GAIN_1                        0x0010 
#define GAUSSMETER_GAIN_2                        0x0020 
#define GAUSSMETER_GAIN_3                        0x0030 
#define GAUSSMETER_GAIN_4                        0x0040 
#define GAUSSMETER_GAIN_5                        0x0050 
#define GAUSSMETER_GAIN_6                        0x0060 
#define GAUSSMETER_GAIN_7                        0x0070 
#define GAUSSMETER_BUILT_IN_SELF_TEST_DIS        0x0000 
#define GAUSSMETER_BUILT_IN_SELF_TEST_EN         0x0100 
#define GAUSSMETER_DIS_Z_MEASURE_PLATES          0x0000 
#define GAUSSMETER_EN_Z_MEASURE_PLATES           0x0080 
#define GAUSSMETER_TRIG_MODE                     0x0000 
#define GAUSSMETER_INT_MODE                      0x8000 
#define GAUSSMETER_SPI_ONLY                      0x4000 
#define GAUSSMETER_I2C_ONLY                      0x0600 
#define GAUSSMETER_BOTH_DRIVER                   0x0000 
#define GAUSSMETER_WOC_DIFF_DIS                  0x0000 
#define GAUSSMETER_WOC_DIFF_EN                   0x1000 
#define GAUSSMETER_EXT_TRIG_DIS                  0x0000 
#define GAUSSMETER_EXT_TRIG_EN                   0x0800 
#define GAUSSMETER_TCMP_DIS                      0x0000 
#define GAUSSMETER_TCMP_EN                       0x0400 
#define GAUSSMETER_RES_0                         0x0000 
#define GAUSSMETER_RES_1                         0x0020 
#define GAUSSMETER_RES_2                         0x0040 
#define GAUSSMETER_RES_3                         0x0060 

#define GAUSSMETER_START_BURST_MODE_COMM         0x10 
#define GAUSSMETER_START_WOC_MODE_COMM           0x20 
#define GAUSSMETER_START_SINGLE_MEAS_MODE_COMM   0x30 
#define GAUSSMETER_READ_MEAS_COMM                0x40 
#define GAUSSMETER_READ_REG_COMM                 0x50 
#define GAUSSMETER_WRITE_REG_COMM                0x60 
#define GAUSSMETER_EXIT_MODE_COMM                0x80 
#define GAUSSMETER_MEM_RECALL_COMM               0xD0 
#define GAUSSMETER_MEM_STORE_COMM                0xE0 
#define GAUSSMETER_RESET_COMM                    0xF0 

#define GAUSSMETER_EN_Z_AXIS                     0x01 
#define GAUSSMETER_DIS_Z_AXIS                    0x00 
#define GAUSSMETER_EN_Y_AXIS                     0x01 
#define GAUSSMETER_DIS_Y_AXIS                    0x00 
#define GAUSSMETER_EN_X_AXIS                     0x01 
#define GAUSSMETER_DIS_X_AXIS                    0x00 
#define GAUSSMETER_EN_TEMP_MEAS                  0x01 
#define GAUSSMETER_DIS_TEMP_MEAS                 0x00 

#define GAUSSMETER_EN_SPI_DRIVER                 0x00 
#define GAUSSMETER_DIS_SPI_DRIVER                0x01                          
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
typedef uint8_t  gaussmeter_select_t;

/**
 * @brief Master Input/Output type.
 */
struct gaussmeter_s;
typedef void ( *gaussmeter_master_io_t )( struct gaussmeter_s*, uint8_t*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Axis object definition.
 */
typedef struct 
{
   uint8_t x;
   uint8_t y;
   uint8_t z;
   
} gaussmeter_axis_t;

/**
 * @brief Auxiliary object definition.
 */
typedef struct
{
   uint8_t command_byte_low;
   uint16_t select_gain;
   uint16_t select_res;

} gaussmeter_aux_t;

/**
 * @brief Click ctx object definition.
 */
 typedef struct gaussmeter_s
{
   // Output pins 
   
   digital_out_t cs;

   // Input pins 

   digital_in_t trg;
   digital_in_t int_pin;
   
   // Modules 

   i2c_master_t i2c;
   spi_master_t spi;

   // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   gaussmeter_master_io_t  data_transfer_f;
   gaussmeter_select_t master_sel;

   gaussmeter_aux_t aux;
   gaussmeter_axis_t axis;

} gaussmeter_t;

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

    pin_name_t trg;
    pin_name_t int_pin;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   gaussmeter_select_t sel;
   gaussmeter_aux_t aux;

} gaussmeter_cfg_t;

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
void gaussmeter_cfg_setup ( gaussmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gaussmeter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GAUSSMETER_RETVAL gaussmeter_init ( gaussmeter_t *ctx, gaussmeter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Gaussmeter click.
 */
void gaussmeter_default_cfg ( gaussmeter_t *ctx );

/**
 * @brief Write register function.
 *
 * @param ctx             Click object.
 * @param reg_addr        Register address value.
 * @param transfer_data   Data to be transfered.
 *
 * @description This function writes 16-bit data to the specified register address.
 */
uint8_t gaussmeter_write_reg ( gaussmeter_t *ctx, uint8_t reg_addr, uint16_t transfer_data );

/**
 * @brief Send command function.
 *
 * @param ctx        Click object.
 * @param command    Command value.
 *
 * @description This function sends a single specified command to the chip and checks for
 *              communication errors.
 */
uint8_t gaussmeter_send_command ( gaussmeter_t *ctx, uint8_t command );

/**
 * @brief Enable measure function.
 *
 * @param ctx    Click object.
 * @param temp   Command value.
 *
 * @description This function enables the measurement function on the chip.
 */
void gaussmeter_enable_measure ( gaussmeter_t *ctx, uint8_t temp );

/**
 * @brief Get data function.
 *
 * @param ctx           Click object.
 * @param output_data   Command value.
 *
 * @description This function reads the temperature and axis data from the chip.
 */
uint8_t gaussmeter_get_data( gaussmeter_t *ctx, float *output_data );

/**
 * @brief Generic read function.
 *
 * @param ctx         Click object.
 * @param write_buf   Output data buf
 * @param write_len   Number of the bytes to be written.
 * @param read_buf    Data buf to be written.
 * @param read_len    Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void gaussmeter_generic_data_transfer ( gaussmeter_t *ctx, uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len );

/**
 * @brief Digital read interrupt function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads the digital input signal from the INT pin.
 */
uint8_t gaussmeter_digital_read_int ( gaussmeter_t *ctx );

/**
 * @brief Digital read pwm function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads the digital input signal from the PWM pin.
 */
uint8_t gaussmeter_digital_read_pwm ( gaussmeter_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _GAUSSMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

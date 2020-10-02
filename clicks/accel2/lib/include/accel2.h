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
 * \brief This file contains API for Accel 2 Click driver.
 *
 * \addtogroup accel2 Accel 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL2_H
#define ACCEL2_H

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

#define ACCEL2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL2_MASTER_I2C 0
#define ACCEL2_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL2_RETVAL  uint8_t

#define ACCEL2_OK           0x00
#define ACCEL2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_addres_map    Register Address Map
 * \{
 */
#define ACCEL2_INFO1        0x0D
#define ACCEL2_INFO2        0x0E
#define ACCEL2_WHO_AM_I     0x0F
#define ACCEL2_CTRL_REG3    0x23
#define ACCEL2_CTRL_REG4    0x20
#define ACCEL2_CTRL_REG5    0x24
#define ACCEL2_CTRL_REG6    0x25
#define ACCEL2_STATUS       0x27
#define ACCEL2_OUT_T        0x0C
#define ACCEL2_OFF_X        0x10
#define ACCEL2_OFF_Y        0x11
#define ACCEL2_OFF_Z        0x12
#define ACCEL2_CS_X         0x13
#define ACCEL2_CS_Y         0x14
#define ACCEL2_CS_Z         0x15
#define ACCEL2_LC_L         0x16
#define ACCEL2_LC_H         0x17
#define ACCEL2_STAT         0x18
#define ACCEL2_VFC_1        0x1B
#define ACCEL2_VFC_2        0x1C
#define ACCEL2_VFC_3        0x1D
#define ACCEL2_VFC_4        0x1E
#define ACCEL2_THRS3        0x1F
#define ACCEL2_OUT_X_L      0x28
#define ACCEL2_OUT_X_H      0x29
#define ACCEL2_OUT_Y_L      0x2A
#define ACCEL2_OUT_Y_H      0x2B
#define ACCEL2_OUT_Z_L      0x2C
#define ACCEL2_OUT_Z_H      0x2D
#define ACCEL2_FIFO_CTRL    0x2E
#define ACCEL2_FIFO_SRC     0x2F
#define ACCEL2_CTRL_REG1    0x21
#define ACCEL2_ST1_1        0x40
#define ACCEL2_ST2_1        0x41
#define ACCEL2_ST3_1        0x42
#define ACCEL2_ST4_1        0x43
#define ACCEL2_ST5_1        0x44
#define ACCEL2_ST6_1        0x45
#define ACCEL2_ST7_1        0x46
#define ACCEL2_ST8_1        0x47
#define ACCEL2_ST9_1        0x48
#define ACCEL2_ST10_1       0x49
#define ACCEL2_ST11_1       0x4A
#define ACCEL2_ST12_1       0x4B
#define ACCEL2_ST13_1       0x4C
#define ACCEL2_ST14_1       0x4D
#define ACCEL2_ST15_1       0x4E
#define ACCEL2_ST16_1       0x4F
#define ACCEL2_TIM4_1       0x50
#define ACCEL2_TIM3_1       0x51
#define ACCEL2_TIM2_1_L     0x52
#define ACCEL2_TIM2_1_H     0x53
#define ACCEL2_TIM1_1_L     0x54
#define ACCEL2_TIM1_1_H     0x55
#define ACCEL2_THRS2_1      0x56
#define ACCEL2_THRS1_1      0x57
#define ACCEL2_MASK1_B      0x59
#define ACCEL2_MASK1_A      0x5A
#define ACCEL2_SETT1        0x5B
#define ACCEL2_PR1          0x5C
/** \} */

/**
 * \defgroup addres   Address
 * \{
 */
#define ACCEL2_I2C_ADDRESS   = 0x1D
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
typedef uint8_t  accel2_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel2_master_io_t )( struct accel2_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel2_s
{
   // Output pins 
   digital_out_t cs;

   // Input pins 

   digital_in_t int_pin;
   
   // Modules 

   i2c_master_t i2c;
   spi_master_t spi;

   // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   accel2_master_io_t  write_f;
   accel2_master_io_t  read_f;
   accel2_select_t master_sel;

} accel2_t;

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

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    uint32_t spi_speed;
    uint8_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   accel2_select_t sel;

} accel2_cfg_t;

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
void accel2_cfg_setup ( accel2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param accel2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL2_RETVAL accel2_init ( accel2_t *ctx, accel2_cfg_t *cfg );

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
void accel2_generic_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void accel2_generic_read ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Initializes function.
 *
 * @param ctx      Click object.
 *
 * @description This function initializes Accel 2 register.
 */
void accel2_setting ( accel2_t *ctx );

/**
 * @brief Check Accel 2 ID.
 *
 * @param ctx      Click object.
 *
 * @description This function check Accel 2 ID.
 */
uint8_t accel2_check_id ( accel2_t *ctx );

/**
 * @brief Function read X axis.
 *
 * @param ctx      Click object.
 *
 * @description This function read X axis from Accel 2.
 */
int16_t accel2_read_xaxis ( accel2_t *ctx );

/**
 * @brief Function read Y axis.
 *
 * @param ctx      Click object.
 *
 * @description This function read Y axis from Accel 2.
 */
int16_t accel2_read_yaxis ( accel2_t *ctx );

/**
 * @brief Function read Z axis.
 *
 * @param ctx      Click object.
 *
 * @description This function read Z axis from Accel 2.
 */
int16_t accel2_read_zaxis ( accel2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for PRESSURE 11 Click driver.
 *
 * \addtogroup pressure11 PRESSURE 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE11_H
#define PRESSURE11_H

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

#define PRESSURE11_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define PRESSURE11_MASTER_I2C 0
#define PRESSURE11_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE11_RETVAL  uint8_t

#define PRESSURE11_OK              0x00
#define PRESSURE11_INIT_ERROR      0xFF

#define DEVICE_ERROR               0x02
#define DEVICE_OK                  0x00
/** \} */

/**
 * \defgroup chip_id    Chip ID
 * \{
 */
#define PRESSURE11_I_AM                                     0xB1
/** \} */

/**
 * \defgroup registers    Registers
 * \{
 */
#define PRESSURE11_REG_INTERRUPT                            0x0B
#define PRESSURE11_REG_THS_P_L                              0x0C
#define PRESSURE11_REG_THS_P_H                              0x0D
#define PRESSURE11_REG_WHO_AM_I                             0x0F
#define PRESSURE11_REG_CTRL_REG1                            0x10
#define PRESSURE11_REG_CTRL_REG2                            0x11
#define PRESSURE11_REG_CTRL_REG3                            0x12
#define PRESSURE11_REG_FIFO_CTRL                            0x14
#define PRESSURE11_REG_REF_P_XL                             0x15
#define PRESSURE11_REG_REF_P_L                              0x16
#define PRESSURE11_REG_REF_P_H                              0x17
#define PRESSURE11_REG_RPDS_L                               0x18
#define PRESSURE11_REG_RPDS_H                               0x19
#define PRESSURE11_REG_RES_CONF                             0x1A
#define PRESSURE11_REG_INT_SOURCE                           0x25
#define PRESSURE11_REG_FIFO_STATUS                          0x26
#define PRESSURE11_REG_STATUS                               0x27
#define PRESSURE11_REG_PRESS_OUT_XL                         0x28
#define PRESSURE11_REG_PRESS_OUT_L                          0x29
#define PRESSURE11_REG_PRESS_OUT_H                          0x2A
#define PRESSURE11_REG_TEMP_OUT_L                           0x2B
#define PRESSURE11_REG_TEMP_OUT_H                           0x2C
#define PRESSURE11_REG_LPFP_RES                             0x33
/** \} */

/**
 * \defgroup interrupt_configuration    Interrupt Configuration
 * \{
 */
#define PRESSURE11_CFG_INTERRUPT_AUTORIFP                   0x80
#define PRESSURE11_CFG_INTERRUPT_RESET_ARP                  0x40
#define PRESSURE11_CFG_INTERRUPT_AUTOZERO                   0x20
#define PRESSURE11_CFG_INTERRUPT_RESET_AZ                   0x10
#define PRESSURE11_CFG_INTERRUPT_DIFF_EN                    0x08
#define PRESSURE11_CFG_INTERRUPT_LIR                        0x04
#define PRESSURE11_CFG_INTERRUPT_PLE                        0x02
#define PRESSURE11_CFG_INTERRUPT_PHE                        0x01
#define PRESSURE11_CFG_INTERRUPT_DISABLE_ALL                0x00
/** \} */

/**
 * \defgroup control_register_1    Control Register 1
 * \{
 */
#define PRESSURE11_CTRL_1_ODR_1_HZ                          0x10
#define PRESSURE11_CTRL_1_ODR_10_HZ                         0x20
#define PRESSURE11_CTRL_1_ODR_25_HZ                         0x30
#define PRESSURE11_CTRL_1_ODR_50_HZ                         0x40
#define PRESSURE11_CTRL_1_ODR_75_HZ                         0x50
#define PRESSURE11_CTRL_1_EN_LPFP                           0x08
#define PRESSURE11_CTRL_1_LPFP_CFG                          0x04
#define PRESSURE11_CTRL_1_BDU                               0x02
#define PRESSURE11_CTRL_1_SIM                               0x01
#define PRESSURE11_CTRL_1_DISABLE_ALL                       0x00
/** \} */

/**
 * \defgroup control_register_2    Control Register 2
 * \{
 */
#define PRESSURE11_CTRL_2_BOOT                              0x80
#define PRESSURE11_CTRL_2_FIFO_EN                           0x40
#define PRESSURE11_CTRL_2_STOP_ON_FTH                       0x20
#define PRESSURE11_CTRL_2_IF_ADD_INC                        0x10
#define PRESSURE11_CTRL_2_I2C_DIS                           0x08
#define PRESSURE11_CTRL_2_SWRESET                           0x04
#define PRESSURE11_CTRL_2_ONE_SHOT                          0x01
#define PRESSURE11_CTRL_2_DISABLE_ALL                       0x00
/** \} */

/**
 * \defgroup control_register_3    Control Register 3
 * \{
 */
#define PRESSURE11_CTRL_3_INT_H_L                           0x80
#define PRESSURE11_CTRL_3_PP_OD                             0x40
#define PRESSURE11_CTRL_3_F_FSS5                            0x20
#define PRESSURE11_CTRL_3_F_FTH                             0x10
#define PRESSURE11_CTRL_3_F_OVR                             0x08
#define PRESSURE11_CTRL_3_DRDY                              0x04
#define PRESSURE11_CTRL_3_INT_PRESS_LOW_OR_HIGH             0x03
#define PRESSURE11_CTRL_3_INT_PRESS_LOW                     0x02
#define PRESSURE11_CTRL_3_INT_PRESS_HIGH                    0x01
#define PRESSURE11_CTRL_3_DISABLE_ALL                       0x00
/** \} */

/**
 * \defgroup fifo_control_register    Control Register
 * \{
 */
#define PRESSURE11_CTRL_FIFO_BYPASS_TO_FIFO_MODE            0xE0
#define PRESSURE11_CTRL_FIFO_DYNAMIC_STREAM_MODE            0xC0
#define PRESSURE11_CTRL_FIFO_BYPASS_TO_STREAM_MODE          0x80
#define PRESSURE11_CTRL_FIFO_STREAM_TO_FIFO_MODE            0x60
#define PRESSURE11_CTRL_FIFO_STREAM_MODE                    0x40
#define PRESSURE11_CTRL_FIFO_FIFO_MODE                      0x20
#define PRESSURE11_CTRL_FIFO_BYPASS_MODE                    0x00
/** \} */  

/**
 * \defgroup interrupt_source    Interrupt Source
 * \{
 */
#define PRESSURE11_INT_SOURCE_BOOT_STATUS                   0x80
#define PRESSURE11_INT_SOURCE_IA                            0x04
#define PRESSURE11_INT_SOURCE_PL                            0x02
#define PRESSURE11_INT_SOURCE_PH                            0x01
/** \} */

/**
 * \defgroup fifo_status_register    FIFO Status Register
 * \{
 */
#define PRESSURE11_STATUS_FTH_FIFO                                  0x80
#define PRESSURE11_STATUS_OVR                                       0x40
#define PRESSURE11_STATUS_FIFO_32_UNREAD_SAMPLES                    0x20
#define PRESSURE11_STATUS_FIFO_31_UNREAD_SAMPLES                    0x1F
#define PRESSURE11_STATUS_FIFO_30_UNREAD_SAMPLES                    0x1E
#define PRESSURE11_STATUS_FIFO_29_UNREAD_SAMPLES                    0x1D
#define PRESSURE11_STATUS_FIFO_28_UNREAD_SAMPLES                    0x1C
#define PRESSURE11_STATUS_FIFO_27_UNREAD_SAMPLES                    0x1B
#define PRESSURE11_STATUS_FIFO_26_UNREAD_SAMPLES                    0x1A
#define PRESSURE11_STATUS_FIFO_25_UNREAD_SAMPLES                    0x19
#define PRESSURE11_STATUS_FIFO_24_UNREAD_SAMPLES                    0x18
#define PRESSURE11_STATUS_FIFO_23_UNREAD_SAMPLES                    0x17
#define PRESSURE11_STATUS_FIFO_22_UNREAD_SAMPLES                    0x16
#define PRESSURE11_STATUS_FIFO_21_UNREAD_SAMPLES                    0x15
#define PRESSURE11_STATUS_FIFO_20_UNREAD_SAMPLES                    0x14
#define PRESSURE11_STATUS_FIFO_19_UNREAD_SAMPLES                    0x13
#define PRESSURE11_STATUS_FIFO_18_UNREAD_SAMPLES                    0x12
#define PRESSURE11_STATUS_FIFO_17_UNREAD_SAMPLES                    0x11
#define PRESSURE11_STATUS_FIFO_16_UNREAD_SAMPLES                    0x10
#define PRESSURE11_STATUS_FIFO_15_UNREAD_SAMPLES                    0x0F
#define PRESSURE11_STATUS_FIFO_14_UNREAD_SAMPLES                    0x0E
#define PRESSURE11_STATUS_FIFO_13_UNREAD_SAMPLES                    0x0D
#define PRESSURE11_STATUS_FIFO_12_UNREAD_SAMPLES                    0x0C
#define PRESSURE11_STATUS_FIFO_11_UNREAD_SAMPLES                    0x0B
#define PRESSURE11_STATUS_FIFO_10_UNREAD_SAMPLES                    0x0A
#define PRESSURE11_STATUS_FIFO_9_UNREAD_SAMPLES                     0x09
#define PRESSURE11_STATUS_FIFO_8_UNREAD_SAMPLES                     0x08
#define PRESSURE11_STATUS_FIFO_7_UNREAD_SAMPLES                     0x07
#define PRESSURE11_STATUS_FIFO_6_UNREAD_SAMPLES                     0x06
#define PRESSURE11_STATUS_FIFO_5_UNREAD_SAMPLES                     0x05
#define PRESSURE11_STATUS_FIFO_4_UNREAD_SAMPLES                     0x04
#define PRESSURE11_STATUS_FIFO_3_UNREAD_SAMPLES                     0x03
#define PRESSURE11_STATUS_FIFO_2_UNREAD_SAMPLES                     0x02
#define PRESSURE11_STATUS_FIFO_1_UNREAD_SAMPLES                     0x01
#define PRESSURE11_STATUS_FIFO_EMPTY                                0x00
/** \} */

/**
 * \defgroup fifo_status_register    FIFO Status Register
 * \{
 */
#define PRESSURE11_STATUS_T_OR                                      0x20
#define PRESSURE11_STATUS_P_OR                                      0x10
#define PRESSURE11_STATUS_T_DA                                      0x02
#define PRESSURE11_STATUS_P_DA                                      0x01
/** \} */

/**
 * \defgroup addresses     Addresses
 * \{
 */
#define PRESSURE11_DEVICE_SLAVE_ADDR_GND                            0x5C
#define PRESSURE11_DEVICE_SLAVE_ADDR_VDD                            0x5D
/** \} */

// End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  pressure11_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *pressure11_master_io_t )( struct pressure11_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct pressure11_s
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

   pressure11_master_io_t  write_f;
   pressure11_master_io_t  read_f;
   pressure11_select_t master_sel;

} pressure11_t;

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
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   pressure11_select_t sel;

} pressure11_cfg_t;

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
void pressure11_cfg_setup ( pressure11_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PRESSURE11_RETVAL pressure11_init ( pressure11_t *ctx, pressure11_cfg_t *cfg );

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
void pressure11_generic_write ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void pressure11_generic_read ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for cheking commuincation with the chip and checking its ID.
 *
 * @param ctx  Click object.
 *
 * @description This function is information whether the chip is successfully read or not.
 */
uint8_t pressure11_check_id ( pressure11_t *ctx );

/**
 * @brief Functions for temperature reading.
 *
 * @param ctx  Click object.
 *
 * @description This function is temperature data in Celsius.
 */
float pressure11_get_temperature ( pressure11_t *ctx );

/**
 * @brief Functions for pressure reading.
 *
 * @param ctx  Click object.
 *
 * @description This function is Pressure data in hPa (mBar).
 */
float pressure11_get_pressure ( pressure11_t *ctx );

/**
 * @brief Functions for read int pin.
 *
 * @param ctx  Click object.
 *
 * @description This function is interrupt pin state.
 */
uint8_t pressure11_get_interrupt ( pressure11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

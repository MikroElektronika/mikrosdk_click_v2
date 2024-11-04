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
 * \brief This file contains API for Proximity Click driver.
 *
 * \addtogroup proximity Proximity Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY_H
#define PROXIMITY_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define PROXIMITY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY_RETVAL  uint8_t

#define PROXIMITY_OK           0x00
#define PROXIMITY_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup proximity_registers Proximity registers
 * \{
 */
#define PROXIMITY_SLAVE_ADDR                      0x13
#define PROXIMITY_REGISTER_COMMAND                0x80
#define PROXIMITY_REGISTER_ID                     0x81
#define PROXIMITY_REGISTER_PROX_RATE              0x82
#define PROXIMITY_REGISTER_PROX_CURRENT           0x83
#define PROXIMITY_REGISTER_AMBI_PARAMETER         0x84
#define PROXIMITY_REGISTER_AMBI_VALUE             0x85
#define PROXIMITY_REGISTER_PROX_VALUE             0x87
#define PROXIMITY_REGISTER_INTERRUPT_CONTROL      0x89
#define PROXIMITY_REGISTER_INTERRUPT_LOW_THRES    0x8a
#define PROXIMITY_REGISTER_INTERRUPT_HIGH_THRES   0x8c
#define PROXIMITY_REGISTER_INTERRUPT_STATUS       0x8e
#define PROXIMITY_REGISTER_PROX_TIMING            0xf9
#define PROXIMITY_REGISTER_AMBI_IR_LIGHT_LEVEL    0x90
/** \} */

/**
 * \defgroup proximity_registers Proximity registers
 * \{
 */
#define PROXIMITY_COMMAND_ALL_DISABLE             0x00
#define PROXIMITY_COMMAND_SELFTIMED_MODE_ENABLE   0x01
#define PROXIMITY_COMMAND_PROX_ENABLE             0x02
#define PROXIMITY_COMMAND_AMBI_ENABLE             0x04
#define PROXIMITY_COMMAND_PROX_ON_DEMAND          0x08
#define PROXIMITY_COMMAND_AMBI_ON_DEMAND          0x10
#define PROXIMITY_COMMAND_MASK_PROX_DATA_READY    0x20
#define PROXIMITY_COMMAND_MASK_AMBI_DATA_READY    0x40
#define PROXIMITY_COMMAND_MASK_LOCK               0x80
/** \} */

/**
 * \defgroup product_id Product id and revision
 * \{
 */
#define PROXIMITY_PRODUCT_MASK_REVISION_ID        0x0f
#define PROXIMITY_PRODUCT_MASK_PRODUCT_ID         0xf0
/** \} */

/**
 * \defgroup measurement_rate Measurement rates registers
 * \{
 */
#define PROXIMITY_MEASUREMENT_RATE_2              0x00
#define PROXIMITY_MEASUREMENT_RATE_4              0x01
#define PROXIMITY_MEASUREMENT_RATE_8              0x02
#define PROXIMITY_MEASUREMENT_RATE_16             0x03
#define PROXIMITY_MEASUREMENT_RATE_31             0x04
#define PROXIMITY_MEASUREMENT_RATE_62             0x05
#define PROXIMITY_MEASUREMENT_RATE_125            0x06
#define PROXIMITY_MEASUREMENT_RATE_250            0x07
#define PROXIMITY_MASK_MEASUREMENT_RATE           0x07
/** \} */

/**
 * \defgroup measurement_rate Measurement rates registers
 * \{
 */
#define PROXIMITY_MASK_LED_CURRENT                0x3f
#define PROXIMITY_MASK_FUSE_PROG_ID               0xc0
/** \} */

/**
 * \defgroup ambient_parameters Proximity ambient parameter registers
 * \{
 */
#define PROXIMITY_AMBI_PARA_AVERAGE_1             0x00
#define PROXIMITY_AMBI_PARA_AVERAGE_2             0x01
#define PROXIMITY_AMBI_PARA_AVERAGE_4             0x02
#define PROXIMITY_AMBI_PARA_AVERAGE_8             0x03
#define PROXIMITY_AMBI_PARA_AVERAGE_16            0x04
#define PROXIMITY_AMBI_PARA_AVERAGE_32            0x05 
#define PROXIMITY_AMBI_PARA_AVERAGE_64            0x06
#define PROXIMITY_AMBI_PARA_AVERAGE_128           0x07
#define PROXIMITY_AMBI_MASK_PARA_AVERAGE          0x07
#define PROXIMITY_AMBI_PARA_AUTO_OFFSET_ENABLE    0x08
#define PROXIMITY_AMBI_MASK_PARA_AUTO_OFFSET      0x08
#define PROXIMITY_AMBI_PARA_MEAS_RATE_1           0x00
#define PROXIMITY_AMBI_PARA_MEAS_RATE_2           0x10 
#define PROXIMITY_AMBI_PARA_MEAS_RATE_3           0x20
#define PROXIMITY_AMBI_PARA_MEAS_RATE_4           0x30
#define PROXIMITY_AMBI_PARA_MEAS_RATE_5           0x40
#define PROXIMITY_AMBI_PARA_MEAS_RATE_6           0x50
#define PROXIMITY_AMBI_PARA_MEAS_RATE_8           0x60
#define PROXIMITY_AMBI_PARA_MEAS_RATE_10          0x70
#define PROXIMITY_AMBI_MASK_PARA_MEAS_RATE        0x70
#define PROXIMITY_AMBI_PARA_CONT_CONV_ENABLE      0x80
#define PROXIMITY_AMBI_MASK_PARA_CONT_CONV        0x80
/** \} */

/**
 * \defgroup interrupt_registers  Interrupt registers
 * \{
 */
#define PROXIMITY_INTERRUPT_THRES_SEL_PROX        0x00
#define PROXIMITY_INTERRUPT_THRES_SEL_ALS         0x01
#define PROXIMITY_INTERRUPT_THRES_ENABLE          0x02
#define PROXIMITY_INTERRUPT_ALS_READY_ENABLE      0x04
#define PROXIMITY_INTERRUPT_PROX_READY_ENABLE     0x08
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_1        0x00 
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_2        0x20
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_4        0x40
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_8        0x60
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_16       0x80
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_32       0xa0
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_64       0xc0
#define PROXIMITY_INTERRUPT_COUNT_EXCEED_128      0xe0
#define PROXIMITY_INTERRUPT_MASK_COUNT_EXCEED     0xe0
#define PROXIMITY_INTERRUPT_STATUS_THRES_HI       0x01
#define PROXIMITY_INTERRUPT_STATUS_THRES_LO       0x02
#define PROXIMITY_INTERRUPT_STATUS_ALS_READY      0x04
#define PROXIMITY_INTERRUPT_STATUS_PROX_READY     0x08
#define PROXIMITY_INTERRUPT_MASK_STATUS_THRES_HI  0x01
#define PROXIMITY_INTERRUPT_MASK_THRES_LO         0x02
#define PROXIMITY_INTERRUPT_MASK_ALS_READY        0x04
#define PROXIMITY_INTERRUPT_MASK_PROX_READY       0x08
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} proximity_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} proximity_cfg_t;

/** \} */ // End types group

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void proximity_cfg_setup ( proximity_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PROXIMITY_RETVAL proximity_init ( proximity_t *ctx, proximity_cfg_t *cfg );

/**
 * @brief Functions for write one byte in register
 *
 * @param ctx       Click object
 * @param w_addr    Register in which the data will be written
 * @param w_data    Data which be written in the register
 */
void proximity_write_byte ( proximity_t *ctx, uint8_t w_addr, uint8_t w_data);

/**
 * @brief Functions for read byte from register
 *
 * @param ctx       Click object
 * @param r_addr    Register which will be read
 *
 * @retval one byte data which is read from the register
 */
uint8_t proximity_read_byte ( proximity_t *ctx, uint8_t r_addr);

/**
 * @brief Functions for read data from register
 *
 * @param ctx          Click object
 * @param r_addr       Register which will be read
 * @param rcv_data     Output buffer
 * @param n_len        Number of bytes will be reads
 */
void proximity_read_data ( proximity_t *ctx, uint8_t r_addr, uint8_t* rcv_data, uint8_t n_len);

/**
 * @brief Functions for write data
 *
 * @param ctx          Click object
 * @param w_addr       Register
 * @param wr_data      Buffer with data
 * @param n_len        Number of bytes will be writting
 */
void proximity_write_data ( proximity_t *ctx, uint8_t w_addr, uint8_t* wr_data, uint8_t n_len);

/**
 * @brief Functions for sets default mode
 * @param ctx       Click object
 */
void proximity_set_default_mode ( proximity_t *ctx );

/**
 * @brief Functions for sets upper threshold
 * @param ctx       Click object
 */
void proximity_set_upper_threshold ( proximity_t *ctx );

/**
 * @brief Functions for reads Proximity data
 *
 * @param ctx       Click object
 * @returns Proximity data
 */
uint16_t proximity_read_prox_data ( proximity_t *ctx );

/**
 * @brief Functions for reads Ambient light
 *
 * @param ctx       Click object
 * @returns Ambient Light data
 */
uint16_t proximity_read_ambient_light ( proximity_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

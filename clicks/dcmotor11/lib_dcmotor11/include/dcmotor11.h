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
 * \brief This file contains API for DC Motor 11 Click driver.
 *
 * \addtogroup dcmotor11 DC Motor 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR11_H
#define DCMOTOR11_H

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
#define DCMOTOR11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR11_RETVAL  uint8_t

#define DCMOTOR11_OK           0x00
#define DCMOTOR11_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define DCMOTOR11_DEVICE_SLAVE_ADDR_0_0  0x60
#define DCMOTOR11_DEVICE_SLAVE_ADDR_0_1  0x62
#define DCMOTOR11_DEVICE_SLAVE_ADDR_1_0  0x66
#define DCMOTOR11_DEVICE_SLAVE_ADDR_1_1  0x68
/** \} */
 
/**
 * \defgroup register Register
 * \{
 */
#define DCMOTOR11_REGISTER_CONTROL  0x00
#define DCMOTOR11_REGISTER_FAULT    0x01
/** \} */
 
/**
 * \defgroup output_voltage  Output Voltage
 * \{
 */
#define DCMOTOR11_VSET_480mV       0x06 << 2
#define DCMOTOR11_VSET_560mV       0x07 << 2
#define DCMOTOR11_VSET_640mV       0x08 << 2
#define DCMOTOR11_VSET_720mV       0x09 << 2
#define DCMOTOR11_VSET_800mV       0x0A << 2
#define DCMOTOR11_VSET_880mV       0x0B << 2
#define DCMOTOR11_VSET_960mV       0x0C << 2
#define DCMOTOR11_VSET_1040mV      0x0D << 2
#define DCMOTOR11_VSET_1120mV      0x0E << 2
#define DCMOTOR11_VSET_1200mV      0x0F << 2
#define DCMOTOR11_VSET_1290mV      0x10 << 2
#define DCMOTOR11_VSET_1370mV      0x11 << 2
#define DCMOTOR11_VSET_1450mV      0x12 << 2
#define DCMOTOR11_VSET_1530mV      0x13 << 2
#define DCMOTOR11_VSET_1610mV      0x14 << 2
#define DCMOTOR11_VSET_1690mV      0x15 << 2
#define DCMOTOR11_VSET_1770mV      0x16 << 2
#define DCMOTOR11_VSET_1850mV      0x17 << 2
#define DCMOTOR11_VSET_1930mV      0x18 << 2
#define DCMOTOR11_VSET_2010mV      0x19 << 2
#define DCMOTOR11_VSET_2090mV      0x1A << 2
#define DCMOTOR11_VSET_2170mV      0x1B << 2
#define DCMOTOR11_VSET_2500mV      0x1C << 2
#define DCMOTOR11_VSET_2330mV      0x1D << 2
#define DCMOTOR11_VSET_2410mV      0x1E << 2
#define DCMOTOR11_VSET_2490mV      0x1F << 2
#define DCMOTOR11_VSET_2570mV      0x20 << 2
#define DCMOTOR11_VSET_2650mV      0x21 << 2
#define DCMOTOR11_VSET_2730mV      0x22 << 2
#define DCMOTOR11_VSET_2810mV      0x23 << 2
#define DCMOTOR11_VSET_2890mV      0x24 << 2
#define DCMOTOR11_VSET_2970mV      0x25 << 2
#define DCMOTOR11_VSET_3050mV      0x26 << 2
#define DCMOTOR11_VSET_3130mV      0x27 << 2
#define DCMOTOR11_VSET_3210mV      0x28 << 2
#define DCMOTOR11_VSET_3290mV      0x29 << 2
#define DCMOTOR11_VSET_3370mV      0x2A << 2
#define DCMOTOR11_VSET_3450mV      0x2B << 2
#define DCMOTOR11_VSET_3530mV      0x2C << 2
#define DCMOTOR11_VSET_3610mV      0x2D << 2
#define DCMOTOR11_VSET_3690mV      0x2E << 2
#define DCMOTOR11_VSET_3770mV      0x2F << 2
#define DCMOTOR11_VSET_3860mV      0x30 << 2
#define DCMOTOR11_VSET_3940mV      0x31 << 2
#define DCMOTOR11_VSET_4020mV      0x32 << 2
#define DCMOTOR11_VSET_4100mV      0x33 << 2
#define DCMOTOR11_VSET_4180mV      0x34 << 2
#define DCMOTOR11_VSET_4260mV      0x35 << 2
#define DCMOTOR11_VSET_4340mV      0x36 << 2
#define DCMOTOR11_VSET_4420mV      0x37 << 2
#define DCMOTOR11_VSET_4500mV      0x38 << 2
#define DCMOTOR11_VSET_4580mV      0x39 << 2
#define DCMOTOR11_VSET_4660mV      0x3A << 2
#define DCMOTOR11_VSET_4740mV      0x3B << 2
#define DCMOTOR11_VSET_4820mV      0x3C << 2
#define DCMOTOR11_VSET_4900mV      0x3D << 2
#define DCMOTOR11_VSET_4980mV      0x3E << 2
#define DCMOTOR11_VSET_5060mV      0x3F << 2
/** \} */
 
/**
 * \defgroup disrection  Disrection
 * \{
 */
#define DCMOTOR11_DIRECTION_FORWARD   0x01
#define DCMOTOR11_DIRECTION_BACKWARD  0x02
#define DCMOTOR11_DIRECTION_STOP      0x00
#define DCMOTOR11_DIRECTION_BREAK     0x03
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

    digital_in_t flt;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} dcmotor11_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t flt;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} dcmotor11_cfg_t;

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
void dcmotor11_cfg_setup ( dcmotor11_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR11_RETVAL dcmotor11_init ( dcmotor11_t *ctx, dcmotor11_cfg_t *cfg );

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
void dcmotor11_generic_write ( dcmotor11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void dcmotor11_generic_read ( dcmotor11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Motor Control
 *
 * @param ctx    Click object.
 * @param dir    Sets Directions - FORWARD/BACKWARD
 * @param speed  Sets output voltage (Speed)
 */
void dcmotor11_control ( dcmotor11_t *ctx, uint8_t dir, uint8_t speed );

/**
 * @brief Get Fault
 *
 * @param ctx          Click object.
 *
 * @return Fault registar state
 */
uint8_t dcmotor11_get_fault ( dcmotor11_t *ctx );

/**
 * @brief Set Fault
 *
 * @param ctx         Click object.
 * @param dev_data    Data for write to the Fault register
 */
void dcmotor11_clear_fault ( dcmotor11_t *ctx, uint8_t dev_data );

/**
 * @brief Motor Stop
 *
 * @param ctx          Click object.
 */
void dcmotor11_stop ( dcmotor11_t *ctx );

/**
 * @brief Motor Break
 *
 * @param ctx          Click object.
 */
void dcmotor11_break ( dcmotor11_t *ctx );

/**
 * @brief Interrupt state on the INT pin
 *
 * @param ctx          Click object.
 *
 * @return Interrupt state
 */
uint8_t dcmotor11_get_interrupt_state ( dcmotor11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for BUCK 7 Click driver.
 *
 * \addtogroup buck7 BUCK 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK7_H
#define BUCK7_H

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

#define BUCK7_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.en    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.mod   = MIKROBUS( mikrobus, MIKROBUS_PWM ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK7_RETVAL  uint8_t

#define BUCK7_OK           0x00
#define BUCK7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode  Mode
 * \{
 */
#define BUCK7_MODE_DCM  0x01
#define BUCK7_MODE_PWM  0x00
/** \} */

/**
 * \defgroup output_voltage  Output voltage 
 * \{
 */
#define BUCK7_OUT_VOLTAGE_3_3V   0x0FAF
#define BUCK7_OUT_VOLTAGE_5V     0x0EA6
#define BUCK7_OUT_VOLTAGE_6V     0x0E10
#define BUCK7_OUT_VOLTAGE_7V     0x0D7A
#define BUCK7_OUT_VOLTAGE_8V     0x0CE4
#define BUCK7_OUT_VOLTAGE_9V     0x0C4E
#define BUCK7_OUT_VOLTAGE_10V    0x0BB8
#define BUCK7_OUT_VOLTAGE_11V    0x0B22
#define BUCK7_OUT_VOLTAGE_12V    0x0A8C
#define BUCK7_OUT_VOLTAGE_13V    0x09F6
#define BUCK7_OUT_VOLTAGE_14V    0x0960
#define BUCK7_OUT_VOLTAGE_15V    0x08CA
#define BUCK7_OUT_VOLTAGE_16V    0x0834
#define BUCK7_OUT_VOLTAGE_17V    0x079E
#define BUCK7_OUT_VOLTAGE_18V    0x0708
#define BUCK7_OUT_VOLTAGE_19V    0x0672
#define BUCK7_OUT_VOLTAGE_20V    0x059C
#define BUCK7_OUT_VOLTAGE_21V    0x0546
#define BUCK7_OUT_VOLTAGE_22V    0x04B0
#define BUCK7_OUT_VOLTAGE_23V    0x041A
#define BUCK7_OUT_VOLTAGE_24V    0x0384
#define BUCK7_OUT_VOLTAGE_25V    0x02EE
#define BUCK7_OUT_VOLTAGE_26V    0x0244
#define BUCK7_OUT_VOLTAGE_27V    0x0190
#define BUCK7_OUT_VOLTAGE_28V    0x00FA
#define BUCK7_OUT_VOLTAGE_29V    0x0096
#define BUCK7_OUT_VOLTAGE_30V    0x0000
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

    digital_out_t en;
    digital_out_t rst;
    digital_out_t mod;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} buck7_t;

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

    pin_name_t en;
    pin_name_t rst;
    pin_name_t mod;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} buck7_cfg_t;

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
void buck7_cfg_setup ( buck7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK7_RETVAL buck7_init ( buck7_t *ctx, buck7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for BUCK 7 click.
 */
void buck7_default_cfg ( buck7_t *ctx );

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
void buck7_generic_transfer 
( 
    buck7_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Function for settings output voltage.
 *
 * @param ctx          Click object.
 * @param voltage      Voltage which be set
 *
 * @description Function for settings output voltage
 */
void buck7_set_output_voltage ( buck7_t *ctx, uint16_t voltage );

/**
 * @brief Function for enable chip
 *
 * @param ctx          Click object.
 *
 * @description Function for enable chip
 */
void buck7_enable ( buck7_t *ctx );

/**
 * @brief Function for settings chip mode
 *
 * @param ctx          Click object.
 * @param mode         Mode of work chip
 *
 * @description Function for settings chip mode
 */
void buck7_set_mode ( buck7_t *ctx, uint8_t mode );

/**
 * @brief Function for read RES state
 *
 * @param ctx          Click object.
 *
 * @description Function for read RES state
 */
uint8_t buck7_get_res_state ( buck7_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _BUCK7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

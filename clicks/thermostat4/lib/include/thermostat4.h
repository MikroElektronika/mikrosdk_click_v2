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
 * \brief This file contains API for Thermostat 4 Click driver.
 *
 * \addtogroup thermostat4 Thermostat 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMOSTAT4_H
#define THERMOSTAT4_H

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

#define THERMOSTAT4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.oa  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.rly = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.ob  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMOSTAT4_RETVAL  uint8_t

#define THERMOSTAT4_OK           0x00
#define THERMOSTAT4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup relay_control Relay control
 * \{
 */
#define THERMOSTAT4_RELAY_ON                0x01
#define THERMOSTAT4_RELAY_OFF               0x00
/** \} */

/**
 * \defgroup reset Reset
 * \{
 */
#define THERMOSTAT4_RESET_ON                0x01
#define THERMOSTAT4_RESET_OFF               0x00
/** \} */

/**
 * \defgroup alert Alert
 * \{
 */
#define THERMOSTAT4_WARM_ALERT              0x00
#define THERMOSTAT4_HOT_ALERT               0x00
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

    digital_out_t rst;
    digital_out_t rly;
    digital_out_t cs;

    // Input pins 

    digital_in_t oa;
    digital_in_t ob;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} thermostat4_t;

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

    pin_name_t oa;
    pin_name_t rst;
    pin_name_t rly;
    pin_name_t ob;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} thermostat4_cfg_t;

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
void thermostat4_cfg_setup ( thermostat4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMOSTAT4_RETVAL thermostat4_init ( thermostat4_t *ctx, thermostat4_cfg_t *cfg );

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
void thermostat4_generic_transfer 
( 
    thermostat4_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Relay Control
 *
 * @param ctx     Click object. 
 * @param state   Relay ( ON or OFF state )
 *
 * @description This function write desired state on RLY pin.
 */
void thermostat4_relay_ctrl ( thermostat4_t *ctx, uint8_t state );

/**
 * @brief Sets reset pin state
 *
 * @param ctx     Click object.  
 * @param state   Reset ( 1 - ON or 0 - OFF state )
 *
 * @description This function write desired state om RST pin.
 */
void thermostat4_rst_pin_ctrl ( thermostat4_t *ctx, uint8_t state );

/**
 * @brief Hot temperature ALERT
 *
 * @param ctx     Click object. 
 * 
 * @returns Alert( 0 - ON or 1 - OFF state )
 *
 * @description This function read state from OA pin.
 */
uint8_t thermostat4_hot_alert_state ( thermostat4_t *ctx );

/**
 * @brief Warm temperature ALERT
 *
 * @param ctx     Click object.  
 *
 * @returns Alert( 0 - ON or 1 - OFF state )
 *
 * @description This function read state from OB pin.
 */
uint8_t thermostat4_warm_alert_state ( thermostat4_t *ctx );

/**
 * @brief Hysteresis on the Warm channel
 *
 * @param ctx         Click object.  
 * @param hyst_data   Potentiometer data 0- 255
 *
 * @description This function write hysteresis data.
 */
void thermostat4_set_warm_hysteresis ( thermostat4_t *ctx, uint8_t hyst_data );

/**
 * @brief Reset module and upload new configuration on the Warm channel
 *
 * @param ctx     Click object. 
 *
 * @description This function reset module and upload new configuration on the Warm channel.
 */
void thermostat4_new_cfg_upload ( thermostat4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMOSTAT4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

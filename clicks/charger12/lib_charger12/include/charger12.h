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
 * \brief This file contains API for CHARGER 12 Click driver.
 *
 * \addtogroup charger12 CHARGER 12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CHARGER12_H
#define CHARGER12_H

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

#define CHARGER12_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.che = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.mod = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.vok = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CHARGER12_RETVAL  uint8_t

#define CHARGER12_OK           0x00
#define CHARGER12_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup spi_register_address SPI register address
 * \{
 */
#define CHARGER12_SPI_VOLATILE_WIPER_0      0x00
#define CHARGER12_SPI_VOLATILE_WIPER_1      0x01
#define CHARGER12_SPI_NON_VOLATILE_WIPER_0  0x02
#define CHARGER12_SPI_NON_VOLATILE_WIPER_1  0x03
#define CHARGER12_SPI_VOLATILE_TCON         0x04
#define CHARGER12_SPI_STATUS_REGISTER       0x05
#define CHARGER12_SPI_DATA_EEPROM_0         0x06
#define CHARGER12_SPI_DATA_EEPROM_1         0x07
#define CHARGER12_SPI_DATA_EEPROM_2         0x08
#define CHARGER12_SPI_DATA_EEPROM_3         0x09
#define CHARGER12_SPI_DATA_EEPROM_4         0x0A
#define CHARGER12_SPI_DATA_EEPROM_5         0x0B
#define CHARGER12_SPI_DATA_EEPROM_6         0x0C
#define CHARGER12_SPI_DATA_EEPROM_7         0x0D
#define CHARGER12_SPI_DATA_EEPROM_8         0x0E
#define CHARGER12_SPI_DATA_EEPROM_9         0x0F
/** \} */

/**
 * \defgroup modes_of_operation Modes of operation
 * \{
 */
#define CHARGER12_MODE_Li          0
#define CHARGER12_MODE_NiMh_NiCd   1
#define CHARGER12_MODE_DISABLE     2
#define CHARGER12_MODE_NO_BATTERY  3
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

    digital_out_t cs;
    digital_out_t che;
    digital_out_t mod;
    
    // Input pins 

    digital_in_t vok;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} charger12_t;

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

    pin_name_t che;
    pin_name_t mod;
    pin_name_t vok;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} charger12_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void charger12_cfg_setup ( charger12_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
CHARGER12_RETVAL charger12_init ( charger12_t *ctx, charger12_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param data_in      Data in.
 * @param data_out     Data output.
 * @param tx_len       Transmitter lenght.
 * @param rx_len       Receiver lenght. 
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void charger12_generic_transfer ( charger12_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t tx_len, uint8_t rx_len );

/**
 * @brief Getting INT pin state.
 *
 * @param ctx          Click object.
 *
 * @description This function return 0 if INT pin is in LOW state or 1 if INT pin is in HIGH state.
 */uint8_t charger12_int_get ( charger12_t *ctx );

 /**
 * @brief Setting PWM pin state.
 *
 * @param ctx          Click object.
 * @param pin_state    Pin state.
 *
 * @description This function sets PWM pin state.
 */void charger12_pwm_set ( charger12_t *ctx, uint8_t pin_state );

 /**
 * @brief Setting RST pin state.
 *
 * @param ctx          Click object.
 * @param pin_state    Pin state.
 *
 * @description  This function sets RST pin state.
 */void charger12_rst_set ( charger12_t *ctx, uint8_t pin_state );

 /**
 * @brief Setting CS pin state.
 *
 * @param ctx          Click object.
 * @param pin_state    Pin state.
 *
 * @description This function sets CS pin state.
 */void charger12_cs_set ( charger12_t *ctx, uint8_t pin_state );

 /**
 * @brief Selecting device operation mode.
 *
 * @param ctx          Click object.
 * @param mode_select  Mode selection.
 *
 * @description This function selects device operation mode by setting RST(CHGEN) and PWM(MODE) pins.
 */uint8_t charger12_mode_select ( charger12_t *ctx, uint8_t mode_select );

 /**
 * @brief Setting register.
 *
 * @param ctx          Click object.
 * @param register_address     Register address.
 * @param register_value       Register value.
 *
 * @description This function sets register value.
 */void charger12_spi_set_register( charger12_t *ctx, uint8_t register_address, uint16_t register_value );

 /**
 * @brief Incrementing wiper position.
 *
 * @param ctx                  Click object.
 *
 * @description This function increments wiper position by sending 8bit increment wiper command.
 */void charger12_spi_increment_wiper( charger12_t *ctx );

 /**
 * @brief Decrementing wiper position.
 *
 * @param ctx          Click object.
 *
 * @description This function decrements wiper position by sending 8bit decrement wiper command.S
 */void charger12_spi_decrement_wiper( charger12_t *ctx );



#ifdef __cplusplus
}
#endif
#endif  // _CHARGER12_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

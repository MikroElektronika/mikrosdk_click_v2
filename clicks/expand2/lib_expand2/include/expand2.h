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
 * \brief This file contains API for Expand 2 Click driver.
 *
 * \addtogroup expand2 Expand 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EXPAND2_H
#define EXPAND2_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define EXPAND2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EXPAND2_RETVAL  uint8_t

#define EXPAND2_OK           0x00
#define EXPAND2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup addr Address
 * \{
 */
#define EXPAND2_I2C_MODULE_ADDRESS_0                                0x20
#define EXPAND2_I2C_MODULE_ADDRESS_1                                0x21
#define EXPAND2_I2C_MODULE_ADDRESS_2                                0x22
#define EXPAND2_I2C_MODULE_ADDRESS_3                                0x23
#define EXPAND2_I2C_MODULE_ADDRESS_4                                0x24
#define EXPAND2_I2C_MODULE_ADDRESS_5                                0x25
#define EXPAND2_I2C_MODULE_ADDRESS_6                                0x26
#define EXPAND2_I2C_MODULE_ADDRESS_7                                0x27
/** \} */

/**
 * \defgroup port_dir Port Direction
 * \{
 */
#define EXPAND2_PORT_DIRECTION_OUTPUT                               0x00
#define EXPAND2_PORT_DIRECTION_INPUT                                0xFF
/** \} */

/**
 * \defgroup b1_reg_cfg BANK 1 Register Configuration
 * \{
 */
#define EXPAND2_IODIRA_BANK1                                        0x00
#define EXPAND2_IPOLA_BANK1                                         0x01
#define EXPAND2_GPINTENA_BANK1                                      0x02
#define EXPAND2_DEFVALA_BANK1                                       0x03
#define EXPAND2_INTCONA_BANK1                                       0x04
#define EXPAND2_IOCON_BANK1                                         0x05
#define EXPAND2_GPPUA_BANK1                                         0x06
#define EXPAND2_INTFA_BANK1                                         0x07
#define EXPAND2_INTCAPA_BANK1                                       0x08
#define EXPAND2_GPIOA_BANK1                                         0x09
#define EXPAND2_OLATA_BANK1                                         0x0A
#define EXPAND2_IODIRB_BANK1                                        0x10
#define EXPAND2_IPOLB_BANK1                                         0x11
#define EXPAND2_GPINTENB_BANK1                                      0x12
#define EXPAND2_DEFVALB_BANK1                                       0x13
#define EXPAND2_INTCONB_BANK1                                       0x14
#define EXPAND2_IOCONO_BANK1                                        0x15
#define EXPAND2_GPPUB_BANK1                                         0x16
#define EXPAND2_INTFB_BANK1                                         0x17
#define EXPAND2_INTCAPB_BANK1                                       0x18
#define EXPAND2_GPIOB_BANK1                                         0x19
#define EXPAND2_OLATB_BANK1                                         0x1A
/** \} */

/**
 * \defgroup b0_reg_cfg BANK 0 Register Configuration
 * \{
 */
#define EXPAND2_IODIRA_BANK0                                        0x00
#define EXPAND2_IODIRB_BANK0                                        0x01
#define EXPAND2_IPOLA_BANK0                                         0x02
#define EXPAND2_IPOLB_BANK0                                         0x03
#define EXPAND2_GPINTENA_BANK0                                      0x04
#define EXPAND2_GPINTENB_BANK0                                      0x05
#define EXPAND2_DEFVALA_BANK0                                       0x06
#define EXPAND2_DEFVALB_BANK0                                       0x07
#define EXPAND2_INTCONA_BANK0                                       0x08
#define EXPAND2_INTCONB_BANK0                                       0x09
#define EXPAND2_IOCON_BANK0                                         0x0A
#define EXPAND2_GPPUA_BANK0                                         0x0C
#define EXPAND2_GPPUB_BANK0                                         0x0D
#define EXPAND2_INTFA_BANK0                                         0x0E
#define EXPAND2_INTFB_BANK0                                         0x0F
#define EXPAND2_INTCAPA_BANK0                                       0x10
#define EXPAND2_INTCAPB_BANK0                                       0x11
#define EXPAND2_GPIOA_BANK0                                         0x12
#define EXPAND2_GPIOB_BANK0                                         0x13
#define EXPAND2_OLATA_BANK0                                         0x14
#define EXPAND2_OLATB_BANK0                                         0x15

#define EXPAND2_HD1_PA0                                             0x01
#define EXPAND2_HD1_PA1                                             0x02
#define EXPAND2_HD1_PA2                                             0x04
#define EXPAND2_HD1_PA3                                             0x08
#define EXPAND2_HD1_PA4                                             0x10
#define EXPAND2_HD1_PA5                                             0x20
#define EXPAND2_HD1_PA6                                             0x40
#define EXPAND2_HD1_PA7                                             0x80

#define EXPAND2_HD2_PB0                                             0x01
#define EXPAND2_HD2_PB1                                             0x02
#define EXPAND2_HD2_PB2                                             0x04
#define EXPAND2_HD2_PB3                                             0x08
#define EXPAND2_HD2_PB4                                             0x10
#define EXPAND2_HD2_PB5                                             0x20
#define EXPAND2_HD2_PB6                                             0x40
#define EXPAND2_HD2_PB7                                             0x80

#define EXPAND2_HD_START_POSITION                                   0x01

#define EXPAND2_INT_ERR                                             0xFF
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} expand2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} expand2_cfg_t;

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
void expand2_cfg_setup ( expand2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param expand2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EXPAND2_RETVAL expand2_init ( expand2_t *ctx, expand2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Expand2 click.
 */
void expand2_default_cfg ( expand2_t *ctx );

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
void expand2_generic_write ( expand2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void expand2_generic_read ( expand2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set register bits function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param reg_address                        register address
 * @param bit_mask                           bits mask
 *
 * @description Function set bits to 8-bit register address of MCP23017 chip.
 */
void expand2_set_bits ( expand2_t *ctx, uint8_t module_address, uint8_t reg_address, uint8_t bit_mask );

/**
 * @brief Clear register bits function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param reg_address                        register address
 * @param bit_mask                           bits mask
 *
 * @description Function clear bits from 8-bit register address of MCP23017 chip.
 */
void expand2_clear_bits ( expand2_t *ctx, uint8_t module_address, uint8_t reg_address, uint8_t bit_mask );

/**
 * @brief Toggle register bits function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param reg_address                        register address
 * @param bit_mask                           bits mask
 *
 * @description Function toggle bits from 8-bit register address of MCP23017 chip.
 */
void expand2_toggle_bits ( expand2_t *ctx, uint8_t module_address, uint8_t reg_address, uint8_t bit_mask );

/**
 * @brief Read one byte of data from PORTA function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @return result                            read data ( PORTA )
 *
 * @description Function read 8-bit of data from PORTA from 8-bit register address of MCP23017 chip.
 */
uint8_t expand2_read_port_a ( expand2_t *ctx, uint8_t module_address );

/**
 * @brief Read one byte of data from PORTB function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @return result                            read data ( PORTB )
 *
 * @description Function read 8-bit of data from PORTB from 8-bit register address of MCP23017 chip.
 */
uint8_t expand2_read_port_b ( expand2_t *ctx, uint8_t module_address );

/**
 * @brief Read two byte of data from PORTA & PORTB function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @return result                            read data ( PORTA & PORTB )
 *
 * @description Function read 16-bit of data from PORTA & PORTB from 8-bit register address of MCP23017 chip.
 */
uint16_t expand2_read_both_ports ( expand2_t *ctx, uint8_t module_address );

/**
 * @brief Write one byte of data to register for PORTA function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         data to write
 *
 * @description Function write 8-bit of data to 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_write_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t write_data );

/**
 * @brief Clear bit from register for PORTA function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bits mask
 *
 * @description Function clear bit from 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_clear_bit_port_a ( expand2_t *ctx, uint8_t moduleAddress, uint8_t bitMask );

/**
 * @brief Set bit to register for PORTA function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bits mask
 *
 * @description Function set bit to 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_set_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Toggle bit to register for PORTA function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bits mask
 *
 * @description Function toggle bit from 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_toggle_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Write one byte of data to register for PORTB function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         data to write
 *
 * @description Function write 8-bit of data to 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_write_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t write_data );

/**
 * @brief Clear bit from register for PORTB function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bits mask
 *
 * @description Function clear bit from 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_clear_bit_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Set bit to register for PORTB function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bits mask
 *
 * @description Function set bit to 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_setBitPortB( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Toggle bit to register for PORTB function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bits mask
 *
 * @description Function toggle bit from 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_toggle_bit_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Set expander PORTA direction function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         data to write
 *
 * @description Function set expander direction by write 8-bit data to 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_set_direction_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t write_data );

/**
 * @brief Set expander PORTA input direction function
 *
 * @param ctx                                Click object.
 * @param module_address                     module addres
 * @param bit_mask                           bit mask
 *
 * @description Function write bit, when expander direction of PORTA set as input, to 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_set_input_dir_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Set expander PORTA output direction function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bit mask
 *
 * @description Function write bit, when expander direction of PORTA set as output, to 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_set_output_dir_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Set expander PORTB direction function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         data to write
 *
 * @description Function set expander direction by write 8-bit data to 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_set_direction_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t write_data );

/**
 * @brief Set expander PORTB input direction function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bit mask
 *
 * @description Function write bit, when expander direction of PORTB set as input, to 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_set_input_dir_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Set expander PORTB output direction function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param bit_mask                           bit mask
 *
 * @description Function write bit, when expander direction of PORTB set as output, to 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_set_output_dir_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

/**
 * @brief Set pull-ups of the expander for PORTA pins function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         pull up value
 *
 * @description Function set pull-ups of the expander for PORTA pins by write 8-bit pull up value data to 8-bit register address from PORTA of MCP23017 chip.
 */
void expand2_set_pull_ups_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t write_data );

/**
 * @brief Set pull-ups of the expander for PORTB pins function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         pull up value
 *
 * @description Function set pull-ups of the expander for PORTB pins by write 8-bit pull up value data to 8-bit register address from PORTB of MCP23017 chip.
 */
void expand2_set_pull_ups_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t write_data );

/**
 * @brief Active pin by position on PORTA function
 *
 * @param ctx                               Click object.
 * @param module_address                    module address
 * @param position                          pin position
 *
 * @description Function activate pin on PORTA by position, from PA0 to PA7.
 */
void expand2_set_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t position );

/**
 * @brief Active pin by position on PORTB function
 *
 * @param ctx                               Click object.
 * @param module_address                    module address
 * @param position                          pin position
 *
 * @description Function activate pin on PORTB by position, from PB0 to PB7.
 */
void expand2_set_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t position );

/**
 * @brief Reset function
 *
 * @param ctx                                Click object.
 * @param module_address                     module address
 * @param write_data                         pull up value
 *
 * @description Function reset Expand 2 click by set RST pin from low to high.
 *
 * @note delay is 11ms
 */
void expand2_reset( expand2_t *ctx );

/**
 * @brief Get state of interrupt pin function
 *
 * @param ctx          Click object.
 * 
 * @return state
 *      <pre>  
 *        0 - No Active
 *        1 - Active
 *      </pre>     
 * 
 * @description Function get state of interrupt ( INT ) pin.
 */
uint8_t expand2_getInterrupt( expand2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _EXPAND2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

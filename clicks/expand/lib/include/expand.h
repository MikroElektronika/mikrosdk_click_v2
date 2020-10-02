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
 * \brief This file contains API for Expand Click driver.
 *
 * \addtogroup expand Expand Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EXPAND_H
#define EXPAND_H

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

#define EXPAND_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EXPAND_RETVAL  uint8_t

#define EXPAND_OK           0x00
#define EXPAND_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup opcode Opcode
 * \{
 */
#define EXPAND_SPI_DEVICE_OPCODE                                  0x40
#define EXPAND_OPCODE_WRITE                                       0x00
#define EXPAND_OPCODE_READ                                        0x01
/** \} */

/**
 * \defgroup module_position
 * \{
 */
#define EXPAND_SPI_MODULE_POSITION_0                              0x00
#define EXPAND_SPI_MODULE_POSITION_1                              0x02
#define EXPAND_SPI_MODULE_POSITION_2                              0x04
#define EXPAND_SPI_MODULE_POSITION_3                              0x06
#define EXPAND_SPI_MODULE_POSITION_4                              0x08
#define EXPAND_SPI_MODULE_POSITION_5                              0x0A
#define EXPAND_SPI_MODULE_POSITION_6                              0x0C
#define EXPAND_SPI_MODULE_POSITION_7                              0x0E
/** \} */

/**
 * \defgroup port_direction Port Direction
 * \{
 */
#define EXPAND_PORT_DIRECTION_OUTPUT                              0x00
#define EXPAND_PORT_DIRECTION_INPUT                               0xFF
/** \} */

/**
 * \defgroup bank1_register_configuration BANK 1 register configuration
 * \{
 */
#define EXPAND_IODIRA_BANK1                                       0x00
#define EXPAND_IPOLA_BANK1                                        0x01
#define EXPAND_GPINTENA_BANK1                                     0x02
#define EXPAND_DEFVALA_BANK1                                      0x03
#define EXPAND_INTCONA_BANK1                                      0x04
#define EXPAND_IOCON_BANK1                                        0x05
#define EXPAND_GPPUA_BANK1                                        0x06
#define EXPAND_INTFA_BANK1                                        0x07
#define EXPAND_INTCAPA_BANK1                                      0x08
#define EXPAND_GPIOA_BANK1                                        0x09
#define EXPAND_OLATA_BANK1                                        0x0A
#define EXPAND_IODIRB_BANK1                                       0x10
#define EXPAND_IPOLB_BANK1                                        0x11
#define EXPAND_GPINTENB_BANK1                                     0x12
#define EXPAND_DEFVALB_BANK1                                      0x13
#define EXPAND_INTCONB_BANK1                                      0x14
#define EXPAND_IOCONO_BANK1                                       0x15
#define EXPAND_GPPUB_BANK1                                        0x16
#define EXPAND_INTFB_BANK1                                        0x17
#define EXPAND_INTCAPB_BANK1                                      0x18
#define EXPAND_GPIOB_BANK1                                        0x19
#define EXPAND_OLATB_BANK1                                        0x1A
/** \} */

/**
 * \defgroup bank0_register_configuration BANK 0 register configuration
 * \{
 * \{
 */
#define EXPAND_IODIRA_BANK0                                       0x00
#define EXPAND_IODIRB_BANK0                                       0x01
#define EXPAND_IPOLA_BANK0                                        0x02
#define EXPAND_IPOLB_BANK0                                        0x03
#define EXPAND_GPINTENA_BANK0                                     0x04
#define EXPAND_GPINTENB_BANK0                                     0x05
#define EXPAND_DEFVALA_BANK0                                      0x06
#define EXPAND_DEFVALB_BANK0                                      0x07
#define EXPAND_INTCONA_BANK0                                      0x08
#define EXPAND_INTCONB_BANK0                                      0x09
#define EXPAND_IOCON_BANK0                                        0x0A
#define EXPAND_GPPUA_BANK0                                        0x0C
#define EXPAND_GPPUB_BANK0                                        0x0D
#define EXPAND_INTFA_BANK0                                        0x0E
#define EXPAND_INTFB_BANK0                                        0x0F
#define EXPAND_INTCAPA_BANK0                                      0x10
#define EXPAND_INTCAPB_BANK0                                      0x11
#define EXPAND_GPIOA_BANK0                                        0x12
#define EXPAND_GPIOB_BANK0                                        0x13
#define EXPAND_OLATA_BANK0                                        0x14
#define EXPAND_OLATB_BANK0                                        0x15
/** \} */

/**
 * \defgroup expand_iocon Expand IOCON
 * \{
 */
#define EXPAND_IOCON_BYTE_MODE                                    0x20
#define EXPAND_IOCON_HAEN                                         0x08

#define EXPAND_CN4_PA0                                            0x01
#define EXPAND_CN4_PA1                                            0x02
#define EXPAND_CN4_PA2                                            0x04
#define EXPAND_CN4_PA3                                            0x08
#define EXPAND_CN4_PA4                                            0x10
#define EXPAND_CN4_PA5                                            0x20
#define EXPAND_CN4_PA6                                            0x40
#define EXPAND_CN4_PA7                                            0x80

#define EXPAND_CN5_PB0                                            0x01
#define EXPAND_CN5_PB1                                            0x02
#define EXPAND_CN5_PB2                                            0x04
#define EXPAND_CN5_PB3                                            0x08
#define EXPAND_CN5_PB4                                            0x10
#define EXPAND_CN5_PB5                                            0x20
#define EXPAND_CN5_PB6                                            0x40
#define EXPAND_CN5_PB7                                            0x80

#define EXPAND_CN_START_POSITION                                  0x01

#define EXPAND_INT_ERR                                            0xFF
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
    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;

} expand_t;

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

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    hal_spi_speed_t spi_speed;
    hal_spi_mode_t spi_mode;

} expand_cfg_t;

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
void expand_cfg_setup ( expand_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param expand Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EXPAND_RETVAL expand_init ( expand_t *ctx, expand_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param block        Transfer block structure.
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void expand_generic_transfer ( expand_t *ctx, spi_master_transfer_data_t *block );

/**
 * @brief Generic read one bayt from register function
 *
 * @param ctx          Click object.
 * @param mod_amd      Module command.
 * @param reg_addr     Register address.
 *
 * @description Function read 8-bit of data from 8-bit register address of MCP23S17 chip.
 */
uint8_t expand_read_byte ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr );

/**
 * @brief Generic write one bayt to register function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param reg_addr     Register address.
 * @param write_data   Data to write to register.
 *
 * @description Function write 8-bit of data to 8-bit register address of MCP23S17 chip.
 */
void expand_write_byte ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t write_data );

/**
 * @brief Generic write one bayt to register function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 *
 * @description Function set default configuration to MCP23S17 chip.
 */
void expand_default_configuration ( expand_t *ctx, uint8_t mod_cmd );

/**
 * @brief Set register bits function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param reg_addr     Register address.
 * @param bit_mask     Bits mask.
 *
 * @description Function set bits to 8-bit register address of MCP23S17 chip.
 */
void expand_set_bits ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask );

/**
 * @brief Clear register bits function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param reg_addr     Register address.
 * @param bit_mask     Bits mask.
 *
 * @description Function clear bits from 8-bit register address of MCP23S17 chip.
 */
void expand_clear_bits ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask );

/**
 * @brief Toggle register bits function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param reg_addr     Register address.
 * @param bit_mask     Bits mask.
 *
 * @description Function toggle bits from 8-bit register address of MCP23S17 chip.
 */
void expand_toggle_bits ( expand_t *ctx, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask );

/**
 * @brief Read one byte of data from PORTA function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 *
 * @return result      Read data ( PORTA ).
 *
 * @description Function read 8-bit of data from PORTA from 8-bit register address of MCP23S17 chip.
 */
uint8_t expand_read_port_a ( expand_t *ctx, uint8_t mod_cmd );

/**
 * @brief Read one byte of data from PORTB function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 *
 * @return result      Read data ( PORTB ).
 *
 * @description Function read 8-bit of data from PORTB from 8-bit register address of MCP23S17 chip.
 */
uint8_t expand_read_port_b ( expand_t *ctx, uint8_t mod_cmd );

/**
 * @brief Read two byte of data from PORTA & PORTB function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 *
 * @return result      Read data ( PORTA & PORTB ).
 *
 * @description Function read 16-bit of data from PORTA & PORTB from 8-bit register address of MCP23S17 chip.
 */
uint16_t expand_read_both_porta ( expand_t *ctx, uint8_t mod_cmd );

/**
 * @brief Write one byte of data to register for PORTA function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param write_data   Data to write.
 *
 * @description Function write 8-bit of data to 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_write_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

/**
 * @brief Clear bit from register for PORTA function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bits mask.
 *
 * @description Function clear bit from 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_clear_bit_port_a( uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set bit to register for PORTA function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bits mask.
 *
 * @description Function set bit to 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_set_bit_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Toggle bit to register for PORTA function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bits mask.
 *
 * @description Function toggle bit from 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_toggle_bit_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Write one byte of data to register for PORTB function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param write_data   Data to write.
 *
 * @description Function write 8-bit of data
 * to 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_write_port_b( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

/**
 * @brief Clear bit from register for PORTB function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bits mask.
 *
 * @description Function clear bit from 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_clear_bit_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set bit to register for PORTB function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bits mask.
 *
 * @description Function set bit to 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_set_bit_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Toggle bit to register for PORTB function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bits mask.
 *
 * @description Function toggle bit from 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_toggle_bit_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set expander PORTA direction function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param write_data   Data to write.
 *
 * @description Function set expander direction by write 8-bit data
 * to 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_set_direction_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

/**
 * @brief Set expander PORTA input direction function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bit mask.
 *
 * @description Function write bit, when expander direction of PORTA set as input,
 * to 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_set_input_dir_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set expander PORTA output direction function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param bit_mask     Bit mask.
 *
 * @description Function write bit, when expander direction of PORTA set as output,
 * to 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_set_output_dir_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set expander PORTB direction function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param write_data   Data to write.
 *
 * @description Function set expander direction by write 8-bit data
 * to 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_set_direction_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

/**
 * @brief Set expander PORTB input direction function
 *
 * @param ctx          Click object
 * @param mod_cmd      Module command.
 * @param bit_mask     Bit mask.
 *
 * @description Function write bit, when expander direction of PORTB set as input,
 * to 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_set_input_dir_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set expander PORTB output direction function
 *
 * @param ctx          Click object
 * @param mod_cmd      Module command.
 * @param bit_mask     Bit mask.
 *
 * @description Function write bit, when expander direction of PORTB set as output,
 * to 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_set_output_dir_port_b( expand_t *ctx, uint8_t mod_cmd, uint8_t bit_mask );

/**
 * @brief Set pull-ups of the expander for PORTA pins function
 *
 * @param ctx          Click object
 * @param mod_cmd      Module command.
 * @param write_data   Pull up value.
 *
 * @description Function set pull-ups of the expander for PORTA pins
 * by write 8-bit pull up value data
 * to 8-bit register address from PORTA of MCP23S17 chip.
 */
void expand_set_pull_ups_port_a( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

/**
 * @brief Set pull-ups of the expander for PORTB pins function
 *
 * @param ctx          Click object
 * @param mod_cmd      Module command.
 * @param write_data   Pull up value.
 *
 * @description Function set pull-ups of the expander for PORTB pins
 * by write 8-bit pull up value data
 * to 8-bit register address from PORTB of MCP23S17 chip.
 */
void expand_set_pull_ups_port_b ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

/**
 * @brief Active pin by position on PORTA function
 *
 * @param ctx          Click object.
 * @param position     Pin position.
 *
 * @description Function activate pin on PORTA by position, from PA0 to PA7.
 */
void expand_set_potr_a( expand_t *ctx, uint8_t position );

/**
 * @brief Active pin by position on PORTB function
 *
 * @param ctx          Click object.
 * @param position     Pin position.
 *
 * @description Function activate pin on PORTB by position, from PB0 to PB7.
 */
void expand_set_potr_b ( expand_t *ctx, uint8_t position );

/**
 * @brief Reset function
 *
 * @param ctx          Click object.
 * @param mod_cmd      Module command.
 * @param write_data   Pull up value.
 *
 * @description Function reset Expand 2 click by set RST pin from low to high.
 *
 * @note
 * delay is 11ms
 */
void expand_reset ( expand_t *ctx );

/**
 * @brief Get state of interrupt pin function
 *
 * @param ctx          Click object.
 *
 * @return state
 * 0 - No Active, 1 - Active
 *
 * @description Function get state of interrupt ( INT ) pin.
 */
uint8_t expand_get_interrupt( expand_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _EXPAND_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for MCP73213 Click driver.
 *
 * \addtogroup mcp73213 MCP73213 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MCP73213_H
#define MCP73213_H

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

#define MCP73213_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MCP73213_RETVAL  uint8_t

#define MCP73213_OK           0x00
#define MCP73213_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define MCP73213_SPI_CMD_READ                                      0x0C
#define MCP73213_SPI_CMD_WRITE                                     0x00
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define MCP73213_VOLATILE_WIPER_0                                  0x00
#define MCP73213_VOLATILE_WIPER_1                                  0x01
#define MCP73213_NON_VOLATILE_WIPER_0                              0x02
#define MCP73213_NON_VOLATILE_WIPER_1                              0x03
#define MCP73213_VOLATILE_TCON_REGISTER                            0x04
#define MCP73213_STATUS_REGISTER                                   0x05
#define MCP73213_DATA_EEPROM_6                                     0x06
#define MCP73213_DATA_EEPROM_7                                     0x07
#define MCP73213_DATA_EEPROM_8                                     0x08
#define MCP73213_DATA_EEPROM_9                                     0x09
#define MCP73213_DATA_EEPROM_A                                     0x0A
#define MCP73213_DATA_EEPROM_B                                     0x0B
#define MCP73213_DATA_EEPROM_C                                     0x0C
#define MCP73213_DATA_EEPROM_D                                     0x0D
#define MCP73213_DATA_EEPROM_E                                     0x0E
#define MCP73213_DATA_EEPROM_F                                     0x0F
//#define MCP73213_DATA_WRITE_CMD                                    0x00
/** \} */

/**
 * \defgroup vref  Vref
 * \{
 */
#define P73213_VREF_3V3                                            3.30
#define P73213_VREF_5V                                             5.00
/** \} */

/**
 * \defgroup output_value  Output value
 * \{
 */
#define MCP73213_OUTPUT_130_mA                                     0x00
#define MCP73213_OUTPUT_250_mA                                     0x82
#define MCP73213_OUTPUT_550_mA                                     0xCC
#define MCP73213_OUTPUT_1100_mA                                    0xE9
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
    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} mcp73213_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} mcp73213_cfg_t;

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
void mcp73213_cfg_setup ( mcp73213_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mcp73213 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MCP73213_RETVAL mcp73213_init ( mcp73213_t *ctx, mcp73213_cfg_t *cfg );

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
void mcp73213_generic_transfer 
( 
    mcp73213_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic write 8-bit data function
 *
 * @param ctx              Click object.
 * @param command          8-bit data address command
 * @param write_data       8-bit data to write
 *
 * @description Function write 8-bit data via SPI
 * on the MCP4161 chip register on MCP73213 Click board.
 */
void mcp73213_write_data ( mcp73213_t *ctx, uint8_t command, uint8_t write_data );

/**
 * @brief Generic read 8-bit data function
 *
 * @param ctx             Click object.
 * @param command         8-bit data address command
 *
 * @return
 * 8-bit data from address command register
 *
 * @description Function read 8-bit data from address command register
 * on the MCP4161 chip register on MCP73213 Click board.
 */
uint8_t mcp73213_read_data ( mcp73213_t *ctx, uint8_t command );

/**
 * @brief Set values for output current function
 *
 * @param ctx              Click object.
 * @param out_data         8-bit current output value
 *
 * @description Function set values for output current by write outData 
 * to the MCP4161 chip register on MCP73213 Click board.
 */
void mcp73213_set_current_output ( mcp73213_t *ctx, uint8_t out_data );

/**
 * @brief Get the status register data function
 *
 * @param ctx          Click object.
 * 
 * @return
 * 8-bit data from status register
 *
 * @description Function get 8-bit status data from status register
 * on the MCP4161 chip register on MCP73213 Click board.
 */
uint8_t mcp73213_get_status ( mcp73213_t *ctx );

/**
 * @brief Convert ADC value to volatage
 *
 * @param ctx               Click object.
 * @param value_adc         10-bit ADC value
 * @param v_ref             Voltage Reference 3.3V or 5V
 *
 * @return
 * float voltage ( 0V - 3.3V ) or ( 0V - 5.0V )
 *
 * @description Convert 8-bit ADC value to volatage
 * of on MCP73213 Click board.
 */
float mcp73213_convert_output ( uint8_t value_adc, float v_ref );

#ifdef __cplusplus
}
#endif
#endif  // _MCP73213_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

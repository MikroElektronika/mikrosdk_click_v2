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
 * \brief This file contains API for RS232 SPI Click driver.
 *
 * \addtogroup rs232spi RS232 SPI Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS232SPI_H
#define RS232SPI_H

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

#define RS232SPI_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.sdn   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.irq   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS232SPI_RETVAL  uint8_t

#define RS232SPI_OK           0x00
#define RS232SPI_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define RS232SPI_CMD_WRITE_CONF   0xC000
#define RS232SPI_CMD_READ_CONF    0x4000
#define RS232SPI_CMD_WRITE_DATA   0x8000
#define RS232SPI_CMD_READ_DATA    0x0000 
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define RS232SPI_CONF_R       0x8000
#define RS232SPI_CONF_T       0x4000
#define RS232SPI_CONF_RM      0x0400

#define RS232SPI_CONF_FEN     0x2000
#define RS232SPI_CONF_SHDN    0x1000
#define RS232SPI_CONF_TM      0x0800
#define RS232SPI_CONF_PM      0x0200
#define RS232SPI_CONF_RAM     0x0100
#define RS232SPI_CONF_IR      0x0080
#define RS232SPI_CONF_ST      0x0040
#define RS232SPI_CONF_PE      0x0020
#define RS232SPI_CONF_L       0x0010
#define RS232SPI_BAUD         0x000F

#define RS232SPI_CONF_TE      0x400
#define RS232SPI_CONF_RA_FE   0x400
#define RS232SPI_CONF_RTS     0x0200
#define RS232SPI_CONF_CTS     0x0200
#define RS232SPI_CONF_PT      0x0100
#define RS232SPI_CONF_DATA    0x00FF     
/** \} */

/**
 * \defgroup baud_rates_clk_mtp_x1 Baud Rates for Clock Multiplier x1
 * \{
 */
#define RS232SPI_CONF_BAUD_X1_115200   0x0000
#define RS232SPI_CONF_BAUD_X1_57600    0x0001
#define RS232SPI_CONF_BAUD_X1_38400    0x0008
#define RS232SPI_CONF_BAUD_X1_19200    0x0009
#define RS232SPI_CONF_BAUD_X1_9600     0x000A
#define RS232SPI_CONF_BAUD_X1_4800     0x000B
#define RS232SPI_CONF_BAUD_X1_2400     0x000C
#define RS232SPI_CONF_BAUD_X1_1200     0x000D
#define RS232SPI_CONF_BAUD_X1_600      0x000E
#define RS232SPI_CONF_BAUD_X1_300      0x000F
/** \} */

/**
 * \defgroup baud_rates_clk_mtp_x2 Baud Rates for Clock Multiplier x2
 * \{
 */
#define RS232SPI_CONF_BAUD_X2_230400   0x0000 
#define RS232SPI_CONF_BAUD_X2_115200   0x0001 
#define RS232SPI_CONF_BAUD_X2_57600    0x0002 
#define RS232SPI_CONF_BAUD_X2_38400    0x0009 
#define RS232SPI_CONF_BAUD_X2_19200    0x000A 
#define RS232SPI_CONF_BAUD_X2_9600     0x000B 
#define RS232SPI_CONF_BAUD_X2_4800     0x000C 
#define RS232SPI_CONF_BAUD_X2_2400     0x000D 
#define RS232SPI_CONF_BAUD_X2_1200     0x000E 
#define RS232SPI_CONF_BAUD_X2_600      0x000F 
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

    digital_out_t sdn;
    digital_out_t cs;

    // Input pins 

    digital_in_t irq;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rs232spi_t;

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

    pin_name_t sdn;
    pin_name_t irq;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rs232spi_cfg_t;

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
void rs232spi_cfg_setup ( rs232spi_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rs232spi Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RS232SPI_RETVAL rs232spi_init ( rs232spi_t *ctx, rs232spi_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx     Click object.
 * @param speed   Speed variable.
 *
 * @description This function executes default configuration for RS232 SPI click.
 */
void rs232spi_default_cfg ( rs232spi_t *ctx, uint32_t speed );

/**
 * @brief Register write function.
 *
 * @param ctx          Click object.
 * @param write_data   Write data variable.
 *
 * @description This function writes two bytes of data using the SPI serial interface.
 */
void rs232spi_reg_write ( rs232spi_t *ctx, uint16_t write_data );

/**
 * @brief Register read function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads two bytes of data using the SPI serial interface.
 */
uint8_t rs232spi_reg_read ( rs232spi_t *ctx );

/**
 * @brief SPI transfer function.
 *
 * @param ctx          Click object.
 * @param write_data   Write data variable.
 *
 * @description This function reads and writes two bytes of data using the SPI serial interface.
 */
uint16_t rs232spi_transfer ( rs232spi_t *ctx, uint16_t write_data );

/**
 * @brief Read configuration function.
 *
 * @param ctx   Click object.
 *
 * @description This function reads two bytes of data from the configuration register.
 */
uint16_t rs232spi_read_cfg ( rs232spi_t *ctx );

/**
 * @brief Flush function.
 *
 * @param ctx   Click object.
 *
 * @description This function flushes the read buffer.
 */
void rs232spi_flush ( rs232spi_t *ctx );

/**
 * @brief Data ready function.
 *
 * @param ctx   Click object.
 *
 * @description This function checks if the UART is ready to read.
 */
uint16_t rs232spi_data_ready ( rs232spi_t *ctx );

/**
 * @brief Check if busy function.
 *
 * @param ctx   Click object.
 *
 * @description This function checks if the UART is busy.
 */
uint16_t rs232spi_check_busy ( rs232spi_t *ctx );

/**
 * @brief Data write function.
 *
 * @param ctx   Click object.
 *
 * @description This function writes data using the reg_write(...) function.
 */
void rs232spi_data_write ( rs232spi_t *ctx, uint8_t write_data );

/**
 * @brief Digital write reset function.
 *
 * @param ctx      Click object.
 * @param signal   Digital output signal.
 *
 * @description This function writes the specified digital signal to the RST pin.
 */
void rs232spi_digital_write_rst ( rs232spi_t *ctx, uint8_t signal );

/**
 * @brief Digital read interrupt function.
 *
 * @param ctx      Click object.
 *
 * @description This function reads the digital signal from the INT pin.
 */
uint8_t rs232spi_digital_read_int ( rs232spi_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RS232SPI_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

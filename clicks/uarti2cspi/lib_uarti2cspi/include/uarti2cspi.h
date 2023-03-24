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
 * \brief This file contains API for UART I2C/SPI  Click driver.
 *
 * \addtogroup uarti2cspi UART I2C/SPI  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UARTI2CSPI_H
#define UARTI2CSPI_H

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

#define UARTI2CSPI_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define UARTI2CSPI_MASTER_I2C 0
#define UARTI2CSPI_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UARTI2CSPI_RETVAL  uint8_t

#define UARTI2CSPI_OK           0x00
#define UARTI2CSPI_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup ctrl_cfg Control & Configuration
 * \{
 */
#define UARTI2CSPI_OSCILATOR_FREQ       1843200.0
#define UARTI2CSPI_PRESCALER_DEF        1.0      
#define UARTI2CSPI_ADDR                 0x48     
#define UARTI2CSPI_RHR                  0x00 << 3  
#define UARTI2CSPI_THR                  0x00 << 3  
#define UARTI2CSPI_IER                  0x01 << 3  
#define UARTI2CSPI_FCR                  0x02 << 3  
#define UARTI2CSPI_IIR                  0x02 << 3  
#define UARTI2CSPI_LCR                  0x03 << 3  
#define UARTI2CSPI_MCR                  0x04 << 3  
#define UARTI2CSPI_LSR                  0x05 << 3  
#define UARTI2CSPI_MSR                  0x06 << 3  
#define UARTI2CSPI_SPR                  0x07 << 3  
#define UARTI2CSPI_TCR                  0x06 << 3  
#define UARTI2CSPI_TLR                  0x07 << 3  
#define UARTI2CSPI_TXLVL                0x08 << 3  
#define UARTI2CSPI_RXLVL                0x09 << 3  
#define UARTI2CSPI_EFCR                 0x0F << 3  
/** \} */

/**
 * \defgroup spec_enh_reg_set Special/Enhanced Register Set 
 * \{
 */
#define UARTI2CSPI_DLL       0x00 << 3
#define UARTI2CSPI_DLH       0x01 << 3
     
#define UARTI2CSPI_EFR       0x02 << 3
#define UARTI2CSPI_XON1      0x04 << 3
#define UARTI2CSPI_XON2      0x05 << 3
#define UARTI2CSPI_XOFF1     0x06 << 3
#define UARTI2CSPI_XOFF2     0x07 << 3
/** \} */

/**
 * \defgroup bit_fields_init_adv Bit fields Initialization Advanced 
 * \{
 */
#define UARTI2CSPI_UART_5_BIT_DATA       0x00
#define UARTI2CSPI_UART_6_BIT_DATA       0x01
#define UARTI2CSPI_UART_7_BIT_DATA       0x02
#define UARTI2CSPI_UART_8_BIT_DATA       0x03
#define UARTI2CSPI_UART_NOPARITY         0x00
#define UARTI2CSPI_UART_EVENPARITY       0x18
#define UARTI2CSPI_UART_ODDPARITY        0x08
#define UARTI2CSPI_UART_PARITY_ONE       0x38
#define UARTI2CSPI_UART_PARITY_ZERO      0x28
#define UARTI2CSPI_UART_ONE_STOPBIT      0x00
#define UARTI2CSPI_UART_TWO_STOPBITS     0x04
/** \} */

/**
 * \defgroup int_bits Interrupt Bits 
 * \{
 */
#define UARTI2CSPI_CTS_INT_EN                     0x80
#define UARTI2CSPI_RTS_INT_EN                     0x40
#define UARTI2CSPI_XOFF_INT_EN                    0x20
#define UARTI2CSPI_SLEEP_INT_EN                   0x10
#define UARTI2CSPI_MODEM_STATUS_INT_EN            0x08
#define UARTI2CSPI_RECEIVE_LINE_STATUS_INT_EN     0x04
#define UARTI2CSPI_THR_EMPTY_INT_EN               0x02
#define UARTI2CSPI_RXD_INT_EN                     0x01
/** \} */

/**
 * \defgroup flags Flags 
 * \{
 */
#define UARTI2CSPI_DATA_READY                     0x01
#define UARTI2CSPI_DATA_NOT_READY                 0x00
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  uarti2cspi_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *uarti2cspi_master_write_t )( struct uarti2cspi_s*, uint8_t, uint8_t );
typedef void ( *uarti2cspi_master_read_t )( struct uarti2cspi_s*, uint8_t, uint8_t* );

/**
 * @brief Click ctx object definition.
 */
typedef struct uarti2cspi_s
{
   // Output pins 

   digital_out_t cs;
   digital_out_t rst;

   // Input pins 

   digital_in_t int_pin;
    
   // Modules 

   i2c_master_t i2c;
   spi_master_t spi;

   // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   uarti2cspi_master_write_t  write_f;
   uarti2cspi_master_read_t  read_f;
   uarti2cspi_select_t master_sel;

} uarti2cspi_t;

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

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   uarti2cspi_select_t sel;

} uarti2cspi_cfg_t;

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
void uarti2cspi_cfg_setup ( uarti2cspi_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UARTI2CSPI_RETVAL uarti2cspi_init ( uarti2cspi_t *ctx, uarti2cspi_cfg_t *cfg );

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
void uarti2cspi_generic_write ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void uarti2cspi_generic_read ( uarti2cspi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set RST pin state function.
 *
 * @param ctx      Click object.
 * @param state    The state of RST pin.
 *
 * @description This function sets the RST pin state.
 */
void uarti2cspi_set_reset ( uarti2cspi_t *ctx, uint8_t state );

/**
 * @brief Advanced initialization function.
 *
 * @param ctx          Click object.
 * @param baud_rate    Baud rate.
 * @param data_bits    Data bits.
 * @param parity_mode  Parity mode.
 * @param stop_bits    Stop bits.
 *
 * @description This function configures the click module.
 */
void uarti2cspi_advanced_init ( uarti2cspi_t *ctx, uint32_t baud_rate, uint8_t data_bits, 
                                                   uint8_t parity_mode, uint8_t stop_bits );

/**
 * @brief Interrupt enable function.
 *
 * @param ctx        Click object.
 * @param vector     IER vector. 
 *
 * @description This function enables/disables interrupts on the click module by writing the 
 *              specified configuration vector to the Interrupt Enable Register.
 */
void uarti2cspi_interrupt_enable ( uarti2cspi_t *ctx, uint8_t vector );

/**
 * @brief Uart write text function.
 *
 * @param ctx           Click object.
 * @param w_text        Data message pointer.
 *
 * @description This function sends the specified string using UART.
 */
void uarti2cspi_uart_write_text ( uarti2cspi_t *ctx, uint8_t *w_text );

/**
 * @brief Uart write function.
 *
 * @param ctx           Click object.
 * @param w_byte        Data byte.
 *
 * @description This function sends the specified byte using UART.
 */
void uarti2cspi_uart_write ( uarti2cspi_t *ctx, uint8_t w_byte );

/**
 * @brief Uart data ready function.
 *
 * @param ctx           Click object.
 *
 * @return @li @c  0 - DATA NOT READY,
 *         @li @c  1 - DATA READY.
 * 
 * @description This function checks if UART data is ready.
 */
uint8_t uarti2cspi_uart_data_ready ( uarti2cspi_t *ctx );

/**
 * @brief Uart read function.
 *
 * @param ctx Click object.
 * 
 * @return Read data byte.
 * 
 * @description This function reads one byte from the click module.
 */
uint8_t uarti2cspi_uart_read ( uarti2cspi_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _UARTI2CSPI_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

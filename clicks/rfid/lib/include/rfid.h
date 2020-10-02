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
 * \brief This file contains API for rfid Click driver.
 *
 * \addtogroup rfid rfid Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RFID_H
#define RFID_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

#define RFID_MAX_DATA_LEN   0xFF

#define RFID_UART           0x00
#define RFID_SPI            0x01

/**
 * \defgroup Controls
 * \{
 */
#define RFID_SEND_CMD_CRTL  0x00
#define RFID_POLL_CTRL      0x03
#define RFID_READ_CTRL      0x02
#define RFID_RESET_CTRL     0x01
/** \} */

/**
 * \defgroup Commands
 * \{
 */
#define RFID_IDN            0x01
#define RFID_PROT_SELECT    0x02
#define RFID_SEND_RECV      0x04
#define RFID_IDLE           0x07
#define RFID_RD_WAKEUP_REG  0x08
#define RFID_WR_WAKEUP_REG  0x09
#define RFID_SET_BAUD       0x0A
#define RFID_ECHO           0x55
/** \} */

/**
 * \defgroup RFID protocols
 * \{
 */
#define RFID_FIELD_OFF      0x00
#define RFID_ISO_15693      0x01
#define RFID_ISO_14443A     0x02    
#define RFID_ISO_14443B     0x03
#define RFID_ISO_18092NFC   0x04
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define RFID_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RFID_RETVAL  uint8_t

#define RFID_OK           0x00
#define RFID_INIT_ERROR   0xFF
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    digital_out_t cs;
    
    // Output pins 

   digital_out_t an;
   digital_out_t rst;
   digital_out_t pwm;
   digital_out_t int_pin;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rfid_t;

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

   pin_name_t an;
   pin_name_t rst;
   pin_name_t pwm;
   pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rfid_cfg_t;

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
void rfid_cfg_setup ( rfid_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rfid Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RFID_RETVAL rfid_init ( rfid_t *ctx, rfid_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for rfid click.
 */
void rfid_default_cfg ( rfid_t *ctx );

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
void rfid_generic_transfer 
( 
    rfid_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Communication select function.
 *
 * @param ctx           Click object.
 * @param com           Communication macro (value).
 *
 * @description Setting up communication protocol, UART or SPI.
 */
uint8_t rfid_com_select( rfid_t* ctx , uint8_t com );

/**
 * @brief SPI write function.
 *
 * @param ctx           Click object.
 * @param cmd           Command
 * @param len           Number of byte in write data buffer
 * @param w_data        Write data buffer
 *
 * @description Performs SPI write of the control and command value followed by data buffer.
 */
uint8_t rfid_write( rfid_t* ctx , uint8_t cmd , uint8_t len , uint8_t* w_data );

/**
 * @brief Polling function.
 *
 * @param ctx           Click object.
 *
 * @description SPI poll, waits until receive 3rd bit high or pops up after 255 itterations.
 */
uint8_t rfid_poll( rfid_t* ctx );


/**
 * @brief SPI read function.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 * @param len           Number of byte in read data buffer
 *
 * @description Performs SPI read.
 */
void rfid_read( rfid_t* ctx , uint8_t* r_buf , uint8_t len);

/**
 * @brief IDN read function.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 *
 * @description Function reads device IDN using SPI communication.
 */
void rfid_read_idn( rfid_t* ctx , uint8_t* r_buf );

/**
 * @brief Select RFID protocol.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 * @param protocol      Protocol macro (value)
 *
 * @description Select RFID protocol for tag reading using SPI communication.
 */
void rfid_protocol_select( rfid_t* ctx , uint8_t* r_buf , uint8_t protocol );

/**
 * @brief Echo function.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 *
 * @description Write and read echo protocol and cheks return value correctness.
 */
uint8_t rfid_echo( rfid_t* ctx , uint8_t* r_buf );

/**
 * @brief Setting autiomated tag detection.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 *
 * @description Sets automatic tag detection.
 */
void rfid_auto_det( rfid_t* ctx , uint8_t* r_buf  );

/**
 * @brief Index mode.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 *
 * @description Sets index mode.
 */
void rfid_index_mod( rfid_t* ctx , uint8_t* r_buf  );

/**
 * @brief Read tag id function.
 *
 * @param ctx           Click object.
 * @param r_buf         Read data buffer
 *
 * @description Reads rfid tag id, returns 0x87 if no tag.
 */
void rfid_read_nfc_tag( rfid_t* ctx , uint8_t* r_buf );

#ifdef __cplusplus
}
#endif
#endif  // _RFID_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

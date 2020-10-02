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
 * \brief This file contains API for ATA6570 Click driver.
 *
 * \addtogroup ata6570 ATA6570 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ATA6570_H
#define ATA6570_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "drv_uart.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define ATA6570_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
   cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )
   
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ATA6570_RETVAL  uint8_t

#define ATA6570_OK           0x00
#define ATA6570_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * \defgroup registers   Registers
 * \{
 */
#define ATA6570_DMCR        0x01
#define ATA6570_DMSR        0x03
#define ATA6570_SECR        0x04
#define ATA6570_GPM0        0x06
#define ATA6570_GPM1        0x07
#define ATA6570_GPM2        0x08
#define ATA6570_GPM3        0x09
#define ATA6570_RWPR        0x0A
/** \} */

/**
 * \defgroup controle_register
 * \{
 */
#define ATA6570_TRXCR       0x20
#define ATA6570_TRXSR       0x22
#define ATA6570_TRXECR      0x23
#define ATA6570_DRCR        0x26
#define ATA6570_CIDR0       0x27
#define ATA6570_CIDR1       0x28
#define ATA6570_CIDR2       0x29
#define ATA6570_CIDR3       0x2A
#define ATA6570_CIDMR0      0x2B
#define ATA6570_CIDMR1      0x2C
#define ATA6570_CIDMR2      0x2D
#define ATA6570_CIDMR3      0x2E
#define ATA6570_CFCR        0x2F
#define ATA6570_BFECR       0x32
#define ATA6570_BFIR        0x33
#define ATA6570_TRXECR2     0x34
#define ATA6570_TRXESR2     0x35
#define ATA6570_WDCR1       0x36
#define ATA6570_WDCR2       0x37
#define ATA6570_WDSR        0x38
#define ATA6570_WDTRIG      0x39
#define ATA6570_EFCR        0x3A
#define ATA6570_FECR        0x3B
#define ATA6570_GLFT        0x67
#define ATA6570_CDMR0       0x68
#define ATA6570_CDMR1       0x69
#define ATA6570_CDMR2       0x6A
#define ATA6570_CDMR3       0x6B
#define ATA6570_CDMR4       0x6C
#define ATA6570_CDMR5       0x6D
#define ATA6570_CDMR6       0x6E
#define ATA6570_CDMR7       0x6F
#define ATA6570_PWKS        0x4B
#define ATA6570_WKECR       0x4C
#define ATA6570_GESR        0x60
#define ATA6570_SESR        0x61
#define ATA6570_WKESR       0x64
/** \} */

/**
 * \defgroup device_id_register      Device ID Register 
 * \{
 */
#define ATA6570_DIDR        0x7E
/** \} */

/**
 * \defgroup status_register     Status Register
 * \{
 */
#define ATA6570_FUDI        0x70
#define ATA6570_FUDO        0x71
#define ATA6570_FUSEL       0x72
#define ATA6570_BGCAL       0x73
#define ATA6570_FRCCAL      0x74
#define ATA6570_HRCCALL     0x75
#define ATA6570_HRCCALH     0x76
/** \} */

/**
 * \defgroup mode   Mode
 * \{
 */
#define ATA6570_OPMODE_SLEEP   0x01
#define ATA6570_OPMODE_STBY    0x04
#define ATA6570_OPMODE_NORMAL  0x07
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins

    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    uart_t uart;
    
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} ata6570_t;

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

    pin_name_t rx_pin;
    pin_name_t tx_pin;

    // static variables 

        // spi 

        uint32_t spi_speed;
        spi_master_mode_t   spi_mode;
        spi_master_chip_select_polarity_t cs_polarity;

        // uart

        uint32_t          baud_rate;     // Clock speed.
        bool              uart_blocking;
        uart_data_bits_t  data_bit;      // Data bits.
        uart_parity_t     parity_bit;    // Parity bit.  
        uart_stop_bits_t  stop_bit;      // Stop bits.    

} ata6570_cfg_t;

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
void ata6570_cfg_setup ( ata6570_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ATA6570_RETVAL ata6570_init ( ata6570_t *ctx, ata6570_cfg_t *cfg );

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
void ata6570_generic_transfer ( ata6570_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer.
 * @param len          Number of the bytes in the data buffer.
 *
 * @description This function writes data.
 */
void ata6570_generic_multi_write ( ata6570_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic multi read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 *
 * @description This function reads data.
 */
void ata6570_generic_multi_read ( ata6570_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic single read function.
 *
 * @param ctx        Click object.
 * @return one byte data
 *
 * @description This function read one byte data.
 */
char ata6570_generic_single_read ( ata6570_t *ctx );

/**
 * @brief Generic single write function.
 *
 * @param ctx          Click object.
 * @param tx_data      Input data 
 *
 * @description This function write one byte data.
 */
void ata6570_generic_single_write ( ata6570_t *ctx, char tx_data );

/**
 * @brief Write Register
 *
 * @param ctx          Click object.
 * @param address - register address
 * @param input - register data to write
 * 
 * @note 
 * Function uses SPI bus.
 * 
 * @description This function used write register.
 */
void ata6570_write_reg ( ata6570_t *ctx, const uint8_t address, uint8_t input );

/**
 * @brief Read Register
 *
 * @param ctx          Click object.
 * @param address - register address
 * 
 * @note 
 * Function uses SPI bus.
 * 
 * @description This function used write register.
 */
uint8_t ata6570_read_reg ( ata6570_t *ctx, const uint8_t address );

#ifdef __cplusplus
}
#endif
#endif  // _ATA6570_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

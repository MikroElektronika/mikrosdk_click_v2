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
 * \brief This file contains API for DIGI POT 3 Click driver.
 *
 * \addtogroup digipot3 DIGI POT 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DIGIPOT3_H
#define DIGIPOT3_H

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

#define DIGIPOT3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rdy   = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DIGIPOT3_RETVAL  uint8_t

#define DIGIPOT3_OK           0x00
#define DIGIPOT3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup comm Comm
 * \{
 */
#define DIGIPOT3_DO_NOTHING_COMM                    0x00
#define DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM         0x01
#define DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM           0x02
#define DIGIPOT3_DECREMENT_RDAC_6DB_COMM            0x04
#define DIGIPOT3_DECREMENT_RDAC_ONESTEP_COMM        0x06
#define DIGIPOT3_RESTORE_RDAC_WITH_EEMEM_COMM       0x08
#define DIGIPOT3_INCREMENT_RDAC_6DB_COMM            0x0C
#define DIGIPOT3_INCREMENT_RDAC_ONESTEP_COMM        0x0E
/** \} */

/**
 * \defgroup eemem_loc EEMEM LOC
 * \{
 */
#define DIGIPOT3_RDAC_EEMEM_LOC                     0x00
#define DIGIPOT3_O1_O2_EEMEM_LOC                    0x01
#define DIGIPOT3_USER1_EEMEM_LOC                    0x02
#define DIGIPOT3_USER2_EEMEM_LOC                    0x03
#define DIGIPOT3_USER3_EEMEM_LOC                    0x04
#define DIGIPOT3_USER4_EEMEM_LOC                    0x05
#define DIGIPOT3_USER5_EEMEM_LOC                    0x06
#define DIGIPOT3_USER6_EEMEM_LOC                    0x07
#define DIGIPOT3_USER7_EEMEM_LOC                    0x08
#define DIGIPOT3_USER8_EEMEM_LOC                    0x09
#define DIGIPOT3_USER9_EEMEM_LOC                    0x0A
#define DIGIPOT3_USER10_EEMEM_LOC                   0x0B
#define DIGIPOT3_USER11_EEMEM_LOC                   0x0C
#define DIGIPOT3_USER12_EEMEM_LOC                   0x0D
#define DIGIPOT3_USER13_EEMEM_LOC                   0x0E
#define DIGIPOT3_USER14_EEMEM_LOC                   0x0F
/** \} */

/**
 * \defgroup scale Scale
 * \{
 */
#define DIGIPOT3_ZERO_SCALE                         0x0000
#define DIGIPOT3_QUARTER_SCALE                      0x0100
#define DIGIPOT3_HALF_SCALE                         0x0200
#define DIGIPOT3_THREE_QUARTERS_SCALE               0x0300
#define DIGIPOT3_FULL_SCALE                         0x03FF
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
    
    // Input pins 

    digital_in_t an;
    digital_in_t rdy;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} digipot3_t;

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
    pin_name_t rdy;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} digipot3_cfg_t;

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
void digipot3_cfg_setup ( digipot3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DIGIPOT3_RETVAL digipot3_init ( digipot3_t *ctx, digipot3_cfg_t *cfg );

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
void digipot2_generic_transfer ( digipot3_t *ctx, uint8_t *wr_buf, 
                                 uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Command Send function.
 *
 * @param ctx               Click object.
 * @param command_byte      Command which be executed.
 *
 * @description This function executes the desired command.
 */
uint8_t digipot3_send_command ( digipot3_t *ctx, uint8_t command_byte );

/**
 * @brief EEMEM Store function.
 *
 * @param ctx                   Click object.
 * @param location_address      EEMEM location where data be stored.
 * @param transfer_data         Data which be stored.
 *
 * @description This function stores 16-bit data to the desired EEMEM (non volatile) memory location.
 */
uint8_t digipot3_store_eemem ( digipot3_t *ctx, uint8_t location_address, uint16_t transfer_data );

/**
 * @brief EEMEM Read function.
 *
 * @param ctx                   Click object.
 * @param location_address      EEMEM location which from data be read.
 * @param data_out              Buffer where data be stored.
 *
 * @description This function reads 16-bit data from the EEMEM (non volatile) memory location.
 */
uint8_t digipot3_read_eemem ( digipot3_t *ctx, uint8_t location_address, uint16_t *data_out );

/**
 * @brief DAC Write function
 *
 * @param ctx            Click object.
 * @param value_dac      Determines the wiper position.
 *
 * @description This function writes 10-bit value to DAC register and determines the wiper position.
 */
uint8_t digipot3_write_dac ( digipot3_t *ctx, uint16_t value_dac );

/**
 * @brief DAC Read function.
 *
 * @param ctx           Click object.
 * @param data_out      Buffer where DAC value be stored.
 *
 * @description This function reads 10-bit value from DAC register (wiper position).
 */
void digipot3_read_dac ( digipot3_t *ctx, uint16_t *data_out );

/**
 * @brief Data Ready Check function.
 *
 * @param ctx           Click object.
 *
 * @description This function checks is command executed or not.
 */
uint8_t digipot3_check_data_ready( digipot3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DIGIPOT3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

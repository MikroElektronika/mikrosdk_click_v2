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
 * \brief This file contains API for MRAM 2 Click driver.
 *
 * \addtogroup mram2 MRAM 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MRAM2_H
#define MRAM2_H

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

#define MRAM2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MRAM2_RETVAL  uint8_t

#define MRAM2_OK                 0x00
#define MRAM2_INIT_ERROR         0xFF
/** \} */
 
/**
 * \defgroup spi_mode_commands  Spi mode commands
 * \{
 */
#define MRAM2_CMD_RDSR           0x05
#define MRAM2_CMD_WREN           0x06
#define MRAM2_CMD_WRDI           0x04
#define MRAM2_CMD_WRSR           0x01
#define MRAM2_CMD_READ           0x03
#define MRAM2_CMD_FREAD          0x0B
#define MRAM2_CMD_WRITE          0x02
#define MRAM2_CMD_SLEEP          0xB9
#define MRAM2_CMD_WAKE           0xAB
#define MRAM2_CMD_TDET           0x17
#define MRAM2_CMD_TDETX          0x07
#define MRAM2_CMD_RDID           0x4B
/** \} */
 
/**
 * \defgroup status_register  Status register
 * \{
 */
#define MRAM2_STAT_REG_SRWD      0x80
#define MRAM2_STAT_REG_QPI       0x40
#define MRAM2_STAT_REG_BP1       0x08
#define MRAM2_STAT_REG_BP0       0x04
#define MRAM2_STAT_REG_WEL       0x02
/** \} */
 
/**
 * \defgroup execute_in_place  Execute in place
 * \{
 */
#define MRAM2_XIP_SET_CONT       0xEF
#define MRAM2_XIP_RST_STOP       0xFF
/** \} */
 
/**
 * \defgroup pin_states  Pin states
 * \{
 */
#define MRAM2_WP_ENABLE          0x01
#define MRAM2_WP_DISABLE         0x00
#define MRAM2_HLD_ENABLE         0x01
#define MRAM2_HLD_DISABLE        0x00
#define MRAM2_PIN_LOW            0x00
#define MRAM2_PIN_HIGH           0x01
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
    // Output pins 

    digital_out_t rst;
    digital_out_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} mram2_t;

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

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} mram2_cfg_t;

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
void mram2_cfg_setup ( mram2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mram2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MRAM2_RETVAL mram2_init ( mram2_t *ctx, mram2_cfg_t *cfg );

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
void mram2_generic_transfer 
( 
    mram2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Read Status Register function
 *
 * @param ctx          Click object.
 * 
 * @returns 8-bit data representing current status
 *
 * Function is used to read Status register.
**/
uint8_t mram2_rdsr ( mram2_t *ctx );

/**
 * @brief Write Enable function
 *
 * @param ctx          Click object.
 * 
 * Function is used to enable write operation.
**/
void mram2_wren ( mram2_t *ctx );

/**
 * @brief Write Disable function
 *
 * @param ctx          Click object.
 * 
 * Function is used to disable write operation.
**/
void mram2_wrdi ( mram2_t *ctx );

/**
 * @brief Write Status Register function
 *
 * @param ctx       Click object.
 * @param stat_reg  8-bit input walue
 *
 * Function is used to change settings in Status register.
 * @note Write Status Register function will not be work if used before 
 * Write Enable function and if Write protect is enabled.
 * @note QPI Mode Bit, Bit 6, and the WEL Bit, Bit 0, are set by other 
 * commands and cannot be changed by this command.
**/
void mram2_wrsr ( mram2_t *ctx, uint8_t stat_reg );

/**
 * @brief Read Data Bytes  function
 *
 * @param ctx      Click object.
 * @param mem_adr  24-bit memory address entry
 * @param rd_data  data read
 * @param n_bytes  number of bytes to read
 *
 * The Read Data Bytes function allows data bytes to be continuously read
 * starting at an initial address.
**/
void mram2_read ( mram2_t *ctx, uint32_t mem_adr, uint8_t *rd_data, uint8_t n_bytes );

/**
 * @brief Fast Read Data Bytes function
 *
 * @param ctx      Click object.
 * @param mem_adr  24-bit memory address entry
 * @param mode     8-bit XIP operation option
 * @param rd_data  data read
 * @param n_bytes  number of bytes to read
 *
 * The Fast Read Data Bytes function allows data bytes to be continuously read
 * starting at an initial address at the highest frequency.
**/
void mram2_fread ( mram2_t *ctx, uint32_t mem_adr, uint8_t mode, uint8_t *rd_data, uint8_t n_bytes );

/**
 * @brief Write Data Bytes function
 *
 * @param ctx      Click object.
 * @param mem_adr  24-bit memory address entry
 * @param wr_data  8-bit write data
 * @param n_bytes  number of bytes to read
 *
 * The Write Data Bytes function allows data bytes to be written sequentially.
 * @note Write Data Bytes function will not be work if used before
 * Write Enable function and if Write protect is enabled.
**/
void mram2_write ( mram2_t *ctx, uint32_t mem_adr, uint8_t *wr_data, uint8_t n_bytes );

/**
 * @brief Enter Sleep Mode function
 *
 * @param ctx          Click object.
 * 
 * Function is used to place the device into sleep mode.
**/
void mram2_sleep ( mram2_t *ctx );

/**
 * @brief Exit Sleep Mode  function
 *
 * @param ctx          Click object.
 * 
 * Function is used to wake up the device from the sleep mode.
**/
void mram2_wake ( mram2_t *ctx );

/**
 * @brief Tamper Detect (TDET) function
 *
 * @param ctx          Click object.
 * 
 * @returns tamper detect result
 *
 * The Tamper Detect function is used to check whether the memory contents 
 * have been corrupted by exposure to external magnetic fields.
 * @note Any 1�s, of the tamper detect result, present in the 32-bit string 
 * indicate probable corruption of the memory contents.
 * @note After running a TDET function, any other function can be run as the 
 * next function, except another TDET function.
**/
uint32_t mram2_tdet ( mram2_t *ctx );

/**
 * @brief Tamper Detect Exit function
 *
 * @param ctx          Click object.
 * 
 * Function is used to exit the Tamper Detect.
 * @note If another TDET function is to be run, then the Tamper Detect Exit
 * function must be run first to reset the device.
**/
void mram2_tdetx ( mram2_t *ctx );

/**
 * @brief Read ID function
 *
 * @param ctx    Click object.
 * @param rd_id  information that identify the device
 *
 * The Read Device ID function oututs the information that identify the device.
**/
void mram2_rdid ( mram2_t *ctx, uint8_t *rd_id );

/**
 * @brief Write Protect function
 *
 * @param ctx    Click object.
 * @param state  value that defines whether write protect is enabled or not
 *
 * Function is used to eable or disable Write protect.
**/
void mram2_write_protect ( mram2_t *ctx, uint8_t state );

/**
 * @brief Hold function
 *
 * @param ctx    Click object.
 * @param state  value that defines whether Hold is enabled or not
 *
 * Function is used to hold or un-hold the device.
**/
void mram2_hold ( mram2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _MRAM2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

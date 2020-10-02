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
 * \brief This file contains API for MCP16331 INV Click driver.
 *
 * \addtogroup mcp16331inv MCP16331 INV Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MCP16331INV_H
#define MCP16331INV_H

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

#define MCP16331INV_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MCP16331INV_RETVAL  uint8_t

#define MCP16331INV_OK           0x00
#define MCP16331INV_INIT_ERROR   0xFF
/** \} */


/**
 * \defgroup en_di_comm Command witch enables or disables pull up on the VIN
 * \{
 */
#define  MCP16331INV_ENABLE_VIN_PULL_UP     1
#define  MCP16331INV_DISABLE_VIN_PULL_UP    0
/** \} */

/**
 * \defgroup set_gain_comm Command witch sets gain to 1x VREF or 2x VREF
 * \{
 */
#define  MCP16331INV_GAIN_1X_VREF    1
#define  MCP16331INV_GAIN_2X_VREF    0
/** \} */

/**
 * \defgroup act_shd_mode_comm Coomand witch puts device in active or shutdown mode
 * \{
 */
#define  MCP16331INV_ACTIVE_MODE      1
#define  MCP16331INV_SHUTDOWN_MODE    0
/** \} */

/**
 * \defgroup dac_in_val_1x DAC input digital values for determined output analog voltage values, when gain is set up on 1x
 * \{
 */
#define MCP16331INV_MIN_2715_MV_1X_GAIN    0x0000
#define MCP16331INV_2900_MV_1X_GAIN        0x00F5
#define MCP16331INV_3000_MV_1X_GAIN        0x017A
#define MCP16331INV_3100_MV_1X_GAIN        0x01FE
#define MCP16331INV_3300_MV_1X_GAIN        0x02FE
#define MCP16331INV_3500_MV_1X_GAIN        0x03FF
#define MCP16331INV_3700_MV_1X_GAIN        0x04FF
#define MCP16331INV_3900_MV_1X_GAIN        0x05FF
#define MCP16331INV_4000_MV_1X_GAIN        0x0690
#define MCP16331INV_4300_MV_1X_GAIN        0x0810
#define MCP16331INV_5000_MV_1X_GAIN        0x0BAE
#define MCP16331INV_5200_MV_1X_GAIN        0x0CAF
#define MCP16331INV_5300_MV_1X_GAIN        0x0D3F
#define MCP16331INV_MAX_5400_MV_1X_GAIN    0x0FFF
/** \} */

/**
 * \defgroup dac_in_val_2x DAC input digital values for determined output analog voltage values, when gain is set up on 2x
 * \{
 */
#define MCP16331INV_MIN_2715_MV_2X_GAIN    0x0000
#define MCP16331INV_3000_MV_2X_GAIN        0x00B8
#define MCP16331INV_3500_MV_2X_GAIN        0x01FF
#define MCP16331INV_3900_MV_2X_GAIN        0x02FF
#define MCP16331INV_4400_MV_2X_GAIN        0x044F
#define MCP16331INV_4800_MV_2X_GAIN        0x0558
#define MCP16331INV_4900_MV_2X_GAIN        0x0590
#define MCP16331INV_5000_MV_2X_GAIN        0x05D0
#define MCP16331INV_5300_MV_2X_GAIN        0x0690
#define MCP16331INV_MAX_5400_MV_2X_GAIN    0x0FFF

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
    digital_out_t cs;

    // Input pins 

    digital_in_t an;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} mcp16331inv_t;

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

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} mcp16331inv_cfg_t;

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
void mcp16331inv_cfg_setup ( mcp16331inv_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mcp16331inv Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MCP16331INV_RETVAL mcp16331inv_init ( mcp16331inv_t *ctx, mcp16331inv_cfg_t *cfg );

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
void mcp16331inv_generic_transfer 
( 
    mcp16331inv_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief DAC output voltage set function
 *
 * @param ctx            Click object.
 * @param DAC_value      12-bit DAC input value
 * @param gain_value     1 - 1x VREF, 0 - 2x VREF
 * @param mode           1 - active mode, 0 - shutdown mode
 *
 * @description Function determines DAC output voltage value in depending on the input DAC_value (0x0000 - 0x0FFF) and gain_value.
 * Function also can put device on active or shutdown mode.
 */
void mcp16331inv_set_dac_vout ( mcp16331inv_t *ctx, uint16_t dac_value, uint8_t gain_value, uint8_t mode );

/**
 * @brief VIN Pull Up enable function
 *
 * @param ctx            Click object.
 * @param state          1 - enable, 0 - disable
 *
 * @description Function enables or disables internal VIN pull up.
 */
void mcp16331inv_enable_vin ( mcp16331inv_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _MCP16331INV_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

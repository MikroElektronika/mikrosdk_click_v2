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
 * \brief This file contains API for GNSS ZOE Click driver.
 *
 * \addtogroup gnsszoe GNSS ZOE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GNSSZOE_H
#define GNSSZOE_H

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

#define GNSSZOE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.exi = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GNSSZOE_RETVAL  uint8_t

#define GNSSZOE_OK           0x00
#define GNSSZOE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define GNSSZOE_NEMA_GNGGA 1
#define GNSSZOE_NEMA_GNGLL 3
#define GNSSZOE_NEMA_GNGGA_NUM_ELEMENT 15
#define GNSSZOE_NEMA_GNGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define GNSSZOE_GNGGA_TIME                      1 
#define GNSSZOE_GNGGA_LATITUDE                  2
#define GNSSZOE_GNGGA_LATITUDE_SIDE             3
#define GNSSZOE_GNGGA_LONGITUDE                 4
#define GNSSZOE_GNGGA_LONGITUDE_SIDE            5
#define GNSSZOE_GNGGA_QUALITY_INDICATOR         6
#define GNSSZOE_GNGGA_NUMBER_OF_SATELLITES      7
#define GNSSZOE_GNGGA_H_DILUTION_OF_POS         8
#define GNSSZOE_GNGGA_ALTITUDE                  9
#define GNSSZOE_GNGGA_ALTITUDE_UNIT             10
#define GNSSZOE_GNGGA_GEOIDAL_SEPARATION        11
#define GNSSZOE_GNGGA_GEOIDAL_SEPARATION_UNIT   12
#define GNSSZOE_GNGGA_TIME_SINCE_LAST_DGPS      13
#define GNSSZOE_GNGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define GNSSZOE_GNGLL_LATITUDE                  1
#define GNSSZOE_GNGLL_LATITUDE_SIDE             2
#define GNSSZOE_GNGLL_LONGITUDE                 3
#define GNSSZOE_GNGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GNSSZOE_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GNSSZOE_ERROR_START_OR_END_COMMAND 0x8F
#define GNSSZOE_ERROR_NEXT_ELEMENT         0x4F
#define GNSSZOE_ERROR_CURRENT_ELEMENT      0x2F
#define GNSSZOE_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500

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
    digital_out_t exi;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} gnsszoe_t;

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
    pin_name_t exi;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;


} gnsszoe_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t gnsszoe_error_t;

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
void gnsszoe_cfg_setup ( gnsszoe_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gnsszoe Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GNSSZOE_RETVAL gnsszoe_init ( gnsszoe_t *ctx, gnsszoe_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param block        Transfer block structure.
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void gnsszoe_generic_transfer 
( 
    gnsszoe_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic parser function.
 * @param gnsszoe Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gnsszoe_error_t gnsszoe_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param rsp          Read buffer.
 *
 * @description Generic SPI read function, for sending and receiving packages
 */
void gnsszoe_generic_read ( gnsszoe_t *ctx,  uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Reset module.
 * @param gnsszoe Click object.
 */
void gnsszoe_module_reset ( gnsszoe_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _GNSSZOE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

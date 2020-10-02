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
 * \brief This file contains API for Diff pressure Click driver.
 *
 * \addtogroup diffpressure Diff pressure Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DIFFPRESSURE_H
#define DIFFPRESSURE_H

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

#define DIFFPRESSURE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DIFFPRESSURE_RETVAL  uint8_t

#define DIFFPRESSURE_OK           0x01
#define DIFFPRESSURE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup ready  Ready
 * \{
 */
#define DIFFPRESSURE_NOT_RDY        0
#define DIFFPRESSURE_OK_RDY         1
#define DIFFPRESSURE_OVH            2
#define DIFFPRESSURE_OVL            3
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
    // Modules 

    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;

} diffpressure_t;

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
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} diffpressure_cfg_t;

typedef enum
{
	NOT_RDY = 0,
	OVH     = 2,
	OVL     = 3,
        OK      = 1
} status_t;

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
void diffpressure_cfg_setup ( diffpressure_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DIFFPRESSURE_RETVAL diffpressure_init ( diffpressure_t *ctx, diffpressure_cfg_t *cfg );

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
void diffpressure_generic_transfer ( diffpressure_t *ctx, uint8_t *wr_buf, 
                                    uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic read data function.
 *
 * @param ctx          Click object.
 *
 * @description This function read ADC value from Diff Pressure click.
 */
int32_t diffpressure_read_data ( diffpressure_t *ctx );

/**
 * @brief Get kPa Difference function.
 *
 * @param ctx          Click object.
 * @param difference   Click object.
 *
 * @description This function get kPa difference.
 */
int32_t diffpressure_get_kpa_difference ( diffpressure_t *ctx, int32_t difference );

/**
 * @brief Check status of measurement.
 *
 * @param ctx          Click object.
 * @param result       Result.
 *
 * @description This function check status of measurement.
 */
status_t diffpressure_status_check ( diffpressure_t *ctx, int32_t result );

#ifdef __cplusplus
}
#endif
#endif  // _DIFFPRESSURE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Hall Current Click driver.
 *
 * \addtogroup hallcurrent Hall Current Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HALLCURRENT_H
#define HALLCURRENT_H

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
#include "spi_specifics.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define HALLCURRENT_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.ocd   = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HALLCURRENT_OK                      0
#define HALLCURRENT_ERROR                  -1
/** \} */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hallcurrent_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HALLCURRENT_SET_DATA_SAMPLE_EDGE    SET_SPI_DATA_SAMPLE_EDGE
#define HALLCURRENT_SET_DATA_SAMPLE_MIDDLE  SET_SPI_DATA_SAMPLE_MIDDLE

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
    digital_in_t ocd;
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;

} hallcurrent_t;

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
    pin_name_t ocd;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} hallcurrent_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void hallcurrent_cfg_setup ( hallcurrent_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param hallcurrent Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t hallcurrent_init ( hallcurrent_t *ctx, hallcurrent_cfg_t *cfg );

/**
 * @brief Generic read 16-bit data function
 *
 * @return 16-bit read data
 *
 * @details Function read the 16-bit data from the target register address
 * of TLI4970-D050T4 miniature magnetic digital current sensor
 */
uint16_t hallcurrent_read_data ( hallcurrent_t *ctx );

/**
 * @brief Check status of read data function.
 *
 * @return status
 * - 0 : OK, Sensor Value Message.
 * - 1 : ERROR, Sensor Status Message.
 *
 * @details Function read the 16-bit data from the target register address
 * and return 0 if data is valid or 1 of data not valid.
 */
uint8_t hallcurrent_check_status ( hallcurrent_t *ctx );

/**
 * @brief Read electric current function
 *
 * @return float electric current data
 *
 * @details Function read the current data and return 0 if data is not valid.
 */
float hallcurrent_read_current ( hallcurrent_t *ctx );

/**
 * @brief Read OCD pin state function
 *
 * @return Pin logic state
 *
 * @details Reads the OCD pin logic state.
 */
uint8_t hallcurrent_get_ocd_pin ( hallcurrent_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HALLCURRENT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \file digipot5.h
 *
 * \brief This file contains API for DIGI POT 5 Click driver.
 *
 * \addtogroup digipot5 DIGI POT 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _DIGIPOT5_H_
#define _DIGIPOT5_H_

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

#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DIGIPOT5_RETVAL  uint8_t

#define DIGIPOT5_OK           0x00
#define DIGIPOT5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup wp_res Wiper Resistance
 * \{
 */
#define DIGIPOT5_RES_ZEROSCALE         0x00
#define DIGIPOT5_RES_1KOHM             0x1A
#define DIGIPOT5_RES_2KOHM             0x34
#define DIGIPOT5_RES_3KOHM             0x4E
#define DIGIPOT5_RES_5KOHM_HALFSCALE   0x80
#define DIGIPOT5_RES_7KOHM             0xB6
#define DIGIPOT5_RES_8KOHM             0xD0
#define DIGIPOT5_RES_10KOHM_FULLSCALE  0x100
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define DIGIPOT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST  ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS   ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sdi = MIKROBUS( mikrobus, MIKROBUS_MOSI )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click error code definition.
 */
typedef enum
{
    DIGIPOT5_STATUS_OK,
    DIGIPOT5_ERROR_CMD,
    DIGIPOT5_ERROR_INIT_DRV,
    DIGIPOT5_ERROR_REG_ADDR

} digipot5_err_t;

/**
 * @brief Click register address definition.
 */
typedef enum
{
    DIGIPOT5_REG_WIPER0_VOL,
    DIGIPOT5_REG_WIPER1_VOL,
    DIGIPOT5_REG_WIPER0_NONVOL,
    DIGIPOT5_REG_WIPER1_NONVOL,
    DIGIPOT5_REG_TCON0_VOL,
    DIGIPOT5_REG_STATUS_VOL,
    DIGIPOT5_REG_WIPER2_VOL,
    DIGIPOT5_REG_WIPER3_VOL,
    DIGIPOT5_REG_WIPER2_NONVOL,
    DIGIPOT5_REG_WIPER3_NONVOL,
    DIGIPOT5_REG_TCON1_VOL,
    DIGIPOT5_REG_EEPROM0_NONVOL,
    DIGIPOT5_REG_EEPROM1_NONVOL,
    DIGIPOT5_REG_EEPROM2_NONVOL,
    DIGIPOT5_REG_EEPROM3_NONVOL,
    DIGIPOT5_REG_EEPROM4_NONVOL

} digipot5_reg_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    digital_out_t cs;

    //  Reset control pin.
    digital_out_t  rst;

    //  Modules.
    spi_master_t  spi;
    pin_name_t chip_select;

} digipot5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  cs;
    pin_name_t  sck;
    pin_name_t  sdo;
    pin_name_t  sdi;

    //  Additional gpio pin.
    pin_name_t  rst;

    //  SPI config variables.
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} digipot5_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes the click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void
digipot5_cfg_setup( digipot5_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns Init status: 0 - Ok,
 *                       2 - Driver init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
digipot5_err_t
digipot5_init( digipot5_t *ctx, digipot5_cfg_t *cfg );

/**
 * @brief Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function allows the device to be reset and put back to
 * normal operation mode.
 */
void
digipot5_reset( digipot5_t *ctx );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a default configuration for the
 * DIGI POT 5 click.
 */
void
digipot5_default_cfg( digipot5_t *ctx );

/**
 * @brief Generic Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address where data be written.
 * @param data_in  Data to be written.
 *
 * @returns Command status: 0 - Ok,
 *                          1 - Command error,
 *                          3 - Invalid register address.
 *
 * @description This function writes 9 bits wide data to the selected register.
 */
digipot5_err_t
digipot5_generic_write( digipot5_t *ctx, digipot5_reg_t reg_addr,
                        uint16_t data_in );

/**
 * @brief Generic Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address which from data be read.
 * @param data_out  Memory where read data be stored.
 *
 * @returns Command status: 0 - Ok,
 *                          1 - Command error.
 *
 * @description This function reads 9 bits wide data from the selected register.
 */
digipot5_err_t
digipot5_generic_read( digipot5_t *ctx, digipot5_reg_t reg_addr,
                       uint16_t *data_out );

/**
 * @brief Increment Wiper function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Address of wiper which will be incremented.
 *
 * @returns Command status: 0 - Ok,
 *                          1 - Command error,
 *                          3 - Invalid register address.
 *
 * @description This function allows the selected wiper to be incremented.
 */
digipot5_reg_t
digipot5_increment_wiper( digipot5_t *ctx, digipot5_reg_t reg_addr );

/**
 * @brief Decrement Wiper function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Address of wiper which will be decremented.
 *
 * @returns Command status: 0 - Ok,
 *                          1 - Command error,
 *                          3 - Invalid register address.
 *
 * @description This function allows the selected wiper to be decremented.
 */
digipot5_reg_t
digipot5_decrement_wiper( digipot5_t *ctx, digipot5_reg_t reg_addr );

#ifdef __cplusplus
}
#endif
#endif  //  _DIGIPOT5_H_

/** \} */ //  End public_function group
/// \}    //  End digipot5 group
/*! @} */
// ------------------------------------------------------------------------ END

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
 * \brief This file contains API for DC Motor 10 Click driver.
 *
 * \addtogroup dcmotor10 DC Motor 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR10_H
#define DCMOTOR10_H

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

#define DCMOTOR10_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.inh = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR10_RETVAL  uint8_t

#define DCMOTOR10_OK           0x00
#define DCMOTOR10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup in_data_protocol Input Data Protocol
 * \{
 */
#define DCMOTOR10_STATUS_REG_RST          0x0001
#define DCMOTOR10_LS_SWITCH_1             0x0002
#define DCMOTOR10_HS_SWITCH_1             0x0004
#define DCMOTOR10_LS_SWITCH_2             0x0008
#define DCMOTOR10_HS_SWITCH_2             0x0010
#define DCMOTOR10_LS_SWITCH_3             0x0020
#define DCMOTOR10_HS_SWITCH_3             0x0040
#define DCMOTOR10_LS_SWITCH_4             0x0080
#define DCMOTOR10_HS_SWITCH_4             0x0100
#define DCMOTOR10_LS_SWITCH_5             0x0200
#define DCMOTOR10_HS_SWITCH_5             0x0400
#define DCMOTOR10_LS_SWITCH_6             0x0800
#define DCMOTOR10_HS_SWITCH_6             0x1000
#define DCMOTOR10_OVERCURRENT_SHUT_DOWN   0x2000
#define DCMOTOR10_UNDERLOAD_SHUT_DOWN     0x4000
#define DCMOTOR10_OVER_VOLT_LOCKOUT       0x8000
/** \} */

/**
 * \defgroup diag_data_protocol Diagnosis Data Protocol
 * \{
 */
#define DCMOTOR10_TEMP_PREWARNING         0x0001
#define DCMOTOR10_STATUS_LS_SWITCH_1      0x0002
#define DCMOTOR10_STATUS_HS_SWITCH_1      0x0004
#define DCMOTOR10_STATUS_LS_SWITCH_2      0x0008
#define DCMOTOR10_STATUS_HS_SWITCH_2      0x0010
#define DCMOTOR10_STATUS_LS_SWITCH_3      0x0020
#define DCMOTOR10_STATUS_HS_SWITCH_3      0x0040
#define DCMOTOR10_STATUS_LS_SWITCH_4      0x0080
#define DCMOTOR10_STATUS_HS_SWITCH_4      0x0100
#define DCMOTOR10_STATUS_LS_SWITCH_5      0x0200
#define DCMOTOR10_STATUS_HS_SWITCH_5      0x0400
#define DCMOTOR10_STATUS_LS_SWITCH_6      0x0800
#define DCMOTOR10_STATUS_HS_SWITCH_6      0x1000
#define DCMOTOR10_OVERLOAD                0x2000
#define DCMOTOR10_UNDERLOAD               0x4000
#define DCMOTOR10_POWER_SUPPLY_FAIL       0x8000
/** \} */

/**
 * \defgroup fault_res Fault Result
 * \{
 */
#define DCMOTOR10_OVERCURRENT_FAULT          0x2000
#define DCMOTOR10_GND_SHORT_CIRCUIT          0x2000
#define DCMOTOR10_VS_SHORT_CIRCUIT           0x2000
#define DCMOTOR10_TEMP_WARNING               0x0001
#define DCMOTOR10_OPENLOAD_FAULT             0x4000
#define DCMOTOR10_UNDERLOAD_FAULT            0x4000
#define DCMOTOR10_UNDER_VOLT_LOCKOUT_FAULT   0x8000
#define DCMOTOR10_OVER_VOLT_LOCKOUT_FAULT    0x8000
/** \} */

/**
 * \defgroup enable_cmd Enable commands
 * \{
 */
#define DCMOTOR10_RESET_STATUS_REG  0x0001
#define DCMOTOR10_ENABLE_1          0x000E
#define DCMOTOR10_ENABLE_2          0x0038
#define DCMOTOR10_ENABLE_3          0x00E0
#define DCMOTOR10_ENABLE_4          0x0380
#define DCMOTOR10_ENABLE_5          0x0E00
#define DCMOTOR10_ENABLE_6          0x3800
#define DCMOTOR10_ENABLE_ALL        0x1FFE
/** \} */

/**
 * \defgroup enable_h_brg_cmd Enable H bridge commands
 * \{
 */
#define DCMOTOR10_HB_ENABLE_1_CV    0x000C
#define DCMOTOR10_HB_ENABLE_1_CCV   0x0012
#define DCMOTOR10_HB_ENABLE_2_CV    0x0030
#define DCMOTOR10_HB_ENABLE_2_CCV   0x0048
#define DCMOTOR10_HB_ENABLE_3_CV    0x00C0
#define DCMOTOR10_HB_ENABLE_3_CCV   0x0120
#define DCMOTOR10_HB_ENABLE_4_CV    0x0300
#define DCMOTOR10_HB_ENABLE_4_CCV   0x0480
#define DCMOTOR10_HB_ENABLE_5_CV    0x0C00
#define DCMOTOR10_HB_ENABLE_5_CCV   0x1200
/** \} */

/**
 * \defgroup cmd_set Inhibit pin settings and data filter
 * \{
 */
#define DCMOTOR10_8_BIT_DATA 0xFF
#define DCMOTOR10_INHIBIT 0x00
#define DCMOTOR10_UNINHIBIT 0x01
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
    // Output pins 

    digital_out_t cs;
    digital_out_t inh;
    
    // Modules 

    spi_master_t spi;

    // Ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;

} dcmotor10_t;

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

    pin_name_t inh;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} dcmotor10_cfg_t;

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
void dcmotor10_cfg_setup ( dcmotor10_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR10_RETVAL dcmotor10_init ( dcmotor10_t *ctx, dcmotor10_cfg_t *cfg );

/**
 * @brief Send command function
 *
 * @param ctx          Click object.
 * @param wr_data  16-bit input command
 *
 * @description Function is used to send command.
 * @note Consult datasheet in order to discern what to write into register or use predefined values.
**/
void dcmotor10_send_cmd ( dcmotor10_t *ctx, uint16_t wr_data );

/**
 * @brief Read status function
 *
 * @param ctx          Click object.
 * 
 * @returns result 16-bit status value
 *
 * @description Function is used to read status.
 * @note Use datasheet to discerm what value from register represents.
**/
uint16_t dcmotor10_read_status ( dcmotor10_t *ctx );

/**
 * @brief Inhibit device function
 *
 * @param ctx          Click object.
 * @param state        8-bit command.
 * 
 * @description Function is used to inhibit or uninhibit the device.
**/
void dcmotor10_inhibit ( dcmotor10_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR10_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

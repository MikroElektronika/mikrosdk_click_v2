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
 * \brief This file contains API for BALANCER 2 Click driver.
 *
 * \addtogroup balancer2 BALANCER 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BALANCER2_H
#define BALANCER2_H

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

#define BALANCER2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.cell2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.cell1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.stat = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BALANCER2_RETVAL  uint8_t

#define BALANCER2_OK           0x00
#define BALANCER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup referent_voltage Referent voltage
 * \{
 */
#define BALANCER2_VREF_5V                         5000
#define BALANCER2_VREF_3V3                        3300
/** \} */

/**
 * \defgroup command_mode Command mode
 * \{
 */
#define BALANCER2_CMD_START                        0x01
#define BALANCER2_CMD_MSBF_LSB                     0x20
#define BALANCER2_CMD_MSBF_MSB                     0x00
#define BALANCER2_CMD_SINGLE_MODE_CH0              0x80
#define BALANCER2_CMD_SINGLE_MODE_CH1              0xC0
#define BALANCER2_CMD_DIFF_MODE_CH0M_CH1P          0x40
#define BALANCER2_CMD_DIFF_MODE_CH0P_CH1M          0x00
#define BALANCER2_CMD_DUMMY                        0x00
/** \} */

/**
 * \defgroup mask Mask
 * \{
 */
#define BALANCER2_MASK                             0x0F
/** \} */

/**
 * \defgroup mode_select Mode select
 * \{
 */
#define BALANCER2_BATT1                            0xAA
#define BALANCER2_BATT2                            0xBB
#define BALANCER2_BATT_BOTH                        0xCC
/** \} */

/**
 * \defgroup pin_state Pin state
 * \{
 */
#define BALANCER2_PIN_STATE_HIGH                   1
#define BALANCER2_PIN_STATE_LOW                    0
/** \} */

/**
 * \defgroup mode_charging Mode charging
 * \{
 */
#define BALANCER2_MODE_CHARGING                    0x10
#define BALANCER2_MODE_BALANCING_P                 0x20
#define BALANCER2_MODE_BALANCING_NP                0x30
#define BALANCER2_MODE_BALANCING_PP                0x40
#define BALANCER2_MODE_BALANCING_NPP               0x50
#define BALANCER2_MODE_BALANCING_P1                0x60
#define BALANCER2_MODE_BALANCING_NP1               0x70
#define BALANCER2_MODE_BALANCING_P2                0x80
#define BALANCER2_MODE_BALANCING_NP2               0x90
/** \} */

/**
 * \defgroup number Number
 * \{
 */
#define CHN_0_MV_MULT                              3.0
#define CHN_1_MV_MULT                              1.5
#define ADC_RESOLUTION                             4096.0
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

    digital_out_t  cs;
    digital_out_t  cell2;
    digital_out_t  int_pin;
    digital_out_t  cell1;
    digital_out_t  stat;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} balancer2_t;

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

    pin_name_t  cell2;
    pin_name_t  int_pin;
    pin_name_t  cell1;
    pin_name_t  stat;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} balancer2_cfg_t;

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
void balancer2_cfg_setup ( balancer2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BALANCER2_RETVAL balancer2_init ( balancer2_t *ctx, balancer2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for BALANCER 2 click.
 */
void balancer2_default_cfg ( balancer2_t *ctx );

/**
 * @brief Generic function for setting cell 1 pin status.
 *
 * @param ctx          Click object.
 * @param state        State of the pin.
 *
 * @description This function setting cell 1 pin status.
 */
void balancer2_cell_1_state ( balancer2_t *ctx, uint8_t state );

/**
 * @brief Generic function for setting  cell 2 pin status.
 *
 * @param ctx          Click object.
 * @param state        State of the pin.
 *
 * @description This function setting cell 2 pin status.
 */
void balancer2_cell_2_state ( balancer2_t *ctx, uint8_t state );

/**
 * @brief Generic function for setting supply pin status.
 *
 * @param ctx          Click object.
 * @param state        State of the pin.
 *
 * @description This function setting supply pin status.
 */
void balancer2_supply_state ( balancer2_t *ctx, uint8_t state );

/**
 * @brief Generic function for setting status led pin status.
 *
 * @param ctx          Click object.
 * @param state        State of the pin.
 *
 * @description This function setting status led pin status.
 */
void balancer2_status_led_state ( balancer2_t *ctx, uint8_t state );

/**
 * @brief Function for reading adc value.
 * 
 * @param ctx          Click object.
 * @param cmd_byte     Command byte.
 * 
 * @return Return read adc value
 *
 * @description This function setting status led pin status.
 */
uint16_t balancer2_read_adc ( balancer2_t *ctx, uint8_t cmd_byte );

/**
 * @brief Function for setting reference value.
 *
 * @param ctx          Click object.
 * @param vref         Reference value.
 */
void balancer2_set_vref ( balancer2_t *ctx, uint16_t vref );

/**
 * @brief Function for getting real battery lvl.
 * 
 * @param ctx          Click object.
 * @param bat_num      Battery macro.
 * 
 * @return Return lvl of selected battery
 *
 * @description This function getting real battery lvl.
 */
float balancer2_get_batttery_lvl ( balancer2_t *ctx, uint8_t bat_num );

/**
 * @brief Function for converting adc value to mV.
 * 
 * @param ctx          Click object.
 * @param adc_val      Adc value.
 * 
 * @return Return converted data
 *
 * @description This function converting adc value to mV.
 */
float balancer2_adc_to_mv ( balancer2_t *ctx, uint16_t adc_val );

#ifdef __cplusplus
}
#endif
#endif  // _BALANCER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

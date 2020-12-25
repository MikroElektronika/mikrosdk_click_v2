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
 * \brief This file contains API for c2x20W Amp Click driver.
 *
 * \addtogroup c2x20wamp c2x20W Amp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C2X20WAMP_H
#define C2X20WAMP_H

#include "drv_digital_out.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define C2X20WAMP_MAP_MIKROBUS( cfg, mikrobus )   \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
  cfg.shdn = MIKROBUS( mikrobus, MIKROBUS_RST );  \
  cfg.mute = MIKROBUS( mikrobus, MIKROBUS_CS );   \
  cfg.addr1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.addr2 = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C2X20WAMP_RETVAL  int8_t

#define C2X20WAMP_OK             0
#define C2X20WAMP_INIT_ERROR   (-1)
/** \} */

/**
 * \defgroup i2c_address I2C slave address
 * \{
 */
#define C2X20WAMP_I2C_ADDRESS                                     0x48
/** \} */

/**
 * \defgroup check_ad1 Channel address
 * \{
 */
#define C2X20WAMP_ADDRESS_1                                       0x01 
#define C2X20WAMP_ADDRESS_2                                       0x02
/** \} */

/**
 * \defgroup cmd Commands
 * \{
 */
#define C2X20WAMP_6_BIT_VALUE                                     0x3F
#define C2X20WAMP_CMD_VOLUME_UP                                   0xC4
#define C2X20WAMP_CMD_VOLUME_DOWN                                 0xC5
#define C2X20WAMP_CMD_FILTERLESS_MODULATION                       0x40
#define C2X20WAMP_CMD_CLASSIC_PWM_MODULATION                      0x41
/** \} */

/**
 * \defgroup bit_mask Bit mask
 * \{
 */
#define C2X20WAMP_6_BIT_VALUE                                     0x3F
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

    digital_out_t shdn;
    digital_out_t mute;

    // Input pins 

    digital_out_t addr1;
    digital_out_t addr2;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c2x20wamp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t shdn;
    pin_name_t mute;
    pin_name_t addr1;
    pin_name_t addr2;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c2x20wamp_cfg_t;

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
void c2x20wamp_cfg_setup ( c2x20wamp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c2x20wamp Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C2X20WAMP_RETVAL c2x20wamp_init ( c2x20wamp_t *ctx, c2x20wamp_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 *
 * @description This function writes data to the desired register.
 */
void c2x20wamp_generic_write ( c2x20wamp_t *ctx, uint8_t data_buf );


/**
 * @brief Set Play mode of the amplifier function
 *
 * @param ctx          Click object.
 * 
 * Function set Play operating mode of the amplifier
 * by clear MUTE pin of 2x20W Amp Click.
 */
void c2x20wamp_mode_play( c2x20wamp_t *ctx );

/**
 * @brief Set Mute mode of the amplifier function
 * 
 * @param ctx          Click object.
 * 
 * Function set Mute operating mode of the amplifier
 * by set MUTE pin of 2x20W Amp Click.
 */
void c2x20wamp_mode_mute( c2x20wamp_t *ctx );

/**
 * @brief Disable the amplifier function
 *
 * @param ctx          Click object.
 * 
 * Function disable the amplifier
 * by clear SHDN pin of 2x20W Amp Click.
 */
void c2x20wamp_disable( c2x20wamp_t *ctx );

/**
 * @brief Enable the amplifier function
 * 
 * @param ctx          Click object.
 * 
 * Function enable the amplifier
 * by set SHDN pin of 2x20W Amp Click.
 */
void c2x20wamp_enable( c2x20wamp_t *ctx );

/**
 * @brief Set volume of the amplifier function
 * 
 * @param ctx          Click object.
 *
 * @param[in] volume
 * - minimum volume :  0
 * - maximum volume : 63
 *
 * Function set volume of the amplifier 
 * by write volume value
 * to the MAX9744ETH+T chip on 2x20W Amp Click.
 */
void c2x20wamp_set_volume( c2x20wamp_t *ctx, uint8_t volume );

/**
 * @brief Increase the volume by one level function
 *
 * Function increase the volume by one level 
 * by write increases command ( 0xC4 )
 * to the MAX9744ETH+T chip on 2x20W Amp Click.
 */
void c2x20wamp_volume_up( c2x20wamp_t *ctx );

/**
 * @brief Decrease the volume by one level function
 * 
 * @param ctx          Click object.
 *
 * Function decrease the volume by one level
 * by write decreases command( 0xC5 )
 * to the MAX9744ETH+T chip on 2x20W Amp Click.
 */
void c2x20wamp_volume_down( c2x20wamp_t *ctx );

/**
 * @brief Set filterless output modulation function
 * 
 * @param ctx          Click object.
 *
 * Function set filterless output modulation
 * by write filterless command ( 0x40 )
 * to the MAX9744ETH+T chip on 2x20W Amp Click.
 */
void c2x20wamp_filterless_modulation( c2x20wamp_t *ctx );

/**
 * @brief Set classic PWM output modulation function
 * 
 * @param ctx          Click object.
 *
 * Function set classic PWM output modulation
 * by write classic PWM command ( 0x41 )
 * to the MAX9744ETH+T chip on 2x20W Amp Click.
 */
void c2x20wamp_classic_pwm_modulation( c2x20wamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // C2X20WAMP_H

/** \} */ // End public_function group
/** \} */ // End click Driver group  

// ------------------------------------------------------------------------ END

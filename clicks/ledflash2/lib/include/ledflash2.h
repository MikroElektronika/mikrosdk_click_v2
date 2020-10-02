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
 * \brief This file contains API for Led Flash 2 Click driver.
 *
 * \addtogroup ledflash2 Led Flash 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDFLASH2_H
#define LEDFLASH2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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
#define LEDFLASH2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.fi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.fen = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.ten = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDFLASH2_RETVAL  uint8_t

#define LEDFLASH2_OK                    0x00
#define LEDFLASH2_INIT_ERROR            0xFF
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define LEDFLASH2_MODE_OFF              0x00
#define LEDFLASH2_MODE_FLASH            0x01
#define LEDFLASH2_MODE_TORCH            0x02
/** \} */

/**
 * \defgroup cur Cur
 * \{
 */
#define LEDFLASH2_CUR_100               0x00
#define LEDFLASH2_CUR_90                0x01
#define LEDFLASH2_CUR_80                0x02
#define LEDFLASH2_CUR_70                0x03
#define LEDFLASH2_CUR_63                0x04
#define LEDFLASH2_CUR_56                0x05
#define LEDFLASH2_CUR_50                0x06
#define LEDFLASH2_CUR_44                0x07
#define LEDFLASH2_CUR_39                0x08
#define LEDFLASH2_CUR_35                0x09
#define LEDFLASH2_CUR_31                0x0A
#define LEDFLASH2_CUR_28                0x0B
#define LEDFLASH2_CUR_25                0x0C
#define LEDFLASH2_CUR_22                0x0D
#define LEDFLASH2_CUR_20                0x0E
#define LEDFLASH2_CUR_18                0x0F
/** \} */

/**
 * \defgroup ftmr Ftmr
 * \{
 */
#define LEDFLASH2_FTMR_1250             0xE0
#define LEDFLASH2_FTMR_1093             0xC0
#define LEDFLASH2_FTMR_937              0xA0
#define LEDFLASH2_FTMR_781              0x80
#define LEDFLASH2_FTMR_625              0x60
#define LEDFLASH2_FTMR_468              0x40
#define LEDFLASH2_FTMR_312              0x20
#define LEDFLASH2_FTMR_156              0x00
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

    digital_out_t fi;
    digital_out_t en;
    digital_out_t fen;
    digital_out_t ten;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} ledflash2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t fi;
    pin_name_t en;
    pin_name_t fen;
    pin_name_t ten;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} ledflash2_cfg_t;

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
void ledflash2_cfg_setup ( ledflash2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ledflash2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LEDFLASH2_RETVAL ledflash2_init ( ledflash2_t *ctx, ledflash2_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void ledflash2_generic_write ( ledflash2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void ledflash2_generic_read ( ledflash2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read register function.
 *
 * @param ctx              Click object.
 * @param reg_address      Register address.
 *
 * @description This function reads raw data from any register.
 */
uint8_t ledflash2_read_register ( ledflash2_t *ctx, uint8_t reg_address );

/**
 * @brief Write register function.
 *
 * @param ctx              Click object.
 * @param reg_address      Register address.
 * @param reg_data         Data to write.
 *
 * @description This function writes data into any register.
 */
void ledflash2_write_register ( ledflash2_t *ctx, uint8_t reg_address, uint8_t reg_data );

/**
 * @brief Set mode function.
 *
 * @param ctx               Click object.
 * @param mode              Mode to select.
 * @param intensity         Led intensity.
 * @param flash_duration    Flash duration.
 *
 * @description This control function that sets the click into one of the three available modes.
 * OFF mode requires no additional parameters, and will ignore intensity and
 * duration. 
 * Flash mode will set both the intensity and duration, and will set them to
 * default value (100% intensity, 156 duration) if 0 values are passed instead.
 * Torch mode only requires intensity parameter. It will ignore duration
 * parameter, and will set the intensity to default (100 %) if intensity 
 * parameter is 0.
 */
void ledflash2_set_mode ( ledflash2_t *ctx, uint8_t mode, uint8_t intensity, uint8_t flash_duration );

/**
 * @brief Toggle flash inhibit function.
 *
 * @param ctx            Click object.
 * @param pin_state      Flash inhibit on or off.
 *
 * @description This function will set the flash inhibit pin to either 1 or 0. It should be
 * used when click is in flash mode, to reduce the flash intensity.
 */
void ledflash2_toggle_flash_inhibit ( ledflash2_t *ctx, uint8_t pin_state );

#ifdef __cplusplus
}
#endif
#endif  // _LEDFLASH2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

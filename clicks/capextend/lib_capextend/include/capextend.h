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
 * \brief This file contains API for Cap Extend Click driver.
 *
 * \addtogroup capextend Cap Extend Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPEXTEND_H
#define CAPEXTEND_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define CAPEXTEND_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPEXTEND_RETVAL  uint8_t

#define CAPEXTEND_OK           0x00
#define CAPEXTEND_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup spm_registers SPM Registers
 * \{
 */
#define CAPEXTEND_SPM_CFG          0x0D
#define CAPEXTEND_SPM_BASE_ADDR    0x0E
#define CAPEXTEND_SPM_KEY_MSB      0xAC
#define CAPEXTEND_SPM_KEY_LSB      0xAD
/** \} */

/**
 * \defgroup blocks_for_spm Blocks For SPM
 * \{
 */
#define CAPEXTEND_BLOCK_1     0x00
#define CAPEXTEND_BLOCK_2     0x08
#define CAPEXTEND_BLOCK_3     0x10
#define CAPEXTEND_BLOCK_4     0x20
#define CAPEXTEND_BLOCK_5     0x28
#define CAPEXTEND_BLOCK_6     0x30
#define CAPEXTEND_BLOCK_7     0x38
#define CAPEXTEND_BLOCK_8     0x40
#define CAPEXTEND_BLOCK_9     0x48
#define CAPEXTEND_BLOCK_10    0x50
#define CAPEXTEND_BLOCK_11    0x58
#define CAPEXTEND_BLOCK_12    0x60
#define CAPEXTEND_BLOCK_13    0x68
#define CAPEXTEND_BLOCK_14    0x70
#define CAPEXTEND_BLOCK_15    0x78
/** \} */

/**
 * \defgroup i2c_registers I2C Registers
 * \{
 */
#define CAPEXTEND_IRQ_SRC          0x00
#define CAPEXTEND_CAP_STAT_MSB     0x01
#define CAPEXTEND_CAP_STAT_LSB     0x02
#define CAPEXTEND_GPI_STAT         0x07
#define CAPEXTEND_SPM_STAT         0x08
#define CAPEXTEND_COMP_OP_MODE     0x09
#define CAPEXTEND_GPO_CTRL         0x0A
#define CAPEXTEND_GPP_PIN_ID       0x0B
#define CAPEXTEND_GPP_INTENSITY    0x0C
#define CAPEXTEND_SOFT_RESET       0xB1
#define CAPEXTEND_MON_SCAN_PER     0xF9
#define CAPEXTEND_SLAVE_ADDRESS    0x2B
/** \} */

/**
 * \defgroup real_time_monitoring_addresses Real Time Monitoring Addresses
 * \{
 */
#define CAPEXTEND_CAP_DIFF_BA    0xB4
#define CAPEXTEND_CAP_RAW_BA     0x80
#define CAPEXTEND_CAP_AVG_BA     0x9A
/** \} */

/**
 * \defgroup real_time_monitoring_blocks Real Time Monitoring Blocks
 * \{
 */
#define CAPEXTEND_CAP_DIFF_BLK_1         0xB4
#define CAPEXTEND_CAP_DIFF_BLK_2         0xBC
#define CAPEXTEND_CAP_DIFF_BLK_3         0xC4
#define CAPEXTEND_CAP_AVG_BLK_1          0x80
#define CAPEXTEND_CAP_AVG_BLK_2          0x88
#define CAPEXTEND_CAP_AVG_BLK_3          0x90
#define CAPEXTEND_CAP_RAW_BLK_1          0x9A
#define CAPEXTEND_CAP_RAW_BLK_2          0xA2
#define CAPEXTEND_CAP_RAW_BLK_3          0xAA
#define CAPEXTEND_GPIO_0                 0x00
#define CAPEXTEND_GPIO_1                 0x01
#define CAPEXTEND_GPIO_2                 0x02
#define CAPEXTEND_GPIO_3                 0x03
#define CAPEXTEND_GPIO_4                 0x04
#define CAPEXTEND_GPIO_5                 0x05
#define CAPEXTEND_GPIO_6                 0x06
#define CAPEXTEND_GPIO_7                 0x07
#define CAPEXTEND_GPIO_ALL               0x08
#define CAPEXTEND_COMMON_SETTINGS        0x01
#define CAPEXTEND_INDIVIDUAL_SETTINGS    0x04
#define CAPEXTEND_DISABLED               0x00
#define CAPEXTEND_BUTTON                 0x01
#define CAPEXTEND_MULTI_TOUCH            0x00
#define CAPEXTEND_SINGLE_TOUCH           0x01
#define CAPEXTEND_INT_MASKED             0x00
#define CAPEXTEND_INT_TOUCH              0x01
#define CAPEXTEND_INT_RELEASE            0x02    
#define CAPEXTEND_INT_BOTH_TR            0x03
#define CAPEXTEND_SMPL_0                 0x00
#define CAPEXTEND_SMPL_2                 0x01
#define CAPEXTEND_SMPL_3                 0x02      
#define CAPEXTEND_SMPL_4                 0x03
#define CAPEXTEND_BTN_0                  0x00
#define CAPEXTEND_BTN_1                  0x01              
#define CAPEXTEND_BTN_2                  0x02              
#define CAPEXTEND_BTN_3                  0x03              
#define CAPEXTEND_BTN_4                  0x04              
#define CAPEXTEND_BTN_5                  0x05              
#define CAPEXTEND_BTN_6                  0x06              
#define CAPEXTEND_BTN_7                  0x07              
#define CAPEXTEND_BTN_8                  0x08              
#define CAPEXTEND_BTN_9                  0x09              
#define CAPEXTEND_BTN_10                 0x0A
#define CAPEXTEND_BTN_11                 0x0B
#define CAPEXTEND_GROUP_0                0x0C
#define CAPEXTEND_GROUP_1                0x0D
#define CAPEXTEND_GPO                    0x00
#define CAPEXTEND_GPP                    0x01   
#define CAPEXTEND_GPI                    0x02
#define CAPEXTEND_LOG                    0x00
#define CAPEXTEND_LIN                    0x01
#define CAPEXTEND_EVERY_TIME             0x00
#define CAPEXTEND_EVERY_16               0x01
#define CAPEXTEND_NONE                   0x00
#define CAPEXTEND_PULLUP                 0x01
#define CAPEXTEND_PULLDOWN               0x02
#define CAPEXTEND_NO_INT                 0x00
#define CAPEXTEND_RISING                 0x01
#define CAPEXTEND_FALLING                0x02
#define CAPEXTEND_BOTH                   0x03
#define CAPEXTEND_OP_MODE_INT            0x01
#define CAPEXTEND_COMP_INT               0x02
#define CAPEXTEND_BUTTON_INT             0x04
#define CAPEXTEND_GPI_INT                0x10
#define CAPEXTEND_SPM_INT                0x20
#define CAPEXTEND_NVM_INT                0x40
#define CAPEXTEND_ACTIVE_MODE            0x00 
#define CAPEXTEND_DOZE_MODE              0x01
#define CAPEXTEND_SLEEP_MODE             0x02
#define CAPEXTEND_RAW                    0x00
#define CAPEXTEND_AVG                    0x01
#define CAPEXTEND_DIFF                   0x02
#define CAPEXTEND_MSB_BUTTONS_ADDR       0x01
#define CAPEXTEND_LSB_BUTTONS_ADDR       0x02
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

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} capextend_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} capextend_cfg_t;

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
void capextend_cfg_setup ( capextend_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param capextend Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPEXTEND_RETVAL capextend_init ( capextend_t *ctx, capextend_cfg_t *cfg );

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
void capextend_generic_write ( capextend_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void capextend_generic_read ( capextend_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read MSB buttons function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the MSB button map data.
 */
int8_t capextend_read_msb_buttons ( capextend_t *ctx );

/**
 * @brief Read LSB buttons function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the LSB button map data.
 */
int8_t capextend_read_lsb_buttons ( capextend_t *ctx );

/**
 * @brief Read buttons function.
 *
 * @param ctx          Click object.
 * 
 * @retval Returns 12bit data of buttons state.
 *
 * @description This function reads the button map data.
 */
uint16_t capextend_read_buttons ( capextend_t *ctx );

/**
 * @brief Reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function does a software reset of the click module.
 */
void capextend_reset ( capextend_t *ctx );

/**
 * @brief Set reset high function.
 *
 * @param ctx          Click object.
 *
 * @description This function sets the output voltage on the reset pin to high.
 */
void capextend_set_rst_high ( capextend_t *ctx );

/**
 * @brief Set reset low function.
 *
 * @param ctx          Click object.
 *
 * @description This function sets the output voltage on the reset pin to low.
 */
void capextend_set_rst_low ( capextend_t *ctx );

/**
 * @brief Get interrupt input function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the input voltage on the interrupt pin.
 */
uint8_t capextend_get_int_input ( capextend_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CAPEXTEND_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

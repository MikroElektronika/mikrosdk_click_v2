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
 * \brief This file contains API for Color 9 Click driver.
 *
 * \addtogroup color9 Color 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR9_H
#define COLOR9_H

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

#define COLOR9_SLAVE_ADDR          0x52
#define COLOR9_MAIN_CTRL           0x00
#define COLOR9_LS_MEAS_RATE        0x04
#define COLOR9_LS_GAIN             0x05
#define COLOR9_PART_ID             0x06
#define COLOR9_MAIN_STATUS         0x07
#define COLOR9_LS_DATA_IR_0        0x0A
#define COLOR9_LS_DATA_IR_1        0x0B
#define COLOR9_LS_DATA_IR_2        0x0C
#define COLOR9_LS_DATA_GREEN_0     0x0D
#define COLOR9_LS_DATA_GREEN_1     0x0E
#define COLOR9_LS_DATA_GREEN_2     0x0F
#define COLOR9_LS_DATA_BLUE_0      0x10
#define COLOR9_LS_DATA_BLUE_1      0x11
#define COLOR9_LS_DATA_BLUE_2      0x12
#define COLOR9_LS_DATA_RED_0       0x13
#define COLOR9_LS_DATA_RED_1       0x14
#define COLOR9_LS_DATA_RED_2       0x15
#define COLOR9_INT_CFG             0x19
#define COLOR9_INT_PERSISTENCE     0x1A
#define COLOR9_LS_THRES_UP_0       0x21
#define COLOR9_LS_THRES_UP_1       0x22
#define COLOR9_LS_THRES_UP_2       0x23
#define COLOR9_LS_THRES_LOW_0      0x24
#define COLOR9_LS_THRES_LOW_1      0x25
#define COLOR9_LS_THRES_LOW_2      0x26
#define COLOR9_LS_THRES_VAR        0x27


/**
 * \defgroup main_crtl Main Control Bits
 * \{
 */
#define COLOR9_MAIN_CTRL_SW_RESET  0x10
#define COLOR9_MAIN_CTRL_CS_MODE   0x04
#define COLOR9_MAIN_CTRL_LS_EN     0x02
/** \} */ // End group main_ctrl 


/**
 * \defgroup ls_meas_rate LS_MEAS_RATE bits
 * \{
 */
#define COLOR9_LS_MEAS_BITWIDTH_20    0x00
#define COLOR9_LS_MEAS_BITWIDTH_19    0x01
#define COLOR9_LS_MEAS_BITWIDTH_18    0x02
#define COLOR9_LS_MEAS_BITWIDTH_17    0x03
#define COLOR9_LS_MEAS_BITWIDTH_16    0x04
#define COLOR9_LS_MEAS_BITWIDTH_13    0x05

#define COLOR9_LS_MEAS_RATE_25ms      0x00
#define COLOR9_LS_MEAS_RATE_50ms      0x01
#define COLOR9_LS_MEAS_RATE_100ms     0x02
#define COLOR9_LS_MEAS_RATE_200ms     0x03
#define COLOR9_LS_MEAS_RATE_500ms     0x04
#define COLOR9_LS_MEAS_RATE_1000ms    0x05
#define COLOR9_LS_MEAS_RATE_2000ms    0x06
/** \} */ // End group ls_meas_rate 

/**
 * \defgroup ls_gain LS_GAIN bits
 * \{
 */
#define COLOR9_LS_GAIN_1              0x00
#define COLOR9_LS_GAIN_3              0x01
#define COLOR9_LS_GAIN_6              0x02
#define COLOR9_LS_GAIN_9              0x03
#define COLOR9_LS_GAIN_18             0x04
/** \} */ // End group ls_gain

/**
 * \defgroup int_cfg INT Configuration
 * \{
 */
#define COLOR9_INT_CFG_IR_CH                   0x00
#define COLOR9_INT_CFG_ALS_GREEN_CH            0x01
#define COLOR9_INT_CFG_RED_CH                  0x02
#define COLOR9_INT_CFG_BLUE_CH                 0x03
#define COLOR9_INT_CFG_LS_THRESHOLD_INT_MODE   0x00
#define COLOR9_INT_CFG_LS_VARIATION_INT_MODE   0x01 
#define COLOR9_INT_CFG_LS_INT_ENABLE           0x01
#define COLOR9_INT_CFG_LS_INT_DISABLE          0x00
/** \} */ // End group int_cfg

/**
 * \defgroup int_persistence INT Persistence
 * \{
 */
#define COLOR9_INT_PERSISTENCE_ANYVAL_TRIGGER          0x00
#define COLOR9_INT_PERSISTENCE_SECOND_COUNT_TRIGGER    0x01
#define COLOR9_INT_PERSISTENCE_SIXTEEN_COUNT_TRIGGER   0x0F
/** \} */ // End group int_persistence

/**
 * \defgroup ls_thres_var LS_THRES_VAR
 * \{
 */
#define COLOR9_LS_THRES_VAR_COUNT_8                    0x00
#define COLOR9_LS_THRES_VAR_COUNT_16                   0x01
#define COLOR9_LS_THRES_VAR_COUNT_32                   0x02
#define COLOR9_LS_THRES_VAR_COUNT_64                   0x03
#define COLOR9_LS_THRES_VAR_COUNT_1024                 0x07
 /** \} */ // End group ls_thres_var

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define COLOR9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR9_RETVAL  uint8_t

#define COLOR9_OK           0x00
#define COLOR9_INIT_ERROR   0xFF
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
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} color9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} color9_cfg_t;

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
void color9_cfg_setup ( color9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param color9 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COLOR9_RETVAL color9_init ( color9_t *ctx, color9_cfg_t *cfg );



/**
 * @brief Generic write function.
 *
 * @param color9        Click object.
 * @param reg_addr      Register address to write to.
 * @param reg_data      Data to write to register address.
 *
 * @description This function writes data to given address.
 */
void color9_write ( color9_t* ctx, uint8_t reg_addr, uint8_t r_data );

/**
 * @brief Generic read function.
 * @param color9        Click object.
 * @param reg_addr      Register address to read from.
 *
 * @returns Result      
 * @description This function reads from given address.
 */
uint8_t color9_read ( color9_t* ctx, uint8_t reg_addr );

/**
 * @brief Software reset function.
 * @param color9        Click object.
 *
 * @description This function resets the software.
 */
void color9_sw_reset ( color9_t* ctx );

/**
 * @brief Get value of IR measurement reading.
 *
 * @param color9        Click object.
 *
 * @returns Result
 *
 * @description This function gets IR reading.
 */
uint32_t color9_get_Ir ( color9_t* ctx );

/**
 * @brief Gets value of Green measurement reading.
 *
 * @param color9        Click object.
 *
 * @returns Result.
 *
 * @description This function gets Green measurement reading.
 */
uint32_t color9_get_green ( color9_t* ctx );

/**
 * @brief Gets value of Blue measurement reading.
 *
 * @param color9        Click object.
 *
 * @returns Result.
 *
 * @description This function gets Blue measurement reading.
 */
uint32_t color9_get_blue ( color9_t* ctx );

/**
 * @brief Gets value of Red measurement reading.
 *
 * @param color9        Click object.
 *
 * @returns Result.
 *
 * @description This function gets Red measurement reading.
 */
uint32_t color9_get_red ( color9_t* ctx );

/**
 * @brief Status register value.
 *
 * @param color9        Click object.
 *
 * @returns Result.
 *
 * @description This function gets status register value.
 */
uint8_t color9_get_status_reg ( color9_t* ctx );

/**
 * @brief Configure measurement rates.
 *
 * @param color9        Click object.
 * @param resolution    Resolution.
 * @param meas_rate     Measurement rate.
 *
 * @description This function configures measurement rate.
 */
void color9_meas_rate ( color9_t* ctx, uint8_t resolution, uint8_t meas_rate );

/**
 * @brief Function for setting the main configuration register.
 *
 * @param color9        Click object.
 * @param cfg           Configuration register.
 *
 * @description This function configures the main configuration register.
 */
void color9_reg_ctrl ( color9_t* ctx, uint8_t cfg );

/**
 * @brief Function for gain setting.
 *
 * @param color9        Click object.
 * @param g_settings    Gain settings.
 *
 * @description This function configures the gain settings.
 */
void color9_set_gain ( color9_t* ctx, uint8_t g_setting );

/**
 * @brief Interrupt configuration 
 *
 * @param color9        Click object.
 * @param int_select    Selects interrupt.
 * @param int_mode      Selects mode.
 * @param cfg_setting   Configuration settings.
 *
 * @description This function configures interrupt.
 */
void color9_int_config ( color9_t* ctx, uint8_t int_select, uint8_t int_mode,
                         uint8_t cfg_setting );

/**
 * @brief Configre number of compares between samples.
 *
 * @param color9             Click object.
 * @param num_of_compares    Number of compares.
 *
 * @description This function configures interrupt.
 */
void color9_sample_compare ( color9_t* ctx, uint8_t num_of_compares );

/**
 * @brief Generic read function for 32 bits.
 *
 * @param color9             Click object.
 * @param reg_addr           Address form which we read 32 bits.
 *
 * @description This reads 32 bits from given address.
 */
uint32_t color9_read_32 ( color9_t* ctx, uint8_t reg_addr );

/**
 * @brief Generic write function for 32 bits.
 *
 * @param color9             Click object.
 * @param reg_addr           Address to write to 32 bits.
 * @param treas_val          Value to be written.
 *
 * @description This function writes 32 bits to given address.
 */
void color9_write_32 ( color9_t* ctx, uint8_t reg_addr, uint32_t treas_val );

/**
 * @brief Similarity count.
 *
 * @param color9             Click object.
 * @param sim_set            Set similarity.
 *
 * @description This function sets the similarity.
 */
void color9_similarity_count ( color9_t* ctx, uint8_t sim_set );

/**
 * @brief Upper Tresset.
 *
 * @param color9             Click object.
 * @param set_val            Upper tresset value.
 *
 * @description Sets upper tresset value.
 */
void color9_upper_tresset ( color9_t* ctx, uint32_t set_val );

/**
 * @brief Lower Tresset.
 *
 * @param color9             Click object.
 * @param set_val            Lower tresset value.
 *
 * @description Sets lower tresset value.
 */
void color9_lower_tresset ( color9_t* ctx, uint32_t set_val );

#ifdef __cplusplus
}
#endif
#endif  // _COLOR9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

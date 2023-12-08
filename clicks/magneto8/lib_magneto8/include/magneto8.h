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
 * \brief This file contains API for Magneto 8 Click driver.
 *
 * \addtogroup magneto8 Magneto 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MAGNETO8_H
#define MAGNETO8_H

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
#define MAGNETO8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MAGNETO8_OK             0
#define MAGNETO8_ERROR         -1
/** \} */
 
/**
 * \defgroup config_reg  Config reg
 * \{
 */
#define MAGNETO8_REG_ZMCO       0x00
#define MAGNETO8_REG_ZPOS_MSB   0x01
#define MAGNETO8_REG_ZPOS_LSB   0x02 
#define MAGNETO8_REG_CONF_C1    0x07
#define MAGNETO8_REG_CONF_C2    0x08
#define MAGNETO8_REG_ABN        0x09
#define MAGNETO8_REG_PUSHTHR    0x0A
/** \} */
 
/**
 * \defgroup output_reg  Output reg
 * \{
 */
#define MAGNETO8_REG_RAW_ANGLE_MSB  0x0C
#define MAGNETO8_REG_RAW_ANGLE_LSB  0x0D
#define MAGNETO8_REG_ANGLE_MSB      0x0E
#define MAGNETO8_REG_ANGLE_LSB      0x0F
/** \} */
 
/**
 * \defgroup status_reg  Status reg
 * \{
 */
#define MAGNETO8_REG_STATUS         0x0B
#define MAGNETO8_REG_AGC            0x1A
#define MAGNETO8_REG_MAGNITUDE_MSB  0x1B
#define MAGNETO8_REG_MAGNITUDE_LSB  0x1C
/** \} */
 
/**
 * \defgroup burn_command  Burn Command
 * \{
 */
#define MAGNETO8_REG_BURN           0xFF
#define MAGNETO8_BURN_ANGLE         0x80
#define MAGNETO8_BURN_SETTING       0x40
/** \} */
 
/**
 * \defgroup conf_mapping  Conf mapping
 * \{
 */
#define MAGNETO8_CFG_MODE_NOM     0x0000
#define MAGNETO8_CFG_MODE_LPM1    0x0001
#define MAGNETO8_CFG_MODE_LPM2    0x0002
#define MAGNETO8_CFG_MODE_LPM3    0x0003

#define MAGNETO8_CFG_HYST_OFF     0x0000
#define MAGNETO8_CFG_HYST_1_LSB   0x0004
#define MAGNETO8_CFG_HYST_2_LSB   0x0008
#define MAGNETO8_CFG_HYST_3_LSB   0x000C

#define MAGNETO8_CFG_SF_16x       0x0000
#define MAGNETO8_CFG_SF_8x        0x0100
#define MAGNETO8_CFG_SF_4x        0x0200
#define MAGNETO8_CFG_SF_2x        0x0300

#define MAGNETO8_CFG_FTH_SLOW     0x0000
#define MAGNETO8_CFG_FTH_6_LSB    0x0400
#define MAGNETO8_CFG_FTH_7_LSB    0x0800
#define MAGNETO8_CFG_FTH_9_LSB    0x0C00
#define MAGNETO8_CFG_FTH_18_LSB   0x1000
#define MAGNETO8_CFG_FTH_21_LSB   0x1400
#define MAGNETO8_CFG_FTH_24_LSB   0x1800
#define MAGNETO8_CFG_FTH_10_LSB   0x1C00

#define MAGNETO8_CFG_WD_OFF       0x2000
#define MAGNETO8_CFG_WD_ON        0x2000
/** \} */
 
/**
 * \defgroup abn_mapping  Abn mapping
 * \{
 */
#define MAGNETO8_ABN_8              0x00
#define MAGNETO8_ABN_16             0x01
#define MAGNETO8_ABN_32             0x02
#define MAGNETO8_ABN_64             0x03
#define MAGNETO8_ABN_128            0x04
#define MAGNETO8_ABN_256            0x05
#define MAGNETO8_ABN_512            0x06
#define MAGNETO8_ABN_1024           0x07
#define MAGNETO8_ABN_2048           0x08
/** \} */
 
/**
 * \defgroup status_reg  Status reg
 * \{
 */
#define MAGNETO8_STATUS_MD    0x20
#define MAGNETO8_STATUS_ML    0x10
#define MAGNETO8_STATUS_MH    0x08

#define MAGNETO8_SLAVE_ADDR  0x36
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
    // Input pins 

    digital_in_t rst;
    digital_in_t cs;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} magneto8_t;

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
    pin_name_t cs;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} magneto8_cfg_t;

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
void magneto8_cfg_setup ( magneto8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t magneto8_init ( magneto8_t *ctx, magneto8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note: Config contains -
 * <pre>
 *   - CONFIGURATION REG:
 *       - MAGNETO8_CFG_MODE_NOM
 *       - MAGNETO8_CFG_HYST_OFF
 *       - MAGNETO8_CFG_SF_2x
 *       - MAGNETO8_CFG_FTH_SLOW
 *       - MAGNETO8_CFG_WD_ON
 *   - ABN REG:
 *       - MAGNETO8_ABN_64
 * </pre>
 * 
 * @details This function executes default configuration for Magneto8 click.
 */
void magneto8_default_cfg ( magneto8_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param tx_data     Data buf to be written.
 *
 * @details This function writes data to the desired register.
 */
void magneto8_generic_write ( magneto8_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @details This function reads data from the desired register.
 */
uint8_t magneto8_generic_read ( magneto8_t *ctx, uint8_t reg );

/**
 * @brief Gets Angle raw data
 *
 * @param ctx  Click object.
 * 
 * @return  (uint16_t) Angle raw data
 */
uint16_t magneto8_get_raw_angle ( magneto8_t *ctx );

/**
 * @brief Gets Angle data
 *
 * @param ctx  Click object.
 * 
 * @return (float) Angle data
 */
float magneto8_get_angle_data ( magneto8_t *ctx );

/**
 * @brief Gets status data
 *
 * @param ctx  Click object.
 * 
 * @return (uint8_t) Status data
 */
uint8_t magneto8_get_status ( magneto8_t *ctx );

/**
 * @brief Gets magnitude data
 *
 * @param ctx  Click object.
 * 
 * @return  (uint16_t) Magnitude data
 */
uint16_t magneto8_get_magnitude ( magneto8_t *ctx );

/**
 * @brief Gets AGC data
 *
 * @param ctx  Click object.
 * 
 * @return  (uint8_t) AGC data
 */
uint8_t magneto8_get_agc ( magneto8_t *ctx );

/**
 * @brief Gets ZMCO data
 *
 * @param ctx  Click object.
 * 
 * @return  (uint8_t) ZMCO data
 */
uint8_t magneto8_get_zmco ( magneto8_t *ctx );

/**
 * @brief Gets A pin state
 *
 * @param ctx  Click object.
 * 
 * @return  RST ( A ) pin state
 */
uint8_t magneto8_a_pin_state ( magneto8_t *ctx );

/**
 * @brief Gets B pin state
 *
 * @param ctx  Click object.
 * 
 * @return  CS ( B ) pin state
 */
uint8_t magneto8_b_pin_state ( magneto8_t *ctx );

/**
 * @brief Gets PSH pin state
 *
 * @param ctx  Click object.
 * 
 * @return  INT ( PSH ) pin state
 */
uint8_t magneto8_psh_pin_state ( magneto8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MAGNETO8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

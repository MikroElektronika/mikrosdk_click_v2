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
 * \brief This file contains API for Angle 5 Click driver.
 *
 * \addtogroup angle5 Angle 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANGLE5_H
#define ANGLE5_H

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

#define ANGLE5_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mgh   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.mgl   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANGLE5_RETVAL  uint8_t

#define ANGLE5_OK                           0x00
#define ANGLE5_INIT_ERROR                   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define ANGLE5_REG_ZERO_SETTING_LSB         0x00
#define ANGLE5_REG_ZERO_SETTING_MSB         0x01
#define ANGLE5_REG_BIAS_CURRENT_TRIMMING    0x02
#define ANGLE5_REG_ENABLE_TRIMMING_XY       0x03
#define ANGLE5_REG_CONFIG_1                 0x04
#define ANGLE5_REG_CONFIG_2                 0x05
#define ANGLE5_REG_MAGNETIC_FIELD_THR       0x06
#define ANGLE5_REG_NUMBER_OF_POLE_PAIRS     0x07
#define ANGLE5_REG_ROTATION_DIRECTION       0x09
#define ANGLE5_REG_MG_H_L                   0x1B
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define ANGLE5_CMD_READ_ANGLE               0x00
#define ANGLE5_CMD_READ                     0x40
#define ANGLE5_CMD_WRITE                    0x80
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

    // Input pins 

    digital_in_t mgh;
    digital_in_t mgl;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} angle5_t;

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

    pin_name_t mgh;
    pin_name_t mgl;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} angle5_cfg_t;

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
void angle5_cfg_setup ( angle5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANGLE5_RETVAL angle5_init ( angle5_t *ctx, angle5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Angle 5 click.
 */
void angle5_default_cfg ( angle5_t *ctx );

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
void angle5_generic_transfer 
( 
    angle5_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Reads Raw Angle data
 *
 * @param ctx          Click object.
 * 
 * @return ( 12 bit ) angle data
 *
 * @description Use this function for reads raw angle data
 */
uint16_t angle5_read_raw_angle ( angle5_t *ctx );

/**
 * @brief Reads Angle data in deg
 *
 * @param ctx          Click object.
 * 
 * @return Angle data ( 0 - 360 deg )
 *
 * @description Use this function for reads angle data
 */
float angle5_read_angle_deg ( angle5_t *ctx );

/**
 * @brief Generic read function
 *
 * @param ctx           Click object. 
 * @param reg_addr      Register address
 * @param rsp           Data reads from register
 * 
 * @return Angle raw data
 *
 * @description Use this function for reads data via SPI
 */
uint16_t angle5_read_register ( angle5_t *ctx, uint8_t reg_addr, uint8_t *rsp );

/**
 * @brief Generic write function
 *
 * @param ctx           Click object. 
 * @param reg_addr      Register address
 * @param tx_data       Data thet will be send
 * @param status        Reading status
 *
 * @return Angle raw data
 *
 * @description Use this function for send data via SPI
 */
uint16_t angle5_write_register ( angle5_t *ctx, uint8_t reg_addr, uint8_t tx_data, uint8_t *status );

/**
 * @brief Calculating angle data to RPM
 *
 * @param old_angle Old Angle data ( previous measurement )
 * @param new_angle New Angle data ( current measurement )
 *
 * @return RPM ( Revolutions per minute )
 *
 * @description Function for calculating angle data to RPM
 */
float angle5_calc_rpm ( float old_angle, float new_angle );

/**
 * @brief Gets MGH (PWM) pin state
 *
 * @param ctx           Click object. 
 * 
 * @return MGH pin state
 *
 * @description Function for getting MGH (PWM) pin state
 */
uint8_t angle5_get_mgh_pin_state( angle5_t *ctx );

/**
 * @brief Gets MGL (INT) pin state
 *
 * @param ctx           Click object. 
 * 
 * @return MGL pin state
 *
 * @description Function for getting MGL (INT) pin state
 */
uint8_t angle5_get_mgl_pin_state( angle5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ANGLE5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

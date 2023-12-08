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
 * \brief This file contains API for Boost-INV Click driver.
 *
 * \addtogroup boostinv Boost-INV Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BOOSTINV_H
#define BOOSTINV_H

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
#define BOOSTINV_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BOOSTINV_RETVAL  uint8_t

#define BOOSTINV_OK           0x00
#define BOOSTINV_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addresses Slave addresses
 * \{
 */
#define BOOSTINV_I2C_SLAVE_ADDRESS_GND           0x30   
#define BOOSTINV_I2C_SLAVE_ADDRESS_VCC           0x31 
/** \} */

/**
 * \defgroup reg_addresses Register addresses
 * \{
 */
#define BOOSTINV_REG_POSITIVE_VOUT               0x00 
#define BOOSTINV_REG_NEGATIVE_VOUT               0x01 
#define BOOSTINV_REG_CONFIG                      0x02 
#define BOOSTINV_REG_COMMAND                     0x04 
#define BOOSTINV_REG_OTP0                        0x00 
#define BOOSTINV_REG_OTP1                        0x01 
#define BOOSTINV_REG_OTP2                        0x02 
/** \} */

/**
 * \defgroup cfg_addresses Configuration addresses
 * \{
 */
#define BOOSTINV_CFG_LOCKOUT_BIT_ENABLE          0x40
#define BOOSTINV_CFG_LOCKOUT_BIT_DISABLE         0x00
#define BOOSTINV_CFG_VPLUS_ENABLE                0x20
#define BOOSTINV_CFG_VPLUS_DISABLE               0x00
#define BOOSTINV_CFG_IRAMP_1uA                   0x00
#define BOOSTINV_CFG_IRAMP_2uA                   0x08
#define BOOSTINV_CFG_IRAMP_4uA                   0x10
#define BOOSTINV_CFG_IRAMP_8uA                   0x18
#define BOOSTINV_CFG_PDDIS_ENABLE                0x04
#define BOOSTINV_CFG_PDDIS_DISABLE               0x00
#define BOOSTINV_CFG_PUSEQ_OUTPUTS_DISABLED      0x00
#define BOOSTINV_CFG_PUSEQ_VOUTN_RAMP_1ST        0x01
#define BOOSTINV_CFG_PUSEQ_VOUTP_RAMP_1ST        0x02
#define BOOSTINV_CFG_PUSEQ_BOTH_RAMP_TOGETHER    0x03
/** \} */

/**
 * \defgroup cmd_reg Command registers
 * \{
 */
#define BOOSTINV_CMD_WRITE_OTP_MEMORY            0x80
#define BOOSTINV_CMD_CLEAR_OTP_FAULT             0x40
#define BOOSTINV_CMD_RESET                       0x20
#define BOOSTINV_CMD_SWITCHES_OFF                0x10
#define BOOSTINV_CMD_REGISTER_SELECT_POS_VOUT    0x04
#define BOOSTINV_CMD_REGISTER_SELECT_NEG_VOUT    0x02
#define BOOSTINV_CMD_REGISTER_SELECT_CONFIG      0x01
#define BOOSTINV_CMD_REGISTER_SELECT_OTP2        0x00
#define BOOSTINV_CMD_REGISTER_SELECT_OTP1        0x00
#define BOOSTINV_CMD_REGISTER_SELECT_OTP0        0x00
/** \} */

/**
 * \defgroup pos_neg_out_v Positive and negative output voltage
 * \{
 */
#define BOOSTINV_VOLTAGE_POSITIVE_3200_mV        3200
#define BOOSTINV_VOLTAGE_POSITIVE_7750_mV        7750
#define BOOSTINV_VOLTAGE_POSITIVE_12000_mV       12000
#define BOOSTINV_VOLTAGE_NEGATIVE_1450_mV       -1450
#define BOOSTINV_VOLTAGE_NEGATIVE_6700_mV       -6700
#define BOOSTINV_VOLTAGE_NEGATIVE_11050_mV      -11050
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

     digital_out_t en;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} boostinv_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} boostinv_cfg_t;

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
void boostinv_cfg_setup ( boostinv_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param boostinv Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BOOSTINV_RETVAL boostinv_init ( boostinv_t *ctx, boostinv_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for BoostInv click.
 * 
 * @note
 *    Click default configuration:
 * -------------------------------------------------
 * <pre>
 *    1) Enable Boost Inv
 * </pre>
 * 
 * <pre>
 *    2) Configuration:
 * </pre>
 * 
 * <pre>
 *    BOOSTINV_REG_CONFIG
 * -------------------------------------------------
 *    BOOSTINV_CFG_PUSEQ_VOUTP_RAMP_1ST
 * </pre>
 * 
 * <pre>
 *    BOOSTINV_REG_COMMAND
 * -------------------------------------------------
 *    BOOSTINV_CMD_REGISTER_SELECT_POS_VOUT
 *    BOOSTINV_CMD_REGISTER_SELECT_NEG_VOUT
 *    BOOSTINV_CMD_REGISTER_SELECT_CONFIG
 * </pre>
 */
void boostinv_default_cfg ( boostinv_t *ctx );

/**
 * @brief Functions for write one byte in register.
 *
 * @param ctx          Click object.
 * @param reg_addr     Register in which the data will be written.
 * @param tx_data      Data which be written in the register.
 * 
 * @description This function write the byte of data to the desired register.
 */
void boostinv_generic_write ( boostinv_t *ctx, uint8_t reg_addr, uint8_t tx_data );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * 
 * @return             uint8_t read data.
 *
 * @description This function reads the byte of data from the desired register.
 */
uint8_t boostinv_generic_read ( boostinv_t *ctx, uint8_t reg_addr );

/**
 * @brief Functions for enable chip.
 *
 * @param ctx          Click object.
 *
 * @description This function enable chip device for Boost INV click.
 */
void boostinv_enable ( boostinv_t *ctx );

/**
 * @brief Functions for set positive output voltage
 *
 * @param ctx          Click object.
 * @param voltage      Voltage that will be set
 *
 * @description Positive output voltage goes from 3200mV to 12750mV 
 * with a step of 50mV.
 */
void boostinv_set_positive_voltage ( boostinv_t *ctx, uint16_t voltage );

/**
 * @brief Functions for set negative output voltage
 *
 * @param ctx          Click object.
 * @param voltage      Voltage that will be set
 *
 * @description Negative output voltage goes from -1200mV to -13950mV 
 * with a step of 50mV.
 */
void boostinv_set_negative_voltage ( boostinv_t *ctx, int16_t voltage );

#ifdef __cplusplus
}
#endif
#endif  // _BOOSTINV_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

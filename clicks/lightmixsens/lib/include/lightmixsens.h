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
 * \brief This file contains API for Light mix sens Click driver.
 *
 * \addtogroup lightmixsens Light mix sens Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LIGHTMIXSENS_H
#define LIGHTMIXSENS_H

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
#define LIGHTMIXSENS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LIGHTMIXSENS_RETVAL  uint8_t

#define LIGHTMIXSENS_OK                          0x00
#define LIGHTMIXSENS_INIT_ERROR                  0xFF
/** \} */


#define LIGHTMIXSENS_ATIME_WTIME_CONST           2.8
#define LIGHTMIXSENS_PTIME_CONST                 88
#define LIGHTMIXSENS_WTIME_INCR_FACTOR           12

/**
 * \defgroup register_address Register address
 * \{
 */
#define LIGHTMIXSENS_REG_ENABLE                  0x80
#define LIGHTMIXSENS_REG_ATIME                   0x81
#define LIGHTMIXSENS_REG_PTIME                   0x82
#define LIGHTMIXSENS_REG_WTIME                   0x83
#define LIGHTMIXSENS_REG_AILT                    0x84
#define LIGHTMIXSENS_REG_AIHT                    0x86
#define LIGHTMIXSENS_REG_PILT                    0x88
#define LIGHTMIXSENS_REG_PIHT                    0x8A
#define LIGHTMIXSENS_REG_PERS                    0x8C
#define LIGHTMIXSENS_REG_CFG0                    0x8D
#define LIGHTMIXSENS_REG_PCFG0                   0x8E
#define LIGHTMIXSENS_REG_PCFG1                   0x8F
#define LIGHTMIXSENS_REG_CFG1                    0x90
#define LIGHTMIXSENS_REG_REVID                   0x91
#define LIGHTMIXSENS_REG_ID                      0x92
#define LIGHTMIXSENS_REG_STATUS                  0x93
#define LIGHTMIXSENS_REG_CDATA                   0x94
#define LIGHTMIXSENS_REG_RDATA                   0x96
#define LIGHTMIXSENS_REG_GDATA_IRDATA            0x98
#define LIGHTMIXSENS_REG_BDATA                   0x9A
#define LIGHTMIXSENS_REG_PDATA                   0x9C
#define LIGHTMIXSENS_REG_REVID2                  0x9E
#define LIGHTMIXSENS_REG_CFG2                    0x9F
#define LIGHTMIXSENS_REG_CFG3                    0xAB
#define LIGHTMIXSENS_REG_POFFSET                 0xC0
#define LIGHTMIXSENS_REG_AZCFG                   0xD6
#define LIGHTMIXSENS_REG_CALIB                   0xD7
#define LIGHTMIXSENS_REG_CALIBCFG                0xD9
#define LIGHTMIXSENS_REG_CALIBSTAT               0xDC
#define LIGHTMIXSENS_REG_INTENAB                 0xDD
/** \} */

/**
 * \defgroup settings_for_the_enable_reg Settings for the ENABLE register
 * \{
 */
#define LIGHTMIXSENS_ENABLE_WAIT                 0x8
#define LIGHTMIXSENS_ENABLE_PROX                 0x4
#define LIGHTMIXSENS_ENABLE_ALS                  0x2
#define LIGHTMIXSENS_ENABLE_OSC                  0x1
#define LIGHTMIXSENS_DISABLE_ALL                 0x0
/** \} */

/**
 * \defgroup settings_for_the_pcfg0_reg Settings for the PCFG0 register
 * \{
 */
#define LIGHTMIXSENS_PCFG0_PULSE_LEN_4us         0x0
#define LIGHTMIXSENS_PCFG0_PULSE_LEN_8us         0x40
#define LIGHTMIXSENS_PCFG0_PULSE_LEN_16us        0x80
#define LIGHTMIXSENS_PCFG0_PULSE_LEN_32us        0xC0
#define LIGHTMIXSENS_PCFG0_PULSE_NUM_1           0x0
#define LIGHTMIXSENS_PCFG0_PULSE_NUM_2           0x1
#define LIGHTMIXSENS_PCFG0_PULSE_NUM_3           0x2
#define LIGHTMIXSENS_PCFG0_PULSE_NUM_64          0x3F
/** \} */

/**
 * \defgroup settings_for_the_pcfg1_reg Settings for the PCFG1 register
 * \{
 */
#define LIGHTMIXSENS_PCFG1_GAIN_1x               0x0
#define LIGHTMIXSENS_PCFG1_GAIN_2x               0x40
#define LIGHTMIXSENS_PCFG1_GAIN_4x               0x80
#define LIGHTMIXSENS_PCFG1_GAIN_8x               0xC0
#define LIGHTMIXSENS_PCFG1_DRIVE_6mA             0x0
#define LIGHTMIXSENS_PCFG1_DRIVE_12mA            0x1
#define LIGHTMIXSENS_PCFG1_DRIVE_18mA            0x2
#define LIGHTMIXSENS_PCFG1_DRIVE_192mA           0x1F
/** \} */

/**
 * \defgroup settings_for_the_cfg0_reg Settings for the CFG0 register
 * \{
 */
#define LIGHTMIXSENS_CFG0_WLONG                  0x4
/** \} */

/**
 * \defgroup settings_for_the_cfg1_reg Settings for the CFG1 register
 * \{
 */
#define LIGHTMIXSENS_CFG1_IR_TO_GREEN            0x8
#define LIGHTMIXSENS_CFG1_AGAIN_1x               0x0
#define LIGHTMIXSENS_CFG1_AGAIN_4x               0x1
#define LIGHTMIXSENS_CFG1_AGAIN_16x              0x2
#define LIGHTMIXSENS_CFG1_AGAIN_64x              0x3
/** \} */

/**
 * \defgroup settings_for_the_cfg2_reg Settings for the CFG2 register
 * \{
 */
#define LIGHTMIXSENS_CFG2_AGAINMAX               0x10
#define LIGHTMIXSENS_CFG2_AGAINL                 0x4
/** \} */

/**
 * \defgroup settings_for_the_cfg3_reg Settings for the CFG3 register
 * \{
 */
#define LIGHTMIXSENS_CFG3_INT_READ_CLEAR         0x80
#define LIGHTMIXSENS_CFG3_SAI                    0x10
/** \} */

/**
 * \defgroup interrupt_bit_flags Interrupt bit flags for the STATUS and INTENAB registers
 * \{
 */
#define LIGHTMIXSENS_FLAG_ASAT                   0x80
#define LIGHTMIXSENS_FLAG_PSAT                   0x40
#define LIGHTMIXSENS_FLAG_PINT                   0x20
#define LIGHTMIXSENS_FLAG_AINT                   0x10
#define LIGHTMIXSENS_FLAG_CINT                   0x8
#define LIGHTMIXSENS_FLAG_PSAT_REFL              0x2
#define LIGHTMIXSENS_FLAG_PSAT_AMB               0x1
/** \} */

/**
 * \defgroup settings_for_the_calib_reg Settings for the CALIB register
 * \{
 */
#define LIGHTMIXSENS_CALIB_ELECTRICAL            0x20
#define LIGHTMIXSENS_CALIB_OFFSET_START          0x1
/** \} */

/**
 * \defgroup settings_for_the_calibcfg_reg Settings for the CALIBCFG register
 * \{
 */
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_0      0x0
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_1      0x20
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_3      0x40
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_7      0x60
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_15     0x80
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_31     0xA0
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_63     0xC0
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_127    0xE0
#define LIGHTMIXSENS_CALIBCFG_AUTO_OFFSET_ADJ    0x8
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_DIS       0x0
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_2         0x1
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_4         0x2
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_8         0x3
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_16        0x4
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_32        0x5
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_64        0x6
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_128       0x7
/** \} */

/**
 * \defgroup settings_for_the_calibstat_reg Settings for the CALIBSTAT register
 * \{
 */
#define LIGHTMIXSENS_CALIBSTAT_FINISHED          0x1
/** \} */

/**
 * \defgroup driver_error_code Driver error code
 * \{
 */
#define LIGHTMIXSENS_ERR_STAT_OK                 0x0
#define LIGHTMIXSENS_ERR_STAT_INVAL_ADDR         0xFF
/** \} */

/**
 * \defgroup driver_dummy_data Driver dummy data
 * \{
 */
#define LIGHTMIXSENS_DUMMY_DATA                  0x0
/** \} */

/**
 * \defgroup device_slave_address Device slave address
 * \{
 */
#define LIGHTMIXSENS_DEVICE_ADDR                 0x39
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} lightmixsens_t;

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

} lightmixsens_cfg_t;

/**
 * @macro lightmixsens_err_t
 * @brief Driver Error type
 */
#define lightmixsens_err_t   uint8_t

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
void lightmixsens_cfg_setup ( lightmixsens_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LIGHTMIXSENS_RETVAL lightmixsens_init ( lightmixsens_t *ctx, lightmixsens_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for LightMixSens click.
 */
void lightmixsens_default_cfg ( lightmixsens_t *ctx );

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
void lightmixsens_generic_write ( lightmixsens_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void lightmixsens_generic_read ( lightmixsens_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Write Byte function.
 *
 * @param ctx           Click object. 
 * @param reg_addr      Address where data be written.
 * @param data_in       Data to be written.
 *
 * @returns 0x0  - Ok;    0xFF - Invalid register address.
 *
 * @description This function writes data byte to the selected register.
 */
lightmixsens_err_t lightmixsens_write_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Generic Write Word function.
 *
 * @param ctx           Click object.  
 * @param reg_addr      Start address where data be written.
 * @param data_in       Data to be written.
 *
 * @returns 0x0  - Ok;    0xFF - Invalid register address.
 *
 * @description This function writes 16-bit data starting from the selected 
 *              register to the next one.
 */
lightmixsens_err_t lightmixsens_write_word ( lightmixsens_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Generic Read Byte function.
 *
 * @param ctx           Click object.  
 * @param reg_addr      Address which from data be read.
 * @param data_out      Buffer where data be placed.
 *
 * @returns 0x0  - Ok;    0xFF - Invalid register address.
 *
 * @description This function reads data byte from the selected register.
 */
lightmixsens_err_t lightmixsens_read_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief Generic Read Word function.
 *
 * @param ctx           Click object.  
 * @param reg_addr      Start address which from data be read.
 * @param data_out      Buffer where data be placed.
 *
 * @returns 0x0  - Ok;    0xFF - Invalid register address.
 *
 * @description This function reads 16-bit data starting from the selected 
 *              register to the next one.
 */
lightmixsens_err_t lightmixsens_read_word ( lightmixsens_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Get Status function.
 *
 * @param ctx           Click object.  
 * @param flag_mask     Bit flag selection to include/mask the desired bits.
 * @param status        Buffer where masked status byte be placed.
 *
 * @description This function allows the desired bit flags to be checked from 
 *              the STATUS register.
 */
void lightmixsens_get_status ( lightmixsens_t *ctx, uint8_t flag_mask, uint8_t *status );

/**
 * @brief Switch IR To Green Channel function.
 *
 * @param ctx           Click object. 
 * 
 * @description This function switches the IR light to be measured in the Green
 *              channel (GDATA) register.
 */
void lightmixsens_switch_ir_to_green ( lightmixsens_t *ctx );

/**
 * @brief Switch IR To Proximity function.
 *
 * @param ctx           Click object. 
 * 
 * @description This function switches the IR light to measure proximity in the
 *              PDATA register.
 */
void lightmixsens_switch_ir_to_prox ( lightmixsens_t *ctx );

/**
 * @brief Wait ALS/Color Intregration Time Done function.
 *
 * @param ctx           Click object. 
 * 
 * @description This function performs a delay time determined by the ALS/Color
 *              integration time (ATIME) register.
 */
void lightmixsens_wait_atime ( lightmixsens_t *ctx );

/**
 * @brief Wait Proximity Sample Time Done function.
 *
 * @param ctx           Click object. 

 * @description This function performs a delay time determined by the Proximity
 *              sample time (PTIME) register.
 */
void lightmixsens_wait_ptime ( lightmixsens_t *ctx );

/**
 * @brief Wait WTIME + WLONG Done function.
 *
 * @param ctx           Click object. 
 * 
 * @description This function performs a delay time determined by the WTIME and
 *              WLONG registers.
 */
void lightmixsens_wait_wtime ( lightmixsens_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LIGHTMIXSENS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

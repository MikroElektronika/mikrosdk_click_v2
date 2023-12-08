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
 * \brief This file contains API for Gyro 2 Click driver.
 *
 * \addtogroup gyro2 Gyro 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GYRO2_H
#define GYRO2_H

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
 * \defgroup slave_addr Slave Address
 * \{
 */
#define GYRO2_ADDR0    0x20
#define GYRO2_ADDR1    0x21

/**
 * \defgroup regs Registers
 * \{
 */
#define GYRO2_STATUS           0x00
#define GYRO2_OUT_X_MSB        0x01
#define GYRO2_OUT_X_LSB        0x02
#define GYRO2_OUT_Y_MSB        0x03
#define GYRO2_OUT_Y_LSB        0x04
#define GYRO2_OUT_Z_MSB        0x05
#define GYRO2_OUT_Z_LSB        0x06
#define GYRO2_DR_STATUS        0x07
#define GYRO2_F_STATUS         0x08
#define GYRO2_F_SETUP          0x09
#define GYRO2_F_EVENT          0x0A
#define GYRO2_INT_SRC_FLAG     0x0B
#define GYRO2_WHO_AM_I         0x0C
#define GYRO2_CTRL_REG0        0x0D
#define GYRO2_CTRL_REG1        0x13

/**
 * \defgroup bits_start Bits start
 * \{
 */
#define  GYRO2_SCALE_0    0
#define  GYRO2_SCALE_1    1
#define  GYRO2_SCALE_2    2
#define  GYRO2_SCALE_3    3

#define  GYRO2_HI_PASS_OFF     0x00
#define  GYRO2_HI_PASS_MOD0    0x04
#define  GYRO2_HI_PASS_MOD1    0x0C
#define  GYRO2_HI_PASS_MOD2    0x14
#define  GYRO2_HI_PASS_MOD3    0x1C

#define  GYRO2_LO_PASS_OFF     0x00
#define  GYRO2_LO_PASS_MOD0    0x20
#define  GYRO2_LO_PASS_MOD1    0x60
#define  GYRO2_LO_PASS_MOD2    0xE0

/**
 * \defgroup bits_end Bits end
 * \{
 */
#define GYRO2_RT_CFG     0x0E

/**
 * \defgroup bits_start Bits start
 * \{
 */
#define GYRO2_RT_CFG_ELE      0x08
#define GYRO2_RT_CFG_ZTEFE    0x04
#define GYRO2_RT_CFG_YTEFE    0x02
#define GYRO2_RT_CFG_XTEFE    0x01

/**
 * \defgroup bits_end Bits end
 * \{
 */
#define GYRO2_RT_SRC          0x0F
#define GYRO2_RT_THS          0x10
#define GYRO2_RT_COUNT        0x11
#define GYRO2_TEMP            0x12

/**
 * \defgroup bits Bits
 * \{
 */
#define  GYRO2_DR_800Hz          0
#define  GYRO2_DR_400Hz          1
#define  GYRO2_DR_200Hz          2
#define  GYRO2_DR_100Hz          3
#define  GYRO2_DR_50Hz           4
#define  GYRO2_DR_25Hz           5
#define  GYRO2_DR_12_5Hz         6
#define  GYRO2_STANDBY           0
#define  GYRO2_READY             1
#define  GYRO2_ACTIVE            3

/**
 * \defgroup reg Reg
 * \{
 */
#define GYRO2_CTRL_REG2       0x14

/**
 * \defgroup bits Bits
 * \{
 */
#define GYRO2_INT_CFG_FIFO_INT1    0x80
#define GYRO2_INT_CFG_FIFO_INT2    0x00
#define GYRO2_INT_EN_FIFO          0x40
#define GYRO2_INT_DIS_FIFO         0x00
#define GYRO2_INT_CFG_RT_INT1      0x20
#define GYRO2_INT_CFG_RT_INT2      0x00
#define GYRO2_INT_EN_RT            0x10
#define GYRO2_DIS_EN_RT            0x00
#define GYRO2_INT_CFG_DRDY_INT1    0x08
#define GYRO2_INT_CFG_DRDY_INT2    0x00
#define GYRO2_INT_EN_DRDY          0x04
#define GYRO2_INT_DIS_DRDY         0x00
#define GYRO2_IPOL_ACTIVE_HI       0x02
#define GYRO2_IPOL_ACTIVE_LO       0x00
#define GYRO2_PP_OD_OS             0x01
#define GYRO2_PP_OD_PUSH_PULL      0x00

/**
 * \defgroup end_bits End bits
 * \{
 */
#define GYRO2_CTRL_REG3            0x15

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define GYRO2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.scs     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.rdy     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GYRO2_RETVAL  uint8_t

#define GYRO2_OK           0x00
#define GYRO2_INIT_ERROR   0xFF
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Master Input/Output type.
 */
typedef void ( *gyro2_master_io_t )( struct gyro2_s*, uint8_t, uint8_t*, uint8_t );

typedef struct 
{
   uint8_t tmp_ctrl_reg0;
   uint8_t tmp_ctrl_reg1;
   uint8_t tmp_ctrl_reg2;
   uint8_t tmp_ctrl_reg3;

} ctrl_reg_t;


/**
 * @brief Click ctx object definition.
 */
typedef struct gyro2_s
{
    // Output pins 

    digital_out_t scs;
    digital_out_t rst;
    digital_out_t rdy_pin;
    digital_out_t cs;

    // Input pins 

    digital_in_t rdy;
    digital_in_t int_pin;

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    //ctrl register variables

    ctrl_reg_t tmp_ctrl_reg;

} gyro2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t cs;
    
    // Additional gpio pins 

    pin_name_t scs;
    pin_name_t rst;
    pin_name_t rdy;
    pin_name_t int_pin;
    pin_name_t rdy_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} gyro2_cfg_t;

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
void gyro2_cfg_setup ( gyro2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gyro2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GYRO2_RETVAL gyro2_init ( gyro2_t *ctx, gyro2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Gyro 2 click.
 */
uint8_t gyro2_default_cfg ( gyro2_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void gyro2_generic_write ( gyro2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void gyro2_generic_read ( gyro2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set cs pin function
 * 
 * @param ctx     Click object.
 * @param val     Pin state value.
 * 
 * @description Function for setting the chip select pin value.
 */
void gyro2_scs_set ( gyro2_t *ctx, uint8_t val );

/**
 * @brief Set rst pin function
 * 
 * @param ctx     Click object.
 * @param val     Pin state value.
 * 
 * @description Function for setting the hw reset pin.
 */
void gyro2_rst_set ( gyro2_t *ctx, uint8_t val );

/**
 * @brief Comm interface function
 * 
 * @param ctx     Click object.
 * @param val     Pin state value.
 * 
 * @description Function for setting the communication interface.
 * <pre>
 *  0 - I2C inteface enabled
 *  1 - SPI interface enabled 
 * </pre>
 */
void gyro2_cs_set ( gyro2_t *ctx, uint8_t val );

/**
 * @brief Set ready pin function
 * 
 * @param ctx     Click object.
 * @param val     Pin state value.
 * 
 * @description Function for setting the ready pin.
 */
void gyro2_rdy_set ( gyro2_t *ctx, uint8_t val );

/**
 * @brief Get ready pin function
 * 
 * @param ctx     Click object.
 *  
 * @description Function for reading the state of the ready pin.
 */
uint8_t gyro2_rdy_get ( gyro2_t *ctx );

/**
 * @brief Get int pin function
 * 
 * @param ctx     Click object.
 *  
 * @description Function for reading the state of the interrupt pin.
 */
uint8_t gyro2_int_get ( gyro2_t *ctx );

/**
 * @brief Hardware reset function
 * 
 * @param ctx     Click object.
 * 
 * @description Function for hardware reset of the device.
 */
void gyro2_hw_reset ( gyro2_t *ctx );

/**
 * @brief ID return function
 * 
 * @param ctx     Click object.
 * 
 * @description Function will return the ID from the ID register
  */
uint8_t gyro2_get_id ( gyro2_t *ctx );

/**
 * @brief Axis read function
 * 
 * @param ctx           Click object.
 * @param axis_data     16bit axis data array
 * 
 * @description Function will read the X, Y and Z axis registers.
 * Data that is read is storred the 3 16bit array.
  */
void gyro2_get_axisraw ( gyro2_t *ctx, int16_t *axis_data );

/**
 * @brief Calc axis funtion
 * 
 * @param axis_data     16bit axis data array
 * 
 * @description Function for calculating raw axis data.
  */
void gyro2_calc_axis ( int16_t *axis_data );

/**
 * @brief Temperature read function
 * 
 * @param ctx        Click object.
 * 
 * @description Function for reading the temperature register.
 */
uint8_t gyro2_read_temperature ( gyro2_t *ctx );

/** 
 * @brief Soft reset function
 * 
 * @param ctx     Click object.
 * 
 * @description Function for tringgering a software reset of the click board.
  */
void gyro2_sw_reset ( gyro2_t *ctx );

/**
 * @brief Data rate function
 * 
 * @param ctx     Click object.
 * @param rate    Data rate 
 * 
 * @description Function for setting the data rate.
*/
void gyro2_set_dr ( gyro2_t *ctx, uint8_t rate );

void gyro2_set_opmode ( gyro2_t *ctx, uint8_t opmode );

/**
 * @brief Interrupt cfg function
 * 
 * @param ctx                       Click object.
 * @param int_route                 Cfg route.
 * @param int_en                    Interrupt enable
 * @param polarity_outdrvsetting    logical polarity
 * 
 * @description Function for configuring Interrupt register
  */
void gyro2_interrupt_cfg ( gyro2_t *ctx, uint8_t int_route, uint8_t int_en, uint8_t polarity_outdrvsetting );

/**
 * @brief Int event generation function
 * 
 * @param ctx                       Click object.
 * @param cfg                       Configuration value
 * 
 * @description Function for enabling interrupt event generation
   */
void gyro2_interrupt_event_generation ( gyro2_t *ctx, uint8_t cfg );

/**
 * @brief Sensitivity function
 *
 * @param ctx                       Click object
 * @param s_setting                 Sensitivity setting
 *
 * @description Function for setting the sensitivity
  */
void gyro2_sensitivity ( gyro2_t *ctx, uint8_t s_setting );

/**
 * @brief Filter and scale of measurement functio
 *
 * @param ctx                       Click object
 * @param low_pass                  Low pass filte
 * @param hi_pass                   High pass filte
 * @param scale_set                 Scake settin
 *
 * @description Function for setting filters and the full scale of the measurement
  */
void gyro2_fr_setup ( gyro2_t *ctx, uint8_t low_pass, uint8_t hi_pass, uint8_t scale_set );

#ifdef __cplusplu

#endif
#endif  // GYRO2_H

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END

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
 * \brief This file contains API for Presence Click driver.
 *
 * \addtogroup presence Presence Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESENCE_H
#define PRESENCE_H

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
#define PRESENCE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESENCE_OK                             0
#define PRESENCE_ERROR                         -1
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define PRESENCE_REG_TP_OBJECT_MSB              0x01
#define PRESENCE_REG_TP_OBJECT_MID              0x02
#define PRESENCE_REG_TP_OBJECT_LSB              0x03
#define PRESENCE_REG_TP_AMBIENT_MSB             0x03
#define PRESENCE_REG_TP_AMBIENT_LSB             0x04
#define PRESENCE_REG_TP_OBJECT_LP1_MSB          0x05
#define PRESENCE_REG_TP_OBJECT_LP1_MID          0x06
#define PRESENCE_REG_TP_OBJECT_LP1_LSB          0x07
#define PRESENCE_REG_TP_OBJECT_LP2_MSB          0x07
#define PRESENCE_REG_TP_OBJECT_LP2_MID          0x08
#define PRESENCE_REG_TP_OBJECT_LP2_LSB          0x09
#define PRESENCE_REG_TP_AMBIENT_LP3_MSB         0x0A
#define PRESENCE_REG_TP_AMBIENT_LP3_LSB         0x0B
#define PRESENCE_REG_TP_OBJECT_LP2F_MSB         0x0C
#define PRESENCE_REG_TP_OBJECT_LP2F_MID         0x0D
#define PRESENCE_REG_TP_OBJECT_LP2F_LSB         0x0E
#define PRESENCE_REG_TP_PRESENCE                0x0F
#define PRESENCE_REG_TP_MOTION                  0x10
#define PRESENCE_REG_TP_AMBIENT_SHOCK           0x11
#define PRESENCE_REG_INTERRUPT_STATUS           0x12
#define PRESENCE_REG_CHIP_STATUS                0x13
#define PRESENCE_REG_LOW_PASS_TIME_1            0x14
#define PRESENCE_REG_LOW_PASS_TIME_2            0x15
#define PRESENCE_REG_TP_PRESENCE_THR            0x16
#define PRESENCE_REG_TP_MOTION_THR              0x17
#define PRESENCE_REG_TP_AMB_SHOCK_THR           0x18
#define PRESENCE_REG_INTERRUPT_MASK_1           0x19
#define PRESENCE_REG_INTERRUPT_MASK_2           0x1A
#define PRESENCE_REG_TIMER_INTERRUPT            0x1B
#define PRESENCE_REG_TP_OT_THR_1                0x1C
#define PRESENCE_REG_TP_OT_THR_2                0x1D
#define PRESENCE_REG_EEPROM_CTRL                0x1F
/** \} */

/**
 * \defgroup eeprom Eeprom
 * \{
 */
#define PRESENCE_EEPROM_PROTOCOL                0x20
#define PRESENCE_EEPROM_CHECKSUM_1              0x21
#define PRESENCE_EEPROM_CHECKSUM_2              0x22
#define PRESENCE_EEPROM_LOOKUP                  0x29
#define PRESENCE_EEPROM_PTAT25_1                0x2A
#define PRESENCE_EEPROM_PTAT25_2                0x2B
#define PRESENCE_EEPROM_M_1                     0x2C
#define PRESENCE_EEPROM_M_2                     0x2D
#define PRESENCE_EEPROM_U0_1                    0x2E
#define PRESENCE_EEPROM_U0_2                    0x2F
#define PRESENCE_EEPROM_UOUT_1                  0x30
#define PRESENCE_EEPROM_UOUT_2                  0x31
#define PRESENCE_EEPROM_TOBJ                    0x32
#define PRESENCE_EEPROM_SLAVE_ADDR              0x3F
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define PRESENCE_DEVICE_SLAVE_ADDRESS           0x0C
#define PRESENCE_DEVICE_GEN_CALL_ADDRESS        0x00
/** \} */

/**
 * \defgroup time_const Low-Pass time constants
 * \{
 */
#define PRESENCE_LOW_PASS_TIME_512S             0x00
#define PRESENCE_LOW_PASS_TIME_256S             0x01
#define PRESENCE_LOW_PASS_TIME_128S             0x02
#define PRESENCE_LOW_PASS_TIME_64S              0x03
#define PRESENCE_LOW_PASS_TIME_32S              0x04
#define PRESENCE_LOW_PASS_TIME_16S              0x05
#define PRESENCE_LOW_PASS_TIME_8S               0x08
#define PRESENCE_LOW_PASS_TIME_4S               0x09
#define PRESENCE_LOW_PASS_TIME_2S               0x0A
#define PRESENCE_LOW_PASS_TIME_1S               0x0B
#define PRESENCE_LOW_PASS_TIME_0P50S            0x0C
#define PRESENCE_LOW_PASS_TIME_0P25S            0x0D
/** \} */

/**
 * \defgroup int_mask_1 Interrupt mask 1
 * \{
 */
#define PRESENCE_INT_MASK1_TP_OT                0x10
#define PRESENCE_INT_MASK1_PRESENCE             0x08
#define PRESENCE_INT_MASK1_MOTION               0x04
#define PRESENCE_INT_MASK1_AMB_SHOCK            0x02
#define PRESENCE_INT_MASK1_TIMER                0x01
/** \} */

/**
 * \defgroup int_mask_2 Interrupt mask 2
 * \{
 */
#define PRESENCE_INT_MASK2_TPOT_DIR             0x10
#define PRESENCE_INT_MASK2_SRC_TPOBJ_LP2        ( 0x00 << 2 )
#define PRESENCE_INT_MASK2_SRC_LP1_LP2          ( 0x01 << 2 )
#define PRESENCE_INT_MASK2_SRC_TPOBJ_LP2FROZEN  ( 0x02 << 2 )
#define PRESENCE_INT_MASK2_SRC_LP1_LP2FROZEN    ( 0x03 << 2 )
#define PRESENCE_INT_MASK2_CYCLE_TIME_30MS      0x00
#define PRESENCE_INT_MASK2_CYCLE_TIME_60MS      0x01
#define PRESENCE_INT_MASK2_CYCLE_TIME_120MS     0x02
#define PRESENCE_INT_MASK2_CYCLE_TIME_140MS     0x04
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint16_t ptat25_data;
    uint16_t m_data;
    uint16_t u0_data;
    uint8_t  tobj_data;
    uint32_t uout_data;
    uint16_t checksum_data;

} eeprom_data_t;

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
    
    eeprom_data_t eeprom_data;

} presence_t;

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

} presence_cfg_t;


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
void presence_cfg_setup ( presence_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t presence_init ( presence_t *ctx, presence_cfg_t *cfg );

/**
 * @brief Presence default configuration function.
 * @details This function executes a default configuration of Presence
 * click board.
 * @param[in] ctx : Click context object.
 * See #presence_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t presence_default_cfg ( presence_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *
 * @details This function writes data to the desired register.
 */
err_t presence_generic_write ( presence_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * 
 * @details This function reads data from the desired register.
 */
err_t presence_generic_read ( presence_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get interrupt state function
 *
 * @param ctx          Click object.
 *
 * @details This function reads state from int pin.
 */
uint8_t presence_get_int_state ( presence_t *ctx );

/**
 * @brief General call address
 * 
 * @param ctx          Click object.
 * 
 * @details This function writes general call address and sets slave address.
 */
void presence_general_call_addr ( presence_t *ctx );

/**
 * @brief EEPRM PROCESS
 *
 * @param ctx          Click object.
 * 
 * @return Has it successfully read eeprom? [ 0 - YES ] or [ -1 - NO ]
 *
 * @details This Function enables , read and dsiables the eeprom
 * and then checks whether or not it as successfully read any data from it.
 * 
 * @note This function must be performed at the start of each program
 * in order to read and accommodate all calibration coefficients.
 */
err_t presence_eeprom_process ( presence_t *ctx );

/**
 * @brief Calibration constant K
 * 
 * @param ctx          Click object.
 *
 * @return K value
 * 
 * This function returns calbration constant's K value.
 */
float presence_get_calib_constants( presence_t *ctx );

/**
 * @brief Ambient Temperature
 *
 * @param ctx          Click object.
 * @param temperature  Temperaure in C
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * 
 * @details This function returns ambient temperature in degrees Celsius.
 */
err_t presence_ambient_temperature( presence_t *ctx, float *temperature );

/**
 * @brief Object Temperature
 *
 * @param ctx          Click object.
 * @param temperature  Temperaure in C
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * 
 * @details This function returns object temperature.
 */
err_t presence_object_temperature( presence_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif  // _PRESENCE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

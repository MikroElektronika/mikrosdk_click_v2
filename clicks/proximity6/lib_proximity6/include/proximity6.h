
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
 * \brief This file contains API for Proximity 6 Click driver.
 *
 * \addtogroup proximity6 Proximity 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY6_H
#define PROXIMITY6_H

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
#define PROXIMITY6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY6_OK                           0
#define PROXIMITY6_ERROR                       -1
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define PROXIMITY6_REG_DATA_REGISTER_X1         0x00
#define PROXIMITY6_REG_DATA_REGISTER_X2         0x01
#define PROXIMITY6_REG_DATA_REGISTER_Y1         0x02
#define PROXIMITY6_REG_DATA_REGISTER_Y2         0x03
#define PROXIMITY6_REG_DATA_REGISTER_SAMPLE_I   0x04
#define PROXIMITY6_REG_DATA_REGISTER_SAMPLE_X   0x05
#define PROXIMITY6_REG_DATA_REGISTER_SAMPLE_Y   0x06
#define PROXIMITY6_REG_RESERVED1                0x07
#define PROXIMITY6_REG_ID_VERSION               0x08
#define PROXIMITY6_REG_SLAVE_ADDRESS            0x09
#define PROXIMITY6_REG_OSC_CAL_OUT              0x0A
#define PROXIMITY6_REG_RESERVED2                0x0C
#define PROXIMITY6_REG_SW_RESET                 0x0F
#define PROXIMITY6_REG_ADC_CONTROL_RESERVED1    0x10
#define PROXIMITY6_REG_ADC_CONTROL_RESERVED2    0x11
#define PROXIMITY6_REG_AFE_TRIM                 0x12
#define PROXIMITY6_REG_AFE_MUX_TEST             0x13
#define PROXIMITY6_REG_RESERVED3                0x14
#define PROXIMITY6_REG_LED_TRIM                 0x16
#define PROXIMITY6_REG_OS32K                    0x18
#define PROXIMITY6_REG_OS32M_BYPASS             0x19
#define PROXIMITY6_REG_OS32M_TRIM               0x1A
#define PROXIMITY6_REG_ADC_SPACING              0x1B
#define PROXIMITY6_REG_INT_PIN                  0x1C
#define PROXIMITY6_REG_INT_PIN_POL              0x1D
#define PROXIMITY6_REG_I2C                      0x1E
#define PROXIMITY6_REG_FIFO_TH                  0x1F
#define PROXIMITY6_REG_LED_OFFSET_WIDTH_GEST    0x20
#define PROXIMITY6_REG_LED_PERIOD_PULSES_GEST   0x21
#define PROXIMITY6_REG_LED_OFFSET_WIDTH_PROX    0x22
#define PROXIMITY6_REG_LED_PERIOD_PULSES_PROX   0x23
#define PROXIMITY6_REG_LED_MASK                 0x24
#define PROXIMITY6_REG_AFE_CONT_GEST            0x25
#define PROXIMITY6_REG_AFE_CONT_PROX            0x26
#define PROXIMITY6_REG_AFE_MASK                 0x27
#define PROXIMITY6_REG_GEST_DI_TH               0x28
#define PROXIMITY6_REG_ORIENTATION              0x29
#define PROXIMITY6_REG_PROX_TH_ON1              0x2A
#define PROXIMITY6_REG_PROX_TH_OFF1             0x2B
#define PROXIMITY6_REG_PROX_TH_ON2              0x2C
#define PROXIMITY6_REG_PROX_TH_OFF2             0x2D
#define PROXIMITY6_REG_PROX_TH_ON1_OFF1_HIGH    0x2E
#define PROXIMITY6_REG_PROX_TH_ON2_OFF2_HIGH    0x2F
#define PROXIMITY6_REG_TEST_MODE                0x30
#define PROXIMITY6_REG_POWER_DOWN_CONT          0x32
#define PROXIMITY6_REG_GAIN_CONT1               0x38
#define PROXIMITY6_REG_GAIN_CONT2               0x39
#define PROXIMITY6_REG_CH1_OFFSET               0x3A
#define PROXIMITY6_REG_CH2_OFFSET               0x3B
#define PROXIMITY6_REG_CH3_OFFSET               0x3C
#define PROXIMITY6_REG_CH4_OFFSET               0x3D
#define PROXIMITY6_REG_SLOPE_TH                 0x3E
#define PROXIMITY6_REG_FREQ                     0x40
#define PROXIMITY6_REG_LED_REF                  0x41
#define PROXIMITY6_REG_OP_TIME                  0x42
#define PROXIMITY6_REG_AFE_TIME                 0x43
#define PROXIMITY6_REG_DSAMPLE_TIME             0x44
#define PROXIMITY6_REG_OPERATION_CONTROL        0x45
#define PROXIMITY6_REG_DEC_MODE                 0x46
#define PROXIMITY6_REG_INT_MASK                 0x48
#define PROXIMITY6_REG_INT_STATUS               0x49
#define PROXIMITY6_REG_I2C_STATUS               0x4A
#define PROXIMITY6_REG_DATA_BUFFER_OUT          0x60
#define PROXIMITY6_REG_DEBUG_X1L                0x68
#define PROXIMITY6_REG_DEBUG_X2L                0x69
#define PROXIMITY6_REG_DEBUG_Y1L                0x6A
#define PROXIMITY6_REG_DEBUG_Y2L                0x6B
#define PROXIMITY6_REG_DEBUG_X1H                0x6C
#define PROXIMITY6_REG_DEBUG_X2H                0x6D
#define PROXIMITY6_REG_DEBUG_Y1H                0x6E
#define PROXIMITY6_REG_DEBUG_Y2H                0x6F
/** \} */

/**
 * \defgroup mode_selectors Mode Selectors
 * \{
 */
#define PROXIMITY6_STANDBY_MODE                 0
#define PROXIMITY6_PROXIMITY_MODE               1
#define PROXIMITY6_SAMPLE_MODE                  2
#define PROXIMITY6_IDLE_MODE                    3
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
    uint8_t mode_sel;

} proximity6_t;

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

} proximity6_cfg_t;

/**
 * @brief Click axis data structure definition.
 */
typedef struct
{
    uint16_t val_x1;
    uint16_t val_x2;
    uint16_t val_y1;
    uint16_t val_y2;

} proximity6_data_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void proximity6_cfg_setup ( proximity6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function executes default configuration for Proximity6 Click and sets the registers in default state.
 */
err_t proximity6_default_cfg ( proximity6_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t proximity6_generic_write ( proximity6_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function reads data from the desired register.
 */
err_t proximity6_generic_read ( proximity6_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief Mode Set function
 *
 * @param ctx           Click object.
 * @param select_mode   0 - Standby Mode, 1 - Proximity Mode, 2 - Sample Mode, 3 - Idle Mode
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function puts the device in the desired operating mode.
 */
err_t proximity6_set_mode( proximity6_t *ctx, uint8_t select_mode );

/**
 * @brief Data Read function
 *
 * @param ctx           Click object.
 * @param axis_out      Structure object where data will be stored
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function reads proximity data when one or more data register is updated.
 */
err_t proximity6_read_data( proximity6_t *ctx, proximity6_data_t *axis_out );

/**
 * @brief Interrupt Check function
 *
 * @param ctx          Click object.
 * 
 * @return State of INT pin
 *
 * @details Function checks is interrupt occurred and returns the state of the INT pin.
 * INT pin can be configured to show are data registers updated with the new values or not.
 */
uint8_t proximity6_check_interrupt( proximity6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY6_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

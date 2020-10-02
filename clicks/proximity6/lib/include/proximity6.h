
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
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY6_RETVAL  uint8_t

#define PROXIMITY6_OK           0x00
#define PROXIMITY6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define PROXIMITY6_DATA_REGISTER_X1_REG          0x00
#define PROXIMITY6_DATA_REGISTER_X2_REG          0x01
#define PROXIMITY6_DATA_REGISTER_Y1_REG          0x02
#define PROXIMITY6_DATA_REGISTER_Y2_REG          0x03
#define PROXIMITY6_DATA_REGISTER_SAMPLE_I_REG    0x04
#define PROXIMITY6_DATA_REGISTER_SAMPLE_X_REG    0x05
#define PROXIMITY6_DATA_REGISTER_SAMPLE_Y_REG    0x06
#define PROXIMITY6_RESERVED1_REG                 0x07
#define PROXIMITY6_ID_VERSION_REG                0x08
#define PROXIMITY6_SLAVE_ADDRESS_REG             0x09
#define PROXIMITY6_OSC_CAL_OUT_REG               0x0A
#define PROXIMITY6_RESERVED2                     0x0C
#define PROXIMITY6_SW_RESET_REG                  0x0F
#define PROXIMITY6_ADC_CONTROL_RESERVED1_REG     0x10
#define PROXIMITY6_ADC_CONTROL_RESERVED2_REG     0x11
#define PROXIMITY6_AFE_TRIM_REG                  0x12
#define PROXIMITY6_AFE_MUX_TEST_REG              0x13
#define PROXIMITY6_RESERVED3_REG                 0x14
#define PROXIMITY6_LED_TRIM_REG                  0x16
#define PROXIMITY6_OS32K_REG                     0x18
#define PROXIMITY6_OS32M_BYPASS_REG              0x19
#define PROXIMITY6_OS32M_TRIM_REG                0x1A
#define PROXIMITY6_ADC_SPACING_REG               0x1B
#define PROXIMITY6_INT_PIN_REG                   0x1C
#define PROXIMITY6_INT_PIN_POL_REG               0x1D
#define PROXIMITY6_I2C_REG                       0x1E
#define PROXIMITY6_FIFO_TH_REG                   0x1F
#define PROXIMITY6_LED_OFFSET_WIDTH_GEST_REG     0x20
#define PROXIMITY6_LED_PERIOD_PULSES_GEST_REG    0x21
#define PROXIMITY6_LED_OFFSET_WIDTH_PROX_REG     0x22
#define PROXIMITY6_LED_PERIOD_PULSES_PROX_REG    0x23
#define PROXIMITY6_LED_MASK_REG                  0x24
#define PROXIMITY6_AFE_CONT_GEST_REG             0x25
#define PROXIMITY6_AFE_CONT_PROX_REG             0x26
#define PROXIMITY6_AFE_MASK_REG                  0x27
#define PROXIMITY6_GEST_DI_TH_REG                0x28
#define PROXIMITY6_ORIENTATION_REG               0x29
#define PROXIMITY6_PROX_TH_ON1_REG               0x2A
#define PROXIMITY6_PROX_TH_OFF1_REG              0x2B
#define PROXIMITY6_PROX_TH_ON2_REG               0x2C
#define PROXIMITY6_PROX_TH_OFF2_REG              0x2D
#define PROXIMITY6_PROX_TH_ON1_OFF1_HIGH_REG     0x2E
#define PROXIMITY6_PROX_TH_ON2_OFF2_HIGH_REG     0x2F
#define PROXIMITY6_TEST_MODE_REG                 0x30
#define PROXIMITY6_POWER_DOWN_CONT_REG           0x32
#define PROXIMITY6_GAIN_CONT1_REG                0x38
#define PROXIMITY6_GAIN_CONT2_REG                0x39
#define PROXIMITY6_CH1_OFFSET_REG                0x3A
#define PROXIMITY6_CH2_OFFSET_REG                0x3B
#define PROXIMITY6_CH3_OFFSET_REG                0x3C
#define PROXIMITY6_CH4_OFFSET_REG                0x3D
#define PROXIMITY6_SLOPE_TH_REG                  0x3E
#define PROXIMITY6_FREQ_REG                      0x40
#define PROXIMITY6_LED_REF_REG                   0x41
#define PROXIMITY6_OP_TIME_REG                   0x42
#define PROXIMITY6_AFE_TIME_REG                  0x43
#define PROXIMITY6_DSAMPLE_TIME_REG              0x44
#define PROXIMITY6_OPERATION_CONTROL_REG         0x45
#define PROXIMITY6_DEC_MODE_REG                  0x46
#define PROXIMITY6_INT_MASK_REG                  0x48
#define PROXIMITY6_INT_STATUS_REG                0x49
#define PROXIMITY6_I2C_STATUS_REG                0x4A
#define PROXIMITY6_DATA_BUFFER_OUT_REG           0x60
#define PROXIMITY6_DEBUG_X1L_REG                 0x68
#define PROXIMITY6_DEBUG_X2L_REG                 0x69
#define PROXIMITY6_DEBUG_Y1L_REG                 0x6A
#define PROXIMITY6_DEBUG_Y2L_REG                 0x6B
#define PROXIMITY6_DEBUG_X1H_REG                 0x6C
#define PROXIMITY6_DEBUG_X2H_REG                 0x6D
#define PROXIMITY6_DEBUG_Y1H_REG                 0x6E
#define PROXIMITY6_DEBUG_Y2H_REG                 0x6F
/** \} */

/**
 * \defgroup mode_selectors Mode Selectors
 * \{
 */
#define PROXIMITY6_STANDBY_MODE                     0
#define PROXIMITY6_PROXIMITY_MODE                   1
#define PROXIMITY6_SAMPLE_MODE                      2
#define PROXIMITY6_IDLE_MODE                        3
/** \} */

/**
 * \defgroup pos_values Position Values
 * \{
 */
#define PROXIMITY6_RIGHT_POS                        0
#define PROXIMITY6_LEFT_POS                         1
#define PROXIMITY6_BOTTOM_POS                       2
#define PROXIMITY6_UP_POS                           3
#define PROXIMITY6_NO_DETECT_POS                    4
/** \} */

/**
 * \defgroup res_set Resolution setters
 * \{
 */
#define PROXIMITY6_RESOLUTION_300                   0
#define PROXIMITY6_RESOLUTION_400                   1
#define PROXIMITY6_RESOLUTION_500                   2
#define PROXIMITY6_RESOLUTION_600                   3
#define PROXIMITY6_RESOLUTION_700                   4
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
void proximity6_cfg_setup ( proximity6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY6_RETVAL proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity6 click and sets the registers in default state.
 */
void proximity6_default_cfg ( proximity6_t *ctx );

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
void proximity6_generic_write ( proximity6_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len );

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
void proximity6_generic_read ( proximity6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Mode Set function
 *
 * @param ctx          Click object.
 * @param selectMode   0 - Standby Mode, 1 - Proximity Mode, 2 - Sample Mode, 3 - Idle Mode
 *
 * @return 0 - OK, 1 - Wrong parameter value
 *
 * @description Function puts the device in the desired operating mode.
 */
uint8_t proximity6_set_mode( proximity6_t *ctx, uint8_t select_mode );

/**
 * @brief Data Read function
 *
 * @param ctx          Click object.
 * @param axisOut      Buffer where data be stored
 *
 * @return 0 - OK, 1 - Device is in Standby or Idle Mode
 *
 * @description Function reads proximity data when one or more data register is updated.
 */
uint8_t proximity6_read_data( proximity6_t *ctx, uint16_t *axis_out );

/**
 * @brief Position Get function
 *
 * @param ctx          Click object.
 * @param position         Buffer where position data be stored
 *
 * @description Function reads proximity data and checks from which side the object (body) affects on the sensor.
 */
void proximity6_get_position( proximity6_t *ctx, uint8_t *position );

/**
 * @brief Data Display function
 *
 * @param ctx          Click object.
 * @param dataValue       Buffer where data be stored
 * @param setResolution    Determines in which resolution the data be shown
 *
 * @return 0 - OK, 1 - Wrong resolution parameter
 *
 * @description Function shows proximity data values in determined resolution as graphic view.
 */
uint8_t proximity6_display_data( proximity6_t *ctx, uint8_t *data_value, uint8_t set_resolution );

/**
 * @brief Settings Load function
 *
 * @param ctx          Click object.
 * 
 * @description Function loads settings which puts device in proper operating mode.
 */
void proximity6_load_settings( proximity6_t *ctx );

/**
 * @brief Interrupt Check function
 *
 * @param ctx          Click object.
 * 
 * @return State of INT pin
 *
 * @description Function checks is interrupt occurred and returns the state of the INT pin.
 * INT pin can be configured to show are data registers updated with the new values or not.
 */
uint8_t proximity6_check_interrupt( proximity6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

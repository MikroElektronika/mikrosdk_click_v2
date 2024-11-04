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
 * \brief This file contains API for DAC 7 Click driver.
 *
 * \addtogroup dac7 DAC 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC7_H
#define DAC7_H

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
#define DAC7_MAP_MIKROBUS( cfg, mikrobus )           \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );
/** \} */

/**
 * \defgroup error_code Error code
 * \{
 */
#define DAC7_RETVAL       uint8_t
#define DAC7_RETVAL_T     uint8_t

#define DAC7_OK                                        0x00
#define DAC7_INIT_ERROR                                0xFF

#define DAC7_ERROR                                     0x00
#define DAC7_SUCCESS                                   0x01
/** \} */

/**
 * \defgroup command Command definition
 * \{
 */
#define DAC7_COMMAND_WRITE_INPUT_REGISTER              0x00
#define DAC7_COMMAND_UPDATE_DAC_REGISTER               0x08
#define DAC7_COMMAND_WRITE_INPUT_REGISTER_UPDATE_ALL   0x10
#define DAC7_COMMAND_WRITE_UPDATE_CHANNEL              0x18
#define DAC7_COMMAND_POWER_UPDOWN                      0x20
#define DAC7_COMMAND_RESET                             0x28
#define DAC7_COMMAND_SET_LDAC                          0x30
#define DAC7_COMMAND_REFERENCE_ONOFF                   0x38          

/** \} */

/**
 * \defgroup address Address command
 * \{
 */
#define DAC7_ADDRESS_CHANNEL_A                         0x00
#define DAC7_ADDRESS_CHANNEL_B                         0x01
#define DAC7_ADDRESS_CHANNEL_C                         0x02
#define DAC7_ADDRESS_CHANNEL_D                         0x03
#define DAC7_ADDRESS_CHANNEL_ALL                       0x07
/** \} */

/**
 * \defgroup select_channel Select channel
 * \{
 */
#define DAC7_SELECT_CHANNEL_A                          0x01
#define DAC7_SELECT_CHANNEL_B                          0x02
#define DAC7_SELECT_CHANNEL_C                          0x04
#define DAC7_SELECT_CHANNEL_D                          0x08
#define DAC7_SELECT_CHANNEL_ALL                        0x0F
/** \} */

/**
 * \defgroup set_mode Set mode
 * \{
 */
#define DAC7_SET_MODE_INPUT                            0x00
#define DAC7_SET_MODE_INPUT_DAC                        0x18
#define DAC7_SET_MODE_INPUT_DAC_ALL                    0x10
/** \} */

/**
 * \defgroup pwr_mode Power mode
 * \{
 */
#define DAC7_PWR_MODE_NORMAL                           0x00
#define DAC7_PWR_MODE_POWERDOWN_1K                     0x10
#define DAC7_PWR_MODE_POWERDOWN_100K                   0x20
#define DAC7_PWR_MODE_TRISTATE                         0x30
/** \} */

/**
 * \defgroup pwr_on Set power enable
 * \{
 */
#define DAC7_PWR_ON_DISABLE                            0x00
#define DAC7_PWR_ON_ENABLE                             0x01
/** \} */

/**
 * \defgroup sw_rst Reset
 * \{
 */
#define DAC7_SW_RST_COMMAND                            0x01
/** \} */

/**
 * \defgroup dont_care Don't care
 * \{
 */
#define DAC7_DONT_CARE_COMMAND                         0x00
/** \} */

/**
 * \defgroup mask_bit Mask bit
 * \{
 */
#define DAC7_MASK_BIT_COMMAND                          0x38
#define DAC7_MASK_BIT_ADDRESS                          0x07
#define DAC7_MASK_BIT_POWERMODE                        0x30
#define DAC7_MASK_BIT_SEL_CHANNEL                      0x0F
#define DAC7_MASK_BIT_0                                0x01
#define DAC7_MASK_BIT_LBS                              0x00FF
/** \} */

/**
 * \defgroup vref Vref
 * \{
 */
#define DAC7_VREF_4096mV                               0x1000
#define DAC7_VREF_5000mV                               0x13BA
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
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;

} dac7_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} dac7_cfg_t;

/** \} */ // End types group

// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 
/** \} */ // End constants group

// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group

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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void dac7_cfg_setup ( dac7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param dac7          Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
DAC7_RETVAL dac7_init ( dac7_t *ctx, dac7_cfg_t *cfg );

/**
 * @brief Generic write data function.
 *
 * @param ctx           Click object.
 * @param def_cmd       3-bit command definition.
 * @param addr_cmd      3-bit address command.
 * @param write_data    12-bit data to write.
 *
 * @description This function set 3-bit command definition and write 12-bit data 
 * to the target 3-bit address command of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
void dac7_write_data ( dac7_t *ctx, uint8_t def_cmd, uint8_t addr_cmd, uint16_t write_data );

/**
 * @brief Set the values of the specified channel function.
 *
 * @param ctx           Click object.
 * @param set_cmd       3-bit command definition.
 * @param addr_ch       3-bit address command.
 * @param write_data    12-bit values of the specified channel.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function set 12-bit value of 3-bit command definition 
 * to the target 3-bit address command of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_set_channel ( dac7_t *ctx, uint8_t set_cmd, uint8_t addr_ch, uint16_t write_data );

/**
 * @brief Set the voltage values of the specified channel function.
 *
 * @param ctx           Click object.
 * @param addr_ch       3-bit address command.
 * @param vol_val       Voltage values [ from 0 mV to 4096 mV or 5000 mV ].
 * @param v_ref_mv      Voltage reference value.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function set 12-bit value of 3-bit command definition 
 * to the target 3-bit address command of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_set_ch_voltage ( dac7_t *ctx, uint8_t addr_ch, uint16_t vol_val, uint16_t v_ref_mv );

/**
 * @brief Update channel function.
 *
 * @param ctx           Click object.
 * @param addr_ch       3-bit address command.
 * @param ch_data       12-bit values of the specified channel.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function write and update 12-bit data to the target 
 * 3-bit address command of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_update_channel ( dac7_t *ctx, uint8_t addr_ch, uint16_t ch_data );

/**
 * @brief Set power mode function.
 *
 * @param ctx           Click object.
 * @param pwr_en        Power Enable/Disable.
 * @param sel_ch        Channel selection.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function set power mode of selected channel 
 * of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_set_power ( dac7_t *ctx, uint8_t pwr_en, uint8_t sel_ch );

/**
 * @brief Software reset function.
 *
 * @param ctx           Click object.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function set software reset of selected channel 
 * of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_sw_reset ( dac7_t *ctx );

/**
 * @brief Set LDAC setup function.
 *
 * @param ctx           Click object.
 * @param sel_ch        Channel selection.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function set LDAC setup of respective channel 
 * of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_set_ldac ( dac7_t *ctx, uint8_t sel_ch );

/**
 * @brief Set internal reference function.
 *
 * @param ctx           Click object.
 * @param int_ref_en    Channel selection.
 * 
 * @return 8-bit data containing flags.
 *         Flag state:
 * -------------------------------------
 * <pre>
 *     0x00 ( DAC7_ERROR )   - Error
 *     0x01 ( DAC7_SUCCESS ) - Success
 * </pre>
 * -------------------------------------
 *
 * @description This function set internal reference of respective channel 
 * of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
 */
DAC7_RETVAL_T dac7_set_internal_reference ( dac7_t *ctx, uint8_t int_ref_en );

#ifdef __cplusplus
}
#endif
#endif  // _DAC7_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

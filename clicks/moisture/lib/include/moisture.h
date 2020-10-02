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
 * \brief This file contains API for Moisture Click driver.
 *
 * \addtogroup moisture Moisture Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MOISTURE_H
#define MOISTURE_H

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
#define MOISTURE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MOISTURE_RETVAL  uint8_t

#define MOISTURE_OK           0x00
#define MOISTURE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Device slave address
 * \{
 */
#define MOISTURE_DEV_ADR_GND                      0x2A
#define MOISTURE_DEV_ADR_VCC                      0x2B
/** \} */

/**
 * \defgroup def_offset Default offset
 * \{
 */
#define MOISTURE_DEFAULT_OFFSET                   0x00AA
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define MOISTURE_REG_DATA                         0x00
#define MOISTURE_REG_RCNT                         0x08
#define MOISTURE_REG_OFFSET                       0x0C
#define MOISTURE_REG_SETTLE_CNT                   0x10
#define MOISTURE_REG_CLOCK_DIVIDERS               0x14
#define MOISTURE_REG_STATUS                       0x18
#define MOISTURE_REG_ERR_CFG                      0x19
#define MOISTURE_REG_CFG                          0x1A
#define MOISTURE_REG_MUX_CFG                      0x1B
#define MOISTURE_REG_RESET_DEV                    0x1C
#define MOISTURE_REG_DRIVE_CURR                   0x1E
#define MOISTURE_REG_DEVICE_ID                    0x7F
#define MOISTURE_REG_MFC_ID                       0x7E
/** \} */

/**
 * \defgroup drive_current Drive current
 * \{
 */
#define MOISTURE_DRIVE_CURR_0_016mA               0x0000
#define MOISTURE_DRIVE_CURR_0_018mA               0x0800
#define MOISTURE_DRIVE_CURR_0_021mA               0x1000
#define MOISTURE_DRIVE_CURR_0_025mA               0x1800
#define MOISTURE_DRIVE_CURR_0_028mA               0x2000
#define MOISTURE_DRIVE_CURR_0_033mA               0x2800
#define MOISTURE_DRIVE_CURR_0_038mA               0x3000
#define MOISTURE_DRIVE_CURR_0_044mA               0x3800
#define MOISTURE_DRIVE_CURR_0_052mA               0x4000
#define MOISTURE_DRIVE_CURR_0_060mA               0x4800
#define MOISTURE_DRIVE_CURR_0_069mA               0x5000
#define MOISTURE_DRIVE_CURR_0_081mA               0x5800
#define MOISTURE_DRIVE_CURR_0_093mA               0x6000
#define MOISTURE_DRIVE_CURR_0_108mA               0x6800
#define MOISTURE_DRIVE_CURR_0_126mA               0x7000
#define MOISTURE_DRIVE_CURR_0_146mA               0x7800
#define MOISTURE_DRIVE_CURR_0_169mA               0x8000
#define MOISTURE_DRIVE_CURR_0_196mA               0x8800
#define MOISTURE_DRIVE_CURR_0_228mA               0x9000
#define MOISTURE_DRIVE_CURR_0_264mA               0x9800
#define MOISTURE_DRIVE_CURR_0_307mA               0xA000
#define MOISTURE_DRIVE_CURR_0_356mA               0xA800
#define MOISTURE_DRIVE_CURR_0_413mA               0xB000
#define MOISTURE_DRIVE_CURR_0_479mA               0xB800
#define MOISTURE_DRIVE_CURR_0_555mA               0xC000
#define MOISTURE_DRIVE_CURR_0_644mA               0xC800
#define MOISTURE_DRIVE_CURR_0_747mA               0xD000
#define MOISTURE_DRIVE_CURR_0_867mA               0xD800
#define MOISTURE_DRIVE_CURR_1_006mA               0xE000
#define MOISTURE_DRIVE_CURR_1_167mA               0xE800
#define MOISTURE_DRIVE_CURR_1_354mA               0xF000
#define MOISTURE_DRIVE_CURR_1_571mA               0xF800
/** \} */

/**
 * \defgroup reset Reset device
 * \{
 */
#define MOISTURE_RESET_DEVICE                     0x8000
#define MOISTURE_OUTPUT_GAIN_x1                   0x0000
#define MOISTURE_OUTPUT_GAIN_x4                   0x0200
#define MOISTURE_OUTPUT_GAIN_x8                   0x0400
#define MOISTURE_OUTPUT_GAIN_x16                  0x0600
/** \} */

/**
 * \defgroup mux_cfg Mux configuration
 * \{
 */
#define MOISTURE_MUX_CFG_AUTOSCAN_MODE            0x8000
#define MOISTURE_MUX_CFG_CONTINUOUS_MODE          0x0000
#define MOISTURE_MUX_CFG_RR_SEQUENCE_CH_01        0x0000
#define MOISTURE_MUX_CFG_DEGLITCH_1MHz            0x0001
#define MOISTURE_MUX_CFG_DEGLITCH_3_3MHz          0x0004
#define MOISTURE_MUX_CFG_DEGLITCH_10MHz           0x0005
#define MOISTURE_MUX_CFG_DEGLITCH_33MHz           0x0007
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define MOISTURE_CFG_ACTIVE_CHAN_CH0              0x0000
#define MOISTURE_CFG_DEVICE_ACTIVE                0x0000
#define MOISTURE_CFG_DEVICE_IN_SLEEP_MODE         0x2000
#define MOISTURE_CFG_FULL_CURRENT_MODE            0x0000
#define MOISTURE_CFG_LOW_POWER_MODE               0x0800
#define MOISTURE_CFG_INT_PIN_ENABLE               0x0000
#define MOISTURE_CFG_INT_PIN_DISABLE              0x0080
/** \} */

/**
 * \defgroup error_cfg  Error configuration
 * \{
 */
#define MOISTURE_ERR_CFG_WATCHDOG_TIMEOUT         0x2000
#define MOISTURE_ERR_CFG_AMPLITUDE_HIGH           0x1000
#define MOISTURE_ERR_CFG_AMPLITUDE_LOW            0x0800
#define MOISTURE_ERR_CFG_DATA_RDY_IN_PIN          0x0001
/** \} */

/**
 * \defgroup status  Status
 * \{
 */
#define MOISTURE_STATUS_ERR_CHAN_0                0x0000
#define MOISTURE_STATUS_ERR_WD                    0x0800
#define MOISTURE_STATUS_ERR_AHW                   0x0400
#define MOISTURE_STATUS_ERR_AHL                   0x0200
#define MOISTURE_STATUS_DATA_RDY                  0x0040
#define MOISTURE_STATUS_CH0_UNREADCONV            0x0008
/** \} */

/**
 * \defgroup clock_divider Clock divider
 * \{
 */
#define MOISTURE_CLOCK_DIVIDERS_x1                0x00001
#define MOISTURE_CLOCK_DIVIDERS_x2                0x00002
#define MOISTURE_CLOCK_DIVIDERS_x3                0x00003
#define MOISTURE_CLOCK_DIVIDERS_x4                0x00004
#define MOISTURE_CLOCK_DIVIDERS_x5                0x00005
#define MOISTURE_CLOCK_DIVIDERS_x6                0x00006
#define MOISTURE_CLOCK_DIVIDERS_x7                0x00007
#define MOISTURE_CLOCK_DIVIDERS_x8                0x00008
#define MOISTURE_CLOCK_DIVIDERS_x9                0x00009
#define MOISTURE_CLOCK_DIVIDERS_x10               0x0000A
#define MOISTURE_CLOCK_DIVIDERS_x11               0x0000B
#define MOISTURE_CLOCK_DIVIDERS_x12               0x0000C
#define MOISTURE_CLOCK_DIVIDERS_x13               0x0000D
#define MOISTURE_CLOCK_DIVIDERS_x14               0x0000E
#define MOISTURE_CLOCK_DIVIDERS_x15               0x0000F
/** \} */

/**
 * \defgroup device_id Device ID
 * \{
 */
#define MOISTURE_FDC2112_ID                       0x3054
#define MOISTURE_FDC2212_ID                       0x3055
/** \} */

/**
 * \defgroup device_settings Device Settings
 * \{
 */
#define MOISTURE_SETTLE_CNT_CFG_DEFAULT           0x0064
#define MOISTURE_RCNT_CFG_DEFAULT                 0x010F
#define MOISTURE_COMBINED_VAL_CH0_DIV             0x2001
#define MOISTURE_DRIVE_CURR_CH0                   0x7C00
#define MOISTURE_ALL_ERR_ENABLED                  0xFFFF
#define MOISTURE_REG_CFG_DEFAULT_SETTINGS         0x0000
#define MOISTURE_INPUT_DEGLITCH_FILT_BWDTH_33MHZ  0x0007
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
    uint16_t calib_air_data;

} moisture_t;

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

} moisture_cfg_t;

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
void moisture_cfg_setup ( moisture_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MOISTURE_RETVAL moisture_init ( moisture_t *ctx, moisture_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Moisture click.
 * <pre>
 *   MOISTURE_REG_RESET_DEV
 * -------------------------------------------
 *   MOISTURE_OUTPUT_GAIN_x16
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_SETTLE_CNT
 * -------------------------------------------
 *   MOISTURE_SETTLE_CNT_CFG_DEFAULT
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_RCNT
 * -------------------------------------------
 *   MOISTURE_RCNT_CFG_DEFAULT
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_OFFSET
 * -------------------------------------------
 *   MOISTURE_DEFAULT_OFFSET
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_CLOCK_DIVIDERS
 * -------------------------------------------
 *   MOISTURE_COMBINED_VAL_CH0_DIV
 *   MOISTURE_CLOCK_DIVIDERS_x10
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_DRIVE_CURR
 * -------------------------------------------
 *   MOISTURE_DRIVE_CURR_CH0
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_ERR_CFG
 * -------------------------------------------
 *   MOISTURE_ALL_ERR_ENABLED
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_CFG
 * -------------------------------------------
 *   MOISTURE_REG_CFG_DEFAULT_SETTINGS
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_MUX_CFG
 * -------------------------------------------
 *   MOISTURE_INPUT_DEGLITCH_FILT_BWDTH_33MHZ
 * </pre>
 *
 */
void moisture_default_cfg ( moisture_t *ctx );

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
void moisture_generic_write ( moisture_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void moisture_generic_read ( moisture_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write word function
 *
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written.
 * @param data_in      Data which will be written in the register.
 *
 * @description This function writes word to the desired register.
 */
void moisture_write_word ( moisture_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Read word function
 *
 * @param ctx          Click object.
 * @param reg          Register which will be read.
 * @retval result      Two byte data which is read from the register.
 *
 * @description This function reads one word from the desired register.
 */
uint16_t moisture_read_word ( moisture_t *ctx, uint8_t reg );

/**
 * @brief Soft reset function
 *
 * @param ctx          Click object.
 *
 * @description This function performs soft reset.
 */
void moisture_soft_reset ( moisture_t *ctx );

/**
 * @brief Configure device function
 *
 * @param ctx          Click object.
 * @param gain         Select moisture gain data.
 * @param offset       Select offset data.
 * @param clk_div      Select clock divider.
 *
 * @description Functions is used to configure moisture gain, offset and clock divider.
  <pre>
 *   MOISTURE_REG_RESET_DEV
 * -------------------------------------------
 *   gain
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_SETTLE_CNT
 * -------------------------------------------
 *   MOISTURE_SETTLE_CNT_CFG_DEFAULT
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_RCNT
 * -------------------------------------------
 *   MOISTURE_RCNT_CFG_DEFAULT
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_OFFSET
 * -------------------------------------------
 *   offset
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_CLOCK_DIVIDERS
 * -------------------------------------------
 *   MOISTURE_COMBINED_VAL_CH0_DIV
 *   clk_div
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_DRIVE_CURR
 * -------------------------------------------
 *   MOISTURE_DRIVE_CURR_CH0
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_ERR_CFG
 * -------------------------------------------
 *   MOISTURE_ALL_ERR_ENABLED
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_CFG
 * -------------------------------------------
 *   MOISTURE_REG_CFG_DEFAULT_SETTINGS
 * </pre>
 *
 * <pre>
 *   MOISTURE_REG_MUX_CFG
 * -------------------------------------------
 *   MOISTURE_INPUT_DEGLITCH_FILT_BWDTH_33MHZ
 * </pre>
 */
void  moisture_cfg( moisture_t *ctx, uint16_t gain, uint16_t offset, uint16_t clk_div );

/**
 * @brief Measurement data function
 *
 * @param ctx          Click object.
 * @retval moisture    Data in percent.
 *
 * @description Functions is used to measure moisture.
 * @note Moisture data depends on the set gain, offset and clock divider.
 */
uint8_t moisture_get_data ( moisture_t *ctx );

/**
 * @brief Chip calibration function
 *
 * @param ctx          Click object.
 *
 * @description Functions is used to calibrate the device.
 * @note Don't touch the sensor while calibrating!
 */
void moisture_cal ( moisture_t *ctx );

/**
 * @brief Soft reset function
 *
 * @param ctx          Click object.
 * @retval state   0 - no interrupt  / 1 - interrupt has occured.
 *
 * @description This function checks if interrupt has occured.
 */
uint8_t moisture_check_interrupt ( moisture_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MOISTURE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

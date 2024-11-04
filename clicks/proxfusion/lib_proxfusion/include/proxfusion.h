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
 * \brief This file contains API for ProxFusion Click driver.
 *
 * \addtogroup proxfusion ProxFusion Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXFUSION_H
#define PROXFUSION_H

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
#define PROXFUSION_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXFUSION_OK                           0
#define PROXFUSION_ERROR                       -1
/** \} */

/**
 * \defgroup info_data Device information data
 * \{
 */
#define PROXFUSION_REG_PR_NUMBER                0x00
#define PROXFUSION_REG_SW_NUMBER                0x01
#define PROXFUSION_REG_HW_NUMBER                0x02
/** \} */

/**
 * \defgroup product_number Read variants Product number
 * \{
 */
#define PROXFUSION_PR_OK                        0x41
#define PROXFUSION_SW_IQS620_OK                 0x04
#define PROXFUSION_SW_IQS620A_OK                0x08
#define PROXFUSION_HW_OK                        0x82
/** \} */

/**
 * \defgroup flag_register Flag register
 * \{
 */
#define PROXFUSION_FREG_SYSTEM                  0x10
#define PROXFUSION_FREG_GLOBAL_EVENTS           0x11
#define PROXFUSION_FREG_UI                      0x12
#define PROXFUSION_FREG_SAR_HYSTERESIS_UI       0x13
#define PROXFUSION_FREG_HALL_EFFECT_UI          0x16
/** \} */

/**
 * \defgroup channel_counts Channel counts
 * \{
 */
#define PROXFUSION_REG_CH_0_LSB                 0x20
#define PROXFUSION_REG_CH_0_MSB                 0x21
#define PROXFUSION_REG_CH_1_LSB                 0x22
#define PROXFUSION_REG_CH_1_MSB                 0x23
#define PROXFUSION_REG_CH_2_LSB                 0x24
#define PROXFUSION_REG_CH_2_MSB                 0x25
#define PROXFUSION_REG_CH_3_LSB                 0x26
#define PROXFUSION_REG_CH_3_MSB                 0x27
#define PROXFUSION_REG_CH_4_LSB                 0x28
#define PROXFUSION_REG_CH_4_MSB                 0x29
#define PROXFUSION_REG_CH_5_LSB                 0x2A
#define PROXFUSION_REG_CH_5_MSB                 0x2B
/** \} */

/**
 * \defgroup lta_values LTA values (Filtered data)
 * \{
 */
#define PROXFUSION_REG_LTA_CH_0_LSB             0x30
#define PROXFUSION_REG_LTA_CH_0_MSB             0x31
#define PROXFUSION_REG_LTA_CH_1_LSB             0x32
#define PROXFUSION_REG_LTA_CH_1_MSB             0x33
#define PROXFUSION_REG_LTA_CH_2_LSB             0x34
#define PROXFUSION_REG_LTA_CH_2_MSB             0x35
/** \} */

/**
 * \defgroup block_0 ProxFusion sensor settings block 0
 * \{
 */
#define PROXFUSION_REG_SETTINGS_0_0             0x40
#define PROXFUSION_REG_SETTINGS_0_1             0x41
#define PROXFUSION_REG_SETTINGS_0_2             0x42
#define PROXFUSION_REG_SETTINGS_1_0             0x43
#define PROXFUSION_REG_SETTINGS_1_1             0x44
#define PROXFUSION_REG_SETTINGS_1_2             0x45
#define PROXFUSION_REG_SETTINGS_2_0             0x46
#define PROXFUSION_REG_SETTINGS_2_1             0x47
#define PROXFUSION_REG_SETTINGS_2_2             0x48
#define PROXFUSION_REG_SETTINGS_3_0             0x49
#define PROXFUSION_REG_SETTINGS_3_1             0x4A
#define PROXFUSION_REG_SETTINGS_3_2             0x4B
/** \} */

/**
 * \defgroup block_1 ProxFusion sensor settings block 1
 * \{
 */
#define PROXFUSION_REG_SETTINGS_4               0x50
#define PROXFUSION_REG_SETTINGS_5               0x51
#define PROXFUSION_REG_COMPENSATION_CH_0        0x52
#define PROXFUSION_REG_COMPENSATION_CH_1        0x53
#define PROXFUSION_REG_COMPENSATION_CH_2        0x54
#define PROXFUSION_REG_MULTIPLIERS_CH_0         0x55
#define PROXFUSION_REG_MULTIPLIERS_CH_1         0x56
#define PROXFUSION_REG_MULTIPLIERS_CH_2         0x57
/** \} */

/**
 * \defgroup ui_settings ProxFusion UI settings
 * \{
 */
#define PROXFUSION_REG_PROX_CH_0                0x60
#define PROXFUSION_REG_TOUCH_CH_0               0x61
#define PROXFUSION_REG_PROX_CH_1                0x62
#define PROXFUSION_REG_TOUCH_CH_1               0x63
#define PROXFUSION_REG_PROX_CH_2                0x64
#define PROXFUSION_REG_TOUCH_CH_2               0x65
#define PROXFUSION_REG_UI_HALY_TIME             0x66
/** \} */

/**
 * \defgroup sar_ui_settings SAR UI settings
 * \{
 */
#define PROXFUSION_REG_SAR_SETTINGS_CH0         0x70
#define PROXFUSION_REG_SAR_SETTINGS_CH1         0x71
#define PROXFUSION_REG_QRD_THRESHOLD            0x72
#define PROXFUSION_REG_FILTER_HALT_THRESHOLD    0x73
#define PROXFUSION_REG_PROX_THRESHOLD           0x74
/** \} */

/**
 * \defgroup hys_ui_settings Hysteresis UI settings
 * \{
 */
#define PROXFUSION_REG_HYS_UI_SETTINGS          0x80
#define PROXFUSION_REG_HYS_FILTER_THRESHOLD     0x81
#define PROXFUSION_REG_HYS_PROX_THRESHOLD       0x82
#define PROXFUSION_REG_HYS_TOUCH_THRESHOLD      0x83
/** \} */

/**
 * \defgroup  hall_sensor_set Hall-effect sensor settings
 * \{
 */
#define PROXFUSION_REG_HALL_SETTINGS_0          0x90
#define PROXFUSION_REG_HALL_SETTINGS_1          0x91
#define PROXFUSION_REG_HALL_COMPENSATION_4_5    0x92
#define PROXFUSION_REG_HALL_MULTIPLIERS_4_5     0x93
/** \} */

/**
 * \defgroup  hall_sw_ui_set Hall-effect switch UI settings
 * \{
 */
#define PROXFUSION_REG_HALL_SWITCH_UI           0xA0
#define PROXFUSION_REG_HALL_SWITCH_PROX         0xA1
#define PROXFUSION_REG_HALL_SWITCH_TOUCH        0xA2
/** \} */

/**
 * \defgroup  i2c_settings I2C settings
 * \{
 */
#define PROXFUSION_REG_I2C_SETTINGS             0xDA
/** \} */

/**
 * \defgroup  system_settings System settings
 * \{
 */
#define PROXFUSION_SYSTEM_RESET                 ( 0x02 << 6 )
#define PROXFUSION_SYSTEM_ATI_RESET             ( 0x02 )
#define PROXFUSION_EVENT_MODE_0                 ( 0x00 << 5 )
#define PROXFUSION_EVENT_MODE_1                 ( 0x01 << 5 )
#define PROXFUSION_CLOCK_16MHz                  ( 0x00 << 4 )
#define PROXFUSION_CLOCK_4MHz                   ( 0x01 << 4 )
#define PROXFUSION_ATI_DESABLED                 ( 0x00 << 3 )
#define PROXFUSION_ATI_ENABLED                  ( 0x01 << 3 )
#define PROXFUSION_ATI_BAND_1_8                 ( 0x00 << 3 )
#define PROXFUSION_ATI_BAND_1_16                ( 0x01 << 3 )
/** \} */

/**
 * \defgroup event_mask Event mask
 * \{
 */
#define PROXFUSION_MASK_SAR_ACTIVE              0x80
#define PROXFUSION_MASK_PMU_EVENT               0x40
#define PROXFUSION_MASK_SYS_EVENT               0x20
#define PROXFUSION_MASK_TEMP_EVENT              0x10
#define PROXFUSION_MASK_HYSTERESIS_EVENT        0x08
#define PROXFUSION_MASK_HALL_EVENT              0x04
#define PROXFUSION_MASK_SAR_EVENT               0x02
#define PROXFUSION_MASK_PROX_SENSE_EVENT        0x01
/** \} */

/**
 * \defgroup slave_address Device slave address
 * \{
 */
#define PROXFUSION_SLAVE_ADDRESS                0x44
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

} proxfusion_t;

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

} proxfusion_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void proxfusion_cfg_setup ( proxfusion_cfg_t *cfg );

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
err_t proxfusion_init ( proxfusion_t *ctx, proxfusion_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function executes default configuration for ProxFusion Click.
 *
 * @note Default configuration of the chip contains the settings :
 *      Sysyem register:
 *         - PROXFUSION_SYSTEM_RESET
 *         - PROXFUSION_EVENT_MODE_1
 *         - PROXFUSION_CLOCK_16MHz
 *         - PROXFUSION_ATI_ENABLED
 *         - PROXFUSION_ATI_BAND_1_16
 *         - PROXFUSION_SYSTEM_ATI_RESET
 *      Event register:
 *          - PROXFUSION_MASK_SYS_EVENT
 *
 */
err_t proxfusion_default_cfg ( proxfusion_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buffer  Output data buffer
 * @param len          Number of the bytes to be read
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t proxfusion_generic_write ( proxfusion_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buffer  Data buffer to be written.
 * @param len          Number of the bytes in data buffer.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function reads data from the desired register.
 */
err_t proxfusion_generic_read ( proxfusion_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len );

/**
 * @brief Touch event
 *
 * @param ctx      Click object.
 *
 * @return Current touch event ( rignt, left or both )
 */
uint8_t proxfusion_get_touch ( proxfusion_t *ctx );

/**
 * @brief Sets system register
 *
 * @param ctx      Click object.
 * @param cfg      System register configuration
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Configuration data (value) consists of multiple settings:
 *    - Software Reset and ACK Reset set on 1 (default),
 *    - Event mode enable,
 *    - Main Clock frequency selection,
 *    - Communications during ATI,
 *    - Re-ATI Band selection,
 *    - Redo ATI on all channels set on 1 (default)
 *    - Reseed all Long-term filters set on 1 (default).
 */
err_t proxfusion_set_system_reg ( proxfusion_t *ctx, uint8_t cfg );

/**
 * @brief Selecting events
 *
 * @param ctx      Click object.
 * @param cfg      Event register configuration
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Selection options:
 *          - SAR activation state,
 *          - Power management unit event,
 *          - System event,
 *          - Temperature event,
 *          - Hysteresis UI event,
 *          - Hall-effect event,
 *          - SAR event and
 *          - ProxSense event.
 */
err_t proxfusion_set_event_reg ( proxfusion_t *ctx, uint8_t cfg );

#ifdef __cplusplus
}
#endif
#endif  // _PROXFUSION_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

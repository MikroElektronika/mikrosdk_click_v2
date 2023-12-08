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
 * \brief This file contains API for Charger 8 Click driver.
 *
 * \addtogroup charger8 Charger 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CHARGER8_H
#define CHARGER8_H

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
 * \defgroup f_addr_regs Firs Address Register
 * \{
 */
#define CHARGER8_M5REG_STATUS             0x00
#define CHARGER8_M5REG_VALRTTH            0x01
#define CHARGER8_M5REG_TALRTTH            0x02
#define CHARGER8_M5REG_SALRTTH            0x03
#define CHARGER8_M5REG_ATRATE             0x04
#define CHARGER8_M5REG_REP_CAP            0x05
#define CHARGER8_M5REG_REP_SOC            0x06
#define CHARGER8_M5REG_AGE                0x07
#define CHARGER8_M5REG_TEMPERATURE        0x08
#define CHARGER8_M5REG_VCELL              0x09
#define CHARGER8_M5REG_CURRENT            0x0A
#define CHARGER8_M5REG_AVE_CURRENT        0x0B
#define CHARGER8_M5REG_QRESIDUAL          0x0C
#define CHARGER8_M5REG_MIX_SOC            0x0D
#define CHARGER8_M5REG_AV_SOC             0x0E
#define CHARGER8_M5REG_MIX_CAP            0x0F
#define CHARGER8_M5REG_FULL_CAP           0x10
#define CHARGER8_M5REG_TIME_TO_EMPTY      0x11
#define CHARGER8_M5REG_QRTABLE00          0x12
#define CHARGER8_M5REG_FULL_SOC_THR       0x13
#define CHARGER8_M5REG_RCALL              0x14
#define CHARGER8_M5REG_RFAST              0x15
#define CHARGER8_M5REG_AVG_TA             0x16
#define CHARGER8_M5REG_BATTERY_CYCLES     0x17
#define CHARGER8_M5REG_DESIGN_CAP         0x18
#define CHARGER8_M5REG_AVG_VCALL          0x19
#define CHARGER8_M5REG_MAX_MIN_TEMP       0x1A
#define CHARGER8_M5REG_MAX_MIN_VOLT       0x1B
#define CHARGER8_M5REG_MAX_MIN_CURRENT    0x1C
#define CHARGER8_M5REG_CONFIG             0x1D
#define CHARGER8_M5REG_ICHGTERM           0x1E
#define CHARGER8_M5REG_AV_CAP             0x1F
#define CHARGER8_M5REG_TIME_TO_FULL       0x20
#define CHARGER8_M5REG_DEVICE_NAME        0x21
#define CHARGER8_M5REG_QRTABLE10          0x22
#define CHARGER8_M5REG_FULL_CAP_NOM       0x23
#define CHARGER8_M5REG_AIN0               0x27
#define CHARGER8_M5REG_LEARN_CFG          0x28
#define CHARGER8_M5REG_FILTER_CFG         0x29
#define CHARGER8_M5REG_RELAX_CFG          0x2A
#define CHARGER8_M5REG_MISC_CFG           0x2B
#define CHARGER8_M5REG_T_GAIN             0x2C
#define CHARGER8_M5REG_T_OFF              0x2D
#define CHARGER8_M5REG_C_GAIN             0x2E
#define CHARGER8_M5REG_C_OFF              0x2F
#define CHARGER8_M5REG_QRTABLE20          0x32
#define CHARGER8_M5REG_FULL_CAP_REP       0x35
#define CHARGER8_M5REG_IAVG_EMPTY         0x36
#define CHARGER8_M5REG_RCOMP0             0x38
#define CHARGER8_M5REG_TEMPCO             0x39
#define CHARGER8_M5REG_V_EMPTY            0x3A
#define CHARGER8_M5REG_FSTAT              0x3D
#define CHARGER8_M5REG_TIMER              0x3E
#define CHARGER8_M5REG_SHDN_TIMER         0x3F
#define CHARGER8_M5REG_QRTABLE30          0x42
#define CHARGER8_M5REG_DQACC              0x45
#define CHARGER8_M5REG_DPACC              0x46
#define CHARGER8_M5REG_VF_REM_CAP         0x4A
#define CHARGER8_M5REG_QH                 0x4D
#define CHARGER8_M5REG_STATUS_2           0xB0
#define CHARGER8_M5REG_IALRTTH            0xB4
#define CHARGER8_M5REG_VSHDN_CFG          0xB8
#define CHARGER8_M5REG_AGE_FORECAST       0xB9
#define CHARGER8_M5REG_HIB_CFG            0xBA
#define CHARGER8_M5REG_CONFIG_2           0xBB
#define CHARGER8_M5REG_VRIPPLE            0xBC
#define CHARGER8_M5REG_PACK_CFG           0xBD
#define CHARGER8_M5REG_TIMER_H            0xBE
#define CHARGER8_M5REG_AVG_CELL_4         0xD1
#define CHARGER8_M5REG_AVG_CELL_3         0xD2
#define CHARGER8_M5REG_AVG_CELL_2         0xD3
#define CHARGER8_M5REG_AVG_CELL_1         0xD4
#define CHARGER8_M5REG_CELL_4             0xD5
#define CHARGER8_M5REG_CELL_3             0xD6
#define CHARGER8_M5REG_CELL_2             0xD7
#define CHARGER8_M5REG_CELL_1             0xD8
#define CHARGER8_M5REG_CELL_X             0xD9
#define CHARGER8_M5REG_BATTERY_VOLTAGE    0xDA
#define CHARGER8_M5REG_ATQ_RESIDUAL       0xDC
#define CHARGER8_M5REG_AT_TTE             0xDD
#define CHARGER8_M5REG_ATAV_SOC           0xDE
#define CHARGER8_M5REG_ATAV_CAP           0xDF
/** \} */

/**
 * \defgroup nv_addr_regs NV Address Registers
 * \{
 */
#define CHARGER8_NVREG_X_TABLE0             0x80
#define CHARGER8_NVREG_X_TABLE1             0x81
#define CHARGER8_NVREG_X_TABLE2             0x82
#define CHARGER8_NVREG_X_TABLE3             0x83
#define CHARGER8_NVREG_X_TABLE4             0x84
#define CHARGER8_NVREG_X_TABLE5             0x85
#define CHARGER8_NVREG_X_TABLE6             0x86
#define CHARGER8_NVREG_X_TABLE7             0x87
#define CHARGER8_NVREG_X_TABLE8             0x88
#define CHARGER8_NVREG_X_TABLE9             0x89
#define CHARGER8_NVREG_X_TABLE10            0x8A
#define CHARGER8_NVREG_X_TABLE11            0x8B
#define CHARGER8_NVREG_USER_18C             0x8C
#define CHARGER8_NVREG_USER_18D             0x8D
#define CHARGER8_NVREG_ODSCTH               0x8E
#define CHARGER8_NVREG_ODSCCFG              0x8F
#define CHARGER8_NVREG_OCV_TABLE0           0x90
#define CHARGER8_NVREG_OCV_TABLE1           0x91
#define CHARGER8_NVREG_OCV_TABLE2           0x92
#define CHARGER8_NVREG_OCV_TABLE3           0x93
#define CHARGER8_NVREG_OCV_TABLE4           0x94
#define CHARGER8_NVREG_OCV_TABLE5           0x95
#define CHARGER8_NVREG_OCV_TABLE6           0x96
#define CHARGER8_NVREG_OCV_TABLE7           0x97
#define CHARGER8_NVREG_OCV_TABLE8           0x98
#define CHARGER8_NVREG_OCV_TABLE9           0x99
#define CHARGER8_NVREG_OCV_TABLE10          0x9A
#define CHARGER8_NVREG_OCV_TABLE11          0x9B
#define CHARGER8_NVREG_ICHG_TERM            0x9C
#define CHARGER8_NVREG_FILTER_CFG           0x9D
#define CHARGER8_NVREG_V_EMPTY              0x9E
#define CHARGER8_NVREG_LEARN_CFG            0x9F
#define CHARGER8_NVREG_QR_TABLE00           0xA0
#define CHARGER8_NVREG_QR_TABLE10           0xA1
#define CHARGER8_NVREG_QR_TABLE20           0xA2
#define CHARGER8_NVREG_QR_TABLE30           0xA3
#define CHARGER8_NVREG_CYCLES               0xA4
#define CHARGER8_NVREG_FULL_CAP_NOM         0xA5
#define CHARGER8_NVREG_R_COMP_0             0xA6
#define CHARGER8_NVREG_TEMP_CO              0xA7
#define CHARGER8_NVREG_IAVG_EMPTY           0xA8
#define CHARGER8_NVREG_FULL_CAP_REP         0xA9
#define CHARGER8_NVREG_VOLT_TEMP            0xAA
#define CHARGER8_NVREG_MIN_MAX_CURRENT      0xAB
#define CHARGER8_NVREG_MIN_MAX_VOLT         0xAC
#define CHARGER8_NVREG_MIN_MAX_TEMP         0xAD
#define CHARGER8_NVREG_SOC                  0xAE
#define CHARGER8_NVREG_TIMER_H              0xAF
#define CHARGER8_NVREG_CONFIG               0xB0
#define CHARGER8_NVREG_RIPPLE_CFG           0xB1
#define CHARGER8_NVREG_MISC_CFG             0xB2
#define CHARGER8_NVREG_DESIGN_CFG           0xB3
#define CHARGER8_NVREG_HIB_CFG              0xB4
#define CHARGER8_NVREG_PACK_CFG             0xB5
#define CHARGER8_NVREG_RELAX_CFG            0xB6
#define CHARGER8_NVREG_CONVG_CFG            0xB7
#define CHARGER8_NVREG_NV_CONFIG_0          0xB8
#define CHARGER8_NVREG_NV_CONFIG_1          0xB9
#define CHARGER8_NVREG_NV_CONFIG_2          0xBA
#define CHARGER8_NVREG_SBS_CFG              0xBB
#define CHARGER8_NVREG_ROM_ID_0             0xBC
#define CHARGER8_NVREG_ROM_ID_1             0xBD
#define CHARGER8_NVREG_ROM_ID_2             0xBE
#define CHARGER8_NVREG_ROM_ID_3             0xBF
#define CHARGER8_NVREG_V_ALRT_TH            0xC0
#define CHARGER8_NVREG_T_ALRT_TH            0xC1
#define CHARGER8_NVREG_S_ALRT_TH            0xC2
#define CHARGER8_NVREG_I_ALRT_TH            0xC3
#define CHARGER8_NVREG_USER_1C4             0xC4
#define CHARGER8_NVREG_USER_1C5             0xC5
#define CHARGER8_NVREG_FULL_SOC_THR         0xC6
#define CHARGER8_NVREG_TTF_CFG              0xC7
#define CHARGER8_NVREG_C_GAIN               0xC8
#define CHARGER8_NVREG_T_CURVE              0xC9
#define CHARGER8_NVREG_T_GAIN               0xCA
#define CHARGER8_NVREG_T_OFF                0xCB
#define CHARGER8_NVREG_MANIFCTURE_NAME_0    0xCC
#define CHARGER8_NVREG_MANIFCTURE_NAME_1    0xCD
#define CHARGER8_NVREG_MANIFCTURE_NAME_2    0xCE
#define CHARGER8_NVREG_R_SENSE              0xCF
#define CHARGER8_NVREG_USER_1D0             0xD0
#define CHARGER8_NVREG_USER_1D1             0xD1
#define CHARGER8_NVREG_AGE_FC_CFG           0xD2
#define CHARGER8_NVREG_DESIGN_VOLTAGE       0xD3
#define CHARGER8_NVREG_USER_1D4             0xD4
#define CHARGER8_NVREG_R_FAST_V_SHDN        0xD5
#define CHARGER8_NVREG_MANIFACTURE_DATE     0xD6
#define CHARGER8_NVREG_FIRST_USED           0xD7
#define CHARGER8_NVREG_SERIAL_NUMBER_0      0xD8
#define CHARGER8_NVREG_SERIAL_NUMBER_1      0xD9
#define CHARGER8_NVREG_SERIAL_NUMBER_2      0xDA
#define CHARGER8_NVREG_DEVICE_NUMBER_0      0xDB
#define CHARGER8_NVREG_DEVICE_NUMBER_1      0xDC
#define CHARGER8_NVREG_DEVICE_NUMBER_2      0xDD
#define CHARGER8_NVREG_DEVICE_NUMBER_3      0xDE
#define CHARGER8_NVREG_DEVICE_NUMBER_4      0xDF
/** \} */

/**
 * \defgroup cmds Commands
 * \{
 */
#define CHARGER8_COMMAND                    0x60
#define CHARGER8_CMD_COPY_NV_BLOCK_MSB      0xE9
#define CHARGER8_CMD_NV_RECALL_MSB          0xE0
#define CHARGER8_CMD_NV_RECALL_LSB          0x01
/** \} */

/**
 * \defgroup enable/disable_charger Enable / Disable charger
 * \{
 */
#define CHARGER8_CHARGER_ENABLE    0x00
#define CHARGER8_CHARGER_DISABLE   0x01
/** \} */

/**
 * \defgroup alert Alert
 * \{
 */
#define CHARGER8_ALERT_ENABLE    0x01
#define CHARGER8_ALERT_DISABLE   0x00
/** \} */

/**
 * \defgroup usb_suspand USB SUSPAND
 */
#define CHARGER8_USB_SUSPAND_MODE_ENABLE     0x01
#define CHARGER8_USB_SUSPAND_MODE_DISABLE    0x00
/** \} */

/**
 * \defgroup Slave Address
 * \{
 */
#define CHARGER8_DEVICE_SLAVE_ADDRESS       0x36
#define CHARGER8_DEVICE_NV_SLAVE_ADDRESS    0x0B
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CHARGER8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.dok = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.alt = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.us = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CHARGER8_RETVAL  uint8_t

#define CHARGER8_OK           0x00
#define CHARGER8_INIT_ERROR   0xFF
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

    digital_out_t dok;
    digital_out_t alt;
    digital_out_t en;
    digital_out_t us;

    // Input pins 

    digital_in_t flt;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint8_t nv_slave_address;
    uint16_t max_bat_capacity;

} charger8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t dok;
    pin_name_t alt;
    pin_name_t en;
    pin_name_t us;
    pin_name_t flt;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint8_t i2c_nv_address;

} charger8_cfg_t;

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
void charger8_cfg_setup ( charger8_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param charger8 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CHARGER8_RETVAL charger8_init ( charger8_t *ctx, charger8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Charger8 click.
 */
void charger8_default_cfg ( charger8_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_wr     Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void charger8_generic_write ( charger8_t *ctx, uint8_t reg, uint16_t data_wr );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * 
 * @retval read data
 *
 * @description This function reads data from the desired register.
 */
uint16_t charger8_generic_read ( charger8_t *ctx, uint8_t reg );

/**
 * @brief Functions for enable or disable device
 *
 * @param ctx             Click object.
 * @param[in] enable      Enable or Disable device
 *
 * @description Use this function when enable or disable device.
 */
void charger8_enable ( charger8_t *ctx, uint8_t enable );

/**
 * @brief Functions for read Temperature of the chip
 *
 * @retval Temperature of the chip (data in [C])
 *
 * @param ctx             Click object.
 *
 * @description Use this function when read temperature of the chip.
 */
float charger8_get_temperature ( charger8_t *ctx );

/**
 * @brief Functions for reading the current charging battery
 *
 * @retval Current data in [mA]
 *
 * @param ctx             Click object.
 *
 * @description Use this function when read current.
 */
float charger8_get_current ( charger8_t *ctx );

/**
 * @brief Functions for reading the voltage of the battery
 *
 * @retval Voltage of the battery in [mV]
 *
 * @param ctx             Click object.
 *
 * @description Use this function when read voltage of the battery.
 */
float charger8_get_voltage ( charger8_t *ctx );

/**
 * @brief Function for reads the percentage of the battery charge
 *
 * @retval Percentage of battery charge
 *
 * @param ctx             Click object.
 *
 * @description Use this function when reading pecentage of the battery charge.
 */
uint8_t charger8_get_soc ( charger8_t *ctx );

/**
 * @brief Function for reads the current capacity of the battery
 *
 * @retval Current capacity of the battery in [mAh]
 *
 * @param ctx             Click object.
 *
 * @description To get the correct current battery capacity, 
 * it is necessary to set the maximum capacity of the battery beforehand.
 */
uint16_t charger8_get_capacity ( charger8_t *ctx );

/**
 * @brief Function for reads the Time to Empty data
 *
 * @retval Time to empty data in [s]
 *
 * @param ctx             Click object.
 *
 * @descritpion Use this function to read Time until empty data.
 */
float charger8_get_time_to_empty ( charger8_t *ctx );

/**
 * @brief Function for reads the Time to Full data
 *
 * @retval Time to full data im [s]
 *
 * @param ctx             Click object.
 *
 * @descritpion Use this function to read Time until Full data.
 */
float charger8_get_time_to_full ( charger8_t *ctx );

/**
 * @brief Function for reads the Status register
 *
 * @retval data read from the status register
 *
 * @param ctx             Click object.
 *
 * @description Use this function to read the Status register.
 *
 */
uint16_t charger8_get_status ( charger8_t *ctx );

/**
 * @brief General reset procedure
 *
 * @param ctx             Click object.
 *
 * @description Use this function for general reset.
 *
 */
void charger8_reset ( charger8_t *ctx );

/**
 * @brief Function for reads FAULT pin state
 *
 * @retval FAULT pin state
 *
 * @param ctx             Click object.
 *
 * @description Use this function to read FAULT pin state.
 */
uint8_t charger8_get_fault_output ( charger8_t *ctx );

/**
 * @brief Function for set USB Suspand pin
 *
 * @param[in] mode  USB Suspand mode (enable or disable)
 *
 * @param ctx             Click object.
 *
 * @description Use this function to set USB Suspand pin.
 *
 */
void charger8_set_usb_suspend ( charger8_t *ctx, uint8_t mode );

/**
 * @brief Function for set Alert pin state
 *
 * @param[in] state  Alert mode (enable or disable)
 *
 * @param ctx             Click object.
 *
 * @description Use this function to set Alert pin state.
 */
void charger8_set_alert ( charger8_t *ctx, uint8_t state );

/**
 * @brief Function for reads DC power pin state
 *
 * @retval DC Power OK pin state
 *
 * @param ctx             Click object.
 *
 * @description Use this function to read DC power pin state.
 */
uint8_t charger8_get_dc_power_ok ( charger8_t *ctx );

/**
 * @brief Function for set Max battery capacity in [mAh]
 *
 * @param ctx             Click object.
 * @param capacity  Max battery capacity in [mAh]
 *
 * @description Use this function to set Max battery capacity in [mAh] 
 */
void charger8_set_max_battery_capacity ( charger8_t *ctx, uint16_t capacity );

                                                                       /** @} */
#ifdef __cplusplus
}
#endif
#endif  // _CHARGER8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

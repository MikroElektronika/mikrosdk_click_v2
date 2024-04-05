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
 * \brief This file contains API for VCP Monitor 2 Click driver.
 *
 * \addtogroup vcpmonitor2 VCP Monitor 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VCPMONITOR2_H
#define VCPMONITOR2_H

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
#define VCPMONITOR2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VCPMONITOR2_RETVAL  uint8_t

#define VCPMONITOR2_OK           0x00
#define VCPMONITOR2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup DAVICE SLAVE ADDRESS
 * \{
 */
#define VCPMONITOR2_DEVICE_SLAVE_ADDR_GND        0x40
#define VCPMONITOR2_DEVICE_SLAVE_ADDR_VCC        0x41
#define VCPMONITOR2_DEVICE_SLAVE_ADDR_SCL        0x42
#define VCPMONITOR2_DEVICE_SLAVE_ADDR_SDA        0x43
/** \} */

/**
 * \defgroup STATUS SLAVE ADDRESS
 * \{
 */
#define VCPMONITOR2_STATUS_ADDR_GND_GND          0x70
#define VCPMONITOR2_STATUS_ADDR_VCC_GND          0x72
#define VCPMONITOR2_STATUS_ADDR_GND_VCC          0x71
#define VCPMONITOR2_STATUS_ADDR_VCC_VCC          0x73
/** \} */

/**
 * \defgroup STATUS INPUT CONFIGURATION
 * \{
 */
#define VCPMONITOR2_ALERT_REG_INPUT            0x00
#define VCPMONITOR2_ALERT_REG_POLARITY         0x02
#define VCPMONITOR2_ALERT_REG_CONFIG           0x03
/** \} */

/**
 * \defgroup REGISTERS
 * \{
 */
#define VCPMONITOR2_REG_CONFIGURATION              0x00
#define VCPMONITOR2_REG_CH_1_SHUNT_VOLT            0x01
#define VCPMONITOR2_REG_CH_1_BUS_VOLT              0x02
#define VCPMONITOR2_REG_CH_2_SHUNT_VOLT            0x03
#define VCPMONITOR2_REG_CH_2_BUS_VOLT              0x04
#define VCPMONITOR2_REG_CH_3_SHUNT_VOLT            0x05
#define VCPMONITOR2_REG_CH_3_BUS_VOLT              0x06
#define VCPMONITOR2_REG_CH_1_CRITICAL_ALT          0x07
#define VCPMONITOR2_REG_CH_1_WARNING_ALT           0x08
#define VCPMONITOR2_REG_CH_2_CRITICAL_ALT          0x09
#define VCPMONITOR2_REG_CH_2_WARNING_ALT           0x0A
#define VCPMONITOR2_REG_CH_3_CRITICAL_ALT          0x0B
#define VCPMONITOR2_REG_CH_3_WARNING_ALT           0x0C
#define VCPMONITOR2_REG_SHUNT_VOLT_SUM             0x0D
#define VCPMONITOR2_REG_SHUNT_VOLT_SUM_LIMIT       0x0E
#define VCPMONITOR2_REG_MASK_ENABLE                0x0F
#define VCPMONITOR2_REG_PWR_UPPER_LIMIT            0x10
#define VCPMONITOR2_REG_PWR_LOWER_LIMIT            0x11
#define VCPMONITOR2_REG_MANUFACTURER_ID            0xFE
#define VCPMONITOR2_REG_DIE_ID                     0xFF
/** \} */

/**
 * \defgroup DEFAULT VALUE AFTER THE RESET
 * \{
 */
#define VCPMONITOR2_DEF_MANUFACTURE_ID             0x5449
#define VCPMONITOR2_DEF_DIE_ID                     0x3220
#define VCPMONITOR2_DEF_PWR_LOWER_LIMIT            0x2328
#define VCPMONITOR2_DEF_PWR_UPPER_LIMIT            0x2F10
#define VCPMONITOR2_DEF_MASK_ENABLE                0x0002
#define VCPMONITOR2_DEF_SHUNT_VOLT_SUM_LIMIT       0x7FFE
#define VCPMONITOR2_DEF_CONFIGURATION              0x7127
#define VCPMONITOR2_DEF_CH_1234_ALERT              0x7FF8
/** \} */

/**
 * \defgroup CONFIGURATION REGISTER
 * \{
 */
#define VCPMONITOR2_CFG_SW_RESET                    0x8000
#define VCPMONITOR2_CFG_CH_1_ENABLE                 0x4000
#define VCPMONITOR2_CFG_CH_1_DISABLE                0x0000
#define VCPMONITOR2_CFG_CH_2_ENABLE                 0x2000
#define VCPMONITOR2_CFG_CH_2_DISABLE                0x0000
#define VCPMONITOR2_CFG_CH_3_ENABLE                 0x1000
#define VCPMONITOR2_CFG_CH_3_DISABLE                0x0000
#define VCPMONITOR2_CFG_AVG_1                       0x0000
#define VCPMONITOR2_CFG_AVG_4                       0x0200
#define VCPMONITOR2_CFG_AVG_16                      0x0400
#define VCPMONITOR2_CFG_AVG_64                      0x0600
#define VCPMONITOR2_CFG_AVG_128                     0x0800
#define VCPMONITOR2_CFG_AVG_256                     0x0A00
#define VCPMONITOR2_CFG_AVG_512                     0x0C00
#define VCPMONITOR2_CFG_AVG_1024                    0x0D00

#define VCPMONITOR2_CFG_VBUS_CT_140us               0x0000
#define VCPMONITOR2_CFG_VBUS_CT_204us               0x0040
#define VCPMONITOR2_CFG_VBUS_CT_332us               0x0080
#define VCPMONITOR2_CFG_VBUS_CT_588us               0x00C0
#define VCPMONITOR2_CFG_VBUS_CT_1100us              0x0100
#define VCPMONITOR2_CFG_VBUS_CT_2116us              0x0140
#define VCPMONITOR2_CFG_VBUS_CT_4156us              0x0180
#define VCPMONITOR2_CFG_VBUS_CT_8244us              0x01C0
#define VCPMONITOR2_CFG_VSH_CT_140us                0x0000
#define VCPMONITOR2_CFG_VSH_CT_204us                0x0008
#define VCPMONITOR2_CFG_VSH_CT_332us                0x0010
#define VCPMONITOR2_CFG_VSH_CT_588us                0x0018
#define VCPMONITOR2_CFG_VSH_CT_1100us               0x0020
#define VCPMONITOR2_CFG_VSH_CT_2116us               0x0028
#define VCPMONITOR2_CFG_VSH_CT_4156us               0x0030
#define VCPMONITOR2_CFG_VSH_CT_8244us               0x0038

#define VCPMONITOR2_CFG_MODE_POWER_DOWN             0x0000
#define VCPMONITOR2_CFG_MODE_SS_SHUNT_VOLT          0x0001
#define VCPMONITOR2_CFG_MODE_SS_BUS_VOLT            0x0002
#define VCPMONITOR2_CFG_MODE_SS_SHUNT_BUS_VOLT      0x0003
#define VCPMONITOR2_CFG_MODE_CONT_SHUNT_VOLT        0x0005
#define VCPMONITOR2_CFG_MODE_CONT_BUS_VOLT          0x0006
#define VCPMONITOR2_CFG_MODE_CONT_SHUNT_BUS_VOLT    0x0007
/** \} */

/**
 * \defgroup MASK ENABLE
 * \{
 */
#define VCPMONITOR2_CFG_MASK_SCC_1_ENABLE             0x4000
#define VCPMONITOR2_CFG_MASK_SCC_2_ENABLE             0x2000
#define VCPMONITOR2_CFG_MASK_SCC_3_ENABLE             0x1000
#define VCPMONITOR2_CFG_MASK_SCC_1_DISABLE            0x0000
#define VCPMONITOR2_CFG_MASK_SCC_2_DISABLE            0x0000
#define VCPMONITOR2_CFG_MASK_SCC_3_DISABLE            0x0000
#define VCPMONITOR2_CFG_MASK_WEN_TRANSPARENT          0x0000
#define VCPMONITOR2_CFG_MASK_WEN_LATCH_ENABLED        0x0800
#define VCPMONITOR2_CFG_MASK_CEN_TRANSPARENT          0x0000
#define VCPMONITOR2_CFG_MASK_CEN_LATCH_ENABLED        0x0400
#define VCPMONITOR2_CFG_MASK_CF_1_ENABLE              0x0080
#define VCPMONITOR2_CFG_MASK_CF_2_ENABLE              0x0100
#define VCPMONITOR2_CFG_MASK_CF_3_ENABLE              0x0200
#define VCPMONITOR2_CFG_MASK_CF_1_DISABLE             0x0000
#define VCPMONITOR2_CFG_MASK_CF_2_DISABLE             0x0000
#define VCPMONITOR2_CFG_MASK_CF_3_DISABLE             0x0000
#define VCPMONITOR2_CFG_MASK_SF_ENABLE                0x0040
#define VCPMONITOR2_CFG_MASK_SF_DISABLE               0x0000
#define VCPMONITOR2_CFG_MASK_VF_1_ENABLE              0x0008
#define VCPMONITOR2_CFG_MASK_VF_2_ENABLE              0x0010
#define VCPMONITOR2_CFG_MASK_VF_3_ENABLE              0x0020
#define VCPMONITOR2_CFG_MASK_VF_1_DISABLE             0x0000
#define VCPMONITOR2_CFG_MASK_VF_2_DISABLE             0x0000
#define VCPMONITOR2_CFG_MASK_VF_3_DISABLE             0x0000
#define VCPMONITOR2_CFG_MASK_PVF_ENABLE               0x0004
#define VCPMONITOR2_CFG_MASK_TCF_ENABLE               0x0002
#define VCPMONITOR2_CFG_MASK_CVRF_ENABLE              0x0001
#define VCPMONITOR2_CFG_MASK_PVF_DISABLE              0x0000
#define VCPMONITOR2_CFG_MASK_TCF_DISABLE              0x0000
#define VCPMONITOR2_CFG_MASK_CVRF_DISABLE             0x0000
/** \} */

/**
 * \defgroup CHANNEL
 * \{
 */
#define VCPMONITOR2_CHANNEL_1                          0x01
#define VCPMONITOR2_CHANNEL_2                          0x02
#define VCPMONITOR2_CHANNEL_3                          0x03
/** \} */

/**
 * \defgroup ALERT
 * \{
 */
#define VCPMONITOR2_ALERT_PVALID                       0x01
#define VCPMONITOR2_ALERT_WRNG                         0x02
#define VCPMONITOR2_ALERT_CRTCL                        0x04
#define VCPMONITOR2_ALERT_TCTRL                        0x08
/** \} */

#define DEVICE_OK 0
#define DEVICE_ERROR 1

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

    digital_out_t rst;
  
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t device_slave_address;
    uint8_t device_status_address;

} vcpmonitor2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;

    // static variable 

    uint32_t i2c_speed;
    uint8_t device_slave_address;
    uint8_t device_status_address;

} vcpmonitor2_cfg_t;

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
void vcpmonitor2_cfg_setup ( vcpmonitor2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VCPMONITOR2_RETVAL vcpmonitor2_init ( vcpmonitor2_t *ctx, vcpmonitor2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Vcpmonitor2 click.
 */
void vcpmonitor2_default_cfg ( vcpmonitor2_t *ctx );

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
void vcpmonitor2_generic_write ( vcpmonitor2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void vcpmonitor2_generic_read ( vcpmonitor2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get Manufacture ID.
 *
 * @param ctx          Click object.
 * 
 * @return Manufacture ID ( default 0x5449 )
 */
uint16_t vcpmonitor2_get_manifacture_id ( vcpmonitor2_t *ctx );

/**
 * @brief Get DIE ID.
 *
 * @param ctx          Click object.
 * 
 * @return DIE ID ( default 0x3220 )
 */
uint16_t vcpmonitor2_get_die_id ( vcpmonitor2_t *ctx );

/**
 * @brief Get BUS voltage in mV.
 *
 * @param ctx          Click object.
 * 
 * @param channel Channel ( 1 / 2 / 3 )
 * @return BUS voltage in mV
 */
float vcpmonitor2_get_bus_voltage ( vcpmonitor2_t *ctx, uint8_t channel );

/**
 * @brief Get Shunt voltage in mV
 *
 * @param ctx          Click object.
 * 
 * @param channel Channel ( 1 / 2 / 3 )
 * @return Shunt voltage in mV
 */
float vcpmonitor2_get_shunt_voltage ( vcpmonitor2_t *ctx, uint8_t channel );

/**
 * @brief Get Current data in mA
 *
 * @param ctx          Click object.
 * 
 * @param channel Channel ( 1 / 2 / 3 )
 * @return Current data in mA
 */
float vcpmonitor2_get_current ( vcpmonitor2_t *ctx, uint8_t channel );

/**
 * @brief Get Power in W
 *
 * @param ctx          Click object.
 * 
 * @param channel Channel ( 1 / 2 / 3 )
 * @return Power data in W
 */
float vcpmonitor2_get_power ( vcpmonitor2_t *ctx, uint8_t channel );

/**
 * @brief Configuration function
 *
 * @param ctx          Click object.
 * @param cfg   Config data for set
 * @note Config data options:
 * <pre>
 *   -- VBUS ( 140us, 204us, 332us, 588us, 1100us 2116us, 4156us, 8244us )
 *   -- VSH ( 140us, 204us, 332us, 588us, 1100us 2116us, 4156us, 8244us )
 *   -- MODE ( POWER_DOWN, SS_SHUNT_VOLT, SS_BUS_VOLT, CONT_SHUNT_VOLT,
 *             CONT_BUS_VOLT, CONT_SHUNT_BUS_VOLT )
 * </pre>
 */
void vcpmonitor2_configuration ( vcpmonitor2_t *ctx, uint16_t cfg );

/**
 * @brief Get Alert status
 *
 * @param ctx          Click object.
 * 
 * @return Alert Status ( PVALID, WRNG, CRTCL, TCTRL )
 */
uint8_t vcpmonitor2_get_alert_status ( vcpmonitor2_t *ctx );

/**
 * @brief  Alert reset
 * 
 * @param ctx          Click object.
 * 
 */
void vcpmonitor2_reset_alert ( vcpmonitor2_t *ctx );

/**
 * @brief Alert configuration ( Enable / Disable )
 *
 * @param ctx          Click object.
 * @param cfg Configuration data
 *
 * @note Options for enable or disable:
 * <pre>
 *   - PVALID ALERT
 *   - WRNG ALERT
 *   - CRTCL ALERT
 *   - TCTRL ALERT
 * </pre>
 */
void vcpmonitor2_alert_config ( vcpmonitor2_t *ctx, uint8_t cfg );

#ifdef __cplusplus
}
#endif
#endif  // _VCPMONITOR2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Ambient 6 Click driver.
 *
 * \addtogroup ambient6 Ambient 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT6_H
#define AMBIENT6_H

#include "drv_digital_out.h"
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
#define AMBIENT6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT6_RETVAL  uint8_t

#define AMBIENT6_OK           0x00
#define AMBIENT6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define AMBIENT6_CMD_CONFIGURATION             0x00
#define AMBIENT6_CMD_THRESHOLD_HIGH_SETTINGS   0x01
#define AMBIENT6_CMD_THRESHOLD_LOW_SETTINGS    0x02
#define AMBIENT6_CMD_MODE_SETTINGS             0x03
#define AMBIENT6_CMD_ALS_DATA                  0x04
#define AMBIENT6_CMD_WHITE_DATA                0x05
#define AMBIENT6_CMD_ALS_THRESHOLD_INTERRUPT   0x06
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define AMBIENT6_CFG_ALS_SENSITIVITY_X1       0x0000 << 11
#define AMBIENT6_CFG_ALS_SENSITIVITY_X2       0x0001 << 11
#define AMBIENT6_CFG_ALS_SENSITIVITY_X1_8     0x0002 << 11
#define AMBIENT6_CFG_ALS_SENSITIVITY_X1_4     0x0003 << 11
#define AMBIENT6_CFG_ALS_TIME_SETTING_25MS    0x000C << 6
#define AMBIENT6_CFG_ALS_TIME_SETTING_50MS    0x0008 << 6
#define AMBIENT6_CFG_ALS_TIME_SETTING_100MS   0x0000
#define AMBIENT6_CFG_ALS_TIME_SETTING_200MS   0x0001 << 6
#define AMBIENT6_CFG_ALS_TIME_SETTING_400MS   0x0002 << 6
#define AMBIENT6_CFG_ALS_TIME_SETTING_800MS   0x0003 << 6
#define AMBIENT6_CFG_PERSISTENCE_NUMBER_1     0x0000 << 4
#define AMBIENT6_CFG_PERSISTENCE_NUMBER_2     0x0001 << 4
#define AMBIENT6_CFG_PERSISTENCE_NUMBER_4     0x0002 << 4
#define AMBIENT6_CFG_PERSISTENCE_NUMBER_8     0x0003 << 4
#define AMBIENT6_CFG_ALS_INT_DISABLE          0x0000
#define AMBIENT6_CFG_ALS_INT_ENABLE           0x0001 << 1
#define AMBIENT6_CFG_ALS_POWER_ON             0x0000
#define AMBIENT6_CFG_ALS_SHUT_DOWN            0x0001
/** \} */

/**
 * \defgroup mode_settings  Mode settings
 * \{
 */
#define AMBIENT6_POWER_MODE_1        0x0000
#define AMBIENT6_POWER_MODE_2        0x0002
#define AMBIENT6_POWER_MODE_3        0x0004
#define AMBIENT6_POWER_MODE_4        0x0006
#define AMBIENT6_POWER_MODE_ENABLE   0x0001
#define AMBIENT6_POWER_MODE_DISABLE  0x0000
/** \} */

/**
 * \defgroup device_slave_address  Device slave address
 * \{
 */
#define AMBIENT6_DEVICE_SLAVE_ADDRESS  0x10
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

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    
    float c_gain;
    float c_time;

} ambient6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} ambient6_cfg_t;

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
void ambient6_cfg_setup ( ambient6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ambient6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMBIENT6_RETVAL ambient6_init ( ambient6_t *ctx, ambient6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Ambient6 click.
 * @note Default configuration of the chip contains the settings
 *<pre> 
 *   Ambient6_settings:
 *      - AMBIENT6_CFG_ALS_SENSITIVITY_X2
 *      - AMBIENT6_CFG_ALS_TIME_SETTING_25MS
 *      - AMBIENT6_CFG_PERSISTENCE_NUMBER_1
 *      - AMBIENT6_CFG_ALS_INT_DISABLE
 *      - AMBIENT6_CFG_ALS_POWER_ON
 *   Set AMBIENT6_CMD_MODE_SETTINGS register:
 *      - AMBIENT6_POWER_MODE_ENABLE
 *      - AMBIENT6_POWER_MODE_1
 *</pre>
 */
void ambient6_default_cfg ( ambient6_t *ctx );

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
void ambient6_generic_write ( ambient6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void ambient6_generic_read ( ambient6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for read 16bit Ambient Data (ALS)
 *
 * 
 * @param ctx          Click object.
 *
 * @retval Ambient data 
 *
 */
uint16_t ambient6_get_ambient_data ( ambient6_t *ctx );

/**
 * @brief Functions for configuration device for measurement
 *
 * 
 * @param ctx          Click object.
 * @param config_data  16Bit data for configuration
 *
 * @note - Options for settings:
 *<pre> 
 * Sensitivity mode selection (x1,x2,x1/8 or x1/4)
 *    ALS integration time setting (25ms, 50ms, 100ms, 200ms, 400ms or 800ms)
 *    ALS persistence protect number setting (1,2,4 or 8)
 *    ALS interrupt enable setting (enable or disable)
 *    ALS shut down setting (ALS power on or ALS shut down) 
 *</pre> 
 */
void ambient6_settings ( ambient6_t *ctx, uint16_t config_data);

/**
 * @brief Functions for get Ambient Light Data
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function converts ambient light depending on the set Gain and measurement time.
 */
float ambient6_get_ambient_light ( ambient6_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

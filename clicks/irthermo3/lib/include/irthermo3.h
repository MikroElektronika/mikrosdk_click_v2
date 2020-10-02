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
 * \brief This file contains API for IrThermo 3 Click driver.
 *
 * \addtogroup irthermo3 IrThermo 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRTHERMO3_H
#define IRTHERMO3_H

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
#define IRTHERMO3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRTHERMO3_RETVAL  uint8_t

#define IRTHERMO3_OK           0x00
#define IRTHERMO3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_slave Device slave address
 * \{
 */
#define IRTHERMO3_DEV_ADR_GND                   0x3A
#define IRTHERMO3_DEV_ADR_VCC                   0x3B
/** \} */

/**
 * \defgroup eeprom_ver EEPROM version
 * \{
 */
#define IRTHERMO3_EEPROM_VERSION                0x240B
/** \} */

/**
 * \defgroup eeprom_constants EEPROM constants
 * \{
 */
#define IRTHERMO3_EEPROM_CAL_CONST_P_R_LSW      0x240C
#define IRTHERMO3_EEPROM_CAL_CONST_P_R_MSW      0x240D
#define IRTHERMO3_EEPROM_CAL_CONST_P_G_LSW      0x240E
#define IRTHERMO3_EEPROM_CAL_CONST_P_G_MSW      0x240F
#define IRTHERMO3_EEPROM_CAL_CONST_P_T_LSW      0x2410
#define IRTHERMO3_EEPROM_CAL_CONST_P_T_MSW      0x2411
#define IRTHERMO3_EEPROM_CAL_CONST_P_O_LSW      0x2412
#define IRTHERMO3_EEPROM_CAL_CONST_P_O_MSW      0x2413
#define IRTHERMO3_EEPROM_CAL_CONST_AA_LSW       0x2414
#define IRTHERMO3_EEPROM_CAL_CONST_AA_MSW       0x2415
#define IRTHERMO3_EEPROM_CAL_CONST_AB_LSW       0x2416
#define IRTHERMO3_EEPROM_CAL_CONST_AB_MSW       0x2417
#define IRTHERMO3_EEPROM_CAL_CONST_BA_LSW       0x2418
#define IRTHERMO3_EEPROM_CAL_CONST_BA_MSW       0x2419
#define IRTHERMO3_EEPROM_CAL_CONST_BB_LSW       0x241A
#define IRTHERMO3_EEPROM_CAL_CONST_BB_MSW       0x241B
#define IRTHERMO3_EEPROM_CAL_CONST_CA_LSW       0x241C
#define IRTHERMO3_EEPROM_CAL_CONST_CA_MSW       0x241D
#define IRTHERMO3_EEPROM_CAL_CONST_CB_LSW       0x241E
#define IRTHERMO3_EEPROM_CAL_CONST_CB_MSW       0x241F
#define IRTHERMO3_EEPROM_CAL_CONST_DA_LSW       0x2420
#define IRTHERMO3_EEPROM_CAL_CONST_DA_MSW       0x2421
#define IRTHERMO3_EEPROM_CAL_CONST_DB_LSW       0x2422
#define IRTHERMO3_EEPROM_CAL_CONST_DB_MSW       0x2423
#define IRTHERMO3_EEPROM_CAL_CONST_EA_LSW       0x2424
#define IRTHERMO3_EEPROM_CAL_CONST_EA_MSW       0x2425
#define IRTHERMO3_EEPROM_CAL_CONST_EB_LSW       0x2426
#define IRTHERMO3_EEPROM_CAL_CONST_EB_MSW       0x2427
#define IRTHERMO3_EEPROM_CAL_CONST_FA_LSW       0x2428
#define IRTHERMO3_EEPROM_CAL_CONST_FA_MSW       0x2429
#define IRTHERMO3_EEPROM_CAL_CONST_FB_LSW       0x242A
#define IRTHERMO3_EEPROM_CAL_CONST_FB_MSW       0x242B
#define IRTHERMO3_EEPROM_CAL_CONST_GA_LSW       0x242C
#define IRTHERMO3_EEPROM_CAL_CONST_GA_MSW       0x242D
#define IRTHERMO3_EEPROM_CAL_CONST_GB           0x242E
#define IRTHERMO3_EEPROM_CAL_CONST_KA           0x242E
#define IRTHERMO3_EEPROM_CAL_CONST_KB           0x242E
#define IRTHERMO3_EEPROM_CAL_CONST_HA_COSTUMER  0x2481
#define IRTHERMO3_EEPROM_CAL_CONST_HB_COSTUMER  0x2482
/** \} */

/**
 * \defgroup ctrl_status Control and status registers
 * \{
 */
#define IRTHERMO3_EEPROM_CTRL_REG               0x24D4
#define IRTHERMO3_EEPROM_I2C_ADDRESS            0x24D5
#define IRTHERMO3_REG_I2C_ADDRESS               0x3000
#define IRTHERMO3_REG_CONTROL                   0x3001
#define IRTHERMO3_REG_STATUS                    0x3FFF
/** \} */

/**
 * \defgroup ram_registers RAM Registers
 * \{
 */
#define IRTHERMO3_RAW_DATA_1                    0x4000
#define IRTHERMO3_RAW_DATA_2                    0x4001
#define IRTHERMO3_RAW_DATA_3                    0x4002
#define IRTHERMO3_RAW_DATA_4                    0x4003
#define IRTHERMO3_RAW_DATA_5                    0x4004
#define IRTHERMO3_RAW_DATA_6                    0x4005
#define IRTHERMO3_RAW_DATA_7                    0x4006
#define IRTHERMO3_RAW_DATA_8                    0x4007
#define IRTHERMO3_RAW_DATA_9                    0x4008
/** \} */

/**
 * \defgroup modes Device mode
 * \{
 */
#define IRTHERMO3_MODE_SLEEP                    0x02
#define IRTHERMO3_MODE_STEPIN                   0x04
#define IRTHERMO3_MODE_CONTINOUS                0x06
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Calculation coefficients.
 */
typedef struct
{
    float p_r;
    float p_g;
    float p_t;
    float p_o;
    float ea;
    float eb;
    float fa;
    float fb;
    float ga;
    float gb;
    float ka;
    float ha;
    float hb;

} irthermo3_cal_coef_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    // Calculation coefficients

    irthermo3_cal_coef_t cal_coef;

} irthermo3_t;

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

} irthermo3_cfg_t;

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
void irthermo3_cfg_setup ( irthermo3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRTHERMO3_RETVAL irthermo3_init ( irthermo3_t *ctx, irthermo3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for IrThermo3 click.
 */
void irthermo3_default_cfg ( irthermo3_t *ctx );

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
void irthermo3_generic_write ( irthermo3_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len );

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
void irthermo3_generic_read ( irthermo3_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write u16 data function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param wr_data     Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void irthermo3_write_u16 ( irthermo3_t *ctx, uint16_t reg, uint16_t wr_data );

/**
 * @brief Read i16 dat function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @retval ret_val two bytes signed data which is read from the address.
 *
 * @description This function reads signed data from the desired register.
 */
int16_t irthermo3_read_i16( irthermo3_t *ctx, uint16_t reg );

/**
 * @brief Read i32 dat function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @retval ret_val four bytes signed data which is read from the address.
 *
 * @description This function reads signed data from the desired register.
 */
int32_t irthermo3_read_i32 ( irthermo3_t *ctx, uint16_t reg );

/**
 * @brief Global write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the addressed device.
 * @note This function is used exclusively to perform Addressed reset
 *       ( which resets the device ) or EEPROM unlock (for customer access)
 *        on slave address defined device
 */
void irthermo3_global_write ( irthermo3_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set device mode function
 *
 * @param ctx          Click object.
 * @param mode         Mode to be set.
 *
 * @description This function is used to set the devices mode to sleep,
 *              step mode or continuous mode.
 */
void irthermo3_set_mode( irthermo3_t *ctx, uint8_t mode );

/**
 * @brief Calibration function
 *
 * @param ctx          Click object.
 *
 * @description Function is used to calibrate the device.
 * @note This function must be used at least once in order to get correct readings!
 */
void irthermo3_cal ( irthermo3_t *ctx );

/**
 * @brief Read Ambient Temperature function
 *
 * @retval - Ambient temperature.
 *
 * @description Function is used to read ambient temperature.
 */
float irthermo3_get_ambient_temperature ( irthermo3_t *ctx );

/**
 * @brief Read Object Temperature function
 *
 * @retval - Object temperature.
 *
 * @description Function is used to read object temperature.
 */
float irthermo3_get_object_temperature ( irthermo3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRTHERMO3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

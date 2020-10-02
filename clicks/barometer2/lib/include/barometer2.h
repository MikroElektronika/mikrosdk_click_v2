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
 * \brief This file contains API for Barometer 2 Click driver.
 *
 * \addtogroup barometer2 Barometer 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BAROMETER2_H
#define BAROMETER2_H

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
#define BAROMETER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BAROMETER2_RETVAL  uint8_t

#define BAROMETER2_OK           0x00
#define BAROMETER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define  BAROMETER2_REG_INTERRUPT_CONFIG            0x0B
#define  BAROMETER2_REG_THRESHOLD_LSB               0x0C
#define  BAROMETER2_REG_THRESHOLD_MSB               0x0D
#define  BAROMETER2_REG_WHO_AM_I                    0x0F
#define  BAROMETER2_REG_CTRL_1                      0x10
#define  BAROMETER2_REG_CTRL_2                      0x11
#define  BAROMETER2_REG_CTRL_3                      0x12
#define  BAROMETER2_REG_FIFO_CTRL                   0x14
#define  BAROMETER2_REG_REF_P_XL                    0x15
#define  BAROMETER2_REG_REF_P_L                     0x16
#define  BAROMETER2_REG_REF_P_H                     0x17
#define  BAROMETER2_REG_RPDS_LSB                    0x18
#define  BAROMETER2_REG_RPDS_MSB                    0x19
#define  BAROMETER2_REG_RES_CONFIG                  0x1A
#define  BAROMETER2_REG_INT_SOURCE                  0x25
#define  BAROMETER2_REG_FIFO_STATUS                 0x26
#define  BAROMETER2_REG_STATUS                      0x27
#define  BAROMETER2_REG_PRESSURE_OUT_XL             0x28
#define  BAROMETER2_REG_PRESSURE_OUT_L              0x29
#define  BAROMETER2_REG_PRESSURE_OUT_H              0x2A
#define  BAROMETER2_REG_TEMPERATURE_LSB             0x2B
#define  BAROMETER2_REG_TEMPERATURE_MSB             0x2C
#define  BAROMETER2_REG_LPFP_RES                    0x33
/** \} */

/**
 * \defgroup interrupt_config Interrupt Config
 * \{
 */
#define  BAROMETER2_ICFG_AUTORIFP_DISABLE           0x00
#define  BAROMETER2_ICFG_AUTORIFP_ENABLE            0x80
#define  BAROMETER2_ICFG_AUTORIFP_NO_RESET          0x00
#define  BAROMETER2_ICFG_AUTORIFP_RESET             0x40
#define  BAROMETER2_ICFG_AUTOZERO_DISABLE           0x00
#define  BAROMETER2_ICFG_AUTOZERO_ENABLE            0x20
#define  BAROMETER2_ICFG_AUTOZERO_NO_RESET          0x00
#define  BAROMETER2_ICFG_AUTOZERO_RESET             0x10
#define  BAROMETER2_ICFG_INT_GENERATION_DISABLE     0x00
#define  BAROMETER2_ICFG_INT_GENERATION_ENABLE      0x08
#define  BAROMETER2_ICFG_INT_NOT_LATCHED            0x00
#define  BAROMETER2_ICFG_INT_LATCHED                0x04
#define  BAROMETER2_ICFG_INT_PLE_DISABLE            0x00
#define  BAROMETER2_ICFG_INT_PLE_ENABLE             0x02
#define  BAROMETER2_ICFG_INT_PHE_DISABLE            0x00
#define  BAROMETER2_ICFG_INT_PHE_ENABLE             0x01
/** \} */

/**
 * \defgroup ctrl_1 Ctrl 1
 * \{
 */
#define  BAROMETER2_CTRL1_ODR_1Hz                   0x10
#define  BAROMETER2_CTRL1_ODR_10Hz                  0x20
#define  BAROMETER2_CTRL1_ODR_25Hz                  0x30
#define  BAROMETER2_CTRL1_ODR_50Hz                  0x40
#define  BAROMETER2_CTRL1_ODR_75Hz                  0x50
#define  BAROMETER2_CTRL1_LPFP_DISABLE              0x00
#define  BAROMETER2_CTRL1_LPFP_ENABLE               0x08
#define  BAROMETER2_CTRL1_LPFP_CFG_ODR_2            0x00
#define  BAROMETER2_CTRL1_LPFP_CFG_ODR_9            0x08
#define  BAROMETER2_CTRL1_LPFP_CFG_ODR_10           0x0C
#define  BAROMETER2_CTRL1_BDU_CONT_UPDATE           0x00
#define  BAROMETER2_CTRL1_BDU_NOT_UPDATE            0x02
/** \} */

/**
 * \defgroup ctrl_2 Ctrl 2
 * \{
 */
#define  BAROMETER2_CTRL2_BOOT_NORMAL_MODE          0x00
#define  BAROMETER2_CTRL2_BOOT_REBOOT_MEMORY        0x80
#define  BAROMETER2_CTRL2_FIFO_DISABLED             0x00
#define  BAROMETER2_CTRL2_FIFO_ENABLED              0x40
#define  BAROMETER2_CTRL2_FIFO_THR_DISABLED         0x00
#define  BAROMETER2_CTRL2_FIFO_THR_ENABLED          0x20
#define  BAROMETER2_CTRL2_ID_ADD_INC_DISABLED       0x00
#define  BAROMETER2_CTRL2_ID_ADD_INC_ENABLED        0x10
#define  BAROMETER2_CTRL2_SOFTWARE_RESET            0x04
#define  BAROMETER2_CTRL2_MODE_IDLE                 0x01
/** \} */

/**
 * \defgroup ctrl_3 Ctrl 3
 * \{
 */
#define  BAROMETER2_CTRL3_INT_ACTIVE_HIGH           0x00
#define  BAROMETER2_CTRL3_INT_ACTIVE_LOW            0x80
#define  BAROMETER2_CTRL3_INT_PUSH_PULL             0x00
#define  BAROMETER2_CTRL3_INT_OPEN_DRAIN            0x40
#define  BAROMETER2_CTRL3_FIFO_FULL_DISABLED        0x00
#define  BAROMETER2_CTRL3_FIFO_FULL_ENABLED         0x20
#define  BAROMETER2_CTRL3_FIFO_WTM_DISABLED         0x00
#define  BAROMETER2_CTRL3_FIFO_WTM_ENABLED          0x10
#define  BAROMETER2_CTRL3_FIFO_OVERRUN_DISABLED     0x00
#define  BAROMETER2_CTRL3_FIFO_OVERRUN_ENABLED      0x08
#define  BAROMETER2_CTRL3_DRDY_DISABLED             0x00
#define  BAROMETER2_CTRL3_DRDY_ENABLED              0x04
#define  BAROMETER2_CTRL3_DRDY_STATUS_P_HIGH        0x01
#define  BAROMETER2_CTRL3_DRDY_STATUS_P_LOW         0x02
/** \} */

/**
 * \defgroup fifo_ctrl FIFO Ctrl
 * \{
 */
#define  BAROMETER2_FIFO_CTRL_BYPASS_MODE           0x00
#define  BAROMETER2_FIFO_CTRL_FIFO_MODE             0x20
#define  BAROMETER2_FIFO_CTRL_STREAM_MODE           0x40
#define  BAROMETER2_FIFO_CTRL_STREAM_TO_FIFO_MODE   0x60
#define  BAROMETER2_FIFO_CTRL_BYPASS_TO_STREAM_MODE 0x80
#define  BAROMETER2_FIFO_CTRL_DYNAMIC_STREAM_MODE   0xC0
#define  BAROMETER2_FIFO_CTRL_BYPASS_TO_FIFO_MODE   0xE0
/** \} */

/**
 * \defgroup res_config Res Config
 * \{
 */
#define  BAROMETER2_RESCFG_NORMAL_MODE              0x00
#define  BAROMETER2_RESCFG_LOW_CURRENT_MODE         0x01
/** \} */

/**
 * \defgroup return_data Return Data
 * \{
 */
#define  BAROMETER2_WHO_AM_I                        0xB1
#define  BAROMETER2_DEVICE_SLAVE_ADDR_GND           0x5C
#define  BAROMETER2_DEVICE_SLAVE_ADDR_VCC           0x5D
/** \} */

/**
 * \defgroup pressure_data_format Pressure Data Format
 * \{
 */
#define  BAROMETER2_PRESSURE_DATA_IN_mBar           0
#define  BAROMETER2_PRESSURE_DATA_IN_hPa            0
#define  BAROMETER2_PRESSURE_DATA_IN_kPa            2
#define  BAROMETER2_PRESSURE_DATA_IN_Torr           1
#define  BAROMETER2_PRESSURE_DATA_IN_mmHg           1
#define  BAROMETER2_PRESSURE_DATA_IN_Bar            3
/** \} */

/**
 * \defgroup temperature_data_format Temperature Data Format
 * \{
 */
#define  BAROMETER2_TEMPERATURE_IN_CELSIUS          0x00
#define  BAROMETER2_TEMPERATURE_IN_KELVIN           0x01
#define  BAROMETER2_TEMPERATURE_IN_FARENHAJT        0x02
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
    
} barometer2_t;

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

} barometer2_cfg_t;

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
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void barometer2_cfg_setup ( barometer2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param barometer2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BAROMETER2_RETVAL barometer2_init ( barometer2_t *ctx, barometer2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Barometer2 click.
 */
void barometer2_default_cfg ( barometer2_t *ctx );

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
void barometer2_generic_write ( barometer2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void barometer2_generic_read ( barometer2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write one byte function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_bytes         Data to be written.
 *
 * @description This function writes one byte of data to the desired register.
 */
void barometer2_write_byte ( barometer2_t *ctx, uint8_t reg, uint8_t data_bytes );

/**
 * @brief Read one byte function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads one byte of data from the desired register.
 */
uint8_t barometer2_read_byte ( barometer2_t *ctx, uint8_t reg );

/**
 * @brief Read temperature function.
 * 
 * @param ctx          Click object.
 * @param temp_format          Unit of measurement.
 *
 * @description This function reads temperature data and stores it in different formats depending on the unit of measurement parameter.
 */
float barometer2_get_temperature ( barometer2_t *ctx, uint8_t temp_format );

/**
 * @brief Reset function.
 * 
 * @param ctx          Click object.
 * 
 * @description This function resets the device to its default settings.
 */
void barometer2_software_reset ( barometer2_t *ctx );

/**
 * @brief Read pressure function.
 * 
 * @param ctx          Click object.
 * @param temp_format          Unit of measurement.
 *
 * @description This function reads pressure data and stores it in different formats depending on the unit of measurement parameter.
 */
float barometer2_get_pressure ( barometer2_t *ctx, uint8_t press_format );

/**
 * @brief Gets interrupt.
 * 
 * @param ctx          Click object. 
 * 
 * @description This function gets the interrupt.
 */
uint8_t barometer2_get_interrupt ( barometer2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BAROMETER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

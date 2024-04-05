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
 * \brief This file contains API for LightRanger Click driver.
 *
 * \addtogroup lightranger LightRanger Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LIGHTRANGER_H
#define LIGHTRANGER_H

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
#define LIGHTRANGER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LIGHTRANGER_RETVAL  uint8_t

#define LIGHTRANGER_OK           0x00
#define LIGHTRANGER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup identification_registers Identification Registers
 * \{
 */
#define LIGHTRANGER_IDENTIFICATION_MODEL_ID                    0x0000
#define LIGHTRANGER_IDENTIFICATION_MODEL_REV_MAJOR             0x0001
#define LIGHTRANGER_IDENTIFICATION_MODEL_REV_MINOR             0x0002
#define LIGHTRANGER_IDENTIFICATION_MODULE_REV_MAJOR            0x0003
#define LIGHTRANGER_IDENTIFICATION_MODULE_REV_MINOR            0x0004
#define LIGHTRANGER_IDENTIFICATION_DATE_HI                     0x0006
#define LIGHTRANGER_IDENTIFICATION_DATE_LO                     0x0007
#define LIGHTRANGER_IDENTIFICATION_TIME_HI                     0x0008
#define LIGHTRANGER_IDENTIFICATION_TIME_LO                     0x0009
/** \} */

/**
 * \defgroup system_mode System Modes
 * \{
 */
#define LIGHTRANGER_SYSTEM_MODE_GPIO0                          0x0010
#define LIGHTRANGER_SYSTEM_MODE_GPIO1                          0x0011
#define LIGHTRANGER_SYSTEM_HISTORY_CTRL                        0x0012
#define LIGHTRANGER_SYSTEM_INTERRUPT_CONFIG_GPIO               0x0014
#define LIGHTRANGER_SYSTEM_INTERRUPT_CLEAR                     0x0015
#define LIGHTRANGER_SYSTEM_FRESH_OUT_OF_RESET                  0x0016
#define LIGHTRANGER_SYSTEM_GROUPED_PARAMETER_HOLD              0x0017
/** \} */

/**
 * \defgroup system_range   System range registers
 * \{
 */
#define LIGHTRANGER_SYSRANGE_START                             0x0018
#define LIGHTRANGER_SYSRANGE_THRESH_HIGH                       0x0019
#define LIGHTRANGER_SYSRANGE_THRESH_LOW                        0x001A
#define LIGHTRANGER_SYSRANGE_INTERMEASUREMENT_PERIOD           0x001B
#define LIGHTRANGER_SYSRANGE_MAX_CONVERGENCE_TIME              0x001C
#define LIGHTRANGER_SYSRANGE_CROSSTALK_COMPENSATION_RATE       0x001E
#define LIGHTRANGER_SYSRANGE_CROSSTALK_VALID_HEIGHT            0x0021
#define LIGHTRANGER_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE        0x0022
#define LIGHTRANGER_SYSRANGE_PART_TO_PART_RANGE_OFFSET         0x0024
#define LIGHTRANGER_SYSRANGE_RANGE_IGNORE_VALID_HEIGHT         0x0025
#define LIGHTRANGER_SYSRANGE_RANGE_IGNORE_THRESHOLD            0x0026
#define LIGHTRANGER_SYSRANGE_MAX_AMBIENT_LEVEL_MULT            0x002C
#define LIGHTRANGER_SYSRANGE_RANGE_CHECK_ENABLES               0x002D
#define LIGHTRANGER_SYSRANGE_VHV_RECALIBRATE                   0x002E
#define LIGHTRANGER_SYSRANGE_VHV_REPEAT_RATE                   0x0031
#define LIGHTRANGER_SYSALS_START                               0x0038
#define LIGHTRANGER_SYSALS_THRESH_HIGH                         0x003A
#define LIGHTRANGER_SYSALS_THRESH_LOW                          0x003C
#define LIGHTRANGER_SYSALS_INTERMEASUREMENT_PERIOD             0x003E
#define LIGHTRANGER_SYSALS_ANALOGUE_GAIN                       0x003F
#define LIGHTRANGER_SYSALS_INTEGRATION_PERIOD                  0x0040
/** \} */

/**
 * \defgroup result_registers   Result registers
 * \{
 */
#define LIGHTRANGER_RESULT_RANGE_STATUS                        0x004D
#define LIGHTRANGER_RESULT_ALS_STATUS                          0x004E
#define LIGHTRANGER_RESULT_INTERRUPT_STATUS_GPIO               0x004F
#define LIGHTRANGER_RESULT_ALS_VAL                             0x0050
#define LIGHTRANGER_RESULT_HISTORY_BUFFER0                     0x0052 
#define LIGHTRANGER_RESULT_HISTORY_BUFFER1                     0x0053 
#define LIGHTRANGER_RESULT_HISTORY_BUFFER2                     0x0054 
#define LIGHTRANGER_RESULT_HISTORY_BUFFER3                     0x0055
#define LIGHTRANGER_RESULT_HISTORY_BUFFER4                     0x0056
#define LIGHTRANGER_RESULT_HISTORY_BUFFER5                     0x0057
#define LIGHTRANGER_RESULT_HISTORY_BUFFER6                     0x0058
#define LIGHTRANGER_RESULT_HISTORY_BUFFER7                     0x0059
#define LIGHTRANGER_RESULT_HISTORY_BUFFER8                     0x0060  
#define LIGHTRANGER_RESULT_RANGE_VAL                           0x0062
#define LIGHTRANGER_RESULT_RANGE_RAW                           0x0064
#define LIGHTRANGER_RESULT_RANGE_RETURN_RATE                   0x0066
#define LIGHTRANGER_RESULT_RANGE_REFERENCE_RATE                0x0068
#define LIGHTRANGER_RESULT_RANGE_RETURN_SIGNAL_COUNT           0x006C
#define LIGHTRANGER_RESULT_RANGE_REFERENCE_SIGNAL_COUNT        0x0070
#define LIGHTRANGER_RESULT_RANGE_RETURN_AMB_COUNT              0x0074
#define LIGHTRANGER_RESULT_RANGE_REFERENCE_AMB_COUNT           0x0078
#define LIGHTRANGER_RESULT_RANGE_RETURN_CONV_TIME              0x007C
#define LIGHTRANGER_RESULT_RANGE_REFERENCE_CONV_TIME           0x0080
 /** \} */
/**
 * \defgroup various_registers   Various registers
 * \{
 */ 
#define LIGHTRANGER_READOUT_AVERAGING_SAMPLE_PERIOD            0x010A
#define LIGHTRANGER_FIRMWARE_BOOTUP                            0x0119
#define LIGHTRANGER_FIRMWARE_RESULT_SCALER                     0x0120
#define LIGHTRANGER_I2C_SLAVE_DEVICE_ADDRESS                   0x0212
#define LIGHTRANGER_INTERLEAVED_MODE_ENABLE                    0x02A3
 /** \} */

/**
 * \defgroup lightranger_commands LightRanger Commands
 * \{
 */
#define LIGHTRANGER_CMD_RESET                   0x1E    
#define LIGHTRANGER_CMD_ADC_READ                0x00   
#define LIGHTRANGER_CMD_ADC_CONV                0x40   
#define LIGHTRANGER_CMD_ADC_D1                  0x00   
#define LIGHTRANGER_CMD_ADC_D2                  0x10   
#define LIGHTRANGER_CMD_ADC_256                 0x00   
#define LIGHTRANGER_CMD_ADC_512                 0x02   
#define LIGHTRANGER_CMD_ADC_1024                0x04   
#define LIGHTRANGER_CMD_ADC_2048                0x06   
#define LIGHTRANGER_CMD_ADC_4096                0x08   
#define LIGHTRANGER_CMD_PROM_RD                 0xA0   
#define LIGHTRANGER_CMD_CALC_DIST               0x32   
#define LIGHTRANGER_CMD_INTERRUPT_CLEAR         0x07  
#define LIGHTRANGER_CMD_GAIN_1X                 0x06  
 /** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define LIGHTRANGER_I2C_ADDRESS  0x29
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
    
    digital_out_t en;
   
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} lightranger_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en;

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} lightranger_cfg_t;

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
void lightranger_cfg_setup ( lightranger_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param lightranger Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LIGHTRANGER_RETVAL lightranger_init ( lightranger_t *ctx, lightranger_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for LightRanger Click.
 */
void lightranger_default_cfg ( lightranger_t* ctx );

/**
 * @brief Clear Interrupts.
 *
 * @param lightranger Click object.
 *
 * @description This function clears interrupts.
 */
void lightranger_interrupts_clear ( lightranger_t* ctx );

/**
 * @brief Poll range.
 *
 * @param lightranger Click object.
 *
 *
 * @description This function waits for new sample to be ready.
 */
void lightranger_poll_range ( lightranger_t* ctx );

/**
 * @brief Get Distance.
 *
 * @param lightranger Click object.
 *
 * @returns Data      16-bit data range value.
 *
 * @description This function reads range result from register.
 */
uint8_t lightranger_get_distance ( lightranger_t* ctx );

/**
 * @brief Get ambiant light.
 *
 * @param lightranger       Click object.
 * @param als_gain_check    ALS Gain value.
 *
 * @returns Data            Float light level in lux.
 *
 * @description This function reads register and calculates the light level in lux.
 */
float lightranger_get_ambiant_light ( lightranger_t* ctx, uint8_t als_gain_check );

/**
 * @brief Function Start Single Mode
 *
 * @param lightranger       Click object.
 *
 *
 * @description This function starts single shot range mode.
 */
void lightranger_start_single_shot_range_mode ( lightranger_t* ctx );

/**
 * @brief Generic read data function.
 *
 * @param lightranger       Click object.
 * @param reg_addr          16-bit register address.
 *
 * @returns Data            16-bit data from given address.
 *
 * @description This function reads 16-bit data from given address.
 */
uint16_t lightranger_read_data ( lightranger_t* ctx, uint16_t reg_addr );

/**
 * @brief Generic write data function.
 *
 * @param lightranger       Click object.
 * @param reg_addr          16-bit register address.
 * @param write_command     16-bit command to write.
 *
 *
 * @description This function writes 16-bit command to given address.
 */
void lightranger_write_data ( lightranger_t* ctx, uint16_t reg_addr, uint16_t write_command );

/**
 * @brief Generic read byte function.
 *
 * @param lightranger       Click object.
 * @param reg_addr          16-bit register address.
 *
 * @returns Data            Byte from given address.
 *
 * @description This function reads a byte of data from given address.
 */
uint8_t lightranger_read_byte ( lightranger_t* ctx, uint16_t reg_addr );

/**
 * @brief Generic write byte function.
 *
 * @param lightranger       Click object.
 * @param reg_addr          16-bit register address.
 * @param write_command     Byte of data to write.
 *
 * @description This function writes a byte of data to given address.
 */
void lightranger_write_byte ( lightranger_t* ctx, uint16_t reg_addr, uint8_t write_command );



#ifdef __cplusplus
}
#endif
#endif  // _LIGHTRANGER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

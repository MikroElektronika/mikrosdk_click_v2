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
 * \brief This file contains API for BATT-MON Click driver.
 *
 * \addtogroup battmon BATT-MON Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BATTMON_H
#define BATTMON_H

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
#define BATTMON_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rio  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.alm  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BATTMON_RETVAL  uint8_t

#define BATTMON_OK           0x00
#define BATTMON_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup dummy_byte Dummy byte
 * \{
 */
#define DUMMY_BYTE  0x00
/** \} */

/**
 * \defgroup device_slave_address Device Slave Address
 * \{
 */
#define BATTMON_DEV_ADDR                      0x70
/** \} */
 
/**
 * \defgroup data_registers  Data Registers
 * \{
 */
#define BATTMON_REG_MODE                      0
#define BATTMON_REG_CTRL                      1
#define BATTMON_REG_SOC                       2
#define BATTMON_REG_COUNTER                   4
#define BATTMON_REG_CURRENT                   6
#define BATTMON_REG_VOLTAGE                   8
#define BATTMON_REG_TEMPERATURE               10
#define BATTMON_REG_CC_ADJ_HIGH               11
#define BATTMON_REG_VM_ADJ_HIGH               12
#define BATTMON_REG_OCV                       13
#define BATTMON_REG_CC_CNF                    15
#define BATTMON_REG_VM_CNF                    17
#define BATTMON_REG_ALARM_SOC                 19
#define BATTMON_REG_ALARM_VOLTAGE             20
#define BATTMON_REG_CURRENT_THRES             21
#define BATTMON_REG_RELAX_COUNT               22
#define BATTMON_REG_RELAX_MAX                 23
#define BATTMON_REG_ID                        24
#define BATTMON_REG_CC_ADJ_LOW                25
#define BATTMON_REG_VM_ADJ_LOW                26
#define BATTMON_ACC_CC_ADJ                    27
#define BATTMON_ACC_VM_ADJ                    29
/** \} */
 
/**
 * \defgroup ram_registers  Ram registers
 * \{
 */
#define BATTMON_REG_RAM0                      32
#define BATTMON_REG_RAM1                      33
#define BATTMON_REG_RAM2                      34
#define BATTMON_REG_RAM3                      35
#define BATTMON_REG_RAM4                      36
#define BATTMON_REG_RAM5                      37
#define BATTMON_REG_RAM6                      38
#define BATTMON_REG_RAM7                      39
#define BATTMON_REG_RAM8                      40
#define BATTMON_REG_RAM9                      41
#define BATTMON_REG_RAM10                     42
#define BATTMON_REG_RAM11                     43
#define BATTMON_REG_RAM12                     44
#define BATTMON_REG_RAM13                     45
#define BATTMON_REG_RAM14                     46
#define BATTMON_REG_RAM15                     47
/** \} */
 
/**
 * \defgroup ocv?registers OCV Registers
 * \{
 */
#define BATTMON_REG_OCVTAB0                   48
#define BATTMON_REG_OCVTAB1                   49
#define BATTMON_REG_OCVTAB2                   50
#define BATTMON_REG_OCVTAB3                   51
#define BATTMON_REG_OCVTAB4                   52
#define BATTMON_REG_OCVTAB5                   53
#define BATTMON_REG_OCVTAB6                   54
#define BATTMON_REG_OCVTAB7                   55
#define BATTMON_REG_OCVTAB8                   56
#define BATTMON_REG_OCVTAB9                   57
#define BATTMON_REG_OCVTAB10                  58
#define BATTMON_REG_OCVTAB11                  59
#define BATTMON_REG_OCVTAB12                  60
#define BATTMON_REG_OCVTAB13                  61
#define BATTMON_REG_OCVTAB14                  62
#define BATTMON_REG_OCVTAB15                  63
/** \} */
 
/**
 * \defgroup mode_registers  Mode registers
 * \{
 */
#define BATTMON_MIXED_MODE                    0x00
#define BATTMON_PWR_SAVE_VOLT_MODE            0x01
#define BATTMON_CLR_VM_ADJ                    0x02
#define BATTMON_CLR_CC_ADJ                    0x04
#define BATTMON_ALM_EN                        0x08
#define BATTMON_STNDBY_RUN_MODE               0x00
#define BATTMON_OP_RUN_MODE                   0x10
#define BATTMON_FORCE_CC                      0x20
#define BATTMON_FORCE_VM                      0x40
/** \} */
 
/**
 * \defgroup control_registers  Control Registers
 * \{
 */
#define BATTMON_ALM_PIN_STAT_MASK             0x01
#define BATTMON_FORCE_ALM_PIN_LOW             0x00
#define BATTMON_DRIVE_ALM_PIN_COND            0x01
#define BATTMON_RST_CONV_CNT                  0x02
#define BATTMON_SOC_STAT_MASK                 0x04
#define BATTMON_SOC_CC_MODE                   0x00
#define BATTMON_SOC_VM_MODE                   0x04
#define BATTMON_BATFAIL_DET_MASK              0x08
#define BATTMON_POR_DET_MASK                  0x10
#define BATTMON_POR_INACTIVE                  0x00
#define BATTMON_POR_ACTIVE                    0x10
#define BATTMON_SOFT_RST                      0x10
#define BATTMON_ALM_SOC_DET_MASK              0x20
#define BATTMON_ALM_VOLT_DET_MASK             0x40
/** \} */
 
/**
 * \defgroup error_function  Error function
 * \{
 */
#define BATTMON_INVALID_ADDR                  0xFF
#define BATTMON_INVALID_NBYTES                0xFE
#define BATTMON_INVALID_ALM_VAL               0xFD
#define BATTMON_OK                            0x00
#define BATTMON_LOG_LOW                       0x00
#define BATTMON_LOG_HIGH                      0x01
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

    digital_in_t rio;
    digital_in_t alm;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} battmon_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rio;
    pin_name_t alm;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} battmon_cfg_t;

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
void battmon_cfg_setup ( battmon_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param battmon Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BATTMON_RETVAL battmon_init ( battmon_t *ctx, battmon_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note 
 *<pre>
 *      Set: BATTMON_REG_MODE
 *            - BATTMON_MIXED_MODE | 
 *            - BATTMON_ALM_EN | 
 *            - BATTMON_OP_RUN_MODE
 *      Set: BATTMON_REG_CTRL
 *            - BATTMON_RST_CONV_CNT | 
 *            - BATTMON_DRIVE_ALM_PIN_COND
 *      Set: BATTMON_REG_ALARM_SOC
 *            - 1
 *      Set: BATTMON_REG_ALARM_VOLTAGE
 *            - 3000
 *</pre>
 * @description This function executes default configuration for BattMon click.
 */
void battmon_default_cfg ( battmon_t *ctx );

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
void battmon_generic_write ( battmon_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void battmon_generic_read ( battmon_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Bytes Read function
 *
 * @param ctx        Click object.
 * @param reg_addr  Address which from data reading be started
 * @param dataOut   Memory where data be stored
 * @param n_bytes   Number of bytes to be read
 *
 * @returns 0x00 - OK, 0xFF - Invalid address, 0xFE - Invalid number of bytes
 *
 * @description This function reads the desired number of bytes starting from the selected register.
 */
uint8_t battmon_read_bytes ( battmon_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Word Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address which from data be read
 * @param data_out  Memory where data be stored
 *
 * @returns 0x00 - OK, 0xFF - Invalid address
 *
 * @description This function reads 16bit data from the selected register.
 */
uint8_t battmon_read_word ( battmon_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Byte Write function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address where data be written
 * @param data_in   Data to be written
 *
 * @returns 0x00 - OK, 0xFF - Invalid address
 *
 * @description This function writes one byte data to the selected register.
 */
uint8_t battmon_write_byte ( battmon_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Word Write function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address where data be written
 * @param data_in   Data to be written
 *
 * @returns 0x00 - OK, 0xFF - Invalid address
 *
 * @description This function writes 16bit data to the selected register.
 */
uint8_t battmon_write_word ( battmon_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Data Get function
 *
 * @param ctx        Click object.
 * @param data_addr  Address of data to be read
 *
 * @returns The selected data value
 *
 * This function allows user to get the desired data calculated to the properly unit.
 * @note 
 *<pre>
 * If data address is invalid, the function will return 0.
 * Data unit to be calculated: SOC [%]
 *                             Counter [sec]
 *                             Current [mA]
 *                             Voltage [mV]
 *                             Temperature [Celsius degrees]
 *</pre>
 */
float battmon_get_data ( battmon_t *ctx, uint8_t data_addr );

/**
 * @brief Alarm Set function
 *
 * @param ctx          Click object.
 * @param alarm_addr   Address of alarm to be set
 * @param alarm_value  Alarm value to be set
 *
 * @returns 0x00 - OK, 0xFF - Invalid address, 0xFD - Invalid alarm value
 *
 * @description This function allows user to set alarm registers to the desired value.
 * @note The properly alarm value unit: SOC [%]
 *                                      Voltage [mV]
 *                                      Current [mA]
 */
uint8_t battmon_set_alarm ( battmon_t *ctx, uint8_t alarm_addr, float alarm_value );

/**
 * @brief RIO Pin Get function
 *
 * @param ctx  Click object.
 *
 * @returns 0 or 1
 *
 * @description This function allows user to check state of the RIO pin.
 */
uint8_t battmon_get_rio_pin ( battmon_t *ctx );

/**
 * @brief ALM Pin Get function
 *
 * @param ctx  Click object.
 *
 * @returns 0 or 1
 *
 * @description This function allows user to check state of the ALM pin.
 * @note The ALM pin remains low (even if the conditions disappear) until the software writes
 *       the ALM_VOLT and ALM_SOC bits to 0 to clear the interrupt.
 */
uint8_t battmon_get_alm_pin ( battmon_t *ctx );

/**
 * @brief Alarm Check And Clear function
 *
 * @param ctx  Click object.
 *
 * @returns Alarm status
 *
 * @description This function allows user to check status of the low-SOC and low-voltage conditions.
 * @note If any of these conditions is set, the both alarm flags will be cleared.
 */
uint8_t battmon_check_clear_alarm ( battmon_t *ctx );

/**
 * @brief SW Reset function
 *
 * @param ctx  Click object.
 *
 * @description This function performs a device SW reset and waits until reset operation was done.
 */
void battmon_sw_reset ( battmon_t *ctx );

/**
 * @brief Conversion Counter Reset function
 *
 * @param ctx  Click object.
 *
 * @description This function allows user to reset the conversion counter.
 */
void battmon_reset_conv_cnt ( battmon_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BATTMON_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

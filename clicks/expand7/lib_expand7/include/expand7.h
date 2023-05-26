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
 * \brief This file contains API for Expand 7 Click driver.
 *
 * \addtogroup expand7 Expand 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EXPAND7_H
#define EXPAND7_H

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
#define EXPAND7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EXPAND7_OK                         0
#define EXPAND7_ERROR                     -1
/** \} */
 
/**
 * \defgroup device_address Device address
 * \{
 */
#define EXPAND7_M_PORT_BASE_ADR            0x20
#define EXPAND7_EEPROM_BASE_ADR            0x50
#define EXPAND7_DEV_ADR_GND                0x00
#define EXPAND7_DEV_ADR_VCC                0x01
/** \} */
 
/**
 * \defgroup reg_map  Reg map
 * \{
 */
#define EXPAND7_REG_IN_PORT0_ADR           0x00
#define EXPAND7_REG_IN_PORT1_ADR           0x01
#define EXPAND7_REG_IN_PORT2_ADR           0x02
#define EXPAND7_REG_IN_PORT3_ADR           0x03
#define EXPAND7_REG_IN_PORT4_ADR           0x04
#define EXPAND7_REG_IN_PORT5_ADR           0x05
#define EXPAND7_REG_IN_PORT6_ADR           0x06
#define EXPAND7_REG_IN_PORT7_ADR           0x07
#define EXPAND7_REG_OUT_PORT0_ADR          0x08
#define EXPAND7_REG_OUT_PORT1_ADR          0x09
#define EXPAND7_REG_OUT_PORT2_ADR          0x0A
#define EXPAND7_REG_OUT_PORT3_ADR          0x0B
#define EXPAND7_REG_OUT_PORT4_ADR          0x0C
#define EXPAND7_REG_OUT_PORT5_ADR          0x0D
#define EXPAND7_REG_OUT_PORT6_ADR          0x0E
#define EXPAND7_REG_OUT_PORT7_ADR          0x0F
#define EXPAND7_REG_INT_STAT_PORT0_ADR     0x10
#define EXPAND7_REG_INT_STAT_PORT1_ADR     0x11
#define EXPAND7_REG_INT_STAT_PORT2_ADR     0x12
#define EXPAND7_REG_INT_STAT_PORT3_ADR     0x13
#define EXPAND7_REG_INT_STAT_PORT4_ADR     0x14
#define EXPAND7_REG_INT_STAT_PORT5_ADR     0x15
#define EXPAND7_REG_INT_STAT_PORT6_ADR     0x16
#define EXPAND7_REG_INT_STAT_PORT7_ADR     0x17
#define EXPAND7_REG_PORT_SEL_ADR           0x18
#define EXPAND7_REG_INT_MASK_ADR           0x19
#define EXPAND7_REG_SEL_PWM_OUT_ADR        0x1A
#define EXPAND7_REG_INV_ADR                0x1B
#define EXPAND7_REG_PORT_DIR_ADR           0x1C
#define EXPAND7_REG_PULL_UP_ADR            0x1D
#define EXPAND7_REG_PULL_DOWN_ADR          0x1E
#define EXPAND7_REG_OPEN_DRAIN_HIGH_ADR    0x1F
#define EXPAND7_REG_OPEN_DRAIN_LOW_ADR     0x20
#define EXPAND7_REG_STRONG_ADR             0x21
#define EXPAND7_REG_SLOW_STRONG_ADR        0x22
#define EXPAND7_REG_HIGH_Z_ADR             0x23
#define EXPAND7_REG_RSRVD_1_ADR            0x24
#define EXPAND7_REG_RSRVD_2_ADR            0x25
#define EXPAND7_REG_RSRVD_3_ADR            0x26
#define EXPAND7_REG_RSRVD_4_ADR            0x27
#define EXPAND7_REG_PWM_SEL_ADR            0x28
#define EXPAND7_REG_CFG_PWM_ADR            0x29
#define EXPAND7_REG_PERIOD_PWM_ADR         0x2A
#define EXPAND7_REG_PULSE_WIDTH_PWM_ADR    0x2B
#define EXPAND7_REG_DIVIDER_ADR            0x2C
#define EXPAND7_REG_EEPROM_ADR             0x2D
#define EXPAND7_REG_DEV_ID_ADR             0x2E
#define EXPAND7_REG_WDT_ADR                0x2F
#define EXPAND7_REG_CMD_ADR                0x30
/** \} */
 
/**
 * \defgroup pwm_select  Pwm select
 * \{
 */
#define EXPAND7_SEL_PWM_0                  0x00
#define EXPAND7_SEL_PWM_1                  0x01
#define EXPAND7_SEL_PWM_2                  0x02
#define EXPAND7_SEL_PWM_3                  0x03
#define EXPAND7_SEL_PWM_4                  0x04
#define EXPAND7_SEL_PWM_5                  0x05
#define EXPAND7_SEL_PWM_6                  0x06
#define EXPAND7_SEL_PWM_7                  0x07
/** \} */
 
/**
 * \defgroup pwm_clock_source  Pwm clock source
 * \{
 */
#define EXPAND7_PWM_CLK_SRC_32_KHZ         0x00
#define EXPAND7_PWM_CLK_SRC_24_MHZ         0x01
#define EXPAND7_PWM_CLK_SRC_1_5_MHZ        0x02
#define EXPAND7_PWM_CLK_SRC_93_75_KHZ      0x03
#define EXPAND7_PWM_CLK_SRC_367_6_HZ       0x04
#define EXPAND7_PWM_CLK_SRC_PREV           0x05
/** \} */
 
/**
 * \defgroup avilable_commands  Available commands
 * \{
 */
#define EXPAND7_STORE_POR_CFG_TO_EEPROM    0x01
#define EXPAND7_RESTORE_DEFAULTS           0x02
#define EXPAND7_WRITE_EEPROM_POR           0x03
#define EXPAND7_READ_EEPROM_POR            0x04
#define EXPAND7_WRITE_DEV_CFG              0x05
#define EXPAND7_READ_DEV_CFG               0x06
#define EXPAND7_RECFG_DEV_TO_POR           0x07
/** \} */
 
/**
 * \defgroup enable_reg  Enable reg
 * \{
 */
#define EXPAND7_EEPROM_EN_WDE              0x01
#define EXPAND7_EEPROM_EN_EEE              0x02
#define EXPAND7_EEPROM_EN_EERO             0x04
/** \} */
 
/**
 * \defgroup port_select  Port select
 * \{
 */
#define EXPAND7_PORT_0                     0x00
#define EXPAND7_PORT_1                     0x01
#define EXPAND7_PORT_2                     0x02
#define EXPAND7_PORT_3                     0x03
#define EXPAND7_PORT_4                     0x04
#define EXPAND7_PORT_5                     0x05
/** \} */
 
/**
 * \defgroup pin_states Pin states
 * \{
 */
#define EXPAND7_LOW                        0x00
#define EXPAND7_HIGH                       0x01
#define EXPAND7_INT_NORMAL                 0x00
#define EXPAND7_INT_INVERTED               0x01
/** \} */
 
/**
 * \defgroup configuration_data_structure_offsets  Configuration data structure offsets 
 * \{
 */
#define EXPAND7_PORT0_OUT_INX              0x00
#define EXPAND7_PORT1_OUT_INX              0x01
#define EXPAND7_PORT2_OUT_INX              0x02
#define EXPAND7_PORT3_OUT_INX              0x03
#define EXPAND7_PORT4_OUT_INX              0x04
#define EXPAND7_PORT5_OUT_INX              0x05
#define EXPAND7_PORT6_OUT_INX              0x06
#define EXPAND7_PORT7_OUT_INX              0x07

#define EXPAND7_PORT0_INT_MASK_INX         0x08
#define EXPAND7_PORT1_INT_MASK_INX         0x09
#define EXPAND7_PORT2_INT_MASK_INX         0x0A
#define EXPAND7_PORT3_INT_MASK_INX         0x0B
#define EXPAND7_PORT4_INT_MASK_INX         0x0C
#define EXPAND7_PORT5_INT_MASK_INX         0x0D
#define EXPAND7_PORT6_INT_MASK_INX         0x0E
#define EXPAND7_PORT7_INT_MASK_INX         0x0F

#define EXPAND7_PORT0_SEL_PWM_INX          0x10
#define EXPAND7_PORT1_SEL_PWM_INX          0x11
#define EXPAND7_PORT2_SEL_PWM_INX          0x12
#define EXPAND7_PORT3_SEL_PWM_INX          0x13
#define EXPAND7_PORT4_SEL_PWM_INX          0x14
#define EXPAND7_PORT5_SEL_PWM_INX          0x15
#define EXPAND7_PORT6_SEL_PWM_INX          0x16
#define EXPAND7_PORT7_SEL_PWM_INX          0x17

#define EXPAND7_PORT0_INV_INX              0x18
#define EXPAND7_PORT1_INV_INX              0x19
#define EXPAND7_PORT2_INV_INX              0x1A
#define EXPAND7_PORT3_INV_INX              0x1B
#define EXPAND7_PORT4_INV_INX              0x1C
#define EXPAND7_PORT5_INV_INX              0x1D
#define EXPAND7_PORT6_INV_INX              0x1E
#define EXPAND7_PORT7_INV_INX              0x1F

#define EXPAND7_PORT0_DIR_INX              0x20
#define EXPAND7_PORT1_DIR_INX              0x21
#define EXPAND7_PORT2_DIR_INX              0x22
#define EXPAND7_PORT3_DIR_INX              0x23
#define EXPAND7_PORT4_DIR_INX              0x24
#define EXPAND7_PORT5_DIR_INX              0x25
#define EXPAND7_PORT6_DIR_INX              0x26
#define EXPAND7_PORT7_DIR_INX              0x27

#define EXPAND7_PORT0_PULL_UP_INX          0x28
#define EXPAND7_PORT0_PULL_DOWN_INX        0x29
#define EXPAND7_PORT0_OPEN_DRAIN_HIGH_INX  0x2A
#define EXPAND7_PORT0_OPEN_DRAIN_LOW_INX   0x2B
#define EXPAND7_PORT0_STRONG_INX           0x2C
#define EXPAND7_PORT0_SLOW_STRONG_INX      0x2D
#define EXPAND7_PORT0_HIGH_Z_INX           0x2E

#define EXPAND7_PORT1_PULL_UP_INX          0x2F
#define EXPAND7_PORT1_PULL_DOWN_INX        0x30
#define EXPAND7_PORT1_OPEN_DRAIN_HIGH_INX  0x31
#define EXPAND7_PORT1_OPEN_DRAIN_LOW_INX   0x32
#define EXPAND7_PORT1_STRONG_INX           0x33
#define EXPAND7_PORT1_SLOW_STRONG_INX      0x34
#define EXPAND7_PORT1_HIGH_Z_INX           0x35

#define EXPAND7_PORT2_PULL_UP_INX          0x36
#define EXPAND7_PORT2_PULL_DOWN_INX        0x37
#define EXPAND7_PORT2_OPEN_DRAIN_HIGH_INX  0x38
#define EXPAND7_PORT2_OPEN_DRAIN_LOW_INX   0x39
#define EXPAND7_PORT2_STRONG_INX           0x3A
#define EXPAND7_PORT2_SLOW_STRONG_INX      0x3B
#define EXPAND7_PORT2_HIGH_Z_INX           0x3C

#define EXPAND7_PORT3_PULL_UP_INX          0x3D
#define EXPAND7_PORT3_PULL_DOWN_INX        0x3E
#define EXPAND7_PORT3_OPEN_DRAIN_HIGH_INX  0x3F
#define EXPAND7_PORT3_OPEN_DRAIN_LOW_INX   0x40
#define EXPAND7_PORT3_STRONG_INX           0x41
#define EXPAND7_PORT3_SLOW_STRONG_INX      0x42
#define EXPAND7_PORT3_HIGH_Z_INX           0x43

#define EXPAND7_PORT4_PULL_UP_INX          0x44
#define EXPAND7_PORT4_PULL_DOWN_INX        0x45
#define EXPAND7_PORT4_OPEN_DRAIN_HIGH_INX  0x46
#define EXPAND7_PORT4_OPEN_DRAIN_LOW_INX   0x47
#define EXPAND7_PORT4_STRONG_INX           0x48
#define EXPAND7_PORT4_SLOW_STRONG_INX      0x49
#define EXPAND7_PORT4_HIGH_Z_INX           0x4A

#define EXPAND7_PORT5_PULL_UP_INX          0x4B
#define EXPAND7_PORT5_PULL_DOWN_INX        0x4C
#define EXPAND7_PORT5_OPEN_DRAIN_HIGH_INX  0x4D
#define EXPAND7_PORT5_OPEN_DRAIN_LOW_INX   0x4E
#define EXPAND7_PORT5_STRONG_INX           0x4F
#define EXPAND7_PORT5_SLOW_STRONG_INX      0x50
#define EXPAND7_PORT5_HIGH_Z_INX           0x51

#define EXPAND7_PORT6_PULL_UP_INX          0x52
#define EXPAND7_PORT6_PULL_DOWN_INX        0x53
#define EXPAND7_PORT6_OPEN_DRAIN_HIGH_INX  0x54
#define EXPAND7_PORT6_OPEN_DRAIN_LOW_INX   0x55
#define EXPAND7_PORT6_STRONG_INX           0x56
#define EXPAND7_PORT6_SLOW_STRONG_INX      0x57
#define EXPAND7_PORT6_HIGH_Z_INX           0x58

#define EXPAND7_PORT7_PULL_UP_INX          0x59
#define EXPAND7_PORT7_PULL_DOWN_INX        0x5A
#define EXPAND7_PORT7_OPEN_DRAIN_HIGH_INX  0x5B
#define EXPAND7_PORT7_OPEN_DRAIN_LOW_INX   0x5C
#define EXPAND7_PORT7_STRONG_INX           0x5D
#define EXPAND7_PORT7_SLOW_STRONG_INX      0x5E
#define EXPAND7_PORT7_HIGH_Z_INX           0x5F

#define EXPAND7_PWM0_CFG_INX               0x60
#define EXPAND7_PWM0_PERIOD_INX            0x61
#define EXPAND7_PWM0_PULSE_WIDTH_INX       0x62

#define EXPAND7_PWM1_CFG_INX               0x63
#define EXPAND7_PWM1_PERIOD_INX            0x64
#define EXPAND7_PWM1_PULSE_WIDTH_INX       0x65

#define EXPAND7_PWM2_CFG_INX               0x66
#define EXPAND7_PWM2_PERIOD_INX            0x67
#define EXPAND7_PWM2_PULSE_WIDTH_INX       0x68

#define EXPAND7_PWM3_CFG_INX               0x69
#define EXPAND7_PWM3_PERIOD_INX            0x6A
#define EXPAND7_PWM3_PULSE_WIDTH_INX       0x6B

#define EXPAND7_PWM4_CFG_INX               0x6C
#define EXPAND7_PWM4_PERIOD_INX            0x6D
#define EXPAND7_PWM4_PULSE_WIDTH_INX       0x6E

#define EXPAND7_PWM5_CFG_INX               0x6F
#define EXPAND7_PWM5_PERIOD_INX            0x70
#define EXPAND7_PWM5_PULSE_WIDTH_INX       0x71

#define EXPAND7_PWM6_CFG_INX               0x72
#define EXPAND7_PWM6_PERIOD_INX            0x73
#define EXPAND7_PWM6_PULSE_WIDTH_INX       0x74

#define EXPAND7_PWM7_CFG_INX               0x75
#define EXPAND7_PWM7_PERIOD_INX            0x76
#define EXPAND7_PWM7_PULSE_WIDTH_INX       0x77

#define EXPAND7_PWM8_CFG_INX               0x78
#define EXPAND7_PWM8_PERIOD_INX            0x79
#define EXPAND7_PWM8_PULSE_WIDTH_INX       0x7A

#define EXPAND7_PWM9_CFG_INX               0x7B
#define EXPAND7_PWM9_PERIOD_INX            0x7C
#define EXPAND7_PWM9_PULSE_WIDTH_INX       0x7D

#define EXPAND7_PWM10_CFG_INX              0x7E
#define EXPAND7_PWM10_PERIOD_INX           0x7F
#define EXPAND7_PWM10_PULSE_WIDTH_INX      0x80

#define EXPAND7_PWM11_CFG_INX              0x81
#define EXPAND7_PWM11_PERIOD_INX           0x82
#define EXPAND7_PWM11_PULSE_WIDTH_INX      0x83

#define EXPAND7_PWM12_CFG_INX              0x84
#define EXPAND7_PWM12_PERIOD_INX           0x85
#define EXPAND7_PWM12_PULSE_WIDTH_INX      0x86

#define EXPAND7_PWM13_CFG_INX              0x87
#define EXPAND7_PWM13_PERIOD_INX           0x88
#define EXPAND7_PWM13_PULSE_WIDTH_INX      0x89

#define EXPAND7_PWM14_CFG_INX              0x8A
#define EXPAND7_PWM14_PERIOD_INX           0x8B
#define EXPAND7_PWM14_PULSE_WIDTH_INX      0x8C

#define EXPAND7_PWM15_CFG_INX              0x8D
#define EXPAND7_PWM15_PERIOD_INX           0x8E
#define EXPAND7_PWM15_PULSE_WIDTH_INX      0x8F

#define EXPAND7_DIVIDER_INX                0x90
#define EXPAND7_EEPROM_ENABLE_INX          0x91
#define EXPAND7_CRC_INX                    0x92
/** \} */
 
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief PWM Configuration
 */
typedef struct
{
    uint8_t pwm_sel;
    uint8_t clk_src;
    uint8_t period;
    uint8_t pulse_wid;
    uint8_t devider;

} expand7_pwm_cfg_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t rst;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} expand7_t;

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
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} expand7_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void expand7_cfg_setup ( expand7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param expand7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t expand7_init ( expand7_t *ctx, expand7_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function writes data to the desired register.
 */
void expand7_generic_write ( expand7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads data from the desired register.
 */
void expand7_generic_read ( expand7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write byte function
 *
 * @param ctx          Click object.
 * @param reg_adr  8-bit value that defines the register
 * @param wr_data  8-bit value that defines the input data
 *
 * Function is used to write single byte of data into user defined register.
**/
void expand7_write_byte ( expand7_t *ctx, uint8_t reg_adr, uint8_t wr_data );

/**
 * @brief Read byte function
 *
 * @param ctx          Click object.
 * @param reg_adr  8-bit value that defines the register
 *
 * @returns rx_buf 8-bit value that defines the output data
 *
 * Function is used to read single byte of data from user defined register.
**/
uint8_t expand7_read_byte ( expand7_t *ctx, uint8_t reg_adr );

/**
 * @brief Port Expander Write function
 *
 * @param ctx          Click object.
 * @param reg  8-bit register address
 * @param buf  8-bit write data
 * @param len  8-bit number of bytes
 *
 * Writes user defined number of bytes into registers defined by 8-bit register
 * address
**/
void expand7_write_port_exp ( expand7_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len );

/**
 * @brief Port Expander Read function
 *
 * @param ctx          Click object.
 * @param reg  8-bit register address
 * @param buf  8-bit read data
 * @param len  8-bit number of bytes
 *
 * Reads user defined number of bytes from registers defined by 8-bit register
 * address
**/
void expand7_read_port_exp ( expand7_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len );

/**
 * @brief Send Command function
 *
 * @param ctx          Click object.
 * @param cmd  8-bit value that defines the command
 *
 * Function is used to send the command to Command Register.
**/
void expand7_send_eeprom_cmd ( expand7_t *ctx, uint8_t cmd );

/**
 * @brief EEPROM Write function
 *
 * @param ctx          Click object.
 * @param reg  8-bit register address
 * @param wr_data  8-bit write data
 * @param len  8-bit number of bytes
 *
 * Writes user defined number of bytes into EEPROM defined by 8-bit address
**/
void expand7_write_eeprom ( expand7_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len );

/**
 * @brief EEPROM Read function
 *
 * @param ctx          Click object.
 * @param reg  8-bit register address
 * @param buf  8-bit read data
 * @param len  8-bit number of bytes
 *
 * Reads user defined number of bytes from EEPROM defined by 8-bit address
**/
void expand7_read_eeprom ( expand7_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len );

/**
 * @brief Read bit function
 *
 * @param ctx          Click object.
 * @param reg_adr  8-bit value that defines the register
 * @param bit_num  8-bit value that defines the specific bit
 *
 * @returns 8-bit value that represents the specific bit's value
 *
 * Function is used to read state of a single bit of data from user defined register.
**/
uint8_t expand7_read_bit ( expand7_t *ctx, uint8_t reg_adr, uint8_t bit_num );

/**
 * @brief Write bit function
 *
 * @param ctx          Click object.
 * @param reg_adr  8-bit value that defines the register
 * @param bit_num  8-bit value that defines the specific bit
 * @param pin_val  8-bit value that defines the specific bit's value
 *
 * Function is used to set or clear the specific bit.
**/
void expand7_write_bit ( expand7_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val );

/**
 * @brief Get a single INPUT pin's logic level function
 *
 * @param ctx          Click object.
 * @param pin  16-bit value that defines the specific pin
 *
 * @returns 8-bit value that represents the specific pin's state
 *
 * Function is used to read the state of a defined pin.
**/
uint8_t expand7_read_pin ( expand7_t *ctx, uint8_t pin, uint8_t inv );

/**
 * @brief Get all pin logic levels from one port function
 *
 * @param ctx          Click object.
 * @param port 8-bit value that defines the port
 *
 * @returns 8-bit value that represents the states of pins in selected port.
 *
 * Function is used to read the states of pins in selected port.
**/
uint8_t expand7_read_port ( expand7_t *ctx, uint8_t port, uint8_t inv );

/**
 * @brief Get a single OUTPUT pin's setting function
 *
 * @param ctx          Click object.
 * @param pin  8-bit value that defines the specific pin
 *
 * @returns Pin output setting (0 or 1)
 *
 * Function is used to get a single OUTPUT pin's setting.
**/
uint8_t expand7_get_pin_out_lvl ( expand7_t *ctx, uint8_t pin );

/**
 * @brief Get all pin output settings from one port function
 *
 * @param ctx          Click object.
 * @param port 8-bit value that defines the port
 *
 * @returns Pin output setting (0 or 1)
 *
 * Function is used to get all pin output settings from one port.
**/
uint8_t expand7_get_port_out_lvl ( expand7_t *ctx, uint8_t port );

/**
 * @brief Set a single OUTPUT pin's logic level function
 *
 * @param ctx          Click object.
 * @param pin 8-bit value that defines the specific pin
 * @param pin_val 8-bit value that defines the specific pin's value
 *
 * Function is used to set a single output pin's logic level.
**/
void expand7_write_pin ( expand7_t *ctx, uint8_t pin, uint8_t pin_val );

/**
 * @brief Set all OUTPUT pins' logic levels in one port function
 *
 * @param ctx          Click object.
 * @param port  8-bit value that defines which port to write to.
 * @param value  8-bit value that defines pins' output logic level (0 or 1 for each pin).
 *
 * Function is used to set logic levels in one port.
**/
void expand7_write_port ( expand7_t *ctx, uint8_t port, uint8_t value );

/**
 * @brief  Set all OUTPUT pins' logic levels function
 *
 * @param ctx          Click object.
 * @param value  8-bit value that defines pins' output logic level (0 or 1 for each pin).
 *
 * Function is used to set logic levels of all ouptut pins.
 * @note Since only four pins of ports 2 and 5 are used only the lower nibble 
 * of the input value is used.
**/
void expand7_write_all ( expand7_t *ctx, uint8_t value );

/**
 * @brief Select a PWM output pin function
 *
 * @param ctx          Click object.
 * @param port  8-bit value that defines PWM output pin.
 * @param value  8-bit value that enables or disables PWM output (0 or 1 for each pin).
 *
 * Function is used to enable or disable PWM output on a specific pin.
**/
void expand7_sel_pwm_pin ( expand7_t *ctx, uint8_t pin, uint8_t pwm_en );

/**
 * @brief PWM Configuration function
 *
 * @param ctx          Click object.
 * @param expand7_pwm_cfg_t  structure where PWM Configuration data are stored.
 * @param duty_cyc  float value representing PWM duty cycle
 * @param freq  float value representing output frequency
 *
 * Function is used to configure PWM output.
**/
void expand7_pwm_cfg ( expand7_t *ctx, expand7_pwm_cfg_t pwm_cfg, float *duty_cyc, float *freq );

/**
 * @brief Enable Register Configuration function
 *
 * @param ctx          Click object.
 * @param cmd value that represents input data to Enable Register
 *
 * Function is used to write to Enable Register.
 * @note Writes to this register differ from other registers,
 * consult datasheet for further information.
**/
void expand7_eeprom_enable ( expand7_t *ctx, uint8_t cmd );

/**
 * @brief Reset function
 *
 * @param ctx          Click object.
 * 
 * Function is used to reset the device.
 * @note Functon holds two 100 ms reset delays.
**/
void expand7_reset ( expand7_t *ctx );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx          Click object.
 * 
 * @return
 * - 0 : Interrupt has not occured
 * - 1 : Interrupt has occured
 *
 * Function is used to check if an interrupt has occured.
**/
uint8_t expand7_check_int ( expand7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _EXPAND7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

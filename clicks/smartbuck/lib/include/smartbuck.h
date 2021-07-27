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
 * \brief This file contains API for SMART BUCK Click driver.
 *
 * \addtogroup smartbuck SMART BUCK Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SMARTBUCK_H
#define SMARTBUCK_H

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
#define SMARTBUCK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.pg  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SMARTBUCK_RETVAL  uint8_t
#define SMARTBUCK_OK           0x00
#define SMARTBUCK_INIT_ERROR   0xFF
/** \} */
/**
 * \defgroup module_slave_address Module Slave Addresses
 * \{
 */
#define SMARTBUCK_EEPROM_SLAVE_000                   0x50
#define SMARTBUCK_EEPROM_SLAVE_001                   0x51
#define SMARTBUCK_EEPROM_SLAVE_010                   0x52
#define SMARTBUCK_EEPROM_SLAVE_011                   0x53
#define SMARTBUCK_EEPROM_SLAVE_100                   0x54
#define SMARTBUCK_EEPROM_SLAVE_101                   0x55
#define SMARTBUCK_EEPROM_SLAVE_110                   0x56
#define SMARTBUCK_EEPROM_SLAVE_111                   0x57
#define SMARTBUCK_MCP4661_SLAVE_000                  0x28
#define SMARTBUCK_MCP4661_SLAVE_001                  0x29
#define SMARTBUCK_MCP4661_SLAVE_010                  0x2A
#define SMARTBUCK_MCP4661_SLAVE_011                  0x2B
#define SMARTBUCK_MCP4661_SLAVE_100                  0x2C
#define SMARTBUCK_MCP4661_SLAVE_101                  0x2D
#define SMARTBUCK_MCP4661_SLAVE_110                  0x2E
#define SMARTBUCK_MCP4661_SLAVE_111                  0x2F
#define SMARTBUCK_PAC1934_SLAVE_0                    0x10
#define SMARTBUCK_PAC1934_SLAVE_1                    0x1F
/** \} */
/**
 * \defgroup reg_address_for_mcp4661 Register addresses for MCP4661
 * \{
 */
#define SMARTBUCK_WIPER0_VOL_REG                     0x00
#define SMARTBUCK_WIPER1_VOL_REG                     0x01
#define SMARTBUCK_WIPER0_NONVOL_REG                  0x02
#define SMARTBUCK_WIPER1_NONVOL_REG                  0x03
#define SMARTBUCK_POT_TCON_VOL_REG                   0x04
#define SMARTBUCK_POT_STATUS_REG                     0x05
/** \} */
/**
 * \defgroup wiper_position Wiper position 
 * \{
 */
#define SMARTBUCK_WIPER_FULL_SCALE                  0x100
#define SMARTBUCK_WIPER_HALF_SCALE                  0x080
#define SMARTBUCK_WIPER_QUARTER_SCALE               0x040
#define SMARTBUCK_WIPER_FULL_PER_8_SCALE            0x020
#define SMARTBUCK_WIPER_ZERO_SCALE                  0x000
/** \} */
/**
 * \defgroup tcon_options Options for TCON ( MCP4661 ) 
 * \{
 */
#define SMARTBUCK_TCON_GENCALL_EN                   0x100
#define SMARTBUCK_TCON_R1HW_SHDWN_EN                0x080
#define SMARTBUCK_TCON_R1A_CONNECT                  0x040
#define SMARTBUCK_TCON_R1W_CONNECT                  0x020
#define SMARTBUCK_TCON_R1B_CONNECT                  0x010
#define SMARTBUCK_TCON_R0HW_SHDWN_EN                0x008
#define SMARTBUCK_TCON_R0A_CONNECT                  0x004
#define SMARTBUCK_TCON_R0W_CONNECT                  0x002
#define SMARTBUCK_TCON_R0B_CONNECT                  0x001
/** \} */
/**
 * \defgroup pac_address_cmd Register addresses and commands for PAC1934
 * \{
 */
#define SMARTBUCK_REFRESH_CMND                      0x00
#define SMARTBUCK_PAC_CTRL_REG                      0x01
#define SMARTBUCK_PAC_ACC_COUNT_REG                 0x02
#define SMARTBUCK_PAC_VPOW1_ACC_REG                 0x03
#define SMARTBUCK_PAC_VPOW2_ACC_REG                 0x04
#define SMARTBUCK_PAC_VPOW3_ACC_REG                 0x05
#define SMARTBUCK_PAC_VPOW4_ACC_REG                 0x06
#define SMARTBUCK_PAC_VBUS1_REG                     0x07
#define SMARTBUCK_PAC_VBUS2_REG                     0x08
#define SMARTBUCK_PAC_VBUS3_REG                     0x09
#define SMARTBUCK_PAC_VBUS4_REG                     0x0A
#define SMARTBUCK_PAC_VSENSE1_REG                   0x0B
#define SMARTBUCK_PAC_VSENSE2_REG                   0x0C
#define SMARTBUCK_PAC_VSENSE3_REG                   0x0D
#define SMARTBUCK_PAC_VSENSE4_REG                   0x0E
#define SMARTBUCK_PAC_VBUS1_AVG_REG                 0x0F
#define SMARTBUCK_PAC_VBUS2_AVG_REG                 0x10
#define SMARTBUCK_PAC_VBUS3_AVG_REG                 0x11
#define SMARTBUCK_PAC_VBUS4_AVG_REG                 0x12
#define SMARTBUCK_PAC_VSENSE1_AVG_REG               0x13
#define SMARTBUCK_PAC_VSENSE2_AVG_REG               0x14
#define SMARTBUCK_PAC_VSENSE3_AVG_REG               0x15
#define SMARTBUCK_PAC_VSENSE4_AVG_REG               0x16
#define SMARTBUCK_PAC_VPOW1_REG                     0x17
#define SMARTBUCK_PAC_VPOW2_REG                     0x18
#define SMARTBUCK_PAC_VPOW3_REG                     0x19
#define SMARTBUCK_PAC_VPOW4_REG                     0x1A
#define SMARTBUCK_PAC_CHANN_DIS_REG                 0x1C
#define SMARTBUCK_PAC_NEG_PWR_REG                   0x1D
#define SMARTBUCK_REFRESH_G_CMND                    0x1E
#define SMARTBUCK_REFRESH_V_CMND                    0x1F
#define SMARTBUCK_PAC_SLOW_REG                      0x20
#define SMARTBUCK_PAC_CTRL_STAT_REG                 0x21
#define SMARTBUCK_PAC_CHANN_DIS_STAT_REG            0x22
#define SMARTBUCK_PAC_NEG_PWR_STAT_REG              0x23
#define SMARTBUCK_PAC_CTRL_LATCH_REG                0x24
#define SMARTBUCK_PAC_CHANN_DIS_LATCH_REG           0x25
#define SMARTBUCK_PAC_NEG_PWR_LATCH_REG             0x26
#define SMARTBUCK_PAC_PID_REG                       0xFD
#define SMARTBUCK_PAC_MANU_ID_REG                   0xFE
#define SMARTBUCK_PAC_REV_ID_REG                    0xFF
/** \} */
/**
 * \defgroup pac_control_register PAC1934 Control register
 * \{
 */
#define SMARTBUCK_PAC_1024_SAMPL                     0x00
#define SMARTBUCK_PAC_256_SAMPL                      0x40
#define SMARTBUCK_PAC_64_SAMPL                       0x80
#define SMARTBUCK_PAC_8_SAMPL                        0xC0
#define SMARTBUCK_PAC_SLEEP_MODE                     0x20
#define SMARTBUCK_PAC_SEQUENTIAL_MODE                0x00
#define SMARTBUCK_PAC_SINGLE_SHOT_MODE               0x10
#define SMARTBUCK_PAC_ALERT_PIN_EN                   0x0C
#define SMARTBUCK_PAC_OVF_ALERT_EN                   0x02
/** \} */
/**
 * \defgroup driver_functions Options for driver functions
 * \{
 */
#define SMARTBUCK_WIPER0_SEL                         0x00
#define SMARTBUCK_WIPER1_SEL                         0x01
#define SMARTBUCK_REGULATOR_DIS                      0x00
#define SMARTBUCK_REGULATOR_EN                       0x01
#define SMARTBUCK_AUTO_TRICKLE_MODE                  0x01
#define SMARTBUCK_FORCE_PWM_MODE                     0x00
#define SMARTBUCK_ALL_CHANN_OFF                      0xF0
#define SMARTBUCK_ALL_CHANN_ON                       0x00
#define SMARTBUCK_CH1_ON                             0x70
#define SMARTBUCK_CH2_ON                             0xB0
#define SMARTBUCK_CH3_ON                             0xD0
#define SMARTBUCK_CH4_ON                             0xE0
#define SMARTBUCK_ALL_DATA_UNSIGN_FORM               0x00
#define SMARTBUCK_ALL_DATA_SIGN_FORM                 0xFF
#define SMARTBUCK_CH1_VSENSE_SIGN_FORM               0x80
#define SMARTBUCK_CH2_VSENSE_SIGN_FORM               0x40
#define SMARTBUCK_CH3_VSENSE_SIGN_FORM               0x20
#define SMARTBUCK_CH4_VSENSE_SIGN_FORM               0x10
#define SMARTBUCK_CH1_VBUS_SIGN_FORM                 0x08
#define SMARTBUCK_CH2_VBUS_SIGN_FORM                 0x04
#define SMARTBUCK_CH3_VBUS_SIGN_FORM                 0x02
#define SMARTBUCK_CH4_VBUS_SIGN_FORM                 0x01
#define SMARTBUCK_SAMPL_DATA_MODE                    0x00
#define SMARTBUCK_AVRG_DATA_MODE                     0x01
/** \} */
/**
 * \defgroup pac_address_cmd Register addresses and commands for PAC1934
 * \{
 */
#define SMARTBUCK_POT_WRITE_CMND                     0x00
#define SMARTBUCK_POT_INCR_CMND                      0x04
#define SMARTBUCK_POT_DECR_CMND                      0x08
#define SMARTBUCK_POT_READ_CMND                      0x0C
#define SMARTBUCK_PAC_GENERAL_CALL_SLAVE             0x00
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/** This variable checks which channel is enabled */
extern uint8_t enabled_chann;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en1;
    digital_out_t en2;
    digital_out_t pwm;

    // Input pins 

    digital_in_t pg;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_eeprom;
    uint8_t slave_mcp4661;
    uint8_t slave_pac1934;

    uint8_t enabled_chann;
    uint8_t data_form;
    uint8_t data_select;

} smartbuck_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en1;
    pin_name_t en2;
    pin_name_t pwm;
    pin_name_t pg;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address_eeprom;
    uint8_t i2c_address_mcp4661;
    uint8_t i2c_address_pac1934;

} smartbuck_cfg_t;

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
void smartbuck_cfg_setup ( smartbuck_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SMARTBUCK_RETVAL smartbuck_init ( smartbuck_t *ctx, smartbuck_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for SMARTBUCK click.
 */
void smartbuck_default_cfg ( smartbuck_t *ctx );

/**
 * @brief EEPROM Write function
 *
 * @param ctx          Click object.
 * @param eeprom_addr  Address where data be written
 * @param data_in  Data to be written
 *
 * @returns 0 - OK, 1 - Wrong EEPROM address
 *
 * Function writes one byte to the EEPROM.
 */
uint8_t smartbuck_write_eeprom( smartbuck_t *ctx, uint8_t eeprom_addr, uint8_t data_in );

/**
 * @brief EEPROM Read function
 *
 * @param ctx          Click object.
 * @param eeprom_addr  Address which from data be read
 * @param data_out  Memory where data be stored
 *
 * @returns 0 - OK, 1 - Wrong EEPROM address
 *
 * Function reads one byte from the EEPROM.
 */
uint8_t smartbuck_read_eeprom( smartbuck_t *ctx, uint8_t eeprom_addr, uint8_t *data_out );

/**
 * @brief Sequential EEPROM Read function
 *
 * @param ctx          Click object.
 * @param eeprom_addr  Start address which from data be read
 * @param data_out     Memory where data be stored
 * @param n_bytes      Number of bytes to be read
 *
 * @returns 0 - OK, 1 - Wrong EEPROM address
 *
 * Function reads the desired number of bytes from the EEPROM.
 */
uint8_t smartbuck_read_seq_eeprom( smartbuck_t *ctx, uint8_t eeprom_addr, uint8_t *data_out , uint8_t n_bytes);

/**
 * @brief Potentiometer Write function
 *
 * @param ctx          Click object.
 * @param reg_addr     Address where data be written
 * @param data_in      Data to be written
 *
 * @returns 0 - OK, 1 - Wrong register address, 2 - Wrong input data
 *
 * Function writes 16bit data to the Potentiometer register (MCP4661).
 */
uint8_t smartbuck_write_pot( smartbuck_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Potentiometer Read function
 *
 * @param ctx          Click object.
 * @param reg_addr     Address which from data be read
 * @param data_out     Memory where data be stored
 *
 * @returns 0 - OK, 1 - Wrong register address
 *
 * Function reads 16bit data from the Potentiometer register (MCP4661).
 */
uint8_t smartbuck_read_pot( smartbuck_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Potentiometer Increment function
 *
 * @param ctx          Click object.
 * @param wiper_sel    0 - Wiper0, 1 - Wiper1
 * @param steps        Determines for how many steps potentiometer be incremented
 *
 * @returns 0 - OK, 1 - Number of steps is out of range, 2 - Wrong wiper selection
 *
 * Function increments the desired wiper for the desired number of steps.
 */
uint8_t smartbuck_incr_pot( smartbuck_t *ctx, uint8_t wiper_sel, uint16_t steps );

/**
 * @brief Potentiometer Decrement function
 *
 * @param ctx          Click object.
 * @param wiper_sel    0 - Wiper0, 1 - Wiper1
 * @param steps        Determines for how many steps potentiometer be decremented
 *
 * @returns 0 - OK, 1 - Number of steps is out of range, 2 - Wrong wiper selection
 *
 * Function decrements the desired wiper for the desired number of steps.
 */
uint8_t smartbuck_decr_pot( smartbuck_t *ctx, uint8_t wiper_sel, uint16_t steps );

/**
 * @brief Regulator1 Enable function
 *
 * @param ctx          Click object.
 * @param state  0 - OFF, 1 - ON
 *
 * Function puts Regulator1 to the desired state.
 */
void smartbuck_en_regulator1 ( smartbuck_t *ctx, uint8_t state );

/**
 * @brief Regulator2 Enable function
 *
 * @param ctx          Click object.
 * @param state  0 - OFF, 1 - ON
 *
 * Function puts Regulator2 to the desired state.
 */
void smartbuck_en_regulator2 ( smartbuck_t *ctx,  uint8_t state );

/**
 * @brief PWM Mode Force function
 *
 * @param ctx          Click object.
 * @param state  0 - PWM Forced Mode, 1 - Auto Trickle Mode
 *
 * Function puts regulator to Forced PWM Mode or to Automatic Trickle Mode.
 */
void smartbuck_force_pwm_mode ( smartbuck_t *ctx, uint8_t state );

/**
 * @brief Diagnostic Check function
 *
 * @param ctx          Click object.
 * 
 * Function checks regulator diagnostic (Power Good state) and returns result.
 */
uint8_t smartbuck_check_diagnostic ( smartbuck_t *ctx );

/**
 * @brief Command Send function
 *
 * @param ctx      Click object.
 * @param command  Command to be performed
 *
 * @returns 0 - OK, 1 - Wrong command
 *
 * Function performs the desired command for PAC1934.
 */
uint8_t smartbuck_send_cmd_pac ( smartbuck_t *ctx, uint8_t command ); 

/**
 * @brief PAC1934 Write function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address where data be written
 * @param data_in   Data to be written
 *
 * @returns 0 - OK, 1 - Wrong register address
 *
 * Function writes one byte to the PAC1934 register.
 */
uint8_t smartbuck_write_pac ( smartbuck_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief PAC1934 Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address which from data be read
 * @param data_out  Memory where data be stored
 *
 * @returns 0 - OK, 1 - Wrong register address
 *
 * Function reads one byte from the PAC1934 register.
 */
uint8_t smartbuck_read_pac ( smartbuck_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief Address Pointer Set function
 *
 * @param ctx          Click object.
 * @param reg_addr     Address on which address pointer be set up
 *
 * @returns 0 - OK, 1 - Wrong register address
 *
 * Function sets internal address pointer on the desired PAC1934 register.
 */
uint8_t smartbuck_set_addr_ptr_pac ( smartbuck_t *ctx, uint8_t reg_addr );

/**
 * @brief Byte Receive function
 *
 * @param ctx          Click object.
 * @param data_out     Memory where byte be stored
 *
 * Function receives one byte from the PAC1934 address on which internal address pointer is set up.
 */
void smartbuck_receive_byte_pac ( smartbuck_t *ctx, uint8_t *data_out );

/**
 * @brief PAC1934 Block Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Start address which from data be read
 * @param data_out  Memory where data be stored
 * @param n_bytes   Number of bytes to be read
 *
 * @returns 0 - OK, 1 - Wrong register address
 *
 * Function reads the desired number of bytes from the PAC1934 registers.
 */
uint8_t smartbuck_block_read_pac( smartbuck_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief PAC1934 Configuration Set function
 *
 * @param ctx          Click object.
 * @param en_chann     Determines which channel be enabled or disabled
 * @param data_format  Determines format of data, signed or unsigned
 * @param data_sel     Selects conversion mode, one sample(0) or averaged data(1)
 *
 * @returns 0 - OK, 1 - Channel is not exist, 2 - Wrong data selection
 *
 * Function sets configuration for conversion cycle for PAC1934.
 * @note The format of enChann parameter is 0bc1c2c3c4 0000. If 'cn' is 0 that means that channel 'n' is activated.
 *       And if 'cn' is 1 that means that channel 'n' is not activated.
 *       The format of dataFormat parameter is 0bi1i2i3i4 v1v2v3v4. If 'in' is 0 that means that VSENSE for channel 'n' be unsigned.
 *       If 'in' is 1 that means that VSENSE for channel 'n' be signed. Same is for 'vn' but it applies to VBUS for channel 'n'.
 */
uint8_t smartbuck_set_config_pac ( smartbuck_t *ctx, uint8_t en_chann, uint8_t data_format, uint8_t data_sel );

/**
 * @brief Data Get function
 *
 * @param ctx      Click object.
 * @param voltage  Memory where voltage data be stored
 * @param current  Memory where current data be stored.
 * @param power    Memory where power data be stored.
 *
 * Function reads and calculates the voltage, current and power data from PAC1934 activated channels.
 * @note Results will be stored in order from 0 to the number of activated channels, and begins with channel 1.
 *       Voltage value be calculated in V unit, current in mA unit and power in mW unit.
 */
void smartbuck_get_data ( smartbuck_t *ctx,  float *voltage, float *current, float *power );

#ifdef __cplusplus
}
#endif
#endif  // _SMARTBUCK_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Oximeter Click driver.
 *
 * \addtogroup oximeter Oximeter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OXIMETER_H
#define OXIMETER_H

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
#define OXIMETER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.io0  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.io1  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OXIMETER_RETVAL  uint8_t

#define OXIMETER_OK           0x00
#define OXIMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup generic_registers Generic registers
 * \{
 */
#define OXIM_STATUS_REG                  0x00
#define OXIM_INT_MASK_REG                0x01
#define OXIM_GPIO_DRV_REG                0x02
#define OXIM_FIFO_THRESH_REG             0x06
#define OXIM_DEVID_REG                   0x08
#define OXIM_I2CS_ID_REG                 0x09
#define OXIM_CLK_RATIO_REG               0x0A
#define OXIM_GPIO_CTRL_REG               0x0B
#define OXIM_SLAVE_ADDRESS_KEY_REG       0x0D
#define OXIM_SW_RESET_REG                0x0F
#define OXIM_MODE_REG                    0x10
#define OXIM_SLOT_EN_REG                 0x11
#define OXIM_FSAMPLE_REG                 0x12
#define OXIM_PD_LED_SELECT_REG           0x14
#define OXIM_NUM_AVG_REG                 0x15
#define OXIM_SLOTA_CH1_OFFSET_REG        0x18
#define OXIM_SLOTA_CH2_OFFSET_REG        0x19
#define OXIM_SLOTA_CH3_OFFSET_REG        0x1A
#define OXIM_SLOTA_CH4_OFFSET_REG        0x1B
#define OXIM_SLOTB_CH1_OFFSET_REG        0x1E
#define OXIM_SLOTB_CH2_OFFSET_REG        0x1F
#define OXIM_SLOTB_CH3_OFFSET_REG        0x20
#define OXIM_SLOTB_CH4_OFFSET_REG        0x21
#define OXIM_ILED3_COARSE_REG            0x22
#define OXIM_ILED1_COARSE_REG            0x23
#define OXIM_ILED2_COARSE_REG            0x24
#define OXIM_ILED_FINE_REG               0x25
#define OXIM_SLOTA_LED_PULSE_REG         0x30
#define OXIM_SLOTA_NUMPULSES_REG         0x31
#define OXIM_LED_DISABLE_REG             0x34
#define OXIM_SLOTB_LED_PULSE_REG         0x35
#define OXIM_SLOTB_NUMPULSES_REG         0x36
#define OXIM_ALT_PWR_DN_REG              0x37
#define OXIM_EXT_SYNC_STARTUP_REG        0x38
#define OXIM_SLOTA_AFE_WINDOW_REG        0x39
#define OXIM_SLOTB_AFE_WINDOW_REG        0x3B
#define OXIM_AFE_PWR_CFG1_REG            0x3C
#define OXIM_SLOTA_TIA_CFG_REG           0x42
#define OXIM_SLOTA_AFE_CFG_REG           0x43
#define OXIM_SLOTB_TIA_CFG_REG           0x44
#define OXIM_SLOTB_AFE_CFG_REG           0x45
#define OXIM_SAMPLE_CLK_REG              0x4B
#define OXIM_CLK32M_ADJUST_REG           0x4D
#define OXIM_ADC_CLOCK_REG               0x4E
#define OXIM_EXT_SYNC_SEL_REG            0x4F
#define OXIM_CLK32M_CAL_EN_REG           0x50
#define OXIM_AFE_PWR_CFG2_REG            0x54
#define OXIM_TIA_INDEP_GAIN_REG          0x55
#define OXIM_DIGITAL_INT_EN_REG          0x58
#define OXIM_DIG_INT_CFG_REG             0x5A
#define OXIM_DATA_ACCESS_CTL_REG         0x5F
#define OXIM_FIFO_ACCESS_REG             0x60
#define OXIM_SLOTA_PD1_16BIT_REG         0x64
#define OXIM_SLOTA_PD2_16BIT_REG         0x65
#define OXIM_SLOTA_PD3_16BIT_REG         0x66
#define OXIM_SLOTA_PD4_16BIT_REG         0x67
#define OXIM_SLOTB_PD1_16BIT_REG         0x68
#define OXIM_SLOTB_PD2_16BIT_REG         0x69
#define OXIM_SLOTB_PD3_16BIT_REG         0x6A
#define OXIM_SLOTB_PD4_16BIT_REG         0x6B
#define OXIM_A_PD1_LOW_REG               0x70
#define OXIM_A_PD2_LOW_REG               0x71
#define OXIM_A_PD3_LOW_REG               0x72
#define OXIM_A_PD4_LOW_REG               0x73
#define OXIM_A_PD1_HIGH_REG              0x74
#define OXIM_A_PD2_HIGH_REG              0x75
#define OXIM_A_PD3_HIGH_REG              0x76
#define OXIM_A_PD4_HIGH_REG              0x77
#define OXIM_B_PD1_LOW_REG               0x78
#define OXIM_B_PD2_LOW_REG               0x79
#define OXIM_B_PD3_LOW_REG               0x7A
#define OXIM_B_PD4_LOW_REG               0x7B
#define OXIM_B_PD1_HIGH_REG              0x7C
#define OXIM_B_PD2_HIGH_REG              0x7D
#define OXIM_B_PD3_HIGH_REG              0x7E
#define OXIM_B_PD4_HIGH_REG              0x7F
/** \} */

/**
 * \defgroup enable_slot Enable Slot
 * \{
 */
#define OXIM_DIS_SLOT                    0x00
#define OXIM_EN_SLOT                     0x01
/** \} */

/**
 * \defgroup photodiode_connect Photodiode Connect
 * \{
 */
#define OXIM_NO_PHOTODIODE_CONN          0x00
#define OXIM_ALL_PHOTODIODE_CONN         0x01
#define OXIM_PD5_PD6_PD7_PD8_CONN        0x02
#define OXIM_PD1_PD2_PD3_PD4_CONN        0x03
 /** \} */

/**
* \defgroup led_enable Led enable
* \{
*/
#define OXIM_PDX_TO_AFE                  0x00
#define OXIM_LEDX1_EN                    0x01
#define OXIM_LEDX2_EN                    0x02
#define OXIM_LEDX3_EN                    0x03
#define OXIM_DIS_LED                     0x04
/** \} */

/**
* \defgroup slot_mode Slot Mode
* \{
*/
#define OXIM_SLOT_NORM_OP_MODE           0x00
#define OXIM_SLOT_DIG_INT_OP_MODE        0x01
/** \} */

/**
* \defgroup enable_channels Enable Channels
* \{
*/
#define OXIM_CH1_EN                      0x00
#define OXIM_CH2_EN                      0x01
#define OXIM_CH1_CH2_EN                  0x02
#define OXIM_CH3_CH4_EN                  0x03
#define OXIM_CH2_CH3_CH4_EN              0x04
#define OXIM_ALL_CHANN_EN                0x05
/** \} */

/**
* \defgroup result_mode Result Mode
* \{
*/
#define OXIM_AVERAGE_RES_MODE            0x00
#define OXIM_SUM_RES_MODE                0x01
/** \} */

/**
* \defgroup device_mode Device Mode
* \{
*/
#define OXIM_DEV_STANDBY_OP_MODE         0x0000
#define OXIM_DEV_PROGRAM_OP_MODE         0x0001
#define OXIM_DEV_NORMAL_OP_MODE          0x0002
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
    digital_in_t io0;

    digital_in_t io1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint8_t enabled_chann;
    uint8_t enabled_slot_a;
    uint8_t enabled_slot_b;
    uint8_t result_mode_check;

} oximeter_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t io0;
    pin_name_t io1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

    uint8_t dev_enabled_chann;
    uint8_t dev_enabled_slot_a;
    uint8_t dev_enabled_slot_b;
    uint8_t dev_result_mode_check;

} oximeter_cfg_t;

typedef struct
{
    uint8_t enable_slot;
    uint8_t enable_photodiode;
    uint8_t enable_led;
} enable_t;

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
void oximeter_cfg_setup ( oximeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OXIMETER_RETVAL oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Oximeter click.
 */
void oximeter_default_cfg ( oximeter_t *ctx );

/**
 * @brief Generic Write function
 *
 * @param ctx                        Click object.
 * @param register_address           Address where data be written
 * @param transfer_data              Data to be written
 *
 * @returns 0 - OK, 1 - Wrong address parameter
 *
 * @description Function writes 16-bit data to the register.
 */
uint8_t oxim_write_reg ( oximeter_t* ctx, uint8_t register_address,
                         uint16_t transfer_data );

/**
 * @brief Generic Read function
 *
 * @param ctx                        Click object.
 * @param register_address           Address which from data be read
 * @param data_out                   Buffer where data be stored
 * @param n_registers                Number of registers to be read
 *
 * @returns 0 - OK, 1 - Wrong address parameter, 2 - Wrong nRegisters parameter value
 *
 * @description Function reads 16-bit data from the register/registers.
 */
uint8_t oxim_read_reg ( oximeter_t* ctx, uint8_t register_address, uint16_t* data_out,
                        uint8_t n_registers );

/**
 * @brief Time Slot A Set function
 *
 * @param ctx                  Click object.
 * @param dev_enable           Structure which determines which photodiode 
 * input/inputs be connected from PD1 to PD8 and determines which LED input be
 * connected from LEDX1 to LEDX3 enable
 * @param set_mode             0 - normal operating mode, 1 - digital integration operating mode
 *
 * @returns 0 - OK, 1 - Wrong enable_photodiode parameter value, 2 - Wrong enable_led parameter value
 *
 * @description Function performs the configuration for Time Slot A and enables the interrupt for this Slot.
 */
uint8_t oxim_set_time_slot_a ( oximeter_t* ctx, enable_t* dev_enable,
                               uint8_t set_mode );

/**
 * @brief Time Slot B Set function
 *
 * @param ctx                  Click object.
 * @param dev_enable           Structure which determines which photodiode
 * input/inputs be connected from PD1 to PD8 and determines which LED input be
 * connected from LEDX1 to LEDX3 enable
 * @param set_mode             0 - normal operating mode, 1 - digital integration operating mode
 *
 * @returns 0 - OK, 1 - Wrong enable_photodiode parameter value, 2 - Wrong enable_led parameter value
 *
 * @description Function performs the configuration for Time Slot B and enables the interrupt for this Slot.
 */
uint8_t oxim_set_time_slot_b ( oximeter_t* ctx, enable_t* dev_enable, uint8_t set_mode );

/**
 * @brief Channels Enable function
 *
 * @param ctx                  Click object.
 * @param select_channel       Determines which channel/channels be enabled from CH1 to CH4
 *
 * @returns 0 - OK, 1 - Wrong selectChannel parameter value
 *
 * @description Function determines which channel/channels be enabled.
 */
uint8_t oxim_enable_channels ( oximeter_t* ctx, uint8_t select_channel );

/**
 * @brief Data Read function
 *
 * @param ctx                    Click object.
 * @param chann_results          Buffer where results be stored
 * @param result_mode            0 - average results, 1 - sum results
 *
 * @description Function reads data in the desired mode for determined Slot.
 */
void oxim_read_data ( oximeter_t* ctx, uint32_t* chann_results, uint8_t result_mode );

/**
 * @brief GPIO0 Interrupt Get function
 *
 * @param ctx                    Click object.
 *
 * @returns The state of the GPIO0 pin.
 *
 * @description Function checks the state of the GPIO0 pin.
 */
uint8_t oxim_get_interr_gpio0 ( oximeter_t* ctx );

/**
 * @brief GPIO1 Interrupt Get function
 *
 * @param ctx                    Click object.
 *
 * @returns The state of the GPIO1 pin.
 *
 * @description Function checks the state of the GPIO1 pin.
 */
uint8_t oxim_get_interr_gpio1 ( oximeter_t* ctx );

/**
 * @brief Reset function
 *
 * @param ctx                    Click object.
 *
 * @description Function performs the SW reset of the device and waits until the device returns back to normal state.
 */
void oxim_reset ( oximeter_t* ctx );

/**
 * @brief Mode Set function
 *
 * @param ctx           Click object.
 * @param select_mode   0 - Standby Mode, 1 - Program Mode, 2 - Normal OP Mode
 *
 * @returns 0 - OK, 1 - Wrong selectMode parameter value
 *
 * @description Function puts the device to desired operating mode.
 */
uint8_t oxim_set_mode ( oximeter_t* ctx, uint16_t select_mode );

#ifdef __cplusplus
}
#endif
#endif  // _OXIMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

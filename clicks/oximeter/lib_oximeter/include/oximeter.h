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
#define OXIMETER_OK                         0
#define OXIMETER_ERROR                     -1
/** \} */

/**
 * \defgroup generic_registers Generic registers
 * \{
 */
#define OXIMETER_REG_STATUS                 0x00
#define OXIMETER_REG_INT_MASK               0x01
#define OXIMETER_REG_GPIO_DRV               0x02
#define OXIMETER_REG_FIFO_THRESH            0x06
#define OXIMETER_REG_DEVID                  0x08
#define OXIMETER_REG_I2CS_ID                0x09
#define OXIMETER_REG_CLK_RATIO              0x0A
#define OXIMETER_REG_GPIO_CTRL              0x0B
#define OXIMETER_REG_SLAVE_ADDRESS_KEY      0x0D
#define OXIMETER_REG_SW_RESET               0x0F
#define OXIMETER_REG_MODE                   0x10
#define OXIMETER_REG_SLOT_EN                0x11
#define OXIMETER_REG_FSAMPLE                0x12
#define OXIMETER_REG_PD_LED_SELECT          0x14
#define OXIMETER_REG_NUM_AVG                0x15
#define OXIMETER_REG_SLOTA_CH1_OFFSET       0x18
#define OXIMETER_REG_SLOTA_CH2_OFFSET       0x19
#define OXIMETER_REG_SLOTA_CH3_OFFSET       0x1A
#define OXIMETER_REG_SLOTA_CH4_OFFSET       0x1B
#define OXIMETER_REG_SLOTB_CH1_OFFSET       0x1E
#define OXIMETER_REG_SLOTB_CH2_OFFSET       0x1F
#define OXIMETER_REG_SLOTB_CH3_OFFSET       0x20
#define OXIMETER_REG_SLOTB_CH4_OFFSET       0x21
#define OXIMETER_REG_ILED3_COARSE           0x22
#define OXIMETER_REG_ILED1_COARSE           0x23
#define OXIMETER_REG_ILED2_COARSE           0x24
#define OXIMETER_REG_ILED_FINE              0x25
#define OXIMETER_REG_SLOTA_LED_PULSE        0x30
#define OXIMETER_REG_SLOTA_NUMPULSES        0x31
#define OXIMETER_REG_LED_DISABLE            0x34
#define OXIMETER_REG_SLOTB_LED_PULSE        0x35
#define OXIMETER_REG_SLOTB_NUMPULSES        0x36
#define OXIMETER_REG_ALT_PWR_DN             0x37
#define OXIMETER_REG_EXT_SYNC_STARTUP       0x38
#define OXIMETER_REG_SLOTA_AFE_WINDOW       0x39
#define OXIMETER_REG_SLOTB_AFE_WINDOW       0x3B
#define OXIMETER_REG_AFE_PWR_CFG1           0x3C
#define OXIMETER_REG_SLOTA_TIA_CFG          0x42
#define OXIMETER_REG_SLOTA_AFE_CFG          0x43
#define OXIMETER_REG_SLOTB_TIA_CFG          0x44
#define OXIMETER_REG_SLOTB_AFE_CFG          0x45
#define OXIMETER_REG_SAMPLE_CLK             0x4B
#define OXIMETER_REG_CLK32M_ADJUST          0x4D
#define OXIMETER_REG_ADC_CLOCK              0x4E
#define OXIMETER_REG_EXT_SYNC_SEL           0x4F
#define OXIMETER_REG_CLK32M_CAL_EN          0x50
#define OXIMETER_REG_AFE_PWR_CFG2           0x54
#define OXIMETER_REG_TIA_INDEP_GAIN         0x55
#define OXIMETER_REG_DIGITAL_INT_EN         0x58
#define OXIMETER_REG_DIG_INT_CFG            0x5A
#define OXIMETER_REG_DATA_ACCESS_CTL        0x5F
#define OXIMETER_REG_FIFO_ACCESS            0x60
#define OXIMETER_REG_SLOTA_PD1_16BIT        0x64
#define OXIMETER_REG_SLOTA_PD2_16BIT        0x65
#define OXIMETER_REG_SLOTA_PD3_16BIT        0x66
#define OXIMETER_REG_SLOTA_PD4_16BIT        0x67
#define OXIMETER_REG_SLOTB_PD1_16BIT        0x68
#define OXIMETER_REG_SLOTB_PD2_16BIT        0x69
#define OXIMETER_REG_SLOTB_PD3_16BIT        0x6A
#define OXIMETER_REG_SLOTB_PD4_16BIT        0x6B
#define OXIMETER_REG_A_PD1_LOW              0x70
#define OXIMETER_REG_A_PD2_LOW              0x71
#define OXIMETER_REG_A_PD3_LOW              0x72
#define OXIMETER_REG_A_PD4_LOW              0x73
#define OXIMETER_REG_A_PD1_HIGH             0x74
#define OXIMETER_REG_A_PD2_HIGH             0x75
#define OXIMETER_REG_A_PD3_HIGH             0x76
#define OXIMETER_REG_A_PD4_HIGH             0x77
#define OXIMETER_REG_B_PD1_LOW              0x78
#define OXIMETER_REG_B_PD2_LOW              0x79
#define OXIMETER_REG_B_PD3_LOW              0x7A
#define OXIMETER_REG_B_PD4_LOW              0x7B
#define OXIMETER_REG_B_PD1_HIGH             0x7C
#define OXIMETER_REG_B_PD2_HIGH             0x7D
#define OXIMETER_REG_B_PD3_HIGH             0x7E
#define OXIMETER_REG_B_PD4_HIGH             0x7F
/** \} */

/**
 * \defgroup enable_slot Enable Slot
 * \{
 */
#define OXIMETER_DIS_SLOT                   0x00
#define OXIMETER_EN_SLOT                    0x01
/** \} */

/**
 * \defgroup photodiode_connect Photodiode Connect
 * \{
 */
#define OXIMETER_NO_PHOTODIODE_CONN         0x00
#define OXIMETER_ALL_PHOTODIODE_CONN        0x01
#define OXIMETER_PD5_PD6_PD7_PD8_CONN       0x02
#define OXIMETER_PD1_PD2_PD3_PD4_CONN       0x03
 /** \} */

/**
* \defgroup led_enable Led enable
* \{
*/
#define OXIMETER_PDX_TO_AFE                 0x00
#define OXIMETER_LEDX1_EN                   0x01
#define OXIMETER_LEDX2_EN                   0x02
#define OXIMETER_LEDX3_EN                   0x03
#define OXIMETER_DIS_LED                    0x04
/** \} */

/**
* \defgroup slot_mode Slot Mode
* \{
*/
#define OXIMETER_SLOT_NORM_OP_MODE          0x00
#define OXIMETER_SLOT_DIG_INT_OP_MODE       0x01
/** \} */

/**
* \defgroup enable_channels Enable Channels
* \{
*/
#define OXIMETER_CH1_EN                     0x00
#define OXIMETER_CH2_EN                     0x01
#define OXIMETER_CH1_CH2_EN                 0x02
#define OXIMETER_CH3_CH4_EN                 0x03
#define OXIMETER_CH2_CH3_CH4_EN             0x04
#define OXIMETER_ALL_CHANN_EN               0x05
/** \} */

/**
* \defgroup result_mode Result Mode
* \{
*/
#define OXIMETER_AVERAGE_RES_MODE           0x00
#define OXIMETER_SUM_RES_MODE               0x01
/** \} */

/**
* \defgroup device_mode Device Mode
* \{
*/
#define OXIMETER_DEV_STANDBY_OP_MODE        0x0000
#define OXIMETER_DEV_PROGRAM_OP_MODE        0x0001
#define OXIMETER_DEV_NORMAL_OP_MODE         0x0002
/** \} */

/**
* \defgroup slave_address Device slave address
* \{
*/
#define OXIMETER_DEVICE_ADDRESS             0x64
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
    
} oximeter_enable_t;

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
void oximeter_cfg_setup ( oximeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for Oximeter click.
 */
void oximeter_default_cfg ( oximeter_t *ctx );

/**
 * @brief Generic Write function
 *
 * @param ctx           Click object.
 * @param reg           Address where data be written
 * @param data_in       Data to be written
 *
 * @returns 0 - OK, -1 - Wrong address parameter
 *
 * @details Function writes 16-bit data to the register.
 */
err_t oximeter_write_reg ( oximeter_t* ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Generic Read function
 *
 * @param ctx           Click object.
 * @param reg           Address which from data be read
 * @param data_out      Buffer where data be stored
 * @param len           Number of registers to be read
 *
 * @returns 0 - OK, -1 - Wrong address parameter or Wrong len parameter value
 *
 * @details Function reads 16-bit data from the register/registers.
 */
err_t oximeter_read_reg ( oximeter_t* ctx, uint8_t reg, uint16_t* data_out, uint8_t len );

/**
 * @brief Time Slot A Set function
 *
 * @param ctx                  Click object.
 * @param dev_enable           Structure which determines which photodiode 
 * input/inputs be connected from PD1 to PD8 and determines which LED input be
 * connected from LEDX1 to LEDX3 enable
 * @param set_mode             0 - normal operating mode, 1 - digital integration operating mode
 *
 * @returns 0 - OK, -1 - Wrong enable_photodiode parameter value or Wrong enable_led parameter value
 *
 * @details Function performs the configuration for Time Slot A and enables the interrupt for this Slot.
 */
err_t oximeter_set_time_slot_a ( oximeter_t* ctx, oximeter_enable_t* dev_enable, uint8_t set_mode );

/**
 * @brief Time Slot B Set function
 *
 * @param ctx                  Click object.
 * @param dev_enable           Structure which determines which photodiode
 * input/inputs be connected from PD1 to PD8 and determines which LED input be
 * connected from LEDX1 to LEDX3 enable
 * @param set_mode             0 - normal operating mode, 1 - digital integration operating mode
 *
 * @returns 0 - OK, -1 - Wrong enable_photodiode parameter value or Wrong enable_led parameter value
 *
 * @details Function performs the configuration for Time Slot B and enables the interrupt for this Slot.
 */
err_t oximeter_set_time_slot_b ( oximeter_t* ctx, oximeter_enable_t* dev_enable, uint8_t set_mode );

/**
 * @brief Channels Enable function
 *
 * @param ctx                  Click object.
 * @param select_channel       Determines which channel/channels be enabled from CH1 to CH4
 *
 * @returns 0 - OK, -1 - Wrong select_channel parameter value
 *
 * @details Function determines which channel/channels be enabled.
 */
err_t oximeter_enable_channels ( oximeter_t* ctx, uint8_t select_channel );

/**
 * @brief Data Read function
 *
 * @param ctx                    Click object.
 * @param chann_results          Buffer where results be stored
 * @param result_mode            0 - average results, 1 - sum results
 *
 * @details Function reads data in the desired mode for determined Slot.
 */
void oximeter_read_data ( oximeter_t* ctx, uint32_t* chann_results, uint8_t result_mode );

/**
 * @brief GPIO0 Interrupt Get function
 *
 * @param ctx                    Click object.
 *
 * @returns The state of the GPIO0 pin.
 *
 * @details Function checks the state of the GPIO0 pin.
 */
uint8_t oximeter_get_int_gpio0 ( oximeter_t* ctx );

/**
 * @brief GPIO1 Interrupt Get function
 *
 * @param ctx                    Click object.
 *
 * @returns The state of the GPIO1 pin.
 *
 * @details Function checks the state of the GPIO1 pin.
 */
uint8_t oximeter_get_int_gpio1 ( oximeter_t* ctx );

/**
 * @brief Reset function
 *
 * @param ctx                    Click object.
 *
 * @details Function performs the SW reset of the device and waits until the device returns back to normal state.
 */
void oximeter_reset ( oximeter_t* ctx );

/**
 * @brief Mode Set function
 *
 * @param ctx           Click object.
 * @param select_mode   0 - Standby Mode, 1 - Program Mode, 2 - Normal OP Mode
 *
 * @returns 0 - OK, -1 - Wrong select_mode parameter value
 *
 * @details Function puts the device to desired operating mode.
 */
err_t oximeter_set_mode ( oximeter_t* ctx, uint16_t select_mode );

#ifdef __cplusplus
}
#endif
#endif  // _OXIMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

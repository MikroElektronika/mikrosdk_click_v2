/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  oximeter2.h
 * @brief This file contains API header for Oximeter2 Click driver.
 */

// ----------------------------------------------------------------------------

#ifndef _OXIMETER2_H_
#define _OXIMETER2_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/*!
 * @addtogroup oximeter2 Oximeter 2 Click Driver
 * @brief API for configuring and manipulating Oximeter 2 Click driver.
 * @{
 */

/**
 * @defgroup oximeter2_set Oximeter 2 Settings
 * @brief Settings for configuration of Oximeter 2 Click driver.
 */

/**
 * @addtogroup oximeter2_cfg
 * @{
 */

/**
 * @brief Oximeter 2 default I2C slave address.
 * @details Specified setting for reading default slave address of Oximeter 2 Click.
 */
#define OXIMETER2_SLAVE_ADDRESS 0x64

/*! @} */ // oximeter2_cfg

/**
 * @defgroup oximeter2_map Oximeter 2 mikroBUS map
 * @brief MikroBUS pin mapping of Oximeter 2 Click driver.
 */

/**
 * @addtogroup oximeter2_map
 * @{
 */

#define OXIMETER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl_pin  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda_pin  = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */   // oximeter2_map
  
/*! @} */   // oximeter2
  
  
/**
 * \defgroup error_code Error Code
 * \{
 */
#define OXIMETER2_RETVAL uint8_t

#define OXIMETER2_OK 0x00
#define OXIMETER2_INIT_ERROR 0xFF
/** \} */

/**
 * \defgroup generic_registers Generic registers
 * \{
 */
#define OXIMETER2_STATUS_REG            0x00
#define OXIMETER2_INT_MASK_REG          0x01
#define OXIMETER2_INT_IO_CTL_REG        0x02
#define OXIMETER2_FIFO_THRESH_REG       0x06
#define OXIMETER2_DEVID_REG             0x08
#define OXIMETER2_CLK_RATIO_REG         0x0A
#define OXIMETER2_MODE_REG              0x10
#define OXIMETER2_SLOT_EN_REG           0x11
#define OXIMETER2_FSAMPLE_REG           0x12
#define OXIMETER2_PD_LED_SELECT_REG     0x14
#define OXIMETER2_NUM_AVG_REG           0x15
#define OXIMETER2_SLOTA_CH1_OFFSET_REG  0x18
#define OXIMETER2_SLOTA_CH2_OFFSET_REG  0x19
#define OXIMETER2_SLOTA_CH3_OFFSET_REG  0x1A
#define OXIMETER2_SLOTA_CH4_OFFSET_REG  0x1B
#define OXIMETER2_SLOTB_CH1_OFFSET_REG  0x1E
#define OXIMETER2_SLOTB_CH2_OFFSET_REG  0x1F
#define OXIMETER2_SLOTB_CH3_OFFSET_REG  0x20
#define OXIMETER2_SLOTB_CH4_OFFSET_REG  0x21
#define OXIMETER2_ILED1_COARSE_REG      0x23
#define OXIMETER2_ILED2_COARSE_REG      0x24
#define OXIMETER2_ILED_FINE_REG         0x25
#define OXIMETER2_SLOTA_LEDMODE_REG     0x30
#define OXIMETER2_SLOTA_NUMPULSES_REG   0x31
#define OXIMETER2_LED_DISABLE_REG       0x34
#define OXIMETER2_SLOTB_LEDMODE_REG     0x35
#define OXIMETER2_SLOTB_NUMPULSES_REG   0x36
#define OXIMETER2_EXT_SYNC_STARTUP_REG  0x38
#define OXIMETER2_SLOTA_AFEMODE_REG     0x39
#define OXIMETER2_SLOTB_AFEMODE_REG     0x3B
#define OXIMETER2_SLOTA_GAIN_REG        0x42
#define OXIMETER2_SLOTA_AFE_CON_REG     0x43
#define OXIMETER2_SLOTB_GAIN_REG        0x44
#define OXIMETER2_SLOTB_AFE_CON_REG     0x45
#define OXIMETER2_SAMPLE_CLK_REG        0x4B
#define OXIMETER2_CLK32M_ADJUST_REG     0x4D
#define OXIMETER2_ADC_TIMING_REG        0x4E
#define OXIMETER2_EXT_SYNC_SEL_REG      0x4F
#define OXIMETER2_CLK32M_CAL_EN_REG     0x50
#define OXIMETER2_TIA_INDEP_GAIN_REG    0x55
#define OXIMETER2_DATA_ACCESS_CTL_REG   0x5F
#define OXIMETER2_FIFO_ACCESS           0x60
#define OXIMETER2_SLOTA_PD1_16BIT_REG   0x64
#define OXIMETER2_SLOTA_PD2_16BIT_REG   0x65
#define OXIMETER2_SLOTA_PD3_16BIT_REG   0x66
#define OXIMETER2_SLOTA_PD4_16BIT_REG   0x67
#define OXIMETER2_SLOTB_PD1_16BIT_REG   0x68
#define OXIMETER2_SLOTB_PD2_16BIT_REG   0x69
#define OXIMETER2_SLOTB_PD3_16BIT_REG   0x6A
#define OXIMETER2_SLOTB_PD4_16BIT_REG   0x6B
#define OXIMETER2_A_PD1_LOW_REG         0x70
#define OXIMETER2_A_PD2_LOW_REG         0x71
#define OXIMETER2_A_PD3_LOW_REG         0x72
#define OXIMETER2_A_PD4_LOW_REG         0x73
#define OXIMETER2_A_PD1_HIGH_REG        0x74
#define OXIMETER2_A_PD2_HIGH_REG        0x75
#define OXIMETER2_A_PD3_HIGH_REG        0x76
#define OXIMETER2_A_PD4_HIGH_REG        0x77
#define OXIMETER2_B_PD1_LOW_REG         0x78
#define OXIMETER2_B_PD2_LOW_REG         0x79
#define OXIMETER2_B_PD3_LOW_REG         0x7A
#define OXIMETER2_B_PD4_LOW_REG         0x7B
#define OXIMETER2_B_PD1_HIGH_REG        0x7C
#define OXIMETER2_B_PD2_HIGH_REG        0x7D
#define OXIMETER2_B_PD3_HIGH_REG        0x7E
#define OXIMETER2_B_PD4_HIGH_REG        0x7F

/**
 * \defgroup enable_slot Enable Slot
 * \{
 */
#define OXIMETER2_DIS_SLOT 0x00
#define OXIMETER2_EN_SLOT 0x01
/** \} */


/**
 * \defgroup device_mode Device mode
 * \{
 */
#define OXIMETER2_MODE_STANDBY 0x0000
#define OXIMETER2_MODE_PROGRAM 0x0001
#define OXIMETER2_MODE_SAMPLE 0x0002
/** \} */

/**
 * \defgroup clock_sample Clock sample
 * \{
 */
#define OXIMETER2_SAMPLE_CLK_CLK32K_EN  0x0080
/** \} */

/**
 * \defgroup register_reads Defines for register reads
 * \{
 */
#define OXIMETER2_DATA_ACCESS_CTL_SLOTA_DATA_HOLD 0x0002
#define OXIMETER2_DATA_ACCESS_CTL_SLOTB_DATA_HOLD 0x0004
/** \} */

/**
 * \defgroup led_control LED control register bits
 * \{
 */
#define SLOTA_LED_SEL_LEDX1 0x0001
#define SLOTA_LED_SEL_LEDX2 0x0002

#define SLOTB_LED_SEL_LEDX1 0x0004
#define SLOTB_LED_SEL_LEDX2 0x0008
/** \} */

/**
 * \defgroup enable_channels Enable Channels
 * \{
 */
#define OXIMETER2_ALL_CHANNELS_SELECTED 0x00
#define OXIMETER2_CH3_CH4_SELECTED 0x01
 /** \} */
 
/**
 * \defgroup led_enable Led enable
 * \{
 */
#define OXIMETER2_LEDX1_EN 0x00
#define OXIMETER2_LEDX2_EN 0x01
#define OXIMETER2_DIS_LED 0x02
/** \} */


/**
 * \defgroup photo_diode_control Photo Diode control register bits
 * \{
 */
#define SLOTA_PD_SEL_CH3_CH4 0x0010
#define SLOTA_PD_SEL_ALL_CH 0x0040
#define SLOTB_PD_SEL_CH3_CH4 0x1000
#define SLOTB_PD_SEL_ALL_CH 0x0400

/** \} */

/**
 * \defgroup enable_slot Enable Slot
 * \{
 */
#define OXIMETER2_SLOT_A_EN 0x0001
#define OXIMETER2_SLOT_B_EN 0x0020
/** \} */

/**
* \defgroup result_mode Result Mode
* \{
*/
#define OXIMETER2_AVERAGE_RES_MODE 0x00
#define OXIMETER2_SUM_RES_MODE 0x01
/** \} */

#define OXIMETER2_16_BIT_DATA_MASK 0x0000FFFF
#define OXIMETER2_CLEAR_INTERRUPTS 0x00FF
#define OXIMETER2_PREVENT_UPDATE_OF_DATA_REGS 0x0006
#define OXIMETER2_ALLOW_UPDATE_OF_DATA_REGS 0x0000

/** \} */ // End group Generic registers

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * @defgroup type Types
 * @{
 */

/**
 * @brief Oximeter 2 Click context object.
 * @details Context object definition of Oximeter 2 Click driver.
 */
typedef struct
{
    // Oximeter 2 Click employs I2C protocol.
    i2c_master_t i2c;
    
    // I2C protocol requires slave address.
    uint8_t slave_address;
    
    // Optical sensor on this Click has channels.
    uint8_t enabled_channel;
    
    // Optical sensor on this Click has Time Slots.
    uint8_t enabled_slot_a;
    uint8_t enabled_slot_b;
    
} oximeter2_t;


/**
 * @brief Oximeter 2 Click configuration object.
 * @details Configuration object definition of Oximeter 2 Click driver.
 */
typedef struct
{
    /**< I2C communication pins. */
    pin_name_t scl_pin;
    pin_name_t sda_pin;
    
    /**< I2C general settings. */
    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint8_t dev_enabled_channel;
    uint8_t dev_enabled_slot_a;
    uint8_t dev_enabled_slot_b;
    
} oximeter2_cfg_t;

/**
 * @brief Oximeter 2 hardware selector.
 * @details Structure for selection of hardware that is present on the Click.
 */
typedef struct
{
    uint8_t enable_slot;
    uint8_t enable_photodiode;
} enable_t;


/** @} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * @defgroup public_function Public function
 * @{
 */

/**
 * @brief Oximeter 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial values.
 * @param[in] *cfg: Click configuration structure.
 * @note All used pins will be set to unconnected state.
 */
void oximeter2_cfg_setup( oximeter2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @details This function initializes all necessary pins and peripherals used for this click.
 * @param[in] *ctx Click object.
 * @param[in] *cfg Click configuration structure.
 */
OXIMETER2_RETVAL oximeter2_init( oximeter2_t *ctx, oximeter2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 * @details This function executes default configuration for Oximeter 2 Click.
 * @param[in] *ctx  Click object.
 */
void oximeter2_default_cfg ( oximeter2_t *ctx );

/**
 * @brief Generic Write function.
 * @details Function writes 16-bit data to the register.
 * @param[in] *ctx Click object.
 * @param[in] register_address Register which will be written to.
 * @param[in] transfer_data Data to be written.
 * @return 0 - OK, 1 - Wrong address parameter.
 */
uint8_t oximeter2_write_reg( oximeter2_t *ctx, uint8_t register_address, uint16_t transfer_data );

/**
 * @brief Generic Read function.
 * @details Function reads 16-bit data from the register/registers.
 * @param[in] *cfg Click configuration.
 * @param[in] *register_address Register which will be read.
 * @param[out] *data_out Buffer for storing data that has been read.
 * @param[in] num_of_regs Number of registers to be read.
 * @return 0 - OK, 1 - Wrong address parameter.
 */
uint8_t oximeter2_read_reg( oximeter2_t *cfg, uint8_t register_address, uint16_t *data_out, uint8_t num_of_regs );

/**
 * @brief Time Slot A Set function
 * @details Function performs the configuration for Time Slot B.
 * @param[in] *ctx Click object.
 * @param[in] *dev_enable Structure which determines which photodiode will be connected.
 * @return 0 - OK, 1 - Wrong enable_photodiode parameter value.
 */
uint8_t oximeter2_set_time_slot_a ( oximeter2_t* ctx, enable_t* dev_enable );

/**
 * @brief Time Slot B Set function.
 * @details Function performs the configuration for Time Slot B.
 * @param[in] *ctx Click object.
 * @param[in] *dev_enable Structure which determines which photodiode will be connected.
 * @return 0 - OK, 1 - Wrong enable_photodiode parameter value.
 */
uint8_t oximeter2_set_time_slot_b ( oximeter2_t* ctx, enable_t* dev_enable );


/**
 * @brief Oximeter 2 Data Read function.
 * @details Function reads data in the desired mode for determined Slot.
 * @param[in] *ctx Click object.
 * @param[in] *channel_results Buffer where results will be stored.
 */
void oximeter2_read_data( oximeter2_t* ctx, uint32_t *channel_results );

/**
 * @brief Oximeter 2 Reset function.
 * @details Function performs the SW reset of the device and waits until the device returns back to normal state.
 * @param[in] *ctx Click object.
 */
void oximeter2_reset( oximeter2_t *ctx );

/**
 * @brief Oximeter 2 Mode Set function.
 * @details Function sets the device to desired operating mode.
 * @param[in] *ctx Click object.
 * @param[in] desired_mode 0 - Standby Mode, 1 - Program Mode, 2 - Normal Mode
 * @return 0 - OK, 1 - Wrong desired_mode parameter value.
 */
uint8_t oximeter2_set_mode( oximeter2_t *ctx, uint8_t desired_mode );

#ifdef __cplusplus
}
#endif
#endif  // _OXIMETER2_H_

/** @} */ // End public_function group
// ------------------------------------------------------------------------- END

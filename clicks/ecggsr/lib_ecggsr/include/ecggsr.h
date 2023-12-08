/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file  ecggsr.h
 * @brief This file contains API header for ECG GSR Click driver.
 */

// ----------------------------------------------------------------------------

#ifndef _ECGGSR_H_
#define _ECGGSR_H_

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
 * @addtogroup ecggsr ECG GSR Click Driver
 * @brief API for configuring and manipulating ECG GSR Click driver.
 * @{
 */ 

/**
 * @defgroup ecggsr_set ECG GSR Settings
 * @brief Settings for configuration of ECG GSR Click driver.
 */

/**
 * @addtogroup ecggsr_cfg
 * @{
 */

/**
 * @brief ECG GSR default I2C slave address.
 * @details Specified setting for reading default slave address of ECG GSR Click.
 */
#define ECGGSR_SLAVE_ADDRESS            0x30
/*! @} */ // ecggsr_cfg

/**
 * @defgroup ecggsr_map ECG GSR mikroBUS map
 * @brief MikroBUS pin mapping of ECG GSR Click driver.
 */

/**
 * @addtogroup ecggsr_map
 * @{
 */

#define ECGGSR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl_pin  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda_pin  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.enable_pin  = MIKROBUS( mikrobus, MIKROBUS_CS );
  

/*! @} */   // ecggsr_map
  
/*! @} */   // ecggsr


/*!
 * @defgroup return_value Return value
 * @{
 */
#define ECGGSR_RETVAL uint8_t
/*! @} */

/*!
 * @defgroup generic_registers Generic registers
 * @{
 */
#define ECGGSR_GPIO_SYNC_REG            0x0F
#define ECGGSR_LED_CFG_REG              0x10
#define ECGGSR_LED_WAIT_LOW_REG         0x11
#define ECGGSR_LED1_CURRL_REG           0x12
#define ECGGSR_LED1_CURRH_REG           0x13
#define ECGGSR_LED2_CURRL_REG           0x14
#define ECGGSR_LED2_CURRH_REG           0x15
#define ECGGSR_LED3_CURRL_REG           0x16
#define ECGGSR_LED3_CURRH_REG           0x17
#define ECGGSR_LED4_CURRL_REG           0x18
#define ECGGSR_LED4_CURRH_REG           0x19
#define ECGGSR_LED12_MODE_REG           0x2C
#define ECGGSR_LED34_MODE_REG           0x2D 
#define ECGGSR_MAN_SEQ_CFG_REG          0x2E
#define ECGGSR_PD_CFG_REG               0x1A
#define ECGGSR_PDOFFX_LEDOFF_REG        0x1B
#define ECGGSR_PDOFFX_LEDON_REG         0x1C
#define ECGGSR_PD_AMPRCCFG_REG          0x1D
#define ECGGSR_PD_AMPCFG_REG            0x1E
#define ECGGSR_OFE1_PD_THCFG_REG        0x1F 
#define ECGGSR_SEQ_CNT_REG              0x30 
#define ECGGSR_SEQ_DIV_REG              0x31 
#define ECGGSR_SEQ_START_REG            0x32 
#define ECGGSR_SEQ_PER_REG              0x33 
#define ECGGSR_SEQ_LED_ST_REG           0x34 
#define ECGGSR_SEQ_LED_STO_REG          0x35 
#define ECGGSR_SEQ_SECLED_STA_REG       0x36  
#define ECGGSR_SEQ_SECLED_STO_REG       0x37  
#define ECGGSR_SEQ_ITG_STA_REG          0x38 
#define ECGGSR_SEQ_ITG_STO_REG          0x39 
#define ECGGSR_SEQ_SDP1_STA_REG         0x3A 
#define ECGGSR_SEQ_SDP1_STO_REG         0x3B 
#define ECGGSR_SEQ_SDP2_STA_REG         0x3C 
#define ECGGSR_SEQ_SDP2_STO_REG         0x3D 
#define ECGGSR_SEQ_SDM1_STA_REG         0x3E 
#define ECGGSR_SEQ_SDM1_STO_REG         0x3F 
#define ECGGSR_SEQ_SDM2_STA_REG         0x40 
#define ECGGSR_SEQ_SDM2_STO_REG         0x41 
#define ECGGSR_SEQ_ADC_REG              0x42 
#define ECGGSR_SEQ_ADC2TIA_REG          0x43 
#define ECGGSR_SEQ_ADC3TIA_REG          0x44 
#define ECGGSR_SD_SUBS_REG              0x45 
#define ECGGSR_SEQ_CFG_REG              0x46 
#define ECGGSR_SEQ_ERR_REG              0x47 
#define ECGGSR_SEQ_OVS_SEL_REG          0x48
#define ECGGSR_SEQ_OVS_VAL_REG          0x49
#define ECGGSR_SEQ_DIS_SEL_REG          0x4A 
#define ECGGSR_SEQ_DIS_VAL1_REG         0x4B 
#define ECGGSR_SEQ_DIS_VAL2_REG         0x4C 
#define ECGGSR_CYC_COUNTER_REG          0x60 
#define ECGGSR_SEQ_COUNTER_REG          0x61 
#define ECGGSR_SUBS_COUNTER_REG         0x62 
#define ECGGSR_OFE_CFGA_REG             0x50 
#define ECGGSR_OFE1_SD_THCFG_REG        0x51 
#define ECGGSR_OFE_CFGC_REG             0x52 
#define ECGGSR_OFE_CFGD_REG             0x53 
#define ECGGSR_OFE1_CFGA_REG            0x54 
#define ECGGSR_OFE1_CFGB_REG            0x55 
#define ECGGSR_OFE2_PD_THCFG_REG        0x56 
#define ECGGSR_OFE2_SD_THCFG_REG        0x57 
#define ECGGSR_OFE2_CFGA_REG            0x58 
#define ECGGSR_OFE2_CFGB_REG            0x59 
#define ECGGSR_LTFDATA0_L_REG           0x20 
#define ECGGSR_LTFDATA0_H_REG           0x21 
#define ECGGSR_LTFDATA1_L_REG           0x22 
#define ECGGSR_LTFDATA1_H_REG           0x23 
#define ECGGSR_ITIME_REG                0x24 
#define ECGGSR_LTF_CONFIG_REG           0x25 
#define ECGGSR_LTF_SEL_REG              0x26 
#define ECGGSR_LTF_GAIN_REG             0x27 
#define ECGGSR_LTF_CONTROL_REG          0x28 
#define ECGGSR_AZ_CONTROL_REG           0x29 
#define ECGGSR_OFFSET0_REG              0x2A 
#define ECGGSR_OFFSET1_REG              0x2B 
#define ECGGSR_LTF_THRESHOLD_LOW0_REG   0x6C 
#define ECGGSR_LTF_THRESHOLD_LOW1_REG   0x6D 
#define ECGGSR_LTF_THRESHOLD_HIGH0_REG  0x6E  
#define ECGGSR_LTF_THRESHOLD_HIGH1_REG  0x6F  
#define ECGGSR_EAF_CFG_REG              0x70 
#define ECGGSR_EAF_GST_REG              0x80 
#define ECGGSR_EAF_BIAS_REG             0x81 
#define ECGGSR_EAF_DAC_REG              0x82 
#define ECGGSR_EAF_DAC1_L_REG           0x83 
#define ECGGSR_EAF_DAC1_H_REG           0x84 
#define ECGGSR_EAF_DAC2_L_REG           0x85 
#define ECGGSR_EAF_DAC2_H_REG           0x86 
#define ECGGSR_EAF_DAC_CFG_REG          0x87 
#define ECGGSR_OFE_NOTCH_REG            0x5A 
#define ECGGSR_ECG_MODE_REG             0x5B 
#define ECGGSR_ECG_CFGA_REG             0x5C 
#define ECGGSR_ECG_CFGB_REG             0x5D 
#define ECGGSR_ECG_THRESHOLD_LOW_REG    0x6A 
#define ECGGSR_ECG_THRESHOLD_HIGH_REG   0x6B 
#define ECGGSR_ECG_CFGC_REG             0x5E 
#define ECGGSR_ECG_CFGD_REG             0x5F 
#define ECGGSR_ADC_THRESHOLD_REG        0x68 
#define ECGGSR_ADC_THRESHOLD_CFG_REG    0x69 
#define ECGGSR_ADC_CFGA_REG             0x88 
#define ECGGSR_ADC_CFGB_REG             0x89 
#define ECGGSR_ADC_CFGC_REG             0x8A 
#define ECGGSR_ADC_CHANNEL_MASK_L_REG   0x8B  
#define ECGGSR_ADC_CHANNEL_MASK_H_REG   0x8C  
#define ECGGSR_ADC_DATA_L_REG           0x8E 
#define ECGGSR_ADC_DATA_H_REG           0x8F 
#define ECGGSR_FIFO_CFG_REG             0x78 
#define ECGGSR_FIFO_CNTRL_REG           0x79 
#define ECGGSR_FIFOL_REG                0xFE 
#define ECGGSR_FIFOH_REG                0xFF 
#define ECGGSR_CONTROL_REG              0x00 
#define ECGGSR_GPIO_A_REG               0x08 
#define ECGGSR_GPIO_E_REG               0x09 
#define ECGGSR_GPIO_O_REG               0x0A 
#define ECGGSR_GPIO_I_REG               0x0B 
#define ECGGSR_GPIO_P_REG               0x0C 
#define ECGGSR_GPIO_SR_REG              0x0D 
#define ECGGSR_SUBID_REG                0x91 
#define ECGGSR_ID_REG                   0x92 
#define ECGGSR_STATUS_REG               0xA0 
#define ECGGSR_STATUS2_REG              0xA1 
#define ECGGSR_CLIPSTATUS_REG           0xA2 
#define ECGGSR_LEDSTATUS_REG            0xA3 
#define ECGGSR_FIFOSTATUS_REG           0xA4 
#define ECGGSR_LTFSTATUS_REG            0xA5 
#define ECGGSR_FIFOLEVEL_REG            0xA6 
#define ECGGSR_INTENAB_REG              0xA8 
#define ECGGSR_INTENAB2_REG             0xA9 
#define ECGGSR_INTR_REG                 0xAA 
#define ECGGSR_INTR2_REG                0xAB 

#define ECGGSR_DEV_ID_MASK              0xFC
#define ECGGSR_DEV_ID                   0x54


// 35mA current flows through LEDs.
#define ECGGSR_LED_CURR_LOW_2           0x80
#define ECGGSR_LED_CURR_HIGH_2          0x59


// 100mA current flows through LEDs.
#define ECGGSR_LED_CURR_LOW_3           0xC0
#define ECGGSR_LED_CURR_HIGH_3          0xFF

// PPG related definitions.
#define ECGGSR_ENABLE_OSC_AND_LDO       0x03
#define ECGGSR_READ_VALUE_CONTROL_REG   0x83
#define ECGGSR_ENABLE_REF_AND_DIODES    0x8B
#define ECGGSR_ENABLE_LED12_OUTPUT      0x99
#define ECGGSR_ENABLE_LED4_OUTPUT       0x90
#define ECGGSR_CONF_PHOTODIODE          0x3E
#define ECGGSR_SUNLIGHT_COMPENSATION    0x5E
#define ECGGSR_FEEDBACK_RESISTOR        0xE2
#define ECGGSR_ENABLE_PHOTOAMPLIFIER    0xBC
#define ECGGSR_START_PPG                0xE1
#define ECGGSR_ENABLE_ADC               0x01
#define ECGGSR_START_ADC_CONVERSION     0x01
#define ECGGSR_ENABLE_OFE_AND_BIAS      0xE6
#define ECGGSR_OFE1_CFGA                0x70
#define ECGGSR_OFE2_CFGA                0x70
#define ECGGSR_ADC_DATA_H_MASK          0x3F
#define ECGGSR_PPG_SCALE_VAL            0x64
#define ECGGSR_PD_LED_CURRENT           0x80
#define ECGGSR_PPG_L_THRESHOLD          0x48
#define ECGGSR_PPG_H_THRESHOLD          0x5F
#define ECGGSR_PPG_MAX_VAL              0x64

// ECG related definitions.
#define ECGGSR_ENABLE_SIG_REFERENCE     0x80
#define ECGGSR_ENABLE_BIAS_AND_GAIN     0x09
#define ECGGSR_INPUT_AND_REF_VOLTAGE    0xB0
#define ECGGSR_RESISTIVE_BIASING        0xA0
#define ECGGSR_GAIN_SETTINGS_STAGES1_2  0x0B
#define ECGGSR_ENABLE_ECG_AMPLIFIER     0x88
#define ECGGSR_GAIN_SETTINGS_STAGE3     0x04
#define ECGGSR_ENABLE_REF_AMPLIFIER     0x01
#define ECGGSR_START_SEQUENCER          0xE1
#define ECGGSR_SELECT_EFE               0x40
#define ECGGSR_SELECT_AMPLIFIER_INPUT   0x01
#define ECGGSR_ECG_SCALE_VAL            0x02

// GSR related definitions.
#define ECGGSR_ENABLE_GPIO1_ANALOG      0x02
#define ECGGSR_SET_SLEW_RATE_GPIO1      0x02
#define ECGGSR_SET_GPIO1_AS_INPUT       0x46
#define ECGGSR_SET_RES_BIAS_GPIO1       0x40


/*! @} */   // generic_registers

/*! @} */   // ecggsr

// --------------------------------------------------------------- PUBLIC TYPES

/**
 * @defgroup type Types
 * @{
 */

/**
 * @brief ECG GSR type of measurement selector.
 * @details Enumerator structure for selection of type of working state of the ECG GSR Click.
 */
typedef enum
{
    ENABLE_OXIMETER_FUNCTIONALITY = 0,
    ENABLE_HEARTRATE_FUNCTIONALITY,
    ENABLE_GALVANIC_SKIN_RESPONSE_FUNCTIONALITY,
    
    DEFAULT_ECGGSR_CLICK_FUNCTIONALITY = ENABLE_HEARTRATE_FUNCTIONALITY
} ecggsr_functionality_t;

/*!
 * @brief Context structure.
 * @details
 */
typedef struct
{
    /**< ECG GSR Click employs I2C protocol. */
    i2c_master_t i2c;
    
    /**< I2C protocol requires slave address. */
    uint8_t slave_address;
    
    /**< Reset routine requires enable pin. */
    pin_name_t enable_pin;
    
} ecggsr_t;

/*!
 * @brief Configuration structure.
 * @details
 */

typedef struct
{
    /**< I2C communication pins. */
    pin_name_t scl_pin;
    pin_name_t sda_pin;
    pin_name_t enable_pin;
    
    /**< I2C general settings. */
    uint32_t i2c_speed;
    uint8_t i2c_address;
    
    /**< ECG GSR Click functionality. */
    ecggsr_functionality_t click_functionality;
    
} ecggsr_cfg_t;

/*!
 * @brief Error Code.
 * @details
 */
typedef enum
{
    ecggsr_ok = 0,
    ecggsr_init_error
} ecggsr_err_t;

/** @} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * @defgroup public_function Public function
 * @{
 */

/**
 * @brief ECG GSR configuration object setup function.
 * @details This function initializes click configuration structure to initial values.
 * @param[in] *cfg: Click configuration structure.
 * @note All used pins will be set to unconnected state.
 */
void ecggsr_cfg_setup( ecggsr_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @details This function initializes all necessary pins and peripherals used for this click.
 * @param[in] *ctx Click object.
 * @param[in] *cfg Click configuration structure.
 * @return 0 - OK, 1 - I2C Master Open functionality has failed.
 */
err_t ecggsr_init( ecggsr_t *ctx, ecggsr_cfg_t* cfg );

/**
 * @brief Click Default Configuration function.
 * @details This function executes default configuration for ECG GSR Click.
 * @param[in] *ctx  Click object.
 * @param[in] *cfg  Click configuration structure.
 */
void ecggsr_default_cfg( ecggsr_t *ctx, ecggsr_cfg_t *cfg );

/**
 * @brief Generic Write function.
 * @details Function writes 8-bit data to the register.
 * @param[in] *ctx Click object.
 * @param[in] register_address Register which will be written to.
 * @param[in] transfer_data Data to be written.
 * @return 0 - OK, 1 - Wrong address parameter.
 */
err_t ecggsr_write_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t transfer_data );

/**
 * @brief Generic Read function.
 * @details Function reads 8-bit data from the register/registers.
 * @param[in] *cfg Click configuration.
 * @param[in] register_address Register which will be read.
 * @param[out] *data_out Buffer for storing data that has been read.
 * @param[in] num_of_regs Number of registers to be read.
 * @return 0 - OK, 1 - Wrong address parameter.
 */
err_t ecggsr_read_reg( ecggsr_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t num_of_regs );

/**
 * @brief ECG GSR Read ID function.
 * @details Function performs reading of an ID of the device.
 * @param[in] *ctx Click object.
 * @param[out] *dev_id_out Buffer for storing identification number that has been read.
 */
void ecggsr_read_dev_id( ecggsr_t *ctx, uint8_t *dev_id_out );

/**
 * @brief ECG GSR Reset function.
 * @details Function performs the SW reset of the device and waits until the device returns back to normal state.
 * @param[in] *ctx Click object.
 */
void ecggsr_reset( ecggsr_t *ctx );

/** @} */ // End public_function group

#ifdef __cplusplus
}
#endif

#endif // _ECGGSR_H_
// ------------------------------------------------------------------------- END

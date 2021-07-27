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
 * @file  ecg_gsr.h
 * @brief This file contains API header for ECG GSR Click driver.
 */

// ----------------------------------------------------------------------------

#ifndef _ECG_GSR_H_
#define _ECG_GSR_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/*!
 * @addtogroup ecg_gsr ECG GSR Click Driver
 * @brief API for configuring and manipulating ECG GSR Click driver.
 * @{
 */ 

/**
 * @defgroup ecg_gsr_set ECG GSR Settings
 * @brief Settings for configuration of ECG GSR Click driver.
 */

/**
 * @addtogroup ecg_gsr_cfg
 * @{
 */

/**
 * @brief ECG GSR default I2C slave address.
 * @details Specified setting for reading default slave address of ECG GSR Click.
 */
#define ECG_GSR_SLAVE_ADDRESS 0x30
/*! @} */ // ecg_gsr_cfg

/**
 * @defgroup ecg_gsr_map ECG GSR mikroBUS map
 * @brief MikroBUS pin mapping of ECG GSR Click driver.
 */

/**
 * @addtogroup ecg_gsr_map
 * @{
 */

#define ECG_GSR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl_pin  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda_pin  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.enable_pin  = MIKROBUS( mikrobus, MIKROBUS_CS );
  

/*! @} */   // ecg_gsr_map
  
/*! @} */   // ecg_gsr


/*!
 * @defgroup return_value Return value
 * @{
 */
#define ECG_GSR_RETVAL uint8_t
/*! @} */

/*!
 * @defgroup generic_registers Generic registers
 * @{
 */
#define ECG_GSR_GPIO_SYNC_REG           0x0F
#define ECG_GSR_LED_CFG_REG             0x10
#define ECG_GSR_LED_WAIT_LOW_REG        0x11
#define ECG_GSR_LED1_CURRL_REG          0x12
#define ECG_GSR_LED1_CURRH_REG          0x13
#define ECG_GSR_LED2_CURRL_REG          0x14
#define ECG_GSR_LED2_CURRH_REG          0x15
#define ECG_GSR_LED3_CURRL_REG          0x16
#define ECG_GSR_LED3_CURRH_REG          0x17
#define ECG_GSR_LED4_CURRL_REG          0x18
#define ECG_GSR_LED4_CURRH_REG          0x19
#define ECG_GSR_LED12_MODE_REG          0x2C
#define ECG_GSR_LED34_MODE_REG          0x2D 
#define ECG_GSR_MAN_SEQ_CFG_REG         0x2E
#define ECG_GSR_PD_CFG_REG              0x1A
#define ECG_GSR_PDOFFX_LEDOFF_REG       0x1B
#define ECG_GSR_PDOFFX_LEDON_REG        0x1C
#define ECG_GSR_PD_AMPRCCFG_REG         0x1D
#define ECG_GSR_PD_AMPCFG_REG           0x1E
#define ECG_GSR_OFE1_PD_THCFG_REG       0x1F 
#define ECG_GSR_SEQ_CNT_REG             0x30 
#define ECG_GSR_SEQ_DIV_REG             0x31 
#define ECG_GSR_SEQ_START_REG           0x32 
#define ECG_GSR_SEQ_PER_REG             0x33 
#define ECG_GSR_SEQ_LED_ST_REG          0x34 
#define ECG_GSR_SEQ_LED_STO_REG         0x35 
#define ECG_GSR_SEQ_SECLED_STA_REG      0x36  
#define ECG_GSR_SEQ_SECLED_STO_REG      0x37  
#define ECG_GSR_SEQ_ITG_STA_REG         0x38 
#define ECG_GSR_SEQ_ITG_STO_REG         0x39 
#define ECG_GSR_SEQ_SDP1_STA_REG        0x3A 
#define ECG_GSR_SEQ_SDP1_STO_REG        0x3B 
#define ECG_GSR_SEQ_SDP2_STA_REG        0x3C 
#define ECG_GSR_SEQ_SDP2_STO_REG        0x3D 
#define ECG_GSR_SEQ_SDM1_STA_REG        0x3E 
#define ECG_GSR_SEQ_SDM1_STO_REG        0x3F 
#define ECG_GSR_SEQ_SDM2_STA_REG        0x40 
#define ECG_GSR_SEQ_SDM2_STO_REG        0x41 
#define ECG_GSR_SEQ_ADC_REG             0x42 
#define ECG_GSR_SEQ_ADC2TIA_REG         0x43 
#define ECG_GSR_SEQ_ADC3TIA_REG         0x44 
#define ECG_GSR_SD_SUBS_REG             0x45 
#define ECG_GSR_SEQ_CFG_REG             0x46 
#define ECG_GSR_SEQ_ERR_REG             0x47 
#define ECG_GSR_SEQ_OVS_SEL_REG         0x48
#define ECG_GSR_SEQ_OVS_VAL_REG         0x49
#define ECG_GSR_SEQ_DIS_SEL_REG         0x4A 
#define ECG_GSR_SEQ_DIS_VAL1_REG        0x4B 
#define ECG_GSR_SEQ_DIS_VAL2_REG        0x4C 
#define ECG_GSR_CYC_COUNTER_REG         0x60 
#define ECG_GSR_SEQ_COUNTER_REG         0x61 
#define ECG_GSR_SUBS_COUNTER_REG        0x62 
#define ECG_GSR_OFE_CFGA_REG            0x50 
#define ECG_GSR_OFE1_SD_THCFG_REG       0x51 
#define ECG_GSR_OFE_CFGC_REG            0x52 
#define ECG_GSR_OFE_CFGD_REG            0x53 
#define ECG_GSR_OFE1_CFGA_REG           0x54 
#define ECG_GSR_OFE1_CFGB_REG           0x55 
#define ECG_GSR_OFE2_PD_THCFG_REG       0x56 
#define ECG_GSR_OFE2_SD_THCFG_REG       0x57 
#define ECG_GSR_OFE2_CFGA_REG           0x58 
#define ECG_GSR_OFE2_CFGB_REG           0x59 
#define ECG_GSR_LTFDATA0_L_REG          0x20 
#define ECG_GSR_LTFDATA0_H_REG          0x21 
#define ECG_GSR_LTFDATA1_L_REG          0x22 
#define ECG_GSR_LTFDATA1_H_REG          0x23 
#define ECG_GSR_ITIME_REG               0x24 
#define ECG_GSR_LTF_CONFIG_REG          0x25 
#define ECG_GSR_LTF_SEL_REG             0x26 
#define ECG_GSR_LTF_GAIN_REG            0x27 
#define ECG_GSR_LTF_CONTROL_REG         0x28 
#define ECG_GSR_AZ_CONTROL_REG          0x29 
#define ECG_GSR_OFFSET0_REG             0x2A 
#define ECG_GSR_OFFSET1_REG             0x2B 
#define ECG_GSR_LTF_THRESHOLD_LOW0_REG  0x6C 
#define ECG_GSR_LTF_THRESHOLD_LOW1_REG  0x6D 
#define ECG_GSR_LTF_THRESHOLD_HIGH0_REG 0x6E  
#define ECG_GSR_LTF_THRESHOLD_HIGH1_REG 0x6F  
#define ECG_GSR_EAF_CFG_REG             0x70 
#define ECG_GSR_EAF_GST_REG             0x80 
#define ECG_GSR_EAF_BIAS_REG            0x81 
#define ECG_GSR_EAF_DAC_REG             0x82 
#define ECG_GSR_EAF_DAC1_L_REG          0x83 
#define ECG_GSR_EAF_DAC1_H_REG          0x84 
#define ECG_GSR_EAF_DAC2_L_REG          0x85 
#define ECG_GSR_EAF_DAC2_H_REG          0x86 
#define ECG_GSR_EAF_DAC_CFG_REG         0x87 
#define ECG_GSR_OFE_NOTCH_REG           0x5A 
#define ECG_GSR_ECG_MODE_REG            0x5B 
#define ECG_GSR_ECG_CFGA_REG            0x5C 
#define ECG_GSR_ECG_CFGB_REG            0x5D 
#define ECG_GSR_ECG_THRESHOLD_LOW_REG   0x6A 
#define ECG_GSR_ECG_THRESHOLD_HIGH_REG  0x6B 
#define ECG_GSR_ECG_CFGC_REG            0x5E 
#define ECG_GSR_ECG_CFGD_REG            0x5F 
#define ECG_GSR_ADC_THRESHOLD_REG       0x68 
#define ECG_GSR_ADC_THRESHOLD_CFG_REG   0x69 
#define ECG_GSR_ADC_CFGA_REG            0x88 
#define ECG_GSR_ADC_CFGB_REG            0x89 
#define ECG_GSR_ADC_CFGC_REG            0x8A 
#define ECG_GSR_ADC_CHANNEL_MASK_L_REG  0x8B  
#define ECG_GSR_ADC_CHANNEL_MASK_H_REG  0x8C  
#define ECG_GSR_ADC_DATA_L_REG          0x8E 
#define ECG_GSR_ADC_DATA_H_REG          0x8F 
#define ECG_GSR_FIFO_CFG_REG            0x78 
#define ECG_GSR_FIFO_CNTRL_REG          0x79 
#define ECG_GSR_FIFOL_REG               0xFE 
#define ECG_GSR_FIFOH_REG               0xFF 
#define ECG_GSR_CONTROL_REG             0x00 
#define ECG_GSR_GPIO_A_REG              0x08 
#define ECG_GSR_GPIO_E_REG              0x09 
#define ECG_GSR_GPIO_O_REG              0x0A 
#define ECG_GSR_GPIO_I_REG              0x0B 
#define ECG_GSR_GPIO_P_REG              0x0C 
#define ECG_GSR_GPIO_SR_REG             0x0D 
#define ECG_GSR_SUBID_REG               0x91 
#define ECG_GSR_ID_REG                  0x92 
#define ECG_GSR_STATUS_REG              0xA0 
#define ECG_GSR_STATUS2_REG             0xA1 
#define ECG_GSR_CLIPSTATUS_REG          0xA2 
#define ECG_GSR_LEDSTATUS_REG           0xA3 
#define ECG_GSR_FIFOSTATUS_REG          0xA4 
#define ECG_GSR_LTFSTATUS_REG           0xA5 
#define ECG_GSR_FIFOLEVEL_REG           0xA6 
#define ECG_GSR_INTENAB_REG             0xA8 
#define ECG_GSR_INTENAB2_REG            0xA9 
#define ECG_GSR_INTR_REG                0xAA 
#define ECG_GSR_INTR2_REG               0xAB 

#define ECG_GSR_DEV_ID_MASK             0xFC
#define ECG_GSR_DEV_ID                  0x54


// 35mA current flows through LEDs.
#define ECG_GSR_LED_CURR_LOW_2          0x80
#define ECG_GSR_LED_CURR_HIGH_2         0x59


// 100mA current flows through LEDs.
#define ECG_GSR_LED_CURR_LOW_3          0xC0
#define ECG_GSR_LED_CURR_HIGH_3         0xFF

// PPG related definitions.
#define ECG_GSR_ENABLE_OSC_AND_LDO      0x03
#define ECG_GSR_READ_VALUE_CONTROL_REG  0x83
#define ECG_GSR_ENABLE_REF_AND_DIODES   0x8B
#define ECG_GSR_ENABLE_LED12_OUTPUT     0x99
#define ECG_GSR_ENABLE_LED4_OUTPUT      0x90
#define ECG_GSR_CONF_PHOTODIODE         0x3E
#define ECG_GSR_SUNLIGHT_COMPENSATION   0x5E
#define ECG_GSR_FEEDBACK_RESISTOR       0xE2
#define ECG_GSR_ENABLE_PHOTOAMPLIFIER   0xBC
#define ECG_GSR_START_PPG               0xE1
#define ECG_GSR_ENABLE_ADC              0x01
#define ECG_GSR_START_ADC_CONVERSION    0x01
#define ECG_GSR_ENABLE_OFE_AND_BIAS     0xE6
#define ECG_GSR_OFE1_CFGA               0x70
#define ECG_GSR_OFE2_CFGA               0x70
#define ECG_GSR_ADC_DATA_H_MASK         0x3F
#define ECG_GSR_PPG_SCALE_VAL           0x64
#define ECG_GSR_PD_LED_CURRENT          0x80
#define ECG_GSR_PPG_L_THRESHOLD         0x48
#define ECG_GSR_PPG_H_THRESHOLD         0x5F
#define ECG_GSR_PPG_MAX_VAL             0x64

// ECG related definitions.
#define ECG_GSR_ENABLE_SIG_REFERENCE    0x80
#define ECG_GSR_ENABLE_BIAS_AND_GAIN    0x09
#define ECG_GSR_INPUT_AND_REF_VOLTAGE   0xB0
#define ECG_GSR_RESISTIVE_BIASING       0xA0
#define ECG_GSR_GAIN_SETTINGS_STAGES1_2 0x0B
#define ECG_GSR_ENABLE_ECG_AMPLIFIER    0x88
#define ECG_GSR_GAIN_SETTINGS_STAGE3    0x04
#define ECG_GSR_ENABLE_REF_AMPLIFIER    0x01
#define ECG_GSR_START_SEQUENCER         0xE1
#define ECG_GSR_SELECT_EFE              0x40
#define ECG_GSR_SELECT_AMPLIFIER_INPUT  0x01
#define ECG_GSR_ECG_SCALE_VAL           0x02

// GSR related definitions.
#define ECG_GSR_ENABLE_GPIO1_ANALOG 0x02
#define ECG_GSR_SET_SLEW_RATE_GPIO1 0x02
#define ECG_GSR_SET_GPIO1_AS_INPUT  0x46
#define ECG_GSR_SET_RES_BIAS_GPIO1  0x40


/*! @} */   // generic_registers

/*! @} */   // ecg_gsr

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
    
    DEFAULT_ECG_GSR_CLICK_FUNCTIONALITY = ENABLE_OXIMETER_FUNCTIONALITY
} ecg_gsr_functionality_t;

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
    
} ecg_gsr_t;

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
    ecg_gsr_functionality_t click_functionality;
    
} ecg_gsr_cfg_t;

/*!
 * @brief Error Code.
 * @details
 */
typedef enum
{
    ecg_gsr_ok = 0,
    ecg_gsr_init_error
} ecg_gsr_err_t;

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
void ecg_gsr_cfg_setup( ecg_gsr_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @details This function initializes all necessary pins and peripherals used for this click.
 * @param[in] *ctx Click object.
 * @param[in] *cfg Click configuration structure.
 * @return 0 - OK, 1 - I2C Master Open functionality has failed.
 */
ecg_gsr_err_t ecg_gsr_init( ecg_gsr_t *ctx, ecg_gsr_cfg_t* cfg );

/**
 * @brief Click Default Configuration function.
 * @details This function executes default configuration for ECG GSR Click.
 * @param[in] *ctx  Click object.
 * @param[in] *cfg  Click configuration structure.
 */
void ecg_gsr_default_cfg( ecg_gsr_t *ctx, ecg_gsr_cfg_t *cfg );

/**
 * @brief Generic Write function.
 * @details Function writes 8-bit data to the register.
 * @param[in] *ctx Click object.
 * @param[in] register_address Register which will be written to.
 * @param[in] transfer_data Data to be written.
 * @return 0 - OK, 1 - Wrong address parameter.
 */
ecg_gsr_err_t ecg_gsr_write_reg( ecg_gsr_t *ctx, uint8_t register_address, uint8_t transfer_data );

/**
 * @brief Generic Read function.
 * @details Function reads 8-bit data from the register/registers.
 * @param[in] *cfg Click configuration.
 * @param[in] *register_address Register which will be read.
 * @param[out] *data_out Buffer for storing data that has been read.
 * @param[in] num_of_regs Number of registers to be read.
 * @return 0 - OK, 1 - Wrong address parameter.
 */
ecg_gsr_err_t ecg_gsr_read_reg( ecg_gsr_t *ctx, uint8_t register_address, uint16_t *data_out, uint8_t num_of_regs );

/**
 * @brief ECG GSR Read ID function.
 * @details Function performs reading of an ID of the device.
 * @param[in] *ctx Click object.
 * @param[in] *register_address Register which will be read.
 * @param[out] *dev_id_out Buffer for storing identification number that has been read.
 * @param[in] num_of_regs Number of registers to be read.
 */
void ecg_gsr_read_dev_id( ecg_gsr_t *ctx, uint8_t register_address, uint8_t *dev_id_out, uint8_t num_of_regs );

/**
 * @brief ECG GSR Reset function.
 * @details Function performs the SW reset of the device and waits until the device returns back to normal state.
 * @param[in] *ctx Click object.
 */
void ecg_gsr_reset( ecg_gsr_t *ctx );

/** @} */ // End public_function group

#ifdef __cplusplus
}
#endif

#endif // _ECG_GSR_H_
// ------------------------------------------------------------------------- END

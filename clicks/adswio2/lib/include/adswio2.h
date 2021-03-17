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
 * \brief This file contains API for AD SWIO 2 Click driver.
 *
 * \addtogroup adswio2 AD SWIO 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADSWIO2_H
#define ADSWIO2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define ADSWIO2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.alt   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.rdy   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup driver_abstract_type  Driver Abstract type 
 * \{
 */
#define adswio2_obj_t  const uint8_t*
/** \} */

 /**
 * \defgroup driver_error_handler_type  Driver Error Handler type
 * \{
 */
#define adswio2_err_t  uint8_t
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADSWIO2_RETVAL  uint8_t

#define ADSWIO2_OK           0x00
#define ADSWIO2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup rd_frame Readback Frame
 * \{
 */
#define ADSWIO2_FRAME_LENGTH                                 4
#define ADSWIO2_MASK_RD_FRAME_RESERVED_BIT                   0x80
#define ADSWIO2_MASK_RD_FRAME_REG_ADDR                       0x7F
#define ADSWIO2_MASK_RD_FRAME_STATUS                         0x7F
/** \} */

/**
 * \defgroup rd_info Readback Info Setup
 * \{
 */
#define ADSWIO2_RD_RET_INFO                                  0x1
/** \} */

/**
 * \defgroup reg_offset Results Registers Offset
 * \{
 */
#define ADSWIO2_OFFSET_REG_CONV_RES                          0x25
#define ADSWIO2_OFFSET_REG_DIAG_RES                          0x29
/** \} */

/**
 * \defgroup random Random Macros
 * \{
 */
#define DUMMY                                               0
#define ADSWIO2_NULL                                        0
/** \} */

/**
 * \defgroup rd_setup Auto Read Setup
 * \{
 */
#define ADSWIO2_RD_AUTO_EN                                   0x2
#define ADSWIO2_RD_AUTO_DIS                                  0x0
/** \} */

/**
 * \defgroup offset_mask Offset And Mask Setup
 * \{
 */

/**
 * \defgroup conv_en Conversion Enable
 * \{
 */
#define ADSWIO2_MASK_CONV_EN                                 0xF
#define ADSWIO2_OFFSET_CONV_EN_CH                            0  
#define ADSWIO2_OFFSET_CONV_EN_DIAG                          4  
/** \} */

/**
 * \defgroup diag_assign Diagnostic Assign
 * \{
 */
#define ADSWIO2_MASK_DIAG_ASSIGN                             0xF
#define ADSWIO2_OFFSET_ASSIGN_DIAG0                          0  
#define ADSWIO2_OFFSET_ASSIGN_DIAG1                          4  
#define ADSWIO2_OFFSET_ASSIGN_DIAG2                          8  
#define ADSWIO2_OFFSET_ASSIGN_DIAG3                          12 
/** \} */

/**
 * \defgroup conv_mode Conversion Mode
 * \{
 */
#define ADSWIO2_MASK_CONV_MODE                               0x300
#define  ADSWIO2_OFFSET_CONV_MODE                            8    
/** \} */

/**
 * \defgroup dac_code DAC Code
 * \{
 */
#define ADSWIO2_MASK_DAC_CODE                                0x1FFF
/** \} */

/**
 * \defgroup alert Alert
 * \{
 */
#define ADSWIO2_MASK_ALERT                                   0x7FFF
/** \} */

/**
 * \defgroup din_thresh DIN Threshold
 * \{
 */
#define ADSWIO2_MASK_DIN_THRESH_COMP                         0x3E
/** \} */

/**
 * \defgroup status_alrt Status Alert
 * \{
 */
#define ADSWIO2_MASK_STATUS_ALRT_CAL_MEM_ERR                 0x4000
#define ADSWIO2_MASK_STATUS_ALRT_SPI_CRC_ERR                 0x2000
#define ADSWIO2_MASK_STATUS_ALRT_RST                         0x8000
#define ADSWIO2_MASK_STATUS_ALRT_SPI_SCLK_CNT_ERR            0x1000
#define ADSWIO2_MASK_STATUS_ALRT_ADC_SAT_ERR                 0x800 
#define ADSWIO2_MASK_STATUS_ALRT_ADC_CONV_ERR                0x400 
#define ADSWIO2_MASK_STATUS_ALRT_ALDO1V8_ERR                 0x200 
#define ADSWIO2_MASK_STATUS_ALRT_DVCC_ERR                    0x100 
#define ADSWIO2_MASK_STATUS_ALRT_AVDD_ERR                    0x80  
#define ADSWIO2_MASK_STATUS_ALRT_ALDO5V_ERR                  0x40  
#define ADSWIO2_MASK_STATUS_ALRT_CHARGE_PUMP_ERR             0x20  
#define ADSWIO2_MASK_STATUS_ALRT_HI_TEMP_ERR                 0x10  
#define ADSWIO2_MASK_STATUS_ALRT_VI_ERR_D                    0x8   
#define ADSWIO2_MASK_STATUS_ALRT_VI_ERR_C                    0x4   
#define ADSWIO2_MASK_STATUS_ALRT_VI_ERR_B                    0x2   
#define ADSWIO2_MASK_STATUS_ALRT_VI_ERR_A                    0x1   
/** \} */

/**
 * \defgroup status_live Status Live
 * \{
 */
#define ADSWIO2_MASK_STATUS_LIVE_ADC_DRDY                    0x4000
#define ADSWIO2_MASK_STATUS_LIVE_ADC_BUSY                    0x2000
#define ADSWIO2_MASK_STATUS_LIVE_ADC_CURR_CH                 0x1C00
#define ADSWIO2_MASK_STATUS_LIVE_ALDO1V8                     0x200 
#define ADSWIO2_MASK_STATUS_LIVE_DVCC                        0x100 
#define ADSWIO2_MASK_STATUS_LIVE_AVDD                        0x80  
#define ADSWIO2_MASK_STATUS_LIVE_ALDO5V                      0x40  
#define ADSWIO2_MASK_STATUS_LIVE_CHARGE_PUMP                 0x20  
#define ADSWIO2_MASK_STATUS_LIVE_HI_TEMP                     0x10  
#define ADSWIO2_MASK_STATUS_LIVE_VI_ERR_CURR_D               0x8   
#define ADSWIO2_MASK_STATUS_LIVE_VI_ERR_CURR_C               0x4   
#define ADSWIO2_MASK_STATUS_LIVE_VI_ERR_CURR_B               0x2   
#define ADSWIO2_MASK_STATUS_LIVE_VI_ERR_CURR_A               0x1   
/** \} */

/**
 * \defgroup num_words Data Words Transfer Limits
 * \{
 */
#define ADSWIO2_MAX_NWORDS                                   4
#define ADSWIO2_MIN_NWORDS                                   1
/** \} */

/** \} */ //  End offset_mask group

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define ADSWIO2_REG_NOP                                      0x0
#define ADSWIO2_REG_FUNC_SETUP_CHA                           0x1
#define ADSWIO2_REG_FUNC_SETUP_CHB                           0x2
#define ADSWIO2_REG_FUNC_SETUP_CHC                           0x3
#define ADSWIO2_REG_FUNC_SETUP_CHD                           0x4
#define ADSWIO2_REG_CFG_ADC_CHA                              0x5
#define ADSWIO2_REG_CFG_ADC_CHB                              0x6
#define ADSWIO2_REG_CFG_ADC_CHC                              0x7
#define ADSWIO2_REG_CFG_ADC_CHD                              0x8
#define ADSWIO2_REG_CFG_DIN_CHA                              0x9
#define ADSWIO2_REG_CFG_DIN_CHB                              0xA
#define ADSWIO2_REG_CFG_DIN_CHC                              0xB
#define ADSWIO2_REG_CFG_DIN_CHD                              0xC
#define ADSWIO2_REG_GPO_PARALLEL                             0xD
#define ADSWIO2_REG_CFG_GPO_CHA                              0xE
#define ADSWIO2_REG_CFG_GPO_CHB                              0xF
#define ADSWIO2_REG_CFG_GPO_CHC                              0x10
#define ADSWIO2_REG_CFG_GPO_CHD                              0x11
#define ADSWIO2_REG_CFG_OUTPUT_CHA                           0x12
#define ADSWIO2_REG_CFG_OUTPUT_CHB                           0x13
#define ADSWIO2_REG_CFG_OUTPUT_CHC                           0x14
#define ADSWIO2_REG_CFG_OUTPUT_CHD                           0x15
#define ADSWIO2_REG_DAC_CODE_CHA                             0x16
#define ADSWIO2_REG_DAC_CODE_CHB                             0x17
#define ADSWIO2_REG_DAC_CODE_CHC                             0x18
#define ADSWIO2_REG_DAC_CODE_CHD                             0x19
#define ADSWIO2_REG_DAC_CODE_CLR_CHA                         0x1A
#define ADSWIO2_REG_DAC_CODE_CLR_CHB                         0x1B
#define ADSWIO2_REG_DAC_CODE_CLR_CHC                         0x1C
#define ADSWIO2_REG_DAC_CODE_CLR_CHD                         0x1D
#define ADSWIO2_REG_DAC_CODE_ACT_CHA                         0x1E
#define ADSWIO2_REG_DAC_CODE_ACT_CHB                         0x1F
#define ADSWIO2_REG_DAC_CODE_ACT_CHC                         0x20
#define ADSWIO2_REG_DAC_CODE_ACT_CHD                         0x21
#define ADSWIO2_REG_DIN_THRESH                               0x22
#define ADSWIO2_REG_ADC_CONV_CTRL                            0x23
#define ADSWIO2_REG_DIAG_ASSIGN                              0x24
#define ADSWIO2_REG_DIN_COMP_OUT                             0x25
#define ADSWIO2_REG_RESULT_ADC_CHA                           0x26
#define ADSWIO2_REG_RESULT_ADC_CHB                           0x27
#define ADSWIO2_REG_RESULT_ADC_CHC                           0x28
#define ADSWIO2_REG_RESULT_ADC_CHD                           0x29
#define ADSWIO2_REG_RESULT_DIAG1                             0x2A
#define ADSWIO2_REG_RESULT_DIAG2                             0x2B
#define ADSWIO2_REG_RESULT_DIAG3                             0x2C
#define ADSWIO2_REG_RESULT_DIAG4                             0x2D
#define ADSWIO2_REG_STATUS_ALERT                             0x2E
#define ADSWIO2_REG_STATUS_LIVE                              0x2F
#define ADSWIO2_REG_MASK_ALERT                               0x3C
#define ADSWIO2_REG_DIN_COUNTER_CHA                          0x3D
#define ADSWIO2_REG_DIN_COUNTER_CHB                          0x3E
#define ADSWIO2_REG_DIN_COUNTER_CHC                          0x3F
#define ADSWIO2_REG_DIN_COUNTER_CHD                          0x40
#define ADSWIO2_REG_READ_SELECT                              0x41
#define ADSWIO2_REG_THERM_RST                                0x43
#define ADSWIO2_REG_CMD_KEY                                  0x44
#define ADSWIO2_REG_SCRATCH                                  0x45
#define ADSWIO2_REG_SILICON_REV                              0x46
/** \} */

/**
 * \defgroup reg_setup Registers Setup
 * \{
 */

/**
 * \defgroup ch_conv_en_set Channel Conversion Enable Settings
 * \{
 */
#define ADSWIO2_SETUP_CONV_EN_CHD                            0x8
#define ADSWIO2_SETUP_CONV_EN_CHC                            0x4
#define ADSWIO2_SETUP_CONV_EN_CHB                            0x2
#define ADSWIO2_SETUP_CONV_EN_CHA                            0x1
/** \} */

/**
 * \defgroup ch_func_set Channel Function Settings
 * \{
 */
#define ADSWIO2_SETUP_CH_FUNC_HZ                             0x0
#define ADSWIO2_SETUP_CH_FUNC_VOLT_OUTPUT                    0x1
#define ADSWIO2_SETUP_CH_FUNC_CURR_OUTPUT                    0x2
#define ADSWIO2_SETUP_CH_FUNC_VOLT_INPUT                     0x3
#define ADSWIO2_SETUP_CH_FUNC_CURR_INPUT_PWR_EXT             0x4
#define ADSWIO2_SETUP_CH_FUNC_CURR_INPUT_PWR_LOOP            0x5
#define ADSWIO2_SETUP_CH_FUNC_RES_MEAS                       0x6
#define ADSWIO2_SETUP_CH_FUNC_DIG_INPUT_LOGIC                0x7
#define ADSWIO2_SETUP_CH_FUNC_DIG_INPUT_PWR_LOOP             0x8
#define ADSWIO2_SETUP_CH_FUNC_CURR_INPUT_PWR_EXT_HART        0x9
#define ADSWIO2_SETUP_CH_FUNC_CURR_INPUT_PWR_LOOP_HART       0xA
/** \} */

/**
 * \defgroup diag_conv_en_set Diagnostic Conversion Enable Settings
 * \{
 */
#define ADSWIO2_SETUP_CONV_EN_DIAG3                          0x8
#define ADSWIO2_SETUP_CONV_EN_DIAG2                          0x4
#define ADSWIO2_SETUP_CONV_EN_DIAG1                          0x2
#define ADSWIO2_SETUP_CONV_EN_DIAG0                          0x1
/** \} */

/**
 * \defgroup diag_assign_set Diagnostic Assign Settings
 * \{
 */
#define ADSWIO2_SETUP_DIAG_ASSIGN_AGND                       0x0
#define ADSWIO2_SETUP_DIAG_ASSIGN_TEMP                       0x1
#define ADSWIO2_SETUP_DIAG_ASSIGN_AVDD                       0x2
#define ADSWIO2_SETUP_DIAG_ASSIGN_VAVSS                      0x3
#define ADSWIO2_SETUP_DIAG_ASSIGN_REFOUT                     0x4
#define ADSWIO2_SETUP_DIAG_ASSIGN_ALDO5V                     0x5
#define ADSWIO2_SETUP_DIAG_ASSIGN_ALDO1V8                    0x6
#define ADSWIO2_SETUP_DIAG_ASSIGN_DLDO1V8                    0x7
#define ADSWIO2_SETUP_DIAG_ASSIGN_DVCC                       0x8
#define ADSWIO2_SETUP_DIAG_ASSIGN_IOVDD                      0x9
#define ADSWIO2_SETUP_DIAG_ASSIGN_SENSELA                    0xA
#define ADSWIO2_SETUP_DIAG_ASSIGN_SENSELB                    0xB
#define ADSWIO2_SETUP_DIAG_ASSIGN_SENSELC                    0xC
#define ADSWIO2_SETUP_DIAG_ASSIGN_SENSELD                    0xD
#define ADSWIO2_SETUP_DIAG_ASSIGN_LVIN                       0xE
/** \} */

/**
 * \defgroup conv_mode_set Conversion Mode Settings
 * \{
 */
#define ADSWIO2_SETUP_CONV_STOP_CONT_CONV_ADC_PWR_UP         0x0
#define ADSWIO2_SETUP_CONV_START_SING_SEQ_CONV               0x1
#define ADSWIO2_SETUP_CONV_START_CONT_CONV                   0x2
#define ADSWIO2_SETUP_CONV_STOP_CONT_CONV_ADC_PWR_DWN        0x3
/** \} */

/**
 * \defgroup adc_set ADC Settings
 * \{
 */
#define ADSWIO2_SETUP_ADC_RANGE_0V_TO_10V                    0x0 
#define ADSWIO2_SETUP_ADC_RANGE_2500MV_PWR_EXT               0x20
#define ADSWIO2_SETUP_ADC_RANGE_2500MV_PWR_LOOP              0x40
#define ADSWIO2_SETUP_ADC_RANGE_2500MV_NEG_TO_2500MV_POS     0x60
#define ADSWIO2_SETUP_ADC_RANGE_104MV_NEG_TO_104MV_POS       0x80
#define ADSWIO2_SETUP_ADC_SAMPLE_RATE_20SPS                  0x0 
#define ADSWIO2_SETUP_ADC_SAMPLE_RATE_4800SPS                0x8 
#define ADSWIO2_SETUP_ADC_SAMPLE_RATE_10SPS                  0x10
#define ADSWIO2_SETUP_ADC_SAMPLE_RATE_1200SPS                0x18
#define ADSWIO2_SETUP_ADC_CH_200K_TO_GND                     0x4 
#define ADSWIO2_SETUP_ADC_INPUT_VOLTAGE_AGND_SENSE           0x0 
#define ADSWIO2_SETUP_ADC_INPUT_VOLTAGE_100_OHM_RES          0x1 
/** \} */

/**
 * \defgroup din_set DIN Settings
 * \{
 */
#define ADSWIO2_SETUP_DIN_COUNT_EN                           0x8000
#define ADSWIO2_SETUP_DIN_COMP_IN_FILTERED                   0x4000
#define ADSWIO2_SETUP_DIN_COMP_OUT_INV                       0x2000
#define ADSWIO2_SETUP_DIN_COMP_EN                            0x1000
#define ADSWIO2_SETUP_DIN_RANGE_0                            0x0   
#define ADSWIO2_SETUP_DIN_RANGE_1                            0x800 
#define ADSWIO2_SETUP_DIN_DEBOUNCE_MODE_0                    0x0   
#define ADSWIO2_SETUP_DIN_DEBOUNCE_MODE_1                    0x20  
/** \} */

/**
 * \defgroup gpo_parall_set GPO Parallel Settings
 * \{
 */
#define ADSWIO2_SETUP_GPO_PARALL_DATA_D                      0x8
#define ADSWIO2_SETUP_GPO_PARALL_DATA_C                      0x4
#define ADSWIO2_SETUP_GPO_PARALL_DATA_B                      0x2
#define ADSWIO2_SETUP_GPO_PARALL_DATA_A                      0x1
/** \} */

/**
 * \defgroup gpo_set GPO Settings
 * \{
 */
#define ADSWIO2_SETUP_GPO_LOGIC_LOW                          0x0
#define ADSWIO2_SETUP_GPO_LOGIC_HIGH                         0x8
/** \} */

/**
 * \defgroup out_set Output Settings
 * \{
 */
#define ADSWIO2_SETUP_OUT_SLEW_EN_LINEAR                     0x40
#define ADSWIO2_SETUP_OUT_SLEW_EN_HART                       0x80
#define ADSWIO2_SETUP_OUT_SLEW_LIN_STEP_64_DEC_CODES         0x0 
#define ADSWIO2_SETUP_OUT_SLEW_LIN_STEP_120_DEC_CODES        0x10
#define ADSWIO2_SETUP_OUT_SLEW_LIN_STEP_500_DEC_CODES        0x20
#define ADSWIO2_SETUP_OUT_SLEW_LIN_STEP_1820_DEC_CODES       0x30
#define ADSWIO2_SETUP_OUT_SLEW_LIN_RATE_4KHZ                 0x0 
#define ADSWIO2_SETUP_OUT_SLEW_LIN_RATE_64KHZ                0x4 
#define ADSWIO2_SETUP_OUT_SLEW_LIN_RATE_150KHZ               0x8 
#define ADSWIO2_SETUP_OUT_SLEW_LIN_RATE_240KHZ               0xC 
#define ADSWIO2_SETUP_OUT_CLR_EN                             0x2 
#define ADSWIO2_SETUP_OUT_CURR_LIM_30MA                      0x0 
#define ADSWIO2_SETUP_OUT_CURR_LIM_7_5MA                     0x1 
/** \} */

/**
 * \defgroup din_thresh_set DIN Threshold Settings
 * \{
 */
#define ADSWIO2_SETUP_DIN_THRESH_GND_AND_AVDD                0x0
#define ADSWIO2_SETUP_DIN_THRESH_GND_AND_16V                 0x1
/** \} */

/**
 * \defgroup conv_set Conversion Settings
 * \{
 */
#define ADSWIO2_SETUP_CONV_EN_50_60_HZ_REJ_DIAG              0x400

#define ADSWIO2_SETUP_CONV_EN_ALL_CH                         0xF
#define ADSWIO2_SETUP_CONV_EN_ALL_DIAG                       0xF
#define ADSWIO2_SETUP_CONV_DIS_ALL_CH                        0x0
#define ADSWIO2_SETUP_CONV_DIS_ALL_DIAG                      0x0
/** \} */

/**
 * \defgroup therm_set Thermal Settings
 * \{
 */
#define ADSWIO2_SETUP_THERM_RST_EN                           0x1
/** \} */

/**
 * \defgroup adc_curr_status ADC Current Conversion Status
 * \{
 */
#define ADSWIO2_STATUS_LIVE_ADC_CURR_CHA                     0x0   
#define ADSWIO2_STATUS_LIVE_ADC_CURR_CHB                     0x400 
#define ADSWIO2_STATUS_LIVE_ADC_CURR_CHC                     0x800 
#define ADSWIO2_STATUS_LIVE_ADC_CURR_CHD                     0xC00 
#define ADSWIO2_STATUS_LIVE_ADC_CURR_DIAG0                   0x1000
#define ADSWIO2_STATUS_LIVE_ADC_CURR_DIAG1                   0x1400
#define ADSWIO2_STATUS_LIVE_ADC_CURR_DIAG2                   0x1800
#define ADSWIO2_STATUS_LIVE_ADC_CURR_DIAG3                   0x1C00
/** \} */

/**
 * \defgroup command Commands
 * \{
 */
#define  ADSWIO2_CMD_NOP                                     0x0   
#define ADSWIO2_CMD_SW_RST_KEY1                              0x15FA
#define ADSWIO2_CMD_SW_RST_KEY2                              0xAF51
#define ADSWIO2_CMD_LDAC_KEY                                 0x953A
#define ADSWIO2_CMD_DAC_CLR_KEY                              0x73D1
/** \} */

/** \} */ //  End reg_setup group

/**
 * \defgroup err_code Error Code
 * \{
 */
#define ADSWIO2_ERR_STATUS_OK                                0
#define ADSWIO2_ERR_INIT_DRV                                 1
#define ADSWIO2_ERR_UNSUPPORTED_PIN                          2
#define ADSWIO2_ERR_RD_STATUS                                3
#define ADSWIO2_ERR_RD_MODE                                  4
#define ADSWIO2_ERR_RD_NWORDS                                5
#define ADSWIO2_ERR_CMD_KEY                                  6
#define ADSWIO2_ERR_EN_CH                                    7
#define ADSWIO2_ERR_EN_DIAG                                  8
#define ADSWIO2_ERR_CRC                                      9
#define ADSWIO2_ERR_REG_ADDR                                 10
#define ADSWIO2_ERR_CONV_MODE                                11
#define ADSWIO2_ERR_CH_FUNC                                  12
#define ADSWIO2_ERR_DIAG_ASSIGN                              13
/** \} */

/**
 * \defgroup id_sil_rev Silicon Revision ID
 * \{
 */
#define ADSWIO2_ID_SILICON_REV                               0x8
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click error handler definition.
 */
typedef void ( * adswio2_handler_t )( uint8_t * );


/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs;
    digital_out_t rst;

    // Input pins 

    digital_out_t alt;
    digital_in_t rdy;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // static variable
    
    adswio2_handler_t err_handler;

} adswio2_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // static variable
    
    uint8_t reg_addr; 
    uint16_t *data_out;
    uint8_t rd_mode; 
    uint8_t n_words;

} adswio2_read_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t alt;
    pin_name_t rdy;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} adswio2_cfg_t;

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
void adswio2_cfg_setup ( adswio2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ADSWIO2_RETVAL adswio2_init ( adswio2_t *ctx, adswio2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for AD SWIO 2 click.
 */
void adswio2_default_cfg ( adswio2_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void adswio2_generic_transfer ( adswio2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Click Reset function.
 *
 * @description This function executes a hardware reset of the click board.
 */
void adswio2_reset( adswio2_t *ctx );

/**
 * @brief Ready Pin Status Check function.
 *
 * @param ctx          Click object.
 * 
 * @returns State of the ready pin, 0 or 1.
 *
 * @description This function checks the status of the ready pin.
 */
uint8_t adswio2_status_pin_ready ( adswio2_t *ctx );

/**
 * @brief Alert Pin Status Check function.
 *
 * @param ctx          Click object.
 * 
 * @returns State of the alert pin, 0 or 1.
 *
 * @description This function checks the status of the alert pin.
 */
uint8_t adswio2_status_pin_alert ( adswio2_t *ctx );

/**
 * @brief Error Handler Setup function.
 *
 * @param ctx          Click object. 
 * @param handler      Function to be executed.
 *
 * @description This function executes an error handler setup.
 */
void adswio2_set_handler ( adswio2_t *ctx, adswio2_handler_t handler );

/**
 * @brief Error Handler Clear function.
 *
 * @param ctx          Click object.
 * 
 * @description This function will set the error handler to NULL (unused).
 */
void adswio2_clear_handler ( adswio2_t *ctx );

/**
 * @brief Generic Write function.
 *
 * @param ctx           Click object. 
 * @param reg_addr      Address where data be written.
 * @param data_in       Data to be written.
 *
 * @returns 0  - Ok;  10 - Invalid register address.
 *
 * @description This function writes 16-bit data to the selected register.
 */ 
adswio2_err_t adswio2_generic_write ( adswio2_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Generic Read function.
 *
 * @param ctx           Click object. 
 * @param reg_addr      Address which from data be read.
 * @param data_out      Memory where read data be stored.
 * @param rd_status     Readback status.
 *
 * @returns 
 * <pre>
 *          0  - Ok,
 *          3  - Readback status error,
 *          9  - CRC error,
 *          10 - Invalid register address.
 * </pre>
 *
 * @description This function reads 16-bit data from the selected register and
 *              also shows the readback status.
 */
adswio2_err_t adswio2_generic_read ( adswio2_t *ctx, uint8_t reg_addr, uint16_t *data_out, uint8_t *rd_status );

/**
 * @brief Generic Multi Read function.
 *
 * @param ctx           Click object. 
 * @param reg_addr      Address which from data reading be started.
 * @param data_out      Memory where read data be stored.
 * @param rd_mode       0 - Auto read disable; 2 - Auto read enable.
 * @param n_words       Selects number of data words to be read. The range is from 1 to 4.
 *
 * @returns 
 * <pre>
 *          0  - Ok,
 *          3  - Readback status error,
 *          4  - Auto read setup error,
 *          5  - Number of words is out of range,
 *          9  - CRC error,
 *          10 - Invalid register address.
 * </pre> 
 *
 * @description This function reads the desired number of 16-bit data words
 *              starting from the selected register.
 * @note The auto read mode setup allows user to read the same register a couple
 *       of times, or to read registers consecutively.
 */
adswio2_err_t adswio2_generic_multi_read ( adswio2_t *ctx, adswio2_read_t *rd );

/**
 * @brief Command Execute function.
 *
 * @param ctx          Click object. 
 * @param cmd_key      Command key to be executed.
 *
 * @returns 0 - Ok, 6 - Invalid command key.
 *
 * @description This function executes an entered command key.
 */
adswio2_err_t adswio2_exe_command (  adswio2_t *ctx, uint16_t cmd_key );

/**
 * @brief Alert Mask function.
 *
 * @param ctx          Click object. 
 * @param alert_mask   Selects alerts to be masked.
 *
 * @description This function allows user to mask the irrelevant alerts.
 */
void adswio2_mask_alert_set ( adswio2_t *ctx, uint16_t alert_mask );

/**
 * @brief Live Status function.
 *
 * @param ctx          Click object. 
 * @param status       Live status of the click.
 * @param status_mask  Irrelevant status flags to be masked.
 *
 * @returns 0 - Ok; 3 - Readback status error; 9 - CRC error.
 *
 * @description This function allows user to check the live status of the click,
 *              masking the irrelevant status flags.
 */
adswio2_err_t adswio2_status_live ( adswio2_t *ctx, uint16_t *status, uint16_t status_mask );

/**
 * @brief Data Ready Status function.
 *
 * @param ctx          Click object. 
 * @param drdy         Data ready status; 0 - not ready, 1 - ready.
 * @param conv_target  Current executed ADC measurement.
 *
 * @returns 0 - Ok; 3 - Readback status error; 9 - CRC error.
 *
 * @description This function allows user to check the data ready status and
 *              gives an information about current executed AD conversion.
 * @note If data ready flag has been asserted, it will be deasserted
 *       automatically by using this function.
 */
adswio2_err_t adswio2_status_data_ready ( adswio2_t *ctx, uint8_t *drdy, uint16_t *conv_target );

/**
 * @brief Alert Status function.
 *
 * @param ctx           Click object. 
 * @param status        Alert status of the click.
 * @param status_mask   Irrelevant status flags to be masked.
 *
 * @returns 0 - Ok; 3 - Readback status error; 9 - CRC error.
 *
 * @description This function allows user to check the alert status, masking
 *              the irrelevant status flags.
 * @note If any of the alert status flags has been asserted, it will be
 *       deasserted automatically by using this function.
 */
adswio2_err_t adswio2_status_alert ( adswio2_t *ctx, uint16_t *status, uint16_t status_mask );

/**
 * @brief Conversion Mode Setup function.
 *
 * @param ctx   Click object. 
 * @param mode  Mode to be set.
 *
 * @returns 
 * <pre>
 *          0  - Ok,
 *          3  - Readback status error,
 *          9  - CRC error,
 *          11 - Invalid conversion mode.
 * </pre> 
 *
 * @description This function sets the conversion mode and performs power control of the click.
 */
adswio2_err_t adswio2_set_conv_mode ( adswio2_t *ctx, uint8_t mode );

/**
 * @brief Channel Enable function.
 *
 * @param ctx          Click object. 
 * @param channel      Selects channel/s to be enabled.
 *
 * @returns 
 * <pre>
 *          0 - Ok,
 *          3 - Readback status error,
 *          7 - Invalid channel selection,
 *          9 - CRC error.
 * </pre>
 *
 * @description This function allows user to enable the desired channel/channels.
 */
adswio2_err_t adswio2_enable_ch ( adswio2_t *ctx, uint8_t channel );

/**
 * @brief Diagnostic Enable function.
 *
 * @param ctx          Click object. 
 * @param diagnostic  Selects diagnostic/s to be enabled.
 *
 * @returns 
 * <pre>
 *          0 - Ok,
 *          3 - Readback status error,
 *          8 - Invalid diagnostic selection,
 *          9 - CRC error.
 * </pre> 
 *
 * @description This function allows user to enable the desired diagnostic/diagnostics.
 */
adswio2_err_t adswio2_enable_diag ( adswio2_t *ctx, uint8_t diagnostic );

/**
 * @brief Channel Function Setup function.
 *
 * @param ctx           Click object. 
 * @param channel       Selects channel to be modified.
 * @param ch_func       Selects new channel function.
 *
 * @returns 0  - Ok; 7  - Invalid channel selection; 12 - Invalid channel function.
 *
 * @description This function allows user to modify the functionality of the selected channel.
 */
adswio2_err_t adswio2_set_ch_func ( adswio2_t *ctx, uint8_t channel, uint8_t ch_func );

/**
 * @brief Diagnostic Assign function.
 *
 * @param ctx          Click object. 
 * @param diagnostic   Selects diagnostic to be assigned.
 * @param duty         Selects new duty to be assigned.
 *
 * @returns 
 * <pre>
 *          0  - Ok,
 *          3  - Readback status error,
 *          8  - Invalid diagnostic selection,
 *          9  - CRC error,
 *          13 - Diagnostic assign error.
 * </pre>  
 *
 * @description This function allows user to assign the new duty for the selected diagnostic.
 */
adswio2_err_t adswio2_assign_diag ( adswio2_t *ctx, uint8_t diagnostic, uint8_t duty );

/**
 * @brief Channel Results Get function.
 *
 * @param ctx          Click object. 
 * @param channel      Choose channel results.
 * @param data_out     Results of channel conversion.
 *
 * @returns 
 * <pre>
 *          0 - Ok,
 *          3 - Readback status error,
 *          7 - Invalid channel selection,
 *          9 - CRC error.
 * </pre>   
 *
 * @description This function allows user to get the converted results of the selected channel.
 */
adswio2_err_t adswio2_get_conv_results ( adswio2_t *ctx, uint8_t channel, uint16_t *data_out );

/**
 * @brief Diagnostic Results Get function.
 *
 * @param ctx           Click object. 
 * @param diagnostic    Choose diagnostic results.
 * @param data_out      Results of target diagnostic.
 *
 * @returns 
 * <pre>  
 *          0 - Ok,
 *          3 - Readback status error,
 *          8 - Invalid diagnostic selection,
 *          9 - CRC error.
 * </pre>   
 *
 * @description This function allows user to get the results of the selected diagnostic.
 */
adswio2_err_t adswio2_get_diag_results ( adswio2_t *ctx, uint8_t diagnostic, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif  // _ADSWIO2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

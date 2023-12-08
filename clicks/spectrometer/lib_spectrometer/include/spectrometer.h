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
 * \brief This file contains API for Spectrometer Click driver.
 *
 * \addtogroup spectrometer Spectrometer Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SPECTROMETER_H
#define SPECTROMETER_H

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
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define SPECTROMETER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SPECTROMETER_RETVAL  uint8_t

#define SPECTROMETER_OK                                0x00
#define SPECTROMETER_INIT_ERROR                        0xFF
/** \} */

/**
 * \defgroup devide_i2c_slave_address Devide I2C Slave Address
 * \{
 */
#define SPECTROMETER_I2C_DEV_ADR                       0x39
/** \} */

/**
 * \defgroup register_map Register Map
 * \{
 */
#define SPECTROMETER_ASTAT                             0x60
#define SPECTROMETER_CH0_DATA_L                        0x61
#define SPECTROMETER_CH0_DATA_H                        0x62
#define SPECTROMETER_ITIME_L                           0x63
#define SPECTROMETER_ITIME_M                           0x64
#define SPECTROMETER_ITIME_H                           0x65
#define SPECTROMETER_CH1_DATA_L                        0x66
#define SPECTROMETER_CH1_DATA_H                        0x67
#define SPECTROMETER_CH2_DATA_L                        0x68
#define SPECTROMETER_CH2_DATA_H                        0x69
#define SPECTROMETER_CH3_DATA_L                        0x6A
#define SPECTROMETER_CH3_DATA_H                        0x6B
#define SPECTROMETER_CH4_DATA_L                        0x6C
#define SPECTROMETER_CH4_DATA_H                        0x6D
#define SPECTROMETER_CH5_DATA_L                        0x6E
#define SPECTROMETER_CH5_DATA_H                        0x6F
#define SPECTROMETER_CFG                               0x70
#define SPECTROMETER_STAT                              0x71
#define SPECTROMETER_SYNC_EDGE                         0x72
#define SPECTROMETER_GPIO                              0x73
#define SPECTROMETER_LED                               0x74
#define SPECTROMETER_ENABLE                            0x80
#define SPECTROMETER_ATIME                             0x81
#define SPECTROMETER_WTIME                             0x83
#define SPECTROMETER_SP_TH_L_LSB                       0x84
#define SPECTROMETER_SP_TH_L_MSB                       0x85
#define SPECTROMETER_SP_TH_H_LSB                       0x86
#define SPECTROMETER_SP_TH_H_MSB                       0x87
#define SPECTROMETER_AUXID                             0x90
#define SPECTROMETER_REVID                             0x91
#define SPECTROMETER_ID                                0x92
#define SPECTROMETER_STATUS                            0x93
#define SPECTROMETER_ASTATUS                           0x94
#define SPECTROMETER_CH0_ADC_DATA_L                    0x95
#define SPECTROMETER_CH0_ADC_DATA_H                    0x96
#define SPECTROMETER_CH1_ADC_DATA_L                    0x97
#define SPECTROMETER_CH1_ADC_DATA_H                    0x98
#define SPECTROMETER_CH2_ADC_DATA_L                    0x99
#define SPECTROMETER_CH2_ADC_DATA_H                    0x9A
#define SPECTROMETER_CH3_ADC_DATA_L                    0x9B
#define SPECTROMETER_CH3_ADC_DATA_H                    0x9C
#define SPECTROMETER_CH4_ADC_DATA_L                    0x9D
#define SPECTROMETER_CH4_ADC_DATA_H                    0x9E
#define SPECTROMETER_CH5_ADC_DATA_L                    0x9F
#define SPECTROMETER_CH5_ADC_DATA_H                    0xA0
#define SPECTROMETER_STAT_2                            0xA3
#define SPECTROMETER_STAT_3                            0xA4
#define SPECTROMETER_STAT_5                            0xA6
#define SPECTROMETER_STAT_6                            0xA7
#define SPECTROMETER_CFG_0                             0xA9
#define SPECTROMETER_CFG_1                             0xAA
#define SPECTROMETER_CFG_3                             0xAC
#define SPECTROMETER_CFG_6                             0xAF
#define SPECTROMETER_CFG_8                             0xB1
#define SPECTROMETER_CFG_9                             0xB2
#define SPECTROMETER_CFG_10                            0xB3
#define SPECTROMETER_CFG_12                            0xB5
#define SPECTROMETER_PERS                              0xBD
#define SPECTROMETER_GPIO_2                            0xBE
#define SPECTROMETER_ASTEP_L                           0xCA
#define SPECTROMETER_ASTEP_H                           0xCB
#define SPECTROMETER_AGC_GAIN_MAX                      0xCF
#define SPECTROMETER_AZ_CFG                            0xD6
#define SPECTROMETER_FD_TIME_1                         0xD8
#define SPECTROMETER_FD_TIME_2                         0xDA
#define SPECTROMETER_FD_CFG0                           0xD7
#define SPECTROMETER_FD_STAT                           0xDB
#define SPECTROMETER_INTENAB                           0xF9
#define SPECTROMETER_CTL                               0xFA
#define SPECTROMETER_FIFO_MAP                          0xFC
#define SPECTROMETER_FIFO_LVL                          0xFD
#define SPECTROMETER_FDATA_L                           0xFE
#define SPECTROMETER_FDATA_H                           0xFF
/** \} */

/**
 * \defgroup config_register_bit_settings CONFIG Register Bit Settings
 * \{
 */
#define SPECTROMETER_CFG_LED_SEL                       0x08
#define SPECTROMETER_CFG_INT_SEL                       0x04
#define SPECTROMETER_CFG_INT_MODE_SYND                 0x03
#define SPECTROMETER_CFG_INT_MODE_SYNS                 0x01
#define SPECTROMETER_CFG_INT_MODE_SPM                  0x00
/** \} */

/**
 * \defgroup status_register_flags STATUS Register Flags
 * \{
 */
#define SPECTROMETER_STAT_WAIT_SYNC                    0x02
#define SPECTROMETER_STAT_READY                        0x01
/** \} */

/**
 * \defgroup gpio_register_bit_settings  GPIO Register Bit Settings
 * \{
 */
#define SPECTROMETER_GPIO_PD_GPIO                      0x02
#define SPECTROMETER_GPIO_PD_INT                       0x01
/** \} */

/**
 * \defgroup led_register_bit_settings LED Register Bit Settings
 * \{
 */
#define SPECTROMETER_LED_LED_ACT                       0x80
#define SPECTROMETER_LED_LED_DRV_4MA                   0x00
#define SPECTROMETER_LED_LED_DRV_6MA                   0x01
#define SPECTROMETER_LED_LED_DRV_8MA                   0x02
#define SPECTROMETER_LED_LED_DRV_10MA                  0x03
#define SPECTROMETER_LED_LED_DRV_12MA                  0x04
#define SPECTROMETER_LED_LED_DRV_256MA                 0x7E
#define SPECTROMETER_LED_LED_DRV_258MA                 0x7F
/** \} */

/**
 * \defgroup enable_register_bit_settings ENABLE Register Bit Settings
 * \{
 */
#define SPECTROMETER_EN_FDEN                           0x40
#define SPECTROMETER_EN_SMUXEN                         0x10
#define SPECTROMETER_EN_WEN                            0x08
#define SPECTROMETER_EN_SP_EN                          0x02
#define SPECTROMETER_EN_PON                            0x01
/** \} */

/**
 * \defgroup status_register_flags STATUS Register Flags
 * \{
 */
#define SPECTROMETER_STATUS_ASAT                       0x80
#define SPECTROMETER_STATUS_AINT                       0x08
#define SPECTROMETER_STATUS_FINT                       0x04
#define SPECTROMETER_STATUS_CINT                       0x02
#define SPECTROMETER_STATUS_SINT                       0x01
/** \} */

/**
 * \defgroup status_2_register_flags STATUS 2 Register Flags
 * \{
 */
#define SPECTROMETER_STAT_2_AVALID                     0x40
#define SPECTROMETER_STAT_2_ASAT_DIG                   0x10
#define SPECTROMETER_STAT_2_ASAT_ANA                   0x08
#define SPECTROMETER_STAT_2_FDSAT_ANA                  0x02
#define SPECTROMETER_STAT_2_FDSAT_DIG                  0x01
/** \} */

/**
 * \defgroup status_3_register_flags STATUS 3 Register Flags
 * \{
 */
#define SPECTROMETER_STAT_3_INT_SP_H                   0x20
#define SPECTROMETER_STAT_3_INT_SP_L                   0x10
/** \} */

/**
 * \defgroup status_5_register_flags STATUS 5 Register Flags
 * \{
 */
#define SPECTROMETER_STAT_5_SINT_FD                    0x08
#define SPECTROMETER_STAT_5_SINT_SMUX                  0x04
/** \} */

/**
 * \defgroup status_6_register_flags STATUS 6 Register Flags
 * \{
 */
#define SPECTROMETER_STAT_6_FIFO_OV                    0x80
#define SPECTROMETER_STAT_6_OVTEMP                     0x20
#define SPECTROMETER_STAT_6_FD_TRIG                    0x10
#define SPECTROMETER_STAT_6_SP_TRIG                    0x04
#define SPECTROMETER_STAT_6_SAI_ACT                    0x02
#define SPECTROMETER_STAT_6_INT_BUSY                   0x01
/** \} */

/**
 * \defgroup cfg0_register_gain_settings CFG0 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_0_LOW_POW                     0x20
#define SPECTROMETER_CFG_0_REG_BANK_1                  0x10
#define SPECTROMETER_CFG_0_REG_BANK_0                  0x00
#define SPECTROMETER_CFG_0_WLONG                       0x04
/** \} */

/**
 * \defgroup cfg1_register_gain_settings CFG1 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_1_AGAIN_512                   0x0A
#define SPECTROMETER_CFG_1_AGAIN_256                   0x09
#define SPECTROMETER_CFG_1_AGAIN_128                   0x08
#define SPECTROMETER_CFG_1_AGAIN_64                    0x07
#define SPECTROMETER_CFG_1_AGAIN_32                    0x06
#define SPECTROMETER_CFG_1_AGAIN_16                    0x05
#define SPECTROMETER_CFG_1_AGAIN_8                     0x04
#define SPECTROMETER_CFG_1_AGAIN_4                     0x03
#define SPECTROMETER_CFG_1_AGAIN_2                     0x02
#define SPECTROMETER_CFG_1_AGAIN_1                     0x01
#define SPECTROMETER_CFG_1_AGAIN_05                    0x00
/** \} */

/**
 * \defgroup cfg3_register_gain_settings CFG3 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_3_SAI                         0x10
/** \} */

/**
 * \defgroup cfg6_register_gain_settings CFG6 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_6_SMUX_CMD_2                  0x10
#define SPECTROMETER_CFG_6_SMUX_CMD_1                  0x08
#define SPECTROMETER_CFG_6_SMUX_CMD_0                  0x00
/** \} */

/**
 * \defgroup cfg8_register_gain_settings CFG8 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_8_FIFO_TH_16                  0xC0
#define SPECTROMETER_CFG_8_FIFO_TH_8                   0x80
#define SPECTROMETER_CFG_8_FIFO_TH_4                   0x40
#define SPECTROMETER_CFG_8_FIFO_TH_1                   0x00
#define SPECTROMETER_CFG_8_FD_AGC                      0x08
#define SPECTROMETER_CFG_8_SP_AGC                      0x04
/** \} */

/**
 * \defgroup cfg9_register_gain_settings CFG9 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_9_SIEN_FD                     0x40
#define SPECTROMETER_CFG_9_SIEN_SMUX                   0x10
/** \} */

/**
 * \defgroup cfg10_register_gain_settings CFG10 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_10_AGC_H_3                    0xC0
#define SPECTROMETER_CFG_10_AGC_H_2                    0x80
#define SPECTROMETER_CFG_10_AGC_H_1                    0x40
#define SPECTROMETER_CFG_10_AGC_H_0                    0x00
#define SPECTROMETER_CFG_10_AGC_L_3                    0x60
#define SPECTROMETER_CFG_10_AGC_L_2                    0x20
#define SPECTROMETER_CFG_10_AGC_L_1                    0x10
#define SPECTROMETER_CFG_10_AGC_L_0                    0x00
#define SPECTROMETER_CFG_10_FD_PERS_DEF                0x02
/** \} */

/**
 * \defgroup cfg12_register_gain_settings CFG12 Register Gain Settings
 * \{
 */
#define SPECTROMETER_CFG_12_SP_TH_CH_4                 0x04
#define SPECTROMETER_CFG_12_SP_TH_CH_3                 0x03
#define SPECTROMETER_CFG_12_SP_TH_CH_2                 0x02
#define SPECTROMETER_CFG_12_SP_TH_CH_1                 0x01
#define SPECTROMETER_CFG_12_SP_TH_CH_0                 0x00
/** \} */

/**
 * \defgroup pers_register_settings PERS Register Settings
 * \{
 */
#define SPECTROMETER_PERS_APERS_60                     0x0F
#define SPECTROMETER_PERS_APERS_55                     0x0E
#define SPECTROMETER_PERS_APERS_50                     0x0D
#define SPECTROMETER_PERS_APERS_45                     0x0C
#define SPECTROMETER_PERS_APERS_40                     0x0B
#define SPECTROMETER_PERS_APERS_35                     0x0A
#define SPECTROMETER_PERS_APERS_30                     0x09
#define SPECTROMETER_PERS_APERS_25                     0x08
#define SPECTROMETER_PERS_APERS_20                     0x07
#define SPECTROMETER_PERS_APERS_15                     0x06
#define SPECTROMETER_PERS_APERS_10                     0x05
#define SPECTROMETER_PERS_APERS_5                      0x04
#define SPECTROMETER_PERS_APERS_3                      0x03
#define SPECTROMETER_PERS_APERS_2                      0x02
#define SPECTROMETER_PERS_APERS_1                      0x01
#define SPECTROMETER_PERS_APERS                        0x00
/** \} */

/**
 * \defgroup gpio_2_register_bit_settings GPIO 2 Register Bit Settings
 * \{
 */
#define SPECTROMETER_GPIO_2_GPIO_INV                   0x08
#define SPECTROMETER_GPIO_2_GPIO_IN                    0x04
#define SPECTROMETER_GPIO_2_GPIO_OUT                   0x02
/** \} */

/**
 * \defgroup agc_gain_max_register_settings AGC_GAIN_MAX Register Settings
 * \{
 */
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_512  0xA0
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_256  0x90
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_128  0x80
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_64   0x70
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_32   0x60
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_16   0x50
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_8    0x40
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_4    0x30
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_2    0x20
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_1    0x10
#define SPECTROMETER_AGC_GAIN_MAX_AGC_FD_GAIN_MAX_05   0x00
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_512    0x0A
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_256    0x09
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_128    0x08
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_64     0x07
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_32     0x06
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_16     0x05
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_8      0x04
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_4      0x03
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_2      0x02
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_1      0x01
#define SPECTROMETER_AGC_GAIN_MAX_AGC_AGAIN_MAX_05     0x00
/** \} */

/**
 * \defgroup fifo_cfg0_register_settings FIFO CFG0 Register Settings
 * \{
 */
#define SPECTROMETER_FD_CFG0_FD_FIFO                   0x80
/** \} */

/**
 * \defgroup fd_status_register_flags FD STATUS Register Flags
 * \{
 */
#define SPECTROMETER_FD_STAT_FD_VALID                  0x20
#define SPECTROMETER_FD_STAT_FD_SAT                    0x10
#define SPECTROMETER_FD_STAT_FD_120HZ_VALID            0x08
#define SPECTROMETER_FD_STAT_FD_100HZ_VALID            0x04
#define SPECTROMETER_FD_STAT_FD_120HZ                  0x02
#define SPECTROMETER_FD_STAT_FD_100HZ                  0x01
/** \} */

/**
 * \defgroup intenab_register_bit_settings INTENAB Register Bit Settings
 * \{
 */
#define SPECTROMETER_INTENAB_ASIEN                     0x80
#define SPECTROMETER_INTENAB_SP_IEN                    0x08
#define SPECTROMETER_INTENAB_F_IEN                     0x04
#define SPECTROMETER_INTENAB_SIEN                      0x01
/** \} */

/**
 * \defgroup control_register_bit_settings CONTROL Register Bit Settings
 * \{
 */
#define SPECTROMETER_CTL_AZ_SP_MAN                     0x04
#define SPECTROMETER_CTL_FIFO_CLR                      0x02
#define SPECTROMETER_CTL_CLR_SAI_ACT                   0x01
/** \} */

/**
 * \defgroup fifo_map_register_settings FIFO MAP Register Settings
 * \{
 */
#define SPECTROMETER_FIFO_MAP_WR_DATA_CH6              0x40
#define SPECTROMETER_FIFO_MAP_WR_DATA_CH5              0x20
#define SPECTROMETER_FIFO_MAP_WR_DATA_CH3              0x10
#define SPECTROMETER_FIFO_MAP_WR_DATA_CH2              0x08
#define SPECTROMETER_FIFO_MAP_WR_DATA_CH1              0x04
#define SPECTROMETER_FIFO_MAP_WR_DATA_CH0              0x02
#define SPECTROMETER_FIFO_MAP_WR_ASTAT                 0x01
/** \} */

/**
 * \defgroup fd_time_2_register_gain_settings FD_TIME_2 Register Gain Settings
 * \{
 */
#define SPECTROMETER_FD_TIME_2_FD_GAIN_05              0x00
#define SPECTROMETER_FD_TIME_2_FD_GAIN_1               0x08
#define SPECTROMETER_FD_TIME_2_FD_GAIN_2               0x10
#define SPECTROMETER_FD_TIME_2_FD_GAIN_4               0x18
#define SPECTROMETER_FD_TIME_2_FD_GAIN_8               0x20
#define SPECTROMETER_FD_TIME_2_FD_GAIN_16              0x28
#define SPECTROMETER_FD_TIME_2_FD_GAIN_32              0x30
#define SPECTROMETER_FD_TIME_2_FD_GAIN_64              0x38
#define SPECTROMETER_FD_TIME_2_FD_GAIN_128             0x40
#define SPECTROMETER_FD_TIME_2_FD_GAIN_256             0x48
#define SPECTROMETER_FD_TIME_2_FD_GAIN_512             0x50
/** \} */

/**
 * \defgroup flicker_status_flags Flicker status flags
 * \{
 */
#define SPECTROMETER_UNKNOWN_FREQ                      0x01
#define SPECTROMETER_DETECTED_100_HZ                   0x02
#define SPECTROMETER_DETECTED_120_HZ                   0x03
#define SPECTROMETER_READING_ERROR                     0x00
/** \} */

/**
 * \defgroup id_value ID value
 * \{
 */
#define SPECTROMETER_ID_VALUE                          0x24
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} spectrometer_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} spectrometer_cfg_t;

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
void spectrometer_cfg_setup ( spectrometer_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SPECTROMETER_RETVAL spectrometer_init ( spectrometer_t *ctx, spectrometer_cfg_t *cfg );

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
void spectrometer_generic_write ( spectrometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void spectrometer_generic_read ( spectrometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set the power on bit function
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to set the PON (Power on) bit on the chip.
 *
 * @note Function clears the PON bit in ENABLE register and keeps the other bits.
**/
void spectrometer_pon ( spectrometer_t *ctx );

/**
 * @brief Set the spectral measurement enabled bit function
 *
 * @param ctx          Click object. 
 * @param state
 * <pre>
 *       - 1 : spectral measurement enabled bit set
 *       - 0 : spectral measurement enabled bit cleared
 * </pre>
 *
 * @description This function is used to set the SP_EN (spectral measurement enabled) bit on the chip.
**/
void spectrometer_sp_en ( spectrometer_t *ctx, uint8_t state );

/**
 * @brief Starting the SMUX function
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to start the SMUX command by setting the SMUXEN bit in 
 *              register ENABLE.
 *
 * @note The SMUXEN bit gets cleared automatically as soon as SMUX operation is finished.
**/
void spectrometer_smux_en ( spectrometer_t *ctx );

/**
 * @brief Reading and Polling the the SMUX Enable bit function
 *
 * @param ctx          Click object.
 *
 * @returns  1 : SMUX operation is not finished,     0 : SMUX operation is finished
 *
 * @description This function is used to read and poll the the SMUX Enable bit in Enable Register.
**/
uint8_t spectrometer_get_smux_en ( spectrometer_t *ctx );

/**
 * @brief Reading and Polling the the AVALID bit function
 *
 * @param ctx          Click object.
 * 
 * @returns   1 : Data ready,       0 : Data not ready
 *
 * @description This function is used to read and poll the the AVALID bit in order to 
 *              check data ready.
**/
uint8_t spectrometer_get_data_ready ( spectrometer_t *ctx );

/**
 * @brief SMUX Configuration for F1,F2,F3,F4,NIR,Clear function
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to map the individual Photo diodes to dedicated ADCs using 
 *              SMUX Configuration for F1-F4,Clear,NIR.
**/
void spectrometer_f1f4_clr_nir ( spectrometer_t *ctx );

/**
 * @brief SMUX Configuration for F5,F6,F7,F8,NIR,Clear function
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to map the individual Photo diodes to dedicated ADCs using 
 *              SMUX Configuration for F5-F8,Clear,NIR.
**/
void spectrometer_f5f8_clr_nir ( spectrometer_t *ctx );

/**
 * @brief Flicker Detect Configuration function
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to map the individual Photo diodes to dedicated ADCs using
 *              SMUX Configuration for Flicker detection.
**/
void spectrometer_fd_cfg ( spectrometer_t *ctx );

/**
 * @brief Select Register bank function
 *
 * @param ctx          Click object. 
 * @param reg_bank     8-bit data that defines register bank to address
 *
 * @description This function is used to select which Register bank to address.
 *
 * @note reg_bank bit(4) is set to '1' for setting the 0x00-0x7f.
**/
void spectrometer_reg_bank_cfg ( spectrometer_t *ctx, uint8_t reg_bank );

/**
 * @brief Default configuration function
 *
 * @param ctx          Click object.
 * 
 * @description This function is used to apply the default configuration used to demonstrate 
 * the usage of the click board.
**/
void spectrometer_def_cfg ( spectrometer_t *ctx );

/**
 * @brief Raw Read Mode 1 function
 *
 * @param ctx          Click object. 
 * @param adc_data     Output adc values
 *
 * @description This function is used to read out channels with SMUX configration 1; F1-F4, Clear.
**/
void spectrometer_raw_rd_val_mode_1 ( spectrometer_t *ctx, uint8_t *adc_data );

/**
 * @brief Raw Read Mode 2 function
 *
 * @param ctx          Click object. 
 * @param adc_data     Output adc values
 *
 * @description This function is used to read out channels with SMUX configration 2; F5-F8, Clear.
**/
void spectrometer_raw_rd_val_mode_2 ( spectrometer_t *ctx, uint8_t *adc_data );

/**
 * @brief name function
 *
 * @param ctx          Click object.
 * 
 * @returns result 8-bit status from FD_Status register
 *
 * @description This function is used to detect flicker for 100 and 120 Hz.
**/
uint8_t spectrometer_flicker_detection ( spectrometer_t *ctx );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx          Click object.
 * 
 * @returns   1 : Interrupt has not occured,     0 : Interrupt has occured
 *
 * @description This function is used to check if an interrupt has occured.
**/
uint8_t spectrometer_get_int ( spectrometer_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SPECTROMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

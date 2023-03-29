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
 * \brief This file contains API for Ecg 6 Click driver.
 *
 * \addtogroup ecg6 Ecg 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ECG6_H
#define ECG6_H

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
#define ECG6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ECG6_RETVAL  uint8_t

#define ECG6_OK           0x00
#define ECG6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg_stat  Register Status
 * \{
 */
#define ECG6_REG_INTERRUPT_STATUS_1                   0x00
#define ECG6_REG_INTERRUPT_STATUS_2                   0x01
#define ECG6_REG_INTERRUPT_ENABLE_1                   0x02
#define ECG6_REG_INTERRUPT_ENABLE_2                   0x03
/** \} */

/**
 * \defgroup reg_fifo  Register FIFO
 * \{
 */
#define ECG6_REG_FIFO_WRITE                           0x04
#define ECG6_REG_OVERFLOW_CNT                         0x05
#define ECG6_REG_FIFO_READ                            0x06
#define ECG6_REG_FIFO_DATA                            0x07
#define ECG6_REG_FIFO_CFG                             0x08
/** \} */

/**
 * \defgroup reg_fifo_data  Register FIFO Data
 * \{
 */
#define ECG6_REG_FIFO_DATA_CTRL_1                     0x09
#define ECG6_REG_FIFO_DATA_CTRL_2                     0x0A
/** \} */

/**
 * \defgroup reg_sys_ctrl  Register System CTRL
 * \{
 */
#define ECG6_REG_SYSTEM_CTRL                          0x0D
/** \} */


/**
 * \defgroup reg_ppg_cfg  Register PPG CFG
 * \{
 */
#define ECG6_REG_PPG_CFG_1                            0x0E
#define ECG6_REG_PPG_CFG_2                            0x0F
#define ECG6_REG_PROX_INT_THR                         0x10
/** \} */

/**
 * \defgroup reg_led  Register Led Pulse Amplitude
 * \{
 */
#define ECG6_REG_LED_PULSE_AMPLITUDE_1                0x11
#define ECG6_REG_LED_PULSE_AMPLITUDE_2                0x12
#define ECG6_REG_LED_RANGE                            0x14
#define ECG6_REG_LED_PILOT_PULSE_AMPLITUDE            0x15
/** \} */

/**
 * \defgroup reg_ecg_cfg  Register ECG CFG
 * \{
 */
#define ECG6_REG_CONFIG_1                             0x3C
#define ECG6_REG_CONFIG_3                             0x3E
/** \} */

/**
 * \defgroup reg_part_id  Register Part ID
 * \{
 */
#define ECG6_REG_PART_ID                              0xFF
/** \} */

/**
 * \defgroup ecg_reg  ECG6 Reg Interrupt Status 1
 * \{
 */
#define ECG6_INTS1_A_FULL_ON                          0x80
#define ECG6_INTS1_A_FULL_OFF                         0x00
#define ECG6_INTS1_PPG_RDY_ON                         0x40
#define ECG6_INTS1_PPG_RDY_OFF                        0x00
#define ECG6_INTS1_ALC_OVF_ON                         0x20
#define ECG6_INTS1_ALC_OVF_OFF                        0x00
#define ECG6_INTS1_PROX_INIT_ON                       0x10
#define ECG6_INTS1_PROX_INIT_OFF                      0x00
#define ECG6_INTS1_PWR_RDY_ON                         0x01
#define ECG6_INTS1_PWR_RDY_OFF                        0x00
/** \} */

/**
 * \defgroup ecg_reg  ECG6 Reg Interrupt Status 2
 * \{
 */
#define ECG6_INTS2_VDD_OOR_ON                         0x80
#define ECG6_INTS2_VDD_OOR_OFF                        0x00
#define ECG6_INTS2_DRDY_ON                            0x04
#define ECG6_INTS2_DRDY_OFF                           0x00
/** \} */

/**
 * \defgroup reg_enb_1 ECG Reg Interrupt Enable 1
 * \{
 */
#define ECG6_INTE1_A_FULL_ENABLE                      0x80
#define ECG6_INTE1_A_FULL_DISABLE                     0x00
#define ECG6_INTE1_PPG_RDY_ENABLE                     0x40
#define ECG6_INTE1_PPG_RDY_DISABLE                    0x00
#define ECG6_INTE1_ALC_OVF_ENABLE                     0x20
#define ECG6_INTE1_ALC_OVF_DISABLE                    0x00
#define ECG6_INTE1_PROX_INT_ENABLE                    0x10
#define ECG6_INTE1_PROX_INT_DISABLE                   0x00
/** \} */

/**
 * \defgroup reg_enb_2 ECG Reg Interrupt Enable 2
 * \{
 */
#define ECG6_INTS2_VDD_OOR_ENABLE                     0x80
#define ECG6_INTS2_VDD_OOR_DISABLE                    0x00
#define ECG6_INTS2_DRDY_ENABLE                        0x04
#define ECG6_INTS2_DRDY_DISABLE                       0x00
/** \} */

/**
 * \defgroup reg_fifo_cfg Ecg Reg Interrupt FIFO CFG
 * \{
 */
#define ECG6_FCFG_A_FULL_CLR                          0x40
#define ECG6_FCFG_A_FULL_NO_CLR                       0x00
#define ECG6_FCFG_A_FULL_TYPE_RPT                     0x00
#define ECG6_FCFG_A_FULL_TYPE_ONCE                    0x20
#define ECG6_FCFG_FIFO_ROLLS_ON_FULL_ON               0x10
#define ECG6_FCFG_FIFO_ROLLS_ON_FULL_OFF              0x00
/** \} */

/**
 * \defgroup reg_sys_ctrl Ecg Reg System CTRL
 * \{
 */
#define ECG6_SYSCTRL_FIFO_ENABLE                      0x04
#define ECG6_SYSCTRL_FIFO_DISABLE                     0x00
#define ECG6_SYSCTRL_SHUTDOWN_ENABLE                  0x02
#define ECG6_SYSCTRL_SHUTDOWN_DISABLE                 0x00
#define ECG6_SYSCTRL_RESET_ENABLE                     0x01
#define ECG6_SYSCTRL_RESET_DISABLE                    0x00
/** \} */

/**
 * \defgroup reg_ppg_cfg_1 Register PPG CFG 1
 * \{
 */
#define ECG6_PPGCFG1_PPG_ADC_RGE_4096nA               0x00
#define ECG6_PPGCFG1_PPG_ADC_RGE_8192nA               0x40
#define ECG6_PPGCFG1_PPG_ADC_RGE_16384nA              0x80
#define ECG6_PPGCFG1_PPG_ADC_RGE_32768nA              0xC0

#define ECG6_PPGCFG1_PPG_SR_10n1                      0x00
#define ECG6_PPGCFG1_PPG_SR_20n1                      0x04
#define ECG6_PPGCFG1_PPG_SR_50n1                      0x08
#define ECG6_PPGCFG1_PPG_SR_84n1                      0x0C
#define ECG6_PPGCFG1_PPG_SR_100n1                     0x10
#define ECG6_PPGCFG1_PPG_SR_200                       0x14
#define ECG6_PPGCFG1_PPG_SR_400                       0x18
#define ECG6_PPGCFG1_PPG_SR_800                       0x1C
#define ECG6_PPGCFG1_PPG_SR_1000                      0x20
#define ECG6_PPGCFG1_PPG_SR_1600                      0x24
#define ECG6_PPGCFG1_PPG_SR_3200                      0x28
#define ECG6_PPGCFG1_PPG_SR_10n2                      0x2C
#define ECG6_PPGCFG1_PPG_SR_20n2                      0x30
#define ECG6_PPGCFG1_PPG_SR_50n2                      0x34
#define ECG6_PPGCFG1_PPG_SR_84n2                      0x38
#define ECG6_PPGCFG1_PPG_SR_100n2                     0x3C

#define ECG6_PPGCFG1_PPG_PW_50us                      0x00
#define ECG6_PPGCFG1_PPG_PW_100us                     0x01
#define ECG6_PPGCFG1_PPG_PW_200us                     0x02
#define ECG6_PPGCFG1_PPG_PW_400us                     0x03
/** \} */

/**
 * \defgroup reg_ppg_cfg_2 Register PPG CFG 2
 * \{
 */
#define ECG6_PPGCFG2_SMP_AVE_1                        0x00
#define ECG6_PPGCFG2_SMP_AVE_2                        0x01
#define ECG6_PPGCFG2_SMP_AVE_4                        0x02
#define ECG6_PPGCFG2_SMP_AVE_8                        0x03
#define ECG6_PPGCFG2_SMP_AVE_16                       0x04
#define ECG6_PPGCFG2_SMP_AVE_32                       0x05
/** \} */

/**
 * \defgroup reg_range_led  Register Led Range 
 * \{
 */
#define ECG6_LRANG_LED2_SMP_AVE_50                    0x00
#define ECG6_LRANG_LED2_SMP_AVE_100                   0x04
#define ECG6_LRANG_LED1_SMP_AVE_50                    0x00
#define ECG6_LRANG_LED1_SMP_AVE_100                   0x01
/** \} */

/**
 * \defgroup reg_cfg_1 Register Config 1
 * \{
 */
#define ECG6_CFG1_ADC_OSR_1600                        0x00
#define ECG6_CFG1_ADC_OSR_800                         0x01
#define ECG6_CFG1_ADC_OSR_400                         0x02
#define ECG6_CFG1_ADC_OSR_200                         0x03
#define ECG6_CFG1_ADC_OSR_3200                        0x04
/** \} */

/**
 * \defgroup reg_cfg_3 Register Config 3
 * \{
 */
#define ECG6_CFG3_PGA_GAIN_1                          0x00
#define ECG6_CFG3_PGA_GAIN_2                          0x04
#define ECG6_CFG3_PGA_GAIN_4                          0x08
#define ECG6_CFG3_PGA_GAIN_8                          0x0C
#define ECG6_CFG3_IA_GAIN_5                           0x00
#define ECG6_CFG3_IA_GAIN_9p5                         0x01
#define ECG6_CFG3_IA_GAIN_20                          0x02
#define ECG6_CFG3_IA_GAIN_50                          0x03
/** \} */

/**
 * \defgroup reg_part_id Register Part ID
 * \{
 */
#define ECG6_DEF_PART_ID                              0x1E 
/** \} */

/**
 * \defgroup dev_slv_addr  Device Slave Address
 * \{
 */
#define ECG6_DEVICE_SLAVE_ADDRESS                     0x5E
/** \} */

/**
 * \defgroup fifo_data_ctrl  FIFO DATA CTRL
 * \{
 */
#define ECG6_SENSOR_PPG_LED_1                         0x01
#define ECG6_SENSOR_PPG_LED_2                         0x02
#define ECG6_SENSOR_PPG_PILOT_LED_1                   0x05
#define ECG6_SENSOR_PPG_PILOT_LED_2                   0x06
#define ECG6_SENSOR_ECG                               0x09
#define ECG6_SENSOR_NONE                              0x00 
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
typedef struct
{
   uint8_t a_full;
   uint8_t ppg_rdy;
   uint8_t alc_ovf;
   uint8_t prox_int;
   uint8_t pwr_rdy;
   uint8_t vdd_oor;
   uint8_t ecg_rdy;
   
} ecg6_int_status_t;

typedef struct
{
     uint32_t element_1;
     uint32_t element_2;
     uint32_t element_3;
     uint32_t element_4;
     
} ecg6_element_t;

typedef struct
{
    ecg6_element_t sample_0;
    ecg6_element_t sample_1;
    ecg6_element_t sample_2;
    ecg6_element_t sample_3;
    ecg6_element_t sample_4;
    ecg6_element_t sample_5;
    ecg6_element_t sample_6;
    ecg6_element_t sample_7;
    ecg6_element_t sample_8;
    ecg6_element_t sample_9;
    ecg6_element_t sample_10;
    ecg6_element_t sample_11;
    ecg6_element_t sample_12;
    ecg6_element_t sample_13;
    ecg6_element_t sample_14;
    ecg6_element_t sample_15;
    ecg6_element_t sample_16;
    ecg6_element_t sample_17;
    ecg6_element_t sample_18;
    ecg6_element_t sample_19;
    ecg6_element_t sample_20;
    ecg6_element_t sample_21;
    ecg6_element_t sample_22;
    ecg6_element_t sample_23;
    ecg6_element_t sample_24;
    ecg6_element_t sample_25;
    ecg6_element_t sample_26;
    ecg6_element_t sample_27;
    ecg6_element_t sample_28;
    ecg6_element_t sample_29;
    ecg6_element_t sample_30;
    ecg6_element_t sample_31;

}ecg6_fifo_t;

typedef struct
{
    uint8_t element_1;
    uint8_t element_2;
    uint8_t element_3;
    uint8_t element_4;

} ecg6_cfg_element_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 


    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} ecg6_t;

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

} ecg6_cfg_t;

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
void ecg6_cfg_setup ( ecg6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ECG6_RETVAL ecg6_init ( ecg6_t *ctx, ecg6_cfg_t *cfg );

/**
 * @brief Default configuration for ECG sensor
 *
 * @param ctx  Click object.
 *
 * @note: This function contains:
 * <pre>
 * --  ECG6_REG_INTERRUPT_ENABLE_1
 *     ----------------------------
 *     ECG6_INTS1_A_FULL_OFF
 *     ECG6_INTS1_PPG_RDY_OFF
 *     ECG6_INTS1_ALC_OVF_OFF
 *     ECG6_INTS1_PROX_INIT_OFF
 *     ECG6_INTS1_PWR_RDY_OFF
 *
 * --  ECG6_REG_INTERRUPT_ENABLE_2
 *     ---------------------------
 *     ECG6_INTS2_VDD_OOR_OFF
 *     ECG6_INTS2_DRDY_ON
 *
 * --  ECG6_REG_SYSTEM_CTRL
 *     ---------------------
 *     ECG6_SYSCTRL_RESET_ENABLE
 *     Delay - 100ms
 *
 * --  ECG6_REG_FIFO_CFG
 *     -----------------
 *     ECG6_FCFG_A_FULL_CLR
 *     ECG6_FCFG_A_FULL_TYPE_ONCE
 *     ECG6_FCFG_FIFO_ROLLS_ON_FULL_ON
 *     0x0F
 *
 * --  ----------------------------------
 *     cfg.element_1 = ECG6_SENSOR_ECG;
 *     cfg.element_2 = ECG6_SENSOR_NONE;
 *     cfg.element_3 = ECG6_SENSOR_NONE;
 *     cfg.element_4 = ECG6_SENSOR_NONE;
 *     ecg6_cfg_element( &cfg );
 *     ----------------------------------
 *
 * --  ECG6_REG_PPG_CFG_1
 *      -------------------
 *      ECG6_PPGCFG1_PPG_ADC_RGE_32768nA
 *      ECG6_PPGCFG1_PPG_SR_100n1
 *      ECG6_PPGCFG1_PPG_PW_100us
 *
 * --  ECG6_REG_PPG_CFG_2  ( 0x06 )
 *
 * --  ECG6_REG_LED_RANGE
 *      -------------------
 *      ECG6_LRANG_LED2_SMP_AVE_50
 *      ECG6_LRANG_LED1_SMP_AVE_50
 *
 * --  ECG6_REG_SYSTEM_CTRL
 *      ----------------------
 *      ECG6_SYSCTRL_FIFO_ENABLE
 *      ECG6_SYSCTRL_SHUTDOWN_DISABLE
 *      ECG6_SYSCTRL_RESET_DISABLE
 *
 * --  ECG6_REG_CONFIG_1
 *      --------------------
 *      ECG6_CFG1_ADC_OSR_3200
 *
 * --  ECG6_REG_CONFIG_3
 *      ------------------
 *      ECG6_CFG3_PGA_GAIN_4
 *      ECG6_CFG3_IA_GAIN_5
 *
 * --  ecg6_set_led_pulse( 0x00, 0x00 );
 *
 * --  ECG6_REG_FIFO_WRITE ( 0x00 )
 * --  ECG6_REG_OVERFLOW_CNT ( 0x00 )
 * --  ECG6_REG_FIFO_READ ( 0x00 )
 *
 *      Delay - 100ms
 * </pre>
 *
 * @description This function executes default configuration for Ecg6 click.
 */
void ecg6_default_cfg ( ecg6_t *ctx );

/**
 * @brief Generic Write function
 *
 * @param ctx      Click object. 
 * @param reg      Address where data be written
 * @param in_data  Data to be written
 *
 * @description Function writes data to the register.
 */
void ecg6_write_data( ecg6_t *ctx, uint8_t reg, uint8_t in_data );

/**
 * @brief Generic Write buffer function
 *
 * @param ctx       Click object.
 * @param reg       Address where data be written
 * @param data_buf  Data buffer to be written
 * @param len       Number of the data in buffer
 *
 * @description Function writes data buffer to the register.
 */
void ecg6_write_data_buf( ecg6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Read function
 *
 * @param ctx  Click object. 
 * @param reg  Address which from data be read
 *
 * @returns Data byte
 *
 * @description Function reads data from the register.
 */
uint8_t ecg6_read_data( ecg6_t *ctx, uint8_t reg );

/**
 * @brief Generic Read buffer function
 *
 * @param ctx       Click object. 
 * @param reg       Address which from data be read
 * @param data_buf  Data buffer for data stored
 * @param len       Number of the data for read
 *
 * @description Function reads data buffer from the register.
 */
void ecg6_read_data_buf( ecg6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for check path ID
 *
 * @param ctx      Click object.
 * 
 * @returns 0 - OK, 1 - Wrong ID
 *
 * @note: Default ID is ECG6_DEF_PART_ID
 * @description Function checks path ID.
 */
uint8_t ecg6_check_path_id ( ecg6_t *ctx );

/**
 * @brief Function for configuration sensors to element
 *
 * @param ctx       Click object. 
 * @param cfg       Config structure
 *
 * @note: Select sensors.
 * <pre> 
 * Depending on the set sensors - reading fifo, use the elements. 
 * Example: If you set the ECG to the first element, 
 * when you read the ecg it will be given to the first element.
 * <pre>
 *
 * @description
 */
void ecg6_cfg_element( ecg6_t *ctx, ecg6_cfg_element_t *cfg );

/**
 * @brief Funcrion for set LED pulse
 *
 * @param ctx      Click object. 
 * @param ir_led   IR LED pulse ( from 0x00 to 0xFF )
 * @param red_led  RED LED pulse ( from 0x00 to 0xFF )
 *
 * @note: This function is required to read PPG.
 *
 * @description This functions is contains in default configuration for PPG sensor
 */
void ecg6_set_led_pulse( ecg6_t *ctx, uint8_t ir_led, uint8_t red_led );

/**
 * @brief Default configuration for PPG sensor
 *
 * @param ctx      Click object. 
 *
 * @note: This function contains:
 * <pre>
 * --  ECG6_REG_INTERRUPT_ENABLE_1
 *     ----------------------------
 *     ECG6_INTS1_A_FULL_OFF
 *     ECG6_INTS1_PPG_RDY_ON
 *     ECG6_INTS1_ALC_OVF_OFF
 *     ECG6_INTS1_PROX_INIT_OFF
 *     ECG6_INTS1_PWR_RDY_OFF
 *
 * --  ECG6_REG_INTERRUPT_ENABLE_2
 *     ---------------------------
 *     ECG6_INTS2_VDD_OOR_OFF
 *     ECG6_INTS2_DRDY_OFF
 *
 * --  ECG6_REG_SYSTEM_CTRL
 *     ---------------------
 *     ECG6_SYSCTRL_RESET_ENABLE
 *     Delay - 100ms
 *
 * --  ECG6_REG_FIFO_CFG
 *     -----------------
 *     ECG6_FCFG_A_FULL_CLR
 *     ECG6_FCFG_A_FULL_TYPE_ONCE
 *     ECG6_FCFG_FIFO_ROLLS_ON_FULL_ON
 *     0x0F
 *
 * --  ----------------------------------
 *     cfg.element_1 = ECG6_SENSOR_PPG_LED_1;
 *     cfg.element_2 = ECG6_SENSOR_PPG_LED_2;
 *     cfg.element_3 = ECG6_SENSOR_ECG;
 *     cfg.element_4 = ECG6_SENSOR_NONE;
 *     ecg6_cfg_element( &cfg );
 *     ----------------------------------
 *
 * --  ECG6_REG_PPG_CFG_1
 *      -------------------
 *      ECG6_PPGCFG1_PPG_ADC_RGE_32768nA
 *      ECG6_PPGCFG1_PPG_SR_100n1
 *      ECG6_PPGCFG1_PPG_PW_100us
 *
 * --  ECG6_REG_PPG_CFG_2  ( 0x06 )
 *
 * --  ECG6_REG_LED_RANGE
 *      -------------------
 *      ECG6_LRANG_LED2_SMP_AVE_50
 *      ECG6_LRANG_LED1_SMP_AVE_50
 *
 * --  ECG6_REG_SYSTEM_CTRL
 *      ----------------------
 *      ECG6_SYSCTRL_FIFO_ENABLE
 *      ECG6_SYSCTRL_SHUTDOWN_DISABLE
 *      ECG6_SYSCTRL_RESET_DISABLE
 *
 * --  ECG6_REG_CONFIG_1
 *      --------------------
 *      ECG6_CFG1_ADC_OSR_3200
 *
 * --  ECG6_REG_CONFIG_3
 *      ------------------
 *      ECG6_CFG3_PGA_GAIN_4
 *      ECG6_CFG3_IA_GAIN_5
 *
 * --  ecg6_set_led_pulse( 0xFF, 0xFF );
 *
 * --  ECG6_REG_FIFO_WRITE ( 0x00 )
 * --  ECG6_REG_OVERFLOW_CNT ( 0x00 )
 * --  ECG6_REG_FIFO_READ ( 0x00 )
 *
 *      Delay - 100ms
 * </pre>
 *
 * @description This function executes default configuration for PPG sensor.
 */
uint8_t ecg6_ppg_default_config ( ecg6_t *ctx );

/**
 * @brief Get one sample from FIFO
 *
 * @param ctx         Click object. 
 * @param element     sample ( elements ) structure
 * @param num_sample  The position of the sample being read
 *
 * @note: This function reads one sample (of 4 elements)
 * @description This function gets one sample from FIFO
 */
void ecg6_get_sample_data( ecg6_t *ctx, ecg6_element_t *element, uint8_t num_sample );

/**
 * @brief Get all samples from FIFO
 *
 * @param ctx        Click object. 
 * @param fifo_data  samples ( elements ) structure
 *
 * @note: This function reads all samples ( 32 samples per 4 elements )
 * @description This function gets all samples from FIFO
 */
void ecg6_get_all_samples( ecg6_t *ctx, ecg6_fifo_t *fifo_data );

/**
 * @brief Get Interrupt registers status
 *
 * @param ctx       Click object. 
 * @param status    Status strusture
 *
 * @description This function reads all interupt statuses 
 *              and writes them to the structure.
 */
void ecg6_get_interrupt_status ( ecg6_t *ctx, ecg6_int_status_t *status );

/**
 * @brief Get Interrupt pin state
 *
 * @param ctx      Click object.
 * 
 * @return Interrupt pin state
 * @description This function gets interrupt pin state.
 */
uint8_t ecg6_int_pin_state ( ecg6_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _ECG6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

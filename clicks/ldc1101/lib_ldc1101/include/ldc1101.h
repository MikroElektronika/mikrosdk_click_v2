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
 * \brief This file contains API for LDC 1101 Click driver.
 *
 * \addtogroup ldc1101 LDC 1101 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LDC1101_H
#define LDC1101_H

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

#define LDC1101_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LDC1101_RETVAL  uint8_t

#define LDC1101_OK           0x00
#define LDC1101_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define LDC1101_REG_CFG_RP_MEASUREMENT_DYNAMIC_RANGE         0x01
#define LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_1             0x02
#define LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_2             0x03
#define LDC1101_REG_CFG_RP_L_CONVERSION_INTERVAL             0x04
#define LDC1101_REG_CFG_ADDITIONAL_DEVICE                    0x05
#define LDC1101_REG_RP_THRESH_H_LSB                          0x06
#define LDC1101_REG_RP_THRESH_H_MSB                          0x07
#define LDC1101_REG_RP_THRESH_L_LSB                          0x08
#define LDC1101_REG_RP_THRESH_L_MSB                          0x09
#define LDC1101_REG_CFG_INTB_MODE                            0x0A
#define LDC1101_REG_CFG_POWER_STATE                          0x0B
#define LDC1101_REG_AMPLITUDE_CONTROL_REQUIREMENT            0x0C
#define LDC1101_REG_L_THRESH_HI_LSB                          0x16
#define LDC1101_REG_L_THRESH_HI_MSB                          0x17
#define LDC1101_REG_L_THRESH_LO_LSB                          0x18
#define LDC1101_REG_L_THRESH_LO_MSB                          0x19
#define LDC1101_REG_RP_L_MEASUREMENT_STATUS                  0x20
#define LDC1101_REG_RP_DATA_LSB                              0x21
#define LDC1101_REG_RP_DATA_MSB                              0x22
#define LDC1101_REG_L_DATA_LSB                               0x23
#define LDC1101_REG_L_DATA_MSB                               0x24
#define LDC1101_REG_LHR_RCOUNT_LSB                           0x30
#define LDC1101_REG_LHR_RCOUNT_MSB                           0x31
#define LDC1101_REG_LHR_OFFSET_LSB                           0x32
#define LDC1101_REG_LHR_OFFSET_MSB                           0x33
#define LDC1101_REG_CFG_LHR                                  0x34
#define LDC1101_REG_LHR_DATA_LSB                             0x38
#define LDC1101_REG_LHR_DATA_MID                             0x39
#define LDC1101_REG_LHR_DATA_MSB                             0x3A
#define LDC1101_REG_LHR_STATUS                               0x3B
#define LDC1101_REG_DEVICE_RID_VALUE                         0x3E
#define LDC1101_REG_CHIP_ID                                  0x3F
/** \} */

/**
 * \defgroup id_value Chip ID value
 * \{
 */
#define LDC1101_CHIP_ID_VAL                                  0xD4
/** \} */

/**
 * \defgroup rp_set RP_SET Field Descriptions
 * \{
 */
#define LDC1101_RP_SET_RP_MAX_IS_DRIVEN                      0x00
#define LDC1101_RP_SET_RP_MAX_CURRENT_IS_IGNORED             0x80
#define LDC1101_RP_SET_RP_MAX_96KOhm                         0x00
#define LDC1101_RP_SET_RP_MAX_48KOhm                         0x10
#define LDC1101_RP_SET_RP_MAX_24KOhm                         0x20
#define LDC1101_RP_SET_RP_MAX_12KOhm                         0x30
#define LDC1101_RP_SET_RP_MAX_6KOhm                          0x40
#define LDC1101_RP_SET_RP_MAX_3KOhm                          0x50
#define LDC1101_RP_SET_RP_MAX_1_5KOhm                        0x60
#define LDC1101_RP_SET_RP_MAX_0_75KOh                        0x70
#define LDC1101_RP_SET_RP_MIN_96KOhm                         0x00
#define LDC1101_RP_SET_RP_MIN_48KOhm                         0x01
#define LDC1101_RP_SET_RP_MIN_24KOhm                         0x02
#define LDC1101_RP_SET_RP_MIN_12KOhm                         0x03
#define LDC1101_RP_SET_RP_MIN_6KOhm                          0x04
#define LDC1101_RP_SET_RP_MIN_3KOhm                          0x05
#define LDC1101_RP_SET_RP_MIN_1_5KOhm                        0x06
#define LDC1101_RP_SET_RP_MIN_0_75KOh                        0x07
/** \} */

/**
 * \defgroup cfg_time_const1 Configure Internal Time Constant 1
 * \{
 */
#define LDC1101_TC1_C1_0_75pF                                0x00
#define LDC1101_TC1_C1_1_5pF                                 0x40
#define LDC1101_TC1_C1_3pF                                   0x80
#define LDC1101_TC1_C1_6pF                                   0xC0
#define LDC1101_TC1_R1_417kOhm                               0x00
#define LDC1101_TC1_R1_212_7kOhm                             0x10
#define LDC1101_TC1_R1_21_1kOhm                              0x1F
/** \} */

/**
 * \defgroup cfg_time_const2 Configure Internal Time Constant 2
 * \{
 */
#define LDC1101_TC2_C2_3pF                                   0x00
#define LDC1101_TC2_C2_6pF                                   0x40
#define LDC1101_TC2_C2_12pF                                  0x80
#define LDC1101_TC2_C2_24pF                                  0xC0
#define LDC1101_TC2_R2_835kOhm                               0x00
#define LDC1101_TC2_R2_426_4kOhm                             0x20
#define LDC1101_TC2_R2_30_5kOhm                              0x3F
/** \} */

/**
 * \defgroup cfg_rp_l Configure RP+L conversion interval
 * \{
 */
#define LDC1101_DIG_CFG_MIN_FREQ_500kHz                      0x00
#define LDC1101_DIG_CFG_MIN_FREQ_118kHz                      0xD0
#define LDC1101_DIG_CFG_MIN_FREQ_8MHz                        0xF0
#define LDC1101_DIG_CFG_RESP_TIME_192s                       0x02
#define LDC1101_DIG_CFG_RESP_TIME_384s                       0x03
#define LDC1101_DIG_CFG_RESP_TIME_768s                       0x04
#define LDC1101_DIG_CFG_RESP_TIME_1536s                      0x05
#define LDC1101_DIG_CFG_RESP_TIME_3072s                      0x06
#define LDC1101_DIG_CFG_RESP_TIME_6144s                      0x07
/** \} */

/**
 * \defgroup cfg_add_device Configure additional device settings
 * \{
 */
#define LDC1101_ALT_CFG_SHUTDOWN_ENABLE                      0x02
#define LDC1101_ALT_CFG_SHUTDOWN_DISABLE                     0x00
#define LDC1101_ALT_CFG_L_OPTIMAL_DISABLED                   0x00
#define LDC1101_ALT_CFG_L_OPTIMAL_ENABLE                     0x01
#define LDC1101_ALT_CFG_R_OPTIMAL_ENABLE                     0x02
#define LDC1101_REQ_AMPLINTUDE_REGUL_CONVERT                 0x00
#define LDC1101_CONTINUES_CONVERT                            0x01
/** \} */

/**
 * \defgroup cfg_intb Configure INTB reporting on SDO pin
 * \{
 */
#define LDC1101_INTB_MODE_DONT_REPORT_INTB_ON_SDO_PIN        0x00
#define LDC1101_INTB_MODE_REPORT_INTB_ON_SDO_PIN             0x80
#define LDC1101_INTB_MODE_REPORT_LHR_DATA_READY              0x20
#define LDC1101_INTB_MODE_L_CONVERSION_TO_L_THRESHOLDS       0x10
#define LDC1101_INTB_MODE_L_CONVERSION_TO_L_HIGH_THRESHOLDS  0x08
#define LDC1101_INTB_MODE_REPORT_RP_L_DATA_READY             0x04
#define LDC1101_INTB_MODE_RP_CONVERSION_TO_L_THRESHOLDS      0x02
#define LDC1101_INTB_MODE_RP_CONVERSION_TO_L_HIGH_THRESHOLDS 0x01
#define LDC1101_INTB_MODE_NO_OUTPUT                          0x00
/** \} */

/**
 * \defgroup thr_res_mes Threshold, Resolution Measurement Count/Offset Setting
 * \{
 */
#define LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG                0x00
#define LDC1101_RES_L_MEAS_REF_CNT_DEF_CFG                   0x00
#define LDC1101_RES_OFF_L_MEAS_REF_CNT_DEF_CFG               0x00
/** \} */

/**
 * \defgroup cfg_power_state Configure Power State
 * \{
 */
#define LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE             0x00
#define LDC1101_FUNC_MODE_SLEEP_MODE                         0x01
#define LDC1101_FUNC_MODE_SHUTDOWN_MODE                      0x02
/** \} */

/**
 * \defgroup cfg_dev_settings Configure additional device settings
 * \{
 */
#define LDC1101_SENSOR_FREQ_DIV_NO                           0x00
#define LDC1101_SENSOR_FREQ_DIV_BY_2                         0x01
#define LDC1101_SENSOR_FREQ_DIV_BY_4                         0x02
#define LDC1101_SENSOR_FREQ_DIV_BY_8                         0x04
/** \} */

/**
 * \defgroup high_res High Resolution L Configuration
 * \{
 */
#define LDC1101_LHR_CFG_FREQUENCY_NOT_DIVIDED                0x00
#define LDC1101_LHR_CFG_FREQUENCY_DIVIDED_BY_2               0x01
#define LDC1101_LHR_CFG_FREQUENCY_DIVIDED_BY_4               0x02
#define LDC1101_LHR_CFG_FREQUENCY_DIVIDED_BY_8               0x03
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
    digital_out_t cs;

    // Input pins 

    digital_in_t pwm;
    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} ldc1101_t;

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

    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ldc1101_cfg_t;

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
void ldc1101_cfg_setup ( ldc1101_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ldc1101 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LDC1101_RETVAL ldc1101_init ( ldc1101_t *ctx, ldc1101_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Ldc1101 click.
 * @note
 *    Click default configuration:
 * -------------------------------------------------
 * 
 * <pre>
 *    LDC1101_REG_CFG_RP_MEASUREMENT_DYNAMIC_RANGE
 * -------------------------------------------------
 *    LDC1101_RP_SET_RP_MIN_0_75KOh
 * </pre>
 * 
 * <pre>
 *    LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_1
 * -------------------------------------------------
 *    LDC1101_TC1_C1_3pF
 *    LDC1101_TC1_R1_212_7kOhm
 * </pre>
 *  
 * <pre>
 *    LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_2
 * -------------------------------------------------
 *    LDC1101_TC2_C2_12pF
 *    LDC1101_TC2_R2_426_4kOhm
 * </pre>
 *   
 * <pre>
 *    LDC1101_REG_CFG_RP_L_CONVERSION_INTERVAL
 * -------------------------------------------------
 *    LDC1101_DIG_CFG_RESP_TIME_384s
 * </pre>
 *   
 * <pre>
 *    LDC1101_REG_CFG_ADDITIONAL_DEVICE
 * -------------------------------------------------
 *    LDC1101_ALT_CFG_SHUTDOWN_DISABLE
 *    LDC1101_ALT_CFG_L_OPTIMAL_DISABLED
 * </pre>
 *    
 * <pre>
 *    LDC1101_REG_RP_THRESH_H_MSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *     
 * <pre>
 *    LDC1101_REG_RP_THRESH_L_LSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *      
 * <pre>
 *    LDC1101_REG_RP_THRESH_L_MSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *       
 * <pre>
 *    LDC1101_REG_CFG_INTB_MODE
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE
 * </pre>
 *        
 * <pre>
 *    LDC1101_REG_CFG_POWER_STATE
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_SLEEP_MODE
 * </pre>
 *         
 * <pre>
 *    LDC1101_REG_AMPLITUDE_CONTROL_REQUIREMENT
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE
 * </pre>
 *          
 * <pre>
 *    LDC1101_REG_L_THRESH_HI_LSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *           
 * <pre>
 *    LDC1101_REG_L_THRESH_HI_MSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *           
 * <pre>
 *    LDC1101_REG_L_THRESH_LO_LSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *           
 * <pre>
 *    LDC1101_REG_L_THRESH_LO_MSB
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_MODE_DEF_CFG
 * </pre>
 *            
 * <pre>
 *    LDC1101_REG_LHR_RCOUNT_LSB
 * -------------------------------------------------
 *    LDC1101_RES_L_MEAS_REF_CNT_DEF_CFG
 * </pre>
 *             
 * <pre>
 *    LDC1101_REG_LHR_RCOUNT_MSB
 * -------------------------------------------------
 *    LDC1101_RES_L_MEAS_REF_CNT_DEF_CFG
 * </pre>
 *              
 * <pre>
 *    LDC1101_REG_LHR_OFFSET_LSB
 * -------------------------------------------------
 *    LDC1101_RES_OFF_L_MEAS_REF_CNT_DEF_CFG
 * </pre>
 *               
 * <pre>
 *    LDC1101_REG_LHR_OFFSET_MSB
 * -------------------------------------------------
 *    LDC1101_RES_OFF_L_MEAS_REF_CNT_DEF_CFG
 * </pre>
 *                
 * <pre>
 *    LDC1101_REG_CFG_LHR
 * -------------------------------------------------
 *    LDC1101_SENSOR_FREQ_DIV_NO
 * </pre>
 * 
 *    Work configuration:
 * -------------------------------------------------
 * 
 * <pre>
 *    LDC1101_REG_CFG_RP_MEASUREMENT_DYNAMIC_RANGE
 * -------------------------------------------------
 *    LDC1101_RP_SET_RP_MAX_24KOhm
 *    LDC1101_RP_SET_RP_MIN_1_5KOhm
 * </pre>
 * 
 * <pre>
 *    LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_1
 * -------------------------------------------------
 *    LDC1101_TC1_C1_0_75pF
 *    LDC1101_TC1_R1_21_1kOhm
 * </pre>
 * 
 * <pre>
 *    LDC1101_REG_CFG_INTERNAL_TIME_CONSTANT_2
 * -------------------------------------------------
 *    LDC1101_TC2_C2_3pF
 *    LDC1101_TC2_R2_30_5kOhm
 * </pre>
 * 
 * <pre>
 *    LDC1101_REG_CFG_RP_L_CONVERSION_INTERVAL
 * -------------------------------------------------
 *    LDC1101_DIG_CFG_MIN_FREQ_118kHz
 *    LDC1101_DIG_CFG_RESP_TIME_768s
 * </pre>
 * 
 *    Set power mode:
 * -------------------------------------------------
 * 
 * <pre>
 *    LDC1101_REG_CFG_POWER_STATE
 * -------------------------------------------------
 *    LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE
 * </pre>
 */
void ldc1101_default_cfg ( ldc1101_t *ctx );

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
void ldc1101_generic_transfer 
( 
    ldc1101_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Functions for write one byte on address
 *
 * @param ctx          Click object.
 * @param reg_addr     Address in which the data will be written.
 * @param tx_data      Data which be written on the address.
 * 
 * @description Generic SPI read, for receiving packages.
 */
void ldc1101_generic_write ( ldc1101_t *ctx, uint8_t reg_addr, uint8_t tx_data );

/**
 * @brief Functions for read byte from address
 *
 * @param ctx          Click object.
 * @param reg_addr     Address in which the data will be written.
 * @return byte        uint8_t data which is read from the address.
 * 
 * @description Generic SPI transfer, for sending packages.
 */
uint8_t ldc1101_generic_read ( ldc1101_t *ctx, uint8_t reg_addr );

/**
 * @brief Set power mode function.
 *
 * @param ctx          Click object.
 * @param pwr_mode     Mode to be set.
 * <pre>
 * - 0 : LDC1101_FUNC_MODE_ACTIVE_CONVERSION_MODE;
 * - 1 : LDC1101_FUNC_MODE_SLEEP_MODE;
 * - 2 : LDC1101_FUNC_MODE_SHUTDOWN_MODE;
 *</pre>
 * @description Function set power mode.   
 */
void ldc1101_set_power_mode ( ldc1101_t *ctx, uint8_t pwr_mode );

/**
 * @brief Functions for go to L mode
 * 
 * @param ctx          Click object.
 */
void ldc1101_go_to_l_mode ( ldc1101_t *ctx );

/**
 * @brief Functions for go to RP mode
 * 
 * @param ctx          Click object.
 */
void ldc1101_go_to_r_mode ( ldc1101_t *ctx );

/**
 * @brief Functions for reads status
 * 
 * @param ctx          Click object.
 */
uint8_t ldc1101_get_status( ldc1101_t *ctx );

/**
 * @brief Functions for reads RP data
 *
 * @param ctx          Click object.
 * @return uint16_t RT data
 */
uint16_t ldc1101_get_rp_data ( ldc1101_t *ctx );

/**
 * @brief Functions for reads L data
 *
 * @param ctx          Click object.
 * @return uint16_t L data
 */
uint16_t ldc1101_get_l_data ( ldc1101_t *ctx );

/**
 * @brief Functions for get interrupt pin status
 *
 * @param ctx          Click object.
 * @return INT pin status
 */
uint8_t ldc1101_get_interrupt( ldc1101_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _LDC1101_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

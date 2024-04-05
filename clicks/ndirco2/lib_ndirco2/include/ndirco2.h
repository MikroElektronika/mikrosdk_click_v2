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
 * \brief This file contains API for NDIR CO2 Click driver.
 *
 * \addtogroup ndirco2 NDIR CO2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NDIRCO2_H
#define NDIRCO2_H

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
#define NDIRCO2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.bsy = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cal = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NDIRCO2_RETVAL  uint8_t

#define NDIRCO2_OK           0x00
#define NDIRCO2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define NDIRCO2_SOFTWARE_RESET_REG         0x00
#define NDIRCO2_CONTROL_REG                0x01
#define NDIRCO2_STATUS_REG                 0x02
#define NDIRCO2_DATA_LOW_REG               0x03
#define NDIRCO2_DATA_HIGH_REG              0x04
#define NDIRCO2_AVERAGING_COUNT_REG        0x07
#define NDIRCO2_HIGH_ALARM_THRESHOLD_REG   0x0C
#define NDIRCO2_LOW_ALARM_THRESHOLD_REG    0x0D
#define NDIRCO2_FUNCTION_REG               0x0F
/** \} */

/**
 * \defgroup reset Reset
 * \{
 */
#define NDIRCO2_NORMAL_STATE               0x00
#define NDIRCO2_RESET                      0x01
/** \} */

/**
 * \defgroup average_and_filter_sel  Average and filter sel
 * \{
 */
#define NDIRCO2_MOVING_AVERAGE_SEL         0x00
#define NDIRCO2_IIR_DIGITAL_FILTER_SEL     0x04
/** \} */

/**
 * \defgroup counter_time  Counter time
 * \{
 */
#define NDIRCO2_MIN_AVG_COUNT_1_TIME       0x00
#define NDIRCO2_MAX_AVG_COUNT_64_TIMES     0x3F
/** \} */

/**
 * \defgroup pwm_pin_state Pwm pin state
 * \{
 */
#define NDIRCO2_PWM_PIN_DISABLE            0x00
#define NDIRCO2_PWM_PIN_ENABLE             0x01
#define NDIRCO2_PWM_HIGH_CONCENTRATION     0x00
#define NDIRCO2_PWM_LOW_CONCENTRATION      0x08
/** \} */

/**
 * \defgroup check_and_mode Check and mode
 * \{
 */
#define NDIRCO2_CHECK_EACH_MEASURE         0x00
#define NDIRCO2_CHECK_AVG_COMPLETED        0x01
#define NDIRCO2_POWER_DOWN_MODE            0x00
#define NDIRCO2_CONTINUOUS_OP_MODE         0x01
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

    digital_in_t an;
    digital_in_t bsy;
    digital_in_t cal;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} ndirco2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t bsy;
    pin_name_t cal;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} ndirco2_cfg_t;

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
void ndirco2_cfg_setup ( ndirco2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NDIRCO2_RETVAL ndirco2_init ( ndirco2_t *ctx, ndirco2_cfg_t *cfg );

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
void ndirco2_generic_write ( ndirco2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void ndirco2_generic_read ( ndirco2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Read function
 *
 * @param ctx                 Click object.
 * @param register_address    Address which from data be read
 * @param data_out            Buffer where data be stored
 *
 * @return 0 - OK, 1 - wrong address parameter
 *
 * @description Function reads data from register.
 */
uint8_t ndirco2_read_register ( ndirco2_t *ctx, uint8_t register_address, uint16_t *data_out );

/**
 * @brief Generic Write function
 *
 * @param ctx                 Click object.
 * @param register_address    Address where data be written
 * @param transfer_data       Data which be written
 *
 * @return 0 - OK, 1 - wrong address parameter
 *
 * @description Function writes one byte data to register.
 */
uint8_t ndirco2_write_register ( ndirco2_t *ctx, uint8_t register_address, uint8_t transfer_data );

/**
 * @brief Current Address Read function
 *
 * @param ctx          Click object.
 * @param data_out     Buffer where data be stored
 * @param n_bytes      Number of bytes which be read
 *
 * @description Function reads one byte data from the last accessed address + 1.
 */
void ndirco2_read_current_address ( ndirco2_t *ctx, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief CO2 Concentration Read function
 *
 * @param ctx               Click object.
 * @param set_check_mode    0 - reads data after each measurement when data is ready to be read
 *                          1 - reads data after number of measurements determined by AVE register + 1
 * @param output_data       Buffer where 15-bit CO2 concentration data be stored
 *
 * @description Function reads 15-bit CO2 concentration data from data registers only when data is ready for reading
 * after each measurement or after number of measurements determined by AVE register + 1.
 */
void ndirco2_read_co2 ( ndirco2_t *ctx, uint8_t set_check_mode, uint16_t *output_data );

/**
 * @brief Data Ready Check function
 *
 * @param ctx           Click object.
 * 
 * @return 0 - data readable, 1 - busy state
 *
 * @description Function checks is data ready for reading by checking state of Busy pin.
 */
uint8_t ndirco2_check_busy ( ndirco2_t *ctx );

/**
 * @brief Average Complete Check function
 *
 * @param ctx           Click object.
 * 
 * @return 0 - averaging operation not completed yet, 1 - averaging operation completed
 *
 * @description Function checks is number of measurements exceeded determined value (averaging operation is completed).
 */
uint8_t ndirco2_check_average_complete ( ndirco2_t *ctx );

/**
 * @brief Mode Set function
 *
 * @param ctx           Click object.
 * @param select_mode   0 - power down mode, 1 (value different from zero) - continuous operating mode
 *
 * @desription Function puts device in desired mode (power down or continuous operating mode).
 */
void ndirco2_set_mode ( ndirco2_t *ctx, uint8_t select_mode );

/**
 * @brief Software Reset function
 *
 * @param ctx          Click object.
 * 
 * @description Function performs reset of device and after that puts device in power down mode when reset is done.
 */
void ndirco2_reset ( ndirco2_t *ctx );

/**
 * @brief CO2 Concentration Limit Check function
 *
 * @param ctx          Click object.
 * 
 * @return 0 - the CO2 concentration drops below ten times the value of Low Alarm Threshold register
 *         1 - the CO2 concentration goes above ten times the value of High Alarm Threshold register
 *
 * @description Function checks is CO2 concentration cross limit value, and when that happens then generates interrupt (ALARM pin).
 */
uint8_t ndirco2_check_alarm( ndirco2_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _NDIRCO2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

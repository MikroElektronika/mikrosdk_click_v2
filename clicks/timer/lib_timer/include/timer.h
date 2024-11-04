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
 * \brief This file contains API for Timer Click driver.
 *
 * \addtogroup timer Timer Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

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
#define TIMER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.evt = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.alm = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TIMER_RETVAL  uint8_t

#define TIMER_OK           0x00
#define TIMER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup  i2c_address I2c address
 * \{
 */
#define TIMER_I2C_ADDR                                 0x6B
/** \} */

/**
 * \defgroup registers  Registers
 * \{
 */
#define TIMER_REG_CONFIG                               0x00
#define TIMER_REG_ALARM                                0x01
#define TIMER_REG_ELAPSED                              0x05
#define TIMER_REG_EVT_CNTR                             0x09
#define TIMER_REG_EEPROM                               0x0B
#define TIMER_REG_RESET                                0x1D
#define TIMER_REG_WRITE_DISABLE                        0x1E
#define TIMER_REG_WRITE_MEM_DISABLE                    0x1F
/** \} */

/**
 * \defgroup bit Bit
 * \{
 */
#define TIMER_ECMSB_BIT                                0x01
#define TIMER_AP_BIT                                   0x02
#define TIMER_RE_BIT                                   0x04
#define TIMER_AOS_BIT                                  0x08
#define TIMER_WMDF_BIT                                 0x10
#define TIMER_WDF_BIT                                  0x20
#define TIMER_AF_BIT                                   0x40
/** \} */

/**
 * \defgroup eeprom_size Eeprom Size
 * \{
 */
#define TIMER_EEPROM_SIZE                               10
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
    // Output pins 

    digital_out_t evt;

    // Input pins 

    digital_in_t alm;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} timer_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t evt;
    pin_name_t alm;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} timer_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void timer_cfg_setup ( timer_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TIMER_RETVAL timer_init ( timer_t *ctx, timer_cfg_t *cfg );

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
void timer_generic_write ( timer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void timer_generic_read ( timer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardwere reset function
 *
 * @param ctx          Click object.
 *
 * @description Function hardwere reset device by set RST pin on Timer Click.
 */
void timer_hw_reset ( timer_t *ctx );

/**
 * @brief Read data from the EEPROM memory function
 *
 * @param ctx          Click object.
 * 
 * @description Function read all data from the EEPROM memory
 * of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_read_eeprom ( timer_t *ctx );

/**
 * @brief Write data from the EEPROM memory function
 *
 * @param ctx          Click object.
 * @param location     EEPROM location from 1 to 10
 * @param write_data   8-bit data to write
 *
 * @description Function write data to the target EEPROM memory location
 * of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_write_byte_eeprom ( timer_t *ctx, uint8_t location, uint8_t write_data );

/**
 * @brief Read the byte of data from the EEPROM memory function
 *
 * @param ctx          Click object. 
 * @param location   EEPROM location from 1 to 10
 * 
 * @return
 * 8-bit read data from desired EPPROM location
 *
 * @description Function read 8-bit data from the target EEPROM memory location
 * of DS1682 total elapsed time recorder on Timer Click.
 */
uint8_t timer_read_byte_eeprom ( timer_t *ctx, uint8_t location );

/**
 * @brief Get configuration data function
 *
 * @param ctx          Click object.  
 * @return
 * 8-bit read data
 *
 * @description Function read the 8-bit configuration data from the
 * target 8-bit configuration register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint8_t timer_get_configuration ( timer_t *ctx );

/**
 * @brief Get elapsed time counter (ETC) data function
 *
 * @param ctx          Click object.   
 * @return
 * 32-bit read data ( quarter seconds )
 *
 * @description Function read the 32-bit elapsed time counter (ETC) data from the
 * target 8-bit ETC register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint32_t timer_get_etc_data ( timer_t *ctx );

/**
 * @brief Set elapsed time counter (ETC) data function
 *
 * @param ctx          Click object.  
 * @param etc_value    32-bit read data ( quarter seconds )
 *
 * @description Function write the 32-bit elapsed time counter (ETC) data to the
 * target 8-bit ETC register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_etc_data ( timer_t *ctx, uint32_t etc_value );

/**
 * @brief Get elapsed time counter (ETC) seconds function
 *
 * @param ctx          Click object.   
 * @return
 * 32-bit read ETC seconds
 *
 * @description Function read the 32-bit elapsed time counter (ETC) seconds from the
 * target 8-bit ETC register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint32_t timer_get_etc_seconds ( timer_t *ctx );

/**
 * @brief Set elapsed time counter (ETC) time function
 *
 * @param ctx                        Click object.   
 * @param time_days                  pointer of time days
 * @param time_hours                 pointer of time hours [ 0 h : 23 h ]
 * @param time_minutes               pointer of time minutes [ 0 min : 59 min ]
 * @param time_seconds               pointer of time seconds [ 0 sec : 59 sec ]
 *
 * @description Function write the 32-bit elapsed time counter (ETC) time to the
 * target 8-bit ETC register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_get_time ( timer_t *ctx, uint16_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );

/**
 * @brief Set elapsed time counter (ETC) seconds function
 *
 * @param ctx          Click object.  
 * @param etc_seconds  32-bit read data ( quarter seconds )
 *
 * @description Function write the 32-bit elapsed time counter (ETC) seconds to the
 * target 8-bit ETC register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_etc_seconds ( timer_t *ctx, uint32_t etc_seconds );

/**
 * @brief Get event counter (EC) data function
 *
 * @param ctx          Click object. 
 * @return
 * 16-bit read data ( quarter seconds )
 *
 * @description Function read the 32-bit elapsed time counter (EC) data from the
 * target 8-bit EC register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint16_t timer_get_ec_data ( timer_t *ctx );

/**
 * @brief Set elapsed time counter (EC) data function
 *
 * @param ctx          Click object.
 * @param ec_value     16-bit read data ( quarter seconds )
 *
 * @description Function write the 16-bit elapsed time counter (EC) data to the
 * target 8-bit EC register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_ec_data ( timer_t *ctx, uint16_t ec_value );

/**
 * @brief Get elapsed time counter (EC) seconds function
 *
 * @param ctx          Click object.
 * @return
 * 16-bit read EC seconds
 *
 * @description Function read the 16-bit elapsed time counter (EC) seconds from the
 * target 8-bit EC register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint16_t timer_get_ec_seconds ( timer_t *ctx );

/**
 * @brief Set elapsed time counter (EC) seconds function
 *
 * @param ctx          Click object.
 * @param ec_seconds   16-bit read data ( quarter seconds )
 *
 * @description Function write the 16-bit elapsed time counter (EC) seconds to the
 * target 8-bit EC register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_ec_seconds ( timer_t *ctx, uint16_t ec_seconds );

/**
 * @brief Get alarm data function
 *
 * @param ctx          Click object.
 * @return
 * 32-bit read alarm data ( quarter seconds )
 *
 * @description Function read the 32-bit alarm data from the
 * target 8-bit ALARM register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint32_t timer_get_alarm_data ( timer_t *ctx );

/**
 * @brief Set alarm data function
 *
 * @param ctx          Click object.
 * @param a_data       32-bit read data ( quarter seconds )
 *
 * @description Function write the 32-bit alarm data to the
 * target 8-bit ALARM register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_alarm_data ( timer_t *ctx, uint32_t a_data );

/**
 * @brief Get alarm seconds function
 *
 * @param ctx          Click object.
 * @return
 * 32-bit read alarm seconds
 *
 * @description Function read the 32-bit alarm seconds from the
 * target 8-bit ALARM register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint32_t timer_get_alarm_seconds ( timer_t *ctx  );

/**
 * @brief Get alarm time
 *
 * @param ctx              Click object.
 * @param time_days        pointer of time days
 * @param time_hours       pointer of time hours [ 0 h : 23 h ]
 * @param time_minutes     pointer of time minutes [ 0 min : 59 min ]
 * @param time_seconds     pointer of time seconds [ 0 sec : 59 sec ]
 *
 * @description Function get 16-bit day and 8-bit alarm hours, minutes and seconds.
 */
void timer_get_alarm_time ( timer_t *ctx, uint16_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );

/**
 * @brief Set alarm seconds function
 *
 * @param ctx              Click object.
 * @param alarm_seconds    32-bit read data ( quarter seconds )
 *
 * @description Function write the 32-bit alarm seconds to the
 * target 8-bit ALARM register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_alarm_seconds ( timer_t *ctx, uint32_t alarm_seconds );

/**
 * @brief Check write disable ( write protection ) function
 *
 * @param ctx     Click object.
 * @return        write protection status
 * - 0 : OFF;
 * - 1 : ON;
 *
 * @description Function check write disable ( write protection ) by read from the
 * target 8-bit CONFIG register address of DS1682 total elapsed time recorder on Timer Click
 * and return status of bit 4.
 */
uint8_t timer_check_write_disable ( timer_t *ctx );

/**
 * @brief Disable write data ( write protection ) function
 *
 * @param ctx     Click object.
 *
 * @description Function disable write data ( write protection ) by write twice value of 0xAA to the
 * target 8-bit WRITE_DISABLE register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_disable_write ( timer_t *ctx );

/**
 * @brief Enable write data function
 *
 * @param ctx     Click object.
 *
 * @description Function enable write data by write twice value of 0xF0 to the
 * target 8-bit WRITE_DISABLE register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_enable_write ( timer_t *ctx );

/**
 * @brief Set alarm output select function
 *
 * @param ctx     Click object.
 *
 * @description Function set alarm output select by set bit 3 to the
 * target 8-bit CONFIG register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_alarm_output_select ( timer_t *ctx );

/**
 * @brief Set enable reset function
 *
 * @param ctx     Click object.
 *
 * @description Function set enable reset by set bit 2 to the
 * target 8-bit CONFIG register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_reset_enable ( timer_t *ctx );

/**
 * @brief Set alarm polarity function
 *
 * @param ctx     Click object.
 *
 * @description Function set alarm polarity by set bit 1 to the
 * target 8-bit CONFIG register address of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_set_alarm_polarity ( timer_t *ctx );

/**
 * @brief Get alarm flag function
 *
 * @param ctx     Click object.
 *
 * @return        alarm flag status
 *                - 0 :  no matches;
 *                - 1 :  when the ETC value matches the alarm value;
 *
 * @note
 * Once the this bit is set it cannot be clear.
 * 
 * @description Function get alarm flag by read and return status of bit 6 from the
 * target 8-bit CONFIG register address of DS1682 total elapsed time recorder on Timer Click.
 */
uint8_t timer_get_alarm_flag ( timer_t *ctx );

/**
 * @brief Soft reset function
 *
 * @param ctx     Click object.
 *
 * @description Function software reset by set bit 2 to the target 8-bit CONFIG register address
 * and write twice value of 0x55 to the target 8-bit RESET of DS1682 total elapsed time recorder on Timer Click.
 */
void timer_soft_reset ( timer_t *ctx );

/**
 * @brief Check interrupt function
 *
 * @param ctx     Click object.
 *
 * @returns       interrupt state ( state of ALM pin )
 *                0 : no active;
 *                1 : active;
 *
 * @description Function checks the interrupt state, state of ALM pin on Timer Click.
 */
uint8_t timer_check_interrupt ( timer_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _TIMER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

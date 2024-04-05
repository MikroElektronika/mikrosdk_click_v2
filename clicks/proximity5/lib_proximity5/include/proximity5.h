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
 * \brief This file contains API for Proximity 5 Click driver.
 *
 * \addtogroup proximity5 Proximity 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY5_H
#define PROXIMITY5_H

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
#define PROXIMITY5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY5_RETVAL  uint8_t

#define PROXIMITY5_OK           0x00
#define PROXIMITY5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg_als_cfg1 Register ALS_CONF1
 * \{
 */
#define ALS_SD_ON            0
#define ALS_SD_OFF           1
#define ALS_INTEN            1
#define ALS_INT_DIS          0
#define ALS_PERS_1           1
#define ALS_PERS_2           2
#define ALS_PERS_4           4
#define ALS_PERS_8           8
#define ALS_IT_50_ms         0
#define ALS_IT_100_ms        1
#define ALS_IT_200_ms        2
#define ALS_IT_400_ms        3
#define ALS_IT_800_ms        7
/** \} */

/**
 * \defgroup reg_als_cfg2 Register ALS_CONF2
 * \{
 */
#define ALS_WHITE_SD_ON      0
#define ALS_WHITE_SD_OFF     1
/** \} */

/**
 * \defgroup ps_conf1 PS_CONF1
 * \{
 */
#define PS_DUTY_1_40         0
#define PS_DUTY_1_80         1
#define PS_DUTY_1_160        2
#define PS_DUTY_1_320        3
#define PS_PERS_1            0
#define PS_PERS_2            1
#define PS_PERS_3            2
#define PS_PERS_4            3
#define PS_IT_1T             0
#define PS_IT_1T5            1
#define PS_IT_2T             2
#define PS_IT_2T5            3
#define PS_IT_3T             4
#define PS_IT_3T5            5
#define PS_IT_4T             6
#define PS_IT_8T             7
#define PS_SD_ON             0
#define PS_SD_OFF            1
/** \} */

/**
 * \defgroup ps_conf2 PS_CONF2
 * \{
 */
#define GEST_INT_EN          1
#define GEST_INT_DIS         0
#define GEST_MODE_EN         1
#define GEST_MODE_DIS        0
#define PS_GAIN_TWO_STEP     1
#define PS_GAIN_SINGLX8      2
#define PS_GAIN_SINGLX1      3
#define PS_HD_12BIT          0
#define PS_HD_16BIT          1
#define PS_NS_TWO_STEPX4     0
#define PS_NS_TWO_STEP       1
#define PS_INT_DIS           0
#define PS_INT_CLOS          1
#define PS_INT_AWAY          2
#define PS_INT_CLOS_AWAY     3
/** \} */

/**
 * \defgroup ps_conf3 PS_CONF3
 * \{
 */
#define LED_I_LOW_DIS        0
#define LED_I_LOW_EN         1
#define IRED_SEL_IRED1       0
#define IRED_SEL_IRED2       1
#define IRED_SEL_IRED3       2
#define PS_SMART_PERS_DIS    0
#define PS_SMART_PERS_EN     1
#define PS_AF_DIS            0
#define PS_AF_EN             1
#define PS_TRIG_DIS          0
#define PS_TRIG_EN           1
#define PS_MS_INT            0
#define PS_MS_LOG_OUT        1
#define PS_SC_EN_ON          1
#define PS_SC_EN_OFF         0
/** \} */

/**
 * \defgroup reg_ps_ms Register ps_ms
 * \{
 */
#define PS_SC_CUR_1X                0
#define PS_SC_CUR_2X                1
#define PS_SC_CUR_4X                2
#define PS_SC_CUR_8X                3
#define PS_SP_TYP                   0
#define PS_SP_TYPX1_5               1
#define PS_SPO_00h                  0
#define PS_SPO_FFh                  1
#define LED_I_50MA                  0
#define LED_I_75MA                  1
#define LED_I_100MA                 2
#define LED_I_120MA                 3
#define LED_I_140MA                 4
#define LED_I_160MA                 5
#define LED_I_180MA                 6
#define LED_I_200MA                 7
/** \} */

/**
 * \defgroup cmd Commands
 * \{
 */
#define CMD_ALS_CONF1                    0x00
#define CMD_ALS_CONF2                    0x00
#define CMD_ALS_CONF1_2                  0x00
#define CMD_ALS_THDH_L                   0x01
#define CMD_ALS_THDH_H                   0x01
#define CMD_ALS_THDH_L_M                 0x01
#define CMD_ALS_THDL_L                   0x02
#define CMD_ALS_THDL_H                   0x02
#define CMD_ALS_THDL_L_M                 0x02
#define CMD_PS_CONF1                     0x03
#define CMD_PS_CONF2                     0x03
#define CMD_PS_CONF1_2                   0x03
#define CMD_PS_CONF3                     0x04
#define CMD_PS_MS                        0x04
#define CMD_PS_CONF3_MS                  0x04
#define CMD_PS_CANC_L                    0x05
#define CMD_PS_CANC_M                    0x05
#define CMD_PS_CANC_L_M                  0x05
#define CMD_PS_THDH_L                    0x06
#define CMD_PS_THDH_M                    0x06
#define CMD_PS_THDH_L_M                  0x06
#define CMD_PS_THDL_L                    0x07
#define CMD_PS_THDL_M                    0x07
#define CMD_PS_THDL_L_M                  0x07
#define CMD_PS1_DATA_L                   0x08
#define CMD_PS1_DATA_M                   0x08
#define CMD_PS1_DATA_L_M                 0x08
#define CMD_PS2_DATA_L                   0x09
#define CMD_PS2_DATA_M                   0x09
#define CMD_PS2_DATA_L_M                 0x09
#define CMD_PS3_DATA_L                   0x0A
#define CMD_PS3_DATA_M                   0x0A
#define CMD_PS3_DATA_L_M                 0x0A
#define CMD_ALS_DATA_L                   0x0B
#define CMD_ALS_DATA_M                   0x0B
#define CMD_ALS_DATA_L_M                 0x0B
#define CMD_WHITE_DATA_L                 0x0C
#define CMD_WHITE_DATA_M                 0x0C
#define CMD_WHITE_DATA_L_M               0x0C
#define RESERVED                         0x0D
#define CMD_INT_FLAG                     0x0D
#define CMD_ID_L                         0x0E
#define CMD_ID_M                         0x0E
#define CMD_ID_L_M                       0x0E
/** \} */

/**
 * \defgroup slav_addr Slave Address
 * \{
 */
#define PROXIMITY5_ADDR                  0x60
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

} proximity5_t;

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

} proximity5_cfg_t;

/**
 * @brief Click calibration unions.
 */
typedef union 
{
    unsigned char ALL;
    struct
    {

      unsigned char ALS_SD      : 1;
      unsigned char ALS_INT_EN  : 1;
      unsigned char ALS_PERS    : 2;
      unsigned char RES         : 1;
      unsigned char ALS_IT      : 3;
    };

} als_conf1_t;

typedef union 
{
    unsigned char ALL;
    struct 
    {

      unsigned char WHITE_SD   : 1;
      unsigned char RES        : 7;
    };

} als_conf2_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t ALS_THDH_L        : 8;
      uint16_t ALS_THDH_M        : 8;
    };

} als_thdh_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t LS_THDL_L        : 8;
      uint16_t LS_THDL_M        : 8;
    };

} als_thdl_l_m_t;

typedef union
{
    uint16_t ALL;
    struct 
    {

      uint16_t ALS_DATA_L        : 8;
      uint16_t ALS_DATA_M        : 8;
    };

} als_data_l_m_t;

typedef union 
{
    uint8_t ALL;
    struct 
    {
      uint8_t PS_SD        : 1;
      uint8_t PS_IT        : 3;
      uint8_t PS_PERS      : 2;
      uint8_t PS_DUTY      : 2;
    };

} ps_conf1_t;

typedef union 
{
    uint8_t ALL;
    struct {

      uint8_t PS_INT_EN     : 2;
      uint8_t PS_NS         : 1;
      uint8_t PS_HD         : 1;
      uint8_t PS_GAIN       : 2;
      uint8_t GEST_MODE     : 1;
      uint8_t GEST_INTEN   : 1;
    };

} ps_conf2_t;

typedef union 
{
    uint8_t ALL;
    struct 
    {

      uint8_t PS_SC_EN       : 1;
      uint8_t PS_MS          : 1;
      uint8_t PS_TRIG        : 1;
      uint8_t PS_AF          : 1;
      uint8_t PS_SMART_PERS  : 1;
      uint8_t IRED_SEL       : 2;
      uint8_t LED_I_LOW      : 1;
    };

} ps_conf3_t;

typedef union 
{
    uint8_t ALL;
    struct 
    {

      uint8_t LED_I          : 3;
      uint8_t PS_SPO         : 1;
      uint8_t PS_SP          : 1;
      uint8_t PS_SC_CUR      : 2;
      uint8_t RES            : 1;

    };

} ps_ms_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t PS_CANC_L     : 8;
      uint16_t PS_CANC_M     : 8;
    };

} ps_canc_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t PS_THDL_L     : 8;
      uint16_t PS_THDL_M     : 8;
    };

} ps_thdl_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t PS_THDH_L        : 8;
      uint16_t PS_THDH_M        : 8;
    };

} ps_thdh_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t PS1_DATA_L        : 8;
      uint16_t PS1_DATA_M        : 8;
    };

} ps1_data_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct {

      uint16_t PS2_DATA_L        : 8;
      uint16_t PS2_DATA_M        : 8;
    };

} ps2_data_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t PS3_DATA_L        : 8;
      uint16_t PS3_DATA_M        : 8;
    };

} ps3_data_l_m_t;

typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t WHITE_DATA_L        : 8;
      uint16_t WHITE_DATA_M        : 8;
    };

} white_data_l_m_t;


typedef union 
{
    uint8_t ALL;
    struct 
    {

      uint8_t PS_IF_AWAY            : 1;
      uint8_t PS_IF_CLOSE           : 1;
      uint8_t RES1                  : 1;
      uint8_t RES0                  : 1;
      uint8_t ALS_IF_H              : 1;
      uint8_t ALS_IF_L              : 1;
      uint8_t PS_SPFLAG             : 1;
      uint8_t GEST_DATA_RDY_FLG     : 1;
    };

} int_flag_t;


typedef union 
{
    uint16_t ALL;
    struct 
    {

      uint16_t ID_L                : 8;
      uint16_t ID_M                : 8;

    };

} id_l_m_t;

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
void proximity5_cfg_setup ( proximity5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY5_RETVAL proximity5_init ( proximity5_t *ctx, proximity5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity5 click.
 */
void proximity5_default_cfg ( proximity5_t *ctx );

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
void proximity5_generic_write ( proximity5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void proximity5_generic_read ( proximity5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
  
/**
 * @brief 16bit read function.
 *
 * @param ctx          Click object.
 * @param addr         Register address.
 * 
 * @return 16bit value from the register.
 *
 * @description Generic function for reading both high and low register value 
 * and returns those combined values to a 16bit variable.
 */
uint16_t proximity5_read_reg ( proximity5_t *ctx, uint8_t addr );

/**
 * @brief 16bit read function.
 *
 * @param ctx          Click object.
 * @param addr         Register address.
 * 
 * @return 16bit value from the register.
 *
 * @description Read the ID from the ID register of the sensor.
 */
uint16_t proximity5_get_id ( proximity5_t *ctx );

/**
 * @brief Proximity value get function.
 *
 * @param ctx          Click object.
 * @param prox_val     Proximity data buffer.
 * 
 * @description Starts the conversion and waits for the interrupt to finish. 
 * After the interrupt finishes the proximity data from the proximity registers 
 * is returned to a 3 member uint16_t array.
 */
void proximity5_get_values ( proximity5_t *ctx, uint16_t *prox_val );


#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

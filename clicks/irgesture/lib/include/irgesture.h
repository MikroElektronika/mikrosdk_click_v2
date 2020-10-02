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
 * \brief This file contains API for IR Gesture Click driver.
 *
 * \addtogroup irgesture IR Gesture Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRGESTURE_H
#define IRGESTURE_H

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
#define IRGESTURE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRGESTURE_RETVAL  uint8_t

#define IRGESTURE_OK               0x00
#define IRGESTURE_INIT_ERROR       0xFF
/** \} */

/**
 * \defgroup apds_i2c_address APDS-9960 I2C address
 * \{
 */
#define  IRGESTURE_I2C_ADDR        0x39
/** \} */

/**
 * \defgroup apds_9960_address APDS-9960 register addresses
 * \{
 */
#define IRGESTURE_ENABLE           0x80
#define IRGESTURE_ATIME            0x81
#define IRGESTURE_WTIME            0x83
#define IRGESTURE_AILTL            0x84
#define IRGESTURE_AILTH            0x85
#define IRGESTURE_AIHTL            0x86
#define IRGESTURE_AIHTH            0x87
#define IRGESTURE_PILT             0x89
#define IRGESTURE_PIHT             0x8B
#define IRGESTURE_PERS             0x8C
#define IRGESTURE_CONFIG1          0x8D
#define IRGESTURE_PPULSE           0x8E
#define IRGESTURE_CONTROL          0x8F
#define IRGESTURE_CONFIG2          0x90
#define IRGESTURE_ID               0x92
#define IRGESTURE_STATUS           0x93
#define IRGESTURE_CDATAL           0x94
#define IRGESTURE_CDATAH           0x95
#define IRGESTURE_RDATAL           0x96
#define IRGESTURE_RDATAH           0x97
#define IRGESTURE_GDATAL           0x98
#define IRGESTURE_GDATAH           0x99
#define IRGESTURE_BDATAL           0x9A
#define IRGESTURE_BDATAH           0x9B
#define IRGESTURE_PDATA            0x9C
#define IRGESTURE_POFFSET_UR       0x9D
#define IRGESTURE_POFFSET_DL       0x9E
#define IRGESTURE_CONFIG3          0x9F
#define IRGESTURE_GPENTH           0xA0
#define IRGESTURE_GEXTH            0xA1
#define IRGESTURE_GCONF1           0xA2
#define IRGESTURE_GCONF2           0xA3
#define IRGESTURE_GOFFSET_U        0xA4
#define IRGESTURE_GOFFSET_D        0xA5
#define IRGESTURE_GOFFSET_L        0xA7
#define IRGESTURE_GOFFSET_R        0xA9
#define IRGESTURE_GPULSE           0xA6
#define IRGESTURE_GCONF3           0xAA
#define IRGESTURE_GCONF4           0xAB
#define IRGESTURE_GFLVL            0xAE
#define IRGESTURE_GSTATUS          0xAF
#define IRGESTURE_IFORCE           0xE4
#define IRGESTURE_PICLEAR          0xE5
#define IRGESTURE_CICLEAR          0xE6
#define IRGESTURE_AICLEAR          0xE7
#define IRGESTURE_GFIFO_U          0xFC
#define IRGESTURE_GFIFO_D          0xFD
#define IRGESTURE_GFIFO_L          0xFE
#define IRGESTURE_GFIFO_R          0xFF
/** \} */

/**
 * \defgroup defaul_values Default values
 * \{
 */
#define DEFAULT_ATIME              219     
#define DEFAULT_WTIME              246     
#define DEFAULT_PROX_PPULSE        0x87    
#define DEFAULT_GESTURE_PPULSE     0x89    
#define DEFAULT_POFFSET_UR         0       
#define DEFAULT_POFFSET_DL         0       
#define DEFAULT_CONFIG1            0x60    
#define DEFAULT_LDRIVE             0     
#define DEFAULT_PGAIN              2       
#define DEFAULT_AGAIN              1       
#define DEFAULT_PILT               0       
#define DEFAULT_PIHT               50      
#define DEFAULT_AILT               0xFFFF  
#define DEFAULT_AIHT               0
#define DEFAULT_PERS               0x11    
#define DEFAULT_CONFIG2            0x01   
#define DEFAULT_CONFIG3            0       
#define DEFAULT_GPENTH             40      
#define DEFAULT_GEXTH              30      
#define DEFAULT_GCONF1             0x40    
#define DEFAULT_GGAIN              2      
#define DEFAULT_GLDRIVE            0      
#define DEFAULT_GWTIME             1      
#define DEFAULT_GOFFSET            0       
#define DEFAULT_GPULSE             0xC9    
#define DEFAULT_GCONF3             0     
#define DEFAULT_GIEN               0      
/** \} */

/**
 * \defgroup bit_fields Bit fields
 * \{
 */
#define IRGESTURE_PON              0b00000001
#define IRGESTURE_AEN              0b00000010
#define IRGESTURE_PEN              0b00000100
#define IRGESTURE_WEN              0b00001000
#define IRGESTURE_AIEN             0b00010000
#define IRGESTURE_PIEN             0b00100000
#define IRGESTURE_GEN              0b01000000
#define IRGESTURE_GVALID           0b00000001
/** \} */

/**
 * \defgroup gesture_results Gesture results 
 * \{
 */
#define IRGESTURE_FAR              0x00
#define IRGESTURE_RIGHT            0x01
#define IRGESTURE_LEFT             0x02
#define IRGESTURE_UP               0x03
#define IRGESTURE_DOWN             0x04
#define IRGESTURE_NEAR             0x05
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

} irgesture_t;

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

} irgesture_cfg_t;

typedef enum
{
    NA_STATE,
    NEAR_STATE,
    FAR_STATE,
    ALL_STATE

} gesture_prox_t;

/**
 * @brief Direction definitions.
 */
typedef enum
{
    DIR_NONE,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
    DIR_NEAR,
    DIR_FAR,
    DIR_ALL

} gesture_dir_t;

/**
 * @brief Container for gesture data.
 */
typedef struct
{
    uint8_t u_data[ 32 ];
    uint8_t d_data[ 32 ];
    uint8_t l_data[ 32 ];
    uint8_t r_data[ 32 ];
    uint8_t index;
    uint8_t total_gestures;
    uint8_t in_threshold;
    uint8_t out_threshold;
    uint16_t ud_delta;
    uint16_t lr_delta;
    uint16_t ud_count;
    uint16_t lr_count;
    uint16_t near_count;
    uint16_t far_count;
    gesture_prox_t state;
    gesture_dir_t motion;

} gesture_data_t;

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
void irgesture_cfg_setup ( irgesture_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param irgesture Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRGESTURE_RETVAL irgesture_init ( irgesture_t *ctx, irgesture_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for IrGesture click.
 */
void irgesture_default_cfg ( irgesture_t *ctx );

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * @param write_data   Byte of data to be written.
 *
 * @description This function writes the 8-bit of data to the desired register.
 */
void irgesture_write_data ( irgesture_t *ctx, uint8_t reg_addr, uint8_t write_data );

/**
 * @brief Read function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * 
 * @returns 8-bit read data
 *
 * @description This function readsthe 8-bit of data from the
 * target 8-bit register address.
 */
uint8_t irgesture_read_data ( irgesture_t *ctx, uint8_t reg_addr );

/**
 * @brief Get state of interrupt pin function
 * 
 * @param ctx          Click object.
 *
 * @returns state of INT pin ( 0 - not active; 1 - active;)
 *
 * @description Function get state of interrupt ( INT ) pin.
 */
uint8_t irgesture_get_interrupt ( irgesture_t *ctx );

/**
 * @brief Processes a gesture event function
 * 
 * @param ctx          Click object.
 *
 * @returns gesture_dir_t
 * <pre>
 * - Number corresponding to gesture.
 * - or -1 on error.
 *</pre>

 * @description Function processes a gesture event and returns best guessed gesture
 * engine on the APDS-9960 IC on IR Gesture Click.
 */
gesture_dir_t irgesture_gesture_read_gesture ( irgesture_t *ctx );

/**
 * @brief Sets the gesture mode function
 * 
 * @param ctx          Click object.
 *
 * @description Function set the gesture mode engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_set_gesture_mode ( irgesture_t *ctx );

/**
 * @brief Enable power sensor function
 *
 * @param ctx          Click object.
 *
 * @description Function enable power sensor engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enable_power ( irgesture_t *ctx );

/**
 * @brief Disable power sensor function
 *
 * @param ctx          Click object.
 *
 * @description Function disable power sensor engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disable_power ( irgesture_t *ctx );

/**
 * @brief Set gain for ambient light function
 *
 * @param ctx          Click object.
 * @param gain_val     8-bit gain data
 *
 * @description Function set gain for ambient light on the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_set_ambient_light_gain ( irgesture_t *ctx, uint8_t gain_val );

/**
 * @brief Get gain for ambient light function
 *
 * @param ctx          Click object.
 * 
 * @returns 8-bit gain data
 *
 * @description Function get gain for ambient light from the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_get_ambient_light_gain ( irgesture_t *ctx );

/**
 * @brief Enable specific ambient light sensors function
 *
 * @param ctx          Click object.
 * 
 * @description Function enable specific ambient light sensors
 * and set default gain on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enable_light_sensor ( irgesture_t *ctx );

/**
 * @brief Disable specific ambient light sensors function
 *
 * @param ctx          Click object.
 * 
 * @description Function disable specific ambient light sensors on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disable_light_sensor ( irgesture_t *ctx );

/**
 * @brief Read ambient light data function
 *
 * @param ctx          Click object.
 * 
 * @returns 16-bit read ambient light data
 *
 * @description Function read ambient light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_read_ambient_light ( irgesture_t *ctx );

/**
 * @brief Read RED light data function
 *
 * @param ctx          Click object.
 * 
 * @returns 16-bit read RED light data
 *
 * @description Function read red light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_read_red_light ( irgesture_t *ctx );

/**
 * @brief Read GREEN light data function
 *
 * @param ctx          Click object.
 * 
 * @returns 16-bit read GREEN light data
 *
 * @description Function read green light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_read_green_light ( irgesture_t *ctx );

/**
 * @brief Read BLUE light data function
 *
 * @param ctx          Click object.
 * 
 * @return 16-bit read BLUE light data
 *
 * @description Function read blue light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_read_blue_light ( irgesture_t *ctx );

/**
 * @brief Sets the LED current boost value function
 *
 * @param ctx          Click object.
 * 
 * @param boost 
 * <pre>
 * Boost value (0-3)
 *  - 0 :       100%;
 *  - 1 :       150%;
 *  - 2 :       200%;
 *  - 3 :       300%;
 * </pre>

 * @description Function set the LED current boost value to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_set_led_boost ( irgesture_t *ctx, uint8_t boost );

/**
 * @brief Gets the LED current boost value function
 *
 * @param ctx          Click object. 
 * 
 * @returns boost value (0-3)
 * <pre>
 *  - 0 :       100%;
 *  - 1 :       150%;
 *  - 2 :       200%;
 *  - 3 :       300%;
 * </pre>
 * @description Function get the LED current boost value to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_get_led_boost ( irgesture_t *ctx );

/**
 * @brief Determines if there is a gesture available function
 *
 * @param ctx          Click object.
 * 
 * @returns  1 if TRUE;  0 if FALSE;
 *
 * @description Function determines if there is a gesture available 
 * for reading from target 8-bit register address of
 * APDS-9960 IC sensor on IR Gesture Click.
 */
uint8_t irgesture_available ( irgesture_t *ctx );

/**
 * @brief Set gain for gesture function
 *
 * @param ctx          Click object.
 * @param gain_val     8-bit gain data
 *
 * @description Function set gain for gesture on the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_set_gesture_gain ( irgesture_t *ctx, uint8_t gain_val );

/**
 * @brief Get gain for gesture function
 * 
 * @param ctx          Click object.
 *
 * @returns 8-bit gain data
 *
 * @description Function get gain for gesture from the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_get_gesture_gain ( irgesture_t *ctx );

/**
 * @brief Starts the gesture recognition engine function
 * 
 * @param ctx          Click object.
 *
 * @description Function starts the gesture recognition engine on the 
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enable_gesture_sensor ( irgesture_t *ctx );

/**
 * @brief Disable the gesture recognition engine function
 *
 * @param ctx          Click object.
 *
 * @description Function disable the gesture recognition engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disable_gesture_sensor ( irgesture_t *ctx );

/**
 * @brief Function decode a gesture event function
 *
 * @param ctx          Click object.
 * 
 * @returns 8-bit position of decode gesture
 *
 * @description Function processes a gesture event and returns best guessed position
 * engine on the APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_detect_gesture ( irgesture_t *ctx );

/**
 * @brief Set gain for proximity function
 *
 * @param ctx          Click object.
 * @param gain_val                8-bit gain proximity data
 *
 * @description Function set gain for proximity on the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_set_proximity_gain ( irgesture_t *ctx, uint8_t gain_val );

/**
 * @brief Get gain for proximity function
 *
 * @param ctx          Click object.
 * 
 * @returns 8-bit gain proximity data
 *
 * @description Function get gain for proximity from the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_get_proximity_gain ( irgesture_t *ctx );

/**
 * @brief Enable specific proximity sensors function
 *
 * @param ctx          Click object.
 * 
 * @description Function enable specific proximity sensors
 * and set default gain on the APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enable_proximity_sensor ( irgesture_t *ctx );

/**
 * @brief Disable specific proximity sensors function
 *
 * @param ctx          Click object.
 * 
 * @description Function disable specific proximity sensors
 * and set default gain on the APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disable_proximity_sensor ( irgesture_t *ctx );

/**
 * @brief Get the current mask for enabled/disabled proximity photodiodes function
 *
 * @param ctx          Click object.
 * 
 * @returns 8-bit photo mask data
 * <pre>
 *  - 1     : disabled;
 *  - 0     : enabled;
 *  - Bit 3 : UP;
 *  - Bit 2 : DOWN;
 *  - Bit 1 : LEFT;
 *  - Bit 0 : RIGHT;
 * </pre>
 * 
 * @description Function get the current mask for enabled/disabled proximity photodiodes 
 * to the target register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_get_proxy_photo_mask ( irgesture_t *ctx );

/**
 * @brief Get the current mask for enabled/disabled proximity photodiodes function
 *
 * @param ctx          Click object.
 * @param mask
 * <pre>
 *  - 1     : disabled;
 *  - 0     : enabled;
 *  - Bit 3 : UP;
 *  - Bit 2 : DOWN;
 *  - Bit 1 : LEFT;
 *  - Bit 0 : RIGHT;
 *</pre>
 * 
 * @description Function get the current mask for enabled/disabled
 * proximity photodiodes to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_set_proxy_photo_mask ( irgesture_t *ctx, uint8_t mask );

/**
 * @brief Read proximity data function
 *
 * @param ctx          Click object.
 * @returns 8-bit read proximity data
 *
 * @description Function read proximity data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_read_proximity_data ( irgesture_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _IRGESTURE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

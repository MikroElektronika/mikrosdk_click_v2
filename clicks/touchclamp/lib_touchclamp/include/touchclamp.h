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
 * \brief This file contains API for TouchClamp Click driver.
 *
 * \addtogroup touchclamp TouchClamp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TOUCHCLAMP_H
#define TOUCHCLAMP_H

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
#define TOUCHCLAMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TOUCHCLAMP_RETVAL  uint8_t

#define TOUCHCLAMP_OK           0x00
#define TOUCHCLAMP_INIT_ERROR   0xFF
/** \} */

#define TOUCHCLAMP_I2C_ADDRESS      0x5A

/**
 * \defgroup reg_deff MPR121 Register Defines
 * \{
 */
/**
 * \defgroup touch_data Touch and OOR statuses
 * \{
 */
#define TOUCHCLAMP_REG_TS1              0x00
#define TOUCHCLAMP_REG_TS2              0x01
#define TOUCHCLAMP_REG_OORS1            0x02
#define TOUCHCLAMP_REG_OORS2            0x03
/** \} */
/**
 * \defgroup filtered_data Ffiltered data
 * \{
 */
#define TOUCHCLAMP_REG_E0FDL            0x04
#define TOUCHCLAMP_REG_E0FDH            0x05
#define TOUCHCLAMP_REG_E1FDL            0x06
#define TOUCHCLAMP_REG_E1FDH            0x07
#define TOUCHCLAMP_REG_E2FDL            0x08
#define TOUCHCLAMP_REG_E2FDH            0x09
#define TOUCHCLAMP_REG_E3FDL            0x0A
#define TOUCHCLAMP_REG_E3FDH            0x0B
#define TOUCHCLAMP_REG_E4FDL            0x0C
#define TOUCHCLAMP_REG_E4FDH            0x0D
#define TOUCHCLAMP_REG_E5FDL            0x0E
#define TOUCHCLAMP_REG_E5FDH            0x0F
#define TOUCHCLAMP_REG_E6FDL            0x10
#define TOUCHCLAMP_REG_E6FDH            0x11
#define TOUCHCLAMP_REG_E7FDL            0x12
#define TOUCHCLAMP_REG_E7FDH            0x13
#define TOUCHCLAMP_REG_E8FDL            0x14
#define TOUCHCLAMP_REG_E8FDH            0x15
#define TOUCHCLAMP_REG_E9FDL            0x16
#define TOUCHCLAMP_REG_E9FDH            0x17
#define TOUCHCLAMP_REG_E10FDL           0x18
#define TOUCHCLAMP_REG_E10FDH           0x19
#define TOUCHCLAMP_REG_E11FDL           0x1A
#define TOUCHCLAMP_REG_E11FDH           0x1B
#define TOUCHCLAMP_REG_E12FDL           0x1C
#define TOUCHCLAMP_REG_E12FDH           0x1D
/** \} */
/**
 * \defgroup baseline_val Baseline values
 * \{
 */
#define TOUCHCLAMP_REG_E0BV             0x1E
#define TOUCHCLAMP_REG_E1BV             0x1F
#define TOUCHCLAMP_REG_E2BV             0x20
#define TOUCHCLAMP_REG_E3BV             0x21
#define TOUCHCLAMP_REG_E4BV             0x22
#define TOUCHCLAMP_REG_E5BV             0x23
#define TOUCHCLAMP_REG_E6BV             0x24
#define TOUCHCLAMP_REG_E7BV             0x25
#define TOUCHCLAMP_REG_E8BV             0x26
#define TOUCHCLAMP_REG_E9BV             0x27
#define TOUCHCLAMP_REG_E10BV            0x28
#define TOUCHCLAMP_REG_E11BV            0x29
#define TOUCHCLAMP_REG_E12BV            0x2A
/** \} */
/** \} */  // MPR121 Register Defines 
/**
 * \defgroup tsb_ft General electrode touch sense baseline filters
 * \{
 */
/**
 * \defgroup rising_filter Rising filter
 * \{
 */
#define TOUCHCLAMP_REG_MHDR             0x2B
#define TOUCHCLAMP_REG_NHDR             0x2C
#define TOUCHCLAMP_REG_NCLR             0x2D
#define TOUCHCLAMP_REG_FDLR             0x2E
/** \} */
/**
 * \defgroup falling_filter Falling filter
 * \{
 */
#define TOUCHCLAMP_REG_MHDF             0x2F
#define TOUCHCLAMP_REG_NHDF             0x30
#define TOUCHCLAMP_REG_NCLF             0x31
#define TOUCHCLAMP_REG_FDLF             0x32
#define TOUCHCLAMP_REG_NHDT             0x33 
#define TOUCHCLAMP_REG_NCLT             0x34 
#define TOUCHCLAMP_REG_FDLT             0x35
/** \} */
/** \} */  // General electrode touch sense baseline filters

/**
 * \defgroup prox_tsb_fil Proximity electrode touch sense baseline filters
 * \{
 */
/**
 * \defgroup rising_filter Rising filter
 * \{
 */
#define TOUCHCLAMP_REG_MHDPROXR         0x36
#define TOUCHCLAMP_REG_NHDPROXR         0x37
#define TOUCHCLAMP_REG_NCLPROXR         0x38
#define TOUCHCLAMP_REG_FDLPROXR         0x39
/** \} */                   
/**
 * \defgroup falling_filter Falling filter
 * \{
 */
#define TOUCHCLAMP_REG_MHDPROXF         0x3A
#define TOUCHCLAMP_REG_NHDPROXF         0x3B
#define TOUCHCLAMP_REG_NCLPROXF         0x3C
#define TOUCHCLAMP_REG_FDLPROXF         0x3D
/** \} */
/**
 * \defgroup touched_filter Touched filter
 * \{
 */
#define TOUCHCLAMP_REG_NHDPROXT         0x3E
#define TOUCHCLAMP_REG_NCLPROXT         0x3F
#define TOUCHCLAMP_REG_FDLPROXT         0x40
/** \} */
/**
 * \defgroup el_touch_release Electrode touch and release thresholds
 * \{
 */
#define TOUCHCLAMP_REG_E0TTH            0x41
#define TOUCHCLAMP_REG_E0RTH            0x42
#define TOUCHCLAMP_REG_E1TTH            0x43
#define TOUCHCLAMP_REG_E1RTH            0x44
#define TOUCHCLAMP_REG_E2TTH            0x45
#define TOUCHCLAMP_REG_E2RTH            0x46
#define TOUCHCLAMP_REG_E3TTH            0x47
#define TOUCHCLAMP_REG_E3RTH            0x48
#define TOUCHCLAMP_REG_E4TTH            0x49
#define TOUCHCLAMP_REG_E4RTH            0x4A
#define TOUCHCLAMP_REG_E5TTH            0x4B
#define TOUCHCLAMP_REG_E5RTH            0x4C
#define TOUCHCLAMP_REG_E6TTH            0x4D
#define TOUCHCLAMP_REG_E6RTH            0x4E
#define TOUCHCLAMP_REG_E7TTH            0x4F
#define TOUCHCLAMP_REG_E7RTH            0x50
#define TOUCHCLAMP_REG_E8TTH            0x51
#define TOUCHCLAMP_REG_E8RTH            0x52
#define TOUCHCLAMP_REG_E9TTH            0x53
#define TOUCHCLAMP_REG_E9RTH            0x54
#define TOUCHCLAMP_REG_E10TTH           0x55
#define TOUCHCLAMP_REG_E10RTH           0x56
#define TOUCHCLAMP_REG_E11TTH           0x57
#define TOUCHCLAMP_REG_E11RTH           0x58
#define TOUCHCLAMP_REG_E12TTH           0x59
#define TOUCHCLAMP_REG_E12RTH           0x5A
/** \} */ 
/**
 * \defgroup debounce_settings Debounce settings
 * \{
 */
#define TOUCHCLAMP_REG_DTR              0x5B
/** \} */ 
/**
 * \defgroup config_reg Configuration registers
 * \{
 */
#define TOUCHCLAMP_REG_AFE1             0x5C
#define TOUCHCLAMP_REG_AFE2             0x5D
#define TOUCHCLAMP_REG_ECR              0x5E
/** \} */
/**
 * \defgroup electrode_currents Electrode currents
 * \{
 */
#define TOUCHCLAMP_REG_CDC0             0x5F
#define TOUCHCLAMP_REG_CDC1             0x60
#define TOUCHCLAMP_REG_CDC2             0x61
#define TOUCHCLAMP_REG_CDC3             0x62
#define TOUCHCLAMP_REG_CDC4             0x63
#define TOUCHCLAMP_REG_CDC5             0x64
#define TOUCHCLAMP_REG_CDC6             0x65
#define TOUCHCLAMP_REG_CDC7             0x66
#define TOUCHCLAMP_REG_CDC8             0x67
#define TOUCHCLAMP_REG_CDC9             0x68
#define TOUCHCLAMP_REG_CDC10            0x69
#define TOUCHCLAMP_REG_CDC11            0x6A
#define TOUCHCLAMP_REG_CDC12            0x6B
/** \} */
/**
 * \defgroup elec_ch_times Electrode charge times
 * \{
 */
#define TOUCHCLAMP_REG_CDT01            0x6C
#define TOUCHCLAMP_REG_CDT23            0x6D
#define TOUCHCLAMP_REG_CDT45            0x6E
#define TOUCHCLAMP_REG_CDT67            0x6F
#define TOUCHCLAMP_REG_CDT89            0x70
#define TOUCHCLAMP_REG_CDT1011          0x71
#define TOUCHCLAMP_REG_CDT11            0x72
/** \} */
/**
 * \defgroup gpio GPIO
 * \{
 */
#define TOUCHCLAMP_REG_CTL0             0x73
#define TOUCHCLAMP_REG_CTL1             0x74
#define TOUCHCLAMP_REG_DAT              0x75
#define TOUCHCLAMP_REG_DIR              0x76
#define TOUCHCLAMP_REG_EN               0x77
#define TOUCHCLAMP_REG_SET              0x78
#define TOUCHCLAMP_REG_CLR              0x79
#define TOUCHCLAMP_REG_TOG              0x7A
/** \} */ 
/**
 * \defgroup auto_config Auto-config
 * \{
 */
#define TOUCHCLAMP_REG_ACCR0            0x7B
#define TOUCHCLAMP_REG_ACCR1            0x7C
#define TOUCHCLAMP_REG_USL              0x7D
#define TOUCHCLAMP_REG_LSL              0x7E
#define TOUCHCLAMP_REG_TL               0x7F
/** \} */
/**
 * \defgroup soft_reset Soft reset
 * \{
 */
#define TOUCHCLAMP_REG_SRST             0x80
/** \} */
/** \} */  // Proximity electrode touch sense baseline filters

/**
 * \defgroup def_config_val Default configuration value
 * \{
 */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_ECR
 * \{
 */
#define TOUCHCLAMP_ECR_INIT_VAL         0x00
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_MHDR
 * \{
 */
#define TOUCHCLAMP_MHDR_MAX_VAL         0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NHDR
 * \{
 */
#define TOUCHCLAMP_NHDR_MIN_VAL         0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NCLR
 * \{
 */
#define TOUCHCLAMP_NCLR_DEF_VAL         0x10
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_FDLR
 * \{
 */
#define TOUCHCLAMP_FDLR_DEF_VAL         0x20
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_MHDF
 * \{
 */
#define TOUCHCLAMP_MHDF_DEF_VAL         0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NHDF
 * \{
 */
#define TOUCHCLAMP_NHDF_DEF_VAL         0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NCLF
 * \{
 */
#define TOUCHCLAMP_NCLF_DEF_VAL         0x10
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_FDLF
 * \{
 */
#define TOUCHCLAMP_FDLF_DEF_VAL         0x20
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NHDT
 * \{
 */
#define TOUCHCLAMP_NHDT_DEF_VAL         0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NCLT
 * \{
 */
#define TOUCHCLAMP_NCLT_DEF_VAL         0x10
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_FDLT
 * \{
 */
#define TOUCHCLAMP_FDLT_DEF_VAL         0xFF
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_MHDPROXR
 * \{
 */
#define TOUCHCLAMP_MHDPROXR_DEF_VAL     0x0F
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NHDPROXR
 * \{
 */
#define TOUCHCLAMP_NHDPROXR_DEF_VAL     0x0F
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NCLPROXR
 * \{
 */
#define TOUCHCLAMP_NCLPROXR_DEF_VAL     0x00
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_FDLPROXR
 * \{
 */
#define TOUCHCLAMP_FDLPROXR_DEF_VAL     0x00
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_MHDPROXF
 * \{
 */
#define TOUCHCLAMP_MHDPROXF_DEF_VAL     0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NHDPROXF
 * \{
 */
#define TOUCHCLAMP_NHDPROXF_DEF_VAL     0x01
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NCLPROXF
 * \{
 */
#define TOUCHCLAMP_NCLPROXF_DEF_VAL     0xFF
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_NHDPROXT
 * \{
 */
#define TOUCHCLAMP_NHDPROXT_DEF_VAL     0x00
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_DTR
 * \{
 */
#define TOUCHCLAMP_DTR_DEF_VAL          0x11
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_AFE1
 * \{
 */
#define TOUCHCLAMP_AFE1_DEF_VAL         0xFF
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_AFE2
 * \{
 */
#define TOUCHCLAMP_AFE2_DEF_VAL         0x30
/** \} */
/**
 * \defgroup def_config_val TOUCHCLAMP_REG_ECR
 * \{
 */
#define TOUCHCLAMP_ECR_DEF_VAL          0x88
/** \} */
/** \} */  // Default configuration value

/**
 * \defgroup bit_mask Bit mask
 * \{
 */
#define TOUCHCLAMP_BIT_MASK_SCRATCH    0xF8
#define TOUCHCLAMP_BIT_MASK_SAMP_PER   0x07
#define TOUCHCLAMP_BIT_MASK_STOP_BIT   0xC0
#define TOUCHCLAMP_BIT_MASK_SW_RESET   0x63
/** \} */

/**
 * \defgroup touch_data Touch clamp data position value
 * \{
 */
#define TOUCHCLAMP_TOUCH_POSITION_A    0x80
#define TOUCHCLAMP_TOUCH_POSITION_B    0x40
#define TOUCHCLAMP_TOUCH_POSITION_C    0x20
#define TOUCHCLAMP_TOUCH_POSITION_D    0x08
#define TOUCHCLAMP_TOUCH_POSITION_E    0x04
#define TOUCHCLAMP_TOUCH_POSITION_F    0x02
#define TOUCHCLAMP_TOUCH_POSITION_G    0x01
#define TOUCHCLAMP_TOUCH_POSITION_H    0x10
#define TOUCHCLAMP_NO_TOUCH            0x00
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

} touchclamp_t;

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

} touchclamp_cfg_t;

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
void touchclamp_cfg_setup ( touchclamp_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TOUCHCLAMP_RETVAL touchclamp_init ( touchclamp_t *ctx, touchclamp_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TouchClamp click.
 * @note
 *    Click default configuration:
 * -------------------------------------------------
 * 
 * <pre>
 *    TOUCHCLAMP_REG_ECR
 * -------------------------------------------------
 *    TOUCHCLAMP_ECR_INIT_VAL
 * </pre>
 * 
 * <pre>
 *    TOUCHCLAMP_REG_MHDR
 * -------------------------------------------------
 *    TOUCHCLAMP_MHDR_MAX_VAL
 * </pre>
 *  
 * <pre>
 *    TOUCHCLAMP_REG_NHDR
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDR_MIN_VAL
 * </pre>
 *   
 * <pre>
 *    TOUCHCLAMP_REG_NCLR
 * -------------------------------------------------
 *    TOUCHCLAMP_NCLR_DEF_VAL
 * </pre>
 *   
 * <pre>
 *    TOUCHCLAMP_REG_FDLR
 * -------------------------------------------------
 *    TOUCHCLAMP_FDLR_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_MHDF
 * -------------------------------------------------
 *    TOUCHCLAMP_MHDF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NHDF
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NCLF
 * -------------------------------------------------
 *    TOUCHCLAMP_NCLF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_FDLF
 * -------------------------------------------------
 *    TOUCHCLAMP_FDLF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NHDT
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDT_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NCLT
 * -------------------------------------------------
 *    TOUCHCLAMP_NCLT_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_FDLT
 * -------------------------------------------------
 *    TOUCHCLAMP_FDLT_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_MHDPROXR
 * -------------------------------------------------
 *    TOUCHCLAMP_MHDPROXR_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NHDPROXR
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDPROXR_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NCLPROXR
 * -------------------------------------------------
 *    TOUCHCLAMP_NCLPROXR_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_FDLPROXR
 * -------------------------------------------------
 *    TOUCHCLAMP_FDLPROXR_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_MHDPROXF
 * -------------------------------------------------
 *    TOUCHCLAMP_MHDPROXF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NHDPROXF
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDPROXF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NCLPROXF
 * -------------------------------------------------
 *    TOUCHCLAMP_NCLPROXF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_FDLPROXF
 * -------------------------------------------------
 *    TOUCHCLAMP_NCLPROXF_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NHDPROXT
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDPROXT_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_NCLPROXT
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDPROXT_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_FDLPROXT
 * -------------------------------------------------
 *    TOUCHCLAMP_NHDPROXT_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_DTR
 * -------------------------------------------------
 *    TOUCHCLAMP_DTR_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_AFE1
 * -------------------------------------------------
 *    TOUCHCLAMP_AFE1_DEF_VAL
 * </pre>
 * <pre>
 *    TOUCHCLAMP_REG_AFE2
 * -------------------------------------------------
 *    TOUCHCLAMP_AFE2_DEF_VAL
 * </pre>
 * <pre>
 *    Set touch threshold
 * -------------------------------------------------
 *    0x28 ( 40 )
 * </pre>
 * <pre>
 *    Set release threshold
 * -------------------------------------------------
 *    0x14 ( 20 )
 * </pre>
 * <pre>
 *    LDC1101_REG_CFG_ADDITIONAL_DEVICE
 * -------------------------------------------------
 *    TOUCHCLAMP_ECR_DEF_VAL
 * </pre>
 */
void touchclamp_default_cfg ( touchclamp_t *ctx );

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
void touchclamp_generic_write ( touchclamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void touchclamp_generic_read ( touchclamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Soft reset function.
 * 
 * @param ctx          Click object.
 *
 * @description This function performs a software reset.
 */
void touchclamp_soft_reset ( touchclamp_t *ctx );

/**
 * @brief Setting touch threshold for a specified electrode function.
 * 
 * @param ctx          Click object.
 * @param th_data      Touch threshold value.
 *
 * @description This function set touch threshold value
 * for a specified electrode of MPR121 chip.
 */
void touchclamp_set_touch_threshold ( touchclamp_t *ctx, uint8_t th_data );

/**
 * @brief Get the current touch threshold for a specified electrode function.
 * 
 * @param ctx          Click object.
 * @param electrode    Touch threshold electrode position value.
 * 
 * @return             8-bit touch threshold data.
 *
 * @description This function get the current touch threshold 
 * for a specified electrode of MPR121 chip.
 */
uint8_t touchclamp_get_touch_threshold ( touchclamp_t *ctx, uint8_t electrode );

/**
 * @brief Setting release threshold for a specified electrode function.
 * 
 * @param ctx          Click object.
 * @param th_data      Release threshold value.
 *
 * @description This function set release threshold value
 * for a specified electrode of MPR121 chip.
 */
void touchclamp_set_release_threshold ( touchclamp_t *ctx, uint8_t rth_data );

/**
 * @brief Get the current release threshold for a specified electrode function.
 * 
 * @param ctx          Click object.
 * @param electrode    Release threshold electrode position value.
 * 
 * @return             8-bit release threshold data.
 *
 * @description This function current release threshold
 * for a specified electrode of MPR121 chip.
 */
uint8_t touchclamp_get_release_threshold ( touchclamp_t *ctx, uint8_t electrode );

/**
 * @brief Get touch data function.
 * 
 * @param ctx          Click object.
 * @return             16-bit touch data.
 *
 * @description This function 16-bit touch data 
 * from the two register address of MPR121 chip.
 */
uint16_t touchclamp_get_touch_data ( touchclamp_t *ctx );
 
/**
 * @brief Sets the sample period function.
 * 
 * @param ctx          Click object.
 * @param sample_per   8-bit sample period value.
 *
 * @description This function set the sample period of the MPR121, 
 * the time between capacitive readings. 
 * Higher values consume less power, but are less responsive.
 */
void touchclamp_set_sample_period ( touchclamp_t *ctx, uint8_t sample_per );

/**
 * @brief Toggles electrode set as GPIO output function.
 * 
 * @param ctx          Click object.
 * @param electrode    Digital toggle electrode position value.
 *
 * @description This function set the sample period of the MPR121, 
 * the time between capacitive readings. 
 * Higher values consume less power, but are less responsive.
 */
void touchclamp_digital_toggle ( touchclamp_t *ctx, uint8_t electrode );

/**
 * @brief Stop touch clamp function.
 * 
 * @param ctx          Click object.
 *
 * @description The stop function switch the MPR121 chip to stop mode
 * which reduces power consumption to 3uA.
 */
void touchclamp_stop ( touchclamp_t *ctx );

/**
 * @brief Get state of interrupt pin function.
 *
 * @param ctx          Click object.
 *
 * @return
 * Interrupt state:
 * <pre>
 *    0 : Not active.
 * </pre>
 * <pre>
 *    1 : Active.
 * </pre>
 * 
 * @description This function gets states of the 
 * interrupt ( INT ) pin of the MPR121 chip.
 */
uint8_t touchclamp_get_interrupt ( touchclamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TOUCHCLAMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

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
 * \brief This file contains API for Accel 13 Click driver.
 *
 * \addtogroup accel13 Accel 13 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL13_H
#define ACCEL13_H

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

#define ACCEL13_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL13_MASTER_I2C 0
#define ACCEL13_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL13_RETVAL  uint8_t

#define ACCEL13_OK           0x00
#define ACCEL13_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Slave address
 * \{
 */
#define ACCEL13_DEVICE_SLAVE_ADDR_GND       0x18
#define ACCEL13_DEVICE_SLAVE_ADDR_VCC       0x19

/**
 * \defgroup register_map Register Map
 * \{
 */
#define ACCEL13_REG_TEMPERATURE_DATA_LSB    0x0D
#define ACCEL13_REG_TEMPERATURE_DATA_MSB    0x0E
#define ACCEL13_REG_WHO_AM_I                0x0F
#define ACCEL13_REG_CTRL_1                  0x20
#define ACCEL13_REG_CTRL_2                  0x21
#define ACCEL13_REG_CTRL_3                  0x22
#define ACCEL13_REG_CTRL_4_INT1             0x23
#define ACCEL13_REG_CTRL_5_INT2             0x24
#define ACCEL13_REG_CTRL_6                  0x25
#define ACCEL13_REG_TEMPERATURE_OUTPUT      0x26
#define ACCEL13_REG_STATUS                  0x27
#define ACCEL13_REG_AXIS_X_LSB              0x28
#define ACCEL13_REG_AXIS_X_MSB              0x29
#define ACCEL13_REG_AXIS_Y_LSB              0x2A
#define ACCEL13_REG_AXIS_Y_MSB              0x2B
#define ACCEL13_REG_AXIS_Z_LSB              0x2C
#define ACCEL13_REG_AXIS_Z_MSB              0x2D
#define ACCEL13_REG_FIFO_CTRL               0x2E
#define ACCEL13_REG_FIFO_SAMPLES            0x2F
#define ACCEL13_REG_TAP_AXIS_X              0x30
#define ACCEL13_REG_TAP_AXIS_Y              0x31
#define ACCEL13_REG_TAP_AXIS_Z              0x32
#define ACCEL13_REG_INT_DURATION            0x33
#define ACCEL13_REG_WAKE_UP_THRESHOLD       0x34
#define ACCEL13_REG_WAKE_UP_DURATION        0x35
#define ACCEL13_REG_FREE_FALL_CONFIG        0x36
#define ACCEL13_REG_STATUS_DUP              0x37
#define ACCEL13_REG_WAKE_UP_SOURCE          0x38
#define ACCEL13_REG_TAP_SOURCE              0x39
#define ACCEL13_REG_6D_SOURCE               0x3A
#define ACCEL13_REG_ALL_INT_SOURCE          0x3B
#define ACCEL13_REG_X_OFFSET_USER           0x3C
#define ACCEL13_REG_Y_OFFSET_USER           0x3D
#define ACCEL13_REG_Z_OFFSET_USER           0x3E
#define ACCEL13_REG_CTRL_7                  0x3F
/** \} */

/**
 * \defgroup defualt_value Default Value
 * \{
 */
#define ACCEL13_DEF_WHO_AM_I    0x44
/** \} */

/**
 * \defgroup ctrl_1 Control 1
 * \{
 */
#define ACCEL13_CTRL1_ODR_POWER_DOWN                      0x00
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_12p5_1p6Hz       0x10
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_12p5Hz           0x20
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_25Hz             0x30
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_50Hz             0x40
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_100Hz            0x50
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_200Hz            0x60
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_400_200Hz        0x70
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_800_200Hz        0x80
#define ACCEL13_CTRL1_ODR_LOW_POWER_MODE_1600_200Hz       0x90
#define ACCEL13_CTRL1_MODE_LOW_POWER_MODE_12_14bit        0x00
#define ACCEL13_CTRL1_MODE_HIGH_PERFORMANCE_MODE_14bit    0x04
#define ACCEL13_CTRL1_SINGLE_DATA_CONVERSION_12_14bit     0x08
#define ACCEL13_CTRL1_LP_MODE_1                           0x00
#define ACCEL13_CTRL1_LP_MODE_2                           0x01
#define ACCEL13_CTRL1_LP_MODE_3                           0x02
#define ACCEL13_CTRL1_LP_MODE_4                           0x03
/** \} */

/**
 * \defgroup ctrl_2 Control 2
 * \{
 */
#define ACCEL13_CTRL2_BOOT_DISABLE             0x00
#define ACCEL13_CTRL2_BOOT_ENABLE              0x80
#define ACCEL13_CTRL2_SOFT_RESET_DISABLE       0x00
#define ACCEL13_CTRL2_SOFT_RESET_ENABLE        0x20
#define ACCEL13_CTRL2_PULLUP_CS_PIN_ENABLE     0x00
#define ACCEL13_CTRL2_PULLUP_CS_PIN_DISABLE    0x10
#define ACCEL13_CTRL2_BDU_CONTINUOUS_UPDATE    0x00
#define ACCEL13_CTRL2_BDU_UPDATE_REGISTER      0x08
#define ACCEL13_CTRL2_IF_ADD_INC_ENABLED       0x04
#define ACCEL13_CTRL2_IF_ADD_INC_DISABLED      0x00
#define ACCEL13_CTRL2_I2C_AND_SPI_ENABLE       0x00
#define ACCEL13_CTRL2_I2C_DISABLE              0x02
#define ACCEL13_CTRL2_SPI_4_WIRE               0x00
#define ACCEL13_CTRL2_SPI_3_WIRE               0x01
/** \} */

/**
 * \defgroup ctrl_3 Control 3
 * \{
 */
#define ACCEL13_CTRL3_SELF_TEST_DISABLE        0x00
#define ACCEL13_CTRL3_SELF_TEST_POS_SIGN       0x40
#define ACCEL13_CTRL3_SELF_TEST_NEG_SIGN       0x80
#define ACCEL13_CTRL3_PUSH_PULL_INT_PAD        0x00
#define ACCEL13_CTRL3_OPEN_DRAIN_INT_PAD       0x20
#define ACCEL13_CTRL3_LATCHED_INT_ENABLE       0x20
#define ACCEL13_CTRL3_LATCHED_INT_DISABLE      0x10
#define ACCEL13_CTRL3_INT_ACTIVE_HIGH          0x00
#define ACCEL13_CTRL3_INT_ACTIVE_LOW           0x08
#define ACCEL13_CTRL3_SLP_MODE_SEL_EN_INT2     0x00
#define ACCEL13_CTRL3_SLP_MODE_SEL_EN_MODE1    0x02
/** \} */

/**
 * \defgroup ctrl_4_int1_pad_ctrl Control 4 Int1 Pad Control
 * \{
 */
#define ACCEL13_CTRL4_INT1_6D_DISABLED            0x00
#define ACCEL13_CTRL4_INT1_6D_ENABLED             0x80
#define ACCEL13_CTRL4_INT1_SINGLE_TAP_DISABLED    0x00
#define ACCEL13_CTRL4_INT1_SINGLE_TAP_ENABLED     0x40
#define ACCEL13_CTRL4_INT1_WAKEUP_DISABLED        0x00
#define ACCEL13_CTRL4_INT1_WAKEUP_ENABLED         0x20
#define ACCEL13_CTRL4_INT1_FREE_FALL_DISABLED     0x00
#define ACCEL13_CTRL4_INT1_FREE_FALL_ENABLED      0x10
#define ACCEL13_CTRL4_INT1_TAP_DISABLED           0x00
#define ACCEL13_CTRL4_INT1_TAP_ENABLED            0x08
#define ACCEL13_CTRL4_INT1_DIFF5_DISABLED         0x00
#define ACCEL13_CTRL4_INT1_DIFF5_ENABLED          0x04
#define ACCEL13_CTRL4_INT1_FTH_DISABLED           0x00
#define ACCEL13_CTRL4_INT1_FTH_ENABLED            0x02
#define ACCEL13_CTRL4_INT1_DRDY_DISABLED          0x00
#define ACCEL13_CTRL4_INT1_DRDY_ENABLED           0x01
/** \} */

/**
 * \defgroup ctrl_5_int2_pad_ctrl Control 5 Int2 Pad Control
 * \{
 */
#define ACCEL13_CTRL5_INT2_SLEEP_STATE_DISABLED    0x00
#define ACCEL13_CTRL5_INT2_SLEEP_STATE_ENABLED     0x80
#define ACCEL13_CTRL5_INT2_SLEEP_CHG_DISABLED      0x00
#define ACCEL13_CTRL5_INT2_SLEEP_CHG_ENABLED       0x40
#define ACCEL13_CTRL5_INT2_BOOT_DISABLED           0x00
#define ACCEL13_CTRL5_INT2_BOOT_ENABLED            0x20
#define ACCEL13_CTRL5_INT2_T_DRDY_DISABLED         0x00
#define ACCEL13_CTRL5_INT2_T_DRDY_ENABLED          0x10
#define ACCEL13_CTRL5_INT2_OVR_DISABLED            0x00
#define ACCEL13_CTRL5_INT2_OVR_ENABLED             0x08
#define ACCEL13_CTRL4_INT2_DIFF5_DISABLED          0x00
#define ACCEL13_CTRL4_INT2_DIFF5_ENABLED           0x04
#define ACCEL13_CTRL4_INT2_FTH_DISABLED            0x00
#define ACCEL13_CTRL4_INT2_FTH_ENABLED             0x02
#define ACCEL13_CTRL4_INT2_DRDY_DISABLED           0x00
#define ACCEL13_CTRL4_INT2_DRDY_ENABLED            0x01
/** \} */

/**
 * \defgroup ctrl_6 Control 6
 * \{
 */
#define ACCEL13_CTRL6_BW_FILT_ODR_2        0x00
#define ACCEL13_CTRL6_BW_FILT_ODR_4        0x40
#define ACCEL13_CTRL6_BW_FILT_ODR_10       0x80
#define ACCEL13_CTRL6_BW_FILT_ODR_20       0xC0
#define ACCEL13_CTRL6_FULL_SCALE_2g        0x00
#define ACCEL13_CTRL6_FULL_SCALE_4g        0x10
#define ACCEL13_CTRL6_FULL_SCALE_8g        0x20
#define ACCEL13_CTRL6_FULL_SCALE_16g       0x30
#define ACCEL13_CTRL6_FDS_LOW_PASS         0x00
#define ACCEL13_CTRL6_FDS_HIGH_PASS        0x08
#define ACCEL13_CTRL6_LOW_NOISE_DISABLE    0x00
#define ACCEL13_CTRL6_LOW_NOISE_ENABLE     0x04
/** \} */

/**
 * \defgroup fifo_ctrl Fifo Control
 * \{
 */
#define ACCEL13_FCTRL_BYPASS_MODE             0x00
#define ACCEL13_FCTRL_FIFO_MODE               0x20
#define ACCEL13_FCTRL_CONTINUOUS_TO_FIFO      0x60
#define ACCEL13_FCTRL_BYPASS_TO_CONTINUOUS    0x80
#define ACCEL13_FCTRL_CONTINUOUS_MODE         0xC0
/** \} */

/**
 * \defgroup tap_ths_x Tap THS X
 * \{
 */
#define ACCEL3_TAPTHX_4DEN_NO_POSITION_DETECTED    0x00
#define ACCEL3_TAPTHX_4DEN_POSITION_DETECTED       0x80
#define ACCEL3_TAPTHX_6DTHS_80_DEGREES             0x00
#define ACCEL3_TAPTHX_6DTHS_70_DEGREES             0x20
#define ACCEL3_TAPTHX_6DTHS_60_DEGREES             0x40
#define ACCEL3_TAPTHX_6DTHS_50_DEGREES             0x60
/** \} */

/**
 * \defgroup tap_ths_y Tap THS Y
 * \{
 */
#define ACCEL3_TAPTHY_PERIOD_X_Y_Z    0x00
#define ACCEL3_TAPTHY_PERIOD_Y_X_Z    0x20
#define ACCEL3_TAPTHY_PERIOD_X_Z_Y    0x40
#define ACCEL3_TAPTHY_PERIOD_Z_Y_X    0x60
/** \} */

/**
 * \defgroup tap_ths_z Tap THS Z
 * \{
 */
#define ACCEL13_TAPTHZ_TAP_X_DISABLE    0x00
#define ACCEL13_TAPTHZ_TAP_Y_DISABLE    0x00
#define ACCEL13_TAPTHZ_TAP_Z_DISABLE    0x00
#define ACCEL13_TAPTHZ_TAP_X_ENABLE     0x80
#define ACCEL13_TAPTHZ_TAP_Y_ENABLE     0x40
#define ACCEL13_TAPTHZ_TAP_Z_ENABLE     0x20
/** \} */

/**
 * \defgroup wake_up_ths Wake Up THS
 * \{
 */
#define ACCEL13_WUT_TAP_SINGLE_EN               0x00
#define ACCEL13_WUT_TAP_SINGLE_AND_DOUBLE_EN    0x80
#define ACCEL13_WUT_SLEEP_DISABLE               0x00
#define ACCEL13_WUT_SLEEP_ENABLE                0x40
/** \} */

/**
 * \defgroup free_fall Free Fall
 * \{
 */
#define ACCEL13_FFTHS_DECODING_LSB_5     0x00
#define ACCEL13_FFTHS_DECODING_LSB_7     0x01
#define ACCEL13_FFTHS_DECODING_LSB_8     0x02
#define ACCEL13_FFTHS_DECODING_LSB_10    0x03
#define ACCEL13_FFTHS_DECODING_LSB_11    0x04
#define ACCEL13_FFTHS_DECODING_LSB_13    0x05
#define ACCEL13_FFTHS_DECODING_LSB_15    0x06
#define ACCEL13_FFTHS_DECODING_LSB_16    0x07
/** \} */

/**
 * \defgroup status_dur Status Dur
 * \{
 */
#define ACCEL13_SDUR_OVR_FIFO_NOT_COMPLETELY        0x00
#define ACCEL13_SDUR_OVR_FIFO_COMPLETELY            0x80
#define ACCEL13_SDUR_T_DRDY_NO_DATA                 0x00
#define ACCEL13_SDUR_T_DRDY_DATA_IS_AVAILABLE       0x40
#define ACCEL13_SDUR_SLEEP_EVENT_NO_DETECT          0x00
#define ACCEL13_SDUR_SLEEP_EVENT_DETECT             0x20
#define ACCEL13_SDUR_DOUBLE_TAP_EVENT_NO_DETECT     0x00
#define ACCEL13_SDUR_DOUBLE_TAP_EVENT_DETECT        0x10
#define ACCEL13_SDUR_SINGLE_TAP_EVENT_NO_DETECT     0x00
#define ACCEL13_SDUR_SINGLE_TAP_EVENT_DETECT        0x08
#define ACCEL13_SDUR_6D_IA_EVENT_NO_DETECT          0x00
#define ACCEL13_SDUR_6D_IA_EVENT_DETECT             0x04
#define ACCEL13_SDUR_FF_IA_EVENT_NO_DETECT          0x00
#define ACCEL13_SDUR_FF_IA_EVENT_DETECT             0x02
#define ACCEL13_SDUR_DRDY_NO_READY                  0x00
#define ACCEL13_SDUR_DRDY_XYZ_NEW_DATA_AVAILABLE    0x01
/** \} */

/**
 * \defgroup wake_up_src Wake_Up_SRC
 * \{
 */
#define ACCEL13_WUSRC_FF_IA_EVENT_NO_DETECT       0x00
#define ACCEL13_WUSRC_FF_IA_EVENT_DETECT          0x20
#define ACCEL13_WUSRC_SLEEP_EVENT_NO_DETECT       0x00
#define ACCEL13_WUSRC_SLEEP_EVENT_DETECT          0x10
#define ACCEL13_WUSRC_WAKEUP_EVENT_NO_DETECT      0x00
#define ACCEL13_WUSRC_WAKEUP_EVENT_DETECT         0x08
#define ACCEL13_WUSRC_WAKEUP_X_EVENT_NO_DETECT    0x00
#define ACCEL13_WUSRC_WAKEUP_X_EVENT_DETECT       0x04
#define ACCEL13_WUSRC_WAKEUP_Y_EVENT_NO_DETECT    0x00
#define ACCEL13_WUSRC_WAKEUP_Y_EVENT_DETECT       0x02
#define ACCEL13_WUSRC_WAKEUP_Z_EVENT_NO_DETECT    0x00
#define ACCEL13_WUSRC_WAKEUP_Z_EVENT_DETECT       0x01
/** \} */

/**
 * \defgroup tap_src Tap_SRC
 * \{
 */
#define ACCEL13_TAPSRC_TAP_IA_EVENT_NO_DETECT        0x00
#define ACCEL13_TAPSRC_TAP_EVENT_DETECT              0x40
#define ACCEL13_TAPSRC_SINGLE_TAP_EVENT_NO_DETECT    0x00
#define ACCEL13_TAPSRC_SINGLE_TAP_EVENT_DETECT       0x20
#define ACCEL13_TAPSRC_DOUBLE_TAP_EVENT_NO_DETECT    0x00
#define ACCEL13_TAPSRC_DOUBLE_TAP_EVENT_DETECT       0x10
#define ACCEL13_TAPSRC_TAP_SIGN_EVENT_NO_DETECT      0x00
#define ACCEL13_TAPSRC_TAP_SIGN_EVENT_DETECT         0x08
#define ACCEL13_TAPSRC_X_TAP_EVENT_NO_DETECT         0x00
#define ACCEL13_TAPSRC_X_TAP_EVENT_DETECT            0x04
#define ACCEL13_TAPSRC_Y_TAP_EVENT_NO_DETECT         0x00
#define ACCEL13_TAPSRC_Y_TAP_EVENT_DETECT            0x02
#define ACCEL13_TAPSRC_Z_TAP_EVENT_NO_DETECT         0x00
#define ACCEL13_TAPSRC_Z_TAP_EVENT_DETECT            0x01
/** \} */

/**
 * \defgroup 6d_src 6D_SRC
 * \{
 */
#define ACCEL13_SIXDSRC_6D_IA_EVENT_NO_DETECT    0x00
/** \} */

/**
 * \defgroup interrupt Interrupt
 * \{
 */
#define ACCEL13_INT_PIN_INTERRUPT_1    0x00
#define ACCEL13_PWM_PIN_INTERRUPT_2    0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  accel13_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel13_master_io_t )( struct accel13_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel13_s
{
    // Output pins 
   digital_out_t cs;

    // Input pins 

    digital_in_t int2;
    digital_in_t int1;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    accel13_master_io_t  write_f;
    accel13_master_io_t  read_f;
    accel13_select_t master_sel;

} accel13_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    
    // Additional gpio pins 

    pin_name_t int2;
    pin_name_t int1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    uint32_t spi_speed;
    uint8_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    accel13_select_t sel;

} accel13_cfg_t;

/**
 * @brief Accel axis data structure.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel13_axis_t;

/**
 * @brief Structure for collecting status data,
 * read from the STATUS registers
 */
typedef struct
{
    uint8_t fifo_threshold;
    uint8_t wakeup_event;
    uint8_t sleep_event;
    uint8_t double_tap_event;
    uint8_t single_tap_event;
    uint8_t event_6d;
    uint8_t free_fall_event;
    uint8_t drdy_event;

}  accel13_status_t;

/**
 * @brief Structure for collecting status data,
 * read from the WAKE-UP SRC register
 */
typedef struct
{
   uint8_t free_fall_event;
   uint8_t sleep_event;
   uint8_t wakeup_event;
   uint8_t wakeup_x;
   uint8_t wakeup_y;
   uint8_t wakeup_z;

} accel13_wake_up_t;

/**
 * @brief Structure for collecting status data,
 * read from the TAP SRC register
 */
typedef struct
{
   uint8_t tap;
   uint8_t single_tap;
   uint8_t double_tap;
   uint8_t sign_tap;
   uint8_t tap_x;
   uint8_t tap_y;
   uint8_t tap_z;

} accel13_tap_t;

/**
 * @brief Structure for collecting status data,
   read from the 6D SRC register
 */
typedef struct
{
   uint8_t event_6d;
   uint8_t z_high;
   uint8_t z_low;
   uint8_t y_high;
   uint8_t y_low;
   uint8_t x_high;
   uint8_t x_low;

} accel13_6d_t;

/**
 * @brief Structure for collecting data,
   read from the USER OFFSET registers
 */
typedef struct
{
    int8_t x;
    int8_t y;
    int8_t z;

} accel13_user_offset_t;

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
void accel13_cfg_setup ( accel13_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param accel13 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL13_RETVAL accel13_init ( accel13_t *ctx, accel13_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Accel 13 click.
 *
 * @note:
 *    This functions contains some basic initial setups that we have set for start-up wake-up and configuration of the chip
 *    All settings can be changed by You as well by writing your new setup and settings.
 *
 *    List of registers and their set values:
 *    
 *    <pre>
 *    #  ACCEL13_REG_CTRL_1  
 *       ACCEL13_CTRL1_ODR_LOW_POWER_MODE_400_200Hz,
 *       ACCEL13_CTRL1_MODE_HIGH_PERFORMANCE_MODE_14bit,
 *       ACCEL13_CTRL1_LP_MODE_1.
 *
 *    # ACCEL13_REG_CTRL_2
 *      ACCEL13_CTRL2_BOOT_ENABLE,
 *      ACCEL13_CTRL2_SOFT_RESET_DISABLE,
 *      ACCEL13_CTRL2_PULLUP_CS_PIN_ENABLE,
 *      ACCEL13_CTRL2_BDU_CONTINUOUS_UPDATE,
 *      ACCEL13_CTRL2_IF_ADD_INC_ENABLED,
 *      ACCEL13_CTRL2_I2C_AND_SPI_ENABLE,
 *      ACCEL13_CTRL2_SPI_4_WIRE.
 *
 *     # ACCEL13_REG_CTRL_3
 *       ACCEL13_CTRL3_SELF_TEST_DISABLE,
 *       ACCEL13_CTRL3_OPEN_DRAIN_INT_PAD,
 *       ACCEL13_CTRL3_LATCHED_INT_DISABLE,
 *       ACCEL13_CTRL3_INT_ACTIVE_HIGH,
 *       ACCEL13_CTRL3_SLP_MODE_SEL_EN_INT2.
 *
 *     # ACCEL13_REG_CTRL_4_INT1
 *       ACCEL13_CTRL4_INT1_6D_DISABLED,
 *       ACCEL13_CTRL4_INT1_SINGLE_TAP_DISABLED,
 *       ACCEL13_CTRL4_INT1_WAKEUP_DISABLED,
 *       ACCEL13_CTRL4_INT1_FREE_FALL_DISABLED,
 *       ACCEL13_CTRL4_INT1_TAP_ENABLED,
 *       ACCEL13_CTRL4_INT1_DIFF5_DISABLED,
 *       ACCEL13_CTRL4_INT1_FTH_DISABLED,
 *       ACCEL13_CTRL4_INT1_DRDY_DISABLED.
 *
 *
 *     # ACCEL13_REG_CTRL_5_INT2
 *       ACCEL13_CTRL5_INT2_SLEEP_STATE_DISABLED
 *       ACCEL13_CTRL5_INT2_SLEEP_CHG_DISABLED,
 *       ACCEL13_CTRL5_INT2_BOOT_DISABLED,
 *       ACCEL13_CTRL5_INT2_T_DRDY_DISABLED,
 *       ACCEL13_CTRL5_INT2_OVR_DISABLED,
 *       ACCEL13_CTRL4_INT2_DIFF5_DISABLED,
 *       ACCEL13_CTRL4_INT2_DRDY_ENABLED.
 *
 *      # ACCEL13_REG_WAKE_UP_DURATION -  0x00
 *      # ACCEL13_REG_FREE_FALL_CONFIG -  0x33
 *      # ACCEL13_REG_CTRL_7 -  0x20
 *      # ACCEL13_REG_TAP_AXIS_X - 0x09
 *      # ACCEL13_REG_TAP_AXIS_Y - 0xE9
 *      # ACCEL13_REG_TAP_AXIS_Z - 0xE9
 *      # ACCEL13_REG_INT_DURATION - 0x06
 *      # ACCEL13_REG_X_OFFSET_USER - 0x00
 *      # ACCEL13_REG_Y_OFFSET_USER - 0x00
 *      # ACCEL13_REG_Z_OFFSET_USER - 0x40
 *    </pre> 
 */
void accel13_default_cfg ( accel13_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx            Click object.
 * @param reg            Register address.
 * @param data_buf       Input data buf
 * @param len            Number of the bytes to be written
 *
 * @description This function writes data to the desired register.
 */
void accel13_generic_write_bytes ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Single byte write function.
 *
 * @param ctx            Click object.
 * @param reg            Register address.
 * @param data_in        Input data
 *
 * @description This function writes 1 byte to the desired register.
 */
void accel13_generic_write_single_byte ( accel13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Generic 8bit read function.
 *
 * @param ctx            Click object.
 * @param reg            Register address.
 * @param data_buf       Output data buf
 * @param len            Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void accel13_generic_read_bytes ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief 16bit read function.
 *
 * @param ctx            Click object.
 * @param reg            Register address.
 * 
 * @retval read 16bit value.
 *
 * @description This function returns single 16bit value read from the desired registers.
 */
int16_t accel13_generic_read_word ( accel13_t *ctx, uint8_t reg );

/**
 * @brief Temperature functions
 *
 * @param ctx            Click object.
 *
 * @retval Temperature data in C.
 */
float accel13_get_temperature ( accel13_t *ctx );

/**
 * @brief Read function for Accel axis data
 *
 * @param ctx            Click object.
 * @param axis           An object that contains X , Y and Z axis data.
 * 
 * @description This function reads the axis data and stores it in the axis object.
 */
void accel13_get_axis_data ( accel13_t *ctx, accel13_axis_t *axis );

/**
 * @brief Read functions for Status data
 *
 * @param ctx            Click object.
 * @param status         An object that contains status data.
 *
 * @description This function reads the status data and stores it in the status object.
 */
void accel13_get_status ( accel13_t *ctx, accel13_status_t *status);

/**
 * @brief Read function for Wake-up status data
 *
 * @param ctx            Click object.
 * @param wu_status      An object that contains wake-up status data.
 *
 * @description This function reads the wake-up status data and stores it in the wu_status object.
 */
void accel13_get_wake_up_status ( accel13_t *ctx, accel13_wake_up_t *wu_status);

/**
 * @brief Read function for Tap status data
 *
 * @param ctx            Click object.
 * @param tap_status     An object that contains wake-up status data.
 *
 * @description This function reads the tap status data and stores it in the tap_status object.
 */
void accel13_get_tap_status ( accel13_t *ctx, accel13_tap_t *tap_status );

/**
 * @brief Read function for 6D status data
 *
 * @param ctx            Click object.
 * @param sixd_status    An object that contains 6D status data.
 *
 * @description This function reads the 6D status data and stores it in the sixd_status object.
 */
void accel13_get_6d_status ( accel13_t *ctx, accel13_6d_t *sixd_status );

/**
 * @brief Read function for User offset data
 *
 * @param ctx            Click object.
 * @param axis           An object that contains user offset data.
 *
 * @description This function reads the 6D status data and stores it in the axis object.
 */
void accel13_get_user_offset ( accel13_t *ctx, accel13_user_offset_t *axis );

/**
 * @brief Set function for User offset data
 *
 * @param ctx            Click object.
 * @param axis           An object that contains user offset data.
 *
 * @description This function sets the User offset data from the axis object.
 */
void accel13_set_user_offset ( accel13_t *ctx, accel13_user_offset_t *axis );

/**
 * @brief Interrupt functions
 *
 * @param ctx            Click object.
 * @param intNum         Interrupt pin.
 *
 * @return Interrupt state on the this select pin
 *
 * @description This function returns value of interupt state from the selected pin
 */
uint8_t accel13_get_interrupt ( accel13_t *ctx, uint8_t int_num );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL13_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

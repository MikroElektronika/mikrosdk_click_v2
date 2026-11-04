/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file silentstep5.h
 * @brief This file contains API for Silent Step 5 Click Driver.
 */

#ifndef SILENTSTEP5_H
#define SILENTSTEP5_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "spi_specifics.h"

/*!
 * @addtogroup silentstep5 Silent Step 5 Click Driver
 * @brief API for configuring and manipulating Silent Step 5 Click driver.
 * @{
 */

/**
 * @defgroup silentstep5_reg Silent Step 5 Registers List
 * @brief List of registers of Silent Step 5 Click driver.
 */

/**
 * @addtogroup silentstep5_reg
 * @{
 */

/**
 * @brief Silent Step 5 register map.
 * @details Specified register map of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_REG_GCONF                           0x00
#define SILENTSTEP5_REG_GSTAT                           0x01
#define SILENTSTEP5_REG_DO_CONF                         0x02
#define SILENTSTEP5_REG_DO_SCOPE_CONF                   0x03
#define SILENTSTEP5_REG_IOIN                            0x04
#define SILENTSTEP5_REG_X_COMPARE                       0x05
#define SILENTSTEP5_REG_X_COMPARE_REPEAT                0x06
#define SILENTSTEP5_REG_DRV_CONF                        0x0A
#define SILENTSTEP5_REG_PLL                             0x0B
#define SILENTSTEP5_REG_IHOLD_IRUN                      0x10
#define SILENTSTEP5_REG_TPOWERDOWN                      0x11
#define SILENTSTEP5_REG_TSTEP                           0x12
#define SILENTSTEP5_REG_TPWMTHRS                        0x13
#define SILENTSTEP5_REG_TCOOLTHRS                       0x14
#define SILENTSTEP5_REG_THIGH                           0x15
#define SILENTSTEP5_REG_TSGP_LOW_VEL_THRS               0x16
#define SILENTSTEP5_REG_T_RCOIL_MEAS                    0x17
#define SILENTSTEP5_REG_TUDCSTEP                        0x18
#define SILENTSTEP5_REG_UDC_CONF                        0x19
#define SILENTSTEP5_REG_STEPS_LOST                      0x1A
#define SILENTSTEP5_REG_RAMPMODE                        0x20
#define SILENTSTEP5_REG_XACTUAL                         0x21
#define SILENTSTEP5_REG_VACTUAL                         0x22
#define SILENTSTEP5_REG_VSTART                          0x23
#define SILENTSTEP5_REG_A1                              0x24
#define SILENTSTEP5_REG_V1                              0x25
#define SILENTSTEP5_REG_AMAX                            0x26
#define SILENTSTEP5_REG_VMAX                            0x27
#define SILENTSTEP5_REG_DMAX                            0x28
#define SILENTSTEP5_REG_TVMAX                           0x29
#define SILENTSTEP5_REG_D1                              0x2A
#define SILENTSTEP5_REG_VSTOP                           0x2B
#define SILENTSTEP5_REG_TZEROWAIT                       0x2C
#define SILENTSTEP5_REG_XTARGET                         0x2D
#define SILENTSTEP5_REG_V2                              0x2E
#define SILENTSTEP5_REG_A2                              0x2F
#define SILENTSTEP5_REG_D2                              0x30
#define SILENTSTEP5_REG_AACTUAL                         0x31
#define SILENTSTEP5_REG_SW_MODE                         0x34
#define SILENTSTEP5_REG_RAMP_STAT                       0x35
#define SILENTSTEP5_REG_XLATCH                          0x36
#define SILENTSTEP5_REG_ENCMODE                         0x38
#define SILENTSTEP5_REG_X_ENC                           0x39
#define SILENTSTEP5_REG_ENC_CONST                       0x3A
#define SILENTSTEP5_REG_ENC_STATUS                      0x3B
#define SILENTSTEP5_REG_ENC_LATCH                       0x3C
#define SILENTSTEP5_REG_ENC_DEVIATION                   0x3D
#define SILENTSTEP5_REG_VIRTUAL_STOP_L                  0x3E
#define SILENTSTEP5_REG_VIRTUAL_STOP_R                  0x3F
#define SILENTSTEP5_REG_CURRENT_PI                      0x40
#define SILENTSTEP5_REG_ANGLE_PI                        0x41
#define SILENTSTEP5_REG_CUR_ANGLE_LIMIT                 0x42
#define SILENTSTEP5_REG_ANGLE_LOWER_LIMIT               0x43
#define SILENTSTEP5_REG_CUR_ANGLE_MEAS                  0x44
#define SILENTSTEP5_REG_PI_RESULTS                      0x45
#define SILENTSTEP5_REG_COIL_INDUCT                     0x46
#define SILENTSTEP5_REG_R_COIL                          0x47
#define SILENTSTEP5_REG_R_COIL_USER                     0x48
#define SILENTSTEP5_REG_SGP_CONF                        0x49
#define SILENTSTEP5_REG_SGP_IND_2_3                     0x4A
#define SILENTSTEP5_REG_SGP_IND_0_1                     0x4B
#define SILENTSTEP5_REG_INDUCTANCE_VOLTAGE              0x4C
#define SILENTSTEP5_REG_SGP_BEMF                        0x4D
#define SILENTSTEP5_REG_COOLSTEPPLUS_CONF               0x4E
#define SILENTSTEP5_REG_COOLSTEPPLUS_PI                 0x4F
#define SILENTSTEP5_REG_COOLSTEPPLUS_PI_DOWN            0x50
#define SILENTSTEP5_REG_COOLSTEPPLUS_RESERVE_CONF       0x51
#define SILENTSTEP5_REG_COOLSTEPPLUS_LOAD_RESERVE       0x52
#define SILENTSTEP5_REG_TSTEP_VELOCITY                  0x53
#define SILENTSTEP5_REG_ADC_VSUPPLY_TEMP                0x58
#define SILENTSTEP5_REG_ADC_I                           0x59
#define SILENTSTEP5_REG_OTW_OV_VTH                      0x5A
#define SILENTSTEP5_REG_MSLUT_0                         0x60
#define SILENTSTEP5_REG_MSLUT_1                         0x61
#define SILENTSTEP5_REG_MSLUT_2                         0x62
#define SILENTSTEP5_REG_MSLUT_3                         0x63
#define SILENTSTEP5_REG_MSLUT_4                         0x64
#define SILENTSTEP5_REG_MSLUT_5                         0x65
#define SILENTSTEP5_REG_MSLUT_6                         0x66
#define SILENTSTEP5_REG_MSLUT_7                         0x67
#define SILENTSTEP5_REG_MSLUTSEL                        0x68
#define SILENTSTEP5_REG_MSLUTSTART                      0x69
#define SILENTSTEP5_REG_MSCNT                           0x6A
#define SILENTSTEP5_REG_MSCURACT                        0x6B
#define SILENTSTEP5_REG_CHOPCONF                        0x6C
#define SILENTSTEP5_REG_COOLCONF                        0x6D
#define SILENTSTEP5_REG_DRV_STATUS                      0x6F
#define SILENTSTEP5_REG_PWMCONF                         0x70

/**
 * @brief Silent Step 5 PCA9538A registers.
 * @details Specified PCA9538A registers of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_EXP_REG_INPUT                       0x00
#define SILENTSTEP5_EXP_REG_OUTPUT                      0x01
#define SILENTSTEP5_EXP_REG_POLARITY                    0x02
#define SILENTSTEP5_EXP_REG_CONFIG                      0x03

/*! @} */ // silentstep5_reg

/**
 * @defgroup silentstep5_set Silent Step 5 Registers Settings
 * @brief Settings for registers of Silent Step 5 Click driver.
 */

/**
 * @addtogroup silentstep5_set
 * @{
 */

/**
 * @brief Silent Step 5 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_EXP_PIN_SLEEP                       0x02
#define SILENTSTEP5_EXP_PIN_DIAG0                       0x08
#define SILENTSTEP5_EXP_PIN_DIAG1                       0x10
#define SILENTSTEP5_EXP_PIN_DRV_EN                      0x80

/**
 * @brief Silent Step 5 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_EXP_DEFAULT_CONFIG                  0x7D

/**
 * @brief Silent Step 5 direction setting.
 * @details Specified setting for direction of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_DIR_CW                              0
#define SILENTSTEP5_DIR_CCW                             1

/**
 * @brief Silent Step 5 pin logic state setting.
 * @details Specified setting for pin logic state of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_PIN_STATE_LOW                       0
#define SILENTSTEP5_PIN_STATE_HIGH                      1

/**
 * @brief Silent Step 5 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define SILENTSTEP5_SPEED_VERY_SLOW                     0
#define SILENTSTEP5_SPEED_SLOW                          1
#define SILENTSTEP5_SPEED_MEDIUM                        2
#define SILENTSTEP5_SPEED_FAST                          3
#define SILENTSTEP5_SPEED_VERY_FAST                     4

/**
 * @brief Silent Step 5 GCONF register setting.
 * @details Specified setting for GCONF register of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_GCONF_FAST_STANDSTILL_DIS           0x00000000ul
#define SILENTSTEP5_GCONF_FAST_STANDSTILL_EN            0x00000001ul
#define SILENTSTEP5_GCONF_FAST_STANDSTILL_MASK          0x00000001ul
#define SILENTSTEP5_GCONF_STEALTHCHOP_DIS               0x00000000ul
#define SILENTSTEP5_GCONF_STEALTHCHOP_EN                0x00000002ul
#define SILENTSTEP5_GCONF_STEALTHCHOP_MASK              0x00000002ul
#define SILENTSTEP5_GCONF_MULTISTEP_FILT_DIS            0x00000000ul
#define SILENTSTEP5_GCONF_MULTISTEP_FILT_EN             0x00000004ul
#define SILENTSTEP5_GCONF_MULTISTEP_FILT_MASK           0x00000004ul
#define SILENTSTEP5_GCONF_SHAFT_NORMAL                  0x00000000ul
#define SILENTSTEP5_GCONF_SHAFT_INVERSE                 0x00000008ul
#define SILENTSTEP5_GCONF_SHAFT_MASK                    0x00000008ul
#define SILENTSTEP5_GCONF_SMALL_HYSTERESIS_DIS          0x00000000ul
#define SILENTSTEP5_GCONF_SMALL_HYSTERESIS_EN           0x00000010ul
#define SILENTSTEP5_GCONF_SMALL_HYSTERESIS_MASK         0x00000010ul
#define SILENTSTEP5_GCONF_STOP_ENABLE_DIS               0x00000000ul
#define SILENTSTEP5_GCONF_STOP_ENABLE_EN                0x00000020ul
#define SILENTSTEP5_GCONF_STOP_ENABLE_MASK              0x00000020ul
#define SILENTSTEP5_GCONF_DIRECT_MODE_DIS               0x00000000ul
#define SILENTSTEP5_GCONF_DIRECT_MODE_EN                0x00000040ul
#define SILENTSTEP5_GCONF_DIRECT_MODE_MASK              0x00000040ul
#define SILENTSTEP5_GCONF_LENGTH_STEP_PULSE_SHIFT       8
#define SILENTSTEP5_GCONF_LENGTH_STEP_PULSE_MASK        0x00000F00ul
#define SILENTSTEP5_GCONF_OV_N_DIS                      0x00000000ul
#define SILENTSTEP5_GCONF_OV_N_EN                       0x00001000ul
#define SILENTSTEP5_GCONF_OV_N_MASK                     0x00001000ul
#define SILENTSTEP5_GCONF_STEP_DIR_INTERNAL             0x00000000ul
#define SILENTSTEP5_GCONF_STEP_DIR_EXTERNAL             0x80000000ul
#define SILENTSTEP5_GCONF_STEP_DIR_MASK                 0x80000000ul

/**
 * @brief Silent Step 5 GSTAT register setting.
 * @details Specified setting for GSTAT register of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_GSTAT_RESET                         0x00000001ul
#define SILENTSTEP5_GSTAT_DRV_ERR                       0x00000002ul
#define SILENTSTEP5_GSTAT_UV_CP                         0x00000004ul
#define SILENTSTEP5_GSTAT_REGISTER_RESET                0x00000008ul
#define SILENTSTEP5_GSTAT_VM_UVLO                       0x00000010ul
#define SILENTSTEP5_GSTAT_VCCIO_UV                      0x00000020ul
#define SILENTSTEP5_GSTAT_CLEAR_ALL                     0x0000003Ful

/**
 * @brief Silent Step 5 DRV_CONF register setting.
 * @details Specified setting for DRV_CONF register of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_DRV_CONF_CURRENT_RANGE_0            0x00000000ul
#define SILENTSTEP5_DRV_CONF_CURRENT_RANGE_1            0x00000001ul
#define SILENTSTEP5_DRV_CONF_CURRENT_RANGE_2            0x00000002ul
#define SILENTSTEP5_DRV_CONF_CURRENT_RANGE_3            0x00000003ul
#define SILENTSTEP5_DRV_CONF_CURRENT_RANGE_MASK         0x00000003ul
#define SILENTSTEP5_DRV_CONF_CURRENT_SCALE_0            0x00000000ul
#define SILENTSTEP5_DRV_CONF_CURRENT_SCALE_1            0x00000004ul
#define SILENTSTEP5_DRV_CONF_CURRENT_SCALE_2            0x00000008ul
#define SILENTSTEP5_DRV_CONF_CURRENT_SCALE_3            0x0000000Cul
#define SILENTSTEP5_DRV_CONF_CURRENT_SCALE_MASK         0x0000000Cul
#define SILENTSTEP5_DRV_CONF_SLOPE_0                    0x00000000ul
#define SILENTSTEP5_DRV_CONF_SLOPE_1                    0x00000010ul
#define SILENTSTEP5_DRV_CONF_SLOPE_2                    0x00000020ul
#define SILENTSTEP5_DRV_CONF_SLOPE_3                    0x00000030ul
#define SILENTSTEP5_DRV_CONF_SLOPE_CONTROL_MASK         0x00000030ul

/**
 * @brief Silent Step 5 PLL register setting.
 * @details Specified setting for PLL register of Silent Step 5 Click driver.
 */
#define SILENTSTEP5_PLL_CLK_IS_STUCK                    0x00004000ul
#define SILENTSTEP5_PLL_CLK_LOSS                        0x00002000ul
#define SILENTSTEP5_PLL_CLK_1M0_TMO                     0x00001000ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_1MHZ              0x00000000ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_2MHZ              0x00000020ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_3MHZ              0x00000040ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_4MHZ              0x00000060ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_5MHZ              0x00000080ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_6MHZ              0x000000A0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_7MHZ              0x000000C0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_8MHZ              0x000000E0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_9MHZ              0x00000100ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_10MHZ             0x00000120ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_11MHZ             0x00000140ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_12MHZ             0x00000160ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_13MHZ             0x00000180ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_14MHZ             0x000001A0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_15MHZ             0x000001C0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_16MHZ             0x000001E0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_17MHZ             0x00000200ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_18MHZ             0x00000220ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_19MHZ             0x00000240ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_20MHZ             0x00000260ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_21MHZ             0x00000280ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_22MHZ             0x000002A0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_23MHZ             0x000002C0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_24MHZ             0x000002E0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_25MHZ             0x00000300ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_26MHZ             0x00000320ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_27MHZ             0x00000340ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_28MHZ             0x00000360ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_29MHZ             0x00000380ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_30MHZ             0x000003A0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_31MHZ             0x000003C0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_32MHZ             0x000003E0ul
#define SILENTSTEP5_PLL_CLOCK_DIVIDER_MASK              0x000003E0ul
#define SILENTSTEP5_PLL_CLK_FSM_ENA                     0x00000008ul
#define SILENTSTEP5_PLL_CLK_SYS_SEL                     0x00000004ul
#define SILENTSTEP5_PLL_EXT_NOT_INT                     0x00000002ul
#define SILENTSTEP5_PLL_COMMIT                          0x00000001ul

/**
 * @brief Silent Step 5 off time settings.
 * @details Specified setting for off time that controls duration of slow decay phase.
 */
#define SILENTSTEP5_TOFF_MASK                           0x0000000Ful
#define SILENTSTEP5_TOFF_SHIFT                          0
#define SILENTSTEP5_TOFF_DRIVER_DISABLE                 0
#define SILENTSTEP5_TOFF_MIN                            1
#define SILENTSTEP5_TOFF_DEFAULT                        4
#define SILENTSTEP5_TOFF_MAX                            15

/**
 * @brief Silent Step 5 step resolution settings.
 * @details Specified setting for micro step resolution.
 */
#define SILENTSTEP5_MRES_MASK                           0x0F000000ul
#define SILENTSTEP5_MRES_SHIFT                          24
#define SILENTSTEP5_MRES_256                            0
#define SILENTSTEP5_MRES_128                            1
#define SILENTSTEP5_MRES_64                             2
#define SILENTSTEP5_MRES_32                             3
#define SILENTSTEP5_MRES_16                             4
#define SILENTSTEP5_MRES_8                              5
#define SILENTSTEP5_MRES_4                              6
#define SILENTSTEP5_MRES_2                              7
#define SILENTSTEP5_MRES_FULLSTEP                       8

/**
 * @brief Silent Step 5 run current settings.
 * @details Specified setting for motor run current.
 */
#define SILENTSTEP5_IRUN_MASK                           0x0000FF00ul
#define SILENTSTEP5_IRUN_SHIFT                          8
#define SILENTSTEP5_IRUN_MIN                            0
#define SILENTSTEP5_IRUN_DEFAULT                        127
#define SILENTSTEP5_IRUN_MAX                            255

/**
 * @brief Silent Step 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Silent Step 5 Click driver.
 */
#define SILENTSTEP5_DEVICE_ADDRESS_A1A0_00              0x70
#define SILENTSTEP5_DEVICE_ADDRESS_A1A0_01              0x71
#define SILENTSTEP5_DEVICE_ADDRESS_A1A0_10              0x72
#define SILENTSTEP5_DEVICE_ADDRESS_A1A0_11              0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b silentstep5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SILENTSTEP5_SET_DATA_SAMPLE_EDGE                SET_SPI_DATA_SAMPLE_EDGE
#define SILENTSTEP5_SET_DATA_SAMPLE_MIDDLE              SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // silentstep5_set

/**
 * @defgroup silentstep5_map Silent Step 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Silent Step 5 Click driver.
 */

/**
 * @addtogroup silentstep5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Silent Step 5 Click to the selected MikroBUS.
 */
#define SILENTSTEP5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // silentstep5_map
/*! @} */ // silentstep5

/**
 * @brief Silent Step 5 Click context object.
 * @details Context object definition of Silent Step 5 Click driver.
 */
typedef struct silentstep5_s
{
    digital_out_t dir;                  /**< Direction control pin. */
    digital_out_t rst;                  /**< PCA9538A reset pin. */
    digital_out_t step;                 /**< Step signal pin. */

    digital_in_t int_pin;               /**< PCA9538A interrupt pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */

} silentstep5_t;

/**
 * @brief Silent Step 5 Click configuration object.
 * @details Configuration object definition of Silent Step 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t dir;                     /**< Direction control pin. */
    pin_name_t rst;                     /**< PCA9538A reset pin. */
    pin_name_t step;                    /**< Step signal pin. */
    pin_name_t int_pin;                 /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} silentstep5_cfg_t;

/**
 * @brief Silent Step 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SILENTSTEP5_OK = 0,
    SILENTSTEP5_ERROR = -1

} silentstep5_return_value_t;

/*!
 * @addtogroup silentstep5 Silent Step 5 Click Driver
 * @brief API for configuring and manipulating Silent Step 5 Click driver.
 * @{
 */

/**
 * @brief Silent Step 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #silentstep5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void silentstep5_cfg_setup ( silentstep5_cfg_t *cfg );

/**
 * @brief Silent Step 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #silentstep5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_init ( silentstep5_t *ctx, silentstep5_cfg_t *cfg );

/**
 * @brief Silent Step 5 default configuration function.
 * @details This function executes a default configuration of Silent Step 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t silentstep5_default_cfg ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 write reg function.
 * @details This function writes a desired 32-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_write_reg ( silentstep5_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Silent Step 5 read reg function.
 * @details This function reads 32-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 32-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_read_reg ( silentstep5_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Silent Step 5 write expander reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_write_exp_reg ( silentstep5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Silent Step 5 read expander reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_read_exp_reg ( silentstep5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Silent Step 5 get sleep pin function.
 * @details This function reads the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_get_sleep_pin ( silentstep5_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 5 set sleep pin function.
 * @details This function sets the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_set_sleep_pin ( silentstep5_t *ctx, uint8_t state );

/**
 * @brief Silent Step 5 get diag0 pin function.
 * @details This function reads the diag0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_get_diag0_pin ( silentstep5_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 5 get diag1 pin function.
 * @details This function reads the diag1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_get_diag1_pin ( silentstep5_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 5 get drv_en pin function.
 * @details This function reads the driver enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_get_drv_en_pin ( silentstep5_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 5 set drv_en pin function.
 * @details This function sets the driver enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_set_drv_en_pin ( silentstep5_t *ctx, uint8_t state );

/**
 * @brief Silent Step 5 enable device function.
 * @details This function enables the device by setting the DRV_EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_enable_device ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 disable device function.
 * @details This function disables the device by setting the DRV_EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_disable_device ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void silentstep5_set_direction ( silentstep5_t *ctx, uint8_t dir );

/**
 * @brief Silent Step 5 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep5_switch_direction ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 reset expander function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep5_reset_exp ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep5_set_rst_pin ( silentstep5_t *ctx, uint8_t state );

/**
 * @brief Silent Step 5 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t silentstep5_get_int_pin ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep5_set_step_pin ( silentstep5_t *ctx, uint8_t state );

/**
 * @brief Silent Step 5 set toff function.
 * @details This function sets the off time and driver enable bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] toff : TOFF bits setting [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_set_toff ( silentstep5_t *ctx, uint8_t toff );

/**
 * @brief Silent Step 5 set step res function.
 * @details This function sets the microstep resolution bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] mres : MRES bits setting:
 *                   @li @c 0 - 1/256 microsteps,
 *                   @li @c 1 - 1/128 microsteps,
 *                   @li @c 2 - 1/64 microsteps,
 *                   @li @c 3 - 1/32 microsteps,
 *                   @li @c 4 - 1/16 microsteps,
 *                   @li @c 5 - 1/8 microsteps,
 *                   @li @c 6 - quarter step,
 *                   @li @c 7 - half step,
 *                   @li @c 8 - full step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_set_step_res ( silentstep5_t *ctx, uint8_t mres );

/**
 * @brief Silent Step 5 set run current function.
 * @details This function sets the motor run current bits in IHOLD_IRUN register.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] irun : IRUN bits setting [0-31].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_set_run_current ( silentstep5_t *ctx, uint8_t irun );

/**
 * @brief Silent Step 5 enable step dir interface function.
 * @details This function enables STEP and DIR interface as step source.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_enable_step_dir ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 disable step dir interface function.
 * @details This function disables STEP and DIR interface as step source.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep5_disable_step_dir ( silentstep5_t *ctx );

/**
 * @brief Silent Step 5 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #silentstep5_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return None.
 * @note None.
 */
void silentstep5_drive_motor ( silentstep5_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // SILENTSTEP5_H

/*! @} */ // silentstep5

// ------------------------------------------------------------------------ END

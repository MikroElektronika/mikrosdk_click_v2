/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file silentstep2.h
 * @brief This file contains API for Silent Step 2 Click Driver.
 */

#ifndef SILENTSTEP2_H
#define SILENTSTEP2_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup silentstep2 Silent Step 2 Click Driver
 * @brief API for configuring and manipulating Silent Step 2 Click driver.
 * @{
 */

/**
 * @defgroup silentstep2_reg Silent Step 2 Registers List
 * @brief List of registers of Silent Step 2 Click driver.
 */

/**
 * @addtogroup silentstep2_reg
 * @{
 */

/**
 * @brief Silent Step 2 description register.
 * @details Specified register for description of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_REG_GCONF                      0x00 
#define SILENTSTEP2_REG_GSTAT                      0x01 
#define SILENTSTEP2_REG_IOIN                       0x04 
#define SILENTSTEP2_REG_IHOLD_IRUN                 0x10 
#define SILENTSTEP2_REG_TPOWERDOWN                 0x11 
#define SILENTSTEP2_REG_TSTEP                      0x12 
#define SILENTSTEP2_REG_TPWMTHRS                   0x13 
#define SILENTSTEP2_REG_TCOOLTHRS                  0x14 
#define SILENTSTEP2_REG_THIGH                      0x15 
#define SILENTSTEP2_REG_XDIRECT                    0x2D  
#define SILENTSTEP2_REG_VDCMIN                     0x33 
#define SILENTSTEP2_REG_MSLUT0                     0x60 
#define SILENTSTEP2_REG_MSLUT1                     0x61 
#define SILENTSTEP2_REG_MSLUT2                     0x62 
#define SILENTSTEP2_REG_MSLUT3                     0x63 
#define SILENTSTEP2_REG_MSLUT4                     0x64 
#define SILENTSTEP2_REG_MSLUT5                     0x65 
#define SILENTSTEP2_REG_MSLUT6                     0x66 
#define SILENTSTEP2_REG_MSLUT7                     0x67 
#define SILENTSTEP2_REG_MSLUTSEL                   0x68 
#define SILENTSTEP2_REG_MSLUTSTART                 0x69
#define SILENTSTEP2_REG_MSCNT                      0x6A
#define SILENTSTEP2_REG_MSCURACT                   0x6B
#define SILENTSTEP2_REG_CHOPCONF                   0x6C
#define SILENTSTEP2_REG_COOLCONF                   0x6D
#define SILENTSTEP2_REG_DCCTRL                     0x6E
#define SILENTSTEP2_REG_DRV_STATUS                 0x6F
#define SILENTSTEP2_REG_PWMCONF                    0x70
#define SILENTSTEP2_REG_PWM_SCALE                  0x71
#define SILENTSTEP2_REG_ENCM_CTRL                  0x72
#define SILENTSTEP2_REG_LOST_STEPS                 0x73
#define SILENTSTEP2_REG_EXP_IN_PORT                0x00
#define SILENTSTEP2_REG_EXP_OUT_PORT               0x01
#define SILENTSTEP2_REG_EXP_POL_INV                0x02
#define SILENTSTEP2_REG_EXP_CONFIG                 0x03

/*! @} */ // silentstep2_reg

/**
 * @defgroup silentstep2_set Silent Step 2 Registers Settings
 * @brief Settings for registers of Silent Step 2 Click driver.
 */

/**
 * @addtogroup silentstep2_set
 * @{
 */

/**
 * @brief Silent Step 2 global status flags.
 * @details Specified global status flags of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_GSTAT_RESET                    0x00000001ul
#define SILENTSTEP2_GSTAT_DRV_ERR                  0x00000002ul
#define SILENTSTEP2_GSTAT_UV_CP                    0x00000004ul

/**
 * @brief Silent Step 2 global configuration flags.
 * @details Specified global configuration flags of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_GCONF_I_SC_AN_OP_NORMAL        0x00
#define SILENTSTEP2_GCONF_I_SC_AN_AIN              0x01
#define SILENTSTEP2_GCONF_INT_RSE_OP_NORMAL        0x00
#define SILENTSTEP2_GCONF_INT_RSE_INT_RSE          0x01
#define SILENTSTEP2_GCONF_DISABLE                  0x00
#define SILENTSTEP2_GCONF_ENABLE                   0x01

/**
 * @brief Silent Step 2 velocity setting for different chopper modes and full stepping to maximize torque.
 * @details Specified velocity setting for different chopper modes and full stepping to maximize torque of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_THIGH_DEFAULT                  0x00000300ul
#define SILENTSTEP2_THIGH_MAX                      0x000FFFFFul

/**
 * @brief Silent Step 2 threshold velocity for switching on smart
energy.
 * @details Specified threshold velocity for switching on smart
energy of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_TCOOLTHRS_DEFAULT              0x00002700ul
#define SILENTSTEP2_TCOOLTHRS_MAX                  0x000FFFFFul

/**
 * @brief Silent Step 2 coolStep smart current control register
and stallGuard2 configuration.
 * @details Specified coolStep smart current control register
and stallGuard2 configuration of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_CHOPCONF_SEMIN_0               0x00
#define SILENTSTEP2_CHOPCONF_SEMIN_BIT_MASK        0x0F
#define SILENTSTEP2_CHOPCONF_SEUP_1                0x00
#define SILENTSTEP2_CHOPCONF_SEUP_2                0x01
#define SILENTSTEP2_CHOPCONF_SEUP_3                0x02
#define SILENTSTEP2_CHOPCONF_SEUP_8                0x03
#define SILENTSTEP2_CHOPCONF_SEMAX_0               0x00
#define SILENTSTEP2_CHOPCONF_SEMAX_BIT_MASK        0x0F
#define SILENTSTEP2_CHOPCONF_SEDN_32               0x00
#define SILENTSTEP2_CHOPCONF_SEDN_8                0x01
#define SILENTSTEP2_CHOPCONF_SEDN_2                0x02
#define SILENTSTEP2_CHOPCONF_SEDN_1                0x03
#define SILENTSTEP2_CHOPCONF_SEIMIN_1_2            0x00
#define SILENTSTEP2_CHOPCONF_SEIMIN_1_4            0x01
#define SILENTSTEP2_CHOPCONF_SGT_M64               0x00
#define SILENTSTEP2_CHOPCONF_SGT_P64               0x7F
#define SILENTSTEP2_CHOPCONF_SFILT_MODE_STD        0x00
#define SILENTSTEP2_CHOPCONF_SFILT_MODE_FLTR       0x01

/**
 * @brief Silent Step 2 coolStep smart current control register
and stallGuard2 configuration.
 * @details Specified coolStep smart current control register
and stallGuard2 configuration of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_IHOLD_10_32                    0x0A
#define SILENTSTEP2_IHOLD_BIT_MASK                 0x1F
#define SILENTSTEP2_IRUN_10_32                     0x0A
#define SILENTSTEP2_IRUN_BIT_MASK                  0x1F
#define SILENTSTEP2_IHOLDDELAY_PWR_DOWN            0x00
#define SILENTSTEP2_IHOLDDELAY_32                  0x05
#define SILENTSTEP2_IHOLDDELAY_BIT_MASK            0x0F

/**
 * @brief Silent Step 2 off time setting controls duration of slow decay phase.
 * @details Specified off time setting controls duration of slow decay phase of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_TOFF_DIS                       0x00
#define SILENTSTEP2_TOFF_NCLK_140                  0x04
#define SILENTSTEP2_TOFF_BIT_MASK                  0x0F

/**
 * @brief Silent Step 2 step speed and angle data values.
 * @details Specified step speed and angle data values of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_STEP_SPEED_MIN                 1
#define SILENTSTEP2_STEP_SPEED_MAX                 100
#define SILENTSTEP2_ANGLE_360_DEGREES              360.0f

/**
 * @brief Silent Step 2 chopper and driver configuration.
 * @details Specified chopper and driver configuration of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_CHOPCONF_CHM_MODE_STND         0x00
#define SILENTSTEP2_CHOPCONF_CHM_CONST_OFF_TIME    0x01
#define SILENTSTEP2_CHOPCONF_CHM_BIT_MASK          0x00004000ul
#define SILENTSTEP2_CHOPCONF_HE_OS_M3              0x00
#define SILENTSTEP2_CHOPCONF_HE_OS_M2              0x01
#define SILENTSTEP2_CHOPCONF_HE_OS_M1              0x02
#define SILENTSTEP2_CHOPCONF_HE_OS_0               0x03
#define SILENTSTEP2_CHOPCONF_HE_OS_1               0x04
#define SILENTSTEP2_CHOPCONF_HE_OS_2               0x05
#define SILENTSTEP2_CHOPCONF_HE_OS_3               0x06
#define SILENTSTEP2_CHOPCONF_HE_OS_4               0x07
#define SILENTSTEP2_CHOPCONF_HE_OS_5               0x08
#define SILENTSTEP2_CHOPCONF_HE_OS_6               0x09
#define SILENTSTEP2_CHOPCONF_HE_OS_7               0x0A
#define SILENTSTEP2_CHOPCONF_HE_OS_8               0x0B
#define SILENTSTEP2_CHOPCONF_HE_OS_9               0x0C
#define SILENTSTEP2_CHOPCONF_HE_OS_10              0x0D
#define SILENTSTEP2_CHOPCONF_HE_OS_11              0x0E
#define SILENTSTEP2_CHOPCONF_HE_OS_12              0x0F
#define SILENTSTEP2_CHOPCONF_HE_OS_BIT_MASK        0x00000780ul
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_0           0x00
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_1           0x01
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_2           0x02
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_3           0x03
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_4           0x04
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_5           0x05
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_6           0x06
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_7           0x07
#define SILENTSTEP2_CHOPCONF_HSTRT_TFD_BIT_MASK    0x00000070ul

/**
 * @brief Silent Step 2 microstep table entries and defines four segments values.
 * @details Specified microstep table entries and defines four segments values of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_MSLUT_SEL_0                    0x00
#define SILENTSTEP2_MSLUT_SEL_1                    0x01
#define SILENTSTEP2_MSLUT_SEL_2                    0x02
#define SILENTSTEP2_MSLUT_SEL_3                    0x03
#define SILENTSTEP2_MSLUT_SEL_4                    0x04
#define SILENTSTEP2_MSLUT_SEL_5                    0x05
#define SILENTSTEP2_MSLUT_SEL_6                    0x06
#define SILENTSTEP2_MSLUT_SEL_7                    0x07
#define SILENTSTEP2_MSLUTSEL_WIDTH_BIT_MASK        0x000000FFul
#define SILENTSTEP2_MSLUTSEL_SEG_BIT_MASK          0x00FFFFFFul

/**
 * @brief Silent Step 2 absolute current at microstep table entry values.
 * @details Specified absolute current at microstep table entry values of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_MSLUTSTART_SIN_BIT_MASK        0x000000FFul
#define SILENTSTEP2_MSLUTSTART_SIN90_BIT_MASK      0x000000FFul

/**
 * @brief Silent Step 2 chopper configuration bit masks values.
 * @details Specified micro step resolution values of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_CHOPCONF_MRES_BIT_MASK         0xF0FFFFFFul
#define SILENTSTEP2_CHOPCONF_DEDGE_BIT_MASK        0xDFFFFFFFul
#define SILENTSTEP2_CHOPCONF_INTPOL_BIT_MASK       0xEFFFFFFFul
#define SILENTSTEP2_CHOPCONF_TBL_BIT_MASK          0xFFFE7FFFul
#define SILENTSTEP2_CHOPCONF_TOFF_BIT_MASK         0xFFFFFFF0ul

/**
 * @brief Silent Step 2 GPIO expander pin setting.
 * @details Specified setting for pin bit mask of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_PIN_NONE                       0x00
#define SILENTSTEP2_PIN_EN                         0x01
#define SILENTSTEP2_PIN_FT1                        0x02
#define SILENTSTEP2_PIN_FT2                        0x04
#define SILENTSTEP2_PIN_ALL                        0x07

/**
 * @brief Silent Step 2 step/direction driver mode.
 * @details Specified step/direction driver mode of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE     0
#define SILENTSTEP2_DIRECTION_CLOCKWISE            1

/**
 * @brief Silent Step 2 step delay default value.
 * @details Specified step delay default value of Silent Step 2 Click driver.
 */
#define SILENTSTEP2_STEP_DELAY_DEFAULT_100US       100ul

/**
 * @brief Silent Step 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Silent Step 2 Click driver.
 */
#define SILENTSTEP2_DEVICE_ADDRESS_0               0x70
#define SILENTSTEP2_DEVICE_ADDRESS_1               0x72
#define SILENTSTEP2_DEVICE_ADDRESS_2               0x74
#define SILENTSTEP2_DEVICE_ADDRESS_3               0x76

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b silentstep2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SILENTSTEP2_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define SILENTSTEP2_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // silentstep2_set

/**
 * @defgroup silentstep2_map Silent Step 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Silent Step 2 Click driver.
 */

/**
 * @addtogroup silentstep2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Silent Step 2 Click to the selected MikroBUS.
 */
#define SILENTSTEP2_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.stp  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // silentstep2_map
/*! @} */ // silentstep2

/**
 * @brief Silent Step 2 Click driver selector.
 * @details Selects target driver interface of Silent Step 2 Click driver.
 */
typedef enum
{
    SILENTSTEP2_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SILENTSTEP2_DRV_SEL_I2C       /**< I2C driver descriptor. */

} silentstep2_drv_t;

/**
 * @brief Silent Step 2 Click context object.
 * @details Context object definition of Silent Step 2 Click driver.
 */
typedef struct
{
    digital_out_t dir;       /**< Direction pin. */
    digital_out_t stp;       /**< Step pin. */

    digital_in_t int_pin;    /**< Interrupt pin. */

    i2c_master_t i2c;        /**< I2C driver object. */
    spi_master_t spi;        /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    
    uint32_t  step_delay;          /**< Step delay. */

} silentstep2_t;

/**
 * @brief Silent Step 2 Click configuration object.
 * @details Configuration object definition of Silent Step 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t dir;        /**< Direction pin. */
    pin_name_t stp;        /**< Step pin. */
    pin_name_t int_pin;    /**< Interrupt pin. */
    
    uint32_t  step_delay;  /**< Step delay. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} silentstep2_cfg_t;

/**
 * @brief Silent Step 2 Click global configuration object.
 * @details Global configuration object definition of Silent Step 2 Click driver.
 */
typedef struct
{
    uint8_t  i_scale_analog;       /**< Use voltage supplied to AIN as current reference. */
    uint8_t  internal_rsense;      /**< Enable internal sense resistors. */
    uint8_t  en_pwm_mode;          /**< Enable stealthChop voltage PWM mode. */
    uint8_t  enc_commutation;      /**< Enable commutation by full step encoder. */
    uint8_t  shaft;                /**< Inverse motor direction. */
    uint8_t  diag0_error;          /**< Enable DIAG0 active on driver errors. */
    uint8_t  diag0_otpw;           /**< Enable DIAG0 active on driver over temperature prewarning. */
    uint8_t  diag0_stall;          /**< Enable DIAG0 active on motor stall. */
    uint8_t  diag1_stall;          /**< Enable DIAG1 active on motor stall. */
    uint8_t  diag1_index;          /**< Enable DIAG1 active on index position. */
    uint8_t  diag1_onstate;        /**< Enable DIAG1 active when chopper is on. */
    uint8_t  diag1_steps_skipped;  /**< Enable output toggle. */
    uint8_t  diag0_int_pushpull;   /**< DIAG0 open - push pull. */
    uint8_t  diag1_pushpull;       /**< DIAG1 open - push pull. */
    uint8_t  small_hysteresis;     /**< Hysteresis for step frequency comparison. */
    uint8_t  stop_enable;          /**< Normal operation - Emergency stop. */
    uint8_t  direct_mode;          /**< Normal operation - Motor coil currents. */

} silentstep2_gconf_t;

/**
 * @brief Silent Step 2 Click smart energy control coolStep and stallGuard2 object.
 * @details Smart energy control coolStep and stallGuard2 object definition of Silent Step 2 Click driver.
 */
typedef struct
{
    uint8_t  semin;   /**< Min stallGuard2 value for smart current - control and enable. */
    uint8_t  seup;    /**< Current up step width. */
    uint8_t  semax;   /**< StallGuard2 hysteresis value for smart current control. */
    uint8_t  sedn;    /**< Current down step speed. */
    uint8_t  seimin;  /**< Minimum current for smart current control. */
    uint8_t  sgt;     /**< StallGuard2 threshold value. */
    uint8_t  sfilt;   /**< StallGuard2 filter enable. */

} silentstep2_coolconf_t;

/**
 * @brief Silent Step 2 Click voltage mode pwm stealthChop object.
 * @details Voltage mode pwm stealthChop object definition of Silent Step 2 Click driver.
 */
typedef struct
{
    uint8_t  pwm_ampl;       /**< User defined amplitude (offset). */
    uint8_t  pwm_grad;       /**< Amplitude (gradient) or regulation loop gradient. */
    uint8_t  pwm_freq;       /**< PWM frequency selection. */
    uint8_t  pwm_autoscale;  /**< PWM automatic amplitude scaling. */
    uint8_t  pwm_symmetric;  /**< Force symmetric PWM. */
    uint8_t  freewheel;      /**< Stand still option when motor current setting is zero. */

} silentstep2_pwmconf_t;

/**
 * @brief Silent Step 2 Click stallGuard2 value and driver error flags object.
 * @details StallGuard2 value and driver error flags object definition of Silent Step 2 Click driver.
 */
typedef struct
{
    uint16_t sg_result;    /**< StallGuard2 result respectively PWM on time for coil A. */
    uint8_t  fsactive;     /**< Full step active indicator. */
    uint8_t  cs_actual;    /**< Actual motor current / smart energy current. */
    uint8_t  stall_guard;  /**< StallGuard2 status. */
    uint8_t  ot;           /**< Overtemperature flag. */
    uint8_t  otpw;         /**< Overtemperature prewarning flag. */
    uint8_t  s2ga;         /**< Short to ground indicator phase A. */
    uint8_t  s2gb;         /**< Short to ground indicator phase B. */
    uint8_t  ola;          /**< Open load indicator phase A. */
    uint8_t  olb;          /**< Open load indicator phase B. */
    uint8_t  stst;         /**< Standstill indicator. */

} silentstep2_drv_status_t;

/**
 * @brief Silent Step 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SILENTSTEP2_OK = 0,
    SILENTSTEP2_ERROR = -1

} silentstep2_return_value_t;

/**
 * @brief Silent Step 2 Click reduced microstep resolution value data.
 * @details Predefined enum values for driver reduced microstep resolution values.
 */
typedef enum
{
    SILENTSTEP2_MRES_256 = 0,
    SILENTSTEP2_MRES_128,
    SILENTSTEP2_MRES_64,
    SILENTSTEP2_MRES_32,
    SILENTSTEP2_MRES_16,
    SILENTSTEP2_MRES_8,
    SILENTSTEP2_MRES_4,
    SILENTSTEP2_MRES_2,
    SILENTSTEP2_MRES_NATIVE
    
} silentstep2_mres_t;

/**
 * @brief Silent Step 2 Click comparator blank time value data.
 * @details Predefined enum values for driver comparator blank time values.
 */
typedef enum
{
    SILENTSTEP2_TBL_CLOCKS_16 = 0,
    SILENTSTEP2_TBL_CLOCKS_24,
    SILENTSTEP2_TBL_CLOCKS_36,
    SILENTSTEP2_TBL_CLOCKS_54
    
} silentstep2_tbl_t;

/*!
 * @addtogroup silentstep2 Silent Step 2 Click Driver
 * @brief API for configuring and manipulating Silent Step 2 Click driver.
 * @{
 */

/**
 * @brief Silent Step 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #silentstep2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void silentstep2_cfg_setup ( silentstep2_cfg_t *cfg );

/**
 * @brief Silent Step 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #silentstep2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_init ( silentstep2_t *ctx, silentstep2_cfg_t *cfg );

/**
 * @brief Silent Step 2 default configuration function.
 * @details This function executes a default configuration of Silent Step 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t silentstep2_default_cfg ( silentstep2_t *ctx );

/**
 * @brief Silent Step 2 data writing function.
 * @details This function writes a desired data byte to the selected register
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_reg_write ( silentstep2_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Silent Step 2 data reading function.
 * @details This function reads a desired data byte from the selected register
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_reg_read ( silentstep2_t *ctx, uint8_t reg, uint32_t *data_in );

/**
 * @brief Silent Step 2 sets global configuration function.
 * @details This function sets global configuration
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] gconf : Global configuration object.
 * See #silentstep2_gconf_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_gconf ( silentstep2_t *ctx, silentstep2_gconf_t gconf );

/**
 * @brief Silent Step 2 get global status function.
 * @details This function reads the global status data value
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[out] gstat : Global status flags.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_get_gstat ( silentstep2_t *ctx, uint32_t *gstat );

/**
 * @brief Silent Step 2 sets driver current control function.
 * @details This function sets the desired value of the driver's current control
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] ihold : Standstill current.
 * @param[in] irun : Motor run current.
 * @param[in] ihold_delay : Delay per current reduction step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_ihold_irun ( silentstep2_t *ctx, uint8_t ihold, uint8_t irun, uint8_t ihold_delay );

/**
 * @brief Silent Step 2 sets lower threshold velocity for switching on smart energy function.
 * @details This function sets the lower threshold velocity 
 * for switching on smart energy coolStep and stallGuard feature
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] tcoolthrs : Lower threshold velocity.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_tcoolthrs ( silentstep2_t *ctx, uint32_t tcoolthrs );

/**
 * @brief Silent Step 2 sets the velocity setting function.
 * @details This velocity setting allows velocity-dependent switching into 
 * a different chopper mode and full stepping to maximize torque (unsigned).
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] thigh : Velocity setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_thigh ( silentstep2_t *ctx, uint32_t thigh );

/**
 * @brief Silent Step 2 sets the microstep table entries function.
 * @details This function sets the differential coding for the first quarter of a wave
 * for switching on smart energy coolStep and stallGuard feature
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] mslut_num : Microstep table selection.
 * @param[in] mslut : Microstep table entries.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_mslut ( silentstep2_t *ctx, uint8_t mslut_sel, uint32_t mslut );

/**
 * @brief Silent Step 2 sets the microstep segments function.
 * @details This function sets the desired data values to 
 * define four segments within each quarter MSLUT wave
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] lut_seg_str : LUT segment.
 * @param[in] lut_width_sel : LUT width select.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_mslutsel ( silentstep2_t *ctx, uint32_t lut_seg_str, uint32_t lut_width_sel );

/**
 * @brief Silent Step 2 sets the absolute current microstep table function.
 * @details This function sets the absolute current microstep table entry at 0 and at positions 256
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] start_sin : Current microstep table entry at 0 positions.
 * @param[in] start_sin90 : Current microstep table entry at 256 positions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_mslutstart ( silentstep2_t *ctx, uint32_t start_sin, uint32_t start_sin90 );

/**
 * @brief Silent Step 2 sets the micro step resolution function.
 * @details This function sets the desired micro step resolution
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] step_width : Step width, reduced microstep resolution.
 * See #silentstep2_mres_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_mstep_res ( silentstep2_t *ctx, silentstep2_mres_t step_width );

/**
 * @brief Silent Step 2 sets the step impulsen function.
 * @details This function enable/disable step impulse 
 * at each step edge to reduce step frequency requirement
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] dedge_en : Enable/disable step impulse.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_dedge ( silentstep2_t *ctx, uint8_t dedge_en );

/**
 * @brief Silent Step 2 enable the actual microstep resolution function.
 * @details This function enable the actual microstep resolution becomes extrapolated
 * to 256 microsteps for smoothest motor operation
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] intpol_en : Enable/disable interpolation to 256 microsteps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_intpol ( silentstep2_t *ctx, uint8_t intpol_en );

/**
 * @brief Silent Step 2 enable the blank time select function.
 * @details This function enable the comparator blank time to 16, 24, 36 or 54 clocks
 * to 256 microsteps for smoothest motor operation
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] intpol_en : Blank time select.
 * See #silentstep2_tbl_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_tbl_blank_time ( silentstep2_t *ctx, silentstep2_tbl_t tbl );

/**
 * @brief Silent Step 2 sets the chopper mode config function.
 * @details This function sets the chopper mode, hysteresis low value/sine wave offset
 * and hysteresis start value/fast decay time setting
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] chm : Chopper mode select.
 * @param[in] h_end_offset : Hysteresis low value/sine wave offset.
 * @param[in] hstrt_tfd : Hysteresis start value/fast decay time setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_h_end_strt ( silentstep2_t *ctx, uint8_t chm, uint8_t h_end_offset, uint8_t hstrt_tfd );

/**
 * @brief Silent Step 2 sets the off time and driver enable function.
 * @details This function sets the off time setting controls duration of slow decay phase 
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] off_time : Off time and driver enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_toff ( silentstep2_t *ctx, uint8_t off_time );

/**
 * @brief Silent Step 2 sets the coolStep smart current control function.
 * @details This function sets the coolStep smart current control 
 * and stallGuard2 configuration data
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] coolconf : CoolStep smart current control object.
 * See #silentstep2_coolconf_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_coolconf ( silentstep2_t *ctx, silentstep2_coolconf_t coolconf );

/**
 * @brief Silent Step 2 sets the voltage PWM Mode stealthChop function.
 * @details This function sets the voltage PWM Mode stealthChop
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] coolconf : Voltage PWM Mode stealthChop object.
 * See #silentstep2_pwmconf_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_pwmconf ( silentstep2_t *ctx, silentstep2_pwmconf_t pwmconf );

/**
 * @brief Silent Step 2 get driver status error flags function.
 * @details This function reads the stallguard2 value and driver status error flags
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[out] drv_status : Driver status error object.
 * See #silentstep2_drv_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_get_drv_status ( silentstep2_t *ctx, silentstep2_drv_status_t *drv_status );

/**
 * @brief Silent Step 2 port expander data writing function.
 * @details This function writes a desired data byte to the selected register
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_port_exp_write ( silentstep2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Silent Step 2 port expander data reading function.
 * @details This function reads a desired data byte from the selected register
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_port_exp_read ( silentstep2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Silent Step 2 sets the pin states function.
 * @details This function sets and clears the value of the selected pins
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @param[in] clr_mask : Pin clear mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_set_pins ( silentstep2_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Silent Step 2 get the diagnostics output DIAG0 function.
 * @details This function reads the diagnostics output DIAG0 pin state
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] diag0 : DIAG0 pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_get_diag0 ( silentstep2_t *ctx, uint8_t *diag0 );

/**
 * @brief Silent Step 2 get the diagnostics output DIAG1 function.
 * @details This function reads the diagnostics output DIAG1 pin state
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] diag1 : DIAG1 pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_get_diag1 ( silentstep2_t *ctx, uint8_t *diag1 );

/**
 * @brief Silent Step 2 sets the power OFF function.
 * @details This function sets the power stage switched OFF
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_switch_off ( silentstep2_t *ctx );

/**
 * @brief Silent Step 2 enable input function.
 * @details This function perform device power ON by enabling the inputs
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_input_enable ( silentstep2_t *ctx );

/**
 * @brief Silent Step 2 sets the clockwise or counterclockwise direction movement function.
 * @details This function selects the direction of movement of the
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] dir : Direction of movement.
 * @return Nothing.
 * @note None.
 */
void silentstep2_set_direction ( silentstep2_t *ctx, uint8_t dir );

/**
 * @brief Silent Step 2 set the step pin state function.
 * @details This function sets the step (STP) pin state
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] step : Step (STP) pin state.
 * @return Nothing.
 * @note None.
 */
void silentstep2_set_step ( silentstep2_t *ctx, uint8_t step );

/**
 * @brief Silent Step 2 make the one step function.
 * @details This function is used to make one step of the desired speed
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed percent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_make_one_step ( silentstep2_t *ctx, uint8_t step_speed );

/**
 * @brief Silent Step 2 rotates the shaft through a desired angle function.
 * @details This function rotates the shaft through a desired step speed and angle
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed percent.
 * @param[in] angle : Angle of rotation.
 * @param[in] res_360 : Resolution of steps per revolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep2_rotate_by_angle ( silentstep2_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 );

/**
 * @brief Silent Step 2 get the interrupt function.
 * @details This function reads state of the interrupt (INT) pin
 * of the TMC2130, high performance driver IC for two phase stepper motors
 * on the Silent Step 2 Click board™. 
 * @param[in] ctx : Click context object.
 * See #silentstep2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t silentstep2_get_interrupt ( silentstep2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SILENTSTEP2_H

/*! @} */ // silentstep2

// ------------------------------------------------------------------------ END

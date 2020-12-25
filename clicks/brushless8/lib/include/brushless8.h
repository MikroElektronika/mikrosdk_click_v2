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
 * @file brushless8.h
 * @brief This file contains API for Brushless 8 Click Driver.
 */

#ifndef BRUSHLESS8_H
#define BRUSHLESS8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_analog_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup brushless8 Brushless 8 Click Driver
 * @brief API for configuring and manipulating Brushless 8 Click driver.
 * @{
 */

/**
 * @defgroup brushless8_reg Brushless 8 Register List
 * @brief List of registers of Brushless 8 Click driver.
 */

/**
 * @addtogroup brushless8_reg
 * @{
 */

/**
 * @brief Brushless 8 description register.
 * @details Specified register for description of Brushless 8 Click driver.
 */
#define BRUSHLESS8_DAC_REG_DEVICE_CONFIG         0x01
#define BRUSHLESS8_DAC_REG_STATUS_TRIGGER        0x02
#define BRUSHLESS8_DAC_REG_BRDCAST               0x03
#define BRUSHLESS8_DAC_REG_CHN_A_DVSP            0x08
#define BRUSHLESS8_DAC_REG_CHN_B_FGC             0x09
#define BRUSHLESS8_DAC_REG_CHN_C_LA              0x0A
#define BRUSHLESS8_DAC_REG_CHN_D_LAS             0x0B
#define BRUSHLESS8_DAC_REG_CHN_E_LAL             0x0C
#define BRUSHLESS8_DAC_REG_CHN_F_LAAJ            0x0D

/*! @} */ // brushless8_reg

/**
 * @defgroup brushless8_set Brushless 8 Registers Settings
 * @brief Settings for registers of Brushless 8 Click driver.
 */

/**
 * @addtogroup brushless8_set
 * @{
 */

/**
 * @brief Brushless 8 motor direction control.
 * @details @b dir pin status for motor rotating direcion control.
 */
#define BRUSHLESS8_DIRECTION_CW                  1
#define BRUSHLESS8_DIRECTION_CCW                 0

/**
 * @brief Brushless 8 motor reset pin state setting.
 * @details Specified values used for setting @b rst pin in
 * adequate state.
 */
#define BRUSHLESS8_RESET_EN                      1
#define BRUSHLESS8_RESET_DIS                     0

/**
 * @brief Brushless 8 DAC @b VREF and ADC resolution.
 * @details DAC referent Voltage and ADC resolution.
 */
#define BRUSHLESS8_VREF                          5000
#define BRUSHLESS8_RESOLUTION                    1024

/**
 * @brief Brushless 8 function status.
 * @details Specified function status.
 */
#define BRUSHLESS8_RETVAL                        int8_t
#define BRUSHLESS8_OK                            0
#define BRUSHLESS8_ERROR                         (-1)
#define BRUSHLESS8_PARAM_ERROR                   (-2)

/**
 * @brief Brushless 8 @b fcg pin functions.
 * @details FGC pin controls FG pin functionality.
 */
#define BRUSHLESS8_FGC_STEP_0                    0
#define BRUSHLESS8_FGC_STEP_1                    310
#define BRUSHLESS8_FGC_STEP_2                    630
#define BRUSHLESS8_FGC_STEP_3                    940
#define BRUSHLESS8_FGC_STEP_4                    1250
#define BRUSHLESS8_FGC_STEP_5                    1560
#define BRUSHLESS8_FGC_STEP_6                    1880
#define BRUSHLESS8_FGC_STEP_7                    2190
#define BRUSHLESS8_FGC_STEP_8                    2500
#define BRUSHLESS8_FGC_STEP_9                    2810

/**
 * @brief Brushless 8 LAS pin settings.
 * @details Setting specific V on LAS pin set its functionality for
 * sine_wave_generation.
 */
#define BRUSHLESS8_LAS_AUTOMATIC_60_DEG_RST      0
#define BRUSHLESS8_LAS_AUTOMATIC_360_DEG_RST     1250
#define BRUSHLESS8_LAS_EXT_IN_60_DEG_RST         2500
#define BRUSHLESS8_LAS_EXT_IN_360_DEG_RST        3750

/**
 * @brief Brushless 8 LA pin settings.
 * @details Setting specific V on LA pin set its functionality for
 * lead angle.
 */
#define BRUSHLESS8_LA_STEP_0_DEG_0               0
#define BRUSHLESS8_LA_STEP_1_DEG_1p9             160
#define BRUSHLESS8_LA_STEP_2_DEG_3p8             310
#define BRUSHLESS8_LA_STEP_3_DEG_5p6             470
#define BRUSHLESS8_LA_STEP_4_DEG_7p5             630
#define BRUSHLESS8_LA_STEP_5_DEG_9p4             780
#define BRUSHLESS8_LA_STEP_6_DEG_11p3            940
#define BRUSHLESS8_LA_STEP_7_DEG_13p1            1090
#define BRUSHLESS8_LA_STEP_8_DEG_15              1250
#define BRUSHLESS8_LA_STEP_9_DEG_16p9            1410
#define BRUSHLESS8_LA_STEP_10_DEG_18p8           1560
#define BRUSHLESS8_LA_STEP_11_DEG_20p6           1720
#define BRUSHLESS8_LA_STEP_12_DEG_22p5           1880
#define BRUSHLESS8_LA_STEP_13_DEG_24p4           2030
#define BRUSHLESS8_LA_STEP_14_DEG_26p3           2190
#define BRUSHLESS8_LA_STEP_15_DEG_28p1           2340
#define BRUSHLESS8_LA_STEP_16_DEG_30             2500
#define BRUSHLESS8_LA_STEP_17_DEG_31p9           2660
#define BRUSHLESS8_LA_STEP_18_DEG_33p8           2810
#define BRUSHLESS8_LA_STEP_19_DEG_35p6           2970
#define BRUSHLESS8_LA_STEP_20_DEG_37p5           3130
#define BRUSHLESS8_LA_STEP_21_DEG_39p4           3280
#define BRUSHLESS8_LA_STEP_22_DEG_41p3           3440
#define BRUSHLESS8_LA_STEP_23_DEG_43p1           3590
#define BRUSHLESS8_LA_STEP_24_DEG_45             3750
#define BRUSHLESS8_LA_STEP_25_DEG_46p9           3910
#define BRUSHLESS8_LA_STEP_26_DEG_48p8           4060
#define BRUSHLESS8_LA_STEP_27_DEG_50p6           4220
#define BRUSHLESS8_LA_STEP_28_DEG_52p5           4380
#define BRUSHLESS8_LA_STEP_29_DEG_54p4           4530
#define BRUSHLESS8_LA_STEP_30_DEG_56p3           4690
#define BRUSHLESS8_LA_STEP_31_DEG_58p1           4840

/**
 * @brief Brushless 8 LAL pin settings.
 * @details Setting specific V on LAL pin set its functionality for
 * VSP limit.
 */
#define BRUSHLESS8_LAL_STEP_0_DEG_0              0
#define BRUSHLESS8_LAL_STEP_1_DEG_5p6            310
#define BRUSHLESS8_LAL_STEP_2_DEG_0              630
#define BRUSHLESS8_LAL_STEP_3_DEG_11p3           640
#define BRUSHLESS8_LAL_STEP_4_DEG_5p6            1250
#define BRUSHLESS8_LAL_STEP_5_DEG_0              1560
#define BRUSHLESS8_LAL_STEP_6_DEG_12p2           1880
#define BRUSHLESS8_LAL_STEP_7_DEG_6p6            2190
#define BRUSHLESS8_LAL_STEP_8_DEG_0              2500
#define BRUSHLESS8_LAL_STEP_9_DEG_13p1           2810
#define BRUSHLESS8_LAL_STEP_10_DEG_7p5           3130
#define BRUSHLESS8_LAL_STEP_11_DEG_0             3440
#define BRUSHLESS8_LAL_STEP_12_DEG_18p8          3750
#define BRUSHLESS8_LAL_STEP_13_DEG_13p1          4060
#define BRUSHLESS8_LAL_STEP_14_DEG_7p5           4380
#define BRUSHLESS8_LAL_STEP_15_DEG_0             4690

/**
 * @brief Brushless 8 LAAJ pin settings.
 * @details Setting specific V on LAAJ pin set its functionality for 
 * adjusting auto lead angle.
 */
#define BRUSHLESS8_LAAJ_STEP_0_PHASE_DEG_0       0
#define BRUSHLESS8_LAAJ_STEP_1_PHASE_DEG_0       80
#define BRUSHLESS8_LAAJ_STEP_2_PHASE_DEG_0       160
#define BRUSHLESS8_LAAJ_STEP_3_PHASE_DEG_0       230
#define BRUSHLESS8_LAAJ_STEP_4_PHASE_DEG_0       310
#define BRUSHLESS8_LAAJ_STEP_5_PHASE_DEG_0       390
#define BRUSHLESS8_LAAJ_STEP_6_PHASE_DEG_0       470
#define BRUSHLESS8_LAAJ_STEP_7_PHASE_DEG_0       550
#define BRUSHLESS8_LAAJ_STEP_8_PHASE_DEG_0p9     630
#define BRUSHLESS8_LAAJ_STEP_9_PHASE_DEG_1p9     700
#define BRUSHLESS8_LAAJ_STEP_10_PHASE_DEG_2p8    780
#define BRUSHLESS8_LAAJ_STEP_11_PHASE_DEG_3p8    860
#define BRUSHLESS8_LAAJ_STEP_12_PHASE_DEG_4p7    940
#define BRUSHLESS8_LAAJ_STEP_13_PHASE_DEG_5p6    1020
#define BRUSHLESS8_LAAJ_STEP_14_PHASE_DEG_6p6    1090
#define BRUSHLESS8_LAAJ_STEP_15_PHASE_DEG_7p5    1170
#define BRUSHLESS8_LAAJ_STEP_16_PHASE_DEG_8p4    1250
#define BRUSHLESS8_LAAJ_STEP_17_PHASE_DEG_9p4    1330
#define BRUSHLESS8_LAAJ_STEP_18_PHASE_DEG_10p3   1410
#define BRUSHLESS8_LAAJ_STEP_19_PHASE_DEG_11p3   1480
#define BRUSHLESS8_LAAJ_STEP_20_PHASE_DEG_12p2   1560
#define BRUSHLESS8_LAAJ_STEP_21_PHASE_DEG_13p1   1640
#define BRUSHLESS8_LAAJ_STEP_22_PHASE_DEG_13p1   1720
#define BRUSHLESS8_LAAJ_STEP_23_PHASE_DEG_15     1800
#define BRUSHLESS8_LAAJ_STEP_24_PHASE_DEG_15p9   1880
#define BRUSHLESS8_LAAJ_STEP_25_PHASE_DEG_16p9   1950
#define BRUSHLESS8_LAAJ_STEP_26_PHASE_DEG_17p8   2030
#define BRUSHLESS8_LAAJ_STEP_27_PHASE_DEG_18p8   2110
#define BRUSHLESS8_LAAJ_STEP_28_PHASE_DEG_19p7   2190
#define BRUSHLESS8_LAAJ_STEP_29_PHASE_DEG_20p6   2270
#define BRUSHLESS8_LAAJ_STEP_30_PHASE_DEG_21p6   2340
#define BRUSHLESS8_LAAJ_STEP_31_PHASE_DEG_22p5   2420
#define BRUSHLESS8_LAAJ_STEP_32_PHASE_DEG_23p4   2500
#define BRUSHLESS8_LAAJ_STEP_33_PHASE_DEG_24p4   2580
#define BRUSHLESS8_LAAJ_STEP_34_PHASE_DEG_25p3   2660
#define BRUSHLESS8_LAAJ_STEP_35_PHASE_DEG_26p3   2730
#define BRUSHLESS8_LAAJ_STEP_36_PHASE_DEG_27p2   2810
#define BRUSHLESS8_LAAJ_STEP_37_PHASE_DEG_28p1   2890
#define BRUSHLESS8_LAAJ_STEP_38_PHASE_DEG_29p1   2970
#define BRUSHLESS8_LAAJ_STEP_39_PHASE_DEG_30     3050
#define BRUSHLESS8_LAAJ_STEP_40_PHASE_DEG_30     3130
#define BRUSHLESS8_LAAJ_STEP_41_PHASE_DEG_30     3200
#define BRUSHLESS8_LAAJ_STEP_42_PHASE_DEG_30     3280
#define BRUSHLESS8_LAAJ_STEP_43_PHASE_DEG_30     3360
#define BRUSHLESS8_LAAJ_STEP_44_PHASE_DEG_30     3440
#define BRUSHLESS8_LAAJ_STEP_45_PHASE_DEG_30     3520
#define BRUSHLESS8_LAAJ_STEP_46_PHASE_DEG_30     3590
#define BRUSHLESS8_LAAJ_STEP_47_PHASE_DEG_30     3670
#define BRUSHLESS8_LAAJ_STEP_48_PHASE_DEG_30     3750
#define BRUSHLESS8_LAAJ_STEP_49_PHASE_DEG_30     3830
#define BRUSHLESS8_LAAJ_STEP_50_PHASE_DEG_30     3910
#define BRUSHLESS8_LAAJ_STEP_51_PHASE_DEG_30     3980
#define BRUSHLESS8_LAAJ_STEP_52_PHASE_DEG_30     4060
#define BRUSHLESS8_LAAJ_STEP_53_PHASE_DEG_30     4140
#define BRUSHLESS8_LAAJ_STEP_54_PHASE_DEG_30     4220
#define BRUSHLESS8_LAAJ_STEP_55_PHASE_DEG_30     4300
#define BRUSHLESS8_LAAJ_STEP_56_PHASE_DEG_30     4380
#define BRUSHLESS8_LAAJ_STEP_57_PHASE_DEG_30     4450
#define BRUSHLESS8_LAAJ_STEP_58_PHASE_DEG_30     4530
#define BRUSHLESS8_LAAJ_STEP_59_PHASE_DEG_30     4610
#define BRUSHLESS8_LAAJ_STEP_60_PHASE_DEG_30     4690
#define BRUSHLESS8_LAAJ_STEP_61_PHASE_DEG_30     4770
#define BRUSHLESS8_LAAJ_STEP_62_PHASE_DEG_30     4840
#define BRUSHLESS8_LAAJ_STEP_63_PHASE_DEG_30     4920

/**
 * @brief Brushless 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 8 Click driver.
 */
#define BRUSHLESS8_SLAVE_ADDRESS_1               0x47
#define BRUSHLESS8_SLAVE_ADDRESS_2               0x48

/**
 * @brief Brushless 8 motor control settings.
 * @details Macros for setting default communication for controlling motor.
 */
#define BRUSHLESS8_DAC                           1
#define BRUSHLESS8_PWM                           2

/*! @} */ // brushless8_set

/**
 * @defgroup brushless8_map Brushless 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 8 Click driver.
 */

/**
 * @addtogroup brushless8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 8  Click to the selected MikroBUS.
 */
#define BRUSHLESS8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.res = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fg  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless8_map
/*! @} */ // brushless8

/**
 * @brief Brushless 8  Click context object.
 * @details Context object definition of Brushless 8  Click driver.
 */
typedef struct brushless8_s
{
    digital_out_t dir;     /**< Chip select pin. */
    digital_out_t res;     /**< Reset pin. */

    digital_in_t an;       /**< Analog input pin. */
    digital_in_t fg;       /**< Interrupt pin. */

    i2c_master_t i2c;      /**< I2C driver object. */
    pwm_t pwm;             /**< PWM driver object. */
    analog_in_t adc;       /**< ADC driver object. */

    uint8_t slave_address; /**< Device slave address (used for I2C driver). */

    uint16_t pwm_period;   /**< PWM period value. */
    uint32_t pwm_freq;     /**< PWM frequency value. */
    
    uint8_t ctrl_mod;      /**< Selected operating mode. */
} brushless8_t;

/**
 * @brief Brushless 8  Click configuration object.
 * @details Configuration object definition of Brushless 8  Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t dir;        /**< Description. */
    pin_name_t an;         /**< Description. */
    pin_name_t res;        /**< Description. */
    pin_name_t pwm;        /**< Description. */
    pin_name_t fg;         /**< Description. */

    uint32_t i2c_speed;    /**< I2C serial speed. */
    uint8_t  i2c_address;  /**< I2C slave address. */
    
    uint32_t dev_pwm_freq; /**< PWM frequency value. */
    
    analog_in_resolution_t resolution; /**< Resolution */
    float vref;                        /**< Reference voltage */
    
    uint8_t ctrl_mod;                  /**< Selected operating mode. */
} brushless8_cfg_t;

/*!
 * @addtogroup brushless8 Brushless 8  Click Driver
 * @brief API for configuring and manipulating Brushless 8  Click driver.
 * @{
 */

/**
 * @brief Brushless 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg Click configuration structure.
 * See #brushless8_cfg_t object definition for detailed explanation.
 * 
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * SCL pin             | HAL_PIN_NC (invalid pin)  |
 * SDA pin             | HAL_PIN_NC (invalid pin)  |
 * DIR pin             | HAL_PIN_NC (invalid pin)  |
 * AN pin              | HAL_PIN_NC (invalid pin)  |
 * RST pin             | HAL_PIN_NC (invalid pin)  |
 * PWM pin             | HAL_PIN_NC (invalid pin)  |
 * FG pin              | HAL_PIN_NC (invalid pin)  |
 * I2C baud rate       | 100000bps                 |
 * I2C slave address   | 0x47                      |
 * PWM frequency       | 18kHz                     |
 * ADC resolution      | 12-bit                    |
 * ADC vref            | 2.5V                      |
 * Default mode        | BRUSHLESS8_PWM            |
 *
 * @return Nothing.
 * @note All used pins will be set to default state -- NOT CONNECTED.
 */
void brushless8_cfg_setup ( brushless8_cfg_t *cfg );

/**
 * @brief Brushless 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @param[in] cfg Click configuration structure.
 * See #brushless8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
BRUSHLESS8_RETVAL brushless8_init ( brushless8_t *ctx, brushless8_cfg_t *cfg );

/**
 * @brief Brushless 8 default configuration function.
 * @details This function executes a default configuration of Brushless 8 
 * click board.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist of any necessary configuration
 * or setting to set device into operating mode.
 */
BRUSHLESS8_RETVAL brushless8_default_cfg ( brushless8_t *ctx );

/**
 * @brief Brushless 8 I2C write function.
 * @details This function writes 16 bits of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @param[in] reg Start register address.
 * @param[in] write_data Data to be written.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void brushless8_dac_write_data ( brushless8_t *ctx, uint8_t reg, uint16_t write_data );

/**
 * @brief Brushless 8 I2C read function.
 * @details This function reads 16 bits of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @param[in] reg Start register address.
 * @return Output read data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint16_t brushless8_dac_read_data ( brushless8_t *ctx, uint8_t reg );

/**
 * @brief Brushless 8 fg state.
 * @details This function reads @b fg pin input state.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @return @li @c  0 - logical state low,
 *         @li @c  1 - logical state high.
 *
 * @note None.
 */
uint8_t brushless8_get_fg ( brushless8_t *ctx );

/**
 * @brief Brushless 8 @b dir pin setting.
 * @details This function sets @b dir pin output to
 * @b status setting.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @param[in] status Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 *
 * @note None.
 */
void brushless8_set_direction ( brushless8_t *ctx, uint8_t status );

/**
 * @brief Brushless 8 @b rst pin setting.
 * @details This function sets @b rst pin output to
 * @b status setting.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @param[in] status Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 *
 * @note None.
 */
void brushless8_set_reset ( brushless8_t *ctx, uint8_t status );

/**
 * @brief Brushless 8 I2C function for setting @b vout.
 * @details This function writes adequate @b vout value to
 * appropriate @b dac_chn channel.
 * @param[in] ctx Click context object.
 * See #brushless8_t object definition for detailed explanation.
 * @param[in] dac_chn Adequate channel.
 * @param[in] vout Output voltage.
 * @return Function returns @b BRUSHLESS8_OK.
 * @note None.
 */
int8_t brushless8_set_dac_vout ( brushless8_t *ctx, uint8_t dac_chn, uint16_t vout );

/**
 * @brief Sets PWM duty cycle.
 * @param ctx Click object.
 * @param duty_cycle PWM Duty cycle value.
 * @description This function sets the PWM duty cycle value
 * to @b duty_cycle.
 */
void brushless8_set_duty_cycle ( brushless8_t *ctx, float duty_cycle );

/**
 * @brief Stops PWM module.
 * @param ctx Click object.
 * @description This function stops the PWM module.
 */
void brushless8_pwm_stop ( brushless8_t *ctx );

/**
 * @brief Starts PWM module.
 * @param ctx Click object.
 * @description This function starts the PWM module.
 */
void brushless8_pwm_start ( brushless8_t *ctx );

/**
 * @brief ADC read function.
 * @param[in] ctx Click object.
 * @param[out] data_out Buffer where read data is to be placed.
 * @return @li @c   0  - Ok,
 *         @li @c  -1  - Error.
 * @description This function reads the ADC converted data.
 */
BRUSHLESS8_RETVAL brushless8_read_adc ( brushless8_t *ctx, uint16_t *data_out );

/**
 * @brief AN voltage read function.
 * @param ctx  Click object.
 * @param data_out Buffer where read data is to be placed.
 * @return @li @c   0 - Ok,
 *         @li @c  -1 - Error.
 * @description This function reads and calculates the voltage level of the AN pin.
 */
BRUSHLESS8_RETVAL brushless8_read_an_voltage ( brushless8_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS8_H

/*! @} */ // brushless8
// ------------------------------------------------------------------------ END

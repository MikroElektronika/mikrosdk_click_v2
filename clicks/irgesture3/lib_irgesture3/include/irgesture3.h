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
 * @file irgesture3.h
 * @brief This file contains API for IR Gesture 3 Click Driver.
 */

#ifndef IRGESTURE3_H
#define IRGESTURE3_H

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

/*!
 * @addtogroup irgesture3 IR Gesture 3 Click Driver
 * @brief API for configuring and manipulating IR Gesture 3 Click driver.
 * @{
 */

/**
 * @defgroup irgesture3_reg IR Gesture 3 Registers List
 * @brief List of registers of IR Gesture 3 Click driver.
 */

/**
 * @addtogroup irgesture3_reg
 * @{
 */

/**
 * @brief IR Gesture 3 register list.
 * @details Specified register list of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_REG_STATUS                           0x00
#define IRGESTURE3_REG_INT_MASK                         0x01
#define IRGESTURE3_REG_GPIO_DRV                         0x02
#define IRGESTURE3_REG_BG_STATUS                        0x04
#define IRGESTURE3_REG_FIFO_THRESH                      0x06
#define IRGESTURE3_REG_DEVID                            0x08
#define IRGESTURE3_REG_I2CS_ID                          0x09
#define IRGESTURE3_REG_CLK_RATIO                        0x0A
#define IRGESTURE3_REG_GPIO_CTRL                        0x0B
#define IRGESTURE3_REG_SLAVE_ADDRESS_KEY                0x0D
#define IRGESTURE3_REG_SW_RESET                         0x0F
#define IRGESTURE3_REG_MODE                             0x10
#define IRGESTURE3_REG_SLOT_EN                          0x11
#define IRGESTURE3_REG_FSAMPLE                          0x12
#define IRGESTURE3_REG_PD_LED_SELECT                    0x14
#define IRGESTURE3_REG_NUM_AVG                          0x15
#define IRGESTURE3_REG_BG_MEAS_A                        0x16
#define IRGESTURE3_REG_INT_SEQ_A                        0x17
#define IRGESTURE3_REG_SLOTA_CH1_OFFSET                 0x18
#define IRGESTURE3_REG_SLOTA_CH2_OFFSET                 0x19
#define IRGESTURE3_REG_SLOTA_CH3_OFFSET                 0x1A
#define IRGESTURE3_REG_SLOTA_CH4_OFFSET                 0x1B
#define IRGESTURE3_REG_BG_MEAS_B                        0x1C
#define IRGESTURE3_REG_INT_SEQ_B                        0x1D
#define IRGESTURE3_REG_SLOTB_CH1_OFFSET                 0x1E
#define IRGESTURE3_REG_SLOTB_CH2_OFFSET                 0x1F
#define IRGESTURE3_REG_SLOTB_CH3_OFFSET                 0x20
#define IRGESTURE3_REG_SLOTB_CH4_OFFSET                 0x21
#define IRGESTURE3_REG_ILED3_COARSE                     0x22
#define IRGESTURE3_REG_ILED1_COARSE                     0x23
#define IRGESTURE3_REG_ILED2_COARSE                     0x24
#define IRGESTURE3_REG_ILED_FINE                        0x25
#define IRGESTURE3_REG_SLOTA_LED_PULSE                  0x30
#define IRGESTURE3_REG_SLOTA_NUMPULSES                  0x31
#define IRGESTURE3_REG_LED_DISABLE                      0x34
#define IRGESTURE3_REG_SLOTB_LED_PULSE                  0x35
#define IRGESTURE3_REG_SLOTB_NUMPULSES                  0x36
#define IRGESTURE3_REG_ALT_PWR_DN                       0x37
#define IRGESTURE3_REG_EXT_SYNC_STARTUP                 0x38
#define IRGESTURE3_REG_SLOTA_AFE_WINDOW                 0x39
#define IRGESTURE3_REG_SLOTB_AFE_WINDOW                 0x3B
#define IRGESTURE3_REG_AFE_PWR_CFG1                     0x3C
#define IRGESTURE3_REG_SLOTA_FLOAT_LED                  0x3E
#define IRGESTURE3_REG_SLOTB_FLOAT_LED                  0x3F
#define IRGESTURE3_REG_SLOTA_TIA_CFG                    0x42
#define IRGESTURE3_REG_SLOTA_AFE_CFG                    0x43
#define IRGESTURE3_REG_SLOTB_TIA_CFG                    0x44
#define IRGESTURE3_REG_SLOTB_AFE_CFG                    0x45
#define IRGESTURE3_REG_SAMPLE_CLK                       0x4B
#define IRGESTURE3_REG_CLK32M_ADJUST                    0x4D
#define IRGESTURE3_REG_EXT_SYNC_SEL                     0x4F
#define IRGESTURE3_REG_CLK32M_CAL_EN                    0x50
#define IRGESTURE3_REG_AFE_PWR_CFG2                     0x54
#define IRGESTURE3_REG_TIA_INDEP_GAIN                   0x55
#define IRGESTURE3_REG_MATH                             0x58
#define IRGESTURE3_REG_FLT_CONFIG_B                     0x59
#define IRGESTURE3_REG_FLT_LED_FIRE                     0x5A
#define IRGESTURE3_REG_FLT_CONFIG_A                     0x5E
#define IRGESTURE3_REG_DATA_ACCESS_CTL                  0x5F
#define IRGESTURE3_REG_FIFO_ACCESS                      0x60
#define IRGESTURE3_REG_SLOTA_PD1_16BIT                  0x64
#define IRGESTURE3_REG_SLOTA_PD2_16BIT                  0x65
#define IRGESTURE3_REG_SLOTA_PD3_16BIT                  0x66
#define IRGESTURE3_REG_SLOTA_PD4_16BIT                  0x67
#define IRGESTURE3_REG_SLOTB_PD1_16BIT                  0x68
#define IRGESTURE3_REG_SLOTB_PD2_16BIT                  0x69
#define IRGESTURE3_REG_SLOTB_PD3_16BIT                  0x6A
#define IRGESTURE3_REG_SLOTB_PD4_16BIT                  0x6B
#define IRGESTURE3_REG_A_PD1_LOW                        0x70
#define IRGESTURE3_REG_A_PD2_LOW                        0x71
#define IRGESTURE3_REG_A_PD3_LOW                        0x72
#define IRGESTURE3_REG_A_PD4_LOW                        0x73
#define IRGESTURE3_REG_A_PD1_HIGH                       0x74
#define IRGESTURE3_REG_A_PD2_HIGH                       0x75
#define IRGESTURE3_REG_A_PD3_HIGH                       0x76
#define IRGESTURE3_REG_A_PD4_HIGH                       0x77
#define IRGESTURE3_REG_B_PD1_LOW                        0x78
#define IRGESTURE3_REG_B_PD2_LOW                        0x79
#define IRGESTURE3_REG_B_PD3_LOW                        0x7A
#define IRGESTURE3_REG_B_PD4_LOW                        0x7B
#define IRGESTURE3_REG_B_PD1_HIGH                       0x7C
#define IRGESTURE3_REG_B_PD2_HIGH                       0x7D
#define IRGESTURE3_REG_B_PD3_HIGH                       0x7E
#define IRGESTURE3_REG_B_PD4_HIGH                       0x7F

/*! @} */ // irgesture3_reg

/**
 * @defgroup irgesture3_set IR Gesture 3 Registers Settings
 * @brief Settings for registers of IR Gesture 3 Click driver.
 */

/**
 * @addtogroup irgesture3_set
 * @{
 */

/**
 * @brief IR Gesture 3 SAMPLE_CLK register settings.
 * @details Specified settings for SAMPLE_CLK register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_SAMPLE_CLK_RESERVED                  0x2600u
#define IRGESTURE3_SAMPLE_CLK_CLK32K_BYP_MASK           0x0100u
#define IRGESTURE3_SAMPLE_CLK_CLK32K_EN_MASK            0x0080u
#define IRGESTURE3_SAMPLE_CLK_CLK32K_ADJUST_MASK        0x003Fu

/**
 * @brief IR Gesture 3 INT_MASK register settings.
 * @details Specified settings for INT_MASK register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_INT_MASK_RESERVED                    0x009Fu
#define IRGESTURE3_INT_MASK_FIFO_INT_MASK               0x0100u
#define IRGESTURE3_INT_MASK_SLOTB_INT_MASK              0x0040u
#define IRGESTURE3_INT_MASK_SLOTA_INT_MASK              0x0020u

/**
 * @brief IR Gesture 3 GPIO_DRV register settings.
 * @details Specified settings for GPIO_DRV register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_GPIO_DRV_GPIO1_DRV_MASK              0x0200u
#define IRGESTURE3_GPIO_DRV_GPIO1_POL_MASK              0x0100u
#define IRGESTURE3_GPIO_DRV_GPIO0_ENA_MASK              0x0004u
#define IRGESTURE3_GPIO_DRV_GPIO0_DRV_MASK              0x0002u
#define IRGESTURE3_GPIO_DRV_GPIO0_POL_MASK              0x0001u

/**
 * @brief IR Gesture 3 SLOT_EN register settings.
 * @details Specified settings for SLOT_EN register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_SLOT_EN_RDOUT_MODE_MASK              0x2000u
#define IRGESTURE3_SLOT_EN_FIFO_OVRN_PREVENT_MASK       0x1000u
#define IRGESTURE3_SLOT_EN_SLOTB_FIFO_MODE_MASK         0x01C0u
#define IRGESTURE3_SLOT_EN_SLOTB_EN_MASK                0x0020u
#define IRGESTURE3_SLOT_EN_SLOTA_FIFO_MODE_MASK         0x001Cu
#define IRGESTURE3_SLOT_EN_SLOTA_EN_MASK                0x0001u

/**
 * @brief IR Gesture 3 PD_LED_SELECT register settings.
 * @details Specified settings for PD_LED_SELECT register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_NC_NC_NC_NC   0x0000u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_34_12_NC_NC   0x0100u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_78_56_NC_NC   0x0200u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_1234_NC_NC_NC 0x0300u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_5_6_7_8       0x0400u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_1_2_3_4       0x0500u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_34_56_NC_NC   0x0600u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_5678_NC_NC_NC 0x0700u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_PD_SEL_MASK      0x0F00u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_NC_NC_NC_NC   0x0000u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_34_12_NC_NC   0x0010u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_78_56_NC_NC   0x0020u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_1234_NC_NC_NC 0x0030u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_5_6_7_8       0x0040u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_1_2_3_4       0x0050u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_34_56_NC_NC   0x0060u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_5678_NC_NC_NC 0x0070u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_PD_SEL_MASK      0x00F0u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_LED_FLOAT        0x0000u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_LED_1            0x0004u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_LED_2            0x0008u
#define IRGESTURE3_PD_LED_SELECT_SLOTB_LED_3            0x000Cu
#define IRGESTURE3_PD_LED_SELECT_SLOTB_LED_SEL_MASK     0x000Cu
#define IRGESTURE3_PD_LED_SELECT_SLOTA_LED_FLOAT        0x0000u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_LED_1            0x0001u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_LED_2            0x0002u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_LED_3            0x0003u
#define IRGESTURE3_PD_LED_SELECT_SLOTA_LED_SEL_MASK     0x0003u

/**
 * @brief IR Gesture 3 NUM_AVG register settings.
 * @details Specified settings for NUM_AVG register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_NUM_AVG_SLOTB_1                      0x0000u
#define IRGESTURE3_NUM_AVG_SLOTB_2                      0x0100u
#define IRGESTURE3_NUM_AVG_SLOTB_4                      0x0200u
#define IRGESTURE3_NUM_AVG_SLOTB_8                      0x0300u
#define IRGESTURE3_NUM_AVG_SLOTB_16                     0x0400u
#define IRGESTURE3_NUM_AVG_SLOTB_32                     0x0500u
#define IRGESTURE3_NUM_AVG_SLOTB_64                     0x0600u
#define IRGESTURE3_NUM_AVG_SLOTB_128                    0x0700u
#define IRGESTURE3_NUM_AVG_SLOTB_MASK                   0x0700u
#define IRGESTURE3_NUM_AVG_SLOTA_1                      0x0000u
#define IRGESTURE3_NUM_AVG_SLOTA_2                      0x0010u
#define IRGESTURE3_NUM_AVG_SLOTA_4                      0x0020u
#define IRGESTURE3_NUM_AVG_SLOTA_8                      0x0030u
#define IRGESTURE3_NUM_AVG_SLOTA_16                     0x0040u
#define IRGESTURE3_NUM_AVG_SLOTA_32                     0x0050u
#define IRGESTURE3_NUM_AVG_SLOTA_64                     0x0060u
#define IRGESTURE3_NUM_AVG_SLOTA_128                    0x0070u
#define IRGESTURE3_NUM_AVG_SLOTA_MASK                   0x0070u

/**
 * @brief IR Gesture 3 INT_SEQ_A register settings.
 * @details Specified settings for INT_SEQ_A register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_INT_SEQ_A_INTEG_ORDER_A_1001         0x0009u
#define IRGESTURE3_INT_SEQ_A_INTEG_ORDER_A_MASK         0x000Fu

/**
 * @brief IR Gesture 3 ILED1_COARSE register settings.
 * @details Specified settings for ILED1_COARSE register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_ILED1_COARSE_RESERVED                0x1000u
#define IRGESTURE3_ILED1_COARSE_SCALE_10_PCT            0x0000u
#define IRGESTURE3_ILED1_COARSE_SCALE_100_PCT           0x2000u
#define IRGESTURE3_ILED1_COARSE_SCALE_MASK              0x2000u
#define IRGESTURE3_ILED1_COARSE_SLEW_MIN                0x0000u
#define IRGESTURE3_ILED1_COARSE_SLEW_3                  0x0030u
#define IRGESTURE3_ILED1_COARSE_SLEW_MAX                0x0070u
#define IRGESTURE3_ILED1_COARSE_SLEW_MASK               0x0070u
#define IRGESTURE3_ILED1_COARSE_COARSE_MIN              0x0000u
#define IRGESTURE3_ILED1_COARSE_COARSE_6                0x0006u
#define IRGESTURE3_ILED1_COARSE_COARSE_MAX              0x000Fu
#define IRGESTURE3_ILED1_COARSE_COARSE_MASK             0x000Fu

/**
 * @brief IR Gesture 3 SLOTA_NUMPULSES register settings.
 * @details Specified settings for SLOTA_NUMPULSES register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_SLOTA_NUMPULSES_PULSES_4             0x0400u
#define IRGESTURE3_SLOTA_NUMPULSES_PULSES_MASK          0xFF00u
#define IRGESTURE3_SLOTA_NUMPULSES_PERIOD_15_US         0x000Eu
#define IRGESTURE3_SLOTA_NUMPULSES_PERIOD_MASK          0x00FFu

/**
 * @brief IR Gesture 3 SLOTA_AFE_WINDOW register settings.
 * @details Specified settings for SLOTA_AFE_WINDOW register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_SLOTA_AFE_WINDOW_WIDTH_4_US          0x2000u
#define IRGESTURE3_SLOTA_AFE_WINDOW_WIDTH_MASK          0xF800u
#define IRGESTURE3_SLOTA_AFE_WINDOW_OFFSET_23_5_US      0x02F0u
#define IRGESTURE3_SLOTA_AFE_WINDOW_OFFSET_MASK         0x07FFu

/**
 * @brief IR Gesture 3 MATH register settings.
 * @details Specified settings for MATH register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_MATH_FLT_MATH34_B_ADD_1_2            0x0000u
#define IRGESTURE3_MATH_FLT_MATH34_B_ADD_1_SUB_2        0x0400u
#define IRGESTURE3_MATH_FLT_MATH34_B_SUB_1_ADD_2        0x0800u
#define IRGESTURE3_MATH_FLT_MATH34_B_SUB_1_2            0x0C00u
#define IRGESTURE3_MATH_FLT_MATH34_B_MASK               0x0C00u
#define IRGESTURE3_MATH_FLT_MATH34_A_ADD_1_2            0x0000u
#define IRGESTURE3_MATH_FLT_MATH34_A_ADD_1_SUB_2        0x0100u
#define IRGESTURE3_MATH_FLT_MATH34_A_SUB_1_ADD_2        0x0200u
#define IRGESTURE3_MATH_FLT_MATH34_A_SUB_1_2            0x0300u
#define IRGESTURE3_MATH_FLT_MATH34_A_MASK               0x0300u
#define IRGESTURE3_MATH_ENA_INT_AS_BUF_MASK             0x0080u
#define IRGESTURE3_MATH_FLT_MATH12_B_ADD_1_2            0x0000u
#define IRGESTURE3_MATH_FLT_MATH12_B_ADD_1_SUB_2        0x0020u
#define IRGESTURE3_MATH_FLT_MATH12_B_SUB_1_ADD_2        0x0040u
#define IRGESTURE3_MATH_FLT_MATH12_B_SUB_1_2            0x0060u
#define IRGESTURE3_MATH_FLT_MATH12_B_MASK               0x0060u
#define IRGESTURE3_MATH_FLT_MATH12_A_ADD_1_2            0x0000u
#define IRGESTURE3_MATH_FLT_MATH12_A_ADD_1_SUB_2        0x0002u
#define IRGESTURE3_MATH_FLT_MATH12_A_SUB_1_ADD_2        0x0004u
#define IRGESTURE3_MATH_FLT_MATH12_A_SUB_1_2            0x0006u
#define IRGESTURE3_MATH_FLT_MATH12_A_MASK               0x0006u

/**
 * @brief IR Gesture 3 FSAMPLE register settings.
 * @details Specified settings for FSAMPLE register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_INT_OSC                              32000u
#define IRGESTURE3_FSAMPLE_500_HZ                       500u
#define IRGESTURE3_FSAMPLE_MAX                          2000u

/**
 * @brief IR Gesture 3 SW_RESET register settings.
 * @details Specified settings for SW_RESET register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_SW_RESET                             0x0001u

/**
 * @brief IR Gesture 3 MODE register settings.
 * @details Specified settings for MODE register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_MODE_STANDBY                         0x0000u
#define IRGESTURE3_MODE_PROGRAM                         0x0001u
#define IRGESTURE3_MODE_NORMAL                          0x0002u

/**
 * @brief IR Gesture 3 STATUS register settings.
 * @details Specified settings for STATUS register of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_STATUS_FIFO_SAMPLES_MASK             0xFF00u
#define IRGESTURE3_STATUS_SLOTB_INT_MASK                0x0040u
#define IRGESTURE3_STATUS_SLOTA_INT_MASK                0x0020u
#define IRGESTURE3_STATUS_CLEAR                         0xFFFFu

/**
 * @brief IR Gesture 3 timeout value for data ready.
 * @details Specified timeout value for data ready of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_TIMEOUT_MS                           5000u

/**
 * @brief IR Gesture 3 gesture calculation values.
 * @details Specified gesture calculation values of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_MIN_NUM_SAMPLES                      5
#define IRGESTURE3_MAX_NUM_SAMPLES                      500
#define IRGESTURE3_LIGHT_THRESHOLD                      1000
#define IRGESTURE3_DISTANCE_THRESHOLD                   0.07f
#define IRGESTURE3_GESTURE_CLICK                        0
#define IRGESTURE3_GESTURE_SWIPE_UP                     1
#define IRGESTURE3_GESTURE_SWIPE_DOWN                   2
#define IRGESTURE3_GESTURE_SWIPE_LEFT                   3
#define IRGESTURE3_GESTURE_SWIPE_RIGHT                  4

/**
 * @brief IR Gesture 3 device ID value.
 * @details Specified device ID value of IR Gesture 3 Click driver.
 */
#define IRGESTURE3_DEVICE_ID                            0x16
#define IRGESTURE3_DEVICE_ID_MASK                       0xFF

/**
 * @brief IR Gesture 3 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Gesture 3 Click driver.
 */
#define IRGESTURE3_DEVICE_ADDRESS                       0x64

/*! @} */ // irgesture3_set

/**
 * @defgroup irgesture3_map IR Gesture 3 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Gesture 3 Click driver.
 */

/**
 * @addtogroup irgesture3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Gesture 3 Click to the selected MikroBUS.
 */
#define IRGESTURE3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.io1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.io0 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // irgesture3_map
/*! @} */ // irgesture3

/**
 * @brief IR Gesture 3 Click photodiodes data object.
 * @details Photodiodes data object definition of IR Gesture 3 Click driver.
 */
typedef struct
{
    uint16_t x_left;
    uint16_t x_right;
    uint16_t y_top;
    uint16_t y_bottom;

} irgesture3_pd_data_t;

/**
 * @brief IR Gesture 3 Click context object.
 * @details Context object definition of IR Gesture 3 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t io1;           /**< GPIO1 pin. */
    digital_in_t io0;           /**< GPIO0 pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} irgesture3_t;

/**
 * @brief IR Gesture 3 Click configuration object.
 * @details Configuration object definition of IR Gesture 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t io1;             /**< GPIO1 pin. */
    pin_name_t io0;             /**< GPIO0 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} irgesture3_cfg_t;

/**
 * @brief IR Gesture 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRGESTURE3_OK = 0,
    IRGESTURE3_ERROR = -1

} irgesture3_return_value_t;

/*!
 * @addtogroup irgesture3 IR Gesture 3 Click Driver
 * @brief API for configuring and manipulating IR Gesture 3 Click driver.
 * @{
 */

/**
 * @brief IR Gesture 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irgesture3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irgesture3_cfg_setup ( irgesture3_cfg_t *cfg );

/**
 * @brief IR Gesture 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irgesture3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_init ( irgesture3_t *ctx, irgesture3_cfg_t *cfg );

/**
 * @brief IR Gesture 3 default configuration function.
 * @details This function executes a default configuration of IR Gesture 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irgesture3_default_cfg ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 write register function.
 * @details This function writes data word to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_write_register ( irgesture3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief IR Gesture 3 read register function.
 * @details This function reads data word from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_read_register ( irgesture3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief IR Gesture 3 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_check_communication ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 get io0 function.
 * @details This function returns the GPIO0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t irgesture3_get_io0_pin ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 get io1 function.
 * @details This function returns the GPIO1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t irgesture3_get_io1_pin ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 sw reset function.
 * @details This function executes software reset of the device.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_sw_reset ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 set mode function.
 * @details This function sets the device operating mode.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Standby,
 *                   @li @c 1 - Program,
 *                   @li @c 2 - Normal.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_set_mode ( irgesture3_t *ctx, uint8_t mode );

/**
 * @brief IR Gesture 3 set adc fsample function.
 * @details This function sets the sample frequency of the device.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[in] freq_hz : Sample frequency in Hz (up to 2000 Hz).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_set_adc_fsample ( irgesture3_t *ctx, uint16_t freq_hz );

/**
 * @brief IR Gesture 3 clear status function.
 * @details This function clears the STATUS register.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_clear_status ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 wait data ready function.
 * @details This function waits for the data ready interrupt up to @b IRGESTURE3_TIMEOUT_MS 
 * milliseconds and then clears the STATUS registers.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_wait_data_ready ( irgesture3_t *ctx );

/**
 * @brief IR Gesture 3 get pd data function.
 * @details This function waits for the data ready interrupt and then reads data from 
 * photodiodes XR, XL, YB, and YT that are connected to channels PD1 to PD4.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[out] pd_data : Photodiodes data.
 * See #irgesture3_pd_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_get_pd_data ( irgesture3_t *ctx, irgesture3_pd_data_t *pd_data );

/**
 * @brief IR Gesture 3 get gesture function.
 * @details This function waits up to @b IRGESTURE3_MAX_NUM_SAMPLES for an object to be detected
 * and then calculates its gesture.
 * @param[in] ctx : Click context object.
 * See #irgesture3_t object definition for detailed explanation.
 * @param[out] gesture : Calculated gesture of the detected object.
 *                       @li @c 0 - Click,
 *                       @li @c 1 - Swipe up,
 *                       @li @c 2 - Swipe down,
 *                       @li @c 3 - Swipe left,
 *                       @li @c 4 - Swipe right.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or no gesture detected.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgesture3_get_gesture ( irgesture3_t *ctx, uint8_t *gesture );

#ifdef __cplusplus
}
#endif
#endif // IRGESTURE3_H

/*! @} */ // irgesture3

// ------------------------------------------------------------------------ END

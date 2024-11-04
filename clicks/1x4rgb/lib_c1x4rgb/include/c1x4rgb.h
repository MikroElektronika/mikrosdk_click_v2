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
 * @file c1x4rgb.h
 * @brief This file contains API for 1x4 RGB Click Driver.
 */

#ifndef C1X4RGB_H
#define C1X4RGB_H

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
 * @addtogroup c1x4rgb 1x4 RGB Click Driver
 * @brief API for configuring and manipulating 1x4 RGB Click driver.
 * @{
 */

/**
 * @defgroup c1x4rgb_reg 1x4 RGB Registers List
 * @brief List of registers of 1x4 RGB Click driver.
 */

/**
 * @addtogroup c1x4rgb_reg
 * @{
 */

/**
 * @brief 1x4 RGB description register.
 * @details Specified register for description of 1x4 RGB Click driver.
 */
#define C1X4RGB_REG_CHIP_EN               0x0000u
#define C1X4RGB_REG_DEV_CFG_0             0x0001u
#define C1X4RGB_REG_DEV_CFG_1             0x0002u
#define C1X4RGB_REG_DEV_CFG_2             0x0003u
#define C1X4RGB_REG_DEV_CFG_3             0x0004u
#define C1X4RGB_REG_DEV_CFG_4             0x0005u
#define C1X4RGB_REG_DEV_CFG_5             0x0006u
#define C1X4RGB_REG_DEV_CFG_6             0x0007u
#define C1X4RGB_REG_DEV_CFG_7             0x0008u
#define C1X4RGB_REG_DEV_CFG_8             0x0009u
#define C1X4RGB_REG_DEV_CFG_9             0x000Au
#define C1X4RGB_REG_DEV_CFG_10            0x000Bu
#define C1X4RGB_REG_DEV_CFG_11            0x000Cu
#define C1X4RGB_REG_DEV_CFG_12            0x000Du
#define C1X4RGB_REG_CMD_UPDATE            0x0010u
#define C1X4RGB_REG_CMD_START             0x0011u
#define C1X4RGB_REG_CMD_STOP              0x0012u
#define C1X4RGB_REG_CMD_PAUSE             0x0013u
#define C1X4RGB_REG_CMD_CONTINUE          0x0014u
#define C1X4RGB_REG_LED_EN_1              0x0020u
#define C1X4RGB_REG_LED_EN_2              0x0021u
#define C1X4RGB_REG_FAULT_CLR             0x0022u
#define C1X4RGB_REG_RESET                 0x0023u
#define C1X4RGB_REG_MANUAL_DC_0           0x0030u
#define C1X4RGB_REG_MANUAL_DC_1           0x0031u
#define C1X4RGB_REG_MANUAL_DC_2           0x0032u
#define C1X4RGB_REG_MANUAL_DC_3           0x0033u
#define C1X4RGB_REG_MANUAL_L0_G           0x0034u
#define C1X4RGB_REG_MANUAL_L0_R           0x0035u
#define C1X4RGB_REG_MANUAL_L0_B           0x0036u
#define C1X4RGB_REG_MANUAL_L1_G           0x0037u
#define C1X4RGB_REG_MANUAL_L1_R           0x0038u
#define C1X4RGB_REG_MANUAL_L1_B           0x0039u
#define C1X4RGB_REG_MANUAL_L2_G           0x003Au
#define C1X4RGB_REG_MANUAL_L2_R           0x003Bu
#define C1X4RGB_REG_MANUAL_L2_B           0x003Cu
#define C1X4RGB_REG_MANUAL_L3_G           0x003Du
#define C1X4RGB_REG_MANUAL_L3_R           0x003Eu
#define C1X4RGB_REG_MANUAL_L3_B           0x003Fu
#define C1X4RGB_REG_MANUAL_PWM_0          0x0040u
#define C1X4RGB_REG_MANUAL_PWM_1          0x0041u
#define C1X4RGB_REG_MANUAL_PWM_2          0x0042u
#define C1X4RGB_REG_MANUAL_PWM_3          0x0043u
#define C1X4RGB_REG_MANUAL_PWM_L0_G       0x0044u
#define C1X4RGB_REG_MANUAL_PWM_L0_R       0x0045u
#define C1X4RGB_REG_MANUAL_PWM_L0_B       0x0046u
#define C1X4RGB_REG_MANUAL_PWM_L1_G       0x0047u
#define C1X4RGB_REG_MANUAL_PWM_L1_R       0x0048u
#define C1X4RGB_REG_MANUAL_PWM_L1_B       0x0049u
#define C1X4RGB_REG_MANUAL_PWM_L2_G       0x004Au
#define C1X4RGB_REG_MANUAL_PWM_L2_R       0x004Bu
#define C1X4RGB_REG_MANUAL_PWM_L2_B       0x004Cu
#define C1X4RGB_REG_MANUAL_PWM_L3_G       0x004Du
#define C1X4RGB_REG_MANUAL_PWM_L3_R       0x004Eu
#define C1X4RGB_REG_MANUAL_PWM_L3_B       0x004Fu
#define C1X4RGB_REG_AUTO_DC_0             0x0050u
#define C1X4RGB_REG_AUTO_DC_1             0x0051u
#define C1X4RGB_REG_AUTO_DC_2             0x0052u
#define C1X4RGB_REG_AUTO_DC_3             0x0053u
#define C1X4RGB_REG_AUTO_L0_G             0x0054u
#define C1X4RGB_REG_AUTO_L0_R             0x0055u
#define C1X4RGB_REG_AUTO_L0_B             0x0056u
#define C1X4RGB_REG_AUTO_L1_G             0x0057u
#define C1X4RGB_REG_AUTO_L1_R             0x0058u
#define C1X4RGB_REG_AUTO_L1_B             0x0059u
#define C1X4RGB_REG_AUTO_L2_G             0x005Au
#define C1X4RGB_REG_AUTO_L2_R             0x005Bu
#define C1X4RGB_REG_AUTO_L2_B             0x005Cu
#define C1X4RGB_REG_AUTO_L3_G             0x005Du
#define C1X4RGB_REG_AUTO_L3_R             0x005Eu
#define C1X4RGB_REG_AUTO_L3_B             0x005Fu
#define C1X4RGB_REG_LED0_AEP_START        0x0080u
#define C1X4RGB_REG_LED0_AEP_END          0x0099u
#define C1X4RGB_REG_LED1_AEP_START        0x009Au
#define C1X4RGB_REG_LED1_AEP_END          0x00B3u
#define C1X4RGB_REG_LED2_AEP_START        0x00B4u
#define C1X4RGB_REG_LED2_AEP_END          0x00CDu
#define C1X4RGB_REG_LED3_AEP_START        0x00CEu
#define C1X4RGB_REG_LED4_AEP_END          0x00E7u
#define C1X4RGB_REG_LED_A0_AEP_START      0x00E8u
#define C1X4RGB_REG_LED_A0_AEP_END        0x0101u
#define C1X4RGB_REG_LED_A1_AEP_START      0x0102u
#define C1X4RGB_REG_LED_A1_AEP_END        0x011Bu
#define C1X4RGB_REG_LED_A2_AEP_START      0x011Cu
#define C1X4RGB_REG_LED_A2_AEP_END        0x0135u
#define C1X4RGB_REG_LED_B0_AEP_START      0x0136u
#define C1X4RGB_REG_LED_B0_AEP_END        0x014Fu
#define C1X4RGB_REG_LED_B1_AEP_START      0x0150u
#define C1X4RGB_REG_LED_B1_AEP_END        0x0169u
#define C1X4RGB_REG_LED_B2_AEP_START      0x016Au
#define C1X4RGB_REG_LED_B2_AEP_END        0x0183u
#define C1X4RGB_REG_LED_C0_AEP_START      0x0184u
#define C1X4RGB_REG_LED_C0_AEP_END        0x019Du
#define C1X4RGB_REG_LED_C1_AEP_START      0x019Eu
#define C1X4RGB_REG_LED_C1_AEP_END        0x01B7u
#define C1X4RGB_REG_LED_C2_AEP_START      0x01B8u
#define C1X4RGB_REG_LED_C2_AEP_END        0x01D1u
#define C1X4RGB_REG_LED_D0_AEP_START      0x01D2u
#define C1X4RGB_REG_LED_D0_AEP_END        0x01EBu
#define C1X4RGB_REG_LED_D1_AEP_START      0x01ECu
#define C1X4RGB_REG_LED_D1_AEP_END        0x0205u
#define C1X4RGB_REG_LED_D2_AEP_START      0x0206u
#define C1X4RGB_REG_LED_D2_AEP_END        0x021Fu
#define C1X4RGB_REG_STATUS_TSD            0x0300u
#define C1X4RGB_REG_STATUS_LDO_1          0x0301u
#define C1X4RGB_REG_STATUS_LDO_2          0x0302u
#define C1X4RGB_REG_STATUS_LSD_1          0x0303u
#define C1X4RGB_REG_STATUS_PWM_INT_0      0x0305u
#define C1X4RGB_REG_STATUS_PWM_INT_1      0x0306u
#define C1X4RGB_REG_STATUS_PWM_INT_2      0x0307u
#define C1X4RGB_REG_STATUS_PWM_INT_3      0x0308u
#define C1X4RGB_REG_STATUS_PWM_INT_D0     0x0309u
#define C1X4RGB_REG_STATUS_PWM_INT_D1     0x030Au
#define C1X4RGB_REG_STATUS_PWM_INT_D2     0x030Bu
#define C1X4RGB_REG_STATUS_PWM_INT_D3     0x030Cu
#define C1X4RGB_REG_STATUS_PWM_INT_D4     0x030Du
#define C1X4RGB_REG_STATUS_PWM_INT_D5     0x030Eu
#define C1X4RGB_REG_STATUS_PWM_INT_D6     0x030Fu
#define C1X4RGB_REG_STATUS_PWM_INT_D7     0x0310u
#define C1X4RGB_REG_STATUS_PWM_INT_D8     0x0311u
#define C1X4RGB_REG_STATUS_PWM_INT_D9     0x0312u
#define C1X4RGB_REG_STATUS_PWM_INT_D10    0x0313u
#define C1X4RGB_REG_STATUS_PWM_INT_D11    0x0314u
#define C1X4RGB_REG_STATUS_PATTERN_1      0x0315u
#define C1X4RGB_REG_STATUS_PATTERN_2      0x0316u
#define C1X4RGB_REG_STATUS_PATTERN_3      0x0317u
#define C1X4RGB_REG_STATUS_PATTERN_4      0x0318u
#define C1X4RGB_REG_STATUS_PATTERN_5      0x0319u
#define C1X4RGB_REG_STATUS_PATTERN_6      0x031Au
#define C1X4RGB_REG_STATUS_PATTERN_7      0x031Bu
#define C1X4RGB_REG_STATUS_PATTERN_8      0x031Cu


/*! @} */ // c1x4rgb_reg

/**
 * @defgroup c1x4rgb_set 1x4 RGB Registers Settings
 * @brief Settings for registers of 1x4 RGB Click driver.
 */

/**
 * @addtogroup c1x4rgb_set
 * @{
 */

/**
 * @brief 1x4 RGB chip enable bitmask.
 * @details Chip enable bitmask of 1x4 RGB Click driver.
 */
#define C1X4RGB_CHIP_ENABLE               0x01

/**
 * @brief 1x4 RGB TCM drive mode selection.
 * @details TCM drive mode selection of 1x4 RGB Click driver.
 */
#define C1X4RGB_TCM_MODE_SCAN_1           0x10
#define C1X4RGB_TCM_MODE_SCAN_2           0x20
#define C1X4RGB_TCM_MODE_SCAN_3           0x30
#define C1X4RGB_TCM_MODE_SCAN_4           0x40

/**
 * @brief 1x4 RGB Configuration command selection.
 * @details Configuration command selection of 1x4 RGB Click driver.
 */
#define C1X4RGB_SET_CMD_UPDATE            0x00
#define C1X4RGB_SET_CMD_START             0x01
#define C1X4RGB_SET_CMD_STOP              0x02
#define C1X4RGB_SET_CMD_PAUSE             0x03
#define C1X4RGB_CMD_ENABLE                0x55

/**
 * @brief 1x4 RGB duty cycle to illuminate the LEDs percent data value.
 * @details Duty cycle to illuminate the LEDs percent data value of 1x4 RGB Click driver.
 */
#define C1X4RGB_DUTY_CYCLE_CALC_FACT      2.55f
#define C1X4RGB_DUTY_CYCLE_10             10.0f
#define C1X4RGB_DUTY_CYCLE_50             50.0f
#define C1X4RGB_DUTY_CYCLE_100            100.0f

/**
 * @brief 1x4 RGB LSD detection data value.
 * @details LSD detection data value of 1x4 RGB Click driver.
 */
#define C1X4RGB_LSD_DET_DEFAULT           0x0B

/**
 * @brief 1x4 RGB LEDs number selection.
 * @details LEDs number selection of 1x4 RGB Click driver.
 */
#define C1X4RGB_NUM_LED_0                 0
#define C1X4RGB_NUM_LED_1                 1
#define C1X4RGB_NUM_LED_2                 2
#define C1X4RGB_NUM_LED_3                 3
#define C1X4RGB_NUM_LED_4                 4
#define C1X4RGB_NUM_LED_5                 5
#define C1X4RGB_NUM_LED_6                 6
#define C1X4RGB_NUM_LED_7                 7
#define C1X4RGB_NUM_LED_8                 8
#define C1X4RGB_NUM_LED_9                 9
#define C1X4RGB_NUM_LED_10                10
#define C1X4RGB_NUM_LED_11                11

/**
 * @brief 1x4 RGB enable all LEDs data bitmask.
 * @details Enable all LEDs of 1x4 RGB Click driver.
 */
#define C1X4RGB_ENABLE_ALL_LEDS           0x0FFFu

/**
 * @brief 1x4 RGB LEDs position selection.
 * @details LEDs position selection of 1x4 RGB Click driver.
 */
#define C1X4RGB_LED_POS_LD1               0
#define C1X4RGB_LED_POS_LD2               1
#define C1X4RGB_LED_POS_LD3               2
#define C1X4RGB_LED_POS_LD4               3

/**
 * @brief 1x4 RGB Configuration command selection.
 * @details Configuration command selection of 1x4 RGB Click driver.
 */
#define C1X4RGB_LED_ENABLE_BITMASK        0x0F00U

/**
 * @brief 1x4 RGB pin states data values.
 * @details Pin states data values of 1x4 RGB Click driver.
 */
#define C1X4RGB_SYC_STATE_LOW             0x00
#define C1X4RGB_SYC_STATE_HIGH            0x01

/**
 * @brief 1x4 RGB device address setting.
 * @details Specified setting for device slave address selection of
 * 1x4 RGB Click driver.
 */
#define C1X4RGB_DEVICE_ADDRESS_IND        0x50
#define C1X4RGB_DEVICE_ADDRESS_BCST       0x6C

/*! @} */ // c1x4rgb_set

/**
 * @defgroup c1x4rgb_map 1x4 RGB MikroBUS Map
 * @brief MikroBUS pin mapping of 1x4 RGB Click driver.
 */

/**
 * @addtogroup c1x4rgb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 1x4 RGB Click to the selected MikroBUS.
 */
#define C1X4RGB_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.syc = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // c1x4rgb_map
/*! @} */ // c1x4rgb

/**
 * @brief 1x4 RGB Click context object.
 * @details Context object definition of 1x4 RGB Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t syc;        /**< Clock synchronous among multiple devices. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} c1x4rgb_t;

/**
 * @brief 1x4 RGB Click configuration object.
 * @details Configuration object definition of 1x4 RGB Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t syc;    /**< Clock synchronous among multiple devices. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} c1x4rgb_cfg_t;

/**
 * @brief 1x4 RGB Click LED color configuration object.
 * @details LED color configuration object definition of 1x4 RGB Click driver.
 */
typedef struct
{
    uint8_t red;      /**< Red color level: 0 to 255. */
    uint8_t green;    /**< Green color level: 0 to 255. */
    uint8_t blue;

} c1x4rgb_led_color_t;

/**
 * @brief 1x4 RGB Click LED position configuration object.
 * @details LED position configuration object definition of 1x4 RGB Click driver.
 */
typedef struct
{
    c1x4rgb_led_color_t led_0;
    c1x4rgb_led_color_t led_1;
    c1x4rgb_led_color_t led_2;
    c1x4rgb_led_color_t led_3;

} c1x4rgb_led_t;


/**
 * @brief 1x4 RGB Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C1X4RGB_OK = 0,
    C1X4RGB_ERROR = -1

} c1x4rgb_return_value_t;

/*!
 * @addtogroup c1x4rgb 1x4 RGB Click Driver
 * @brief API for configuring and manipulating 1x4 RGB Click driver.
 * @{
 */

/**
 * @brief 1x4 RGB configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c1x4rgb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c1x4rgb_cfg_setup ( c1x4rgb_cfg_t *cfg );

/**
 * @brief 1x4 RGB initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c1x4rgb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_init ( c1x4rgb_t *ctx, c1x4rgb_cfg_t *cfg );

/**
 * @brief 1x4 RGB default configuration function.
 * @details This function executes a default configuration of 1x4 RGB
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c1x4rgb_default_cfg ( c1x4rgb_t *ctx );

/**
 * @brief 1x4 RGB I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_generic_write ( c1x4rgb_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 1x4 RGB I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_generic_read ( c1x4rgb_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 1x4 RGB register writing function.
 * @details This writes a desired data byte to the selected register 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_reg_write ( c1x4rgb_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief 1x4 RGB register reading function.
 * @details This function reads a data bytes from the selected register 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_reg_read ( c1x4rgb_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief 1x4 RGB chip enable function.
 * @details This function enabled chip by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_chip_enable ( c1x4rgb_t *ctx );

/**
 * @brief 1x4 RGB set TCM mode function.
 * @details This function configure the desired LED drive mode as TCM 1/2/3/4 scans
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] dev_cfg : Dev_config register address [C1X4RGB_REG_DEV_CFG_0-C1X4RGB_REG_DEV_CFG_12].
 * @param[in] mode : TCM mode [C1X4RGB_TCM_MODE_SCAN_1-C1X4RGB_TCM_MODE_SCAN_4].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_set_tmc_mode ( c1x4rgb_t *ctx, uint8_t dev_cfg, uint8_t mode );

/**
 * @brief 1x4 RGB set LSD threshold function.
 * @details This function sets the desired LSD detection threshold
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] lsd_thold : LSD threshold.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_set_lsd_thold ( c1x4rgb_t *ctx, uint8_t lsd_thold );

/**
 * @brief 1x4 RGB set command function.
 * @details This function sets the desired command
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] command : Configuration command [C1X4RGB_REG_CMD_UPDATE-C1X4RGB_REG_CMD_CONTINUE].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_set_command ( c1x4rgb_t *ctx, uint8_t command );

/**
 * @brief 1x4 RGB get TSD status function.
 * @details This function reads TSD configuration error status
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[out] status : TSD configuration error status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_get_tsd_cfg_status ( c1x4rgb_t *ctx, uint8_t *status );

/**
 * @brief 1x4 RGB enable LEDs function.
 * @details This function turns on the desired LEDs
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] led_bitmask : LEDs bitmasks (12 LEDs) [0x0000-0x0FFF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_enable_leds ( c1x4rgb_t *ctx, uint16_t led_bitmask );

/**
 * @brief 1x4 RGB set LEDs illuminate function.
 * @details This function sets the desired duty cycle of illumination for all LEDs
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle [0-100%].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_set_leds_illuminate ( c1x4rgb_t *ctx, float duty_cycle );

/**
 * @brief 1x4 RGB set illuminate function.
 * @details This function sets the desired duty cycle of illumination for the selected LED
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] n_led : LEDs number [0-12].
 * @param[in] duty_cycle : Duty cycle [0-100%].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_set_led_illuminate ( c1x4rgb_t *ctx, uint8_t n_led, float duty_cycle );

/**
 * @brief 1x4 RGB set colors function.
 * @details This function sets the desired values of RGB colors
 * for the selected LED by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] led_pos : LED position LD1-LD4 [0-3].
 * @param[in] red : Red color [0-255].
 * @param[in] green : Green color [0-255].
 * @param[in] blue : Blue color [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_set_rgb_color ( c1x4rgb_t *ctx, uint8_t led_pos, uint8_t red, uint8_t green, uint8_t blue );

/**
 * @brief 1x4 RGB configure RGB colors function.
 * @details This function configure the desired values of RGB colors
 * for all LEDs by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] led_cfg : LEDs configuration.
 * See #c1x4rgb_led_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1x4rgb_cfg_rgb_color ( c1x4rgb_t *ctx, c1x4rgb_led_t led_cfg );

/**
 * @brief 1x4 RGB set SYNC function.
 * @details This function sets the desired logic state of the SYC (PWM) pin.
 * @param[in] ctx : Click context object.
 * See #c1x4rgb_t object definition for detailed explanation.
 * @param[in] sync : Logic state of the SYC (PWM) pin.
 * @return Nothing.
 * @note None.
 */
void c1x4rgb_set_sync ( c1x4rgb_t *ctx, uint8_t sync );

#ifdef __cplusplus
}
#endif
#endif // C1X4RGB_H

/*! @} */ // c1x4rgb

// ------------------------------------------------------------------------ END

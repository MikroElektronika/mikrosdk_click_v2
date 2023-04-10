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
 * @file ledring2.h
 * @brief This file contains API for LED Ring 2 Click Driver.
 */

#ifndef LEDRING2_H
#define LEDRING2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ledring2 LED Ring 2 Click Driver
 * @brief API for configuring and manipulating LED Ring 2 Click driver.
 * @{
 */

/**
 * @defgroup ledring2_reg LED Ring 2 Registers List
 * @brief List of registers of LED Ring 2 Click driver.
 */

/**
 * @addtogroup ledring2_reg
 * @{
 */

/**
 * @brief LED Ring 2 description register.
 * @details Specified register for description of LED Ring 2 Click driver.
 */

#define LEDRING2_REG_CHIP_EN            0x0000
#define LEDRING2_REG_DEV_INITIAL        0x0001
#define LEDRING2_REG_DEV_CONFIG1        0x0002
#define LEDRING2_REG_DEV_CONFIG2        0x0003
#define LEDRING2_REG_DEV_CONFIG3        0x0004
#define LEDRING2_REG_GLOBAL_BRI         0x0005
#define LEDRING2_REG_GROUP0_BRI         0x0006
#define LEDRING2_REG_GROUP1_BRI         0x0007
#define LEDRING2_REG_GROUP2_BRI         0x0008
#define LEDRING2_REG_R_CURRENT_SET      0x0009
#define LEDRING2_REG_G_CURRENT_SET      0x000A
#define LEDRING2_REG_B_CURRENT_SET      0x000B
#define LEDRING2_REG_DOT_GRP_SEL0       0x000C
#define LEDRING2_REG_DOT_GRP_SEL1       0x000D
#define LEDRING2_REG_DOT_GRP_SEL2       0x000E
#define LEDRING2_REG_DOT_GRP_SEL3       0x000F
#define LEDRING2_REG_DOT_GRP_SEL4       0x0010
#define LEDRING2_REG_DOT_GRP_SEL5       0x0011
#define LEDRING2_REG_DOT_GRP_SEL6       0x0012
#define LEDRING2_REG_DOT_GRP_SEL7       0x0013
#define LEDRING2_REG_DOT_GRP_SEL8       0x0014
#define LEDRING2_REG_DOT_GRP_SEL9       0x0015
#define LEDRING2_REG_DOT_ONOFF0         0x0043
#define LEDRING2_REG_DOT_ONOFF1         0x0044
#define LEDRING2_REG_DOT_ONOFF2         0x0045
#define LEDRING2_REG_DOT_ONOFF3         0x0046
#define LEDRING2_REG_DOT_ONOFF4         0x0047
#define LEDRING2_REG_DOT_ONOFF5         0x0048
#define LEDRING2_REG_FAULT_STATE        0x0064
#define LEDRING2_REG_DOT_LOD0           0x0065
#define LEDRING2_REG_DOT_LOD1           0x0066
#define LEDRING2_REG_DOT_LOD2           0x0067
#define LEDRING2_REG_DOT_LOD3           0x0068
#define LEDRING2_REG_DOT_LOD4           0x0069
#define LEDRING2_REG_DOT_LOD5           0x006A
#define LEDRING2_REG_DOT_LSD0           0x0086
#define LEDRING2_REG_DOT_LSD1           0x0087
#define LEDRING2_REG_DOT_LSD2           0x0088
#define LEDRING2_REG_DOT_LSD3           0x0089
#define LEDRING2_REG_DOT_LSD4           0x008A
#define LEDRING2_REG_DOT_LSD5           0x008B
#define LEDRING2_REG_LOD_CLEAR          0x00A7
#define LEDRING2_REG_LSD_CLEAR          0x00A8
#define LEDRING2_REG_RESET              0x00A9
#define LEDRING2_REG_DC0                0x0100
#define LEDRING2_REG_DC1                0x0101
#define LEDRING2_REG_DC2                0x0102
#define LEDRING2_REG_DC3                0x0103
#define LEDRING2_REG_DC4                0x0104
#define LEDRING2_REG_DC5                0x0105
#define LEDRING2_REG_DC6                0x0106
#define LEDRING2_REG_DC7                0x0107
#define LEDRING2_REG_DC8                0x0108
#define LEDRING2_REG_DC9                0x0109
#define LEDRING2_REG_DC10               0x010A
#define LEDRING2_REG_DC11               0x010B
#define LEDRING2_REG_DC12               0x010C
#define LEDRING2_REG_DC13               0x010D
#define LEDRING2_REG_DC14               0x010E
#define LEDRING2_REG_DC15               0x010F
#define LEDRING2_REG_DC16               0x0110
#define LEDRING2_REG_DC17               0x0111
#define LEDRING2_REG_DC18               0x0112
#define LEDRING2_REG_DC19               0x0113
#define LEDRING2_REG_DC20               0x0114
#define LEDRING2_REG_DC21               0x0115
#define LEDRING2_REG_DC22               0x0116
#define LEDRING2_REG_DC23               0x0117
#define LEDRING2_REG_DC24               0x0118
#define LEDRING2_REG_DC25               0x0119
#define LEDRING2_REG_DC26               0x011A
#define LEDRING2_REG_DC27               0x011B
#define LEDRING2_REG_DC28               0x011C
#define LEDRING2_REG_DC29               0x011D
#define LEDRING2_REG_DC30               0x011E
#define LEDRING2_REG_DC31               0x011F
#define LEDRING2_REG_DC32               0x0120
#define LEDRING2_REG_DC33               0x0121
#define LEDRING2_REG_DC34               0x0122
#define LEDRING2_REG_DC35               0x0123
#define LEDRING2_REG_PWM_BRI0           0x0200
#define LEDRING2_REG_PWM_BRI1           0x0201
#define LEDRING2_REG_PWM_BRI2           0x0202
#define LEDRING2_REG_PWM_BRI3           0x0203
#define LEDRING2_REG_PWM_BRI4           0x0204
#define LEDRING2_REG_PWM_BRI5           0x0205
#define LEDRING2_REG_PWM_BRI6           0x0206
#define LEDRING2_REG_PWM_BRI7           0x0207
#define LEDRING2_REG_PWM_BRI8           0x0208
#define LEDRING2_REG_PWM_BRI9           0x0209
#define LEDRING2_REG_PWM_BRI10          0x020A
#define LEDRING2_REG_PWM_BRI11          0x020B
#define LEDRING2_REG_PWM_BRI12          0x020C
#define LEDRING2_REG_PWM_BRI13          0x020D
#define LEDRING2_REG_PWM_BRI14          0x020E
#define LEDRING2_REG_PWM_BRI15          0x020F
#define LEDRING2_REG_PWM_BRI16          0x0210
#define LEDRING2_REG_PWM_BRI17          0x0211
#define LEDRING2_REG_PWM_BRI18          0x0212
#define LEDRING2_REG_PWM_BRI19          0x0213
#define LEDRING2_REG_PWM_BRI20          0x0214
#define LEDRING2_REG_PWM_BRI21          0x0215
#define LEDRING2_REG_PWM_BRI22          0x0216
#define LEDRING2_REG_PWM_BRI23          0x0217
#define LEDRING2_REG_PWM_BRI24          0x0218
#define LEDRING2_REG_PWM_BRI25          0x0219
#define LEDRING2_REG_PWM_BRI26          0x021A
#define LEDRING2_REG_PWM_BRI27          0x021B
#define LEDRING2_REG_PWM_BRI28          0x021C
#define LEDRING2_REG_PWM_BRI29          0x021D
#define LEDRING2_REG_PWM_BRI30          0x021E
#define LEDRING2_REG_PWM_BRI31          0x021F
#define LEDRING2_REG_PWM_BRI32          0x0220
#define LEDRING2_REG_PWM_BRI33          0x0221
#define LEDRING2_REG_PWM_BRI34          0x0222
#define LEDRING2_REG_PWM_BRI35          0x0223
#define LEDRING2_REG_PWM_BRI36          0x0224
#define LEDRING2_REG_PWM_BRI37          0x0225
#define LEDRING2_REG_PWM_BRI38          0x0226
#define LEDRING2_REG_PWM_BRI39          0x0227
#define LEDRING2_REG_PWM_BRI40          0x0228
#define LEDRING2_REG_PWM_BRI41          0x0229
#define LEDRING2_REG_PWM_BRI42          0x022A
#define LEDRING2_REG_PWM_BRI43          0x022B
#define LEDRING2_REG_PWM_BRI44          0x022C
#define LEDRING2_REG_PWM_BRI45          0x022D
#define LEDRING2_REG_PWM_BRI46          0x022E
#define LEDRING2_REG_PWM_BRI47          0x022F
#define LEDRING2_REG_PWM_BRI48          0x0230
#define LEDRING2_REG_PWM_BRI49          0x0231
#define LEDRING2_REG_PWM_BRI50          0x0232
#define LEDRING2_REG_PWM_BRI51          0x0233
#define LEDRING2_REG_PWM_BRI52          0x0234
#define LEDRING2_REG_PWM_BRI53          0x0235
#define LEDRING2_REG_PWM_BRI54          0x0236
#define LEDRING2_REG_PWM_BRI55          0x0237
#define LEDRING2_REG_PWM_BRI56          0x0238
#define LEDRING2_REG_PWM_BRI57          0x0239
#define LEDRING2_REG_PWM_BRI58          0x023A
#define LEDRING2_REG_PWM_BRI59          0x023B
#define LEDRING2_REG_PWM_BRI60          0x023C
#define LEDRING2_REG_PWM_BRI61          0x023D
#define LEDRING2_REG_PWM_BRI62          0x023E
#define LEDRING2_REG_PWM_BRI63          0x023F
#define LEDRING2_REG_PWM_BRI64          0x0240
#define LEDRING2_REG_PWM_BRI65          0x0241
#define LEDRING2_REG_PWM_BRI66          0x0242
#define LEDRING2_REG_PWM_BRI67          0x0243
#define LEDRING2_REG_PWM_BRI68          0x0244
#define LEDRING2_REG_PWM_BRI69          0x0245
#define LEDRING2_REG_PWM_BRI70          0x0246
#define LEDRING2_REG_PWM_BRI71          0x0247

/*! @} */ // ledring2_reg

/**
 * @defgroup ledring2_set LED Ring 2 Registers Settings
 * @brief Settings for registers of LED Ring 2 Click driver.
 */

/**
 * @addtogroup ledring2_set
 * @{
 */

/**
 * @brief LED Ring 2 description setting.
 * @details Specified setting for description of LED Ring 2 Click driver.
 */
#define LEDRING2_8_9_BIT_MASK             0x00003

#define LEDRING2_LED_DISABLE              0x00
#define LEDRING2_LED_ENABLE               0x01

#define LEDRING2_OP_MODE_1                0x01
#define LEDRING2_OP_MODE_2                0x02
#define LEDRING2_OP_MODE_3                0x03

/**
 * @brief LED Ring 2 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Ring 2 Click driver.
 */
#define LEDRING2_LED_GROUP_U1_LED_1_18    0x40
#define LEDRING2_LED_GROUP_U2_LED_19_36   0x44
#define LEDRING2_LED_GROUP_U3_LED_37_54   0x48

/*! @} */ // ledring2_set

/**
 * @defgroup ledring2_map LED Ring 2 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Ring 2 Click driver.
 */

/**
 * @addtogroup ledring2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Ring 2 Click to the selected MikroBUS.
 */
#define LEDRING2_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.vsy = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ledring2_map
/*! @} */ // ledring2

/**
 * @brief LED Ring 2 Click context object.
 * @details Context object definition of LED Ring 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t vsy;        /**< External synchronize signal for display mode 2 and mode 3. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} ledring2_t;

/**
 * @brief LED Ring 2 Click configuration object.
 * @details Configuration object definition of LED Ring 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t vsy;             /**< External synchronize signal for display mode 2 and mode 3. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ledring2_cfg_t;

/**
 * @brief LED Ring 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDRING2_OK = 0,
    LEDRING2_ERROR = -1

} ledring2_return_value_t;

/**
 * @brief LED Ring 2 Click LED state data.
 * @details Predefined enum values for driver LED state values.
 */
typedef enum
{
    LEDRING2_LED_OFF = 0,
    LEDRING2_LED_ON

} ledring2_led_state_t;

/*!
 * @addtogroup ledring2 LED Ring 2 Click Driver
 * @brief API for configuring and manipulating LED Ring 2 Click driver.
 * @{
 */

/**
 * @brief LED Ring 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ledring2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ledring2_cfg_setup ( ledring2_cfg_t *cfg );

/**
 * @brief LED Ring 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ledring2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_init ( ledring2_t *ctx, ledring2_cfg_t *cfg );

/**
 * @brief LED Ring 2 default configuration function.
 * @details This function executes a default configuration of LED Ring 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ledring2_default_cfg ( ledring2_t *ctx );

/**
 * @brief Set I2C Slave address.
 * @details Sets I2C address of the subordinate I2C device
 * to \p slave_address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] slave_address Specified I2C slave address:
 *         @li @c 0x40 (LEDRING2_LED_GROUP_U1_LED_1_18)  - LED1  : LED18,
 *         @li @c 0x44 (LEDRING2_LED_GROUP_U2_LED_19_36) - LED19 : LED36,
 *         @li @c 0x46 (LEDRING2_LED_GROUP_U3_LED_37_54) - LED37 : LED54.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_set_slave_address ( ledring2_t *ctx, uint8_t slave_address );

/**
 * @brief LED Ring 2 write register function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface
 * of the LP5862 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] led_group :
 *          @li @c 0x40 (LEDRING2_LED_GROUP_U1_LED_1_18)  - LED1  : LED18,
 *          @li @c 0x44 (LEDRING2_LED_GROUP_U2_LED_19_36) - LED19 : LED36,
 *          @li @c 0x46 (LEDRING2_LED_GROUP_U3_LED_37_54) - LED37 : LED54.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_write_reg ( ledring2_t *ctx, uint8_t led_group, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LED Ring 2 read registe function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface 
 * of the LP5862 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] led_group :
 *         @li @c 0x40 (LEDRING2_LED_GROUP_U1_LED_1_18)  - LED1  : LED18,
 *         @li @c 0x44 (LEDRING2_LED_GROUP_U2_LED_19_36) - LED19 : LED36,
 *         @li @c 0x46 (LEDRING2_LED_GROUP_U3_LED_37_54) - LED37 : LED54.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_read_reg ( ledring2_t *ctx, uint8_t led_group, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LED Ring 2 read registe function.
 * @details This function set synchronizes signal pulse for display mode 2 and mode 3
 * of the LP5862 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ledring2_set_vsync ( ledring2_t *ctx );

/**
 * @brief LED Ring 2 enable function.
 * @details This function enable the LP5862, 
 * 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_enable ( ledring2_t *ctx );

/**
 * @brief LED Ring 2 disable function.
 * @details This function disable the LP5862, 
 * 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_disable ( ledring2_t *ctx );

/**
 * @brief LED Ring 2 set all LED state function.
 * @details This function sets the state of all LEDs
 * of the LP5862 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] led_state : LED state.
 * See #ledring2_led_state_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_set_all_led_state ( ledring2_t *ctx, ledring2_led_state_t led_state );

/**
 * @brief LED Ring 2 set LED state function.
 * @details This function sets the desired LED state depending on the LED position selection
 * of the LP5862 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] led_pos : LED position from 1 to 54.
 * @param[in] led_state : LED state.
 * See #ledring2_led_state_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_set_led_pos_state ( ledring2_t *ctx, uint8_t led_pos, ledring2_led_state_t led_state );

/**
 * @brief LED Ring 2 set LED brightness function.
 * @details This function sets the desired LED brightness depending on the LED position selection
 * of the LP5862 2×18 LED Matrix Driver With 8-Bit Analog and 8-/16-Bit PWM Dimming
 * on the LED Ring 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #ledring2_t object definition for detailed explanation.
 * @param[in] led_pos : LED position from 1 to 54.
 * @param[in] led_brightness : LED brightness.
 * See #ledring2_led_state_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledring2_set_led_brightness ( ledring2_t *ctx, uint8_t led_pos, uint16_t led_brightness );

#ifdef __cplusplus
}
#endif
#endif // LEDRING2_H

/*! @} */ // ledring2

// ------------------------------------------------------------------------ END

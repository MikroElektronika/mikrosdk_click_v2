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
 * @file c16x12r.h
 * @brief This file contains API for 16x12 R Click Driver.
 */

#ifndef C16X12R_H
#define C16X12R_H

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
 * @addtogroup c16x12r 16x12 R Click Driver
 * @brief API for configuring and manipulating 16x12 R Click driver.
 * @{
 */

/**
 * @defgroup c16x12r_reg 16x12 R Registers List
 * @brief List of registers of 16x12 R Click driver.
 */

/**
 * @addtogroup c16x12r_reg
 * @{
 */

/**
 * @brief 16x12 R register list 1.
 * @details Specified register list 1 of 16x12 R Click driver.
 */
#define C16X12R_REG_PAGE_SELECT                 0xFD
#define C16X12R_REG_PAGE_LOCK                   0xFE
#define C16X12R_REG_INT_MASK                    0xF0
#define C16X12R_REG_INT_STATUS                  0xF1

/**
 * @brief 16x12 R register list 2.
 * @details Specified register list 2 of 16x12 R Click driver.
 */
#define C16X12R_PAGE_REG_LED_ON_OFF             0x0000
#define C16X12R_PAGE_REG_LED_OPEN               0x0018
#define C16X12R_PAGE_REG_LED_SHORT              0x0030
#define C16X12R_PAGE_REG_PWM                    0x0100
#define C16X12R_PAGE_REG_MODE                   0x0200
#define C16X12R_PAGE_REG_CONFIG                 0x0300
#define C16X12R_PAGE_REG_GLOBAL_CURRENT_CTRL    0x0301
#define C16X12R_PAGE_REG_BREATH_ABM1_CTRL1      0x0302
#define C16X12R_PAGE_REG_BREATH_ABM1_CTRL2      0x0303
#define C16X12R_PAGE_REG_BREATH_ABM1_CTRL3      0x0304
#define C16X12R_PAGE_REG_BREATH_ABM1_CTRL4      0x0305
#define C16X12R_PAGE_REG_BREATH_ABM2_CTRL1      0x0306
#define C16X12R_PAGE_REG_BREATH_ABM2_CTRL2      0x0307
#define C16X12R_PAGE_REG_BREATH_ABM2_CTRL3      0x0308
#define C16X12R_PAGE_REG_BREATH_ABM2_CTRL4      0x0309
#define C16X12R_PAGE_REG_BREATH_ABM3_CTRL1      0x030A
#define C16X12R_PAGE_REG_BREATH_ABM3_CTRL2      0x030B
#define C16X12R_PAGE_REG_BREATH_ABM3_CTRL3      0x030C
#define C16X12R_PAGE_REG_BREATH_ABM3_CTRL4      0x030D
#define C16X12R_PAGE_REG_TIME_UPDATE            0x030E
#define C16X12R_PAGE_REG_SWY_PULLUP_SELECT      0x030F
#define C16X12R_PAGE_REG_CSX_PULLDOWN_SELECT    0x0310
#define C16X12R_PAGE_REG_RESET                  0x0311

/*! @} */ // c16x12r_reg

/**
 * @defgroup c16x12r_set 16x12 R Registers Settings
 * @brief Settings for registers of 16x12 R Click driver.
 */

/**
 * @addtogroup c16x12r_set
 * @{
 */

/**
 * @brief 16x12 R page select setting.
 * @details Specified setting for page select of 16x12 R Click driver.
 */
#define C16X12R_PAGE_SELECT_0                   0x00
#define C16X12R_PAGE_SELECT_1                   0x01
#define C16X12R_PAGE_SELECT_2                   0x02
#define C16X12R_PAGE_SELECT_3                   0x03

/**
 * @brief 16x12 R page lock setting.
 * @details Specified setting for page lock of 16x12 R Click driver.
 */
#define C16X12R_PAGE_LOCK                       0x00
#define C16X12R_PAGE_UNLOCK                     0xC5

/**
 * @brief 16x12 R LED mode setting.
 * @details Specified setting for LED mode of 16x12 R Click driver.
 */
#define C16X12R_MODE_PWM                        0x00
#define C16X12R_MODE_ABM1                       0x01
#define C16X12R_MODE_ABM2                       0x02
#define C16X12R_MODE_ABM3                       0x03

/**
 * @brief 16x12 R config page register setting.
 * @details Specified setting for config page register of 16x12 R Click driver.
 */
#define C16X12R_CONFIG_SYNC_HIGH_Z              0x00
#define C16X12R_CONFIG_SYNC_MASTER              0x40
#define C16X12R_CONFIG_SYNC_SLAVE               0x80
#define C16X12R_CONFIG_SYNC_MASK                0xC0
#define C16X12R_CONFIG_OSD_DIS                  0x00
#define C16X12R_CONFIG_OSD_EN                   0x04
#define C16X12R_CONFIG_OSD_MASK                 0x04
#define C16X12R_CONFIG_B_EN_PWM                 0x00
#define C16X12R_CONFIG_B_EN_ABM                 0x02
#define C16X12R_CONFIG_B_EN_MASK                0x02
#define C16X12R_CONFIG_SSD_SHUTDOWN             0x00
#define C16X12R_CONFIG_SSD_NORMAL               0x01
#define C16X12R_CONFIG_SSD_MASK                 0x01

/**
 * @brief 16x12 R global current ctrl page register setting.
 * @details Specified setting for global current ctrl page register of 16x12 R Click driver.
 */
#define C16X12R_CURRENT_MIN                     0x00
#define C16X12R_CURRENT_DEFAULT                 0xA0
#define C16X12R_CURRENT_MAX                     0xFF

/**
 * @brief 16x12 R PWM page register setting.
 * @details Specified setting for PWM page register of 16x12 R Click driver.
 */
#define C16X12R_PWM_DUTY_MIN                    0x00
#define C16X12R_PWM_DUTY_DEFAULT                0xA0
#define C16X12R_PWM_DUTY_MAX                    0xFF

/**
 * @brief 16x12 R LED state setting.
 * @details Specified setting for LED state of 16x12 R Click driver.
 */
#define C16X12R_LED_STATE_OFF                   0
#define C16X12R_LED_STATE_ON                    1

/**
 * @brief 16x12 R LED selection setting.
 * @details Specified setting for LED selection of 16x12 R Click driver.
 */
#define C16X12R_NUM_LEDS                        192
#define C16X12R_NUM_ROWS                        16
#define C16X12R_NUM_COLUMNS                     12

/**
 * @brief 16x12 R text ASCII byte rotation.
 * @details Specified text ASCII byte rotation of 16x12 R Click driver.
 */
#define C16X12R_ROTATION_V_0                    0x00
#define C16X12R_ROTATION_V_180                  0x01
#define C16X12R_ROTATION_H_0                    0x10
#define C16X12R_ROTATION_H_180                  0x11

/**
 * @brief 16x12 R device address setting.
 * @details Specified setting for device slave address selection of
 * 16x12 R Click driver.
 */
#define C16X12R_DEVICE_ADDRESS_A2A1_00          0x50
#define C16X12R_DEVICE_ADDRESS_A2A1_01          0x53
#define C16X12R_DEVICE_ADDRESS_A2A1_10          0x5C
#define C16X12R_DEVICE_ADDRESS_A2A1_11          0x5F

/*! @} */ // c16x12r_set

/**
 * @defgroup c16x12r_map 16x12 R MikroBUS Map
 * @brief MikroBUS pin mapping of 16x12 R Click driver.
 */

/**
 * @addtogroup c16x12r_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 16x12 R Click to the selected MikroBUS.
 */
#define C16X12R_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sdb = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.intb = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c16x12r_map
/*! @} */ // c16x12r

/**
 * @brief 16x12 R Click context object.
 * @details Context object definition of 16x12 R Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sdb;          /**< Chip shutdown pin (active low). */
    digital_out_t rst;          /**< I2C reset pin (active low). */

    // Input pins
    digital_in_t intb;          /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t leds[ C16X12R_NUM_COLUMNS * C16X12R_NUM_ROWS / 8 ];     /**< LEDs array. */

    uint8_t text_rotation;      /**< ASCII byte rotation. */

} c16x12r_t;

/**
 * @brief 16x12 R Click configuration object.
 * @details Configuration object definition of 16x12 R Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sdb;             /**< Chip shutdown pin (active low). */
    pin_name_t rst;             /**< I2C reset pin (active low). */
    pin_name_t intb;            /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} c16x12r_cfg_t;

/**
 * @brief 16x12 R Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C16X12R_OK = 0,
    C16X12R_ERROR = -1

} c16x12r_return_value_t;

/*!
 * @addtogroup c16x12r 16x12 R Click Driver
 * @brief API for configuring and manipulating 16x12 R Click driver.
 * @{
 */

/**
 * @brief 16x12 R configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c16x12r_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c16x12r_cfg_setup ( c16x12r_cfg_t *cfg );

/**
 * @brief 16x12 R initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c16x12r_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c16x12r_init ( c16x12r_t *ctx, c16x12r_cfg_t *cfg );

/**
 * @brief 16x12 R default configuration function.
 * @details This function executes a default configuration of 16x12 R
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c16x12r_default_cfg ( c16x12r_t *ctx );

/**
 * @brief 16x12 R write register function.
 * @details This function writes a single byte to the selected register using I2C communication.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_reg ( c16x12r_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 16x12 R write registers function.
 * @details This function writes multiple bytes starting from the selected register using I2C communication.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] reg : Starting register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_regs ( c16x12r_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 16x12 R read register function.
 * @details This function reads a single byte from the selected register using I2C communication.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_read_reg ( c16x12r_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 16x12 R read registers function.
 * @details This function reads multiple bytes starting from the selected register using I2C communication.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] reg : Starting register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_read_regs ( c16x12r_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 16x12 R enable device function.
 * @details This function sets the SDB pin high to enable the device.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c16x12r_enable_device ( c16x12r_t *ctx );

/**
 * @brief 16x12 R disable device function.
 * @details This function sets the SDB pin low to disable the device.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c16x12r_disable_device ( c16x12r_t *ctx );

/**
 * @brief 16x12 R reset device I2C function.
 * @details This function toggles the RST pin to perform an I2C reset.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c16x12r_reset_device_i2c ( c16x12r_t *ctx );

/**
 * @brief 16x12 R set reset pin state function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] state : Pin state (0 or 1).
 * @return None.
 * @note None.
 */
void c16x12r_set_rst_pin ( c16x12r_t *ctx, uint8_t state );

/**
 * @brief 16x12 R get interrupt pin function.
 * @details This function reads the logic state of the INTB pin.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return Pin state (0 or 1).
 * @note None.
 */
uint8_t c16x12r_get_intb_pin ( c16x12r_t *ctx );

/**
 * @brief 16x12 R lock page function.
 * @details This function locks the page to prevent further configuration.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_lock_page ( c16x12r_t *ctx );

/**
 * @brief 16x12 R unlock page function.
 * @details This function unlocks the page to allow configuration.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_unlock_page ( c16x12r_t *ctx );

/**
 * @brief 16x12 R select page function.
 * @details This function selects the target page for register access.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] page : Page number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_select_page ( c16x12r_t *ctx, uint8_t page );

/**
 * @brief 16x12 R write page register function.
 * @details This function writes a byte to a register on a selected page.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] page_reg : Combined page and register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_page_reg ( c16x12r_t *ctx, uint16_t page_reg, uint8_t data_in );

/**
 * @brief 16x12 R write page registers function.
 * @details This function writes multiple bytes to a register range on a selected page.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] page_reg : Combined page and register address.
 * @param[in] data_in : Data buffer to write.
 * @param[in] len : Number of bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_page_regs ( c16x12r_t *ctx, uint16_t page_reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 16x12 R read page register function.
 * @details This function reads a byte from a register on a selected page.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] page_reg : Combined page and register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_read_page_reg ( c16x12r_t *ctx, uint16_t page_reg, uint8_t *data_out );

/**
 * @brief 16x12 R read page registers function.
 * @details This function reads multiple bytes from a register range on a selected page.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] page_reg : Combined page and register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_read_page_regs ( c16x12r_t *ctx, uint16_t page_reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 16x12 R fill screen function.
 * @details This function turns on all LEDs on the screen.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_fill_screen ( c16x12r_t *ctx );

/**
 * @brief 16x12 R clear screen function.
 * @details This function turns off all LEDs on the screen.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_clear_screen ( c16x12r_t *ctx );

/**
 * @brief 16x12 R set PWM function.
 * @details This function sets the same PWM duty cycle to all LEDs.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] duty : PWM duty cycle (0?255).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_set_pwm ( c16x12r_t *ctx, uint8_t duty );

/**
 * @brief 16x12 R set mode function.
 * @details This function sets the blinking mode for all LEDs.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] mode : Blinking mode (0?3).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_set_mode ( c16x12r_t *ctx, uint8_t mode );

/**
 * @brief 16x12 R set LED state function.
 * @details This function sets a single LED state to ON or OFF.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] led_num : LED index (0?191).
 * @param[in] state : LED state (0=OFF, 1=ON).
 * @return None.
 * @note None.
 */
void c16x12r_set_led_state ( c16x12r_t *ctx, uint8_t led_num, uint8_t state );

/**
 * @brief 16x12 R write LEDs function.
 * @details This function writes the local LED state buffer to the display.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_leds ( c16x12r_t *ctx );

/**
 * @brief 16x12 R draw picture function.
 * @details This function draws a picture on the display from a 12-column buffer.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] image : Pointer to 12x16 image array.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_draw_picture ( c16x12r_t *ctx, const uint16_t *image );

/**
 * @brief 16x12 R write character function.
 * @details This function writes a single ASCII character to the display.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] data_in : ASCII character to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_char ( c16x12r_t *ctx, uint8_t data_in );

/**
 * @brief 16x12 R write string function.
 * @details This function scrolls a null-terminated ASCII string across the display.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to string to display.
 * @param[in] speed_ms : Scrolling delay in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c16x12r_write_string ( c16x12r_t *ctx, uint8_t *data_in, uint16_t speed_ms );

#ifdef __cplusplus
}
#endif
#endif // C16X12R_H

/*! @} */ // c16x12r

// ------------------------------------------------------------------------ END

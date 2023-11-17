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
 * @file c2x2rgb.h
 * @brief This file contains API for 2x2 RGB Click Driver.
 */

#ifndef C2X2RGB_H
#define C2X2RGB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup c2x2rgb 2x2 RGB Click Driver
 * @brief API for configuring and manipulating 2x2 RGB Click driver.
 * @{
 */

/**
 * @defgroup c2x2rgb_reg 2x2 RGB Registers List
 * @brief List of registers of 2x2 RGB Click driver.
 */

/**
 * @addtogroup c2x2rgb_reg
 * @{
 */

/**
 * @brief 2x2 RGB description register.
 * @details Specified register for description of 2x2 RGB Click driver.
 */
#define C2X2RGB_REG_ID                0x00
#define C2X2RGB_REG_MONITOR           0x01
#define C2X2RGB_REG_CONTROL           0x02
#define C2X2RGB_REG_IRED1             0x03
#define C2X2RGB_REG_IGRN1             0x04
#define C2X2RGB_REG_IBLU1             0x05
#define C2X2RGB_REG_IRED2             0x06
#define C2X2RGB_REG_IGRN2             0x07
#define C2X2RGB_REG_IBLU2             0x08
#define C2X2RGB_REG_IRED3             0x09
#define C2X2RGB_REG_IGRN3             0x0A
#define C2X2RGB_REG_IBLU3             0x0B
#define C2X2RGB_REG_IRED4             0x0C
#define C2X2RGB_REG_IGRN4             0x0D
#define C2X2RGB_REG_IBLU4             0x0E
#define C2X2RGB_REG_PG_CNTL           0x0F
#define C2X2RGB_REG_PG_FADE           0x10
#define C2X2RGB_REG_PG_RGB1           0x11
#define C2X2RGB_REG_PG_RGB2           0x12
#define C2X2RGB_REG_PG_RGB3           0x13
#define C2X2RGB_REG_PG_RGB4           0x14
#define C2X2RGB_REG_PG_WD             0x15

/*! @} */ // c2x2rgb_reg

/**
 * @defgroup c2x2rgb_set 2x2 RGB Registers Settings
 * @brief Settings for registers of 2x2 RGB Click driver.
 */

/**
 * @addtogroup c2x2rgb_set
 * @{
 */

/**
 * @brief 2x2 RGB LED selection data values.
 * @details Specified LED selection of 2x2 RGB Click driver.
 */
#define C2X2RGB_SET_LD1               1
#define C2X2RGB_SET_LD2               2
#define C2X2RGB_SET_LD3               3
#define C2X2RGB_SET_LD4               4

/**
 * @brief 2x2 RGB device ID data values.
 * @details Specified device ID data values of 2x2 RGB Click driver.
 */
#define C2X2RGB_DEV_ID                0x06
#define C2X2RGB_DEV_ID_BIT_MASK       0x0F
#define C2X2RGB_VEN_ID                0x05
#define C2X2RGB_VEN_ID_BIT_MASK       0x07

/**
 * @brief 2x2 RGB device ID data values.
 * @details Specified device ID data values of 2x2 RGB Click driver.
 */
#define C2X2RGB_MONITOR_UV_OT_STAT    0x01
#define C2X2RGB_MONITOR_COOL_STAT     0x02
#define C2X2RGB_MONITOR_BE_STAT       0x04
#define C2X2RGB_MONITOR_SC_STAT       0x08

/**
 * @brief 2x2 RGB LED current setting data values.
 * @details Specified LED current setting data values of 2x2 RGB Click driver.
 */
#define C2X2RGB_LED_CURRENT_OFF       0
#define C2X2RGB_LED_CURRENT_3MA       3000
#define C2X2RGB_LED_CURRENT_MAX       24000
#define C2X2RGB_LED_CURRENT_STEP      125


/**
 * @brief 2x2 RGB control configuration data values.
 * @details Specified control configuration of 2x2 RGB Click driver.
 */
#define C2X2RGB_EN_MODE_SHUTDOWN       0x00
#define C2X2RGB_EN_MODE_NIGHT          0x01
#define C2X2RGB_EN_MODE_NORMAL         0x02
#define C2X2RGB_EN_MODE_SW_RESET       0x03
#define C2X2RGB_EN_MODE_BIT_MASK       0xC0
#define C2X2RGB_BE_DISABLE             0x00
#define C2X2RGB_BE_ENABLE              0x01
#define C2X2RGB_BE_BIT_MASK            0x20
#define C2X2RGB_CE_TEMP_135C           0x00
#define C2X2RGB_CE_TEMP_120C           0x01
#define C2X2RGB_CE_TEMP_105C           0x02
#define C2X2RGB_CE_TEMP_90C            0x03
#define C2X2RGB_CE_TEMP_BIT_MASK       0x18
#define C2X2RGB_FADE_RATE0_32_MS       0x00
#define C2X2RGB_FADE_RATE0_63_MS       0x01
#define C2X2RGB_FADE_RATE0_125_MS      0x02
#define C2X2RGB_FADE_RATE0_250_MS      0x03
#define C2X2RGB_FADE_RATE0_500_MS      0x04
#define C2X2RGB_FADE_RATE0_1_S         0x05
#define C2X2RGB_FADE_RATE0_2_S         0x06
#define C2X2RGB_FADE_RATE0_4_S         0x07
#define C2X2RGB_FADE_RATE0_BIT_MASK    0x07

/**
 * @brief 2x2 RGB pattern configuration data values.
 * @details Specified pattern configuration of 2x2 RGB Click driver.
 */
#define C2X2RGB_PG_MODE_OFF            0x00
#define C2X2RGB_PG_MODE_4P_EN          0x01
#define C2X2RGB_PG_MODE_6P_EN          0x02
#define C2X2RGB_PG_MODE_8P_EN          0x03
#define C2X2RGB_PG_MODE_BIT_MASK       0xC0
#define C2X2RGB_PG_TIME_188_MS         0x00
#define C2X2RGB_PG_TIME_2_S            0x0F
#define C2X2RGB_PG_TIME_BIT_MASK       0x3C

#define C2X2RGB_FADE_RATE1_32_MS       0x00
#define C2X2RGB_FADE_RATE1_4_S         0x07
#define C2X2RGB_FADE_RATE1_BIT_MASK    0x07


/**
 * @brief 2x2 RGB device address setting.
 * @details Specified setting for device slave address selection of
 * 2x2 RGB Click driver.
 */
#define C2X2RGB_DEVICE_ADDRESS        0x74

/*! @} */ // c2x2rgb_set

/**
 * @defgroup c2x2rgb_map 2x2 RGB MikroBUS Map
 * @brief MikroBUS pin mapping of 2x2 RGB Click driver.
 */

/**
 * @addtogroup c2x2rgb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 2x2 RGB Click to the selected MikroBUS.
 */
#define C2X2RGB_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // c2x2rgb_map
/*! @} */ // c2x2rgb

/**
 * @brief 2x2 RGB Click context object.
 * @details Context object definition of 2x2 RGB Click driver.
 */
typedef struct
{

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} c2x2rgb_t;

/**
 * @brief 2x2 RGB Click configuration object.
 * @details Configuration object definition of 2x2 RGB Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} c2x2rgb_cfg_t;

/**
 * @brief 2x2 RGB Click LED current setting object.
 * @details LED current setting of 2x2 RGB Click driver.
 */
typedef struct
{
    uint8_t en_mode;     /**< Enable Mode. */
    uint16_t led1_ired;  /**< Red Current Setting for RGB1. */
    uint16_t led1_igrn;  /**< Green Current Setting for RGB1. */
    uint16_t led1_iblu;  /**< Blue Current Setting for RGB1. */
    uint16_t led2_ired;  /**< Red Current Setting for RGB2. */
    uint16_t led2_igrn;  /**< Green Current Setting for RGB2. */
    uint16_t led2_iblu;  /**< Blue Current Setting for RGB2. */
    uint16_t led3_ired;  /**< Red Current Setting for RGB3. */
    uint16_t led3_igrn;  /**< Green Current Setting for RGB3. */
    uint16_t led3_iblu;  /**< Blue Current Setting for RGB3. */
    uint16_t led4_ired;  /**< Red Current Setting for RGB4. */
    uint16_t led4_igrn;  /**< Green Current Setting for RGB4. */
    uint16_t led4_iblu;  /**< Blue Current Setting for RGB4. */

} c2x2rgb_rgb_led_t;

/**
 * @brief 2x2 RGB Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C2X2RGB_OK = 0,
    C2X2RGB_ERROR = -1

} c2x2rgb_return_value_t;

/*!
 * @addtogroup c2x2rgb 2x2 RGB Click Driver
 * @brief API for configuring and manipulating 2x2 RGB Click driver.
 * @{
 */

/**
 * @brief 2x2 RGB configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c2x2rgb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c2x2rgb_cfg_setup ( c2x2rgb_cfg_t *cfg );

/**
 * @brief 2x2 RGB initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c2x2rgb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_init ( c2x2rgb_t *ctx, c2x2rgb_cfg_t *cfg );

/**
 * @brief 2x2 RGB default configuration function.
 * @details This function executes a default configuration of 2x2 RGB
 * click board.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c2x2rgb_default_cfg ( c2x2rgb_t *ctx );

/**
 * @brief 2x2 RGB I2C writing function.
 * @details This function writes a data bytes to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_generic_write ( c2x2rgb_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 2x2 RGB I2C reading function.
 * @details This function reads a data bytes from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_generic_read ( c2x2rgb_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 2x2 RGB get device ID function.
 * @details This function reads vendor ID and device ID by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] vendor_id : Vendor ID.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_get_device_id ( c2x2rgb_t *ctx, uint8_t *vendor_id, uint8_t *device_id );

/**
 * @brief 2x2 RGB get monitor status function.
 * @details This function reads monitor status by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[out] sc_stat : Short-Circuit Protection Status.
 * @param[out] be_stat : BrightExtend™ Dropout Status.
 * @param[out] cool_stat : CoolExtend™ Die Temperature Status.
 * @param[out] uv_ot_stat : VIN Under-Voltage Lockout or Over Temperature Shutdown Status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_get_monitor_status ( c2x2rgb_t *ctx, uint8_t *sc_stat, uint8_t *be_stat, 
                                                   uint8_t *cool_stat, uint8_t *uv_ot_stat );

/**
 * @brief 2x2 RGB set control function.
 * @details This function sets control by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] en_mode : Enable Mode and Reset.
 * @param[in] be_en : BrightExtend™ Enable.
 * @param[in] ce_temp : CoolExtend™ Temperature Setting.
 * @param[in] fade_rate : Fade-Rate 0 Exponential Time-Constant Setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_control ( c2x2rgb_t *ctx, uint8_t en_mode, uint8_t be_en, 
                                            uint8_t ce_temp, uint8_t fade_rate );

/**
 * @brief 2x2 RGB set normal mode function.
 * @details This function sets normal mode by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_normal_mode ( c2x2rgb_t *ctx );

/**
 * @brief 2x2 RGB set soft reset function.
 * @details This function performs the software reset of the device.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_sw_reset ( c2x2rgb_t *ctx );

/**
 * @brief 2x2 RGB set RGB LED function.
 * @details This function sets RGB LED data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] led_num : LED selectino [1-4].
 * @param[in] ired : Red Current Setting for RGB.
 * @param[in] igrn : Green Current Setting for RGB.
 * @param[in] iblu : Blue Current Setting for RGB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_rgb_led ( c2x2rgb_t *ctx, uint8_t led_num, uint16_t ired, uint16_t igrn, uint16_t iblu );

/**
 * @brief 2x2 RGB set all RGB LED function.
 * @details This function sets all RGB LED data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] cfg_rgb_led : LED current setting object.
 * See #c2x2rgb_rgb_led_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_all_rgb_led ( c2x2rgb_t *ctx, c2x2rgb_rgb_led_t cfg_rgb_led );

/**
 * @brief 2x2 RGB set PG control function.
 * @details This function sets PG control by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] pg_mode : Pattern Generator Enable and Mode.
 * @param[in] pg_time : Pattern-Slot Duration.
 * @param[in] fade_rate : Fade-Rate 1 Exponential Time-Constant Setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_pg_ctrl ( c2x2rgb_t *ctx, uint8_t pg_mode, uint8_t pg_time, uint8_t fade_rate );

/**
 * @brief 2x2 RGB set PG fade function.
 * @details This function sets PG fade by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] pg_fade : Pattern-Slot.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_pg_fade ( c2x2rgb_t *ctx, uint8_t pg_fade );

/**
 * @brief 2x2 RGB set PG fade function.
 * @details This function sets PG fade by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] led_num : LED selectino [1-4].
 * @param[in] pg_rgb : Pattern-Slot 7 RGB On/Off Selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_pg_rgb ( c2x2rgb_t *ctx, uint8_t led_num, uint8_t pg_rgb );

/**
 * @brief 2x2 RGB set pattern watchdog counter function.
 * @details This function sets pattern watchdog counter by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c2x2rgb_t object definition for detailed explanation.
 * @param[in] wd_pcr : pattern watchdog counter.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x2rgb_set_pg_wd ( c2x2rgb_t *ctx, uint8_t wd_pcr );

#ifdef __cplusplus
}
#endif
#endif // C2X2RGB_H

/*! @} */ // c2x2rgb

// ------------------------------------------------------------------------ END

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
 * @file leddriver16.h
 * @brief This file contains API for LED Driver 16 Click Driver.
 */

#ifndef LEDDRIVER16_H
#define LEDDRIVER16_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup leddriver16 LED Driver 16 Click Driver
 * @brief API for configuring and manipulating LED Driver 16 Click driver.
 * @{
 */

/**
 * @defgroup leddriver16_reg LED Driver 16 Registers List
 * @brief List of registers of LED Driver 16 Click driver.
 */

/**
 * @addtogroup leddriver16_reg
 * @{
 */

/**
 * @brief LED Driver 16 registers list.
 * @details Specified registers list of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_REG_MODE1               0x00
#define LEDDRIVER16_REG_MODE2               0x01
#define LEDDRIVER16_REG_LEDOUT0             0x02
#define LEDDRIVER16_REG_LEDOUT1             0x03
#define LEDDRIVER16_REG_LEDOUT2             0x04
#define LEDDRIVER16_REG_LEDOUT3             0x05
#define LEDDRIVER16_REG_GRPPWM              0x06
#define LEDDRIVER16_REG_GRPFREQ             0x07
#define LEDDRIVER16_REG_PWM0                0x08
#define LEDDRIVER16_REG_PWM1                0x09
#define LEDDRIVER16_REG_PWM2                0x0A
#define LEDDRIVER16_REG_PWM3                0x0B
#define LEDDRIVER16_REG_PWM4                0x0C
#define LEDDRIVER16_REG_PWM5                0x0D
#define LEDDRIVER16_REG_PWM6                0x0E
#define LEDDRIVER16_REG_PWM7                0x0F
#define LEDDRIVER16_REG_PWM8                0x10
#define LEDDRIVER16_REG_PWM9                0x11
#define LEDDRIVER16_REG_PWM10               0x12
#define LEDDRIVER16_REG_PWM11               0x13
#define LEDDRIVER16_REG_PWM12               0x14
#define LEDDRIVER16_REG_PWM13               0x15
#define LEDDRIVER16_REG_PWM14               0x16
#define LEDDRIVER16_REG_PWM15               0x17
#define LEDDRIVER16_REG_IREF0               0x18
#define LEDDRIVER16_REG_IREF1               0x19
#define LEDDRIVER16_REG_IREF2               0x1A
#define LEDDRIVER16_REG_IREF3               0x1B
#define LEDDRIVER16_REG_IREF4               0x1C
#define LEDDRIVER16_REG_IREF5               0x1D
#define LEDDRIVER16_REG_IREF6               0x1E
#define LEDDRIVER16_REG_IREF7               0x1F
#define LEDDRIVER16_REG_IREF8               0x20
#define LEDDRIVER16_REG_IREF9               0x21
#define LEDDRIVER16_REG_IREF10              0x22
#define LEDDRIVER16_REG_IREF11              0x23
#define LEDDRIVER16_REG_IREF12              0x24
#define LEDDRIVER16_REG_IREF13              0x25
#define LEDDRIVER16_REG_IREF14              0x26
#define LEDDRIVER16_REG_IREF15              0x27
#define LEDDRIVER16_REG_RAMP_RATE_GRP0      0x28
#define LEDDRIVER16_REG_STEP_TIME_GRP0      0x29
#define LEDDRIVER16_REG_HOLD_CNTL_GRP0      0x2A
#define LEDDRIVER16_REG_IREF_GRP0           0x2B
#define LEDDRIVER16_REG_RAMP_RATE_GRP1      0x2C
#define LEDDRIVER16_REG_STEP_TIME_GRP1      0x2D
#define LEDDRIVER16_REG_HOLD_CNTL_GRP1      0x2E
#define LEDDRIVER16_REG_IREF_GRP1           0x2F
#define LEDDRIVER16_REG_RAMP_RATE_GRP2      0x30
#define LEDDRIVER16_REG_STEP_TIME_GRP2      0x31
#define LEDDRIVER16_REG_HOLD_CNTL_GRP2      0x32
#define LEDDRIVER16_REG_IREF_GRP2           0x33
#define LEDDRIVER16_REG_RAMP_RATE_GRP3      0x34
#define LEDDRIVER16_REG_STEP_TIME_GRP3      0x35
#define LEDDRIVER16_REG_HOLD_CNTL_GRP3      0x36
#define LEDDRIVER16_REG_IREF_GRP3           0x37
#define LEDDRIVER16_REG_GRAD_MODE_SEL0      0x38
#define LEDDRIVER16_REG_GRAD_MODE_SEL1      0x39
#define LEDDRIVER16_REG_GRAD_GRP_SEL0       0x3A
#define LEDDRIVER16_REG_GRAD_GRP_SEL1       0x3B
#define LEDDRIVER16_REG_GRAD_GRP_SEL2       0x3C
#define LEDDRIVER16_REG_GRAD_GRP_SEL3       0x3D
#define LEDDRIVER16_REG_GRAD_CNTL           0x3E
#define LEDDRIVER16_REG_OFFSET              0x3F
#define LEDDRIVER16_REG_PWMALL              0x40
#define LEDDRIVER16_REG_IREFALL             0x41
#define LEDDRIVER16_REG_EFLAG0              0x42
#define LEDDRIVER16_REG_EFLAG1              0x43
#define LEDDRIVER16_REG_EFLAG2              0x44
#define LEDDRIVER16_REG_EFLAG3              0x45

/*! @} */ // leddriver16_reg

/**
 * @defgroup leddriver16_set LED Driver 16 Registers Settings
 * @brief Settings for registers of LED Driver 16 Click driver.
 */

/**
 * @addtogroup leddriver16_set
 * @{
 */

/**
 * @brief LED Driver 16 MODE1 register setting.
 * @details Specified setting for MODE1 register of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_MODE1_NORMAL_MODE       0x00
#define LEDDRIVER16_MODE1_LOW_POWER_MODE    0x10

/**
 * @brief LED Driver 16 MODE2 register setting.
 * @details Specified setting for MODE2 register of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_MODE2_OVERTEMP          0x80
#define LEDDRIVER16_MODE2_ERROR             0x40
#define LEDDRIVER16_MODE2_DMBLNK            0x20
#define LEDDRIVER16_MODE2_CLRERR            0x10
#define LEDDRIVER16_MODE2_EXP_EN            0x04

/**
 * @brief LED Driver 16 LEDOUTx register setting.
 * @details Specified setting for LEDOUTx register of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_LEDOUT_OFF              0x00
#define LEDDRIVER16_LEDOUT_ON               0x01
#define LEDDRIVER16_LEDOUT_PWM_ALL          0x02
#define LEDDRIVER16_LEDOUT_PWM_GRPPWM       0x03
#define LEDDRIVER16_LEDOUT_MASK             0x03

/**
 * @brief LED Driver 16 PWMx register setting.
 * @details Specified setting for PWMx register of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_PWM_DUTY_MIN            0x00
#define LEDDRIVER16_PWM_DUTY_MAX            0xFF

/**
 * @brief LED Driver 16 IREFx register setting.
 * @details Specified setting for IREFx register of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_IREF_MIN                0x00
#define LEDDRIVER16_IREF_MAX                0xFF

/**
 * @brief LED Driver 16 LED channel setting.
 * @details Specified setting for LED channel of LED Driver 16 Click driver.
 */
#define LEDDRIVER16_LED_CHANNEL_0           0x0001u
#define LEDDRIVER16_LED_CHANNEL_1           0x0002u
#define LEDDRIVER16_LED_CHANNEL_2           0x0004u
#define LEDDRIVER16_LED_CHANNEL_3           0x0008u
#define LEDDRIVER16_LED_CHANNEL_4           0x0010u
#define LEDDRIVER16_LED_CHANNEL_5           0x0020u
#define LEDDRIVER16_LED_CHANNEL_6           0x0040u
#define LEDDRIVER16_LED_CHANNEL_7           0x0080u
#define LEDDRIVER16_LED_CHANNEL_8           0x0100u
#define LEDDRIVER16_LED_CHANNEL_9           0x0200u
#define LEDDRIVER16_LED_CHANNEL_10          0x0400u
#define LEDDRIVER16_LED_CHANNEL_11          0x0800u
#define LEDDRIVER16_LED_CHANNEL_12          0x1000u
#define LEDDRIVER16_LED_CHANNEL_13          0x2000u
#define LEDDRIVER16_LED_CHANNEL_14          0x4000u
#define LEDDRIVER16_LED_CHANNEL_15          0x8000u
#define LEDDRIVER16_LED_CHANNEL_GRP0        0x000Fu
#define LEDDRIVER16_LED_CHANNEL_GRP1        0x00F0u
#define LEDDRIVER16_LED_CHANNEL_GRP2        0x0F00u
#define LEDDRIVER16_LED_CHANNEL_GRP3        0xF000u
#define LEDDRIVER16_LED_CHANNEL_ALL         0xFFFFu

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b leddriver16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LEDDRIVER16_SET_DATA_SAMPLE_EDGE    SET_SPI_DATA_SAMPLE_EDGE
#define LEDDRIVER16_SET_DATA_SAMPLE_MIDDLE  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // leddriver16_set

/**
 * @defgroup leddriver16_map LED Driver 16 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 16 Click driver.
 */

/**
 * @addtogroup leddriver16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 16 Click to the selected MikroBUS.
 */
#define LEDDRIVER16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.oe   = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // leddriver16_map
/*! @} */ // leddriver16

/**
 * @brief LED Driver 16 Click context object.
 * @details Context object definition of LED Driver 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active Low). */
    digital_out_t oe;           /**< Output enable pin (Active Low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} leddriver16_t;

/**
 * @brief LED Driver 16 Click configuration object.
 * @details Configuration object definition of LED Driver 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (Active Low). */
    pin_name_t oe;              /**< Output enable pin (Active Low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} leddriver16_cfg_t;

/**
 * @brief LED Driver 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER16_OK = 0,
    LEDDRIVER16_ERROR = -1

} leddriver16_return_value_t;

/*!
 * @addtogroup leddriver16 LED Driver 16 Click Driver
 * @brief API for configuring and manipulating LED Driver 16 Click driver.
 * @{
 */

/**
 * @brief LED Driver 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver16_cfg_setup ( leddriver16_cfg_t *cfg );

/**
 * @brief LED Driver 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver16_init ( leddriver16_t *ctx, leddriver16_cfg_t *cfg );

/**
 * @brief LED Driver 16 default configuration function.
 * @details This function executes a default configuration of LED Driver 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver16_default_cfg ( leddriver16_t *ctx );

/**
 * @brief LED Driver 16 write register function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver16_write_register ( leddriver16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LED Driver 16 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver16_read_register ( leddriver16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LED Driver 16 disable device function.
 * @details This function disables device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void leddriver16_disable_device ( leddriver16_t *ctx );

/**
 * @brief LED Driver 16 enable device function.
 * @details This function enables device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void leddriver16_enable_device ( leddriver16_t *ctx );

/**
 * @brief LED Driver 16 disable output function.
 * @details This function disables output by setting the OE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void leddriver16_disable_output ( leddriver16_t *ctx );

/**
 * @brief LED Driver 16 enable output function.
 * @details This function enables output by setting the OE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void leddriver16_enable_output ( leddriver16_t *ctx );

/**
 * @brief LED Driver 16 clear errors function.
 * @details This function clears all error status bits in EFLAGn register and ERROR (bit 6).
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver16_clear_errors ( leddriver16_t *ctx );

/**
 * @brief LED Driver 16 set led state function.
 * @details This function sets the output state for the specified LEDs.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @param[in] led_ch_mask : LED channel mask (16-bit). See the LED channel setting macros definition.
 * @param[in] state : LED output state @li @c 0 - off.
 *                                     @li @c 1 - fully on (individual brightness and group dimming/blinking not controlled). 
 *                                                The OE pin can be used as external dimming/blinking control in this state.
 *                                     @li @c 2 - individual brightness can be controlled through its PWMx register 
 *                                                (default power-up state) or PWMALL register for all LEDn outputs.
 *                                     @li @c 3 - individual brightness and group dimming/blinking can be controlled through
 *                                                its PWMx register and the GRPPWM registers.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver16_set_led_state ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t state );

/**
 * @brief LED Driver 16 set led pwm function.
 * @details This function sets the PWM duty cycle for the specified LEDs.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @param[in] led_ch_mask : LED channel mask (16-bit). See the LED channel setting macros definition.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note A 31.25 kHz fixed frequency signal is used for each output. Duty cycle is controlled through 255 linear steps
 * from 00h (0 % duty cycle = LED output off) to FEh (99.2 % duty cycle = LED output at maximum brightness) and
 * FFh (100 % duty cycle = LED output completed ON). Applicable to LEDs with output state 2 or 3.
 */
err_t leddriver16_set_led_pwm ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t duty_cycle );

/**
 * @brief LED Driver 16 set led iref function.
 * @details This function sets the gain settings for output current for the specified LEDs.
 * @param[in] ctx : Click context object.
 * See #leddriver16_t object definition for detailed explanation.
 * @param[in] led_ch_mask : LED channel mask (16-bit). See the LED channel setting macros definition.
 * @param[in] iref : Output current setting with steps of 225uA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Output current = iref * 225uA, which leads to range from 225uA to 57.375mA.
 */
err_t leddriver16_set_led_iref ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t iref );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER16_H

/*! @} */ // leddriver16

// ------------------------------------------------------------------------ END

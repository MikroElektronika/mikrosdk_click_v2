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
 * @file leddriver9.h
 * @brief This file contains API for LED Driver 9 Click Driver.
 */

#ifndef LEDDRIVER9_H
#define LEDDRIVER9_H

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
 * @addtogroup leddriver9 LED Driver 9 Click Driver
 * @brief API for configuring and manipulating LED Driver 9 Click driver.
 * @{
 */

/**
 * @defgroup leddriver9_reg LED Driver 9 Registers List
 * @brief List of registers of LED Driver 9 Click driver.
 */

/**
 * @addtogroup leddriver9_reg
 * @{
 */

/**
 * @brief LED Driver 9 MODE1 register.
 * @details Register for general settings of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_MODE1                                        0x00

/**
 * @brief LED Driver 9 MODE2 register.
 * @details Register for general settings of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_MODE2                                        0x01

/**
 * @brief LED Driver 9 PWM0 register.
 * @details Channel 0 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM0                                         0x02

/**
 * @brief LED Driver 9 PWM1 register.
 * @details Channel 1 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM1                                         0x03

/**
 * @brief LED Driver 9 PWM2 register.
 * @details Channel 2 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM2                                         0x04

/**
 * @brief LED Driver 9 PWM3 register.
 * @details Channel 3 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM3                                         0x05

/**
 * @brief LED Driver 9 PWM4 register.
 * @details Channel 4 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM4                                         0x06

/**
 * @brief LED Driver 9 PWM5 register.
 * @details Channel 5 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM5                                         0x07

/**
 * @brief LED Driver 9 PWM6 register.
 * @details Channel 6 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM6                                         0x08

/**
 * @brief LED Driver 9 PWM7 register.
 * @details Channel 7 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM7                                         0x09

/**
 * @brief LED Driver 9 PWM8 register.
 * @details Channel 8 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM8                                         0x0A

/**
 * @brief LED Driver 9 PWM9 register.
 * @details Channel 9 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM9                                         0x0B

/**
 * @brief LED Driver 9 PWM10 register.
 * @details Channel 10 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM10                                        0x0C

/**
 * @brief LED Driver 9 PWM11 register.
 * @details Channel 11 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM11                                        0x0D

/**
 * @brief LED Driver 9 PWM12 register.
 * @details Channel 12 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM12                                        0x0E

/**
 * @brief LED Driver 9 PWM13 register.
 * @details Channel 13 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM13                                        0x0F

/**
 * @brief LED Driver 9 PWM14 register.
 * @details Channel 14 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM14                                        0x10

/**
 * @brief LED Driver 9 PWM15 register.
 * @details Channel 15 duty cycle setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_PWM15                                        0x11

/**
 * @brief LED Driver 9 GRPPWM register.
 * @details Group duty cycle control setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_GRPPWM                                       0x12

/**
 * @brief LED Driver 9 GRPFREQ register.
 * @details Group frequency register setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_GRPFREQ                                      0x13

/**
 * @brief LED Driver 9 LEDOUT0 register.
 * @details LED driver output state register setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_LEDOUT0                                      0x14

/**
 * @brief LED Driver 9 LEDOUT1 register.
 * @details LED driver output state register setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_LEDOUT1                                      0x15

/**
 * @brief LED Driver 9 LEDOUT2 register.
 * @details LED driver output state register setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_LEDOUT2                                      0x16

/**
 * @brief LED Driver 9 LEDOUT3 register.
 * @details LED driver output state register setting of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_LEDOUT3                                      0x17

/**
 * @brief LED Driver 9 SUBADR1 register.
 * @details I2C bus subaddress 1 register of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_SUBADR1                                      0x18

/**
 * @brief LED Driver 9 SUBADR2 register.
 * @details I2C bus subaddress 2 register of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_SUBADR2                                      0x19

/**
 * @brief LED Driver 9 SUBADR3 register.
 * @details I2C bus subaddress 3 register of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_SUBADR3                                      0x1A

/**
 * @brief LED Driver 9 ALLCALLADR register.
 * @details LED all call I2C bus address register of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_ALLCALLADR                                   0x1B

/**
 * @brief LED Driver 9 IREF register.
 * @details Output gain control register of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_IREF                                         0x1C

/**
 * @brief LED Driver 9 EFLAG1 register.
 * @details Error flags register 1 of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_EFLAG1                                       0x1D

/**
 * @brief LED Driver 9 EFLAG2 register.
 * @details Error flags register 2 of LED Driver 9 Click driver.
 */
#define LEDDRIVER9_REG_EFLAG2                                       0x1E

/*! @} */ // leddriver9_reg

/**
 * @defgroup leddriver9_set LED Driver 9 Registers Settings
 * @brief Settings for registers of LED Driver 9 Click driver.
 */

/**
 * @addtogroup leddriver9_set
 * @{
 */

/**
 * @brief LED Driver 9 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 9 Click driver.
 */
#define LEDDRIVER9_SET_DEV_ADDR  0x60

/*! @} */ // leddriver9_set

/**
 * @defgroup leddriver9_map LED Driver 9 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 9 Click driver.
 */

/**
 * @addtogroup leddriver9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 9 Click to the selected MikroBUS.
 */
#define LEDDRIVER9_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // leddriver9_map
/*! @} */ // leddriver9

/**
 * @brief LED Driver 9 Click context object.
 * @details Context object definition of LED Driver 9 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  rst;

    // Modules

    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} leddriver9_t;

/**
 * @brief LED Driver 9 Click configuration object.
 * @details Configuration object definition of LED Driver 9 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;                                 /**< Digital output reset pin. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} leddriver9_cfg_t;

/**
 * @brief LED Driver 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER9_OK = 0,
    LEDDRIVER9_ERROR = -1

} leddriver9_return_value_t;


/**
 * @brief LED Driver 9 Click channel select options.
 * @details Predefined enum values for ledout channels.
 */
typedef enum
{
    LEDDRIVER9_CHANNEL0 = 0,
    LEDDRIVER9_CHANNEL1,
    LEDDRIVER9_CHANNEL2,
    LEDDRIVER9_CHANNEL3,
    LEDDRIVER9_CHANNEL4,
    LEDDRIVER9_CHANNEL5,
    LEDDRIVER9_CHANNEL6,
    LEDDRIVER9_CHANNEL7,
    LEDDRIVER9_CHANNEL8,
    LEDDRIVER9_CHANNEL9,
    LEDDRIVER9_CHANNEL10,
    LEDDRIVER9_CHANNEL11,
    LEDDRIVER9_CHANNEL12,
    LEDDRIVER9_CHANNEL13,
    LEDDRIVER9_CHANNEL14,
    LEDDRIVER9_CHANNEL15

} leddriver9_channel_sel_t;


/**
 * @brief LED Driver 9 Click ledout select options.
 * @details Predefined enum values for ledout options.
 */
typedef enum
{
    LEDDRIVER9_OFF = 0,                              /**< LED driver x is off (default power-up state). */
    LEDDRIVER9_FULL_ON,                              /**< LED driver x is fully on (individual brightness and group dimming/blinking not controlled). */
    LEDDRIVER9_INDIVIDUAL,                           /**< LED driver x is individual brightness can be controlled through its PWMx register. */
    LEDDRIVER9_GROUP                                 /**< Same as individual but also includes the GRPPWM registers. */

} leddriver9_ledout_sel_t;


/**
 * @brief LED Driver 9 Click mode registers.
 * @details Structure that contains MODE1 and MODE2 registers.
 */
typedef struct
{
    union
    {
        uint8_t byte;                                /**< Full register represented as a single byte. */
        struct
        {
            uint8_t ALLCALL : 1;                     /**< MODE1[0] ALLCALL: Device responds to LED All Call I2C bus address option. */
            uint8_t SUB3 : 1;                        /**< MODE1[1] SUB3: Device responds to I2C bus subaddress 3 option. */
            uint8_t SUB2 : 1;                        /**< MODE1[2] SUB2: Device responds to I2C bus subaddress 2 option. */
            uint8_t SUB1 : 1;                        /**< MODE1[3] SUB1: Device responds to I2C bus subaddress 1 option. */
            uint8_t OSC : 1;                         /**< MODE1[4] OSC: Oscillator off option. */
            uint8_t AI0 : 1;                         /**< MODE1[5] AI0: Auto-increment bit 0 option. */
            uint8_t AI1 : 1;                         /**< MODE1[6] AI1: Auto-increment bit 1 option. */
            uint8_t AI2 : 1;                         /**< MODE1[7] AI2: Register auto-increment enable option. */
        };
    } mode_1;
    
    union
    {
        uint8_t byte;                                /**< Full register represented as a single byte. */
        struct
        {
            uint8_t RES : 3;                         /**< MODE2[2:0] RES: Reserved. */
            uint8_t OCH : 1;                         /**< MODE2[3] OCH: Outputs change on ACK or Stop command. */
            uint8_t RES1 : 1;                        /**< MODE2[4] RES1: Reserved. */
            uint8_t DMBLNK : 1;                      /**< MODE2[5] DMBLNK: Group control blinking or dimming. */
            uint8_t RES2 : 1;                        /**< MODE2[6] RES2: Reserved. */
            uint8_t EFCLR : 1;                       /**< MODE2[7] EFCLR: Clear error status flag. */
        };
    } mode_2;
    
} leddriver9_mode_reg_t;

/**
 * @brief LED Driver 9 Click LED output state registers.
 * @details Structure that contains LEDOUTx registers.
 */
typedef struct
{
    union
    {
        uint8_t byte;                                /**< Full register represented as a single byte. */
        struct
        {
            uint8_t LDR0 : 2;                        /**< LDR0[1:0] LDR0: LED0 output state control. */
            uint8_t LDR1 : 2;                        /**< LDR1[3:2] LDR1: LED1 output state control. */
            uint8_t LDR2 : 2;                        /**< LDR2[5:4] LDR2: LED2 output state control. */
            uint8_t LDR3 : 2;                        /**< LDR3[7:6] LDR3: LED3 output state control. */
        };
    } LEDOUT0;
    
    union
    {
        uint8_t byte;                                /**< Full register represented as a single byte. */
        struct
        {
            uint8_t LDR4 : 2;                        /**< LDR4[1:0] LDR4: LED4 output state control. */
            uint8_t LDR5 : 2;                        /**< LDR5[3:2] LDR5: LED5 output state control. */
            uint8_t LDR6 : 2;                        /**< LDR6[5:4] LDR6: LED6 output state control. */
            uint8_t LDR7 : 2;                        /**< LDR7[7:6] LDR7: LED7 output state control. */
        };
    } LEDOUT1;
    
    union
    {
        uint8_t byte;                                /**< Full register represented as a single byte. */
        struct
        {
            uint8_t LDR8 : 2;                        /**< LDR8[1:0] LDR8: LED8 output state control. */
            uint8_t LDR9 : 2;                        /**< LDR9[3:2] LDR9: LED9 output state control. */
            uint8_t LDR10 : 2;                       /**< LDR10[5:4] LDR10: LED10 output state control. */
            uint8_t LDR11 : 2;                       /**< LDR11[7:6] LDR11: LED11 output state control. */
        };
    } LEDOUT2;
    
    union
    {
        uint8_t byte;                                /**< Full register represented as a single byte. */
        struct
        {
            uint8_t LDR12 : 2;                       /**< LDR12[1:0] LDR12: LED12 output state control. */
            uint8_t LDR13 : 2;                       /**< LDR13[3:2] LDR13: LED13 output state control. */
            uint8_t LDR14 : 2;                       /**< LDR14[5:4] LDR14: LED14 output state control. */
            uint8_t LDR15 : 2;                       /**< LDR15[7:6] LDR15: LED15 output state control. */
        };
    } LEDOUT3;
    
} leddriver9_output_state_t;

/*!
 * @addtogroup leddriver9 LED Driver 9 Click Driver
 * @brief API for configuring and manipulating LED Driver 9 Click driver.
 * @{
 */

/**
 * @brief LED Driver 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void leddriver9_cfg_setup ( leddriver9_cfg_t *cfg );

/**
 * @brief LED Driver 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_init ( leddriver9_t *ctx, leddriver9_cfg_t *cfg );

/**
 * @brief LED Driver 9 default configuration function.
 * @details This function executes a default configuration of LED Driver 9
 * Click board.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
void leddriver9_default_cfg ( leddriver9_t *ctx );

/**
 * @brief LED Driver 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_generic_write ( leddriver9_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief LED Driver 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_generic_read ( leddriver9_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief LED Driver 9 MODE1 reg write function.
 * @details This function configures the MODE1 register from the
 * defined config structure.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] mode_reg : Mode reg config structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_mode1_reg_write ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg );

/**
 * @brief LED Driver 9 MODE1 reg read function.
 * @details This function acquires the data from the MODE1 register
 * and stores the content in the defined config structure.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[out] mode_reg : Mode reg config structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_mode1_reg_read ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg );

/**
 * @brief LED Driver 9 MODE2 reg write function.
 * @details This function configures the MODE2 register from the
 * defined config structure.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] mode_reg : Mode reg config structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_mode2_reg_write ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg );

/**
 * @brief LED Driver 9 MODE2 reg read function.
 * @details This function acquires the data from the MODE2 register
 * and stores the content in the defined config structure.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[out] mode_reg : Mode reg config structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_mode2_reg_read ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg );

/**
 * @brief LED Driver 9 LEDOUT state function.
 * @details This function configures the LEDOUTx registers from the
 * defined config structure.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] output_state : Output state config structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t leddriver9_ledout_state ( leddriver9_t *ctx, leddriver9_output_state_t *output_state );

/**
 * @brief LED Driver 9 set PWM function.
 * @details This function sets the PWM duty cycle on selected ledout channel.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] ch_out : Channel selection.
 * @param[in] duty_cycle : Duty cycle value ranging from 0 to 100.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Make sure that the ledout channel is previously configured accordingly.
 *
 * @endcode
 */
err_t leddriver9_set_pwm ( leddriver9_t *ctx, leddriver9_channel_sel_t ch_out, float duty_cycle );

/**
 * @brief LED Driver 9 set dimmer PWM function.
 * @details This function sets the group PWM duty cycle ( GRPPWM ) which
 * can be used for dimming already set PWM channels.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle value ranging from 0 to 100.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Make sure that the ledout channel is previously configured accordingly.
 * This feature is available only if DMBLINK bit is programmed with logic 0.
 *
 * @endcode
 */
err_t leddriver9_set_dimmer_pwm ( leddriver9_t *ctx, float duty_cycle );

/**
 * @brief LED Driver 9 set blink period function.
 * @details This function sets the group frequency period ( GRPFREQ )
 * which will result with LED blinking after the defined time.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 * @param[in] period : Time period in seconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Make sure that the ledout channel is previously configured accordingly.
 * This feature is available only if DMBLINK bit is programmed with logic 1.
 *
 * @endcode
 */
err_t leddriver9_set_blink_period ( leddriver9_t *ctx, float period );

/**
 * @brief LED Driver 9 hardware reset function.
 * @details This function performs the hardware reset on the device.
 * @param[in] ctx : Click context object.
 * See #leddriver9_t object definition for detailed explanation.
 *
 * @note None.
 *
 * @endcode
 */
void leddriver9_hardware_reset ( leddriver9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER9_H

/*! @} */ // leddriver9

// ------------------------------------------------------------------------ END

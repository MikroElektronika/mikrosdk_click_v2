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
 * @file color21.h
 * @brief This file contains API for Color 21 Click Driver.
 */

#ifndef COLOR21_H
#define COLOR21_H

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
 * @addtogroup color21 Color 21 Click Driver
 * @brief API for configuring and manipulating Color 21 Click driver.
 * @{
 */

/**
 * @defgroup color21_reg Color 21 Registers List
 * @brief List of registers of Color 21 Click driver.
 */

/**
 * @addtogroup color21_reg
 * @{
 */

/**
 * @brief Color 21 register list.
 * @details Specified register list of Color 21 Click driver.
 */
#define COLOR21_REG_AUXID                   0x58
#define COLOR21_REG_REVID                   0x59
#define COLOR21_REG_ID                      0x5A
#define COLOR21_REG_CFG_12                  0x66
#define COLOR21_REG_ENABLE                  0x80
#define COLOR21_REG_ATIME                   0x81
#define COLOR21_REG_WTIME                   0x83
#define COLOR21_REG_ALS_TH_L_LSB            0x84
#define COLOR21_REG_ALS_TH_L_MSB            0x85
#define COLOR21_REG_ALS_TH_H_LSB            0x86
#define COLOR21_REG_ALS_TH_H_MSB            0x87
#define COLOR21_REG_STATUS                  0x93
#define COLOR21_REG_ASTATUS                 0x94
#define COLOR21_REG_ADATA_0_L               0x95
#define COLOR21_REG_ADATA_0_H               0x96
#define COLOR21_REG_ADATA_1_L               0x97
#define COLOR21_REG_ADATA_1_H               0x98
#define COLOR21_REG_ADATA_2_L               0x99
#define COLOR21_REG_ADATA_2_H               0x9A
#define COLOR21_REG_ADATA_3_L               0x9B
#define COLOR21_REG_ADATA_3_H               0x9C
#define COLOR21_REG_ADATA_4_L               0x9D
#define COLOR21_REG_ADATA_4_H               0x9E
#define COLOR21_REG_ADATA_5_L               0x9F
#define COLOR21_REG_ADATA_5_H               0xA0
#define COLOR21_REG_ADATA_6_L               0xA1
#define COLOR21_REG_ADATA_6_H               0xA2
#define COLOR21_REG_ADATA_7_L               0xA3
#define COLOR21_REG_ADATA_7_H               0xA4
#define COLOR21_REG_ADATA_8_L               0xA5
#define COLOR21_REG_ADATA_8_H               0xA6
#define COLOR21_REG_ADATA_9_L               0xA7
#define COLOR21_REG_ADATA_9_H               0xA8
#define COLOR21_REG_ADATA_10_L              0xA9
#define COLOR21_REG_ADATA_10_H              0xAA
#define COLOR21_REG_ADATA_11_L              0xAB
#define COLOR21_REG_ADATA_11_H              0xAC
#define COLOR21_REG_ADATA_12_L              0xAD
#define COLOR21_REG_ADATA_12_H              0xAE
#define COLOR21_REG_ADATA_13_L              0xAF
#define COLOR21_REG_ADATA_13_H              0xB0
#define COLOR21_REG_ADATA_14_L              0xB1
#define COLOR21_REG_ADATA_14_H              0xB2
#define COLOR21_REG_ADATA_15_L              0xB3
#define COLOR21_REG_ADATA_15_H              0xB4
#define COLOR21_REG_ADATA_16_L              0xB5
#define COLOR21_REG_ADATA_16_H              0xB6
#define COLOR21_REG_ADATA_17_L              0xB7
#define COLOR21_REG_ADATA_17_H              0xB8
#define COLOR21_REG_STATUS_2                0x90
#define COLOR21_REG_STATUS_3                0x91
#define COLOR21_REG_STATUS_5                0xBB
#define COLOR21_REG_STATUS_4                0xBC
#define COLOR21_REG_CFG_0                   0xBF
#define COLOR21_REG_CFG_1                   0xC6
#define COLOR21_REG_CFG_3                   0xC7
#define COLOR21_REG_CFG_6                   0xF5
#define COLOR21_REG_CFG_8                   0xC9
#define COLOR21_REG_CFG_9                   0xCA
#define COLOR21_REG_CFG_10                  0x65
#define COLOR21_REG_PERS                    0xCF
#define COLOR21_REG_GPIO                    0x6B
#define COLOR21_REG_ASTEP_LSB               0xD4
#define COLOR21_REG_ASTEP_MSB               0xD5
#define COLOR21_REG_CFG_20                  0xD6
#define COLOR21_REG_LED                     0xCD
#define COLOR21_REG_AGC_GAIN_MAX            0xD7
#define COLOR21_REG_AZ_CONFIG               0xDE
#define COLOR21_REG_FD_TIME_1               0xE0
#define COLOR21_REG_FD_TIME_2               0xE2
#define COLOR21_REG_FD_CFG_0                0xDF
#define COLOR21_REG_FD_STATUS               0xE3
#define COLOR21_REG_INTENAB                 0xF9
#define COLOR21_REG_CONTROL                 0xFA
#define COLOR21_REG_FIFO_MAP                0xFC
#define COLOR21_REG_FIFO_LVL                0xFD
#define COLOR21_REG_FDATA_L                 0xFE
#define COLOR21_REG_FDATA_H                 0xFF

/*! @} */ // color21_reg

/**
 * @defgroup color21_set Color 21 Registers Settings
 * @brief Settings for registers of Color 21 Click driver.
 */

/**
 * @addtogroup color21_set
 * @{
 */

/**
 * @brief Color 21 ENABLE register setting.
 * @details Specified setting for ENABLE register of Color 21 Click driver.
 */
#define COLOR21_ENABLE_FDEN                 0x40
#define COLOR21_ENABLE_SMUXEN               0x10
#define COLOR21_ENABLE_WEN                  0x08
#define COLOR21_ENABLE_ALS_EN               0x02
#define COLOR21_ENABLE_PON                  0x01
#define COLOR21_ENABLE_POFF                 0x00

/**
 * @brief Color 21 CFG_0 register setting.
 * @details Specified setting for CFG_0 register of Color 21 Click driver.
 */
#define COLOR21_CFG_0_LOW_POWER             0x20
#define COLOR21_CFG_0_REG_BANK              0x10
#define COLOR21_CFG_0_WLONG                 0x04

/**
 * @brief Color 21 CFG_1 register setting.
 * @details Specified setting for CFG_1 register of Color 21 Click driver.
 */
#define COLOR21_CFG_1_AGAIN_0_5             0x00
#define COLOR21_CFG_1_AGAIN_1               0x01
#define COLOR21_CFG_1_AGAIN_2               0x02
#define COLOR21_CFG_1_AGAIN_4               0x03
#define COLOR21_CFG_1_AGAIN_8               0x04
#define COLOR21_CFG_1_AGAIN_16              0x05
#define COLOR21_CFG_1_AGAIN_32              0x06
#define COLOR21_CFG_1_AGAIN_64              0x07
#define COLOR21_CFG_1_AGAIN_128             0x08
#define COLOR21_CFG_1_AGAIN_256             0x09
#define COLOR21_CFG_1_AGAIN_512             0x0A
#define COLOR21_CFG_1_AGAIN_1024            0x0B
#define COLOR21_CFG_1_AGAIN_2048            0x0C
#define COLOR21_CFG_1_AGAIN_MASK            0x1F

/**
 * @brief Color 21 CFG_20 register setting.
 * @details Specified setting for CFG_20 register of Color 21 Click driver.
 */
#define COLOR21_CFG_20_FD_FIFO_8BIT         0x80
#define COLOR21_CFG_20_AUTO_SMUX_6CH        0x00
#define COLOR21_CFG_20_AUTO_SMUX_12CH       0x40
#define COLOR21_CFG_20_AUTO_SMUX_18CH       0x60
#define COLOR21_CFG_20_AUTO_SMUX_MASK       0x60

/**
 * @brief Color 21 CONTROL register setting.
 * @details Specified setting for CONTROL register of Color 21 Click driver.
 */
#define COLOR21_CONTROL_SW_RESET            0x08
#define COLOR21_CONTROL_ALS_MAN_AZ          0x04
#define COLOR21_CONTROL_FIFO_CLR            0x02
#define COLOR21_CONTROL_CLEAR_SAI_ACT       0x01

/**
 * @brief Color 21 LED register setting.
 * @details Specified setting for LED register of Color 21 Click driver.
 */
#define COLOR21_LED_OFF                     0x00
#define COLOR21_LED_ON                      0x80
#define COLOR21_LED_DRIVE_CURR_MIN          4
#define COLOR21_LED_DRIVE_CURR_MAX          258
#define COLOR21_LED_DRIVE_CURR_STEP         2
#define COLOR21_LED_DRIVE_CURR_DEFAULT      8

/**
 * @brief Color 21 STATUS register setting.
 * @details Specified setting for STATUS register of Color 21 Click driver.
 */
#define COLOR21_STATUS_ASAT                 0x80
#define COLOR21_STATUS_AINT                 0x08
#define COLOR21_STATUS_FINT                 0x04
#define COLOR21_STATUS_SINT                 0x01

/**
 * @brief Color 21 ASTATUS register setting.
 * @details Specified setting for ASTATUS register of Color 21 Click driver.
 */
#define COLOR21_ASTATUS_ASAT                0x80
#define COLOR21_ASTATUS_AGAIN_MASK          0x0F

/**
 * @brief Color 21 STATUS_2 register setting.
 * @details Specified setting for STATUS_2 register of Color 21 Click driver.
 */
#define COLOR21_STATUS_2_AVALID             0x40
#define COLOR21_STATUS_2_ASAT_DIG           0x10
#define COLOR21_STATUS_2_ASAT_ANA           0x08
#define COLOR21_STATUS_2_FDSAT_ANA          0x02
#define COLOR21_STATUS_2_FDSAT_DIG          0x01

/**
 * @brief Color 21 device ID value.
 * @details Specified device ID value of Color 21 Click driver.
 */
#define COLOR21_DEVICE_ID                   0x81

/**
 * @brief Color 21 register bank access setting.
 * @details Specified setting for register bank access of Color 21 Click driver.
 */
#define COLOR21_ACCESS_REG_BANK_ABOVE_80H   0
#define COLOR21_ACCESS_REG_BANK_20H_7FH     1

/**
 * @brief Color 21 integration time setting.
 * @details Specified setting for integration time of Color 21 Click driver.
 */
#define COLOR21_SINGLE_STEP_MS              0.00278f
#define COLOR21_ATIME_MAX                   255
#define COLOR21_ASTEP_MAX                   65534
#define COLOR21_INTEGRATION_TIME_MAX        ( ( float ) ( COLOR21_ATIME_MAX + 1 ) * ( COLOR21_ASTEP_MAX + 1 ) * COLOR21_SINGLE_STEP_MS )
#define COLOR21_INTEGRATION_TIME_MIN        COLOR21_SINGLE_STEP_MS
#define COLOR21_INTEGRATION_TIME_DEFAULT    90.0f
#define COLOR21_WAIT_STEP_MS                2.78f
#define COLOR21_WTIME_MAX                   255
#define COLOR21_WAIT_TIME_MAX                ( ( float ) ( COLOR21_WTIME_MAX + 1 ) * COLOR21_WAIT_STEP_MS )
#define COLOR21_WAIT_TIME_MIN               COLOR21_WAIT_STEP_MS
#define COLOR21_WAIT_TIME_DEFAULT           100.0f

/**
 * @brief Color 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 21 Click driver.
 */
#define COLOR21_DEVICE_ADDRESS              0x59

/*! @} */ // color21_set

/**
 * @defgroup color21_map Color 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 21 Click driver.
 */

/**
 * @addtogroup color21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 21 Click to the selected MikroBUS.
 */
#define COLOR21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ldr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.io_pin = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color21_map
/*! @} */ // color21

/**
 * @brief Color 21 Click data object.
 * @details Data object definition of Color 21 Click driver.
 */
typedef struct
{
    uint8_t status;
    uint8_t astatus;
    uint16_t ch_fz;
    uint16_t ch_fy;
    uint16_t ch_fxl;
    uint16_t ch_nir;
    uint16_t ch_2x_vis_1;
    uint16_t ch_fd_1;
    uint16_t ch_f2;
    uint16_t ch_f3;
    uint16_t ch_f4;
    uint16_t ch_f6;
    uint16_t ch_2x_vis_2;
    uint16_t ch_fd_2;
    uint16_t ch_f1;
    uint16_t ch_f5;
    uint16_t ch_f7;
    uint16_t ch_f8;
    uint16_t ch_2x_vis_3;
    uint16_t ch_fd_3;
    
} color21_data_t;

/**
 * @brief Color 21 Click context object.
 * @details Context object definition of Color 21 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ldr;          /**< LED driver pin. */

    // Input pins
    digital_in_t io_pin;        /**< GPIO pin. */
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} color21_t;

/**
 * @brief Color 21 Click configuration object.
 * @details Configuration object definition of Color 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ldr;             /**< LED driver pin. */
    pin_name_t io_pin;          /**< GPIO pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color21_cfg_t;

/**
 * @brief Color 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR21_OK = 0,
    COLOR21_ERROR = -1

} color21_return_value_t;

/*!
 * @addtogroup color21 Color 21 Click Driver
 * @brief API for configuring and manipulating Color 21 Click driver.
 * @{
 */

/**
 * @brief Color 21 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color21_cfg_setup ( color21_cfg_t *cfg );

/**
 * @brief Color 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_init ( color21_t *ctx, color21_cfg_t *cfg );

/**
 * @brief Color 21 default configuration function.
 * @details This function executes a default configuration of Color 21
 * Click board.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color21_default_cfg ( color21_t *ctx );

/**
 * @brief Color 21 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_generic_write ( color21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 21 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_generic_read ( color21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 21 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_write_reg ( color21_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Color 21 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_read_reg ( color21_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Color 21 write register word function.
 * @details This function writes a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_write_reg_word ( color21_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Color 21 read register word function.
 * @details This function reads a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_read_reg_word ( color21_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Color 21 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_check_communication ( color21_t *ctx );

/**
 * @brief Color 21 set ldr pin function.
 * @details This function sets the LDR pin logic state.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void color21_set_ldr_pin ( color21_t *ctx, uint8_t state );

/**
 * @brief Color 21 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t color21_get_int_pin ( color21_t *ctx );

/**
 * @brief Color 21 get io pin function.
 * @details This function returns the IO pin logic state.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t color21_get_io_pin ( color21_t *ctx );

/**
 * @brief Color 21 set reg bank access function.
 * @details This function sets the register bank access.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] reg_bank : @li @c 0 - Access to registers above 80h,
 *                       @li @c 1 - Access to registers from 20h to 7Fh.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_set_reg_bank_access ( color21_t *ctx, uint8_t reg_bank );

/**
 * @brief Color 21 disable ext led function.
 * @details This function disables the onboard LED.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_disable_ext_led ( color21_t *ctx );

/**
 * @brief Color 21 enable ext led function.
 * @details This function enables the onboard LED with the selected led driver current.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] led_curr : LED Driver current in mA [4-258].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_enable_ext_led ( color21_t *ctx, uint16_t led_curr );

/**
 * @brief Color 21 set integration time ms function.
 * @details This function sets the integration time in milliseconds by setting
 * the ATIME and ASTEP registers.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] int_time_ms : Integration time in milliseconds 
 * [from COLOR21_INTEGRATION_TIME_MIN to COLOR21_INTEGRATION_TIME_MAX].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_set_integration_time_ms ( color21_t *ctx, float int_time_ms );

/**
 * @brief Color 21 set wait time ms function.
 * @details This function sets the wait time in milliseconds by setting the WTIME register.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[in] wait_time_ms : Wait time in milliseconds 
 * [from COLOR21_WAIT_TIME_MIN to COLOR21_WAIT_TIME_MAX].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_set_wait_time_ms ( color21_t *ctx, float wait_time_ms );

/**
 * @brief Color 21 read data function.
 * @details This function checks if the spectral measurement data is ready and then reads
 * data from all channels along with the STATUS and ASTATUS bytes.
 * @param[in] ctx : Click context object.
 * See #color21_t object definition for detailed explanation.
 * @param[out] data_out : Spectral measurements data object.
 * See #color21_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color21_read_data ( color21_t *ctx, color21_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // COLOR21_H

/*! @} */ // color21

// ------------------------------------------------------------------------ END

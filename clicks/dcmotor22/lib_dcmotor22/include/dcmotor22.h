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
 * @file dcmotor22.h
 * @brief This file contains API for DC Motor 22 Click Driver.
 */

#ifndef DCMOTOR22_H
#define DCMOTOR22_H

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
#include "drv_uart.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup dcmotor22 DC Motor 22 Click Driver
 * @brief API for configuring and manipulating DC Motor 22 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor22_cmd DC Motor 22 Device Settings
 * @brief Settings for registers of DC Motor 22 Click driver.
 */

/**
 * @addtogroup dcmotor22_cmd
 * @{
 */

/**
 * @brief DC Motor 22 registers map.
 * @details Specified registers map of DC Motor 22 Click driver.
 */
#define DCMOTOR22_REG_GCONF                         0x00
#define DCMOTOR22_REG_GSTAT                         0x01
#define DCMOTOR22_REG_IFCNT                         0x02
#define DCMOTOR22_REG_SLAVECONF                     0x03
#define DCMOTOR22_REG_IOIN                          0x06
#define DCMOTOR22_REG_CURRENT_LIMIT                 0x10
#define DCMOTOR22_REG_PWM_AB                        0x22
#define DCMOTOR22_REG_CHOPCONF                      0x6C
#define DCMOTOR22_REG_DRV_STATUS                    0x6F
#define DCMOTOR22_REG_PWMCONF                       0x70

/**
 * @brief DC Motor 22 sync byte, read/write bit, and timeout value for 
 * read and retry send in milliseconds.
 * @details Specified sync byte, read/write bit, and timeout value for 
 * read and retry send in milliseconds of DC Motor 22 Click driver.
 */
#define DCMOTOR22_SYNC_BYTE                         0x05
#define DCMOTOR22_READ_WRITE_BIT                    0x80
#define DCMOTOR22_RETRY_SEND_TIMEOUT                100
#define DCMOTOR22_READ_TIMEOUT                      1000

/**
 * @brief DC Motor 22 GCONF register settings.
 * @details Specified GCONF register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_GCONF_PWM_DIRECT                  ( 0x01ul )
#define DCMOTOR22_GCONF_EXTCAP_AVAILABLE            ( 0x02ul )
#define DCMOTOR22_GCONF_PAR_MODE_DUAL_MOTOR         ( 0x00ul )
#define DCMOTOR22_GCONF_PAR_MODE_SINGLE_MOTOR       ( 0x04ul )
#define DCMOTOR22_GCONF_TEST_MODE                   ( 0x08ul )

/**
 * @brief DC Motor 22 GSTAT register settings.
 * @details Specified GSTAT register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_GSTAT_RESET                       ( 0x01ul )
#define DCMOTOR22_GSTAT_DRV_ERR                     ( 0x02ul )
#define DCMOTOR22_GSTAT_UNDER_3V5                   ( 0x04ul )
#define DCMOTOR22_GSTAT_CLEAR_ALL                   ( 0x07ul )

/**
 * @brief DC Motor 22 SLAVECONF register settings.
 * @details Specified SLAVECONF register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_SLAVECONF_SENDDELAY_8BIT          ( 0x0000ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_24BIT         ( 0x0200ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_40BIT         ( 0x0400ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_56BIT         ( 0x0600ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_72BIT         ( 0x0800ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_88BIT         ( 0x0A00ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_104BIT        ( 0x0C00ul )
#define DCMOTOR22_SLAVECONF_SENDDELAY_120BIT        ( 0x0E00ul )

/**
 * @brief DC Motor 22 IOIN register settings.
 * @details Specified IOIN register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_IOIN_EN                           ( 0x01ul )
#define DCMOTOR22_IOIN_NSTDBY                       ( 0x02ul )
#define DCMOTOR22_IOIN_AD0                          ( 0x04ul )
#define DCMOTOR22_IOIN_AD1                          ( 0x08ul )
#define DCMOTOR22_IOIN_DIAG                         ( 0x10ul )
#define DCMOTOR22_IOIN_UART_ON                      ( 0x20ul )
#define DCMOTOR22_IOIN_UART_IN                      ( 0x40ul )
#define DCMOTOR22_IOIN_MODE_IN                      ( 0x80ul )
#define DCMOTOR22_IOIN_A2                           ( 0x0100ul )
#define DCMOTOR22_IOIN_A1                           ( 0x0200ul )
#define DCMOTOR22_IOIN_COMP_A1A2                    ( 0x0400ul )
#define DCMOTOR22_IOIN_COMP_B1B2                    ( 0x0800ul )
#define DCMOTOR22_IOIN_VERSION                      ( 0x40000000ul )
#define DCMOTOR22_IOIN_VERSION_MASK                 ( 0xFF000000ul )

/**
 * @brief DC Motor 22 CURRENT_LIMIT register settings.
 * @details Specified CURRENT_LIMIT register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_CURRENT_LIMIT_EN_FREEWHEELING     ( 0x01ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_1_32           ( 0x0000ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_2_32           ( 0x0100ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_3_32           ( 0x0200ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_4_32           ( 0x0300ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_5_32           ( 0x0400ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_6_32           ( 0x0500ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_7_32           ( 0x0600ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_8_32           ( 0x0700ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_9_32           ( 0x0800ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_10_32          ( 0x0900ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_11_32          ( 0x0A00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_12_32          ( 0x0B00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_13_32          ( 0x0C00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_14_32          ( 0x0D00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_15_32          ( 0x0E00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_16_32          ( 0x0F00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_17_32          ( 0x1000ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_18_32          ( 0x1100ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_19_32          ( 0x1200ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_20_32          ( 0x1300ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_21_32          ( 0x1400ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_22_32          ( 0x1500ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_23_32          ( 0x1600ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_24_32          ( 0x1700ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_25_32          ( 0x1800ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_26_32          ( 0x1900ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_27_32          ( 0x1A00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_28_32          ( 0x1B00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_29_32          ( 0x1C00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_30_32          ( 0x1D00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_31_32          ( 0x1E00ul )
#define DCMOTOR22_CURRENT_LIMIT_IRUN_32_32          ( 0x1F00ul )

/**
 * @brief DC Motor 22 motor PWM settings.
 * @details Specified motor PWM settings for ADC of DC Motor 22 Click driver.
 */
#define DCMOTOR22_MAX_PWM                           255
#define DCMOTOR22_MIN_PWM                           ( -255 )
#define DCMOTOR22_PWM_RES                           0x01FF
#define DCMOTOR22_PWM_DUTY_0                        ( 0x00ul )

/**
 * @brief DC Motor 22 CHOPCONF register settings.
 * @details Specified CHOPCONF register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_CHOPCONF_DISS2VS                  ( 0x80000000ul )
#define DCMOTOR22_CHOPCONF_DISS2G                   ( 0x40000000ul )
#define DCMOTOR22_CHOPCONF_TBL_0                    ( 0x00000000ul )
#define DCMOTOR22_CHOPCONF_TBL_1                    ( 0x00008000ul )
#define DCMOTOR22_CHOPCONF_TBL_2                    ( 0x00010000ul )
#define DCMOTOR22_CHOPCONF_TBL_3                    ( 0x00018000ul )
#define DCMOTOR22_CHOPCONF_ENABLEDRV                ( 0x00000001ul )

/**
 * @brief DC Motor 22 PWMCONF register settings.
 * @details Specified PWMCONF register settings of DC Motor 22 Click driver.
 */
#define DCMOTOR22_PWMCONF_FREEWHEEL_NORMAL_OP       ( 0x00000000ul )
#define DCMOTOR22_PWMCONF_FREEWHEEL_FREEWHEELING    ( 0x00100000ul )
#define DCMOTOR22_PWMCONF_FREEWHEEL_LS_SHORTED      ( 0x00200000ul )
#define DCMOTOR22_PWMCONF_FREEWHEEL_HS_SHORTED      ( 0x00300000ul )
#define DCMOTOR22_PWMCONF_PWM_FREQ_2_1024           ( 0x00000000ul )
#define DCMOTOR22_PWMCONF_PWM_FREQ_2_683            ( 0x00010000ul )
#define DCMOTOR22_PWMCONF_PWM_FREQ_2_512            ( 0x00020000ul )
#define DCMOTOR22_PWMCONF_PWM_FREQ_2_410            ( 0x00030000ul )

/**
 * @brief DC Motor 22 motor selection values.
 * @details Specified motor selection values of DC Motor 22 Click driver.
 */
#define DCMOTOR22_MOTOR_A                           0x00
#define DCMOTOR22_MOTOR_B                           0x01

/**
 * @brief DC Motor 22 current calculation values.
 * @details Specified current calculation values for ADC of DC Motor 22 Click driver.
 */
#define DCMOTOR22_NUM_CONVERSIONS                   100
#define DCMOTOR22_RSENSE                            0.1

/**
 * @brief DC Motor 22 ADC setup byte values.
 * @details Specified ADC setup byte values of DC Motor 22 Click driver.
 */
#define DCMOTOR22_ADC_REG_SETUP                     0x80
#define DCMOTOR22_ADC_SETUP_VREF_VDD_REF_NC_OFF     0x00
#define DCMOTOR22_ADC_SETUP_VREF_EXT_REF_IN_OFF     0x20
#define DCMOTOR22_ADC_SETUP_VREF_INT_REF_NC_OFF     0x40
#define DCMOTOR22_ADC_SETUP_VREF_INT_REF_NC_ON      0x50
#define DCMOTOR22_ADC_SETUP_VREF_INT_REF_OUT_OFF    0x60
#define DCMOTOR22_ADC_SETUP_VREF_INT_REF_OUT_ON     0x70
#define DCMOTOR22_ADC_SETUP_CLK_INT                 0x00
#define DCMOTOR22_ADC_SETUP_CLK_EXT                 0x08
#define DCMOTOR22_ADC_SETUP_UNIPOLAR                0x00
#define DCMOTOR22_ADC_SETUP_BIPOLAR                 0x04
#define DCMOTOR22_ADC_SETUP_RST_RESET               0x00
#define DCMOTOR22_ADC_SETUP_RST_NO_ACTION           0x02

/**
 * @brief DC Motor 22 ADC config byte values.
 * @details Specified ADC config byte values of DC Motor 22 Click driver.
 */
#define DCMOTOR22_ADC_REG_CONFIG                    0x00
#define DCMOTOR22_ADC_CONFIG_SCAN_AIN0_TO_CS0       0x00
#define DCMOTOR22_ADC_CONFIG_SCAN_CS0_8_TIMES       0x20
#define DCMOTOR22_ADC_CONFIG_SCAN_CS0               0x60
#define DCMOTOR22_ADC_CONFIG_CS0_AIN0               0x00
#define DCMOTOR22_ADC_CONFIG_CS0_AIN1               0x02
#define DCMOTOR22_ADC_CONFIG_DIFFERENTIAL           0x00
#define DCMOTOR22_ADC_CONFIG_SINGLE_ENDED           0x01

/**
 * @brief DC Motor 22 ADC register bit mask.
 * @details Specified ADC register bit of DC Motor 22 Click driver.
 */
#define DCMOTOR22_ADC_REG_BIT_MASK                  0x80
#define DCMOTOR22_ADC_SETUP_VREF_BIT_MASK           0x70
#define DCMOTOR22_ADC_SETUP_CLK_BIT_MASK            0x08
#define DCMOTOR22_ADC_SETUP_UNI_BIP_BIT_MASK        0x04
#define DCMOTOR22_ADC_SETUP_RST_BIT_MASK            0x02
#define DCMOTOR22_ADC_CONFIG_SCAN_BIT_MASK          0x60
#define DCMOTOR22_ADC_CONFIG_CS0_BIT_MASK           0x02
#define DCMOTOR22_ADC_CONFIG_SGL_DIF_BIT_MASK       0x01

/**
 * @brief DC Motor 22 ADC channel selection values.
 * @details Specified ADC channel selection values of DC Motor 22 Click driver.
 */
#define DCMOTOR22_ADC_CHANNEL_0                     0
#define DCMOTOR22_ADC_CHANNEL_1                     1

/**
 * @brief DC Motor 22 ADC calculation values.
 * @details Specified ADC calculation values of DC Motor 22 Click driver.
 */
#define DCMOTOR22_ADC_RESOLUTION                    0x0FFF
#define DCMOTOR22_ADC_VREF                          2.048

/**
 * @brief DC Motor 22 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 22 Click driver.
 */
#define DCMOTOR22_ADC_DEVICE_ADDRESS                0x36
#define DCMOTOR22_UART_DEVICE_ADDRESS_0             0x00
#define DCMOTOR22_UART_DEVICE_ADDRESS_1             0x01
#define DCMOTOR22_UART_DEVICE_ADDRESS_2             0x02
#define DCMOTOR22_UART_DEVICE_ADDRESS_3             0x03
#define DCMOTOR22_UART_DEVICE_ADDRESS_MASK          0x03

/**
 * @brief DC Motor 22 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                             200

/*! @} */ // dcmotor22_cmd

/**
 * @defgroup dcmotor22_map DC Motor 22 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 22 Click driver.
 */

/**
 * @addtogroup dcmotor22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 22 Click to the selected MikroBUS.
 */
#define DCMOTOR22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.a0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.a1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // dcmotor22_map
/*! @} */ // dcmotor22

/**
 * @brief DC Motor 22 Click context object.
 * @details Context object definition of DC Motor 22 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t a0;           /**< Address selection pin 0. */
    digital_out_t a1;           /**< Address selection pin 1. */
    digital_out_t en;           /**< Enable pin (Active High). */

    // Input pins
    digital_in_t int_pin;       /**< Diagnostic interrupt pin (Active High). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    uart_t uart;                /**< UART driver object. */
    
    uint8_t uart_device_address;/**< Device slave address (used for UART driver). */
    uint8_t i2c_slave_address;  /**< Device slave address (used for I2C driver). */

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    
    uint8_t adc_setup_byte;     /**< ADC setup byte last programmed value. */
    uint8_t adc_config_byte;    /**< ADC config byte last programmed value. */
    uint32_t pwm_ab;            /**< PWM AB register settings. */

} dcmotor22_t;

/**
 * @brief DC Motor 22 Click configuration object.
 * @details Configuration object definition of DC Motor 22 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t a0;              /**< Address selection pin 0. */
    pin_name_t a1;              /**< Address selection pin 1. */
    pin_name_t en;              /**< Enable pin (Active High). */
    pin_name_t int_pin;         /**< Diagnostic interrupt pin (Active High). */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */
    
    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} dcmotor22_cfg_t;

/**
 * @brief DC Motor 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR22_OK = 0,
    DCMOTOR22_ERROR = -1

} dcmotor22_return_value_t;

/*!
 * @addtogroup dcmotor22 DC Motor 22 Click Driver
 * @brief API for configuring and manipulating DC Motor 22 Click driver.
 * @{
 */

/**
 * @brief DC Motor 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor22_cfg_setup ( dcmotor22_cfg_t *cfg );

/**
 * @brief DC Motor 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_init ( dcmotor22_t *ctx, dcmotor22_cfg_t *cfg );

/**
 * @brief DC Motor 22 default configuration function.
 * @details This function executes a default configuration of DC Motor 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor22_default_cfg ( dcmotor22_t *ctx );

/**
 * @brief DC Motor 22 write register function.
 * @details This function writes a desired data to the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_write_register ( dcmotor22_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief DC Motor 22 read register function.
 * @details This function reads 32-bit data from the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 32-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_read_register ( dcmotor22_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief DC Motor 22 ADC write setup byte function.
 * @details This function writes a setup byte to the ADC chip by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] setup_byte : Setup byte to be written ( the value will be stored in @b ctx->setup_byte ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_adc_write_setup_byte ( dcmotor22_t *ctx, uint8_t setup_byte );

/**
 * @brief DC Motor 22 ADC write config byte function.
 * @details This function writes a config byte to the ADC chip by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] config_byte : Config byte to be written ( the value will be stored in @b ctx->config_byte ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_adc_write_config_byte ( dcmotor22_t *ctx, uint8_t config_byte );

/**
 * @brief DC Motor 22 ADC set channel function.
 * @details This function sets the selected channel active by modifying the config byte.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] channel : Channel number (0-1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_adc_set_channel ( dcmotor22_t *ctx, uint8_t channel );

/**
 * @brief DC Motor 22 ADC get voltage function.
 * @details This function reads the voltage from the previously selected channel 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[out] voltage : Voltage value [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_adc_get_voltage ( dcmotor22_t *ctx, float *voltage );

/**
 * @brief DC Motor 22 get motor current function.
 * @details This function reads the current consumption of the selected motor.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] motor_sel : Motor selection @li @c 0 - Motor A,
 *                                        @li @c 1 - Motor B.
 * @param[out] current : Current value [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_get_motor_current ( dcmotor22_t *ctx, uint8_t motor_sel, float *current );

/**
 * @brief DC Motor 22 set motor pwm function.
 * @details This function sets the PWM duty cycle of the selected motor.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] motor_sel : Motor selection @li @c 0 - Motor A,
 *                                        @li @c 1 - Motor B.
 * @param[in] pwm_duty : PWM duty in range -255 to +255 [-100% to 100%].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor22_set_motor_pwm ( dcmotor22_t *ctx, uint8_t motor_sel, int16_t pwm_duty );

/**
 * @brief DC Motor 22 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor22_enable_device ( dcmotor22_t *ctx );

/**
 * @brief DC Motor 22 disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor22_disable_device ( dcmotor22_t *ctx );

/**
 * @brief DC Motor 22 reset device function.
 * @details This function resets the device by toggling the EN pin state.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor22_reset_device ( dcmotor22_t *ctx );

/**
 * @brief DC Motor 22 set device address function.
 * @details This function sets the device address.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @param[in] addr : Device address in range 0 to 3.
 * @return None.
 * @note None.
 */
void dcmotor22_set_device_address ( dcmotor22_t *ctx, uint8_t addr );

/**
 * @brief DC Motor 22 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor22_get_int_pin ( dcmotor22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR22_H

/*! @} */ // dcmotor22

// ------------------------------------------------------------------------ END

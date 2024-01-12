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
 * @file ltecat12.h
 * @brief This file contains API for LTE Cat.1 2 Click Driver.
 */

#ifndef LTECAT12_H
#define LTECAT12_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup ltecat12 LTE Cat.1 2 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 2 Click driver.
 * @{
 */

/**
 * @defgroup ltecat12_cmd LTE Cat.1 2 Device Settings
 * @brief Settings for registers of LTE Cat.1 2 Click driver.
 */

/**
 * @addtogroup ltecat12_cmd
 * @{
 */

/**
 * @brief LTE Cat.1 2 MAX9860 registers.
 * @details Specified MAX9860 registers for control commands of LTE Cat.1 2 Click driver.
 */
#define LTECAT12_MAX9860_REG_INTR_STATS             0x00
#define LTECAT12_MAX9860_REG_MIC_NG_AGC             0x01
#define LTECAT12_MAX9860_REG_INTR_EN                0x02
#define LTECAT12_MAX9860_REG_SYS_CLK                0x03
#define LTECAT12_MAX9860_REG_STEREO_CLK_MSB         0x04
#define LTECAT12_MAX9860_REG_STEREO_CLK_LSB         0x05
#define LTECAT12_MAX9860_REG_AUDIO_INTERFACE_1      0x06
#define LTECAT12_MAX9860_REG_AUDIO_INTERFACE_2      0x07
#define LTECAT12_MAX9860_REG_VOICE_FILTER           0x08
#define LTECAT12_MAX9860_REG_DAC_ATTENUATION        0x09
#define LTECAT12_MAX9860_REG_ADC_OUTPUT_LEVELS      0x0A
#define LTECAT12_MAX9860_REG_DAC_GAIN               0x0B
#define LTECAT12_MAX9860_REG_MIC_GAIN               0x0C
#define LTECAT12_MAX9860_REG_MIC_AGC                0x0E
#define LTECAT12_MAX9860_REG_NOISE_GATE             0x0F
#define LTECAT12_MAX9860_REG_SYS_SHUTDOWN           0x10

/**
 * @brief LTE Cat.1 2 control commands.
 * @details Specified setting for control commands of LTE Cat.1 2 Click driver.
 */
#define LTECAT12_CMD_AT                             "AT"
#define LTECAT12_CMD_ATI                            "ATI"
#define LTECAT12_CMD_CFUN                           "AT+CFUN"
#define LTECAT12_CMD_CREG                           "AT+CREG"
#define LTECAT12_CMD_CGDCONT                        "AT+CGDCONT"
#define LTECAT12_CMD_CESQ                           "AT+CESQ"
#define LTECAT12_CMD_COPS                           "AT+COPS"
#define LTECAT12_CMD_CMGS                           "AT+CMGS"
#define LTECAT12_CMD_CMGF                           "AT+CMGF"
#define LTECAT12_CMD_CGPADDR                        "AT+CGPADDR"
#define LTECAT12_CMD_SICA                           "AT^SICA"
#define LTECAT12_CMD_SISS                           "AT^SISS"
#define LTECAT12_CMD_SISO                           "AT^SISO"
#define LTECAT12_CMD_SISW                           "AT^SISW"
#define LTECAT12_CMD_SISR                           "AT^SISR"
#define LTECAT12_CMD_SISC                           "AT^SISC"
#define LTECAT12_CMD_SGPSC                          "AT^SGPSC"
#define LTECAT12_CMD_CHUP                           "AT+CHUP"
#define LTECAT12_CMD_SCFG                           "AT^SCFG"
#define LTECAT12_CMD_SAIC                           "AT^SAIC"
#define LTECAT12_CMD_SNFS                           "AT^SNFS"
#define LTECAT12_CMD_ATD                            "ATD"

/**
 * @brief LTE Cat.1 2 MAX9860 commands.
 * @details Specified setting for MAX9860 configuration of LTE Cat.1 2 Click driver.
 */
#define LTECAT12_PSCLK_12MHZ                        0x10
#define LTECAT12_LRCLK_8MHZ_MSB                     0x10
#define LTECAT12_LRCLK_8MHZ_LSB                     0x00
#define LTECAT12_DBCI_FALLING_EDGE                  0x20
#define LTECAT12_HIZ_ENABLE                         0x08
#define LTECAT12_TDM_ENABLE                         0x04
#define LTECAT12_ABCI_FALLING_EDGE                  0x20
#define LTECAT12_ADLY_ENABLE                        0x10
#define LTECAT12_STEREO_ENABLE                      0x08
#define LTECAT12_AVFLT_DISABLE                      0x00
#define LTECAT12_DVFLT_DISABLE                      0x00
#define LTECAT12_DVA_GAIN_0                         0x06
#define LTECAT12_ADC_GAIN_3                         0x00
#define LTECAT12_DAC_GAIN_0                         0x00
#define LTECAT12_DVST_GAIN_0                        0x01
#define LTECAT12_MIC_GAIN_0                         0x20
#define LTECAT12_PGAM_GAIN_0                        0x14
#define LTECAT12_AGCSRC_ENABLE                      0x80
#define LTECAT12_ANTH_DISABLE                       0x00
#define LTECAT12_AGCTH_MINUS_3                      0x00
#define LTECAT12_POWER_ON                           0x80
#define LTECAT12_DAC_ENABLE                         0x08
#define LTECAT12_ADCL_ADCR_ENABLE                   0x03

/**
 * @brief LTE Cat.1 2 pin state.
 * @details Specified setting for pin state of LTE Cat.1 2 Click driver.
 */
#define LTECAT12_PIN_STATE_HIGH                     0x01
#define LTECAT12_PIN_STATE_LOW                      0x00

/**
 * @brief LTE Cat.1 2 device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT12_RSP_OK                              "OK"
#define LTECAT12_RSP_ERROR                           "ERROR"
#define LTECAT12_RSP_SYSSTART                        "^SYSSTART"

/**
 * @brief LTE Cat.1 2 power state settings.
 * @details Specified power state settings of LTE Cat.1 2 Click driver.
 */
#define LTECAT12_POWER_STATE_SWITCH                  0
#define LTECAT12_POWER_STATE_ON                      1
#define LTECAT12_POWER_STATE_REBOOT                  2

/**
 * @brief LTE Cat.1 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT12_TX_DRV_BUFFER_SIZE                 300
#define LTECAT12_RX_DRV_BUFFER_SIZE                 300

/**
 * @brief LTE Cat.1 2 device address setting.
 * @details Specified setting for device slave address selection of
 * LTE Cat.1 2 Click driver.
 */
#define LTECAT12_ADDRESS                            0x10

/*! @} */ // ltecat12_cmd

/**
 * @defgroup ltecat12_map LTE Cat.1 2 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1 2 Click driver.
 */

/**
 * @addtogroup ltecat12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1 2 Click to the selected MikroBUS.
 */
#define LTECAT12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fsd = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat12_map
/*! @} */ // ltecat12

/**
 * @brief LTE Cat.1 2 Click context object.
 * @details Context object definition of LTE Cat.1 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rts;                  /**< UART ready to send pin. */
    digital_out_t fsd;                  /**< Fast shutdown pin. */

    // Input pins
    digital_in_t cts;                   /**< UART clear to send pin. */

    // Modules
    i2c_master_t i2c;                   /**< I2C driver object. */
    uart_t uart;                        /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address;              /**< Device slave address (used for I2C driver). */
    
    // Buffers
    uint8_t uart_rx_buffer[ LTECAT12_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT12_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} ltecat12_t;

/**
 * @brief LTE Cat.1 2 Click configuration object.
 * @details Configuration object definition of LTE Cat.1 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t cts;                     /**< UART clear to send pin. */
    pin_name_t fsd;                     /**< Fast shutdown pin. */
    pin_name_t rts;                     /**< UART ready to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */
    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */
    
} ltecat12_cfg_t;

/**
 * @brief LTE Cat.1 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT12_OK = 0,
    LTECAT12_ERROR = -1,
    LTECAT12_ERROR_TIMEOUT = -2,
    LTECAT12_ERROR_CMD = -3,
    LTECAT12_ERROR_UNKNOWN = -4

} ltecat12_return_value_t;

/*!
 * @addtogroup ltecat12 LTE Cat.1 2 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 2 Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat12_cfg_setup ( ltecat12_cfg_t *cfg );

/**
 * @brief LTE Cat.1 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat12_init ( ltecat12_t *ctx, ltecat12_cfg_t *cfg );

/**
 * @brief LTE Cat.1 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat12_generic_write ( ltecat12_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.1 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat12_generic_read ( ltecat12_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE Cat.1 2 MAX9860 writing function.
 * @details This function writes a data byte into the selected register address.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat12_write_register ( ltecat12_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LTE Cat.1 2 MAX9860 reading function.
 * @details This function reads a data byte from the selected register address.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat12_read_register ( ltecat12_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LTE Cat.1 2 MAX9860 configuration function.
 * @details This function is used to set basic config for MAX9860 of LTE Cat.1 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Some gain levels need to be configured for different headphones.
 */
err_t ltecat12_max9860_cfg ( ltecat12_t *ctx );

/**
 * @brief LTE Cat.1 2 set fsd pin function.
 * @details This function sets the FSD pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note In order to use this pin you need to add R27.
 */
void ltecat12_set_fsd_pin ( ltecat12_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 2 set rts pin function.
 * @details This function sets the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat12_set_rts_pin ( ltecat12_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 2 get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat12_get_cts_pin ( ltecat12_t *ctx );

/**
 * @brief LTE Cat.1 2 send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void ltecat12_send_cmd ( ltecat12_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 2 send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat12_send_cmd_with_params ( ltecat12_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief LTE Cat.1 2 check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat12_send_cmd_check ( ltecat12_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief LTE Cat.1 2 check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat12_send_cmd_parameter_check ( ltecat12_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief LTE Cat.1 2 set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat12_set_sim_apn ( ltecat12_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.1 2 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat12_send_sms_text ( ltecat12_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1 2 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat12_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat12_send_sms_pdu ( ltecat12_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTECAT12_H

/*! @} */ // ltecat12

// ------------------------------------------------------------------------ END

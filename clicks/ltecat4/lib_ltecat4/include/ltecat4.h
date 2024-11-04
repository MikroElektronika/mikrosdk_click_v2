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
 * @file ltecat4.h
 * @brief This file contains API for LTE Cat.4 Click Driver.
 */

#ifndef LTECAT4_H
#define LTECAT4_H

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
#include "drv_uart.h"

/*!
 * @addtogroup ltecat4 LTE Cat.4 Click Driver
 * @brief API for configuring and manipulating LTE Cat.4 Click driver.
 * @{
 */

/**
 * @defgroup ltecat4_cmd LTE Cat.4 Device Settings
 * @brief Settings for registers of LTE Cat.4 Click driver.
 */

/**
 * @addtogroup ltecat4_cmd
 * @{
 */

/**
 * @brief LTE Cat.4 MAX9860 registers.
 * @details Specified MAX9860 registers for control commands of LTE Cat.4 Click driver.
 */
#define LTECAT4_MAX9860_REG_INTR_STATS              0x00
#define LTECAT4_MAX9860_REG_MIC_NG_AGC              0x01
#define LTECAT4_MAX9860_REG_INTR_EN                 0x02
#define LTECAT4_MAX9860_REG_SYS_CLK                 0x03
#define LTECAT4_MAX9860_REG_STEREO_CLK_MSB          0x04
#define LTECAT4_MAX9860_REG_STEREO_CLK_LSB          0x05
#define LTECAT4_MAX9860_REG_AUDIO_INTERFACE_1       0x06
#define LTECAT4_MAX9860_REG_AUDIO_INTERFACE_2       0x07
#define LTECAT4_MAX9860_REG_VOICE_FILTER            0x08
#define LTECAT4_MAX9860_REG_DAC_ATTENUATION         0x09
#define LTECAT4_MAX9860_REG_ADC_OUTPUT_LEVELS       0x0A
#define LTECAT4_MAX9860_REG_DAC_GAIN                0x0B
#define LTECAT4_MAX9860_REG_MIC_GAIN                0x0C
#define LTECAT4_MAX9860_REG_MIC_AGC                 0x0E
#define LTECAT4_MAX9860_REG_NOISE_GATE              0x0F
#define LTECAT4_MAX9860_REG_SYS_SHUTDOWN            0x10

/**
 * @brief LTE Cat.4 MAX9860 commands.
 * @details Specified setting for MAX9860 configuration of LTE Cat.4 Click driver.
 */
#define LTECAT4_PSCLK_24MHZ                         0x20
#define LTECAT4_LRCLK_8MHZ_MSB                      0x10
#define LTECAT4_LRCLK_8MHZ_LSB                      0x62
#define LTECAT4_DBCI_FALLING_EDGE                   0x20
#define LTECAT4_HIZ_ENABLE                          0x08
#define LTECAT4_TDM_ENABLE                          0x04
#define LTECAT4_ABCI_FALLING_EDGE                   0x20
#define LTECAT4_ADLY_ENABLE                         0x10
#define LTECAT4_STEREO_ENABLE                       0x08
#define LTECAT4_AVFLT_DISABLE                       0x00
#define LTECAT4_DVFLT_DISABLE                       0x00
#define LTECAT4_DVA_GAIN_0                          0x06
#define LTECAT4_ADC_GAIN_3                          0x00
#define LTECAT4_DAC_GAIN_0                          0x00
#define LTECAT4_DVST_GAIN_0                         0x01
#define LTECAT4_MIC_GAIN_30                         0x60
#define LTECAT4_PGAM_GAIN_20                        0x00
#define LTECAT4_AGCSRC_ENABLE                       0x80
#define LTECAT4_AGCHLD_50                           0x01
#define LTECAT4_ANTH_DISABLE                        0x00
#define LTECAT4_AGCTH_MINUS_3                       0x00
#define LTECAT4_POWER_ON                            0x80
#define LTECAT4_DAC_ENABLE                          0x08
#define LTECAT4_ADCL_ADCR_ENABLE                    0x03

/**
 * @brief LTE Cat.4 control commands.
 * @details Specified setting for control commands of LTE Cat.4 Click driver.
 */
#define LTECAT4_CMD_AT                              "AT"
#define LTECAT4_CMD_GET_MODEL_ID                    "AT+CGMM"
#define LTECAT4_CMD_GET_SW_VERSION                  "AT+CGMR"
#define LTECAT4_CMD_GET_SERIAL_NUM                  "AT+CGSN"
#define LTECAT4_CMD_FACTORY_RESET                   "AT&F"
#define LTECAT4_CMD_SET_UE_FUNCTIONALITY            "AT+CFUN"
#define LTECAT4_CMD_NETWORK_REGISTRATION            "AT+CREG"
#define LTECAT4_CMD_SIGNAL_QUALITY_REPORT           "AT+CSQ"
#define LTECAT4_CMD_OPERATOR_SELECTION              "AT+COPS"
#define LTECAT4_CMD_SEND_SMS                        "AT+CMGS"
#define LTECAT4_CMD_SELECT_SMS_FORMAT               "AT+CMGF"
#define LTECAT4_CMD_DEFINE_PDP_CONTEXT              "AT+CGDCONT"
#define LTECAT4_CMD_SHOW_PDP_ADDRESS                "AT+CGPADDR"
#define LTECAT4_CMD_ACTIVATE_PDP_CONTEXT            "AT+QIACT"
#define LTECAT4_CMD_OPEN_SOCKET                     "AT+QIOPEN"
#define LTECAT4_CMD_CLOSE_SOCKET                    "AT+QICLOSE"
#define LTECAT4_CMD_SEND_DATA                       "AT+QISEND"
#define LTECAT4_CMD_RECEIVE_DATA                    "AT+QIRD"
#define LTECAT4_CMD_TURN_ON_GNSS                    "AT+QGPS"
#define LTECAT4_CMD_ACQUIRE_NMEA_SENTENCES          "AT+QGPSGNMEA"
#define LTECAT4_CMD_SET_MIC_GAIN                    "AT+QMIC"
#define LTECAT4_CMD_CONFIG_AUDIO_INTERFACE          "AT+QDAI"
#define LTECAT4_CMD_DIAL_NUMBER                     "ATD"
#define LTECAT4_CMD_TERMINATE_CALL                  "ATH"
#define LTECAT4_CMD_ANSWER_CALL                     "ATA"
#define LTECAT4_CMD_LIST_CALLS                      "AT+CLCC"
#define LTECAT4_CMD_CONFIG_URC_INDICATION           "AT+QURCCFG"

/**
 * @brief LTE Cat.4 response buffer commands.
 * @details Specified response buffer commands of LTE Cat.4 Click driver.
 */
#define LTECAT4_RSP_START                           "$"
#define LTECAT4_RSP_DELIMITER                       ","
#define LTECAT4_RSP_END                             "\r\n"
#define LTECAT4_RSP_GGA                             "GGA"

/**
 * @brief LTE Cat.4 device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT4_RSP_OK                              "OK"
#define LTECAT4_RSP_ERROR                           "ERROR"

/**
 * @brief LTE Cat.4 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTECAT4_URC_RECEIVED_DATA                   "+QIURC:"
#define LTECAT4_URC_RING                            "RING"
#define LTECAT4_URC_NO_CARRIER                      "NO CARRIER"

/**
 * @brief LTE Cat.4 power state settings.
 * @details Specified power state settings of LTE Cat.4 Click driver.
 */
#define LTECAT4_POWER_STATE_OFF                     0
#define LTECAT4_POWER_STATE_ON                      1

/**
 * @brief LTE Cat.4 GGA command elements.
 * @details Specified GGA command elements of LTE Cat.4 Click driver.
 */
#define LTECAT4_GGA_ELEMENT_SIZE                    15
#define LTECAT4_GGA_TIME                            1
#define LTECAT4_GGA_LATITUDE                        2
#define LTECAT4_GGA_LATITUDE_SIDE                   3
#define LTECAT4_GGA_LONGITUDE                       4
#define LTECAT4_GGA_LONGITUDE_SIDE                  5
#define LTECAT4_GGA_QUALITY_INDICATOR               6
#define LTECAT4_GGA_NUMBER_OF_SATELLITES            7
#define LTECAT4_GGA_H_DILUTION_OF_POS               8
#define LTECAT4_GGA_ALTITUDE                        9
#define LTECAT4_GGA_ALTITUDE_UNIT                   10
#define LTECAT4_GGA_GEOIDAL_SEPARATION              11
#define LTECAT4_GGA_GEOIDAL_SEPARATION_UNIT         12
#define LTECAT4_GGA_TIME_SINCE_LAST_DGPS            13
#define LTECAT4_GGA_DGPS_REFERENCE_STATION_ID       14

/**
 * @brief LTE Cat.4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT4_TX_DRV_BUFFER_SIZE                  256
#define LTECAT4_RX_DRV_BUFFER_SIZE                  256

/**
 * @brief LTE Cat.4 device address setting.
 * @details Specified setting for device slave address selection of
 * LTE Cat.4 Click driver.
 */
#define LTECAT4_DEVICE_ADDRESS                      0x10

/*! @} */ // ltecat4_cmd

/**
 * @defgroup ltecat4_map LTE Cat.4 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.4 Click driver.
 */

/**
 * @addtogroup ltecat4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.4 Click to the selected MikroBUS.
 */
#define LTECAT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat4_map
/*! @} */ // ltecat4

/**
 * @brief LTE Cat.4 Click context object.
 * @details Context object definition of LTE Cat.4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;      /**< Power pin. */
    digital_out_t rts;      /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;      /**< Ring indicator pin. */
    digital_in_t cts;       /**< UART clear to send pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */
    uart_t uart;            /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

    // Buffers
    uint8_t uart_rx_buffer[ LTECAT4_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT4_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTECAT4_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} ltecat4_t;

/**
 * @brief LTE Cat.4 Click configuration object.
 * @details Configuration object definition of LTE Cat.4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t pwr;                     /**< Power pin. */
    pin_name_t rts;                     /**< UART ready to send pin. */
    pin_name_t ring;                    /**< Ring indicator pin. */
    pin_name_t cts;                     /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */
    uint32_t         i2c_speed;         /**< I2C serial speed. */
    uint8_t          i2c_address;       /**< I2C slave address. */

} ltecat4_cfg_t;

/**
 * @brief LTE Cat.4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT4_OK = 0,
    LTECAT4_ERROR = -1,
    LTECAT4_ERROR_TIMEOUT = -2,
    LTECAT4_ERROR_CMD = -3,
    LTECAT4_ERROR_UNKNOWN = -4

} ltecat4_return_value_t;

/*!
 * @addtogroup ltecat4 LTE Cat.4 Click Driver
 * @brief API for configuring and manipulating LTE Cat.4 Click driver.
 * @{
 */

/**
 * @brief LTE Cat.4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat4_cfg_setup ( ltecat4_cfg_t *cfg );

/**
 * @brief LTE Cat.4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_init ( ltecat4_t *ctx, ltecat4_cfg_t *cfg );

/**
 * @brief LTE Cat.4 MAX9860 writing function.
 * @details This function writes a data byte into the selected register address.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_write_register ( ltecat4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LTE Cat.4 MAX9860 reading function.
 * @details This function reads a data byte from the selected register address.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_read_register ( ltecat4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LTE Cat.4 config codec function.
 * @details This function is used to set basic config for MAX9860 audio codec of 
 * LTE Cat.4 Click board.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Some gain levels need to be configured for different headphones.
 */
err_t ltecat4_config_codec ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_generic_write ( ltecat4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_generic_read ( ltecat4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE Cat.4 set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat4_set_pwr_pin ( ltecat4_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.4 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat4_set_rts_pin ( ltecat4_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.4 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat4_get_ring_pin ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat4_get_cts_pin ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 set power state function.
 * @details This function sets a desired power state by toggling PWR pin with a specific time for high state.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void ltecat4_set_power_state ( ltecat4_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void ltecat4_send_cmd ( ltecat4_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat4_send_cmd_par ( ltecat4_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat4_send_cmd_check ( ltecat4_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat4_set_sim_apn ( ltecat4_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.4 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat4_send_sms_text ( ltecat4_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.4 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_send_sms_pdu ( ltecat4_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.4 dial number.
 * @details This function dials the selected phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to dial.
 * @return Nothing.
 * @note None.
 */
void ltecat4_dial_number ( ltecat4_t *ctx, uint8_t *phone_number );

/**
 * @brief LTE Cat.4 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat4_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTECAT4_H

/*! @} */ // ltecat4

// ------------------------------------------------------------------------ END

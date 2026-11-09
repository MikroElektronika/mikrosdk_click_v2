/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file c5gredcap.h
 * @brief This file contains API for 5G RedCap Click Driver.
 */

#ifndef C5GREDCAP_H
#define C5GREDCAP_H

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
 * @addtogroup c5gredcap 5G RedCap Click Driver
 * @brief API for configuring and manipulating 5G RedCap Click driver.
 * @{
 */

/**
 * @defgroup c5gredcap_cmd 5G RedCap Device Settings
 * @brief Settings for registers of 5G RedCap Click driver.
 */

/**
 * @addtogroup c5gredcap_cmd
 * @{
 */

/**
 * @brief 5G RedCap MAX9860 registers.
 * @details Specified MAX9860 registers for control commands of 5G RedCap Click driver.
 */
#define C5GREDCAP_MAX9860_REG_INTR_STATS                0x00
#define C5GREDCAP_MAX9860_REG_MIC_NG_AGC                0x01
#define C5GREDCAP_MAX9860_REG_INTR_EN                   0x02
#define C5GREDCAP_MAX9860_REG_SYS_CLK                   0x03
#define C5GREDCAP_MAX9860_REG_STEREO_CLK_MSB            0x04
#define C5GREDCAP_MAX9860_REG_STEREO_CLK_LSB            0x05
#define C5GREDCAP_MAX9860_REG_AUDIO_INTERFACE_1         0x06
#define C5GREDCAP_MAX9860_REG_AUDIO_INTERFACE_2         0x07
#define C5GREDCAP_MAX9860_REG_VOICE_FILTER              0x08
#define C5GREDCAP_MAX9860_REG_DAC_ATTENUATION           0x09
#define C5GREDCAP_MAX9860_REG_ADC_OUTPUT_LEVELS         0x0A
#define C5GREDCAP_MAX9860_REG_DAC_GAIN                  0x0B
#define C5GREDCAP_MAX9860_REG_MIC_GAIN                  0x0C
#define C5GREDCAP_MAX9860_REG_MIC_AGC                   0x0E
#define C5GREDCAP_MAX9860_REG_NOISE_GATE                0x0F
#define C5GREDCAP_MAX9860_REG_SYS_SHUTDOWN              0x10

/**
 * @brief 5G RedCap MAX9860 commands.
 * @details Specified setting for MAX9860 configuration of 5G RedCap Click driver.
 */
#define C5GREDCAP_PSCLK_24MHZ                           0x20
#define C5GREDCAP_LRCLK_8KHZ_MSB                        0x10
#define C5GREDCAP_LRCLK_8KHZ_LSB                        0x62
#define C5GREDCAP_DBCI_FALLING_EDGE                     0x20
#define C5GREDCAP_HIZ_ENABLE                            0x08
#define C5GREDCAP_TDM_ENABLE                            0x04
#define C5GREDCAP_ABCI_FALLING_EDGE                     0x20
#define C5GREDCAP_ADLY_ENABLE                           0x10
#define C5GREDCAP_STEREO_ENABLE                         0x08
#define C5GREDCAP_AVFLT_DISABLE                         0x00
#define C5GREDCAP_DVFLT_DISABLE                         0x00
#define C5GREDCAP_DVA_GAIN_0                            0x06
#define C5GREDCAP_ADC_GAIN_3                            0x00
#define C5GREDCAP_DAC_GAIN_0                            0x00
#define C5GREDCAP_DVST_GAIN_0                           0x01
#define C5GREDCAP_MIC_GAIN_30                           0x60
#define C5GREDCAP_PGAM_GAIN_20                          0x00
#define C5GREDCAP_AGCSRC_ENABLE                         0x80
#define C5GREDCAP_AGCHLD_50                             0x01
#define C5GREDCAP_ANTH_DISABLE                          0x00
#define C5GREDCAP_AGCTH_MINUS_3                         0x00
#define C5GREDCAP_POWER_ON                              0x80
#define C5GREDCAP_DAC_ENABLE                            0x08
#define C5GREDCAP_ADCL_ADCR_ENABLE                      0x03

/**
 * @brief 5G RedCap control commands.
 * @details Specified setting for control commands of 5G RedCap Click driver.
 */
#define C5GREDCAP_CMD_AT                                "AT"
#define C5GREDCAP_CMD_GET_MODEL_ID                      "AT+CGMM"
#define C5GREDCAP_CMD_GET_SW_VERSION                    "AT+QGMR"
#define C5GREDCAP_CMD_GET_SERIAL_NUM                    "AT+CGSN"
#define C5GREDCAP_CMD_FACTORY_RESET                     "AT&F"
#define C5GREDCAP_CMD_SET_UE_FUNCTIONALITY              "AT+CFUN"
#define C5GREDCAP_CMD_NETWORK_REGISTRATION              "AT+CEREG"
#define C5GREDCAP_CMD_SIGNAL_QUALITY_REPORT             "AT+QCSQ"
#define C5GREDCAP_CMD_OPERATOR_SELECTION                "AT+COPS"
#define C5GREDCAP_CMD_SEND_SMS                          "AT+CMGS"
#define C5GREDCAP_CMD_SELECT_SMS_FORMAT                 "AT+CMGF"
#define C5GREDCAP_CMD_DEFINE_PDP_CONTEXT                "AT+CGDCONT"
#define C5GREDCAP_CMD_SHOW_PDP_ADDRESS                  "AT+CGPADDR"
#define C5GREDCAP_CMD_EXT_CONFIG                        "AT+QCFG"
#define C5GREDCAP_CMD_ACTIVATE_PDP_CONTEXT              "AT+QIACT"
#define C5GREDCAP_CMD_OPEN_SOCKET                       "AT+QIOPEN"
#define C5GREDCAP_CMD_CLOSE_SOCKET                      "AT+QICLOSE"
#define C5GREDCAP_CMD_SEND_DATA                         "AT+QISEND"
#define C5GREDCAP_CMD_RECEIVE_DATA                      "AT+QIRD"
#define C5GREDCAP_CMD_TURN_ON_GNSS                      "AT+QGPS"
#define C5GREDCAP_CMD_ACQUIRE_NMEA_SENTENCES            "AT+QGPSGNMEA"
#define C5GREDCAP_CMD_SET_MIC_GAIN                      "AT+QMIC"
#define C5GREDCAP_CMD_CONFIG_AUDIO_INTERFACE            "AT+QDAI"
#define C5GREDCAP_CMD_DIAL_NUMBER                       "ATD"
#define C5GREDCAP_CMD_TERMINATE_CALL                    "ATH"
#define C5GREDCAP_CMD_ANSWER_CALL                       "ATA"
#define C5GREDCAP_CMD_LIST_CALLS                        "AT+CLCC"
#define C5GREDCAP_CMD_CONFIG_URC_INDICATION             "AT+QURCCFG"

/**
 * @brief 5G RedCap response buffer commands.
 * @details Specified response buffer commands of 5G RedCap Click driver.
 */
#define C5GREDCAP_RSP_START                             "$"
#define C5GREDCAP_RSP_DELIMITER                         ","
#define C5GREDCAP_RSP_END                               "\r\n"
#define C5GREDCAP_RSP_GGA                               "GGA"

/**
 * @brief 5G RedCap device response for AT commands.
 * @details Device response after commands.
 */
#define C5GREDCAP_RSP_OK                                "OK"
#define C5GREDCAP_RSP_ERROR                             "ERROR"

/**
 * @brief 5G RedCap device response time for AT commands.
 * @details Device response time after commands.
 */
#define C5GREDCAP_MAX_RSP_TIME_DEFAULT                  300ul
#define C5GREDCAP_MAX_RSP_TIME_COPS                     180000ul
#define C5GREDCAP_MAX_RSP_TIME_QIACT                    150000ul
#define C5GREDCAP_MAX_RSP_TIME_CFUN                     15000ul
#define C5GREDCAP_MAX_RSP_TIME_CMGS                     120000ul
#define C5GREDCAP_MAX_RSP_TIME_QICLOSE                  10000ul
#define C5GREDCAP_MAX_RSP_TIME_URC                      30000ul
#define C5GREDCAP_MAX_RSP_TIME_READY                    60000ul

/**
 * @brief 5G RedCap device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define C5GREDCAP_URC_OPEN_SOCKET                       "+QIOPEN: "
#define C5GREDCAP_URC_RECEIVED_DATA                     "+QIURC: \"recv\""
#define C5GREDCAP_URC_NETWORK_REGISTERED                "+CEREG: 2,1"
#define C5GREDCAP_URC_SMS_FORMAT_PDU                    "+CMGF: 0"
#define C5GREDCAP_URC_SMS_FORMAT_TXT                    "+CMGF: 1"
#define C5GREDCAP_URC_RING                              "RING"
#define C5GREDCAP_URC_NO_CARRIER                        "NO CARRIER"
#define C5GREDCAP_URC_RDY                               "RDY"

/**
 * @brief 5G RedCap power state settings.
 * @details Specified power state settings of 5G RedCap Click driver.
 */
#define C5GREDCAP_POWER_STATE_OFF                       0
#define C5GREDCAP_POWER_STATE_ON                        1
#define C5GREDCAP_POWER_STATE_RESET                     2

/**
 * @brief 5G RedCap GGA command elements.
 * @details Specified GGA command elements of 5G RedCap Click driver.
 */
#define C5GREDCAP_GGA_ELEMENT_SIZE                      15
#define C5GREDCAP_GGA_TIME                              1
#define C5GREDCAP_GGA_LATITUDE                          2
#define C5GREDCAP_GGA_LATITUDE_SIDE                     3
#define C5GREDCAP_GGA_LONGITUDE                         4
#define C5GREDCAP_GGA_LONGITUDE_SIDE                    5
#define C5GREDCAP_GGA_QUALITY_INDICATOR                 6
#define C5GREDCAP_GGA_NUMBER_OF_SATELLITES              7
#define C5GREDCAP_GGA_H_DILUTION_OF_POS                 8
#define C5GREDCAP_GGA_ALTITUDE                          9
#define C5GREDCAP_GGA_ALTITUDE_UNIT                     10
#define C5GREDCAP_GGA_GEOIDAL_SEPARATION                11
#define C5GREDCAP_GGA_GEOIDAL_SEPARATION_UNIT           12
#define C5GREDCAP_GGA_TIME_SINCE_LAST_DGPS              13
#define C5GREDCAP_GGA_DGPS_REFERENCE_STATION_ID         14

/**
 * @brief 5G RedCap driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define C5GREDCAP_TX_DRV_BUFFER_SIZE                    256
#define C5GREDCAP_RX_DRV_BUFFER_SIZE                    256

/**
 * @brief 5G RedCap device address setting.
 * @details Specified setting for device slave address selection of
 * 5G RedCap Click driver.
 */
#define C5GREDCAP_DEVICE_ADDRESS                        0x10

/*! @} */ // c5gredcap_cmd

/**
 * @defgroup c5gredcap_map 5G RedCap MikroBUS Map
 * @brief MikroBUS pin mapping of 5G RedCap Click driver.
 */

/**
 * @addtogroup c5gredcap_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 5G RedCap Click to the selected MikroBUS.
 */
#define C5GREDCAP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // c5gredcap_map
/*! @} */ // c5gredcap

/**
 * @brief 5G RedCap Click context object.
 * @details Context object definition of 5G RedCap Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;      /**< PWRKEY pin (active high). */
    digital_out_t rst;      /**< Reset pin (active low). */
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
    uint8_t uart_rx_buffer[ C5GREDCAP_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ C5GREDCAP_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    uint8_t cmd_buffer[ C5GREDCAP_TX_DRV_BUFFER_SIZE ];     /**< Command buffer. */

} c5gredcap_t;

/**
 * @brief 5G RedCap Click configuration object.
 * @details Configuration object definition of 5G RedCap Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t pwr;                     /**< PWRKEY pin (active high). */
    pin_name_t rst;                     /**< Reset pin (active low). */
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

} c5gredcap_cfg_t;

/**
 * @brief 5G RedCap Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C5GREDCAP_OK = 0,
    C5GREDCAP_ERROR = -1,
    C5GREDCAP_ERROR_TIMEOUT = -2,
    C5GREDCAP_ERROR_CMD = -3

} c5gredcap_return_value_t;

/*!
 * @addtogroup c5gredcap 5G RedCap Click Driver
 * @brief API for configuring and manipulating 5G RedCap Click driver.
 * @{
 */

/**
 * @brief 5G RedCap configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c5gredcap_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c5gredcap_cfg_setup ( c5gredcap_cfg_t *cfg );

/**
 * @brief 5G RedCap initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c5gredcap_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_init ( c5gredcap_t *ctx, c5gredcap_cfg_t *cfg );

/**
 * @brief 5G RedCap MAX9860 writing function.
 * @details This function writes a data byte into the selected register address.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_write_register ( c5gredcap_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 5G RedCap MAX9860 reading function.
 * @details This function reads a data byte from the selected register address.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_read_register ( c5gredcap_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 5G RedCap config codec function.
 * @details This function is used to set basic config for MAX9860 audio codec of 
 * 5G RedCap Click board.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Some gain levels need to be configured for different headphones.
 */
err_t c5gredcap_config_codec ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_generic_write ( c5gredcap_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief 5G RedCap data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_generic_read ( c5gredcap_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief 5G RedCap set PWR pin function.
 * @details This function sets the PWR (PWRKEY) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c5gredcap_set_pwr_pin ( c5gredcap_t *ctx, uint8_t state );

/**
 * @brief 5G RedCap set RST pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c5gredcap_set_rst_pin ( c5gredcap_t *ctx, uint8_t state );

/**
 * @brief 5G RedCap set RTS pin function.
 * @details This function sets the ready to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c5gredcap_set_rts_pin ( c5gredcap_t *ctx, uint8_t state );

/**
 * @brief 5G RedCap get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c5gredcap_get_ring_pin ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c5gredcap_get_cts_pin ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap set power state function.
 * @details This function sets a desired power state by toggling PWR and RST pins with a specific time frame.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void c5gredcap_set_power_state ( c5gredcap_t *ctx, uint8_t state );

/**
 * @brief 5G RedCap cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void c5gredcap_cmd_run ( c5gredcap_t *ctx, uint8_t *cmd );

/**
 * @brief 5G RedCap cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void c5gredcap_cmd_set ( c5gredcap_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief 5G RedCap cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void c5gredcap_cmd_get ( c5gredcap_t *ctx, uint8_t *cmd );

/**
 * @brief 5G RedCap cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void c5gredcap_cmd_help ( c5gredcap_t *ctx, uint8_t *cmd );

/**
 * @brief 5G RedCap set sim card APN function.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void c5gredcap_set_sim_apn ( c5gredcap_t *ctx, uint8_t *sim_apn );

/**
 * @brief 5G RedCap send SMS in text mode function.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void c5gredcap_send_sms_text ( c5gredcap_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief 5G RedCap send SMS in PDU mode function.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_send_sms_pdu ( c5gredcap_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief 5G RedCap dial number function.
 * @details This function dials the selected phone number.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to dial.
 * @return Nothing.
 * @note None.
 */
void c5gredcap_dial_number ( c5gredcap_t *ctx, uint8_t *phone_number );

/**
 * @brief 5G RedCap parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gredcap_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // C5GREDCAP_H

/*! @} */ // c5gredcap

// ------------------------------------------------------------------------ END

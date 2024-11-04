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
 * @file ltecat13aux.h
 * @brief This file contains API for LTE Cat.1 3 AUX Click Driver.
 */

#ifndef LTECAT13AUX_H
#define LTECAT13AUX_H

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
 * @addtogroup ltecat13aux LTE Cat.1 3 AUX Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 3 AUX Click driver.
 * @{
 */

/**
 * @defgroup ltecat13aux_cmd LTE Cat.1 3 AUX Device Settings
 * @brief Settings for registers of LTE Cat.1 3 AUX Click driver.
 */

/**
 * @addtogroup ltecat13aux_cmd
 * @{
 */

/**
 * @brief LTE Cat.1 3 AUX MAX9860 registers.
 * @details Specified MAX9860 registers for control commands of LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_MAX9860_REG_INTR_STATS             0x00
#define LTECAT13AUX_MAX9860_REG_MIC_NG_AGC             0x01
#define LTECAT13AUX_MAX9860_REG_INTR_EN                0x02
#define LTECAT13AUX_MAX9860_REG_SYS_CLK                0x03
#define LTECAT13AUX_MAX9860_REG_STEREO_CLK_MSB         0x04
#define LTECAT13AUX_MAX9860_REG_STEREO_CLK_LSB         0x05
#define LTECAT13AUX_MAX9860_REG_AUDIO_INTERFACE_1      0x06
#define LTECAT13AUX_MAX9860_REG_AUDIO_INTERFACE_2      0x07
#define LTECAT13AUX_MAX9860_REG_VOICE_FILTER           0x08
#define LTECAT13AUX_MAX9860_REG_DAC_ATTENUATION        0x09
#define LTECAT13AUX_MAX9860_REG_ADC_OUTPUT_LEVELS      0x0A
#define LTECAT13AUX_MAX9860_REG_DAC_GAIN               0x0B
#define LTECAT13AUX_MAX9860_REG_MIC_GAIN               0x0C
#define LTECAT13AUX_MAX9860_REG_MIC_AGC                0x0E
#define LTECAT13AUX_MAX9860_REG_NOISE_GATE             0x0F
#define LTECAT13AUX_MAX9860_REG_SYS_SHUTDOWN           0x10

/**
 * @brief LTE Cat.1 3 AUX control commands.
 * @details Specified setting for control commands of LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_CMD_AT                             "AT"
#define LTECAT13AUX_CMD_ATI                            "ATI"
#define LTECAT13AUX_CMD_CFUN                           "AT+CFUN"
#define LTECAT13AUX_CMD_CREG                           "AT+CREG"
#define LTECAT13AUX_CMD_CGDCONT                        "AT+CGDCONT"
#define LTECAT13AUX_CMD_CSQ                            "AT+CSQ"
#define LTECAT13AUX_CMD_COPS                           "AT+COPS"
#define LTECAT13AUX_CMD_CMGS                           "AT+CMGS"
#define LTECAT13AUX_CMD_CMGF                           "AT+CMGF"
#define LTECAT13AUX_CMD_CGPADDR                        "AT+CGPADDR"
#define LTECAT13AUX_CMD_QIACT                          "AT+QIACT"
#define LTECAT13AUX_CMD_CHUP                           "AT+CHUP"
#define LTECAT13AUX_CMD_QIRD                           "AT+QIRD"
#define LTECAT13AUX_CMD_QIGETERROR                     "AT+QIGETERROR"
#define LTECAT13AUX_CMD_QICSGP                         "AT+QICSGP"
#define LTECAT13AUX_CMD_QIOPEN                         "AT+QIOPEN"
#define LTECAT13AUX_CMD_QISEND                         "AT+QISEND"
#define LTECAT13AUX_CMD_QICLOSE                        "AT+QICLOSE"
#define LTECAT13AUX_CMD_CLCC                           "AT+CLCC"
#define LTECAT13AUX_CMD_QGPSGNMEA                      "AT+QGPSGNMEA"
#define LTECAT13AUX_CMD_CSCS                           "AT+CSCS"
#define LTECAT13AUX_CMD_QGPS                           "AT+QGPS"
#define LTECAT13AUX_CMD_ATD                            "ATD"

/**
 * @brief LTE Cat.1 3 AUX MAX9860 commands.
 * @details Specified setting for MAX9860 configuration of LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_PSCLK_24MHZ                        0x20
#define LTECAT13AUX_LRCLK_8MHZ_MSB                     0x10
#define LTECAT13AUX_LRCLK_8MHZ_LSB                     0x62
#define LTECAT13AUX_DBCI_FALLING_EDGE                  0x20
#define LTECAT13AUX_HIZ_ENABLE                         0x08
#define LTECAT13AUX_TDM_ENABLE                         0x04
#define LTECAT13AUX_ABCI_FALLING_EDGE                  0x20
#define LTECAT13AUX_ADLY_ENABLE                        0x10
#define LTECAT13AUX_STEREO_ENABLE                      0x08
#define LTECAT13AUX_AVFLT_DISABLE                      0x00
#define LTECAT13AUX_DVFLT_DISABLE                      0x00
#define LTECAT13AUX_DVA_GAIN_0                         0x06
#define LTECAT13AUX_ADC_GAIN_3                         0x00
#define LTECAT13AUX_DAC_GAIN_0                         0x00
#define LTECAT13AUX_DVST_GAIN_0                        0x01
#define LTECAT13AUX_MIC_GAIN_0                         0x20
#define LTECAT13AUX_PGAM_GAIN_0                        0x14
#define LTECAT13AUX_AGCSRC_ENABLE                      0x80
#define LTECAT13AUX_ANTH_DISABLE                       0x00
#define LTECAT13AUX_AGCTH_MINUS_3                      0x00
#define LTECAT13AUX_POWER_ON                           0x80
#define LTECAT13AUX_DAC_ENABLE                         0x08
#define LTECAT13AUX_ADCL_ADCR_ENABLE                   0x03

/**
 * @brief LTE Cat.1 3 AUX pin state.
 * @details Specified setting for pin state of LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_PIN_STATE_HIGH                     0x01
#define LTECAT13AUX_PIN_STATE_LOW                      0x00

/**
 * @brief LTE Cat.1 3 AUX response buffer commands.
 * @details Specified response buffer commands of LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_RSP_START                          "$"
#define LTECAT13AUX_RSP_DELIMITER                      ","
#define LTECAT13AUX_RSP_GPGGA                          "$GPGGA"

/**
 * @brief LTE Cat.1 3 AUX GPGGA command elements.
 * @details Specified GPGGA command elements of LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_GPGGA_ELEMENT_SIZE                 15
#define LTECAT13AUX_GPGGA_TIME                         1 
#define LTECAT13AUX_GPGGA_LATITUDE                     2
#define LTECAT13AUX_GPGGA_LATITUDE_SIDE                3
#define LTECAT13AUX_GPGGA_LONGITUDE                    4
#define LTECAT13AUX_GPGGA_LONGITUDE_SIDE               5
#define LTECAT13AUX_GPGGA_QUALITY_INDICATOR            6
#define LTECAT13AUX_GPGGA_NUMBER_OF_SATELLITES         7
#define LTECAT13AUX_GPGGA_H_DILUTION_OF_POS            8
#define LTECAT13AUX_GPGGA_ALTITUDE                     9
#define LTECAT13AUX_GPGGA_ALTITUDE_UNIT                10
#define LTECAT13AUX_GPGGA_GEOIDAL_SEPARATION           11
#define LTECAT13AUX_GPGGA_GEOIDAL_SEPARATION_UNIT      12
#define LTECAT13AUX_GPGGA_TIME_SINCE_LAST_DGPS         13
#define LTECAT13AUX_GPGGA_DGPS_REFERENCE_STATION_ID    14

/**
 * @brief LTE Cat.1 3 AUX device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT13AUX_RSP_OK                              "OK"
#define LTECAT13AUX_RSP_ERROR                           "ERROR"
#define LTECAT13AUX_RSP_RDY                             "RDY"
#define LTECAT13AUX_RSP_SEND_OK                         "SEND OK"

/**
 * @brief LTE Cat.1 3 AUX Pin state.
 * @details Specified pin states.
 */
#define LTECAT13AUX_PIN_STATE_HIGH                     0x01    
#define LTECAT13AUX_PIN_STATE_LOW                      0x00    

/**
 * @brief LTE Cat.1 3 AUX driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT13AUX_TX_DRV_BUFFER_SIZE                 200
#define LTECAT13AUX_RX_DRV_BUFFER_SIZE                 300

/**
 * @brief LTE Cat.1 3 AUX device address setting.
 * @details Specified setting for device slave address selection of
 * LTE Cat.1 3 AUX Click driver.
 */
#define LTECAT13AUX_ADDRESS                            0x10

/*! @} */ // ltecat13aux_cmd

/**
 * @defgroup ltecat13aux_map LTE Cat.1 3 AUX MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1 3 AUX Click driver.
 */

/**
 * @addtogroup ltecat13aux_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1 3 AUX Click to the selected MikroBUS.
 */
#define LTECAT13AUX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ri  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat13aux_map
/*! @} */ // ltecat13aux

/**
 * @brief LTE Cat.1 3 AUX Click context object.
 * @details Context object definition of LTE Cat.1 3 AUX Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;      /**< Power pin. */
    digital_out_t rts;      /**< UART ready to send pin. */

    // Input pins
    digital_in_t ri;        /**< Ring indicator pin. */
    digital_in_t cts;       /**< UART clear to send pin. */

    // Modules]
    i2c_master_t i2c;       /**< I2C driver object. */
    uart_t uart;            /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

    // Buffers
    uint8_t uart_rx_buffer[ LTECAT13AUX_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT13AUX_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} ltecat13aux_t;

/**
 * @brief LTE Cat.1 3 AUX Click configuration object.
 * @details Configuration object definition of LTE Cat.1 3 AUX Click driver.
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
    pin_name_t ri;                      /**< Ring indicator pin. */
    pin_name_t cts;                     /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */
    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

} ltecat13aux_cfg_t;

/**
 * @brief LTE Cat.1 3 AUX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT13AUX_OK = 0,
    LTECAT13AUX_ERROR = -1,
    LTECAT13AUX_ERROR_TIMEOUT = -2,
    LTECAT13AUX_ERROR_CMD = -3,
    LTECAT13AUX_ERROR_UNKNOWN = -4

} ltecat13aux_return_value_t;

/*!
 * @addtogroup ltecat13aux LTE Cat.1 3 AUX Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 3 AUX Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1 3 AUX configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat13aux_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat13aux_cfg_setup ( ltecat13aux_cfg_t *cfg );

/**
 * @brief LTE Cat.1 3 AUX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat13aux_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_init ( ltecat13aux_t *ctx, ltecat13aux_cfg_t *cfg );

/**
 * @brief LTE Cat.1 3 AUX data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_generic_write ( ltecat13aux_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.1 3 AUX data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_generic_read ( ltecat13aux_t *ctx, uint8_t *data_out, uint16_t len );


/**
 * @brief LTE Cat.1 3 AUX start up function.
 * @details This function is used to start device.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] pin_state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat13aux_start_up ( ltecat13aux_t *ctx );

/**
 * @brief LTE Cat.1 3 AUX set PWR pin function.
 * @details This function sets the PWR pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] pin_state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat13aux_set_pwr_pin ( ltecat13aux_t *ctx, uint8_t pin_state );

/**
 * @brief LTE Cat.1 3 AUX set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] pin_state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat13aux_set_rts_pin ( ltecat13aux_t *ctx, uint8_t pin_state );

/**
 * @brief LTE Cat.1 3 AUX get RI pin function.
 * @details This function returns the RI pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat13aux_get_ri_pin ( ltecat13aux_t *ctx );

/**
 * @brief LTE Cat.1 3 AUX get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat13aux_get_cts_pin ( ltecat13aux_t *ctx );

/**
 * @brief LTE Cat.1 3 AUX MAX9860 writing function.
 * @details This function writes a data byte into the selected register address.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_write_register ( ltecat13aux_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LTE Cat.1 3 AUX MAX9860 reading function.
 * @details This function reads a data byte from the selected register address.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_read_register ( ltecat13aux_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LTE Cat.1 3 AUX MAX9860 configuration function.
 * @details This function is used to set basic config for MAX9860 of LTE Cat.1 3 AUX
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Some gain levels need to be configured for different headphones.
 */
err_t ltecat13aux_max9860_cfg ( ltecat13aux_t *ctx );

/**
 * @brief LTE Cat.1 3 AUX send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void ltecat13aux_send_cmd ( ltecat13aux_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 3 AUX send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat13aux_send_cmd_with_params ( ltecat13aux_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief LTE Cat.1 3 AUX check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat13aux_send_cmd_check ( ltecat13aux_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief LTE Cat.1 3 AUX check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat13aux_send_cmd_param_check ( ltecat13aux_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief LTE Cat.1 3 AUX set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat13aux_set_sim_apn ( ltecat13aux_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.1 3 AUX send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat13aux_send_sms_text ( ltecat13aux_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1 3 AUX send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat13aux_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_send_sms_pdu ( ltecat13aux_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1  parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat13aux_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTECAT13AUX_H

/*! @} */ // ltecat13aux

// ------------------------------------------------------------------------ END

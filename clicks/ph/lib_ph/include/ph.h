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
 * @file ph.h
 * @brief This file contains API for pH Click Driver.
 */

#ifndef PH_H
#define PH_H

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
#include "drv_uart.h"

/*!
 * @addtogroup ph pH Click Driver
 * @brief API for configuring and manipulating pH Click driver.
 * @{
 */

/**
 * @defgroup ph_cmd pH Device Settings
 * @brief Settings for registers of pH Click driver.
 */

/**
 * @addtogroup ph_cmd
 * @{
 */

/**
 * @brief pH control commands.
 * @details Specified setting for control commands of pH Click driver.
 */
#define PH_CMD_CNG_BAUD_RATE  "Baud,"
#define PH_CMD_CHK_BAUD_RATE  "Baud,?"
#define PH_CMD_SET_CONT_READ  "C,"
#define PH_CMD_CHK_CONT_READ  "C,?"
#define PH_CMD_CALIB_PERF     "Cal"
#define PH_CMD_CALIB_MID      ",mid,"
#define PH_CMD_CALIB_LOW      ",low,"
#define PH_CMD_CALIB_HIGH     ",high,"
#define PH_CMD_CHK_CALIB      "Cal,?"
#define PH_CMD_CALIB_EXP      "Export"
#define PH_CMD_CHK_CALIB_EXP  "Export,?"
#define PH_CMD_CALIB_IMP      "Import,"
#define PH_CMD_EN_FTY_RST     "Factory"
#define PH_CMD_DEV_FIND       "Find"
#define PH_CMD_DEV_INFO       "i"
#define PH_CMD_CNG_I2C        "I2C,"
#define PH_CMD_EN_LED         "L,"
#define PH_CMD_CHK_LED        "L,?"
#define PH_CMD_SET_DEV_NAME   "Name,"
#define PH_CMD_GET_DEV_NAME   "Name,?"
#define PH_CMD_PROTOCOL_LOCK  "Plock,"
#define PH_CMD_PROTOCOL_CKH   "Plock,?"
#define PH_CMD_SET_SNGL_READ  "r"
#define PH_CMD_ENTER_SLEEP    "Sleep"
#define PH_CMD_RET_SLOPE      "Slope,?"
#define PH_CMD_READ_STATUS    "Status"
#define PH_CMD_TEMP_COMP      "T,"
#define PH_CMD_CHK_TEMP_COMP  "T,?"
#define PH_CMD_RSP_CODES      "*OK"
#define PH_CMD_EN_RSP_CODES   "*OK,1"
#define PH_CMD_DIS_RSP_CODES  "*OK,0"
#define PH_CMD_CHK_RSP_CODES  "*OK,?"
#define PH_CMD_END_COMMAND    "\r"

/**
 * @brief pH Response codes list.
 * @details Specified response codes list of pH Click driver.
 */
#define PH_RSP_CODE_ERROR     "*ER"
#define PH_RSP_CODE_OV_VOLT   "*OV"
#define PH_RSP_CODE_UN_VOLT   "*UV"
#define PH_RSP_CODE_RESET     "*RS"
#define PH_RSP_CODE_READY     "*RE"
#define PH_RSP_CODE_SLEEP_EN  "*SL"
#define PH_RSP_CODE_WAKE_UP   "*WA"
#define PH_RSP_CODE_ALL_GOOD  "*OK"
// Restart codes list

/**
 * @brief pH Restart codes list.
 * @details Specified restart codes list of pH Click driver.
 */
#define PH_RST_CODE_POW_OFF   "P"
#define PH_RST_CODE_SW_RST    "S"
#define PH_RST_CODE_BRWN_OUT  "B"
#define PH_RST_CODE_WTD       "W"
#define PH_RST_CODE_UNKNOWN   "U"

/**
 * @brief pH Baud rate list.
 * @details Specified baud rate list of pH Click driver.
 */
#define PH_BAUD_RATE_300            "300"
#define PH_BAUD_RATE_1200           "1200"
#define PH_BAUD_RATE_2400           "2400"
#define PH_BAUD_RATE_9600           "9600"
#define PH_BAUD_RATE_19200          "19200"
#define PH_BAUD_RATE_38400          "38400"
#define PH_BAUD_RATE_57600          "57600"
#define PH_BAUD_RATE_115200         "115200"

/**
 * @brief pH driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // ph_cmd

/**
 * @defgroup ph_map pH MikroBUS Map
 * @brief MikroBUS pin mapping of pH Click driver.
 */

/**
 * @addtogroup ph_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of pH Click to the selected MikroBUS.
 */
#define PH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )
/*! @} */ // ph_map
/*! @} */ // ph

/**
 * @brief pH Click context object.
 * @details Context object definition of pH Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} ph_t;

/**
 * @brief pH Click configuration object.
 * @details Configuration object definition of pH Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} ph_cfg_t;

/**
 * @brief pH Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PH_OK = 0,
    PH_ERROR = -1

} ph_return_value_t;

/*!
 * @addtogroup ph pH Click Driver
 * @brief API for configuring and manipulating pH Click driver.
 * @{
 */

/**
 * @brief pH configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ph_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ph_cfg_setup ( ph_cfg_t *cfg );

/**
 * @brief pH initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ph_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ph_init ( ph_t *ctx, ph_cfg_t *cfg );

/**
 * @brief pH default configuration function.
 * @details This function executes a default configuration of pH
 * click board.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ph_default_cfg ( ph_t *ctx );

/**
 * @brief pH data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ph_generic_write ( ph_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief pH data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ph_generic_read ( ph_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief UART Write Single Byte function.
 * @details Writes sinle byte.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] input : Byte for sending.
 * @return Nothing.
 */
void ph_uart_write ( ph_t *ctx, uint8_t input );

/**
 * @brief UART read until delimiter function.
 * @details Function reads data until it finds delimiter.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_tx_data : Pointer to output data.
 * @param[in] delim : Delimiter.
 * @return Nothing.
**/
void ph_uart_read_until ( ph_t *ctx, char *p_rx_data, char *delim );

/**
 * @brief Send command function
 * @details Function is used to send command and does not expect response.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] p_cmd : Pointer to input command
 * @return Nothing.
**/
void ph_send_cmd ( ph_t *ctx, char *p_cmd );

/**
 * @brief Send command and get response function.
 * @details Function is used to send command and gets the response.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] p_cmd : Pointer to input command.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_send_cmd_resp ( ph_t *ctx, char *p_cmd, char *p_resp );

/**
 * @brief Send command with number and get response function
 * @details Function is used to send command alongside floating point number
 * and gets the response.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param p_cmd  pointer to input command
 * @param name  flt_val input float value
 * @param[out] p_resp : Pointer to response.
 * @return Nothing. 
**/
void ph_send_cmd_w_num ( ph_t *ctx, char *p_cmd, char *flt_val, char *p_resp );

/**
 * @brief Send get response function.
 * @details Function is used to get response from a command.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] p_cmd : Pointer to input command.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing. 
**/
void ph_get_cmd_resp ( ph_t *ctx, char *p_cmd, char *p_resp );

/**
 * @brief Toggle LED function.
 * @details Function is used to turn LED on or off.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] state : Turns LED on or off
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_switch_led ( ph_t *ctx, uint8_t state, char *p_resp );

/**
 * @brief Check LED state function.
 * @details Function is used to check the state of the LED.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_chk_led_state ( ph_t *ctx, char *p_resp );

/**
 * @brief Find device function
 * @details Function is used to find the device.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note When the command is issued LED blinks white.
**/
void ph_find_dev ( ph_t *ctx, char *p_resp );

/**
 * @brief Set Continous read function
 * @details Function is used to enable, disable or change settings
 * of the continous read.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] time : Defines reading interval ranging from 1 to 90 seconds,
 *                   if 0 is applied continous reading is disabled.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_cont_read ( ph_t *ctx, uint8_t time, char *p_resp );

/**
 * @brief Check Continous read settings function.
 * @details Function is used to check the settings of the continous read.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_chk_cont_read ( ph_t *ctx, char *p_resp );

/**
 * @brief Perform Calibration function
 * @details Function is used to perform calibration.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] point : Pointer to calibration point ( mid, low or high ).
 * @param[in] flt_val : Float value representing calibration reference.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Cal,mid,n <cr> single point calibration at midpoint.
 *       Cal,low,n <cr> two point calibration at lowpoint.
 *       Cal,high,n <cr> three point calibration at highpoint.
**/
void ph_perf_calib ( ph_t *ctx, char *point, float flt_val, char *p_resp );

/**
 * @brief Check if Calibration was performed function
 * @details Function is used to check if calibration was performed.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note ?Cal,0 <cr> not calibrated.
 *       ?Cal,1 <cr> one point calibration performed.
 *       ?Cal,2 <cr> two point calibration performed.
 *       ?Cal,3 <cr> three point calibration performed.
**/
void ph_chk_calib ( ph_t *ctx, char *p_resp );

/**
 * @brief Check slope function
 * @details Function is used to check the slope of the probe.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_chk_slope ( ph_t *ctx, char *p_resp );

/**
 * @brief Export calibration data function
 * @details Function is used to export calibration data.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to exported calibration data
 * @return Nothing.
 * 
 * @note Up 10 12 byte strings to export.
**/
void ph_get_calib_exp_bytes_num ( ph_t *ctx, char *p_resp );

/**
 * @brief Import calibration data function.
 * @details Function is used to import calibration data.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] in_calib : Pointer to imported calibration data.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Up 10 12 byte strings to import.
**/
void ph_import_calib ( ph_t *ctx, uint8_t *in_calib, char *p_resp );

/**
 * @brief Perform Factory Reset function.
 * @details Function is used to perform factory reset.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_factory_rst ( ph_t *ctx, char *p_resp );

/**
 * @brief Set Temperature Compensation function.
 * @details Function is used to set temperature compensation.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] flt_val : Compensation temperature.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Temperature changes of < 2 deg C are insignificant.
 *       Temperature is always in degrees centigrade.
**/
void ph_set_temp_comp ( ph_t *ctx, float flt_val, char *p_resp );

/**
 * @brief Get Temperature Compensation function.
 * @details Function is used to get temperature compensation.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Temperature is always in degrees centigrade.
**/
void ph_get_temp_comp ( ph_t *ctx, char *p_resp );

/**
 * @brief Set name function.
 * @details Function is used to name the device.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] p_dev_name : Pointer to the devices name.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Must not exceed 16 ASCII characters.
**/
void ph_set_name ( ph_t *ctx, char *p_dev_name, char *p_resp );

/**
 * @brief Show Device Name function
 * @details Function is used to show the device's name.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] p_dev_name : Pointer to the devices name
 * @return Nothing.
**/
void ph_show_name ( ph_t *ctx, char *p_dev_name );

/**
 * @brief Get Device Information function
 * @details Function is used to read information about the device.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_get_dev_info ( ph_t *ctx, char *p_resp );

/**
 * @brief Check Device Status function.
 * @details Function is used to check status of the device.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_check_status ( ph_t *ctx, char *p_resp );

/**
 * @brief Enter Sleep mode function
 * @details Function is used to enter the sleep mode.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @return Nothing.
**/
void ph_sleep ( ph_t *ctx );

/**
 * @brief Change Baud Rate function.
 * @details Function is used to change the baud rate.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] baud_rate : Baud rate.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Default speed is 9600.
**/
void ph_chng_baud_rate ( ph_t *ctx, char *baud_rate, char *p_resp  );

/**
 * @brief Check Baud Rate applied function.
 * @details Function is used to check the baud rate.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
 * 
 * @note Default speed is 9600.
**/
void ph_chk_baud_rate ( ph_t *ctx, char *p_resp );

/**
 * @brief Protocol Lock enable/disable function.
 * @details Function is used to lock device to UART mode.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] state : lock/unlock the protocol.
 * @param[out] p_resp : Pointer to response.
 * @return Nothing.
**/
void ph_protocol_lock ( ph_t *ctx, uint8_t state, char *p_resp );

/**
 * @brief Check Protocol Lock function.
 * @details Function is used to check if the device is lock to UART mode.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to response. data.
 * @return Nothing.
**/
void ph_check_protocol_lock ( ph_t *ctx, char *p_resp );

/**
 * @brief Change Device's I2C slave address function.
 * @details Function is used to set I2C address and reboot into I2C mode.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[in] i2c_adr : Device slave address.
 * @param[out] p_resp : Pointer to response. data.
 * @return Nothing.
 * 
 * @note Default I2C address 99 (0x63).
**/
void ph_chng_i2c_adr ( ph_t *ctx, uint32_t i2c_adr, char *p_resp );

/**
 * @brief Perform single read function.
 * @details Function is used to perform single read of the pH value.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to pH value of the tested substance.
 * @return Nothing.
**/
void ph_single_read ( ph_t *ctx, char *p_resp );

/**
 * @brief pH Response handler function
 * @details Function is used to handle collected data.
 * @param[in] ctx : Click context object.
 * See #ph_t object definition for detailed explanation.
 * @param[out] p_resp : Pointer to collected data.
 * @returns Lenght of the read data.
**/
uint8_t ph_response ( ph_t *ctx, char *p_resp );

/**
 * @brief Clear log buffer function
 * @details Function is used to empty log's data buffer.
 * @param[in] p_str : Data buffer.
 * @return Nothing.
**/
void ph_clr_log_buf ( char *p_str );

#ifdef __cplusplus
}
#endif
#endif // PH_H

/*! @} */ // ph

// ------------------------------------------------------------------------ END

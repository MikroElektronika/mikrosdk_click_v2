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
 * @file adc10.h
 * @brief This file contains API for ADC 10 Click Driver.
 */

#ifndef ADC10_H
#define ADC10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"
    

/*!
 * @addtogroup adc10 ADC 10 Click Driver
 * @brief API for configuring and manipulating ADC 10 Click driver.
 * @{
 */

/**
 * @defgroup adc10_reg ADC 10 Commands List
 * @brief List of commands of ADC 10 Click driver.
 */

/**
 * @addtogroup adc10_reg
 * @{
 */

/**
 * @brief ADC 10 description register.
 * @details Specified register for description of ADC 10 Click driver.
 */
#define ADC10_REG_CONFIG_0                                          0x00 
#define ADC10_REG_CONFIG_1                                          0x01 
#define ADC10_REG_CONFIG_2                                          0x02 
#define ADC10_REG_CONFIG_3                                          0x03 
#define ADC10_REG_CONFIG_4                                          0x04 

/*! @} */ // adc10_reg

/**
 * @defgroup adc10_set ADC 10 Device Settings
 * @brief Settings for registers of ADC 10 Click driver.
 */

/**
 * @addtogroup adc10_set
 * @{
 */

/**
 * @brief ADC 10 commands description setting.
 * @details Specified commands setting for description 
 * of ADC 10 Click driver.
 */ 
#define ADC10_SYNC_WORD                                             0x55 
#define ADC10_CMD_RESET                                             0x06 
#define ADC10_CMD_START                                             0x08 
#define ADC10_CMD_POWERDOWN                                         0x03 
#define ADC10_CMD_RDATA                                             0x10 
#define ADC10_CMD_RREG                                              0x20 
#define ADC10_CMD_WREG                                              0x40 

/**
 * @brief ADC 10 Configuration Register 0 description setting.
 * @details Specified Input multiplexer configuration setting 
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG0_MUX_P0_N1                                        0x00 
#define ADC10_REG0_MUX_P0_N2                                        0x01 
#define ADC10_REG0_MUX_P0_N3                                        0x02 
#define ADC10_REG0_MUX_P1_N0                                        0x03 
#define ADC10_REG0_MUX_P1_N2                                        0x04 
#define ADC10_REG0_MUX_P1_N3                                        0x05 
#define ADC10_REG0_MUX_P2_N3                                        0x06 
#define ADC10_REG0_MUX_P3_N2                                        0x07 
#define ADC10_REG0_MUX_P0_NS                                        0x08 
#define ADC10_REG0_MUX_P1_NS                                        0x09 
#define ADC10_REG0_MUX_P2_NS                                        0x0A 
#define ADC10_REG0_MUX_P3_NS                                        0x0B 
#define ADC10_REG0_MUX_VREF                                         0x0C 
#define ADC10_REG0_MUX_AVOLD_4                                      0x0D 
#define ADC10_REG0_MUX_AVOLAVER                                     0x0E 
#define ADC10_REG0_MUX_RESERVE                                      0x0F

/**
 * @brief ADC 10 Configuration Register 0 description setting.
 * @details Specified Gain configuration setting 
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG0_GAIN_1                                           0x00 
#define ADC10_REG0_GAIN_2                                           0x01 
#define ADC10_REG0_GAIN_4                                           0x02 
#define ADC10_REG0_GAIN_8                                           0x03 
#define ADC10_REG0_GAIN_16                                          0x04 
#define ADC10_REG0_GAIN_32                                          0x05 
#define ADC10_REG0_GAIN_64                                          0x06 
#define ADC10_REG0_GAIN_128                                         0x07

/**
 * @brief ADC 10 Configuration Register 0 description setting.
 * @details Specified Disables and bypasses the internal low-noise PGA setting 
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG0_PGA_ENABLED                                      0x00 
#define ADC10_REG0_PGA_DISABLED                                     0x01 

/**
 * @brief ADC 10 Configuration Register 1 description setting.
 * @details Specified Data rate setting 
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG1_DR_NORMAL_20                                     0x00 
#define ADC10_REG1_DR_NORMAL_45                                     0x01 
#define ADC10_REG1_DR_NORMAL_90                                     0x02 
#define ADC10_REG1_DR_NORMAL_175                                    0x03 
#define ADC10_REG1_DR_NORMAL_330                                    0x04 
#define ADC10_REG1_DR_NORMAL_600                                    0x05 
#define ADC10_REG1_DR_NORMAL_1000                                   0x06 
#define ADC10_REG1_DR_TURBO_40                                      0x00 
#define ADC10_REG1_DR_TURBO_90                                      0x01 
#define ADC10_REG1_DR_TURBO_180                                     0x02 
#define ADC10_REG1_DR_TURBO_350                                     0x03 
#define ADC10_REG1_DR_TURBO_660                                     0x04 
#define ADC10_REG1_DR_TURBO_1200                                    0x05 
#define ADC10_REG1_DR_TURBO_2000                                    0x06 

/**
 * @brief ADC 10 Configuration Register 1 description setting.
 * @details Specified Operating mode
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG1_MODE_NORMAL                                      0x00 
#define ADC10_REG1_MODE_TURBO                                       0x01 

/**
 * @brief ADC 10 Configuration Register 1 description setting.
 * @details Specified Conversion mode
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG1_CM_SINGAL_SHOT                                   0x00 
#define ADC10_REG1_CM_CONTINUOUS                                    0x01 

/**
 * @brief ADC 10 Configuration Register 1 description setting.
 * @details Specified Voltage reference selection
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG1_VREF_INTERNAL_2048                               0x00 
#define ADC10_REG1_VREF_EXTERNAL_REF                                0x01 
#define ADC10_REG1_VREF_ANALOG_1                                    0x02 
#define ADC10_REG1_VREF_ANALOG_2                                    0x03 

/**
 * @brief ADC 10 Configuration Register 1 description setting.
 * @details Specified Temperature sensor mode
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG1_TS_DISABLED                                      0x00 
#define ADC10_REG1_TS_ENABLED                                       0x01 

/**
 * @brief ADC 10 Configuration Register 2 description setting.
 * @details Specified Conversion result ready flag
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG2_DRDY_NOT_READY                                   0x00 
#define ADC10_REG2_DRDY_READY                                       0x01 

/**
 * @brief ADC 10 Configuration Register 2 description setting.
 * @details Specified Data counter enable
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG2_DCNT_DISABLED                                    0x00 
#define ADC10_REG2_DCNT_ENABLED                                     0x01 

/**
 * @brief ADC 10 Configuration Register 2 description setting.
 * @details Specified Data integrity check enable
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG2_CRC_DISABLED                                     0x00 
#define ADC10_REG2_CRC_INVERTED_ENABLED                             0x01 
#define ADC10_REG2_CRC_CRC16_ENABLED                                0x02 
#define ADC10_REG2_CRC_RESERVED                                     0x03 

/**
 * @brief ADC 10 Configuration Register 2 description setting.
 * @details Specified Burn-out current sources
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG2_BCS_CURRENT_SOURCE_OFF                           0x00 
#define ADC10_REG2_BCS_CURRENT_SOURCE_ON                            0x01 

/**
 * @brief ADC 10 Configuration Register 2 description setting.
 * @details Specified IDAC current setting
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG2_IDAC_CURRENT_OFF                                 0x00 
#define ADC10_REG2_IDAC_CURRENT_10_uA                               0x01 
#define ADC10_REG2_IDAC_CURRENT_50_uA                               0x02 
#define ADC10_REG2_IDAC_CURRENT_100_uA                              0x03 
#define ADC10_REG2_IDAC_CURRENT_250_uA                              0x04 
#define ADC10_REG2_IDAC_CURRENT_500_uA                              0x05 
#define ADC10_REG2_IDAC_CURRENT_1000_uA                             0x06 
#define ADC10_REG2_IDAC_CURRENT_1500_uA                             0x07 

/**
 * @brief ADC 10 Configuration Register 3 description setting.
 * @details Specified IDAC1 routing configuration
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG3_L1MUX_DISABLED                                   0x00 
#define ADC10_REG3_L1MUX_TO_AIN0                                    0x01 
#define ADC10_REG3_L1MUX_TO_AIN1                                    0x02 
#define ADC10_REG3_L1MUX_TO_AIN2                                    0x03 
#define ADC10_REG3_L1MUX_TO_AIN3                                    0x04 
#define ADC10_REG3_L1MUX_TO_REFP                                    0x05 
#define ADC10_REG3_L1MUX_TO_REFN                                    0x06 
#define ADC10_REG3_L1MUX_RESERVED                                   0x07 

/**
 * @brief ADC 10 Configuration Register 3 description setting.
 * @details Specified IDAC2 routing configuration
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG3_L2MUX_DISABLED                                   0x00 
#define ADC10_REG3_L2MUX_TO_AIN0                                    0x01 
#define ADC10_REG3_L2MUX_TO_AIN1                                    0x02 
#define ADC10_REG3_L2MUX_TO_AIN2                                    0x03 
#define ADC10_REG3_L2MUX_TO_AIN3                                    0x04 
#define ADC10_REG3_L2MUX_TO_REFP                                    0x05 
#define ADC10_REG3_L2MUX_TO_REFN                                    0x06 

/**
 * @brief ADC 10 Configuration Register 3 description setting.
 * @details Specified ADC data output mode
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG3_DATA_MODE_MANUAL                                 0x00 
#define ADC10_REG3_DATA_MODE_AUTO                                   0x01 

/**
 * @brief ADC 10 Configuration Register 4 description setting.
 * @details Specified GPIO direction control
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG4_GPIO2_DIR_INPUT                                  0x00 
#define ADC10_REG4_GPIO2_DIR_OUTPUT                                 0x01 
#define ADC10_REG4_GPIO1_DIR_INPUT                                  0x00 
#define ADC10_REG4_GPIO1_DIR_OUTPUT                                 0x01 
#define ADC10_REG4_GPIO0_DIR_INPUT                                  0x00 
#define ADC10_REG4_GPIO0_DIR_OUTPUT                                 0x01 

/**
 * @brief ADC 10 Configuration Register 4 description setting.
 * @details Specified GPIO2/DRDY control
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG4_GPIO2_SEL_DAT                                    0x00 
#define ADC10_REG4_GPIO2_SEL_DRDY                                   0x01 

/**
 * @brief ADC 10 Configuration Register 4 description setting.
 * @details Specified GPIO control
 * for description of ADC 10 Click driver.
 */
#define ADC10_REG4_GPIO_LOW                                         0x00 
#define ADC10_REG4_GPIO_HIGH                                        0x01 

/**
 * @brief ADC 10 Configuration analog input setting.
 * @details Specified analog input of ADC 10 Click driver.
 */
#define ADC10_ANALOG_INPUT_CH_0                                     0x00 
#define ADC10_ANALOG_INPUT_CH_1                                     0x01 
#define ADC10_ANALOG_INPUT_CH_2                                     0x02 
#define ADC10_ANALOG_INPUT_CH_3                                     0x03 

/**
 * @brief ADC 10 Configuration data ready setting.
 * @details Specified data ready of ADC 10 Click driver.
 */
#define ADC10_NEW_DATA_IS_READY                                     0x00 
#define ADC10_NEW_DATA_NOT_READY                                    0x01

/**
 * @brief ADC 10 Gain value.
 * @details Specified gain value of ADC 10 Click driver.
 */
#define ADC10_GAIN_1                                                  1 
#define ADC10_GAIN_2                                                  2 
#define ADC10_GAIN_4                                                  4 
#define ADC10_GAIN_8                                                  8 
#define ADC10_GAIN_16                                                16 
#define ADC10_GAIN_32                                                32 
#define ADC10_GAIN_64                                                64 
#define ADC10_GAIN_128                                              128

/**
 * @brief ADC 10 Configuration Vref and resolution setting.
 * @details Specified Vref and resolution of ADC 10 Click driver.
 */
#define ADC10_REG_BITS                                              0x0E 
#define ADC10_ADC_RESOLUTION                                        0x007FFFFF 
#define ADC10_VREF_INTERNAL                                         2048.0 
#define ADC10_VREF_EXTERNAL_3300_mA                                 3300.0 
#define ADC10_VREF_EXTERNAL_5000_mA                                 5000.0 


/**
 * @brief ADC 10 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                                             200

/*! @} */ // adc10_set

/**
 * @defgroup adc10_map ADC 10 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 10 Click driver.
 */

/**
 * @addtogroup adc10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 10 Click to the selected MikroBUS.
 */
#define ADC10_MAP_MIKROBUS( cfg, mikrobus )          \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc10_map
/*! @} */ // adc10

/**
 * @brief ADC 10 Click context object.
 * @details Context object definition of ADC 10 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t rst;                         /**< Reset pin.                 */
                                                                               
    // Input pins                                                              
                                                                               
    digital_in_t int_pin;                      /**< Interrupt pin.             */
                                                                               
    // Modules                                                                 
                                                                               
    uart_t uart;                               /**< UART driver object.        */
                                                                               
    // Buffers                                                                 
                                                                               
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];    /**< Buffer size.               */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];    /**< Buffer size.               */
                                                                               
} adc10_t;                                                                     
                                                                               
/**                                                                            
 * @brief ADC 10 Click configuration object.                                   
 * @details Configuration object definition of ADC 10 Click driver.            
 */                                                                            
typedef struct                                                                 
{                                                                              
    // Communication gpio pins                                                 
                                                                               
    pin_name_t rx_pin;                         /**< RX pin.                    */
    pin_name_t tx_pin;                         /**< TX pin.                    */

    // Additional gpio pins

    pin_name_t rst;                            /**< Reset pin.                 */
    pin_name_t int_pin;                        /**< Interrupt pin.             */

    // Static variable

    uint32_t          baud_rate;               /**< Clock speed.               */
    bool              uart_blocking;           /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                /**< Data bits.                 */
    uart_parity_t     parity_bit;              /**< Parity bit.                */
    uart_stop_bits_t  stop_bit;                /**< Stop bits.                 */

} adc10_cfg_t;

typedef struct
{
    uint8_t input_mux;
    uint8_t gain;
    uint8_t pga_bypass;
    uint8_t data_rate;
    uint8_t op_mode;
    uint8_t conv_mode;
    uint8_t vref;
    uint8_t temp_sensor;
    uint8_t conv_drdy;
    uint8_t data_cnt;
    uint8_t data_integ_check;
    uint8_t b_current_src;
    uint8_t idac_current;
    uint8_t idac1_routing;
    uint8_t idac2_routing;
    uint8_t adc_data_out_mode;
    uint8_t gpio2_ctrl;
    uint8_t gpio1_ctrl;
    uint8_t gpio0_ctrl;
    uint8_t gpio2_drdy_ctrl;
    uint8_t gpio2_io_lvl;
    uint8_t gpio1_io_lvl;
    uint8_t gpio0_io_lvl;
}
adc10_settings_t;

/*!
 * @addtogroup adc10 ADC 10 Click Driver
 * @brief API for configuring and manipulating ADC 10 Click driver.
 * @{
 */

/**
 * @brief ADC 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc10_cfg_setup ( adc10_cfg_t *cfg );

/**
 * @brief ADC 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc10_init ( adc10_t *ctx, adc10_cfg_t *cfg );

/**
 * @brief ADC 10 default configuration function.
 * @details This function executes a default configuration of ADC 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void adc10_default_cfg ( adc10_t *ctx );

/**
 * @brief ADC 10 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc10_generic_write ( adc10_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief ADC 10 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc10_generic_read ( adc10_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief ADC 10 Hardware reset function.
 * @details This function perform a hardware reset the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_hw_reset ( adc10_t *ctx );

/**
 * @brief ADC 10 Check DRDY function.
 * @details This function indicates when a new conversion result is ready 
 * for retrieval of the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @return @li @c 0x00 ( ADC10_NEW_DATA_IS_READY )  - Data ready,
 *         @li @c 0x01 ( ADC10_NEW_DATA_NOT_READY ) - No new data.
 *
 * @note None.
 */
uint8_t adc10_check_drdy ( adc10_t *ctx );

/**
 * @brief ADC 10 Send command function.
 * @details This function sends the desired command to the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] cmd : Commands instruction.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_send_command ( adc10_t *ctx, uint8_t cmd );

/**
 * @brief ADC 10 Software reset function.
 * @details This function perform a software reset
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_reset ( adc10_t *ctx );

/**
 * @brief ADC 10 Start the synchronization function.
 * @details This function send start sync command to the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_start_sync ( adc10_t *ctx );

/**
 * @brief ADC 10 Shutdown function.
 * @details This function perform a shutdown of the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_shutdown ( adc10_t *ctx );

/**
 * @brief ADC 10 Write register function.
 * @details This function perform a writes the byte of data to the targeted 8-bit
 * register address of the 
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_data : Data to be written.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_write_reg ( adc10_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief ADC 10 Read register function.
 * @details This function perform a read the byte of data to the targeted 8-bit
 * register address of the 
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return Output read data.
 * 
 * @note None.
 */
uint8_t adc10_read_reg ( adc10_t *ctx, uint8_t reg );

/**
 * @brief ADC 10 Get the channel output function.
 * @details This function reads the ADC output of the channel
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] sel_ch : @li @c 0x00 ( ADC10_ANALOG_INPUT_CH_0 ) - Analog input 0.
 *                     @li @c 0x01 ( ADC10_ANALOG_INPUT_CH_1 ) - Analog input 1.
 *                     @li @c 0x02 ( ADC10_ANALOG_INPUT_CH_2 ) - Analog input 2.
 *                     @li @c 0x03 ( ADC10_ANALOG_INPUT_CH_3 ) - Analog input 3.
 * @return 24-bits of data ( two's complement format ) ADC data.
 * 
 * @note None.
 */
int32_t adc10_get_ch_output ( adc10_t *ctx, uint8_t sel_ch );

/**
 * @brief ADC 10 Calculate the voltage function.
 * @details This function reads the ADC output of the channel
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] adc_data : 24-bits of data ( two's complement format ) ADC data.
 * @param[in] vref : Voltage reference ( mV ).
 * @param[in] gain : Gain.
 * @return float voltage data ( mV ).
 * 
 * @note None.
 */
float adc10_calc_voltage ( adc10_t *ctx, int32_t adc_data, float vref, uint8_t gain );

/**
 * @brief ADC 10 Set configuration function.
 * @details This function set configuration data of the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[in] adc10_settings_t : Click settings configuration object.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_set_config ( adc10_t *ctx, adc10_settings_t cfg_data );

/**
 * @brief ADC 10 Get configuration function.
 * @details This function get configuration data of the
 * ADS122U04 24-Bit, 4-Channel, 2-kSPS, Delta-Sigma ADC With UART Interface
 * on the ADC 10 click board.
 * @param[in] ctx : Click context object.
 * See #adc10_t object definition for detailed explanation.
 * @param[out] adc10_settings_t : Click settings configuration object.
 * @return Nothing.
 * 
 * @note None.
 */
void adc10_get_config ( adc10_t *ctx, adc10_settings_t *cfg_data );



#ifdef __cplusplus
}
#endif
#endif // ADC10_H

/*! @} */ // adc10

// ------------------------------------------------------------------------ END

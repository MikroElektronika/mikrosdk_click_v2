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
 * @file rtd4.h
 * @brief This file contains API for RTD 4 Click Driver.
 */

#ifndef RTD4_H
#define RTD4_H

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

/*!
 * @addtogroup rtd4 RTD 4 Click Driver
 * @brief API for configuring and manipulating RTD 4 Click driver.
 * @{
 */

/**
 * @defgroup rtd4_cmd RTD 4 Device Settings
 * @brief Settings of RTD 4 Click driver.
 */

/**
 * @addtogroup rtd4_cmd
 * @{
 */

/**
 * @brief RTD 4 configuration registers list.
 * @details The ADS122U04 uses five 8-bit configuration registers to select
 * the input pair, gain, reference source, current source value and DRDY flag.
 */
#define RTD4_REG_CONFIG_0                       0x00
#define RTD4_REG_CONFIG_1                       0x01
#define RTD4_REG_CONFIG_2                       0x02
#define RTD4_REG_CONFIG_3                       0x03
#define RTD4_REG_CONFIG_4                       0x04

/**
 * @brief RTD 4 ADS122U04 commands.
 * @details UART command bytes used by the ADS122U04. Each command transaction
 * starts with #RTD4_SYNC_WORD so the ADC can synchronize to the UART baud rate.
 */
#define RTD4_SYNC_WORD                          0x55
#define RTD4_CMD_RESET                          0x06
#define RTD4_CMD_START_SYNC                     0x08
#define RTD4_CMD_POWERDOWN                      0x02
#define RTD4_CMD_RDATA                          0x10
#define RTD4_CMD_RREG                           0x20
#define RTD4_CMD_WREG                           0x40

/**
 * @brief RTD 4 ADS122U04 command framing.
 * @details Register command bytes contain the register address shifted into
 * the ADS122U04 command byte. The device returns conversion data as a 3-byte
 * two's complement value.
 */
#define RTD4_CMD_REG_ADDR_MASK                  0x07
#define RTD4_CMD_REG_ADDR_SHIFT                 1
#define RTD4_CMD_FRAME_SIZE                     2
#define RTD4_CMD_WREG_FRAME_SIZE                3
#define RTD4_CMD_RDATA_SIZE                     3
#define RTD4_FRAME_SYNC_BYTE                    0
#define RTD4_FRAME_CMD_BYTE                     1
#define RTD4_FRAME_DATA_BYTE                    2
#define RTD4_RDATA_LSB_BYTE                     0
#define RTD4_RDATA_MID_BYTE                     1
#define RTD4_RDATA_MSB_BYTE                     2
#define RTD4_REG_READ_SIZE                      1

/**
 * @brief RTD 4 Configuration Register 0 bit settings.
 * @details Input multiplexer, gain and PGA bypass settings.
 */
#define RTD4_REG_MASK_ALL_BITS                  0xFF
#define RTD4_REG0_MUX_MASK                      0xF0
#define RTD4_REG0_GAIN_MASK                     0x0E
#define RTD4_REG0_PGA_MASK                      0x01
#define RTD4_REG0_MUX_AIN0_AIN1                 0x00
#define RTD4_REG0_MUX_AIN0_AIN2                 0x10
#define RTD4_REG0_MUX_AIN0_AIN3                 0x20
#define RTD4_REG0_MUX_AIN1_AIN0                 0x30
#define RTD4_REG0_MUX_AIN1_AIN2                 0x40
#define RTD4_REG0_MUX_AIN1_AIN3                 0x50
#define RTD4_REG0_MUX_AIN2_AIN3                 0x60
#define RTD4_REG0_MUX_AIN3_AIN2                 0x70
#define RTD4_REG0_MUX_AIN0_AVSS                 0x80
#define RTD4_REG0_MUX_AIN1_AVSS                 0x90
#define RTD4_REG0_MUX_AIN2_AVSS                 0xA0
#define RTD4_REG0_MUX_AIN3_AVSS                 0xB0
#define RTD4_REG0_MUX_REF_MON                   0xC0
#define RTD4_REG0_MUX_SUPPLY_MON                0xD0
#define RTD4_REG0_MUX_SHORTED                   0xE0
#define RTD4_REG0_MUX_RESERVED                  0xF0
#define RTD4_REG0_GAIN_1                        0x00
#define RTD4_REG0_GAIN_2                        0x02
#define RTD4_REG0_GAIN_4                        0x04
#define RTD4_REG0_GAIN_8                        0x06
#define RTD4_REG0_GAIN_16                       0x08
#define RTD4_REG0_GAIN_32                       0x0A
#define RTD4_REG0_GAIN_64                       0x0C
#define RTD4_REG0_GAIN_128                      0x0E
#define RTD4_REG0_PGA_ENABLED                   0x00
#define RTD4_REG0_PGA_DISABLED                  0x01

/**
 * @brief RTD 4 Configuration Register 1 bit settings.
 * @details Data rate, operating mode, conversion mode, reference source and
 * internal temperature sensor settings.
 */
#define RTD4_REG1_DR_MASK                       0xE0
#define RTD4_REG1_MODE_MASK                     0x10
#define RTD4_REG1_CM_MASK                       0x08
#define RTD4_REG1_VREF_MASK                     0x06
#define RTD4_REG1_TS_MASK                       0x01
#define RTD4_REG1_DR_20SPS                      0x00
#define RTD4_REG1_DR_45SPS                      0x20
#define RTD4_REG1_DR_90SPS                      0x40
#define RTD4_REG1_DR_175SPS                     0x60
#define RTD4_REG1_DR_330SPS                     0x80
#define RTD4_REG1_DR_600SPS                     0xA0
#define RTD4_REG1_DR_1000SPS                    0xC0
#define RTD4_REG1_DR_RESERVED                   0xE0
#define RTD4_REG1_MODE_NORMAL                   0x00
#define RTD4_REG1_MODE_TURBO                    0x10
#define RTD4_REG1_CM_SINGLE                     0x00
#define RTD4_REG1_CM_CONTINUOUS                 0x08
#define RTD4_REG1_VREF_INTERNAL                 0x00
#define RTD4_REG1_VREF_REFP_REFN                0x02
#define RTD4_REG1_VREF_AVDD_AVSS                0x04
#define RTD4_REG1_VREF_SUPPLY                   0x06
#define RTD4_REG1_TS_DISABLED                   0x00
#define RTD4_REG1_TS_ENABLED                    0x01

/**
 * @brief RTD 4 Configuration Register 2 bit settings.
 * @details Conversion ready flag, data counter, data integrity, burnout source
 * and IDAC current settings.
 */
#define RTD4_REG2_CFG_MASK                      0x7F
#define RTD4_REG2_DRDY_MASK                     0x80
#define RTD4_REG2_DCNT_MASK                     0x40
#define RTD4_REG2_CRC_MASK                      0x30
#define RTD4_REG2_BCS_MASK                      0x08
#define RTD4_REG2_IDAC_MASK                     0x07
#define RTD4_REG2_DRDY_SHIFT                    7
#define RTD4_REG2_DRDY_STATE_MASK               0x01
#define RTD4_REG2_DRDY_CLEAR                    0x00
#define RTD4_REG2_DRDY_READY                    0x80
#define RTD4_REG2_DCNT_DISABLED                 0x00
#define RTD4_REG2_DCNT_ENABLED                  0x40
#define RTD4_REG2_CRC_DISABLED                  0x00
#define RTD4_REG2_CRC_INVERTED                  0x10
#define RTD4_REG2_CRC_CRC16                     0x20
#define RTD4_REG2_CRC_RESERVED                  0x30
#define RTD4_REG2_BCS_OFF                       0x00
#define RTD4_REG2_BCS_ON                        0x08
#define RTD4_REG2_IDAC_OFF                      0x00
#define RTD4_REG2_IDAC_10UA                     0x01
#define RTD4_REG2_IDAC_50UA                     0x02
#define RTD4_REG2_IDAC_100UA                    0x03
#define RTD4_REG2_IDAC_250UA                    0x04
#define RTD4_REG2_IDAC_500UA                    0x05
#define RTD4_REG2_IDAC_1000UA                   0x06
#define RTD4_REG2_IDAC_1500UA                   0x07

/**
 * @brief RTD 4 Configuration Register 3 bit settings.
 * @details IDAC1 routing, IDAC2 routing and automatic conversion data read
 * settings.
 */
#define RTD4_REG3_I1MUX_MASK                    0xE0
#define RTD4_REG3_I2MUX_MASK                    0x1C
#define RTD4_REG3_RESERVED_MASK                 0x02
#define RTD4_REG3_AUTO_MASK                     0x01
#define RTD4_REG3_I1MUX_DISABLED                0x00
#define RTD4_REG3_I1MUX_AIN0                    0x20
#define RTD4_REG3_I1MUX_AIN1                    0x40
#define RTD4_REG3_I1MUX_AIN2                    0x60
#define RTD4_REG3_I1MUX_AIN3                    0x80
#define RTD4_REG3_I1MUX_REFP                    0xA0
#define RTD4_REG3_I1MUX_REFN                    0xC0
#define RTD4_REG3_I1MUX_RESERVED                0xE0
#define RTD4_REG3_I2MUX_DISABLED                0x00
#define RTD4_REG3_I2MUX_AIN0                    0x04
#define RTD4_REG3_I2MUX_AIN1                    0x08
#define RTD4_REG3_I2MUX_AIN2                    0x0C
#define RTD4_REG3_I2MUX_AIN3                    0x10
#define RTD4_REG3_I2MUX_REFP                    0x14
#define RTD4_REG3_I2MUX_REFN                    0x18
#define RTD4_REG3_I2MUX_RESERVED                0x1C
#define RTD4_REG3_RESERVED_0                    0x00
#define RTD4_REG3_DATA_MANUAL                   0x00
#define RTD4_REG3_DATA_AUTO                     0x01

/**
 * @brief RTD 4 Configuration Register 4 bit settings.
 * @details GPIO direction, GPIO2/DRDY output select and GPIO data level
 * settings.
 */
#define RTD4_REG4_RESERVED_MASK                 0x80
#define RTD4_REG4_GPIO2_DIR_MASK                0x40
#define RTD4_REG4_GPIO1_DIR_MASK                0x20
#define RTD4_REG4_GPIO0_DIR_MASK                0x10
#define RTD4_REG4_GPIO2_SEL_MASK                0x08
#define RTD4_REG4_GPIO2_DAT_MASK                0x04
#define RTD4_REG4_GPIO1_DAT_MASK                0x02
#define RTD4_REG4_GPIO0_DAT_MASK                0x01
#define RTD4_REG4_RESERVED_0                    0x00
#define RTD4_REG4_GPIO2_INPUT                   0x00
#define RTD4_REG4_GPIO2_OUTPUT                  0x40
#define RTD4_REG4_GPIO1_INPUT                   0x00
#define RTD4_REG4_GPIO1_OUTPUT                  0x20
#define RTD4_REG4_GPIO0_INPUT                   0x00
#define RTD4_REG4_GPIO0_OUTPUT                  0x10
#define RTD4_REG4_GPIO2_SEL_DAT                 0x00
#define RTD4_REG4_GPIO2_SEL_DRDY                0x08
#define RTD4_REG4_GPIO2_LOW                     0x00
#define RTD4_REG4_GPIO2_HIGH                    0x04
#define RTD4_REG4_GPIO1_LOW                     0x00
#define RTD4_REG4_GPIO1_HIGH                    0x02
#define RTD4_REG4_GPIO0_LOW                     0x00
#define RTD4_REG4_GPIO0_HIGH                    0x01

/**
 * @brief RTD 4 default register values.
 * @details These values configure a 3-wire PT100 measurement using AIN1/AIN0,
 * gain 8, external ratiometric reference, two 500 uA IDAC sources and 3-byte
 * conversion reads.
 */
#define RTD4_CFG0_RTD_3WIRE                     ( RTD4_REG0_MUX_AIN1_AIN0 | \
                                                  RTD4_REG0_GAIN_8 | \
                                                  RTD4_REG0_PGA_ENABLED )
#define RTD4_CFG1_RTD_3WIRE                     ( RTD4_REG1_DR_20SPS | \
                                                  RTD4_REG1_MODE_NORMAL | \
                                                  RTD4_REG1_CM_CONTINUOUS | \
                                                  RTD4_REG1_VREF_REFP_REFN | \
                                                  RTD4_REG1_TS_DISABLED )
#define RTD4_CFG2_RTD_3WIRE                     ( RTD4_REG2_DRDY_CLEAR | \
                                                  RTD4_REG2_DCNT_DISABLED | \
                                                  RTD4_REG2_CRC_DISABLED | \
                                                  RTD4_REG2_BCS_OFF | \
                                                  RTD4_REG2_IDAC_500UA )
#define RTD4_CFG3_RTD_3WIRE                     ( RTD4_REG3_I1MUX_AIN2 | \
                                                  RTD4_REG3_I2MUX_AIN3 | \
                                                  RTD4_REG3_RESERVED_0 | \
                                                  RTD4_REG3_DATA_MANUAL )
#define RTD4_CFG4_RTD_3WIRE                     ( RTD4_REG4_RESERVED_0 | \
                                                  RTD4_REG4_GPIO2_OUTPUT | \
                                                  RTD4_REG4_GPIO1_INPUT | \
                                                  RTD4_REG4_GPIO0_INPUT | \
                                                  RTD4_REG4_GPIO2_SEL_DRDY | \
                                                  RTD4_REG4_GPIO2_LOW | \
                                                  RTD4_REG4_GPIO1_LOW | \
                                                  RTD4_REG4_GPIO0_LOW )

/**
 * @brief RTD 4 conversion constants.
 * @details Constants used by the helper functions that convert the ADC code
 * to PT100 resistance and approximate temperature.
 */
#define RTD4_ADC_FULL_SCALE                     8388608.0f
#define RTD4_REF_RESISTOR_OHM                   1690.0f
#define RTD4_RTD_GAIN                           8.0f
#define RTD4_PT100_R0_OHM                       100.0f
#define RTD4_PT100_ALPHA                        0.385f
#define RTD4_ADC_MID_SHIFT                      8
#define RTD4_ADC_MSB_SHIFT                      16
#define RTD4_ADC_SIGN_BIT                       0x00800000
#define RTD4_ADC_SIGN_EXT                       0xFF000000
#define RTD4_RTD_REF_FACTOR                     2.0f

/**
 * @brief RTD 4 polling timeouts.
 * @details Timeout values used while waiting for UART response bytes and
 * ADS122U04 conversion completion.
 */
#define RTD4_REG_READ_TIMEOUT_MS                20
#define RTD4_DATA_READ_TIMEOUT_MS               50
#define RTD4_CONV_TIMEOUT_MS                    500

/**
 * @brief RTD 4 data ready state.
 * @details The ADS122U04 register DRDY bit is set when a new conversion
 * result can be read.
 */
#define RTD4_DATA_NOT_READY                     0
#define RTD4_DATA_READY                         1

/**
 * @brief RTD 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RTD4_TX_DRV_BUFFER_SIZE                 200
#define RTD4_RX_DRV_BUFFER_SIZE                 200

/*! @} */ // rtd4_cmd

/**
 * @defgroup rtd4_map RTD 4 MikroBUS Map
 * @brief MikroBUS pin mapping of RTD 4 Click driver.
 */

/**
 * @addtogroup rtd4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTD 4 Click to the selected MikroBUS.
 */
#define RTD4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // rtd4_map
/*! @} */ // rtd4

/**
 * @brief RTD 4 Click context object.
 * @details Context object definition of RTD 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Device reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RTD4_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ RTD4_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} rtd4_t;

/**
 * @brief RTD 4 Click configuration object.
 * @details Configuration object definition of RTD 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Device reset pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} rtd4_cfg_t;

/**
 * @brief RTD 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTD4_OK = 0,
    RTD4_ERROR = -1

} rtd4_return_value_t;

/*!
 * @addtogroup rtd4 RTD 4 Click Driver
 * @brief API for configuring and manipulating RTD 4 Click driver.
 * @{
 */

/**
 * @brief RTD 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtd4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtd4_cfg_setup ( rtd4_cfg_t *cfg );

/**
 * @brief RTD 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtd4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtd4_init ( rtd4_t *ctx, rtd4_cfg_t *cfg );

/**
 * @brief RTD 4 default configuration function.
 * @details This function executes a default configuration of RTD 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtd4_default_cfg ( rtd4_t *ctx );

/**
 * @brief RTD 4 data writing function.
 * @details This function writes a desired number of data bytes by using the
 * UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtd4_generic_write ( rtd4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RTD 4 data reading function.
 * @details This function reads a desired number of data bytes by using the UART
 * serial interface.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/empty ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtd4_generic_read ( rtd4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RTD 4 hardware reset function.
 * @details This function toggles the ADS122U04 RESET pin and waits for the
 * device to complete the power-on reset sequence.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rtd4_hw_reset ( rtd4_t *ctx );

/**
 * @brief RTD 4 data ready function.
 * @details This function reads the ADS122U04 configuration register 2 and
 * returns the state of the DRDY bit.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @return @li @c 0 - Conversion data is not ready,
 *         @li @c 1 - New conversion data is ready.
 * @note None.
 */
uint8_t rtd4_get_drdy ( rtd4_t *ctx );

/**
 * @brief RTD 4 command function.
 * @details This function sends one ADS122U04 command with the required UART
 * synchronization byte.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] cmd : ADS122U04 command byte.
 * @return None.
 * @note None.
 */
void rtd4_send_cmd ( rtd4_t *ctx, uint8_t cmd );

/**
 * @brief RTD 4 register writing function.
 * @details This function writes one ADS122U04 configuration register.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Register data to be written.
 * @return None.
 * @note None.
 */
void rtd4_write_reg ( rtd4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTD 4 register reading function.
 * @details This function reads one ADS122U04 configuration register.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Read register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtd4_read_reg ( rtd4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTD 4 raw ADC reading function.
 * @details This function starts a conversion, waits for DRDY and reads the
 * 24-bit two's complement ADC conversion result.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[out] adc_data : Signed 24-bit ADC code extended to 32 bits.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtd4_read_raw ( rtd4_t *ctx, int32_t *adc_data );

/**
 * @brief RTD 4 resistance reading function.
 * @details This function reads the ADC conversion result and converts it to
 * RTD resistance using the ratiometric 3-wire measurement equation.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[out] resistance : Calculated RTD resistance in ohms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The calculation uses #RTD4_REF_RESISTOR_OHM and #RTD4_RTD_GAIN.
 */
err_t rtd4_read_res ( rtd4_t *ctx, float *resistance );

/**
 * @brief RTD 4 temperature reading function.
 * @details This function reads RTD resistance and calculates approximate PT100
 * temperature using a linear coefficient.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[out] temperature : Calculated temperature in degrees Celsius.
 * @param[out] resistance : Calculated RTD resistance in ohms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For high accuracy or temperatures below 0 C, use the full Callendar-
 * Van Dusen equation in the application layer.
 */
err_t rtd4_read_temp ( rtd4_t *ctx, float *temperature, float *resistance );

#ifdef __cplusplus
}
#endif
#endif // RTD4_H

/*! @} */ // rtd4

// ------------------------------------------------------------------------ END

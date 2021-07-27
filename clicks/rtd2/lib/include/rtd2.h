/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for RTD 2 Click driver.
 *
 * \addtogroup rtd2 RTD 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTD2_H
#define RTD2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define RTD2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.str   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.rdy   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTD2_RETVAL  uint8_t

#define RTD2_OK           0x00
#define RTD2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_map Register Map
 * \{
 */
#define RTD2_REG_MUX0                                              0x00
#define RTD2_REG_VBIAS                                             0x01
#define RTD2_REG_MUX1                                              0x02
#define RTD2_REG_SYS0                                              0x03
#define RTD2_REG_OFC0                                              0x04
#define RTD2_REG_OFC1                                              0x05
#define RTD2_REG_OFC2                                              0x06
#define RTD2_REG_FSC0                                              0x07
#define RTD2_REG_FSC1                                              0x08
#define RTD2_REG_FSC2                                              0x09
#define RTD2_REG_IDAC0                                             0x0A
#define RTD2_REG_IDAC1                                             0x0B
#define RTD2_REG_GPIOCFG                                           0x0C
#define RTD2_REG_GPIODIR                                           0x0D
#define RTD2_REG_GPIODAT                                           0x0E
/** \} */

/**
 * \defgroup command_definitions Command Definitions
 * \{
 */

/**
 * \defgroup system_control System Control
 * \{
 */
#define RTD2_CMD_WAKEUP                                            0x01
#define RTD2_CMD_SLEEP                                             0x03
#define RTD2_CMD_SYNC                                              0x05
#define RTD2_CMD_RESET                                             0x07
#define RTD2_CMD_NOP                                               0xFF
/** \} */

/**
 * \defgroup data_read Data Read
 * \{
 */
#define RTD2_CMD_RDATA                                             0x12
#define RTD2_CMD_RDATAC                                            0x14
#define RTD2_CMD_SDATAC                                            0x16
/** \} */

/**
 * \defgroup read_register Read Register
 * \{
 */
#define RTD2_CMD_RREG                                              0x20
/** \} */

/**
 * \defgroup write_register Write Register
 * \{
 */
#define RTD2_CMD_WREG                                              0x40
/** \} */

/**
 * \defgroup calibration Calibration
 * \{
 */
#define RTD2_CMD_SYSOCAL                                           0x60
#define RTD2_CMD_SYSGCAL                                           0x61
#define RTD2_CMD_SELFOCAL                                          0x62
/** \} */

/**
 * \defgroup  dummy  Dummy
 * \{
 */
#define RTD2_RW_DUMMY                                              0xFF
/** \} */
/** \} */

/**
 * \defgroup  multiplexer_ctrl_reg Multiplexer Control Register 0 (MUX0) Definition
 * \{
 */

/**
 * \defgroup  define_bcs Define BCS ( burnout current source )
 * \{
 */
#define RTD2_BCS_OFF                                               0x00
#define RTD2_BCS_500                                               0x40
#define RTD2_BCS_2                                                 0x80
#define RTD2_BCS_10                                                0xC0
/** \} */

/**
 * \defgroup   define_positive_mux_input_channels  Define Positive MUX Input Channels
 * \{
 */
#define RTD2_AINP0                                                 0x00
#define RTD2_AINP1                                                 0x08
#define RTD2_AINP2                                                 0x10
#define RTD2_AINP3                                                 0x18
#define RTD2_AIN_POS                                               0x38
/** \} */

/**
 * \defgroup  define_negative_mux_input_channels Define Negative Mux Input Channels
 * \{
 */
#define RTD2_AINN0                                                 0x00
#define RTD2_AINN1                                                 0x01
#define RTD2_AINN2                                                 0x02
#define RTD2_AINN3                                                 0x03
#define RTD2_AIN_NEG                                               0x07
/** \} */

/**
 * \defgroup  bias_voltage_register_definition Bias Voltage Register (VBIAS) Definition
 * \{
 */
#define RTD2_VBIAS_OFF                                             0x00
#define RTD2_VBIAS0                                                0x01
#define RTD2_VBIAS1                                                0x02
#define RTD2_VBIAS2                                                0x04
#define RTD2_VBIAS3                                                0x08
/** \} */
/** \} */

/**
 * \defgroup multiplexer_control_register_1 Multiplexer Control Register 1 (MUX1) Definition
 * \{
 */

/**
 * \defgroup define_internal_reference Define Internal Reference
 * \{
 */
#define RTD2_INT_VREF_OFF                                          0x00
#define RTD2_INT_VREF_ON                                           0x20
#define RTD2_INT_VREF_CONV                                         0x40
/** \} */

/**
 * \defgroup define_reference_select Define Reference Select
 * \{
 */
#define RTD2_REF0                                                  0x00
#define RTD2_INT                                                   0x10
#define RTD2_INT_REF0                                              0x18
/** \} */

/**
 * \defgroup define_system_monitor Define System Monitor
 * \{
 */
#define RTD2_MEAS_NORM                                             0x00
#define RTD2_MEAS_OFFSET                                           0x01
#define RTD2_MEAS_GAIN                                             0x02
#define RTD2_MEAS_TEMP                                             0x03
#define RTD2_MEAS_REF0                                             0x05
#define RTD2_MEAS_AVDD                                             0x06
#define RTD2_MEAS_DVDD                                             0x07
/** \} */
/** \} */

/**
 * \defgroup system_control_register 0 System Control Register 0 (SYS0) Definition
 * \{
 */

/**
 * \defgroup define_gain Define Gain
 * \{
 */
#define RTD2_GAIN_1                                                0x00
#define RTD2_GAIN_2                                                0x10
#define RTD2_GAIN_4                                                0x20
#define RTD2_GAIN_8                                                0x30
#define RTD2_GAIN_16                                               0x40
#define RTD2_GAIN_32                                               0x50
#define RTD2_GAIN_64                                               0x60
#define RTD2_GAIN_128                                              0x70
/** \} */

/**
 * \defgroup define_data_rate Define data rate
 * \{
 */
#define RTD2_DR_5                                                  0x00
#define RTD2_DR_10                                                 0x01
#define RTD2_DR_20                                                 0x02
#define RTD2_DR_40                                                 0x03
#define RTD2_DR_80                                                 0x04
#define RTD2_DR_160                                                0x05
#define RTD2_DR_320                                                0x06
#define RTD2_DR_640                                                0x07
#define RTD2_DR_1000                                               0x08
#define RTD2_DR_2000                                               0x0F
/** \} */
/** \} */

/**
 * \defgroup idac_control_register_0 IDAC Control Register 0 (IDAC0) Definition
 * \{
 */

/**
 * \defgroup id ID
 * \{
 */
#define RTD2_IDAC_ID                                               0x90
/** \} */

/**
 * \defgroup define_drdy_mode_on_dout Define DRDY mode on DOUT
 * \{
 */
#define RTD2_DRDY_OFF                                              0x00
#define RTD2_DRDY_ON                                               0x08
/** \} */

/**
 * \defgroup define_idac_magnitude Define IDAC Magnitude
 * \{
 */
#define RTD2_IDAC_OFF                                              0x00
#define RTD2_IDAC_50                                               0x01
#define RTD2_IDAC_100                                              0x02
#define RTD2_IDAC_250                                              0x03
#define RTD2_IDAC_500                                              0x04
#define RTD2_IDAC_750                                              0x05
#define RTD2_IDAC_1000                                             0x06
#define RTD2_IDAC_1500                                             0x07
/** \} */
/** \} */

/**
 * \defgroup idac_control_register_1 IDAC Control Register 1 (IDAC1) Definition
 * \{
 */

/**
 * \defgroup define_idac1_output Define IDAC1 Output
 * \{
 */
#define RTD2_IDAC1_A0                                              0xCC
#define RTD2_IDAC1_A1                                              0xDC
#define RTD2_IDAC1_A2                                              0xEC
#define RTD2_IDAC1_A3                                              0xFC
/** \} */

/**
 * \defgroup define_idac2_output Define IDAC2 Output
 * \{
 */
#define RTD2_IDAC2_A0                                              0xCC
#define RTD2_IDAC2_A1                                              0xCD
#define RTD2_IDAC2_A2                                              0xCE
#define RTD2_IDAC2_A3                                              0xCF
/** \} */
/** \} */

/**
 * \defgroup gpio_cfg_reg GPIO Configuration Register (GPIOCFG) Definition
 * \{
 */

/**
 * \defgroup define_gpio Define GPIO (0-Analog; 1-GPIO)
 * \{
 */
#define RTD2_GPIO_0                                                0x01
#define RTD2_GPIO_1                                                0x02
#define RTD2_GPIO_2                                                0x04
#define RTD2_GPIO_3                                                0x08
/** \} */
/** \} */

/**
 * \defgroup gpio_direction_register Definition GPIO Direction Register (GPIODIR) Definition
 * \{
 */

/**
 * \defgroup define_gpio_direction Define GPIO Direction (0-Output; 1-Input)
 * \{
 */
#define RTD2_IO_0                                                  0x01
#define RTD2_IO_1                                                  0x02
#define RTD2_IO_2                                                  0x04
#define RTD2_IO_3                                                  0x08
/** \} */
/** \} */

/**
 * \defgroup gpio_data_register_definition GPIO Data Register (GPIODAT) Definition
 * \{
 */
#define RTD2_OUT_0                                                 0x01
#define RTD2_OUT_1                                                 0x02
#define RTD2_OUT_2                                                 0x04
#define RTD2_OUT_3                                                 0x08
/** \} */

/**
 * \defgroup pin_states_definition Pin States Definition
 * \{
 */
#define RTD2_PIN_LOW                                               0x00
#define RTD2_PIN_HIGH                                              0x01
/** \} */

/**
 * \defgroup Error Flags Definition Error Flags Definition
 * \{
 */
#define RTD2_ERROR                                                 0x00
#define RTD2_SUCESS                                                0x01
/** \} */

/**
 * \defgroup  start_conversion  Start conversion
 * \{
 */
#define RTD2_START_CONVERSION_DISABLE                              0x00
#define RTD2_START_CONVERSION_ENABLE                               0x01
/** \} */

/**
 * \defgroup check_new_data_ready Check new data ready
 * \{
 */
#define RTD2_NEW_DATA_IS_NOT_READY                                 0x00
#define RTD2_NEW_DATA_IS_READY                                     0x01
/** \} */

/**
 * \defgroup linearization_coefficient_for_pt100 Linearization coefficient for Pt100
 * \{
 */
#define COEFF_PT100_RESISTANCE_OHMS_0_C                            100.00000000
#define COEFF_ALPHA                                                0.3920000000
#define COEFF_ADC_RES_RT_P                                         0.0000753846
#define COEFF_ADC_COR_FACT                                         50.980300000
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    digital_out_t cs;
    // Output pins 

    digital_out_t str;
    digital_out_t rst;

    // Input pins 

    digital_in_t rdy;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rtd2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t str;
    pin_name_t rst;
    pin_name_t rdy;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rtd2_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void rtd2_cfg_setup ( rtd2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 *
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTD2_RETVAL rtd2_init ( rtd2_t *ctx, rtd2_cfg_t *cfg );

/**
 * @brief Set default configuration function.
 *
 * @param ctx Click object. 
 *
 * @description The function set default configuration of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
 * 
 * @note Default configuration 
 *         [ reg ]           :         [ reg value ]
 * - 0x00 ( RTD2_REG_MUX0 )  : RTD2_AINP1 | RTD2_AINN2.
 * - 0x01 ( RTD2_REG_VBIAS ) : RTD2_VBIAS0.
 * - 0x02 ( RTD2_REG_MUX1 )  : RTD2_INT_VREF_ON | RTD2_INT_REF0.
 * - 0x03 ( RTD2_REG_SYS0 )  : RTD2_GAIN_4 | RTD2_DR_20.
 * - 0x0A ( RTD2_REG_IDAC0 ) : RTD2_IDAC_ID | RTD2_IDAC_1000.
 * - 0x0B ( RTD2_REG_IDAC1 ) : RTD2_IDAC1_A0 | RTD2_IDAC1_A03.
**/
void rtd2_default_cfg ( rtd2_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void rtd2_generic_transfer 
( 
    rtd2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Hardware reset function.
 *
 * @param ctx Click object.
 * 
 * @description The function hardware reset,
 * resets the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
 *
 * @note Delay time of 1 ms after RESET rising edge.
**/
void rtd2_hw_reset ( rtd2_t *ctx );

/**
 * @brief Toggle CS pin function.
 *
 * @param ctx Click object. 
 * @param cs_state
 * - 0x00 : The pin condition is low.
 * - 0x01 : The pin condition is high.
 *
 * @description The function toggle CS pin, set CS pin condition of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_toggle_cs ( rtd2_t *ctx, uint8_t cs_state );

/**
 * @brief Enable conversion start function.
 *
 * @param ctx Click object. 
 * @param en_start
 * - 0x00 : Disable conversion.
 * - 0x01 : Enable conversion.
 *
 * @description The function enables ADC conversion of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_enable_start ( rtd2_t *ctx, uint8_t en_start );

/**
 * @brief Check interrupt status function.
 *
 * @param ctx Click object.
 * 
 * @return
 * Interrupt state:
 * - 0 : No active.
 * - 1 : Active.
 *
 * @description The function check interrupt state by return state
 * of the INT pin of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
 */
uint8_t rtd2_check_interupt ( rtd2_t *ctx );

/**
 * @brief Send command function.
 *
 * @param ctx         Click object. 
 * @param cmd         8-bit SPI Commands.
 *
 * @description The function sends the command to control the operation of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_send_cmd ( rtd2_t *ctx, uint8_t cmd );

/**
 * @brief Set wakeup function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set wakeup, after a sleep, power up the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_wakeup ( rtd2_t *ctx );

/**
 * @brief Set to sleep function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set to sleep, places into power-down mode the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_sleep ( rtd2_t *ctx );

/**
 * @brief Set sync function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set sync, 
 * resets the ADC digital filter and starts a new conversion of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_sync ( rtd2_t *ctx );

/**
 * @brief Set reset function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set-reset,
 * restores the registers to the respective default values of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_reset ( rtd2_t *ctx );

/**
 * @brief Set read data once function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set to read data once,
 * loads the most recent conversion result into the output register of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_read_data_once ( rtd2_t *ctx );

/**
 * @brief Set read data continuous function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set to read data continuous,
 * enables read data continuous mode of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_read_data_continuous ( rtd2_t *ctx );

/**
 * @brief Set stop data function.
 *
 * @param ctx         Click object. 
 * 
 * @description The function set stop data continuous,
 * terminates read data continuous mode of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_stop_data ( rtd2_t *ctx );

/**
 * @brief Continuous write the data function.
 *
 * @param ctx         Click object. 
 *
 * @param reg         8-bit register address.
 *
 * @param p_tx_data   pointer to the data to be written.
 *
 * @param n_bytes     number of bytes to be written.
 *
 * @description The function writes a sequential data starting
 * from the targeted register address of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_write_continuous ( rtd2_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Continuous read the data function.
 *
 * @param ctx         Click object. 
 * 
 * @param reg         8-bit register address.
 *
 * @param p_rx_data   pointer to the memory location where data be stored.
 *
 * @param n_bytes     number of bytes to be read.
 *
 * @description The function read a sequential data starting
 * from the targeted register address of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_read_continuous ( rtd2_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Write the register function.
 *
 * @param ctx         Click object. 
 * 
 * @param reg         8-bit register address.
 *
 * @param tx_data     8-bit write data.
 *
 * @description The function write the data byte
 * of the desired register address of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement 
 * on the RTD 2 click board.
**/
void rtd2_write_reg ( rtd2_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Read the register function.
 *
 * @param ctx         Click object. 
 * 
 * @param reg         8-bit register address.
 *
 * @return
 * 8-bit read data.
 *
 * @description The function read the data byte
 * of the desired register address of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
uint8_t rtd2_read_reg ( rtd2_t *ctx, uint8_t reg );

/**
 * @brief Set burn out source function.
 *
 * @param ctx         Click object. 
 * 
 * @param burn_out
 * - 0x00 ( RTD2_BCS_OFF ) : Burn-out current source off( default ).
 * - 0x40 ( RTD2_BCS_500 ) : Burn-out current source on, 0.5 �A.
 * - 0x80 ( RTD2_BCS_2 )   : Burn-out current source on, 2 �A.
 * - 0xC0 ( RTD2_BCS_10 )  : Burn-out current source on, 10 �A.
 *
 * @return status
 * - 0x00 ( RTD2_ERROR ) : Error.
 * - 0x01 ( RTD2_SUCESS ): Sucess.
 *
 * @description The function set burn out source of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
uint8_t rtd2_set_burn_out_source ( rtd2_t *ctx, uint8_t burn_out );

/**
 * @brief Set multiplexer selection function.
 *
 * @param ctx         Click object. 
 * 
 * @param adc_pos
 * - 0x00 ( RTD2_AINP0 ) : AIN0( default ).
 * - 0x08 ( RTD2_AINP1 ) : AIN1.
 * - 0x10 ( RTD2_AINP2 ) : AIN2.
 * - 0x18 ( RTD2_AINP3 ) : AIN3.
 *
 * @param adc_neg
 * - 0x00 ( RTD2_AINN0 ) : AIN0( default ).
 * - 0x01 ( RTD2_AINN1 ) : AIN1.
 * - 0x02 ( RTD2_AINN2 ) : AIN2.
 * - 0x04 ( RTD2_AINN3 ) : AIN3.
 *
 * @description The function set multiplexer selection,  
 * set positive and negative input channel selection of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_mux_sel ( rtd2_t *ctx, uint8_t adc_pos, uint8_t adc_neg );

/**
 * @brief Set bias function.
 *
 * @param ctx         Click object. 
 * 
 * @param v_bias
 * - 0x00 ( RTD2_VBIAS_OFF ) : Bias voltage is not enabled( default ).
 * - 0x01 ( RTD2_VBIAS0 )    : VBIAS[0] Voltage Enable.
 * - 0x02 ( RTD2_VBIAS1 )    : VBIAS[1] Voltage Enable.
 * - 0x04 ( RTD2_VBIAS2 )    : VBIAS[2] Voltage Enable.
 * - 0x08 ( RTD2_VBIAS3 )    : VBIAS[3] Voltage Enable.
 *
 * @return status
 * - 0x00 ( RTD2_ERROR ) : Error.
 * - 0x01 ( RTD2_SUCESS ): Sucess.
 *
 * @description The function set bias voltage of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
uint8_t rtd2_set_bias ( rtd2_t *ctx, uint8_t v_bias );

/**
 * @brief Set int ref function.
 *
 * @param ctx         Click object. 
 * 
 * @param s_ref
 * - 0x00 ( RTD2_INT_VREF_OFF )  : Internal reference is always off( default ).
 * - 0x20 ( RTD2_INT_VREF_ON )   : Internal reference is always on.
 * - 0x40 ( RTD2_INT_VREF_CONV ) : Internal reference is on when conversion on.
 *
 * @return status
 * - 0x00 ( RTD2_ERROR ) : Error.
 * - 0x01 ( RTD2_SUCESS ): Sucess.
 *
 * @description The function set internal reference control of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
uint8_t rtd2_set_int_ref ( rtd2_t *ctx, uint8_t s_ref );

/**
 * @brief Set system monitor function.
 *
 * @param ctx         Click object. 
 * 
 * @param sys_mon
 * - 0x00 ( RTD2_MEAS_NORM )   : Normal operation( default ).
 * - 0x01 ( RTD2_MEAS_OFFSET ) : Offset calibration.
 * - 0x02 ( RTD2_MEAS_GAIN )   : Gain calibration.
 * - 0x03 ( RTD2_MEAS_TEMP )   : Temperature measuremen.
 * - 0x05 ( RTD2_MEAS_REF0 )   : REF0 monitor.
 * - 0x06 ( RTD2_MEAS_AVDD )   : Analog supply monitor.
 * - 0x07 ( RTD2_MEAS_DVDD )   : Digital supply monitor.
 *
 * @description The function set system monitor control of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_system_monitor ( rtd2_t *ctx, uint8_t sys_mon );

/**
 * @brief Set system control function.
 *
 * @param ctx         Click object. 
 *
 * @param gain
 * - 0x00 ( RTD2_GAIN_1 )   : Gain of the PGA = 1( default ).
 * - 0x10 ( RTD2_GAIN_2 )   : Gain of the PGA = 2.
 * - 0x20 ( RTD2_GAIN_4 )   : Gain of the PGA = 4.
 * - 0x30 ( RTD2_GAIN_8 )   : Gain of the PGA = 8.
 * - 0x40 ( RTD2_GAIN_16 )  : Gain of the PGA = 16.
 * - 0x50 ( RTD2_GAIN_32 )  : Gain of the PGA = 32.
 * - 0x60 ( RTD2_GAIN_64 )  : Gain of the PGA = 64.
 * - 0x70 ( RTD2_GAIN_128 ) : Gain of the PGA = 128.
 *
 * @param output_rate
 * - 0x00 ( RTD2_DR_5 )    : Data output rate of the ADC, DR = 5 SPS( default ).
 * - 0x01 ( RTD2_DR_10 )   : Data output rate of the ADC, DR = 10 SPS.
 * - 0x02 ( RTD2_DR_20 )   : Data output rate of the ADC, DR = 20 SPS.
 * - 0x03 ( RTD2_DR_40 )   : Data output rate of the ADC, DR = 40 SPS.
 * - 0x04 ( RTD2_DR_80 )   : Data output rate of the ADC, DR = 80 SPS.
 * - 0x05 ( RTD2_DR_160 )  : Data output rate of the ADC, DR = 160 SPS.
 * - 0x06 ( RTD2_DR_320 )  : Data output rate of the ADC, DR = 320 SPS.
 * - 0x07 ( RTD2_DR_640 )  : Data output rate of the ADC, DR = 6400 SPS.
 * - 0x08 ( RTD2_DR_1000 ) : Data output rate of the ADC, DR = 1000 SPS.
 * - 0x09 ( RTD2_DR_2000 ) : Data output rate of the ADC, DR = 2000 SPS.
 *
 * @description The function set system control of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_system_control ( rtd2_t *ctx, uint8_t gain, uint8_t output_rate );

/**
 * @brief Set IDAC current magnitude function.
 *
 * @param ctx         Click object. 
 * 
 * @param c_idac 
 * - 0x00 ( RTD2_IDAC_OFF )  : Off( default ).
 * - 0x01 ( RTD2_IDAC_50 )   : 50 �A.
 * - 0x02 ( RTD2_IDAC_100 )  : 100 �A.
 * - 0x03 ( RTD2_IDAC_250 )  : 250 �A.
 * - 0x04 ( RTD2_IDAC_500 )  : 500 �A.
 * - 0x05 ( RTD2_IDAC_750 )  : 750 �A.
 * - 0x06 ( RTD2_IDAC_1000 ) : 1000 �A.
 * - 0x07 ( RTD2_IDAC_1500 ) : 1500 �A.
 *
 * @description The function set IDAC excitation current magnitude of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_idac_current_mag ( rtd2_t *ctx, uint8_t c_idac );

/**
 * @brief Set IDAC current out function.
 *
 * @param ctx         Click object. 
 * 
 * @param c_out_1
 * - 0x00 ( RTD2_IDAC1_A0 ) : AIN0.
 * - 0x08 ( RTD2_IDAC1_A1 ) : AIN1.
 * - 0x10 ( RTD2_IDAC1_A2 ) : AIN2.
 * - 0x18 ( RTD2_IDAC1_A3 ) : AIN3.
 *
 * @param c_out_2
 * - 0x00 ( RTD2_IDAC2_A0 ) : AIN0.
 * - 0x01 ( RTD2_IDAC2_A1 ) : AIN1.
 * - 0x02 ( RTD2_IDAC2_A2 ) : AIN2.
 * - 0x04 ( RTD2_IDAC2_A3 ) : AIN3.
 *
 * @description The function set IDAC excitation current output 1 and 2, of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
void rtd2_set_idac_current_out ( rtd2_t *ctx, uint8_t c_out_1, uint8_t c_out_2 );

/**
 * @brief Check new data ready function.
 *
 * @param ctx         Click object. 
 * 
 * @return
 * - 0x00 ( RTD2_NEW_DATA_IS_NOT_READY ) : New data is not ready.
 * - 0x01 ( RTD2_NEW_DATA_IS_READY )     : New data is ready.
 *
 * @description The function check new data ready of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
uint8_t rtd2_check_new_data_ready ( rtd2_t *ctx );

/**
 * @brief Read output data function.
 *
 * @param ctx         Click object. 
 * 
 * @return read 24-bit ( signed ) output data.
 *
 * @description The function read output data of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
int32_t rtd2_read_output_data ( rtd2_t *ctx );

/**
 * @brief Calculate temperature function.
 *
 * @param ctx         Click object. 
 * 
 * @param adc_val     24-bit ( signed ) ADC output data.
 *
 * @return float temperature in degrees Celsius.
 *
 * @description The function calculates the temperature of the
 * 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
float rtd2_calc_temperature ( int32_t adc_val );

/**
 * @brief Get temperature function.
 *
 * @param ctx         Click object. 
 * 
 * @return float temperature in degrees Celsius.
 *
 * @description The function read output data and
 * return ambient temperature from the PT100 3-wire temperature probe
 * wired to the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board.
**/
float rtd2_get_temperature ( rtd2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RTD2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END

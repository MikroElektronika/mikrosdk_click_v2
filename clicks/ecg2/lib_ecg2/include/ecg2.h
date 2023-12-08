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
 * @file ecg2.h
 * @brief This file contains API for ECG 2 Click Driver.
 */

#ifndef ECG2_H
#define ECG2_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup ecg2 ECG 2 Click Driver
 * @brief API for configuring and manipulating ECG 2 Click driver.
 * @{
 */

/**
 * @defgroup ecg2_reg ECG 2 Registers List
 * @brief List of registers of ECG 2 Click driver.
 */

/**
 * @addtogroup ecg2_reg
 * @{
 */

/**
 * @brief ECG 2 description register.
 * @details Specified register for description of ECG 2 Click driver.
 */
#define ECG2_ID_REG                                                0x00
#define ECG2_CONFIG1_REG                                           0x01
#define ECG2_CONFIG2_REG                                           0x02
#define ECG2_CONFIG3_REG                                           0x03
#define ECG2_LOFF_REG                                              0x04
#define ECG2_CH1SET_REG                                            0x05
#define ECG2_CH2SET_REG                                            0x06
#define ECG2_CH3SET_REG                                            0x07
#define ECG2_CH4SET_REG                                            0x08
#define ECG2_CH5SET_REG                                            0x09
#define ECG2_CH6SET_REG                                            0x0A
#define ECG2_CH7SET_REG                                            0x0B
#define ECG2_CH8SET_REG                                            0x0C
#define ECG2_RLD_SENSP_REG                                         0x0D
#define ECG2_RLD_SENSN_REG                                         0x0E
#define ECG2_LOFF_SENSP_REG                                        0x0F
#define ECG2_LOFF_SENSN_REG                                        0x10
#define ECG2_LOFF_FLIP_REG                                         0x11
#define ECG2_LOFF_STATP_REG                                        0x12
#define ECG2_LOFF_STATN_REG                                        0x13
#define ECG2_GPIO_REG                                              0x14
#define ECG2_PACE_REG                                              0x15
#define ECG2_CONFIG4_REG                                           0x17
#define ECG2_WCT1_REG                                              0x18
#define ECG2_WCT2_REG                                              0x19

/*! @} */ // ecg2_reg

/**
 * @defgroup ecg2_set ECG 2 Registers Settings
 * @brief Settings for registers of ECG 2 Click driver.
 */

/**
 * @addtogroup ecg2_set
 * @{
 */

/**
 * @brief ECG 2 description setting.
 * @details Specified setting for description of ECG 2 Click driver.
 */

/**
 * @brief ECG 2 commands.
 * @details Specified commands for description of ECG 2 Click driver.
 */
#define ECG2_WAKEUP_CMD                                             0x02
#define ECG2_STANDBY_CMD                                            0x04
#define ECG2_RESET_CMD                                              0x06
#define ECG2_START_CONVERSION                                       0x08
#define ECG2_STOP_CONVERSION                                        0x0A
#define ECG2_ENABLE_READ_DATA_CONT_MODE                             0x10
#define ECG2_STOP_DATA_CONT_MODE                                    0x11
#define ECG2_READ_DATA_CMD                                          0x12
#define ECG2_SPI_CMD_WRITE                                          0x40
#define ECG2_SPI_CMD_READ                                           0x20

/**
 * @brief ECG 2 config register default values.
 * @details Specified config register default values of ECG 2 Click driver.
 */
#define ECG2_CONFIG1_REG_DEFAULT_VAL                                0x04
#define ECG2_CONFIG2_REG_DEFAULT_VAL                                0x20
#define ECG2_CONFIG3_REG_DEFAULT_VAL                                0x40

/**
 * @brief ECG 2 read type settings.
 * @details Specified read type settings of ECG 2 Click driver.
 */
#define ECG2_CFG_DAISY_ENABLE                                       0x00
#define ECG2_CFG_MULTI_READBACK                                     0x40

/**
 * @brief ECG 2 clock settings.
 * @details Specified clock settings of ECG 2 Click driver.
 */
#define ECG2_CFG_CLK_ENABLE                                         0x20
#define ECG2_CFG_CLK_DISABLE                                        0x00

/**
 * @brief ECG 2 data speed settings.
 * @details Specified data speed settings of ECG 2 Click driver.
 */
#define ECG2_CFG_DATA_SPEED_8K                                      0x00
#define ECG2_CFG_DATA_SPEED_4K                                      0x01
#define ECG2_CFG_DATA_SPEED_2K                                      0x02
#define ECG2_CFG_DATA_SPEED_1K                                      0x03
#define ECG2_CFG_DATA_SPEED_500                                     0x04
#define ECG2_CFG_DATA_SPEED_250                                     0x05
#define ECG2_CFG_DATA_SPEED_125                                     0x06
#define ECG2_CFG_DATA_SPEED_OFF                                     0x07

/**
 * @brief ECG 2 data speed settings.
 * @details Specified data speed settings of ECG 2 Click driver.
 */
#define ECG2_CFG_INT_TEST_EXT                                       0x10
#define ECG2_CFG_INT_TEST_INT                                       0x00

/**
 * @brief ECG 2 frequency divider settings.
 * @details Specified frequency divider settings of ECG 2 Click driver.
 */
#define ECG2_CFG_FREQ_F_DIV_2_TO_21                                 0x00
#define ECG2_CFG_FREQ_F_DIV_2_TO_20                                 0x01
#define ECG2_CFG_FREQ_NOT_USED                                      0x02
#define ECG2_CFG_FREQ_AT_DC                                         0x03

/**
 * @brief ECG 2 negative amplitude settings.
 * @details Specified negative amplitude settings of ECG 2 Click driver.
 */
#define ECG2_CFG_AMPLITUDE_NEGATIVE_1                               0x00
#define ECG2_CFG_AMPLITUDE_NEGATIVE_2                               0x01

/**
 * @brief ECG 2 internal buffer settings.
 * @details Specified internal buffer settings of ECG 2 Click driver.
 */
#define ECG2_CFG_ENABLE_INT_BUFFER                                  0x80
#define ECG2_CFG_DISABLE_INT_BUFFER                                 0x00

#define ECG2_CFG_REFBUF_ENABLE                                      0x80
#define ECG2_CFG_REFBUF_DISABLE                                     0x00

#define ECG2_CFG_INTERNAL_RLDREF                                    0x08
#define ECG2_CFG_EXTERNAL_RLDREF                                    0x00

#define ECG2_CFG_RLD_ENABLE                                         0x0C
#define ECG2_CFG_RLD_DISABLE                                        0x00

#define ECG2_CFG_RLD_SENSE_ENABLE                                   0x02
#define ECG2_CFG_RLD_SENSE_DISABLE                                  0x00

#define ECG2_CFG_RLD_NOT_CONNECTED                                  0x01
#define ECG2_CFG_RLD_CONNECTED                                      0x00

/**
 * @brief ECG 2 Vref settings.
 * @details Specified Vref settings of ECG 2 Click driver.
 */
#define ECG2_CFG_VREF_2V4                                          0x00
#define ECG2_CFG_VREF_4V                                            0x20

/**
 * @brief ECG 2 positive comparator settings.
 * @details Specified positive comparator settings of ECG 2 Click driver.
 */
#define ECG2_CFG_COMPARATOR_P_95                                    0x00
#define ECG2_CFG_COMPARATOR_P_92_5                                  0x20
#define ECG2_CFG_COMPARATOR_P_90                                    0x40
#define ECG2_CFG_COMPARATOR_P_87_5                                  0x60
#define ECG2_CFG_COMPARATOR_P_85                                    0x80
#define ECG2_CFG_COMPARATOR_P_80                                    0xA0
#define ECG2_CFG_COMPARATOR_P_75                                    0xC0
#define ECG2_CFG_COMPARATOR_P_70                                    0xE0

/**
 * @brief ECG 2 negative comparator settings.
 * @details Specified negative comparator settings of ECG 2 Click driver.
 */
#define ECG2_CFG_COMPARATOR_N_5                                     0x00
#define ECG2_CFG_COMPARATOR_N_7_5                                   0x20
#define ECG2_CFG_COMPARATOR_N_10                                    0x40
#define ECG2_CFG_COMPARATOR_N_12_5                                  0x60
#define ECG2_CFG_COMPARATOR_N_15                                    0x80
#define ECG2_CFG_COMPARATOR_N_20                                    0xA0
#define ECG2_CFG_COMPARATOR_N_25                                    0xC0
#define ECG2_CFG_COMPARATOR_N_30                                    0xE0

/**
 * @brief ECG 2 lead settings.
 * @details Specified lead settings of ECG 2 Click driver.
 */
#define ECG2_CFG_VLEAD_OFF                                          0x00
#define ECG2_CFG_VLEAD_EN                                           0x10

#define ECG2_CFG_ILEAD_OFF_4nA                                      0x00
#define ECG2_CFG_ILEAD_OFF_8nA                                      0x04        
#define ECG2_CFG_ILEAD_OFF_12nA                                     0x08
#define ECG2_CFG_ILEAD_OFF_16nA                                     0x0C

#define ECG2_CFG_FLEAD_OFF_AC_OFF                                   0x01
#define ECG2_CFG_FLEAD_OFF_NOT_USED                                 0x02
#define ECG2_CFG_FLEAD_OFF_DC_OFF                                   0x03

/**
 * @brief ECG 2 mode settings.
 * @details Specified mode settings of ECG 2 Click driver.
 */
#define ECG2_CFG_NORMAL_MODE                                        0x00
#define ECG2_CFG_POWER_DOWN                                         0x80

/**
 * @brief ECG 2 gain settings.
 * @details Specified gain settings of ECG 2 Click driver.
 */
#define ECG2_CFG_PGA_GAIN_6                                         0x00
#define ECG2_CFG_PGA_GAIN_1                                         0x01
#define ECG2_CFG_PGA_GAIN_2                                         0x02
#define ECG2_CFG_PGA_GAIN_3                                         0x03
#define ECG2_CFG_PGA_GAIN_4                                         0x04
#define ECG2_CFG_PGA_GAIN_8                                         0x05
#define ECG2_CFG_PGA_GAIN_12                                        0x06

/**
 * @brief ECG 2 MUX settings.
 * @details Specified MUX settings of ECG 2 Click driver.
 */
#define ECG2_CFG_MUX_NORMAL_ELECTRODE                               0x00
#define ECG2_CFG_MUX_SHORTED_INPUT                                  0x01
#define ECG2_CFG_MUX_RLD_MEASURMENTS                                0x02
#define ECG2_CFG_MUX_MVDD_MEASURMENTS                               0x03
#define ECG2_CFG_MUX_TEMPERATURE_SENSOR                             0x04
#define ECG2_CFG_MUX_TEST_SIGNAL                                    0x05
#define ECG2_CFG_MUX_RLD_DRP                                        0x06
#define ECG2_CFG_MUX_RLD_DRN                                        0x07

/**
 * @brief ECG 2 channel settings.
 * @details Specified channel settings of ECG 2 Click driver.
 */
#define ECG2_CHANNEL_ODD_CHANNEL_1                                  0x00
#define ECG2_CHANNEL_ODD_CHANNEL_3                                  0x01
#define ECG2_CHANNEL_ODD_CHANNEL_5                                  0x02
#define ECG2_CHANNEL_ODD_CHANNEL_7                                  0x03

#define ECG2_CHANNEL_EVEN_CHANNEL_2                                 0x00
#define ECG2_CHANNEL_EVEN_CHANNEL_4                                 0x01
#define ECG2_CHANNEL_EVEN_CHANNEL_6                                 0x02
#define ECG2_CHANNEL_EVEN_CHANNEL_8                                 0x03

#define ECG2_CHANNEL_ENABLE                                         0x01
#define ECG2_CHANNEL_DISABLE                                        0x00

#define ECG2_DATA_READY                                             0x01
/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ecg2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ECG2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ECG2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ecg2_set

/**
 * @defgroup ecg2_map ECG 2 MikroBUS Map
 * @brief MikroBUS pin mapping of ECG 2 Click driver.
 */

/**
 * @addtogroup ecg2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ECG 2 Click to the selected MikroBUS.
 */
#define ECG2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwd = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.drd = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ecg2_map
/*! @} */ // ecg2

/**
 * @brief ECG 2 Click context object.
 * @details Context object definition of ECG 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< System reset	. */
    digital_out_t  pwd;         /**< Power Down. */

    // Input pins
    digital_in_t  drd;          /**< Data Ready. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    analog_in_t  adc;           /**< ADC module object. */

} ecg2_t;

/**
 * @brief ECG 2 Click configuration object.
 * @details Configuration object definition of ECG 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;          /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;          /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;           /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;            /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  an;            /**< ADC module object. */
    pin_name_t  rst;           /**< System reset	. */
    pin_name_t  pwd;           /**< Power Down. */
    pin_name_t  drd;           /**< Data Ready. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
} ecg2_cfg_t;

/**
 * @brief ECG 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ECG2_OK = 0,
    ECG2_ERROR = -1

} ecg2_return_value_t;

/*!
 * @addtogroup ecg2 ECG 2 Click Driver
 * @brief API for configuring and manipulating ECG 2 Click driver.
 * @{
 */

/**
 * @brief ECG 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ecg2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ecg2_cfg_setup ( ecg2_cfg_t *cfg );

/**
 * @brief ECG 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ecg2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_init ( ecg2_t *ctx, ecg2_cfg_t *cfg );

/**
 * @brief ECG 2 default configuration function.
 * @details This function executes a default configuration of ECG 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ecg2_default_cfg ( ecg2_t *ctx );

/**
 * @brief ECG 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_generic_write ( ecg2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ECG 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_generic_read ( ecg2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ECG 2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_read_an_pin_value ( ecg2_t *ctx, uint16_t *data_out );

/**
 * @brief ECG 2 register data write function.
 * @details This function writes a data bytes to
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_write_register ( ecg2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ECG 2 register data reading function.
 * @details This function reads a data bytes from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_read_register ( ecg2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ECG 2 data multi writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_multi_write ( ecg2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ECG 2 data multi reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_multi_read ( ecg2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ECG 2 send command function.
 * @details This function sends a command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] command : Command to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_send_command ( ecg2_t *ctx, uint8_t command );

/**
 * @brief ECG 2 hardware reset function.
 * @details This function is used to perform a hardware reset.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @return Nothing.
 */
void ecg2_hw_reset ( ecg2_t *ctx );

/**
 * @brief ECG 2 get device id function.
 * @details This function reads device id by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @return Device ID
 */
uint8_t ecg2_get_device_id( ecg2_t *ctx );

/**
 * @brief ECG 2 configure channel function.
 * @details This function configure selected channel by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] channel : Selected channel.
 * @param[in] enable : State of the selected channel.
 * @param[in] pga_gain : Settings for channel pga gain.
 * @param[in] channel_input : Settings for channel input mode.
 * @return Nothing.
 */
err_t ecg2_configure_channel ( ecg2_t *ctx, uint8_t channel, uint8_t enable, uint8_t pga_gain, 
                                int8_t channel_input);

/**
 * @brief ECG 2 right leg positive drive settings function.
 * @details This function configuring right leg positive drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void ecg2_right_leg_positive_drive_set ( ecg2_t *ctx, uint8_t data_in );

/**
 * @brief ECG 2 right leg negative drive settings function.
 * @details This function configuring right leg negative drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void ecg2_right_leg_negative_drive_set ( ecg2_t *ctx, uint8_t data_in );

/**
 * @brief ECG 2 lead off positive drive settings function.
 * @details This function configuring lead off positive drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void ecg2_lead_off_positive_channel_select ( ecg2_t *ctx, uint8_t data_in );

/**
 * @brief ECG 2 lead off negative drive settings function.
 * @details This function configuring lead off negative drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void ecg2_lead_off_negative_channel_select ( ecg2_t *ctx, uint8_t data_in );

/**
 * @brief ECG 2 lead off current direction drive settings function.
 * @details This function configuring lead off current direction drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void ecg2_lead_off_current_direction_select ( ecg2_t *ctx, uint8_t data_in );

/**
 * @brief ECG 2 pace detect even chanels drive settings function.
 * @details This function configuring pace detect even chanels drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t ecg2_pace_detect_even_channels_select ( ecg2_t *ctx, uint8_t select );

/**
 * @brief ECG 2 pace detect odd chanels drive settings function.
 * @details This function configuring pace detect odd chanels drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t ecg2_pace_detect_odd_channels_select ( ecg2_t *ctx, uint8_t select );

/**
 * @brief ECG 2 right leg positive drive settings function.
 * @details This function configuring right leg positive drive by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 */
void ecg2_wilson_center_terminal_configure ( ecg2_t *ctx, uint16_t set );

/**
 * @brief ECG 2 is data ready function.
 * @details This function gets state of DRD pin.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @return State of DRD pin.
 */
uint8_t ecg2_data_ready ( ecg2_t *ctx );

/**
 * @brief ECG 2 read ADC data function.
 * @details This function reads raw ADC data by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[out] data_out : Read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_read_data ( ecg2_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief ECG 2 read data channel function.
 * @details This function reads ADC data of selected channel by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ecg2_t object definition for detailed explanation.
 * @param[in] channel : Selected channel .
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg2_read_channel_data ( ecg2_t *ctx, uint8_t channel, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ECG2_H

/*! @} */ // ecg2

// ------------------------------------------------------------------------ END

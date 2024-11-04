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
 * @file hodcap.h
 * @brief This file contains API for HOD CAP Click Driver.
 */

#ifndef HODCAP_H
#define HODCAP_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup hodcap HOD CAP Click Driver
 * @brief API for configuring and manipulating HOD CAP Click driver.
 * @{
 */

/**
 * @defgroup hodcap_reg HOD CAP Registers List
 * @brief List of registers of HOD CAP Click driver.
 */

/**
 * @addtogroup hodcap_reg
 * @{
 */

/**
 * @brief HOD CAP description register.
 * @details Specified register for description of HOD CAP Click driver.
 */
#define HODCAP_REG_SENSOR_ID                          0x01
#define HODCAP_REG_STATUS                             0x02
#define HODCAP_REG_I_DATA                             0x03
#define HODCAP_REG_Q_DATA                             0x04
#define HODCAP_REG_ADC_STATUS                         0x05
#define HODCAP_REG_EDIV                               0x20
#define HODCAP_REG_FREQ                               0x21
#define HODCAP_REG_TXV                                0x22
#define HODCAP_REG_MUX_CTRL                           0x23
#define HODCAP_REG_SDG                                0x24
#define HODCAP_REG_CBG                                0x25
#define HODCAP_REG_DCLK                               0x26
#define HODCAP_REG_PGA                                0x27
#define HODCAP_REG_PGA_OFFSET_I                       0x28
#define HODCAP_REG_PGA_OFFSET_Q                       0x29
#define HODCAP_REG_ADCTL                              0x2A
#define HODCAP_REG_BLANK                              0x2B
#define HODCAP_REG_DIAG_MUX_CTRL                      0x2C
#define HODCAP_REG_QUICK_READ                         0x90

/**
 * @brief HOD CAP description command.
 * @details Specified command for description of HOD CAP Click driver.
 */
#define HODCAP_CMD_WRITE                              0x10
#define HODCAP_CMD_READ                               0x00
#define HODCAP_CMD_QUICK_READ                         0x90

/*! @} */ // hodcap_reg

/**
 * @defgroup hodcap_set HOD CAP Registers Settings
 * @brief Settings for registers of HOD CAP Click driver.
 */

/**
 * @addtogroup hodcap_set
 * @{
 */

/**
 * @brief HOD CAP sensor ID value.
 * @details Specified sensor ID value of HOD CAP Click driver.
 */
#define HODCAP_SENSOR_ID                              0xA431u

/**
 * @brief HOD CAP ADC data ready value.
 * @details ADC data ready value of HOD CAP Click driver.
 */
#define HODCAP_ADC_DATA_READY                         0x0001u

/**
 * @brief HOD CAP division factor values.
 * @details Division factor values of HOD CAP Click driver.
 */
#define HODCAP_SET_EDIV_12                            0x0000u
#define HODCAP_SET_EDIV_11                            0x0001u
#define HODCAP_SET_EDIV_10                            0x0002u
#define HODCAP_SET_EDIV_9                             0x0003u
#define HODCAP_SET_EDIV_8                             0x0004u
#define HODCAP_SET_EDIV_7                             0x0005u
#define HODCAP_SET_EDIV_6                             0x0006u
#define HODCAP_SET_EDIV_5                             0x0007u
#define HODCAP_SET_EDIV_4                             0x0008u
#define HODCAP_SET_EDIV_3                             0x0009u
#define HODCAP_SET_EDIV_2                             0x000Au
#define HODCAP_SET_EDIV_1                             0x000Bu
#define HODCAP_SET_EDIV_BIT_MASK                      0x000Fu

/**
 * @brief HOD CAP sine wave generator frequency values.
 * @details Sine wave generator frequency values of HOD CAP Click driver.
 */
#define HODCAP_SET_FREQ_45_45KHZ                      0x0000u
#define HODCAP_SET_FREQ_71_4KHZ                       0x0001u
#define HODCAP_SET_FREQ_100KHZ                        0x0002u
#define HODCAP_SET_FREQ_125KHZ                        0x0003u

/**
 * @brief HOD CAP transmitter output AC voltage values.
 * @details Transmitter output AC voltage values of HOD CAP Click driver.
 */
#define HODCAP_SET_TXV_0V                             0x0000u
#define HODCAP_SET_TXV_0_5V                           0x0001u
#define HODCAP_SET_TXV_1V                             0x0002u

/**
 * @brief HOD CAP MUX Control values.
 * @details MUX Control values of HOD CAP Click driver.
 */
#define HODCAP_SET_MUX_CTRL_MODE_OPEN                 0x0000u
#define HODCAP_SET_MUX_CTRL_MODE_SENSOR_DRV           0x0001u
#define HODCAP_SET_MUX_CTRL_MODE_COMMON               0x0002u
#define HODCAP_SET_MUX_CTRL_MODE_NO_OP                0x0003u
#define HODCAP_SET_MUX_CTRL_SEL_SEN0                  0x0000u
#define HODCAP_SET_MUX_CTRL_SEL_SEN1                  0x0004u
#define HODCAP_SET_MUX_CTRL_SEL_SEN2                  0x0008u
#define HODCAP_SET_MUX_CTRL_SEL_SEN3                  0x000Cu
#define HODCAP_SET_MUX_CTRL_SEL_SEN4                  0x0010u
#define HODCAP_SET_MUX_CTRL_SEL_SEN5                  0x0014u
#define HODCAP_SET_MUX_CTRL_SEL_SEN6                  0x0018u
#define HODCAP_SET_MUX_CTRL_SEL_SEN7                  0x001Cu
#define HODCAP_SET_MUX_CTRL_SEL_SEN8                  0x0020u
#define HODCAP_SET_MUX_CTRL_SEL_SEN9                  0x0024u
#define HODCAP_SET_MUX_CTRL_SEL_NONE                  0x0028u
#define HODCAP_SET_MUX_CTRL_SEL_VAR_SEN               0x002Cu
#define HODCAP_SET_MUX_CTRL_SEL_BIT_MASK              0x003Cu

/**
 * @brief HOD CAP total number of channels value.
 * @details Total number of channels value of HOD CAP Click driver.
 */
#define HODCAP_TOTAL_NUMBER_OF_CHANNELS                   10

/**
 * @brief HOD CAP PGA voltage gain control values.
 * @details PGA voltage gain control values of HOD CAP Click driver.
 */
#define HODCAP_SET_PGA_GAIN_36                        0x0000u
#define HODCAP_SET_PGA_GAIN_24                        0x0001u
#define HODCAP_SET_PGA_GAIN_16                        0x0002u
#define HODCAP_SET_PGA_GAIN_10_67                     0x0003u
#define HODCAP_SET_PGA_GAIN_7_11                      0x0004u
#define HODCAP_SET_PGA_GAIN_4_74                      0x0005u
#define HODCAP_SET_PGA_GAIN_3_16                      0x0006u
#define HODCAP_SET_PGA_GAIN_2_11                      0x0007u

/**
 * @brief HOD CAP PGA I/Q offset values.
 * @details PGA I/Q offset values of HOD CAP Click driver.
 */
#define HODCAP_SET_DEFAULT_PGA_OFFSET_I                  96
#define HODCAP_SET_DEFAULT_PGA_OFFSET_Q                 144

/**
 * @brief HOD CAP ADC control values.
 * @details ADC control values of HOD CAP Click driver.
 */
#define HODCAP_SET_ADCTL_MODE_RESET_STOP              0x0000u
#define HODCAP_SET_ADCTL_MODE_START_SINGLE_CONVO      0x0001u
#define HODCAP_SET_ADCTL_MODE_START_CONT_CONVO        0x0002u
#define HODCAP_SET_ADCTL_MODE_STOP_CURRENT_CONVO      0x0003u
#define HODCAP_SET_ADCTL_MODE_BIT_MASK                0x0003u
#define HODCAP_SET_ADCTL_CS_CLK_250KHZ                0x0000u
#define HODCAP_SET_ADCTL_CS_CLK_500KHZ                0x0004u
#define HODCAP_SET_ADCTL_CS_CLK_1000KHZ               0x0008u
#define HODCAP_SET_ADCTL_ACCU_NUMB_OF_SAMPLES_4       0x0000u
#define HODCAP_SET_ADCTL_ACCU_NUMB_OF_SAMPLES_8       0x0010u
#define HODCAP_SET_ADCTL_ACCU_NUMB_OF_SAMPLES_16      0x0020u
#define HODCAP_SET_ADCTL_TS_400US                     0x0000u
#define HODCAP_SET_ADCTL_TS_576US                     0x0040u
#define HODCAP_SET_ADCTL_TS_664US                     0x0080u

/**
 * @brief HOD CAP diagnostic MUX control values.
 * @details Diagnostic MUX control values of HOD CAP Click driver.
 */
#define HODCAP_SET_MUX_CTRL_PLUS_SEN0                 0x0000u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN1                 0x0001u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN2                 0x0002u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN3                 0x0003u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN4                 0x0004u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN5                 0x0005u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN6                 0x0006u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN7                 0x0007u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN8                 0x0008u
#define HODCAP_SET_MUX_CTRL_PLUS_SEN9                 0x0009u
#define HODCAP_SET_MUX_CTRL_PLUS_VAR_SEN              0x000Bu
#define HODCAP_SET_MUX_CTRL_PLUS_NONE                 0x000Fu
#define HODCAP_SET_MUX_CTRL_MINUS_SEN0                0x0000u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN1                0x0010u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN2                0x0020u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN3                0x0030u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN4                0x0040u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN5                0x0050u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN6                0x0060u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN7                0x0070u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN8                0x0080u
#define HODCAP_SET_MUX_CTRL_MINUS_SEN9                0x0090u
#define HODCAP_SET_MUX_CTRL_MINUS_VAR_SEN             0x00B0u
#define HODCAP_SET_MUX_CTRL_MINUS_NONE                0x00F0u

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hodcap_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HODCAP_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HODCAP_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hodcap_set

/**
 * @defgroup hodcap_map HOD CAP MikroBUS Map
 * @brief MikroBUS pin mapping of HOD CAP Click driver.
 */

/**
 * @addtogroup hodcap_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HOD CAP Click to the selected MikroBUS.
 */
#define HODCAP_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.clk  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // hodcap_map
/*! @} */ // hodcap

/**
 * @brief HOD CAP Click context object.
 * @details Context object definition of HOD CAP Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t clk;           /**< External clock pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} hodcap_t;

/**
 * @brief HOD CAP Click configuration object.
 * @details Configuration object definition of HOD CAP Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t clk;             /**< External clock pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hodcap_cfg_t;

/**
 * @brief HOD CAP Click status object.
 * @details Status object definition of HOD CAP Click driver.
 */
typedef struct
{
    uint8_t    r_ediv;    /**< System CLK Divider Selection. */ 
    uint8_t    otpf;      /**< Signature of the OTP is wrong. */ 
    uint8_t    ppsf;      /**< Pin-to-Pin short Error. */ 
    uint8_t    bpff;      /**< Voltage of internal filter is exceeding the op range. */ 
    uint8_t    regf;      /**< Regulator voltage is exceeding the op range. */ 
    uint8_t    ocsld;     /**< Current exceeds the maximum limit. */ 
    uint8_t    ocsen;     /**< Current exceeds the maximum limit. */ 
    uint8_t    test;      /**< Test status. */ 
    uint8_t    tx1f;      /**< Output voltage of sensor driver is exceeding the op range. */ 
    uint8_t    tx2f;      /**< Output voltage of VAR_SEN driver is exceeding the op range. */ 
    uint8_t    pga1f;     /**< I channel is saturated high or low. */ 
    uint8_t    pga2f;     /**< Q channel is saturated high or low. */ 
    uint8_t    nclk;      /**< Clock is missing or invalid. */ 
    uint8_t    cbf;       /**< Output voltage of current buffer is exceeding the op range. */ 

} hodcap_status_t;

/**
 * @brief HOD CAP Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HODCAP_OK = 0,
    HODCAP_ERROR = -1

} hodcap_return_value_t;

/*!
 * @addtogroup hodcap HOD CAP Click Driver
 * @brief API for configuring and manipulating HOD CAP Click driver.
 * @{
 */

/**
 * @brief HOD CAP configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hodcap_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hodcap_cfg_setup ( hodcap_cfg_t *cfg );

/**
 * @brief HOD CAP initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hodcap_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_init ( hodcap_t *ctx, hodcap_cfg_t *cfg );

/**
 * @brief HOD CAP default configuration function.
 * @details This function executes a default configuration of HOD CAP
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hodcap_default_cfg ( hodcap_t *ctx );

/**
 * @brief HOD CAP data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_generic_write ( hodcap_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief HOD CAP data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_generic_read ( hodcap_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief HOD CAP write register function.
 * @details This function writes a 16-bit data to
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_write_reg ( hodcap_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief HOD CAP read register function.
 * @details This function reads a 16-bit data from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_read_reg ( hodcap_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief HOD CAP gets sensor ID function.
 * @details This function reads a sensor ID 
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[out] sensor_id : Sensor ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_get_sensor_id ( hodcap_t *ctx, uint16_t *sensor_id );

/**
 * @brief HOD CAP gets sensor status function.
 * @details This function reads a sensor status data
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[out] status : Sensor status object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_get_status ( hodcap_t *ctx, hodcap_status_t *status );

/**
 * @brief HOD CAP check ADC data ready function.
 * @details This function check if ADC data is ready
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[out] data_ready : ADC data ready.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_check_adc_data_ready ( hodcap_t *ctx, uint16_t *data_ready );

/**
 * @brief HOD CAP sets the ADC operation mode function.
 * @details This function configure the ADC operation mode
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] adc_op_mode : ADC operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_set_adc_op_mode ( hodcap_t *ctx, uint16_t adc_op_mode );

/**
 * @brief HOD CAP MUX channel selection function.
 * @details This function is used to select the desired channel (SEN)
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] sen_pos : Channel (SEN) position [0-9].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_mux_channel_selection ( hodcap_t *ctx, uint8_t sen_pos );

/**
 * @brief HOD CAP gets the I and Q data function.
 * @details This function reads the I-Channel and Q-Channel data 
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[out] i_data : I data values.
 * @param[out] q_data : Q data values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_get_i_q_data ( hodcap_t *ctx, uint16_t *i_data, uint16_t *q_data );

/**
 * @brief HOD CAP wait ADC data ready function.
 * @details This function wait until ADC has completed accumulation
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error/Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hodcap_wait_adc_data_ready ( hodcap_t *ctx );

/**
 * @brief HOD CAP set CLK pin state function.
 * @details This function sets CLK (PWM) pin state
 * of the AS8579 Capacitive Sensor on the HOD CAP Click board™.
 * @param[in] ctx : Click context object.
 * See #hodcap_t object definition for detailed explanation.
 * @param[in] clk_state : Logic value to write.
 * @return Nothing.
 * @note None.
 */
void hodcap_set_clk_state ( hodcap_t *ctx, uint8_t clk_state );

#ifdef __cplusplus
}
#endif
#endif // HODCAP_H

/*! @} */ // hodcap

// ------------------------------------------------------------------------ END

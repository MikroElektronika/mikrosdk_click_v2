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
 * @file ultrasonic5.h
 * @brief This file contains API for Ultrasonic 5 Click Driver.
 */

#ifndef ULTRASONIC5_H
#define ULTRASONIC5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_analog_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup ultrasonic5 Ultrasonic 5 Click Driver
 * @brief API for configuring and manipulating Ultrasonic 5 Click driver.
 * @{
 */

/**
 * @defgroup ultrasonic5_reg Ultrasonic 5 Registers List
 * @brief List of registers of Ultrasonic 5 Click driver.
 */

/**
 * @addtogroup ultrasonic5_reg
 * @{
 */

/**
 * @brief Ultrasonic 5 registers list.
 * @details Specified registers list of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_REG_BPF_CONFIG_1                0x10
#define ULTRASONIC5_REG_BPF_CONFIG_2                0x11
#define ULTRASONIC5_REG_DEV_CTRL_1                  0x12
#define ULTRASONIC5_REG_DEV_CTRL_2                  0x13
#define ULTRASONIC5_REG_DEV_CTRL_3                  0x14
#define ULTRASONIC5_REG_VDRV_CTRL                   0x16
#define ULTRASONIC5_REG_ECHO_INT_CONFIG             0x17
#define ULTRASONIC5_REG_ZC_CONFIG                   0x18
#define ULTRASONIC5_REG_BURST_PULSE                 0x1A
#define ULTRASONIC5_REG_TOF_CONFIG                  0x1B
#define ULTRASONIC5_REG_DEV_STAT                    0x1C
#define ULTRASONIC5_REG_DEVICE_ID                   0x1D
#define ULTRASONIC5_REG_REV_ID                      0x1E

/*! @} */ // ultrasonic5_reg

/**
 * @defgroup ultrasonic5_set Ultrasonic 5 Registers Settings
 * @brief Settings for registers of Ultrasonic 5 Click driver.
 */

/**
 * @addtogroup ultrasonic5_set
 * @{
 */

/**
 * @brief Ultrasonic 5 BPF_CONFIG_1 register settings.
 * @details Specified BPF_CONFIG_1 register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_BPF_CONFIG_1_FC_TRIM_FRC        0x80
#define ULTRASONIC5_BPF_CONFIG_1_BYPASS             0x40
#define ULTRASONIC5_BPF_CONFIG_1_HPF_FREQ_MASK      0x3F
#define ULTRASONIC5_BPF_CONFIG_1_RESET              0x00

/**
 * @brief Ultrasonic 5 BPF_CONFIG_2 register settings.
 * @details Specified BPF_CONFIG_2 register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_BPF_CONFIG_2_Q_SEL_4            0x00
#define ULTRASONIC5_BPF_CONFIG_2_Q_SEL_5            0x10
#define ULTRASONIC5_BPF_CONFIG_2_Q_SEL_2            0x20
#define ULTRASONIC5_BPF_CONFIG_2_Q_SEL_3            0x30
#define ULTRASONIC5_BPF_CONFIG_2_Q_SEL_MASK         0x30
#define ULTRASONIC5_BPF_CONFIG_2_FC_TRIM_MASK       0x0F
#define ULTRASONIC5_BPF_CONFIG_2_RESET              0x00

/**
 * @brief Ultrasonic 5 DEV_CTRL_1 register settings.
 * @details Specified DEV_CTRL_1 register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_DEV_CTRL_1_LOGAMP_FRC           0x80
#define ULTRASONIC5_DEV_CTRL_1_LOGAMP_SLP_ADJ_MASK  0x70
#define ULTRASONIC5_DEV_CTRL_1_LOGAMP_INT_ADJ_MASK  0x0F
#define ULTRASONIC5_DEV_CTRL_1_RESET                0x00

/**
 * @brief Ultrasonic 5 DEV_CTRL_2 register settings.
 * @details Specified DEV_CTRL_2 register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_DEV_CTRL_2_LOGAMP_DIS_FIRST     0x80
#define ULTRASONIC5_DEV_CTRL_2_LOGAMP_DIS_LAST      0x40
#define ULTRASONIC5_DEV_CTRL_2_VOUT_SCALE_SEL_5V    0x04
#define ULTRASONIC5_DEV_CTRL_2_LNA_GAIN_15V         0x00
#define ULTRASONIC5_DEV_CTRL_2_LNA_GAIN_10V         0x01
#define ULTRASONIC5_DEV_CTRL_2_LNA_GAIN_20V         0x02
#define ULTRASONIC5_DEV_CTRL_2_LNA_GAIN_12_5V       0x03
#define ULTRASONIC5_DEV_CTRL_2_LNA_GAIN_MASK        0x03
#define ULTRASONIC5_DEV_CTRL_2_RESET                0x00

/**
 * @brief Ultrasonic 5 DEV_CTRL_3 register settings.
 * @details Specified DEV_CTRL_3 register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_64US  0x00
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_48US  0x04
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_32US  0x08
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_24US  0x0C
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_16US  0x10
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_8US   0x14
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_4US   0x18
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_DIS   0x1C
#define ULTRASONIC5_DEV_CTRL_3_DRV_PLS_FLT_DT_MASK  0x1C
#define ULTRASONIC5_DEV_CTRL_3_IO_MODE_0            0x00
#define ULTRASONIC5_DEV_CTRL_3_IO_MODE_1            0x01
#define ULTRASONIC5_DEV_CTRL_3_IO_MODE_2            0x02
#define ULTRASONIC5_DEV_CTRL_3_IO_MODE_3            0x03
#define ULTRASONIC5_DEV_CTRL_3_IO_MODE_MASK         0x03
#define ULTRASONIC5_DEV_CTRL_3_RESET                0x00

/**
 * @brief Ultrasonic 5 VDRV_CTRL register settings.
 * @details Specified VDRV_CTRL register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_VDRV_CTRL_DIS_VDRV_REG_LSTN     0x40
#define ULTRASONIC5_VDRV_CTRL_VDRV_HI_Z             0x20
#define ULTRASONIC5_VDRV_CTRL_VDRV_CURR_LVL_20MA    0x10
#define ULTRASONIC5_VDRV_CTRL_VDRV_VOLT_LVL_5V      0x00
#define ULTRASONIC5_VDRV_CTRL_VDRV_VOLT_LVL_MASK    0x0F
#define ULTRASONIC5_VDRV_CTRL_RESET                 0x20

/**
 * @brief Ultrasonic 5 ECHO_INT_CONFIG register settings.
 * @details Specified ECHO_INT_CONFIG register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_ECHO_INT_CONFIG_CMP_EN          0x10
#define ULTRASONIC5_ECHO_INT_CONFIG_THR_SEL_MASK    0x0F
#define ULTRASONIC5_ECHO_INT_CONFIG_RESET           0x07

/**
 * @brief Ultrasonic 5 ZC_CONFIG register settings.
 * @details Specified ZC_CONFIG register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_ZC_CONFIG_CMP_EN                0x80
#define ULTRASONIC5_ZC_CONFIG_EN_ECHO_INT           0x40
#define ULTRASONIC5_ZC_CONFIG_CMP_IN_SEL            0x20
#define ULTRASONIC5_ZC_CONFIG_CMP_STG_SEL_MASK      0x18
#define ULTRASONIC5_ZC_CONFIG_CMP_HYST_MASK         0x07
#define ULTRASONIC5_ZC_CONFIG_RESET                 0x14

/**
 * @brief Ultrasonic 5 BURST_PULSE register settings.
 * @details Specified BURST_PULSE register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_BURST_PULSE_HALF_BRG_MODE       0x80
#define ULTRASONIC5_BURST_PULSE_PRE_DRIVER_MODE     0x40
#define ULTRASONIC5_BURST_PULSE_BURST_PULSE_16      0x0F
#define ULTRASONIC5_BURST_PULSE_BURST_PULSE_MASK    0x3F
#define ULTRASONIC5_BURST_PULSE_RESET               0x00

/**
 * @brief Ultrasonic 5 TOF_CONFIG register settings.
 * @details Specified TOF_CONFIG register settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_TOF_CONFIG_SLEEP_MODE_EN        0x80
#define ULTRASONIC5_TOF_CONFIG_STDBY_MODE_EN        0x40
#define ULTRASONIC5_TOF_CONFIG_VDRV_TRIGGER         0x02
#define ULTRASONIC5_TOF_CONFIG_CMD_TRIGGER          0x01
#define ULTRASONIC5_TOF_CONFIG_RESET                0x00

/**
 * @brief Ultrasonic 5 default PWM settings.
 * @details Specified setting for default PWM settings of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_DEF_FREQ                        40000
#define ULTRASONIC5_DEF_DYTY                        0.5f

/**
 * @brief Ultrasonic 5 device ID.
 * @details Specified device ID of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_DEVICE_ID                       0xB9

/**
 * @brief Ultrasonic 5 ODD parity flag.
 * @details Specified flag for ODD parity of Ultrasonic 5 Click driver.
 */
#define ULTRASONIC5_ODD_PARITY                      0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ultrasonic5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ULTRASONIC5_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define ULTRASONIC5_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ultrasonic5_set

/**
 * @defgroup ultrasonic5_map Ultrasonic 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Ultrasonic 5 Click driver.
 */

/**
 * @addtogroup ultrasonic5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ultrasonic 5 Click to the selected MikroBUS.
 */
#define ULTRASONIC5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.io1  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.io2  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.out4 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ultrasonic5_map
/*! @} */ // ultrasonic5

/**
 * @brief Ultrasonic 5 Click context object.
 * @details Context object definition of Ultrasonic 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t io1;              /**< IO1 burst generator pin. */

    // Input pins
    digital_in_t  out4;             /**< TUSS4470 OUT4 pin. */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */
    analog_in_t   adc;              /**< ADC module object. */
    pwm_t         pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t      pwm_freq;         /**< PWM frequency value. */
    pin_name_t    chip_select;      /**< Chip select pin descriptor (used for SPI driver). */

} ultrasonic5_t;

/**
 * @brief Ultrasonic 5 Click configuration object.
 * @details Configuration object definition of Ultrasonic 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t an;                  /**< Analog pin descriptor. */
    pin_name_t io2;                 /**< IO2 burst generator pin. */

    // Additional gpio pins
    pin_name_t io1;                 /**< IO1 burst generator pin. */
    pin_name_t out4;                /**< TUSS4470 OUT4 pin. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    
    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} ultrasonic5_cfg_t;

/**
 * @brief Ultrasonic 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ULTRASONIC5_OK = 0,
    ULTRASONIC5_ERROR = -1

} ultrasonic5_return_value_t;

/*!
 * @addtogroup ultrasonic5 Ultrasonic 5 Click Driver
 * @brief API for configuring and manipulating Ultrasonic 5 Click driver.
 * @{
 */

/**
 * @brief Ultrasonic 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ultrasonic5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ultrasonic5_cfg_setup ( ultrasonic5_cfg_t *cfg );

/**
 * @brief Ultrasonic 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ultrasonic5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_init ( ultrasonic5_t *ctx, ultrasonic5_cfg_t *cfg );

/**
 * @brief Ultrasonic 5 default configuration function.
 * @details This function executes a default configuration of Ultrasonic 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ultrasonic5_default_cfg ( ultrasonic5_t *ctx );

/**
 * @brief Ultrasonic 5 data writing function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0xXX - Status bits,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_write_register ( ultrasonic5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ultrasonic 5 data reading function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0xXX - Status bits,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_read_register ( ultrasonic5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ultrasonic 5 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_check_communication ( ultrasonic5_t *ctx );

/**
 * @brief Ultrasonic 5 set io1 pin function.
 * @details This function sets the IO1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ultrasonic5_set_io1_pin ( ultrasonic5_t *ctx );

/**
 * @brief Ultrasonic 5 clear io1 pin function.
 * @details This function clears the IO1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ultrasonic5_clear_io1_pin ( ultrasonic5_t *ctx );

/**
 * @brief Ultrasonic 5 get out4 pin function.
 * @details This function returns the OUT4 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ultrasonic5_get_out4_pin ( ultrasonic5_t *ctx );

/**
 * @brief Ultrasonic 5 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_read_an_pin_value ( ultrasonic5_t *ctx, uint16_t *data_out );

/**
 * @brief Ultrasonic 5 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ultrasonic5_read_an_pin_voltage ( ultrasonic5_t *ctx, float *data_out );

/**
 * @brief Ultrasonic 5 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_set_duty_cycle ( ultrasonic5_t *ctx, float duty_cycle );

/**
 * @brief Ultrasonic 5 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_pwm_stop ( ultrasonic5_t *ctx );

/**
 * @brief Ultrasonic 5 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #ultrasonic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic5_pwm_start ( ultrasonic5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ULTRASONIC5_H

/*! @} */ // ultrasonic5

// ------------------------------------------------------------------------ END

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
 * @file haptic3.h
 * @brief This file contains API for HAPTIC 3 Click Driver.
 */

#ifndef HAPTIC3_H
#define HAPTIC3_H

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

/*!
 * @addtogroup haptic3 HAPTIC 3 Click Driver
 * @brief API for configuring and manipulating HAPTIC 3 Click driver.
 * @{
 */

/**
 * @defgroup haptic3_reg HAPTIC 3 Registers List
 * @brief List of registers of HAPTIC 3 Click driver.
 */

/**
 * @addtogroup haptic3_reg
 * @{
 */

/**
 * @brief HAPTIC 3 Register Map.
 * @details Specified Register Map of HAPTIC 3 Click driver.
 */
#define HAPTIC3_REG_CHIP_REV                    0x00
#define HAPTIC3_REG_IRQ_EVENT1                  0x03
#define HAPTIC3_REG_IRQ_EVENT_WARNING_DIAG      0x04
#define HAPTIC3_REG_IRQ_EVENT_SEQ_DIAG          0x05
#define HAPTIC3_REG_IRQ_STATUS1                 0x06
#define HAPTIC3_REG_IRQ_MASK1                   0x07
#define HAPTIC3_REG_CIF_I2C1                    0x08
#define HAPTIC3_REG_FRQ_LRA_PER_H               0x0A
#define HAPTIC3_REG_FRQ_LRA_PER_L               0x0B
#define HAPTIC3_REG_ACTUATOR1                   0x0C
#define HAPTIC3_REG_ACTUATOR2                   0x0D
#define HAPTIC3_REG_ACTUATOR3                   0x0E
#define HAPTIC3_REG_CALIB_V2I_H                 0x0F
#define HAPTIC3_REG_CALIB_V2I_L                 0x10
#define HAPTIC3_REG_CALIB_IMP_H                 0x11
#define HAPTIC3_REG_CALIB_IMP_L                 0x12
#define HAPTIC3_REG_TOP_CFG1                    0x13
#define HAPTIC3_REG_TOP_CFG2                    0x14
#define HAPTIC3_REG_TOP_CFG3                    0x15
#define HAPTIC3_REG_TOP_CFG4                    0x16
#define HAPTIC3_REG_TOP_INT_CFG1                0x17
#define HAPTIC3_REG_TOP_INT_CFG6_H              0x1C
#define HAPTIC3_REG_TOP_INT_CFG6_L              0x1D
#define HAPTIC3_REG_TOP_INT_CFG7_H              0x1E
#define HAPTIC3_REG_TOP_INT_CFG7_L              0x1F
#define HAPTIC3_REG_TOP_INT_CFG8                0x20
#define HAPTIC3_REG_TOP_CTL1                    0x22
#define HAPTIC3_REG_TOP_CTL2                    0x23
#define HAPTIC3_REG_SEQ_CTL1                    0x24
#define HAPTIC3_REG_SWG_C1                      0x25
#define HAPTIC3_REG_SWG_C2                      0x26
#define HAPTIC3_REG_SWG_C3                      0x27
#define HAPTIC3_REG_SEQ_CTL2                    0x28
#define HAPTIC3_REG_GPI_0_CTL                   0x29
#define HAPTIC3_REG_GPI_1_CTL                   0x2A
#define HAPTIC3_REG_GPI_2_CTL                   0x2B
#define HAPTIC3_REG_MEM_CTL1                    0x2C
#define HAPTIC3_REG_MEM_CTL2                    0x2D
#define HAPTIC3_REG_ADC_DATA_H1                 0x2E
#define HAPTIC3_REG_ADC_DATA_L1                 0x2F
#define HAPTIC3_REG_POLARITY                    0x43
#define HAPTIC3_REG_LRA_AVR_H                   0x44
#define HAPTIC3_REG_LRA_AVR_L                   0x45
#define HAPTIC3_REG_FRQ_LRA_PER_ACT_H           0x46
#define HAPTIC3_REG_FRQ_LRA_PER_ACT_L           0x47
#define HAPTIC3_REG_FRQ_PHASE_H                 0x48
#define HAPTIC3_REG_FRQ_PHASE_L                 0x49
#define HAPTIC3_REG_FRQ_CTL                     0x4C
#define HAPTIC3_REG_TRIM3                       0x5F
#define HAPTIC3_REG_TRIM4                       0x60
#define HAPTIC3_REG_TRIM6                       0x62
#define HAPTIC3_REG_TOP_CFG5                    0x6E
#define HAPTIC3_REG_IRQ_EVENT_ACTUATOR_FAULT    0x81
#define HAPTIC3_REG_IRQ_STATUS2                 0x82
#define HAPTIC3_REG_IRQ_MASK2                   0x83
#define HAPTIC3_REG_SNP_MEM_X                   0x84

/*! @} */ // haptic3_reg

/**
 * @defgroup haptic3_set HAPTIC 3 Registers Settings
 * @brief Settings for registers of HAPTIC 3 Click driver.
 */

/**
 * @addtogroup haptic3_set
 * @{
 */

/**
 * @brief HAPTIC 3 chip rev value.
 * @details Specified chip rev value of HAPTIC 3 Click driver.
 */
#define HAPTIC3_CHIP_REV                        0xDA

/**
 * @brief HAPTIC 3 top cfg 1 register settings.
 * @details Specified top cfg 1 register settings of HAPTIC 3 Click driver.
 */
#define HAPTIC3_TOP_CFG1_EMB_MODE_MANUAL        0x00
#define HAPTIC3_TOP_CFG1_EMB_MODE_AUTO          0x80
#define HAPTIC3_TOP_CFG1_EMB_MODE_MASK          0x80
#define HAPTIC3_TOP_CFG1_ACT_TYPE_LRA           0x00
#define HAPTIC3_TOP_CFG1_ACT_TYPE_ERM           0x20
#define HAPTIC3_TOP_CFG1_ACT_TYPE_MASK          0x20
#define HAPTIC3_TOP_CFG1_BEMF_SENSE_CUSTOM_WF   0x00
#define HAPTIC3_TOP_CFG1_BEMF_SENSE_STANDARD    0x10
#define HAPTIC3_TOP_CFG1_BEMF_SENSE_MASK        0x10
#define HAPTIC3_TOP_CFG1_FREQ_TRACK_DISABLE     0x00
#define HAPTIC3_TOP_CFG1_FREQ_TRACK_ENABLE      0x08
#define HAPTIC3_TOP_CFG1_FREQ_TRACK_MASK        0x08
#define HAPTIC3_TOP_CFG1_ACCEL_DISABLE          0x00
#define HAPTIC3_TOP_CFG1_ACCEL_ENABLE           0x04
#define HAPTIC3_TOP_CFG1_ACCEL_MASK             0x04
#define HAPTIC3_TOP_CFG1_RAPID_STOP_DISABLE     0x00
#define HAPTIC3_TOP_CFG1_RAPID_STOP_ENABLE      0x02
#define HAPTIC3_TOP_CFG1_RAPID_STOP_MASK        0x02
#define HAPTIC3_TOP_CFG1_AMPLITUDE_PID_DISABLE  0x00
#define HAPTIC3_TOP_CFG1_AMPLITUDE_PID_ENABLE   0x01
#define HAPTIC3_TOP_CFG1_AMPLITUDE_PID_MASK     0x01

/**
 * @brief HAPTIC 3 top ctl 1 register settings.
 * @details Specified top ctl 1 register settings of HAPTIC 3 Click driver.
 */
#define HAPTIC3_TOP_CTL1_SEQ_STOP               0x00
#define HAPTIC3_TOP_CTL1_SEQ_START              0x10
#define HAPTIC3_TOP_CTL1_SEQ_MASK               0x10
#define HAPTIC3_TOP_CTL1_STANDBY_DISABLE        0x00
#define HAPTIC3_TOP_CTL1_STANDBY_ENABLE         0x08
#define HAPTIC3_TOP_CTL1_STANDBY_MASK           0x08
#define HAPTIC3_TOP_CTL1_OP_MODE_INACTIVE       0x00
#define HAPTIC3_TOP_CTL1_OP_MODE_DRO            0x01
#define HAPTIC3_TOP_CTL1_OP_MODE_PWM            0x02
#define HAPTIC3_TOP_CTL1_OP_MODE_RTWM           0x03
#define HAPTIC3_TOP_CTL1_OP_MODE_ETWM           0x04
#define HAPTIC3_TOP_CTL1_OP_MODE_MASK           0x07

/**
 * @brief HAPTIC 3 calculation macros.
 * @details Specified calculation macros of HAPTIC 3 Click driver.
 */
#define HAPTIC3_ACTUATOR_VOLTAGE_MIN            0.0
#define HAPTIC3_ACTUATOR_VOLTAGE_MAX            6.0
#define HAPTIC3_ACTUATOR_VOLTAGE_RESOLUTION     0.0234
#define HAPTIC3_ACTUATOR_IMAX_MIN               28.6
#define HAPTIC3_ACTUATOR_IMAX_MAX               251.8
#define HAPTIC3_ACTUATOR_IMAX_DIVIDER           7.2
#define HAPTIC3_ACTUATOR_IMAX_RESOLUTION        0x1F
#define HAPTIC3_ACTUATOR_IMPEDANCE_MIN          4.0
#define HAPTIC3_ACTUATOR_IMPEDANCE_MAX          50.0
#define HAPTIC3_ACTUATOR_V2I_FACTOR_DIVIDER     1.6104
#define HAPTIC3_ACTUATOR_LRA_FREQ_MIN           0.0
#define HAPTIC3_ACTUATOR_LRA_FREQ_MAX           300.0
#define HAPTIC3_ACTUATOR_LRA_FREQ_RESOLUTION    0.00000133332
#define HAPTIC3_VIBRATION_LEVEL_MIN             -1.0
#define HAPTIC3_VIBRATION_LEVEL_MAX             1.0
#define HAPTIC3_VIBRATION_LEVEL_MIN_ACC_EN      0.0
#define HAPTIC3_VIBRATION_LEVEL_RESOLUTION      0.008
#define HAPTIC3_ROUND_TO_NEAREST_INT            0.5

/**
 * @brief HAPTIC 3 actuator settings default values.
 * @details Specified actuator settings default values of HAPTIC 3 Click driver.
 */
#define HAPTIC3_DEFAULT_ACTUATOR_TYPE           HAPTIC3_TOP_CFG1_ACT_TYPE_LRA
#define HAPTIC3_DEFAULT_ACTUATOR_ABS_VOLT       2.808
#define HAPTIC3_DEFAULT_ACTUATOR_NOM_VOLT       2.106
#define HAPTIC3_DEFAULT_ACTUATOR_IMAX           194.0
#define HAPTIC3_DEFAULT_ACTUATOR_IMPEDANCE      16.0
#define HAPTIC3_DEFAULT_ACTUATOR_LRA_FREQ       174.0

/**
 * @brief HAPTIC 3 device address setting.
 * @details Specified setting for device slave address selection of
 * HAPTIC 3 Click driver.
 */
#define HAPTIC3_DEVICE_ADDRESS                  0x4A

/*! @} */ // haptic3_set

/**
 * @defgroup haptic3_map HAPTIC 3 MikroBUS Map
 * @brief MikroBUS pin mapping of HAPTIC 3 Click driver.
 */

/**
 * @addtogroup haptic3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HAPTIC 3 Click to the selected MikroBUS.
 */
#define HAPTIC3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // haptic3_map
/*! @} */ // haptic3

/**
 * @brief HAPTIC 3 Click context object.
 * @details Context object definition of HAPTIC 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable device pin (Active High). */

    // Input pins
    digital_in_t  irq;          /**< Interrupt pin (Active Low). */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} haptic3_t;

/**
 * @brief HAPTIC 3 Click configuration object.
 * @details Configuration object definition of HAPTIC 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable device pin (Active Low). */
    pin_name_t irq;             /**< Interrupt pin (Active Low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} haptic3_cfg_t;

/**
 * @brief HAPTIC 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HAPTIC3_OK = 0,
    HAPTIC3_ERROR = -1

} haptic3_return_value_t;

/*!
 * @addtogroup haptic3 HAPTIC 3 Click Driver
 * @brief API for configuring and manipulating HAPTIC 3 Click driver.
 * @{
 */

/**
 * @brief HAPTIC 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #haptic3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void haptic3_cfg_setup ( haptic3_cfg_t *cfg );

/**
 * @brief HAPTIC 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #haptic3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_init ( haptic3_t *ctx, haptic3_cfg_t *cfg );

/**
 * @brief HAPTIC 3 default configuration function.
 * @details This function executes a default configuration of HAPTIC 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t haptic3_default_cfg ( haptic3_t *ctx );

/**
 * @brief HAPTIC 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_generic_write ( haptic3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief HAPTIC 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_generic_read ( haptic3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief HAPTIC 3 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_write_register ( haptic3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief HAPTIC 3 read register function.
 * @details This function reads a desired data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_read_register ( haptic3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief HAPTIC 3 write register bits function.
 * @details This function writes a desired data bits to the bits specified with @b mask of the selected
 * register.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Mask of bits to be changed.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_write_register_bits ( haptic3_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in );

/**
 * @brief HAPTIC 3 check communication function.
 * @details This function checks the communication by reading and verifying the chip ID.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_check_communication ( haptic3_t *ctx );

/**
 * @brief HAPTIC 3 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic3_enable_device ( haptic3_t *ctx );

/**
 * @brief HAPTIC 3 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic3_disable_device ( haptic3_t *ctx );

/**
 * @brief HAPTIC 3 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t haptic3_get_int_pin ( haptic3_t *ctx );

/**
 * @brief HAPTIC 3 set actuator type function.
 * @details This function sets the actuator type bits in TOP CFG1 register.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] type : @li @c 0x00 - LRA,
 *                   @li @c 0x20 - ERM.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_actuator_type ( haptic3_t *ctx, uint8_t type );

/**
 * @brief HAPTIC 3 set actuator abs volt function.
 * @details This function sets the actuator absolute maximum voltage.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] abs_volt : Voltage in range of 0.0 to 6.0 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_actuator_abs_volt ( haptic3_t *ctx, float abs_volt );

/**
 * @brief HAPTIC 3 set actuator nom volt function.
 * @details This function sets the actuator nominal voltage.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] nom_volt : Voltage in range of 0.0 to 6.0 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_actuator_nom_volt ( haptic3_t *ctx, float nom_volt );

/**
 * @brief HAPTIC 3 set actuator imax function.
 * @details This function sets the actuator max current rating.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] max_curr : Current in range of 28.6 to 251.8 mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_actuator_imax ( haptic3_t *ctx, float max_curr );

/**
 * @brief HAPTIC 3 set actuator impedance function.
 * @details This function sets the actuator impedance.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] impedance : Impedance in range of 4.0 to 50.0 Ohm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The value is dependent on the max current value that can be set using 
 * @b haptic3_set_actuator_imax function.
 */
err_t haptic3_set_actuator_impedance ( haptic3_t *ctx, float impedance );

/**
 * @brief HAPTIC 3 set actuator lra freq function.
 * @details This function sets the actuator LRA frequency.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] frequency : Frequency in range of 0.0 to 300.0 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_actuator_lra_freq ( haptic3_t *ctx, float frequency );

/**
 * @brief HAPTIC 3 set operation mode function.
 * @details This function sets the operation mode bits in TOP CTL1 register.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] op_mode : @li @c 0x00 - Inactive,
 *                      @li @c 0x01 - DRO (I2C Control),
 *                      @li @c 0x02 - PWM,
 *                      @li @c 0x03 - RTWM (Register-Triggered-Waveform-Memory),
 *                      @li @c 0x04 - ETWM (Edge-Triggered-Waveform-Memory Mode).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_operation_mode ( haptic3_t *ctx, uint8_t op_mode );

/**
 * @brief HAPTIC 3 set freq track function.
 * @details This function sets the frequency tracking bits in TOP CFG1 register.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] freq_track_en : @li @c 0x00 - Disable,
 *                            @li @c 0x08 - Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_freq_track ( haptic3_t *ctx, uint8_t freq_track_en );

/**
 * @brief HAPTIC 3 set acceleration mode function.
 * @details This function sets the acceleration mode bits in TOP CFG1 register.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] accel_en : @li @c 0x00 - Disable,
 *                       @li @c 0x04 - Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_acceleration_mode ( haptic3_t *ctx, uint8_t accel_en );

/**
 * @brief HAPTIC 3 set vibration level function.
 * @details This function sets the motor vibration level.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[in] level : Vibration level in percentage from 0.0 
 *                    (or -1.0 if acceleration mode is disabled) to 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_set_vibration_level ( haptic3_t *ctx, float level );

/**
 * @brief HAPTIC 3 get vibration level function.
 * @details This function reads the motor vibration level.
 * @param[in] ctx : Click context object.
 * See #haptic3_t object definition for detailed explanation.
 * @param[out] level : Vibration level in percentage from 0.0 
 *                    (or -1.0 if acceleration mode is disabled) to 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic3_get_vibration_level ( haptic3_t *ctx, float *level );

#ifdef __cplusplus
}
#endif
#endif // HAPTIC3_H

/*! @} */ // haptic3

// ------------------------------------------------------------------------ END

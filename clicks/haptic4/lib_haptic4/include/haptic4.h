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
 * @file haptic4.h
 * @brief This file contains API for Haptic 4 Click Driver.
 */

#ifndef HAPTIC4_H
#define HAPTIC4_H

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
 * @addtogroup haptic4 Haptic 4 Click Driver
 * @brief API for configuring and manipulating Haptic 4 Click driver.
 * @{
 */

/**
 * @defgroup haptic4_reg Haptic 4 Registers List
 * @brief List of registers of Haptic 4 Click driver.
 */

/**
 * @addtogroup haptic4_reg
 * @{
 */

/**
 * @brief Haptic 4 description register.
 * @details Specified register for description of Haptic 4 Click driver.
 */
#define HAPTIC4_REG_CHIP_REV                    0x00
#define HAPTIC4_REG_IRQ_EVENT1                  0x03
#define HAPTIC4_REG_IRQ_EVENT_WARNING_DIAG      0x04
#define HAPTIC4_REG_IRQ_EVENT_SEQ_DIAG          0x05
#define HAPTIC4_REG_IRQ_STATUS1                 0x06
#define HAPTIC4_REG_IRQ_MASK1                   0x07
#define HAPTIC4_REG_CIF_I2C1                    0x08
#define HAPTIC4_REG_FRQ_LRA_PER_H               0x0A
#define HAPTIC4_REG_FRQ_LRA_PER_L               0x0B
#define HAPTIC4_REG_ACTUATOR1                   0x0C
#define HAPTIC4_REG_ACTUATOR2                   0x0D
#define HAPTIC4_REG_ACTUATOR3                   0x0E
#define HAPTIC4_REG_CALIB_V2I_H                 0x0F
#define HAPTIC4_REG_CALIB_V2I_L                 0x10
#define HAPTIC4_REG_CALIB_IMP_H                 0x11
#define HAPTIC4_REG_CALIB_IMP_L                 0x12
#define HAPTIC4_REG_TOP_CFG1                    0x13
#define HAPTIC4_REG_TOP_CFG2                    0x14
#define HAPTIC4_REG_TOP_CFG3                    0x15
#define HAPTIC4_REG_TOP_CFG4                    0x16
#define HAPTIC4_REG_TOP_INT_CFG1                0x17
#define HAPTIC4_REG_TOP_INT_CFG6_H              0x1C
#define HAPTIC4_REG_TOP_INT_CFG6_L              0x1D
#define HAPTIC4_REG_TOP_INT_CFG7_H              0x1E
#define HAPTIC4_REG_TOP_INT_CFG7_L              0x1F
#define HAPTIC4_REG_TOP_INT_CFG8                0x20
#define HAPTIC4_REG_TOP_CTL1                    0x22
#define HAPTIC4_REG_TOP_CTL2                    0x23
#define HAPTIC4_REG_SEQ_CTL1                    0x24
#define HAPTIC4_REG_SWG_C1                      0x25
#define HAPTIC4_REG_SWG_C2                      0x26
#define HAPTIC4_REG_SWG_C3                      0x27
#define HAPTIC4_REG_SEQ_CTL2                    0x28
#define HAPTIC4_REG_GPI_0_CTL                   0x29
#define HAPTIC4_REG_GPI_1_CTL                   0x2A
#define HAPTIC4_REG_GPI_2_CTL                   0x2B
#define HAPTIC4_REG_MEM_CTL1                    0x2C
#define HAPTIC4_REG_MEM_CTL2                    0x2D
#define HAPTIC4_REG_ADC_DATA_H1                 0x2E
#define HAPTIC4_REG_ADC_DATA_L1                 0x2F
#define HAPTIC4_REG_POLARITY                    0x43
#define HAPTIC4_REG_LRA_AVR_H                   0x44
#define HAPTIC4_REG_LRA_AVR_L                   0x45
#define HAPTIC4_REG_FRQ_LRA_PER_ACT_H           0x46
#define HAPTIC4_REG_FRQ_LRA_PER_ACT_L           0x47
#define HAPTIC4_REG_FRQ_PHASE_H                 0x48
#define HAPTIC4_REG_FRQ_PHASE_L                 0x49
#define HAPTIC4_REG_FRQ_CTL                     0x4C
#define HAPTIC4_REG_TRIM3                       0x5F
#define HAPTIC4_REG_TRIM4                       0x60
#define HAPTIC4_REG_TRIM6                       0x62
#define HAPTIC4_REG_TOP_CFG5                    0x6E
#define HAPTIC4_REG_IRQ_EVENT_ACTUATOR_FAULT    0x81
#define HAPTIC4_REG_IRQ_STATUS2                 0x82
#define HAPTIC4_REG_IRQ_MASK2                   0x83
#define HAPTIC4_REG_SNP_MEM_X                   0x84

/*! @} */ // haptic4_reg

/**
 * @defgroup haptic4_set Haptic 4 Registers Settings
 * @brief Settings for registers of Haptic 4 Click driver.
 */

/**
 * @addtogroup haptic4_set
 * @{
 */

/**
 * @brief Haptic 4 CHIP REV value.
 * @details Specified CHIP REV value of Haptic 4 Click driver.
 */
#define HAPTIC4_CHIP_REV                        0xBA

/**
 * @brief Haptic 4 pin state.
 * @details Specified pin state of Haptic 4 Click driver.
 */
#define HAPTIC4_PIN_STATE_LOW                   0x00
#define HAPTIC4_PIN_STATE_HIGH                  0x01

/**
 * @brief Haptic 4 top CFG 1 register settings.
 * @details Specified top CFG 1 register settings of Haptic 4 Click driver.
 */
#define HAPTIC4_TOP_CFG1_EMB_MODE_MANUAL        0x00
#define HAPTIC4_TOP_CFG1_EMB_MODE_AUTO          0x80
#define HAPTIC4_TOP_CFG1_EMB_MODE_MASK          0x80
#define HAPTIC4_TOP_CFG1_ACT_TYPE_LRA           0x00
#define HAPTIC4_TOP_CFG1_ACT_TYPE_ERM           0x20
#define HAPTIC4_TOP_CFG1_ACT_TYPE_MASK          0x20
#define HAPTIC4_TOP_CFG1_BEMF_SENSE_CUSTOM_WF   0x00
#define HAPTIC4_TOP_CFG1_BEMF_SENSE_STANDARD    0x10
#define HAPTIC4_TOP_CFG1_BEMF_SENSE_MASK        0x10
#define HAPTIC4_TOP_CFG1_FREQ_TRACK_DISABLE     0x00
#define HAPTIC4_TOP_CFG1_FREQ_TRACK_ENABLE      0x08
#define HAPTIC4_TOP_CFG1_FREQ_TRACK_MASK        0x08
#define HAPTIC4_TOP_CFG1_ACCEL_DISABLE          0x00
#define HAPTIC4_TOP_CFG1_ACCEL_ENABLE           0x04
#define HAPTIC4_TOP_CFG1_ACCEL_MASK             0x04
#define HAPTIC4_TOP_CFG1_RAPID_STOP_DISABLE     0x00
#define HAPTIC4_TOP_CFG1_RAPID_STOP_ENABLE      0x02
#define HAPTIC4_TOP_CFG1_RAPID_STOP_MASK        0x02
#define HAPTIC4_TOP_CFG1_AMPLITUDE_PID_DISABLE  0x00
#define HAPTIC4_TOP_CFG1_AMPLITUDE_PID_ENABLE   0x01
#define HAPTIC4_TOP_CFG1_AMPLITUDE_PID_MASK     0x01

/**
 * @brief Haptic 4 top CTL 1 register settings.
 * @details Specified top CTL 1 register settings of Haptic 4 Click driver.
 */
#define HAPTIC4_TOP_CTL1_SEQ_STOP               0x00
#define HAPTIC4_TOP_CTL1_SEQ_START              0x10
#define HAPTIC4_TOP_CTL1_SEQ_MASK               0x10
#define HAPTIC4_TOP_CTL1_STANDBY_DISABLE        0x00
#define HAPTIC4_TOP_CTL1_STANDBY_ENABLE         0x08
#define HAPTIC4_TOP_CTL1_STANDBY_MASK           0x08
#define HAPTIC4_TOP_CTL1_OP_MODE_INACTIVE       0x00
#define HAPTIC4_TOP_CTL1_OP_MODE_DRO            0x01
#define HAPTIC4_TOP_CTL1_OP_MODE_PWM            0x02
#define HAPTIC4_TOP_CTL1_OP_MODE_RTWM           0x03
#define HAPTIC4_TOP_CTL1_OP_MODE_ETWM           0x04
#define HAPTIC4_TOP_CTL1_OP_MODE_MASK           0x07

/**
 * @brief Haptic 4 calculation macros.
 * @details Specified calculation macros of Haptic 4 Click driver.
 */
#define HAPTIC4_ACTUATOR_VOLTAGE_MIN            0.0f
#define HAPTIC4_ACTUATOR_VOLTAGE_MAX            6.0f
#define HAPTIC4_ACTUATOR_VOLTAGE_RESOLUTION     0.0234f
#define HAPTIC4_ACTUATOR_IMAX_MIN               28.6f
#define HAPTIC4_ACTUATOR_IMAX_MAX               251.8f
#define HAPTIC4_ACTUATOR_IMAX_DIVIDER           7.2f
#define HAPTIC4_ACTUATOR_IMAX_RESOLUTION        0x1F
#define HAPTIC4_ACTUATOR_IMPEDANCE_MIN          4.0f
#define HAPTIC4_ACTUATOR_IMPEDANCE_MAX          50.0f
#define HAPTIC4_ACTUATOR_V2I_FACTOR_DIVIDER     1.6104f
#define HAPTIC4_ACTUATOR_LRA_FREQ_MIN           0.0f
#define HAPTIC4_ACTUATOR_LRA_FREQ_MAX           300.0f
#define HAPTIC4_ACTUATOR_LRA_FREQ_RESOLUTION    0.00000133332f
#define HAPTIC4_VIBRATION_LEVEL_MIN             -1.0f
#define HAPTIC4_VIBRATION_LEVEL_MAX             1.0f
#define HAPTIC4_VIBRATION_LEVEL_MIN_ACC_EN      0.0f
#define HAPTIC4_VIBRATION_LEVEL_RESOLUTION      0.008f
#define HAPTIC4_ROUND_TO_NEAREST_INT            0.5f

/**
 * @brief Haptic 4 actuator settings default values.
 * @details Specified actuator settings default values of Haptic 4 Click driver.
 */
#define HAPTIC4_DEFAULT_ACTUATOR_TYPE           HAPTIC4_TOP_CFG1_ACT_TYPE_LRA
#define HAPTIC4_DEFAULT_ACTUATOR_ABS_VOLT       2.808f
#define HAPTIC4_DEFAULT_ACTUATOR_NOM_VOLT       2.106f
#define HAPTIC4_DEFAULT_ACTUATOR_IMAX           194.0f
#define HAPTIC4_DEFAULT_ACTUATOR_IMPEDANCE      16.0f
#define HAPTIC4_DEFAULT_ACTUATOR_LRA_FREQ       174.0f

/**
 * @brief Haptic 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Haptic 4 Click driver.
 */
#define HAPTIC4_DEVICE_ADDRESS                  0x4A

/*! @} */ // haptic4_set

/**
 * @defgroup haptic4_map Haptic 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Haptic 4 Click driver.
 */

/**
 * @addtogroup haptic4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Haptic 4 Click to the selected MikroBUS.
 */
#define HAPTIC4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // haptic4_map
/*! @} */ // haptic4

/**
 * @brief Haptic 4 Click context object.
 * @details Context object definition of Haptic 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t gp1;          /**< GPI sequence trigger 1. */
    digital_out_t gp2;          /**< GPI sequence trigger 2. */
    digital_out_t gp0;          /**< GPI sequence trigger 0. */

    // Input pins
    digital_in_t irq;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} haptic4_t;

/**
 * @brief Haptic 4 Click configuration object.
 * @details Configuration object definition of Haptic 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t gp1;             /**< GPI sequence trigger 1. */
    pin_name_t gp2;             /**< GPI sequence trigger 2. */
    pin_name_t gp0;             /**< GPI sequence trigger 0. */
    pin_name_t irq;             /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} haptic4_cfg_t;

/**
 * @brief Haptic 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HAPTIC4_OK = 0,
    HAPTIC4_ERROR = -1

} haptic4_return_value_t;

/*!
 * @addtogroup haptic4 Haptic 4 Click Driver
 * @brief API for configuring and manipulating Haptic 4 Click driver.
 * @{
 */

/**
 * @brief Haptic 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #haptic4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void haptic4_cfg_setup ( haptic4_cfg_t *cfg );

/**
 * @brief Haptic 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #haptic4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_init ( haptic4_t *ctx, haptic4_cfg_t *cfg );

/**
 * @brief Haptic 4 default configuration function.
 * @details This function executes a default configuration of Haptic 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t haptic4_default_cfg ( haptic4_t *ctx );

/**
 * @brief Haptic 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_generic_write ( haptic4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Haptic 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_generic_read ( haptic4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );


/**
 * @brief Haptic 4 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_write_register ( haptic4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Haptic 4 read register function.
 * @details This function reads a desired data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_read_register ( haptic4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Haptic 4 write register bits function.
 * @details This function writes a desired data bits to the bits specified with @b mask of the selected
 * register.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Mask of bits to be changed.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_write_register_bits ( haptic4_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in );

/**
 * @brief Haptic 4 check communication function.
 * @details This function checks the communication by reading and verifying the chip ID.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_check_communication ( haptic4_t *ctx );

/**
 * @brief Haptic 4 set GP0 pin state function.
 * @details This function is used to set GP0 pin state.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void haptic4_set_gp0 ( haptic4_t *ctx, uint8_t pin_state );

/**
 * @brief Haptic 4 set GP1 pin state function.
 * @details This function is used to set GP1 pin state.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void haptic4_set_gp1 ( haptic4_t *ctx, uint8_t pin_state );

/**
 * @brief Haptic 4 set GP2 pin state function.
 * @details This function is used to set GP2 pin state.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void haptic4_set_gp2 ( haptic4_t *ctx, uint8_t pin_state );

/**
 * @brief Haptic 4 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t haptic4_get_int_pin ( haptic4_t *ctx );

/**
 * @brief Haptic 4 set actuator type function.
 * @details This function sets the actuator type bits in TOP CFG1 register.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] type : Selected actuator type.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_actuator_type ( haptic4_t *ctx, uint8_t type );

/**
 * @brief Haptic 4 set actuator abs volt function.
 * @details This function sets the actuator absolute maximum voltage.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] abs_volt : Voltage in range of 0.0 to 6.0 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_actuator_abs_volt ( haptic4_t *ctx, float abs_volt );

/**
 * @brief Haptic 4 set actuator nom volt function.
 * @details This function sets the actuator nominal voltage.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] nom_volt : Voltage in range of 0.0 to 6.0 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_actuator_nom_volt ( haptic4_t *ctx, float nom_volt );

/**
 * @brief Haptic 4 set actuator imax function.
 * @details This function sets the actuator max current rating.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] max_curr : Current in range of 28.6 to 251.8 mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_actuator_imax ( haptic4_t *ctx, float max_curr );

/**
 * @brief Haptic 4 set actuator impedance function.
 * @details This function sets the actuator impedance.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] impedance : Impedance in range of 4.0 to 50.0 Ohm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The value is dependent on the max current value that can be set using 
 * @b haptic4_set_actuator_imax function.
 */
err_t haptic4_set_actuator_impedance ( haptic4_t *ctx, float impedance );

/**
 * @brief Haptic 4 set actuator lra freq function.
 * @details This function sets the actuator LRA frequency.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] frequency : Frequency in range of 0.0 to 300.0 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_actuator_lra_freq ( haptic4_t *ctx, float frequency );

/**
 * @brief Haptic 4 set operation mode function.
 * @details This function sets the operation mode bits in TOP CTL1 register.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] op_mode : Selected operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_operation_mode ( haptic4_t *ctx, uint8_t op_mode );

/**
 * @brief Haptic 4 set freq track function.
 * @details This function sets the frequency tracking bits in TOP CFG1 register.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] freq_track_en : Selected frequency tracking mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_freq_track ( haptic4_t *ctx, uint8_t freq_track_en );

/**
 * @brief Haptic 4 set accel mode function.
 * @details This function sets the accel mode bits in TOP CFG1 register.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] accel_en : Selected accel mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_acceleration_mode ( haptic4_t *ctx, uint8_t accel_en );

/**
 * @brief Haptic 4 set vibration level function.
 * @details This function sets the motor vibration level.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[in] level : Vibration level in percentage from 0.0 
 *                    (or -1.0 if accel mode is disabled) to 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_set_vibration_level ( haptic4_t *ctx, float level );

/**
 * @brief Haptic 4 get vibration level function.
 * @details This function reads the motor vibration level.
 * @param[in] ctx : Click context object.
 * See #haptic4_t object definition for detailed explanation.
 * @param[out] level : Vibration level in percentage from 0.0 
 *                    (or -1.0 if acceleration mode is disabled) to 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic4_get_vibration_level ( haptic4_t *ctx, float *level );

#ifdef __cplusplus
}
#endif
#endif // HAPTIC4_H

/*! @} */ // haptic4

// ------------------------------------------------------------------------ END

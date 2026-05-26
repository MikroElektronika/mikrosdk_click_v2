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
 * @file dcmotor32.h
 * @brief This file contains API for DC Motor 32 Click Driver.
 */

#ifndef DCMOTOR32_H
#define DCMOTOR32_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup dcmotor32 DC Motor 32 Click Driver
 * @brief API for configuring and manipulating DC Motor 32 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor32_set DC Motor 32 Settings
 * @brief Settings of DC Motor 32 Click driver.
 */

/**
 * @addtogroup dcmotor32_set
 * @{
 */

/**
 * @brief DC Motor 32 control byte setting.
 * @details Specified setting for control byte of DC Motor 32 Click driver.
 */
#define DCMOTOR32_CONTROL_SDO_SEL_CONTROL               0x00
#define DCMOTOR32_CONTROL_SDO_SEL_STATUS                0x80
#define DCMOTOR32_CONTROL_SDO_SEL_MASK                  0x80
#define DCMOTOR32_CONTROL_MODE_PD_GND_OUT               0x00
#define DCMOTOR32_CONTROL_MODE_PU_SHORT_TO_GND          0x08
#define DCMOTOR32_CONTROL_MODE_SLOW_DECAY_LSB           0x10
#define DCMOTOR32_CONTROL_MODE_SLOW_DECAY_LSA           0x18
#define DCMOTOR32_CONTROL_MODE_FAST_DECAY_HSB           0x20
#define DCMOTOR32_CONTROL_MODE_FAST_DECAY_HSB_OPEN_LOAD 0x28
#define DCMOTOR32_CONTROL_MODE_FORWARD_HSB              0x30
#define DCMOTOR32_CONTROL_MODE_FORWARD_LSA              0x38
#define DCMOTOR32_CONTROL_MODE_FAST_DECAY_HSA_OPEN_LOAD 0x40
#define DCMOTOR32_CONTROL_MODE_FAST_DECAY_HSA           0x48
#define DCMOTOR32_CONTROL_MODE_REVERSE_LSB              0x50
#define DCMOTOR32_CONTROL_MODE_REVERSE_HSA              0x58
#define DCMOTOR32_CONTROL_MODE_SLOW_DECAY_HSB           0x60
#define DCMOTOR32_CONTROL_MODE_SLOW_DECAY_HSA           0x68
#define DCMOTOR32_CONTROL_MODE_HALF_BRIDGE_A_TRI_STATE  0x70
#define DCMOTOR32_CONTROL_MODE_HALF_BRIDGE_B_TRI_STATE  0x78
#define DCMOTOR32_CONTROL_MODE_MASK                     0x78
#define DCMOTOR32_CONTROL_CURRENT_SENSE_DISABLE         0x00
#define DCMOTOR32_CONTROL_CURRENT_SENSE_ENABLE          0x04
#define DCMOTOR32_CONTROL_CURRENT_SENSE_MASK            0x04
#define DCMOTOR32_CONTROL_SLEW_RATE_SLOW                0x00
#define DCMOTOR32_CONTROL_SLEW_RATE_FAST                0x02
#define DCMOTOR32_CONTROL_SLEW_RATE_MASK                0x02
#define DCMOTOR32_CONTROL_EN_DISABLE                    0x00
#define DCMOTOR32_CONTROL_EN_ENABLE                     0x01
#define DCMOTOR32_CONTROL_EN_MASK                       0x01

/**
 * @brief DC Motor 32 status byte setting.
 * @details Specified setting for status byte of DC Motor 32 Click driver.
 */
#define DCMOTOR32_STATUS_SDO_SEL_CONTROL                0x00
#define DCMOTOR32_STATUS_SDO_SEL_STATUS                 0x80
#define DCMOTOR32_STATUS_SDO_SEL_MASK                   0x80
#define DCMOTOR32_STATUS_OCA_MASK                       0x40
#define DCMOTOR32_STATUS_OCB_MASK                       0x20
#define DCMOTOR32_STATUS_OL_MASK                        0x10
#define DCMOTOR32_STATUS_UV_MASK                        0x08
#define DCMOTOR32_STATUS_TSDA_MASK                      0x04
#define DCMOTOR32_STATUS_TSDB_MASK                      0x02
#define DCMOTOR32_STATUS_EN_MASK                        0x01

/**
 * @brief DC Motor 32 current calculation setting.
 * @details Specified setting for current calculation of DC Motor 32 Click driver.
 */
#define DCMOTOR32_R8                                    1000.0
#define DCMOTOR32_R9                                    820.0

/**
 * @brief DC Motor 32 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of DC Motor 32 Click driver.
 */
#define DCMOTOR32_NUM_CONVERSIONS                       200

/**
 * @brief DC Motor 32 ADC setting.
 * @details Specified settings for ADC of DC Motor 32 Click driver.
 */
#define DCMOTOR32_VREF_3V3                              3.3
#define DCMOTOR32_VREF_5V                               5.0
#define DCMOTOR32_VREF_DEFAULT                          DCMOTOR32_VREF_3V3

/**
 * @brief DC Motor 32 timeout setting.
 * @details Specified setting for timeout of DC Motor 32 Click driver.
 */
#define DCMOTOR32_TIMEOUT_MS                            2000

/*! @} */ // dcmotor32_set

/**
 * @defgroup dcmotor32_map DC Motor 32 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 32 Click driver.
 */

/**
 * @addtogroup dcmotor32_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 32 Click to the selected MikroBUS.
 */
#define DCMOTOR32_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.is_pin = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // dcmotor32_map
/*! @} */ // dcmotor32

/**
 * @brief DC Motor 32 Click context object.
 * @details Context object definition of DC Motor 32 Click driver.
 */
typedef struct
{
    digital_out_t mosi;             /**< Master output - slave input pin descriptor for SPI driver. */
    digital_out_t sck;              /**< Clock pin descriptor for SPI driver. */
    digital_out_t cs;               /**< Chip select pin descriptor for SPI driver. */
    digital_in_t miso;              /**< Master input - slave output pin descriptor for SPI driver. */
    analog_in_t adc;                /**< ADC module object. */

    uint8_t control;                /**< Control byte. */
    uint8_t status;                 /**< Status byte. */
    float zero_curr_offset;         /**< Voltage offset for zero current (tri-state mode). */

} dcmotor32_t;

/**
 * @brief DC Motor 32 Click configuration object.
 * @details Configuration object definition of DC Motor 32 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t is_pin;              /**< Current monitoring ADC pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} dcmotor32_cfg_t;

/**
 * @brief DC Motor 32 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR32_OK = 0,
    DCMOTOR32_ERROR = -1

} dcmotor32_return_value_t;

/*!
 * @addtogroup dcmotor32 DC Motor 32 Click Driver
 * @brief API for configuring and manipulating DC Motor 32 Click driver.
 * @{
 */

/**
 * @brief DC Motor 32 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor32_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor32_cfg_setup ( dcmotor32_cfg_t *cfg );

/**
 * @brief DC Motor 32 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor32_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_init ( dcmotor32_t *ctx, dcmotor32_cfg_t *cfg );

/**
 * @brief DC Motor 32 default configuration function.
 * @details This function executes a default configuration of DC Motor 32
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor32_default_cfg ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 set control function.
 * @details This function writes the control value and checks the returned control byte.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[in] control : Control register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The SDO select field is set to control mode before writing.
 */
err_t dcmotor32_set_control ( dcmotor32_t *ctx, uint8_t control );

/**
 * @brief DC Motor 32 get status function.
 * @details This function reads the device status byte using SPI communication.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The SDO select field is set to status mode before reading.
 */
err_t dcmotor32_get_status ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 set operation mode function.
 * @details This function sets the selected device operation mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[in] mode : Operation mode value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_set_operation_mode ( dcmotor32_t *ctx, uint8_t mode );

/**
 * @brief DC Motor 32 enable current sense function.
 * @details This function enables the current sense function.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_enable_isense ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 disable current sense function.
 * @details This function disables the current sense function.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_disable_isense ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 set fast slew rate function.
 * @details This function sets the output slew rate to fast mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_set_fast_slew_rate ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 set slow slew rate function.
 * @details This function sets the output slew rate to slow mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_set_slow_slew_rate ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 enable device function.
 * @details This function enables the device.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_enable_device ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 disable device function.
 * @details This function disables the device.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_disable_device ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 read raw IS ADC value function.
 * @details This function reads results of AD conversion of the IS pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_read_adc_raw ( dcmotor32_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 32 read IS pin voltage level function.
 * @details This function reads results of AD conversion of the IS pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor32_read_adc_volt ( dcmotor32_t *ctx, float *data_out );

/**
 * @brief DC Motor 32 read IS pin voltage level average function.
 * @details This function a desired number of IS pin ADC voltage samples and averages it.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] volt_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor32_read_adc_volt_avg ( dcmotor32_t *ctx, uint16_t num_conv, float *volt_avg );

/**
 * @brief DC Motor 32 set vref function.
 * @details This function sets the ADC voltage reference for DC Motor 32 Click driver.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b dcmotor32_init is 3.3V.
 */
err_t dcmotor32_set_adc_vref ( dcmotor32_t *ctx, float vref );

/**
 * @brief DC Motor 32 calibrate offset function.
 * @details This function measures and stores the zero current offset voltage.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor32_calib_offset ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 get output current function.
 * @details This function calculates the output current from the measured ADC voltage.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[out] current : Pointer to the memory location where the output current will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The current is calculated using the stored zero current offset value.
 */
err_t dcmotor32_get_out_current ( dcmotor32_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR32_H

/*! @} */ // dcmotor32

// ------------------------------------------------------------------------ END

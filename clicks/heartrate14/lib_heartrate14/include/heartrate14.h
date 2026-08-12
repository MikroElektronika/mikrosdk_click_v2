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
 * @file heartrate14.h
 * @brief This file contains API for Heart Rate 14 Click Driver.
 */

#ifndef HEARTRATE14_H
#define HEARTRATE14_H

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
 * @addtogroup heartrate14 Heart Rate 14 Click Driver
 * @brief API for configuring and manipulating Heart Rate 14 Click driver.
 * @{
 */

/**
 * @defgroup heartrate14_reg Heart Rate 14 Registers List
 * @brief List of registers of Heart Rate 14 Click driver.
 */

/**
 * @addtogroup heartrate14_reg
 * @{
 */

/**
 * @brief Heart Rate 14 register list.
 * @details Specified register list of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_REG_INT_STATUS1             0x00
#define HEARTRATE14_REG_INT_STATUS2             0x01
#define HEARTRATE14_REG_INT_ENABLE1             0x02
#define HEARTRATE14_REG_INT_ENABLE2             0x03
#define HEARTRATE14_REG_FIFO_WR_PTR             0x04
#define HEARTRATE14_REG_FIFO_RD_PTR             0x05
#define HEARTRATE14_REG_OVF_COUNTER             0x06
#define HEARTRATE14_REG_FIFO_DATA_CNT           0x07
#define HEARTRATE14_REG_FIFO_DATA               0x08
#define HEARTRATE14_REG_FIFO_CFG1               0x09
#define HEARTRATE14_REG_FIFO_CFG2               0x0A
#define HEARTRATE14_REG_SYS_CTRL                0x0D
#define HEARTRATE14_REG_PPG_SYNC_CTRL           0x10
#define HEARTRATE14_REG_PPG_CFG1                0x11
#define HEARTRATE14_REG_PPG_CFG2                0x12
#define HEARTRATE14_REG_PPG_CFG3                0x13
#define HEARTRATE14_REG_PROX_INT_THRESH         0x14
#define HEARTRATE14_REG_PD_BIAS                 0x15
#define HEARTRATE14_REG_PICKET_FENCE            0x16
#define HEARTRATE14_REG_LED_SEQ1                0x20
#define HEARTRATE14_REG_LED_SEQ2                0x21
#define HEARTRATE14_REG_LED_SEQ3                0x22
#define HEARTRATE14_REG_LED1_PA                 0x23
#define HEARTRATE14_REG_LED2_PA                 0x24
#define HEARTRATE14_REG_LED3_PA                 0x25
#define HEARTRATE14_REG_LED_PILOT_PA            0x29
#define HEARTRATE14_REG_LED_RANGE               0x2A
#define HEARTRATE14_REG_TEMP_CFG                0x40
#define HEARTRATE14_REG_TEMP_INT                0x41
#define HEARTRATE14_REG_TEMP_FRAC               0x42
#define HEARTRATE14_REG_DAC_CAL_EN              0x50
#define HEARTRATE14_REG_PART_ID                 0xFF

/*! @} */ // heartrate14_reg

/**
 * @defgroup heartrate14_set Heart Rate 14 Registers Settings
 * @brief Settings for registers of Heart Rate 14 Click driver.
 */

/**
 * @addtogroup heartrate14_set
 * @{
 */

/**
 * @brief Heart Rate 14 interrupt status 1 register setting.
 * @details Specified setting for interrupt status 1 register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_INT1_A_FULL                 0x80
#define HEARTRATE14_INT1_DATA_RDY               0x40
#define HEARTRATE14_INT1_ALC_OVF                0x20
#define HEARTRATE14_INT1_PROX_INT               0x10
#define HEARTRATE14_INT1_LED_COMPB              0x08
#define HEARTRATE14_INT1_DIE_TEMP_RDY           0x04
#define HEARTRATE14_INT1_PWR_RDY                0x01

/**
 * @brief Heart Rate 14 system control register setting.
 * @details Specified setting for system control register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_SYS_CTRL_SINGLE_PPG         0x08
#define HEARTRATE14_SYS_CTRL_LP_MODE            0x04
#define HEARTRATE14_SYS_CTRL_SHDN               0x02
#define HEARTRATE14_SYS_CTRL_RESET              0x01

/**
 * @brief Heart Rate 14 PPG configuration 1 register setting.
 * @details Specified setting for PPG configuration 1 register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_PPG_CFG1_ALC_DISABLE        0x80
#define HEARTRATE14_PPG_CFG1_ADD_OFFSET         0x40
#define HEARTRATE14_PPG_CFG1_ADC_RGE_MASK       0x0C
#define HEARTRATE14_PPG_CFG1_ADC_RGE_4UA        0x00
#define HEARTRATE14_PPG_CFG1_ADC_RGE_8UA        0x04
#define HEARTRATE14_PPG_CFG1_ADC_RGE_16UA       0x08
#define HEARTRATE14_PPG_CFG1_ADC_RGE_32UA       0x0C
#define HEARTRATE14_PPG_CFG1_TINT_MASK          0x03
#define HEARTRATE14_PPG_CFG1_TINT_14P8US        0x00
#define HEARTRATE14_PPG_CFG1_TINT_29P4US        0x01
#define HEARTRATE14_PPG_CFG1_TINT_58P7US        0x02
#define HEARTRATE14_PPG_CFG1_TINT_117P3US       0x03

/**
 * @brief Heart Rate 14 PPG configuration 2 register setting.
 * @details Specified setting for PPG configuration 2 register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_PPG_CFG2_SR_MASK            0xF8
#define HEARTRATE14_PPG_CFG2_SR_25SPS           0x00
#define HEARTRATE14_PPG_CFG2_SR_50SPS           0x08
#define HEARTRATE14_PPG_CFG2_SR_84SPS           0x10
#define HEARTRATE14_PPG_CFG2_SR_100SPS          0x18
#define HEARTRATE14_PPG_CFG2_SR_200SPS          0x20
#define HEARTRATE14_PPG_CFG2_SR_400SPS          0x28
#define HEARTRATE14_PPG_CFG2_SR_8SPS            0x50
#define HEARTRATE14_PPG_CFG2_SR_32SPS           0x60
#define HEARTRATE14_PPG_CFG2_SR_128SPS          0x70
#define HEARTRATE14_PPG_CFG2_SR_256SPS          0x78
#define HEARTRATE14_PPG_CFG2_SMP_AVE_MASK       0x07
#define HEARTRATE14_PPG_CFG2_SMP_AVE_1          0x00
#define HEARTRATE14_PPG_CFG2_SMP_AVE_2          0x01
#define HEARTRATE14_PPG_CFG2_SMP_AVE_4          0x02
#define HEARTRATE14_PPG_CFG2_SMP_AVE_8          0x03
#define HEARTRATE14_PPG_CFG2_SMP_AVE_16         0x04
#define HEARTRATE14_PPG_CFG2_SMP_AVE_32         0x05

/**
 * @brief Heart Rate 14 PPG configuration 3 register setting.
 * @details Specified setting for PPG configuration 3 register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_PPG_CFG3_LED_SETLNG_MASK    0xC0
#define HEARTRATE14_PPG_CFG3_LED_SETLNG_4US     0x00
#define HEARTRATE14_PPG_CFG3_LED_SETLNG_6US     0x40
#define HEARTRATE14_PPG_CFG3_LED_SETLNG_8US     0x80
#define HEARTRATE14_PPG_CFG3_LED_SETLNG_12US    0xC0

/**
 * @brief Heart Rate 14 photo diode bias register setting.
 * @details Specified setting for photo diode bias register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_PD_BIAS_0_65PF              0x01
#define HEARTRATE14_PD_BIAS_65_130PF            0x05
#define HEARTRATE14_PD_BIAS_130_260PF           0x06
#define HEARTRATE14_PD_BIAS_260_520PF           0x07

/**
 * @brief Heart Rate 14 LED sequence registers setting.
 * @details Specified setting for LED sequence registers of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_LED_SEQ_NONE                0x00
#define HEARTRATE14_LED_SEQ_GREEN               0x01
#define HEARTRATE14_LED_SEQ_IR                  0x02
#define HEARTRATE14_LED_SEQ_RED                 0x03
#define HEARTRATE14_LED_SEQ_PILOT_GREEN         0x08
#define HEARTRATE14_LED_SEQ_AMBIENT             0x09
#define HEARTRATE14_LED_SEQ2_DIS_LEDC34         0x00
#define HEARTRATE14_LED_SEQ3_DIS_LEDC56         0x00
#define HEARTRATE14_LED_SEQ1_LEDC1_GREEN        0x01
#define HEARTRATE14_LED_SEQ1_LEDC2_NONE         0x00

/**
 * @brief Heart Rate 14 LED range 1 register setting.
 * @details Specified setting for LED range 1 register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_LED1_RGE_31MA               0x00
#define HEARTRATE14_LED1_RGE_62MA               0x01
#define HEARTRATE14_LED1_RGE_93MA               0x02
#define HEARTRATE14_LED1_RGE_124MA              0x03
#define HEARTRATE14_LED2_RGE_31MA               0x00
#define HEARTRATE14_LED2_RGE_62MA               0x04
#define HEARTRATE14_LED2_RGE_93MA               0x08
#define HEARTRATE14_LED2_RGE_124MA              0x0C
#define HEARTRATE14_LED3_RGE_31MA               0x00
#define HEARTRATE14_LED3_RGE_62MA               0x10
#define HEARTRATE14_LED3_RGE_93MA               0x20
#define HEARTRATE14_LED3_RGE_124MA              0x30

/**
 * @brief Heart Rate 14 LED pulse amplitude register setting.
 * @details Specified setting for LED pulse amplitude register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_LED1_PA_7P5MA               0x1F
#define HEARTRATE14_LED2_PA_OFF                 0x00
#define HEARTRATE14_LED3_PA_OFF                 0x00

/**
 * @brief Heart Rate 14 FIFO configuration 2 register setting.
 * @details Specified setting for FIFO configuration 2 register of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_FIFO_CFG2_FLUSH             0x10
#define HEARTRATE14_FIFO_CFG2_STAT_CLR          0x08
#define HEARTRATE14_FIFO_CFG2_A_FULL_TYPE       0x04
#define HEARTRATE14_FIFO_CFG2_FIFO_RO           0x02

/**
 * @brief Heart Rate 14 FIFO data format constants setting.
 * @details Specified setting for FIFO data format constants of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_FIFO_MAX_SAMPLES            128
#define HEARTRATE14_FIFO_BYTES_PER_SAMPLE       3
#define HEARTRATE14_FIFO_TAG_MASK               0x1F
#define HEARTRATE14_FIFO_ADC_MASK               0x0007FFFFul
#define HEARTRATE14_FIFO_TAG_LEDC1              0x01
#define HEARTRATE14_FIFO_TAG_LEDC2              0x02
#define HEARTRATE14_FIFO_TAG_LEDC3              0x03
#define HEARTRATE14_FIFO_TAG_INVALID            0x1E

/**
 * @brief Heart Rate 14 part ID value setting.
 * @details Specified setting for part ID value of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_PART_ID                     0x36

/**
 * @brief Heart Rate 14 timeout in milliseconds setting.
 * @details Specified setting for timeout in milliseconds of Heart Rate 14 Click driver.
 */
#define HEARTRATE14_TIMEOUT_MS                  5000

/**
 * @brief Heart Rate 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Heart Rate 14 Click driver.
 */
#define HEARTRATE14_DEVICE_ADDRESS              0x62

/*! @} */ // heartrate14_set

/**
 * @defgroup heartrate14_map Heart Rate 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Heart Rate 14 Click driver.
 */

/**
 * @addtogroup heartrate14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Heart Rate 14 Click to the selected MikroBUS.
 */
#define HEARTRATE14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.gpo = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.gpi = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // heartrate14_map
/*! @} */ // heartrate14

/**
 * @brief Heart Rate 14 Click context object.
 * @details Context object definition of Heart Rate 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t gpi;                          /**< GPIO input to sensor. */
    digital_out_t en;                           /**< Enable pin. */

    // Input pins
    digital_in_t gpo;                           /**< GPIO output from sensor. */
    digital_in_t int_pin;                       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} heartrate14_t;

/**
 * @brief Heart Rate 14 Click configuration object.
 * @details Configuration object definition of Heart Rate 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t gpo;                             /**< GPIO output from sensor descriptor. */
    pin_name_t gpi;                             /**< GPIO input to sensor descriptor. */
    pin_name_t en;                              /**< Enable pin descriptor. */
    pin_name_t int_pin;                         /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} heartrate14_cfg_t;

/**
 * @brief Heart Rate 14 Click FIFO data structure.
 * @details FIFO data object definition of Heart Rate 14 Click driver.
 */
typedef struct
{
    uint32_t ledc1;                             /**< 19-bit ADC value from LEDC1 time slot (default: Green LED) */
    uint32_t ledc2;                             /**< 19-bit ADC value from LEDC2 time slot (default: unused) */
    uint32_t ledc3;                             /**< 19-bit ADC value from LEDC3 time slot (default: unused) */

} heartrate14_fifo_data_t;

/**
 * @brief Heart Rate 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEARTRATE14_OK = 0,
    HEARTRATE14_ERROR = -1

} heartrate14_return_value_t;

/*!
 * @addtogroup heartrate14 Heart Rate 14 Click Driver
 * @brief API for configuring and manipulating Heart Rate 14 Click driver.
 * @{
 */

/**
 * @brief Heart Rate 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #heartrate14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void heartrate14_cfg_setup ( heartrate14_cfg_t *cfg );

/**
 * @brief Heart Rate 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #heartrate14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_init ( heartrate14_t *ctx, heartrate14_cfg_t *cfg );

/**
 * @brief Heart Rate 14 default configuration function.
 * @details This function executes a default configuration of Heart Rate 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t heartrate14_default_cfg ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_write_reg ( heartrate14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Heart Rate 14 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_write_regs ( heartrate14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Heart Rate 14 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_read_reg ( heartrate14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Heart Rate 14 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_read_regs ( heartrate14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Heart Rate 14 check communication function.
 * @details This function checks the communication by reading and verifying the PART_ID register.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_check_comm ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 software reset function.
 * @details This function performs a software reset by setting
 * the RESET bit in SYS_CTRL register.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait at least 1ms after calling this before any further register access.
 */
err_t heartrate14_sw_reset ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 enable device function.
 * @details This function enables its internal LDO by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void heartrate14_enable_device ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 disable device function.
 * @details This function disables its internal LDO by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void heartrate14_disable_device ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 get INT pin function.
 * @details This function returns the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return INT pin logic state.
 * @note None.
 */
uint8_t heartrate14_get_int_pin ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 get GPO pin function.
 * @details This function returns the logic state of the GPO pin.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return GPO pin logic state.
 * @note None.
 */
uint8_t heartrate14_get_gpo_pin ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 set GPI pin function.
 * @details This function sets the logic state of the GPI pin.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - LOW,
 *                    @li @c 1 - HIGH.
 * @return Nothing.
 * @note None.
 */
void heartrate14_set_gpi_pin ( heartrate14_t *ctx, uint8_t state );

/**
 * @brief Heart Rate 14 flush FIFO function.
 * @details This function clears all data from the FIFO and resets its
 * write/read pointers and data counter to zero.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_flush_fifo ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 wait data ready function.
 * @details This function waits until the INT pin goes LOW signaling
 * that new data is ready to be read from the FIFO.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_wait_data_ready ( heartrate14_t *ctx );

/**
 * @brief Heart Rate 14 get FIFO data function.
 * @details This function reads the FIFO whenever a new sample is ready and fills the provided
 * FIFO data structure with the sampled data.
 * @param[in] ctx : Click context object.
 * See #heartrate14_t object definition for detailed explanation.
 * @param[out] fifo_data : Pointer to the FIFO data structure to be filled.
 * See #heartrate14_fifo_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate14_get_fifo_data ( heartrate14_t *ctx, heartrate14_fifo_data_t *fifo_data );

#ifdef __cplusplus
}
#endif
#endif // HEARTRATE14_H

/*! @} */ // heartrate14

// ------------------------------------------------------------------------ END

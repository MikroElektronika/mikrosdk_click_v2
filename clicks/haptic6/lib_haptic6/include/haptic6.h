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
 * @file haptic6.h
 * @brief This file contains API for Haptic 6 Click Driver.
 */

#ifndef HAPTIC6_H
#define HAPTIC6_H

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
 * @addtogroup haptic6 Haptic 6 Click Driver
 * @brief API for configuring and manipulating Haptic 6 Click driver.
 * @{
 */

/**
 * @defgroup haptic6_reg Haptic 6 Registers List
 * @brief List of registers of Haptic 6 Click driver.
 */

/**
 * @addtogroup haptic6_reg
 * @{
 */

/**
 * @brief IQS397 version registers.
 * @details Read-only registers that contain product and firmware information.
 */
#define HAPTIC6_REG_PRODUCT_NUM                 0x0000
#define HAPTIC6_REG_MAJOR_VER                   0x0001
#define HAPTIC6_REG_MINOR_VER                   0x0002

/**
 * @brief IQS397 system control registers.
 * @details Registers used to acknowledge reset, select the I2C interface mode,
 * enable event reporting and configure power behavior.
 */
#define HAPTIC6_REG_SYS_COMMANDS                0x1000
#define HAPTIC6_REG_POWER_SETTINGS              0x1001
#define HAPTIC6_REG_EVENT_MASKS                 0x1002
#define HAPTIC6_REG_ULP_AR_WD                   0x1003
#define HAPTIC6_REG_I2C_TIMEOUT                 0x1010

/**
 * @brief IQS397 ProxFusion registers.
 * @details Registers used to read and configure the sensing channel.
 */
#define HAPTIC6_REG_PROXFUSION_0                0x1012
#define HAPTIC6_REG_PROXFUSION_1                0x1013
#define HAPTIC6_REG_PROX_THRESHOLD              0x1026
#define HAPTIC6_REG_TOUCH_THRESHOLD             0x102A
#define HAPTIC6_REG_PROXFUSION_DIV              0x103A
#define HAPTIC6_REG_PROXFUSION_COMP             0x103C

/**
 * @brief IQS397 haptics configuration registers.
 * @details Registers used to enable the LRA haptic output, configure the
 * H-bridge and select drive waveform settings.
 */
#define HAPTIC6_REG_HAPTIC_CONTROL              0x103E
#define HAPTIC6_REG_OT_SETTINGS                 0x103F
#define HAPTIC6_REG_HBRIDGE_SETUP               0x1042
#define HAPTIC6_REG_PWM_FREQUENCY               0x1044
#define HAPTIC6_REG_LRA_FREQUENCY               0x1046
#define HAPTIC6_REG_AR_SETTINGS                 0x1048
#define HAPTIC6_REG_DRIVE_SETTINGS              0x1049

/**
 * @brief IQS397 status and event registers.
 * @details Read-only registers that report power mode, reset, haptic,
 * proximity and touch events.
 */
#define HAPTIC6_REG_POWER_FLAGS                 0x2000
#define HAPTIC6_REG_DEVICE_STATUS               0x2001
#define HAPTIC6_REG_SYS_EVENTS                  0x2002
#define HAPTIC6_REG_PROXFUSION_STATE            0x2003
#define HAPTIC6_REG_INFO_FLAGS                  0x2004
#define HAPTIC6_REG_BUTTON_EVENTS               0x2005
#define HAPTIC6_REG_RAW_COUNTS                  0x2006
#define HAPTIC6_REG_FILTERED_COUNTS             0x200A
#define HAPTIC6_REG_DELTA                       0x2012

/*! @} */ // haptic6_reg

/**
 * @defgroup haptic6_set Haptic 6 Registers Settings
 * @brief Settings for registers of Haptic 6 Click driver.
 */

/**
 * @addtogroup haptic6_set
 * @{
 */

/**
 * @brief IQS397 System Commands register masks.
 * @details Command bits are self-clearing unless stated otherwise by the
 * device.
 */
#define HAPTIC6_SYS_CMD_TRIGGER                 0x20
#define HAPTIC6_SYS_CMD_RESEED                  0x10
#define HAPTIC6_SYS_CMD_ATI                     0x04
#define HAPTIC6_SYS_CMD_SOFT_RESET              0x02
#define HAPTIC6_SYS_CMD_ACK_RESET               0x01

/**
 * @brief IQS397 Power Settings register masks.
 * @details Values used to keep the I2C interface available and select IQS397
 * power mode.
 */
#define HAPTIC6_POWER_TERM_STOP                 0x80
#define HAPTIC6_POWER_IF_STREAMING              0x00
#define HAPTIC6_POWER_IF_EVENT                  0x20
#define HAPTIC6_POWER_IF_STANDALONE             0x60
#define HAPTIC6_POWER_MODE_NORMAL               0x00
#define HAPTIC6_POWER_MODE_ULP                  0x01
#define HAPTIC6_POWER_MODE_AUTO                 0x02

/**
 * @brief IQS397 event mask register masks.
 * @details Event masks open an I2C communication window when the selected
 * event occurs in event interface mode.
 */
#define HAPTIC6_EVENT_OT                        0x20
#define HAPTIC6_EVENT_HAPTIC                    0x10
#define HAPTIC6_EVENT_TOUCH                     0x08
#define HAPTIC6_EVENT_PROX                      0x04
#define HAPTIC6_EVENT_ATI                       0x02
#define HAPTIC6_EVENT_POWER                     0x01
#define HAPTIC6_EVENT_ALL                       0x3F

/**
 * @brief IQS397 Haptic Control register masks.
 * @details Bits used to enable, trigger or cancel LRA haptic output.
 */
#define HAPTIC6_HAPTIC_ENABLE                   0x0001
#define HAPTIC6_HAPTIC_TRIGGER                  0x0002
#define HAPTIC6_HAPTIC_CANCEL                   0x0004

/**
 * @brief IQS397 Device Status register masks.
 * @details Status bits reported by the IQS397 after reset and AutoProx
 * activity.
 */
#define HAPTIC6_DEV_STATUS_RESET                0x01
#define HAPTIC6_DEV_STATUS_AUTOPROX_ERR         0x02

/**
 * @brief IQS397 Button Event register masks.
 * @details Event flags reported by the ProxFusion button UI.
 */
#define HAPTIC6_BUTTON_LTA_HALT                 0x01
#define HAPTIC6_BUTTON_PROX                     0x02
#define HAPTIC6_BUTTON_TOUCH                    0x04

/**
 * @brief IQS397 Info Flags register masks.
 * @details Runtime state bits reported by the ProxFusion button UI.
 */
#define HAPTIC6_INFO_OUTPUT_STATE               0x01
#define HAPTIC6_INFO_DEBOUNCE                   0x02
#define HAPTIC6_INFO_SENSITIVITY                0x04
#define HAPTIC6_INFO_REPORT_RATE                0x08

/**
 * @brief IQS397 default haptic settings.
 * @details Values used by #haptic6_default_cfg for a basic LRA haptic pulse
 * configuration.
 */
#define HAPTIC6_DEF_HBRIDGE_SETUP               0x153E
#define HAPTIC6_DEF_PWM_FREQ                    20000
#define HAPTIC6_DEF_LRA_FREQ                    240
#define HAPTIC6_DEF_AR_SETTINGS                 0x51
#define HAPTIC6_DEF_DRIVE_SETTINGS              0xE0
#define HAPTIC6_DEF_I2C_TIMEOUT                 250

/**
 * @brief Haptic 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Haptic 6 Click driver.
 */
#define HAPTIC6_DEVICE_ADDRESS                  0x56

/*! @} */ // haptic6_set

/**
 * @defgroup haptic6_map Haptic 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Haptic 6 Click driver.
 */

/**
 * @addtogroup haptic6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Haptic 6 Click to the selected MikroBUS.
 */
#define HAPTIC6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // haptic6_map
/*! @} */ // haptic6

/**
 * @brief Haptic 6 Click context object.
 * @details Context object definition of Haptic 6 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t rdy;               /**< Ready interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} haptic6_t;

/**
 * @brief Haptic 6 Click configuration object.
 * @details Configuration object definition of Haptic 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rdy;                 /**< Ready interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} haptic6_cfg_t;

/**
 * @brief Haptic 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HAPTIC6_OK = 0,
    HAPTIC6_ERROR = -1

} haptic6_return_value_t;

/*!
 * @addtogroup haptic6 Haptic 6 Click Driver
 * @brief API for configuring and manipulating Haptic 6 Click driver.
 * @{
 */

/**
 * @brief Haptic 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #haptic6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void haptic6_cfg_setup ( haptic6_cfg_t *cfg );

/**
 * @brief Haptic 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #haptic6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_init ( haptic6_t *ctx, haptic6_cfg_t *cfg );

/**
 * @brief Haptic 6 default configuration function.
 * @details This function executes a default configuration of Haptic 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t haptic6_default_cfg ( haptic6_t *ctx );

/**
 * @brief Haptic 6 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_write_reg ( haptic6_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief Haptic 6 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_write_regs ( haptic6_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Haptic 6 write register word function.
 * @details This function writes a data word to the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written (16-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_write_reg_word ( haptic6_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief Haptic 6 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_read_reg ( haptic6_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief Haptic 6 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_read_regs ( haptic6_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Haptic 6 read register word function.
 * @details This function reads a data word from the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_read_reg_word ( haptic6_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief Haptic 6 trigger function.
 * @details This function triggers one haptic waveform using the IQS397 System
 * Commands register.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Haptics must be enabled before triggering.
 */
err_t haptic6_trigger ( haptic6_t *ctx );

/**
 * @brief Haptic 6 cancel function.
 * @details This function cancels the active haptic waveform.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_cancel ( haptic6_t *ctx );

/**
 * @brief Haptic 6 reset acknowledge function.
 * @details This function sends the IQS397 Ack Reset command.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_ack_reset ( haptic6_t *ctx );

/**
 * @brief Haptic 6 soft reset function.
 * @details This function sends the IQS397 Soft Reset command.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic6_soft_reset ( haptic6_t *ctx );

/**
 * @brief Haptic 6 RDY state function.
 * @details This function reads the IQS397 RDY/IRQ pin state.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c 0 - RDY pin is low,
 *         @li @c 1 - RDY pin is high.
 * @note None.
 */
uint8_t haptic6_get_rdy ( haptic6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HAPTIC6_H

/*! @} */ // haptic6

// ------------------------------------------------------------------------ END

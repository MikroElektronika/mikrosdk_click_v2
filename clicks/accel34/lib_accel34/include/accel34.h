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
 * @file accel34.h
 * @brief This file contains API for Accel 34 Click Driver.
 */

#ifndef ACCEL34_H
#define ACCEL34_H

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
 * @addtogroup accel34 Accel 34 Click Driver
 * @brief API for configuring and manipulating Accel 34 Click driver.
 * @{
 */

/**
 * @defgroup accel34_reg Accel 34 Registers List
 * @brief List of registers of Accel 34 Click driver.
 */

/**
 * @addtogroup accel34_reg
 * @{
 */

/**
 * @brief Accel 34 register map.
 * @details Specified register map of Accel 34 Click driver.
 */
#define ACCEL34_REG_DEVID_AD                0x00
#define ACCEL34_REG_DEVID_MST               0x01
#define ACCEL34_REG_PART_ID                 0x02
#define ACCEL34_REG_PART_ID_REV_ID          0x03
#define ACCEL34_REG_SERIAL_NUMBER_0         0x04
#define ACCEL34_REG_SERIAL_NUMBER_1         0x05
#define ACCEL34_REG_SERIAL_NUMBER_2         0x06
#define ACCEL34_REG_SERIAL_NUMBER_3         0x07
#define ACCEL34_REG_SERIAL_NUMBER_4         0x08
#define ACCEL34_REG_SERIAL_NUMBER_5         0x09
#define ACCEL34_REG_SERIAL_NUMBER_6         0x0A
#define ACCEL34_REG_DEV_DELTA_Q_X           0x0B
#define ACCEL34_REG_DEV_DELTA_Q_Y           0x0C
#define ACCEL34_REG_DEV_DELTA_Q_Z           0x0D
#define ACCEL34_REG_DEV_DELTA_F0_X          0x0E
#define ACCEL34_REG_DEV_DELTA_F0_Y          0x0F
#define ACCEL34_REG_DEV_DELTA_F0_Z          0x10
#define ACCEL34_REG_STATUS0                 0x11
#define ACCEL34_REG_STATUS1                 0x12
#define ACCEL34_REG_STATUS2                 0x13
#define ACCEL34_REG_STATUS3                 0x14
#define ACCEL34_REG_XDATA_H                 0x15
#define ACCEL34_REG_XDATA_L                 0x16
#define ACCEL34_REG_YDATA_H                 0x17
#define ACCEL34_REG_YDATA_L                 0x18
#define ACCEL34_REG_ZDATA_H                 0x19
#define ACCEL34_REG_ZDATA_L                 0x1A
#define ACCEL34_REG_TDATA_H                 0x1B
#define ACCEL34_REG_TDATA_L                 0x1C
#define ACCEL34_REG_FIFO_DATA               0x1D
#define ACCEL34_REG_FIFO_STATUS0            0x1E
#define ACCEL34_REG_FIFO_STATUS1            0x1F
#define ACCEL34_REG_MISC0                   0x20
#define ACCEL34_REG_MISC1                   0x21
#define ACCEL34_REG_SENS_DSM                0x24
#define ACCEL34_REG_CLK_CTRL                0x25
#define ACCEL34_REG_OP_MODE                 0x26
#define ACCEL34_REG_DIG_EN                  0x27
#define ACCEL34_REG_SAR_I2C                 0x28
#define ACCEL34_REG_NVM_CTL                 0x29
#define ACCEL34_REG_RESET                   0x2A
#define ACCEL34_REG_INT0_MAP0               0x2B
#define ACCEL34_REG_INT0_MAP1               0x2C
#define ACCEL34_REG_INT1_MAP0               0x2D
#define ACCEL34_REG_INT1_MAP1               0x2E
#define ACCEL34_REG_FIFO_CFG0               0x30
#define ACCEL34_REG_FIFO_CFG1               0x31
#define ACCEL34_REG_SPT_CFG0                0x32
#define ACCEL34_REG_SPT_CFG1                0x33
#define ACCEL34_REG_SPT_CFG2                0x34
#define ACCEL34_REG_SYNC_CFG                0x35
#define ACCEL34_REG_PDM_CFG                 0x36
#define ACCEL34_REG_ACT_INACT_CTL           0x37
#define ACCEL34_REG_SNSR_AXIS_EN            0x38
#define ACCEL34_REG_THRESH_ACT_H            0x39
#define ACCEL34_REG_THRESH_ACT_L            0x3A
#define ACCEL34_REG_TIME_ACT_H              0x3B
#define ACCEL34_REG_TIME_ACT_M              0x3C
#define ACCEL34_REG_TIME_ACT_L              0x3D
#define ACCEL34_REG_THRESH_INACT_H          0x3E
#define ACCEL34_REG_THRESH_INACT_L          0x3F
#define ACCEL34_REG_TIME_INACT_H            0x40
#define ACCEL34_REG_TIME_INACT_M            0x41
#define ACCEL34_REG_TIME_INACT_L            0x42
#define ACCEL34_REG_TAP_THRESH              0x43
#define ACCEL34_REG_TAP_DUR                 0x44
#define ACCEL34_REG_TAP_LATENT              0x45
#define ACCEL34_REG_TAP_WINDOW              0x46
#define ACCEL34_REG_TAP_CFG                 0x47
#define ACCEL34_REG_OR_CFG                  0x48
#define ACCEL34_REG_TRIG_CFG                0x49
#define ACCEL34_REG_X_SAR_OFFSET            0x4A
#define ACCEL34_REG_Y_SAR_OFFSET            0x4B
#define ACCEL34_REG_Z_SAR_OFFSET            0x4C
#define ACCEL34_REG_X_DSM_OFFSET            0x4D
#define ACCEL34_REG_Y_DSM_OFFSET            0x4E
#define ACCEL34_REG_Z_DSM_OFFSET            0x4F
#define ACCEL34_REG_FILTER                  0x50
#define ACCEL34_REG_USER_TEMP_SENS_0        0x55
#define ACCEL34_REG_USER_TEMP_SENS_1        0x56
#define ACCEL34_REG_MISO                    0x58
#define ACCEL34_REG_SOUT0                   0x59
#define ACCEL34_REG_MCLK                    0x5A
#define ACCEL34_REG_BCLK                    0x5B
#define ACCEL34_REG_FSYNC                   0x5C
#define ACCEL34_REG_INT0                    0x5D
#define ACCEL34_REG_INT1                    0x5E

/*! @} */ // accel34_reg

/**
 * @defgroup accel34_set Accel 34 Registers Settings
 * @brief Settings for registers of Accel 34 Click driver.
 */

/**
 * @addtogroup accel34_set
 * @{
 */

/**
 * @brief Accel 34 INTx_MAPx registers settings.
 * @details Specified INTx_MAPx registers settings of Accel 34 Click driver.
 */
#define ACCEL34_INTX_MAP0_NVM_BUSY          0x80
#define ACCEL34_INTX_MAP0_INACT             0x40
#define ACCEL34_INTX_MAP0_ACT               0x20
#define ACCEL34_INTX_MAP0_FIFO_WATERMARK    0x08
#define ACCEL34_INTX_MAP0_FIFO_OVERRUN      0x04
#define ACCEL34_INTX_MAP0_FIFO_FULL         0x02
#define ACCEL34_INTX_MAP0_DATA_RDY          0x01
#define ACCEL34_INTX_MAP1_NVM_DONE          0x80
#define ACCEL34_INTX_MAP1_NVM_IRQ           0x40
#define ACCEL34_INTX_MAP1_UV_FLAG           0x20
#define ACCEL34_INTX_MAP1_OVER_RANGE        0x10
#define ACCEL34_INTX_MAP1_PARITY_ERR        0x08
#define ACCEL34_INTX_MAP1_TRIPLE_TAP        0x04
#define ACCEL34_INTX_MAP1_DOUBLE_TAP        0x02
#define ACCEL34_INTX_MAP1_SINGLE_TAP        0x01

/**
 * @brief Accel 34 OP_MODE register settings.
 * @details Specified OP_MODE register settings of Accel 34 Click driver.
 */
#define ACCEL34_OP_MODE_RANGE_15G           0x00
#define ACCEL34_OP_MODE_RANGE_30G           0x40
#define ACCEL34_OP_MODE_RANGE_60G           0x80
#define ACCEL34_OP_MODE_RANGE_MASK          0xC0
#define ACCEL34_OP_MODE_PDM_MODE_DIS        0x00
#define ACCEL34_OP_MODE_PDM_MODE_EN         0x20
#define ACCEL34_OP_MODE_PDM_MODE_MASK       0x20
#define ACCEL34_OP_MODE_AUDIO_MODE_DIS      0x00
#define ACCEL34_OP_MODE_AUDIO_MODE_EN       0x10
#define ACCEL34_OP_MODE_AUDIO_MODE_MASK     0x10
#define ACCEL34_OP_MODE_STANDBY             0x00
#define ACCEL34_OP_MODE_HEART_SOUND         0x01
#define ACCEL34_OP_MODE_ULP                 0x02
#define ACCEL34_OP_MODE_VLP                 0x03
#define ACCEL34_OP_MODE_LP                  0x04
#define ACCEL34_OP_MODE_LP_ULP              0x06
#define ACCEL34_OP_MODE_LP_VLP              0x07
#define ACCEL34_OP_MODE_RBW                 0x08
#define ACCEL34_OP_MODE_RBW_ULP             0x0A
#define ACCEL34_OP_MODE_RBW_VLP             0x0B
#define ACCEL34_OP_MODE_HP                  0x0C
#define ACCEL34_OP_MODE_HP_ULP              0x0E
#define ACCEL34_OP_MODE_HP_VLP              0x0F
#define ACCEL34_OP_MODE_MASK                0x0F

/**
 * @brief Accel 34 DIG_EN register settings.
 * @details Specified DIG_EN register settings of Accel 34 Click driver.
 */
#define ACCEL34_DIG_EN_MODE_CHANNEL_EN_X    0x10
#define ACCEL34_DIG_EN_MODE_CHANNEL_EN_Y    0x20
#define ACCEL34_DIG_EN_MODE_CHANNEL_EN_Z    0x40
#define ACCEL34_DIG_EN_MODE_CHANNEL_EN_TEMP 0x80
#define ACCEL34_DIG_EN_MODE_CHANNEL_EN_ALL  0xF0
#define ACCEL34_DIG_EN_MODE_CHANNEL_EN_MASK 0xF0
#define ACCEL34_DIG_EN_FIFO_EN_DIS          0x00
#define ACCEL34_DIG_EN_FIFO_EN_EN           0x08
#define ACCEL34_DIG_EN_FIFO_EN_MASK         0x08
#define ACCEL34_DIG_EN_INT01_EVENT_LIVE     0x00
#define ACCEL34_DIG_EN_INT01_EVENT_EVENT    0x02
#define ACCEL34_DIG_EN_INT01_EVENT_MASK     0x02
#define ACCEL34_DIG_EN_PARITY_EN_DIS        0x00
#define ACCEL34_DIG_EN_PARITY_EN_EN         0x01
#define ACCEL34_DIG_EN_PARITY_EN_MASK       0x01

/**
 * @brief Accel 34 STATUS3 register settings.
 * @details Specified STATUS3 register settings of Accel 34 Click driver.
 */
#define ACCEL34_STATUS3_DATA_READY          0x01

/**
 * @brief Accel 34 RESET register settings.
 * @details Specified RESET register settings of Accel 34 Click driver.
 */
#define ACCEL34_RESET                       0x02

/**
 * @brief Accel 34 device ID setting.
 * @details Specified setting for device ID of Accel 34 Click driver.
 */
#define ACCEL34_DEVID_AD                    0xAD
#define ACCEL34_DEVID_MST                   0x1D

/**
 * @brief Accel 34 accel full scale range setting.
 * @details Specified setting for accel full scale range of Accel 34 Click driver.
 */
#define ACCEL34_ACCEL_FSR_15G               0
#define ACCEL34_ACCEL_FSR_30G               1
#define ACCEL34_ACCEL_FSR_60G               2

/**
 * @brief Accel 34 data resolution settings.
 * @details Specified data resolution settings of Accel 34 Click driver.
 */
#define ACCEL34_SCALE_FACTOR_LSB_PER_G      2000.0f
#define ACCEL34_TEMP_SENS                   10.2f
#define ACCEL34_TEMP_OFFSET_LSB             295

/**
 * @brief Accel 34 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 34 Click driver.
 */
#define ACCEL34_DEVICE_ADDRESS_0            0x1D
#define ACCEL34_DEVICE_ADDRESS_1            0x53
#define ACCEL34_DEVICE_ADDRESS_2            0x54
#define ACCEL34_DEVICE_ADDRESS_3            0x55

/*! @} */ // accel34_set

/**
 * @defgroup accel34_map Accel 34 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 34 Click driver.
 */

/**
 * @addtogroup accel34_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 34 Click to the selected MikroBUS.
 */
#define ACCEL34_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel34_map
/*! @} */ // accel34

/**
 * @brief Accel 34 Click context object.
 * @details Context object definition of Accel 34 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int0;      /**< Interrupt 0 pin. */
    digital_in_t int1;      /**< Interrupt 1 pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

    float accel_sens;       /**< Accel sensitivity setting. */

} accel34_t;

/**
 * @brief Accel 34 Click configuration object.
 * @details Configuration object definition of Accel 34 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int0;        /**< Interrupt 0 pin. */
    pin_name_t int1;        /**< Interrupt 1 pin. */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} accel34_cfg_t;

/**
 * @brief Accel 34 Click axes data structure.
 * @details Axes data object definition of Accel 34 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel34_axes_t;

/**
 * @brief Accel 34 Click data structure.
 * @details Data object definition of Accel 34 Click driver.
 */
typedef struct
{
    accel34_axes_t accel;           /**< Accel data. */
    float temperature;              /**< Temperature data. */

} accel34_data_t;

/**
 * @brief Accel 34 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL34_OK = 0,
    ACCEL34_ERROR = -1,
    ACCEL34_DATA_NOT_READY = -2

} accel34_return_value_t;

/*!
 * @addtogroup accel34 Accel 34 Click Driver
 * @brief API for configuring and manipulating Accel 34 Click driver.
 * @{
 */

/**
 * @brief Accel 34 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel34_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel34_cfg_setup ( accel34_cfg_t *cfg );

/**
 * @brief Accel 34 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel34_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel34_init ( accel34_t *ctx, accel34_cfg_t *cfg );

/**
 * @brief Accel 34 default configuration function.
 * @details This function executes a default configuration of Accel 34
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel34_default_cfg ( accel34_t *ctx );

/**
 * @brief Accel 34 write multiple registers function.
 * @details This function writes data to multiple registers of the Accel 34 device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_write_regs ( accel34_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 34 read multiple registers function.
 * @details This function reads data from multiple registers of the Accel 34 device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_read_regs ( accel34_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 34 write single register function.
 * @details This function writes a single byte to a specified register of the Accel 34 device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_write_reg ( accel34_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 34 read single register function.
 * @details This function reads a single byte from a specified register of the Accel 34 device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to store read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_read_reg ( accel34_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 34 get INT0 pin state function.
 * @details This function returns the logic state of the INT0 interrupt pin.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel34_get_int0_pin ( accel34_t *ctx );

/**
 * @brief Accel 34 get INT1 pin state function.
 * @details This function returns the logic state of the INT1 interrupt pin.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel34_get_int1_pin ( accel34_t *ctx );

/**
 * @brief Accel 34 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @return @li @c  0 - Success (device detected),
 *         @li @c -1 - Error (device not detected).
 * @note None.
 */
err_t accel34_check_communication ( accel34_t *ctx );

/**
 * @brief Accel 34 reset device function.
 * @details This function soft resets the Accel 34 device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_reset_device ( accel34_t *ctx );

/**
 * @brief Accel 34 set operating mode function.
 * @details This function sets the operating mode of the Accel 34 device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_set_op_mode ( accel34_t *ctx, uint8_t op_mode );

/**
 * @brief Accel 34 set full-scale range function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 15G,
 *                  @li @c 1 - 30G,
 *                  @li @c 2 - 60G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_set_accel_fsr ( accel34_t *ctx, uint8_t fsr );

/**
 * @brief Accel 34 get data ready status function.
 * @details This function checks if new accelerometer data is available.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel34_get_drdy ( accel34_t *ctx, uint8_t *drdy );

/**
 * @brief Accel 34 get accelerometer data function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (g).
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[out] accel : Pointer to store the acceleration values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (data not ready).
 * @note None.
 */
err_t accel34_get_accel ( accel34_t *ctx, accel34_axes_t *accel );

/**
 * @brief Accel 34 get temperature function.
 * @details This function reads the internal temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[out] temp : Pointer to store the temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (data not ready).
 * @note None.
 */
err_t accel34_get_temp ( accel34_t *ctx, float *temp );

/**
 * @brief Accel 34 get accelerometer and temperature data function.
 * @details This function reads both accelerometer and temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel34_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store the acceleration and temperature values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (data not ready).
 * @note None.
 */
err_t accel34_get_data ( accel34_t *ctx, accel34_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ACCEL34_H

/*! @} */ // accel34

// ------------------------------------------------------------------------ END

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
 * @file accel32.h
 * @brief This file contains API for Accel 32 Click Driver.
 */

#ifndef ACCEL32_H
#define ACCEL32_H

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
 * @addtogroup accel32 Accel 32 Click Driver
 * @brief API for configuring and manipulating Accel 32 Click driver.
 * @{
 */

/**
 * @defgroup accel32_reg Accel 32 Registers List
 * @brief List of registers of Accel 32 Click driver.
 */

/**
 * @addtogroup accel32_reg
 * @{
 */

/**
 * @brief Accel 32 register map.
 * @details Specified register map of Accel 32 Click driver.
 */
#define ACCEL32_REG_DEVID_AD                0x00
#define ACCEL32_REG_DEVID_MST               0x01
#define ACCEL32_REG_PART_ID                 0x02
#define ACCEL32_REG_PART_ID_REV_ID          0x03
#define ACCEL32_REG_SERIAL_NUMBER_0         0x04
#define ACCEL32_REG_SERIAL_NUMBER_1         0x05
#define ACCEL32_REG_SERIAL_NUMBER_2         0x06
#define ACCEL32_REG_SERIAL_NUMBER_3         0x07
#define ACCEL32_REG_SERIAL_NUMBER_4         0x08
#define ACCEL32_REG_SERIAL_NUMBER_5         0x09
#define ACCEL32_REG_SERIAL_NUMBER_6         0x0A
#define ACCEL32_REG_DEV_DELTA_Q_X           0x0B
#define ACCEL32_REG_DEV_DELTA_Q_Y           0x0C
#define ACCEL32_REG_DEV_DELTA_Q_Z           0x0D
#define ACCEL32_REG_DEV_DELTA_F0_X          0x0E
#define ACCEL32_REG_DEV_DELTA_F0_Y          0x0F
#define ACCEL32_REG_DEV_DELTA_F0_Z          0x10
#define ACCEL32_REG_STATUS0                 0x11
#define ACCEL32_REG_STATUS1                 0x12
#define ACCEL32_REG_STATUS2                 0x13
#define ACCEL32_REG_STATUS3                 0x14
#define ACCEL32_REG_XDATA_H                 0x15
#define ACCEL32_REG_XDATA_L                 0x16
#define ACCEL32_REG_YDATA_H                 0x17
#define ACCEL32_REG_YDATA_L                 0x18
#define ACCEL32_REG_ZDATA_H                 0x19
#define ACCEL32_REG_ZDATA_L                 0x1A
#define ACCEL32_REG_TDATA_H                 0x1B
#define ACCEL32_REG_TDATA_L                 0x1C
#define ACCEL32_REG_FIFO_DATA               0x1D
#define ACCEL32_REG_FIFO_STATUS0            0x1E
#define ACCEL32_REG_FIFO_STATUS1            0x1F
#define ACCEL32_REG_MISC0                   0x20
#define ACCEL32_REG_MISC1                   0x21
#define ACCEL32_REG_SENS_DSM                0x24
#define ACCEL32_REG_CLK_CTRL                0x25
#define ACCEL32_REG_OP_MODE                 0x26
#define ACCEL32_REG_DIG_EN                  0x27
#define ACCEL32_REG_SAR_I2C                 0x28
#define ACCEL32_REG_NVM_CTL                 0x29
#define ACCEL32_REG_RESET                   0x2A
#define ACCEL32_REG_INT0_MAP0               0x2B
#define ACCEL32_REG_INT0_MAP1               0x2C
#define ACCEL32_REG_INT1_MAP0               0x2D
#define ACCEL32_REG_INT1_MAP1               0x2E
#define ACCEL32_REG_FIFO_CFG0               0x30
#define ACCEL32_REG_FIFO_CFG1               0x31
#define ACCEL32_REG_SPT_CFG0                0x32
#define ACCEL32_REG_SPT_CFG1                0x33
#define ACCEL32_REG_SPT_CFG2                0x34
#define ACCEL32_REG_SYNC_CFG                0x35
#define ACCEL32_REG_PDM_CFG                 0x36
#define ACCEL32_REG_ACT_INACT_CTL           0x37
#define ACCEL32_REG_SNSR_AXIS_EN            0x38
#define ACCEL32_REG_THRESH_ACT_H            0x39
#define ACCEL32_REG_THRESH_ACT_L            0x3A
#define ACCEL32_REG_TIME_ACT_H              0x3B
#define ACCEL32_REG_TIME_ACT_M              0x3C
#define ACCEL32_REG_TIME_ACT_L              0x3D
#define ACCEL32_REG_THRESH_INACT_H          0x3E
#define ACCEL32_REG_THRESH_INACT_L          0x3F
#define ACCEL32_REG_TIME_INACT_H            0x40
#define ACCEL32_REG_TIME_INACT_M            0x41
#define ACCEL32_REG_TIME_INACT_L            0x42
#define ACCEL32_REG_TAP_THRESH              0x43
#define ACCEL32_REG_TAP_DUR                 0x44
#define ACCEL32_REG_TAP_LATENT              0x45
#define ACCEL32_REG_TAP_WINDOW              0x46
#define ACCEL32_REG_TAP_CFG                 0x47
#define ACCEL32_REG_OR_CFG                  0x48
#define ACCEL32_REG_TRIG_CFG                0x49
#define ACCEL32_REG_X_SAR_OFFSET            0x4A
#define ACCEL32_REG_Y_SAR_OFFSET            0x4B
#define ACCEL32_REG_Z_SAR_OFFSET            0x4C
#define ACCEL32_REG_X_DSM_OFFSET            0x4D
#define ACCEL32_REG_Y_DSM_OFFSET            0x4E
#define ACCEL32_REG_Z_DSM_OFFSET            0x4F
#define ACCEL32_REG_FILTER                  0x50
#define ACCEL32_REG_USER_TEMP_SENS_0        0x55
#define ACCEL32_REG_USER_TEMP_SENS_1        0x56
#define ACCEL32_REG_MISO                    0x58
#define ACCEL32_REG_SOUT0                   0x59
#define ACCEL32_REG_MCLK                    0x5A
#define ACCEL32_REG_BCLK                    0x5B
#define ACCEL32_REG_FSYNC                   0x5C
#define ACCEL32_REG_INT0                    0x5D
#define ACCEL32_REG_INT1                    0x5E

/*! @} */ // accel32_reg

/**
 * @defgroup accel32_set Accel 32 Registers Settings
 * @brief Settings for registers of Accel 32 Click driver.
 */

/**
 * @addtogroup accel32_set
 * @{
 */

/**
 * @brief Accel 32 INTx_MAPx registers settings.
 * @details Specified INTx_MAPx registers settings of Accel 32 Click driver.
 */
#define ACCEL32_INTX_MAP0_NVM_BUSY          0x80
#define ACCEL32_INTX_MAP0_INACT             0x40
#define ACCEL32_INTX_MAP0_ACT               0x20
#define ACCEL32_INTX_MAP0_FIFO_WATERMARK    0x08
#define ACCEL32_INTX_MAP0_FIFO_OVERRUN      0x04
#define ACCEL32_INTX_MAP0_FIFO_FULL         0x02
#define ACCEL32_INTX_MAP0_DATA_RDY          0x01
#define ACCEL32_INTX_MAP1_NVM_DONE          0x80
#define ACCEL32_INTX_MAP1_NVM_IRQ           0x40
#define ACCEL32_INTX_MAP1_UV_FLAG           0x20
#define ACCEL32_INTX_MAP1_OVER_RANGE        0x10
#define ACCEL32_INTX_MAP1_PARITY_ERR        0x08
#define ACCEL32_INTX_MAP1_TRIPLE_TAP        0x04
#define ACCEL32_INTX_MAP1_DOUBLE_TAP        0x02
#define ACCEL32_INTX_MAP1_SINGLE_TAP        0x01

/**
 * @brief Accel 32 OP_MODE register settings.
 * @details Specified OP_MODE register settings of Accel 32 Click driver.
 */
#define ACCEL32_OP_MODE_RANGE_15G           0x00
#define ACCEL32_OP_MODE_RANGE_30G           0x40
#define ACCEL32_OP_MODE_RANGE_60G           0x80
#define ACCEL32_OP_MODE_RANGE_MASK          0xC0
#define ACCEL32_OP_MODE_PDM_MODE_DIS        0x00
#define ACCEL32_OP_MODE_PDM_MODE_EN         0x20
#define ACCEL32_OP_MODE_PDM_MODE_MASK       0x20
#define ACCEL32_OP_MODE_AUDIO_MODE_DIS      0x00
#define ACCEL32_OP_MODE_AUDIO_MODE_EN       0x10
#define ACCEL32_OP_MODE_AUDIO_MODE_MASK     0x10
#define ACCEL32_OP_MODE_STANDBY             0x00
#define ACCEL32_OP_MODE_HEART_SOUND         0x01
#define ACCEL32_OP_MODE_ULP                 0x02
#define ACCEL32_OP_MODE_VLP                 0x03
#define ACCEL32_OP_MODE_LP                  0x04
#define ACCEL32_OP_MODE_LP_ULP              0x06
#define ACCEL32_OP_MODE_LP_VLP              0x07
#define ACCEL32_OP_MODE_RBW                 0x08
#define ACCEL32_OP_MODE_RBW_ULP             0x0A
#define ACCEL32_OP_MODE_RBW_VLP             0x0B
#define ACCEL32_OP_MODE_HP                  0x0C
#define ACCEL32_OP_MODE_HP_ULP              0x0E
#define ACCEL32_OP_MODE_HP_VLP              0x0F
#define ACCEL32_OP_MODE_MASK                0x0F

/**
 * @brief Accel 32 DIG_EN register settings.
 * @details Specified DIG_EN register settings of Accel 32 Click driver.
 */
#define ACCEL32_DIG_EN_MODE_CHANNEL_EN_X    0x10
#define ACCEL32_DIG_EN_MODE_CHANNEL_EN_Y    0x20
#define ACCEL32_DIG_EN_MODE_CHANNEL_EN_Z    0x40
#define ACCEL32_DIG_EN_MODE_CHANNEL_EN_TEMP 0x80
#define ACCEL32_DIG_EN_MODE_CHANNEL_EN_ALL  0xF0
#define ACCEL32_DIG_EN_MODE_CHANNEL_EN_MASK 0xF0
#define ACCEL32_DIG_EN_FIFO_EN_DIS          0x00
#define ACCEL32_DIG_EN_FIFO_EN_EN           0x08
#define ACCEL32_DIG_EN_FIFO_EN_MASK         0x08
#define ACCEL32_DIG_EN_INT01_EVENT_LIVE     0x00
#define ACCEL32_DIG_EN_INT01_EVENT_EVENT    0x02
#define ACCEL32_DIG_EN_INT01_EVENT_MASK     0x02
#define ACCEL32_DIG_EN_PARITY_EN_DIS        0x00
#define ACCEL32_DIG_EN_PARITY_EN_EN         0x01
#define ACCEL32_DIG_EN_PARITY_EN_MASK       0x01

/**
 * @brief Accel 32 STATUS3 register settings.
 * @details Specified STATUS3 register settings of Accel 32 Click driver.
 */
#define ACCEL32_STATUS3_DATA_READY          0x01

/**
 * @brief Accel 32 RESET register settings.
 * @details Specified RESET register settings of Accel 32 Click driver.
 */
#define ACCEL32_RESET                       0x02

/**
 * @brief Accel 32 device ID setting.
 * @details Specified setting for device ID of Accel 32 Click driver.
 */
#define ACCEL32_DEVID_AD                    0xAD
#define ACCEL32_DEVID_MST                   0x1D

/**
 * @brief Accel 32 accel full scale range setting.
 * @details Specified setting for accel full scale range of Accel 32 Click driver.
 */
#define ACCEL32_ACCEL_FSR_15G               0
#define ACCEL32_ACCEL_FSR_30G               1
#define ACCEL32_ACCEL_FSR_60G               2

/**
 * @brief Accel 32 data resolution settings.
 * @details Specified data resolution settings of Accel 32 Click driver.
 */
#define ACCEL32_SCALE_FACTOR_LSB_PER_G      2000.0f
#define ACCEL32_TEMP_SENS                   10.2f
#define ACCEL32_TEMP_OFFSET_LSB             295

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel32_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL32_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL32_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel32_set

/**
 * @defgroup accel32_map Accel 32 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 32 Click driver.
 */

/**
 * @addtogroup accel32_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 32 Click to the selected MikroBUS.
 */
#define ACCEL32_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel32_map
/*! @} */ // accel32

/**
 * @brief Accel 32 Click context object.
 * @details Context object definition of Accel 32 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int0;              /**< Interrupt 0 pin. */
    digital_in_t int1;              /**< Interrupt 1 pin. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    float accel_sens;               /**< Accel sensitivity setting. */

} accel32_t;

/**
 * @brief Accel 32 Click configuration object.
 * @details Configuration object definition of Accel 32 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t int0;                /**< Interrupt 0 pin. */
    pin_name_t int1;                /**< Interrupt 1 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} accel32_cfg_t;

/**
 * @brief Accel 32 Click axes data structure.
 * @details Axes data object definition of Accel 32 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel32_axes_t;

/**
 * @brief Accel 32 Click data structure.
 * @details Data object definition of Accel 32 Click driver.
 */
typedef struct
{
    accel32_axes_t accel;           /**< Accel data. */
    float temperature;              /**< Temperature data. */

} accel32_data_t;

/**
 * @brief Accel 32 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL32_OK = 0,
    ACCEL32_ERROR = -1,
    ACCEL32_DATA_NOT_READY = -2

} accel32_return_value_t;

/*!
 * @addtogroup accel32 Accel 32 Click Driver
 * @brief API for configuring and manipulating Accel 32 Click driver.
 * @{
 */

/**
 * @brief Accel 32 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel32_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel32_cfg_setup ( accel32_cfg_t *cfg );

/**
 * @brief Accel 32 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel32_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel32_init ( accel32_t *ctx, accel32_cfg_t *cfg );

/**
 * @brief Accel 32 default configuration function.
 * @details This function executes a default configuration of Accel 32
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel32_default_cfg ( accel32_t *ctx );

/**
 * @brief Accel 32 write multiple registers function.
 * @details This function writes data to multiple registers of the Accel 32 device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_write_regs ( accel32_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 32 read multiple registers function.
 * @details This function reads data from multiple registers of the Accel 32 device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_read_regs ( accel32_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 32 write single register function.
 * @details This function writes a single byte to a specified register of the Accel 32 device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_write_reg ( accel32_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 32 read single register function.
 * @details This function reads a single byte from a specified register of the Accel 32 device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to store read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_read_reg ( accel32_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 32 get INT0 pin state function.
 * @details This function returns the logic state of the INT0 interrupt pin.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel32_get_int0_pin ( accel32_t *ctx );

/**
 * @brief Accel 32 get INT1 pin state function.
 * @details This function returns the logic state of the INT1 interrupt pin.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel32_get_int1_pin ( accel32_t *ctx );

/**
 * @brief Accel 32 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @return @li @c  0 - Success (device detected),
 *         @li @c -1 - Error (device not detected).
 * @note None.
 */
err_t accel32_check_communication ( accel32_t *ctx );

/**
 * @brief Accel 32 reset device function.
 * @details This function soft resets the Accel 32 device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_reset_device ( accel32_t *ctx );

/**
 * @brief Accel 32 set operating mode function.
 * @details This function sets the operating mode of the Accel 32 device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_set_op_mode ( accel32_t *ctx, uint8_t op_mode );

/**
 * @brief Accel 32 set full-scale range function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 15G,
 *                  @li @c 1 - 30G,
 *                  @li @c 2 - 60G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_set_accel_fsr ( accel32_t *ctx, uint8_t fsr );

/**
 * @brief Accel 32 get data ready status function.
 * @details This function checks if new accelerometer data is available.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel32_get_drdy ( accel32_t *ctx, uint8_t *drdy );

/**
 * @brief Accel 32 get accelerometer data function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (g).
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[out] accel : Pointer to store the acceleration values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (data not ready).
 * @note None.
 */
err_t accel32_get_accel ( accel32_t *ctx, accel32_axes_t *accel );

/**
 * @brief Accel 32 get temperature function.
 * @details This function reads the internal temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[out] temp : Pointer to store the temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (data not ready).
 * @note None.
 */
err_t accel32_get_temp ( accel32_t *ctx, float *temp );

/**
 * @brief Accel 32 get accelerometer and temperature data function.
 * @details This function reads both accelerometer and temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel32_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store the acceleration and temperature values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (data not ready).
 * @note None.
 */
err_t accel32_get_data ( accel32_t *ctx, accel32_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ACCEL32_H

/*! @} */ // accel32

// ------------------------------------------------------------------------ END

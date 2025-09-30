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
 * @file ambient25.h
 * @brief This file contains API for Ambient 25 Click Driver.
 */

#ifndef AMBIENT25_H
#define AMBIENT25_H

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
 * @addtogroup ambient25 Ambient 25 Click Driver
 * @brief API for configuring and manipulating Ambient 25 Click driver.
 * @{
 */

/**
 * @defgroup ambient25_reg Ambient 25 Registers List
 * @brief List of registers of Ambient 25 Click driver.
 */

/**
 * @addtogroup ambient25_reg
 * @{
 */

/**
 * @brief Ambient 25 register list.
 * @details Specified register list of Ambient 25 Click driver.
 */
#define AMBIENT25_REG_MOD_CHANNEL_CTRL                  0x40
#define AMBIENT25_REG_ENABLE                            0x80
#define AMBIENT25_REG_MEAS_MODE0                        0x81
#define AMBIENT25_REG_MEAS_MODE1                        0x82
#define AMBIENT25_REG_SAMPLE_TIME0                      0x83
#define AMBIENT25_REG_SAMPLE_TIME1                      0x84
#define AMBIENT25_REG_ALS_NR_SAMPLES0                   0x85
#define AMBIENT25_REG_ALS_NR_SAMPLES1                   0x86
#define AMBIENT25_REG_FD_NR_SAMPLES0                    0x87
#define AMBIENT25_REG_FD_NR_SAMPLES1                    0x88
#define AMBIENT25_REG_WTIME                             0x89
#define AMBIENT25_REG_AILT0                             0x8A
#define AMBIENT25_REG_AILT1                             0x8B
#define AMBIENT25_REG_AILT2                             0x8C
#define AMBIENT25_REG_AIHT0                             0x8D
#define AMBIENT25_REG_AIHT1                             0x8E
#define AMBIENT25_REG_AIHT2                             0x8F
#define AMBIENT25_REG_AUX_ID                            0x90
#define AMBIENT25_REG_REV_ID                            0x91
#define AMBIENT25_REG_ID                                0x92
#define AMBIENT25_REG_STATUS                            0x93
#define AMBIENT25_REG_ALS_STATUS                        0x94
#define AMBIENT25_REG_ALS_DATA0_LSB                     0x95
#define AMBIENT25_REG_ALS_DATA0_MSB                     0x96
#define AMBIENT25_REG_ALS_DATA1_LSB                     0x97
#define AMBIENT25_REG_ALS_DATA1_MSB                     0x98
#define AMBIENT25_REG_ALS_STATUS2                       0x9B
#define AMBIENT25_REG_STATUS2                           0x9D
#define AMBIENT25_REG_STATUS3                           0x9E
#define AMBIENT25_REG_STATUS4                           0x9F
#define AMBIENT25_REG_STATUS5                           0xA0
#define AMBIENT25_REG_CFG0                              0xA1
#define AMBIENT25_REG_CFG1                              0xA2
#define AMBIENT25_REG_CFG2                              0xA3
#define AMBIENT25_REG_CFG3                              0xA4
#define AMBIENT25_REG_CFG4                              0xA5
#define AMBIENT25_REG_CFG5                              0xA6
#define AMBIENT25_REG_CFG6                              0xA7
#define AMBIENT25_REG_CFG7                              0xA8
#define AMBIENT25_REG_CFG8                              0xA9
#define AMBIENT25_REG_CFG9                              0xAA
#define AMBIENT25_REG_AGC_NR_SAMPLES0                   0xAC
#define AMBIENT25_REG_AGC_NR_SAMPLES1                   0xAD
#define AMBIENT25_REG_TRIGGER_MODE                      0xAE
#define AMBIENT25_REG_CONTROL                           0xB1
#define AMBIENT25_REG_INTENAB                           0xBA
#define AMBIENT25_REG_SIEN                              0xBB
#define AMBIENT25_REG_MOD_COMP_CFG1                     0xCE
#define AMBIENT25_REG_MEAS_SEQR_FD_0                    0xCF
#define AMBIENT25_REG_MEAS_SEQR_ALS_1                   0xD0
#define AMBIENT25_REG_MEAS_SEQR_APERS_AND_VSYNC_WAIT    0xD1
#define AMBIENT25_REG_MEAS_SEQR_RESIDUAL_0              0xD2
#define AMBIENT25_REG_MEAS_SEQR_RESIDUAL_1_AND_WAIT     0xD3
#define AMBIENT25_REG_MEAS_SEQR_STEP0_MOD_GAINX_L       0xD4
#define AMBIENT25_REG_MEAS_SEQR_STEP1_MOD_GAINX_L       0xD6
#define AMBIENT25_REG_MEAS_SEQR_STEP2_MOD_GAINX_L       0xD8
#define AMBIENT25_REG_MEAS_SEQR_STEP3_MOD_GAINX_L       0xDA
#define AMBIENT25_REG_MEAS_SEQR_STEP0_MOD_PHDX_SMUX_L   0xDC
#define AMBIENT25_REG_MEAS_SEQR_STEP0_MOD_PHDX_SMUX_H   0xDD
#define AMBIENT25_REG_MEAS_SEQR_STEP1_MOD_PHDX_SMUX_L   0xDE
#define AMBIENT25_REG_MEAS_SEQR_STEP1_MOD_PHDX_SMUX_H   0xDF
#define AMBIENT25_REG_MEAS_SEQR_STEP2_MOD_PHDX_SMUX_L   0xE0
#define AMBIENT25_REG_MEAS_SEQR_STEP2_MOD_PHDX_SMUX_H   0xE1
#define AMBIENT25_REG_MEAS_SEQR_STEP3_MOD_PHDX_SMUX_L   0xE2
#define AMBIENT25_REG_MEAS_SEQR_STEP3_MOD_PHDX_SMUX_H   0xE3
#define AMBIENT25_REG_MOD_CALIB_CFG0                    0xE4
#define AMBIENT25_REG_MOD_CALIB_CFG2                    0xE6
#define AMBIENT25_REG_VSYNC_PERIOD0                     0xF2
#define AMBIENT25_REG_VSYNC_PERIOD1                     0xF3
#define AMBIENT25_REG_VSYNC_PERIOD_TARGET0              0xF4
#define AMBIENT25_REG_VSYNC_PERIOD_TARGET1              0xF5
#define AMBIENT25_REG_VSYNC_CONTROL                     0xF6
#define AMBIENT25_REG_VSYNC_CFG                         0xF7
#define AMBIENT25_REG_VSYNC_GPIO_INT                    0xF8
#define AMBIENT25_REG_MOD_FIFO_DATA_CFG0                0xF9
#define AMBIENT25_REG_MOD_FIFO_DATA_CFG1                0xFA
#define AMBIENT25_REG_FIFO_THR                          0xFC
#define AMBIENT25_REG_FIFO_STATUS0                      0xFD
#define AMBIENT25_REG_FIFO_STATUS1                      0xFE
#define AMBIENT25_REG_FIFO_DATA                         0xFF

/*! @} */ // ambient25_reg

/**
 * @defgroup ambient25_set Ambient 25 Registers Settings
 * @brief Settings for registers of Ambient 25 Click driver.
 */

/**
 * @addtogroup ambient25_set
 * @{
 */

/**
 * @brief Ambient 25 ENABLE register setting.
 * @details Specified setting for ENABLE register of Ambient 25 Click driver.
 */
#define AMBIENT25_ENABLE_FDEN                           0x40
#define AMBIENT25_ENABLE_AEN                            0x02
#define AMBIENT25_ENABLE_PON                            0x01

/**
 * @brief Ambient 25 WTIME register setting.
 * @details Specified setting for WTIME register of Ambient 25 Click driver.
 */
#define AMBIENT25_WTIME_DEFAULT                         0x46

/**
 * @brief Ambient 25 TRIGGER_MODE register setting.
 * @details Specified setting for TRIGGER_MODE register of Ambient 25 Click driver.
 */
#define AMBIENT25_TRIGGER_MODE_OFF                      0x00
#define AMBIENT25_TRIGGER_MODE_NORMAL                   0x01
#define AMBIENT25_TRIGGER_MODE_LONG                     0x02
#define AMBIENT25_TRIGGER_MODE_FAST                     0x03
#define AMBIENT25_TRIGGER_MODE_FASTLONG                 0x04
#define AMBIENT25_TRIGGER_MODE_VSYNC                    0x05
#define AMBIENT25_TRIGGER_MODE_MASK                     0x07

/**
 * @brief Ambient 25 INTENAB register setting.
 * @details Specified setting for INTENAB register of Ambient 25 Click driver.
 */
#define AMBIENT25_INTENAB_MIEN                          0x80
#define AMBIENT25_INTENAB_AIEN                          0x08
#define AMBIENT25_INTENAB_FIEN                          0x04
#define AMBIENT25_INTENAB_SIEN                          0x01

/**
 * @brief Ambient 25 MEAS_MODE1 register setting.
 * @details Specified setting for MEAS_MODE1 register of Ambient 25 Click driver.
 */
#define AMBIENT25_MEAS_MODE1_MOD_FIFO_FD_END_MARKER_WEN 0x80
#define AMBIENT25_MEAS_MODE1_MOD_FIFO_FD_CHECKSUM_WEN   0x40
#define AMBIENT25_MEAS_MODE1_MOD_FIFO_FD_GAIN_WEN       0x20
#define AMBIENT25_MEAS_MODE1_ALS_MSB_POSITION_DEFAULT   0x08
#define AMBIENT25_MEAS_MODE1_ALS_MSB_POSITION_MASK      0x1F

/**
 * @brief Ambient 25 modulator gain setting.
 * @details Specified setting for modulator gain of Ambient 25 Click driver.
 */
#define AMBIENT25_GAIN_MOD1_HALF                        0x00
#define AMBIENT25_GAIN_MOD1_1X                          0x10
#define AMBIENT25_GAIN_MOD1_2X                          0x20
#define AMBIENT25_GAIN_MOD1_4X                          0x30
#define AMBIENT25_GAIN_MOD1_8X                          0x40
#define AMBIENT25_GAIN_MOD1_16X                         0x50
#define AMBIENT25_GAIN_MOD1_32X                         0x60
#define AMBIENT25_GAIN_MOD1_64X                         0x70
#define AMBIENT25_GAIN_MOD1_128X                        0x80
#define AMBIENT25_GAIN_MOD1_256X                        0x90
#define AMBIENT25_GAIN_MOD1_512X                        0xA0
#define AMBIENT25_GAIN_MOD1_1024X                       0xB0
#define AMBIENT25_GAIN_MOD1_2048X                       0xC0
#define AMBIENT25_GAIN_MOD1_4096X                       0xD0
#define AMBIENT25_GAIN_MOD0_HALF                        0x00
#define AMBIENT25_GAIN_MOD0_1X                          0x01
#define AMBIENT25_GAIN_MOD0_2X                          0x02
#define AMBIENT25_GAIN_MOD0_4X                          0x03
#define AMBIENT25_GAIN_MOD0_8X                          0x04
#define AMBIENT25_GAIN_MOD0_16X                         0x05
#define AMBIENT25_GAIN_MOD0_32X                         0x06
#define AMBIENT25_GAIN_MOD0_64X                         0x07
#define AMBIENT25_GAIN_MOD0_128X                        0x08
#define AMBIENT25_GAIN_MOD0_256X                        0x09
#define AMBIENT25_GAIN_MOD0_512X                        0x0A
#define AMBIENT25_GAIN_MOD0_1024X                       0x0B
#define AMBIENT25_GAIN_MOD0_2048X                       0x0C
#define AMBIENT25_GAIN_MOD0_4096X                       0x0D

/**
 * @brief Ambient 25 FIFO interrupt threshold setting.
 * @details Specified setting for FIFO interrupt threshold of Ambient 25 Click driver.
 */
#define AMBIENT25_FIFO_THR_DEFAULT                      5

/**
 * @brief Ambient 25 CONTROL register setting.
 * @details Specified setting for CONTROL register of Ambient 25 Click driver.
 */
#define AMBIENT25_CONTROL_SOFT_RESET                    0x08
#define AMBIENT25_CONTROL_FIFO_CLR                      0x02
#define AMBIENT25_CONTROL_CLEAR_SAI_ACTIVE              0x01

/**
 * @brief Ambient 25 ALS data saturation setting.
 * @details Specified setting for ALS data saturation of Ambient 25 Click driver.
 */
#define AMBIENT25_ALS_DATA_SATURATION                   0xFFFF

/**
 * @brief Ambient 25 device ID value.
 * @details Specified device ID value of Ambient 25 Click driver.
 */
#define AMBIENT25_DEVICE_ID                             0x5C

/**
 * @brief Ambient 25 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 25 Click driver.
 */
#define AMBIENT25_DEVICE_ADDRESS                        0x39

/*! @} */ // ambient25_set

/**
 * @defgroup ambient25_map Ambient 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 25 Click driver.
 */

/**
 * @addtogroup ambient25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 25 Click to the selected MikroBUS.
 */
#define AMBIENT25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.vsync = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient25_map
/*! @} */ // ambient25

/**
 * @brief Ambient 25 Click data object.
 * @details Data object definition of Ambient 25 Click driver.
 */
typedef struct
{
    uint16_t als_data_0;        /**< ALS data 0 counts. */
    uint16_t als_data_1;        /**< ALS data 1 counts. */
    
} ambient25_data_t;

/**
 * @brief Ambient 25 Click context object.
 * @details Context object definition of Ambient 25 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */
    digital_out_t vsync;        /**< Synchronization pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} ambient25_t;

/**
 * @brief Ambient 25 Click configuration object.
 * @details Configuration object definition of Ambient 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t vsync;           /**< Synchronization pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ambient25_cfg_t;

/**
 * @brief Ambient 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT25_OK = 0,
    AMBIENT25_ERROR = -1

} ambient25_return_value_t;

/*!
 * @addtogroup ambient25 Ambient 25 Click Driver
 * @brief API for configuring and manipulating Ambient 25 Click driver.
 * @{
 */

/**
 * @brief Ambient 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient25_cfg_setup ( ambient25_cfg_t *cfg );

/**
 * @brief Ambient 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_init ( ambient25_t *ctx, ambient25_cfg_t *cfg );

/**
 * @brief Ambient 25 default configuration function.
 * @details This function executes a default configuration of Ambient 25
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient25_default_cfg ( ambient25_t *ctx );

/**
 * @brief Ambient 25 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_write_regs ( ambient25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 25 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_read_regs ( ambient25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 25 write reg function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_write_reg ( ambient25_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 25 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_read_reg ( ambient25_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 25 write reg word function.
 * @details This function writes a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_write_reg_word ( ambient25_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Ambient 25 read reg word function.
 * @details This function reads a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_read_reg_word ( ambient25_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Ambient 25 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_check_communication ( ambient25_t *ctx );

/**
 * @brief Ambient 25 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ambient25_enable_device ( ambient25_t *ctx );

/**
 * @brief Ambient 25 disable device function.
 * @details This function enables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ambient25_disable_device ( ambient25_t *ctx );

/**
 * @brief Ambient 25 set vsync pin state function.
 * @details This function sets the VSYNC pin state.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ambient25_set_vsync_pin ( ambient25_t *ctx, uint8_t state );

/**
 * @brief Ambient 25 get int pin state function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient25_get_int_pin ( ambient25_t *ctx );

/**
 * @brief Ambient 25 soft reset function.
 * @details This function executes the defice software reset command.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_soft_reset ( ambient25_t *ctx );

/**
 * @brief Ambient 25 clear fifo function.
 * @details This function clears the FIFO buffers and interrupts.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_clear_fifo ( ambient25_t *ctx );

/**
 * @brief Ambient 25 read fifo size function.
 * @details This function reads the number of data bytes available to read from FIFO.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[out] fifo_size : Number of data bytes available to read from FIFO.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_read_fifo_size ( ambient25_t *ctx, uint16_t *fifo_size );

/**
 * @brief Ambient 25 read data function.
 * @details This function checks if the als measurement data are ready for all channels and reads them.
 * @param[in] ctx : Click context object.
 * See #ambient25_t object definition for detailed explanation.
 * @param[out] data_out : ALS measurements data object.
 * See #ambient25_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient25_read_data ( ambient25_t *ctx, ambient25_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT25_H

/*! @} */ // ambient25

// ------------------------------------------------------------------------ END

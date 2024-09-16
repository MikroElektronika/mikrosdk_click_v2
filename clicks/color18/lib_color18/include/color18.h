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
 * @file color18.h
 * @brief This file contains API for Color 18 Click Driver.
 */

#ifndef COLOR18_H
#define COLOR18_H

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
 * @addtogroup color18 Color 18 Click Driver
 * @brief API for configuring and manipulating Color 18 Click driver.
 * @{
 */

/**
 * @defgroup color18_reg Color 18 Registers List
 * @brief List of registers of Color 18 Click driver.
 */

/**
 * @addtogroup color18_reg
 * @{
 */

/**
 * @brief Color 18 register list.
 * @details Specified register list of Color 18 Click driver.
 */
#define COLOR18_REG_CONTROL_SCL                     0x24
#define COLOR18_REG_MOD_OFFSET0_LSB                 0x40
#define COLOR18_REG_MOD_OFFSET0_MSB                 0x41
#define COLOR18_REG_MOD_OFFSET1_LSB                 0x42
#define COLOR18_REG_MOD_OFFSET1_MSB                 0x43
#define COLOR18_REG_MOD_OFFSET2_LSB                 0x44
#define COLOR18_REG_MOD_OFFSET2_MSB                 0x45
#define COLOR18_REG_MOD_OFFSET3_LSB                 0x46
#define COLOR18_REG_MOD_OFFSET3_MSB                 0x47
#define COLOR18_REG_MOD_OFFSET4_LSB                 0x48
#define COLOR18_REG_MOD_OFFSET4_MSB                 0x49
#define COLOR18_REG_MOD_OFFSET5_LSB                 0x4A
#define COLOR18_REG_MOD_OFFSET5_MSB                 0x4B
#define COLOR18_REG_MOD_OFFSET6_LSB                 0x4C
#define COLOR18_REG_MOD_OFFSET6_MSB                 0x4D
#define COLOR18_REG_MOD_OFFSET7_LSB                 0x4E
#define COLOR18_REG_MOD_OFFSET7_MSB                 0x4F
#define COLOR18_REG_OSCEN                           0x7F
#define COLOR18_REG_ENABLE                          0x80
#define COLOR18_REG_MEAS_MODE0                      0x81
#define COLOR18_REG_MEAS_MODE1                      0x82
#define COLOR18_REG_SAMPLE_TIME0                    0x83
#define COLOR18_REG_SAMPLE_TIME1                    0x84
#define COLOR18_REG_SAMPLE_TIME_ALTERNATIVE0        0x85
#define COLOR18_REG_SAMPLE_TIME_ALTERNATIVE1        0x86
#define COLOR18_REG_ALS_NR_SAMPLES0                 0x87
#define COLOR18_REG_ALS_NR_SAMPLES1                 0x88
#define COLOR18_REG_ALS_NR_SAMPLES_ALTERNATIVE0     0x89
#define COLOR18_REG_ALS_NR_SAMPLES_ALTERNATIVE1     0x8A
#define COLOR18_REG_FD_NR_SAMPLES0                  0x8B
#define COLOR18_REG_FD_NR_SAMPLES1                  0x8C
#define COLOR18_REG_FD_NR_SAMPLES_ALTERNATIVE0      0x8D
#define COLOR18_REG_FD_NR_SAMPLES_ALTERNATIVE1      0x8E
#define COLOR18_REG_WTIME                           0x8F
#define COLOR18_REG_AUX_ID                          0x90
#define COLOR18_REG_REV_ID                          0x91
#define COLOR18_REG_ID                              0x92
#define COLOR18_REG_AILT0                           0x93
#define COLOR18_REG_AILT1                           0x94
#define COLOR18_REG_AILT2                           0x95
#define COLOR18_REG_AIHT0                           0x96
#define COLOR18_REG_AIHT1                           0x97
#define COLOR18_REG_AIHT2                           0x98
#define COLOR18_REG_AGC_NR_SAMPLES0                 0x99
#define COLOR18_REG_AGC_NR_SAMPLES1                 0x9A
#define COLOR18_REG_STATUS                          0x9B
#define COLOR18_REG_STATUS2                         0x9C
#define COLOR18_REG_STATUS3                         0x9D
#define COLOR18_REG_STATUS4                         0x9E
#define COLOR18_REG_STATUS5                         0x9F
#define COLOR18_REG_STATUS6                         0xA0
#define COLOR18_REG_CFG0                            0xA1
#define COLOR18_REG_CFG1                            0xA2
#define COLOR18_REG_CFG2                            0xA3
#define COLOR18_REG_CFG3                            0xA4
#define COLOR18_REG_CFG4                            0xA5
#define COLOR18_REG_CFG5                            0xA6
#define COLOR18_REG_CFG6                            0xA7
#define COLOR18_REG_CFG7                            0xA8
#define COLOR18_REG_CFG8                            0xA9
#define COLOR18_REG_CFG9                            0xAA
#define COLOR18_REG_MOD_CHANNEL_CTRL                0xAB
#define COLOR18_REG_TRIGGER_MODE                    0xAD
#define COLOR18_REG_OSC_TUNE                        0xAE
#define COLOR18_REG_VSYNC_GPIO_INT                  0xB0
#define COLOR18_REG_INTENAB                         0xBA
#define COLOR18_REG_SIEN                            0xBB
#define COLOR18_REG_CONTROL                         0xBC
#define COLOR18_REG_ALS_DATA_STATUS                 0xBD
#define COLOR18_REG_ALS_DATA_FIRST                  0xBE
#define COLOR18_REG_ALS_DATA                        0xBF
#define COLOR18_REG_MEAS_SEQR_STEP0_MOD_GAINX_0     0xC0
#define COLOR18_REG_MEAS_SEQR_STEP0_MOD_GAINX_1     0xC1
#define COLOR18_REG_MEAS_SEQR_STEP0_MOD_GAINX_2     0xC2
#define COLOR18_REG_MEAS_SEQR_STEP0_MOD_GAINX_3     0xC3
#define COLOR18_REG_MEAS_SEQR_STEP1_MOD_GAINX_0     0xC4
#define COLOR18_REG_MEAS_SEQR_STEP1_MOD_GAINX_1     0xC5
#define COLOR18_REG_MEAS_SEQR_STEP1_MOD_GAINX_2     0xC6
#define COLOR18_REG_MEAS_SEQR_STEP1_MOD_GAINX_3     0xC7
#define COLOR18_REG_MEAS_SEQR_STEP2_MOD_GAINX_0     0xC8
#define COLOR18_REG_MEAS_SEQR_STEP2_MOD_GAINX_1     0xC9
#define COLOR18_REG_MEAS_SEQR_STEP2_MOD_GAINX_2     0xCA
#define COLOR18_REG_MEAS_SEQR_STEP2_MOD_GAINX_3     0xCB
#define COLOR18_REG_MEAS_SEQR_STEP3_MOD_GAINX_0     0xCC
#define COLOR18_REG_MEAS_SEQR_STEP3_MOD_GAINX_1     0xCD
#define COLOR18_REG_MEAS_SEQR_STEP3_MOD_GAINX_2     0xCE
#define COLOR18_REG_MEAS_SEQR_STEP3_MOD_GAINX_3     0xCF
#define COLOR18_REG_MEAS_SEQR_STEP0_FD              0xD0
#define COLOR18_REG_MEAS_SEQR_STEP1_FD              0xD1
#define COLOR18_REG_MEAS_SEQR_STEP2_FD              0xD2
#define COLOR18_REG_MEAS_SEQR_STEP3_FD              0xD3
#define COLOR18_REG_MEAS_SEQR_STEP0_RESIDUAL        0xD4
#define COLOR18_REG_MEAS_SEQR_STEP1_RESIDUAL        0xD5
#define COLOR18_REG_MEAS_SEQR_STEP2_RESIDUAL        0xD6
#define COLOR18_REG_MEAS_SEQR_STEP3_RESIDUAL        0xD7
#define COLOR18_REG_MEAS_SEQR_STEP0_ALS             0xD8
#define COLOR18_REG_MEAS_SEQR_STEP1_ALS             0xD9
#define COLOR18_REG_MEAS_SEQR_STEP2_ALS             0xDA
#define COLOR18_REG_MEAS_SEQR_STEP3_ALS             0xDB
#define COLOR18_REG_MEAS_SEQR_APERS_AND_VSYNC_WAIT  0xDC
#define COLOR18_REG_MEAS_SEQR_AGC                   0xDD
#define COLOR18_REG_MEAS_SEQR_SMUX_AND_SAMPLE_TIME  0xDE
#define COLOR18_REG_MEAS_SEQR_WAIT_AND_TS_ENABLE    0xDF
#define COLOR18_REG_MOD_CALIB_CFG0                  0xE0
#define COLOR18_REG_MOD_CALIB_CFG2                  0xE2
#define COLOR18_REG_MOD_CALIB_CFG3                  0xE3
#define COLOR18_REG_MOD_COMP_CFG2                   0xE7
#define COLOR18_REG_MOD_RESIDUAL_CFG0               0xE8
#define COLOR18_REG_MOD_RESIDUAL_CFG1               0xE9
#define COLOR18_REG_MOD_RESIDUAL_CFG2               0xEA
#define COLOR18_REG_VSYNC_DELAY_CFG0                0xEB
#define COLOR18_REG_VSYNC_DELAY_CFG1                0xEC
#define COLOR18_REG_VSYNC_PERIOD0                   0xED
#define COLOR18_REG_VSYNC_PERIOD1                   0xEE
#define COLOR18_REG_VSYNC_PERIOD_TARGET0            0xEF
#define COLOR18_REG_VSYNC_PERIOD_TARGET1            0xF0
#define COLOR18_REG_VSYNC_CONTROL                   0xF1
#define COLOR18_REG_VSYNC_CFG                       0xF2
#define COLOR18_REG_FIFO_THR                        0xF3
#define COLOR18_REG_MOD_FIFO_DATA_CFG0              0xF4
#define COLOR18_REG_MOD_FIFO_DATA_CFG1              0xF5
#define COLOR18_REG_MOD_FIFO_DATA_CFG2              0xF6
#define COLOR18_REG_MOD_FIFO_DATA_CFG3              0xF7
#define COLOR18_REG_MOD_FIFO_DATA_CFG4              0xF8
#define COLOR18_REG_MOD_FIFO_DATA_CFG5              0xF9
#define COLOR18_REG_MOD_FIFO_DATA_CFG6              0xFA
#define COLOR18_REG_MOD_FIFO_DATA_CFG7              0xFB
#define COLOR18_REG_FIFO_STATUS0                    0xFC
#define COLOR18_REG_FIFO_STATUS1                    0xFD
#define COLOR18_REG_FIFO_DATA_PROTOCOL              0xFE
#define COLOR18_REG_FIFO_DATA                       0xFF

/*! @} */ // color18_reg

/**
 * @defgroup color18_set Color 18 Registers Settings
 * @brief Settings for registers of Color 18 Click driver.
 */

/**
 * @addtogroup color18_set
 * @{
 */

/**
 * @brief Color 18 CONTROL_SCL register setting.
 * @details Specified setting for CONTROL_SCL register of Color 18 Click driver.
 */
#define COLOR18_CONTROL_SCL_SOFT_RESET              0x01

/**
 * @brief Color 18 OSCEN register setting.
 * @details Specified setting for OSCEN register of Color 18 Click driver.
 */
#define COLOR18_OSCEN_PON_INIT                      0x04
#define COLOR18_OSCEN_OSCEN_STATUS                  0x02
#define COLOR18_OSCEN_OSCEN                         0x01

/**
 * @brief Color 18 ENABLE register setting.
 * @details Specified setting for ENABLE register of Color 18 Click driver.
 */
#define COLOR18_ENABLE_FDEN                         0x40
#define COLOR18_ENABLE_AEN                          0x02
#define COLOR18_ENABLE_PON                          0x01

/**
 * @brief Color 18 WTIME register setting.
 * @details Specified setting for WTIME register of Color 18 Click driver.
 */
#define COLOR18_WTIME_DEFAULT                       0x46

/**
 * @brief Color 18 TRIGGER_MODE register setting.
 * @details Specified setting for TRIGGER_MODE register of Color 18 Click driver.
 */
#define COLOR18_TRIGGER_MODE_OFF                    0x00
#define COLOR18_TRIGGER_MODE_NORMAL                 0x01
#define COLOR18_TRIGGER_MODE_LONG                   0x02
#define COLOR18_TRIGGER_MODE_FAST                   0x03
#define COLOR18_TRIGGER_MODE_FASTLONG               0x04
#define COLOR18_TRIGGER_MODE_VSYNC                  0x05
#define COLOR18_TRIGGER_MODE_MASK                   0x07

/**
 * @brief Color 18 INTENAB register setting.
 * @details Specified setting for INTENAB register of Color 18 Click driver.
 */
#define COLOR18_INTENAB_MIEN                        0x80
#define COLOR18_INTENAB_AIEN                        0x08
#define COLOR18_INTENAB_FIEN                        0x04
#define COLOR18_INTENAB_SIEN                        0x01

/**
 * @brief Color 18 FIFO interrupt threshold setting.
 * @details Specified setting for FIFO interrupt threshold of Color 18 Click driver.
 */
#define COLOR18_FIFO_THR_DEFAULT                    15

/**
 * @brief Color 18 CONTROL register setting.
 * @details Specified setting for CONTROL register of Color 18 Click driver.
 */
#define COLOR18_CONTROL_FIFO_CLR                    0x02
#define COLOR18_CONTROL_CLEAR_SAI_ACTIVE            0x01

/**
 * @brief Color 18 device ID value.
 * @details Specified device ID value of Color 18 Click driver.
 */
#define COLOR18_DEVICE_ID                           0x68

/**
 * @brief Color 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 18 Click driver.
 */
#define COLOR18_DEVICE_ADDRESS                      0x39

/*! @} */ // color18_set

/**
 * @defgroup color18_map Color 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 18 Click driver.
 */

/**
 * @addtogroup color18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 18 Click to the selected MikroBUS.
 */
#define COLOR18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.vsync = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color18_map
/*! @} */ // color18

/**
 * @brief Color 18 Click data object.
 * @details Data object definition of Color 18 Click driver.
 */
typedef struct
{
    uint16_t x;                 /**< X/RED (MOD0) data counts. */
    uint16_t y;                 /**< Y/GREEN (MOD1) data counts. */
    uint16_t z;                 /**< Z/BLUE (MOD2) data counts. */
    uint16_t ir;                /**< IR (MOD3) data counts. */
    uint16_t hgl;               /**< HgL (MOD4) data counts. */
    uint16_t hgh;               /**< HgH (MOD5) data counts. */
    uint16_t clear;             /**< Clear (MOD6) data counts. */
    uint16_t flicker;           /**< Flicker (MOD7) data counts. */
    
} color18_data_t;

/**
 * @brief Color 18 Click context object.
 * @details Context object definition of Color 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t vsync;        /**< Synchronization pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} color18_t;

/**
 * @brief Color 18 Click configuration object.
 * @details Configuration object definition of Color 18 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t vsync;           /**< Synchronization pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color18_cfg_t;

/**
 * @brief Color 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR18_OK = 0,
    COLOR18_ERROR = -1

} color18_return_value_t;

/*!
 * @addtogroup color18 Color 18 Click Driver
 * @brief API for configuring and manipulating Color 18 Click driver.
 * @{
 */

/**
 * @brief Color 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color18_cfg_setup ( color18_cfg_t *cfg );

/**
 * @brief Color 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_init ( color18_t *ctx, color18_cfg_t *cfg );

/**
 * @brief Color 18 default configuration function.
 * @details This function executes a default configuration of Color 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color18_default_cfg ( color18_t *ctx );

/**
 * @brief Color 18 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_write_regs ( color18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 18 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_read_regs ( color18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 18 write reg function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_write_reg ( color18_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Color 18 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_read_reg ( color18_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Color 18 write reg word function.
 * @details This function writes a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_write_reg_word ( color18_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Color 18 read reg word function.
 * @details This function reads a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_read_reg_word ( color18_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Color 18 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_check_communication ( color18_t *ctx );

/**
 * @brief Color 18 set vsync pin state function.
 * @details This function sets the VSYNC pin state.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void color18_set_vsync_pin ( color18_t *ctx, uint8_t state );

/**
 * @brief Color 18 get int pin state function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t color18_get_int_pin ( color18_t *ctx );

/**
 * @brief Color 18 soft reset function.
 * @details This function executes the defice software reset command.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_soft_reset ( color18_t *ctx );

/**
 * @brief Color 18 clear fifo function.
 * @details This function clears the FIFO buffers and interrupts.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_clear_fifo ( color18_t *ctx );

/**
 * @brief Color 18 read fifo size function.
 * @details This function reads the number of data bytes available to read from FIFO.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[out] fifo_size : Number of data bytes available to read from FIFO.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_read_fifo_size ( color18_t *ctx, uint16_t *fifo_size );

/**
 * @brief Color 18 read data function.
 * @details This function checks if the color measurement data are ready for all channels and reads them.
 * @param[in] ctx : Click context object.
 * See #color18_t object definition for detailed explanation.
 * @param[out] data_out : Color measurements data object.
 * See #color18_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color18_read_data ( color18_t *ctx, color18_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // COLOR18_H

/*! @} */ // color18

// ------------------------------------------------------------------------ END
